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
/// \file   Test.c
///
/// \brief  Unit Test Cases for Anima (animations)
///
/// \author Georgiana Sevastre (F54430C)
///         mailTo:georgiana.sevastre[at]marelli.com
//-----------------------------------------------------------------------------

//==============================================================================
//  Files covered by this module unit test:
//            - ctaaAnima.c
//            - Anima.c
//            - Anima_RteAccess.c
//            - Anima_CodPrj.c
//            - AnimMa.c
//            - AnimMa_Blocks.c
//==============================================================================

//=============================================================================
// Includes
//=============================================================================
#include "Test_Coding_Cfg.h"
#include "Test_DatasetData.h"
#include "Test_Stubs.h"
#include "Test.h"

//=============================================================================
//  Module Test Cases
//=============================================================================

//-----------------------------------------------------------------------------
/// Initialize stubs and globals
//-----------------------------------------------------------------------------
void  Mt_CtrlLed_PreTest(void)
{
    int i;
    for (i = 0; i < ANIMMA_NR_PIXELS; i++)
    {
        AnimMaRamp_aucPxlIntTgt[i] = 0;
        AnimMaRamp_aucPxlIntInc[i] = 0;
        AnimMaRamp_aucPxlIntDec[i] = 0;
        Anima_TgtAniArr.unTgtAni[i] = 0u;
    }

    Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_NONE;

    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_None;
    Rte_Read_IoHwAbUser_GetMountingSide_Param1 = eMountedLeft;
    riAnima_Init();
    rpAnima_Cycle0();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimDoRamps_TestCase1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that ramps are calculated by increments and decrements. Check for overflow protection.
///                     Use different values for increments and decrements.
///                     Increment with value 1: 0, 1, 2, 3, 4, ..., 100 (and not beyond)
///                     Decrement with value 2: 98, 96, 94, 92, 90, ..., 0 (and not below)
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input   AnimMaRamp_aucPxlIntDec[0] = 2;
/// \input   AnimMaRamp_aucPxlIntInc[0] = 1;
/// \input   AnimMaRamp_aucPxlIntTgt[0] = 100;
///
///   - Expectations:
///
/// \output  Anima_TgtAniArr.unTgtAni[0] = aunExpInc[i]
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimDoRamps_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    int i;
    static const uint16 aunExpInc[110] = { 327, 654, 981, 1308, 1635, 1962, 2289, 2616, 2943, 3270, 3597, 3924, 4251, 4578, 4905, 5232, 5559, 5886, 6213, 6540, 6867, 7194, 7521, 7848, 8175, 8502, 8829, 9156, 9483, 9810, 10137, 10464, 10791, 11118, 11445, 11772, 12099, 12426, 12753, 13080, 13407, 13734, 14061, 14388, 14715, 15042, 15369, 15696, 16023, 16350, 16677, 17004, 17331, 17658, 17985, 18312, 18639, 18966, 19293, 19620, 19947, 20274, 20601, 20928, 21255, 21582, 21909, 22236, 22563, 22890, 23217, 23544, 23871, 24198, 24525, 24852, 25179, 25506, 25833, 26160, 26487, 26814, 27141, 27468, 27795, 28122, 28449, 28776, 29103, 29430, 29757, 30084, 30411, 30738, 31065, 31392, 31719, 32046, 32373, 32700, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768 };
    static const uint16 aunExpDec[110] = { 32113, 31458, 30803, 30148, 29493, 28838, 28183, 27528, 26873, 26218, 25563, 24908, 24253, 23598, 22943, 22288, 21633, 20978, 20323, 19668, 19013, 18358, 17703, 17048, 16393, 15738, 15083, 14428, 13773, 13118, 12463, 11808, 11153, 10498, 9843, 9188, 8533, 7878, 7223, 6568, 5913, 5258, 4603, 3948, 3293, 2638, 1983, 1328, 673, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Start(" Mt_CtrlLed_DoRamps_TestCase1.txt");
#endif
    memcpy(&AnimMa_pCodingData->Animation.AnimationByteStream.aucByteStream[0], &Anima_CodPrj_aucDataset0_Run[0], sizeof(Anima_CodPrj_aucDataset0_Run[0] / sizeof(uint8)));
    Mt_CtrlLed_PreTest();
    AnimMaRamp_aucPxlIntDec[0] = 2u;
    AnimMaRamp_aucPxlIntInc[0] = 1u;
    AnimMaRamp_aucPxlIntTgt[0] = 100u;  // step 1 - increment from 0 to 100

    for (i = 0; i < 110; i++)
    {
        //Step 3) Call FUT
        Anima_DoRamps();
#if CFG_ENABLE_LOGGING == 1
        Mt_CtrlLed_Log("%d, ", Anima_TgtAniArr.unTgtAni[0]);
#endif
        //Step 4) Check expected output values
        AL_UNITTEST_CHECK(Anima_TgtAniArr.unTgtAni[0], aunExpInc[i], == );
    }
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log("\n");
#endif

    AnimMaRamp_aucPxlIntTgt[0] = 0u;  // step 2 - decrement from 100 to 0

    for (i = 0; i < 110; i++)
    {
        Anima_DoRamps();
#if CFG_ENABLE_LOGGING == 1
        Mt_CtrlLed_Log("%d, ", Anima_TgtAniArr.unTgtAni[0]);
#endif
        //Step 4) Check expected output values
        AL_UNITTEST_CHECK(Anima_TgtAniArr.unTgtAni[0], aunExpDec[i], == );
    }
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log("\n");
#endif

#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Stop();
#endif
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimDoRamps_TestCase2
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that ramps are calculated by increments and decrements. Check for overflow protection.
///                     Use different values for increments and decrements.
///                     Increment with value 1: 0, 1, 2, 3, 4, ..., 100 (and not beyond)
///                     Decrement with value 2: 98, 96, 94, 92, 90, ..., 0 (and not below)
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input   AnimMaRamp_aucPxlIntTgt[0]  = 100u;
/// \input   AnimMaRamp_aucPxlIntInc[0]  = 0u;
/// \input   AnimMaRamp_aucPxlIntDec[0]  = 0u;
/// \input   Anima_TgtAniArr.unTgtAni[0] = 50000u;
///
///   - Expectations:
///
/// \output  Anima_TgtAniArr.unTgtAni[0] = aunExpInc[i]
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimDoRamps_TestCase2(void)
{
    int i;
    static const uint16 aunExp[3] = { 32768, 0, 0, };
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Start(" Mt_CtrlLed_DoRamps_TestCase2.txt");
#endif
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    AnimMaRamp_aucPxlIntTgt[0]  = 100u;
    AnimMaRamp_aucPxlIntInc[0]  = 0u;
    AnimMaRamp_aucPxlIntDec[0]  = 0u;
    Anima_TgtAniArr.unTgtAni[0] = 50000u;

    for (i = 0; i < 3; i++)
    {
        //Step 3) Call FUT
        Anima_DoRamps();
#if CFG_ENABLE_LOGGING == 1
        Mt_CtrlLed_Log("%d, ", Anima_TgtAniArr.unTgtAni[i]);
#endif
        //Step 4) Check expected output values
        AL_UNITTEST_CHECK(Anima_TgtAniArr.unTgtAni[i], aunExp[i], == );
    }
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log("\n");
#endif

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimDoRamps
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check start sequence
///
/// \Expected test results : All test cases contained are passed
///
//----------------------------------------------------------------------------
void Mt_CtrlLed_AnimDoRamps(void)
{
    Mt_CtrlLed_AnimDoRamps_TestCase1();
    Mt_CtrlLed_AnimDoRamps_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_InterpolateDim 
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check if the interpolation routine is working properly.
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input       aunTimes1[ANIMMA_DIMBLOCK_POINT_NUMBER]       = { T2P(0), T2P(100), T2P(200), T2P(300) };
/// \input       aunIntensities1[ANIMMA_DIMBLOCK_POINT_NUMBER] = { 0 ,     100 ,       0 ,     100 };
/// \input       aunTime1[] = { 0, 50, 100, 150, 200, 250, 300, 350, 400 };
/// \input       aucExpected1[] = { 0, 50, 100,  50,   0,  50, 100, 100, 100 };
/// \input       aunTimes2[ANIMMA_DIMBLOCK_POINT_NUMBER] = { T2P(50), T2P(100), T2P(200), T2P(300) };
/// \input       aunIntensities2[ANIMMA_DIMBLOCK_POINT_NUMBER] = { 0 ,     100 ,       0 ,     100 };
/// \input       aunTime2[] = { 0, 50, 100, 150, 200, 250, 300, 350, 400 };
/// \input       aucExpected2[] = { 0,  0, 100,  50,   0,  50, 100, 100, 100 };
///
///   - Expectations:
///
/// \output  ucRet = aucExpected1[i]
/// \output  ucRet = aucExpected2[i]
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_InterpolateDim(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values

    uint16 aunTimes1[ANIMMA_DIMBLOCK_POINT_NUMBER] = { T2P(0), T2P(100), T2P(200), T2P(300) };
    uint16 aunIntensities1[ANIMMA_DIMBLOCK_POINT_NUMBER] = { 0 ,     100 ,       0 ,     100 };
    uint32 aunTime1[] = { 0, 50, 100, 150, 200, 250, 300, 350, 400 };
    uint8  aucExpected1[] = { 0, 50, 100,  50,   0,  50, 100, 100, 100 };

    uint16 aunTimes2[ANIMMA_DIMBLOCK_POINT_NUMBER] = { T2P(50), T2P(100), T2P(200), T2P(300) };
    uint16 aunIntensities2[ANIMMA_DIMBLOCK_POINT_NUMBER] = { 0 ,     100 ,       0 ,     100 };
    uint32 aunTime2[] = { 0, 50, 100, 150, 200, 250, 300, 350, 400 };
    uint8  aucExpected2[] = { 0,  0, 100,  50,   0,  50, 100, 100, 100 };

    uint8 ucRet;
    uint32 i;

    for (i = 0; i < sizeof(aunTime1) / sizeof(uint32); i++)
    {
        //Step 3) Call FUT
        ucRet = interpolateDim(&aunTimes1[0], &aunIntensities1[0], aunTime1[i]);
        //Step 4) Check expected output values
        AL_UNITTEST_CHECK(ucRet, aucExpected1[i], == );
    }

    for (i = 0; i < sizeof(aunTime2) / sizeof(uint32); i++)
    {
        //Step 3) Call FUT
        ucRet = interpolateDim(&aunTimes2[0], &aunIntensities2[0], aunTime2[i]);
        //Step 4) Check expected output values
        AL_UNITTEST_CHECK(ucRet, aucExpected2[i], == );
    }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_GetPxlNr
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Chck the correct acquisition of pixel number(103)
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input      returnvalue = 0U;
///
///   - Expectations:
///
/// \output    returnvalue =  ANIMMA_NR_PIXELS
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_GetPxlNr()
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    uint8 returnvalue = 0U;

    //Step 3) Call FUT
    returnvalue = AnimMa_GetPxlNr();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(returnvalue, ANIMMA_NR_PIXELS, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_getMountSideLeft
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Chck the correct mounting side to left
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input      AnimMa_ucMountingSide = ANIMMA_MOUNTINGSIDE_LEFT;
///
///   - Expectations:
///
/// \output     ret = ANIMMA_MOUNTINGSIDE_LEFT
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_getMountSideLeft()
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    AnimMa_ucMountingSide = ANIMMA_MOUNTINGSIDE_LEFT;

    //Step 3) Call FUT
    uint8 ret = AnimMa_getMountSide();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(ret, ANIMMA_MOUNTINGSIDE_LEFT, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_getMountSideRight
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Chck the correct mounting side to right
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input      AnimMa_ucMountingSide = ANIMMA_MOUNTINGSIDE_RIGHT;
///
///   - Expectations:
///
/// \output     ret = ANIMMA_MOUNTINGSIDE_RIGHT
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_getMountSideRight()
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    AnimMa_ucMountingSide = ANIMMA_MOUNTINGSIDE_RIGHT;

    //Step 3) Call FUT
    uint8 ret = AnimMa_getMountSide();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(ret, ANIMMA_MOUNTINGSIDE_RIGHT, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_getMountSideUnknown
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Chck the unknown mounting side
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input      AnimMa_ucMountingSide = ANIMMA_MOUNTINGSIDE_UNKNOWN;
///
///   - Expectations:
///
/// \output     ret = ANIMMA_MOUNTINGSIDE_UNKNOWN
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_getMountSideUnknown()
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    AnimMa_ucMountingSide = ANIMMA_MOUNTINGSIDE_UNKNOWN;

    //Step 3) Call FUT
    uint8 ret = AnimMa_getMountSide();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(ret, ANIMMA_MOUNTINGSIDE_UNKNOWN, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Anima_Init_MountSideUnknown
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Test that animation request is not followed if mounting side is unknown
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input            Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedUndef;
/// \input            Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input            Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;
/// \input            Rte_Read_SysMon_TurnIndicatorCmd_Req_Param1                      = ReqLighted_On;
///
///   - Expectations:
///
/// \output           Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_NONE
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_Init_MountSideUnknown(void)
{
    //Step 1) Set pre-conditions,Assign Input values
    Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedUndef;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;
    Rte_Read_SysMon_TurnIndicatorCmd_Req_Param1                      = ReqLighted_On;

    //Step 2) Call FUT
    Anima_Init();

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_getMountSide
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check mounting side
///
/// \Expected test results : All test cases contained are passed
///
//----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_getMountSide(void)
{
    Mt_CtrlLed_AnimMa_getMountSideLeft();
    Mt_CtrlLed_AnimMa_getMountSideLeft();
    Mt_CtrlLed_AnimMa_getMountSideUnknown();
    Mt_CtrlLed_Anima_Init_MountSideUnknown();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_AllocateBlockContext_RUNN
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that RUNN block is allocated correctly when 
///                     the number of allocated blocks is not exceeded
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input      uint32 returnvalue                = ANIMMA_INVALID_BLOCK_IDX;
/// \input      AnimMa_AllocateBlockContext_Param = RUNN;
/// \input      AnimMa_unActiveBlocksRunNCnt      = 2u;
///
///   - Expectations:
///
/// \output     returnvalue = 2u;
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_AllocateBlockContext_RUNN()
{
    //Step 1) Set pre-conditions
   //Step 2) Assign Input values
    uint32 returnvalue                = ANIMMA_INVALID_BLOCK_IDX;
    //Do not exceed nr of allocated blocks
    AnimMa_AllocateBlockContext_Param = RUNN;
    AnimMa_unActiveBlocksRunNCnt      = 2u;

    //Step 3) Call FUT
    returnvalue = AnimMa_AllocateBlockContext(AnimMa_AllocateBlockContext_Param);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(returnvalue, 2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_AllocateBlockContext_RUNN_Exceed
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that RUNN block is allocated correctly when 
///                     the number of allocated blocks is  exceeded
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input      uint32 returnvalue                = ANIMMA_INVALID_BLOCK_IDX;
/// \input      AnimMa_AllocateBlockContext_Param = RUNN;
/// \input      AnimMa_unActiveBlocksRunNCnt      = 25u;
///
///   - Expectations:
///
/// \output     returnvalue = ANIMMA_INVALID_BLOCK_IDX;
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_AllocateBlockContext_RUNN_Exceed()
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    uint32 returnvalue                = ANIMMA_INVALID_BLOCK_IDX;
    //Runn exceed nr of allocated blocks
    AnimMa_AllocateBlockContext_Param = RUNN;
    AnimMa_unActiveBlocksRunNCnt      = 25u;

    //Step 3) Call FUT
    returnvalue = AnimMa_AllocateBlockContext(AnimMa_AllocateBlockContext_Param);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(returnvalue, ANIMMA_INVALID_BLOCK_IDX, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_AllocateBlockContext_RUN10
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that RUN block is allocated correctly when 
///                     the number of allocated blocks is not exceeded
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input              uint32 returnvalue            = ANIMMA_INVALID_BLOCK_IDX;
/// \input          AnimMa_AllocateBlockContext_Param = RUN10;
/// \input          AnimMa_unActiveBlocksRun10Cnt     = 2u;
///
///   - Expectations:
///
/// \output     returnvalue = 2u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_AllocateBlockContext_RUN10()
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    uint32 returnvalue                = ANIMMA_INVALID_BLOCK_IDX;
    //Do not exceed nr of allocated blocks
    AnimMa_AllocateBlockContext_Param = RUN10;
    AnimMa_unActiveBlocksRun10Cnt     = 2u;

    //Step 3) Call FUT
    returnvalue = AnimMa_AllocateBlockContext(AnimMa_AllocateBlockContext_Param);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(returnvalue, 2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_AllocateBlockContext_RUN10_Exceed
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that RUN block is allocated correctly when 
///                     the number of allocated blocks is  exceeded
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input          uint32 returnvalue                = ANIMMA_INVALID_BLOCK_IDX;
/// \input          AnimMa_AllocateBlockContext_Param = RUN10;
/// \input          AnimMa_unActiveBlocksRun10Cnt     = ANIMMA_NR_BLOCKS_RUN10 + 10u;
///
///   - Expectations:
///
/// \output         returnvalue = ANIMMA_INVALID_BLOCK_IDX
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_AllocateBlockContext_RUN10_Exceed()
{
    //Step 1) Set pre-conditions
   //Step 2) Assign Input values
    uint32 returnvalue                = ANIMMA_INVALID_BLOCK_IDX;
    //Runn exceed nr of allocated blocks
    AnimMa_AllocateBlockContext_Param = RUN10;
    AnimMa_unActiveBlocksRun10Cnt     = ANIMMA_NR_BLOCKS_RUN10 + 10u;

    //Step 3) Call FUT
    returnvalue = AnimMa_AllocateBlockContext(AnimMa_AllocateBlockContext_Param);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(returnvalue, ANIMMA_INVALID_BLOCK_IDX, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_AllocateBlockContext_SPARKLE_LFSR
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that SPARKLE_LFSR block is allocated correctly when 
///                     the number of allocated blocks is not exceeded
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input          uint32 returnvalue                  = ANIMMA_INVALID_BLOCK_IDX;
/// \input          AnimMa_AllocateBlockContext_Param   = SPARKLE_LFSR;
/// \input          AnimMa_unActiveBlocksSparkleLfsrCnt = 1u;
///
///   - Expectations:
///
/// \output         returnvalue= 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_AllocateBlockContext_SPARKLE_LFSR()
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    uint32 returnvalue                  = ANIMMA_INVALID_BLOCK_IDX;
    //Do not exceed nr of allocated blocks
    AnimMa_AllocateBlockContext_Param   = SPARKLE_LFSR;
    AnimMa_unActiveBlocksSparkleLfsrCnt = 1u;

    //Step 3) Call FUT
    returnvalue = AnimMa_AllocateBlockContext(AnimMa_AllocateBlockContext_Param);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(returnvalue, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_AllocateBlockContext_SPARKLE_LFSR_Exceed
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that SPARKLE_LFSR block is allocated correctly when 
///                     the number of allocated blocks is  exceeded
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input          uint32 returnvalue                  = ANIMMA_INVALID_BLOCK_IDX;
/// \input          AnimMa_AllocateBlockContext_Param   = SPARKLE_LFSR;
/// \input          AnimMa_unActiveBlocksSparkleLfsrCnt =  ANIMMA_NR_BLOCKS_SPARKLE_LFSR + 10u
///
///   - Expectations:
///
/// \output        returnvalue= ANIMMA_INVALID_BLOCK_IDX
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_AllocateBlockContext_SPARKLE_LFSR_Exceed()
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    uint32 returnvalue                  = ANIMMA_INVALID_BLOCK_IDX;
    //Runn exceed nr of allocated blocks
    AnimMa_AllocateBlockContext_Param   = SPARKLE_LFSR;
    AnimMa_unActiveBlocksSparkleLfsrCnt = ANIMMA_NR_BLOCKS_SPARKLE_LFSR + 10u;

    //Step 3) Call FUT
    returnvalue = AnimMa_AllocateBlockContext(AnimMa_AllocateBlockContext_Param);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(returnvalue, ANIMMA_INVALID_BLOCK_IDX, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_AllocateBlockContext_SPARKLE_XOR64
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that SPARKLE_XOR64 block is allocated correctly when 
///                     the number of allocated blocks is not exceeded
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input          uint32 returnvalue                   = ANIMMA_INVALID_BLOCK_IDX;
/// \input          AnimMa_AllocateBlockContext_Param    = SPARKLE_XOR64;
/// \input          AnimMa_unActiveBlocksSparkleXor64Cnt = 5u;
///
///   - Expectations:
///
/// \output         returnvalue =5u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_AllocateBlockContext_SPARKLE_XOR64()
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    uint32 returnvalue                   = ANIMMA_INVALID_BLOCK_IDX;
    //Do not exceed nr of allocated blocks
    AnimMa_AllocateBlockContext_Param    = SPARKLE_XOR64;
    AnimMa_unActiveBlocksSparkleXor64Cnt = 5u;

    //Step 3) Call FUT
    returnvalue = AnimMa_AllocateBlockContext(AnimMa_AllocateBlockContext_Param);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(returnvalue, 5u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_AllocateBlockContext_SPARKLE_XOR64_Exceed
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that SPARKLE_XOR64 block is allocated correctly when 
///                     the number of allocated blocks is  exceeded
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input          uint32 returnvalue                   = ANIMMA_INVALID_BLOCK_IDX;
/// \input          AnimMa_AllocateBlockContext_Param    = SPARKLE_XOR64;
/// \input          AnimMa_unActiveBlocksSparkleXor64Cnt = ANIMMA_NR_BLOCKS_SPARKLE_XOR64 + 10u;
///
///   - Expectations:
///
/// \output         returnvalue =ANIMMA_INVALID_BLOCK_IDX
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_AllocateBlockContext_SPARKLE_XOR64_Exceed()
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    uint32 returnvalue                   = ANIMMA_INVALID_BLOCK_IDX;
    //Runn exceed nr of allocated blocks
    AnimMa_AllocateBlockContext_Param    = SPARKLE_XOR64;
    AnimMa_unActiveBlocksSparkleXor64Cnt = ANIMMA_NR_BLOCKS_SPARKLE_XOR64 + 10u;

    //Step 3) Call FUT
    returnvalue = AnimMa_AllocateBlockContext(AnimMa_AllocateBlockContext_Param);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(returnvalue, ANIMMA_INVALID_BLOCK_IDX, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_AllocateBlockContext_CLAMP
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that CLAMP block is allocated correctly 
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input          uint32 returnvalue                = ANIMMA_INVALID_BLOCK_IDX;
/// \input          AnimMa_AllocateBlockContext_Param = CLAMP;
/// \input          AnimMa_unActiveBlocksClampCnt     = 7u;
///
///   - Expectations:
///
/// \output         returnvalue = 7u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_AllocateBlockContext_CLAMP()
{
    //Step 1) Set pre-conditions,Assign Input values
    uint32 returnvalue                = ANIMMA_INVALID_BLOCK_IDX;
    //Do not exceed nr of allocated blocks
    AnimMa_AllocateBlockContext_Param = CLAMP;
    AnimMa_unActiveBlocksClampCnt     = 7u;

    //Step 2) Call FUT
    returnvalue = AnimMa_AllocateBlockContext(AnimMa_AllocateBlockContext_Param);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(returnvalue, 7u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_AllocateBlockContext_INVERT
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that INVERT block is allocated correctly 
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input          uint32 returnvalue                = ANIMMA_INVALID_BLOCK_IDX;
/// \input          AnimMa_AllocateBlockContext_Param = INVERT;
/// \input          AnimMa_unActiveBlocksInvertCnt    = 7u;
///
///   - Expectations:
///
/// \output         returnvalue = 7u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_AllocateBlockContext_INVERT()
{
    //Step 1) Set pre-conditions,Assign Input values
    uint32 returnvalue                = ANIMMA_INVALID_BLOCK_IDX;
    //Do not exceed nr of allocated blocks
    AnimMa_AllocateBlockContext_Param = INVERT;
    AnimMa_unActiveBlocksInvertCnt    = 7u;

    //Step 2) Call FUT
    returnvalue = AnimMa_AllocateBlockContext(AnimMa_AllocateBlockContext_Param);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(returnvalue, 7u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_AllocateBlockContext_BLINK
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that BLINK block is allocated correctly when 
///                     the number of allocated blocks is not exceeded
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input          uint32 returnvalue                = ANIMMA_INVALID_BLOCK_IDX;
/// \input          AnimMa_AllocateBlockContext_Param = BLINK
/// \input          AnimMa_unActiveBlocksBlinkCnt     = 7u;
///
///   - Expectations:
///
/// \output         returnvalue = 7u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_AllocateBlockContext_BLINK()
{
    //Step 1) Set pre-conditions,Assign Input values
    uint32 returnvalue                = ANIMMA_INVALID_BLOCK_IDX;
    //Do not exceed nr of allocated blocks
    AnimMa_AllocateBlockContext_Param = BLINK;
    AnimMa_unActiveBlocksBlinkCnt     = 7u;

    //Step 2) Call FUT
    returnvalue = AnimMa_AllocateBlockContext(AnimMa_AllocateBlockContext_Param);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(returnvalue, 7u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_AllocateBlockContext_BLINK_Exceed
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that BLINK block is allocated correctly when 
///                     the number of allocated blocks is  exceeded
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input          uint32 returnvalue                = ANIMMA_INVALID_BLOCK_IDX;
/// \input          AnimMa_AllocateBlockContext_Param = BLINK
/// \input          AnimMa_unActiveBlocksBlinkCnt     = ANIMMA_NR_BLOCKS_BLINK + 10u;
///
///   - Expectations:
///
/// \output         returnvalue = ANIMMA_INVALID_BLOCK_IDX
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_AllocateBlockContext_BLINK_Exceed()
{
    //Step 1) Set pre-conditions,Assign Input values
    uint32 returnvalue                = ANIMMA_INVALID_BLOCK_IDX;
    //Do not exceed nr of allocated blocks
    AnimMa_AllocateBlockContext_Param = BLINK;
    AnimMa_unActiveBlocksBlinkCnt     = ANIMMA_NR_BLOCKS_BLINK + 10u;

    //Step 2) Call FUT
    returnvalue = AnimMa_AllocateBlockContext(AnimMa_AllocateBlockContext_Param);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(returnvalue, ANIMMA_INVALID_BLOCK_IDX, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_AllocateBlockContext_FLEX
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that FLEX block is allocated correctly when 
///                     the number of allocated blocks is not exceeded
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input          uint32 returnvalue                = ANIMMA_INVALID_BLOCK_IDX;
/// \input          AnimMa_AllocateBlockContext_Param = FLEX
/// \input          AnimMa_unActiveBlocksFlexCnt      = 7u;
///
///   - Expectations:
///
/// \output         returnvalue = 7u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_AllocateBlockContext_FLEX()
{
    //Step 1) Set pre-conditions,Assign Input values
    uint32 returnvalue                = ANIMMA_INVALID_BLOCK_IDX;
    //Do not exceed nr of allocated blocks
    AnimMa_AllocateBlockContext_Param = FLEX;
    AnimMa_unActiveBlocksFlexCnt      = 7u;

    //Step 2) Call FUT
    returnvalue = AnimMa_AllocateBlockContext(AnimMa_AllocateBlockContext_Param);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(returnvalue, 7u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_AllocateBlockContext_FLEX_Exceed
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that FLEX block is allocated correctly when 
///                     the number of allocated blocks is  exceeded
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input          uint32 returnvalue                = ANIMMA_INVALID_BLOCK_IDX;
/// \input          AnimMa_AllocateBlockContext_Param = FLEX
/// \input          AnimMa_unActiveBlocksFlexCnt      = ANIMMA_NR_BLOCKS_FLEX + 10u
///
///   - Expectations:
///
/// \output        returnvalue = ANIMMA_INVALID_BLOCK_IDX
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_AllocateBlockContext_FLEX_Exceed()
{
    //Step 1) Set pre-conditions,Assign Input values
    uint32 returnvalue                = ANIMMA_INVALID_BLOCK_IDX;
    //Do not exceed nr of allocated blocks
    AnimMa_AllocateBlockContext_Param = FLEX;
    AnimMa_unActiveBlocksFlexCnt      = ANIMMA_NR_BLOCKS_FLEX + 10u;

    //Step 2) Call FUT
    returnvalue = AnimMa_AllocateBlockContext(AnimMa_AllocateBlockContext_Param);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(returnvalue, ANIMMA_INVALID_BLOCK_IDX, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_AllocateBlockContext_SPEEDASSIGN
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that SPEEDASSIGN block is allocated correctly
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input         uint32 returnvalue                  = ANIMMA_INVALID_BLOCK_IDX;
/// \input         AnimMa_AllocateBlockContext_Param   = SPEEDASSIGN
/// \input         AnimMa_unActiveBlocksSpeedAssignCnt = 7u;
///
///   - Expectations:
///
/// \output        returnvalue = 7u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_AllocateBlockContext_SPEEDASSIGN()
{
    //Step 1) Set pre-conditions,Assign Input values
    uint32 returnvalue                  = ANIMMA_INVALID_BLOCK_IDX;
    //Do not exceed nr of allocated blocks
    AnimMa_AllocateBlockContext_Param   = SPEEDASSIGN;
    AnimMa_unActiveBlocksSpeedAssignCnt = 7u;

    //Step 2) Call FUT
    returnvalue = AnimMa_AllocateBlockContext(AnimMa_AllocateBlockContext_Param);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(returnvalue, 7u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_AllocateBlockContext_PIECEWISELINEAR
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that PIECEWISELINEAR block is allocated correctly when 
///                     the number of allocated blocks is not exceeded
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input          Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input          Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeNight;
/// \input          Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input          uint32 returnvalue                                               = ANIMMA_INVALID_BLOCK_IDX;
/// \input          AnimMa_BlockContext_BkType                                       = PIECEWISELINEAR;
/// \input          AnimMa_unActiveBlocksPiecewiseLinearCnt                          = 7u;
///
///   - Expectations:
///
/// \output        returnvalue = 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_AllocateBlockContext_PIECEWISELINEAR()
{
    int i;
    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaC;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(AnimMa_CodPrj_aucDataset8_Picewise) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = AnimMa_CodPrj_aucDataset8_Picewise[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
    Mt_CtrlLed_PreTest();

    //Step 1) Set pre-conditions,Assign Input values
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeNight;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;

    uint32 returnvalue                                               = ANIMMA_INVALID_BLOCK_IDX;
    AnimMa_BlockContext_BkType                                       = PIECEWISELINEAR;
    AnimMa_unActiveBlocksPiecewiseLinearCnt                          = 7u;

    //Step 2) Call FUT
    returnvalue = AnimMa_AllocateBlockContext(AnimMa_BlockContext_BkType);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(returnvalue, 7u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_AllocateBlockContext_PIECEWISELINEAR_Exceed
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that PIECEWISELINEAR block is allocated correctly when 
///                     the number of allocated blocks is  exceeded
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input         uint32 returnvalue                       = ANIMMA_INVALID_BLOCK_IDX;
/// \input          AnimMa_BlockContext_BkType              = PIECEWISELINEAR;
/// \input          AnimMa_unActiveBlocksPiecewiseLinearCnt = ANIMMA_NR_BLOCKS_BLINK + 10u;
///
///   - Expectations:
///
/// \output        returnvalue = 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_AllocateBlockContext_PIECEWISELINEAR_Exceed()
{
    uint32 returnvalue                     = ANIMMA_INVALID_BLOCK_IDX;
    //Do not exceed nr of allocated blocks
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_BlockContext_BkType              = PIECEWISELINEAR;
    AnimMa_unActiveBlocksPiecewiseLinearCnt = ANIMMA_NR_BLOCKS_BLINK + 10u;
    //Step 2) Call FUT
    returnvalue = AnimMa_AllocateBlockContext(AnimMa_BlockContext_BkType);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(returnvalue, ANIMMA_INVALID_BLOCK_IDX, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_AllocateBlockContext_INVERTINTENSITY
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that INVERTINTENSITY block is allocated correctly
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input          uint32 returnvalue                      = ANIMMA_INVALID_BLOCK_IDX;
/// \input          AnimMa_BlockContext_BkType              = INVERTINTENSITY;
/// \input          AnimMa_unActiveBlocksInvertIntensityCnt = 7u;
///
///   - Expectations:
///
/// \output        returnvalue = 7u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_AllocateBlockContext_INVERTINTENSITY()
{
    uint32 returnvalue                     = ANIMMA_INVALID_BLOCK_IDX;
    //Do not exceed nr of allocated blocks
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_BlockContext_BkType              = INVERTINTENSITY;
    AnimMa_unActiveBlocksInvertIntensityCnt = 7u;

    //Step 2) Call FUT
    returnvalue = AnimMa_AllocateBlockContext(AnimMa_BlockContext_BkType);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(returnvalue, 7u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_AllocateBlockContext_TIMEOFFSET
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that TIMEOFFSET block is allocated correctly 
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input          uint32 returnvalue                 = ANIMMA_INVALID_BLOCK_IDX;
/// \input          AnimMa_BlockContext_BkType         = TIMEOFFSET;
/// \input          AnimMa_unActiveBlocksRepetitionCnt = 7u;
///
///   - Expectations:
///
/// \output        returnvalue = 7u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_AllocateBlockContext_TIMEOFFSET()
{
    uint32 returnvalue                 = ANIMMA_INVALID_BLOCK_IDX;
    //Do not exceed nr of allocated blocks
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_BlockContext_BkType         = TIMEOFFSET;
    AnimMa_unActiveBlocksRepetitionCnt = 7u;

    //Step 2) Call FUT
    returnvalue = AnimMa_AllocateBlockContext(AnimMa_BlockContext_BkType);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(returnvalue, 7u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_AllocateBlockContext_REPETITION
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that REPETITION block is allocated correctly
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input          uint32 returnvalue                 = ANIMMA_INVALID_BLOCK_IDX;
/// \input          AnimMa_BlockContext_BkType         = REPETITION;
/// \input          AnimMa_unActiveBlocksRepetitionCnt = 7u;
///
///   - Expectations:
///
/// \output        returnvalue = 7u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_AllocateBlockContext_REPETITION()
{
    uint32 returnvalue                 = ANIMMA_INVALID_BLOCK_IDX;
    //Do not exceed nr of allocated blocks
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_BlockContext_BkType         = REPETITION;
    AnimMa_unActiveBlocksRepetitionCnt = 7u;

    //Step 2) Call FUT
    returnvalue = AnimMa_AllocateBlockContext(AnimMa_BlockContext_BkType);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(returnvalue, 7u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_AllocateBlockContext_Default
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that DEFAULT block is allocated correctly
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input          uint32 returnvalue         = ANIMMA_INVALID_BLOCK_IDX;
/// \input          AnimMa_BlockContext_BkType = 18u;
///
///   - Expectations:
///
/// \output        returnvalue = ANIMMA_INVALID_BLOCK_IDX
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_AllocateBlockContext_Default()
{
    uint32 returnvalue        = ANIMMA_INVALID_BLOCK_IDX;
    //Do not exceed nr of allocated blocks
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_BlockContext_BkType = 18u;

    //Step 2) Call FUT
    returnvalue = AnimMa_AllocateBlockContext(AnimMa_BlockContext_BkType);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(returnvalue, ANIMMA_INVALID_BLOCK_IDX, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_AnimMa_AllocateBlockContext
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  check the set event status value
///
/// \Expected test results : All test cases contained are passed
///
//----------------------------------------------------------------------------
void Mt_AnimMa_AllocateBlockContext(void)
{
    Mt_CtrlLed_AnimMa_AllocateBlockContext_RUNN();
    Mt_CtrlLed_AnimMa_AllocateBlockContext_RUNN_Exceed();
    Mt_CtrlLed_AnimMa_AllocateBlockContext_RUN10();
    Mt_CtrlLed_AnimMa_AllocateBlockContext_RUN10_Exceed();
    Mt_CtrlLed_AnimMa_AllocateBlockContext_SPARKLE_LFSR();
    Mt_CtrlLed_AnimMa_AllocateBlockContext_SPARKLE_LFSR_Exceed();
    Mt_CtrlLed_AnimMa_AllocateBlockContext_SPARKLE_XOR64();
    Mt_CtrlLed_AnimMa_AllocateBlockContext_SPARKLE_XOR64_Exceed();
    Mt_CtrlLed_AnimMa_AllocateBlockContext_CLAMP();
    Mt_CtrlLed_AnimMa_AllocateBlockContext_INVERT();
    Mt_CtrlLed_AnimMa_AllocateBlockContext_BLINK();
    Mt_CtrlLed_AnimMa_AllocateBlockContext_BLINK_Exceed();
    Mt_CtrlLed_AnimMa_AllocateBlockContext_FLEX();
    Mt_CtrlLed_AnimMa_AllocateBlockContext_FLEX_Exceed();
    Mt_CtrlLed_AnimMa_AllocateBlockContext_SPEEDASSIGN();
    Mt_CtrlLed_AnimMa_AllocateBlockContext_PIECEWISELINEAR();
    Mt_CtrlLed_AnimMa_AllocateBlockContext_PIECEWISELINEAR_Exceed();
    Mt_CtrlLed_AnimMa_AllocateBlockContext_INVERTINTENSITY();
    Mt_CtrlLed_AnimMa_AllocateBlockContext_TIMEOFFSET();
    Mt_CtrlLed_AnimMa_AllocateBlockContext_REPETITION();
    Mt_CtrlLed_AnimMa_AllocateBlockContext_Default();
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_DeleteBlockContext_RUN10
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that RUN10 block is deleted correctly when 
///                     the number of allocated blocks is not exceeded
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input          AnimMa_DeleteBlockContext_BlkIdx  = 2u;
/// \input          AnimMa_BlockContext_BkType        = RUN10;
/// \input          AnimMa_unActiveBlocksRun10Cnt     = 5u;
/// \input          AnimMa_unDeactivateBlocksRun10Cnt = 2u;
///
///   - Expectations:
///
/// \output        AnimMa_unActiveBlocksRun10Cnt     = 4u
/// \output        AnimMa_unDeactivateBlocksRun10Cnt = 3u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_DeleteBlockContext_RUN10()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_DeleteBlockContext_BlkIdx  = 2u;
    AnimMa_BlockContext_BkType        = RUN10;
    AnimMa_unActiveBlocksRun10Cnt     = 5u;
    AnimMa_unDeactivateBlocksRun10Cnt = 2u;

    //Step 2) Call FUT
    AnimMa_DeleteBlockContext(AnimMa_DeleteBlockContext_BlkIdx, AnimMa_BlockContext_BkType);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_unActiveBlocksRun10Cnt,     4u, == );
    AL_UNITTEST_CHECK(AnimMa_unDeactivateBlocksRun10Cnt, 3u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_DeleteBlockContext_RUN10_Exceed
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that RUN10 block is deleted correctly when 
///                     the number of allocated blocks is  exceeded
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input          AnimMa_unActiveBlocksRun10Cnt     = 3u;
/// \input          AnimMa_unDeactivateBlocksRun10Cnt = 4u;
/// \input          AnimMa_DeleteBlockContext_BlkIdx  = 5u;
/// \input          AnimMa_BlockContext_BkType        = RUN10;
///
///   - Expectations:
///
/// \output        AnimMa_unActiveBlocksRun10Cnt     = 3u
/// \output        AnimMa_unDeactivateBlocksRun10Cnt = 4u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_DeleteBlockContext_RUN10_Exceed()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_unActiveBlocksRun10Cnt     = 3u;
    AnimMa_unDeactivateBlocksRun10Cnt = 4u;
    AnimMa_DeleteBlockContext_BlkIdx  = 5u;
    AnimMa_BlockContext_BkType        = RUN10;

    //Step 2) Call FUT
    AnimMa_DeleteBlockContext(AnimMa_DeleteBlockContext_BlkIdx, AnimMa_BlockContext_BkType);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_unActiveBlocksRun10Cnt,    3u, == );
    AL_UNITTEST_CHECK(AnimMa_unDeactivateBlocksRun10Cnt, 4u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_DeleteBlocks
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that blocks are deleted correctly after execution
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input          Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input          Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeNight;
/// \input          Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input          AnimMa_unActiveBlocksCnt                                         = 10u;
/// \input          AnimMa_DeleteBlocks_Param1                                       = 0u;
/// \input          AnimMa_DeleteBlocks_Param2                                       =0u;
///
///   - Expectations:
///
/// \output        Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_NONE
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_DeleteBlocks()
{
    int i;
    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaC;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(AnimMa_CodPrj_aucDeleteBlocks) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = AnimMa_CodPrj_aucDeleteBlocks[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
    Mt_CtrlLed_PreTest();

    //Step 1) Set pre-conditions,Assign Input values
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeNight;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    uint32 AnimMa_DeleteBlocks_Param1;
    uint32 AnimMa_DeleteBlocks_Param2;
    AnimMa_unActiveBlocksCnt                                         = 10u;
    AnimMa_DeleteBlocks_Param1                                       = 0u;
    AnimMa_DeleteBlocks_Param2                                       = 0u;

    //Step 2) Call FUT
    AnimMa_DeleteBlocks(AnimMa_DeleteBlocks_Param1, AnimMa_DeleteBlocks_Param2);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_DeleteBlockContext_RUNN
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that RUNN block is deleted correctly when 
///                     the number of allocated blocks is not exceeded
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input          AnimMa_DeleteBlockContext_BlkIdx = 2u;
/// \input          AnimMa_BlockContext_BkType       = RUNN;
/// \input          AnimMa_unActiveBlocksRunNCnt     = 5u;
/// \input          AnimMa_unDeactivateBlocksRunNCnt = 2u;
///
///   - Expectations:
///
/// \output        AnimMa_unActiveBlocksRunNCnt     = 4u
/// \output        AnimMa_unDeactivateBlocksRunNCnt = 3u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_DeleteBlockContext_RUNN()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_DeleteBlockContext_BlkIdx = 2u;
    AnimMa_BlockContext_BkType       = RUNN;
    AnimMa_unActiveBlocksRunNCnt     = 5u;
    AnimMa_unDeactivateBlocksRunNCnt = 2u;
    //Step 2) Call FUT

    AnimMa_DeleteBlockContext(AnimMa_DeleteBlockContext_BlkIdx, AnimMa_BlockContext_BkType);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_unActiveBlocksRunNCnt,     4u, == );
    AL_UNITTEST_CHECK(AnimMa_unDeactivateBlocksRunNCnt, 3u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_DeleteBlockContext_RUNN_Exceed
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that RUNN block is deleted correctly when 
///                     the number of allocated blocks is  exceeded
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input          AnimMa_unActiveBlocksRunNCnt     = 3u;
/// \input          AnimMa_unDeactivateBlocksRunNCnt = 4u;
/// \input          AnimMa_DeleteBlockContext_BlkIdx = 5u;
/// \input          AnimMa_BlockContext_BkType       = RUNN;
///
///   - Expectations:
///
/// \output        AnimMa_unActiveBlocksRunNCnt     = 3u
/// \output        AnimMa_unDeactivateBlocksRunNCnt = 4u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_DeleteBlockContext_RUNN_Exceed()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_unActiveBlocksRunNCnt     = 3u;
    AnimMa_unDeactivateBlocksRunNCnt = 4u;
    AnimMa_DeleteBlockContext_BlkIdx = 5u;
    AnimMa_BlockContext_BkType       = RUNN;

    //Step 2) Call FUT
    AnimMa_DeleteBlockContext(AnimMa_DeleteBlockContext_BlkIdx, AnimMa_BlockContext_BkType);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_unActiveBlocksRunNCnt,     3u, == );
    AL_UNITTEST_CHECK(AnimMa_unDeactivateBlocksRunNCnt, 4u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_DeleteBlockContext_SPARKLE_LFSR
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that SPARKLE_LFSR block is deleted correctly when 
///                     the number of allocated blocks is not exceeded
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           AnimMa_DeleteBlockContext_BlkIdx        = 2u;
/// \input           AnimMa_BlockContext_BkType              = SPARKLE_LFSR;
/// \input           AnimMa_unActiveBlocksSparkleLfsrCnt     = 5u;
/// \input           AnimMa_unDeactivateBlocksSparkleLfsrCnt = 2u;
///
///   - Expectations:
///
/// \output          AnimMa_unActiveBlocksSparkleLfsrCnt     = 4u
/// \output          AnimMa_unDeactivateBlocksSparkleLfsrCnt = 3u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_DeleteBlockContext_SPARKLE_LFSR()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_DeleteBlockContext_BlkIdx        = 2u;
    AnimMa_BlockContext_BkType              = SPARKLE_LFSR;
    AnimMa_unActiveBlocksSparkleLfsrCnt     = 5u;
    AnimMa_unDeactivateBlocksSparkleLfsrCnt = 2u;

    //Step 2) Call FUT
    AnimMa_DeleteBlockContext(AnimMa_DeleteBlockContext_BlkIdx, AnimMa_BlockContext_BkType);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_unActiveBlocksSparkleLfsrCnt,     4u, == );
    AL_UNITTEST_CHECK(AnimMa_unDeactivateBlocksSparkleLfsrCnt, 3u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_DeleteBlockContext_SPARKLE_LFSR_Exceed
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that SPARKLE_LFSR block is deleted correctly when 
///                     the number of allocated blocks is  exceeded
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           AnimMa_unActiveBlocksSparkleLfsrCnt      = 3u;
/// \input           AnimMa_unDeactivateBlocksSparkleLfsrCnt = 4u;
/// \input           AnimMa_DeleteBlockContext_BlkIdx        = 5u;
/// \input           AnimMa_BlockContext_BkType              = SPARKLE_LFSR;
///
///   - Expectations:
///
/// \output          AnimMa_unActiveBlocksSparkleLfsrCnt     = 3u
/// \output          AnimMa_unDeactivateBlocksSparkleLfsrCnt = 4u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_DeleteBlockContext_SPARKLE_LFSR_Exceed()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_unActiveBlocksSparkleLfsrCnt     = 3u;
    AnimMa_unDeactivateBlocksSparkleLfsrCnt = 4u;
    AnimMa_DeleteBlockContext_BlkIdx        = 5u;
    AnimMa_BlockContext_BkType              = SPARKLE_LFSR;

    //Step 2) Call FUT
    AnimMa_DeleteBlockContext(AnimMa_DeleteBlockContext_BlkIdx, AnimMa_BlockContext_BkType);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_unActiveBlocksSparkleLfsrCnt,     3u, == );
    AL_UNITTEST_CHECK(AnimMa_unDeactivateBlocksSparkleLfsrCnt, 4u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_DeleteBlockContext_SPARKLE_XOR64
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that SPARKLE_XOR64 block is deleted correctly when 
///                     the number of allocated blocks is not exceeded
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           AnimMa_DeleteBlockContext_BlkIdx         = 2u;
/// \input           AnimMa_BlockContext_BkType               = SPARKLE_XOR64;
/// \input           AnimMa_unActiveBlocksSparkleXor64Cnt     = 5u;
/// \input           AnimMa_unDeactivateBlocksSparkleXor64Cnt = 2u;
///
///   - Expectations:
///
/// \output          AnimMa_unActiveBlocksSparkleXor64Cnt     = 4u
/// \output          AnimMa_unDeactivateBlocksSparkleXor64Cnt = 3u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_DeleteBlockContext_SPARKLE_XOR64()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_DeleteBlockContext_BlkIdx         = 2u;
    AnimMa_BlockContext_BkType               = SPARKLE_XOR64;
    AnimMa_unActiveBlocksSparkleXor64Cnt     = 5u;
    AnimMa_unDeactivateBlocksSparkleXor64Cnt = 2u;

    //Step 2) Call FUT
    AnimMa_DeleteBlockContext(AnimMa_DeleteBlockContext_BlkIdx, AnimMa_BlockContext_BkType);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_unActiveBlocksSparkleXor64Cnt,     4u, == );
    AL_UNITTEST_CHECK(AnimMa_unDeactivateBlocksSparkleXor64Cnt, 3u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_DeleteBlockContext_SPARKLE_XOR64_Exceed
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that SPARKLE_XOR64 block is deleted correctly when 
///                     the number of allocated blocks is  exceeded
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           AnimMa_unActiveBlocksSparkleXor64Cnt     = 3u;
/// \input           AnimMa_unDeactivateBlocksSparkleXor64Cnt = 4u;
/// \input           AnimMa_DeleteBlockContext_BlkIdx         = 5u;
/// \input           AnimMa_BlockContext_BkType               = SPARKLE_XOR64;
///
///   - Expectations:
///
/// \output         AnimMa_unActiveBlocksSparkleXor64Cnt     = 3u
/// \output         AnimMa_unDeactivateBlocksSparkleXor64Cnt = 4u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_DeleteBlockContext_SPARKLE_XOR64_Exceed()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_unActiveBlocksSparkleXor64Cnt     = 3u;
    AnimMa_unDeactivateBlocksSparkleXor64Cnt = 4u;
    AnimMa_DeleteBlockContext_BlkIdx         = 5u;
    AnimMa_BlockContext_BkType               = SPARKLE_XOR64;

    //Step 2) Call FUT
    AnimMa_DeleteBlockContext(AnimMa_DeleteBlockContext_BlkIdx, AnimMa_BlockContext_BkType);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_unActiveBlocksSparkleXor64Cnt,     3u, == );
    AL_UNITTEST_CHECK(AnimMa_unDeactivateBlocksSparkleXor64Cnt, 4u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_DeleteBlockContext_CLAMP
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that CLAMP block is deleted correctly when 
///                     the number of allocated blocks is not exceeded
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           AnimMa_DeleteBlockContext_BlkIdx  = 2u;
/// \input           AnimMa_BlockContext_BkType        = CLAMP;
/// \input           AnimMa_unActiveBlocksClampCnt     = 5u;
/// \input           AnimMa_unDeactivateBlocksClampCnt = 2u;
///
///   - Expectations:
///
/// \output         AnimMa_unActiveBlocksClampCnt     = 4u
/// \output         AnimMa_unDeactivateBlocksClampCnt = 3u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_DeleteBlockContext_CLAMP()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_DeleteBlockContext_BlkIdx  = 2u;
    AnimMa_BlockContext_BkType        = CLAMP;
    AnimMa_unActiveBlocksClampCnt     = 5u;
    AnimMa_unDeactivateBlocksClampCnt = 2u;

    //Step 2) Call FUT
    AnimMa_DeleteBlockContext(AnimMa_DeleteBlockContext_BlkIdx, AnimMa_BlockContext_BkType);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_unActiveBlocksClampCnt,     4u, == );
    AL_UNITTEST_CHECK(AnimMa_unDeactivateBlocksClampCnt, 3u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_DeleteBlockContext_CLAMP_Exceed
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that CLAMP block is deleted correctly when 
///                     the number of allocated blocks is not exceeded
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           AnimMa_unActiveBlocksClampCnt            = 3u;
/// \input           AnimMa_unDeactivateBlocksSparkleXor64Cnt = 4u;
/// \input           AnimMa_DeleteBlockContext_BlkIdx         = 5u;
/// \input           AnimMa_BlockContext_BkType               = CLAMP;
///
///   - Expectations:
///
/// \output         AnimMa_unActiveBlocksClampCnt            = 3u
/// \output         AnimMa_unDeactivateBlocksSparkleXor64Cnt = 4u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_DeleteBlockContext_CLAMP_Exceed()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_unActiveBlocksClampCnt     = 3u;
    AnimMa_unDeactivateBlocksClampCnt = 4u;
    AnimMa_DeleteBlockContext_BlkIdx  = 5u;
    AnimMa_BlockContext_BkType        = CLAMP;

    //Step 2) Call FUT
    AnimMa_DeleteBlockContext(AnimMa_DeleteBlockContext_BlkIdx, AnimMa_BlockContext_BkType);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_unActiveBlocksClampCnt,     3u, == );
    AL_UNITTEST_CHECK(AnimMa_unDeactivateBlocksClampCnt, 4u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_DeleteBlockContext_INVERT
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that INVERT block is deleted correctly
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           AnimMa_DeleteBlockContext_BlkIdx   = 2u;
/// \input           AnimMa_BlockContext_BkType         = INVERT;
/// \input           AnimMa_unActiveBlocksInvertCnt     = 5u;
/// \input           AnimMa_unDeactivateBlocksInvertCnt = 2u;
///
///   - Expectations:
///
/// \output         AnimMa_unActiveBlocksInvertCnt     = 4u
/// \output         AnimMa_unDeactivateBlocksInvertCnt = 3u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_DeleteBlockContext_INVERT()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_DeleteBlockContext_BlkIdx   = 2u;
    AnimMa_BlockContext_BkType         = INVERT;
    AnimMa_unActiveBlocksInvertCnt     = 5u;
    AnimMa_unDeactivateBlocksInvertCnt = 2u;

    //Step 2) Call FUT
    AnimMa_DeleteBlockContext(AnimMa_DeleteBlockContext_BlkIdx, AnimMa_BlockContext_BkType);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_unActiveBlocksInvertCnt,     4u, == );
    AL_UNITTEST_CHECK(AnimMa_unDeactivateBlocksInvertCnt, 3u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_DeleteBlockContext_BLINK
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that BLINK block is deleted correctly when 
///                     the number of allocated blocks is not exceeded
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           AnimMa_DeleteBlockContext_BlkIdx  = 2u;
/// \input           AnimMa_BlockContext_BkType        = BLINK;
/// \input           AnimMa_unActiveBlocksBlinkCnt     = 5u;
/// \input           AnimMa_unDeactivateBlocksBlinkCnt = 2u;
///
///   - Expectations:
///
/// \output         AnimMa_unActiveBlocksBlinkCnt     = 4u
/// \output         AnimMa_unDeactivateBlocksBlinkCnt = 3u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_DeleteBlockContext_BLINK()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_DeleteBlockContext_BlkIdx  = 2u;
    AnimMa_BlockContext_BkType        = BLINK;
    AnimMa_unActiveBlocksBlinkCnt     = 5u;
    AnimMa_unDeactivateBlocksBlinkCnt = 2u;

    //Step 2) Call FUT
    AnimMa_DeleteBlockContext(AnimMa_DeleteBlockContext_BlkIdx, AnimMa_BlockContext_BkType);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_unActiveBlocksBlinkCnt,     4u, == );
    AL_UNITTEST_CHECK(AnimMa_unDeactivateBlocksBlinkCnt, 3u, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_DeleteBlockContext_BLINK_Exceed
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that BLINK block is deleted correctly when 
///                     the number of allocated blocks is exceeded
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           AnimMa_unActiveBlocksBlinkCnt     = 3u;
/// \input           AnimMa_unDeactivateBlocksBlinkCnt = 4u;
/// \input           AnimMa_DeleteBlockContext_BlkIdx  = 5u;
/// \input           AnimMa_BlockContext_BkType        = BLINK;
///
///   - Expectations:
///
/// \output         AnimMa_unActiveBlocksBlinkCnt = 3u
/// \output         AnimMa_unDeactivateBlocksBlinkCnt = 4u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_DeleteBlockContext_BLINK_Exceed()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_unActiveBlocksBlinkCnt     = 3u;
    AnimMa_unDeactivateBlocksBlinkCnt = 4u;
    AnimMa_DeleteBlockContext_BlkIdx  = 5u;
    AnimMa_BlockContext_BkType        = BLINK;

    //Step 2) Call FUT
    AnimMa_DeleteBlockContext(AnimMa_DeleteBlockContext_BlkIdx, AnimMa_BlockContext_BkType);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_unActiveBlocksBlinkCnt,    3u, == );
    AL_UNITTEST_CHECK(AnimMa_unDeactivateBlocksBlinkCnt, 4u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_DeleteBlockContext_FLEX
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that FLEX block is deleted correctly when 
///                     the number of allocated blocks is not exceeded
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input            AnimMa_DeleteBlockContext_BlkIdx = 2u;
/// \input            AnimMa_BlockContext_BkType       = FLEX;
/// \input            AnimMa_unActiveBlocksFlexCnt     = 5u;
/// \input            AnimMa_unDeactivateBlocksFlexCnt = 2u;
///
///   - Expectations:
///
/// \output         AnimMa_unActiveBlocksFlexCnt     = 4u
/// \output         AnimMa_unDeactivateBlocksFlexCnt = 3u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_DeleteBlockContext_FLEX()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_DeleteBlockContext_BlkIdx = 2u;
    AnimMa_BlockContext_BkType       = FLEX;
    AnimMa_unActiveBlocksFlexCnt     = 5u;
    AnimMa_unDeactivateBlocksFlexCnt = 2u;

    //Step 2) Call FUT
    AnimMa_DeleteBlockContext(AnimMa_DeleteBlockContext_BlkIdx, AnimMa_BlockContext_BkType);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_unActiveBlocksFlexCnt,     4u, == );
    AL_UNITTEST_CHECK(AnimMa_unDeactivateBlocksFlexCnt, 3u, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_DeleteBlockContext_FLEX_Exceed
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that FLEX block is deleted correctly when 
///                     the number of allocated blocks is exceeded
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input            AnimMa_unActiveBlocksFlexCnt     = 3u;
/// \input            AnimMa_unDeactivateBlocksFlexCnt = 4u;
/// \input            AnimMa_DeleteBlockContext_BlkIdx = 5u;
/// \input            AnimMa_BlockContext_BkType       = FLEX;
///
///   - Expectations:
///
/// \output          AnimMa_unActiveBlocksFlexCnt = 3u
/// \output          AnimMa_unDeactivateBlocksFlexCnt = 4u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_DeleteBlockContext_FLEX_Exceed()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_unActiveBlocksFlexCnt     = 3u;
    AnimMa_unDeactivateBlocksFlexCnt = 4u;
    AnimMa_DeleteBlockContext_BlkIdx = 5u;
    AnimMa_BlockContext_BkType       = FLEX;

    //Step 2) Call FUT
    AnimMa_DeleteBlockContext(AnimMa_DeleteBlockContext_BlkIdx, AnimMa_BlockContext_BkType);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_unActiveBlocksFlexCnt,     3u, == );
    AL_UNITTEST_CHECK(AnimMa_unDeactivateBlocksFlexCnt, 4u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_DeleteBlockContext_SPEEDASSIGN
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that SPEEDASSIGN block is deleted correctly when 
///                     the number of allocated blocks is not exceeded
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           AnimMa_DeleteBlockContext_BlkIdx        = 2u;
/// \input           AnimMa_BlockContext_BkType              = SPEEDASSIGN;
/// \input           AnimMa_unActiveBlocksSpeedAssignCnt     = 5u;
/// \input           AnimMa_unDeactivateBlocksSpeedAssignCnt = 2u;
///
///   - Expectations:
///
/// \output         AnimMa_unActiveBlocksSpeedAssignCnt     = 4u
/// \output         AnimMa_unDeactivateBlocksSpeedAssignCnt =3u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_DeleteBlockContext_SPEEDASSIGN()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_DeleteBlockContext_BlkIdx        = 2u;
    AnimMa_BlockContext_BkType              = SPEEDASSIGN;
    AnimMa_unActiveBlocksSpeedAssignCnt     = 5u;
    AnimMa_unDeactivateBlocksSpeedAssignCnt = 2u;

    //Step 2) Call FUT
    AnimMa_DeleteBlockContext(AnimMa_DeleteBlockContext_BlkIdx, AnimMa_BlockContext_BkType);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_unActiveBlocksSpeedAssignCnt,     4u, == );
    AL_UNITTEST_CHECK(AnimMa_unDeactivateBlocksSpeedAssignCnt, 3u, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_DeleteBlockContext_SPEEDASSIGN_Exceed
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that SPEEDASSIGN block is deleted correctly when 
///                     the number of allocated blocks is exceeded
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input            AnimMa_unActiveBlocksSpeedAssignCnt = 3u;
/// \input            AnimMa_unDeactivateBlocksFlexCnt    = 4u;
/// \input            AnimMa_DeleteBlockContext_BlkIdx    = 5u;
/// \input            AnimMa_BlockContext_BkType          = SPEEDASSIGN;
///
///   - Expectations:
///
/// \output          AnimMa_unActiveBlocksSpeedAssignCnt     = 3u
/// \output          AnimMa_unDeactivateBlocksSpeedAssignCnt = 4u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_DeleteBlockContext_SPEEDASSIGN_Exceed()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_unActiveBlocksSpeedAssignCnt = 3u;
    AnimMa_unDeactivateBlocksFlexCnt    = 4u;
    AnimMa_DeleteBlockContext_BlkIdx    = 5u;
    AnimMa_BlockContext_BkType          = SPEEDASSIGN;

    //Step 2) Call FUT
    AnimMa_DeleteBlockContext(AnimMa_DeleteBlockContext_BlkIdx, AnimMa_BlockContext_BkType);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_unActiveBlocksSpeedAssignCnt, 3u, == );
    AL_UNITTEST_CHECK(AnimMa_unDeactivateBlocksFlexCnt,    4u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_DeleteBlockContext_PIECEWISELINEAR
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that PIECEWISELINEAR block is deleted correctly when 
///                     the number of allocated blocks is not exceeded
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           AnimMa_DeleteBlockContext_BlkIdx            = 2u;
/// \input           AnimMa_BlockContext_BkType                  = PIECEWISELINEAR;
/// \input           AnimMa_unActiveBlocksPiecewiseLinearCnt     = 5u;
/// \input           AnimMa_unDeactivateBlocksPiecewiseLinearCnt = 2u;
///
///   - Expectations:
///
/// \output         AnimMa_unActiveBlocksPiecewiseLinearCnt     = 4u
/// \output         AnimMa_unDeactivateBlocksPiecewiseLinearCnt = 3u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_DeleteBlockContext_PIECEWISELINEAR()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_DeleteBlockContext_BlkIdx            = 2u;
    AnimMa_BlockContext_BkType                  = PIECEWISELINEAR;
    AnimMa_unActiveBlocksPiecewiseLinearCnt     = 5u;
    AnimMa_unDeactivateBlocksPiecewiseLinearCnt = 2u;

    //Step 2) Call FUT
    AnimMa_DeleteBlockContext(AnimMa_DeleteBlockContext_BlkIdx, AnimMa_BlockContext_BkType);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_unActiveBlocksPiecewiseLinearCnt,     4u, == );
    AL_UNITTEST_CHECK(AnimMa_unDeactivateBlocksPiecewiseLinearCnt, 3u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_DeleteBlockContext_PIECEWISELINEAR_Exceed
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that PIECEWISELINEAR block is deleted correctly when 
///                     the number of allocated blocks is exceeded
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           AnimMa_unActiveBlocksPiecewiseLinearCnt     = 3u;
/// \input           AnimMa_unDeactivateBlocksPiecewiseLinearCnt = 4u;
/// \input           AnimMa_DeleteBlockContext_BlkIdx            = 5u;
/// \input           AnimMa_BlockContext_BkType                  = PIECEWISELINEAR;
///
///   - Expectations:
///
/// \output         AnimMa_unActiveBlocksPiecewiseLinearCnt     = 3u
/// \output         AnimMa_unDeactivateBlocksPiecewiseLinearCnt = 4u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_DeleteBlockContext_PIECEWISELINEAR_Exceed()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_unActiveBlocksPiecewiseLinearCnt     = 3u;
    AnimMa_unDeactivateBlocksPiecewiseLinearCnt = 4u;
    AnimMa_DeleteBlockContext_BlkIdx            = 5u;
    AnimMa_BlockContext_BkType                  = PIECEWISELINEAR;
    //Step 2) Call FUT

    AnimMa_DeleteBlockContext(AnimMa_DeleteBlockContext_BlkIdx, AnimMa_BlockContext_BkType);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_unActiveBlocksPiecewiseLinearCnt,     3u, == );
    AL_UNITTEST_CHECK(AnimMa_unDeactivateBlocksPiecewiseLinearCnt, 4u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_DeleteBlockContext_INVERTINTENSITY
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that INVERTINTENSITY block is deleted correctly 
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           AnimMa_DeleteBlockContext_BlkIdx            = 2u;
/// \input           AnimMa_BlockContext_BkType                  = INVERTINTENSITY;
/// \input           AnimMa_unActiveBlocksInvertIntensityCnt     = 5u;
/// \input           AnimMa_unDeactivateBlocksInvertIntensityCnt = 2u;
///
///   - Expectations:
///
/// \output     AnimMa_unActiveBlocksInvertIntensityCnt     = 4u
/// \output     AnimMa_unDeactivateBlocksInvertIntensityCnt = 3u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_DeleteBlockContext_INVERTINTENSITY()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_DeleteBlockContext_BlkIdx            = 2u;
    AnimMa_BlockContext_BkType                  = INVERTINTENSITY;
    AnimMa_unActiveBlocksInvertIntensityCnt     = 5u;
    AnimMa_unDeactivateBlocksInvertIntensityCnt = 2u;
    //Step 2) Call FUT
    AnimMa_DeleteBlockContext(AnimMa_DeleteBlockContext_BlkIdx, AnimMa_BlockContext_BkType);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_unActiveBlocksInvertIntensityCnt,     4u, == );
    AL_UNITTEST_CHECK(AnimMa_unDeactivateBlocksInvertIntensityCnt, 3u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_DeleteBlockContext_TIMEOFFSET
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that TIMEOFFSET block is deleted correctly 
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           AnimMa_DeleteBlockContext_BlkIdx            = 2u;
/// \input           AnimMa_BlockContext_BkType                  = TIMEOFFSET;
/// \input           AnimMa_unActiveBlocksInvertIntensityCnt     = 5u;
/// \input           AnimMa_unDeactivateBlocksInvertIntensityCnt = 2u;
///
///   - Expectations:
///
/// \output         AnimMa_unActiveBlocksInvertIntensityCnt     = 5u
/// \output         AnimMa_unDeactivateBlocksInvertIntensityCnt = 2u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_DeleteBlockContext_TIMEOFFSET()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_DeleteBlockContext_BlkIdx            = 2u;
    AnimMa_BlockContext_BkType                  = TIMEOFFSET;
    AnimMa_unActiveBlocksInvertIntensityCnt     = 5u;
    AnimMa_unDeactivateBlocksInvertIntensityCnt = 2u;

    //Step 2) Call FUT
    AnimMa_DeleteBlockContext(AnimMa_DeleteBlockContext_BlkIdx, AnimMa_BlockContext_BkType);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_unActiveBlocksInvertIntensityCnt,     5u, == );
    AL_UNITTEST_CHECK(AnimMa_unDeactivateBlocksInvertIntensityCnt, 2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_DeleteBlockContext_REPETITION
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that REPETITION block is deleted correctly when 
///                     the number of allocated blocks is not exceeded
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input            AnimMa_DeleteBlockContext_BlkIdx       = 2u;
/// \input            AnimMa_BlockContext_BkType             = REPETITION;
/// \input            AnimMa_unActiveBlocksRepetitionCnt     = 5u;
/// \input            AnimMa_unDeactivateBlocksRepetitionCnt = 2u;
///
///   - Expectations:
///
/// \output          AnimMa_unActiveBlocksRepetitionCnt     = 4u
/// \output          AnimMa_unDeactivateBlocksRepetitionCnt = 3u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_DeleteBlockContext_REPETITION()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_DeleteBlockContext_BlkIdx       = 2u;
    AnimMa_BlockContext_BkType             = REPETITION;
    AnimMa_unActiveBlocksRepetitionCnt     = 5u;
    AnimMa_unDeactivateBlocksRepetitionCnt = 2u;

    //Step 2) Call FUT
    AnimMa_DeleteBlockContext(AnimMa_DeleteBlockContext_BlkIdx, AnimMa_BlockContext_BkType);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_unActiveBlocksRepetitionCnt,     4u, == );
    AL_UNITTEST_CHECK(AnimMa_unDeactivateBlocksRepetitionCnt, 3u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_DeleteBlockContext_REPETITION_Exceed
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that REPETITION block is deleted correctly when 
///                     the number of allocated blocks is exceeded
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           AnimMa_unActiveBlocksRepetitionCnt     = 3u;
/// \input           AnimMa_unDeactivateBlocksRepetitionCnt = 4u;
/// \input           AnimMa_DeleteBlockContext_BlkIdx       = 5u;
/// \input           AnimMa_BlockContext_BkType             = REPETITION;
///
///   - Expectations:
///
/// \output         AnimMa_unActiveBlocksRepetitionCnt     = 3u
/// \output         AnimMa_unDeactivateBlocksRepetitionCnt = 4u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_DeleteBlockContext_REPETITION_Exceed()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_unActiveBlocksRepetitionCnt     = 3u;
    AnimMa_unDeactivateBlocksRepetitionCnt = 4u;
    AnimMa_DeleteBlockContext_BlkIdx       = 5u;
    AnimMa_BlockContext_BkType             = REPETITION;

    //Step 2) Call FUT
    AnimMa_DeleteBlockContext(AnimMa_DeleteBlockContext_BlkIdx, AnimMa_BlockContext_BkType);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_unActiveBlocksRepetitionCnt,     3u, == );
    AL_UNITTEST_CHECK(AnimMa_unDeactivateBlocksRepetitionCnt, 4u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_DeleteBlockContext_Default
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that Default block is working properly
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           AnimMa_unActiveBlocksRepetitionCnt     = 3u;
/// \input           AnimMa_unDeactivateBlocksRepetitionCnt = 4u
/// \input           AnimMa_DeleteBlockContext_BlkIdx       = 5u;
/// \input           AnimMa_BlockContext_BkType             = 18u;
///
///   - Expectations:
///
/// \output         AnimMa_unActiveBlocksRepetitionCnt     = 3u
/// \output         AnimMa_unDeactivateBlocksRepetitionCnt = 4u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_DeleteBlockContext_Default()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_unActiveBlocksRepetitionCnt      = 3u;
    AnimMa_unDeactivateBlocksRepetitionCnt  = 4u;
    AnimMa_DeleteBlockContext_BlkIdx        = 5u;
    AnimMa_BlockContext_BkType              = 18u;

    //Step 2) Call FUT
    AnimMa_DeleteBlockContext(AnimMa_DeleteBlockContext_BlkIdx, AnimMa_BlockContext_BkType);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_unActiveBlocksRepetitionCnt,     3u, == );
    AL_UNITTEST_CHECK(AnimMa_unDeactivateBlocksRepetitionCnt, 4u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_DeleteBlockContext
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  check the set event status value
///
/// \Expected test results : All test cases contained are passed
///
//----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_DeleteBlockContext(void)
{
    Mt_CtrlLed_AnimMa_DeleteBlockContext_RUN10();
    Mt_CtrlLed_AnimMa_DeleteBlockContext_RUN10_Exceed();
    Mt_CtrlLed_AnimMa_DeleteBlockContext_RUNN_Exceed();
    Mt_CtrlLed_AnimMa_DeleteBlockContext_RUNN();
    Mt_CtrlLed_AnimMa_DeleteBlockContext_SPARKLE_LFSR();
    Mt_CtrlLed_AnimMa_DeleteBlockContext_SPARKLE_LFSR_Exceed();
    Mt_CtrlLed_AnimMa_DeleteBlockContext_SPARKLE_XOR64();
    Mt_CtrlLed_AnimMa_DeleteBlockContext_SPARKLE_XOR64_Exceed();
    Mt_CtrlLed_AnimMa_DeleteBlockContext_CLAMP();
    Mt_CtrlLed_AnimMa_DeleteBlockContext_CLAMP_Exceed();
    Mt_CtrlLed_AnimMa_DeleteBlockContext_INVERT();
    Mt_CtrlLed_AnimMa_DeleteBlockContext_BLINK();
    Mt_CtrlLed_AnimMa_DeleteBlockContext_BLINK_Exceed();
    Mt_CtrlLed_AnimMa_DeleteBlockContext_FLEX();
    Mt_CtrlLed_AnimMa_DeleteBlockContext_FLEX_Exceed();
    Mt_CtrlLed_AnimMa_DeleteBlockContext_SPEEDASSIGN();
    Mt_CtrlLed_AnimMa_DeleteBlockContext_SPEEDASSIGN_Exceed();
    Mt_CtrlLed_AnimMa_DeleteBlockContext_PIECEWISELINEAR();
    Mt_CtrlLed_AnimMa_DeleteBlockContext_PIECEWISELINEAR_Exceed();
    Mt_CtrlLed_AnimMa_DeleteBlockContext_INVERTINTENSITY();
    Mt_CtrlLed_AnimMa_DeleteBlockContext_TIMEOFFSET();
    Mt_CtrlLed_AnimMa_DeleteBlockContext_REPETITION();
    Mt_CtrlLed_AnimMa_DeleteBlockContext_REPETITION_Exceed();
    Mt_CtrlLed_AnimMa_DeleteBlockContext_Default();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_Blocks_Init
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that init is working properly
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input              AnimMa_unActiveBlocksRun10Cnt                   = 0U;
/// \input              AnimMa_unDeactivateBlocksRun10Cnt               = 0U;
/// \input              AnimMa_aActiveBlocksRun10[i].ucMovePos          = 0U;
/// \input              AnimMa_aActiveBlocks[i].unGenParamCodIdx        = 0U;
/// \input              AnimMa_aActiveBlocks[i].unSpcParamCodIdx        = 0U;
/// \input              AnimMa_aActiveBlocks[i].ucBlkCtxIdx             = 0U;
/// \input              AnimMa_aActiveBlocksSparkleLfsr[i].unNextTime   = 0U;
/// \input              AnimMa_unActiveBlocksSparkleXor64Cnt            = 0U;
/// \input              AnimMa_unDeactivateBlocksSparkleXor64Cnt        = 0U;
/// \input              AnimMa_aActiveBlocksSparkleXor64[i].unNextTime  = 0U;
/// \input              AnimMa_aActiveBlocksSparkleXor64[i].ulReg       = 0U;
/// \input              AnimMa_unActiveBlocksBlinkCnt                   = 0U;
/// \input              AnimMa_unDeactivateBlocksBlinkCnt               = 0U;
/// \input              AnimMa_unActiveBlocksClampCnt                   = 0U;
/// \input              AnimMa_unDeactivateBlocksClampCnt               = 0U;
/// \input              AnimMa_unActiveBlocksInvertCnt                  = 0U;
/// \input              AnimMa_unDeactivateBlocksInvertCnt              = 0U;
/// \input              AnimMa_unActiveBlocksFlexCnt                    = 0U;
/// \input              AnimMa_unDeactivateBlocksFlexCnt                = 0U;
/// \input              AnimMa_unActiveBlocksPiecewiseLinearCnt         = 0U;
/// \input              AnimMa_unDeactivateBlocksPiecewiseLinearCnt     = 0U;
/// \input              AnimMa_unActiveBlocksInvertIntensityCnt         = 0U;
/// \input              AnimMa_unDeactivateBlocksInvertIntensityCnt     = 0U;
/// \input              AnimMa_unActiveBlocksRepetitionCnt              = 0U;
/// \input              AnimMa_unDeactivateBlocksRepetitionCnt          = 0U;
/// \input              AnimMa_aActiveBlocksFlex[i].ulNextTime          = 0U;
/// \input              AnimMa_aActiveBlocksFlex[i].ulPos               = 0U;
/// \input              AnimMaRamp_aucPxlIntTgt[i]                      = 0U;
/// \input              AnimMaRamp_aucPxlIntInc[i]                      = 0U;
/// \input              AnimMaRamp_aucPxlIntDec[i]                      = 0U;
///
///   - Expectations:
///
/// \output    AnimMa_unActiveBlocksCnt                   = 0u
/// \output    AnimMa_unActiveBlocksRun10Cnt              = 0u
/// \output    AnimMa_unDeactivateBlocksRun10Cn           = 0u
/// \output    AnimMa_unActiveBlocksRunNCnt               = 0u
/// \output    AnimMa_unDeactivateBlocksRunNCnt           = 0u
/// \output    AnimMa_unActiveBlocksSparkleLfsrCnt        = 0u
/// \output    AnimMa_unDeactivateBlocksSparkleLfsrCnt    = 0u
/// \output    AnimMa_unActiveBlocksSparkleXor64Cnt       = 0u
/// \output    AnimMa_unDeactivateBlocksSparkleXor64Cnt   = 0u
/// \output    AnimMa_unActiveBlocksBlinkCnt              = 0u
/// \output    AnimMa_unDeactivateBlocksBlinkCnt          = 0u
/// \output    AnimMa_unDeactivateBlocksClampCnt          = 0u
/// \output    AnimMa_unActiveBlocksInvertCnt             = 0u
/// \output    AnimMa_unDeactivateBlocksInvertCnt         = 0u
/// \output    AnimMa_unActiveBlocksFlexCnt               = 0u
/// \output    AnimMa_unDeactivateBlocksFlexCnt           = 0u
/// \output    AnimMa_unActiveBlocksSpeedAssignCnt        = 0u
/// \output    AnimMa_unDeactivateBlocksSpeedAssignCnt    = 0u
/// \output    AnimMa_unActiveBlocksPiecewiseLinearCnt    = 0u
/// \output    AnimMa_unDeactivateBlocksPiecewiseLinearCnt= 0u
/// \output    AnimMa_unActiveBlocksInvertIntensityCnt    = 0u
/// \output    AnimMa_unDeactivateBlocksInvertIntensityCnt= 0u
/// \output    AnimMa_unActiveBlocksRepetitionCnt         = 0u
/// \output    AnimMa_unDeactivateBlocksRepetitionCnt     = 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_Blocks_Init(void)
{
    uint32 i, j;
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_unActiveBlocksCnt = 0;
    for (i = 0; i < ANIMMA_NR_BLOCKS; i++)
    {
        AnimMa_aActiveBlocks[i].unGenParamCodIdx      = 0U;
        AnimMa_aActiveBlocks[i].unSpcParamCodIdx      = 0U;
        AnimMa_aActiveBlocks[i].ucBlkCtxIdx           = 0U;
    }
    AnimMa_unActiveBlocksRun10Cnt                     = 0U;
    AnimMa_unDeactivateBlocksRun10Cnt                 = 0U;
    for (i = 0; i < ANIMMA_NR_BLOCKS_RUN10; i++)      
    {
        AnimMa_aActiveBlocksRun10[i].ucMovePos        = 0U;
    }
    AnimMa_unActiveBlocksSparkleLfsrCnt               = 0U;
    AnimMa_unDeactivateBlocksSparkleLfsrCnt           = 0U;
    for (i = 0; i < ANIMMA_NR_BLOCKS_SPARKLE_LFSR; i++)
    {
        AnimMa_aActiveBlocksSparkleLfsr[i].unNextTime = 0U;
        for (j = 0; j < ANIMMA_BLOCK_LFSR_NR_REG_BYTES; j++)
        {
            AnimMa_aActiveBlocksSparkleLfsr[i].ucReg[j]= 0U;
        }
    }
    AnimMa_unActiveBlocksSparkleXor64Cnt               = 0U;
    AnimMa_unDeactivateBlocksSparkleXor64Cnt           = 0U;
    for (i = 0; i < ANIMMA_NR_BLOCKS_SPARKLE_XOR64; i++)
    {
        AnimMa_aActiveBlocksSparkleXor64[i].unNextTime = 0U;
        AnimMa_aActiveBlocksSparkleXor64[i].ulReg      = 0U;
    }
    AnimMa_unActiveBlocksBlinkCnt                      = 0U;
    AnimMa_unDeactivateBlocksBlinkCnt                  = 0U;
    AnimMa_unActiveBlocksClampCnt                      = 0U;
    AnimMa_unDeactivateBlocksClampCnt                  = 0U;
    AnimMa_unActiveBlocksInvertCnt                     = 0U;
    AnimMa_unDeactivateBlocksInvertCnt                 = 0U;
    AnimMa_unActiveBlocksFlexCnt                       = 0U;
    AnimMa_unDeactivateBlocksFlexCnt                   = 0U;
    AnimMa_unActiveBlocksPiecewiseLinearCnt            = 0U;
    AnimMa_unDeactivateBlocksPiecewiseLinearCnt        = 0U;
    AnimMa_unActiveBlocksInvertIntensityCnt            = 0U;
    AnimMa_unDeactivateBlocksInvertIntensityCnt        = 0U;
    AnimMa_unActiveBlocksRepetitionCnt                 = 0U;
    AnimMa_unDeactivateBlocksRepetitionCnt             = 0U;
    for (i = 0; i < ANIMMA_NR_BLOCKS_FLEX; i++)
    {
        AnimMa_aActiveBlocksFlex[i].ulNextTime         = 0U;
        AnimMa_aActiveBlocksFlex[i].ulPos              = 0U;
    }
    AnimMa_unActiveBlocksSpeedAssignCnt                = 0U;
    AnimMa_unDeactivateBlocksSpeedAssignCnt            = 0U;

    for (i = 0; i < ANIMMA_NR_PIXELS; i++)
    {
        AnimMaRamp_aucPxlIntTgt[i]                     = 0U;
        AnimMaRamp_aucPxlIntInc[i]                     = 0U;
        AnimMaRamp_aucPxlIntDec[i]                     = 0U;
    }
    //Step 2) Call FUT
    AnimMa_Blocks_Init();

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_unActiveBlocksCnt,                    0u, == );
    AL_UNITTEST_CHECK(AnimMa_unActiveBlocksRun10Cnt,               0u, == );
    AL_UNITTEST_CHECK(AnimMa_unDeactivateBlocksRun10Cnt,           0u, == );
    AL_UNITTEST_CHECK(AnimMa_unActiveBlocksRunNCnt,                0u, == );
    AL_UNITTEST_CHECK(AnimMa_unDeactivateBlocksRunNCnt,            0u, == );
    AL_UNITTEST_CHECK(AnimMa_unActiveBlocksSparkleLfsrCnt,         0u, == );
    AL_UNITTEST_CHECK(AnimMa_unDeactivateBlocksSparkleLfsrCnt,     0u, == );
    AL_UNITTEST_CHECK(AnimMa_unActiveBlocksSparkleXor64Cnt,        0u, == );
    AL_UNITTEST_CHECK(AnimMa_unDeactivateBlocksSparkleXor64Cnt,    0u, == );
    AL_UNITTEST_CHECK(AnimMa_unActiveBlocksBlinkCnt,               0u, == );
    AL_UNITTEST_CHECK(AnimMa_unDeactivateBlocksBlinkCnt,           0u, == );
    AL_UNITTEST_CHECK(AnimMa_unDeactivateBlocksClampCnt,           0u, == );
    AL_UNITTEST_CHECK(AnimMa_unActiveBlocksInvertCnt,              0u, == );
    AL_UNITTEST_CHECK(AnimMa_unDeactivateBlocksInvertCnt,          0u, == );
    AL_UNITTEST_CHECK(AnimMa_unActiveBlocksFlexCnt,                0u, == );
    AL_UNITTEST_CHECK(AnimMa_unDeactivateBlocksFlexCnt,            0u, == );
    AL_UNITTEST_CHECK(AnimMa_unActiveBlocksSpeedAssignCnt,         0u, == );
    AL_UNITTEST_CHECK(AnimMa_unDeactivateBlocksSpeedAssignCnt,     0u, == );
    AL_UNITTEST_CHECK(AnimMa_unActiveBlocksPiecewiseLinearCnt,     0u, == );
    AL_UNITTEST_CHECK(AnimMa_unDeactivateBlocksPiecewiseLinearCnt, 0u, == );
    AL_UNITTEST_CHECK(AnimMa_unActiveBlocksInvertIntensityCnt,     0u, == );
    AL_UNITTEST_CHECK(AnimMa_unDeactivateBlocksInvertIntensityCnt, 0u, == );
    AL_UNITTEST_CHECK(AnimMa_unActiveBlocksRepetitionCnt,          0u, == );
    AL_UNITTEST_CHECK(AnimMa_unDeactivateBlocksRepetitionCnt,      0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_TimeWarp
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check the modified time
///                     adds offsets from block TimeOffset and block Repetition.
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input            AnimMa_TimeWarp_Param            = 10u;
/// \input            sTimeWarp.ulTimeOffset           = 5u;
/// \input            sTimeWarp.ulTimeOffsetRepetition = 10u;
///
///   - Expectations:
///
/// \output           returnval = 25u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_TimeWarp()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_TimeWarp_Param            = 10u;
    sTimeWarp.ulTimeOffset           = 5u;
    sTimeWarp.ulTimeOffsetRepetition = 10u;

    //Step 2) Call FUT
    uint32 returnval = AnimMa_TimeWarp(AnimMa_TimeWarp_Param);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(returnval, 25u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_RepetitionStack_Push_TestCase1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check the push of unTime and ucBlockCnt to Repetition stack
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input            sTimeWarp.RepetitionStack.ucCnt    = 3u;
/// \input            sTimeWarp.ulTimeOffsetRepetition   = 25u;
/// \input            AnimMa_RepetitionStack_Push_Param1 = 4;
/// \input            AnimMa_RepetitionStack_Push_Param2 = 2u;
///
///   - Expectations:
///
/// \output     sTimeWarp.RepetitionStack.aValues[var].ulTimeOffset  = 4u
/// \output     sTimeWarp.RepetitionStack.aValues[var].ucRepBlkCntDn = 2u
/// \output     sTimeWarp.ulTimeOffsetRepetition                     = 29u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_RepetitionStack_Push_TestCase1()
{
    //Step 1) Set pre-conditions,Assign Input values
    sTimeWarp.RepetitionStack.ucCnt     = 3u;
    const uint32 var = sTimeWarp.RepetitionStack.ucCnt;
    sTimeWarp.ulTimeOffsetRepetition    = 25u;
    AnimMa_RepetitionStack_Push_Param1  = 4u;
    AnimMa_RepetitionStack_Push_Param2  = 2u;

    //Step 2) Call FUT
    AnimMa_RepetitionStack_Push(AnimMa_RepetitionStack_Push_Param1, AnimMa_RepetitionStack_Push_Param2);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(sTimeWarp.RepetitionStack.aValues[var].ulTimeOffset,  4u, == );
    AL_UNITTEST_CHECK(sTimeWarp.RepetitionStack.aValues[var].ucRepBlkCntDn, 2u, == );
    AL_UNITTEST_CHECK(sTimeWarp.ulTimeOffsetRepetition,                     29u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_RepetitionStack_Push_TestCase2
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check the push of unTime and ucBlockCnt to Repetition stack
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input            sTimeWarp.RepetitionStack.ucCnt                       = 5u;
/// \input            sTimeWarp.ulTimeOffsetRepetition                      = 25u;
/// \input            sTimeWarp.RepetitionStack.aValues[var].ulTimeOffset   = 0u;
/// \input            sTimeWarp.RepetitionStack.aValues[var].ucRepBlkCntDn  = 0u;
/// \input            AnimMa_RepetitionStack_Push_Param1                    = 4u;
/// \input            AnimMa_RepetitionStack_Push_Param2                    = 2u;
///
///   - Expectations:
///
/// \output     sTimeWarp.RepetitionStack.aValues[var].ulTimeOffset  = 0u
/// \output     sTimeWarp.RepetitionStack.aValues[var].ucRepBlkCntDn = 0u
/// \output     sTimeWarp.ulTimeOffsetRepetition                     = 25u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_RepetitionStack_Push_TestCase2()
{
    //Step 1) Set pre-conditions,Assign Input values
    sTimeWarp.RepetitionStack.ucCnt                      = 5u;
    const uint32 var = sTimeWarp.RepetitionStack.ucCnt;
    sTimeWarp.RepetitionStack.aValues[var].ulTimeOffset  = 0u;
    sTimeWarp.RepetitionStack.aValues[var].ucRepBlkCntDn = 0u;
    sTimeWarp.ulTimeOffsetRepetition                     = 25u;
    AnimMa_RepetitionStack_Push_Param1                   = 4;
    AnimMa_RepetitionStack_Push_Param2                   = 2u;

    //Step 2) Call FUT
    AnimMa_RepetitionStack_Push(AnimMa_RepetitionStack_Push_Param1, AnimMa_RepetitionStack_Push_Param2);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(sTimeWarp.RepetitionStack.aValues[var].ulTimeOffset  , 0u, == );
    AL_UNITTEST_CHECK(sTimeWarp.RepetitionStack.aValues[var].ucRepBlkCntDn , 0u, == );
    AL_UNITTEST_CHECK(sTimeWarp.ulTimeOffsetRepetition                     , 25u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_RepetitionStack_Pop_TestCase1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check the pop of last value from Repetition stack.
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           sTimeWarp.RepetitionStack.ucCnt                   = 1u;
/// \input           sTimeWarp.ulTimeOffsetRepetition                  = 15u;
/// \input           sTimeWarp.RepetitionStack.aValues[0].ulTimeOffset = 3u;
///
///   - Expectations:
///
/// \output     sTimeWarp.ulTimeOffsetRepetition = 12u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_RepetitionStack_Pop_TestCase1()
{
    //Step 1) Set pre-conditions,Assign Input values
    sTimeWarp.RepetitionStack.ucCnt                   = 1u;
    sTimeWarp.ulTimeOffsetRepetition                  = 15u;
    sTimeWarp.RepetitionStack.aValues[0].ulTimeOffset = 3u;

    //Step 2) Call FUT
    AnimMa_RepetitionStack_Pop();

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(sTimeWarp.ulTimeOffsetRepetition, 12u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_RepetitionStack_Pop_TestCase2
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check the pop of last value from Repetition stack.
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           sTimeWarp.RepetitionStack.ucCnt                    = 0u;
/// \input           sTimeWarp.ulTimeOffsetRepetition                   = 16u;
/// \input           sTimeWarp.RepetitionStack.aValues[0u].ulTimeOffset = 2u;
///
///   - Expectations:
///
/// \output     sTimeWarp.ulTimeOffsetRepetition = 16u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_RepetitionStack_Pop_TestCase2()
{
    //Step 1) Set pre-conditions,Assign Input values
    sTimeWarp.RepetitionStack.ucCnt                    = 0u;
    sTimeWarp.ulTimeOffsetRepetition                   = 16u;
    sTimeWarp.RepetitionStack.aValues[0u].ulTimeOffset = 2u;

    //Step 2) Call FUT
    AnimMa_RepetitionStack_Pop();

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(sTimeWarp.ulTimeOffsetRepetition, 16u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_UpdateRepetition_TestCase1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Update the Repetition stack: pop (remove) an element if its (number of) blocks have been executed
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           sTimeWarp.RepetitionStack.ucCnt                    = 3u;
/// \input           sTimeWarp.RepetitionStack.aValues[2].ucRepBlkCntDn = 7u;
///
///   - Expectations:
///
/// \output     sTimeWarp.RepetitionStack.aValues[2].ucRepBlkCntDn = 6u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_UpdateRepetition_TestCase1()
{
    //Step 1) Set pre-conditions,Assign Input values
    sTimeWarp.RepetitionStack.ucCnt                    = 3u;
    sTimeWarp.RepetitionStack.aValues[2].ucRepBlkCntDn = 7u;

    //Step 2) Call FUT
    AnimMa_UpdateRepetition();

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(sTimeWarp.RepetitionStack.aValues[2].ucRepBlkCntDn, 6u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_UpdateRepetition_TestCase2
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Update the Repetition stack: pop (remove) an element if its (number of) blocks have not been executed
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           sTimeWarp.RepetitionStack.ucCnt                    = 0u;
/// \input           sTimeWarp.RepetitionStack.aValues[2].ucRepBlkCntDn = 0u;
///
///   - Expectations:
///
/// \output     sTimeWarp.RepetitionStack.aValues[2].ucRepBlkCntDn = 0u
/// \output     sTimeWarp.RepetitionStack.ucCnt                    = 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_UpdateRepetition_TestCase2()
{
    //Step 1) Set pre-conditions,Assign Input values
    sTimeWarp.RepetitionStack.ucCnt                    = 0u;
    sTimeWarp.RepetitionStack.aValues[0].ucRepBlkCntDn = 0u;

    //Step 2) Call FUT
    AnimMa_UpdateRepetition();

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(sTimeWarp.RepetitionStack.ucCnt,                    0u, == );
    AL_UNITTEST_CHECK(sTimeWarp.RepetitionStack.aValues[0].ucRepBlkCntDn, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_UpdateRepetition_TestCase3
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Update the Repetition stack: pop (remove) 5 elements if its (number of) blocks have been executed
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           sTimeWarp.RepetitionStack.ucCnt                    = 5u;
/// \input           sTimeWarp.RepetitionStack.aValues[2].ucRepBlkCntDn = 0u;
///
///   - Expectations:
///
/// \output     sTimeWarp.RepetitionStack.aValues[2].ucRepBlkCntDn = 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_UpdateRepetition_TestCase3()
{
    //Step 1) Set pre-conditions,Assign Input values
    sTimeWarp.RepetitionStack.ucCnt                    = 5u;
    sTimeWarp.RepetitionStack.aValues[0].ucRepBlkCntDn = 0u;

    //Step 2) Call FUT
    AnimMa_UpdateRepetition();

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(sTimeWarp.RepetitionStack.aValues[0].ucRepBlkCntDn, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_Repetition
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check repetition block in sequence
///
/// \Expected test results : All test cases contained are passed
///
//----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_Repetition(void)
{
    Mt_CtrlLed_AnimMa_RepetitionStack_Push_TestCase1();
    Mt_CtrlLed_AnimMa_RepetitionStack_Push_TestCase2();
    Mt_CtrlLed_AnimMa_RepetitionStack_Pop_TestCase1();
    Mt_CtrlLed_AnimMa_RepetitionStack_Pop_TestCase2();
    Mt_CtrlLed_AnimMa_UpdateRepetition_TestCase1();
    Mt_CtrlLed_AnimMa_UpdateRepetition_TestCase2();
    Mt_CtrlLed_AnimMa_UpdateRepetition_TestCase3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_EnableInitContext_TestCase1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check  initializations of block contexts
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input            AnimMa_EnableInitContext_Param = 5u;
/// \input            sTimeWarp.ucInitContextCnt     = 6u;
///
///   - Expectations:
///
/// \output     sTimeWarp.ucInitContextCnt = 6u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_EnableInitContext_TestCase1()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_EnableInitContext_Param = 5u;
    sTimeWarp.ucInitContextCnt     = 6u;

    //Step 2) Call FUT
    AnimMa_EnableInitContext(AnimMa_EnableInitContext_Param);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(sTimeWarp.ucInitContextCnt, 6u, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_EnableInitContext_TestCase2
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check  initializations of block contexts
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input            AnimMa_EnableInitContext_Param = 5u;
/// \input            sTimeWarp.ucInitContextCnt     = 4u;
///
///   - Expectations:
///
/// \output     sTimeWarp.ucInitContextCnt = 5u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_EnableInitContext_TestCase2()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_EnableInitContext_Param = 5u;
    sTimeWarp.ucInitContextCnt     = 4u;

    //Step 2) Call FUT
    AnimMa_EnableInitContext(AnimMa_EnableInitContext_Param);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(sTimeWarp.ucInitContextCnt, 5u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_EnableInitContext_TestCase3
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check  initializations of block contexts
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input            AnimMa_EnableInitContext_Param = 4u;
/// \input            sTimeWarp.ucInitContextCnt     = 4u;
///
///   - Expectations:
///
/// \output     sTimeWarp.ucInitContextCnt = 4u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_EnableInitContext_TestCase3()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_EnableInitContext_Param = 4u;
    sTimeWarp.ucInitContextCnt     = 4u;

    //Step 2) Call FUT
    AnimMa_EnableInitContext(AnimMa_EnableInitContext_Param);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(sTimeWarp.ucInitContextCnt, 4u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_EnableInitContext
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check initial context of the animation
///
/// \Expected test results : All test cases contained are passed
///
//----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_EnableInitContext(void)
{
    Mt_CtrlLed_AnimMa_EnableInitContext_TestCase1();
    Mt_CtrlLed_AnimMa_EnableInitContext_TestCase2();
    Mt_CtrlLed_AnimMa_EnableInitContext_TestCase3();
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_CtrlLed_Anima_AnimMa_Cod_GetSequenceIdx
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check the sequence id and if sequence was not found return 0;
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           AnimMa_Cod_GetSequenceIdx_Param = 74
///
///   - Expectations:
///
/// \output     AnimMa_Cod_GetSequenceIdx_RetVal = 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_Cod_GetSequenceIdx()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_Cod_GetSequenceIdx_Param = 74u;

    //Step 2) Call FUT
    AnimMa_Cod_GetSequenceIdx_RetVal = AnimMa_Cod_GetSequenceIdx(AnimMa_Cod_GetSequenceIdx_Param);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_Cod_GetSequenceIdx_RetVal, 0u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_CtrlLed_Anima_AnimMa_FindSequence_TestCase1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  find the sequence id
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           AnimMa_FindSequence_Param    = 74u;
/// \input           AnimMa_ucActiveSeqCnt        = 4u;
/// \input           AnimMa_aActiveSeq[0].ucSeqId = 2u;
/// \input           AnimMa_aActiveSeq[1].ucSeqId = 1u;
/// \input           AnimMa_aActiveSeq[2].ucSeqId = 2u;
/// \input           AnimMa_aActiveSeq[3].ucSeqId = 4u;
///
///   - Expectations:
///
/// \output     AnimMa_FindSequence_RetVal = 4u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_FindSequence_TestCase1()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_FindSequence_Param    = 74u;
    AnimMa_ucActiveSeqCnt        = 4u;
    AnimMa_aActiveSeq[0].ucSeqId = 2u;
    AnimMa_aActiveSeq[1].ucSeqId = 1u;
    AnimMa_aActiveSeq[2].ucSeqId = 2u;
    AnimMa_aActiveSeq[3].ucSeqId = 4u;

    //Step 2) Call FUT
    AnimMa_FindSequence_RetVal = AnimMa_FindSequence(AnimMa_FindSequence_Param);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_FindSequence_RetVal, 4u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_CtrlLed_Anima_AnimMa_FindSequence_TestCase2
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  find the sequence id
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           AnimMa_FindSequence_Param    = 2u;
/// \input           AnimMa_ucActiveSeqCnt        = 4u;
/// \input           AnimMa_aActiveSeq[0].ucSeqId = 2u;
/// \input           AnimMa_aActiveSeq[1].ucSeqId = 1u;
/// \input           AnimMa_aActiveSeq[2].ucSeqId = 2u;
/// \input           AnimMa_aActiveSeq[3].ucSeqId = 4u;
///
///   - Expectations:
///
/// \output     AnimMa_FindSequence_RetVal = 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_FindSequence_TestCase2()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_FindSequence_Param    = 2u;
    AnimMa_ucActiveSeqCnt        = 4u;
    AnimMa_aActiveSeq[0].ucSeqId = 2u;
    AnimMa_aActiveSeq[1].ucSeqId = 1u;
    AnimMa_aActiveSeq[2].ucSeqId = 2u;
    AnimMa_aActiveSeq[3].ucSeqId = 4u;

    //Step 2) Call FUT
    AnimMa_FindSequence_RetVal = AnimMa_FindSequence(AnimMa_FindSequence_Param);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_FindSequence_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Anima_AnimMa_FindSequence
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check start sequence
///
/// \Expected test results : All test cases contained are passed
///
//----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_FindSequence(void)
{
    Mt_CtrlLed_Anima_AnimMa_FindSequence_TestCase1();
    Mt_CtrlLed_Anima_AnimMa_FindSequence_TestCase2();
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_CtrlLed_Anima_AnimMa_IsIdxValid_TestCase1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  check id validity for calculating elapsed time
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input          ulIdx                 = 5u;
/// \input          AnimMa_ucActiveSeqCnt = 4u;
///
///   - Expectations:
///
/// \output     RetVal = 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_IsIdxValid_TestCase1()
{
    uint32 ulIdx;
    uint32 RetVal;
    //Step 1) Set pre-conditions,Assign Input values
    ulIdx                 = 5u;
    AnimMa_ucActiveSeqCnt = 4u;

    //Step 2) Call FUT
    RetVal = AnimMa_IsIdxValid(ulIdx);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(RetVal, 0u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_CtrlLed_Anima_AnimMa_IsIdxValid_TestCase2
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  check id validity for calculating elapsed time
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input          ulIdx                  = 5u;
/// \input          AnimMa_ucActiveSeqCnt  = 6u;
///
///   - Expectations:
///
/// \output     RetVal = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_IsIdxValid_TestCase2()
{
    uint32 ulIdx;
    uint32 RetVal;
    //Step 1) Set pre-conditions,Assign Input values
    ulIdx                 = 5u;
    AnimMa_ucActiveSeqCnt = 6u;

    //Step 2) Call FUT
    RetVal = AnimMa_IsIdxValid(ulIdx);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Anima_AnimMa_IsIdxValid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check start sequence
///
/// \Expected test results : All test cases contained are passed
///
//----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_IsIdxValid(void)
{
    Mt_CtrlLed_Anima_AnimMa_IsIdxValid_TestCase1();
    Mt_CtrlLed_Anima_AnimMa_IsIdxValid_TestCase2();
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_CtrlLed_Anima_AnimMa_isSequenceActive_TestCase1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  check if sequence is currently active
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           AnimMa_isSequenceActive_Param = 5u;
/// \input           AnimMa_ucActiveSeqCnt         = 4u;
/// \input           AnimMa_aActiveSeq[0].ucSeqId  = 2u;
/// \input           AnimMa_aActiveSeq[1].ucSeqId  = 1u;
/// \input           AnimMa_aActiveSeq[2].ucSeqId  = 2u;
/// \input           AnimMa_aActiveSeq[3].ucSeqId  = 4u;
///
///   - Expectations:
///
/// \output     AnimMa_isSequenceActive_RetVal = 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_isSequenceActive_TestCase1()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_isSequenceActive_Param = 5u;
    AnimMa_ucActiveSeqCnt         = 4u;
    AnimMa_aActiveSeq[0].ucSeqId  = 2u;
    AnimMa_aActiveSeq[1].ucSeqId  = 1u;
    AnimMa_aActiveSeq[2].ucSeqId  = 2u;
    AnimMa_aActiveSeq[3].ucSeqId  = 4u;

    //Step 2) Call FUT
    AnimMa_isSequenceActive_RetVal = AnimMa_isSequenceActive(AnimMa_isSequenceActive_Param);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_isSequenceActive_RetVal, 0u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_CtrlLed_Anima_AnimMa_isSequenceActive_TestCase2
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  check if sequence is currently active
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           AnimMa_isSequenceActive_Param = 4u;
/// \input           AnimMa_ucActiveSeqCnt         = 4u;
/// \input           AnimMa_aActiveSeq[0].ucSeqId  = 2u;
/// \input           AnimMa_aActiveSeq[1].ucSeqId  = 1u;
/// \input           AnimMa_aActiveSeq[2].ucSeqId  = 2u;
/// \input           AnimMa_aActiveSeq[3].ucSeqId  = 4u;
///
///   - Expectations:
///
/// \output     AnimMa_isSequenceActive_RetVal = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_isSequenceActive_TestCase2()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_isSequenceActive_Param = 4u;
    AnimMa_ucActiveSeqCnt         = 4u;
    AnimMa_aActiveSeq[0].ucSeqId  = 2u;
    AnimMa_aActiveSeq[1].ucSeqId  = 1u;
    AnimMa_aActiveSeq[2].ucSeqId  = 2u;
    AnimMa_aActiveSeq[3].ucSeqId  = 4u;

    //Step 2) Call FUT
    AnimMa_isSequenceActive_RetVal = AnimMa_isSequenceActive(AnimMa_isSequenceActive_Param);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_isSequenceActive_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Anima_AnimMa_isSequenceActive
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check start sequence
///
/// \Expected test results : All test cases contained are passed
///
//----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_isSequenceActive(void)
{
    Mt_CtrlLed_Anima_AnimMa_isSequenceActive_TestCase1();
    Mt_CtrlLed_Anima_AnimMa_isSequenceActive_TestCase2();
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_CtrlLed_Anima_AnimMa_isStopSequenceActive_TestCase1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  check if sequence is active and return true if it is
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           AnimMa_isStopSequenceActive_Param = 4u;
/// \input           AnimMa_ucActiveSeqCnt             = 4u;
/// \input           AnimMa_aActiveSeq[0].ucSeqId      = 2u;
/// \input           AnimMa_aActiveSeq[1].ucSeqId      = 1u;
/// \input           AnimMa_aActiveSeq[2].ucSeqId      = 2u;
/// \input           AnimMa_aActiveSeq[3].ucSeqId      = 4u;
/// \input           AnimMa_aActiveSeq[0].unStopBlocks = 2u;
/// \input           AnimMa_aActiveSeq[1].unStopBlocks = 1u;
/// \input           AnimMa_aActiveSeq[2].unStopBlocks = 2u;
/// \input           AnimMa_aActiveSeq[3].unStopBlocks = 4u;
/// \input           AnimMa_aActiveSeq[0].unSeqStatus  = StopSeqRun;
/// \input           AnimMa_aActiveSeq[1].unSeqStatus  = StopSeqRun;
/// \input           AnimMa_aActiveSeq[2].unSeqStatus  = StopSeqRun;
/// \input           AnimMa_aActiveSeq[3].unSeqStatus  = StopSeqRun;
///
///   - Expectations:
///
/// \output     AnimMa_isStopSequenceActive_RetVal = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_isStopSequenceActive_TestCase1()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_isStopSequenceActive_Param = 4u;
    AnimMa_ucActiveSeqCnt             = 4u;
    AnimMa_aActiveSeq[0].ucSeqId      = 2u;
    AnimMa_aActiveSeq[1].ucSeqId      = 1u;
    AnimMa_aActiveSeq[2].ucSeqId      = 2u;
    AnimMa_aActiveSeq[3].ucSeqId      = 4u;
    AnimMa_aActiveSeq[0].unStopBlocks = 2u;
    AnimMa_aActiveSeq[1].unStopBlocks = 1u;
    AnimMa_aActiveSeq[2].unStopBlocks = 2u;
    AnimMa_aActiveSeq[3].unStopBlocks = 4u;
    AnimMa_aActiveSeq[0].unSeqStatus  = StopSeqRun;
    AnimMa_aActiveSeq[1].unSeqStatus  = StopSeqRun;
    AnimMa_aActiveSeq[2].unSeqStatus  = StopSeqRun;
    AnimMa_aActiveSeq[3].unSeqStatus  = StopSeqRun;

    //Step 2) Call FUT
    AnimMa_isStopSequenceActive_RetVal = AnimMa_isStopSequenceActive(AnimMa_isStopSequenceActive_Param);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_isStopSequenceActive_RetVal, 1u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_CtrlLed_Anima_AnimMa_isStopSequenceActive_TestCase2
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  check if sequence is active and return false if it is not
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           AnimMa_isStopSequenceActive_Param = 4u;
/// \input           AnimMa_ucActiveSeqCnt             = 16u;
/// \input           AnimMa_aActiveSeq[0].ucSeqId      = 2u;
/// \input           AnimMa_aActiveSeq[1].ucSeqId      = 1u;
/// \input           AnimMa_aActiveSeq[2].ucSeqId      = 2u;
/// \input           AnimMa_aActiveSeq[3].ucSeqId      = 4u;
/// \input           AnimMa_aActiveSeq[0].unStopBlocks = 2u;
/// \input           AnimMa_aActiveSeq[1].unStopBlocks = 1u;
/// \input           AnimMa_aActiveSeq[2].unStopBlocks = 2u;
/// \input           AnimMa_aActiveSeq[3].unStopBlocks = 4u;
/// \input           AnimMa_aActiveSeq[0].unSeqStatus  = ActiveSeqRun;
/// \input           AnimMa_aActiveSeq[1].unSeqStatus  = ActiveSeqRun;
/// \input           AnimMa_aActiveSeq[2].unSeqStatus  = ActiveSeqRun;
/// \input           AnimMa_aActiveSeq[3].unSeqStatus  = ActiveSeqRun;
///
///   - Expectations:
///
/// \output     AnimMa_isStopSequenceActive_RetVal = 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_isStopSequenceActive_TestCase2()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_isStopSequenceActive_Param = 4u;
    AnimMa_ucActiveSeqCnt             = 16u;
    AnimMa_aActiveSeq[0].ucSeqId      = 2u;
    AnimMa_aActiveSeq[1].ucSeqId      = 1u;
    AnimMa_aActiveSeq[2].ucSeqId      = 2u;
    AnimMa_aActiveSeq[3].ucSeqId      = 4u;
    AnimMa_aActiveSeq[0].unStopBlocks = 2u;
    AnimMa_aActiveSeq[1].unStopBlocks = 1u;
    AnimMa_aActiveSeq[2].unStopBlocks = 2u;
    AnimMa_aActiveSeq[3].unStopBlocks = 4u;
    AnimMa_aActiveSeq[0].unSeqStatus  = ActiveSeqRun;
    AnimMa_aActiveSeq[1].unSeqStatus  = ActiveSeqRun;
    AnimMa_aActiveSeq[2].unSeqStatus  = ActiveSeqRun;
    AnimMa_aActiveSeq[3].unSeqStatus  = ActiveSeqRun;

    //Step 2) Call FUT
    AnimMa_isStopSequenceActive_RetVal = AnimMa_isStopSequenceActive(AnimMa_isStopSequenceActive_Param);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_isStopSequenceActive_RetVal, 0u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_CtrlLed_Anima_AnimMa_isSeqActivePhase_WithNoRunningIDs_TestCase1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  check if sequence is active and return false if it is not
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input            AnimMa_isSeqActivePhase_WithNoRunningIDs_Param = 4u;
/// \input            AnimMa_ucActiveSeqCnt                          = 16u;
/// \input            AnimMa_aActiveSeq[0].ucSeqId                   = 2u;
/// \input            AnimMa_aActiveSeq[1].ucSeqId                   = 1u;
/// \input            AnimMa_aActiveSeq[2].ucSeqId                   = 2u;
/// \input            AnimMa_aActiveSeq[3].ucSeqId                   = 4u;
/// \input            AnimMa_aActiveSeq[0].unSeqCodIdx               = 2u;
/// \input            AnimMa_aActiveSeq[1].unSeqCodIdx               = 1u;
/// \input            AnimMa_aActiveSeq[2].unSeqCodIdx               = 2u;
/// \input            AnimMa_aActiveSeq[3].unSeqCodIdx               = 4u;
/// \input            AnimMa_aActiveSeq[0].unStopBlocks              = 2u;
/// \input            AnimMa_aActiveSeq[1].unStopBlocks              = 1u;
/// \input            AnimMa_aActiveSeq[2].unStopBlocks              = 2u;
/// \input            AnimMa_aActiveSeq[3].unStopBlocks              = 4u;
/// \input            AnimMa_aActiveSeq[0].unSeqStatus               = StopSeqRun;
/// \input            AnimMa_aActiveSeq[1].unSeqStatus               = ActiveSeqRun;
/// \input            AnimMa_aActiveSeq[2].unSeqStatus               = ActiveSeqRun;
/// \input            AnimMa_aActiveSeq[3].unSeqStatus               = ActiveSeqRun;
///
///   - Expectations:
///
/// \output     AnimMa_isSeqActivePhase_WithNoRunningIDs_RetVal = false
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_isSeqActivePhase_WithNoRunningIDs_TestCase1()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_isSeqActivePhase_WithNoRunningIDs_Param = 4u;
    AnimMa_ucActiveSeqCnt                          = 16u;
    AnimMa_aActiveSeq[0].ucSeqId                   = 2u;
    AnimMa_aActiveSeq[1].ucSeqId                   = 1u;
    AnimMa_aActiveSeq[2].ucSeqId                   = 2u;
    AnimMa_aActiveSeq[3].ucSeqId                   = 4u;
    AnimMa_aActiveSeq[0].unSeqCodIdx               = 2u;
    AnimMa_aActiveSeq[1].unSeqCodIdx               = 1u;
    AnimMa_aActiveSeq[2].unSeqCodIdx               = 2u;
    AnimMa_aActiveSeq[3].unSeqCodIdx               = 4u;
    AnimMa_aActiveSeq[0].unStopBlocks              = 2u;
    AnimMa_aActiveSeq[1].unStopBlocks              = 1u;
    AnimMa_aActiveSeq[2].unStopBlocks              = 2u;
    AnimMa_aActiveSeq[3].unStopBlocks              = 4u;
    AnimMa_aActiveSeq[0].unSeqStatus               = StopSeqRun;
    AnimMa_aActiveSeq[1].unSeqStatus               = ActiveSeqRun;
    AnimMa_aActiveSeq[2].unSeqStatus               = ActiveSeqRun;
    AnimMa_aActiveSeq[3].unSeqStatus               = ActiveSeqRun;

    //Step 2) Call FUT
    AnimMa_isSeqActivePhase_WithNoRunningIDs_RetVal = AnimMa_isSeqActivePhase_WithNoRunningIDs(AnimMa_isSeqActivePhase_WithNoRunningIDs_Param);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_isSeqActivePhase_WithNoRunningIDs_RetVal, false, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_CtrlLed_Anima_AnimMa_isSeqActivePhase_WithNoRunningIDs_TestCase2
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  check if sequence is active and return true if it is
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           AnimMa_isSeqActivePhase_WithNoRunningIDs_Param = 2u;
/// \input           AnimMa_ucActiveSeqCnt                          = 2u;
/// \input           AnimMa_aActiveSeq[0].ucSeqId                   = 2u;
/// \input           AnimMa_aActiveSeq[1].ucSeqId                   = 2u;
/// \input           AnimMa_aActiveSeq[0].unSeqCodIdx               = 0u;
/// \input           AnimMa_aActiveSeq[1].unSeqCodIdx               = 0u;
/// \input           AnimMa_aActiveSeq[0].unStopBlocks              = 1u;
/// \input           AnimMa_aActiveSeq[1].unStopBlocks              = 1u;
/// \input           AnimMa_aActiveSeq[0].unSeqStatus               = ActiveSeqRun;
/// \input           AnimMa_aActiveSeq[1].unSeqStatus               = ActiveSeqRun;
///
///   - Expectations:
///
/// \output     AnimMa_isSeqActivePhase_WithNoRunningIDs_RetVal = true
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_isSeqActivePhase_WithNoRunningIDs_TestCase2()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_isSeqActivePhase_WithNoRunningIDs_Param = 2u;
    AnimMa_ucActiveSeqCnt                          = 2u;
    AnimMa_aActiveSeq[0].ucSeqId                   = 2u;
    AnimMa_aActiveSeq[1].ucSeqId                   = 2u;
    AnimMa_aActiveSeq[0].unSeqCodIdx               = 0u;
    AnimMa_aActiveSeq[1].unSeqCodIdx               = 0u;
    AnimMa_aActiveSeq[0].unStopBlocks              = 1u;
    AnimMa_aActiveSeq[1].unStopBlocks              = 1u;
    AnimMa_aActiveSeq[0].unSeqStatus               = ActiveSeqRun;
    AnimMa_aActiveSeq[1].unSeqStatus               = ActiveSeqRun;

    //Step 2) Call FUT
    AnimMa_isSeqActivePhase_WithNoRunningIDs_RetVal = AnimMa_isSeqActivePhase_WithNoRunningIDs(AnimMa_isSeqActivePhase_WithNoRunningIDs_Param);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_isSeqActivePhase_WithNoRunningIDs_RetVal, true, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Anima_AnimMa_isStopSequenceActive
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check start sequence
///
/// \Expected test results : All test cases contained are passed
///
//----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_isStopSequenceActive(void)
{
    Mt_CtrlLed_Anima_AnimMa_isStopSequenceActive_TestCase1();
    Mt_CtrlLed_Anima_AnimMa_isStopSequenceActive_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Anima_AnimMa_isSeqActivePhase_WithNoRunningIDs
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check start sequence
///
/// \Expected test results : All test cases contained are passed
///
//----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_isSeqActivePhase_WithNoRunningIDs(void)
{
    Mt_CtrlLed_Anima_AnimMa_isSeqActivePhase_WithNoRunningIDs_TestCase1();
    Mt_CtrlLed_Anima_AnimMa_isSeqActivePhase_WithNoRunningIDs_TestCase2();
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_CtrlLed_Anima_AnimMa_getElapsedTime_TestCase1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  check if the elapsed time has passed and return it
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           AnimMa_getElapsedTime_Param                     = 2u;
/// \input           AnimMa_aActiveSeq[AnimMa_ucActiveSeqCnt].ulTime = 500u;
///
///   - Expectations:
///
/// \output     AnimMa_getElapsedTime_RetVal = 500u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_getElapsedTime_TestCase1()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_getElapsedTime_Param                     = 2u;
    AnimMa_aActiveSeq[AnimMa_ucActiveSeqCnt].ulTime = 500u;

    //Step 2) Call FUT
    AnimMa_getElapsedTime_RetVal = AnimMa_getElapsedTime(AnimMa_getElapsedTime_Param);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_getElapsedTime_RetVal, 500u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_CtrlLed_Anima_AnimMa_getElapsedTime_TestCase2
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  check if the elapsed time has passed and return 0xFFFFFF if it is not 
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           AnimMa_getElapsedTime_Param                     = 77u;
/// \input           AnimMa_aActiveSeq[AnimMa_ucActiveSeqCnt].ulTime = 500u;
///
///   - Expectations:
///
/// \output     AnimMa_getElapsedTime_RetVal = 0xFFFFFF
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_getElapsedTime_TestCase2()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_getElapsedTime_Param                     = 77u;
    AnimMa_aActiveSeq[AnimMa_ucActiveSeqCnt].ulTime = 500u;

    //Step 2) Call FUT
    AnimMa_getElapsedTime_RetVal = AnimMa_getElapsedTime(AnimMa_getElapsedTime_Param);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_getElapsedTime_RetVal, 0xFFFFFF, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Anima_AnimMa_getElapsedTime
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check start sequence
///
/// \Expected test results : All test cases contained are passed
///
//----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_getElapsedTime(void)
{
    Mt_CtrlLed_Anima_AnimMa_getElapsedTime_TestCase1();
    Mt_CtrlLed_Anima_AnimMa_getElapsedTime_TestCase2();
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_CtrlLed_Anima_AnimMa_stopSequence
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  check the correct stop of a sequence
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           AnimMa_stopSequence_Param    = eExtLightingAnimationReq_LockDay;
/// \input           AnimMa_ucActiveSeqCnt        = 16u;
/// \input           AnimMa_aActiveSeq[0].ucSeqId = 2u;
/// \input           AnimMa_aActiveSeq[1].ucSeqId = 1u;
/// \input           AnimMa_aActiveSeq[2].ucSeqId = 2u;
///                  AnimMa_aActiveSeq[3].ucSeqId = 4u;  
///   - Expectations:
///
/// \output     AnimMa_aActiveSeq[1].unSeqStatus = ActiveSeqRun
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_stopSequence()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_stopSequence_Param    = eExtLightingAnimationReq_LockDay;
    AnimMa_ucActiveSeqCnt        = 16u;
    AnimMa_aActiveSeq[0].ucSeqId = 2u;
    AnimMa_aActiveSeq[1].ucSeqId = 1u;
    AnimMa_aActiveSeq[2].ucSeqId = 2u;
    AnimMa_aActiveSeq[3].ucSeqId = 4u;

    //Step 2) Call FUT
    AnimMa_stopSequence(AnimMa_stopSequence_Param);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_aActiveSeq[1].unSeqStatus, ActiveSeqRun, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_CtrlLed_Anima_AnimMa_rcSequence_TestCase1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  check run normal block
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           AnimMa_aActiveSeq[0].unSeqStatus = 3u;
/// \input           AnimMa_aActiveSeq[0].ucBlkFstIdx = 5u;
/// \input           AnimMa_aActiveSeq[0].ulTime      = 500u;
///
///   - Expectations:
///
/// \output     AnimMa_aActiveSeq[0].ucBlkFstIdx = 5u
/// \output     AnimMa_aActiveSeq[0].ulTime      = 550u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_rcSequence_TestCase1()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_rcSequence_Param1         = 0u;
    AnimMa_aActiveSeq[0].unSeqStatus = 3u;
    AnimMa_aActiveSeq[0].ucBlkFstIdx = 5u;
    AnimMa_aActiveSeq[0].ulTime      = 500u;

    //Step 2) Call FUT
    AnimMa_rcSequence(AnimMa_rcSequence_Param1);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_aActiveSeq[0].ucBlkFstIdx, 5u, == );
    AL_UNITTEST_CHECK(AnimMa_aActiveSeq[0].ulTime,      550u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_CtrlLed_Anima_AnimMa_rcSequence_TestCase2
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  check run stop block
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           AnimMa_aActiveSeq[0].ucBlkFstIdx           = 1u;
/// \input           AnimMa_aActiveSeq[0].ulTime                = 500u;
/// \input           AnimMa_aActiveBlocks[1].unGenParamCodIdx   = 3u;
/// \input           Rte_Read_IoHwAbUser_GetMountingSide_Param1 = eMountedLeft;
/// \input           AnimMa_aActiveSeq[0].unStopBlocks          = 0u;
/// \input           AnimMa_aActiveSeq[0].unSeqStatus           = 2u;
/// \input           AnimMa_aActiveSeq[0].unSeqStatus           = 3u;
/// \input           AnimMa_aActiveBlocks[0].unGenParamCodIdx   = 1u;
///
///   - Expectations:
///
/// \output     AnimMa_aActiveSeq[0].ucBlkFstIdx = 0u
/// \output     AnimMa_aActiveSeq[0].ulTime      = 500u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_rcSequence_TestCase2()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_rcSequence_Param1                   = 1u;
    AnimMa_aActiveSeq[1].ucBlkFstIdx           = 1u;
    AnimMa_aActiveSeq[1].ulTime                = 500u;
    AnimMa_aActiveBlocks[1].unGenParamCodIdx   = 3u;
    Rte_Read_IoHwAbUser_GetMountingSide_Param1 = eMountedLeft;
    AnimMa_aActiveSeq[1].unStopBlocks          = 0u;
    AnimMa_aActiveSeq[1].unSeqStatus           = StopSeqRun;
    AnimMa_aActiveSeq[1].unSeqStatus           = 3u;
    AnimMa_aActiveSeq[1].unSeqCodIdx           = 3u;
    AnimMa_aActiveBlocks[1].unGenParamCodIdx   = 1u;

    //Step 2) Call FUT
    AnimMa_rcSequence(AnimMa_rcSequence_Param1);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_aActiveSeq[1].ucBlkFstIdx, 1u, == );
    AL_UNITTEST_CHECK(AnimMa_aActiveSeq[1].ulTime,      550u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Anima_AnimMa_rcSequence
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check start sequence
///
/// \Expected test results : All test cases contained are passed
///
//----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_rcSequence(void)
{
    Mt_CtrlLed_Anima_AnimMa_rcSequence_TestCase1();
    Mt_CtrlLed_Anima_AnimMa_rcSequence_TestCase2();
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_CtrlLed_Anima_AnimMa_startSequence_TestCase1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  check start sequence do not start due to invalid coding
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           AnimMa_startSequence_Param                                        = 38u;
/// \input           AnimMa_pCodingData.Animation.AnimationByteStream.aucByteStream[0] = NULL_PTR;
/// \input           AnimMa_ucActiveSeqCnt                                             = 48u;
/// \input           AnimMa_aActiveSeq[1].unSeqStatus                                  = 0u;
/// \input           AnimMa_aActiveSeq[0].ucSeqId                                      = 2u;
/// \input           AnimMa_aActiveSeq[1].ucSeqId                                      = 1u;
/// \input           AnimMa_aActiveSeq[2].ucSeqId                                      = 2u;
/// \input           AnimMa_aActiveSeq[3].ucSeqId                                      = 4u;
///
///   - Expectations:
///
/// \output     AnimMa_aActiveSeq[1].unSeqStatus = 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_startSequence_TestCase1()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_startSequence_Param                                         = 38u;
    AnimMa_pCodingData->Animation.AnimationByteStream.aucByteStream[0] = NULL_PTR;
    AnimMa_ucActiveSeqCnt                                              = 48u;
    AnimMa_aActiveSeq[1].unSeqStatus                                   = 0u;
    AnimMa_aActiveSeq[0].ucSeqId                                       = 2u;
    AnimMa_aActiveSeq[1].ucSeqId                                       = 1u;
    AnimMa_aActiveSeq[2].ucSeqId                                       = 2u;
    AnimMa_aActiveSeq[3].ucSeqId                                       = 4u;

    //Step 2) Call FUT
    AnimMa_startSequence(AnimMa_startSequence_Param);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_aActiveSeq[1].unSeqStatus, 0u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_CtrlLed_Anima_AnimMa_startSequence_TestCase2
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  check start sequence do not start due to exceeded active sequences
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input            AnimMa_startSequence_Param                                        = 38u;
/// \input            memcpy(&AnimMa_pCodingData->Animation.AnimationByteStream.aucByteStream[0], &Anima_CodPrj_aucAnimation1[0], sizeof(Anima_CodPrj_aucAnimation1[0] / sizeof(uint8)));
/// \input            AnimMa_ucActiveSeqCnt                                             = 48u;
/// \input            AnimMa_aActiveSeq[1].unSeqStatus                                  = 5u;
/// \input            AnimMa_aActiveSeq[0].ucSeqId                                      = 2u;
/// \input            AnimMa_aActiveSeq[1].ucSeqId                                      = 1u;
/// \input            AnimMa_aActiveSeq[2].ucSeqId                                      = 2u;
/// \input            AnimMa_aActiveSeq[3].ucSeqId                                      = 4u;
///
///   - Expectations:
///
/// \output      AnimMa_aActiveSeq[1].unSeqStatus = 5u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_startSequence_TestCase2()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_startSequence_Param       = 38u;
    memcpy(&AnimMa_pCodingData->Animation.AnimationByteStream.aucByteStream[0], &Anima_CodPrj_aucAnimation1[0], sizeof(Anima_CodPrj_aucAnimation1[0] / sizeof(uint8)));
    AnimMa_aActiveSeq[1].unSeqStatus = 5u;
    AnimMa_ucActiveSeqCnt            = 48u;
    AnimMa_aActiveSeq[0].ucSeqId     = 2u;
    AnimMa_aActiveSeq[1].ucSeqId     = 1u;
    AnimMa_aActiveSeq[2].ucSeqId     = 2u;
    AnimMa_aActiveSeq[3].ucSeqId     = 4u;

    //Step 2) Call FUT
    AnimMa_startSequence(AnimMa_startSequence_Param);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_aActiveSeq[1].unSeqStatus, 5u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_CtrlLed_Anima_AnimMa_startSequence_TestCase3
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  check start sequence do not start due to not correct Id
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input            AnimMa_startSequence_Param                                        = 29u;
/// \input            AnimMa_pCodingData.Animation.AnimationByteStream.aucByteStream[0] = &(Anima_CodPrj_aucAnimation1[0]);
/// \input            AnimMa_ucActiveSeqCnt                                             = 2u;
/// \input            AnimMa_aActiveSeq[1].unSeqStatus                                  = 8u;
/// \input            AnimMa_aActiveSeq[0].ucSeqId                                      = 2u;
/// \input            AnimMa_aActiveSeq[1].ucSeqId                                      = 1u;
/// \input            AnimMa_aActiveSeq[2].ucSeqId                                      = 2u;
/// \input            AnimMa_aActiveSeq[3].ucSeqId                                      = 4u;
///
///   - Expectations:
///
/// \output     AnimMa_aActiveSeq[1].unSeqStatus = 8u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_startSequence_TestCase3()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_startSequence_Param                                         = 29u;
    AnimMa_pCodingData->Animation.AnimationByteStream.aucByteStream[0] = Anima_CodPrj_aucAnimation1;
    AnimMa_ucActiveSeqCnt                                              = 2u;
    AnimMa_aActiveSeq[1].unSeqStatus                                   = 8u;
    AnimMa_aActiveSeq[0].ucSeqId                                       = 2u;
    AnimMa_aActiveSeq[1].ucSeqId                                       = 1u;
    AnimMa_aActiveSeq[2].ucSeqId                                       = 2u;
    AnimMa_aActiveSeq[3].ucSeqId                                       = 4u;

    //Step 2) Call FUT
    AnimMa_startSequence(AnimMa_startSequence_Param);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_aActiveSeq[1].unSeqStatus, 8u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_CtrlLed_Anima_AnimMa_startSequence_TestCase4
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  check start sequence do not start due to not active sequence
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input             AnimMa_startSequence_Param                                       = 1u;
/// \input             AnimMa_pCodingData.Animation.AnimationByteStream.aucByteStream[0] = &(Anima_CodPrj_aucAnimation1[0]);
/// \input             AnimMa_ucActiveSeqCnt                                             = 2u;
/// \input             AnimMa_aActiveSeq[0].ucSeqId                                      = 2u;
/// \input             AnimMa_aActiveSeq[1].ucSeqId                                      = 1u;
/// \input             AnimMa_aActiveSeq[2].ucSeqId                                      = 2u;
/// \input             AnimMa_aActiveSeq[3].ucSeqId                                      = 4u;
///
///   - Expectations:
///
/// \output     AnimMa_aActiveSeq[0].unSeqStatus = ActiveSeqRun
/// \output     AnimMa_aActiveSeq[1].unSeqStatus = ActiveSeqRun
/// \output     AnimMa_aActiveSeq[2].unSeqStatus = ActiveSeqRun
/// \output     AnimMa_aActiveSeq[3].unSeqStatus = ActiveSeqRun
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_startSequence_TestCase4()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_startSequence_Param   = 1u;
    memcpy(&AnimMa_pCodingData->Animation.AnimationByteStream.aucByteStream[0], &Anima_CodPrj_aucAnimation1[0], sizeof(Anima_CodPrj_aucAnimation1[0] / sizeof(uint8)));
    AnimMa_ucActiveSeqCnt        = 2u;
    AnimMa_aActiveSeq[0].ucSeqId = 2u;
    AnimMa_aActiveSeq[1].ucSeqId = 1u;
    AnimMa_aActiveSeq[2].ucSeqId = 2u;
    AnimMa_aActiveSeq[3].ucSeqId = 4u;

    //Step 2) Call FUT
    AnimMa_startSequence(AnimMa_startSequence_Param);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_aActiveSeq[0].unSeqStatus, ActiveSeqRun, != );
    AL_UNITTEST_CHECK(AnimMa_aActiveSeq[1].unSeqStatus, ActiveSeqRun, != );
    AL_UNITTEST_CHECK(AnimMa_aActiveSeq[2].unSeqStatus, ActiveSeqRun, == );
    AL_UNITTEST_CHECK(AnimMa_aActiveSeq[3].unSeqStatus, ActiveSeqRun, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_CtrlLed_Anima_AnimMa_startSequence_TestCase5
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  check start sequence do not start due invalid coding
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input             AnimMa_pCodingData               = NULL_PTR;
/// \input             AnimMa_aActiveSeq[0].unSeqStatus = 0u;
///
///   - Expectations:
///
/// \output     AnimMa_aActiveSeq[1].unSeqStatus = 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_startSequence_TestCase5()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_pCodingData               = NULL_PTR;
    AnimMa_aActiveSeq[0].unSeqStatus = 0u;

    //Step 2) Call FUT
    AnimMa_startSequence(1u);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_aActiveSeq[0].unSeqStatus, 0u, == )
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Anima_AnimMa_startSequence
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check start sequence
///
/// \Expected test results : All test cases contained are passed
///
//----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_startSequence(void)
{
    Mt_CtrlLed_Anima_AnimMa_startSequence_TestCase1();
    Mt_CtrlLed_Anima_AnimMa_startSequence_TestCase2();
    Mt_CtrlLed_Anima_AnimMa_startSequence_TestCase3();
    Mt_CtrlLed_Anima_AnimMa_startSequence_TestCase4();
    Mt_CtrlLed_Anima_AnimMa_startSequence_TestCase5();
}

///---------------------------------------------------------------------------- -
/// \Test Case : Mt_CtrlLed_Anima_AnimMa_clearSequence
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  check clear sequence correctly
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input            AnimMa_clearSequence_Param = 1u;
/// \input            AnimMa_ucActiveSeqCnt = 3u;
/// \input                AnimMa_unActiveBlocksCnt = 5u;
/// \input            AnimMa_aActiveSeq[AnimMa_clearSequence_Param].unSeqCodIdx  = 5u;
/// \input            AnimMa_aActiveSeq[AnimMa_clearSequence_Param].ucBlkFstIdx  = 1u;
/// \input            AnimMa_aActiveSeq[AnimMa_clearSequence_Param].ucSeqId      = eExtLightingAnimationReq_WelcomeDay;
/// \input            AnimMa_aActiveSeq[AnimMa_clearSequence_Param].ulTime       = 50u;
/// \input            AnimMa_aActiveSeq[AnimMa_clearSequence_Param].unSeqStatus  = ActiveSeqRun;
/// \input            AnimMa_aActiveSeq[AnimMa_clearSequence_Param].unStopBlocks = 0u;
/// \input            AnimMa_unActiveBlocksCnt                                   = 4u
/// \input            AnimMa_pCodingData                                         = &AnimaCodingAreaC
///
///   - Expectations:
///
/// \output     AnimMa_ucActiveSeqCnt = 2u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_clearSequence()
{
    //Step 1) Set pre-conditions,Assign Input values
    uint32 AnimMa_clearSequence_Param                          = 10u;
    AnimMa_ucActiveSeqCnt                                      = 3u;
    AnimMa_aActiveSeq[AnimMa_clearSequence_Param].unSeqCodIdx  = 5u;
    AnimMa_aActiveSeq[AnimMa_clearSequence_Param].ucBlkFstIdx  = 1u;
    AnimMa_aActiveSeq[AnimMa_clearSequence_Param].ucSeqId      = eExtLightingAnimationReq_WelcomeDay;
    AnimMa_aActiveSeq[AnimMa_clearSequence_Param].ulTime       = 50u;
    AnimMa_aActiveSeq[AnimMa_clearSequence_Param].unSeqStatus  = ActiveSeqRun;
    AnimMa_aActiveSeq[AnimMa_clearSequence_Param].unStopBlocks = 0u;
    AnimMa_unActiveBlocksCnt                                   = 4u;
    AnimMa_pCodingData                                         = &AnimaCodingAreaC;

    //Step 2) Call FUT
    AnimMa_clearSequence(AnimMa_clearSequence_Param);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_ucActiveSeqCnt, 2u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_CtrlLed_Anima_AnimMa_softStopSequence_TestCase1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  check soft stop with valid id
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input            AnimMa_ucActiveSeqCnt             = 1u;
/// \input            AnimMa_softStopSequence_Param     = eExtLightingAnimationReq_WelcomeDay;
/// \input            AnimMa_aActiveSeq[1].ucSeqId      = 1u;
/// \input            AnimMa_aActiveSeq[1].unStopBlocks = 2u;
/// \input            AnimMa_aActiveSeq[1].unSeqStatus  = ActiveSeqRun;
/// \input            AnimMa_aActiveSeq[1].ucBlkFstIdx  = 1u;
/// \input            AnimMa_aActiveSeq[1].unSeqCodIdx  = 5u;
/// \input            AnimMa_aActiveSeq[1].ulTime       = 50u;
/// \input            AnimMa_aActiveSeq[0].ucSeqId      = 1u;
/// \input            AnimMa_aActiveSeq[0].unStopBlocks = 2u;
/// \input            AnimMa_aActiveSeq[0].unSeqStatus  = ActiveSeqRun;
/// \input            AnimMa_aActiveSeq[0].ucBlkFstIdx  = 1u;
/// \input            AnimMa_aActiveSeq[0].unSeqCodIdx  = 5u;
/// \input            AnimMa_aActiveSeq[0].ulTime       = 50u;
/// \input            AnimMa_unActiveBlocksCnt          = 18u;
///
///   - Expectations:
///
/// \output     AnimMa_aActiveSeq[1].ulTime      = 50u
/// \output     AnimMa_aActiveSeq[1].ucBlkFstIdx = 1u
/// \output     AnimMa_aActiveSeq[1].unSeqCodIdx = 5u
/// \output     AnimMa_aActiveSeq[1].unSeqStatus = ActiveSeqRun
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_softStopSequence_TestCase1()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_ucActiveSeqCnt             = 1u;
    AnimMa_softStopSequence_Param     = eExtLightingAnimationReq_WelcomeDay;
    AnimMa_aActiveSeq[1].ucSeqId      = 1u;
    AnimMa_aActiveSeq[1].unStopBlocks = 2u;
    AnimMa_aActiveSeq[1].unSeqStatus  = ActiveSeqRun;
    AnimMa_aActiveSeq[1].ucBlkFstIdx  = 1u;
    AnimMa_aActiveSeq[1].unSeqCodIdx  = 5u;
    AnimMa_aActiveSeq[1].ulTime       = 50u;
    AnimMa_aActiveSeq[0].ucSeqId      = 1u;
    AnimMa_aActiveSeq[0].unStopBlocks = 2u;
    AnimMa_aActiveSeq[0].unSeqStatus  = ActiveSeqRun;
    AnimMa_aActiveSeq[0].ucBlkFstIdx  = 1u;
    AnimMa_aActiveSeq[0].unSeqCodIdx  = 5u;
    AnimMa_aActiveSeq[0].ulTime       = 50u;
    AnimMa_unActiveBlocksCnt          = 18u;

    AnimMa_unActiveBlocksCnt = 18u;

    //Step 2) Call FUT
    AnimMa_softStopSequence(AnimMa_softStopSequence_Param);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_aActiveSeq[1].ulTime,      50u, == );
    AL_UNITTEST_CHECK(AnimMa_aActiveSeq[1].ucBlkFstIdx, 1u, == );
    AL_UNITTEST_CHECK(AnimMa_aActiveSeq[1].unSeqCodIdx, 5u, == );
    AL_UNITTEST_CHECK(AnimMa_aActiveSeq[1].unSeqStatus, ActiveSeqRun, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_CtrlLed_Anima_AnimMa_softStopSequence_TestCase2
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  check soft stop with invalid id
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input            AnimMa_ucActiveSeqCnt             = 2u;
/// \input            AnimMa_softStopSequence_Param     = 1u;
/// \input            AnimMa_aActiveSeq[1].ucSeqId      = 1u;
/// \input            AnimMa_aActiveSeq[1].unStopBlocks = 0u;
/// \input            AnimMa_aActiveSeq[0].unSeqStatus  = StopSeqRun;
/// \input            AnimMa_aActiveSeq[1].unSeqStatus  = StopSeqRun;
/// \input            AnimMa_aActiveSeq[1].ucBlkFstIdx  = 1u;
/// \input            AnimMa_aActiveSeq[1].unSeqCodIdx  = 5u;
/// \input            AnimMa_aActiveSeq[1].ulTime       = 50u;
/// \input            AnimMa_unActiveBlocksCnt          = 18u;
///
///   - Expectations: 
///
/// \output     AnimMa_aActiveSeq[1].ulTime      = 50u
/// \output     AnimMa_aActiveSeq[1].ucBlkFstIdx = 1u
/// \output     AnimMa_aActiveSeq[1].unSeqCodIdx = 5u
/// \output     AnimMa_aActiveSeq[1].unSeqStatus = StopSeqRun
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_softStopSequence_TestCase2()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_ucActiveSeqCnt             = 2u;
    AnimMa_softStopSequence_Param     = eExtLightingAnimationReq_WelcomeDay;
    AnimMa_aActiveSeq[1].ucSeqId      = 1u;
    AnimMa_aActiveSeq[1].unStopBlocks = 0u;
    AnimMa_aActiveSeq[0].unSeqStatus  = StopSeqRun;
    AnimMa_aActiveSeq[1].unSeqStatus  = StopSeqRun;
    AnimMa_aActiveSeq[1].ucBlkFstIdx  = 1u;
    AnimMa_aActiveSeq[1].unSeqCodIdx  = 5u;
    AnimMa_aActiveSeq[1].ulTime       = 50u;
    AnimMa_unActiveBlocksCnt          = 18u;

    //Step 2) Call FUT
    AnimMa_softStopSequence(AnimMa_softStopSequence_Param);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_aActiveSeq[1].ulTime,      50u, == );
    AL_UNITTEST_CHECK(AnimMa_aActiveSeq[1].ucBlkFstIdx, 1u, == );
    AL_UNITTEST_CHECK(AnimMa_aActiveSeq[1].unSeqCodIdx, 5u, == );
    AL_UNITTEST_CHECK(AnimMa_aActiveSeq[1].unSeqStatus, StopSeqRun, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_CtrlLed_Anima_AnimMa_softStopSequence_TestCase3
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  check soft stop with invalid id
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input            AnimMa_ucActiveSeqCnt             = 1u;
/// \input            AnimMa_softStopSequence_Param     = eExtLightingAnimationReq_WelcomeDay;
/// \input            AnimMa_aActiveSeq[1].ucSeqId      = 2u;
/// \input            AnimMa_aActiveSeq[0].ucSeqId      = 2u;
/// \input            AnimMa_aActiveSeq[0].unStopBlocks = 1u;
/// \input            AnimMa_aActiveSeq[1].unStopBlocks = 1u;
/// \input            AnimMa_aActiveSeq[0].unSeqStatus  = StopSeqRun;
/// \input            AnimMa_aActiveSeq[1].unSeqStatus  = StopSeqRun;
/// \input            AnimMa_aActiveSeq[0].unSeqStatus  = StopSeqRun;
/// \input            AnimMa_aActiveSeq[1].ucBlkFstIdx  = 1u;
/// \input            AnimMa_aActiveSeq[1].unSeqCodIdx  = 5u;
/// \input            AnimMa_aActiveSeq[0].unSeqCodIdx  = 5u;
/// \input            AnimMa_aActiveSeq[1].ulTime       = 50u;
/// \input            AnimMa_aActiveSeq[0].ulTime       = 50u;
/// \input            AnimMa_unActiveBlocksCnt          = 18u;
///
///Expectations:
///
/// \output     AnimMa_aActiveSeq[1].ulTime      = 50u
/// \output     AnimMa_aActiveSeq[1].ucBlkFstIdx = 1u
/// \output     AnimMa_aActiveSeq[1].unSeqCodIdx = 5u
/// \output     AnimMa_aActiveSeq[1].unSeqStatus = StopSeqRun
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_softStopSequence_TestCase3()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_ucActiveSeqCnt             = 1u;
    AnimMa_softStopSequence_Param     = eExtLightingAnimationReq_WelcomeDay;
    AnimMa_aActiveSeq[1].ucSeqId      = 2u;
    AnimMa_aActiveSeq[0].ucSeqId      = 2u;
    AnimMa_aActiveSeq[0].unStopBlocks = 1u;
    AnimMa_aActiveSeq[1].unStopBlocks = 1u;
    AnimMa_aActiveSeq[0].unSeqStatus  = StopSeqRun;
    AnimMa_aActiveSeq[1].unSeqStatus  = StopSeqRun;
    AnimMa_aActiveSeq[0].unSeqStatus  = StopSeqRun;
    AnimMa_aActiveSeq[1].ucBlkFstIdx  = 1u;
    AnimMa_aActiveSeq[1].unSeqCodIdx  = 5u;
    AnimMa_aActiveSeq[0].unSeqCodIdx  = 5u;
    AnimMa_aActiveSeq[1].ulTime       = 50u;
    AnimMa_aActiveSeq[0].ulTime       = 50u;
    AnimMa_unActiveBlocksCnt          = 18u;

    //Step 2) Call FUT
     AnimMa_softStopSequence(AnimMa_softStopSequence_Param);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_aActiveSeq[1].ulTime,      50u, == );
    AL_UNITTEST_CHECK(AnimMa_aActiveSeq[1].ucBlkFstIdx, 1u, == );
    AL_UNITTEST_CHECK(AnimMa_aActiveSeq[1].unSeqCodIdx, 5u, == );
    AL_UNITTEST_CHECK(AnimMa_aActiveSeq[1].unSeqStatus, StopSeqRun, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Anima_AnimMa_softStopSequence
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check soft stop
///
/// \Expected test results : All test cases contained are passed
///
//----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_softStopSequence(void)
{
    Mt_CtrlLed_Anima_AnimMa_softStopSequence_TestCase1();
    Mt_CtrlLed_Anima_AnimMa_softStopSequence_TestCase2();
    Mt_CtrlLed_Anima_AnimMa_softStopSequence_TestCase3();
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_CtrlLed_Anima_AnimMa_ActiveSeqNr
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  check number of active sequences
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           AnimMa_ucActiveSeqCnt = 2u;
///
///Expectations:
///
/// \output     AnimMa_ActiveSeqNr_RetVal = 2u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_ActiveSeqNr()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_ucActiveSeqCnt = 2u;

    //Step 2) Call FUT
    AnimMa_ActiveSeqNr_RetVal = AnimMa_ActiveSeqNr();

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_ActiveSeqNr_RetVal, 2u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_CtrlLed_Anima_rcAnimMa50
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  check number of active sequences
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           AnimMa_pCodingData.Animation.AnimationByteStream.aucByteStream[0] = NULL_PTR;
/// \input           AnimMa_ucActiveSeqCnt                                             = 2u;
/// \input           AnimMa_aActiveSeq[0].unStopBlocks                                 = 0u;
/// \input           AnimMa_aActiveSeq[1].unStopBlocks                                 = 0u;
/// \input           AnimMa_aActiveSeq[0].unSeqStatus                                  = Inactive;
///                  AnimMa_aActiveSeq[1].unSeqStatus                                  = Inactive;
///   - Expectations:
///
/// \output     AnimMa_aActiveSeq[1].unStopBlocks = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_rcAnimMa50()
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_pCodingData                = NULL_PTR;
    AnimMa_ucActiveSeqCnt             = 2u;
    AnimMa_aActiveSeq[0].unStopBlocks = 0u;
    AnimMa_aActiveSeq[1].unStopBlocks = 0u;
    AnimMa_aActiveSeq[0].unSeqStatus  = Inactive;
    AnimMa_aActiveSeq[1].unSeqStatus  = Inactive;

    //Step 2) Call FUT
    rcAnimMa50();
    //Step 3) Check expected output values

    AL_UNITTEST_CHECK(AnimMa_aActiveSeq[1].unStopBlocks, 0u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_CtrlLed_Anima_Anima_ReadFrontTurnIndicatorCmd_TestCase1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  check the turn indicator request ON
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input          Rte_Read_SysMon_TurnIndicatorCmd_Req_Param1 = ReqLighted_On;
///
///   - Expectations:
///
/// \output     Anima_ReadFrontTurnIndicatorCmd_RetVal = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_Anima_ReadFrontTurnIndicatorCmd_TestCase1()
{
    //Step 1) Set pre-conditions,Assign Input values
    Rte_Read_SysMon_TurnIndicatorCmd_Req_Param1 = ReqLighted_On;

    //Step 2) Call FUT
    Anima_ReadFrontTurnIndicatorCmd_RetVal = Anima_ReadFrontTurnIndicatorCmd();

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(Anima_ReadFrontTurnIndicatorCmd_RetVal, TRUE, == )
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_CtrlLed_Anima_Anima_ReadFrontTurnIndicatorCmd_TestCase2
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  check the turn indicator request OFF
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           Rte_Read_SysMon_TurnIndicatorCmd_Req_Param1 = ReqLighted_Off;
/// \input           Anima_TgtPrep_TiDelayTimer.eState           = Di_On;
///
///   - Expectations:
///
/// \output     Anima_ReadFrontTurnIndicatorCmd_RetVal = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_Anima_ReadFrontTurnIndicatorCmd_TestCase2()
{
    //Step 1) Set pre-conditions,Assign Input values
    Rte_Read_SysMon_TurnIndicatorCmd_Req_Param1 = ReqLighted_Off;
    Anima_TgtPrep_TiDelayTimer.eState           = Di_On;

    //Step 2) Call FUT
    Anima_ReadFrontTurnIndicatorCmd_RetVal = Anima_ReadFrontTurnIndicatorCmd();

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(Anima_ReadFrontTurnIndicatorCmd_RetVal, FALSE, == )
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_CtrlLed_AnimMa_rcBlockSparkleXor64
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  check block id greater than the blocks sparkle xor64
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           uint32 AnimMa_unActiveBlocksSparkleXor64Cnt;
/// \input           uint32 unActiveBlkId                 = 0u;
/// \input           uint32 unTime                        = 0;
/// \input           AnimMa_unActiveBlocksSparkleXor64Cnt = 0u;
///
///   - Expectations:
///
/// \output     AnimMaRamp_aucPxlIntInc != 0;
/// \output     AnimMaRamp_aucPxlIntDec != 0;
/// \output     AnimMaRamp_aucPxlIntTgt != 0;
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_rcBlockSparkleXor64()
{
    //Step 1) Set pre-conditions,Assign Input values
    uint32 AnimMa_unActiveBlocksSparkleXor64Cnt;
    uint32 unActiveBlkId                 = 0u;
    uint32 unTime                        = 0u;
    AnimMa_unActiveBlocksSparkleXor64Cnt = 0u;

    //Step 2) Call FUT
    AnimMa_rcBlockSparkleXor64(unActiveBlkId, unTime);

    //Step 3) Check expected output values
   //check ithat anima master do not keep 0% intensity
    AL_UNITTEST_CHECK(AnimMaRamp_aucPxlIntInc, 0, != )
    AL_UNITTEST_CHECK(AnimMaRamp_aucPxlIntDec, 0, != )
    AL_UNITTEST_CHECK(AnimMaRamp_aucPxlIntTgt, 0, != )

}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_CtrlLed_AnimMa_muldiv32_ceil
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  check the ramp calculation 
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           muldiv32_ceil_Param1 = 100u;
/// \input           muldiv32_ceil_Param2 = 28u;
/// \input           muldiv32_ceil_Param3 = 3u;
///
///   - Expectations:
///
/// \output     muldiv32_ceil_RetVal = 934u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_muldiv32_ceil()
{
    //Step 1) Set pre-conditions,Assign Input values
    muldiv32_ceil_Param1 = 100u;
    muldiv32_ceil_Param2 = 28u;
    muldiv32_ceil_Param3 = 3u;

    //Step 2) Call FUT
    muldiv32_ceil_RetVal = muldiv32_ceil(muldiv32_ceil_Param1, muldiv32_ceil_Param2, muldiv32_ceil_Param3);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(muldiv32_ceil_RetVal, 934u, == );

}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_CtrlLed_AnimMa_Ramp_UpdateDelta_TestCase1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  check the ramp calculation case 1: dt > 0, y2 > y1, ulCur < ulTgt
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           uint32 dt1       = 10u;
/// \input           uint32 y11       = 20u;
/// \input           uint32 y21       = 40u;
/// \input           uint32 timestep1 = 5u;
/// \input           tStepRamp ramp1  = { 10u, 30u, 0u };
///
///   - Expectations:
///
/// \output     ramp1.ulDelta = 10u
///
//-----------------------------------------------------------------------------
void  Mt_CtrlLed_AnimMa_Ramp_UpdateDelta_TestCase1()
{
    //Step 1) Set pre-conditions,Assign Input values
    uint32 dt1       = 10u;
    uint32 y11       = 20u;
    uint32 y21       = 40u;
    uint32 timestep1 = 5u;
    tStepRamp ramp1  = { 10u, 30u, 0u };

    //Step 2) Call FUT
    AnimMa_Ramp_UpdateDelta(dt1, y11, y21, timestep1, &ramp1);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(ramp1.ulDelta, 10u, == )
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_CtrlLed_AnimMa_Ramp_UpdateDelta_TestCase2
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  check the ramp calculation  case 2: dt > 0, y2 < y1, ulCur < ulTgt
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           uint32 dt2       = 8u;
/// \input           uint32 y12       = 40u;
/// \input           uint32 y22       = 20u;
/// \input           uint32 timestep2 = 4u;
/// \input           tStepRamp ramp2  = { 30u, 10u, 0u };
///
///   - Expectations:
///
/// \output     ramp1.ulDelta = 10u
///
//-----------------------------------------------------------------------------
void  Mt_CtrlLed_AnimMa_Ramp_UpdateDelta_TestCase2()
{
    //Step 1) Set pre-conditions,Assign Input values
    uint32 dt2       = 8u;
    uint32 y12       = 40u;
    uint32 y22       = 20u;
    uint32 timestep2 = 4u;
    tStepRamp ramp2  = { 30u, 10u, 0u };

    //Step 2) Call FUT
    AnimMa_Ramp_UpdateDelta(dt2, y12, y22, timestep2, &ramp2);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(ramp2.ulDelta, 10u, == )
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_CtrlLed_AnimMa_Ramp_UpdateDelta_TestCase3
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  check the ramp calculation case 3: dt > 0, y2 > y1, ulCur > ulTgt
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           uint32 dt3       = 10u;
/// \input           uint32 y13       = 20u;
/// \input           uint32 y23       = 40u;
/// \input           uint32 timestep3 = 5u;
/// \input           tStepRamp ramp3  = { 30u, 10u, 0u };
///
///   - Expectations:
///
/// \output     ramp1.ulDelta = 10u
///
//-----------------------------------------------------------------------------
void  Mt_CtrlLed_AnimMa_Ramp_UpdateDelta_TestCase3()
{
    //Step 1) Set pre-conditions,Assign Input values
    uint32 dt3       = 10u;
    uint32 y13       = 20u;
    uint32 y23       = 40u;
    uint32 timestep3 = 5u;
    tStepRamp ramp3  = { 30u, 10u, 0u };

    //Step 2) Call FUT
    AnimMa_Ramp_UpdateDelta(dt3, y13, y23, timestep3, &ramp3);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(ramp3.ulDelta, 10u, == )
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_CtrlLed_AnimMa_Ramp_UpdateDelta_TestCase4
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  check the ramp calculation case 4: dt = 0
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input            uint32 dt4       = 0u;
/// \input            uint32 y14       = 40u;
/// \input            uint32 y24       = 20u;
/// \input            uint32 timestep4 = 4u;
/// \input            tStepRamp ramp4  = { 30u, 10u, 0u };
///
///   - Expectations:
///
/// \output     ramp1.ulDelta = 0u
///
//-----------------------------------------------------------------------------
void  Mt_CtrlLed_AnimMa_Ramp_UpdateDelta_TestCase4()
{
    //Step 1) Set pre-conditions,Assign Input values
    uint32 dt4       = 0u;
    uint32 y14       = 40u;
    uint32 y24       = 20u;
    uint32 timestep4 = 4u;
    tStepRamp ramp4  = { 30u, 10u, 0u };

    //Step 2) Call FUT
    AnimMa_Ramp_UpdateDelta(dt4, y14, y24, timestep4, &ramp4);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(ramp4.ulDelta, 0u, == )
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_Ramp_UpdateDelta
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  check the set event status value
///
/// \Expected test results : All test cases contained are passed
///
//----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_Ramp_UpdateDelta(void)
{
    Mt_CtrlLed_AnimMa_Ramp_UpdateDelta_TestCase1();
    Mt_CtrlLed_AnimMa_Ramp_UpdateDelta_TestCase2();
    Mt_CtrlLed_AnimMa_Ramp_UpdateDelta_TestCase3();
    Mt_CtrlLed_AnimMa_Ramp_UpdateDelta_TestCase4();
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_CtrlLed_AnimMa_Ramp_Step_TestCase1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject: Test case where pRamp->ulTgt is equal to pRamp->ulCur.
///    -               //This is a simple test case to ensure that the function handles the case
///    -               // where the current value is already equal to the target value.
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input             tStepRamp ramp = { 100, 100, 10 };
/// \input             ramp.ulCur     = 0;
/// \input             ramp.ulTgt     = 100;
/// \input             ramp.ulDelta   = 10;
///
///   - Expectations:
///
/// \output     ramp1.ulCur = 10u
///
//-----------------------------------------------------------------------------
void  Mt_CtrlLed_AnimMa_Ramp_Step_TestCase1()
{
    //Step 1) Set pre-conditions,Assign Input values
    tStepRamp ramp = { 100, 100, 10 };
    ramp.ulCur     = 0;
    ramp.ulTgt     = 100;
    ramp.ulDelta   = 10;

    //Step 2) Call FUT
    AnimMa_Ramp_Step(&ramp);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(ramp.ulCur, 10u, == )
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_CtrlLed_AnimMa_Ramp_Step_TestCase2
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject: Test case where pRamp->ulTgt is less than pRamp->ulCur
///    -               //and the delta is less than the difference between pRamp->ulTgt and pRamp->ulCur.
///    -               // This tests whether the function correctly decrements the current value by the delta.
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input             tStepRamp ramp = { 100, 100, 10 };
/// \input             ramp.ulCur     = 0;
/// \input             ramp.ulTgt     = 100;
/// \input             ramp.ulDelta   = 10;
///
///   - Expectations:
///
/// \output     ramp1.ulCur = 100u
///
//-----------------------------------------------------------------------------
void  Mt_CtrlLed_AnimMa_Ramp_Step_TestCase2()
{
    //Step 1) Set pre-conditions,Assign Input values
    tStepRamp ramp = { 100, 50, 10 };
    ramp.ulCur     = 0;
    ramp.ulTgt     = 100;
    ramp.ulDelta   = 200;

    //Step 2) Call FUT
    AnimMa_Ramp_Step(&ramp);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(ramp.ulCur, 100u, == )
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_CtrlLed_AnimMa_Ramp_Step_TestCase3
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject: Test case where pRamp->ulTgt is less than pRamp->ulCur
///    -               //and the delta is less than the difference between pRamp->ulTgt and pRamp->ulCur.
///    -               // This tests whether the function correctly decrements the current value by the delta.
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input             tStepRamp ramp = { 100, 100, 10 };
/// \input             ramp.ulCur     = 0;
/// \input             ramp.ulTgt     = 100;
/// \input             ramp.ulDelta   = 10;
///
///   - Expectations:
///
/// \output     ramp1.ulCur = 95u
///
//-----------------------------------------------------------------------------
void  Mt_CtrlLed_AnimMa_Ramp_Step_TestCase3()
{
    //Step 1) Set pre-conditions,Assign Input values
    tStepRamp ramp = { 100, 50, 10 };
    ramp.ulCur     = 100;
    ramp.ulTgt     = 90;
    ramp.ulDelta   = 5;

    //Step 2) Call FUT
    AnimMa_Ramp_Step(&ramp);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(ramp.ulCur, 95u, == )
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_CtrlLed_AnimMa_Ramp_Step_TestCase4
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject: Test case where pRamp->ulTgt is less than pRamp->ulCur
///    -               //and the delta is less than the difference between pRamp->ulTgt and pRamp->ulCur.
///    -               // This tests whether the function correctly decrements the current value by the delta.
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input            tStepRamp ramp = { 100, 50, 10 };
/// \input            ramp.ulCur     = 100;
/// \input            ramp.ulTgt     = 90;
/// \input            ramp.ulDelta   = 15;
///
///   - Expectations:
///
/// \output     ramp1.ulCur = 90u
///
//-----------------------------------------------------------------------------
void  Mt_CtrlLed_AnimMa_Ramp_Step_TestCase4()
{
    //Step 1) Set pre-conditions,Assign Input values
    tStepRamp ramp = { 100, 50, 10 };
    ramp.ulCur     = 100;
    ramp.ulTgt     = 90;
    ramp.ulDelta   = 15;

    //Step 2) Call FUT
    AnimMa_Ramp_Step(&ramp);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(ramp.ulCur, 90u, == )
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_Ramp_Step
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  check the set event status value
///
/// \Expected test results : All test cases contained are passed
///
//----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_Ramp_Step(void)
{
    Mt_CtrlLed_AnimMa_Ramp_Step_TestCase1();
    Mt_CtrlLed_AnimMa_Ramp_Step_TestCase2();
    Mt_CtrlLed_AnimMa_Ramp_Step_TestCase3();
    Mt_CtrlLed_AnimMa_Ramp_Step_TestCase4();
}

// ---------------------------------------------------------------------------- -
/// \Test Case : void  Mt_CtrlLed_AnimMa_PiecewiseLinear_InitRamp_TestCase1()
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject: check the picewise linear block initialization when pCodSpc->ucN equals 0
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input             Anima_PicewiseInit[ANIMMA_CODING_BYTES] = {0x01, 0x01, 0x02, 0x00, 0x16, 0x02, 0x01, 0x09, 0x00, 0x0A, 0x00, 0x00, 0x28, 0x00, 0x0A, 0x0A, 0x02, 0x00, 0x04, 0x00, 0x32, 0x0A, 0x46, 0x14, 0x64, 0x28, 0x00};
/// \input             uint32 ulIdx                            = 0u;
/// \input             tBlockSpecificPiecewiseLinear  pCodSpc;
/// \input             pCodSpc.ucDimDnDec                      = 20u;
/// \input             pCodSpc.ucDimUpInc                      = 10u;
/// \input             pCodSpc.ucInitI                         = 30u;
/// \input             pCodSpc.ucN                             = 0u;
/// \input             pCodSpc.ucByte0                         =  &Anima_PicewiseInit[0];
/// \input             tStepRamp  pRamp                        = {0};
///
///   - Expectations:
///
/// \output     ramp1.ulCur   = 122880u
/// \output     ramp1.ulTgt   = 122880u
/// \output     ramp1.ulDelta = 0u
///
//-----------------------------------------------------------------------------
void  Mt_CtrlLed_AnimMa_PiecewiseLinear_InitRamp_TestCase1()
{
    memcpy(&AnimMa_pCodingData->Animation.AnimationByteStream.aucByteStream[0], &Anima_CodPrj_PicewiseInit[0], sizeof(Anima_CodPrj_PicewiseInit[0]) / sizeof(uint8));
    AnimMa_startSequence(2);
    //Step 1) Set pre-conditions,Assign Input values
    uint8 Anima_PicewiseInit[ANIMMA_CODING_BYTES] = {
0x01, 0x01, 0x02, 0x00, 0x16, 0x02, 0x01, 0x09, 0x00, 0x0A, 0x00, 0x00, 0x28, 0x00, 0x0A, 0x0A, 0x02, 0x00, 0x04, 0x00, 0x32, 0x0A, 0x46, 0x14, 0x64, 0x28, 0x00
    };
    uint32 ulIdx         = 0u;
    tBlockSpecificPiecewiseLinear  pCodSpc;
    pCodSpc.ucDimDnDec   = 20u;
    pCodSpc.ucDimUpInc   = 10u;
    pCodSpc.ucInitI      = 30u;
    pCodSpc.ucN          = 0u;
    pCodSpc.ucByte0      = &Anima_PicewiseInit[0];
    tStepRamp  pRamp     = { 0 };

    //Step 2) Call FUT
    AnimMa_PiecewiseLinear_InitRamp(ulIdx, &pCodSpc, &pRamp);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(pRamp.ulCur,   122880u, == )
    AL_UNITTEST_CHECK(pRamp.ulTgt,   122880u, == )
    AL_UNITTEST_CHECK(pRamp.ulDelta, 0u, == )
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_CtrlLed_AnimMa_PiecewiseLinear_InitRamp_TestCase2
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject: check the picewise linear block initialization when /ulIdx equals 0 and pCodSpc->ucN is greater than 0
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input             Anima_PicewiseInit[ANIMMA_CODING_BYTES] = {0x00, 0x00, 0x02, 0x00, 0x16, 0x02, 0x01, 0x09, 0x00, 0x0A, 0x00, 0x00, 0x28, 0x00, 0x0A, 0x0A, 0x02, 0x00, 0x04, 0x00, 0x32, 0x0A, 0x46, 0x14, 0x64, 0x28, 0x00};
/// \input             uint32 ulIdx   = 0;
/// \input             tBlockSpecificPiecewiseLinear pCodSpc = {
///                      .ucDimUpInc  = 10,
///                      .ucDimDnDec  = 20,
///                      .ucInitI     = 30,
///                      .ucN         = 1,
///                      .ucByte0     = &Anima_PicewiseInit[0]
///                  };
/// \input            tStepRamp pRamp = { 0 };
///
///   - Expectations:
///
/// \output     ramp1.ulCur    = 122880u
/// \output     ramp1.ulTgt    = 0u
/// \output     ramp1.ulDelta  = 1536u
///
//-----------------------------------------------------------------------------
void  Mt_CtrlLed_AnimMa_PiecewiseLinear_InitRamp_TestCase2()
{
    memcpy(&AnimMa_pCodingData->Animation.AnimationByteStream.aucByteStream[0], &Anima_CodPrj_PicewiseInit[0], sizeof(Anima_CodPrj_PicewiseInit[0]) / sizeof(uint8));    AnimMa_startSequence(2);
    //Step 1) Set pre-conditions,Assign Input values
    uint8 Anima_PicewiseInit[ANIMMA_CODING_BYTES] = {
  0x00, 0x00, 0x02, 0x00, 0x16, 0x02, 0x01, 0x09, 0x00, 0x0A, 0x00, 0x00, 0x28, 0x00, 0x0A, 0x0A, 0x02, 0x00, 0x04, 0x00, 0x32, 0x0A, 0x46, 0x14, 0x64, 0x28, 0x00
    };
    uint32 ulIdx    = 0u;
    tBlockSpecificPiecewiseLinear pCodSpc = {
        .ucDimUpInc = 10u,
        .ucDimDnDec = 20u,
        .ucInitI    = 30u,
        .ucN        = 1u,
        .ucByte0    = &Anima_PicewiseInit[0]
    };
    tStepRamp pRamp = { 0u };

    //Step 2) Call FUT
    AnimMa_PiecewiseLinear_InitRamp(ulIdx, &pCodSpc, &pRamp);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(pRamp.ulCur,   122880u, == )
    AL_UNITTEST_CHECK(pRamp.ulTgt,   0u, == )
    AL_UNITTEST_CHECK(pRamp.ulDelta, 1536u, == )
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_CtrlLed_AnimMa_PiecewiseLinear_InitRamp_TestCase3
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject: check the picewise linear block initialization when ulIdx is greater than 0 and less than pCodSpc->ucN
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input             uint8 Anima_PicewiseInit[ANIMMA_CODING_BYTES]={0x01, 0x01, 0x02, 0x00, 0x16, 0x02, 0x01, 0x09, 0x00, 0x0A, 0x00, 0x00, 0x28, 0x00, 0x0A, 0x0A, 0x02, 0x00, 0x04, 0x00, 0x32, 0x0A, 0x46, 0x14, 0x64, 0x28, 0x00};
/// \input             uint32 ulIdx    = 5;
/// \input             tBlockSpecificPiecewiseLinear pCodSpc = {
///                      .ucDimUpInc   = 10,
///                      .ucDimDnDec   = 20,
///                      .ucInitI-     = 30,
///                      .ucN          = 8,
///                      .ucByte0      =  &Anima_PicewiseInit[0]
///                  };
/// \input             tStepRamp pRamp = { 0 };
///
///   - Expectations:
///
/// \output     ramp1.ulCur   = 0u
/// \output     ramp1.ulTgt   = 0u
/// \output     ramp1.ulDelta = 0u
///
//-----------------------------------------------------------------------------
void  Mt_CtrlLed_AnimMa_PiecewiseLinear_InitRamp_TestCase3()
{
    //Step 1) Set pre-conditions,Assign Input values
    memcpy(&AnimMa_pCodingData->Animation.AnimationByteStream.aucByteStream[0], &Anima_CodPrj_PicewiseInit[0], sizeof(Anima_CodPrj_PicewiseInit[0]) / sizeof(uint8));    AnimMa_startSequence(2);
    uint8 Anima_PicewiseInit[ANIMMA_CODING_BYTES] = {
0x01, 0x01, 0x02, 0x00, 0x16, 0x02, 0x01, 0x09, 0x00, 0x0A, 0x00, 0x00, 0x28, 0x00, 0x0A, 0x0A, 0x02, 0x00, 0x04, 0x00, 0x32, 0x0A, 0x46, 0x14, 0x64, 0x28, 0x00
    };
    uint32 ulIdx    = 5u;
    tBlockSpecificPiecewiseLinear pCodSpc = {
        .ucDimUpInc = 10u,
        .ucDimDnDec = 20u,
        .ucInitI    = 30u,
        .ucN        = 8u,
        .ucByte0    = &Anima_PicewiseInit[0]
    };
    tStepRamp pRamp = { 0u };

    //Step 2) Call FUT
    AnimMa_PiecewiseLinear_InitRamp(ulIdx, &pCodSpc, &pRamp);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(pRamp.ulCur,   0u, == )
    AL_UNITTEST_CHECK(pRamp.ulTgt,   0u, == )
    AL_UNITTEST_CHECK(pRamp.ulDelta, 0u, == )
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_CtrlLed_AnimMa_PiecewiseLinear_InitRamp_Test4
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject: check the picewise linear block initialization when ulIdx is equal to pCodSpc->ucN
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input             Anima_PicewiseInit[ANIMMA_CODING_BYTES] = {0x00, 0x01, 0x02, 0x00, 0x16, 0x02, 0x01, 0x09, 0x00, 0x0A, 0x00, 0x00, 0x28, 0x00, 0x0A, 0x0A, 0x02, 0x00, 0x04, 0x00, 0x32, 0x0A, 0x46, 0x14, 0x64, 0x28, 0x00};
/// \input             uint32 ulIdx  = 2u;
/// \input             tBlockSpecificPiecewiseLinear pCodSpc = {
///                      .ucDimUpInc = 10u,
///                      .ucDimDnDec = 20u,
///                      .ucInitI    = 30u,
///                      .ucN        = 2u,
///                      .ucByte0    = &Anima_PicewiseInit[0]
///                  };
/// \input             tStepRamp pRamp = { 0 };
///
///   - Expectations:
///
/// \output     ramp1.ulCur   = 8192u
/// \output     ramp1.ulTgt   = 8192u
/// \output     ramp1.ulDelta = 0u
///
//-----------------------------------------------------------------------------
void  Mt_CtrlLed_AnimMa_PiecewiseLinear_InitRamp_TestCase4()
{
    //Step 1) Set pre-conditions,Assign Input values
    memcpy(&AnimMa_pCodingData->Animation.AnimationByteStream.aucByteStream[0], &Anima_CodPrj_PicewiseInit[0], sizeof(Anima_CodPrj_PicewiseInit[0]) / sizeof(uint8));    AnimMa_startSequence(2);
    uint8 Anima_PicewiseInit[ANIMMA_CODING_BYTES] = {
 0x00, 0x01, 0x02, 0x00, 0x16, 0x02, 0x01, 0x09, 0x00, 0x0A, 0x00, 0x00, 0x28, 0x00, 0x0A, 0x0A, 0x02, 0x00, 0x04, 0x00, 0x32, 0x0A, 0x46, 0x14, 0x64, 0x28, 0x00
    };
    uint32 ulIdx    = 2u;
    tBlockSpecificPiecewiseLinear pCodSpc = {
        .ucDimUpInc = 10u,
        .ucDimDnDec = 20u,
        .ucInitI    = 30u,
        .ucN        = 2u,
        .ucByte0    = &Anima_PicewiseInit[0]
    };
    tStepRamp pRamp = { 0u };

    //Step 2) Call FUT
    AnimMa_PiecewiseLinear_InitRamp(ulIdx, &pCodSpc, &pRamp);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(pRamp.ulCur,   8192u, == )
    AL_UNITTEST_CHECK(pRamp.ulTgt,   8192u, == )
    AL_UNITTEST_CHECK(pRamp.ulDelta, 0u, == )
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_PiecewiseLinear_InitRamp
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  check the set event status value
///
/// \Expected test results : All test cases contained are passed
///
//----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_PiecewiseLinear_InitRamp(void)
{
    Mt_CtrlLed_AnimMa_PiecewiseLinear_InitRamp_TestCase1();
    Mt_CtrlLed_AnimMa_PiecewiseLinear_InitRamp_TestCase2();
    Mt_CtrlLed_AnimMa_PiecewiseLinear_InitRamp_TestCase3();
    Mt_CtrlLed_AnimMa_PiecewiseLinear_InitRamp_TestCase4();
}

// ---------------------------------------------------------------------------- -
/// \Test Case : void  Mt_CtrlLed_AnimMa_AllocateBlocks()
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject: check the invalid block allocation
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input             AnimMa_unActiveBlocksCnt                     = 95u;
/// \input             AnimMa_AllocateBlocks_Param                  = 10u;
/// \input             Rte_Read_CodM_Anima_Para_Param1.eCodingState = eParaFct0_CodingDataValid;
///
///   - Expectations:
///
/// \output     AnimMa_AllocateBlocks_RetVal = ANIMMA_INVALID_BLOCK_IDX
///
//-----------------------------------------------------------------------------
void  Mt_CtrlLed_AnimMa_AllocateBlocks()
{
    //Step 1) Set pre-conditions,Assign Input values
    int i;
    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaC;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(AnimMa_CodPrj_aucDataset8_MoreThan60Blocks) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = AnimMa_CodPrj_aucDataset8_MoreThan60Blocks[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState = eParaFct0_CodingDataValid;
    AnimMa_unActiveBlocksCnt                     = 95u;
    AnimMa_AllocateBlocks_Param                  = 10u;

    //Step 2) Call FUT
    AnimMa_AllocateBlocks_RetVal = AnimMa_AllocateBlocks(AnimMa_AllocateBlocks_Param);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_AllocateBlocks_RetVal, ANIMMA_INVALID_BLOCK_IDX, == )
}

// ---------------------------------------------------------------------------- -
/// \Test Case : void  Mt_CtrlLed_Anima_roAnima_ParaFct0()
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject: check the coding alocation
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input       roAnima_ParaFct0_Param1 = eParaFct0_CodingDataInvalid;
/// \input       roAnima_ParaFct0_Param2 = &(Anima_CodPrj_aucAnimation1[0]);
///
///   - Expectations:
///
/// \output     AnimMa_pCodingData       = roAnima_ParaFct0_Param2
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_roAnima_ParaFct0()
{
    //Step 1) Set pre-conditions,Assign Input values
    roAnima_ParaFct0_Param1 = eParaFct0_CodingDataInvalid;
    roAnima_ParaFct0_Param2 = &(Anima_CodPrj_aucAnimation1[0]);

    //Step 2) Call FUT
    roAnima_ParaFct0(roAnima_ParaFct0_Param1, roAnima_ParaFct0_Param2);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_pCodingData, roAnima_ParaFct0_Param2, == )
}

// ---------------------------------------------------------------------------- -
/// \Test Case : void  Mt_CtrlLed_Anima_AnimMa_setCodingData()
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject: check the correct coding set
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input             pData_Param = &AnimaCodingAreaC;
///
///   - Expectations:
///
/// \output            AnimMa_pCodingData != NULL_PTR
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_setCodingData()
{
    //Step 1) Set pre-conditions,Assign Input values
    pData_Param = &AnimaCodingAreaC;

    //Step 2) Call FUT
    AnimMa_setCodingData(pData_Param);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_pCodingData, NULL_PTR, != )
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Cycle10_AnimaCPriorityNone_TA_NOMINAL
///
/// \Functional Safety: NA
///
/// \Test methods: Check animation do not start when electric state is not ok
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Test that animation request is not followed if electric state is TI NOMINAL
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input            Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input            Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input            Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;
/// \input            Rte_Read_SysMon_VehNetState_Param1.eSigQty                       = SIG_VALID;
/// \input            Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState         = eTA_NOMINAL;
///   - Expectations:
///
/// \output         Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_NONE
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_AnimaCPriorityNone_TA_NOMINAL(void)
{
    int i, j;
    //Step 1) Set pre-conditions,Assign Input values
    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaC;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset0_AnimaC) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset0_AnimaC[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;
    Rte_Read_SysMon_VehNetState_Param1.eSigQty                       = SIG_VALID;
    Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState         = eTA_NOMINAL;

    //Step 2) Call FUT
    Anima_Cycle10();

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Cycle10_AnimaCPriorityNone_TA_DEGRADE
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Test that animation request is not followed if electric state is TA DEGRADE
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input            Rte_Read_CodM_Anima_Para_Param1.eCodingState                      = eParaFct0_CodingDataValid;
/// \input            Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                      = SIG_VALID;
/// \input            Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl  = eExtLightingAnimationReq_WelcomeDay;
/// \input            Rte_Read_SysMon_VehNetState_Param1.eSigQty                        = SIG_VALID;
/// \input            Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState          = eTA_DEGRADE;
///   - Expectations:
///
/// \output         Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_NONE
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_AnimaCPriorityNone_TA_DEGRADE(void)
{
    int i, j;
    //Step 1) Set pre-conditions,Assign Input values
    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaC;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset0_AnimaC) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset0_AnimaC[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;
    Rte_Read_SysMon_VehNetState_Param1.eSigQty                       = SIG_VALID;
    Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState         = eTA_DEGRADE;

    //Step 2) Call FUT
    Anima_Cycle10();

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Cycle10_AnimaCPriorityNone_REDEMARRAGE
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
/// \Test Case Description
///    - Test subject:  Test that animation request is not followed if electric state is REDEMARRAGE
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input            Rte_Read_CodM_Anima_Para_Param1.eCodingState                      = eParaFct0_CodingDataValid;
/// \input            Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                      = SIG_VALID;
/// \input            Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl  = eExtLightingAnimationReq_WelcomeDay;
/// \input            Rte_Read_SysMon_VehNetState_Param1.eSigQty                        = SIG_VALID;
/// \input            Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState          = eREDEMARRAGE;
///   - Expectations:
///
/// \output         Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_NONE
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_AnimaCPriorityNone_REDEMARRAGE(void)
{
    int i, j;

    //Step 1) Set pre-conditions,Assign Input values
    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaC;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset0_AnimaC) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset0_AnimaC[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;
    Rte_Read_SysMon_VehNetState_Param1.eSigQty                       = SIG_VALID;
    Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState         = eREDEMARRAGE;

    //Step 2) Call FUT
    Anima_Cycle10();

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Cycle10_AnimaCPriorityNone_TI_DISPO_DEM
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Test that animation request is not followed if electric state is TI_DISPO_DEM
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input            Rte_Read_CodM_Anima_Para_Param1.eCodingState                      = eParaFct0_CodingDataValid;
/// \input            Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                      = SIG_VALID;
/// \input            Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl  = eExtLightingAnimationReq_WelcomeDay;
/// \input            Rte_Read_SysMon_VehNetState_Param1.eSigQty                        = SIG_VALID;
/// \input            Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState          = eTI_DISPO_DEM;
///   - Expectations:
///
/// \output         Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_NONE
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_AnimaCPriorityNone_TI_DISPO_DEM(void)
{
    int i, j;
    //Step 1) Set pre-conditions,Assign Input values
    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaC;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset0_AnimaC) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset0_AnimaC[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;
    Rte_Read_SysMon_VehNetState_Param1.eSigQty                       = SIG_VALID;
    Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState         = eTI_DISPO_DEM;

    //Step 2) Call FUT
    Anima_Cycle10();

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Cycle10_AnimaCPriorityNone_DEMARRAGE
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Test that animation request is not followed if electric state is DEMARRAGE
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input            Rte_Read_CodM_Anima_Para_Param1.eCodingState                      = eParaFct0_CodingDataValid;
/// \input            Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                      = SIG_VALID;
/// \input            Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl  = eExtLightingAnimationReq_WelcomeDay;
/// \input            Rte_Read_SysMon_VehNetState_Param1.eSigQty                        = SIG_VALID;
/// \input            Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState          = eDEMARRAGE;
///   - Expectations:
///
/// \output         Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_NONE
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_AnimaCPriorityNone_DEMARRAGE(void)
{
    int i, j;
    //Step 1) Set pre-conditions,Assign Input values
    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaC;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset0_AnimaC) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset0_AnimaC[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;
    Rte_Read_SysMon_VehNetState_Param1.eSigQty                       = SIG_VALID;
    Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState         = eDEMARRAGE;

    //Step 2) Call FUT
    Anima_Cycle10();

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Anima_RteAccess_ElectricNetworkState_TestCase1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Test that animation request is not followed if electric state is DEMARRAGE and signal valid
///    -                 Check that rte port is assigned correct
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input            Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl  = eExtLightingAnimationReq_WelcomeDay;
/// \input            Rte_Read_SysMon_VehNetState_Param1.eSigQty                        = SIG_VALID;
/// \input            Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState          = eDEMARRAGE;
///   - Expectations:
///
/// \output         Rte_Read_SysMon_VehNetState_RetVal                                  = eDEMARRAGE
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_RteAccess_ElectricNetworkState_TestCase1(void)
{
    //Step 1) Set pre-conditions,Assign Input values
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;
    Rte_Read_SysMon_VehNetState_Param1.eSigQty                       = SIG_VALID;
    Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState         = eDEMARRAGE;

    //Step 2) Call FUT
    Rte_Read_SysMon_VehNetState_RetVal = Anima_RteAccess_ElectricNetworkState();
    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_RetVal, eDEMARRAGE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Anima_RteAccess_ElectricNetworkState_TestCase2
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:   Test that animation request is not followed if electric state is DEMARRAGE and signal invalid
///    -                 Check that rte port is assigned correct
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input            Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl  = eExtLightingAnimationReq_WelcomeDay;
/// \input            Rte_Read_SysMon_VehNetState_Param1.eSigQty                        = SIG_INVALID;
/// \input            Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState          = eDEMARRAGE;
///   - Expectations:
///
/// \output           Rte_Read_SysMon_VehNetState_RetVal                                = eInvalid
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_RteAccess_ElectricNetworkState_TestCase2(void)
{
    //Step 1) Set pre-conditions,Assign Input values
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;
    Rte_Read_SysMon_VehNetState_Param1.eSigQty                       = SIG_INVALID;
    Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState         = eDEMARRAGE;

    //Step 2) Call FUT
    Rte_Read_SysMon_VehNetState_RetVal = Anima_RteAccess_ElectricNetworkState();

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_RetVal, eInvalid, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Cycle10_Etat_Anima
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check animation behavior in different cases for electric nw state
///
/// \Expected test results : All test cases contained are passed
///
//----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_Etat_Anima(void)
{
    Mt_CtrlLed_Cycle10_AnimaCPriorityNone_TA_NOMINAL();
    Mt_CtrlLed_Cycle10_AnimaCPriorityNone_TA_DEGRADE();
    Mt_CtrlLed_Cycle10_AnimaCPriorityNone_REDEMARRAGE();
    Mt_CtrlLed_Cycle10_AnimaCPriorityNone_TI_DISPO_DEM();
    Mt_CtrlLed_Cycle10_AnimaCPriorityNone_DEMARRAGE();
    Mt_CtrlLed_Anima_RteAccess_ElectricNetworkState_TestCase1();
    Mt_CtrlLed_Anima_RteAccess_ElectricNetworkState_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Cycle10_Dataset0_Dim
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that animation of dataset 0 is executed correctly.
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_ByeByeDay;
///
///   - Expectations:
///
/// \output         Anima_Tgt()->unTgtAni[j]   = aExpectedDim[i].aunHopt[j]
/// \output         Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_RUNNING
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_Dataset0_Dim(void)
{
    int i, j;
    //Step 1) Set pre-conditions,Assign Input values
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Start(" Mt_CtrlLed_Cycle10_Dataset1_Clamp.txt");
#endif

    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaDim;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset0_Dim) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset0_Dim[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;

    Mt_CtrlLed_PreTest();
    Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_ByeByeDay;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;

    for (i = 0; i < 120; i++)
    {    //Step 2) Call FUT
        Anima_Cycle10();
        for (j = 0; j < 10; j++)
        {
            //Step 3) Check expected output values
            AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], aExpectedDim[i].aunHopt[j], == );
        }
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_RUNNING, == );

        //Cfg logging
#if CFG_ENABLE_LOGGING == 1
        Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d } }\n", 10 * i
            , (int)Anima_Tgt()->unTgtAni[0]
            , (int)Anima_Tgt()->unTgtAni[1]
            , (int)Anima_Tgt()->unTgtAni[2]
            , (int)Anima_Tgt()->unTgtAni[3]
            , (int)Anima_Tgt()->unTgtAni[4]
            , (int)Anima_Tgt()->unTgtAni[5]
            , (int)Anima_Tgt()->unTgtAni[6]
            , (int)Anima_Tgt()->unTgtAni[7]
            , (int)Anima_Tgt()->unTgtAni[8]
            , (int)Anima_Tgt()->unTgtAni[9]
        );
#endif
    }
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_None;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    //Step 2) Call FUT
    Anima_Cycle10();

    for (j = 0; j < 10; j++)
    {
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], 0u, == );
    }
    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );

    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d } }\n", 10 * i
        , (int)Anima_Tgt()->unTgtAni[0]
        , (int)Anima_Tgt()->unTgtAni[1]
        , (int)Anima_Tgt()->unTgtAni[2]
        , (int)Anima_Tgt()->unTgtAni[3]
        , (int)Anima_Tgt()->unTgtAni[4]
        , (int)Anima_Tgt()->unTgtAni[5]
        , (int)Anima_Tgt()->unTgtAni[6]
        , (int)Anima_Tgt()->unTgtAni[7]
        , (int)Anima_Tgt()->unTgtAni[8]
        , (int)Anima_Tgt()->unTgtAni[9]
    );
#endif

#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Stop();
#endif
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Cycle10_Dataset0_Run
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that animation of dataset 1 is executed correctly.
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;
///
///   - Expectations:
///
/// \output         Anima_Tgt()->unTgtAni[j]   = aExpectedRun[i].aunHopt[j]
/// \output         Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_RUNNING
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_Dataset0_Run(void)
{
    int i, j;
    //Step 1) Set pre-conditions,Assign Input values
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Start(" Mt_CtrlLed_Cycle10_Dataset0_Run.txt");
#endif

    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaRun;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset0_Run) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset0_Run[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;

    Mt_CtrlLed_PreTest();
    Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;

    for (i = 0; i < 1000; i++)
    {
        //Step 2) Call FUT
        Anima_Cycle10();
        for (j = 0; j < 10; j++)
        {
            //Step 3) Check expected output values
            AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], aExpectedRun[i].aunHopt[j], == );
        }
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_RUNNING, == );

#if CFG_ENABLE_LOGGING == 1
        Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d } }\n", 10 * i
            , (int)Anima_Tgt()->unTgtAni[0]
            , (int)Anima_Tgt()->unTgtAni[1]
            , (int)Anima_Tgt()->unTgtAni[2]
            , (int)Anima_Tgt()->unTgtAni[3]
            , (int)Anima_Tgt()->unTgtAni[4]
            , (int)Anima_Tgt()->unTgtAni[5]
            , (int)Anima_Tgt()->unTgtAni[6]
            , (int)Anima_Tgt()->unTgtAni[7]
            , (int)Anima_Tgt()->unTgtAni[8]
            , (int)Anima_Tgt()->unTgtAni[9]
        );
#endif
    }
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_None;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    //Step 2) Call FUT
    Anima_Cycle10();

    for (j = 0; j < 10; j++)
    {
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], 0u, == );
    }
    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );

#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d } }\n", 10 * i
        , (int)Anima_Tgt()->unTgtAni[0]
        , (int)Anima_Tgt()->unTgtAni[1]
        , (int)Anima_Tgt()->unTgtAni[2]
        , (int)Anima_Tgt()->unTgtAni[3]
        , (int)Anima_Tgt()->unTgtAni[4]
        , (int)Anima_Tgt()->unTgtAni[5]
        , (int)Anima_Tgt()->unTgtAni[6]
        , (int)Anima_Tgt()->unTgtAni[7]
        , (int)Anima_Tgt()->unTgtAni[8]
        , (int)Anima_Tgt()->unTgtAni[9]
    );
#endif

#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Stop();
#endif
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Cycle10_Dataset1_Flex
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that animation of dataset 1 is executed correctly.
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeNight;
///
///   - Expectations:
///
/// \output         Anima_Tgt()->unTgtAni[j]    = aExpectedFlex[i].aunHopt[j]
/// \output         Anima_TgtAniArr.boPriority  = PRIORITY_ANIMATION_RUNNING
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_Dataset1_Flex(void)
{
    int i, j;
    //Step 1) Set pre-conditions,Assign Input values
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Start(" Mt_CtrlLed_Cycle10_Dataset1_Flex.txt");
#endif

    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaFlex;
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset1_Flex) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset1_Flex[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
    Mt_CtrlLed_PreTest();
    Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeNight;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;

    for (i = 0; i < 200; i++)
    {
        //Step 2) Call FUT
        Anima_Cycle10();
        for (j = 0; j < 10; j++)
        {
            //Step 3) Check expected output values
            AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], aExpectedFlex[i].aunHopt[j], == );
        }
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_RUNNING, == );

        //Cfg logging
#if CFG_ENABLE_LOGGING == 1
        Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d } }\n", 10 * i
            , (int)Anima_Tgt()->unTgtAni[0]
            , (int)Anima_Tgt()->unTgtAni[1]
            , (int)Anima_Tgt()->unTgtAni[2]
            , (int)Anima_Tgt()->unTgtAni[3]
            , (int)Anima_Tgt()->unTgtAni[4]
            , (int)Anima_Tgt()->unTgtAni[5]
            , (int)Anima_Tgt()->unTgtAni[6]
            , (int)Anima_Tgt()->unTgtAni[7]
            , (int)Anima_Tgt()->unTgtAni[8]
            , (int)Anima_Tgt()->unTgtAni[9]
        );
#endif
    }

    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_None;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    //Step 2) Call FUT
    Anima_Cycle10();

    for (j = 0; j < 10; j++)
    {
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], 0u, == );
    }
    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );

    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d } }\n", 10 * i
        , (int)Anima_Tgt()->unTgtAni[0]
        , (int)Anima_Tgt()->unTgtAni[1]
        , (int)Anima_Tgt()->unTgtAni[2]
        , (int)Anima_Tgt()->unTgtAni[3]
        , (int)Anima_Tgt()->unTgtAni[4]
        , (int)Anima_Tgt()->unTgtAni[5]
        , (int)Anima_Tgt()->unTgtAni[6]
        , (int)Anima_Tgt()->unTgtAni[7]
        , (int)Anima_Tgt()->unTgtAni[8]
        , (int)Anima_Tgt()->unTgtAni[9]
    );
#endif

#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Stop();
#endif
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_rcAnimMa50_Dataset2_Flex
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that animation of dataset 2 is executed correctly.
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_None;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input           AnimMa_aActiveSeq[0].unStopBlocks                                = 0u;
/// \input           AnimMa_aActiveSeq[0].unSeqStatus                                 = 2u;
/// \input           AnimMa_aActiveSeq[0].unSeqStatus                                 = 3u;
///
///   - Expectations:
///
/// \output         Anima_Tgt()->unTgtAni[j]     = 0u
/// \output         Anima_TgtAniArr.boPriority   = PRIORITY_ANIMATION_NONE
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_rcAnimMa50_Dataset2_Flex(void)
{
    int i, j;
    //Step 1) Set pre-conditions,Assign Input values

    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaFlex;
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset2_Flex) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset2_Flex[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;

    Mt_CtrlLed_PreTest();
    Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_None;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    AnimMa_startSequence(0);

    AnimMa_aActiveSeq[0].unStopBlocks = 0u;
    AnimMa_aActiveSeq[0].unSeqStatus  = 2u;
    //Step 2) Call FUT
    rcAnimMa50();
    AnimMa_aActiveSeq[0].unSeqStatus  = 3u;

    for (j = 0; j < 10; j++)
    {
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], 0u, == );
    }
    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_rcBlockFlex_TestCase1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that animation of dataset 2 isnot executed if rcBlock Flex parameters are not valid.
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           Rte_Read_CodM_Anima_Para_Param1.eCodingState                                         = eParaFct0_CodingDataValid;
/// \input           Rte_Read_IoHwAbUser_GetMountingSide_Param1                                           = eMountedLeft;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl                     = eExtLightingAnimationReq_WelcomeNight;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                                         = SIG_VALID;
/// \input           ulActiveBlkId                                                                        = 9u;
/// \input           ulTime                                                                               = 0u;
/// \input           AnimMa_aActiveBlocks[ulActiveBlkId].ucBlkCtxIdx                                      = 2u;
/// \input           AnimMa_aActiveBlocksFlex[AnimMa_aActiveBlocks[ulActiveBlkId].ucBlkCtxIdx].ulNextTime = 500u;
/// \input           AnimMa_unActiveBlocksFlexCnt                                                         = 1u;
///
///   - Expectations:
///
/// \output         Anima_Tgt()->unTgtAni[j] = 0u;
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_rcBlockFlex_TestCase1(void)
{
    int i, j;
    uint32 ulActiveBlkId;
    uint32 ulTime;
    //Step 1) Set pre-conditions,Assign Input values

    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaFlex;
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset1_Flex) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset1_Flex[i];
    }

    Rte_Read_CodM_Anima_Para_Param1.eCodingState                                         = eParaFct0_CodingDataValid;
    Rte_Read_IoHwAbUser_GetMountingSide_Param1                                           = eMountedLeft;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl                     = eExtLightingAnimationReq_WelcomeNight;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                                         = SIG_VALID;
    ulActiveBlkId                                                                        = 9u;
    ulTime                                                                               = 0u;
    AnimMa_aActiveBlocks[ulActiveBlkId].ucBlkCtxIdx                                      = 2u;
    AnimMa_aActiveBlocksFlex[AnimMa_aActiveBlocks[ulActiveBlkId].ucBlkCtxIdx].ulNextTime = 500u;
    AnimMa_unActiveBlocksFlexCnt                                                         = 1u;

    //Step 2) Call FUT
    AnimMa_rcBlockFlex(ulActiveBlkId, ulTime);

    for (i = 0; i < 200; i++)
    {
        for (j = 0; j < 10; j++)
        {
            //Step 3) Check expected output values
            AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], 0u, == );
        }
    }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_rcBlockFlex_TestCase2
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that animation of dataset 2 isnot executed if rcBlock Flex parameters are not valid.
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input          Rte_Read_CodM_Anima_Para_Param1.eCodingState                                         = eParaFct0_CodingDataValid;
/// \input          Rte_Read_IoHwAbUser_GetMountingSide_Param1                                           = eMountedLeft;
/// \input          Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl                     = eExtLightingAnimationReq_WelcomeNight;
/// \input          Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                                         = SIG_VALID;
/// \input          ulActiveBlkId                                                                        = 9u;
/// \input          ulTime                                                                               = 0u;
/// \input          AnimMa_aActiveBlocks[ulActiveBlkId].ucBlkCtxIdx                                      = 2u;
/// \input          AnimMa_aActiveBlocksFlex[AnimMa_aActiveBlocks[ulActiveBlkId].ucBlkCtxIdx].ulNextTime = 500u;
/// \input          AnimMa_unActiveBlocksFlexCnt                                                         = 3u;
///
///   - Expectations:
///
/// \output         Anima_Tgt()->unTgtAni[j] = 0u;
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_rcBlockFlex_TestCase2(void)
{
    int i, j;
    uint32 ulActiveBlkId;
    uint32 ulTime;
    //Step 1) Set pre-conditions,Assign Input values

    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaFlex;
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset1_Flex) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset1_Flex[i];
    }

    Rte_Read_CodM_Anima_Para_Param1.eCodingState                                         = eParaFct0_CodingDataValid;
    Rte_Read_IoHwAbUser_GetMountingSide_Param1                                           = eMountedLeft;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl                     = eExtLightingAnimationReq_WelcomeNight;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                                         = SIG_VALID;
    ulActiveBlkId                                                                        = 9u;
    ulTime                                                                               = 0u;
    AnimMa_aActiveBlocks[ulActiveBlkId].ucBlkCtxIdx                                      = 2u;
    AnimMa_aActiveBlocksFlex[AnimMa_aActiveBlocks[ulActiveBlkId].ucBlkCtxIdx].ulNextTime = 500u;
    AnimMa_unActiveBlocksFlexCnt                                                         = 3u;

    //Step 2) Call FUT
    AnimMa_rcBlockFlex(ulActiveBlkId, ulTime);

    for (i = 0; i < 200; i++)
    {
        for (j = 0; j < 10; j++)
        {
            //Step 3) Check expected output values
            AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], 0u, == );
        }
    }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Cycle10_Dataset0_Blink
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that animation of dataset 1 is executed correctly.
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input               Rte_Read_CodM_Anima_Para_Param1.eCodingState                    = eParaFct0_CodingDataValid;
/// \input               Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
/// \input               Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_ByeByeNight;
/// \input               Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
///
///   - Expectations:
///
/// \output              Anima_Tgt()->unTgtAni[j]   = aExpectedBlink[i].aunHopt[j]
/// \output              Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_RUNNING
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_Dataset0_Blink(void)
{
    int i, j;
    //Step 1) Set pre-conditions,Assign Input values
    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Start(" Mt_CtrlLed_Cycle10_Dataset0_Blink.txt");
#endif

    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaBlink;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset0_Blink) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset0_Blink[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
    Mt_CtrlLed_PreTest();
    Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_ByeByeNight;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;

    //1000 iterations for the total time set on run block : t =2s
    for (i = 0; i < 300; i++)
    {    //Step 2) Call FUT
        Anima_Cycle10();
        for (j = 0; j < 10; j++)//number of pixels
        {
            //Step 3) Check expected output values
            AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], aExpectedBlink[i].aunHopt[j], == );
        }
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_RUNNING, == );

        //Cfg logging
#if CFG_ENABLE_LOGGING == 1
        Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d } }\n", 10 * i
            , (int)Anima_Tgt()->unTgtAni[0]
            , (int)Anima_Tgt()->unTgtAni[1]
            , (int)Anima_Tgt()->unTgtAni[2]
            , (int)Anima_Tgt()->unTgtAni[3]
            , (int)Anima_Tgt()->unTgtAni[4]
            , (int)Anima_Tgt()->unTgtAni[5]
            , (int)Anima_Tgt()->unTgtAni[6]
            , (int)Anima_Tgt()->unTgtAni[7]
            , (int)Anima_Tgt()->unTgtAni[8]
            , (int)Anima_Tgt()->unTgtAni[9]
        );
#endif
    }

    //stop previus animation
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_None;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    //Step 2) Call FUT
    Anima_Cycle10();

    for (j = 0; j < 10; j++)
    {
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], 0u, == );
    }
    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );

    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d } }\n", 10 * i
        , (int)Anima_Tgt()->unTgtAni[0]
        , (int)Anima_Tgt()->unTgtAni[1]
        , (int)Anima_Tgt()->unTgtAni[2]
        , (int)Anima_Tgt()->unTgtAni[3]
        , (int)Anima_Tgt()->unTgtAni[4]
        , (int)Anima_Tgt()->unTgtAni[5]
        , (int)Anima_Tgt()->unTgtAni[6]
        , (int)Anima_Tgt()->unTgtAni[7]
        , (int)Anima_Tgt()->unTgtAni[8]
        , (int)Anima_Tgt()->unTgtAni[9]
    );
#endif

#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Stop();
#endif
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_rcBlock_TestCase1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that flag is correctly updated for a generic block and mounting side left
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input               Rte_Read_CodM_Anima_Para_Param1.eCodingState          = eParaFct0_CodingDataValid;
/// \input               ulActiveBlkId                                         = 9u;
/// \input               ulTime                                                = 0u;
/// \input               ucMountingSide                                        = 1u;
/// \input               AnimMa_aActiveBlocks[ulActiveBlkId].unGenParamCodIdx  = 7u;
///
///   - Expectations:
///
/// \output         AnimMa_Cod_GetBlockGenericBlkGenIdx(AnimMa_aActiveBlocks[ulActiveBlkId].unGenParamCodIdx)->ucFlags = 4u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_rcBlock_TestCase1(void)
{
    int i, j;
    uint32 ulActiveBlkId;
    uint32 ulTime;
    uint8 ucMountingSide;
    //Step 1) Set pre-conditions,Assign Input values
    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaBlink;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset0_Blink2) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset0_Blink2[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState          = eParaFct0_CodingDataValid;
    ulActiveBlkId                                         = 9u;
    ulTime                                                = 0u;
    ucMountingSide                                        = 1u;
    AnimMa_aActiveBlocks[ulActiveBlkId].unGenParamCodIdx  = 7u;

    //Step 2) Call FUT
    AnimMa_rcBlock(ulActiveBlkId, ulTime, ucMountingSide);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_Cod_GetBlockGenericBlkGenIdx(AnimMa_aActiveBlocks[ulActiveBlkId].unGenParamCodIdx)->ucFlags, 4u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_rcBlock_TestCase2
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that flag is correctly updated for a generic block and mounting side left
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input              Rte_Read_CodM_Anima_Para_Param1.eCodingState         = eParaFct0_CodingDataValid;
/// \input              ulActiveBlkId                                        = 9u;
/// \input              ulTime                                               = 0u;
/// \input              ucMountingSide                                       = 2u;
/// \input              AnimMa_aActiveBlocks[ulActiveBlkId].unGenParamCodIdx = 7u;
///
///   - Expectations:
///
/// \output         AnimMa_Cod_GetBlockGenericBlkGenIdx(AnimMa_aActiveBlocks[ulActiveBlkId].unGenParamCodIdx)->ucFlags = 2u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_rcBlock_TestCase2(void)
{
    int i, j;
    uint32 ulActiveBlkId;
    uint32 ulTime;
    uint8 ucMountingSide;
    //Step 1) Set pre-conditions,Assign Input values
    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaBlink;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset0_Blink3) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset0_Blink3[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState         = eParaFct0_CodingDataValid;
    ulActiveBlkId                                        = 9u;
    ulTime                                               = 0u;
    ucMountingSide                                       = 2u;
    AnimMa_aActiveBlocks[ulActiveBlkId].unGenParamCodIdx = 7u;

    //Step 2) Call FUT
    AnimMa_rcBlock(ulActiveBlkId, ulTime, ucMountingSide);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_Cod_GetBlockGenericBlkGenIdx(AnimMa_aActiveBlocks[ulActiveBlkId].unGenParamCodIdx)->ucFlags, 2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Cycle10_LFSR_XOR
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that animation LSFR XOR block is runned correctly
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_UnlockDay;
///
///   - Expectations:
///
/// \output         Anima_Tgt()->unTgtAni[j]   = aExpectedLFSRXOR[i].aunHopt[j]
/// \output         Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_RUNNING
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_LFSR_XOR(void)
{
    int i, j;
    //Step 1) Set pre-conditions,Assign Input values
  //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Start(" Mt_CtrlLed_Cycle10_LFSR_XOR.txt");
#endif

    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaLFSR_XOR;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucLFSR_XOR) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucLFSR_XOR[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
    Mt_CtrlLed_PreTest();
    Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_UnlockDay;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;

    for (i = 0; i < 200; i++)
    {
        //Step 2) Call FUT
        Anima_Cycle10();
        for (j = 0; j < 10; j++)
        {

            //Step 3) Check expected output values
            AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], aExpectedLFSRXOR[i].aunHopt[j], == );
        }
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_RUNNING, == );

        //Cfg logging
#if CFG_ENABLE_LOGGING == 1
        Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d, } }\n", 10 * i
            , (int)Anima_Tgt()->unTgtAni[0]
            , (int)Anima_Tgt()->unTgtAni[1]
            , (int)Anima_Tgt()->unTgtAni[2]
            , (int)Anima_Tgt()->unTgtAni[3]
            , (int)Anima_Tgt()->unTgtAni[4]
            , (int)Anima_Tgt()->unTgtAni[5]
            , (int)Anima_Tgt()->unTgtAni[6]
            , (int)Anima_Tgt()->unTgtAni[7]
            , (int)Anima_Tgt()->unTgtAni[8]
            , (int)Anima_Tgt()->unTgtAni[9]
        );
#endif
    }

    //stop previus animation
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_None;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    //Step 2) Call FUT
    Anima_Cycle10();

    for (j = 0; j < 10; j++)
    {
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], 0u, == );
    }
    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );

    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d } }\n", 10 * i
        , (int)Anima_Tgt()->unTgtAni[0]
        , (int)Anima_Tgt()->unTgtAni[1]
        , (int)Anima_Tgt()->unTgtAni[2]
        , (int)Anima_Tgt()->unTgtAni[3]
        , (int)Anima_Tgt()->unTgtAni[4]
        , (int)Anima_Tgt()->unTgtAni[5]
        , (int)Anima_Tgt()->unTgtAni[6]
        , (int)Anima_Tgt()->unTgtAni[7]
        , (int)Anima_Tgt()->unTgtAni[8]
        , (int)Anima_Tgt()->unTgtAni[9]
    );
#endif

#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Stop();
#endif
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Anima_AnimMa_rcBlockSparkleLfsr
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that animation LSFR XOR block is runned correctly
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           Rte_Read_CodM_Anima_Para_Param1.eCodingState                                              = eParaFct0_CodingDataValid;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl                          = eExtLightingAnimationReq_UnlockDay;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                                              = SIG_VALID;
/// \input           ulActiveBlkId                                                                             = 9u;
/// \input           ulTime                                                                                    = 50u;
/// \input           AnimMa_aActiveBlocks[ulActiveBlkId].ucBlkCtxIdx                                           = 0u;
/// \input           AnimMa_unActiveBlocksSparkleLfsrCnt                                                       = 1u;
/// \input           AnimMa_aActiveBlocksSparkleLfsr[AnimMa_aActiveBlocks[ulActiveBlkId].ucBlkCtxIdx].ucReg[0] = 0u;
///
///   - Expectations:
///
/// \output         Anima_TgtAniArr.boPriority = 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_rcBlockSparkleLfsr(void)
{
    uint32 ulActiveBlkId;
    uint32 ulTime;

    //Step 1) Set pre-conditions,Assign Input values
    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaLFSR_XOR;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucLFSR_XOR) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucLFSR_XOR[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                                              = eParaFct0_CodingDataValid;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl                          = eExtLightingAnimationReq_UnlockDay;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                                              = SIG_VALID;
    ulActiveBlkId                                                                             = 9u;
    ulTime                                                                                    = 50u;
    AnimMa_aActiveBlocks[ulActiveBlkId].ucBlkCtxIdx                                           = 0u;
    AnimMa_unActiveBlocksSparkleLfsrCnt                                                       = 1u;
    AnimMa_aActiveBlocksSparkleLfsr[AnimMa_aActiveBlocks[ulActiveBlkId].ucBlkCtxIdx].ucReg[0] = 0u;

    //Step 2) Call FUT
    AnimMa_rcBlockSparkleLfsr(ulActiveBlkId, ulTime);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Anima_AnimMa_rcBlockBlink
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that for blink block,if plauible check is passed,the target intensity is not 0
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input           AnimMa_unActiveBlocksCnt                                         = 18u;
/// \input           AnimMa_ucActiveSeqCnt                                            = 2u;
/// \input           ulActiveBlkId                                                    = 26u;
/// \input           ulTime                                                           = 0u;
///
///   - Expectations:
///
/// \output         AnimMaRamp_aucPxlIntTgt !=  0u;
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_rcBlockBlink(void)
{
    int i, j;
    uint32 ulActiveBlkId;
    uint32 ulTime;
    //Step 1) Set pre-conditions,Assign Input values
    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaBlink;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset0_BlinkPhase) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset0_BlinkPhase[i];
    }

    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    AnimMa_unActiveBlocksCnt                                         = 18u;
    AnimMa_ucActiveSeqCnt                                            = 2u;
    ulActiveBlkId                                                    = 26u;
    ulTime                                                           = 0u;

    //Step 2) Call FUT
    AnimMa_rcBlockBlink(ulActiveBlkId, ulTime);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMaRamp_aucPxlIntTgt, 0u, != );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Anima_AnimMa_rcBlockInvert
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that for invert block,if start time is equal to end time,the target intensity is not 0
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input            Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input            Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;
/// \input            Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input            AnimMa_unActiveBlocksCnt                                         = 18u;
/// \input            AnimMa_ucActiveSeqCnt                                            = 2u;
/// \input            ulActiveBlkId                                                    = 25u;
/// \input            ulTime                                                           = 0u;
///
///   - Expectations:
///
/// \output         AnimMaRamp_aucPxlIntTgt !=  0u;
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_rcBlockInvert(void)
{
    int i, j;
    uint32 ulActiveBlkId;
    uint32 ulTime;
    //Step 1) Set pre-conditions,Assign Input values
    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaBlink;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset0_BlinkPhase) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset0_BlinkPhase[i];
    }

    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    AnimMa_unActiveBlocksCnt                                         = 18u;
    AnimMa_ucActiveSeqCnt                                            = 2u;
    ulActiveBlkId                                                    = 25u;
    ulTime                                                           = 0u;

    //Step 2) Call FUT
    AnimMa_rcBlockInvert(ulActiveBlkId, ulTime);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMaRamp_aucPxlIntTgt, 0u, != );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Cycle10_BlocksCheck
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check different blocks implemented in anima tool
///
/// \Expected test results : All test cases contained are passed
///
//----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_BlocksCheck(void)
{
    Mt_CtrlLed_rcAnimMa50_Dataset2_Flex();
    Mt_CtrlLed_Cycle10_LFSR_XOR();
    Mt_CtrlLed_Cycle10_Dataset0_Blink();
    Mt_CtrlLed_Anima_AnimMa_rcBlockBlink();
    Mt_CtrlLed_Anima_AnimMa_rcBlockInvert();
    Mt_CtrlLed_AnimMa_rcBlock_TestCase1();
    Mt_CtrlLed_AnimMa_rcBlock_TestCase2();
    Mt_CtrlLed_Cycle10_Dataset0_Dim();
    Mt_CtrlLed_Cycle10_Dataset1_Flex();
    Mt_CtrlLed_AnimMa_rcBlockFlex_TestCase1();
    Mt_CtrlLed_AnimMa_rcBlockFlex_TestCase2();
    Mt_CtrlLed_Cycle10_Dataset0_Run();
    Mt_CtrlLed_AnimMa_rcBlockSparkleXor64();
    Mt_CtrlLed_Anima_AnimMa_rcBlockSparkleLfsr();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Cycle10_Dataset0_WelcomeDay
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that animation WelcomeDay is executed correctly.
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;
///
///   - Expectations:
///
/// \output         Anima_Tgt()->unTgtAni[j]   = aExpected[i].aunHopt[j]
/// \output         Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_RUNNING
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_Dataset0_WelcomeDay(void)
{
    int i, j;
    //Step 1) Set pre-conditions,Assign Input values
   //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Start(" Mt_CtrlLed_Cycle10_WelcomeDay.txt");
#endif
    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaWelcomeDayNight;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset0_Welcome) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset0_Welcome[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
    Mt_CtrlLed_PreTest();
    Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;

    for (i = 0; i < 3000; i++)
    {
        //Step 2) Call FUT
        Anima_Cycle10();
        for (j = 0; j < 27; j++)//number of pixels
        {
            //Step 3) Check expected output values
            AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], aExpected[i].aunHopt[j], == );
        }
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_RUNNING, == );

        //Cfg logging
#if CFG_ENABLE_LOGGING == 1
        Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
            , (int)Anima_Tgt()->unTgtAni[0]
            , (int)Anima_Tgt()->unTgtAni[1]
            , (int)Anima_Tgt()->unTgtAni[2]
            , (int)Anima_Tgt()->unTgtAni[3]
            , (int)Anima_Tgt()->unTgtAni[4]
            , (int)Anima_Tgt()->unTgtAni[5]
            , (int)Anima_Tgt()->unTgtAni[6]
            , (int)Anima_Tgt()->unTgtAni[7]
            , (int)Anima_Tgt()->unTgtAni[8]
            , (int)Anima_Tgt()->unTgtAni[9]
            , (int)Anima_Tgt()->unTgtAni[10]
            , (int)Anima_Tgt()->unTgtAni[11]
            , (int)Anima_Tgt()->unTgtAni[12]
            , (int)Anima_Tgt()->unTgtAni[13]
            , (int)Anima_Tgt()->unTgtAni[14]
            , (int)Anima_Tgt()->unTgtAni[15]
            , (int)Anima_Tgt()->unTgtAni[16]
            , (int)Anima_Tgt()->unTgtAni[17]
            , (int)Anima_Tgt()->unTgtAni[18]
            , (int)Anima_Tgt()->unTgtAni[19]
            , (int)Anima_Tgt()->unTgtAni[20]
            , (int)Anima_Tgt()->unTgtAni[21]
            , (int)Anima_Tgt()->unTgtAni[22]
            , (int)Anima_Tgt()->unTgtAni[23]
            , (int)Anima_Tgt()->unTgtAni[24]
            , (int)Anima_Tgt()->unTgtAni[25]
            , (int)Anima_Tgt()->unTgtAni[26]
        );
#endif
    }

    //stop previus animation
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_None;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    //Step 2) Call FUT
    Anima_Cycle10();

    for (j = 0; j < 27; j++)
    {
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], 0u, == );
    }
    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );

    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
        , (int)Anima_Tgt()->unTgtAni[0]
        , (int)Anima_Tgt()->unTgtAni[1]
        , (int)Anima_Tgt()->unTgtAni[2]
        , (int)Anima_Tgt()->unTgtAni[3]
        , (int)Anima_Tgt()->unTgtAni[4]
        , (int)Anima_Tgt()->unTgtAni[5]
        , (int)Anima_Tgt()->unTgtAni[6]
        , (int)Anima_Tgt()->unTgtAni[7]
        , (int)Anima_Tgt()->unTgtAni[8]
        , (int)Anima_Tgt()->unTgtAni[9]
        , (int)Anima_Tgt()->unTgtAni[10]
        , (int)Anima_Tgt()->unTgtAni[11]
        , (int)Anima_Tgt()->unTgtAni[12]
        , (int)Anima_Tgt()->unTgtAni[13]
        , (int)Anima_Tgt()->unTgtAni[14]
        , (int)Anima_Tgt()->unTgtAni[15]
        , (int)Anima_Tgt()->unTgtAni[16]
        , (int)Anima_Tgt()->unTgtAni[17]
        , (int)Anima_Tgt()->unTgtAni[18]
        , (int)Anima_Tgt()->unTgtAni[19]
        , (int)Anima_Tgt()->unTgtAni[20]
        , (int)Anima_Tgt()->unTgtAni[21]
        , (int)Anima_Tgt()->unTgtAni[22]
        , (int)Anima_Tgt()->unTgtAni[23]
        , (int)Anima_Tgt()->unTgtAni[24]
        , (int)Anima_Tgt()->unTgtAni[25]
        , (int)Anima_Tgt()->unTgtAni[26]
    );
#endif

#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Stop();
#endif
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Cycle10_Dataset0_WelcomeNight
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that animation WelcomeNight is executed correctly.
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeNight;
///
///   - Expectations:
///
/// \output         Anima_Tgt()->unTgtAni[j]                                 = aExpected[i].aunHopt[j]
/// \output         Anima_TgtAniArr.boPriority                               = 0u
/// \output         Rte_Write_AnimaScrollingActivation_Param1.unTgtAniScr[1] = aExpected[i].aunHopt[27]
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_Dataset0_WelcomeNight(void)
{
    int i, j;
    //Step 1) Set pre-conditions,Assign Input values
    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Start(" Mt_CtrlLed_Cycle10_WelcomeNight.txt");
#endif
    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaWelcomeDayNight;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset0_Welcome) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset0_Welcome[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
    Mt_CtrlLed_PreTest();
    Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeNight;

    for (i = 0; i < 3000; i++)
    {
        //Step 2) Call FUT
        Anima_Cycle10();
        for (j = 0U; j < 28; j++)//number of pixels
        {
            //Step 3) Check expected output values
            AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j],                                        aExpected[i].aunHopt[j], == );
            AL_UNITTEST_CHECK((uint32)Rte_Write_AnimaScrollingActivation_Param1.boPriorityScr, 0u, == );
            AL_UNITTEST_CHECK((uint32)Rte_Write_AnimaScrollingActivation_Param1.unTgtAniScr[1], aExpected[i].aunHopt[27], == );

        }
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_RUNNING, == );

        //Cfg logging
#if CFG_ENABLE_LOGGING == 1
        Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d , %5d } }\n", 10 * i
            , (int)Anima_Tgt()->unTgtAni[0]
            , (int)Anima_Tgt()->unTgtAni[1]
            , (int)Anima_Tgt()->unTgtAni[2]
            , (int)Anima_Tgt()->unTgtAni[3]
            , (int)Anima_Tgt()->unTgtAni[4]
            , (int)Anima_Tgt()->unTgtAni[5]
            , (int)Anima_Tgt()->unTgtAni[6]
            , (int)Anima_Tgt()->unTgtAni[7]
            , (int)Anima_Tgt()->unTgtAni[8]
            , (int)Anima_Tgt()->unTgtAni[9]
            , (int)Anima_Tgt()->unTgtAni[10]
            , (int)Anima_Tgt()->unTgtAni[11]
            , (int)Anima_Tgt()->unTgtAni[12]
            , (int)Anima_Tgt()->unTgtAni[13]
            , (int)Anima_Tgt()->unTgtAni[14]
            , (int)Anima_Tgt()->unTgtAni[15]
            , (int)Anima_Tgt()->unTgtAni[16]
            , (int)Anima_Tgt()->unTgtAni[17]
            , (int)Anima_Tgt()->unTgtAni[18]
            , (int)Anima_Tgt()->unTgtAni[19]
            , (int)Anima_Tgt()->unTgtAni[20]
            , (int)Anima_Tgt()->unTgtAni[21]
            , (int)Anima_Tgt()->unTgtAni[22]
            , (int)Anima_Tgt()->unTgtAni[23]
            , (int)Anima_Tgt()->unTgtAni[24]
            , (int)Anima_Tgt()->unTgtAni[25]
            , (int)Anima_Tgt()->unTgtAni[26]
            , (int)Anima_Tgt()->unTgtAni[27]
        );
#endif
    }

    //stop previus animation
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_None;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    //Step 2) Call FUT
    Anima_Cycle10();

    for (j = 0; j < 28; j++)
    {
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], 0u, == );
    }
    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );

    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
        , (int)Anima_Tgt()->unTgtAni[0]
        , (int)Anima_Tgt()->unTgtAni[1]
        , (int)Anima_Tgt()->unTgtAni[2]
        , (int)Anima_Tgt()->unTgtAni[3]
        , (int)Anima_Tgt()->unTgtAni[4]
        , (int)Anima_Tgt()->unTgtAni[5]
        , (int)Anima_Tgt()->unTgtAni[6]
        , (int)Anima_Tgt()->unTgtAni[7]
        , (int)Anima_Tgt()->unTgtAni[8]
        , (int)Anima_Tgt()->unTgtAni[9]
        , (int)Anima_Tgt()->unTgtAni[10]
        , (int)Anima_Tgt()->unTgtAni[11]
        , (int)Anima_Tgt()->unTgtAni[12]
        , (int)Anima_Tgt()->unTgtAni[13]
        , (int)Anima_Tgt()->unTgtAni[14]
        , (int)Anima_Tgt()->unTgtAni[15]
        , (int)Anima_Tgt()->unTgtAni[16]
        , (int)Anima_Tgt()->unTgtAni[17]
        , (int)Anima_Tgt()->unTgtAni[18]
        , (int)Anima_Tgt()->unTgtAni[19]
        , (int)Anima_Tgt()->unTgtAni[20]
        , (int)Anima_Tgt()->unTgtAni[21]
        , (int)Anima_Tgt()->unTgtAni[22]
        , (int)Anima_Tgt()->unTgtAni[23]
        , (int)Anima_Tgt()->unTgtAni[24]
        , (int)Anima_Tgt()->unTgtAni[25]
        , (int)Anima_Tgt()->unTgtAni[26]
        , (int)Anima_Tgt()->unTgtAni[27]

    );
#endif

#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Stop();
#endif
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Cycle10_Dataset0_TIScr
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that TI Scrolling can be activated 
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input           Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;
///
///   - Expectations:
///
/// \output         Anima_Tgt()->unTgtAni[j]                                          = aExpectedScr[i].aunHopt[j]
/// \output         Rte_Write_AnimaScrollingActivation_Param1.boPriorityScr           = 0u
/// \output         Rte_Write_AnimaScrollingActivation_Param1.unTgtAniScr[1]          = aExpected[i].aunHopt[27]
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_Dataset0_TIScr(void)
{
    int i, j;
    //Step 1) Set pre-conditions,Assign Input values

    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaWelcomeDayNight;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(AnimMa_CodPrj_aucDataset_TIScr) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = AnimMa_CodPrj_aucDataset_TIScr[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
    Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;

    for (i = 0; i < 3000; i++)
    {
        //Step 2) Call FUT
        Anima_Cycle10();
        for (j = 0U; j < 28; j++)//number of pixels
        {
            //Step 3) Check expected output values
            AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j],                                         aExpectedScr[i].aunHopt[j], == );
            AL_UNITTEST_CHECK((uint32)Rte_Write_AnimaScrollingActivation_Param1.boPriorityScr,  0u, == );
            AL_UNITTEST_CHECK((uint32)Rte_Write_AnimaScrollingActivation_Param1.unTgtAniScr[1], aExpected[i].aunHopt[27], == );
        }
    }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Cycle10_Dataset0_UnlockDayExt
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that animation UnlockDayExt is executed correctly.
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_UnlockDayExt;
///
///   - Expectations:
///
/// \output         Anima_Tgt()->unTgtAni[j]   = aExpectedUnlockExt[i].aunHopt[j]
/// \output         Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_RUNNING
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_Dataset0_UnlockDayExt(void)
{
    int i, j;
    //Step 1) Set pre-conditions,Assign Input values
   //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Start(" Mt_CtrlLed_Cycle10_UnlockDayExt.txt");
#endif
    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaUnlockDayNightExt;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_UnlockDayNightExt) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_UnlockDayNightExt[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
    Mt_CtrlLed_PreTest();
    Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_UnlockDayExtension;

    for (i = 0; i < 3000; i++)
    {
        //Step 2) Call FUT
        Anima_Cycle10();
        for (j = 0; j < 27; j++)
        {
            //Step 3) Check expected output values
            AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], aExpectedUnlockExt[i].aunHopt[j], == );
        }
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_RUNNING, == );

        //Cfg logging
#if CFG_ENABLE_LOGGING == 1
        Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
            , (int)Anima_Tgt()->unTgtAni[0]
            , (int)Anima_Tgt()->unTgtAni[1]
            , (int)Anima_Tgt()->unTgtAni[2]
            , (int)Anima_Tgt()->unTgtAni[3]
            , (int)Anima_Tgt()->unTgtAni[4]
            , (int)Anima_Tgt()->unTgtAni[5]
            , (int)Anima_Tgt()->unTgtAni[6]
            , (int)Anima_Tgt()->unTgtAni[7]
            , (int)Anima_Tgt()->unTgtAni[8]
            , (int)Anima_Tgt()->unTgtAni[9]
            , (int)Anima_Tgt()->unTgtAni[10]
            , (int)Anima_Tgt()->unTgtAni[11]
            , (int)Anima_Tgt()->unTgtAni[12]
            , (int)Anima_Tgt()->unTgtAni[13]
            , (int)Anima_Tgt()->unTgtAni[14]
            , (int)Anima_Tgt()->unTgtAni[15]
            , (int)Anima_Tgt()->unTgtAni[16]
            , (int)Anima_Tgt()->unTgtAni[17]
            , (int)Anima_Tgt()->unTgtAni[18]
            , (int)Anima_Tgt()->unTgtAni[19]
            , (int)Anima_Tgt()->unTgtAni[20]
            , (int)Anima_Tgt()->unTgtAni[21]
            , (int)Anima_Tgt()->unTgtAni[22]
            , (int)Anima_Tgt()->unTgtAni[23]
            , (int)Anima_Tgt()->unTgtAni[24]
            , (int)Anima_Tgt()->unTgtAni[25]
            , (int)Anima_Tgt()->unTgtAni[26]
        );
#endif
    }

    //stop previus animation
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_None;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    //Step 2) Call FUT
    Anima_Cycle10();

    for (j = 0; j < 27; j++)
    {
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], 0u, == );
    }
    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );

    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
        , (int)Anima_Tgt()->unTgtAni[0]
        , (int)Anima_Tgt()->unTgtAni[1]
        , (int)Anima_Tgt()->unTgtAni[2]
        , (int)Anima_Tgt()->unTgtAni[3]
        , (int)Anima_Tgt()->unTgtAni[4]
        , (int)Anima_Tgt()->unTgtAni[5]
        , (int)Anima_Tgt()->unTgtAni[6]
        , (int)Anima_Tgt()->unTgtAni[7]
        , (int)Anima_Tgt()->unTgtAni[8]
        , (int)Anima_Tgt()->unTgtAni[9]
        , (int)Anima_Tgt()->unTgtAni[10]
        , (int)Anima_Tgt()->unTgtAni[11]
        , (int)Anima_Tgt()->unTgtAni[12]
        , (int)Anima_Tgt()->unTgtAni[13]
        , (int)Anima_Tgt()->unTgtAni[14]
        , (int)Anima_Tgt()->unTgtAni[15]
        , (int)Anima_Tgt()->unTgtAni[16]
        , (int)Anima_Tgt()->unTgtAni[17]
        , (int)Anima_Tgt()->unTgtAni[18]
        , (int)Anima_Tgt()->unTgtAni[19]
        , (int)Anima_Tgt()->unTgtAni[20]
        , (int)Anima_Tgt()->unTgtAni[21]
        , (int)Anima_Tgt()->unTgtAni[22]
        , (int)Anima_Tgt()->unTgtAni[23]
        , (int)Anima_Tgt()->unTgtAni[24]
        , (int)Anima_Tgt()->unTgtAni[25]
        , (int)Anima_Tgt()->unTgtAni[26]
    );
#endif

#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Stop();
#endif
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Cycle10_Dataset0_UnlockNightExt
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that animation UnlockNightExt is executed correctly.
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_UnlockNightExtension;
///
///   - Expectations:
///
/// \output         Anima_Tgt()->unTgtAni[j]   = aExpectedUnlockExt[i].aunHopt[j]
/// \output         Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_RUNNING
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_Dataset0_UnlockNightExt(void)
{
    int i, j;
    //Step 1) Set pre-conditions,Assign Input values
    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Start(" Mt_CtrlLed_Cycle10_UnlockNightExt.txt");
#endif
    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaUnlockDayNightExt;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_UnlockDayNightExt) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_UnlockDayNightExt[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
    Mt_CtrlLed_PreTest();
    Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_UnlockNightExtension;

    for (i = 0; i < 3000; i++)
    {
        //Step 2) Call FUT
        Anima_Cycle10();
        for (j = 0; j < 27; j++)
        {
            //Step 3) Check expected output values
            AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], aExpectedUnlockExt[i].aunHopt[j], == );
        }
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_RUNNING, == );

        //Cfg logging
#if CFG_ENABLE_LOGGING == 1
        Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
            , (int)Anima_Tgt()->unTgtAni[0]
            , (int)Anima_Tgt()->unTgtAni[1]
            , (int)Anima_Tgt()->unTgtAni[2]
            , (int)Anima_Tgt()->unTgtAni[3]
            , (int)Anima_Tgt()->unTgtAni[4]
            , (int)Anima_Tgt()->unTgtAni[5]
            , (int)Anima_Tgt()->unTgtAni[6]
            , (int)Anima_Tgt()->unTgtAni[7]
            , (int)Anima_Tgt()->unTgtAni[8]
            , (int)Anima_Tgt()->unTgtAni[9]
            , (int)Anima_Tgt()->unTgtAni[10]
            , (int)Anima_Tgt()->unTgtAni[11]
            , (int)Anima_Tgt()->unTgtAni[12]
            , (int)Anima_Tgt()->unTgtAni[13]
            , (int)Anima_Tgt()->unTgtAni[14]
            , (int)Anima_Tgt()->unTgtAni[15]
            , (int)Anima_Tgt()->unTgtAni[16]
            , (int)Anima_Tgt()->unTgtAni[17]
            , (int)Anima_Tgt()->unTgtAni[18]
            , (int)Anima_Tgt()->unTgtAni[19]
            , (int)Anima_Tgt()->unTgtAni[20]
            , (int)Anima_Tgt()->unTgtAni[21]
            , (int)Anima_Tgt()->unTgtAni[22]
            , (int)Anima_Tgt()->unTgtAni[23]
            , (int)Anima_Tgt()->unTgtAni[24]
            , (int)Anima_Tgt()->unTgtAni[25]
            , (int)Anima_Tgt()->unTgtAni[26]
        );
#endif
    }

    //stop previus animation
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl  = eExtLightingAnimationReq_None;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                      = SIG_VALID;
    //Step 2) Call FUT
    Anima_Cycle10();

    for (j = 0; j < 27; j++)
    {
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], 0u, == );
    }
    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );

    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
        , (int)Anima_Tgt()->unTgtAni[0]
        , (int)Anima_Tgt()->unTgtAni[1]
        , (int)Anima_Tgt()->unTgtAni[2]
        , (int)Anima_Tgt()->unTgtAni[3]
        , (int)Anima_Tgt()->unTgtAni[4]
        , (int)Anima_Tgt()->unTgtAni[5]
        , (int)Anima_Tgt()->unTgtAni[6]
        , (int)Anima_Tgt()->unTgtAni[7]
        , (int)Anima_Tgt()->unTgtAni[8]
        , (int)Anima_Tgt()->unTgtAni[9]
        , (int)Anima_Tgt()->unTgtAni[10]
        , (int)Anima_Tgt()->unTgtAni[11]
        , (int)Anima_Tgt()->unTgtAni[12]
        , (int)Anima_Tgt()->unTgtAni[13]
        , (int)Anima_Tgt()->unTgtAni[14]
        , (int)Anima_Tgt()->unTgtAni[15]
        , (int)Anima_Tgt()->unTgtAni[16]
        , (int)Anima_Tgt()->unTgtAni[17]
        , (int)Anima_Tgt()->unTgtAni[18]
        , (int)Anima_Tgt()->unTgtAni[19]
        , (int)Anima_Tgt()->unTgtAni[20]
        , (int)Anima_Tgt()->unTgtAni[21]
        , (int)Anima_Tgt()->unTgtAni[22]
        , (int)Anima_Tgt()->unTgtAni[23]
        , (int)Anima_Tgt()->unTgtAni[24]
        , (int)Anima_Tgt()->unTgtAni[25]
        , (int)Anima_Tgt()->unTgtAni[26]
    );
#endif

#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Stop();
#endif
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Cycle10_Dataset0_UnlockDay
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that animation UnlockDay is executed correctly.
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_UnlockDay;
///
///   - Expectations:
///
/// \output         Anima_Tgt()->unTgtAni[j]   = aExpectedUnlock[i].aunHopt[j]
/// \output         Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_RUNNING
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_Dataset0_UnlockDay(void)
{
    int i, j;
    //Step 1) Set pre-conditions,Assign Input values

   //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Start(" Mt_CtrlLed_Cycle10_UnlockDay.txt");
#endif
    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaUnlockDayNight;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset0_Unlock) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset0_Unlock[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
    Mt_CtrlLed_PreTest();
    Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_UnlockDay;

    for (i = 0; i < 400; i++)
    {
        //Step 2) Call FUT
        Anima_Cycle10();
        for (j = 0; j < 27; j++)
        {
            //Step 3) Check expected output values
            AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], aExpectedUnlock[i].aunHopt[j], == );
        }
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_RUNNING, == );

        //Cfg logging
#if CFG_ENABLE_LOGGING == 1
        Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
            , (int)Anima_Tgt()->unTgtAni[0]
            , (int)Anima_Tgt()->unTgtAni[1]
            , (int)Anima_Tgt()->unTgtAni[2]
            , (int)Anima_Tgt()->unTgtAni[3]
            , (int)Anima_Tgt()->unTgtAni[4]
            , (int)Anima_Tgt()->unTgtAni[5]
            , (int)Anima_Tgt()->unTgtAni[6]
            , (int)Anima_Tgt()->unTgtAni[7]
            , (int)Anima_Tgt()->unTgtAni[8]
            , (int)Anima_Tgt()->unTgtAni[9]
            , (int)Anima_Tgt()->unTgtAni[10]
            , (int)Anima_Tgt()->unTgtAni[11]
            , (int)Anima_Tgt()->unTgtAni[12]
            , (int)Anima_Tgt()->unTgtAni[13]
            , (int)Anima_Tgt()->unTgtAni[14]
            , (int)Anima_Tgt()->unTgtAni[15]
            , (int)Anima_Tgt()->unTgtAni[16]
            , (int)Anima_Tgt()->unTgtAni[17]
            , (int)Anima_Tgt()->unTgtAni[18]
            , (int)Anima_Tgt()->unTgtAni[19]
            , (int)Anima_Tgt()->unTgtAni[20]
            , (int)Anima_Tgt()->unTgtAni[21]
            , (int)Anima_Tgt()->unTgtAni[22]
            , (int)Anima_Tgt()->unTgtAni[23]
            , (int)Anima_Tgt()->unTgtAni[24]
            , (int)Anima_Tgt()->unTgtAni[25]
            , (int)Anima_Tgt()->unTgtAni[26]
        );
#endif
    }

    //stop previus animation
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_None;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    //Step 2) Call FUT
    Anima_Cycle10();

    for (j = 0; j < 27; j++)
    {
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], 0u, == );
    }
    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );

    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
        , (int)Anima_Tgt()->unTgtAni[0]
        , (int)Anima_Tgt()->unTgtAni[1]
        , (int)Anima_Tgt()->unTgtAni[2]
        , (int)Anima_Tgt()->unTgtAni[3]
        , (int)Anima_Tgt()->unTgtAni[4]
        , (int)Anima_Tgt()->unTgtAni[5]
        , (int)Anima_Tgt()->unTgtAni[6]
        , (int)Anima_Tgt()->unTgtAni[7]
        , (int)Anima_Tgt()->unTgtAni[8]
        , (int)Anima_Tgt()->unTgtAni[9]
        , (int)Anima_Tgt()->unTgtAni[10]
        , (int)Anima_Tgt()->unTgtAni[11]
        , (int)Anima_Tgt()->unTgtAni[12]
        , (int)Anima_Tgt()->unTgtAni[13]
        , (int)Anima_Tgt()->unTgtAni[14]
        , (int)Anima_Tgt()->unTgtAni[15]
        , (int)Anima_Tgt()->unTgtAni[16]
        , (int)Anima_Tgt()->unTgtAni[17]
        , (int)Anima_Tgt()->unTgtAni[18]
        , (int)Anima_Tgt()->unTgtAni[19]
        , (int)Anima_Tgt()->unTgtAni[20]
        , (int)Anima_Tgt()->unTgtAni[21]
        , (int)Anima_Tgt()->unTgtAni[22]
        , (int)Anima_Tgt()->unTgtAni[23]
        , (int)Anima_Tgt()->unTgtAni[24]
        , (int)Anima_Tgt()->unTgtAni[25]
        , (int)Anima_Tgt()->unTgtAni[26]
    );
#endif

#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Stop();
#endif
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Cycle10_Dataset0_UnlockNight
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that animation UnlockNight is executed correctly.
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_UnlockNight;
///
///   - Expectations:
///
/// \output         Anima_Tgt()->unTgtAni[j] = aExpectedUnlock[i].aunHopt[j]
/// \output         Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_RUNNING
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_Dataset0_UnlockNight(void)
{
    int i, j;
    //Step 1) Set pre-conditions,Assign Input values
    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Start(" Mt_CtrlLed_Cycle10_UnlockNight.txt");
#endif
    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaUnlockDayNight;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset0_Unlock) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset0_Unlock[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState = eParaFct0_CodingDataValid;
    Mt_CtrlLed_PreTest();
    Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_UnlockNight;

    for (i = 0; i < 400; i++)
    {
        //Step 2) Call FUT
        Anima_Cycle10();
        for (j = 0; j < 27; j++)
        {
            //Step 3) Check expected output values
            AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], aExpectedUnlock[i].aunHopt[j], == );
        }
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_RUNNING, == );

        //Cfg logging
#if CFG_ENABLE_LOGGING == 1
        Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
            , (int)Anima_Tgt()->unTgtAni[0]
            , (int)Anima_Tgt()->unTgtAni[1]
            , (int)Anima_Tgt()->unTgtAni[2]
            , (int)Anima_Tgt()->unTgtAni[3]
            , (int)Anima_Tgt()->unTgtAni[4]
            , (int)Anima_Tgt()->unTgtAni[5]
            , (int)Anima_Tgt()->unTgtAni[6]
            , (int)Anima_Tgt()->unTgtAni[7]
            , (int)Anima_Tgt()->unTgtAni[8]
            , (int)Anima_Tgt()->unTgtAni[9]
            , (int)Anima_Tgt()->unTgtAni[10]
            , (int)Anima_Tgt()->unTgtAni[11]
            , (int)Anima_Tgt()->unTgtAni[12]
            , (int)Anima_Tgt()->unTgtAni[13]
            , (int)Anima_Tgt()->unTgtAni[14]
            , (int)Anima_Tgt()->unTgtAni[15]
            , (int)Anima_Tgt()->unTgtAni[16]
            , (int)Anima_Tgt()->unTgtAni[17]
            , (int)Anima_Tgt()->unTgtAni[18]
            , (int)Anima_Tgt()->unTgtAni[19]
            , (int)Anima_Tgt()->unTgtAni[20]
            , (int)Anima_Tgt()->unTgtAni[21]
            , (int)Anima_Tgt()->unTgtAni[22]
            , (int)Anima_Tgt()->unTgtAni[23]
            , (int)Anima_Tgt()->unTgtAni[24]
            , (int)Anima_Tgt()->unTgtAni[25]
            , (int)Anima_Tgt()->unTgtAni[26]
        );
#endif
    }

    //stop previus animation
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_None;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    //Step 2) Call FUT
    Anima_Cycle10();

    for (j = 0; j < 27; j++)
    {
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], 0u, == );
    }
    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );

    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
        , (int)Anima_Tgt()->unTgtAni[0]
        , (int)Anima_Tgt()->unTgtAni[1]
        , (int)Anima_Tgt()->unTgtAni[2]
        , (int)Anima_Tgt()->unTgtAni[3]
        , (int)Anima_Tgt()->unTgtAni[4]
        , (int)Anima_Tgt()->unTgtAni[5]
        , (int)Anima_Tgt()->unTgtAni[6]
        , (int)Anima_Tgt()->unTgtAni[7]
        , (int)Anima_Tgt()->unTgtAni[8]
        , (int)Anima_Tgt()->unTgtAni[9]
        , (int)Anima_Tgt()->unTgtAni[10]
        , (int)Anima_Tgt()->unTgtAni[11]
        , (int)Anima_Tgt()->unTgtAni[12]
        , (int)Anima_Tgt()->unTgtAni[13]
        , (int)Anima_Tgt()->unTgtAni[14]
        , (int)Anima_Tgt()->unTgtAni[15]
        , (int)Anima_Tgt()->unTgtAni[16]
        , (int)Anima_Tgt()->unTgtAni[17]
        , (int)Anima_Tgt()->unTgtAni[18]
        , (int)Anima_Tgt()->unTgtAni[19]
        , (int)Anima_Tgt()->unTgtAni[20]
        , (int)Anima_Tgt()->unTgtAni[21]
        , (int)Anima_Tgt()->unTgtAni[22]
        , (int)Anima_Tgt()->unTgtAni[23]
        , (int)Anima_Tgt()->unTgtAni[24]
        , (int)Anima_Tgt()->unTgtAni[25]
        , (int)Anima_Tgt()->unTgtAni[26]
    );
#endif

#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Stop();
#endif
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CtrlLed_Cycle10_Dataset0_ByeByeNightFmh(void)
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that animation ByeByeNightFm is executed correctly.
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_ByeByeNightFm;
///
///   - Expectations:
///
/// \output         Anima_Tgt()->unTgtAni[j] = aExpectedUndefined[i].aunHopt[j]
/// \output         Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_RUNNING
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_Dataset0_ByeByeNightFmh(void)
{
    int i, j;
     //Step 1) Set pre-conditions,Assign Input values
    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
     Mt_CtrlLed_Log_Start(" Mt_CtrlLed_Cycle10_ByeByeNightFmh.txt");
#endif
    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaUndefinedAnima;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset0_UndefinedAnima) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset0_UndefinedAnima[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
    Mt_CtrlLed_PreTest();
    Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_ByeByeNightFmh;

    for (i = 0; i < 5000; i++)
    {
        //Step 2) Call FUT
        Anima_Cycle10();
        for (j = 0; j < 27; j++)
        {
            //Step 3) Check expected output values
            AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], aExpectedUndefined[i].aunHopt[j], == );
        }
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_RUNNING, == );

        //Cfg logging
#if CFG_ENABLE_LOGGING == 1
        Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
            , (int)Anima_Tgt()->unTgtAni[0]
            , (int)Anima_Tgt()->unTgtAni[1]
            , (int)Anima_Tgt()->unTgtAni[2]
            , (int)Anima_Tgt()->unTgtAni[3]
            , (int)Anima_Tgt()->unTgtAni[4]
            , (int)Anima_Tgt()->unTgtAni[5]
            , (int)Anima_Tgt()->unTgtAni[6]
            , (int)Anima_Tgt()->unTgtAni[7]
            , (int)Anima_Tgt()->unTgtAni[8]
            , (int)Anima_Tgt()->unTgtAni[9]
            , (int)Anima_Tgt()->unTgtAni[10]
            , (int)Anima_Tgt()->unTgtAni[11]
            , (int)Anima_Tgt()->unTgtAni[12]
            , (int)Anima_Tgt()->unTgtAni[13]
            , (int)Anima_Tgt()->unTgtAni[14]
            , (int)Anima_Tgt()->unTgtAni[15]
            , (int)Anima_Tgt()->unTgtAni[16]
            , (int)Anima_Tgt()->unTgtAni[17]
            , (int)Anima_Tgt()->unTgtAni[18]
            , (int)Anima_Tgt()->unTgtAni[19]
            , (int)Anima_Tgt()->unTgtAni[20]
            , (int)Anima_Tgt()->unTgtAni[21]
            , (int)Anima_Tgt()->unTgtAni[22]
            , (int)Anima_Tgt()->unTgtAni[23]
            , (int)Anima_Tgt()->unTgtAni[24]
            , (int)Anima_Tgt()->unTgtAni[25]
            , (int)Anima_Tgt()->unTgtAni[26]
        );
#endif
    }

    //stop previus animation
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_None;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    //Step 2) Call FUT
    Anima_Cycle10();

    for (j = 0; j < 27; j++)
    {
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], 0u, == );
    }
    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CtrlLed_Cycle10_Dataset0_RemoteLighting(void)
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that animation RemoteLighting is executed correctly.
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_RemoteLighting;
///
///   - Expectations:
///
/// \output         Anima_Tgt()->unTgtAni[j]   = aExpectedUndefined[i].aunHopt[j]
/// \output         Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_RUNNING
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_Dataset0_RemoteLighting(void)
{
    int i, j;
    //Step 1) Set pre-conditions,Assign Input values
    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Start(" Mt_CtrlLed_Cycle10_RemoteLighting.txt");
#endif
    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaUndefinedAnima;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset0_UndefinedAnima) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset0_UndefinedAnima[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
    Mt_CtrlLed_PreTest();
    Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_None;

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );

    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_RemoteLighting;

    for (i = 0; i < 5000; i++)
    {
        //Step 2) Call FUT
        Anima_Cycle10();
        for (j = 0; j < 27; j++)
        {
            //Step 3) Check expected output values
            AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], aExpectedUndefined[i].aunHopt[j], == );
        }
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_RUNNING, == );

        //Cfg logging
#if CFG_ENABLE_LOGGING == 1
        Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
            , (int)Anima_Tgt()->unTgtAni[0]
            , (int)Anima_Tgt()->unTgtAni[1]
            , (int)Anima_Tgt()->unTgtAni[2]
            , (int)Anima_Tgt()->unTgtAni[3]
            , (int)Anima_Tgt()->unTgtAni[4]
            , (int)Anima_Tgt()->unTgtAni[5]
            , (int)Anima_Tgt()->unTgtAni[6]
            , (int)Anima_Tgt()->unTgtAni[7]
            , (int)Anima_Tgt()->unTgtAni[8]
            , (int)Anima_Tgt()->unTgtAni[9]
            , (int)Anima_Tgt()->unTgtAni[10]
            , (int)Anima_Tgt()->unTgtAni[11]
            , (int)Anima_Tgt()->unTgtAni[12]
            , (int)Anima_Tgt()->unTgtAni[13]
            , (int)Anima_Tgt()->unTgtAni[14]
            , (int)Anima_Tgt()->unTgtAni[15]
            , (int)Anima_Tgt()->unTgtAni[16]
            , (int)Anima_Tgt()->unTgtAni[17]
            , (int)Anima_Tgt()->unTgtAni[18]
            , (int)Anima_Tgt()->unTgtAni[19]
            , (int)Anima_Tgt()->unTgtAni[20]
            , (int)Anima_Tgt()->unTgtAni[21]
            , (int)Anima_Tgt()->unTgtAni[22]
            , (int)Anima_Tgt()->unTgtAni[23]
            , (int)Anima_Tgt()->unTgtAni[24]
            , (int)Anima_Tgt()->unTgtAni[25]
            , (int)Anima_Tgt()->unTgtAni[26]
        );
#endif
    }

    //stop previus animation
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_None;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    //Step 2) Call FUT
    Anima_Cycle10();

    for (j = 0; j < 27; j++)
    {
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], 0u, == );
    }
    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CtrlLed_Cycle10_Dataset0_SwitchOff(void)
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that animation SwitchOff is executed correctly.
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_SwitchOff;
///
///   - Expectations:
///
/// \output         Anima_Tgt()->unTgtAni[j] = aExpectedUndefined[i].aunHopt[j]
/// \output         Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_RUNNING
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_Dataset0_SwitchOff(void)
{
    int i, j;
    //Step 1) Set pre-conditions,Assign Input values
    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Start(" Mt_CtrlLed_Cycle10_SwitchOff.txt");
#endif
    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaUndefinedAnima;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset0_UndefinedAnima) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset0_UndefinedAnima[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
    Mt_CtrlLed_PreTest();
    Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_None;

    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );

    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_SwitchOff;

    for (i = 0; i < 5000; i++)
    {
        //Step 2) Call FUT
        Anima_Cycle10();
        for (j = 0; j < 27; j++)
        {
            //Step 3) Check expected output values
            AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], aExpectedUndefined[i].aunHopt[j], == );
        }
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_RUNNING, == );

        //Cfg logging
#if CFG_ENABLE_LOGGING == 1
        Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
            , (int)Anima_Tgt()->unTgtAni[0]
            , (int)Anima_Tgt()->unTgtAni[1]
            , (int)Anima_Tgt()->unTgtAni[2]
            , (int)Anima_Tgt()->unTgtAni[3]
            , (int)Anima_Tgt()->unTgtAni[4]
            , (int)Anima_Tgt()->unTgtAni[5]
            , (int)Anima_Tgt()->unTgtAni[6]
            , (int)Anima_Tgt()->unTgtAni[7]
            , (int)Anima_Tgt()->unTgtAni[8]
            , (int)Anima_Tgt()->unTgtAni[9]
            , (int)Anima_Tgt()->unTgtAni[10]
            , (int)Anima_Tgt()->unTgtAni[11]
            , (int)Anima_Tgt()->unTgtAni[12]
            , (int)Anima_Tgt()->unTgtAni[13]
            , (int)Anima_Tgt()->unTgtAni[14]
            , (int)Anima_Tgt()->unTgtAni[15]
            , (int)Anima_Tgt()->unTgtAni[16]
            , (int)Anima_Tgt()->unTgtAni[17]
            , (int)Anima_Tgt()->unTgtAni[18]
            , (int)Anima_Tgt()->unTgtAni[19]
            , (int)Anima_Tgt()->unTgtAni[20]
            , (int)Anima_Tgt()->unTgtAni[21]
            , (int)Anima_Tgt()->unTgtAni[22]
            , (int)Anima_Tgt()->unTgtAni[23]
            , (int)Anima_Tgt()->unTgtAni[24]
            , (int)Anima_Tgt()->unTgtAni[25]
            , (int)Anima_Tgt()->unTgtAni[26]
        );
#endif
    }

    //stop previus animation
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_None;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    //Step 2) Call FUT
    Anima_Cycle10();

    for (j = 0; j < 27; j++)
    {
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], 0u, == );
    }
    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CtrlLed_Cycle10_ShowroomContinu(void)
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that animation ShowroomContinu is executed correctly.
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_ShowroomContinu;
///
///   - Expectations:
///
/// \output         Anima_Tgt()->unTgtAni[j]   = aExpectedShowroomContinu[i].aunHopt[j]
/// \output         Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_RUNNING
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_ShowroomContinu(void)
{
    int i, j;
    //Step 1) Set pre-conditions,Assign Input values
    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Start(" Mt_CtrlLed_Cycle10_ShowroomContinu.txt");
#endif
    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaShowroomEvent;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucShowroomContinu) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucShowroomContinu[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;

    Mt_CtrlLed_PreTest();
    Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_ShowroomContinu;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    //Step 2) Call FUT
    Anima_Cycle10();

    for (i = 0; i < 3000; i++)
    {
        for (j = 0; j < 27; j++)
        {
            //Step 3) Check expected output values
            AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], aExpectedShowroomContinu[i].aunHopt[j], == );
        }
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_RUNNING, == );

        //Cfg logging
#if CFG_ENABLE_LOGGING == 1
        Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
            , (int)Anima_Tgt()->unTgtAni[0]
            , (int)Anima_Tgt()->unTgtAni[1]
            , (int)Anima_Tgt()->unTgtAni[2]
            , (int)Anima_Tgt()->unTgtAni[3]
            , (int)Anima_Tgt()->unTgtAni[4]
            , (int)Anima_Tgt()->unTgtAni[5]
            , (int)Anima_Tgt()->unTgtAni[6]
            , (int)Anima_Tgt()->unTgtAni[7]
            , (int)Anima_Tgt()->unTgtAni[8]
            , (int)Anima_Tgt()->unTgtAni[9]
            , (int)Anima_Tgt()->unTgtAni[10]
            , (int)Anima_Tgt()->unTgtAni[11]
            , (int)Anima_Tgt()->unTgtAni[12]
            , (int)Anima_Tgt()->unTgtAni[13]
            , (int)Anima_Tgt()->unTgtAni[14]
            , (int)Anima_Tgt()->unTgtAni[15]
            , (int)Anima_Tgt()->unTgtAni[16]
            , (int)Anima_Tgt()->unTgtAni[17]
            , (int)Anima_Tgt()->unTgtAni[18]
            , (int)Anima_Tgt()->unTgtAni[19]
            , (int)Anima_Tgt()->unTgtAni[20]
            , (int)Anima_Tgt()->unTgtAni[21]
            , (int)Anima_Tgt()->unTgtAni[22]
            , (int)Anima_Tgt()->unTgtAni[23]
            , (int)Anima_Tgt()->unTgtAni[24]
            , (int)Anima_Tgt()->unTgtAni[25]
            , (int)Anima_Tgt()->unTgtAni[26]
        );
#endif
    }

    //stop previus animation
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_None;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    //Step 2) Call FUT
    Anima_Cycle10();

    for (j = 0; j < 27; j++)
    {
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], 0u, == );
    }
    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );

    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d } }\n", 10 * i
        , (int)Anima_Tgt()->unTgtAni[0]
        , (int)Anima_Tgt()->unTgtAni[1]
        , (int)Anima_Tgt()->unTgtAni[2]
        , (int)Anima_Tgt()->unTgtAni[3]
        , (int)Anima_Tgt()->unTgtAni[4]
        , (int)Anima_Tgt()->unTgtAni[5]
        , (int)Anima_Tgt()->unTgtAni[6]
        , (int)Anima_Tgt()->unTgtAni[7]
        , (int)Anima_Tgt()->unTgtAni[8]
        , (int)Anima_Tgt()->unTgtAni[9]
        , (int)Anima_Tgt()->unTgtAni[10]
        , (int)Anima_Tgt()->unTgtAni[11]
        , (int)Anima_Tgt()->unTgtAni[12]
        , (int)Anima_Tgt()->unTgtAni[13]
        , (int)Anima_Tgt()->unTgtAni[14]
        , (int)Anima_Tgt()->unTgtAni[15]
        , (int)Anima_Tgt()->unTgtAni[16]
        , (int)Anima_Tgt()->unTgtAni[17]
        , (int)Anima_Tgt()->unTgtAni[18]
        , (int)Anima_Tgt()->unTgtAni[19]
        , (int)Anima_Tgt()->unTgtAni[20]
        , (int)Anima_Tgt()->unTgtAni[21]
        , (int)Anima_Tgt()->unTgtAni[22]
        , (int)Anima_Tgt()->unTgtAni[23]
        , (int)Anima_Tgt()->unTgtAni[24]
        , (int)Anima_Tgt()->unTgtAni[25]
        , (int)Anima_Tgt()->unTgtAni[26]
    );
#endif

#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Stop();
#endif
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CtrlLed_Cycle10_Dataset0_LockDay(void)
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that animation LockDay is executed correctly.
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_LockDay;
///
///   - Expectations:
///
/// \output         Anima_Tgt()->unTgtAni[j]   = aExpectedLock[i].aunHopt[j]
/// \output         Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_RUNNING
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_Dataset0_LockDay(void)
{
    int i, j;
    //Step 1) Set pre-conditions,Assign Input values
    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Start(" Mt_CtrlLed_Cycle10_LockDay.txt");
#endif

    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaLockDayNight;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset0_Lock) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset0_Lock[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;

    Mt_CtrlLed_PreTest();
    Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_LockDay;

    for (i = 0; i < 400; i++)
    {
        //Step 2) Call FUT
        Anima_Cycle10();
        for (j = 0; j < 27; j++)
        {
            //Step 3) Check expected output values
            AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], aExpectedLock[i].aunHopt[j], == );
        }
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_RUNNING, == );

        //Cfg logging
#if CFG_ENABLE_LOGGING == 1
        Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
            , (int)Anima_Tgt()->unTgtAni[0]
            , (int)Anima_Tgt()->unTgtAni[1]
            , (int)Anima_Tgt()->unTgtAni[2]
            , (int)Anima_Tgt()->unTgtAni[3]
            , (int)Anima_Tgt()->unTgtAni[4]
            , (int)Anima_Tgt()->unTgtAni[5]
            , (int)Anima_Tgt()->unTgtAni[6]
            , (int)Anima_Tgt()->unTgtAni[7]
            , (int)Anima_Tgt()->unTgtAni[8]
            , (int)Anima_Tgt()->unTgtAni[9]
            , (int)Anima_Tgt()->unTgtAni[10]
            , (int)Anima_Tgt()->unTgtAni[11]
            , (int)Anima_Tgt()->unTgtAni[12]
            , (int)Anima_Tgt()->unTgtAni[13]
            , (int)Anima_Tgt()->unTgtAni[14]
            , (int)Anima_Tgt()->unTgtAni[15]
            , (int)Anima_Tgt()->unTgtAni[16]
            , (int)Anima_Tgt()->unTgtAni[17]
            , (int)Anima_Tgt()->unTgtAni[18]
            , (int)Anima_Tgt()->unTgtAni[19]
            , (int)Anima_Tgt()->unTgtAni[20]
            , (int)Anima_Tgt()->unTgtAni[21]
            , (int)Anima_Tgt()->unTgtAni[22]
            , (int)Anima_Tgt()->unTgtAni[23]
            , (int)Anima_Tgt()->unTgtAni[24]
            , (int)Anima_Tgt()->unTgtAni[25]
            , (int)Anima_Tgt()->unTgtAni[26]
        );
#endif
    }

    //stop previus animation
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_None;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    //Step 2) Call FUT
    Anima_Cycle10();

    for (j = 0; j < 27; j++)
    {
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], 0u, == );
    }
    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );

    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
        , (int)Anima_Tgt()->unTgtAni[0]
        , (int)Anima_Tgt()->unTgtAni[1]
        , (int)Anima_Tgt()->unTgtAni[2]
        , (int)Anima_Tgt()->unTgtAni[3]
        , (int)Anima_Tgt()->unTgtAni[4]
        , (int)Anima_Tgt()->unTgtAni[5]
        , (int)Anima_Tgt()->unTgtAni[6]
        , (int)Anima_Tgt()->unTgtAni[7]
        , (int)Anima_Tgt()->unTgtAni[8]
        , (int)Anima_Tgt()->unTgtAni[9]
        , (int)Anima_Tgt()->unTgtAni[10]
        , (int)Anima_Tgt()->unTgtAni[11]
        , (int)Anima_Tgt()->unTgtAni[12]
        , (int)Anima_Tgt()->unTgtAni[13]
        , (int)Anima_Tgt()->unTgtAni[14]
        , (int)Anima_Tgt()->unTgtAni[15]
        , (int)Anima_Tgt()->unTgtAni[16]
        , (int)Anima_Tgt()->unTgtAni[17]
        , (int)Anima_Tgt()->unTgtAni[18]
        , (int)Anima_Tgt()->unTgtAni[19]
        , (int)Anima_Tgt()->unTgtAni[20]
        , (int)Anima_Tgt()->unTgtAni[21]
        , (int)Anima_Tgt()->unTgtAni[22]
        , (int)Anima_Tgt()->unTgtAni[23]
        , (int)Anima_Tgt()->unTgtAni[24]
        , (int)Anima_Tgt()->unTgtAni[25]
        , (int)Anima_Tgt()->unTgtAni[26]
    );
#endif

#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Stop();
#endif
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CtrlLed_Cycle10_Dataset0_LockNight(void)
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that animation LockNight is executed correctly.
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReqLockNight;
///
///   - Expectations:
///
/// \output         Anima_Tgt()->unTgtAni[j]   = aExpectedLock[i].aunHopt[j]
/// \output         Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_RUNNING
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_Dataset0_LockNight(void)
{
    int i, j;
    //Step 1) Set pre-conditions,Assign Input values
    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Start(" Mt_CtrlLed_Cycle10_LockNight.txt");
#endif

    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaLockDayNight;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset0_Lock) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset0_Lock[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;

    Mt_CtrlLed_PreTest();
    Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_LockNight;

    for (i = 0; i < 400; i++)
    {
        //Step 2) Call FUT
        Anima_Cycle10();
        for (j = 0; j < 27; j++)
        {
            //Step 3) Check expected output values
            AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], aExpectedLock[i].aunHopt[j], == );
        }
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_RUNNING, == );

        //Cfg logging
#if CFG_ENABLE_LOGGING == 1
        Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
            , (int)Anima_Tgt()->unTgtAni[0]
            , (int)Anima_Tgt()->unTgtAni[1]
            , (int)Anima_Tgt()->unTgtAni[2]
            , (int)Anima_Tgt()->unTgtAni[3]
            , (int)Anima_Tgt()->unTgtAni[4]
            , (int)Anima_Tgt()->unTgtAni[5]
            , (int)Anima_Tgt()->unTgtAni[6]
            , (int)Anima_Tgt()->unTgtAni[7]
            , (int)Anima_Tgt()->unTgtAni[8]
            , (int)Anima_Tgt()->unTgtAni[9]
            , (int)Anima_Tgt()->unTgtAni[10]
            , (int)Anima_Tgt()->unTgtAni[11]
            , (int)Anima_Tgt()->unTgtAni[12]
            , (int)Anima_Tgt()->unTgtAni[13]
            , (int)Anima_Tgt()->unTgtAni[14]
            , (int)Anima_Tgt()->unTgtAni[15]
            , (int)Anima_Tgt()->unTgtAni[16]
            , (int)Anima_Tgt()->unTgtAni[17]
            , (int)Anima_Tgt()->unTgtAni[18]
            , (int)Anima_Tgt()->unTgtAni[19]
            , (int)Anima_Tgt()->unTgtAni[20]
            , (int)Anima_Tgt()->unTgtAni[21]
            , (int)Anima_Tgt()->unTgtAni[22]
            , (int)Anima_Tgt()->unTgtAni[23]
            , (int)Anima_Tgt()->unTgtAni[24]
            , (int)Anima_Tgt()->unTgtAni[25]
            , (int)Anima_Tgt()->unTgtAni[26]
        );
#endif
    }

    //stop previus animation
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_None;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    //Step 2) Call FUT
    Anima_Cycle10();

    for (j = 0; j < 27; j++)
    {
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], 0u, == );
    }
    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );

    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
        , (int)Anima_Tgt()->unTgtAni[0]
        , (int)Anima_Tgt()->unTgtAni[1]
        , (int)Anima_Tgt()->unTgtAni[2]
        , (int)Anima_Tgt()->unTgtAni[3]
        , (int)Anima_Tgt()->unTgtAni[4]
        , (int)Anima_Tgt()->unTgtAni[5]
        , (int)Anima_Tgt()->unTgtAni[6]
        , (int)Anima_Tgt()->unTgtAni[7]
        , (int)Anima_Tgt()->unTgtAni[8]
        , (int)Anima_Tgt()->unTgtAni[9]
        , (int)Anima_Tgt()->unTgtAni[10]
        , (int)Anima_Tgt()->unTgtAni[11]
        , (int)Anima_Tgt()->unTgtAni[12]
        , (int)Anima_Tgt()->unTgtAni[13]
        , (int)Anima_Tgt()->unTgtAni[14]
        , (int)Anima_Tgt()->unTgtAni[15]
        , (int)Anima_Tgt()->unTgtAni[16]
        , (int)Anima_Tgt()->unTgtAni[17]
        , (int)Anima_Tgt()->unTgtAni[18]
        , (int)Anima_Tgt()->unTgtAni[19]
        , (int)Anima_Tgt()->unTgtAni[20]
        , (int)Anima_Tgt()->unTgtAni[21]
        , (int)Anima_Tgt()->unTgtAni[22]
        , (int)Anima_Tgt()->unTgtAni[23]
        , (int)Anima_Tgt()->unTgtAni[24]
        , (int)Anima_Tgt()->unTgtAni[25]
        , (int)Anima_Tgt()->unTgtAni[26]
    );
#endif

#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Stop();
#endif
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Cycle10_Dataset0_Autorelock
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that animation Autorelock is executed correctly.
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_Autorelock;
///
///   - Expectations:
///
/// \output         Anima_Tgt()->unTgtAni[j]   = aExpectedLock[i].aunHopt[j]
/// \output         Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_RUNNING
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_Dataset0_Autorelock(void)
{
    int i, j;
    //Step 1) Set pre-conditions,Assign Input values
    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Start(" Mt_CtrlLed_Cycle10_Autorelock.txt");
#endif

    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaLockDayNight;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset0_Lock) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset0_Lock[i];
    } 
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;

    Mt_CtrlLed_PreTest();
    Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_Autorelock;

    for (i = 0; i < 400; i++)
    {
        //Step 2) Call FUT
        Anima_Cycle10();
        for (j = 0; j < 27; j++)
        {
            //Step 3) Check expected output values
            AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], aExpectedLock[i].aunHopt[j], == );
        }
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_RUNNING, == );

        //Cfg logging
#if CFG_ENABLE_LOGGING == 1
        Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
            , (int)Anima_Tgt()->unTgtAni[0]
            , (int)Anima_Tgt()->unTgtAni[1]
            , (int)Anima_Tgt()->unTgtAni[2]
            , (int)Anima_Tgt()->unTgtAni[3]
            , (int)Anima_Tgt()->unTgtAni[4]
            , (int)Anima_Tgt()->unTgtAni[5]
            , (int)Anima_Tgt()->unTgtAni[6]
            , (int)Anima_Tgt()->unTgtAni[7]
            , (int)Anima_Tgt()->unTgtAni[8]
            , (int)Anima_Tgt()->unTgtAni[9]
            , (int)Anima_Tgt()->unTgtAni[10]
            , (int)Anima_Tgt()->unTgtAni[11]
            , (int)Anima_Tgt()->unTgtAni[12]
            , (int)Anima_Tgt()->unTgtAni[13]
            , (int)Anima_Tgt()->unTgtAni[14]
            , (int)Anima_Tgt()->unTgtAni[15]
            , (int)Anima_Tgt()->unTgtAni[16]
            , (int)Anima_Tgt()->unTgtAni[17]
            , (int)Anima_Tgt()->unTgtAni[18]
            , (int)Anima_Tgt()->unTgtAni[19]
            , (int)Anima_Tgt()->unTgtAni[20]
            , (int)Anima_Tgt()->unTgtAni[21]
            , (int)Anima_Tgt()->unTgtAni[22]
            , (int)Anima_Tgt()->unTgtAni[23]
            , (int)Anima_Tgt()->unTgtAni[24]
            , (int)Anima_Tgt()->unTgtAni[25]
            , (int)Anima_Tgt()->unTgtAni[26]
        );
#endif
    }

    //stop previus animation
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_None;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    //Step 2) Call FUT
    Anima_Cycle10();

    for (j = 0; j < 27; j++)
    {
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], 0u, == );
    }
    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );

    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
        , (int)Anima_Tgt()->unTgtAni[0]
        , (int)Anima_Tgt()->unTgtAni[1]
        , (int)Anima_Tgt()->unTgtAni[2]
        , (int)Anima_Tgt()->unTgtAni[3]
        , (int)Anima_Tgt()->unTgtAni[4]
        , (int)Anima_Tgt()->unTgtAni[5]
        , (int)Anima_Tgt()->unTgtAni[6]
        , (int)Anima_Tgt()->unTgtAni[7]
        , (int)Anima_Tgt()->unTgtAni[8]
        , (int)Anima_Tgt()->unTgtAni[9]
        , (int)Anima_Tgt()->unTgtAni[10]
        , (int)Anima_Tgt()->unTgtAni[11]
        , (int)Anima_Tgt()->unTgtAni[12]
        , (int)Anima_Tgt()->unTgtAni[13]
        , (int)Anima_Tgt()->unTgtAni[14]
        , (int)Anima_Tgt()->unTgtAni[15]
        , (int)Anima_Tgt()->unTgtAni[16]
        , (int)Anima_Tgt()->unTgtAni[17]
        , (int)Anima_Tgt()->unTgtAni[18]
        , (int)Anima_Tgt()->unTgtAni[19]
        , (int)Anima_Tgt()->unTgtAni[20]
        , (int)Anima_Tgt()->unTgtAni[21]
        , (int)Anima_Tgt()->unTgtAni[22]
        , (int)Anima_Tgt()->unTgtAni[23]
        , (int)Anima_Tgt()->unTgtAni[24]
        , (int)Anima_Tgt()->unTgtAni[25]
        , (int)Anima_Tgt()->unTgtAni[26]
    );
#endif

#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Stop();
#endif
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CtrlLed_Cycle10_Dataset0_LockDayExt(void)
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that animation LockDayExt is executed correctly.
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_LockDayExtension;
///
///   - Expectations:
///
/// \output         Anima_Tgt()->unTgtAni[j] = aExpectedLockExt[i].aunHopt[j]
/// \output         Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_RUNNING
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_Dataset0_LockDayExt(void)
{
    int i, j;
    //Step 1) Set pre-conditions,Assign Input values

   //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Start(" Mt_CtrlLed_Cycle10_LockDayExt.txt");
#endif
    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaLockDayNight;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset0_LockExt) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset0_LockExt[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;

    Mt_CtrlLed_PreTest();
    Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_LockDayExtension;

    for (i = 0; i < 500; i++)
    {
        //Step 2) Call FUT
        Anima_Cycle10();
        for (j = 0; j < 27; j++)
        {
            //Step 3) Check expected output values
            AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], aExpectedLockExt[i].aunHopt[j], == );
        }
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_RUNNING, == );

        //Cfg logging
#if CFG_ENABLE_LOGGING == 1
        Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
            , (int)Anima_Tgt()->unTgtAni[0]
            , (int)Anima_Tgt()->unTgtAni[1]
            , (int)Anima_Tgt()->unTgtAni[2]
            , (int)Anima_Tgt()->unTgtAni[3]
            , (int)Anima_Tgt()->unTgtAni[4]
            , (int)Anima_Tgt()->unTgtAni[5]
            , (int)Anima_Tgt()->unTgtAni[6]
            , (int)Anima_Tgt()->unTgtAni[7]
            , (int)Anima_Tgt()->unTgtAni[8]
            , (int)Anima_Tgt()->unTgtAni[9]
            , (int)Anima_Tgt()->unTgtAni[10]
            , (int)Anima_Tgt()->unTgtAni[11]
            , (int)Anima_Tgt()->unTgtAni[12]
            , (int)Anima_Tgt()->unTgtAni[13]
            , (int)Anima_Tgt()->unTgtAni[14]
            , (int)Anima_Tgt()->unTgtAni[15]
            , (int)Anima_Tgt()->unTgtAni[16]
            , (int)Anima_Tgt()->unTgtAni[17]
            , (int)Anima_Tgt()->unTgtAni[18]
            , (int)Anima_Tgt()->unTgtAni[19]
            , (int)Anima_Tgt()->unTgtAni[20]
            , (int)Anima_Tgt()->unTgtAni[21]
            , (int)Anima_Tgt()->unTgtAni[22]
            , (int)Anima_Tgt()->unTgtAni[23]
            , (int)Anima_Tgt()->unTgtAni[24]
            , (int)Anima_Tgt()->unTgtAni[25]
            , (int)Anima_Tgt()->unTgtAni[26]
        );
#endif
    }

    //stop previus animation
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_None;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    //Step 2) Call FUT
    Anima_Cycle10();

    for (j = 0; j < 27; j++)
    {
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], 0u, == );
    }
    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );

    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
        , (int)Anima_Tgt()->unTgtAni[0]
        , (int)Anima_Tgt()->unTgtAni[1]
        , (int)Anima_Tgt()->unTgtAni[2]
        , (int)Anima_Tgt()->unTgtAni[3]
        , (int)Anima_Tgt()->unTgtAni[4]
        , (int)Anima_Tgt()->unTgtAni[5]
        , (int)Anima_Tgt()->unTgtAni[6]
        , (int)Anima_Tgt()->unTgtAni[7]
        , (int)Anima_Tgt()->unTgtAni[8]
        , (int)Anima_Tgt()->unTgtAni[9]
        , (int)Anima_Tgt()->unTgtAni[10]
        , (int)Anima_Tgt()->unTgtAni[11]
        , (int)Anima_Tgt()->unTgtAni[12]
        , (int)Anima_Tgt()->unTgtAni[13]
        , (int)Anima_Tgt()->unTgtAni[14]
        , (int)Anima_Tgt()->unTgtAni[15]
        , (int)Anima_Tgt()->unTgtAni[16]
        , (int)Anima_Tgt()->unTgtAni[17]
        , (int)Anima_Tgt()->unTgtAni[18]
        , (int)Anima_Tgt()->unTgtAni[19]
        , (int)Anima_Tgt()->unTgtAni[20]
        , (int)Anima_Tgt()->unTgtAni[21]
        , (int)Anima_Tgt()->unTgtAni[22]
        , (int)Anima_Tgt()->unTgtAni[23]
        , (int)Anima_Tgt()->unTgtAni[24]
        , (int)Anima_Tgt()->unTgtAni[25]
        , (int)Anima_Tgt()->unTgtAni[26]
    );
#endif

#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Stop();
#endif
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CtrlLed_Cycle10_Dataset0_LockNightExt(void)
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that animation LockNightExt is executed correctly.
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_LockNightExtension;
///
///   - Expectations:
///
/// \output         Anima_Tgt()->unTgtAni[j]   = aExpectedLockExt[i].aunHopt[j]
/// \output         Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_RUNNING
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_Dataset0_LockNightExt(void)
{
    int i, j;
    //Step 1) Set pre-conditions,Assign Input values
    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Start(" Mt_CtrlLed_Cycle10_LockNightExt.txt");
#endif

    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaLockDayNight;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset0_LockExt) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset0_LockExt[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState = eParaFct0_CodingDataValid;

    Mt_CtrlLed_PreTest();
    Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_LockNightExtension;

    for (i = 0; i < 400; i++)
    {
        //Step 2) Call FUT
        Anima_Cycle10();
        for (j = 0; j < 27; j++)
        {
            //Step 3) Check expected output values
            AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], aExpectedLockExt[i].aunHopt[j], == );
        }
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_RUNNING, == );

        //Cfg logging
#if CFG_ENABLE_LOGGING == 1
        Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
            , (int)Anima_Tgt()->unTgtAni[0]
            , (int)Anima_Tgt()->unTgtAni[1]
            , (int)Anima_Tgt()->unTgtAni[2]
            , (int)Anima_Tgt()->unTgtAni[3]
            , (int)Anima_Tgt()->unTgtAni[4]
            , (int)Anima_Tgt()->unTgtAni[5]
            , (int)Anima_Tgt()->unTgtAni[6]
            , (int)Anima_Tgt()->unTgtAni[7]
            , (int)Anima_Tgt()->unTgtAni[8]
            , (int)Anima_Tgt()->unTgtAni[9]
            , (int)Anima_Tgt()->unTgtAni[10]
            , (int)Anima_Tgt()->unTgtAni[11]
            , (int)Anima_Tgt()->unTgtAni[12]
            , (int)Anima_Tgt()->unTgtAni[13]
            , (int)Anima_Tgt()->unTgtAni[14]
            , (int)Anima_Tgt()->unTgtAni[15]
            , (int)Anima_Tgt()->unTgtAni[16]
            , (int)Anima_Tgt()->unTgtAni[17]
            , (int)Anima_Tgt()->unTgtAni[18]
            , (int)Anima_Tgt()->unTgtAni[19]
            , (int)Anima_Tgt()->unTgtAni[20]
            , (int)Anima_Tgt()->unTgtAni[21]
            , (int)Anima_Tgt()->unTgtAni[22]
            , (int)Anima_Tgt()->unTgtAni[23]
            , (int)Anima_Tgt()->unTgtAni[24]
            , (int)Anima_Tgt()->unTgtAni[25]
            , (int)Anima_Tgt()->unTgtAni[26]
        );
#endif
    }

    //stop previus animation
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_None;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    //Step 2) Call FUT
    Anima_Cycle10();

    for (j = 0; j < 27; j++)
    {
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], 0u, == );
    }
    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );

    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
        , (int)Anima_Tgt()->unTgtAni[0]
        , (int)Anima_Tgt()->unTgtAni[1]
        , (int)Anima_Tgt()->unTgtAni[2]
        , (int)Anima_Tgt()->unTgtAni[3]
        , (int)Anima_Tgt()->unTgtAni[4]
        , (int)Anima_Tgt()->unTgtAni[5]
        , (int)Anima_Tgt()->unTgtAni[6]
        , (int)Anima_Tgt()->unTgtAni[7]
        , (int)Anima_Tgt()->unTgtAni[8]
        , (int)Anima_Tgt()->unTgtAni[9]
        , (int)Anima_Tgt()->unTgtAni[10]
        , (int)Anima_Tgt()->unTgtAni[11]
        , (int)Anima_Tgt()->unTgtAni[12]
        , (int)Anima_Tgt()->unTgtAni[13]
        , (int)Anima_Tgt()->unTgtAni[14]
        , (int)Anima_Tgt()->unTgtAni[15]
        , (int)Anima_Tgt()->unTgtAni[16]
        , (int)Anima_Tgt()->unTgtAni[17]
        , (int)Anima_Tgt()->unTgtAni[18]
        , (int)Anima_Tgt()->unTgtAni[19]
        , (int)Anima_Tgt()->unTgtAni[20]
        , (int)Anima_Tgt()->unTgtAni[21]
        , (int)Anima_Tgt()->unTgtAni[22]
        , (int)Anima_Tgt()->unTgtAni[23]
        , (int)Anima_Tgt()->unTgtAni[24]
        , (int)Anima_Tgt()->unTgtAni[25]
        , (int)Anima_Tgt()->unTgtAni[26]
    );
#endif

#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Stop();
#endif
}
//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CtrlLed_Cycle10_Dataset0_LocalizationDay(void)
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that animation LocalizationDay is executed correctly.
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_LocalizationDay;
///
///   - Expectations:
///
/// \output         Anima_Tgt()->unTgtAni[j]   = aExpectedLocalization[i].aunHopt[j]
/// \output         Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_RUNNING
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_Dataset0_LocalizationDay(void)
{
    int i, j;
    //Step 1) Set pre-conditions,Assign Input values
    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Start(" Mt_CtrlLed_Cycle10_LocalizationDay.txt");
#endif

    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaLockDayNight;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset0_Localization) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset0_Localization[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
    Mt_CtrlLed_PreTest();
    Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_LocalizationDay;

    for (i = 0; i < 1000; i++)
    {
        //Step 2) Call FUT
        Anima_Cycle10();
        for (j = 0; j < 27; j++)
        {
            //Step 3) Check expected output values
            AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], aExpectedLocalization[i].aunHopt[j], == );
        }
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_RUNNING, == );

        //Cfg logging
#if CFG_ENABLE_LOGGING == 1
        Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
            , (int)Anima_Tgt()->unTgtAni[0]
            , (int)Anima_Tgt()->unTgtAni[1]
            , (int)Anima_Tgt()->unTgtAni[2]
            , (int)Anima_Tgt()->unTgtAni[3]
            , (int)Anima_Tgt()->unTgtAni[4]
            , (int)Anima_Tgt()->unTgtAni[5]
            , (int)Anima_Tgt()->unTgtAni[6]
            , (int)Anima_Tgt()->unTgtAni[7]
            , (int)Anima_Tgt()->unTgtAni[8]
            , (int)Anima_Tgt()->unTgtAni[9]
            , (int)Anima_Tgt()->unTgtAni[10]
            , (int)Anima_Tgt()->unTgtAni[11]
            , (int)Anima_Tgt()->unTgtAni[12]
            , (int)Anima_Tgt()->unTgtAni[13]
            , (int)Anima_Tgt()->unTgtAni[14]
            , (int)Anima_Tgt()->unTgtAni[15]
            , (int)Anima_Tgt()->unTgtAni[16]
            , (int)Anima_Tgt()->unTgtAni[17]
            , (int)Anima_Tgt()->unTgtAni[18]
            , (int)Anima_Tgt()->unTgtAni[19]
            , (int)Anima_Tgt()->unTgtAni[20]
            , (int)Anima_Tgt()->unTgtAni[21]
            , (int)Anima_Tgt()->unTgtAni[22]
            , (int)Anima_Tgt()->unTgtAni[23]
            , (int)Anima_Tgt()->unTgtAni[24]
            , (int)Anima_Tgt()->unTgtAni[25]
            , (int)Anima_Tgt()->unTgtAni[26]
        );
#endif
    }

    //stop previus animation
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_None;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    //Step 2) Call FUT
    Anima_Cycle10();

    for (j = 0; j < 27; j++)
    {
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], 0u, == );
    }
    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );

    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
        , (int)Anima_Tgt()->unTgtAni[0]
        , (int)Anima_Tgt()->unTgtAni[1]
        , (int)Anima_Tgt()->unTgtAni[2]
        , (int)Anima_Tgt()->unTgtAni[3]
        , (int)Anima_Tgt()->unTgtAni[4]
        , (int)Anima_Tgt()->unTgtAni[5]
        , (int)Anima_Tgt()->unTgtAni[6]
        , (int)Anima_Tgt()->unTgtAni[7]
        , (int)Anima_Tgt()->unTgtAni[8]
        , (int)Anima_Tgt()->unTgtAni[9]
        , (int)Anima_Tgt()->unTgtAni[10]
        , (int)Anima_Tgt()->unTgtAni[11]
        , (int)Anima_Tgt()->unTgtAni[12]
        , (int)Anima_Tgt()->unTgtAni[13]
        , (int)Anima_Tgt()->unTgtAni[14]
        , (int)Anima_Tgt()->unTgtAni[15]
        , (int)Anima_Tgt()->unTgtAni[16]
        , (int)Anima_Tgt()->unTgtAni[17]
        , (int)Anima_Tgt()->unTgtAni[18]
        , (int)Anima_Tgt()->unTgtAni[19]
        , (int)Anima_Tgt()->unTgtAni[20]
        , (int)Anima_Tgt()->unTgtAni[21]
        , (int)Anima_Tgt()->unTgtAni[22]
        , (int)Anima_Tgt()->unTgtAni[23]
        , (int)Anima_Tgt()->unTgtAni[24]
        , (int)Anima_Tgt()->unTgtAni[25]
        , (int)Anima_Tgt()->unTgtAni[26]
    );
#endif

#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Stop();
#endif
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CtrlLed_Cycle10_Dataset0_LocalizationNight(void)
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that animation LocalizationNight is executed correctly.
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_LocalizationNight;
///
///   - Expectations:
///
/// \output         Anima_Tgt()->unTgtAni[j]   = aExpectedLocalization[i].aunHopt[j]
/// \output         Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_RUNNING
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_Dataset0_LocalizationNight(void)
{
    int i, j;
    //Step 1) Set pre-conditions,Assign Input values

    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Start(" Mt_CtrlLed_Cycle10_LocalizationNight.txt");
#endif
    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaLockDayNight;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset0_Localization) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset0_Localization[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;

    Mt_CtrlLed_PreTest();
    Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_LocalizationNight;

    for (i = 0; i < 1000; i++)
    {
        //Step 2) Call FUT
        Anima_Cycle10();
        for (j = 0; j < 27; j++)
        {
            //Step 3) Check expected output values
            AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], aExpectedLocalization[i].aunHopt[j], == );
        }
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_RUNNING, == );

        //Cfg logging
#if CFG_ENABLE_LOGGING == 1
        Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
            , (int)Anima_Tgt()->unTgtAni[0]
            , (int)Anima_Tgt()->unTgtAni[1]
            , (int)Anima_Tgt()->unTgtAni[2]
            , (int)Anima_Tgt()->unTgtAni[3]
            , (int)Anima_Tgt()->unTgtAni[4]
            , (int)Anima_Tgt()->unTgtAni[5]
            , (int)Anima_Tgt()->unTgtAni[6]
            , (int)Anima_Tgt()->unTgtAni[7]
            , (int)Anima_Tgt()->unTgtAni[8]
            , (int)Anima_Tgt()->unTgtAni[9]
            , (int)Anima_Tgt()->unTgtAni[10]
            , (int)Anima_Tgt()->unTgtAni[11]
            , (int)Anima_Tgt()->unTgtAni[12]
            , (int)Anima_Tgt()->unTgtAni[13]
            , (int)Anima_Tgt()->unTgtAni[14]
            , (int)Anima_Tgt()->unTgtAni[15]
            , (int)Anima_Tgt()->unTgtAni[16]
            , (int)Anima_Tgt()->unTgtAni[17]
            , (int)Anima_Tgt()->unTgtAni[18]
            , (int)Anima_Tgt()->unTgtAni[19]
            , (int)Anima_Tgt()->unTgtAni[20]
            , (int)Anima_Tgt()->unTgtAni[21]
            , (int)Anima_Tgt()->unTgtAni[22]
            , (int)Anima_Tgt()->unTgtAni[23]
            , (int)Anima_Tgt()->unTgtAni[24]
            , (int)Anima_Tgt()->unTgtAni[25]
            , (int)Anima_Tgt()->unTgtAni[26]
        );
#endif
    }

    //stop previus animation
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_None;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    //Step 2) Call FUT
    Anima_Cycle10();

    for (j = 0; j < 27; j++)
    {
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], 0u, == );
    }
    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );

    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
        , (int)Anima_Tgt()->unTgtAni[0]
        , (int)Anima_Tgt()->unTgtAni[1]
        , (int)Anima_Tgt()->unTgtAni[2]
        , (int)Anima_Tgt()->unTgtAni[3]
        , (int)Anima_Tgt()->unTgtAni[4]
        , (int)Anima_Tgt()->unTgtAni[5]
        , (int)Anima_Tgt()->unTgtAni[6]
        , (int)Anima_Tgt()->unTgtAni[7]
        , (int)Anima_Tgt()->unTgtAni[8]
        , (int)Anima_Tgt()->unTgtAni[9]
        , (int)Anima_Tgt()->unTgtAni[10]
        , (int)Anima_Tgt()->unTgtAni[11]
        , (int)Anima_Tgt()->unTgtAni[12]
        , (int)Anima_Tgt()->unTgtAni[13]
        , (int)Anima_Tgt()->unTgtAni[14]
        , (int)Anima_Tgt()->unTgtAni[15]
        , (int)Anima_Tgt()->unTgtAni[16]
        , (int)Anima_Tgt()->unTgtAni[17]
        , (int)Anima_Tgt()->unTgtAni[18]
        , (int)Anima_Tgt()->unTgtAni[19]
        , (int)Anima_Tgt()->unTgtAni[20]
        , (int)Anima_Tgt()->unTgtAni[21]
        , (int)Anima_Tgt()->unTgtAni[22]
        , (int)Anima_Tgt()->unTgtAni[23]
        , (int)Anima_Tgt()->unTgtAni[24]
        , (int)Anima_Tgt()->unTgtAni[25]
        , (int)Anima_Tgt()->unTgtAni[26]
    );
#endif

#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Stop();
#endif
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Cycle10_Dataset0_ByeByeDay
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that animation ByeByeDay is executed and stopped correctly.
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input               Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input               Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input               Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_ByeByeDay;
///
///   - Expectations:
///
/// \output         Anima_Tgt()->unTgtAni[j]   = aExpectedBB[i].aunHopt[j]
/// \output         Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_RUNNING
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_Dataset0_ByeByeDay(void)
{
    int i, j;
    //Step 1) Set pre-conditions,Assign Input values

    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Start(" Mt_CtrlLed_Cycle10_ByeByeDay.txt");
#endif

    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaBye;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset0_Bye) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset0_Bye[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_ByeByeDay;

    for (i = 0; i < 500; i++)
    {
        //Step 2) Call FUT
        Anima_Cycle10();
        for (j = 0; j < 27; j++)
        {
            //Step 3) Check expected output values
            AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], aExpectedBB[i].aunHopt[j], == );
        }
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_RUNNING, == );

        //Cfg logging
#if CFG_ENABLE_LOGGING == 1
        Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
            , (int)Anima_Tgt()->unTgtAni[0]
            , (int)Anima_Tgt()->unTgtAni[1]
            , (int)Anima_Tgt()->unTgtAni[2]
            , (int)Anima_Tgt()->unTgtAni[3]
            , (int)Anima_Tgt()->unTgtAni[4]
            , (int)Anima_Tgt()->unTgtAni[5]
            , (int)Anima_Tgt()->unTgtAni[6]
            , (int)Anima_Tgt()->unTgtAni[7]
            , (int)Anima_Tgt()->unTgtAni[8]
            , (int)Anima_Tgt()->unTgtAni[9]
            , (int)Anima_Tgt()->unTgtAni[10]
            , (int)Anima_Tgt()->unTgtAni[11]
            , (int)Anima_Tgt()->unTgtAni[12]
            , (int)Anima_Tgt()->unTgtAni[13]
            , (int)Anima_Tgt()->unTgtAni[14]
            , (int)Anima_Tgt()->unTgtAni[15]
            , (int)Anima_Tgt()->unTgtAni[16]
            , (int)Anima_Tgt()->unTgtAni[17]
            , (int)Anima_Tgt()->unTgtAni[18]
            , (int)Anima_Tgt()->unTgtAni[19]
            , (int)Anima_Tgt()->unTgtAni[20]
            , (int)Anima_Tgt()->unTgtAni[21]
            , (int)Anima_Tgt()->unTgtAni[22]
            , (int)Anima_Tgt()->unTgtAni[23]
            , (int)Anima_Tgt()->unTgtAni[24]
            , (int)Anima_Tgt()->unTgtAni[25]
            , (int)Anima_Tgt()->unTgtAni[26]
        );
#endif
    }

    //stop previus animation
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_None;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    //Step 2) Call FUT
    Anima_Cycle10();

    for (j = 0; j < 27; j++)
    {
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], 0u, == );
    }
    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );

    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
        , (int)Anima_Tgt()->unTgtAni[0]
        , (int)Anima_Tgt()->unTgtAni[1]
        , (int)Anima_Tgt()->unTgtAni[2]
        , (int)Anima_Tgt()->unTgtAni[3]
        , (int)Anima_Tgt()->unTgtAni[4]
        , (int)Anima_Tgt()->unTgtAni[5]
        , (int)Anima_Tgt()->unTgtAni[6]
        , (int)Anima_Tgt()->unTgtAni[7]
        , (int)Anima_Tgt()->unTgtAni[8]
        , (int)Anima_Tgt()->unTgtAni[9]
        , (int)Anima_Tgt()->unTgtAni[10]
        , (int)Anima_Tgt()->unTgtAni[11]
        , (int)Anima_Tgt()->unTgtAni[12]
        , (int)Anima_Tgt()->unTgtAni[13]
        , (int)Anima_Tgt()->unTgtAni[14]
        , (int)Anima_Tgt()->unTgtAni[15]
        , (int)Anima_Tgt()->unTgtAni[16]
        , (int)Anima_Tgt()->unTgtAni[17]
        , (int)Anima_Tgt()->unTgtAni[18]
        , (int)Anima_Tgt()->unTgtAni[19]
        , (int)Anima_Tgt()->unTgtAni[20]
        , (int)Anima_Tgt()->unTgtAni[21]
        , (int)Anima_Tgt()->unTgtAni[22]
        , (int)Anima_Tgt()->unTgtAni[23]
        , (int)Anima_Tgt()->unTgtAni[24]
        , (int)Anima_Tgt()->unTgtAni[25]
        , (int)Anima_Tgt()->unTgtAni[26]
    );
#endif

#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Stop();
#endif
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Cycle10_Dataset0_ByeByeNight
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that animation ByeByeNight is executed and stopped correctly.
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input               Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input               Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input               Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_ByeByeNight;
///
///   - Expectations:
///
/// \output         Anima_Tgt()->unTgtAni[j]   = aExpectedBB[i].aunHopt[j]
/// \output         Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_RUNNING
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_Dataset0_ByeByeNight(void)
{
    int i, j;
    //Step 1) Set pre-conditions,Assign Input values

    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Start(" Mt_CtrlLed_Cycle10_ByeByeNight.txt");
#endif

    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaBye;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset0_Bye) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset0_Bye[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_ByeByeNight;

    //1000 iterations for the total time set on run block : t =2s
    for (i = 0; i < 500; i++)
    {
        //Step 2) Call FUT
        Anima_Cycle10();
        for (j = 0; j < 27; j++)//number of pixels
        {
            //Step 3) Check expected output values
            AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], aExpectedBB[i].aunHopt[j], == );
        }
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_RUNNING, == );

        //Cfg logging
#if CFG_ENABLE_LOGGING == 1
        Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
            , (int)Anima_Tgt()->unTgtAni[0]
            , (int)Anima_Tgt()->unTgtAni[1]
            , (int)Anima_Tgt()->unTgtAni[2]
            , (int)Anima_Tgt()->unTgtAni[3]
            , (int)Anima_Tgt()->unTgtAni[4]
            , (int)Anima_Tgt()->unTgtAni[5]
            , (int)Anima_Tgt()->unTgtAni[6]
            , (int)Anima_Tgt()->unTgtAni[7]
            , (int)Anima_Tgt()->unTgtAni[8]
            , (int)Anima_Tgt()->unTgtAni[9]
            , (int)Anima_Tgt()->unTgtAni[10]
            , (int)Anima_Tgt()->unTgtAni[11]
            , (int)Anima_Tgt()->unTgtAni[12]
            , (int)Anima_Tgt()->unTgtAni[13]
            , (int)Anima_Tgt()->unTgtAni[14]
            , (int)Anima_Tgt()->unTgtAni[15]
            , (int)Anima_Tgt()->unTgtAni[16]
            , (int)Anima_Tgt()->unTgtAni[17]
            , (int)Anima_Tgt()->unTgtAni[18]
            , (int)Anima_Tgt()->unTgtAni[19]
            , (int)Anima_Tgt()->unTgtAni[20]
            , (int)Anima_Tgt()->unTgtAni[21]
            , (int)Anima_Tgt()->unTgtAni[22]
            , (int)Anima_Tgt()->unTgtAni[23]
            , (int)Anima_Tgt()->unTgtAni[24]
            , (int)Anima_Tgt()->unTgtAni[25]
            , (int)Anima_Tgt()->unTgtAni[26]
        );
#endif
    }

    //stop previus animation
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_None;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    //Step 2) Call FUT
    Anima_Cycle10();

    for (j = 0; j < 27; j++)
    {
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], 0u, == );
    }
    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );

    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
        , (int)Anima_Tgt()->unTgtAni[0]
        , (int)Anima_Tgt()->unTgtAni[1]
        , (int)Anima_Tgt()->unTgtAni[2]
        , (int)Anima_Tgt()->unTgtAni[3]
        , (int)Anima_Tgt()->unTgtAni[4]
        , (int)Anima_Tgt()->unTgtAni[5]
        , (int)Anima_Tgt()->unTgtAni[6]
        , (int)Anima_Tgt()->unTgtAni[7]
        , (int)Anima_Tgt()->unTgtAni[8]
        , (int)Anima_Tgt()->unTgtAni[9]
        , (int)Anima_Tgt()->unTgtAni[10]
        , (int)Anima_Tgt()->unTgtAni[11]
        , (int)Anima_Tgt()->unTgtAni[12]
        , (int)Anima_Tgt()->unTgtAni[13]
        , (int)Anima_Tgt()->unTgtAni[14]
        , (int)Anima_Tgt()->unTgtAni[15]
        , (int)Anima_Tgt()->unTgtAni[16]
        , (int)Anima_Tgt()->unTgtAni[17]
        , (int)Anima_Tgt()->unTgtAni[18]
        , (int)Anima_Tgt()->unTgtAni[19]
        , (int)Anima_Tgt()->unTgtAni[20]
        , (int)Anima_Tgt()->unTgtAni[21]
        , (int)Anima_Tgt()->unTgtAni[22]
        , (int)Anima_Tgt()->unTgtAni[23]
        , (int)Anima_Tgt()->unTgtAni[24]
        , (int)Anima_Tgt()->unTgtAni[25]
        , (int)Anima_Tgt()->unTgtAni[26]
    );
#endif

#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Stop();
#endif
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Cycle10_Dataset0_EndNightByeBye
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that animation EndNightByeBye is executed and stopped correctly.
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input               Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input               Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input               Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_EndNightByeBye;
///
///   - Expectations:
///
/// \output         Anima_Tgt()->unTgtAni[j]   = aExpectedBB[i].aunHopt[j]
/// \output         Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_RUNNING
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_Dataset0_EndNightByeBye(void)
{
    int i, j;
    //Step 1) Set pre-conditions,Assign Input values

    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Start(" Mt_CtrlLed_Cycle10_EndNightByeBye.txt");
#endif

    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaBye;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset0_Bye) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset0_Bye[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
    Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_EndNightByeBye;

    for (i = 0; i < 500; i++)
    {
        //Step 2) Call FUT
        Anima_Cycle10();
        for (j = 0; j < 27; j++)//number of pixels
        {
            //Step 3) Check expected output values
            AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], aExpectedBB[i].aunHopt[j], == );
        }
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_RUNNING, == );

        //Cfg logging
#if CFG_ENABLE_LOGGING == 1
        Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
            , (int)Anima_Tgt()->unTgtAni[0]
            , (int)Anima_Tgt()->unTgtAni[1]
            , (int)Anima_Tgt()->unTgtAni[2]
            , (int)Anima_Tgt()->unTgtAni[3]
            , (int)Anima_Tgt()->unTgtAni[4]
            , (int)Anima_Tgt()->unTgtAni[5]
            , (int)Anima_Tgt()->unTgtAni[6]
            , (int)Anima_Tgt()->unTgtAni[7]
            , (int)Anima_Tgt()->unTgtAni[8]
            , (int)Anima_Tgt()->unTgtAni[9]
            , (int)Anima_Tgt()->unTgtAni[10]
            , (int)Anima_Tgt()->unTgtAni[11]
            , (int)Anima_Tgt()->unTgtAni[12]
            , (int)Anima_Tgt()->unTgtAni[13]
            , (int)Anima_Tgt()->unTgtAni[14]
            , (int)Anima_Tgt()->unTgtAni[15]
            , (int)Anima_Tgt()->unTgtAni[16]
            , (int)Anima_Tgt()->unTgtAni[17]
            , (int)Anima_Tgt()->unTgtAni[18]
            , (int)Anima_Tgt()->unTgtAni[19]
            , (int)Anima_Tgt()->unTgtAni[20]
            , (int)Anima_Tgt()->unTgtAni[21]
            , (int)Anima_Tgt()->unTgtAni[22]
            , (int)Anima_Tgt()->unTgtAni[23]
            , (int)Anima_Tgt()->unTgtAni[24]
            , (int)Anima_Tgt()->unTgtAni[25]
            , (int)Anima_Tgt()->unTgtAni[26]
        );
#endif
    }

    //stop previus animation
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_None;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    //Step 2) Call FUT
    Anima_Cycle10();

    for (j = 0; j < 27; j++)
    {
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], 0u, == );
    }
    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );

    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
        , (int)Anima_Tgt()->unTgtAni[0]
        , (int)Anima_Tgt()->unTgtAni[1]
        , (int)Anima_Tgt()->unTgtAni[2]
        , (int)Anima_Tgt()->unTgtAni[3]
        , (int)Anima_Tgt()->unTgtAni[4]
        , (int)Anima_Tgt()->unTgtAni[5]
        , (int)Anima_Tgt()->unTgtAni[6]
        , (int)Anima_Tgt()->unTgtAni[7]
        , (int)Anima_Tgt()->unTgtAni[8]
        , (int)Anima_Tgt()->unTgtAni[9]
        , (int)Anima_Tgt()->unTgtAni[10]
        , (int)Anima_Tgt()->unTgtAni[11]
        , (int)Anima_Tgt()->unTgtAni[12]
        , (int)Anima_Tgt()->unTgtAni[13]
        , (int)Anima_Tgt()->unTgtAni[14]
        , (int)Anima_Tgt()->unTgtAni[15]
        , (int)Anima_Tgt()->unTgtAni[16]
        , (int)Anima_Tgt()->unTgtAni[17]
        , (int)Anima_Tgt()->unTgtAni[18]
        , (int)Anima_Tgt()->unTgtAni[19]
        , (int)Anima_Tgt()->unTgtAni[20]
        , (int)Anima_Tgt()->unTgtAni[21]
        , (int)Anima_Tgt()->unTgtAni[22]
        , (int)Anima_Tgt()->unTgtAni[23]
        , (int)Anima_Tgt()->unTgtAni[24]
        , (int)Anima_Tgt()->unTgtAni[25]
        , (int)Anima_Tgt()->unTgtAni[26]
    );
#endif

#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Stop();
#endif
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Cycle10_Dataset0_FMH15
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that FMH15 works
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_Fmh;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eDelayFmh                   = eDelayFmh_15Seconds;
/// \input           Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
///
///   - Expectations:
///
/// \output         Anima_Tgt()->unTgtAni[j]   = aExpectedFMH15[i].aunHopt[j]
/// \output         Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_RUNNING
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_Dataset0_FMH15(void)
{
    int i, j;
    //Step 1) Set pre-conditions,Assign Input values
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Start(" Mt_CtrlLed_Cycle10_FMH15.txt");
#endif

    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaFMH;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset0_FMH) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset0_FMH[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
    Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
    Mt_CtrlLed_PreTest();
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_Fmh;
    Rte_Read_SigPrep_AnimationReq_Param1.eDelayFmh                   = eDelayFmh_15Seconds;

    for (i = 0; i < 1500; i++)
    {
        //Step 2) Call FUT
        Anima_Cycle10();
        for (j = 0; j < 27; j++)
        {
            //Step 3) Check expected output values
            AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], aExpectedFMH15[i].aunHopt[j], == );
        }
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_RUNNING, == );

#if CFG_ENABLE_LOGGING == 1
        Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
            , (int)Anima_Tgt()->unTgtAni[0]
            , (int)Anima_Tgt()->unTgtAni[1]
            , (int)Anima_Tgt()->unTgtAni[2]
            , (int)Anima_Tgt()->unTgtAni[3]
            , (int)Anima_Tgt()->unTgtAni[4]
            , (int)Anima_Tgt()->unTgtAni[5]
            , (int)Anima_Tgt()->unTgtAni[6]
            , (int)Anima_Tgt()->unTgtAni[7]
            , (int)Anima_Tgt()->unTgtAni[8]
            , (int)Anima_Tgt()->unTgtAni[9]
            , (int)Anima_Tgt()->unTgtAni[10]
            , (int)Anima_Tgt()->unTgtAni[11]
            , (int)Anima_Tgt()->unTgtAni[12]
            , (int)Anima_Tgt()->unTgtAni[13]
            , (int)Anima_Tgt()->unTgtAni[14]
            , (int)Anima_Tgt()->unTgtAni[15]
            , (int)Anima_Tgt()->unTgtAni[16]
            , (int)Anima_Tgt()->unTgtAni[17]
            , (int)Anima_Tgt()->unTgtAni[18]
            , (int)Anima_Tgt()->unTgtAni[19]
            , (int)Anima_Tgt()->unTgtAni[20]
            , (int)Anima_Tgt()->unTgtAni[21]
            , (int)Anima_Tgt()->unTgtAni[22]
            , (int)Anima_Tgt()->unTgtAni[23]
            , (int)Anima_Tgt()->unTgtAni[24]
            , (int)Anima_Tgt()->unTgtAni[25]
            , (int)Anima_Tgt()->unTgtAni[26]
        );
#endif
    }

    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_None;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    //Step 2) Call FUT
    Anima_Cycle10();

    for (j = 0; j < 27; j++)
    {
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], 0u, == );
    }
    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );

#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
        , (int)Anima_Tgt()->unTgtAni[0]
        , (int)Anima_Tgt()->unTgtAni[1]
        , (int)Anima_Tgt()->unTgtAni[2]
        , (int)Anima_Tgt()->unTgtAni[3]
        , (int)Anima_Tgt()->unTgtAni[4]
        , (int)Anima_Tgt()->unTgtAni[5]
        , (int)Anima_Tgt()->unTgtAni[6]
        , (int)Anima_Tgt()->unTgtAni[7]
        , (int)Anima_Tgt()->unTgtAni[8]
        , (int)Anima_Tgt()->unTgtAni[9]
        , (int)Anima_Tgt()->unTgtAni[10]
        , (int)Anima_Tgt()->unTgtAni[11]
        , (int)Anima_Tgt()->unTgtAni[12]
        , (int)Anima_Tgt()->unTgtAni[13]
        , (int)Anima_Tgt()->unTgtAni[14]
        , (int)Anima_Tgt()->unTgtAni[15]
        , (int)Anima_Tgt()->unTgtAni[16]
        , (int)Anima_Tgt()->unTgtAni[17]
        , (int)Anima_Tgt()->unTgtAni[18]
        , (int)Anima_Tgt()->unTgtAni[19]
        , (int)Anima_Tgt()->unTgtAni[20]
        , (int)Anima_Tgt()->unTgtAni[21]
        , (int)Anima_Tgt()->unTgtAni[22]
        , (int)Anima_Tgt()->unTgtAni[23]
        , (int)Anima_Tgt()->unTgtAni[24]
        , (int)Anima_Tgt()->unTgtAni[25]
        , (int)Anima_Tgt()->unTgtAni[26]
    );
#endif

#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Stop();
#endif
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Cycle10_Dataset0_FMH30
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that FMH30 works
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_Fmh;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eDelayFmh                   = eDelayFmh_30Seconds;
///
///   - Expectations:
///
/// \output         Anima_Tgt()->unTgtAni[j]   = aExpectedFMH30[i].aunHopt[j]
/// \output         Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_RUNNING
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_Dataset0_FMH30(void)
{
    int i, j;
    //Step 1) Set pre-conditions,Assign Input values
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Start(" Mt_CtrlLed_Cycle10_FMH30.txt");
#endif

    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaFMH30;
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset0_FMH30) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset0_FMH30[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                      = eParaFct0_CodingDataValid;
    Mt_CtrlLed_PreTest();
    Rte_Read_IoHwAbUser_GetMountingSide_Param1                        = eMountedLeft;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                      = SIG_VALID;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl  = eExtLightingAnimationReq_Fmh;
    Rte_Read_SigPrep_AnimationReq_Param1.eDelayFmh                    = eDelayFmh_30Seconds;
    for (i = 0; i < 3000; i++)
    {
        //Step 2) Call FUT
        Anima_Cycle10();
        for (j = 0; j < 27; j++)
        {
            //Step 3) Check expected output values
            AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], aExpectedFMH30[i].aunHopt[j], == );
        }
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_RUNNING, == );

#if CFG_ENABLE_LOGGING == 1
        Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
            , (int)Anima_Tgt()->unTgtAni[0]
            , (int)Anima_Tgt()->unTgtAni[1]
            , (int)Anima_Tgt()->unTgtAni[2]
            , (int)Anima_Tgt()->unTgtAni[3]
            , (int)Anima_Tgt()->unTgtAni[4]
            , (int)Anima_Tgt()->unTgtAni[5]
            , (int)Anima_Tgt()->unTgtAni[6]
            , (int)Anima_Tgt()->unTgtAni[7]
            , (int)Anima_Tgt()->unTgtAni[8]
            , (int)Anima_Tgt()->unTgtAni[9]
            , (int)Anima_Tgt()->unTgtAni[10]
            , (int)Anima_Tgt()->unTgtAni[11]
            , (int)Anima_Tgt()->unTgtAni[12]
            , (int)Anima_Tgt()->unTgtAni[13]
            , (int)Anima_Tgt()->unTgtAni[14]
            , (int)Anima_Tgt()->unTgtAni[15]
            , (int)Anima_Tgt()->unTgtAni[16]
            , (int)Anima_Tgt()->unTgtAni[17]
            , (int)Anima_Tgt()->unTgtAni[18]
            , (int)Anima_Tgt()->unTgtAni[19]
            , (int)Anima_Tgt()->unTgtAni[20]
            , (int)Anima_Tgt()->unTgtAni[21]
            , (int)Anima_Tgt()->unTgtAni[22]
            , (int)Anima_Tgt()->unTgtAni[23]
            , (int)Anima_Tgt()->unTgtAni[24]
            , (int)Anima_Tgt()->unTgtAni[25]
            , (int)Anima_Tgt()->unTgtAni[26]
        );
#endif
    }

    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_None;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    //Step 2) Call FUT
    Anima_Cycle10();

    for (j = 0; j < 27; j++)
    {
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], 0u, == );
    }
    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );

#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
        , (int)Anima_Tgt()->unTgtAni[0]
        , (int)Anima_Tgt()->unTgtAni[1]
        , (int)Anima_Tgt()->unTgtAni[2]
        , (int)Anima_Tgt()->unTgtAni[3]
        , (int)Anima_Tgt()->unTgtAni[4]
        , (int)Anima_Tgt()->unTgtAni[5]
        , (int)Anima_Tgt()->unTgtAni[6]
        , (int)Anima_Tgt()->unTgtAni[7]
        , (int)Anima_Tgt()->unTgtAni[8]
        , (int)Anima_Tgt()->unTgtAni[9]
        , (int)Anima_Tgt()->unTgtAni[10]
        , (int)Anima_Tgt()->unTgtAni[11]
        , (int)Anima_Tgt()->unTgtAni[12]
        , (int)Anima_Tgt()->unTgtAni[13]
        , (int)Anima_Tgt()->unTgtAni[14]
        , (int)Anima_Tgt()->unTgtAni[15]
        , (int)Anima_Tgt()->unTgtAni[16]
        , (int)Anima_Tgt()->unTgtAni[17]
        , (int)Anima_Tgt()->unTgtAni[18]
        , (int)Anima_Tgt()->unTgtAni[19]
        , (int)Anima_Tgt()->unTgtAni[20]
        , (int)Anima_Tgt()->unTgtAni[21]
        , (int)Anima_Tgt()->unTgtAni[22]
        , (int)Anima_Tgt()->unTgtAni[23]
        , (int)Anima_Tgt()->unTgtAni[24]
        , (int)Anima_Tgt()->unTgtAni[25]
        , (int)Anima_Tgt()->unTgtAni[26]
    );
#endif

#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Stop();
#endif
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Cycle10_Dataset0_FMH60_TestCase1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that FMH60 works
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_Fmh;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eDelayFmh                   = eDelayFmh_60Seconds;
///
///   - Expectations:
///
/// \output         Anima_Tgt()->unTgtAni[j]   = aExpectedFMH60[i].aunHopt[j]
/// \output         Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_RUNNING
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_Dataset0_FMH60_TestCase1(void)
{
    int i, j;

    //Step 1) Set pre-conditions,Assign Input values
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Start(" Mt_CtrlLed_Cycle10_FMH60.txt");
#endif

    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaFMH60;
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset0_FMH60) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset0_FMH60[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState = eParaFct0_CodingDataValid;
    Mt_CtrlLed_PreTest();
    Rte_Read_IoHwAbUser_GetMountingSide_Param1   = eMountedLeft;
    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );

    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_Fmh;
    Rte_Read_SigPrep_AnimationReq_Param1.eDelayFmh                   = eDelayFmh_60Seconds;

    for (i = 0; i < 6000; i++)
    {
        //Step 2) Call FUT
        Anima_Cycle10();
        for (j = 0; j < 27; j++)
        {
            //Step 3) Check expected output values
            AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], aExpectedFMH60[i].aunHopt[j], == );
        }
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_RUNNING, == );

#if CFG_ENABLE_LOGGING == 1
        Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
            , (int)Anima_Tgt()->unTgtAni[0]
            , (int)Anima_Tgt()->unTgtAni[1]
            , (int)Anima_Tgt()->unTgtAni[2]
            , (int)Anima_Tgt()->unTgtAni[3]
            , (int)Anima_Tgt()->unTgtAni[4]
            , (int)Anima_Tgt()->unTgtAni[5]
            , (int)Anima_Tgt()->unTgtAni[6]
            , (int)Anima_Tgt()->unTgtAni[7]
            , (int)Anima_Tgt()->unTgtAni[8]
            , (int)Anima_Tgt()->unTgtAni[9]
            , (int)Anima_Tgt()->unTgtAni[10]
            , (int)Anima_Tgt()->unTgtAni[11]
            , (int)Anima_Tgt()->unTgtAni[12]
            , (int)Anima_Tgt()->unTgtAni[13]
            , (int)Anima_Tgt()->unTgtAni[14]
            , (int)Anima_Tgt()->unTgtAni[15]
            , (int)Anima_Tgt()->unTgtAni[16]
            , (int)Anima_Tgt()->unTgtAni[17]
            , (int)Anima_Tgt()->unTgtAni[18]
            , (int)Anima_Tgt()->unTgtAni[19]
            , (int)Anima_Tgt()->unTgtAni[20]
            , (int)Anima_Tgt()->unTgtAni[21]
            , (int)Anima_Tgt()->unTgtAni[22]
            , (int)Anima_Tgt()->unTgtAni[23]
            , (int)Anima_Tgt()->unTgtAni[24]
            , (int)Anima_Tgt()->unTgtAni[25]
            , (int)Anima_Tgt()->unTgtAni[26]
        );
#endif
    }

    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_None;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    //Step 2) Call FUT
    Anima_Cycle10();

    for (j = 0; j < 27; j++)
    {
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], 0u, == );
    }
    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );

#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
        , (int)Anima_Tgt()->unTgtAni[0]
        , (int)Anima_Tgt()->unTgtAni[1]
        , (int)Anima_Tgt()->unTgtAni[2]
        , (int)Anima_Tgt()->unTgtAni[3]
        , (int)Anima_Tgt()->unTgtAni[4]
        , (int)Anima_Tgt()->unTgtAni[5]
        , (int)Anima_Tgt()->unTgtAni[6]
        , (int)Anima_Tgt()->unTgtAni[7]
        , (int)Anima_Tgt()->unTgtAni[8]
        , (int)Anima_Tgt()->unTgtAni[9]
        , (int)Anima_Tgt()->unTgtAni[10]
        , (int)Anima_Tgt()->unTgtAni[11]
        , (int)Anima_Tgt()->unTgtAni[12]
        , (int)Anima_Tgt()->unTgtAni[13]
        , (int)Anima_Tgt()->unTgtAni[14]
        , (int)Anima_Tgt()->unTgtAni[15]
        , (int)Anima_Tgt()->unTgtAni[16]
        , (int)Anima_Tgt()->unTgtAni[17]
        , (int)Anima_Tgt()->unTgtAni[18]
        , (int)Anima_Tgt()->unTgtAni[19]
        , (int)Anima_Tgt()->unTgtAni[20]
        , (int)Anima_Tgt()->unTgtAni[21]
        , (int)Anima_Tgt()->unTgtAni[22]
        , (int)Anima_Tgt()->unTgtAni[23]
        , (int)Anima_Tgt()->unTgtAni[24]
        , (int)Anima_Tgt()->unTgtAni[25]
        , (int)Anima_Tgt()->unTgtAni[26]
    );
#endif

#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Stop();
#endif
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Cycle10_Dataset0_FMH60_TestCase2
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that eDelayFmh_NotUsed is working 
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_Fmh;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eDelayFmh                   = eDelayFmh_NotUsed;
///
///   - Expectations:
///
/// \output         Anima_Tgt()->unTgtAni[j]   = aExpectedFMH60_2[i].aunHopt[j]
/// \output         Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_RUNNING
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_Dataset0_FMH60_TestCase2(void)
{
    int i, j;
    //Step 1) Set pre-conditions,Assign Input values
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Start(" Mt_CtrlLed_Cycle10_FMH60def.txt");
#endif

    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaFMH60;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset0_FMH60) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset0_FMH60[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
    Mt_CtrlLed_PreTest();
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_Fmh;
    Rte_Read_SigPrep_AnimationReq_Param1.eDelayFmh                   = eDelayFmh_NotUsed;
    for (i = 0; i < 6000; i++)
    {
        //Step 2) Call FUT
        Anima_Cycle10();
        for (j = 0; j < 27; j++)
        {
            //Step 3) Check expected output values
            AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], aExpectedFMH60_2[i].aunHopt[j], == );
        }
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );

#if CFG_ENABLE_LOGGING == 1
        Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
            , (int)Anima_Tgt()->unTgtAni[0]
            , (int)Anima_Tgt()->unTgtAni[1]
            , (int)Anima_Tgt()->unTgtAni[2]
            , (int)Anima_Tgt()->unTgtAni[3]
            , (int)Anima_Tgt()->unTgtAni[4]
            , (int)Anima_Tgt()->unTgtAni[5]
            , (int)Anima_Tgt()->unTgtAni[6]
            , (int)Anima_Tgt()->unTgtAni[7]
            , (int)Anima_Tgt()->unTgtAni[8]
            , (int)Anima_Tgt()->unTgtAni[9]
            , (int)Anima_Tgt()->unTgtAni[10]
            , (int)Anima_Tgt()->unTgtAni[11]
            , (int)Anima_Tgt()->unTgtAni[12]
            , (int)Anima_Tgt()->unTgtAni[13]
            , (int)Anima_Tgt()->unTgtAni[14]
            , (int)Anima_Tgt()->unTgtAni[15]
            , (int)Anima_Tgt()->unTgtAni[16]
            , (int)Anima_Tgt()->unTgtAni[17]
            , (int)Anima_Tgt()->unTgtAni[18]
            , (int)Anima_Tgt()->unTgtAni[19]
            , (int)Anima_Tgt()->unTgtAni[20]
            , (int)Anima_Tgt()->unTgtAni[21]
            , (int)Anima_Tgt()->unTgtAni[22]
            , (int)Anima_Tgt()->unTgtAni[23]
            , (int)Anima_Tgt()->unTgtAni[24]
            , (int)Anima_Tgt()->unTgtAni[25]
            , (int)Anima_Tgt()->unTgtAni[26]
        );
#endif
    }

    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_None;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    //Step 2) Call FUT
    Anima_Cycle10();

    for (j = 0; j < 27; j++)
    {
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], 0u, == );
    }
    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );

#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
        , (int)Anima_Tgt()->unTgtAni[0]
        , (int)Anima_Tgt()->unTgtAni[1]
        , (int)Anima_Tgt()->unTgtAni[2]
        , (int)Anima_Tgt()->unTgtAni[3]
        , (int)Anima_Tgt()->unTgtAni[4]
        , (int)Anima_Tgt()->unTgtAni[5]
        , (int)Anima_Tgt()->unTgtAni[6]
        , (int)Anima_Tgt()->unTgtAni[7]
        , (int)Anima_Tgt()->unTgtAni[8]
        , (int)Anima_Tgt()->unTgtAni[9]
        , (int)Anima_Tgt()->unTgtAni[10]
        , (int)Anima_Tgt()->unTgtAni[11]
        , (int)Anima_Tgt()->unTgtAni[12]
        , (int)Anima_Tgt()->unTgtAni[13]
        , (int)Anima_Tgt()->unTgtAni[14]
        , (int)Anima_Tgt()->unTgtAni[15]
        , (int)Anima_Tgt()->unTgtAni[16]
        , (int)Anima_Tgt()->unTgtAni[17]
        , (int)Anima_Tgt()->unTgtAni[18]
        , (int)Anima_Tgt()->unTgtAni[19]
        , (int)Anima_Tgt()->unTgtAni[20]
        , (int)Anima_Tgt()->unTgtAni[21]
        , (int)Anima_Tgt()->unTgtAni[22]
        , (int)Anima_Tgt()->unTgtAni[23]
        , (int)Anima_Tgt()->unTgtAni[24]
        , (int)Anima_Tgt()->unTgtAni[25]
        , (int)Anima_Tgt()->unTgtAni[26]
    );
#endif

#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Stop();
#endif
}
//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CtrlLed_Cycle10_ShowroomEvent(void)
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that animation ShowroomEvent is executed correctly.
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           sTimeWarp.ulTimeOffset                                           = 0U;
/// \input           sTimeWarp.bInitContext                                           = false;
/// \input           sTimeWarp.ucInitContextCnt                                       = 0U;
/// \input           sTimeWarp.ulTimeOffsetRepetition                                 = 0U;
/// \input           sTimeWarp.RepetitionStack.ucCnt                                  = 0U;
/// \input           AnimMa_unActiveBlocksCnt                                         = 0U;
/// \input           AnimMa_unActiveBlocksRun10Cnt                                    = 0U;
/// \input           AnimMa_unDeactivateBlocksRun10Cnt                                = 0U;
/// \input           AnimMa_unActiveBlocksRunNCnt                                     = 0U;
/// \input           AnimMa_unDeactivateBlocksRunNCnt                                 = 0U;
/// \input           AnimMa_unActiveBlocksSparkleLfsrCnt                              = 0U;
/// \input           AnimMa_unDeactivateBlocksSparkleLfsrCnt                          = 0U;
/// \input           AnimMa_unActiveBlocksSparkleXor64Cnt                             = 0U;
/// \input           AnimMa_unDeactivateBlocksSparkleXor64Cnt                         = 0U;
/// \input           AnimMa_unActiveBlocksBlinkCnt                                    = 0U;
/// \input           AnimMa_unDeactivateBlocksBlinkCnt                                = 0U;
/// \input           AnimMa_unActiveBlocksClampCnt                                    = 0U;
/// \input           AnimMa_unDeactivateBlocksClampCnt                                = 0U;
/// \input           AnimMa_unActiveBlocksInvertCnt                                   = 0U;
/// \input           AnimMa_unDeactivateBlocksInvertCnt                               = 0U;
/// \input           AnimMa_unActiveBlocksFlexCnt                                     = 0U;
/// \input           AnimMa_unDeactivateBlocksFlexCnt                                 = 0U;
/// \input           AnimMa_unActiveBlocksSpeedAssignCnt                              = 0U;
/// \input           AnimMa_unDeactivateBlocksSpeedAssignCnt                          = 0U;
/// \input           AnimMa_unActiveBlocksPiecewiseLinearCnt                          = 0U;
/// \input           AnimMa_unDeactivateBlocksPiecewiseLinearCnt                      = 0U;
/// \input           AnimMa_unActiveBlocksInvertIntensityCnt                          = 0U;
/// \input           AnimMa_unDeactivateBlocksInvertIntensityCnt                      = 0U;
/// \input           AnimMa_unActiveBlocksRepetitionCnt                               = 0U;
/// \input           AnimMa_unDeactivateBlocksRepetitionCnt                           = 0U;
/// \input           Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_ShowroomEvent;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
///
///   - Expectations:
///
/// \output         Anima_Tgt()->unTgtAni[j]   = aExpectedShowroomEv[i].aunHopt[j]
/// \output         Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_RUNNING
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_ShowroomEvent(void)
{
    int i, j;
    //Step 1) Set pre-conditions,Assign Input values
    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Start(" Mt_CtrlLed_Cycle10_ShowroomEvent.txt");
#endif
    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaShowroomEvent;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucShowroomEvent) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucShowroomEvent[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                      = eParaFct0_CodingDataValid;
    sTimeWarp.ulTimeOffset                                            = 0U;
    sTimeWarp.bInitContext                                            = false;
    sTimeWarp.ucInitContextCnt                                        = 0U;
    sTimeWarp.ulTimeOffsetRepetition                                  = 0U;
    sTimeWarp.RepetitionStack.ucCnt                                   = 0U;
    AnimMa_unActiveBlocksCnt                                          = 0U;
    AnimMa_unActiveBlocksRun10Cnt                                     = 0U;
    AnimMa_unDeactivateBlocksRun10Cnt                                 = 0U;
    AnimMa_unActiveBlocksRunNCnt                                      = 0U;
    AnimMa_unDeactivateBlocksRunNCnt                                  = 0U;
    AnimMa_unActiveBlocksSparkleLfsrCnt                               = 0U;
    AnimMa_unDeactivateBlocksSparkleLfsrCnt                           = 0U;
    AnimMa_unActiveBlocksSparkleXor64Cnt                              = 0U;
    AnimMa_unDeactivateBlocksSparkleXor64Cnt                          = 0U;
    AnimMa_unActiveBlocksBlinkCnt                                     = 0U;
    AnimMa_unDeactivateBlocksBlinkCnt                                 = 0U;
    AnimMa_unActiveBlocksClampCnt                                     = 0U;
    AnimMa_unDeactivateBlocksClampCnt                                 = 0U;
    AnimMa_unActiveBlocksInvertCnt                                    = 0U;
    AnimMa_unDeactivateBlocksInvertCnt                                = 0U;
    AnimMa_unActiveBlocksFlexCnt                                      = 0U;
    AnimMa_unDeactivateBlocksFlexCnt                                  = 0U;
    AnimMa_unActiveBlocksSpeedAssignCnt                               = 0U;
    AnimMa_unDeactivateBlocksSpeedAssignCnt                           = 0U;
    AnimMa_unActiveBlocksPiecewiseLinearCnt                           = 0U;
    AnimMa_unDeactivateBlocksPiecewiseLinearCnt                       = 0U;
    AnimMa_unActiveBlocksInvertIntensityCnt                           = 0U;
    AnimMa_unDeactivateBlocksInvertIntensityCnt                       = 0U;
    AnimMa_unActiveBlocksRepetitionCnt                                = 0U;
    AnimMa_unDeactivateBlocksRepetitionCnt                            = 0U;
    Rte_Read_IoHwAbUser_GetMountingSide_Param1                        = eMountedLeft;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl  = eExtLightingAnimationReq_ShowroomEvent;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                      = SIG_VALID;

    for (i = 0; i < 3000; i++)
    {
        //Step 2) Call FUT
        Anima_Cycle10();
        for (j = 0; j < 27; j++)
        {
            //Step 3) Check expected output values
            AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], aExpectedShowroomEv[i].aunHopt[j], == );
        }
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_RUNNING, == );

        //Cfg logging
#if CFG_ENABLE_LOGGING == 1
        Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
            , (int)Anima_Tgt()->unTgtAni[0]
            , (int)Anima_Tgt()->unTgtAni[1]
            , (int)Anima_Tgt()->unTgtAni[2]
            , (int)Anima_Tgt()->unTgtAni[3]
            , (int)Anima_Tgt()->unTgtAni[4]
            , (int)Anima_Tgt()->unTgtAni[5]
            , (int)Anima_Tgt()->unTgtAni[6]
            , (int)Anima_Tgt()->unTgtAni[7]
            , (int)Anima_Tgt()->unTgtAni[8]
            , (int)Anima_Tgt()->unTgtAni[9]
            , (int)Anima_Tgt()->unTgtAni[10]
            , (int)Anima_Tgt()->unTgtAni[11]
            , (int)Anima_Tgt()->unTgtAni[12]
            , (int)Anima_Tgt()->unTgtAni[13]
            , (int)Anima_Tgt()->unTgtAni[14]
            , (int)Anima_Tgt()->unTgtAni[15]
            , (int)Anima_Tgt()->unTgtAni[16]
            , (int)Anima_Tgt()->unTgtAni[17]
            , (int)Anima_Tgt()->unTgtAni[18]
            , (int)Anima_Tgt()->unTgtAni[19]
            , (int)Anima_Tgt()->unTgtAni[20]
            , (int)Anima_Tgt()->unTgtAni[21]
            , (int)Anima_Tgt()->unTgtAni[22]
            , (int)Anima_Tgt()->unTgtAni[23]
            , (int)Anima_Tgt()->unTgtAni[24]
            , (int)Anima_Tgt()->unTgtAni[25]
            , (int)Anima_Tgt()->unTgtAni[26]
        );
#endif
    }

    //stop previus animation
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_None;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    //Step 2) Call FUT
    Anima_Cycle10();

    for (j = 0; j < 27; j++)
    {
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], 0u, == );
    }
    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );

    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d } }\n", 10 * i
        , (int)Anima_Tgt()->unTgtAni[0]
        , (int)Anima_Tgt()->unTgtAni[1]
        , (int)Anima_Tgt()->unTgtAni[2]
        , (int)Anima_Tgt()->unTgtAni[3]
        , (int)Anima_Tgt()->unTgtAni[4]
        , (int)Anima_Tgt()->unTgtAni[5]
        , (int)Anima_Tgt()->unTgtAni[6]
        , (int)Anima_Tgt()->unTgtAni[7]
        , (int)Anima_Tgt()->unTgtAni[8]
        , (int)Anima_Tgt()->unTgtAni[9]
        , (int)Anima_Tgt()->unTgtAni[10]
        , (int)Anima_Tgt()->unTgtAni[11]
        , (int)Anima_Tgt()->unTgtAni[12]
        , (int)Anima_Tgt()->unTgtAni[13]
        , (int)Anima_Tgt()->unTgtAni[14]
        , (int)Anima_Tgt()->unTgtAni[15]
        , (int)Anima_Tgt()->unTgtAni[16]
        , (int)Anima_Tgt()->unTgtAni[17]
        , (int)Anima_Tgt()->unTgtAni[18]
        , (int)Anima_Tgt()->unTgtAni[19]
        , (int)Anima_Tgt()->unTgtAni[20]
        , (int)Anima_Tgt()->unTgtAni[21]
        , (int)Anima_Tgt()->unTgtAni[22]
        , (int)Anima_Tgt()->unTgtAni[23]
        , (int)Anima_Tgt()->unTgtAni[24]
        , (int)Anima_Tgt()->unTgtAni[25]
        , (int)Anima_Tgt()->unTgtAni[26]
    );
#endif

#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Stop();
#endif
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Cycle10_Animations_test
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check all the animations
///
/// \Expected test results : All test cases contained are passed
///
//----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_Animations_test(void)
{
    Mt_CtrlLed_Cycle10_Dataset0_FMH15();
    Mt_CtrlLed_Cycle10_Dataset0_FMH30();
    Mt_CtrlLed_Cycle10_Dataset0_FMH60_TestCase1();
    Mt_CtrlLed_Cycle10_Dataset0_FMH60_TestCase2();
    Mt_CtrlLed_Cycle10_Dataset0_WelcomeDay();
    Mt_CtrlLed_Cycle10_Dataset0_WelcomeNight();
    Mt_CtrlLed_Cycle10_Dataset0_TIScr();
    Mt_CtrlLed_Cycle10_Dataset0_ByeByeDay();
    Mt_CtrlLed_Cycle10_Dataset0_ByeByeNight();
    Mt_CtrlLed_Cycle10_Dataset0_EndNightByeBye();
    Mt_CtrlLed_Cycle10_Dataset0_UnlockNight();
    Mt_CtrlLed_Cycle10_Dataset0_UnlockDay();
    Mt_CtrlLed_Cycle10_Dataset0_UnlockDayExt();
    Mt_CtrlLed_Cycle10_Dataset0_LockDay();
    Mt_CtrlLed_Cycle10_ShowroomEvent();
    Mt_CtrlLed_Cycle10_Dataset0_LockDayExt();
    Mt_CtrlLed_Cycle10_Dataset0_LockNightExt();
    Mt_CtrlLed_Cycle10_Dataset0_LockNight();
    Mt_CtrlLed_Cycle10_Dataset0_Autorelock();
    Mt_CtrlLed_Cycle10_Dataset0_UnlockNightExt();
    Mt_CtrlLed_Cycle10_Dataset0_LocalizationNight();
    Mt_CtrlLed_Cycle10_Dataset0_LocalizationDay();
    Mt_CtrlLed_Cycle10_Dataset0_ByeByeNightFmh();
    Mt_CtrlLed_Cycle10_Dataset0_RemoteLighting();
    Mt_CtrlLed_Cycle10_Dataset0_SwitchOff();
    Mt_CtrlLed_Cycle10_ShowroomContinu();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Anima_Anima_ReadFrontTurnIndicatorCmd
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check start sequence
///
/// \Expected test results : All test cases contained are passed
///
//----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_Anima_ReadFrontTurnIndicatorCmd(void)
{
    Mt_CtrlLed_Anima_Anima_ReadFrontTurnIndicatorCmd_TestCase1();
    Mt_CtrlLed_Anima_Anima_ReadFrontTurnIndicatorCmd_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Cycle10_AnimaCInvalid_TestCase1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check invalid animation with no light request ON
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input           Rte_Read_SysMon_VehNetState_Param1.eSigQty                       = SIG_VALID;
/// \input           Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState         = eTI_NOMINAL;
/// \input           Rte_Read_SysMon_TurnIndicatorCmd_Req_Param1                      = ReqLighted_Off;
/// \input           Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty                    = SIG_VALID;
/// \input           Rte_Read_SysMon_StdLgtFcts_Req_Param1.eDrl_Request               = ReqLighted_Off;
/// \input           Rte_Read_SysMon_StdLgtFcts_Req_Param1.eHbFlash_Request           = ReqLighted_Off;
/// \input           Rte_Read_SysMon_StdLgtFcts_Req_Param1.ePos_Request               = ReqLighted_Off;
/// \input           Rte_Read_SysMon_LowBeamCmd_Req_Param1                            = ReqLighted_Off;
/// \input           Rte_Read_SysMon_StdLgtFcts_Req_Param1.eHb_Request                = ReqLighted_Off;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;
///
///   - Expectations:
///
/// \output         Anima_Tgt()->unTgtAni[j]   = aExpectedInvalid[i].aunHopt[j]
/// \output         Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_RUNNING
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_AnimaCInvalid_TestCase1(void)
{
    int i, j;
    //Step 1) Set pre-conditions,Assign Input values
//Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Start(" Mt_CtrlLed_Cycle10_AnimaCInvalid.txt");
#endif

    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaC;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset0_AnimaC) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset0_AnimaC[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
    Rte_Read_SysMon_VehNetState_Param1.eSigQty                       = SIG_VALID;
    Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState         = eTI_NOMINAL;
    Rte_Read_SysMon_TurnIndicatorCmd_Req_Param1                      = ReqLighted_Off;
    Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty                    = SIG_VALID;
    Rte_Read_SysMon_StdLgtFcts_Req_Param1.eDrl_Request               = ReqLighted_Off;
    Rte_Read_SysMon_StdLgtFcts_Req_Param1.eHbFlash_Request           = ReqLighted_Off;
    Rte_Read_SysMon_StdLgtFcts_Req_Param1.ePos_Request               = ReqLighted_Off;
    Rte_Read_SysMon_LowBeamCmd_Req_Param1                            = ReqLighted_Off;
    Rte_Read_SysMon_StdLgtFcts_Req_Param1.eHb_Request                = ReqLighted_Off;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;

    for (i = 0; i < 3000; i++)
    {
        //Step 2) Call FUT
        Anima_Cycle10();
        for (j = 0; j < 27U; j++)//number of pixels
        {
            Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_INVALID;
            Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_Invalid;
            //Step 3) Check expected output values
            AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], aExpectedInvalid[i].aunHopt[j], == );
        }
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_RUNNING, == );
    }

    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
        , (int)Anima_Tgt()->unTgtAni[0]
        , (int)Anima_Tgt()->unTgtAni[1]
        , (int)Anima_Tgt()->unTgtAni[2]
        , (int)Anima_Tgt()->unTgtAni[3]
        , (int)Anima_Tgt()->unTgtAni[4]
        , (int)Anima_Tgt()->unTgtAni[5]
        , (int)Anima_Tgt()->unTgtAni[6]
        , (int)Anima_Tgt()->unTgtAni[7]
        , (int)Anima_Tgt()->unTgtAni[8]
        , (int)Anima_Tgt()->unTgtAni[9]
        , (int)Anima_Tgt()->unTgtAni[10]
        , (int)Anima_Tgt()->unTgtAni[11]
        , (int)Anima_Tgt()->unTgtAni[12]
        , (int)Anima_Tgt()->unTgtAni[13]
        , (int)Anima_Tgt()->unTgtAni[14]
        , (int)Anima_Tgt()->unTgtAni[15]
        , (int)Anima_Tgt()->unTgtAni[16]
        , (int)Anima_Tgt()->unTgtAni[17]
        , (int)Anima_Tgt()->unTgtAni[18]
        , (int)Anima_Tgt()->unTgtAni[19]
        , (int)Anima_Tgt()->unTgtAni[20]
        , (int)Anima_Tgt()->unTgtAni[21]
        , (int)Anima_Tgt()->unTgtAni[22]
        , (int)Anima_Tgt()->unTgtAni[23]
        , (int)Anima_Tgt()->unTgtAni[24]
        , (int)Anima_Tgt()->unTgtAni[25]
        , (int)Anima_Tgt()->unTgtAni[26]
    );
#endif

#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Stop();
#endif
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Cycle10_AnimaCInvalid_TestCase2
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:   Check invalid animation with light request ON
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input           Rte_Read_SysMon_VehNetState_Param1.eSigQty                       = SIG_VALID;
/// \input           Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState         = eTI_NOMINAL;
/// \input           Rte_Read_SysMon_TurnIndicatorCmd_Req_Param1                      = ReqLighted_On;
/// \input           Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty                    = SIG_VALID;
/// \input           Rte_Read_SysMon_StdLgtFcts_Req_Param1.eDrl_Request               = ReqLighted_On;
/// \input           Rte_Read_SysMon_StdLgtFcts_Req_Param1.eHbFlash_Request           = ReqLighted_Off;
/// \input           Rte_Read_SysMon_StdLgtFcts_Req_Param1.ePos_Request               = ReqLighted_On;
/// \input           Rte_Read_SysMon_LowBeamCmd_Req_Param1                            = ReqLighted_On;
/// \input           Rte_Read_SysMon_StdLgtFcts_Req_Param1.eHb_Request                = ReqLighted_Off;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;
///
///   - Expectations:
///
/// \output         Anima_Tgt()->unTgtAni[j]   = 0u
/// \output         Anima_TgtAniArr.boPriority = 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_AnimaCInvalid_TestCase2(void)
{
    int i, j;
    //Step 1) Set pre-conditions,Assign Input values
    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Start(" Mt_CtrlLed_Cycle10_AnimaCInvalid.txt");
#endif

    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaC;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset0_AnimaC) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset0_AnimaC[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
    Rte_Read_SysMon_VehNetState_Param1.eSigQty                       = SIG_VALID;
    Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState         = eTI_NOMINAL;
    Rte_Read_SysMon_TurnIndicatorCmd_Req_Param1                      = ReqLighted_On;
    Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty                    = SIG_VALID;
    Rte_Read_SysMon_StdLgtFcts_Req_Param1.eDrl_Request               = ReqLighted_On;
    Rte_Read_SysMon_StdLgtFcts_Req_Param1.eHbFlash_Request           = ReqLighted_Off;
    Rte_Read_SysMon_StdLgtFcts_Req_Param1.ePos_Request               = ReqLighted_On;
    Rte_Read_SysMon_LowBeamCmd_Req_Param1                            = ReqLighted_On;
    Rte_Read_SysMon_StdLgtFcts_Req_Param1.eHb_Request                = ReqLighted_Off;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;

    for (i = 0; i < 3000; i++)
    {
        //Step 2) Call FUT
        Anima_Cycle10();
        for (j = 0; j < 27; j++)//number of pixels
        {
            Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_INVALID;
            Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_Invalid;
            //Step 3) Check expected output values
            AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], 0u, == );
        }
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, 0U, == );
    }

    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d,%5d, %5d, %5d, %5d, %5d,   %5d, %5d } }\n", 10 * i
        , (int)Anima_Tgt()->unTgtAni[0]
        , (int)Anima_Tgt()->unTgtAni[1]
        , (int)Anima_Tgt()->unTgtAni[2]
        , (int)Anima_Tgt()->unTgtAni[3]
        , (int)Anima_Tgt()->unTgtAni[4]
        , (int)Anima_Tgt()->unTgtAni[5]
        , (int)Anima_Tgt()->unTgtAni[6]
        , (int)Anima_Tgt()->unTgtAni[7]
        , (int)Anima_Tgt()->unTgtAni[8]
        , (int)Anima_Tgt()->unTgtAni[9]
        , (int)Anima_Tgt()->unTgtAni[10]
        , (int)Anima_Tgt()->unTgtAni[11]
        , (int)Anima_Tgt()->unTgtAni[12]
        , (int)Anima_Tgt()->unTgtAni[13]
        , (int)Anima_Tgt()->unTgtAni[14]
        , (int)Anima_Tgt()->unTgtAni[15]
        , (int)Anima_Tgt()->unTgtAni[16]
        , (int)Anima_Tgt()->unTgtAni[17]
        , (int)Anima_Tgt()->unTgtAni[18]
        , (int)Anima_Tgt()->unTgtAni[19]
        , (int)Anima_Tgt()->unTgtAni[20]
        , (int)Anima_Tgt()->unTgtAni[21]
        , (int)Anima_Tgt()->unTgtAni[22]
        , (int)Anima_Tgt()->unTgtAni[23]
        , (int)Anima_Tgt()->unTgtAni[24]
        , (int)Anima_Tgt()->unTgtAni[25]
        , (int)Anima_Tgt()->unTgtAni[26]
    );
#endif

#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Stop();
#endif
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Cycle10_AnimaCInvalid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check start sequence
///
/// \Expected test results : All test cases contained are passed
///
//----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_AnimaCInvalid(void)
{
    Mt_CtrlLed_Cycle10_AnimaCInvalid_TestCase1();
    Mt_CtrlLed_Cycle10_AnimaCInvalid_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Cycle10_AnimaCPriorityNoneTIReq
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Test that animation request is not followed if TI request is coming
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedRight;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;
/// \input           Rte_Read_SysMon_TurnIndicatorCmd_Req_Param1                      = ReqLighted_On;
///
///   - Expectations:
///
/// \output         Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_NONE
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_AnimaCPriorityNoneTIReq(void)
{
    //Step 1) Set pre-conditions,Assign Input values
    Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedRight;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;
    Rte_Read_SysMon_TurnIndicatorCmd_Req_Param1                      = ReqLighted_On;

    //Step 2) Call FUT
    Anima_Cycle10();

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Anima_Init_NoAnima
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Test boPriority is false when no animation is requested at init
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedRight;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;
///
///   - Expectations:
///
/// \output         Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_NONE
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_Init_NoAnima(void)
{
    //Step 1) Set pre-conditions,Assign Input values
    Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedRight;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_None;

    //Step 2) Call FUT
    Anima_Init();

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Cycle10_AnimaCPriorityNoneHBFlashReq
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Test that animation request is not followed if HB Flash request is coming
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;
/// \input           Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty                    = SIG_VALID;
/// \input           Rte_Read_SysMon_StdLgtFcts_Req_Param1.eHbFlash_Request           = ReqLighted_On;
///
///   - Expectations:
///
/// \output           Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_NONE
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_AnimaCPriorityNoneHBFlashReq(void)
{
    //Step 1) Set pre-conditions,Assign Input values
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;
    Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty                    = SIG_VALID;
    Rte_Read_SysMon_StdLgtFcts_Req_Param1.eHbFlash_Request           = ReqLighted_On;

    //Step 2) Call FUT
    Anima_Cycle10();

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Cycle10_AnimaCPriorityNoneDRLReq
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Test that animation request is not followed if DRL Flash request is coming
///    - Test Design Technique: ET (Exploratory Testing)
///    - Preconditions:
///
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;
/// \input           Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty                    = SIG_VALID;
/// \input           Rte_Read_SysMon_StdLgtFcts_Req_Param1.eDrl_Request               = ReqLighted_On;
///
///   - Expectations:
///
/// \output           Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_NONE
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_AnimaCPriorityNoneDRLReq(void)
{
    //Step 1) Set pre-conditions,Assign Input values
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;
    Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty                    = SIG_VALID;
    Rte_Read_SysMon_StdLgtFcts_Req_Param1.eDrl_Request               = ReqLighted_On;

    //Step 2) Call FUT
    Anima_Cycle10();

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Cycle10_AnimaCPriorityNonePOSReq
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Test that animation request is not followed if POS request is coming
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;
/// \input           Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty                    = SIG_VALID;
/// \input           Rte_Read_SysMon_StdLgtFcts_Req_Param1.ePos_Request               = ReqLighted_On;
///
///   - Expectations:
///
/// \output           Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_NONE
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_AnimaCPriorityNonePOSReq(void)
{
    //Step 1) Set pre-conditions,Assign Input values
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;
    Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty                    = SIG_VALID;
    Rte_Read_SysMon_StdLgtFcts_Req_Param1.ePos_Request               = ReqLighted_On;

    //Step 2) Call FUT
    Anima_Cycle10();

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Cycle10_AnimaCPriorityNoneLBReq
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Test that animation request is not followed if LB request is coming
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input            Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input            Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;
/// \input            Rte_Read_SysMon_LowBeamCmd_Req_Param1                            = ReqLighted_On;
///
///   - Expectations:
///
/// \output           Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_NONE
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_AnimaCPriorityNoneLBReq(void)
{
    //Step 1) Set pre-conditions,Assign Input values
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;
    Rte_Read_SysMon_LowBeamCmd_Req_Param1                            = ReqLighted_On;

    //Step 2) Call FUT
    Anima_Cycle10();

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Cycle10_AnimaCPriorityNoneHBReq
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Test that animation request is not followed if HB request is coming
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input            Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input            Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;
/// \input            Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty                    = SIG_VALID;
/// \input            Rte_Read_SysMon_StdLgtFcts_Req_Param1.eHb_Request                = ReqLighted_On;
///
///   - Expectations:
///
/// \output           Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_NONE
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_AnimaCPriorityNoneHBReq(void)
{
    //Step 1) Set pre-conditions,Assign Input values
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;
    Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty                    = SIG_VALID;
    Rte_Read_SysMon_StdLgtFcts_Req_Param1.eHb_Request                = ReqLighted_On;

    //Step 2) Call FUT
    Anima_Cycle10();

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Cycle10_AnimaCPriority
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check start sequence when anima is inhibited or no anima requested
///
/// \Expected test results : All test cases contained are passed
///
//----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_AnimaCPriority(void)
{
    Mt_CtrlLed_Cycle10_AnimaCPriorityNoneTIReq();
    Mt_CtrlLed_Anima_Init_NoAnima();
    Mt_CtrlLed_Cycle10_AnimaCPriorityNoneHBFlashReq();
    Mt_CtrlLed_Cycle10_AnimaCPriorityNoneDRLReq();
    Mt_CtrlLed_Cycle10_AnimaCPriorityNonePOSReq();
    Mt_CtrlLed_Cycle10_AnimaCPriorityNoneLBReq();
    Mt_CtrlLed_Cycle10_AnimaCPriorityNoneHBReq();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_rcBlockRun10_TestCase1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that animation rcblock is handled correct when unlock day animation is requested 
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           AnimMa_rcBlockRun10_Param1                                       = 5u;
/// \input           AnimMa_rcBlockRun10_Param2                                       = 800u;
/// \input           AnimMa_aActiveBlocks[AnimMa_rcBlockRun10_Param1].ucBlkCtxIdx     = 8u;
/// \input           AnimMa_unActiveBlocksRun10Cnt                                    = 5u;
/// \input           Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input           Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_None;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_UnlockDay;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input           AnimMa_unActiveBlocksRun10Cnt                                    = 50u;
///
///   - Expectations:
///
/// \output         AnimMa_aActiveBlocks[AnimMa_rcBlockRun10_Param1].unGenParamCodIdx   = 83u;
/// \output         AnimMa_aActiveBlocks[AnimMa_rcBlockRun10_Param1].ucBlkCtxIdx        = 8u;
/// \output         AnimMa_aActiveBlocks[AnimMa_rcBlockRun10_Param1].unSpcParamCodIdx   = 350u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_rcBlockRun10_TestCase1(void)
{    
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_rcBlockRun10_Param1                                   = 5u;
    AnimMa_rcBlockRun10_Param2                                   = 800u;
    AnimMa_aActiveBlocks[AnimMa_rcBlockRun10_Param1].ucBlkCtxIdx = 8u;
    AnimMa_unActiveBlocksRun10Cnt = 5u;

    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaC;
    for (uint32 i = 0; i < sizeof(AnimMa_CodPrj_auTest) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = AnimMa_CodPrj_auTest[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
    Mt_CtrlLed_PreTest();
    Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_UnlockDay;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    AnimMa_unActiveBlocksRun10Cnt                                    = 50u;

    //Step 2) Call FUT
    AnimMa_rcBlockRun10(AnimMa_rcBlockRun10_Param1, AnimMa_rcBlockRun10_Param2);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_aActiveBlocks[AnimMa_rcBlockRun10_Param1].unGenParamCodIdx, 83u , == );
    AL_UNITTEST_CHECK(AnimMa_aActiveBlocks[AnimMa_rcBlockRun10_Param1].ucBlkCtxIdx     , 8u  , == );
    AL_UNITTEST_CHECK(AnimMa_aActiveBlocks[AnimMa_rcBlockRun10_Param1].unSpcParamCodIdx, 350u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_rcBlockRun10_TestCase2
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that animation rcblock is handled correct when unlock day animation is requested  and unDeltaTime <= unCodTime
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           AnimMa_rcBlockRun10_Param1                                       = 6u;
/// \input           AnimMa_rcBlockRun10_Param2                                       = 0u;
/// \input           AnimMa_aActiveBlocks[AnimMa_rcBlockRun10_Param1].ucBlkCtxIdx     = 12u;
/// \input           AnimMa_unActiveBlocksRun10Cnt                                    = 5u;
/// \input           Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input           Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_ByeByeDay;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input           AnimMa_unActiveBlocksRun10Cnt                                    = 1u;
///
///   - Expectations:
///
/// \output         AnimMa_aActiveBlocks[AnimMa_rcBlockRun10_Param1].unGenParamCodIdx   = 91u;
/// \output         AnimMa_aActiveBlocks[AnimMa_rcBlockRun10_Param1].ucBlkCtxIdx        = 12u;
/// \output         AnimMa_aActiveBlocks[AnimMa_rcBlockRun10_Param1].unSpcParamCodIdx   = 366u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_rcBlockRun10_TestCase2(void)
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_rcBlockRun10_Param1                                   = 6u;
    AnimMa_rcBlockRun10_Param2                                   = 0u;
    AnimMa_aActiveBlocks[AnimMa_rcBlockRun10_Param1].ucBlkCtxIdx = 12u;
    AnimMa_unActiveBlocksRun10Cnt                                = 5u;

    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaC;
    for (uint32 i = 0; i < sizeof(AnimMa_CodPrj_auTest) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = AnimMa_CodPrj_auTest[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
    Mt_CtrlLed_PreTest();
    Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_ByeByeDay;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    AnimMa_unActiveBlocksRun10Cnt                                    = 1u;

    //Step 2) Call FUT
    AnimMa_rcBlockRun10(AnimMa_rcBlockRun10_Param1, AnimMa_rcBlockRun10_Param2);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_aActiveBlocks[AnimMa_rcBlockRun10_Param1].unGenParamCodIdx, 91u, == );
    AL_UNITTEST_CHECK(AnimMa_aActiveBlocks[AnimMa_rcBlockRun10_Param1].ucBlkCtxIdx     , 12u, == );
    AL_UNITTEST_CHECK(AnimMa_aActiveBlocks[AnimMa_rcBlockRun10_Param1].unSpcParamCodIdx, 366u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_rcBlockRun10_TestCase3
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that animation rcblock is handled correct when unlock day animation is requested  and unDeltaTime >unCodTime
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           AnimMa_rcBlockRun10_Param1                                       = 6u;
/// \input           AnimMa_rcBlockRun10_Param2                                       = 551u;
/// \input           AnimMa_aActiveBlocks[AnimMa_rcBlockRun10_Param1].ucBlkCtxIdx     = 0u;
/// \input           AnimMa_unActiveBlocksRun10Cnt                                    = 5u;
/// \input           Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input           Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_ByeByeDay;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input           AnimMa_unActiveBlocksRun10Cnt                                    = 1u;
///
///   - Expectations:
///
/// \output         AnimMa_aActiveBlocks[AnimMa_rcBlockRun10_Param1].unGenParamCodIdx   = 91u;
/// \output         AnimMa_aActiveBlocks[AnimMa_rcBlockRun10_Param1].ucBlkCtxIdx        = 0u;
/// \output         AnimMa_aActiveBlocks[AnimMa_rcBlockRun10_Param1].unSpcParamCodIdx   = 366u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_rcBlockRun10_TestCase3(void)
{
    //Step 1) Set pre-conditions,Assign Input values
    AnimMa_rcBlockRun10_Param1                                   = 6u;
    AnimMa_rcBlockRun10_Param2                                   = 551u;
    AnimMa_aActiveBlocks[AnimMa_rcBlockRun10_Param1].ucBlkCtxIdx = 0u;
    AnimMa_unActiveBlocksRun10Cnt                                = 5u;

    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaC;
    for (uint32 i = 0; i < sizeof(AnimMa_CodPrj_auTest2) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = AnimMa_CodPrj_auTest2[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
    Mt_CtrlLed_PreTest();
    Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_ByeByeDay;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    AnimMa_unActiveBlocksRun10Cnt                                    = 1u;

    //Step 2) Call FUT
    AnimMa_rcBlockRun10(AnimMa_rcBlockRun10_Param1, AnimMa_rcBlockRun10_Param2);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_aActiveBlocks[AnimMa_rcBlockRun10_Param1].unGenParamCodIdx, 91u, == );
    AL_UNITTEST_CHECK(AnimMa_aActiveBlocks[AnimMa_rcBlockRun10_Param1].ucBlkCtxIdx,      0u, == );
    AL_UNITTEST_CHECK(AnimMa_aActiveBlocks[AnimMa_rcBlockRun10_Param1].unSpcParamCodIdx, 366u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Cycle10_AnimaCPriority
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check start sequence
///
/// \Expected test results : All test cases contained are passed
///
//----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_rcBlockRun10(void)
{
    Mt_CtrlLed_AnimMa_rcBlockRun10_TestCase1();
    Mt_CtrlLed_AnimMa_rcBlockRun10_TestCase2();
    Mt_CtrlLed_AnimMa_rcBlockRun10_TestCase3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_LfsrShift
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check LFSR block if number of bytes is exceeded
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           AnimMa_LfsrShift_Param3 = 200u
/// \input           AnimMa_LfsrShift_Param1 = 5u;
/// \input           AnimMa_LfsrShift_Param2 = 0u;
///
///   - Expectations:
///
/// \output         AnimMa_aActiveBlocksSparkleLfsr[AnimMa_LfsrShift_Param1].ucReg[(AnimMa_LfsrShift_Param3+7)/8] = 0u;
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_LfsrShift(void)
{   
     //Step 1) Set pre-conditions,Assign Input values
    AnimMa_LfsrShift_Param3 = 200u;
    AnimMa_LfsrShift_Param1 = 5u;
    AnimMa_LfsrShift_Param2 = 0u;

    //Step 2) Call FUT
    AnimMa_LfsrShift(AnimMa_LfsrShift_Param1, &AnimMa_LfsrShift_Param2, AnimMa_LfsrShift_Param3);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_aActiveBlocksSparkleLfsr[AnimMa_LfsrShift_Param1].ucReg[(AnimMa_LfsrShift_Param3+7)/8], 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_rcBlockSparkleLfsr_TestCase1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check LFSR block if blocks id is greater than the active blocks Lfsr with max value set
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           AnimMa_rcBlockSparkleLfsr_Param1                                   = 5u;
/// \input           AnimMa_rcBlockSparkleLfsr_Param2                                   = 100u;
/// \input           AnimMa_unActiveBlocksSparkleLfsrCnt                                = 2u;
/// \input           AnimMa_aActiveBlocks[AnimMa_rcBlockSparkleLfsr_Param1].ucBlkCtxIdx = 1u;
/// \input           Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks          = &AnimaCodingAreaC;
///
///   - Expectations:
///
/// \output         AnimMaRamp_aucPxlIntInc[0u] = 0u;
/// \output         AnimMaRamp_aucPxlIntDec[0u] = 0u;
/// \output         AnimMaRamp_aucPxlIntTgt[i]  = 0u;
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_rcBlockSparkleLfsr_TestCase1(void)
{
    //Step 1) Set pre-conditions,Assign Input values
    sint32 i;
    AnimMa_rcBlockSparkleLfsr_Param1                                   = 5u;
    AnimMa_rcBlockSparkleLfsr_Param2                                   = 100u;
    AnimMa_unActiveBlocksSparkleLfsrCnt                                = 2u;
    AnimMa_aActiveBlocks[AnimMa_rcBlockSparkleLfsr_Param1].ucBlkCtxIdx = 8u;
    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks          = &AnimaCodingAreaC;

    const tBlockGeneric             * pCodGen = &AnimMa_pCodingData->Animation.AnimationByteStream.aucByteStream[AnimMa_aActiveBlocks[AnimMa_rcBlockSparkleLfsr_Param1].unGenParamCodIdx];
    const tBlockSpecificSparkleLfsr * pCodSpc = &AnimMa_pCodingData->Animation.AnimationByteStream.aucByteStream[AnimMa_aActiveBlocks[AnimMa_rcBlockSparkleLfsr_Param1].unSpcParamCodIdx];
    for (i = (sint32)pCodGen->ucPStart; i <= (sint32)pCodGen->ucPEnd; i++)
    {
        (uint32)AnimMa_aActiveBlocksSparkleLfsr[AnimMa_aActiveBlocks[AnimMa_rcBlockSparkleLfsr_Param1].ucBlkCtxIdx].ucReg[i / 8];
    }

    //Step 2) Call FUT
    AnimMa_rcBlockSparkleLfsr(AnimMa_rcBlockSparkleLfsr_Param1, AnimMa_rcBlockSparkleLfsr_Param2);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMaRamp_aucPxlIntInc[i], 0u  , == );
    AL_UNITTEST_CHECK(AnimMaRamp_aucPxlIntDec[i], 0u  , == );
    AL_UNITTEST_CHECK(AnimMaRamp_aucPxlIntTgt[i], 0u  , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_rcBlockSparkleLfsr_TestCase2
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check LFSR block if blocks id is greater than the active blocks Lfsr with min value set
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           AnimMa_rcBlockSparkleLfsr_Param1                                   = 5u;
/// \input           AnimMa_rcBlockSparkleLfsr_Param2                                   = 100u;
/// \input           AnimMa_unActiveBlocksSparkleLfsrCnt                                = 2u;
/// \input           AnimMa_aActiveBlocks[AnimMa_rcBlockSparkleLfsr_Param1].ucBlkCtxIdx = 0u;
///
///   - Expectations:
///
/// \output         AnimMaRamp_aucPxlIntInc[0u] = 0u;
/// \output         AnimMaRamp_aucPxlIntDec[0u] = 0u;
/// \output         AnimMaRamp_aucPxlIntTgt[i]  = 0u;
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_rcBlockSparkleLfsr_TestCase2(void)
{
    //Step 1) Set pre-conditions,Assign Input values
    sint32 i;
    AnimMa_rcBlockSparkleLfsr_Param1                                   = 5u;
    AnimMa_rcBlockSparkleLfsr_Param2                                   = 100u;
    AnimMa_unActiveBlocksSparkleLfsrCnt                                = 2u;
    AnimMa_aActiveBlocks[AnimMa_rcBlockSparkleLfsr_Param1].ucBlkCtxIdx = 0u;
    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks          = &AnimaCodingAreaC;

    const tBlockGeneric             * pCodGen = &AnimMa_pCodingData->Animation.AnimationByteStream.aucByteStream[AnimMa_aActiveBlocks[AnimMa_rcBlockSparkleLfsr_Param1].unGenParamCodIdx];
    const tBlockSpecificSparkleLfsr * pCodSpc = &AnimMa_pCodingData->Animation.AnimationByteStream.aucByteStream[AnimMa_aActiveBlocks[AnimMa_rcBlockSparkleLfsr_Param1].unSpcParamCodIdx];
    for (i = (sint32)pCodGen->ucPStart; i <= (sint32)pCodGen->ucPEnd; i++)
    {
        (uint32)AnimMa_aActiveBlocksSparkleLfsr[AnimMa_aActiveBlocks[AnimMa_rcBlockSparkleLfsr_Param1].ucBlkCtxIdx].ucReg[i / 8];
    }

    //Step 2) Call FUT
    AnimMa_rcBlockSparkleLfsr(AnimMa_rcBlockSparkleLfsr_Param1, AnimMa_rcBlockSparkleLfsr_Param2);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMaRamp_aucPxlIntInc[i], 0u, == );
    AL_UNITTEST_CHECK(AnimMaRamp_aucPxlIntDec[i], 0u, == );
    AL_UNITTEST_CHECK(AnimMaRamp_aucPxlIntTgt[i], 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_rcBlockSparkleLfsr
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check start sequence
///
/// \Expected test results : All test cases contained are passed
///
//----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_rcBlockSparkleLfsr(void)
{
    Mt_CtrlLed_AnimMa_rcBlockSparkleLfsr_TestCase1();
    Mt_CtrlLed_AnimMa_rcBlockSparkleLfsr_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_rcBlockClamp_TestCase1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check anima do not start if for clamp block the time si not 0 when started
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input            Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input            Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_UnlockDay;
/// \input            Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input            ulTime                                                           = 0u;
/// \input            ulActiveBlkId                                                    = 5u;
/// \input            AnimMa_unActiveBlocksClampCnt                                    = 123U;
///
///   - Expectations:
///
/// \output        Anima_Tgt()->unTgtAni[j] = 0u;
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_rcBlockClamp_TestCase1(void)
{
    uint32 ulActiveBlkId;
    uint32 ulTime;
    int i, j;
    //Step 1) Set pre-conditions,Assign Input values
    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaC;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucBlockClamp) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucBlockClamp[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_UnlockDay;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    ulTime                                                           = 0u;
    ulActiveBlkId                                                    = 5u;
    AnimMa_unActiveBlocksClampCnt                                    = 123U;

    //Step 2) Call FUT
    AnimMa_rcBlockClamp(ulActiveBlkId, ulTime);

    for (i = 0; i < 200; i++)
    {
        for (j = 0; j < 10; j++)
        {    //Step 3) Check expected output values
            AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], 0u, == );
        }
    }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_rcBlockClamp_TestCase2
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check anima do not start if for clamp block the time si not 0 when started
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input            Rte_Read_CodM_Anima_Para_Param1.eCodingState         = eParaFct0_CodingDataValid;
/// \input            Rte_Read_IoHwAbUser_GetMountingSide_Param1           = eMountedLeft;
/// \input            ulTime                                               = 0u;
/// \input            ulActiveBlkId                                        = 18u;
/// \input            AnimMa_aActiveBlocks[ulActiveBlkId].unGenParamCodIdx = 187u;
///
///   - Expectations:
///
/// \output        Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_NONE;
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_rcBlockClamp_TestCase2(void)
{
    uint32 ulActiveBlkId;
    uint32 ulTime;

    //Step 1) Set pre-conditions,Assign Input values
    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaC;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucBlockClamp2) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucBlockClamp2[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState         = eParaFct0_CodingDataValid;
    Rte_Read_IoHwAbUser_GetMountingSide_Param1           = eMountedLeft;
    ulTime                                               = 0u;
    ulActiveBlkId                                        = 18u;
    AnimMa_aActiveBlocks[ulActiveBlkId].unGenParamCodIdx = 187u;

    //Step 2) Call FUT
    AnimMa_rcBlockClamp(ulActiveBlkId, ulTime);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_rcBlockClamp
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check start sequence
///
/// \Expected test results : All test cases contained are passed
///
//----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_rcBlockClamp(void)
{
    Mt_CtrlLed_AnimMa_rcBlockClamp_TestCase1();
    Mt_CtrlLed_AnimMa_rcBlockClamp_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Anima_AnimMa_InitBlockContext_RUN10
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that anima do not start if number of allocated blocks is not correct for RUN10 block
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input          Rte_Read_CodM_Anima_Para_Param1.eCodingState                      = eParaFct0_CodingDataValid;
/// \input          Rte_Read_IoHwAbUser_GetMountingSide_Param1                        = eMountedLeft;
/// \input          Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl  = eExtLightingAnimationReq_WelcomeDay;
/// \input          Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                      = SIG_VALID;
/// \input          AnimMa_unActiveBlocksCnt                                          = 18u;
/// \input          AnimMa_ucActiveSeqCnt                                             = 2u;
/// \input          ulActiveBlkId                                                     = 0u;
/// \input          AnimMa_aActiveBlocks[ulActiveBlkId].ucBlkCtxIdx                   = 5u;
///
///   - Expectations:
///
/// \output         Anima_TgtAniArr.boPriority ==  PRIORITY_ANIMATION_NONE;
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_InitBlockContext_RUN10(void)
{
    uint32 ulActiveBlkId;
    //Step 1) Set pre-conditions,Assign Input values
    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaBlink;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset0_RUN) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset0_RUN[i];
    }
    AnimMa_pCodingData = &AnimaCodingAreaBlink;
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
    Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    AnimMa_unActiveBlocksCnt                                         = 18u;
    AnimMa_ucActiveSeqCnt                                            = 2u;
    ulActiveBlkId                                                    = 0u;
    AnimMa_aActiveBlocks[ulActiveBlkId].ucBlkCtxIdx                  = 5u;

    //Step 2) Call FUT
    AnimMa_InitBlockContext(ulActiveBlkId);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Anima_AnimMa_InitBlockContext_RUNN
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that anima do not start if number of allocated blocks is not correct for RUNN block
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input            Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input            Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
/// \input            Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;
/// \input            Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input            AnimMa_unActiveBlocksCnt                                         = 18u;
/// \input            AnimMa_ucActiveSeqCnt                                            = 2u;
/// \input            ulActiveBlkId                                                    = 0u;
/// \input            AnimMa_aActiveBlocks[ulActiveBlkId].ucBlkCtxIdx                  = 5u;
/// \input            AnimMa_aActiveBlocks[ulActiveBlkId].unGenParamCodIdx             = 11u;
///
///   - Expectations:
///
/// \output         Anima_TgtAniArr.boPriority ==  PRIORITY_ANIMATION_NONE;
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_InitBlockContext_RUNN(void)
{
    uint32 ulActiveBlkId;
    //Step 1) Set pre-conditions,Assign Input values
    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaBlink;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset0_RUNN) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset0_RUNN[i];
    }

    AnimMa_pCodingData = &AnimaCodingAreaBlink;
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
    Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    AnimMa_unActiveBlocksCnt                                         = 18u;
    AnimMa_ucActiveSeqCnt                                            = 2u;
    ulActiveBlkId                                                    = 0u;
    AnimMa_aActiveBlocks[ulActiveBlkId].ucBlkCtxIdx                  = 5u;
    AnimMa_aActiveBlocks[ulActiveBlkId].unGenParamCodIdx             = 11u;

    //Step 2) Call FUT
    AnimMa_InitBlockContext(ulActiveBlkId);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Anima_AnimMa_InitBlockContext_SPARKLEXOR
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that anima do not start if number of allocated blocks is not correct for SPARKLE XOR block
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input            Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input            Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
/// \input            Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;
/// \input            Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input            AnimMa_unActiveBlocksCnt                                         = 18u;
/// \input            AnimMa_ucActiveSeqCnt                                            = 2u;
/// \input            ulActiveBlkId                                                    = 0u;
/// \input            AnimMa_aActiveBlocks[ulActiveBlkId].ucBlkCtxIdx                  = 5u;
/// \input            AnimMa_aActiveBlocks[ulActiveBlkId].unGenParamCodIdx             = 11u;
///
///   - Expectations:
///
/// \output         Anima_TgtAniArr.boPriority ==  PRIORITY_ANIMATION_NONE;
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_InitBlockContext_SPARKLEXOR(void)
{
    uint32 ulActiveBlkId;
    //Step 1) Set pre-conditions,Assign Input values
    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaBlink;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset0_SXOR) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset0_SXOR[i];
    }

    AnimMa_pCodingData = &AnimaCodingAreaBlink;
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
    Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    AnimMa_unActiveBlocksCnt                                         = 18u;
    AnimMa_ucActiveSeqCnt                                            = 2u;
    ulActiveBlkId                                                    = 0u;
    AnimMa_aActiveBlocks[ulActiveBlkId].ucBlkCtxIdx                  = 5u;
    AnimMa_aActiveBlocks[ulActiveBlkId].unGenParamCodIdx             = 11u;

    //Step 2) Call FUT
    AnimMa_InitBlockContext(ulActiveBlkId);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Anima_AnimMa_InitBlockContext_FLEX
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that anima do not start if number of allocated blocks is not correct for FLEX block
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input            Rte_Read_CodM_Anima_Para_Param1.eCodingState                      = eParaFct0_CodingDataValid;
/// \input            Rte_Read_IoHwAbUser_GetMountingSide_Param1                        = eMountedLeft;
/// \input            Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl  = eExtLightingAnimationReq_WelcomeDay;
/// \input            Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                      = SIG_VALID;
/// \input            AnimMa_unActiveBlocksCnt                                          = 18u;
/// \input            AnimMa_ucActiveSeqCnt                                             = 2u;
/// \input            ulActiveBlkId                                                     = 0u;
/// \input            AnimMa_aActiveBlocks[ulActiveBlkId].ucBlkCtxIdx                   = 5u;
/// \input            AnimMa_aActiveBlocks[ulActiveBlkId].unGenParamCodIdx              = 11u;
///
///   - Expectations:
///
/// \output         Anima_TgtAniArr.boPriority ==  PRIORITY_ANIMATION_NONE;
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_InitBlockContext_FLEX(void)
{
    uint32 ulActiveBlkId;
    //Step 1) Set pre-conditions,Assign Input values
    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaBlink;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset0_FLEX) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset0_FLEX[i];
    }

    AnimMa_pCodingData = &AnimaCodingAreaBlink;
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                       = eParaFct0_CodingDataValid;
    Rte_Read_IoHwAbUser_GetMountingSide_Param1                         = eMountedLeft;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl   = eExtLightingAnimationReq_WelcomeDay;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                       = SIG_VALID;
    AnimMa_unActiveBlocksCnt                                           = 18u;
    AnimMa_ucActiveSeqCnt                                              = 2u;
    ulActiveBlkId                                                      = 0u;
    AnimMa_aActiveBlocks[ulActiveBlkId].ucBlkCtxIdx                    = 5u;
    AnimMa_aActiveBlocks[ulActiveBlkId].unGenParamCodIdx               = 11u;

    //Step 2) Call FUT
    AnimMa_InitBlockContext(ulActiveBlkId);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Anima_AnimMa_InitBlockContext_PICEWISE
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that anima do not start if number of allocated blocks is not correct for PIXEWISE LINEAR block
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input            AnimMa_pCodingData                                               = &AnimaCodingAreaBlink;
/// \input            Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input            Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
/// \input            Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;
/// \input            Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input            AnimMa_unActiveBlocksCnt                                         = 18u;
/// \input            AnimMa_ucActiveSeqCnt                                            = 2u;
/// \input            ulActiveBlkId                                                    = 0u;
/// \input            AnimMa_aActiveBlocks[ulActiveBlkId].ucBlkCtxIdx                  = 5u;
/// \input            AnimMa_aActiveBlocks[ulActiveBlkId].unGenParamCodIdx             = 11u;
///
///   - Expectations:
///
/// \output         Anima_TgtAniArr.boPriority ==  PRIORITY_ANIMATION_NONE;
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_InitBlockContext_PICEWISE(void)
{
    uint32 ulActiveBlkId;
    //Step 1) Set pre-conditions,Assign Input values
    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaBlink;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset0_PICEWISE) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset0_PICEWISE[i];
    }

    AnimMa_pCodingData = &AnimaCodingAreaBlink;
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
    Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    AnimMa_unActiveBlocksCnt                                         = 18u;
    AnimMa_ucActiveSeqCnt                                            = 2u;
    ulActiveBlkId                                                    = 0u;
    AnimMa_aActiveBlocks[ulActiveBlkId].ucBlkCtxIdx                  = 5u;
    AnimMa_aActiveBlocks[ulActiveBlkId].unGenParamCodIdx             = 11u;

    //Step 2) Call FUT
    AnimMa_InitBlockContext(ulActiveBlkId);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Anima_AnimMa_InitBlockContext
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check start sequence
///
/// \Expected test results : All test cases contained are passed
///
//----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_AnimMa_InitBlockContext(void)
{
    Mt_CtrlLed_Anima_AnimMa_InitBlockContext_RUN10();
    Mt_CtrlLed_Anima_AnimMa_InitBlockContext_RUNN();
    Mt_CtrlLed_Anima_AnimMa_InitBlockContext_SPARKLEXOR();
    Mt_CtrlLed_Anima_AnimMa_InitBlockContext_FLEX();
    Mt_CtrlLed_Anima_AnimMa_InitBlockContext_PICEWISE();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Anima_Cycle10_CheckBlocksNotUsedInP64animas
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that animation not used in P64 configurations are working
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks        = &AnimaCodingAreaBlink;
/// \input           AnimMa_pCodingData                                               = &AnimaCodingAreaBlink
/// \input           Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
/// \input           Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input           AnimMa_unActiveBlocksCnt                                         = 18u
/// \input           AnimMa_ucActiveSeqCnt                                            = 2u
///
///   - Expectations:
///
/// \output         Anima_Tgt()->unTgtAni[j]   = aExpectedCheckBlocksNotUsedInP64animas[i].aunHopt[j]
/// \output         Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_RUNNING
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Anima_Cycle10_CheckBlocksNotUsedInP64animas(void)
{
    int i, j;
    //Step 1) Set pre-conditions,Assign Input values
    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Start(" Test_Mt_Anima_Cycle10_CheckBlocksNotUsedInP64animas.txt");
#endif

    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks       = &AnimaCodingAreaBlink;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset0_BlocksNotUsed) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset0_BlocksNotUsed[i];
    }

    AnimMa_pCodingData                                               = &AnimaCodingAreaBlink;
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
    Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedLeft;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    AnimMa_unActiveBlocksCnt                                         = 18u;
    AnimMa_ucActiveSeqCnt                                            = 2u;

    for (i = 0; i < 300; i++)
    {    //Step 2) Call FUT
        Anima_Cycle10();
        for (j = 0; j < 10; j++)
        {
            //Step 3) Check expected output values
            AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], aExpectedCheckBlocksNotUsedInP64animas[i].aunHopt[j], == );
        }
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_RUNNING, == );

        //Cfg logging
#if CFG_ENABLE_LOGGING == 1
        Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d } }\n", 10 * i
            , (int)Anima_Tgt()->unTgtAni[0]
            , (int)Anima_Tgt()->unTgtAni[1]
            , (int)Anima_Tgt()->unTgtAni[2]
            , (int)Anima_Tgt()->unTgtAni[3]
            , (int)Anima_Tgt()->unTgtAni[4]
            , (int)Anima_Tgt()->unTgtAni[5]
            , (int)Anima_Tgt()->unTgtAni[6]
            , (int)Anima_Tgt()->unTgtAni[7]
            , (int)Anima_Tgt()->unTgtAni[8]
            , (int)Anima_Tgt()->unTgtAni[9]
        );
#endif
    }

    //stop previus animation
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_None;
    AnimMa_clearSequence(eExtLightingAnimationReq_WelcomeDay);
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    //Step 2) Call FUT
    Anima_Cycle10();
    for (j = 0; j < 10; j++)
    {
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], 0u, == );
    }
    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );

    //Cfg logging
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d } }\n", 10 * i
        , (int)Anima_Tgt()->unTgtAni[0]
        , (int)Anima_Tgt()->unTgtAni[1]
        , (int)Anima_Tgt()->unTgtAni[2]
        , (int)Anima_Tgt()->unTgtAni[3]
        , (int)Anima_Tgt()->unTgtAni[4]
        , (int)Anima_Tgt()->unTgtAni[5]
        , (int)Anima_Tgt()->unTgtAni[6]
        , (int)Anima_Tgt()->unTgtAni[7]
        , (int)Anima_Tgt()->unTgtAni[8]
        , (int)Anima_Tgt()->unTgtAni[9]
    );
#endif

#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Stop();
#endif
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_rcBlockPiecewiseLinear
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that index is updated when picewise linear is running
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           Rte_Read_CodM_Anima_Para_Param1.eCodingState                                                    = eParaFct0_CodingDataValid;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                                                    = SIG_VALID;
/// \input           AnimMa_unActiveBlocksCnt                                                                        = 18u;
/// \input           AnimMa_ucActiveSeqCnt                                                                           = 2u;
/// \input           ulTime                                                                                          = 0u;
/// \input           ulActiveBlkId                                                                                   = 28u;
/// \input           AnimMa_aActiveBlocks[ulActiveBlkId].ucBlkCtxIdx                                                 = 0u;
/// \input           AnimMa_aActiveBlocksPiecewiseLinear[AnimMa_aActiveBlocks[ulActiveBlkId].ucBlkCtxIdx].ulNextTime = 0u;
/// \input           AnimMa_aActiveBlocksPiecewiseLinear[AnimMa_aActiveBlocks[ulActiveBlkId].ucBlkCtxIdx].ucIdx      = 0u;
///
///   - Expectations:
///
/// \output         AnimMa_aActiveBlocksPiecewiseLinear[AnimMa_aActiveBlocks[ulActiveBlkId].ucBlkCtxIdx].ucIdx = 1u;
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_rcBlockPiecewiseLinear(void)
{
    int i, j;
    uint32 ulActiveBlkId;
    uint32 ulTime;
    //Step 1) Set pre-conditions,Assign Input values

    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaBlink;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset0_BlocksNotUsed2) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset0_BlocksNotUsed2[i];
    }

    Rte_Read_CodM_Anima_Para_Param1.eCodingState                                                    = eParaFct0_CodingDataValid;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                                                    = SIG_VALID;
    AnimMa_unActiveBlocksCnt                                                                        = 18u;
    AnimMa_ucActiveSeqCnt                                                                           = 2u;
    ulTime                                                                                          = 0u;
    ulActiveBlkId                                                                                   = 28u;
    AnimMa_aActiveBlocks[ulActiveBlkId].ucBlkCtxIdx                                                 = 0u;
    AnimMa_aActiveBlocksPiecewiseLinear[AnimMa_aActiveBlocks[ulActiveBlkId].ucBlkCtxIdx].ulNextTime = 0u;
    AnimMa_aActiveBlocksPiecewiseLinear[AnimMa_aActiveBlocks[ulActiveBlkId].ucBlkCtxIdx].ucIdx      = 0u;

    //Step 2) Call FUT
    AnimMa_rcBlockPiecewiseLinear(ulActiveBlkId, ulTime);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(AnimMa_aActiveBlocksPiecewiseLinear[AnimMa_aActiveBlocks[ulActiveBlkId].ucBlkCtxIdx].ucIdx, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Cycle10_AnimaCSwitchValidtoValidAnima
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that if an animation is running and then the communication is lost , the anima continue until is done
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input            Rte_Read_CodM_Anima_Para_Param1.eCodingState                         = eParaFct0_CodingDataValid;
/// \input            Rte_Read_SysMon_VehNetState_Param1.eSigQty                           = SIG_VALID;
/// \input            Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState             = eTI_NOMINAL;
/// \input            Rte_Read_SysMon_TurnIndicatorCmd_Req_Param1                          = ReqLighted_Off;
/// \input            Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty                        = SIG_VALID;
/// \input            Rte_Read_SysMon_StdLgtFcts_Req_Param1.eDrl_Request                   = ReqLighted_Off;
/// \input            Rte_Read_SysMon_StdLgtFcts_Req_Param1.eHbFlash_Request               = ReqLighted_Off;
/// \input            Rte_Read_SysMon_StdLgtFcts_Req_Param1.ePos_Request                   = ReqLighted_Off;
/// \input            Rte_Read_SysMon_LowBeamCmd_Req_Param1                                = ReqLighted_Off;
/// \input            Rte_Read_SysMon_StdLgtFcts_Req_Param1.eHb_Request                    = ReqLighted_Off;
/// \input                Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;
///
///   - Expectations:
///
/// \output         Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_RUNNING
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_AnimaCSwitchValidtoValidAnima(void)
{
    int i, j;
    //Step 1) Set pre-conditions,Assign Input values

    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaC;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset0_AnimaC) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset0_AnimaC[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
    Rte_Read_SysMon_VehNetState_Param1.eSigQty                       = SIG_VALID;
    Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState         = eTI_NOMINAL;
    Rte_Read_SysMon_TurnIndicatorCmd_Req_Param1                      = ReqLighted_Off;
    Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty                    = SIG_VALID;
    Rte_Read_SysMon_StdLgtFcts_Req_Param1.eDrl_Request               = ReqLighted_Off;
    Rte_Read_SysMon_StdLgtFcts_Req_Param1.eHbFlash_Request           = ReqLighted_Off;
    Rte_Read_SysMon_StdLgtFcts_Req_Param1.ePos_Request               = ReqLighted_Off;
    Rte_Read_SysMon_LowBeamCmd_Req_Param1                            = ReqLighted_Off;
    Rte_Read_SysMon_StdLgtFcts_Req_Param1.eHb_Request                = ReqLighted_Off;
    Rte_Read_SysMon_VehNetState_Param1.eSigQty                       = SIG_INVALID;
    Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState         = eTI_NOMINAL;
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;

    for (i = 0; i < 3000; i++)
    {
        //Step 2) Call FUT
        Anima_Cycle10();
        for (j = 0; j < 27; j++)//number of pixels
        {
            Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_ByeByeDay;

        }
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_RUNNING, == );
    }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Cycle10_AnimaInvalid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Test that no animation request is not followed if first request is invalid
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input            Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
/// \input            Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_Invalid;
///
///   - Expectations:
///
/// \output           Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_NONE
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_AnimaInvalid(void)
{
    //Step 1) Set pre-conditions,Assign Input values
    Rte_Read_SigPrep_AnimationReq_Param1.eSigQty                     = SIG_VALID;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_Invalid;

    //Step 2) Call FUT
    Anima_Cycle10();

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Cycle10_AnimaPriorityNone
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that animation WelcomeDay is not started if the priority is not correctly set
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input           Rte_Read_CodM_Anima_Para_Param1.eCodingState             = eParaFct0_CodingDataValid;
/// \input           Rte_Read_SysMon_VehNetState_Param1.eSigQty               = SIG_VALID;
/// \input           Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eTI_NOMINAL;
/// \input           Rte_Read_SysMon_TurnIndicatorCmd_Req_Param1              = ReqLighted_Off;
/// \input           Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty            = SIG_VALID;
/// \input           Rte_Read_SysMon_StdLgtFcts_Req_Param1.eDrl_Request       = ReqLighted_Off;
/// \input           Rte_Read_SysMon_StdLgtFcts_Req_Param1.eHbFlash_Request   = ReqLighted_Off;
/// \input           Rte_Read_SysMon_StdLgtFcts_Req_Param1.ePos_Request       = ReqLighted_Off;
/// \input           Rte_Read_SysMon_LowBeamCmd_Req_Param1                    = ReqLighted_Off;
/// \input           Rte_Read_SysMon_StdLgtFcts_Req_Param1.eHb_Request        = ReqLighted_On;
/// \input           Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;
///
///   - Expectations:
///
/// \output        Anima_Tgt()->unTgtAni[j]    = 0U
/// \output         Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_NONE
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle10_AnimaPriorityNone(void)
{
    int i, j;
    //Step 1) Set pre-conditions,Assign Input values
    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaC;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(Anima_CodPrj_aucDataset0_AnimaC) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = Anima_CodPrj_aucDataset0_AnimaC[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState                     = eParaFct0_CodingDataValid;
    Rte_Read_SysMon_VehNetState_Param1.eSigQty                       = SIG_VALID;
    Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState         = eTI_NOMINAL;
    Rte_Read_SysMon_TurnIndicatorCmd_Req_Param1                      = ReqLighted_Off;
    Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty                    = SIG_VALID;
    Rte_Read_SysMon_StdLgtFcts_Req_Param1.eDrl_Request               = ReqLighted_Off;
    Rte_Read_SysMon_StdLgtFcts_Req_Param1.eHbFlash_Request           = ReqLighted_Off;
    Rte_Read_SysMon_StdLgtFcts_Req_Param1.ePos_Request               = ReqLighted_Off;
    Rte_Read_SysMon_LowBeamCmd_Req_Param1                            = ReqLighted_Off;
    Rte_Read_SysMon_StdLgtFcts_Req_Param1.eHb_Request                = ReqLighted_On;
    Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl = eExtLightingAnimationReq_WelcomeDay;

    //Step 2) Call FUT
    Anima_Cycle10();

    for (i = 0; i < 3000; i++)
    {
        for (j = 0; j < 27; j++)//number of pixels
        {
            //Step 3) Check expected output values
            AL_UNITTEST_CHECK(Anima_Tgt()->unTgtAni[j], 0U, == );
        }
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK((uint32)Anima_TgtAniArr.boPriority, PRIORITY_ANIMATION_NONE, == );
    }
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_CtrlLed_rcAnimMa50_Dataset4_AllBlocks
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check execution of multiple sequences and switched between sequences-start/stop/softstop sequence
///                     that animation of sequence 0 and sequence 1 of dataset 4 is executed correctly (dataset 4 contains all block types).
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input            Rte_Read_CodM_Anima_Para_Param1.eCodingState  = eParaFct0_CodingDataValid;
/// \input            Rte_Read_IoHwAbUser_GetMountingSide_Param1    = eMountedLeft;
/// \input           
/// \input           
///
///   - Expectations:
///
/// \output         AnimMaRamp_aucPxlIntTgt[j] = aExpected_Mt_AnimMa_Cycle50_Dataset5_DimInterrupt[i].aunHopt[j]     when anima starts
/// \output         AnimMaRamp_aucPxlIntTgt[j] = aExpected_Mt_AnimMa_Cycle50_Dataset5_DimInterrupt[i + k].aunHopt[j] when anima stops
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_rcAnimMa50_Dataset4_AllBlocks(void)
{
    int i, j, k;
    //Step 1) Set pre-conditions,Assign Input values
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Start("Mt_AnimMa_Cycle50_Dataset5_DimInterrupt.txt");
#endif

    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaC;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(AnimMa_CodPrj_aucDataset5_Dim_Dim) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = AnimMa_CodPrj_aucDataset5_Dim_Dim[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState = eParaFct0_CodingDataValid;
    Rte_Read_IoHwAbUser_GetMountingSide_Param1   = eMountedLeft;
    AnimMa_startSequence(0);

    for (i = 0; i < 10; i++)
    {   //Step 2) Call FUT
        rcAnimMa50();
        for (j = 0; j < 10; j++)
        {
            //Step 3) Check expected output values
            AL_UNITTEST_CHECK(AnimMaRamp_aucPxlIntTgt[j], aExpected_Mt_AnimMa_Cycle50_Dataset5_DimInterrupt[i].aunHopt[j], == );
        }
#if CFG_ENABLE_LOGGING == 1
        Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d } }\n", 50 * i
            , (int)AnimMaRamp_aucPxlIntTgt[0]
            , (int)AnimMaRamp_aucPxlIntTgt[1]
            , (int)AnimMaRamp_aucPxlIntTgt[2]
            , (int)AnimMaRamp_aucPxlIntTgt[3]
            , (int)AnimMaRamp_aucPxlIntTgt[4]
            , (int)AnimMaRamp_aucPxlIntTgt[5]
            , (int)AnimMaRamp_aucPxlIntTgt[6]
            , (int)AnimMaRamp_aucPxlIntTgt[7]
            , (int)AnimMaRamp_aucPxlIntTgt[8]
            , (int)AnimMaRamp_aucPxlIntTgt[9]
        );
#endif
    }
    k = i;
    AnimMa_softStopSequence(0);
    for (i = 0; i < 20; i++)
    {   //Step 2) Call FUT
        rcAnimMa50();
        for (j = 0; j < 10; j++)
        {
            //Step 3) Check expected output values
            AL_UNITTEST_CHECK(AnimMaRamp_aucPxlIntTgt[j], aExpected_Mt_AnimMa_Cycle50_Dataset5_DimInterrupt[i + k].aunHopt[j], == );
        }
#if CFG_ENABLE_LOGGING == 1
        Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d } }\n", 50 * i
            , (int)AnimMaRamp_aucPxlIntTgt[0]
            , (int)AnimMaRamp_aucPxlIntTgt[1]
            , (int)AnimMaRamp_aucPxlIntTgt[2]
            , (int)AnimMaRamp_aucPxlIntTgt[3]
            , (int)AnimMaRamp_aucPxlIntTgt[4]
            , (int)AnimMaRamp_aucPxlIntTgt[5]
            , (int)AnimMaRamp_aucPxlIntTgt[6]
            , (int)AnimMaRamp_aucPxlIntTgt[7]
            , (int)AnimMaRamp_aucPxlIntTgt[8]
            , (int)AnimMaRamp_aucPxlIntTgt[9]
        );
#endif
    }
    AnimMa_stopSequence(0);
    for (j = 0; j < 10; j++)
    {  //Step 2) Call FUT
        rcAnimMa50();
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK(AnimMaRamp_aucPxlIntTgt[j], aExpected_Mt_AnimMa_Cycle50_Dataset5_DimInterrupt[i + k].aunHopt[j], == );
    }
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d } }\n", 50 * i
        , (int)AnimMaRamp_aucPxlIntTgt[0]
        , (int)AnimMaRamp_aucPxlIntTgt[1]
        , (int)AnimMaRamp_aucPxlIntTgt[2]
        , (int)AnimMaRamp_aucPxlIntTgt[3]
        , (int)AnimMaRamp_aucPxlIntTgt[4]
        , (int)AnimMaRamp_aucPxlIntTgt[5]
        , (int)AnimMaRamp_aucPxlIntTgt[6]
        , (int)AnimMaRamp_aucPxlIntTgt[7]
        , (int)AnimMaRamp_aucPxlIntTgt[8]
        , (int)AnimMaRamp_aucPxlIntTgt[9]
    );
#endif

#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Stop();
#endif
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_TimeCondEndSeq 
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check if stop blocks are executed
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input               Rte_Read_CodM_Anima_Para_Param1.eCodingState         = eParaFct0_CodingDataValid;
/// \input               ulActiveBlkId                                        = 30U;
/// \input               ulTime                                               = 0U;
/// \input               pulStopTime                                          = 12750u;
/// \input               AnimMa_aActiveBlocks[ulActiveBlkId].unGenParamCodIdx = 15U;
///
///   - Expectations:
///
/// \output         bRet = true;
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_TimeCondEndSeq(void)
{
    uint32 ulActiveBlkId;
    uint32 ulTime;
    uint32 pulStopTime;
    bool bRet;
    //Step 1) Set pre-conditions,Assign Input values
    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaC;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(AnimMa_CodPrj_aucDataset5_Dim2) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = AnimMa_CodPrj_aucDataset5_Dim2[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState           = eParaFct0_CodingDataValid;
    ulActiveBlkId                                          = 30U;
    ulTime                                                 = 0U;
    pulStopTime                                            = 12750u;
    AnimMa_aActiveBlocks[ulActiveBlkId].unGenParamCodIdx   = 15U;

    //Step 2) Call FUT
    bRet = AnimMa_TimeCondEndSeq(ulActiveBlkId, ulTime, &pulStopTime);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(bRet, true, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Cycle50_StopBlocks 
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check if stop blocks are executed in a sequence
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input               Rte_Read_CodM_Anima_Para_Param1.eCodingState = eParaFct0_CodingDataValid;
/// \input               Rte_Read_IoHwAbUser_GetMountingSide_Param1   = eMountedLeft;
/// \input           
/// \input           
///
///   - Expectations:
///
/// \output         AnimMaRamp_aucPxlIntTgt[j] = aExpected_Mt_AnimMa_Cycle50_StopBlocks[i].aunHopt[j]      when anima starts
/// \output         AnimMaRamp_aucPxlIntTgt[j] = aExpected_Mt_AnimMa_Cycle50_StopBlocks[i + k].aunHopt[j]  when anima stops
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_rcAnimMa50_StopBlocks(void)
{
    int i, j, k;
    //Step 1) Set pre-conditions,Assign Input values
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Start("Mt_AnimMa_Cycle50_StopBlocks.txt");
#endif

    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaC;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(AnimMa_CodPrj_aucDataset_StopBlocks) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = AnimMa_CodPrj_aucDataset_StopBlocks[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState = eParaFct0_CodingDataValid;
    Rte_Read_IoHwAbUser_GetMountingSide_Param1   = eMountedLeft;
    AnimMa_startSequence(0);

    for (i = 0; i < 1000 / 50; i++)
    {    //Step 2) Call FUT
        rcAnimMa50();
        for (j = 0; j < 10; j++)
        {
            //Step 3) Check expected output values
            AL_UNITTEST_CHECK(AnimMaRamp_aucPxlIntTgt[j], aExpected_Mt_AnimMa_Cycle50_StopBlocks[i].aunHopt[j], == );
        }
#if CFG_ENABLE_LOGGING == 1
        Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d } }\n", 50 * i
            , (int)AnimMaRamp_aucPxlIntTgt[0]
            , (int)AnimMaRamp_aucPxlIntTgt[1]
            , (int)AnimMaRamp_aucPxlIntTgt[2]
            , (int)AnimMaRamp_aucPxlIntTgt[3]
            , (int)AnimMaRamp_aucPxlIntTgt[4]
            , (int)AnimMaRamp_aucPxlIntTgt[5]
            , (int)AnimMaRamp_aucPxlIntTgt[6]
            , (int)AnimMaRamp_aucPxlIntTgt[7]
            , (int)AnimMaRamp_aucPxlIntTgt[8]
            , (int)AnimMaRamp_aucPxlIntTgt[9]
        );
#endif
    }
    k = i;
    AnimMa_softStopSequence(0);

    for (i = 0; i < 1000 / 50; i++)
    {    //Step 2) Call FUT
        rcAnimMa50();
        for (j = 0; j < 10; j++)
        {
            //Step 3) Check expected output values
            AL_UNITTEST_CHECK(AnimMaRamp_aucPxlIntTgt[j], aExpected_Mt_AnimMa_Cycle50_StopBlocks[i + k].aunHopt[j], == );
        }
#if CFG_ENABLE_LOGGING == 1
        Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d } }\n", 50 * i
            , (int)AnimMaRamp_aucPxlIntTgt[0]
            , (int)AnimMaRamp_aucPxlIntTgt[1]
            , (int)AnimMaRamp_aucPxlIntTgt[2]
            , (int)AnimMaRamp_aucPxlIntTgt[3]
            , (int)AnimMaRamp_aucPxlIntTgt[4]
            , (int)AnimMaRamp_aucPxlIntTgt[5]
            , (int)AnimMaRamp_aucPxlIntTgt[6]
            , (int)AnimMaRamp_aucPxlIntTgt[7]
            , (int)AnimMaRamp_aucPxlIntTgt[8]
            , (int)AnimMaRamp_aucPxlIntTgt[9]
        );
#endif
    }
    AnimMa_stopSequence(0);
    for (j = 0; j < 10; j++)
    { //Step 2) Call FUT
        rcAnimMa50();
        //Step 3) Check expected output values
        AL_UNITTEST_CHECK(AnimMaRamp_aucPxlIntTgt[j], aExpected_Mt_AnimMa_Cycle50_StopBlocks[i + k].aunHopt[j], == );
    }
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log(", { %4d, { %5d, %5d, %5d, %5d, %5d,   %5d, %5d, %5d, %5d, %5d } }\n", 50 * i
        , (int)AnimMaRamp_aucPxlIntTgt[0]
        , (int)AnimMaRamp_aucPxlIntTgt[1]
        , (int)AnimMaRamp_aucPxlIntTgt[2]
        , (int)AnimMaRamp_aucPxlIntTgt[3]
        , (int)AnimMaRamp_aucPxlIntTgt[4]
        , (int)AnimMaRamp_aucPxlIntTgt[5]
        , (int)AnimMaRamp_aucPxlIntTgt[6]
        , (int)AnimMaRamp_aucPxlIntTgt[7]
        , (int)AnimMaRamp_aucPxlIntTgt[8]
        , (int)AnimMaRamp_aucPxlIntTgt[9]
    );
#endif
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Stop();
#endif
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_rcStopBlock_TestCase1 
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check if stop block is executed on left side
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input               Rte_Read_CodM_Anima_Para_Param1.eCodingState = eParaFct0_CodingDataValid;
/// \input               ucMountingSide                               = 1u;
/// \input               ulActiveBlkId                                = 29u;
/// \input               ulTime                                       = 0u;
///
///   - Expectations:
///
/// \output         ret = false;
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_rcStopBlock_TestCase1(void)
{
    uint32 ulActiveBlkId;
    uint32 ulTime;
    uint8 ucMountingSide;
    bool ret;

    //Step 1) Set pre-conditions,Assign Input values
#if CFG_ENABLE_LOGGING == 1
    Mt_CtrlLed_Log_Start("Mt_AnimMa_Cycle50_StopBlocks.txt");
#endif

    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaC;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(AnimMa_CodPrj_aucDataset_StopBlocks2) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = AnimMa_CodPrj_aucDataset_StopBlocks2[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState = eParaFct0_CodingDataValid;
    ucMountingSide                               = 1u;
    ulActiveBlkId                                = 29u;
    ulTime                                       = 0u;
   
    //Step 2) Call FUT
    ret = AnimMa_rcStopBlock(ulActiveBlkId, ulTime, ucMountingSide);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(ret, false, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_rcStopBlock_TestCase2 
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check if stop block is executed on left side
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input               Rte_Read_CodM_Anima_Para_Param1.eCodingState = eParaFct0_CodingDataValid;
/// \input               ucMountingSide                               = 2u;
/// \input               ulActiveBlkId                                = 29u;
/// \input               ulTime                                       = 0u;
///
///   - Expectations:
///
/// \output         ret = false;
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_rcStopBlock_TestCase2(void)
{
    uint32 ulActiveBlkId;
    uint32 ulTime;
    uint8 ucMountingSide;
    bool ret;

    //Step 1) Set pre-conditions,Assign Input values

    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaC;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(AnimMa_CodPrj_aucDataset_StopBlocks3) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = AnimMa_CodPrj_aucDataset_StopBlocks3[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState = eParaFct0_CodingDataValid;
    ucMountingSide                               = 2u;
    ulActiveBlkId                                = 29u;
    ulTime                                       = 0u;

    //Step 2) Call FUT
    ret = AnimMa_rcStopBlock(ulActiveBlkId, ulTime, ucMountingSide);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(ret, false, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_rcStopBlock_TestCase3
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check if stop block is executed on left side and flag type 8 to run once
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input               Rte_Read_CodM_Anima_Para_Param1.eCodingState = eParaFct0_CodingDataValid;
/// \input               ucMountingSide                               = 1u;
/// \input               ulActiveBlkId                                = 29u;
/// \input               ulTime                                       = 600u;
///
///   - Expectations:
///
/// \output         ret = true;
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_rcStopBlock_TestCase3(void)
{
    uint32 ulActiveBlkId;
    uint32 ulTime;
    uint8 ucMountingSide;
    bool ret;

    //Step 1) Set pre-conditions,Assign Input values
    Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks = &AnimaCodingAreaC;
    // Set coding data on our RTE
    for (uint32 i = 0; i < sizeof(AnimMa_CodPrj_aucDataset_StopBlocks4) / sizeof(uint8); i++)
    {
        Rte_Read_CodM_Anima_Para_Param1.psCodingParameters_Blocks->Animation.AnimationByteStream.aucByteStream[i] = AnimMa_CodPrj_aucDataset_StopBlocks4[i];
    }
    Rte_Read_CodM_Anima_Para_Param1.eCodingState = eParaFct0_CodingDataValid;
    ucMountingSide                               = 1u;
    ulActiveBlkId                                = 29u;
    ulTime                                       = 600u;

    //Step 2) Call FUT
    ret = AnimMa_rcStopBlock(ulActiveBlkId, ulTime, ucMountingSide);

    //Step 3) Check expected output values
    AL_UNITTEST_CHECK(ret, true, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_AnimMa_StopBlock
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check start sequence
///
/// \Expected test results : All test cases contained are passed
///
//----------------------------------------------------------------------------
void Mt_CtrlLed_AnimMa_StopBlock(void)
{
    Mt_CtrlLed_rcAnimMa50_StopBlocks();
    Mt_CtrlLed_AnimMa_rcStopBlock_TestCase1();
    Mt_CtrlLed_AnimMa_rcStopBlock_TestCase2();
    Mt_CtrlLed_AnimMa_rcStopBlock_TestCase3();
}
//=============================================================================
// Add tests to the test suite
//=============================================================================
void ALUnitTest_AddTests(void)
{
    ALUnitTest_AddFunction("Mt_CtrlLed_AnimMa_DeleteBlocks"                            , Mt_CtrlLed_AnimMa_DeleteBlocks);
    ALUnitTest_AddFunction("Mt_CtrlLed_AnimMa_PiecewiseLinear_InitRamp"                , Mt_CtrlLed_AnimMa_PiecewiseLinear_InitRamp);
    ALUnitTest_AddFunction("Mt_CtrlLed_AnimMa_Ramp_Step"                               , Mt_CtrlLed_AnimMa_Ramp_Step);
    ALUnitTest_AddFunction("Mt_CtrlLed_AnimMa_muldiv32_ceil"                           , Mt_CtrlLed_AnimMa_muldiv32_ceil);
    ALUnitTest_AddFunction("Mt_CtrlLed_AnimMa_Ramp_UpdateDelta"                        , Mt_CtrlLed_AnimMa_Ramp_UpdateDelta);
    ALUnitTest_AddFunction("Mt_CtrlLed_AnimDoRamps"                                    , Mt_CtrlLed_AnimDoRamps);
    ALUnitTest_AddFunction("Mt_CtrlLed_Cycle10_BlocksCheck"                            , Mt_CtrlLed_Cycle10_BlocksCheck);
    ALUnitTest_AddFunction("Mt_CtrlLed_AnimMa_InterpolateDim"                          , Mt_CtrlLed_AnimMa_InterpolateDim);
    ALUnitTest_AddFunction("Mt_CtrlLed_AnimMa_GetPxlNr"                                , Mt_CtrlLed_AnimMa_GetPxlNr);
    ALUnitTest_AddFunction("Mt_AnimMa_AllocateBlockContext"                            , Mt_AnimMa_AllocateBlockContext);
    ALUnitTest_AddFunction("Mt_CtrlLed_AnimMa_DeleteBlockContext"                      , Mt_CtrlLed_AnimMa_DeleteBlockContext);
    ALUnitTest_AddFunction("Mt_CtrlLed_AnimMa_Blocks_Init"                             , Mt_CtrlLed_AnimMa_Blocks_Init);
    ALUnitTest_AddFunction("Mt_CtrlLed_AnimMa_TimeWarp"                                , Mt_CtrlLed_AnimMa_TimeWarp);
    ALUnitTest_AddFunction("Mt_CtrlLed_AnimMa_Repetition"                              , Mt_CtrlLed_AnimMa_Repetition);
    ALUnitTest_AddFunction("Mt_CtrlLed_AnimMa_EnableInitContext"                       , Mt_CtrlLed_AnimMa_EnableInitContext);
    ALUnitTest_AddFunction("Mt_CtrlLed_Anima_AnimMa_Cod_GetSequenceIdx"                , Mt_CtrlLed_Anima_AnimMa_Cod_GetSequenceIdx);
    ALUnitTest_AddFunction("Mt_CtrlLed_Anima_AnimMa_FindSequence"                      , Mt_CtrlLed_Anima_AnimMa_FindSequence);
    ALUnitTest_AddFunction("Mt_CtrlLed_Anima_AnimMa_IsIdxValid"                        , Mt_CtrlLed_Anima_AnimMa_IsIdxValid);
    ALUnitTest_AddFunction("Mt_CtrlLed_Anima_AnimMa_isSequenceActive"                  , Mt_CtrlLed_Anima_AnimMa_isSequenceActive);
    ALUnitTest_AddFunction("Mt_CtrlLed_Anima_AnimMa_isStopSequenceActive"              , Mt_CtrlLed_Anima_AnimMa_isStopSequenceActive);
    ALUnitTest_AddFunction("Mt_CtrlLed_Anima_AnimMa_isSeqActivePhase_WithNoRunningIDs" , Mt_CtrlLed_Anima_AnimMa_isSeqActivePhase_WithNoRunningIDs);
    ALUnitTest_AddFunction("Mt_CtrlLed_Anima_AnimMa_getElapsedTime"                    , Mt_CtrlLed_Anima_AnimMa_getElapsedTime);
    ALUnitTest_AddFunction("Mt_CtrlLed_Anima_AnimMa_stopSequence"                      , Mt_CtrlLed_Anima_AnimMa_stopSequence);
    ALUnitTest_AddFunction("Mt_CtrlLed_Anima_AnimMa_rcSequence"                        , Mt_CtrlLed_Anima_AnimMa_rcSequence);
    ALUnitTest_AddFunction("Mt_CtrlLed_Anima_AnimMa_startSequence"                     , Mt_CtrlLed_Anima_AnimMa_startSequence);
    ALUnitTest_AddFunction("Mt_CtrlLed_Anima_AnimMa_clearSequence"                     , Mt_CtrlLed_Anima_AnimMa_clearSequence);
    ALUnitTest_AddFunction("Mt_CtrlLed_Anima_AnimMa_softStopSequence"                  , Mt_CtrlLed_Anima_AnimMa_softStopSequence);
    ALUnitTest_AddFunction("Mt_CtrlLed_Anima_AnimMa_ActiveSeqNr"                       , Mt_CtrlLed_Anima_AnimMa_ActiveSeqNr);
    ALUnitTest_AddFunction("Mt_CtrlLed_Anima_rcAnimMa50"                               , Mt_CtrlLed_Anima_rcAnimMa50);
    ALUnitTest_AddFunction("Mt_CtrlLed_Anima_Cycle10_CheckBlocksNotUsedInP64animas"    , Mt_CtrlLed_Anima_Cycle10_CheckBlocksNotUsedInP64animas);
    ALUnitTest_AddFunction("Mt_CtrlLed_AnimMa_rcBlockPiecewiseLinear"                  , Mt_CtrlLed_AnimMa_rcBlockPiecewiseLinear);
    ALUnitTest_AddFunction("Mt_CtrlLed_Cycle10_Animations_test"                        , Mt_CtrlLed_Cycle10_Animations_test);
    ALUnitTest_AddFunction("Mt_CtrlLed_Cycle10_AnimaCSwitchValidtoValidAnima"          , Mt_CtrlLed_Cycle10_AnimaCSwitchValidtoValidAnima);
    ALUnitTest_AddFunction("Mt_CtrlLed_Cycle10_Etat_Anima"                             , Mt_CtrlLed_Cycle10_Etat_Anima);
    ALUnitTest_AddFunction("Mt_CtrlLed_Cycle10_AnimaCPriority"                         , Mt_CtrlLed_Cycle10_AnimaCPriority);
    ALUnitTest_AddFunction("Mt_CtrlLed_Cycle10_AnimaInvalid"                           , Mt_CtrlLed_Cycle10_AnimaInvalid);
    ALUnitTest_AddFunction("Mt_CtrlLed_Cycle10_AnimaPriorityNone"                      , Mt_CtrlLed_Cycle10_AnimaPriorityNone);
    ALUnitTest_AddFunction("Mt_CtrlLed_Anima_Anima_ReadFrontTurnIndicatorCmd"          , Mt_CtrlLed_Anima_Anima_ReadFrontTurnIndicatorCmd);
    ALUnitTest_AddFunction("Mt_CtrlLed_Cycle10_AnimaCInvalid"                          , Mt_CtrlLed_Cycle10_AnimaCInvalid);
    ALUnitTest_AddFunction("Mt_CtrlLed_rcAnimMa50_Dataset4_AllBlocks"                  , Mt_CtrlLed_rcAnimMa50_Dataset4_AllBlocks);
    ALUnitTest_AddFunction("Mt_CtrlLed_AnimMa_TimeCondEndSeq"                          , Mt_CtrlLed_AnimMa_TimeCondEndSeq);
    ALUnitTest_AddFunction("Mt_CtrlLed_AnimMa_StopBlock"                               , Mt_CtrlLed_AnimMa_StopBlock);
    ALUnitTest_AddFunction("Mt_CtrlLed_AnimMa_AllocateBlocks"                          , Mt_CtrlLed_AnimMa_AllocateBlocks);
    ALUnitTest_AddFunction("Mt_CtrlLed_AnimMa_getMountSide"                            , Mt_CtrlLed_AnimMa_getMountSide);
    ALUnitTest_AddFunction("Mt_CtrlLed_Anima_roAnima_ParaFct0"                         , Mt_CtrlLed_Anima_roAnima_ParaFct0);
    ALUnitTest_AddFunction("Mt_CtrlLed_Anima_AnimMa_setCodingData"                     , Mt_CtrlLed_Anima_AnimMa_setCodingData);
    ALUnitTest_AddFunction("Mt_CtrlLed_AnimMa_rcBlockRun10"                            , Mt_CtrlLed_AnimMa_rcBlockRun10);
    ALUnitTest_AddFunction("Mt_CtrlLed_AnimMa_LfsrShift"                               , Mt_CtrlLed_AnimMa_LfsrShift);
    ALUnitTest_AddFunction("Mt_CtrlLed_AnimMa_rcBlockSparkleLfsr"                      , Mt_CtrlLed_AnimMa_rcBlockSparkleLfsr);
    ALUnitTest_AddFunction("Mt_CtrlLed_AnimMa_rcBlockClamp"                            , Mt_CtrlLed_AnimMa_rcBlockClamp);
    ALUnitTest_AddFunction("Mt_CtrlLed_Anima_AnimMa_InitBlockContext"                  , Mt_CtrlLed_Anima_AnimMa_InitBlockContext);
}

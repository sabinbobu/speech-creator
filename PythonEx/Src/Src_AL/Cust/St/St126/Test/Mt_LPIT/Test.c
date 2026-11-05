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
/// \file  Test.c
///
///
/// \brief Module test for LPTMR
///
/// 
/// 
/// author 
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//=============================================================================
// includes
//=============================================================================

#include "Test.h"

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_Init_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function issues a fotware reset for all channels and registers
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_Init_Param1                      = NULL_PTR;
///
/// - Expectations:
///
/// \output Lpit_Drv_Init_RetVal                 = E_OK;
/// \output Lpit_Drv_LpitSetDebugMode_Param1.MCR = 0u;
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_Init_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_Init_Param1 = NULL_PTR;
  
  //Step 3) Call FUT

  Lpit_Init(Lpit_Init_Param1);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(Lpit_Drv_Init_RetVal,               E_OK, == );
  AL_UNITTEST_CHECK(Lpit_Drv_LpitSetDebugMode_Param1.MCR, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_Init_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function issues a fotware reset for all channels and registers
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_Init_Param1                                = NULL_PTR;
/// \input LPIT0_BASE->PARAM                               = 5u;
/// \input Lpit_Init_Param1.sLpitInstanceCfg.psLpitInstCfg = 5u;
///
/// - Expectations:
///
/// \output Lpit_Drv_Init_RetVal                            = E_OK
/// \output Lpit_Drv_LpitSetDebugMode_Param1.MCR            = 0u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_Init_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  LPIT0_BASE->PARAM                                = 5u;
  Lpit_Init_Param1                                 = LPIT0_BASE;
  Lpit_Init_Param1->sLpitInstanceCfg.psLpitInstCfg = 5u;

  //Step 3) Call FUT

  Lpit_Init(Lpit_Init_Param1);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(Lpit_Drv_Init_RetVal,               E_OK, == );
  AL_UNITTEST_CHECK(Lpit_Drv_LpitSetDebugMode_Param1.MCR, 0u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_Drv_LpitSetDebugMode_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function sets the debug mode
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_Drv_LpitSetDebugMode_Param1.MCR   = 10u
/// \input Lpit_Drv_LpitSetDebugMode_Param2       = 0u
///
/// - Expectations:
///
/// \output Lpit_Drv_LpitSetDebugMode_Param1.MCR  = 2u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_Drv_LpitSetDebugMode_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_Drv_LpitSetDebugMode_Param1.MCR = 10u;
  Lpit_Drv_LpitSetDebugMode_Param2 = 0u;
  
  //Step 3) Call FUT

  Lpit_Drv_LpitSetDebugMode(&Lpit_Drv_LpitSetDebugMode_Param1, Lpit_Drv_LpitSetDebugMode_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(Lpit_Drv_LpitSetDebugMode_Param1.MCR, 2u,==);
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_Drv_LpitSetDebugMode_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function sets the debug mode
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_Drv_LpitSetDebugMode_Param1.MCR   = 10u
/// \input Lpit_Drv_LpitSetDebugMode_Param2       = 15u
///
/// - Expectations:
///
/// \output Lpit_Drv_LpitSetDebugMode_Param1.MCR  = 10u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_Drv_LpitSetDebugMode_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_Drv_LpitSetDebugMode_Param1.MCR = 10u;
  Lpit_Drv_LpitSetDebugMode_Param2     = 15u;

  //Step 3) Call FUT

  Lpit_Drv_LpitSetDebugMode(&Lpit_Drv_LpitSetDebugMode_Param1, Lpit_Drv_LpitSetDebugMode_Param2);

  //Step 4) Check expected output values-

  AL_UNITTEST_CHECK(Lpit_Drv_LpitSetDebugMode_Param1.MCR, 10u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_Drv_LpitSetDozeMode_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function sets the doze mode
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_Drv_LpitSetDozeMode_Param1.MCR   = 10u
/// \input Lpit_Drv_LpitSetDozeMode_Param2       = 0u
///
/// - Expectations:
///
/// \output Lpit_Drv_LpitSetDozeMode_Param1.MCR  = 15u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_Drv_LpitSetDozeMode_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_Drv_LpitSetDozeMode_Param1.MCR = 15u;
  Lpit_Drv_LpitSetDozeMode_Param2     = 1u;

  //Step 3) Call FUT

  Lpit_Drv_LpitSetDozeMode(&Lpit_Drv_LpitSetDozeMode_Param1, Lpit_Drv_LpitSetDozeMode_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(Lpit_Drv_LpitSetDozeMode_Param1.MCR, 15u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_Drv_LpitSetDozeMode_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function sets the doze mode
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_Drv_LpitSetDozeMode_Param1.MCR   = 10u
/// \input Lpit_Drv_LpitSetDozeMode_Param2       = 15u
///
/// - Expectations:
///
/// \output Lpit_Drv_LpitSetDozeMode_Param1.MCR  = 10u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_Drv_LpitSetDozeMode_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_Drv_LpitSetDozeMode_Param1.MCR = 10u;
  Lpit_Drv_LpitSetDozeMode_Param2     = 15u;

  //Step 3) Call FUT

  Lpit_Drv_LpitSetDozeMode(&Lpit_Drv_LpitSetDozeMode_Param1, Lpit_Drv_LpitSetDozeMode_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(Lpit_Drv_LpitSetDozeMode_Param1.MCR, 10u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_Drv_LpitSetModEnblStat_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function sets the doze mode
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_Drv_LpitSetModEnblStat_Param1.MCR   = 10u
/// \input Lpit_Drv_LpitSetModEnblStat_Param2       = 1u
///
/// - Expectations:
///
/// \output Lpit_Drv_LpitSetModEnblStat_Param1.MCR  = 11u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_Drv_LpitSetModEnblStat_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_Drv_LpitSetModEnblStat_Param1.MCR = 10u;
  Lpit_Drv_LpitSetModEnblStat_Param2     = 1u;

  //Step 3) Call FUT

  Lpit_Drv_LpitSetModEnblStat(&Lpit_Drv_LpitSetModEnblStat_Param1, Lpit_Drv_LpitSetModEnblStat_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(Lpit_Drv_LpitSetModEnblStat_Param1.MCR, 11u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_Drv_LpitSetModEnblStat_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function sets the doze mode
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_Drv_LpitSetModEnblStat_Param1.MCR   = 10u
/// \input Lpit_Drv_LpitSetModEnblStat_Param2       = 15u
///
/// - Expectations:
///
/// \output Lpit_Drv_LpitSetModEnblStat_Param1.MCR  = 10u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_Drv_LpitSetModEnblStat_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_Drv_LpitSetModEnblStat_Param1.MCR = 10u;
  Lpit_Drv_LpitSetModEnblStat_Param2     = 15u;

  //Step 3) Call FUT

  Lpit_Drv_LpitSetModEnblStat(&Lpit_Drv_LpitSetModEnblStat_Param1, Lpit_Drv_LpitSetModEnblStat_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(Lpit_Drv_LpitSetModEnblStat_Param1.MCR, 10u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_Drv_LpitSetTmrEnblBit_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function enable the timer 
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_Drv_LpitSetTmrEnblBit_Param1.ucLpitInst   = 1u
/// \input Lpit_Drv_LpitSetTmrEnblBit_Param1.ucChnNr      = 3u
/// \input Lpit_Drv_LpitSetTmrEnblBit_Param2              = 15u
/// \input LPIT0->TMR[3].TCTRL                            = 10u
///
/// - Expectations:
///
/// \output LPIT0->TMR[3].TCTRL                           = 10u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_Drv_LpitSetTmrEnblBit_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_Drv_LpitSetTmrEnblBit_Param1.ucLpitInst = 1u;
  Lpit_Drv_LpitSetTmrEnblBit_Param2            = 15u;
  Lpit_Drv_LpitSetTmrEnblBit_Param1.ucChnNr    = 3u;
  LPIT0->TMR[3].TCTRL                          = 10u;

  //Step 3) Call FUT

  Lpit_Drv_LpitSetTmrEnblBit(&Lpit_Drv_LpitSetTmrEnblBit_Param1, Lpit_Drv_LpitSetTmrEnblBit_Param2);

  //Step 4) Check expected output values

 AL_UNITTEST_CHECK(LPIT0->TMR[3].TCTRL, 10u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_Drv_LpitSetTmrEnblBit_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function enable the timer 
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_Drv_LpitSetTmrEnblBit_Param1.ucLpitInst   = 0u
/// \input Lpit_Drv_LpitSetTmrEnblBit_Param1.ucChnNr      = 5u
/// \input Lpit_Drv_LpitSetTmrEnblBit_Param2              = 1u
/// \input LPIT0->TMR[5].TCTRL                            = 20u
///
/// - Expectations:
///
/// \output LLPIT0->TMR[5].TCTRL                          = 21u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_Drv_LpitSetTmrEnblBit_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_Drv_LpitSetTmrEnblBit_Param1.ucLpitInst = 0u;
  Lpit_Drv_LpitSetTmrEnblBit_Param2 = 1u;
  Lpit_Drv_LpitSetTmrEnblBit_Param1.ucChnNr = 5u;
  LPIT0->TMR[5].TCTRL = 20u;

  //Step 3) Call FUT

  Lpit_Drv_LpitSetTmrEnblBit(&Lpit_Drv_LpitSetTmrEnblBit_Param1, Lpit_Drv_LpitSetTmrEnblBit_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LPIT0->TMR[5].TCTRL, 21u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_Drv_LpitReturnCount_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function returns the timer value
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_Drv_LpitReturnCount_Param1.ucLpitInst   = 0u
/// \input Lpit_Drv_LpitReturnCount_Param1.ucChnNr      = 2u
/// \input LPIT0->TMR[2].CVAL                           = 22u
///
/// - Expectations:
///
/// \output LPIT0->TMR[2].CVAL                          = 22u
/// \output Lpit_Drv_LpitReturnCount_RetVal             = 22u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_Drv_LpitReturnCount_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_Drv_LpitReturnCount_Param1.ucChnNr = 2u;
  Lpit_Drv_LpitReturnCount_Param1.ucLpitInst = 0u;
  LPIT0->TMR[2].CVAL = 22u;

  //Step 3) Call FUT

  Lpit_Drv_LpitReturnCount_RetVal = Lpit_Drv_LpitReturnCount(&Lpit_Drv_LpitReturnCount_Param1);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LPIT0->TMR[2].CVAL,              22u, == );
  AL_UNITTEST_CHECK(Lpit_Drv_LpitReturnCount_RetVal, 22u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_Drv_LpitReturnCount_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function returns the timer value
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_Drv_LpitReturnCount_Param1.ucLpitInst   = 2u
/// \input Lpit_Drv_LpitReturnCount_Param1.ucChnNr      = 3u
/// \input LPIT0->TMR[2].CVAL                           = 21u
///
/// - Expectations:
///
/// \output LPIT0->TMR[2].CVAL                          = 21u
/// \output Lpit_Drv_LpitReturnCount_RetVal             = 0u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_Drv_LpitReturnCount_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_Drv_LpitReturnCount_Param1.ucChnNr    = 2u;
  Lpit_Drv_LpitReturnCount_Param1.ucLpitInst = 3u;
  LPIT0->TMR[2].CVAL                         = 21u;

  //Step 3) Call FUT

  Lpit_Drv_LpitReturnCount_RetVal = Lpit_Drv_LpitReturnCount(&Lpit_Drv_LpitReturnCount_Param1);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LPIT0->TMR[2].CVAL,             21u, == );
  AL_UNITTEST_CHECK(Lpit_Drv_LpitReturnCount_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_Drv_ClearInterruptFlag_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function clears the interrupt clear flag
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_Drv_ClearInterruptFlag_Param1   = 0u
/// \input Lpit_Drv_ClearInterruptFlag_Param2   = 5u
///
/// - Expectations:
///
/// \output LPIT0->MSR.MSR                      = 32u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_Drv_ClearInterruptFlag_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_Drv_ClearInterruptFlag_Param1 = 0u;
  Lpit_Drv_ClearInterruptFlag_Param2 = 5u;

  //Step 3) Call FUT

  Lpit_Drv_ClearInterruptFlag(Lpit_Drv_ClearInterruptFlag_Param1, Lpit_Drv_ClearInterruptFlag_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LPIT0->MSR, 32u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_Drv_ClearInterruptFlag_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function clears the interrupt clear flag
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_Drv_ClearInterruptFlag_Param1   = 5u
/// \input Lpit_Drv_ClearInterruptFlag_Param2   = 5u
/// \input LPIT0->MSR                           = 5u
/// \input LPIT0_BASE->VERID                    = 1u
///
/// - Expectations:
///
/// \output LPIT0->MSR                          = 32u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_Drv_ClearInterruptFlag_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_Drv_ClearInterruptFlag_Param1 = 5u;
  Lpit_Drv_ClearInterruptFlag_Param2 = 5u;
  LPIT0->MSR = 5u;
  LPIT0_BASE->VERID = 1u;

  //Step 3) Call FUT

  Lpit_Drv_ClearInterruptFlag(Lpit_Drv_ClearInterruptFlag_Param1, Lpit_Drv_ClearInterruptFlag_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LPIT0->MSR, 5u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_Drv_ClearInterruptFlag_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function checks the timer channel enable procedure
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_Drv_TimerChannelEnable_Param1   = 0u
/// \input Lpit_Drv_TimerChannelEnable_Param2   = 10u
/// \input LPIT0->SETTEN                        = 5u
///
/// - Expectations:
///
/// \output LPIT0->SETTEN                       = 1029u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_Drv_TimerChannelEnable_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_Drv_TimerChannelEnable_Param1 = 0u;
  Lpit_Drv_TimerChannelEnable_Param2 = 10u;
  LPIT0->SETTEN = 5u;

  //Step 3) Call FUT

  Lpit_Drv_TimerChannelEnable(Lpit_Drv_TimerChannelEnable_Param1, Lpit_Drv_TimerChannelEnable_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LPIT0->SETTEN, 1029u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_Drv_TimerChannelEnable_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function checks the timer channel enable procedure
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_Drv_TimerChannelEnable_Param1   = 1u
/// \input Lpit_Drv_TimerChannelEnable_Param2   = 0u
/// \input LPIT0->SETTEN                        = 5u
///
/// - Expectations:
///
/// \output LPIT0->SETTEN                       = 5u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_Drv_TimerChannelEnable_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_Drv_TimerChannelEnable_Param1 = 1u;
  Lpit_Drv_TimerChannelEnable_Param2 = 0u;
  LPIT0->SETTEN = 5u;

  //Step 3) Call FUT

  Lpit_Drv_TimerChannelEnable(Lpit_Drv_TimerChannelEnable_Param1, Lpit_Drv_TimerChannelEnable_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LPIT0->SETTEN, 5u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_Drv_LpitSetTmrChCompVal_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function updates the timer compare value
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_Drv_LpitSetTmrChCompVal_Param1.ucLpitInst   = 1u
/// \input Lpit_Drv_LpitSetTmrChCompVal_Param1.ucChnNr      = 1u
/// \input Lpit_Drv_LpitSetTmrChCompVal_Param2              = 0u
///
/// - Expectations:
///
/// \output LPIT0->TMR[1].TVAL                              = 0u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_Drv_LpitSetTmrChCompVal_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_Drv_LpitSetTmrChCompVal_Param1.ucLpitInst = 1u;
  Lpit_Drv_LpitSetTmrChCompVal_Param1.ucChnNr = 1u;
  Lpit_Drv_LpitSetTmrChCompVal_Param2 = 0u;

  //Step 3) Call FUT

  Lpit_Drv_LpitSetTmrChCompVal(&Lpit_Drv_LpitSetTmrChCompVal_Param1, Lpit_Drv_LpitSetTmrChCompVal_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LPIT0->TMR[1].TVAL, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_Drv_LpitSetTmrChCompVal_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function updates the timer compare value
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_Drv_LpitSetTmrChCompVal_Param1.ucLpitInst   = 0u
/// \input Lpit_Drv_LpitSetTmrChCompVal_Param1.ucChnNr      = 1u
/// \input Lpit_Drv_LpitSetTmrChCompVal_Param2              = 0u
///
/// - Expectations:
///
/// \output LPIT0->TMR[1].TVAL                              = 0u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_Drv_LpitSetTmrChCompVal_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_Drv_LpitSetTmrChCompVal_Param1.ucLpitInst = 0u;
  Lpit_Drv_LpitSetTmrChCompVal_Param1.ucChnNr = 1u;
  Lpit_Drv_LpitSetTmrChCompVal_Param2 = 0u;
 
  //Step 3) Call FUT

  Lpit_Drv_LpitSetTmrChCompVal(&Lpit_Drv_LpitSetTmrChCompVal_Param1, Lpit_Drv_LpitSetTmrChCompVal_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LPIT0->TMR[1].TVAL, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_Drv_LpitClearTimeout_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function clears time-out flag in MSR register procedure
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_Drv_LpitClearTimeout_Param1.ucLpitInst      = 0u
/// \input Lpit_Drv_LpitClearTimeout_Param1.ucChnNr         = 1u
/// \input LPIT0->MSR                                       = 5u
///
/// - Expectations:
///
/// \output LPIT0->MSR                                      = 5u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_Drv_LpitClearTimeout_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_Drv_LpitClearTimeout_Param1.ucLpitInst = 0u;
  Lpit_Drv_LpitClearTimeout_Param1.ucChnNr = 1u;
  LPIT0->MSR = 5u;

  //Step 3) Call FUT

  Lpit_Drv_LpitClearTimeout(&Lpit_Drv_LpitClearTimeout_Param1);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LPIT0->MSR, 5u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_Drv_LpitClearTimeout_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function clears time-out flag in MSR register procedure
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_Drv_LpitClearTimeout_Param1.ucLpitInst      = 1u
/// \input Lpit_Drv_LpitClearTimeout_Param1.ucChnNr         = 1u
/// \input LPIT0->MSR                                       = 5u
///
/// - Expectations:
///
/// \output LPIT0->MSR                                      = 5u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_Drv_LpitClearTimeout_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_Drv_LpitClearTimeout_Param1.ucLpitInst = 1u;
  Lpit_Drv_LpitClearTimeout_Param1.ucChnNr    = 1u;
  LPIT0->MSR                                  = 5u;

  //Step 3) Call FUT

  Lpit_Drv_LpitClearTimeout(&Lpit_Drv_LpitClearTimeout_Param1);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LPIT0->MSR, 5u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_Drv_LpitSetTmrChIntEnbl_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function checks the interrupt enable procedure
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_Drv_LpitSetTmrChIntEnbl_Param1.ucLpitInst   = 0u
/// \input Lpit_Drv_LpitSetTmrChIntEnbl_Param1.ucChnNr      = 0u
/// \input Lpit_Drv_LpitSetTmrChIntEnbl_Param2              = 1u
///
/// - Expectations:
///
/// \output LPIT0->MIER                                     = 1u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_Drv_LpitSetTmrChIntEnbl_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_Drv_LpitSetTmrChIntEnbl_Param1.ucLpitInst = 0u;
  Lpit_Drv_LpitSetTmrChIntEnbl_Param1.ucChnNr = 0u;
  Lpit_Drv_LpitSetTmrChIntEnbl_Param2 = 1u;


  //Step 3) Call FUT

  Lpit_Drv_LpitSetTmrChIntEnbl(&Lpit_Drv_LpitSetTmrChIntEnbl_Param1, Lpit_Drv_LpitSetTmrChIntEnbl_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LPIT0->MIER, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_Drv_LpitSetTmrChIntEnbl_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function checks the interrupt enable procedure
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_Drv_LpitSetTmrChIntEnbl_Param1.ucLpitInst   = 0u
/// \input Lpit_Drv_LpitSetTmrChIntEnbl_Param1.ucChnNr      = 1u
/// \input Lpit_Drv_LpitSetTmrChIntEnbl_Param2              = 1u
///
/// - Expectations:
///
/// \output LPIT0->MIER                                     = 3u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_Drv_LpitSetTmrChIntEnbl_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_Drv_LpitSetTmrChIntEnbl_Param1.ucLpitInst = 0u;
  Lpit_Drv_LpitSetTmrChIntEnbl_Param1.ucChnNr = 1u;
  Lpit_Drv_LpitSetTmrChIntEnbl_Param2 = 1u;


  //Step 3) Call FUT

  Lpit_Drv_LpitSetTmrChIntEnbl(&Lpit_Drv_LpitSetTmrChIntEnbl_Param1, Lpit_Drv_LpitSetTmrChIntEnbl_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LPIT0->MIER, 3u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_Drv_LpitSetTmrChIntEnbl_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function checks the interrupt enable procedure
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_Drv_LpitSetTmrChIntEnbl_Param1.ucLpitInst   = 0u
/// \input Lpit_Drv_LpitSetTmrChIntEnbl_Param1.ucChnNr      = 2u
/// \input Lpit_Drv_LpitSetTmrChIntEnbl_Param2              = 1u
///
/// - Expectations:
///
/// \output LPIT0->MIER                                     = 7u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_Drv_LpitSetTmrChIntEnbl_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_Drv_LpitSetTmrChIntEnbl_Param1.ucLpitInst = 0u;
  Lpit_Drv_LpitSetTmrChIntEnbl_Param1.ucChnNr = 2u;
  Lpit_Drv_LpitSetTmrChIntEnbl_Param2 = 1u;


  //Step 3) Call FUT

  Lpit_Drv_LpitSetTmrChIntEnbl(&Lpit_Drv_LpitSetTmrChIntEnbl_Param1, Lpit_Drv_LpitSetTmrChIntEnbl_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LPIT0->MIER, 7u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_Drv_LpitSetTmrChIntEnbl_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function checks the interrupt enable procedure
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_Drv_LpitSetTmrChIntEnbl_Param1.ucLpitInst   = 0u
/// \input Lpit_Drv_LpitSetTmrChIntEnbl_Param1.ucChnNr      = 3u
/// \input Lpit_Drv_LpitSetTmrChIntEnbl_Param2              = 1u
///
/// - Expectations:
///
/// \output LPIT0->MIER                                     = 15u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_Drv_LpitSetTmrChIntEnbl_TestCase_4(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_Drv_LpitSetTmrChIntEnbl_Param1.ucLpitInst = 0u;
  Lpit_Drv_LpitSetTmrChIntEnbl_Param1.ucChnNr = 3u;
  Lpit_Drv_LpitSetTmrChIntEnbl_Param2 = 1u;


  //Step 3) Call FUT

  Lpit_Drv_LpitSetTmrChIntEnbl(&Lpit_Drv_LpitSetTmrChIntEnbl_Param1, Lpit_Drv_LpitSetTmrChIntEnbl_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LPIT0->MIER, 15u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_Drv_LpitSetTmrChIntEnbl_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function checks the interrupt enable procedure
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_Drv_LpitSetTmrChIntEnbl_Param1.ucLpitInst   = 0u
/// \input Lpit_Drv_LpitSetTmrChIntEnbl_Param1.ucChnNr      = 7u
/// \input Lpit_Drv_LpitSetTmrChIntEnbl_Param2              = 1u
///
/// - Expectations:
///
/// \output LPIT0->MIER                                     = 15u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_Drv_LpitSetTmrChIntEnbl_TestCase_5(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_Drv_LpitSetTmrChIntEnbl_Param1.ucLpitInst = 0u;
  Lpit_Drv_LpitSetTmrChIntEnbl_Param1.ucChnNr = 7u;
  Lpit_Drv_LpitSetTmrChIntEnbl_Param2 = 1u;


  //Step 3) Call FUT

  Lpit_Drv_LpitSetTmrChIntEnbl(&Lpit_Drv_LpitSetTmrChIntEnbl_Param1, Lpit_Drv_LpitSetTmrChIntEnbl_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LPIT0->MIER, 15u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_Drv_LpitSetTmrChIntEnbl_TestCase_6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function checks the interrupt enable procedure
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_Drv_LpitSetTmrChIntEnbl_Param1.ucLpitInst   = 1u
/// \input Lpit_Drv_LpitSetTmrChIntEnbl_Param1.ucChnNr      = 1u
/// \input Lpit_Drv_LpitSetTmrChIntEnbl_Param2              = 1u
///
/// - Expectations:
///
/// \output LPIT0->MIER                                     = 15u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_Drv_LpitSetTmrChIntEnbl_TestCase_6(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_Drv_LpitSetTmrChIntEnbl_Param1.ucLpitInst = 1u;
  Lpit_Drv_LpitSetTmrChIntEnbl_Param1.ucChnNr = 1u;
  Lpit_Drv_LpitSetTmrChIntEnbl_Param2 = 1u;

  //Step 3) Call FUT

  Lpit_Drv_LpitSetTmrChIntEnbl(&Lpit_Drv_LpitSetTmrChIntEnbl_Param1, Lpit_Drv_LpitSetTmrChIntEnbl_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LPIT0->MIER, 15u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_Drv_LpitSetTmrChChain_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function enables timer chain procedure
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_Drv_LpitSetTmrChChain_Param1.ucLpitInst   = 0u
/// \input Lpit_Drv_LpitSetTmrChChain_Param1.ucChnNr      = 1u
/// \input Lpit_Drv_LpitSetTmrChChain_Param2              = 1u
/// \input LPIT0->TMR[1].TCTRL                            = 0u
///
/// - Expectations:
///
/// \output LPIT0->TMR[1].TCTRL                            = 2u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_Drv_LpitSetTmrChChain_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_Drv_LpitSetTmrChChain_Param1.ucLpitInst = 0u;
  Lpit_Drv_LpitSetTmrChChain_Param1.ucChnNr = 1u;
  Lpit_Drv_LpitSetTmrChChain_Param2 = 1u;
  LPIT0->TMR[1].TCTRL = 0u;

  //Step 3) Call FUT

  Lpit_Drv_LpitSetTmrChChain(&Lpit_Drv_LpitSetTmrChChain_Param1, Lpit_Drv_LpitSetTmrChChain_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LPIT0->TMR[1].TCTRL, 2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_Drv_LpitSetTmrChChain_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function enables timer chain procedure
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_Drv_LpitSetTmrChChain_Param1.ucLpitInst   = 5u
/// \input Lpit_Drv_LpitSetTmrChChain_Param1.ucChnNr      = 1u
/// \input Lpit_Drv_LpitSetTmrChChain_Param2              = 1u
/// \input LPIT0->TMR[1].TCTRL                            = 0u
///
/// - Expectations:
///
/// \output LPIT0->TMR[1].TCTRL                            = 0u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_Drv_LpitSetTmrChChain_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_Drv_LpitSetTmrChChain_Param1.ucLpitInst = 5u;
  Lpit_Drv_LpitSetTmrChChain_Param1.ucChnNr = 1u;
  Lpit_Drv_LpitSetTmrChChain_Param2 = 1u;
  LPIT0->TMR[1].TCTRL = 0u;

  //Step 3) Call FUT

  Lpit_Drv_LpitSetTmrChChain(&Lpit_Drv_LpitSetTmrChChain_Param1, Lpit_Drv_LpitSetTmrChChain_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LPIT0->TMR[1].TCTRL, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_Drv_LpitSetTmrChSoT_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function enables timer chain procedure
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_Drv_LpitSetTmrChSoT_Param1.ucLpitInst   = 0u
/// \input Lpit_Drv_LpitSetTmrChSoT_Param1.ucChnNr      = 1u
/// \input Lpit_Drv_LpitSetTmrChSoT_Param2              = 1564u
/// \input LPIT0->TMR[1].TCTRL                          = 15u
///
/// - Expectations:
///
/// \output LPIT0->TMR[1].TCTRL                          = 15u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_Drv_LpitSetTmrChSoT_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_Drv_LpitSetTmrChSoT_Param1.ucLpitInst = 0u;
  Lpit_Drv_LpitSetTmrChSoT_Param1.ucChnNr = 1u;
  Lpit_Drv_LpitSetTmrChSoT_Param2 = 1564u;
  LPIT0->TMR[1].TCTRL = 15u;

  //Step 3) Call FUT

  Lpit_Drv_LpitSetTmrChSoT(&Lpit_Drv_LpitSetTmrChSoT_Param1, Lpit_Drv_LpitSetTmrChSoT_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LPIT0->TMR[1].TCTRL, 15u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_Drv_LpitSetTmrChSoT_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function enables timer chain procedure
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_Drv_LpitSetTmrChSoT_Param1.ucLpitInst   = 5u
/// \input Lpit_Drv_LpitSetTmrChSoT_Param1.ucChnNr      = 1u
/// \input Lpit_Drv_LpitSetTmrChSoT_Param2              = 1564u
/// \input LPIT0->TMR[1].TCTRL                          = 0u
///
/// - Expectations:
///
/// \output LPIT0->TMR[1].TCTRL                          = 0u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_Drv_LpitSetTmrChSoT_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_Drv_LpitSetTmrChSoT_Param1.ucLpitInst = 5u;
  Lpit_Drv_LpitSetTmrChSoT_Param1.ucChnNr = 1u;
  Lpit_Drv_LpitSetTmrChSoT_Param2 = 1564u;
  LPIT0->TMR[1].TCTRL = 0u;

  //Step 3) Call FUT

  Lpit_Drv_LpitSetTmrChSoT(&Lpit_Drv_LpitSetTmrChSoT_Param1, Lpit_Drv_LpitSetTmrChSoT_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LPIT0->TMR[1].TCTRL, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_Drv_LpitSetTmrChSoI_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function starts on interrupt configure procedure
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_Drv_LpitSetTmrChSoI_Param1.ucLpitInst   = 0u
/// \input Lpit_Drv_LpitSetTmrChSoI_Param1.ucChnNr      = 1u
/// \input Lpit_Drv_LpitSetTmrChSoI_Param2              = 1564u
/// \input LPIT0->TMR[1].TCTRL                          = 20u
///
/// - Expectations:
///
/// \output LPIT0->TMR[1].TCTRL                          = 20u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_Drv_LpitSetTmrChSoI_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_Drv_LpitSetTmrChSoI_Param1.ucLpitInst = 0u;
  Lpit_Drv_LpitSetTmrChSoI_Param1.ucChnNr = 1u;
  Lpit_Drv_LpitSetTmrChSoI_Param2 = 1564u;
  LPIT0->TMR[1].TCTRL = 20u;

  //Step 3) Call FUT

  Lpit_Drv_LpitSetTmrChSoI(&Lpit_Drv_LpitSetTmrChSoI_Param1, Lpit_Drv_LpitSetTmrChSoI_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LPIT0->TMR[1].TCTRL, 20u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_Drv_LpitSetTmrChSoI_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function starts on interrupt configure procedure
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_Drv_LpitSetTmrChSoI_Param1.ucLpitInst   = 5u
/// \input Lpit_Drv_LpitSetTmrChSoI_Param1.ucChnNr      = 1u
/// \input Lpit_Drv_LpitSetTmrChSoI_Param2              = 1u
/// \input LPIT0->TMR[1].TCTRL                          = 0u
///
/// - Expectations:
///
/// \output LPIT0->TMR[1].TCTRL                          = 0u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_Drv_LpitSetTmrChSoI_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_Drv_LpitSetTmrChSoI_Param1.ucLpitInst = 5u;
  Lpit_Drv_LpitSetTmrChSoI_Param1.ucChnNr = 1u;
  Lpit_Drv_LpitSetTmrChSoI_Param2 = 1u;
  LPIT0->TMR[1].TCTRL = 0u;

  //Step 3) Call FUT

  Lpit_Drv_LpitSetTmrChSoI(&Lpit_Drv_LpitSetTmrChSoI_Param1, Lpit_Drv_LpitSetTmrChSoI_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LPIT0->TMR[1].TCTRL, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_Drv_LpitSetTmrChRoT_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function starts on interrupt configure procedure
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_Drv_LpitSetTmrChRoT_Param1.ucLpitInst   = 5u
/// \input Lpit_Drv_LpitSetTmrChRoT_Param1.ucChnNr      = 1u
/// \input Lpit_Drv_LpitSetTmrChRoT_Param2              = 1564u
/// \input LPIT0->TMR[1].TCTRL                          = 55u
///
/// - Expectations:
///
/// \output LPIT0->TMR[1].TCTRL                         = 55u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_Drv_LpitSetTmrChRoT_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_Drv_LpitSetTmrChRoT_Param1.ucLpitInst = 0u;
  Lpit_Drv_LpitSetTmrChRoT_Param1.ucChnNr = 1u;
  Lpit_Drv_LpitSetTmrChRoT_Param2 = 1564u;
  LPIT0->TMR[1].TCTRL = 55u;

  //Step 3) Call FUT

  Lpit_Drv_LpitSetTmrChRoT(&Lpit_Drv_LpitSetTmrChRoT_Param1, Lpit_Drv_LpitSetTmrChRoT_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LPIT0->TMR[1].TCTRL, 55u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_Drv_LpitSetTmrChRoT_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function starts on interrupt configure procedure
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_Drv_LpitSetTmrChRoT_Param1.ucLpitInst   = 5u
/// \input Lpit_Drv_LpitSetTmrChRoT_Param1.ucChnNr      = 1u
/// \input Lpit_Drv_LpitSetTmrChRoT_Param2              = 1u
/// \input LPIT0->TMR[1].TCTRL                          = 0u
///
/// - Expectations:
///
/// \output LPIT0->TMR[1].TCTRL                         = 0u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_Drv_LpitSetTmrChRoT_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_Drv_LpitSetTmrChRoT_Param1.ucLpitInst = 5u;
  Lpit_Drv_LpitSetTmrChRoT_Param1.ucChnNr = 1u;
  Lpit_Drv_LpitSetTmrChRoT_Param2 = 1u;
  LPIT0->TMR[1].TCTRL = 0u;

  //Step 3) Call FUT

  Lpit_Drv_LpitSetTmrChRoT(&Lpit_Drv_LpitSetTmrChRoT_Param1, Lpit_Drv_LpitSetTmrChRoT_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LPIT0->TMR[1].TCTRL, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_Drv_LpitSetTmrChTrigSel_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function triggers the channel seelction
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_Drv_LpitSetTmrChTrigSel_Param1.ucLpitInst   = 0u
/// \input Lpit_Drv_LpitSetTmrChTrigSel_Param1.ucChnNr      = 1u
/// \input Lpit_Drv_LpitSetTmrChTrigSel_Param2              = 1564u
/// \input LPIT0->TMR[1].TCTRL                              = 66u
///
/// - Expectations:
///
/// \output LPIT0->TMR[1].TCTRL                             = 66u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_Drv_LpitSetTmrChTrigSel_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_Drv_LpitSetTmrChTrigSel_Param1.ucLpitInst = 0u;
  Lpit_Drv_LpitSetTmrChTrigSel_Param1.ucChnNr = 1u;
  Lpit_Drv_LpitSetTmrChTrigSel_Param2 = 1564u;
  LPIT0->TMR[1].TCTRL = 66u;

  //Step 3) Call FUT

  Lpit_Drv_LpitSetTmrChTrigSel(&Lpit_Drv_LpitSetTmrChTrigSel_Param1, Lpit_Drv_LpitSetTmrChTrigSel_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LPIT0->TMR[1].TCTRL, 66u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_Drv_LpitSetTmrChTrigSel_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function triggers the channel seelction
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_Drv_LpitSetTmrChTrigSel_Param1.ucLpitInst   = 0u
/// \input Lpit_Drv_LpitSetTmrChTrigSel_Param1.ucChnNr      = 1u
/// \input Lpit_Drv_LpitSetTmrChTrigSel_Param2              = 1u
/// \input LPIT0->TMR[1].TCTRL                              = 0u
///
/// - Expectations:
///
/// \output LPIT0->TMR[1].TCTRL                             = 0u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_Drv_LpitSetTmrChTrigSel_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_Drv_LpitSetTmrChTrigSel_Param1.ucLpitInst = 5u;
  Lpit_Drv_LpitSetTmrChTrigSel_Param1.ucChnNr = 1u;
  Lpit_Drv_LpitSetTmrChTrigSel_Param2 = 1u;
  LPIT0->TMR[1].TCTRL = 0u;

  //Step 3) Call FUT

  Lpit_Drv_LpitSetTmrChTrigSel(&Lpit_Drv_LpitSetTmrChTrigSel_Param1, Lpit_Drv_LpitSetTmrChTrigSel_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LPIT0->TMR[1].TCTRL, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_Drv_LpitSetTmrChTrigSrc_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function triggers the source selector
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_Drv_LpitSetTmrChTrigSrc_Param1.ucLpitInst   = 0u
/// \input Lpit_Drv_LpitSetTmrChTrigSrc_Param1.ucChnNr      = 1u
/// \input Lpit_Drv_LpitSetTmrChTrigSrc_Param2              = 1564u
/// \input LPIT0->TMR[1].TCTRL                              = 55u
///
/// - Expectations:
///
/// \output LPIT0->TMR[1].TCTRL                             = 55u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_Drv_LpitSetTmrChTrigSrc_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_Drv_LpitSetTmrChTrigSrc_Param1.ucLpitInst = 0u;
  Lpit_Drv_LpitSetTmrChTrigSrc_Param1.ucChnNr = 1u;
  Lpit_Drv_LpitSetTmrChTrigSrc_Param2 = 1564u;
  LPIT0->TMR[1].TCTRL = 55u;

  //Step 3) Call FUT

  Lpit_Drv_LpitSetTmrChTrigSrc(&Lpit_Drv_LpitSetTmrChTrigSrc_Param1, Lpit_Drv_LpitSetTmrChTrigSrc_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LPIT0->TMR[1].TCTRL, 55u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_Drv_LpitSetTmrChTrigSrc_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function triggers the source selector
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_Drv_LpitSetTmrChTrigSrc_Param1.ucLpitInst   = 5u
/// \input Lpit_Drv_LpitSetTmrChTrigSrc_Param1.ucChnNr      = 1u
/// \input Lpit_Drv_LpitSetTmrChTrigSrc_Param2              = 1u
/// \input LPIT0->TMR[1].TCTRL                              = 0u
///
/// - Expectations:
///
/// \output LPIT0->TMR[1].TCTRL                             = 0u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_Drv_LpitSetTmrChTrigSrc_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_Drv_LpitSetTmrChTrigSrc_Param1.ucLpitInst = 5u;
  Lpit_Drv_LpitSetTmrChTrigSrc_Param1.ucChnNr = 1u;
  Lpit_Drv_LpitSetTmrChTrigSrc_Param2 = 1u;
  LPIT0->TMR[1].TCTRL = 0u;

  //Step 3) Call FUT

  Lpit_Drv_LpitSetTmrChTrigSrc(&Lpit_Drv_LpitSetTmrChTrigSrc_Param1, Lpit_Drv_LpitSetTmrChTrigSrc_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LPIT0->TMR[1].TCTRL, 0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_Drv_LpitSetTmrChTrigSrc_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function sets up the procedure
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_Drv_LpitSetTmrChMode_Param1.ucLpitInst   = 0u
/// \input Lpit_Drv_LpitSetTmrChMode_Param1.ucChnNr      = 1u
/// \input Lpit_Drv_LpitSetTmrChMode_Param2              = 1u
/// \input LPIT0->TMR[1].TCTRL                           = 0u
///
/// - Expectations:
///
/// \output LPIT0->TMR[1].TCTRL                          = 4u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_Drv_LpitSetTmrChMode_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_Drv_LpitSetTmrChMode_Param1.ucLpitInst = 0u;
  Lpit_Drv_LpitSetTmrChMode_Param1.ucChnNr = 1u;
  Lpit_Drv_LpitSetTmrChMode_Param2 = 1u;
  LPIT0->TMR[1].TCTRL = 0u;

  //Step 3) Call FUT

  Lpit_Drv_LpitSetTmrChMode(&Lpit_Drv_LpitSetTmrChMode_Param1, Lpit_Drv_LpitSetTmrChMode_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LPIT0->TMR[1].TCTRL, 4u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_Drv_LpitSetTmrChTrigSrc_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function sets up the procedure
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_Drv_LpitSetTmrChMode_Param1.ucLpitInst   = 5u
/// \input Lpit_Drv_LpitSetTmrChMode_Param1.ucChnNr      = 1u
/// \input Lpit_Drv_LpitSetTmrChMode_Param2              = 1u
/// \input LPIT0->TMR[1].TCTRL                           = 0u
///
/// - Expectations:
///
/// \output LPIT0->TMR[1].TCTRL                         = 00u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_Drv_LpitSetTmrChMode_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_Drv_LpitSetTmrChMode_Param1.ucLpitInst = 5u;
  Lpit_Drv_LpitSetTmrChMode_Param1.ucChnNr = 1u;
  Lpit_Drv_LpitSetTmrChMode_Param2 = 1u;
  LPIT0->TMR[1].TCTRL = 0u;

  //Step 3) Call FUT

  Lpit_Drv_LpitSetTmrChMode(&Lpit_Drv_LpitSetTmrChMode_Param1, Lpit_Drv_LpitSetTmrChMode_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LPIT0->TMR[1].TCTRL, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_InitLpitInstance_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function inits the procedure
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Lpit_InitLpitInstance_Param1                   = LPIT0_BASE
/// \input  Lpit_InitLpitInstance_Param1->ucLpitInst       = 0u
/// \input  Lpit_InitLpitInstance_Param1->boEnableDebug    = FALSE
/// \input  Lpit_InitLpitInstance_Param1->boEnableDoze     = FALSE
/// \input  Lpit_InitLpitInstance_Param1->boEnableModule   = FALSE
/// \input  Lpit_Drv_LpitSetDebugMode_Param1.MCR           = 10u
/// \input  Lpit_Drv_LpitSetDebugMode_Param2               = 0u
///
/// - Expectations:
///
/// /// \output Lpit_Drv_LpitSetDebugMode_Param1.MCR   = 10u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_InitLpitInstance_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_InitLpitInstance_Param1                 = LPIT0_BASE;
  Lpit_InitLpitInstance_Param1->ucLpitInst     = 0u;
  Lpit_InitLpitInstance_Param1->boEnableDebug  = FALSE;
  Lpit_InitLpitInstance_Param1->boEnableDoze   = FALSE;
  Lpit_InitLpitInstance_Param1->boEnableModule = FALSE;
  Lpit_Drv_LpitSetDebugMode_Param1.MCR         = 10u;
  Lpit_Drv_LpitSetDebugMode_Param2             = 0u;

  //Step 3) Call FUT

  Lpit_InitLpitInstance(Lpit_InitLpitInstance_Param1);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(Lpit_Drv_LpitSetDebugMode_Param1.MCR, 10u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_InitLpitInstance_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function inits the procedure
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Lpit_InitLpitInstance_Param1                 = LPIT0_BASE
/// \input  Lpit_InitLpitInstance_Param1->ucLpitInst     = 15u
/// \input  Lpit_InitLpitInstance_Param1->boEnableDebug  = TRUE
/// \input  Lpit_InitLpitInstance_Param1->boEnableDoze   = TRUE
/// \input  Lpit_InitLpitInstance_Param1->boEnableModule = TRUE
/// \input  Lpit_Drv_LpitSetDebugMode_Param1.MCR         = 10u
/// \input  Lpit_Drv_LpitSetDebugMode_Param2             = 0u
///
/// - Expectations:
///
/// \output Lpit_Drv_LpitSetDebugMode_Param1.MCR        = 10u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_InitLpitInstance_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Lpit_InitLpitInstance_Param1                 = LPIT0_BASE;
  Lpit_InitLpitInstance_Param1->ucLpitInst     = 0u;
  Lpit_InitLpitInstance_Param1->boEnableDebug  = TRUE;
  Lpit_InitLpitInstance_Param1->boEnableDoze   = TRUE;
  Lpit_InitLpitInstance_Param1->boEnableModule = TRUE;
  Lpit_Drv_LpitSetDebugMode_Param1.MCR         = 10u;
  Lpit_Drv_LpitSetDebugMode_Param2             = 0u;
  
  //Step 3) Call FUT

  Lpit_InitLpitInstance(Lpit_InitLpitInstance_Param1);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(Lpit_Drv_LpitSetDebugMode_Param1.MCR, 10u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_InitLpitInstance_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function inits the procedure
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_InitLpitInstance_Param1.ucLpitInst   = 5u
///
/// - Expectations:
///
/// \output Lpit_Drv_LpitSetDebugMode_Param1.MCR     = 10u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_InitLpitInstance_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_InitLpitInstance_Param1->ucLpitInst = 5u;

  //Step 3) Call FUT-

  Lpit_InitLpitInstance(Lpit_InitLpitInstance_Param1);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(Lpit_Drv_LpitSetDebugMode_Param1.MCR, 10u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_InitLpitTmrChn_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function inits the timer channel
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_InitLpitTmrChn_Param1.ucLpitInst           = 1u
/// \input Lpit_Drv_LpitSetTmrChCompVal_Param1.ucLpitInst  = 1u
/// \input Lpit_Drv_LpitSetTmrChCompVal_Param1.ucChnNr     = 1u
/// \input Lpit_Drv_LpitSetTmrChCompVal_Param2             = 0u
///
/// - Expectations:
///
/// \output LPIT0->TMR[1].TVAL                             = 0u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_InitLpitTmrChn_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_InitLpitTmrChn_Param1.ucLpitInst = 1u;
  Lpit_Drv_LpitSetTmrChCompVal_Param1.ucLpitInst = 1u;
  Lpit_Drv_LpitSetTmrChCompVal_Param1.ucChnNr = 1u;
  Lpit_Drv_LpitSetTmrChCompVal_Param2 = 0u;

  //Step 3) Call FUT

  Lpit_InitLpitTmrChn(&Lpit_InitLpitTmrChn_Param1);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LPIT0->TMR[1].TVAL, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_InitLpitTmrChn_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function inits the timer channel
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_InitLpitTmrChn_Param1.ucLpitInst          = 1u
/// \input Lpit_InitLpitTmrChn_Param1.boReloadOnTrigger   = TRUE
/// \input Lpit_InitLpitTmrChn_Param1.boStopOnInterrupt   = TRUE
/// \input Lpit_InitLpitTmrChn_Param1.boStartOnTrigger    = TRUE
/// \input Lpit_InitLpitTmrChn_Param1.boChainChannel      = TRUE
/// \input Lpit_InitLpitTmrChn_Param1.boIntEnbl           = TRUE
/// \input Lpit_Drv_LpitSetTmrChCompVal_Param1.ucLpitInst = 1u
/// \input Lpit_Drv_LpitSetTmrChCompVal_Param1.ucChnNr    = 1u
/// \input Lpit_Drv_LpitSetTmrChCompVal_Param2            = 0u
///
/// - Expectations:
///
/// \output LPIT0->TMR[1].TVAL                            = 0u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_InitLpitTmrChn_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_InitLpitTmrChn_Param1.ucLpitInst = 1u;
  Lpit_InitLpitTmrChn_Param1.boReloadOnTrigger = TRUE;
  Lpit_InitLpitTmrChn_Param1.boStopOnInterrupt = TRUE;
  Lpit_InitLpitTmrChn_Param1.boStartOnTrigger = TRUE;
  Lpit_InitLpitTmrChn_Param1.boChainChannel = TRUE;
  Lpit_InitLpitTmrChn_Param1.boIntEnbl = TRUE;
  Lpit_Drv_LpitSetTmrChCompVal_Param1.ucLpitInst = 1u;
  Lpit_Drv_LpitSetTmrChCompVal_Param1.ucChnNr = 1u;
  Lpit_Drv_LpitSetTmrChCompVal_Param2 = 0u;



  //Step 3) Call FUT

  Lpit_InitLpitTmrChn(&Lpit_InitLpitTmrChn_Param1);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LPIT0->TMR[1].TVAL, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_LpitSetTmrEnable_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function enables/disables timer instance procedure
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_LpitSetTmrEnable_Param1.ucLpitInst      = 1u
/// \input Lpit_LpitSetTmrEnable_Param2                 = FALSE
/// \input Lpit_Drv_LpitSetTmrEnblBit_Param1.ucLpitInst = 1u
/// \input Lpit_Drv_LpitSetTmrEnblBit_Param2            = 15u
/// \input Lpit_Drv_LpitSetTmrEnblBit_Param1.ucChnNr    = 3u
/// \input LPIT0->TMR[3].TCTRL                          = 10u
///
/// - Expectations:
///
/// \output LPIT0->TMR[3].TCTRL                        = 10u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_LpitSetTmrEnable_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_LpitSetTmrEnable_Param1.ucLpitInst = 1u;
  Lpit_LpitSetTmrEnable_Param2 = FALSE;
  Lpit_Drv_LpitSetTmrEnblBit_Param1.ucLpitInst = 1u;
  Lpit_Drv_LpitSetTmrEnblBit_Param2 = 15u;
  Lpit_Drv_LpitSetTmrEnblBit_Param1.ucChnNr = 3u;
  LPIT0->TMR[3].TCTRL = 10u;
 
  //Step 3) Call FUT

  Lpit_LpitSetTmrEnable(&Lpit_LpitSetTmrEnable_Param1, Lpit_LpitSetTmrEnable_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LPIT0->TMR[3].TCTRL, 10u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_Drv_Init_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function initializes the instances and channels
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input LPIT0_BASE->PARAM                                                   = 5u;
/// \input Lpit_Drv_Init_Param1                                                = LPIT0_BASE;
/// \input Lpit_Drv_Init_Param1->sLpitInstanceCfg.psLpitInstCfg                = LPIT0_BASE;
/// \input Lpit_Drv_Init_Param1->sLpitTmrCfg.sLpitTmrCfg                       = LPIT0_BASE;
/// \input Lpit_Drv_Init_Param1->sLpitInstanceCfg.psLpitInstCfg->boEnableDebug = 0u;
/// \input Lpit_Drv_Init_Param1->sLpitTmrCfg.sLpitTmrCfg->boChainChannel       = 0u; 
/// \input Lpit_Drv_Init_Param1->sLpitInstanceCfg.ucCfgLength                  = 15u;
/// \input Lpit_Drv_Init_Param1->sLpitTmrCfg.ucCfgLength                       = 15u;
/// \input Lpit_InitLpitInstance_Param1->ucLpitInst                            = 15u;
/// \input Lpit_LpitSetTmrEnblBit_Param1.ucLpitInst                            = 1u;
/// \input Lpit_LpitSetTmrEnblBit_Param1.ucChnNr                               = 3u;
/// \input Lpit_LpitSetTmrEnblBit_Param2                                       = 15u;
/// \input LPIT0->TMR[3].TCTRL                                                 = 10u;
/// \input Lpit_Drv_LpitSetDebugMode_Param1.MCR                                = 10u;
/// \input Lpit_Drv_LpitSetDebugMode_Param2                                    = 0u;
///
/// - Expectations
///
/// \output Lpit_Drv_Init_RetVal                                               = E_OK
/// \output Lpit_Drv_LpitSetDebugMode_Param1.MCR                               = 10u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_Drv_Init_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  LPIT0_BASE->PARAM = 5u;
  Lpit_Drv_Init_Param1 = LPIT0_BASE;
  Lpit_Drv_Init_Param1->sLpitInstanceCfg.psLpitInstCfg = LPIT0_BASE;
  Lpit_Drv_Init_Param1->sLpitTmrCfg.sLpitTmrCfg = LPIT0_BASE;
  Lpit_Drv_Init_Param1->sLpitInstanceCfg.psLpitInstCfg->boEnableDebug = 0u;
  Lpit_Drv_Init_Param1->sLpitTmrCfg.sLpitTmrCfg->boChainChannel = 0u; 
  Lpit_Drv_Init_Param1->sLpitInstanceCfg.ucCfgLength = 15u;
  Lpit_Drv_Init_Param1->sLpitTmrCfg.ucCfgLength = 15u;
  Lpit_InitLpitInstance_Param1->ucLpitInst = 15u;
  Lpit_LpitSetTmrEnblBit_Param1.ucLpitInst = 1u;
  Lpit_LpitSetTmrEnblBit_Param1.ucChnNr = 3u;
  Lpit_LpitSetTmrEnblBit_Param2 = 15u;
  LPIT0->TMR[3].TCTRL = 10u;
  Lpit_Drv_LpitSetDebugMode_Param1.MCR = 10u;
  Lpit_Drv_LpitSetDebugMode_Param2 = 0u;
  LPIT0->TMR[1].TCTRL = 5u;


  //Step 3) Call FUT

  Lpit_Drv_Init_RetVal = Lpit_Drv_Init(Lpit_Drv_Init_Param1);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(Lpit_Drv_Init_RetVal, E_OK, == );
  AL_UNITTEST_CHECK(Lpit_Drv_LpitSetDebugMode_Param1.MCR, 10u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_LpitSetTmrEnblBit_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the interface for Lpit_Drv_LpitSetTmrEnblBit works ok
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_LpitSetTmrEnblBit_Param1.ucLpitInst = 1u
/// \input Lpit_LpitSetTmrEnblBit_Param1.ucChnNr    = 3u
/// \input Lpit_LpitSetTmrEnblBit_Param2            = 15u
/// \input LPIT0->TMR[3].TCTRL                      = 10u
///
/// - Expectations:
///
/// \output LPIT0->TMR[3].TCTRL                     = 10u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_LpitSetTmrEnblBit_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_LpitSetTmrEnblBit_Param1.ucLpitInst = 1u;
  Lpit_LpitSetTmrEnblBit_Param1.ucChnNr = 3u;
  Lpit_LpitSetTmrEnblBit_Param2 = 15u;
  LPIT0->TMR[3].TCTRL = 10u;

  //Step 3) Call FUT

  Lpit_LpitSetTmrEnblBit(&Lpit_LpitSetTmrEnblBit_Param1, Lpit_LpitSetTmrEnblBit_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LPIT0->TMR[3].TCTRL, 10u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_LpitSetTmrChCompVal_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the interface for Lpit_Drv_LpitSetTmrChCompVal works ok
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_LpitSetTmrChCompVal_Param1.ucLpitInst = 1u;
/// \input Lpit_LpitSetTmrChCompVal_Param1.ucChnNr    = 1u;
/// \input Lpit_LpitSetTmrChCompVal_Param2            = 0u;
///
/// - Expectations:
///
/// \output LPIT0->TMR[1].TVAL                         = 0u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_LpitSetTmrChCompVal_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_LpitSetTmrChCompVal_Param1.ucLpitInst = 1u;
  Lpit_LpitSetTmrChCompVal_Param1.ucChnNr = 1u;
  Lpit_LpitSetTmrChCompVal_Param2 = 0u;


  //Step 3) Call FUT

  Lpit_LpitSetTmrChCompVal(&Lpit_LpitSetTmrEnblBit_Param1, Lpit_LpitSetTmrEnblBit_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LPIT0->TMR[1].TVAL, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_LpitSetTmrChIntEnbl_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the interface for Lpit_LpitSetTmrChIntEnbl works ok
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_LpitSetTmrChIntEnbl_Param1.ucLpitInst  = 0u;
/// \input Lpit_LpitSetTmrChIntEnbl_Param1.ucChnNr     = 0u;
/// \input Lpit_LpitSetTmrChIntEnbl_Param2             = 0u;
///
/// - Expectations:
///
/// \output LPIT0->MIER                                = 15u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_LpitSetTmrChIntEnbl_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_LpitSetTmrChIntEnbl_Param1.ucLpitInst = 0u;
  Lpit_LpitSetTmrChIntEnbl_Param1.ucChnNr    = 0u;
  Lpit_LpitSetTmrChIntEnbl_Param2 = 1u;

  //Step 3) Call FUT

  Lpit_LpitSetTmrChIntEnbl(&Lpit_LpitSetTmrChIntEnbl_Param1, Lpit_LpitSetTmrChIntEnbl_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LPIT0->MIER, 15u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_LpitReturnCount_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the interface for Lpit_LpitReturnCount works ok
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Lpit_LpitReturnCount_Param1.ucLpitInst   = 3u
/// \input  Lpit_LpitReturnCount_Param1.ucChnNr      = 2u
/// \input  LPIT0->TMR[2].CVAL                       = 21u
///
/// - Expectations:
///
/// \output LPIT0->TMR[2].CVAL                       = 21u
/// \output Lpit_LpitReturnCount_RetVal              = 0u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_LpitReturnCount_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_LpitReturnCount_Param1.ucLpitInst = 3u;
  Lpit_LpitReturnCount_Param1.ucChnNr = 2u;
  LPIT0->TMR[2].CVAL = 21u;

  //Step 3) Call FUT

  Lpit_LpitReturnCount_RetVal = Lpit_LpitReturnCount(&Lpit_LpitReturnCount_Param1);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LPIT0->TMR[2].CVAL,         21u, == );
  AL_UNITTEST_CHECK(Lpit_LpitReturnCount_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_LpitClearTimeout_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the interface for Lpit_LpitClearTimeout works ok
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_InitLpitTmrChn_Param1.ucLpitInst   = 0u
/// \input Lpit_InitLpitTmrChn_Param1.ucChnNr      = 1u
/// \input LPIT0->MSR                              = 5u
///
/// - Expectations:
///
/// \output LPIT0->MSR  = 5u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_LpitClearTimeout_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_LpitClearTimeout_Param1.ucLpitInst = 0u;
  Lpit_LpitClearTimeout_Param1.ucChnNr    = 1u;
  LPIT0->MSR = 5u;


  //Step 3) Call FUT

  Lpit_LpitClearTimeout(&Lpit_LpitClearTimeout_Param1);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LPIT0->MSR, 5u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_ClearInterruptFlag_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the interface for Lpit_TmrChannelEnable works ok
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_TmrChannelEnable_Param1   = 0u
/// \input Lpit_TmrChannelEnable_Param2   = 5u
/// \input LPIT0->MSR                     = 5u
///
/// - Expectations:
///
/// \output LPIT0->MSR                   = 32u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_ClearInterruptFlag_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_ClearInterruptFlag_Param1 = 0u;
  Lpit_ClearInterruptFlag_Param2 = 5u;
  LPIT0->MSR = 5u;


  //Step 3) Call FUT

  Lpit_ClearInterruptFlag(Lpit_ClearInterruptFlag_Param1, Lpit_ClearInterruptFlag_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LPIT0->MSR, 32u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Lpit_Lpit_TmrChannelEnable_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the interface for Lpit_TmrChannelEnable works ok
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Lpit_TmrChannelEnable_Param1   = 0u
/// \input Lpit_TmrChannelEnable_Param2   = 5u
/// \input LPIT0->MSR                     = 5u
///
/// - Expectations:
///
/// \output LPIT0->MSR                   = 5u
///
//-----------------------------------------------------------------------------
void Mt_Lpit_Lpit_TmrChannelEnable_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Lpit_TmrChannelEnable_Param1 = 0u;
  Lpit_TmrChannelEnable_Param2 = 5u;
  LPIT0->MSR = 5u;

  //Step 3) Call FUT

  Lpit_TmrChannelEnable(Lpit_TmrChannelEnable_Param1, Lpit_TmrChannelEnable_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LPIT0->MSR, 5u, == );
}

//-----------------------------------------------------------------------------
/// \brief  ALUnitTest_AddTests
///
/// \descr  Every test case shall be added to this list
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void ALUnitTest_AddTests(void)
{
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_Init_TestCase_1", Mt_Lpit_Lpit_Init_TestCase_1);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_Init_TestCase_2", Mt_Lpit_Lpit_Init_TestCase_2);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_Drv_LpitSetDebugMode_TestCase_1", Mt_Lpit_Lpit_Drv_LpitSetDebugMode_TestCase_1);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_Drv_LpitSetDebugMode_TestCase_2", Mt_Lpit_Lpit_Drv_LpitSetDebugMode_TestCase_2);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_Drv_LpitSetDozeMode_TestCase_1", Mt_Lpit_Lpit_Drv_LpitSetDozeMode_TestCase_1);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_Drv_LpitSetDozeMode_TestCase_2", Mt_Lpit_Lpit_Drv_LpitSetDozeMode_TestCase_2);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_Drv_LpitSetModEnblStat_TestCase_1", Mt_Lpit_Lpit_Drv_LpitSetModEnblStat_TestCase_1);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_Drv_LpitSetModEnblStat_TestCase_2", Mt_Lpit_Lpit_Drv_LpitSetModEnblStat_TestCase_2);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_Drv_LpitSetTmrEnblBit_TestCase_1", Mt_Lpit_Lpit_Drv_LpitSetTmrEnblBit_TestCase_1);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_Drv_LpitSetTmrEnblBit_TestCase_2", Mt_Lpit_Lpit_Drv_LpitSetTmrEnblBit_TestCase_2);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_Drv_LpitReturnCount_TestCase_1", Mt_Lpit_Lpit_Drv_LpitReturnCount_TestCase_1);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_Drv_LpitReturnCount_TestCase_2", Mt_Lpit_Lpit_Drv_LpitReturnCount_TestCase_2);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_Drv_ClearInterruptFlag_TestCase_1", Mt_Lpit_Lpit_Drv_ClearInterruptFlag_TestCase_1);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_Drv_ClearInterruptFlag_TestCase_2", Mt_Lpit_Lpit_Drv_ClearInterruptFlag_TestCase_2);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_Drv_TimerChannelEnable_TestCase_1", Mt_Lpit_Lpit_Drv_TimerChannelEnable_TestCase_1);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_Drv_TimerChannelEnable_TestCase_2", Mt_Lpit_Lpit_Drv_TimerChannelEnable_TestCase_2);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_Drv_LpitSetTmrChCompVal_TestCase_1", Mt_Lpit_Lpit_Drv_LpitSetTmrChCompVal_TestCase_1);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_Drv_LpitSetTmrChCompVal_TestCase_2", Mt_Lpit_Lpit_Drv_LpitSetTmrChCompVal_TestCase_2);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_Drv_LpitClearTimeout_TestCase_1", Mt_Lpit_Lpit_Drv_LpitClearTimeout_TestCase_1);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_Drv_LpitClearTimeout_TestCase_2", Mt_Lpit_Lpit_Drv_LpitClearTimeout_TestCase_2);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_Drv_LpitSetTmrChIntEnbl_TestCase_1", Mt_Lpit_Lpit_Drv_LpitSetTmrChIntEnbl_TestCase_1);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_Drv_LpitSetTmrChIntEnbl_TestCase_2", Mt_Lpit_Lpit_Drv_LpitSetTmrChIntEnbl_TestCase_2);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_Drv_LpitSetTmrChIntEnbl_TestCase_3", Mt_Lpit_Lpit_Drv_LpitSetTmrChIntEnbl_TestCase_3);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_Drv_LpitSetTmrChIntEnbl_TestCase_4", Mt_Lpit_Lpit_Drv_LpitSetTmrChIntEnbl_TestCase_4);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_Drv_LpitSetTmrChIntEnbl_TestCase_5", Mt_Lpit_Lpit_Drv_LpitSetTmrChIntEnbl_TestCase_5);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_Drv_LpitSetTmrChIntEnbl_TestCase_6", Mt_Lpit_Lpit_Drv_LpitSetTmrChIntEnbl_TestCase_6);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_Drv_LpitSetTmrChChain_TestCase_1", Mt_Lpit_Lpit_Drv_LpitSetTmrChChain_TestCase_1);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_Drv_LpitSetTmrChChain_TestCase_2", Mt_Lpit_Lpit_Drv_LpitSetTmrChChain_TestCase_2);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_Drv_LpitSetTmrChSoT_TestCase_1", Mt_Lpit_Lpit_Drv_LpitSetTmrChSoT_TestCase_1);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_Drv_LpitSetTmrChSoT_TestCase_2", Mt_Lpit_Lpit_Drv_LpitSetTmrChSoT_TestCase_2);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_Drv_LpitSetTmrChSoI_TestCase_1", Mt_Lpit_Lpit_Drv_LpitSetTmrChSoI_TestCase_1);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_Drv_LpitSetTmrChSoI_TestCase_2", Mt_Lpit_Lpit_Drv_LpitSetTmrChSoI_TestCase_2);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_Drv_LpitSetTmrChRoT_TestCase_1", Mt_Lpit_Lpit_Drv_LpitSetTmrChRoT_TestCase_1);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_Drv_LpitSetTmrChRoT_TestCase_2", Mt_Lpit_Lpit_Drv_LpitSetTmrChRoT_TestCase_2);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_Drv_LpitSetTmrChTrigSel_TestCase_1", Mt_Lpit_Lpit_Drv_LpitSetTmrChTrigSel_TestCase_1);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_Drv_LpitSetTmrChTrigSel_TestCase_2", Mt_Lpit_Lpit_Drv_LpitSetTmrChTrigSel_TestCase_2);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_Drv_LpitSetTmrChTrigSrc_TestCase_1", Mt_Lpit_Lpit_Drv_LpitSetTmrChTrigSrc_TestCase_1);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_Drv_LpitSetTmrChTrigSrc_TestCase_2", Mt_Lpit_Lpit_Drv_LpitSetTmrChTrigSrc_TestCase_2);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_Drv_LpitSetTmrChMode_TestCase_1", Mt_Lpit_Lpit_Drv_LpitSetTmrChMode_TestCase_1);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_Drv_LpitSetTmrChMode_TestCase_2", Mt_Lpit_Lpit_Drv_LpitSetTmrChMode_TestCase_2);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_InitLpitInstance_TestCase_1", Mt_Lpit_Lpit_InitLpitInstance_TestCase_1);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_InitLpitInstance_TestCase_2", Mt_Lpit_Lpit_InitLpitInstance_TestCase_2);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_InitLpitInstance_TestCase_3", Mt_Lpit_Lpit_InitLpitInstance_TestCase_3);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_InitLpitTmrChn_TestCase_1", Mt_Lpit_Lpit_InitLpitTmrChn_TestCase_1);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_InitLpitTmrChn_TestCase_2", Mt_Lpit_Lpit_InitLpitTmrChn_TestCase_2);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_LpitSetTmrEnable_TestCase_1", Mt_Lpit_Lpit_LpitSetTmrEnable_TestCase_1);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_LpitSetTmrEnblBit_TestCase_1", Mt_Lpit_Lpit_LpitSetTmrEnblBit_TestCase_1);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_LpitSetTmrChCompVal_TestCase_1", Mt_Lpit_Lpit_LpitSetTmrChCompVal_TestCase_1);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_LpitSetTmrChIntEnbl_TestCase_1", Mt_Lpit_Lpit_LpitSetTmrChIntEnbl_TestCase_1);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_LpitReturnCount_TestCase_1", Mt_Lpit_Lpit_LpitReturnCount_TestCase_1);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_LpitClearTimeout_TestCase_1", Mt_Lpit_Lpit_LpitClearTimeout_TestCase_1);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_ClearInterruptFlag_TestCase_1", Mt_Lpit_Lpit_ClearInterruptFlag_TestCase_1);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_TmrChannelEnable_TestCase_1", Mt_Lpit_Lpit_TmrChannelEnable_TestCase_1);
 ALUnitTest_AddFunction("Mt_Lpit_Lpit_Drv_Init_TestCase_1", Mt_Lpit_Lpit_Drv_Init_TestCase_1);

}

// EOF

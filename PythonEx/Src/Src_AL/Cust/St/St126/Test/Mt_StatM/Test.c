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
/// \brief  Unit Test Cases for StatM
///
/// \author Pop Anca Alexandra (M01470A)
///         mailTo:ancaalexandra.pop[at]marelli.com
//-----------------------------------------------------------------------------

//==============================================================================
//  Files covered by this module unit test:
//            - ctaaStatM.c
//            - StatM.c
//==============================================================================

//=============================================================================
// Includes
//=============================================================================

// Standard unit test header
#include <ALUnitTest_UserInterface.h>
#include <stdio.h>
#include <string.h>

// Stub headers
#include "Test_Stubs.h"

// Headers of the unit test Module
#include "Test.h"

//-----------------------------------------------------------------------------
//  Module Test Cases
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/// \Test Case : Mt_StatM__vEcuTimeProcessing
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function increment the cyclic time counters
///                     of Ecu
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions:
///
/// \input ucEcuOnTime : counter for cycle time
/// \input ulEcuOnTime : counter for ECU on time
///
///   - Expectations:
///
/// \output ulEcuOnTime_Output : output value for Ecu on time
///
//-----------------------------------------------------------------------------
void Mt_StatM__vEcuTimeProcessing(void)
{
  //Step 1: Set pre-conditions

  struct { uint8  ucEcuOnTime;           uint32 ulEcuOnTime;          uint32 ulEcuOnTime_Output;         } asTestCaseData[]
    = {  {       0u,                            UINT32_MAX - 1u,                UINT32_MAX - 1u,         },
         {       11u,                           UINT32_MAX - 2u,                UINT32_MAX - 1u,         },
         {       11u,                           UINT32_MAX ,                    UINT32_MAX ,             },
         {       8u,                            UINT32_MAX,                     UINT32_MAX ,             },
  };
  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 2) Assign Input values
    ucEcuOnTime = asTestCaseData[ucIdx].ucEcuOnTime;
    StatM_stStat.ulEcuOnTime = asTestCaseData[ucIdx].ulEcuOnTime;

    //Step 3) Call FUT
    StatM__vEcuTimeProcessing();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(StatM_stStat.ulEcuOnTime, asTestCaseData[ucIdx].ulEcuOnTime_Output, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_StatM__vLedTimeProcessing
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function increment the cyclic time counters
///                     of Led
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions:
///
/// \input ucLedOn : counter for cycle time
/// \input Chn_Status    : channel status 
/// \input ucLedCh : index led chn
/// \input ulLedOnTimer : counter for LED on time
///
///   - Expectations:
///
/// \output ulEcuOnTime_Output : output value for LED counter 
///
//-----------------------------------------------------------------------------
void Mt_StatM__vLedTimeProcessing(void)
{
  //Step 1: Set pre-conditions

    struct { uint8 ucLedOn;  tCddLedChnStatus Chn_Status;               uint8 ucLedCh;    uint32 ulLedOnTimer;          uint32 ulLedOn_Output } asTestCaseData[]
    = {  {          10u,                    eCddLed_ChnOn,              0u,               UINT32_MAX - 1u,                UINT32_MAX          },
         {          8u,                     eCddLed_ChnOn,              1u,               UINT32_MAX ,                    UINT32_MAX          },
         {          10u,                    eCddLed_ChnOff,             2u,               UINT32_MAX ,                    UINT32_MAX          },
         {          10u,                    eCddLed_ChnOn,              3u,               UINT32_MAX ,                    UINT32_MAX          },

    };
  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    
      //Step 2) Assign Input values
      Rte_Read_CddLed_Status_Param1.aStatus[asTestCaseData[ucIdx].ucLedCh].Chn = asTestCaseData[ucIdx].Chn_Status;
      ucLedOnTime[asTestCaseData[ucIdx].ucLedCh] = asTestCaseData[ucIdx].ucLedOn;
      StatM_stStat.ulLedOnTime[asTestCaseData[ucIdx].ucLedCh] = asTestCaseData[ucIdx].ulLedOnTimer;

      //Step 3) Call FUT
      StatM__vLedTimeProcessing();

      //Step 4) Check expected output values
      AL_UNITTEST_CHECK(StatM_stStat.ulLedOnTime[asTestCaseData[ucIdx].ucLedCh], asTestCaseData[ucIdx].ulLedOn_Output, == );
    
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_StatM__vTempClassProcessing
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function increment the cyclic time counters
///                     of Temperature
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions:
///
/// \input nVal : temperature msg
/// \input eQty : signal quality
/// \input ucTempTime :counter for cycle time
/// \input ucId : index for temp zone
/// \input ulStatTempTime counter for Temperature Class
///
///   - Expectations:
///
/// \output ulStatTempTime_Output : output value for Temperature on time
///
//-----------------------------------------------------------------------------
void Mt_StatM__vTempClassProcessing(void)
{
  //Step 1: Set pre-conditions

  struct { sint16 nVal;              teRte_SigQty eQty;         uint8 ucTempTime;  uint8 ucId;  uint32 ulStatTempTime;            uint32 ulStatTempTime_Output;          } asTestCaseData[]
    = {  {        STATM_TEMP_130,                 SIG_VALID,             10u,            4u,                 UINT32_MAX,                     UINT32_MAX                  },
         {        STATM_TEMP_110,                 SIG_VALID,             10u,            3u,                 UINT32_MAX,                     UINT32_MAX                  },
         {        STATM_TEMP_70,                  SIG_VALID,             10u,            1u,                 UINT32_MAX,                     UINT32_MAX                  },
         {        STATM_TEMP_90,                  SIG_VALID,             10u,            2u,                 1u,                             2u                          },
         {        STATM_TEMP_0,                   SIG_VALID,             10u,            0u,                 UINT32_MAX,                     UINT32_MAX                  },
         {        1350,                           SIG_VALID,             10u,            5u,                 UINT32_MAX,                     UINT32_MAX                  },
         {        STATM_TEMP_130,                 SIG_INVALID,           10u,            5u,                 UINT32_MAX,                     UINT32_MAX                  },
         {        STATM_TEMP_90,                  SIG_VALID,             8u,             2u,                 5u,                             5u                          },

  };
  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 2) Assign Input values
    StatM__vTempClassProcessing_Param1.eQty = asTestCaseData[ucIdx].eQty;
    StatM__vTempClassProcessing_Param1.nVal = asTestCaseData[ucIdx].nVal;
    StatM__vTempClassProcessing_Param2[asTestCaseData[ucIdx].ucId] = asTestCaseData[ucIdx].ucTempTime;
    StatM__vTempClassProcessing_Param3[asTestCaseData[ucIdx].ucId]= asTestCaseData[ucIdx].ulStatTempTime;


    //Step 3) Call FUT
    StatM__vTempClassProcessing(StatM__vTempClassProcessing_Param1, StatM__vTempClassProcessing_Param2, StatM__vTempClassProcessing_Param3);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(StatM__vTempClassProcessing_Param3[asTestCaseData[ucIdx].ucId], asTestCaseData[ucIdx].ulStatTempTime_Output, == );
    
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_StatM__vErrorCountersProcessing_TestCase1
///
/// \Functional Safety: QM
///
/// \Test Case Description
///    - Test subject:  Check that the error counters are incremented correctly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input StatM_stStat : {0}
/// \input Rte_Read_CddLed_Status_Param1.aStatus[0u].TempData.boThermalWarning = TRUE;
/// \input Rte_Read_CddLed_LedState_Param1.aLedStates[0].eLedErrStatus = eRteCddLed_ErrThermShutdn;
/// \input Rte_Read_CddLed_LedState_Param1.aLedStates[0].boVinBoostOk = TRUE;
/// \input Rte_Read_CddBoost_BoostStatus_Param1.aStatus[0] = eCddBoost_ErrThermShutdn;
/// \input Rte_Read_CddBoost_BoostStatus_Param1.aboThermalWarning[0] = TRUE;
///
///   - Expectations:
///
/// \output StatM_stStat.unBuck_TW[0] = 1u
/// \output StatM_stStat.unBuck_TSD[0] = 1u
/// \output StatM_stStat.unBooster_TW = 1u
/// \output StatM_stStat.unBooster_TSD = 1u
/// \output StatM_stStat.unBooster_VBoostUV_Err = 0u
///
//-----------------------------------------------------------------------------
void Mt_StatM__vErrorCountersProcessing_TestCase1(void)
{
  //Step 1: Set pre-conditions
  tstStatistics sStatM = { { 0u}, 0, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
  
  //Step 2) Assign Input values
  memcpy(&StatM_stStat, &sStatM, sizeof(tstStatistics));

  Rte_Read_CddLed_Status_Param1.aStatus[0u].TempData.boThermalWarning = TRUE;
  Rte_Read_CddLed_LedState_Param1.aLedStates[0].eLedErrStatus = eRteCddLed_ErrThermShutdn;
  Rte_Read_CddLed_LedState_Param1.aLedStates[0].boVinBoostOk = TRUE;
  Rte_Read_CddBoost_BoostStatus_Param1.aStatus[0] = eCddBoost_ErrThermShutdn;
  Rte_Read_CddBoost_BoostStatus_Param1.aboThermalWarning[0] = TRUE;

  //Step 3) Call FUT
  StatM__vErrorCountersProcessing();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(StatM_stStat.unBuck_TW[0], 1u, == );
  AL_UNITTEST_CHECK(StatM_stStat.unBuck_TSD[0], 1u, == );
  AL_UNITTEST_CHECK(StatM_stStat.unBooster_TW, 1u, == );
  AL_UNITTEST_CHECK(StatM_stStat.unBooster_TSD, 1u, == );
  AL_UNITTEST_CHECK(StatM_stStat.unBooster_VBoostUV_Err, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_StatM__vErrorCountersProcessing_TestCase2
///
/// \Functional Safety: QM
///
/// \Test Case Description
///    - Test subject:  Check that the error counters are incremented correctly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input StatM_stStat : {0}
/// \input Rte_Read_CddLed_Status_Param1.aStatus[0u].TempData.boThermalWarning = TRUE;
/// \input Rte_Read_CddLed_LedState_Param1.aLedStates[0].eLedErrStatus = eRteCddLed_ErrThermShutdn;
/// \input Rte_Read_CddLed_LedState_Param1.aLedStates[0].boVinBoostOk = FALSE;
/// \input Rte_Read_CddBoost_BoostStatus_Param1.aStatus[0] = eCddBoost_ErrVoltHi;
/// \input Rte_Read_CddBoost_BoostStatus_Param1.aboThermalWarning[0] = FALSE;
///
///   - Expectations:
///
/// \output StatM_stStat.unBuck_TW[0] = 0u
/// \output StatM_stStat.unBuck_TSD[0] = 0u
/// \output StatM_stStat.unBooster_TW = 0u
/// \output StatM_stStat.unBooster_TSD = 0u
/// \output StatM_stStat.unBooster_VBoostUV_Err = 0u
///
//-----------------------------------------------------------------------------
void Mt_StatM__vErrorCountersProcessing_TestCase2(void)
{
  //Step 1: Set pre-conditions
  tstStatistics sStatM = { { 0u}, 0, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };

  //Step 2) Assign Input values
  memcpy(&StatM_stStat, &sStatM, sizeof(tstStatistics));

  Rte_Read_CddLed_Status_Param1.aStatus[0u].TempData.boThermalWarning = TRUE;
  Rte_Read_CddLed_LedState_Param1.aLedStates[0].eLedErrStatus = eRteCddLed_ErrThermShutdn;
  Rte_Read_CddLed_LedState_Param1.aLedStates[0].boVinBoostOk = FALSE;
  Rte_Read_CddBoost_BoostStatus_Param1.aStatus[0] = eCddBoost_ErrVoltHi;
  Rte_Read_CddBoost_BoostStatus_Param1.aboThermalWarning[0] = FALSE;

  //Step 3) Call FUT
  StatM__vErrorCountersProcessing();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(StatM_stStat.unBuck_TW[0], 0u, == );
  AL_UNITTEST_CHECK(StatM_stStat.unBuck_TSD[0], 0u, == );
  AL_UNITTEST_CHECK(StatM_stStat.unBooster_TW, 0u, == );
  AL_UNITTEST_CHECK(StatM_stStat.unBooster_TSD, 0u, == );
  AL_UNITTEST_CHECK(StatM_stStat.unBooster_VBoostUV_Err, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_StatM__vErrorCountersProcessing_TestCase3
///
/// \Functional Safety: QM
///
/// \Test Case Description
///    - Test subject:  Check that the error counters are incremented correctly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input StatM_stStat : {0}
/// \input Rte_Read_CddLed_LedState_Param1.aLedStates[0].boVinBoostOk = FALSE;
///
///   - Expectations:
///
/// \output StatM_stStat.unBooster_VBoostUV_Err = 1u
///
//-----------------------------------------------------------------------------
void Mt_StatM__vErrorCountersProcessing_TestCase3(void)
{
  //Step 1: Set pre-conditions
  tstStatistics sStatM = { { 0u}, 0, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };

  //Step 2) Assign Input values
  memcpy(&StatM_stStat, &sStatM, sizeof(tstStatistics));

  Rte_Read_CddLed_LedState_Param1.aLedStates[0].boVinBoostOk = FALSE;


  //Step 3) Call FUT
  StatM__vErrorCountersProcessing();
  StatM__vErrorCountersProcessing();
  StatM__vErrorCountersProcessing();
  StatM__vErrorCountersProcessing();
  StatM__vErrorCountersProcessing();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(StatM_stStat.unBooster_VBoostUV_Err, 1u, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_StatM__vFanTimeProcessing
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function increment the cyclic time counters
///                     of Fan
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions:
///
/// \input ucFan_Idx    : index for FAN device
/// \input unActVal     : actual value for CddSwi Switch Status
/// \input unActCurrent : current value for CddSwi Switch Status
/// \input ucFan1OnTime : counter for cycle time
/// \input ucFan2OnTime : counter for cycle time
/// \input ulFanOnTime  : counter for FAN on time
///
///   - Expectations:
///
/// \output ulFanOnTime_Output : output value for FAN on time
///
//-----------------------------------------------------------------------------
void Mt_StatM__vFanTimeProcessing(void)
{
  //Step 1: Set pre-conditions
    struct { uint8 ucFan_Idx;   tun16Percent_1_328 unActVal;  tiu16Current_mA unActCurrent;    uint8 ucFan1OnTime;                 uint8 ucFan2OnTime;              uint32 ulFanOnTime;         uint32 ulFanOnTime_Output; }asTestCaseData[]
      = {  {      0u,                                1u,                          1u,               STATM_CYCLES_IN_1S,                  STATM_CYCLES_IN_1S,               UINT32_MAX - 1u,              UINT32_MAX         },
           {      0u,                                0u,                          0u,               STATM_CYCLES_IN_1S,                  STATM_CYCLES_IN_1S,               UINT32_MAX,                   UINT32_MAX         },
           {      0u,                                1u,                          1u,               8u,                                                  8u,               UINT32_MAX,                   UINT32_MAX         },
           {      0u,                                1u,                          1u,               STATM_CYCLES_IN_1S ,                 STATM_CYCLES_IN_1S,               UINT32_MAX,                   UINT32_MAX         },
           {      1u,                                1u,                          1u,               STATM_CYCLES_IN_1S,                  STATM_CYCLES_IN_1S,               UINT32_MAX - 1u,              UINT32_MAX         },
           {      1u,                                0u,                          0u,               STATM_CYCLES_IN_1S,                  STATM_CYCLES_IN_1S,               UINT32_MAX,                   UINT32_MAX         },
           {      1u,                                1u,                          1u,               8u,                                                  8u,               UINT32_MAX,                   UINT32_MAX         },
           {      1u,                                1u,                          1u,               STATM_CYCLES_IN_1S ,                 STATM_CYCLES_IN_1S,               UINT32_MAX,                   UINT32_MAX         },
    };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 2) Assign Input values
    Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[asTestCaseData[ucIdx].ucFan_Idx].unActVal = asTestCaseData[ucIdx].unActVal;
    Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[asTestCaseData[ucIdx].ucFan_Idx].unActCurrent = asTestCaseData[ucIdx].unActCurrent;
    ucFan1OnTime = asTestCaseData[ucIdx].ucFan1OnTime;
    ucFan2OnTime = asTestCaseData[ucIdx].ucFan2OnTime;
    StatM_stStat.ulFanOnTime[asTestCaseData[ucIdx].ucFan_Idx] = asTestCaseData[ucIdx].ulFanOnTime;

    //Step 3) Call FUT
    StatM__vFanTimeProcessing();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(StatM_stStat.ulFanOnTime[asTestCaseData[ucIdx].ucFan_Idx], asTestCaseData[ucIdx].ulFanOnTime_Output, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_StatM__vStpTimeProcessing_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function increment the cyclic time counters 
///                     of Stepper if StepLoss is detected
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError = sStatusError_Tst
/// \input StatM_boStepLoss = FALSE
/// \input StatM_boWasMoving = FALSE
/// \input StatM_stStat = sStatM
///
///   - Expectations:
///
/// \output StatM_stStat.unStepperSteploss =1u
/// \output StatM_stStat.ulStepperMoveTime =1u
/// \output StatM_stStat.unStepperStarted =1u
///
//-----------------------------------------------------------------------------
void Mt_StatM__vStpTimeProcessing_TestCase1(void)
{
    tisStpStatusError sStatusError_Tst = { SUPPORT_YES, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, 0U, TRUE, TRUE,TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, FALSE, FALSE };
    Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError = sStatusError_Tst;
    StatM_boStepLoss = FALSE;
    StatM_boWasMoving = FALSE;
    StatM_ucMoveTime = STATM_CYCLES_IN_1S;
    tstStatistics sStatM = { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
    memcpy(&StatM_stStat, &sStatM, sizeof(tstStatistics));

    //Step 3) Call FUT
    StatM__vStpTimeProcessing();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(StatM_stStat.unStepperSteploss, 1u, == );
    AL_UNITTEST_CHECK(StatM_stStat.ulStepperMoveTime, 1u, == );
    AL_UNITTEST_CHECK(StatM_stStat.unStepperStarted, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_StatM__vStpTimeProcessing_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function increment the cyclic time counters
///                     of Stepper is StepLoss was not detected
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError = sStatusError_Tst
/// \input StatM_boStepLoss = FALSE
/// \input StatM_boWasMoving = FALSE
/// \input StatM_stStat = sStatM
/// \input StatM_ucMoveTime = STATM_CYCLES_IN_1S
///
///   - Expectations:
///
/// \output StatM_stStat.unStepperSteploss =UINT16_MAX
/// \output StatM_stStat.ulStepperMoveTime =UINT32_MAX
/// \output StatM_stStat.unStepperStarted =UINT16_MAX
///
//-----------------------------------------------------------------------------
void Mt_StatM__vStpTimeProcessing_TestCase2(void)
{
    tisStpStatusError sStatusError_Tst = { SUPPORT_YES, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, 0U, TRUE, TRUE,TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, FALSE, FALSE };
    Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError = sStatusError_Tst;
    StatM_boStepLoss = FALSE;
    StatM_boWasMoving = FALSE;
    StatM_ucMoveTime = STATM_CYCLES_IN_1S;
    tstStatistics sStatM = { {{0u}}, 0u, UINT32_MAX, UINT16_MAX, 0u, UINT16_MAX, {{0u}}, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
    memcpy(&StatM_stStat, &sStatM, sizeof(tstStatistics));

    //Step 3) Call FUT
    StatM__vStpTimeProcessing();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(StatM_stStat.unStepperSteploss, UINT16_MAX, == );
    AL_UNITTEST_CHECK(StatM_stStat.ulStepperMoveTime, UINT32_MAX, == );
    AL_UNITTEST_CHECK(StatM_stStat.unStepperStarted, UINT16_MAX, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_StatM__vStpTimeProcessing_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function increment the cyclic time counters
///                     of Stepper if the Stepper is moving
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError = sStatusError_Tst
/// \input StatM_boStepLoss = TRUE
/// \input StatM_boWasMoving = TRUE
/// \input StatM_stStat = sStatM
/// \input StatM_ucMoveTime = STATM_CYCLES_IN_1S
///
///   - Expectations:
///
/// \output StatM_stStat.ulStepperHoldTime =1u
/// \output StatM_stStat.unStepperFinishedUnsuccesfull =1u
///
//-----------------------------------------------------------------------------
void Mt_StatM__vStpTimeProcessing_TestCase3(void)
{
    tisStpStatusError sStatusError_Tst = { SUPPORT_YES, TRUE, TRUE, TRUE, FALSE, TRUE, TRUE, TRUE, 0U, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, FALSE, FALSE };
    Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError = sStatusError_Tst;
    StatM_boStepLoss = TRUE;
    StatM_ucHoldTime = STATM_CYCLES_IN_1S;
    StatM_boWasMoving = TRUE;
    tstStatistics sStatM = { 0u, 0u, UINT32_MAX, UINT16_MAX, 0u, UINT16_MAX, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
    memcpy(&StatM_stStat, &sStatM, sizeof(tstStatistics));

    //Step 3) Call FUT
    StatM__vStpTimeProcessing();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(StatM_stStat.ulStepperHoldTime, 1u, == );
    AL_UNITTEST_CHECK(StatM_stStat.unStepperFinishedUnsuccesfull, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_StatM__vStpTimeProcessing_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function increment the cyclic time counters
///                     of Stepper for a transition from moving to stop moving
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError = sStatusError_Tst
/// \input StatM_boStepLoss = TRUE
/// \input StatM_boWasMoving = FALSE
/// \input StatM_stStat = sStatM
/// \input StatM_ucMoveTime = 8u
///
///   - Expectations:
///
/// \output StatM_stStat.ulStepperHoldTime =0u
/// \output StatM_stStat.unStepperFinishedUnsuccesfull =0u
///
//-----------------------------------------------------------------------------
void Mt_StatM__vStpTimeProcessing_TestCase4(void)
{
    tisStpStatusError sStatusError_Tst = { SUPPORT_YES, TRUE, TRUE, TRUE, FALSE, TRUE, TRUE, TRUE, 0U, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, FALSE, FALSE };
    Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError = sStatusError_Tst;
    StatM_boStepLoss = TRUE;
    StatM_ucHoldTime = 8u;
    StatM_boWasMoving = FALSE;
    tstStatistics sStatM = { 0u, 0u, UINT32_MAX, UINT16_MAX, 0u, UINT16_MAX, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
    memcpy(&StatM_stStat, &sStatM, sizeof(tstStatistics));

    //Step 3) Call FUT
    StatM__vStpTimeProcessing();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(StatM_stStat.ulStepperHoldTime, 0u, == );
    AL_UNITTEST_CHECK(StatM_stStat.unStepperFinishedUnsuccesfull, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_StatM__vStpTimeProcessing_TestCase5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function increment the cyclic time counters
///                     of Stepper for a transition when stepper is not moving
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError = sStatusError_Tst
/// \input StatM_boWasMoving = TRUE
/// \input StatM_stStat = sStatM
/// \input StatM_ucMoveTime = STATM_CYCLES_IN_1S
///
///   - Expectations:
///
/// \output StatM_stStat.ulStepperHoldTime =0u
///
//-----------------------------------------------------------------------------
void Mt_StatM__vStpTimeProcessing_TestCase5(void)
{
    tisStpStatusError sStatusError_Tst = { SUPPORT_YES, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, 0U, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
    Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError = sStatusError_Tst;
    StatM_boWasMoving = TRUE;
    StatM_ucMoveTime = 8u;
    tstStatistics sStatM = { {{ 0u}}, UINT32_MAX+1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
    memcpy(&StatM_stStat, &sStatM, sizeof(tstStatistics));

    //Step 3) Call FUT
    StatM__vStpTimeProcessing();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(StatM_stStat.ulStepperMoveTime, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_StatM__vStpTimeProcessing_TestCase6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function increment the cyclic time counters
///                     of Stepper for a transition from moving to stop moving and 
///                     if an error is detected
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError = sStatusError_Tst
/// \input StatM_stStat = sStatM
/// \input StatM_ucHoldTime = STATM_CYCLES_IN_1S
///
///   - Expectations:
///
/// \output StatM_stStat.ulStepperHoldTime =UINT32_MAX
/// \output StatM_stStat.unStepperFinishedUnsuccesfull =UINT16_MAX
///
//-----------------------------------------------------------------------------
void Mt_StatM__vStpTimeProcessing_TestCase6(void)
{
    tisStpStatusError sStatusError_Tst = { SUPPORT_YES, TRUE, TRUE, TRUE, FALSE, TRUE, TRUE, TRUE, 0U, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, FALSE };
    Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError = sStatusError_Tst;
    tstStatistics sStatM = { {{0u}}, UINT32_MAX, 0u, 0u, UINT16_MAX, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
    memcpy(&StatM_stStat, &sStatM, sizeof(tstStatistics));
    StatM_ucHoldTime = STATM_CYCLES_IN_1S;

    //Step 3) Call FUT
    StatM__vStpTimeProcessing();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(StatM_stStat.unStepperFinishedUnsuccesfull, UINT16_MAX, == );
    AL_UNITTEST_CHECK(StatM_stStat.ulStepperHoldTime, UINT32_MAX, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_StatM__vStpTimeProcessing_TestCase7
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function increment the cyclic time counters
///                     of Stepper for a transition from moving to stop moving and 
///                     if an error isn't detected
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError = sStatusError_Tst
/// \input StatM_boWasMoving = TRUE
/// \input StatM_stStat = sStatM
///
///   - Expectations:
///
/// \output StatM_stStat.unStepperFinishedUnsuccesfull =0u
///
//-----------------------------------------------------------------------------
void Mt_StatM__vStpTimeProcessing_TestCase7(void)
{
    tisStpStatusError sStatusError_Tst = { SUPPORT_YES, TRUE, TRUE, TRUE, FALSE, TRUE, TRUE, TRUE, 0U, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
    Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError = sStatusError_Tst;
    StatM_boWasMoving = TRUE;
    tstStatistics sStatM = { {{0u}}, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
    memcpy(&StatM_stStat, &sStatM, sizeof(tstStatistics));

    //Step 3) Call FUT
    StatM__vStpTimeProcessing();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(StatM_stStat.unStepperFinishedUnsuccesfull, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_StatM__vTempTimeProcessing
///
/// \Functional Safety: NA
///
/// \Test Case Description  Check that the function increment the cyclic time counters
///                         for Temperature Zones and PCB in  a  given Temperature Class
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions:
///
/// \input Rte_Read_RSens_PcbTemperature_Param1.eQty = SIG_VALID;
/// \input Rte_Read_RSens_PcbTemperature_Param1.nVal = STATM_TEMP_130
/// \input Rte_Read_RSens_PcbTemperature_HitCount  = 0u
/// \input Rte_Read_RSens_ThermzoneTemperatures_Param1.s16_NTCTemperatureCelsius[1u] = 15u
/// \input Rte_Read_RSens_ThermzoneTemperatures_HitCount  = 0u
///
///   - Expectations:
///
/// \output StatM_stStat.ulTempZoneTime[1u][1u] = 0u
/// \output Rte_Read_RSens_PcbTemperature_HitCount = 1u
/// \output Rte_Read_RSens_ThermzoneTemperatures_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_StatM__vTempTimeProcessing(void)
{
    //Step 1: Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_RSens_PcbTemperature_Param1.eQty = SIG_VALID;
    Rte_Read_RSens_PcbTemperature_Param1.nVal = STATM_TEMP_130;
    Rte_Read_RSens_ThermzoneTemperatures_Param1.s16_NTCTemperatureCelsius[1u] = 15u;
    Rte_Read_RSens_PcbTemperature_HitCount = 0u;
    Rte_Read_RSens_ThermzoneTemperatures_HitCount = 0u;

    //Step 3) Call FUT
    StatM__vTempTimeProcessing();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Rte_Read_RSens_PcbTemperature_HitCount, 1u, == );
    AL_UNITTEST_CHECK(Rte_Read_RSens_ThermzoneTemperatures_HitCount, 1u, == );
    AL_UNITTEST_CHECK(StatM_stStat.ulTempZoneTime[1u][1u], 0u, == );
  
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_StatM_Cycle0
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the cyclic runnable calls and executes
///                     the cycle function of StatM and does stack measurment
///                     according to the MeasureStack parameter
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions:
///
/// \input boMeasureStack : flag status for stack Measurement
/// \input StatM_boMeasureStack = asTestCaseData[ucIdx].boMeasureStack;
/// \input ucEcuOnTime = STATM_CYCLES_IN_1S;
/// \input StatM_stStat.ulEcuOnTime = 0u;
/// \input Rte_Read_CddLed_Status_Param1.aStatus[0u].Chn = eCddLed_ChnOn;
/// \input ucLedOnTime[0u] = STATM_CYCLES_IN_1S;
/// \input StatM_stStat.ulLedOnTime[0u] = 0u;
/// \input Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[0u].unActVal = 1u;
/// \input Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[0u].unActCurrent = 1u;
/// \input ucFan1OnTime = STATM_CYCLES_IN_1S;
/// \input StatM_stStat.ulFanOnTime[0u] = 0u;
/// \input Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[1u].unActVal = 1u;
/// \input Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[1u].unActCurrent = 1u;
/// \input ucFan1OnTime = STATM_CYCLES_IN_1S;
/// \input StatM_stStat.ulFanOnTime[1u] = 0u;
/// \input StatM_boStepLoss = FALSE;
/// \input StatM_stStat.unStepperSteploss = 0u;
/// \input StatM_ucMoveTime = STATM_CYCLES_IN_1S;
/// \input StatM_boWasMoving = FALSE;
/// \input StatM_ucHoldTime = STATM_CYCLES_IN_1S;
/// \input StatM_stStat.ulStepperHoldTime = UINT32_MAX;
/// \input Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError = sStatusError_Tst;
/// \input StatM_stStat.unStepperFinishedUnsuccesfull = UINT16_MAX;
/// \input StatM_stStat.ulStepperMoveTime = 0u;
/// \input StatM_stStat.unStepperStarted = 0u;
/// \input StatM_ucTimeCount_stack = STATM_CYCLES_IN_10S
/// \input Rte_Read_RSens_PcbTemperature_Param1.eQty = SIG_VALID;
/// \input Rte_Read_RSens_PcbTemperature_Param1.nVal = STATM_TEMP_130;
/// \input Rte_Read_RSens_ThermzoneTemperatures_Param1.s16_NTCTemperatureCelsius[1u] = 15u;
///
///   - Expectations:
///
/// \output StatM_stStat.ulEcuOnTime = 1u
/// \output StatM_stStat.ulLedOnTime[0u] = 1u
/// \output StatM_stStat.ulFanOnTime[0u] = 1u
/// \output StatM_stStat.ulFanOnTime[1u] = 0u
/// \output StatM_stStat.unStepperSteploss = 1u
/// \output StatM_stStat.ulStepperMoveTime = 1u
/// \output StatM_stStat.unStepperStarted = 1u,
/// \output StatM_stStat.ulStepperHoldTime = UINT32_MAX
/// \output StatM_stStat.unStepperFinishedUnsuccesfull = UINT16_MAX
///
//-----------------------------------------------------------------------------
void Mt_StatM_Cycle0(void)
{
  //Step 1: Set pre-conditions

    struct { boolean boMeasureStack;   uint8 ucHitCount;  uint8 ucHitCount_Output; }asTestCaseData[]
    ={   {          TRUE,                     0u,                       1u       },
         {          FALSE,                    0u,                       0u       },
  };
  
  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 2) Assign Input values
    StatM_boMeasureStack = asTestCaseData[ucIdx].boMeasureStack;
    StatM_ucTimeCount_stack = STATM_CYCLES_IN_10S;
    ucEcuOnTime = STATM_CYCLES_IN_1S;
    StatM_stStat.ulEcuOnTime = 0u;

    Rte_Read_CddLed_Status_Param1.aStatus[0u].Chn = eCddLed_ChnOn;
    ucLedOnTime[0u] = STATM_CYCLES_IN_1S;
    StatM_stStat.ulLedOnTime[0u] = 0u;

    Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[0u].unActVal = 1u;
    Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[0u].unActCurrent = 1u;
    ucFan1OnTime = STATM_CYCLES_IN_1S;
    StatM_stStat.ulFanOnTime[0u] = 0u;
    Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[1u].unActVal = 1u;
    Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[1u].unActCurrent = 1u;
    ucFan1OnTime = STATM_CYCLES_IN_1S;
    StatM_stStat.ulFanOnTime[1u] = 0u;

    
    StatM_boStepLoss = FALSE;
    StatM_stStat.unStepperSteploss = 0u;
    StatM_ucMoveTime = STATM_CYCLES_IN_1S;
    StatM_boWasMoving = FALSE;
    StatM_ucHoldTime = STATM_CYCLES_IN_1S;
    StatM_stStat.ulStepperHoldTime = UINT32_MAX;
    tisStpStatusError sStatusError_Tst = { SUPPORT_YES, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, 0U, TRUE, TRUE,TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, FALSE, FALSE };
    Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError = sStatusError_Tst;
    StatM_stStat.unStepperFinishedUnsuccesfull = UINT16_MAX;
    StatM_stStat.ulStepperMoveTime = 0u;
    StatM_stStat.unStepperStarted = 0u;

    Rte_Read_RSens_PcbTemperature_Param1.eQty = SIG_VALID;
    Rte_Read_RSens_PcbTemperature_Param1.nVal = STATM_TEMP_130;
    Rte_Read_RSens_ThermzoneTemperatures_Param1.s16_NTCTemperatureCelsius[1u] = 15u;

    Rte_Write_StatM_StackUsage_HitCount = asTestCaseData[ucIdx].ucHitCount;

    //Step 3) Call FUT
    StatM_Cycle0();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(StatM_stStat.ulEcuOnTime, 1u, == );
    AL_UNITTEST_CHECK(StatM_stStat.ulLedOnTime[0u], 1u, == );
    AL_UNITTEST_CHECK(StatM_stStat.ulFanOnTime[0u], 1u, == );
    AL_UNITTEST_CHECK(StatM_stStat.ulFanOnTime[1u], 0u, == );
    AL_UNITTEST_CHECK(StatM_stStat.unStepperSteploss, 1u, == );
    AL_UNITTEST_CHECK(StatM_stStat.ulStepperMoveTime, 1u, == );
    AL_UNITTEST_CHECK(StatM_stStat.unStepperStarted, 1u, == );
    AL_UNITTEST_CHECK(StatM_stStat.ulStepperHoldTime, UINT32_MAX, == );
    AL_UNITTEST_CHECK(StatM_stStat.unStepperFinishedUnsuccesfull, UINT16_MAX, == );
    AL_UNITTEST_CHECK(Rte_Write_StatM_StackUsage_HitCount, asTestCaseData[ucIdx].ucHitCount_Output, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_StatM_Init
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the init function reads stat from Nvm, increment the reset counter
///                     with limitation to max
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions:
///
/// \input unEcuReset
///
///   - Expectations:
///
/// \output   unEcuReset_Output
///
//-----------------------------------------------------------------------------
void Mt_StatM_Init(void)
{
  //Step 1: Set pre-conditions

  struct { uint16 unEcuReset; uint16 unEcuReset_Output }asTestCaseData[]
    = { {          0u,                    1u,              },
         {        UINT16_MAX,          UINT16_MAX,          },
  };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {

    //Step 2) Assign Input values

    NvmBlockStatistics.sStatistics.unEcuReset= asTestCaseData[ucIdx].unEcuReset;

    //Step 3) Call FUT
    StatM_Init();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(StatM_stStat.unEcuReset, asTestCaseData[ucIdx].unEcuReset_Output, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_StatM_ReadStatistics_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function read from NVM
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions:
///
/// \input StatM_ReadStatistics_Param1= &test
/// \input NvmBlockStatistics.sStatistics.unEcuReset = 10u
/// \input StatM_ReadStatistics_Param2 = TRUE
///
///   - Expectations:
///
/// \output StatM_ReadStatistics_Param1->unEcuReset = 10u
///
//-----------------------------------------------------------------------------
void Mt_StatM_ReadStatistics_TestCase1(void)
{
    //Step 1: Set pre-conditions
    tstStatistics test = { 0 };

    //Step 2) Assign Input values
    NvmBlockStatistics.sStatistics.unEcuReset = 10u;
    StatM_ReadStatistics_Param1= &test;
    StatM_ReadStatistics_Param2 = TRUE;

    //Step 3) Call FUT
    StatM_ReadStatistics(StatM_ReadStatistics_Param1, StatM_ReadStatistics_Param2);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(StatM_ReadStatistics_Param1->unEcuReset, 10u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_StatM_ReadStatistics_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function read from internal statM structure
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions:
///
/// \input StatM_ReadStatistics_Param1 = &test
/// \input StatM_stStat.unEcuReset = 10u
/// \input StatM_ReadStatistics_Param2 = FALSE
///
///   - Expectations:
///
/// \output StatM_ReadStatistics_Param1->unEcuReset = 10u
///
//-----------------------------------------------------------------------------
void Mt_StatM_ReadStatistics_TestCase2(void)
{
    //Step 1: Set pre-conditions
    tstStatistics test = { 0 };

    //Step 2) Assign Input values
    StatM_stStat.unEcuReset = 10u;
    StatM_ReadStatistics_Param1 = &test;
    StatM_ReadStatistics_Param2 = FALSE;
    
    //Step 3) Call FUT
    StatM_ReadStatistics(StatM_ReadStatistics_Param1, StatM_ReadStatistics_Param2);
    
    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(StatM_ReadStatistics_Param1->unEcuReset, 10u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_StatM_WriteStatistics
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function write statistics to NvM
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input NvM_WriteBlock_HitCount =0u
/// \input NvM_WriteBlock_Param1 =0u
/// \input NvmBlockStatistics.sStatistics.unEcuReset = 0u
/// \input StatM_stStat.unEcuReset = 10u
///
///   - Expectations:
///
/// \output NvM_WriteBlock_HitCount =1u
/// \output NvM_WriteBlock_Param1 =NvmBlockStatisticsId
/// \output NvmBlockStatistics.sStatistics.unEcuReset = 10u
///
//-----------------------------------------------------------------------------
void Mt_StatM_WriteStatistics(void)
{
   //Step 1: Set pre-conditions
   //Step 2) Assign Input values
   NvM_WriteBlock_HitCount = 0u;
   NvM_WriteBlock_Param1 = 0u;
   NvmBlockStatistics.sStatistics.unEcuReset = 0u;
   StatM_stStat.unEcuReset = 10u;

   //Step 3) Call FUT
   StatM_WriteStatistics();

   //Step 4) Check expected output values
   AL_UNITTEST_CHECK(NvM_WriteBlock_HitCount, 1u, == );
   AL_UNITTEST_CHECK(NvM_WriteBlock_Param1, NvmBlockStatisticsId, == );
   AL_UNITTEST_CHECK(NvmBlockStatistics.sStatistics.unEcuReset, 10u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_StatM__boCheckPatern_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function verify if has the corect pattern
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions:
///
/// \input StatM__boCheckPatern_Param1 = (uint32)&Pattern;
///
///   - Expectations:
///
/// \output StatM__boCheckPatern_RetVal =TRUE
///
//-----------------------------------------------------------------------------
void Mt_StatM__boCheckPatern_TestCase1(void)
{

  //Step 1: Set pre-conditions

  //Step 2) Assign Input values
  uint8 Pattern[4u];
  Pattern[0u] = STATM_ENDOFSTACK_PATTERN_1;
  Pattern[1u] = STATM_ENDOFSTACK_PATTERN_2;
  Pattern[2u] = STATM_ENDOFSTACK_PATTERN_3;
  Pattern[3u] = STATM_ENDOFSTACK_PATTERN_4;
  StatM__boCheckPatern_Param1 = (uint32)&Pattern;

  //Step 3) Call FUT
  StatM__boCheckPatern_RetVal = StatM__boCheckPatern(StatM__boCheckPatern_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(StatM__boCheckPatern_RetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_StatM__boCheckPatern_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function verify if has the corect pattern
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions:
///
/// \input StatM__boCheckPatern_Param1 = (uint32)&Pattern;
///
///   - Expectations:
///
/// \output StatM__boCheckPatern_RetVal = FALSE
///
//-----------------------------------------------------------------------------
void Mt_StatM__boCheckPatern_TestCase2(void)
{
  //Step 1: Set pre-conditions

  //Step 2) Assign Input values
  uint8 Pattern[4u];
  Pattern[0u] = STATM_ENDOFSTACK_PATTERN_1 - 1u;
  Pattern[1u] = STATM_ENDOFSTACK_PATTERN_2;
  Pattern[2u] = STATM_ENDOFSTACK_PATTERN_3;
  Pattern[3u] = STATM_ENDOFSTACK_PATTERN_4;
  StatM__boCheckPatern_Param1 = (uint32)&Pattern;

  //Step 3) Call FUT
  StatM__boCheckPatern_RetVal = StatM__boCheckPatern(StatM__boCheckPatern_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(StatM__boCheckPatern_RetVal, FALSE, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_StatM__unGetNumberFreeBytes_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function return number of bytes between start address and end address
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Pattern_Statm[1u] = STATM_NOTUSEDSTACK_PATTERN
/// \input Pattern_Statm[2u] = STATM_NOTUSEDSTACK_PATTERN+1u
/// \input StatM__unGetNumberFreeBytes_Param1 = (uint32)&Pattern_Statm[1u];
/// \input StatM__unGetNumberFreeBytes_Param2 = (uint32)&Pattern_Statm[2u];
///
///   - Expectations:
///
/// \output StatM__unGetNumberFreeBytes_RetVal= 1u
///
//-----------------------------------------------------------------------------
void Mt_StatM__unGetNumberFreeBytes_TestCase1(void)
{
  //Step 1: Set pre-conditions

  //Step 2) Assign Input values
  uint8 Pattern_Statm[4u];
  Pattern_Statm[1u] = STATM_NOTUSEDSTACK_PATTERN;
  Pattern_Statm[2u] = STATM_NOTUSEDSTACK_PATTERN + 1u;
  StatM__unGetNumberFreeBytes_Param1 = (uint32)&Pattern_Statm[1u];
  StatM__unGetNumberFreeBytes_Param2 = (uint32)&Pattern_Statm[2u];

  //Step 3) Call FUT
  StatM__unGetNumberFreeBytes_RetVal = StatM__unGetNumberFreeBytes(StatM__unGetNumberFreeBytes_Param1, StatM__unGetNumberFreeBytes_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(StatM__unGetNumberFreeBytes_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_StatM__unGetNumberFreeBytes_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function return number of bytes between start address and end address
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Pattern_Statm[1u] = 0u
/// \input Pattern_Statm[2u] = 0u
/// \input StatM__unGetNumberFreeBytes_Param1 = (uint32)&Pattern_Statm[1u]
/// \input StatM__unGetNumberFreeBytes_Param2 = (uint32)&Pattern_Statm[2u]
///
///   - Expectations:
///
/// \output StatM__unGetNumberFreeBytes_RetVal = 0u
///
//-----------------------------------------------------------------------------
void Mt_StatM__unGetNumberFreeBytes_TestCase2(void)
{
  //Step 1: Set pre-conditions

  //Step 2) Assign Input values
  uint8 Pattern_Statm[4u];
  Pattern_Statm[1u] = 0u;
  Pattern_Statm[2u] = 0u;
  StatM__unGetNumberFreeBytes_Param1 = (uint32)&Pattern_Statm[1u];
  StatM__unGetNumberFreeBytes_Param2 = (uint32)&Pattern_Statm[2u];
  
  //Step 3) Call FUT
  StatM__unGetNumberFreeBytes_RetVal = StatM__unGetNumberFreeBytes(StatM__unGetNumberFreeBytes_Param1, StatM__unGetNumberFreeBytes_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(StatM__unGetNumberFreeBytes_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_StatM_Deinit
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function deinitialization of statM module
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions:
///
/// \input StatM_stStat = sStatM
/// \input NvmBlockStatistics.sStatistics.unEcuReset = 10u
///
///   - Expectations:
///
/// \output NvmBlockStatistics.sStatistics.unEcuReset = 0u
///
//-----------------------------------------------------------------------------
void Mt_StatM_Deinit(void)
{
     //Step 1: Set pre-conditions
    //Step 2) Assign Input values
    NvmBlockStatistics.sStatistics.unEcuReset = 10u;

    tstStatistics sStatM = { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
    memcpy(&StatM_stStat, &sStatM, sizeof(tstStatistics));

    //Step 3) Call FUT
    StatM_Deinit();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(NvmBlockStatistics.sStatistics.unEcuReset, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_StatM_ResetStatistics
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function reset all statistics to value 0
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input StatM_stStat.unEcuReset = 10u
/// \input NvM_WriteBlock_HitCount =0u
/// \input NvM_WriteBlock_Param1 =0u
///
///   - Expectations:
///
/// \output NvM_WriteBlock_HitCount =1u
/// \output NvM_WriteBlock_Param1 =8u
/// \output StatM_stStat.unEcuReset= 0u
///
//-----------------------------------------------------------------------------
void Mt_StatM_ResetStatistics(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
   NvM_WriteBlock_HitCount = 0u;
   NvM_WriteBlock_Param1 = 0u;
   StatM_stStat.unEcuReset = 10u;

  //Step 3) Call FUT
   StatM_ResetStatistics();

  //Step 4) Check expected output values
   AL_UNITTEST_CHECK(NvM_WriteBlock_HitCount, 1u, == );
   AL_UNITTEST_CHECK(NvM_WriteBlock_Param1, 8u, == );
   AL_UNITTEST_CHECK(StatM_stStat.unEcuReset, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_StatM__vStackSizeMeasurement_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function verify the end pattern is valid or invalid
///                     for trusted HH 
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions:
///
/// \input StatM_ucTimeCount_stack = STATM_CYCLES_IN_10S
/// \input ucPattern[4] : stack pattern
/// 
///
///   - Expectations:
/// \output ucPercent : percent for Thread
/// \output ucCount_Thread  state for Thread
///
//-----------------------------------------------------------------------------
void Mt_StatM__vStackSizeMeasurement_TestCase1(void)
{
    //Step 1: Set pre-conditions
    
    Rte_Write_StatM_StackUsage_HitCount = 0u;

    struct { uint8 ucPattern[4];                                                                                                   uint16 unPercent;                           uint16 unCount_Thread;                }asTestCaseData[] 
        = { {{STATM_ENDOFSTACK_PATTERN_1, STATM_ENDOFSTACK_PATTERN_2, STATM_ENDOFSTACK_PATTERN_3, STATM_ENDOFSTACK_PATTERN_4} ,             0u,                                      0u                              },
            {{STATM_ENDOFSTACK_PATTERN_1 -1u , STATM_ENDOFSTACK_PATTERN_2, STATM_ENDOFSTACK_PATTERN_3, STATM_ENDOFSTACK_PATTERN_4} ,        STATM_STACK_INVALID,                     STATM_STACK_INVALID             },
};

    for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
    {
        for (uint8 ucI= 0; ucI< 4;ucI++)
        {
            //Step 2) Assign Input values
            ucTemp[0u + ucI] = asTestCaseData[ucIdx].ucPattern[ucI];

        }
        StatM_ucTimeCount_stack = STATM_CYCLES_IN_10S;

        //Step 3) Call FUT
        StatM__vStackSizeMeasurement();

        //Step 4) Check expected output values
        AL_UNITTEST_CHECK(StatM_unUnusedStackTrusted_HH, asTestCaseData[ucIdx].unCount_Thread, == );
        AL_UNITTEST_CHECK(StatM_unUnusedStackTrusted_percent_HH, asTestCaseData[ucIdx].unPercent, == );
    }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_StatM__vStackSizeMeasurement_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function verify the end pattern is valid or invalid
///                     for trusted HL 
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions:
///
/// \input StatM_ucTimeCount_stack = STATM_CYCLES_IN_10S
/// \input ucPattern[4] : stack pattern
/// 
///
///   - Expectations:
/// \output ucPercent : percent for Thread
/// \output ucCount_Thread  state for Thread
///
//-----------------------------------------------------------------------------
void Mt_StatM__vStackSizeMeasurement_TestCase2(void)
{
    //Step 1: Set pre-conditions
    
    Rte_Write_StatM_StackUsage_HitCount = 0u;

    struct { uint8 ucPattern[4];                                                                                                    uint16 unPercent;              uint16 unCount_Thread;                  }asTestCaseData[]
        = { {{STATM_ENDOFSTACK_PATTERN_1, STATM_ENDOFSTACK_PATTERN_2, STATM_ENDOFSTACK_PATTERN_3, STATM_ENDOFSTACK_PATTERN_4} ,              0u,                                0u                         },
            {{STATM_ENDOFSTACK_PATTERN_1 - 1 , STATM_ENDOFSTACK_PATTERN_2, STATM_ENDOFSTACK_PATTERN_3, STATM_ENDOFSTACK_PATTERN_4} ,        STATM_STACK_INVALID,                STATM_STACK_INVALID        },
    };

    for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
    {
        for (uint8 ucI = 0; ucI < 4;ucI++)
        {
            //Step 2) Assign Input values
            ucTemp[RTE_THREAD_T_HH + ucI] = asTestCaseData[ucIdx].ucPattern[ucI];

        }
        StatM_ucTimeCount_stack = STATM_CYCLES_IN_10S;

        //Step 3) Call FUT
        StatM__vStackSizeMeasurement();

        //Step 4) Check expected output values
        AL_UNITTEST_CHECK(StatM_unUnusedStackTrusted_HL, asTestCaseData[ucIdx].unCount_Thread, == );
        AL_UNITTEST_CHECK(StatM_unUnusedStackTrusted_percent_HL, asTestCaseData[ucIdx].unPercent, == );
    }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_StatM__vStackSizeMeasurement_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function verify the end pattern is valid or invalid
///                     for trusted LH 
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions:
///
/// \input StatM_ucTimeCount_stack = STATM_CYCLES_IN_10S
/// \input ucPattern[4] : stack pattern
/// 
///
///   - Expectations:
/// \output ucPercent : percent for Thread
/// \output ucCount_Thread  state for Thread
///
//-----------------------------------------------------------------------------
void Mt_StatM__vStackSizeMeasurement_TestCase3(void)
{
    //Step 1: Set pre-conditions
   
    Rte_Write_StatM_StackUsage_HitCount = 0u;

    struct { uint8 ucPattern[4];                                                                                                   uint16 unPercent;              uint16 unCount_Thread; }asTestCaseData[]
        = { {{STATM_ENDOFSTACK_PATTERN_1, STATM_ENDOFSTACK_PATTERN_2, STATM_ENDOFSTACK_PATTERN_3, STATM_ENDOFSTACK_PATTERN_4} ,              0u,                                0u                           },
            {{STATM_ENDOFSTACK_PATTERN_1 - 1 , STATM_ENDOFSTACK_PATTERN_2, STATM_ENDOFSTACK_PATTERN_3, STATM_ENDOFSTACK_PATTERN_4} ,         STATM_STACK_INVALID,               STATM_STACK_INVALID          },
    };
    for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
    {
        for (uint8 ucI = 0; ucI < 4;ucI++)
        {
            //Step 2) Assign Input values
            ucTemp[RTE_THREAD_T_HH + RTE_THREAD_T_HL + ucI] = asTestCaseData[ucIdx].ucPattern[ucI];

        }
        StatM_ucTimeCount_stack = STATM_CYCLES_IN_10S;

        //Step 3) Call FUT
        StatM__vStackSizeMeasurement();

        //Step 4) Check expected output values
        AL_UNITTEST_CHECK(StatM_unUnusedStackTrusted_LH, asTestCaseData[ucIdx].unCount_Thread, == );
        AL_UNITTEST_CHECK(StatM_unUnusedStackTrusted_percent_LH, asTestCaseData[ucIdx].unPercent, == );
    }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_StatM__vStackSizeMeasurement_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function verify the end pattern is valid or invalid
///                     for trusted LL 
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions:
///
/// \input StatM_ucTimeCount_stack = STATM_CYCLES_IN_10S
/// \input ucPattern[4] : stack pattern
/// 
///
///   - Expectations:
/// \output ucPercent : percent for Thread
/// \output ucCount_Thread  state for Thread
///
//-----------------------------------------------------------------------------
void Mt_StatM__vStackSizeMeasurement_TestCase4(void)
{
    struct { uint8 ucPattern[4];                                                                                                   uint16 unPercent;              uint16 unCount_Thread;                   }asTestCaseData[]
        = { {{STATM_ENDOFSTACK_PATTERN_1, STATM_ENDOFSTACK_PATTERN_2, STATM_ENDOFSTACK_PATTERN_3, STATM_ENDOFSTACK_PATTERN_4} ,             0u,                                0u                          },
            {{STATM_ENDOFSTACK_PATTERN_1 - 1 , STATM_ENDOFSTACK_PATTERN_2, STATM_ENDOFSTACK_PATTERN_3, STATM_ENDOFSTACK_PATTERN_4} ,        STATM_STACK_INVALID,               STATM_STACK_INVALID         },
    };

    for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
    {
        for (uint8 ucI = 0; ucI < 4;ucI++)
        {
            //Step 2) Assign Input values
            ucTemp[RTE_THREAD_T_HH + RTE_THREAD_T_HL + RTE_THREAD_T_LH + ucI] = asTestCaseData[ucIdx].ucPattern[ucI];

        }
        StatM_ucTimeCount_stack = STATM_CYCLES_IN_10S;

        //Step 3) Call FUT
        StatM__vStackSizeMeasurement();

        //Step 4) Check expected output values
        AL_UNITTEST_CHECK(StatM_unUnusedStackTrusted_LL, asTestCaseData[ucIdx].unCount_Thread, == );
        AL_UNITTEST_CHECK(StatM_unUnusedStackTrusted_percent_LL, asTestCaseData[ucIdx].unPercent, == );
    }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_StatM__vStackSizeMeasurement_TestCase5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function verify the end pattern is valid or invalid
///                     for untrusted HH 
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions:
///
/// \input StatM_ucTimeCount_stack = STATM_CYCLES_IN_10S
/// \input ucPattern[4] : stack pattern
/// 
///
///   - Expectations:
/// \output ucPercent : percent for Thread
/// \output ucCount_Thread  state for Thread
///
//-----------------------------------------------------------------------------
void Mt_StatM__vStackSizeMeasurement_TestCase5(void)
{
    //Step 1: Set pre-conditions
    Rte_Write_StatM_StackUsage_HitCount = 0u;

    struct { uint8 ucPattern[4];                                                                                                   uint16 unPercent;              uint16 unCount_Thread;                   }asTestCaseData[]
        = { {{STATM_ENDOFSTACK_PATTERN_1, STATM_ENDOFSTACK_PATTERN_2, STATM_ENDOFSTACK_PATTERN_3, STATM_ENDOFSTACK_PATTERN_4} ,              0u,                                0u                         },
            {{STATM_ENDOFSTACK_PATTERN_1 - 1 , STATM_ENDOFSTACK_PATTERN_2, STATM_ENDOFSTACK_PATTERN_3, STATM_ENDOFSTACK_PATTERN_4} ,         STATM_STACK_INVALID,               STATM_STACK_INVALID        },
    };

    for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
    {
        for (uint8 ucI = 0; ucI < 4;ucI++)
        {
            //Step 2) Assign Input values
            ucTemp[RTE_THREAD_T_HH + RTE_THREAD_T_HL + RTE_THREAD_T_LH + RTE_THREAD_T_LL +ucI] = asTestCaseData[ucIdx].ucPattern[ucI];

        }
        StatM_ucTimeCount_stack = STATM_CYCLES_IN_10S;

        //Step 3) Call FUT
        StatM__vStackSizeMeasurement();

        //Step 4) Check expected output values
        AL_UNITTEST_CHECK(StatM_unUnusedStackUntrusted_HH, asTestCaseData[ucIdx].unCount_Thread, == );
        AL_UNITTEST_CHECK(StatM_unUnusedStackUntrusted_percent_HH, asTestCaseData[ucIdx].unPercent, == );
    }
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_StatM__vStackSizeMeasurement_TestCase6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function verify the end pattern is valid or invalid
///                     for untrusted HL 
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions:
///
/// \input StatM_ucTimeCount_stack = STATM_CYCLES_IN_10S
/// \input ucPattern[4] : stack pattern
/// 
///
///   - Expectations:
/// \output ucPercent : percent for Thread
/// \output ucCount_Thread  state for Thread
///
//-----------------------------------------------------------------------------
void Mt_StatM__vStackSizeMeasurement_TestCase6(void)
{
    //Step 1: Set pre-conditions
    
    Rte_Write_StatM_StackUsage_HitCount = 0u;

    struct { uint8 ucPattern[4];                                                                                                   uint16 unPercent;              uint16 unCount_Thread;                   }asTestCaseData[]
        = { {{STATM_ENDOFSTACK_PATTERN_1, STATM_ENDOFSTACK_PATTERN_2, STATM_ENDOFSTACK_PATTERN_3, STATM_ENDOFSTACK_PATTERN_4} ,              0u,                                0u                         },
            {{STATM_ENDOFSTACK_PATTERN_1 - 1 , STATM_ENDOFSTACK_PATTERN_2, STATM_ENDOFSTACK_PATTERN_3, STATM_ENDOFSTACK_PATTERN_4} ,         STATM_STACK_INVALID,               STATM_STACK_INVALID        },
    };

    for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
    {
        for (uint8 ucI = 0; ucI < 4;ucI++)
        {
            //Step 2) Assign Input values
            ucTemp[RTE_THREAD_T_HH + RTE_THREAD_T_HL + RTE_THREAD_T_LH + RTE_THREAD_T_LL+ RTE_THREAD_U_HH + ucI] = asTestCaseData[ucIdx].ucPattern[ucI];

        }
        StatM_ucTimeCount_stack = STATM_CYCLES_IN_10S;

        //Step 3) Call FUT
        StatM__vStackSizeMeasurement();

        //Step 4) Check expected output values
        AL_UNITTEST_CHECK(StatM_unUnusedStackUntrusted_HL, asTestCaseData[ucIdx].unCount_Thread, == );
        AL_UNITTEST_CHECK(StatM_unUnusedStackUntrusted_percent_HL, asTestCaseData[ucIdx].unPercent, == );
    }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_StatM__vStackSizeMeasurement_TestCase7
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function verify the end pattern is valid or invalid
///                     for untrusted LH 
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions:
///
/// \input StatM_ucTimeCount_stack = STATM_CYCLES_IN_10S
/// \input ucPattern[4] : stack pattern
/// 
///
///   - Expectations:
/// \output ucPercent : percent for Thread
/// \output ucCount_Thread  state for Thread
///
//-----------------------------------------------------------------------------
void Mt_StatM__vStackSizeMeasurement_TestCase7(void)
{
    //Step 1: Set pre-conditions

    Rte_Write_StatM_StackUsage_HitCount = 0u;

    struct { uint8 ucPattern[4];                                                                                                   uint16 unPercent;              uint16 unCount_Thread;                  }asTestCaseData[]
        = { {{STATM_ENDOFSTACK_PATTERN_1, STATM_ENDOFSTACK_PATTERN_2, STATM_ENDOFSTACK_PATTERN_3, STATM_ENDOFSTACK_PATTERN_4} ,             0u,                                0u                         },
            {{STATM_ENDOFSTACK_PATTERN_1 - 1 , STATM_ENDOFSTACK_PATTERN_2, STATM_ENDOFSTACK_PATTERN_3, STATM_ENDOFSTACK_PATTERN_4} ,        STATM_STACK_INVALID,               STATM_STACK_INVALID        },
    };

    for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
    {
        for (uint8 ucI = 0; ucI < 4;ucI++)
        {
            //Step 2) Assign Input values
            ucTemp[RTE_THREAD_T_HH + RTE_THREAD_T_HL + RTE_THREAD_T_LH + RTE_THREAD_T_LL + RTE_THREAD_U_HH + RTE_THREAD_U_HL+ ucI] = asTestCaseData[ucIdx].ucPattern[ucI];

        }
        StatM_ucTimeCount_stack = STATM_CYCLES_IN_10S;

        //Step 3) Call FUT
        StatM__vStackSizeMeasurement();

        //Step 4) Check expected output values
        AL_UNITTEST_CHECK(StatM_unUnusedStackUntrusted_LH, asTestCaseData[ucIdx].unCount_Thread, == );
        AL_UNITTEST_CHECK(StatM_unUnusedStackUntrusted_percent_LH, asTestCaseData[ucIdx].unPercent, == );
    }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_StatM__vStackSizeMeasurement_TestCase8
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function verify the end  pattern is valid or invalid
///                     for untrusted LL 
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions:
///
/// \input StatM_ucTimeCount_stack = STATM_CYCLES_IN_10S
/// \input ucPattern[4] : stack pattern
/// 
///
///   - Expectations:
/// \output ucPercent : percent for Thread
/// \output ucCount_Thread  state for Thread
///
//-----------------------------------------------------------------------------
void Mt_StatM__vStackSizeMeasurement_TestCase8(void)
{
    //Step 1: Set pre-conditions
    Rte_Write_StatM_StackUsage_HitCount = 0u;

    struct { uint8 ucPattern[4];                                                                                                   uint16 unPercent;              uint16 unCount_Thread;                   }asTestCaseData[]
        = { {{STATM_ENDOFSTACK_PATTERN_1, STATM_ENDOFSTACK_PATTERN_2, STATM_ENDOFSTACK_PATTERN_3, STATM_ENDOFSTACK_PATTERN_4} ,              0u,                                0u                         },
            {{STATM_ENDOFSTACK_PATTERN_1 - 1 , STATM_ENDOFSTACK_PATTERN_2, STATM_ENDOFSTACK_PATTERN_3, STATM_ENDOFSTACK_PATTERN_4} ,         STATM_STACK_INVALID,               STATM_STACK_INVALID        },
    };

    for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
    {
        for (uint8 ucI = 0; ucI < 4;ucI++)
        {
            //Step 2) Assign Input values
            ucTemp[RTE_THREAD_T_HH + RTE_THREAD_T_HL + RTE_THREAD_T_LH + RTE_THREAD_T_LL + RTE_THREAD_U_HH + RTE_THREAD_U_HL + RTE_THREAD_U_LH + ucI] = asTestCaseData[ucIdx].ucPattern[ucI];

        }
        StatM_ucTimeCount_stack = STATM_CYCLES_IN_10S;
        //Step 3) Call FUT
        StatM__vStackSizeMeasurement();

        //Step 4) Check expected output values
        AL_UNITTEST_CHECK(StatM_unUnusedStackUntrusted_LL, asTestCaseData[ucIdx].unCount_Thread, == );
        AL_UNITTEST_CHECK(StatM_unUnusedStackUntrusted_percent_LL, asTestCaseData[ucIdx].unPercent, == );
    }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_StatM__vStackSizeMeasurement_TestCase9
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function doesn't calculate stack size in case
///                      the time count was not reached
///
///    - Test Design Technique: ET (Expolratory Testing)
///
/// - Preconditions:
///
/// \input StatM_ucTimeCount_stack = 90u
/// \input StatM_unUnusedStackUntrusted_percent_LL = STATM_STACK_INVALID
///
///   - Expectations:
/// \output StatM_unUnusedStackUntrusted_percent_LL = STATM_STACK_INVALID
///
//-----------------------------------------------------------------------------
void Mt_StatM__vStackSizeMeasurement_TestCase9(void)
{
    //Step 1: Set pre-conditions
    //Step 2) Assign Input values
    StatM_ucTimeCount_stack = 90u;
    StatM_unUnusedStackUntrusted_percent_LL = STATM_STACK_INVALID;

    //Step 3) Call FUT
    StatM__vStackSizeMeasurement();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(StatM_unUnusedStackUntrusted_percent_LL, STATM_STACK_INVALID, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_riStatM_Init
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the init function reads stat from Nvm, increment the reset counter
///                     with limitation to max
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions:
///
/// \input unEcuReset : initial value for reset counter
/// \input StatM_stStat.unStepperSteploss = 0u
/// \input NvmBlockStatistics.sStatistics.unStepperSteploss = 10u
///
///   - Expectations:
///
/// \output unEcuReset_Output : reset counter value after init
/// \output StatM_stStat.unStepperSteploss = 10u
///
//-----------------------------------------------------------------------------
void Mt_riStatM_Init(void)
{
  //Step 1: Set pre-conditions

  struct { uint16 unEcuReset; uint16 unEcuReset_Output      }asTestCaseData[]
    = {  {          0u,                    1u,              },
         {        UINT16_MAX,          UINT16_MAX,          },
  };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {

    //Step 2) Assign Input values
    NvmBlockStatistics.sStatistics.unEcuReset = asTestCaseData[ucIdx].unEcuReset;
    StatM_stStat.unStepperSteploss = 0u;
    NvmBlockStatistics.sStatistics.unStepperSteploss = 10u;
    //Step 3) Call FUT
    riStatM_Init();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(StatM_stStat.unEcuReset, asTestCaseData[ucIdx].unEcuReset_Output, == );
    AL_UNITTEST_CHECK(StatM_stStat.unStepperSteploss, 10u, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_reStatM_ResetStatistics
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function call the function
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions:
///
/// \input test = { 10u }
/// \input NvM_WriteBlock_HitCount = 0u
/// \input NvM_WriteBlock_Param1 = 0u
///
///   - Expectations:
///
/// \output StatM_stStat.unEcuReset=0u
/// \output NvM_WriteBlock_HitCount = 8u
/// \output NvM_WriteBlock_Param1 = 0u
///
//-----------------------------------------------------------------------------
void Mt_reStatM_ResetStatistics(void)
{
  //Step 1: Set pre-conditions
  tstStatistics test = { 10u };

  //Step 2) Assign Input values
  NvM_WriteBlock_HitCount = 0u;
  NvM_WriteBlock_Param1 = 0u;
  StatM_stStat.unEcuReset = &test;

  //Step 3) Call FUT
  reStatM_ResetStatistics();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_WriteBlock_HitCount, 1u, == );
  AL_UNITTEST_CHECK(NvM_WriteBlock_Param1, 8u, == );
  AL_UNITTEST_CHECK(StatM_stStat.unEcuReset, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_rcStatM_Cycle10ms
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function runs the cycle behavior
///                     and increments the counters
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input StatM_boMeasureStack = TRUE
/// \input ucEcuOnTime = STATM_CYCLES_IN_1S
/// \input StatM_stStat.ulEcuOnTime = 0u
/// \input Rte_Read_CddLed_Status_Param1.aStatus[0u].Chn = eCddLed_ChnOn
/// \input ucLedOnTime[0u] = STATM_CYCLES_IN_1S
/// \input StatM_stStat.ulLedOnTime[0u] = 0u
/// \input Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[0u].unActVal = 1u
/// \input Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[0u].unActCurrent = 1u
/// \input ucFan1OnTime = STATM_CYCLES_IN_1S
/// \input StatM_stStat.ulFanOnTime[0u] = 0u
/// \input Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[1u].unActVal = 1u
/// \input Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[1u].unActCurrent = 1u
/// \input ucFan1OnTime = STATM_CYCLES_IN_1S
/// \input StatM_stStat.ulFanOnTime[1u] = 0u
/// \input Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError.boStepLoss = TRUE
/// \input StatM_boStepLoss = FALSE
/// \input StatM_stStat.unStepperSteploss = 0u
/// \input Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError.boIsMoving = TRUE
/// \input StatM_ucMoveTime = STATM_CYCLES_IN_1S
/// \input StatM_boWasMoving = FALSE
/// \input StatM_ucHoldTime = STATM_CYCLES_IN_1S
/// \input StatM_stStat.ulStepperHoldTime = UINT32_MAX
/// \input Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError = sStatusError_Tst;
/// \input StatM_stStat.unStepperFinishedUnsuccesfull = UINT16_MAX
/// \input StatM_stStat.ulStepperMoveTime = 0u
/// \input StatM_stStat.unStepperStarted = 0u
/// \input Rte_Read_RSens_PcbTemperature_Param1.eQty = SIG_VALID
/// \input Rte_Read_RSens_PcbTemperature_Param1.nVal = STATM_TEMP_130
/// \input Rte_Read_RSens_ThermzoneTemperatures_Param1.s16_NTCTemperatureCelsius[1u] = 15u
///
///   - Expectations:
///
/// \output StatM_stStat.ulEcuOnTime = 1u
/// \output StatM_stStat.ulLedOnTime[0u] = 1u
/// \output StatM_stStat.ulFanOnTime[0u] = 1u
/// \output StatM_stStat.ulFanOnTime[1u] = 1u
/// \output StatM_stStat.unStepperSteploss = 1u
/// \output StatM_stStat.ulStepperMoveTime = 1u
/// \output StatM_stStat.ulStepperHoldTime = UINT32_MAX
/// \output StatM_stStat.unStepperFinishedUnsuccesfull =UINT16_MAX
///
//-----------------------------------------------------------------------------
void Mt_rcStatM_Cycle10ms(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
    StatM_boMeasureStack = TRUE;

    ucEcuOnTime = STATM_CYCLES_IN_1S;
    StatM_stStat.ulEcuOnTime = 0u;

    Rte_Read_CddLed_Status_Param1.aStatus[0u].Chn = eCddLed_ChnOn;
    ucLedOnTime[0u] = STATM_CYCLES_IN_1S;
    StatM_stStat.ulLedOnTime[0u] = 0u;

    Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[0u].unActVal = 1u;
    Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[0u].unActCurrent = 1u;
    ucFan1OnTime = STATM_CYCLES_IN_1S;
    StatM_stStat.ulFanOnTime[0u] = 0u;
    Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[1u].unActVal = 1u;
    Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[1u].unActCurrent = 1u;
    ucFan1OnTime = STATM_CYCLES_IN_1S;
    StatM_stStat.ulFanOnTime[1u] = 0u;

    StatM_boStepLoss = FALSE;
    StatM_stStat.unStepperSteploss = 0u;
    StatM_ucMoveTime = STATM_CYCLES_IN_1S;
    StatM_boWasMoving = FALSE;
    StatM_ucHoldTime = STATM_CYCLES_IN_1S;
    StatM_stStat.ulStepperHoldTime = UINT32_MAX;
    tisStpStatusError sStatusError_Tst = { SUPPORT_YES, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, 0U, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
    Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError = sStatusError_Tst;
    StatM_stStat.unStepperFinishedUnsuccesfull = UINT16_MAX;
    StatM_stStat.ulStepperMoveTime = 0u;
    StatM_stStat.unStepperStarted = 0u;

    Rte_Read_RSens_PcbTemperature_Param1.eQty = SIG_VALID;
    Rte_Read_RSens_PcbTemperature_Param1.nVal = STATM_TEMP_130;
    Rte_Read_RSens_ThermzoneTemperatures_Param1.s16_NTCTemperatureCelsius[1u] = 15u;

    //Step 3) Call FUT
    rcStatM_Cycle10ms();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(StatM_stStat.ulEcuOnTime, 1u, == );
    AL_UNITTEST_CHECK(StatM_stStat.ulLedOnTime[0u], 1u, == );
    AL_UNITTEST_CHECK(StatM_stStat.ulFanOnTime[0u], 1u, == );
    AL_UNITTEST_CHECK(StatM_stStat.ulFanOnTime[1u], 0u, == );
    AL_UNITTEST_CHECK(StatM_stStat.unStepperSteploss, 0u, == );
    AL_UNITTEST_CHECK(StatM_stStat.ulStepperMoveTime, 1u, == );
    AL_UNITTEST_CHECK(StatM_stStat.unStepperStarted, 1u, == );
    AL_UNITTEST_CHECK(StatM_stStat.ulStepperHoldTime, UINT32_MAX, == );
    AL_UNITTEST_CHECK(StatM_stStat.unStepperFinishedUnsuccesfull, UINT16_MAX, == );
  
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_StatM_ReadStatistics
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the function handles the statistics from NvM or Local Variable 
///
///    - Test Design Technique: ET (Exploratory Testing), DT (Decision Table)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_StatM_ReadStatistics(void)
{
    Mt_StatM_ReadStatistics_TestCase1();
    Mt_StatM_ReadStatistics_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_StatM__boCheckPatern
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the function handles the pattern
///
///    - Test Design Technique: ET (Exploratory Testing), DT (Decision Table)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_StatM__boCheckPatern(void)
{
    Mt_StatM__boCheckPatern_TestCase1();
    Mt_StatM__boCheckPatern_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_StatM__unGetNumberFreeBytes
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the function handles the number of free bytes
///
///    - Test Design Technique: ET (Exploratory Testing), DT (Decision Table)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_StatM__unGetNumberFreeBytes(void)
{
    Mt_StatM__unGetNumberFreeBytes_TestCase1();
    Mt_StatM__unGetNumberFreeBytes_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_StatM__vStackSizeMeasurement
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the function handles the stack size 
///
///    - Test Design Technique: ET (Exploratory Testing), DT (Decision Table)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_StatM__vStackSizeMeasurement(void)
{
     Mt_StatM__vStackSizeMeasurement_TestCase1();
     Mt_StatM__vStackSizeMeasurement_TestCase2();
     Mt_StatM__vStackSizeMeasurement_TestCase3();
     Mt_StatM__vStackSizeMeasurement_TestCase4();
     Mt_StatM__vStackSizeMeasurement_TestCase5();
     Mt_StatM__vStackSizeMeasurement_TestCase6();
     Mt_StatM__vStackSizeMeasurement_TestCase7();
     Mt_StatM__vStackSizeMeasurement_TestCase8();
     Mt_StatM__vStackSizeMeasurement_TestCase9();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_StatM__vErrorCountersProcessing
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the function handles the error
///
///    - Test Design Technique: ET (Exploratory Testing),DT (Decision Table)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_StatM__vErrorCountersProcessing(void)
{
    Mt_StatM__vErrorCountersProcessing_TestCase1();
    Mt_StatM__vErrorCountersProcessing_TestCase2();
    Mt_StatM__vErrorCountersProcessing_TestCase3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_reStatM_Deinit
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function deinitialization of statM module
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions:
///
/// \input StatM_stStat = sStatM
/// \input NvmBlockStatistics.sStatistics.unEcuReset = 10u
///
///   - Expectations:
///
/// \output NvmBlockStatistics.sStatistics.unEcuReset = 0u
///
//-----------------------------------------------------------------------------
void Mt_reStatM_Deinit(void)
{
  //Step 1: Set pre-conditions
 //Step 2) Assign Input values
  NvmBlockStatistics.sStatistics.unEcuReset = 10u;

  tstStatistics sStatM = { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
  memcpy(&StatM_stStat, &sStatM, sizeof(tstStatistics));

  //Step 3) Call FUT
  reStatM_Deinit();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvmBlockStatistics.sStatistics.unEcuReset, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_StatM__vStpTimeProcessing
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the function handles the stepper
///
///    - Test Design Technique: ET (Exploratory Testing),DT (Decision Table)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_StatM__vStpTimeProcessing(void)
{
      Mt_StatM__vStpTimeProcessing_TestCase1();
      Mt_StatM__vStpTimeProcessing_TestCase2();
      Mt_StatM__vStpTimeProcessing_TestCase3();
      Mt_StatM__vStpTimeProcessing_TestCase4();
      Mt_StatM__vStpTimeProcessing_TestCase5();
      Mt_StatM__vStpTimeProcessing_TestCase6();
      Mt_StatM__vStpTimeProcessing_TestCase7();
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
  /// StatM.c
  ALUnitTest_AddFunction("Mt_StatM__vEcuTimeProcessing", Mt_StatM__vEcuTimeProcessing);
  ALUnitTest_AddFunction("Mt_StatM__vLedTimeProcessing", Mt_StatM__vLedTimeProcessing);
  ALUnitTest_AddFunction("Mt_StatM__vTempClassProcessing", Mt_StatM__vTempClassProcessing);
  ALUnitTest_AddFunction("Mt_StatM__vErrorCountersProcessing", Mt_StatM__vErrorCountersProcessing);
  ALUnitTest_AddFunction("Mt_StatM__vFanTimeProcessing", Mt_StatM__vFanTimeProcessing);
  ALUnitTest_AddFunction("Mt_StatM__vStpTimeProcessing", Mt_StatM__vStpTimeProcessing);
  ALUnitTest_AddFunction("Mt_StatM__vTempTimeProcessing", Mt_StatM__vTempTimeProcessing);
  ALUnitTest_AddFunction("Mt_StatM_ReadStatistics", Mt_StatM_ReadStatistics);
  ALUnitTest_AddFunction("Mt_StatM_WriteStatistics", Mt_StatM_WriteStatistics);
  ALUnitTest_AddFunction("Mt_StatM_ResetStatistics", Mt_StatM_ResetStatistics);
  ALUnitTest_AddFunction("Mt_StatM_Deinit", Mt_StatM_Deinit);
  ALUnitTest_AddFunction("Mt_StatM__boCheckPatern", Mt_StatM__boCheckPatern);
  ALUnitTest_AddFunction("Mt_StatM__unGetNumberFreeBytes", Mt_StatM__unGetNumberFreeBytes);
  ALUnitTest_AddFunction("Mt_StatM__vStackSizeMeasurement", Mt_StatM__vStackSizeMeasurement);
  ALUnitTest_AddFunction("Mt_StatM_Cycle0", Mt_StatM_Cycle0);
  ALUnitTest_AddFunction("Mt_StatM_Init", Mt_StatM_Init);

  /// ctaaStatM.c
  ALUnitTest_AddFunction("Mt_riStatM_Init", Mt_riStatM_Init);
  ALUnitTest_AddFunction("Mt_reStatM_Deinit", Mt_reStatM_Deinit);
  ALUnitTest_AddFunction("Mt_rcStatM_Cycle10ms", Mt_rcStatM_Cycle10ms);
  ALUnitTest_AddFunction("Mt_reStatM_ResetStatistics", Mt_reStatM_ResetStatistics);
  
}
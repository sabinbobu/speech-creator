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
/// \file  StatM.c
///
/// \brief Statistic Manager SWC
///
/// \descr StatM is responsible for
///
///        read, update and write Statistic data in NvM
///        Perform Diagnostic Requests of Read and Reset statistics
///
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================
#include <Swc/StatM/StatM.h>
#include <Swc/StatM/ctaaStatM.h>
#include <Cfg/Cfg.h>

#ifndef UNIT_TEST
//lint -e451 Header file repeatedly included but does not have a standard include guard
#include <Rte.h>
#include <Os_MemMap.h>
#else
#include <RteCommonTypes.h>
#include <../CddLed/Api/CddLed.h>
#include <../CddBoost/Api/CddBoost.h>
#endif

//lint +e451 Header file repeatedly included but does not have a standard include guard

//=============================================================================
// defines
//=============================================================================


// cycle time is 10ms, so 100cycles is 1 second
#define STATM_CYCLES_IN_1S   10u
#define STATM_CYCLES_IN_10S 100u
#define STATM_DELAY_500MS   5u
//#define STATM_LED_CHN        ((CFG_LED_CHANNELS_NR <= STATM_MAX_LED_CHN) ? CFG_LED_CHANNELS_NR : STATM_MAX_LED_CHN)
#define STATM_TEMP_0           0
#define STATM_TEMP_70        700
#define STATM_TEMP_90        900
#define STATM_TEMP_110      1100
#define STATM_TEMP_130      1300

#ifdef CFG_VARIANT_FULL
#define STATM_ZONES     12u
#define STATM_LED_CHN   12u
#else
//#define STATM_ZONES      4u
#define STATM_ZONES     12u
#define STATM_LED_CHN    4u
#endif

#define STATM_ENDOFSTACK_PATTERN_1   0xA5u
#define STATM_ENDOFSTACK_PATTERN_2   0x2Eu
#define STATM_ENDOFSTACK_PATTERN_3   0x5Au
#define STATM_ENDOFSTACK_PATTERN_4   0xE2u
#define STATM_NOTUSEDSTACK_PATTERN   0xCCu


#define STATM_STACK_INIT     0xFFFFu
#define STATM_STACK_INVALID  0xFFFEu
#define STATM_STACK_CYCLE    STATM_CYCLES_IN_1S


//=============================================================================
// variables
//=============================================================================

STATIC_AL tstStatistics StatM_stStat;

STATIC_AL volatile boolean StatM_boMeasureStack                    = TRUE;
STATIC_AL volatile uint16 StatM_unUnusedStackTrusted_HH            = STATM_STACK_INIT;
STATIC_AL volatile uint16 StatM_unUnusedStackUntrusted_HH          = STATM_STACK_INIT;
STATIC_AL volatile uint16 StatM_unUnusedStackTrusted_percent_HH    = STATM_STACK_INIT;
STATIC_AL volatile uint16 StatM_unUnusedStackUntrusted_percent_HH  = STATM_STACK_INIT;
STATIC_AL volatile uint16 StatM_unUnusedStackTrusted_HL            = STATM_STACK_INIT;
STATIC_AL volatile uint16 StatM_unUnusedStackUntrusted_HL          = STATM_STACK_INIT;
STATIC_AL volatile uint16 StatM_unUnusedStackTrusted_percent_HL    = STATM_STACK_INIT;
STATIC_AL volatile uint16 StatM_unUnusedStackUntrusted_percent_HL  = STATM_STACK_INIT;
STATIC_AL volatile uint16 StatM_unUnusedStackTrusted_LH            = STATM_STACK_INIT;
STATIC_AL volatile uint16 StatM_unUnusedStackUntrusted_LH          = STATM_STACK_INIT;
STATIC_AL volatile uint16 StatM_unUnusedStackTrusted_percent_LH    = STATM_STACK_INIT;
STATIC_AL volatile uint16 StatM_unUnusedStackUntrusted_percent_LH  = STATM_STACK_INIT;
STATIC_AL volatile uint16 StatM_unUnusedStackTrusted_LL            = STATM_STACK_INIT;
STATIC_AL volatile uint16 StatM_unUnusedStackUntrusted_LL          = STATM_STACK_INIT;
STATIC_AL volatile uint16 StatM_unUnusedStackTrusted_percent_LL    = STATM_STACK_INIT;
STATIC_AL volatile uint16 StatM_unUnusedStackUntrusted_percent_LL  = STATM_STACK_INIT;

//static uint8  StatM_ucCycle                = STATM_CYCLES_IN_1S;  // to be replaced by #define STATM_STACK_CYCLE after value is fixed.

//=============================================================================
// functions
//=============================================================================

STATIC_AL void StatM__vEcuTimeProcessing(void);
STATIC_AL void StatM__vLedTimeProcessing(void);
#ifdef CFG_VARIANT_FULL
STATIC_AL void StatM__vStpTimeProcessing(void);
#endif
STATIC_AL void StatM__vFanTimeProcessing(void);
STATIC_AL void StatM__vTempTimeProcessing(void);
STATIC_AL void StatM__vTempClassProcessing(tsRte_PcbTemperatureMsg sTemp, uint8 *ucTempTime, uint32 *ulStatTempTime);
STATIC_AL void StatM__vErrorCountersProcessing(void);

STATIC_AL void StatM__vStackSizeMeasurement(void);
STATIC_AL boolean StatM__boCheckPatern(uint32 ulAddress);
STATIC_AL uint16 StatM__unGetNumberFreeBytes(uint32 ulStartAdd, uint32 ulEndAdd);

STATIC_AL void StatM_WriteStatistics(void);

//-----------------------------------------------------------------------------
/// \brief  StatM_Init
///
/// \descr  Initialize StatM module
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void StatM_Init(void)
{
	 // read stat from nvm
  (void)memcpy(&StatM_stStat, &NvmBlockStatistics.sStatistics, sizeof(tstStatistics));
	 // increment the reset counter with limitation to max
  StatM_stStat.unEcuReset = (StatM_stStat.unEcuReset < (uint16)UINT16_MAX) ? StatM_stStat.unEcuReset + 1u : (uint16)UINT16_MAX;

  //Reason: Save reset occurence in Nvm and not wait for a shutdown of ECU (otherwise consecutive resets will not be recorded)
  StatM_WriteStatistics();
}


//-----------------------------------------------------------------------------
/// \brief  StatM_Cycle0
///
/// \descr  Cyclic processing of StatM module
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void StatM_Cycle0(void)
{
	// increment the cyclic time counters
    StatM__vEcuTimeProcessing();
    StatM__vLedTimeProcessing();
    StatM__vErrorCountersProcessing();
#if defined CFG_VARIANT_FULL || defined(UNIT_TEST)
    StatM__vStpTimeProcessing();
#endif
    StatM__vFanTimeProcessing();
    StatM__vTempTimeProcessing();

    if (StatM_boMeasureStack == TRUE)
    {
        StatM__vStackSizeMeasurement();
    }
} // PRQA S 5324 1 // design

//-----------------------------------------------------------------------------
/// \brief  StatM_Deinit
///
/// \descr  Deinitialization of StatM module
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void StatM_Deinit(void)
{
    (void)memcpy(&NvmBlockStatistics.sStatistics, &StatM_stStat, sizeof(tstStatistics));
}

//-----------------------------------------------------------------------------
/// \brief  StatM_ResetStatistics
///
/// \descr  Reset all statistics to value 0
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void StatM_ResetStatistics(void)
{
	 // reset all stats to 0
  (void)memset(&StatM_stStat, 0, sizeof(tstStatistics));
  StatM_WriteStatistics();
}

//-----------------------------------------------------------------------------
/// \brief  StatM_ResetStatistics
///
/// \descr  provide the statistics from NvM or Local Variable
///
/// \param  tstStatistics *pstStats: adress to store the Statistics
///         boolean boFromNvM: TRUE: read from NVM
///                            FALSE: read from Local Variable
///
/// \return void
//-----------------------------------------------------------------------------
void StatM_ReadStatistics(tstStatistics *pstStats, boolean boFromNvM)
{
	 //store in parameter the Statistics from NvM or Local based on flag
  (void)memcpy(pstStats, ((boFromNvM == STATM_READ_FROM_NVM) ? (&NvmBlockStatistics.sStatistics) : (&StatM_stStat)), sizeof(tstStatistics));
}

//-----------------------------------------------------------------------------
/// \brief  StatM_WriteStatistics
///
/// \descr  Write statistics to NvM
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void StatM_WriteStatistics(void)
{
  // write Stats to NvM
  // as info: all blocks are stored in NvM before shutdown in EcuM_ShutDownPrep_HandleTransitions();
  (void)memcpy(&NvmBlockStatistics.sStatistics, &StatM_stStat, sizeof(tstStatistics));
  (void)NvM_WriteBlock((NvM_BlockIdType)NvmBlockStatisticsId, &NvmBlockStatistics);
}



STATIC_AL void StatM__vEcuTimeProcessing(void)
{
    // increment cyclic time counter for ECU ON time
    STATIC_UT(uint8, ucEcuOnTime, 0u);

    ucEcuOnTime++;

    if (ucEcuOnTime >= STATM_CYCLES_IN_1S)
    {
        ucEcuOnTime = 0u;
        StatM_stStat.ulEcuOnTime = (StatM_stStat.ulEcuOnTime < UINT32_MAX) ? StatM_stStat.ulEcuOnTime + 1u : UINT32_MAX;
    }
}

STATIC_AL void StatM__vLedTimeProcessing(void)
{
    // increment cyclic time counter for LED ON time
#ifdef CFG_VARIANT_FULL
    static uint8 ucLedOnTime[STATM_LED_CHN] = { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
#else
  STATIC_UT(uint8, ucLedOnTime[STATM_LED_CHN], { 0u });
#endif
    tCddLedStatus sLedStatus;
    uint8 ucI;

    (void)Rte_Read_CddLed_Status(&sLedStatus);

    for (ucI = 0u; ucI < STATM_LED_CHN; ucI++)
    {
        if (sLedStatus.aStatus[ucI].Chn == eCddLed_ChnOn)
        {
            ucLedOnTime[ucI]++;
            if (ucLedOnTime[ucI] >= STATM_CYCLES_IN_1S)
            {
                ucLedOnTime[ucI] = 0u;
                StatM_stStat.ulLedOnTime[ucI] = (StatM_stStat.ulLedOnTime[ucI] < UINT32_MAX) ? StatM_stStat.ulLedOnTime[ucI] + 1u : UINT32_MAX;
            }
        }
    }
}

STATIC_AL void StatM__vFanTimeProcessing(void)
{
    // increment cyclic time counter for FAN ON time
  STATIC_UT(uint8, ucFan1OnTime, 0u);
  STATIC_UT(uint8, ucFan2OnTime, 0u);
    tsRte_HssStatus sHssStatus;
    uint8 ucI;

    
    (void)Rte_Read_CddSwi_SwitchStatus(&sHssStatus);

    if (sHssStatus.sSwitchStatus[0u].unActVal > 0u && sHssStatus.sSwitchStatus[0u].unActCurrent > 0u)
    {
        ucFan1OnTime++;
        if (ucFan1OnTime >= STATM_CYCLES_IN_1S)
        {
            ucFan1OnTime = 0u;
            StatM_stStat.ulFanOnTime[0u] = (StatM_stStat.ulFanOnTime[0u] < UINT32_MAX) ? StatM_stStat.ulFanOnTime[0u] + 1u : UINT32_MAX;
        }
    }
#if defined (CFG_VARIANT_FULL)  || defined (UNIT_TEST)
    if (sHssStatus.sSwitchStatus[1u].unActVal > 0u && sHssStatus.sSwitchStatus[1u].unActCurrent > 0u)
    {
        ucFan2OnTime++;
        if (ucFan2OnTime >= STATM_CYCLES_IN_1S)
        {
            ucFan2OnTime = 0u;
            StatM_stStat.ulFanOnTime[1u] = (StatM_stStat.ulFanOnTime[1u] < UINT32_MAX) ? StatM_stStat.ulFanOnTime[1u] + 1u : UINT32_MAX;
        }
    }
#endif
}

#if defined (CFG_VARIANT_FULL)  || defined (UNIT_TEST)

STATIC_AL void StatM__vStpTimeProcessing(void)
{
     STATIC_UT(uint8, StatM_ucMoveTime, 0u);
     STATIC_UT(uint8, StatM_ucHoldTime, 0u);
     STATIC_UT(boolean, StatM_boStepLoss, FALSE);
     STATIC_UT(boolean, StatM_boWasMoving, FALSE);

    tsRte_CddStpActual sStp;

    (void)Rte_Read_ppCddStpActual0_sStpActualValues(&sStp);

    //  no steploss before          and    steploss is detected
    if ((StatM_boStepLoss == FALSE) && (sStp.sLwrActual.sStatusError.boStepLoss == TRUE))
    {
        // increment the counter
        StatM_stStat.unStepperSteploss = (StatM_stStat.unStepperSteploss < (uint16)UINT16_MAX) ? StatM_stStat.unStepperSteploss + 1u : (uint16)UINT16_MAX;
    }
    // save the new value for usage in next cycle
    StatM_boStepLoss = sStp.sLwrActual.sStatusError.boStepLoss;

    if (sStp.sLwrActual.sStatusError.boIsMoving == TRUE)
    {
        // stepper is moving
        StatM_ucMoveTime++;
        if (StatM_ucMoveTime >= STATM_CYCLES_IN_1S)
        {
            // increment the moving time counter
            StatM_ucMoveTime = 0u;
            StatM_stStat.ulStepperMoveTime = (StatM_stStat.ulStepperMoveTime < UINT32_MAX) ? StatM_stStat.ulStepperMoveTime + 1u : UINT32_MAX;
        }

        if (StatM_boWasMoving == FALSE)
        {
            // transition from not moving to moving, aka started to move
            // increment the counter
            StatM_boWasMoving = TRUE;
            StatM_stStat.unStepperStarted = (StatM_stStat.unStepperStarted < (uint16)UINT16_MAX) ? StatM_stStat.unStepperStarted + 1u : (uint16)UINT16_MAX;
        }
    }
    else
    {
        // stepper is not moving
        StatM_ucHoldTime++;
        if (StatM_ucHoldTime >= STATM_CYCLES_IN_1S)
        {
            // increment the hold counter
            StatM_ucHoldTime = 0u;
            StatM_stStat.ulStepperHoldTime = (StatM_stStat.ulStepperHoldTime < UINT32_MAX) ? StatM_stStat.ulStepperHoldTime + 1u : UINT32_MAX;
        }

        if (StatM_boWasMoving == TRUE)
        {
            // transition from moving to not moving, aka stopped moving
            StatM_boWasMoving = FALSE;
            // if an error is detected, consider it was finished unsuccesfull
            if ((sStp.sLwrActual.sStatusError.boIsFatalError   == TRUE) ||
                (sStp.sLwrActual.sStatusError.boStepLoss       == TRUE) ||
                (sStp.sLwrActual.sStatusError.boCommDefect     == TRUE) ||
                (sStp.sLwrActual.sStatusError.boElecOL         == TRUE) ||
                (sStp.sLwrActual.sStatusError.boElecSC         == TRUE) ||
                (sStp.sLwrActual.sStatusError.boVoltUSSM       == TRUE) ||
                (sStp.sLwrActual.sStatusError.boVoltOver       == TRUE) ||
                (sStp.sLwrActual.sStatusError.boOverTempShtDwn == TRUE))
            {
                StatM_stStat.unStepperFinishedUnsuccesfull = (StatM_stStat.unStepperFinishedUnsuccesfull < (uint16)UINT16_MAX) ? StatM_stStat.unStepperFinishedUnsuccesfull + 1u : (uint16)UINT16_MAX;
            }
        }
    }
}
#endif

STATIC_AL void StatM__vTempTimeProcessing(void)
{
    // increment cyclic time counter for Temperature Zones and PCB in each Temperature Class
    STATIC_UT(uint8, ucTempPCBTime[STATM_TEMP_CLASSES], { 0u });
    STATIC_UT(uint8, ucTempZoneTime[STATM_ZONES][STATM_TEMP_CLASSES], { 0u });

    tsRte_PcbTemperatureMsg sTempPCB;
    tsRte_PcbTemperatureMsg sTempConvert;
    tsRte_NTCTemperature sTemp;
    uint8 ucI = 0u;

    (void)Rte_Read_RSens_PcbTemperature(&sTempPCB);
    (void)Rte_Read_RSens_ThermzoneTemperatures(&sTemp);

    StatM__vTempClassProcessing(sTempPCB, ucTempPCBTime, StatM_stStat.ulPCBTempTime);

    for (ucI = 0u; ucI < STATM_ZONES; ucI++)
    {
        //helper conversion to be able to use StatM_vTempClassProcessing
        sTempConvert.eQty = sTemp.eSigQty[ucI];
        sTempConvert.nVal = sTemp.s16_NTCTemperatureCelsius[ucI];
        StatM__vTempClassProcessing(sTempConvert, ucTempZoneTime[ucI], StatM_stStat.ulTempZoneTime[ucI]);
    }
}

STATIC_AL void StatM__vTempClassProcessing(tsRte_PcbTemperatureMsg sTemp, uint8 *ucTempTime, uint32 *ulStatTempTime)
{
    uint8 ucI = 0u;

    if (sTemp.eQty == SIG_VALID)
    {
      //if      (sTemp.nVal <= STATM_TEMP_0  ) { ucI = 0u; }
      //else if (sTemp.nVal <= STATM_TEMP_70 ) { ucI = 1u; }
      //else if (sTemp.nVal <= STATM_TEMP_90 ) { ucI = 2u; }
      //else if (sTemp.nVal <= STATM_TEMP_110) { ucI = 3u; }
      //else if (sTemp.nVal <= STATM_TEMP_130) { ucI = 4u; }
      //else                                   { ucI = 5u; }
      //optimize STMIF for the above
      ucI = 5u;
      if (sTemp.nVal <= STATM_TEMP_130) { ucI = 4u; };
      if (sTemp.nVal <= STATM_TEMP_110) { ucI = 3u; };
      if (sTemp.nVal <= STATM_TEMP_90)  { ucI = 2u; };
      if (sTemp.nVal <= STATM_TEMP_70)  { ucI = 1u; };
      if (sTemp.nVal <= STATM_TEMP_0)   { ucI = 0u; };

      ucTempTime[ucI]++;

      if (ucTempTime[ucI] >= STATM_CYCLES_IN_1S)
      {
          ucTempTime[ucI] = 0u;
          ulStatTempTime[ucI] = (ulStatTempTime[ucI] < UINT32_MAX) ? ulStatTempTime[ucI] + 1u : UINT32_MAX;
      }
    }
}

STATIC_AL void StatM__vErrorCountersProcessing(void)
{
    static uint8 ucVboostDelay = 0U;
    uint8 ucI;
    tCddLedStatus sLedStatus;
    tsRte_LedStates sLedState;
    tCddBoostStatus sBoostStatus;
    static boolean StatM_boBuck_TW[6] = { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
    static boolean StatM_boBuck_TSD[6] = { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
    static boolean StatM_boBooster_TW = FALSE;
    static boolean StatM_boBooster_TSD = FALSE;
    static boolean StatM_boBooster_UV = FALSE;

    (void)Rte_Read_CddLed_Status(&sLedStatus);
    (void)Rte_Read_CddLed_LedState(&sLedState);
    (void)Rte_Read_CddBoost_BoostStatus(&sBoostStatus);

    for (ucI = 0u; ucI < STATM_NR_BUCKS; ucI++)
    {
        if ((sLedStatus.aStatus[ucI * 2u].TempData.boThermalWarning == TRUE)            && (StatM_stStat.unBuck_TW[ucI]  < (uint16)UINT16_MAX) && (StatM_boBuck_TW[ucI]  == FALSE)) { StatM_stStat.unBuck_TW[ucI]++;  StatM_boBuck_TW[ucI]  = TRUE;} else { StatM_boBuck_TW[ucI] = FALSE;  }
        if ((sLedState.aLedStates[ucI * 2u].eLedErrStatus == eRteCddLed_ErrThermShutdn) && (StatM_stStat.unBuck_TSD[ucI] < (uint16)UINT16_MAX) && (StatM_boBuck_TSD[ucI] == FALSE)) { StatM_stStat.unBuck_TSD[ucI]++; StatM_boBuck_TSD[ucI] = TRUE;} else { StatM_boBuck_TSD[ucI] = FALSE; }
    }
    if ((sBoostStatus.aboThermalWarning[0] == TRUE)            && (StatM_stStat.unBooster_TW           < (uint16)UINT16_MAX) && (StatM_boBooster_TW  == FALSE)) { StatM_stStat.unBooster_TW++;           StatM_boBooster_TW  = TRUE; } else {StatM_boBooster_TW  = FALSE; }
    if ((sBoostStatus.aStatus[0] == eCddBoost_ErrThermShutdn)  && (StatM_stStat.unBooster_TSD          < (uint16)UINT16_MAX) && (StatM_boBooster_TSD == FALSE)) { StatM_stStat.unBooster_TSD++;          StatM_boBooster_TSD = TRUE; } else {StatM_boBooster_TSD = FALSE; }
    
    if (ucVboostDelay >= STATM_DELAY_500MS)
    {
      if ((sLedState.aLedStates[0].boVinBoostOk == FALSE) && (StatM_stStat.unBooster_VBoostUV_Err < (uint16)UINT16_MAX) && (StatM_boBooster_UV == FALSE)) { StatM_stStat.unBooster_VBoostUV_Err++; StatM_boBooster_UV = TRUE; }
      else { StatM_boBooster_UV = FALSE; }
    }
    else
    {
      ucVboostDelay++;
    }
 // StatM_stStat.unBooster_TempOut         are not used, see LDMO-2554
 // StatM_stStat.unBooster_BoostOV         are not used, see LDMO-2554
 // StatM_stStat.unBooster_VBSTDIV_UV      are not used, see LDMO-2554
 // StatM_stStat.unBooster_VBSTDRIVE_NOK   are not used, see LDMO-2554
 // StatM_stStat.unBooster_VBoostOV_Err    are not used, see LDMO-2554

} //PRQA S 5310 1 // design and readability


STATIC_AL boolean StatM__boCheckPatern(uint32 ulAddress)
{
    boolean boRes;

    // PRQA S 303 5 // Memory access is needed here by design.
    // PRQA S 306 4 // Memory access is needed here by design.
    if (((uint8)(*(const volatile uint8*)(ulAddress))      == (uint8)STATM_ENDOFSTACK_PATTERN_1) &&
        ((uint8)(*(const volatile uint8*)(ulAddress + 1u)) == (uint8)STATM_ENDOFSTACK_PATTERN_2) &&
        ((uint8)(*(const volatile uint8*)(ulAddress + 2u)) == (uint8)STATM_ENDOFSTACK_PATTERN_3) &&
        ((uint8)(*(const volatile uint8*)(ulAddress + 3u)) == (uint8)STATM_ENDOFSTACK_PATTERN_4))
    {
        boRes = TRUE;
    }
    else
    {
        boRes = FALSE;
    }

    return boRes;
}

STATIC_AL uint16 StatM__unGetNumberFreeBytes(uint32 ulStartAdd, uint32 ulEndAdd)
{
    uint16 unNumberBytes = 0;
    // PRQA S 303 3 // Memory access is needed here by design.
    // PRQA S 306 2 // Memory access is needed here by design.
    while ((ulStartAdd < (uint32)ulEndAdd) &&
        ((uint8)(*(const volatile uint8*)(ulStartAdd)) == (uint8)STATM_NOTUSEDSTACK_PATTERN))
    {
        unNumberBytes++;
        ulStartAdd++;
    }

    return unNumberBytes;
}

STATIC_AL void StatM__vStackSizeMeasurement(void)
{
    STATIC_UT(uint8, StatM_ucTimeCount_stack, 0u);
    uint32 ulUnusedStack = 0u;
    uint8 ucTotalStackUsePercentage = 0u;

    StatM_ucTimeCount_stack++;

    if (StatM_ucTimeCount_stack >= STATM_CYCLES_IN_10S)
    {
        // one second passed
        StatM_ucTimeCount_stack = 0;

#if (RTE_THREAD_T_HH > 0u)
        // calculate stack size trusted HH
        if (StatM__boCheckPatern(STATM_STACK_T_HH_END) == TRUE)
        {
            // end pattern is valid
            StatM_unUnusedStackTrusted_HH = StatM__unGetNumberFreeBytes((STATM_STACK_T_HH_END + 4u), STATM_STACK_T_HH_START);
            ulUnusedStack += StatM_unUnusedStackTrusted_HH;
            StatM_unUnusedStackTrusted_percent_HH = (uint16)((uint32)((uint32)StatM_unUnusedStackTrusted_HH * 1000u) / ((uint32)STATM_STACK_T_HH_SIZE - 4u));
        }
        else
        {
            // end pattern is not valid
            StatM_unUnusedStackTrusted_HH = STATM_STACK_INVALID;
            StatM_unUnusedStackTrusted_percent_HH = STATM_STACK_INVALID;
        }
#endif

#if (RTE_THREAD_T_HL > 0u)
        // calculate stack size trusted HL
        if (StatM__boCheckPatern(STATM_STACK_T_HL_END) == TRUE)
        {
            // end pattern is valid
            StatM_unUnusedStackTrusted_HL = StatM__unGetNumberFreeBytes((STATM_STACK_T_HL_END + 4u), STATM_STACK_T_HL_START);
            ulUnusedStack += StatM_unUnusedStackTrusted_HL;
            StatM_unUnusedStackTrusted_percent_HL = (uint16)((uint32)((uint32)StatM_unUnusedStackTrusted_HL * 1000u) / ((uint32)STATM_STACK_T_HL_SIZE - 4u));
        }
        else
        {
            // end pattern is not valid
            StatM_unUnusedStackTrusted_HL = STATM_STACK_INVALID;
            StatM_unUnusedStackTrusted_percent_HL = STATM_STACK_INVALID;
        }
#endif

#if (RTE_THREAD_T_LH > 0u)
        // calculate stack size trusted LH
        if (StatM__boCheckPatern(STATM_STACK_T_LH_END) == TRUE)
        {
            // end pattern is valid
            StatM_unUnusedStackTrusted_LH = StatM__unGetNumberFreeBytes((STATM_STACK_T_LH_END + 4u), STATM_STACK_T_LH_START);
            ulUnusedStack += StatM_unUnusedStackTrusted_LH;
            StatM_unUnusedStackTrusted_percent_LH = (uint16)((uint32)((uint32)StatM_unUnusedStackTrusted_LH * 1000u) / ((uint32)STATM_STACK_T_LH_SIZE - 4u));
        }
        else
        {
            // end pattern is not valid
            StatM_unUnusedStackTrusted_LH = STATM_STACK_INVALID;
            StatM_unUnusedStackTrusted_percent_LH = STATM_STACK_INVALID;
        }
#endif

#if (RTE_THREAD_T_LL > 0u)
        // calculate stack size trusted LL
        if (StatM__boCheckPatern(STATM_STACK_T_LL_END) == TRUE)
        {
            // end pattern is valid
            StatM_unUnusedStackTrusted_LL = StatM__unGetNumberFreeBytes((STATM_STACK_T_LL_END + 4u), STATM_STACK_T_LL_START);
            ulUnusedStack += StatM_unUnusedStackTrusted_LL;
            StatM_unUnusedStackTrusted_percent_LL = (uint16)((uint32)((uint32)StatM_unUnusedStackTrusted_LL * 1000u) / ((uint32)STATM_STACK_T_LL_SIZE - 4u));
        }
        else
        {
            // end pattern is not valid
            StatM_unUnusedStackTrusted_LL = STATM_STACK_INVALID;
            StatM_unUnusedStackTrusted_percent_LL = STATM_STACK_INVALID;
        }
#endif


#if (RTE_THREAD_U_HH > 0u)

        // calculate stack size untrusted HH
        if (StatM__boCheckPatern(STATM_STACK_U_HH_END) == TRUE)
        {
            // end pattern is valid
            StatM_unUnusedStackUntrusted_HH = StatM__unGetNumberFreeBytes((STATM_STACK_U_HH_END + 4u), STATM_STACK_U_HH_START);
            ulUnusedStack += StatM_unUnusedStackUntrusted_HH;
            StatM_unUnusedStackUntrusted_percent_HH = (uint16)((uint32)((uint32)StatM_unUnusedStackUntrusted_HH * 1000u) / ((uint32)STATM_STACK_U_HH_SIZE - 4u));
        }
        else
        {
            // end pattern is not valid
            StatM_unUnusedStackUntrusted_HH = STATM_STACK_INVALID;
            StatM_unUnusedStackUntrusted_percent_HH = STATM_STACK_INVALID;
        }
#endif


#if (RTE_THREAD_U_HL > 0u)

        // calculate stack size untrusted HL
        if (StatM__boCheckPatern(STATM_STACK_U_HL_END) == TRUE)
        {
            // end pattern is valid
            StatM_unUnusedStackUntrusted_HL = StatM__unGetNumberFreeBytes((STATM_STACK_U_HL_END + 4u), STATM_STACK_U_HL_START);
            ulUnusedStack += StatM_unUnusedStackUntrusted_HL;
            StatM_unUnusedStackUntrusted_percent_HL = (uint16)((uint32)((uint32)StatM_unUnusedStackUntrusted_HL * 1000u) / ((uint32)STATM_STACK_U_HL_SIZE - 4u));
        }
        else
        {
            // end pattern is not valid
            StatM_unUnusedStackUntrusted_HL = STATM_STACK_INVALID;
            StatM_unUnusedStackUntrusted_percent_HL = STATM_STACK_INVALID;
        }
#endif


#if (RTE_THREAD_U_LH > 0u)

        // calculate stack size untrusted LH
        if (StatM__boCheckPatern(STATM_STACK_U_LH_END) == TRUE)
        {
            // end pattern is valid
            StatM_unUnusedStackUntrusted_LH = StatM__unGetNumberFreeBytes((STATM_STACK_U_LH_END + 4u), STATM_STACK_U_LH_START);
            ulUnusedStack += StatM_unUnusedStackUntrusted_LH;
            StatM_unUnusedStackUntrusted_percent_LH = (uint16)((uint32)((uint32)StatM_unUnusedStackUntrusted_LH * 1000u) / ((uint32)STATM_STACK_U_LH_SIZE - 4u));
        }
        else
        {
            // end pattern is not valid
            StatM_unUnusedStackUntrusted_LH = STATM_STACK_INVALID;
            StatM_unUnusedStackUntrusted_percent_LH = STATM_STACK_INVALID;
        }
#endif


#if (RTE_THREAD_U_LL > 0u)

        // calculate stack size untrusted LL
        if (StatM__boCheckPatern(STATM_STACK_U_LL_END) == TRUE)
        {
            // end pattern is valid
            StatM_unUnusedStackUntrusted_LL = StatM__unGetNumberFreeBytes((STATM_STACK_U_LL_END + 4u), STATM_STACK_U_LL_START);
            ulUnusedStack += StatM_unUnusedStackUntrusted_LL;
            StatM_unUnusedStackUntrusted_percent_LL = (uint16)((uint32)((uint32)StatM_unUnusedStackUntrusted_LL * 1000u) / ((uint32)STATM_STACK_U_LL_SIZE - 4u));
        }
        else
        {
            // end pattern is not valid
            StatM_unUnusedStackUntrusted_LL = STATM_STACK_INVALID;
            StatM_unUnusedStackUntrusted_percent_LL = STATM_STACK_INVALID;
        }
#endif
        ucTotalStackUsePercentage = (uint8)100u - (uint8)(((ulUnusedStack * 100u) + (STATM_STACK_SIZE / 2u)) / STATM_STACK_SIZE);
        (void)Rte_Write_StatM_StackUsage(ucTotalStackUsePercentage);
    }
    else
    {
        // do nothing
    }
}

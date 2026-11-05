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
/// \file  Icu_Cfg.c
///
/// \brief Configuration of ICU module
///
/// \descr  Configuration of ICU module to initialise the reading of PWM 
///         from sensors
///
///
/// \author Tanase Alexandru-Anton (F58375C)
///         mailTo:alexandru-anton.tanase[at]marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// Include
//=============================================================================

#include <Icu.h>

#ifndef UNIT_TEST
#include <ftm_ic_driver.h>
#else
#include <Icu_TargetTypes.h>
#endif // !UNIT_TEST

#include <UtilUtility.h>
#include <Cfg/Cfg.h>


//=============================================================================
// Defines
//=============================================================================

#define DUMMYMAX 25000U //dummy value for a parameter configuration because it is not used

//=============================================================================
// Configuration
//=============================================================================

#ifdef LDMO_A0_SAMPLE
#ifdef SAMPLE_FULL

/* hwChannelId, inputMode, edgeAlignement, measurementType,  filterValue, filterEn*/
/*continuousModeEn,  channelsCallbacksParams, channelsCallbacks*/
ftm_input_ch_param_t icu_pal_configs_FTM0[2] =
{
  /* hwChannelId, inputMode, edgeAlignement, measurementType,  filterValue, filterEn*/
/*continuousModeEn,  channelsCallbacksParams, channelsCallbacks*/
  {0, FTM_SIGNAL_MEASUREMENT, FTM_BOTH_EDGES, FTM_PERIOD_ON_MEASUREMENT, 0u, false, true, NULL_PTR, NULL_PTR}, //SENS_1_UC
  {4, FTM_SIGNAL_MEASUREMENT, FTM_BOTH_EDGES, FTM_PERIOD_ON_MEASUREMENT, 0u, false, true, NULL_PTR, NULL_PTR}, //SENS_2_UC
};

#elif defined(SAMPLE_ECO)

/* hwChannelId, inputMode, edgeAlignement, measurementType,  filterValue, filterEn*/
/*continuousModeEn,  channelsCallbacksParams, channelsCallbacks*/
ftm_input_ch_param_t icu_pal_configs_FTM0[2] =
{
  /* hwChannelId, inputMode, edgeAlignement, measurementType,  filterValue, filterEn*/
/*continuousModeEn,  channelsCallbacksParams, channelsCallbacks*/
  {0, FTM_SIGNAL_MEASUREMENT, FTM_BOTH_EDGES, FTM_PERIOD_ON_MEASUREMENT, 0u, false, true, NULL_PTR, NULL_PTR}, //SENS_1_UC
  {4, FTM_SIGNAL_MEASUREMENT, FTM_BOTH_EDGES, FTM_PERIOD_ON_MEASUREMENT, 0u, false, true, NULL_PTR, NULL_PTR}, //SENS_2_UC
};

#endif
#endif

#if defined (LDMO_B0_SAMPLE) || defined (UNIT_TEST)
#if defined (SAMPLE_FULL) || defined (UNIT_TEST)

/* hwChannelId, inputMode, edgeAlignement, measurementType,  filterValue, filterEn*/
/*continuousModeEn,  channelsCallbacksParams, channelsCallbacks*/
STATIC_AL ftm_input_ch_param_t sIcu_pal_configs_FTM0[2] =
{
  /* hwChannelId, inputMode, edgeAlignement, measurementType,  filterValue, filterEn*/
/*continuousModeEn,  channelsCallbacksParams, channelsCallbacks*/
  {0u, FTM_SIGNAL_MEASUREMENT, FTM_BOTH_EDGES, FTM_RISING_EDGE_PERIOD_MEASUREMENT, 0u, false, true, NULL_PTR, NULL_PTR}, //SENS_1_UC
  {4u, FTM_SIGNAL_MEASUREMENT, FTM_BOTH_EDGES, FTM_RISING_EDGE_PERIOD_MEASUREMENT, 0u, false, true, NULL_PTR, NULL_PTR}, //SENS_2_UC
};

#elif defined(SAMPLE_ECO)

/* hwChannelId, inputMode, edgeAlignement, measurementType,  filterValue, filterEn*/
/*continuousModeEn,  channelsCallbacksParams, channelsCallbacks*/
STATIC_AL ftm_input_ch_param_t sIcu_pal_configs_FTM0[2U] =
{
  /* hwChannelId, inputMode, edgeAlignement, measurementType,  filterValue, filterEn*/
/*continuousModeEn,  channelsCallbacksParams, channelsCallbacks*/
  {0u, FTM_SIGNAL_MEASUREMENT, FTM_BOTH_EDGES, FTM_PERIOD_ON_MEASUREMENT, 0u, false, true, NULL_PTR, NULL_PTR}, //SENS_1_UC
  {4u, FTM_SIGNAL_MEASUREMENT, FTM_BOTH_EDGES, FTM_PERIOD_ON_MEASUREMENT, 0u, false, true, NULL_PTR, NULL_PTR}, //SENS_2_UC
};

#endif
#endif

#ifdef LDMO_A0_SAMPLE
#ifdef SAMPLE_FULL
STATIC_AL uint32 ulIcu_pal_instances[1] = { 0 };
#elif defined(SAMPLE_ECO)
STATIC_AL uint32 ulIcu_pal_instances[1] = { 0 };
#endif
#endif

#if defined (LDMO_B0_SAMPLE) || defined (UNIT_TEST)
#if defined (SAMPLE_FULL) || defined (UNIT_TEST)
STATIC_AL uint32 ulIcu_pal_instances[1] = { 0 };
#elif defined(SAMPLE_ECO)
STATIC_AL uint32 ulIcu_pal_instances[1] = { 0 };
#endif
#endif


#ifdef LDMO_A0_SAMPLE
#ifdef SAMPLE_FULL
ftm_input_param_t sIcu_pal_configs[1] =
{
  /* nNumChannels,  nMaxCountValue, inputChConfig */
 {UTIL_COUNTOF(sIcu_pal_configs_FTM0), DUMMYMAX, &sIcu_pal_configs_FTM0[0] }

#elif defined(SAMPLE_ECO)
ftm_input_param_t sIcu_pal_configs[1] =
{
  /* nNumChannels,  nMaxCountValue, inputChConfig */
 {UTIL_COUNTOF(sIcu_pal_configs_FTM0), DUMMYMAX, &sIcu_pal_configs_FTM0[0] }

#endif
#endif

#if defined (LDMO_B0_SAMPLE) || defined (UNIT_TEST)
#if defined (SAMPLE_FULL) || defined (UNIT_TEST)
STATIC_AL ftm_input_param_t sIcu_pal_configs[1] =
{
  /* nNumChannels,  nMaxCountValue, inputChConfig */
 {UTIL_COUNTOF(sIcu_pal_configs_FTM0), DUMMYMAX, &sIcu_pal_configs_FTM0[0] }

#elif defined(SAMPLE_ECO)
STATIC_AL ftm_input_param_t sIcu_pal_configs[1] =
{
  /* nNumChannels,  nMaxCountValue, inputChConfig */
 {UTIL_COUNTOF(sIcu_pal_configs_FTM0), DUMMYMAX, &sIcu_pal_configs_FTM0[0] }

#endif
#endif
};

#ifdef LDMO_A0_SAMPLE
#ifdef SAMPLE_FULL
STATIC_AL ftm_user_config_t sIcu_pal_info[1] =
{
  /* syncMethod,  ftmMode, ftmPrescaler, ftmClockSource, BDMMode, isTofIsrEnabled, enableInitializationTrigger */
  {
    .syncMethod.softwareSync = true,
    .syncMethod.hardwareSync0 = false,
    .syncMethod.hardwareSync1 = false,
    .syncMethod.hardwareSync2 = false,
    .syncMethod.maxLoadingPoint = false,
    .syncMethod.minLoadingPoint = false,
    .syncMethod.inverterSync = FTM_SYSTEM_CLOCK,
    .syncMethod.outRegSync = FTM_SYSTEM_CLOCK,
    .syncMethod.maskRegSync = FTM_SYSTEM_CLOCK,
    .syncMethod.initCounterSync = FTM_SYSTEM_CLOCK,
    .syncMethod.autoClearTrigger = true,
    .syncMethod.syncPoint = FTM_UPDATE_NOW,
    .ftmMode = FTM_MODE_NOT_INITIALIZED,
    .ftmPrescaler = FTM_CLOCK_DIVID_BY_16,
    .ftmClockSource = FTM_CLOCK_SOURCE_SYSTEMCLK,
    .BDMMode = FTM_BDM_MODE_11,
    .isTofIsrEnabled = false,
    .enableInitializationTrigger = false,
  }
#elif defined(SAMPLE_ECO)
ftm_user_config_t sIcu_pal_info[1] =
{
  /* syncMethod,  ftmMode, ftmPrescaler, ftmClockSource, BDMMode, isTofIsrEnabled, enableInitializationTrigger */
  {
    .syncMethod.softwareSync = true,
    .syncMethod.hardwareSync0 = false,
    .syncMethod.hardwareSync1 = false,
    .syncMethod.hardwareSync2 = false,
    .syncMethod.maxLoadingPoint = false,
    .syncMethod.minLoadingPoint = false,
    .syncMethod.inverterSync = FTM_SYSTEM_CLOCK,
    .syncMethod.outRegSync = FTM_SYSTEM_CLOCK,
    .syncMethod.maskRegSync = FTM_SYSTEM_CLOCK,
    .syncMethod.initCounterSync = FTM_SYSTEM_CLOCK,
    .syncMethod.autoClearTrigger = true,
    .syncMethod.syncPoint = FTM_UPDATE_NOW,
    .ftmMode = FTM_MODE_NOT_INITIALIZED,
    .ftmPrescaler = FTM_CLOCK_DIVID_BY_16,
    .ftmClockSource = FTM_CLOCK_SOURCE_SYSTEMCLK,
    .BDMMode = FTM_BDM_MODE_11,
    .isTofIsrEnabled = false,
    .enableInitializationTrigger = false,
  }

#endif
};
#endif

#if defined (LDMO_B0_SAMPLE) || defined (UNIT_TEST)
#if defined (SAMPLE_FULL) || defined (UNIT_TEST)
STATIC_AL ftm_user_config_t sIcu_pal_info[1] =
{
  /* syncMethod,  ftmMode, ftmPrescaler, ftmClockSource, BDMMode, isTofIsrEnabled, enableInitializationTrigger */
  {
    .syncMethod.softwareSync = true,
    .syncMethod.hardwareSync0 = false,
    .syncMethod.hardwareSync1 = false,
    .syncMethod.hardwareSync2 = false,
    .syncMethod.maxLoadingPoint = false,
    .syncMethod.minLoadingPoint = false,
    .syncMethod.inverterSync = FTM_SYSTEM_CLOCK,
    .syncMethod.outRegSync = FTM_SYSTEM_CLOCK,
    .syncMethod.maskRegSync = FTM_SYSTEM_CLOCK,
    .syncMethod.initCounterSync = FTM_SYSTEM_CLOCK,
    .syncMethod.autoClearTrigger = true,
    .syncMethod.syncPoint = FTM_UPDATE_NOW,
    .ftmMode = FTM_MODE_NOT_INITIALIZED,
    .ftmPrescaler = FTM_CLOCK_DIVID_BY_16,
    .ftmClockSource = FTM_CLOCK_SOURCE_SYSTEMCLK,
    .BDMMode = FTM_BDM_MODE_11,
    .isTofIsrEnabled = false,
    .enableInitializationTrigger = false,
  }
#elif defined(SAMPLE_ECO)
STATIC_AL ftm_user_config_t sIcu_pal_info[1] =
{
  /* syncMethod,  ftmMode, ftmPrescaler, ftmClockSource, BDMMode, isTofIsrEnabled, enableInitializationTrigger */
  {
    .syncMethod.softwareSync = true,
    .syncMethod.hardwareSync0 = false,
    .syncMethod.hardwareSync1 = false,
    .syncMethod.hardwareSync2 = false,
    .syncMethod.maxLoadingPoint = false,
    .syncMethod.minLoadingPoint = false,
    .syncMethod.inverterSync = FTM_SYSTEM_CLOCK,
    .syncMethod.outRegSync = FTM_SYSTEM_CLOCK,
    .syncMethod.maskRegSync = FTM_SYSTEM_CLOCK,
    .syncMethod.initCounterSync = FTM_SYSTEM_CLOCK,
    .syncMethod.autoClearTrigger = true,
    .syncMethod.syncPoint = FTM_UPDATE_NOW,
    .ftmMode = FTM_MODE_NOT_INITIALIZED,
    .ftmPrescaler = FTM_CLOCK_DIVID_BY_16,
    .ftmClockSource = FTM_CLOCK_SOURCE_SYSTEMCLK,
    .BDMMode = FTM_BDM_MODE_11,
    .isTofIsrEnabled = false,
    .enableInitializationTrigger = false,
  }

#endif
};
#endif

#ifdef LDMO_A0_SAMPLE
#ifdef SAMPLE_FULL
tsIcu_ConfigInstanceMap sIcu_Instance_Map[1U] =
{
  {&ulIcu_pal_instances[0],  &sIcu_pal_configs[0]}
};
#elif defined(SAMPLE_ECO)
tsIcu_ConfigInstanceMap sIcu_Instance_Map[1U] =
{
  {&ulIcu_pal_instances[0],  &sIcu_pal_configs[0]}
};
#endif
#endif

#if defined (LDMO_B0_SAMPLE) || defined (UNIT_TEST)
#if defined (SAMPLE_FULL) || defined (UNIT_TEST)
STATIC_AL tsIcu_ConfigInstanceMap sIcu_Instance_Map[1U] =
{
  {&ulIcu_pal_instances[0],  &sIcu_pal_configs[0], &sIcu_pal_info[0]}
};
#elif defined(SAMPLE_ECO)
STATIC_AL tsIcu_ConfigInstanceMap sIcu_Instance_Map[1U] =
{
  {&ulIcu_pal_instances[0],  &sIcu_pal_configs[0], &sIcu_pal_info[0]}
};
#endif
#endif

CONST_AL tsIcu_SpecificType sIcu_Config =
{
  UTIL_COUNTOF(sIcu_Instance_Map),
  (tsIcu_ConfigInstanceMap*)&sIcu_Instance_Map[0]
};

//EOF

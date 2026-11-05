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
/// \file  Pdb_Cfg.c
///
/// \brief Project related Pdb configuration
///
/// \author Stefan Tyirean (f75617c)
///         mailto: stefan.tyirean[at]marelli.com
///
/// \Date April 2021
///
//-----------------------------------------------------------------------------

#include <Pdb.h>
#include <UtilUtility.h>
#include <Std_Types.h>
#include <Cfg/Cfg.h>

#if defined (CPU_S32K146)
#define SAMPLE_FULL
#elif defined (CPU_S32K142)
#define SAMPLE_ECO
#endif

// PDB input clk 48Mhz
#define PDB_CLK_FREQ      48000000u

// PDB period 10ms
#define PDB_DIVIDER                           8000u // 8Khz (125us sampling)
#define PDB_PARAM_DIVIDER                     1u    // Divider based on multiplier and divider (1 * 1)
#define PDB_PARAM_MULTIPLIER                  1u    // Divider based on multiplier and divider (1 * 1)
#define PDB_PERIOD                            PDB_CLK_FREQ / ((PDB_DIVIDER * PDB_PARAM_DIVIDER * PDB_PARAM_MULTIPLIER))  // 6000u
#define PDB0_CH0_TRIGGER_TIME_OFFSET          10u
#define PDB1_CH0_TRIGGER_TIME_OFFSET          20u
#define PDB0_CH1_TRIGGER_TIME_OFFSET          ((PDB_PERIOD / 2u) + 10u)
#define PDB1_CH1_TRIGGER_TIME_OFFSET          ((PDB_PERIOD / 2u) + 20u)

// Pdb Instances Configuration
STATIC_AL CONST_AL tsPdb_PdbInstanceCfg Pdb_asPdbInstCfg[] =
{
  /*PDB instance,     Load Mode,  Int Enable,   DMA Request,  Prescaler,   Multiplier,       Trigger,    Continous,  PDB period,      DMA/Int Trig Time,  Module Enable  */
  {     0u,          eImidiately,   FALSE,        FALSE,      eMulBy1,   eMultiplier1,    eTrigMuxIn,    FALSE,      PDB_PERIOD,       PDB_PERIOD,               TRUE },
  {     1u,          eImidiately,   FALSE,        FALSE,      eMulBy1,   eMultiplier1,    eTrigMuxIn,    FALSE,      PDB_PERIOD,       PDB_PERIOD,               TRUE }
};

// Pdb Channels configuration based on ADC inputs
STATIC_AL CONST_AL tsPdb_PdbInputCfg Pdb_asPdbChMapCfg[] =
{
  /*Channel,     Adc Input,  Int Enable, Pdb Instance,  Chn mod 8,                      Start Triger,  Trig Out,  Back2Back, Ch Enbl */
#ifdef LDMO_A0_SAMPLE
  {   0u,         eExtCh3,      FALSE,        1u,           0u,         PDB1_CH0_TRIGGER_TIME_OFFSET,       TRUE,     FALSE,    TRUE },
  {   0u,         eExtCh11,     FALSE,        0u,           0u,         PDB0_CH0_TRIGGER_TIME_OFFSET,       TRUE,     FALSE,    TRUE },
  {   1u,         eExtCh9,      FALSE,        0u,           0u,                                   0u,       TRUE,     TRUE,     TRUE },
  {   2u,         eExtCh8,      FALSE,        0u,           0u,                                   0u,       TRUE,     TRUE,     TRUE },
  {   3u,         eExtCh15,     FALSE,        0u,           0u,                                   0u,       TRUE,     TRUE,     TRUE },
  {   4u,         eExtCh14,     FALSE,        0u,           0u,                                   0u,       TRUE,     TRUE,     TRUE },
  {   5u,         eExtCh13,     FALSE,        0u,           0u,                                   0u,       TRUE,     TRUE,     TRUE },
  {   6u,         eExtCh12,     FALSE,        0u,           0u,                                   0u,       TRUE,     TRUE,     TRUE },
  {   7u,         eExtCh2,      FALSE,        0u,           0u,                                   0u,       TRUE,     TRUE,     TRUE },
  {   1u,         eExtCh0,      FALSE,        1u,           0u,                                   0u,       TRUE,     TRUE,     TRUE },
  {   2u,         eExtCh8,      FALSE,        1u,           0u,                                   0u,       TRUE,     TRUE,     TRUE },
  {   8u,         eExtCh10,     FALSE,        0u,           1u,         PDB0_CH1_TRIGGER_TIME_OFFSET,       TRUE,    FALSE,     TRUE },
  {   3u,         eExtCh14,     FALSE,        1u,           0u,                                   0u,       TRUE,     TRUE,     TRUE },
  {   4u,         eExtCh9,      FALSE,        1u,           0u,                                   0u,       TRUE,     TRUE,     TRUE },
  {   5u,         eExtCh13,     FALSE,        1u,           0u,                                   0u,       TRUE,     TRUE,     TRUE },
  {   6u,         eExtCh6,      FALSE,        1u,           0u,                                   0u,       TRUE,     TRUE,     TRUE },
  {   7u,         eExtCh7,      FALSE,        1u,           0u,                                   0u,       TRUE,     TRUE,     TRUE },
  {   8u,         eExtCh2,      FALSE,        1u,           1u,         PDB1_CH1_TRIGGER_TIME_OFFSET,       TRUE,    FALSE,     TRUE },
  {   9u,         eExtCh1,      FALSE,        1u,           1u,                                   0u,       TRUE,     TRUE,     TRUE },
  {  10u,         eExtCh10,     FALSE,        1u,           1u,                                   0u,       TRUE,     TRUE,     TRUE },
  {   9u,         eExtCh1,      FALSE,        0u,           1u,                                   0u,       TRUE,     TRUE,     TRUE },
  {  11u,         eExtCh15,     FALSE,        1u,           1u,                                   0u,       TRUE,     TRUE,     TRUE },
  {  10u,         eExtCh0,      FALSE,        0u,           1u,                                   0u,       TRUE,     TRUE,     TRUE }
#elif defined (LDMO_B0_SAMPLE)
#ifdef SAMPLE_FULL
  {   0u,         eExtCh2,      FALSE,        1u,           0u,         PDB1_CH0_TRIGGER_TIME_OFFSET,       TRUE,     FALSE,    TRUE },
  {   0u,         eExtCh11,     FALSE,        0u,           0u,         PDB0_CH0_TRIGGER_TIME_OFFSET,       TRUE,     FALSE,    TRUE },
  {   1u,         eExtCh9,      FALSE,        0u,           0u,                                   0u,       TRUE,      TRUE,    TRUE },
  {   2u,         eExtCh8,      FALSE,        0u,           0u,                                   0u,       TRUE,      TRUE,    TRUE },
  {   3u,         eExtCh15,     FALSE,        0u,           0u,                                   0u,       TRUE,      TRUE,    TRUE },
  {   4u,         eExtCh14,     FALSE,        0u,           0u,                                   0u,       TRUE,      TRUE,    TRUE },
  {   5u,         eExtCh13,     FALSE,        0u,           0u,                                   0u,       TRUE,      TRUE,    TRUE },
  {   6u,         eExtCh7,      FALSE,        0u,           0u,                                   0u,       TRUE,      TRUE,    TRUE },
  {   7u,         eExtCh2,      FALSE,        0u,           0u,                                   0u,       TRUE,      TRUE,    TRUE },
  {   1u,         eExtCh0,      FALSE,        1u,           0u,                                   0u,       TRUE,      TRUE,    TRUE },
  {   2u,         eExtCh8,      FALSE,        1u,           0u,                                   0u,       TRUE,      TRUE,    TRUE },
  {   8u,         eExtCh10,     FALSE,        0u,           1u,         PDB0_CH1_TRIGGER_TIME_OFFSET,       TRUE,     FALSE,    TRUE },
  {   3u,         eExtCh14,     FALSE,        1u,           0u,                                   0u,       TRUE,      TRUE,    TRUE },
  {   4u,         eExtCh9,      FALSE,        1u,           0u,                                   0u,       TRUE,      TRUE,    TRUE },
  {   5u,         eExtCh13,     FALSE,        1u,           0u,                                   0u,       TRUE,      TRUE,    TRUE },
  {   6u,         eExtCh6,      FALSE,        1u,           0u,                                   0u,       TRUE,      TRUE,    TRUE },
  {   9u,         eExtCh3,      FALSE,        0u,           1u,                                   0u,       TRUE,      TRUE,    TRUE },
  {   7u,         eExtCh1,      FALSE,        1u,           0u,                                   0u,       TRUE,      TRUE,    TRUE },
  {   8u,         eExtCh10,     FALSE,        1u,           1u,         PDB1_CH1_TRIGGER_TIME_OFFSET,       TRUE,     FALSE,    TRUE },
  {  10u,         eExtCh1,      FALSE,        0u,           1u,                                   0u,       TRUE,      TRUE,    TRUE },
  {   9u,         eExtCh15,     FALSE,        1u,           1u,                                   0u,       TRUE,      TRUE,    TRUE },
  {  11u,         eExtCh0,      FALSE,        0u,           1u,                                   0u,       TRUE,      TRUE,    TRUE }
#elif defined(SAMPLE_ECO)
  {   0u,         eExtCh11,     FALSE,        0u,           0u,         PDB0_CH0_TRIGGER_TIME_OFFSET,       TRUE,     FALSE,    TRUE },
  {   1u,         eExtCh3,      FALSE,        0u,           0u,                                   0u,       TRUE,      TRUE,    TRUE },
  {   2u,         eExtCh2,      FALSE,        0u,           0u,                                   0u,       TRUE,      TRUE,    TRUE },
  {   0u,         eExtCh8,      FALSE,        1u,           0u,         PDB1_CH0_TRIGGER_TIME_OFFSET,       TRUE,     FALSE,    TRUE },
  {   1u,         eExtCh6,      FALSE,        1u,           0u,                                   0u,       TRUE,      TRUE,    TRUE },
  {   2u,         eExtCh2,      FALSE,        1u,           0u,                                   0u,       TRUE,      TRUE,    TRUE },
  {   3u,         eExtCh13,     FALSE,        0u,           0u,                                   0u,       TRUE,      TRUE,    TRUE },
  {   4u,         eExtCh14,     FALSE,        0u,           0u,                                   0u,       TRUE,      TRUE,    TRUE },
  {   5u,         eExtCh15,     FALSE,        0u,           0u,                                   0u,       TRUE,      TRUE,    TRUE },
  {   6u,         eExtCh8,      FALSE,        0u,           0u,                                   0u,       TRUE,      TRUE,    TRUE },
  {   7u,         eExtCh10,     FALSE,        0u,           0u,                                   0u,       TRUE,      TRUE,    TRUE },
  {   3u,         eExtCh1,      FALSE,        1u,           0u,                                   0u,       TRUE,      TRUE,    TRUE },
  {   4u,         eExtCh0,      FALSE,        1u,           0u,                                   0u,       TRUE,      TRUE,    TRUE },
  {   8u,         eExtCh9,      FALSE,        0u,           1u,         PDB0_CH1_TRIGGER_TIME_OFFSET,       TRUE,     FALSE,    TRUE },
  {   9u,         eExtCh7,      FALSE,        0u,           1u,                                   0u,       TRUE,      TRUE,    TRUE },
  {  10u,         eExtCh1,      FALSE,        0u,           1u,                                   0u,       TRUE,      TRUE,    TRUE }
#endif
#endif
};

// Extern data configuration passed to Pdb Init function
const tsPdb_CfgData Pdb_sPdbDatatCfg = 
{
  /*     Config array,                count*/
  { &Pdb_asPdbChMapCfg[0],  countof(Pdb_asPdbChMapCfg) },
  { &Pdb_asPdbInstCfg[0],   countof(Pdb_asPdbInstCfg)  }
};

// EOF

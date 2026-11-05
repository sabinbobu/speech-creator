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
/// \file  Pdb_TargetTypes.h
///
/// \brief Lpit Driver type definitions (low access to the PDB pheripheric)
///
/// \author Stefan Tyirean (f75617c)
///         mailto: stefan.tyirean[at]marelli.com
///
/// \Date April 2021
///
//-----------------------------------------------------------------------------
#ifndef PDB_TYPES_2021_03_16_H_
#define PDB_TYPES_2021_03_16_H_

//====================================================================
// Include files
//====================================================================

#include <Std_Types.h>
#include <AL_Helper.h>

//====================================================================
// Type data definitions
//====================================================================

typedef enum
{
  eExtCh0 = 0u,
  eExtCh1 = 1u,
  eExtCh2 = 2u,
  eExtCh3 = 3u,
  eExtCh4 = 4u,
  eExtCh5 = 5u,
  eExtCh6 = 6u,
  eExtCh7 = 7u,
  eExtCh8 = 8u,
  eExtCh9 = 9u,
  eExtCh10 = 10u,
  eExtCh11 = 11u,
  eExtCh12 = 12u,
  eExtCh13 = 13u,
  eExtCh14 = 14u,
  eExtCh15 = 15u,
  eIntCh0 = 21u,
  eIntCh1 = 22u,
  eIntCh2 = 23u,
  eBandGap = 27u,
  eIntCh3 = 28u,
  eVrefH = 29u,
  eVrefL = 30u,
  eExtCh16 = 32u,
  eExtCh17 = 33u,
  eExtCh18 = 34u,
  eExtCh19 = 35u,
  eExtCh20 = 36u,
  eExtCh21 = 37u,
  eExtCh22 = 38u,
  eExtCh23 = 39u,
  eExtCh24 = 40u,
  eExtCh25 = 41u,
  eExtCh26 = 42u,
  eExtCh27 = 42u,
  eExtCh28 = 44u,
  eExtCh29 = 45u,
  eExtCh30 = 46u,
  eExtCh32 = 47u,
  eDisabled = 63u
}tePdb_InChMap;

typedef struct
{
  uint8 ucAdcCh;
  tePdb_InChMap eInCh;
  boolean boIntEnbl;
  uint8 ucPdbInst;
  uint8 ucPdbChannel;
  uint32 ulPdbChnInDelayOffset_Reg;
  boolean boPdbTriggerOutput;
  boolean boPdbBack2Back;
  boolean boPdbAdcChnEnbl;
}tsPdb_PdbInputCfg;

typedef enum
{
  eImidiately = 0u,
  eModulusMatch = 1u,
  eTriggered = 2u,
  eBoth = 3u
}tePdb_PdbLdModCfg;

typedef enum
{
  eMulBy1 = 0u,
  eMulBy2 = 1u,
  eMulBy4 = 2u,
  eMulBy8 = 3u,
  eMulBy16 = 4u,
  eMulBy32 = 5u,
  eMulBy64 = 6u,
  eMulby128 = 7u
}tePdb_PdbPrescalerCfg;

typedef enum
{
  eMultiplier1 = 0u,
  eMultiplier10 = 1u,
  eMultiplier20 = 2u,
  eMultiplier40 = 3u
}tePdb_PdbMultiplierCfg;

typedef enum
{
  eTrigMuxIn = 0u,
  eTrigSw = 15u
}tePdb_PdbTriggerCfg;

typedef struct
{
  uint8 ucPdbInst;
  tePdb_PdbLdModCfg eLdMod;
  boolean boIntEnable;
  boolean boDmaEnable;
  tePdb_PdbPrescalerCfg ePrescaler;
  tePdb_PdbMultiplierCfg eMul;
  tePdb_PdbTriggerCfg eTrigger;
  boolean boContinousMode;
  uint32 ulPdbPeriod_Reg;
  uint32 ulIntDmaTrigTime_Reg;
  boolean boModEnbl;
}tsPdb_PdbInstanceCfg;


typedef struct
{
  CONST_AL tsPdb_PdbInputCfg* CONST_AL psPdbInCfg;
  uint8 ucCfgLength;
}tsPdb_PdbChInCfgMap;

typedef struct
{
  CONST_AL tsPdb_PdbInstanceCfg* CONST_AL psPdbInstCfg;
  uint8 ucCfgLength;
}tsPdb_PdbInstCfgMap;

typedef struct
{
  tsPdb_PdbChInCfgMap sPdbInputChCfg;
  tsPdb_PdbInstCfgMap sPdbInstanceCfg;
}tsPdb_CfgData;


#endif // PDB_TARGET_TYPES_2021_03_16_H_

// EOF

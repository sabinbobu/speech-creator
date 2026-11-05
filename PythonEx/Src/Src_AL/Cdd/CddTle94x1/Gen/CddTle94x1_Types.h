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
/// \file  CddTle94x1_Types.h
///
/// \brief  SBC complex device driver
///
/// \descr  System Basic Chip
///
/// \author Diana Ursan
/// \e-mail: elena-diana.ursan@marelli.com
///
//-----------------------------------------------------------------------------
#ifndef CDD_TLE94X1_TYPES_2021_03_08_H_
#define CDD_TLE94X1_TYPES_2021_03_08_H_

//=============================================================================
//  preprocessor definitions
//=============================================================================

//=============================================================================
//  includes
//=============================================================================
#include <Std_Types.h>
//=============================================================================
//  definitions
//=============================================================================


//=============================================================================
//  types
//=============================================================================


typedef struct
{
  boolean boInitStatRead;
  boolean boInitCtrlWrite;
  boolean boGoToStop_Failure;
  boolean boGotoStop_SpiFailure;
  boolean boGoToSleep_Failure;
  boolean boGotoSleep_SpiFailure;
  boolean boCyclic_SPI_Communication;
  boolean boCyclic_CanMode;
  boolean boReadWKStat_Failure;
  boolean boReadSUPStat_Failure;
  boolean boScheduleTableFull;
  boolean boCanModeError;
  boolean boCanChannelError;
  boolean boSpiWdgFailure;
  boolean boReadWdgStat_Failure;
  boolean boErrorReset;
  boolean boTSDError;
  boolean boShorttoVBAT;
  boolean boShorttoGND;
} tsCddTle94x1_ErrorState;

typedef enum teCddTle94x1_MsgType
{
  eNoMsg = 0,                             // No Reset
  eBUS_CTRL_0,                            // Control register BUS_CTRL
  eBUS_STAT,                              // Status register BUS_STAT
  eWK_LVL_STAT,                           // Status register WK_LVL_STAT
  eSUP_STAT_0                             // Status register SUP_STAT_0
}teCddTle94x1_MsgType;

//=============================================================================
//  global variable
//=============================================================================

//=============================================================================
//  inline functions
//=============================================================================

//=============================================================================
//Intern prototypes
//=============================================================================

#endif // CDD_TLE94X1_TYPES_2021_03_08_H_
// EOF

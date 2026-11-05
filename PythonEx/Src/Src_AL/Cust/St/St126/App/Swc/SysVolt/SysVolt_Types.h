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
/// \file   SysVolt_Types.h
///
/// \brief  SysVolt type Definitions
///
/// \descr  All type definitions used by SysVolt module
///
/// \author Henrietta Futo (F31185D)
///         mailTo: henrietta-helena.futo[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef __SYSVOLT_TYPES_H__
#define __SYSVOLT_TYPES_H__

//=============================================================================
// includes
//=============================================================================

#include <Std_Types.h>
#include <Util_Time.h>
#include <AL_Helper.h>
//#include <Swc/CodM/CodM.h>  // this will be used when CodM will be available
//#include <Swc/CodM/CodM_Para.h> // this will be used when CodM will be available

//=============================================================================
// Type definitions
//=============================================================================

// Volt ranges local type
typedef enum
{
  eSysVolt_eLow6 = 0,
  eSysVolt_eLow5 = 1,
  eSysVolt_eLow4 = 2,
  eSysVolt_eLow3 = 3,
  eSysVolt_eLow2 = 4,
  eSysVolt_eLow1 = 5,

  eSysVolt_eNormal = 6,

  eSysVolt_eHigh1 = 7,
  eSysVolt_eHigh2 = 8,
  eSysVolt_eHigh3 = 9,
  eSysVolt_eHigh4 = 10,
  eSysVolt_eHigh5 = 11,
  eSysVolt_eHigh6 = 12,
  eSysVolt_eUnknown = 255
} teSysVolt_VoltRanges;

// Module Indexes for voltage states processing
typedef enum {
  eSysV_Stp_Idx = 0,
  eSysV_Fan_Idx,
  eSysV_Vbat_Idx,
  eSysV_Led_Idx,
  eSysV_LastModule_Idx      // marks the end of all indexes
} teSysVolt_EntryModIx;

// A result set contains all variables necessary to build a valid result
typedef struct
{
  teSysVolt_VoltRanges  eVoltageRangeResult;      // Instant Voltage Range
  teSysVolt_VoltRanges  ePreviousVoltageRange;    // Last Voltage Known
  TIMER                 ulDebounceTmr_Us;         // Debounce timer (Us)
  uint16                unDebounceValTo_Ms;       // Debounce value (Ms)
}tsSysVolt_InVoltState;

// Vbat states [Normal, overvoltage, undervoltage]
typedef enum
{
  eVbatLow = 0,       // Vbat Voltage Low
  eVbatNormal,        // Vbat Voltage Normal
  eVbatHigh           // Vbat Voltage High
}teSysVolt_VbatState;

// A voltage range set specifies the symbolic name of a voltage range an its upper voltage limit 
typedef struct
{
  teSysVolt_VoltRanges                eVoltageRange;            // enum value for the voltage range
  uint16                              unRangeUpperLimit_mV;     // upper voltage limit for the corresponding voltage range
  uint16                              unDebounceCnt_RangeGetsWorse_Ms;  // debounce counter value in case we want to go to a worse range
  uint16                              unDebounceCnt_RangeGetsBetter_Ms; // debounce counter value in case we want to go to a better range
}tsSysVolt_VoltageRangeSet;

// Function pointer type for range change callbacks
typedef void (*tpfSysVolt_RangeChangeInd) (teSysVolt_VoltRanges);

// Function pointer for reading voltage (IO HW abstraction functions for ADC)
typedef void(*tpfSysVolt_ReadVoltage)(uint16* const);

// Status of the 12V electrical energy supply in by engine
typedef enum
{
  SysVolt_eEtatFee_1_1 = 0U,
  SysVolt_eEtatFee_1_2 = 1U,
  SysVolt_eEtatFee_1_3c = 2U,
  SysVolt_eEtatFee_1_3r = 3U,
  SysVolt_eEtatFee_2_1 = 4U,
  SysVolt_eEtatFee_3c_1 = 5U,
  SysVolt_eEtatFee_3r_1 = 6U,
  SysVolt_eEtatFee_4_1 = 7U,
  SysVolt_eEtatFee_5_5 = 8U,
  SysVolt_eEtatFee_1_3vr = 9U,
  SysVolt_eEtatFee_3vr_1 = 10U,
  SysVolt_eEtatFee_Invalid = 11U
}teSysVolt_EtatFee;

// Vehicle main state
typedef enum
{
	eSysVolt_State_Stop = 0U, // VES main state Stop/Arret
	eSysVolt_State_Contact = 1U, // VES main state Contact/Ignition
	eSysVolt_State_Start = 2U, // VES main state Start Engine/DEM
	eSysVolt_State_InvalidSEV = 3U  // VES main state Invalid/Reserved
}teSysVolt_EtatPrincipSEV;
// Config set contains the complete configuration that is necessary for a module that uses SysVolt
typedef struct
{
  tsSysVolt_VoltageRangeSet*          pRangeCfg;                        // voltage range configuration table
  CONST_AL uint8                      ucNumOfRanges;                    // number of voltage ranges in pRangeCfg
  CONST_AL tpfSysVolt_RangeChangeInd  pfRangeChangeIndCb;               // callback that is called on each range change
  CONST_AL tpfSysVolt_ReadVoltage     pfReadVoltageCb;                  // function used for reading the voltage value
}tsSysVolt_InVoltCfg;

#endif // __SYSVOLT_TYPES_H__


// EOF

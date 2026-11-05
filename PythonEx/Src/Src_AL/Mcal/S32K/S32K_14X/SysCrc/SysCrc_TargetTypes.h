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
/// \file  SysCrc_TargetTypes.h
///
/// \brief
///
//-----------------------------------------------------------------------------
#ifndef SYS_CRC_TARGET_TYPES_2021_06_25_H_
#define SYS_CRC_TARGET_TYPES_2021_06_25_H_

#include <Std_Types.h>
#include <Cfg/Cfg.h>

 
//=============================================================================
// Exported Macros
//=============================================================================

//Nr of CRC istances
#define INST_SYSCRC      (0u)

//=============================================================================
// Exported Types
//=============================================================================
typedef struct SysCrc_SpecificType
{
  uint8 ucCountOfSysCrcInstances;
  void* SysCrc_cfg;
} SysCrc_SpecificType;

// SysCrc callback function definition
typedef void(*tSysCrc_pFnct) (void);

// Describe ROM segments
typedef struct
{
  uint32          SysCrc_ulStartAddrOfSegment; // start address of the ROM-/Calib-/etc- segment
  uint32          SysCrc_ulSizeOfSegment;      // size of the ROM-/Calib-/etc- segment
  boolean         SysCrc_boSwapCrc;            // swap CRC? (e.g. 0x1234 -> 0x3412)
  uint16          SysCrc_unDtc;                // used DTC of this checked segment
  uint32          SysCrc_ulRomCalcCRC;         // Rom Address for calculated CRC
  tSysCrc_pFnct   SysCrc_pfnCrcFailure;        // callback function to report Flash CRC failure
}tsSysCrc_SegmentConfig;

typedef enum
{
  eApplicationSegment,
  eCalibrationSegment,
  eSegmentsCount,
}teSysCrc_SegmentId;

typedef struct
{
  boolean boCalibFailStatus;
  boolean boCalibCheckInitStatus;
}tsSysCrc_CalibGetStatus;

// pointer type for pointers to data buffers, from which the CRC value is to be calculated.
typedef P2CONST(uint8, AUTOMATIC, CRC_APPL_DATA) Crc_DataRefType;

//=============================================================================
// Exported Variables
//=============================================================================

//=============================================================================
// Exported Functions Declaration
//=============================================================================

#endif // SYS_CRC_TARGET_TYPES_2021_06_25_H_

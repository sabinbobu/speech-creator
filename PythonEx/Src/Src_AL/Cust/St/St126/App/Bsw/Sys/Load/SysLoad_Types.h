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
/// \file  SysLoad_Types.h
///
/// \brief
///
//-----------------------------------------------------------------------------
#ifndef SYS_LOAD_TYPES_2019_12_11_H_
#define SYS_LOAD_TYPES_2019_12_11_H_
//=============================================================================
//  Includes
//=============================================================================

#include <Util_Time.h>
#include <UtilUtility.h>

//=============================================================================
//  Macros
//=============================================================================
#define MEASURE_RUNNABLE             0u
#define MEASURE_ISR                  1u
#define MEASURE_TASK                 2u
#define MEASURE_STACK                3u
#define MEASURE_RUNNABLE_PERIOD_ONLY 4u
//=============================================================================
//  Types
//=============================================================================

typedef struct
{
  TIMER  tiRunTimeMinOverall_us;
  TIMER  tiRunTimeMaxOverall_us;
  TIMER  tiRunTimeAverageOverall_us;
  TIMER  tiCallPeriodAverageOverall_us;
  TIMER  tiFirstExecutionRunTime_us;
  TIMER  tiFirstCallTimeStamp_us;
  uint32 tiSysLoad_ExecutionOrder_Number;
}tSysLoad_MeasurementResults;

#endif // SYS_LOAD_TYPES_2019_12_11_H_

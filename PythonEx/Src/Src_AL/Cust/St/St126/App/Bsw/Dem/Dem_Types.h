//*****************************************************************************
// (C) Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written 
// authorization of Automotive Lighting Reutlingen GmbH.
//*****************************************************************************
//----------------------------------------------------------------------------
// \file   Dem_Types.h
//
// \brief  
//
// \descr  Declarations and types of the DEM
//
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//----------------------------------------------------------------------------
#ifndef __DEM_TYPES_H__
#define __DEM_TYPES_H__


//=============================================================================
// includes
//=============================================================================
#include <Util_Time.h> 

//=============================================================================
// declarations
//=============================================================================

//-----------------------------------------------------------------------------
// Defines the condition function
typedef void(*dem_condition_fct)(uint16 event_id);

//-----------------------------------------------------------------------------
// Defines the notification function
typedef void(*dem_notify_fct)(uint16 event_id, boolean status_passed);

typedef struct dem_counter_confirm_status
{
  uint16  unDiagFaultCnt;
  uint8   ucDiagFaultState;
  TIMER   ulDiagConfirmedTimer;
}Dem_tsDiagFaultState;


//-----------------------------------------------------------------------------
// DEM configutation entry
typedef struct struct_dem_config_type {
  // 16 bit event id
  uint16            event_id;
  // Debounce time in [ms] for event test fail, set to 0 if unused
  uint16            debounce_time_failed;
  // Debounce time in [ms] for event test pass, set to 0 if unused
  uint16            debounce_time_passed;
  // Debounce steps for event test fail, set to 0 if unused (127 is used as default)
  uint16            debounce_cnt_inc;
  // Debounce steps for event test pass, set to 0 if unused (128 is used as default)
  uint16            debounce_cnt_dec;
  // Debounce counter max
  uint16            debounce_cnt_max;
  // Debounce counter minim
  uint16            debounce_cnt_min;
  // Jdd Reporter
  boolean           jdd_reporter;
  // Callback function handler
  dem_condition_fct condition_present;
  // Callback function handler
  dem_condition_fct condition_confirmed_present;
  // Callback function handler
  dem_condition_fct condition_absent;
  // Callback function handler
  dem_condition_fct condition_confirmed_absent;


  // Callback function handler, called after event status changed to failed
  dem_notify_fct    notify_failed;
  // Callback function handler, called after event status changed to passed
  dem_notify_fct    notify_passed;
  // Callback function handler, called after ervery event status change
  dem_notify_fct    notify_custom;
} dem_config_type;


//-----------------------------------------------------------------------------
// Structure for each DemEventId
typedef struct struct_Dem_aEventStatus {
  // Keeps the current time value
  TIMER  ulDebounceStartTime;
  // Keeps the current bits status
  uint16 unStatus;
} tDem_aEventStatus_type;


//-----------------------------------------------------------------------------
// Global structure which keeps in RAM the request status of each ALEC
typedef struct {
  // Variable which keeps the current status of test; the initial value is STATUS_TEST_PASSED even the test was not done at initialization phase
  uint8   ucResult;
  // Variable which indicate that the test ALEC was done in the current cycle
  boolean boDoneThisCycle;
}Dem_tsStatusTest;

#endif  // __DEM_TYPES_H_

// EOF

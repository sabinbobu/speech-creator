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
/// \file  Dem.c
///
/// \brief Generic implementation of the DEM
///
/// \descr In this file flags and timers handle are performed
///
/// \date   16.03.2021
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <Nvm.h>
#include <Bsw/Nvm/NvM_Para.h>
#include <Dem.h>
//#include <EcuM.h>

#include <SysMonRx_Callbacks.h>  // permitted because is used to read values
#include <LgmEIMMainAPI.h>
// TODO VS: #include "Bsw/Com/Can/CanErr.h"
#ifndef UNIT_TEST
#include <Rte.h>
#else
#include <_NM_Types.h>
#endif

//=============================================================================
// Expand configuration
//=============================================================================

//lint -e451 Header file 'xxx' repeatedly included but does not have a standard include guard

// declare function prototypes
#define  DEM_CONFIG_DECL_FCT
#include <Dem_Cfg.h>
#undef   DEM_CONFIG_DECL_FCT

// define DEM configuration table
#define  DEM_CONFIG_MAC_DEF_TABLE
#include <Dem_Cfg.h>
#undef   DEM_CONFIG_MAC_DEF_TABLE

//lint +e451 Header file 'xxx' repeatedly included but does not have a standard include guard

//=============================================================================
// Static Variables
//=============================================================================

// Global array which keeps in RAM the following information for each DemEventId: status and debounce start time
STATIC_AL tDem_aEventStatus_type         Dem_astEventStatus[DEM_CONFIG_ENTRY_MAX];

STATIC_AL Dem_tsDiagFaultState           Dem_asDiagFaultState[DEM_CONFIG_ENTRY_MAX];

// Global variable which keeps status test for each Alec
STATIC_AL Dem_tsStatusTest               Dem_asStatusTest[DEM_CONFIG_ENTRY_MAX];

// Global flag which indicate if Dem is ready for usage or not: TRUE - Dem can be use, FALSE - Dem is not available yet
STATIC_AL boolean                        Dem_boInitializationDone = FALSE;

// Global variable which indicate the side of headlamp: 1 - left, 2 - right
STATIC_AL uint8                          Dem_ucSideModifier;

// Global flag which indicates start-up sequence when it is true
STATIC_AL boolean                        Dem_boStartupStat = TRUE;

//// Global flag which indicates if a new Nvm Write is needed
STATIC_AL boolean                        Dem_boNvmDirty = FALSE;

//global flag which indicates 0x85 service is activated/deactivated
STATIC_AL boolean LockDTC = TRUE;
STATIC_AL boolean Dem_boInitEvent = FALSE;


//=============================================================================
// Definitions
//=============================================================================

// Configuration of the flag to be set when a request for clearing operation is performed
#define DEM_STATUS_CONFIG_CLEAR                     (DEM_STATUS_TEST_NOT_COMPLETED_THIS_CYCLE | DEM_STATUS_TEST_NOT_COMPLETED_SINCE_CLEAR | DEM_STATUS_TEST_PASSED)

// Configuration of the bits status for nvm blovk to be set in case of test failed
#define DEM_STATUS_SET_NVM_TEST_FAILED              (DEM_STATUS_TEST_FAILED_THIS_CYCLE | DEM_STATUS_TEST_FAILED_SINCE_CLEAR | DEM_STATUS_TEST_FAILED)

// Configuration of the bits status to be set in case of test failed
#define DEM_STATUS_SET_TEST_FAILED                  (DEM_STATUS_SET_NVM_TEST_FAILED | DEM_STATUS_PENDING_DTC | DEM_STATUS_CONFIRMED_DTC)

// Configuration bits status to be set in case the test prefailed
#define DEM_STATUS_RESET_TEST_PREFAILED             (DEM_STATUS_TEST_PASSED | DEM_STATUS_TEST_PREPASSED)

// Configuration of the bits status to be reset in case of test failed
#define DEM_STATUS_RESET_TEST_FAILED                (DEM_STATUS_RESET_TEST_PREFAILED | DEM_STATUS_TEST_PREFAILED | DEM_STATUS_TEST_NOT_COMPLETED_SINCE_CLEAR | DEM_STATUS_TEST_NOT_COMPLETED_THIS_CYCLE)

// Configuration bits status to be reset in case the test passed
#define DEM_STATUS_RESET_TEST_PASSED                (DEM_STATUS_TEST_FAILED | DEM_STATUS_TEST_PREPASSED | DEM_STATUS_TEST_PREFAILED | DEM_STATUS_TEST_NOT_COMPLETED_SINCE_CLEAR | DEM_STATUS_TEST_NOT_COMPLETED_THIS_CYCLE)

// Configuration bits status for nvm block to be reset in case the test passed
#define DEM_STATUS_RESET_NVM_TEST_PASSED            (DEM_STATUS_TEST_NOT_COMPLETED_SINCE_CLEAR | DEM_STATUS_TEST_FAILED)

// These two bits shall be set at the begining of an operation cycle
#define DEM_STATUS_CONFIG_INITIALIZATION            (DEM_STATUS_TEST_NOT_COMPLETED_THIS_CYCLE | DEM_STATUS_TEST_PASSED)

// Configuration bits status to be set in case the test prepassed
#define DEM_STATUS_RESET_TEST_PREPASSED             (DEM_STATUS_TEST_FAILED | DEM_STATUS_TEST_PREFAILED)

// Number of Alecs to be processed in one cycle
#define DEM_MAX_ALECS_NUMBER                        120u

// Diag Fault Present Flag
#define DEM_JDD_FAULT_PRESENT                       0x01u

// Diag Fault Present Confirmed Flag
#define DEM_JDD_FAULT_PRESENT_CONFIRMED             0x02u

// Diag Fault Absent Flag
#define DEM_JDD_FAULT_ABSENT                        0x04u

// Diag Fault Absent Confirmed Flag
#define DEM_JDD_FAULT_ABSENT_CONFIRMED              0x08u

// Diag Fault Present Confirmed Dtc Flag
#define DEM_JDD_FAULT_PRESENT_CONFIRMED_DTC         0x10u

// Diag Fault Present Confirmed Dtc Flag
#define DEM_JDD_FAULT_ABSENT_CONFIRMED_DTC          0x20u

// Clear present condition flags
#define DEM_JDD_CLEAR_CONFIRMED_PRESENT_CONDITIONS  (uint8)(~(DEM_JDD_FAULT_PRESENT | DEM_JDD_FAULT_PRESENT_CONFIRMED))

// Set absent condition flags
#define DEM_JDD_SET_CONFIRMED_ABSENT_CONDITIONS     (uint8)(DEM_JDD_FAULT_ABSENT_CONFIRMED | DEM_JDD_FAULT_ABSENT_CONFIRMED_DTC)

// Clear absent condition flags
#define DEM_JDD_CLEAR_CONFIRMED_ABSENT_CONDITIONS   (uint8)(~(DEM_JDD_FAULT_ABSENT | DEM_JDD_FAULT_ABSENT_CONFIRMED))

// Set present condition flags
#define DEM_JDD_SET_CONFIRMED_PRESENT_CONDITIONS    (uint8)(DEM_JDD_FAULT_PRESENT_CONFIRMED | DEM_JDD_FAULT_PRESENT_CONFIRMED_DTC)

//============================================================================
// Prototypes
//=============================================================================
STATIC_AL void    Dem_TriggerCallbackFunctions        (uint16 unEventIdx);
STATIC_AL void    Dem_ProcessEvent                    (uint16 unEventIndex, uint8 ucEventStatus);
STATIC_AL void    Dem_PreProcessEvent                 (uint16 unPreEventIndex, uint8 ucPreEventStatus);
STATIC_AL void    Dem_DiagProcessEvent                (uint16 unEventId, uint8 ucEventStatus);
STATIC_AL void    Dem_DiagProcessEvent_Pass_TimeOut   (uint16 unEventId);
STATIC_AL void    Dem_DiagProcessEvent_Pass_Cnt       (uint16 unEventId);
STATIC_AL void    Dem_DiagProcessEvent_Fail_TimeOut   (uint16 unEventId);
STATIC_AL void    Dem_DiagProcessEvent_Fail_Cnt       (uint16 unEventId);
STATIC_AL void    Dem_ResetArrays                     (uint16 unDemIdx);

//-----------------------------------------------------------------------------
/// \brief  Dem_Init
///
/// \descr  Initialisation of DEM module. It has to be called once after startup. Nvm must be ready and Nvm data must be valid at this time
///
/// \param   void
///
/// \return  void 
//-----------------------------------------------------------------------------
void Dem_Init(void)
{
  // Index variable
  uint16 unIdx;
  // HeadLamp side
  teRte_MountingSide eMountingSide = { 0 };

  // Browse the table with ALECs or DEM event IDs
  for (unIdx = 0u; unIdx < DEM_CONFIG_ENTRY_MAX; unIdx++)
  {

    if ((NvmBlockDemData.aucStatus[unIdx] &  DEM_STATUS_TEST_FAILED) == 0u)
    {
      Dem_asDiagFaultState[unIdx].ucDiagFaultState = DEM_JDD_FAULT_ABSENT_CONFIRMED;
    }
    else
    {
      // Set present flag
      Dem_asDiagFaultState[unIdx].ucDiagFaultState = Dem_asDiagFaultState[unIdx].ucDiagFaultState | DEM_JDD_SET_CONFIRMED_PRESENT_CONDITIONS;
    }
    
    // Initialized the status request with passed in order to not load the first cycle too much
    Dem_asStatusTest[unIdx].ucResult = DEM_EVENT_STATUS_PASSED;

    // Initialize the satus bits
    Dem_astEventStatus[unIdx].unStatus = DEM_STATUS_CONFIG_INITIALIZATION;

    // Check if alec test did not failed in the previous cycle and if aging counter is greater than 0
    if (((NvmBlockDemData.aucStatus[unIdx] & (uint8)DEM_STATUS_TEST_FAILED_THIS_CYCLE) == 0u) && (NvmBlockDemData.aucAgingCounter[unIdx] > 0u))
    {
      // Decrement the aging counter
      NvmBlockDemData.aucAgingCounter[unIdx]--;

      // Set dirty flag only if status has changed
      Dem_boNvmDirty = TRUE;
    }
    else
    {
      // Nothing to do because ALEC failed in the previous operation cycle
    }

    // Check if there has passed 40 operation cycle with ALEC test passed
    if (NvmBlockDemData.aucAgingCounter[unIdx] > 0u)
    {
      // It has not passed 40 operation cycle in which the ALEC test passed, therefore the ALEC status can be confirmed
      Dem_astEventStatus[unIdx].unStatus = Dem_astEventStatus[unIdx].unStatus | DEM_STATUS_CONFIRMED_DTC;

      if ((NvmBlockDemData.aucStatus[unIdx] & DEM_STATUS_TEST_FAILED_THIS_CYCLE) != 0u)
      {
        // The ALEC has failed in the previous operation Cycle
        Dem_astEventStatus[unIdx].unStatus = Dem_astEventStatus[unIdx].unStatus | DEM_STATUS_PENDING_DTC;

        // Reset the TEST_FAILED_THIS_CYCLE flag
        NvmBlockDemData.aucStatus[unIdx] = NvmBlockDemData.aucStatus[unIdx] & (uint8)(~DEM_STATUS_TEST_FAILED_THIS_CYCLE);

        // Set dirty flag only if status has changed
        Dem_boNvmDirty = TRUE;
      }
      else
      {
        // The ALEC test passed in the previous operation cycle
      }
    }
    else
    {
      // It has passed 40 operation cycle in which the ALEC test failed
    }
  }

  // update NVM
  if (Dem_boNvmDirty != FALSE)
  {
    Dem_boNvmDirty = (NvM_WriteBlock((uint16)NvmBlockDemDataId, NULL_PTR) != E_OK ) ? TRUE : FALSE;
  }
  else
  {
    // nothing to do
  }
  
  // Read MountingSide RTE port
  (void)Rte_Read_IoHwAbUser_GetMountingSide(&eMountingSide);
  
  // Get the current mounting side, cast from enum to uint8
  Dem_ucSideModifier = (uint8)eMountingSide;

  // Check if the mounting side value is valid, cast from enum to uint8
  if (Dem_ucSideModifier == (uint8)eMountedUndef)
  {
    // In case the side can not be detected set right as the default one, cast from enum to uint8
    Dem_ucSideModifier = (uint8)eMountedRight;
  }
  else
  {
    // Side detection succeeded, therefore nothing to do
  }

  // Increase by 1 in order to calculate right value the dem event id in Dem_SetEventStatus
  Dem_ucSideModifier++;

  // Signalize to Dem_Task that intialization has been performed successfully
  Dem_boInitializationDone = TRUE;
}


//-----------------------------------------------------------------------------
/// \brief  Dem_TriggerCallbackFunctions
///
/// \descr  This function trigger the following callback functions: 
///  notify_custom and (notify_passed  or notify_failed)
///
/// \param   unEventIndex
///
/// \return  void 
//-----------------------------------------------------------------------------
STATIC_AL void Dem_TriggerCallbackFunctions(uint16 unEventIdx)
{
  // Check if DEM_EVENT_STATUS_PASSED_IMMEDIATELY is the case
  if (((Dem_astEventStatus[unEventIdx].unStatus & DEM_STATUS_TEST_PASSED) != 0u) && ((Dem_astEventStatus[unEventIdx].unStatus & DEM_STATUS_TEST_FAILED) == 0u))
  {
    // Check if the callback is different than Null
    if (dem_config[unEventIdx].notify_passed != NULL_PTR)
    {
      dem_config[unEventIdx].notify_passed(dem_config[unEventIdx].event_id, TRUE);
    }
    else
    {
      // There is no valid callback, therefore nothing to do
    }
  }
  // Check if DEM_EVENT_STATUS_FAILED_IMMEDIATELY is the case
  else if (((Dem_astEventStatus[unEventIdx].unStatus & DEM_STATUS_TEST_PASSED) == 0u) && ((Dem_astEventStatus[unEventIdx].unStatus & DEM_STATUS_TEST_FAILED) != 0u))
  {
    //Check if the callback is different than null
    if (dem_config[unEventIdx].notify_failed != NULL_PTR)
    {
      dem_config[unEventIdx].notify_failed(dem_config[unEventIdx].event_id, FALSE);
    }
    else
    {
      //There is no valid callback, therefore nothing to do
    }
  }
  else
  {
    // Not a valid case, therefore nothing to do
  }

  //Check if the callback is different than Null
  if (dem_config[unEventIdx].notify_custom != NULL_PTR)
  {
    dem_config[unEventIdx].notify_custom(dem_config[unEventIdx].event_id, (uint8)Dem_astEventStatus[unEventIdx].unStatus);
  }
  else
  {
    //There is no valid callback, therefore nothing to do
  }
}


//-----------------------------------------------------------------------------
/// \brief  Dem_ProcessEvent
///
/// \descr  This function set/reset all the flags for ALEC(unEventIndex + 1) according with ucEventStatus value after maturation/dematuration time expired
///         Trigger ErrCust for setting the corresponding DTC 
///
/// \param   unEventIndex, ucEventStatus
///
/// \return  void 
//-----------------------------------------------------------------------------
STATIC_AL void Dem_ProcessEvent(uint16 unEventIndex, uint8 ucEventStatus)
{
  switch (ucEventStatus)
  {
  case DEM_EVENT_STATUS_PASSED_IMMEDIATELY:
    // Set the test passed flag
    Dem_astEventStatus[unEventIndex].unStatus = Dem_astEventStatus[unEventIndex].unStatus | DEM_STATUS_TEST_PASSED;

    // Reset the TEST_FAILED, TEST_PREPASSED, TEST_PREFAILED, TEST_NOT_COMPLETED_SINCE_CLEAR and TEST_NOT_COMPLETED_THIS_CYCLE flags
    Dem_astEventStatus[unEventIndex].unStatus = Dem_astEventStatus[unEventIndex].unStatus & (uint16)(~DEM_STATUS_RESET_TEST_PASSED);

    // Stop the timer
    Dem_astEventStatus[unEventIndex].ulDebounceStartTime = 0u;

    //Check if pending bit can be clear
    if (NvmBlockDemData.aucAgingCounter[unEventIndex] == AGING_COUNTER_MAX - 1u)
    {
      //PRQA S 4399 1 //An expression which is the result of a ~ or << operation has been cast to a wider type; Same problem as the one from line 274, but the cast here don't remove warning
      Dem_astEventStatus[unEventIndex].unStatus = Dem_astEventStatus[unEventIndex].unStatus & (uint16)(~DEM_STATUS_PENDING_DTC);
    }
    else
    {
      // Pending bit is not needed to be clear, therefore nothing to do
    }

    // Check if the test failed or test is not completed since clear in the previous operation cycle
    if ((NvmBlockDemData.aucStatus[unEventIndex] & DEM_STATUS_RESET_NVM_TEST_PASSED) != 0u)
    {
      NvmBlockDemData.aucStatus[unEventIndex] = NvmBlockDemData.aucStatus[unEventIndex] & (uint8)(~DEM_STATUS_RESET_NVM_TEST_PASSED);

      // Set dirty flag only if status has changed
      Dem_boNvmDirty = TRUE;
    }
    else
    {
      // Flags are not needed to be clear, therefore nothing to do
    }
    break;

  case DEM_EVENT_STATUS_FAILED_IMMEDIATELY:
    // Set TEST_FAILED, TEST_FAILED_THIS_CYCLE, TEST_FAILED_SINCE_CLEAR, PENDING_DTC, CONFIRMED_DTC flags
    Dem_astEventStatus[unEventIndex].unStatus = Dem_astEventStatus[unEventIndex].unStatus | (uint16)DEM_STATUS_SET_TEST_FAILED;

    // Reset TEST_PASSED, TEST_PREPASSED, TEST_PREFAILED, TEST_NOT_COMPLETED_SINCE_CLEAR, TEST_NOT_COMPLETED_THIS_CYCLE flags
    Dem_astEventStatus[unEventIndex].unStatus = Dem_astEventStatus[unEventIndex].unStatus &  (uint16)(~DEM_STATUS_RESET_TEST_FAILED);

    // Stop the timer
    Dem_astEventStatus[unEventIndex].ulDebounceStartTime = 0u;

    // Process Nvm mirror block
    {

      // Aging counter is set to maximum value
      NvmBlockDemData.aucAgingCounter[unEventIndex] = AGING_COUNTER_MAX;

      // Set TEST_FAILED_THIS_CYCLE, TEST_FAILED_SINCE_CLEAR and TEST_FAILED flags
      NvmBlockDemData.aucStatus[unEventIndex] = NvmBlockDemData.aucStatus[unEventIndex] | (uint8)DEM_STATUS_SET_NVM_TEST_FAILED;

      // Clear TEST_NOT_COMPLETED_SINCE_CLEAR flag
      NvmBlockDemData.aucStatus[unEventIndex] = NvmBlockDemData.aucStatus[unEventIndex] & (uint8)(~DEM_STATUS_TEST_NOT_COMPLETED_SINCE_CLEAR);

      // Set dirty flag only if status has changed
      Dem_boNvmDirty = TRUE;
    }
    break;

  default:
    // unknown event, ignore
    break;
  }

  // For current implementaion trigger only notify_custom
  Dem_TriggerCallbackFunctions(unEventIndex);
}


//-----------------------------------------------------------------------------
/// \brief  Dem_PreProcessEvent
///
/// \descr  This function starts the debounce timer and set/reset all the flags for ALEC corresponding to unPreEventIndex
///         
///
/// \param   unPreEventIndex, ucPreEventStatus
///
/// \return  void 
//-----------------------------------------------------------------------------
STATIC_AL void Dem_PreProcessEvent(uint16 unPreEventIndex, uint8 ucPreEventStatus)
{
  switch (ucPreEventStatus)
  {
  case DEM_EVENT_STATUS_PREPASSED:

    // Check if debounce time was set; Check if test passed function was called
    if ((dem_config[unPreEventIndex].debounce_time_passed != 0u) && ((Dem_astEventStatus[unPreEventIndex].unStatus & (DEM_STATUS_TEST_PREPASSED | DEM_STATUS_TEST_PASSED)) == 0u))
    {
      // (Re)start debounce timer
      Dem_astEventStatus[unPreEventIndex].ulDebounceStartTime = TimerGetTick();
    }
    else
    {
      // Conditions are not ok or/and there is no debounce time set; Test passed function was already called at least once      
    }

    // Set TEST_PREPASSED flag
    Dem_astEventStatus[unPreEventIndex].unStatus = Dem_astEventStatus[unPreEventIndex].unStatus | DEM_STATUS_TEST_PREPASSED;

    // Clear TEST_FAILED and TEST_PREFAILED flags
    Dem_astEventStatus[unPreEventIndex].unStatus = Dem_astEventStatus[unPreEventIndex].unStatus & (uint16)(~DEM_STATUS_RESET_TEST_PREPASSED);
    break;

  case DEM_EVENT_STATUS_PREFAILED:

    // Check if debounce time was set; Test failed function was already called at least once
    if ((dem_config[unPreEventIndex].debounce_time_failed != 0u) && ((Dem_astEventStatus[unPreEventIndex].unStatus & (DEM_STATUS_TEST_PREFAILED | DEM_STATUS_TEST_FAILED)) == 0u))
    {

      // (Re)start debounce timer
      Dem_astEventStatus[unPreEventIndex].ulDebounceStartTime = TimerGetTick();
    }
    else
    {
      // Conditions are not ok or/and there is no debounce time set 
    }

    // Set TEST_PREFAILED flag
    Dem_astEventStatus[unPreEventIndex].unStatus = Dem_astEventStatus[unPreEventIndex].unStatus | DEM_STATUS_TEST_PREFAILED;

    // Clear TEST_PASSED and TEST_PREPASSED flags
    Dem_astEventStatus[unPreEventIndex].unStatus = Dem_astEventStatus[unPreEventIndex].unStatus & (uint16)(~DEM_STATUS_RESET_TEST_PREFAILED);

    break;

  default:
    // unknown event, ignore
    break;
  }
}


//-----------------------------------------------------------------------------
/// \brief Dem_DiagProcessEvent_Pass_TimeOut
///
/// \descr Diagnostic passed condition when confirmation is done based on timer
///
/// \param  unEventId: Alec Id
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Dem_DiagProcessEvent_Pass_TimeOut(uint16 unEventId)
{
  // is fault marked as fault absent during DiagMuxOn
  if ((Dem_asDiagFaultState[unEventId].ucDiagFaultState & DEM_JDD_FAULT_ABSENT) == 0u)
  {
    // clear present flag (fix)
    Dem_asDiagFaultState[unEventId].ucDiagFaultState = Dem_asDiagFaultState[unEventId].ucDiagFaultState & (uint8)(~DEM_JDD_FAULT_PRESENT);
    // Set absent flag
    Dem_asDiagFaultState[unEventId].ucDiagFaultState = Dem_asDiagFaultState[unEventId].ucDiagFaultState | DEM_JDD_FAULT_ABSENT;
    // Take system time
    Dem_asDiagFaultState[unEventId].ulDiagConfirmedTimer = TimerGetTick();

    dem_config[unEventId].condition_absent(unEventId);

  }
  else
  {
    // fault absent already
  }

  // is fault marked as absent and not confirmed absent and there is time-out on time passed (debounce)
   //PRQA S 3415 2 //The right hand operand of a logical && operator is only evaluated if the left hand operand evaluates to 1 ("true") -> intended
  if ((TimerGetTimeSince(Dem_asDiagFaultState[unEventId].ulDiagConfirmedTimer) >= FT_MSEC(dem_config[unEventId].debounce_time_passed)) &&
    //(((Dem_asDiagFaultState[unEventId].ucDiagFaultState & DEM_JDD_FAULT_PRESENT_CONFIRMED) != 0u) && (Dem_asDiagFaultState[unEventId].ucDiagFaultState & DEM_JDD_FAULT_ABSENT) != 0u) && ((Dem_asDiagFaultState[unEventId].ucDiagFaultState & DEM_JDD_FAULT_ABSENT_CONFIRMED) == 0u))
    (((Dem_asDiagFaultState[unEventId].ucDiagFaultState & (DEM_JDD_FAULT_PRESENT_CONFIRMED | DEM_JDD_FAULT_ABSENT)) == (DEM_JDD_FAULT_PRESENT_CONFIRMED | DEM_JDD_FAULT_ABSENT)) && ((Dem_asDiagFaultState[unEventId].ucDiagFaultState & DEM_JDD_FAULT_ABSENT_CONFIRMED) == 0u)))
  {
    // confirmed absent custom callback (Jdd send Bsi data info on Can)
    if (dem_config[unEventId].condition_confirmed_absent != NULL_PTR)
    {
      dem_config[unEventId].condition_confirmed_absent(unEventId);
    }
    else
    {
      // skip callback call if NULL_PTR
    }
    // set absent confirmed flag
    Dem_asDiagFaultState[unEventId].ucDiagFaultState = Dem_asDiagFaultState[unEventId].ucDiagFaultState | DEM_JDD_SET_CONFIRMED_ABSENT_CONDITIONS;
    // clear present confirmed condition
    Dem_asDiagFaultState[unEventId].ucDiagFaultState = Dem_asDiagFaultState[unEventId].ucDiagFaultState & (uint8)(~DEM_JDD_FAULT_PRESENT_CONFIRMED);
  }
  else
  {
    // fault doesn't match to the conditions
  }
}


//-----------------------------------------------------------------------------
/// \brief Dem_DiagProcessEvent_Pass_Cnt
///
/// \descr Diagnostic passed condition when confirmation is done based on counter
///
/// \param  unEventId: Alec Id
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Dem_DiagProcessEvent_Pass_Cnt(uint16 unEventId)
{
  // is fault marked as fault absent during DiagMuxOn
  if ((Dem_asDiagFaultState[unEventId].ucDiagFaultState & DEM_JDD_FAULT_PRESENT_CONFIRMED) != 0u)
  {
    // set initial fault counter value to the maximum - dec step
    Dem_asDiagFaultState[unEventId].unDiagFaultCnt = ((dem_config[unEventId].debounce_cnt_max - dem_config[unEventId].debounce_cnt_dec) > dem_config[unEventId].debounce_cnt_min) ?
      (dem_config[unEventId].debounce_cnt_max - dem_config[unEventId].debounce_cnt_dec) : dem_config[unEventId].debounce_cnt_min;
    if (dem_config[unEventId].condition_absent != NULL_PTR)
    {
      // absent custom callback
      dem_config[unEventId].condition_absent(unEventId);   // Deh_DisappearanceDetected
    }
    else
    {
      // skip callback call if NULL_PTR
    }
    // clear present and confirmed present flags
    Dem_asDiagFaultState[unEventId].ucDiagFaultState = Dem_asDiagFaultState[unEventId].ucDiagFaultState & DEM_JDD_CLEAR_CONFIRMED_PRESENT_CONDITIONS;
    // Set absent flag
    Dem_asDiagFaultState[unEventId].ucDiagFaultState = Dem_asDiagFaultState[unEventId].ucDiagFaultState | DEM_JDD_FAULT_ABSENT;
  }
  else
  {
    // Continue to decrement fault counter
    Dem_asDiagFaultState[unEventId].unDiagFaultCnt = (Dem_asDiagFaultState[unEventId].unDiagFaultCnt > (dem_config[unEventId].debounce_cnt_min + dem_config[unEventId].debounce_cnt_dec)) ?
      (Dem_asDiagFaultState[unEventId].unDiagFaultCnt - dem_config[unEventId].debounce_cnt_dec) : dem_config[unEventId].debounce_cnt_min;

    // Clear present flag
    Dem_asDiagFaultState[unEventId].ucDiagFaultState = Dem_asDiagFaultState[unEventId].ucDiagFaultState & (uint8)~DEM_JDD_FAULT_PRESENT;
  }

  // if fault is absent and not confirmed absent and its fault counter reaches minimum value
  if (((Dem_asDiagFaultState[unEventId].ucDiagFaultState & DEM_JDD_FAULT_ABSENT_CONFIRMED) == 0u) && ((Dem_asDiagFaultState[unEventId].ucDiagFaultState & DEM_JDD_FAULT_ABSENT) != 0u) &&
    ((Dem_asDiagFaultState[unEventId].ucDiagFaultState & DEM_JDD_FAULT_PRESENT) == 0u) && (Dem_asDiagFaultState[unEventId].unDiagFaultCnt == dem_config[unEventId].debounce_cnt_min))
  {
    if (dem_config[unEventId].condition_confirmed_absent != NULL_PTR)
    {
      // confirmed absent custom callback (Jdd send Bsi data info on Can)
      dem_config[unEventId].condition_confirmed_absent(unEventId);  // Deh_DisappearanceConfirmed
    }
    else
    {
      // skip callback call if NULL_PTR
    }
    // set absent confirmation flag and DTC condition for faults based on DiagMux and counters
    Dem_asDiagFaultState[unEventId].ucDiagFaultState = Dem_asDiagFaultState[unEventId].ucDiagFaultState | DEM_JDD_SET_CONFIRMED_ABSENT_CONDITIONS;
  }
  else
  {
    // fault doesn't match to the conditions
  }
}


//-----------------------------------------------------------------------------
/// \brief Dem_DiagProcessEvent_Fail_TimeOut
///
/// \descr Diagnostic fail condition when confirmation is done based on timers
///
/// \param  unEventId: Alec Id
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Dem_DiagProcessEvent_Fail_TimeOut(uint16 unEventId)
{
  // is fault marked as fault present during DiagMuxOn
  if ((Dem_asDiagFaultState[unEventId].ucDiagFaultState & DEM_JDD_FAULT_PRESENT) == 0u)
  {
    if (dem_config[unEventId].condition_present != NULL_PTR)
    {
      // absent custom callback (Jdd freeze Bsi data info)
      dem_config[unEventId].condition_present(unEventId);  // Deh_AppearanceDetected
    }
    else
    {
      // skip callback call if NULL_PTR
    }
    // clear presend and confirmed absent flags
    Dem_asDiagFaultState[unEventId].ucDiagFaultState = Dem_asDiagFaultState[unEventId].ucDiagFaultState & DEM_JDD_CLEAR_CONFIRMED_ABSENT_CONDITIONS;
    // Set present flag
    Dem_asDiagFaultState[unEventId].ucDiagFaultState = Dem_asDiagFaultState[unEventId].ucDiagFaultState | DEM_JDD_FAULT_PRESENT;
    // Take system time
    Dem_asDiagFaultState[unEventId].ulDiagConfirmedTimer = TimerGetTick();
  }
  else
  {
    // fault present already
  }

  // is fault marked as present and not confirmed present and there is time-out on time failed (debounce)
  //PRQA S 3415 2 //The right hand operand of a logical && operator is only evaluated if the left hand operand evaluates to 1 ("true") -> intended
  if ((TimerGetTimeSince(Dem_asDiagFaultState[unEventId].ulDiagConfirmedTimer) >= FT_MSEC(dem_config[unEventId].debounce_time_failed)) &&
    ((Dem_asDiagFaultState[unEventId].ucDiagFaultState & DEM_JDD_FAULT_PRESENT) != 0u) && ((Dem_asDiagFaultState[unEventId].ucDiagFaultState & DEM_JDD_FAULT_PRESENT_CONFIRMED) == 0u))
  {
    if (dem_config[unEventId].condition_confirmed_present != NULL_PTR)
    {
      // confirmed present custom callback (Jdd send Bsi data info on Can)
      dem_config[unEventId].condition_confirmed_present(unEventId); // Deh_AppearanceConfirmed
    }
    else
    {
      // skip callback call if NULL_PTR
    }
    // set present confirmed flag
    Dem_asDiagFaultState[unEventId].ucDiagFaultState = Dem_asDiagFaultState[unEventId].ucDiagFaultState | DEM_JDD_SET_CONFIRMED_PRESENT_CONDITIONS;
  }
  else
  {
    // fault doesn't match to the conditions
  }
}


//-----------------------------------------------------------------------------
/// \brief Dem_DiagProcessEvent_Fail_Cnt
///
/// \descr Diagnostic fail condition when confirmation is done based on counters
///
/// \param  unEventId: Alec Id
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Dem_DiagProcessEvent_Fail_Cnt(uint16 unEventId)
{
  // is fault marked as fault present during DiagMuxOn
  if ((Dem_asDiagFaultState[unEventId].ucDiagFaultState & DEM_JDD_FAULT_ABSENT_CONFIRMED) != 0u)
  {
    // set initial fault counter value to the minimum + inc step
    Dem_asDiagFaultState[unEventId].unDiagFaultCnt = ((dem_config[unEventId].debounce_cnt_min + dem_config[unEventId].debounce_cnt_inc) < dem_config[unEventId].debounce_cnt_max) ?
      (dem_config[unEventId].debounce_cnt_min + dem_config[unEventId].debounce_cnt_inc) : dem_config[unEventId].debounce_cnt_max;
    if (dem_config[unEventId].condition_present != NULL_PTR)
    {
      // present custom callback
      dem_config[unEventId].condition_present(unEventId);   // Deh_AppearanceDetected
    }
    else
    {
      // skip callback call if NULL_PTR
    }
    // clear absent and confirmed present flags
    Dem_asDiagFaultState[unEventId].ucDiagFaultState = Dem_asDiagFaultState[unEventId].ucDiagFaultState & DEM_JDD_CLEAR_CONFIRMED_ABSENT_CONDITIONS;
    // set present flag
    Dem_asDiagFaultState[unEventId].ucDiagFaultState = Dem_asDiagFaultState[unEventId].ucDiagFaultState | DEM_JDD_FAULT_PRESENT;
  }
  else
  {
    // Continue to increment fault counter
    Dem_asDiagFaultState[unEventId].unDiagFaultCnt = (Dem_asDiagFaultState[unEventId].unDiagFaultCnt < (dem_config[unEventId].debounce_cnt_max - dem_config[unEventId].debounce_cnt_inc)) ?
      (Dem_asDiagFaultState[unEventId].unDiagFaultCnt + dem_config[unEventId].debounce_cnt_inc) : dem_config[unEventId].debounce_cnt_max;
    // Set present flag
    Dem_asDiagFaultState[unEventId].ucDiagFaultState = Dem_asDiagFaultState[unEventId].ucDiagFaultState | DEM_JDD_FAULT_PRESENT;
  }

  // if fault is present and not confirmed present and its fault counter reaches maximum value
  if (((Dem_asDiagFaultState[unEventId].ucDiagFaultState & DEM_JDD_FAULT_PRESENT_CONFIRMED) == 0u) && ((Dem_asDiagFaultState[unEventId].ucDiagFaultState & DEM_JDD_FAULT_PRESENT) != 0u) &&
    ((Dem_asDiagFaultState[unEventId].ucDiagFaultState & DEM_JDD_FAULT_ABSENT) == 0u) && (Dem_asDiagFaultState[unEventId].unDiagFaultCnt == dem_config[unEventId].debounce_cnt_max))
  {
    if (dem_config[unEventId].condition_confirmed_present != NULL_PTR)
    {
      // confirmed present custom callback (Jdd send Bsi data info on Can)
      dem_config[unEventId].condition_confirmed_present(unEventId);   // Deh_AppearanceConfirmed
    }
    else
    {
      // skip callback call if NULL_PTR
    }
    // set absent confirmation flag and DTC condition for faults based on DiagMux and counters
    Dem_asDiagFaultState[unEventId].ucDiagFaultState = Dem_asDiagFaultState[unEventId].ucDiagFaultState | DEM_JDD_SET_CONFIRMED_PRESENT_CONDITIONS;
  }
  else
  {
    // fault doesn't match to the conditions
  }
}


//-----------------------------------------------------------------------------
/// \brief Dem_DiagProcessEvent
///
/// \descr This function monitors the fault during DiagMuxOn and set callbacks for first events of absent/present
///        and for conditions of confirmed absent/present
///
/// \param  unEventId: Alec Id
/// \param  ucEventStatus: Event status (absent or present)
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Dem_DiagProcessEvent(uint16 unEventId, uint8 ucEventStatus)
{
  switch (ucEventStatus)
  {
    // Fault present during DiagMuxOn
  case DEM_EVENT_STATUS_PASSED:
    // is fault marked for Jdd reporting and confirmation is based on time-out
    if ((dem_config[unEventId].debounce_time_passed != 0u) && (dem_config[unEventId].jdd_reporter != FALSE))
    {
      Dem_DiagProcessEvent_Pass_TimeOut(unEventId);
    }
    // is fault marked for Jdd reporting and for confirmation is not based on time-out (counters)
    else if (dem_config[unEventId].jdd_reporter != FALSE)
    {
      Dem_DiagProcessEvent_Pass_Cnt(unEventId);
    }
    else
    {
      // fault doesn't match to the conditions
    }
    break;
  case DEM_EVENT_STATUS_FAILED:
    // is fault marked for Jdd reporting and confirmation is based on time-out
    if ((dem_config[unEventId].debounce_time_failed != 0u) && (dem_config[unEventId].jdd_reporter != FALSE))
    {
      Dem_DiagProcessEvent_Fail_TimeOut(unEventId);
    }
    // is fault marked for Jdd reporting and for confirmation is not based on time-out (counters)
    else if (dem_config[unEventId].jdd_reporter != FALSE)
    {
      Dem_DiagProcessEvent_Fail_Cnt(unEventId);
    }
    else
    {
      // fault doesn't match to the conditions
    }
    break;
  default:
    // Other fault status is prohibited, nothing to do
    break;
  }
}

//-----------------------------------------------------------------------------
/// \brief Dem_Diag_LockDTC
///
/// \descr This function monitors the fault during DiagMuxOn and set callbacks for first events of absent/present
///        and for conditions of confirmed absent/present
///
/// \param  boolean: Enable stroing DTC
///
/// \return void
void Dem_Diag_LockDTC(boolean boEnableDTC)
{
  LockDTC = (boEnableDTC != FALSE) ? TRUE : FALSE;
}

//-----------------------------------------------------------------------------
/// \brief  Dem_SetEventStatus
///
/// \descr  This function is called each time for a test failed/passed in the module which report errors
///         
///
/// \param   unAlecId, ucTestStatus
///
/// \return  void 
//-----------------------------------------------------------------------------
void Dem_SetEventStatus(uint16 unAlecId, uint8 ucTestStatus)
{
  // Dem index
  uint16 unDemEventId;

  // Get Dig Mux from SysMonRx_Callbacks (this will keep last value known for a time  DiagMux_Prod)
  boolean boDiagMuxOn = FALSE;
  //Get DiagMuxState
  SysMonRx_Callbacks_GetDiagMuxState(&boDiagMuxOn);
  //Get InterMemoDef State
  tsRte_SysMon_LifePhases sLifePhases;
  (void)Rte_Read_SysMon_LifePhases(&sLifePhases);

  NM_ModeType NMMode;
  // Get life phases from the NM
  (void)NM_GetMode(&NMMode);

  // Get Electronic Integration Mode
  LEIM_TE_CurrentEIMode EIMode = EAPI_GetCurrentEIMode();

  boolean boElecIntStatus = (EIMode != LEIM_E_ACTIVE) ? FALSE : TRUE;

  // Find the according dem event id of the unAlecId
  unDemEventId = unAlecId - ((uint16)Dem_ucSideModifier) % 2u;

  // verifiy if the System is In LIMP HOME and 036 frame is lost
  boolean NMModeDTC = (NMMode == LIMP_HOME_MODE) && (unAlecId == (uint16)HS6_COMMANDES_VSM_036_ID) ? TRUE : FALSE;

  // Get ElecInt and Dem Init status, further actions are not allowed outside these cases
  if (((Dem_boInitEvent != FALSE) || ((boElecIntStatus == FALSE) && (Dem_boInitializationDone != FALSE) && (boDiagMuxOn != FALSE) && (LockDTC == TRUE) && (NMMode != LIMP_HOME_MODE) && (sLifePhases.eInterdMemoDef != eMemorisationForbidden)) || (NMModeDTC == TRUE)))
  {
    // Call Diag (for Jdd Processing)
    Dem_DiagProcessEvent(unDemEventId, ucTestStatus);

    // Proced Dem in case of DiagMux active, StartUp Sequence or all the time Passed conition
    if ((ucTestStatus == DEM_EVENT_STATUS_PASSED) || (Dem_boStartupStat != FALSE))
    {
      // Check if it's the first call of the function with status request 'DEM_EVENT_STATUS_FAILED' OR if the number of call is greater than 1 check only if status is changed
      if ((Dem_asStatusTest[unDemEventId].ucResult != ucTestStatus) || ((Dem_asStatusTest[unDemEventId].boDoneThisCycle == FALSE) && (Dem_asStatusTest[unDemEventId].ucResult == DEM_EVENT_STATUS_FAILED)))
      {
        // Mark that the Dem_ReportErrorStatus function was called at least once for the current ALEC 
        Dem_asStatusTest[unDemEventId].boDoneThisCycle = TRUE;
        // Update the request Status
        Dem_asStatusTest[unDemEventId].ucResult = ucTestStatus;

        // Preprocess event
        Dem_PreProcessEvent(unDemEventId, ucTestStatus);
      }
      else if ((Dem_asStatusTest[unDemEventId].boDoneThisCycle == FALSE) && (Dem_asStatusTest[unDemEventId].ucResult == DEM_EVENT_STATUS_PASSED))
      {
        // Test passed is called for the first time, clear test not completed flag
        // PRQA S 4399 1 //An expression which is the result of a ~ or << operation has been cast to a wider type; Same problem as the one from line 274, but the cast here don't remove warning
        Dem_astEventStatus[unDemEventId].unStatus = Dem_astEventStatus[unDemEventId].unStatus & (uint16)(~DEM_STATUS_TEST_NOT_COMPLETED_THIS_CYCLE);

        // At this phase is not needed any debounce passed time measurement, therefore is needed to set DEM_STATUS_TEST_PASSED bit
        Dem_astEventStatus[unDemEventId].unStatus = Dem_astEventStatus[unDemEventId].unStatus | DEM_STATUS_TEST_PASSED;

        // Marked that the function was called at least once
        Dem_asStatusTest[unDemEventId].boDoneThisCycle = TRUE;

        // Process NVM blocks, check if the alec failed in the previous operation cycle
        if ((NvmBlockDemData.aucStatus[unDemEventId] & (DEM_STATUS_TEST_NOT_COMPLETED_SINCE_CLEAR | DEM_STATUS_TEST_FAILED)) != 0u)
        {

          NvmBlockDemData.aucStatus[unDemEventId] = NvmBlockDemData.aucStatus[unDemEventId] & (uint8)(~DEM_STATUS_TEST_NOT_COMPLETED_SINCE_CLEAR);

          NvmBlockDemData.aucStatus[unDemEventId] = NvmBlockDemData.aucStatus[unDemEventId] & (uint8)(~DEM_STATUS_TEST_FAILED);

          // Set dirty flag only if status has changed
          Dem_boNvmDirty = TRUE;
          }
          else
          {
            // ALEC test passed in the previous operation cycle, bits TEST_NOT_COMPLETED_SINCE_CLEAR and TEST_FAILED are already cleared, therefore nothing to do
          }

        // Preprocess event, Dem_TriggerCallbackFunctions will be called from rpDem_Cycle0
        Dem_PreProcessEvent(unDemEventId, ucTestStatus);
      }
      else
      {
        //The request status is unchanged as against previous call of the function, therefore nothing to do
      }
    }
    else
    {
      // Dem processing skiped outside above conditions
    }
    

  }
  else
  {
    // Dem and Jdd processing skiped outside above conditions
  }
  //PRQA S 5336 1 // STMIF = 5, Statement intended due function complexity
}


//-----------------------------------------------------------------------------
/// \brief  Dem_boEventPassed
///
/// \descr  This function checks if the Alec Id (unEventIdx + 1) given as parameter was passed or not
///         
///
/// \param   unEventIdx
///
/// \return  boolean 
//-----------------------------------------------------------------------------
boolean Dem_boEventPassed(uint16 unEventIdx)
{
  // Variable which shows if alec test is passed or not, by default is not passed
  boolean boTstPsd = FALSE;

  // Check if Alec test was passed
  if ((Dem_astEventStatus[unEventIdx].unStatus & DEM_STATUS_TEST_PASSED) != 0u)
  {
    // Test Alec is passed
    boTstPsd = TRUE;
  }
  else
  {
    // Test Alec is not passed, therefore nothing to do
  }

  return boTstPsd;
}


//-----------------------------------------------------------------------------
/// \brief  Dem_ClearAlec
///
/// \descr  This function clear all ALEC or ALEC corresponding with dem index
///  
///
/// \param   boAllAlecs, unDemIndex
///
/// \return  void 
//-----------------------------------------------------------------------------
void Dem_ClearAlec(boolean boAllAlecs, uint16 unDemIndex)
{
  if (boAllAlecs != FALSE)
  {
    for (uint16 unIdx = 0u; unIdx < DEM_CONFIG_ENTRY_MAX; ++unIdx)
    {
      // Reset Dem_astEventStatus, NvmBlockDemData and Dem_asStatusTest arrays to their initail values
      Dem_ResetArrays(unIdx);
    }
  }
  else // GroupOfDtc or a single DTC
  {
    // Reset Dem_astEventStatus, NvmBlockDemData and Dem_asStatusTest arrays to their initail values
    Dem_ResetArrays(unDemIndex);
  }
}


//-----------------------------------------------------------------------------
/// \brief  Dem_Task
///
/// \descr  This function is called cyclically
///
/// \param   void
///
/// \return  void 
//-----------------------------------------------------------------------------
void Dem_Task(void)
{
  // Value of thie variable represent the first dem event id for which Dem is searching in one cycle 
  static uint16 unStartIdxCycle = 0u;
  // Variable used as index for Dem event id table
  uint16 unIdx;
  // Variable used for Nvm writing every 300ms
  static TIMER  ulNvmLastRetry = 0U;

  //Check if the initialization has been performed
  if (Dem_boInitializationDone != FALSE)
  {

    // Loop only DEM_MAX_ALECS_NUMBER in one task slice
    for (unIdx = unStartIdxCycle; (unIdx < unStartIdxCycle + DEM_MAX_ALECS_NUMBER) && (unIdx < DEM_CONFIG_ENTRY_MAX); unIdx++)
    {
      if ((Dem_astEventStatus[unIdx].unStatus & DEM_STATUS_TEST_PREPASSED) != 0u)
      {
        Dem_DiagProcessEvent(unIdx, DEM_EVENT_STATUS_PASSED);
      }
      else if ((Dem_astEventStatus[unIdx].unStatus & DEM_STATUS_TEST_PREFAILED) != 0u)
      {
        Dem_DiagProcessEvent(unIdx, DEM_EVENT_STATUS_FAILED);
      }
      else
      {
        //do nothing 
      }
      // Check if Event is prepassed and check if timer expired
      //PRQA S 3415 1 //The right hand operand of a logical && operator is only evaluated if the left hand operand evaluates to 1 ("true") -> intended
      if (((Dem_astEventStatus[unIdx].unStatus & DEM_STATUS_TEST_PREPASSED) != 0u) && (TimerGetTimeSince(Dem_astEventStatus[unIdx].ulDebounceStartTime) >= FT_MSEC(dem_config[unIdx].debounce_time_passed)))
      {
        // Clear Alec
        Dem_ProcessEvent(unIdx, DEM_EVENT_STATUS_PASSED_IMMEDIATELY);
      }
      //Check if Event is prefailed and check if timer expired
      //PRQA S 3415 1 //The right hand operand of a logical && operator is only evaluated if the left hand operand evaluates to 1 ("true") -> intended
      else if (((Dem_astEventStatus[unIdx].unStatus & DEM_STATUS_TEST_PREFAILED) != 0u) && (TimerGetTimeSince(Dem_astEventStatus[unIdx].ulDebounceStartTime) >= FT_MSEC(dem_config[unIdx].debounce_time_failed)))
      {
        // Set Alec
        Dem_ProcessEvent(unIdx, DEM_EVENT_STATUS_FAILED_IMMEDIATELY);
      }
      else
      {
        // Alec is not prepassed/prefialed OR time hasn't expired yet
      }

    }//end for loop

    // If unStartIdx reaches DEM_CONFIG_ENTRY_MAX then it will be set again to 0, else the value is unchanged by 'modulo' operation
    unStartIdxCycle = unIdx % DEM_CONFIG_ENTRY_MAX;

    // update NVM
    // PRQA S 3415 1     // QA Tool problem, functions do not modify variables
    if ((Dem_boNvmDirty != FALSE) && (TimerGetTimeSince(ulNvmLastRetry) >= FT_MSEC(300U)))
    {
      // retry every 300 ms
      Dem_boNvmDirty = ( NvM_WriteBlock((uint16)NvmBlockDemDataId, NULL_PTR) != E_OK ) ? TRUE : FALSE;
      ulNvmLastRetry = TimerGetTick();
    }
    else
    {
      // nothing to do
    }
  }
  else
  {
    //DEM is not initialized yet, therefore nothing to do
  }
}


//-----------------------------------------------------------------------------
/// \brief Dem_ResetArrays
///
/// \descr This function reset all arrays which are used by Dem at their initial values according with the value of parameter 'unDemIdx'
///
/// \param  unDemIdx
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Dem_ResetArrays(uint16 unDemIdx)
{
  // Clear only for a given dem event id
  Dem_astEventStatus[unDemIdx].ulDebounceStartTime = 0u;
  Dem_astEventStatus[unDemIdx].unStatus = DEM_STATUS_CONFIG_CLEAR;

  NvmBlockDemData.aucAgingCounter[unDemIdx] = 0u;
  NvmBlockDemData.aucStatus[unDemIdx] = (uint8)DEM_STATUS_CONFIG_CLEAR;

  // Set dirty flag only if status has changed
  Dem_boNvmDirty = TRUE;

  // Initialized the status test request with passed in order to set again the Alec/Dtc if this one appeare again after clear
  Dem_asStatusTest[unDemIdx].ucResult = DEM_EVENT_STATUS_PASSED;
}


//-----------------------------------------------------------------------------
/// \brief Dem_ClearStartUpStatus
///
/// \descr Startup flag clear. Once Dem_boStartupStat flag is set, all errors are allowed to be logged independently by DiagMuxOn
///        Once Dem_boStartupStat is cleared after Start-Up sequence, Dem event set/clear is dependent by DiagMuxOn
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void Dem_ClearStartUpStatus(void)
{
  Dem_boStartupStat = FALSE;
}


//-----------------------------------------------------------------------------
/// \brief  Dem_Custom_OV_NotifyFailed
///
/// \descr  Callback from Dem module. It is called when the event is present
///
/// \param  unEventId, ucStatus
///
/// \return void
//-----------------------------------------------------------------------------
void Dem_Custom_UV_NotifyFailed(uint16 unEventId, uint8 ucStatus)
{
  (void)unEventId;
  (void)ucStatus;
  
  const boolean boUvStatus = TRUE;
  //call Rte
  (void)Rte_Write_DEM_UV_NotifyStatus(&boUvStatus);
}

//-----------------------------------------------------------------------------
/// \brief  Dem_Custom_UV_NotifyPassed
///
/// \descr  Callback from Dem module. It is called when the event isn't present
///
/// \param  unEventId, ucStatus
///
/// \return void
//-----------------------------------------------------------------------------
void Dem_Custom_UV_NotifyPassed(uint16 unEventId, uint8 ucStatus)
{
  (void)unEventId;
  (void)ucStatus;

  const boolean boUvStatus = FALSE;
  //call Rte
  (void)Rte_Write_DEM_UV_NotifyStatus(&boUvStatus);
}

//-----------------------------------------------------------------------------
/// \brief  Dem_Custom_OV_NotifyFailed
///
/// \descr  Callback from Dem module. It is called when the event is present
///
/// \param  unEventId, ucStatus
///
/// \return void
//-----------------------------------------------------------------------------
void Dem_Custom_OV_NotifyFailed(uint16 unEventId, uint8 ucStatus)
{
(void)unEventId;
(void)ucStatus;

const boolean boOvStatus = TRUE;
//call Rte
(void)Rte_Write_DEM_OV_NotifyStatus(&boOvStatus);
}

//-----------------------------------------------------------------------------
/// \brief  Dem_Custom_OV_NotifyPassed
///
/// \descr  Callback from Dem module. It is called when the event isn't present
///
/// \param  unEventId, ucStatus
///
/// \return void
//-----------------------------------------------------------------------------
void Dem_Custom_OV_NotifyPassed(uint16 unEventId, uint8 ucStatus)
{
	(void)unEventId;
	(void)ucStatus;

	const boolean boOvStatus = FALSE;
	//call Rte
	(void)Rte_Write_DEM_OV_NotifyStatus(&boOvStatus);
}

//-----------------------------------------------------------------------------
/// \brief  Dem_Custom_350Lost_NotifyFailed
///
/// \descr  Callback from Dem module. It is called when the event is present
///
/// \param  unEventId, ucStatus
///
/// \return void
//-----------------------------------------------------------------------------
void Dem_Custom_350Lost_NotifyFailed(uint16 unEventId, uint8 ucStatus)
{
	(void)unEventId;
	(void)ucStatus;

	const boolean bo350LostStatus = TRUE;

#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
	//call Rte
	(void)Rte_Write_DEM_350Lost_NotifyStatus(&bo350LostStatus);
#endif
}

//-----------------------------------------------------------------------------
/// \brief  Dem_Custom_350Lost_NotifyPassed
///
/// \descr  Callback from Dem module. It is called when the event isn't present
///
/// \param  unEventId, ucStatus
///
/// \return void
//-----------------------------------------------------------------------------
void Dem_Custom_350Lost_NotifyPassed(uint16 unEventId, uint8 ucStatus)
{
	(void)unEventId;
	(void)ucStatus;

	const boolean bo350LostStatus = FALSE;

#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
	//call Rte
	(void)Rte_Write_DEM_350Lost_NotifyStatus(&bo350LostStatus);
#endif
}

//-----------------------------------------------------------------------------
/// \brief Dem_Set_Init_Window
///
/// \descr
///
/// \param  boLevel
///
/// \return void
//-----------------------------------------------------------------------------
void Dem_Set_Init_Window(boolean boLevel)
{
	Dem_boInitEvent = boLevel;
}



//EOF

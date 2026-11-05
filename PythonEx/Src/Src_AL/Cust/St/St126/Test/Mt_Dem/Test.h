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
/// \file  Test.h
///
/// \brief This file contains functions prototypes of the tested module, 
///        including functions parameters and global variables
///
//-----------------------------------------------------------------------------
#ifndef TEST_2023_08_25_H_
#define TEST_2023_08_25_H_

//=============================================================================
// Includes
//=============================================================================
#include <Bsw/Dem/Dem_Mac.h>
#include <Dem.h>
#include <Dem_Cfg.h>


//=============================================================================
// Defines
//=============================================================================
#define DEM_JDD_FAULT_PRESENT                       0x01u
#define DEM_JDD_FAULT_PRESENT_CONFIRMED             0x02u
//#define DEM_JDD_CUSTOM_FAULT_CNT_MAX                255u
#define DEM_STATUS_TEST_PREFAILED                   0x0100u
#define DEM_STATUS_TEST_PREPASSED                   0x0200u
#define DEM_JDD_FAULT_PRESENT_CONFIRMED_DTC         0x10u
#define DEM_JDD_FAULT_ABSENT_CONFIRMED_DTC          0x20u


//=============================================================================
// Module global variables
//=============================================================================
extern tDem_aEventStatus_type         Dem_astEventStatus[DEM_CONFIG_ENTRY_MAX];
extern Dem_tsDiagFaultState           Dem_asDiagFaultState[DEM_CONFIG_ENTRY_MAX];
extern Dem_tsStatusTest               Dem_asStatusTest[DEM_CONFIG_ENTRY_MAX];
extern boolean                        Dem_boInitializationDone;
extern uint8                          Dem_ucSideModifier;
extern boolean                        Dem_boStartupStat;
extern boolean                        Dem_boNvmDirty;
extern dem_config_type                dem_config[];
extern boolean                        LockDTC;
extern boolean                        Dem_boInitEvent;
extern NM_ModeType                    NMMode;


//=============================================================================
// Module function declarations
//=============================================================================
extern void    riDem_Init(void);
extern void    rpDem_Cycle0(void);
extern void    Dem_Init(void);
extern void    Dem_SetEventStatus(uint16 unAlecId, uint8 ucTestStatus);
extern void    Dem_ClearAlec(boolean boAllAlecs, uint16 unDemIndex);
extern void    Dem_Task(void);
extern boolean Dem_boEventPassed(uint16 unEventIdx);
extern void    Dem_ClearStartUpStatus(void);
extern void    Dem_TriggerCallbackFunctions(uint16 unEventIdx);
extern void    Dem_ProcessEvent(uint16 unEventIndex, uint8 ucEventStatus);
extern void    Dem_PreProcessEvent(uint16 unPreEventIndex, uint8 ucPreEventStatus);
extern void    Dem_DiagProcessEvent(uint16 unEventId, uint8 ucEventStatus);
extern void    Dem_DiagProcessEvent_Pass_TimeOut(uint16 unEventId);
extern void    Dem_DiagProcessEvent_Pass_Cnt(uint16 unEventId);
extern void    Dem_DiagProcessEvent_Fail_TimeOut(uint16 unEventId);
extern void    Dem_DiagProcessEvent_Fail_Cnt(uint16 unEventId);
extern void    Dem_ResetArrays(uint16 unDemIdx);
extern void    Dem_Custom_350Lost_NotifyPassed(uint16 unEventId, uint8 ucStatus);
extern void    Dem_Custom_350Lost_NotifyFailed(uint16 unEventId, uint8 ucStatus);
extern void    Dem_Custom_OV_NotifyPassed(uint16 unEventId, uint8 ucStatus);
extern void    Dem_Custom_OV_NotifyFailed(uint16 unEventId, uint8 ucStatus);
extern void    Dem_Custom_UV_NotifyPassed(uint16 unEventId, uint8 ucStatus);
extern void    Dem_Custom_UV_NotifyFailed(uint16 unEventId, uint8 ucStatus);
extern void    Dem_Diag_LockDTC(boolean boEnableDTC);


//=============================================================================
// Module function parameter stubs
//=============================================================================
boolean        Dem_Diag_LockDTC_Param1;
uint16         Dem_Custom_UV_NotifyFailed_Param1;
uint8          Dem_Custom_UV_NotifyFailed_Param2;
uint16         Dem_Custom_UV_NotifyPassed_Param1;
uint8          Dem_Custom_UV_NotifyPassed_Param2;
uint16         Dem_Custom_OV_NotifyFailed_Param1;
uint8          Dem_Custom_OV_NotifyFailed_Param2;
uint16         Dem_Custom_OV_NotifyPassed_Param1;
uint8          Dem_Custom_OV_NotifyPassed_Param2;
uint16         Dem_Custom_350Lost_NotifyFailed_Param1;
uint8          Dem_Custom_350Lost_NotifyFailed_Param2;
uint16         Dem_Custom_350Lost_NotifyPassed_Param1;
uint8          Dem_Custom_350Lost_NotifyPassed_Param2;
uint16         Dem_TriggerCallbackFunctions_Param1;
uint16         Dem_ResetArrays_Param1;
boolean        Dem_ClearAlec_Param1;
uint16         Dem_ClearAlec_Param2;
uint16         Dem_boEventPassed_Param1;
uint16         Dem_SetEventStatus_Param1;
uint8          Dem_SetEventStatus_Param2;
uint16         Dem_DiagProcessEvent_Param1;
uint8          Dem_DiagProcessEvent_Param2;
uint16         Dem_DiagProcessEvent_Fail_Cnt_Param1;
uint16         Dem_DiagProcessEvent_Fail_TimeOut_Param1;
uint16         Dem_DiagProcessEvent_Pass_Cnt_Param1;
uint16         Dem_DiagProcessEvent_Pass_TimeOut_Param1;
uint16         Dem_PreProcessEvent_Param1;
uint8          Dem_PreProcessEvent_Param2;
uint16         Dem_ProcessEvent_Param1;
uint8          Dem_ProcessEvent_Param2;
boolean        Dem_Set_Init_Window_Param1;


//=============================================================================
// Module function return value stubs
//=============================================================================
boolean        Dem_boEventPassed_RetVal;


#endif // TEST_2023_08_25_H_

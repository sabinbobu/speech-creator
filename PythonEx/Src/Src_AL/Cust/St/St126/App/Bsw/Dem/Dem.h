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
// \file   Dem.h
//
// \brief  DEM declaratrions
//
// \descr  Declarations and types of the DEM
//
// \author Vlad Sarghe (F09695CC)
//         mailto:adrian-vlad.sarghe[at]marelli.com
//----------------------------------------------------------------------------
#ifndef __DEM_H__
#define __DEM_H__

//----------------------------------------------------------------------------
// Includes
//----------------------------------------------------------------------------
#include <Dem_Types.h>

//----------------------------------------------------------------------------
// Expand configuration
//----------------------------------------------------------------------------
#define  DEM_CONFIG_MAC_DECL_ENUM
#include <Dem_Cfg.h>
#undef   DEM_CONFIG_MAC_DECL_ENUM


//----------------------------------------------------------------------------
// Definitions
//----------------------------------------------------------------------------
#define DEM_EVENT_STATUS_PASSED_IMMEDIATELY 0x00u
#define DEM_EVENT_STATUS_FAILED_IMMEDIATELY 0x01u
#define DEM_EVENT_STATUS_PREPASSED          0x02u
#define DEM_EVENT_STATUS_PREFAILED          0x03u
#define DEM_EVENT_STATUS_INIT               0xFFu
#define DEM_EVENT_STATUS_PASSED             DEM_EVENT_STATUS_PREPASSED
#define DEM_EVENT_STATUS_FAILED             DEM_EVENT_STATUS_PREFAILED


// DEM status flags
#define DEM_STATUS_TEST_FAILED                      0x0001u
#define DEM_STATUS_TEST_FAILED_THIS_CYCLE           0x0002u
#define DEM_STATUS_PENDING_DTC                      0x0004u
#define DEM_STATUS_CONFIRMED_DTC                    0x0008u
#define DEM_STATUS_TEST_NOT_COMPLETED_SINCE_CLEAR   0x0010u
#define DEM_STATUS_TEST_FAILED_SINCE_CLEAR          0x0020u
#define DEM_STATUS_TEST_NOT_COMPLETED_THIS_CYCLE    0x0040u
#define DEM_STATUS_TEST_PASSED                      0x0080u
#define DEM_STATUS_TEST_PREFAILED                   0x0100u
#define DEM_STATUS_TEST_PREPASSED                   0x0200u

// Define for unused condition/notification function
#define DEM_FCT_NONE                                NULL_PTR

//----------------------------------------------------------------------------
// Prototypes
//----------------------------------------------------------------------------
void Dem_Init(void);
void Dem_SetEventStatus(uint16 unAlecId, uint8 ucTestStatus);
void Dem_ClearAlec(boolean boAllAlecs, uint16 unDemIndex);
void Dem_Task(void);
boolean Dem_boEventPassed(uint16 unEventIdx);
void Dem_ClearStartUpStatus(void);
void Dem_Diag_LockDTC(boolean boEnableDTC);
void Dem_Custom_UV_NotifyFailed(uint16 unEventId, uint8 ucStatus);
void Dem_Custom_UV_NotifyPassed(uint16 unEventId, uint8 ucStatus);
void Dem_Custom_OV_NotifyFailed(uint16 unEventId, uint8 ucStatus);
void Dem_Custom_OV_NotifyPassed(uint16 unEventId, uint8 ucStatus);
void Dem_Custom_350Lost_NotifyFailed(uint16 unEventId, uint8 ucStatus);
void Dem_Custom_350Lost_NotifyPassed(uint16 unEventId, uint8 ucStatus);
void Dem_Set_Init_Window(boolean boLevel);

#endif  // __DEM_H__

// EOF


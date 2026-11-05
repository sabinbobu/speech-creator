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
/// \file  Test_Stubs.h
///
/// \brief Stub functions prototypes for access to software modules excluded from test
///        including stub parameters
///
//-----------------------------------------------------------------------------
#ifndef TEST_STUBS_2023_08_25_H_
#define TEST_STUBS_2023_08_25_H_

//=============================================================================
// Includes
//=============================================================================
#include <Nvm.h>
#include <Std_Types.h>
#include <LgmEIMMainAPI.h>
#include <Gpt.h>
#include <RteCommonTypes.h>
#include <_NM_Types.h>


//=============================================================================
// Stub function declarations
//=============================================================================
Std_ReturnType            NvM_WriteBlock(NvM_BlockIdType BlockId, void* NvM_SrcPtr);
void                      ErrCust_ErrHandling(uint16 unAlecId, uint8 ucAlecStatus);
void                      SysMonRx_Callbacks_GetDiagMuxState(boolean *pboValue);
LEIM_TE_CurrentEIMode     EAPI_GetCurrentEIMode(void);
void                      Deh_AppearanceDetected(uint16 unEventId);
void                      Deh_AppearanceConfirmed(uint16 unEventId);
void                      Deh_DisappearanceDetected(uint16 unEventId);
void                      Deh_DisappearanceConfirmed(uint16 unEventId);
uint32                    LPTMR0_GetTimeElapsed(const uint32 ulStartValue);
Std_ReturnType            Rte_Read_IoHwAbUser_GetMountingSide(teRte_MountingSide* ppara1);
Std_ReturnType            Rte_Read_SysMon_LifePhases(tsRte_SysMon_LifePhases* ppara1);
void                      Dem_UnitTest_NotifyPassed(uint16 event_id, boolean status_passed);
void                      Dem_UnitTest_NotifyFailed(uint16 event_id, boolean status_passed);
Std_ReturnType            Rte_Write_DEM_UV_NotifyStatus(boolean* ppara1);
Std_ReturnType            Rte_Write_DEM_OV_NotifyStatus(boolean* ppara1);
Std_ReturnType            Rte_Write_DEM_350Lost_NotifyStatus(boolean* ppara1);
NM_ErrorCodeType          NM_GetMode(NM_ModeType * p_NMMode);


//=============================================================================
// Stub function parameter stubs
//=============================================================================
extern tieFeeState               Fee_State;
extern MemIf_JobResultType       Fee_JobResult;
extern boolean                   Rte_Write_DEM_350Lost_NotifyStatus_Param1;
extern boolean                   Rte_Write_DEM_OV_NotifyStatus_Param1;
extern boolean                   Rte_Write_DEM_UV_NotifyStatus_Param1;
extern uint16                    Dem_UnitTest_NotifyPassed_Param1;
extern boolean                   Dem_UnitTest_NotifyPassed_Param2;
extern uint16                    Dem_UnitTest_NotifyFailed_Param1;
extern boolean                   Dem_UnitTest_NotifyFailed_Param2;
extern uint16                    ErrCust_ErrHandling_Param1;
extern uint8                     ErrCust_ErrHandling_Param2;
extern boolean                   SysMonRx_Callbacks_GetDiagMuxState_Param1;
extern NvM_BlockIdType           NvM_WriteBlock_Param1;
extern void*                     NvM_WriteBlock_Param2;
extern uint16                    Deh_AppearanceDetected_Param1;
extern uint16                    Deh_AppearanceConfirmed_Param1;
extern uint16                    Deh_DisappearanceDetected_Param1;
extern uint16                    Deh_DisappearanceConfirmed_Param1;
extern uint32                    LPTMR0_GetTimeElapsed_Param1;
extern teRte_MountingSide        Rte_Read_IoHwAbUser_GetMountingSide_Param1;
extern NM_ModeType               NM_GetMode_Param1;
extern tsRte_SysMon_LifePhases   Rte_Read_SysMon_LifePhases_Param1;


//=============================================================================
// Stub function returned value stubs
//=============================================================================
extern LEIM_TE_CurrentEIMode     EAPI_GetCurrentEIMode_RetVal;
extern Std_ReturnType            NvM_WriteBlock_RetVal;
extern uint32                    LPTMR0_GetTimeElapsed_RetVal;
extern Std_ReturnType            Rte_Read_IoHwAbUser_GetMountingSide_RetVal;
extern Std_ReturnType            Rte_Write_DEM_UV_NotifyStatus_RetVal;
extern Std_ReturnType            Rte_Write_DEM_OV_NotifyStatus_RetVal;
extern Std_ReturnType            Rte_Write_DEM_350Lost_NotifyStatus_RetVal;
extern NM_ErrorCodeType          NM_GetMode_RetVal;
extern Std_ReturnType            Rte_Read_SysMon_LifePhases_RetVal;


//=============================================================================
// Stub function hit count variables
//=============================================================================
extern uint8                     Rte_Write_DEM_350Lost_NotifyStatus_HitCount;
extern uint8                     Rte_Write_DEM_OV_NotifyStatus_HitCount;
extern uint8                     Rte_Write_DEM_UV_NotifyStatus_HitCount;
extern uint8                     ErrCust_ErrHandling_HitCount;
extern uint8                     EAPI_GetCurrentEIMode_HitCount;
extern uint8                     NvM_WriteBlock_HitCount;
extern uint8                     SysMonRx_Callbacks_GetDiagMuxState_HitCount;
extern uint8                     Deh_AppearanceDetected_HitCount;
extern uint8                     Deh_AppearanceConfirmed_HitCount;
extern uint8                     Deh_DisappearanceDetected_HitCount;
extern uint8                     Deh_DisappearanceConfirmed_HitCount;
extern uint8                     LPTMR0_GetTimeElapsed_HitCount;
extern uint8                     Rte_Read_IoHwAbUser_GetMountingSide_HitCount;
extern uint8                     Dem_UnitTest_NotifyPassed_HitCount;
extern uint8                     Dem_UnitTest_NotifyFailed_HitCount;
extern uint32                    NM_GetMode_HitCount;
extern uint32                    Rte_Read_SysMon_LifePhases_HitCount;


#endif // TEST_STUBS_2023_08_25_H_

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
/// \file  Test_Stubs.c
///
/// \brief Stub functions for access to software modules excluded from test
///
//-----------------------------------------------------------------------------

//=============================================================================
// Includes
//=============================================================================
#include "Test_Stubs.h"


//=============================================================================
// Stub function parameter stubs
//=============================================================================
tieFeeState               Fee_State;
MemIf_JobResultType       Fee_JobResult;
boolean                   Rte_Write_DEM_350Lost_NotifyStatus_Param1;
boolean                   Rte_Write_DEM_OV_NotifyStatus_Param1;
boolean                   Rte_Write_DEM_UV_NotifyStatus_Param1;
uint16                    Dem_UnitTest_NotifyPassed_Param1;
boolean                   Dem_UnitTest_NotifyPassed_Param2;
uint16                    Dem_UnitTest_NotifyFailed_Param1;
boolean                   Dem_UnitTest_NotifyFailed_Param2;
uint16                    ErrCust_ErrHandling_Param1;
uint8                     ErrCust_ErrHandling_Param2;
boolean                   SysMonRx_Callbacks_GetDiagMuxState_Param1;
NvM_BlockIdType           NvM_WriteBlock_Param1;
void*                     NvM_WriteBlock_Param2;
uint16                    Deh_AppearanceDetected_Param1;
uint16                    Deh_AppearanceConfirmed_Param1;
uint16                    Deh_DisappearanceDetected_Param1;
uint16                    Deh_DisappearanceConfirmed_Param1;
uint32                    LPTMR0_GetTimeElapsed_Param1;
teRte_MountingSide        Rte_Read_IoHwAbUser_GetMountingSide_Param1;
NM_ModeType               NM_GetMode_Param1;
tsRte_SysMon_LifePhases   Rte_Read_SysMon_LifePhases_Param1;


//=============================================================================
// Stub function returned value stubs
//=============================================================================
LEIM_TE_CurrentEIMode     EAPI_GetCurrentEIMode_RetVal;
Std_ReturnType            NvM_WriteBlock_RetVal;
uint32                    LPTMR0_GetTimeElapsed_RetVal;
Std_ReturnType            Rte_Read_IoHwAbUser_GetMountingSide_RetVal;
Std_ReturnType            Rte_Write_DEM_UV_NotifyStatus_RetVal;
Std_ReturnType            Rte_Write_DEM_OV_NotifyStatus_RetVal;
Std_ReturnType            Rte_Write_DEM_350Lost_NotifyStatus_RetVal;
NM_ErrorCodeType          NM_GetMode_RetVal;
Std_ReturnType            Rte_Read_SysMon_LifePhases_RetVal;


//=============================================================================
// Stub function hit count variables
//=============================================================================
uint8                     Rte_Write_DEM_350Lost_NotifyStatus_HitCount;
uint8                     Rte_Write_DEM_OV_NotifyStatus_HitCount;
uint8                     Rte_Write_DEM_UV_NotifyStatus_HitCount;
uint8                     ErrCust_ErrHandling_HitCount;
uint8                     EAPI_GetCurrentEIMode_HitCount;
uint8                     NvM_WriteBlock_HitCount;
uint8                     SysMonRx_Callbacks_GetDiagMuxState_HitCount;
uint8                     Deh_AppearanceDetected_HitCount;
uint8                     Deh_AppearanceConfirmed_HitCount;
uint8                     Deh_DisappearanceDetected_HitCount;
uint8                     Deh_DisappearanceConfirmed_HitCount;
uint8                     LPTMR0_GetTimeElapsed_HitCount;
uint8                     Rte_Read_IoHwAbUser_GetMountingSide_HitCount;
uint8                     Dem_UnitTest_NotifyPassed_HitCount;
uint8                     Dem_UnitTest_NotifyFailed_HitCount;
uint32                    NM_GetMode_HitCount;
uint32                    Rte_Read_SysMon_LifePhases_HitCount;


//=============================================================================
// Stub function definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SysMon_LifePhases
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SysMon_LifePhases
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Read_SysMon_LifePhases(tsRte_SysMon_LifePhases* ppara1)
{
  *ppara1 = Rte_Read_SysMon_LifePhases_Param1;
  Rte_Read_SysMon_LifePhases_HitCount++;

  return Rte_Read_SysMon_LifePhases_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  NM_GetMode
///
/// \descr  Stub function created to simulate the behaviour of NM_GetMode
///
/// \param  p_NMMode
///
/// \return NM_ErrorCodeType
//-----------------------------------------------------------------------------
NM_ErrorCodeType NM_GetMode(NM_ModeType * p_NMMode)
{
  *p_NMMode = NM_GetMode_Param1;
  NM_GetMode_HitCount++;

  return NM_GetMode_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Write_DEM_350Lost_NotifyStatus
///
/// \descr Stub function for Rte_Write_DEM_350Lost_NotifyStatus
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_DEM_350Lost_NotifyStatus(boolean* ppara1)
{
  Rte_Write_DEM_350Lost_NotifyStatus_Param1 = *ppara1;
  Rte_Write_DEM_350Lost_NotifyStatus_HitCount++;

  return Rte_Write_DEM_350Lost_NotifyStatus_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Write_DEM_OV_NotifyStatus
///
/// \descr Stub function for Rte_Write_DEM_OV_NotifyStatus
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_DEM_OV_NotifyStatus(boolean* ppara1)
{
  Rte_Write_DEM_OV_NotifyStatus_Param1 = *ppara1;
  Rte_Write_DEM_OV_NotifyStatus_HitCount++;

  return Rte_Write_DEM_OV_NotifyStatus_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Write_DEM_UV_NotifyStatus
///
/// \descr Stub function for Rte_Write_DEM_UV_NotifyStatus
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_DEM_UV_NotifyStatus(boolean* ppara1)
{
  Rte_Write_DEM_UV_NotifyStatus_Param1 = *ppara1;
  Rte_Write_DEM_UV_NotifyStatus_HitCount++;

  return Rte_Write_DEM_UV_NotifyStatus_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Dem_UnitTest_NotifyPassed
///
/// \descr  Stub function created to simulate the behaviour of Dem_UnitTest_NotifyPassed
///
/// \param  event_id, status_passed
///
/// \return void
//-----------------------------------------------------------------------------
void Dem_UnitTest_NotifyPassed(uint16 event_id, boolean status_passed)
{
  Dem_UnitTest_NotifyPassed_Param1 = event_id;
  Dem_UnitTest_NotifyPassed_Param2 = status_passed;
  Dem_UnitTest_NotifyPassed_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Dem_UnitTest_NotifyFailed
///
/// \descr  Stub function created to simulate the behaviour of Dem_UnitTest_NotifyFailed
///
/// \param  event_id, status_passed
///
/// \return void
//-----------------------------------------------------------------------------
void Dem_UnitTest_NotifyFailed(uint16 event_id, boolean status_passed)
{
  Dem_UnitTest_NotifyFailed_Param1 = event_id;
  Dem_UnitTest_NotifyFailed_Param2 = status_passed;
  Dem_UnitTest_NotifyFailed_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  NvM_WriteBlock
///
/// \descr  Stub function created to simulate the behaviour of NvM_WriteBlock
///
/// \param  - BlockId, NvM_SrcPtr
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType NvM_WriteBlock(NvM_BlockIdType BlockId, void* NvM_SrcPtr)
{
  NvM_WriteBlock_Param1 = BlockId;
  NvM_WriteBlock_Param2 = NvM_SrcPtr;
  NvM_WriteBlock_HitCount++;

  return NvM_WriteBlock_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  ErrCust_ErrHandling
///
/// \descr  Stub function created to simulate the behaviour of ErrCust_ErrHandling
///
/// \param  unAlecId, ucAlecStatus
///
/// \return void
//-----------------------------------------------------------------------------
void ErrCust_ErrHandling(uint16 unAlecId, uint8 ucAlecStatus)
{
  ErrCust_ErrHandling_Param1 = unAlecId;
  ErrCust_ErrHandling_Param2 = ucAlecStatus;
  ErrCust_ErrHandling_HitCount++;
}

///-----------------------------------------------------------------------------
/// \brief  EAPI_GetCurrentEIMode
///
/// \descr  Stub function created to simulate the behaviour of  EAPI_GetCurrentEIMode
///
/// \param  -
///
/// \return  LEIM_TE_CurrentEIMode
//-----------------------------------------------------------------------------
LEIM_TE_CurrentEIMode EAPI_GetCurrentEIMode(void)
{
  EAPI_GetCurrentEIMode_HitCount++;

  return EAPI_GetCurrentEIMode_RetVal;
}

///-----------------------------------------------------------------------------
/// \brief  SysMonRx_Callbacks_GetDiagMuxState
///
/// \descr  Stub function created to simulate the behaviour of  SysMonRx_Callbacks_GetDiagMuxState
///
/// \param *pboValue, *pboSigStatus
///
/// \return -
//-----------------------------------------------------------------------------
void SysMonRx_Callbacks_GetDiagMuxState(boolean *pboValue)
{
  *pboValue = SysMonRx_Callbacks_GetDiagMuxState_Param1;
  SysMonRx_Callbacks_GetDiagMuxState_HitCount++;
}

///-----------------------------------------------------------------------------
/// \brief  Deh_AppearanceDetected
///
/// \descr  Stub function created to simulate the behaviour of  Deh_AppearanceDetected
///
/// \param unEventId
///
/// \return -
//-----------------------------------------------------------------------------
void Deh_AppearanceDetected(uint16 unEventId)
{
  Deh_AppearanceDetected_Param1 = unEventId;
  Deh_AppearanceDetected_HitCount++;
}

///-----------------------------------------------------------------------------
/// \brief  Deh_AppearanceConfirmed
///
/// \descr  Stub function created to simulate the behaviour of  Deh_AppearanceConfirmed
///
/// \param unEventId
///
/// \return -
//-----------------------------------------------------------------------------
void Deh_AppearanceConfirmed(uint16 unEventId)
{
  Deh_AppearanceConfirmed_Param1 = unEventId;
  Deh_AppearanceConfirmed_HitCount++;
}

///-----------------------------------------------------------------------------
/// \brief  Deh_DisappearanceDetected
///
/// \descr  Stub function created to simulate the behaviour of  Deh_DisappearanceDetected
///
/// \param unEventId
///
/// \return -
//-----------------------------------------------------------------------------
void Deh_DisappearanceDetected(uint16 unEventId)
{
  Deh_DisappearanceDetected_Param1 = unEventId;
  Deh_DisappearanceDetected_HitCount++;
}

///-----------------------------------------------------------------------------
/// \brief  Deh_DisappearanceConfirmed
///
/// \descr  Stub function created to simulate the behaviour of  Deh_DisappearanceConfirmed
///
/// \param unEventId
///
/// \return -
//-----------------------------------------------------------------------------
void Deh_DisappearanceConfirmed(uint16 unEventId)
{
  Deh_DisappearanceConfirmed_Param1 = unEventId;
  Deh_DisappearanceConfirmed_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief LPTMR0_GetTimeElapsed
///
/// \descr Stub function for LPTMR0_GetTimeElapsed
///
/// \param  ulStartValue
///
/// \return uint32
//-----------------------------------------------------------------------------
uint32 LPTMR0_GetTimeElapsed(const uint32 ulStartValue)
{
  LPTMR0_GetTimeElapsed_HitCount++;
  LPTMR0_GetTimeElapsed_Param1 = ulStartValue;

  return LPTMR0_GetTimeElapsed_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Read_IoHwAbUser_GetMountingSide
///
/// \descr Stub function for Rte_Read_IoHwAbUser_GetMountingSide
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_IoHwAbUser_GetMountingSide(teRte_MountingSide* ppara1)
{
  *ppara1 = Rte_Read_IoHwAbUser_GetMountingSide_Param1;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount++;

  return Rte_Read_IoHwAbUser_GetMountingSide_RetVal;
}


// EOF

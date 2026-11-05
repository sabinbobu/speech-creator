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
tieFeeState                Fee_State;
MemIf_JobResultType        Fee_JobResult;
TE_Bool                    DAPI_InitModule_Param1;
Tu8_Int                    DAPI_InitModule_Param2;
LDEH_TE_PermFifo           DAPI_PermFifoStorage_Param1;
LDEH_TE_PermToSend         DAPI_SetPermToSend_Param1;
uint8                      ErrCust_ulGetDtcCode_Param1;
LDEH_TS_DECtxt *           DAPI_BuildDECtxt_Param1;
LDEH_TE_EvtType            DAPI_BuildDECtxt_Param2;
Tu32_Int                   DAPI_BuildDECtxt_Param3;
Tu8_Int                    DAPI_BuildDECtxt_Param4;
Tu8_Int                    DAPI_BuildDECtxt_Param5;
LDEH_TS_DECtxt *           DAPI_AddDE_Param1;
TE_Bool                    DAPI_AddDE_Param2;
LGM_MessageIdentifier      LGM_InitMessage_Param1;
UINT8                      LGM_InitMessage_Param2[8];
tindexIpdu                 IL_EnvoyerIpdu_Param1;
teRte_MountingSide         Rte_Read_IoHwAbUser_GetMountingSide_Param1;
TE_Bool                    DAPI_SetSafetyConditions_Param1;
DAPI_TE_MainStatus         DAPI_SetMainStatus_Param1;
uint16                     ErrCust_GetActualErrorIndex_Param1;
uint16                     Dem_SetEventStatus_Param1;
uint8                      Dem_SetEventStatus_Param2;
uint8                      ErrCust_GetStatusOfDtc_Param2;
NvM_BlockIdType            NvM_WriteBlock_Param1;
void*                      NvM_WriteBlock_Param2;
tsRte_SysMon_LifePhases    Rte_Read_SysMon_LifePhases_Param1;
tsRte_SysMon_VehicleSpeed  Rte_Read_SysMon_VehicleSpeed_Param1;
uint8                      ErrCust_ucGetStatusOfDTC_Param1;
uint8                      ErrCust_GetStatusOfDtc_Param1;
boolean                    Dem_Set_Init_Window_Param1;


//=============================================================================
// Stub function returned value stubs
//=============================================================================
LDEH_TE_ErrVal             DAPI_ScheduleMainFunction_RetVal;
uint32                     ErrCust_ulGetDtcCode_RetVal;
LDEH_TE_ErrVal             DAPI_BuildDECtxt_RetVal;
LDEH_TE_ErrVal             DAPI_AddDE_RetVal;
IL_StatusType              LGM_InitMessage_RetVal;
IL_StatusType              IL_EnvoyerIpdu_RetVal;
Std_ReturnType             Rte_Read_IoHwAbUser_GetMountingSide_RetVal;
uint8                      Rte_Read_SysMon_LifePhases_RetVal;
Std_ReturnType             Rte_Read_SysMon_VehicleSpeed_RetVal;
uint8                      ErrCust_GetActualErrorIndex_RetVal;
uint8                      ErrCust_GetStatusOfDtc_RetVal;
Std_ReturnType             NvM_WriteBlock_RetVal;
uint8                      ErrCust_ucGetStatusOfDTC_RetVal;


//=============================================================================
// Stub function hit count variables
//=============================================================================
uint32                     DAPI_InitModule_HitCount;
uint32                     DAPI_PermFifoStorage_HitCount;
uint32                     DAPI_SetPermToSend_HitCount;
uint32                     DAPI_ScheduleMainFunction_HitCount;
uint32                     ErrCust_ulGetDtcCode_HitCount;
uint32                     DAPI_BuildDECtxt_HitCount;
uint32                     DAPI_AddDE_HitCount;
uint32                     LGM_InitMessage_HitCount;
uint32                     IL_EnvoyerIpdu_HitCount;
uint32                     Rte_Read_IoHwAbUser_GetMountingSide_HitCount;
uint32                     ErrCust_GetActualErrorIndex_HitCount;
uint32                     DAPI_SetSafetyConditions_HitCount;
uint32                     DAPI_SetMainStatus_HitCount;
uint32                     Dem_SetEventStatus_HitCount;
uint32                     NvM_WriteBlock_HitCount;
uint32                     Deh_CheckSafetyConditions_HitCount;
uint8                      Rte_Read_SysMon_LifePhases_HitCount;
uint8                      Rte_Read_SysMon_VehicleSpeed_HitCount;
uint8                      ErrCust_GetStatusOfDtc_HitCount;
uint8                      ErrCust_ucGetStatusOfDTC_HitCount;
uint8                      Dem_Set_Init_Window_HitCount;


//=============================================================================
// Stub function definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  ErrCust_ucGetStatusOfDTC
///
/// \descr  Stub function created to simulate the behaviour of ErrCust_ucGetStatusOfDTC
///
/// \param  ucDtcIndex
///
/// \return uint8
//-----------------------------------------------------------------------------
uint8 ErrCust_ucGetStatusOfDTC(uint8 ucDtcIndex)
{
  ErrCust_ucGetStatusOfDTC_Param1 = ucDtcIndex;
  ErrCust_ucGetStatusOfDTC_HitCount++;

  return ErrCust_ucGetStatusOfDTC_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SysMon_VehicleSpeed
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SysMon_VehicleSpeed
///
/// \param  *ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SysMon_VehicleSpeed(tsRte_SysMon_VehicleSpeed* ppara1)
{
  *ppara1 = Rte_Read_SysMon_VehicleSpeed_Param1;
  Rte_Read_SysMon_VehicleSpeed_HitCount++;

  return Rte_Read_SysMon_VehicleSpeed_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SysMon_LifePhases
/// 
/// \descr  Stub function to simulate the behavoiur of Rte_Read_SysMon_LifePhases
///
/// \param  *ppara1
///
/// \return Std_ReturnType
//----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SysMon_LifePhases(tsRte_SysMon_LifePhases* ppara1)
{
  *ppara1 = Rte_Read_SysMon_LifePhases_Param1;
  Rte_Read_SysMon_LifePhases_HitCount++;

  return Rte_Read_SysMon_LifePhases_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  ErrCust_GetStatusOfDtc
///
/// \descr  Stub function created to simulate the behaviour of ErrCust_GetStatusOfDtc
///
/// \param  ucDtcIndex
///
/// \return uint8
//-----------------------------------------------------------------------------
uint8 ErrCust_GetStatusOfDtc(uint8 ucDtcIndex)
{
  ErrCust_GetStatusOfDtc_Param1 = ucDtcIndex;
  ErrCust_GetStatusOfDtc_HitCount++;

  return ErrCust_GetStatusOfDtc_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  DAPI_InitModule
///
/// \descr  Stub function created to simulate the behaviour of DAPI_InitModule
///
/// \param  PIE_NVMEnable
/// \param  PIu8_EcuCode
///
/// \return void
//-----------------------------------------------------------------------------
void DAPI_InitModule(const TE_Bool PIE_NVMEnable, const Tu8_Int PIu8_EcuCode)
{
  DAPI_InitModule_Param1 = PIE_NVMEnable;
  DAPI_InitModule_Param2 = PIu8_EcuCode;
  DAPI_InitModule_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  DAPI_PermFifoStorage
///
/// \descr  Stub function created to simulate the behaviour of DAPI_PermFifoStorage
///
/// \param  PIE_FifoStoragePerm
///
/// \return void
//-----------------------------------------------------------------------------
void DAPI_PermFifoStorage(const LDEH_TE_PermFifo PIE_FifoStoragePerm)
{
  DAPI_PermFifoStorage_Param1 = PIE_FifoStoragePerm;
  DAPI_PermFifoStorage_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  DAPI_SetMainStatus
///
/// \descr  Stub function created to simulate the behaviour of DAPI_SetMainStatus
///
/// \param  PIE_value
///
/// \return void
//-----------------------------------------------------------------------------
void DAPI_SetMainStatus(const DAPI_TE_MainStatus PIE_value)
{
  DAPI_SetMainStatus_Param1 = PIE_value;
  DAPI_SetMainStatus_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  DAPI_SetPermToSend
///
/// \descr  Stub function created to simulate the behaviour of DAPI_SetPermToSend
///
/// \param  PIE_PermToSend
///
/// \return void
//-----------------------------------------------------------------------------
void DAPI_SetPermToSend(const LDEH_TE_PermToSend PIE_PermToSend)
{
  DAPI_SetPermToSend_Param1 = PIE_PermToSend;
  DAPI_SetPermToSend_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  DAPI_ScheduleMainFunction
///
/// \descr  Stub function created to simulate the behaviour of DAPI_ScheduleMainFunction
///
/// \param  void
///
/// \return LDEH_TE_ErrVal
//-----------------------------------------------------------------------------
LDEH_TE_ErrVal DAPI_ScheduleMainFunction(void)
{
  DAPI_ScheduleMainFunction_HitCount++;

  return DAPI_ScheduleMainFunction_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  ErrCust_ulGetDtcCode
///
/// \descr  Stub function created to simulate the behaviour of ErrCust_ulGetDtcCode
///
/// \param  ucDtcIndex
///
/// \return uint32
//-----------------------------------------------------------------------------
uint32 ErrCust_ulGetDtcCode(uint8 ucDtcIndex)
{
  ErrCust_ulGetDtcCode_Param1 = ucDtcIndex;
  ErrCust_ulGetDtcCode_HitCount++;

  return ErrCust_ulGetDtcCode_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  DAPI_BuildDECtxt
///
/// \descr  Stub function created to simulate the behaviour of DAPI_BuildDECtxt
///
/// \param  * const POSP_DE
/// \param  IE_EventType
/// \param  PIu32_DefaultCode
/// \param  PIu8_DTCFormatId
/// \param  PIu8_ECUCode
///
/// \return LDEH_TE_ErrVal
//-----------------------------------------------------------------------------
LDEH_TE_ErrVal DAPI_BuildDECtxt(LDEH_TS_DECtxt * const POSP_DE, const LDEH_TE_EvtType PIE_EventType,
  const Tu32_Int PIu32_DefaultCode, const Tu8_Int PIu8_DTCFormatId,
  const Tu8_Int PIu8_ECUCode)
{
  DAPI_BuildDECtxt_Param1 = POSP_DE;
  DAPI_BuildDECtxt_Param2 = PIE_EventType;
  DAPI_BuildDECtxt_Param3 = PIu32_DefaultCode;
  DAPI_BuildDECtxt_Param4 = PIu8_DTCFormatId;
  DAPI_BuildDECtxt_Param5 = PIu8_ECUCode;
  DAPI_BuildDECtxt_HitCount++;

  return DAPI_BuildDECtxt_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  DAPI_AddDE
///
/// \descr  Stub function created to simulate the behaviour of DAPI_AddDE
///
/// \param  * const PISP_DE
/// \param  PIE_IsNewDE
///
/// \return LDEH_TE_ErrVal
//-----------------------------------------------------------------------------
LDEH_TE_ErrVal DAPI_AddDE(LDEH_TS_DECtxt const * const PISP_DE, const TE_Bool PIE_IsNewDE)
{
  DAPI_AddDE_Param1 = PISP_DE;
  DAPI_AddDE_Param2 = PIE_IsNewDE;
  DAPI_AddDE_HitCount++;

  return DAPI_AddDE_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  LGM_InitMessage
///
/// \descr  Stub function created to simulate the behaviour of LGM_InitMessage
///
/// \param  ID
/// \param  * const dataRef
///
/// \return IL_StatusType
//-----------------------------------------------------------------------------
IL_StatusType LGM_InitMessage(LGM_MessageIdentifier ID, const UINT8* const dataRef)
{
  LGM_InitMessage_Param1 = ID;
  for (uint8 i = 0u; i < 7u; i++)
  {
    LGM_InitMessage_Param2[i] = dataRef[i];
  }
  LGM_InitMessage_HitCount++;

  return LGM_InitMessage_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  IL_EnvoyerIpdu
///
/// \descr  Stub function created to simulate the behaviour of IL_EnvoyerIpdu
///
/// \param  ID
///
/// \return IL_StatusType
//-----------------------------------------------------------------------------
IL_StatusType IL_EnvoyerIpdu(tindexIpdu ID)
{
  IL_EnvoyerIpdu_Param1 = ID;
  IL_EnvoyerIpdu_HitCount++;

  return IL_EnvoyerIpdu_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_IoHwAbUser_GetMountingSide
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_IoHwAbUser_GetMountingSide
///
/// \param  *ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_IoHwAbUser_GetMountingSide(teRte_MountingSide* ppara1)
{
  *ppara1 = Rte_Read_IoHwAbUser_GetMountingSide_Param1;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount++;

  return Rte_Read_IoHwAbUser_GetMountingSide_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief ErrCust_GetActualErrorIndex
///
/// \descr Get actual error dtc index based on Alec Index input
///
/// \param  unAlecId: Alec Id
///
/// \return uint8: Error Dtc Index
//-----------------------------------------------------------------------------
uint8 ErrCust_GetActualErrorIndex(uint16 unAlecId)
{
  ErrCust_GetActualErrorIndex_Param1 = unAlecId;
  ErrCust_GetActualErrorIndex_HitCount++;

  return ErrCust_GetActualErrorIndex_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief DAPI_SetSafetyConditions
///
/// \descr Set safety conditions for the DEH module
///
/// \param  PIE_value: TRUE or FALSE if safety conditions are OK
///
/// \return void
//-----------------------------------------------------------------------------
void DAPI_SetSafetyConditions(const TE_Bool PIE_value)
{
  DAPI_SetSafetyConditions_Param1 = PIE_value;
  DAPI_SetSafetyConditions_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Dem_SetEventStatus
///
/// \descr  Stub function created to simulate the behaviour of E2E checks on the
///
/// \param  unAlecId        : ID of the DTC to be set
/// \param  ucTestStatus    : evaluated status of the DTC
///
/// \return void
//-----------------------------------------------------------------------------
void Dem_SetEventStatus(uint16 unAlecId, uint8 ucTestStatus)
{
  Dem_SetEventStatus_Param1 = unAlecId;
  Dem_SetEventStatus_Param2 = ucTestStatus;
  Dem_SetEventStatus_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  NvM_WriteBlock
///
/// \descr  Stub function created to simulate the behaviour of NvM_WriteBlock
///
/// \param  BlockId
/// \param  *NvM_SrcPtr
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
/// \brief  Dem_Set_Init_Window
///
/// \descr  Stub function created to simulate the behaviour of Dem_Set_Init_Window
///
/// \param  boWindow
///
/// \return void
//-----------------------------------------------------------------------------
void  Dem_Set_Init_Window(boolean boWindow)
{
  Dem_Set_Init_Window_Param1 = boWindow;
  Dem_Set_Init_Window_HitCount++;
}

// EOF

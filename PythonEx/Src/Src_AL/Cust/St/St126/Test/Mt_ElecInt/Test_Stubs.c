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
tieFeeState            Fee_State;
MemIf_JobResultType    Fee_JobResult;
TE_Bool                EAPI_SetSafetyConditions_Param1;
LGM_BOOL               NM_ProhibitDefectMemorization_Param1;
LDEH_TE_PermFifo       DAPI_PermFifoStorage_Param1;
NM_ControlType_Type    NM_CommunicationControl_Param1;
LDEH_TE_PermToSend     DAPI_SetPermToSend_Param1;
NM_ModeType            NM_GetMode_Param1;
uint8                  EcuM_RequestRUN_Param1;
uint8                  EcuM_ReleasePOST_RUN_Param1;
boolean                Rte_Write_ElecInt_EnableCallbacks_Param1;
boolean                Rte_Write_ElecInt_ActivateTxBufer_Param1;
uint8                  Rte_Write_ElecInt_RequestRUN_Param1;
uint8                  Rte_Write_ElecInt_ReleasePOST_RUN_Param1;
uint8                  Rte_Write_ElecInt_ReleaseRUN_Param1;


//=============================================================================
// Stub function returned value stubs
//=============================================================================
LEIM_TE_ActionRequest  EAPI_MainFunction_RetVal;
NM_ErrorCodeType       NM_CommunicationControl_RetVal;
LEIM_TE_CurrentEIMode  EAPI_GetCurrentEIMode_RetVal;
NM_ErrorCodeType       NM_GetMode_RetVal;
Std_ReturnType         Rte_Write_ElecInt_EnableCallbacks_RetVal;
Std_ReturnType         Rte_Write_ElecInt_ActivateTxBufer_RetVal;
Std_ReturnType         Rte_Write_ElecInt_RequestRUN_RetVal;
Std_ReturnType         Rte_Write_ElecInt_ReleasePOST_RUN_RetVal;
Std_ReturnType         Rte_Write_ElecInt_ReleaseRUN_RetVal;


//=============================================================================
// Stub function hit count variables
//=============================================================================
uint32                 EAPI_InitModule_HitCount;
uint32                 EAPI_SetSafetyConditions_HitCount;
uint32                 EAPI_MainFunction_HitCount;
uint32                 NM_ProhibitDefectMemorization_HitCount;
uint32                 DAPI_PermFifoStorage_HitCount;
uint32                 NM_CommunicationControl_HitCount;
uint32                 DAPI_SetPermToSend_HitCount;
uint32                 EAPI_GetCurrentEIMode_HitCount;
uint32                 NM_GetMode_HitCount;
uint32                 EcuM_RequestRUN_HitCount;
uint32                 EcuM_ReleasePOST_RUN_HitCount;
uint32                 SigPrepRx_ComM_EnableCallbacks_HitCount;
uint32                 SigPrepTx_ComM_ActivateTxBufer_HitCount;
uint32                 Rte_Write_ElecInt_EnableCallbacks_HitCount;
uint32                 Rte_Write_ElecInt_ActivateTxBufer_HitCount;
uint32                 Rte_Write_ElecInt_RequestRUN_HitCount;
uint32                 Rte_Write_ElecInt_ReleasePOST_RUN_HitCount;
uint32                 Rte_Write_ElecInt_ReleaseRUN_HitCount;
uint32                 SigPrepRx_ComM_DisableCallbacks_HitCount;
uint32                 SigPrepTx_ComM_DeactivateTxBuffer_HitCount;


//=============================================================================
// Stub function definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  EAPI_InitModule
///
/// \descr  Stub function created to simulate the behaviour of EAPI_InitModule
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void EAPI_InitModule(void)
{
  EAPI_InitModule_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  EAPI_SetSafetyConditions
///
/// \descr  Stub function created to simulate the behaviour of EAPI_SetSafetyConditions
///
/// \param  PIE_SafetyConditionsCheck
///
/// \return void
//-----------------------------------------------------------------------------
void EAPI_SetSafetyConditions(TE_Bool PIE_SafetyConditionsCheck)
{
  EAPI_SetSafetyConditions_Param1 = PIE_SafetyConditionsCheck;
  EAPI_SetSafetyConditions_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  EAPI_MainFunction
///
/// \descr  Stub function created to simulate the behaviour of EAPI_MainFunction
///
/// \param  void
///
/// \return LEIM_TE_ActionRequest
//-----------------------------------------------------------------------------
LEIM_TE_ActionRequest EAPI_MainFunction(void)
{
  EAPI_MainFunction_HitCount++;

  return EAPI_MainFunction_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  NM_ProhibitDefectMemorization
///
/// \descr  Stub function created to simulate the behaviour of NM_ProhibitDefectMemorization
///
/// \param  b_IsProhibited
///
/// \return void
//-----------------------------------------------------------------------------
void NM_ProhibitDefectMemorization(LGM_BOOL b_IsProhibited)
{
  NM_ProhibitDefectMemorization_Param1 = b_IsProhibited;
  NM_ProhibitDefectMemorization_HitCount++;
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
/// \brief  NM_CommunicationControl
///
/// \descr  Stub function created to simulate the behaviour of NM_CommunicationControl
///
/// \param  ControlType
///
/// \return NM_ErrorCodeType
//-----------------------------------------------------------------------------
NM_ErrorCodeType NM_CommunicationControl(NM_ControlType_Type ControlType)
{
  NM_CommunicationControl_Param1 = ControlType;
  NM_CommunicationControl_HitCount++;

  return NM_CommunicationControl_RetVal;
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
/// \brief  EAPI_GetCurrentEIMode
///
/// \descr  Stub function created to simulate the behaviour of EAPI_GetCurrentEIMode
///
/// \param  void
///
/// \return LEIM_TE_CurrentEIMode
//-----------------------------------------------------------------------------
LEIM_TE_CurrentEIMode EAPI_GetCurrentEIMode(void)
{
  EAPI_GetCurrentEIMode_HitCount++;

  return EAPI_GetCurrentEIMode_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  NM_GetMode
///
/// \descr  Stub function created to simulate the behaviour of NM_GetMode
///
/// \param  *p_NMMode
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
/// \brief  EcuM_RequestRUN
///
/// \descr  Stub function created to simulate the behaviour of EcuM_RequestRUN
///
/// \param  ucUser
///
/// \return void
//-----------------------------------------------------------------------------
void EcuM_RequestRUN(uint8 ucUser)
{
  EcuM_RequestRUN_Param1 = ucUser;
  EcuM_RequestRUN_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  EcuM_ReleasePOST_RUN
///
/// \descr  Stub function created to simulate the behaviour of EcuM_ReleasePOST_RUN
///
/// \param  ucUser
///
/// \return void
//-----------------------------------------------------------------------------
void EcuM_ReleasePOST_RUN(uint8 ucUser)
{
  EcuM_ReleasePOST_RUN_Param1 = ucUser;
  EcuM_ReleasePOST_RUN_HitCount++;
}


//-----------------------------------------------------------------------------
/// \brief  SigPrepRx_ComM_EnableCallbacks
///
/// \descr  Stub function created to simulate the behaviour of SigPrepRx_ComM_EnableCallbacks
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void SigPrepRx_ComM_EnableCallbacks(void)
{
  SigPrepRx_ComM_EnableCallbacks_HitCount++;
}


//-----------------------------------------------------------------------------
/// \brief  SigPrepTx_ComM_ActivateTxBufer
///
/// \descr  Stub function created to simulate the behaviour of SigPrepTx_ComM_ActivateTxBufer
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void SigPrepTx_ComM_ActivateTxBufer(void)
{
  SigPrepTx_ComM_ActivateTxBufer_HitCount++;
}



//-----------------------------------------------------------------------------
/// \brief  Rte_Write_ElecInt_EnableCallbacks
///
/// \descr  Stub function to simulate the behaviour of Rte_Write_ElecInt_EnableCallbacks
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_ElecInt_EnableCallbacks(boolean ppara1)
{
  Rte_Write_ElecInt_EnableCallbacks_Param1 = ppara1;
  Rte_Write_ElecInt_EnableCallbacks_HitCount++;

  return Rte_Write_ElecInt_EnableCallbacks_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_ElecInt_ActivateTxBufer
///
/// \descr  Stub function to simulate the behaviour of Rte_Write_ElecInt_ActivateTxBufer
///
/// \param  para1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_ElecInt_ActivateTxBufer(boolean para1)
{
  Rte_Write_ElecInt_ActivateTxBufer_Param1 = para1;
  Rte_Write_ElecInt_ActivateTxBufer_HitCount++;

  return Rte_Write_ElecInt_ActivateTxBufer_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_ElecInt_RequestRUN
///
/// \descr  Stub function to simulate the behaviour of Rte_Write_ElecInt_RequestRUN
///
/// \param  *ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_ElecInt_RequestRUN(const uint8* ppara1)
{
  Rte_Write_ElecInt_RequestRUN_Param1 = *ppara1;
  Rte_Write_ElecInt_RequestRUN_HitCount++;

  return Rte_Write_ElecInt_RequestRUN_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_ElecInt_ReleasePOST_RUN
///
/// \descr  Stub function to simulate the behaviour of Rte_Write_ElecInt_ReleasePOST_RUN
///
/// \param  *ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_ElecInt_ReleasePOST_RUN(const uint8* ppara1)
{
  Rte_Write_ElecInt_ReleasePOST_RUN_Param1 = *ppara1;
  Rte_Write_ElecInt_ReleasePOST_RUN_HitCount++;

  return Rte_Write_ElecInt_ReleasePOST_RUN_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  SigPrepRx_ComM_DisableCallbacks
///
/// \descr  Stub function created to simulate the behaviour of SigPrepRx_ComM_DisableCallbacks
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void SigPrepRx_ComM_DisableCallbacks(void)
{
  SigPrepRx_ComM_DisableCallbacks_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  SigPrepTx_ComM_DeactivateTxBuffer
///
/// \descr  Stub function created to simulate the behaviour of SigPrepTx_ComM_DeactivateTxBuffer
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void SigPrepTx_ComM_DeactivateTxBuffer(void)
{
  SigPrepTx_ComM_DeactivateTxBuffer_HitCount++;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Write_ElecInt_ReleaseRUN
///
/// \descr  Stub function to simulate the behaviour of the Rte_Write_ElecInt_ReleaseRUN
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_ElecInt_ReleaseRUN(const uint8* ppara1)
{
  Rte_Write_ElecInt_ReleaseRUN_Param1 = *ppara1;
  Rte_Write_ElecInt_ReleaseRUN_HitCount++;

  return Rte_Write_ElecInt_ReleaseRUN_RetVal;
}


// EOF


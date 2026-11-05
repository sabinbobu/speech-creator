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
#include <_NM_Types.h>
#include <LgmEIMMainAPI.h>
#include <LgmDEHMainAPI.h>
#include <SigPrepRx.h>
#include <SigPrepTx.h>
#include <Fee.h>


//=============================================================================
// Stub function declarations
//=============================================================================
void                   EAPI_InitModule(void);
void                   EAPI_SetSafetyConditions(TE_Bool PIE_SafetyConditionsCheck);
LEIM_TE_ActionRequest  EAPI_MainFunction(void);
void                   NM_ProhibitDefectMemorization(LGM_BOOL b_IsProhibited);
void                   DAPI_PermFifoStorage(const LDEH_TE_PermFifo PIE_FifoStoragePerm);
NM_ErrorCodeType       NM_CommunicationControl(NM_ControlType_Type ControlType);
void                   DAPI_SetPermToSend(const LDEH_TE_PermToSend PIE_PermToSend);
LEIM_TE_CurrentEIMode  EAPI_GetCurrentEIMode(void);
NM_ErrorCodeType       NM_GetMode(NM_ModeType * p_NMMode);
void                   EcuM_RequestRUN(uint8 ucUser);
void                   EcuM_ReleasePOST_RUN(uint8 ucUser);
void                   SigPrepRx_ComM_EnableCallbacks(void);
void                   SigPrepTx_ComM_ActivateTxBufer(void);
Std_ReturnType         Rte_Write_ElecInt_EnableCallbacks(boolean ppara1);
Std_ReturnType         Rte_Write_ElecInt_ActivateTxBufer(boolean para1);
Std_ReturnType         Rte_Write_ElecInt_RequestRUN(const uint8* ppara1);
Std_ReturnType         Rte_Write_ElecInt_ReleasePOST_RUN(const uint8* ppara1);
Std_ReturnType         Rte_Write_ElecInt_ReleaseRUN(const uint8* ppara1);
void                   SigPrepRx_ComM_DisableCallbacks(void);
void                   SigPrepTx_ComM_DeactivateTxBuffer(void);


//=============================================================================
// Stub function parameter stubs
//=============================================================================
extern tieFeeState            Fee_State;
extern MemIf_JobResultType    Fee_JobResult;
extern TE_Bool                EAPI_SetSafetyConditions_Param1;
extern LGM_BOOL               NM_ProhibitDefectMemorization_Param1;
extern LDEH_TE_PermFifo       DAPI_PermFifoStorage_Param1;
extern NM_ControlType_Type    NM_CommunicationControl_Param1;
extern LDEH_TE_PermToSend     DAPI_SetPermToSend_Param1;
extern NM_ModeType            NM_GetMode_Param1;
extern uint8                  EcuM_RequestRUN_Param1;
extern uint8                  EcuM_ReleasePOST_RUN_Param1;
extern boolean                Rte_Write_ElecInt_EnableCallbacks_Param1;
extern boolean                Rte_Write_ElecInt_ActivateTxBufer_Param1;
extern uint8                  Rte_Write_ElecInt_RequestRUN_Param1;
extern uint8                  Rte_Write_ElecInt_ReleasePOST_RUN_Param1;
extern uint8                  Rte_Write_ElecInt_ReleaseRUN_Param1;


//=============================================================================
// Stub function returned value stubs
//=============================================================================
extern LEIM_TE_ActionRequest  EAPI_MainFunction_RetVal;
extern NM_ErrorCodeType       NM_CommunicationControl_RetVal;
extern LEIM_TE_CurrentEIMode  EAPI_GetCurrentEIMode_RetVal;
extern NM_ErrorCodeType       NM_GetMode_RetVal;
extern Std_ReturnType         Rte_Write_ElecInt_EnableCallbacks_RetVal;
extern Std_ReturnType         Rte_Write_ElecInt_ActivateTxBufer_RetVal;
extern Std_ReturnType         Rte_Write_ElecInt_RequestRUN_RetVal;
extern Std_ReturnType         Rte_Write_ElecInt_ReleasePOST_RUN_RetVal;
extern Std_ReturnType         Rte_Write_ElecInt_ReleaseRUN_RetVal;


//=============================================================================
// Stub function hit count variables
//=============================================================================
extern uint32                 EAPI_InitModule_HitCount;
extern uint32                 EAPI_SetSafetyConditions_HitCount;
extern uint32                 EAPI_MainFunction_HitCount;
extern uint32                 NM_ProhibitDefectMemorization_HitCount;
extern uint32                 DAPI_PermFifoStorage_HitCount;
extern uint32                 NM_CommunicationControl_HitCount;
extern uint32                 DAPI_SetPermToSend_HitCount;
extern uint32                 EAPI_GetCurrentEIMode_HitCount;
extern uint32                 NM_GetMode_HitCount;
extern uint32                 EcuM_RequestRUN_HitCount;
extern uint32                 EcuM_ReleasePOST_RUN_HitCount;
extern uint32                 SigPrepRx_ComM_EnableCallbacks_HitCount;
extern uint32                 SigPrepTx_ComM_ActivateTxBufer_HitCount;
extern uint32                 Rte_Write_ElecInt_EnableCallbacks_HitCount;
extern uint32                 Rte_Write_ElecInt_ActivateTxBufer_HitCount;
extern uint32                 Rte_Write_ElecInt_RequestRUN_HitCount;
extern uint32                 Rte_Write_ElecInt_ReleasePOST_RUN_HitCount;
extern uint32                 Rte_Write_ElecInt_ReleaseRUN_HitCount;
extern uint32                 SigPrepRx_ComM_DisableCallbacks_HitCount;
extern uint32                 SigPrepTx_ComM_DeactivateTxBuffer_HitCount;



#endif // TEST_STUBS_2023_08_25_H_

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
#include <AL_Helper.h>
#include <LgmDEHMainAPI.h>
#include <ErrCust.h>
#include <_IL_types.h>
#include <p_IL_messages.h>
#include <p_NM.h>
#include <LgmDEHConfig_Cfg.h>
#include <RteCommonTypes.h>
#include <Fee.h>
#include <Nvm.h>


//=============================================================================
// Stub function declarations
//=============================================================================
void                       DAPI_InitModule(const TE_Bool PIE_NVMEnable, const Tu8_Int PIu8_EcuCode);
void                       DAPI_PermFifoStorage(const LDEH_TE_PermFifo PIE_FifoStoragePerm);
void                       DAPI_SetPermToSend(const LDEH_TE_PermToSend PIE_PermToSend);
LDEH_TE_ErrVal             DAPI_ScheduleMainFunction(void);
void                       DAPI_SetMainStatus(const DAPI_TE_MainStatus PIE_value);
uint32                     ErrCust_ulGetDtcCode(uint8 ucDtcIndex);
LDEH_TE_ErrVal             DAPI_BuildDECtxt(LDEH_TS_DECtxt * const POSP_DE, const LDEH_TE_EvtType PIE_EventType,
                           const Tu32_Int PIu32_DefaultCode, const Tu8_Int PIu8_DTCFormatId,const Tu8_Int PIu8_ECUCode);
LDEH_TE_ErrVal             DAPI_AddDE(LDEH_TS_DECtxt const * const PISP_DE, const TE_Bool PIE_IsNewDE);
IL_StatusType              LGM_InitMessage(LGM_MessageIdentifier ID, const UINT8* const dataRef);
IL_StatusType              IL_EnvoyerIpdu(tindexIpdu ID);
Std_ReturnType             Rte_Read_IoHwAbUser_GetMountingSide(teRte_MountingSide* ppara1);
void                       DAPI_SetSafetyConditions(const TE_Bool PIE_value);
void                       APPLI_DEAck(LDEH_TS_DECtxt const * const PISP_DE);
void                       APPLI_DENotAck(LDEH_TS_DECtxt const * const PISP_DE);
uint8                      ErrCust_GetStatusOfDtc(uint8 ucDtcIndex);
uint8                      ErrCust_GetActualErrorIndex(uint16 unAlecId);
Std_ReturnType             NvM_WriteBlock(NvM_BlockIdType BlockId, void* NvM_SrcPtr);
void                       Deh_CheckSafetyConditions(void);
Std_ReturnType             Rte_Read_SysMon_LifePhases(tsRte_SysMon_LifePhases* ppara1);
Std_ReturnType             Rte_Read_SysMon_VehicleSpeed(tsRte_SysMon_VehicleSpeed* ppara1);
void                       Dem_Set_Init_Window(boolean boWindow);


//=============================================================================
// Stub function parameter stubs
//=============================================================================
extern tieFeeState                Fee_State;
extern MemIf_JobResultType        Fee_JobResult;
extern TE_Bool                    DAPI_InitModule_Param1;
extern Tu8_Int                    DAPI_InitModule_Param2;
extern LDEH_TE_PermFifo           DAPI_PermFifoStorage_Param1;
extern LDEH_TE_PermToSend         DAPI_SetPermToSend_Param1;
extern uint8                      ErrCust_ulGetDtcCode_Param1;
extern LDEH_TS_DECtxt *           DAPI_BuildDECtxt_Param1;
extern LDEH_TE_EvtType            DAPI_BuildDECtxt_Param2;
extern Tu32_Int                   DAPI_BuildDECtxt_Param3;
extern Tu8_Int                    DAPI_BuildDECtxt_Param4;
extern Tu8_Int                    DAPI_BuildDECtxt_Param5;
extern LDEH_TS_DECtxt *           DAPI_AddDE_Param1;
extern TE_Bool                    DAPI_AddDE_Param2;
extern LGM_MessageIdentifier      LGM_InitMessage_Param1;
extern UINT8                      LGM_InitMessage_Param2[8];
extern tindexIpdu                 IL_EnvoyerIpdu_Param1;
extern teRte_MountingSide         Rte_Read_IoHwAbUser_GetMountingSide_Param1;
extern TE_Bool                    DAPI_SetSafetyConditions_Param1;
extern DAPI_TE_MainStatus         DAPI_SetMainStatus_Param1;
extern uint16                     ErrCust_GetActualErrorIndex_Param1;
extern uint16                     Dem_SetEventStatus_Param1;
extern uint8                      Dem_SetEventStatus_Param2;
extern uint8                      ErrCust_GetStatusOfDtc_Param2;
extern NvM_BlockIdType            NvM_WriteBlock_Param1;
extern void*                      NvM_WriteBlock_Param2;
extern tsRte_SysMon_LifePhases    Rte_Read_SysMon_LifePhases_Param1;
extern tsRte_SysMon_VehicleSpeed  Rte_Read_SysMon_VehicleSpeed_Param1;
extern uint8                      ErrCust_ucGetStatusOfDTC_Param1;
extern uint8                      ErrCust_GetStatusOfDtc_Param1;
extern boolean                    Dem_Set_Init_Window_Param1;


//=============================================================================
// Stub function returned value stubs
//=============================================================================
extern LDEH_TE_ErrVal             DAPI_ScheduleMainFunction_RetVal;
extern uint32                     ErrCust_ulGetDtcCode_RetVal;
extern LDEH_TE_ErrVal             DAPI_BuildDECtxt_RetVal;
extern LDEH_TE_ErrVal             DAPI_AddDE_RetVal;
extern IL_StatusType              LGM_InitMessage_RetVal;
extern IL_StatusType              IL_EnvoyerIpdu_RetVal;
extern Std_ReturnType             Rte_Read_IoHwAbUser_GetMountingSide_RetVal;
extern uint8                      Rte_Read_SysMon_LifePhases_RetVal;
extern Std_ReturnType             Rte_Read_SysMon_VehicleSpeed_RetVal;
extern uint8                      ErrCust_GetActualErrorIndex_RetVal;
extern uint8                      ErrCust_GetStatusOfDtc_RetVal;
extern Std_ReturnType             NvM_WriteBlock_RetVal;
extern uint8                      ErrCust_ucGetStatusOfDTC_RetVal;


//=============================================================================
// Stub function hit count variables
//=============================================================================
extern uint32                     DAPI_InitModule_HitCount;
extern uint32                     DAPI_PermFifoStorage_HitCount;
extern uint32                     DAPI_SetPermToSend_HitCount;
extern uint32                     DAPI_ScheduleMainFunction_HitCount;
extern uint32                     ErrCust_ulGetDtcCode_HitCount;
extern uint32                     DAPI_BuildDECtxt_HitCount;
extern uint32                     DAPI_AddDE_HitCount;
extern uint32                     LGM_InitMessage_HitCount;
extern uint32                     IL_EnvoyerIpdu_HitCount;
extern uint32                     Rte_Read_IoHwAbUser_GetMountingSide_HitCount;
extern uint32                     ErrCust_GetActualErrorIndex_HitCount;
extern uint32                     DAPI_SetSafetyConditions_HitCount;
extern uint32                     DAPI_SetMainStatus_HitCount;
extern uint32                     Dem_SetEventStatus_HitCount;
extern uint32                     NvM_WriteBlock_HitCount;
extern uint32                     Deh_CheckSafetyConditions_HitCount;
extern uint8                      Rte_Read_SysMon_LifePhases_HitCount;
extern uint8                      Rte_Read_SysMon_VehicleSpeed_HitCount;
extern uint8                      ErrCust_GetStatusOfDtc_HitCount;
extern uint8                      ErrCust_ucGetStatusOfDTC_HitCount;
extern uint8                      Dem_Set_Init_Window_HitCount;


#endif // TEST_STUBS_2023_08_25_H_

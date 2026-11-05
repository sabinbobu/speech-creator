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
#include <stdio.h>
#include <RteCommonTypes.h>
#include <CommonTypes.h>
#include <CommonE2E.h>
#include <Lgm_Types.h>
#include <LgmDEHMainAPI.h>
#include <LgmEIMMainAPI.h>
#include <ProcessE2E.h>
#include <Bsw/Crc/Crc.h>
#include <CddEft.h>
#include <_NM_Types.h>


//=============================================================================
// Stub function declarations
//=============================================================================
Std_ReturnType    Rte_Write_SysMon_TgtLedSig_sVal(const tsRte_TgtLedSig0_ASIL* ppara1);
Std_ReturnType    Rte_Write_SysMon_StdLgtTi_Req(const tsRte_SysMonLgtTiReq* ppara1);
Std_ReturnType    Rte_Write_SysMon_StdLgtFcts_Req(const tsRte_SysMonLgtFctsReq* ppara1);
Std_ReturnType    Rte_Write_SysMon_Afs_Signals(const tsRte_SysMonAfsSignals* ppara1);
Std_ReturnType    Rte_Write_SysMon_LifePhases(tsRte_SysMon_LifePhases* ppara1);
Std_ReturnType    Rte_Write_SysMon_VehNetState(const tsRte_SysMon_VehNetState* ppara1);
Std_ReturnType    Rte_Write_SysMon_VehicleSpeed(const tsRte_SysMon_VehicleSpeed* ppara1);
Std_ReturnType    Rte_Write_SysMon_LowBeamCmd_Req(const teRte_ReqLightState* ppara1);
Std_ReturnType    Rte_Write_SysMon_TurnIndicatorCmd_Req(const teRte_ReqLightState* ppara1);
Std_ReturnType    Rte_Write_SysMon_LedState(const tsRte_SysMon_LedStates* ppara1);
Std_ReturnType    Rte_Write_SysMon_SetDiagMux(TE_Bool ppara1);
Std_ReturnType    Rte_Write_SysMon_SendFrame457(const tSysMon_SendFrame457* ppara1);
Std_ReturnType    Rte_Write_SysMon_SendFrame477(const tSysMon_SendFrame477* ppara1);
Std_ReturnType    Rte_Read_Cpm_TgtLedSig_sVal(tsRte_TgtLedSig0Arr* ppara1);
Std_ReturnType    Rte_Read_SysMon_StdLgtTi_Req(tsRte_SysMonLgtTiReq* ppara1);
Std_ReturnType    Rte_Read_SysMon_StdLgtFcts_Req(tsRte_SysMonLgtFctsReq* ppara1);
Std_ReturnType    Rte_Read_IoHwAbUser_GetMountingSide(teRte_MountingSide* ppara1);
Std_ReturnType    Rte_Read_SysMon_Afs_Signals(tsRte_SysMonAfsSignals* ppara1);
Std_ReturnType    Rte_Read_SysMon_LifePhases(tsRte_SysMon_LifePhases* ppara1);
Std_ReturnType    Rte_Read_SysMon_VehNetState(tsRte_SysMon_VehNetState* ppara1);
Std_ReturnType    Rte_Read_SysMon_VehicleSpeed(tsRte_SysMon_VehicleSpeed* ppara1);
Std_ReturnType    Rte_Read_DrvLedDiag(tsRte_Hs6_Diag_Drvled_L_457* ppara1);
Std_ReturnType    Rte_Read_DrvLedDiagR(tsRte_Hs6_Diag_Drvled_R_477* ppara1);
Std_ReturnType    Rte_Read_Dbl_SysMonTx_FullStatus(tsRte_Hs6_Diag_Drvled_BendingBeamFault* ppara1);
Std_ReturnType    Rte_Read_CodM_SysMon_CRC32(boolean* ppara1);
Std_ReturnType    Rte_Read_CodM_SysMon_Para(tsRteCodingParameters* ppara1);
Std_ReturnType    Rte_Read_SysMon_LowBeamCmd_Req(teRte_ReqLightState* ppara1);
Std_ReturnType    Rte_Read_CddLed_LedState(tsRte_LedStates* ppara1);
Std_ReturnType    Rte_Read_AdbMxb_Gfhb_Diag(boolean* ppara1);
Std_ReturnType    Rte_Read_FctR_LgtFctState(tsRte_LgtFctState* ppara1);
Std_ReturnType    Rte_Read_SigPrep_VehicleConfigSig(tsRte_SigPrep_VehicleConfigSig* ppara1);
Std_ReturnType    Rte_Read_MPU_ErrorCounter(uint32* ppara1);
Std_ReturnType    Rte_Read_CddLed_TgtLed_FaultStatus_ASIL(tsRte_TgtLedSig0_FaultStatus_ASIL* ppara1);
Std_ReturnType    Rte_Read_FctR_TiFailureStatus(boolean* ppara1);
Std_ReturnType    Rte_Read_SigPrep_ElecSupState(tsRte_SigPrep_ElecSupState* ppara1);
Std_ReturnType    Rte_Read_SigPrep_HS6_COMMANDES_VSM_036_Received(tHS6_COMMANDES_VSM_036* ppara1);
Std_ReturnType    Rte_Read_SigPrep_HS6_DAT_BSI_432_Received(tHS6_DAT_BSI_432* ppara1);
Std_ReturnType    Rte_Read_SigPrep_HS6_DAT_VSM_2AE_Received(tHS6_DAT_VSM_2AE* ppara1);
Std_ReturnType    Rte_Read_SigPrep_HS6_DAT_VSM_34E_Received(tHS6_DAT_VSM_34E* ppara1);
Std_ReturnType    Rte_Read_SigPrep_HS6_DYN_ABR_38D_Received(tHS6_DYN_ABR_38D* ppara1);
Std_ReturnType    Rte_Read_SigPrep_NMMode(NM_ModeType* ppara1);
Std_ReturnType    Rte_Read_ElecInt_EnableCallbacks(boolean* ppara1);
Std_ReturnType    Rte_Read_ElecInt_ActivateTxBufer(boolean* ppara1);
Std_ReturnType    Rte_Read_CddBoost_BoostState(tsRte_BoostState* ppara1);
Std_ReturnType    Rte_Read_SysVolt_LedVoltRng0_sVoltRng(teRte_SysVolt_Results* ppara1);
Std_ReturnType    Rte_Read_CtrlLed_LedChFbit(tsRte_LedChFbit* ppara1);
boolean           LPTMR_Check_Config(void);
void              EcuM_McuPrivilegeSwitch(uint8 ppara1);
void              LPTMR_INIT(const LPTMR_ConfigType* pparam1);
void              EEPR_Init(void);
TE_ReturnType     EEPR_MainFunction(void);
TE_ReturnType     EEPL_GetRawState(Tu8_Int const PIu8_ChunkId, EECO_TEP_ProfileOneChunkStatusPtr const POE_ChunkState);
void              Dem_SetEventStatus(uint16 unAlecId, uint8 ucTestStatus);
void              DAPI_BSIAckState(const Tu8_Int PIu8_AckCode);
void              DAPI_SetDiagMux(const TE_Bool PIE_DiagMuxOn);
void              DAPI_SetConfigMode(DAPI_TE_ConfigMode PIE_ConfigMode);
void              DAPI_SetMainStatus(const DAPI_TE_MainStatus PIE_value);
void              DAPI_SyncModule(const Tu32_Int PIu32_DateVehicle);
void              DAPI_RemoveAllDE(const TE_Bool PIE_RemoveState);
IL_StatusType     LGM_SendMessage(LGM_MessageIdentifier ID, const UINT8* const dataRef);
uint32            LPTMR0_GetTimeElapsed(const uint32 ulStartValue);
NM_ErrorCodeType  NM_GetMode(NM_ModeType * p_NMMode);
uint32            Crc_CalculateCRC32P4(CONST_AL uint8 *DataPtr, CONST_AL uint32 Length, CONST_AL uint32 StartValue32);
uint8             Crc_CalculateCRC8H2F(CONST_AL uint8 *DataPtr, CONST_AL uint32 Length, CONST_AL uint8  StartValue8);
void              LGM_HS6_COMMANDES_VSM_036_Received(void);
void              LGM_HS6_COMMANDES_VSM_036_NotReceived(void);
void              LGM_HS6_DAT_BSI_432_Received(void);
void              LGM_HS6_DAT_BSI_432_NotReceived(void);
void              LGM_HS6_DYN_ABR_38D_Received(void);
void              LGM_HS6_DYN_ABR_38D_NotReceived(void);
void              LGM_HS6_DIAG_DRVLED_Sent(void);
void              LGM_HS6_DIAG_DRVLED_NotSent(void);
void              LGM_HS6_DAT_VSM_2AE_Received(void);
void              LGM_HS6_DAT_VSM_2AE_NotReceived(void);
void              LGM_HS6_DAT_VSM_34E_Received(void);
void              LGM_HS6_DAT_VSM_34E_NotReceived(void);
boolean           CddEft_DataValid(void);


//=============================================================================
// Stub function parameter stubs
//=============================================================================
extern tsRte_TgtLedSig0_ASIL                   Rte_Write_SysMon_TgtLedSig_sVal_Param1;
extern tsRte_SysMonLgtTiReq                    Rte_Write_SysMon_StdLgtTi_Req_Param1;
extern tsRte_SysMonLgtFctsReq                  Rte_Write_SysMon_StdLgtFcts_Req_Param1;
extern tsRte_SysMonAfsSignals                  Rte_Write_SysMon_Afs_Signals_Param1;
extern tsRte_SysMon_LifePhases                 Rte_Write_SysMon_LifePhases_Param1;
extern tsRte_SysMon_VehNetState                Rte_Write_SysMon_VehNetState_Param1;
extern tsRte_SysMon_VehicleSpeed               Rte_Write_SysMon_VehicleSpeed_Param1;
extern teRte_ReqLightState                     Rte_Write_SysMon_LowBeamCmd_Req_Param1;
extern teRte_ReqLightState                     Rte_Write_SysMon_TurnIndicatorCmd_Req_Param1;
extern tsRte_LedStates                         Rte_Write_CddLed_LedState_Param1;
extern tsRte_SysMon_LedStates                  Rte_Write_SysMon_LedState_Param1;
extern TE_Bool                                 Rte_Write_SysMon_SetDiagMux_Param1;
extern tSysMon_SendFrame457                    Rte_Write_SysMon_SendFrame457_Param1;
extern tSysMon_SendFrame477                    Rte_Write_SysMon_SendFrame477_Param1;
extern tsRte_TgtLedSig0Arr                     Rte_Read_Cpm_TgtLedSig_sVal_Param1;
extern tsRte_SysMonLgtTiReq                    Rte_Read_SysMon_StdLgtTi_Req_Param1;
extern tsRte_SysMonLgtFctsReq                  Rte_Read_SysMon_StdLgtFcts_Req_Param1;
extern teRte_MountingSide                      Rte_Read_IoHwAbUser_GetMountingSide_Param1;
extern tsRte_SysMonAfsSignals                  Rte_Read_SysMon_Afs_Signals_Param1;
extern tsRte_SysMon_LifePhases                 Rte_Read_SysMon_LifePhases_Param1;
extern tsRte_SysMon_VehNetState                Rte_Read_SysMon_VehNetState_Param1;
extern tsRte_SysMon_VehicleSpeed               Rte_Read_SysMon_VehicleSpeed_Param1;
extern tsRte_Hs6_Diag_Drvled_L_457             Rte_Read_DrvLedDiag_Param1;
extern tsRte_Hs6_Diag_Drvled_R_477             Rte_Read_DrvLedDiagR_Param1;
extern tsRte_Hs6_Diag_Drvled_BendingBeamFault  Rte_Read_Dbl_SysMonTx_FullStatus_Param1;
extern boolean                                 Rte_Read_CodM_SysMon_CRC32_Param1;
extern tsRteCodingParameters                   Rte_Read_CodM_SysMon_Para_Param1;
extern teRte_ReqLightState                     Rte_Read_SysMon_LowBeamCmd_Req_Param1;
extern tsRte_LedStates                         Rte_Read_CddLed_LedState_Param1;
extern boolean                                 Rte_Read_AdbMxb_Gfhb_Diag_Param1;
extern tsRte_LgtFctState                       Rte_Read_FctR_LgtFctState_Param1;
extern tsRte_SigPrep_VehicleConfigSig          Rte_Read_SigPrep_VehicleConfigSig_Param1;
extern uint32                                  Rte_Read_MPU_ErrorCounter_Param1;
extern tsRte_TgtLedSig0_FaultStatus_ASIL       Rte_Read_CddLed_TgtLed_FaultStatus_ASIL_Param1;
extern boolean                                 Rte_Read_FctR_TiFailureStatus_Param1;
extern tsRte_SigPrep_ElecSupState              Rte_Read_SigPrep_ElecSupState_Param1;
extern tHS6_COMMANDES_VSM_036                  Rte_Read_SigPrep_HS6_COMMANDES_VSM_036_Received_Param1;
extern tHS6_DAT_BSI_432                        Rte_Read_SigPrep_HS6_DAT_BSI_432_Received_Param1;
extern tHS6_DAT_VSM_2AE                        Rte_Read_SigPrep_HS6_DAT_VSM_2AE_Received_Param1;
extern tHS6_DAT_VSM_34E                        Rte_Read_SigPrep_HS6_DAT_VSM_34E_Received_Param1;
extern tHS6_DYN_ABR_38D                        Rte_Read_SigPrep_HS6_DYN_ABR_38D_Received_Param1;
extern NM_ModeType                             Rte_Read_SigPrep_NMMode_Param1;
extern boolean                                 Rte_Read_ElecInt_EnableCallbacks_Param1;
extern boolean                                 Rte_Read_ElecInt_ActivateTxBufer_Param1;
extern tsRte_BoostState                        Rte_Read_CddBoost_BoostState_Param1;
extern teRte_SysVolt_Results                   Rte_Read_SysVolt_LedVoltRng0_sVoltRng_Param1;
extern tsRte_LedChFbit                         Rte_Read_CtrlLed_LedChFbit_Param1;
extern uint8                                   EcuM_McuPrivilegeSwitch_Param1;
extern LPTMR_ConfigType                        LPTMR_INIT_Param1_Val;
extern Tu8_Int                                 DAPI_BSIAckState_Param1;
extern TE_Bool                                 Rte_Write_SysMon_SetDiagMux_Param1;
extern DAPI_TE_ConfigMode                      DAPI_SetConfigMode_Param1;
extern DAPI_TE_MainStatus                      DAPI_SetMainStatus_Param1;
extern Tu32_Int                                DAPI_SyncModule_Param1;
extern TE_Bool                                 DAPI_RemoveAllDE_Param1;
extern LGM_MessageIdentifier                   LGM_SendMessage_Param1;
extern UINT8                                   LGM_SendMessage_Param2;
extern uint32                                  LPTMR0_GetTimeElapsed_Param1;
extern uint16                                  Dem_SetEventStatus_Param1;
extern uint8                                   Dem_SetEventStatus_Param2;
extern uint8*                                  Crc_CalculateCRC32P4_Param1;
extern uint32                                  Crc_CalculateCRC32P4_Param2;
extern uint32                                  Crc_CalculateCRC32P4_Param3;
extern uint8*                                  Crc_CalculateCRC8H2F_Param1;
extern uint32                                  Crc_CalculateCRC8H2F_Param2;
extern uint8                                   Crc_CalculateCRC8H2F_Param3;
extern NM_ModeType                             NM_GetMode_Param1;
extern Tu8_Int                                 EEPL_GetRawState_Param1;
extern EECO_TEP_ProfileOneChunkStatusPtr       EEPL_GetRawState_Param2;


//=============================================================================
// Stub function returned value stubs
//=============================================================================
extern Std_ReturnType    Rte_Write_SysMon_TgtLedSig_sVal_RetVal;
extern Std_ReturnType    Rte_Write_SysMon_StdLgtTi_Req_RetVal;
extern Std_ReturnType    Rte_Write_SysMon_StdLgtFcts_Req_RetVal;
extern Std_ReturnType    Rte_Write_SysMon_Afs_Signals_RetVal;
extern Std_ReturnType    Rte_Write_SysMon_LifePhases_RetVal;
extern Std_ReturnType    Rte_Write_SysMon_VehNetState_RetVal;
extern Std_ReturnType    Rte_Write_SysMon_VehicleSpeed_RetVal;
extern Std_ReturnType    Rte_Write_SysMon_LowBeamCmd_Req_RetVal;
extern Std_ReturnType    Rte_Write_SysMon_TurnIndicatorCmd_Req_RetVal;
extern Std_ReturnType    Rte_Write_SysMon_LedState_RetVal;
extern Std_ReturnType    Rte_Write_DEM_SetEvent_MasterPort_RetVal;
extern Std_ReturnType    Rte_Write_SysMon_SetDiagMux_RetVal;
extern Std_ReturnType    Rte_Write_SysMon_SendFrame457_RetVal;
extern Std_ReturnType    Rte_Write_SysMon_SendFrame477_RetVal;
extern Std_ReturnType    Rte_Read_Cpm_TgtLedSig_sVal_RetVal;
extern Std_ReturnType    Rte_Read_SysMon_StdLgtTi_Req_RetVal;
extern Std_ReturnType    Rte_Read_SysMon_StdLgtFcts_Req_RetVal;
extern Std_ReturnType    Rte_Read_IoHwAbUser_GetMountingSide_RetVal;
extern Std_ReturnType    Rte_Read_SysMon_Afs_Signals_RetVal;
extern Std_ReturnType    Rte_Read_SysMon_LifePhases_RetVal;
extern Std_ReturnType    Rte_Read_SysMon_VehNetState_RetVal;
extern Std_ReturnType    Rte_Read_SysMon_VehicleSpeed_RetVal;
extern Std_ReturnType    Rte_Read_DrvLedDiag_RetVal;
extern Std_ReturnType    Rte_Read_DrvLedDiagR_RetVal;
extern Std_ReturnType    Rte_Read_Dbl_SysMonTx_FullStatus_RetVal;
extern Std_ReturnType    Rte_Read_CodM_SysMon_CRC32_RetVal;
extern Std_ReturnType    Rte_Read_CodM_SysMon_Para_RetVal;
extern Std_ReturnType    Rte_Read_SysMon_LowBeamCmd_Req_RetVal;
extern Std_ReturnType    Rte_Read_CddLed_LedState_RetVal;
extern Std_ReturnType    Rte_Read_AdbMxb_Gfhb_Diag_RetVal;
extern Std_ReturnType    Rte_Read_FctR_LgtFctState_RetVal;
extern Std_ReturnType    Rte_Read_DEM_SetEvent_MasterPort_RetVal;
extern Std_ReturnType    Rte_Read_SigPrep_VehicleConfigSig_RetVal;
extern Std_ReturnType    Rte_Read_MPU_ErrorCounter_RetVal;
extern Std_ReturnType    Rte_Read_CddLed_TgtLed_FaultStatus_ASIL_RetVal;
extern Std_ReturnType    Rte_Read_FctR_TiFailureStatus_RetVal;
extern Std_ReturnType    Rte_Read_SigPrep_ElecSupState_RetVal;
extern Std_ReturnType    Rte_Read_SigPrep_HS6_COMMANDES_VSM_036_Received_RetVal;
extern Std_ReturnType    Rte_Read_SigPrep_HS6_DAT_BSI_432_Received_RetVal;
extern Std_ReturnType    Rte_Read_SigPrep_HS6_DAT_VSM_2AE_Received_RetVal;
extern Std_ReturnType    Rte_Read_SigPrep_HS6_DAT_VSM_34E_Received_RetVal;
extern Std_ReturnType    Rte_Read_SigPrep_HS6_DYN_ABR_38D_Received_RetVal;
extern Std_ReturnType    Rte_Read_SigPrep_NMMode_RetVal;
extern Std_ReturnType    Rte_Read_ElecInt_EnableCallbacks_RetVal;
extern Std_ReturnType    Rte_Read_ElecInt_ActivateTxBufer_RetVal;
extern Std_ReturnType    Rte_Read_CddBoost_BoostState_RetVal;
extern Std_ReturnType    Rte_Read_SysVolt_LedVoltRng0_sVoltRng_RetVal;
extern Std_ReturnType    Rte_Read_CtrlLed_LedChFbit_RetVal;
extern IL_StatusType     LGM_SendMessage_RetVal;
extern uint32            LPTMR0_GetTimeElapsed_RetVal;
extern TE_ReturnType     EEPR_MainFunction_RetVal;
extern uint32            Crc_CalculateCRC32P4_RetVal;
extern uint8             Crc_CalculateCRC8H2F_RetVal;
extern boolean           LPTMR_Check_Config_RetVal;
extern NM_ErrorCodeType  NM_GetMode_RetVal;
extern boolean           CddEft_DataValid_RetVal;
extern TE_ReturnType     EEPL_GetRawState_RetVal;


//=============================================================================
// Stub function hit count variables
//=============================================================================
extern uint8   Rte_Write_SysMon_TgtLedSig_sVal_HitCount;
extern uint8   Rte_Write_SysMon_StdLgtTi_Req_HitCount;
extern uint8   Rte_Write_SysMon_StdLgtFcts_Req_HitCount;
extern uint8   Rte_Write_SysMon_Afs_Signals_HitCount;
extern uint8   Rte_Write_SysMon_LifePhases_HitCount;
extern uint8   Rte_Write_SysMon_VehNetState_HitCount;
extern uint8   Rte_Write_SysMon_VehicleSpeed_HitCount;
extern uint8   Rte_Write_SysMon_LowBeamCmd_Req_HitCount;
extern uint8   Rte_Write_SysMon_TurnIndicatorCmd_Req_HitCount;
extern uint8   Rte_Write_SysMon_LedState_HitCount;
extern uint8   Rte_Write_DEM_SetEvent_MasterPort_HitCount;
extern uint8   Rte_Write_SysMon_SetDiagMux_HitCount;
extern uint8   Rte_Write_SysMon_SendFrame457_HitCount;
extern uint8   Rte_Write_SysMon_SendFrame477_HitCount;
extern uint8   Rte_Read_Cpm_TgtLedSig_sVal_HitCount;
extern uint8   Rte_Read_SysMon_StdLgtTi_Req_HitCount;
extern uint8   Rte_Read_SysMon_StdLgtFcts_Req_HitCount;
extern uint8   Rte_Read_IoHwAbUser_GetMountingSide_HitCount;
extern uint8   Rte_Read_SysMon_Afs_Signals_HitCount;
extern uint8   Rte_Read_SysMon_LifePhases_HitCount;
extern uint8   Rte_Read_SysMon_VehNetState_HitCount;
extern uint8   Rte_Read_SysMon_VehicleSpeed_HitCount;
extern uint8   Rte_Read_DrvLedDiag_HitCount;
extern uint8   Rte_Read_DrvLedDiagR_HitCount;
extern uint8   Rte_Read_Dbl_SysMonTx_FullStatus_HitCount;
extern uint8   Rte_Read_CodM_SysMon_CRC32_HitCount;
extern uint8   Rte_Read_CodM_SysMon_Para_HitCount;
extern uint8   Rte_Read_SysMon_LowBeamCmd_Req_HitCount;
extern uint8   Rte_Read_CddLed_LedState_HitCount;
extern uint8   Rte_Read_AdbMxb_Gfhb_Diag_HitCount;
extern uint8   Rte_Read_FctR_LgtFctState_HitCount;
extern uint8   Rte_Read_DEM_SetEvent_MasterPort_HitCount;
extern uint8   Rte_Read_SigPrep_VehicleConfigSig_HitCount;
extern uint8   Rte_Read_MPU_ErrorCounter_HitCount;
extern uint8   Rte_Read_CddLed_TgtLed_FaultStatus_ASIL_HitCount;
extern uint8   Rte_Read_FctR_TiFailureStatus_HitCount;
extern uint8   Rte_Read_SigPrep_ElecSupState_HitCount;
extern uint8   Rte_Read_SigPrep_HS6_COMMANDES_VSM_036_Received_HitCount;
extern uint8   Rte_Read_SigPrep_HS6_DAT_BSI_432_Received_HitCount;
extern uint8   Rte_Read_SigPrep_HS6_DAT_VSM_2AE_Received_HitCount;
extern uint8   Rte_Read_SigPrep_HS6_DAT_VSM_34E_Received_HitCount;
extern uint8   Rte_Read_SigPrep_HS6_DYN_ABR_38D_Received_HitCount;
extern uint8   Rte_Read_SigPrep_NMMode_HitCount;
extern uint8   Rte_Read_ElecInt_EnableCallbacks_HitCount;
extern uint8   Rte_Read_ElecInt_ActivateTxBufer_HitCount;
extern uint8   Rte_Read_CddBoost_BoostState_HitCount;
extern uint8   Rte_Read_SysVolt_LedVoltRng0_sVoltRng_HitCount;
extern uint8   Rte_Read_CtrlLed_LedChFbit_HitCount;
extern uint8   EEPR_Init_HitCount;
extern uint8   EEPR_MainFunction_HitCount;
extern uint8   EEPL_GetRawState_HitCount;
extern uint8   Dem_SetEventStatus_HitCount;
extern uint8   DAPI_BSIAckState_HitCount;
extern uint8   Rte_Write_SysMon_SetDiagMux_HitCount;
extern uint8   DAPI_SetConfigMode_HitCount;
extern uint8   DAPI_SetMainStatus_HitCount;
extern uint8   DAPI_SyncModule_HitCount;
extern uint32  DAPI_RemoveAllDE_HitCount;
extern uint8   LGM_SendMessage_HitCount;
extern uint8   LPTMR0_GetTimeElapsed_HitCount;
extern uint8   Crc_CalculateCRC32P4_HitCount;
extern uint8   LPTMR_Check_Config_HitCount;
extern uint8   EcuM_McuPrivilegeSwitch_HitCount;
extern uint8   LPTMR_INIT_HitCount;
extern uint8   Crc_CalculateCRC8H2F_HitCount;
extern uint8   NM_GetMode_HitCount;
extern uint8   CddEft_DataValid_HitCount;
extern uint8   LGM_HS6_COMMANDES_VSM_036_Received_HitCount;
extern uint8   LGM_HS6_COMMANDES_VSM_036_NotReceived_HitCount;
extern uint8   LGM_HS6_DAT_BSI_432_Received_HitCount;
extern uint8   LGM_HS6_DAT_BSI_432_NotReceived_HitCount;
extern uint8   LGM_HS6_DYN_ABR_38D_Received_HitCount;
extern uint8   LGM_HS6_DYN_ABR_38D_NotReceived_HitCount;
extern uint8   LGM_HS6_DIAG_DRVLED_Sent_HitCount;
extern uint8   LGM_HS6_DIAG_DRVLED_NotSent_HitCount;
extern uint8   LGM_HS6_DAT_VSM_2AE_Received_HitCount;
extern uint8   LGM_HS6_DAT_VSM_2AE_NotReceived_HitCount;
extern uint8   LGM_HS6_DAT_VSM_34E_Received_HitCount;
extern uint8   LGM_HS6_DAT_VSM_34E_NotReceived_HitCount;



#endif // TEST_STUBS_2023_08_25_H_

//*****************************************************************************
// (C) Marelli Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Marelli Automotive Lighting Reutlingen GmbH owns all the rights to this work. 
// This work shall not be copied, reproduced, used, modified, transferred 
// or its information shall not be disclosed without the prior written 
// authorization of Marelli Automotive Lighting Reutlingen GmbH. 
//*****************************************************************************

//-----------------------------------------------------------------------------
/// \file Rte_Cfg.h
/// 
/// \brief Configuration of the RTE. 
///
/// \descr 
///
/// \author ALRteGenerator version 0.28 from Dec 09 2021
/// 
//-----------------------------------------------------------------------------

#ifndef __RTE_CFG_H
#define __RTE_CFG_H

// Rte_Threads (stack sizes)
#define RTE_THREAD_T_HH   0x400
#define RTE_THREAD_T_HL   0x400
#define RTE_THREAD_T_LH   0x0
#define RTE_THREAD_T_LL   0x0
#define RTE_THREAD_U_HH   0x400
#define RTE_THREAD_U_HL   0xA00
#define RTE_THREAD_U_LH   0xC00
#define RTE_THREAD_U_LL   0x400

// the following part is NOT included in the linker scatter file!
#ifndef SCATTER_LOAD

#define ALRTEGENERATOR_VERSION_MAJOR 0
#define ALRTEGENERATOR_VERSION_MINOR 28
#define RTE_CFG_H_ID 1252364596

// *****************************************************************************
// includes
// *****************************************************************************
#include "Std_Types.h"
#include "stdint.h"
#include "Rte.h"
#include "RteCommonTypes.h"

// *****************************************************************************
// typedefinitions
// *****************************************************************************
#define RTECYC_rpCodM_Cycle0 0u         // 0 : Cycle/Offset = 100/7
#define RTECYC_rcSysMon_Cycle1ms 1u     // 1 : Cycle/Offset =  1/0
#define RTECYC_rpSchM_Func_NonTrusted_Cycle 2u // 2 : Cycle/Offset =  1/0
#define RTECYC_rcMemoryProc 3u          // 3 : Cycle/Offset =  5/0
#define RTECYC_rpSchM_Func_Trusted_Cycle 4u // 4 : Cycle/Offset =  1/0
#define RTECYC_rpCpm20ms 5u             // 5 : Cycle/Offset = 20/4
#define RTECYC_rpSysVolt_Cycle 6u       // 6 : Cycle/Offset = 20/0
#define RTECYC_rcStatM_Cycle10ms 7u     // 7 : Cycle/Offset = 100/0
#define RTECYC_rpRSens_Cycle0 8u        // 8 : Cycle/Offset = 20/3
#define RTECYC_rpDiagControl_Cycle0 9u  // 9 : Cycle/Offset = 20/7
#define RTECYC_rpFctR_Cycle 10u         // 10 : Cycle/Offset = 10/9
#define RTECYC_rpCtrlLed_Cycle0 11u     // 11 : Cycle/Offset =  5/3
#define RTECYC_rpCtrlSwiCycle0 12u      // 12 : Cycle/Offset = 10/5
#define RTECYC_rpCddLed_Cycle 13u       // 13 : Cycle/Offset = 20/4
#define RTECYC_rpCddBoost_Cycle 14u     // 14 : Cycle/Offset = 20/4
#define RTECYC_rpCddSpi_Cycle 15u       // 15 : Cycle/Offset =  1/0
#define RTECYC_rpCddSbc_Cycle0 16u      // 16 : Cycle/Offset = 20/5
#define RTECYC_rpCddSwi_Cycle0 17u      // 17 : Cycle/Offset = 10/5
#define RTECYC_rpAvacStat1_Cycle0 18u   // 18 : Cycle/Offset = 20/2
#define RTECYC_rpCddDcm_Cycle0 19u      // 19 : Cycle/Offset =  5/2
#define RTECYC_rpPitch_Cycle0 20u       // 20 : Cycle/Offset = 20/2
#define RTECYC_rpCtrlDcm_Cycle 21u      // 21 : Cycle/Offset = 20/4
#define RTECYC_RunnableCount 22u

typedef enum
{
  eRtePortSR_T_SysMon_E2Eexec,
  eRtePortSR_T_SysMon_StdLgtFcts_Req,
  eRtePortSR_T_SysMon_LowBeamCmd_Req,
  eRtePortSR_T_SysMon_TurnIndicatorCmd_Req,
  eRtePortSR_T_SysMon_StdLgtTi_Req,
  eRtePortSR_T_SysMon_VehicleSpeed,
  eRtePortSR_T_SysMon_VehNetState,
  eRtePortSR_T_SysMon_LifePhases,
  eRtePortSR_T_SysMon_SetDiagMux,
  eRtePortSR_T_SysMon_SendFrame457,
  eRtePortSR_T_SysMon_SendFrame477,
  eRtePortSR_T_SysMon_TgtLedSig_sVal,
  eRtePortSR_T_SysMon_LedState,
  eRtePortSR_T_IoHwAbUser_GetMountingSide,
  eRtePortSR_T_IoHwAb_User_GetAdc_DIAG_VBAT,
  eRtePortSR_T_IoHwAb_GetSens_Balanced,
  eRtePortSR_T_IoHwAb_GetSens_Raw,
  eRtePortSR_T_IoHwAb_GetPCB,
  eRtePortSR_T_IoHwAb_GetVoltage_NTCs,
  eRtePortSR_T_IoHwAb_VCCX1Voltage,
  eRtePortSR_T_MPU_ErrorCounter,
  eRtePortSR_T_EcuM_Deinit,
  eRtePortSR_T_CddLed_LedState,
  eRtePortSR_T_CddLed_Status,
  eRtePortSR_T_CddLed_TgtLed_FaultStatus_ASIL,
  eRtePortSR_T_CddBoost_BoostState,
  eRtePortSR_T_CddBoost_BoostStatus,
  eRtePortSR_T_Count
}eRtePortSR_T_t;

typedef enum
{
  eRtePortSR_U_CodM_FctR_Para,
  eRtePortSR_U_CodM_AppM_Para,
  eRtePortSR_U_CodM_CtrlLed_Para,
  eRtePortSR_U_CodM_Rsens_Para,
  eRtePortSR_U_CodM_CtrlFan_Para,
  eRtePortSR_U_CodM_SysVolt_Para,
  eRtePortSR_U_CodM_CddLed_Para,
  eRtePortSR_U_CodM_CddSwi_Para,
  eRtePortSR_U_CodM_CddBoost_Para,
  eRtePortSR_U_CodM_SigPrep_Para,
  eRtePortSR_U_CodM_SysMon_Para,
  eRtePortSR_U_CodM_Anima_Para,
  eRtePortSR_U_CodM_Pitch_Para,
  eRtePortSR_U_CodM_IoHwAbUser_Para,
  eRtePortSR_U_CodM_Err_Para,
  eRtePortSR_U_Diag_LdActivationRoutineControl,
  eRtePortSR_U_Diag_DiagResetRequest,
  eRtePortSR_U_Diag_RequestPOST_RUN,
  eRtePortSR_U_Dcm_RoutineControl,
  eRtePortSR_U_SigPrep_YawSpeed,
  eRtePortSR_U_SigPrep_ElecSupState,
  eRtePortSR_U_SigPrep_VehicleConfigSig,
  eRtePortSR_U_SigPrep_DynamicSigs,
  eRtePortSR_U_SigPrep_VehiclePitchAngle,
  eRtePortSR_U_SigPrep_NsoTrigger_Port,
  eRtePortSR_U_SigPrep_AnimationReq,
  eRtePortSR_U_SigPrep_VehTimeCntr,
  eRtePortSR_U_SigPrep_OdometerTotal,
  eRtePortSR_U_SigPrep_ElecIntegra,
  eRtePortSR_U_SigPrep_DcmDiagStatusR,
  eRtePortSR_U_SigPrep_LevellingTgtPos,
  eRtePortSR_U_SigPrep_HS6_DAT_VSM_2AE_Received,
  eRtePortSR_U_SigPrep_HS6_DAT_VSM_2AE_NotReceived,
  eRtePortSR_U_SigPrep_HS6_DAT_VSM_34E_Received,
  eRtePortSR_U_SigPrep_HS6_DAT_VSM_34E_NotReceived,
  eRtePortSR_U_SigPrep_HS6_COMMANDES_VSM_036_Received,
  eRtePortSR_U_SigPrep_HS6_COMMANDES_VSM_036_NotReceived,
  eRtePortSR_U_SigPrep_HS6_DAT_BSI_432_Received,
  eRtePortSR_U_SigPrep_HS6_DAT_BSI_432_NotReceived,
  eRtePortSR_U_SigPrep_HS6_DYN_ABR_38D_Received,
  eRtePortSR_U_SigPrep_HS6_DYN_ABR_38D_NotReceived,
  eRtePortSR_U_SigPrep_SleepBSI,
  eRtePortSR_U_SigPrep_NMMode,
  eRtePortSR_U_SigPrep_HS6_DIAG_DRVLED_Sent,
  eRtePortSR_U_SigPrep_HS6_DIAG_DRVLED_NotSent,
  eRtePortSR_U_DEM_UV_NotifyStatus,
  eRtePortSR_U_DEM_OV_NotifyStatus,
  eRtePortSR_U_DEM_350Lost_NotifyStatus,
  eRtePortSR_U_ElecInt_RequestRUN,
  eRtePortSR_U_ElecInt_ReleaseRUN,
  eRtePortSR_U_ElecInt_ReleasePOST_RUN,
  eRtePortSR_U_ElecInt_EnableCallbacks,
  eRtePortSR_U_ElecInt_ActivateTxBufer,
  eRtePortSR_U_Diag_ResetStatistics,
  eRtePortSR_U_OS_CPULoadAvg,
  eRtePortSR_U_OS_CPULoadPeak,
  eRtePortSR_U_Diag_TiScrollingTakeOver,
  eRtePortSR_U_Cpm_TgtLedSig_sVal,
  eRtePortSR_U_CpmHssTarget0_sSetting,
  eRtePortSR_U_Cpm_SigPrepTx_PowerFactor,
  eRtePortSR_U_Cpm_PowFact_Temp,
  eRtePortSR_U_Cpm_CtrlSwi_HSS3Target,
  eRtePortSR_U_SysVolt_FanVoltRng0_sVoltRng,
  eRtePortSR_U_SysVolt_LedVoltRng0_sVoltRng,
  eRtePortSR_U_StatM_StackUsage,
  eRtePortSR_U_RSens_PcbTemperature,
  eRtePortSR_U_RSens_ThermzoneTemperatures,
  eRtePortSR_U_RSens_BinningClass_sVal_00,
  eRtePortSR_U_RSens_BinningClass_sVal_01,
  eRtePortSR_U_RSens_BinningClass_sVal_02,
  eRtePortSR_U_RSens_BinningClass_sVal_03,
  eRtePortSR_U_RSens_NTC_BIN_Input_Errors,
  eRtePortSR_U_RSens_BinningDataDiag,
  eRtePortSR_U_FctR_TgtLed_sVal,
  eRtePortSR_U_FctR_LgtFctState,
  eRtePortSR_U_FctR_LgtFctStatus,
  eRtePortSR_U_FctR_TiWarningMode,
  eRtePortSR_U_FctR_TiFailureStatus,
  eRtePortSR_U_FctR_LgtDistStatus,
  eRtePortSR_U_CtrlLed_TgtLedSig_sVal,
  eRtePortSR_U_CtrlLed_TgtHssSig_sVal,
  eRtePortSR_U_CtrlLed_LedSettings_sVal,
  eRtePortSR_U_CtrlLed_ActLed_sState,
  eRtePortSR_U_CtrlLed_BinningClass,
  eRtePortSR_U_CtrlLed_LedChFbit,
  eRtePortSR_U_CtrlLed_ChState,
  eRtePortSR_U_CtrlSwi_TgtValue_Fan1,
  eRtePortSR_U_CtrlSwi_TgtValue_Fan2,
  eRtePortSR_U_CtrlSwi_TgtValue_SMRGB,
  eRtePortSR_U_CtrlSwi_StatusErr,
  eRtePortSR_U_CtrlSwi_TgtValue_ScrollingSatelite,
  eRtePortSR_U_CtrlSwi_Hss3StatusErr,
  eRtePortSR_U_CddSwi_SwitchStatus,
  eRtePortSR_U_ppsAvacStat1Out_Port,
  eRtePortSR_U_AvacStat1_SpeedMode,
  eRtePortSR_U_DcmPos0_Port,
  eRtePortSR_U_DcmState0_Port,
  eRtePortSR_U_CddDcm_ErrorStatus,
  eRtePortSR_U_Pitch_SensRaw,
  eRtePortSR_U_Pitch_Angle,
  eRtePortSR_U_Pitch_PlausState,
  eRtePortSR_U_CtrlDcm_MasterCommand,
  eRtePortSR_U_ppCtrlDcmTarget0_DcmTargetValues,
  eRtePortSR_U_CtrlDcm_StatusParameters_Port,
  eRtePortSR_U_DrvLedDiag,
  eRtePortSR_U_DrvLedDiagR,
  eRtePortSR_U_Count
}eRtePortSR_U_t;

#define eRteThreadFlag_T_HH_reSysMonRx_HS6_DAT_VSM_2AE_Received 0u
#define eRteThreadFlag_T_HH_reSysMonRx_HS6_DAT_VSM_2AE_NotReceived 1u
#define eRteThreadFlag_T_HH_reSysMonRx_HS6_DAT_VSM_34E_Received 2u
#define eRteThreadFlag_T_HH_reSysMonRx_HS6_DAT_VSM_34E_NotReceived 3u
#define eRteThreadFlag_T_HH_reSysMonRx_HS6_COMMANDES_VSM_036_Received 4u
#define eRteThreadFlag_T_HH_reSysMonRx_HS6_COMMANDES_VSM_036_NotReceived 5u
#define eRteThreadFlag_T_HH_reSysMonRx_HS6_DAT_BSI_432_Received 6u
#define eRteThreadFlag_T_HH_reSysMonRx_HS6_DAT_BSI_432_NotReceived 7u
#define eRteThreadFlag_T_HH_reSysMonRx_HS6_DYN_ABR_38D_Received 8u
#define eRteThreadFlag_T_HH_reSysMonRx_HS6_DYN_ABR_38D_NotReceived 9u
#define eRteThreadFlag_T_HH_reSysMonRx_EnableCallbacks 10u
#define eRteThreadFlag_T_HH_reSysMonTx_HS6_DIAG_DRVLED_Sent 11u
#define eRteThreadFlag_T_HH_reSysMonTx_HS6_DIAG_DRVLED_NotSent 12u
#define eRteThreadFlag_T_HH_reSysMonTx_ActivateTxBufer 13u
#define eRteThreadFlag_T_HH_reEcuM_RequestRUN 14u
#define eRteThreadFlag_T_HH_reEcuM_ReleaseRUN 15u
#define eRteThreadFlag_T_HH_reEcuM_ReleasePOST_RUN 16u
#define eRteThreadFlag_T_HH_reEcuM_RequestPOST_RUN 17u
#define eRteThreadFlag_T_HH_reEcuM_DiagResetRequest 18u
#define eRteThreadFlag_T_HH_Count 19u

#define eRteThreadFlag_T_HL_rcSysMon_Cycle1ms 0u
#define eRteThreadFlag_T_HL_rpSchM_Func_Trusted_Cycle 1u
#define eRteThreadFlag_T_HL_rpCddLed_Cycle 2u
#define eRteThreadFlag_T_HL_rpCddBoost_Cycle 3u
#define eRteThreadFlag_T_HL_rpCddSpi_Cycle 4u
#define eRteThreadFlag_T_HL_rpCddSbc_Cycle0 5u
#define eRteThreadFlag_T_HL_Count 6u

#define eRteThreadFlag_T_LH_Count 0u

#define eRteThreadFlag_T_LL_Count 0u

#define eRteThreadFlag_U_HH_reSigPrepRx_LifePhases 0u
#define eRteThreadFlag_U_HH_reSigPrepRx_SetDiagMux 1u
#define eRteThreadFlag_U_HH_reSigPrepTx_SendFrame457 2u
#define eRteThreadFlag_U_HH_reSigPrepTx_SendFrame477 3u
#define eRteThreadFlag_U_HH_reStatM_Deinit 4u
#define eRteThreadFlag_U_HH_reStatM_ResetStatistics 5u
#define eRteThreadFlag_U_HH_Count 6u

#define eRteThreadFlag_U_HL_rpSchM_Func_NonTrusted_Cycle 0u
#define eRteThreadFlag_U_HL_Count 1u

#define eRteThreadFlag_U_LH_rpCodM_Cycle0 0u
#define eRteThreadFlag_U_LH_rpCpm20ms 1u
#define eRteThreadFlag_U_LH_rpSysVolt_Cycle 2u
#define eRteThreadFlag_U_LH_rcStatM_Cycle10ms 3u
#define eRteThreadFlag_U_LH_rpRSens_Cycle0 4u
#define eRteThreadFlag_U_LH_rpDiagControl_Cycle0 5u
#define eRteThreadFlag_U_LH_rpFctR_Cycle 6u
#define eRteThreadFlag_U_LH_rpCtrlLed_Cycle0 7u
#define eRteThreadFlag_U_LH_rpCtrlSwiCycle0 8u
#define eRteThreadFlag_U_LH_rpCddSwi_Cycle0 9u
#define eRteThreadFlag_U_LH_rpAvacStat1_Cycle0 10u
#define eRteThreadFlag_U_LH_rpCddDcm_Cycle0 11u
#define eRteThreadFlag_U_LH_rpPitch_Cycle0 12u
#define eRteThreadFlag_U_LH_rpCtrlDcm_Cycle 13u
#define eRteThreadFlag_U_LH_Count 14u

#define eRteThreadFlag_U_LL_rcMemoryProc 0u
#define eRteThreadFlag_U_LL_Count 1u


// *****************************************************************************
// external declarations
// *****************************************************************************
extern void riCodM_Init(void);
extern void riSysMon_Init(void);
extern void riSchM_Func_NonTrusted_Init(void);
extern void riSchM_Func_Trusted_Init(void);
extern void riCpmInit(void);
extern void riSysVoltInit(void);
extern void riStatM_Init(void);
extern void riRSens_Init(void);
extern void riDiagControl_Init(void);
extern void riFctRInit(void);
extern void riCtrlLed_Init(void);
extern void riCtrlSwiInit(void);
extern void riCddLedInit(void);
extern void riCddBoostInit(void);
extern void riCddSpiInit(void);
extern void riCddSbc_Init(void);
extern void riCddEftInit(void);
extern void riCddSwi_Init(void);
extern void riAvacStat1_Init(void);
extern void riCddDcm_Init(void);
extern void riPitch_Init(void);
extern void riCtrlDcm_Init(void);
extern void rpCodM_Cycle0(void);
extern void rcSysMon_Cycle1ms(void);
extern void rpSchM_Func_NonTrusted_Cycle(void);
extern void rcMemoryProc(void);
extern void rpSchM_Func_Trusted_Cycle(void);
extern void rpCpm20ms(void);
extern void rpSysVolt_Cycle(void);
extern void rcStatM_Cycle10ms(void);
extern void rpRSens_Cycle0(void);
extern void rpDiagControl_Cycle0(void);
extern void rpFctR_Cycle(void);
extern void rpCtrlLed_Cycle0(void);
extern void rpCtrlSwiCycle0(void);
extern void rpCddLed_Cycle(void);
extern void rpCddBoost_Cycle(void);
extern void rpCddSpi_Cycle(void);
extern void rpCddSbc_Cycle0(void);
extern void rpCddSwi_Cycle0(void);
extern void rpAvacStat1_Cycle0(void);
extern void rpCddDcm_Cycle0(void);
extern void rpPitch_Cycle0(void);
extern void rpCtrlDcm_Cycle(void);
extern void reSysMonRx_HS6_DAT_VSM_2AE_Received(void);
extern void reSysMonRx_HS6_DAT_VSM_2AE_NotReceived(void);
extern void reSysMonRx_HS6_DAT_VSM_34E_Received(void);
extern void reSysMonRx_HS6_DAT_VSM_34E_NotReceived(void);
extern void reSysMonRx_HS6_COMMANDES_VSM_036_Received(void);
extern void reSysMonRx_HS6_COMMANDES_VSM_036_NotReceived(void);
extern void reSysMonRx_HS6_DAT_BSI_432_Received(void);
extern void reSysMonRx_HS6_DAT_BSI_432_NotReceived(void);
extern void reSysMonRx_HS6_DYN_ABR_38D_Received(void);
extern void reSysMonRx_HS6_DYN_ABR_38D_NotReceived(void);
extern void reSysMonRx_EnableCallbacks(void);
extern void reSysMonTx_HS6_DIAG_DRVLED_Sent(void);
extern void reSysMonTx_HS6_DIAG_DRVLED_NotSent(void);
extern void reSysMonTx_ActivateTxBufer(void);
extern void reSigPrepRx_LifePhases(void);
extern void reSigPrepRx_SetDiagMux(void);
extern void reSigPrepTx_SendFrame457(void);
extern void reSigPrepTx_SendFrame477(void);
extern void reEcuM_RequestRUN(void);
extern void reEcuM_ReleaseRUN(void);
extern void reEcuM_ReleasePOST_RUN(void);
extern void reEcuM_RequestPOST_RUN(void);
extern void reEcuM_DiagResetRequest(void);
extern void reStatM_Deinit(void);
extern void reStatM_ResetStatistics(void);

// *****************************************************************************
// function prototypes
// *****************************************************************************
Std_ReturnType Rte_Write_CodM_FctR_Para(const tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Read_CodM_FctR_Para(tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Write_CodM_AppM_Para(const tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Read_CodM_AppM_Para(tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Write_CodM_CtrlLed_Para(const tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Read_CodM_CtrlLed_Para(tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Write_CodM_Rsens_Para(const tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Read_CodM_Rsens_Para(tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Write_CodM_CtrlFan_Para(const tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Read_CodM_CtrlFan_Para(tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Write_CodM_SysVolt_Para(const tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Read_CodM_SysVolt_Para(tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Write_CodM_CddLed_Para(const tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Read_CodM_CddLed_Para(tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Write_CodM_CddSwi_Para(const tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Read_CodM_CddSwi_Para(tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Write_CodM_CddBoost_Para(const tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Read_CodM_CddBoost_Para(tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Write_CodM_SigPrep_Para(const tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Read_CodM_SigPrep_Para(tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Write_CodM_SysMon_Para(const tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Read_CodM_SysMon_Para(tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Write_CodM_Anima_Para(const tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Read_CodM_Anima_Para(tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Write_CodM_Pitch_Para(const tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Read_CodM_Pitch_Para(tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Write_CodM_IoHwAbUser_Para(const tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Read_CodM_IoHwAbUser_Para(tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Write_CodM_Err_Para(const tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Read_CodM_Err_Para(tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Write_SysMon_E2Eexec(const uint8* ppara1);
Std_ReturnType Rte_Read_SysMon_E2Eexec(uint8* ppara1);
Std_ReturnType Rte_Write_SysMon_StdLgtFcts_Req(const tsRte_SysMonLgtFctsReq* ppara1);
Std_ReturnType Rte_Read_SysMon_StdLgtFcts_Req(tsRte_SysMonLgtFctsReq* ppara1);
Std_ReturnType Rte_Write_SysMon_LowBeamCmd_Req(const teRte_ReqLightState* ppara1);
Std_ReturnType Rte_Read_SysMon_LowBeamCmd_Req(teRte_ReqLightState* ppara1);
Std_ReturnType Rte_Write_SysMon_TurnIndicatorCmd_Req(const teRte_ReqLightState* ppara1);
Std_ReturnType Rte_Read_SysMon_TurnIndicatorCmd_Req(teRte_ReqLightState* ppara1);
Std_ReturnType Rte_Write_SysMon_StdLgtTi_Req(const tsRte_SysMonLgtTiReq* ppara1);
Std_ReturnType Rte_Read_SysMon_StdLgtTi_Req(tsRte_SysMonLgtTiReq* ppara1);
Std_ReturnType Rte_Write_SysMon_VehicleSpeed(const tsRte_SysMon_VehicleSpeed* ppara1);
Std_ReturnType Rte_Read_SysMon_VehicleSpeed(tsRte_SysMon_VehicleSpeed* ppara1);
Std_ReturnType Rte_Write_SysMon_VehNetState(const tsRte_SysMon_VehNetState* ppara1);
Std_ReturnType Rte_Read_SysMon_VehNetState(tsRte_SysMon_VehNetState* ppara1);
Std_ReturnType Rte_Write_SysMon_LifePhases(const tsRte_SysMon_LifePhases* ppara1);
Std_ReturnType Rte_Read_SysMon_LifePhases(tsRte_SysMon_LifePhases* ppara1);
Std_ReturnType Rte_Write_SysMon_SetDiagMux(TE_Bool ppara1);
TE_Bool Rte_DRead_SysMon_SetDiagMux(void);
Std_ReturnType Rte_Read_SysMon_SetDiagMux(TE_Bool* ppara1);
Std_ReturnType Rte_Write_SysMon_SendFrame457(const tSysMon_SendFrame457* ppara1);
Std_ReturnType Rte_Read_SysMon_SendFrame457(tSysMon_SendFrame457* ppara1);
Std_ReturnType Rte_Write_SysMon_SendFrame477(const tSysMon_SendFrame477* ppara1);
Std_ReturnType Rte_Read_SysMon_SendFrame477(tSysMon_SendFrame477* ppara1);
Std_ReturnType Rte_Write_SysMon_TgtLedSig_sVal(const tsRte_TgtLedSig0_ASIL* ppara1);
Std_ReturnType Rte_Read_SysMon_TgtLedSig_sVal(tsRte_TgtLedSig0_ASIL* ppara1);
Std_ReturnType Rte_Write_SysMon_LedState(const tsRte_SysMon_LedStates* ppara1);
Std_ReturnType Rte_Read_SysMon_LedState(tsRte_SysMon_LedStates* ppara1);
Std_ReturnType Rte_Write_Diag_LdActivationRoutineControl(const tsRte_Ld_ActivationRoutineControl* ppara1);
Std_ReturnType Rte_Read_Diag_LdActivationRoutineControl(tsRte_Ld_ActivationRoutineControl* ppara1);
Std_ReturnType Rte_Write_Diag_DiagResetRequest(const boolean* ppara1);
Std_ReturnType Rte_Read_Diag_DiagResetRequest(boolean* ppara1);
Std_ReturnType Rte_Write_Diag_RequestPOST_RUN(const uint8* ppara1);
Std_ReturnType Rte_Read_Diag_RequestPOST_RUN(uint8* ppara1);
Std_ReturnType Rte_Write_Dcm_RoutineControl(const tsRte_DcMotorRoutineControl* ppara1);
Std_ReturnType Rte_Read_Dcm_RoutineControl(tsRte_DcMotorRoutineControl* ppara1);
Std_ReturnType Rte_Write_SigPrep_YawSpeed(const tsRte_SigPrep_YawSpeed* ppara1);
Std_ReturnType Rte_Read_SigPrep_YawSpeed(tsRte_SigPrep_YawSpeed* ppara1);
Std_ReturnType Rte_Write_SigPrep_ElecSupState(const tsRte_SigPrep_ElecSupState* ppara1);
Std_ReturnType Rte_Read_SigPrep_ElecSupState(tsRte_SigPrep_ElecSupState* ppara1);
Std_ReturnType Rte_Write_SigPrep_VehicleConfigSig(const tsRte_SigPrep_VehicleConfigSig* ppara1);
Std_ReturnType Rte_Read_SigPrep_VehicleConfigSig(tsRte_SigPrep_VehicleConfigSig* ppara1);
Std_ReturnType Rte_Write_SigPrep_DynamicSigs(const tsRte_SigPrep_DynamicSigs* ppara1);
Std_ReturnType Rte_Read_SigPrep_DynamicSigs(tsRte_SigPrep_DynamicSigs* ppara1);
Std_ReturnType Rte_Write_SigPrep_VehiclePitchAngle(const tsRte_SigPrep_VehiclePitchAngle* ppara1);
Std_ReturnType Rte_Read_SigPrep_VehiclePitchAngle(tsRte_SigPrep_VehiclePitchAngle* ppara1);
Std_ReturnType Rte_Write_SigPrep_NsoTrigger_Port(const tsRte_SigPrepNsoTrig* ppara1);
Std_ReturnType Rte_Read_SigPrep_NsoTrigger_Port(tsRte_SigPrepNsoTrig* ppara1);
Std_ReturnType Rte_Write_SigPrep_AnimationReq(const tsRte_AnimationReq* ppara1);
Std_ReturnType Rte_Read_SigPrep_AnimationReq(tsRte_AnimationReq* ppara1);
Std_ReturnType Rte_Write_SigPrep_VehTimeCntr(const tsRte_VehTimeCntr* ppara1);
Std_ReturnType Rte_Read_SigPrep_VehTimeCntr(tsRte_VehTimeCntr* ppara1);
Std_ReturnType Rte_Write_SigPrep_OdometerTotal(const tsRte_OdometerTotal* ppara1);
Std_ReturnType Rte_Read_SigPrep_OdometerTotal(tsRte_OdometerTotal* ppara1);
Std_ReturnType Rte_Write_SigPrep_ElecIntegra(const tsRte_ElecIntegra* ppara1);
Std_ReturnType Rte_Read_SigPrep_ElecIntegra(tsRte_ElecIntegra* ppara1);
Std_ReturnType Rte_Write_SigPrep_DcmDiagStatusR(const tsRte_DcmDiagStatusR* ppara1);
Std_ReturnType Rte_Read_SigPrep_DcmDiagStatusR(tsRte_DcmDiagStatusR* ppara1);
Std_ReturnType Rte_Write_SigPrep_LevellingTgtPos(const tsRte_LevellingTgtPos* ppara1);
Std_ReturnType Rte_Read_SigPrep_LevellingTgtPos(tsRte_LevellingTgtPos* ppara1);
Std_ReturnType Rte_Write_SigPrep_HS6_DAT_VSM_2AE_Received(const tHS6_DAT_VSM_2AE* ppara1);
Std_ReturnType Rte_Read_SigPrep_HS6_DAT_VSM_2AE_Received(tHS6_DAT_VSM_2AE* ppara1);
Std_ReturnType Rte_Write_SigPrep_HS6_DAT_VSM_2AE_NotReceived(boolean ppara1);
boolean Rte_DRead_SigPrep_HS6_DAT_VSM_2AE_NotReceived(void);
Std_ReturnType Rte_Read_SigPrep_HS6_DAT_VSM_2AE_NotReceived(boolean* ppara1);
Std_ReturnType Rte_Write_SigPrep_HS6_DAT_VSM_34E_Received(const tHS6_DAT_VSM_34E* ppara1);
Std_ReturnType Rte_Read_SigPrep_HS6_DAT_VSM_34E_Received(tHS6_DAT_VSM_34E* ppara1);
Std_ReturnType Rte_Write_SigPrep_HS6_DAT_VSM_34E_NotReceived(boolean ppara1);
boolean Rte_DRead_SigPrep_HS6_DAT_VSM_34E_NotReceived(void);
Std_ReturnType Rte_Read_SigPrep_HS6_DAT_VSM_34E_NotReceived(boolean* ppara1);
Std_ReturnType Rte_Write_SigPrep_HS6_COMMANDES_VSM_036_Received(const tHS6_COMMANDES_VSM_036* ppara1);
Std_ReturnType Rte_Read_SigPrep_HS6_COMMANDES_VSM_036_Received(tHS6_COMMANDES_VSM_036* ppara1);
Std_ReturnType Rte_Write_SigPrep_HS6_COMMANDES_VSM_036_NotReceived(boolean ppara1);
boolean Rte_DRead_SigPrep_HS6_COMMANDES_VSM_036_NotReceived(void);
Std_ReturnType Rte_Read_SigPrep_HS6_COMMANDES_VSM_036_NotReceived(boolean* ppara1);
Std_ReturnType Rte_Write_SigPrep_HS6_DAT_BSI_432_Received(const tHS6_DAT_BSI_432* ppara1);
Std_ReturnType Rte_Read_SigPrep_HS6_DAT_BSI_432_Received(tHS6_DAT_BSI_432* ppara1);
Std_ReturnType Rte_Write_SigPrep_HS6_DAT_BSI_432_NotReceived(boolean ppara1);
boolean Rte_DRead_SigPrep_HS6_DAT_BSI_432_NotReceived(void);
Std_ReturnType Rte_Read_SigPrep_HS6_DAT_BSI_432_NotReceived(boolean* ppara1);
Std_ReturnType Rte_Write_SigPrep_HS6_DYN_ABR_38D_Received(const tHS6_DYN_ABR_38D* ppara1);
Std_ReturnType Rte_Read_SigPrep_HS6_DYN_ABR_38D_Received(tHS6_DYN_ABR_38D* ppara1);
Std_ReturnType Rte_Write_SigPrep_HS6_DYN_ABR_38D_NotReceived(boolean ppara1);
boolean Rte_DRead_SigPrep_HS6_DYN_ABR_38D_NotReceived(void);
Std_ReturnType Rte_Read_SigPrep_HS6_DYN_ABR_38D_NotReceived(boolean* ppara1);
Std_ReturnType Rte_Write_SigPrep_SleepBSI(const uint8* ppara1);
Std_ReturnType Rte_Read_SigPrep_SleepBSI(uint8* ppara1);
Std_ReturnType Rte_Write_SigPrep_NMMode(const NM_ModeType* ppara1);
Std_ReturnType Rte_Read_SigPrep_NMMode(NM_ModeType* ppara1);
Std_ReturnType Rte_Write_SigPrep_HS6_DIAG_DRVLED_Sent(boolean ppara1);
boolean Rte_DRead_SigPrep_HS6_DIAG_DRVLED_Sent(void);
Std_ReturnType Rte_Read_SigPrep_HS6_DIAG_DRVLED_Sent(boolean* ppara1);
Std_ReturnType Rte_Write_SigPrep_HS6_DIAG_DRVLED_NotSent(boolean ppara1);
boolean Rte_DRead_SigPrep_HS6_DIAG_DRVLED_NotSent(void);
Std_ReturnType Rte_Read_SigPrep_HS6_DIAG_DRVLED_NotSent(boolean* ppara1);
Std_ReturnType Rte_Write_DEM_UV_NotifyStatus(const boolean* ppara1);
Std_ReturnType Rte_Read_DEM_UV_NotifyStatus(boolean* ppara1);
Std_ReturnType Rte_Write_DEM_OV_NotifyStatus(const boolean* ppara1);
Std_ReturnType Rte_Read_DEM_OV_NotifyStatus(boolean* ppara1);
Std_ReturnType Rte_Write_DEM_350Lost_NotifyStatus(const boolean* ppara1);
Std_ReturnType Rte_Read_DEM_350Lost_NotifyStatus(boolean* ppara1);
Std_ReturnType Rte_Write_ElecInt_RequestRUN(const uint8* ppara1);
Std_ReturnType Rte_Read_ElecInt_RequestRUN(uint8* ppara1);
Std_ReturnType Rte_Write_ElecInt_ReleaseRUN(const uint8* ppara1);
Std_ReturnType Rte_Read_ElecInt_ReleaseRUN(uint8* ppara1);
Std_ReturnType Rte_Write_ElecInt_ReleasePOST_RUN(const uint8* ppara1);
Std_ReturnType Rte_Read_ElecInt_ReleasePOST_RUN(uint8* ppara1);
Std_ReturnType Rte_Write_ElecInt_EnableCallbacks(boolean ppara1);
boolean Rte_DRead_ElecInt_EnableCallbacks(void);
Std_ReturnType Rte_Read_ElecInt_EnableCallbacks(boolean* ppara1);
Std_ReturnType Rte_Write_ElecInt_ActivateTxBufer(boolean ppara1);
boolean Rte_DRead_ElecInt_ActivateTxBufer(void);
Std_ReturnType Rte_Read_ElecInt_ActivateTxBufer(boolean* ppara1);
Std_ReturnType Rte_Write_Diag_ResetStatistics(boolean ppara1);
boolean Rte_DRead_Diag_ResetStatistics(void);
Std_ReturnType Rte_Read_Diag_ResetStatistics(boolean* ppara1);
Std_ReturnType Rte_Write_OS_CPULoadAvg(uint8 ppara1);
uint8 Rte_DRead_OS_CPULoadAvg(void);
Std_ReturnType Rte_Read_OS_CPULoadAvg(uint8* ppara1);
Std_ReturnType Rte_Write_OS_CPULoadPeak(uint8 ppara1);
uint8 Rte_DRead_OS_CPULoadPeak(void);
Std_ReturnType Rte_Read_OS_CPULoadPeak(uint8* ppara1);
Std_ReturnType Rte_Write_Diag_TiScrollingTakeOver(const boolean* ppara1);
Std_ReturnType Rte_Read_Diag_TiScrollingTakeOver(boolean* ppara1);
Std_ReturnType Rte_Write_IoHwAbUser_GetMountingSide(const teRte_MountingSide* ppara1);
Std_ReturnType Rte_Read_IoHwAbUser_GetMountingSide(teRte_MountingSide* ppara1);
Std_ReturnType Rte_Write_IoHwAb_User_GetAdc_DIAG_VBAT(const tiu32Voltage_mV* ppara1);
Std_ReturnType Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT(tiu32Voltage_mV* ppara1);
Std_ReturnType Rte_Write_IoHwAb_GetSens_Balanced(const tsRte_SensorBalance* ppara1);
Std_ReturnType Rte_Read_IoHwAb_GetSens_Balanced(tsRte_SensorBalance* ppara1);
Std_ReturnType Rte_Write_IoHwAb_GetSens_Raw(const tsRte_SensorRaw* ppara1);
Std_ReturnType Rte_Read_IoHwAb_GetSens_Raw(tsRte_SensorRaw* ppara1);
Std_ReturnType Rte_Write_IoHwAb_GetPCB(const tiu16Voltage_mV* ppara1);
Std_ReturnType Rte_Read_IoHwAb_GetPCB(tiu16Voltage_mV* ppara1);
Std_ReturnType Rte_Write_IoHwAb_GetVoltage_NTCs(const tsRte_Voltage_mV* ppara1);
Std_ReturnType Rte_Read_IoHwAb_GetVoltage_NTCs(tsRte_Voltage_mV* ppara1);
Std_ReturnType Rte_Write_IoHwAb_VCCX1Voltage(const tiu16Voltage_mV* ppara1);
Std_ReturnType Rte_Read_IoHwAb_VCCX1Voltage(tiu16Voltage_mV* ppara1);
Std_ReturnType Rte_Write_MPU_ErrorCounter(const uint32* ppara1);
Std_ReturnType Rte_Read_MPU_ErrorCounter(uint32* ppara1);
Std_ReturnType Rte_Write_EcuM_Deinit(boolean ppara1);
boolean Rte_DRead_EcuM_Deinit(void);
Std_ReturnType Rte_Read_EcuM_Deinit(boolean* ppara1);
Std_ReturnType Rte_Write_Cpm_TgtLedSig_sVal(const tsRte_TgtLedSig0Arr* ppara1);
Std_ReturnType Rte_Read_Cpm_TgtLedSig_sVal(tsRte_TgtLedSig0Arr* ppara1);
Std_ReturnType Rte_Write_CpmHssTarget0_sSetting(const tsRteHssTarget* ppara1);
Std_ReturnType Rte_Read_CpmHssTarget0_sSetting(tsRteHssTarget* ppara1);
Std_ReturnType Rte_Write_Cpm_SigPrepTx_PowerFactor(const tsRte_PowerFactor* ppara1);
Std_ReturnType Rte_Read_Cpm_SigPrepTx_PowerFactor(tsRte_PowerFactor* ppara1);
Std_ReturnType Rte_Write_Cpm_PowFact_Temp(const tsRtePowFactTemp* ppara1);
Std_ReturnType Rte_Read_Cpm_PowFact_Temp(tsRtePowFactTemp* ppara1);
Std_ReturnType Rte_Write_Cpm_CtrlSwi_HSS3Target(const tsRte_CpmHSS3Duty* ppara1);
Std_ReturnType Rte_Read_Cpm_CtrlSwi_HSS3Target(tsRte_CpmHSS3Duty* ppara1);
Std_ReturnType Rte_Write_SysVolt_FanVoltRng0_sVoltRng(const teRte_SysVolt_Results* ppara1);
Std_ReturnType Rte_Read_SysVolt_FanVoltRng0_sVoltRng(teRte_SysVolt_Results* ppara1);
Std_ReturnType Rte_Write_SysVolt_LedVoltRng0_sVoltRng(const teRte_SysVolt_Results* ppara1);
Std_ReturnType Rte_Read_SysVolt_LedVoltRng0_sVoltRng(teRte_SysVolt_Results* ppara1);
Std_ReturnType Rte_Write_StatM_StackUsage(uint8 ppara1);
uint8 Rte_DRead_StatM_StackUsage(void);
Std_ReturnType Rte_Read_StatM_StackUsage(uint8* ppara1);
Std_ReturnType Rte_Write_RSens_PcbTemperature(const tsRte_PcbTemperatureMsg* ppara1);
Std_ReturnType Rte_Read_RSens_PcbTemperature(tsRte_PcbTemperatureMsg* ppara1);
Std_ReturnType Rte_Write_RSens_ThermzoneTemperatures(const tsRte_NTCTemperature* ppara1);
Std_ReturnType Rte_Read_RSens_ThermzoneTemperatures(tsRte_NTCTemperature* ppara1);
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_00(const tsRte_Binning0* ppara1);
Std_ReturnType Rte_Read_RSens_BinningClass_sVal_00(tsRte_Binning0* ppara1);
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_01(const tsRte_Binning0* ppara1);
Std_ReturnType Rte_Read_RSens_BinningClass_sVal_01(tsRte_Binning0* ppara1);
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_02(const tsRte_Binning0* ppara1);
Std_ReturnType Rte_Read_RSens_BinningClass_sVal_02(tsRte_Binning0* ppara1);
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_03(const tsRte_Binning0* ppara1);
Std_ReturnType Rte_Read_RSens_BinningClass_sVal_03(tsRte_Binning0* ppara1);
Std_ReturnType Rte_Write_RSens_NTC_BIN_Input_Errors(const tsRteNTCBinInData* ppara1);
Std_ReturnType Rte_Read_RSens_NTC_BIN_Input_Errors(tsRteNTCBinInData* ppara1);
Std_ReturnType Rte_Write_RSens_BinningDataDiag(const tsRte_D409Binning* ppara1);
Std_ReturnType Rte_Read_RSens_BinningDataDiag(tsRte_D409Binning* ppara1);
Std_ReturnType Rte_Write_FctR_TgtLed_sVal(const tsRte_TgtLedVal0Arr* ppara1);
Std_ReturnType Rte_Read_FctR_TgtLed_sVal(tsRte_TgtLedVal0Arr* ppara1);
Std_ReturnType Rte_Write_FctR_LgtFctState(const tsRte_LgtFctState* ppara1);
Std_ReturnType Rte_Read_FctR_LgtFctState(tsRte_LgtFctState* ppara1);
Std_ReturnType Rte_Write_FctR_LgtFctStatus(const tsRte_LgtFctStatus* ppara1);
Std_ReturnType Rte_Read_FctR_LgtFctStatus(tsRte_LgtFctStatus* ppara1);
Std_ReturnType Rte_Write_FctR_TiWarningMode(const teRte_WarningMode* ppara1);
Std_ReturnType Rte_Read_FctR_TiWarningMode(teRte_WarningMode* ppara1);
Std_ReturnType Rte_Write_FctR_TiFailureStatus(const boolean* ppara1);
Std_ReturnType Rte_Read_FctR_TiFailureStatus(boolean* ppara1);
Std_ReturnType Rte_Write_FctR_LgtDistStatus(const uint32* ppara1);
Std_ReturnType Rte_Read_FctR_LgtDistStatus(uint32* ppara1);
Std_ReturnType Rte_Write_CtrlLed_TgtLedSig_sVal(const tsRte_TgtLedSig0Arr* ppara1);
Std_ReturnType Rte_Read_CtrlLed_TgtLedSig_sVal(tsRte_TgtLedSig0Arr* ppara1);
Std_ReturnType Rte_Write_CtrlLed_TgtHssSig_sVal(const tsRte_TgtLedSig0* ppara1);
Std_ReturnType Rte_Read_CtrlLed_TgtHssSig_sVal(tsRte_TgtLedSig0* ppara1);
Std_ReturnType Rte_Write_CtrlLed_LedSettings_sVal(const tsRte_ChLedSettings* ppara1);
Std_ReturnType Rte_Read_CtrlLed_LedSettings_sVal(tsRte_ChLedSettings* ppara1);
Std_ReturnType Rte_Write_CtrlLed_ActLed_sState(const tsRte_LedErrStateArr* ppara1);
Std_ReturnType Rte_Read_CtrlLed_ActLed_sState(tsRte_LedErrStateArr* ppara1);
Std_ReturnType Rte_Write_CtrlLed_BinningClass(const tsRte_ucBinningSelect* ppara1);
Std_ReturnType Rte_Read_CtrlLed_BinningClass(tsRte_ucBinningSelect* ppara1);
Std_ReturnType Rte_Write_CtrlLed_LedChFbit(const tsRte_LedChFbit* ppara1);
Std_ReturnType Rte_Read_CtrlLed_LedChFbit(tsRte_LedChFbit* ppara1);
Std_ReturnType Rte_Write_CtrlLed_ChState(const tsRte_CtrlLed_ChStatesDiag* ppara1);
Std_ReturnType Rte_Read_CtrlLed_ChState(tsRte_CtrlLed_ChStatesDiag* ppara1);
Std_ReturnType Rte_Write_CtrlSwi_TgtValue_Fan1(const tRteSwitchTgtVal* ppara1);
Std_ReturnType Rte_Read_CtrlSwi_TgtValue_Fan1(tRteSwitchTgtVal* ppara1);
Std_ReturnType Rte_Write_CtrlSwi_TgtValue_Fan2(const tRteSwitchTgtVal* ppara1);
Std_ReturnType Rte_Read_CtrlSwi_TgtValue_Fan2(tRteSwitchTgtVal* ppara1);
Std_ReturnType Rte_Write_CtrlSwi_TgtValue_SMRGB(const tRteSwitchTgtVal* ppara1);
Std_ReturnType Rte_Read_CtrlSwi_TgtValue_SMRGB(tRteSwitchTgtVal* ppara1);
Std_ReturnType Rte_Write_CtrlSwi_StatusErr(const tisHssStatusError* ppara1);
Std_ReturnType Rte_Read_CtrlSwi_StatusErr(tisHssStatusError* ppara1);
Std_ReturnType Rte_Write_CtrlSwi_TgtValue_ScrollingSatelite(const teRte_SateliteStatus* ppara1);
Std_ReturnType Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite(teRte_SateliteStatus* ppara1);
Std_ReturnType Rte_Write_CtrlSwi_Hss3StatusErr(const tsRte_Hss3Status* ppara1);
Std_ReturnType Rte_Read_CtrlSwi_Hss3StatusErr(tsRte_Hss3Status* ppara1);
Std_ReturnType Rte_Write_CddLed_LedState(const tsRte_LedStates* ppara1);
Std_ReturnType Rte_Read_CddLed_LedState(tsRte_LedStates* ppara1);
Std_ReturnType Rte_Write_CddLed_Status(const tCddLedStatus* ppara1);
Std_ReturnType Rte_Read_CddLed_Status(tCddLedStatus* ppara1);
Std_ReturnType Rte_Write_CddLed_TgtLed_FaultStatus_ASIL(const tsRte_TgtLedSig0_FaultStatus_ASIL* ppara1);
Std_ReturnType Rte_Read_CddLed_TgtLed_FaultStatus_ASIL(tsRte_TgtLedSig0_FaultStatus_ASIL* ppara1);
Std_ReturnType Rte_Write_CddBoost_BoostState(const tsRte_BoostState* ppara1);
Std_ReturnType Rte_Read_CddBoost_BoostState(tsRte_BoostState* ppara1);
Std_ReturnType Rte_Write_CddBoost_BoostStatus(const tCddBoostStatus* ppara1);
Std_ReturnType Rte_Read_CddBoost_BoostStatus(tCddBoostStatus* ppara1);
Std_ReturnType Rte_Write_CddSwi_SwitchStatus(const tsRte_HssStatus* ppara1);
Std_ReturnType Rte_Read_CddSwi_SwitchStatus(tsRte_HssStatus* ppara1);
Std_ReturnType Rte_Write_ppsAvacStat1Out_Port(const tPositionOut* ppara1);
Std_ReturnType Rte_Read_ppsAvacStat1Out_Port(tPositionOut* ppara1);
Std_ReturnType Rte_Write_AvacStat1_SpeedMode(const teRte_DcmSpeedMode* ppara1);
Std_ReturnType Rte_Read_AvacStat1_SpeedMode(teRte_DcmSpeedMode* ppara1);
Std_ReturnType Rte_Write_DcmPos0_Port(const tDcmPosMsg* ppara1);
Std_ReturnType Rte_Read_DcmPos0_Port(tDcmPosMsg* ppara1);
Std_ReturnType Rte_Write_DcmState0_Port(const tDcmStateMsg* ppara1);
Std_ReturnType Rte_Read_DcmState0_Port(tDcmStateMsg* ppara1);
Std_ReturnType Rte_Write_CddDcm_ErrorStatus(const tsRte_DcmStatusError* ppara1);
Std_ReturnType Rte_Read_CddDcm_ErrorStatus(tsRte_DcmStatusError* ppara1);
Std_ReturnType Rte_Write_Pitch_SensRaw(const tSensRaw0* ppara1);
Std_ReturnType Rte_Read_Pitch_SensRaw(tSensRaw0* ppara1);
Std_ReturnType Rte_Write_Pitch_Angle(const tPitch0* ppara1);
Std_ReturnType Rte_Read_Pitch_Angle(tPitch0* ppara1);
Std_ReturnType Rte_Write_Pitch_PlausState(const teRte_HlsSensorState* ppara1);
Std_ReturnType Rte_Read_Pitch_PlausState(teRte_HlsSensorState* ppara1);
Std_ReturnType Rte_Write_CtrlDcm_MasterCommand(const tsRte_LevellingTgtPos* ppara1);
Std_ReturnType Rte_Read_CtrlDcm_MasterCommand(tsRte_LevellingTgtPos* ppara1);
Std_ReturnType Rte_Write_ppCtrlDcmTarget0_DcmTargetValues(const tsRte_CtrlDcmTarget* ppara1);
Std_ReturnType Rte_Read_ppCtrlDcmTarget0_DcmTargetValues(tsRte_CtrlDcmTarget* ppara1);
Std_ReturnType Rte_Write_CtrlDcm_StatusParameters_Port(const tsRte_CtrlDcmStatusParams* ppara1);
Std_ReturnType Rte_Read_CtrlDcm_StatusParameters_Port(tsRte_CtrlDcmStatusParams* ppara1);
Std_ReturnType Rte_Write_DrvLedDiag(const tsRte_Hs6_Diag_Drvled_L_457* ppara1);
Std_ReturnType Rte_Read_DrvLedDiag(tsRte_Hs6_Diag_Drvled_L_457* ppara1);
Std_ReturnType Rte_Write_DrvLedDiagR(const tsRte_Hs6_Diag_Drvled_R_477* ppara1);
Std_ReturnType Rte_Read_DrvLedDiagR(tsRte_Hs6_Diag_Drvled_R_477* ppara1);


#endif // SCATTER_LOAD

#endif // __RTE_CFG_H


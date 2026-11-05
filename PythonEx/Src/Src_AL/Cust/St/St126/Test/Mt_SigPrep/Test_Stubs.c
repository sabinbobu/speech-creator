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
tieFeeState                           Fee_State;
MemIf_JobResultType                   Fee_JobResult;
tsRte_SysMon_LifePhases               Rte_Read_SysMon_LifePhases_Param1;
tsRte_SysMon_LifePhases               Rte_Write_SysMon_LifePhases_Param1;
tsRte_SysMon_VehNetState              Rte_Read_SysMon_VehNetState_Param1;
tsRte_SysMon_VehNetState              Rte_Write_SysMon_VehNetState_Param1;
tsRte_AnimationReq                    Rte_Read_SigPrep_AnimationReq_Param1;
tsRte_AnimationReq                    Rte_Write_SigPrep_AnimationReq_Param1;
tsRte_SigPrep_VehicleConfigSig        Rte_Read_SigPrep_VehicleConfigSig_Param1;
tsRte_SigPrep_VehicleConfigSig        Rte_Write_SigPrep_VehicleConfigSig_Param1;
tsRte_OdometerTotal                   Rte_Read_SigPrep_OdometerTotal_Param1;
tsRte_OdometerTotal                   Rte_Write_SigPrep_OdometerTotal_Param1;
tsRte_VehTimeCntr                     Rte_Read_SigPrep_VehTimeCntr_Param1;
tsRte_VehTimeCntr                     Rte_Write_SigPrep_VehTimeCntr_Param1;
tsRte_SysMon_VehicleSpeed             Rte_Read_SysMon_VehicleSpeed_Param1;
tsRte_SysMon_VehicleSpeed             Rte_Write_SysMon_VehicleSpeed_Param1;
tsRte_SigPrep_ElecSupState            Rte_Read_SigPrep_ElecSupState_Param1;
tsRte_SigPrep_ElecSupState            Rte_Write_SigPrep_ElecSupState_Param1;
tsRte_ElecIntegra                     Rte_Read_SigPrep_ElecIntegra_Param1;
tsRte_ElecIntegra                     Rte_Write_SigPrep_ElecIntegra_Param1;
tsRte_SigPrep_YawSpeed                Rte_Read_SigPrep_YawSpeed_Param1;
tsRte_SigPrep_YawSpeed                Rte_Write_SigPrep_YawSpeed_Param1;
tsRte_LevellingDiagStatus             Rte_Read_SigPrep_LevellingDiagStatus_Param1;
tsRte_LevellingDiagStatus             Rte_Write_SigPrep_LevellingDiagStatus_Param1;
tsRte_DcmDiagStatusR                  Rte_Read_SigPrep_DcmDiagStatusR_Param1;
tsRte_DcmDiagStatusR                  Rte_Write_SigPrep_DcmDiagStatusR_Param1;
tsRte_LevellingTgtPos                 Rte_Read_SigPrep_LevellingTgtPos_Param1;
tsRte_LevellingTgtPos                 Rte_Write_SigPrep_LevellingTgtPos_Param1;
tsRte_SigPrep_DynamicSigs             Rte_Read_SigPrep_DynamicSigs_Param1;
tsRte_SigPrep_DynamicSigs             Rte_Write_SigPrep_DynamicSigs_Param1;
tsRte_SigPrep_SteeringWheelAngle      Rte_Read_SigPrep_SteeringWheelAngle_Param1;
tsRte_SigPrep_SteeringWheelAngle      Rte_Write_SigPrep_SteeringWheelAngle_Param1;
tsRte_SigPrep_VehiclePitchAngle       Rte_Read_SigPrep_VehiclePitchAngle_Param1;
tsRte_SigPrep_VehiclePitchAngle       Rte_Write_SigPrep_VehiclePitchAngle_Param1;
tsRte_LevellingFeedback               Rte_Read_SigPrep_LevellingFeedback_Param1;
tsRte_LevellingFeedback               Rte_Write_SigPrep_LevellingFeedback_Param1;
tsRte_SigPrep_VehPathCurvature        Rte_Read_SigPrep_VehPathCurvature_Param1;
tsRte_SigPrep_VehPathCurvature        Rte_Write_SigPrep_VehPathCurvature_Param1;
tsRte_SigPrepLgtClSblReq              Rte_Read_SigPrep_StdLgtClSbl_Req_Param1;
tsRte_SigPrepLgtClSblReq              Rte_Write_SigPrep_StdLgtClSbl_Req_Param1;
teRte_MountingSide                    Rte_Read_IoHwAbUser_GetMountingSide_Param1;
teRte_MountingSide                    Rte_Write_IoHwAbUser_GetMountingSide_Param1;
tsRte_SigPrep_EnvCondition            Rte_Read_SigPrep_EnvCondition_Param1;
tsRte_SigPrep_EnvCondition            Rte_Write_SigPrep_EnvCondition_Param1;
tsRte_SigPrep_PerceiveSigGroup1_sVal  Rte_Read_SigPrep_PerceiveSigGroup1_sVal_00_Param1;
tsRte_SigPrep_PerceiveSigGroup1_sVal  Rte_Write_SigPrep_PerceiveSigGroup1_sVal_00_Param1;
tsRte_SigPrep_PerceiveSigGroup1_sVal  Rte_Read_SigPrep_PerceiveSigGroup1_sVal_01_Param1;
tsRte_SigPrep_PerceiveSigGroup1_sVal  Rte_Write_SigPrep_PerceiveSigGroup1_sVal_01_Param1;
tsRte_SigPrep_PerceiveSigGroup1_sVal  Rte_Read_SigPrep_PerceiveSigGroup1_sVal_02_Param1;
tsRte_SigPrep_PerceiveSigGroup1_sVal  Rte_Write_SigPrep_PerceiveSigGroup1_sVal_02_Param1;
tsRte_SigPrep_ClusterSigGroup1_sVal   Rte_Read_SigPrep_ClusterSigGroup1_sVal_00_Param1;
tsRte_SigPrep_ClusterSigGroup1_sVal   Rte_Write_SigPrep_ClusterSigGroup1_sVal_00_Param1;
tsRte_SigPrep_ClusterSigGroup1_sVal   Rte_Read_SigPrep_ClusterSigGroup1_sVal_01_Param1;
tsRte_SigPrep_ClusterSigGroup1_sVal   Rte_Write_SigPrep_ClusterSigGroup1_sVal_01_Param1;
tsRte_SigPrep_ClusterSigGroup1_sVal   Rte_Read_SigPrep_ClusterSigGroup1_sVal_02_Param1;
tsRte_SigPrep_ClusterSigGroup1_sVal   Rte_Write_SigPrep_ClusterSigGroup1_sVal_02_Param1;
tsRte_SigPrep_ClusterSigGroup1_sVal   Rte_Read_SigPrep_ClusterSigGroup1_sVal_03_Param1;
tsRte_SigPrep_ClusterSigGroup1_sVal   Rte_Write_SigPrep_ClusterSigGroup1_sVal_03_Param1;
tsRte_SigPrep_ClusterSigGroup1_sVal   Rte_Read_SigPrep_ClusterSigGroup1_sVal_04_Param1;
tsRte_SigPrep_ClusterSigGroup1_sVal   Rte_Write_SigPrep_ClusterSigGroup1_sVal_04_Param1;
tsRte_SigPrep_PerceiveSigGroup2_sVal  Rte_Read_SigPrep_PerceiveSigGroup2_sVal_00_Param1;
tsRte_SigPrep_PerceiveSigGroup2_sVal  Rte_Write_SigPrep_PerceiveSigGroup2_sVal_00_Param1;
tsRte_SigPrep_PerceiveSigGroup2_sVal  Rte_Read_SigPrep_PerceiveSigGroup2_sVal_01_Param1;
tsRte_SigPrep_PerceiveSigGroup2_sVal  Rte_Write_SigPrep_PerceiveSigGroup2_sVal_01_Param1;
tsRte_SigPrep_PerceiveSigGroup2_sVal  Rte_Read_SigPrep_PerceiveSigGroup2_sVal_02_Param1;
tsRte_SigPrep_PerceiveSigGroup2_sVal  Rte_Write_SigPrep_PerceiveSigGroup2_sVal_02_Param1;
tsRte_SigPrep_ClusterSigGroup2_sVal   Rte_Read_SigPrep_ClusterSigGroup2_sVal_00_Param1;
tsRte_SigPrep_ClusterSigGroup2_sVal   Rte_Write_SigPrep_ClusterSigGroup2_sVal_00_Param1;
tsRte_SigPrep_ClusterSigGroup2_sVal   Rte_Read_SigPrep_ClusterSigGroup2_sVal_01_Param1;
tsRte_SigPrep_ClusterSigGroup2_sVal   Rte_Write_SigPrep_ClusterSigGroup2_sVal_01_Param1;
tsRte_SigPrep_ClusterSigGroup2_sVal   Rte_Read_SigPrep_ClusterSigGroup2_sVal_02_Param1;
tsRte_SigPrep_ClusterSigGroup2_sVal   Rte_Write_SigPrep_ClusterSigGroup2_sVal_02_Param1;
tsRte_SigPrep_ClusterSigGroup2_sVal   Rte_Read_SigPrep_ClusterSigGroup2_sVal_03_Param1;
tsRte_SigPrep_ClusterSigGroup2_sVal   Rte_Write_SigPrep_ClusterSigGroup2_sVal_03_Param1;
tsRte_SigPrep_ClusterSigGroup2_sVal   Rte_Read_SigPrep_ClusterSigGroup2_sVal_04_Param1;
tsRte_SigPrep_ClusterSigGroup2_sVal   Rte_Write_SigPrep_ClusterSigGroup2_sVal_04_Param1;
tsRte_Hs6_Diag_Drvled_L_457           Rte_Read_DrvLedDiag_Param1;
tsRte_LevellingTgtPos                 Rte_Read_CtrlStp_MasterCommand_Param1;
tsRte_LevellingFeedback               Rte_Read_CtrlStp_SlaveFeedback_Param1;
tsRte_LevellingDiagStatus             Rte_Read_CtrlStp_SlaveDiagStatus_Param1;
tsRte_SysMon_LifePhases               Rte_Read_SysMon_LifePhases_Param1;
uint16                                Dem_SetEventStatus_Param1;
uint8                                 Dem_SetEventStatus_Param2;
Tu8_Int                               DAPI_BSIAckState_Param1;
TE_Bool                               DAPI_SetDiagMux_Param1;
TE_Bool                               DAPI_RemoveAllDE_Param1;
DAPI_TE_ConfigMode                    DAPI_SetConfigMode_Param1;
DAPI_TE_MainStatus                    DAPI_SetMainStatus_Param1;
Tu32_Int                              DAPI_SyncModule_Param1;
LDEH_TE_PermToSend                    DAPI_SetPermToSend_Param1;
Tu8_Int                               EAPI_SetEIMInfo_CAN_Param1;
LEIM_TE_LifePhase                     EAPI_SetEIMInfo_CAN_Param2;
Tu32_Int                              CMGT_SetMileage_Param1;
boolean                               SigPrepRx_GetDiagMuxState_Param1;
boolean                               SigPrepRx_GetDiagMuxState_Param2;
LGM_MessageIdentifier                 LGM_SendMessage_Param1;
UINT8                                 *LGM_SendMessage_Param2;
NM_ModeType                           NM_GetMode_Param1;
uint32                                LPTMR0_GetTimeElapsed_Param1;
tsRte_BendingBeamFault_OtherHL        Rte_Write_SigPrepRx_Dbl_RightStatus_Param1;
tsRte_BendingBeamFault_OtherHL        Rte_Write_SigPrepRx_Dbl_LeftStatus_Param1;
tsRte_BendingBeamFault_OtherHL        Rte_Read_SigPrepRx_Dbl_LeftStatus_Param1;
tsRte_BendingBeamFault_OtherHL        Rte_Read_SigPrepRx_Dbl_RightStatus_Param1;
tsRte_BendingBeamFault_OtherHL        Rte_Read_Dbl_SigPrepTx_LeftStatus_Param1;
tsRte_BendingBeamFault_OtherHL        Rte_Read_Dbl_SigPrepTx_RightStatus_Param1;
NvM_BlockIdType                       NvM_WriteBlock_Param1;
void*                                 NvM_WriteBlock_Param2;
tPitch0                               Rte_Read_Pitch_Angle_Param1;
tsRte_SysMon_VehNetState              Rte_Read_SysMon_VehNetState_Param1;
tsRte_boMtxSegmentFault               Rte_Read_CtrlPxl_ActualPxlError_Param1;
tHS6_DAT_VSM_2AE                      Rte_Write_SigPrep_HS6_DAT_VSM_2AE_Received_Param1;
boolean                               Rte_Write_SigPrep_HS6_DAT_VSM_2AE_NotReceived_Param1;
tHS6_DAT_VSM_34E                      Rte_Write_SigPrep_HS6_DAT_VSM_34E_Received_Param1;
boolean                               Rte_Write_SigPrep_HS6_DAT_VSM_34E_NotReceived_Param1;
tHS6_COMMANDES_VSM_036                Rte_Write_SigPrep_HS6_COMMANDES_VSM_036_Received_Param1;
boolean                               Rte_Write_SigPrep_HS6_COMMANDES_VSM_036_NotReceived_Param1;
tHS6_DAT_BSI_432                      Rte_Write_SigPrep_HS6_DAT_BSI_432_Received_Param1;
boolean                               Rte_Write_SigPrep_HS6_DAT_BSI_432_NotReceived_Param1;
tHS6_DYN_ABR_38D                      Rte_Write_SigPrep_HS6_DYN_ABR_38D_Received_Param1;
boolean                               Rte_Write_SigPrep_HS6_DYN_ABR_38D_NotReceived_Param1;
uint8                                 Rte_Write_SigPrep_SleepBSI_Param1;
boolean                               Rte_Write_SigPrep_HS6_DIAG_DRVLED_Sent_Param1;
boolean                               Rte_Write_SigPrep_HS6_DIAG_DRVLED_NotSent_Param1;
tsRte_NTCTemperature                  Rte_Read_RSens_ThermzoneTemperatures_Param1;
tsRte_ActStatStp0                     Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1;
tsRte_SensorRaw                       Rte_Read_IoHwAb_GetSens_Raw_Param1;
tsRte_DblOut                          Rte_Read_Dbl_SwivellingOut_Param1;
tsRte_ucActualPxlPWM                  Rte_Read_CtrlPxl_ActualPxlPWM_Param1;
TE_Bool                               Rte_Read_SysMon_SetDiagMux_Param1;
tSysMon_SendFrame457                  Rte_Read_SysMon_SendFrame457_Param1;
tSysMon_SendFrame477                  Rte_Read_SysMon_SendFrame477_Param1;
tsPositionOut                         Rte_Read_ppsAvacOut_Param1;
tAdbOut                               Rte_Read_ppsAdb_Out_sVal_0_Param1;
tsRte_TgtLedSig0_ASIL                 Rte_Read_SysMon_TgtLedSig_sVal_Param1;
NM_ModeType                           Rte_Write_SigPrep_NMMode_Param1;
tsRte_PowerFactor                     Rte_Read_Cpm_SigPrepTx_PowerFactor_Param1;
tisHssStatusError                     Rte_Read_CtrlSwi_StatusErr_Param1;
tsRteCodingParameters                 Rte_Read_CodM_SigPrep_Para_Param1;


//=============================================================================
// Stub function returned value stubs
//=============================================================================
Std_ReturnType    Rte_Read_SigPrep_LifePhases_RetVal;
Std_ReturnType    Rte_Write_SigPrep_LifePhases_RetVal;
Std_ReturnType    Rte_Read_SigPrep_VehNetState_RetVal;
Std_ReturnType    Rte_Write_SigPrep_VehNetState_RetVal;
Std_ReturnType    Rte_Read_SigPrep_AnimationReq_RetVal;
Std_ReturnType    Rte_Write_SigPrep_AnimationReq_RetVal;
Std_ReturnType    Rte_Read_SigPrep_VehicleConfigSig_RetVal;
Std_ReturnType    Rte_Write_SigPrep_VehicleConfigSig_RetVal;
Std_ReturnType    Rte_Read_SigPrep_OdometerTotal_RetVal;
Std_ReturnType    Rte_Write_SigPrep_OdometerTotal_RetVal;
Std_ReturnType    Rte_Read_SigPrep_VehTimeCntr_RetVal;
Std_ReturnType    Rte_Write_SigPrep_VehTimeCntr_RetVal;
Std_ReturnType    Rte_Read_SysMon_VehicleSpeed_RetVal;
Std_ReturnType    Rte_Write_SysMon_VehicleSpeed_RetVal;
Std_ReturnType    Rte_Read_SigPrep_ElecSupState_RetVal;
Std_ReturnType    Rte_Write_SigPrep_ElecSupState_RetVal;
Std_ReturnType    Rte_Read_SigPrep_ElecIntegra_RetVal;
Std_ReturnType    Rte_Write_SigPrep_ElecIntegra_RetVal;
Std_ReturnType    Rte_Read_SigPrep_YawSpeed_RetVal;
Std_ReturnType    Rte_Write_SigPrep_YawSpeed_RetVal;
Std_ReturnType    Rte_Read_SigPrep_LevellingDiagStatus_RetVal;
Std_ReturnType    Rte_Write_SigPrep_LevellingDiagStatus_RetVal;
Std_ReturnType    Rte_Read_SigPrep_DcmDiagStatusR_RetVal;
Std_ReturnType    Rte_Write_SigPrep_DcmDiagStatusR_RetVal;
Std_ReturnType    Rte_Read_SigPrep_LevellingTgtPos_RetVal;
Std_ReturnType    Rte_Write_SigPrep_LevellingTgtPos_RetVal;
Std_ReturnType    Rte_Read_SigPrep_DynamicSigs_RetVal;
Std_ReturnType    Rte_Write_SigPrep_DynamicSigs_RetVal;
Std_ReturnType    Rte_Read_SigPrep_SteeringWheelAngle_RetVal;
Std_ReturnType    Rte_Write_SigPrep_SteeringWheelAngle_RetVal;
Std_ReturnType    Rte_Read_SigPrep_VehiclePitchAngle_RetVal;
Std_ReturnType    Rte_Write_SigPrep_VehiclePitchAngle_RetVal;
Std_ReturnType    Rte_Read_SigPrep_LevellingFeedback_RetVal;
Std_ReturnType    Rte_Write_SigPrep_LevellingFeedback_RetVal;
Std_ReturnType    Rte_Read_SigPrep_VehPathCurvature_RetVal;
Std_ReturnType    Rte_Write_SigPrep_VehPathCurvature_RetVal;
Std_ReturnType    Rte_Read_SigPrep_StdLgtClSbl_Req_RetVal;
Std_ReturnType    Rte_Write_SigPrep_StdLgtClSbl_Req_RetVal;
Std_ReturnType    Rte_Read_IoHwAbUser_GetMountingSide_RetVal;
Std_ReturnType    Rte_Write_IoHwAbUser_GetMountingSide_RetVal;
Std_ReturnType    Rte_Read_SigPrep_EnvCondition_RetVal;
Std_ReturnType    Rte_Write_SigPrep_EnvCondition_RetVal;
Std_ReturnType    Rte_Read_SigPrep_PerceiveSigGroup1_sVal_00_RetVal;
Std_ReturnType    Rte_Write_SigPrep_PerceiveSigGroup1_sVal_00_RetVal;
Std_ReturnType    Rte_Read_SigPrep_PerceiveSigGroup1_sVal_01_RetVal;
Std_ReturnType    Rte_Write_SigPrep_PerceiveSigGroup1_sVal_01_RetVal;
Std_ReturnType    Rte_Read_SigPrep_PerceiveSigGroup1_sVal_02_RetVal;
Std_ReturnType    Rte_Write_SigPrep_PerceiveSigGroup1_sVal_02_RetVal;
Std_ReturnType    Rte_Read_SigPrep_ClusterSigGroup1_sVal_00_RetVal;
Std_ReturnType    Rte_Write_SigPrep_ClusterSigGroup1_sVal_00_RetVal;
Std_ReturnType    Rte_Read_SigPrep_ClusterSigGroup1_sVal_01_RetVal;
Std_ReturnType    Rte_Write_SigPrep_ClusterSigGroup1_sVal_01_RetVal;
Std_ReturnType    Rte_Read_SigPrep_ClusterSigGroup1_sVal_02_RetVal;
Std_ReturnType    Rte_Write_SigPrep_ClusterSigGroup1_sVal_02_RetVal;
Std_ReturnType    Rte_Read_SigPrep_ClusterSigGroup1_sVal_03_RetVal;
Std_ReturnType    Rte_Write_SigPrep_ClusterSigGroup1_sVal_03_RetVal;
Std_ReturnType    Rte_Read_SigPrep_ClusterSigGroup1_sVal_04_RetVal;
Std_ReturnType    Rte_Write_SigPrep_ClusterSigGroup1_sVal_04_RetVal;
Std_ReturnType    Rte_Read_SigPrep_PerceiveSigGroup2_sVal_00_RetVal;
Std_ReturnType    Rte_Write_SigPrep_PerceiveSigGroup2_sVal_00_RetVal;
Std_ReturnType    Rte_Read_SigPrep_PerceiveSigGroup2_sVal_01_RetVal;
Std_ReturnType    Rte_Write_SigPrep_PerceiveSigGroup2_sVal_01_RetVal;
Std_ReturnType    Rte_Read_SigPrep_PerceiveSigGroup2_sVal_02_RetVal;
Std_ReturnType    Rte_Write_SigPrep_PerceiveSigGroup2_sVal_02_RetVal;
Std_ReturnType    Rte_Read_SigPrep_ClusterSigGroup2_sVal_00_RetVal;
Std_ReturnType    Rte_Write_SigPrep_ClusterSigGroup2_sVal_00_RetVal;
Std_ReturnType    Rte_Read_SigPrep_ClusterSigGroup2_sVal_01_RetVal;
Std_ReturnType    Rte_Write_SigPrep_ClusterSigGroup2_sVal_01_RetVal;
Std_ReturnType    Rte_Read_SigPrep_ClusterSigGroup2_sVal_02_RetVal;
Std_ReturnType    Rte_Write_SigPrep_ClusterSigGroup2_sVal_02_RetVal;
Std_ReturnType    Rte_Read_SigPrep_ClusterSigGroup2_sVal_03_RetVal;
Std_ReturnType    Rte_Write_SigPrep_ClusterSigGroup2_sVal_03_RetVal;
Std_ReturnType    Rte_Read_SigPrep_ClusterSigGroup2_sVal_04_RetVal;
Std_ReturnType    Rte_Write_SigPrep_ClusterSigGroup2_sVal_04_RetVal;
Std_ReturnType    Rte_Read_DrvLedDiag_Param1_RetVal;
Std_ReturnType    Rte_Read_CtrlStp_MasterCommand_RetVal;
Std_ReturnType    Rte_Read_CtrlStp_SlaveFeedback_RetVal;
Std_ReturnType    Rte_Read_CtrlStp_SlaveDiagStatus_RetVal;
boolean           SigPrep_RxCallback_SideCheck_297_RX_RetVal;
boolean           SigPrep_RxCallback_SideCheck_4D7_RX_RetVal;
boolean           SigPrep_RxCallback_SideCheck_2B7_RX_RetVal;
boolean           SigPrep_RxCallback_SideCheck_477_RX_RetVal;
IL_StatusType     LGM_SendMessage_RetVal;
uint32            LPTMR0_GetTimeElapsed_RetVal;
NM_ErrorCodeType  NM_GetMode_RetVal;
Std_ReturnType    Rte_Write_SigPrepRx_Dbl_RightStatus_RetVal;
Std_ReturnType    Rte_Write_SigPrepRx_Dbl_LeftStatus_RetVal;
Std_ReturnType    Rte_Read_SigPrepRx_Dbl_LeftStatus_RetVal;
Std_ReturnType    Rte_Read_SigPrepRx_Dbl_RightStatus_RetVal;
Std_ReturnType    NvM_WriteBlock_RetVal;
Std_ReturnType    Rte_Read_Pitch_Angle_RetVal;
Std_ReturnType    Rte_Read_SysMon_VehNetState_RetVal;
Std_ReturnType    Rte_Read_Dbl_SigPrepTx_LeftStatus_RetVal;
Std_ReturnType    Rte_Read_Dbl_SigPrepTx_RightStatus_RetVal;
Std_ReturnType    Rte_Read_SysMon_LifePhases_RetVal;
Std_ReturnType    Rte_Read_CtrlPxl_ActualPxlError_RetVal;
Std_ReturnType    Rte_Write_SigPrep_HS6_DAT_VSM_2AE_Received_RetVal;
Std_ReturnType    Rte_Write_SigPrep_HS6_DAT_VSM_2AE_NotReceived_RetVal;
Std_ReturnType    Rte_Write_SigPrep_HS6_DAT_VSM_34E_Received_RetVal;
Std_ReturnType    Rte_Write_SigPrep_HS6_DAT_VSM_34E_NotReceived_RetVal;
Std_ReturnType    Rte_Write_SigPrep_HS6_COMMANDES_VSM_036_Received_RetVal;
Std_ReturnType    Rte_Write_SigPrep_HS6_COMMANDES_VSM_036_NotReceived_RetVal;
Std_ReturnType    Rte_Write_SigPrep_HS6_DAT_BSI_432_Received_RetVal;
Std_ReturnType    Rte_Write_SigPrep_HS6_DAT_BSI_432_NotReceived_RetVal;
Std_ReturnType    Rte_Write_SigPrep_HS6_DYN_ABR_38D_Received_RetVal;
Std_ReturnType    Rte_Write_SigPrep_HS6_DYN_ABR_38D_NotReceived_RetVal;
Std_ReturnType    Rte_Write_SigPrep_SleepBSI_RetVal;
Std_ReturnType    Rte_Write_SigPrep_HS6_DIAG_DRVLED_Sent_RetVal;
Std_ReturnType    Rte_Write_SigPrep_HS6_DIAG_DRVLED_NotSent_RetVal;
Std_ReturnType    Rte_Read_RSens_ThermzoneTemperatures_RetVal;
Std_ReturnType    Rte_Read_CtrlStp_ActStatStp_sVal_0_RetVal;
Std_ReturnType    Rte_Read_IoHwAb_GetSens_Raw_RetVal;
Std_ReturnType    Rte_Read_Dbl_SwivellingOut_RetVal;
Std_ReturnType    Rte_Read_CtrlPxl_ActualPxlPWM_RetVal;
Std_ReturnType    Rte_Read_SysMon_SetDiagMux_RetVal;
Std_ReturnType    Rte_Read_SysMon_SendFrame457_RetVal;
Std_ReturnType    Rte_Read_SysMon_SendFrame477_RetVal;
Std_ReturnType    Rte_Read_ppsAvacOut_RetVal;
Std_ReturnType    Rte_Read_ppsAdb_Out_sVal_0_RetVal;
Std_ReturnType    Rte_Read_SysMon_TgtLedSig_sVal_RetVal;
Std_ReturnType    Rte_Write_SigPrep_NMMode_RetVal;
Std_ReturnType    Rte_Read_Cpm_SigPrepTx_PowerFactor_RetVal;
tPitch0           SigPrep_RxCallbacks_ConfigDetection_RetVal;
uint8             SigPrepTx_Callbacks_LogZoneLastDataSearch_RetVal;
Std_ReturnType    Rte_Read_CtrlSwi_StatusErr_RetVal;
Std_ReturnType    Rte_Read_CodM_SigPrep_Para_RetVal;


//=============================================================================
// Stub function hit count variables
//=============================================================================
uint32  Rte_Read_SigPrep_LifePhases_HitCount;
uint32  Rte_Write_SigPrep_LifePhases_HitCount;
uint32  Rte_Read_SigPrep_VehNetState_HitCount;
uint32  Rte_Write_SigPrep_VehNetState_HitCount;
uint32  Rte_Read_SigPrep_AnimationReq_HitCount;
uint32  Rte_Write_SigPrep_AnimationReq_HitCount;
uint32  Rte_Read_SigPrep_VehicleConfigSig_HitCount;
uint32  Rte_Write_SigPrep_VehicleConfigSig_HitCount;
uint32  Rte_Read_SigPrep_OdometerTotal_HitCount;
uint32  Rte_Write_SigPrep_OdometerTotal_HitCount;
uint32  Rte_Read_SigPrep_VehTimeCntr_HitCount;
uint32  Rte_Write_SigPrep_VehTimeCntr_HitCount;
uint32  Rte_Read_SysMon_VehicleSpeed_HitCount;
uint32  Rte_Write_SysMon_VehicleSpeed_HitCount;
uint32  Rte_Read_SigPrep_ElecSupState_HitCount;
uint32  Rte_Write_SigPrep_ElecSupState_HitCount;
uint32  Rte_Read_SigPrep_ElecIntegra_HitCount;
uint32  Rte_Write_SigPrep_ElecIntegra_HitCount;
uint32  Rte_Read_SigPrep_YawSpeed_HitCount;
uint32  Rte_Write_SigPrep_YawSpeed_HitCount;
uint32  Rte_Read_SigPrep_LevellingDiagStatus_HitCount;
uint32  Rte_Write_SigPrep_LevellingDiagStatus_HitCount;
uint32  Rte_Read_SigPrep_LevellingTgtPos_HitCount;
uint32  Rte_Read_SigPrep_DcmDiagStatusR_HitCount;
uint32  Rte_Write_SigPrep_DcmDiagStatusR_HitCount;
uint32  Rte_Write_SigPrep_LevellingTgtPos_HitCount;
uint32  Rte_Read_SigPrep_DynamicSigs_HitCount;
uint32  Rte_Write_SigPrep_DynamicSigs_HitCount;
uint32  Rte_Read_SigPrep_SteeringWheelAngle_HitCount;
uint32  Rte_Write_SigPrep_SteeringWheelAngle_HitCount;
uint32  Rte_Read_SigPrep_VehiclePitchAngle_HitCount;
uint32  Rte_Write_SigPrep_VehiclePitchAngle_HitCount;
uint32  Rte_Read_SigPrep_LevellingFeedback_HitCount;
uint32  Rte_Write_SigPrep_LevellingFeedback_HitCount;
uint32  Rte_Read_SigPrep_VehPathCurvature_HitCount;
uint32  Rte_Write_SigPrep_VehPathCurvature_HitCount;
uint32  Rte_Read_SigPrep_StdLgtClSbl_Req_HitCount;
uint32  Rte_Write_SigPrep_StdLgtClSbl_Req_HitCount;
uint32  Rte_Read_IoHwAbUser_GetMountingSide_HitCount;
uint32  Rte_Write_IoHwAbUser_GetMountingSide_HitCount;
uint32  Rte_Read_SigPrep_EnvCondition_HitCount;
uint32  Rte_Write_SigPrep_EnvCondition_HitCount;
uint32  Rte_Read_SigPrep_PerceiveSigGroup1_sVal_00_HitCount;
uint32  Rte_Write_SigPrep_PerceiveSigGroup1_sVal_00_HitCount;
uint32  Rte_Read_SigPrep_PerceiveSigGroup1_sVal_01_HitCount;
uint32  Rte_Write_SigPrep_PerceiveSigGroup1_sVal_01_HitCount;
uint32  Rte_Read_SigPrep_PerceiveSigGroup1_sVal_02_HitCount;
uint32  Rte_Write_SigPrep_PerceiveSigGroup1_sVal_02_HitCount;
uint32  Rte_Read_SigPrep_ClusterSigGroup1_sVal_00_HitCount;
uint32  Rte_Write_SigPrep_ClusterSigGroup1_sVal_00_HitCount;
uint32  Rte_Read_SigPrep_ClusterSigGroup1_sVal_01_HitCount;
uint32  Rte_Write_SigPrep_ClusterSigGroup1_sVal_01_HitCount;
uint32  Rte_Read_SigPrep_ClusterSigGroup1_sVal_02_HitCount;
uint32  Rte_Write_SigPrep_ClusterSigGroup1_sVal_02_HitCount;
uint32  Rte_Read_SigPrep_ClusterSigGroup1_sVal_03_HitCount;
uint32  Rte_Write_SigPrep_ClusterSigGroup1_sVal_03_HitCount;
uint32  Rte_Read_SigPrep_ClusterSigGroup1_sVal_04_HitCount;
uint32  Rte_Write_SigPrep_ClusterSigGroup1_sVal_04_HitCount;
uint32  Rte_Read_SigPrep_PerceiveSigGroup2_sVal_00_HitCount;
uint32  Rte_Write_SigPrep_PerceiveSigGroup2_sVal_00_HitCount;
uint32  Rte_Read_SigPrep_PerceiveSigGroup2_sVal_01_HitCount;
uint32  Rte_Write_SigPrep_PerceiveSigGroup2_sVal_01_HitCount;
uint32  Rte_Read_SigPrep_PerceiveSigGroup2_sVal_02_HitCount;
uint32  Rte_Write_SigPrep_PerceiveSigGroup2_sVal_02_HitCount;
uint32  Rte_Read_SigPrep_ClusterSigGroup2_sVal_00_HitCount;
uint32  Rte_Write_SigPrep_ClusterSigGroup2_sVal_00_HitCount;
uint32  Rte_Read_SigPrep_ClusterSigGroup2_sVal_01_HitCount;
uint32  Rte_Write_SigPrep_ClusterSigGroup2_sVal_01_HitCount;
uint32  Rte_Read_SigPrep_ClusterSigGroup2_sVal_02_HitCount;
uint32  Rte_Write_SigPrep_ClusterSigGroup2_sVal_02_HitCount;
uint32  Rte_Read_SigPrep_ClusterSigGroup2_sVal_03_HitCount;
uint32  Rte_Write_SigPrep_ClusterSigGroup2_sVal_03_HitCount;
uint32  Rte_Read_SigPrep_ClusterSigGroup2_sVal_04_HitCount;
uint32  Rte_Write_SigPrep_ClusterSigGroup2_sVal_04_HitCount;
uint32  Rte_Read_DrvLedDiag_Param1_HitCount;
uint32  Rte_Read_CtrlStp_MasterCommand_HitCount;
uint32  Rte_Read_CtrlStp_SlaveFeedback_HitCount;
uint32  Rte_Read_CtrlStp_SlaveDiagStatus_HitCount;
uint32  Dem_SetEventStatus_HitCount;
uint32  DAPI_BSIAckState_HitCount;
uint32  DAPI_SetDiagMux_HitCount;
uint32  DAPI_RemoveAllDE_HitCount;
uint32  DAPI_SetConfigMode_HitCount;
uint32  DAPI_SetMainStatus_HitCount;
uint32  DAPI_SyncModule_HitCount;
uint32  DAPI_SetPermToSend_HitCount;
uint32  EAPI_SetEIMInfo_CAN_HitCount;
uint32  CMGT_SetMileage_HitCount;
uint32  LGM_SendMessage_HitCount;
uint32  LPTMR0_GetTimeElapsed_HitCount;
uint32  Rte_Write_SigPrepRx_Dbl_RightStatus_HitCount;
uint32  Rte_Write_SigPrepRx_Dbl_LeftStatus_HitCount;
uint32  Rte_Read_SigPrepRx_Dbl_LeftStatus_HitCount;
uint32  Rte_Read_SigPrepRx_Dbl_RightStatus_HitCount;
uint32  Rte_Read_Dbl_SigPrepTx_LeftStatus_HitCount;
uint32  Rte_Read_Dbl_SigPrepTx_RightStatus_HitCount;
uint8   DAPI_TransmitAck_HitCount;
uint8   DAPI_TransmitNack_HitCount;
uint8   SigPrep_RxCallback_SideCheck_4D7_RX_HitCount;
uint8   NvM_WriteBlock_HitCount;
uint8   Rte_Read_Pitch_Angle_HitCount;
uint8   Rte_Read_SysMon_VehNetState_HitCount;
uint8   Rte_Read_SysMon_LifePhases_HitCount;
uint32  Rte_Read_CtrlPxl_ActualPxlError_HitCount;
uint32  Rte_Write_SigPrep_HS6_DAT_VSM_2AE_Received_HitCount;
uint32  Rte_Write_SigPrep_HS6_DAT_VSM_2AE_NotReceived_HitCount;
uint32  Rte_Write_SigPrep_HS6_DAT_VSM_34E_Received_HitCount;
uint32  Rte_Write_SigPrep_HS6_DAT_VSM_34E_NotReceived_HitCount;
uint32  Rte_Write_SigPrep_HS6_COMMANDES_VSM_036_Received_HitCount;
uint32  Rte_Write_SigPrep_HS6_COMMANDES_VSM_036_NotReceived_HitCount;
uint32  Rte_Write_SigPrep_HS6_DAT_BSI_432_Received_HitCount;
uint32  Rte_Write_SigPrep_HS6_DAT_BSI_432_NotReceived_HitCount;
uint32  Rte_Write_SigPrep_HS6_DYN_ABR_38D_Received_HitCount;
uint32  Rte_Write_SigPrep_HS6_DYN_ABR_38D_NotReceived_HitCount;
uint32  Rte_Write_SigPrep_SleepBSI_HitCount;
uint32  Rte_Write_SigPrep_HS6_DIAG_DRVLED_Sent_HitCount;
uint32  Rte_Write_SigPrep_HS6_DIAG_DRVLED_NotSent_HitCount;
uint32  Rte_Read_RSens_ThermzoneTemperatures_HitCount;
uint32  Rte_Read_CtrlStp_ActStatStp_sVal_0_HitCount;
uint32  Rte_Read_IoHwAb_GetSens_Raw_HitCount;
uint32  Rte_Read_Dbl_SwivellingOut_HitCount;
uint32  Rte_Read_CtrlPxl_ActualPxlPWM_HitCount;
uint32  Rte_Read_SysMon_SetDiagMux_HitCount;
uint32  Rte_Read_SysMon_SendFrame457_HitCount;
uint32  Rte_Read_SysMon_SendFrame477_HitCount;
uint32  Rte_Read_ppsAvacOut_HitCount;
uint32  Rte_Read_ppsAdb_Out_sVal_0_HitCount;
uint32  Rte_Read_SysMon_TgtLedSig_sVal_HitCount;
uint32  Rte_Write_SigPrep_NMMode_HitCount;
uint32  Rte_Read_Cpm_SigPrepTx_PowerFactor_HitCount;
uint32  NM_GetMode_HitCount;
uint32  Rte_Read_CtrlSwi_StatusErr_HitCount;
uint32  Rte_Read_CodM_SigPrep_Para_HitCount;


//=============================================================================
// Stub function definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief Rte_Read_SysMon_VehNetState
///
/// \descr Stub function for Rte_Read_SysMon_VehNetState
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SysMon_VehNetState(tsRte_SysMon_VehNetState* ppara1)
{
  *ppara1 = Rte_Read_SysMon_VehNetState_Param1;
  Rte_Read_SysMon_VehNetState_HitCount++;

  return Rte_Read_SysMon_VehNetState_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SysMon_LifePhases
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SysMon_LifePhases
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SysMon_LifePhases(tsRte_SysMon_LifePhases* ppara1)
{
  *ppara1 = Rte_Read_SysMon_LifePhases_Param1;
  Rte_Read_SysMon_LifePhases_HitCount++;

  return Rte_Read_SysMon_LifePhases_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Read_Pitch_Angle
///
/// \descr Stub function for Rte_Write_ppsAvacOut
///
/// \param  *ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_Pitch_Angle(tPitch0* ppara1)
{
  *ppara1 = Rte_Read_Pitch_Angle_Param1;
  Rte_Read_Pitch_Angle_HitCount++;

  return Rte_Read_Pitch_Angle_RetVal;
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
/// \brief  DAPI_TransmitNAck
///
/// \descr  Stub function created to simulate the behaviour of DAPI_TransmitNAck
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------
void DAPI_TransmitNack(void)
{
  DAPI_TransmitNack_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  DAPI_TransmitAck
///
/// \descr  Stub function created to simulate the behaviour of DAPI_TransmitAck
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------
void DAPI_TransmitAck(void)
{
  DAPI_TransmitAck_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_Dbl_SigPrepTx_LeftStatus
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_Dbl_SigPrepTx_LeftStatus
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_Dbl_SigPrepTx_LeftStatus(tsRte_BendingBeamFault_OtherHL* ppara1)
{
  *ppara1 = Rte_Read_Dbl_SigPrepTx_LeftStatus_Param1;
  Rte_Read_Dbl_SigPrepTx_LeftStatus_HitCount++;

  return Rte_Read_Dbl_SigPrepTx_LeftStatus_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_Dbl_SigPrepTx_RightStatus
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_Dbl_SigPrepTx_RightStatus
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_Dbl_SigPrepTx_RightStatus(tsRte_BendingBeamFault_OtherHL* ppara1)
{
  *ppara1 = Rte_Read_Dbl_SigPrepTx_RightStatus_Param1;
  Rte_Read_Dbl_SigPrepTx_RightStatus_HitCount++;

  return Rte_Read_Dbl_SigPrepTx_RightStatus_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrepRx_Dbl_RightStatus
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrepRx_Dbl_RightStatus
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Read_SigPrepRx_Dbl_RightStatus(tsRte_BendingBeamFault_OtherHL* ppara1)
{
  *ppara1 = Rte_Read_SigPrepRx_Dbl_RightStatus_Param1;
  Rte_Read_SigPrepRx_Dbl_RightStatus_HitCount++;

  return Rte_Read_SigPrepRx_Dbl_RightStatus_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrepRx_Dbl_RightStatus
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrepRx_Dbl_RightStatus
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Write_SigPrepRx_Dbl_RightStatus(const tsRte_BendingBeamFault_OtherHL* ppara1)
{
  Rte_Write_SigPrepRx_Dbl_RightStatus_Param1 = *ppara1;
  Rte_Write_SigPrepRx_Dbl_RightStatus_HitCount++;

  return Rte_Write_SigPrepRx_Dbl_RightStatus_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrepRx_Dbl_LeftStatus
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrepRx_Dbl_LeftStatus
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Read_SigPrepRx_Dbl_LeftStatus(tsRte_BendingBeamFault_OtherHL* ppara1)
{
  *ppara1 = Rte_Read_SigPrepRx_Dbl_LeftStatus_Param1;
  Rte_Read_SigPrepRx_Dbl_LeftStatus_HitCount++;

  return Rte_Read_SigPrepRx_Dbl_LeftStatus_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrepRx_Dbl_LeftStatus
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrepRx_Dbl_LeftStatus
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Write_SigPrepRx_Dbl_LeftStatus(const tsRte_BendingBeamFault_OtherHL* ppara1)
{
  Rte_Write_SigPrepRx_Dbl_LeftStatus_Param1 = *ppara1;
  Rte_Write_SigPrepRx_Dbl_LeftStatus_HitCount++;

  return Rte_Write_SigPrepRx_Dbl_LeftStatus_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_AnimationReq
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_AnimationReq
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_AnimationReq(tsRte_AnimationReq* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_AnimationReq_Param1;
  Rte_Read_SigPrep_AnimationReq_HitCount++;

  return Rte_Read_SigPrep_AnimationReq_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_AnimationReq
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_AnimationReq
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SigPrep_AnimationReq(const tsRte_AnimationReq* ppara1)
{
  Rte_Write_SigPrep_AnimationReq_Param1 = *ppara1;
  Rte_Write_SigPrep_AnimationReq_HitCount++;

  return Rte_Write_SigPrep_AnimationReq_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_VehicleConfigSig
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_VehicleConfigSig
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_VehicleConfigSig(tsRte_SigPrep_VehicleConfigSig* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_VehicleConfigSig_Param1;
  Rte_Read_SigPrep_VehicleConfigSig_HitCount++;

  return Rte_Read_SigPrep_VehicleConfigSig_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_VehicleConfigSig
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_VehicleConfigSig
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SigPrep_VehicleConfigSig(const tsRte_SigPrep_VehicleConfigSig* ppara1)
{
  Rte_Write_SigPrep_VehicleConfigSig_Param1 = *ppara1;
  Rte_Write_SigPrep_VehicleConfigSig_HitCount++;

  return Rte_Write_SigPrep_VehicleConfigSig_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_OdometerTotal
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_OdometerTotal
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_OdometerTotal(tsRte_OdometerTotal* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_OdometerTotal_Param1;
  Rte_Read_SigPrep_OdometerTotal_HitCount++;

  return Rte_Read_SigPrep_OdometerTotal_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_OdometerTotal
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_OdometerTotal
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SigPrep_OdometerTotal(const tsRte_OdometerTotal* ppara1)
{
  Rte_Write_SigPrep_OdometerTotal_Param1 = *ppara1;
  Rte_Write_SigPrep_OdometerTotal_HitCount++;

  return Rte_Write_SigPrep_OdometerTotal_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_VehTimeCntr
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_VehTimeCntr
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_VehTimeCntr(tsRte_VehTimeCntr* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_VehTimeCntr_Param1;
  Rte_Read_SigPrep_VehTimeCntr_HitCount++;

  return Rte_Read_SigPrep_VehTimeCntr_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_VehTimeCntr
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_VehTimeCntr
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SigPrep_VehTimeCntr(const tsRte_VehTimeCntr* ppara1)
{
  Rte_Write_SigPrep_VehTimeCntr_Param1 = *ppara1;
  Rte_Write_SigPrep_VehTimeCntr_HitCount++;

  return Rte_Write_SigPrep_VehTimeCntr_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SysMon_VehicleSpeed
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SysMon_VehicleSpeed
///
/// \param  ppara1
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
/// \brief  Rte_Write_SysMon_VehicleSpeed
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SysMon_VehicleSpeed
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SysMon_VehicleSpeed(const tsRte_SysMon_VehicleSpeed* ppara1)
{
  Rte_Write_SysMon_VehicleSpeed_Param1 = *ppara1;
  Rte_Write_SysMon_VehicleSpeed_HitCount++;

  return Rte_Write_SysMon_VehicleSpeed_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_ElecSupState
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_ElecSupState
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_ElecSupState(tsRte_SigPrep_ElecSupState* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_ElecSupState_Param1;
  Rte_Read_SigPrep_ElecSupState_HitCount++;

  return Rte_Read_SigPrep_ElecSupState_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_ElecSupState
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_ElecSupState
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SigPrep_ElecSupState(const tsRte_SigPrep_ElecSupState* ppara1)
{
  Rte_Write_SigPrep_ElecSupState_Param1 = *ppara1;
  Rte_Write_SigPrep_ElecSupState_HitCount++;

  return Rte_Write_SigPrep_ElecSupState_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_ElecIntegra
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_ElecIntegra
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_ElecIntegra(tsRte_ElecIntegra* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_ElecIntegra_Param1;
  Rte_Read_SigPrep_ElecIntegra_HitCount++;

  return Rte_Read_SigPrep_ElecIntegra_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_ElecIntegra
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_ElecIntegra
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SigPrep_ElecIntegra(const tsRte_ElecIntegra* ppara1)
{
  Rte_Write_SigPrep_ElecIntegra_Param1 = *ppara1;
  Rte_Write_SigPrep_ElecIntegra_HitCount++;

  return Rte_Write_SigPrep_ElecIntegra_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_YawSpeed
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_YawSpeed
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_YawSpeed(tsRte_SigPrep_YawSpeed* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_YawSpeed_Param1;
  Rte_Read_SigPrep_YawSpeed_HitCount++;

  return Rte_Read_SigPrep_YawSpeed_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_YawSpeed
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_YawSpeed
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SigPrep_YawSpeed(const tsRte_SigPrep_YawSpeed* ppara1)
{
  Rte_Write_SigPrep_YawSpeed_Param1 = *ppara1;
  Rte_Write_SigPrep_YawSpeed_HitCount++;

  return Rte_Write_SigPrep_YawSpeed_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_LevellingDiagStatus
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_LevellingDiagStatus
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_LevellingDiagStatus(tsRte_LevellingDiagStatus* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_LevellingDiagStatus_Param1;
  Rte_Read_SigPrep_LevellingDiagStatus_HitCount++;

  return Rte_Read_SigPrep_LevellingDiagStatus_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_LevellingDiagStatus
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_LevellingDiagStatus
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SigPrep_LevellingDiagStatus(const tsRte_LevellingDiagStatus* ppara1)
{
  Rte_Write_SigPrep_LevellingDiagStatus_Param1 = *ppara1;
  Rte_Write_SigPrep_LevellingDiagStatus_HitCount++;

  return Rte_Write_SigPrep_LevellingDiagStatus_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_LevellingTgtPos
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_LevellingTgtPos
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_LevellingTgtPos(tsRte_LevellingTgtPos* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_LevellingTgtPos_Param1;
  Rte_Read_SigPrep_LevellingTgtPos_HitCount++;

  return Rte_Read_SigPrep_LevellingTgtPos_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_DcmDiagStatusR
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_DcmDiagStatusR
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_DcmDiagStatusR(tsRte_DcmDiagStatusR* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_DcmDiagStatusR_Param1;
  Rte_Read_SigPrep_DcmDiagStatusR_HitCount++;

  return Rte_Read_SigPrep_DcmDiagStatusR_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_DcmDiagStatusR
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_DcmDiagStatusR
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SigPrep_DcmDiagStatusR(tsRte_DcmDiagStatusR* ppara1)
{
  Rte_Write_SigPrep_DcmDiagStatusR_Param1 = *ppara1;
  Rte_Write_SigPrep_DcmDiagStatusR_HitCount++;

  return Rte_Write_SigPrep_DcmDiagStatusR_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_LevellingTgtPos
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_LevellingTgtPos
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SigPrep_LevellingTgtPos(const tsRte_LevellingTgtPos* ppara1)
{
  Rte_Write_SigPrep_LevellingTgtPos_Param1 = *ppara1;
  Rte_Write_SigPrep_LevellingTgtPos_HitCount++;

  return Rte_Write_SigPrep_LevellingTgtPos_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_DynamicSigs
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_DynamicSigs
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_DynamicSigs(tsRte_SigPrep_DynamicSigs* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_DynamicSigs_Param1;
  Rte_Read_SigPrep_DynamicSigs_HitCount++;

  return Rte_Read_SigPrep_DynamicSigs_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_DynamicSigs
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_DynamicSigs
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SigPrep_DynamicSigs(const tsRte_SigPrep_DynamicSigs* ppara1)
{
  Rte_Write_SigPrep_DynamicSigs_Param1 = *ppara1;
  Rte_Write_SigPrep_DynamicSigs_HitCount++;

  return Rte_Write_SigPrep_DynamicSigs_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_SteeringWheelAngle
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_SteeringWheelAngle
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_SteeringWheelAngle(tsRte_SigPrep_SteeringWheelAngle* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_SteeringWheelAngle_Param1;
  Rte_Read_SigPrep_SteeringWheelAngle_HitCount++;

  return Rte_Read_SigPrep_SteeringWheelAngle_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_SteeringWheelAngle
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_SteeringWheelAngle
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SigPrep_SteeringWheelAngle(const tsRte_SigPrep_SteeringWheelAngle* ppara1)
{
  Rte_Write_SigPrep_SteeringWheelAngle_Param1 = *ppara1;
  Rte_Write_SigPrep_SteeringWheelAngle_HitCount++;

  return Rte_Write_SigPrep_SteeringWheelAngle_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_VehiclePitchAngle
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_VehiclePitchAngle
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_VehiclePitchAngle(tsRte_SigPrep_VehiclePitchAngle* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_VehiclePitchAngle_Param1;
  Rte_Read_SigPrep_VehiclePitchAngle_HitCount++;

  return Rte_Read_SigPrep_VehiclePitchAngle_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_VehiclePitchAngle
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_VehiclePitchAngle
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SigPrep_VehiclePitchAngle(const tsRte_SigPrep_VehiclePitchAngle* ppara1)
{
  Rte_Write_SigPrep_VehiclePitchAngle_Param1 = *ppara1;
  Rte_Write_SigPrep_VehiclePitchAngle_HitCount++;

  return Rte_Write_SigPrep_VehiclePitchAngle_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_LevellingFeedback
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_LevellingFeedback
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_LevellingFeedback(tsRte_LevellingFeedback* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_LevellingFeedback_Param1;
  Rte_Read_SigPrep_LevellingFeedback_HitCount++;

  return Rte_Read_SigPrep_LevellingFeedback_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_LevellingFeedback
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_LevellingFeedback
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SigPrep_LevellingFeedback(const tsRte_LevellingFeedback* ppara1)
{
  Rte_Write_SigPrep_LevellingFeedback_Param1 = *ppara1;
  Rte_Write_SigPrep_LevellingFeedback_HitCount++;

  return Rte_Write_SigPrep_LevellingFeedback_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_VehPathCurvature
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_VehPathCurvature
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_VehPathCurvature(tsRte_SigPrep_VehPathCurvature* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_VehPathCurvature_Param1;
  Rte_Read_SigPrep_VehPathCurvature_HitCount++;

  return Rte_Read_SigPrep_VehPathCurvature_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_VehPathCurvature
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_VehPathCurvature
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SigPrep_VehPathCurvature(const tsRte_SigPrep_VehPathCurvature* ppara1)
{
  Rte_Write_SigPrep_VehPathCurvature_Param1 = *ppara1;
  Rte_Write_SigPrep_VehPathCurvature_HitCount++;

  return Rte_Write_SigPrep_VehPathCurvature_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_StdLgtClSbl_Req
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_StdLgtClSbl_Req
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_StdLgtClSbl_Req(tsRte_SigPrepLgtClSblReq* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_StdLgtClSbl_Req_Param1;
  Rte_Read_SigPrep_StdLgtClSbl_Req_HitCount++;

  return Rte_Read_SigPrep_StdLgtClSbl_Req_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_StdLgtClSbl_Req
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_StdLgtClSbl_Req
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SigPrep_StdLgtClSbl_Req(const tsRte_SigPrepLgtClSblReq* ppara1)
{
  Rte_Write_SigPrep_StdLgtClSbl_Req_Param1 = *ppara1;
  Rte_Write_SigPrep_StdLgtClSbl_Req_HitCount++;

  return Rte_Write_SigPrep_StdLgtClSbl_Req_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_IoHwAbUser_GetMountingSide
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_IoHwAbUser_GetMountingSide
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

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_IoHwAbUser_GetMountingSide
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_IoHwAbUser_GetMountingSide
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_IoHwAbUser_GetMountingSide(const teRte_MountingSide* ppara1)
{
  Rte_Write_IoHwAbUser_GetMountingSide_Param1 = *ppara1;
  Rte_Write_IoHwAbUser_GetMountingSide_HitCount++;

  return Rte_Write_IoHwAbUser_GetMountingSide_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_EnvCondition
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_EnvCondition
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_EnvCondition(tsRte_SigPrep_EnvCondition* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_EnvCondition_Param1;
  Rte_Read_SigPrep_EnvCondition_HitCount++;

  return Rte_Read_SigPrep_EnvCondition_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_EnvCondition
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_EnvCondition
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SigPrep_EnvCondition(const tsRte_SigPrep_EnvCondition* ppara1)
{
  Rte_Write_SigPrep_EnvCondition_Param1 = *ppara1;
  Rte_Write_SigPrep_EnvCondition_HitCount++;

  return Rte_Write_SigPrep_EnvCondition_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_PerceiveSigGroup1_sVal_00
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_PerceiveSigGroup1_sVal_00
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_PerceiveSigGroup1_sVal_00(tsRte_SigPrep_PerceiveSigGroup1_sVal* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_PerceiveSigGroup1_sVal_00_Param1;
  Rte_Read_SigPrep_PerceiveSigGroup1_sVal_00_HitCount++;

  return Rte_Read_SigPrep_PerceiveSigGroup1_sVal_00_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_PerceiveSigGroup1_sVal_00
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_PerceiveSigGroup1_sVal_00
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SigPrep_PerceiveSigGroup1_sVal_00(const tsRte_SigPrep_PerceiveSigGroup1_sVal* ppara1)
{
  Rte_Write_SigPrep_PerceiveSigGroup1_sVal_00_Param1 = *ppara1;
  Rte_Write_SigPrep_PerceiveSigGroup1_sVal_00_HitCount++;

  return Rte_Write_SigPrep_PerceiveSigGroup1_sVal_00_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_PerceiveSigGroup1_sVal_01
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_PerceiveSigGroup1_sVal_01
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_PerceiveSigGroup1_sVal_01(tsRte_SigPrep_PerceiveSigGroup1_sVal* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_PerceiveSigGroup1_sVal_01_Param1;
  Rte_Read_SigPrep_PerceiveSigGroup1_sVal_01_HitCount++;

  return Rte_Read_SigPrep_PerceiveSigGroup1_sVal_01_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_PerceiveSigGroup1_sVal_01
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_PerceiveSigGroup1_sVal_01
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SigPrep_PerceiveSigGroup1_sVal_01(const tsRte_SigPrep_PerceiveSigGroup1_sVal* ppara1)
{
  Rte_Write_SigPrep_PerceiveSigGroup1_sVal_01_Param1 = *ppara1;
  Rte_Write_SigPrep_PerceiveSigGroup1_sVal_01_HitCount++;

  return Rte_Write_SigPrep_PerceiveSigGroup1_sVal_01_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_PerceiveSigGroup1_sVal_02
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_PerceiveSigGroup1_sVal_02
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_PerceiveSigGroup1_sVal_02(tsRte_SigPrep_PerceiveSigGroup1_sVal* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_PerceiveSigGroup1_sVal_02_Param1;
  Rte_Read_SigPrep_PerceiveSigGroup1_sVal_02_HitCount++;

  return Rte_Read_SigPrep_PerceiveSigGroup1_sVal_02_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_PerceiveSigGroup1_sVal_02
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_PerceiveSigGroup1_sVal_02
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SigPrep_PerceiveSigGroup1_sVal_02(const tsRte_SigPrep_PerceiveSigGroup1_sVal* ppara1)
{
  Rte_Write_SigPrep_PerceiveSigGroup1_sVal_02_Param1 = *ppara1;
  Rte_Write_SigPrep_PerceiveSigGroup1_sVal_02_HitCount++;

  return Rte_Write_SigPrep_PerceiveSigGroup1_sVal_02_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_ClusterSigGroup1_sVal_00
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_ClusterSigGroup1_sVal_00
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_ClusterSigGroup1_sVal_00(tsRte_SigPrep_ClusterSigGroup1_sVal* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_ClusterSigGroup1_sVal_00_Param1;
  Rte_Read_SigPrep_ClusterSigGroup1_sVal_00_HitCount++;

  return Rte_Read_SigPrep_ClusterSigGroup1_sVal_00_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_ClusterSigGroup1_sVal_00
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_ClusterSigGroup1_sVal_00
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SigPrep_ClusterSigGroup1_sVal_00(const tsRte_SigPrep_ClusterSigGroup1_sVal* ppara1)
{
  Rte_Write_SigPrep_ClusterSigGroup1_sVal_00_Param1 = *ppara1;
  Rte_Write_SigPrep_ClusterSigGroup1_sVal_00_HitCount++;

  return Rte_Write_SigPrep_ClusterSigGroup1_sVal_00_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_ClusterSigGroup1_sVal_01
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_ClusterSigGroup1_sVal_01
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_ClusterSigGroup1_sVal_01(tsRte_SigPrep_ClusterSigGroup1_sVal* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_ClusterSigGroup1_sVal_01_Param1;
  Rte_Read_SigPrep_ClusterSigGroup1_sVal_01_HitCount++;

  return Rte_Read_SigPrep_ClusterSigGroup1_sVal_01_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_ClusterSigGroup1_sVal_01
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_ClusterSigGroup1_sVal_01
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SigPrep_ClusterSigGroup1_sVal_01(const tsRte_SigPrep_ClusterSigGroup1_sVal* ppara1)
{
  Rte_Write_SigPrep_ClusterSigGroup1_sVal_01_Param1 = *ppara1;
  Rte_Write_SigPrep_ClusterSigGroup1_sVal_01_HitCount++;

  return Rte_Write_SigPrep_ClusterSigGroup1_sVal_01_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_ClusterSigGroup1_sVal_02
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_ClusterSigGroup1_sVal_02
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_ClusterSigGroup1_sVal_02(tsRte_SigPrep_ClusterSigGroup1_sVal* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_ClusterSigGroup1_sVal_02_Param1;
  Rte_Read_SigPrep_ClusterSigGroup1_sVal_02_HitCount++;

  return Rte_Read_SigPrep_ClusterSigGroup1_sVal_02_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_ClusterSigGroup1_sVal_02
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_ClusterSigGroup1_sVal_02
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SigPrep_ClusterSigGroup1_sVal_02(const tsRte_SigPrep_ClusterSigGroup1_sVal* ppara1)
{
  Rte_Write_SigPrep_ClusterSigGroup1_sVal_02_Param1 = *ppara1;
  Rte_Write_SigPrep_ClusterSigGroup1_sVal_02_HitCount++;

  return Rte_Write_SigPrep_ClusterSigGroup1_sVal_02_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_ClusterSigGroup1_sVal_03
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_ClusterSigGroup1_sVal_03
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_ClusterSigGroup1_sVal_03(tsRte_SigPrep_ClusterSigGroup1_sVal* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_ClusterSigGroup1_sVal_03_Param1;
  Rte_Read_SigPrep_ClusterSigGroup1_sVal_03_HitCount++;

  return Rte_Read_SigPrep_ClusterSigGroup1_sVal_03_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_ClusterSigGroup1_sVal_03
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_ClusterSigGroup1_sVal_03
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SigPrep_ClusterSigGroup1_sVal_03(const tsRte_SigPrep_ClusterSigGroup1_sVal* ppara1)
{
  Rte_Write_SigPrep_ClusterSigGroup1_sVal_03_Param1 = *ppara1;
  Rte_Write_SigPrep_ClusterSigGroup1_sVal_03_HitCount++;

  return Rte_Write_SigPrep_ClusterSigGroup1_sVal_03_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_ClusterSigGroup1_sVal_04
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_ClusterSigGroup1_sVal_04
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_ClusterSigGroup1_sVal_04(tsRte_SigPrep_ClusterSigGroup1_sVal* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_ClusterSigGroup1_sVal_04_Param1;
  Rte_Read_SigPrep_ClusterSigGroup1_sVal_04_HitCount++;

  return Rte_Read_SigPrep_ClusterSigGroup1_sVal_04_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_ClusterSigGroup1_sVal_04
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_ClusterSigGroup1_sVal_04
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SigPrep_ClusterSigGroup1_sVal_04(const tsRte_SigPrep_ClusterSigGroup1_sVal* ppara1)
{
  Rte_Write_SigPrep_ClusterSigGroup1_sVal_04_Param1 = *ppara1;
  Rte_Write_SigPrep_ClusterSigGroup1_sVal_04_HitCount++;

  return Rte_Write_SigPrep_ClusterSigGroup1_sVal_04_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_PerceiveSigGroup2_sVal_00
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_PerceiveSigGroup2_sVal_00
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_PerceiveSigGroup2_sVal_00(tsRte_SigPrep_PerceiveSigGroup2_sVal* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_PerceiveSigGroup2_sVal_00_Param1;
  Rte_Read_SigPrep_PerceiveSigGroup2_sVal_00_HitCount++;

  return Rte_Read_SigPrep_PerceiveSigGroup2_sVal_00_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_PerceiveSigGroup2_sVal_00
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_PerceiveSigGroup2_sVal_00
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SigPrep_PerceiveSigGroup2_sVal_00(const tsRte_SigPrep_PerceiveSigGroup2_sVal* ppara1)
{
  Rte_Write_SigPrep_PerceiveSigGroup2_sVal_00_Param1 = *ppara1;
  Rte_Write_SigPrep_PerceiveSigGroup2_sVal_00_HitCount++;

  return Rte_Write_SigPrep_PerceiveSigGroup2_sVal_00_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_PerceiveSigGroup2_sVal_01
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_PerceiveSigGroup2_sVal_01
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_PerceiveSigGroup2_sVal_01(tsRte_SigPrep_PerceiveSigGroup2_sVal* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_PerceiveSigGroup2_sVal_01_Param1;
  Rte_Read_SigPrep_PerceiveSigGroup2_sVal_01_HitCount++;

  return Rte_Read_SigPrep_PerceiveSigGroup2_sVal_01_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_PerceiveSigGroup2_sVal_01
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_PerceiveSigGroup2_sVal_01
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SigPrep_PerceiveSigGroup2_sVal_01(const tsRte_SigPrep_PerceiveSigGroup2_sVal* ppara1)
{
  Rte_Write_SigPrep_PerceiveSigGroup2_sVal_01_Param1 = *ppara1;
  Rte_Write_SigPrep_PerceiveSigGroup2_sVal_01_HitCount++;

  return Rte_Write_SigPrep_PerceiveSigGroup2_sVal_01_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_PerceiveSigGroup2_sVal_02
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_PerceiveSigGroup2_sVal_02
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_PerceiveSigGroup2_sVal_02(tsRte_SigPrep_PerceiveSigGroup2_sVal* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_PerceiveSigGroup2_sVal_02_Param1;
  Rte_Read_SigPrep_PerceiveSigGroup2_sVal_02_HitCount++;

  return Rte_Read_SigPrep_PerceiveSigGroup2_sVal_02_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_PerceiveSigGroup2_sVal_02
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_PerceiveSigGroup2_sVal_02
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SigPrep_PerceiveSigGroup2_sVal_02(const tsRte_SigPrep_PerceiveSigGroup2_sVal* ppara1)
{
  Rte_Write_SigPrep_PerceiveSigGroup2_sVal_02_Param1 = *ppara1;
  Rte_Write_SigPrep_PerceiveSigGroup2_sVal_02_HitCount++;

  return Rte_Write_SigPrep_PerceiveSigGroup2_sVal_02_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_ClusterSigGroup2_sVal_00
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_ClusterSigGroup2_sVal_00
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_ClusterSigGroup2_sVal_00(tsRte_SigPrep_ClusterSigGroup2_sVal* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_ClusterSigGroup2_sVal_00_Param1;
  Rte_Read_SigPrep_ClusterSigGroup2_sVal_00_HitCount++;

  return Rte_Read_SigPrep_ClusterSigGroup2_sVal_00_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_ClusterSigGroup2_sVal_00
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_ClusterSigGroup2_sVal_00
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SigPrep_ClusterSigGroup2_sVal_00(const tsRte_SigPrep_ClusterSigGroup2_sVal* ppara1)
{
  Rte_Write_SigPrep_ClusterSigGroup2_sVal_00_Param1 = *ppara1;
  Rte_Write_SigPrep_ClusterSigGroup2_sVal_00_HitCount++;

  return Rte_Write_SigPrep_ClusterSigGroup2_sVal_00_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_ClusterSigGroup2_sVal_01
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_ClusterSigGroup2_sVal_01
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_ClusterSigGroup2_sVal_01(tsRte_SigPrep_ClusterSigGroup2_sVal* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_ClusterSigGroup2_sVal_01_Param1;
  Rte_Read_SigPrep_ClusterSigGroup2_sVal_01_HitCount++;

  return Rte_Read_SigPrep_ClusterSigGroup2_sVal_01_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_ClusterSigGroup2_sVal_01
///
/// \descr  Stub function created to simulate the behaviour of 
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SigPrep_ClusterSigGroup2_sVal_01(const tsRte_SigPrep_ClusterSigGroup2_sVal* ppara1)
{
  Rte_Write_SigPrep_ClusterSigGroup2_sVal_01_Param1 = *ppara1;
  Rte_Write_SigPrep_ClusterSigGroup2_sVal_01_HitCount++;

  return Rte_Write_SigPrep_ClusterSigGroup2_sVal_01_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_ClusterSigGroup2_sVal_02
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_ClusterSigGroup2_sVal_02
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_ClusterSigGroup2_sVal_02(tsRte_SigPrep_ClusterSigGroup2_sVal* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_ClusterSigGroup2_sVal_02_Param1;
  Rte_Read_SigPrep_ClusterSigGroup2_sVal_02_HitCount++;

  return Rte_Read_SigPrep_ClusterSigGroup2_sVal_02_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_ClusterSigGroup2_sVal_02
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_ClusterSigGroup2_sVal_02
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SigPrep_ClusterSigGroup2_sVal_02(const tsRte_SigPrep_ClusterSigGroup2_sVal* ppara1)
{
  Rte_Write_SigPrep_ClusterSigGroup2_sVal_02_Param1 = *ppara1;
  Rte_Write_SigPrep_ClusterSigGroup2_sVal_02_HitCount++;

  return Rte_Write_SigPrep_ClusterSigGroup2_sVal_02_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_ClusterSigGroup2_sVal_03
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_ClusterSigGroup2_sVal_03
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_ClusterSigGroup2_sVal_03(tsRte_SigPrep_ClusterSigGroup2_sVal* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_ClusterSigGroup2_sVal_03_Param1;
  Rte_Read_SigPrep_ClusterSigGroup2_sVal_03_HitCount++;

  return Rte_Read_SigPrep_ClusterSigGroup2_sVal_03_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_ClusterSigGroup2_sVal_03
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_ClusterSigGroup2_sVal_03
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SigPrep_ClusterSigGroup2_sVal_03(const tsRte_SigPrep_ClusterSigGroup2_sVal* ppara1)
{
  Rte_Write_SigPrep_ClusterSigGroup2_sVal_03_Param1 = *ppara1;
  Rte_Write_SigPrep_ClusterSigGroup2_sVal_03_HitCount++;

  return Rte_Write_SigPrep_ClusterSigGroup2_sVal_03_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_ClusterSigGroup2_sVal_04
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_ClusterSigGroup2_sVal_04
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_ClusterSigGroup2_sVal_04(tsRte_SigPrep_ClusterSigGroup2_sVal* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_ClusterSigGroup2_sVal_04_Param1;
  Rte_Read_SigPrep_ClusterSigGroup2_sVal_04_HitCount++;

  return Rte_Read_SigPrep_ClusterSigGroup2_sVal_04_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_ClusterSigGroup2_sVal_04
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_ClusterSigGroup2_sVal_04
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SigPrep_ClusterSigGroup2_sVal_04(const tsRte_SigPrep_ClusterSigGroup2_sVal* ppara1)
{
  Rte_Write_SigPrep_ClusterSigGroup2_sVal_04_Param1 = *ppara1;
  Rte_Write_SigPrep_ClusterSigGroup2_sVal_04_HitCount++;

  return Rte_Write_SigPrep_ClusterSigGroup2_sVal_04_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_DrvLedDiag
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_DrvLedDiag
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_DrvLedDiag(tsRte_Hs6_Diag_Drvled_L_457* ppara1)
{
  *ppara1 = Rte_Read_DrvLedDiag_Param1;
  Rte_Read_DrvLedDiag_Param1_HitCount++;

  return Rte_Read_DrvLedDiag_Param1_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlStp_MasterCommand
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_DrvLedDiag
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CtrlStp_MasterCommand(tsRte_LevellingTgtPos* ppara1)
{
  *ppara1 = Rte_Read_CtrlStp_MasterCommand_Param1;
  Rte_Read_CtrlStp_MasterCommand_HitCount++;

  return Rte_Read_CtrlStp_MasterCommand_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_DrvLedDiag
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_DrvLedDiag
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CtrlStp_SlaveFeedback(tsRte_LevellingFeedback* ppara1)
{
  *ppara1 = Rte_Read_CtrlStp_SlaveFeedback_Param1;
  Rte_Read_CtrlStp_SlaveFeedback_HitCount++;

  return Rte_Read_CtrlStp_SlaveFeedback_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_DrvLedDiag
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_DrvLedDiag
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CtrlStp_SlaveDiagStatus(tsRte_LevellingDiagStatus* ppara1)
{
  *ppara1 = Rte_Read_CtrlStp_SlaveDiagStatus_Param1;
  Rte_Read_CtrlStp_SlaveDiagStatus_HitCount++;

  return Rte_Read_CtrlStp_SlaveDiagStatus_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlPxl_ActualPxlError
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CtrlPxl_ActualPxlError
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CtrlPxl_ActualPxlError(tsRte_boMtxSegmentFault* ppara1)
{
  *ppara1 = Rte_Read_CtrlPxl_ActualPxlError_Param1;
  Rte_Read_CtrlPxl_ActualPxlError_HitCount++;

  return Rte_Read_CtrlPxl_ActualPxlError_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_HS6_DAT_VSM_2AE_Received
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_HS6_DAT_VSM_2AE_Received
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Write_SigPrep_HS6_DAT_VSM_2AE_Received(const tHS6_DAT_VSM_2AE* ppara1)
{
  Rte_Write_SigPrep_HS6_DAT_VSM_2AE_Received_Param1 = *ppara1;
  Rte_Write_SigPrep_HS6_DAT_VSM_2AE_Received_HitCount++;

  return Rte_Write_SigPrep_HS6_DAT_VSM_2AE_Received_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_HS6_DAT_VSM_2AE_NotReceived
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_HS6_DAT_VSM_2AE_NotReceived
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Write_SigPrep_HS6_DAT_VSM_2AE_NotReceived(boolean ppara1)
{
  Rte_Write_SigPrep_HS6_DAT_VSM_2AE_NotReceived_Param1 = ppara1;
  Rte_Write_SigPrep_HS6_DAT_VSM_2AE_NotReceived_HitCount++;

  return Rte_Write_SigPrep_HS6_DAT_VSM_2AE_NotReceived_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_HS6_DAT_VSM_34E_Received
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_HS6_DAT_VSM_34E_Received
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Write_SigPrep_HS6_DAT_VSM_34E_Received(const tHS6_DAT_VSM_34E* ppara1)
{
  Rte_Write_SigPrep_HS6_DAT_VSM_34E_Received_Param1 = *ppara1;
  Rte_Write_SigPrep_HS6_DAT_VSM_34E_Received_HitCount++;

  return Rte_Write_SigPrep_HS6_DAT_VSM_34E_Received_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_HS6_DAT_VSM_34E_NotReceived
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_HS6_DAT_VSM_34E_NotReceived
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Write_SigPrep_HS6_DAT_VSM_34E_NotReceived(boolean ppara1)
{
  Rte_Write_SigPrep_HS6_DAT_VSM_34E_NotReceived_Param1 = ppara1;
  Rte_Write_SigPrep_HS6_DAT_VSM_34E_NotReceived_HitCount++;

  return Rte_Write_SigPrep_HS6_DAT_VSM_34E_NotReceived_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_HS6_COMMANDES_VSM_036_Received
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_HS6_COMMANDES_VSM_036_Received
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Write_SigPrep_HS6_COMMANDES_VSM_036_Received(const tHS6_COMMANDES_VSM_036* ppara1)
{
  Rte_Write_SigPrep_HS6_COMMANDES_VSM_036_Received_Param1 = *ppara1;
  Rte_Write_SigPrep_HS6_COMMANDES_VSM_036_Received_HitCount++;

  return Rte_Write_SigPrep_HS6_COMMANDES_VSM_036_Received_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_HS6_COMMANDES_VSM_036_NotReceived
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_HS6_COMMANDES_VSM_036_NotReceived
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Write_SigPrep_HS6_COMMANDES_VSM_036_NotReceived(boolean ppara1)
{
  Rte_Write_SigPrep_HS6_COMMANDES_VSM_036_NotReceived_Param1 = ppara1;
  Rte_Write_SigPrep_HS6_COMMANDES_VSM_036_NotReceived_HitCount++;

  return Rte_Write_SigPrep_HS6_COMMANDES_VSM_036_NotReceived_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_HS6_DAT_BSI_432_Received
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_HS6_DAT_BSI_432_Received
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Write_SigPrep_HS6_DAT_BSI_432_Received(const tHS6_DAT_BSI_432* ppara1)
{
  Rte_Write_SigPrep_HS6_DAT_BSI_432_Received_Param1 = *ppara1;
  Rte_Write_SigPrep_HS6_DAT_BSI_432_Received_HitCount++;

  return Rte_Write_SigPrep_HS6_DAT_BSI_432_Received_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_HS6_DAT_BSI_432_NotReceived
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_HS6_DAT_BSI_432_NotReceived
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Write_SigPrep_HS6_DAT_BSI_432_NotReceived(boolean ppara1)
{
  Rte_Write_SigPrep_HS6_DAT_BSI_432_NotReceived_Param1 = ppara1;
  Rte_Write_SigPrep_HS6_DAT_BSI_432_NotReceived_HitCount++;

  return Rte_Write_SigPrep_HS6_DAT_BSI_432_NotReceived_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_HS6_DYN_ABR_38D_Received
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_HS6_DYN_ABR_38D_Received
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Write_SigPrep_HS6_DYN_ABR_38D_Received(const tHS6_DYN_ABR_38D* ppara1)
{
  Rte_Write_SigPrep_HS6_DYN_ABR_38D_Received_Param1 = *ppara1;
  Rte_Write_SigPrep_HS6_DYN_ABR_38D_Received_HitCount++;

  return Rte_Write_SigPrep_HS6_DYN_ABR_38D_Received_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_HS6_DYN_ABR_38D_NotReceived
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_HS6_DYN_ABR_38D_NotReceived
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Write_SigPrep_HS6_DYN_ABR_38D_NotReceived(boolean ppara1)
{
  Rte_Write_SigPrep_HS6_DYN_ABR_38D_NotReceived_Param1 = ppara1;
  Rte_Write_SigPrep_HS6_DYN_ABR_38D_NotReceived_HitCount++;

  return Rte_Write_SigPrep_HS6_DYN_ABR_38D_NotReceived_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_SleepBSI
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_SleepBSI
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Write_SigPrep_SleepBSI(const uint8* ppara1)
{
  Rte_Write_SigPrep_SleepBSI_Param1 = *ppara1;
  Rte_Write_SigPrep_SleepBSI_HitCount++;

  return Rte_Write_SigPrep_SleepBSI_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_HS6_DIAG_DRVLED_Sent
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_HS6_DIAG_DRVLED_Sent
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Write_SigPrep_HS6_DIAG_DRVLED_Sent(boolean ppara1)
{
  Rte_Write_SigPrep_HS6_DIAG_DRVLED_Sent_Param1 = ppara1;
  Rte_Write_SigPrep_HS6_DIAG_DRVLED_Sent_HitCount++;

  return Rte_Write_SigPrep_HS6_DIAG_DRVLED_Sent_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_HS6_DIAG_DRVLED_NotSent
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_HS6_DIAG_DRVLED_NotSent
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Write_SigPrep_HS6_DIAG_DRVLED_NotSent(boolean ppara1)
{
  Rte_Write_SigPrep_HS6_DIAG_DRVLED_NotSent_Param1 = ppara1;
  Rte_Write_SigPrep_HS6_DIAG_DRVLED_NotSent_HitCount++;

  return Rte_Write_SigPrep_HS6_DIAG_DRVLED_NotSent_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_RSens_ThermzoneTemperatures
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_RSens_ThermzoneTemperatures
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Read_RSens_ThermzoneTemperatures(tsRte_NTCTemperature* ppara1)
{
  *ppara1 = Rte_Read_RSens_ThermzoneTemperatures_Param1;
  Rte_Read_RSens_ThermzoneTemperatures_HitCount++;

  return Rte_Read_RSens_ThermzoneTemperatures_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlStp_ActStatStp_sVal_0
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CtrlStp_ActStatStp_sVal_0
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Read_CtrlStp_ActStatStp_sVal_0(tsRte_ActStatStp0* ppara1)
{
  *ppara1 = Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1;
  Rte_Read_CtrlStp_ActStatStp_sVal_0_HitCount++;

  return Rte_Read_CtrlStp_ActStatStp_sVal_0_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_IoHwAb_GetSens_Raw
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_IoHwAb_GetSens_Raw
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Read_IoHwAb_GetSens_Raw(tsRte_SensorRaw* ppara1)
{
  *ppara1 = Rte_Read_IoHwAb_GetSens_Raw_Param1;
  Rte_Read_IoHwAb_GetSens_Raw_HitCount++;

  return Rte_Read_IoHwAb_GetSens_Raw_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_Dbl_SwivellingOut
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_Dbl_SwivellingOut
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Read_Dbl_SwivellingOut(tsRte_DblOut* ppara1)
{
  *ppara1 = Rte_Read_Dbl_SwivellingOut_Param1;
  Rte_Read_Dbl_SwivellingOut_HitCount++;

  return Rte_Read_Dbl_SwivellingOut_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlPxl_ActualPxlPWM
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CtrlPxl_ActualPxlPWM
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Read_CtrlPxl_ActualPxlPWM(tsRte_ucActualPxlPWM* ppara1)
{
  *ppara1 = Rte_Read_CtrlPxl_ActualPxlPWM_Param1;
  Rte_Read_CtrlPxl_ActualPxlPWM_HitCount++;

  return Rte_Read_CtrlPxl_ActualPxlPWM_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SysMon_SetDiagMux
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SysMon_SetDiagMux
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Read_SysMon_SetDiagMux(TE_Bool* ppara1)
{
  *ppara1 = Rte_Read_SysMon_SetDiagMux_Param1;
  Rte_Read_SysMon_SetDiagMux_HitCount++;

  return Rte_Read_SysMon_SetDiagMux_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SysMon_SendFrame457
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SysMon_SendFrame457
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Read_SysMon_SendFrame457(tSysMon_SendFrame457* ppara1)
{
  *ppara1 = Rte_Read_SysMon_SendFrame457_Param1;
  Rte_Read_SysMon_SendFrame457_HitCount++;

  return Rte_Read_SysMon_SendFrame457_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SysMon_SendFrame477
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SysMon_SendFrame477
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Read_SysMon_SendFrame477(tSysMon_SendFrame477* ppara1)
{
  *ppara1 = Rte_Read_SysMon_SendFrame477_Param1;
  Rte_Read_SysMon_SendFrame477_HitCount++;

  return Rte_Read_SysMon_SendFrame477_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_ppsAvacOut
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_ppsAvacOut
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_ppsAvacOut(tsPositionOut* ppara1)
{
  *ppara1 = Rte_Read_ppsAvacOut_Param1;
  Rte_Read_ppsAvacOut_HitCount++;

  return Rte_Read_ppsAvacOut_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_ppsAvacOut
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_ppsAvacOut
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Read_ppsAdb_Out_sVal_0(tAdbOut* ppara1)
{
  *ppara1 = Rte_Read_ppsAdb_Out_sVal_0_Param1;
  Rte_Read_ppsAdb_Out_sVal_0_HitCount++;

  return Rte_Read_ppsAdb_Out_sVal_0_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SysMon_TgtLedSig_sVal
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SysMon_TgtLedSig_sVal
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Read_SysMon_TgtLedSig_sVal(tsRte_TgtLedSig0_ASIL* ppara1)
{
  *ppara1 = Rte_Read_SysMon_TgtLedSig_sVal_Param1;
  Rte_Read_SysMon_TgtLedSig_sVal_HitCount++;

  return Rte_Read_SysMon_TgtLedSig_sVal_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SigPrep_NMMode
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SigPrep_NMMode
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Write_SigPrep_NMMode(const NM_ModeType* ppara1)
{
  Rte_Write_SigPrep_NMMode_Param1 = *ppara1;
  Rte_Write_SigPrep_NMMode_HitCount++;

  return Rte_Write_SigPrep_NMMode_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_Cpm_SigPrepTx_PowerFactor
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_Cpm_SigPrepTx_PowerFactor
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Read_Cpm_SigPrepTx_PowerFactor(tsRte_PowerFactor* ppara1)
{
  *ppara1 = Rte_Read_Cpm_SigPrepTx_PowerFactor_Param1;
  Rte_Read_Cpm_SigPrepTx_PowerFactor_HitCount++;

  return Rte_Read_Cpm_SigPrepTx_PowerFactor_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlSwi_StatusErr
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CtrlSwi_StatusErr
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CtrlSwi_StatusErr(tisHssStatusError* ppara1)
{
  *ppara1 = Rte_Read_CtrlSwi_StatusErr_Param1;
  Rte_Read_CtrlSwi_StatusErr_HitCount++;

  return Rte_Read_CtrlSwi_StatusErr_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CodM_SigPrep_Para
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CodM_SigPrep_Para
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CodM_SigPrep_Para(tsRteCodingParameters* ppara1)
{
  *ppara1 = Rte_Read_CodM_SigPrep_Para_Param1;
  Rte_Read_CodM_SigPrep_Para_HitCount++;

  return Rte_Read_CodM_SigPrep_Para_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Dem_SetEventStatus
///
/// \descr  Stub function created to simulate the behaviour of Dem_SetEventStatus
///
/// \param  unAlecId
/// \param  ucTestStatus
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
/// \brief  DAPI_BSIAckState
///
/// \descr  Stub function created to simulate the behaviour of DAPI_BSIAckState
///
/// \param  PIu8_AckCode
///
/// \return void
//-----------------------------------------------------------------------------
void DAPI_BSIAckState(const Tu8_Int PIu8_AckCode)
{
  DAPI_BSIAckState_Param1 = PIu8_AckCode;
  DAPI_BSIAckState_HitCount++;
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
/// \brief  DAPI_SetDiagMux
///
/// \descr  Stub function created to simulate the behaviour of DAPI_SetDiagMux
///
/// \param  PIE_DiagMuxOn
///
/// \return void
//-----------------------------------------------------------------------------
void DAPI_SetDiagMux(const TE_Bool PIE_DiagMuxOn)
{
  DAPI_SetDiagMux_Param1 = PIE_DiagMuxOn;
  DAPI_SetDiagMux_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  DAPI_RemoveAllDE
///
/// \descr  Stub function created to simulate the behaviour of DAPI_RemoveAllDE
///
/// \param  PIE_RemoveState
///
/// \return void
//-----------------------------------------------------------------------------
void DAPI_RemoveAllDE(const TE_Bool PIE_RemoveState)
{
  DAPI_RemoveAllDE_Param1 = PIE_RemoveState;
  DAPI_RemoveAllDE_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  DAPI_SetConfigMode
///
/// \descr  Stub function created to simulate the behaviour of DAPI_SetConfigMode
///
/// \param  PIE_ConfigMode
///
/// \return void
//-----------------------------------------------------------------------------
void DAPI_SetConfigMode(DAPI_TE_ConfigMode PIE_ConfigMode)
{
  DAPI_SetConfigMode_Param1 = PIE_ConfigMode;
  DAPI_SetConfigMode_HitCount++;
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
/// \brief  DAPI_SyncModule
///
/// \descr  Stub function created to simulate the behaviour of DAPI_SyncModule
///
/// \param  PIu32_DateVehicle
///
/// \return void
//-----------------------------------------------------------------------------
void DAPI_SyncModule(const Tu32_Int PIu32_DateVehicle)
{
  DAPI_SyncModule_Param1 = PIu32_DateVehicle;
  DAPI_SyncModule_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  EAPI_SetEIMInfo_CAN
///
/// \descr  Stub function created to simulate the behaviour of EAPI_SetEIMInfo_CAN
///
/// \param  PIu8_Interd_Memo_Def
/// \param  PIE_LifePhase
///
/// \return void
//-----------------------------------------------------------------------------
void EAPI_SetEIMInfo_CAN(Tu8_Int PIu8_Interd_Memo_Def, LEIM_TE_LifePhase PIE_LifePhase)
{
  EAPI_SetEIMInfo_CAN_Param1 = PIu8_Interd_Memo_Def;
  EAPI_SetEIMInfo_CAN_Param2 = PIE_LifePhase;
  EAPI_SetEIMInfo_CAN_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  CMGT_SetMileage
///
/// \descr  Stub function created to simulate the behaviour of CMGT_SetMileage
///
/// \param  PIu32_Mileage
///
/// \return void
//-----------------------------------------------------------------------------
void CMGT_SetMileage(const Tu32_Int PIu32_Mileage)
{
  CMGT_SetMileage_Param1 = PIu32_Mileage;
  CMGT_SetMileage_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  LGM_SendMessage
///
/// \descr  Stub function created to simulate the behaviour of LGM_SendMessage
///
/// \param  ID
/// \param  dataRef
///
/// \return void
//-----------------------------------------------------------------------------
IL_StatusType LGM_SendMessage(LGM_MessageIdentifier ID, const UINT8* const dataRef)
{
  LGM_SendMessage_Param1 = ID;
  LGM_SendMessage_Param2 = *dataRef;
  LGM_SendMessage_HitCount++;

  return LGM_SendMessage_RetVal;
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

  return (LPTMR0_GetTimeElapsed_RetVal);
}



// EOF

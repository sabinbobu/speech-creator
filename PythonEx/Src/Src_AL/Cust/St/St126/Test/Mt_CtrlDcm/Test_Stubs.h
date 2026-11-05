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
#include <Nvm.h>

#include <RteCommonTypes.h>
#include "../Include/_NM_Types.h"
//=============================================================================
// Typedef
//=============================================================================

//=============================================================================
// Stub function declarations
//=============================================================================

uint32                LPTMR0_GetTimeElapsed(const uint32 ulStartValue);
NM_ErrorCodeType      NM_GetMode(NM_ModeType* p_NMMode);
Std_ReturnType        Rte_Read_SysMon_VehicleSpeed(tsRte_SysMon_VehicleSpeed* ppara1);
Std_ReturnType        Rte_Read_SysMon_VehNetState(tsRte_SysMon_VehNetState* ppara1);
Std_ReturnType        Rte_Read_SigPrep_VehicleConfigSig(tsRte_SigPrep_VehicleConfigSig* ppara1);
Std_ReturnType        Rte_Read_ppsAvacStat1Out_Port(tPositionOut* ppara1);
Std_ReturnType        Rte_Read_CddDcm_ErrorStatus(tsRte_DcmStatusError* ppara1);
Std_ReturnType        Rte_Read_Pitch_PlausState(teRte_HlsSensorState* ppara1);
Std_ReturnType        Rte_Read_SigPrep_LevellingTgtPos(tsRte_LevellingTgtPos* ppara1);
Std_ReturnType        Rte_Read_CtrlDcm_MasterCommand(tsRte_LevellingTgtPos* ppara1);
Std_ReturnType        Rte_Read_DrvLedDiag(tsRte_Hs6_Diag_Drvled_L_457* ppara1);
Std_ReturnType        Rte_Read_SigPrep_DcmDiagStatusR(tsRte_DcmDiagStatusR* ppara1);
Std_ReturnType        Rte_Write_DrvLedDiag(const tsRte_Hs6_Diag_Drvled_L_457* ppara1);
Std_ReturnType        Rte_Read_DrvLedDiagR(tsRte_Hs6_Diag_Drvled_R_477* ppara1);
Std_ReturnType        Rte_Write_CtrlDcm_MasterCommand(tsRte_LevellingTgtPos* ppara1);
Std_ReturnType        Rte_Write_ppCtrlDcmTarget0_DcmTargetValues(tsRte_CtrlDcmTarget* ppara1);
Std_ReturnType        Rte_Write_CtrlDcm_StatusParameters_Port(tsRte_CtrlDcmStatusParams* ppara1);
Std_ReturnType        Rte_Read_Dcm_RoutineControl(tsRte_DcMotorRoutineControl* ppara1);
Std_ReturnType        Rte_Write_DrvLedDiagR(tsRte_Hs6_Diag_Drvled_R_477* ppara1);
Std_ReturnType        Rte_Write_Dcm_RoutineControl(tsRte_DcMotorRoutineControl* ppara1);
Std_ReturnType        Rte_Read_CodM_Pitch_Para(tsRteCodingParameters*     ppara1);

//=============================================================================
// Stub function parameter stubs
//=============================================================================

extern uint32                                       LPTMR0_GetTimeElapsed_Param1;
extern NM_ModeType                                  NM_GetMode_Param1;
extern teRte_MountingSide                           Rte_Read_IoHwAbUser_GetMountingSide_Param1;
extern tsRte_SysMon_VehicleSpeed                    Rte_Read_SysMon_VehicleSpeed_Param1;
extern tsRte_SysMon_VehNetState                     Rte_Read_SysMon_VehNetState_Param1;
extern tsRte_SigPrep_VehicleConfigSig               Rte_Read_SigPrep_VehicleConfigSig_Param1;
extern tPositionOut                                 Rte_Read_ppsAvacStat1Out_Port_Param1;
extern tsRte_DcmStatusError                         Rte_Read_CddDcm_ErrorStatus_Param1;
extern teRte_HlsSensorState                         Rte_Read_Pitch_PlausState_Param1;
extern tsRte_LevellingTgtPos                        Rte_Read_SigPrep_LevellingTgtPos_Param1;
extern tsRte_LevellingTgtPos                        Rte_Read_CtrlDcm_MasterCommand_Param1;
extern tsRte_Hs6_Diag_Drvled_L_457                  Rte_Read_DrvLedDiag_Param1;
extern tsRte_DcmDiagStatusR                         Rte_Read_SigPrep_DcmDiagStatusR_Param1;
extern tsRte_Hs6_Diag_Drvled_L_457                  Rte_Write_DrvLedDiag_Param1;
extern tsRte_Hs6_Diag_Drvled_R_477                  Rte_Read_DrvLedDiagR_Param1;
extern tsRte_LevellingTgtPos                        Rte_Write_CtrlDcm_MasterCommand_Param1;
extern tsRte_CtrlDcmTarget                          Rte_Write_ppCtrlDcmTarget0_DcmTargetValues_Param1;
extern tsRte_CtrlDcmStatusParams                    Rte_Write_CtrlDcm_StatusParameters_Port_Param1;
extern tsRte_DcMotorRoutineControl                  Rte_Read_Dcm_RoutineControl_Param1;
extern tsRte_Hs6_Diag_Drvled_R_477                  Rte_Write_DrvLedDiagR_Param1;
extern tsRte_DcMotorRoutineControl                  Rte_Write_Dcm_RoutineControl_Param1;
extern tsRteCodingParameters                        Rte_Read_CodM_Pitch_Para_Param1;

//=============================================================================
// Stub function returned value stubs
//=============================================================================

extern uint32                 LPTMR0_GetTimeElapsed_RetVal;
extern NM_ErrorCodeType       NM_GetMode_RetVal;
extern Std_ReturnType         Rte_Read_IoHwAbUser_GetMountingSide_RetVal;
extern Std_ReturnType         Rte_Read_SysMon_VehicleSpeed_RetVal;
extern Std_ReturnType         Rte_Read_SysMon_VehNetState_RetVal;
extern Std_ReturnType         Rte_Read_SigPrep_VehicleConfigSig_RetVal;
extern Std_ReturnType         Rte_Read_ppsAvacStat1Out_Port_RetVal;
extern Std_ReturnType         Rte_Read_CddDcm_ErrorStatus_RetVal;
extern Std_ReturnType         Rte_Read_Pitch_PlausState_RetVal;
extern Std_ReturnType         Rte_Read_SigPrep_LevellingTgtPos_RetVal;
extern Std_ReturnType         Rte_Read_CtrlDcm_MasterCommand_RetVal;
extern Std_ReturnType         Rte_Read_DrvLedDiag_RetVal;
extern Std_ReturnType         Rte_Read_SigPrep_DcmDiagStatusR_RetVal;
extern Std_ReturnType         Rte_Write_DrvLedDiag_RetVal;
extern Std_ReturnType         Rte_Read_DrvLedDiagR_RetVal;
extern Std_ReturnType         Rte_Write_CtrlDcm_MasterCommand_RetVal;
extern Std_ReturnType         Rte_Write_ppCtrlDcmTarget0_DcmTargetValues_RetVal;
extern Std_ReturnType         Rte_Write_CtrlDcm_StatusParameters_Port_RetVal;
extern Std_ReturnType         Rte_Read_Dcm_RoutineControl_RetVal;
extern Std_ReturnType         Rte_Write_DrvLedDiagR_RetVal;
extern Std_ReturnType         Rte_Write_Dcm_RoutineControl_RetVal;
extern Std_ReturnType         Rte_Read_CodM_Pitch_Para_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================

extern uint8   LPTMR0_GetTimeElapsed_HitCount;
extern uint32  NM_GetMode_HitCount;
extern uint8   Rte_Read_IoHwAbUser_GetMountingSide_HitCount;
extern uint8   Rte_Read_SysMon_VehicleSpeed_HitCount;
extern uint8   Rte_Read_SysMon_VehNetState_HitCount;
extern uint8   Rte_Read_SigPrep_VehicleConfigSig_HitCount;
extern uint8   Rte_Read_ppsAvacStat1Out_Port_HitCount;
extern uint8   Rte_Read_CddDcm_ErrorStatus_HitCount;
extern uint8   Rte_Read_Pitch_PlausState_HitCount;
extern uint8   Rte_Read_SigPrep_LevellingTgtPos_HitCount;
extern uint8   Rte_Read_CtrlDcm_MasterCommand_HitCount;
extern uint8   Rte_Read_DrvLedDiag_HitCount;
extern uint8   Rte_Read_SigPrep_DcmDiagStatusR_HitCount;
extern uint8   Rte_Write_DrvLedDiag_HitCount;
extern uint8   Rte_Read_DrvLedDiagR_HitCount;
extern uint8   Rte_Write_CtrlDcm_MasterCommand_HitCount;
extern uint8   Rte_Write_ppCtrlDcmTarget0_DcmTargetValues_HitCount;
extern uint8   Rte_Write_CtrlDcm_StatusParameters_Port_HitCount;
extern uint8   Rte_Read_Dcm_RoutineControl_HitCount;
extern uint8   Rte_Write_DrvLedDiagR_HitCount;
extern uint8   Rte_Write_Dcm_RoutineControl_HitCount;
extern uint8   Rte_Read_CodM_Pitch_Para_HitCount;

#endif // TEST_STUBS_2023_08_25_H_

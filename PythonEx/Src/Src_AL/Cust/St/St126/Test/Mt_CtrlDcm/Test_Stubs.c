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

uint32                                       LPTMR0_GetTimeElapsed_Param1;
NM_ModeType                                  NM_GetMode_Param1;
teRte_MountingSide                           Rte_Read_IoHwAbUser_GetMountingSide_Param1;
tsRte_SysMon_VehicleSpeed                    Rte_Read_SysMon_VehicleSpeed_Param1;
tsRte_SysMon_VehNetState                     Rte_Read_SysMon_VehNetState_Param1;
tsRte_SigPrep_VehicleConfigSig               Rte_Read_SigPrep_VehicleConfigSig_Param1;
tPositionOut                                 Rte_Read_ppsAvacStat1Out_Port_Param1;
tsRte_DcmStatusError                         Rte_Read_CddDcm_ErrorStatus_Param1;
teRte_HlsSensorState                         Rte_Read_Pitch_PlausState_Param1;
tsRte_LevellingTgtPos                        Rte_Read_SigPrep_LevellingTgtPos_Param1;
tsRte_LevellingTgtPos                        Rte_Read_CtrlDcm_MasterCommand_Param1;
tsRte_Hs6_Diag_Drvled_L_457                  Rte_Read_DrvLedDiag_Param1;
tsRte_DcmDiagStatusR                         Rte_Read_SigPrep_DcmDiagStatusR_Param1;
tsRte_Hs6_Diag_Drvled_L_457                  Rte_Write_DrvLedDiag_Param1;
tsRte_Hs6_Diag_Drvled_R_477                  Rte_Read_DrvLedDiagR_Param1;
tsRte_LevellingTgtPos                        Rte_Write_CtrlDcm_MasterCommand_Param1;
tsRte_CtrlDcmTarget                          Rte_Write_ppCtrlDcmTarget0_DcmTargetValues_Param1;
tsRte_CtrlDcmStatusParams                    Rte_Write_CtrlDcm_StatusParameters_Port_Param1;
tsRte_DcMotorRoutineControl                  Rte_Read_Dcm_RoutineControl_Param1;
tsRte_Hs6_Diag_Drvled_R_477                  Rte_Write_DrvLedDiagR_Param1;
tsRte_DcMotorRoutineControl                  Rte_Write_Dcm_RoutineControl_Param1;
tsRteCodingParameters                        Rte_Read_CodM_Pitch_Para_Param1;

//=============================================================================
// Stub function returned value stubs
//=============================================================================

uint32                 LPTMR0_GetTimeElapsed_RetVal;
NM_ErrorCodeType       NM_GetMode_RetVal;
Std_ReturnType         Rte_Read_IoHwAbUser_GetMountingSide_RetVal;
Std_ReturnType         Rte_Read_SysMon_VehicleSpeed_RetVal;
Std_ReturnType         Rte_Read_SysMon_VehNetState_RetVal;
Std_ReturnType         Rte_Read_SigPrep_VehicleConfigSig_RetVal;
Std_ReturnType         Rte_Read_ppsAvacStat1Out_Port_RetVal;
Std_ReturnType         Rte_Read_CddDcm_ErrorStatus_RetVal;
Std_ReturnType         Rte_Read_Pitch_PlausState_RetVal;
Std_ReturnType         Rte_Read_SigPrep_LevellingTgtPos_RetVal;
Std_ReturnType         Rte_Read_CtrlDcm_MasterCommand_RetVal;
Std_ReturnType         Rte_Read_DrvLedDiag_RetVal;
Std_ReturnType         Rte_Read_SigPrep_DcmDiagStatusR_RetVal;
Std_ReturnType         Rte_Write_DrvLedDiag_RetVal;
Std_ReturnType         Rte_Read_DrvLedDiagR_RetVal;
Std_ReturnType         Rte_Write_CtrlDcm_MasterCommand_RetVal;
Std_ReturnType         Rte_Write_ppCtrlDcmTarget0_DcmTargetValues_RetVal;
Std_ReturnType         Rte_Write_CtrlDcm_StatusParameters_Port_RetVal;
Std_ReturnType         Rte_Read_Dcm_RoutineControl_RetVal;
Std_ReturnType         Rte_Write_DrvLedDiagR_RetVal;
Std_ReturnType         Rte_Write_Dcm_RoutineControl_RetVal;
Std_ReturnType         Rte_Read_CodM_Pitch_Para_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================

uint8   LPTMR0_GetTimeElapsed_HitCount;
uint32  NM_GetMode_HitCount;
uint8   Rte_Read_IoHwAbUser_GetMountingSide_HitCount;
uint8   Rte_Read_SysMon_VehicleSpeed_HitCount;
uint8   Rte_Read_SysMon_VehNetState_HitCount;
uint8   Rte_Read_SigPrep_VehicleConfigSig_HitCount;
uint8   Rte_Read_ppsAvacStat1Out_Port_HitCount;
uint8   Rte_Read_CddDcm_ErrorStatus_HitCount;
uint8   Rte_Read_Pitch_PlausState_HitCount;
uint8   Rte_Read_SigPrep_LevellingTgtPos_HitCount;
uint8   Rte_Read_CtrlDcm_MasterCommand_HitCount;
uint8   Rte_Read_DrvLedDiag_HitCount;
uint8   Rte_Read_SigPrep_DcmDiagStatusR_HitCount;
uint8   Rte_Write_DrvLedDiag_HitCount;
uint8   Rte_Read_DrvLedDiagR_HitCount;
uint8   Rte_Write_CtrlDcm_MasterCommand_HitCount;
uint8   Rte_Write_ppCtrlDcmTarget0_DcmTargetValues_HitCount;
uint8   Rte_Write_CtrlDcm_StatusParameters_Port_HitCount;
uint8   Rte_Read_Dcm_RoutineControl_HitCount;
uint8   Rte_Write_DrvLedDiagR_HitCount;
uint8   Rte_Write_Dcm_RoutineControl_HitCount;
uint8   Rte_Read_CodM_Pitch_Para_HitCount;

//=============================================================================
// Stub function definitions
//=============================================================================

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
  LPTMR0_GetTimeElapsed_Param1 = ulStartValue;
  LPTMR0_GetTimeElapsed_HitCount++;

  return LPTMR0_GetTimeElapsed_RetVal;
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
/// \brief  Rte_Read_CodM_Pitch_Para
///
/// \descr Stub used to simulate the behaviour of  Rte_Read_CodM_Pitch_Para
///
/// \param  *ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Read_CodM_Pitch_Para(tsRteCodingParameters *ppara1)
{
  *ppara1 = Rte_Read_CodM_Pitch_Para_Param1;
  Rte_Read_CodM_Pitch_Para_HitCount++;
  return  Rte_Read_CodM_Pitch_Para_RetVal;
}

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
/// \brief Rte_Read_SysMon_VehicleSpeed
///
/// \descr Stub function for Rte_Read_SysMon_VehicleSpeed
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
/// \brief  Rte_Read_ppsAvacStat1Out_Port
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_ppsAvacStat1Out_Port
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_ppsAvacStat1Out_Port(tPositionOut* ppara1)
{
  *ppara1 = Rte_Read_ppsAvacStat1Out_Port_Param1;
  Rte_Read_ppsAvacStat1Out_Port_HitCount++;
  return Rte_Read_ppsAvacStat1Out_Port_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CddDcm_ErrorStatus
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CddDcm_ErrorStatus
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CddDcm_ErrorStatus(tsRte_DcmStatusError* ppara1)
{
  *ppara1 = Rte_Read_CddDcm_ErrorStatus_Param1;
  Rte_Read_CddDcm_ErrorStatus_HitCount++;
  return Rte_Read_CddDcm_ErrorStatus_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_Pitch_PlausState
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_Pitch_PlausState
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_Pitch_PlausState(teRte_HlsSensorState* ppara1)
{
  *ppara1 = Rte_Read_Pitch_PlausState_Param1;
  Rte_Read_Pitch_PlausState_HitCount++;
  return Rte_Read_Pitch_PlausState_RetVal;
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
/// \brief  Rte_Read_CtrlDcm_MasterCommand
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CtrlDcm_MasterCommand
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CtrlDcm_MasterCommand(tsRte_LevellingTgtPos* ppara1)
{
  *ppara1 = Rte_Read_CtrlDcm_MasterCommand_Param1;
  Rte_Read_CtrlDcm_MasterCommand_HitCount++;
  return Rte_Read_CtrlDcm_MasterCommand_RetVal;
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
  Rte_Read_DrvLedDiag_HitCount++;
  return Rte_Read_DrvLedDiag_RetVal;
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
/// \brief Rte_Write_DrvLedDiag
///
/// \descr Stub function for Rte_Write_DrvLedDiag
///
/// \param  tsRte_Hs6_Diag_Drvled_L_457
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_DrvLedDiag(const tsRte_Hs6_Diag_Drvled_L_457* ppara1)
{
  Rte_Write_DrvLedDiag_Param1 = *ppara1;
  Rte_Write_DrvLedDiag_HitCount++;
  return Rte_Write_DrvLedDiag_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_DrvLedDiagR
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_DrvLedDiagR
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_DrvLedDiagR(tsRte_Hs6_Diag_Drvled_R_477* ppara1)
{
  *ppara1 = Rte_Read_DrvLedDiagR_Param1;
  Rte_Read_DrvLedDiagR_HitCount++;
  return Rte_Read_DrvLedDiagR_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Write_CtrlDcm_MasterCommand
///
/// \descr Stub function for Rte_Write_CtrlDcm_MasterCommand
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CtrlDcm_MasterCommand(tsRte_LevellingTgtPos* ppara1)
{
  Rte_Write_CtrlDcm_MasterCommand_Param1 = *ppara1;
  Rte_Write_CtrlDcm_MasterCommand_HitCount++;
  return Rte_Write_CtrlDcm_MasterCommand_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Write_ppCtrlDcmTarget0_DcmTargetValues
///
/// \descr Stub function for Rte_Write_ppCtrlDcmTarget0_DcmTargetValues
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_ppCtrlDcmTarget0_DcmTargetValues(tsRte_CtrlDcmTarget* ppara1)
{
  Rte_Write_ppCtrlDcmTarget0_DcmTargetValues_Param1 = *ppara1;
  Rte_Write_ppCtrlDcmTarget0_DcmTargetValues_HitCount++;
  return Rte_Write_ppCtrlDcmTarget0_DcmTargetValues_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Write_CtrlDcm_StatusParameters_Port
///
/// \descr Stub function for Rte_Write_CtrlDcm_StatusParameters_Port
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CtrlDcm_StatusParameters_Port(tsRte_CtrlDcmStatusParams* ppara1)
{
  Rte_Write_CtrlDcm_StatusParameters_Port_Param1 = *ppara1;
  Rte_Write_CtrlDcm_StatusParameters_Port_HitCount++;
  return Rte_Write_CtrlDcm_StatusParameters_Port_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Read_Dcm_RoutineControl
///
/// \descr Stub function for Rte_Read_Dcm_RoutineControl
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_Dcm_RoutineControl(tsRte_DcMotorRoutineControl* ppara1)
{
  *ppara1 = Rte_Read_Dcm_RoutineControl_Param1;
  Rte_Read_Dcm_RoutineControl_HitCount++;
  return Rte_Read_Dcm_RoutineControl_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Write_DrvLedDiagR
///
/// \descr Stub function for Rte_Write_DrvLedDiagR
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_DrvLedDiagR(tsRte_Hs6_Diag_Drvled_R_477* ppara1)
{
  Rte_Write_DrvLedDiagR_Param1 = *ppara1;
  Rte_Write_DrvLedDiagR_HitCount++;
  return Rte_Write_DrvLedDiagR_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Write_Dcm_RoutineControl
///
/// \descr Stub function for Rte_Write_Dcm_RoutineControl
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_Dcm_RoutineControl(tsRte_DcMotorRoutineControl* ppara1)
{
  Rte_Write_Dcm_RoutineControl_Param1 = *ppara1;
  Rte_Write_Dcm_RoutineControl_HitCount++;
  return Rte_Write_Dcm_RoutineControl_RetVal;
}
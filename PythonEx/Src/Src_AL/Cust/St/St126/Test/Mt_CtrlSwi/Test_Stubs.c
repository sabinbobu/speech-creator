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
extern tsRteCodingParameters        Rte_Write_CodM_CtrlFan_Para_Param1;
extern uint16                       Rte_Write_CtrlSwi_TgtValue_Fan1_Param1;
extern uint16                       Rte_Write_CtrlSwi_TgtValue_Fan2_Param1;
extern tRteCtrlSwi_ErrorFlags       Rte_Write_CtrlSwi_HssStatus_Param1;
extern tisHssStatusError            Rte_Write_CtrlSwi_StatusErr_Param1;
extern uint16                       Rte_Write_CtrlSwi_TgtValue_Fan1_Param1;
extern tRteSwitchTgtVal             Rte_Write_CtrlSwi_TgtValue_SMRGB_Param1;
extern teRte_SateliteStatus         Rte_Write_CtrlSwi_TgtValue_ScrollingSatelite_Param1;
extern tsRte_Hss3Status             Rte_Write_CtrlSwi_Hss3StatusErr_Param1;
extern tsRteCodingParameters        Rte_Read_CodM_CtrlFan_Para_Param1;
extern teRte_SysVolt_Results        Rte_Read_SysVolt_FanVoltRng0_sVoltRng_Param1;
extern tsRte_HssStatus              Rte_Read_CddSwi_SwitchStatus_Param1;
extern tsRte_SigPrep_ElecSupState   Rte_Read_SigPrep_ElecSupState_Param1;
extern tScrollingPresent_Stat       Rte_Read_CddSwi_ScrollingOn_Stat_Param1;
extern tsRte_SysMonLgtTiReq         Rte_Read_SysMon_StdLgtTi_Req_Param1;
extern boolean                      Rte_Read_Diag_TiScrollingTakeOver_Param1;
extern tsRteHssTarget               Rte_Read_CpmHssTarget0_sSetting_Param1;
extern tsRte_CpmHSS3Duty            Rte_Read_Cpm_CtrlSwi_HSS3Target_Param1;
extern uint32                       LPTMR0_GetTimeElapsed_Param1;
extern uint16                       Dem_SetEventStatus_Param1;
extern uint8	                      Dem_SetEventStatus_Param2;
extern tsRte_TgtAniArrScr           Rte_Read_AnimaScrollingActivation_Param1;
extern teRte_ScrollingTgt           Rte_Read_Diag_Scrolling_TgtValue_Param1;

//=============================================================================
// Stub function returned value stubs
//=============================================================================
extern Std_ReturnType               Rte_Write_CodM_CtrlFan_Para_RetVal;
extern Std_ReturnType               Rte_Write_CtrlSwi_TgtValue_Fan1_RetVal;
extern Std_ReturnType               Rte_Write_CtrlSwi_TgtValue_Fan2_RetVal;
extern Std_ReturnType               Rte_Write_CtrlSwi_HssStatus_RetVal;
extern Std_ReturnType               Rte_Write_CtrlSwi_StatusErr_RetVal;
extern Std_ReturnType               Rte_Write_CtrlSwi_TgtValue_ScrollingSatelite_RetVal;
extern Std_ReturnType               Rte_Write_CtrlSwi_Hss3StatusErr_RetVal;
extern Std_ReturnType               Rte_Read_CodM_CtrlFan_Para_RetVal;
extern Std_ReturnType               Rte_Read_SysVolt_FanVoltRng0_sVoltRng_RetVal;
extern Std_ReturnType               Rte_Read_CddSwi_SwitchStatus_RetVal;
extern Std_ReturnType               Rte_Read_SigPrep_ElecSupState_RetVal;
extern Std_ReturnType               Rte_Read_CddSwi_ScrollingOn_Stat_RetVal;
extern Std_ReturnType               Rte_Read_SysMon_StdLgtTi_Req_RetVal;
extern Std_ReturnType               Rte_Read_Diag_TiScrollingTakeOver_RetVal;
extern Std_ReturnType               Rte_Read_CpmHssTarget0_sSetting_RetVal;
extern Std_ReturnType               Rte_Read_Cpm_CtrlSwi_HSS3Target_RetVal;
extern Std_ReturnType               Rte_Read_AnimaScrollingActivation_RetVal;
extern Std_ReturnType               Rte_Read_Diag_Scrolling_TgtValue_RetVal;
extern uint32                       LPTMR0_GetTimeElapsed_RetVal;
extern uint8                        Dem_SetEventStatus_Retval;
extern uint8                        CtrlSwi_Get_ETAT_FEE_Ret_Val;
extern boolean                      CtrlSwi_DataValid_RetVal;
extern uint8                        Rte_Write_CtrlSwi_TgtValue_SMRGB_RetVal;
extern uint8                        CtrlSwi_ErrorTimers_RetVal;
extern boolean                      CtrlSwi_HandleMaturationTime_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================
extern uint8                        Rte_Write_CodM_CtrlFan_Para_HitCount;
extern uint8                        Rte_Write_CtrlSwi_TgtValue_Fan1_HitCount;
extern uint8                        Rte_Write_CtrlSwi_TgtValue_Fan2_HitCount;
extern uint8                        Rte_Write_CtrlSwi_HssStatus_HitCount;
extern uint8                        Rte_Write_CtrlSwi_TgtValue_Fan1_HitCount;
extern uint8                        Rte_Write_CtrlSwi_TgtValue_SMRGB_HitCount;
extern uint8                        Rte_Write_CtrlSwi_StatusErr_HitCount;
extern uint8                        Rte_Write_CtrlSwi_TgtValue_ScrollingSatelite_HitCount;
extern uint8                        Rte_Write_CtrlSwi_Hss3StatusErr_HitCount;
extern uint8                        Rte_Read_CodM_CtrlFan_Para_HitCount;
extern uint8                        Rte_Read_SysVolt_FanVoltRng0_sVoltRng_HitCount;
extern uint8                        Rte_Read_CddSwi_SwitchStatus_HitCount;
extern uint8                        Rte_Read_SigPrep_ElecSupState_HitCount;
extern uint8                        Rte_Read_CddSwi_ScrollingOn_Stat_HitCount;
extern uint8                        Rte_Read_SysMon_StdLgtTi_Req_HitCount;
extern uint8                        Rte_Read_Diag_TiScrollingTakeOver_HitCount;
extern uint8                        Rte_Read_CpmHssTarget0_sSetting_HitCount;
extern uint8                        Rte_Read_Cpm_CtrlSwi_HSS3Target_HitCount;
extern uint8                        LPTMR0_GetTimeElapsed_HitCount;
extern uint8                        Dem_SetEventStatus_HitCount;
extern uint8                        CtrlSwi_DataValid_Hit_Count;
extern uint8                        Rte_Read_AnimaScrollingActivation_Hit_Count;
extern uint8                        Rte_Read_Diag_Scrolling_TgtValue_HitCount;

//=============================================================================
// Stub function definitions
//=============================================================================
//-----------------------------------------------------------------------------
/// \brief Rte_Read_AnimaScrollingActivation
/// 
/// \descr  Stub function to simulate the behavoiur of Rte_Read_AnimaScrollingActivation
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_AnimaScrollingActivation(tsRte_TgtAniArrScr* ppara1)
{
  *ppara1 = Rte_Read_AnimaScrollingActivation_Param1;
  Rte_Read_AnimaScrollingActivation_Hit_Count++;
  return Rte_Read_AnimaScrollingActivation_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Read_Diag_TiScrollingTakeOver
/// 
/// \descr  Stub function to simulate the behavoiur of Rte_Read_Diag_TiScrollingTakeOver
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_Diag_TiScrollingTakeOver(boolean* ppara1)
{
  *ppara1 = Rte_Read_Diag_TiScrollingTakeOver_Param1;
  Rte_Read_Diag_TiScrollingTakeOver_HitCount++;
  return Rte_Read_Diag_TiScrollingTakeOver_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Read_CpmHssTarget0_sSetting
/// 
/// \descr  Stub function to simulate the behavoiur of Rte_Read_CpmHssTarget0_sSetting
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CpmHssTarget0_sSetting(tsRteHssTarget* ppara1)
{
  *ppara1 = Rte_Read_CpmHssTarget0_sSetting_Param1;
  Rte_Read_CpmHssTarget0_sSetting_HitCount++;
  return Rte_Read_CpmHssTarget0_sSetting_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Read_Cpm_CtrlSwi_HSS3Target
/// 
/// \descr  Stub function to simulate the behavoiur of Rte_Read_Cpm_CtrlSwi_HSS3Target
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_Cpm_CtrlSwi_HSS3Target(tsRte_CpmHSS3Duty* ppara1)
{
  *ppara1 = Rte_Read_Cpm_CtrlSwi_HSS3Target_Param1;
  Rte_Read_Cpm_CtrlSwi_HSS3Target_HitCount++;
  return Rte_Read_Cpm_CtrlSwi_HSS3Target_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Read_CodM_CtrlFan_Para
/// 
/// \descr  Stub function to simulate the behavoiur of Rte_Read_CodM_CtrlFan_Para
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CodM_CtrlFan_Para(tsRteCodingParameters* ppara1)
{
  *ppara1 = Rte_Read_CodM_CtrlFan_Para_Param1;
  Rte_Read_CodM_CtrlFan_Para_HitCount++;
  return Rte_Read_CodM_CtrlFan_Para_RetVal;

}

//-----------------------------------------------------------------------------
/// \brief Rte_Write_CodM_CtrlFan_Para
/// 
/// \descr  Stub function to simulate the behavoiur of Rte_Write_CodM_CtrlFan_Para
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CodM_CtrlFan_Para(const tsRteCodingParameters *ppara1)
{
  Rte_Write_CodM_CtrlFan_Para_Param1 = *ppara1;
  Rte_Write_CodM_CtrlFan_Para_HitCount++;
  return Rte_Write_CodM_CtrlFan_Para_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Write_CtrlSwi_TgtValue_Fan1
/// 
/// \descr  Stub function to simulate the behavoiur of Rte_Write_CtrlSwi_TgtValue_Fan1
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CtrlSwi_TgtValue_Fan1(const uint16 *ppara1)
{
  Rte_Write_CtrlSwi_TgtValue_Fan1_Param1 = *ppara1;
  Rte_Write_CtrlSwi_TgtValue_Fan1_HitCount++;
  return Rte_Write_CtrlSwi_TgtValue_Fan1_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Write_CtrlSwi_TgtValue_Fan2
/// 
/// \descr  Stub function to simulate the behavoiur of Rte_Write_CtrlSwi_TgtValue_Fan2
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CtrlSwi_TgtValue_Fan2(const uint16 *ppara1)
{
  Rte_Write_CtrlSwi_TgtValue_Fan2_Param1 = *ppara1;
  Rte_Write_CtrlSwi_TgtValue_Fan2_HitCount++;
  return Rte_Write_CtrlSwi_TgtValue_Fan2_RetVal;
}
//-----------------------------------------------------------------------------
/// \brief Rte_Write_CtrlSwi_HssStatus
/// 
/// \descr  Stub function to simulate the behavoiur of Rte_Write_CtrlSwi_HssStatus
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------

Std_ReturnType Rte_Write_CtrlSwi_HssStatus(const tRteCtrlSwi_ErrorFlags *ppara1)
{
  Rte_Write_CtrlSwi_HssStatus_Param1 = *ppara1;
  Rte_Write_CtrlSwi_HssStatus_HitCount++;
  return Rte_Write_CtrlSwi_HssStatus_RetVal;

}

//-----------------------------------------------------------------------------
/// \brief Rte_Write_CtrlSwi_TgtValue_SMRGB
/// 
/// \descr  Stub function to simulate the behavoiur of Rte_Write_CtrlSwi_TgtValue_SMRGB
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CtrlSwi_TgtValue_SMRGB(const tRteSwitchTgtVal* ppara1)
{
  Rte_Write_CtrlSwi_TgtValue_SMRGB_Param1 = *ppara1;
  Rte_Write_CtrlSwi_TgtValue_SMRGB_HitCount++;
  return Rte_Write_CtrlSwi_TgtValue_SMRGB_RetVal;

}

//-----------------------------------------------------------------------------
/// \brief Rte_Write_CtrlSwi_StatusErr
/// 
/// \descr  Stub function to simulate the behavoiur of Rte_Write_CtrlSwi_StatusErr
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CtrlSwi_StatusErr(const tisHssStatusError* ppara1)
{
  Rte_Write_CtrlSwi_StatusErr_Param1 = *ppara1;
  Rte_Write_CtrlSwi_StatusErr_HitCount++;
  return Rte_Write_CtrlSwi_StatusErr_RetVal;

}

//-----------------------------------------------------------------------------
/// \brief Rte_Read_SysVolt_FanVoltRng0_sVoltRng
/// 
/// \descr  Stub function to simulate the behavoiur of Rte_Read_SysVolt_FanVoltRng0_sVoltRng
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------

Std_ReturnType Rte_Read_SysVolt_FanVoltRng0_sVoltRng(teRte_SysVolt_Results *ppara1)
{
  *ppara1 = Rte_Read_SysVolt_FanVoltRng0_sVoltRng_Param1;
  Rte_Read_SysVolt_FanVoltRng0_sVoltRng_HitCount++;
  return Rte_Read_SysVolt_FanVoltRng0_sVoltRng_RetVal;

}
//-----------------------------------------------------------------------------
/// \brief Rte_Read_CddSwi_SwitchStatus
/// 
/// \descr  Stub function to simulate the behavoiur of Rte_Read_CddSwi_SwitchStatu
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CddSwi_SwitchStatus(tsRte_HssStatus *ppara1)
{
  *ppara1 = Rte_Read_CddSwi_SwitchStatus_Param1;
  Rte_Read_CddSwi_SwitchStatus_HitCount++;
  return Rte_Read_CddSwi_SwitchStatus_RetVal;

}
//-----------------------------------------------------------------------------
/// \brief Rte_Read_SigPrep_ElecSupState
/// 
/// \descr  Stub function to simulate the behavoiur of Rte_Read_SigPrep_ElecSupState
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------

Std_ReturnType Rte_Read_SigPrep_ElecSupState(tsRte_SigPrep_ElecSupState *ppara1)
{
  *ppara1 = Rte_Read_SigPrep_ElecSupState_Param1;
  Rte_Read_SigPrep_ElecSupState_HitCount++;
  return Rte_Read_SigPrep_ElecSupState_RetVal;
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
/// \brief  CddEft_DataValid
///
/// \descr  Stub function created to simulate the behaviour of CddEft_DataValid
///
///
/// \return CddEft_DataValid_RetVal
//-----------------------------------------------------------------------------
boolean CddEft_DataValid(void)
{
  CtrlSwi_DataValid_Hit_Count++;

  return CtrlSwi_DataValid_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CtrlSwi_TgtValue_ScrollingSatelite
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CtrlSwi_TgtValue_ScrollingSatelite
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CtrlSwi_TgtValue_ScrollingSatelite(const teRte_SateliteStatus* ppara1)
{
  Rte_Write_CtrlSwi_TgtValue_ScrollingSatelite_Param1 = *ppara1;
  Rte_Write_CtrlSwi_TgtValue_ScrollingSatelite_HitCount++;
  return Rte_Write_CtrlSwi_TgtValue_ScrollingSatelite_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CddSwi_ScrollingOn_Stat
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CddSwi_ScrollingOn_Stat
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CddSwi_ScrollingOn_Stat(tScrollingPresent_Stat* ppara1)
{
  *ppara1 = Rte_Read_CddSwi_ScrollingOn_Stat_Param1;
  Rte_Read_CddSwi_ScrollingOn_Stat_HitCount++;
  return Rte_Read_CddSwi_ScrollingOn_Stat_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SysMon_StdLgtTi_Req
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SysMon_StdLgtTi_Req
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SysMon_StdLgtTi_Req(tsRte_SysMonLgtTiReq* ppara1)
{
  *ppara1 = Rte_Read_SysMon_StdLgtTi_Req_Param1;
  Rte_Read_SysMon_StdLgtTi_Req_HitCount++;
  return Rte_Read_SysMon_StdLgtTi_Req_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Write_CtrlSwi_Hss3StatusErr
/// 
/// \descr  Stub function to simulate the behavoiur of Rte_Write_CtrlSwi_Hss3StatusErr
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CtrlSwi_Hss3StatusErr(const tsRte_Hss3Status *ppara1)
{
  Rte_Write_CtrlSwi_Hss3StatusErr_Param1 = *ppara1;
  Rte_Write_CtrlSwi_Hss3StatusErr_HitCount++;
  return Rte_Write_CtrlSwi_Hss3StatusErr_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Read_Diag_Scrolling_TgtValue
/// 
/// \descr  Stub function to simulate the behavoiur of Rte_Read_Diag_Scrolling_TgtValue
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_Diag_Scrolling_TgtValue(teRte_ScrollingTgt* ppara1)
{
  *ppara1 = Rte_Read_Diag_Scrolling_TgtValue_Param1;
  Rte_Read_Diag_Scrolling_TgtValue_HitCount++;
  return Rte_Read_Diag_Scrolling_TgtValue_RetVal;
}

// EOF
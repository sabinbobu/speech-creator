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

tsRteCodingParameters   Rte_Write_CodM_Anima_Para_Param1;
tsRteCodingParameters   Rte_Write_CodM_IoHwAbUser_Para_Param1;
tsRteCodingParameters   Rte_Write_CodM_FctR_Para_Param1;
tsRteCodingParameters   Rte_Write_CodM_SysMon_Para_Param1;
tsRteCodingParameters   Rte_Write_CodM_CddSwi_Para_Param1;
tsRteCodingParameters   Rte_Write_CodM_CddLed_Para_Param1;
tsRteCodingParameters   Rte_Write_CodM_SysVolt_Para_Param1;
tsRteCodingParameters   Rte_Write_CodM_CtrlFan_Para_Param1;
tsRteCodingParameters   Rte_Write_CodM_Rsens_Para_Param1;
tsRteCodingParameters   Rte_Write_CodM_CtrlLed_Para_Param1;
tsRteCodingParameters   Rte_Write_CodM_AppM_Para_Param1;
tsRteCodingParameters   Rte_Write_CodM_Dbl_Para_Param1;
tsRteCodingParameters   Rte_Write_CodM_CddMlc_Para_Param1;
tsRteCodingParameters   Rte_Write_CodM_CtrlPxl_Para_Param1;
tsRteCodingParameters   Rte_Write_CodM_CddStp_Para_Param1;
tsRteCodingParameters   Rte_Write_CodM_CtrlStp_Para_Param1;
tsRteCodingParameters   Rte_Write_CodM_Adb_Mxb_Para_Param1;
tsRteCodingParameters   Rte_Write_CodM_Adb_Pxa_Para_Param1;
tsRteCodingParameters   Rte_Write_CodM_Pitch_Para_Param1;
tsRteCodingParameters   Rte_Write_CodM_CddBoost_Para_Param1;
tsRteCodingParameters   Rte_Write_CodM_SigPrep_Para_Param1;
tsRteCodingParameters   Rte_Write_CodM_Err_Para_Param1;
tsSysCrc_CalibGetStatus SysCrc_RomSegs_GetCalibState_Param1;
boolean                 Dem_Set_Init_Window_Param1;
uint16                  Dem_SetEventStatus_Param1;
uint8                   Dem_SetEventStatus_Param2;

//=============================================================================
// Stub function returned value stubs
//=============================================================================

boolean CddEft_DataValid_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================

uint8 Rte_Write_CodM_Anima_Para_HitCount;
uint8 Rte_Write_CodM_IoHwAbUser_Para_HitCount;
uint8 Rte_Write_CodM_FctR_Para_HitCount;
uint8 Rte_Write_CodM_SysMon_Para_HitCount;
uint8 Rte_Write_CodM_CddSwi_Para_HitCount;
uint8 Rte_Write_CodM_CddLed_Para_HitCount;
uint8 Rte_Write_CodM_SysVolt_Para_HitCount;
uint8 Rte_Write_CodM_CtrlFan_Para_HitCount;
uint8 Rte_Write_CodM_Rsens_Para_HitCount;
uint8 Rte_Write_CodM_CtrlLed_Para_HitCount;
uint8 Rte_Write_CodM_AppM_Para_HitCount;
uint8 Rte_Write_CodM_CddBoost_Para_HitCount;
uint8 Rte_Write_CodM_Dbl_Para_HitCount;
uint8 Rte_Write_CodM_CddMlc_Para_HitCount;
uint8 Rte_Write_CodM_CtrlPxl_Para_HitCount;
uint8 Rte_Write_CodM_CddStp_Para_HitCount;
uint8 Rte_Write_CodM_CtrlStp_Para_HitCount;
uint8 Rte_Write_CodM_Adb_Mxb_Para_HitCount;
uint8 Rte_Write_CodM_Adb_Pxa_Para_HitCount;
uint8 Rte_Write_CodM_Pitch_Para_HitCount;
uint8 Rte_Write_CodM_SigPrep_Para_HitCount;
uint8 Rte_Write_CodM_Err_Para_HitCount;
uint8 SysCrc_RomSegs_GetCalibState_HitCount;
uint8 CddEft_DataValid_Hit_Count;
uint8 Dem_SetEventStatus_HitCount;
uint8 Dem_Set_Init_Window_HitCount;

//=============================================================================
// Stub function definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CodM_Dbl_Para
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CodM_Dbl_Para
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CodM_Dbl_Para(const tsRteCodingParameters* ppara1)
{
  Rte_Write_CodM_Dbl_Para_Param1 = *ppara1;
  Rte_Write_CodM_Dbl_Para_HitCount++;
}
//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CodM_CddMlc_Para
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CodM_CddMlc_Para
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CodM_CddMlc_Para(const tsRteCodingParameters* ppara1)
{
  Rte_Write_CodM_CddMlc_Para_Param1 = *ppara1;
  Rte_Write_CodM_CddMlc_Para_HitCount++;
}
//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CodM_CtrlPxl_Para
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CodM_CtrlPxl_Para
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CodM_CtrlPxl_Para(const tsRteCodingParameters* ppara1)
{
  Rte_Write_CodM_CtrlPxl_Para_Param1 = *ppara1;
  Rte_Write_CodM_CtrlPxl_Para_HitCount++;
}
//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CodM_CddStp_Para
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CodM_CddStp_Para
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CodM_CddStp_Para(const tsRteCodingParameters* ppara1)
{
  Rte_Write_CodM_CddStp_Para_Param1 = *ppara1;
  Rte_Write_CodM_CddStp_Para_HitCount++;
}
//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CodM_CtrlStp_Para
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CodM_CtrlStp_Para
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CodM_CtrlStp_Para(const tsRteCodingParameters* ppara1)
{
  Rte_Write_CodM_CtrlStp_Para_Param1 = *ppara1;
  Rte_Write_CodM_CtrlStp_Para_HitCount++;
}
//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CodM_Adb_Mxb_Para
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CodM_Adb_Mxb_Para
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CodM_Adb_Mxb_Para(const tsRteCodingParameters* ppara1)
{
  Rte_Write_CodM_Adb_Mxb_Para_Param1 = *ppara1;
  Rte_Write_CodM_Adb_Mxb_Para_HitCount++;
}
//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CodM_Adb_Pxa_Para
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CodM_Adb_Pxa_Para
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CodM_Adb_Pxa_Para(const tsRteCodingParameters* ppara1)
{
  Rte_Write_CodM_Adb_Pxa_Para_Param1 = *ppara1;
  Rte_Write_CodM_Adb_Pxa_Para_HitCount++;
}
//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CodM_Pitch_Para
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CodM_Pitch_Para
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CodM_Pitch_Para(const tsRteCodingParameters* ppara1)
{
  Rte_Write_CodM_Pitch_Para_Param1 = *ppara1;
  Rte_Write_CodM_Pitch_Para_HitCount++;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CodM_AppM_Para
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CodM_AppM_Para
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CodM_AppM_Para(const tsRteCodingParameters* ppara1)
{
  Rte_Write_CodM_AppM_Para_Param1 = *ppara1;
  Rte_Write_CodM_AppM_Para_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CodM_CtrlLed_Para
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CodM_CtrlLed_Para
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CodM_CtrlLed_Para(const tsRteCodingParameters* ppara1)
{
  Rte_Write_CodM_CtrlLed_Para_Param1 = *ppara1;
  Rte_Write_CodM_CtrlLed_Para_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CodM_Rsens_Para
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CodM_Rsens_Para
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CodM_Rsens_Para(const tsRteCodingParameters* ppara1)
{
  Rte_Write_CodM_Rsens_Para_Param1 = *ppara1;
  Rte_Write_CodM_Rsens_Para_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CodM_CtrlFan_Para
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CodM_CtrlFan_Para
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CodM_CtrlFan_Para(const tsRteCodingParameters* ppara1)
{
  Rte_Write_CodM_CtrlFan_Para_Param1 = *ppara1;
  Rte_Write_CodM_CtrlFan_Para_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CodM_SysVolt_Para
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CodM_SysVolt_Para
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CodM_SysVolt_Para(const tsRteCodingParameters* ppara1)
{
  Rte_Write_CodM_SysVolt_Para_Param1 = *ppara1;
  Rte_Write_CodM_SysVolt_Para_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CodM_CddLed_Para
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CodM_CddLed_Para
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CodM_CddLed_Para(const tsRteCodingParameters* ppara1)
{
  Rte_Write_CodM_CddLed_Para_Param1 = *ppara1;
  Rte_Write_CodM_CddLed_Para_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CodM_CddSwi_Para
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CodM_CddSwi_Para
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CodM_CddSwi_Para(const tsRteCodingParameters* ppara1)
{
  Rte_Write_CodM_CddSwi_Para_Param1 = *ppara1;
  Rte_Write_CodM_CddSwi_Para_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CodM_CddBoost_Para
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CodM_CddBoost_Para
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CodM_CddBoost_Para(tsRteCodingParameters* ppara1)
{
  Rte_Write_CodM_CddBoost_Para_Param1 = *ppara1;
  Rte_Write_CodM_CddBoost_Para_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CodM_SysMon_Para
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CodM_SysMon_Para
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CodM_SysMon_Para(const tsRteCodingParameters* ppara1)
{
  Rte_Write_CodM_SysMon_Para_Param1 = *ppara1;
  Rte_Write_CodM_SysMon_Para_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CodM_FctR_Para
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CodM_FctR_Para
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CodM_FctR_Para(const tsRteCodingParameters* ppara1)
{
  Rte_Write_CodM_FctR_Para_Param1 = *ppara1;
  Rte_Write_CodM_FctR_Para_HitCount++;
  //return E_OK;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CodM_Anima_Para
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CodM_Anima_Para
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CodM_Anima_Para(const tsRteCodingParameters* ppara1)
{
  Rte_Write_CodM_Anima_Para_Param1 = *ppara1;
  Rte_Write_CodM_Anima_Para_HitCount++;
  //return E_OK;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CodM_IoHwAbUser_Para
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CodM_IoHwAbUser_Para
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CodM_IoHwAbUser_Para(const tsRteCodingParameters* ppara1)
{
  Rte_Write_CodM_IoHwAbUser_Para_Param1 = *ppara1;
  Rte_Write_CodM_IoHwAbUser_Para_HitCount++;
  //return E_OK;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CodM_SigPrep_Para
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CodM_SigPrep_Para
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CodM_SigPrep_Para(const tsRteCodingParameters* ppara1)
{
  Rte_Write_CodM_SigPrep_Para_Param1 = *ppara1;
  Rte_Write_CodM_SigPrep_Para_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CodM_Err_Para
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CodM_Err_Para
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CodM_Err_Para(const tsRteCodingParameters* ppara1)
{
  Rte_Write_CodM_Err_Para_Param1 = *ppara1;
  Rte_Write_CodM_Err_Para_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  SysCrc_RomSegs_GetCalibState
///
/// \descr  Stub function created to simulate the behaviour of SysCrc_RomSegs_GetCalibState
///
/// \param  psCalibState
///
/// \return void
//-----------------------------------------------------------------------------
void SysCrc_RomSegs_GetCalibState(tsSysCrc_CalibGetStatus *psCalibState)
{
  *psCalibState = SysCrc_RomSegs_GetCalibState_Param1;
  SysCrc_RomSegs_GetCalibState_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  CddEft_DataValid
///
/// \descr  Stub function created to simulate the behaviour of CddEft_DataValid
///
/// \param  void
///
/// \return CddEft_DataValid_RetVal
//-----------------------------------------------------------------------------
boolean CddEft_DataValid(void)
{
  CddEft_DataValid_Hit_Count++;

  return CddEft_DataValid_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Dem_Set_Init_Window
///
/// \descr  Stub function created to simulate the behaviour of Dem_Set_Init_Window
///
/// \param  Dem_Set_Init_Window_Param1
///
/// \return void
//-----------------------------------------------------------------------------
void  Dem_Set_Init_Window(boolean boWindow)
{
  Dem_Set_Init_Window_Param1 = boWindow;
  Dem_Set_Init_Window_HitCount++;
};


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
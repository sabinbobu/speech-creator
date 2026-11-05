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
// Global variable stubs
//=============================================================================
tNvmPara_CodingArea           Coding_Dummy = { 0u };
tParaFct0_Cmd                 Coding_State = eParaFct0_CodingDataInvalid;

//=============================================================================
// Stub function parameter stubs
//=============================================================================
tsRteCodingParameters     Rte_Read_CodM_CddMlc_Para_Param1;
tsRte_MatrixEE0peration   Rte_Read_CtrlPxl_MatrixEE_DataRead_Param1;
tsRte_MatrixEE0peration   Rte_Read_CtrlPxl_MatrixEE_DataWrite_Param1;
tsRte_MatrixEE0CbkFn      Rte_Read_CtrlPxl_MatrixEE_CbkInitData_Param1;
teRte_VccxLineState       Rte_Read_IoHwAbUser_VccxLineState_Param1;

tsRte_CddMlcComStatus     Rte_Write_CtrlPxl_CddMlc_ComStatus_sVal_Param1;
tasRte_MlcLedStatus       Rte_Write_CtrlPxl_CddMlc_LedStatus_aVal_Param1;
tasRte_MlcAdcResult       Rte_Write_CtrlPxl_CddMlc_AdcResult_aVal_Param1;
boolean                   Rte_Write_CtrlPxl_CddMlc_ReinitMatrix_Param1;
tsRte_MlcComErrorStatus   Rte_Write_CtrlPxl_CddMlc_CrcError_sVal_Param1;
teRte_CddMlc_SystemMode   Rte_Write_CtrlPxl_CddMlc_SystemMode_eVal_Param1;


//=============================================================================
// Stub function returned value stubs
//=============================================================================
Std_ReturnType Rte_Read_CodM_CddMlc_Para_RetVal;
Std_ReturnType Rte_Read_CtrlPxl_MatrixEE_DataRead_RetVal;
Std_ReturnType Rte_Read_CtrlPxl_MatrixEE_DataWrite_RetVal;
Std_ReturnType Rte_Read_CtrlPxl_MatrixEE_CbkInitData_RetVal;
Std_ReturnType Rte_Read_IoHwAbUser_VccxLineState_RetVal;

Std_ReturnType Rte_Write_CtrlPxl_CddMlc_ComStatus_sVal_RetVal;
Std_ReturnType Rte_Write_CtrlPxl_CddMlc_LedStatus_aVal_RetVal;
Std_ReturnType Rte_Write_CtrlPxl_CddMlc_AdcResult_aVal_RetVal;
Std_ReturnType Rte_Write_CtrlPxl_CddMlc_ReinitMatrix_RetVal;
Std_ReturnType Rte_Write_CtrlPxl_CddMlc_CrcError_sVal_RetVal;
Std_ReturnType Rte_Write_CtrlPxl_CddMlc_SystemMode_eVal_RetVal;


//=============================================================================
// Stub function hit count variables
//=============================================================================
uint8 Rte_Read_CodM_CddMlc_Para_HitCount;
uint8 Rte_Read_CtrlPxl_MatrixEE_DataRead_HitCount;
uint8 Rte_Read_CtrlPxl_MatrixEE_DataWrite_HitCount;
uint8 Rte_Read_CtrlPxl_MatrixEE_CbkInitData_HitCount;
uint8 Rte_Read_IoHwAbUser_VccxLineState_HitCount;

uint8 Rte_Write_CtrlPxl_CddMlc_ComStatus_sVal_HitCount;
uint8 Rte_Write_CtrlPxl_CddMlc_LedStatus_aVal_HitCount;
uint8 Rte_Write_CtrlPxl_CddMlc_AdcResult_aVal_HitCount;
uint8 Rte_Write_CtrlPxl_CddMlc_ReinitMatrix_HitCount;
uint8 Rte_Write_CtrlPxl_CddMlc_CrcError_sVal_HitCount;
uint8 Rte_Write_CtrlPxl_CddMlc_SystemMode_eVal_HitCount;


//=============================================================================
// Stub function definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CodM_CddMlc_Para
///
/// \descr  Stub function to simulate the behavior of Rte_Read_CodM_CddMlc_Para
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CodM_CddMlc_Para(tsRteCodingParameters* ppara1)
{
  *ppara1 = Rte_Read_CodM_CddMlc_Para_Param1;
  Rte_Read_CodM_CddMlc_Para_HitCount++;
  return Rte_Read_CodM_CddMlc_Para_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlPxl_MatrixEE_DataRead
///
/// \descr Stub function created to simulate the behaviour of Rte_Read_CtrlPxl_MatrixEE_DataRead
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Read_CtrlPxl_MatrixEE_DataRead(tsRte_MatrixEE0peration* ppara1)
{
  *ppara1 = Rte_Read_CtrlPxl_MatrixEE_DataRead_Param1;
  Rte_Read_CtrlPxl_MatrixEE_DataRead_HitCount++;

  return Rte_Read_CtrlPxl_MatrixEE_DataRead_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlPxl_MatrixEE_DataWrite
///
/// \descr Stub function created to simulate the behaviour of Rte_Read_CtrlPxl_MatrixEE_DataWrite
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Read_CtrlPxl_MatrixEE_DataWrite(tsRte_MatrixEE0peration* ppara1)
{
  *ppara1 = Rte_Read_CtrlPxl_MatrixEE_DataWrite_Param1;
  Rte_Read_CtrlPxl_MatrixEE_DataWrite_HitCount++;

  return Rte_Read_CtrlPxl_MatrixEE_DataWrite_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlPxl_MatrixEE_CbkInitData
///
/// \descr Stub function created to simulate the behaviour of Rte_Read_CtrlPxl_MatrixEE_CbkInitData
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Read_CtrlPxl_MatrixEE_CbkInitData(tsRte_MatrixEE0CbkFn* ppara1)
{
  *ppara1 = Rte_Read_CtrlPxl_MatrixEE_CbkInitData_Param1;
  Rte_Read_CtrlPxl_MatrixEE_CbkInitData_HitCount++;

  return Rte_Read_CtrlPxl_MatrixEE_CbkInitData_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CtrlPxl_CddMlc_ComStatus_sVal
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CtrlPxl_CddMlc_ComStatus_sVal
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Write_CtrlPxl_CddMlc_ComStatus_sVal(const tsRte_CddMlcComStatus* ppara1)
{
  Rte_Write_CtrlPxl_CddMlc_ComStatus_sVal_Param1 = *ppara1;
  Rte_Write_CtrlPxl_CddMlc_ComStatus_sVal_HitCount++;

  return Rte_Write_CtrlPxl_CddMlc_ComStatus_sVal_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CtrlPxl_CddMlc_LedStatus_aVal
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CtrlPxl_CddMlc_LedStatus_aVal
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Write_CtrlPxl_CddMlc_LedStatus_aVal(const tasRte_MlcLedStatus* ppara1)
{
  uint16* psRteData = (uint16*)ppara1;

  for (uint32 ulIdx = 0u; ulIdx < sizeof(tasRte_MlcLedStatus)/sizeof(tsRte_CddMlc_LedStatus); ulIdx++)
  {
    Rte_Write_CtrlPxl_CddMlc_LedStatus_aVal_Param1[ulIdx].unLedFault = *psRteData++;
  }
  Rte_Write_CtrlPxl_CddMlc_LedStatus_aVal_HitCount++;

  return Rte_Write_CtrlPxl_CddMlc_LedStatus_aVal_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CtrlPxl_CddMlc_AdcResult_aVal
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CtrlPxl_CddMlc_AdcResult_aVal
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Write_CtrlPxl_CddMlc_AdcResult_aVal(const tasRte_MlcAdcResult* ppara1)
{
  tsRte_CddMlc_AdcResult* psRteData = (tsRte_CddMlc_AdcResult*)ppara1;

  for (uint32 ulIdx = 0u; ulIdx < sizeof(tasRte_MlcAdcResult)/sizeof(tsRte_CddMlc_AdcResult); ulIdx++)
  {
    Rte_Write_CtrlPxl_CddMlc_AdcResult_aVal_Param1[ulIdx] = *psRteData++;
  }
  Rte_Write_CtrlPxl_CddMlc_AdcResult_aVal_HitCount++;

  return Rte_Write_CtrlPxl_CddMlc_AdcResult_aVal_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CtrlPxl_CddMlc_ReinitMatrix
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CtrlPxl_CddMlc_ReinitMatrix
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CtrlPxl_CddMlc_ReinitMatrix(const boolean* ppara1)
{
  Rte_Write_CtrlPxl_CddMlc_ReinitMatrix_Param1 = *ppara1;
  Rte_Write_CtrlPxl_CddMlc_ReinitMatrix_HitCount++;

  return Rte_Write_CtrlPxl_CddMlc_ReinitMatrix_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CtrlPxl_CddMlc_CrcError_sVal
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CtrlPxl_CddMlc_CrcError_sVal
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Write_CtrlPxl_CddMlc_CrcError_sVal(const tsRte_MlcComErrorStatus* ppara1)
{

  for (uint32 ulIdx = 0u; ulIdx < sizeof(tsRte_MlcComErrorStatus) / sizeof(uint8); ulIdx++)
  {
    *((uint8*)(void*)&Rte_Write_CtrlPxl_CddMlc_CrcError_sVal_Param1 + ulIdx) = *((uint8*)(void*)ppara1 + ulIdx);
  }
  Rte_Write_CtrlPxl_CddMlc_CrcError_sVal_HitCount++;

  return Rte_Write_CtrlPxl_CddMlc_CrcError_sVal_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CtrlPxl_CddMlc_SystemMode_eVal
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CtrlPxl_CddMlc_SystemMode_eVal
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Write_CtrlPxl_CddMlc_SystemMode_eVal(const teRte_CddMlc_SystemMode* ppara1)
{
  Rte_Write_CtrlPxl_CddMlc_SystemMode_eVal_Param1 = *ppara1;
  Rte_Write_CtrlPxl_CddMlc_SystemMode_eVal_HitCount++;

  return Rte_Write_CtrlPxl_CddMlc_SystemMode_eVal_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_IoHwAbUser_VccxLineState
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_IoHwAbUser_VccxLineState
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Read_IoHwAbUser_VccxLineState(teRte_VccxLineState* ppara1)
{
  *ppara1 = Rte_Read_IoHwAbUser_VccxLineState_Param1;
  Rte_Read_IoHwAbUser_VccxLineState_HitCount++;

  return Rte_Read_IoHwAbUser_VccxLineState_RetVal;
}
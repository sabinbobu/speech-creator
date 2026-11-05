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
// Global variable stubs
//=============================================================================

tNvmPara_CodingArea           Coding_Dummy = { 0u };
tParaFct0_Cmd                 Coding_State = eParaFct0_CodingDataInvalid;

//=============================================================================
// Stub function parameter stubs
//=============================================================================

tsRteCodingParameters       Rte_Read_CodM_CtrlPxl_Para_Param1;
teRte_MountingSide          Rte_Read_IoHwAbUser_GetMountingSide_Param1;
tsRte_CddMlcComStatus       Rte_Read_CtrlPxl_CddMlc_ComStatus_sVal_Param1;
tasRte_MlcLedStatus         Rte_Read_CtrlPxl_CddMlc_LedStatus_aVal_Param1;
tsRte_MlcComErrorStatus     Rte_Read_CtrlPxl_CddMlc_CrcError_sVal_Param1;
teRte_VccxLineState         Rte_Read_IoHwAbUser_VccxLineState_Param1;
tsRte_TgtPxlSig0Arr         Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_Param1;
                            
tsRte_TgtMtxPixels_sVal     Rte_Write_CtrlPxl_TgtMtxPixels_sVal_Param1;
tsRte_MatrixFaultStates     Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState_Param1;
tauRte_CtrlPxl_Mtx_bErr     Rte_Write_CtrlPxl_CtrlLed_Matrix_bErr_aVal_Param1;
uint8                       Rte_Write_CtrlPxl_CddMlc_SysCtrlCommand_Param1;
tsRte_ucActualPxlPWM        Rte_Write_CtrlPxl_ActualPxlPWM_Param1;
tsRte_boMtxSegmentFault     Rte_Write_CtrlPxl_ActualPxlError_Param1;
tsRte_MtxEeprom_ErrStatus   Rte_Write_CtrlPxl_MtxEeprom_ErrorStatus_Param1;
tasRte_CtrlPxl_BinEEprom    Rte_Write_CtrlPxl_CtrlLed_EepromBinningClass_aVal_Param1;
tsRte_MatrixEE0CbkFn        Rte_Write_CtrlPxl_MatrixEE_CbkInitData_Param1;
tsRte_MatrixEE0peration     Rte_Write_CtrlPxl_MatrixEE_DataRead_Param1;
tsRte_MatrixEE0peration     Rte_Write_CtrlPxl_MatrixEE_DataWrite_Param1;
tsRte_NvMBlock              Rte_Write_CtrlPxl_Nvm_WriteData_Param1;
boolean                     Rte_Write_CtrlPxl_CddMlc_ReinitMatrix_Param1;

uint32                      LPTMR0_GetTimeElapsed_Param1;
uint8*                      Crc_CalculateCRC8H1D_Param1;
uint32                      Crc_CalculateCRC8H1D_Param2;
uint8                       Crc_CalculateCRC8H1D_Param3;
uint8                       UtilMemCopy_Input_Param1;
uint8                       UtilMemCopy_Input_Param2;
uint16_least                UtilMemCopy_Input_Param3;                     
uint8                       UtilMemCopy_Output_Param1[256];
uint8                       UtilMemCopy_Output_Param2[256];

//=============================================================================
// Stub function returned value stubs
//=============================================================================

Std_ReturnType  Rte_Read_CodM_CtrlPxl_Para_RetVal;
Std_ReturnType  Rte_Read_IoHwAbUser_GetMountingSide_RetVal;
Std_ReturnType  Rte_Read_CtrlPxl_CddMlc_ComStatus_sVal_RetVal;
Std_ReturnType  Rte_Read_CtrlPxl_CddMlc_LedStatus_aVal_RetVal;
Std_ReturnType  Rte_Read_CtrlPxl_CddMlc_CrcError_sVal_RetVal;
Std_ReturnType  Rte_Read_IoHwAbUser_VccxLineState_RetVal;
Std_ReturnType  Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_RetVal;

Std_ReturnType  Rte_Write_CtrlPxl_TgtMtxPixels_sVal_RetVal;
Std_ReturnType  Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState_RetVal;
Std_ReturnType  Rte_Write_CtrlPxl_CtrlLed_Matrix_bErr_aVal_RetVal;
Std_ReturnType  Rte_Write_CtrlPxl_CddMlc_SysCtrlCommand_RetVal;
Std_ReturnType  Rte_Write_CtrlPxl_ActualPxlPWM_RetVal;
Std_ReturnType  Rte_Write_CtrlPxl_ActualPxlError_RetVal;
Std_ReturnType  Rte_Write_CtrlPxl_MtxEeprom_ErrorStatus_RetVal;
Std_ReturnType  Rte_Write_CtrlPxl_CtrlLed_EepromBinningClass_aVal_RetVal;
Std_ReturnType  Rte_Write_CtrlPxl_MatrixEE_CbkInitData_RetVal;
Std_ReturnType  Rte_Write_CtrlPxl_MatrixEE_DataRead_RetVal;
Std_ReturnType  Rte_Write_CtrlPxl_MatrixEE_DataWrite_RetVal;
Std_ReturnType  Rte_Write_CtrlPxl_Nvm_WriteData_RetVal;
Std_ReturnType  Rte_Write_CtrlPxl_CddMlc_ReinitMatrix_RetVal;

uint32          LPTMR0_GetTimeElapsed_RetVal;
uint8           Crc_CalculateCRC8H1D_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================

uint8   Rte_Read_CodM_CtrlPxl_Para_HitCount;
uint8   Rte_Read_IoHwAbUser_GetMountingSide_HitCount;
uint8   Rte_Read_CtrlPxl_CddMlc_ComStatus_sVal_HitCount;
uint8   Rte_Read_CtrlPxl_CddMlc_LedStatus_aVal_HitCount;
uint8   Rte_Read_CtrlPxl_CddMlc_CrcError_sVal_HitCount;
uint8   Rte_Read_IoHwAbUser_VccxLineState_HitCount;
uint8   Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_HitCount;

uint8   Rte_Write_CtrlPxl_TgtMtxPixels_sVal_HitCount;
uint8   Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState_HitCount;
uint8   Rte_Write_CtrlPxl_CtrlLed_Matrix_bErr_aVal_HitCount;
uint8   Rte_Write_CtrlPxl_CddMlc_SysCtrlCommand_HitCount;
uint8   Rte_Write_CtrlPxl_ActualPxlPWM_HitCount;
uint8   Rte_Write_CtrlPxl_ActualPxlError_HitCount;
uint8   Rte_Write_CtrlPxl_MtxEeprom_ErrorStatus_HitCount;
uint8   Rte_Write_CtrlPxl_CtrlLed_EepromBinningClass_aVal_HitCount;
uint8   Rte_Write_CtrlPxl_MatrixEE_CbkInitData_HitCount;
uint8   Rte_Write_CtrlPxl_MatrixEE_DataRead_HitCount;
uint8   Rte_Write_CtrlPxl_MatrixEE_DataWrite_HitCount;
uint8   Rte_Write_CtrlPxl_Nvm_WriteData_HitCount;
uint8   Rte_Write_CtrlPxl_CddMlc_ReinitMatrix_HitCount;

uint8   LPTMR0_GetTimeElapsed_HitCount;
uint8   Crc_CalculateCRC8H1D_HitCount;
uint8   UtilMemCopy_HitCount;


//=============================================================================
// Stub function definitions
//=============================================================================

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
/// \brief  Rte_Read_CodM_CtrlPxl_Para
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CodM_CtrlPxl_Para
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CodM_CtrlPxl_Para(tsRteCodingParameters* ppara1)
{
  Rte_Read_CodM_CtrlPxl_Para_Param1.eCodingState              = Coding_State;
  Rte_Read_CodM_CtrlPxl_Para_Param1.psCodingParameters_Blocks = &Coding_Dummy;
  *ppara1 = Rte_Read_CodM_CtrlPxl_Para_Param1;

  Rte_Read_CodM_CtrlPxl_Para_HitCount++;

  return Rte_Read_CodM_CtrlPxl_Para_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlPxl_CddMlc_ComStatus_sVal
///
/// \descr  Stub function to simulate the behavoiur of Rte_Read_CtrlPxl_CddMlc_ComStatus_sVal
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CtrlPxl_CddMlc_ComStatus_sVal(tsRte_CddMlcComStatus* ppara1)
{
  *ppara1 = Rte_Read_CtrlPxl_CddMlc_ComStatus_sVal_Param1;
  Rte_Read_CtrlPxl_CddMlc_ComStatus_sVal_HitCount++;

  return Rte_Read_CtrlPxl_CddMlc_ComStatus_sVal_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlPxl_CddMlc_LedStatus_aVal
///
/// \descr  Stub function to simulate the behavoiur of Rte_Read_CtrlPxl_CddMlc_LedStatus_aVal
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CtrlPxl_CddMlc_LedStatus_aVal(tasRte_MlcLedStatus* ppara1)
{
  for (uint32 ulIdx = 0u; ulIdx < sizeof(tasRte_MlcLedStatus)/sizeof(tsRte_CddMlc_LedStatus); ulIdx++)
  {
    *((uint8*)(void*)ppara1 + ulIdx) = *((uint8*)(void*)&Rte_Read_CtrlPxl_CddMlc_LedStatus_aVal_Param1 + ulIdx);
  }
  Rte_Read_CtrlPxl_CddMlc_LedStatus_aVal_HitCount++;

  return Rte_Read_CtrlPxl_CddMlc_LedStatus_aVal_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlPxl_CddMlc_CrcError_sVal
///
/// \descr  Stub function to simulate the behavoiur of Rte_Read_CtrlPxl_CddMlc_CrcError_sVal
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CtrlPxl_CddMlc_CrcError_sVal(tsRte_MlcComErrorStatus* ppara1)
{
  *ppara1 = Rte_Read_CtrlPxl_CddMlc_CrcError_sVal_Param1;
  Rte_Read_CtrlPxl_CddMlc_CrcError_sVal_HitCount++;

  return Rte_Read_CtrlPxl_CddMlc_CrcError_sVal_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_IoHwAbUser_VccxLineState
///
/// \descr  Stub function to simulate the behavoiur of Rte_Read_IoHwAbUser_VccxLineState
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_IoHwAbUser_VccxLineState(teRte_VccxLineState* ppara1)
{
  *ppara1 = Rte_Read_IoHwAbUser_VccxLineState_Param1;
  Rte_Read_IoHwAbUser_VccxLineState_HitCount++;

  return Rte_Read_IoHwAbUser_VccxLineState_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels
///
/// \descr  stub function to simulate the behaviour of Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels(tsRte_TgtPxlSig0Arr* ppara1)
{
  uint16* pTest = (uint16*)ppara1;
  for (uint8 ucIdx = 0u; ucIdx < CFG_LOGICAL_UNITS; ucIdx++)
  {
    *pTest++ = Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_Param1.unPxl_Int[ucIdx];
  }
  Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_HitCount++;

  return Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CtrlPxl_TgtMtxPixels_sVal
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CtrlPxl_TgtMtxPixels_sVal
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CtrlPxl_TgtMtxPixels_sVal(const tsRte_TgtMtxPixels_sVal* ppara1)
{
  Rte_Write_CtrlPxl_TgtMtxPixels_sVal_Param1[0][0] = *ppara1;
  Rte_Write_CtrlPxl_TgtMtxPixels_sVal_HitCount++;

  return Rte_Write_CtrlPxl_TgtMtxPixels_sVal_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState
/// 
/// \descr  Stub function to simulate the behavoiur of  Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState(const tsRte_MatrixFaultStates* ppara1)
{
  Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState_Param1 = *ppara1;
  Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState_HitCount++;
  
  return Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CtrlPxl_CtrlLed_Matrix_bErr_aVal
///
/// \descr  Stub function to simulate the behavoiur of Rte_Write_CtrlPxl_CtrlLed_Matrix_bErr_aVal
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CtrlPxl_CtrlLed_Matrix_bErr_aVal(const tauRte_CtrlPxl_Mtx_bErr* ppara1)
{
  tuRte_CtrlPxl_bErr* pTest = (tuRte_CtrlPxl_bErr*) ppara1;

  for (uint32 ulIdx = 0u; ulIdx < CFG_LOGICAL_UNITS; ulIdx++)
  {
    Rte_Write_CtrlPxl_CtrlLed_Matrix_bErr_aVal_Param1.auMtxErrorStatus[ulIdx] = *pTest++;
  }
  Rte_Write_CtrlPxl_CtrlLed_Matrix_bErr_aVal_HitCount++;

  return Rte_Write_CtrlPxl_CtrlLed_Matrix_bErr_aVal_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CtrlPxl_CddMlc_SysCtrlCommand
///
/// \descr Stub function created to simulate the behaviour of Rte_Write_CtrlPxl_CddMlc_SysCtrlCommand
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CtrlPxl_CddMlc_SysCtrlCommand(const uint8* ppara1)
{
  Rte_Write_CtrlPxl_CddMlc_SysCtrlCommand_Param1 = *ppara1;
  Rte_Write_CtrlPxl_CddMlc_SysCtrlCommand_HitCount++;

  return Rte_Write_CtrlPxl_CddMlc_SysCtrlCommand_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CtrlPxl_ActualPxlPWM
///
/// \descr  Stub function to simulate the behaviour of Rte_Write_CtrlPxl_ActualPxlPWM
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CtrlPxl_ActualPxlPWM(const tsRte_ucActualPxlPWM* ppara1)
{
  for (uint8 ucSegIdx = 0u; ucSegIdx < CFG_MATRIX_MAX_NO_PXL; ucSegIdx++)
  {
    *((uint8*)&Rte_Write_CtrlPxl_ActualPxlPWM_Param1 + ucSegIdx )= *((uint8*)(void*)ppara1 + ucSegIdx);
  }
  Rte_Write_CtrlPxl_ActualPxlPWM_HitCount++;
  return Rte_Write_CtrlPxl_ActualPxlPWM_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CtrlPxl_ActualPxlError
///
/// \descr  Stub function to simulate the behaviour of Rte_Write_CtrlPxl_ActualPxlError
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CtrlPxl_ActualPxlError(const tsRte_boMtxSegmentFault* ppara1)
{
  for (uint32 ucSegIdx = 0u; ucSegIdx < CFG_MATRIX_MAX_NO_PXL; ucSegIdx++)
  {
    *((uint8*)(void*)&Rte_Write_CtrlPxl_ActualPxlError_Param1 + ucSegIdx) = *((uint8*)(void*)ppara1 + ucSegIdx);
  }
  Rte_Write_CtrlPxl_ActualPxlError_HitCount++;
  return Rte_Write_CtrlPxl_ActualPxlError_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CtrlPxl_MtxEeprom_ErrorStatus
///
/// \descr  Stub function to simulate the behaviour of Rte_Write_CtrlPxl_MtxEeprom_ErrorStatus
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CtrlPxl_MtxEeprom_ErrorStatus(const tsRte_MtxEeprom_ErrStatus* ppara1)
{
  Rte_Write_CtrlPxl_MtxEeprom_ErrorStatus_Param1 = *ppara1;
  Rte_Write_CtrlPxl_MtxEeprom_ErrorStatus_HitCount++;

  return Rte_Write_CtrlPxl_MtxEeprom_ErrorStatus_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CtrlPxl_CtrlLed_EepromBinningClass_aVal
///
/// \descr  Stub function to simulate the behaviour of Rte_Write_CtrlPxl_CtrlLed_EepromBinningClass_aVal
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CtrlPxl_CtrlLed_EepromBinningClass_aVal(const tasRte_CtrlPxl_BinEEprom* ppara1)
{
  for (uint32 ucSegIdx = 0u; ucSegIdx < sizeof(tasRte_CtrlPxl_BinEEprom); ucSegIdx++)
  {
    *((uint8*)(void*)&Rte_Write_CtrlPxl_CtrlLed_EepromBinningClass_aVal_Param1 + ucSegIdx) = *((uint8*)(void*)ppara1 + ucSegIdx);

  }

  Rte_Write_CtrlPxl_CtrlLed_EepromBinningClass_aVal_HitCount++;

  return Rte_Write_CtrlPxl_CtrlLed_EepromBinningClass_aVal_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CtrlPxl_MatrixEE_CbkInitData
///
/// \descr  Stub function to simulate the behaviour of Rte_Write_CtrlPxl_MatrixEE_CbkInitData
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CtrlPxl_MatrixEE_CbkInitData(const tsRte_MatrixEE0CbkFn* ppara1)
{
  Rte_Write_CtrlPxl_MatrixEE_CbkInitData_Param1 = *ppara1;
  Rte_Write_CtrlPxl_MatrixEE_CbkInitData_HitCount++;

  return Rte_Write_CtrlPxl_MatrixEE_CbkInitData_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CtrlPxl_MatrixEE_DataRead
///
/// \descr  Stub function to simulate the behaviour of Rte_Write_CtrlPxl_MatrixEE_DataRead
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CtrlPxl_MatrixEE_DataRead(const tsRte_MatrixEE0peration* ppara1)
{
  Rte_Write_CtrlPxl_MatrixEE_DataRead_Param1 = *ppara1;
  Rte_Write_CtrlPxl_MatrixEE_DataRead_HitCount++;

  return Rte_Write_CtrlPxl_MatrixEE_DataRead_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CtrlPxl_MatrixEE_DataWrite
///
/// \descr  Stub function to simulate the behaviour of Rte_Write_CtrlPxl_MatrixEE_DataWrite
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CtrlPxl_MatrixEE_DataWrite(const tsRte_MatrixEE0peration* ppara1) 
{
  Rte_Write_CtrlPxl_MatrixEE_DataWrite_Param1 = *ppara1;
  Rte_Write_CtrlPxl_MatrixEE_DataWrite_HitCount++;

  return Rte_Write_CtrlPxl_MatrixEE_DataWrite_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CtrlPxl_Nvm_WriteData
///
/// \descr  Stub function to simulate the behaviour of Rte_Write_CtrlPxl_Nvm_WriteData
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CtrlPxl_Nvm_WriteData(const tsRte_NvMBlock* ppara1)
{
  Rte_Write_CtrlPxl_Nvm_WriteData_Param1 = *ppara1;
  Rte_Write_CtrlPxl_Nvm_WriteData_HitCount++;

  return Rte_Write_CtrlPxl_Nvm_WriteData_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CtrlPxl_CddMlc_ReinitMatrix
///
/// \descr  Stub function to simulate the behavior of Rte_Write_CtrlPxl_CddMlc_ReinitMatrix
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
/// \brief  Crc_CalculateCRC8H1D
///
/// \descr  Stub function created to simulate the behaviour of Crc_CalculateCRC8H1D
///
/// \param  pucCrc_DataPtr
/// \param  ulCrc_Length
/// \param  ulCrc_StartValue32
///
/// \return Crc_CalculateCRC8H1D_RetVal
//-----------------------------------------------------------------------------
uint8 Crc_CalculateCRC8H1D(CONST_AL uint8 *DataPtr, CONST_AL uint32 Length, CONST_AL uint8  StartValue8)
{
  Crc_CalculateCRC8H1D_Param1 = DataPtr;
  Crc_CalculateCRC8H1D_Param2 = Length;
  Crc_CalculateCRC8H1D_Param3 = StartValue8;

  Crc_CalculateCRC8H1D_HitCount++;

  return Crc_CalculateCRC8H1D_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  UtilMemCopy
///
/// \descr  Stub function created to simulate the behaviour of UtilMemCopy
///
/// \param  pucDest     : pointer to destination data buffer
/// \param  pucSource   : pointer to source data buffer
/// \param  unLength    : data length to be copied
///
/// \return void
//-----------------------------------------------------------------------------
void UtilMemCopy(uint8* pucDest, const uint8* pucSource, uint16_least unLength)
{
  UtilMemCopy_Input_Param1 = *pucDest;
  UtilMemCopy_Input_Param2 = *pucSource;
  UtilMemCopy_Input_Param3 = unLength;

  pucDest   = UtilMemCopy_Output_Param1;
  pucSource = UtilMemCopy_Output_Param2;

  UtilMemCopy_HitCount++;
}

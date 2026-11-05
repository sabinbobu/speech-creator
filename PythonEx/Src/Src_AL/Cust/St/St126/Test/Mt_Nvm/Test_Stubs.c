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
uint8             UtilMemClr_Param1;
uint16_least      UtilMemClr_Param2;

uint8*            Crc_CalculateCRC32_Param1;
uint32_least      Crc_CalculateCRC32_Param2;
uint32            Crc_CalculateCRC32_Param3;

uint8             UtilMemCopy_Input_Param1;
uint8             UtilMemCopy_Input_Param2;
uint16_least      UtilMemCopy_Input_Param3;

uint8             UtilMemCopy_Output_Param1[90];
uint8             UtilMemCopy_Output_Param2[90];

tsRte_NvMBlock    Rte_Read_CtrlPxl_Nvm_WriteData_Param1;

//=============================================================================
// Stub function returned value stubs
//=============================================================================

uint32            Crc_CalculateCRC32_RetVal;
uint32            Rte_Read_CtrlPxl_Nvm_WriteData_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================
uint8             UtilMemClr_HitCount;
uint8             UtilMemCopy_HitCount;
uint8             Crc_CalculateCRC32_HitCount;
uint8             Mt_Nvm_Internal_CallbackFunction_Stub_HitCount;
uint8             Mt_Nvm_Internal_InitCallback_Stub_HitCount;
uint8             Rte_Read_CtrlPxl_Nvm_WriteData_HitCount;

//=============================================================================
// Stub function definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  Mt_Nvm_Internal_pfnCallBackFunc_Stub
///
/// \descr  Stub function created to simulate the behaviour of a Callback Function
///
/// \return void
//-----------------------------------------------------------------------------
void Mt_Nvm_Internal_pfnCallBackFunc_Stub(void)
{
  Mt_Nvm_Internal_CallbackFunction_Stub_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Mt_Nvm_Internal_pfnInitCallback_Stub
///
/// \descr  Stub function created to simulate the behaviour of init callback fct.
///
/// \return void
//-----------------------------------------------------------------------------
void Mt_Nvm_Internal_pfnInitCallback_Stub(void)
{
  Mt_Nvm_Internal_InitCallback_Stub_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  UtilMemClr
///
/// \descr  Stub function created to simulate the behaviour of UtilMemClr
///
/// \param  pucBuffer   : pointer to data buffer
/// \param  unLength    : data length
///
/// \return void
//-----------------------------------------------------------------------------
void UtilMemClr(uint8 *pucBuffer, uint16_least unLength)
{
  UtilMemClr_Param1 = *pucBuffer;
  UtilMemClr_Param2 = unLength;
  UtilMemClr_HitCount++;
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

  pucDest                  = UtilMemCopy_Output_Param1;
  pucSource                = UtilMemCopy_Output_Param2;

  UtilMemCopy_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Crc_CalculateCRC32
///
/// \descr  Stub function created to simulate the behaviour of Crc_CalculateCRC32
///
/// \param  pucCrc_DataPtr
/// \param  ulCrc_Length
/// \param  ulCrc_StartValue32
///
/// \return Crc_CalculateCRC32_RetVal
//-----------------------------------------------------------------------------
uint32 Crc_CalculateCRC32(CONST_AL uint8* pucCrc_DataPtr, uint32_least ulCrc_Length, uint32 ulCrc_StartValue32)
{
  Crc_CalculateCRC32_Param1 = pucCrc_DataPtr;
  Crc_CalculateCRC32_Param2 = ulCrc_Length;
  Crc_CalculateCRC32_Param3 = ulCrc_StartValue32;

  Crc_CalculateCRC32_HitCount++;

  return Crc_CalculateCRC32_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlPxl_Nvm_WriteData
///
/// \descr  Stub function used to simulate the behavior of Rte_Read_CtrlPxl_Nvm_WriteData
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CtrlPxl_Nvm_WriteData(tsRte_NvMBlock* ppara1)
{
  *ppara1 = Rte_Read_CtrlPxl_Nvm_WriteData_Param1;
  Rte_Read_CtrlPxl_Nvm_WriteData_HitCount++;

  return Rte_Read_CtrlPxl_Nvm_WriteData_RetVal;
}

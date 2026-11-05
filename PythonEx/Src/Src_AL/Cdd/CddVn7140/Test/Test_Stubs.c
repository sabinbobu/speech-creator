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
boolean            IoHwAbUser_SetHss_Sen_Param1;
uint32             IoHwAbUser_GetHss0Sense_Param1;
uint32             IoHwAbUser_GetHss1Sense_Param1;
uint8              CDDVN7140_ECUVARCFG_aHSS_Type_Param1;
uint32             LPTMR0_GetTimeElapsed_Param1;
tun16Percent_1_328 IoHwAbUser_SetHss_En1_Param1;
tun16Percent_1_328 IoHwAbUser_SetHss_En2_Param1;

//=============================================================================
// Stub function returned value stubs
//=============================================================================
uint8              CDDVN7140_ECUVARCFG_aHSS_Type_RetVal;
uint32             LPTMR0_GetTimeElapsed_RetVal;
                   
uint16             Cod_HSS3Shor2GndThr_RetVal;
uint16             Cod_HSS3Shor2VbatThr_RetVal;
uint16             Cod_HSS3OpenLoadThr_RetVal;
boolean            Cod_DiagValid_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================
uint8              IoHwAbUser_SetHss_Sen_HitCount;
uint8              CDDVN7140_ECUVARCFG_aHSS_Type_HitCount;
uint8              LPTMR0_GetTimeElapsed_HitCount;
uint8              IoHwAbUser_GetHss0Sense_HitCount;
uint8              IoHwAbUser_GetHss1Sense_HitCount;
uint8              IoHwAbUser_SetHss_En1_HitCount;
uint8              IoHwAbUser_SetHss_En2_HitCount;
                   
uint8              Cod_HSS3Shor2GndThr_HitCount;
uint8              Cod_HSS3Shor2VbatThr_HitCount;
uint8              Cod_HSS3OpenLoadThr_HitCount;
uint8              Cod_DiagValid_HitCount;

//=============================================================================
// Stub function definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  Cod_DiagValid
///
/// \descr  Stub function created to simulate the behaviour of Cod_DiagValid
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean Cod_DiagValid(void)
{
  Cod_DiagValid_HitCount++;
  return Cod_DiagValid_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Cod_HSS2Shor2GndThr
///
/// \descr  Stub function created to simulate the behaviour of Cod_HSS3Shor2GndThr
///
/// \param  void
///
/// \return uint16
//-----------------------------------------------------------------------------
uint16 Cod_HSS3Shor2GndThr(void)
{
  Cod_HSS3Shor2GndThr_HitCount++;
  return Cod_HSS3Shor2GndThr_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Cod_HSS3Shor2VbatThr
///
/// \descr  Stub function created to simulate the behaviour of Cod_HSS3Shor2VbatThr
///
/// \param  void
///
/// \return uint16
//-----------------------------------------------------------------------------
uint16 Cod_HSS3Shor2VbatThr(void)
{
  Cod_HSS3Shor2VbatThr_HitCount++;
  return Cod_HSS3Shor2VbatThr_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Cod_HSS3OpenLoadThr
///
/// \descr  Stub function created to simulate the behaviour of Cod_HSS3OpenLoadThr
///
/// \param  void
///
/// \return uint16
//-----------------------------------------------------------------------------
uint16 Cod_HSS3OpenLoadThr(void)
{
  Cod_HSS3OpenLoadThr_HitCount++;
  return Cod_HSS3OpenLoadThr_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  IoHwAbUser_SetHss_En2
///
/// \descr  Stub function created to simulate the behaviour of IoHwAbUser_SetHss_En2
///
/// \param  unTgtVal
///
/// \return void
//-----------------------------------------------------------------------------
void IoHwAbUser_SetHss_En2(tun16Percent_1_328 unTgtVal)
{
  IoHwAbUser_SetHss_En2_Param1 = unTgtVal;
  IoHwAbUser_SetHss_En2_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  IoHwAbUser_SetHss_En1
///
/// \descr  Stub function created to simulate the behaviour of IoHwAbUser_SetHss_En1
///
/// \param  unTgtVal
///
/// \return void
//-----------------------------------------------------------------------------
void IoHwAbUser_SetHss_En1(tun16Percent_1_328 unTgtVal)
{
  IoHwAbUser_SetHss_En1_Param1 = unTgtVal;
  IoHwAbUser_SetHss_En1_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  IoHwAbUser_GetHss1Sense
///
/// \descr  Stub function created to simulate the behaviour of IoHwAbUser_GetHss1Sense
///
/// \param  unDiagVal
///
/// \return void
//-----------------------------------------------------------------------------
void IoHwAbUser_GetHss1Sense(uint32* unDiagVal)
{
  *unDiagVal = IoHwAbUser_GetHss1Sense_Param1;
  IoHwAbUser_GetHss1Sense_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  IoHwAbUser_GetHss0Sense
///
/// \descr  Stub function created to simulate the behaviour of IoHwAbUser_GetHss0Sense
///
/// \param  unDiagVal
///
/// \return void
//-----------------------------------------------------------------------------
void IoHwAbUser_GetHss0Sense(uint32* unDiagVal)
{
  *unDiagVal = IoHwAbUser_GetHss0Sense_Param1;
  IoHwAbUser_GetHss0Sense_HitCount++;
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
/// \brief  CDDVN7140_ECUVARCFG_aHSS_Type
///
/// \descr  Stub function created to simulate the behaviour of CDDVN7140_ECUVARCFG_aHSS_Type
///
/// \param  ucIdx
///
/// \return uint8
//-----------------------------------------------------------------------------
uint8 CDDVN7140_ECUVARCFG_aHSS_Type(uint8 ucIdx)
{
  CDDVN7140_ECUVARCFG_aHSS_Type_Param1 = ucIdx;
  CDDVN7140_ECUVARCFG_aHSS_Type_HitCount++;
  return CDDVN7140_ECUVARCFG_aHSS_Type_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  IoHwAbUser_SetHss_Sen
///
/// \descr  Stub function created to simulate the behaviour of IoHwAbUser_SetHss_Sen
///
/// \param  boSettingValue
///
/// \return void
//-----------------------------------------------------------------------------
void IoHwAbUser_SetHss_Sen(boolean boSettingValue)
{
  IoHwAbUser_SetHss_Sen_Param1 = boSettingValue;
  IoHwAbUser_SetHss_Sen_HitCount++;
}

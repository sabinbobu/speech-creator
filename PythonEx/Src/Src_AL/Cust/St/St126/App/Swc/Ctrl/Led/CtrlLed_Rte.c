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
/// \file   CtrlLed_Rte.c
///
/// \brief  RteAccess for CtrlLed
///
/// \author Caba Ionut-Stefan (F37899C)
///         mailTo:ionut-stefan.caba[at]marelli.com
//-----------------------------------------------------------------------------
//=============================================================================
// includes
//=============================================================================
#include "CtrlLed_Rte.h"
#include "CtrlLed_Cfg.h"

#ifdef UNIT_TEST
extern Std_ReturnType Rte_Read_RSens_BinningClass_sVal_00(tsRte_Binning0* ppara1);
extern Std_ReturnType Rte_Read_RSens_BinningClass_sVal_01(tsRte_Binning0* ppara1);
extern Std_ReturnType Rte_Read_RSens_BinningClass_sVal_02(tsRte_Binning0* ppara1);
extern Std_ReturnType Rte_Read_RSens_BinningClass_sVal_03(tsRte_Binning0* ppara1);
extern Std_ReturnType Rte_Read_RSens_BinningClass_sVal_04(tsRte_Binning0* ppara1);
extern Std_ReturnType Rte_Read_RSens_BinningClass_sVal_05(tsRte_Binning0* ppara1);
extern Std_ReturnType Rte_Read_RSens_BinningClass_sVal_06(tsRte_Binning0* ppara1);
extern Std_ReturnType Rte_Read_RSens_BinningClass_sVal_07(tsRte_Binning0* ppara1);
extern Std_ReturnType Rte_Read_RSens_BinningClass_sVal_08(tsRte_Binning0* ppara1);
extern Std_ReturnType Rte_Read_RSens_BinningClass_sVal_09(tsRte_Binning0* ppara1);
extern Std_ReturnType Rte_Read_RSens_BinningClass_sVal_10(tsRte_Binning0* ppara1);
extern Std_ReturnType Rte_Read_RSens_BinningClass_sVal_11(tsRte_Binning0* ppara1);
#endif
//=============================================================================
// variables
//=============================================================================

// Array of function pointers to read Binning Class value
STATIC_AL Std_ReturnType(*CtrlLed_Rte_apfnReadTgtBinningClass_sVal_List[CTRLLED_CFG_BASIC_LED_CH]) (tsRte_Binning0* psTgtBinningVal) =
{
  Rte_Read_RSens_BinningClass_sVal_00,
  Rte_Read_RSens_BinningClass_sVal_01,
  Rte_Read_RSens_BinningClass_sVal_02,
  Rte_Read_RSens_BinningClass_sVal_03,
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
  Rte_Read_RSens_BinningClass_sVal_04,
  Rte_Read_RSens_BinningClass_sVal_05,
  Rte_Read_RSens_BinningClass_sVal_06,
  Rte_Read_RSens_BinningClass_sVal_07,
  Rte_Read_RSens_BinningClass_sVal_08,
  Rte_Read_RSens_BinningClass_sVal_09,
  Rte_Read_RSens_BinningClass_sVal_10,
  Rte_Read_RSens_BinningClass_sVal_11,
#endif

};

//=============================================================================
// functions prototype
//=============================================================================
STATIC_AL Std_ReturnType CtrlLed_Rte_ReadTgtBinningVal(uint8_fast ucIdx, tsRte_Binning0* sTgtBinningVal);
STATIC_AL Std_ReturnType CtrlLed_RteAccess_Get_EcuSide(teCtrlLed_EcuSide* eEcuSide);

//=============================================================================
// functions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_Rte_ReadTgtBinningVal
///
/// \descr  This function calls an array of function pointers for each led channel
///
/// \param  ucIdx         - index of led channel
///         sTgtBinningVal - pointer to the data structure with target binning value
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
STATIC_AL Std_ReturnType CtrlLed_Rte_ReadTgtBinningVal(uint8_fast ucIdx, tsRte_Binning0* sTgtBinningVal)
{
  Std_ReturnType ucReturnValue = 0u;

  //check against null ptr
  if (CtrlLed_Rte_apfnReadTgtBinningClass_sVal_List[ucIdx] != NULL_PTR)
  {
    //read binning classes
    ucReturnValue = CtrlLed_Rte_apfnReadTgtBinningClass_sVal_List[ucIdx](sTgtBinningVal);
  }

  return ucReturnValue;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_Rte_Get_BinningClass
///
/// \descr  This function return binning class for each led channel
///
/// \param  ucIdx         - index of led channel
///
/// \return uint8 (binning class)
//-----------------------------------------------------------------------------
uint8 CtrlLed_Rte_Get_BinningClass(uint8_fast ucIdx)
{
  tsRte_Binning0 sBinning;
  uint8 ucBinningClass = CTRLLED_CFG_UNKNOWN_UINT8_VALUE; //0xFFu -> invalid binning (class 5)
  //read power factor for each channel
  (void)CtrlLed_Rte_ReadTgtBinningVal(ucIdx, &sBinning);

  //check signal qty or 
  ucBinningClass = ((sBinning.eSigQty != SIG_VALID) || (sBinning.ucBinning == (uint8)eBinningClassErr)) ? CTRLLED_CFG_UNKNOWN_UINT8_VALUE : sBinning.ucBinning;

  //return binning class
  return ucBinningClass;
}

//-----------------------------------------------------------------------------
/// \brief CtrlLed_RteAccess_Read_Vbat
///
/// \descr Read Vbat voltage Rte call wrapper
///
/// \param  void
///
/// \return unVoltage_mV - batery voltage indirected
//-----------------------------------------------------------------------------
uint16 CtrlLed_RteAccess_Read_Vbat(void)
{
  tiu32Voltage_mV u32Voltage_mV;
  // Rte call for Vbat voltage
  (void)Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT(&u32Voltage_mV);

  return (uint16)u32Voltage_mV;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_RteAccess_Get_EcuSide
///
/// \descr  Read Ecu mounting side from Rte
///
/// \param  eEcuSide - stores Ecu mounting side
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
STATIC_AL Std_ReturnType CtrlLed_RteAccess_Get_EcuSide(teCtrlLed_EcuSide* eEcuSide)
{
  Std_ReturnType     ucReturnValue;
  teRte_MountingSide eMountingSide;

  ucReturnValue = Rte_Read_IoHwAbUser_GetMountingSide(&eMountingSide);

  switch (eMountingSide)
  {
  case eMountedLeft:
    *eEcuSide = eEcu_Left;
    break;
  case eMountedRight:
    *eEcuSide = eEcu_Right;
    break;
  default:
    *eEcuSide = eEcu_Undef;
    break;
  }

  return ucReturnValue;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_RteAccess_Read_EcuSide
///
/// \descr  this function return ECU side, used for coding data handling
///
/// \param  void
///
/// \return eEcuSide - stores Ecu mounting side
//-----------------------------------------------------------------------------
uint8 CtrlLed_RteAccess_Get_ECU_Side(void)
{
  teCtrlLed_EcuSide eEcuSide = eEcu_Undef;
  //read ECU side
  (void)CtrlLed_RteAccess_Get_EcuSide(&eEcuSide);
  //return ECU side, cast needed for macro
  return (uint8)eEcuSide;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_RteAccess_Get_CodingPara
///
/// \descr  this function get coding params via RTE
///
/// \param  *sCodingParam
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlLed_RteAccess_Get_CodingPara(tsCtrlLed_CodingParam *sCodingParam)
{
  tsRteCodingParameters *sRteCoding;
  //PRQA S 310 1 //cust needed
  sRteCoding = (tsRteCodingParameters*)sCodingParam;
  //read coding 
  (void)Rte_Read_CodM_CtrlLed_Para(sRteCoding);
}

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_RteAccess_Get_ChannelState
///
/// \descr  this function get channel states via RTE
///
/// \param  *sChannelState
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlLed_RteAccess_Get_ChannelState(uint8_fast ucIdx, tsCtrlLed_aChannelState *psChannelState)
{
  static tsRte_SysMon_LedStates sRte_LedStates;
  //read led state 
  (void)Rte_Read_SysMon_LedState(&sRte_LedStates);
  //PRQA S 310 1 //cust needed
  psChannelState->asChannelState[ucIdx].ucChannelStatus = sRte_LedStates.aLedStates[ucIdx];
  psChannelState->asChannelState[ucIdx].boVinOk = sRte_LedStates.boVinBoostOk[ucIdx];
}

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_RteAccess_Set_ChannelSettings
///
/// \descr  this function set errors disabled for each channel
///
/// \param  *psChannelSettings
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlLed_RteAccess_Set_ChannelSettings(tsCtrlLed_ChannelSettings* psChannelSettings)
{
  tsRte_ChLedSettings psRte_ChLedSettings;

  psRte_ChLedSettings.ulDisableErrE2E = psChannelSettings->ulDisable_ErrE2E;
  psRte_ChLedSettings.ulDisableErrOpenLoad = psChannelSettings->ulDisable_ErrOpenLoad;
  psRte_ChLedSettings.ulDisableErrOverCurrent = psChannelSettings->ulDisable_ErrOverCurrent;
  psRte_ChLedSettings.ulDisableErrShortToGnd = psChannelSettings->ulDisable_ErrShortToGnd;
  psRte_ChLedSettings.ulDisableErrShortToUbat = psChannelSettings->ulDisable_ErrShortToUbat;
  psRte_ChLedSettings.ulDisableErrSpi = psChannelSettings->ulDisable_ErrSpi;
  psRte_ChLedSettings.ulDisableErrThermalShutdown = psChannelSettings->ulDisable_ErrThermalShutdown;
  psRte_ChLedSettings.ulDisableErrUnderVoltage = psChannelSettings->ulDisable_ErrUnderVoltage;
  psRte_ChLedSettings.ulDisableErrOverVoltage = psChannelSettings->ulDisable_ErrOverVoltage;

  (void)Rte_Write_CtrlLed_LedSettings_sVal(&psRte_ChLedSettings);
}

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_RteAccess_Set_IlluminantsStatus
///
/// \descr   
///
/// \param  ucIdxIl,  ucIlluminantState, boIlluminantStatus, ucChFctName
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlLed_RteAccess_Set_IlluminantsStatus(uint8_fast ucIdxIl, uint16 unIlluminantState, boolean boIlluminantStatus, uint8 ucChFctName)
{
  static tsRte_LedErrStateArr sLedErrStateArr = { 0 };

  sLedErrStateArr.uIlluminantState[ucIdxIl].unRaw = unIlluminantState;
  sLedErrStateArr.boIlluminantStatus[ucIdxIl] = boIlluminantStatus;
  sLedErrStateArr.ucIlluminantFctName[ucIdxIl] = ucChFctName;

  (void)Rte_Write_CtrlLed_ActLed_sState(&sLedErrStateArr);
}

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_RteAccess_Set_ChanelLedStatus
///
/// \descr   
///
/// \param   ucIdx,   boChanelLedState
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlLed_RteAccess_Set_ChanelLedStatus(uint8_fast ucIdx, boolean boChanelLedState)
{
    static tsRte_CtrlLed_ChStatesDiag sCtrlLedErrStateArr = { 0 };

    sCtrlLedErrStateArr.aboChStates[ucIdx] = boChanelLedState;

    (void)Rte_Write_CtrlLed_ChState(&sCtrlLedErrStateArr);
}

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_RteAccess_Set_Channel_Fbit
///
/// \descr   
///
/// \param  ucIdx,  boFbit
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlLed_RteAccess_Set_Channel_Fbit(uint8_fast ucIdx, boolean boFbit)
{
  static tsRte_LedChFbit sLedChFbit;

  sLedChFbit.aboLedChFbit[ucIdx] = boFbit;

  (void)Rte_Write_CtrlLed_LedChFbit(&sLedChFbit);
}

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_RteAccess_Set_HSS3_Duty
///
/// \descr   
///
/// \param  unDuty
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlLed_RteAccess_Set_HSS3_Duty(uint16 unDuty)
{
  tsRte_TgtLedSig0 sTgtHss3Sig0;

  sTgtHss3Sig0.unDutyCycle = unDuty;
  sTgtHss3Sig0.unCurrent = 0U;
  //write Rte
  (void)Rte_Write_CtrlLed_TgtHssSig_sVal(&sTgtHss3Sig0);
}

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_RteAccess_Get_HSS3_Status
///
/// \descr   
///
/// \param  *pucDataErr,  *pboEnabled
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlLed_RteAccess_Get_HSS3_Status(uint8 *pucDataErr, boolean *pboEnabled)
{
  tsRte_Hss3Status sHss3Status;
  *pucDataErr = 0xFFU;
  (void)Rte_Read_CtrlSwi_Hss3StatusErr(&sHss3Status);

  *pboEnabled = sHss3Status.boHss3_Enabled;
  
  if (sHss3Status.boHss3_OpenLoadStatus != FALSE)
  {
    *pucDataErr = 0U;
  }
  else if (sHss3Status.boHss3_Sh2VbatStatus != FALSE)
  {
    *pucDataErr = 1U;
  }
  else if (sHss3Status.boHss3_Sh2GndStatus != FALSE)
  {
    *pucDataErr = 2U;
  }
  else
  {
    *pucDataErr = 0xFFU;
  }
}

#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
//-----------------------------------------------------------------------------
/// \brief  CtrlLed_RteAccess_Get_DD01_Diag_Status
///
/// \descr   
///
/// \param  void
///
/// \return boDD04_Diag_Enable
//-----------------------------------------------------------------------------
boolean CtrlLed_RteAccess_Get_DD01_Diag_Status(void)
{
  boolean boDD01_Status;
  (void)Rte_Read_Diag_DD01_Activation(&boDD01_Status);

  return boDD01_Status;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_RteAccess_Get_Diag_Pixel_Intensity
///
/// \descr   
///
/// \param  *pucData
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlLed_RteAccess_Get_Diag_Pixel_Intensity(uint8 *pucData)
{
  tsRte_DIDPixelActivation *psDIDPixelActivation;
  //PRQA S 310 1 // Cast needed
  psDIDPixelActivation = (tsRte_DIDPixelActivation*)pucData;
  (void)Rte_Read_Diag_DD01_PixelActivation(psDIDPixelActivation);
  
}
//-----------------------------------------------------------------------------
/// \brief CtrlLed_RteAccess_VoltageRange
///
/// \descr Read voltage range via Rte call wrapper
///
/// \param  void
///
/// \return uint8 - batery voltage range
//-----------------------------------------------------------------------------
uint8 CtrlLed_RteAccess_VoltageRange(void)
{
  teRte_SysVolt_Results eSetVoltageState;
  // Rte call for Vbat voltage
  (void)Rte_Read_SysVolt_LedVoltRng0_sVoltRng(&eSetVoltageState);
  uint8 ucSetVoltageState = (eSetVoltageState == SysVolt_eNormal) ? CTRLLED_NORMAL_VOLT : \
    (eSetVoltageState == SysVolt_eLow2) ? CTRLLED_LOW2_VOLT : \
    (eSetVoltageState == SysVolt_eLow1) ? CTRLLED_LOW1_VOLT : \
    CTRLLED_UNKNOWN_VOLT;
  return ucSetVoltageState;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_RteAccess_Get_MatrixLuErrors
///
/// \descr   
///
/// \param  ucLu,  *puStatus
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlLed_RteAccess_Get_MatrixLuErrors(uint8 ucLu, tuCtrlLed_bErr *puStatus)
{
  tauRte_CtrlPxl_Mtx_bErr auMatrixErrors;

  (void)Rte_Read_CtrlPxl_CtrlLed_Matrix_bErr_aVal(&auMatrixErrors);

  puStatus[ucLu].bErr.bLossComm = auMatrixErrors.auMtxErrorStatus[ucLu].bErr.bLossComm;
  puStatus[ucLu].bErr.bCoruptComm = auMatrixErrors.auMtxErrorStatus[ucLu].bErr.bCoruptComm;
  puStatus[ucLu].bErr.bPxlFault = auMatrixErrors.auMtxErrorStatus[ucLu].bErr.bPxlFault;
  puStatus[ucLu].bErr.Reserved = auMatrixErrors.auMtxErrorStatus[ucLu].bErr.Reserved;
}


//-----------------------------------------------------------------------------
/// \brief  CtrlLed_RteAccess_Get_MatrixVccxErrors
///
/// \descr   
///
/// \param  *pboVccxGnd, *pboVccxBat
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlLed_RteAccess_Get_MatrixVccxErrors(boolean *pboVccxGnd, boolean *pboVccxBat)
{
  tsRte_MatrixFaultStates sMatrixFault;

  (void)Rte_Read_CtrlPxl_CtrLed_MatrixFault_sState(&sMatrixFault);

  *pboVccxGnd = sMatrixFault.boShortToGndError;
  *pboVccxBat = sMatrixFault.boShortToVbatError;  
}

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_RteAccess_Get_MatrixSystemMode
///
/// \descr  This function read the current matrix system mode and set TRUE if matrix
///         reached CddMlc_SystemMode_CfgLeds
///
/// \param  *pboData
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlLed_RteAccess_Get_MatrixSystemMode(boolean *pboData)
{
  teRte_CddMlc_SystemMode eSystemMode;

  (void)Rte_Read_CtrlPxl_CddMlc_SystemMode_eVal(&eSystemMode);

  *pboData = (eSystemMode >= CddMlc_SystemMode_CfgLeds) ? TRUE : FALSE;
}
#endif

// EOF

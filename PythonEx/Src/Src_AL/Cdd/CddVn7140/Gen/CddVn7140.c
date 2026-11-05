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
/// \file   CddVnd7140.c
///
/// \brief  Specific code for Vnd7140 hardware - MOST OF THE FEATURES WILL BE IN R2
///
/// \author Adrian Horlescu (F31197D)
///         mailTo:adrian-marian.horlescu[at]marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// Includes
//=============================================================================

#include <Std_Types.h>
#include <Util_Time.h>

#ifndef UNIT_TEST
#include <CddEft.h>
#include <CddSwi_Router.h>
#endif

#include <CddVn7140.h>
#include <CddVn7140_Cfg.h>
#include <CddVn7140_Router.h>
#include <CddVn7140_Types.h>
#include <Cfg/Cfg.h>

//=============================================================================
// Defines and Typedef
//=============================================================================

//=============================================================================
// Static variable declarations
//=============================================================================

STATIC_AL           boolean                       CddVn7140_boCodingValid;
STATIC_AL           boolean                       CddVn7140_boEftValid;
STATIC_AL           boolean                       CddVn7140_boHssSupport[CDDVN7140_CFG_OUTPUTS_CNT];
STATIC_AL           tsCddVn7140_States            CddVn7140_asStates[CDDVN7140_CFG_OUTPUTS_CNT];
STATIC_AL CONST_AL  tsCddVn7140_GetDiagVal_Router CddVn7140_GetDiagFuncList[CDDVN7140_CFG_OUTPUTS_CNT] = DrvVn7140GetDiagVal_FuncRouteList;
STATIC_AL CONST_AL  tsCddVn7140_SetTgt_Router     CddVn7140_SetTgtFuncList[CDDVN7140_CFG_OUTPUTS_CNT]  = DrvVn7140SetTgt_FuncRouteList;

STATIC_AL CONST_AL  uint16 CddVn7140_aCurrentFactor[CDDVN7140_CFG_OUTPUTS_CNT] =
{
  CDDVN7140_CFG_CURRENT_FACTOR_HSS3,
};

STATIC_AL uint16 CddVn7140_aunOpenLoadThreshold[CDDVN7140_CFG_OUTPUTS_CNT] =
{
  CDDVN7140_CFG_OPENLOAD_THRESHOLD,
};

STATIC_AL uint16 CddVn7140_aunShort2GndThreshold[CDDVN7140_CFG_OUTPUTS_CNT] =
{
  CDDVN7140_CFG_SHORT2GND_THRESHOLD,
};

STATIC_AL uint16 CddVn7140_aunShort2VbatThreshold[CDDVN7140_CFG_OUTPUTS_CNT] =
{
  CDDVN7140_CFG_SHORT2VBAT_THRESHOLD,
};

STATIC_AL CONST_AL uint16 CddVn7140_unCurrentRsens = CDDVN7140_CFG_CURRENT_RSENES;

STATIC_AL tFTimer CddVn7140_HSSErrorWait;

STATIC_AL boolean CddVn7140_boFanActive;
STATIC_AL boolean CddVn7140_boRgbActive;

//=============================================================================
// Function prototypes
//=============================================================================

STATIC_AL void CddVn7140_ReadDiagVal(void);
STATIC_AL void CddVn7140_Diag_CheckAllErrors(void);
STATIC_AL void CddVn7140_CheckOpenload(uint32 ulChIdx);
STATIC_AL void CddVn7140_CheckShort2GND(uint32 ulChIdx);
STATIC_AL void CddVn7140_CheckShort2VBAT(uint32 ulChIdx);

//=============================================================================
// Macros
//=============================================================================
#define CDDVN7140_HSSOUT_OFFSET                                   2u
#define CDDVN7140_HSS_MINDUTY                                     40u
//=============================================================================
// Function definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  CddVn7140_Init
///
/// \descr  HSS Init function
///
/// \param  ulChipIdx
///
/// \return void
//-----------------------------------------------------------------------------
void CddVn7140_Init(CONST_AL uint32 ulChipIdx)
{
  (void)ulChipIdx;
  uint8 ucEFT_Idx;

  // read availability of coding data
  CddVn7140_boCodingValid = Cod_DiagValid();
  // Initialize error thresholds from coding
  CddVn7140_InitCodingParams();

  // read the EFT data
#ifndef UNIT_TEST
  CddVn7140_boEftValid = CddEft_DataValid();
#if defined(SAMPLE_FULL)
  CddVn7140_boHssSupport[CDDVN7140_CFG_OUTPUT1] = (CddSwi_pCodingArea->Led1.LedConfigDRV13.FUSA_DRV13_NAME != 0u) ? TRUE : FALSE;

#elif defined(SAMPLE_ECO)
  CddVn7140_boFanActive = CddSwi_pCodingArea->Fan1.Fans_Presence.ucFan1Enabled;
  CddVn7140_boRgbActive = (CddSwi_pCodingArea->Led1.LedConfigDRV13.FUSA_DRV13_NAME == CDDVN7140_HSS_SM || CddSwi_pCodingArea->Led1.LedConfigDRV13.FUSA_DRV13_NAME == CDDVN7140_HSS_DRL) ? TRUE : FALSE;

  CddVn7140_boHssSupport[CDDVN7140_CFG_OUTPUT1] = (CddVn7140_boFanActive == TRUE) || (CddVn7140_boRgbActive == TRUE) ? TRUE : FALSE;
#endif
#endif

  if ((CddVn7140_boEftValid != FALSE) && (CddVn7140_boCodingValid != FALSE))
  {
    // Initialize the hardware
    // set HSS_SEN to HIGH
    IoHwAbUser_SetHss_Sen(TRUE);
#if defined(SAMPLE_FULL)
    IoHwAbUser_SetHss_En3(CDDVN7140_CFG_HSS_EN_HIGH);
#endif
    for (uint8 ucIdx = 0; ucIdx < CDDVN7140_CFG_OUTPUTS_CNT; ucIdx++)
    {
      CddVn7140_asStates[ucIdx].ucHwState = ((CddVn7140_boHssSupport[ucIdx] != 0u) && (CDDVN7140_ECUVARCFG_aHSS_Type(ucEFT_Idx) != 0u)) ? CDDVN7140_CFG_HSS_SUPPORT : CDDVN7140_CFG_HSS_NOSUPPORT;
    }
  }
  else
  {
    for (uint8 ucIdx = 0; ucIdx < CDDVN7140_CFG_OUTPUTS_CNT; ucIdx++)
    {
      CddVn7140_asStates[ucIdx].ucHwState = CDDVN7140_CFG_HSS_NOEFT;
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddVn7140_InitCodingParams
///
/// \descr  Initialize error thresholds from coding
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddVn7140_InitCodingParams(void)
{
  // Check if coding is valid
  if (CddVn7140_boCodingValid != FALSE)
  {
    CddVn7140_aunShort2GndThreshold[CDDVN7140_CFG_OUTPUT1]  = (uint16)Cod_HSS3Shor2GndThr();
    CddVn7140_aunOpenLoadThreshold[CDDVN7140_CFG_OUTPUT1]   = (uint16)Cod_HSS3OpenLoadThr();
    CddVn7140_aunShort2VbatThreshold[CDDVN7140_CFG_OUTPUT1] = (uint16)Cod_HSS3Shor2VbatThr();
  }
  else
  {
    // Leave params previously defined
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddVnd7140_Cycle0
///
/// \descr  cyclic behaviour
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddVn7140_Cycle0(void)
{
  if (CddVn7140_boEftValid == TRUE)
  {
    // read the ADC value
    CddVn7140_ReadDiagVal();

    // evaluate the ADC value
    CddVn7140_Diag_CheckAllErrors();
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddVnd7140_SetTgt
///
/// \descr  set target value on HSS channel
///
/// \param  ulChipIdx
/// \param  ulChnIdx
/// \param  unTagVal
///
/// \return void
//-----------------------------------------------------------------------------
void CddVn7140_SetTgt(CONST_AL uint32 ulChipIdx, CONST_AL uint32 ulOutIdx, CONST_AL uint16 unTgtVal)
{
  (void)ulOutIdx;

  CddVn7140_asStates[ulChipIdx].unTgtVal = unTgtVal;

  if (CddVn7140_asStates[ulChipIdx].ucHwState == CDDVN7140_CFG_HSS_SUPPORT)
  { 
  // evaluate the target value and set the output
  if (unTgtVal == CDD_SWI_OFF)  // unTgtVal: ON -> OFF
  {
    // set output to Low;
    CddVn7140_SetTgtFuncList[ulChipIdx].IoHwAbUSerSetTgtFunc(CDDVN7140_CFG_HSS_EN_LOW);
    CddVn7140_asStates[ulChipIdx].unActVal    = unTgtVal;
    CddVn7140_asStates[ulChipIdx].unPreTgtVal = unTgtVal;
  }
  else if (unTgtVal <= CDD_SWI_ON)  // unTgtVal: 0FF -> ON
  {
    // set Duty Cycle;
    CddVn7140_SetTgtFuncList[ulChipIdx].IoHwAbUSerSetTgtFunc(unTgtVal);

    CddVn7140_asStates[ulChipIdx].unActVal    = unTgtVal;
    CddVn7140_asStates[ulChipIdx].unPreTgtVal = unTgtVal;
  }
  else  //unTgtVal: ON -> ON or OFF -> OFF
  {
    // do nothing
  }
  }
  else
  {
    // set output to Low;
    CddVn7140_SetTgtFuncList[ulChipIdx].IoHwAbUSerSetTgtFunc(CDDVN7140_CFG_HSS_EN_LOW);
    CddVn7140_asStates[ulChipIdx].unActVal = unTgtVal;
    CddVn7140_asStates[ulChipIdx].unPreTgtVal = unTgtVal;
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddVnd7140_GetSwitchState
///
/// \descr  return switch state on HSS channel
///
/// \param  ulChnIdx
///
/// \return uint8
//-----------------------------------------------------------------------------
tsCddVn7140_DrvStatus CddVn7140_GetState(CONST_AL uint32 ulChipIdx, CONST_AL uint32 ulOutIdx)
{
  (void)ulOutIdx;
  tsCddVn7140_DrvStatus tSwitchStatus;

  // check hardware state and set switch status
  if (CddVn7140_asStates[ulChipIdx].ucHwState == CDDVN7140_CFG_HSS_SUPPORT)
  {
    tSwitchStatus.unActVal = CddVn7140_asStates[ulChipIdx].unActVal;

    tSwitchStatus.ucErrOpenLoad     = CddVn7140_asStates[ulChipIdx].ucErrOpenload;
    tSwitchStatus.ucErrShort2GND    = CddVn7140_asStates[ulChipIdx].ucErrShort2GND;
    tSwitchStatus.ucErrShort2VBAT   = CddVn7140_asStates[ulChipIdx].ucErrShort2VBAT;
    tSwitchStatus.unActCurrent     = CddVn7140_asStates[ulChipIdx].unCurrent;
    tSwitchStatus.ucHwState        = CDDVN7140_CFG_HSS_SUPPORT;
  }
  else if (CddVn7140_asStates[ulChipIdx].ucHwState == CDDVN7140_CFG_HSS_NOEFT)
  {
    tSwitchStatus.ucHwState = CDDVN7140_CFG_HSS_NOEFT;
  }
  else if (CddVn7140_asStates[ulChipIdx].ucHwState == CDDVN7140_CFG_HSS_NOSUPPORT)
  {
    tSwitchStatus.ucHwState = CDDVN7140_CFG_HSS_NOSUPPORT;
  }
  else
  {
    tSwitchStatus.ucHwState = CDDVN7140_CFG_HSS_SNA;
  }
  return tSwitchStatus;
}

//-----------------------------------------------------------------------------
/// \brief  CddVnd7140_ReadDiagVal
///
/// \descr  read the diagnose value from IoHwAbUser
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddVn7140_ReadDiagVal(void)
{
  tiu32Voltage_mV unDiagVal = 0u;

  for (uint8 ucIdx = 0; ucIdx < CDDVN7140_CFG_OUTPUTS_CNT; ucIdx++)
  {
    if (CddVn7140_asStates[ucIdx].ucHwState == CDDVN7140_CFG_HSS_SUPPORT)
    {
      CddVn7140_GetDiagFuncList[ucIdx].IoHwAbUSerGetDiagValFunc(&unDiagVal);
      CddVn7140_asStates[ucIdx].unDiagVal = (uint16)unDiagVal;
      // calculate the current
      if (CddVn7140_unCurrentRsens != 0u)
      {
        CddVn7140_asStates[ucIdx].unCurrent = (uint16)(unDiagVal * CddVn7140_aCurrentFactor[ucIdx] / CDDVN7140_CFG_CURRENT_RSENES);
      }
      else
      {
        // do nothing
      }
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddVn7140_Diag_CheckAllErrors
///
/// \descr  check open load, short to ground and shor to vbat errors
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddVn7140_Diag_CheckAllErrors(void)
{
  for (uint8 ucIdx = 0; ucIdx < CDDVN7140_CFG_OUTPUTS_CNT; ucIdx++)
  {
    if (CddVn7140_asStates[ucIdx].ucHwState == CDDVN7140_CFG_HSS_SUPPORT)
    {
      CddVn7140_CheckOpenload(ucIdx);
      CddVn7140_CheckShort2GND(ucIdx);
      CddVn7140_CheckShort2VBAT(ucIdx);
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddVn7140_CheckOpenload
///
/// \descr  check open load
///
/// \param  uint32 ulChIdx
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddVn7140_CheckOpenload(uint32 ulChIdx)
{
  // evaluate the target value
  if (CddVn7140_asStates[ulChIdx].unTgtVal != CDD_SWI_OFF)
  {
    // evaluate the daignose value for open load and set error

  // ucHssDuty should not be 0
    uint8 ucHssDuty = (uint8)(((CddVn7140_asStates[ulChIdx].unTgtVal * 100u / 0x8000u) != 0u) ? (CddVn7140_asStates[ulChIdx].unTgtVal * 100u / 0x8000u) : 1u);

    if ((CddVn7140_asStates[ulChIdx].unDiagVal < (CddVn7140_aunOpenLoadThreshold[ulChIdx] * ucHssDuty) / 100u) && ucHssDuty > CDDVN7140_HSS_MINDUTY)

    {
      if (CddVn7140_asStates[ulChIdx].ucErrShort2VBAT != CDDVN7140_CFG_ERR_YES)
      {
        CddVn7140_asStates[ulChIdx].ucErrOpenload = CDDVN7140_CFG_ERR_YES;
      }
      // TBC
    }
    else
    {
      CddVn7140_asStates[ulChIdx].ucErrOpenload = CDDVN7140_CFG_ERR_NO;
      CddVn7140_asStates[ulChIdx].ucErrShort2VBAT = CDDVN7140_CFG_ERR_NO;
    }
  }
  else
  {
    // do nothing
  }
}


//-----------------------------------------------------------------------------
/// \brief  CddVn7140_CheckShort2GND
///
/// \descr  check shortcoil to GND
///
/// \param  uint32 ulChIdx
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddVn7140_CheckShort2GND(uint32 ulChIdx)
{
  // evaluate the target value
  if (CddVn7140_asStates[ulChIdx].unTgtVal != CDD_SWI_OFF)
  {
    // evaluate the daignose value for short to ground and set error

    // ucHssDuty should not be 0
    uint8 ucHssDuty = (uint8)(((CddVn7140_asStates[ulChIdx].unTgtVal * 100u / 0x8000u) != 0u) ? (CddVn7140_asStates[ulChIdx].unTgtVal * 100u / 0x8000u) : 1u);

    if ((CddVn7140_asStates[ulChIdx].unDiagVal > (CddVn7140_aunShort2GndThreshold[ulChIdx] * ucHssDuty) / 100u) && ucHssDuty > CDDVN7140_HSS_MINDUTY)
    {
      CddVn7140_asStates[ulChIdx].ucErrShort2GND = CDDVN7140_CFG_ERR_YES;
    }
    else
    {
      CddVn7140_asStates[ulChIdx].ucErrShort2GND = CDDVN7140_CFG_ERR_NO;
    }
  }
  else
  {
    // do nothing
  }
}


//-----------------------------------------------------------------------------
/// \brief  CddVn7140_CheckShort2VBAT
///
/// \descr  check shortcoil to VBAT
///
/// \param  (uint32 ulChIdx
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddVn7140_CheckShort2VBAT(uint32 ulChIdx)
{
  // evaluate the target value
  if (CddVn7140_asStates[ulChIdx].unTgtVal == 0u)
  {
    // evaluate the daignose value for short to vbat and set error
    if (CddVn7140_asStates[ulChIdx].unDiagVal > CddVn7140_aunShort2VbatThreshold[ulChIdx])
    {
      CddVn7140_asStates[ulChIdx].ucErrShort2VBAT = CDDVN7140_CFG_ERR_YES;
    }
    else
    {
      CddVn7140_asStates[ulChIdx].ucErrShort2VBAT = CDDVN7140_CFG_ERR_NO;
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddVnd7140_DeInit
///
/// \descr  intialisation
///
/// \param  ulChipIdx
///
/// \return void
//-----------------------------------------------------------------------------
void CddVn7140_DeInit(CONST_AL uint32 ulChipIdx)
{
  (void)ulChipIdx;

  if (CddVn7140_boEftValid == TRUE)
  {
    // Deinitialize the hardware
    // set HSS_SEN to LOW
#if defined(SAMPLE_FULL)
    DrvVn7140EnableHssSense(FALSE);
#endif
    // switch the output off
    for (uint8 ucIdx = 0; ucIdx < CDDVN7140_CFG_OUTPUTS_CNT; ucIdx++)
    {
      CddVn7140_SetTgtFuncList[ucIdx].IoHwAbUSerSetTgtFunc(FALSE);
    }
  }
}

// EOF

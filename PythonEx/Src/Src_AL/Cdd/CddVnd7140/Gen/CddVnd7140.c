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
/// \brief  Specific code for Vnd7140 hardware
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

#include <CddVnd7140.h>
#include <CddVnd7140_Cfg.h>
#include <CddVnd7140_Router.h>
#include <CddVnd7140_Types.h>

//=============================================================================
// Defines and Typedef
//=============================================================================,

#define CDDVND7140_HSSError_FTimer     FT_MSEC(30u) // time in [ms]

//=============================================================================
// Static variable declarations
//=============================================================================

STATIC_AL          boolean                       CddVnd7140_boCodingValid;
STATIC_AL          boolean                       CddVnd7140_boEftValid;
STATIC_AL          boolean                       CddVnd7140_boHssSupport[CDDVND7140_CFG_OUTPUTS_CNT];
STATIC_AL          tsCddVnd7140_States           CddVnd7140_asStates[CDDVND7140_CFG_OUTPUTS_CNT];
STATIC_AL CONST_AL tsCddVnd7140_SetTgtRouter     CddVnd7140_SetTgtFuncList[CDDVND7140_CFG_OUTPUTS_CNT]  = DrvVnd7140SetTgt_FuncRouteList;
STATIC_AL CONST_AL tsCddVnd7140_GetDiagValRouter CddVnd7140_GetDiagFuncList[CDDVND7140_CFG_OUTPUTS_CNT] = DrvVnd7140GetDiagVal_FuncRouteList;

STATIC_AL uint16 CddVnd7140_aunShort2GndThreshold[CDDVND7140_CFG_OUTPUTS_CNT] =
{
  CDDVND7140_CFG_CH1_SHORT2GND_THRESHOLD,
  CDDVND7140_CFG_CH2_SHORT2GND_THRESHOLD,
};

STATIC_AL uint16 CddVnd7140_aunShort2VbatThreshold[CDDVND7140_CFG_OUTPUTS_CNT] =
{
  CDDVND7140_CFG_CH1_SHORT2VBAT_THRESHOLD,
  CDDVND7140_CFG_CH2_SHORT2VBAT_THRESHOLD,
};

STATIC_AL uint16 CddVnd7140_aunOpenLoadThreshold[CDDVND7140_CFG_OUTPUTS_CNT] =
{
  CDDVND7140_CFG_CH1_OPENLOAD_THRESHOLD,
  CDDVND7140_CFG_CH2_OPENLOAD_THRESHOLD,
};

STATIC_AL CONST_AL uint16 CddVnd7140_aCurrentFactor[CDDVND7140_CFG_OUTPUTS_CNT] =
{
  CDDVND7140_CFG_CURRENT_FACTOR_HSS1_2,
  CDDVND7140_CFG_CURRENT_FACTOR_HSS1_2,
};

STATIC_AL CONST_AL uint16 CddVnd7140_unCurrentRsens = CDDVND7140_CFG_CURRENT_RSENES;

STATIC_AL tFTimer CddVnd7140_HSSErrorWait;


//=============================================================================
// Function prototypes
//=============================================================================

STATIC_AL void CddVnd7140_ReadDiagVal(void);
STATIC_AL void CddVnd7140_Diag_CheckAllErrors(void);
STATIC_AL void CddVnd7140_CheckOpenload(uint32 ulChIdx);
STATIC_AL void CddVnd7140_CheckShort2GND(uint32 ulChIdx);
STATIC_AL void CddVnd7140_CheckShort2VBAT(uint32 ulChIdx);

//=============================================================================
// Macros
//=============================================================================

//=============================================================================
// Function definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  CddVnd7140_Init
///
/// \descr  HSS Init function
///
/// \param  ulChipIdx
///
/// \return void
//-----------------------------------------------------------------------------
void CddVnd7140_Init(CONST_AL uint32 ulChipIdx)
{
  (void)ulChipIdx;

  // read availability of coding data
  CddVnd7140_boCodingValid = Cod_DiagValid();
  // Initialize error thresholds from coding
  CddVnd7140_InitCodingParams();

  // read the EFT data
#ifndef UNIT_TEST
  CddVnd7140_boEftValid = CddEft_DataValid();
  CddVnd7140_boHssSupport[CDDVND7140_CFG_OUTPUT1] = CddSwi_pCodingArea->Fan1.Fans_Presence.ucFan1Enabled;
  CddVnd7140_boHssSupport[CDDVND7140_CFG_OUTPUT2] = CddSwi_pCodingArea->Fan1.Fans_Presence.ucFan2Enabled;
#endif

  if ((CddVnd7140_boEftValid != FALSE) && (CddVnd7140_boCodingValid != FALSE))
  {
    // Initialize the hardware
    // set HSS_SEN to HIGH
    DrvVnd7140EnableHssSense(TRUE);
    // set HSS_ERROR to HIGH
    DrvVnd7140SetHssERROR(TRUE);

    for (uint8 ucIdx = 0; ucIdx < CDDVND7140_CFG_OUTPUTS_CNT; ucIdx++)
    {
      CddVnd7140_asStates[ucIdx].ucHwState = ((CddVnd7140_boHssSupport[ucIdx] != 0u) && (CDDVND7140_ECUVARCFG_aHSS_Type(ucIdx) != 0u)) ? CDDVND7140_CFG_HSS_SUPPORT : CDDVND7140_CFG_HSS_NOSUPPORT;
    }
  }
  else
  {
    for (uint8 ucIdx = 0; ucIdx < CDDVND7140_CFG_OUTPUTS_CNT; ucIdx++)
    {
      CddVnd7140_asStates[ucIdx].ucHwState = CDDVND7140_CFG_HSS_NOEFT;
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddVnd7140_InitCodingParams
///
/// \descr  Initialize error thresholds from coding
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddVnd7140_InitCodingParams(void)
{
  // Check if coding is valid
  if (CddVnd7140_boCodingValid != FALSE)
  {
    CddVnd7140_aunShort2GndThreshold[CDDVND7140_CFG_OUTPUT1]  = (uint16)Cod_HSS1Shor2GndThr();
    CddVnd7140_aunShort2GndThreshold[CDDVND7140_CFG_OUTPUT2]  = (uint16)Cod_HSS2Shor2GndThr();

    CddVnd7140_aunOpenLoadThreshold[CDDVND7140_CFG_OUTPUT1]   = (uint16)Cod_HSS1OpenLoadThr();
    CddVnd7140_aunOpenLoadThreshold[CDDVND7140_CFG_OUTPUT2]   = (uint16)Cod_HSS2OpenLoadThr();

    CddVnd7140_aunShort2VbatThreshold[CDDVND7140_CFG_OUTPUT1] = (uint16)Cod_HSS1Shor2VbatThr();
    CddVnd7140_aunShort2VbatThreshold[CDDVND7140_CFG_OUTPUT2] = (uint16)Cod_HSS2Shor2VbatThr();
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
void CddVnd7140_Cycle0(void)
{
  if (CddVnd7140_boEftValid != FALSE)
  {
  // read the ADC value
    CddVnd7140_ReadDiagVal();

  // evaluate the ADC value
    CddVnd7140_Diag_CheckAllErrors();
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
void CddVnd7140_SetTgt(CONST_AL uint32 ulChipIdx, CONST_AL uint32 ulOutIdx, CONST_AL uint16 unTgtVal)
{
  static uint32 ulTimerStart  = 0u;
  static uint32 ulTimeElapsed = 0u;

  CddVnd7140_asStates[ulChipIdx + ulOutIdx].unTgtVal = unTgtVal;

  if (CddVnd7140_asStates[ulChipIdx + ulOutIdx].ucHwState == CDDVND7140_CFG_HSS_SUPPORT)
  { 
  // evaluate the target value and set the output
  if ((unTgtVal == CDD_SWI_ON) && (CddVnd7140_asStates[ulChipIdx + ulOutIdx].unPreTgtVal == 0u))  // unTgtVal: 0FF -> ON
  {
    CddVnd7140_HSSErrorWait = FastTimerStart(CDDVND7140_HSSError_FTimer);
    // set HSS_ERROR to LOW for 30ms
    DrvVnd7140SetHssERROR(FALSE);

    // set output to High;
    CddVnd7140_SetTgtFuncList[ulChipIdx+ ulOutIdx].IoHwAbUSerSetTgtFunc(CDDVND7140_CFG_HSS_EN_HIGH);
    CddVnd7140_asStates[ulChipIdx + ulOutIdx].unActVal    = unTgtVal;
    CddVnd7140_asStates[ulChipIdx + ulOutIdx].unPreTgtVal = unTgtVal;
  }
  else if ((unTgtVal == CDD_SWI_OFF) && (CddVnd7140_asStates[ulChipIdx + ulOutIdx].unPreTgtVal == CDD_SWI_ON))  // unTgtVal: ON -> OFF
  {
    // set output to Low;
    CddVnd7140_SetTgtFuncList[ulChipIdx + ulOutIdx].IoHwAbUSerSetTgtFunc(CDDVND7140_CFG_HSS_EN_LOW);
    CddVnd7140_asStates[ulChipIdx + ulOutIdx].unActVal    = unTgtVal;
    CddVnd7140_asStates[ulChipIdx + ulOutIdx].unPreTgtVal = unTgtVal;
  }
  else  //unTgtVal: ON -> ON or OFF -> OFF
  {
    ulTimeElapsed = UTILTIME_MSEC(TimerGetTimeSince(ulTimerStart));
    if (FastTimerTimeout(CddVnd7140_HSSErrorWait) != FALSE)
    {
      // set HSS_ERROR to HIGH
      DrvVnd7140SetHssERROR(TRUE);
    }
  }
  }
  else
  {
    // set output to Low;
    CddVnd7140_SetTgtFuncList[ulChipIdx + ulOutIdx].IoHwAbUSerSetTgtFunc(CDDVND7140_CFG_HSS_EN_LOW);
    CddVnd7140_asStates[ulChipIdx + ulOutIdx].unActVal = unTgtVal;
    CddVnd7140_asStates[ulChipIdx + ulOutIdx].unPreTgtVal = unTgtVal;
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddVnd7140_GetSwitchState
///
/// \descr  return switch state on HSS channel
///
/// \param  ulChipIdx
/// \param  ulChnIdx
///
/// \return tsCddVnd7140_States
//-----------------------------------------------------------------------------
tsCddVnd7140_DrvStatus CddVnd7140_GetState(CONST_AL uint32 ulChipIdx, CONST_AL uint32 ulOutIdx)
{
  tsCddVnd7140_DrvStatus tSwitchStatus;

  // check hardware state and set switch status
  if (CddVnd7140_asStates[ulChipIdx + ulOutIdx].ucHwState == CDDVND7140_CFG_HSS_SUPPORT)
  {
    tSwitchStatus.unActVal          = CddVnd7140_asStates[ulChipIdx + ulOutIdx].unActVal;
    tSwitchStatus.ucErrOpenLoad     = CddVnd7140_asStates[ulChipIdx + ulOutIdx].ucErrOpenload;
    tSwitchStatus.ucErrShort2GND    = CddVnd7140_asStates[ulChipIdx + ulOutIdx].ucErrShort2GND;
    tSwitchStatus.ucErrShort2VBAT   = CddVnd7140_asStates[ulChipIdx + ulOutIdx].ucErrShort2VBAT;
    tSwitchStatus.unActCurrent      = CddVnd7140_asStates[ulChipIdx + ulOutIdx].unCurrent;
    tSwitchStatus.ucHwState         = CDDVND7140_CFG_HSS_SUPPORT;
  }
  else if (CddVnd7140_asStates[ulChipIdx + ulOutIdx].ucHwState == CDDVND7140_CFG_HSS_NOEFT)
  {
    tSwitchStatus.ucHwState = CDDVND7140_CFG_HSS_NOEFT;
  }
  else if (CddVnd7140_asStates[ulChipIdx + ulOutIdx].ucHwState == CDDVND7140_CFG_HSS_NOSUPPORT)
  {
    tSwitchStatus.ucHwState = CDDVND7140_CFG_HSS_NOSUPPORT;
  }
  else
  {
    tSwitchStatus.ucHwState = CDDVND7140_CFG_HSS_SNA;
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
STATIC_AL void CddVnd7140_ReadDiagVal(void)
{
  tiu32Voltage_mV ulDiagVal = 0u;

  for (uint8 ucIdx = 0; ucIdx < CDDVND7140_CFG_OUTPUTS_CNT; ucIdx++)
  {
    if (CddVnd7140_asStates[ucIdx].ucHwState == CDDVND7140_CFG_HSS_SUPPORT)
    {
      CddVnd7140_GetDiagFuncList[ucIdx].IoHwAbUSerGetDiagValFunc(&ulDiagVal);
      CddVnd7140_asStates[ucIdx].unDiagVal = (uint16) ulDiagVal;
      // calculate the current
      if (CddVnd7140_unCurrentRsens != 0u)
      {
        CddVnd7140_asStates[ucIdx].unCurrent = (uint16)(ulDiagVal * CddVnd7140_aCurrentFactor[ucIdx] / CDDVND7140_CFG_CURRENT_RSENES);
      }
      else
      {
        // do nothing
      }
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddVnd7140_Diag_CheckAllErrors
///
/// \descr  check open load, short to ground and shor to vbat errors
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddVnd7140_Diag_CheckAllErrors(void)
{
  for (uint8 ucIdx = 0; ucIdx < CDDVND7140_CFG_OUTPUTS_CNT; ucIdx++)
  {
    if (CddVnd7140_asStates[ucIdx].ucHwState == CDDVND7140_CFG_HSS_SUPPORT)
    {
      CddVnd7140_CheckOpenload(ucIdx);
      CddVnd7140_CheckShort2GND(ucIdx);
      CddVnd7140_CheckShort2VBAT(ucIdx);
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddVnd7140_CheckOpenload
///
/// \descr  check open load
///
/// \param  uint32 ulChIdx
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddVnd7140_CheckOpenload(uint32 ulChIdx)
{
  // evaluate the target value
  if (CddVnd7140_asStates[ulChIdx].unTgtVal == CDD_SWI_ON)
  {
    // evaluate the daignose value for open load and set error
    if (CddVnd7140_asStates[ulChIdx].unDiagVal < CddVnd7140_aunOpenLoadThreshold[ulChIdx])
    {
      if (CddVnd7140_asStates[ulChIdx].ucErrShort2VBAT == CDDVND7140_CFG_ERR_NO)
      {
        CddVnd7140_asStates[ulChIdx].ucErrOpenload = CDDVND7140_CFG_ERR_YES;
      }
    }
    else
    {
      CddVnd7140_asStates[ulChIdx].ucErrOpenload   = CDDVND7140_CFG_ERR_NO;
      CddVnd7140_asStates[ulChIdx].ucErrShort2VBAT = CDDVND7140_CFG_ERR_NO;
    }
  }
  else
  {
     // do nothing
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddVnd7140_CheckShort2GND
///
/// \descr  check shortcoil to GND
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddVnd7140_CheckShort2GND(uint32 ulChIdx)
{
  // evaluate the target value
  if (CddVnd7140_asStates[ulChIdx].unTgtVal == CDD_SWI_ON)
  {
    // evaluate the daignose value for short to ground and set error
    if (CddVnd7140_asStates[ulChIdx].unDiagVal > CddVnd7140_aunShort2GndThreshold[ulChIdx])
    {
      CddVnd7140_asStates[ulChIdx].ucErrShort2GND = CDDVND7140_CFG_ERR_YES;
    }
    else
    {
      CddVnd7140_asStates[ulChIdx].ucErrShort2GND = CDDVND7140_CFG_ERR_NO;
    }
  }
  else
  {
    //do nothing
  }
}


//-----------------------------------------------------------------------------
/// \brief  CddVnd7140_CheckShort2VBAT
///
/// \descr  check shortcoil to VBAT
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddVnd7140_CheckShort2VBAT(uint32 ulChIdx)
{
  // evaluate the target value
  if (CddVnd7140_asStates[ulChIdx].unTgtVal == CDD_SWI_OFF)
  {
    // evaluate the daignose value for short to vbat and set error
    if (CddVnd7140_asStates[ulChIdx].unDiagVal > CddVnd7140_aunShort2VbatThreshold[ulChIdx])
    {
      CddVnd7140_asStates[ulChIdx].ucErrShort2VBAT = CDDVND7140_CFG_ERR_YES;
    }
    else
    {
      CddVnd7140_asStates[ulChIdx].ucErrShort2VBAT = CDDVND7140_CFG_ERR_NO;
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddVnd7140_DeInit
///
/// \descr  deintialisation
///
/// \param  ulChipIdx
///
/// \return void
//-----------------------------------------------------------------------------
void CddVnd7140_DeInit(CONST_AL uint32 ulChipIdx)
{
  (void)ulChipIdx;
  if (CddVnd7140_boEftValid != FALSE)
  {
    // Deinitialize the hardware
    // set HSS_SEN to LOW
    DrvVnd7140EnableHssSense(FALSE);

    // set HSS_ERROR to LOW
    DrvVnd7140SetHssERROR(FALSE);

    // set HSS_EN to LOW
    // switch the output off
    for (uint8 ucIdx = 0; ucIdx < CDDVND7140_CFG_OUTPUTS_CNT; ucIdx++)
    {
      CddVnd7140_SetTgtFuncList[ucIdx].IoHwAbUSerSetTgtFunc(CDDVND7140_CFG_HSS_EN_LOW);
    }
  }
}

// EOF

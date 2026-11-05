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
/// \file   CddNcv78702.c
///
/// \brief
///
/// \author OTT, Peter ALDE-RT/EES6
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
// standard includes
#include <Std_Types.h>
#include <AL_Helper.h>
#include <UtilUtility.h>

// module API (include path)
#include <CddNcv78702.h>
#include <CddNcv78702_Cb.h>

// module includes (relative to API)
#include <../Cfg/CddNcv78702_Cfg.h>
#include <../Cfg/CddNcv78702_RoutCfg.h>
#include <../Gen/CddNcv78702_Types.h>
#include <../Gen/CddNcv78702_Com.h>


//-----------------------------------------------------------------------------
// Start definitions of initialized boolean variables
//-----------------------------------------------------------------------------
#define ctadCddBoost_START_SEC_VAR_INIT_BOOLEAN
#include <../Cfg/CddNcv78702_MemMap.h>

STATIC_AL boolean CddNcv78702_boThermalShtDwnStatus  = FALSE;
STATIC_AL boolean CddNcv78702_boThermalWarningStatus = FALSE;

#define ctadCddBoost_STOP_SEC_VAR_INIT_BOOLEAN
#include <../Cfg/CddNcv78702_MemMap.h>
//-----------------------------------------------------------------------------
// End definitions of initialized boolean variables
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Start declaration or definitions of functions
//-----------------------------------------------------------------------------
#define ctadCddBoost_START_SEC_CODE
#include <../Cfg/CddNcv78702_MemMap.h>


//-----------------------------------------------------------------------------
// Function definitions
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
/// \brief  SPI error status
///
/// \descr  
///
/// \param  uint32 index (for future expansion, not used)
///
/// \return TRUE in case of SPI error
//-----------------------------------------------------------------------------
boolean CddNcv78702_IsSpiError(const uint32 ulIdx)
{
  tCddNcv78702_Reg0x0A Reg0x0A;

  boolean boIsValid = CddNcv78702_GetReg0x0A(&Reg0x0A);

  (void)Reg0x0A;  // register contents not relevant for SPI check
  (void)ulIdx;    // index for future use: still not supported

  return (boIsValid == FALSE) ? TRUE : FALSE;
}


//-----------------------------------------------------------------------------
/// \brief  Get TSD status from hardware driver
///
/// \descr  
///
/// \param  uint32 index (for future expansion, not used)
///
/// \return TRUE if thermal shutdown active
//-----------------------------------------------------------------------------
boolean CddNcv78702_IsThermalShutDown(const uint32 ulIdx)
{
  tCddNcv78702_Reg0x0A Reg0x0A;

  boolean boIsValid = CddNcv78702_GetReg0x0A(&Reg0x0A);

  (void)ulIdx;  // index for future use: still not supported

  if (boIsValid != FALSE)  // discard RX data in case of SPI error, return value keeps unchanged
  {
    CddNcv78702_boThermalShtDwnStatus = (Reg0x0A.Bit.biTSD == 0u) ? FALSE : TRUE;
  }

  return CddNcv78702_boThermalShtDwnStatus;
}


//-----------------------------------------------------------------------------
/// \brief  Get TW status from hardware driver
///
/// \descr  
///
/// \param  uint32 index (for future expansion, not used)
///
/// \return TRUE if thermal warning active
//-----------------------------------------------------------------------------
boolean CddNcv78702_IsThermalWarning(const uint32 ulIdx)
{
  tCddNcv78702_Reg0x0A Reg0x0A;

  boolean boIsValid = CddNcv78702_GetReg0x0A(&Reg0x0A);

  (void)ulIdx;  // index for future use: still not supported

  if (boIsValid != FALSE)  // discard RX data in case of SPI error, return value keeps unchanged
  {
    CddNcv78702_boThermalWarningStatus = (Reg0x0A.Bit.biTW == 0u) ? FALSE : TRUE;
  }

  return CddNcv78702_boThermalWarningStatus;
}


//-----------------------------------------------------------------------------
/// \brief  Set GPIOs BOOST_ENABLE and BOOST_FSO pin
///
/// \descr  Control GPIOs enable pins of booster depending on EFT parameters
///
/// \param  boBoostEnable:  TRUE or FALSE
///
/// \return void
//-----------------------------------------------------------------------------
void CddNcv78702_SetBoostEnableGpio(const boolean boBoostEnable)
{
  CDDNCV78702_SetBoosterEn(boBoostEnable);
}

//-----------------------------------------------------------------------------
/// \brief  Set the duty cycle of BSTSYNC PWM signal
///
/// \descr  Control the duty cycle of BSTSYNC signal
///
/// \param  unBstSyncDuty_1_32768
///
/// \return void
//-----------------------------------------------------------------------------
void CddNcv78702_SetBoostBstSyncDuty(const uint16 unBstSyncDuty_1_32768)
{
  boolean boEnable = (unBstSyncDuty_1_32768 != 0u) ? TRUE : FALSE;

  CDDNCV78702_SetBoosterPwm(boEnable); // Florin Onufriciuc: set booster pwm is empty ?
}//PRQA S 5334 //Architecture

//-----------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void CddNcv78702_SetBoosterVoltage(const uint32 ulIdx, const uint16 unVBoostTarget_mV)
{
  uint8   ucBoostVsetpoint = 0u;
  sint32  slVBoostTargetAdjusted = 0;
  sint16  snCalibBoostVoffset = CDDNCV78702_CALIB_nVOffset(0);
  uint16  unCalibBoostVfactor = CDDNCV78702_CALIB_unVFactor(0);
#if defined (CFG_VARIANT_ECO)
  uint8   unCalibBoostVariant = CDDNCV78702_ECUVARCFG_ucVariant(0);
#endif

  (void)ulIdx;  // for future use

  if (unCalibBoostVfactor == 0xFFFFu)  // if booster is not explicitely calibrated
  {
    snCalibBoostVoffset = CDDNCV78702_ECUVARCFG_nVOffset(0);
    unCalibBoostVfactor = CDDNCV78702_ECUVARCFG_unVFactor(0);
  }

  //Guard to avoid any division by 0.
  if (unCalibBoostVfactor != 0u)
  {
#if defined (CFG_VARIANT_ECO)
    if (unCalibBoostVariant == 3u)
    {
      uint16 unVBoostLim = UTIL_MIN(unVBoostTarget_mV, CDDNCV78702_Cfg_60V_VboostMax);  // upper limit
      unVBoostLim = UTIL_MAX(unVBoostLim, CDDNCV78702_Cfg_60V_VboostMin);  // lower limit

      slVBoostTargetAdjusted = (sint32)unVBoostLim - snCalibBoostVoffset;                  // calculate according to EFT data
      ucBoostVsetpoint = (uint8)(((uint32)slVBoostTargetAdjusted + ((uint32)unCalibBoostVfactor / 2u)) / unCalibBoostVfactor);  // divide and round

      ucBoostVsetpoint = UTIL_MIN(ucBoostVsetpoint, CDDNCV78702_Cfg_60V_BOOST_VSETPOINT_Max);  // upper limit
      ucBoostVsetpoint = UTIL_MAX(ucBoostVsetpoint, CDDNCV78702_Cfg_60V_BOOST_VSETPOINT_Min);  // lower limit
    }
    else
#endif
    {
      uint16 unVBoostLim = UTIL_MIN(unVBoostTarget_mV, CDDNCV78702_Cfg_VboostMax);  // upper limit
      unVBoostLim = UTIL_MAX(unVBoostLim, CDDNCV78702_Cfg_VboostMin);  // lower limit

      slVBoostTargetAdjusted = (sint32)unVBoostLim - snCalibBoostVoffset;                  // calculate according to EFT data
      ucBoostVsetpoint = (uint8)(((uint32)slVBoostTargetAdjusted + ((uint32)unCalibBoostVfactor / 2u)) / unCalibBoostVfactor);  // divide and round

      ucBoostVsetpoint = UTIL_MIN(ucBoostVsetpoint, CDDNCV78702_Cfg_BOOST_VSETPOINT_Max);  // upper limit
      ucBoostVsetpoint = UTIL_MAX(ucBoostVsetpoint, CDDNCV78702_Cfg_BOOST_VSETPOINT_Min);  // lower limit
    }
  }

  if (CDDNCV78702_EftDataValid() != FALSE)  // end of line data available
  {
    CddNcv78702_SetBoostVsetpoint(ucBoostVsetpoint);
  }
}

//-----------------------------------------------------------------------------
/// \brief  Initialize module and return EFT status
///
/// \descr  
///
/// \param  
///
/// \return uint32 - bit mask indicating available booster channels
///                  Bit0 - Channel 0, Bit1 - channel 1...
//-----------------------------------------------------------------------------
uint32 CddNcv78702_Init(void)
{
  uint32 ulRet = 0u;

  if (CDDNCV78702_EftDataValid() != FALSE)
  {
    // check if channel is available (do not check output assignment yet, no requirement yet)
    if (CDDNCV78702_ECUVARCFG_ucBoostCfg(0) != CDDNCV78702_EFT_BoosterNone)
    {
      ulRet = 1u;  // up to now only 1 channel supported
      CddNcv78702_SetBoostEnableGpio(TRUE);
#if defined (CFG_VARIANT_ECO) || defined (UNIT_TEST)
      CddNcv78702_SetBoostOverVoltageThr();
#endif
    }
  }

  return ulRet;
}


//-----------------------------------------------------------------------------
/// \brief
///
/// \descr  This function may be called only if SPI cyclic mode is stopped
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void CddNcv78702_Shutdown(void)
{
  CddNcv78702_SetBoostBstSyncDuty(0u);
  CddNcv78702_SetBoostEnableGpio(FALSE);
  CddNcv78702_SetBoostSleep();
}

#define ctadCddBoost_STOP_SEC_CODE
#include <../Cfg/CddNcv78702_MemMap.h>
//-----------------------------------------------------------------------------
// End declaration or definitions of functions
//-----------------------------------------------------------------------------

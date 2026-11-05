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
/// \file  CddBoost.c
///
/// \brief
///
/// \descr
///
/// \author OTT, Peter ALDE-RT/EES6
//-----------------------------------------------------------------------------


//=============================================================================
// Includes
//=============================================================================
// standard includes
#include <Std_Types.h>
#include <AL_Helper.h>

// module API (include path)
#include <CddBoost.h>

// module includes (relative to API)
#include <../Cfg/CddBoost_Cfg.h>
#include <../Cfg/CddBoost_RoutCfg.h>


//=============================================================================
// Defines
//=============================================================================
#define CDDBOOST_VoffsetForStart        500u  // [mV] offset to start booster at lower voltage than buck


//-----------------------------------------------------------------------------
// Start definitions of initialized 32 bit variables
//-----------------------------------------------------------------------------
#define ctadCddBoost_START_SEC_VAR_INIT_32
#include <../Cfg/CddBoost_MemMap.h>

STATIC_AL uint32 CddBoost_ulAvailMask = 0u;  // mask indicating availability of channels

#define ctadCddBoost_STOP_SEC_VAR_INIT_32
#include <../Cfg/CddBoost_MemMap.h>
//-----------------------------------------------------------------------------
// End definitions of initialized 32 bit variables
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// Start definitions of initialized boolean variables
//-----------------------------------------------------------------------------
#define ctadCddBoost_START_SEC_VAR_INIT_BOOLEAN
#include <../Cfg/CddBoost_MemMap.h>

STATIC_AL boolean CddBoost_boIsRunning = FALSE;
STATIC_AL boolean CddBoost_boParaValid = FALSE;

#define ctadCddBoost_STOP_SEC_VAR_INIT_BOOLEAN
#include <../Cfg/CddBoost_MemMap.h>
//-----------------------------------------------------------------------------
// End definitions of initialized boolean variables
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Start definitions of initialized structures and unions or arrays variables
//-----------------------------------------------------------------------------
#define ctadCddBoost_START_SEC_VAR_INIT_UNSPECIFIED
#include <../Cfg/CddBoost_MemMap.h>

STATIC_AL tCddBoostTarget CddBoost_sTarget = { 0u };

#define ctadCddBoost_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <../Cfg/CddBoost_MemMap.h>
//-----------------------------------------------------------------------------
// End definitions of initialized structures and unions or arrays variables
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Start declaration or definitions of functions
//-----------------------------------------------------------------------------
#define ctadCddBoost_START_SEC_CODE
#include <../Cfg/CddBoost_MemMap.h>


//-----------------------------------------------------------------------------
/// \brief  Startup initialization
///
/// \descr
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void CddBoost_Init(void)
{
  CddBoost_ulAvailMask = CDDBOOST_Drv_Init();  // Initialize and check for available devices
}


//-----------------------------------------------------------------------------
/// \brief  Function to update target values
///
/// \descr
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void CddBoost_SetTarget(tCddBoostTarget* pTarget)
{
  boolean boStartAllowed = TRUE;

  if (CddBoost_boIsRunning == FALSE)
  {
    uint32 ulSupplyVoltage_mV;

    CDDBOOST_GetECUSupply(&ulSupplyVoltage_mV);

    if (ulSupplyVoltage_mV < (CDDBOOST_Para_LED_VBAT_MIN_ON_V - CDDBOOST_VoffsetForStart))
    {
      boStartAllowed = FALSE;  // avoid booster start before reaching enough supply voltage
    }
    else
    {
      CddBoost_boIsRunning = TRUE;  // make sure thatbooster start is suppressed only at ECU startup
    }
  }

  CddBoost_sTarget = *pTarget;

  for (uint32 ul = 0u; ul < CDDBOOST_Cfg_NbOfChannels; ul++)
  {
    if (boStartAllowed != FALSE)
    {
      CDDBOOST_Drv_SetBoosterVoltage(ul, CddBoost_sTarget.aunBoostVolt_mV[ul]);
    }
  }
}


//-----------------------------------------------------------------------------
/// \brief  Function to return status
///
/// \descr
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void CddBoost_GetStatus(tCddBoostStatus* pStatus)
{
  for (uint32 ul = 0u; ul < CDDBOOST_Cfg_NbOfChannels; ul++)
  {
    boolean boSpiError          = CDDBOOST_Drv_IsSpiError(ul);
    boolean boIsReset           = CDDBOOST_Drv_IsReset(ul);
    boolean boIsThermalShutDown = CDDBOOST_Drv_IsThermalShutDown(ul);
    boolean boIsThermalWarning  = CDDBOOST_Drv_IsThermalWarning(ul);

    if ( ((CddBoost_ulAvailMask & ((uint32)1u << ul)) ==    0u)
      || ( CddBoost_boParaValid                       == FALSE) )
    {
      pStatus->aStatus[ul] = eCddBoost_NoSupport;
    }
    else if (boSpiError != FALSE)
    {
      pStatus->aStatus[ul] = eCddBoost_ErrSpi;
    }
    else if ((boIsReset != FALSE) || (CddBoost_boIsRunning == FALSE))
    {
      pStatus->aStatus[ul] = eCddBoost_Reset;
    }
    else if (boIsThermalShutDown != FALSE)
    {
      pStatus->aStatus[ul] = eCddBoost_ErrThermShutdn;
    }
    else
    {
      pStatus->aStatus[ul] = eCddBoost_StatusOk;
    }

    pStatus->aboThermalWarning[ul] = boIsThermalWarning;
  }

  // PRQA S 5336 1 // Simple "else if" construction
}


//-----------------------------------------------------------------------------
/// \brief  Function to set parameters
///
/// \descr
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void CddBoost_SetPara(boolean boValid)
{
  CddBoost_boParaValid = boValid;
}


//-----------------------------------------------------------------------------
/// \brief  Cyclic function which execute requested action every 20ms
///
/// \descr
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void CddBoost_Cycle20ms(void)
{
  return;  // not needed
}

//-----------------------------------------------------------------------------
/// \brief  Shutdown booster
///
/// \descr  This function sets the booster chip to sleep mode
///         It may be called only after stop of SPI cyclic communication
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void CddBoost_Shutdown(void)
{
  CDDBOOST_Drv_Shutdown();
}

#define ctadCddBoost_STOP_SEC_CODE
#include <../Cfg/CddBoost_MemMap.h>
//-----------------------------------------------------------------------------
// End declaration or definitions of functions
//-----------------------------------------------------------------------------


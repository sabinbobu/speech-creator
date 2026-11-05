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
/// \file   CddBoost_Adapter.c
///
/// \brief  Default adapter
///
/// \author OTT, Peter ALDE-RT/EES6
//-----------------------------------------------------------------------------
#include <Std_Types.h>
#include <AL_Helper.h>
#include <CddBoost.h>
#include <CddBoost_Adapter.h>
#include <../Cfg/CddBoost_RoutCfg.h>
#include <Cfg/Cfg.h>

#include <Bsw/Sys/Load/SysLoad.h>

#ifndef UNIT_TEST
#include <Rte.h>
#else
#include <RteCommonTypes.h>
#endif

#ifdef SYS_LOAD_RUNNABLE
SYS_LOAD_MEAS_VAR_DEC(riCddBoostInit)
SYS_LOAD_MEAS_VAR_DEC(rpCddBoost_Cycle)
#endif

//=============================================================================
// defines
//=============================================================================
// Needed because of booster voltage calculation in CddBoost
#if defined (CFG_VARIANT_FULL) || defined(UNIT_TEST)
#define CDDBOOST_BoostVoltLimit       49000u //FULL
#else
#define CDDBOOST_BoostVoltLimit       62000u //ECO
#endif


//=============================================================================
// variables
//=============================================================================
CONST_AL  tNvmPara_CodingArea* CddBoost_pCodingArea;
STATIC_AL boolean              CddBoost_boCodingValidity = FALSE;
STATIC_AL boolean              CddBoost_boParaInit       = FALSE;

// PRQA S 3408 1 // Explicit debug code
STATIC_AL tCddBoostStatus CddBoost_sStatus;

STATIC_AL uint16 CddBoost_unV_Boost = 0U;

//=============================================================================
//  Prototypes
//=============================================================================
STATIC_AL boolean CddBoost_ParaFct0(tParaFct0_Cmd eCmd, CONST_AL tNvmPara_CodingArea* CONST_AL pData);
STATIC_AL boolean CddBoost_CodingDataValidation(void);
STATIC_AL void    CddBoost_CalcTgtBoostVolt(boolean boValid);


//-----------------------------------------------------------------------------
/// \brief  riCddBoostInit
///
/// \descr  Init runnable to be called at MCU startup
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void riCddBoostInit(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(riCddBoostInit)
#endif
  CddBoost_boCodingValidity = CddBoost_CodingDataValidation();
  CddBoost_Init();

  if (CddBoost_boCodingValidity != FALSE)
  {
    CddBoost_boParaInit = TRUE; //check for FALSE to not activate the booster
    CddBoost_SetPara(CddBoost_boParaInit);

    // Calculate threshold for booster error detection
    CddBoost_CalcTgtBoostVolt(CddBoost_boParaInit);

    CddBoost_GetStatus(&CddBoost_sStatus);
  }

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(riCddBoostInit)
#endif
}


//-----------------------------------------------------------------------------
/// \brief  reCddBoostNewTarget
///
/// \descr  Function to be called on new target values
///         This shall be done event triggered by writing RTE target value
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void reCddBoostNewTarget(void) //This function should be called only when data reception
{
  tCddBoostTarget Target;
  //(void)RTE_READ_CDDBOOST_TARGET(&Target); //read port from SysMon
  Target.aunBoostVolt_mV[0] = CddBoost_unV_Boost;
  CddBoost_SetTarget            (&Target);
}


//-----------------------------------------------------------------------------
/// \brief  rpCddBoost_Cycle
///
/// \descr  Cyclic function which execute requested action every 5ms
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void rpCddBoost_Cycle(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(rpCddBoost_Cycle)
#endif
  tsRte_BoostState sBoostStates = { 0U };
  //tCddBoostStatus Status;

  // process only when coding is valid
  if (CddBoost_boCodingValidity != FALSE)
  {
    if (CddBoost_boParaInit == FALSE)
    {
      CddBoost_boParaInit = TRUE;
      CddBoost_SetPara(CddBoost_boParaInit);
      // Calculate threshold for booster error detection
      CddBoost_CalcTgtBoostVolt(CddBoost_boParaInit);
    }
    else
    {
      // nothing to do
    }
    
    reCddBoostNewTarget();
    CddBoost_Cycle20ms();
    CddBoost_GetStatus(&CddBoost_sStatus);

    sBoostStates.aboBoostDefect[0] = ((CddBoost_sStatus.aStatus[0] == eCddBoost_ErrSpi) || (CddBoost_sStatus.aStatus[0] == eCddBoost_ErrThermShutdn)) ? TRUE : FALSE;
    //write RTE
    (void)Rte_Write_CddBoost_BoostState(&sBoostStates);
    (void)Rte_Write_CddBoost_BoostStatus(&CddBoost_sStatus);
  }
  else
  {
    CddBoost_boCodingValidity = CddBoost_CodingDataValidation();
  }

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(rpCddBoost_Cycle)
#endif
  // PRQA S 5324 1 // STCAL = 8' exceeds threshold 7 for Number of Distinct Function Calls (STCAL)
}


//-----------------------------------------------------------------------------
/// \brief  CddBoost_Get_CodingPara
///
/// \descr  this function get coding params via RTE
///
/// \param  *sCodingParam
///
/// \return void
//-----------------------------------------------------------------------------
void CddBoost_Get_CodingPara(tsCddBoost_CodingParam *sCodingParam)
{
  tsRteCodingParameters *sRteCoding;
  //PRQA S 310 1 //cust needed
  sRteCoding = (tsRteCodingParameters*)sCodingParam;
  //read coding 
  (void)Rte_Read_CodM_CddBoost_Para(sRteCoding);
}


//-----------------------------------------------------------------------------
/// \brief  CddBoost_CodingDataValidation
///
/// \descr  get and handle coding parameters for CddBoost module
///
/// \param  void
///
/// \return return validity of coding as TRUE
//-----------------------------------------------------------------------------
STATIC_AL boolean CddBoost_CodingDataValidation(void)
{
  tsCddBoost_CodingParam sCodingParameters;

  //get coding data via RTE
  CDDBOOST_RTE_RE_GET_CODING_DATA(&sCodingParameters)
  //get coding data and return validity of this
  CONST_AL boolean boCodingValidity = CddBoost_ParaFct0(sCodingParameters.eCodingState, sCodingParameters.psCodingParameters_Blocks);

  //return validity of coding
  return boCodingValidity;
}


//-----------------------------------------------------------------------------
/// \brief  CddBoost_ParaFct0
///
/// \descr  this function get coding params and validity of coding data 
///
/// \param  eCmd - valid/invalid, pData - coding params
///
/// \return coding validity
//-----------------------------------------------------------------------------
STATIC_AL boolean CddBoost_ParaFct0(tParaFct0_Cmd eCmd, CONST_AL tNvmPara_CodingArea* CONST_AL pData)
{
  boolean boCodingValidity = FALSE;
  CddBoost_pCodingArea = pData;
  switch (eCmd)
  {
  case eParaFct0_CodingDataValid:
    boCodingValidity = TRUE;
    break;
  case eParaFct0_CodingDataInvalid:
    boCodingValidity = FALSE;
    break;
  default:
    break;
  }

  return boCodingValidity;
}


//-----------------------------------------------------------------------------
/// \brief  Function to set parameters
///
/// \descr  Function to calculate threshold for booster error detection
///
/// \param  boValid - Coding validity
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddBoost_CalcTgtBoostVolt(boolean boValid)
{
  uint16 unInputVoltThreshold = 0u;  // minimum input voltage

  if (boValid != FALSE)
  {
    uint32 ulTargetVolt = 0u;

    for (uint32 ul = 0u; ul < CDDLED_Cfg_NbOfChannels; ul++)
    {
      uint32 ulVoltChn = CDDBOOST_Para_FUSA_DRV_LED_OVER_VOLTAGE(ul);

      if (ulTargetVolt < ulVoltChn)
      {
        ulTargetVolt = ulVoltChn;
      }
    }

    ulTargetVolt       = ulTargetVolt + CDDBOOST_Para_BOOST_VOLT_HEADROOM;                    // ulTargetVolt is now the target booster voltage

    if (ulTargetVolt > CDDBOOST_BoostVoltLimit)                                               // use same limitation as in booster code
    {
      ulTargetVolt = CDDBOOST_BoostVoltLimit;
    }

    CddBoost_unV_Boost = (uint16)ulTargetVolt;  // CddBoost_unV_Boost is the threshold for booster error detection
  }
}


// EOF




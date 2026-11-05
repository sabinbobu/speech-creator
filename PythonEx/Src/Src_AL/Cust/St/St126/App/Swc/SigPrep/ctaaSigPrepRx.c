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
/// \file   ctaaSigPrepRx.c
///
/// \brief  
///
/// \descr  Init and Cyclic Runnables for SigPrep Rx
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <ctaaSigPrepRx.h>
#include <SigPrepRx.h>
#include <Bsw/Sys/Load/SysLoad.h>
#include <LgmEIMMainAPI.h>
#include <LgmDEHMainAPI.h>

#ifdef SYS_LOAD_RUNNABLE
SYS_LOAD_MEAS_VAR_DEC(rpSigPrepRx_Cycle)
SYS_LOAD_MEAS_VAR_DEC(riSigPrepRx_Init)
#endif

//-----------------------------------------------------------------------------
// functions
//-----------------------------------------------------------------------------

/// ---------------------------------------------------------------------------
/// \func     riSigPrepRx_Init
///
/// \brief    Init runnable
///
/// \param    none
///
/// \return   none
///
/// \descr    
/// ---------------------------------------------------------------------------
void riSigPrepRx_Init(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(riSigPrepRx_Init)
#endif

  SigPrepRx_Init();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(riSigPrepRx_Init)
#endif
}


/// ---------------------------------------------------------------------------
/// \func     rpSigPrepRx_Cycle0
///
/// \brief    Cyclic runnable
///
/// \param    none
///
/// \return   none
///
/// \descr    
/// ---------------------------------------------------------------------------
void rpSigPrepRx_Cycle(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(rpSigPrepRx_Cycle)
#endif

  SigPrepRx_Cycle0();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(rpSigPrepRx_Cycle)
#endif
}


//-----------------------------------------------------------------------------
/// \brief  reSigPrepRx_LifePhases
///
/// \descr  Runnable event for LGM function call EAPI_SetEIMInfo_CAN
///
/// \param  void 
///
/// \return void 
//-----------------------------------------------------------------------------
void reSigPrepRx_LifePhases(void)
{
  tsRte_SysMon_LifePhases  sLifePhases = { 0 };
  uint8                    ucInterdMemoDef = 0u;
  LEIM_TE_LifePhase        eLifePhase = LEIM_E_LF_WAKEUP;

  // Get values from SysMon
  (void)Rte_Read_SysMon_LifePhases(&sLifePhases);

  // Convert InterdMemoDef to correct type
  ucInterdMemoDef = (sLifePhases.eInterdMemoDef != eMemorisationAuthorized) ? 1u : 0u;

  // Convert PhaseVie to correct type
  switch (sLifePhases.ePhaseVie)
  {
    case eStandBy:
      eLifePhase = LEIM_E_LF_SLEEP;
      break;

    case eNormalMode:
      eLifePhase = LEIM_E_LF_NORMAL;
      break;

    case eSwitchToStadby:
      eLifePhase = LEIM_E_LF_GO_TO_SLEEP;
      break;

    case eWake:
      eLifePhase = LEIM_E_LF_WAKEUP;
      break;

    case eCOM_OFF:
      eLifePhase = LEIM_E_LF_COM_OFF;
      break;

    default:
      // Set as normal in case of Invalid value
      eLifePhase = LEIM_E_LF_NORMAL;
      break;
  }

  EAPI_SetEIMInfo_CAN(ucInterdMemoDef, eLifePhase);
}


//-----------------------------------------------------------------------------
/// \brief  reSigPrepRx_SetDiagMux
///
/// \descr  Runnable event for LGM function call DAPI_SetDiagMux
///
/// \param  void 
///
/// \return void 
//-----------------------------------------------------------------------------
void reSigPrepRx_SetDiagMux(void)
{
  TE_Bool ucDiagMux;
  (void)Rte_Read_SysMon_SetDiagMux(&ucDiagMux);
  DAPI_SetDiagMux(ucDiagMux);
}


// EOF

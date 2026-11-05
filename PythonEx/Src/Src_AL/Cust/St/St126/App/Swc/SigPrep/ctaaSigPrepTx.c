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
/// \file   ctaaSigPrepTx.c
///
/// \brief  
///
/// \descr  Init and Cyclic Runnables for SigPrep Tx 
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <ctaaSigPrepTx.h>
#include <SigPrepTx.h>
#include <SigPrepRx.h>
#include <Bsw/Sys/Load/SysLoad.h>
#include <p_NM.h>
#ifdef SYS_LOAD_RUNNABLE
SYS_LOAD_MEAS_VAR_DEC(riSigPrepTx_Init)
SYS_LOAD_MEAS_VAR_DEC(rpSigPrepTx_Cycle)
#endif

//-----------------------------------------------------------------------------
// functions
//-----------------------------------------------------------------------------

/// ---------------------------------------------------------------------------
/// \func     riSigPrepTx_Init
///
/// \brief    Init runnable
///
/// \param    none
///
/// \return   none
///
/// \descr    
/// ---------------------------------------------------------------------------
void riSigPrepTx_Init(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(riSigPrepTx_Init)
#endif

  SigPrepTx_Init();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(riSigPrepTx_Init)
#endif
}


/// ---------------------------------------------------------------------------
/// \func     rpSigPrepTx_Cycle0 
///
/// \brief    Cyclic runnable at every 10 ms
///
/// \param    none
///
/// \return   none
///
/// \descr    
/// ---------------------------------------------------------------------------
void rpSigPrepTx_Cycle(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(rpSigPrepTx_Cycle)
#endif

  SigPrepTx_Cycle0();
  SigPrepTx_CommStackDataRouter();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(rpSigPrepTx_Cycle)
#endif
}


//-----------------------------------------------------------------------------
/// \brief  reSigPrepTx_SendFrame457
///
/// \descr  Runnable event for triggering frame 0x457 transmission
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void reSigPrepTx_SendFrame457(void)
{
  tSysMon_SendFrame457 stData;
  (void)Rte_Read_SysMon_SendFrame457(&stData);

#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // Inhibit DBL HMI if DBL option is not available in coding
  boolean boDbl_Enable = Cod_Dbl_Enable();
  stData.ucDynamicBendingBeamFault = (boDbl_Enable != FALSE) ? stData.ucDynamicBendingBeamFault : 0u;

  // Inhibit LVL HMI if ADL option is not available in coding
  boolean boAdl_Enable = Cod_AvacStp_Enable();
  stData.ucLevellingAdjustFault = (boAdl_Enable != FALSE) ? stData.ucLevellingAdjustFault : 0u;

  // Inhibit GFHB_Fault HMI if GFHB, TSAG, Curtain Effect or Motorway options are not available in coding
  boolean boGFHB_Enable           = Cod_GFHB_Enable();
  boolean boTSAG_Enable           = Cod_TSAG_Enable();
  boolean boCurtainEffect_Enable  = Cod_CurtainEffect_Enable();
  boolean boMotorway_Enable       = Cod_Motorway_Enable();
  stData.ucGfhbFault = ((boGFHB_Enable == FALSE) || (boTSAG_Enable == FALSE) || (boCurtainEffect_Enable == FALSE) || (boMotorway_Enable == FALSE)) ? 0u : stData.ucGfhbFault;

  // Send status
  (void)LGM_SendMessage(DIAG_DBL, &stData.ucDynamicBendingBeamFault);
  (void)LGM_SendMessage(RL_GFHB_FAULT, &stData.ucGfhbFault);
  (void)LGM_SendMessage(DIAG_SBL_RL, &stData.ucStaticBendingBeamFault);

#elif defined (CFG_VARIANT_ECO)
  // Inhibit LVL HMI if ASL option is not available in coding
  boolean boAsl_Enable = Cod_Asl_Enable();
  stData.ucLevellingAdjustFault = (boAsl_Enable != FALSE) ? stData.ucLevellingAdjustFault : 0u;
#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)

  (void)LGM_SendMessage(DIAG_LVL, &stData.ucLevellingAdjustFault);
  (void)LGM_SendMessage(DIAG_LB_RL, &stData.ucLowBeamFault);
  (void)LGM_SendMessage(DIAG_TI_L_F_S, &stData.ucFrontTurnIndicatorFault);
}// PRQA S 5324 1 // Program architecture and readability


//-----------------------------------------------------------------------------
/// \brief  reSigPrepTx_SendFrame477
///
/// \descr  Runnable event for triggering frame 0x477 transmission
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void reSigPrepTx_SendFrame477(void)
{
  tSysMon_SendFrame477 stData;
  (void)Rte_Read_SysMon_SendFrame477(&stData);

#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // Inhibit GFHB_Fault HMI if GFHB, TSAG, Curtain Effect or Motorway options are not available in coding
  boolean boGFHB_Enable           = Cod_GFHB_Enable();
  boolean boTSAG_Enable           = Cod_TSAG_Enable();
  boolean boCurtainEffect_Enable  = Cod_CurtainEffect_Enable();
  boolean boMotorway_Enable       = Cod_Motorway_Enable();
  stData.ucGfhbFault = ((boGFHB_Enable == FALSE) || (boTSAG_Enable == FALSE) || (boCurtainEffect_Enable == FALSE) || (boMotorway_Enable == FALSE)) ? 0u : stData.ucGfhbFault;

  // Send status
  (void)LGM_SendMessage(RL_GFHB_FAULT, &stData.ucGfhbFault);
  (void)LGM_SendMessage(DIAG_SBL_RL, &stData.ucStaticBendingBeamFault);
#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)
#if defined (CFG_VARIANT_ECO) || defined (UNIT_TEST) // Applicable only for ECO version
  // Inhibit LVL HMI if ASL option is not available in coding
  boolean boAsl_Enable = Cod_Asl_Enable();
  stData.ucLevellingAdjustFaultR = (boAsl_Enable != FALSE) ? stData.ucLevellingAdjustFaultR : 0u;

  (void)LGM_SendMessage(DIAG_LVL_R_TX, &stData.ucLevellingAdjustFaultR);
#endif // (CFG_VARIANT_ECO) || (UNIT_TEST)
  (void)LGM_SendMessage(DIAG_LB_RL, &stData.ucLowBeamFault);
  (void)LGM_SendMessage(DIAG_TI_R_F_S, &stData.ucFrontTurnIndicatorFault);
}

// EOF

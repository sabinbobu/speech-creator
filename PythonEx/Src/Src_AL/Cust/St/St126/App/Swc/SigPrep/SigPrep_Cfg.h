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
/// \file   SigPrep_Cfg.h
///
/// \brief  SigPrep Config file
///
/// \descr  Config tables for SigPrep Tx, SigPrep Rx
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef __SIG_PREP_CFG_H__
#define __SIG_PREP_CFG_H__

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include <SigPrep_Mac.h>
#include <SigPrep_Types.h>

//-----------------------------------------------------------------------------
// include for callbacks
//-----------------------------------------------------------------------------
#include <SigPrepRx_Callbacks.h>
#include <SigPrepTx_Callbacks.h>

//-----------------------------------------------------------------------------
// defines
//-----------------------------------------------------------------------------

//----------------------------------------------------
// map of receive frames handled by SigPrepRx
//----------------------------------------------------
// Precheck callback           : Precheck callback of Rx frame
// callback                    : Callback function
//----------------------------------------------------
//                    Precheck callback                  ,           callback
BEGIN_SIG_PREP_RX_MAP
  SIGPREP_CAN_RX_FRM(                            NULL_PTR,           SigPrep_RxCallbacks_HS6_ACQ_NEW_JDD_55F       )
  SIGPREP_CAN_RX_FRM(                            NULL_PTR,           SigPrep_RxCallbacks_HS6_DAT_VSM_36E           )
  SIGPREP_CAN_RX_FRM(                            NULL_PTR,           SigPrep_RxCallbacks_HS6_DAT_VSM_3AE           )
  SIGPREP_CAN_RX_FRM(                            NULL_PTR,           SigPrep_RxCallbacks_HS6_DAT_VSM_54D           )
  SIGPREP_CAN_RX_FRM(                            NULL_PTR,           SigPrep_RxCallbacks_HS6_DAT4_V2_BSI_552       )
  SIGPREP_CAN_RX_FRM(                            NULL_PTR,           SigPrep_RxCallbacks_HS6_DYN3_CMM_468          )
  SIGPREP_CAN_RX_FRM(                            NULL_PTR,           SigPrep_RxCallbacks_HS6_INTE_ELECTRON_BSI_092 )
  SIGPREP_CAN_RX_FRM(                            NULL_PTR,           SigPrep_RxCallbacks_HS6_DYN_VSM_257           )
  SIGPREP_CAN_RX_FRM( SigPrep_RxCallback_SideCheck_2B7_RX,           SigPrep_RxCallbacks_HS6_DYN_BEMP_2B7_RX       )
  SIGPREP_CAN_RX_FRM(                            NULL_PTR,           SigPrep_RxCallbacks_HS6_DYN2_FRE_3CD          )
#if defined (CFG_VARIANT_ECO) || (UNIT_TEST) // Applicable only for ECO version
  SIGPREP_CAN_RX_FRM( SigPrep_RxCallback_SideCheck_477_RX,           SigPrep_RxCallbacks_HS6_DIAG_DRVLED_R_477_RX  )
#endif
#if defined (CFG_VARIANT_FULL) || (UNIT_TEST) // Applicable only for FULL version
  SIGPREP_CAN_RX_FRM( SigPrep_RxCallback_SideCheck_4D7_RX,           SigPrep_RxCallbacks_HS6_DAT2_DRVLED_R_4D7_RX  )
  SIGPREP_CAN_RX_FRM(                            NULL_PTR,           SigPrep_RxCallbacks_HS6_DAT_CSS_350           )
  SIGPREP_CAN_RX_FRM( SigPrep_RxCallback_SideCheck_297_RX,           SigPrep_RxCallbacks_HS6_DAT_DRVLED_R_297_RX   )
  SIGPREP_CAN_RX_FRM(                            NULL_PTR,           SigPrep_RxCallbacks_HS6_DYN_VSM_28E           )
  SIGPREP_CAN_RX_FRM(                            NULL_PTR,           SigPrep_RxCallbacks_HS6_DAT_VSM_32E           )
  SIGPREP_CAN_RX_FRM(                            NULL_PTR,           SigPrep_RxCallbacks_HS6_DAT7_BSI_612          )
  SIGPREP_CAN_RX_FRM(                            NULL_PTR,           SigPrep_RxCallbacks_HS6_DYN_VSM_0AB           )
  SIGPREP_CAN_RX_FRM(                            NULL_PTR,           SigPrep_RxCallbacks_HS6_DYN_VSM_0C3           )
  SIGPREP_CAN_RX_FRM(                            NULL_PTR,           SigPrep_RxCallbacks_HS6_DYN_VSM_0CB           )
  SIGPREP_CAN_RX_FRM(                            NULL_PTR,           SigPrep_RxCallbacks_HS6_DYN_VSM_0E3           )
  SIGPREP_CAN_RX_FRM(                            NULL_PTR,           SigPrep_RxCallbacks_HS6_DYN_VSM_0EB           )
  SIGPREP_CAN_RX_FRM(                            NULL_PTR,           SigPrep_RxCallbacks_HS6_DYN_VSM_103           )
  SIGPREP_CAN_RX_FRM(                            NULL_PTR,           SigPrep_RxCallbacks_HS6_DYN_VSM_10B           )
  SIGPREP_CAN_RX_FRM(                            NULL_PTR,           SigPrep_RxCallbacks_HS6_DYN_VSM_123           )
  SIGPREP_CAN_RX_FRM(                            NULL_PTR,           SigPrep_RxCallbacks_HS6_DYN_VSM_12B           )
  SIGPREP_CAN_RX_FRM(                            NULL_PTR,           SigPrep_RxCallbacks_HS6_DYN_VSM_143           )
  SIGPREP_CAN_RX_FRM(                            NULL_PTR,           SigPrep_RxCallbacks_HS6_DYN_VSM_14B           )
  SIGPREP_CAN_RX_FRM(                            NULL_PTR,           SigPrep_RxCallbacks_HS6_DYN_VSM_163           )
  SIGPREP_CAN_RX_FRM(                            NULL_PTR,           SigPrep_RxCallbacks_HS6_DYN_VSM_16B           )
  SIGPREP_CAN_RX_FRM(                            NULL_PTR,           SigPrep_RxCallbacks_HS6_DYN_VSM_183           )
  SIGPREP_CAN_RX_FRM(                            NULL_PTR,           SigPrep_RxCallbacks_HS6_DYN_VSM_18B           )
  SIGPREP_CAN_RX_FRM(                            NULL_PTR,           SigPrep_RxCallbacks_HS6_DYN_VSM_1AB           )
#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)
END_SIG_PREP_RX_MAP


//----------------------------------------------------
// map of transmit frames handled by SigPrepTx
//----------------------------------------------------
// Frame for Side              : For what Ecu Identity side is this frame
// Nack Timeout                : Not Acknowledged Timeout
// Cyclic Callback             : Periodic frame update Callback
// Trigger Callback            : Event frame trigger
// Nack Callback               : Not Acnowledged Timeout Callback
//----------------------------------------------------
BEGIN_SIG_PREP_TX_MAP
  SIGPREP_CAN_TX_FRM(  eLeftTxFrame,         60u,         SigPrep_TxCallbacks_CyclicFrame_2B7,                                  NULL_PTR,         SigPrep_TxCallbacks_ToFrame_2B7)
  SIGPREP_CAN_TX_FRM(  eLeftTxFrame,       3000u,         SigPrep_TxCallbacks_CyclicFrame_5x7,                                  NULL_PTR,         SigPrep_TxCallbacks_ToFrame_5x7)
#if defined (CFG_VARIANT_FULL) || (UNIT_TEST) // Applicable only for FULL version
  SIGPREP_CAN_TX_FRM( eRightTxFrame,         60u,         SigPrep_TxCallbacks_CyclicFrame_297,                                  NULL_PTR,         SigPrep_TxCallbacks_ToFrame_297)
  SIGPREP_CAN_TX_FRM( eRightTxFrame,        300u,         SigPrep_TxCallbacks_CyclicFrame_4D7,                                  NULL_PTR,         SigPrep_TxCallbacks_ToFrame_4D7)
#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)
  SIGPREP_CAN_TX_FRM( eRightTxFrame,       3000u,         SigPrep_TxCallbacks_CyclicFrame_5x7,                                  NULL_PTR,         SigPrep_TxCallbacks_ToFrame_5x7)
END_SIG_PREP_TX_MAP


/* begin Fileversion check */
/*For sefaty reason,do not define SKIP_MAGIC_NUMBER*/
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
#if MAGIC_NUMBER != 371832701
#error "The CAN driver generated may not fit to 40e Shadow Register Index assigned previous. Please check can_par.h file and adjust it! "
#endif
#else
#define MAGIC_NUMBER 371832701
#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

#endif // __SIG_PREP_CFG_H__

// EOF

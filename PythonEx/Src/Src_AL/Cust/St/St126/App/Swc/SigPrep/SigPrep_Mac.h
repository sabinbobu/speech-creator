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
/// \file   SigPrep_Mac.h
///
/// \brief  Macro definitions
/// 
/// \descr  Specific macros for SigPrep module are defined here
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef __SIG_PREP_MAC_H__
#define __SIG_PREP_MAC_H__

//-----------------------------------------------------------------------------
// Macro defines
//-----------------------------------------------------------------------------

#ifdef BEGIN_SIG_PREP_RX_MAP
#undef BEGIN_SIG_PREP_RX_MAP
#endif
#ifdef SIGPREP_CAN_RX_FRM
#undef SIGPREP_CAN_RX_FRM
#endif
#ifdef END_SIG_PREP_RX_MAP
#undef END_SIG_PREP_RX_MAP
#endif
#ifdef BEGIN_SIG_PREP_TX_MAP
#undef BEGIN_SIG_PREP_TX_MAP
#endif
#ifdef SIGPREP_CAN_TX_FRM
#undef SIGPREP_CAN_TX_FRM
#endif
#ifdef END_SIG_PREP_TX_MAP
#undef END_SIG_PREP_TX_MAP
#endif

#if defined(SIGPREP_TX_FRM_CONFIG)

#define BEGIN_SIG_PREP_RX_MAP
#define SIGPREP_CAN_RX_FRM(PreCheckCb, callback)
#define END_SIG_PREP_RX_MAP

#define BEGIN_SIG_PREP_TX_MAP                                                               STATIC_AL tsSigPrep_TxFrameInfoConst asSigPrepCanTxFrameInfoConst[] = {
#define SIGPREP_CAN_TX_FRM(side, msgTimeout, CyclicCb, TrgCb, TimeoutCb)                    { side, FALSE, FALSE,  msgTimeout, 0xFFFFFFFFU, CyclicCb,  TrgCb, TimeoutCb },
#define END_SIG_PREP_TX_MAP                                                                 };

#elif defined (SIGPREP_TX_ENUM_FRM_CONFIG)

#define BEGIN_SIG_PREP_RX_MAP
#define SIGPREP_CAN_RX_FRM(PreCheckCb, callback)
#define END_SIG_PREP_RX_MAP

#define BEGIN_SIG_PREP_TX_MAP                                                               typedef enum  {
#define SIGPREP_CAN_TX_FRM(side, msgTimeout, CyclicCb, TrgCb, TimeoutCb)                    msgHdl##_Idx ,
#define END_SIG_PREP_TX_MAP                                                                 SigPrep_EndFrm_Idx }teSigPrepTx_FrmlNames_EnumType;

#elif defined(SIGPREP_RX_FRM_CONFIG)

#define BEGIN_SIG_PREP_RX_MAP                                                               STATIC_AL tsSigPrep_RxFrameInfoConst asSigPrepCanRxFrameInfoConst[] = {
#define SIGPREP_CAN_RX_FRM(PreCheckCb, callback)                                            { PreCheckCb, FALSE, FALSE, callback },
#define END_SIG_PREP_RX_MAP                                                                 };

#define BEGIN_SIG_PREP_TX_MAP
#define SIGPREP_CAN_TX_FRM(side, msgTimeout, CyclicCb, TrgCb, TimeoutCb)
#define END_SIG_PREP_TX_MAP

#elif defined (SIGPREP_RX_ENUM_TIMEOUT_CONFIG)

#define BEGIN_SIG_PREP_RX_MAP                                                               typedef enum teSigPrep_RxSignalNames_EnumType {
#define SIGPREP_CAN_RX_FRM(flgHdlTimeout, PreCheckCb, flgHdlUpdate, callback)               SigPrep_X##flgHdlTimeout ,
#define END_SIG_PREP_RX_MAP                                                                 };

#define BEGIN_SIG_PREP_TX_MAP
#define SIGPREP_CAN_TX_FRM(side, msgTimeout, CyclicCb, TrgCb, TimeoutCb)
#define END_SIG_PREP_TX_MAP

#elif defined (SIGPREP_RX_ENUM_FRM_CONFIG)

#define BEGIN_SIG_PREP_RX_MAP                                                               typedef enum  {
#define SIGPREP_CAN_RX_FRM(PreCheckCb, callback)                                            msgHdl##_Idx ,
#define END_SIG_PREP_RX_MAP                                                                 SigPrep_LastFrm_Idx }teSigPrepRx_FrmlNames_EnumType;

#define BEGIN_SIG_PREP_TX_MAP
#define SIGPREP_CAN_TX_FRM(side, msgTimeout, CyclicCb, TrgCb, TimeoutCb)
#define END_SIG_PREP_TX_MAP

#elif defined (SIGPREP_NO_MACRO_GENERATED)

#define BEGIN_SIG_PREP_RX_MAP
#define SIGPREP_CAN_RX_FRM(PreCheckCb, callback)
#define END_SIG_PREP_RX_MAP

#define BEGIN_SIG_PREP_TX_MAP
#define SIGPREP_CAN_TX_FRM(side, msgTimeout, CyclicCb, TrgCb, TimeoutCb)
#define END_SIG_PREP_TX_MAP

#else
#error "Sigprep configuration undefined, please select the correct one!"
#endif

#endif // __SIG_PREP_MAC_H__

// EOF

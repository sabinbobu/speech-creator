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
/// \file   SysMon_Mac.h
///
/// \brief  Macro definitions
/// 
/// \descr  Specific macros for SysMon module are defined here
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef __SYS_MON_MAC_H__
#define __SYS_MON_MAC_H__

//-----------------------------------------------------------------------------
// Macro defines
//-----------------------------------------------------------------------------

#ifdef BEGIN_SYS_MON_RX_MAP
#undef BEGIN_SYS_MON_RX_MAP
#endif
#ifdef SYSMON_CAN_RX_FRM
#undef SYSMON_CAN_RX_FRM
#endif
#ifdef END_SYS_MON_RX_MAP
#undef END_SYS_MON_RX_MAP
#endif
#ifdef BEGIN_SYS_MON_TX_MAP
#undef BEGIN_SYS_MON_TX_MAP
#endif
#ifdef SYSMON_CAN_TX_FRM
#undef SYSMON_CAN_TX_FRM
#endif
#ifdef END_SYS_MON_TX_MAP
#undef END_SYS_MON_TX_MAP
#endif

#if defined(SYSMON_TX_FRM_CONFIG)

#define BEGIN_SYS_MON_RX_MAP
#define SYSMON_CAN_RX_FRM(callback)
#define END_SYS_MON_RX_MAP

#define BEGIN_SYS_MON_TX_MAP                                                               STATIC_AL tsSysMon_TxFrameInfoConst asSysMonCanTxFrameInfoConst[] = {
#define SYSMON_CAN_TX_FRM(side, msgTimeout, CyclicCb, TimeoutCb)                           { side, FALSE, msgTimeout, 0xFFFFFFFFU, CyclicCb, TimeoutCb },
#define END_SYS_MON_TX_MAP                                                                 };

#elif defined (SYSMON_TX_ENUM_FRM_CONFIG)

#define BEGIN_SYS_MON_RX_MAP
#define SYSMON_CAN_RX_FRM(callback)
#define END_SYS_MON_RX_MAP

#define BEGIN_SYS_MON_TX_MAP                                                               typedef enum  {
#define SYSMON_CAN_TX_FRM(side, msgTimeout, CyclicCb, TimeoutCb)                           msgHdl##_Idx ,
#define END_SYS_MON_TX_MAP                                                                 SysMon_EndFrm_Idx }teSysMonTx_FrmlNames_EnumType;

#elif defined(SYSMON_RX_FRM_CONFIG)

#define BEGIN_SYS_MON_RX_MAP                                                               STATIC_AL tsSysMon_RxFrameInfoConst asSysMonCanRxFrameInfoConst[] = {
#define SYSMON_CAN_RX_FRM(callback)                                                        { FALSE, FALSE, callback },
#define END_SYS_MON_RX_MAP                                                                 };

#define BEGIN_SYS_MON_TX_MAP
#define SYSMON_CAN_TX_FRM(side, msgTimeout, CyclicCb, TimeoutCb)
#define END_SYS_MON_TX_MAP

#elif defined (SYSMON_RX_ENUM_TIMEOUT_CONFIG)

#define BEGIN_SYS_MON_RX_MAP                                                               typedef enum teSysMon_RxSignalNames_EnumType {
#define SYSMON_CAN_RX_FRM(flgHdlTimeout, PreCheckCb, flgHdlUpdate, callback)               SysMon_X##flgHdlTimeout ,
#define END_SYS_MON_RX_MAP                                                                 };

#define BEGIN_SYS_MON_TX_MAP
#define SYSMON_CAN_TX_FRM(side, msgTimeout, CyclicCb, TimeoutCb)
#define END_SYS_MON_TX_MAP

#elif defined (SYSMON_RX_ENUM_FRM_CONFIG)

#define BEGIN_SYS_MON_RX_MAP                                                               typedef enum  {
#define SYSMON_CAN_RX_FRM(callback)                                                        msgHdl##_Idx ,
#define END_SYS_MON_RX_MAP                                                                 SysMon_LastFrm_Idx }teSysMonRx_FrmlNames_EnumType;

#define BEGIN_SYS_MON_TX_MAP
#define SYSMON_CAN_TX_FRM(side, msgTimeout, CyclicCb, TimeoutCb)
#define END_SYS_MON_TX_MAP

#elif defined (SYSMON_NO_MACRO_GENERATED)

#define BEGIN_SYS_MON_RX_MAP
#define SYSMON_CAN_RX_FRM(callback)
#define END_SYS_MON_RX_MAP

#define BEGIN_SYS_MON_TX_MAP
#define SYSMON_CAN_TX_FRM(side, msgTimeout, CyclicCb, TimeoutCb)
#define END_SYS_MON_TX_MAP

#else
#error "SysMon configuration undefined, please select the correct one!"
#endif

#endif // __SYS_MON_MAC_H__

// EOF

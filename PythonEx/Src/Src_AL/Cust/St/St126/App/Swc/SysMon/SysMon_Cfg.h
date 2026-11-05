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
/// \file   SysMon_Cfg.h
///
/// \brief  SysMon Config file
///
/// \descr  Config tables for SysMon Rx
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef __SYS_MON_CFG_H__
#define __SYS_MON_CFG_H__

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include <SysMon_Mac.h>
#include <SysMon_Types.h>

//-----------------------------------------------------------------------------
// include for callbacks
//-----------------------------------------------------------------------------
#include <SysMonRx_Callbacks.h>
#include <SysMonTx_Callbacks.h>

//-----------------------------------------------------------------------------
// defines
//-----------------------------------------------------------------------------
#define SYSMON_DIAG_ERR_ID_UNKNOWN                 0xFFu
#define SYSMON_DIAG_STATUS_LED_OFF                 2u      // -  eRteCddLed_Disabled = 2,         // LED off
#define SYSMON_DIAG_STATUS_ERR_OK                  4u      // -  eRteCddLed_StatusOk = 4,         // normal operation
#define SYSMON_DIAG_ERR_OPEN_LOAD                  5u      // 0  eRteCddLed_ErrOpenLoad = 5,      // open load
#define SYSMON_DIAG_ERR_SHORT_TO_GND               6u      // 1  eRteCddLed_ErrShortToGnd = 6,    // short to GND
#define SYSMON_DIAG_ERR_SHORT_TO_BAT               7u      // 2  eRteCddLed_ErrShortToUbat = 7,   // short to Ubat
#define SYSMON_DIAG_ERR_VOLTAGE_LOW                8u      // 3  eRteCddLed_ErrUnderVoltage = 8,  // voltage of LED string too low
#define SYSMON_DIAG_ERR_VOLTAGE_HIGH               9u      // 4  eRteCddLed_ErrOverVoltage = 9,   // voltage of LED string too high
#define SYSMON_DIAG_ERR_THERM_SHUT_DOWN            10u     // 5  eRteCddLed_ErrThermShutdn = 10,  // thermal shutdown
#define SYSMON_DIAG_ERR_OVER_CURRENT               11u     // 6  eRteCddLed_ErrOvercurrent = 11,  // overcurrent
#define SYSMON_DIAG_ERR_SPI                        12u     // 7  eRteCddLed_ErrSpi = 12,          // SPI error
#define SYSMON_DIAG_ERR_CRC                        13u     // 8  eRteCddLed_ErrCrc = 13,          // CRC error
#define SYSMON_DIAG_ERR_BOOST                      14u     // 8  eRteCddLed_ErrCrc = 13,          // CRC error
#define SYSMON_DIAG_MAX_CNT                        (SYSMON_DIAG_ERR_BOOST + 1U)
#define SYSMON_DIAG_MAX_STATUS_CNT                 SYSMON_DIAG_MAX_CNT
#define SYSMON_DIAG_MAX_ERR_ARRAY                  (SYSMON_DIAG_MAX_STATUS_CNT - SYSMON_DIAG_STATUS_ERR_OK)
#define SYSMON_DIAG_START_ERR_CNT                  SYSMON_DIAG_ERR_OPEN_LOAD

#define SYSMON_CFG_LED_CHANNELS_NR                   CFG_LED_CHANNELS_NR
#define SYSMON_CFG_NR_OF_LOGICAL_UNITS               CFG_LOGICAL_UNITS
#define SYSMON_CFG_MAX_BUCK_DRV                      12u //coding driver type
#define SYSMON_CFG_MAX_LMM_SW_NO                     12u //max switch number allowed
#define SYSMON_CFG_MAX_LMM_DRV                       7u  //coding LMM type

//----------------------------------------------------
// map of receive frames handled by SysMonRx
//----------------------------------------------------
// callback                    : Callback function
//----------------------------------------------------
//                    callback
BEGIN_SYS_MON_RX_MAP
  SYSMON_CAN_RX_FRM(  SysMon_RxCallbacks_HS6_DAT_VSM_2AE  )
  SYSMON_CAN_RX_FRM(  SysMon_RxCallbacks_HS6_DAT_VSM_34E  )
  SYSMON_CAN_RX_FRM(  SysMon_RxCallbacks_HS6_COMMANDES_VSM_036  )
  SYSMON_CAN_RX_FRM(  SysMon_RxCallbacks_HS6_DAT_BSI_432  )
  SYSMON_CAN_RX_FRM(  SysMon_RxCallbacks_HS6_DYN_ABR_38D  )
END_SYS_MON_RX_MAP

//----------------------------------------------------
// map of transmit frames handled by SysMonTx
//----------------------------------------------------
// Frame for Side              : For what Ecu Identity side is this frame
// Nack Timeout                : Not Acknowledged Timeout
// Cyclic Callback             : Periodic frame update Callback
// Nack Callback               : Not Acnowledged Timeout Callback
//----------------------------------------------------
BEGIN_SYS_MON_TX_MAP
  SYSMON_CAN_TX_FRM(  eSysMonLeftTxFrame,   600u,     SysMon_TxCallbacks_CyclicFrame_457,       SysMon_TxCallbacks_ToFrame_4x7)
  SYSMON_CAN_TX_FRM( eSysMonRightTxFrame,   600u,     SysMon_TxCallbacks_CyclicFrame_477,       SysMon_TxCallbacks_ToFrame_4x7)
END_SYS_MON_TX_MAP


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

#endif // __SYS_MON_CFG_H__

// EOF

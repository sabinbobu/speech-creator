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
/// \file   CddTps92520_Sched.h
///
/// \brief  Schedule table for TPS92520
///
/// \author OTT, Peter ALDE-RT/EES6
//-----------------------------------------------------------------------------
#ifndef CDD_TPS92520_SCHED_2021_01_21_H_
#define CDD_TPS92520_SCHED_2021_01_21_H_

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <Std_Types.h>

#include <../Gen/CddTps92520_Types.h>
#include <../Cfg/CddTps92520_Cfg.h>

//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------
// Actions executed synchrone with SPI schedule Table before a SPI Tx
#define CDDTPS92520_NO_ACT         0u
#define CDDTPS92520_ST_GETVIN      1u
#define CDDTPS92520_ST_GETVLED     2u
#define CDDTPS92520_ST_GETVLEDON   3u


//-----------------------------------------------------------------------------
//  SPI scheduling configuration
//-----------------------------------------------------------------------------
#define CDDTPS92520_Cfg_SpiSchedTableLen 112u

#define CDDTPS92520_Cfg_SpiSchedTable_Init                                                                                                             \
{                                                                                                                                                      \
  /* next       Optional                    Read/Write                     Register                    Data                   Data                  */ \
  /* state      action                      command                        address                     to transmit            to receive            */ \
  /*---------------------- Init sequence -----------------------------------------------------------------------------------------------------------*/ \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrRESET_Tx,      CDDTPS92520_RESET_Tx,     CDDTPS92520_Dummy_Rx      }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrSYSCFG1_Tx,    CDDTPS92520_SYSCFG1_Tx,   CDDTPS92520_Dummy_Rx      }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrSTATUS3_Tx,    CDDTPS92520_Zero_Tx,      CDDTPS92520_SYSCFG1_Rx    }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrSYSCFG2_Tx,    CDDTPS92520_SYSCFG2_Tx,   CDDTPS92520_STATUS3_Rx    }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrCMWTAP_Tx,     CDDTPS92520_CMWTAP_Tx,    CDDTPS92520_SYSCFG2_Rx    }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrTWLMT_Tx,      CDDTPS92520_TWLMT_Tx,     CDDTPS92520_CMWTAP_Rx     }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrSLEEP_Tx,      CDDTPS92520_SLEEP_Tx,     CDDTPS92520_TWLMT_Rx      }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrCH1IADJH_Tx,   CDDTPS92520_CH1IADJH_Tx,  CDDTPS92520_SLEEP_Rx      }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrCH1IADJL_Tx,   CDDTPS92520_CH1IADJL_Tx,  CDDTPS92520_CH1IADJH_Rx   }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrCH2IADJH_Tx,   CDDTPS92520_CH2IADJH_Tx,  CDDTPS92520_CH1IADJL_Rx   }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrCH2IADJL_Tx,   CDDTPS92520_CH2IADJL_Tx,  CDDTPS92520_CH2IADJH_Rx   }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrPWMDIV_Tx,     CDDTPS92520_PMWDIV_Tx,    CDDTPS92520_CH2IADJL_Rx   }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrCH1PWMH_Tx,    CDDTPS92520_CH1PWMH_Tx,   CDDTPS92520_PMWDIV_Rx     }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrCH1PWML_Tx,    CDDTPS92520_CH1PWML_Tx,   CDDTPS92520_CH1PWMH_Rx    }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrCH2PWMH_Tx,    CDDTPS92520_CH2PWMH_Tx,   CDDTPS92520_CH1PWML_Rx    }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrCH2PWML_Tx,    CDDTPS92520_CH2PWML_Tx,   CDDTPS92520_CH2PWMH_Rx    }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrCH1TON_Tx,     CDDTPS92520_CH1TON_Tx,    CDDTPS92520_CH2PWML_Rx    }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrCH2TON_Tx,     CDDTPS92520_CH2TON_Tx,    CDDTPS92520_CH1TON_Rx     }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrCH1VIN_Tx,     CDDTPS92520_Zero_Tx,      CDDTPS92520_CH2TON_Rx     }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrCH2VIN_Tx,     CDDTPS92520_Zero_Tx,      CDDTPS92520_CH1VIN_Rx     }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrCH1VLED_Tx,    CDDTPS92520_Zero_Tx,      CDDTPS92520_CH2VIN_Rx     }, \
  {  +1, CDDTPS92520_ST_GETVIN,      CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrCH2VLED_Tx,    CDDTPS92520_Zero_Tx,      CDDTPS92520_CH1VLED_Rx    }, \
  {  +1, CDDTPS92520_ST_GETVIN,      CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrCH1VLEDON_Tx,  CDDTPS92520_Zero_Tx,      CDDTPS92520_CH2VLED_Rx    }, \
  {  +1, CDDTPS92520_ST_GETVIN,      CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrCH2VLEDON_Tx,  CDDTPS92520_Zero_Tx,      CDDTPS92520_CH1VLEDON_Rx  }, \
  {  +1, CDDTPS92520_ST_GETVIN,      CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrTEMPL_Tx,      CDDTPS92520_Zero_Tx,      CDDTPS92520_CH2VLEDON_Rx  }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrTEMPH_Tx,      CDDTPS92520_Zero_Tx,      CDDTPS92520_TEMPL_Rx      }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrV5D_Tx,        CDDTPS92520_Zero_Tx,      CDDTPS92520_TEMPH_Rx      }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrLHCFG1_Tx,     CDDTPS92520_LHCFG1_Tx,    CDDTPS92520_V5D_Rx        }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrSTATUS1_Tx,    CDDTPS92520_Zero_Tx,      CDDTPS92520_LHCFG1_Rx     }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrSTATUS2_Tx,    CDDTPS92520_Zero_Tx,      CDDTPS92520_STATUS1_Rx    }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrSTATUS3_Tx,    CDDTPS92520_Zero_Tx,      CDDTPS92520_STATUS2_Rx    }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrCH2VLEDOFF_Tx, CDDTPS92520_Zero_Tx,      CDDTPS92520_STATUS3_Rx    }, \
  /*----------------- Cyclic 0ms -------------------------------------------------------------------------------------------------------------------*/ \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrSYSCFG1_Tx,    CDDTPS92520_SYSCFG1_Tx,   CDDTPS92520_Dummy_Rx      }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrSTATUS1_Tx,    CDDTPS92520_Zero_Tx,      CDDTPS92520_SYSCFG1_Rx    }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrCH1VLED_Tx,    CDDTPS92520_Zero_Tx,      CDDTPS92520_STATUS1_Rx    }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrCH2VLED_Tx,    CDDTPS92520_Zero_Tx,      CDDTPS92520_CH1VLED_Rx    }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrCH1VLEDON_Tx,  CDDTPS92520_Zero_Tx,      CDDTPS92520_CH2VLED_Rx    }, \
  {  +1, CDDTPS92520_ST_GETVLED,     CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrCH2VLEDON_Tx,  CDDTPS92520_Zero_Tx,      CDDTPS92520_CH1VLEDON_Rx  }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrCH1IADJH_Tx,   CDDTPS92520_CH1IADJH_Tx,  CDDTPS92520_CH2VLEDON_Rx  }, \
  {  +1, CDDTPS92520_ST_GETVLEDON,   CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrCH1IADJL_Tx,   CDDTPS92520_CH1IADJL_Tx,  CDDTPS92520_CH1IADJH_Rx   }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrCH2IADJH_Tx,   CDDTPS92520_CH2IADJH_Tx,  CDDTPS92520_CH1IADJL_Rx   }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrCH2IADJL_Tx,   CDDTPS92520_CH2IADJL_Tx,  CDDTPS92520_CH2IADJH_Rx   }, \
  /*----------------- Cyclic 10ms ------------------------------------------------------------------------------------------------------------------*/ \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrSYSCFG1_Tx,    CDDTPS92520_SYSCFG1_Tx,   CDDTPS92520_CH2IADJL_Rx   }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrSTATUS1_Tx,    CDDTPS92520_Zero_Tx,      CDDTPS92520_SYSCFG1_Rx    }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrCH1VLED_Tx,    CDDTPS92520_Zero_Tx,      CDDTPS92520_STATUS1_Rx    }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrCH2VLED_Tx,    CDDTPS92520_Zero_Tx,      CDDTPS92520_CH1VLED_Rx    }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrCH1VLEDON_Tx,  CDDTPS92520_Zero_Tx,      CDDTPS92520_CH2VLED_Rx    }, \
  {  +1, CDDTPS92520_ST_GETVLED,     CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrCH2VLEDON_Tx,  CDDTPS92520_Zero_Tx,      CDDTPS92520_CH1VLEDON_Rx  }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrSTATUS2_Tx,    CDDTPS92520_Zero_Tx,      CDDTPS92520_CH2VLEDON_Rx  }, \
  {  +1, CDDTPS92520_ST_GETVLEDON,   CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrSTATUS3_Tx,    CDDTPS92520_Zero_Tx,      CDDTPS92520_STATUS2_Rx    }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrTEMPL_Tx,      CDDTPS92520_Zero_Tx,      CDDTPS92520_STATUS3_Rx    }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrTEMPH_Tx,      CDDTPS92520_Zero_Tx,      CDDTPS92520_TEMPL_Rx      }, \
  /*----------------- Cyclic 20ms ------------------------------------------------------------------------------------------------------------------*/ \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrSYSCFG1_Tx,    CDDTPS92520_SYSCFG1_Tx,   CDDTPS92520_TEMPH_Rx      }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrSTATUS1_Tx,    CDDTPS92520_Zero_Tx,      CDDTPS92520_SYSCFG1_Rx    }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrCH1VLED_Tx,    CDDTPS92520_Zero_Tx,      CDDTPS92520_STATUS1_Rx    }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrCH2VLED_Tx,    CDDTPS92520_Zero_Tx,      CDDTPS92520_CH1VLED_Rx    }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrCH1VLEDON_Tx,  CDDTPS92520_Zero_Tx,      CDDTPS92520_CH2VLED_Rx    }, \
  {  +1, CDDTPS92520_ST_GETVLED,     CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrCH2VLEDON_Tx,  CDDTPS92520_Zero_Tx,      CDDTPS92520_CH1VLEDON_Rx  }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrCH1IADJH_Tx,   CDDTPS92520_CH1IADJH_Tx,  CDDTPS92520_CH2VLEDON_Rx  }, \
  {  +1, CDDTPS92520_ST_GETVLEDON,   CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrCH1IADJL_Tx,   CDDTPS92520_CH1IADJL_Tx,  CDDTPS92520_CH1IADJH_Rx   }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrCH2IADJH_Tx,   CDDTPS92520_CH2IADJH_Tx,  CDDTPS92520_CH1IADJL_Rx   }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrCH2IADJL_Tx,   CDDTPS92520_CH2IADJL_Tx,  CDDTPS92520_CH2IADJH_Rx   }, \
  /*----------------- Cyclic 30ms ------------------------------------------------------------------------------------------------------------------*/ \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrSYSCFG1_Tx,    CDDTPS92520_SYSCFG1_Tx,   CDDTPS92520_CH2IADJL_Rx   }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrSTATUS1_Tx,    CDDTPS92520_Zero_Tx,      CDDTPS92520_SYSCFG1_Rx    }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrCH1VLED_Tx,    CDDTPS92520_Zero_Tx,      CDDTPS92520_STATUS1_Rx    }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrCH2VLED_Tx,    CDDTPS92520_Zero_Tx,      CDDTPS92520_CH1VLED_Rx    }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrCH1VLEDON_Tx,  CDDTPS92520_Zero_Tx,      CDDTPS92520_CH2VLED_Rx    }, \
  {  +1, CDDTPS92520_ST_GETVLED,     CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrCH2VLEDON_Tx,  CDDTPS92520_Zero_Tx,      CDDTPS92520_CH1VLEDON_Rx  }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrCH1VIN_Tx,     CDDTPS92520_Zero_Tx,      CDDTPS92520_CH2VLEDON_Rx  }, \
  {  +1, CDDTPS92520_ST_GETVLEDON,   CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrSLEEP_Tx,      CDDTPS92520_SLEEP_Tx,     CDDTPS92520_CH1VIN_Rx     }, \
  {  +1, CDDTPS92520_ST_GETVIN,      CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrSYSCFG2_Tx,    CDDTPS92520_SYSCFG2_Tx,   CDDTPS92520_SLEEP_Rx      }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrCMWTAP_Tx,     CDDTPS92520_CMWTAP_Tx,    CDDTPS92520_SYSCFG2_Rx    }, \
  /*----------------- Cyclic 40ms ------------------------------------------------------------------------------------------------------------------*/ \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrSYSCFG1_Tx,    CDDTPS92520_SYSCFG1_Tx,   CDDTPS92520_CMWTAP_Rx     }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrSTATUS1_Tx,    CDDTPS92520_Zero_Tx,      CDDTPS92520_SYSCFG1_Rx    }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrCH1VLED_Tx,    CDDTPS92520_Zero_Tx,      CDDTPS92520_STATUS1_Rx    }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrCH2VLED_Tx,    CDDTPS92520_Zero_Tx,      CDDTPS92520_CH1VLED_Rx    }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrCH1VLEDON_Tx,  CDDTPS92520_Zero_Tx,      CDDTPS92520_CH2VLED_Rx    }, \
  {  +1, CDDTPS92520_ST_GETVLED,     CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrCH2VLEDON_Tx,  CDDTPS92520_Zero_Tx,      CDDTPS92520_CH1VLEDON_Rx  }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrCH1IADJH_Tx,   CDDTPS92520_CH1IADJH_Tx,  CDDTPS92520_CH2VLEDON_Rx  }, \
  {  +1, CDDTPS92520_ST_GETVLEDON,   CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrCH1IADJL_Tx,   CDDTPS92520_CH1IADJL_Tx,  CDDTPS92520_CH1IADJH_Rx   }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrCH2IADJH_Tx,   CDDTPS92520_CH2IADJH_Tx,  CDDTPS92520_CH1IADJL_Rx   }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrCH2IADJL_Tx,   CDDTPS92520_CH2IADJL_Tx,  CDDTPS92520_CH2IADJH_Rx   }, \
  /*----------------- Cyclic 50ms ------------------------------------------------------------------------------------------------------------------*/ \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrSYSCFG1_Tx,    CDDTPS92520_SYSCFG1_Tx,   CDDTPS92520_CH2IADJL_Rx   }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrSTATUS1_Tx,    CDDTPS92520_Zero_Tx,      CDDTPS92520_SYSCFG1_Rx    }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrCH1VLED_Tx,    CDDTPS92520_Zero_Tx,      CDDTPS92520_STATUS1_Rx    }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrCH2VLED_Tx,    CDDTPS92520_Zero_Tx,      CDDTPS92520_CH1VLED_Rx    }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrCH1VLEDON_Tx,  CDDTPS92520_Zero_Tx,      CDDTPS92520_CH2VLED_Rx    }, \
  {  +1, CDDTPS92520_ST_GETVLED,     CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrCH2VLEDON_Tx,  CDDTPS92520_Zero_Tx,      CDDTPS92520_CH1VLEDON_Rx  }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrSTATUS2_Tx,    CDDTPS92520_Zero_Tx,      CDDTPS92520_CH2VLEDON_Rx  }, \
  {  +1, CDDTPS92520_ST_GETVLEDON,   CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrSTATUS3_Tx,    CDDTPS92520_Zero_Tx,      CDDTPS92520_STATUS2_Rx    }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrCH1TON_Tx,     CDDTPS92520_CH1TON_Tx,    CDDTPS92520_STATUS3_Rx    }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrCH2TON_Tx,     CDDTPS92520_CH2TON_Tx,    CDDTPS92520_CH1TON_Rx     }, \
  /*----------------- Cyclic 60ms ------------------------------------------------------------------------------------------------------------------*/ \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrSYSCFG1_Tx,    CDDTPS92520_SYSCFG1_Tx,   CDDTPS92520_CH2TON_Rx     }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrSTATUS1_Tx,    CDDTPS92520_Zero_Tx,      CDDTPS92520_SYSCFG1_Rx    }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrCH1VLED_Tx,    CDDTPS92520_Zero_Tx,      CDDTPS92520_STATUS1_Rx    }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrCH2VLED_Tx,    CDDTPS92520_Zero_Tx,      CDDTPS92520_CH1VLED_Rx    }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrCH1VLEDON_Tx,  CDDTPS92520_Zero_Tx,      CDDTPS92520_CH2VLED_Rx    }, \
  {  +1, CDDTPS92520_ST_GETVLED,     CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrCH2VLEDON_Tx,  CDDTPS92520_Zero_Tx,      CDDTPS92520_CH1VLEDON_Rx  }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrCH1IADJH_Tx,   CDDTPS92520_CH1IADJH_Tx,  CDDTPS92520_CH2VLEDON_Rx  }, \
  {  +1, CDDTPS92520_ST_GETVLEDON,   CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrCH1IADJL_Tx,   CDDTPS92520_CH1IADJL_Tx,  CDDTPS92520_CH1IADJH_Rx   }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrCH2IADJH_Tx,   CDDTPS92520_CH2IADJH_Tx,  CDDTPS92520_CH1IADJL_Rx   }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrCH2IADJL_Tx,   CDDTPS92520_CH2IADJL_Tx,  CDDTPS92520_CH2IADJH_Rx   }, \
  /*----------------- Cyclic 70ms ------------------------------------------------------------------------------------------------------------------*/ \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrSYSCFG1_Tx,    CDDTPS92520_SYSCFG1_Tx,   CDDTPS92520_CH2IADJL_Rx   }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrSTATUS1_Tx,    CDDTPS92520_Zero_Tx,      CDDTPS92520_SYSCFG1_Rx    }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrCH1VLED_Tx,    CDDTPS92520_Zero_Tx,      CDDTPS92520_STATUS1_Rx    }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrCH2VLED_Tx,    CDDTPS92520_Zero_Tx,      CDDTPS92520_CH1VLED_Rx    }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrCH1VLEDON_Tx,  CDDTPS92520_Zero_Tx,      CDDTPS92520_CH2VLED_Rx    }, \
  {  +1, CDDTPS92520_ST_GETVLED,     CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrCH2VLEDON_Tx,  CDDTPS92520_Zero_Tx,      CDDTPS92520_CH1VLEDON_Rx  }, \
  {  +1, CDDTPS92520_NO_ACT,         CDDTPS92520_ReadCmdBit_Tx,  CDDTPS92520_AddrCH2VIN_Tx,     CDDTPS92520_Zero_Tx,      CDDTPS92520_CH2VLEDON_Rx  }, \
  {  +1, CDDTPS92520_ST_GETVLEDON,   CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrSLEEP_Tx,      CDDTPS92520_SLEEP_Tx,     CDDTPS92520_CH2VIN_Rx     }, \
  {  +1, CDDTPS92520_ST_GETVIN,      CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrTWLMT_Tx,      CDDTPS92520_TWLMT_Tx,     CDDTPS92520_SLEEP_Rx      }, \
  { -79, CDDTPS92520_NO_ACT,         CDDTPS92520_WriteCmdBit_Tx, CDDTPS92520_AddrLHCFG1_Tx,     CDDTPS92520_LHCFG1_Tx,    CDDTPS92520_TWLMT_Rx      }  \
  /*----------------- Cyclic 80ms ------------------------------------------------------------------------------------------------------------------*/ \
}


#endif // CDD_TPS92520_SCHED_2021_01_21_H_

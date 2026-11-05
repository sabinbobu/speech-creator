//*****************************************************************************
// (C) Marelli Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Marelli Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Marelli Automotive Lighting Reutlingen GmbH.
//*****************************************************************************
//-----------------------------------------------------------------------------
/// \file  CddTpsGen3_Sched.h
///
/// \brief
///
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
///
//-----------------------------------------------------------------------------
#ifndef CDD_TPS_GEN3_SCHED_2024_02_05_H
#define CDD_TPS_GEN3_SCHED_2024_02_05_H

//=============================================================================
// Includes
//=============================================================================
#include <CddTpsGen3_Com.h>
#include <CddTpsGen3_Types.h>


//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------

#define  CDDTPSGEN3_ST_NO_ACT             0u
#define  CDDTPSGEN3_ST_ACT_DIS_COMM       1u
#define  CDDTPSGEN3_ST_ACT_EN_COMM        2u
#define  CDDTPSGEN3_ST_ACT_WAIT_ACK       3u
#define  CDDTPSGEN3_ST_ACT_SET_PHASE      4u
#define  CDDTPSGEN3_ST_ACT_SET_PWM        5u
#define  CDDTPSGEN3_ST_ACT_CHECK_START    6u
#define  CDDTPSGEN3_ST_ACT_CHECK_PWR      7u
#define  CDDTPSGEN3_ST_ACT_CFG_CHIP       8u
#define  CDDTPSGEN3_ST_ACT_CFG_LEDS       9u
#define  CDDTPSGEN3_ST_ACT_CHECK_CODING  10u
#define  CDDTPSGEN3_ST_ACT_START_CYCLE   11u
#define  CDDTPSGEN3_ST_ACT_CHECK_RESTART 12u
#define  CDDTPSGEN3_ST_ACT_SYSCFG        13u

#define  CDDTPSGEN3_SIZE_ACKBYTE          1u
#define  CDDTPSGEN3_SIZE_CRCBYTES         2u
#define  CDDTPSGEN3_SIZE_HEADERBYTES      3u

//-----------------------------------------------------------------------------
//  UART scheduling configuration
//-----------------------------------------------------------------------------
#define CDDTPSGEN3_Cfg_UartSchedTableLen          7u    // to be calculated based on the scheduler table !!!
#define CDDTPSGEN3_Cfg_UartSchedTableCycStart     14u   // to be calculated based on the scheduler table !!!


                                                                                                                               
#define CDDTPSGEN3_Cfg_UartSchedTable_Init                                                                                                                                                                                                                                       \
{                                                                                                                                                                                                                                                                                \
         /* next      Optional                          Dynamic               Read/Write                      Register                          Data                             Tx Data                           Data                        Rx Data             */            \
         /* state     action                            command               command(INIT)                   address                        to transmit                         Length                         to receive                     Length              */            \
         /*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/            \
         /*---------    Init sequence   ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/            \
/* 0*/    {  +1,  CDDTPSGEN3_ST_ACT_CHECK_RESTART,  eBroadcastCmd,      CDDTPSGEN3_WRITE_01_BYTES,       CDDTPSGEN3_AddrSYSCFG,            CDDTPSGEN3_SYSCFG_DEFAULT_Tx,    CDDTPSGEN3_LEN_1_BYTE,        CDDTPSGEN3_BROADCAST2_SYSCFG_Rx,      CDDTPSGEN3_LEN_0_BYTES     },    \
/* 1*/    {  +1,  CDDTPSGEN3_ST_ACT_CHECK_START,    eBroadcastCmd,      CDDTPSGEN3_WRITE_01_BYTES,       CDDTPSGEN3_AddrSYSCFG,            CDDTPSGEN3_SYSCFG_DEFAULT_Tx,    CDDTPSGEN3_LEN_1_BYTE,        CDDTPSGEN3_BROADCAST2_SYSCFG_Rx,      CDDTPSGEN3_LEN_0_BYTES     },    \
/* 2*/    {  +1,  CDDTPSGEN3_ST_NO_ACT,             eSingleFASTCmd,     CDDTPSGEN3_READ_01_BYTES,        CDDTPSGEN3_AddrICID,              CDDTPSGEN3_Zero_Tx,              CDDTPSGEN3_LEN_0_BYTES,       CDDTPSGEN3_ICID_Rx,                   CDDTPSGEN3_LEN_3_BYTES     },    \
/* 3*/    {  +1,  CDDTPSGEN3_ST_ACT_SYSCFG,         eSingleFASTCmd,     CDDTPSGEN3_WRITE_03_BYTES,       CDDTPSGEN3_AddrSYSCFG,            CDDTPSGEN3_SYSCFG_Tx,            CDDTPSGEN3_LEN_3_BYTES,       CDDTPSGEN3_SYSCFG_Rx,                 CDDTPSGEN3_LEN_1_BYTE      },    \
/* 4*/    {  +1,  CDDTPSGEN3_ST_ACT_SET_PHASE,      eSingleFASTCmd,     CDDTPSGEN3_WRITE_04_BYTES,       CDDTPSGEN3_AddrPHASE04_01L,       CDDTPSGEN3_PHASE_LSB_Tx,         CDDTPSGEN3_LEN_4_BYTES,       CDDTPSGEN3_PHASES_LSB_Rx,             CDDTPSGEN3_LEN_1_BYTE      },    \
/* 5*/    {  +1,  CDDTPSGEN3_ST_NO_ACT,             eSingleFASTCmd,     CDDTPSGEN3_WRITE_16_BYTES,       CDDTPSGEN3_AddrPHASE01H,          CDDTPSGEN3_PHASE_MSB_Tx,         CDDTPSGEN3_LEN_16_BYTES,      CDDTPSGEN3_PHASES_MSB_Rx,             CDDTPSGEN3_LEN_1_BYTE      },    \
/* 6*/    {  +1,  CDDTPSGEN3_ST_ACT_CFG_LEDS,       eSingleFASTCmd,     CDDTPSGEN3_WRITE_02_BYTES,       CDDTPSGEN3_AddrSLEWL,             CDDTPSGEN3_SLEWRATE_Tx,          CDDTPSGEN3_LEN_2_BYTES,       CDDTPSGEN3_CFGLEDS_Rx,                CDDTPSGEN3_LEN_1_BYTE      },    \
/* 7*/    {  +1,  CDDTPSGEN3_ST_NO_ACT,             eSingleFASTCmd,     CDDTPSGEN3_WRITE_16_BYTES,       CDDTPSGEN3_AddrDEFWIDTH01,        CDDTPSGEN3_DEFWIDTH_Tx,          CDDTPSGEN3_LEN_16_BYTES,      CDDTPSGEN3_CFGDEF_Rx,                 CDDTPSGEN3_LEN_1_BYTE      },    \
/* 8*/    {  +1,  CDDTPSGEN3_ST_NO_ACT,             eSingleFASTCmd,     CDDTPSGEN3_WRITE_02_BYTES,       CDDTPSGEN3_AddrCLK_SYNC,          CDDTPSGEN3_SSYNC_STATUS_Tx,      CDDTPSGEN3_LEN_2_BYTES,       CDDTPSGEN3_SSYNC_STATUS_Rx,           CDDTPSGEN3_LEN_1_BYTE      },    \
/* 9*/    {  +1,  CDDTPSGEN3_ST_NO_ACT,             eSingleFASTCmd,     CDDTPSGEN3_WRITE_01_BYTES,       CDDTPSGEN3_AddrMTPCFG,            CDDTPSGEN3_MTPCFG_FS_Tx,         CDDTPSGEN3_LEN_1_BYTE,        CDDTPSGEN3_EXIT_FS_Rx,                CDDTPSGEN3_LEN_1_BYTE      },    \
         /*--------     Cyclic 0ms     ---------    ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/           \
/*10*/    {  +1,  CDDTPSGEN3_ST_ACT_START_CYCLE,    eSingleFASTCmd,     CDDTPSGEN3_WRITE_04_BYTES,       CDDTPSGEN3_AddrWIDTH04_01L,       CDDTPSGEN3_WIDTH_LSB_Tx,         CDDTPSGEN3_LEN_4_BYTES,       CDDTPSGEN3_PWM_LSB_Rx,                CDDTPSGEN3_LEN_1_BYTE      },    \
/*11*/    {  +1,  CDDTPSGEN3_ST_NO_ACT,             eSingleFASTCmd,     CDDTPSGEN3_WRITE_16_BYTES,       CDDTPSGEN3_AddrWIDTH01H,          CDDTPSGEN3_WIDTH_MSB_Tx,         CDDTPSGEN3_LEN_16_BYTES,      CDDTPSGEN3_PWM_MSB_Rx,                CDDTPSGEN3_LEN_1_BYTE      },    \
/*12*/    {  +1,  CDDTPSGEN3_ST_NO_ACT,             eSingleSLOWCmd,     CDDTPSGEN3_READ_03_BYTES,        CDDTPSGEN3_AddrSYSCFG,            CDDTPSGEN3_Zero_Tx,              CDDTPSGEN3_LEN_0_BYTES,       CDDTPSGEN3_SYSCONFIG_Rx,              CDDTPSGEN3_LEN_5_BYTES     },    \
/*13*/    {  +1,  CDDTPSGEN3_ST_NO_ACT,             eSingleFASTCmd,     CDDTPSGEN3_READ_01_BYTES,        CDDTPSGEN3_AddrSTATUS,            CDDTPSGEN3_Zero_Tx,              CDDTPSGEN3_LEN_0_BYTES,       CDDTPSGEN3_STATUS_Rx,                 CDDTPSGEN3_LEN_3_BYTES     },    \
/*14*/    {  +1,  CDDTPSGEN3_ST_ACT_CHECK_PWR,      eSingleSLOWCmd,     CDDTPSGEN3_READ_04_BYTES,        CDDTPSGEN3_AddrADC1,              CDDTPSGEN3_Zero_Tx,              CDDTPSGEN3_LEN_0_BYTES,       CDDTPSGEN3_ADC_Rx,                    CDDTPSGEN3_LEN_6_BYTES     },    \
/*15*/    {  +1,  CDDTPSGEN3_ST_NO_ACT,             eSingleFASTCmd,     CDDTPSGEN3_WRITE_04_BYTES,       CDDTPSGEN3_AddrWIDTH04_01L,       CDDTPSGEN3_WIDTH_LSB_Tx,         CDDTPSGEN3_LEN_4_BYTES,       CDDTPSGEN3_PWM_LSB_Rx,                CDDTPSGEN3_LEN_1_BYTE      },    \
/*16*/    {  +1,  CDDTPSGEN3_ST_NO_ACT,             eSingleFASTCmd,     CDDTPSGEN3_WRITE_16_BYTES,       CDDTPSGEN3_AddrWIDTH01H,          CDDTPSGEN3_WIDTH_MSB_Tx,         CDDTPSGEN3_LEN_16_BYTES,      CDDTPSGEN3_PWM_MSB_Rx,                CDDTPSGEN3_LEN_1_BYTE      },    \
/*17*/    {  +1,  CDDTPSGEN3_ST_NO_ACT,             eSingleSLOWCmd,     CDDTPSGEN3_READ_04_BYTES,        CDDTPSGEN3_AddrOUTCTRL,           CDDTPSGEN3_Zero_Tx,              CDDTPSGEN3_LEN_0_BYTES,       CDDTPSGEN3_SLEWRATE_Rx,               CDDTPSGEN3_LEN_6_BYTES     },    \
/*18*/    {  +1,  CDDTPSGEN3_ST_NO_ACT,             eSingleSLOWCmd,     CDDTPSGEN3_READ_04_BYTES,        CDDTPSGEN3_AddrFLT_OPEN_OR_DRVL,  CDDTPSGEN3_Zero_Tx,              CDDTPSGEN3_LEN_0_BYTES,       CDDTPSGEN3_ELEFAULT_Rx,               CDDTPSGEN3_LEN_6_BYTES     },    \
/*19*/    {  -9,  CDDTPSGEN3_ST_NO_ACT,             eSingleSLOWCmd,     CDDTPSGEN3_WRITE_04_BYTES,       CDDTPSGEN3_AddrFLT_OPEN_OR_DRVL,  CDDTPSGEN3_ELECFAULTS_Tx,        CDDTPSGEN3_LEN_4_BYTES,       CDDTPSGEN3_CLR_ELEFAULT_Rx,           CDDTPSGEN3_LEN_1_BYTE      },    \
         /*--------     Cyclic End    -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/            \
}

#endif // CDD_TPS_GEN3_SCHED_2024_02_05_H

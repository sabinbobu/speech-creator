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
/// \file  CddTpsGEN2_Sched.h
///
/// \brief
///
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef CDD_TPS_GEN2_SCHED_2024_01_30_H_
#define CDD_TPS_GEN2_SCHED_2024_01_30_H_

//=============================================================================
// Includes
//=============================================================================
#include <../Gen/CddTpsGen2_Com.h>    //should be the cfg file included
#include <../Gen/CddTpsGen2_Types.h>

//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------

#define  CDDTPSGEN2_ST_NO_ACT             0u
#define  CDDTPSGEN2_ST_ACT_DIS_COMM       1u
#define  CDDTPSGEN2_ST_ACT_EN_COMM        2u
#define  CDDTPSGEN2_ST_ACT_WAIT_ACK       3u
#define  CDDTPSGEN2_ST_ACT_SET_PHASE      4u
#define  CDDTPSGEN2_ST_ACT_SET_PWM        5u
#define  CDDTPSGEN2_ST_ACT_CHECK_START    6u
#define  CDDTPSGEN2_ST_ACT_CHECK_PWR      7u
#define  CDDTPSGEN2_ST_ACT_SYSCFG         8u
#define  CDDTPSGEN2_ST_ACT_CFG_LEDS       9u
#define  CDDTPSGEN2_ST_ACT_CHECK_CODING   10u
#define  CDDTPSGEN2_ST_ACT_START_CYCLE    11u
#define  CDDTPSGEN2_ST_ACT_CHECK_RESTART  12u

#define  CDDTPSGEN2_ST_EE_NO_ACT          0u
#define  CDDTPSGEN2_ST_EE_CHECK_PREINIT   1u
#define  CDDTPSGEN2_ST_EE_CHECK_INIT      2u
#define  CDDTPSGEN2_ST_EE_READ_START      3u
#define  CDDTPSGEN2_ST_EE_READ_STATUS     4u
#define  CDDTPSGEN2_ST_EE_READ_DATA       5u
#define  CDDTPSGEN2_ST_EE_WRITE_DATA      6u
#define  CDDTPSGEN2_ST_EE_WRITE_START     7u
#define  CDDTPSGEN2_ST_EE_WRITE_STATUS    8u
#define  CDDTPSGEN2_ST_EE_RESET           9u

#define  CDDTPSGEN2_SIZE_ACKBYTE          1u
#define  CDDTPSGEN2_SIZE_CRCBYTES         2u
#define  CDDTPSGEN2_SIZE_HEADERBYTES      3u


/* Command Frames sizes */
#define  CDDTPSGEN2_WRITE_CMD_SIZE(DataLen)             (CDDTPSGEN2_SIZE_HEADERBYTES + DataLen + CDDTPSGEN2_SIZE_CRCBYTES )
#define  CDDTPSGEN2_READ_CMD_SIZE                       (CDDTPSGEN2_SIZE_HEADERBYTES +           CDDTPSGEN2_SIZE_CRCBYTES )
#define  CDDTPSGEN2_RESPONSE_ACK_CMD_SIZE(DataLen)      (CDDTPSGEN2_WRITE_CMD_SIZE(DataLen)    + CDDTPSGEN2_SIZE_ACKBYTE  )
#define  CDDTPSGEN2_READ_RESPONSE_CMD_SIZE(DataLen)     (CDDTPSGEN2_READ_CMD_SIZE    + DataLen + CDDTPSGEN2_SIZE_CRCBYTES )


#define GEN_RxSize(DataLen)      (DataLen + CDDTPSGEN2_SIZE_ACKBYTE)
#define GEN_RxReadSize(DataLen)  (DataLen + CDDTPSGEN2_SIZE_CRCBYTES)

//-----------------------------------------------------------------------------
//  UART scheduling configuration
//-----------------------------------------------------------------------------
#define CDDTPSGEN2_Cfg_UartSchedTableLen          7u    // to be calculated based on the scheduler table !!!
#define CDDTPSGEN2_Cfg_UartSchedTableCycStart     14u   // to be calculated based on the scheduler table !!!



#define CDDTPSGEN2_Cfg_UartSchedTable_Init                                                                                                                                                                                                                                    \
{                                                                                                                                                                                                                                                                             \
         /* next      Optional                        Dynamic               Read/Write                      Register                            Data                           Tx Data                        Data                              Rx Data             */        \
         /* state     action                          command               command(INIT)                   address                          to transmit                       Length                      to receive                           Length              */        \
         /*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */        \
         /*---------    Init sequence   --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */        \
/* 0*/    {  +1,  CDDTPSGEN2_ST_ACT_CHECK_RESTART,  eBroadcastCmd,      CDDTPSGEN2_WRITE_01_BYTES,       CDDTPSGEN2_AddrADCID,             CDDTPSGEN2_ADCID_Tx,            CDDTPSGEN2_LEN_1_BYTE,        CDDTPSGEN2_BROADCAST1_ADCID_Rx,       CDDTPSGEN2_LEN_0_BYTES      },    \
/* 1*/    {  +1,  CDDTPSGEN2_ST_ACT_CHECK_START,    eBroadcastCmd,      CDDTPSGEN2_WRITE_01_BYTES,       CDDTPSGEN2_AddrADCID,             CDDTPSGEN2_ADCID_Tx,            CDDTPSGEN2_LEN_1_BYTE,        CDDTPSGEN2_BROADCAST1_ADCID_Rx,       CDDTPSGEN2_LEN_0_BYTES      },    \
/* 2*/    {  +1,  CDDTPSGEN2_ST_NO_ACT,             eBroadcastCmd,      CDDTPSGEN2_WRITE_01_BYTES,       CDDTPSGEN2_AddrSYSCFG,            CDDTPSGEN2_SYSCFG_DEFAULT_Tx,   CDDTPSGEN2_LEN_1_BYTE,        CDDTPSGEN2_BROADCAST2_SYSCFG_Rx,      CDDTPSGEN2_LEN_0_BYTES      },    \
/* 3*/    {  +1,  CDDTPSGEN2_ST_NO_ACT,             eSingleFASTCmd,     CDDTPSGEN2_READ_01_BYTES,        CDDTPSGEN2_AddrICID,              CDDTPSGEN2_Zero_Tx,             CDDTPSGEN2_LEN_0_BYTES,       CDDTPSGEN2_ICID_Rx,                   CDDTPSGEN2_LEN_3_BYTES      },    \
/* 4*/    {  +1,  CDDTPSGEN2_ST_ACT_SYSCFG,         eSingleFASTCmd,     CDDTPSGEN2_WRITE_03_BYTES,       CDDTPSGEN2_AddrSYSCFG,            CDDTPSGEN2_SYSCFG_Tx,           CDDTPSGEN2_LEN_3_BYTES,       CDDTPSGEN2_SYSCFG_Rx,                 CDDTPSGEN2_LEN_1_BYTE       },    \
/* 5*/    {  +1,  CDDTPSGEN2_ST_ACT_SET_PHASE,      eSingleFASTCmd,     CDDTPSGEN2_WRITE_16_BYTES,       CDDTPSGEN2_AddrMPHASE01L,         CDDTPSGEN2_MPHASE_Tx,           CDDTPSGEN2_LEN_16_BYTES,      CDDTPSGEN2_PHASES_Rx,                 CDDTPSGEN2_LEN_1_BYTE       },    \
/* 6*/    {  +1,  CDDTPSGEN2_ST_ACT_CFG_LEDS,       eSingleFASTCmd,     CDDTPSGEN2_WRITE_12_BYTES,       CDDTPSGEN2_AddrSLEWRATE,          CDDTPSGEN2_STRINGS_Tx,          CDDTPSGEN2_LEN_12_BYTES,      CDDTPSGEN2_CFGLEDS_Rx,                CDDTPSGEN2_LEN_1_BYTE       },    \
/* 7*/    {  +1,  CDDTPSGEN2_ST_NO_ACT,             eSingleFASTCmd,     CDDTPSGEN2_READ_16_BYTES,        CDDTPSGEN2_AddrSYSCFG,            CDDTPSGEN2_Zero_Tx,             CDDTPSGEN2_LEN_0_BYTES,       CDDTPSGEN2_CONFIG2_Rx,                CDDTPSGEN2_LEN_18_BYTES     },    \
        /*--------     Cyclic 0ms     -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/         \
/* 8*/    {  +1,  CDDTPSGEN2_ST_ACT_START_CYCLE,    eSingleFASTCmd,     CDDTPSGEN2_WRITE_16_BYTES,       CDDTPSGEN2_AddrMWIDTH01L,         CDDTPSGEN2_MWIDTH_Tx,           CDDTPSGEN2_LEN_16_BYTES,      CDDTPSGEN2_PWMS_Rx,                   CDDTPSGEN2_LEN_1_BYTE       },    \
/* 9*/    {  +1,  CDDTPSGEN2_ST_NO_ACT,             eSingleSLOWCmd,     CDDTPSGEN2_READ_16_BYTES,        CDDTPSGEN2_AddrSLEWRATE,          CDDTPSGEN2_Zero_Tx,             CDDTPSGEN2_LEN_0_BYTES,       CDDTPSGEN2_CONFIG1_Rx,                CDDTPSGEN2_LEN_18_BYTES     },    \
/* 10*/   {  +1,  CDDTPSGEN2_ST_NO_ACT,             eSingleSLOWCmd,     CDDTPSGEN2_READ_16_BYTES,        CDDTPSGEN2_AddrSYSCFG,            CDDTPSGEN2_Zero_Tx,             CDDTPSGEN2_LEN_0_BYTES,       CDDTPSGEN2_CONFIG2_Rx,                CDDTPSGEN2_LEN_18_BYTES     },    \
/* 11*/   {  +1,  CDDTPSGEN2_ST_ACT_CHECK_PWR,      eSingleSLOWCmd,     CDDTPSGEN2_READ_02_BYTES,        CDDTPSGEN2_AddrADC1,              CDDTPSGEN2_Zero_Tx,             CDDTPSGEN2_LEN_0_BYTES,       CDDTPSGEN2_ADC_Rx,                    CDDTPSGEN2_LEN_4_BYTES      },    \
/* 12*/   {  +1,  CDDTPSGEN2_ST_NO_ACT,             eSingleFASTCmd,     CDDTPSGEN2_WRITE_16_BYTES,       CDDTPSGEN2_AddrMWIDTH01L,         CDDTPSGEN2_MWIDTH_Tx,           CDDTPSGEN2_LEN_16_BYTES,      CDDTPSGEN2_PWMS_Rx,                   CDDTPSGEN2_LEN_1_BYTE       },    \
/* 13*/   {  +1,  CDDTPSGEN2_ST_NO_ACT,             eSingleSLOWCmd,     CDDTPSGEN2_READ_03_BYTES,        CDDTPSGEN2_AddrFAULTL,            CDDTPSGEN2_Zero_Tx,             CDDTPSGEN2_LEN_0_BYTES,       CDDTPSGEN2_ELEFAULT_Rx,               CDDTPSGEN2_LEN_5_BYTES      },    \
/* 14*/   {  -6,  CDDTPSGEN2_ST_NO_ACT,             eSingleSLOWCmd,     CDDTPSGEN2_WRITE_03_BYTES,       CDDTPSGEN2_AddrFAULTL,            CDDTPSGEN2_ELECFAULTS_Tx,       CDDTPSGEN2_LEN_3_BYTES,       CDDTPSGEN2_CLR_ELEFAULT_Rx,           CDDTPSGEN2_LEN_1_BYTE       },    \
         /*--------     End Cyclic      --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/          \
}

#ifndef UNIT_TEST
#define CDDTPSGEN2_Cfg_UartSchedTableEE_Init                                                                                                                                                                                                                                    \
{                                                                                                                                                                                                                                                                             \
         /*                next                      Optional                              Dynamic               Read/Write                      Register                            Data                           Tx Data                        Data                              Rx Data       */        \
         /*                state                     action                                command               command(INIT)                   address                          to transmit                       Length                      to receive                           Length        */        \
         /*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */        \
         /*---------    Dynamic sequence   ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */        \
/* 0*/    {  CDDTPSGEN2_STATE_EE_PREINIT,         CDDTPSGEN2_ST_EE_CHECK_PREINIT,         eEEPROMCmd,         CDDTPSGEN2_WRITE_01_BYTES,       CDDTPSGEN2_AddrSYSCFG,             CDDTPSGEN2_I2C_SYSCFG_EETx,      CDDTPSGEN2_LEN_1_BYTE,        CDDTPSGEN2_ACK_EERx,       CDDTPSGEN2_LEN_1_BYTE      },    \
/* 1*/    {  CDDTPSGEN2_STATE_EE_INIT,            CDDTPSGEN2_ST_EE_CHECK_INIT,            eEEPROMCmd,         CDDTPSGEN2_WRITE_01_BYTES,       CDDTPSGEN2_AddrI2CTICK,            CDDTPSGEN2_I2CTICK_EETx,         CDDTPSGEN2_LEN_1_BYTE,        CDDTPSGEN2_ACK_EERx,       CDDTPSGEN2_LEN_1_BYTE      },    \
/* 2*/    {  CDDTPSGEN2_STATE_EE_READ_START,      CDDTPSGEN2_ST_EE_READ_START,            eEEPROMCmd,         CDDTPSGEN2_WRITE_04_BYTES,       CDDTPSGEN2_AddrI2CSLA,             CDDTPSGEN2_I2C_STARTCMD_EETx,    CDDTPSGEN2_LEN_4_BYTES,       CDDTPSGEN2_ACK_EERx,       CDDTPSGEN2_LEN_1_BYTE      },    \
/* 3*/    {  CDDTPSGEN2_STATE_EE_RR_STATUS,       CDDTPSGEN2_ST_EE_READ_STATUS,           eEEPROMCmd,         CDDTPSGEN2_READ_01_BYTES,        CDDTPSGEN2_AddrI2CSTAT,            CDDTPSGEN2_Zero_Tx,              CDDTPSGEN2_LEN_0_BYTES,       CDDTPSGEN2_I2C_STAT_EERx,  CDDTPSGEN2_LEN_3_BYTES     },    \
/* 4*/    {  CDDTPSGEN2_STATE_EE_READ_1_BYTE,     CDDTPSGEN2_ST_EE_READ_DATA,             eEEPROMCmd,         CDDTPSGEN2_READ_01_BYTES,        CDDTPSGEN2_AddrI2CDAT,             CDDTPSGEN2_Zero_Tx,              CDDTPSGEN2_LEN_0_BYTES,       CDDTPSGEN2_I2C_DATA_EERx,  CDDTPSGEN2_LEN_3_BYTES     },    \
/* 5*/    {  CDDTPSGEN2_STATE_EE_READ_2_BYTES,    CDDTPSGEN2_ST_EE_READ_DATA,             eEEPROMCmd,         CDDTPSGEN2_READ_02_BYTES,        CDDTPSGEN2_AddrI2CDAT,             CDDTPSGEN2_Zero_Tx,              CDDTPSGEN2_LEN_0_BYTES,       CDDTPSGEN2_I2C_DATA_EERx,  CDDTPSGEN2_LEN_4_BYTES     },    \
/* 6*/    {  CDDTPSGEN2_STATE_EE_READ_3_BYTES,    CDDTPSGEN2_ST_EE_READ_DATA,             eEEPROMCmd,         CDDTPSGEN2_READ_03_BYTES,        CDDTPSGEN2_AddrI2CDAT,             CDDTPSGEN2_Zero_Tx,              CDDTPSGEN2_LEN_0_BYTES,       CDDTPSGEN2_I2C_DATA_EERx,  CDDTPSGEN2_LEN_5_BYTES     },    \
/* 7*/    {  CDDTPSGEN2_STATE_EE_READ_4_BYTES,    CDDTPSGEN2_ST_EE_READ_DATA,             eEEPROMCmd,         CDDTPSGEN2_READ_04_BYTES,        CDDTPSGEN2_AddrI2CDAT,             CDDTPSGEN2_Zero_Tx,              CDDTPSGEN2_LEN_0_BYTES,       CDDTPSGEN2_I2C_DATA_EERx,  CDDTPSGEN2_LEN_6_BYTES     },    \
/* 8*/    {  CDDTPSGEN2_STATE_EE_READ_12_BYTES,   CDDTPSGEN2_ST_EE_READ_DATA,             eEEPROMCmd,         CDDTPSGEN2_READ_12_BYTES,        CDDTPSGEN2_AddrI2CDAT,             CDDTPSGEN2_Zero_Tx,              CDDTPSGEN2_LEN_0_BYTES,       CDDTPSGEN2_I2C_DATA_EERx,  CDDTPSGEN2_LEN_14_BYTES    },    \
/* 9*/    {  CDDTPSGEN2_STATE_EE_READ_16_BYTES,   CDDTPSGEN2_ST_EE_READ_DATA,             eEEPROMCmd,         CDDTPSGEN2_READ_16_BYTES,        CDDTPSGEN2_AddrI2CDAT,             CDDTPSGEN2_Zero_Tx,              CDDTPSGEN2_LEN_0_BYTES,       CDDTPSGEN2_I2C_DATA_EERx,  CDDTPSGEN2_LEN_18_BYTES    },    \
/*10*/    {  CDDTPSGEN2_STATE_EE_WRITE_DATA,      CDDTPSGEN2_ST_EE_WRITE_DATA,            eEEPROMCmd,         CDDTPSGEN2_WRITE_01_BYTES,       CDDTPSGEN2_AddrI2CDAT,             CDDTPSGEN2_I2C_DATA_EETx,        CDDTPSGEN2_LEN_1_BYTE ,       CDDTPSGEN2_ACK_EERx,       CDDTPSGEN2_LEN_1_BYTE      },    \
/*11*/    {  CDDTPSGEN2_STATE_EE_WRITE_START,     CDDTPSGEN2_ST_EE_WRITE_START,           eEEPROMCmd,         CDDTPSGEN2_WRITE_04_BYTES,       CDDTPSGEN2_AddrI2CSLA,             CDDTPSGEN2_I2C_STARTCMD_EETx,    CDDTPSGEN2_LEN_4_BYTES,       CDDTPSGEN2_ACK_EERx,       CDDTPSGEN2_LEN_1_BYTE      },    \
/*12*/    {  CDDTPSGEN2_STATE_EE_RW_STATUS,       CDDTPSGEN2_ST_EE_WRITE_STATUS,          eEEPROMCmd,         CDDTPSGEN2_READ_01_BYTES,        CDDTPSGEN2_AddrI2CSTAT,            CDDTPSGEN2_Zero_Tx,              CDDTPSGEN2_LEN_0_BYTES,       CDDTPSGEN2_I2C_STAT_EERx,  CDDTPSGEN2_LEN_3_BYTES     },    \
/*13*/    {  CDDTPSGEN2_STATE_EE_RESET,           CDDTPSGEN2_ST_EE_RESET,                 eEEPROMCmd,         CDDTPSGEN2_WRITE_04_BYTES,       CDDTPSGEN2_AddrI2CSLA,             CDDTPSGEN2_I2C_STARTCMD_EETx,    CDDTPSGEN2_LEN_4_BYTES,       CDDTPSGEN2_ACK_EERx,       CDDTPSGEN2_LEN_1_BYTE      },    \
}
#else
#define CDDTPSGEN2_Cfg_UartSchedTableEE_Init                                                                                                                                                                                                                                    \
{                                                                                                                                                                                                                                                                             \
         /*                next                      Optional                              Dynamic               Read/Write                      Register                            Data                           Tx Data                        Data                              Rx Data       */        \
         /*                state                     action                                command               command(INIT)                   address                          to transmit                       Length                      to receive                           Length        */        \
         /*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */        \
         /*---------    Dynamic sequence   ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */        \
/* 0*/    {  CDDTPSGEN2_STATE_EE_PREINIT,         CDDTPSGEN2_ST_EE_CHECK_PREINIT,         eEEPROMCmd,         CDDTPSGEN2_WRITE_01_BYTES,       CDDTPSGEN2_AddrSYSCFG,             CDDTPSGEN2_I2C_SYSCFG_EETx,      CDDTPSGEN2_LEN_1_BYTE,        CDDTPSGEN2_ACK_EERx,       CDDTPSGEN2_LEN_1_BYTE      },    \
/* 1*/    {  CDDTPSGEN2_STATE_EE_INIT,            CDDTPSGEN2_ST_EE_CHECK_INIT,            eEEPROMCmd,         CDDTPSGEN2_WRITE_01_BYTES,       CDDTPSGEN2_AddrI2CTICK,            CDDTPSGEN2_I2CTICK_EETx,         CDDTPSGEN2_LEN_1_BYTE,        CDDTPSGEN2_ACK_EERx,       CDDTPSGEN2_LEN_1_BYTE      },    \
/* 2*/    {  CDDTPSGEN2_STATE_EE_READ_START,      CDDTPSGEN2_ST_EE_READ_START,            eEEPROMCmd,         CDDTPSGEN2_WRITE_04_BYTES,       CDDTPSGEN2_AddrI2CSLA,             CDDTPSGEN2_I2C_STARTCMD_EETx,    CDDTPSGEN2_LEN_4_BYTES,       CDDTPSGEN2_ACK_EERx,       CDDTPSGEN2_LEN_1_BYTE      },    \
/* 3*/    {  CDDTPSGEN2_STATE_EE_RR_STATUS,       CDDTPSGEN2_ST_EE_READ_STATUS,           eEEPROMCmd,         CDDTPSGEN2_READ_01_BYTES,        CDDTPSGEN2_AddrI2CSTAT,            CDDTPSGEN2_Zero_Tx,              CDDTPSGEN2_LEN_0_BYTES,       CDDTPSGEN2_I2C_STAT_EERx,  CDDTPSGEN2_LEN_3_BYTES     },    \
/* 4*/    {  CDDTPSGEN2_STATE_EE_READ_1_BYTE,     CDDTPSGEN2_ST_EE_READ_DATA,             eEEPROMCmd,         CDDTPSGEN2_READ_01_BYTES,        CDDTPSGEN2_AddrI2CDAT,             CDDTPSGEN2_Zero_Tx,              CDDTPSGEN2_LEN_0_BYTES,       CDDTPSGEN2_I2C_DATA_EERx,  CDDTPSGEN2_LEN_3_BYTES     },    \
/* 5*/    {  CDDTPSGEN2_STATE_EE_READ_2_BYTES,    CDDTPSGEN2_ST_EE_READ_DATA,             eEEPROMCmd,         CDDTPSGEN2_READ_02_BYTES,        CDDTPSGEN2_AddrI2CDAT,             CDDTPSGEN2_Zero_Tx,              CDDTPSGEN2_LEN_0_BYTES,       CDDTPSGEN2_I2C_DATA_EERx,  CDDTPSGEN2_LEN_4_BYTES     },    \
/* 6*/    {  CDDTPSGEN2_STATE_EE_READ_3_BYTES,    CDDTPSGEN2_ST_EE_READ_DATA,             eEEPROMCmd,         CDDTPSGEN2_READ_03_BYTES,        CDDTPSGEN2_AddrI2CDAT,             CDDTPSGEN2_Zero_Tx,              CDDTPSGEN2_LEN_0_BYTES,       CDDTPSGEN2_I2C_DATA_EERx,  CDDTPSGEN2_LEN_5_BYTES     },    \
/* 7*/    {  CDDTPSGEN2_STATE_EE_READ_4_BYTES,    CDDTPSGEN2_ST_EE_READ_DATA,             eEEPROMCmd,         CDDTPSGEN2_READ_04_BYTES,        CDDTPSGEN2_AddrI2CDAT,             CDDTPSGEN2_Zero_Tx,              CDDTPSGEN2_LEN_0_BYTES,       CDDTPSGEN2_I2C_DATA_EERx,  CDDTPSGEN2_LEN_6_BYTES     },    \
/* 8*/    {  CDDTPSGEN2_STATE_EE_READ_12_BYTES,   CDDTPSGEN2_ST_EE_READ_DATA,             eEEPROMCmd,         CDDTPSGEN2_READ_12_BYTES,        CDDTPSGEN2_AddrI2CDAT,             CDDTPSGEN2_Zero_Tx,              CDDTPSGEN2_LEN_0_BYTES,       CDDTPSGEN2_I2C_DATA_EERx,  CDDTPSGEN2_LEN_14_BYTES    },    \
/* 9*/    {  CDDTPSGEN2_STATE_EE_READ_16_BYTES,   CDDTPSGEN2_ST_EE_READ_DATA,             eEEPROMCmd,         CDDTPSGEN2_READ_16_BYTES,        CDDTPSGEN2_AddrI2CDAT,             CDDTPSGEN2_Zero_Tx,              CDDTPSGEN2_LEN_0_BYTES,       CDDTPSGEN2_I2C_DATA_EERx,  CDDTPSGEN2_LEN_18_BYTES    },    \
/*10*/    {  CDDTPSGEN2_STATE_EE_WRITE_DATA,      CDDTPSGEN2_ST_EE_WRITE_DATA,            eEEPROMCmd,         CDDTPSGEN2_WRITE_01_BYTES,       CDDTPSGEN2_AddrI2CDAT,             CDDTPSGEN2_I2C_DATA_EETx,        CDDTPSGEN2_LEN_1_BYTE ,       CDDTPSGEN2_ACK_EERx,       CDDTPSGEN2_LEN_1_BYTE      },    \
/*11*/    {  CDDTPSGEN2_STATE_EE_WRITE_START,     CDDTPSGEN2_ST_EE_WRITE_START,           eEEPROMCmd,         CDDTPSGEN2_WRITE_04_BYTES,       CDDTPSGEN2_AddrI2CSLA,             CDDTPSGEN2_I2C_STARTCMD_EETx,    CDDTPSGEN2_LEN_4_BYTES,       CDDTPSGEN2_ACK_EERx,       CDDTPSGEN2_LEN_1_BYTE      },    \
/*12*/    {  CDDTPSGEN2_STATE_EE_RW_STATUS,       CDDTPSGEN2_ST_EE_WRITE_STATUS,          eEEPROMCmd,         CDDTPSGEN2_READ_01_BYTES,        CDDTPSGEN2_AddrI2CSTAT,            CDDTPSGEN2_Zero_Tx,              CDDTPSGEN2_LEN_0_BYTES,       CDDTPSGEN2_I2C_STAT_EERx,  CDDTPSGEN2_LEN_3_BYTES     },    \
/*13*/    {  CDDTPSGEN2_STATE_EE_RESET,           CDDTPSGEN2_ST_EE_RESET,                 eEEPROMCmd,         CDDTPSGEN2_WRITE_04_BYTES,       CDDTPSGEN2_AddrI2CSLA,             CDDTPSGEN2_I2C_STARTCMD_EETx,    CDDTPSGEN2_LEN_4_BYTES,       CDDTPSGEN2_ACK_EERx,       CDDTPSGEN2_LEN_1_BYTE      },    \
/*14*/    {  15,                                  CDDTPSGEN2_ST_EE_RESET,                 eEEPROMCmd,         CDDTPSGEN2_WRITE_04_BYTES,       CDDTPSGEN2_AddrI2CSLA,             CDDTPSGEN2_I2C_STARTCMD_EETx,    CDDTPSGEN2_LEN_4_BYTES,       CDDTPSGEN2_ACK_EERx,       CDDTPSGEN2_LEN_1_BYTE      },    \
/*15*/    {  0,                                   CDDTPSGEN2_ST_NO_ACT,                 eEEPROMCmd,         CDDTPSGEN2_WRITE_04_BYTES,       CDDTPSGEN2_AddrI2CSLA,             CDDTPSGEN2_I2C_STARTCMD_EETx,    CDDTPSGEN2_LEN_4_BYTES,       CDDTPSGEN2_ACK_EERx,       CDDTPSGEN2_LEN_1_BYTE      },    \
}
#endif

#endif // CDD_TPSGEN2_SCHED_2023_09_06_H

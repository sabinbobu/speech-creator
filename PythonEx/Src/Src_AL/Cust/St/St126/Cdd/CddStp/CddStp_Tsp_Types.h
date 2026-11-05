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
/// \file  CddStp_Tsp_Types.h
///
/// \brief
///
//-----------------------------------------------------------------------------
#ifndef CDD_STP_TSP_TYPES_2020_03_05_H_
#define CDD_STP_TSP_TYPES_2020_03_05_H_

#include <Std_Types.h>
//#include <../Mcal/S32K/S32K_14X/_146/Reg/S32K146.h>

// Control register
typedef struct {
  uint32              unTDRE : 1;
  uint32              unTCF : 1;
  uint32              unTIE : 1;
  uint32              unTPS : 2;
  uint32              unTPP : 1;
  uint32              unTFC : 1;
  uint32              unTMS : 1;
  uint32              unTEN : 1;
  uint32              unReserved : 23;
}ts_LPT_CSR_BitField;

typedef union {
  ts_LPT_CSR_BitField tsLPT_CSR_Bit;
  uint32 unLPT_CSR_Data;
}un_LPT_CSR_Field;


typedef struct {
  uint32              unPCS : 2;
  uint32              unPBYP : 1;
  uint32              unPRESCALE : 4;
  uint32              unReserved : 25;
}ts_LPT_PSR_BitField;


// prescaler register
typedef union {
  ts_LPT_PSR_BitField tsLPT_PSR_Bit;
  uint32 unLPT_PSR_Data;
}un_LPT_PSR_Field;


// Compare register
typedef struct {
  uint32              unCOMPARE : 16;
  uint32              unReserved : 16;
}ts_LPT_CMR_BitField;

typedef union {
  ts_LPT_CMR_BitField tsLPT_CMR_Bit;
  uint32 unLPT_CMR_Data;
}un_LPT_CMR_Field;


// Counter register
typedef struct {
  uint32              unCOUNTER : 16;
  uint32              unReserved : 16;
}ts_LPT_CNR_BitField;

typedef union {
  ts_LPT_CNR_BitField tsLPT_CNR_Bit;
  uint32 unLPT_CNR_Data;
}un_LPT_CNR_Field;


typedef struct {
  un_LPT_CSR_Field unCSR;
  un_LPT_PSR_Field unPSR;
  un_LPT_CMR_Field unCMR;
  un_LPT_CNR_Field unCNR;
}LPTMR0_Type;

/**
  * \brief Counter control register (TCPWM_GRP_CNT_CTRL)
  */
typedef struct stc_TCPWM_GRP_CNT_CTRL_field {
  uint32                         u1AUTO_RELOAD_CC0:1;
  uint32                         u1AUTO_RELOAD_CC1:1;
  uint32                         u1AUTO_RELOAD_PERIOD:1;
  uint32                         u1AUTO_RELOAD_LINE_SEL:1;
  uint32                         u1CC0_MATCH_UP_EN:1;
  uint32                         u1CC0_MATCH_DOWN_EN:1;
  uint32                         u1CC1_MATCH_UP_EN:1;
  uint32                         u1CC1_MATCH_DOWN_EN:1;
  uint32                         u1PWM_IMM_KILL:1;
  uint32                         u1PWM_STOP_ON_KILL:1;
  uint32                         u1PWM_SYNC_KILL:1;
  uint32                         :1;
  uint32                         u2PWM_DISABLE_MODE:2;
  uint32                         :2;
  uint32                         u2UP_DOWN_MODE:2;
  uint32                         u1ONE_SHOT:1;
  uint32                         :1;
  uint32                         u2QUAD_ENCODING_MODE:2;
  uint32                         :2;
  uint32                         u3MODE:3;
  uint32                         :3;
  uint32                         u1DBG_FREEZE_EN:1;
  uint32                         u1ENABLED:1;
} stc_TCPWM_GRP_CNT_CTRL_field_t;

typedef union un_TCPWM_GRP_CNT_CTRL {
  uint32                         u32Register;
  stc_TCPWM_GRP_CNT_CTRL_field_t   stcField;
  uint8                          au8Byte[4];
  uint16                         au16Halfword[2];
} un_TCPWM_GRP_CNT_CTRL_t;

/**
  * \brief Counter status register (TCPWM_GRP_CNT_STATUS)
  */
typedef struct stc_TCPWM_GRP_CNT_STATUS_field {
  uint32                         u1DOWN:1;
  uint32                         :3;
  uint32                         u1TR_CAPTURE0:1;
  uint32                         u1TR_COUNT:1;
  uint32                         u1TR_RELOAD:1;
  uint32                         u1TR_STOP:1;
  uint32                         u1TR_START:1;
  uint32                         u1TR_CAPTURE1:1;
  uint32                         u1LINE_OUT:1;
  uint32                         u1LINE_COMPL_OUT:1;
  uint32                         :3;
  uint32                         u1RUNNING:1;
  uint32                         u8DT_CNT_L:8;
  uint32                         u8DT_CNT_H:8;
} stc_TCPWM_GRP_CNT_STATUS_field_t;

typedef union un_TCPWM_GRP_CNT_STATUS {
  uint32                         u32Register;
  stc_TCPWM_GRP_CNT_STATUS_field_t stcField;
  uint8                          au8Byte[4];
  uint16                         au16Halfword[2];
} un_TCPWM_GRP_CNT_STATUS_t;

/**
  * \brief Counter count register (TCPWM_GRP_CNT_COUNTER)
  */
typedef struct stc_TCPWM_GRP_CNT_COUNTER_field {
  uint32                         u32COUNTER:32;
} stc_TCPWM_GRP_CNT_COUNTER_field_t;

typedef union un_TCPWM_GRP_CNT_COUNTER {
  uint32                         u32Register;
  stc_TCPWM_GRP_CNT_COUNTER_field_t stcField;
  uint8                          au8Byte[4];
  uint16                         au16Halfword[2];
} un_TCPWM_GRP_CNT_COUNTER_t;

/**
  * \brief Counter compare/capture 0 register (TCPWM_GRP_CNT_CC0)
  */
typedef struct stc_TCPWM_GRP_CNT_CC0_field {
  uint32                         u32CC:32;
} stc_TCPWM_GRP_CNT_CC0_field_t;

typedef union un_TCPWM_GRP_CNT_CC0 {
  uint32                         u32Register;
  stc_TCPWM_GRP_CNT_CC0_field_t    stcField;
  uint8                          au8Byte[4];
  uint16                         au16Halfword[2];
} un_TCPWM_GRP_CNT_CC0_t;

/**
  * \brief Counter buffered compare/capture 0 register (TCPWM_GRP_CNT_CC0_BUFF)
  */
typedef struct stc_TCPWM_GRP_CNT_CC0_BUFF_field {
  uint32                         u32CC:32;
} stc_TCPWM_GRP_CNT_CC0_BUFF_field_t;

typedef union un_TCPWM_GRP_CNT_CC0_BUFF {
  uint32                         u32Register;
  stc_TCPWM_GRP_CNT_CC0_BUFF_field_t stcField;
  uint8                          au8Byte[4];
  uint16                         au16Halfword[2];
} un_TCPWM_GRP_CNT_CC0_BUFF_t;

/**
  * \brief Counter compare/capture 1 register (TCPWM_GRP_CNT_CC1)
  */
typedef struct stc_TCPWM_GRP_CNT_CC1_field {
  uint32                         u32CC:32;
} stc_TCPWM_GRP_CNT_CC1_field_t;

typedef union un_TCPWM_GRP_CNT_CC1 {
  uint32                         u32Register;
  stc_TCPWM_GRP_CNT_CC1_field_t    stcField;
  uint8                          au8Byte[4];
  uint16                         au16Halfword[2];
} un_TCPWM_GRP_CNT_CC1_t;

/**
  * \brief Counter buffered compare/capture 1 register (TCPWM_GRP_CNT_CC1_BUFF)
  */
typedef struct stc_TCPWM_GRP_CNT_CC1_BUFF_field {
  uint32                         u32CC:32;
} stc_TCPWM_GRP_CNT_CC1_BUFF_field_t;

typedef union un_TCPWM_GRP_CNT_CC1_BUFF {
  uint32                         u32Register;
  stc_TCPWM_GRP_CNT_CC1_BUFF_field_t stcField;
  uint8                          au8Byte[4];
  uint16                         au16Halfword[2];
} un_TCPWM_GRP_CNT_CC1_BUFF_t;

/**
  * \brief Counter period register (TCPWM_GRP_CNT_PERIOD)
  */
typedef struct stc_TCPWM_GRP_CNT_PERIOD_field {
  uint32                         u32PERIOD:32;
} stc_TCPWM_GRP_CNT_PERIOD_field_t;

typedef union un_TCPWM_GRP_CNT_PERIOD {
  uint32                         u32Register;
  stc_TCPWM_GRP_CNT_PERIOD_field_t stcField;
  uint8                          au8Byte[4];
  uint16                         au16Halfword[2];
} un_TCPWM_GRP_CNT_PERIOD_t;

/**
  * \brief Counter buffered period register (TCPWM_GRP_CNT_PERIOD_BUFF)
  */
typedef struct stc_TCPWM_GRP_CNT_PERIOD_BUFF_field {
  uint32                         u32PERIOD:32;
} stc_TCPWM_GRP_CNT_PERIOD_BUFF_field_t;

typedef union un_TCPWM_GRP_CNT_PERIOD_BUFF {
  uint32                         u32Register;
  stc_TCPWM_GRP_CNT_PERIOD_BUFF_field_t stcField;
  uint8                          au8Byte[4];
  uint16                         au16Halfword[2];
} un_TCPWM_GRP_CNT_PERIOD_BUFF_t;

/**
  * \brief Counter line selection register (TCPWM_GRP_CNT_LINE_SEL)
  */
typedef struct stc_TCPWM_GRP_CNT_LINE_SEL_field {
  uint32                         u3OUT_SEL:3;
  uint32                         :1;
  uint32                         u3COMPL_OUT_SEL:3;
  uint32                         :25;
} stc_TCPWM_GRP_CNT_LINE_SEL_field_t;

typedef union un_TCPWM_GRP_CNT_LINE_SEL {
  uint32                         u32Register;
  stc_TCPWM_GRP_CNT_LINE_SEL_field_t stcField;
  uint8                          au8Byte[4];
  uint16                         au16Halfword[2];
} un_TCPWM_GRP_CNT_LINE_SEL_t;

/**
  * \brief Counter buffered line selection register (TCPWM_GRP_CNT_LINE_SEL_BUFF)
  */
typedef struct stc_TCPWM_GRP_CNT_LINE_SEL_BUFF_field {
  uint32                         u3OUT_SEL:3;
  uint32                         :1;
  uint32                         u3COMPL_OUT_SEL:3;
  uint32                         :25;
} stc_TCPWM_GRP_CNT_LINE_SEL_BUFF_field_t;

typedef union un_TCPWM_GRP_CNT_LINE_SEL_BUFF {
  uint32                         u32Register;
  stc_TCPWM_GRP_CNT_LINE_SEL_BUFF_field_t stcField;
  uint8                          au8Byte[4];
  uint16                         au16Halfword[2];
} un_TCPWM_GRP_CNT_LINE_SEL_BUFF_t;

/**
  * \brief Counter PWM dead time register (TCPWM_GRP_CNT_DT)
  */
typedef struct stc_TCPWM_GRP_CNT_DT_field {
  uint32                         u8DT_LINE_OUT_L:8;
  uint32                         u8DT_LINE_OUT_H:8;
  uint32                         u16DT_LINE_COMPL_OUT:16;
} stc_TCPWM_GRP_CNT_DT_field_t;

typedef union un_TCPWM_GRP_CNT_DT {
  uint32                         u32Register;
  stc_TCPWM_GRP_CNT_DT_field_t     stcField;
  uint8                          au8Byte[4];
  uint16                         au16Halfword[2];
} un_TCPWM_GRP_CNT_DT_t;

/**
  * \brief Counter trigger command register (TCPWM_GRP_CNT_TR_CMD)
  */
typedef struct stc_TCPWM_GRP_CNT_TR_CMD_field {
  uint32                         u1CAPTURE0:1;
  uint32                         :1;
  uint32                         u1RELOAD:1;
  uint32                         u1STOP:1;
  uint32                         u1START:1;
  uint32                         u1CAPTURE1:1;
  uint32                         :26;
} stc_TCPWM_GRP_CNT_TR_CMD_field_t;

typedef union un_TCPWM_GRP_CNT_TR_CMD {
  uint32                         u32Register;
  stc_TCPWM_GRP_CNT_TR_CMD_field_t stcField;
  uint8                          au8Byte[4];
  uint16                         au16Halfword[2];
} un_TCPWM_GRP_CNT_TR_CMD_t;

/**
  * \brief Counter input trigger selection register 0 (TCPWM_GRP_CNT_TR_IN_SEL0)
  */
typedef struct stc_TCPWM_GRP_CNT_TR_IN_SEL0_field {
  uint32                         u8CAPTURE0_SEL:8;
  uint32                         u8COUNT_SEL:8;
  uint32                         u8RELOAD_SEL:8;
  uint32                         u8STOP_SEL:8;
} stc_TCPWM_GRP_CNT_TR_IN_SEL0_field_t;

typedef union un_TCPWM_GRP_CNT_TR_IN_SEL0 {
  uint32                         u32Register;
  stc_TCPWM_GRP_CNT_TR_IN_SEL0_field_t stcField;
  uint8                          au8Byte[4];
  uint16                         au16Halfword[2];
} un_TCPWM_GRP_CNT_TR_IN_SEL0_t;

/**
  * \brief Counter input trigger selection register 1 (TCPWM_GRP_CNT_TR_IN_SEL1)
  */
typedef struct stc_TCPWM_GRP_CNT_TR_IN_SEL1_field {
  uint32                         u8START_SEL:8;
  uint32                         u8CAPTURE1_SEL:8;
  uint32                         :16;
} stc_TCPWM_GRP_CNT_TR_IN_SEL1_field_t;

typedef union un_TCPWM_GRP_CNT_TR_IN_SEL1 {
  uint32                         u32Register;
  stc_TCPWM_GRP_CNT_TR_IN_SEL1_field_t stcField;
  uint8                          au8Byte[4];
  uint16                         au16Halfword[2];
} un_TCPWM_GRP_CNT_TR_IN_SEL1_t;

/**
  * \brief Counter input trigger edge selection register (TCPWM_GRP_CNT_TR_IN_EDGE_SEL)
  */
typedef struct stc_TCPWM_GRP_CNT_TR_IN_EDGE_SEL_field {
  uint32                         u2CAPTURE0_EDGE:2;
  uint32                         u2COUNT_EDGE:2;
  uint32                         u2RELOAD_EDGE:2;
  uint32                         u2STOP_EDGE:2;
  uint32                         u2START_EDGE:2;
  uint32                         u2CAPTURE1_EDGE:2;
  uint32                         :20;
} stc_TCPWM_GRP_CNT_TR_IN_EDGE_SEL_field_t;

typedef union un_TCPWM_GRP_CNT_TR_IN_EDGE_SEL {
  uint32                         u32Register;
  stc_TCPWM_GRP_CNT_TR_IN_EDGE_SEL_field_t stcField;
  uint8                          au8Byte[4];
  uint16                         au16Halfword[2];
} un_TCPWM_GRP_CNT_TR_IN_EDGE_SEL_t;

/**
  * \brief Counter trigger PWM control register (TCPWM_GRP_CNT_TR_PWM_CTRL)
  */
typedef struct stc_TCPWM_GRP_CNT_TR_PWM_CTRL_field {
  uint32                         u2CC0_MATCH_MODE:2;
  uint32                         u2OVERFLOW_MODE:2;
  uint32                         u2UNDERFLOW_MODE:2;
  uint32                         u2CC1_MATCH_MODE:2;
  uint32                         :24;
} stc_TCPWM_GRP_CNT_TR_PWM_CTRL_field_t;

typedef union un_TCPWM_GRP_CNT_TR_PWM_CTRL {
  uint32                         u32Register;
  stc_TCPWM_GRP_CNT_TR_PWM_CTRL_field_t stcField;
  uint8                          au8Byte[4];
  uint16                         au16Halfword[2];
} un_TCPWM_GRP_CNT_TR_PWM_CTRL_t;

/**
  * \brief Counter output trigger selection register (TCPWM_GRP_CNT_TR_OUT_SEL)
  */
typedef struct stc_TCPWM_GRP_CNT_TR_OUT_SEL_field {
  uint32                         u3OUT0:3;
  uint32                         :1;
  uint32                         u3OUT1:3;
  uint32                         :25;
} stc_TCPWM_GRP_CNT_TR_OUT_SEL_field_t;

typedef union un_TCPWM_GRP_CNT_TR_OUT_SEL {
  uint32                         u32Register;
  stc_TCPWM_GRP_CNT_TR_OUT_SEL_field_t stcField;
  uint8                          au8Byte[4];
  uint16                         au16Halfword[2];
} un_TCPWM_GRP_CNT_TR_OUT_SEL_t;

/**
  * \brief Interrupt request register (TCPWM_GRP_CNT_INTR)
  */
typedef struct stc_TCPWM_GRP_CNT_INTR_field {
  uint32                         u1TC:1;
  uint32                         u1CC0_MATCH:1;
  uint32                         u1CC1_MATCH:1;
  uint32                         :29;
} stc_TCPWM_GRP_CNT_INTR_field_t;

typedef union un_TCPWM_GRP_CNT_INTR {
  uint32                         u32Register;
  stc_TCPWM_GRP_CNT_INTR_field_t   stcField;
  uint8                          au8Byte[4];
  uint16                         au16Halfword[2];
} un_TCPWM_GRP_CNT_INTR_t;

/**
  * \brief Interrupt set request register (TCPWM_GRP_CNT_INTR_SET)
  */
typedef struct stc_TCPWM_GRP_CNT_INTR_SET_field {
  uint32                         u1TC:1;
  uint32                         u1CC0_MATCH:1;
  uint32                         u1CC1_MATCH:1;
  uint32                         :29;
} stc_TCPWM_GRP_CNT_INTR_SET_field_t;

typedef union un_TCPWM_GRP_CNT_INTR_SET {
  uint32                         u32Register;
  stc_TCPWM_GRP_CNT_INTR_SET_field_t stcField;
  uint8                          au8Byte[4];
  uint16                         au16Halfword[2];
} un_TCPWM_GRP_CNT_INTR_SET_t;

/**
  * \brief Interrupt mask register (TCPWM_GRP_CNT_INTR_MASK)
  */
typedef struct stc_TCPWM_GRP_CNT_INTR_MASK_field {
  uint32                         u1TC:1;
  uint32                         u1CC0_MATCH:1;
  uint32                         u1CC1_MATCH:1;
  uint32                         :29;
} stc_TCPWM_GRP_CNT_INTR_MASK_field_t;

typedef union un_TCPWM_GRP_CNT_INTR_MASK {
  uint32                         u32Register;
  stc_TCPWM_GRP_CNT_INTR_MASK_field_t stcField;
  uint8                          au8Byte[4];
  uint16                         au16Halfword[2];
} un_TCPWM_GRP_CNT_INTR_MASK_t;

/**
  * \brief Interrupt masked request register (TCPWM_GRP_CNT_INTR_MASKED)
  */
typedef struct stc_TCPWM_GRP_CNT_INTR_MASKED_field {
  uint32                         u1TC:1;
  uint32                         u1CC0_MATCH:1;
  uint32                         u1CC1_MATCH:1;
  uint32                         :29;
} stc_TCPWM_GRP_CNT_INTR_MASKED_field_t;

typedef union un_TCPWM_GRP_CNT_INTR_MASKED {
  uint32                         u32Register;
  stc_TCPWM_GRP_CNT_INTR_MASKED_field_t stcField;
  uint8                          au8Byte[4];
  uint16                         au16Halfword[2];
} un_TCPWM_GRP_CNT_INTR_MASKED_t;



/**
  * \brief Timer/Counter/PWM Counter Module (TCPWM_GRP_CNT)
  */
typedef struct stc_TCPWM_GRP_CNT {
  un_TCPWM_GRP_CNT_CTRL_t          unCTRL;             /*!< 0x00000000 Counter control register */
  un_TCPWM_GRP_CNT_STATUS_t        unSTATUS;           /*!< 0x00000004 Counter status register */
  un_TCPWM_GRP_CNT_COUNTER_t       unCOUNTER;          /*!< 0x00000008 Counter count register */
  uint32                         u32Reserved;
  un_TCPWM_GRP_CNT_CC0_t           unCC0;              /*!< 0x00000010 Counter compare/capture 0 register */
  un_TCPWM_GRP_CNT_CC0_BUFF_t      unCC0_BUFF;         /*!< 0x00000014 Counter buffered compare/capture 0 register */
  un_TCPWM_GRP_CNT_CC1_t           unCC1;              /*!< 0x00000018 Counter compare/capture 1 register */
  un_TCPWM_GRP_CNT_CC1_BUFF_t      unCC1_BUFF;         /*!< 0x0000001C Counter buffered compare/capture 1 register */
  un_TCPWM_GRP_CNT_PERIOD_t        unPERIOD;           /*!< 0x00000020 Counter period register */
  un_TCPWM_GRP_CNT_PERIOD_BUFF_t   unPERIOD_BUFF;      /*!< 0x00000024 Counter buffered period register */
  un_TCPWM_GRP_CNT_LINE_SEL_t      unLINE_SEL;         /*!< 0x00000028 Counter line selection register */
  un_TCPWM_GRP_CNT_LINE_SEL_BUFF_t unLINE_SEL_BUFF;    /*!< 0x0000002C Counter buffered line selection register */
  un_TCPWM_GRP_CNT_DT_t            unDT;               /*!< 0x00000030 Counter PWM dead time register */
  uint32                         au32Reserved1[3];
  un_TCPWM_GRP_CNT_TR_CMD_t        unTR_CMD;           /*!< 0x00000040 Counter trigger command register */
  un_TCPWM_GRP_CNT_TR_IN_SEL0_t    unTR_IN_SEL0;       /*!< 0x00000044 Counter input trigger selection register 0 */
  un_TCPWM_GRP_CNT_TR_IN_SEL1_t    unTR_IN_SEL1;       /*!< 0x00000048 Counter input trigger selection register 1 */
  un_TCPWM_GRP_CNT_TR_IN_EDGE_SEL_t unTR_IN_EDGE_SEL;  /*!< 0x0000004C Counter input trigger edge selection register */
  un_TCPWM_GRP_CNT_TR_PWM_CTRL_t   unTR_PWM_CTRL;      /*!< 0x00000050 Counter trigger PWM control register */
  un_TCPWM_GRP_CNT_TR_OUT_SEL_t    unTR_OUT_SEL;       /*!< 0x00000054 Counter output trigger selection register */
  uint32                         au32Reserved2[6];
  un_TCPWM_GRP_CNT_INTR_t          unINTR;             /*!< 0x00000070 Interrupt request register */
  un_TCPWM_GRP_CNT_INTR_SET_t      unINTR_SET;         /*!< 0x00000074 Interrupt set request register */
  un_TCPWM_GRP_CNT_INTR_MASK_t     unINTR_MASK;        /*!< 0x00000078 Interrupt mask register */
  un_TCPWM_GRP_CNT_INTR_MASKED_t   unINTR_MASKED;      /*!< 0x0000007C Interrupt masked request register */
} stc_TCPWM_GRP_CNT_t;                                 /*!< Size = 128 (0x80) */

/**
  * \brief Group of counters (TCPWM_GRP)
  */
typedef struct stc_TCPWM_GRP {
  stc_TCPWM_GRP_CNT_t              CNT[256];           /*!< 0x00000000 Timer/Counter/PWM Counter Module */
} stc_TCPWM_GRP_t;                                     /*!< Size = 32768 (0x8000) */

/**
  * \brief Timer/Counter/PWM (TCPWM)
  */
typedef struct stc_TCPWM {
  stc_TCPWM_GRP_t                  GRP[4];             /*!< 0x00000000 Group of counters */
} stc_TCPWM_t;                                         /*!< Size = 131072 (0x20000) */

//Divider command
typedef struct ts_PERI_DIV_CMD
{
  uint32 u8DIV_SEL     : 8;
  uint32 u2TYPE_SEL    : 2;
  uint32               : 6;
  uint32 u8PA_DIV_SEL  : 8;
  uint32 u2PA_TYPE_SEL : 2;
  uint32               : 4;
  uint32 u1DISABLE     : 1;
  uint32 u1ENABLE      : 1;
} ts_PERI_DIV_CMD;

typedef union tu_PERI_DIV_CMD
{
  ts_PERI_DIV_CMD sBit;
  uint32                        ulData;
  uint16                        aunData[2];
  uint8                         aucData[4];
} tu_PERI_DIV_CMD;

//Clock Control
typedef struct ts_PERI_CLOCK_CTL
{
  uint32 u8DIV_SEL  : 8;
  uint32 u2TYPE_SEL : 2;
  uint32            : 22;
}ts_PERI_CLOCK_CTL;

typedef union tu_PERI_CLOCK_CTL
{
  ts_PERI_CLOCK_CTL sBit;
  uint32                          ulData;
  uint16                          aunData[2];
  uint8                           aucData[4];
} tu_PERI_CLOCK_CTL;

//Divider control for 8.0 divider
typedef struct ts_PERI_DIV_8
{
  uint32 u1EN       : 1;
  uint32            : 7;
  uint32 u8INT8_DIV : 8;
  uint32            : 16;
} ts_PERI_DIV_8;

typedef union tu_PERI_DIV_8
{
  ts_PERI_DIV_8 sBit;
  uint32                      ulData;
  uint16                      aunData[2];
  uint8                       aucData[4];
} tu_PERI_DIV_8;

typedef struct ts_PERI
{
  uint32                          aulReserved1[256];        //0x00000000
  tu_PERI_DIV_CMD                 unDIV_CMD;                //0x00000400
  uint32                          aulReserved2[511];        //0x00000BFC
  tu_PERI_CLOCK_CTL               unCLOCK_CTL[256];         //0x00000C00
  tu_PERI_DIV_8                   unDIV_8_CTL[256];         //0x00001000
}ts_PERI;


#endif // CDD_STP_TSP_TYPES_2020_03_05_H_

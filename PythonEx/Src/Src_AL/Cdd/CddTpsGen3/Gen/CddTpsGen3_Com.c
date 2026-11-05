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
/// \file  CddTpsGen3_Com.c
///
/// \brief
///
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
///
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
//standard includes
#include <AL_Helper.h>

//module API include path
#include <CddTpsGen3.h>
#include <CddTpsGen3_Cb.h>
#include <CddTpsGen3_Cod.h>
#include <Dio.h>

//module includes relative to API
#include <CddTpsGen3_Cfg.h>
#include <CddTpsGen3_Com.h>
#include <CddTpsGen3_Types.h>
#include <CddTpsGen3_Sched.h>
 

//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------

#define CDDTPSGEN3_SET_BIT_U8(var, bitPos) ((var) |= (uint8)((uint8)1u << (uint8)(bitPos)))
#define CDDTPSGEN3_CLR_BIT_U8(var, bitPos) ((var) &= (uint8)(~(uint8)((uint8)1u << (uint8)(bitPos))))
#define CDDTPSGEN3_SET_CLR_CONDITION_U8(cnd, var, bitPos) ((cnd) == FALSE) ? (uint8)CDDTPSGEN3_SET_BIT_U8((var), (bitPos)) : (uint8)CDDTPSGEN3_CLR_BIT_U8((var), (bitPos))

#define CDDTPSGEN3_ENABLE_BIT           1u
#define CDDTPSGEN3_DISABLE_BIT          0u


/* ---------------------------------------------*/
/*           Data Mirror Defines                */
/* ---------------------------------------------*/

#if (CFG_MAX_NO_OF_MLC_CHIPS == 1)
#define CDDTPSGEN3_INIT(x) { x }
#elif (CFG_MAX_NO_OF_MLC_CHIPS == 7)
#define CDDTPSGEN3_INIT(x) { x, x, x, x, x, x, x }
#elif (CFG_MAX_NO_OF_MLC_CHIPS == 8)
#define CDDTPSGEN3_INIT(x) { x, x, x, x, x, x, x, x }
#endif /* (CDDTPSGE32_Cfg_NbOfDevices = maximum nb of GEN3 chips allowed on the bus) */

#if (CFG_MAX_NO_OF_MLC_CHIPS > 0U)
#define CDDTPSGEN3_INIT_ADCID_MAP 0x00u
#elif (CFG_MAX_NO_OF_MLC_CHIPS > 8U)
#define CDDTPSGEN3_INIT_ADCID_MAP 0x01u
#elif (CFG_MAX_NO_OF_MLC_CHIPS > 16U)
#error "The TPS9266x GEN3 chip supports up to 16 devices on the bus"
#endif


#define CDDTPSGEN3_REG_3BYTES_INIT(x)    { x, x, x }
#define CDDTPSGEN3_REG_4BYTES_INIT(x)    { x, x, x, x }
#define CDDTPSGEN3_REG_5BYTES_INIT(x)    { x, x, x, x, x }
#define CDDTPSGEN3_REG_6BYTES_INIT(x)    { x, x, x, x, x, x }
#define CDDTPSGEN3_REG_8BYTES_INIT(x)    { x, x, x, x, x, x, x, x }
#define CDDTPSGEN3_REG_9BYTES_INIT(x)    { x, x, x, x, x, x, x, x, x }
#define CDDTPSGEN3_REG_10BYTES_INIT(x)   { x, x, x, x, x, x, x, x, x, x }
#define CDDTPSGEN3_REG_16BYTES_INIT(x)   { x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x }
#define CDDTPSGEN3_REG_18BYTES_INIT(x)   { x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x }
#define CDDTPSGEN3_REG_22BYTES_INIT(x)   { x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x }
#define CDDTPSGEN3_REG_34BYTES_INIT(x)   { x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x }


         #define CDDTPSGEN3_InitZeroReg                0x00u

/*  1 */ #define CDDTPSGEN3_TxRegPHASE_MSB_Init        { .ucByte =  CDDTPSGEN3_REG_16BYTES_INIT(CDDTPSGEN3_InitZeroReg)              }
/*  2 */ #define CDDTPSGEN3_TxRegPHASE_LSB_Init        { .ucByte =  CDDTPSGEN3_REG_4BYTES_INIT (CDDTPSGEN3_InitZeroReg)              }
/*  3 */ #define CDDTPSGEN3_TxRegWIDTH_MSB_Init        { .ucByte =  CDDTPSGEN3_REG_16BYTES_INIT(CDDTPSGEN3_InitZeroReg)              }
/*  4 */ #define CDDTPSGEN3_TxRegWIDTH_LSB_Init        { .ucByte =  CDDTPSGEN3_REG_4BYTES_INIT (CDDTPSGEN3_InitZeroReg)              }
/*  5 */ #define CDDTPSGEN3_TxRegSTRINGS_Init          { .ucByte = { CDDTPSGEN3_SET_SLEWRATE_REGL((uint8)MEDIUM_SLEWRATE),  CDDTPSGEN3_SET_SLEWRATE_REGH((uint8)MEDIUM_SLEWRATE) } }

/*  6 */ #define CDDTPSGEN3_TxRegDEFAULT_Init          { .ucByte =  CDDTPSGEN3_REG_16BYTES_INIT(CDDTPSGEN3_InitZeroReg)              }


/*  7 */ #define CDDTPSGEN3_TxRegSYSCFG_DEFAULTVAL_Init        { .Bit =  {  .biCSEN      = CDDTPSGEN3_DISABLE_BIT,                          \
                                                                            .biCHPMP_SS  = CDDTPSGEN3_DISABLE_BIT,                          \
                                                                            .biCSGAIN    = CDDTPSGEN3_DISABLE_BIT,                          \
                                                                            .biCMWEN     = CDDTPSGEN3_DISABLE_BIT,                          \
                                                                            .biPSON      = CDDTPSGEN3_DISABLE_BIT,                          \
                                                                            .biACKEN     = CDDTPSGEN3_ENABLE_BIT,                           \
                                                                            .biLEDADCEN  = CDDTPSGEN3_DISABLE_BIT,                          \
                                                                            .biSEPTR     = CDDTPSGEN3_DISABLE_BIT                   }  }



/*  8 */ #define CDDTPSGEN3_TxRegSYSCFG_Init           { .sSysReg = { .RegSYSCFG  = { .Bit =  {  .biCSEN      = CDDTPSGEN3_DISABLE_BIT,                          \
                                                                                                 .biCHPMP_SS  = CDDTPSGEN3_ENABLE_BIT,                           \
                                                                                                 .biCSGAIN    = CDDTPSGEN3_DISABLE_BIT,                          \
                                                                                                 .biCMWEN     = CDDTPSGEN3_ENABLE_BIT,                           \
                                                                                                 .biPSON      = CDDTPSGEN3_DISABLE_BIT,                          \
                                                                                                 .biACKEN     = CDDTPSGEN3_ENABLE_BIT,                           \
                                                                                                 .biLEDADCEN  = CDDTPSGEN3_DISABLE_BIT,                          \
                                                                                                 .biSEPTR     = CDDTPSGEN3_DISABLE_BIT                   }  },   \
                                                                      .RegCMWTAP  = { .Bit =  {  .biCMWTAP   =  CDDTPSGEN3_CFG_CMWTAP_8MHz               }  },   \
                                                                      .RegPWMTICK = { .Bit =  {  .biPTCNT    =  CDDTPSGEN3_CFG_PWMTICK_8MHz              }  }  } \
                                                       }

/*  9 */ #define CDDTPSGEN3_TxRegSOFTSYNC_STATUS_Init  { .sSSYNC_STATUS = { .RegCLK_SYNC = { .Bit = {   .biSSYNC       = CDDTPSGEN3_ENABLE_BIT,                  \
                                                                                                        .biCLK_IS_EXT  = CDDTPSGEN3_DISABLE_BIT          }  },   \
                                                                            .RegSTATUS   = { .Bit = {   .biPWR         = CDDTPSGEN3_ENABLE_BIT           }  }  } \
                                                       }

/* 10 */ #define CDDTPSGEN3_TxRegMTPCFG_FailSafe_Init   { .Bit     = { .biFS_PIN = CDDTPSGEN3_ENABLE_BIT } }
/* 11 */ #define CDDTPSGEN3_TxRegOUTCTRL_Init           { .ucRaw   =  CDDTPSGEN3_InitZeroReg   }
/* 12 */ #define CDDTPSGEN3_TxRegELECFAULT_Init         { .ucByte  = {  CDDTPSGEN3_InitZeroReg, CDDTPSGEN3_InitZeroReg, CDDTPSGEN3_InitZeroReg, CDDTPSGEN3_InitZeroReg }} 


/*  1*/    #define CDDTPSGEN3_RxCmdICID_Init           { CDDTPSGEN3_REG_3BYTES_INIT(CDDTPSGEN3_InitZeroReg)      }
/*  2*/    #define CDDTPSGEN3_RxCmdSYSCONFIG_Init      { CDDTPSGEN3_REG_5BYTES_INIT(CDDTPSGEN3_InitZeroReg)      }
/*  3*/    #define CDDTPSGEN3_RxCmdSYSCFG_Init         { CDDTPSGEN3_InitZeroReg      }
/*  4*/    #define CDDTPSGEN3_RxCmdSSYNC_STATUS_Init   { CDDTPSGEN3_InitZeroReg      }
/* 5,6 */  #define CDDTPSGEN3_RxCmdPHASES_Init         { CDDTPSGEN3_InitZeroReg      }
/* 7,8*/   #define CDDTPSGEN3_RxCmdCFGLEDS_Init        { CDDTPSGEN3_InitZeroReg      }
/*  9*/    #define CDDTPSGEN3_RxCmdEXIT_FS_Init        { CDDTPSGEN3_InitZeroReg      }
/* 10*/    #define CDDTPSGEN3_RxCmdOUTCTRL_Init        { CDDTPSGEN3_InitZeroReg      }
/* 11*/    #define CDDTPSGEN3_RxCmdPWMS_MSB_Init       { CDDTPSGEN3_InitZeroReg      }
/* 12 */   #define CDDTPSGEN3_RxCmdPWMS_LSB_Init       { CDDTPSGEN3_InitZeroReg      }
/* 13*/    #define CDDTPSGEN3_RxCmdELEFAULT_Init       { .ucRxByte = CDDTPSGEN3_REG_6BYTES_INIT(CDDTPSGEN3_InitZeroReg) }
/* 14 */   #define CDDTPSGEN3_RxCmdCLR_ELEFAULT_Init   { CDDTPSGEN3_InitZeroReg      }
/* 15 */   #define CDDTPSGEN3_RxCmdADC_Init            { .ucRxByte = CDDTPSGEN3_REG_6BYTES_INIT(CDDTPSGEN3_InitZeroReg) }
/* 16*/    #define CDDTPSGEN3_RxCmdSTATUS_Init         { .ucRxByte = CDDTPSGEN3_REG_3BYTES_INIT(CDDTPSGEN3_InitZeroReg) }
/* 17*/    #define CDDTPSGEN3_RxCmdSLEWRATE_Init       { .ucRxByte = CDDTPSGEN3_REG_6BYTES_INIT(CDDTPSGEN3_InitZeroReg) }

/* Initialization values of Data Mirror of GEN3 family registers */
#define CDDTPSGEN3_DataMirror_InitZero                                             \
{                                                                                  \
  { /* CtrlTx */                                                                   \
    /*  1 */  CDDTPSGEN3_INIT(CDDTPSGEN3_TxRegPHASE_MSB_Init),                     \
    /*  2 */  CDDTPSGEN3_INIT(CDDTPSGEN3_TxRegPHASE_LSB_Init),                     \
    /*  3 */  CDDTPSGEN3_INIT(CDDTPSGEN3_TxRegWIDTH_MSB_Init),                     \
    /*  4 */  CDDTPSGEN3_INIT(CDDTPSGEN3_TxRegWIDTH_LSB_Init),                     \
    /*  5 */  CDDTPSGEN3_INIT(CDDTPSGEN3_TxRegSTRINGS_Init),                       \
    /*  6 */  CDDTPSGEN3_INIT(CDDTPSGEN3_TxRegDEFAULT_Init),                       \
    /*  7 */  CDDTPSGEN3_INIT(CDDTPSGEN3_TxRegSYSCFG_DEFAULTVAL_Init),             \
    /*  8 */  CDDTPSGEN3_INIT(CDDTPSGEN3_TxRegSYSCFG_Init),                        \
    /*  9 */  CDDTPSGEN3_INIT(CDDTPSGEN3_TxRegSOFTSYNC_STATUS_Init),               \
    /* 10 */  CDDTPSGEN3_INIT(CDDTPSGEN3_TxRegMTPCFG_FailSafe_Init),               \
    /* 11 */  CDDTPSGEN3_INIT(CDDTPSGEN3_TxRegOUTCTRL_Init),                       \
    /* 12 */  CDDTPSGEN3_INIT(CDDTPSGEN3_TxRegELECFAULT_Init)                      \
  },                                                                               \
  { /* StatRx */                                                                   \
    /*  1 */  CDDTPSGEN3_INIT(CDDTPSGEN3_RxCmdICID_Init),                          \
    /*  2 */  CDDTPSGEN3_INIT(CDDTPSGEN3_RxCmdSYSCONFIG_Init),                     \
    /*  3 */  CDDTPSGEN3_INIT(CDDTPSGEN3_RxCmdSYSCFG_Init),                        \
    /*  4 */  CDDTPSGEN3_INIT(CDDTPSGEN3_RxCmdSSYNC_STATUS_Init),                  \
    /*  5 */  CDDTPSGEN3_INIT(CDDTPSGEN3_RxCmdPHASES_Init),                        \
    /*  6 */  CDDTPSGEN3_INIT(CDDTPSGEN3_RxCmdPHASES_Init),                        \
    /*  7 */  CDDTPSGEN3_INIT(CDDTPSGEN3_RxCmdCFGLEDS_Init),                       \
    /*  8 */  CDDTPSGEN3_INIT(CDDTPSGEN3_RxCmdCFGLEDS_Init),                       \
    /*  9 */  CDDTPSGEN3_INIT(CDDTPSGEN3_RxCmdEXIT_FS_Init),                       \
    /* 10 */  CDDTPSGEN3_INIT(CDDTPSGEN3_RxCmdOUTCTRL_Init),                       \
    /* 11 */  CDDTPSGEN3_INIT(CDDTPSGEN3_RxCmdPWMS_MSB_Init),                      \
    /* 12 */  CDDTPSGEN3_INIT(CDDTPSGEN3_RxCmdPWMS_LSB_Init),                      \
    /* 13 */  CDDTPSGEN3_INIT(CDDTPSGEN3_RxCmdELEFAULT_Init),                      \
    /* 14 */  CDDTPSGEN3_INIT(CDDTPSGEN3_RxCmdCLR_ELEFAULT_Init),                  \
    /* 15 */  CDDTPSGEN3_INIT(CDDTPSGEN3_RxCmdADC_Init),                           \
    /* 16 */  CDDTPSGEN3_INIT(CDDTPSGEN3_RxCmdSTATUS_Init),                        \
    /* 17 */  CDDTPSGEN3_INIT(CDDTPSGEN3_RxCmdSLEWRATE_Init)                       \
  }                                                                                \
}


/*  1 */  #define CDDTPSGEN3_PHASE_MSB_Tx         &CddTpsGen3_DataMirror.CtrlTx.RegPHASE_MSB[0].ucByte[0]
/*  2 */  #define CDDTPSGEN3_PHASE_LSB_Tx         &CddTpsGen3_DataMirror.CtrlTx.RegPHASE_LSB[0].ucByte[0]
/*  3 */  #define CDDTPSGEN3_WIDTH_MSB_Tx         &CddTpsGen3_DataMirror.CtrlTx.RegWIDTH_MSB[0].ucByte[0]
/*  4 */  #define CDDTPSGEN3_WIDTH_LSB_Tx         &CddTpsGen3_DataMirror.CtrlTx.RegWIDTH_LSB[0].ucByte[0]
/*  5 */  #define CDDTPSGEN3_SLEWRATE_Tx          &CddTpsGen3_DataMirror.CtrlTx.RegSLEWRATE[0].ucByte[0]
/*  6 */  #define CDDTPSGEN3_DEFWIDTH_Tx          &CddTpsGen3_DataMirror.CtrlTx.RegDEFWIDTH[0].ucByte[0]
/*  7 */  #define CDDTPSGEN3_SYSCFG_DEFAULT_Tx    &CddTpsGen3_DataMirror.CtrlTx.RegSYSCFG_DEFAULT[0].ucRaw
/*  8 */  #define CDDTPSGEN3_SYSCFG_Tx            &CddTpsGen3_DataMirror.CtrlTx.RegSYSCFG[0].ucByte[0]
/*  9 */  #define CDDTPSGEN3_SSYNC_STATUS_Tx      &CddTpsGen3_DataMirror.CtrlTx.RegSSYNC_STATUS[0].ucByte[0]
/* 10 */  #define CDDTPSGEN3_MTPCFG_FS_Tx         &CddTpsGen3_DataMirror.CtrlTx.Reg_MPTCFG_FS[0].ucRaw
/* 11 */  #define CDDTPSGEN3_OUTCTRL_Tx           &CddTpsGen3_DataMirror.CtrlTx.RegOUTCTRL[0].ucRaw
/* 12 */  #define CDDTPSGEN3_ELECFAULTS_Tx        &CddTpsGen3_DataMirror.CtrlTx.RegELEFAULT[0].ucByte[0]

/*  1 */  #define CDDTPSGEN3_ICID_Rx              &CddTpsGen3_DataMirror.StatRx.RxICID[0].ucRxByte[0]
/*  2 */  #define CDDTPSGEN3_SYSCONFIG_Rx         &CddTpsGen3_DataMirror.StatRx.RxSYSCONFIG[0].ucRxByte[0]
/*  3 */  #define CDDTPSGEN3_SYSCFG_Rx            &CddTpsGen3_DataMirror.StatRx.RxSYSCFG[0].ucRxByte[0]
/*  4 */  #define CDDTPSGEN3_SSYNC_STATUS_Rx      &CddTpsGen3_DataMirror.StatRx.RxSSYNC_STATUS[0].ucRxByte[0]
/*  5 */  #define CDDTPSGEN3_PHASES_MSB_Rx        &CddTpsGen3_DataMirror.StatRx.RxPHASES_MSB[0].ucRxByte[0]
/*  6 */  #define CDDTPSGEN3_PHASES_LSB_Rx        &CddTpsGen3_DataMirror.StatRx.RxPHASES_LSB[0].ucRxByte[0]
/*  7 */  #define CDDTPSGEN3_CFGLEDS_Rx           &CddTpsGen3_DataMirror.StatRx.RxCFGLEDS[0].ucRxByte[0]
/*  8 */  #define CDDTPSGEN3_CFGDEF_Rx            &CddTpsGen3_DataMirror.StatRx.RxCFGDEF[0].ucRxByte[0]
/*  9 */  #define CDDTPSGEN3_EXIT_FS_Rx           &CddTpsGen3_DataMirror.StatRx.RxEXIT_FS[0].ucRxByte[0]
/* 10 */  #define CDDTPSGEN3_OUTCTRL_Rx           &CddTpsGen3_DataMirror.StatRx.RxOUTCTRL[0].ucRxByte[0]
/* 11 */  #define CDDTPSGEN3_PWM_MSB_Rx           &CddTpsGen3_DataMirror.StatRx.RxPWMS_MSB[0].ucRxByte[0]
/* 12 */  #define CDDTPSGEN3_PWM_LSB_Rx           &CddTpsGen3_DataMirror.StatRx.RxPWMS_LSB[0].ucRxByte[0]
/* 13 */  #define CDDTPSGEN3_ELEFAULT_Rx          &CddTpsGen3_DataMirror.StatRx.RxELEFAULT[0].ucRxByte[0]
/* 14 */  #define CDDTPSGEN3_CLR_ELEFAULT_Rx      &CddTpsGen3_DataMirror.StatRx.RxCLR_ELEFAULT[0].ucRxByte[0]
/* 15 */  #define CDDTPSGEN3_ADC_Rx               &CddTpsGen3_DataMirror.StatRx.RxADC[0].ucRxByte[0]
/* 16 */  #define CDDTPSGEN3_STATUS_Rx            &CddTpsGen3_DataMirror.StatRx.RxSTATUS[0].ucRxByte[0]
/* 17 */  #define CDDTPSGEN3_SLEWRATE_Rx          &CddTpsGen3_DataMirror.StatRx.RxSLEWRATE[0].ucRxByte[0]



/* ---------------------------------------------------------------*/
/*           Initialization of Broadcast Cmd Arrays               */
/* ---------------------------------------------------------------*/

#define CDDTPSGEN3_RxBrdADCID_Init      { .ucRxByte = CDDTPSGEN3_REG_3BYTES_INIT(CDDTPSGEN3_InitZeroReg) }
#define CDDTPSGEN3_RxBrdSYSCFG_Init     { .ucRxByte = CDDTPSGEN3_REG_3BYTES_INIT(CDDTPSGEN3_InitZeroReg) }

#define BroadcastData_Init        \
{                                 \
   CDDTPSGEN3_RxBrdADCID_Init,    \
   CDDTPSGEN3_RxBrdSYSCFG_Init    \
}

#define CDDTPSGEN3_BROADCAST1_ADCID_Rx   &CddTpsGen3_BroadcastData.RxBrADCID.ucRxByte[0]
#define CDDTPSGEN3_BROADCAST2_SYSCFG_Rx  &CddTpsGen3_BroadcastData.RxBrSYSCFG.ucRxByte[0]

          #define CDDTPSGEN3_Zero_Tx              &CddTpsGen3_aucZero[0]
          #define CDDTPSGEN3_Dummy_Rx             &CddTpsGen3_ucDummy[0]


//-----------------------------------------------------------------------------
// Local types
//-----------------------------------------------------------------------------
// UART schedule table entry datatype
typedef struct tsCddTpsGen3_UartSchedTable
{
  sint8 scNextEntry;                //offset to next scheduler table entry
  uint8 ucAction;                   // index of action function done after Rx
  teGen3_DynCmdType  eDynCmd;       // dynamic command type evaluation
  uint8  ucCmd;                     // read/write command to send
  uint8  ucRegAddr;                 // device register address
  uint8* pucTx;                     // control register data for transmission
  uint8  ucTxSize;                  // size of Tx Buffer command data
  uint8* pucRx;                     // status register data for reception
  uint8  ucRxSize;                  // size of Rx Buffer received data
} tsCddTpsGen3_UartSchedTable;

//-----------------------------------------------------------------------------
// Definitions of initialized variables
//-----------------------------------------------------------------------------

STATIC_AL uint8     CddTpsGen3_ucSchedIx = 0u;  // pointer to scheduler table
STATIC_AL uint8     CddTpsGen3_ucChipIdx = 0u;  // index of current device
STATIC_AL uint8     CddTpsGen3_ucChipIdx_MuxCmd = 0u;  // index of current device for mux commands

STATIC_AL boolean   CddTpsGen3_aboComStatus[CFG_MAX_NO_OF_MLC_CHIPS];
STATIC_AL boolean   CddTpsGen3_aboCrcStatus[CFG_MAX_NO_OF_MLC_CHIPS];
STATIC_AL uint8     CddTpsGen3_ucPowerOnReset_Bit = 0u;
STATIC_AL boolean   CddTpsGen3_boMuxCmdCompleted = FALSE;
STATIC_AL boolean   CddTpsGen3_boInitCompleted = FALSE;

STATIC_AL CONST_AL uint16 CddTpsGen3_aunPhaseShifts_TPS9266x  [][CDDTPSGEN3_TPS9266x_MAX_SWITCHS_PER_DEVICE] = CDDTPSGEN3_PHASE_SHIFT_CFG;
STATIC_AL CONST_AL uint8  CddTpsGen3_aucDefaultWidths_TPS9266x[][CDDTPSGEN3_TPS9266x_MAX_SWITCHS_PER_DEVICE] = CDDTPSGEN3_DEFAULT_WIDTHS;
STATIC_AL CONST_AL uint8  CddTpsGen3_aucConfigSlewrate_LSB[] = CDDTPSGEN3_CFG_SLEWRATE_REGL;
STATIC_AL CONST_AL uint8  CddTpsGen3_aucConfigSlewrate_MSB[] = CDDTPSGEN3_CFG_SLEWRATE_REGH;


//-----------------------------------------------------------------------------
// Definitions of initialized structures and unions or arrays variables
//-----------------------------------------------------------------------------

STATIC_AL uint8  CddTpsGen3_ucDummy[CFG_MAX_NO_OF_MLC_CHIPS] = { 0u };  // for dummy receive Uart Frames
STATIC_AL uint8  CddTpsGen3_aucZero[CFG_MAX_NO_OF_MLC_CHIPS] = { 0u };

STATIC_AL tsCddTpsGen3_DataMirror CddTpsGen3_DataMirror     = CDDTPSGEN3_DataMirror_InitZero;
STATIC_AL tsCddTpsGen3_BrCmd      CddTpsGen3_BroadcastData  = BroadcastData_Init;

STATIC_AL CONST_AL tsCddTpsGen3_UartSchedTable CddTpsGen3_asUartSchedTable[] = CDDTPSGEN3_Cfg_UartSchedTable_Init;

//-----------------------------------------------------------------------------
// Definitions of non initialized variables
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Definitions of non initialized structures and unions or arrays variables
//-----------------------------------------------------------------------------
STATIC_AL uint8 CddTpsGen3_aucTxBuffer[CDDTPSGEN3_MAX_CMD_LENGTH];

//-----------------------------------------------------------------------------
// Function prototypes
//-----------------------------------------------------------------------------
STATIC_AL void    CddTpsGen3_SetComStatus(boolean boRxStat, teGen3_DynCmdType eCmdType);

STATIC_AL void    CddTpsGen3_BuildTxFrame     (const tsCddTpsGen3_UartSchedTable* psEntryData, uint8 ucChipAddress, uint8 ucChipIdx, tsCddUart_MessageEntryType*  sTxCbData);
STATIC_AL void    CddTpsGen3_PrepareTxFrameForSingleCmd(tsCddUart_MessageEntryType* psTxCbData, const tsCddTpsGen3_UartSchedTable* pTabEntry, uint8 ucChipAddress, uint8 ucChipIdx);
STATIC_AL uint16  CddTpsGen3_Calc16BitCRCValue(uint8* pucData, uint8 ucLength);

STATIC_AL void    CddTpsGen3_SchHandle(const tsCddTpsGen3_UartSchedTable* pTabEntry);
STATIC_AL boolean CddTpsGen3_StAction (const uint8 ucAction);
STATIC_AL void    CddTpsGen3_UseDummyTxRx(tsCddUart_MessageEntryType* psTxCbData);

STATIC_AL void    CddTpsGen3_SetPHASEReg_MSB(const uint8_fast ucChipIdx, const uint16* punPhase);
STATIC_AL void    CddTpsGen3_SetPHASEReg_LSB(const uint8_fast ucChipIdx, const uint16* punPhase);
STATIC_AL void    CddTpsGen3_SetCFGLEDSReg  (const uint8_fast ucChipIdx, const uint8* pucDefWidth);

STATIC_AL void    CddTpsGen3_SetWIDTHReg_LSB(const uint8 ucChipIdx, const uint16* punDuty);
STATIC_AL void    CddTpsGen3_SetWIDTHReg_MSB(const uint8 ucChipIdx, const uint16* punDuty);

STATIC_AL boolean CddTpsGen3_CheckCRC(uint8 *ucPtrData, uint8 ucLength);
STATIC_AL boolean CddTpsGen3_CheckReadCommand(const uint8 ucSchCmd);
STATIC_AL void    CddTpsGen3_SetCrcStatus(const tsCddTpsGen3_UartSchedTable *pTabEntry);

//-----------------------------------------------------------------------------
// Function definitions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen3_BuildTxFrame
///
/// \descr  Build the Write Command Frame according to the UART Communications Protocol:
///         INIT | DEVID / 0xBF | REGADRR | DATA1 ..... | DATAn | CRCL | CRCH
///
/// \param  psEntryData
/// \param  ucChipAddress
/// \param  ucChipIdx
/// \param  sTxCbData
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CddTpsGen3_BuildTxFrame(const tsCddTpsGen3_UartSchedTable* psEntryData, uint8 ucChipAddress, uint8 ucChipIdx, tsCddUart_MessageEntryType* sTxCbData)
{
  uint8 ucDataLenght = CDDTPSGEN3_SIZE_HEADERBYTES + psEntryData->ucTxSize;

  sTxCbData->ucTxDataLength = ucDataLenght + CDDTPSGEN3_SIZE_CRCBYTES;

  // Build the command header 
  //             INIT BYTE                     |       DEVID         |           REGADDR
  //    frame initialization (read/write cmd)    (device address)    (starting Register Address byte )

  CddTpsGen3_aucTxBuffer[0] = psEntryData->ucCmd;
  CddTpsGen3_aucTxBuffer[1] = ucChipAddress;
  CddTpsGen3_aucTxBuffer[2] = psEntryData->ucRegAddr;


  //add data into the command frame, after header bytes
  for (uint8 ucByteIdx = 0u; ucByteIdx < psEntryData->ucTxSize; ucByteIdx++)
  {
    CddTpsGen3_aucTxBuffer[CDDTPSGEN3_SIZE_HEADERBYTES + ucByteIdx] = (psEntryData->pucTx[(ucChipIdx * psEntryData->ucTxSize) + ucByteIdx]);
  }

  //calculate the CRC over the full command using look-up table ( CRC-16 IBM)
  uint16 un16CrcValue = CddTpsGen3_Calc16BitCRCValue(&CddTpsGen3_aucTxBuffer[0], ucDataLenght);

  // load the CRC into the final 2 bytes of the frame
  CddTpsGen3_aucTxBuffer[ucDataLenght]      = (uint8)(un16CrcValue & 0xFFu);   // LSByte of CRC
  CddTpsGen3_aucTxBuffer[ucDataLenght + 1u] = (uint8)(un16CrcValue >> 8u);     // MSByte of CRC

  sTxCbData->pucTxData = &CddTpsGen3_aucTxBuffer[0];
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen3_UartTx
///
/// \descr  The function reads the content of the CddTpsGen3_DataMirror and
///         adds the CRC bytes at the end of the command.
///         The function is called before the transmission of UART frame
///         Callback function called by Uart
///
/// \param  psTxCbData
///
/// \return void
//-----------------------------------------------------------------------------
void  CddTpsGen3_UartTx(tsCddUart_MessageEntryType* psTxCbData)
{
  uint8 ucChipAddress = CDDTPSGEN3_ADDR_NOT_CONNECTED;
  uint8 ucRxSize = CddTpsGen3_asUartSchedTable[CddTpsGen3_ucSchedIx].ucRxSize;
  //calculate pointer to actual scheduler table entry
  const tsCddTpsGen3_UartSchedTable* pTabEntry = &CddTpsGen3_asUartSchedTable[CddTpsGen3_ucSchedIx];
  
  //monitor the MLC power supply or coding availability at every new TX message in order to stop the UART communication until the power supply is comming back 
  if ((CddMlc_IsMlcPowered() == FALSE) || (CDDTPSGEN3_Para_IS_CODING_VALID == FALSE))
  {
    psTxCbData->pucTxData = NULL_PTR; //this null pointer will indicate that the UART communication must be empty 
    psTxCbData->ucTxDataLength = 0u; //0 tx data will indicate that the UART communication must be empty 
  }
  //normal behavior
  else
  {
    //prepare DMA with reception parameters
    psTxCbData->pucRxData = pTabEntry->pucRx;
    psTxCbData->ucRxDataLength = ucRxSize;

    // get UART command (read or write), register address and contents of control register for next UART frame
    switch (pTabEntry->eDynCmd)
    {
    case eBroadcastCmd:
      ucChipAddress = (uint8)CDDTPSGEN3_BROADCAST;
      CddTpsGen3_ucChipIdx = 0u;    // reset index for device because after each broadcast will come eSingleFASTCmd
      CddTpsGen3_BuildTxFrame(pTabEntry, ucChipAddress, CddTpsGen3_ucChipIdx, psTxCbData);

      /* Type 1 Command Frame : Broadcast Write
              - Rx data will be the transmitted Tx data,
              hence Rx size = Tx size
       */
      psTxCbData->pucRxData = pTabEntry->pucRx;
      psTxCbData->ucRxDataLength = pTabEntry->ucRxSize;

      break;

    case eSingleFASTCmd:

      /* Rx Size will be calculated as follows :
           Type 2 Command Frame : Single Write Commands
                 case INIT byte = WRITE cmd  ->  RxSize  = Tx command size + ACK
           Type 3 Command Frame : Single Read Command
                 case INIT byte = READ cmd   ->  Rx Size = Tx command size + (N bytes read + 2 CRC) = Tx + Rx data
         */

      if (CddTpsGen3_ucChipIdx < CDDTPSGEN3_Para_COUNT_CONNECTED_DEV)
      {
        ucChipAddress = CDDTPSGEN3_Para_CHIP_ADDR(CddTpsGen3_ucChipIdx).ucPhysicalAddr;

        // Common operations have been moved to a separate function for clarity and reuse
        CddTpsGen3_PrepareTxFrameForSingleCmd(psTxCbData, pTabEntry, ucChipAddress, CDDTPSGEN3_Para_CHIP_IDX(CddTpsGen3_ucChipIdx));
      }
      else
      {
        // If not connected, set transmit/receive to dummy data.
        CddTpsGen3_UseDummyTxRx(psTxCbData);
      }
      break;

    case eSingleSLOWCmd:
      if (CddTpsGen3_ucChipIdx_MuxCmd < CDDTPSGEN3_Para_COUNT_CONNECTED_DEV)
      {
        ucChipAddress = CDDTPSGEN3_Para_CHIP_ADDR(CddTpsGen3_ucChipIdx_MuxCmd).ucPhysicalAddr;

        // Common operations have been moved to a separate function for clarity and reuse
        CddTpsGen3_PrepareTxFrameForSingleCmd(psTxCbData, pTabEntry, ucChipAddress, CDDTPSGEN3_Para_CHIP_IDX(CddTpsGen3_ucChipIdx_MuxCmd));
      }
      else
      {
        // If not connected, set transmit/receive to dummy data.
        CddTpsGen3_UseDummyTxRx(psTxCbData);
      }
      break;
    default:
      CddTpsGen3_UseDummyTxRx(psTxCbData);
      break;
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen3_PrepareTxFrameForSingleCmd
///
/// \descr  This function prepares the command Frame according to current entry 
///         from the scheduler table
///
/// \param  psTxCbData
/// \param  pTabEntry
/// \param  ucChipAddress
/// \param  ucChipIdx
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CddTpsGen3_PrepareTxFrameForSingleCmd(tsCddUart_MessageEntryType* psTxCbData,
                                                     const tsCddTpsGen3_UartSchedTable* pTabEntry,
                                                     uint8 ucChipAddress, uint8 ucChipIdx)
{
  CddTpsGen3_BuildTxFrame(pTabEntry, ucChipAddress, ucChipIdx, psTxCbData);
  psTxCbData->ucRxDataLength  = pTabEntry->ucRxSize;
  psTxCbData->pucRxData       = pTabEntry->pucRx + (pTabEntry->ucRxSize * ucChipIdx);
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen3_UseDummyTxRx
///
/// \descr  This function prepares dummy data to be sent on UART in case of
///         invalid command
///
/// \param  psTxCbData
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CddTpsGen3_UseDummyTxRx(tsCddUart_MessageEntryType* psTxCbData)
{
  psTxCbData->pucTxData       = &CddTpsGen3_aucZero[0];
  psTxCbData->pucRxData       = &CddTpsGen3_ucDummy[0];
  psTxCbData->ucTxDataLength  = 0u;
  psTxCbData->ucRxDataLength  = 0u;
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen3_UartRx
///
/// \descr  This function reads the content of the UART Rx data provided by the 
///         UART and stores the data in the CddTpsGen3_DataMirror.
///         The function is called after reception of a UART frame.
///
/// \param  *pucData      : address of DataMirror for Rx Data (filled by low layer UART and DO NOT REMOVE)
/// \param  boRxStatus    : UART Rx Data completion status
///
/// \return void
//-----------------------------------------------------------------------------
void  CddTpsGen3_UartRx(const uint8* pucRxData, boolean boRxStatus)
{
  boolean boSchTableRestart = FALSE;
  uint8 ucRxData = *pucRxData;//only for qac
  //calculate pointer to actual scheduler table
  const tsCddTpsGen3_UartSchedTable* pTabEntry = &CddTpsGen3_asUartSchedTable[CddTpsGen3_ucSchedIx];
  const uint8 ucSchedulerSize = sizeof(CddTpsGen3_asUartSchedTable) / sizeof(CddTpsGen3_asUartSchedTable[0]);

  //check for communication status
  CddTpsGen3_SetComStatus(boRxStatus, pTabEntry->eDynCmd);
  //check for CRC status on Rx data
  CddTpsGen3_SetCrcStatus(pTabEntry);

  //eBroadcastCmd and eSingleSLOWCmd shall increment the CddTpsGen2_ucSchedIx by 1 always
  //eSingleFASTCmd shall increment the CddTpsGen2_ucSchedIx after a complete present chips have been executed

  /* for Single SLOW CMD, commands are multiplexed for one chip per cycle */
  if (CddTpsGen3_ucSchedIx >= (ucSchedulerSize - 1u))
  {
    /* increment chip index once per CYCLE */
    //CddTpsGen2_ucChipIdx_MuxCmd++;
    //CddTpsGen2_ucChipIdx_MuxCmd %= CDDTPSGEN2_Para_COUNT_CONNECTED_DEV;
    if (CddTpsGen3_ucChipIdx_MuxCmd < (CDDTPSGEN3_Para_COUNT_CONNECTED_DEV - 1u))
    {
      CddTpsGen3_ucChipIdx_MuxCmd += 1u;
    }
    else
    {
      CddTpsGen3_ucChipIdx_MuxCmd = 0u;
      CddTpsGen3_boMuxCmdCompleted = TRUE;
    }
  }

  if (pTabEntry->eDynCmd == eSingleFASTCmd)
  {
    //go to next chip
    CddTpsGen3_ucChipIdx++;
  }

  if ((CddTpsGen3_ucChipIdx > (CDDTPSGEN3_Para_COUNT_CONNECTED_DEV - 1u)) || (pTabEntry->eDynCmd == eBroadcastCmd) || (pTabEntry->eDynCmd == eSingleSLOWCmd))
  {
    // last chip was reached, reset chip index 
    CddTpsGen3_ucChipIdx = 0u;
    //handle the scheduler table
    CddTpsGen3_SchHandle(pTabEntry);
  }
  //in case of invalid commands is something to be done? theoretically the communication should be in timeout
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen3_SchHandle
///
/// \descr  This function handles the actions defined in the scheduler table
///         and updates the index to the scheduler to prepare the next TX cmd
///
/// \param  pTabEntry
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CddTpsGen3_SchHandle(const tsCddTpsGen3_UartSchedTable* pTabEntry)
{
  //set index to next scheduler table entry
  sint32 slSchedIx = (sint32)CddTpsGen3_ucSchedIx + pTabEntry->scNextEntry;

  //update actual index
  CddTpsGen3_ucSchedIx = (CddTpsGen3_ResetScheduler() != FALSE) ? 0u : (uint8)slSchedIx;

  //calculate pointer to actual scheduler table entry (read next Tx entry to check action)
  pTabEntry = &CddTpsGen3_asUartSchedTable[CddTpsGen3_ucSchedIx];

  //check for action
  if (pTabEntry->ucAction != CDDTPSGEN3_ST_NO_ACT)
  {
    const boolean boSchTableRestart = CddTpsGen3_StAction(pTabEntry->ucAction);
    //check for restart
    if (boSchTableRestart != FALSE)
    {
      //matrix not initialized, communication error, restart 
      CddTpsGen3_ucSchedIx = 0u;
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen3_StAction
///
/// \descr  This function handles the actions defined in the scheduler table
///
/// \param  ucAction
///
/// \return STATIC_AL boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean CddTpsGen3_StAction(const uint8 ucAction)
{
  boolean boRestart = FALSE;
  boolean boChipStatus = FALSE;
  uint8   ucChipIdx = 0u;
  uint8   ucPWM_CLK = CDDTPSGEN3_CFG_PWMTICK_8MHz;
  uint8   ucCMWTAP = CDDTPSGEN3_CFG_CMWTAP_8MHz;
  const tsCddTpsGen3_UartSchedTable* pTabEntry = &CddTpsGen3_asUartSchedTable[CddTpsGen3_ucSchedIx];

  switch (ucAction)
  {
  case CDDTPSGEN3_ST_NO_ACT:
    break;
  case CDDTPSGEN3_ST_ACT_CHECK_START:
    CddTpsGen3_boMuxCmdCompleted = FALSE; //reset mux cmd completion status
    /*
        Power Up Delay, before sending any command to MLCs
    */
    if ((CddMlc_IsMlcPowered() == FALSE) || (CDDTPSGEN3_Para_IS_CODING_VALID == FALSE)) //vccx not ok or coding not available yet
    {
      boRestart = TRUE;
    }
    break;

  case CDDTPSGEN3_ST_ACT_CHECK_PWR:
    //If PWR bit of STATUS Register is not set
    if ((uint8)CDDTPSGEN3_PWR != (CddTpsGen3_DataMirror.StatRx.RxSTATUS[CDDTPSGEN3_Para_CHIP_IDX(CddTpsGen3_ucChipIdx_MuxCmd)].ucRxByte[0] & (uint8)CDDTPSGEN3_PWR))
    {
      // Mark the PowerCycle flag to current Mlc chip        
      CDDTPSGEN3_SET_BIT_U8(CddTpsGen3_ucPowerOnReset_Bit, CDDTPSGEN3_Para_CHIP_IDX(CddTpsGen3_ucChipIdx_MuxCmd));
    }
    else
    {
      // Reset the PowerCycle flag from current Mlc chip
      CDDTPSGEN3_CLR_BIT_U8(CddTpsGen3_ucPowerOnReset_Bit, CDDTPSGEN3_Para_CHIP_IDX(CddTpsGen3_ucChipIdx_MuxCmd));
    }

    if (CddTpsGen3_ucPowerOnReset_Bit != 0u)
    {
      boRestart = TRUE;
    }
    break;

  case CDDTPSGEN3_ST_ACT_CFG_CHIP:
    for (ucChipIdx = 0u; ucChipIdx < CDDTPSGEN3_Para_COUNT_CONNECTED_DEV; ucChipIdx++)
    {
     if (CDDTPSGEN3_Para_CHIP_ADDR(ucChipIdx).boIsMasterId != FALSE) //this is the master device
     {
       CddTpsGen3_DataMirror.CtrlTx.RegOUTCTRL[CDDTPSGEN3_Para_CHIP_IDX(ucChipIdx)].Bit.biSYNCOEN = 1u;
       CddTpsGen3_DataMirror.CtrlTx.RegOUTCTRL[CDDTPSGEN3_Para_CHIP_IDX(ucChipIdx)].Bit.biSYNCPEN = 1u;
     }
     else
     {
       CddTpsGen3_DataMirror.CtrlTx.RegOUTCTRL[CDDTPSGEN3_Para_CHIP_IDX(ucChipIdx)].Bit.biSYNCOEN = 0u;
       CddTpsGen3_DataMirror.CtrlTx.RegOUTCTRL[CDDTPSGEN3_Para_CHIP_IDX(ucChipIdx)].Bit.biSYNCPEN = 0u;
     }
    }
    break;

  case CDDTPSGEN3_ST_ACT_SET_PHASE:
    for (ucChipIdx = 0u; ucChipIdx < CDDTPSGEN3_Para_COUNT_CONNECTED_DEV; ucChipIdx++)
    {
      // 1. Ensure LOW Bytes are written first
      CddTpsGen3_SetPHASEReg_LSB(CDDTPSGEN3_Para_CHIP_IDX(ucChipIdx), &CddTpsGen3_aunPhaseShifts_TPS9266x[CDDTPSGEN3_Para_CHIP_IDX(ucChipIdx)][0]);
      // 2. Update HIGH bytes 
      CddTpsGen3_SetPHASEReg_MSB(CDDTPSGEN3_Para_CHIP_IDX(ucChipIdx), &CddTpsGen3_aunPhaseShifts_TPS9266x[CDDTPSGEN3_Para_CHIP_IDX(ucChipIdx)][0]);
    }
    break;

  case CDDTPSGEN3_ST_ACT_CFG_LEDS:
    for (ucChipIdx = 0u; ucChipIdx < CDDTPSGEN3_Para_COUNT_CONNECTED_DEV; ucChipIdx++)
    {
      // {SLEWRATE, OVLMT, PARLED}
      CddTpsGen3_SetCFGLEDSReg(CDDTPSGEN3_Para_CHIP_IDX(ucChipIdx), &CddTpsGen3_aucDefaultWidths_TPS9266x[CDDTPSGEN3_Para_CHIP_IDX(ucChipIdx)][0]);
    }
    break;
  case CDDTPSGEN3_ST_ACT_START_CYCLE:
    CddTpsGen3_boInitCompleted = TRUE;
    break;
  case CDDTPSGEN3_ST_ACT_CHECK_RESTART:
    CddTpsGen3_boInitCompleted = FALSE;
    break;
  case CDDTPSGEN3_ST_ACT_SYSCFG:
    switch (CDDTPSGEN3_Para_BAUDRATE)
    {
    case CDDTPSGEN3_BAUDRATE_1Mbps:
      ucPWM_CLK = CDDTPSGEN3_CFG_PWMTICK_16MHz;
      ucCMWTAP = CDDTPSGEN3_CFG_CMWTAP_16MHz;
      break;
    case CDDTPSGEN3_BAUDRATE_500Kbps:
    default:
      ucPWM_CLK = CDDTPSGEN3_CFG_PWMTICK_8MHz;
      ucCMWTAP = CDDTPSGEN3_CFG_CMWTAP_8MHz;
      break;
    }

    for (ucChipIdx = 0u; ucChipIdx < CDDTPSGEN3_Para_COUNT_CONNECTED_DEV; ucChipIdx++)
    {
      CddTpsGen3_DataMirror.CtrlTx.RegSYSCFG[CDDTPSGEN3_Para_CHIP_IDX(ucChipIdx)].sSysReg.RegSYSCFG.Bit.biACKEN = CDDTPSGEN3_ENABLE_BIT;
      CddTpsGen3_DataMirror.CtrlTx.RegSYSCFG[CDDTPSGEN3_Para_CHIP_IDX(ucChipIdx)].sSysReg.RegSYSCFG.Bit.biCHPMP_SS = CDDTPSGEN3_ENABLE_BIT;
      CddTpsGen3_DataMirror.CtrlTx.RegSYSCFG[CDDTPSGEN3_Para_CHIP_IDX(ucChipIdx)].sSysReg.RegSYSCFG.Bit.biCMWEN = CDDTPSGEN3_ENABLE_BIT;
      CddTpsGen3_DataMirror.CtrlTx.RegSYSCFG[CDDTPSGEN3_Para_CHIP_IDX(ucChipIdx)].sSysReg.RegCMWTAP.Bit.biCMWTAP = ucCMWTAP;
      CddTpsGen3_DataMirror.CtrlTx.RegSYSCFG[CDDTPSGEN3_Para_CHIP_IDX(ucChipIdx)].sSysReg.RegPWMTICK.Bit.biPTCNT = ucPWM_CLK;
      CddTpsGen3_DataMirror.CtrlTx.RegSYSCFG[CDDTPSGEN3_Para_CHIP_IDX(ucChipIdx)].sSysReg.RegPWMTICK.Bit.biPTBASE = 0u; //DIV1 = 1;
    }
    break;
  default:
    break;
  }

  return boRestart;
}// PRQA S 5316 // STCYC exceeded due to program architecture and readability

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen3_Calc16BitCRCValue
///
/// \descr This function calculates CRC16 following CRC16-IBM polynomial 0xA001
///        This function Calculates CRC16 using a Lookup Table.
///
/// \param  pucData   : Buffer which contains the bytes over which CRC16 is performed
/// \param  ucLength  : Number of bytes from pucData used for CRC16 calculation
///
/// \return STATIC_AL uint16 : CRC value computed
///
//-----------------------------------------------------------------------------
STATIC_AL uint16 CddTpsGen3_Calc16BitCRCValue(uint8* pucData, uint8 ucLength)
{
  // Use LookUpTable for 0xA001 Polynom 16 bit CRC IBM Computation
  static const uint16 CRC16_IBM_Lookup_Table[256u] = {
    0x0000u, 0xc0c1u, 0xc181u, 0x0140u, 0xc301u, 0x03c0u, 0x0280u, 0xc241u,
    0xc601u, 0x06c0u, 0x0780u, 0xc741u, 0x0500u, 0xc5c1u, 0xc481u, 0x0440u,
    0xcc01u, 0x0cc0u, 0x0d80u, 0xcd41u, 0x0f00u, 0xcfc1u, 0xce81u, 0x0e40u,
    0x0a00u, 0xcac1u, 0xcb81u, 0x0b40u, 0xc901u, 0x09c0u, 0x0880u, 0xc841u,
    0xd801u, 0x18c0u, 0x1980u, 0xd941u, 0x1b00u, 0xdbc1u, 0xda81u, 0x1a40u,
    0x1e00u, 0xdec1u, 0xdf81u, 0x1f40u, 0xdd01u, 0x1dc0u, 0x1c80u, 0xdc41u,
    0x1400u, 0xd4c1u, 0xd581u, 0x1540u, 0xd701u, 0x17c0u, 0x1680u, 0xd641u,
    0xd201u, 0x12c0u, 0x1380u, 0xd341u, 0x1100u, 0xd1c1u, 0xd081u, 0x1040u,
    0xf001u, 0x30c0u, 0x3180u, 0xf141u, 0x3300u, 0xf3c1u, 0xf281u, 0x3240u,
    0x3600u, 0xf6c1u, 0xf781u, 0x3740u, 0xf501u, 0x35c0u, 0x3480u, 0xf441u,
    0x3c00u, 0xfcc1u, 0xfd81u, 0x3d40u, 0xff01u, 0x3fc0u, 0x3e80u, 0xfe41u,
    0xfa01u, 0x3ac0u, 0x3b80u, 0xfb41u, 0x3900u, 0xf9c1u, 0xf881u, 0x3840u,
    0x2800u, 0xe8c1u, 0xe981u, 0x2940u, 0xeb01u, 0x2bc0u, 0x2a80u, 0xea41u,
    0xee01u, 0x2ec0u, 0x2f80u, 0xef41u, 0x2d00u, 0xedc1u, 0xec81u, 0x2c40u,
    0xe401u, 0x24c0u, 0x2580u, 0xe541u, 0x2700u, 0xe7c1u, 0xe681u, 0x2640u,
    0x2200u, 0xe2c1u, 0xe381u, 0x2340u, 0xe101u, 0x21c0u, 0x2080u, 0xe041u,
    0xa001u, 0x60c0u, 0x6180u, 0xa141u, 0x6300u, 0xa3c1u, 0xa281u, 0x6240u,
    0x6600u, 0xa6c1u, 0xa781u, 0x6740u, 0xa501u, 0x65c0u, 0x6480u, 0xa441u,
    0x6c00u, 0xacc1u, 0xad81u, 0x6d40u, 0xaf01u, 0x6fc0u, 0x6e80u, 0xae41u,
    0xaa01u, 0x6ac0u, 0x6b80u, 0xab41u, 0x6900u, 0xa9c1u, 0xa881u, 0x6840u,
    0x7800u, 0xb8c1u, 0xb981u, 0x7940u, 0xbb01u, 0x7bc0u, 0x7a80u, 0xba41u,
    0xbe01u, 0x7ec0u, 0x7f80u, 0xbf41u, 0x7d00u, 0xbdc1u, 0xbc81u, 0x7c40u,
    0xb401u, 0x74c0u, 0x7580u, 0xb541u, 0x7700u, 0xb7c1u, 0xb681u, 0x7640u,
    0x7200u, 0xb2c1u, 0xb381u, 0x7340u, 0xb101u, 0x71c0u, 0x7080u, 0xb041u,
    0x5000u, 0x90c1u, 0x9181u, 0x5140u, 0x9301u, 0x53c0u, 0x5280u, 0x9241u,
    0x9601u, 0x56c0u, 0x5780u, 0x9741u, 0x5500u, 0x95c1u, 0x9481u, 0x5440u,
    0x9c01u, 0x5cc0u, 0x5d80u, 0x9d41u, 0x5f00u, 0x9fc1u, 0x9e81u, 0x5e40u,
    0x5a00u, 0x9ac1u, 0x9b81u, 0x5b40u, 0x9901u, 0x59c0u, 0x5880u, 0x9841u,
    0x8801u, 0x48c0u, 0x4980u, 0x8941u, 0x4b00u, 0x8bc1u, 0x8a81u, 0x4a40u,
    0x4e00u, 0x8ec1u, 0x8f81u, 0x4f40u, 0x8d01u, 0x4dc0u, 0x4c80u, 0x8c41u,
    0x4400u, 0x84c1u, 0x8581u, 0x4540u, 0x8701u, 0x47c0u, 0x4680u, 0x8641u,
    0x8201u, 0x42c0u, 0x4380u, 0x8341u, 0x4100u, 0x81c1u, 0x8081u, 0x4040u
  };

  uint16 un16CrcValue = 0u; // initial value for CRC

  /* Start calculate CRC value by using a table */
  for (uint8 ucByteIdx = 0u; ucByteIdx < ucLength; ucByteIdx++)
  {
    // Fastest execution time using CRC16 LookUpTable
    un16CrcValue = CRC16_IBM_Lookup_Table[(uint8)(un16CrcValue ^ (*pucData++))] ^ (un16CrcValue >> 8u);
  }

  return un16CrcValue;
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen3_SetComStatus
///
/// \descr  this function set/clear the bit communication status for each connected chip
///
/// \param  boRxStat
/// \param  eCmdType
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CddTpsGen3_SetComStatus(boolean boRxStat, teGen3_DynCmdType eCmdType)
{
  if (eCmdType == eSingleFASTCmd)
  {
    if (CddTpsGen3_ucChipIdx < CDDTPSGEN3_Para_COUNT_CONNECTED_DEV)
    {
      //represent communication error
      CddTpsGen3_aboComStatus[CDDTPSGEN3_Para_CHIP_IDX(CddTpsGen3_ucChipIdx)] = (boRxStat == FALSE) ? TRUE : FALSE;
    }
  }
  else if (eCmdType == eSingleSLOWCmd)
  {
    if (CddTpsGen3_ucChipIdx_MuxCmd < CDDTPSGEN3_Para_COUNT_CONNECTED_DEV)
    {
      //represent communication error
      CddTpsGen3_aboComStatus[CDDTPSGEN3_Para_CHIP_IDX(CddTpsGen3_ucChipIdx_MuxCmd)] = (boRxStat == FALSE) ? TRUE : FALSE;
    }
  }
  else
  {
    //in Broadcast or invalid command, don't set anything (NO- Response from chips)
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen3_SetWIDTHReg_MSB
///
/// \descr  Set the 10-bit WIDTH registers to control the pulse width of the LEDs.
///         This function fills the 8bit WIDTH MSB's .  
///
/// \param  ucChipIdx
/// \param  punDuty
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CddTpsGen3_SetWIDTHReg_MSB(const uint8 ucChipIdx, const uint16* punDuty)
{
  uint8* pucWIDTH_MSB;
  
  pucWIDTH_MSB  = &CddTpsGen3_DataMirror.CtrlTx.RegWIDTH_MSB[ucChipIdx].ucByte[0];

  for (uint8 ucIdx = 0u; ucIdx < CDDTPSGEN3_N_16_BYTES; ucIdx++)
  {
    *(pucWIDTH_MSB++) = (uint8)(*(punDuty++) >> 2u);                            // Fill HIGH sides [9:2] of the WIDTH01H...WIDTH16H registers
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen3_SetWIDTHReg_LSB
///
/// \descr  Set the 10-bit WIDTH registers to control the pulse width of the LEDs.
///         This function fills the 2-bit WIDTH LSB's .  
///
/// \param  ucChipIdx
/// \param  punDuty
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CddTpsGen3_SetWIDTHReg_LSB(const uint8 ucChipIdx, const uint16* punDuty)
{
  uint8* pucWIDTH_LSB;

  pucWIDTH_LSB  = &CddTpsGen3_DataMirror.CtrlTx.RegWIDTH_LSB[ucChipIdx].ucByte[0];

  // Compute 16 times each segment mapped on 4 registers 
  for (uint8 ucIdx = 0u; ucIdx < 4u; ucIdx++)
  {
    // Extract bits [1:0] and shift left to fill [1:0] | [3:2]  |[5:4] | [7:6]
    //PRQA S 400 1  // intended behavior
    //*(pucWIDTH_LSB++) = (uint8)((*(punDuty++) & 0x0003u) << 0u) | (uint8)((*(punDuty++) & 0x0003u) << 2u) |
    //                    (uint8)((*(punDuty++) & 0x0003u) << 4u) | (uint8)((*(punDuty++) & 0x0003u) << 6u);                      // Fill LOW sides [1:0] of the WIDTH04_01L, WIDTH08_05L, WIDTH12_09L, WIDTH16_13L registers
  
    *(pucWIDTH_LSB)  = (uint8)((*(punDuty++) & 0x0003u) << 0u);
    *(pucWIDTH_LSB) |= (uint8)((*(punDuty++) & 0x0003u) << 2u);
    *(pucWIDTH_LSB) |= (uint8)((*(punDuty++) & 0x0003u) << 4u);
    *(pucWIDTH_LSB) |= (uint8)((*(punDuty++) & 0x0003u) << 6u);
    pucWIDTH_LSB++;
  }
}


//-----------------------------------------------------------------------------
/// \brief  CddTpsGen3_SetWIDTHReg
///
/// \descr  Set the 10-bit WIDTH registers to control the pulse width of the LEDs.
///
/// \param  ucChipIdx
/// \param  punDuty
///
/// \return void
//-----------------------------------------------------------------------------
void CddTpsGen3_SetWIDTHReg(const uint8 ucChipIdx, const uint16* punDuty)
{
  // 1. Ensure LOW Bytes are written first
  CddTpsGen3_SetWIDTHReg_LSB(ucChipIdx, punDuty);

  // 2. Update HIGH bytes 
  CddTpsGen3_SetWIDTHReg_MSB(ucChipIdx, punDuty);
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen3_SetPHASEReg_MSB
///
/// \descr  Set the 10-bit PHASE registers to control the phase shift of the LEDs
///
/// \param  ucChipIdx
/// \param  punPhase
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CddTpsGen3_SetPHASEReg_MSB(const uint8_fast ucChipIdx, const uint16* punPhase)
{
  uint8* pucPHASE_MSB = &CddTpsGen3_DataMirror.CtrlTx.RegPHASE_MSB[ucChipIdx].ucByte[0];

  for (uint8 ucIdx = 0u; ucIdx < CDDTPSGEN3_N_16_BYTES; ucIdx++)
  {
    *(pucPHASE_MSB++) = (uint8)(*(punPhase++) >> 2u);                      // Fill HIGH sides [9:2] of the PHASE01H...PHASE16H registers
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen3_SetPHASEReg_LSB
///
/// \descr  Set the 10-bit WIDPHASETH registers to control the pulse width of the LEDs.
///         This function fills the 2-bit PHASE LSB's .  
///
/// \param  ucChipIdx
/// \param  punPhase
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CddTpsGen3_SetPHASEReg_LSB(const uint8_fast ucChipIdx, const uint16* punPhase)
{
  uint8* pucPHASE_LSB = &CddTpsGen3_DataMirror.CtrlTx.RegPHASE_LSB[ucChipIdx].ucByte[0];

  // Compute 16 times each segment mapped on 4 registers 
  for (uint8 ucIdx = 0u; ucIdx < 4u; ucIdx++)
  {

    // Extract bits [1:0] and shift left to fill [1:0] | [3:2]  |[5:4] | [7:6]
    //PRQA S 400 1  // intended behavior
    //*(pucPHASE_LSB++) = (uint8)((*(punPhase++) & 0x0003u) << 0u) | (uint8)((*(punPhase++) & 0x0003u) << 2u) |
    //                    (uint8)((*(punPhase++) & 0x0003u) << 4u) | (uint8)((*(punPhase++) & 0x0003u) << 6u);                  // Fill LOW sides [1:0] of the PHASE04_01L, PHASE08_05L, PHASE12_09L, PHASE16_13L registers
  
    *(pucPHASE_LSB)  = (uint8)((*(punPhase++) & 0x0003u) << 0u);
    *(pucPHASE_LSB) |= (uint8)((*(punPhase++) & 0x0003u) << 2u);
    *(pucPHASE_LSB) |= (uint8)((*(punPhase++) & 0x0003u) << 4u);
    *(pucPHASE_LSB) |= (uint8)((*(punPhase++) & 0x0003u) << 6u);
    pucPHASE_LSB++;
  }
}


//-----------------------------------------------------------------------------
/// \brief  CddTpsGen3_SetCFGLEDSReg
///
/// \descr  The function computes the LED Strings Configuration Commands for each Mlc Chip
///         This is suitable only for a 16-bytes write Command !
///
/// \param  ucChipIdx
/// \param  pucDefWidth
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CddTpsGen3_SetCFGLEDSReg(const uint8_fast ucChipIdx, const uint8* pucDefWidth)
{
  uint8* pucLEDsReg;
 
  // fill SLEWRATE reg
  pucLEDsReg      = &CddTpsGen3_DataMirror.CtrlTx.RegSLEWRATE[ucChipIdx].ucByte[0];
  *(pucLEDsReg++) = CddTpsGen3_aucConfigSlewrate_LSB[ucChipIdx];
  *(pucLEDsReg++) = CddTpsGen3_aucConfigSlewrate_MSB[ucChipIdx];

  // fill Default Pulse Width reg
  uint8* pucDEF_WIDTH;
  pucDEF_WIDTH = &CddTpsGen3_DataMirror.CtrlTx.RegDEFWIDTH[ucChipIdx].ucByte[0];
  
  for (uint8 ucIdx = 0u; ucIdx < CDDTPSGEN3_N_16_BYTES; ucIdx++)
  {
    *(pucDEF_WIDTH + ucIdx ) = (uint8)(*(pucDefWidth + ucIdx));                    // Fill DEFWIDTH01...DEFWIDTH16 registers
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen3_GetADCReg
///
/// \descr  This function returns the actual adc results data from Data Mirror
///         for the requested device
///
/// \param  ucChipIdx
/// \param  puADCReg
///
/// \return void
//-----------------------------------------------------------------------------
void CddTpsGen3_GetADCReg(const uint8_fast ucChipIdx, tuCddTpsGen3_RxADC* puADCReg)
{
  if ((ucChipIdx < CDDTPSGEN3_MAX_CHIPs) && (puADCReg != NULL_PTR))
  {
    *puADCReg = CddTpsGen3_DataMirror.StatRx.RxADC[ucChipIdx];
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen3_GetELEFAULTReg
///
/// \descr  This function returns the actual pixel fault data from Data Mirror
///         for the requested device
///
/// \param  ucChipIdx
/// \param  puELEFAULTReg
///
/// \return void
//-----------------------------------------------------------------------------
void CddTpsGen3_GetELEFAULTReg(const uint8_fast ucChipIdx, tuCddTpsGen3_RxELEFAULT* puELEFAULTReg)
{
  if ((ucChipIdx < CDDTPSGEN3_MAX_CHIPs) && (puELEFAULTReg != NULL_PTR))
  {
    *puELEFAULTReg = CddTpsGen3_DataMirror.StatRx.RxELEFAULT[ucChipIdx];
  }
}

//-----------------------------------------------------------------------------
/// \brief CddTpsGen3_GetComFAULT
///
/// \descr This function returns the device communication error status for
///        the requested device
///
/// \param  pboComFault
///
/// \return void
//-----------------------------------------------------------------------------
boolean CddTpsGen3_GetComFAULT(const uint8_fast ucChipIdx)
{
  return CddTpsGen3_aboComStatus[ucChipIdx];
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen3_GetPWRStatus
///
/// \descr  This function returns the power on reset status for the requested device
///
/// \param  -
///
/// \return uint8
//-----------------------------------------------------------------------------
uint8 CddTpsGen3_GetPWRStatus(void)
{
  return CddTpsGen3_ucPowerOnReset_Bit;
}

//-----------------------------------------------------------------------------
/// \brief CddTpsGen3_GetMuxCmdCompleted
///
/// \descr this function will indicate with TRUE the completion of multiplexed commands 
///             from the scheduler 
///
/// \param  -
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CddTpsGen3_GetMuxCmdCompleted(void)
{
  return CddTpsGen3_boMuxCmdCompleted;
}

//-----------------------------------------------------------------------------
/// \brief CddTpsGen3GetInitCmdCompleted
///
/// \descr this function will indicate with TRUE the completion of initialization commands 
///             from the scheduler 
///
/// \param  -
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CddTpsGen3_GetInitCmdCompleted(void)
{
  return CddTpsGen3_boInitCompleted;
}

//---------------------------------------------------------------------------- -
/// \brief CddTpsGen3_CheckCRC
///
/// \descr Calculate and Check CRC for a given data frame
///
/// \param  *ucPtrData
/// \param  ucLength
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean CddTpsGen3_CheckCRC(uint8 *ucPtrData, uint8 ucLength)
{
  boolean boCrcError = FALSE;
  uint16 unCrc = 0xFFFFu;
  uint16 unComputedCrc = 0u;
  //calculate actual CRC
  unComputedCrc = CddTpsGen3_Calc16BitCRCValue(ucPtrData, (ucLength - CDDTPSGEN3_N_CRC_BYTES));
  //recontruct the CRC received
  unCrc = ucPtrData[ucLength - CDDTPSGEN3_N_CRC_BYTES];
  unCrc |= (uint16)((uint16)ucPtrData[ucLength - CDDTPSGEN3_N_CRC_BYTES + 1u] << 8u);
  //compare CRCs
  boCrcError = (unComputedCrc != unCrc) ? TRUE : FALSE;
  //return the status
  return boCrcError;
}

//---------------------------------------------------------------------------- -
/// \brief CddTpsGen3_CheckReadCommand
///
/// \descr This function check if current command is any type of read command
///        This is needed for CRC checking that is only done on Data comming from
///        the device itself
///
/// \param  ucSchCmd
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean CddTpsGen3_CheckReadCommand(const uint8 ucSchCmd)
{
  boolean boRet = FALSE;
  switch (ucSchCmd)
  {
    case CDDTPSGEN3_READ_01_BYTES:
    case CDDTPSGEN3_READ_02_BYTES:
    case CDDTPSGEN3_READ_03_BYTES:
    case CDDTPSGEN3_READ_04_BYTES:
    case CDDTPSGEN3_READ_12_BYTES:
    case CDDTPSGEN3_READ_16_BYTES:
    case CDDTPSGEN3_READ_32_BYTES:
      boRet = TRUE;
      break;
    default:
      break;
  }

  return boRet;
}

//---------------------------------------------------------------------------- -
/// \brief CddTpsGen3_SetCrcStatus
///
/// \descr This function sets the Crc occurence on the affected chip
///
/// \param  *pTabEntry
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddTpsGen3_SetCrcStatus(const tsCddTpsGen3_UartSchedTable *pTabEntry)
{
  const boolean boCmdRead = CddTpsGen3_CheckReadCommand(pTabEntry->ucCmd);
  if ((pTabEntry->eDynCmd != eBroadcastCmd) && (boCmdRead != FALSE))
  {
    const uint8 ucDynChip = (pTabEntry->eDynCmd == eSingleFASTCmd) ? CDDTPSGEN3_Para_CHIP_IDX(CddTpsGen3_ucChipIdx) : CDDTPSGEN3_Para_CHIP_IDX(CddTpsGen3_ucChipIdx_MuxCmd);
    // Check CRC only if the communication is OK
    if (CddTpsGen3_aboComStatus[ucDynChip] == FALSE)
    {
      CddTpsGen3_aboCrcStatus[ucDynChip] = CddTpsGen3_CheckCRC(pTabEntry->pucRx + (pTabEntry->ucRxSize * ucDynChip), pTabEntry->ucRxSize);
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief CddTpsGen3_GetCrcFAULT
///
/// \descr This function returns the device crc error status for
///        the requested device
///
/// \param  ucChipIdx
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CddTpsGen3_GetCrcFAULT(const uint8_fast ucChipIdx)
{
  return CddTpsGen3_aboCrcStatus[ucChipIdx];
}

//-----------------------------------------------------------------------------
// End declaration or definitions of functions
//-----------------------------------------------------------------------------

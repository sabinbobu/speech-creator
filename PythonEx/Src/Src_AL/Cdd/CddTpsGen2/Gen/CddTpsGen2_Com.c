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
/// \file  CddTpsGen2_Com.c
///
/// \brief
///
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
//standard includes
#include <AL_Helper.h>

//module API include path
#include <CddTpsGen2.h>
#include <CddTpsGen2_Cb.h>
#include <CddTpsGen2_Cod.h>

#include <Dio.h>
//module includes relative to API
#include <CddTpsGen2_Cfg.h>
#include <CddTpsGen2_Com.h>
#include <CddTpsGen2_Types.h>
#include <CddTpsGen2_Sched.h>

//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------

#define CDDTPSGEN2_SET_BIT_U8(var, bitPos) ((var) |= (uint8)((uint8)1u << (uint8)(bitPos)))
#define CDDTPSGEN2_CLR_BIT_U8(var, bitPos) ((var) &= (uint8)(~(uint8)((uint8)1u << (uint8)(bitPos))))
#define CDDTPSGEN2_SET_CLR_CONDITION_U8(cnd, var, bitPos) ((cnd) == FALSE) ? (uint8)CDDTPSGEN2_SET_BIT_U8((var), (bitPos)) : (uint8)CDDTPSGEN2_CLR_BIT_U8((var), (bitPos))

#define CDDTPSGEN2_ENABLE_BIT           1u
#define CDDTPSGEN2_DISABLE_BIT          0u


/* ---------------------------------------------*/
/*           Data Mirror Defines                */
/* ---------------------------------------------*/

#if (CFG_MAX_NO_OF_MLC == 1)
  #define CDDTPSGEN2_INIT(x) { x }
#elif (CFG_MAX_NO_OF_MLC == 7)
  #define CDDTPSGEN2_INIT(x) { x, x, x, x, x, x, x }
#elif (CFG_MAX_NO_OF_MLC == 8)
  #define CDDTPSGEN2_INIT(x) { x, x, x, x, x, x, x, x }
#endif /* (CDDTPSGEN2_Cfg_NbOfDevices = maximum nb of TPS92662A allowed on the bus) */

#if (CFG_MAX_NO_OF_MLC > 0U)
  #define CDDTPSGEN2_INIT_ADCID_MAP 0x00u
#elif (CFG_MAX_NO_OF_MLC > 8U)
  #define CDDTPSGEN2_INIT_ADCID_MAP 0x01u
#elif (CFG_MAX_NO_OF_MLC > 16U)
  #define CDDTPSGEN2_INIT_ADCID_MAP 0x02u
#elif (CFG_MAX_NO_OF_MLC > 31U)
  #error "The TPS9266x GEN2 chip supports up to 31 devices on the bus"
#endif


#define CDDTPSGEN2_REG_3BYTES_INIT(x)    { x, x, x }
#define CDDTPSGEN2_REG_4BYTES_INIT(x)    { x, x, x, x }
#define CDDTPSGEN2_REG_5BYTES_INIT(x)    { x, x, x, x, x }
#define CDDTPSGEN2_REG_6BYTES_INIT(x)    { x, x, x, x, x, x }
#define CDDTPSGEN2_REG_8BYTES_INIT(x)    { x, x, x, x, x, x, x, x }
#define CDDTPSGEN2_REG_9BYTES_INIT(x)    { x, x, x, x, x, x, x, x, x }
#define CDDTPSGEN2_REG_10BYTES_INIT(x)   { x, x, x, x, x, x, x, x, x, x }
#define CDDTPSGEN2_REG_16BYTES_INIT(x)   { x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x }
#define CDDTPSGEN2_REG_18BYTES_INIT(x)   { x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x }
#define CDDTPSGEN2_REG_22BYTES_INIT(x)   { x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x }
#define CDDTPSGEN2_REG_34BYTES_INIT(x)   { x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x }


         #define CDDTPSGEN2_InitZeroReg                0x00u

/*  1 */ #define CDDTPSGEN2_TxRegMPHASE_Init        { .ucByte = CDDTPSGEN2_REG_16BYTES_INIT(CDDTPSGEN2_InitZeroReg)              }
/*  2 */ #define CDDTPSGEN2_TxRegMWIDTH_Init        { .ucByte = CDDTPSGEN2_DEFAULT_STRING                                        }
/*  3 */ #define CDDTPSGEN2_TxRegSTRINGS_Init       { .ucByte = { CDDTPSGEN2_SET_SLEWRATE_REG((uint8)SLOW_RATE), CDDTPSGEN2_SET_OVLMT_REG((uint8)VTH_O3_DEFAULT)  ,(uint8)CDDTPSGEN2_PARLED_NONE  } }

/*  4 */ #define CDDTPSGEN2_TxRegSYSCFG_DEFAULTVAL_Init        {  .Bit =  {  .biPWR      = CDDTPSGEN2_DISABLE_BIT,                   \
                                                                             .biSYNCPEN  = CDDTPSGEN2_DISABLE_BIT,                   \
                                                                             .biSYNCOEN  = CDDTPSGEN2_DISABLE_BIT,                   \
                                                                             .biCMWEN    = CDDTPSGEN2_DISABLE_BIT,                   \
                                                                             .biPSON     = CDDTPSGEN2_DISABLE_BIT,                   \
                                                                             .biACKEN    = CDDTPSGEN2_ENABLE_BIT,                    \
                                                                             .biI2CEN    = CDDTPSGEN2_DISABLE_BIT,                   \
                                                                             .biSEPTR    = CDDTPSGEN2_DISABLE_BIT            }  }


/*  5 */ #define CDDTPSGEN2_TxRegSYSCFG_Init        { .sSysReg = { .RegSYSCFG  = { .Bit =  {  .biPWR      = CDDTPSGEN2_ENABLE_BIT,                            \
                                                                                              .biSYNCPEN  = CDDTPSGEN2_DISABLE_BIT,                           \
                                                                                              .biSYNCOEN  = CDDTPSGEN2_DISABLE_BIT,                           \
                                                                                              .biCMWEN    = CDDTPSGEN2_ENABLE_BIT,                            \
                                                                                              .biPSON     = CDDTPSGEN2_DISABLE_BIT,                           \
                                                                                              .biACKEN    = CDDTPSGEN2_ENABLE_BIT,                            \
                                                                                              .biI2CEN    = CDDTPSGEN2_DISABLE_BIT,                           \
                                                                                              .biSEPTR    = CDDTPSGEN2_DISABLE_BIT                    }  },   \
                                                                   .RegCMWTAP  = { .Bit =  {  .biCMWTAP   = CDDTPSGEN2_CFG_CMWTAP_8MHz                }  },   \
                                                                   .RegPWMTICK = { .Bit =  {  .biPTCNT    = CDDTPSGEN2_CFG_PWMTICK_8MHz               }  }  } \
                                                    }

/*  6 */ #define CDDTPSGEN2_TxRegADCID_Init         { .ucRaw  =  CDDTPSGEN2_INIT_ADCID_MAP                            }
/*  7 */ #define CDDTPSGEN2_TxRegSOFTSYNC_Init      { .Bit    = { .biSSYNC = CDDTPSGEN2_ENABLE_BIT }                  }
/*  8 */ #define CDDTPSGEN2_TxRegI2CCfgReg          { .ucByte = CDDTPSGEN2_REG_6BYTES_INIT(CDDTPSGEN2_InitZeroReg)    }
/*  9 */ #define CDDTPSGEN2_TxRegELECFAULT_Init     { .ucByte = {CDDTPSGEN2_InitZeroReg, CDDTPSGEN2_InitZeroReg, CDDTPSGEN2_InitZeroReg } }
              

/*  1 */ #define CDDTPSGEN2_RxCmdICID_Init          { .ucRxByte = CDDTPSGEN2_REG_3BYTES_INIT(CDDTPSGEN2_InitZeroReg)      }
/*  2 */ #define CDDTPSGEN2_RxCmdSYSCFG_Init        { CDDTPSGEN2_InitZeroReg      }
/*  3 */ #define CDDTPSGEN2_RxCmdPHASES_Init        { CDDTPSGEN2_InitZeroReg      }
/*  4 */ #define CDDTPSGEN2_RxCmdCFGLEDS_Init       { CDDTPSGEN2_InitZeroReg      }
/*  5 */ #define CDDTPSGEN2_RxCmdPWMS_Init          { CDDTPSGEN2_InitZeroReg      }
/*  6 */ #define CDDTPSGEN2_RxCmdELEFAULT_Init      { .ucRxByte = CDDTPSGEN2_REG_5BYTES_INIT(CDDTPSGEN2_InitZeroReg)     }
/*  7 */ #define CDDTPSGEN2_RxCmdCLR_ELEFAULT_Init  { CDDTPSGEN2_InitZeroReg      }
/*  8 */ #define CDDTPSGEN2_RxCmdADC_Init           { .ucRxByte = CDDTPSGEN2_REG_4BYTES_INIT(CDDTPSGEN2_InitZeroReg)      }
/*  9 */ #define CDDTPSGEN2_RxCmdCONFIG1_Init       { .ucRxByte = CDDTPSGEN2_REG_18BYTES_INIT(CDDTPSGEN2_InitZeroReg)     }
/*  9 */ #define CDDTPSGEN2_RxCmdCONFIG2_Init       { .ucRxByte = CDDTPSGEN2_REG_18BYTES_INIT(CDDTPSGEN2_InitZeroReg)     }

/*  1 */ #define CDDTPSGEN2_TxI2CSEQCFG_EEInit      { .ucByte = CDDTPSGEN2_REG_4BYTES_INIT(CDDTPSGEN2_InitZeroReg)        }
/*  2 */ #define CDDTPSGEN2_TxRx_EEInit             { CDDTPSGEN2_InitZeroReg }

/* Initialization values of Data Mirror of GEN2 family registers */
#define CDDTPSGEN2_DataMirror_InitZero                                        \
{                                                                             \
  { /* CtrlTx */                                                              \
    /*  1 */  CDDTPSGEN2_INIT(CDDTPSGEN2_TxRegMPHASE_Init),                   \
    /*  2 */  CDDTPSGEN2_INIT(CDDTPSGEN2_TxRegMWIDTH_Init),                   \
    /*  3 */  CDDTPSGEN2_INIT(CDDTPSGEN2_TxRegSTRINGS_Init),                  \
    /*  4 */  CDDTPSGEN2_INIT(CDDTPSGEN2_TxRegSYSCFG_DEFAULTVAL_Init),        \
    /*  5 */  CDDTPSGEN2_INIT(CDDTPSGEN2_TxRegSYSCFG_Init),                   \
    /*  6 */  CDDTPSGEN2_INIT(CDDTPSGEN2_TxRegADCID_Init),                    \
    /*  7 */  CDDTPSGEN2_INIT(CDDTPSGEN2_TxRegSOFTSYNC_Init),                 \
    /*  8 */  CDDTPSGEN2_INIT(CDDTPSGEN2_TxRegELECFAULT_Init)                 \
  },                                                                          \
  { /* StatRx */                                                              \
    /* 1 */   CDDTPSGEN2_INIT(CDDTPSGEN2_RxCmdICID_Init),                     \
    /* 2 */   CDDTPSGEN2_INIT(CDDTPSGEN2_RxCmdSYSCFG_Init),                   \
    /* 3 */   CDDTPSGEN2_INIT(CDDTPSGEN2_RxCmdPHASES_Init),                   \
    /* 4 */   CDDTPSGEN2_INIT(CDDTPSGEN2_RxCmdCFGLEDS_Init),                  \
    /* 5 */   CDDTPSGEN2_INIT(CDDTPSGEN2_RxCmdPWMS_Init),                     \
    /* 6 */   CDDTPSGEN2_INIT(CDDTPSGEN2_RxCmdELEFAULT_Init),                 \
    /* 7 */   CDDTPSGEN2_INIT(CDDTPSGEN2_RxCmdCLR_ELEFAULT_Init),             \
    /* 8 */   CDDTPSGEN2_INIT(CDDTPSGEN2_RxCmdADC_Init),                      \
    /* 9 */   CDDTPSGEN2_INIT(CDDTPSGEN2_RxCmdCONFIG1_Init),                  \
    /* 9 */   CDDTPSGEN2_INIT(CDDTPSGEN2_RxCmdCONFIG2_Init)                   \
  }                                                                           \
}

/* 1 */  #define CDDTPSGEN2_MPHASE_Tx           &CddTpsGen2_DataMirror.CtrlTx.RegMPHASE[0].ucByte[0]
/* 2 */  #define CDDTPSGEN2_MWIDTH_Tx           &CddTpsGen2_DataMirror.CtrlTx.RegMWIDTH[0].ucByte[0]
/* 3 */  #define CDDTPSGEN2_STRINGS_Tx          &CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[0].ucByte[0] 
/* 4 */  #define CDDTPSGEN2_SYSCFG_DEFAULT_Tx   &CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG_DEFAULT[0].ucRaw
/* 5 */  #define CDDTPSGEN2_SYSCFG_Tx           &CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[0].ucByte[0]
/* 6 */  #define CDDTPSGEN2_ADCID_Tx            &CddTpsGen2_DataMirror.CtrlTx.RegADCID[0].ucRaw
/* 7 */  #define CDDTPSGEN2_SOFTSYNC_Tx         &CddTpsGen2_DataMirror.CtrlTx.RegSOFTSYNC[0].ucRaw
/* 8 */  #define CDDTPSGEN2_I2CCFG_Tx           &CddTpsGen2_DataMirror.CtrlTx.RegI2CCfg[0].ucByte[0]
/* 9 */  #define CDDTPSGEN2_ELECFAULTS_Tx       &CddTpsGen2_DataMirror.CtrlTx.RegELEFAULT[0].ucByte[0]


/* 1 */  #define CDDTPSGEN2_ICID_Rx             &CddTpsGen2_DataMirror.StatRx.RxICID[0].ucRxByte[0]
/* 2 */  #define CDDTPSGEN2_SYSCFG_Rx           &CddTpsGen2_DataMirror.StatRx.RxSYSCFG[0].ucRxByte[0]
/* 3 */  #define CDDTPSGEN2_PHASES_Rx           &CddTpsGen2_DataMirror.StatRx.RxPHASES[0].ucRxByte[0]
/* 4 */  #define CDDTPSGEN2_CFGLEDS_Rx          &CddTpsGen2_DataMirror.StatRx.RxCFGLEDS[0].ucRxByte[0]
/* 5 */  #define CDDTPSGEN2_PWMS_Rx             &CddTpsGen2_DataMirror.StatRx.RxPWMS[0].ucRxByte[0]
/* 6 */  #define CDDTPSGEN2_ELEFAULT_Rx         &CddTpsGen2_DataMirror.StatRx.RxELEFAULT[0].ucRxByte[0]
/* 7 */  #define CDDTPSGEN2_CLR_ELEFAULT_Rx     &CddTpsGen2_DataMirror.StatRx.RxCLR_ELEFAULT[0].ucRxByte[0]
/* 8 */  #define CDDTPSGEN2_ADC_Rx              &CddTpsGen2_DataMirror.StatRx.RxADC[0].ucRxByte[0]
/* 9 */  #define CDDTPSGEN2_CONFIG1_Rx           &CddTpsGen2_DataMirror.StatRx.RxCONFIG1[0].ucRxByte[0]
/* 9 */  #define CDDTPSGEN2_CONFIG2_Rx           &CddTpsGen2_DataMirror.StatRx.RxCONFIG2[0].ucRxByte[0]

/* 1 */  #define CDDTPSGEN2_I2CTICK_EETx        &CddTpsGen2_DataMirrorEE.CtrlTx.TxI2CTICK.ucRaw
/* 2 */  #define CDDTPSGEN2_I2C_STARTCMD_EETx   &CddTpsGen2_DataMirrorEE.CtrlTx.TxsI2CSEQCFG.ucByte[0]
/* 3 */  #define CDDTPSGEN2_I2C_DATA_EETx       &CddTpsGen2_DataMirrorEE.CtrlTx.TxI2CDAT.ucRaw
/* 3 */  #define CDDTPSGEN2_I2C_SYSCFG_EETx     &CddTpsGen2_DataMirrorEE.CtrlTx.TxSYSCFGEE.ucRaw


/* 1 */  #define CDDTPSGEN2_ACK_EERx            &CddTpsGen2_DataMirrorEE.StatRx.RxACK
/* 2 */  #define CDDTPSGEN2_I2C_STAT_EERx       &CddTpsGen2_DataMirrorEE.StatRx.RxI2CSTAT.ucRxByte[0]
/* 3 */  #define CDDTPSGEN2_I2C_DATA_EERx       &CddTpsGen2_DataMirrorEE.StatRx.RxI2CDATA.ucRxByte[0]


/* ---------------------------------------------------------------*/
/*           Initialization of Broadcast Cmd Arrays               */
/* ---------------------------------------------------------------*/

#define CDDTPSGEN2_RxBrdADCID_Init      { .ucRxByte = CDDTPSGEN2_REG_3BYTES_INIT(CDDTPSGEN2_InitZeroReg) }
#define CDDTPSGEN2_RxBrdSYSCFG_Init     { .ucRxByte = CDDTPSGEN2_REG_3BYTES_INIT(CDDTPSGEN2_InitZeroReg) }

#define BroadcastData_Init        \
{                                 \
   CDDTPSGEN2_RxBrdADCID_Init,    \
   CDDTPSGEN2_RxBrdSYSCFG_Init    \
}

#define CDDTPSGEN2_BROADCAST1_ADCID_Rx   &CddTpsGen2_BroadcastData.RxBrADCID.ucRxByte[0]
#define CDDTPSGEN2_BROADCAST2_SYSCFG_Rx  &CddTpsGen2_BroadcastData.RxBrSYSCFG.ucRxByte[0]

#define CDDTPSGEN2_Zero_Tx       &CddTpsGen2_aucZero[0]
#define CDDTPSGEN2_Dummy_Rx      &CddTpsGen2_ucDummy[0]

#define CDDTPSGEN2_DataMirrorEEPROM_InitZero    \
{                                               \
  {  /* CtrlTx */                               \
      CDDTPSGEN2_TxRx_EEInit,                   \
      CDDTPSGEN2_TxI2CSEQCFG_EEInit,            \
      CDDTPSGEN2_TxRx_EEInit,                   \
      CDDTPSGEN2_TxRx_EEInit,                   \
  },                                            \
  {  /* StatRx */                               \
      CDDTPSGEN2_TxRx_EEInit,                   \
      CDDTPSGEN2_TxRx_EEInit,                   \
      CDDTPSGEN2_InitZeroReg,                   \
  }                                             \
}

//-----------------------------------------------------------------------------
// Local types
//-----------------------------------------------------------------------------
// UART schedule table entry datatype
typedef struct tsCddTpsGen2_UartSchedTable
{
  sint8 scNextEntry;                //offset to next scheduler table entry
  uint8 ucAction;                   // index of action function done after Rx
  teGen2_DynCmdType  eDynCmd;       // dynamic command type evaluation
  uint8 ucCmd;                      // read/write command to send
  uint8 ucRegAddr;                  // device register address
  uint8 *pucTx;                     // control register data for transmission
  uint8 ucTxSize;                   // size of Tx Buffer command data
  uint8 *pucRx;                     // status register data for reception
  uint8 ucRxSize;                   // size of Rx Buffer received data
} tsCddTpsGen2_UartSchedTable;


//-----------------------------------------------------------------------------
// Definitions of initialized variables
//-----------------------------------------------------------------------------
STATIC_AL uint8     CddTpsGen2_ucSchedIx         = 0u;  // pointer to scheduler table
STATIC_AL uint8     CddTpsGen2_ucSchedIxEE       = 0u;  // pointer to scheduler table
STATIC_AL uint8     CddTpsGen2_ucChipIdx         = 0u;  // index of current device
STATIC_AL uint8     CddTpsGen2_ucChipIdx_MuxCmd  = 0u;  // index of current device for mux commands
STATIC_AL uint8     CddTpsGen2_ucChipIdx_EE  = CDDTPSGEN2_ADDR_NOT_CONNECTED;  // index of current EEPROM device
STATIC_AL boolean   CddTpsGen2_aboComStatus[CFG_MAX_NO_OF_MLC];
STATIC_AL boolean   CddTpsGen2_aboCrcStatus[CFG_MAX_NO_OF_MLC];
STATIC_AL uint8     CddTpsGen2_ucPowerOnReset_Bit = 0u;
STATIC_AL boolean   CddTpsGen2_boMuxCmdCompleted = FALSE;
STATIC_AL boolean   CddTpsGen2_boInitCompleted = FALSE;

STATIC_AL CONST_AL uint16 CddTpsGen2_aunPhaseShifts_TPS92662A  [][CDDTPSGEN2_TPS92662A_MAX_SWITCHS_PER_DEVICE] = CDDTPSGEN2_PHASE_SHIFT_CFG;
STATIC_AL CONST_AL uint8  CddTpsGen2_aucDefaultWidths_TPS92662A[][CDDTPSGEN2_TPS92662A_MAX_SWITCHS_PER_DEVICE] = CDDTPSGEN2_DEFAULT_WIDTHS;
STATIC_AL CONST_AL uint8  CddTpsGen2_aucConfigSlewrate[] = CDDTPSGEN2_CFG_SLEWRATE;
STATIC_AL CONST_AL uint8  CddTpsGen2_aucConfigOVLimit [] = CDDTPSGEN2_CFG_OVLMT;
STATIC_AL CONST_AL uint8  CddTpsGen2_aucConfigParaLed [] = CDDTPSGEN2_CFG_PARLED;

//-----------------------------------------------------------------------------
// Definitions of initialized structures and unions or arrays variables
//-----------------------------------------------------------------------------
STATIC_AL tsCddTpsGen2_DataMirror   CddTpsGen2_DataMirror     = CDDTPSGEN2_DataMirror_InitZero;
STATIC_AL tsCddTpsGen2_DataMirrorEE CddTpsGen2_DataMirrorEE   = CDDTPSGEN2_DataMirrorEEPROM_InitZero;
STATIC_AL tsCddTpsGen2_BrCmd        CddTpsGen2_BroadcastData  = BroadcastData_Init;

STATIC_AL uint8  CddTpsGen2_ucDummy[CFG_MAX_NO_OF_MLC] = { 0u };  // for dummy receive Uart Frames
STATIC_AL uint8  CddTpsGen2_aucZero[CFG_MAX_NO_OF_MLC] = { 0u };  // for dummy transmit Uart Frames

STATIC_AL CONST_AL tsCddTpsGen2_UartSchedTable CddTpsGen2_asUartSchedTable[] = CDDTPSGEN2_Cfg_UartSchedTable_Init;
STATIC_AL CONST_AL tsCddTpsGen2_UartSchedTable CddTpsGen2_asUartSchedTableEE[] = CDDTPSGEN2_Cfg_UartSchedTableEE_Init;

//-----------------------------------------------------------------------------
// Definitions of non initialized variables
//-----------------------------------------------------------------------------
STATIC_AL uint8 CddTpsGen2_aucTxBuffer[CDDTPSGEN2_MAX_CMD_LENGTH];
//-----------------------------------------------------------------------------
// Definitions of non initialized structures and unions or arrays variables
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Function prototypes
//-----------------------------------------------------------------------------
STATIC_AL void    CddTpsGen2_SetComStatus(boolean boRxStat, teGen2_DynCmdType eCmdType);

STATIC_AL void    CddTpsGen2_BuildTxFrame(const tsCddTpsGen2_UartSchedTable* psEntryData, uint8 ucChipAddress, uint8 ucChipIdx, tsCddUart_MessageEntryType*  sTxCbData);
STATIC_AL void    CddTpsGen2_PrepareTxFrameForSingleCmd(tsCddUart_MessageEntryType* psTxCbData, const tsCddTpsGen2_UartSchedTable* pTabEntry, uint8 ucChipAddress, uint8 ucChipIdx);
STATIC_AL uint16  CddTpsGen2_Calc16BitCRCValue(uint8* pucData, uint8 ucLength);

STATIC_AL void    CddTpsGen2_SchHandle(const tsCddTpsGen2_UartSchedTable* pTabEntry);
STATIC_AL void    CddTpsGen2_SchHandleEE(const tsCddTpsGen2_UartSchedTable* pTabEntry);
STATIC_AL boolean CddTpsGen2_StAction (const uint8 ucAction);
STATIC_AL void    CddTpsGen2_StActionEE (const uint8 ucAction);
STATIC_AL void    CddTpsGen2_UseDummyTxRx(tsCddUart_MessageEntryType* psTxCbData);

STATIC_AL void    CddTpsGen2_SetPHASEReg  (const uint8_fast ucChipIdx, const uint16* punPhase);
STATIC_AL void    CddTpsGen2_SetCFGLEDSReg(const uint8_fast ucChipIdx, const uint8* pucDefWidth);

STATIC_AL boolean CddTpsGen2_CheckCRC(uint8 *ucPtrData, uint8 ucLength);
STATIC_AL boolean CddTpsGen2_CheckReadCommand(const uint8 ucSchCmd);
STATIC_AL void    CddTpsGen2_SetCrcStatus(const tsCddTpsGen2_UartSchedTable *pTabEntry);
//-----------------------------------------------------------------------------
// Function definitions
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_BuildTxFrame
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
STATIC_AL void CddTpsGen2_BuildTxFrame(const tsCddTpsGen2_UartSchedTable* psEntryData, uint8 ucChipAddress, uint8 ucChipIdx, tsCddUart_MessageEntryType*  sTxCbData)
{
  uint8 ucDataLenght = CDDTPSGEN2_SIZE_HEADERBYTES + psEntryData->ucTxSize;

  sTxCbData->ucTxDataLength = ucDataLenght + CDDTPSGEN2_SIZE_CRCBYTES;
  // Build the command header 
  ///             INIT BYTE                     |       DEVID         |           REGADDR
  ///    frame initialization (read/write cmd)    (device address)    (starting Register Address byte )
  CddTpsGen2_aucTxBuffer[0] = psEntryData->ucCmd;
  CddTpsGen2_aucTxBuffer[1] = ucChipAddress;
  CddTpsGen2_aucTxBuffer[2] = psEntryData->ucRegAddr;


  //add data into the command frame, after header bytes
  for (uint8 ucByteIdx = 0u; ucByteIdx < psEntryData->ucTxSize; ucByteIdx++)
  {
    CddTpsGen2_aucTxBuffer[CDDTPSGEN2_SIZE_HEADERBYTES + ucByteIdx] = (psEntryData->pucTx[(ucChipIdx * psEntryData->ucTxSize) + ucByteIdx]);
  }
  
  //calculate the CRC over the full command using look-up table ( CRC-16 IBM)
  uint16 un16CrcValue = CddTpsGen2_Calc16BitCRCValue(&CddTpsGen2_aucTxBuffer[0], ucDataLenght);
  
  // load the CRC into the final 2 bytes of the frame
  CddTpsGen2_aucTxBuffer[ucDataLenght]      = (uint8)(un16CrcValue & 0xFFu);   // LSByte of CRC
  CddTpsGen2_aucTxBuffer[ucDataLenght + 1u] = (uint8)(un16CrcValue >> 8u);     // MSByte of CRC

  sTxCbData->pucTxData = &CddTpsGen2_aucTxBuffer[0];
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_UartTx
///
/// \descr  The function reads the content of the CddTpsGen2_DataMirror and
///         adds the CRC bytes at the end of the command.
///         The function is called before the transmission of UART frame
///
/// \param  psTxCbData
///
/// \return void
//-----------------------------------------------------------------------------
void  CddTpsGen2_UartTx(tsCddUart_MessageEntryType *psTxCbData)
{
  uint8 ucChipAddress = CDDTPSGEN2_ADDR_NOT_CONNECTED;
  boolean boEEPromReq = CddTpsGen2_I2C_CheckEEActivation(&CddTpsGen2_ucSchedIxEE);
  const tsCddTpsGen2_UartSchedTable* pTabEntry = NULL_PTR;
  uint8 ucRxSize = 0u;

  //monitor the MLC power supply or coding availability at every new TX message in order to stop the UART communication until the power supply is comming back 
  if ((CddMlc_IsMlcPowered() == FALSE) || (CDDMLC_Para_IS_CODING_VALID == FALSE))
  {
    psTxCbData->pucTxData = NULL_PTR; //this null pointer will indicate that the UART communication must be empty 
    psTxCbData->ucTxDataLength = 0u; //0 tx data will indicate that the UART communication must be empty 
  }
  //normal behavior
  else
  {
    if ((boEEPromReq != FALSE) && (CddTpsGen2_ucChipIdx_EE != CDDTPSGEN2_ADDR_NOT_CONNECTED))
    {
      ucRxSize = CddTpsGen2_asUartSchedTableEE[CddTpsGen2_ucSchedIxEE].ucRxSize;
      //calculate pointer to actual scheduler table entry
      pTabEntry = &CddTpsGen2_asUartSchedTableEE[CddTpsGen2_ucSchedIxEE];
    }
    else
    {
      ucRxSize = CddTpsGen2_asUartSchedTable[CddTpsGen2_ucSchedIx].ucRxSize;
      //calculate pointer to actual scheduler table entry
      pTabEntry = &CddTpsGen2_asUartSchedTable[CddTpsGen2_ucSchedIx];
    }

    //prepare DMA with reception parameters
    psTxCbData->pucRxData = pTabEntry->pucRx;
    psTxCbData->ucRxDataLength = ucRxSize;

    // get UART command (read or write), register address and contents of control register for next UART frame
    switch (pTabEntry->eDynCmd)
    {
    case eBroadcastCmd:
      ucChipAddress = (uint8)CDDTPSGEN2_BROADCAST;
      CddTpsGen2_ucChipIdx = 0u;    // reset index for device because after each broadcast will come eSingleFASTCmd
      CddTpsGen2_BuildTxFrame(pTabEntry, ucChipAddress, CddTpsGen2_ucChipIdx, psTxCbData);

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

      if (CddTpsGen2_ucChipIdx < CDDTPSGEN2_Para_COUNT_CONNECTED_DEV)
      {
        ucChipAddress = CDDTPSGEN2_Para_CHIP_ADDR(CddTpsGen2_ucChipIdx).ucPhysicalAddr;

        // Common operations have been moved to a separate function for clarity and reuse
        CddTpsGen2_PrepareTxFrameForSingleCmd(psTxCbData, pTabEntry, ucChipAddress, CDDTPSGEN2_Para_CHIP_IDX(CddTpsGen2_ucChipIdx));
      }
      else
      {
        // If not connected, set transmit/receive to dummy data.
        CddTpsGen2_UseDummyTxRx(psTxCbData);
      }
      break;
    case eSingleSLOWCmd:
      if (CddTpsGen2_ucChipIdx_MuxCmd < CDDTPSGEN2_Para_COUNT_CONNECTED_DEV)
      {
        ucChipAddress = CDDTPSGEN2_Para_CHIP_ADDR(CddTpsGen2_ucChipIdx_MuxCmd).ucPhysicalAddr;

        // Common operations have been moved to a separate function for clarity and reuse
        CddTpsGen2_PrepareTxFrameForSingleCmd(psTxCbData, pTabEntry, ucChipAddress, CDDTPSGEN2_Para_CHIP_IDX(CddTpsGen2_ucChipIdx_MuxCmd));
      }
      else
      {
        // If not connected, set transmit/receive to dummy data.
        CddTpsGen2_UseDummyTxRx(psTxCbData);
      }
      break;
    case eEEPROMCmd:
      ucChipAddress = CDDTPSGEN2_Para_CHIP_ADDR(CddTpsGen2_ucChipIdx_EE).ucPhysicalAddr;
      // Common operations have been moved to a separate function for clarity and reuse
      CddTpsGen2_PrepareTxFrameForSingleCmd(psTxCbData, pTabEntry, ucChipAddress, 0u); //last parameter must be 0 because it support ONLY one eeprom device
      break;
    default:
      CddTpsGen2_UseDummyTxRx(psTxCbData);
      break;
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_PrepareTxFrameForSingleCmd
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
STATIC_AL void CddTpsGen2_PrepareTxFrameForSingleCmd(tsCddUart_MessageEntryType *psTxCbData,
                                                     const tsCddTpsGen2_UartSchedTable *pTabEntry,
                                                     uint8 ucChipAddress, uint8 ucChipIdx)
{
  CddTpsGen2_BuildTxFrame(pTabEntry, ucChipAddress, ucChipIdx, psTxCbData);
  psTxCbData->ucRxDataLength = pTabEntry->ucRxSize;
  psTxCbData->pucRxData = pTabEntry->pucRx + (pTabEntry->ucRxSize * ucChipIdx);
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_UseDummyTxRx
///
/// \descr  This function prepares dummy data to be sent on UART in case of
///         invalid command
///
/// \param  psTxCbData
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CddTpsGen2_UseDummyTxRx(tsCddUart_MessageEntryType *psTxCbData)
{
  psTxCbData->pucTxData       = &CddTpsGen2_aucZero[0];
  psTxCbData->pucRxData       = &CddTpsGen2_ucDummy[0];
  psTxCbData->ucTxDataLength = 0u;
  psTxCbData->ucRxDataLength = 0u;
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_UartRx
///
/// \descr  This function reads the content of the UART Rx data provided by the 
///         UART and store the data in the CddTpsGen2_DataMirror.
///         The function is called after reception of a UART frame.
///
/// \param  *pucRxData      : address of DataMirror for Rx Data (filled by low layer UART and DO NOT REMOVE)
/// \param  boRxStatus    : UART Rx Data completion status
///
/// \return void
//-----------------------------------------------------------------------------
void CddTpsGen2_UartRx(const uint8* pucRxData, boolean boRxStatus)
{
  uint8 ucRxData = *pucRxData;//only for qac
  boolean boEEPromReq = CddTpsGen2_I2C_CheckEEActivation(&CddTpsGen2_ucSchedIxEE);
  const tsCddTpsGen2_UartSchedTable* pTabEntry = NULL_PTR;

  if ((boEEPromReq != FALSE) && (CddTpsGen2_ucChipIdx_EE != CDDTPSGEN2_ADDR_NOT_CONNECTED))
  {
    //calculate pointer to actual scheduler table entry
    pTabEntry = &CddTpsGen2_asUartSchedTableEE[CddTpsGen2_ucSchedIxEE];
    //check for communication status
    CddTpsGen2_SetComStatus(boRxStatus, pTabEntry->eDynCmd);
    //check for CRC status on Rx data is not needed because DATA CRC is checked in application module
    //CddTpsGen2_SetCrcStatus(pTabEntry);
    //handle the scheduler table
    CddTpsGen2_SchHandleEE(pTabEntry);
  }
  else
  {
    //calculate pointer to actual scheduler table entry
    pTabEntry = &CddTpsGen2_asUartSchedTable[CddTpsGen2_ucSchedIx];
    //store scheduler size
    const uint8 ucSchedulerSize = sizeof(CddTpsGen2_asUartSchedTable) / sizeof(CddTpsGen2_asUartSchedTable[0]);

    //check for communication status
    CddTpsGen2_SetComStatus(boRxStatus, pTabEntry->eDynCmd);
    //check for CRC status on Rx data
    CddTpsGen2_SetCrcStatus(pTabEntry);

    //eBroadcastCmd and eSingleSLOWCmd shall increment the CddTpsGen2_ucSchedIx by 1 always
    //eSingleFASTCmd shall increment the CddTpsGen2_ucSchedIx after a complete present chips have been executed

    /* for Single SLOW CMD, commands are multiplexed for one chip per cycle */
    if (CddTpsGen2_ucSchedIx >= (ucSchedulerSize - 1u))
    {
      /* increment chip index once per CYCLE */
      //CddTpsGen2_ucChipIdx_MuxCmd++;
      //CddTpsGen2_ucChipIdx_MuxCmd %= CDDTPSGEN2_Para_COUNT_CONNECTED_DEV;
      if (CddTpsGen2_ucChipIdx_MuxCmd < (CDDTPSGEN2_Para_COUNT_CONNECTED_DEV - 1u))
      {
        CddTpsGen2_ucChipIdx_MuxCmd += 1u;
      }
      else
      {
        CddTpsGen2_ucChipIdx_MuxCmd = 0u;
        CddTpsGen2_boMuxCmdCompleted = TRUE;
      }
    }

    if (pTabEntry->eDynCmd == eSingleFASTCmd)
    {
      //go to next chip
      CddTpsGen2_ucChipIdx++;
    }

    if ((CddTpsGen2_ucChipIdx > (CDDTPSGEN2_Para_COUNT_CONNECTED_DEV - 1u)) || (pTabEntry->eDynCmd == eBroadcastCmd) || (pTabEntry->eDynCmd == eSingleSLOWCmd))
    {
      // last chip was reached, reset chip index 
      CddTpsGen2_ucChipIdx = 0u;
      //handle the scheduler table
      CddTpsGen2_SchHandle(pTabEntry);
    }
    //in case of invalid commands is something to be done? theoretically the communication should be in timeout
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_SchHandle
///
/// \descr  This function handles the actions defined in the scheduler table
///         and updates the index to the scheduler to prepare the next TX cmd
///
/// \param  pTabEntry
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CddTpsGen2_SchHandle(const tsCddTpsGen2_UartSchedTable* pTabEntry)
{
  //set index to next scheduler table entry
  sint32 slSchedIx = (sint32)CddTpsGen2_ucSchedIx + pTabEntry->scNextEntry;
  //update actual index
  CddTpsGen2_ucSchedIx = (CddTpsGen2_ResetScheduler() != FALSE) ? 0u : (uint8)slSchedIx;
  //calculate pointer to actual scheduler table entry (read next Tx entry to check action)
  pTabEntry = &CddTpsGen2_asUartSchedTable[CddTpsGen2_ucSchedIx];

  //check for action
  if (pTabEntry->ucAction != CDDTPSGEN2_ST_NO_ACT)
  {
    const boolean boSchTableRestart = CddTpsGen2_StAction(pTabEntry->ucAction);
    //check for restart
    if (boSchTableRestart != FALSE)
    {
      //matrix not initialized, communication error, restart 
      CddTpsGen2_ucSchedIx = 0u;
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_SchHandle
///
/// \descr  This function handles the actions defined in the scheduler table
///         and updates the index to the scheduler to prepare the next TX cmd
///
/// \param  pTabEntry
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CddTpsGen2_SchHandleEE(const tsCddTpsGen2_UartSchedTable* pTabEntry)
{
  //set index to next scheduler table entry
  sint32 slSchedIx = (sint32)pTabEntry->scNextEntry;
  //update actual index
  if (CddTpsGen2_ResetScheduler() != FALSE)
  {
    CddTpsGen2_ucSchedIx = 0u;
    CddTpsGen2_ucSchedIxEE = CDDTPSGEN2_STATE_EE_RESET;
  }
  //calculate pointer to actual scheduler table entry (read next Tx entry to check action)
  pTabEntry = &CddTpsGen2_asUartSchedTableEE[slSchedIx];

  //check for action
  if (pTabEntry->ucAction != CDDTPSGEN2_ST_NO_ACT)
  {
    CddTpsGen2_StActionEE(pTabEntry->ucAction);
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_StActionEE
///
/// \descr  This function handles the actions defined in the scheduler table
///         for EEPROM
///
/// \param  ucAction
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddTpsGen2_StActionEE(const uint8 ucAction)
{
  switch (ucAction)
  {
  case CDDTPSGEN2_ST_NO_ACT:
    break;
  case CDDTPSGEN2_ST_EE_CHECK_PREINIT:
    CddTpsGen2_I2C_HandlePreinit(CDDTPSGEN2_ACK_EERx);
    break;
  case CDDTPSGEN2_ST_EE_CHECK_INIT:
    CddTpsGen2_I2C_HandleInit(CDDTPSGEN2_ACK_EERx);
    break;
  case CDDTPSGEN2_ST_EE_READ_START:
    CddTpsGen2_I2C_HandleStart(CDDTPSGEN2_ACK_EERx);
    break;
  case CDDTPSGEN2_ST_EE_READ_STATUS:
    CddTpsGen2_I2C_HandleReadingStatus(CddTpsGen2_DataMirrorEE.StatRx.RxI2CSTAT.ucRxByte[0]);
    break;
  case CDDTPSGEN2_ST_EE_READ_DATA:
    CddTpsGen2_I2C_HandleReadData(CDDTPSGEN2_I2C_DATA_EERx);
    break;
  case CDDTPSGEN2_ST_EE_WRITE_START:
    CddTpsGen2_I2C_HandleStart(CDDTPSGEN2_ACK_EERx);
    break;
  case CDDTPSGEN2_ST_EE_WRITE_STATUS:
    CddTpsGen2_I2C_HandleWritingStatus(CddTpsGen2_DataMirrorEE.StatRx.RxI2CSTAT.ucRxByte[0]);
    break;
  case CDDTPSGEN2_ST_EE_WRITE_DATA:
    CddTpsGen2_I2C_HandleWriteData(CDDTPSGEN2_ACK_EERx);
    break;
  case CDDTPSGEN2_ST_EE_RESET:
    CddTpsGen2_I2C_HandleReset(NULL_PTR);
    break;
  default:
    break;
  }
}// PRQA S 5324 1 // STCAL = 8' exceeds threshold 7 for Number of Distinct Function Calls (STCAL)

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_StAction
///
/// \descr  This function handles the actions defined in the scheduler table
///
/// \param  ucAction
///
/// \return STATIC_AL boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean CddTpsGen2_StAction(const uint8 ucAction)
{
  boolean boRestart = FALSE;
  boolean boChipStatus = FALSE;
  uint8   ucChipIdx = 0u;
  uint8   ucI2CTICK = CDDTPSGEN2_CFG_I2CTICK_8MHz;
  uint8   ucPWM_CLK = CDDTPSGEN2_CFG_PWMTICK_8MHz;
  uint8   ucCMWTAP = CDDTPSGEN2_CFG_CMWTAP_8MHz;
  const tsCddTpsGen2_UartSchedTable* pTabEntry = &CddTpsGen2_asUartSchedTable[CddTpsGen2_ucSchedIx];

  switch (ucAction)
  {
  case CDDTPSGEN2_ST_NO_ACT:
    break;
  case CDDTPSGEN2_ST_ACT_CHECK_START:
    CddTpsGen2_boMuxCmdCompleted = FALSE; //reset mux cmd completion status
     /*
         Power Up Delay, before sending any command to MLCs
     */
     //if (CDDMLC_IS_DEVICE_POWERED() != FALSE)
     if ((CddMlc_IsMlcPowered() == FALSE) || (CDDMLC_Para_IS_CODING_VALID == FALSE)) //vccx not ok or coding not yet available
     {
       boRestart = TRUE;
     }
    break;
  case CDDTPSGEN2_ST_ACT_CHECK_PWR:
    //If PWR bit of SYSCFG Register is not set
    if ((uint8)CDDTPSGEN2_PWR != (CddTpsGen2_DataMirror.StatRx.RxCONFIG2[CDDTPSGEN2_Para_CHIP_IDX(CddTpsGen2_ucChipIdx_MuxCmd)].ucRxByte[0u] & (uint8)CDDTPSGEN2_PWR))
    {
      // Mark the PowerCycle flag to current Mlc chip        
      CDDTPSGEN2_SET_BIT_U8(CddTpsGen2_ucPowerOnReset_Bit, CDDTPSGEN2_Para_CHIP_IDX(CddTpsGen2_ucChipIdx_MuxCmd));
    }
    else
    {
      // Reset the PowerCycle flag from current Mlc chip
      CDDTPSGEN2_CLR_BIT_U8(CddTpsGen2_ucPowerOnReset_Bit, CDDTPSGEN2_Para_CHIP_IDX(CddTpsGen2_ucChipIdx_MuxCmd));
    }

    if (CddTpsGen2_ucPowerOnReset_Bit != 0u)
    {
      boRestart = TRUE;
    }
    break;
  case CDDTPSGEN2_ST_ACT_SYSCFG:
    switch (CDDTPSGEN2_Para_BAUDRATE)
    {
    case CDDTPSGEN2_BAUDRATE_1Mbps:
      ucI2CTICK = CDDTPSGEN2_CFG_I2CTICK_16MHz;
      ucPWM_CLK = CDDTPSGEN2_CFG_PWMTICK_16MHz;
      ucCMWTAP = CDDTPSGEN2_CFG_CMWTAP_16MHz;
      break;
    case CDDTPSGEN2_BAUDRATE_500Kbps:
    default:
      ucI2CTICK = CDDTPSGEN2_CFG_I2CTICK_8MHz;
      ucPWM_CLK = CDDTPSGEN2_CFG_PWMTICK_8MHz;
      ucCMWTAP = CDDTPSGEN2_CFG_CMWTAP_8MHz;
      break;
    }

    for (ucChipIdx = 0u; ucChipIdx < CDDTPSGEN2_Para_COUNT_CONNECTED_DEV; ucChipIdx++)
    {
      // Master Slave Topology configured as PWM Synchronization Type?    
#if (CDDTPSGEN2_SYNC_TYPE == CDDTPSGEN2_SYNC_HW_MASTER_SLAVE)

      if (CDDTPSGEN2_Para_CHIP_ADDR(ucChipIdx).boIsMasterId != FALSE)
      {
        CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[CDDTPSGEN2_Para_CHIP_IDX(ucChipIdx)].sSysReg.RegSYSCFG.Bit.biSYNCOEN = 1u;
        CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[CDDTPSGEN2_Para_CHIP_IDX(ucChipIdx)].sSysReg.RegSYSCFG.Bit.biSYNCPEN = 1u;
      }
      else
      {
        CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[CDDTPSGEN2_Para_CHIP_IDX(ucChipIdx)].sSysReg.RegSYSCFG.Bit.biSYNCOEN = 0u;
        CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[CDDTPSGEN2_Para_CHIP_IDX(ucChipIdx)].sSysReg.RegSYSCFG.Bit.biSYNCPEN = 0u;
      }

#endif
      // The Mlc I2C Communication enabled?
#if (CDDTPSGEN2_I2C_ENABLED == CDDTPSGEN2_FEATURE_ON) 

      if (CDDTPSGEN2_Para_CHIP_ADDR(ucChipIdx).ucPhysicalAddr == CDDTPSGEN2_Para_CHIP_EEPROM_ADDR)
      {
        CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[CDDTPSGEN2_Para_CHIP_IDX(ucChipIdx)].sSysReg.RegSYSCFG.Bit.biI2CEN = 1u;
        CddTpsGen2_DataMirrorEE.CtrlTx.TxI2CTICK.Bit.biI2CTICK = ucI2CTICK;
        CddTpsGen2_ucChipIdx_EE = ucChipIdx;
      }
      else
      {
        CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[CDDTPSGEN2_Para_CHIP_IDX(ucChipIdx)].sSysReg.RegSYSCFG.Bit.biI2CEN = 0u;
      }

#endif

      CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[CDDTPSGEN2_Para_CHIP_IDX(ucChipIdx)].sSysReg.RegCMWTAP.Bit.biCMWTAP = ucCMWTAP;
      CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[CDDTPSGEN2_Para_CHIP_IDX(ucChipIdx)].sSysReg.RegPWMTICK.Bit.biPTCNT = ucPWM_CLK;
      CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[CDDTPSGEN2_Para_CHIP_IDX(ucChipIdx)].sSysReg.RegPWMTICK.Bit.biPTBASE = 0u; //DIV1 = 1;
    }
    break;

  case CDDTPSGEN2_ST_ACT_SET_PHASE:
    for (ucChipIdx = 0u; ucChipIdx < CDDTPSGEN2_Para_COUNT_CONNECTED_DEV; ucChipIdx++)
    {
      CddTpsGen2_SetPHASEReg(CDDTPSGEN2_Para_CHIP_IDX(ucChipIdx), &CddTpsGen2_aunPhaseShifts_TPS92662A[CDDTPSGEN2_Para_CHIP_IDX(ucChipIdx)][0]);
    }
    break;

  case CDDTPSGEN2_ST_ACT_CFG_LEDS:
    for (ucChipIdx = 0u; ucChipIdx < CDDTPSGEN2_Para_COUNT_CONNECTED_DEV; ucChipIdx++)
    {
      // {SLEWRATE, OVLMT, PARLED}
      CddTpsGen2_SetCFGLEDSReg(CDDTPSGEN2_Para_CHIP_IDX(ucChipIdx), &CddTpsGen2_aucDefaultWidths_TPS92662A[CDDTPSGEN2_Para_CHIP_IDX(ucChipIdx)][0]);
    }
    break;
  case CDDTPSGEN2_ST_ACT_START_CYCLE:
    CddTpsGen2_boInitCompleted = TRUE;
    break;
  case CDDTPSGEN2_ST_ACT_CHECK_RESTART:
    CddTpsGen2_boInitCompleted = FALSE;
    break;
  default:
    break;
  }
  return boRestart;
}// PRQA S 5316 // STCYC exceeded due to program architecture and readability

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_Calc16BitCRCValue
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
STATIC_AL uint16 CddTpsGen2_Calc16BitCRCValue(uint8* pucData, uint8 ucLength)
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
/// \brief  CddTpsGen2_SetComStatus
///
/// \descr  this function set/clear the bit communication status for each connected chip
///
/// \param  boRxStat
/// \param  eCmdType
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CddTpsGen2_SetComStatus(boolean boRxStat, teGen2_DynCmdType eCmdType)
{
  if (eCmdType == eSingleFASTCmd)
  {
    if (CddTpsGen2_ucChipIdx < CDDTPSGEN2_Para_COUNT_CONNECTED_DEV)
    {
      //represent communication error
      CddTpsGen2_aboComStatus[CDDTPSGEN2_Para_CHIP_IDX(CddTpsGen2_ucChipIdx)] = (boRxStat == FALSE) ? TRUE : FALSE;
    }
  }
  else if (eCmdType == eSingleSLOWCmd)
  {
    if (CddTpsGen2_ucChipIdx_MuxCmd < CDDTPSGEN2_Para_COUNT_CONNECTED_DEV)
    {
      //represent communication error
      CddTpsGen2_aboComStatus[CDDTPSGEN2_Para_CHIP_IDX(CddTpsGen2_ucChipIdx_MuxCmd)] = (boRxStat == FALSE) ? TRUE : FALSE;
    }
  }
  else if (eCmdType == eEEPROMCmd)
  {
    //represent communication error
    CddTpsGen2_aboComStatus[CDDTPSGEN2_Para_CHIP_IDX(CddTpsGen2_ucChipIdx_EE)] = (boRxStat == FALSE) ? TRUE : FALSE;
  }
  else
  {
    //in Broadcast or invalid command, don't set anything (NO- Response from chips)
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_SetWIDTHReg
///
/// \descr  Set the 10-bit WIDTH registers to control the pulse width of the LEDs
///
/// \param  ucChipIdx
/// \param  punDuty
///
/// \return void
//-----------------------------------------------------------------------------
void CddTpsGen2_SetWIDTHReg(const uint8 ucChipIdx, const uint16* punDuty)
{
  uint8* pucWIDTHReg = &CddTpsGen2_DataMirror.CtrlTx.RegMWIDTH[ucChipIdx].ucByte[0];

  // Compute 4 times each 3 array of segments mapped on 4 registers (Separate 3 Low Sides - Mixed 1 High Side)
  for (uint8 ucIdx = 0u; ucIdx < 4u; ucIdx++)
  {
    *(pucWIDTHReg++) = (uint8)(*(punDuty + 0u));                // Fill LOW sides [7:0] of the MWIDTH01L, MWIDTH04L, MWIDTH07L, MWIDTH10L registers
    *(pucWIDTHReg++) = (uint8)(*(punDuty + 1u));                // Fill LOW sides [7:0] of the MWIDTH02L, MWIDTH05L, MWIDTH08L, MWIDTH11L registers
    *(pucWIDTHReg++) = (uint8)(*(punDuty + 2u));                // Fill LOW sides [7:0] of the MWIDTH03L, MWIDTH06L, MWIDTH09L, MWIDTH12L registers

    // Initialize and fill HIGH sides [9:8] of the MWIDTH03_01H, MWIDTH06_04H, MWIDTH09_07H, MWIDTH12_10H registers
    *pucWIDTHReg  = (uint8)((*(punDuty++) & 0x0300u) >> 8u);     // Extract bits [9:8] and shift right to [1:0]
    *pucWIDTHReg |= (uint8)((*(punDuty++) & 0x0300u) >> 6u);    // Extract bits [9:8] and shift right to [3:2]
    *pucWIDTHReg |= (uint8)((*(punDuty++) & 0x0300u) >> 4u);    // Extract bits [9:8] and shift right to [5:4]
    pucWIDTHReg++;
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_SetPHASEReg
///
/// \descr  Set the 10-bit PHASE registers to control the phase shift of the LEDs
///
/// \param  ucChipIdx
/// \param  punPhase
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CddTpsGen2_SetPHASEReg(const uint8_fast ucChipIdx, const uint16* punPhase)
{
  uint8* pucPHASEReg = &CddTpsGen2_DataMirror.CtrlTx.RegMPHASE[ucChipIdx].ucByte[0];

  // Compute 4 times each 3 array of segments mapped on 4 registers (Separate 3 Low Sides - Mixed 1 High Side)
  for (uint8_fast ucIdx = 0u; ucIdx < 4u; ucIdx++)
  {
    *(pucPHASEReg++) = (uint8)(*(punPhase + 0u));                  // Fill LOW sides [7:0] of the MPHASE01L, MPHASE04L, MPHASE07L, MPHASE10L registers
    *(pucPHASEReg++) = (uint8)(*(punPhase + 1u));                  // Fill LOW sides [7:0] of the MPHASE02L, MPHASE05L, MPHASE08L, MPHASE11L registers
    *(pucPHASEReg++) = (uint8)(*(punPhase + 2u));                  // Fill LOW sides [7:0] of the MPHASE03L, MPHASE06L, MPHASE09L, MPHASE12L registers

    // Initialize and fill HIGH sides [9:8] of the MPHASE03_01H, MPHASE06_04H, MPHASE09_07H, MPHASE12_10H registers
    *pucPHASEReg  = (uint8)((*(punPhase++) & 0x0300u) >> 8u);      // Extract bits [9:8] and shift right to [1:0]
    *pucPHASEReg |= (uint8)((*(punPhase++) & 0x0300u) >> 6u);      // Extract bits [9:8] and shift right to [3:2]
    *pucPHASEReg |= (uint8)((*(punPhase++) & 0x0300u) >> 4u);      // Extract bits [9:8] and shift right to [5:4]
    pucPHASEReg++;
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_SetCFGLEDSReg
///
/// \descr  The function computes the LED Strings Configuration Commands for each Mlc Chip
///         This is suitable only for a 12-bytes write Command !
///
/// \param  ucChipIdx
/// \param  pucDefWidth
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CddTpsGen2_SetCFGLEDSReg(const uint8_fast ucChipIdx, const uint8* pucDefWidth)
{
  uint8* pucLEDsReg;

  // fill SLEWRATE reg
  pucLEDsReg = &CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[ucChipIdx].sStringCfg.uRegSLEWRATE.ucRaw;
  *(pucLEDsReg++) = CddTpsGen2_aucConfigSlewrate[ucChipIdx];

  // fill Over Voltage Limit reg
  pucLEDsReg = &CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[ucChipIdx].sStringCfg.uRegOVLMT.ucRaw;
  *(pucLEDsReg++) = CddTpsGen2_aucConfigOVLimit[ucChipIdx];

  // fill Parallel LED String reg
  pucLEDsReg = &CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[ucChipIdx].sStringCfg.uRegPARLED.ucRaw;
  *(pucLEDsReg++) = CddTpsGen2_aucConfigParaLed[ucChipIdx];

  // fill Default Pulse Width reg
  pucLEDsReg = CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[ucChipIdx].sStringCfg.uRegDEFWIDTHS.ucByte;

  // {DEFWIDTH02_01, DEFWIDTH04_03, DEFWIDTH06_05, DEFWIDTH08_07, DEFWIDTH10_09, DEFWIDTH12_11}  
  *(pucLEDsReg++) = (uint8)((uint8)(*(pucDefWidth + 1u) << 4u)  | *pucDefWidth);
  *(pucLEDsReg++) = (uint8)((uint8)(*(pucDefWidth + 3u) << 4u)  | *(pucDefWidth + 2u));
  *(pucLEDsReg++) = (uint8)((uint8)(*(pucDefWidth + 5u) << 4u)  | *(pucDefWidth + 4u));
  *(pucLEDsReg++) = (uint8)((uint8)(*(pucDefWidth + 7u) << 4u)  | *(pucDefWidth + 6u));
  *(pucLEDsReg++) = (uint8)((uint8)(*(pucDefWidth + 9u) << 4u)  | *(pucDefWidth + 8u));
  *(pucLEDsReg++) = (uint8)((uint8)(*(pucDefWidth + 11u) << 4u) | *(pucDefWidth + 10u));

  // Fill the left bytes with constants - reserved area
  *(pucLEDsReg++) = 0x00u;  // Fill dummy byte on address 0x79
  *(pucLEDsReg++) = 0x00u;  // Fill dummy byte on address 0x7A
  *(pucLEDsReg)   = 0x00u;  // Fill dummy byte on address 0x7B
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_GetADCReg
///
/// \descr  This function returns the actual adc results data from Data Mirror
///         for the requested device
///
/// \param  ucChipIdx
/// \param  puADCReg
///
/// \return void
//-----------------------------------------------------------------------------
void CddTpsGen2_GetADCReg(const uint8_fast ucChipIdx, tuCddTpsGen2_RxADC* puADCReg)
{
  if ((ucChipIdx < CDDTPSGEN2_MAX_CHIPs) && (puADCReg != NULL_PTR))
  {
    *puADCReg = CddTpsGen2_DataMirror.StatRx.RxADC[ucChipIdx];
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_GetELEFAULTReg
///
/// \descr  This function returns the actual pixel fault data from Data Mirror
///         for the requested device
///
/// \param  ucChipIdx
/// \param  puELEFAULTReg
///
/// \return void
//-----------------------------------------------------------------------------
void CddTpsGen2_GetELEFAULTReg(const uint8_fast ucChipIdx, tuCddTpsGen2_RxELEFAULT* puELEFAULTReg)
{
  if ((ucChipIdx < CDDTPSGEN2_MAX_CHIPs) && (puELEFAULTReg != NULL_PTR))
  {
    *puELEFAULTReg = CddTpsGen2_DataMirror.StatRx.RxELEFAULT[ucChipIdx];
  }
}

//-----------------------------------------------------------------------------
/// \brief CddTpsGen2_GetComFAULT
///
/// \descr This function returns the device communication error status for
///        the requested device
///
/// \param  pboComFault
///
/// \return void
//-----------------------------------------------------------------------------
boolean CddTpsGen2_GetComFAULT(const uint8_fast ucChipIdx)
{
  return CddTpsGen2_aboComStatus[ucChipIdx];
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_GetPWRStatus
///
/// \descr  This function returns the power on reset status for the requested device
///
/// \param  -
///
/// \return uint8
//-----------------------------------------------------------------------------
uint8 CddTpsGen2_GetPWRStatus(void)
{
  return CddTpsGen2_ucPowerOnReset_Bit;
}

//-----------------------------------------------------------------------------
/// \brief CddTpsGen2_GetMuxCmdCompleted
///
/// \descr this function will indicate with TRUE the completion of multiplexed commands 
///             from the scheduler 
///
/// \param  -
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CddTpsGen2_GetMuxCmdCompleted(void)
{
  return CddTpsGen2_boMuxCmdCompleted;
}

//-----------------------------------------------------------------------------
/// \brief CddTpsGen2_GetInitCmdCompleted
///
/// \descr this function will indicate with TRUE the completion of initialization commands 
///             from the scheduler 
///
/// \param  -
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CddTpsGen2_GetInitCmdCompleted(void)
{
  return CddTpsGen2_boInitCompleted;
}

//-----------------------------------------------------------------------------
/// \brief CddTpsGen2_I2C_CmdReadStart
///
/// \descr
///
/// \param  -ucRemainedBytes, ucStartAddr
///
/// \return void
//-----------------------------------------------------------------------------
void CddTpsGen2_I2C_CmdReadStart(const uint8 ucRemainedBytes, const uint8 ucStartAddr)
{
  CddTpsGen2_DataMirrorEE.CtrlTx.TxsI2CSEQCFG.ucByte[0] = (uint8)((uint8)(CDDTPSGEN2_I2C_DEV_TYPE_ID << 4u) | ((uint8)CDDTPSGEN2_I2C_BLOCK_BITS_MASK & (ucStartAddr >> 7u)));//CDD_MLC_CFG_I2CSLA;
  CddTpsGen2_DataMirrorEE.CtrlTx.TxsI2CSEQCFG.ucByte[1] = ucRemainedBytes;         // Byte Length I2CLEN <=255 for current read suboperation
  CddTpsGen2_DataMirrorEE.CtrlTx.TxsI2CSEQCFG.ucByte[2] = ucStartAddr;             // Specify the low 8 bit address
  CddTpsGen2_DataMirrorEE.CtrlTx.TxsI2CSEQCFG.ucByte[3] = ((uint8)CDDTPSGEN2_I2CCTRL_START | (uint8)CDDTPSGEN2_I2CCTRL_RD);
}

//-----------------------------------------------------------------------------
/// \brief CddTpsGen2_I2C_CmdWriteStart
///
/// \descr
///
/// \param  ucStartAddr
///
/// \return void
//-----------------------------------------------------------------------------
void CddTpsGen2_I2C_CmdWriteStart(const uint8 ucStartAddr)
{
  CddTpsGen2_DataMirrorEE.CtrlTx.TxsI2CSEQCFG.ucByte[0] = (uint8)((uint8)(CDDTPSGEN2_I2C_DEV_TYPE_ID << 4u) | (CDDTPSGEN2_I2C_BLOCK_BITS_MASK & (ucStartAddr >> 7u)));//CDD_MLC_CFG_I2CSLA;
  CddTpsGen2_DataMirrorEE.CtrlTx.TxsI2CSEQCFG.ucByte[1] = 1u;                                     // Byte Length is ignored for write operation in I2CLEN register
  CddTpsGen2_DataMirrorEE.CtrlTx.TxsI2CSEQCFG.ucByte[2] = ucStartAddr;                            // Specify the low 8 bit address in I2CADR register
  CddTpsGen2_DataMirrorEE.CtrlTx.TxsI2CSEQCFG.ucByte[3] = CDDTPSGEN2_I2CCTRL_START;               // Set only CDD_MLC_I2CCTRL_START bit from I2CCTRL register
}

//-----------------------------------------------------------------------------
/// \brief CddTpsGen2_I2C_CmdWriteData
///
/// \descr
///
/// \param  *pucData
///
/// \return void
//-----------------------------------------------------------------------------
void CddTpsGen2_I2C_CmdWriteData(uint8 *pucData)
{
  CddTpsGen2_DataMirrorEE.CtrlTx.TxI2CDAT.ucRaw = *pucData;
}

//-----------------------------------------------------------------------------
/// \brief CddTpsGen2_I2C_CmdReset
///
/// \descr
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddTpsGen2_I2C_CmdReset(void)
{
  CddTpsGen2_DataMirrorEE.CtrlTx.TxsI2CSEQCFG.ucByte[0] = (uint8)(CDDTPSGEN2_I2C_DEV_TYPE_ID << 4u); // Set Slave address CDD_MLC_CFG_I2CSLA
  CddTpsGen2_DataMirrorEE.CtrlTx.TxsI2CSEQCFG.ucByte[1] = 0u;                                     // Block Address ignored for reset operation
  CddTpsGen2_DataMirrorEE.CtrlTx.TxsI2CSEQCFG.ucByte[2] = 0u;                                     // Byte Length ignored for reset operation
  CddTpsGen2_DataMirrorEE.CtrlTx.TxsI2CSEQCFG.ucByte[3] = CDDTPSGEN2_I2CCTRL_RST;
}

//-----------------------------------------------------------------------------
/// \brief CddTpsGen2_I2C_CmdReset
///
/// \descr
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddTpsGen2_I2C_CmdPreinit(void)
{
  CddTpsGen2_DataMirrorEE.CtrlTx.TxSYSCFGEE.Bit.biI2CEN = 1u; 
  CddTpsGen2_DataMirrorEE.CtrlTx.TxSYSCFGEE.Bit.biACKEN = 1u; 
  CddTpsGen2_DataMirrorEE.CtrlTx.TxSYSCFGEE.Bit.biPWR   = 1u;
  CddTpsGen2_DataMirrorEE.CtrlTx.TxSYSCFGEE.Bit.biCMWEN = 1u;
}

//---------------------------------------------------------------------------- -
/// \brief CddTpsGen2_CheckCRC
///
/// \descr Calculate and Check CRC for a given data frame
///
/// \param  *ucPtrData
/// \param  ucLength
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean CddTpsGen2_CheckCRC(uint8 *ucPtrData, uint8 ucLength)
{
  boolean boCrcError = FALSE;
  uint16 unCrc = 0xFFFFu;
  uint16 unComputedCrc = 0u;
  //calculate actual CRC
  unComputedCrc = CddTpsGen2_Calc16BitCRCValue(ucPtrData, (ucLength - CDDTPSGEN2_N_CRC_BYTES));
  //recontruct the CRC received
  unCrc = ucPtrData[ucLength - CDDTPSGEN2_N_CRC_BYTES];
  unCrc |= (uint16)((uint16)ucPtrData[ucLength - CDDTPSGEN2_N_CRC_BYTES + 1u] << 8u);
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
STATIC_AL boolean CddTpsGen2_CheckReadCommand(const uint8 ucSchCmd)
{
  boolean boRet = FALSE;
  switch (ucSchCmd)
  {
  case CDDTPSGEN2_READ_01_BYTES:
  case CDDTPSGEN2_READ_02_BYTES:
  case CDDTPSGEN2_READ_03_BYTES:
  case CDDTPSGEN2_READ_04_BYTES:
  case CDDTPSGEN2_READ_12_BYTES:
  case CDDTPSGEN2_READ_16_BYTES:
  case CDDTPSGEN2_READ_32_BYTES:
    boRet = TRUE;
    break;
  default:
    break;
  }

  return boRet;
}

//---------------------------------------------------------------------------- -
/// \brief CddTpsGen2_SetCrcStatus
///
/// \descr This function sets the Crc occurence on the affected chip
///
/// \param  *pTabEntry
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddTpsGen2_SetCrcStatus(const tsCddTpsGen2_UartSchedTable *pTabEntry)
{
  const boolean boReadCmd = CddTpsGen2_CheckReadCommand(pTabEntry->ucCmd);

  if ((pTabEntry->eDynCmd != eBroadcastCmd) && (boReadCmd != FALSE))
  {
    const uint8 ucDynChip = (pTabEntry->eDynCmd == eSingleFASTCmd) ? CDDTPSGEN2_Para_CHIP_IDX(CddTpsGen2_ucChipIdx) : CDDTPSGEN2_Para_CHIP_IDX(CddTpsGen2_ucChipIdx_MuxCmd);
    // Check CRC only if the communication is OK
    
    if(CddTpsGen2_aboComStatus[ucDynChip] == FALSE)
    {
      CddTpsGen2_aboCrcStatus[ucDynChip] = CddTpsGen2_CheckCRC(pTabEntry->pucRx + (pTabEntry->ucRxSize * ucDynChip), pTabEntry->ucRxSize);
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief CddTpsGen2_GetCrcFAULT
///
/// \descr This function returns the device crc error status for
///        the requested device
///
/// \param  ucChipIdx
///
/// \return void
//-----------------------------------------------------------------------------
boolean CddTpsGen2_GetCrcFAULT(const uint8_fast ucChipIdx)
{
  return CddTpsGen2_aboCrcStatus[ucChipIdx];
}
//-----------------------------------------------------------------------------
// End declaration or definitions of functions
//-----------------------------------------------------------------------------

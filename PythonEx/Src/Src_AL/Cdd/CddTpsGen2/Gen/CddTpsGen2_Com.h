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
/// \file  CddTpsGen2_Com.h
///
/// \brief
///
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef CDD_TPS_GEN2_COM_2024_01_30_H_
#define CDD_TPS_GEN2_COM_2024_01_30_H_

//=============================================================================
// Includes
//=============================================================================
#include <Std_Types.h>

#include <CddTpsGen2_Types.h>
#include <CddTpsGen2_Cfg.h>
#include <../../CddMlc/Cfg/CddMlc_Cfg.h>  //temporary

//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------
#define CFG_MAX_NO_OF_MLC                      7U  //temporary
//=============================================================================
// Mirror TPS92662A registers
//=============================================================================

typedef struct tsCddTpsGen2_RxBrADCID
{
  uint8 ucRxData[CDDTPSGEN2_N_01_BYTE];
  uint8 ucCrc[CDDTPSGEN2_N_CRC_BYTES];
}tsCddTpsGen2_RxBrADCID;

typedef struct tsCddTpsGen2_RxBrSYSCFG
{
  uint8 ucRxData[CDDTPSGEN2_N_01_BYTE];
  uint8 ucCrc[CDDTPSGEN2_N_CRC_BYTES];
}tsCddTpsGen2_RxBrSYSCFG;

typedef struct tsCddTpsGen2_RxICID
{
  uint8 ucRxData[CDDTPSGEN2_N_01_BYTE];
  uint8 ucCrc[CDDTPSGEN2_N_CRC_BYTES];
}tsCddTpsGen2_RxICID;

typedef struct tsCddTpsGen2_RxSYSCFG
{
  uint8 ucRxACK[CDDTPSGEN2_N_ACK];
}tsCddTpsGen2_RxSYSCFG;

typedef struct tsCddTpsGen2_RxPHASES
{
  uint8 ucRxACK[CDDTPSGEN2_N_ACK];
}tsCddTpsGen2_RxPHASES;

typedef struct tsCddTpsGen2_RxCFGLEDS
{
  uint8 ucRxACK[CDDTPSGEN2_N_ACK];
}tsCddTpsGen2_RxCFGLEDS;

typedef struct tsCddTpsGen2_RxPWMS
{
  uint8 ucRxACK[CDDTPSGEN2_N_ACK];
}tsCddTpsGen2_RxPWMS;

typedef struct tsCddTpsGen2_RxELEFAULT
{
  uint8 ucRxData[CDDTPSGEN2_N_03_BYTES];
  uint8 ucCrc[CDDTPSGEN2_N_CRC_BYTES];
}tsCddTpsGen2_RxELEFAULT;

typedef struct tsCddTpsGen2_RxCLR_ELEFAULT
{
  uint8 ucRxACK[CDDTPSGEN2_N_ACK];
}tsCddTpsGen2_RxCLR_ELEFAULT;

typedef struct tsCddTpsGen2_RxADC
{
  uint8 ucRxData[CDDTPSGEN2_N_02_BYTES];
  uint8 ucCrc[CDDTPSGEN2_N_CRC_BYTES];
}tsCddTpsGen2_RxADC;


typedef struct tsCddTpsGen2_RxCONFIG1
{
  uint8 ucRxData[CDDTPSGEN2_N_16_BYTES];
  uint8 ucCrc[CDDTPSGEN2_N_CRC_BYTES];
}tsCddTpsGen2_RxCONFIG1;

typedef struct tsCddTpsGen2_RxCONFIG2
{
  uint8 ucRxData[CDDTPSGEN2_N_16_BYTES];
  uint8 ucCrc[CDDTPSGEN2_N_CRC_BYTES];
}tsCddTpsGen2_RxCONFIG2;


typedef union tuCddTpsGen2_RxBrADCID        { tsCddTpsGen2_RxBrADCID        sRxBrADCID;         uint8  ucRxByte[CDDTPSGEN2_N_BR_RX_ADCID];   }tuCddTpsGen2_RxBrADCID;
typedef union tuCddTpsGen2_RxBrSYSCFG       { tsCddTpsGen2_RxBrSYSCFG       sRxBrSYSCFG;        uint8  ucRxByte[CDDTPSGEN2_N_BR_RX_DEF_CFG]; }tuCddTpsGen2_RxBrSYSCFG;
typedef union tuCddTpsGen2_RxSYSCFG         { tsCddTpsGen2_RxSYSCFG         sRxSYSCFG;          uint8  ucRxByte[CDDTPSGEN2_N_RX_CFG_CHIP];   }tuCddTpsGen2_RxSYSCFG;
typedef union tuCddTpsGen2_RxPHASES         { tsCddTpsGen2_RxPHASES         sRxPHASES;          uint8  ucRxByte[CDDTPSGEN2_N_RX_CFG_PHASE];  }tuCddTpsGen2_RxPHASES;
typedef union tuCddTpsGen2_RxCFGLEDS        { tsCddTpsGen2_RxCFGLEDS        sRxCFGLEDS;         uint8  ucRxByte[CDDTPSGEN2_N_RX_CFG_STRING]; }tuCddTpsGen2_RxCFGLEDS;
typedef union tuCddTpsGen2_RxPWMS           { tsCddTpsGen2_RxPWMS           sRxPWMS;            uint8  ucRxByte[CDDTPSGEN2_N_RX_WIDTH];      }tuCddTpsGen2_RxPWMS;
typedef union tuCddTpsGen2_RxICID           { tsCddTpsGen2_RxICID           sRxICID;            uint8  ucRxByte[CDDTPSGEN2_N_RX_ICID];       }tuCddTpsGen2_RxICID;
typedef union tuCddTpsGen2_RxELEFAULT       { tsCddTpsGen2_RxELEFAULT       sRxELEFAULT;        uint8  ucRxByte[CDDTPSGEN2_N_RX_FAULT];      }tuCddTpsGen2_RxELEFAULT;
typedef union tuCddTpsGen2_RxCLR_ELEFAULT   { tsCddTpsGen2_RxCLR_ELEFAULT   sRxCLR_ELEFAULT;    uint8  ucRxByte[CDDTPSGEN2_N_RX_CLRFLT];     }tuCddTpsGen2_RxCLR_ELEFAULT;
typedef union tuCddTpsGen2_RxADC            { tsCddTpsGen2_RxADC            sRxADC;             uint8  ucRxByte[CDDTPSGEN2_N_RX_ADC];        }tuCddTpsGen2_RxADC;
typedef union tuCddTpsGen2_RxCONFIG1        { tsCddTpsGen2_RxCONFIG1        sRxCONFIG1;         uint8  ucRxByte[CDDTPSGEN2_N_RX_CONFIG1];    }tuCddTpsGen2_RxCONFIG1;
typedef union tuCddTpsGen2_RxCONFIG2        { tsCddTpsGen2_RxCONFIG2        sRxCONFIG2;         uint8  ucRxByte[CDDTPSGEN2_N_RX_CONFIG2];    }tuCddTpsGen2_RxCONFIG2;


typedef struct tsCddTpsGen2_RxI2CSTAT
{
  uint8 ucRxData[CDDTPSGEN2_N_01_BYTE];
  uint8 ucCrc   [CDDTPSGEN2_N_CRC_BYTES];
}tsCddTpsGen2_RxI2CSTAT;

typedef struct tsCddTpsGen2_RxI2CDATA
{
  uint8 ucRxData[CDDTPSGEN2_N_16_BYTES];    /* max size supported for EE read = 12 bytes -  de ce a pus in LDM 16 ? */
  uint8 ucCrc   [CDDTPSGEN2_N_CRC_BYTES];
}tsCddTpsGen2_RxI2CDATA;

typedef union tuCddTpsGen2_RxI2CSTAT        { tsCddTpsGen2_RxI2CSTAT        sRxI2CSTAT;         uint8  ucRxByte[CDDTPSGEN2_EE_N_RX_STATUS];     }tuCddTpsGen2_RxI2CSTAT;
typedef union tuCddTpsGen2_RxI2CDATA        { tsCddTpsGen2_RxI2CDATA        sRxI2CDATA;         uint8  ucRxByte[CDDTPSGEN2_EE_N_RX_READ_DATA];  }tuCddTpsGen2_RxI2CDATA;


typedef struct tsCddTpsGen2_CtrlTxReg
{
  tuCddTpsGen2_MPHASEReg          RegMPHASE[CFG_MAX_NO_OF_MLC];
  tuCddTpsGen2_MWIDTHReg          RegMWIDTH[CFG_MAX_NO_OF_MLC];
  tuCddTpsGen2_StringCfg          RegSTRINGS[CFG_MAX_NO_OF_MLC];
  tuCddTpsGen2_RegSYSCFG          RegSYSCFG_DEFAULT[CFG_MAX_NO_OF_MLC];
  tuCddTpsGen2_SystemCfgReg       RegSYSCFG[CFG_MAX_NO_OF_MLC];
  tuCddTpsGen2_RegADCID           RegADCID[CFG_MAX_NO_OF_MLC];
  tuCddTpsGen2_RegSOFTSYNC        RegSOFTSYNC[CFG_MAX_NO_OF_MLC];
  tuCddTpsGen2_FaultCtrlReg       RegELEFAULT[CFG_MAX_NO_OF_MLC];
}tsCddTpsGen2_CtrlTxReg;

typedef struct tsCddTpsGen2_BrCmd
{
  tuCddTpsGen2_RxBrADCID    RxBrADCID;
  tuCddTpsGen2_RxBrSYSCFG   RxBrSYSCFG;
}tsCddTpsGen2_BrCmd;

typedef struct tsCddTpsGen2_StatReg
{
  tuCddTpsGen2_RxICID         RxICID[CFG_MAX_NO_OF_MLC];
  tuCddTpsGen2_RxSYSCFG       RxSYSCFG[CFG_MAX_NO_OF_MLC];
  tuCddTpsGen2_RxPHASES       RxPHASES[CFG_MAX_NO_OF_MLC];
  tuCddTpsGen2_RxCFGLEDS      RxCFGLEDS[CFG_MAX_NO_OF_MLC];
  tuCddTpsGen2_RxPWMS         RxPWMS[CFG_MAX_NO_OF_MLC];
  tuCddTpsGen2_RxELEFAULT     RxELEFAULT[CFG_MAX_NO_OF_MLC];
  tuCddTpsGen2_RxCLR_ELEFAULT RxCLR_ELEFAULT[CFG_MAX_NO_OF_MLC];
  tuCddTpsGen2_RxADC          RxADC[CFG_MAX_NO_OF_MLC];
  tuCddTpsGen2_RxCONFIG1      RxCONFIG1[CFG_MAX_NO_OF_MLC];
  tuCddTpsGen2_RxCONFIG2      RxCONFIG2[CFG_MAX_NO_OF_MLC];
}tsCddTpsGen2_StatReg;


typedef struct tsCddTpsGen2_DataMirror
{
  tsCddTpsGen2_CtrlTxReg      CtrlTx;
  tsCddTpsGen2_StatReg        StatRx;
}tsCddTpsGen2_DataMirror;



typedef struct tsCddTpsGen2_CtrlTxRegEE
{
  tuCddTpsGen2_RegI2CTICK     TxI2CTICK;        /* 1) Init */
  tuCddTpsGen2_RegI2CSeqCfg   TxsI2CSEQCFG;     /* 2) Start Seq - 4 Regs */
  tuCddTpsGen2_RegI2CDAT      TxI2CDAT;         /* 3) Write Data */
  tuCddTpsGen2_RegSYSCFG      TxSYSCFGEE;
}tsCddTpsGen2_CtrlTxRegEE;


typedef struct tsCddTpsGen2_StatRegEE
{
  tuCddTpsGen2_RxI2CSTAT      RxI2CSTAT;        /* 1) Status Reg */
  tuCddTpsGen2_RxI2CDATA      RxI2CDATA;        /* 2) Data Reg */
  uint8                       RxACK;            /* 3) ACK byte */
}tsCddTpsGen2_StatRegEE;


typedef struct tsCddTpsGen2_DataMirrorEE
{
  tsCddTpsGen2_CtrlTxRegEE      CtrlTx;
  tsCddTpsGen2_StatRegEE        StatRx;
}tsCddTpsGen2_DataMirrorEE;


typedef enum
{
  eBroadcastCmd      = 0x01u,
  eSingleFASTCmd     = 0x02u,
  eSingleSLOWCmd     = 0x03u,
  eEEPROMCmd         = 0x04u,
  eInvalidCmd        = 0xFFu,
}teGen2_DynCmdType;

#define CDDTPSGEN2_LEN_0_BYTES      0u
#define CDDTPSGEN2_LEN_1_BYTE       1u
#define CDDTPSGEN2_LEN_2_BYTES      2u
#define CDDTPSGEN2_LEN_3_BYTES      3u
#define CDDTPSGEN2_LEN_4_BYTES      4u
#define CDDTPSGEN2_LEN_5_BYTES      5u
#define CDDTPSGEN2_LEN_6_BYTES      6u
#define CDDTPSGEN2_LEN_12_BYTES     12u
#define CDDTPSGEN2_LEN_14_BYTES     14u
#define CDDTPSGEN2_LEN_16_BYTES     16u
#define CDDTPSGEN2_LEN_18_BYTES     18u
#define CDDTPSGEN2_LEN_32_BYTES     32u
#define CDDTPSGEN2_LEN_34_BYTES     34u

//when dynamic configuration is set, other function handle/move the next state from scheduler
#define  CDDTPSGEN2_STATE_EE_PREINIT          0
#define  CDDTPSGEN2_STATE_EE_INIT             1
#define  CDDTPSGEN2_STATE_EE_READ_START       2
#define  CDDTPSGEN2_STATE_EE_RR_STATUS        3
#define  CDDTPSGEN2_STATE_EE_READ_1_BYTE      4
#define  CDDTPSGEN2_STATE_EE_READ_2_BYTES     5
#define  CDDTPSGEN2_STATE_EE_READ_3_BYTES     6
#define  CDDTPSGEN2_STATE_EE_READ_4_BYTES     7
#define  CDDTPSGEN2_STATE_EE_READ_12_BYTES    8
#define  CDDTPSGEN2_STATE_EE_READ_16_BYTES    9
#define  CDDTPSGEN2_STATE_EE_WRITE_DATA       10
#define  CDDTPSGEN2_STATE_EE_WRITE_START      11
#define  CDDTPSGEN2_STATE_EE_RW_STATUS        12
#define  CDDTPSGEN2_STATE_EE_RESET            13

typedef struct {
  uint32 ulMlcStatus;                                // Global Communication Status for each Mlc device  
  uint32 ulPowerCycleOccurred;                       // Global Power Cycle Flag for each Mlc device
  uint32 ulUartErrorsOccurred;                       // UART Communication Errors Occurrence Counter
  uint32 ulTxCommandOverrun;                         // Counter of Commands not sent during a Mlc cycle   
  uint32 ulAckChipSetting;                           // Acknowledged Chip Setting Configuration
  uint32 ulAckPhaseShifts;                           // Acknowledged Phase Shifts Configuration 
  uint32 ulAckLedSegments;                           // Acknowledged LED Segments Configuration 
  uint8  ucMatrixIcID_List[CFG_MAX_NO_OF_MLC];       // Matrix Chip ID for each device
  uint8  ucTimeoutCounter_List[CFG_MAX_NO_OF_MLC];   // Reception failed counter for each device    
  uint8  ucCrcFltOccurrence_List[CFG_MAX_NO_OF_MLC]; // CRC ERROR count for each device      
} tsCddTpsGen2_ComStatus;

//-----------------------------------------------------------------------------
// Start declaration or definitions of functions
//-----------------------------------------------------------------------------

void    CddTpsGen2_SetWIDTHReg        (const uint8 ucChipIdx, const uint16* punDuty);
void    CddTpsGen2_GetADCReg          (const uint8_fast ucChipIdx, tuCddTpsGen2_RxADC* puADCReg);
void    CddTpsGen2_GetELEFAULTReg     (const uint8_fast ucChipIdx, tuCddTpsGen2_RxELEFAULT* puELEFAULTReg);
boolean CddTpsGen2_GetComFAULT        (const uint8_fast ucChipIdx);
boolean CddTpsGen2_GetCrcFAULT        (const uint8_fast ucChipIdx);
boolean CddTpsGen2_GetMuxCmdCompleted (void);
boolean CddTpsGen2_GetInitCmdCompleted(void);

boolean CddTpsGen2_I2C_CheckEEActivation(uint8 *pucGoToSt);

void CddTpsGen2_I2C_HandlePreinit(uint8 *pucAck);
void CddTpsGen2_I2C_HandleInit(uint8 *pucAck);
void CddTpsGen2_I2C_HandleStart(uint8 *pucAck);
void CddTpsGen2_I2C_HandleReadData(uint8 *pucData);
void CddTpsGen2_I2C_HandleReadingStatus(const uint8 ucStatus);
void CddTpsGen2_I2C_HandleWritingStatus(const uint8 ucStatus);
void CddTpsGen2_I2C_HandleWriteData(uint8 *pucAck);
void CddTpsGen2_I2C_HandleReset(uint8 *pucAck);

void CddTpsGen2_I2C_CmdPreinit(void);
void CddTpsGen2_I2C_CmdReadStart(const uint8 ucRemainedBytes, const uint8 ucStartAddr);
void CddTpsGen2_I2C_CmdWriteStart(const uint8 ucStartAddr);
void CddTpsGen2_I2C_CmdWriteData(uint8 *pucData);
void CddTpsGen2_I2C_CmdReset(void);
//-----------------------------------------------------------------------------
// End declaration or definitions of functions
//-----------------------------------------------------------------------------



#endif // CDD_TPS92662A_COM_2023_09_06_H

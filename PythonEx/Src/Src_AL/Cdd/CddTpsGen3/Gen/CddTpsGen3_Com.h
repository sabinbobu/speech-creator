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
/// \file  CddTpsGen3_Com.h
///
/// \brief
///
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
///
//-----------------------------------------------------------------------------
#ifndef CDD_TPS_GEN3_COM_2024_02_05_H
#define CDD_TPS_GEN3_COM_2024_02_05_H

//=============================================================================
// Includes
//=============================================================================
#include <Std_Types.h>

#include <CddTpsGen3_Types.h>
#include <CddTpsGen3_Cfg.h>

//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------
#define CFG_MAX_NO_OF_MLC_CHIPS                      CFG_MLC_Chip_Cnt 


//=============================================================================
// Mirror GEN3 FAM. registers (TPS92664 | 5 | 7 )
//=============================================================================

typedef struct tsCddTpsGen3_RxBrADCID
{
  uint8 ucRxData[CDDTPSGEN3_N_01_BYTE];
  uint8 ucCrc[CDDTPSGEN3_N_CRC_BYTES];
}tsCddTpsGen3_RxBrADCID;

typedef struct tsCddTpsGen3_RxBrSYSCFG
{
  uint8 ucRxData[CDDTPSGEN3_N_01_BYTE];
  uint8 ucCrc[CDDTPSGEN3_N_CRC_BYTES];
}tsCddTpsGen3_RxBrSYSCFG;

typedef struct tsCddTpsGen3_RxICID
{
  uint8 ucRxData[CDDTPSGEN3_N_01_BYTE];
  uint8 ucCrc[CDDTPSGEN3_N_CRC_BYTES];
}tsCddTpsGen3_RxICID;

typedef struct tsCddTpsGen3_RxSYSCFG
{
  uint8 ucRxACK[CDDTPSGEN3_N_ACK];
}tsCddTpsGen3_RxSYSCFG;

typedef struct tsCddTpsGen3_RxSYSCONFIG
{
  uint8 ucRxData[CDDTPSGEN3_N_03_BYTES];
  uint8 ucCrc[CDDTPSGEN3_N_CRC_BYTES];
}tsCddTpsGen3_RxSYSCONFIG;

typedef struct tsCddTpsGen3_RxSSYNC_STATUS
{
  uint8 ucRxACK[CDDTPSGEN3_N_ACK];
}tsCddTpsGen3_RxSSYNC_STATUS;

typedef struct tsCddTpsGen3_RxPHASES_MSB
{
  uint8 ucRxACK[CDDTPSGEN3_N_ACK];
}tsCddTpsGen3_RxPHASES_MSB;

typedef struct tsCddTpsGen3_RxPHASES_LSB
{
  uint8 ucRxACK[CDDTPSGEN3_N_ACK];
}tsCddTpsGen3_RxPHASES_LSB;

typedef struct tsCddTpsGen3_RxCFGLEDS
{
  uint8 ucRxACK[CDDTPSGEN3_N_ACK];
}tsCddTpsGen3_RxCFGLEDS;

typedef struct tsCddTpsGen3_RxCFGDEF
{
  uint8 ucRxACK[CDDTPSGEN3_N_ACK];
}tsCddTpsGen3_RxCFGDEF;

typedef struct tsCddTpsGen3_RxPWMS_MSB
{
  uint8 ucRxACK[CDDTPSGEN3_N_ACK];
}tsCddTpsGen3_RxPWMS_MSB;


typedef struct tsCddTpsGen3_RxPWMS_LSB
{
  uint8 ucRxACK[CDDTPSGEN3_N_ACK];
}tsCddTpsGen3_RxPWMS_LSB;


typedef struct tsCddTpsGen3_RxELEFAULT
{
  uint8 ucRxData[CDDTPSGEN3_N_04_BYTES];
  uint8 ucCrc[CDDTPSGEN3_N_CRC_BYTES];
}tsCddTpsGen3_RxELEFAULT;

typedef struct tsCddTpsGen3_RxCLR_ELEFAULT
{
  uint8 ucRxACK[CDDTPSGEN3_N_ACK];
}tsCddTpsGen3_RxCLR_ELEFAULT;

typedef struct tsCddTpsGen3_RxEXIT_FS
{
  uint8 ucRxACK[CDDTPSGEN3_N_ACK];
}tsCddTpsGen3_RxEXIT_FS;

typedef struct tsCddTpsGen3_RxOUTCTRL
{
  uint8 ucRxACK[CDDTPSGEN3_N_ACK];
}tsCddTpsGen3_RxOUTCTRL;

typedef struct tsCddTpsGen3_RxADC
{
  uint8 ucRxData[CDDTPSGEN3_N_04_BYTES];
  uint8 ucCrc[CDDTPSGEN3_N_CRC_BYTES];
}tsCddTpsGen3_RxADC;

typedef struct tsCddTpsGen3_RxSTATUS
{
  uint8 ucRxData[CDDTPSGEN3_N_01_BYTE];
  uint8 ucCrc[CDDTPSGEN3_N_CRC_BYTES];
}tsCddTpsGen3_RxSTATUS;

typedef struct tsCddTpsGen3_RxSLEWRATE
{
  uint8 ucRxData[CDDTPSGEN3_N_04_BYTES];
  uint8 ucCrc[CDDTPSGEN3_N_CRC_BYTES];
}tsCddTpsGen3_RxSLEWRATE;

typedef union tuCddTpsGen3_RxBrADCID          { tsCddTpsGen3_RxBrADCID            sRxBrADCID;             uint8  ucRxByte[CDDTPSGEN3_N_BR_RX_ADCID];          }tuCddTpsGen3_RxBrADCID;
typedef union tuCddTpsGen3_RxBrSYSCFG         { tsCddTpsGen3_RxBrSYSCFG           sRxBrSYSCFG;            uint8  ucRxByte[CDDTPSGEN3_N_BR_RX_DEF_CFG];        }tuCddTpsGen3_RxBrSYSCFG;
typedef union tuCddTpsGen3_RxICID             { tsCddTpsGen3_RxICID               sRxICID;                uint8  ucRxByte[CDDTPSGEN3_N_RX_ICID];              }tuCddTpsGen3_RxICID;
typedef union tuCddTpsGen3_RxSYSCFG           { tsCddTpsGen3_RxSYSCFG             sRxSYSCFG;              uint8  ucRxByte[CDDTPSGEN3_N_RX_CFG_CHIP];          }tuCddTpsGen3_RxSYSCFG;
typedef union tuCddTpsGen3_RxSYSCONFIG        { tsCddTpsGen3_RxSYSCONFIG          sRxSYSCONFIG;           uint8  ucRxByte[CDDTPSGEN3_N_RX_SYSCONFIG];         }tuCddTpsGen3_RxSYSCONFIG;
typedef union tuCddTpsGen3_RxSSYNC_STATUS     { tsCddTpsGen3_RxSSYNC_STATUS       sRxSSYNC_STATUS;        uint8  ucRxByte[CDDTPSGEN3_N_RX_CFG_SSYNC];         }tuCddTpsGen3_RxSSYNC_STATUS;
typedef union tuCddTpsGen3_RxPHASES_MSB       { tsCddTpsGen3_RxPHASES_MSB         sRxPHASES_MSB;          uint8  ucRxByte[CDDTPSGEN3_N_RX_CFG_PHASE];         }tuCddTpsGen3_RxPHASES_MSB;
typedef union tuCddTpsGen3_RxPHASES_LSB       { tsCddTpsGen3_RxPHASES_LSB         sRxPHASES_LSB;          uint8  ucRxByte[CDDTPSGEN3_N_RX_CFG_PHASE];         }tuCddTpsGen3_RxPHASES_LSB;
typedef union tuCddTpsGen3_RxCFGLEDS          { tsCddTpsGen3_RxCFGLEDS            sRxCFGLEDS;             uint8  ucRxByte[CDDTPSGEN3_N_RX_CFG_STRING];        }tuCddTpsGen3_RxCFGLEDS;
typedef union tuCddTpsGen3_RxCFGDEF           { tsCddTpsGen3_RxCFGDEF             sRxCFGDEF;              uint8  ucRxByte[CDDTPSGEN3_N_RX_CFG_STRING];        }tuCddTpsGen3_RxCFGDEF;
typedef union tuCddTpsGen3_RxPWMS_MSB         { tsCddTpsGen3_RxPWMS_MSB           sRxPWMS_MSB;            uint8  ucRxByte[CDDTPSGEN3_N_RX_WIDTH];             }tuCddTpsGen3_RxPWMS_MSB;
typedef union tuCddTpsGen3_RxPWMS_LSB         { tsCddTpsGen3_RxPWMS_LSB           sRxPWMS_LSB;            uint8  ucRxByte[CDDTPSGEN3_N_RX_WIDTH];             }tuCddTpsGen3_RxPWMS_LSB;
typedef union tuCddTpsGen3_RxELEFAULT         { tsCddTpsGen3_RxELEFAULT           sRxELEFAULT;            uint8  ucRxByte[CDDTPSGEN3_N_RX_FAULT];             }tuCddTpsGen3_RxELEFAULT;
typedef union tuCddTpsGen3_RxEXIT_FS          { tsCddTpsGen3_RxEXIT_FS            sRxEXIT_FS;             uint8  ucRxByte[CDDTPSGEN3_N_RX_CFG_EXITFAILSAFE];  }tuCddTpsGen3_RxEXIT_FS;
typedef union tuCddTpsGen3_RxOUTCTRL          { tsCddTpsGen3_RxOUTCTRL            sRxOUTCTRL;             uint8  ucRxByte[CDDTPSGEN3_N_RX_CFG_OUTCTRL];       }tuCddTpsGen3_RxOUTCTRL;
typedef union tuCddTpsGen3_RxCLR_ELEFAULT     { tsCddTpsGen3_RxELEFAULT           sRxCLR_ELEFAULT;        uint8  ucRxByte[CDDTPSGEN3_N_RX_CLRFLT];            }tuCddTpsGen3_RxCLR_ELEFAULT;
typedef union tuCddTpsGen3_RxADC              { tsCddTpsGen3_RxADC                sRxADC;                 uint8  ucRxByte[CDDTPSGEN3_N_RX_ADC];               }tuCddTpsGen3_RxADC;
typedef union tuCddTpsGen3_RxSTATUS           { tsCddTpsGen3_RxSTATUS             sRxSTATUS;              uint8  ucRxByte[CDDTPSGEN3_N_RX_STATUS];            }tuCddTpsGen3_RxSTATUS;
typedef union tuCddTpsGen3_RxSLEWRATE         { tsCddTpsGen3_RxSLEWRATE           sRxSLEWRATE;            uint8  ucRxByte[CDDTPSGEN3_N_RX_SLEWRATE];          }tuCddTpsGen3_RxSLEWRATE;

typedef struct tsCddTpsGen3_CtrlTxReg
{
  tuCddTpsGen3_PHASE_MSB_Reg        RegPHASE_MSB      [CFG_MAX_NO_OF_MLC_CHIPS];
  tuCddTpsGen3_PHASE_LSB_Reg        RegPHASE_LSB      [CFG_MAX_NO_OF_MLC_CHIPS];
  tuCddTpsGen3_WIDTH_MSB_Reg        RegWIDTH_MSB      [CFG_MAX_NO_OF_MLC_CHIPS];
  tuCddTpsGen3_WIDTH_LSB_Reg        RegWIDTH_LSB      [CFG_MAX_NO_OF_MLC_CHIPS];
  tuCddTpsGen3_SLEWRATE_Reg         RegSLEWRATE       [CFG_MAX_NO_OF_MLC_CHIPS];
  tuCddTpsGen3_DefWIDTHRegs         RegDEFWIDTH       [CFG_MAX_NO_OF_MLC_CHIPS];
  tuCddTpsGen3_RegSYSCFG            RegSYSCFG_DEFAULT [CFG_MAX_NO_OF_MLC_CHIPS];
  tuCddTpsGen3_SystemCfgReg         RegSYSCFG         [CFG_MAX_NO_OF_MLC_CHIPS];
  tuCddTpsGen3_SSYNC_STATUS_Reg     RegSSYNC_STATUS   [CFG_MAX_NO_OF_MLC_CHIPS];
  tuCddTpsGen3_RegMTPCFG            Reg_MPTCFG_FS     [CFG_MAX_NO_OF_MLC_CHIPS];
  tuCddTpsGen3_RegOUTCTRL           RegOUTCTRL        [CFG_MAX_NO_OF_MLC_CHIPS];
  tuCddTpsGen3_FaultCtrlReg         RegELEFAULT       [CFG_MAX_NO_OF_MLC_CHIPS];
}tsCddTpsGen3_CtrlTxReg;


typedef struct tsCddTpsGen3_StatReg
{
  tuCddTpsGen3_RxICID               RxICID            [CFG_MAX_NO_OF_MLC_CHIPS];
  tuCddTpsGen3_RxSYSCONFIG          RxSYSCONFIG       [CFG_MAX_NO_OF_MLC_CHIPS];
  tuCddTpsGen3_RxSYSCFG             RxSYSCFG          [CFG_MAX_NO_OF_MLC_CHIPS];
  tuCddTpsGen3_RxSSYNC_STATUS       RxSSYNC_STATUS    [CFG_MAX_NO_OF_MLC_CHIPS];
  tuCddTpsGen3_RxPHASES_MSB         RxPHASES_MSB      [CFG_MAX_NO_OF_MLC_CHIPS];
  tuCddTpsGen3_RxPHASES_LSB         RxPHASES_LSB      [CFG_MAX_NO_OF_MLC_CHIPS];
  tuCddTpsGen3_RxCFGLEDS            RxCFGLEDS         [CFG_MAX_NO_OF_MLC_CHIPS];
  tuCddTpsGen3_RxCFGDEF             RxCFGDEF          [CFG_MAX_NO_OF_MLC_CHIPS];
  tuCddTpsGen3_RxEXIT_FS            RxEXIT_FS         [CFG_MAX_NO_OF_MLC_CHIPS];
  tuCddTpsGen3_RxOUTCTRL            RxOUTCTRL         [CFG_MAX_NO_OF_MLC_CHIPS];
  tuCddTpsGen3_RxPWMS_MSB           RxPWMS_MSB        [CFG_MAX_NO_OF_MLC_CHIPS];
  tuCddTpsGen3_RxPWMS_LSB           RxPWMS_LSB        [CFG_MAX_NO_OF_MLC_CHIPS];
  tuCddTpsGen3_RxELEFAULT           RxELEFAULT        [CFG_MAX_NO_OF_MLC_CHIPS];
  tuCddTpsGen3_RxCLR_ELEFAULT       RxCLR_ELEFAULT    [CFG_MAX_NO_OF_MLC_CHIPS];
  tuCddTpsGen3_RxADC                RxADC             [CFG_MAX_NO_OF_MLC_CHIPS];
  tuCddTpsGen3_RxSTATUS             RxSTATUS          [CFG_MAX_NO_OF_MLC_CHIPS];
  tuCddTpsGen3_RxSLEWRATE           RxSLEWRATE        [CFG_MAX_NO_OF_MLC_CHIPS];
}tsCddTpsGen3_StatReg;


typedef struct tsCddTpsGen3_DataMirror
{
  tsCddTpsGen3_CtrlTxReg      CtrlTx;
  tsCddTpsGen3_StatReg        StatRx;
}tsCddTpsGen3_DataMirror;

typedef struct tsCddTpsGen3_BrCmd
{
  tuCddTpsGen3_RxBrADCID    RxBrADCID;
  tuCddTpsGen3_RxBrSYSCFG   RxBrSYSCFG;
}tsCddTpsGen3_BrCmd;

typedef enum
{
  eBroadcastCmd      = 0x01u,
  eSingleFASTCmd     = 0x02u,
  eSingleSLOWCmd     = 0x03u,
  eInvalidCmd        = 0xFFu,
}teGen3_DynCmdType;

#define CDDTPSGEN3_LEN_0_BYTES      0u
#define CDDTPSGEN3_LEN_1_BYTE       1u
#define CDDTPSGEN3_LEN_2_BYTES      2u
#define CDDTPSGEN3_LEN_3_BYTES      3u
#define CDDTPSGEN3_LEN_4_BYTES      4u
#define CDDTPSGEN3_LEN_5_BYTES      5u
#define CDDTPSGEN3_LEN_6_BYTES      6u
#define CDDTPSGEN3_LEN_12_BYTES     12u
#define CDDTPSGEN3_LEN_16_BYTES     16u
#define CDDTPSGEN3_LEN_32_BYTES     32u
#define CDDTPSGEN3_LEN_34_BYTES     34u

//-----------------------------------------------------------------------------
// Start declaration or definitions of functions
//-----------------------------------------------------------------------------

void    CddTpsGen3_SetWIDTHReg        (const uint8 ucChipIdx, const uint16* punDuty);
void    CddTpsGen3_GetADCReg          (const uint8_fast ucChipIdx, tuCddTpsGen3_RxADC* puADCReg);
void    CddTpsGen3_GetELEFAULTReg     (const uint8_fast ucChipIdx, tuCddTpsGen3_RxELEFAULT* puELEFAULTReg);
boolean CddTpsGen3_GetComFAULT        (const uint8_fast ucChipIdx);
boolean CddTpsGen3_GetMuxCmdCompleted (void);
boolean CddTpsGen3_GetInitCmdCompleted(void);
boolean CddTpsGen3_GetCrcFAULT        (const uint8_fast ucChipIdx);
//-----------------------------------------------------------------------------
// End declaration or definitions of functions
//-----------------------------------------------------------------------------

#endif // CDD_TPS_GEN3_COM_2024_02_05_H

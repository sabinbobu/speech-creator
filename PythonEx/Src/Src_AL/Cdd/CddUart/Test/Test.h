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
/// \file  Test.h
///
/// \brief This file contains functions prototypes of the tested module, 
///        including functions parameters and global variables
///
//-----------------------------------------------------------------------------
#ifndef TEST_2023_08_25_H_
#define TEST_2023_08_25_H_

//=============================================================================
// Includes
//=============================================================================
#include <AL_Helper.h>

#include "Test_Stubs.h"
#include "CddUart.h"
#include "CddUart_S32K_14X_Types.h"
#include <CddUart_Cfg.h>

//=============================================================================
// Typedefs
//=============================================================================

typedef boolean(*tfpCddUartDevDynCfg)(uint8 ucDevUartCfg, uint8* pucBaudRate, uint8* pucMountedDev);

typedef struct tsCddUartDevDynCfg
{
  tfpCddUartDevDynCfg fpDevDynCfgCb;
}tsCddUartDevDynCfg;

typedef enum teCddUartIfcSingleMode
{
  CddUart_eIfcSingleMode_Polling = 0,
  CddUart_eIfcSingleMode_Interrupt = 1,
  CddUart_eIfcSingleMode_DMA = 2,
}teCddUartIfcSingleMode;

typedef enum teCddUartIfcCyclicMode
{
  CddUart_eIfcCyclicMode_Polling = 0,
  CddUart_eIfcCyclicMode_Interrupt = 1,
  CddUart_eIfcCyclicMode_DMA = 2,
}teCddUartIfcCyclicMode;

typedef struct tsCddUartIfcCfg
{
  CONST_AL uint8                    ucIfcMap;
  CONST_AL teCddUartIfcSingleMode   eIfcSingleMode;
  CONST_AL teCddUartIfcCyclicMode   eIfcCyclicMode;
  uint8                             ucSeqMap;
}tsCddUartIfcCfg;

typedef void  (*tfpCddUartRxCb)(const uint8* pucRxData, boolean boRxStatus);
typedef void  (*tfpCddUartTxCb)(tsCddUart_MessageEntryType* psTxCbData);
typedef uint8(*tfpCddUartCrc) (uint8* pucData, uint32 ulLength, uint8 ucStartVal, boolean boFirstCall);

typedef struct tsCddUartDevCb
{
  tfpCddUartTxCb fpTx;
  tfpCddUartRxCb fpRx;
}tsCddUartDevCb;

typedef struct tsCddUartCbData
{
  tsCddUartDevCb  sDevCb;
  CONST_AL uint16 unCbId;
}tsCddUartCbData;

typedef struct tsCddUartDevSeqData
{
  tsCddUartCbData* psCbData;
  CONST_AL teCddUartDev     eDev;
  CONST_AL uint8            ucCbCount;
}tsCddUartDevSeqData;

typedef struct tsCddUartDevSeqData_StM
{
  uint8  ucDevAct;
  uint8  ucDevDyn;
  uint8  ucCbAct;
}tsCddUartDevSeqData_StM;

typedef struct tsCddUartSeqData
{
  tsCddUartDevSeqData* psDevData;
  tsCddUartDevSeqData_StM sStM;
}tsCddUartSeqData;

typedef struct tsCddUartSeqHandler
{
  CONST_AL teCddUartIfc eUartIfc;
  uint8                 ucCycleCnt;
  CONST_AL uint8        ucPrescaler;
  CONST_AL uint8        ucTimeOutMax;
  uint8                 ucTimeOutCnt;
  uint8                 ucSeqContext;
  uint8                 ucIntDevIdx;
}tsCddUartSeqHandler;

typedef struct tsCddUartDynamicCfg
{
  uint8 ucMountedDev;
  uint8 aucIdxMountedDev[(uint8)CddUart_eDev_Count];
}tsCddUartDynamicCfg;

//=============================================================================
// Defines
//=============================================================================
#define CDDUART_BAUDRATE_CODING_500Kbps             5U
#define CDDUART_BAUDRATE_CODING_1Mbps               10U

//Sequence context
#define CDDUART_SEQ_CONTEXT_INITIALIZED_MSK         0x01U
#define CDDUART_SEQ_CONTEXT_COMPLETE_MSK            0x02U
#define CDDUART_SEQ_CONTEXT_INITIALIZED_POS         0U
#define CDDUART_SEQ_CONTEXT_COMPLETE_POS            1U

#define CDDUART_UNKNOWN_DEVICE                      0xFFU

//=============================================================================
// Module global variables
//=============================================================================
extern          uint8                           CddUart_ucState;
extern          tsCddUart_S32K_14X_Registers    CddUart_sS32K_14X_Registers;
extern volatile boolean                         CddUart_boIsDmaReady[TEST_SEQ_COUNT];
extern          tsCddUart_S32K_14X_Registers    UART_Register_UnitTest[CddUart_eDev_Count];
extern          tsCddDma_S32K_146_Registers     CDDDMA_BASE_UnitTest;
extern          uint8                           CddUart_aucRxDataDMA[(uint8)TEST_SEQ_COUNT][CDDUART_MAX_RX_DATA];
extern          tsCddUartIfcCfg                 CddUart_asIfcCfg[CddUart_eIfc_Count];
extern          tsCddUartSeqHandler             CddUart_asSeqHandler[];
extern          tsCddUartSeqData                CddUart_asSeqData[];
extern          tsCddUartDevCfg                 CddUart_asDeviceCfg[];
extern          tsCddUartDynamicCfg             CddUart_DynamicCfg[];
extern          tsCddDma_Parameter              CddUart_sDMAConfigTransmission;
extern          boolean                         CddUart_boRxSuccess;
extern          tsCddUart_MessageEntryType      CddUart_sMessageEntry[TEST_SEQ_COUNT];

//=============================================================================
// Module static variables inside functions 
//=============================================================================
boolean boCodingData = FALSE;

//=============================================================================
// Module function declarations
//=============================================================================

// CddUart
extern void riCddUartInit             (void);
extern void rpCddUart_Cycle           (void);
extern void CddUart_Init              (void);
extern void CddUart_DeInit            (void);
extern void CddUart_StartMapping      (void);
extern void CddUart_Cycle             (void);
extern void CddUart_ProcessSequence   (uint8 ucSeq);

// CddUart_S32K_14X
extern void     CddUart_StartTransfer_Deriv       (uint8 ucIfc, uint32* pulTransferData, uint32* pulReceiveData, uint8 ucTxLen, uint8 ucRxLen);
extern boolean  CddUart_TransferCompleteDMA_Deriv (uint8 ucIfc);
extern void     CddUart_FillTxFifo                (uint8 ucIfc, uint8* pucTxData, uint8  ucLength);
extern void     CddUart_ReadRxFifo                (uint8 ucIfc, uint8* pucRxData, uint16 unLength);
extern void     CddUart_RxIntEnable               (uint8 ucIfc);

#endif // TEST_2023_08_25_H_


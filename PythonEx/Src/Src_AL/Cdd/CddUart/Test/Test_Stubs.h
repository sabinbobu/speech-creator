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
/// \file  Test_Stubs.h
///
/// \brief Stub functions prototypes for access to software modules excluded from test
///        including stub parameters
///
//-----------------------------------------------------------------------------
#ifndef TEST_STUBS_2023_08_25_H_
#define TEST_STUBS_2023_08_25_H_

//=============================================================================
// Includes
//=============================================================================
#include <Rte/RteCommonTypes.h>
#include <CddUart_Types.h>
#include <CddUart_Cfg.h>
#include <CddDma.h>

#define TEST_SEQ_COUNT 3u // shall be equal to CddUart_eSeq_Count

typedef struct Test_sMessage {
  uint8 UartTxDummy_Data[50u];
  uint8 UartRxDummy_Data[50u];
}Test_sMessage;

//=============================================================================
// Stub function declarations
//=============================================================================
extern  void         CddTpsGen3_UartTx(tsCddUart_MessageEntryType* psTxCbData);
extern  void         CddTpsGen3_UartRx(const uint8* pucRxData, boolean boRxStatus);
extern  void         CddTpsGen2_UartTx(tsCddUart_MessageEntryType* psTxCbData);
extern  void         CddTpsGen2_UartRx(const uint8* pucRxData, boolean boRxStatus);
extern  boolean      CddMlc_Cod_UartGetConfig(uint8 ucDevUartCfg, uint8* pucBaudRate, uint8* pucMountedDev);
extern  void         CddUart_DMA_RX_CallbackFct(void);
extern  void         CddDma_EnableHwTrigger(CddDma_DynConfig_DmaChannelName_EnumType eDmaChannelName, boolean boEnabled);
extern  void         CddDma_StartJob(CddDma_DynConfig_DmaChannelName_EnumType eDmaChannelName, CONST_AL tsCddDma_Parameter* psParameter, CONST_AL CddDma_tfpCallback fpCallback);
extern  boolean      CddDma_IsJobCompleted(CddDma_DynConfig_DmaChannelName_EnumType eDmaChannelName);


void CddTps_UartTxDummyIFC2(tsCddUart_MessageEntryType* psTxCbData);
void CddTps_UartRxDummyIFC2(const uint8* pucRxData, boolean boRxStatus);
void CddTps_UartTxDummyIFC3(tsCddUart_MessageEntryType* psTxCbData);
void CddTps_UartRxDummyIFC3(const uint8* pucRxData, boolean boRxStatus);

//=============================================================================
// Stub function parameter stubs
//=============================================================================
uint8                                         CddTpsGen3_UartRx_Param1;
boolean                                       CddTpsGen3_UartRx_Param2;
uint8                                         CddTpsGen2_UartRx_Param1;
boolean                                       CddTpsGen2_UartRx_Param2;
uint8                                         CddMlc_Cod_UartGetConfig_Param1;
uint8                                         CddMlc_Cod_UartGetConfig_Param2;
uint8                                         CddMlc_Cod_UartGetConfig_Param3;
CddDma_DynConfig_DmaChannelName_EnumType      CddDma_EnableHwTrigger_Param1;
boolean                                       CddDma_EnableHwTrigger_Param2;
CddDma_DynConfig_DmaChannelName_EnumType      CddDma_StartJob_Param1;
tsCddDma_Parameter                            CddDma_StartJob_Param2;
CddDma_tfpCallback                            CddDma_StartJob_Param3;
CddDma_DynConfig_DmaChannelName_EnumType      CddDma_IsJobCompleted_Param1;

uint8                                         CddTps_UartRxDummyIFC2_Param1;
boolean                                       CddTps_UartRxDummyIFC2_Param2;
uint8                                         CddTps_UartRxDummyIFC3_Param1;
boolean                                       CddTps_UartRxDummyIFC3_Param2;

Test_sMessage                                 Test_sMessageData[TEST_SEQ_COUNT];
extern tsCddUart_MessageEntryType             Test_Uart_sMessageEntry[TEST_SEQ_COUNT];
//=============================================================================
// Stub function returned value stubs
//=============================================================================
boolean  CddMlc_Cod_UartGetConfig_RetVal;
boolean  CddDma_IsJobCompleted_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================
uint8 CddTpsGen3_UartTx_HitCount;
uint8 CddTpsGen3_UartRx_HitCount;
uint8 CddTpsGen2_UartTx_HitCount;
uint8 CddTpsGen2_UartRx_HitCount;
uint8 CddMlc_Cod_UartGetConfig_HitCount;
uint8 CddDma_EnableHwTrigger_HitCount;
uint8 CddDma_StartJob_HitCount;
uint8 CddDma_IsJobCompleted_HitCount;

uint8 CddTps_UartTxDummyIFC2_HitCount;
uint8 CddTps_UartTxDummyIFC3_HitCount;
uint8 CddTps_UartRxDummyIFC2_HitCount;
uint8 CddTps_UartRxDummyIFC3_HitCount;

#endif // TEST_STUBS_2023_08_25_H_

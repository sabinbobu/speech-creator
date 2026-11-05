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
/// \file  Test_Stubs.c
///
/// \brief Stub functions for access to software modules excluded from test
///
//-----------------------------------------------------------------------------

//=============================================================================
// Includes
//=============================================================================
#include "Test_Stubs.h"

tsCddUart_MessageEntryType  Test_Uart_sMessageEntry[TEST_SEQ_COUNT] ={
                                                                        { Test_sMessageData[0].UartTxDummy_Data, 50, Test_sMessageData[0].UartRxDummy_Data, 50, 0},
                                                                        { Test_sMessageData[1].UartTxDummy_Data, 50, Test_sMessageData[1].UartRxDummy_Data, 50, 0},
                                                                        { Test_sMessageData[2].UartTxDummy_Data, 50, Test_sMessageData[2].UartRxDummy_Data, 50, 0},
                                                                      };

//=============================================================================
// Stub function definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen3_UartTx
///
/// \descr Stub used to simulate the behavior of CddTpsGen3_UartTx
///
/// \param  *psTxCbData
///
/// \return void
//-----------------------------------------------------------------------------
void CddTpsGen3_UartTx(tsCddUart_MessageEntryType* psTxCbData)
{
  *psTxCbData = Test_Uart_sMessageEntry[0];
  CddTpsGen3_UartTx_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen3_UartRx
///
/// \descr Stub used to simulate the behavior of CddTpsGen3_UartRx
///
/// \param1  *pucRxData
/// \param2  boRxStatus
///
/// \return void
//-----------------------------------------------------------------------------
void CddTpsGen3_UartRx(const uint8* pucRxData, boolean boRxStatus)
{
  Test_Uart_sMessageEntry[0].pucRxData[0] = *pucRxData;
  boRxStatus = CddTpsGen3_UartRx_Param2;
  CddTpsGen3_UartRx_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_UartTx
///
/// \descr Stub used to simulate the behavior of CddTpsGen2_UartTx
///
/// \param  *psTxCbData
///
/// \return void
//-----------------------------------------------------------------------------
void CddTpsGen2_UartTx(tsCddUart_MessageEntryType* psTxCbData)
{
  *psTxCbData = Test_Uart_sMessageEntry[0];
  CddTpsGen2_UartTx_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_UartRx
///
/// \descr Stub used to simulate the behavior of CddTpsGen2_UartRx
///
/// \param1  *pucRxData
/// \param2  boRxStatus
///
/// \return void
//-----------------------------------------------------------------------------
void CddTpsGen2_UartRx(const uint8* pucRxData, boolean boRxStatus)
{
  Test_Uart_sMessageEntry[0].pucRxData[0] = *pucRxData;
  boRxStatus = CddTpsGen2_UartRx_Param2;
  CddTpsGen2_UartRx_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  CddMlc_Cod_UartGetConfig
///
/// \descr Stub used to simulate the behavior of CddMlc_Cod_UartGetConfig
///
/// \param1  uint8
/// \param2  *uint8
/// \param3  *uint8
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CddMlc_Cod_UartGetConfig(uint8 ucDevUartCfg, uint8* pucBaudRate, uint8* pucMountedDev)
{
  CddMlc_Cod_UartGetConfig_Param1 = ucDevUartCfg;
  *pucBaudRate    = CddMlc_Cod_UartGetConfig_Param2;
  *pucMountedDev  = CddMlc_Cod_UartGetConfig_Param3;
  CddMlc_Cod_UartGetConfig_HitCount++;

  return CddMlc_Cod_UartGetConfig_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  CddDma_EnableHwTrigger
///
/// \descr Stub used to simulate the behavior of CddDma_EnableHwTrigger
///
/// \param1  CddDma_DynConfig_DmaChannelName_EnumType
/// \param2  boolean
///
/// \return void
//-----------------------------------------------------------------------------
void CddDma_EnableHwTrigger(CddDma_DynConfig_DmaChannelName_EnumType eDmaChannelName, boolean boEnabled)
{
  CddDma_EnableHwTrigger_Param1 = eDmaChannelName;
  CddDma_EnableHwTrigger_Param2 = boEnabled;
  CddMlc_Cod_UartGetConfig_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief CddDma_StartJob
///
/// \descr Stub function created to simulate the behavior of CddDma_StartJob
///
/// \param  eDmaChannelName - DMA channel Id
///         psParameter     - parameter with repetitions and addresses
///         fpCallback      - function pointer for a callback
///
/// \return 
//-----------------------------------------------------------------------------
void CddDma_StartJob(CddDma_DynConfig_DmaChannelName_EnumType eDmaChannelName, CONST_AL tsCddDma_Parameter* psParameter, CONST_AL CddDma_tfpCallback fpCallback)
{
  CddDma_StartJob_Param1 = eDmaChannelName;
  CddDma_StartJob_Param2 = *psParameter;
  CddDma_StartJob_Param3 = fpCallback;
  CddDma_StartJob_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief CddDma_IsJobCompleted
///
/// \descr Stub function created to simulate the behavior of CddDma_IsJobCompleted function
///
/// \param eDmaChannelName
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CddDma_IsJobCompleted(CddDma_DynConfig_DmaChannelName_EnumType eDmaChannelName)
{
  CddDma_IsJobCompleted_Param1 = eDmaChannelName;

  CddDma_IsJobCompleted_HitCount++;

  return  CddDma_IsJobCompleted_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  CddTps_UartTxDummyIFC2
///
/// \descr Dummy Stub to check the correct calling from the seq structure CDDUART_IFC2
///
/// \param  *psTxCbData
///
/// \return void
//-----------------------------------------------------------------------------
void CddTps_UartTxDummyIFC2(tsCddUart_MessageEntryType* psTxCbData)
{
  *psTxCbData = Test_Uart_sMessageEntry[1];
  CddTps_UartTxDummyIFC2_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  CddTps_UartRxDummyIFC2
///
/// \descr Dummy Stub to check the correct calling from the seq structure CDDUART_IFC2
///
/// \param1  *pucRxData
/// \param2  boRxStatus
///
/// \return void
//-----------------------------------------------------------------------------
void CddTps_UartRxDummyIFC2(const uint8* pucRxData, boolean boRxStatus)
{
  Test_Uart_sMessageEntry[1].pucRxData[0] = *pucRxData;
  boRxStatus = CddTps_UartRxDummyIFC2_Param2;
  CddTps_UartRxDummyIFC2_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  CddTps_UartTxDummyIFC3
///
/// \descr Dummy Stub to check the correct calling from the seq structure CDDUART_IFC3
///
/// \param  *psTxCbData
///
/// \return void
//-----------------------------------------------------------------------------
void CddTps_UartTxDummyIFC3(tsCddUart_MessageEntryType* psTxCbData)
{
  *psTxCbData = Test_Uart_sMessageEntry[2];
  CddTps_UartTxDummyIFC3_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  CddTps_UartRxDummyIFC3
///
/// \descr Dummy Stub to check the correct calling from the seq structure CDDUART_IFC3
///
/// \param1  *pucRxData
/// \param2  boRxStatus
///
/// \return void
//-----------------------------------------------------------------------------
void CddTps_UartRxDummyIFC3(const uint8* pucRxData, boolean boRxStatus)
{
  Test_Uart_sMessageEntry[2].pucRxData[0] = *pucRxData;
  boRxStatus = CddTps_UartRxDummyIFC3_Param2;
  CddTps_UartRxDummyIFC3_HitCount++;
}








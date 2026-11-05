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


//=============================================================================
// Stub function parameter stubs
//=============================================================================
uint16                                   CddSbc_SpiRx_unId;
uint32                                   CddSbc_SpiRx_ulData;
uint16                                   CddSbc_SpiTx_unId;
uint16                                   CddTps92520_SpiRx_unId;
uint16                                   CddTps92520_SpiTx_unId;
uint16                                   CddNcv78702_SpiRx_unId;
uint32                                   CddNcv78702_SpiRx_ulData;
uint16                                   CddNcv78702_SpiTx_unId;
uint32                                   CddStp_SpiRx_unId;
uint32                                   CddTle94x1_SpiTx_unId;
uint32                                   CddTle94x1_SpiRx_unId;
uint32                                   CddStp_SpiRx_ulData;
uint32                                   CddTle94x1_SpiRx_ulData;
uint32                                   CddTle94x1CddStp_SpiRx_ulData;
uint32                                   CddStp_SpiTx_unId;
CddDma_DynConfig_DmaChannelName_EnumType CddDma_IsJobCompleted_eDmaChannelName;
CddDma_DynConfig_DmaChannelName_EnumType CddDma_StartJob_eDmaChannelName;
tsCddDma_Parameter*                      CddDma_StartJob_psParameter;
CddDma_tfpCallback                       CddDma_StartJob_fpCallback;

tieDataStatus                            Rte_Read_ctacCddSpi_ppCodMEftCrcStatus0_sVal_eData;
tieEftData                               Stub_sEftInitVal;
tieEftDataPtr                            Stub_psEftAddr = &Stub_sEftInitVal;
uint16                                   CddTps92520_SpiGetConfig_unData;

//=============================================================================
// Stub function returned value stubs
//=============================================================================
uint32                                   CddSbc_SpiTx_ulReturn;
uint32                                   CddTps92520_SpiRx_ulData[7];
uint32                                   CddTps92520_SpiTx_ulReturn[7];
uint32                                   CddTle94x1_SpiTx_ulReturn[7];
uint32                                   CddNcv78702_SpiTx_ulReturn;
uint32                                   CddStp_SpiTx_ulReturn;
boolean                                  CddDma_IsJobCompleted_boReturn;
Std_ReturnType                           Rte_Read_ctacCddSpi_ppCodMEftCrcStatus0_sVal_ucReturn;
boolean                                  CddTps92520_SpiGetConfig_boReturn;

//=============================================================================
// Stub function hit count variables
//=============================================================================
uint32                                   CddSbc_SpiRx_HitCount;
uint32                                   CddSbc_SpiTx_HitCount;
uint32                                   CddTps92520_SpiRx_HitCount;
uint32                                   CddTps92520_SpiTx_HitCount;
uint32                                   CddNcv78702_SpiRx_HitCount;
uint32                                   CddNcv78702_SpiTx_HitCount;
uint32                                   CddStp_SpiRx_HitCount;
uint32                                   CddTle94x1_SpiTx_HitCount;
uint32                                   CddTle94x1_SpiRx_HitCount;
uint32                                   CddStp_SpiTx_HitCount;
uint32                                   CddDma_IsJobCompleted_HitCount;
uint32                                   CddDma_StartJob_HitCount;
uint32                                   CddTps92520_SpiGetConfig_HitCount;

//=============================================================================
// Stub function definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief CddSbc_SpiRx
///
/// \descr Stub function created to simulate the behaviour of CddSbc_SpiRx
///
/// \param  unId - decvice Id
///         ulData - data to be transfered
///
/// \return -
//-----------------------------------------------------------------------------
void CddSbc_SpiRx(uint16 unId, uint32 ulData)
{
  CddSbc_SpiRx_unId = unId;
  CddSbc_SpiRx_ulData = ulData;
  CddSbc_SpiRx_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief CddSbc_SpiTx
///
/// \descr Stub function created to simulate the behaviour of CddSbc_SpiTx
///
/// \param  unId - decvice Id
///
/// \return data to be transfered
//-----------------------------------------------------------------------------
uint32 CddSbc_SpiTx(uint16 unId)
{
  CddSbc_SpiTx_unId = unId;
  CddSbc_SpiTx_HitCount++;
  return CddSbc_SpiTx_ulReturn;
}

//-----------------------------------------------------------------------------
/// \brief CddTps92520_SpiRx
///
/// \descr Stub function created to simulate the behaviour of CddTps92520_SpiRx
///
/// \param  unId - decvice Id
///         ulData - data to be transfered
///
/// \return -
//-----------------------------------------------------------------------------
void CddTps92520_SpiRx(uint16 unId, uint32 ulData)
{
  CddTps92520_SpiRx_unId = unId;
  CddTps92520_SpiRx_ulData[unId] = ulData;
  CddTps92520_SpiRx_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief CddTps92520_SpiTx
///
/// \descr Stub function created to simulate the behaviour of CddTps92520_SpiTx
///
/// \param  unId - decvice Id
///
/// \return data to be transfered
//-----------------------------------------------------------------------------
uint32 CddTps92520_SpiTx(uint16 unId)
{
  CddTps92520_SpiTx_unId = unId;
  CddTps92520_SpiTx_HitCount++;
  return CddTps92520_SpiTx_ulReturn[unId];
}

//-----------------------------------------------------------------------------
/// \brief CddNcv78702_SpiRx
///
/// \descr Stub function created to simulate the behaviour of CddNcv78702_SpiRx
///
/// \param  unId - decvice Id
///         ulData - data to be transfered
///
/// \return -
//-----------------------------------------------------------------------------
void CddNcv78702_SpiRx(uint16 unId, uint32 ulData)
{
  CddNcv78702_SpiRx_unId = unId;
  CddNcv78702_SpiRx_ulData = ulData;
  CddNcv78702_SpiRx_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief CddStp_SpiTx
///
/// \descr Stub function created to simulate the behaviour of CddStp_SpiTx
///
/// \param  unId - decvice Id
///
/// \return data to be transfered
//-----------------------------------------------------------------------------
uint32 CddStp_SpiTx(uint16 unId)
{
  CddStp_SpiTx_unId = unId;
  CddStp_SpiTx_HitCount++;
  return CddStp_SpiTx_ulReturn;
}

//-----------------------------------------------------------------------------
/// \brief CddStp_SpiRx
///
/// \descr Stub function created to simulate the behaviour of CddStp_SpiRx
///
/// \param  unId - decvice Id
///         ulData - data to be transfered
///
/// \return -
//-----------------------------------------------------------------------------
void CddStp_SpiRx(uint16 unId, uint32 ulData)
{
  CddStp_SpiRx_ulData = ulData;
  CddStp_SpiRx_unId = unId;
  CddStp_SpiRx_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief CddTle94x1_SpiTx
///
/// \descr Stub function created to simulate the behaviour of CddTle94x1_SpiTx
///
/// \param  unId - decvice Id
///
/// \return data to be transfered
//-----------------------------------------------------------------------------
uint32 CddTle94x1_SpiTx(uint16 unId)
{
  CddTle94x1_SpiTx_unId = unId;
  CddTle94x1_SpiTx_HitCount++;
  return CddTle94x1_SpiTx_ulReturn[unId];
}

//-----------------------------------------------------------------------------
/// \brief CddTle94x1_SpiRx
///
/// \descr Stub function created to simulate the behaviour of CddTle94x1_SpiRx
///
/// \param  unId - decvice Id
///
/// \return data to be transfered
//-----------------------------------------------------------------------------
void CddTle94x1_SpiRx(uint16 unId, uint32 ulData)
{
  CddTle94x1_SpiRx_unId = unId;
  CddTle94x1_SpiRx_ulData = ulData;
  CddTle94x1_SpiRx_HitCount++;
}


//-----------------------------------------------------------------------------
/// \brief CddNcv78702_SpiTx
///
/// \descr Stub function created to simulate the behaviour of CddNcv78702_SpiTx
///
/// \param  unId - decvice Id
///
/// \return data to be transfered
//-----------------------------------------------------------------------------
uint32 CddNcv78702_SpiTx(uint16 unId)
{
  CddNcv78702_SpiTx_unId = unId;
  CddNcv78702_SpiTx_HitCount++;
  return CddNcv78702_SpiTx_ulReturn;
}

//-----------------------------------------------------------------------------
/// \brief CddDma_IsJobCompleted
///
/// \descr Stub function created to simulate the behaviour of CddDma_IsJobCompleted
///
/// \param  eDmaChannelName - DMA channel Id
///
/// \return if DMA job is done
//-----------------------------------------------------------------------------
boolean CddDma_IsJobCompleted(CddDma_DynConfig_DmaChannelName_EnumType eDmaChannelName)
{
  CddDma_IsJobCompleted_eDmaChannelName = eDmaChannelName;
  CddDma_IsJobCompleted_HitCount++;

  return CddDma_IsJobCompleted_boReturn;
}

//-----------------------------------------------------------------------------
/// \brief CddDma_StartJob
///
/// \descr Stub function created to simulate the behaviour of CddDma_StartJob
///
/// \param  eDmaChannelName - DMA channel Id
///         psParameter     - parameter with repetitions and addresses
///         fpCallback      - function pointer for a callback
///
/// \return 
//-----------------------------------------------------------------------------
void CddDma_StartJob(CddDma_DynConfig_DmaChannelName_EnumType eDmaChannelName, CONST_AL tsCddDma_Parameter* psParameter, CONST_AL CddDma_tfpCallback fpCallback)
{
  CddDma_StartJob_eDmaChannelName = eDmaChannelName;
  CddDma_StartJob_psParameter = psParameter;
  CddDma_StartJob_fpCallback = fpCallback;
  CddDma_StartJob_HitCount++;
}


//-----------------------------------------------------------------------------
/// \brief    CddTps92520_SpiGetConfig
///
/// \descr    Stub funciton used to simulate the behaviour of CddTps92520_SpiGetConfig
///
/// \param  punData
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CddTps92520_SpiGetConfig(uint16* punData)
{
  *punData = CddTps92520_SpiGetConfig_unData;
  CddTps92520_SpiGetConfig_HitCount++;

  return CddTps92520_SpiGetConfig_boReturn;
}


FUNC(Std_ReturnType, RTE_CODE) Rte_Call_ppCodMEftData0_GetData(P2VAR(tieEftDataPtr, AUTOMATIC, RTE_APPL_DATA) ppEftData)
{
  *ppEftData = Stub_psEftAddr;
  return E_OK;
}


FUNC(Std_ReturnType, RTE_CODE) Rte_Read_ppCodMEftCrcStatus0_sVal(P2VAR(tieDataStatus, AUTOMATIC, RTE_APPL_DATA)Data)
{
  *Data = Rte_Read_ctacCddSpi_ppCodMEftCrcStatus0_sVal_eData;
  return Rte_Read_ctacCddSpi_ppCodMEftCrcStatus0_sVal_ucReturn;
}

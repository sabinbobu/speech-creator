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
#include <AL_Helper.h>
#include <CddSpi_Types.h>
#include <CddDma.h>

//=============================================================================
// Typedef
//=============================================================================

//=============================================================================
// Stub function declarations
//=============================================================================
void                                            CddSbc_SpiRx(uint16 unId, uint32 ulData);
uint32                                          CddSbc_SpiTx(uint16 unId);
void                                            CddTps92520_SpiRx(uint16 unId, uint32 ulData);
uint32                                          CddTps92520_SpiTx(uint16 unId);
void                                            CddNcv78702_SpiRx(uint16 unId, uint32 ulData);
uint32                                          CddStp_SpiTx(uint16 unId);
void                                            CddStp_SpiRx(uint16 unId, uint32 ulData);
uint32                                          CddTle94x1_SpiTx(uint16 unId);
void                                            CddTle94x1_SpiRx(uint16 unId, uint32 ulData);
uint32                                          CddNcv78702_SpiTx(uint16 unId);
boolean                                         CddDma_IsJobCompleted(CddDma_DynConfig_DmaChannelName_EnumType eDmaChannelName);
void                                            CddDma_StartJob(CddDma_DynConfig_DmaChannelName_EnumType eDmaChannelName, CONST_AL tsCddDma_Parameter* psParameter, CONST_AL CddDma_tfpCallback fpCallback);
boolean                                         CddTps92520_SpiGetConfig(uint16* punData);
FUNC(Std_ReturnType, RTE_CODE)                  Rte_Call_ppCodMEftData0_GetData(P2VAR(tieEftDataPtr, AUTOMATIC, RTE_APPL_DATA) ppEftData);
FUNC(Std_ReturnType, RTE_CODE)                  Rte_Read_ppCodMEftCrcStatus0_sVal(P2VAR(tieDataStatus, AUTOMATIC, RTE_APPL_DATA)Data);


//=============================================================================
// Stub function parameter stubs
//=============================================================================
extern uint16                                   CddSbc_SpiRx_unId;
extern uint32                                   CddSbc_SpiRx_ulData;
extern uint16                                   CddSbc_SpiTx_unId;
extern uint16                                   CddTps92520_SpiRx_unId;
extern uint16                                   CddTps92520_SpiTx_unId;
extern uint16                                   CddNcv78702_SpiRx_unId;
extern uint32                                   CddNcv78702_SpiRx_ulData;
extern uint16                                   CddNcv78702_SpiTx_unId;
extern uint32                                   CddStp_SpiRx_unId;
extern uint32                                   CddTle94x1_SpiTx_unId;
extern uint32                                   CddTle94x1_SpiRx_unId;
extern uint32                                   CddStp_SpiRx_ulData;
extern uint32                                   CddTle94x1_SpiRx_ulData;
extern uint32                                   CddTle94x1CddStp_SpiRx_ulData;
extern uint32                                   CddStp_SpiTx_unId;
extern CddDma_DynConfig_DmaChannelName_EnumType CddDma_IsJobCompleted_eDmaChannelName;
extern CddDma_DynConfig_DmaChannelName_EnumType CddDma_StartJob_eDmaChannelName;
extern tsCddDma_Parameter*                      CddDma_StartJob_psParameter;
extern CddDma_tfpCallback                       CddDma_StartJob_fpCallback;

extern tieDataStatus                            Rte_Read_ctacCddSpi_ppCodMEftCrcStatus0_sVal_eData;
extern tieEftData                               Stub_sEftInitVal;
extern tieEftDataPtr                            Stub_psEftAddr;
extern uint16                                   CddTps92520_SpiGetConfig_unData;

//=============================================================================
// Stub function returned value stubs
//=============================================================================
extern uint32                                   CddSbc_SpiTx_ulReturn;
extern uint32                                   CddTps92520_SpiRx_ulData[7];
extern uint32                                   CddTps92520_SpiTx_ulReturn[7];
extern uint32                                   CddTle94x1_SpiTx_ulReturn[7];
extern uint32                                   CddNcv78702_SpiTx_ulReturn;
extern uint32                                   CddStp_SpiTx_ulReturn;
extern boolean                                  CddDma_IsJobCompleted_boReturn;
extern Std_ReturnType                           Rte_Read_ctacCddSpi_ppCodMEftCrcStatus0_sVal_ucReturn;
extern boolean                                  CddTps92520_SpiGetConfig_boReturn;

//=============================================================================
// Stub function hit count variables
//=============================================================================
extern uint32                                   CddSbc_SpiRx_HitCount;
extern uint32                                   CddSbc_SpiTx_HitCount;
extern uint32                                   CddTps92520_SpiRx_HitCount;
extern uint32                                   CddTps92520_SpiTx_HitCount;
extern uint32                                   CddNcv78702_SpiRx_HitCount;
extern uint32                                   CddNcv78702_SpiTx_HitCount;
extern uint32                                   CddStp_SpiRx_HitCount;
extern uint32                                   CddTle94x1_SpiTx_HitCount;
extern uint32                                   CddTle94x1_SpiRx_HitCount;
extern uint32                                   CddStp_SpiTx_HitCount;
extern uint32                                   CddDma_IsJobCompleted_HitCount;
extern uint32                                   CddDma_StartJob_HitCount;
extern uint32                                   CddTps92520_SpiGetConfig_HitCount;

#endif // TEST_STUBS_2023_08_25_H_

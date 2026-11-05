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
/// \file  Test.c
///
/// \brief  Unit Test Cases for CddDma
///
/// \author  Bodian Bianca Dorina (F31199D)
///          mailTo:bianca-dorina.bodian[at]marelli.com
///
//-----------------------------------------------------------------------------

//==============================================================================
//  Files covered by this module unit test:
//            - CddDma.c
//==============================================================================

//=============================================================================
// Includes
//=============================================================================

// Standard unit test header
#include <ALUnitTest_UserInterface.h>
#include <stdio.h>
#include <string.h>

// Stub headers
#include "Test_Stubs.h"

// Headers of the unit test Module
#include "Test.h"


//=============================================================================
// Test Cases
//=============================================================================

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDma_IsJobCompleted_TestCase1
///
/// \Test Case Description
///        - Test subject: Test if Dma Transfer Job is marked as completed for 
///                        a given  DMA channel based on HW register check
///
///       - Test Design Technique:  - Requirement based test
///                                 - ET (Exploratory Testing) 
///
/// \FuSa Relevant:   ASIL-B
///
/// - Preconditions:
///  All related DMA-HW registers which are used must be emulated by the Test Case.
/// \input  pointer to hardware registers initialized;
/// \input  CddDma_IsJobCompleted_eDmaChannelName = CDDUART_DMA_RX_CHANNEL;
/// \input  CddDma_psRegister->Reg_TCDn[CDDUART_DMA_RX_CHANNEL].tuTCDn_CSR.sBit.u1DONE = 1U;
///
/// - Expectations:
///
/// \output CddDma_psRegister->Reg_TCDn[CDDUART_DMA_RX_CHANNEL].tuTCDn_CSR.sBit.u1DONE = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CddDma_IsJobCompleted_TestCase1(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  CddDma_psRegister                         = &Mt_CddDma_Dma_Register;
  CddDma_IsJobCompleted_eDmaChannelName     = CDDUART_DMA_RX_CHANNEL;
  CddDma_psRegister->Reg_TCDn[CDDUART_DMA_RX_CHANNEL].tuTCDn_CSR.sBit.u1DONE = 1U;

  //Step 3) Call FUT
  CddDma_IsJobCompleted_boRetVal    = CddDma_IsJobCompleted(CddDma_IsJobCompleted_eDmaChannelName);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddDma_IsJobCompleted_boRetVal, TRUE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDma_IsJobCompleted_TestCase2
///
/// \Test Case Description
///        - Test subject: Test if Dma Transfer Job is marked as not completed 
///                        for a given  DMA channel based on HW register check
///
///       - Test Design Technique:  - Requirement based test
///                                 - ET (Exploratory Testing) 
///
/// \FuSa Relevant:   ASIL-B
///
/// - Preconditions:
///
///  All related DMA-HW registers which are used must be emulated by the Test Case.
/// \input  pointer to hardware registers initialized;
/// \input  CddDma_IsJobCompleted_eDmaChannelName = CDDUART_DMA_RX_CHANNEL;
/// \input  CddDma_psRegister->Reg_TCDn[CDDUART_DMA_RX_CHANNEL].tuTCDn_CSR.sBit.u1DONE = 0U;
///
/// - Expectations:
///
/// \output CddDma_psRegister->Reg_TCDn[CDDUART_DMA_RX_CHANNEL].tuTCDn_CSR.sBit.u1DONE = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CddDma_IsJobCompleted_TestCase2(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  CddDma_psRegister                           = &Mt_CddDma_Dma_Register;
  CddDma_IsJobCompleted_eDmaChannelName       = CDDUART_DMA_RX_CHANNEL;
  CddDma_psRegister->Reg_TCDn[CDDUART_DMA_RX_CHANNEL].tuTCDn_CSR.sBit.u1DONE = 0U;

  //Step 3) Call FUT
  CddDma_IsJobCompleted_boRetVal = CddDma_IsJobCompleted(CddDma_IsJobCompleted_eDmaChannelName);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddDma_IsJobCompleted_boRetVal, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDma_IsJobCompleted
///
/// \Test Case Description
///        - Test subject: Check the status for a DMA transfer performed by a
///                        specific channel (completed/ in progress)
///
///       - Test Design Technique:  - Requirement based test
///                                 - ET (Exploratory Testing) 
///
/// \FuSa Relevant:ASIL-B
///
//-----------------------------------------------------------------------------
void Mt_CddDma_IsJobCompleted(void)
{
  Mt_CddDma_IsJobCompleted_TestCase1();
  Mt_CddDma_IsJobCompleted_TestCase2();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDma_GenerateTriggerSignal
///
/// \Test Case Description
///        - Test subject: Test if this function creates a software trigger 
///                        for the chosen DMA Channel
///
/// - Preconditions:
///
///  All related DMA-HW registers which are used must be emulated by the Test Case.
/// \input  pointer to hardware registers initialized;
/// \input  CddDma_GenerateTriggerSignal_eDmaChannelName  = CDDUART_DMA_RX_CHANNEL
///
/// - Expectations:
///
/// \output CddDma_psRegister->Reg_SSRT.ucData = CDDUART_DMA_RX_CHANNEL
///
//-----------------------------------------------------------------------------
void Mt_CddDma_GenerateTriggerSignal(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  CddDma_psRegister                             = &Mt_CddDma_Dma_Register;
  CddDma_GenerateTriggerSignal_eDmaChannelName  = CDDUART_DMA_RX_CHANNEL;

  //Step 3) Call FUT
  CddDma_GenerateTriggerSignal(CddDma_GenerateTriggerSignal_eDmaChannelName);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_SSRT.ucData, CDDUART_DMA_RX_CHANNEL, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDma_EnableHwTrigger_TestCase1
///
/// \Test Case Description
///        - Test subject: Test if the HW Trigger is disabled
///
/// - Preconditions:
///
///  All related DMA-HW registers which are used must be emulated by the Test Case.
/// \input  pointer to hardware registers initialized;
/// \input  CddDma_EnableHwTrigger_eDmaChannelName  = CDDUART_DMA_RX_CHANNEL
/// \input  CddDma_EnableHwTrigger_boEnabled        = FALSE
///
/// - Expectations:
///
/// \output CddDma_psRegister->Reg_CERQ.ucData = CDDUART_DMA_RX_CHANNEL;
///
//-----------------------------------------------------------------------------
void Mt_CddDma_EnableHwTrigger_TestCase1(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  CddDma_psRegister                       = &Mt_CddDma_Dma_Register;
  CddDma_EnableHwTrigger_eDmaChannelName  = CDDUART_DMA_RX_CHANNEL;
  CddDma_EnableHwTrigger_boEnabled        = FALSE;

  //Step 3) Call FUT
  CddDma_EnableHwTrigger(CddDma_EnableHwTrigger_eDmaChannelName, CddDma_EnableHwTrigger_boEnabled);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_CERQ.ucData, CDDUART_DMA_RX_CHANNEL, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDma_EnableHwTrigger_TestCase2
///
/// \Test Case Description
///        - Test subject: Test if the HW Trigger is enabled
///
/// - Preconditions:
///
///  All related DMA-HW registers which are used must be emulated by the Test Case.
/// \input  pointer to hardware registers initialized;
/// \input  CddDma_EnableHwTrigger_eDmaChannelName  = CDDUART_DMA_RX_CHANNEL
/// \input  CddDma_EnableHwTrigger_boEnabled        = TRUE
///
/// - Expectations:
///
/// \output CddDma_psRegister->Reg_SERQ.ucData = CDDUART_DMA_RX_CHANNEL;
///
//-----------------------------------------------------------------------------
void Mt_CddDma_EnableHwTrigger_TestCase2(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  CddDma_psRegister                       = &Mt_CddDma_Dma_Register;
  CddDma_EnableHwTrigger_eDmaChannelName  = CDDUART_DMA_RX_CHANNEL;
  CddDma_EnableHwTrigger_boEnabled        = TRUE;

  //Step 3) Call FUT
  CddDma_EnableHwTrigger(CddDma_EnableHwTrigger_eDmaChannelName, CddDma_EnableHwTrigger_boEnabled);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_SERQ.ucData, CDDUART_DMA_RX_CHANNEL, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDma_EnableHwTrigger
///
/// \Test Case Description
///        - Test subject: Check the activation of hardware triggering on 
///                         a specific DMA channel
///
//-----------------------------------------------------------------------------
void Mt_CddDma_EnableHwTrigger(void)
{
  Mt_CddDma_EnableHwTrigger_TestCase1();
  Mt_CddDma_EnableHwTrigger_TestCase2();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDma_Init_TestCase1
///
/// \Test Case Description
///        - Test subject: Test if the right register is updated with the right value for DMA channel
///                        configured as: (source/destination minor loop offset enable & transfer size <= 32b)
///         virtualDmaName   | irqChannel      | trigger              | sourceAddressOperation  | targetAddressOperation  | transferSize          | loopMode
///         LPSPI1_RX        | DMA_IRQ_INTDMA3 | CDDDMA_REQ_LPSPI1_RX | DMA_ADDRESS_FIXED       | DMA_ADDRESS_INCREMENTED | DMA_TRANSFER_SIZE_16  | DMA_LOOP_MODE_NONE
///
///
///       - Test Design Technique:  - Requirement based test
///                                 - ET (Exploratory Testing) 
///
/// \FuSa Relevant:   ASIL-B
///
/// - Preconditions:
///
///  All related DMA-HW registers which are used must be emulated by the Test Case.
/// \input  pointer to hardware registers initialized;
/// \input  TCD (Transfer Control Descriptor) structure cleared
/// \input  Fixed-priority channel arbitration enabled for each DMA channel
/// \input  Mt_CddDma_TransferSize        = CddDma_cast__DynConfig_Triggers[LPSPI1_RX].eTransferSize;
/// \input  Mt_CddDma_VirtualDmaChannel   = LPSPI1_RX;
/// \input  Mt_CddDma_TransferSizeLimited = Mt_CddDma_TransferSize;
///
/// - Expectations:
///
/// \output CddDma_DmaMux_psRegister->Reg_CHCFGn[Mt_CddDma_VirtualDmaChannel].sBit.u6SOURCE = CDDDMA_REQ_LPSPI1_RX
/// \output CddDma_DmaMux_psRegister->Reg_CHCFGn[Mt_CddDma_VirtualDmaChannel].sBit.u1ENBL = 1u
/// \output CddDma_psRegister->Reg_TCDn[Mt_CddDma_VirtualDmaChannel].tuTCDn_ATTR.sBit.u3SSIZE = Mt_CddDma_TransferSizeLimited
/// \output CddDma_psRegister->Reg_TCDn[Mt_CddDma_VirtualDmaChannel].tuTCDn_ATTR.sBit.u3DSIZE = Mt_CddDma_TransferSizeLimited
/// \output CddDma_psRegister->Reg_TCDn[Mt_CddDma_VirtualDmaChannel].tuTCDn_SOFF.unData = 0u
/// \output CddDma_psRegister->Reg_TCDn[Mt_CddDma_VirtualDmaChannel].tuTCDn_DOFF.unData = 2u
/// \output CddDma_psRegister->Reg_TCDn[Mt_CddDma_VirtualDmaChannel].tuTCDn_NBYTES.tuMLOFFNO.sBit.u1SMLOE = 0u
/// \output CddDma_psRegister->Reg_TCDn[Mt_CddDma_VirtualDmaChannel].tuTCDn_NBYTES.tuMLOFFNO.sBit.u1DMLOE = 0u
/// \output CddDma_psRegister->Reg_TCDn[Mt_CddDma_VirtualDmaChannel].tuTCDn_NBYTES.tuMLOFFNO.sBit.u30NBYTES = 2u
/// \output CddDma_psRegister->Reg_SERQ.ucData = UNIT_TEST_CHANNEL
/// \output CddDma_psRegister->Reg_TCDn[Mt_CddDma_VirtualDmaChannel].tuTCDn_CSR.sBit.u1DREQ = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddDma_Init_TestCase1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  CddDma_DmaMux_psRegister = &Mt_CddDma_DmaMux_Register;
  CddDma_psRegister        = &Mt_CddDma_Dma_Register;

  CddDma_psRegister->Reg_CR.ulData    = 0u;
  CddDma_psRegister->Reg_ES.ulData    = 0u;
  CddDma_psRegister->Reg_ERQ.ulData   = 0u;
  CddDma_psRegister->Reg_EEI.ulData   = 0u;
  CddDma_psRegister->Reg_CEEI.ucData  = 0u;
  CddDma_psRegister->Reg_SEEI.ucData  = 0u;
  CddDma_psRegister->Reg_CERQ.ucData  = 0u;
  CddDma_psRegister->Reg_SERQ.ucData  = 0u;
  CddDma_psRegister->Reg_CDNE.ucData  = 0u;
  CddDma_psRegister->Reg_SSRT.ucData  = 0u;
  CddDma_psRegister->Reg_CERR.ucData  = 0u;
  CddDma_psRegister->Reg_CINT.ucData  = 0u;
  CddDma_psRegister->Reg_INT.ulData   = 0u;
  CddDma_psRegister->Reg_ERR.ulData   = 0u;
  CddDma_psRegister->Reg_HRS.ulData   = 0u;
  CddDma_psRegister->Reg_EARS.ulData  = 0u;


  for (uint8 ucChnlIdx = 0; ucChnlIdx < FEATURE_DMAMUX_CHANNELS; ucChnlIdx++)
  {
    CddDma_DmaMux_psRegister->Reg_CHCFGn[ucChnlIdx].ucData  = 0u;
    CddDma_psRegister->Reg_DCHPRIm[ucChnlIdx].ucData        = 0u;
  }

  for (uint8 ucTCDIdx = 0; ucTCDIdx < VIRTUAL_TRIGGER_NAMES_COUNT; ucTCDIdx++)
  {
    CddDma_psRegister->Reg_TCDn[ucTCDIdx].tuTCDn_SADDR.ulData             = 0u;
    CddDma_psRegister->Reg_TCDn[ucTCDIdx].tuTCDn_SOFF.unData              = 0u;
    CddDma_psRegister->Reg_TCDn[ucTCDIdx].tuTCDn_ATTR.unData              = 0u;
    CddDma_psRegister->Reg_TCDn[ucTCDIdx].tuTCDn_NBYTES.tuMLNO.ulData     = 0u;
    CddDma_psRegister->Reg_TCDn[ucTCDIdx].tuTCDn_NBYTES.tuMLOFFNO.ulData  = 0u;
    CddDma_psRegister->Reg_TCDn[ucTCDIdx].tuTCDn_NBYTES.tuMLOFFYES.ulData = 0u;
    CddDma_psRegister->Reg_TCDn[ucTCDIdx].tuTCDn_SLAST.ulData             = 0u;
    CddDma_psRegister->Reg_TCDn[ucTCDIdx].tuTCDn_DADDR.ulData             = 0u;
    CddDma_psRegister->Reg_TCDn[ucTCDIdx].tuTCDn_DOFF.unData              = 0u;
    CddDma_psRegister->Reg_TCDn[ucTCDIdx].tuTCDn_CITER.tuELINKNO.unData   = 0u;
    CddDma_psRegister->Reg_TCDn[ucTCDIdx].tuTCDn_CITER.tuELINKYES.unData  = 0u;
    CddDma_psRegister->Reg_TCDn[ucTCDIdx].tuTCDn_DLASTSGA.ulData          = 0u;
    CddDma_psRegister->Reg_TCDn[ucTCDIdx].tuTCDn_CSR.unData               = 0u;
    CddDma_psRegister->Reg_TCDn[ucTCDIdx].tuTCDn_BITER.tuELINKNO.unData   = 0u;
    CddDma_psRegister->Reg_TCDn[ucTCDIdx].tuTCDn_BITER.tuELINKYES.unData  = 0u;
  }
  
  //Step 2) Assign Input values
  uint8   Mt_CddDma_VirtualDmaChannel   = LPSPI1_RX;
  uint8   Mt_CddDma_TransferSize        = CddDma_cast__DynConfig_Triggers[Mt_CddDma_VirtualDmaChannel].eTransferSize;
  uint8   Mt_CddDma_TransferSizeLimited = Mt_CddDma_TransferSize;

  //Step 3) Call FUT
  CddDma_Init();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddDma_DmaMux_psRegister->Reg_CHCFGn[Mt_CddDma_VirtualDmaChannel].sBit.u6SOURCE, CDDDMA_REQ_LPSPI1_RX, == );
  AL_UNITTEST_CHECK(CddDma_DmaMux_psRegister->Reg_CHCFGn[Mt_CddDma_VirtualDmaChannel].sBit.u1ENBL, 1u, == );

  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[Mt_CddDma_VirtualDmaChannel].tuTCDn_ATTR.sBit.u3SSIZE, Mt_CddDma_TransferSizeLimited, == );
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[Mt_CddDma_VirtualDmaChannel].tuTCDn_ATTR.sBit.u3DSIZE, Mt_CddDma_TransferSizeLimited, == );
  
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[Mt_CddDma_VirtualDmaChannel].tuTCDn_SOFF.unData, 0u, == );
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[Mt_CddDma_VirtualDmaChannel].tuTCDn_DOFF.unData, 2u, == );

  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[Mt_CddDma_VirtualDmaChannel].tuTCDn_NBYTES.tuMLOFFNO.sBit.u1SMLOE,    0u, == );
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[Mt_CddDma_VirtualDmaChannel].tuTCDn_NBYTES.tuMLOFFNO.sBit.u1DMLOE,    0u, == );
  
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[Mt_CddDma_VirtualDmaChannel].tuTCDn_NBYTES.tuMLOFFNO.sBit.u30NBYTES,  2u, == );
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_SERQ.ucData, UNIT_TEST_CHANNEL, == );
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[Mt_CddDma_VirtualDmaChannel].tuTCDn_CSR.sBit.u1DREQ, 1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDma_Init_TestCase2
///
/// \Test Case Description
///        - Test subject: Test if the right register is updated with the right value for DMA channel
///                        configured as:   (source/destination minor loop offset enable & transfer size > 32b)
///         virtualDmaName      | irqChannel            | trigger                           | sourceAddressOperation  | targetAddressOperation  | transferSize            | loopMode
///         UNIT_TEST_CHANNEL   | CDDDMA_NotAvail_IRQn  | CDDDMA_REQ_DMAMUX_ALWAYS_ENABLED1 | DMA_ADDRESS_FIXED       | DMA_ADDRESS_FIXED       | DMA_TRANSFER_SIZE_2x32  | DMA_LOOP_MODE_ENDLESS
///
///
///       - Test Design Technique:  - Requirement based test
///                                 - ET (Exploratory Testing) 
///
/// \FuSa Relevant:   ASIL-B
///
/// - Preconditions:
///
///  All related DMA-HW registers which are used must be emulated by the Test Case.
/// \input  pointer to hardware registers initialized;
/// \input  TCD (Transfer Control Descriptor) structure cleared
/// \input  Fixed-priority channel arbitration enabled for each DMA channel
/// \input  Mt_CddDma_TransferSize        = CddDma_cast__DynConfig_Triggers[UNIT_TEST_CHANNEL].eTransferSize;
/// \input  Mt_CddDma_VirtualDmaChannel   = UNIT_TEST_CHANNEL;
/// \input  Mt_CddDma_TransferSizeLimited = DMA_TRANSFER_SIZE_32;
///
/// - Expectations:
///
/// \output CddDma_DmaMux_psRegister->Reg_CHCFGn[Mt_CddDma_VirtualDmaChannel].sBit.u6SOURCE = CDDDMA_REQ_DMAMUX_ALWAYS_ENABLED1
/// \output CddDma_DmaMux_psRegister->Reg_CHCFGn[Mt_CddDma_VirtualDmaChannel].sBit.u1ENBL = 1u
/// \output CddDma_psRegister->Reg_TCDn[Mt_CddDma_VirtualDmaChannel].tuTCDn_ATTR.sBit.u3SSIZE = Mt_CddDma_TransferSizeLimited
/// \output CddDma_psRegister->Reg_TCDn[Mt_CddDma_VirtualDmaChannel].tuTCDn_ATTR.sBit.u3DSIZE = Mt_CddDma_TransferSizeLimited
/// \output CddDma_psRegister->Reg_TCDn[Mt_CddDma_VirtualDmaChannel].tuTCDn_SOFF.unData = 4u
/// \output CddDma_psRegister->Reg_TCDn[Mt_CddDma_VirtualDmaChannel].tuTCDn_DOFF.unData = 4u
/// \output CddDma_psRegister->Reg_TCDn[Mt_CddDma_VirtualDmaChannel].tuTCDn_NBYTES.tuMLOFFNO.sBit.u1SMLOE = 1u
/// \output CddDma_psRegister->Reg_TCDn[Mt_CddDma_VirtualDmaChannel].tuTCDn_NBYTES.tuMLOFFNO.sBit.u1DMLOE = 1u
/// \output CddDma_psRegister->Reg_TCDn[Mt_CddDma_VirtualDmaChannel].tuTCDn_NBYTES.tuMLOFFYES.sBit.u10NBYTES = 8u
/// \output CddDma_psRegister->Reg_TCDn[Mt_CddDma_VirtualDmaChannel].tuTCDn_NBYTES.tuMLOFFYES.sBit.u20MLOFF  = Mt_CddDma_MLOFF
/// \output CddDma_psRegister->Reg_SERQ.ucData = UNIT_TEST_CHANNEL
/// \output CddDma_psRegister->Reg_TCDn[Mt_CddDma_VirtualDmaChannel].tuTCDn_CSR.sBit.u1DREQ = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddDma_Init_TestCase2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  CddDma_DmaMux_psRegister = &Mt_CddDma_DmaMux_Register;
  CddDma_psRegister        = &Mt_CddDma_Dma_Register;

  CddDma_psRegister->Reg_CR.ulData    = 0u;
  CddDma_psRegister->Reg_ES.ulData    = 0u;
  CddDma_psRegister->Reg_ERQ.ulData   = 0u;
  CddDma_psRegister->Reg_EEI.ulData   = 0u;
  CddDma_psRegister->Reg_CEEI.ucData  = 0u;
  CddDma_psRegister->Reg_SEEI.ucData  = 0u;
  CddDma_psRegister->Reg_CERQ.ucData  = 0u;
  CddDma_psRegister->Reg_SERQ.ucData  = 0u;
  CddDma_psRegister->Reg_CDNE.ucData  = 0u;
  CddDma_psRegister->Reg_SSRT.ucData  = 0u;
  CddDma_psRegister->Reg_CERR.ucData  = 0u;
  CddDma_psRegister->Reg_CINT.ucData  = 0u;
  CddDma_psRegister->Reg_INT.ulData   = 0u;
  CddDma_psRegister->Reg_ERR.ulData   = 0u;
  CddDma_psRegister->Reg_HRS.ulData   = 0u;
  CddDma_psRegister->Reg_EARS.ulData  = 0u;


  for (uint8 ucChnlIdx = 0; ucChnlIdx < FEATURE_DMAMUX_CHANNELS; ucChnlIdx++)
  {
    CddDma_DmaMux_psRegister->Reg_CHCFGn[ucChnlIdx].ucData  = 0u;
    CddDma_psRegister->Reg_DCHPRIm[ucChnlIdx].ucData        = 0u;
  }

  for (uint8 ucTCDIdx = 0; ucTCDIdx < VIRTUAL_TRIGGER_NAMES_COUNT; ucTCDIdx++)
  {
    CddDma_psRegister->Reg_TCDn[ucTCDIdx].tuTCDn_SADDR.ulData             = 0u;
    CddDma_psRegister->Reg_TCDn[ucTCDIdx].tuTCDn_SOFF.unData              = 0u;
    CddDma_psRegister->Reg_TCDn[ucTCDIdx].tuTCDn_ATTR.unData              = 0u;
    CddDma_psRegister->Reg_TCDn[ucTCDIdx].tuTCDn_NBYTES.tuMLNO.ulData     = 0u;
    CddDma_psRegister->Reg_TCDn[ucTCDIdx].tuTCDn_NBYTES.tuMLOFFNO.ulData  = 0u;
    CddDma_psRegister->Reg_TCDn[ucTCDIdx].tuTCDn_NBYTES.tuMLOFFYES.ulData = 0u;
    CddDma_psRegister->Reg_TCDn[ucTCDIdx].tuTCDn_SLAST.ulData             = 0u;
    CddDma_psRegister->Reg_TCDn[ucTCDIdx].tuTCDn_DADDR.ulData             = 0u;
    CddDma_psRegister->Reg_TCDn[ucTCDIdx].tuTCDn_DOFF.unData              = 0u;
    CddDma_psRegister->Reg_TCDn[ucTCDIdx].tuTCDn_CITER.tuELINKNO.unData   = 0u;
    CddDma_psRegister->Reg_TCDn[ucTCDIdx].tuTCDn_CITER.tuELINKYES.unData  = 0u;
    CddDma_psRegister->Reg_TCDn[ucTCDIdx].tuTCDn_DLASTSGA.ulData          = 0u;
    CddDma_psRegister->Reg_TCDn[ucTCDIdx].tuTCDn_CSR.unData               = 0u;
    CddDma_psRegister->Reg_TCDn[ucTCDIdx].tuTCDn_BITER.tuELINKNO.unData   = 0u;
    CddDma_psRegister->Reg_TCDn[ucTCDIdx].tuTCDn_BITER.tuELINKYES.unData  = 0u;
  }

  //Step 2) Assign Input values
  uint8   Mt_CddDma_VirtualDmaChannel   = UNIT_TEST_CHANNEL;
  uint8   Mt_CddDma_TransferSize        = CddDma_cast__DynConfig_Triggers[Mt_CddDma_VirtualDmaChannel].eTransferSize;
  uint8   Mt_CddDma_TransferSizeLimited = DMA_TRANSFER_SIZE_32;
  uint32  Mt_CddDma_MLOFF = (~(1<< Mt_CddDma_TransferSize) + 1) & 0x000FFFFF;

  //Step 3) Call FUT

  CddDma_Init();

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(CddDma_DmaMux_psRegister->Reg_CHCFGn[Mt_CddDma_VirtualDmaChannel].sBit.u6SOURCE, CDDDMA_REQ_DMAMUX_ALWAYS_ENABLED1, == );
  AL_UNITTEST_CHECK(CddDma_DmaMux_psRegister->Reg_CHCFGn[Mt_CddDma_VirtualDmaChannel].sBit.u1ENBL, 1u, == );

  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[Mt_CddDma_VirtualDmaChannel].tuTCDn_ATTR.sBit.u3SSIZE, Mt_CddDma_TransferSizeLimited, == );
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[Mt_CddDma_VirtualDmaChannel].tuTCDn_ATTR.sBit.u3DSIZE, Mt_CddDma_TransferSizeLimited, == );
  
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[Mt_CddDma_VirtualDmaChannel].tuTCDn_SOFF.unData, 4u, == );
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[Mt_CddDma_VirtualDmaChannel].tuTCDn_DOFF.unData, 4u, == );

  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[Mt_CddDma_VirtualDmaChannel].tuTCDn_NBYTES.tuMLOFFNO.sBit.u1SMLOE,    1u, == );
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[Mt_CddDma_VirtualDmaChannel].tuTCDn_NBYTES.tuMLOFFNO.sBit.u1DMLOE,    1u, == );
  
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[Mt_CddDma_VirtualDmaChannel].tuTCDn_NBYTES.tuMLOFFYES.sBit.u10NBYTES, 8u, == );
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[Mt_CddDma_VirtualDmaChannel].tuTCDn_NBYTES.tuMLOFFYES.sBit.u20MLOFF,  Mt_CddDma_MLOFF, == );
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_SERQ.ucData, UNIT_TEST_CHANNEL, == );
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[Mt_CddDma_VirtualDmaChannel].tuTCDn_CSR.sBit.u1DREQ, 0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDma_Init
///
/// \Test Case Description
///        - Test subject: Perform the initialization of DMA peripheric
///                        based on a channel specific configuration
///
///       - Test Design Technique:  - Requirement based test
///                                 - ET (Exploratory Testing) 
///
/// \FuSa Relevant:ASIL-B
///
//-----------------------------------------------------------------------------
void Mt_CddDma_Init(void)
{
  Mt_CddDma_Init_TestCase1();
  Mt_CddDma_Init_TestCase2();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDma_StartJob_ForInterrupt_TestCase1
///
/// \Test Case Description
///        - Test subject: Test if the correct registers are updated with the correct value for software transfer (memory-memory)
///                        and DMA channel configured as : (source / destination minor loop offset enable & transfer size > 32b)
///         virtualDmaName      | irqChannel            | trigger                           | sourceAddressOperation  | targetAddressOperation  | transferSize            | loopMode
///         UNIT_TEST_CHANNEL   | CDDDMA_NotAvail_IRQn  | CDDDMA_REQ_DMAMUX_ALWAYS_ENABLED1 | DMA_ADDRESS_FIXED       | DMA_ADDRESS_FIXED       | DMA_TRANSFER_SIZE_2x32  | DMA_LOOP_MODE_ENDLESS
///
/// - Preconditions:
///
///  All related DMA-HW registers which are used must be emulated by the Test Case.
///          pointer to hardware registers initialized;
///          TCD (Transfer Control Descriptor) structure cleared
///
/// \input   CddDma_StartJob_ForInterrupt_eDmaChannelName   = UNIT_TEST_CHANNEL
/// \input   CddDma_StartJob_ForInterrupt_psParameter       = Mt_CddDma_CDDDMA_CHECK_ADDRESS_True (Structure containing Dma Parameters initialized)
///
/// - Expectations:
///
/// \output &CddDma_StartJob_ForInterrupt_psParameter != NULL
/// \output CddDma_psRegister->Reg_CERQ.ucData = UNIT_TEST_CHANNEL
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_SADDR.ulData = CddDma_StartJob_ForInterrupt_psParameter.pulSourceAddress
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_DADDR.ulData = CddDma_StartJob_ForInterrupt_psParameter.pulTargetAddress
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_BITER.tuELINKYES.sBit.u1ELINK = 1u
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_CITER.tuELINKYES.sBit.u1ELINK = 1u
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_BITER.tuELINKYES.sBit.u4LINKCH = UNIT_TEST_CHANNEL
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_CITER.tuELINKYES.sBit.u4LINKCH = UNIT_TEST_CHANNEL
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_BITER.tuELINKYES.sBit.u9BITER  = CddDma_StartJob_ForInterrupt_psParameter.unRepetitions
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_CITER.tuELINKYES.sBit.u9CITER  = CddDma_StartJob_ForInterrupt_psParameter.unRepetitions
/// \output CddDma_psRegister->Reg_SSRT.ucData  = UNIT_TEST_CHANNEL
///
//-----------------------------------------------------------------------------
void Mt_CddDma_StartJob_ForInterrupt_TestCase1(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  CddDma_StartJob_ForInterrupt_eDmaChannelName  = UNIT_TEST_CHANNEL;
  CddDma_StartJob_ForInterrupt_psParameter      = Mt_CddDma_CDDDMA_CHECK_ADDRESS_True;

  //Step 3) Call FUT
  CddDma_StartJob_ForInterrupt(CddDma_StartJob_ForInterrupt_eDmaChannelName, &CddDma_StartJob_ForInterrupt_psParameter);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(&CddDma_StartJob_ForInterrupt_psParameter, NULL, != );

  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_CERQ.ucData, UNIT_TEST_CHANNEL, == );
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_SADDR.ulData, CddDma_StartJob_ForInterrupt_psParameter.pulSourceAddress, == );
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_DADDR.ulData, CddDma_StartJob_ForInterrupt_psParameter.pulTargetAddress, == );

  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_BITER.tuELINKYES.sBit.u1ELINK, 1u, == );
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_CITER.tuELINKYES.sBit.u1ELINK, 1u, == );

  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_BITER.tuELINKYES.sBit.u4LINKCH, UNIT_TEST_CHANNEL, == );
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_CITER.tuELINKYES.sBit.u4LINKCH, UNIT_TEST_CHANNEL, == );
 
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_BITER.tuELINKYES.sBit.u9BITER, CddDma_StartJob_ForInterrupt_psParameter.unRepetitions, == );
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_CITER.tuELINKYES.sBit.u9CITER, CddDma_StartJob_ForInterrupt_psParameter.unRepetitions, == );

  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_SSRT.ucData, UNIT_TEST_CHANNEL, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDma_StartJob_ForInterrupt_TestCase2
///
/// \Test Case Description
///        - Test subject: Test if the correct registers are updated with the correct value for software triggered transfer 
///                        and DMA channel configured as : (source / destination minor loop offset enable & transfer size ==  32b)
///         virtualDmaName      | irqChannel            | trigger                           | sourceAddressOperation     | targetAddressOperation  | transferSize            | loopMode
///         UNIT_TEST_CHANNEL   | CDDDMA_NotAvail_IRQn  | CDDDMA_REQ_DMAMUX_ALWAYS_ENABLED1 | DMA_ADDRESS_FIXED          | DMA_ADDRESS_FIXED       | DMA_TRANSFER_SIZE_2x32  | DMA_LOOP_MODE_ENDLESS
///         SYS_CRC             | DMA_IRQ_INTDMA8       | CDDDMA_REQ_DISABLED               | DMA_ADDRESS_INCREMENTED    | DMA_ADDRESS_FIXED       | DMA_TRANSFER_SIZE_32    | DMA_LOOP_MODE_ENDLESS
///
/// - Preconditions:
///
///  All related DMA-HW registers which are used must be emulated by the Test Case.
///          pointer to hardware registers initialized;
///          TCD (Transfer Control Descriptor) structure cleared
///
/// \input   CddDma_StartJob_ForInterrupt_eDmaChannelName   = SYS_CRC
/// \input   CddDma_StartJob_ForInterrupt_psParameter       = Mt_CddDma_CDDDMA_CHECK_ADDRESS_False (Structure containing Dma Parameters initialized)
///
/// - Expectations:
///
/// \output &CddDma_StartJob_ForInterrupt_psParameter != NULL
/// \output CddDma_psRegister->Reg_CERQ.ucData = SYS_CRC
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_SADDR.ulData                   = CddDma_StartJob_ForInterrupt_psParameter.pulSourceAddress
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_DADDR.ulData                   = CddDma_StartJob_ForInterrupt_psParameter.pulTargetAddress
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_BITER.tuELINKNO.sBit.u1ELINK   = 1u
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_CITER.tuELINKNO.sBit.u1ELINK   = 1u
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_BITER.tuELINKYES.sBit.u4LINKCH = CddDma_StartJob_ForInterrupt_eDmaChannelName
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_CITER.tuELINKYES.sBit.u4LINKCH = CddDma_StartJob_ForInterrupt_eDmaChannelName
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_BITER.tuELINKYES.sBit.u9BITER  = CddDma_StartJob_ForInterrupt_psParameter.unRepetitions
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_CITER.tuELINKYES.sBit.u9CITER  = CddDma_StartJob_ForInterrupt_psParameter.unRepetitions
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_SLAST.ulData                   = -32
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_DLASTSGA.ulData                = -32
/// \output CddDma_psRegister->Reg_SERQ.ucData  = SYS_CRC
///
//-----------------------------------------------------------------------------
void Mt_CddDma_StartJob_ForInterrupt_TestCase2(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  CddDma_StartJob_ForInterrupt_eDmaChannelName    = SYS_CRC;
  CddDma_StartJob_ForInterrupt_psParameter        = Mt_CddDma_CDDDMA_CHECK_ADDRESS_False;

  //Step 3) Call FUT
  CddDma_StartJob_ForInterrupt(CddDma_StartJob_ForInterrupt_eDmaChannelName, &CddDma_StartJob_ForInterrupt_psParameter);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(&CddDma_StartJob_ForInterrupt_psParameter, NULL, != );

  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_CERQ.ucData, SYS_CRC, == );
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_SADDR.ulData, (uint32)CddDma_StartJob_ForInterrupt_psParameter.pulSourceAddress, == );
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_DADDR.ulData, (uint32)CddDma_StartJob_ForInterrupt_psParameter.pulTargetAddress, == );

  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_BITER.tuELINKYES.sBit.u1ELINK, 1u, == );
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_CITER.tuELINKYES.sBit.u1ELINK, 1u, == );
  
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_BITER.tuELINKYES.sBit.u4LINKCH, CddDma_StartJob_ForInterrupt_eDmaChannelName, == );
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_CITER.tuELINKYES.sBit.u4LINKCH, CddDma_StartJob_ForInterrupt_eDmaChannelName, == );
 
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_BITER.tuELINKYES.sBit.u9BITER, CddDma_StartJob_ForInterrupt_psParameter.unRepetitions, == );
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_CITER.tuELINKYES.sBit.u9CITER, CddDma_StartJob_ForInterrupt_psParameter.unRepetitions, == );
  
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_SLAST.ulData,     -8, == );  //trasnfer size 8
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_DLASTSGA.ulData,  -8, == );

  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_SSRT.ucData, SYS_CRC, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDma_StartJob_ForInterrupt_TestCase3
///
/// \Test Case Description
///        - Test subject: Test if the correct registers are updated with the correct value for hardware transfer (memory-peripheral, peripheral-peripheral)
///                        and DMA channel configured as : (source / destination minor loop offset enable & transfer size > 32b)
///         virtualDmaName      | irqChannel            | trigger                           | sourceAddressOperation     | targetAddressOperation  | transferSize            | loopMode
///         UNIT_TEST_CHANNEL   | CDDDMA_NotAvail_IRQn  | CDDDMA_REQ_DMAMUX_ALWAYS_ENABLED1 | DMA_ADDRESS_FIXED          | DMA_ADDRESS_FIXED       | DMA_TRANSFER_SIZE_2x32  | DMA_LOOP_MODE_ENDLESS
///
/// - Preconditions:
///
///  All related DMA-HW registers which are used must be emulated by the Test Case.
///          pointer to hardware registers initialized;
///          TCD (Transfer Control Descriptor) structure cleared
///
/// \input   CddDma_StartJob_ForInterrupt_eDmaChannelName   = UNIT_TEST_CHANNEL
/// \input   CddDma_StartJob_ForInterrupt_psParameter       = Mt_CddDma_CDDDMA_CHECK_ADDRESS_False (Structure containing Dma Parameters initialized)
///
/// - Expectations:
///
/// \output &CddDma_StartJob_ForInterrupt_psParameter != NULL
/// \output CddDma_psRegister->Reg_CERQ.ucData    = UNIT_TEST_CHANNEL
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_SADDR.ulData = CddDma_StartJob_ForInterrupt_psParameter.pulSourceAddress
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_DADDR.ulData = CddDma_StartJob_ForInterrupt_psParameter.pulTargetAddress
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_BITER.tuELINKNO.sBit.u1ELINK   = 0u
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_CITER.tuELINKNO.sBit.u1ELINK   = 0u
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_BITER.tuELINKNO.sBit.u15BITER  = CddDma_StartJob_ForInterrupt_psParameter.unRepetitions
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_CITER.tuELINKNO.sBit.u15CITER  = CddDma_StartJob_ForInterrupt_psParameter.unRepetitions
/// \output CddDma_psRegister->Reg_SERQ.ucData  = UNIT_TEST_CHANNEL
///
//-----------------------------------------------------------------------------
void Mt_CddDma_StartJob_ForInterrupt_TestCase3(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  CddDma_StartJob_ForInterrupt_eDmaChannelName    = UNIT_TEST_CHANNEL;
  CddDma_StartJob_ForInterrupt_psParameter        = Mt_CddDma_CDDDMA_CHECK_ADDRESS_False;

  //Step 3) Call FUT
  CddDma_StartJob_ForInterrupt(CddDma_StartJob_ForInterrupt_eDmaChannelName, &CddDma_StartJob_ForInterrupt_psParameter);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(&CddDma_StartJob_ForInterrupt_psParameter, NULL, != );

  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_CERQ.ucData, UNIT_TEST_CHANNEL, == );
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_SADDR.ulData, (uint32)CddDma_StartJob_ForInterrupt_psParameter.pulSourceAddress, == );
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_DADDR.ulData, (uint32)CddDma_StartJob_ForInterrupt_psParameter.pulTargetAddress, == );

  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_BITER.tuELINKNO.sBit.u1ELINK, 0u, == );
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_CITER.tuELINKNO.sBit.u1ELINK, 0u, == );
 
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_BITER.tuELINKNO.sBit.u15BITER, CddDma_StartJob_ForInterrupt_psParameter.unRepetitions, == );
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_ForInterrupt_eDmaChannelName].tuTCDn_CITER.tuELINKNO.sBit.u15CITER, CddDma_StartJob_ForInterrupt_psParameter.unRepetitions, == );

  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_SERQ.ucData, UNIT_TEST_CHANNEL, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDma_StartJob_ForInterrupt
///
/// \Test Case Description
///        - Test subject: Test the configuration of a DMA job performed
///                        without callback functions
///
//-----------------------------------------------------------------------------
void Mt_CddDma_StartJob_ForInterrupt(void)
{
  Mt_CddDma_StartJob_ForInterrupt_TestCase1();
  Mt_CddDma_StartJob_ForInterrupt_TestCase2();
  Mt_CddDma_StartJob_ForInterrupt_TestCase3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDma_StartJob_TestCase1
///
/// \Test Case Description
///        - Test subject: Test if the correct registers are updated with the correct value when function
///                        is called with no callback function and transfer type is software transfer (memory-memory)
///                        and DMA channel configured as: (source/destination minor loop offset enable & transfer size > 32b)
///         virtualDmaName      | irqChannel            | trigger                           | sourceAddressOperation  | targetAddressOperation  | transferSize            | loopMode
///         UNIT_TEST_CHANNEL   | CDDDMA_NotAvail_IRQn  | CDDDMA_REQ_DMAMUX_ALWAYS_ENABLED1 | DMA_ADDRESS_FIXED       | DMA_ADDRESS_FIXED       | DMA_TRANSFER_SIZE_2x32  | DMA_LOOP_MODE_ENDLESS
///
///
///       - Test Design Technique:  - Requirement based test
///                                 - ET (Exploratory Testing) 
///
/// \FuSa Relevant:   ASIL-B
///
/// - Preconditions:
///
///  All related DMA-HW registers which are used must be emulated by the Test Case.
///          pointer to hardware registers initialized;
///          TCD (Transfer Control Descriptor) structure cleared
///
/// \input  CddDma_StartJob_eDmaChannelName     = UNIT_TEST_CHANNEL
/// \input  CddDma_StartJob_psParameter         = Mt_CddDma_CDDDMA_CHECK_ADDRESS_True (Structure containing Dma Parameters initialized)
/// \input  CddDma_StartJob_fpCallback          = NULL_PTR
///
/// - Expectations:
///
/// \output &CddDma_StartJob_ForInterrupt_psParameter != NULL
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_CSR.sBit.u1INTMAJOR = 0u
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_SADDR.ulData = CddDma_StartJob_psParameter.pulSourceAddress
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_DADDR.ulData = CddDma_StartJob_psParameter.pulTargetAddress
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_BITER.tuELINKYES.sBit.u1ELINK  = 1u
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_CITER.tuELINKYES.sBit.u1ELINK  = 1u
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_BITER.tuELINKYES.sBit.u4LINKCH = UNIT_TEST_CHANNEL
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_CITER.tuELINKYES.sBit.u4LINKCH = UNIT_TEST_CHANNEL
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_BITER.tuELINKYES.sBit.u9BITER  = CddDma_StartJob_psParameter.unRepetitions
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_CITER.tuELINKYES.sBit.u9CITER  = CddDma_StartJob_psParameter.unRepetitions
/// \output CddDma_psRegister->Reg_SSRT.ucData = UNIT_TEST_CHANNEL
///
//-----------------------------------------------------------------------------
void Mt_CddDma_StartJob_TestCase1(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  CddDma_StartJob_eDmaChannelName = UNIT_TEST_CHANNEL;
  CddDma_StartJob_psParameter     = Mt_CddDma_CDDDMA_CHECK_ADDRESS_True;

  //Step 3) Call FUT
  CddDma_StartJob(CddDma_StartJob_eDmaChannelName, &CddDma_StartJob_psParameter, NULL_PTR);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(&CddDma_StartJob_psParameter, NULL, != );
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_CSR.sBit.u1INTMAJOR, 0u, == );

  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_SADDR.ulData, (uint32)CddDma_StartJob_psParameter.pulSourceAddress, == );
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_DADDR.ulData, (uint32)CddDma_StartJob_psParameter.pulTargetAddress, == );

  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_BITER.tuELINKYES.sBit.u1ELINK, 1u, == );
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_CITER.tuELINKYES.sBit.u1ELINK, 1u, == );

  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_BITER.tuELINKYES.sBit.u4LINKCH, UNIT_TEST_CHANNEL, == );
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_CITER.tuELINKYES.sBit.u4LINKCH, UNIT_TEST_CHANNEL, == );

  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_BITER.tuELINKYES.sBit.u9BITER, CddDma_StartJob_psParameter.unRepetitions, == );
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_CITER.tuELINKYES.sBit.u9CITER, CddDma_StartJob_psParameter.unRepetitions, == );
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_SSRT.ucData, UNIT_TEST_CHANNEL, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDma_StartJob_TestCase2
///
/// \Test Case Description
///        - Test subject: Test if the correct registers are updated with the correct value when function
///                        is called with  callback function and transfer type is hardware transfer (memory-peripheral, peripheral-peripheral)
///                        and DMA channel configured as : (source / destination minor loop offset enable & transfer size > 32b)
///         virtualDmaName      | irqChannel            | trigger                           | sourceAddressOperation  | targetAddressOperation  | transferSize            | loopMode
///         UNIT_TEST_CHANNEL   | CDDDMA_NotAvail_IRQn  | CDDDMA_REQ_DMAMUX_ALWAYS_ENABLED1 | DMA_ADDRESS_FIXED       | DMA_ADDRESS_FIXED       | DMA_TRANSFER_SIZE_2x32  | DMA_LOOP_MODE_ENDLESS
///
///
///       - Test Design Technique:  - Requirement based test
///                                 - ET (Exploratory Testing) 
///
/// \FuSa Relevant:   ASIL-B
///
/// - Preconditions:
///
///  All related DMA-HW registers which are used must be emulated by the Test Case.
///          pointer to hardware registers initialized;
///          TCD (Transfer Control Descriptor) structure cleared
///
/// \input  CddDma_StartJob_eDmaChannelName     = UNIT_TEST_CHANNEL
/// \input  CddDma_StartJob_psParameter         = Mt_CddDma_CDDDMA_CHECK_ADDRESS_False (Structure containing Dma Parameters initialized)
/// \input  CddDma_StartJob_fpCallback          = &CddDma_StartJob_Callback_Stub
///
///
/// - Expectations:
///
/// \output &CddDma_StartJob_ForInterrupt_psParameter != NULL
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_CSR.sBit.u1INTMAJOR            = 1u
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_SADDR.ulData                   = CddDma_StartJob_psParameter.pulSourceAddress
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_DADDR.ulData                   = CddDma_StartJob_psParameter.pulTargetAddress
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_BITER.tuELINKNO.sBit.u1ELINK   = 0u
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_CITER.tuELINKNO.sBit.u1ELINK   = 0u
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_BITER.tuELINKNO.sBit.u15BITER  = CddDma_StartJob_psParameter.unRepetitions
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_CITER.tuELINKNO.sBit.u15CITER  = CddDma_StartJob_psParameter.unRepetitions
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_SLAST.ulData                   = -64
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_DLASTSGA.ulData                = -64
/// \output CddDma_psRegister->Reg_SERQ.ucData = UNIT_TEST_CHANNEL
///
//-----------------------------------------------------------------------------
void Mt_CddDma_StartJob_TestCase2(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  CddDma_StartJob_eDmaChannelName = UNIT_TEST_CHANNEL;
  CddDma_StartJob_psParameter     = Mt_CddDma_CDDDMA_CHECK_ADDRESS_False;
  CddDma_StartJob_fpCallback      = &CddDma_StartJob_Callback_Stub;

  //Step 3) Call the FUT
  CddDma_StartJob(CddDma_StartJob_eDmaChannelName, &CddDma_StartJob_psParameter, CddDma_StartJob_fpCallback);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(&CddDma_StartJob_psParameter, NULL, != );
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_CSR.sBit.u1INTMAJOR, 1u, == );

  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_SADDR.ulData, (uint32)CddDma_StartJob_psParameter.pulSourceAddress, == );
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_DADDR.ulData, (uint32)CddDma_StartJob_psParameter.pulTargetAddress, == );

  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_BITER.tuELINKNO.sBit.u1ELINK, 0u, == );
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_CITER.tuELINKNO.sBit.u1ELINK, 0u, == );

  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_BITER.tuELINKNO.sBit.u15BITER, CddDma_StartJob_psParameter.unRepetitions, == );
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_CITER.tuELINKNO.sBit.u15CITER, CddDma_StartJob_psParameter.unRepetitions, == );
  
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_SLAST.ulData,    -64, == );
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_DLASTSGA.ulData, -64, == );
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_SERQ.ucData, UNIT_TEST_CHANNEL, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDma_StartJob_TestCase3
///
/// \Test Case Description
///        - Test subject: Test if the correct registers are updated with the correct value when function
///                        is called with  callback function and transfer type is software triggered transfer (memory-peripheral, peripheral-peripheral)
///                        and DMA channel configured as : (source / destination minor loop offset enable & transfer size = 32b)
///         virtualDmaName      | irqChannel            | trigger                           | sourceAddressOperation     | targetAddressOperation  | transferSize            | loopMode
///         SYS_CRC             | DMA_IRQ_INTDMA4       | CDDDMA_REQ_DISABLED               | DMA_ADDRESS_INCREMENTED    | DMA_ADDRESS_FIXED       | DMA_TRANSFER_SIZE_32    | DMA_LOOP_MODE_ENDLESS
///
///
///       - Test Design Technique:  - Requirement based test
///                                 - ET (Exploratory Testing) 
///
/// \FuSa Relevant:   ASIL-B
///
/// - Preconditions:
///
///  All related DMA-HW registers which are used must be emulated by the Test Case.
///          pointer to hardware registers initialized;
///          TCD (Transfer Control Descriptor) structure cleared
///
/// \input  CddDma_StartJob_eDmaChannelName    = SYS_CRC
/// \input  CddDma_StartJob_psParameter        = Mt_CddDma_CDDDMA_CHECK_ADDRESS_False (Structure containing Dma Parameters initialized)
/// \input  CddDma_StartJob_fpCallback         = &CddDma_StartJob_Callback_Stub
///
///
/// - Expectations:
///
/// \output &CddDma_StartJob_ForInterrupt_psParameter != NULL
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_CSR.sBit.u1INTMAJOR            = 1u
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_SADDR.ulData                   = CddDma_StartJob_psParameter.pulSourceAddress
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_DADDR.ulData                   = CddDma_StartJob_psParameter.pulTargetAddress
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_BITER.tuELINKYES.sBit.u1ELINK  = 1u
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_CITER.tuELINKYES.sBit.u1ELINK  = 1u
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_BITER.tuELINKYES.sBit.u4LINKCH = SYS_CRC
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_CITER.tuELINKYES.sBit.u4LINKCH = SYS_CRC
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_BITER.tuELINKYES.sBit.u9BITER  = CddDma_StartJob_psParameter.unRepetitions
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_CITER.tuELINKYES.sBit.u9CITER  = CddDma_StartJob_psParameter.unRepetitions
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_SLAST.ulData                   = -32u
/// \output CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_DLASTSGA.ulData                = -32u
/// \output CddDma_psRegister->Reg_SSRT.ucData = SYS_CRC
///
//-----------------------------------------------------------------------------
void Mt_CddDma_StartJob_TestCase3(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  CddDma_StartJob_eDmaChannelName = SYS_CRC;
  CddDma_StartJob_psParameter     = Mt_CddDma_CDDDMA_CHECK_ADDRESS_False;
  CddDma_StartJob_fpCallback      = &CddDma_StartJob_Callback_Stub;

  //Step 3) Call the FUT
  CddDma_StartJob(CddDma_StartJob_eDmaChannelName, &CddDma_StartJob_psParameter, CddDma_StartJob_fpCallback);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(&CddDma_StartJob_psParameter, NULL, != );
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_CSR.sBit.u1INTMAJOR, 1u, == );

  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_SADDR.ulData, (uint32)CddDma_StartJob_psParameter.pulSourceAddress, == );
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_DADDR.ulData, (uint32)CddDma_StartJob_psParameter.pulTargetAddress, == );

  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_BITER.tuELINKYES.sBit.u1ELINK, 1u, == );
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_CITER.tuELINKYES.sBit.u1ELINK, 1u, == );
  
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_BITER.tuELINKYES.sBit.u4LINKCH, CddDma_StartJob_eDmaChannelName, == );
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_CITER.tuELINKYES.sBit.u4LINKCH, CddDma_StartJob_eDmaChannelName, == );

  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_BITER.tuELINKYES.sBit.u9BITER, CddDma_StartJob_psParameter.unRepetitions, == );
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_CITER.tuELINKYES.sBit.u9CITER, CddDma_StartJob_psParameter.unRepetitions, == );
  

  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_SLAST.ulData,    -8u,    == );  //transfer size 8
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_DLASTSGA.ulData, -8u,    == );
  AL_UNITTEST_CHECK(CddDma_psRegister->Reg_TCDn[CddDma_StartJob_eDmaChannelName].tuTCDn_CSR.sBit.u1START, 1u,    == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDma_StartJob
///
/// \Test Case Description
///        - Test subject: Test the configuration of a DMA job performed
///                        using callback functions
///
///       - Test Design Technique:  - Requirement based test
///                                 - ET (Exploratory Testing) 
///
/// \FuSa Relevant:   ASIL-B
///
//-----------------------------------------------------------------------------
void Mt_CddDma_StartJob(void)
{
  Mt_CddDma_StartJob_TestCase1();
  Mt_CddDma_StartJob_TestCase2();
  Mt_CddDma_StartJob_TestCase3();
}

//-----------------------------------------------------------------------------
/// \brief  ALUnitTest_AddTests
///
/// \descr  Every test case shall be added to this list
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void ALUnitTest_AddTests(void)
{

  ALUnitTest_AddFunction("Mt_CddDma_IsJobCompleted",              Mt_CddDma_IsJobCompleted);
  ALUnitTest_AddFunction("Mt_CddDma_GenerateTriggerSignal",       Mt_CddDma_GenerateTriggerSignal);
  ALUnitTest_AddFunction("Mt_CddDma_EnableHwTrigger",             Mt_CddDma_EnableHwTrigger); 
  ALUnitTest_AddFunction("Mt_CddDma_Init",                        Mt_CddDma_Init);
  ALUnitTest_AddFunction("Mt_CddDma_StartJob_ForInterrupt",       Mt_CddDma_StartJob_ForInterrupt);
  ALUnitTest_AddFunction("Mt_CddDma_StartJob",                    Mt_CddDma_StartJob);

}

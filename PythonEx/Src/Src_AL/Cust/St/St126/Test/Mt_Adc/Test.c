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
/// \brief  Unit Test Cases for ADC module
///
/// \author Sevastre Georgiana (F54430C)
///         mailTo:georgiana.sevastre[at]marelli.com
//-----------------------------------------------------------------------------

//=============================================================================================================================================================
//  Files covered by this module unit test:
//            - Adc.c
//            - Adc_Dma.c
//            - Adc_Drv.c
//=============================================================================================================================================================

//=============================================================================
// Includes
//=============================================================================

// Standard unit test header
#include <ALUnitTest_UserInterface.h>
#include <stdio.h>

// Stub headers
#include "Test_Stubs.h"

// Headers of the unit test Module
#include "Test.h"

//=============================================================================
// Test Cases
//=============================================================================

//Adc.c:

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Adc_Init_TestCase1
///
/// \Test Case Description: Test Adc global configuration avoided, when input config 
///                         parameter is NULL
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input     Temp0 = *ADC0;
/// \input     Temp1 = *ADC1;
///
/// - Expectations: 
///
/// \output   CddDma_StartJob_HitCount  = 0u;
/// \output   Temp0.aR[0]               = ADC0->aR[0]
/// \output   Temp1.CFG1                = ADC0->CFG1
/// \output   Temp0.SC3                 = ADC0->SC3
//-----------------------------------------------------------------------------
void Mt_Adc_Init_TestCase1()
{
  ADC_Type Temp0, Temp1;

  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Temp0 = *ADC0;
  Temp1 = *ADC1;

  //Step 2) Assign Input values
  //-----

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Init(NULL);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddDma_StartJob_HitCount, 0u , == );
  AL_UNITTEST_CHECK(Temp0.aR[0], ADC0->aR[0]     , == );
  AL_UNITTEST_CHECK(Temp1.CFG1,  ADC0->CFG1      , == );
  AL_UNITTEST_CHECK(Temp0.SC3, ADC0->SC3         , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Adc_Init_TestCase2
///
/// \Test Case Description: Test Adc0 global configuration, DMA Job and RAM data 
///                         storage for ADC values when input config parameter is
///                         not NULL
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input        CddDma_StartJob_HitCount                       = 0u
/// \input        asLocalInstCfg[0].ucAdcInst                    = 0u
/// \input        asLocalInstCfg[1].ucAdcInst                    = 1u
/// \input        asLocalCfg[0].eInCh                            = eADC_EXT_2
/// \input        asLocalCfg[0].ucAdcInst                        = 0u
/// \input        asLocalCfg[0].ucAdcCh                          = 1u
/// \input        asLocalCfg[0].eInSelAdc                        = eAdcExtCh9
/// \input        asLocalCfg[0].boIntEnbl                        = FALSE
/// \input        asLocalCfg[0].pulAdcData                       = &aulLocalRes[1]
/// \input        asLocalCfg[1].eInCh                            = eADC_EXT_3
/// \input        asLocalCfg[1].ucAdcInst                        = 1u
/// \input        asLocalCfg[1].ucAdcCh                          = 0u
/// \input        asLocalCfg[1].eInSelAdc                        = eAdcExtCh11
/// \input        asLocalCfg[1].boIntEnbl                        = FALSE
/// \input        asLocalCfg[1].pulAdcData                       = &aulLocalRes[3]
/// \input        Adc_Init_Param1->sAdcInstanceCfg.psAdcInstCfg  = &asLocalInstCfg[0]
/// \input        Adc_Init_Param1->sAdcInstanceCfg.ucCfgLength   = 2u
/// \input        Adc_Init_Param1->sAdcInputChCfg.psAdcInCfg     = &asLocalCfg[0]
/// \input        Adc_Init_Param1->sAdcInputChCfg.ucCfgLength    = 4u
///
/// - Expectations: 
///
/// \output       CddDma_StartJob_HitCount                        =1u
//-----------------------------------------------------------------------------
void Mt_Adc_Init_TestCase2()
{
  tsAdc_AdcInputCfg    asLocalCfg[2];
  uint32               aulLocalRes[2];
  tsAdc_AdcInstanceCfg asLocalInstCfg[2];

  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  CddDma_StartJob_HitCount      = 0u;
  asLocalInstCfg[0].ucAdcInst   = 0u;
  asLocalInstCfg[1].ucAdcInst   = 1u;

  asLocalCfg[0].eInCh           = eADC_EXT_2;
  asLocalCfg[0].ucAdcInst       = 0u;
  asLocalCfg[0].ucAdcCh         = 1u;
  asLocalCfg[0].eInSelAdc       = eAdcExtCh9;
  asLocalCfg[0].boIntEnbl       = FALSE;
  asLocalCfg[0].pulAdcData      = &aulLocalRes[1];

  asLocalCfg[1].eInCh           = eADC_EXT_3;
  asLocalCfg[1].ucAdcInst       = 1u;
  asLocalCfg[1].ucAdcCh         = 0u;
  asLocalCfg[1].eInSelAdc       = eAdcExtCh11;
  asLocalCfg[1].boIntEnbl       = FALSE;
  asLocalCfg[1].pulAdcData      = &aulLocalRes[3];

  psAdcCfgData_Dummy.sAdcInstanceCfg.psAdcInstCfg  = &asLocalInstCfg[0];
  psAdcCfgData_Dummy.sAdcInstanceCfg.ucCfgLength   = 2u;
  psAdcCfgData_Dummy.sAdcInputChCfg.psAdcInCfg     = &asLocalCfg[0];
  psAdcCfgData_Dummy.sAdcInputChCfg.ucCfgLength    = 4u;

  //Step 2) Assign Input values
  Adc_Init_Param1 = &psAdcCfgData_Dummy;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Init(Adc_Init_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddDma_StartJob_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Adc_Init_TestCase3
///
/// \Test Case Description: Test Adc1 global configuration, DMA Job and RAM data 
///                         storage for ADC values when input config parameter is
///                         not NULL
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input        CddDma_StartJob_HitCount                       = 0u
/// \input        asLocalInstCfg[0].ucAdcInst                    = 0u
/// \input        asLocalInstCfg[1].ucAdcInst                    = 1u
/// \input        asLocalCfg[0].eInCh                            = eADC_EXT_2
/// \input        asLocalCfg[0].ucAdcInst                        = 0u
/// \input        asLocalCfg[0].ucAdcCh                          = 1u
/// \input        asLocalCfg[0].eInSelAdc                        = eAdcExtCh9
/// \input        asLocalCfg[0].boIntEnbl                        = FALSE
/// \input        asLocalCfg[0].pulAdcData                       = &aulLocalRes[1]
/// \input        asLocalCfg[1].eInCh                            = eADC_EXT_3
/// \input        asLocalCfg[1].ucAdcInst                        = 1u
/// \input        asLocalCfg[1].ucAdcCh                          = 0u
/// \input        asLocalCfg[1].eInSelAdc                        = eAdcExtCh11
/// \input        asLocalCfg[1].boIntEnbl                        = FALSE
/// \input        asLocalCfg[1].pulAdcData                       = &aulLocalRes[3]
/// \input        Adc_Init_Param1->sAdcInstanceCfg.psAdcInstCfg  = &asLocalInstCfg[0]
/// \input        Adc_Init_Param1->sAdcInstanceCfg.ucCfgLength   = 2u
/// \input        Adc_Init_Param1->sAdcInputChCfg.psAdcInCfg     = &asLocalCfg[0]
/// \input        Adc_Init_Param1->sAdcInputChCfg.ucCfgLength    = 4u
///
/// - Expectations: 
///
/// \output       CddDma_StartJob_HitCount                       = 1u
//-----------------------------------------------------------------------------
void Mt_Adc_Init_TestCase3()
{
  tsAdc_AdcInputCfg    asLocalCfg[2];
  uint32               aulLocalRes[2];
  tsAdc_AdcInstanceCfg asLocalInstCfg[2];

  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  CddDma_StartJob_HitCount     = 0u;
  asLocalInstCfg[0].ucAdcInst  = 0u;
  asLocalInstCfg[1].ucAdcInst  = 1u;

  asLocalCfg[0].eInCh          = eADC_EXT_2;
  asLocalCfg[0].ucAdcInst      = 0u;
  asLocalCfg[0].ucAdcCh        = 1u;
  asLocalCfg[0].eInSelAdc      = eAdcExtCh9;
  asLocalCfg[0].boIntEnbl      = FALSE;
  asLocalCfg[0].pulAdcData     = &aulLocalRes[1];

  asLocalCfg[1].eInCh          = eADC_EXT_3;
  asLocalCfg[1].ucAdcInst      = 1u;
  asLocalCfg[1].ucAdcCh        = 0u;
  asLocalCfg[1].eInSelAdc      = eAdcExtCh11;
  asLocalCfg[1].boIntEnbl      = FALSE;
  asLocalCfg[1].pulAdcData     = &aulLocalRes[3];

  psAdcCfgData_Dummy.sAdcInstanceCfg.psAdcInstCfg  = &asLocalInstCfg[1];
  psAdcCfgData_Dummy.sAdcInstanceCfg.ucCfgLength   = 2u;
  psAdcCfgData_Dummy.sAdcInputChCfg.psAdcInCfg     = &asLocalCfg[1];
  psAdcCfgData_Dummy.sAdcInputChCfg.ucCfgLength    = 4u;

  //Step 2) Assign Input values
  Adc_Init_Param1 = &psAdcCfgData_Dummy;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

   //Step 3) Call FUT
  Adc_Init(Adc_Init_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddDma_StartJob_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Adc_ReadGroup_TestCase
///
/// \Test Case Description: Test Adc value returned
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input         Adc_ReadGroup_Param1                              = 5u
/// \input         ulAdcData_Dummy[Adc_ReadGroup_Param1]             = 30u
/// \input         psAdcInCfg_Dummy[Adc_ReadGroup_Param1].pulAdcData = &ulAdcData_Dummy[Adc_ReadGroup_Param1]
/// \input         Adc_Drv_sInputMap_Dummy.psAdcInCfg                = psAdcInCfg_Dummy
/// \input         Adc_Drv_sInputMap_Dummy.ucCfgLength               = 10u
/// \input         Adc_Drv_psInputMap                                = &Adc_Drv_sInputMap_Dummy
///
/// - Expectations: 
///
/// \output        Adc_ReadGroup_Param2                              = 30u
//-----------------------------------------------------------------------------
void Mt_Adc_ReadGroup_TestCase()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc_Drv_sInputMap_Dummy.psAdcInCfg                = psAdcInCfg_Dummy;
  Adc_Drv_sInputMap_Dummy.ucCfgLength               = 10u;
  Adc_Drv_psInputMap                                = &Adc_Drv_sInputMap_Dummy;

  //Step 2) Assign Input values
  Adc_ReadGroup_Param2 = &Adc_ReadGroup_Param2_Dummy;
  Adc_ReadGroup_Param1 = 5u;
  ulAdcData_Dummy[Adc_ReadGroup_Param1] = 30u;
  psAdcInCfg_Dummy[Adc_ReadGroup_Param1].pulAdcData = &ulAdcData_Dummy[Adc_ReadGroup_Param1];

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_ReadGroup(Adc_ReadGroup_Param1, Adc_ReadGroup_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_ReadGroup_Param2_Dummy, 30u, == );
}

//Adc_Dma.c:

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Adc_Dma_InitDmaJob_TestCase1
///
/// \Test Case Description: Test  ADC0 and ADC1 DMA config and return DMA 
///                         config status TRUE
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input     CddDma_StartJob_HitCount                                = 0u
/// \input     asLocalInstCfg[0].ucAdcInst                             = 0u
/// \input     asLocalInstCfg[1].ucAdcInst                             = 1u
/// \input     asLocalCfg[0].eInCh                                     = eADC_EXT_2
/// \input     asLocalCfg[0].ucAdcInst                                 = 0u
/// \input     asLocalCfg[0].ucAdcCh                                   = 1u
/// \input     asLocalCfg[0].eInSelAdc                                 = eAdcExtCh9
/// \input     asLocalCfg[0].boIntEnbl                                 = FALSE
/// \input     asLocalCfg[0].pulAdcData                                = &aulLocalRes[1]
/// \input     asLocalCfg[1].eInCh                                     = eADC_EXT_3
/// \input     asLocalCfg[1].ucAdcInst                                 = 1u
/// \input     asLocalCfg[1].ucAdcCh                                   = 0u
/// \input     asLocalCfg[1].eInSelAdc                                 = eAdcExtCh11
/// \input     asLocalCfg[1].boIntEnbl                                 = FALSE
/// \input     asLocalCfg[1].pulAdcData                                = &aulLocalRes[3]
/// \input     asLocalCfg[2].eInCh                                     = eADC_EXT_1
/// \input     asLocalCfg[2].ucAdcInst                                 = 0u
/// \input     asLocalCfg[2].ucAdcCh                                   = 2u
/// \input     asLocalCfg[2].eInSelAdc                                 = eAdcExtCh10
/// \input     asLocalCfg[2].boIntEnbl                                 = FALSE
/// \input     asLocalCfg[2].pulAdcData                                = &aulLocalRes[2]
/// \input     asLocalCfg[3].eInCh                                     = eADC_EXT_5
/// \input     asLocalCfg[3].ucAdcInst                                 = 1u
/// \input     asLocalCfg[3].ucAdcCh                                   = 1u
/// \input     asLocalCfg[3].eInSelAdc                                 = eAdcExtCh13
/// \input     asLocalCfg[3].boIntEnbl                                 = FALSE
/// \input     asLocalCfg[3].pulAdcData                                = &aulLocalRes[4]
/// \input     Adc_Dma_InitDmaJob_Param1.sAdcInstanceCfg.psAdcInstCfg  = &asLocalInstCfg[0]
/// \input     Adc_Dma_InitDmaJob_Param1.sAdcInstanceCfg.ucCfgLength   = 2u
/// \input     Adc_Dma_InitDmaJob_Param1.sAdcInputChCfg.psAdcInCfg     = &asLocalCfg[0]
/// \input     Adc_Dma_InitDmaJob_Param1.sAdcInputChCfg.ucCfgLength    = 4u
///
/// - Expectations: 
///
/// \output   Adc_Dma_InitDmaJob_RetVal                                = E_OK
//-----------------------------------------------------------------------------
void Mt_Adc_Dma_InitDmaJob_TestCase1()
{
  tsAdc_AdcInputCfg    asLocalCfg[4];
  uint32               aulLocalRes[5];
  tsAdc_AdcInstanceCfg asLocalInstCfg[2];

  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  //Step 1) Set pre-conditions
  CddDma_StartJob_HitCount       = 0u;

  asLocalInstCfg[0].ucAdcInst    = 0u;
  asLocalInstCfg[1].ucAdcInst    = 1u;

  asLocalCfg[0].eInCh            = eADC_EXT_2;
  asLocalCfg[0].ucAdcInst        = 0u;
  asLocalCfg[0].ucAdcCh          = 1u;
  asLocalCfg[0].eInSelAdc        = eAdcExtCh9;
  asLocalCfg[0].boIntEnbl        = FALSE;
  asLocalCfg[0].pulAdcData       = &aulLocalRes[1];

  asLocalCfg[1].eInCh            = eADC_EXT_3;
  asLocalCfg[1].ucAdcInst        = 1u;
  asLocalCfg[1].ucAdcCh          = 0u;
  asLocalCfg[1].eInSelAdc        = eAdcExtCh11;
  asLocalCfg[1].boIntEnbl        = FALSE;
  asLocalCfg[1].pulAdcData       = &aulLocalRes[3];

  asLocalCfg[2].eInCh            = eADC_EXT_1;
  asLocalCfg[2].ucAdcInst        = 0u;
  asLocalCfg[2].ucAdcCh          = 2u;
  asLocalCfg[2].eInSelAdc        = eAdcExtCh10;
  asLocalCfg[2].boIntEnbl        = FALSE;
  asLocalCfg[2].pulAdcData       = &aulLocalRes[2];

  asLocalCfg[3].eInCh            = eADC_EXT_5;
  asLocalCfg[3].ucAdcInst        = 1u;
  asLocalCfg[3].ucAdcCh          = 1u;
  asLocalCfg[3].eInSelAdc        = eAdcExtCh13;
  asLocalCfg[3].boIntEnbl        = FALSE;
  asLocalCfg[3].pulAdcData       = &aulLocalRes[4];

  psAdcCfgData_Dummy.sAdcInstanceCfg.psAdcInstCfg  = &asLocalInstCfg[0];
  psAdcCfgData_Dummy.sAdcInstanceCfg.ucCfgLength   = 2u;
  psAdcCfgData_Dummy.sAdcInputChCfg.psAdcInCfg     = &asLocalCfg[0];
  psAdcCfgData_Dummy.sAdcInputChCfg.ucCfgLength    = 4u;

  //Step 2) Assign Input values
  Adc_Dma_InitDmaJob_Param1 = &psAdcCfgData_Dummy;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Dma_InitDmaJob_RetVal = Adc_Dma_InitDmaJob(Adc_Dma_InitDmaJob_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Dma_InitDmaJob_RetVal, E_OK, == );
  AL_UNITTEST_CHECK(CddDma_StartJob_HitCount, 2u   , == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Adc_Dma_InitDmaJob_TestCase2
///
/// \Test Case Description: Test  ADC0 and ACD1 DMA config and return DMA 
///                         config status FALSE
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input     CddDma_StartJob_HitCount                                = 0u
/// \input     asLocalInstCfg[0].ucAdcInst                             = 0u
/// \input     asLocalInstCfg[1].ucAdcInst                             = 1u
/// \input     asLocalCfg[0].eInCh                                     = eADC_EXT_2
/// \input     asLocalCfg[0].ucAdcInst                                 = 0u
/// \input     asLocalCfg[0].ucAdcCh                                   = 17u
/// \input     asLocalCfg[0].eInSelAdc                                 = eAdcExtCh9
/// \input     asLocalCfg[0].boIntEnbl                                 = FALSE
/// \input     asLocalCfg[0].pulAdcData                                = &aulLocalRes[1]
/// \input     asLocalCfg[1].eInCh                                     = eADC_EXT_3
/// \input     asLocalCfg[1].ucAdcInst                                 = 1u
/// \input     asLocalCfg[1].ucAdcCh                                   = 17u
/// \input     asLocalCfg[1].eInSelAdc                                 = eAdcExtCh11
/// \input     asLocalCfg[1].boIntEnbl                                 = FALSE
/// \input     asLocalCfg[1].pulAdcData                                = &aulLocalRes[3]
/// \input     asLocalCfg[2].eInCh                                     = eADC_EXT_1
/// \input     asLocalCfg[2].ucAdcInst                                 = 0u
/// \input     asLocalCfg[2].ucAdcCh                                   = 17u
/// \input     asLocalCfg[2].eInSelAdc                                 = eAdcExtCh10
/// \input     asLocalCfg[2].boIntEnbl                                 = FALSE
/// \input     asLocalCfg[2].pulAdcData                                = &aulLocalRes[2]
/// \input     asLocalCfg[3].eInCh                                     = eADC_EXT_5
/// \input     asLocalCfg[3].ucAdcInst                                 = 1u
/// \input     asLocalCfg[3].ucAdcCh                                   = 17u
/// \input     asLocalCfg[3].eInSelAdc                                 = eAdcExtCh13
/// \input     asLocalCfg[3].boIntEnbl                                 = FALSE
/// \input     asLocalCfg[3].pulAdcData                                = &aulLocalRes[4]
/// \input     Adc_Dma_InitDmaJob_Param1.sAdcInstanceCfg.psAdcInstCfg  = &asLocalInstCfg[0]
/// \input     Adc_Dma_InitDmaJob_Param1.sAdcInstanceCfg.ucCfgLength   = 2u
/// \input     Adc_Dma_InitDmaJob_Param1.sAdcInputChCfg.psAdcInCfg     = &asLocalCfg[0]
/// \input     Adc_Dma_InitDmaJob_Param1.sAdcInputChCfg.ucCfgLength    = 4u
///
/// - Expectations: 
///
/// \output   Adc_Dma_InitDmaJob_RetVal                                = E_NOT_OK
/// \output   CddDma_StartJob_HitCount                                 = 0u
//-----------------------------------------------------------------------------
void Mt_Adc_Dma_InitDmaJob_TestCase2()
{
  tsAdc_AdcInputCfg    asLocalCfg[4];
  uint32               aulLocalRes[5];
  tsAdc_AdcInstanceCfg asLocalInstCfg[2];

  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  CddDma_StartJob_HitCount       = 0u;

  asLocalInstCfg[0].ucAdcInst    = 0u;
  asLocalInstCfg[1].ucAdcInst    = 1u;

  asLocalCfg[0].eInCh            = eADC_EXT_2;
  asLocalCfg[0].ucAdcInst        = 0u;
  asLocalCfg[0].ucAdcCh          = 17u;
  asLocalCfg[0].eInSelAdc        = eAdcExtCh9;
  asLocalCfg[0].boIntEnbl        = FALSE;
  asLocalCfg[0].pulAdcData       = &aulLocalRes[1];
  
  asLocalCfg[1].eInCh            = eADC_EXT_3;
  asLocalCfg[1].ucAdcInst        = 1u;
  asLocalCfg[1].ucAdcCh          = 17u;
  asLocalCfg[1].eInSelAdc        = eAdcExtCh11;
  asLocalCfg[1].boIntEnbl        = FALSE;
  asLocalCfg[1].pulAdcData       = &aulLocalRes[3];

  asLocalCfg[2].eInCh            = eADC_EXT_1;
  asLocalCfg[2].ucAdcInst        = 0u;
  asLocalCfg[2].ucAdcCh          = 17u;
  asLocalCfg[2].eInSelAdc        = eAdcExtCh10;
  asLocalCfg[2].boIntEnbl        = FALSE;
  asLocalCfg[2].pulAdcData       = &aulLocalRes[2];

  asLocalCfg[3].eInCh            = eADC_EXT_5;
  asLocalCfg[3].ucAdcInst        = 1u;
  asLocalCfg[3].ucAdcCh          = 17u;
  asLocalCfg[3].eInSelAdc        = eAdcExtCh13;
  asLocalCfg[3].boIntEnbl        = FALSE;
  asLocalCfg[3].pulAdcData       = &aulLocalRes[4];

  psAdcCfgData_Dummy.sAdcInstanceCfg.psAdcInstCfg  = &asLocalInstCfg[0];
  psAdcCfgData_Dummy.sAdcInstanceCfg.ucCfgLength   = 4u;
  psAdcCfgData_Dummy.sAdcInputChCfg.psAdcInCfg     = &asLocalCfg[0];
  psAdcCfgData_Dummy.sAdcInputChCfg.ucCfgLength    = 4u;

  //Step 2) Assign Input values
  Adc_Dma_InitDmaJob_Param1 = &psAdcCfgData_Dummy;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Dma_InitDmaJob_RetVal = Adc_Dma_InitDmaJob(Adc_Dma_InitDmaJob_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Dma_InitDmaJob_RetVal, E_NOT_OK, == );
  AL_UNITTEST_CHECK(CddDma_StartJob_HitCount, 0u       , == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Adc_Dma_SetDmaParam_TestCase1
///
/// \Test Case Description: Test ADC0 and ACD1 instance, find and count the valid channels.
///                         Return DMA source,destination and transfer length addresses
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input      asLocalInstCfg[0].ucAdcInst                               = 0u
/// \input      asLocalInstCfg[1].ucAdcInst                               = 1u
/// \input      asLocalCfg[0].eInCh                                       = eADC_EXT_2
/// \input      asLocalCfg[0].ucAdcInst                                   = 0u
/// \input      asLocalCfg[0].ucAdcCh                                     = 1u
/// \input      asLocalCfg[0].eInSelAdc                                   = eAdcExtCh9
/// \input      asLocalCfg[0].boIntEnbl                                   = FALSE
/// \input      asLocalCfg[0].pulAdcData                                  = &asLocalCfg[1]
/// \input      asLocalCfg[1].eInCh                                       = eADC_EXT_3
/// \input      asLocalCfg[1].ucAdcInst                                   = 1u
/// \input      asLocalCfg[1].ucAdcCh                                     = 0u
/// \input      asLocalCfg[1].eInSelAdc                                   = eAdcExtCh11
/// \input      asLocalCfg[1].boIntEnbl                                   = FALSE
/// \input      asLocalCfg[1].pulAdcData                                  = &asLocalCfg[3]
/// \input      asLocalCfg[2].eInCh                                       = eADC_EXT_1
/// \input      asLocalCfg[2].ucAdcInst                                   = 0u
/// \input      asLocalCfg[2].ucAdcCh                                     = 2u
/// \input      asLocalCfg[2].eInSelAdc                                   = eAdcExtCh10
/// \input      asLocalCfg[2].boIntEnbl                                   = FALSE
/// \input      asLocalCfg[2].pulAdcData                                  = &asLocalCfg[2]
/// \input      asLocalCfg[3].eInCh                                       = eADC_EXT_5
/// \input      asLocalCfg[3].ucAdcInst                                   = 1u
/// \input      asLocalCfg[3].ucAdcCh                                     = 1u
/// \input      asLocalCfg[3].eInSelAdc                                   = eAdcExtCh13
/// \input      asLocalCfg[3].boIntEnbl                                   = FALSE
/// \input      asLocalCfg[3].pulAdcData                                  = &asLocalCfg[4]
/// \input      Adc_Dma_SetDmaParam_Param1.sAdcInstanceCfg.ucCfgLength   = 2
/// \input      Adc_Dma_SetDmaParam_Param1.sAdcInputChCfg.psAdcInCfg     = &asLocalCfg[0]
/// \input      Adc_Dma_SetDmaParam_Param1.sAdcInputChCfg.ucCfgLength    = 4u
///
/// - Expectations: 
///
/// \output   Adc_Dma_SetDmaParam_Param2.pulAdc0Source                    = &Adc0_sReg.R[1]
/// \output   Adc_Dma_SetDmaParam_Param2.pulAdc0Target                    = &asLocalCfg[1]
/// \output   Adc_Dma_SetDmaParam_Param2.unAdc0DataSize                   = 2u
/// \output   Adc_Dma_SetDmaParam_Param2.pulAdc1Source                    = &Adc0_sReg.R[0]
/// \output   Adc_Dma_SetDmaParam_Param2.pulAdc1Target                    = &asLocalCfg[3]
/// \output   Adc_Dma_SetDmaParam_Param2.unAdc1DataSize                   = 2u
//-----------------------------------------------------------------------------
void Mt_Adc_Dma_SetDmaParam_TestCase1(void)
{
  tsAdc_AdcInputCfg    asLocalCfg[4];
  uint32               aulLocalRes[5];
  tsAdc_AdcInstanceCfg asLocalInstCfg[2];

  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  asLocalInstCfg[0].ucAdcInst                              = 0u;
  asLocalInstCfg[1].ucAdcInst                              = 1u;
                                                         
  asLocalCfg[0].eInCh                                      = eADC_EXT_2;
  asLocalCfg[0].ucAdcInst                                  = 0u;
  asLocalCfg[0].ucAdcCh                                    = 1u;
  asLocalCfg[0].eInSelAdc                                  = eAdcExtCh9;
  asLocalCfg[0].boIntEnbl                                  = FALSE;
  asLocalCfg[0].pulAdcData                                 = &aulLocalRes[1];
                                                         
  asLocalCfg[1].eInCh                                      = eADC_EXT_3;
  asLocalCfg[1].ucAdcInst                                  = 1u;
  asLocalCfg[1].ucAdcCh                                    = 0u;
  asLocalCfg[1].eInSelAdc                                  = eAdcExtCh11;
  asLocalCfg[1].boIntEnbl                                  = FALSE;
  asLocalCfg[1].pulAdcData                                 = &aulLocalRes[3];
                                                         
  asLocalCfg[2].eInCh                                      = eADC_EXT_1;
  asLocalCfg[2].ucAdcInst                                  = 0u;
  asLocalCfg[2].ucAdcCh                                    = 2u;
  asLocalCfg[2].eInSelAdc                                  = eAdcExtCh10;
  asLocalCfg[2].boIntEnbl                                  = FALSE;
  asLocalCfg[2].pulAdcData                                 = &aulLocalRes[2];
                                                         
  asLocalCfg[3].eInCh                                      = eADC_EXT_5;
  asLocalCfg[3].ucAdcInst                                  = 1u;
  asLocalCfg[3].ucAdcCh                                    = 1u;
  asLocalCfg[3].eInSelAdc                                  = eAdcExtCh13;
  asLocalCfg[3].boIntEnbl                                  = FALSE;
  asLocalCfg[3].pulAdcData                                 = &aulLocalRes[4];


  sAdc_Dma_SetDmaParam_Param1.sAdcInstanceCfg.psAdcInstCfg = &asLocalInstCfg[0];
  sAdc_Dma_SetDmaParam_Param1.sAdcInstanceCfg.ucCfgLength  = 2u;
  sAdc_Dma_SetDmaParam_Param1.sAdcInputChCfg.psAdcInCfg    = &asLocalCfg[0];
  sAdc_Dma_SetDmaParam_Param1.sAdcInputChCfg.ucCfgLength   = 4u;

  //Step 2) Assign Input values
  Adc_Dma_SetDmaParam_Param1 = &sAdc_Dma_SetDmaParam_Param1;
  Adc_Dma_SetDmaParam_Param2 = &sAdc_Dma_SetDmaParam_Param2;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Dma_SetDmaParam(Adc_Dma_SetDmaParam_Param1, Adc_Dma_SetDmaParam_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Dma_SetDmaParam_Param2->pulAdc0Source, &Adc0_sReg.R[1], == );
  AL_UNITTEST_CHECK(Adc_Dma_SetDmaParam_Param2->pulAdc0Target, &aulLocalRes[1], == );
  AL_UNITTEST_CHECK(Adc_Dma_SetDmaParam_Param2->unAdc0DataSize, 2u            , == );
  AL_UNITTEST_CHECK(Adc_Dma_SetDmaParam_Param2->pulAdc1Source, &Adc1_sReg.R[0], == );
  AL_UNITTEST_CHECK(Adc_Dma_SetDmaParam_Param2->pulAdc1Target, &aulLocalRes[3], == );
  AL_UNITTEST_CHECK(Adc_Dma_SetDmaParam_Param2->unAdc1DataSize, 2u            , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Adc_Dma_SetDmaParam_TestCase2
///
/// \Test Case Description: Test ACD0 and ACD1 instance, find and count the valid channels.
///                         Return DMA source,destination and transfer length addresses
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input      asLocalInstCfg[0].ucAdcInst                               = 0u
/// \input      asLocalInstCfg[1].ucAdcInst                               = 1u
/// \input      asLocalCfg[0].eInCh                                       = eADC_EXT_2
/// \input      asLocalCfg[0].ucAdcInst                                   = 0u
/// \input      asLocalCfg[0].ucAdcCh                                     = 255u
/// \input      asLocalCfg[0].eInSelAdc                                   = eAdcExtCh9
/// \input      asLocalCfg[0].boIntEnbl                                   = FALSE
/// \input      asLocalCfg[0].pulAdcData                                  = &asLocalCfg[1]
/// \input      asLocalCfg[1].eInCh                                       = eADC_EXT_3
/// \input      asLocalCfg[1].ucAdcInst                                   = 1u
/// \input      asLocalCfg[1].ucAdcCh                                     = 255u
/// \input      asLocalCfg[1].eInSelAdc                                   = eAdcExtCh11
/// \input      asLocalCfg[1].boIntEnbl                                   = FALSE
/// \input      asLocalCfg[1].pulAdcData                                  = &asLocalCfg[3]
/// \input      asLocalCfg[2].eInCh                                       = eADC_EXT_1
/// \input      asLocalCfg[2].ucAdcInst                                   = 0u
/// \input      asLocalCfg[2].ucAdcCh                                     = 255u
/// \input      asLocalCfg[2].eInSelAdc                                   = eAdcExtCh10
/// \input      asLocalCfg[2].boIntEnbl                                   = FALSE
/// \input      asLocalCfg[2].pulAdcData                                  = &asLocalCfg[2]
/// \input      asLocalCfg[3].eInCh                                       = eADC_EXT_5
/// \input      asLocalCfg[3].ucAdcInst                                   = 1u
/// \input      asLocalCfg[3].ucAdcCh                                     = 255u
/// \input      asLocalCfg[3].eInSelAdc                                   = eAdcExtCh13
/// \input      asLocalCfg[3].boIntEnbl                                   = FALSE
/// \input      asLocalCfg[3].pulAdcData                                  = &asLocalCfg[4]
/// \input      Adc_Dma_SetDmaParam_Param1.sAdcInstanceCfg.psAdcInstCfg   = &asLocalInstCfg[0]
/// \input      Adc_Dma_SetDmaParam_Param1.sAdcInstanceCfg.ucCfgLength    = 2u
/// \input      Adc_Dma_SetDmaParam_Param1.sAdcInputChCfg.psAdcInCfg      = &asLocalCfg[0]
/// \input      Adc_Dma_SetDmaParam_Param1.sAdcInputChCfg.ucCfgLength     = 4u
///
/// - Expectations: 
///
/// \output   Adc_Dma_SetDmaParam_Param2.pulAdc0Source                    = NULL_PTR
/// \output   Adc_Dma_SetDmaParam_Param2.pulAdc0Target                    = &asLocalCfg[1]
/// \output   Adc_Dma_SetDmaParam_Param2.unAdc0DataSize                   = NULL_PT
/// \output   Adc_Dma_SetDmaParam_Param2.pulAdc1Source                    = NULL_PTR
/// \output   Adc_Dma_SetDmaParam_Param2.pulAdc1Target                    = &asLocalCfg[3]
/// \output   Adc_Dma_SetDmaParam_Param2.unAdc1DataSize                   = NULL_PTR
//-----------------------------------------------------------------------------
void Mt_Adc_Dma_SetDmaParam_TestCase2(void)
{
  tsAdc_AdcInputCfg    asLocalCfg[4];
  uint32               aulLocalRes[5];
  tsAdc_AdcInstanceCfg asLocalInstCfg[2];

  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions                                                       
  asLocalInstCfg[0].ucAdcInst                              = 0u;
  asLocalInstCfg[1].ucAdcInst                              = 1u;
                                                       
  asLocalCfg[0].eInCh                                      = eADC_EXT_2;
  asLocalCfg[0].ucAdcInst                                  = 0u;
  asLocalCfg[0].ucAdcCh                                    = 255u;
  asLocalCfg[0].eInSelAdc                                  = eAdcExtCh9;
  asLocalCfg[0].boIntEnbl                                  = FALSE;
  asLocalCfg[0].pulAdcData                                 = &aulLocalRes[1];
                                                       
  asLocalCfg[1].eInCh                                      = eADC_EXT_3;
  asLocalCfg[1].ucAdcInst                                  = 1u;
  asLocalCfg[1].ucAdcCh                                    = 255u;
  asLocalCfg[1].eInSelAdc                                  = eAdcExtCh11;
  asLocalCfg[1].boIntEnbl                                  = FALSE;
  asLocalCfg[1].pulAdcData                                 = &aulLocalRes[3];
                                                       
  asLocalCfg[2].eInCh                                      = eADC_EXT_1;
  asLocalCfg[2].ucAdcInst                                  = 0u;
  asLocalCfg[2].ucAdcCh                                    = 255u;
  asLocalCfg[2].eInSelAdc                                  = eAdcExtCh10;
  asLocalCfg[2].boIntEnbl                                  = FALSE;
  asLocalCfg[2].pulAdcData                                 = &aulLocalRes[2];
                                                       
  asLocalCfg[3].eInCh                                      = eADC_EXT_5;
  asLocalCfg[3].ucAdcInst                                  = 1u;
  asLocalCfg[3].ucAdcCh                                    = 255u;
  asLocalCfg[3].eInSelAdc                                  = eAdcExtCh13;
  asLocalCfg[3].boIntEnbl                                  = FALSE;
  asLocalCfg[3].pulAdcData                                 = &aulLocalRes[4];

  sAdc_Dma_SetDmaParam_Param1.sAdcInstanceCfg.psAdcInstCfg = &asLocalInstCfg[0];
  sAdc_Dma_SetDmaParam_Param1.sAdcInstanceCfg.ucCfgLength  = 2u;
  sAdc_Dma_SetDmaParam_Param1.sAdcInputChCfg.psAdcInCfg    = &asLocalCfg[0];
  sAdc_Dma_SetDmaParam_Param1.sAdcInputChCfg.ucCfgLength   = 4u;
  
  //Step 2) Assign Input values
  Adc_Dma_SetDmaParam_Param1 = &sAdc_Dma_SetDmaParam_Param1;
  Adc_Dma_SetDmaParam_Param2 = &sAdc_Dma_SetDmaParam_Param2;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Dma_SetDmaParam(Adc_Dma_SetDmaParam_Param1, Adc_Dma_SetDmaParam_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Dma_SetDmaParam_Param2->pulAdc0Source, NULL_PTR       , == );
  AL_UNITTEST_CHECK(Adc_Dma_SetDmaParam_Param2->pulAdc0Target, NULL_PTR       , == );
  AL_UNITTEST_CHECK(Adc_Dma_SetDmaParam_Param2->unAdc0DataSize,0u             , == );
  AL_UNITTEST_CHECK(Adc_Dma_SetDmaParam_Param2->pulAdc1Source, NULL_PTR       , == );
  AL_UNITTEST_CHECK(Adc_Dma_SetDmaParam_Param2->pulAdc1Target, NULL_PTR       , == );
  AL_UNITTEST_CHECK(Adc_Dma_SetDmaParam_Param2->unAdc1DataSize, 0u            , == );
}

//Adc_Drv.c:

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Adc_Drv_InitAdc_TestCase1
///
/// \Test Case Description: ADC driver initialization - EOL calibration failed
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input      asLocalInstCfg[0].ucAdcInst                         = 0u
/// \input      asLocalInstCfg[0].boEolCalib                        = FALSE
/// \input      asLocalInstCfg[0].pfCalibrationParm                 = Adc_EolCalibration_ADC0
/// \input      Adc_EolCalibration_ADC0_Param1                      = NULL_PTR
/// \input      Adc_EolCalibration_ADC0_RetVal                      = FALSE
/// \input      Adc_EolCalibration_ADC0_HitCount                    = 0u
/// \input      asLocalCfg[0].eInCh                                 = eADC_EXT_2
/// \input      asLocalCfg[0].ucAdcInst                             = 0u
/// \input      asLocalCfg[0].ucAdcCh                               = 1u
/// \input      asLocalCfg[0].eInSelAdc                             = eAdcExtCh9
/// \input      asLocalCfg[0].boIntEnbl                             = FALSE
/// \input      asLocalCfg[0].pulAdcData                            = &aulLocalRes[1]
/// \input      Adc_Drv_InitAdc_Param1.sAdcInstanceCfg.psAdcInstCfg = &asLocalInstCfg[0]
/// \input      Adc_Drv_InitAdc_Param1.sAdcInstanceCfg.ucCfgLength  = 2u
/// \input      Adc_Drv_InitAdc_Param1.sAdcInputChCfg.psAdcInCfg    = &asLocalCfg[0]
/// \input      Adc_Drv_InitAdc_Param1.sAdcInputChCfg.ucCfgLength   = 4u
///
/// - Expectations: 
///
/// \output   Adc_Drv_psInputMap->psAdcInCfg  == Adc_Drv_InitAdc_Param1.sAdcInputChCfg.psAdcInCfg
/// \output   Adc_Drv_psInputMap->ucCfgLength == Adc_Drv_InitAdc_Param1.sAdcInputChCfg.ucCfgLength
/// \output   Adc_EolCalibration_ADC0_HitCount == 0u
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_InitAdc_TestCase1()
{
  tsAdc_AdcInputCfg asLocalCfg[1];
  uint32 aulLocalRes[5];
  tsAdc_AdcInstanceCfg asLocalInstCfg[1];

  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  asLocalInstCfg[0].ucAdcInst                         = 0u;
  asLocalInstCfg[0].boEolCalib                        = FALSE;
  asLocalInstCfg[0].pfCalibrationParm                 = Adc_EolCalibration_ADC0;
  Adc_EolCalibration_ADC0_Param1                      = NULL_PTR;
  Adc_EolCalibration_ADC0_RetVal                      = FALSE;
  Adc_EolCalibration_ADC0_HitCount                    = 0u;
  asLocalCfg[0].eInCh                                 = eADC_EXT_2;
  asLocalCfg[0].ucAdcInst                             = 0u;
  asLocalCfg[0].ucAdcCh                               = 1u;
  asLocalCfg[0].eInSelAdc                             = eAdcExtCh9;
  asLocalCfg[0].boIntEnbl                             = FALSE;
  asLocalCfg[0].pulAdcData                            = &aulLocalRes[1];
  psAdcCfgData_Dummy.sAdcInstanceCfg.psAdcInstCfg     = &asLocalInstCfg[0];
  psAdcCfgData_Dummy.sAdcInstanceCfg.ucCfgLength      = 2u;
  psAdcCfgData_Dummy.sAdcInputChCfg.psAdcInCfg        = &asLocalCfg[0];
  psAdcCfgData_Dummy.sAdcInputChCfg.ucCfgLength       = 4u;

  //Step 2) Assign Input values
  Adc_Drv_InitAdc_Param1 = &psAdcCfgData_Dummy;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_InitAdc(Adc_Drv_InitAdc_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_psInputMap->psAdcInCfg,  Adc_Drv_InitAdc_Param1->sAdcInputChCfg.psAdcInCfg  , == );
  AL_UNITTEST_CHECK(Adc_Drv_psInputMap->ucCfgLength, Adc_Drv_InitAdc_Param1->sAdcInputChCfg.ucCfgLength , == );
  AL_UNITTEST_CHECK(Adc_EolCalibration_ADC0_HitCount, 0u , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Adc_Drv_InitAdc_TestCase2
///
/// \Test Case Description: ADC driver initialization - EOL + SELF calibration branches reached - Calibration failed totaly
///
/// - Preconditions:
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// \input      asLocalInstCfg[0].ucAdcInst                         = 3u
/// \input      asLocalInstCfg[0].boEolCalib                        = TRUE
/// \input      asLocalInstCfg[0].pfCalibrationParm                 = Adc_EolCalibration_ADC1
/// \input      Adc_EolCalibration_ADC0_Param1                      = NULL_PTR
/// \input      Adc_EolCalibration_ADC0_RetVal                      = FALSE
/// \input      Adc_EolCalibration_ADC0_HitCount                    = 0u
/// \input      asLocalCfg[0].ucAdcInst                             = 0u
/// \input      asLocalCfg[0].eInCh                                 = eADC_EXT_2
/// \input      asLocalCfg[0].ucAdcInst                             = 0u
/// \input      asLocalCfg[0].ucAdcCh                               = 1u
/// \input      asLocalCfg[0].eInSelAdc                             = eAdcExtCh9
/// \input      asLocalCfg[0].boIntEnbl                             = FALSE
/// \input      asLocalCfg[0].pulAdcData                            = &aulLocalRes[1]
/// \input      Adc_Drv_InitAdc_Param1.sAdcInstanceCfg.psAdcInstCfg = &asLocalInstCfg[0]
/// \input      Adc_Drv_InitAdc_Param1.sAdcInstanceCfg.ucCfgLength  = 2u
/// \input      Adc_Drv_InitAdc_Param1.sAdcInputChCfg.psAdcInCfg    = &asLocalCfg[0]
/// \input      Adc_Drv_InitAdc_Param1.sAdcInputChCfg.ucCfgLength   = 4u
///
/// - Expectations: 
///
/// \output   Adc_Drv_psInputMap->psAdcInCfg  == Adc_Drv_InitAdc_Param1.sAdcInputChCfg.psAdcInCfg
/// \output   Adc_Drv_psInputMap->ucCfgLength == Adc_Drv_InitAdc_Param1.sAdcInputChCfg.ucCfgLength
/// \output   Adc_EolCalibration_ADC0_HitCount == 0u
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_InitAdc_TestCase2()
{
  tsAdc_AdcInputCfg asLocalCfg[1];
  uint32 aulLocalRes[5];
  tsAdc_AdcInstanceCfg asLocalInstCfg[1];

  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  asLocalInstCfg[0].ucAdcInst = 3u;
  asLocalInstCfg[0].boEolCalib = TRUE;
  asLocalInstCfg[0].pfCalibrationParm = Adc_EolCalibration_ADC0;
  Adc_EolCalibration_ADC0_Param1 = NULL_PTR;
  Adc_EolCalibration_ADC0_RetVal = FALSE;
  Adc_EolCalibration_ADC0_HitCount = 0u;
  asLocalCfg[0].eInCh = eADC_EXT_2;
  asLocalCfg[0].ucAdcInst = 0u;
  asLocalCfg[0].ucAdcCh = 1u;
  asLocalCfg[0].eInSelAdc = eAdcExtCh9;
  asLocalCfg[0].boIntEnbl = FALSE;
  asLocalCfg[0].pulAdcData = &aulLocalRes[1];
  psAdcCfgData_Dummy.sAdcInstanceCfg.psAdcInstCfg = &asLocalInstCfg[0];
  psAdcCfgData_Dummy.sAdcInstanceCfg.ucCfgLength = 2u;
  psAdcCfgData_Dummy.sAdcInputChCfg.psAdcInCfg = &asLocalCfg[0];
  psAdcCfgData_Dummy.sAdcInputChCfg.ucCfgLength = 4u;

  //Step 2) Assign Input values
  Adc_Drv_InitAdc_Param1 = &psAdcCfgData_Dummy;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_InitAdc(Adc_Drv_InitAdc_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_psInputMap->psAdcInCfg, Adc_Drv_InitAdc_Param1->sAdcInputChCfg.psAdcInCfg, == );
  AL_UNITTEST_CHECK(Adc_Drv_psInputMap->ucCfgLength, Adc_Drv_InitAdc_Param1->sAdcInputChCfg.ucCfgLength, == );
  AL_UNITTEST_CHECK(Adc_EolCalibration_ADC0_HitCount, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Adc_Drv_InitAdc_TestCase3
///
/// \Test Case Description: ADC driver initialization - EOL  calibration branches reached - EOL Calibration passed
///
/// - Preconditions:
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// \input      asLocalInstCfg[0].ucAdcInst                         = 0u
/// \input      asLocalInstCfg[0].boEolCalib                        = TRUE
/// \input      asLocalInstCfg[0].pfCalibrationParm                 = Adc_EolCalibration_ADC1
/// \input      Adc_EolCalibration_ADC0_Param1                      = &Adc0_Eft_Data[0]
/// \input      Adc_EolCalibration_ADC0_RetVal                      = TRUE
/// \input      Adc_EolCalibration_ADC0_HitCount                    = 0u
/// \input      asLocalCfg[0].ucAdcInst                             = 0u
/// \input      asLocalCfg[0].eInCh                                 = eADC_EXT_2
/// \input      asLocalCfg[0].ucAdcInst                             = 0u
/// \input      asLocalCfg[0].ucAdcCh                               = 1u
/// \input      asLocalCfg[0].eInSelAdc                             = eAdcExtCh9
/// \input      asLocalCfg[0].boIntEnbl                             = FALSE
/// \input      asLocalCfg[0].pulAdcData                            = &aulLocalRes[1]
/// \input      Adc_Drv_InitAdc_Param1.sAdcInstanceCfg.psAdcInstCfg = &asLocalInstCfg[0]
/// \input      Adc_Drv_InitAdc_Param1.sAdcInstanceCfg.ucCfgLength  = 2u
/// \input      Adc_Drv_InitAdc_Param1.sAdcInputChCfg.psAdcInCfg    = &asLocalCfg[0]
/// \input      Adc_Drv_InitAdc_Param1.sAdcInputChCfg.ucCfgLength   = 4u
///
/// - Expectations: 
///
/// \output   Adc_Drv_psInputMap->psAdcInCfg  == Adc_Drv_InitAdc_Param1.sAdcInputChCfg.psAdcInCfg
/// \output   Adc_Drv_psInputMap->ucCfgLength == Adc_Drv_InitAdc_Param1.sAdcInputChCfg.ucCfgLength
/// \output   Adc_EolCalibration_ADC0_HitCount == 1u
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_InitAdc_TestCase3()
{
  tsAdc_AdcInputCfg asLocalCfg[1];
  uint32 aulLocalRes[5];
  tsAdc_AdcInstanceCfg asLocalInstCfg[1];

  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  asLocalInstCfg[0].ucAdcInst = 0u;
  asLocalInstCfg[0].boEolCalib = TRUE;
  asLocalInstCfg[0].pfCalibrationParm = Adc_EolCalibration_ADC0;
  Adc_EolCalibration_ADC0_Param1 = &Adc0_Eft_Data[0];
  Adc_EolCalibration_ADC0_RetVal = TRUE;
  Adc_EolCalibration_ADC0_HitCount = 0u;
  asLocalCfg[0].eInCh = eADC_EXT_2;
  asLocalCfg[0].ucAdcInst = 0u;
  asLocalCfg[0].ucAdcCh = 1u;
  asLocalCfg[0].eInSelAdc = eAdcExtCh9;
  asLocalCfg[0].boIntEnbl = FALSE;
  asLocalCfg[0].pulAdcData = &aulLocalRes[1];
  psAdcCfgData_Dummy.sAdcInstanceCfg.psAdcInstCfg = &asLocalInstCfg[0];
  psAdcCfgData_Dummy.sAdcInstanceCfg.ucCfgLength = 2u;
  psAdcCfgData_Dummy.sAdcInputChCfg.psAdcInCfg = &asLocalCfg[0];
  psAdcCfgData_Dummy.sAdcInputChCfg.ucCfgLength = 4u;

  //Step 2) Assign Input values
  Adc_Drv_InitAdc_Param1 = &psAdcCfgData_Dummy;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_InitAdc(Adc_Drv_InitAdc_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_psInputMap->psAdcInCfg, Adc_Drv_InitAdc_Param1->sAdcInputChCfg.psAdcInCfg, == );
  AL_UNITTEST_CHECK(Adc_Drv_psInputMap->ucCfgLength, Adc_Drv_InitAdc_Param1->sAdcInputChCfg.ucCfgLength, == );
  AL_UNITTEST_CHECK(Adc_EolCalibration_ADC0_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Adc_Drv_ConfigAdc_TestCase1
///
/// \Test Case Description: Test if supply voltage or ADC instance is invalid 
///                         if clocking condition is not met
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input    Adc_Drv_ConfigAdc_Param1.eClkDiv                    = eADC_CLK_DIVIDE_1
/// \input    Adc_Drv_ConfigAdc_Param1.ucAdcInst                  = 2u
/// \input    Adc_Drv_ConfigAdc_Param1.boSupplyMonitoringEnable   = FALSE
///
/// - Expectations: 
///
/// \output   Adc_Drv_ConfigAdc_RetVal                            = E_NOT_OK
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_ConfigAdc_TestCase1()
{
   //-----------------------------------------------------------------------------
   // Inputs
   //-----------------------------------------------------------------------------

   //Step 1) Set pre-conditions
   Adc_Drv_ConfigAdc_Param1_Dummy.eClkDiv                  = eADC_CLK_DIVIDE_1;
   Adc_Drv_ConfigAdc_Param1_Dummy.ucAdcInst                = 2u;
   Adc_Drv_ConfigAdc_Param1_Dummy.boSupplyMonitoringEnable = FALSE;

   //Step 2) Assign Input values
   Adc_Drv_ConfigAdc_Param1 = &Adc_Drv_ConfigAdc_Param1_Dummy;

   //-----------------------------------------------------------------------------
   // Function call
   //-----------------------------------------------------------------------------

   //Step 3) Call FUT
   Adc_Drv_ConfigAdc_RetVal = Adc_Drv_ConfigAdc(Adc_Drv_ConfigAdc_Param1);

   //-----------------------------------------------------------------------------
   // Outputs
   //-----------------------------------------------------------------------------

   //Step 4) Check expected output values
   AL_UNITTEST_CHECK(Adc_Drv_ConfigAdc_RetVal, E_NOT_OK, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Adc_Drv_ConfigAdc_TestCase2
///
/// \Test Case Description: Test if supply voltage or ADC instance is valid 
///                         if clocking condition is met
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input    Adc_Drv_ConfigAdc_Param1.ucAdcInst                  = 0u
/// \input    Adc_Drv_ConfigAdc_Param1.boSupplyMonitoringEnable   = TRUE
/// \input    Adc_Drv_ConfigAdc_Param1.eClkDiv                    = eADC_CLK_DIVIDE_2
/// \input    Adc_Drv_ConfigAdc_Param1.boAvgEnable                = TRUE
/// \input    Adc_Drv_ConfigAdc_Param1.boContinuousConvEnable     = FALSE
/// \input    Adc_Drv_ConfigAdc_Param1.boDmaEnable                = FALSE
/// \input    Adc_Drv_ConfigAdc_Param1.eAverageCfg                = eADC_AVERAGE_4
/// \input    Adc_Drv_ConfigAdc_Param1.eInputClock                = eADC_CLK_ALT_1
/// \input    Adc_Drv_ConfigAdc_Param1.ePreTriggerSel             = eADC_PRETRIGGER_SEL_PDB
/// \input    Adc_Drv_ConfigAdc_Param1.eResolution                = eADC_RESOLUTION_8BIT
/// \input    Adc_Drv_ConfigAdc_Param1.boAvgEnable                = FALSE
///
/// - Expectations: 
///
/// \output   Adc_Drv_ConfigAdc_RetVal                            = E_OK
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_ConfigAdc_TestCase2()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc_Drv_ConfigAdc_Param1_Dummy.ucAdcInst                               = 0u;
  Adc_Drv_ConfigAdc_Param1_Dummy.boSupplyMonitoringEnable                = TRUE;
  Adc_Drv_ConfigAdc_Param1_Dummy.eClkDiv                                 = eADC_CLK_DIVIDE_2;
  Adc_Drv_ConfigAdc_Param1_Dummy.boAvgEnable                             = TRUE;
  Adc_Drv_ConfigAdc_Param1_Dummy.boContinuousConvEnable                  = FALSE;
  Adc_Drv_ConfigAdc_Param1_Dummy.boDmaEnable                             = FALSE;
  Adc_Drv_ConfigAdc_Param1_Dummy.eAverageCfg                             = eADC_AVERAGE_4;
  Adc_Drv_ConfigAdc_Param1_Dummy.eInputClock                             = eADC_CLK_ALT_1;
  Adc_Drv_ConfigAdc_Param1_Dummy.ePreTriggerSel                          = eADC_PRETRIGGER_SEL_PDB;
  Adc_Drv_ConfigAdc_Param1_Dummy.eResolution                             = eADC_RESOLUTION_8BIT;
  Adc_Drv_ConfigAdc_Param1_Dummy.boAvgEnable                             = FALSE;

  //Step 2) Assign Input values
  Adc_Drv_ConfigAdc_Param1 = &Adc_Drv_ConfigAdc_Param1_Dummy;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_ConfigAdc_RetVal = Adc_Drv_ConfigAdc(Adc_Drv_ConfigAdc_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_ConfigAdc_RetVal, E_OK, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Adc_Drv_ConfigAdc_TestCase3
///
/// \Test Case Description: Test if supply voltage or ADC instance is valid if 
///                         clocking condition is met and check the following initializations:
///                         1. Adc instance clock divide initialization
///                         2. Adc sample time initialization
///                         3. Adc resolution initialization
///                         4. Adc input clock initialization
///                         5. Adc input trigger initialization
///                         6. Adc trigger select initialization
///                         7. Adc pretrigger select initialization
///                         8. Adc DMA config initialization
///                         9. Adc reference initialization
///                         10.Adc average conversion config
///                         11.Adc continous convertion initialization
///                         12.Adc supply monitoring configuration only for ADC0
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input    Adc_Drv_ConfigAdc_Param1.eClkDiv                    = eADC_CLK_DIVIDE_2
/// \input    Adc_Drv_ConfigAdc_Param1.ucAdcInst                  = 1u
/// \input    Adc_Drv_ConfigAdc_Param1.boSupplyMonitoringEnable   = FALSE
/// \input    Adc_Drv_ConfigAdc_Param1.ulSampleTime               = 10u
/// \input    Adc_Drv_ConfigAdc_Param1.eResolution                = eADC_RESOLUTION_12BIT
/// \input    Adc_Drv_ConfigAdc_Param1.eInputClock                = eADC_CLK_ALT_2
/// \input    Adc_Drv_ConfigAdc_Param1.eTrigger                   = eADC_TRIGGER_SOFTWARE
/// \input    Adc_Drv_ConfigAdc_Param1.eTriggerSel                = eADC_TRIGGER_SEL_TRGMUX
/// \input    Adc_Drv_ConfigAdc_Param1.ePreTriggerSel             = eADC_PRETRIGGER_SEL_TRGMUX
/// \input    Adc_Drv_ConfigAdc_Param1.boDmaEnable                = TRUE
/// \input    Adc_Drv_ConfigAdc_Param1.eVoltageRef                = eADC_VOLTAGEREF_VALT
/// \input    Adc_Drv_ConfigAdc_Param1.eAverageCfg                = eADC_AVERAGE_16
/// \input    Adc_Drv_ConfigAdc_Param1.boContinuousConvEnable     = TRUE
/// \input    Adc_Drv_ConfigAdc_Param1.boAvgEnable                = TRUE
///
/// - Expectations: 
///
/// \output   Adc_Drv_ConfigAdc_RetVal                            = E_OK
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_ConfigAdc_TestCase3()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc_Drv_ConfigAdc_Param1_Dummy.ucAdcInst                              = 1u;
  Adc_Drv_ConfigAdc_Param1_Dummy.boSupplyMonitoringEnable               = FALSE;
  Adc_Drv_ConfigAdc_Param1_Dummy.eClkDiv                                = eADC_CLK_DIVIDE_2;
  Adc_Drv_ConfigAdc_Param1_Dummy.ulSampleTime                           = 10u;
  Adc_Drv_ConfigAdc_Param1_Dummy.eResolution                            = eADC_RESOLUTION_12BIT;
  Adc_Drv_ConfigAdc_Param1_Dummy.eInputClock                            = eADC_CLK_ALT_2;
  Adc_Drv_ConfigAdc_Param1_Dummy.eTrigger                               = eADC_TRIGGER_SOFTWARE;
  Adc_Drv_ConfigAdc_Param1_Dummy.eTriggerSel                            = eADC_TRIGGER_SEL_TRGMUX;
  Adc_Drv_ConfigAdc_Param1_Dummy.ePreTriggerSel                         = eADC_PRETRIGGER_SEL_TRGMUX;
  Adc_Drv_ConfigAdc_Param1_Dummy.boDmaEnable                            = TRUE;
  Adc_Drv_ConfigAdc_Param1_Dummy.eVoltageRef                            = eADC_VOLTAGEREF_VALT;
  Adc_Drv_ConfigAdc_Param1_Dummy.eAverageCfg                            = eADC_AVERAGE_16;
  Adc_Drv_ConfigAdc_Param1_Dummy.boContinuousConvEnable                 = TRUE;
  Adc_Drv_ConfigAdc_Param1_Dummy.boAvgEnable                            = TRUE;

  //Step 2) Assign Input values
  Adc_Drv_ConfigAdc_Param1 = &Adc_Drv_ConfigAdc_Param1_Dummy;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_ConfigAdc_RetVal = Adc_Drv_ConfigAdc(Adc_Drv_ConfigAdc_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_ConfigAdc_RetVal, E_OK, == );
}
  
// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_AutoCalibration_TestCase1
///
/// \Test Case Description: Return status not ok for input out of range
///
/// - Preconditions:
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// \input        Adc_Drv_AutoCalibration_Param1.ucAdcInst = 2u
/// \input        Adc_Drv_AutoCalibration_Param1           = &Adc_Drv_AutoCalibration_Param1_Dummy
///
/// - Expectations: 
///
/// \output   Adc_Drv_AutoCalibration_RetVal               = E_NOT_OK
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_AutoCalibration_TestCase1()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  //Step 1) Set pre-conditions
  Adc_Drv_AutoCalibration_Param1_Dummy.ucAdcInst = 2u;

  //Step 2) Assign Input values
  Adc_Drv_AutoCalibration_Param1 = &Adc_Drv_AutoCalibration_Param1_Dummy;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_AutoCalibration_RetVal = Adc_Drv_AutoCalibration(Adc_Drv_AutoCalibration_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_AutoCalibration_RetVal, E_NOT_OK, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_AutoCalibration_TestCase2
///
/// \Test Case Description: Return status not ok and set clock divider for
///                          auto calibration standard procedure
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input      Adc_Drv_AutoCalibration_Param1           = &Adc_Drv_AutoCalibration_Param1_Dummy
/// \input      Adc_Drv_AutoCalibration_Param1.ucAdcInst = 0u
/// \input      Adc_Drv_AutoCalibration_Param1.ulAdcFreq = 10000000u
/// \input      Adc0_sReg.CFG1                           = 2u
/// \input      Adc0_sReg.SC3                            = 1u
/// \input      Adc0_sReg.SC2                            = 1u
///
/// - Expectations: 
///
/// \output    Adc_Drv_AutoCalibration_RetVal            = E_NOT_OK
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_AutoCalibration_TestCase2()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc_Drv_AutoCalibration_Param1_Dummy.ucAdcInst        = 0u;
  Adc_Drv_AutoCalibration_Param1_Dummy.ulAdcFreq        = 10000000u;//first if true
  Adc0_sReg.CFG1                                        = 2u;
  Adc0_sReg.SC3                                         = 1u;
  Adc0_sReg.SC2                                         = 1u;

  //Step 2) Assign Input values
  Adc_Drv_AutoCalibration_Param1 = &Adc_Drv_AutoCalibration_Param1_Dummy;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_AutoCalibration_RetVal = Adc_Drv_AutoCalibration(Adc_Drv_AutoCalibration_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_AutoCalibration_RetVal, E_NOT_OK, == );
}
  
// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_AutoCalibration_TestCase3
///
/// \Test Case Description: Return status not ok and set clock divider for
///                          auto calibration standard procedure
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input      Adc_Drv_AutoCalibration_Param1           = &Adc_Drv_AutoCalibration_Param1_Dummy
/// \input      Adc_Drv_AutoCalibration_Param1.ucAdcInst = 0u
/// \input      Adc_Drv_AutoCalibration_Param1.ulAdcFreq = 30000000u
/// \input      Adc0_sReg.CFG1                           = 1u
/// \input      Adc0_sReg.SC3                            = 2u
/// \input      Adc0_sReg.SC2                            = 1u
///
/// - Expectations: 
///
/// \output    Adc_Drv_AutoCalibration_RetVal            = E_NOT_OK
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_AutoCalibration_TestCase3()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc_Drv_AutoCalibration_Param1_Dummy.ucAdcInst        = 0u;
  Adc_Drv_AutoCalibration_Param1_Dummy.ulAdcFreq        = 30000000u;// first else if true
  Adc0_sReg.CFG1                                        = 1u;
  Adc0_sReg.SC3                                         = 2u;
  Adc0_sReg.SC2                                         = 1u;

  //Step 2) Assign Input values
  Adc_Drv_AutoCalibration_Param1 = &Adc_Drv_AutoCalibration_Param1_Dummy;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_AutoCalibration_RetVal = Adc_Drv_AutoCalibration(Adc_Drv_AutoCalibration_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_AutoCalibration_RetVal, E_NOT_OK, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_AutoCalibration_TestCase4
///
/// \Test Case Description: Return status not ok and set clock divider for
///                          auto calibration standard procedure
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input      Adc_Drv_AutoCalibration_Param1.ucAdcInst = 0u
/// \input      Adc_Drv_AutoCalibration_Param1.ulAdcFreq = 60000000u
/// \input      Adc0_sReg.CFG1                           = 1u
/// \input      Adc0_sReg.SC3                            = 3u
/// \input      Adc0_sReg.SC2                            = 1u
///
/// - Expectations: 
///
/// \output    Adc_Drv_AutoCalibration_RetVal            = E_NOT_OK
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_AutoCalibration_TestCase4()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc_Drv_AutoCalibration_Param1_Dummy.ucAdcInst        = 0u;
  Adc_Drv_AutoCalibration_Param1_Dummy.ulAdcFreq        = 60000000u; // second else if true
  Adc0_sReg.CFG1                                        = 1u;
  Adc0_sReg.SC3                                         = 3u;
  Adc0_sReg.SC2                                         = 1u;

  //Step 2) Assign Input values
  Adc_Drv_AutoCalibration_Param1 = &Adc_Drv_AutoCalibration_Param1_Dummy;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_AutoCalibration_RetVal = Adc_Drv_AutoCalibration(Adc_Drv_AutoCalibration_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_AutoCalibration_RetVal, E_NOT_OK, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_AutoCalibration_TestCase5
///
/// \Test Case Description: Return status not ok and set clock divider for
///                          auto calibration standard procedure
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input      Adc_Drv_AutoCalibration_Param1.ucAdcInst = 0u
/// \input      Adc_Drv_AutoCalibration_Param1.ulAdcFreq = 1100000000u
/// \input      Adc0_sReg.CFG1                           = 1u
/// \input      Adc0_sReg.SC3                            = 4u
/// \input      Adc0_sReg.SC2                            = 1u
///
/// - Expectations: 
///
/// \output    Adc_Drv_AutoCalibration_RetVal            = E_NOT_OK
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_AutoCalibration_TestCase5()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc_Drv_AutoCalibration_Param1_Dummy.ucAdcInst        = 0u;
  Adc_Drv_AutoCalibration_Param1_Dummy.ulAdcFreq        = 1100000000u; // third else if true
  Adc0_sReg.CFG1                                        = 1u;
  Adc0_sReg.SC3                                         = 4u;
  Adc0_sReg.SC2                                         = 1u;

  //Step 2) Assign Input values
  Adc_Drv_AutoCalibration_Param1 = &Adc_Drv_AutoCalibration_Param1_Dummy;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_AutoCalibration_RetVal = Adc_Drv_AutoCalibration(Adc_Drv_AutoCalibration_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_AutoCalibration_RetVal, E_NOT_OK, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_AutoCalibration_TestCase6
///
/// \Test Case Description: Return status not ok and set clock divider for
///                          auto calibration standard procedure
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input      Adc_Drv_AutoCalibration_Param1.ucAdcInst = 0u
/// \input      Adc_Drv_AutoCalibration_Param1.ulAdcFreq = 250000000u
/// \input      Adc0_sReg.CFG1                           = 1u
/// \input      Adc0_sReg.SC3                            = 5u
/// \input      Adc0_sReg.SC2                            = 1u
///
/// - Expectations: 
///
/// \output    Adc_Drv_AutoCalibration_RetVal            = E_NOT_OK
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_AutoCalibration_TestCase6()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc_Drv_AutoCalibration_Param1_Dummy.ucAdcInst        = 0u;
  Adc_Drv_AutoCalibration_Param1_Dummy.ulAdcFreq        = 250000000u;  // third else if false
  Adc0_sReg.CFG1                                        = 1u;
  Adc0_sReg.SC3                                         = 5u;
  Adc0_sReg.SC2                                         = 1u;

  //Step 2) Assign Input values
  Adc_Drv_AutoCalibration_Param1 = &Adc_Drv_AutoCalibration_Param1_Dummy;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_AutoCalibration_RetVal = Adc_Drv_AutoCalibration(Adc_Drv_AutoCalibration_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_AutoCalibration_RetVal, E_NOT_OK, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_AutoCalibration_TestCase7
///
/// \Test Case Description: Return status not ok and set clock divider for
///                          auto calibration standard procedure
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input      Adc_Drv_AutoCalibration_Param1.ucAdcInst = 0u
/// \input      Adc_Drv_AutoCalibration_Param1.ulAdcFreq = 160000000u
/// \input      Adc0_sReg.CFG1                           = 1u
/// \input      Adc0_sReg.SC3                            = 6u
/// \input      Adc0_sReg.SC2                            = 1u
///
/// - Expectations: 
///
/// \output    Adc_Drv_AutoCalibration_RetVal            = E_NOT_OK
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_AutoCalibration_TestCase7()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc_Drv_AutoCalibration_Param1_Dummy.ucAdcInst        = 0u;
  Adc_Drv_AutoCalibration_Param1_Dummy.ulAdcFreq        = 160000000u;// third else if true
  Adc0_sReg.CFG1                                        = 1u;
  Adc0_sReg.SC3                                         = 6u;
  Adc0_sReg.SC2                                         = 1u;

  //Step 2) Assign Input values
  Adc_Drv_AutoCalibration_Param1 = &Adc_Drv_AutoCalibration_Param1_Dummy;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_AutoCalibration_RetVal = Adc_Drv_AutoCalibration(Adc_Drv_AutoCalibration_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_AutoCalibration_RetVal, E_NOT_OK, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_AutoCalibration_TestCase8
///
/// \Test Case Description: Microcontroller register 1 access
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input      Adc_Drv_AutoCalibration_Param1.ucAdcInst = 1u
/// \input      ADC1->CFG2                               = 7u
/// \input      ADC1->SC2                                = 112u
///
/// - Expectations: 
///
/// \output    Adc_Drv_AutoCalibration_RetVal           = E_NOT_OK
/// \output    ADC1->CFG2                               = 7u
/// \output    ADC1->SC2                                = 112u
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_AutoCalibration_TestCase8()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc_Drv_AutoCalibration_Param1_Dummy.ucAdcInst                 = 1u;
  ADC1->CFG2                                                     = 7u;
  ADC1->SC2                                                      = 112u;

  //Step 2) Assign Input values
  Adc_Drv_AutoCalibration_Param1 = &Adc_Drv_AutoCalibration_Param1_Dummy;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_AutoCalibration_RetVal = Adc_Drv_AutoCalibration(Adc_Drv_AutoCalibration_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_AutoCalibration_RetVal, E_NOT_OK , == );
  AL_UNITTEST_CHECK(ADC1->CFG2, 7u                           , == );
  AL_UNITTEST_CHECK(ADC1->SC2, 112u                          , == );
}
  
// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_AdcChInit_TestCase1
///
/// \Test Case Description: ADC channels init procedure avoided due to NULL input
///                         config parameter
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input         Temp0       = *ADC0
/// \input         Temp1       = *ADC1
///
/// - Expectations: 
///
/// \output       Temp0.aR[0]  = ADC0->aR[0]
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_AdcChInit_TestCase1()
{
  ADC_Type Temp0, Temp1;

  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Temp0 = *ADC0;
  Temp1 = *ADC1;

  //Step 2) Assign Input values
  //-----

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_AdcChInit(NULL);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Temp0.aR[0], ADC0->aR[0], == );
}
  
// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_AdcChInit_TestCase2
///
/// \Test Case Description: ADC channels init procedure
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input        Adc_Drv_AdcChInit_Param1.ucAdcCh                 = 1u
/// \input        Adc_Drv_AdcChInit_Param1.eInCh                   = eADC_EXT_2
/// \input        Adc0_sReg.SC1[Adc_Drv_AdcChInit_Param1->ucAdcCh] = 0b 0000 0000 0000 0000 1000 0000 11[11 0000]
///
/// - Expectations: 
///
/// \output       Adc0_sReg.SC1[Adc_Drv_AdcChInit_Param1->ucAdcCh] = 0b 0000 0000 0000 0000 1000 0000 11[00 0010]
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_AdcChInit_TestCase2()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc_Drv_AdcChInit_Param1_Dummy.ucAdcCh           = 1u;
  Adc_Drv_AdcChInit_Param1_Dummy.eInCh             = eADC_EXT_2;

  //Step 2) Assign Input values
  Adc_Drv_AdcChInit_Param1 = &Adc_Drv_AdcChInit_Param1_Dummy;
  Adc0_sReg.SC1[Adc_Drv_AdcChInit_Param1->ucAdcCh] = 0b00000000000000001000000011110000; //33008u

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_AdcChInit(Adc_Drv_AdcChInit_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc0_sReg.SC1[Adc_Drv_AdcChInit_Param1->ucAdcCh], 0b00000000000000001000000011000010, == );//32962u
}
  
// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_SwReadChannel_TestCase1
///
/// \Test Case Description: Return read channel status when channel validity is not ok
///                         ADC instance is not ADC0 or ADC1
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input       Adc_Drv_SwReadChannel_Param3_Dummy                                = 0u
/// \input       Adc_Drv_SwReadChannel_Param1                                      = 0u
/// \input       Adc_Drv_sInputMap_Dummy.ucCfgLength                               = 0u
/// \input       asLocalCfg[Adc_Drv_SwReadChannel_Param1].ucAdcInst                = 3u
///
/// - Expectations: 
///
/// \output   Adc_Drv_SwReadChannel_RetVal                                         = E_NOT_OK
/// \output   Adc_Drv_SwReadChannel_Param2[Adc_Drv_SwReadChannel_Param1].ucAdcInst = 3u
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_SwReadChannel_TestCase1()
{
  uint16 Adc_Drv_SwReadChannel_Param3_Dummy = 0u;

  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc_Drv_sInputMap_Dummy.ucCfgLength                                  = 0u;
  Adc_Drv_SwReadChannel_Param2[Adc_Drv_SwReadChannel_Param1].ucAdcInst = 3u;

  //Step 2) Assign Input values
  Adc_Drv_SwReadChannel_Param3 = &Adc_Drv_SwReadChannel_Param3_Dummy;
  Adc_Drv_SwReadChannel_Param1 = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_SwReadChannel_RetVal = Adc_Drv_SwReadChannel(Adc_Drv_SwReadChannel_Param1, Adc_Drv_SwReadChannel_Param2, Adc_Drv_SwReadChannel_Param3);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_SwReadChannel_Param2[Adc_Drv_SwReadChannel_Param1].ucAdcInst, 3u, == );
  AL_UNITTEST_CHECK(Adc_Drv_SwReadChannel_RetVal, E_NOT_OK                                  , == );
}
  
// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_SwReadChannel_TestCase2
///
/// \Test Case Description: Return status not ok for input out of range
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input      Adc_Drv_SwReadChannel_Param3_Dummy                                     = 0u
/// \input      Adc_Drv_SwReadChannel_Param1                                           = 1u
/// \input      Adc1_sReg.SC2                                                          = 5u
/// \input      Adc1_sReg.SC1[0]                                                       = 5u
/// \input      Adc1_sReg.R[0]                                                         = 8u
/// \input      Adc_Drv_sInputMap_Dummy.ucCfgLength                                    = 2u
/// \input      Adc_Drv_SwReadChannel_Param2[Adc_Drv_SwReadChannel_Param1].ucAdcInst   = 1u
/// \input      Adc_Drv_SwReadChannel_Param2[Adc_Drv_SwReadChannel_Param1].ucAdcInst   = 1u
/// \input      Adc_Drv_SwReadChannel_Param2[Adc_Drv_SwReadChannel_Param1].eInCh       = 1u
/// \input      Adc_Drv_SwReadChannel_Param2[Adc_Drv_SwReadChannel_Param1].boIntEnbl   = TRUE
///
/// - Expectations: 
///
/// \output     Adc_Drv_SwReadChannel_RetVal                                           = E_NOT_OK
/// \output     Adc_Drv_SwReadChannel_Param2[Adc_Drv_SwReadChannel_Param1].ucAdcInst   = 1u
/// \output     Adc_Drv_SwReadChannel_Param3                                           = ADC_DRV_READ_CONV_ERROR
/// \output     Adc1_sReg.SC1[0]                                                       = 65u
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_SwReadChannel_TestCase2()
{
  uint16 Adc_Drv_SwReadChannel_Param3_Dummy = 0u;

  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc1_sReg.SC2                                                        = 5u;
  Adc1_sReg.SC1[0]                                                     = 5u;
  Adc1_sReg.R[0]                                                       = 8u;
  Adc_Drv_sInputMap_Dummy.ucCfgLength                                  = 2u;

  //Step 2) Assign Input values
  Adc_Drv_SwReadChannel_Param3 = &Adc_Drv_SwReadChannel_Param3_Dummy;
  Adc_Drv_SwReadChannel_Param1 = 1u;
  Adc_Drv_SwReadChannel_Param2[Adc_Drv_SwReadChannel_Param1].ucAdcInst = 1u;
  Adc_Drv_SwReadChannel_Param2[Adc_Drv_SwReadChannel_Param1].eInCh     = 1u;
  Adc_Drv_SwReadChannel_Param2[Adc_Drv_SwReadChannel_Param1].boIntEnbl = TRUE;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_SwReadChannel_RetVal = Adc_Drv_SwReadChannel(Adc_Drv_SwReadChannel_Param1, Adc_Drv_SwReadChannel_Param2, Adc_Drv_SwReadChannel_Param3);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_SwReadChannel_Param3_Dummy, ADC_DRV_READ_CONV_ERROR                   , == );
  AL_UNITTEST_CHECK(Adc_Drv_SwReadChannel_Param2[Adc_Drv_SwReadChannel_Param1].ucAdcInst, 1u, == );
  AL_UNITTEST_CHECK(Adc1_sReg.SC1[0], 65u                                                   , == );
  AL_UNITTEST_CHECK(Adc_Drv_SwReadChannel_RetVal, E_NOT_OK                                  , == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_SwReadChannel_TestCase3
///
/// \Test Case Description: Store SC1 register value
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input      Adc_Drv_SwReadChannel_Param3_Dummy                                     = 0u
/// \input      Adc_Drv_SwReadChannel_Param1                                           = 1u
/// \input      Adc0_sReg.SC2                                                          = 240u
/// \input      Adc0_sReg.SC1[0]                                                       = 780u
/// \input      Adc0_sReg.R[0]                                                         = 8u
/// \input      Adc_Drv_sInputMap_Dummy.ucCfgLength                                    = 2u
/// \input      Adc_Drv_SwReadChannel_Param2[Adc_Drv_SwReadChannel_Param1].ucAdcInst   = 0u
/// \input      Adc_Drv_SwReadChannel_Param2[Adc_Drv_SwReadChannel_Param1].boIntEnbl   = TRUE
/// \input      Adc_Drv_SwReadChannel_Param2[Adc_Drv_SwReadChannel_Param1].eInCh       = eAdcExtCh8
///
/// - Expectations: 
///
/// \output     Adc_Drv_SwReadChannel_Param3                                           = Adc0_sReg.R[0]
/// \output     Adc_Drv_SwReadChannel_Param2[Adc_Drv_SwReadChannel_Param1].ucAdcInst   = 0u
/// \output     Adc_Drv_SwReadChannel_Param2[Adc_Drv_SwReadChannel_Param1].boIntEnbl   = TRUE
/// \output     Adc0_sReg.SC1[0]                                                       = 840u
/// \output     Adc_Drv_SwReadChannel_RetVal                                           = E_OK
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_SwReadChannel_TestCase3()
{
  uint16 Adc_Drv_SwReadChannel_Param3_Dummy = 0u;

  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc_Drv_SwReadChannel_Param3_Dummy                                   = ADC0->R[0];
  Adc_Drv_sInputMap_Dummy.ucCfgLength                                  = 2u;
  Adc0_sReg.SC2                                                        = 240u;
  Adc0_sReg.SC1[0]                                                     = 780u;
  Adc0_sReg.R[0]                                                       = 8u;

  //Step 2) Assign Input values
  Adc_Drv_SwReadChannel_Param1 = 1u;
  Adc_Drv_SwReadChannel_Param2[Adc_Drv_SwReadChannel_Param1].ucAdcInst = 0u;
  Adc_Drv_SwReadChannel_Param2[Adc_Drv_SwReadChannel_Param1].boIntEnbl = TRUE;
  Adc_Drv_SwReadChannel_Param2[Adc_Drv_SwReadChannel_Param1].eInCh     = eAdcExtCh8;
  Adc_Drv_SwReadChannel_Param3 = &Adc_Drv_SwReadChannel_Param3_Dummy;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_SwReadChannel_RetVal = Adc_Drv_SwReadChannel(Adc_Drv_SwReadChannel_Param1, Adc_Drv_SwReadChannel_Param2, Adc_Drv_SwReadChannel_Param3);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_SwReadChannel_Param3_Dummy, Adc0_sReg.R[0]                        , == );
  AL_UNITTEST_CHECK(Adc_Drv_SwReadChannel_Param2[Adc_Drv_SwReadChannel_Param1].ucAdcInst, 0u  , == );
  AL_UNITTEST_CHECK(Adc_Drv_SwReadChannel_Param2[Adc_Drv_SwReadChannel_Param1].boIntEnbl, TRUE, == );
  AL_UNITTEST_CHECK(Adc0_sReg.SC1[0], 840u                                                    , == );
  AL_UNITTEST_CHECK(Adc_Drv_SwReadChannel_RetVal, E_OK                                        , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Adc_Drv_GetAdcRawValue_TestCase1
///
/// \Test Case Description: Return error in case of invalid channel 
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input      Adc_Drv_GetAdcRawValue_Param1         = 3u
/// \input      Adc_Drv_sInputMap_Dummy.ucCfgLength   = 2u
///
/// - Expectations: 
///
/// \output   Adc_Drv_GetAdcRawValue_RetVal           = ADC_DRV_READ_CONV_ERROR
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_GetAdcRawValue_TestCase1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc_Drv_sInputMap_Dummy.ucCfgLength = 2u;
  Adc_Drv_psInputMap                  = &Adc_Drv_sInputMap_Dummy;

  //Step 2) Assign Input values
  Adc_Drv_GetAdcRawValue_Param1       = 3u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_GetAdcRawValue_RetVal = Adc_Drv_GetAdcRawValue(Adc_Drv_GetAdcRawValue_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_GetAdcRawValue_RetVal, ADC_DRV_READ_CONV_ERROR, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Adc_Drv_GetAdcRawValue_TestCase2
///
/// \Test Case Description: Return DMA RAM source address based on channel input index
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input      Adc_Drv_GetAdcRawValue_Param1                      = 5u
/// \input      ulAdcData_Dummy[Adc_Drv_GetAdcRawValue_Param1]     = 30u
/// \input      Adc_Drv_sInputMap_Dummy.ucCfgLength                = 10u
///
/// - Expectations: 
///
/// \output   Adc_Drv_GetAdcRawValue_RetVal                        = 30u
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_GetAdcRawValue_TestCase2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc_Drv_sInputMap_Dummy.psAdcInCfg                         = psAdcInCfg_Dummy;
  Adc_Drv_sInputMap_Dummy.ucCfgLength                        = 10u;
  Adc_Drv_psInputMap                                         = &Adc_Drv_sInputMap_Dummy;

  //Step 2) Assign Input values
  Adc_Drv_GetAdcRawValue_Param1                              = 5u;
  ulAdcData_Dummy[Adc_Drv_GetAdcRawValue_Param1]             = 30u;
  psAdcInCfg_Dummy[Adc_Drv_GetAdcRawValue_Param1].pulAdcData = &ulAdcData_Dummy[Adc_Drv_GetAdcRawValue_Param1];

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_GetAdcRawValue_RetVal = Adc_Drv_GetAdcRawValue(Adc_Drv_GetAdcRawValue_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_GetAdcRawValue_RetVal, 30u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_SetAdcClkDivider_TestCase1
///
/// \Test Case Description: Update CFG1 register
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input      Adc_Drv_SetAdcClkDivider_Param1.CFG1      = 0b0000 0000 0000 0000 0000 0010 1[01]0 0100
/// \input      Adc_Drv_SetAdcClkDivider_Param2           = 3u;
///
/// - Expectations: 
///
/// \output    Adc_Drv_SetAdcClkDivider_Param1.CFG1       = 0b0000 0000 0000 0000 0000 0010 1[11]0 0100
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_SetAdcClkDivider_TestCase1()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc0_sReg.CFG1                     = 0b00000000000000000000001010100100;

  //Step 2) Assign Input values
  Adc_Drv_SetAdcClkDivider_Param1    = &Adc0_sReg;
  Adc_Drv_SetAdcClkDivider_Param2    = 3u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_SetAdcClkDivider(Adc_Drv_SetAdcClkDivider_Param1, Adc_Drv_SetAdcClkDivider_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc0_sReg.CFG1, 0b00000000000000000000001011100100, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_SetAdcClkDivider_TestCase2
///
/// \Test Case Description: Check ADC instance invalid, configuration wrong
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input      Adc_Drv_SetAdcClkDivider_Param1.CFG1      = 0u
/// \input      Adc_Drv_SetAdcClkDivider_Param2           = 4u
///
/// - Expectations: 
///
/// \output    Adc_Drv_SetAdcClkDivider_Param1.CFG1       = 0u
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_SetAdcClkDivider_TestCase2()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc0_sReg.CFG1                       = 0u;

  //Step 2) Assign Input values
  Adc_Drv_SetAdcClkDivider_Param1      = &Adc0_sReg;
  Adc_Drv_SetAdcClkDivider_Param2      = 4u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_SetAdcClkDivider(Adc_Drv_SetAdcClkDivider_Param1, Adc_Drv_SetAdcClkDivider_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc0_sReg.CFG1, 0u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_SetAdcSampleNr_TestCase1
///
/// \Test Case Description: ADC instance invalid, configuration wrong
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input      Adc_Drv_SetAdcSampleNr_Param1.CFG2          = 0u
/// \input      Adc_Drv_SetAdcSampleNr_Param2               = 5555555555u
///
/// - Expectations: 
///
/// \output   Adc_Drv_SetAdcSampleNr_Param1.CFG2             = 0u
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_SetAdcSampleNr_TestCase1()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc0_sReg.CFG2                     = 0u;

  //Step 2) Assign Input values
  Adc_Drv_SetAdcSampleNr_Param1      = &Adc0_sReg;
  Adc_Drv_SetAdcSampleNr_Param2      = 5555555555u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_SetAdcSampleNr(Adc_Drv_SetAdcSampleNr_Param1, Adc_Drv_SetAdcSampleNr_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_SetAdcSampleNr_Param1->CFG2, 0u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_SetAdcSampleNr_TestCase2
///
/// \Test Case Description: Update CFG2 register
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input      Adc_Drv_SetAdcSampleNr_Param1.CFG2      = 0b0000 0000 0000 0000 0111 1111 0000 [00]00
/// \input      Adc_Drv_SetAdcSampleNr_Param2           = 12u;
///
/// - Expectations: 
///
/// \output   Adc_Drv_SetAdcSampleNr_Param1.CFG2        = 0b0000 0000 0000 0000 0111 1111 0000 [11]00
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_SetAdcSampleNr_TestCase2()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc0_sReg.CFG2                     = 0b00000000000000000111111100000000;

  //Step 2) Assign Input values
  Adc_Drv_SetAdcSampleNr_Param1      = &Adc0_sReg;
  Adc_Drv_SetAdcSampleNr_Param2      = 12u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_SetAdcSampleNr(Adc_Drv_SetAdcSampleNr_Param1, Adc_Drv_SetAdcSampleNr_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_SetAdcSampleNr_Param1->CFG2, 0b00000000000000000111111100001100, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_SetAdcResolution_TestCase1
///
/// \Test Case Description: ADC instance invalid, configuration wrong
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input      Adc_Drv_SetAdcResolution_Param1.CFG1      = 0u
/// \input      Adc_Drv_SetAdcResolution_Param2           = 4u
///
/// - Expectations: 
///
/// \output   Adc_Drv_SetAdcResolution_Param1.CFG1        = 0u
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_SetAdcResolution_TestCase1()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc0_sReg.CFG1                       = 0u;

  //Step 2) Assign Input values
  Adc_Drv_SetAdcResolution_Param1      = &Adc0_sReg;
  Adc_Drv_SetAdcResolution_Param2      = 4u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_SetAdcResolution(Adc_Drv_SetAdcResolution_Param1, Adc_Drv_SetAdcResolution_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_SetAdcResolution_Param1->CFG1, 0u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_SetAdcResolution_TestCase2
///
/// \Test Case Description: Update CFG1 register
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input      Adc_Drv_SetAdcResolution_Param1.CFG1      = 0b0000 0000 0000 0000 0000 0010 1101 [00]11
/// \input      Adc_Drv_SetAdcResolution_Param2           = 3u;
///
/// - Expectations: 
///
/// \output   Adc_Drv_SetAdcResolution_Param1.CFG1        = 0b0000 0000 0000 0000 0000 0010 1101 [11]11
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_SetAdcResolution_TestCase2()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc0_sReg.CFG1                       = 0b00000000000000000000001011010011; //723

  //Step 2) Assign Input values
  Adc_Drv_SetAdcResolution_Param1      = &Adc0_sReg; 
  Adc_Drv_SetAdcResolution_Param2      = 3u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_SetAdcResolution(Adc_Drv_SetAdcResolution_Param1, Adc_Drv_SetAdcResolution_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_SetAdcResolution_Param1->CFG1, 0b00000000000000000000001011011111, == ); //735

}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_SetAdcClkIn_TestCase1
///
/// \Test Case Description: ADC instance invalid, configuration wrong
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input      Adc_Drv_SetAdcClkIn_Param1.CFG1      = 0u
/// \input      Adc_Drv_SetAdcClkIn_Param2           = 4u
///
/// - Expectations: 
///
/// \output   Adc_Drv_SetAdcClkIn_Param1.CFG1        = 0u
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_SetAdcClkIn_TestCase1()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions;
  Adc0_sReg.CFG1                  = 0u;

  //Step 2) Assign Input values
  Adc_Drv_SetAdcClkIn_Param1      = &Adc0_sReg;
  Adc_Drv_SetAdcClkIn_Param2      = 4u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_SetAdcClkIn(Adc_Drv_SetAdcClkIn_Param1, Adc_Drv_SetAdcClkIn_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_SetAdcClkIn_Param1->CFG1, 0u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_SetAdcClkIn_TestCase2
///
/// \Test Case Description: Update CFG1 register
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input      Adc_Drv_SetAdcClkIn_Param1.CFG1      = 0b0000 0000 0000 0000 0000 0000 0000 011[0]
/// \input      Adc_Drv_SetAdcClkIn_Param2           = 3u
///
/// - Expectations: 
///
/// \output   Adc_Drv_SetAdcClkIn_Param1.CFG1        = 0b0000 0000 0000 0000 0000 0000 0000 011[1]
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_SetAdcClkIn_TestCase2()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc0_sReg.CFG1                  = 0b00000000000000000000000000000110;

  //Step 2) Assign Input values
  Adc_Drv_SetAdcClkIn_Param1      = &Adc0_sReg;
  Adc_Drv_SetAdcClkIn_Param2      = 3u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_SetAdcClkIn(Adc_Drv_SetAdcClkIn_Param1, Adc_Drv_SetAdcClkIn_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_SetAdcClkIn_Param1->CFG1, 0b00000000000000000000000000000111, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_SetAdcTrgType_TestCase1
///
/// \Test Case Description: ADC instance invalid, configuration wrong
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input       Adc_Drv_SetAdcTrgType_Param1.SC2      = 0u
/// \input       Adc_Drv_SetAdcTrgType_Param2          = 2u
///
/// - Expectations: 
///
/// \output   Adc_Drv_SetAdcTrgType_Param1.SC2         = 0u
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_SetAdcTrgType_TestCase1()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc0_sReg.SC2                    = 0u;

  //Step 2) Assign Input values
  Adc_Drv_SetAdcTrgType_Param1     = &Adc0_sReg;
  Adc_Drv_SetAdcTrgType_Param2     = 2u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_SetAdcTrgType(Adc_Drv_SetAdcTrgType_Param1, Adc_Drv_SetAdcTrgType_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_SetAdcTrgType_Param1->SC2, 0u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_SetAdcTrgType_TestCase2
///
/// \Test Case Description: Update SC2 register
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input       Adc_Drv_SetAdcTrgType_Param1.SC2      = 0b0000 0000 0000 0000 0000 0000 0000 1000
/// \input       Adc_Drv_SetAdcTrgType_Param2          = 1u
///
/// - Expectations: 
///
/// \output   Adc_Drv_SetAdcTrgType_Param1.SC2         = 0b0000 0000 0000 0000 0000 0000 0100 1000
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_SetAdcTrgType_TestCase2()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc0_sReg.SC2                    = 0b00000000000000000000000000001000;

  //Step 2) Assign Input values
  Adc_Drv_SetAdcTrgType_Param1     = &Adc0_sReg;
  Adc_Drv_SetAdcTrgType_Param2     = 1u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_SetAdcTrgType(Adc_Drv_SetAdcTrgType_Param1, Adc_Drv_SetAdcTrgType_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_SetAdcTrgType_Param1->SC2, 0b00000000000000000000000001001000, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_SetAdcTrgInput_TestCase1
///
/// \Test Case Description: Write Trigger input in TRIG_IN_ADC0 bitfield
///
/// - Preconditions:
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// \input      Adc_Drv_SetAdcTrgInput_Param1 = ADC0
/// \input      Adc_Drv_SetAdcTrgInput_Param2 = 0u
/// \input      Sim_sReg.ADCOPT               = 0b0000 0000 0000 0000 0000 0000 0101 001[1]
///
/// - Expectations: 
///
/// \output   Sim_sReg.ADCOPT                 = 0b0000 0000 0000 0000 0000 0000 0101 001[0]
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_SetAdcTrgInput_TestCase1()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Sim_sReg.ADCOPT               = 0b00000000000000000000000001010011;

  //Step 2) Assign Input values
  Adc_Drv_SetAdcTrgInput_Param1 = ADC0;
  Adc_Drv_SetAdcTrgInput_Param2 = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_SetAdcTrgInput(Adc_Drv_SetAdcTrgInput_Param1, Adc_Drv_SetAdcTrgInput_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK( Sim_sReg.ADCOPT, 0b00000000000000000000000001010010 , == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_SetAdcTrgInput_TestCase2
///
/// \Test Case Description: Write Trigger input in TRIG_IN_ADC1 bitfield
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input      Adc_Drv_SetAdcTrgInput_Param1 = ADC1;
/// \input      Adc_Drv_SetAdcTrgInput_Param2 = 0u;
/// \input      Sim_sReg.ADCOPT               = 0b0000 0000 0000 0000 0000 000[0] 0101 0011
///
/// - Expectations: 
///
/// \output   Sim_sReg.ADCOPT                 = 0b0000 0000 0000 0000 0000 000[1] 0101 0011
//-----------------------------------------------------------------------------

void Mt_Adc_Drv_SetAdcTrgInput_TestCase2()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Sim_sReg.ADCOPT               = 0b00000000000000000000000001010011;

  //Step 2) Assign Input values
  Adc_Drv_SetAdcTrgInput_Param1 = ADC1;
  Adc_Drv_SetAdcTrgInput_Param2 = 1u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_SetAdcTrgInput(Adc_Drv_SetAdcTrgInput_Param1, Adc_Drv_SetAdcTrgInput_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Sim_sReg.ADCOPT, 0b00000000000000000000000101010011, == );
}

// -----------------------------------------------------------------------------
/// \Test Case : Mt_Adc_Drv_SetAdcTrgInput_TestCase3
///
/// \Test Case Description: Test Invalid ADC0 instance, invalid configuration
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input      Adc_Drv_SetAdcTrgInput_Param1 = ADC0;
/// \input      Adc_Drv_SetAdcTrgInput_Param2 = 2u;
/// \input      Sim_sReg.ADCOPT               = 0b0000 0100 0000 0000 0000 1101 0000 1111
///
/// - Expectations: 
///
/// \output   Sim_sReg.ADCOPT                 = 0b0000 0100 0000 0000 0000 1101 0000 111[1]
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_SetAdcTrgInput_TestCase3()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Sim_sReg.ADCOPT               = 0b00000100000000000000110100001111;

  //Step 2) Assign Input values
  Adc_Drv_SetAdcTrgInput_Param1 = ADC0;
  Adc_Drv_SetAdcTrgInput_Param2 = 2u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_SetAdcTrgInput(Adc_Drv_SetAdcTrgInput_Param1, Adc_Drv_SetAdcTrgInput_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK( Sim_sReg.ADCOPT, 0b00000100000000000000110100001111, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_SetAdcTrgInput_TestCase4
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// \Test Case Description: Test Invalid AD1C instance, invalid configuration
///
/// - Preconditions:
///
/// \input      Adc_Drv_SetAdcTrgInput_Param1 = ADC1;
/// \input      Adc_Drv_SetAdcTrgInput_Param2 = 3u;
/// \input      Sim_sReg.ADCOPT               = 0b0000 0100 0000 0000 0000 1101 0000 1111
///
/// - Expectations: 
///
/// \output   Sim_sReg.ADCOPT                 = 0b0000 0100 0000 0000 0000 110[1] 0000 1111
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_SetAdcTrgInput_TestCase4()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Sim_sReg.ADCOPT               = 0b00000100000000000000110100001111;

  //Step 2) Assign Input values
  Adc_Drv_SetAdcTrgInput_Param1 = ADC1;
  Adc_Drv_SetAdcTrgInput_Param2 = 3u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_SetAdcTrgInput(Adc_Drv_SetAdcTrgInput_Param1, Adc_Drv_SetAdcTrgInput_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK( Sim_sReg.ADCOPT, 0b00000100000000000000110100001111, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_SetAdcPreTrgInput_TestCase1
///
/// \Test Case Description: Write Pre-Trigger input in PRETRIG_IN_ADC0 bitfield
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input      Adc_Drv_SetAdcPreTrgInput_Param1 = ADC0;
/// \input      Adc_Drv_SetAdcPreTrgInput_Param2 = 3u;
/// \input      Sim_sReg.ADCOPT                  = 0b0000 0000 0000 0000 0000 0000 01[01] 0011
///
/// - Expectations: 
///
/// \output   Sim_sReg.ADCOPT                    = 0b0000 0000 0000 0000 0000 0000 01[11] 0011
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_SetAdcPreTrgInput_TestCase1()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Sim_sReg.ADCOPT                  = 0b00000000000000000000000001010011;

  //Step 2) Assign Input values
  Adc_Drv_SetAdcPreTrgInput_Param1 = ADC0;
  Adc_Drv_SetAdcPreTrgInput_Param2 = 3u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_SetAdcPreTrgInput(Adc_Drv_SetAdcPreTrgInput_Param1, Adc_Drv_SetAdcPreTrgInput_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK( Sim_sReg.ADCOPT, 0b00000000000000000000000001110011, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_SetAdcPreTrgInput_TestCase2
///
/// \Test Case Description: Write Pre-Trigger input in PRETRIG_IN_ADC1 bitfield
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input      Adc_Drv_SetAdcPreTrgInput_Param1 = ADC1;
/// \input      Adc_Drv_SetAdcPreTrgInput_Param2 = 3u;
/// \input      Sim_sReg.ADCOPT                  = 0b0000 0000 0000 0000 00[00] 0000 0101 0011
///
/// - Expectations: 
///
/// \output   Sim_sReg.ADCOPT                    = 0b0000 0000 0000 0000 00[11] 0000 0101 0011
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_SetAdcPreTrgInput_TestCase2()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Sim_sReg.ADCOPT                  = 0b00000000000000000000000001010011;

  //Step 2) Assign Input values
  Adc_Drv_SetAdcPreTrgInput_Param1 = ADC1;
  Adc_Drv_SetAdcPreTrgInput_Param2 = 3u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_SetAdcPreTrgInput(Adc_Drv_SetAdcPreTrgInput_Param1, Adc_Drv_SetAdcPreTrgInput_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK( Sim_sReg.ADCOPT, 0b00000000000000000011000001010011, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_SetAdcPreTrgInput_TestCase3
///
/// \Test Case Description: Test Invalid ADC0 instance, invalid configuration
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input      Adc_Drv_SetAdcPreTrgInput_Param1 = ADC0
/// \input      Adc_Drv_SetAdcPreTrgInput_Param2 = 4u
/// \input      Sim_sReg.ADCOPT                  = 0b0000 0100 0000 0000 0000 1101 0000 [111]1
///
/// - Expectations: 
///
/// \output   Sim_sReg.ADCOPT                    = 0b0000 0100 0000 0000 0000 1101 0000 [111]1
//-----------------------------------------------------------------------------

void Mt_Adc_Drv_SetAdcPreTrgInput_TestCase3()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Sim_sReg.ADCOPT                  = 0b00000100000000000000110100001111;

  //Step 2) Assign Input values
  Adc_Drv_SetAdcPreTrgInput_Param1 = ADC0;
  Adc_Drv_SetAdcPreTrgInput_Param2 = 4u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_SetAdcPreTrgInput(Adc_Drv_SetAdcPreTrgInput_Param1, Adc_Drv_SetAdcPreTrgInput_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK( Sim_sReg.ADCOPT, 0b00000100000000000000110100001111, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_SetAdcPreTrgInput_TestCase4
///
/// \Test Case Description: Invalid ADC1 instance, invalid configuration
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input      Adc_Drv_SetAdcPreTrgInput_Param1 = ADC1
/// \input      Adc_Drv_SetAdcPreTrgInput_Param2 = 4u
/// \input      Sim_sReg.ADCOPT                  = 0b0000 0100 0000 0000 0000 [110]1 0000 1111
///
/// - Expectations: 
///
/// \output   Sim_sReg.ADCOPT                    = 0b0000 0100 0000 0000 0000 [110]1 0000 1111
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_SetAdcPreTrgInput_TestCase4()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Sim_sReg.ADCOPT                  = 0b00000100000000000000110100001111;

  //Step 2) Assign Input values
  Adc_Drv_SetAdcPreTrgInput_Param1 = ADC1;
  Adc_Drv_SetAdcPreTrgInput_Param2 = 4u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_SetAdcPreTrgInput(Adc_Drv_SetAdcPreTrgInput_Param1, Adc_Drv_SetAdcPreTrgInput_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK( Sim_sReg.ADCOPT, 0b00000100000000000000110100001111, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_SetAdcDmaEnbl_TestCase1
///
/// \Test Case Description: ADC instance invalid, configuration wrong
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input         Adc_Drv_SetAdcDmaEnbl_Param1          = &Adc0_sReg
/// \input         Adc0_sReg.SC2                         = 0u
/// \input         Adc_Drv_SetAdcDmaEnbl_Param2          = 2u
///
/// - Expectations: 
///
/// \output        Adc_Drv_SetAdcDmaEnbl_Param1.SC2      = 0u
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_SetAdcDmaEnbl_TestCase1()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc0_sReg.SC2                    = 0u; 

  //Step 2) Assign Input values
  Adc_Drv_SetAdcDmaEnbl_Param1     = &Adc0_sReg;
  Adc_Drv_SetAdcDmaEnbl_Param2     = 2u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_SetAdcDmaEnbl(Adc_Drv_SetAdcDmaEnbl_Param1, Adc_Drv_SetAdcDmaEnbl_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_SetAdcDmaEnbl_Param1->SC2, 0u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_SetAdcDmaEnbl_TestCase2
///
/// \Test Case Description: Update SC2 register
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input         Adc_Drv_SetAdcDmaEnbl_Param1          = &Adc0_sReg
/// \input         Adc0_sReg.SC2                         = 0b0000 0000 0000 0000 0000 0000 0000 0[1]01
/// \input         Adc_Drv_SetAdcDmaEnbl_Param2          = 0U
///
/// - Expectations: 
///
/// \output   Adc_Drv_SetAdcDmaEnbl_Param1.SC2           = 0b0000 0000 0000 0000 0000 0000 0000 0[0]01
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_SetAdcDmaEnbl_TestCase2()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc0_sReg.SC2                    = 0b00000000000000000000000000000101;

  //Step 2) Assign Input values
  Adc_Drv_SetAdcDmaEnbl_Param1     = &Adc0_sReg;
  Adc_Drv_SetAdcDmaEnbl_Param2     = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_SetAdcDmaEnbl(Adc_Drv_SetAdcDmaEnbl_Param1, Adc_Drv_SetAdcDmaEnbl_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_SetAdcDmaEnbl_Param1->SC2, 0b0000000000000000000000000000001, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_SetAdcRefSel_TestCase1
///
/// \Test Case Description: Adc Reference selection with invalid instance and no SC2 register updated
///
/// - Preconditions:
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// \input          Adc_Drv_SetAdcRefSel_Param2     = 5u
/// \input          Adc0_sReg.SC2                   = 0b0000 0000 0000 0000 0000 0000 0000 11[00]
/// \input          Adc_Drv_SetAdcRefSel_Param1     = &Adc0_sReg
///
/// - Expectations: 
///
/// \output   Adc_Drv_SetAdcRefSel_Param1           = 0b0000 0000 0000 0000 0000 0000 0000 11[00]
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_SetAdcRefSel_TestCase1()
{
  //-----------------------------------------------------------------------------
 // Inputs
 //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc0_sReg.SC2                   = 0b00000000000000000000000000001100;

  //Step 2) Assign Input values
  Adc_Drv_SetAdcRefSel_Param1     = &Adc0_sReg;
  Adc_Drv_SetAdcRefSel_Param2     = 5u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_SetAdcRefSel(Adc_Drv_SetAdcRefSel_Param1, Adc_Drv_SetAdcRefSel_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_SetAdcRefSel_Param1->SC2, 0b00000000000000000000000000001100, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_SetAdcRefSel_TestCase2
///
/// \Test Case Description: Adc Reference selection with valid instance and SC2 register updated
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input          Adc_Drv_SetAdcRefSel_Param2     = 3u
/// \input          Adc0_sReg.SC2                   = 0b0000 0000 0000 0000 0000 0000 0000 11[00]
/// \input          Adc_Drv_SetAdcRefSel_Param1.SC2 = Adc0_sReg.SC2
///
/// - Expectations: 
///
/// \output        Adc_Drv_SetAdcRefSel_Param1      = 0b0000 0000 0000 0000 0000 0000 0000 11[11]
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_SetAdcRefSel_TestCase2()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc0_sReg.SC2               = 0b00000000000000000000000000001100;

  //Step 2) Assign Input values
  Adc_Drv_SetAdcRefSel_Param1 = &Adc0_sReg;
  Adc_Drv_SetAdcRefSel_Param2 = 3u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_SetAdcRefSel(Adc_Drv_SetAdcRefSel_Param1, Adc_Drv_SetAdcRefSel_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_SetAdcRefSel_Param1->SC2, 0b00000000000000000000000000001111, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_SetAdcAvgEnbl_TestCase1
///
/// \Test Case Description: Adc average conversion enable procedure with ADC
///                        instance valid and SC3 updated
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input          Adc_Drv_SetAdcAvgEnbl_Param1      = &Adc0_sReg
/// \input          Adc_Drv_SetAdcAvgEnbl_Param2      = 0u
/// \input          Adc0_sReg.SC3                     = 0b0000 0000 0000 0000 1000 0000 1111 0[1]10
///
/// - Expectations: 
///
/// \output        Adc_Drv_SetAdcAvgEnbl_Param1->SC3  = 0b0000 0000 0000 0000 1000 0000 1111 0[0]10
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_SetAdcAvgEnbl_TestCase1()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc0_sReg.SC3                    = 0b00000000000000001000000011110110;

  //Step 2) Assign Input values
  Adc_Drv_SetAdcAvgEnbl_Param1     = &Adc0_sReg;
  Adc_Drv_SetAdcAvgEnbl_Param2     = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_SetAdcAvgEnbl(Adc_Drv_SetAdcAvgEnbl_Param1, Adc_Drv_SetAdcAvgEnbl_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_SetAdcAvgEnbl_Param1->SC3, 0b00000000000000001000000011110010, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_SetAdcAvgEnbl_TestCase2
///
/// \Test Case Description: Adc average conversion enable procedure with ADC
///                        instance invalid and SC3 not updated
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input          Adc_Drv_SetAdcAvgEnbl_Param1         = &Adc0_sReg;
/// \input          Adc_Drv_SetAdcAvgEnbl_Param2         = 6u
/// \input          Adc0_sReg.SC3                        = 0b0000 0000 0000 0000 0000 0000 0100 0[0]00
///
/// - Expectations: 
///
/// \output        Adc_Drv_SetAdcAvgEnbl_Param1->SC3     = 0b0000 0000 0000 0000 0000 0000 0100 0[0]00
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_SetAdcAvgEnbl_TestCase2()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc0_sReg.SC3                    = 0b00000000000000000000000001000000;

  //Step 2) Assign Input values
  Adc_Drv_SetAdcAvgEnbl_Param1     = &Adc0_sReg; 
  Adc_Drv_SetAdcAvgEnbl_Param2     = 6u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_SetAdcAvgEnbl(Adc_Drv_SetAdcAvgEnbl_Param1, Adc_Drv_SetAdcAvgEnbl_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_SetAdcAvgEnbl_Param1->SC3, 0b00000000000000000000000001000000, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_SetAdcAvgMode_TestCase1
///
/// \Test Case Description: Adc average conversion mode procedure with ADC
///                         instance valid and SC3 updated
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input          Adc_Drv_SetAdcAvgMode_Param1     = &Adc0_sReg
/// \input          Adc_Drv_SetAdcAvgMode_Param2     = 2u
/// \input          Adc0_sReg.SC3                    = 0b0000 0000 0000 0000 0000 1111 0000 11[11]
///
/// - Expectations: 
///
/// \output         Adc_Drv_SetAdcAvgMode_Param1.SC3 = 0b0000 0000 0000 0000 0000 1111 0000 11[01]
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_SetAdcAvgMode_TestCase1()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc0_sReg.SC3                    = 0b00000000000000000000111100001111;

  //Step 2) Assign Input values
  Adc_Drv_SetAdcAvgMode_Param1     = &Adc0_sReg;
  Adc_Drv_SetAdcAvgMode_Param2     = 1u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_SetAdcAvgMode(Adc_Drv_SetAdcAvgMode_Param1, Adc_Drv_SetAdcAvgMode_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_SetAdcAvgMode_Param1->SC3, 0b00000000000000000000111100001101, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_SetAdcAvgMode_TestCase2
///
/// \Test Case Description: Adc average conversion mode procedure with ADC 
///                         instance invalid and SC3 not updated
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input          Adc_Drv_SetAdcAvgMode_Param1       = &Adc0_sReg;
/// \input          Adc_Drv_SetAdcAvgMode_Param2       = 5u
/// \input          Adc0_sReg.SC3                      = 0b0000 0000 0000 0000 0000 1111 0001 00[00]
///
/// - Expectations: 
///
/// \output         Adc_Drv_SetAdcAvgMode_Param1->SC3  = 0b0000 0000 0000 0000 0000 1111 0001 00[00]
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_SetAdcAvgMode_TestCase2()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc0_sReg.SC3                    = 0b00000000000000000000111100010000;

  //Step 2) Assign Input values
  Adc_Drv_SetAdcAvgMode_Param1     = &Adc0_sReg; 
  Adc_Drv_SetAdcAvgMode_Param2     = 5u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_SetAdcAvgMode(Adc_Drv_SetAdcAvgMode_Param1, Adc_Drv_SetAdcAvgMode_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_SetAdcAvgMode_Param1->SC3, 0b00000000000000000000111100010000, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_SetAdcContinousMode_TestCase1
///
/// \Test Case Description: Adc Continous Mode enable procedure with ADC 
///                         instance valid and SC3 updated
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input          Adc_Drv_SetAdcContinousMode_Param1     = &Adc0_sReg
/// \input          Adc_Drv_SetAdcContinousMode_Param2     = 1u
/// \input          Adc0_sReg.SC3                          = 0b0000 0000 0000 0000 0000 0111 1100 [0]010
///
/// - Expectations: 
///
/// \output        Adc_Drv_SetAdcAvgMode_Param1->SC3       = 0b0000 0000 0000 0000 0000 0111 1100 [1]010
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_SetAdcContinousMode_TestCase1()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc0_sReg.SC3                          = 0b00000000000000000000011111000010;

  //Step 2) Assign Input values
  Adc_Drv_SetAdcContinousMode_Param1     = &Adc0_sReg;
  Adc_Drv_SetAdcContinousMode_Param2     = 1u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_SetAdcContinousMode(Adc_Drv_SetAdcContinousMode_Param1, Adc_Drv_SetAdcContinousMode_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_SetAdcContinousMode_Param1->SC3, 0b00000000000000000000011111001010, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_SetAdcContinousMode_TestCase2
///
/// \Test Case Description: Adc Continous Mode enable procedure with ADC
///                        instance invalid and SC3 not updated
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input          Adc_Drv_SetAdcContinousMode_Param2     = 3u
/// \input          Adc0_sReg.SC3                          = 0b0000 0000 0000 0000 0000 0111 1100 [0]011
/// \input          Adc_Drv_SetAdcContinousMode_Param1     = &Adc0_sReg
///
/// - Expectations: 
///
/// \output       Adc_Drv_SetAdcContinousMode_Param1->SC3 = 0b0000 0000 0000 0000 0000 0111 1100 [0]011
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_SetAdcContinousMode_TestCase2()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc0_sReg.SC3                          = 0b00000000000000000000011111000011;

  //Step 2) Assign Input values
  Adc_Drv_SetAdcContinousMode_Param1     = &Adc0_sReg; 
  Adc_Drv_SetAdcContinousMode_Param2     = 3u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_SetAdcContinousMode(Adc_Drv_SetAdcContinousMode_Param1, Adc_Drv_SetAdcContinousMode_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_SetAdcContinousMode_Param1->SC3, 0b00000000000000000000011111000011, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_SetAdcSupplyEn_TestCase1
///
/// \Test Case Description: Write Supply monitoring in SUPEN bitfield and 
///                        Update CHIPCTL register
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input           Adc_Drv_SetAdcSupplyEn_Param1 = ADC0
/// \input           Adc_Drv_SetAdcSupplyEn_Param2 = 1u
/// \input           Sim_sReg.CHIPCTL              = 0b0000 0000 0000 [0]000 1111 0000 0000 1111
///
/// - Expectations: 
///
/// \output          Sim_sReg.CHIPCTL              = 0b0000 0000 0000 [1]000 1111 0000 0000 1111
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_SetAdcSupplyEn_TestCase1()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Sim_sReg.CHIPCTL              = 0b00000000000000001111000000001111;

  //Step 2) Assign Input values
  Adc_Drv_SetAdcSupplyEn_Param1 = ADC0;
  Adc_Drv_SetAdcSupplyEn_Param2 = 1u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_SetAdcSupplyEn(Adc_Drv_SetAdcSupplyEn_Param1, Adc_Drv_SetAdcSupplyEn_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Sim_sReg.CHIPCTL, 0b00000000000010001111000000001111, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_SetAdcSupplyEn_TestCase2
///
/// \Test Case Description: ADC1 doesn't support Supply Monitoring
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input           Adc_Drv_SetAdcSupplyEn_Param1 = ADC1
/// \input           Adc_Drv_SetAdcSupplyEn_Param2 = 2u
/// \input           Sim_sReg.CHIPCTL              = 0b0000 0000 0000 [0]000 1111 0000 0000 1111
///
/// - Expectations: 
///
/// \output          Sim_sReg.CHIPCTL              = 0b0000 0000 0000 [0]000 1111 0000 0000 1111
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_SetAdcSupplyEn_TestCase2()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Sim_sReg.CHIPCTL              = 0b00000000000000001111000000001111;

  //Step 2) Assign Input values
  Adc_Drv_SetAdcSupplyEn_Param1 = ADC1;
  Adc_Drv_SetAdcSupplyEn_Param2 = 2u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_SetAdcSupplyEn(Adc_Drv_SetAdcSupplyEn_Param1, Adc_Drv_SetAdcSupplyEn_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Sim_sReg.CHIPCTL, 0b00000000000000001111000000001111, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_SetAdcStartCalibration
///
/// \Test Case Description: Update SC3 register
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input           Adc_Drv_SetAdcStartCalibration_Param1.SC3 = 0b0000 0000 1110 0000 1111 0000 [0]000 1100
///
/// - Expectations: 
///
/// \output          Adc_Drv_SetAdcStartCalibration_Param1.SC3 = 0b0000 0000 1110 0000 1111 0000 [1]000 1100
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_SetAdcStartCalibration()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc0_sReg.SC3                         = 0b00000000111000001111000000001100;

  //Step 2) Assign Input values
  Adc_Drv_SetAdcStartCalibration_Param1 = &Adc0_sReg;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_SetAdcStartCalibration(Adc_Drv_SetAdcStartCalibration_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_SetAdcStartCalibration_Param1->SC3, 0b00000000111000001111000010001100, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Adc_Drv_GetCalibrationStatus_TestCase1
///
/// \Test Case Description: Return status of ADC self calibration FALSE
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input      Adc_Drv_GetCalibrationStatus_Param1.SC3     = 0b0000 0000 0000 0000 0000 0000 1101 1110
///
/// - Expectations: 
///
/// \output    Adc_Drv_GetCalibrationStatus_RetVal          = FALSE
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_GetCalibrationStatus_TestCase1()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc0_sReg.SC3                       = 0b00000000000000000000000011011110;

  //Step 2) Assign Input values
  Adc_Drv_GetCalibrationStatus_Param1 = &Adc0_sReg;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_GetCalibrationStatus_RetVal = Adc_Drv_GetCalibrationStatus(Adc_Drv_GetCalibrationStatus_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_GetCalibrationStatus_RetVal, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Adc_Drv_GetCalibrationStatus_TestCase2
///
/// \Test Case Description: Return status of ADC self calibration TRUE
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input      Adc_Drv_GetCalibrationStatus_Param1.SC3      = 0u
///
/// - Expectations: 
///
/// \output    Adc_Drv_GetCalibrationStatus_RetVal           = TRUE
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_GetCalibrationStatus_TestCase2()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc0_sReg.SC3                       = 0u;

  //Step 2) Assign Input values
  Adc_Drv_GetCalibrationStatus_Param1 = &Adc0_sReg;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_GetCalibrationStatus_RetVal = Adc_Drv_GetCalibrationStatus(Adc_Drv_GetCalibrationStatus_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_GetCalibrationStatus_RetVal, TRUE, == );
}

/// \Test Case : Mt_Adc_Drv_SetAdcChnInput_TestCase1
///
/// \Test Case Description: Adc Input Channel Configuration based on channel number and input pin
///                         Check wrong configuration
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input         Adc_Drv_SetAdcChnInput_Param1.ucAdcCh           = 2u
/// \input         Adc_Drv_SetAdcChnInput_Param1.ucAdcInst         = 3u
/// \input         Adc_Drv_SetAdcChnInput_Param2                   = 9u
///
/// - Expectations: 
///
/// \output   Adc0_sReg.SC1[Adc_Drv_SetAdcChnInput_Param1.ucAdcCh] == 0u
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_SetAdcChnInput_TestCase1()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc_Drv_SetAdcChnInput_Param1_Dummy.ucAdcCh    = 2u;
  Adc_Drv_SetAdcChnInput_Param1_Dummy.ucAdcInst  = 3u;

  //Step 2) Assign Input values
  Adc_Drv_SetAdcChnInput_Param1                  = &Adc_Drv_SetAdcChnInput_Param1_Dummy;
  Adc_Drv_SetAdcChnInput_Param2                  = 9u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_SetAdcChnInput(Adc_Drv_SetAdcChnInput_Param1, Adc_Drv_SetAdcChnInput_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc0_sReg.SC1[Adc_Drv_SetAdcChnInput_Param1->ucAdcCh], 0u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_SetAdcChnInput_TestCase2
///
/// \Test Case Description: Adc Input Channel Configuration based on channel number and input pin
///                         Check correct configuration and right register SC1 update
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input         Adc_Drv_SetAdcChnInput_Param1.ucAdcCh                = 2u
/// \input         Adc_Drv_SetAdcChnInput_Param1.ucAdcInst              = 1u
/// \input         Adc_Drv_SetAdcChnInput_Param2                        = 9u
/// \input         Adc0_sReg.SC1[Adc_Drv_SetAdcChnInput_Param1.ucAdcCh] = 0b0000 0000 0000 0000 0000 0000 01[00 0000]
///
/// - Expectations: 
///
/// \output        Adc0_sReg.SC1[Adc_Drv_SetAdcChnInput_Param1.ucAdcCh] = 0b0000 0000 0000 0000 0000 0000 01[00 1001]
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_SetAdcChnInput_TestCase2()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc_Drv_SetAdcChnInput_Param1_Dummy.ucAdcCh                = 2u;
  Adc_Drv_SetAdcChnInput_Param1_Dummy.ucAdcInst              = 1u;
  Adc_Drv_SetAdcChnInput_Param2                              = 9u;

  //Step 2) Assign Input values
  Adc_Drv_SetAdcChnInput_Param1                              = &Adc_Drv_SetAdcChnInput_Param1_Dummy;
  Adc1_sReg.SC1[Adc_Drv_SetAdcChnInput_Param1_Dummy.ucAdcCh] = 0b00000000000000000000000001000000;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_SetAdcChnInput(Adc_Drv_SetAdcChnInput_Param1, Adc_Drv_SetAdcChnInput_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc1_sReg.SC1[Adc_Drv_SetAdcChnInput_Param1->ucAdcCh], 0b00000000000000000000000001001001, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_Adc_Drv_SetAdcChnInput_TestCase3
///
/// \Test Case Description: Adc Input Channel Configuration based on channel number and input pin
///                         Check correct configuration and right register SC1 update
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input         Adc_Drv_SetAdcChnInput_Param1.ucAdcCh                = 2u
/// \input         Adc_Drv_SetAdcChnInput_Param1.ucAdcInst              = 0u
/// \input         Adc_Drv_SetAdcChnInput_Param2                        = 9u
/// \input         Adc0_sReg.SC1[Adc_Drv_SetAdcChnInput_Param1.ucAdcCh] = 0b0000 0000 0000 0000 0000 0000 01[00 0000]
///
/// - Expectations: 
///
/// \output       Adc0_sReg.SC1[Adc_Drv_SetAdcChnInput_Param1.ucAdcCh]  = 0b0000 0000 0000 0000 0000 0000 01[00 1001]
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_SetAdcChnInput_TestCase3()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc_Drv_SetAdcChnInput_Param1_Dummy.ucAdcCh                = 2u;
  Adc_Drv_SetAdcChnInput_Param1_Dummy.ucAdcInst              = 0u;
  Adc0_sReg.SC1[Adc_Drv_SetAdcChnInput_Param1_Dummy.ucAdcCh] = 0b00000000000000000000000001000000;

  //Step 2) Assign Input values
  Adc_Drv_SetAdcChnInput_Param1                              = &Adc_Drv_SetAdcChnInput_Param1_Dummy;
  Adc_Drv_SetAdcChnInput_Param2                              = 9u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_SetAdcChnInput(Adc_Drv_SetAdcChnInput_Param1, Adc_Drv_SetAdcChnInput_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc0_sReg.SC1[Adc_Drv_SetAdcChnInput_Param1->ucAdcCh], 0b00000000000000000000000001001001, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Adc_Drv_GetAdcCompleteConvStat_TestCase1
///
/// \Test Case Description: Return the ADC conversion complete status TRUE
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input      AAdc_Drv_GetAdcCompleteConvStat_Param1.SC2    = 0b0000 0000 0000 0000 0000 0000 1101 1110
///
/// - Expectations: 
///
/// \output    Adc_Drv_GetAdcCompleteConvStat_RetVal           = TRUE
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_GetAdcCompleteConvStat_TestCase1()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc0_sReg.SC2                         = 0b00000000000000000000000011011110;

  //Step 2) Assign Input values
  Adc_Drv_GetAdcCompleteConvStat_Param1 = &Adc0_sReg;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_GetAdcCompleteConvStat_RetVal = Adc_Drv_GetAdcCompleteConvStat(Adc_Drv_GetAdcCompleteConvStat_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_GetAdcCompleteConvStat_RetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Adc_Drv_GetAdcCompleteConvStat_TestCase2
///
/// \Test Case Description: Return the ADC conversion complete status FALSE
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input      AAdc_Drv_GetAdcCompleteConvStat_Param1.SC2    = 0u
///
/// - Expectations: 
///
/// \output   Adc_Drv_GetAdcCompleteConvStat_RetVal           = FALSE
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_GetAdcCompleteConvStat_TestCase2()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc0_sReg.SC2                         = 0u;

  //Step 2) Assign Input values
  Adc_Drv_GetAdcCompleteConvStat_Param1 = &Adc0_sReg;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_GetAdcCompleteConvStat_RetVal = Adc_Drv_GetAdcCompleteConvStat(Adc_Drv_GetAdcCompleteConvStat_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_GetAdcCompleteConvStat_RetVal, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Adc_Drv_EolCalibration_TestCase1
///
/// \Test Case Description: EOL calibration failed due the input parameter invalid (NULL_PTR)
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Adc_Drv_EolCalibration_Param1 = NULL_PTR
///
/// - Expectations: 
///
/// \output Adc_Drv_EolCalibration_RetVal = E_NOT_OK
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_EolCalibration_TestCase1()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  //-----

  //Step 2) Assign Input values
  Adc_Drv_EolCalibration_Param1 = NULL_PTR;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_EolCalibration_RetVal = Adc_Drv_EolCalibration(Adc_Drv_EolCalibration_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_EolCalibration_RetVal, E_NOT_OK, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Adc_Drv_EolCalibration_TestCase2
///
/// \Test Case Description: EOL calibration failed due the ADC instance invalid (> 1u)
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Adc_Drv_EolCalibration_Param1 = &Adc_Drv_Adc_Drv_EolCalibration_Param1_Dummy
/// \input Adc_Drv_Adc_Drv_EolCalibration_Param1_Dummy.ucAdcInst = 3u
///
/// - Expectations: 
///
/// \output Adc_Drv_EolCalibration_RetVal = E_NOT_OK
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_EolCalibration_TestCase2()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc_Drv_Adc_Drv_EolCalibration_Param1_Dummy.ucAdcInst = 3u;

  //Step 2) Assign Input values
  Adc_Drv_EolCalibration_Param1 = &Adc_Drv_Adc_Drv_EolCalibration_Param1_Dummy;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_EolCalibration_RetVal = Adc_Drv_EolCalibration(Adc_Drv_EolCalibration_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_EolCalibration_RetVal, E_NOT_OK, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Adc_Drv_EolCalibration_TestCase3
///
/// \Test Case Description: EOL calibration failed due the invalid EOL parameters address
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Adc_Drv_EolCalibration_Param1 = &Adc_Drv_Adc_Drv_EolCalibration_Param1_Dummy
/// \input Adc_Drv_Adc_Drv_EolCalibration_Param1_Dummy.ucAdcInst = 0u
/// \input Adc_Drv_Adc_Drv_EolCalibration_Param1_Dummy.pfCalibrationParm = Adc_EolCalibration_ADC0
/// \input Adc_EolCalibration_ADC0_Param1 = NULL_PTR
/// \input Adc_EolCalibration_ADC0_HitCount = 0u
/// \input  Adc_EolCalibration_ADC0_RetVal = FALSE
///
/// - Expectations: 
///
/// \output Adc_Drv_EolCalibration_RetVal = E_NOT_OK
/// \output Adc_EolCalibration_ADC0_HitCount = 1u
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_EolCalibration_TestCase3()
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Adc_Drv_Adc_Drv_EolCalibration_Param1_Dummy.ucAdcInst = 0u;
  Adc_Drv_Adc_Drv_EolCalibration_Param1_Dummy.pfCalibrationParm = Adc_EolCalibration_ADC0;
  Adc_EolCalibration_ADC0_HitCount = 0u;
  Adc_EolCalibration_ADC0_Param1 = NULL_PTR;
  Adc_EolCalibration_ADC0_RetVal = FALSE;

  //Step 2) Assign Input values
  Adc_Drv_EolCalibration_Param1 = &Adc_Drv_Adc_Drv_EolCalibration_Param1_Dummy;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_EolCalibration_RetVal = Adc_Drv_EolCalibration(Adc_Drv_EolCalibration_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_EolCalibration_RetVal, E_NOT_OK, == );
  AL_UNITTEST_CHECK(Adc_EolCalibration_ADC0_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Adc_Drv_EolCalibration_TestCase4
///
/// \Test Case Description: EOL calibration passed for ADC0
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Adc_Drv_EolCalibration_Param1 = &Adc_Drv_Adc_Drv_EolCalibration_Param1_Dummy
/// \input Adc_Drv_Adc_Drv_EolCalibration_Param1_Dummy.ucAdcInst = 0u
/// \input Adc_Drv_Adc_Drv_EolCalibration_Param1_Dummy.pfCalibrationParm = Adc_EolCalibration_ADC0
/// \input Adc_EolCalibration_ADC0_Param1 = &Adc0_Eft_Data[0]
/// \input Adc_EolCalibration_ADC0_HitCount = 0u
/// \input Adc_EolCalibration_ADC0_RetVal = TRUE
/// \input psADC_Inst = ADC0
/// \input psADC_Inst->BASE_OFS = 0u
/// \input psADC_Inst->OFS = 0u
/// \input psADC_Inst->USR_OFS = 0u
/// \input psADC_Inst->XOFS = 0u
/// \input psADC_Inst->YOFS = 0u
/// \input psADC_Inst->G = 0u
/// \input psADC_Inst->UG = 0u
/// \input psADC_Inst->CLPS = 0u
/// \input psADC_Inst->CLP3 = 0u
/// \input psADC_Inst->CLP2 = 0u
/// \input psADC_Inst->CLP1 = 0u
/// \input psADC_Inst->CLP0 = 0u
/// \input psADC_Inst->CLPX = 0u
/// \input psADC_Inst->CLP9 = 0u
/// \input psADC_Inst->CLPS_OFS = 0u
/// \input psADC_Inst->CLP3_OFS = 0u
/// \input psADC_Inst->CLP2_OFS = 0u
/// \input psADC_Inst->CLP1_OFS = 0u
/// \input psADC_Inst->CLP0_OFS = 0u
/// \input psADC_Inst->CLPX_OFS = 0u
/// \input psADC_Inst->CLP9_OFS = 0u
///
/// - Expectations: 
///
/// \output Adc_Drv_EolCalibration_RetVal = E_OK
/// \output Adc_EolCalibration_ADC0_HitCount = 1u
/// \output psADC_Inst->BASE_OFS = 0u
/// \output psADC_Inst->OFS = 1u
/// \output psADC_Inst->USR_OFS = 2u
/// \output psADC_Inst->XOFS = 3u
/// \output psADC_Inst->YOFS = 4u
/// \output psADC_Inst->G = 5u
/// \output psADC_Inst->UG = 6u
/// \output psADC_Inst->CLPS = 7u
/// \output psADC_Inst->CLP3 = 8u
/// \output psADC_Inst->CLP2 = 9u
/// \output psADC_Inst->CLP1 = 10u
/// \output psADC_Inst->CLP0 = 11u
/// \output psADC_Inst->CLPX = 12u
/// \output psADC_Inst->CLP9 = 13u
/// \output psADC_Inst->CLPS_OFS = 14u
/// \output psADC_Inst->CLP3_OFS = 15u
/// \output psADC_Inst->CLP2_OFS = 16u
/// \output psADC_Inst->CLP1_OFS = 17u
/// \output psADC_Inst->CLP0_OFS = 18u
/// \output psADC_Inst->CLPX_OFS = 19u
/// \output psADC_Inst->CLP9_OFS = 20u
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_EolCalibration_TestCase4()
{
  ADC_Type *psADC_Inst = NULL_PTR;

  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  psADC_Inst = ADC0;
  Adc_Drv_Adc_Drv_EolCalibration_Param1_Dummy.ucAdcInst = 0u;
  Adc_Drv_Adc_Drv_EolCalibration_Param1_Dummy.pfCalibrationParm = Adc_EolCalibration_ADC0;
  Adc_EolCalibration_ADC0_HitCount = 0u;
  Adc_EolCalibration_ADC0_Param1 = &Adc0_Eft_Data[0];
  Adc_EolCalibration_ADC0_RetVal = TRUE;
  psADC_Inst->BASE_OFS = 0u;
  psADC_Inst->OFS = 0u;
  psADC_Inst->USR_OFS = 0u;
  psADC_Inst->XOFS = 0u;
  psADC_Inst->YOFS = 0u;
  psADC_Inst->G = 0u;
  psADC_Inst->UG = 0u;
  psADC_Inst->CLPS = 0u;
  psADC_Inst->CLP3 = 0u;
  psADC_Inst->CLP2 = 0u;
  psADC_Inst->CLP1 = 0u;
  psADC_Inst->CLP0 = 0u;
  psADC_Inst->CLPX = 0u;
  psADC_Inst->CLP9 = 0u;
  psADC_Inst->CLPS_OFS = 0u;
  psADC_Inst->CLP3_OFS = 0u;
  psADC_Inst->CLP2_OFS = 0u;
  psADC_Inst->CLP1_OFS = 0u;
  psADC_Inst->CLP0_OFS = 0u;
  psADC_Inst->CLPX_OFS = 0u;
  psADC_Inst->CLP9_OFS = 0u;

  //Step 2) Assign Input values
  Adc_Drv_EolCalibration_Param1 = &Adc_Drv_Adc_Drv_EolCalibration_Param1_Dummy;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_EolCalibration_RetVal = Adc_Drv_EolCalibration(Adc_Drv_EolCalibration_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_EolCalibration_RetVal, E_OK, == );
  AL_UNITTEST_CHECK(Adc_EolCalibration_ADC0_HitCount, 1u, == );
  AL_UNITTEST_CHECK(psADC_Inst->BASE_OFS, 0u, == );
  AL_UNITTEST_CHECK(psADC_Inst->OFS, 1u, == );
  AL_UNITTEST_CHECK(psADC_Inst->USR_OFS, 2u, == );
  AL_UNITTEST_CHECK(psADC_Inst->XOFS, 3u, == );
  AL_UNITTEST_CHECK(psADC_Inst->YOFS, 4u, == );
  AL_UNITTEST_CHECK(psADC_Inst->G, 5u, == );
  AL_UNITTEST_CHECK(psADC_Inst->UG, 6u, == );
  AL_UNITTEST_CHECK(psADC_Inst->CLPS, 7u, == );
  AL_UNITTEST_CHECK(psADC_Inst->CLP3, 8u, == );
  AL_UNITTEST_CHECK(psADC_Inst->CLP2, 9u, == );
  AL_UNITTEST_CHECK(psADC_Inst->CLP1, 10u, == );
  AL_UNITTEST_CHECK(psADC_Inst->CLP0, 11u, == );
  AL_UNITTEST_CHECK(psADC_Inst->CLPX, 12u, == );
  AL_UNITTEST_CHECK(psADC_Inst->CLP9, 13u, == );
  AL_UNITTEST_CHECK(psADC_Inst->CLPS_OFS, 14u, == );
  AL_UNITTEST_CHECK(psADC_Inst->CLP3_OFS, 15u, == );
  AL_UNITTEST_CHECK(psADC_Inst->CLP2_OFS, 16u, == );
  AL_UNITTEST_CHECK(psADC_Inst->CLP1_OFS, 17u, == );
  AL_UNITTEST_CHECK(psADC_Inst->CLP0_OFS, 18u, == );
  AL_UNITTEST_CHECK(psADC_Inst->CLPX_OFS, 19u, == );
  AL_UNITTEST_CHECK(psADC_Inst->CLP9_OFS, 20u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Adc_Drv_EolCalibration_TestCase5
///
/// \Test Case Description: EOL calibration passed for ADC1
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Adc_Drv_EolCalibration_Param1 = &Adc_Drv_Adc_Drv_EolCalibration_Param1_Dummy
/// \input Adc_Drv_Adc_Drv_EolCalibration_Param1_Dummy.ucAdcInst = 1u
/// \input Adc_Drv_Adc_Drv_EolCalibration_Param1_Dummy.pfCalibrationParm = Adc_EolCalibration_ADC1
/// \input Adc_EolCalibration_ADC1_Param1 = &Adc1_Eft_Data[0]
/// \input Adc_EolCalibration_ADC1_HitCount = 0u
/// \input Adc_EolCalibration_ADC1_RetVal = TRUE
/// \input psADC_Inst = ADC1
/// \input psADC_Inst->BASE_OFS = 0u
/// \input psADC_Inst->OFS = 0u
/// \input psADC_Inst->USR_OFS = 0u
/// \input psADC_Inst->XOFS = 0u
/// \input psADC_Inst->YOFS = 0u
/// \input psADC_Inst->G = 0u
/// \input psADC_Inst->UG = 0u
/// \input psADC_Inst->CLPS = 0u
/// \input psADC_Inst->CLP3 = 0u
/// \input psADC_Inst->CLP2 = 0u
/// \input psADC_Inst->CLP1 = 0u
/// \input psADC_Inst->CLP0 = 0u
/// \input psADC_Inst->CLPX = 0u
/// \input psADC_Inst->CLP9 = 0u
/// \input psADC_Inst->CLPS_OFS = 0u
/// \input psADC_Inst->CLP3_OFS = 0u
/// \input psADC_Inst->CLP2_OFS = 0u
/// \input psADC_Inst->CLP1_OFS = 0u
/// \input psADC_Inst->CLP0_OFS = 0u
/// \input psADC_Inst->CLPX_OFS = 0u
/// \input psADC_Inst->CLP9_OFS = 0u
///
/// - Expectations: 
///
/// \output Adc_Drv_EolCalibration_RetVal = E_OK
/// \output Adc_EolCalibration_ADC1_HitCount = 1u
/// \output psADC_Inst->BASE_OFS = 21u
/// \output psADC_Inst->OFS = 22u
/// \output psADC_Inst->USR_OFS = 23u
/// \output psADC_Inst->XOFS = 24u
/// \output psADC_Inst->YOFS = 25u
/// \output psADC_Inst->G = 26u
/// \output psADC_Inst->UG = 27u
/// \output psADC_Inst->CLPS = 28u
/// \output psADC_Inst->CLP3 = 29u
/// \output psADC_Inst->CLP2 = 30u
/// \output psADC_Inst->CLP1 = 31u
/// \output psADC_Inst->CLP0 = 32u
/// \output psADC_Inst->CLPX = 33u
/// \output psADC_Inst->CLP9 = 34u
/// \output psADC_Inst->CLPS_OFS = 35u
/// \output psADC_Inst->CLP3_OFS = 36u
/// \output psADC_Inst->CLP2_OFS = 37u
/// \output psADC_Inst->CLP1_OFS = 38u
/// \output psADC_Inst->CLP0_OFS = 39u
/// \output psADC_Inst->CLPX_OFS = 40u
/// \output psADC_Inst->CLP9_OFS = 41u
//-----------------------------------------------------------------------------
void Mt_Adc_Drv_EolCalibration_TestCase5()
{
  ADC_Type *psADC_Inst = NULL_PTR;

  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  psADC_Inst = ADC1;
  Adc_Drv_Adc_Drv_EolCalibration_Param1_Dummy.ucAdcInst = 1u;
  Adc_Drv_Adc_Drv_EolCalibration_Param1_Dummy.pfCalibrationParm = Adc_EolCalibration_ADC1;
  Adc_EolCalibration_ADC1_HitCount = 0u;
  Adc_EolCalibration_ADC1_Param1 = &Adc1_Eft_Data[0];
  Adc_EolCalibration_ADC1_RetVal = TRUE;
  psADC_Inst->BASE_OFS = 0u;
  psADC_Inst->OFS = 0u;
  psADC_Inst->USR_OFS = 0u;
  psADC_Inst->XOFS = 0u;
  psADC_Inst->YOFS = 0u;
  psADC_Inst->G = 0u;
  psADC_Inst->UG = 0u;
  psADC_Inst->CLPS = 0u;
  psADC_Inst->CLP3 = 0u;
  psADC_Inst->CLP2 = 0u;
  psADC_Inst->CLP1 = 0u;
  psADC_Inst->CLP0 = 0u;
  psADC_Inst->CLPX = 0u;
  psADC_Inst->CLP9 = 0u;
  psADC_Inst->CLPS_OFS = 0u;
  psADC_Inst->CLP3_OFS = 0u;
  psADC_Inst->CLP2_OFS = 0u;
  psADC_Inst->CLP1_OFS = 0u;
  psADC_Inst->CLP0_OFS = 0u;
  psADC_Inst->CLPX_OFS = 0u;
  psADC_Inst->CLP9_OFS = 0u;

  //Step 2) Assign Input values
  Adc_Drv_EolCalibration_Param1 = &Adc_Drv_Adc_Drv_EolCalibration_Param1_Dummy;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Adc_Drv_EolCalibration_RetVal = Adc_Drv_EolCalibration(Adc_Drv_EolCalibration_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Adc_Drv_EolCalibration_RetVal, E_OK, == );
  AL_UNITTEST_CHECK(Adc_EolCalibration_ADC0_HitCount, 1u, == );
  AL_UNITTEST_CHECK(psADC_Inst->BASE_OFS, 21u, == );
  AL_UNITTEST_CHECK(psADC_Inst->OFS, 22u, == );
  AL_UNITTEST_CHECK(psADC_Inst->USR_OFS, 23u, == );
  AL_UNITTEST_CHECK(psADC_Inst->XOFS, 24u, == );
  AL_UNITTEST_CHECK(psADC_Inst->YOFS, 25u, == );
  AL_UNITTEST_CHECK(psADC_Inst->G, 26u, == );
  AL_UNITTEST_CHECK(psADC_Inst->UG, 27u, == );
  AL_UNITTEST_CHECK(psADC_Inst->CLPS, 28u, == );
  AL_UNITTEST_CHECK(psADC_Inst->CLP3, 29u, == );
  AL_UNITTEST_CHECK(psADC_Inst->CLP2, 30u, == );
  AL_UNITTEST_CHECK(psADC_Inst->CLP1, 31u, == );
  AL_UNITTEST_CHECK(psADC_Inst->CLP0, 32u, == );
  AL_UNITTEST_CHECK(psADC_Inst->CLPX, 33u, == );
  AL_UNITTEST_CHECK(psADC_Inst->CLP9, 34u, == );
  AL_UNITTEST_CHECK(psADC_Inst->CLPS_OFS, 35u, == );
  AL_UNITTEST_CHECK(psADC_Inst->CLP3_OFS, 36u, == );
  AL_UNITTEST_CHECK(psADC_Inst->CLP2_OFS, 37u, == );
  AL_UNITTEST_CHECK(psADC_Inst->CLP1_OFS, 38u, == );
  AL_UNITTEST_CHECK(psADC_Inst->CLP0_OFS, 39u, == );
  AL_UNITTEST_CHECK(psADC_Inst->CLPX_OFS, 40u, == );
  AL_UNITTEST_CHECK(psADC_Inst->CLP9_OFS, 41u, == );
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
 //Adc.c:
 ALUnitTest_AddFunction("Mt_Adc_Init_TestCase1"                      , Mt_Adc_Init_TestCase1);
 ALUnitTest_AddFunction("Mt_Adc_Init_TestCase2"                      , Mt_Adc_Init_TestCase2);
 ALUnitTest_AddFunction("Mt_Adc_Init_TestCase3"                      , Mt_Adc_Init_TestCase3);

 ALUnitTest_AddFunction("Mt_Adc_ReadGroup_TestCase"                  , Mt_Adc_ReadGroup_TestCase);
 
 ///Adc_Dma.c:
 ALUnitTest_AddFunction("Mt_Adc_Dma_InitDmaJob_TestCase1"            , Mt_Adc_Dma_InitDmaJob_TestCase1);
 ALUnitTest_AddFunction("Mt_Adc_Dma_InitDmaJob_TestCase2"            , Mt_Adc_Dma_InitDmaJob_TestCase2);
 
 ALUnitTest_AddFunction("Mt_Adc_Dma_SetDmaParam_TestCase1"           , Mt_Adc_Dma_SetDmaParam_TestCase1); 
 ALUnitTest_AddFunction("Mt_Adc_Dma_SetDmaParam_TestCase2"           , Mt_Adc_Dma_SetDmaParam_TestCase2);
 
 //Adc_Drv.c:
 ALUnitTest_AddFunction("Mt_Adc_Drv_InitAdc_TestCase1"               , Mt_Adc_Drv_InitAdc_TestCase1);
 ALUnitTest_AddFunction("Mt_Adc_Drv_InitAdc_TestCase2"               , Mt_Adc_Drv_InitAdc_TestCase2);
 ALUnitTest_AddFunction("Mt_Adc_Drv_InitAdc_TestCase3"               , Mt_Adc_Drv_InitAdc_TestCase3);
 //
 ALUnitTest_AddFunction("Mt_Adc_Drv_ConfigAdc_TestCase1"             , Mt_Adc_Drv_ConfigAdc_TestCase1);
 ALUnitTest_AddFunction("Mt_Adc_Drv_ConfigAdc_TestCase2"             , Mt_Adc_Drv_ConfigAdc_TestCase2);
 ALUnitTest_AddFunction("Mt_Adc_Drv_ConfigAdc_TestCase3"             , Mt_Adc_Drv_ConfigAdc_TestCase3);

 ALUnitTest_AddFunction("Mt_Adc_Drv_AutoCalibration_TestCase1"       , Mt_Adc_Drv_AutoCalibration_TestCase1);
 ALUnitTest_AddFunction("Mt_Adc_Drv_AutoCalibration_TestCase2"       , Mt_Adc_Drv_AutoCalibration_TestCase2);
 ALUnitTest_AddFunction("Mt_Adc_Drv_AutoCalibration_TestCase3"       , Mt_Adc_Drv_AutoCalibration_TestCase3);
 ALUnitTest_AddFunction("Mt_Adc_Drv_AutoCalibration_TestCase4"       , Mt_Adc_Drv_AutoCalibration_TestCase4);
 ALUnitTest_AddFunction("Mt_Adc_Drv_AutoCalibration_TestCase5"       , Mt_Adc_Drv_AutoCalibration_TestCase5);
 ALUnitTest_AddFunction("Mt_Adc_Drv_AutoCalibration_TestCase6"       , Mt_Adc_Drv_AutoCalibration_TestCase6);
 ALUnitTest_AddFunction("Mt_Adc_Drv_AutoCalibration_TestCase7"       , Mt_Adc_Drv_AutoCalibration_TestCase7);
 ALUnitTest_AddFunction("Mt_Adc_Drv_AutoCalibration_TestCase8"       , Mt_Adc_Drv_AutoCalibration_TestCase8);
 
 ALUnitTest_AddFunction("Mt_Adc_Drv_AdcChInit_TestCase1"             , Mt_Adc_Drv_AdcChInit_TestCase1);
 ALUnitTest_AddFunction("Mt_Adc_Drv_AdcChInit_TestCase2"             , Mt_Adc_Drv_AdcChInit_TestCase2);
 
 ALUnitTest_AddFunction("Mt_Adc_Drv_SwReadChannel_TestCase1"         , Mt_Adc_Drv_SwReadChannel_TestCase1);
 ALUnitTest_AddFunction("Mt_Adc_Drv_SwReadChannel_TestCase2"         , Mt_Adc_Drv_SwReadChannel_TestCase2);
 ALUnitTest_AddFunction("Mt_Adc_Drv_SwReadChannel_TestCase3"         , Mt_Adc_Drv_SwReadChannel_TestCase3);
 
 ALUnitTest_AddFunction("Mt_Adc_Drv_GetAdcRawValue_TestCase1"        , Mt_Adc_Drv_GetAdcRawValue_TestCase1);
 ALUnitTest_AddFunction("Mt_Adc_Drv_GetAdcRawValue_TestCase2"        , Mt_Adc_Drv_GetAdcRawValue_TestCase2);
 
 ALUnitTest_AddFunction("Mt_Adc_Drv_SetAdcClkDivider_TestCase1"      , Mt_Adc_Drv_SetAdcClkDivider_TestCase1);
 ALUnitTest_AddFunction("Mt_Adc_Drv_SetAdcClkDivider_TestCase2"      , Mt_Adc_Drv_SetAdcClkDivider_TestCase2);
 
 ALUnitTest_AddFunction("Mt_Adc_Drv_SetAdcSampleNr_TestCase1"        , Mt_Adc_Drv_SetAdcSampleNr_TestCase1);
 ALUnitTest_AddFunction("Mt_Adc_Drv_SetAdcSampleNr_TestCase2"        , Mt_Adc_Drv_SetAdcSampleNr_TestCase2);
 
 ALUnitTest_AddFunction("Mt_Adc_Drv_SetAdcResolution_TestCase1"      , Mt_Adc_Drv_SetAdcResolution_TestCase1);
 ALUnitTest_AddFunction("Mt_Adc_Drv_SetAdcResolution_TestCase2"      , Mt_Adc_Drv_SetAdcResolution_TestCase2);
 
 ALUnitTest_AddFunction("Mt_Adc_Drv_SetAdcClkIn_TestCase1"           , Mt_Adc_Drv_SetAdcClkIn_TestCase1);
 ALUnitTest_AddFunction("Mt_Adc_Drv_SetAdcClkIn_TestCase2"           , Mt_Adc_Drv_SetAdcClkIn_TestCase2);
 
 ALUnitTest_AddFunction("Mt_Adc_Drv_SetAdcTrgType_TestCase1"         , Mt_Adc_Drv_SetAdcTrgType_TestCase1);
 ALUnitTest_AddFunction("Mt_Adc_Drv_SetAdcTrgType_TestCase2"         , Mt_Adc_Drv_SetAdcTrgType_TestCase2);
 
 ALUnitTest_AddFunction("Mt_Adc_Drv_SetAdcTrgInput_TestCase1"        , Mt_Adc_Drv_SetAdcTrgInput_TestCase1);
 ALUnitTest_AddFunction("Mt_Adc_Drv_SetAdcTrgInput_TestCase2"        , Mt_Adc_Drv_SetAdcTrgInput_TestCase2);
 ALUnitTest_AddFunction("Mt_Adc_Drv_SetAdcTrgInput_TestCase3"        , Mt_Adc_Drv_SetAdcTrgInput_TestCase3);
 ALUnitTest_AddFunction("Mt_Adc_Drv_SetAdcTrgInput_TestCase4"        , Mt_Adc_Drv_SetAdcTrgInput_TestCase4);
 
 ALUnitTest_AddFunction("Mt_Adc_Drv_SetAdcPreTrgInput_TestCase1"     , Mt_Adc_Drv_SetAdcPreTrgInput_TestCase1);
 ALUnitTest_AddFunction("Mt_Adc_Drv_SetAdcPreTrgInput_TestCase2"     , Mt_Adc_Drv_SetAdcPreTrgInput_TestCase2);
 ALUnitTest_AddFunction("Mt_Adc_Drv_SetAdcPreTrgInput_TestCase3"     , Mt_Adc_Drv_SetAdcPreTrgInput_TestCase3);
 ALUnitTest_AddFunction("Mt_Adc_Drv_SetAdcPreTrgInput_TestCase4"     , Mt_Adc_Drv_SetAdcPreTrgInput_TestCase4);

 ALUnitTest_AddFunction("Mt_Adc_Drv_SetAdcDmaEnbl_TestCase1"         , Mt_Adc_Drv_SetAdcDmaEnbl_TestCase1);
 ALUnitTest_AddFunction("Mt_Adc_Drv_SetAdcDmaEnbl_TestCase2"         , Mt_Adc_Drv_SetAdcDmaEnbl_TestCase2);
 
 ALUnitTest_AddFunction("Mt_Adc_Drv_SetAdcRefSel_TestCase1"          , Mt_Adc_Drv_SetAdcRefSel_TestCase1);
 ALUnitTest_AddFunction("Mt_Adc_Drv_SetAdcRefSel_TestCase2"          , Mt_Adc_Drv_SetAdcRefSel_TestCase2);
 
 ALUnitTest_AddFunction("Mt_Adc_Drv_SetAdcAvgEnbl_TestCase1"         , Mt_Adc_Drv_SetAdcAvgEnbl_TestCase1);
 ALUnitTest_AddFunction("Mt_Adc_Drv_SetAdcAvgEnbl_TestCase2"         , Mt_Adc_Drv_SetAdcAvgEnbl_TestCase2);
 
 ALUnitTest_AddFunction("Mt_Adc_Drv_SetAdcAvgMode_TestCase1"         , Mt_Adc_Drv_SetAdcAvgMode_TestCase1);
 ALUnitTest_AddFunction("Mt_Adc_Drv_SetAdcAvgMode_TestCase2"         , Mt_Adc_Drv_SetAdcAvgMode_TestCase2);
 
 ALUnitTest_AddFunction("Mt_Adc_Drv_SetAdcContinousMode_TestCase1"   , Mt_Adc_Drv_SetAdcContinousMode_TestCase1);
 ALUnitTest_AddFunction("Mt_Adc_Drv_SetAdcContinousMode_TestCase2"   , Mt_Adc_Drv_SetAdcContinousMode_TestCase2);
 
 ALUnitTest_AddFunction("Mt_Adc_Drv_SetAdcSupplyEn_TestCase1"        , Mt_Adc_Drv_SetAdcSupplyEn_TestCase1);
 ALUnitTest_AddFunction("Mt_Adc_Drv_SetAdcSupplyEn_TestCase2"        , Mt_Adc_Drv_SetAdcSupplyEn_TestCase2);
 
 ALUnitTest_AddFunction("Mt_Adc_Drv_SetAdcStartCalibration"          , Mt_Adc_Drv_SetAdcStartCalibration);
 
 ALUnitTest_AddFunction("Mt_Adc_Drv_GetCalibrationStatus_TestCase1"  , Mt_Adc_Drv_GetCalibrationStatus_TestCase1);
 ALUnitTest_AddFunction("Mt_Adc_Drv_GetCalibrationStatus_TestCase2"  , Mt_Adc_Drv_GetCalibrationStatus_TestCase2);
 
 ALUnitTest_AddFunction("Mt_Adc_Drv_SetAdcChnInput_TestCase1"        , Mt_Adc_Drv_SetAdcChnInput_TestCase1);
 ALUnitTest_AddFunction("Mt_Adc_Drv_SetAdcChnInput_TestCase2"        , Mt_Adc_Drv_SetAdcChnInput_TestCase2);
 ALUnitTest_AddFunction("Mt_Adc_Drv_SetAdcChnInput_TestCase3"        , Mt_Adc_Drv_SetAdcChnInput_TestCase3);
 
 ALUnitTest_AddFunction("Mt_Adc_Drv_GetAdcCompleteConvStat_TestCase1", Mt_Adc_Drv_GetAdcCompleteConvStat_TestCase1);
 ALUnitTest_AddFunction("Mt_Adc_Drv_GetAdcCompleteConvStat_TestCase2", Mt_Adc_Drv_GetAdcCompleteConvStat_TestCase2);

 ALUnitTest_AddFunction("Mt_Adc_Drv_EolCalibration_TestCase1"        , Mt_Adc_Drv_EolCalibration_TestCase1);
 ALUnitTest_AddFunction("Mt_Adc_Drv_EolCalibration_TestCase2"        , Mt_Adc_Drv_EolCalibration_TestCase2);
 ALUnitTest_AddFunction("Mt_Adc_Drv_EolCalibration_TestCase3"        , Mt_Adc_Drv_EolCalibration_TestCase3);
 ALUnitTest_AddFunction("Mt_Adc_Drv_EolCalibration_TestCase4"        , Mt_Adc_Drv_EolCalibration_TestCase4);
 ALUnitTest_AddFunction("Mt_Adc_Drv_EolCalibration_TestCase5"        , Mt_Adc_Drv_EolCalibration_TestCase5);
}
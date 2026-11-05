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
/// \brief Unit tests for CddTps92520.c and CddTps92520_Com.c
///
//-----------------------------------------------------------------------------

#include <ALUnitTest_UserInterface.h>

// Stub headers
#include "Test_Stubs.h"
#include "Test_Ext.h"

// Headers of the unit test Module
#include "Test.h"

//-----------------------------------------------------------------------------
// Initialization of test cases
//-----------------------------------------------------------------------------
static void InitConditions(void)
{
  TestExt_RestoreStubContents();
}

// ----------------------------------------------------------------------------
// CddTpsGen2_Com Unit Test Cases 
//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_UartTx
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Check if the tx buffer is filled correctly
///
///    - Test Design Technique: DT (Decision Table)
/// 
///    - Preconditions:
/// \input  const asTestCaseData[] =
///       {       //  ucTestSchedIx   ucTestChipIdx   eI2C_State                   ucChipIdx_EE  x 
///       /* 0 */   {{ 0x0u         ,  0x0u         , CddTpsGen2_I2C_NotInit     , 0x0u         }
///       /* 1 */   {{ 0x1u         ,  0x0u         , CddTpsGen2_I2C_NotInit     , 0x0u         }
///       /* 2 */   {{ 0x2u         ,  0x0u         , CddTpsGen2_I2C_NotInit     , 0x0u         }
///       /* 3 */   {{ 0x3u         ,  0x0u         , CddTpsGen2_I2C_NotInit     , 0x0u         }
///       /* 4 */   {{ 0x4u         ,  0x2u         , CddTpsGen2_I2C_NotInit     , 0x0u         }
///       /* 5 */   {{ 0x9u         ,  0x1u         , CddTpsGen2_I2C_NotInit     , 0x0u         }
///                 /* TEST for TableEE*/
///       /* 6 */   {{ 0x0u         ,  0x1u         , CddTpsGen2_I2C_Init        , 0x0u         }
///       /* 7 */   {{ 0x0u         ,  0x2u         , CddTpsGen2_I2C_Read_Status , 0x0u         }
///                 /* TEST FOR OUT OF RANGE INPUTS */
///       /* 8 */   {{ 0x5u         ,  0x3u         , CddTpsGen2_I2C_NotInit     , 0x0u         }
///       /* 9 */   {{ 0x9u         ,  0x4u         , CddTpsGen2_I2C_NotInit     , 0x0u         }
///       /* 10*/   {{ 0x25u        ,  0x4u         , CddTpsGen2_I2C_NotInit     , 0x0u         }
///       /* 11*/   {{ 0x2u         ,  0x0u         , CddTpsGen2_I2C_NotInit     , 0x0u         }
/// \input CddTpsGen2_sDevData.ucConnectedDevices                = 3u;
/// \input CddTpsGen2_sDevData.asMasterSlaveId[0].ucPhysicalAddr = CDDTPSGEN2_DEV_ID00;
/// \input CddTpsGen2_sDevData.aucCodDevID[0]                    = 0u;
/// \input CddTpsGen2_sDevData.asMasterSlaveId[1].ucPhysicalAddr = CDDTPSGEN2_DEV_ID01;
/// \input CddTpsGen2_sDevData.aucCodDevID[1]                    = 1u;
/// \input CddTpsGen2_sDevData.asMasterSlaveId[2].ucPhysicalAddr = CDDTPSGEN2_DEV_ID03;
/// \input CddTpsGen2_sDevData.aucCodDevID[2]                    = 2u;
///
///    - Expected test results: 
/// \output   ucTestCmd                    ucTestChipAddress             ucTestRegAddr             ucTestTxData                    ucTestTxDataLength          ucTestTxDataCrc   ucTestRxDataAdd                    ucTestRxDataLength
///         { CDDTPSGEN2_WRITE_01_BYTES,  (uint8)CDDTPSGEN2_BROADCAST  , CDDTPSGEN2_AddrADCID    , CDDTPSGEN2_ADCID_Tx           , CDDTPSGEN2_LEN_1_BYTE     , {0x0u , 0x78u}  , CDDTPSGEN2_BROADCAST1_ADCID_Rx  ,  CDDTPSGEN2_LEN_0_BYTES    }
///         { CDDTPSGEN2_WRITE_01_BYTES,  (uint8)CDDTPSGEN2_BROADCAST  , CDDTPSGEN2_AddrADCID    , CDDTPSGEN2_ADCID_Tx           , CDDTPSGEN2_LEN_1_BYTE     , {0x0u , 0x78u}  , CDDTPSGEN2_BROADCAST1_ADCID_Rx  ,  CDDTPSGEN2_LEN_0_BYTES    }
///         { CDDTPSGEN2_WRITE_01_BYTES,  (uint8)CDDTPSGEN2_BROADCAST  , CDDTPSGEN2_AddrSYSCFG   , CDDTPSGEN2_SYSCFG_DEFAULT_Tx  , CDDTPSGEN2_LEN_1_BYTE     , {0x20u, 0x79u}  , CDDTPSGEN2_BROADCAST2_SYSCFG_Rx ,  CDDTPSGEN2_LEN_0_BYTES    }
///         { CDDTPSGEN2_READ_01_BYTES ,  (uint8)CDDTPSGEN2_DEV_ID00   , CDDTPSGEN2_AddrICID     , CDDTPSGEN2_Zero_Tx            , CDDTPSGEN2_LEN_0_BYTES    , {0x29u, 0x96u}  , CDDTPSGEN2_ICID_Rx              ,  CDDTPSGEN2_LEN_3_BYTES    }
///         { CDDTPSGEN2_WRITE_03_BYTES,  (uint8)CDDTPSGEN2_DEV_ID03   , CDDTPSGEN2_AddrSYSCFG   , CDDTPSGEN2_SYSCFG_Tx          , CDDTPSGEN2_LEN_3_BYTES    , {0x29u, 0x05u}  , CDDTPSGEN2_SYSCFG_Rx            ,  CDDTPSGEN2_LEN_1_BYTE     }
///         { CDDTPSGEN2_READ_16_BYTES ,  (uint8)CDDTPSGEN2_DEV_ID01   , CDDTPSGEN2_AddrSLEWRATE , CDDTPSGEN2_Zero_Tx            , CDDTPSGEN2_LEN_0_BYTES    , {0xC8u, 0x6Bu}  , CDDTPSGEN2_CONFIG1_Rx           ,  CDDTPSGEN2_LEN_18_BYTES   }
///         /* TEST for TableEE*/
///         { CDDTPSGEN2_WRITE_01_BYTES,  (uint8)CDDTPSGEN2_DEV_ID00   , CDDTPSGEN2_AddrI2CTICK  , CDDTPSGEN2_I2CTICK_EETx       , CDDTPSGEN2_LEN_1_BYTE     , {0x00u, 0x45u}  , CDDTPSGEN2_ACK_EERx             ,  CDDTPSGEN2_LEN_1_BYTE     }
///         { CDDTPSGEN2_READ_01_BYTES ,  (uint8)CDDTPSGEN2_DEV_ID00   , CDDTPSGEN2_AddrI2CSTAT  , CDDTPSGEN2_Zero_Tx            , CDDTPSGEN2_LEN_0_BYTES    , {0xE9u, 0xB8u}  , CDDTPSGEN2_I2C_STAT_EERx        ,  CDDTPSGEN2_LEN_3_BYTES    }
///         /* TEST FOR OUT OF RANGE INPUTS */
///         { 0U                       ,  0U                           , 0u                      , CDDTPSGEN2_Zero_Tx            , CDDTPSGEN2_LEN_0_BYTES    , {0x00u, 0x00u}  , CDDTPSGEN2_Dummy_Rx             ,  CDDTPSGEN2_LEN_0_BYTES    }
///         { 0U                       ,  0U                           , 0u                      , CDDTPSGEN2_Zero_Tx            , CDDTPSGEN2_LEN_0_BYTES    , {0x00u, 0x00u}  , CDDTPSGEN2_Dummy_Rx             ,  CDDTPSGEN2_LEN_0_BYTES    }
///         { 0U                       ,  0U                           , 0u                      , CDDTPSGEN2_Zero_Tx            , CDDTPSGEN2_LEN_0_BYTES    , {0x00u, 0x00u}  , CDDTPSGEN2_Dummy_Rx             ,  CDDTPSGEN2_LEN_0_BYTES    }
///         /* TEST FOR MLC NOT POWERED */                                                                                                                                                                                                    
///         { NULL_PTR                 ,  0U                           , 0u                      , NULL_PTR                      , CDDTPSGEN2_LEN_0_BYTES    , {0x00u, 0x00u}  , CDDTPSGEN2_Dummy_Rx             ,  CDDTPSGEN2_LEN_0_BYTES    }
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_UartTx(void)
{
  typedef struct tsTestDataIn
  {
    uint8 ucTestSchedIx;
    uint8 ucTestChipIdx;
    tCddTpsGen2_I2C_eState eI2C_State;
    uint8 ucChipIdx_EE;
  }tsTestDataIn;

  typedef struct tsTestDataOut
  {
    uint8  ucTestCmd;
    uint8  ucTestChipAddress;
    uint8  ucTestRegAddr;
    uint8* ucTestTxData;
    uint8  ucTestTxDataLength;
    uint8  ucTestTxDataCrc[2u];
    uint8* ucTestRxData;
    uint8  ucTestRxDataLength;
  }tsTestDataOut;

  typedef struct tsTestData
  {
    tsTestDataIn  sInputData;
    tsTestDataOut sOutputData;
  }tsTestData;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  tsTestData const asTestCaseData[] =
  {       //  ucTestSchedIx   ucTestChipIdx   eI2C_State                   ucChipIdx_EE      ucTestCmd                    ucTestChipAddress             ucTestRegAddr             ucTestTxData                    ucTestTxDataLength          ucTestTxDataCrc   ucTestRxDataAdd                    ucTestRxDataLength
  /* 0 */   {{ 0x0u         ,  0x0u         , CddTpsGen2_I2C_NotInit     , 0x0u         }, { CDDTPSGEN2_WRITE_01_BYTES,  (uint8)CDDTPSGEN2_BROADCAST  , CDDTPSGEN2_AddrADCID    , CDDTPSGEN2_ADCID_Tx           , CDDTPSGEN2_LEN_1_BYTE     , {0x0u , 0x78u}  , CDDTPSGEN2_BROADCAST1_ADCID_Rx  ,  CDDTPSGEN2_LEN_0_BYTES   }},
  /* 1 */   {{ 0x1u         ,  0x0u         , CddTpsGen2_I2C_NotInit     , 0x0u         }, { CDDTPSGEN2_WRITE_01_BYTES,  (uint8)CDDTPSGEN2_BROADCAST  , CDDTPSGEN2_AddrADCID    , CDDTPSGEN2_ADCID_Tx           , CDDTPSGEN2_LEN_1_BYTE     , {0x0u , 0x78u}  , CDDTPSGEN2_BROADCAST1_ADCID_Rx  ,  CDDTPSGEN2_LEN_0_BYTES   }},
  /* 2 */   {{ 0x2u         ,  0x0u         , CddTpsGen2_I2C_NotInit     , 0x0u         }, { CDDTPSGEN2_WRITE_01_BYTES,  (uint8)CDDTPSGEN2_BROADCAST  , CDDTPSGEN2_AddrSYSCFG   , CDDTPSGEN2_SYSCFG_DEFAULT_Tx  , CDDTPSGEN2_LEN_1_BYTE     , {0x20u, 0x79u}  , CDDTPSGEN2_BROADCAST2_SYSCFG_Rx ,  CDDTPSGEN2_LEN_0_BYTES   }},
  /* 3 */   {{ 0x3u         ,  0x0u         , CddTpsGen2_I2C_NotInit     , 0x0u         }, { CDDTPSGEN2_READ_01_BYTES ,  (uint8)CDDTPSGEN2_DEV_ID00   , CDDTPSGEN2_AddrICID     , CDDTPSGEN2_Zero_Tx            , CDDTPSGEN2_LEN_0_BYTES    , {0x29u, 0x96u}  , CDDTPSGEN2_ICID_Rx              ,  CDDTPSGEN2_LEN_3_BYTES   }},
  /* 4 */   {{ 0x4u         ,  0x2u         , CddTpsGen2_I2C_NotInit     , 0x0u         }, { CDDTPSGEN2_WRITE_03_BYTES,  (uint8)CDDTPSGEN2_DEV_ID03   , CDDTPSGEN2_AddrSYSCFG   , CDDTPSGEN2_SYSCFG_Tx          , CDDTPSGEN2_LEN_3_BYTES    , {0x29u, 0x05u}  , CDDTPSGEN2_SYSCFG_Rx            ,  CDDTPSGEN2_LEN_1_BYTE    }},
  /* 5 */   {{ 0x9u         ,  0x1u         , CddTpsGen2_I2C_NotInit     , 0x0u         }, { CDDTPSGEN2_READ_16_BYTES ,  (uint8)CDDTPSGEN2_DEV_ID01   , CDDTPSGEN2_AddrSLEWRATE , CDDTPSGEN2_Zero_Tx            , CDDTPSGEN2_LEN_0_BYTES    , {0xC8u, 0x6Bu}  , CDDTPSGEN2_CONFIG1_Rx           ,  CDDTPSGEN2_LEN_18_BYTES  }},
            /* TEST for TableEE*/
  /* 6 */   {{ 0x0u         ,  0x1u         , CddTpsGen2_I2C_Init        , 0x0u         }, { CDDTPSGEN2_WRITE_01_BYTES,  (uint8)CDDTPSGEN2_DEV_ID00   , CDDTPSGEN2_AddrI2CTICK  , CDDTPSGEN2_I2CTICK_EETx       , CDDTPSGEN2_LEN_1_BYTE     , {0x00u, 0x45u}  , CDDTPSGEN2_ACK_EERx             ,  CDDTPSGEN2_LEN_1_BYTE    }},
  /* 7 */   {{ 0x0u         ,  0x2u         , CddTpsGen2_I2C_Read_Status , 0x0u         }, { CDDTPSGEN2_READ_01_BYTES ,  (uint8)CDDTPSGEN2_DEV_ID00   , CDDTPSGEN2_AddrI2CSTAT  , CDDTPSGEN2_Zero_Tx            , CDDTPSGEN2_LEN_0_BYTES    , {0xE9u, 0xB8u}  , CDDTPSGEN2_I2C_STAT_EERx        ,  CDDTPSGEN2_LEN_3_BYTES   }},
  //          /* TEST FOR OUT OF RANGE INPUTS */
  /* 8 */   {{ 0x5u         ,  0x3u         , CddTpsGen2_I2C_NotInit     , 0x0u         }, { 0U                       ,  0U                           , 0u                      , CDDTPSGEN2_Zero_Tx            , CDDTPSGEN2_LEN_0_BYTES    , {0x00u, 0x00u}  , CDDTPSGEN2_Dummy_Rx             ,  CDDTPSGEN2_LEN_0_BYTES  }},
  /* 9 */   {{ 0x9u         ,  0x4u         , CddTpsGen2_I2C_NotInit     , 0x0u         }, { 0U                       ,  0U                           , 0u                      , CDDTPSGEN2_Zero_Tx            , CDDTPSGEN2_LEN_0_BYTES    , {0x00u, 0x00u}  , CDDTPSGEN2_Dummy_Rx             ,  CDDTPSGEN2_LEN_0_BYTES  }},
  /* 10*/   {{ 0x25u        ,  0x4u         , CddTpsGen2_I2C_NotInit     , 0x0u         }, { 0U                       ,  0U                           , 0u                      , CDDTPSGEN2_Zero_Tx            , CDDTPSGEN2_LEN_0_BYTES    , {0x00u, 0x00u}  , CDDTPSGEN2_Dummy_Rx             ,  CDDTPSGEN2_LEN_0_BYTES  }},
  //          /* TEST FOR MLC NOT POWERED */
  /* 11*/   {{ 0x2u         ,  0x0u         , CddTpsGen2_I2C_NotInit     , 0x0u         }, { NULL_PTR                 ,  0U                           , 0u                      , NULL_PTR                      , CDDTPSGEN2_LEN_0_BYTES    , {0x00u, 0x00u}  , CDDTPSGEN2_Dummy_Rx             ,  CDDTPSGEN2_LEN_0_BYTES  }},
  };

  CddTpsGen2_sDevData.ucConnectedDevices                = 3u;
  CddTpsGen2_sDevData.asMasterSlaveId[0].ucPhysicalAddr = CDDTPSGEN2_DEV_ID00;
  CddTpsGen2_sDevData.asMasterSlaveId[1].ucPhysicalAddr = CDDTPSGEN2_DEV_ID01;
  CddTpsGen2_sDevData.asMasterSlaveId[2].ucPhysicalAddr = CDDTPSGEN2_DEV_ID03;
  CddTpsGen2_sDevData.aucCodDevID[0]                    = 0u;
  CddTpsGen2_sDevData.aucCodDevID[1]                    = 1u;
  CddTpsGen2_sDevData.aucCodDevID[2]                    = 2u;

  for (uint8 ucIdx = 0u; ucIdx < ( sizeof(asTestCaseData) / sizeof(tsTestData) ) ; ucIdx++)
  {
    
    uint8 ucByteIdx;
    uint8 aucCodDevID_tested;
    tsCddUart_MessageEntryType psTxCbData;

    CddTpsGen2_ucSchedIx        = asTestCaseData[ucIdx].sInputData.ucTestSchedIx;
    CddTpsGen2_ucChipIdx        = asTestCaseData[ucIdx].sInputData.ucTestChipIdx;
    CddTpsGen2_ucChipIdx_MuxCmd = asTestCaseData[ucIdx].sInputData.ucTestChipIdx;
    CddTpsGen2_I2C_State        = asTestCaseData[ucIdx].sInputData.eI2C_State;
    CddTpsGen2_ucChipIdx_EE     = asTestCaseData[ucIdx].sInputData.ucChipIdx_EE;
    // Calculate ucTestRxData address  
    if (asTestCaseData[ucIdx].sInputData.eI2C_State == CddTpsGen2_I2C_NotInit)
    {
      aucCodDevID_tested = CddTpsGen2_sDevData.aucCodDevID[CddTpsGen2_ucChipIdx];
    }
    else
    {
      aucCodDevID_tested = asTestCaseData[ucIdx].sInputData.ucChipIdx_EE; // This is for EEPROM
    }
    /* only for the last test data, check the Uart Tx when MLC is not powered*/
    if (ucIdx < 11u)
    {
      CddMlc_IsMlcPowered_RetVal = TRUE;
      CddMlc_pfGetCodingData_RetVal.boCodingValid = TRUE;
    }
    else
    {
      CddMlc_IsMlcPowered_RetVal = FALSE;
    }

    //Step 3) Call the FUT
    CddTpsGen2_UartTx(&psTxCbData);

    //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
    if (ucIdx < 8u) // values for ucIdx < 8u are valid values; starting from ucIdx 8u input values are out of range or matrix not powered
    {
      AL_UNITTEST_CHECK(psTxCbData.pucTxData[0u]                      , asTestCaseData[ucIdx].sOutputData.ucTestCmd                       , == );
      AL_UNITTEST_CHECK(psTxCbData.pucTxData[1u]                      , asTestCaseData[ucIdx].sOutputData.ucTestChipAddress               , == );
      AL_UNITTEST_CHECK(psTxCbData.pucTxData[2u]                      , asTestCaseData[ucIdx].sOutputData.ucTestRegAddr                   , == );

      for (ucByteIdx = 3u; ucByteIdx < asTestCaseData[ucIdx].sOutputData.ucTestTxDataLength; ucByteIdx++)
      {
        AL_UNITTEST_CHECK(psTxCbData.pucTxData[ucByteIdx]             , asTestCaseData[ucIdx].sOutputData.ucTestTxData[ucByteIdx - 3u]    , == );
      }
      AL_UNITTEST_CHECK(psTxCbData.pucTxData[ucByteIdx]               , asTestCaseData[ucIdx].sOutputData.ucTestTxDataCrc[0]              , == );
      AL_UNITTEST_CHECK(psTxCbData.pucTxData[ucByteIdx+1u]            , asTestCaseData[ucIdx].sOutputData.ucTestTxDataCrc[1]              , == );
      AL_UNITTEST_CHECK(psTxCbData.ucRxDataLength                     , asTestCaseData[ucIdx].sOutputData.ucTestRxDataLength              , == );
      AL_UNITTEST_CHECK(psTxCbData.pucRxData                          , asTestCaseData[ucIdx].sOutputData.ucTestRxData + \
                  (asTestCaseData[ucIdx].sOutputData.ucTestRxDataLength * aucCodDevID_tested)                                             , == );
    }
    else
    {
      AL_UNITTEST_CHECK(psTxCbData.pucTxData                          , asTestCaseData[ucIdx].sOutputData.ucTestTxData                    , == );
      AL_UNITTEST_CHECK(psTxCbData.pucRxData                          , asTestCaseData[ucIdx].sOutputData.ucTestRxData                    , == );
      AL_UNITTEST_CHECK(psTxCbData.ucRxDataLength                     , asTestCaseData[ucIdx].sOutputData.ucTestRxDataLength              , == );
      AL_UNITTEST_CHECK(psTxCbData.ucTxDataLength                     , asTestCaseData[ucIdx].sOutputData.ucTestRxDataLength              , == );
    }
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_UartRx
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Check if the rx buffer is filled correctly
///
///    - Test Design Technique: DT (Decision Table)
///
///    - Preconditions:
/// \input tsTestData const asTestCaseData[] =
///        {//         ucTestSchedIx   ucChipIdx  boRxStatus  boInitCompleted  eI2C_State                  
///        /*0 */  { { 3u            , 0u       , FALSE     , FALSE          , CddTpsGen2_I2C_NotInit     }
///        /*1 */  { { 4u            , 1u       , TRUE      , FALSE          , CddTpsGen2_I2C_NotInit     }
///        /*2 */  { { 4u            , 3u       , TRUE      , FALSE          , CddTpsGen2_I2C_NotInit     }
///        /*3 */  { { 0u            , 0u       , FALSE     , FALSE          , CddTpsGen2_I2C_NotInit     }
///        /*4 */  { { 11u           , 0u       , FALSE     , FALSE          , CddTpsGen2_I2C_NotInit     }
///        /*5 */  { { 11u           , 2u       , TRUE      , FALSE          , CddTpsGen2_I2C_NotInit     }
///        /*6 */  { { 11u           , 3u       , TRUE      , TRUE           , CddTpsGen2_I2C_NotInit     }
///        /*7 */  { { 14u           , 1u       , FALSE     , FALSE          , CddTpsGen2_I2C_NotInit     }
///        /*8 */  { { 14u           , 2u       , FALSE     , FALSE          , CddTpsGen2_I2C_NotInit     }
///        /*9 */  { { 0u            , 0u       , FALSE     , FALSE          , CddTpsGen2_I2C_Init        }
///        /*10*/  { { 0u            , 0u       , TRUE      , FALSE          , CddTpsGen2_I2C_Read_Status }
///        /*11*/  { { 0u            , 0u       , FALSE     , TRUE           , CddTpsGen2_I2C_Read_Status }
/// \input uint8 pucRxData[50u];
/// \input uint8 ucCrc = 0x5B;
/// \input CDDTPSGEN2_Para_COUNT_CONNECTED_DEV = 3u;
/// \input CDDTPSGEN2_Para_CHIP_IDX(0u)        = 0u;
/// \input CDDTPSGEN2_Para_CHIP_IDX(1u)        = 1u;
/// \input CDDTPSGEN2_Para_CHIP_IDX(2u)        = 2u;
/// \input CDDTPSGEN2_Para_CHIP_IDX(3u)        = 3u;
/// \input CddTpsGen2_aboComStatus[1U]         = FALSE;
/// \input CddTpsGen2_aboComStatus[2U]         = FALSE;
/// \input CddTpsGen2_boReinitChips            = TRUE;
/// \input CddTpsGen2_ucSchedIxEE              = 0u;
/// \input   CddMlc_IsMlcPowered_RetVal        = FALSE;
/// 
/// \input  RX data for ucTestSchedIx 3. Crc error expected (correct CRC D80)
/// \input CddTpsGen2_DataMirror.StatRx.RxICID[0].ucRxByte[0] = 0x12; // Fill rx buffer
/// \input CddTpsGen2_DataMirror.StatRx.RxICID[0].ucRxByte[1] = 0x81; // Crc
/// \input CddTpsGen2_DataMirror.StatRx.RxICID[0].ucRxByte[2] = 0x0D; // Crc
///  
/// \input RX data for ucTestSchedIx 11. Crc correct for first scheduler call, incorrect for the next 2
/// \input CddTpsGen2_DataMirror.StatRx.RxADC[asTestCaseData[ucIdx].sInputData.ucChipIdx].ucRxByte[0] = 0xAC;     // Fill rx buffer
/// \input CddTpsGen2_DataMirror.StatRx.RxADC[asTestCaseData[ucIdx].sInputData.ucChipIdx].ucRxByte[1] = 0xDB;     // Fill rx buffer
/// \input CddTpsGen2_DataMirror.StatRx.RxADC[asTestCaseData[ucIdx].sInputData.ucChipIdx].ucRxByte[2] = 0x3D;     // Crc
/// \input CddTpsGen2_DataMirror.StatRx.RxADC[asTestCaseData[ucIdx].sInputData.ucChipIdx].ucRxByte[3] = ucCrc++;  // Crc is incrementing after first assignment
///
///    - Expected test results: 
/// \output   boComStatus_exp      ucChipIdx_MuxCmd_exp    ucChipIdx_exp   ucSchedIx_exp  ucSchedIxEE_exp  boCrcStatus_exp
///          { TRUE               , 0u                    , 1u            , 3u          , 0u              , TRUE         } }
///          { FALSE              , 1u                    , 2u            , 4u          , 0u              , FALSE        } }
///          { TRUE               , 3u                    , 0u            , 5u          , 0u              , FALSE        } }
///          { FALSE              , 0u                    , 0u            , 0u          , 0u              , FALSE        } }
///          { TRUE               , 0u                    , 0u            , 12u         , 0u              , FALSE        } }
///          { FALSE              , 2u                    , 0u            , 12u         , 0u              , TRUE         } }
///          { TRUE               , 3u                    , 0u            , 0u          , 0u              , TRUE         } }
///          { TRUE               , 2u                    , 0u            , 8u          , 0u              , FALSE        } }
///          { TRUE               , 0u                    , 0u            , 8u          , 0u              , FALSE        } }
///          { TRUE               , 0u                    , 0u            , 0u          , 1u              , FALSE        } }
///          { FALSE              , 0u                    , 0u            , 0u          , 3u              , FALSE        } }
///          { TRUE               , 0u                    , 0u            , 0u          , 0xDu            , FALSE        } }
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_UartRx(void)
{
  typedef struct tsTestDataIn
  {
    uint8   ucTestSchedIx;
    uint8   ucChipIdx;
    boolean boRxStatus;
    boolean boInitCompleted;
    tCddTpsGen2_I2C_eState eI2C_State;
  }tsTestDataIn;

  typedef struct tsTestDataOut
  {
    boolean  boComStatus_exp;
    uint8    ucChipIdx_MuxCmd_exp;
    uint8    ucChipIdx_exp;
    uint8    ucSchedIx_exp;
    uint8    ucSchedIxEE_exp;
    boolean  boCrcStatus_exp;
  }tsTestDataOut;

  typedef struct tsTestData
  {
    tsTestDataIn  sInputData;
    tsTestDataOut sOutputData;
  }tsTestData;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  tsTestData const asTestCaseData[] =
  {//         ucTestSchedIx   ucChipIdx  boRxStatus  boInitCompleted  eI2C_State                     boComStatus_exp      ucChipIdx_MuxCmd_exp    ucChipIdx_exp   ucSchedIx_exp  ucSchedIxEE_exp  boCrcStatus_exp
  /*0 */  { { 3u            , 0u       , FALSE     , FALSE          , CddTpsGen2_I2C_NotInit     }, { TRUE               , 0u                    , 1u            , 3u          , 0u              , FALSE        } }, // boComStatus toggle for fast
  /*1 */  { { 4u            , 1u       , TRUE      , FALSE          , CddTpsGen2_I2C_NotInit     }, { FALSE              , 1u                    , 2u            , 4u          , 0u              , FALSE        } }, // boComStatus toggle for fast
  /*2 */  { { 4u            , 3u       , TRUE      , FALSE          , CddTpsGen2_I2C_NotInit     }, { TRUE               , 3u                    , 0u            , 5u          , 0u              , FALSE        } }, // boComStatus toggle for fast & CddTpsGen2_ucChipIdx too high
  /*3 */  { { 0u            , 0u       , FALSE     , FALSE          , CddTpsGen2_I2C_NotInit     }, { FALSE              , 0u                    , 0u            , 0u          , 0u              , FALSE        } }, // reset due to eBroadcastCmd
  /*4 */  { { 11u           , 0u       , FALSE     , FALSE          , CddTpsGen2_I2C_NotInit     }, { TRUE               , 0u                    , 0u            , 12u         , 0u              , FALSE        } }, // boComStatus toggle for slow
  /*5 */  { { 11u           , 2u       , TRUE      , FALSE          , CddTpsGen2_I2C_NotInit     }, { FALSE              , 2u                    , 0u            , 12u         , 0u              , TRUE         } }, // boComStatus toggle for slow, crc error
  /*6 */  { { 11u           , 3u       , FALSE     , TRUE           , CddTpsGen2_I2C_NotInit     }, { FALSE              , 3u                    , 0u            , 0u          , 0u              , FALSE        } }, // boComStatus ok, no crc error
  /*7 */  { { 14u           , 1u       , FALSE     , FALSE          , CddTpsGen2_I2C_NotInit     }, { TRUE               , 2u                    , 0u            , 8u          , 0u              , FALSE        } }, // increment ucChipIdx_MuxCmd, last scheduler command
  /*8 */  { { 14u           , 2u       , FALSE     , FALSE          , CddTpsGen2_I2C_NotInit     }, { TRUE               , 0u                    , 0u            , 8u          , 0u              , FALSE        } }, // reset ucChipIdx_MuxCmd, last scheduler command
  /*9 */  { { 0u            , 0u       , FALSE     , FALSE          , CddTpsGen2_I2C_Init        }, { TRUE               , 0u                    , 0u            , 0u          , 1u              , FALSE        } }, // EEPROM ComStatus TRUE
  /*10*/  { { 0u            , 0u       , TRUE      , FALSE          , CddTpsGen2_I2C_Read_Status }, { FALSE              , 0u                    , 0u            , 0u          , 3u              , FALSE        } }, // EEPROM ComStatus FALSE
  /*11*/  { { 0u            , 0u       , FALSE     , TRUE           , CddTpsGen2_I2C_Read_Status }, { TRUE               , 0u                    , 0u            , 0u          , 0xDu            , FALSE        } }, // EEPROM CddTpsGen2_ucSchedIxEE reset
  };

  uint8 pucRxData[50u];
  uint8 ucCrc = 0x59u;
  CDDTPSGEN2_Para_COUNT_CONNECTED_DEV = 3u;
  CDDTPSGEN2_Para_CHIP_IDX(0u)        = 0u;
  CDDTPSGEN2_Para_CHIP_IDX(1u)        = 1u;
  CDDTPSGEN2_Para_CHIP_IDX(2u)        = 2u;
  CDDTPSGEN2_Para_CHIP_IDX(3u)        = 3u;
  CddTpsGen2_aboComStatus[1U]         = FALSE;
  CddTpsGen2_aboComStatus[2U]         = FALSE;
  CddTpsGen2_boReinitChips            = TRUE;
  CddTpsGen2_ucSchedIxEE              = 0u;
  CddMlc_IsMlcPowered_RetVal          = FALSE;

  // RX data for ucTestSchedIx 3. Crc error expected (correct CRC D80)
  CddTpsGen2_DataMirror.StatRx.RxICID[0].ucRxByte[0] = 0x12; // Fill rx buffer
  CddTpsGen2_DataMirror.StatRx.RxICID[0].ucRxByte[1] = 0x81; // Crc
  CddTpsGen2_DataMirror.StatRx.RxICID[0].ucRxByte[2] = 0x0D; // Crc

  for (uint8 ucIdx = 0u; ucIdx < (sizeof(asTestCaseData) / sizeof(tsTestData)); ucIdx++)
  {
    CddTpsGen2_ucSchedIx                          = asTestCaseData[ucIdx].sInputData.ucTestSchedIx;
    CddTpsGen2_ucChipIdx                          = asTestCaseData[ucIdx].sInputData.ucChipIdx;
    CddTpsGen2_ucChipIdx_MuxCmd                   = asTestCaseData[ucIdx].sInputData.ucChipIdx;
    CddTpsGen2_aboComStatus[CddTpsGen2_ucChipIdx] = asTestCaseData[ucIdx].sInputData.boRxStatus;
    CddTpsGen2_boInitCompleted                    = asTestCaseData[ucIdx].sInputData.boInitCompleted;
    CddTpsGen2_I2C_State                          = asTestCaseData[ucIdx].sInputData.eI2C_State;
    CddTpsGen2_aboCrcStatus[asTestCaseData[ucIdx].sInputData.ucChipIdx]  = FALSE;
    // RX data for ucTestSchedIx 11. Crc correct for first scheduler call, incorrect for the next 2
    if(asTestCaseData[ucIdx].sInputData.ucTestSchedIx == 11u)
    {
      CddTpsGen2_DataMirror.StatRx.RxADC[asTestCaseData[ucIdx].sInputData.ucChipIdx].ucRxByte[0] = 0xAC;     // Fill rx buffer
      CddTpsGen2_DataMirror.StatRx.RxADC[asTestCaseData[ucIdx].sInputData.ucChipIdx].ucRxByte[1] = 0xDB;     // Fill rx buffer
      CddTpsGen2_DataMirror.StatRx.RxADC[asTestCaseData[ucIdx].sInputData.ucChipIdx].ucRxByte[2] = 0x3D;     // Crc
      CddTpsGen2_DataMirror.StatRx.RxADC[asTestCaseData[ucIdx].sInputData.ucChipIdx].ucRxByte[3] = ucCrc++;  // Crc is incrementing after first assignment
    }

    //Step 3) Call the FUT
    CddTpsGen2_UartRx(pucRxData, asTestCaseData[ucIdx].sInputData.boRxStatus);

    //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
    AL_UNITTEST_CHECK(CddTpsGen2_aboComStatus[asTestCaseData[ucIdx].sInputData.ucChipIdx]               , asTestCaseData[ucIdx].sOutputData.boComStatus_exp       , == );
    AL_UNITTEST_CHECK(CddTpsGen2_ucChipIdx_MuxCmd                                                       , asTestCaseData[ucIdx].sOutputData.ucChipIdx_MuxCmd_exp  , == );
    AL_UNITTEST_CHECK(CddTpsGen2_ucChipIdx                                                              , asTestCaseData[ucIdx].sOutputData.ucChipIdx_exp         , == );
    AL_UNITTEST_CHECK(CddTpsGen2_ucSchedIx                                                              , asTestCaseData[ucIdx].sOutputData.ucSchedIx_exp         , == );
    AL_UNITTEST_CHECK(CddTpsGen2_ucSchedIxEE                                                            , asTestCaseData[ucIdx].sOutputData.ucSchedIxEE_exp       , == );
    AL_UNITTEST_CHECK(CddTpsGen2_aboCrcStatus[asTestCaseData[ucIdx].sInputData.ucChipIdx]               , asTestCaseData[ucIdx].sOutputData.boCrcStatus_exp       , == );
  }
}


//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_StActionEE
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Test if CddTpsGen2_StActionEE function 
///          handles the actions defined in the test table correctly
///
///    - Test Design Technique: DT (Decision Table)
///
///    - Preconditions:
/// \input /  ucAction_in                            , I2C_State_in                           , ucACK_EERx_out            
///        { { CDDTPSGEN2_ST_NO_ACT                  , CddTpsGen2_I2C_Init                    , CDDTPSGEN2_ACK_BYTE      }
///        { { CDDTPSGEN2_ST_EE_CHECK_PREINIT        , CddTpsGen2_I2C_Init                    , CDDTPSGEN2_ACK_BYTE      }
///        { { CDDTPSGEN2_ST_EE_CHECK_INIT           , CddTpsGen2_I2C_Init                    , CDDTPSGEN2_ACK_BYTE      }
///        { { CDDTPSGEN2_ST_EE_READ_START           , CddTpsGen2_I2C_Read_Start              , CDDTPSGEN2_ACK_BYTE      }
///        { { CDDTPSGEN2_ST_EE_READ_STATUS          , CddTpsGen2_I2C_Init                    , CDDTPSGEN2_ACK_BYTE      }
///        { { CDDTPSGEN2_ST_EE_READ_DATA            , CddTpsGen2_I2C_Init                    , CDDTPSGEN2_ACK_BYTE      }
///        { { CDDTPSGEN2_ST_EE_WRITE_START          , CddTpsGen2_I2C_Write_Start             , CDDTPSGEN2_ACK_BYTE      }
///        { { CDDTPSGEN2_ST_EE_WRITE_STATUS         , CddTpsGen2_I2C_Init                    , CDDTPSGEN2_ACK_BYTE      }
///        { { CDDTPSGEN2_ST_EE_WRITE_DATA           , CddTpsGen2_I2C_Init                    , CDDTPSGEN2_ACK_BYTE      }
///        { { CDDTPSGEN2_ST_EE_RESET                , CddTpsGen2_I2C_Init                    , CDDTPSGEN2_ACK_BYTE      }
///        { { CDDTPSGEN2_ST_EE_RESET+1u             , CddTpsGen2_I2C_Init                    , CDDTPSGEN2_ACK_BYTE      }
///
/// \input CddTpsGen2_DataMirrorEE.StatRx.RxI2CSTAT.ucRxByte[0] = ((uint8)CDDTPSGEN2_I2CSTAT_BUSY | (uint8)CDDTPSGEN2_I2CSTAT_RFE);
/// \input CddTpsGen2_I2C_ucPtrReadData                         = NULL_PTR;
/// 
///    - Expected test results: 
/// \output   I2C_State_out               , ucACK_EERx_out
///         { CddTpsGen2_I2C_Init         , CDDTPSGEN2_ACK_BYTE  }
///         { CddTpsGen2_I2C_Init         , 0x00u                }
///         { CddTpsGen2_I2C_Idle         , 0x00u                }
///         { CddTpsGen2_I2C_Read_Status  , 0x00u                }
///         { CddTpsGen2_I2C_Init         , CDDTPSGEN2_ACK_BYTE  }
///         { CddTpsGen2_I2C_ControlReset , CDDTPSGEN2_ACK_BYTE  }
///         { CddTpsGen2_I2C_Write_Status , 0x00u                }
///         { CddTpsGen2_I2C_Init         , CDDTPSGEN2_ACK_BYTE  }
///         { CddTpsGen2_I2C_Write_Start  , 0x00u                }
///         { CddTpsGen2_I2C_Idle         , CDDTPSGEN2_ACK_BYTE  }
///         { CddTpsGen2_I2C_Init         , CDDTPSGEN2_ACK_BYTE  }
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_StActionEE(void)
{
  typedef struct tsTestDataIn
  {
    uint8   ucAction_in;
    tCddTpsGen2_I2C_eState I2C_State_in;
    uint8                  ucACK_EERx_in;
  }tsTestDataIn;

  typedef struct tsTestDataOut
  {
    tCddTpsGen2_I2C_eState I2C_State_out;
    uint8                  ucACK_EERx_out;
  }tsTestDataOut;

  typedef struct tsTestData
  {
    tsTestDataIn  sInputData;
    tsTestDataOut sOutputData;
  }tsTestData;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  boolean    boRestart;
  tsTestData const asTestCaseData[] =
  {//  ucAction_in                            , I2C_State_in                           , ucACK_EERx_out            ,  I2C_State_out               , ucACK_EERx_out
    { { CDDTPSGEN2_ST_NO_ACT                  , CddTpsGen2_I2C_Init                    , CDDTPSGEN2_ACK_BYTE      },{ CddTpsGen2_I2C_Init         , CDDTPSGEN2_ACK_BYTE  } },
    { { CDDTPSGEN2_ST_EE_CHECK_PREINIT        , CddTpsGen2_I2C_Init                    , CDDTPSGEN2_ACK_BYTE      },{ CddTpsGen2_I2C_Init         , 0x00u                } },
    { { CDDTPSGEN2_ST_EE_CHECK_INIT           , CddTpsGen2_I2C_Init                    , CDDTPSGEN2_ACK_BYTE      },{ CddTpsGen2_I2C_Idle         , 0x00u                } },
    { { CDDTPSGEN2_ST_EE_READ_START           , CddTpsGen2_I2C_Read_Start              , CDDTPSGEN2_ACK_BYTE      },{ CddTpsGen2_I2C_Read_Status  , 0x00u                } },
    { { CDDTPSGEN2_ST_EE_READ_STATUS          , CddTpsGen2_I2C_Init                    , CDDTPSGEN2_ACK_BYTE      },{ CddTpsGen2_I2C_Init         , CDDTPSGEN2_ACK_BYTE  } },
    { { CDDTPSGEN2_ST_EE_READ_DATA            , CddTpsGen2_I2C_Init                    , CDDTPSGEN2_ACK_BYTE      },{ CddTpsGen2_I2C_ControlReset , CDDTPSGEN2_ACK_BYTE  } },
    { { CDDTPSGEN2_ST_EE_WRITE_START          , CddTpsGen2_I2C_Write_Start             , CDDTPSGEN2_ACK_BYTE      },{ CddTpsGen2_I2C_Write_Status , 0x00u                } },
    { { CDDTPSGEN2_ST_EE_WRITE_STATUS         , CddTpsGen2_I2C_Init                    , CDDTPSGEN2_ACK_BYTE      },{ CddTpsGen2_I2C_Init         , CDDTPSGEN2_ACK_BYTE  } },
    { { CDDTPSGEN2_ST_EE_WRITE_DATA           , CddTpsGen2_I2C_Init                    , CDDTPSGEN2_ACK_BYTE      },{ CddTpsGen2_I2C_Write_Start  , 0x00u                } },
    { { CDDTPSGEN2_ST_EE_RESET                , CddTpsGen2_I2C_Init                    , CDDTPSGEN2_ACK_BYTE      },{ CddTpsGen2_I2C_Idle         , CDDTPSGEN2_ACK_BYTE  } },
    { { CDDTPSGEN2_ST_EE_RESET+1u             , CddTpsGen2_I2C_Init                    , CDDTPSGEN2_ACK_BYTE      },{ CddTpsGen2_I2C_Init         , CDDTPSGEN2_ACK_BYTE  } },
  };

  CddTpsGen2_DataMirrorEE.StatRx.RxI2CSTAT.ucRxByte[0] = ((uint8)CDDTPSGEN2_I2CSTAT_BUSY | (uint8)CDDTPSGEN2_I2CSTAT_RFE);
  CddTpsGen2_I2C_ucPtrReadData                         = NULL_PTR;

  for (uint8 ucIdx = 0u; ucIdx < (sizeof(asTestCaseData) / sizeof(tsTestData)); ucIdx++)
  {
    CddTpsGen2_I2C_State = asTestCaseData[ucIdx].sInputData.I2C_State_in;
    CddTpsGen2_DataMirrorEE.StatRx.RxACK = asTestCaseData[ucIdx].sInputData.ucACK_EERx_in; // set CDDTPSGEN2_ACK_EERx

    //Step 3) Call the FUT
    CddTpsGen2_StActionEE(asTestCaseData[ucIdx].sInputData.ucAction_in);

    //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
    AL_UNITTEST_CHECK(CddTpsGen2_I2C_State                    , asTestCaseData[ucIdx].sOutputData.I2C_State_out       , == );
    AL_UNITTEST_CHECK(CddTpsGen2_DataMirrorEE.StatRx.RxACK    , asTestCaseData[ucIdx].sOutputData.ucACK_EERx_out, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_StAction_TestCase_1
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Test CddTpsGen2_StAction function when ucAction
///         is in below states (ucAction_in)
///
///    - Test Design Technique: DT (Decision Table)
///
///    - Preconditions:
/// \input  ucAction_in                       boInitCompleted_in      
///        {CDDTPSGEN2_ST_NO_ACT            , TRUE                   }
///        {CDDTPSGEN2_ST_START_CYCLE       , FALSE                  }
///        {CDDTPSGEN2_ST_CHECK_RESTART     , TRUE                   }
///        {CDDTPSGEN2_ST_CHECK_RESTART + 1 , FALSE                  }
/// \input boRestart = TRUE
/// 
///    - Expected test results: 
/// \output   boInitCompleted_out   boReturnVal_out
///        {  TRUE                , FALSE           }
///        {  TRUE                , FALSE           }
///        {  FALSE               , FALSE           }
///        {  FALSE               , FALSE           }
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_StAction_TestCase_1(void)
{
  typedef struct tsTestDataIn
  {
    uint8   ucAction_in;
    boolean boInitCompleted_in;
  }tsTestDataIn;

  typedef struct tsTestDataOut
  {
    boolean  boInitCompleted_out;
    boolean  boReturnVal_out;
  }tsTestDataOut;

  typedef struct tsTestData
  {
    tsTestDataIn  sInputData;
    tsTestDataOut sOutputData;
  }tsTestData;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  boolean    boRestart;
  tsTestData const asTestCaseData[] =
  {//  ucAction_in                          boInitCompleted_in          boInitCompleted_out   boReturnVal_out
    { { CDDTPSGEN2_ST_NO_ACT               , TRUE                   },{  TRUE                , FALSE           } }, // No action
    { { CDDTPSGEN2_ST_ACT_START_CYCLE      , FALSE                  },{  TRUE                , FALSE           } }, // CddTpsGen2_boInitCompleted is set to TRUE
    { { CDDTPSGEN2_ST_ACT_CHECK_RESTART    , TRUE                   },{  FALSE               , FALSE           } }, // CddTpsGen2_boInitCompleted is set to FALSE
    { {(CDDTPSGEN2_ST_ACT_CHECK_RESTART+1) , FALSE                  },{  FALSE               , FALSE           } }, // default case
  };

  for (uint8 ucIdx = 0u; ucIdx < (sizeof(asTestCaseData) / sizeof(tsTestData)); ucIdx++)
  {
    CddTpsGen2_boInitCompleted = asTestCaseData[ucIdx].sInputData.boInitCompleted_in;
    boRestart = TRUE;

    //Step 3) Call the FUT
    boRestart = CddTpsGen2_StAction(asTestCaseData[ucIdx].sInputData.ucAction_in);

    //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
    AL_UNITTEST_CHECK(CddTpsGen2_boInitCompleted    , asTestCaseData[ucIdx].sOutputData.boInitCompleted_out     , == );
    AL_UNITTEST_CHECK(boRestart                     , asTestCaseData[ucIdx].sOutputData.boReturnVal_out         , == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_StAction_TestCase_2
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Test CddTpsGen2_StAction function when ucAction
///         is CDDTPSGEN2_ST_CHECK_START
///
///    - Test Design Technique: DT (Decision Table)
///
///    - Preconditions:
/// \input  boCddMlc_IsMlcPowered_in       boCodingValid_in      boReturnVal_in       }
///        {FALSE                        , FALSE               , FALSE                }
///        {TRUE                         , FALSE               , FALSE                }
///        {FALSE                        , TRUE                , FALSE                }
///        {TRUE                         , TRUE                , TRUE                 }
/// \input boRestart = TRUE
/// 
///    - Expected test results: 
/// \output    boReturnVal_out
///         {  TRUE            }
///         {  TRUE            }
///         {  TRUE            }
///         {  FALSE           }
/// \output CddTpsGen2_boMuxCmdCompleted = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_StAction_TestCase_2(void)
{
  typedef struct tsTestDataIn
  {
    boolean boCddMlc_IsMlcPowered_in;
    boolean boCodingValid_in;
    boolean boReturnVal_in;
  }tsTestDataIn;

  typedef struct tsTestDataOut
  {
    boolean  boReturnVal_out;
  }tsTestDataOut;

  typedef struct tsTestData
  {
    tsTestDataIn  sInputData;
    tsTestDataOut sOutputData;
  }tsTestData;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  boolean    boRestart_out;
  tsTestData const asTestCaseData[] =
  {//  boCddMlc_IsMlcPowered_in       boCodingValid_in      boReturnVal_in              boReturnVal_out
    { {FALSE                        , FALSE               , FALSE                  },{  TRUE            } },
    { {TRUE                         , FALSE               , FALSE                  },{  TRUE            } }, 
    { {FALSE                        , TRUE                , FALSE                  },{  TRUE            } }, 
    { {TRUE                         , TRUE                , TRUE                   },{  FALSE           } },
  };

  for (uint8 ucIdx = 0u; ucIdx < (sizeof(asTestCaseData) / sizeof(tsTestData)); ucIdx++)
  {
    CddTpsGen2_boMuxCmdCompleted  = TRUE;
    boRestart_out                 = asTestCaseData[ucIdx].sInputData.boReturnVal_in;
    CddMlc_IsMlcPowered_RetVal    = asTestCaseData[ucIdx].sInputData.boCddMlc_IsMlcPowered_in;
    CDDMLC_Para_IS_CODING_VALID   = asTestCaseData[ucIdx].sInputData.boCodingValid_in;

    //Step 3) Call the FUT
    boRestart_out = CddTpsGen2_StAction(CDDTPSGEN2_ST_ACT_CHECK_START);

    //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
    AL_UNITTEST_CHECK(CddTpsGen2_boMuxCmdCompleted  , FALSE                                             , == );
    AL_UNITTEST_CHECK(boRestart_out                 , asTestCaseData[ucIdx].sOutputData.boReturnVal_out , == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_StAction_TestCase_3
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Test CddTpsGen2_StAction function when ucAction
///         is CDDTPSGEN2_ST_ACT_CHECK_PWR
///
///    - Test Design Technique: DT (Decision Table)
///
///    - Preconditions:
/// \input ucRxByte_in   
///       {0xFFu        }
///       {0xFEu        }
/// 
/// \input CddTpsGen2_ucChipIdx_MuxCmd                           = 0u;
/// \input CDDTPSGEN2_Para_CHIP_IDX(CddTpsGen2_ucChipIdx_MuxCmd) = 0u;
/// \input boRestart_out                 = TRUE;
/// 
///    - Expected test results: 
/// \output    boReturnVal_out  ucPowerOnReset_Bit
///         {  FALSE           ,      0u       } 
///         {  TRUE            ,      1u       } 
///
///-----------------------------------------------------------------------------
void Mt_CddTpsGen2_StAction_TestCase_3(void)
{
  typedef struct tsTestDataIn
  {
    uint8 ucRxByte_in;
  }tsTestDataIn;

  typedef struct tsTestDataOut
  {
    boolean  boReturnVal_out;
    uint8    ucPowerOnReset_Bit_out;
  }tsTestDataOut;

  typedef struct tsTestData
  {
    tsTestDataIn  sInputData;
    tsTestDataOut sOutputData;
  }tsTestData;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  boolean    boRestart_out;
  tsTestData const asTestCaseData[] =
  {//  ucRxByte_in       boReturnVal_out  ucPowerOnReset_Bit
    { {0xFFu        },{  FALSE           ,      0u       } },
    { {0xFEu        },{  TRUE            ,      1u       } },
  };

  CddTpsGen2_ucChipIdx_MuxCmd                           = 0u;
  CDDTPSGEN2_Para_CHIP_IDX(CddTpsGen2_ucChipIdx_MuxCmd) = 0u;

  for (uint8 ucIdx = 0u; ucIdx < (sizeof(asTestCaseData) / sizeof(tsTestData)); ucIdx++)
  {
    boRestart_out                 = TRUE;
    CddTpsGen2_DataMirror.StatRx.RxCONFIG2[CDDTPSGEN2_Para_CHIP_IDX(CddTpsGen2_ucChipIdx_MuxCmd)].ucRxByte[0u] = asTestCaseData[ucIdx].sInputData.ucRxByte_in;

    //Step 3) Call the FUT
    boRestart_out = CddTpsGen2_StAction(CDDTPSGEN2_ST_ACT_CHECK_PWR);

    //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
    AL_UNITTEST_CHECK(boRestart_out                 , asTestCaseData[ucIdx].sOutputData.boReturnVal_out         , == );
    AL_UNITTEST_CHECK(CddTpsGen2_ucPowerOnReset_Bit , asTestCaseData[ucIdx].sOutputData.ucPowerOnReset_Bit_out  , == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_StAction_TestCase_4
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Test CddTpsGen2_StAction function when ucAction
///         is CDDTPSGEN2_ST_ACT_SYSCFG and CDDTPSGEN2_Para_BAUDRATE is CDDTPSGEN2_BAUDRATE_1Mbps
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input boRestart_out                                 = TRUE;
/// \input CDDTPSGEN2_Para_COUNT_CONNECTED_DEV           = 3u;
/// \input CDDTPSGEN2_Para_CHIP_EEPROM_ADDR              = 0xBB;
/// \input CDDTPSGEN2_Para_CHIP_IDX(0u)                  = 0u;
/// \input CDDTPSGEN2_Para_CHIP_IDX(1u)                  = 1u;
/// \input CDDTPSGEN2_Para_CHIP_IDX(2u)                  = 2u;
/// \input CDDTPSGEN2_Para_BAUDRATE                      = CDDTPSGEN2_BAUDRATE_1Mbps;
/// \input CDDTPSGEN2_Para_CHIP_ADDR(0u).boIsMasterId    = FALSE;
/// \input CDDTPSGEN2_Para_CHIP_ADDR(1u).boIsMasterId    = TRUE;
/// \input CDDTPSGEN2_Para_CHIP_ADDR(2u).boIsMasterId    = TRUE;
/// \input CDDTPSGEN2_Para_CHIP_ADDR(0u).ucPhysicalAddr  = 0xBE;
/// \input CDDTPSGEN2_Para_CHIP_ADDR(1u).ucPhysicalAddr  = 0xBA;
/// \input CDDTPSGEN2_Para_CHIP_ADDR(2u).ucPhysicalAddr  = 0xBB;
/// 
///    - Expected test results: 
/// \output boRestart_out = FALSE
///           #if (CDDTPSGEN2_SYNC_TYPE == CDDTPSGEN2_SYNC_HW_MASTER_SLAVE)
/// \output     AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[0u].sSysReg.RegSYSCFG.Bit.biSYNCOEN,          0u                                           , == );
/// \output     AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[0u].sSysReg.RegSYSCFG.Bit.biSYNCOEN,          0u                                           , == );
/// \output     AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[1u].sSysReg.RegSYSCFG.Bit.biSYNCOEN,          1u                                           , == );
/// \output     AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[1u].sSysReg.RegSYSCFG.Bit.biSYNCOEN,          1u                                           , == );
/// \output     AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[2u].sSysReg.RegSYSCFG.Bit.biSYNCOEN,          1u                                           , == );
/// \output     AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[2u].sSysReg.RegSYSCFG.Bit.biSYNCOEN,          1u                                           , == );
///           #endif
///           
///           #if (CDDTPSGEN2_I2C_ENABLED == CDDTPSGEN2_FEATURE_ON) 
/// \output     AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[0u].sSysReg.RegSYSCFG.Bit.biI2CEN,          0u                                             , == );
/// \output     AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[1u].sSysReg.RegSYSCFG.Bit.biI2CEN,          0u                                             , == );
/// \output     AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[2u].sSysReg.RegSYSCFG.Bit.biI2CEN,          1u                                             , == );
/// \output     AL_UNITTEST_CHECK(CddTpsGen2_DataMirrorEE.CtrlTx.TxI2CTICK.Bit.biI2CTICK,                            CDDTPSGEN2_CFG_I2CTICK_16MHz                   , == );
/// \output     AL_UNITTEST_CHECK(CddTpsGen2_ucChipIdx_EE,                                                           2u                                             , == );
///           #endif
/// \output     AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[0].sSysReg.RegCMWTAP.Bit.biCMWTAP,          CDDTPSGEN2_CFG_CMWTAP_16MHz                    , == );
/// \output     AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[0].sSysReg.RegPWMTICK.Bit.biPTCNT,          CDDTPSGEN2_CFG_PWMTICK_16MHz                   , == );
/// \output     AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[0].sSysReg.RegPWMTICK.Bit.biPTBASE,         0u                                             , == );
/// \output     AL_UNITTEST_CHECK(boRestart_out,                                                                     FALSE                                          , == );
///
///-----------------------------------------------------------------------------
void Mt_CddTpsGen2_StAction_TestCase_4(void)
{
  boolean boRestart_out;
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  boRestart_out                                 = TRUE;
  CDDTPSGEN2_Para_COUNT_CONNECTED_DEV           = 3u;
  CDDTPSGEN2_Para_CHIP_EEPROM_ADDR              = 0xBB;
  CDDTPSGEN2_Para_CHIP_IDX(0u)                  = 0u;
  CDDTPSGEN2_Para_CHIP_IDX(1u)                  = 1u;
  CDDTPSGEN2_Para_CHIP_IDX(2u)                  = 2u;
  CDDTPSGEN2_Para_BAUDRATE                      = CDDTPSGEN2_BAUDRATE_1Mbps;
  CDDTPSGEN2_Para_CHIP_ADDR(0u).boIsMasterId    = FALSE;
  CDDTPSGEN2_Para_CHIP_ADDR(1u).boIsMasterId    = TRUE;
  CDDTPSGEN2_Para_CHIP_ADDR(2u).boIsMasterId    = TRUE;
  CDDTPSGEN2_Para_CHIP_ADDR(0u).ucPhysicalAddr  = 0xBE;
  CDDTPSGEN2_Para_CHIP_ADDR(1u).ucPhysicalAddr  = 0xBA;
  CDDTPSGEN2_Para_CHIP_ADDR(2u).ucPhysicalAddr  = 0xBB;

  //Step 3) Call the FUT
  boRestart_out = CddTpsGen2_StAction(CDDTPSGEN2_ST_ACT_SYSCFG);

  //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
#if (CDDTPSGEN2_SYNC_TYPE == CDDTPSGEN2_SYNC_HW_MASTER_SLAVE)
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[0u].sSysReg.RegSYSCFG.Bit.biSYNCOEN,          0u                                           , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[0u].sSysReg.RegSYSCFG.Bit.biSYNCOEN,          0u                                           , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[1u].sSysReg.RegSYSCFG.Bit.biSYNCOEN,          1u                                           , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[1u].sSysReg.RegSYSCFG.Bit.biSYNCOEN,          1u                                           , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[2u].sSysReg.RegSYSCFG.Bit.biSYNCOEN,          1u                                           , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[2u].sSysReg.RegSYSCFG.Bit.biSYNCOEN,          1u                                           , == );
#endif

#if (CDDTPSGEN2_I2C_ENABLED == CDDTPSGEN2_FEATURE_ON) 
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[0u].sSysReg.RegSYSCFG.Bit.biI2CEN,          0u                                             , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[1u].sSysReg.RegSYSCFG.Bit.biI2CEN,          0u                                             , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[2u].sSysReg.RegSYSCFG.Bit.biI2CEN,          1u                                             , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirrorEE.CtrlTx.TxI2CTICK.Bit.biI2CTICK,                            CDDTPSGEN2_CFG_I2CTICK_16MHz                   , == );
  AL_UNITTEST_CHECK(CddTpsGen2_ucChipIdx_EE,                                                           2u                                             , == );
#endif
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[0].sSysReg.RegCMWTAP.Bit.biCMWTAP,          CDDTPSGEN2_CFG_CMWTAP_16MHz                    , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[0].sSysReg.RegPWMTICK.Bit.biPTCNT,          CDDTPSGEN2_CFG_PWMTICK_16MHz                   , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[0].sSysReg.RegPWMTICK.Bit.biPTBASE,         0u                                             , == );
  AL_UNITTEST_CHECK(boRestart_out,                                                                     FALSE                                          , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_StAction_TestCase_5
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Test CddTpsGen2_StAction function when ucAction
///         is CDDTPSGEN2_ST_ACT_SYSCFG and CDDTPSGEN2_Para_BAUDRATE is CDDTPSGEN2_BAUDRATE_500Kbps
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input boRestart_out                                 = TRUE;
/// \input CDDTPSGEN2_Para_COUNT_CONNECTED_DEV           = 3u;
/// \input CDDTPSGEN2_Para_CHIP_EEPROM_ADDR              = 0xBB;
/// \input CDDTPSGEN2_Para_CHIP_IDX(0u)                  = 0u;
/// \input CDDTPSGEN2_Para_CHIP_IDX(1u)                  = 1u;
/// \input CDDTPSGEN2_Para_CHIP_IDX(2u)                  = 2u;
/// \input CDDTPSGEN2_Para_BAUDRATE                      = CDDTPSGEN2_BAUDRATE_500Kbps;
/// \input CDDTPSGEN2_Para_CHIP_ADDR(0u).boIsMasterId    = FALSE;
/// \input CDDTPSGEN2_Para_CHIP_ADDR(1u).boIsMasterId    = TRUE;
/// \input CDDTPSGEN2_Para_CHIP_ADDR(2u).boIsMasterId    = TRUE;
/// \input CDDTPSGEN2_Para_CHIP_ADDR(0u).ucPhysicalAddr  = 0xBE;
/// \input CDDTPSGEN2_Para_CHIP_ADDR(1u).ucPhysicalAddr  = 0xBA;
/// \input CDDTPSGEN2_Para_CHIP_ADDR(2u).ucPhysicalAddr  = 0xBB;
/// 
///    - Expected test results: 
/// \output boRestart_out = FALSE
///           #if (CDDTPSGEN2_SYNC_TYPE == CDDTPSGEN2_SYNC_HW_MASTER_SLAVE)
/// \output     AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[0u].sSysReg.RegSYSCFG.Bit.biSYNCOEN,          0u                                           , == );
/// \output     AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[0u].sSysReg.RegSYSCFG.Bit.biSYNCOEN,          0u                                           , == );
/// \output     AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[1u].sSysReg.RegSYSCFG.Bit.biSYNCOEN,          1u                                           , == );
/// \output     AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[1u].sSysReg.RegSYSCFG.Bit.biSYNCOEN,          1u                                           , == );
/// \output     AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[2u].sSysReg.RegSYSCFG.Bit.biSYNCOEN,          1u                                           , == );
/// \output     AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[2u].sSysReg.RegSYSCFG.Bit.biSYNCOEN,          1u                                           , == );
///           #endif
///           
///           #if (CDDTPSGEN2_I2C_ENABLED == CDDTPSGEN2_FEATURE_ON) 
/// \output     AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[0u].sSysReg.RegSYSCFG.Bit.biI2CEN,          0u                                             , == );
/// \output     AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[1u].sSysReg.RegSYSCFG.Bit.biI2CEN,          0u                                             , == );
/// \output     AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[2u].sSysReg.RegSYSCFG.Bit.biI2CEN,          1u                                             , == );
/// \output     AL_UNITTEST_CHECK(CddTpsGen2_DataMirrorEE.CtrlTx.TxI2CTICK.Bit.biI2CTICK,                            CDDTPSGEN2_CFG_I2CTICK_8MHz                    , == );
/// \output     AL_UNITTEST_CHECK(CddTpsGen2_ucChipIdx_EE,                                                           2u                                             , == );
///           #endif
/// \output     AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[0].sSysReg.RegCMWTAP.Bit.biCMWTAP,          CDDTPSGEN2_CFG_CMWTAP_8MHz                     , == );
/// \output     AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[0].sSysReg.RegPWMTICK.Bit.biPTCNT,          CDDTPSGEN2_CFG_PWMTICK_8MHz                    , == );
/// \output     AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[0].sSysReg.RegPWMTICK.Bit.biPTBASE,         0u                                             , == );
/// \output     AL_UNITTEST_CHECK(boRestart_out,                                                                     FALSE                                          , == );
///
///-----------------------------------------------------------------------------
void Mt_CddTpsGen2_StAction_TestCase_5(void)
{
  boolean boRestart_out;
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  boRestart_out                                 = TRUE;
  CDDTPSGEN2_Para_COUNT_CONNECTED_DEV           = 3u;
  CDDTPSGEN2_Para_CHIP_EEPROM_ADDR              = 0xBB;
  CDDTPSGEN2_Para_CHIP_IDX(0u)                  = 0u;
  CDDTPSGEN2_Para_CHIP_IDX(1u)                  = 1u;
  CDDTPSGEN2_Para_CHIP_IDX(2u)                  = 2u;
  CDDTPSGEN2_Para_BAUDRATE                      = CDDTPSGEN2_BAUDRATE_500Kbps;
  CDDTPSGEN2_Para_CHIP_ADDR(0u).boIsMasterId    = FALSE;
  CDDTPSGEN2_Para_CHIP_ADDR(1u).boIsMasterId    = TRUE;
  CDDTPSGEN2_Para_CHIP_ADDR(2u).boIsMasterId    = TRUE;
  CDDTPSGEN2_Para_CHIP_ADDR(0u).ucPhysicalAddr  = 0xBE;
  CDDTPSGEN2_Para_CHIP_ADDR(1u).ucPhysicalAddr  = 0xBA;
  CDDTPSGEN2_Para_CHIP_ADDR(2u).ucPhysicalAddr  = 0xBB;

  //Step 3) Call the FUT
  boRestart_out = CddTpsGen2_StAction(CDDTPSGEN2_ST_ACT_SYSCFG);

  //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
#if (CDDTPSGEN2_SYNC_TYPE == CDDTPSGEN2_SYNC_HW_MASTER_SLAVE)
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[0u].sSysReg.RegSYSCFG.Bit.biSYNCOEN,          0u                                           , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[0u].sSysReg.RegSYSCFG.Bit.biSYNCOEN,          0u                                           , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[1u].sSysReg.RegSYSCFG.Bit.biSYNCOEN,          1u                                           , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[1u].sSysReg.RegSYSCFG.Bit.biSYNCOEN,          1u                                           , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[2u].sSysReg.RegSYSCFG.Bit.biSYNCOEN,          1u                                           , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[2u].sSysReg.RegSYSCFG.Bit.biSYNCOEN,          1u                                           , == );
#endif

#if (CDDTPSGEN2_I2C_ENABLED == CDDTPSGEN2_FEATURE_ON) 
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[0u].sSysReg.RegSYSCFG.Bit.biI2CEN,          0u                                             , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[1u].sSysReg.RegSYSCFG.Bit.biI2CEN,          0u                                             , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[2u].sSysReg.RegSYSCFG.Bit.biI2CEN,          1u                                             , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirrorEE.CtrlTx.TxI2CTICK.Bit.biI2CTICK,                            CDDTPSGEN2_CFG_I2CTICK_8MHz                    , == );
  AL_UNITTEST_CHECK(CddTpsGen2_ucChipIdx_EE,                                                           2u                                             , == );
#endif
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[0].sSysReg.RegCMWTAP.Bit.biCMWTAP,          CDDTPSGEN2_CFG_CMWTAP_8MHz                     , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[0].sSysReg.RegPWMTICK.Bit.biPTCNT,          CDDTPSGEN2_CFG_PWMTICK_8MHz                    , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[0].sSysReg.RegPWMTICK.Bit.biPTBASE,         0u                                             , == );
  AL_UNITTEST_CHECK(boRestart_out,                                                                     FALSE                                          , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_StAction_TestCase_6
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Test CddTpsGen2_StAction function when ucAction
///         is CDDTPSGEN2_ST_ACT_SYSCFG and CDDTPSGEN2_Para_BAUDRATE is 3u (reach default)
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input boRestart_out                                 = TRUE;
/// \input CDDTPSGEN2_Para_COUNT_CONNECTED_DEV           = 3u;
/// \input CDDTPSGEN2_Para_CHIP_EEPROM_ADDR              = 0xBB;
/// \input CDDTPSGEN2_Para_CHIP_IDX(0u)                  = 0u;
/// \input CDDTPSGEN2_Para_CHIP_IDX(1u)                  = 1u;
/// \input CDDTPSGEN2_Para_CHIP_IDX(2u)                  = 2u;
/// \input CDDTPSGEN2_Para_BAUDRATE                      = 3u;
/// \input CDDTPSGEN2_Para_CHIP_ADDR(0u).boIsMasterId    = FALSE;
/// \input CDDTPSGEN2_Para_CHIP_ADDR(1u).boIsMasterId    = TRUE;
/// \input CDDTPSGEN2_Para_CHIP_ADDR(2u).boIsMasterId    = TRUE;
/// \input CDDTPSGEN2_Para_CHIP_ADDR(0u).ucPhysicalAddr  = 0xBE;
/// \input CDDTPSGEN2_Para_CHIP_ADDR(1u).ucPhysicalAddr  = 0xBA;
/// \input CDDTPSGEN2_Para_CHIP_ADDR(2u).ucPhysicalAddr  = 0xBB;
/// 
///    - Expected test results: 
/// \output boRestart_out = FALSE
///           #if (CDDTPSGEN2_SYNC_TYPE == CDDTPSGEN2_SYNC_HW_MASTER_SLAVE)
/// \output     AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[0u].sSysReg.RegSYSCFG.Bit.biSYNCOEN,          0u                                           , == );
/// \output     AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[0u].sSysReg.RegSYSCFG.Bit.biSYNCOEN,          0u                                           , == );
/// \output     AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[1u].sSysReg.RegSYSCFG.Bit.biSYNCOEN,          1u                                           , == );
/// \output     AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[1u].sSysReg.RegSYSCFG.Bit.biSYNCOEN,          1u                                           , == );
/// \output     AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[2u].sSysReg.RegSYSCFG.Bit.biSYNCOEN,          1u                                           , == );
/// \output     AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[2u].sSysReg.RegSYSCFG.Bit.biSYNCOEN,          1u                                           , == );
///           #endif
///           
///           #if (CDDTPSGEN2_I2C_ENABLED == CDDTPSGEN2_FEATURE_ON) 
/// \output     AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[0u].sSysReg.RegSYSCFG.Bit.biI2CEN,          0u                                             , == );
/// \output     AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[1u].sSysReg.RegSYSCFG.Bit.biI2CEN,          0u                                             , == );
/// \output     AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[2u].sSysReg.RegSYSCFG.Bit.biI2CEN,          1u                                             , == );
/// \output     AL_UNITTEST_CHECK(CddTpsGen2_DataMirrorEE.CtrlTx.TxI2CTICK.Bit.biI2CTICK,                            CDDTPSGEN2_CFG_I2CTICK_8MHz                    , == );
/// \output     AL_UNITTEST_CHECK(CddTpsGen2_ucChipIdx_EE,                                                           2u                                             , == );
///           #endif
/// \output     AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[0].sSysReg.RegCMWTAP.Bit.biCMWTAP,          CDDTPSGEN2_CFG_CMWTAP_8MHz                     , == );
/// \output     AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[0].sSysReg.RegPWMTICK.Bit.biPTCNT,          CDDTPSGEN2_CFG_PWMTICK_8MHz                    , == );
/// \output     AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[0].sSysReg.RegPWMTICK.Bit.biPTBASE,         0u                                             , == );
/// \output     AL_UNITTEST_CHECK(boRestart_out,                                                                     FALSE                                          , == );
///
///-----------------------------------------------------------------------------
void Mt_CddTpsGen2_StAction_TestCase_6(void)
{
  boolean boRestart_out;
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  boRestart_out                                 = TRUE;
  CDDTPSGEN2_Para_COUNT_CONNECTED_DEV           = 3u;
  CDDTPSGEN2_Para_CHIP_EEPROM_ADDR              = 0xBB;
  CDDTPSGEN2_Para_CHIP_IDX(0u)                  = 0u;
  CDDTPSGEN2_Para_CHIP_IDX(1u)                  = 1u;
  CDDTPSGEN2_Para_CHIP_IDX(2u)                  = 2u;
  CDDTPSGEN2_Para_BAUDRATE                      = 3u;
  CDDTPSGEN2_Para_CHIP_ADDR(0u).boIsMasterId    = FALSE;
  CDDTPSGEN2_Para_CHIP_ADDR(1u).boIsMasterId    = TRUE;
  CDDTPSGEN2_Para_CHIP_ADDR(2u).boIsMasterId    = TRUE;
  CDDTPSGEN2_Para_CHIP_ADDR(0u).ucPhysicalAddr  = 0xBE;
  CDDTPSGEN2_Para_CHIP_ADDR(1u).ucPhysicalAddr  = 0xBA;
  CDDTPSGEN2_Para_CHIP_ADDR(2u).ucPhysicalAddr  = 0xBB;

  //Step 3) Call the FUT
  boRestart_out = CddTpsGen2_StAction(CDDTPSGEN2_ST_ACT_SYSCFG);

  //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
#if (CDDTPSGEN2_SYNC_TYPE == CDDTPSGEN2_SYNC_HW_MASTER_SLAVE)
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[0u].sSysReg.RegSYSCFG.Bit.biSYNCOEN,          0u                                           , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[0u].sSysReg.RegSYSCFG.Bit.biSYNCOEN,          0u                                           , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[1u].sSysReg.RegSYSCFG.Bit.biSYNCOEN,          1u                                           , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[1u].sSysReg.RegSYSCFG.Bit.biSYNCOEN,          1u                                           , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[2u].sSysReg.RegSYSCFG.Bit.biSYNCOEN,          1u                                           , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[2u].sSysReg.RegSYSCFG.Bit.biSYNCOEN,          1u                                           , == );
#endif

#if (CDDTPSGEN2_I2C_ENABLED == CDDTPSGEN2_FEATURE_ON) 
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[0u].sSysReg.RegSYSCFG.Bit.biI2CEN,          0u                                             , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[1u].sSysReg.RegSYSCFG.Bit.biI2CEN,          0u                                             , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[2u].sSysReg.RegSYSCFG.Bit.biI2CEN,          1u                                             , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirrorEE.CtrlTx.TxI2CTICK.Bit.biI2CTICK,                            CDDTPSGEN2_CFG_I2CTICK_8MHz                    , == );
  AL_UNITTEST_CHECK(CddTpsGen2_ucChipIdx_EE,                                                           2u                                             , == );
#endif
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[0].sSysReg.RegCMWTAP.Bit.biCMWTAP,          CDDTPSGEN2_CFG_CMWTAP_8MHz                     , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[0].sSysReg.RegPWMTICK.Bit.biPTCNT,          CDDTPSGEN2_CFG_PWMTICK_8MHz                    , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[0].sSysReg.RegPWMTICK.Bit.biPTBASE,         0u                                             , == );
  AL_UNITTEST_CHECK(boRestart_out,                                                                     FALSE                                          , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_StAction_TestCase_7
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Test CddTpsGen2_StAction function when ucAction
///         is CDDTPSGEN2_ST_ACT_SET_PHASE
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input boRestart_out                                 = TRUE;
/// \input CDDTPSGEN2_Para_COUNT_CONNECTED_DEV           = 3u;
/// \input CDDTPSGEN2_Para_CHIP_IDX(0u)                  = 0u;
/// \input CDDTPSGEN2_Para_CHIP_IDX(1u)                  = 1u;
/// \input CDDTPSGEN2_Para_CHIP_IDX(2u)                  = 2u;
/// 
///    - Expected test results: 
/// \output boRestart_out,                                         = FALSE 
/// \output CddTpsGen2_DataMirror.CtrlTx.RegMPHASE[0u].ucByte[0],  = 0x00u 
/// \output CddTpsGen2_DataMirror.CtrlTx.RegMPHASE[0u].ucByte[1],  = 0x55u 
/// \output CddTpsGen2_DataMirror.CtrlTx.RegMPHASE[0u].ucByte[2],  = 0xAAu 
/// \output CddTpsGen2_DataMirror.CtrlTx.RegMPHASE[0u].ucByte[3],  = 0x00u 
/// \output CddTpsGen2_DataMirror.CtrlTx.RegMPHASE[0u].ucByte[4],  = 0xFFu 
/// \output CddTpsGen2_DataMirror.CtrlTx.RegMPHASE[1u].ucByte[0],  = 0x00u 
/// \output CddTpsGen2_DataMirror.CtrlTx.RegMPHASE[1u].ucByte[1],  = 0x55u 
/// \output CddTpsGen2_DataMirror.CtrlTx.RegMPHASE[1u].ucByte[2],  = 0xAAu 
/// \output CddTpsGen2_DataMirror.CtrlTx.RegMPHASE[1u].ucByte[3],  = 0x00u 
/// \output CddTpsGen2_DataMirror.CtrlTx.RegMPHASE[1u].ucByte[4],  = 0xFFu 
/// \output CddTpsGen2_DataMirror.CtrlTx.RegMPHASE[2u].ucByte[0],  = 0x00u 
/// \output CddTpsGen2_DataMirror.CtrlTx.RegMPHASE[2u].ucByte[1],  = 0x55u 
/// \output CddTpsGen2_DataMirror.CtrlTx.RegMPHASE[2u].ucByte[2],  = 0xAAu 
/// \output CddTpsGen2_DataMirror.CtrlTx.RegMPHASE[2u].ucByte[3],  = 0x00u 
/// \output CddTpsGen2_DataMirror.CtrlTx.RegMPHASE[2u].ucByte[4],  = 0xFFu 
///
///-----------------------------------------------------------------------------
void Mt_CddTpsGen2_StAction_TestCase_7(void)
{
  boolean boRestart_out;
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  boRestart_out = TRUE;
  CDDTPSGEN2_Para_COUNT_CONNECTED_DEV = 3u;
  CDDTPSGEN2_Para_CHIP_IDX(0u)        = 0u;
  CDDTPSGEN2_Para_CHIP_IDX(1u)        = 1u;
  CDDTPSGEN2_Para_CHIP_IDX(2u)        = 2u;

  //Step 3) Call the FUT
  boRestart_out = CddTpsGen2_StAction(CDDTPSGEN2_ST_ACT_SET_PHASE);

  //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
  AL_UNITTEST_CHECK(boRestart_out,                                                FALSE         , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegMPHASE[0u].ucByte[0],         0x00u         , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegMPHASE[0u].ucByte[1],         0x55u         , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegMPHASE[0u].ucByte[2],         0xAAu         , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegMPHASE[0u].ucByte[3],         0x00u         , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegMPHASE[0u].ucByte[4],         0xFFu         , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegMPHASE[1u].ucByte[0],         0x00u         , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegMPHASE[1u].ucByte[1],         0x55u         , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegMPHASE[1u].ucByte[2],         0xAAu         , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegMPHASE[1u].ucByte[3],         0x00u         , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegMPHASE[1u].ucByte[4],         0xFFu         , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegMPHASE[2u].ucByte[0],         0x00u         , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegMPHASE[2u].ucByte[1],         0x55u         , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegMPHASE[2u].ucByte[2],         0xAAu         , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegMPHASE[2u].ucByte[3],         0x00u         , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegMPHASE[2u].ucByte[4],         0xFFu         , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_StAction_TestCase_8
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Test CddTpsGen2_StAction function when ucAction
///         is CDDTPSGEN2_ST_ACT_CFG_LEDS
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input boRestart_out                                 = TRUE;
/// \input CDDTPSGEN2_Para_COUNT_CONNECTED_DEV           = 3u;
/// \input CDDTPSGEN2_Para_CHIP_IDX(0u)                  = 0u;
/// \input CDDTPSGEN2_Para_CHIP_IDX(1u)                  = 1u;
/// \input CDDTPSGEN2_Para_CHIP_IDX(2u)                  = 2u;
/// 
///    - Expected test results: 
/// \output boRestart_out,                                                                    = FALSE 
/// \output CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[0u].sStringCfg.uRegSLEWRATE.ucRaw,        = 0xFFu 
/// \output CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[0u].sStringCfg.uRegOVLMT.ucRaw,           = 0xAAu 
/// \output CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[0u].sStringCfg.uRegPARLED.ucRaw,          = 0x00u 
/// \output CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[0u].sStringCfg.uRegDEFWIDTHS.ucByte[0u],  = 0x00u 
/// \output CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[0u].sStringCfg.uRegDEFWIDTHS.ucByte[1u],  = 0x00u 
/// \output CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[0u].sStringCfg.uRegDEFWIDTHS.ucByte[2u],  = 0x00u 
/// \output CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[0u].sStringCfg.uRegDEFWIDTHS.ucByte[3u],  = 0x00u 
/// \output CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[0u].sStringCfg.uRegDEFWIDTHS.ucByte[4u],  = 0x00u 
/// \output CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[0u].sStringCfg.uRegDEFWIDTHS.ucByte[5u],  = 0x00u 
/// \output CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[1u].sStringCfg.uRegSLEWRATE.ucRaw,        = 0xFFu 
/// \output CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[1u].sStringCfg.uRegOVLMT.ucRaw,           = 0xAAu 
/// \output CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[1u].sStringCfg.uRegPARLED.ucRaw,          = 0x00u 
/// \output CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[1u].sStringCfg.uRegDEFWIDTHS.ucByte[0u],  = 0x00u 
/// \output CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[1u].sStringCfg.uRegDEFWIDTHS.ucByte[1u],  = 0x00u 
/// \output CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[1u].sStringCfg.uRegDEFWIDTHS.ucByte[2u],  = 0x00u 
/// \output CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[1u].sStringCfg.uRegDEFWIDTHS.ucByte[3u],  = 0x00u 
/// \output CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[1u].sStringCfg.uRegDEFWIDTHS.ucByte[4u],  = 0x00u 
/// \output CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[1u].sStringCfg.uRegDEFWIDTHS.ucByte[5u],  = 0x00u 
/// \output CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[2u].sStringCfg.uRegSLEWRATE.ucRaw,        = 0xFFu 
/// \output CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[2u].sStringCfg.uRegOVLMT.ucRaw,           = 0xAAu 
/// \output CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[2u].sStringCfg.uRegPARLED.ucRaw,          = 0x00u 
/// \output CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[2u].sStringCfg.uRegDEFWIDTHS.ucByte[0u],  = 0x00u 
/// \output CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[2u].sStringCfg.uRegDEFWIDTHS.ucByte[1u],  = 0x00u 
/// \output CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[2u].sStringCfg.uRegDEFWIDTHS.ucByte[2u],  = 0x00u 
/// \output CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[2u].sStringCfg.uRegDEFWIDTHS.ucByte[3u],  = 0x00u 
/// \output CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[2u].sStringCfg.uRegDEFWIDTHS.ucByte[4u],  = 0x00u 
/// \output CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[2u].sStringCfg.uRegDEFWIDTHS.ucByte[5u],  = 0x00u 
///
///-----------------------------------------------------------------------------
void Mt_CddTpsGen2_StAction_TestCase_8(void)
{
  boolean boRestart_out;
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  boRestart_out                                 = TRUE;
  CDDTPSGEN2_Para_COUNT_CONNECTED_DEV           = 3u;
  CDDTPSGEN2_Para_CHIP_IDX(0u)                  = 0u;
  CDDTPSGEN2_Para_CHIP_IDX(1u)                  = 1u;
  CDDTPSGEN2_Para_CHIP_IDX(2u)                  = 2u;

  //Step 3) Call the FUT
  boRestart_out = CddTpsGen2_StAction(CDDTPSGEN2_ST_ACT_CFG_LEDS);

  //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
  AL_UNITTEST_CHECK(boRestart_out,                                                                     FALSE                  , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[0u].sStringCfg.uRegSLEWRATE.ucRaw,         0x00u                  , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[0u].sStringCfg.uRegOVLMT.ucRaw,            0xAAu                  , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[0u].sStringCfg.uRegPARLED.ucRaw,           0x00u                  , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[0u].sStringCfg.uRegDEFWIDTHS.ucByte[0u],   0x00u                  , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[0u].sStringCfg.uRegDEFWIDTHS.ucByte[1u],   0x00u                  , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[0u].sStringCfg.uRegDEFWIDTHS.ucByte[2u],   0x00u                  , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[0u].sStringCfg.uRegDEFWIDTHS.ucByte[3u],   0x00u                  , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[0u].sStringCfg.uRegDEFWIDTHS.ucByte[4u],   0x00u                  , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[0u].sStringCfg.uRegDEFWIDTHS.ucByte[5u],   0x00u                  , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[1u].sStringCfg.uRegSLEWRATE.ucRaw,         0x00u                  , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[1u].sStringCfg.uRegOVLMT.ucRaw,            0xAAu                  , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[1u].sStringCfg.uRegPARLED.ucRaw,           0x00u                  , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[1u].sStringCfg.uRegDEFWIDTHS.ucByte[0u],   0x00u                  , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[1u].sStringCfg.uRegDEFWIDTHS.ucByte[1u],   0x00u                  , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[1u].sStringCfg.uRegDEFWIDTHS.ucByte[2u],   0x00u                  , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[1u].sStringCfg.uRegDEFWIDTHS.ucByte[3u],   0x00u                  , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[1u].sStringCfg.uRegDEFWIDTHS.ucByte[4u],   0x00u                  , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[1u].sStringCfg.uRegDEFWIDTHS.ucByte[5u],   0x00u                  , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[2u].sStringCfg.uRegSLEWRATE.ucRaw,         0x00u                  , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[2u].sStringCfg.uRegOVLMT.ucRaw,            0xAAu                  , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[2u].sStringCfg.uRegPARLED.ucRaw,           0x00u                  , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[2u].sStringCfg.uRegDEFWIDTHS.ucByte[0u],   0x00u                  , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[2u].sStringCfg.uRegDEFWIDTHS.ucByte[1u],   0x00u                  , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[2u].sStringCfg.uRegDEFWIDTHS.ucByte[2u],   0x00u                  , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[2u].sStringCfg.uRegDEFWIDTHS.ucByte[3u],   0x00u                  , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[2u].sStringCfg.uRegDEFWIDTHS.ucByte[4u],   0x00u                  , == );
  AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[2u].sStringCfg.uRegDEFWIDTHS.ucByte[5u],   0x00u                  , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTpsGen2_StAction
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test CddTpsGen2_StAction function
///
///    - Test Design Technique: DT (Decision Table) and ET (Exploratory Testing)
///
/// \Expected Test Results : All contained test cases are passed
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_StAction(void) {
  Mt_CddTpsGen2_StAction_TestCase_1();
  Mt_CddTpsGen2_StAction_TestCase_2();
  Mt_CddTpsGen2_StAction_TestCase_3();
  Mt_CddTpsGen2_StAction_TestCase_4();
  Mt_CddTpsGen2_StAction_TestCase_5();
  Mt_CddTpsGen2_StAction_TestCase_6();
  Mt_CddTpsGen2_StAction_TestCase_7();
  Mt_CddTpsGen2_StAction_TestCase_8();
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_GetPWRStatus
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Check if CddTpsGen2_GetPWRStatus function returns correct value
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
/// \input uint8 ucRet = 0u;
/// \input CddTpsGen2_ucPowerOnReset_Bit = 1u;
/// 
///    - Expected test results: 
/// \output boRet = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_GetPWRStatus(void)
{
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  uint8 ucRet = 0u;
  CddTpsGen2_ucPowerOnReset_Bit = 1u;

  //Step 3) Call the FUT
  ucRet = CddTpsGen2_GetPWRStatus();

  //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value
  AL_UNITTEST_CHECK(ucRet, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_SchHandleEE
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Check if CddTpsGen2_SchHandleEE doesn't modify CddTpsGen2_ucSchedIx/EE
///         and CddTpsGen2_I2C_State when scNextEntry has CDDTPSGEN2_ST_NO_ACT
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
/// \input CddTpsGen2_ucSchedIx       = 5u;
/// \input CddTpsGen2_ucSchedIxEE     = 5u;
/// \input CddTpsGen2_I2C_State       = CddTpsGen2_I2C_NotInit;
/// \input CddTpsGen2_boInitCompleted = FALSE;
/// 
///    - Expected test results: 
/// \output CddTpsGen2_ucSchedIx     = 5u 
/// \output CddTpsGen2_ucSchedIxEE   = 5u 
/// \output CddTpsGen2_I2C_State     = CddTpsGen2_I2C_NotInit 
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_SchHandleEE(void)
{
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddTpsGen2_ucSchedIx       = 5u;
  CddTpsGen2_ucSchedIxEE     = 5u;
  CddTpsGen2_I2C_State       = CddTpsGen2_I2C_NotInit;
  CddTpsGen2_boInitCompleted = FALSE;

  //Step 3) Call the FUT
  CddTpsGen2_SchHandleEE(&CddTpsGen2_asUartSchedTableEE[14u]);

  //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value
  AL_UNITTEST_CHECK(CddTpsGen2_ucSchedIx       , 5u                             , == );
  AL_UNITTEST_CHECK(CddTpsGen2_ucSchedIxEE     , 5u                             , == );
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_State       , CddTpsGen2_I2C_NotInit         , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_CheckReadCommand
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Check if CddTpsGen2_CheckReadCommand function returns correct value
///
///    - Test Design Technique: DT (Decision Table)
///
///    - Preconditions: 
/// \input  ucSchCmd_in                 
///        { CDDTPSGEN2_READ_01_BYTES  }
///        { CDDTPSGEN2_READ_02_BYTES  }
///        { CDDTPSGEN2_READ_03_BYTES  }
///        { CDDTPSGEN2_READ_04_BYTES  }
///        { CDDTPSGEN2_READ_12_BYTES  }
///        { CDDTPSGEN2_READ_16_BYTES  }
///        { CDDTPSGEN2_READ_32_BYTES  }
///        { 0x22u                     }
/// 
///    - Expected test results: 
/// \output   boRetVal_out
///         { TRUE     } 
///         { TRUE     } 
///         { TRUE     } 
///         { TRUE     } 
///         { TRUE     } 
///         { TRUE     } 
///         { TRUE     } 
///         { FALSE    } 
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_CheckReadCommand(void)
{
  typedef struct tsTestDataIn
  {
    uint8   ucSchCmd_in;
  }tsTestDataIn;
  typedef struct tsTestDataOut
  {
    boolean boRetVal_out;
  }tsTestDataOut;
  typedef struct tsTestData
  {
    tsTestDataIn  sInputData;
    tsTestDataOut sOutputData;
  }tsTestData;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  tsTestData const asTestCaseData[] = {//  ucSchCmd_in                 ,  boRetVal_out
                                  { { CDDTPSGEN2_READ_01_BYTES  },{ TRUE     } },
                                  { { CDDTPSGEN2_READ_02_BYTES  },{ TRUE     } },
                                  { { CDDTPSGEN2_READ_03_BYTES  },{ TRUE     } },
                                  { { CDDTPSGEN2_READ_04_BYTES  },{ TRUE     } },
                                  { { CDDTPSGEN2_READ_12_BYTES  },{ TRUE     } },
                                  { { CDDTPSGEN2_READ_16_BYTES  },{ TRUE     } },
                                  { { CDDTPSGEN2_READ_32_BYTES  },{ TRUE     } },
                                  { { 0x22u                     },{ FALSE    } },
  };

  for (uint8 ucidx = 0u; ucidx < (sizeof(asTestCaseData) / sizeof(tsTestData)); ucidx++)
  {
    boolean boRetVal = FALSE;
    //Step 3) Call the FUT
    boRetVal = CddTpsGen2_CheckReadCommand(asTestCaseData[ucidx].sInputData.ucSchCmd_in);

    //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value
    AL_UNITTEST_CHECK(boRetVal          , asTestCaseData[ucidx].sOutputData.boRetVal_out      , == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_GetELEFAULTReg
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Check if CddTpsGen2_GetELEFAULTReg function doesn't write RxELEFAULT
///         when ucChipIdx is out of range
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
/// \input uint8_fast ucChipId                                           = CDDTPSGEN2_MAX_CHIPs;
/// \input tuCddTpsGen2_RxELEFAULT puELEFAULTReg                         = { 0u };
/// \input CddTpsGen2_DataMirror.StatRx.RxELEFAULT[ucChipId].ucRxByte[0] = 0x11u;
///
///    - Expected test results: 
/// \output puELEFAULTReg.ucRxByte[0] = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_GetELEFAULTReg(void)
{
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  uint8_fast ucChipId                                           = CDDTPSGEN2_MAX_CHIPs;
  tuCddTpsGen2_RxELEFAULT puELEFAULTReg                         = { 0u };
  CddTpsGen2_DataMirror.StatRx.RxELEFAULT[ucChipId].ucRxByte[0] = 0x11u;

  //Step 3) Call the FUT
  CddTpsGen2_GetELEFAULTReg(ucChipId, &puELEFAULTReg);

  //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value
  AL_UNITTEST_CHECK(puELEFAULTReg.ucRxByte[0]         , 0u        , == );
}


//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_GetADCReg
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Check if Mt_CddTpsGen2_GetADCReg function doesn't write RxELEFAULT
///         when ucChipIdx is out of range
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
/// \input uint8_fast ucChipId           = CDDTPSGEN2_MAX_CHIPs;
/// \input tuCddTpsGen2_RxADC puADCReg   = { 0 };
/// \input CddTpsGen2_DataMirror.StatRx.RxADC[ucChipId].ucRxByte[0] = 0x11;
/// 
///    - Expected test results: 
/// \output puADCReg.ucRxByte[0] = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_GetADCReg(void)
{
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  uint8_fast ucChipId           = CDDTPSGEN2_MAX_CHIPs;
  tuCddTpsGen2_RxADC puADCReg   = { 0 };
  CddTpsGen2_DataMirror.StatRx.RxADC[ucChipId].ucRxByte[0] = 0x11;

  //Step 3) Call the FUT
  CddTpsGen2_GetADCReg(ucChipId, &puADCReg);
    
  //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
  AL_UNITTEST_CHECK(puADCReg.ucRxByte[0]    , 0u    , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_ReinitSch
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Check if CddTpsGen2_boReinitChips is updated as requested 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input boCom = FALSE;
/// \input CddTpsGen2_boReinitChips = TRUE
///
///    - Expected test results: 
/// \output CddTpsGen2_boReinitChips = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_ReinitSch(void)
{
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  boolean boCom = FALSE;
  CddTpsGen2_boReinitChips = TRUE;

  //Step 3) Call the FUT
  CddTpsGen2_ReinitSch(boCom);

  //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value
  AL_UNITTEST_CHECK(CddTpsGen2_boReinitChips, FALSE, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_ResetScheduler
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Check if function writes correct value to data mirror
///
///    - Test Design Technique: DT (Decision Table)
///
///    - Preconditions: 
/// \input boTestData[3][3] = {// CddTpsGen2_boInitCompleted   CddTpsGen2_boReinitChips    boRetVal
///                            {FALSE                        , FALSE                     , FALSE   },
///                            {TRUE                         , TRUE                      , TRUE    },
///                            {TRUE                         , FALSE                     , FALSE   },
///
///    - Expected test results: 
/// \output boRet = boTestData[ucIdx][3u]
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_ResetScheduler(void)
{
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  boolean boRet;
  boolean boTestData[3][3] = {// CddTpsGen2_boInitCompleted   CddTpsGen2_boReinitChips    boRetVal
                              {FALSE                        , FALSE                     , FALSE   },
                              {TRUE                         , TRUE                      , TRUE    },
                              {TRUE                         , FALSE                     , FALSE   },
  };

  for (uint8 ucIdx = 0u; ucIdx < 3u; ucIdx++)
  {
    CddTpsGen2_boInitCompleted = boTestData[ucIdx][0u];
    CddTpsGen2_boReinitChips   = boTestData[ucIdx][1u];

    //Step 3) Call the FUT
    boRet = CddTpsGen2_ResetScheduler();

    //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
    AL_UNITTEST_CHECK( boRet,      boTestData[ucIdx][2u],           == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_GetSensorInfo
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Check if function returns the adc values and if the fault is handled correctly
///
///    - Test Design Technique: DT (Decision Table)
///
///    - Preconditions:
/// \input ucChipId - 0 -> 7
/// \input CddTpsGen2_DataMirror.StatRx.RxADC[ucChipId].ucRxByte[0] = asTestData[ucChipId].ucRxByte0_in;
/// \input CddTpsGen2_DataMirror.StatRx.RxADC[ucChipId].ucRxByte[1] = asTestData[ucChipId].ucRxByte1_in;
/// \input CddTpsGen2_aboComStatus[ucChipId]                        = asTestData[ucChipId].boComFault_in;
/// \input CddTpsGen2_boMuxCmdCompleted                             = asTestData[ucChipId].boMuxCmdCompleted_in;
/// \input asTestData[8] = {//  ucRxByte0_in   ucRxByte1_in   boComFault_in   boMuxCmdCompleted_in   ucADC1Value_out   ucADC2Value_out   eQlty_out
///                          {  0xE2u        , 0x2Eu        , FALSE         , FALSE                , 0xE2u           , 0x2Eu            , SENSOR_QLTY_SNA     },
///                          {  0xA1u        , 0x1Au        , FALSE         , TRUE                 , 0xA1u           , 0x1Au            , SENSOR_QLTY_VALID   },
///                          {  0x21u        , 0x16u        , TRUE          , TRUE                 , 0x21u           , 0x16u            , SENSOR_QLTY_INVALID },
///                          {  0x31u        , 0x14u        , TRUE          , FALSE                , 0x31u           , 0x14u            , SENSOR_QLTY_INVALID },
///                          {  0x51u        , 0x12u        , FALSE         , TRUE                 , 0x51u           , 0x12u            , SENSOR_QLTY_VALID   },
///                          {  0x71u        , 0x15u        , FALSE         , TRUE                 , 0x71u           , 0x15u            , SENSOR_QLTY_VALID   },
///                          {  0x91u        , 0x17u        , FALSE         , TRUE                 , 0x91u           , 0x17u            , SENSOR_QLTY_VALID   },
///                          {  0xA1u        , 0x1Au        , FALSE         , TRUE                 , 0x0u            , 0x0u             , SENSOR_QLTY_INVALID },// out of range
///
///
///    - Expected test results: 
/// \output psSensorData.eQlty         = asTestData[ucChipId].eQlty_out      
/// \output psSensorData.ucADC1Value   = asTestData[ucChipId].ucADC1Value_out
/// \output psSensorData.ucADC2Value   = asTestData[ucChipId].ucADC2Value_out
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_GetSensorInfo(void)
{
  typedef struct tsTestData
  {
    uint8               ucRxByte0_in;
    uint8               ucRxByte1_in;
    boolean             boComFault_in;
    boolean             boMuxCmdCompleted_in;
    uint8               ucADC1Value_out;
    uint8               ucADC2Value_out;
    teCddMlc_SigQuality eQlty_out;
  }tsTestData;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  tsTestData asTestData[8] = {//  ucRxByte0_in   ucRxByte1_in   boComFault_in   boMuxCmdCompleted_in   ucADC1Value_out   ucADC2Value_out   eQlty_out
                               {  0xE2u        , 0x2Eu        , FALSE         , FALSE                , 0xE2u           , 0x2Eu            , SENSOR_QLTY_SNA     },
                               {  0xA1u        , 0x1Au        , FALSE         , TRUE                 , 0xA1u           , 0x1Au            , SENSOR_QLTY_VALID   },
                               {  0x21u        , 0x16u        , TRUE          , TRUE                 , 0x21u           , 0x16u            , SENSOR_QLTY_INVALID },
                               {  0x31u        , 0x14u        , TRUE          , FALSE                , 0x31u           , 0x14u            , SENSOR_QLTY_INVALID },
                               {  0x51u        , 0x12u        , FALSE         , TRUE                 , 0x51u           , 0x12u            , SENSOR_QLTY_VALID   },
                               {  0x71u        , 0x15u        , FALSE         , TRUE                 , 0x71u           , 0x15u            , SENSOR_QLTY_VALID   },
                               {  0x91u        , 0x17u        , FALSE         , TRUE                 , 0x91u           , 0x17u            , SENSOR_QLTY_VALID   },
                               {  0xA1u        , 0x1Au        , FALSE         , TRUE                 , 0x0u            , 0x0u             , SENSOR_QLTY_INVALID },// out of range
  };

  for (uint8 ucChipId = 0u; ucChipId < 8u; ucChipId++)
  {
    tsCddMlc_SensorData psSensorData = { 0 };
    CddTpsGen2_DataMirror.StatRx.RxADC[ucChipId].ucRxByte[0] = asTestData[ucChipId].ucRxByte0_in;
    CddTpsGen2_DataMirror.StatRx.RxADC[ucChipId].ucRxByte[1] = asTestData[ucChipId].ucRxByte1_in;
    CddTpsGen2_aboComStatus[ucChipId]                        = asTestData[ucChipId].boComFault_in;
    CddTpsGen2_boMuxCmdCompleted                             = asTestData[ucChipId].boMuxCmdCompleted_in;

    //Step 3) Call the FUT
    CddTpsGen2_GetSensorInfo(ucChipId, &psSensorData);

    //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value
    AL_UNITTEST_CHECK(psSensorData.eQlty                , asTestData[ucChipId].eQlty_out              , == );
    AL_UNITTEST_CHECK(psSensorData.ucADC1Value          , asTestData[ucChipId].ucADC1Value_out        , == );
    AL_UNITTEST_CHECK(psSensorData.ucADC2Value          , asTestData[ucChipId].ucADC2Value_out        , == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_GetComFault_TestCase1
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Check if communication fault is returned correctly
///         when ucChipId is in range
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input ucChipId = 1u;
/// \input boRet = FALSE;
/// \input CddTpsGen2_aboComStatus[ucChipId] = TRUE;
///
///    - Expected test results: 
/// \output boRet == TRUE
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_GetComFault_TestCase1(void)
{
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  uint8_fast ucChipId = 1u;
  boolean boRet       = FALSE;
  CddTpsGen2_aboComStatus[ucChipId] = TRUE;

  //Step 3) Call the FUT
  boRet = CddTpsGen2_GetComFault(ucChipId);

  //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
  AL_UNITTEST_CHECK(boRet, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_GetComFault_TestCase2
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Check if communication fault is returned correctly
///          when ucChipId is out of range
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input ucChipId = 10u;
/// \input boRet = TRUE;
/// \input CddTpsGen2_aboComStatus[ucChipId] = TRUE;
///
///    - Expected test results: 
/// \output boRet == FALSE
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_GetComFault_TestCase2(void)
{
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  uint8_fast ucChipId = 10u;
  boolean boRet       = TRUE;
  CddTpsGen2_aboComStatus[ucChipId] = TRUE;

  //Step 3) Call the FUT
  boRet = CddTpsGen2_GetComFault(ucChipId);

  //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
  AL_UNITTEST_CHECK(boRet, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTpsGen2_GetComFault
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test Mt_CddTpsGen2_GetComFault function
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected Test Results : All contained test cases are passed
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_GetComFault(void)
{
  Mt_CddTpsGen2_GetComFault_TestCase1();
  Mt_CddTpsGen2_GetComFault_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_GetCrcFault
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Check if CRC fault is returned correctly
///
///    - Test Design Technique: DT (Decision Table)
///
///    - Preconditions:
/// \input   ucChipIdx_in         , boComStatus_in   
///          {0u                   , FALSE           }
///          {1u                   , TRUE            }
///          {CDDTPSGEN2_MAX_CHIPs , TRUE            }
///         
///
///    - Expected test results: 
/// \output   boCrcFault_out
///         { FALSE         }
///         { TRUE          }
///         { FALSE         }
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_GetCrcFault(void)
{
  typedef struct tsTestDataIn
  {
    uint8   ucChipIdx_in;
    boolean boComStatus_in;
  }tsTestDataIn;

  typedef struct tsTestDataOut
  {
    boolean boCrcFault_out;
  }tsTestDataOut;

  typedef struct tsTestData
  {
    tsTestDataIn  sInputData;
    tsTestDataOut sOutputData;
  }tsTestData;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  tsTestData const asTestCaseData[] = {//  ucChipIdx_in         , boComStatus_in   ,  boCrcFault_out
                                  { {0u                   , FALSE           },{ FALSE         } },
                                  { {1u                   , TRUE            },{ TRUE          } },
                                  { {CDDTPSGEN2_MAX_CHIPs , TRUE            },{ FALSE         } },
  };

  for(uint8 ucidx = 0u; ucidx < (sizeof(asTestCaseData) / sizeof(tsTestData)); ucidx++)
  {
    boolean boRet                     = FALSE;
    uint8   ucChipId                  = asTestCaseData[ucidx].sInputData.ucChipIdx_in;
    CddTpsGen2_aboCrcStatus[ucChipId] = asTestCaseData[ucidx].sInputData.boComStatus_in;

    //Step 3) Call the FUT
    boRet = CddTpsGen2_GetCrcFault(ucChipId);

    //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
    AL_UNITTEST_CHECK(boRet       , asTestCaseData[ucidx].sOutputData.boCrcFault_out      , == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_GetInitStatus
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Check if init completed is returned correctly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input   boolean boRet              = FALSE;
/// \input   CddTpsGen2_boInitCompleted = TRUE;
///
///    - Expected test results: 
/// \output   boRet == TRUE
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_GetInitStatus(void)
{

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  boolean boRet              = FALSE;
  CddTpsGen2_boInitCompleted = TRUE;

  //Step 3) Call the FUT
  boRet = CddTpsGen2_GetInitStatus();

  //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
  AL_UNITTEST_CHECK(boRet       , TRUE      , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_I2C_StartInit
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Check I2C state machine initialization
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input   pfnInitSuccessClbk_in = TestExt_ActionSuccessClbk;
/// \input   pfnInitFailedClbk_in  = TestExt_ActionFailedClbk;
/// \input   *peRet = NULL_PTR;
///
///    - Expected test results: 
/// \output   CddTpsGen2_I2C_pfnInitSuccessClbk   = &TestExt_ActionSuccessClbk 
/// \output   CddTpsGen2_I2C_pfnInitFailedClbk    = &TestExt_ActionFailedClbk  
/// \output   CddTpsGen2_I2C_ucInitTimeoutCounter = 0u                                
/// \output   CddTpsGen2_I2C_State                = CddTpsGen2_I2C_Preinit            
/// \output   CddTpsGen2_I2C_InitStatus           = CddTpsGen2_I2C_Pending            
/// \output   peRet                               = &CddTpsGen2_I2C_InitStatus        
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_I2C_StartInit(void)
{

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  tCddTpsGen2_I2C_pFnct   pfnInitSuccessClbk_in = TestExt_ActionSuccessClbk;
  tCddTpsGen2_I2C_pFnct   pfnInitFailedClbk_in  = TestExt_ActionFailedClbk;
  tCddTpsGen2_I2C_eStatus * peRet = NULL_PTR;

  //Step 3) Call the FUT
  peRet = CddTpsGen2_I2C_StartInit(pfnInitSuccessClbk_in, pfnInitFailedClbk_in);

  //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_pfnInitSuccessClbk   , &TestExt_ActionSuccessClbk   , == );
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_pfnInitFailedClbk    , &TestExt_ActionFailedClbk    , == );
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_ucInitTimeoutCounter , 0u                                    , == );
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_State                , CddTpsGen2_I2C_Preinit                , == );
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_InitStatus           , CddTpsGen2_I2C_Pending                , == );
  AL_UNITTEST_CHECK(peRet                               , &CddTpsGen2_I2C_InitStatus            , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_I2C_ReadEeprom_TestCase1
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Check I2C read eeprom function when all the checks are OK
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input   uint8 aucData_List[10];
/// \input   uint16 unStartAddress = 0x16u;
/// \input   uint16 unLength = 10u;
/// \input   tCddTpsGen2_I2C_pFnct   pfnReadSuccessClbk = TestExt_ActionSuccessClbk;
/// \input   tCddTpsGen2_I2C_pFnct   pfnReadFailedClbk  = TestExt_ActionFailedClbk;
/// \input   tCddTpsGen2_I2C_eStatus *peRet = NULL_PTR;
/// \input   CddTpsGen2_I2C_State = CddTpsGen2_I2C_Idle;
/// \input   TestExt_ActionSuccessClbk_HitCount = 0u;
/// \input   TestExt_ActionFailedClbk_HitCount  = 0u;
///
///    - Expected test results: 
/// \output  CddTpsGen2_I2C_ucPtrReadData                    = aucData_List                        
/// \output  CddTpsGen2_I2C_unReadStartAddress               = 0x16u                               
/// \output  CddTpsGen2_I2C_unReadEndAddress                 = 0x20u                               
/// \output  CddTpsGen2_I2C_ucReadTimeoutCounter             = 0                                   
/// \output  CddTpsGen2_I2C_State                            = CddTpsGen2_I2C_Read_Start           
/// \output  CddTpsGen2_I2C_ReadStatus                       = CddTpsGen2_I2C_Pending              
/// \output  peRet                                           = &CddTpsGen2_I2C_ReadStatus          
/// \output  CddTpsGen2_I2C_pfnReadSuccessClbk               = &TestExt_ActionSuccessClbk   
/// \output  CddTpsGen2_I2C_pfnReadFailedClbk                = &TestExt_ActionFailedClbk    
/// \output  TestExt_ActionSuccessClbk_HitCount     = 0u                                  
/// \output  TestExt_ActionFailedClbk_HitCount      = 0u                                  
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_I2C_ReadEeprom_TestCase1(void)
{
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  uint8 aucData_List[10];
  uint16 unStartAddress = 0x16u;
  uint16 unLength       = 10u;
  tCddTpsGen2_I2C_pFnct   pfnReadSuccessClbk = TestExt_ActionSuccessClbk;
  tCddTpsGen2_I2C_pFnct   pfnReadFailedClbk  = TestExt_ActionFailedClbk;
  tCddTpsGen2_I2C_eStatus *peRet = NULL_PTR;

  CddTpsGen2_I2C_State = CddTpsGen2_I2C_Idle;
  TestExt_ActionSuccessClbk_HitCount = 0u;
  TestExt_ActionFailedClbk_HitCount  = 0u;

  //Step 3) Call the FUT
  peRet = CddTpsGen2_I2C_ReadEeprom(aucData_List, unStartAddress, unLength, pfnReadSuccessClbk, pfnReadFailedClbk);

  //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_ucPtrReadData                    , aucData_List                          , == );
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_unReadStartAddress               , 0x16u                                 , == );
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_unReadEndAddress                 , 0x20u                                 , == );
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_ucReadTimeoutCounter             , 0                                     , == );
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_State                            , CddTpsGen2_I2C_Read_Start             , == );
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_ReadStatus                       , CddTpsGen2_I2C_Pending                , == );
  AL_UNITTEST_CHECK(peRet                                           , &CddTpsGen2_I2C_ReadStatus            , == );
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_pfnReadSuccessClbk               , &TestExt_ActionSuccessClbk   , == );
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_pfnReadFailedClbk                , &TestExt_ActionFailedClbk    , == );
  AL_UNITTEST_CHECK(TestExt_ActionSuccessClbk_HitCount     , 0u                                    , == );
  AL_UNITTEST_CHECK(TestExt_ActionFailedClbk_HitCount      , 0u                                    , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_I2C_ReadEeprom_TestCase2
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Check I2C read eeprom function when CddTpsGen2_I2C_State is CddTpsGen2_I2C_Read_Start
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input   uint8 aucData_List[10];
/// \input   uint16 unStartAddress = 0x16u;
/// \input   uint16 unLength       = 10u;
/// \input   tCddTpsGen2_I2C_pFnct   pfnReadSuccessClbk = TestExt_ActionSuccessClbk;
/// \input   tCddTpsGen2_I2C_pFnct   pfnReadFailedClbk  = TestExt_ActionFailedClbk;
/// \input   tCddTpsGen2_I2C_eStatus *peRet = NULL_PTR;
/// \input   CddTpsGen2_I2C_State = CddTpsGen2_I2C_Read_Start;
/// \input   TestExt_ActionSuccessClbk_HitCount = 0u;
/// \input   TestExt_ActionFailedClbk_HitCount  = 0u;
/// \input   CddTpsGen2_I2C_ucPtrReadData      = aucData_List;
/// \input   CddTpsGen2_I2C_unReadStartAddress = 0x00u;
/// \input   CddTpsGen2_I2C_pfnReadFailedClbk  = NULL_PTR;
/// \input   CddTpsGen2_I2C_pfnReadSuccessClbk = NULL_PTR;
/// \input   CddTpsGen2_I2C_ReadStatus         = CddTpsGen2_I2C_Pending;
///
///    - Expected test results: 
/// \output  CddTpsGen2_I2C_unReadStartAddress               , 0x00u                           
/// \output  CddTpsGen2_I2C_ucReadTimeoutCounter             , 0                               
/// \output  CddTpsGen2_I2C_State                            , CddTpsGen2_I2C_Read_Start       
/// \output  CddTpsGen2_I2C_ReadStatus                       , CddTpsGen2_I2C_Rejected         
/// \output  peRet                                           , &CddTpsGen2_I2C_ReadStatus      
/// \output  CddTpsGen2_I2C_pfnReadSuccessClbk               , NULL_PTR                        
/// \output  CddTpsGen2_I2C_pfnReadFailedClbk                , &TestExt_ActionFailedClbk
/// \output  TestExt_ActionSuccessClbk_HitCount     , 0u                              
/// \output  TestExt_ActionFailedClbk_HitCount      , 1u                              
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_I2C_ReadEeprom_TestCase2(void)
{
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  uint8 aucData_List[10];
  uint16 unStartAddress = 0x16u;
  uint16 unLength       = 10u;
  tCddTpsGen2_I2C_pFnct   pfnReadSuccessClbk = TestExt_ActionSuccessClbk;
  tCddTpsGen2_I2C_pFnct   pfnReadFailedClbk  = TestExt_ActionFailedClbk;
  tCddTpsGen2_I2C_eStatus *peRet = NULL_PTR;

  CddTpsGen2_I2C_State = CddTpsGen2_I2C_Read_Start;
  TestExt_ActionSuccessClbk_HitCount = 0u;
  TestExt_ActionFailedClbk_HitCount  = 0u;
  CddTpsGen2_I2C_ucPtrReadData      = aucData_List;
  CddTpsGen2_I2C_unReadStartAddress = 0x00u;
  CddTpsGen2_I2C_pfnReadFailedClbk  = NULL_PTR;
  CddTpsGen2_I2C_pfnReadSuccessClbk = NULL_PTR;
  CddTpsGen2_I2C_ReadStatus         = CddTpsGen2_I2C_Pending;

  //Step 3) Call the FUT
  peRet = CddTpsGen2_I2C_ReadEeprom(aucData_List, unStartAddress, unLength, pfnReadSuccessClbk, pfnReadFailedClbk);

  //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_unReadStartAddress               , 0x00u                                 , == );
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_ucReadTimeoutCounter             , 0                                     , == );
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_State                            , CddTpsGen2_I2C_Read_Start             , == );
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_ReadStatus                       , CddTpsGen2_I2C_Rejected               , == );
  AL_UNITTEST_CHECK(peRet                                           , &CddTpsGen2_I2C_ReadStatus            , == );
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_pfnReadSuccessClbk               , NULL_PTR                              , == );
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_pfnReadFailedClbk                , &TestExt_ActionFailedClbk    , == );
  AL_UNITTEST_CHECK(TestExt_ActionSuccessClbk_HitCount     , 0u                                    , == );
  AL_UNITTEST_CHECK(TestExt_ActionFailedClbk_HitCount      , 1u                                    , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_I2C_ReadEeprom_TestCase3
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Check I2C read eeprom function when ucData_List and pfnReadFailedClbk are NULL_PTR
///         and 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input   uint16 unStartAddress = 0x16u;
/// \input   uint16 unLength       = 10u;
/// \input   tCddTpsGen2_I2C_pFnct   pfnReadSuccessClbk = TestExt_ActionSuccessClbk;
/// \input   tCddTpsGen2_I2C_pFnct   pfnReadFailedClbk  = NULL_PTR;
/// \input   tCddTpsGen2_I2C_eStatus *peRet = NULL_PTR;
/// \input   CddTpsGen2_I2C_State = CddTpsGen2_I2C_Idle;
/// \input   TestExt_ActionSuccessClbk_HitCount = 0u;
/// \input   TestExt_ActionFailedClbk_HitCount  = 0u;
/// \input   CddTpsGen2_I2C_ucPtrReadData      = NULL_PTR;
/// \input   CddTpsGen2_I2C_unReadStartAddress = 0x00u;
/// \input   CddTpsGen2_I2C_pfnReadFailedClbk  = NULL_PTR;
/// \input   CddTpsGen2_I2C_pfnReadSuccessClbk = NULL_PTR;
/// \input   CddTpsGen2_I2C_ReadStatus         = CddTpsGen2_I2C_Pending;
///
///    - Expected test results: 
/// \output  CddTpsGen2_I2C_unReadStartAddress               = 0x00u                           
/// \output  CddTpsGen2_I2C_ucReadTimeoutCounter             = 0                               
/// \output  CddTpsGen2_I2C_State                            = CddTpsGen2_I2C_Idle             
/// \output  CddTpsGen2_I2C_ReadStatus                       = CddTpsGen2_I2C_Rejected         
/// \output  peRet                                           = &CddTpsGen2_I2C_ReadStatus      
/// \output  CddTpsGen2_I2C_pfnReadSuccessClbk               = NULL_PTR                        
/// \output  CddTpsGen2_I2C_pfnReadFailedClbk                = NULL_PTR
/// \output  TestExt_ActionSuccessClbk_HitCount     = 0u                              
/// \output  TestExt_ActionFailedClbk_HitCount      = 0u                              
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_I2C_ReadEeprom_TestCase3(void)
{
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  uint16 unStartAddress = 0x16u;
  uint16 unLength       = 10u;
  tCddTpsGen2_I2C_pFnct   pfnReadSuccessClbk = TestExt_ActionSuccessClbk;
  tCddTpsGen2_I2C_pFnct   pfnReadFailedClbk  = NULL_PTR;
  tCddTpsGen2_I2C_eStatus *peRet = NULL_PTR;

  CddTpsGen2_I2C_State = CddTpsGen2_I2C_Idle;
  TestExt_ActionSuccessClbk_HitCount = 0u;
  TestExt_ActionFailedClbk_HitCount  = 0u;
  CddTpsGen2_I2C_ucPtrReadData      = NULL_PTR;
  CddTpsGen2_I2C_unReadStartAddress = 0x00u;
  CddTpsGen2_I2C_pfnReadFailedClbk  = NULL_PTR;
  CddTpsGen2_I2C_pfnReadSuccessClbk = NULL_PTR;
  CddTpsGen2_I2C_ReadStatus         = CddTpsGen2_I2C_Pending;

  //Step 3) Call the FUT
  peRet = CddTpsGen2_I2C_ReadEeprom(NULL_PTR, unStartAddress, unLength, pfnReadSuccessClbk, pfnReadFailedClbk);

  //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_unReadStartAddress               , 0x00u                               , == );
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_ucReadTimeoutCounter             , 0                                   , == );
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_State                            , CddTpsGen2_I2C_Idle                 , == );
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_ReadStatus                       , CddTpsGen2_I2C_Rejected             , == );
  AL_UNITTEST_CHECK(peRet                                           , &CddTpsGen2_I2C_ReadStatus          , == );
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_pfnReadSuccessClbk               , NULL_PTR                            , == );
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_pfnReadFailedClbk                , NULL_PTR                            , == );
  AL_UNITTEST_CHECK(TestExt_ActionSuccessClbk_HitCount     , 0u                                  , == );
  AL_UNITTEST_CHECK(TestExt_ActionFailedClbk_HitCount      , 0u                                  , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTpsGen2_I2C_ReadEeprom
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test Mt_CddTpsGen2_I2C_ReadEeprom function
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected Test Results : All contained test cases are passed
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_I2C_ReadEeprom(void)
{
  Mt_CddTpsGen2_I2C_ReadEeprom_TestCase1();
  Mt_CddTpsGen2_I2C_ReadEeprom_TestCase2();
  Mt_CddTpsGen2_I2C_ReadEeprom_TestCase3();
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_I2C_WriteEeprom_TestCase1
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Check I2C write eeprom function when all the checks are OK
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input   uint8 aucData_List[10];
/// \input   uint16 unStartAddress = 0x16u;
/// \input   uint16 unLength       = 10u;
/// \input   tCddTpsGen2_I2C_pFnct   pfnReadSuccessClbk = TestExt_ActionSuccessClbk;
/// \input   tCddTpsGen2_I2C_pFnct   pfnReadFailedClbk  = TestExt_ActionFailedClbk;
/// \input   tCddTpsGen2_I2C_eStatus *peRet = NULL_PTR;
/// \input   CddTpsGen2_I2C_State = CddTpsGen2_I2C_Idle;
/// \input   TestExt_ActionSuccessClbk_HitCount = 0u;
/// \input   TestExt_ActionFailedClbk_HitCount  = 0u;
///
///    - Expected test results: 
/// \output  CddTpsGen2_I2C_ucPtrWriteData                   = aucData_List                       
/// \output  CddTpsGen2_I2C_unWriteStartAddress              = 0x16u                              
/// \output  CddTpsGen2_I2C_unWriteEndAddress                = 0x20u                              
/// \output  CddTpsGen2_I2C_ucWriteTimeoutCounter            = 0                                  
/// \output  CddTpsGen2_I2C_State                            = CddTpsGen2_I2C_Write_Data          
/// \output  CddTpsGen2_I2C_WriteStatus                      = CddTpsGen2_I2C_Pending             
/// \output  peRet                                           = &CddTpsGen2_I2C_WriteStatus        
/// \output  CddTpsGen2_I2C_pfnWriteSuccessClbk              = &TestExt_ActionSuccessClbk
/// \output  CddTpsGen2_I2C_pfnWriteFailedClbk               = &TestExt_ActionFailedClbk 
/// \output  TestExt_ActionSuccessClbk_HitCount     = 0u                                 
/// \output  TestExt_ActionFailedClbk_HitCount      = 0u                                 
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_I2C_WriteEeprom_TestCase1(void)
{
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  uint8 aucData_List[10];
  uint16 unStartAddress = 0x16u;
  uint16 unLength       = 10u;
  tCddTpsGen2_I2C_pFnct   pfnReadSuccessClbk = TestExt_ActionSuccessClbk;
  tCddTpsGen2_I2C_pFnct   pfnReadFailedClbk  = TestExt_ActionFailedClbk;
  tCddTpsGen2_I2C_eStatus *peRet = NULL_PTR;

  CddTpsGen2_I2C_State = CddTpsGen2_I2C_Idle;
  TestExt_ActionSuccessClbk_HitCount = 0u;
  TestExt_ActionFailedClbk_HitCount  = 0u;

  //Step 3) Call the FUT
  peRet = CddTpsGen2_I2C_WriteEeprom(aucData_List, unStartAddress, unLength, pfnReadSuccessClbk, pfnReadFailedClbk);

  //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_ucPtrWriteData                             , aucData_List                                  , == );
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_unWriteStartAddress                        , 0x16u                                         , == );
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_unWriteEndAddress                          , 0x20u                                         , == );
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_ucWriteTimeoutCounter                      , 0                                             , == );
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_State                                      , CddTpsGen2_I2C_Write_Data                     , == );
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_WriteStatus                                , CddTpsGen2_I2C_Pending                        , == );
  AL_UNITTEST_CHECK(peRet                                                     , &CddTpsGen2_I2C_WriteStatus                   , == );
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_pfnWriteSuccessClbk                        , &TestExt_ActionSuccessClbk           , == );
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_pfnWriteFailedClbk                         , &TestExt_ActionFailedClbk            , == );
  AL_UNITTEST_CHECK(TestExt_ActionSuccessClbk_HitCount               , 0u                                            , == );
  AL_UNITTEST_CHECK(TestExt_ActionFailedClbk_HitCount                , 0u                                            , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_I2C_WriteEeprom_TestCase2
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Check I2C write eeprom function when CddTpsGen2_I2C_State is CddTpsGen2_I2C_Read_Start
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input   uint8 aucData_List[10];
/// \input   uint16 unStartAddress = 0x16u;
/// \input   uint16 unLength       = 10u;
/// \input   tCddTpsGen2_I2C_pFnct   pfnReadSuccessClbk = TestExt_ActionSuccessClbk;
/// \input   tCddTpsGen2_I2C_pFnct   pfnReadFailedClbk  = TestExt_ActionFailedClbk;
/// \input   tCddTpsGen2_I2C_eStatus *peRet = NULL_PTR;
/// \input   CddTpsGen2_I2C_State = CddTpsGen2_I2C_Write_Data;
/// \input   TestExt_ActionSuccessClbk_HitCount = 0u;
/// \input   TestExt_ActionFailedClbk_HitCount  = 0u;
/// \input   CddTpsGen2_I2C_ucPtrReadData        = aucData_List;
/// \input   CddTpsGen2_I2C_unWriteStartAddress  = 0x00u;
/// \input   CddTpsGen2_I2C_pfnWriteFailedClbk   = NULL_PTR;
/// \input   CddTpsGen2_I2C_pfnWriteSuccessClbk  = NULL_PTR;
/// \input   CddTpsGen2_I2C_WriteStatus          = CddTpsGen2_I2C_Pending;
///
///    - Expected test results: 
/// \output  CddTpsGen2_I2C_unWriteStartAddress               = 0x00u                             
/// \output  CddTpsGen2_I2C_ucWriteTimeoutCounter             = 0                                 
/// \output  CddTpsGen2_I2C_State                             = CddTpsGen2_I2C_Write_Data         
/// \output  CddTpsGen2_I2C_WriteStatus                       = CddTpsGen2_I2C_Rejected           
/// \output  peRet                                            = &CddTpsGen2_I2C_WriteStatus       
/// \output  CddTpsGen2_I2C_pfnWriteSuccessClbk               = NULL_PTR                          
/// \output  CddTpsGen2_I2C_pfnWriteFailedClbk                = &TestExt_ActionFailedClbk
/// \output  TestExt_ActionSuccessClbk_HitCount      = 0u                                
/// \output  TestExt_ActionFailedClbk_HitCount       = 1u                                
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_I2C_WriteEeprom_TestCase2(void)
{
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  uint8 aucData_List[10];
  uint16 unStartAddress = 0x16u;
  uint16 unLength       = 10u;
  tCddTpsGen2_I2C_pFnct   pfnReadSuccessClbk = TestExt_ActionSuccessClbk;
  tCddTpsGen2_I2C_pFnct   pfnReadFailedClbk  = TestExt_ActionFailedClbk;
  tCddTpsGen2_I2C_eStatus *peRet = NULL_PTR;

  CddTpsGen2_I2C_State = CddTpsGen2_I2C_Write_Data;
  TestExt_ActionSuccessClbk_HitCount = 0u;
  TestExt_ActionFailedClbk_HitCount  = 0u;
  CddTpsGen2_I2C_ucPtrReadData        = aucData_List;
  CddTpsGen2_I2C_unWriteStartAddress  = 0x00u;
  CddTpsGen2_I2C_pfnWriteFailedClbk   = NULL_PTR;
  CddTpsGen2_I2C_pfnWriteSuccessClbk  = NULL_PTR;
  CddTpsGen2_I2C_WriteStatus          = CddTpsGen2_I2C_Pending;

  //Step 3) Call the FUT
  peRet = CddTpsGen2_I2C_WriteEeprom(aucData_List, unStartAddress, unLength, pfnReadSuccessClbk, pfnReadFailedClbk);

  //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_unWriteStartAddress                , 0x00u                                   , == );
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_ucWriteTimeoutCounter              , 0                                       , == );
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_State                              , CddTpsGen2_I2C_Write_Data               , == );
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_WriteStatus                        , CddTpsGen2_I2C_Rejected                 , == );
  AL_UNITTEST_CHECK(peRet                                             , &CddTpsGen2_I2C_WriteStatus             , == );
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_pfnWriteSuccessClbk                , NULL_PTR                                , == );
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_pfnWriteFailedClbk                 , &TestExt_ActionFailedClbk      , == );
  AL_UNITTEST_CHECK(TestExt_ActionSuccessClbk_HitCount       , 0u                                      , == );
  AL_UNITTEST_CHECK(TestExt_ActionFailedClbk_HitCount        , 1u                                      , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_I2C_WriteEeprom_TestCase3
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Check I2C write eeprom function when ucData_List and pfnReadFailedClbk are NULL_PTR
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input   uint16 unStartAddress = 0x16u;
/// \input   uint16 unLength       = 10u;
/// \input   tCddTpsGen2_I2C_pFnct   pfnReadSuccessClbk = TestExt_ActionSuccessClbk;
/// \input   tCddTpsGen2_I2C_pFnct   pfnReadFailedClbk  = NULL_PTR;
/// \input   tCddTpsGen2_I2C_eStatus *peRet = NULL_PTR;
/// \input   CddTpsGen2_I2C_State = CddTpsGen2_I2C_Idle;
/// \input   TestExt_ActionSuccessClbk_HitCount = 0u;
/// \input   TestExt_ActionFailedClbk_HitCount  = 0u;
/// \input   CddTpsGen2_I2C_ucPtrWriteData      = NULL_PTR;
/// \input   CddTpsGen2_I2C_unWriteStartAddress = 0x00u;
/// \input   CddTpsGen2_I2C_pfnReadFailedClbk  = NULL_PTR;
/// \input   CddTpsGen2_I2C_pfnReadSuccessClbk = NULL_PTR;
/// \input   CddTpsGen2_I2C_ReadStatus         = CddTpsGen2_I2C_Pending;
///
///    - Expected test results: 
/// \output  CddTpsGen2_I2C_unWriteStartAddress              = 0x00u                       
/// \output  CddTpsGen2_I2C_ucWriteTimeoutCounter            = 0                           
/// \output  CddTpsGen2_I2C_State                            = CddTpsGen2_I2C_Idle         
/// \output  CddTpsGen2_I2C_WriteStatus                      = CddTpsGen2_I2C_Rejected     
/// \output  peRet                                           = &CddTpsGen2_I2C_WriteStatus 
/// \output  CddTpsGen2_I2C_pfnWriteFailedClbk               = NULL_PTR                    
/// \output  CddTpsGen2_I2C_pfnWriteSuccessClbk              = NULL_PTR                    
/// \output  TestExt_ActionSuccessClbk_HitCount     = 0u                           
/// \output  TestExt_ActionFailedClbk_HitCount      = 0u                           
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_I2C_WriteEeprom_TestCase3(void)
{
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  uint16 unStartAddress = 0x16u;
  uint16 unLength       = 10u;
  tCddTpsGen2_I2C_pFnct   pfnReadSuccessClbk = TestExt_ActionSuccessClbk;
  tCddTpsGen2_I2C_pFnct   pfnReadFailedClbk  = NULL_PTR;
  tCddTpsGen2_I2C_eStatus *peRet = NULL_PTR;

  CddTpsGen2_I2C_State = CddTpsGen2_I2C_Idle;
  TestExt_ActionSuccessClbk_HitCount = 0u;
  TestExt_ActionFailedClbk_HitCount  = 0u;
  CddTpsGen2_I2C_ucPtrWriteData      = NULL_PTR;
  CddTpsGen2_I2C_unWriteStartAddress = 0x00u;
  CddTpsGen2_I2C_pfnReadFailedClbk  = NULL_PTR;
  CddTpsGen2_I2C_pfnReadSuccessClbk = NULL_PTR;
  CddTpsGen2_I2C_ReadStatus         = CddTpsGen2_I2C_Pending;

  //Step 3) Call the FUT
  peRet = CddTpsGen2_I2C_WriteEeprom(NULL_PTR, unStartAddress, unLength, pfnReadSuccessClbk, pfnReadFailedClbk);

  //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_unWriteStartAddress                          , 0x00u                                   , == );
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_ucWriteTimeoutCounter                        , 0                                       , == );
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_State                                        , CddTpsGen2_I2C_Idle                     , == );
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_WriteStatus                                  , CddTpsGen2_I2C_Rejected                 , == );
  AL_UNITTEST_CHECK(peRet                                                       , &CddTpsGen2_I2C_WriteStatus             , == );
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_pfnWriteFailedClbk                           , NULL_PTR                                , == );
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_pfnWriteSuccessClbk                          , NULL_PTR                                , == );
  AL_UNITTEST_CHECK(TestExt_ActionSuccessClbk_HitCount                 , 0u                                      , == );
  AL_UNITTEST_CHECK(TestExt_ActionFailedClbk_HitCount                  , 0u                                      , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTpsGen2_I2C_WriteEeprom
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test Mt_CddTpsGen2_I2C_WriteEeprom function
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected Test Results : All contained test cases are passed
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_I2C_WriteEeprom(void)
{
  Mt_CddTpsGen2_I2C_WriteEeprom_TestCase1();
  Mt_CddTpsGen2_I2C_WriteEeprom_TestCase2();
  Mt_CddTpsGen2_I2C_WriteEeprom_TestCase3();
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_I2C_HandlePreinit
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Check the preinit handler
///
///    - Test Design Technique:  DT (Decision Table)
///
///    - Preconditions: 
/// \input const asTestCaseData[] = // ucAck_in             , I2C_State_in          
///                            { {CDDTPSGEN2_ACK_BYTE , CddTpsGen2_I2C_Preinit
///                            { {0x7Eu               , CddTpsGen2_I2C_Preinit
///
///    - Expected test results: 
/// \output     ucAck_out , I2C_State_out
///          {  0x00u     , CddTpsGen2_I2C_Init    
///          {  0x7Eu     , CddTpsGen2_I2C_NotInit 
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_I2C_HandlePreinit(void)
{
  typedef struct tsTestDataIn
  {
    uint8                   ucAck_in;
    tCddTpsGen2_I2C_eState  I2C_State_in;
  }tsTestDataIn;
  typedef struct tsTestDataOut
  {
    uint8                   ucAck_out;
    tCddTpsGen2_I2C_eState  I2C_State_out;
  }tsTestDataOut;
  typedef struct tsTestData
  {
    tsTestDataIn  sInputData;
    tsTestDataOut sOutputData;
  }tsTestData;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  tsTestData const asTestCaseData[] = {// ucAck_in             , I2C_State_in           ,   ucAck_out , I2C_State_out
                                  { {CDDTPSGEN2_ACK_BYTE , CddTpsGen2_I2C_Preinit},{  0x00u     , CddTpsGen2_I2C_Init     } },
                                  { {0x7Eu               , CddTpsGen2_I2C_Preinit},{  0x7Eu     , CddTpsGen2_I2C_NotInit  } },
  };

  for (uint8 ucIdx = 0u; ucIdx < (sizeof(asTestCaseData) / sizeof(tsTestData)) ; ucIdx++)
  {
    CddTpsGen2_I2C_State = asTestCaseData[ucIdx].sInputData.I2C_State_in;
    //Step 3) Call the FUT
    CddTpsGen2_I2C_HandlePreinit(&asTestCaseData[ucIdx].sInputData.ucAck_in);

    //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
    AL_UNITTEST_CHECK(asTestCaseData[ucIdx].sInputData.ucAck_in   , asTestCaseData[ucIdx].sOutputData.ucAck_out       , == );
    AL_UNITTEST_CHECK(CddTpsGen2_I2C_State                        , asTestCaseData[ucIdx].sOutputData.I2C_State_out   , == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_I2C_HandleInit
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Check the init handler
///
///    - Test Design Technique:  DT (Decision Table)
///
///    - Preconditions: 
/// \input const asTestCaseData[] = // ucAck_in             , I2C_State_in           , I2C_InitStatus_in        
///                            { {CDDTPSGEN2_ACK_BYTE , CddTpsGen2_I2C_Preinit , CddTpsGen2_I2C_Rejected }
///                            { {0x7Eu               , CddTpsGen2_I2C_Preinit , CddTpsGen2_I2C_Rejected }
/// /// \input CddTpsGen2_I2C_pfnInitSuccessClbk = TestExt_ActionSuccessClbk;
/// /// \input TestExt_ActionSuccessClbk_HitCount = 0u;
///
///    - Expected test results: 
/// \output     ucAck_out , I2C_State_out          , I2C_InitStatus_out        , Clbk_Stub_HitCount_out
///          {  0x00u     , CddTpsGen2_I2C_Idle    , CddTpsGen2_I2C_Completed  , 1u                    }
///          {  0x7Eu     , CddTpsGen2_I2C_NotInit , CddTpsGen2_I2C_Completed  , 0u                    }
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_I2C_HandleInit(void)
{
  typedef struct tsTestDataIn
  {
    uint8                   ucAck_in;
    tCddTpsGen2_I2C_eState  I2C_State_in;
    tCddTpsGen2_I2C_eStatus I2C_InitStatus_in;
  }tsTestDataIn;
  typedef struct tsTestDataOut
  {
    uint8                   ucAck_out;
    tCddTpsGen2_I2C_eState  I2C_State_out;
    tCddTpsGen2_I2C_eStatus I2C_InitStatus_out;
    uint8                   Clbk_Stub_HitCount_out;
  }tsTestDataOut;
  typedef struct tsTestData
  {
    tsTestDataIn  sInputData;
    tsTestDataOut sOutputData;
  }tsTestData;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  tsTestData const asTestCaseData[] = {// ucAck_in             , I2C_State_in           , I2C_InitStatus_in        ,   ucAck_out , I2C_State_out          , I2C_InitStatus_out        , Clbk_Stub_HitCount_out
                                  { {CDDTPSGEN2_ACK_BYTE , CddTpsGen2_I2C_Preinit , CddTpsGen2_I2C_Rejected },{  0x00u     , CddTpsGen2_I2C_Idle    , CddTpsGen2_I2C_Completed  , 1u                    } },
                                  { {0x7Eu               , CddTpsGen2_I2C_Preinit , CddTpsGen2_I2C_Rejected },{  0x7Eu     , CddTpsGen2_I2C_NotInit , CddTpsGen2_I2C_Completed  , 0u                    } },
  };
  CddTpsGen2_I2C_pfnInitSuccessClbk = TestExt_ActionSuccessClbk;

  for (uint8 ucIdx = 0u; ucIdx < (sizeof(asTestCaseData) / sizeof(tsTestData)) ; ucIdx++)
  {
    TestExt_ActionSuccessClbk_HitCount = 0u;
    CddTpsGen2_I2C_State = asTestCaseData[ucIdx].sInputData.I2C_State_in;

    //Step 3) Call the FUT
    CddTpsGen2_I2C_HandleInit(&asTestCaseData[ucIdx].sInputData.ucAck_in);

    //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
    AL_UNITTEST_CHECK(asTestCaseData[ucIdx].sInputData.ucAck_in       , asTestCaseData[ucIdx].sOutputData.ucAck_out                 , == );
    AL_UNITTEST_CHECK(CddTpsGen2_I2C_State                            , asTestCaseData[ucIdx].sOutputData.I2C_State_out             , == );
    AL_UNITTEST_CHECK(CddTpsGen2_I2C_InitStatus                       , asTestCaseData[ucIdx].sOutputData.I2C_InitStatus_out        , == );
    AL_UNITTEST_CHECK(TestExt_ActionSuccessClbk_HitCount     , asTestCaseData[ucIdx].sOutputData.Clbk_Stub_HitCount_out    , == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_I2C_HandleStart
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Check the start handler states
///
///    - Test Design Technique:  DT (Decision Table)
///
///    - Preconditions: 
/// \input const asTestCaseData[] = ucAck_in             , I2C_State_in                  
///                           {CDDTPSGEN2_ACK_BYTE , CddTpsGen2_I2C_Read_Start    }
///                           {CDDTPSGEN2_ACK_BYTE , CddTpsGen2_I2C_Read_Status   }
///                           {CDDTPSGEN2_ACK_BYTE , CddTpsGen2_I2C_Read_Data     }
///                           {CDDTPSGEN2_ACK_BYTE , CddTpsGen2_I2C_Write_Data    }
///                           {CDDTPSGEN2_ACK_BYTE , CddTpsGen2_I2C_Write_Start   }
///                           {CDDTPSGEN2_ACK_BYTE , CddTpsGen2_I2C_Write_Status  }
///                           {CDDTPSGEN2_ACK_BYTE , CddTpsGen2_I2C_ControlReset  }
///                           {0x7Eu               , CddTpsGen2_I2C_ControlReset  }
///
///    - Expected test results: 
/// \output     ucAck_out , I2C_State_out          
///          {  0x00u     , CddTpsGen2_I2C_Read_Status   }
///          {  0x00u     , CddTpsGen2_I2C_Read_Status   }
///          {  0x00u     , CddTpsGen2_I2C_Read_Status   }
///          {  0x00u     , CddTpsGen2_I2C_Write_Status  }
///          {  0x00u     , CddTpsGen2_I2C_Write_Status  }
///          {  0x00u     , CddTpsGen2_I2C_Write_Status  }
///          {  0x00u     , CddTpsGen2_I2C_Idle          }
///          {  0x7Eu     , CddTpsGen2_I2C_ControlReset  }
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_I2C_HandleStart(void)
{
  typedef struct tsTestDataIn
  {
    uint8                   ucAck_in;
    tCddTpsGen2_I2C_eState  I2C_State_in;
  }tsTestDataIn;
  typedef struct tsTestDataOut
  {
    uint8                   ucAck_out;
    tCddTpsGen2_I2C_eState  I2C_State_out;
  }tsTestDataOut;
  typedef struct tsTestData
  {
    tsTestDataIn  sInputData;
    tsTestDataOut sOutputData;
  }tsTestData;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  tsTestData const asTestCaseData[] = {// ucAck_in             , I2C_State_in                  ,   ucAck_out , I2C_State_out          
                                  { {CDDTPSGEN2_ACK_BYTE , CddTpsGen2_I2C_Read_Start    },{  0x00u     , CddTpsGen2_I2C_Read_Status   } },
                                  { {CDDTPSGEN2_ACK_BYTE , CddTpsGen2_I2C_Read_Status   },{  0x00u     , CddTpsGen2_I2C_Read_Status   } },
                                  { {CDDTPSGEN2_ACK_BYTE , CddTpsGen2_I2C_Read_Data     },{  0x00u     , CddTpsGen2_I2C_Read_Status   } },
                                  { {CDDTPSGEN2_ACK_BYTE , CddTpsGen2_I2C_Write_Data    },{  0x00u     , CddTpsGen2_I2C_Write_Status  } },
                                  { {CDDTPSGEN2_ACK_BYTE , CddTpsGen2_I2C_Write_Start   },{  0x00u     , CddTpsGen2_I2C_Write_Status  } },
                                  { {CDDTPSGEN2_ACK_BYTE , CddTpsGen2_I2C_Write_Status  },{  0x00u     , CddTpsGen2_I2C_Write_Status  } },
                                  { {CDDTPSGEN2_ACK_BYTE , CddTpsGen2_I2C_ControlReset  },{  0x00u     , CddTpsGen2_I2C_Idle          } },
                                  { {0x7Eu               , CddTpsGen2_I2C_ControlReset  },{  0x7Eu     , CddTpsGen2_I2C_ControlReset  } },
  };

  for (uint8 ucIdx = 0u; ucIdx < (sizeof(asTestCaseData) / sizeof(tsTestData)) ; ucIdx++)
  {
    CddTpsGen2_I2C_State = asTestCaseData[ucIdx].sInputData.I2C_State_in;

    //Step 3) Call the FUT
    CddTpsGen2_I2C_HandleStart(&asTestCaseData[ucIdx].sInputData.ucAck_in);

    //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
    AL_UNITTEST_CHECK(asTestCaseData[ucIdx].sInputData.ucAck_in       , asTestCaseData[ucIdx].sOutputData.ucAck_out                 , == );
    AL_UNITTEST_CHECK(CddTpsGen2_I2C_State                            , asTestCaseData[ucIdx].sOutputData.I2C_State_out             , == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_I2C_HandleWritingStatus
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Check the entire flow of writing status handler
///
///    - Test Design Technique:  DT (Decision Table)
///
///    - Preconditions: 
/// \input const asTestCaseData[] = //  ucStatus_in                , I2C_State_in              , I2C_WriteStatus_in       
///                            { {CDDTPSGEN2_I2CSTAT_ADRNACK , CddTpsGen2_I2C_Idle       , CddTpsGen2_I2C_Rejected }
///                            { {CDDTPSGEN2_I2CSTAT_SLANACK , CddTpsGen2_I2C_Idle       , CddTpsGen2_I2C_Rejected }
///                            { {CDDTPSGEN2_I2CSTAT_RFF     , CddTpsGen2_I2C_Idle       , CddTpsGen2_I2C_Rejected }
///                            { {CDDTPSGEN2_I2CSTAT_RFF     , CddTpsGen2_I2C_Write_Data , CddTpsGen2_I2C_Rejected }
///                            { {CDDTPSGEN2_I2CSTAT_BUSY    , CddTpsGen2_I2C_Write_Data , CddTpsGen2_I2C_Rejected }
/// \input CddTpsGen2_I2C_unWriteEndAddress      = 80u;                   
/// \input CddTpsGen2_I2C_unWriteStartAddress    = 78u;                   
/// \input CddTpsGen2_I2C_pfnWriteSuccessClbk    = &TestExt_ActionSuccessClbk;                   
/// \input CddTpsGen2_I2C_pfnWriteFailedClbk     = &TestExt_ActionFailedClbk;                   
/// \input CddTpsGen2_I2C_ucPtrWriteData         = &aucTestData[25];                   
/// \input TestExt_ActionSuccessClbk_HitCount  = 0u;
/// \input TestExt_ActionFailedClbk_HitCount   = 0u;
///
///    - Expected test results: 
/// \output     I2C_State_out               , I2C_WriteStatus_out      , WriteFailedClbk_HitCnt_out , WriteSuccessClbk_HitCnt_out , I2C_unWriteStartAddress_out ,  I2C_ucPtrWriteData_out , I2C_ucWriteTimeoutCounter_out
///          {  CddTpsGen2_I2C_ControlReset , CddTpsGen2_I2C_Failed    , 1u                         , 0u                          , 78u                         ,  &aucTestData[25]       , 5u   } }, // test for if (0u != (uint8)(ucStatus & (uint8)CDDTPSGEN2_I2C_WR_STATUS_VALID))
///          {  CddTpsGen2_I2C_Write_Start  , CddTpsGen2_I2C_Rejected  , 0u                         , 0u                          , 78u                         ,  &aucTestData[25]       , 5u   } }, // test for else if ((ucStatus & (uint8)CDDTPSGEN2_I2CSTAT_SLANACK) != 0u)
///          {  CddTpsGen2_I2C_Write_Data   , CddTpsGen2_I2C_Rejected  , 0u                         , 0u                          , 79u                         ,  &aucTestData[26]       , 0u   } }, // test for if (CddTpsGen2_I2C_unWriteStartAddress < CddTpsGen2_I2C_unWriteEndAddress) -> TRUE
///          {  CddTpsGen2_I2C_Idle         , CddTpsGen2_I2C_Completed , 0u                         , 1u                          , 80u                         ,  &aucTestData[27]       , 0u   } }, // test for if (CddTpsGen2_I2C_unWriteStartAddress < CddTpsGen2_I2C_unWriteEndAddress) -> FALSE
///          {  CddTpsGen2_I2C_Write_Data   , CddTpsGen2_I2C_Rejected  , 0u                         , 0u                          , 80u                         ,  &aucTestData[27]       , 5u   } }, // test for if ((ucStatus & (uint8)CDDTPSGEN2_I2CSTAT_BUSY) != (uint8)CDDTPSGEN2_I2CSTAT_BUSY) -> FALSE
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_I2C_HandleWritingStatus(void)
{
  typedef struct tsTestDataIn
  {
    uint8                   ucStatus_in;
    tCddTpsGen2_I2C_eState  I2C_State_in;
    tCddTpsGen2_I2C_eStatus I2C_WriteStatus_in;
  }tsTestDataIn;
  typedef struct tsTestDataOut
  {
    tCddTpsGen2_I2C_eState  I2C_State_out;
    tCddTpsGen2_I2C_eStatus I2C_WriteStatus_out;
    uint8                   WriteFailedClbk_HitCnt_out;
    uint8                   WriteSuccessClbk_HitCnt_out;
    uint8                   I2C_unWriteStartAddress_out;
    uint8*                  I2C_ucPtrWriteData_out;
    uint8                   I2C_ucWriteTimeoutCounter_out;
  }tsTestDataOut;
  typedef struct tsTestData
  {
    tsTestDataIn  sInputData;
    tsTestDataOut sOutputData;
  }tsTestData;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  uint8 aucTestData[50];
  tsTestData const asTestCaseData[] =
  {//  ucStatus_in                , I2C_State_in              , I2C_WriteStatus_in       ,   I2C_State_out               , I2C_WriteStatus_out      , WriteFailedClbk_HitCnt_out , WriteSuccessClbk_HitCnt_out , I2C_unWriteStartAddress_out ,  I2C_ucPtrWriteData_out , I2C_ucWriteTimeoutCounter_out
    { {CDDTPSGEN2_I2CSTAT_ADRNACK , CddTpsGen2_I2C_Idle       , CddTpsGen2_I2C_Rejected },{  CddTpsGen2_I2C_ControlReset , CddTpsGen2_I2C_Failed    , 1u                         , 0u                          , 78u                         ,  &aucTestData[25]       , 5u   } }, // test for if (0u != (uint8)(ucStatus & (uint8)CDDTPSGEN2_I2C_WR_STATUS_VALID))
    { {CDDTPSGEN2_I2CSTAT_SLANACK , CddTpsGen2_I2C_Idle       , CddTpsGen2_I2C_Rejected },{  CddTpsGen2_I2C_Write_Start  , CddTpsGen2_I2C_Rejected  , 0u                         , 0u                          , 78u                         ,  &aucTestData[25]       , 5u   } }, // test for else if ((ucStatus & (uint8)CDDTPSGEN2_I2CSTAT_SLANACK) != 0u)
    { {CDDTPSGEN2_I2CSTAT_RFF     , CddTpsGen2_I2C_Idle       , CddTpsGen2_I2C_Rejected },{  CddTpsGen2_I2C_Write_Data   , CddTpsGen2_I2C_Rejected  , 0u                         , 0u                          , 79u                         ,  &aucTestData[26]       , 0u   } }, // test for if (CddTpsGen2_I2C_unWriteStartAddress < CddTpsGen2_I2C_unWriteEndAddress) -> TRUE
    { {CDDTPSGEN2_I2CSTAT_RFF     , CddTpsGen2_I2C_Write_Data , CddTpsGen2_I2C_Rejected },{  CddTpsGen2_I2C_Idle         , CddTpsGen2_I2C_Completed , 0u                         , 1u                          , 80u                         ,  &aucTestData[27]       , 0u   } }, // test for if (CddTpsGen2_I2C_unWriteStartAddress < CddTpsGen2_I2C_unWriteEndAddress) -> FALSE
    { {CDDTPSGEN2_I2CSTAT_BUSY    , CddTpsGen2_I2C_Write_Data , CddTpsGen2_I2C_Rejected },{  CddTpsGen2_I2C_Write_Data   , CddTpsGen2_I2C_Rejected  , 0u                         , 0u                          , 80u                         ,  &aucTestData[27]       , 5u   } }, // test for if ((ucStatus & (uint8)CDDTPSGEN2_I2CSTAT_BUSY) != (uint8)CDDTPSGEN2_I2CSTAT_BUSY) -> FALSE
  };

  CddTpsGen2_I2C_unWriteEndAddress      = 80u;
  CddTpsGen2_I2C_unWriteStartAddress    = 78u;
  CddTpsGen2_I2C_pfnWriteSuccessClbk    = &TestExt_ActionSuccessClbk;
  CddTpsGen2_I2C_pfnWriteFailedClbk     = &TestExt_ActionFailedClbk;
  CddTpsGen2_I2C_ucPtrWriteData         = &aucTestData[25];

  for (uint8 ucIdx = 0u; ucIdx < (sizeof(asTestCaseData) / sizeof(tsTestData)) ; ucIdx++)
  {
    TestExt_ActionSuccessClbk_HitCount  = 0u;
    TestExt_ActionFailedClbk_HitCount   = 0u;
    CddTpsGen2_I2C_ucWriteTimeoutCounter         = 5u;
    CddTpsGen2_I2C_State          = asTestCaseData[ucIdx].sInputData.I2C_State_in;
    CddTpsGen2_I2C_WriteStatus    = asTestCaseData[ucIdx].sInputData.I2C_WriteStatus_in;


    //Step 3) Call the FUT
    CddTpsGen2_I2C_HandleWritingStatus(asTestCaseData[ucIdx].sInputData.ucStatus_in);

    //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
    AL_UNITTEST_CHECK(CddTpsGen2_I2C_State                                    , asTestCaseData[ucIdx].sOutputData.I2C_State_out                               , == );
    AL_UNITTEST_CHECK(CddTpsGen2_I2C_WriteStatus                              , asTestCaseData[ucIdx].sOutputData.I2C_WriteStatus_out                         , == );
    AL_UNITTEST_CHECK(TestExt_ActionFailedClbk_HitCount              , asTestCaseData[ucIdx].sOutputData.WriteFailedClbk_HitCnt_out                  , == );
    AL_UNITTEST_CHECK(TestExt_ActionSuccessClbk_HitCount             , asTestCaseData[ucIdx].sOutputData.WriteSuccessClbk_HitCnt_out                 , == );
    AL_UNITTEST_CHECK(CddTpsGen2_I2C_unWriteStartAddress                      , asTestCaseData[ucIdx].sOutputData.I2C_unWriteStartAddress_out                 , == );
    AL_UNITTEST_CHECK(CddTpsGen2_I2C_ucPtrWriteData                           , asTestCaseData[ucIdx].sOutputData.I2C_ucPtrWriteData_out                      , == );
    AL_UNITTEST_CHECK(CddTpsGen2_I2C_ucWriteTimeoutCounter                    , asTestCaseData[ucIdx].sOutputData.I2C_ucWriteTimeoutCounter_out               , == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_I2C_CommandReadStart
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Check read length is calculated correctly and filled in the data mirror
///
///    - Test Design Technique:  DT (Decision Table)
///
///    - Preconditions: 
/// \input const asTestCaseData[] =  //  ucSelSch_in                   , I2C_unReadStartAddress_in , I2C_ReadStatus_in       , I2C_State_in         
///                            { { CDDTPSGEN2_STATE_EE_INIT      , 245u                      , CddTpsGen2_I2C_Pending  , CddTpsGen2_I2C_Init }
///                            { { CDDTPSGEN2_STATE_EE_INIT      , 244u                      , CddTpsGen2_I2C_Pending  , CddTpsGen2_I2C_Init }
///                            { { CDDTPSGEN2_STATE_EE_INIT      , 501u                      , CddTpsGen2_I2C_Pending  , CddTpsGen2_I2C_Init }
/// \input CddTpsGen2_I2C_unReadEndAddress = 500u;
/// \input CddTpsGen2_I2C_pfnReadSuccessClbk = &TestExt_ActionSuccessClbk;
/// \input CddTpsGen2_I2C_ucReadBytesLeft = 0u;
/// \input TestExt_ActionSuccessClbk_HitCount           = 0u;
/// \input CddTpsGen2_I2C_ucReadTimeoutCounter                   = 5u;
/// \input CddTpsGen2_DataMirrorEE.CtrlTx.TxsI2CSEQCFG.ucByte[0] = 0u;
/// \input CddTpsGen2_DataMirrorEE.CtrlTx.TxsI2CSEQCFG.ucByte[1] = 0u;
/// \input CddTpsGen2_DataMirrorEE.CtrlTx.TxsI2CSEQCFG.ucByte[2] = 0u;
/// \input CddTpsGen2_DataMirrorEE.CtrlTx.TxsI2CSEQCFG.ucByte[3] = 0u;
///
///    - Expected test results: 
/// \output   ucSelSch_out                    , I2C_ReadStatus_out       , I2C_State_out       , I2C_ucReadTimeoutCounter_out, ActionSuccessClbk_Cnt_out   , aucByte_out
///         { CDDTPSGEN2_STATE_EE_READ_START  , CddTpsGen2_I2C_Pending   , CddTpsGen2_I2C_Init , 5u                          , 0u                          , { 0xA0u , 0xFFu, 0xF5u, 0x06u }
///         { CDDTPSGEN2_STATE_EE_READ_START  , CddTpsGen2_I2C_Pending   , CddTpsGen2_I2C_Init , 5u                          , 0u                          , { 0xA0u , 0xFFu, 0xF4u, 0x06u }
///         { CDDTPSGEN2_STATE_EE_INIT        , CddTpsGen2_I2C_Completed , CddTpsGen2_I2C_Idle , 0u                          , 1u                          , { 0u    , 0u   , 0u   , 0u    }
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_I2C_CommandReadStart(void)
{
  typedef struct tsTestDataIn
  {
    uint8                    ucSelSch_in;
    uint16                   I2C_unReadStartAddress_in;
    tCddTpsGen2_I2C_eStatus  I2C_ReadStatus_in;
    tCddTpsGen2_I2C_eState   I2C_State_in;
  }tsTestDataIn;
  typedef struct tsTestDataOut
  {
    uint8                    ucSelSch_out;
    tCddTpsGen2_I2C_eStatus  I2C_ReadStatus_out;
    tCddTpsGen2_I2C_eState   I2C_State_out;
    uint8                    I2C_ucReadTimeoutCounter_out;
    uint8                    ActionSuccessClbk_Cnt_out;
    uint8                    aucByte_out[4];
  }tsTestDataOut;
  typedef struct tsTestData
  {
    tsTestDataIn  sInputData;
    tsTestDataOut sOutputData;
  }tsTestData;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  tsTestData const asTestCaseData[] = {
    //  ucSelSch_in                   , I2C_unReadStartAddress_in , I2C_ReadStatus_in       , I2C_State_in         ,  ucSelSch_out                    , I2C_ReadStatus_out       , I2C_State_out       , I2C_ucReadTimeoutCounter_out, ActionSuccessClbk_Cnt_out   , aucByte_out
    { { CDDTPSGEN2_STATE_EE_INIT      , 245u                      , CddTpsGen2_I2C_Pending  , CddTpsGen2_I2C_Init },{ CDDTPSGEN2_STATE_EE_READ_START  , CddTpsGen2_I2C_Pending   , CddTpsGen2_I2C_Init , 5u                          , 0u                          , { 0xA0u , 0xFFu, 0xF5u, 0x06u } }}, // Test for when if (unlength > 255u) -> FALSE; unlength = 255
    { { CDDTPSGEN2_STATE_EE_INIT      , 244u                      , CddTpsGen2_I2C_Pending  , CddTpsGen2_I2C_Init },{ CDDTPSGEN2_STATE_EE_READ_START  , CddTpsGen2_I2C_Pending   , CddTpsGen2_I2C_Init , 5u                          , 0u                          , { 0xA0u , 0xFFu, 0xF4u, 0x06u } }}, // Test for when if (unlength > 255u) -> TRUE ; unlength = 256
    { { CDDTPSGEN2_STATE_EE_INIT      , 501u                      , CddTpsGen2_I2C_Pending  , CddTpsGen2_I2C_Init },{ CDDTPSGEN2_STATE_EE_INIT        , CddTpsGen2_I2C_Completed , CddTpsGen2_I2C_Idle , 0u                          , 1u                          , { 0u    , 0u   , 0u   , 0u    } }}, // Test for when if (CddTpsGen2_I2C_unReadEndAddress > CddTpsGen2_I2C_unReadStartAddress) -> FALSE
  };

  CddTpsGen2_I2C_unReadEndAddress = 500u;
  CddTpsGen2_I2C_pfnReadSuccessClbk = &TestExt_ActionSuccessClbk;

  for (uint8 ucIdx = 0u; ucIdx < (sizeof(asTestCaseData) / sizeof(tsTestData)) ; ucIdx++)
  {
    CddTpsGen2_I2C_ucReadBytesLeft = 0u;
    TestExt_ActionSuccessClbk_HitCount           = 0u;
    CddTpsGen2_I2C_ucReadTimeoutCounter                   = 5u;
    CddTpsGen2_DataMirrorEE.CtrlTx.TxsI2CSEQCFG.ucByte[0] = 0u;
    CddTpsGen2_DataMirrorEE.CtrlTx.TxsI2CSEQCFG.ucByte[1] = 0u;
    CddTpsGen2_DataMirrorEE.CtrlTx.TxsI2CSEQCFG.ucByte[2] = 0u;
    CddTpsGen2_DataMirrorEE.CtrlTx.TxsI2CSEQCFG.ucByte[3] = 0u;

    CddTpsGen2_I2C_unReadStartAddress = asTestCaseData[ucIdx].sInputData.I2C_unReadStartAddress_in;
    CddTpsGen2_I2C_ReadStatus         = asTestCaseData[ucIdx].sInputData.I2C_ReadStatus_in;
    CddTpsGen2_I2C_State              = asTestCaseData[ucIdx].sInputData.I2C_State_in;

    //Step 3) Call the FUT
    CddTpsGen2_I2C_CommandReadStart(&asTestCaseData[ucIdx].sInputData.ucSelSch_in);

    //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
    AL_UNITTEST_CHECK(asTestCaseData[ucIdx].sInputData.ucSelSch_in              , asTestCaseData[ucIdx].sOutputData.ucSelSch_out                      , == );
    AL_UNITTEST_CHECK(CddTpsGen2_I2C_ReadStatus                                 , asTestCaseData[ucIdx].sOutputData.I2C_ReadStatus_out                , == );
    AL_UNITTEST_CHECK(CddTpsGen2_I2C_State                                      , asTestCaseData[ucIdx].sOutputData.I2C_State_out                     , == );
    AL_UNITTEST_CHECK(CddTpsGen2_I2C_ucReadTimeoutCounter                       , asTestCaseData[ucIdx].sOutputData.I2C_ucReadTimeoutCounter_out      , == );
    AL_UNITTEST_CHECK(TestExt_ActionSuccessClbk_HitCount               , asTestCaseData[ucIdx].sOutputData.ActionSuccessClbk_Cnt_out         , == );
    for (uint8 ucIdxData = 0u; ucIdxData < 4u; ucIdxData++)
    {
      AL_UNITTEST_CHECK(CddTpsGen2_DataMirrorEE.CtrlTx.TxsI2CSEQCFG.ucByte[ucIdxData]    , asTestCaseData[ucIdx].sOutputData.aucByte_out[ucIdxData]   , == );
    }
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_I2C_CommandReadData
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Check if read length and scheduler are set correctly
///
///    - Test Design Technique:  DT (Decision Table)
///
///    - Preconditions: 
/// \input const asTestCaseData[] =   ucSelSch_in                   , I2C_ucReadBytesLeft_in 
///                           { CDDTPSGEN2_STATE_EE_RR_STATUS , 15u                   }
///                           { CDDTPSGEN2_STATE_EE_RR_STATUS , 14u                   }
///                           { CDDTPSGEN2_STATE_EE_RR_STATUS , 13u                   }
///                           { CDDTPSGEN2_STATE_EE_RR_STATUS , 12u                   }
///                           { CDDTPSGEN2_STATE_EE_RR_STATUS , 11u                   }
///                           { CDDTPSGEN2_STATE_EE_RR_STATUS , 10u                   }
///                           { CDDTPSGEN2_STATE_EE_RR_STATUS , 9u                    }
///                           { CDDTPSGEN2_STATE_EE_RR_STATUS , 8u                    }
///                           { CDDTPSGEN2_STATE_EE_RR_STATUS , 7u                    }
///                           { CDDTPSGEN2_STATE_EE_RR_STATUS , 6u                    }
///                           { CDDTPSGEN2_STATE_EE_RR_STATUS , 5u                    }
///                           { CDDTPSGEN2_STATE_EE_RR_STATUS , 4u                    }
///                           { CDDTPSGEN2_STATE_EE_RR_STATUS , 3u                    }
///                           { CDDTPSGEN2_STATE_EE_RR_STATUS , 2u                    }
///                           { CDDTPSGEN2_STATE_EE_RR_STATUS , 1u                    }
///                           { CDDTPSGEN2_STATE_EE_RR_STATUS , 16u                   }
/// \input CddTpsGen2_I2C_ucCmdReadData_RxLength = 0u;
///
///    - Expected test results: 
/// \output   ucSelSch_out                       ,  I2C_ucCmdReadData_RxLength_out
///         { CDDTPSGEN2_STATE_EE_READ_12_BYTES  ,  12u                          }
///         { CDDTPSGEN2_STATE_EE_READ_12_BYTES  ,  12u                          }
///         { CDDTPSGEN2_STATE_EE_READ_12_BYTES  ,  12u                          }
///         { CDDTPSGEN2_STATE_EE_READ_12_BYTES  ,  12u                          }
///         { CDDTPSGEN2_STATE_EE_READ_4_BYTES   ,  4u                           }
///         { CDDTPSGEN2_STATE_EE_READ_4_BYTES   ,  4u                           }
///         { CDDTPSGEN2_STATE_EE_READ_4_BYTES   ,  4u                           }
///         { CDDTPSGEN2_STATE_EE_READ_4_BYTES   ,  4u                           }
///         { CDDTPSGEN2_STATE_EE_READ_4_BYTES   ,  4u                           }
///         { CDDTPSGEN2_STATE_EE_READ_4_BYTES   ,  4u                           }
///         { CDDTPSGEN2_STATE_EE_READ_4_BYTES   ,  4u                           }
///         { CDDTPSGEN2_STATE_EE_READ_4_BYTES   ,  4u                           }
///         { CDDTPSGEN2_STATE_EE_READ_3_BYTES   ,  3u                           }
///         { CDDTPSGEN2_STATE_EE_READ_2_BYTES   ,  2u                           }
///         { CDDTPSGEN2_STATE_EE_READ_1_BYTE    ,  1u                           }
///         { CDDTPSGEN2_STATE_EE_READ_16_BYTES  ,  16u                          }
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_I2C_CommandReadData(void)
{
  typedef struct tsTestDataIn
  {
    uint8                    ucSelSch_in;
    uint8                    I2C_ucReadBytesLeft_in;
  }tsTestDataIn;
  typedef struct tsTestDataOut
  {
    uint8                    ucSelSch_out;
    uint8                    I2C_ucCmdReadData_RxLength_out;
  }tsTestDataOut;
  typedef struct tsTestData
  {
    tsTestDataIn  sInputData;
    tsTestDataOut sOutputData;
  }tsTestData;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  tsTestData const asTestCaseData[] = {
    //  ucSelSch_in                   , I2C_ucReadBytesLeft_in ,  ucSelSch_out                       ,  I2C_ucCmdReadData_RxLength_out
    { { CDDTPSGEN2_STATE_EE_RR_STATUS , 15u                   },{ CDDTPSGEN2_STATE_EE_READ_12_BYTES  ,  12u                          }},
    { { CDDTPSGEN2_STATE_EE_RR_STATUS , 14u                   },{ CDDTPSGEN2_STATE_EE_READ_12_BYTES  ,  12u                          }},
    { { CDDTPSGEN2_STATE_EE_RR_STATUS , 13u                   },{ CDDTPSGEN2_STATE_EE_READ_12_BYTES  ,  12u                          }},
    { { CDDTPSGEN2_STATE_EE_RR_STATUS , 12u                   },{ CDDTPSGEN2_STATE_EE_READ_12_BYTES  ,  12u                          }},
    { { CDDTPSGEN2_STATE_EE_RR_STATUS , 11u                   },{ CDDTPSGEN2_STATE_EE_READ_4_BYTES   ,  4u                           }},
    { { CDDTPSGEN2_STATE_EE_RR_STATUS , 10u                   },{ CDDTPSGEN2_STATE_EE_READ_4_BYTES   ,  4u                           }},
    { { CDDTPSGEN2_STATE_EE_RR_STATUS , 9u                    },{ CDDTPSGEN2_STATE_EE_READ_4_BYTES   ,  4u                           }},
    { { CDDTPSGEN2_STATE_EE_RR_STATUS , 8u                    },{ CDDTPSGEN2_STATE_EE_READ_4_BYTES   ,  4u                           }},
    { { CDDTPSGEN2_STATE_EE_RR_STATUS , 7u                    },{ CDDTPSGEN2_STATE_EE_READ_4_BYTES   ,  4u                           }},
    { { CDDTPSGEN2_STATE_EE_RR_STATUS , 6u                    },{ CDDTPSGEN2_STATE_EE_READ_4_BYTES   ,  4u                           }},
    { { CDDTPSGEN2_STATE_EE_RR_STATUS , 5u                    },{ CDDTPSGEN2_STATE_EE_READ_4_BYTES   ,  4u                           }},
    { { CDDTPSGEN2_STATE_EE_RR_STATUS , 4u                    },{ CDDTPSGEN2_STATE_EE_READ_4_BYTES   ,  4u                           }},
    { { CDDTPSGEN2_STATE_EE_RR_STATUS , 3u                    },{ CDDTPSGEN2_STATE_EE_READ_3_BYTES   ,  3u                           }},
    { { CDDTPSGEN2_STATE_EE_RR_STATUS , 2u                    },{ CDDTPSGEN2_STATE_EE_READ_2_BYTES   ,  2u                           }},
    { { CDDTPSGEN2_STATE_EE_RR_STATUS , 1u                    },{ CDDTPSGEN2_STATE_EE_READ_1_BYTE    ,  1u                           }},
    { { CDDTPSGEN2_STATE_EE_RR_STATUS , 16u                   },{ CDDTPSGEN2_STATE_EE_READ_16_BYTES  ,  16u                          }},
  };

  for (uint8 ucIdx = 0u; ucIdx < (sizeof(asTestCaseData) / sizeof(tsTestData)) ; ucIdx++)
  {
    CddTpsGen2_I2C_ucCmdReadData_RxLength = 0u;
    CddTpsGen2_I2C_ucReadBytesLeft        = asTestCaseData[ucIdx].sInputData.I2C_ucReadBytesLeft_in;

    //Step 3) Call the FUT
    CddTpsGen2_I2C_CommandReadData(&asTestCaseData[ucIdx].sInputData.ucSelSch_in);

    //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
    AL_UNITTEST_CHECK(asTestCaseData[ucIdx].sInputData.ucSelSch_in       , asTestCaseData[ucIdx].sOutputData.ucSelSch_out                       , == );
    AL_UNITTEST_CHECK(CddTpsGen2_I2C_ucCmdReadData_RxLength              , asTestCaseData[ucIdx].sOutputData.I2C_ucCmdReadData_RxLength_out     , == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_I2C_HandleReadingStatus
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Check the reading status handler
///
///    - Test Design Technique:  DT (Decision Table)
///
///    - Preconditions: 
/// \input const asTestCaseData[] =   ucStatus_in                , I2C_ucReadBytesLeft_in , I2C_State_in              , I2C_ReadStatus_in      , 
///                           { CDDTPSGEN2_I2CSTAT_ADRNACK , 15u                    , CddTpsGen2_I2C_Read_Data  , CddTpsGen2_I2C_Pending } 
///                           { CDDTPSGEN2_I2CSTAT_SLANACK , 15u                    , CddTpsGen2_I2C_Read_Data  , CddTpsGen2_I2C_Pending } 
///                           { CDDTPSGEN2_I2CSTAT_DATNACK , 0u                     , CddTpsGen2_I2C_Read_Data  , CddTpsGen2_I2C_Pending } 
///                           { CDDTPSGEN2_I2CSTAT_DATNACK , 15u                    , CddTpsGen2_I2C_Read_Start , CddTpsGen2_I2C_Pending } 
///                           { CDDTPSGEN2_I2CSTAT_RFF     , 16u                    , CddTpsGen2_I2C_Read_Start , CddTpsGen2_I2C_Pending } 
///                           { CDDTPSGEN2_I2CSTAT_RFE     , 16u                    , CddTpsGen2_I2C_Read_Start , CddTpsGen2_I2C_Pending } 
///                           { 0x81                       , 16u                    , CddTpsGen2_I2C_Read_Start , CddTpsGen2_I2C_Pending } 
/// \input CddTpsGen2_I2C_pfnReadFailedClbk = TestExt_ActionFailedClbk;
/// \input TestExt_ActionFailedClbk_HitCount      = 0u;
///
///    - Expected test results: 
/// \output  I2C_State_out                ,  I2C_ReadStatus_out     , ucActionFailedClbk_HitCnt_out
///         { CddTpsGen2_I2C_ControlReset ,  CddTpsGen2_I2C_Failed  , 1u                         }}
///         { CddTpsGen2_I2C_Read_Start   ,  CddTpsGen2_I2C_Pending , 0u                         }}
///         { CddTpsGen2_I2C_Read_Start   ,  CddTpsGen2_I2C_Pending , 0u                         }}
///         { CddTpsGen2_I2C_Read_Data    ,  CddTpsGen2_I2C_Pending , 0u                         }}
///         { CddTpsGen2_I2C_Read_Data    ,  CddTpsGen2_I2C_Pending , 0u                         }}
///         { CddTpsGen2_I2C_Read_Start   ,  CddTpsGen2_I2C_Pending , 0u                         }}
///         { CddTpsGen2_I2C_Read_Start   ,  CddTpsGen2_I2C_Pending , 0u                         }}
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_I2C_HandleReadingStatus(void)
{
  typedef struct tsTestDataIn
  {
    uint8                    ucStatus_in;
    uint8                    I2C_ucReadBytesLeft_in;
    tCddTpsGen2_I2C_eState   I2C_State_in;
    tCddTpsGen2_I2C_eStatus  I2C_ReadStatus_in;
  }tsTestDataIn;
  typedef struct tsTestDataOut
  {
    tCddTpsGen2_I2C_eState   I2C_State_out;
    tCddTpsGen2_I2C_eStatus  I2C_ReadStatus_out;
    uint8                    ucActionFailedClbk_HitCnt_out;
  }tsTestDataOut;
  typedef struct tsTestData
  {
    tsTestDataIn  sInputData;
    tsTestDataOut sOutputData;
  }tsTestData;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  tsTestData const asTestCaseData[] = {
    //  ucStatus_in                , I2C_ucReadBytesLeft_in , I2C_State_in              , I2C_ReadStatus_in        ,  I2C_State_out                ,  I2C_ReadStatus_out     , ucActionFailedClbk_HitCnt_out
    { { CDDTPSGEN2_I2CSTAT_ADRNACK , 15u                    , CddTpsGen2_I2C_Read_Data  , CddTpsGen2_I2C_Pending } , { CddTpsGen2_I2C_ControlReset ,  CddTpsGen2_I2C_Failed  , 1u                         }}, // Test for if (0u != (uint8)(ucStatus & (uint8)CDDTPSGEN2_I2C_RD_STATUS_VALID)) -> TRUE
    { { CDDTPSGEN2_I2CSTAT_SLANACK , 15u                    , CddTpsGen2_I2C_Read_Data  , CddTpsGen2_I2C_Pending } , { CddTpsGen2_I2C_Read_Start   ,  CddTpsGen2_I2C_Pending , 0u                         }}, // Test for else if ((0u != (ucStatus & (uint8)CDDTPSGEN2_I2CSTAT_SLANACK)) || (0u == CddTpsGen2_I2C_ucReadBytesLeft))-> TRUE (0 != (TRUE  || FALSE))
    { { CDDTPSGEN2_I2CSTAT_DATNACK , 0u                     , CddTpsGen2_I2C_Read_Data  , CddTpsGen2_I2C_Pending } , { CddTpsGen2_I2C_Read_Start   ,  CddTpsGen2_I2C_Pending , 0u                         }}, // Test for else if ((0u != (ucStatus & (uint8)CDDTPSGEN2_I2CSTAT_SLANACK)) || (0u == CddTpsGen2_I2C_ucReadBytesLeft))-> TRUE (0 != (FALSE || TRUE ))
    { { CDDTPSGEN2_I2CSTAT_DATNACK , 15u                    , CddTpsGen2_I2C_Read_Start , CddTpsGen2_I2C_Pending } , { CddTpsGen2_I2C_Read_Data    ,  CddTpsGen2_I2C_Pending , 0u                         }}, // Test for if ((CddTpsGen2_I2C_ucReadBytesLeft < 16u) || ((ucStatus & (uint8)CDDTPSGEN2_I2CSTAT_RFF) == (uint8)CDDTPSGEN2_I2CSTAT_RFF)) -> TRUE || FALSE
    { { CDDTPSGEN2_I2CSTAT_RFF     , 16u                    , CddTpsGen2_I2C_Read_Start , CddTpsGen2_I2C_Pending } , { CddTpsGen2_I2C_Read_Data    ,  CddTpsGen2_I2C_Pending , 0u                         }}, // Test for if ((CddTpsGen2_I2C_ucReadBytesLeft < 16u) || ((ucStatus & (uint8)CDDTPSGEN2_I2CSTAT_RFF) == (uint8)CDDTPSGEN2_I2CSTAT_RFF)) -> FALSE || TRUE
    { { CDDTPSGEN2_I2CSTAT_RFE     , 16u                    , CddTpsGen2_I2C_Read_Start , CddTpsGen2_I2C_Pending } , { CddTpsGen2_I2C_Read_Start   ,  CddTpsGen2_I2C_Pending , 0u                         }}, // Test for if ((CddTpsGen2_I2C_ucReadBytesLeft < 16u) || ((ucStatus & (uint8)CDDTPSGEN2_I2CSTAT_RFF) == (uint8)CDDTPSGEN2_I2CSTAT_RFF)) -> FALSE 
    { { 0x81                       , 16u                    , CddTpsGen2_I2C_Read_Start , CddTpsGen2_I2C_Pending } , { CddTpsGen2_I2C_Read_Start   ,  CddTpsGen2_I2C_Pending , 0u                         }}, // Test for if ((ucStatus & ((uint8)CDDTPSGEN2_I2CSTAT_BUSY | (uint8)CDDTPSGEN2_I2CSTAT_RFE)) != ((uint8)CDDTPSGEN2_I2CSTAT_BUSY | (uint8)CDDTPSGEN2_I2CSTAT_RFE)) -> FALSE
  };

  CddTpsGen2_I2C_pfnReadFailedClbk = TestExt_ActionFailedClbk;

  for (uint8 ucIdx = 0u; ucIdx < (sizeof(asTestCaseData) / sizeof(tsTestData)) ; ucIdx++)
  {
    TestExt_ActionFailedClbk_HitCount      = 0u;
    CddTpsGen2_I2C_ucReadBytesLeft                  = asTestCaseData[ucIdx].sInputData.I2C_ucReadBytesLeft_in;
    CddTpsGen2_I2C_State                            = asTestCaseData[ucIdx].sInputData.I2C_State_in;
    CddTpsGen2_I2C_ReadStatus                       = asTestCaseData[ucIdx].sInputData.I2C_ReadStatus_in;

    //Step 3) Call the FUT
    CddTpsGen2_I2C_HandleReadingStatus(asTestCaseData[ucIdx].sInputData.ucStatus_in);

    //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
    AL_UNITTEST_CHECK(CddTpsGen2_I2C_State                                , asTestCaseData[ucIdx].sOutputData.I2C_State_out                            , == );
    AL_UNITTEST_CHECK(CddTpsGen2_I2C_ReadStatus                           , asTestCaseData[ucIdx].sOutputData.I2C_ReadStatus_out                       , == );
    AL_UNITTEST_CHECK(TestExt_ActionFailedClbk_HitCount          , asTestCaseData[ucIdx].sOutputData.ucActionFailedClbk_HitCnt_out            , == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_I2C_HandleReadData
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Check the reading data handler
///
///    - Test Design Technique:  DT (Decision Table)
///
///    - Preconditions: 
/// \input aucTestReadBuffer[20] = { 0x22u, 0xAFu, 0xB5u, 0xC1u, 0x1Eu, 0x77u, 0x88u, 0x9Au, 0xABu, 0xBCu, 0xCDu, 0xDEu, 0xEFu, 0xF1u, 0xF2u, 0xF3u, 0xF4u, 0xF5u, 0xF6u, 0xF7u };
/// \input aucTestReadData[20] = {0};
/// \input const asTestCaseData[] =  I2C_ucCmdReadData_RxLength_in , I2C_ucReadBytesLeft_in , I2C_State_in              , I2C_ReadStatus_in      , I2C_ucPtrReadData_in
///                          { 16u                           , 20u                    , CddTpsGen2_I2C_Read_Data  , CddTpsGen2_I2C_Pending , aucTestReadData }   
///                          { 16u                           , 20u                    , CddTpsGen2_I2C_Read_Data  , CddTpsGen2_I2C_Pending , NULL_PTR        }   
/// \input TestExt_ActionFailedClbk_HitCount = 0u;
/// \input CddTpsGen2_I2C_unReadStartAddress     = 0x1120u;
/// \input CddTpsGen2_I2C_pfnReadFailedClbk      = TestExt_ActionFailedClbk;
/// \input CddTpsGen2_I2C_ucReadTimeoutCounter   = 10u;
/// \input CddTpsGen2_I2C_ucReadTimeoutCounter   = 0u;
///
///    - Expected test results: 
/// \output  I2C_State_out                ,  I2C_ReadStatus_out      , I2C_ucReadBytesLeft_out , I2C_unReadStartAddress_out , ucActionFailedClbk_HitCnt_out, I2C_ucReadTimeoutCounter_out
///         { CddTpsGen2_I2C_Read_Status  ,  CddTpsGen2_I2C_Pending  , 4u                      , 0x1130                     , 0u                           , 0u                          }
///         { CddTpsGen2_I2C_ControlReset ,  CddTpsGen2_I2C_Rejected , 20u                     , 0x1130                     , 1u                           , 1u                          }
/// \output aucTestReadBuffer[3u + ucIdxData]         , aucTestReadData[ucIdxData] -> buffer data = read data when CddTpsGen2_I2C_ucPtrReadData != NULL_PTR
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_I2C_HandleReadData(void)
{
  typedef struct tsTestDataIn
  {
    uint8                    I2C_ucCmdReadData_RxLength_in;
    uint8                    I2C_ucReadBytesLeft_in;
    tCddTpsGen2_I2C_eState   I2C_State_in;
    tCddTpsGen2_I2C_eStatus  I2C_ReadStatus_in;
    uint8*                   I2C_ucPtrReadData_in;
  }tsTestDataIn;
  typedef struct tsTestDataOut
  {
    tCddTpsGen2_I2C_eState   I2C_State_out;
    tCddTpsGen2_I2C_eStatus  I2C_ReadStatus_out;
    uint16                   I2C_ucReadBytesLeft_out;
    uint16                   I2C_unReadStartAddress_out;
    uint8                    ucActionFailedClbk_HitCnt_out;
    uint8                    I2C_ucReadTimeoutCounter_out;
  }tsTestDataOut;
  typedef struct tsTestData
  {
    tsTestDataIn  sInputData;
    tsTestDataOut sOutputData;
  }tsTestData;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  uint8  aucTestReadBuffer[20] = { 0x22u, 0xAFu, 0xB5u, 0xC1u, 0x1Eu, 0x77u, 0x88u, 0x9Au, 0xABu, 0xBCu, 0xCDu, 0xDEu, 0xEFu, 0xF1u, 0xF2u, 0xF3u, 0xF4u, 0xF5u, 0xF6u, 0xF7u };
  uint8  aucTestReadData[20] = {0};
  tsTestData const asTestCaseData[] = {
    //  I2C_ucCmdReadData_RxLength_in , I2C_ucReadBytesLeft_in , I2C_State_in              , I2C_ReadStatus_in      , I2C_ucPtrReadData_in  ,  I2C_State_out                ,  I2C_ReadStatus_out      , I2C_ucReadBytesLeft_out , I2C_unReadStartAddress_out , ucActionFailedClbk_HitCnt_out, I2C_ucReadTimeoutCounter_out
    { { 16u                           , 20u                    , CddTpsGen2_I2C_Read_Data  , CddTpsGen2_I2C_Pending , aucTestReadData }     , { CddTpsGen2_I2C_Read_Status  ,  CddTpsGen2_I2C_Pending  , 4u                      , 0x1130                     , 0u                           , 0u                          }},
    { { 16u                           , 20u                    , CddTpsGen2_I2C_Read_Data  , CddTpsGen2_I2C_Pending , NULL_PTR        }     , { CddTpsGen2_I2C_ControlReset ,  CddTpsGen2_I2C_Rejected , 20u                     , 0x1130                     , 1u                           , 1u                          }},
  };

  CddTpsGen2_I2C_unReadStartAddress     = 0x1120u;
  CddTpsGen2_I2C_pfnReadFailedClbk      = TestExt_ActionFailedClbk;
  CddTpsGen2_I2C_ucReadTimeoutCounter   = 10u;

  for (uint8 ucIdx = 0u; ucIdx < (sizeof(asTestCaseData) / sizeof(tsTestData)) ; ucIdx++)
  {
    TestExt_ActionFailedClbk_HitCount = 0u;
    CddTpsGen2_I2C_ucReadTimeoutCounter   = 0u;
    CddTpsGen2_I2C_ucCmdReadData_RxLength = asTestCaseData[ucIdx].sInputData.I2C_ucCmdReadData_RxLength_in;
    CddTpsGen2_I2C_ucReadBytesLeft        = asTestCaseData[ucIdx].sInputData.I2C_ucReadBytesLeft_in;
    CddTpsGen2_I2C_ucPtrReadData          = asTestCaseData[ucIdx].sInputData.I2C_ucPtrReadData_in;

    //Step 3) Call the FUT
    CddTpsGen2_I2C_HandleReadData(&aucTestReadBuffer[3]);

    //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
    AL_UNITTEST_CHECK(CddTpsGen2_I2C_State                                    , asTestCaseData[ucIdx].sOutputData.I2C_State_out                           , == );
    AL_UNITTEST_CHECK(CddTpsGen2_I2C_ReadStatus                               , asTestCaseData[ucIdx].sOutputData.I2C_ReadStatus_out                      , == );
    AL_UNITTEST_CHECK(CddTpsGen2_I2C_unReadStartAddress                       , asTestCaseData[ucIdx].sOutputData.I2C_unReadStartAddress_out              , == );
    AL_UNITTEST_CHECK(CddTpsGen2_I2C_ucReadBytesLeft                          , asTestCaseData[ucIdx].sOutputData.I2C_ucReadBytesLeft_out                 , == );
    AL_UNITTEST_CHECK(TestExt_ActionFailedClbk_HitCount              , asTestCaseData[ucIdx].sOutputData.ucActionFailedClbk_HitCnt_out           , == );
    if(asTestCaseData[ucIdx].sInputData.I2C_ucPtrReadData_in != NULL_PTR)
    {
      for (uint8 ucIdxData = 0u; ucIdxData < asTestCaseData[ucIdx].sInputData.I2C_ucCmdReadData_RxLength_in; ucIdxData++)
      {// Start from the address given to FOT
        AL_UNITTEST_CHECK(aucTestReadBuffer[3u + ucIdxData]         , aucTestReadData[ucIdxData]                        , == );
      }
    }
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_I2C_CommandWriteData
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Check the write data command
///
///    - Test Design Technique:  DT (Decision Table)
///
///    - Preconditions: 
/// \input aucTestWriteData[20] = {0u , 0xAAu, 0xEAu, 0xBFu};
/// \input const asTestCaseData[] =    I2C_State_in                , I2C_WriteStatus_in        , I2C_ucPtrWriteData_in  
///                            { CddTpsGen2_I2C_Idle         , CddTpsGen2_I2C_Pending    , &aucTestWriteData[2]  }
///                            { CddTpsGen2_I2C_Idle         , CddTpsGen2_I2C_Pending    , NULL_PTR              }
/// \input TestExt_ActionFailedClbk_HitCount = 0u;
/// \input CddTpsGen2_DataMirrorEE.CtrlTx.TxI2CDAT.ucRaw   = 0u;
/// \input CddTpsGen2_I2C_pfnWriteFailedClbk               = TestExt_ActionFailedClbk;
///
///    - Expected test results: 
/// \output   I2C_State_out               , I2C_WriteStatus_out      , TxI2CDAT_raw_out      , ucActionFailedClbk_HitCnt_out
///         { CddTpsGen2_I2C_Idle         , CddTpsGen2_I2C_Pending  , 0xEAu                 , 0u                           }
///         { CddTpsGen2_I2C_ControlReset , CddTpsGen2_I2C_Failed   , 0x00u                 , 1u                           }
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_I2C_CommandWriteData(void)
{
  typedef struct tsTestDataIn
  {
    tCddTpsGen2_I2C_eState   I2C_State_in;
    tCddTpsGen2_I2C_eStatus  I2C_WriteStatus_in;
    uint8*                   I2C_ucPtrWriteData_in;
  }tsTestDataIn;
  typedef struct tsTestDataOut
  {
    tCddTpsGen2_I2C_eState   I2C_State_out;
    tCddTpsGen2_I2C_eStatus  I2C_WriteStatus_out;
    uint8                    TxI2CDAT_raw_out;
    uint8                    ucActionFailedClbk_HitCnt_out;
  }tsTestDataOut;
  typedef struct tsTestData
  {
    tsTestDataIn  sInputData;
    tsTestDataOut sOutputData;
  }tsTestData;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  uint8  aucTestWriteData[20] = {0u , 0xAAu, 0xEAu, 0xBFu};
  tsTestData const asTestCaseData[] = {
    //  I2C_State_in                , I2C_WriteStatus_in        , I2C_ucPtrWriteData_in   ,   I2C_State_out               , I2C_WriteStatus_out      , TxI2CDAT_raw_out      , ucActionFailedClbk_HitCnt_out
    { { CddTpsGen2_I2C_Idle         , CddTpsGen2_I2C_Pending    , &aucTestWriteData[2]  } , { CddTpsGen2_I2C_Idle         , CddTpsGen2_I2C_Pending  , 0xEAu                 , 0u                           }},
    { { CddTpsGen2_I2C_Idle         , CddTpsGen2_I2C_Pending    , NULL_PTR              } , { CddTpsGen2_I2C_ControlReset , CddTpsGen2_I2C_Failed   , 0x00u                 , 1u                           }},
  };

  CddTpsGen2_I2C_pfnWriteFailedClbk   = TestExt_ActionFailedClbk;

  for (uint8 ucIdx = 0u; ucIdx < (sizeof(asTestCaseData) / sizeof(tsTestData)) ; ucIdx++)
  {
    TestExt_ActionFailedClbk_HitCount    = 0u;
    CddTpsGen2_DataMirrorEE.CtrlTx.TxI2CDAT.ucRaw = 0u;
    CddTpsGen2_I2C_State          = asTestCaseData[ucIdx].sInputData.I2C_State_in;
    CddTpsGen2_I2C_WriteStatus    = asTestCaseData[ucIdx].sInputData.I2C_WriteStatus_in;
    CddTpsGen2_I2C_ucPtrWriteData = asTestCaseData[ucIdx].sInputData.I2C_ucPtrWriteData_in;

    //Step 3) Call the FUT
    CddTpsGen2_I2C_CommandWriteData();

    //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
    AL_UNITTEST_CHECK(CddTpsGen2_I2C_State                                          , asTestCaseData[ucIdx].sOutputData.I2C_State_out                                   , == );
    AL_UNITTEST_CHECK(CddTpsGen2_I2C_WriteStatus                                    , asTestCaseData[ucIdx].sOutputData.I2C_WriteStatus_out                             , == );
    AL_UNITTEST_CHECK(CddTpsGen2_DataMirrorEE.CtrlTx.TxI2CDAT.ucRaw                 , asTestCaseData[ucIdx].sOutputData.TxI2CDAT_raw_out                                , == );
    AL_UNITTEST_CHECK(TestExt_ActionFailedClbk_HitCount                    , asTestCaseData[ucIdx].sOutputData.ucActionFailedClbk_HitCnt_out                   , == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_I2C_HandleWriteData
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Check response of the I2C Write Data Command
///
///    - Test Design Technique:  DT (Decision Table)
///
///    - Preconditions: 
/// \input const asTestCaseData[] =   I2C_State_in             , ucAck_in            
///                           { CddTpsGen2_I2C_Idle      , CDDTPSGEN2_ACK_BYTE 
///                           { CddTpsGen2_I2C_Idle      , 0x7Eu               
///
///    - Expected test results: 
/// \output   I2C_State_out               , ucAck_out
///         { CddTpsGen2_I2C_Write_Start  , 0x00u   }
///         { CddTpsGen2_I2C_Idle         , 0x7Eu   }
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_I2C_HandleWriteData(void)
{
  typedef struct tsTestDataIn
  {
    tCddTpsGen2_I2C_eState   I2C_State_in;
    uint8                    ucAck_in;
  }tsTestDataIn;
  typedef struct tsTestDataOut
  {
    tCddTpsGen2_I2C_eState   I2C_State_out;
    uint8                    ucAck_out;
  }tsTestDataOut;
  typedef struct tsTestData
  {
    tsTestDataIn  sInputData;
    tsTestDataOut sOutputData;
  }tsTestData;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  tsTestData const asTestCaseData[] = {
    //  I2C_State_in             , ucAck_in               ,   I2C_State_out               , ucAck_out 
    { { CddTpsGen2_I2C_Idle      , CDDTPSGEN2_ACK_BYTE  } , { CddTpsGen2_I2C_Write_Start  , 0x00u   }},
    { { CddTpsGen2_I2C_Idle      , 0x7Eu                } , { CddTpsGen2_I2C_Idle         , 0x7Eu   }},
  };

  for (uint8 ucIdx = 0u; ucIdx < (sizeof(asTestCaseData) / sizeof(tsTestData)) ; ucIdx++)
  {
    CddTpsGen2_I2C_State          = asTestCaseData[ucIdx].sInputData.I2C_State_in;

    //Step 3) Call the FUT
    CddTpsGen2_I2C_HandleWriteData(&asTestCaseData[ucIdx].sInputData.ucAck_in);

    //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
    AL_UNITTEST_CHECK(CddTpsGen2_I2C_State                                          , asTestCaseData[ucIdx].sOutputData.I2C_State_out                                   , == );
    AL_UNITTEST_CHECK(asTestCaseData[ucIdx].sInputData.ucAck_in                     , asTestCaseData[ucIdx].sOutputData.ucAck_out                                , == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_I2C_CheckEEActivation
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Check the selection of the scheduler
///
///    - Test Design Technique:  DT (Decision Table)
///
///    - Preconditions: 
/// \input const asTestCaseData[] =  //  I2C_State_in                  , ucGoToSt_in            
///                            { { CddTpsGen2_I2C_Preinit        , CDDTPSGEN2_ACK_BYTE  } 
///                            { { CddTpsGen2_I2C_Init           , CDDTPSGEN2_ACK_BYTE  } 
///                            { { CddTpsGen2_I2C_Read_Start     , CDDTPSGEN2_ACK_BYTE  } 
///                            { { CddTpsGen2_I2C_Read_Status    , CDDTPSGEN2_ACK_BYTE  } 
///                            { { CddTpsGen2_I2C_Read_Data      , CDDTPSGEN2_ACK_BYTE  } 
///                            { { CddTpsGen2_I2C_Write_Data     , CDDTPSGEN2_ACK_BYTE  } 
///                            { { CddTpsGen2_I2C_Write_Start    , CDDTPSGEN2_ACK_BYTE  } 
///                            { { CddTpsGen2_I2C_Write_Status   , CDDTPSGEN2_ACK_BYTE  } 
///                            { { CddTpsGen2_I2C_ControlReset   , CDDTPSGEN2_ACK_BYTE  } 
///                            { { CddTpsGen2_I2C_NotInit        , CDDTPSGEN2_ACK_BYTE  } 
/// \input CddTpsGen2_I2C_unReadEndAddress   = 0x55332211;
/// \input CddTpsGen2_I2C_unReadStartAddress = 0x55332200;
///
///    - Expected test results: 
/// \output   I2C_State_out               , ucGoToSt_out                       , boRetVal_out
///         { CddTpsGen2_I2C_Preinit      , CDDTPSGEN2_STATE_EE_PREINIT        , TRUE                }},
///         { CddTpsGen2_I2C_Init         , CDDTPSGEN2_STATE_EE_INIT           , TRUE                }},
///         { CddTpsGen2_I2C_Read_Start   , CDDTPSGEN2_STATE_EE_READ_START     , TRUE                }},
///         { CddTpsGen2_I2C_Read_Status  , CDDTPSGEN2_STATE_EE_RR_STATUS      , TRUE                }},
///         { CddTpsGen2_I2C_Read_Data    , CDDTPSGEN2_STATE_EE_READ_16_BYTES  , TRUE                }},
///         { CddTpsGen2_I2C_ControlReset , CDDTPSGEN2_STATE_EE_WRITE_DATA     , TRUE                }},
///         { CddTpsGen2_I2C_Write_Start  , CDDTPSGEN2_STATE_EE_WRITE_START    , TRUE                }},
///         { CddTpsGen2_I2C_Write_Status , CDDTPSGEN2_STATE_EE_RW_STATUS      , TRUE                }},
///         { CddTpsGen2_I2C_ControlReset , CDDTPSGEN2_STATE_EE_RESET          , TRUE                }},
///         { CddTpsGen2_I2C_NotInit      , CDDTPSGEN2_ACK_BYTE                , FALSE               }}, //default
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_I2C_CheckEEActivation(void)
{
  typedef struct tsTestDataIn
  {
    tCddTpsGen2_I2C_eState   I2C_State_in;
    uint8                    ucGoToSt_in;
  }tsTestDataIn;
  typedef struct tsTestDataOut
  {
    tCddTpsGen2_I2C_eState   I2C_State_out;
    uint8                    ucGoToSt_out;
    boolean                  boRetVal_out;
  }tsTestDataOut;
  typedef struct tsTestData
  {
    tsTestDataIn  sInputData;
    tsTestDataOut sOutputData;
  }tsTestData;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  tsTestData const asTestCaseData[] = {
    //  I2C_State_in                  , ucGoToSt_in            ,   I2C_State_out               , ucGoToSt_out                       , boRetVal_out
    { { CddTpsGen2_I2C_Preinit        , CDDTPSGEN2_ACK_BYTE  } , { CddTpsGen2_I2C_Preinit      , CDDTPSGEN2_STATE_EE_PREINIT        , TRUE                }},
    { { CddTpsGen2_I2C_Init           , CDDTPSGEN2_ACK_BYTE  } , { CddTpsGen2_I2C_Init         , CDDTPSGEN2_STATE_EE_INIT           , TRUE                }},
    { { CddTpsGen2_I2C_Read_Start     , CDDTPSGEN2_ACK_BYTE  } , { CddTpsGen2_I2C_Read_Start   , CDDTPSGEN2_STATE_EE_READ_START     , TRUE                }},
    { { CddTpsGen2_I2C_Read_Status    , CDDTPSGEN2_ACK_BYTE  } , { CddTpsGen2_I2C_Read_Status  , CDDTPSGEN2_STATE_EE_RR_STATUS      , TRUE                }},
    { { CddTpsGen2_I2C_Read_Data      , CDDTPSGEN2_ACK_BYTE  } , { CddTpsGen2_I2C_Read_Data    , CDDTPSGEN2_STATE_EE_READ_16_BYTES  , TRUE                }},
    { { CddTpsGen2_I2C_Write_Data     , CDDTPSGEN2_ACK_BYTE  } , { CddTpsGen2_I2C_ControlReset , CDDTPSGEN2_STATE_EE_WRITE_DATA     , TRUE                }},
    { { CddTpsGen2_I2C_Write_Start    , CDDTPSGEN2_ACK_BYTE  } , { CddTpsGen2_I2C_Write_Start  , CDDTPSGEN2_STATE_EE_WRITE_START    , TRUE                }},
    { { CddTpsGen2_I2C_Write_Status   , CDDTPSGEN2_ACK_BYTE  } , { CddTpsGen2_I2C_Write_Status , CDDTPSGEN2_STATE_EE_RW_STATUS      , TRUE                }},
    { { CddTpsGen2_I2C_ControlReset   , CDDTPSGEN2_ACK_BYTE  } , { CddTpsGen2_I2C_ControlReset , CDDTPSGEN2_STATE_EE_RESET          , TRUE                }},
    { { CddTpsGen2_I2C_NotInit        , CDDTPSGEN2_ACK_BYTE  } , { CddTpsGen2_I2C_NotInit      , CDDTPSGEN2_ACK_BYTE                , FALSE               }}, //default
  };
  // input for CddTpsGen2_I2C_Read_Start and CddTpsGen2_I2C_Read_Data
  CddTpsGen2_I2C_unReadEndAddress   = 0x55332211;
  CddTpsGen2_I2C_unReadStartAddress = 0x55332200;

  for (uint8 ucIdx = 0u; ucIdx < (sizeof(asTestCaseData) / sizeof(tsTestData)) ; ucIdx++)
  {
    boolean boRetVal_in;
    CddTpsGen2_I2C_State = asTestCaseData[ucIdx].sInputData.I2C_State_in;

    //Step 3) Call the FUT
    boRetVal_in = CddTpsGen2_I2C_CheckEEActivation(&asTestCaseData[ucIdx].sInputData.ucGoToSt_in);

    //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
    AL_UNITTEST_CHECK(CddTpsGen2_I2C_State                                       , asTestCaseData[ucIdx].sOutputData.I2C_State_out     , == );
    AL_UNITTEST_CHECK(asTestCaseData[ucIdx].sInputData.ucGoToSt_in               , asTestCaseData[ucIdx].sOutputData.ucGoToSt_out      , == );
    AL_UNITTEST_CHECK(boRetVal_in                                                , asTestCaseData[ucIdx].sOutputData.boRetVal_out      , == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_I2C_Timeout_TestCase1
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Check the timeout function for init and preinit cases
///         and for when chip eeprom address is 0xFFu
///
///    - Test Design Technique:  DT (Decision Table)
///
///    - Preconditions: 
/// \input const asTestCaseData[] =   I2C_State_in           , I2C_InitStatus_in      , ucEepromAddr_in , I2C_ucInitTimeoutCounter_in  
///                           { CddTpsGen2_I2C_Preinit , CddTpsGen2_I2C_Pending , 0xFEu           , 10u                         }
///                           { CddTpsGen2_I2C_Init    , CddTpsGen2_I2C_Pending , 0xFEu           , 11u                         }
///                           { CddTpsGen2_I2C_Init    , CddTpsGen2_I2C_Pending , 0xFFu           , 11u                         }
/// 
/// \input CddTpsGen2_I2C_pfnInitFailedClbk           = &TestExt_ActionFailedClbk;
/// \input TestExt_ActionFailedClbk_HitCount = 0u;
///
///    - Expected test results: 
/// \output   I2C_State_out          , I2C_InitStatus_out     , I2C_ucInitTimeoutCounter_out , ucFailedClbk_HitCount
///         { CddTpsGen2_I2C_Preinit , CddTpsGen2_I2C_Pending , 11u                          , 0u                   }
///         { CddTpsGen2_I2C_NotInit , CddTpsGen2_I2C_Failed  , 11u                          , 1u                   }
///         { CddTpsGen2_I2C_Init    , CddTpsGen2_I2C_Pending , 11u                          , 0u                   }
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_I2C_Timeout_TestCase1(void)
{
  typedef struct tsTestDataIn
  {
    tCddTpsGen2_I2C_eState   I2C_State_in;
    tCddTpsGen2_I2C_eStatus  I2C_InitStatus_in;
    uint8                    ucEepromAddr_in;
    uint8                    I2C_ucInitTimeoutCounter_in;
  }tsTestDataIn;
  typedef struct tsTestDataOut
  {
    tCddTpsGen2_I2C_eState   I2C_State_out;
    tCddTpsGen2_I2C_eStatus  I2C_InitStatus_out;
    uint8                    I2C_ucInitTimeoutCounter_out;
    uint8                    ucFailedClbk_HitCount;
  }tsTestDataOut;
  typedef struct tsTestData
  {
    tsTestDataIn  sInputData;
    tsTestDataOut sOutputData;
  }tsTestData;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  tsTestData const asTestCaseData[] = {
    //  I2C_State_in           , I2C_InitStatus_in      , ucEepromAddr_in , I2C_ucInitTimeoutCounter_in   ,   I2C_State_out          , I2C_InitStatus_out     , I2C_ucInitTimeoutCounter_out , ucFailedClbk_HitCount
    { { CddTpsGen2_I2C_Preinit , CddTpsGen2_I2C_Pending , 0xFEu           , 10u                         } , { CddTpsGen2_I2C_Preinit , CddTpsGen2_I2C_Pending , 11u                          , 0u                   }},
    { { CddTpsGen2_I2C_Init    , CddTpsGen2_I2C_Pending , 0xFEu           , 11u                         } , { CddTpsGen2_I2C_NotInit , CddTpsGen2_I2C_Failed  , 11u                          , 1u                   }},
    { { CddTpsGen2_I2C_Init    , CddTpsGen2_I2C_Pending , 0xFFu           , 11u                         } , { CddTpsGen2_I2C_Init    , CddTpsGen2_I2C_Pending , 11u                          , 0u                   }},
  };
  CddTpsGen2_I2C_pfnInitFailedClbk = &TestExt_ActionFailedClbk;

  for (uint8 ucIdx = 0u; ucIdx < (sizeof(asTestCaseData) / sizeof(tsTestData)); ucIdx++)
  {
    CddTpsGen2_I2C_State                       = asTestCaseData[ucIdx].sInputData.I2C_State_in;
    CddTpsGen2_I2C_InitStatus                  = asTestCaseData[ucIdx].sInputData.I2C_InitStatus_in;
    CDDTPSGEN2_Para_CHIP_EEPROM_ADDR           = asTestCaseData[ucIdx].sInputData.ucEepromAddr_in;
    CddTpsGen2_I2C_ucInitTimeoutCounter        = asTestCaseData[ucIdx].sInputData.I2C_ucInitTimeoutCounter_in;
    TestExt_ActionFailedClbk_HitCount = 0u;


    //Step 3) Call the FUT
    CddTpsGen2_I2C_Timeout();

    //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
    AL_UNITTEST_CHECK(CddTpsGen2_I2C_State                             , asTestCaseData[ucIdx].sOutputData.I2C_State_out                       , == );
    AL_UNITTEST_CHECK(CddTpsGen2_I2C_InitStatus                        , asTestCaseData[ucIdx].sOutputData.I2C_InitStatus_out                  , == );
    AL_UNITTEST_CHECK(CddTpsGen2_I2C_ucInitTimeoutCounter              , asTestCaseData[ucIdx].sOutputData.I2C_ucInitTimeoutCounter_out        , == );
    AL_UNITTEST_CHECK(TestExt_ActionFailedClbk_HitCount       , asTestCaseData[ucIdx].sOutputData.ucFailedClbk_HitCount               , == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_I2C_Timeout_TestCase2
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Check the timeout function for read cases
///
///    - Test Design Technique:  DT (Decision Table)
///
///    - Preconditions: 
/// \input const asTestCaseData[] =   I2C_State_in           , I2C_InitStatus_in      , ucEepromAddr_in , I2C_ucInitTimeoutCounter_in  
///                           { CddTpsGen2_I2C_Preinit , CddTpsGen2_I2C_Pending , 0xFEu           , 10u                         }
///                           { CddTpsGen2_I2C_Init    , CddTpsGen2_I2C_Pending , 0xFEu           , 11u                         }
///                           { CddTpsGen2_I2C_Init    , CddTpsGen2_I2C_Pending , 0xFFu           , 11u                         }
/// 
/// \input CddTpsGen2_I2C_pfnInitFailedClbk          = &TestExt_ActionFailedClbk;
/// \input TestExt_ActionFailedClbk_HitCount  = 0u;
///
///    - Expected test results: 
/// \output   I2C_State_out          , I2C_InitStatus_out     , I2C_ucInitTimeoutCounter_out , ucFailedClbk_HitCount
///         { CddTpsGen2_I2C_Preinit , CddTpsGen2_I2C_Pending , 11u                          , 0u                   }
///         { CddTpsGen2_I2C_NotInit , CddTpsGen2_I2C_Failed  , 11u                          , 1u                   }
///         { CddTpsGen2_I2C_Init    , CddTpsGen2_I2C_Pending , 11u                          , 0u                   }
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_I2C_Timeout_TestCase2(void)
{
  typedef struct tsTestDataIn
  {
    tCddTpsGen2_I2C_eState   I2C_State_in;
    tCddTpsGen2_I2C_eStatus  I2C_Status_in;
    uint8                    ucEepromAddr_in;
    uint8                    I2C_ucTimeoutCounter_in;
  }tsTestDataIn;
  typedef struct tsTestDataOut
  {
    tCddTpsGen2_I2C_eState   I2C_State_out;
    tCddTpsGen2_I2C_eStatus  I2C_Status_out;
    uint8                    I2C_ucTimeoutCounter_out;
    uint8                    ucFailedClbk_HitCount;
  }tsTestDataOut;
  typedef struct tsTestData
  {
    tsTestDataIn  sInputData;
    tsTestDataOut sOutputData;
  }tsTestData;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  tsTestData const asTestCaseData[] = {
    //  I2C_State_in               , I2C_ReadStatus_in      , ucEepromAddr_in , I2C_ucInitTimeoutCounter_in   ,   I2C_State_out               , I2C_Status_out         , I2C_ucTimeoutCounter_out , ucFailedClbk_HitCount
    { { CddTpsGen2_I2C_Read_Start  , CddTpsGen2_I2C_Pending , 0xFEu           , 10u                         } , { CddTpsGen2_I2C_Read_Start   , CddTpsGen2_I2C_Pending , 11u                      , 0u                   }},
    { { CddTpsGen2_I2C_Read_Status , CddTpsGen2_I2C_Pending , 0xFEu           , 19u                         } , { CddTpsGen2_I2C_Read_Status  , CddTpsGen2_I2C_Pending , 20u                      , 0u                   }},
    { { CddTpsGen2_I2C_Read_Data   , CddTpsGen2_I2C_Pending , 0xFEu           , 20u                         } , { CddTpsGen2_I2C_ControlReset , CddTpsGen2_I2C_Failed  , 20u                      , 1u                   }},
  };
  CddTpsGen2_I2C_pfnInitFailedClbk = &TestExt_ActionFailedClbk;

  for (uint8 ucIdx = 0u; ucIdx < (sizeof(asTestCaseData) / sizeof(tsTestData)); ucIdx++)
  {
    CddTpsGen2_I2C_State                       = asTestCaseData[ucIdx].sInputData.I2C_State_in;
    CddTpsGen2_I2C_ReadStatus                  = asTestCaseData[ucIdx].sInputData.I2C_Status_in;
    CDDTPSGEN2_Para_CHIP_EEPROM_ADDR           = asTestCaseData[ucIdx].sInputData.ucEepromAddr_in;
    CddTpsGen2_I2C_ucReadTimeoutCounter        = asTestCaseData[ucIdx].sInputData.I2C_ucTimeoutCounter_in;
    TestExt_ActionFailedClbk_HitCount = 0u;

    //Step 3) Call the FUT
    CddTpsGen2_I2C_Timeout();

    //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
    AL_UNITTEST_CHECK(CddTpsGen2_I2C_State                             , asTestCaseData[ucIdx].sOutputData.I2C_State_out                       , == );
    AL_UNITTEST_CHECK(CddTpsGen2_I2C_ReadStatus                        , asTestCaseData[ucIdx].sOutputData.I2C_Status_out                      , == );
    AL_UNITTEST_CHECK(CddTpsGen2_I2C_ucReadTimeoutCounter              , asTestCaseData[ucIdx].sOutputData.I2C_ucTimeoutCounter_out            , == );
    AL_UNITTEST_CHECK(TestExt_ActionFailedClbk_HitCount       , asTestCaseData[ucIdx].sOutputData.ucFailedClbk_HitCount               , == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_I2C_Timeout_TestCase3
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Check the timeout function for write cases
///         and default
///
///    - Test Design Technique:  DT (Decision Table)
///
///    - Preconditions: 
/// \input const asTestCaseData[] =   I2C_State_in                , I2C_ReadStatus_in      , ucEepromAddr_in , I2C_ucInitTimeoutCounter_in  
///                           { CddTpsGen2_I2C_Write_Data   , CddTpsGen2_I2C_Pending , 0xFEu           , 0u                          }
///                           { CddTpsGen2_I2C_Write_Start  , CddTpsGen2_I2C_Pending , 0xFEu           , 9u                          }
///                           { CddTpsGen2_I2C_Write_Status , CddTpsGen2_I2C_Pending , 0xFEu           , 10u                         }
///                           { CddTpsGen2_I2C_NotInit      , CddTpsGen2_I2C_Pending , 0xFEu           , 8u                          }
/// 
/// \input CddTpsGen2_I2C_pfnInitFailedClbk          = &TestExt_ActionFailedClbk;
/// \input TestExt_ActionFailedClbk_HitCount  = 0u;
///
///    - Expected test results: 
/// \output   I2C_State_out               , I2C_Status_out         , I2C_ucTimeoutCounter_out , ucFailedClbk_HitCount
///         { CddTpsGen2_I2C_Write_Data   , CddTpsGen2_I2C_Pending , 1u                       , 0u                   }
///         { CddTpsGen2_I2C_Write_Start  , CddTpsGen2_I2C_Pending , 10u                      , 0u                   }
///         { CddTpsGen2_I2C_ControlReset , CddTpsGen2_I2C_Failed  , 10u                      , 1u                   }
///         { CddTpsGen2_I2C_NotInit      , CddTpsGen2_I2C_Pending , 8u                       , 0u                   }
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_I2C_Timeout_TestCase3(void)
{
  typedef struct tsTestDataIn
  {
    tCddTpsGen2_I2C_eState   I2C_State_in;
    tCddTpsGen2_I2C_eStatus  I2C_Status_in;
    uint8                    ucEepromAddr_in;
    uint8                    I2C_ucTimeoutCounter_in;
  }tsTestDataIn;
  typedef struct tsTestDataOut
  {
    tCddTpsGen2_I2C_eState   I2C_State_out;
    tCddTpsGen2_I2C_eStatus  I2C_Status_out;
    uint8                    I2C_ucTimeoutCounter_out;
    uint8                    ucFailedClbk_HitCount;
  }tsTestDataOut;
  typedef struct tsTestData
  {
    tsTestDataIn  sInputData;
    tsTestDataOut sOutputData;
  }tsTestData;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  tsTestData const asTestCaseData[] = {
    //  I2C_State_in                , I2C_ReadStatus_in      , ucEepromAddr_in , I2C_ucInitTimeoutCounter_in   ,   I2C_State_out               , I2C_Status_out         , I2C_ucTimeoutCounter_out , ucFailedClbk_HitCount
    { { CddTpsGen2_I2C_Write_Data   , CddTpsGen2_I2C_Pending , 0xFEu           , 0u                          } , { CddTpsGen2_I2C_Write_Data   , CddTpsGen2_I2C_Pending , 1u                       , 0u                   }},
    { { CddTpsGen2_I2C_Write_Start  , CddTpsGen2_I2C_Pending , 0xFEu           , 9u                          } , { CddTpsGen2_I2C_Write_Start  , CddTpsGen2_I2C_Pending , 10u                      , 0u                   }},
    { { CddTpsGen2_I2C_Write_Status , CddTpsGen2_I2C_Pending , 0xFEu           , 10u                         } , { CddTpsGen2_I2C_ControlReset , CddTpsGen2_I2C_Failed  , 10u                      , 1u                   }},
    { { CddTpsGen2_I2C_NotInit      , CddTpsGen2_I2C_Pending , 0xFEu           , 8u                          } , { CddTpsGen2_I2C_NotInit      , CddTpsGen2_I2C_Pending , 8u                       , 0u                   }},
  };
  CddTpsGen2_I2C_pfnInitFailedClbk = &TestExt_ActionFailedClbk;

  for (uint8 ucIdx = 0u; ucIdx < (sizeof(asTestCaseData) / sizeof(tsTestData)); ucIdx++)
  {
    CddTpsGen2_I2C_State                       = asTestCaseData[ucIdx].sInputData.I2C_State_in;
    CddTpsGen2_I2C_WriteStatus                 = asTestCaseData[ucIdx].sInputData.I2C_Status_in;
    CDDTPSGEN2_Para_CHIP_EEPROM_ADDR           = asTestCaseData[ucIdx].sInputData.ucEepromAddr_in;
    CddTpsGen2_I2C_ucWriteTimeoutCounter       = asTestCaseData[ucIdx].sInputData.I2C_ucTimeoutCounter_in;
    TestExt_ActionFailedClbk_HitCount = 0u;

    //Step 3) Call the FUT
    CddTpsGen2_I2C_Timeout();

    //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
    AL_UNITTEST_CHECK(CddTpsGen2_I2C_State                             , asTestCaseData[ucIdx].sOutputData.I2C_State_out                       , == );
    AL_UNITTEST_CHECK(CddTpsGen2_I2C_WriteStatus                       , asTestCaseData[ucIdx].sOutputData.I2C_Status_out                      , == );
    AL_UNITTEST_CHECK(CddTpsGen2_I2C_ucWriteTimeoutCounter             , asTestCaseData[ucIdx].sOutputData.I2C_ucTimeoutCounter_out            , == );
    AL_UNITTEST_CHECK(TestExt_ActionFailedClbk_HitCount       , asTestCaseData[ucIdx].sOutputData.ucFailedClbk_HitCount               , == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTpsGen2_I2C_Timeout
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test Mt_CddTpsGen2_I2C_Timeout function
///
///    - Test Design Technique: DT (Decision Table)
///
/// \Expected Test Results : All contained test cases are passed
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_I2C_Timeout(void)
{
  Mt_CddTpsGen2_I2C_Timeout_TestCase1();
  Mt_CddTpsGen2_I2C_Timeout_TestCase2();
  Mt_CddTpsGen2_I2C_Timeout_TestCase3();
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_GetEEConnectedId
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Check if function returns the ID of the MLC 
///         connected EEPROM device correctly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
/// \input ucRetVal = 0u;
/// \input CddTpsGen2_sDevData.ucEepromId = 0x23u;
///
///    - Expected test results: 
/// \output  ucRetVal  == 0x23u
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_GetEEConnectedId(void)
{

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  uint8 ucRetVal = 0u;
  CddTpsGen2_sDevData.ucEepromId = 0x23u;

  //Step 3) Call the FUT
  ucRetVal = CddTpsGen2_GetEEConnectedId();

  //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
  AL_UNITTEST_CHECK(ucRetVal           , 0x23u        , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_I2C_HandleReset
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Check if functions sets the EE state machine to idle state
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
/// \input ucAck_retVal    = 0u;
/// \input CddTpsGen2_I2C_State  = CddTpsGen2_I2C_Write_Data;
///
///    - Expected test results: 
/// \output ucAck_retVal          = 0u                   
/// \output CddTpsGen2_I2C_State  = CddTpsGen2_I2C_Idle   
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_I2C_HandleReset(void)
{

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  uint8 ucAck_retVal    = 0u;
  CddTpsGen2_I2C_State  = CddTpsGen2_I2C_Write_Data;

  //Step 3) Call the FUT
  CddTpsGen2_I2C_HandleReset(&ucAck_retVal);

  //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
  AL_UNITTEST_CHECK(ucAck_retVal           , 0u                        , == );
  AL_UNITTEST_CHECK(CddTpsGen2_I2C_State   , CddTpsGen2_I2C_Idle        , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_GetPixelFault
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Check if electrical fault is stored properly
///
///    - Test Design Technique:  DT (Decision Table)
///
///    - Preconditions: 
/// \input CddTpsGen2_DataMirror.StatRx.RxELEFAULT[ucIdx].ucRxByte[0U] = asTestData[ucIdx].ucRxByte0_in;
/// \input asTestData[8u] = {// ucRxByte0_in     ucRxByte1_in     unExpRet
///                           { 0x2u            , 0x0u            , 0x2u    },
///                           { 0xFFu           , 0xFFu           , 0xFFFu  },
///                           { 0x0u            , 0xEu            , 0xE00u  },
///                           { 0x2u            , 0x0u            , 0x2u    },
///                           { 0x2u            , 0x2u            , 0x202u  },
///                           { 0xEEu           , 0xABu           , 0xBEEu  },
///                           { 0x0u            , 0x4u            , 0x400u  },
///                           { 0xFFu           , 0xFFu           , 0x0u    }, // CHIP ID OUT OF RANGE 
///
///    - Expected test results: 
/// \output  asTestData[unIdx].unExpRet
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_GetPixelFault(void)
{
  typedef struct tsTestData
  {
    uint8  ucRxByte0_in;
    uint8  ucRxByte1_in;
    uint16 unExpRet;
  }tsTestData;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  tsTestData asTestData[8u] = {// ucRxByte0_in     ucRxByte1_in     unExpRet
                                { 0x2u            , 0x0u            , 0x2u    },
                                { 0xFFu           , 0xFFu           , 0xFFFu  },
                                { 0x0u            , 0xEu            , 0xE00u  },
                                { 0x2u            , 0x0u            , 0x2u    },
                                { 0x2u            , 0x2u            , 0x202u  },
                                { 0xEEu           , 0xABu           , 0xBEEu  },
                                { 0x0u            , 0x4u            , 0x400u  },
                                { 0xFFu           , 0xFFu           , 0x0u    }, // CHIP ID OUT OF RANGE 
  };
  /* index must go above CFG_MLC_Chip_Cnt in order to test out of range */
  for (uint8 ucIdx = 0u; ucIdx < 8u; ucIdx++)
  {
    uint16 unRet = 0u;
    CddTpsGen2_DataMirror.StatRx.RxELEFAULT[ucIdx].ucRxByte[0U] = asTestData[ucIdx].ucRxByte0_in;
    CddTpsGen2_DataMirror.StatRx.RxELEFAULT[ucIdx].ucRxByte[1U] = asTestData[ucIdx].ucRxByte1_in;

    //Step 3) Call the FUT
    unRet = CddTpsGen2_GetPixelFault(ucIdx);

    //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
    AL_UNITTEST_CHECK(unRet           , asTestData[ucIdx].unExpRet        , == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTpsGen2_SetDutyCycle_1_1024_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if MWIDTH registers are updated correctly
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions:
/// 
/// \input ucChipId = 0 -> 7;
/// \input punDuty_In[CDDTPSGEN2_TPS92662A_MAX_SWITCHS_PER_DEVICE] = { 0x100u, 0x4u, 0x5u, 0x20Au, (0x32u+ ucChipId), 0x364u, 0x64u, 0x1u, (0x206u+ ucChipId), 0x4u, 0x3u, 0x33u };
///
/// - Expectations:
///
/// \output aucTestDataOut[16u] = {//MWIDTH01/4/7/10      MWIDTH02/5/8/11     MWIDTH03/6/9/12       MWIDTH0x_0xH
///                                  0u                  , 0u                , 5u                  , 1u  , // results of 0x100u, 0x4u, 0x5u
///                                  10u                 , (50u+ ucChipId)   , 100u                , 50u , // results of 0x20Au, (0x32u+ ucChipId), 0x364u
///                                  100u                , 0u                , (6u+ ucChipId)      , 32u , // results of 0x64u, 0x1u, (0x206u+ ucChipId)
///                                  0u                  , 0u                , 51u                 , 0u    // results of 0x4u, 0x3u, 0x33u
///         
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_SetDutyCycle_1_1024_TestCase1(void)
{
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  for (uint8 ucChipId = 0u; ucChipId < 7; ucChipId++)
  {
    //uint8_fast ucChipId = 1u;
    uint16     punDuty_In[12u] = { 0x100u, 0x4u, 0x5u, 0x20Au, (0x32u+ ucChipId), 0x364u, 0x64u, 0x1u, (0x206u+ ucChipId), 0x4u, 0x3u, 0x33u };

    uint8      aucTestDataOut[16u] = {//MWIDTH01/4/7/10      MWIDTH02/5/8/11     MWIDTH03/6/9/12       MWIDTH0x_0xH
                                        0u                  , 0u                , 5u                  , 1u  , // results of 0x100u, 0x4u, 0x5u
                                        10u                 , (50u+ ucChipId)   , 100u                , 50u , // results of 0x20Au, 0x32u, 0x364u
                                        100u                , 0u                , (6u+ ucChipId)      , 32u , // results of 0x64u, 0x1u, 0x206u
                                        0u                  , 0u                , 51u                 , 0u    // results of 0x4u, 0x3u, 0x33u
                                    };

    //Step 3) Call the FUT
    CddTpsGen2_SetDutyCycle_1_1024(ucChipId, punDuty_In);

    //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
    for (uint8 ucIdx = 0u; ucIdx < 16u; ucIdx++)
    {
      AL_UNITTEST_CHECK(CddTpsGen2_DataMirror.CtrlTx.RegMWIDTH[ucChipId].ucByte[ucIdx], aucTestDataOut[ucIdx], == );
    }
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTpsGen2_SetDutyCycle_1_1024_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that punDuty_In is not changing when ucChipId is too high 
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions:
/// 
/// \input ucChipId = 8u;
/// \input punDuty_In[CDDTPSGEN2_TPS92662A_MAX_SWITCHS_PER_DEVICE]     = { 1u, 2u, 3u, 4u, 3u, 3u ,1u, 2u, 3u, 4u, 1u, 3u };
/// \input punDuty_Out[CDDTPSGEN2_TPS92662A_MAX_SWITCHS_PER_DEVICE] = { 1u, 2u, 3u, 4u, 3u, 3u ,1u, 2u, 3u, 4u, 1u, 3u };
///
/// - Expectations:
///
/// \output (punDuty_In[ucIdx] = punDuty_mirror[ucIdx]
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_SetDutyCycle_1_1024_TestCase2(void)
{
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  uint8_fast ucChipId = 8u;
  uint16 punDuty_In[CDDTPSGEN2_TPS92662A_MAX_SWITCHS_PER_DEVICE]  = { 1u, 2u, 3u, 4u, 3u, 3u ,1u, 2u, 3u, 4u, 1u, 3u };
  uint16 punDuty_Out[CDDTPSGEN2_TPS92662A_MAX_SWITCHS_PER_DEVICE] = { 1u, 2u, 3u, 4u, 3u, 3u ,1u, 2u, 3u, 4u, 1u, 3u };

  //Step 3) Call the FUT
  CddTpsGen2_SetDutyCycle_1_1024(ucChipId, punDuty_In);

  //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
  for (uint8 ucIdx = 0u; ucIdx < 12u; ucIdx++)
  {
    AL_UNITTEST_CHECK(punDuty_In[ucIdx], punDuty_Out[ucIdx], == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTpsGen2_SetDutyCycle_1_1024
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test CddTpsGen2_SetDutyCycle_1_1024 function
///
///    - Test Design Technique: DT (Decision Table)
///
/// \Expected Test Results : All contained test cases are passed
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_SetDutyCycle_1_1024(void)
{
  Mt_CddTpsGen2_SetDutyCycle_1_1024_TestCase1();
  Mt_CddTpsGen2_SetDutyCycle_1_1024_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : tsCddTpsGen2_DevData* Mt_CddTpsGen2_pfGetDevData
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Check if function returns coding data structure for GEN2
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
/// \input tsCddTpsGen2_DevData* asRetData = NULL_PTR;
/// 
///    - Expected test results: 
/// \output  asRetData == &CddTpsGen2_sDevData
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_pfGetDevData(void)
{
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  tsCddTpsGen2_DevData* asRetData = NULL_PTR;

  //Step 3) Call the FUT
  asRetData = CddTpsGen2_pfGetDevData();

  //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
  AL_UNITTEST_CHECK(asRetData                               ,&CddTpsGen2_sDevData                                             ,== );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTpsGen2_Init
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if CddTpsGen2_sDevData structure is 
///        updated correctly based on CDDTPSGEN2_Para_Get_CHIP_ID return value
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions:
/// 
/// \input TestExt_Get_Chip_Id_RetVal will take consecutive the following values: 
///               arTestChipID_in[7u] = { 1u, 16u, 7u, 8u, 0xffu, 14u, 15u}
/// \input CDDMLC_Para_CHIP_EEPROM_ID = 5u;
/// \input CDDMLC_Para_CHIP_EEPROM_ID = 5u;
///
/// - Expectations:
///
/// \output Expected values based on arTestChipID_in: 
///                       //        ucPhysicalAddr                  ,boIsMasterId         ,ucCodDevID                     ,ucEepromAddr         ,ucEepromId
///         /* 1u   */      {(uint8)CDDTPSGEN2_DEV_ID01             ,FALSE                ,0u                             ,0u                   ,0u                 },
///         /* 7u   */      {(uint8)CDDTPSGEN2_DEV_ID05             ,FALSE                ,2u                             ,CDDTPSGEN2_DEV_ID05  ,5u                 },
///         /* 8u   */      {(uint8)CDDTPSGEN2_DEV_ID00             ,TRUE                 ,3u                             ,CDDTPSGEN2_DEV_ID05  ,5u                 },
///         /* 14u  */      {(uint8)CDDTPSGEN2_DEV_ID06             ,TRUE                 ,5u                             ,CDDTPSGEN2_DEV_ID05  ,5u                 },
///         /* 15u  */      {(uint8)CDDTPSGEN2_DEV_ID07             ,TRUE                 ,6u                             ,CDDTPSGEN2_DEV_ID05  ,5u                 },
///         /* 16u  */      {0u                                     ,FALSE                ,CDDTPSGEN2_ADDR_NOT_CONNECTED  ,CDDTPSGEN2_DEV_ID05  ,5u                 },
///         /* ffu  */      {0u                                     ,FALSE                ,CDDTPSGEN2_ADDR_NOT_CONNECTED  ,CDDTPSGEN2_DEV_ID05  ,5u                 },
/// \output CddTpsGen2_sDevData.ucConnectedDevices = 5u
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_Init(void)
{
  typedef struct tsTestDataOut
  {
    uint8   ucPhysicalAddr;
    boolean boIsMasterId;
    uint8   ucCodDevID;
    uint8   ucEepromAddr;
    uint8   ucEepromId;
  }tsTestDataOut;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  uint8 arTestChipID_in[7u] = { 1u, 16u, 5u, 8u, 0xffu, 14u, 15u}; 

  // aucCodDevID Check What is the purpose?? It works as intended?
  tsTestDataOut asTestDataExpOut[7u] = { //        ucPhysicalAddr                  ,boIsMasterId         ,ucCodDevID                     ,ucEepromAddr         ,ucEepromId
                            /* 1u   */     {(uint8)CDDTPSGEN2_DEV_ID01             ,FALSE                ,0u                             ,0u                   ,0u                 },
                            /* 5u   */     {(uint8)CDDTPSGEN2_DEV_ID05             ,FALSE                ,2u                             ,CDDTPSGEN2_DEV_ID05  ,5u                 },
                            /* 8u   */     {(uint8)CDDTPSGEN2_DEV_ID00             ,TRUE                 ,3u                             ,CDDTPSGEN2_DEV_ID05  ,5u                 },
                            /* 14u  */     {(uint8)CDDTPSGEN2_DEV_ID06             ,TRUE                 ,5u                             ,CDDTPSGEN2_DEV_ID05  ,5u                 },
                            /* 15u  */     {(uint8)CDDTPSGEN2_DEV_ID07             ,TRUE                 ,6u                             ,CDDTPSGEN2_DEV_ID05  ,5u                 },
                            /* 16u  */     {0u                                     ,FALSE                ,CDDTPSGEN2_ADDR_NOT_CONNECTED  ,CDDTPSGEN2_DEV_ID05  ,5u                 },
                            /* ffu  */     {0u                                     ,FALSE                ,CDDTPSGEN2_ADDR_NOT_CONNECTED  ,CDDTPSGEN2_DEV_ID05  ,5u                 },
                                       };

  memcpy(TestExt_Get_Chip_Id_RetVal, arTestChipID_in, sizeof(arTestChipID_in));

  CDDMLC_Para_CHIP_EEPROM_ID = 5u;
  CDDMLC_Para_CHIP_EEPROM_ID = 5u;

  //Step 3) Call the FUT
  CddTpsGen2_Init();

  //Step 4) Check that the value of the output variables set/changed by the FUT match the corresponding expected output value 
  for (uint8 idx = 0u; idx < (sizeof(asTestDataExpOut) / sizeof(tsTestDataOut)); idx++)
  {
    AL_UNITTEST_CHECK(CddTpsGen2_sDevData.asMasterSlaveId[idx].ucPhysicalAddr            ,asTestDataExpOut[idx].ucPhysicalAddr           ,== );
    AL_UNITTEST_CHECK(CddTpsGen2_sDevData.asMasterSlaveId[idx].boIsMasterId              ,asTestDataExpOut[idx].boIsMasterId             ,== );
    AL_UNITTEST_CHECK(CddTpsGen2_sDevData.aucCodDevID[idx]                               ,asTestDataExpOut[idx].ucCodDevID               ,== );
    AL_UNITTEST_CHECK(CddTpsGen2_sDevData.ucEepromAddr                                   ,asTestDataExpOut[2u].ucEepromAddr              ,== ); // after EEPROM is detected, the ucEepromAddr
    AL_UNITTEST_CHECK(CddTpsGen2_sDevData.ucEepromId                                     ,asTestDataExpOut[2u].ucEepromId                ,== ); // and ucEepromId will remain the same 
  }
  AL_UNITTEST_CHECK(CddTpsGen2_sDevData.ucConnectedDevices                               ,5u                                             ,== );
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTpsGen2_Cycle
///
/// \Functional Safety: NA
/// 
/// \Test Case Description
///    - Test subject: 
///        Call CddTpsGen2_Cycle
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results: 
///
///    Function is added due to architecture design 
//-----------------------------------------------------------------------------
void Mt_CddTpsGen2_Cycle(void)
{
  // Function is added due to architecture design 
  CddTpsGen2_Cycle();
}


void ALUnitTest_AddTests(void)
{
  //CddTpsGen2_Com.c
  ALUnitTest_AddFunction("Mt_CddTpsGen2_UartTx"                       , Mt_CddTpsGen2_UartTx                      );
  ALUnitTest_AddFunction("Mt_CddTpsGen2_UartRx"                       , Mt_CddTpsGen2_UartRx                      );
  ALUnitTest_AddFunction("Mt_CddTpsGen2_StAction"                     , Mt_CddTpsGen2_StAction                    );
  ALUnitTest_AddFunction("Mt_CddTpsGen2_GetPWRStatus"                 , Mt_CddTpsGen2_GetPWRStatus                );
  ALUnitTest_AddFunction("Mt_CddTpsGen2_SchHandleEE"                  , Mt_CddTpsGen2_SchHandleEE                 );
  ALUnitTest_AddFunction("Mt_CddTpsGen2_CheckReadCommand"             , Mt_CddTpsGen2_CheckReadCommand            );
  ALUnitTest_AddFunction("Mt_CddTpsGen2_GetELEFAULTReg"               , Mt_CddTpsGen2_GetELEFAULTReg              );
  ALUnitTest_AddFunction("Mt_CddTpsGen2_GetADCReg"                    , Mt_CddTpsGen2_GetADCReg                   );
  ALUnitTest_AddFunction("Mt_CddTpsGen2_StActionEE"                   , Mt_CddTpsGen2_StActionEE                  );
  //CddTpsGen2.c
  ALUnitTest_AddFunction("Mt_CddTpsGen2_ReinitSch"                    , Mt_CddTpsGen2_ReinitSch                   );
  ALUnitTest_AddFunction("Mt_CddTpsGen2_ResetScheduler"               , Mt_CddTpsGen2_ResetScheduler              );
  ALUnitTest_AddFunction("Mt_CddTpsGen2_GetSensorInfo"                , Mt_CddTpsGen2_GetSensorInfo               );
  ALUnitTest_AddFunction("Mt_CddTpsGen2_GetComFault"                  , Mt_CddTpsGen2_GetComFault                 );
  ALUnitTest_AddFunction("Mt_CddTpsGen2_GetCrcFault"                  , Mt_CddTpsGen2_GetCrcFault                 );
  ALUnitTest_AddFunction("Mt_CddTpsGen2_GetInitStatus"                , Mt_CddTpsGen2_GetInitStatus               );
  ALUnitTest_AddFunction("Mt_CddTpsGen2_I2C_StartInit"                , Mt_CddTpsGen2_I2C_StartInit               );
  ALUnitTest_AddFunction("Mt_CddTpsGen2_I2C_ReadEeprom"               , Mt_CddTpsGen2_I2C_ReadEeprom              );
  ALUnitTest_AddFunction("Mt_CddTpsGen2_I2C_WriteEeprom"              , Mt_CddTpsGen2_I2C_WriteEeprom             );
  ALUnitTest_AddFunction("Mt_CddTpsGen2_I2C_HandlePreinit"            , Mt_CddTpsGen2_I2C_HandlePreinit           );
  ALUnitTest_AddFunction("Mt_CddTpsGen2_I2C_HandleInit"               , Mt_CddTpsGen2_I2C_HandleInit              );
  ALUnitTest_AddFunction("Mt_CddTpsGen2_I2C_HandleStart"              , Mt_CddTpsGen2_I2C_HandleStart             );
  ALUnitTest_AddFunction("Mt_CddTpsGen2_I2C_CommandReadStart"         , Mt_CddTpsGen2_I2C_CommandReadStart        );
  ALUnitTest_AddFunction("Mt_CddTpsGen2_I2C_CommandReadData"          , Mt_CddTpsGen2_I2C_CommandReadData         );
  ALUnitTest_AddFunction("Mt_CddTpsGen2_I2C_HandleReadingStatus"      , Mt_CddTpsGen2_I2C_HandleReadingStatus     );
  ALUnitTest_AddFunction("Mt_CddTpsGen2_I2C_HandleWritingStatus"      , Mt_CddTpsGen2_I2C_HandleWritingStatus     );
  ALUnitTest_AddFunction("Mt_CddTpsGen2_I2C_HandleReadData"           , Mt_CddTpsGen2_I2C_HandleReadData          );
  ALUnitTest_AddFunction("Mt_CddTpsGen2_I2C_CommandWriteData"         , Mt_CddTpsGen2_I2C_CommandWriteData        );
  ALUnitTest_AddFunction("Mt_CddTpsGen2_I2C_HandleWriteData"          , Mt_CddTpsGen2_I2C_HandleWriteData         );
  ALUnitTest_AddFunction("Mt_CddTpsGen2_I2C_CheckEEActivation"        , Mt_CddTpsGen2_I2C_CheckEEActivation       );
  ALUnitTest_AddFunction("Mt_CddTpsGen2_I2C_Timeout"                  , Mt_CddTpsGen2_I2C_Timeout                 );
  ALUnitTest_AddFunction("Mt_CddTpsGen2_GetEEConnectedId"             , Mt_CddTpsGen2_GetEEConnectedId            );
  ALUnitTest_AddFunction("Mt_CddTpsGen2_I2C_HandleReset"              , Mt_CddTpsGen2_I2C_HandleReset             );
  ALUnitTest_AddFunction("Mt_CddTpsGen2_GetPixelFault"                , Mt_CddTpsGen2_GetPixelFault               );
  ALUnitTest_AddFunction("Mt_CddTpsGen2_SetDutyCycle_1_1024"          , Mt_CddTpsGen2_SetDutyCycle_1_1024         );
  ALUnitTest_AddFunction("Mt_CddTpsGen2_pfGetDevData"                 , Mt_CddTpsGen2_pfGetDevData                );
  ALUnitTest_AddFunction("Mt_CddTpsGen2_Init"                         , Mt_CddTpsGen2_Init                        );
  ALUnitTest_AddFunction("Mt_CddTpsGen2_Cycle"                        , Mt_CddTpsGen2_Cycle                       );
}


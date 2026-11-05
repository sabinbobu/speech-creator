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
/// \brief Module test of CddUart 
///
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// Files covered by this module unit test:
///
///    CddUart.c
///    CddUart_S32K_14X.c
///
//-----------------------------------------------------------------------------

//=============================================================================
//  Includes
//=============================================================================
// Standard unit test header
#include <ALUnitTest_UserInterface.h>
// Headers of the unit test module
#include "Test.h"

//=============================================================================
//  Test Cases
//=============================================================================

// ----------------------------------------------------------------------------
// CddUart Unit Test Cases 
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \Test Case : Mt_riCddUartInit_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check Uart wrapper for CddUart_StartMapping
///       that is not mapping the cfg when driver is in reset state
///
///    - Test Design Technique: ET(Exploratory Testing )
///
/// - Preconditions:
/// 
/// \input CddUart_ucState                               = CDDUART_STATE_RESET;
/// \input CddUart_boIsDmaReady[0]                       = FALSE;
/// \input CddUart_asIfcCfg[0].ucSeqMap                  = 0u;
/// \input CddUart_asIfcCfg[1].ucSeqMap                  = 0u;
/// \input CddUart_asIfcCfg[2].ucSeqMap                  = 0u;
///
/// - Expectations:
///
/// \output CddUart_ucState,                               = CDDUART_STATE_RESET
/// \output CddUart_boIsDmaReady[0],                       = FALSE
/// \output CddUart_asIfcCfg[0].ucSeqMap,                  = 0u
/// \output CddUart_asIfcCfg[1].ucSeqMap,                  = 0u
/// \output CddUart_asIfcCfg[2].ucSeqMap,                  = 0u
/// \output 
///
//-----------------------------------------------------------------------------
void Mt_riCddUartInit_TestCase_1()
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddUart_ucState                               = CDDUART_STATE_RESET;
  CddUart_boIsDmaReady[0]                       = FALSE;
  CddUart_asIfcCfg[0].ucSeqMap                  = 0u;
  CddUart_asIfcCfg[1].ucSeqMap                  = 0u;
  CddUart_asIfcCfg[2].ucSeqMap                  = 0u;

  //Step 3) Call FUT
  riCddUartInit();
  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(CddUart_ucState                               , CDDUART_STATE_RESET,                           == );
  AL_UNITTEST_CHECK(CddUart_boIsDmaReady[0]                       , FALSE,                                         == );
  AL_UNITTEST_CHECK(CddUart_asIfcCfg[0].ucSeqMap                  , 0u,                                            == );
  AL_UNITTEST_CHECK(CddUart_asIfcCfg[1].ucSeqMap                  , 0u,                                            == );
  AL_UNITTEST_CHECK(CddUart_asIfcCfg[2].ucSeqMap                  , 0u,                                            == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_riCddUartInit_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check Uart wrapper for CddUart_StartMapping
///        is mapping correctly the cfg
///
///    - Test Design Technique: ET(Exploratory Testing )
///
/// - Preconditions:
/// 
/// \input CddUart_ucState                                  = CDDUART_STATE_INITIALIZED
/// \input CddUart_boIsDmaReady[0]                          = FALSE
/// \input CddUart_sS32K_14X_Registers.uSTAT.sBit.u1IDLE    = 1u
/// \input CddUart_asIfcCfg[0].ucSeqMap                     = 0u;
/// \input CddUart_asIfcCfg[1].ucSeqMap                     = 0u;
/// \input CddUart_asIfcCfg[2].ucSeqMap                     = 0u;
///
/// - Expectations:
///
/// \output CddUart_ucState,                               = CDDUART_STATE_CYCLIC_OPERATION
/// \output CddUart_boIsDmaReady[0],                       = TRUE
/// \output CddUart_asIfcCfg[0].ucSeqMap,                  = 0u
/// \output CddUart_asIfcCfg[1].ucSeqMap,                  = 2u
/// \output CddUart_asIfcCfg[2].ucSeqMap,                  = 1u
///
//-----------------------------------------------------------------------------
void Mt_riCddUartInit_TestCase_2()
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddUart_ucState                                   = CDDUART_STATE_INITIALIZED;
  CddUart_boIsDmaReady[0]                           = FALSE;
  CddUart_sS32K_14X_Registers.uSTAT.sBit.u1IDLE     = 1u;
  CddUart_asIfcCfg[0].ucSeqMap                      = 0u;
  CddUart_asIfcCfg[1].ucSeqMap                      = 0u;
  CddUart_asIfcCfg[2].ucSeqMap                      = 0u;

  //Step 3) Call FUT
  riCddUartInit();
  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(CddUart_ucState                               , CDDUART_STATE_CYCLIC_OPERATION,                == );
  AL_UNITTEST_CHECK(CddUart_boIsDmaReady[0]                       , TRUE,                                          == );
  AL_UNITTEST_CHECK(CddUart_asIfcCfg[0].ucSeqMap                  , 0u,                                            == );
  AL_UNITTEST_CHECK(CddUart_asIfcCfg[1].ucSeqMap                  , 2u,                                            == );
  AL_UNITTEST_CHECK(CddUart_asIfcCfg[2].ucSeqMap                  , 1u,                                            == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_riCddUartInit_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check Uart wrapper for CddUart_StartMapping
///        when the driver is initialized and u1IDLE register is not set
///
///    - Test Design Technique: ET(Exploratory Testing )
///
/// - Preconditions:
/// 
/// \input CddUart_ucState                                   = CDDUART_STATE_INITIALIZED;
/// \input CddUart_boIsDmaReady[0]                           = FALSE;
/// \input CddUart_sS32K_14X_Registers.uSTAT.sBit.u1IDLE     = 0u;
/// \input CddUart_asIfcCfg[0].ucSeqMap                      = 0u;
/// \input CddUart_asIfcCfg[1].ucSeqMap                      = 0u;
/// \input CddUart_asIfcCfg[2].ucSeqMap                      = 0u;
///
/// - Expectations:
///
/// \output CddUart_ucState,                               = CDDUART_STATE_CYCLIC_OPERATION
/// \output CddUart_boIsDmaReady[0],                       = TRUE
/// \output CddUart_asIfcCfg[0].ucSeqMap,                  = 0u
/// \output CddUart_asIfcCfg[1].ucSeqMap,                  = 2u
/// \output CddUart_asIfcCfg[2].ucSeqMap,                  = 1u
///
//-----------------------------------------------------------------------------
void Mt_riCddUartInit_TestCase_3()
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddUart_ucState                                   = CDDUART_STATE_INITIALIZED;
  CddUart_boIsDmaReady[0]                           = FALSE;
  CddUart_sS32K_14X_Registers.uSTAT.sBit.u1IDLE     = 0u;
  CddUart_asIfcCfg[0].ucSeqMap                      = 0u;
  CddUart_asIfcCfg[1].ucSeqMap                      = 0u;
  CddUart_asIfcCfg[2].ucSeqMap                      = 0u;

  //Step 3) Call FUT
  riCddUartInit();
  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(CddUart_ucState                               , CDDUART_STATE_CYCLIC_OPERATION,                == );
  AL_UNITTEST_CHECK(CddUart_boIsDmaReady[0]                       , TRUE,                                          == );
  AL_UNITTEST_CHECK(CddUart_asIfcCfg[0].ucSeqMap                  , 0u,                                            == );
  AL_UNITTEST_CHECK(CddUart_asIfcCfg[1].ucSeqMap                  , 2u,                                            == );
  AL_UNITTEST_CHECK(CddUart_asIfcCfg[2].ucSeqMap                  , 1u,                                            == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_riCddUartInit
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Check the Dynamic Configuration 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected Test Results : All contained test cases are passed
///
//-----------------------------------------------------------------------------
void Mt_riCddUartInit(void)
{
  Mt_riCddUartInit_TestCase_1();
  Mt_riCddUartInit_TestCase_2();
  Mt_riCddUartInit_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_rpCddUart_Cycle_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test first cyclic call when
///       the uart registers are set and first Tx message is setup
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions:
/// 
/// \input Coding BandRate in MLC
/// \input CddUart_asDeviceCfg[] registers
///
/// - Expectations:
///
/// \output UART_Register_UnitTest updated accordingly to input
/// \output One call of the TX call back set in CDDUART_DEVCB_CFG for every sequence 
///
//-----------------------------------------------------------------------------
void Mt_rpCddUart_Cycle_TestCase_1()
{
  typedef struct tsTestCaseData
  {
    uint8  sInputData;
    uint32 sOutputData;
  }tsTestCaseData;

  typedef struct tsTestCaseDataArr
  {
    uint8 sInputData[CddUart_eDev_Count];
    uint8 sOutputData[CddUart_eDev_Count];
  }tsTestCaseDataArr;

  //                                                  BandRate input/output                                                     //
  tsTestCaseData asTestCaseDataBandRate = { CDDUART_BAUDRATE_CODING_500Kbps, CDDUART_BAUDRATE_500K }; 

  tsTestCaseDataArr asTestCaseDataReg[] =
  {
    //--------------------------------------------------------------uBAUD--------------------------------------------------------------//
    { // 0                                                 u13SBR register check                                                 //
      //         Device 1                                                 Device 2                                                          Device 3                                                          Device 4                                                          Device 5                                                         Device 6     //
      { 0,                                                                0,                                                                0,                                                                0,                                                                0,                                                               0                                                                  }, // not used, ulBaudRate set trough CddMlc_Cod_UartGetConfig 
      { CDDUART_BAUDRATE_SBR_DIVISOR_REGISTER_VAL(CDDUART_BAUDRATE_500K), CDDUART_BAUDRATE_SBR_DIVISOR_REGISTER_VAL(CDDUART_BAUDRATE_500K), CDDUART_BAUDRATE_SBR_DIVISOR_REGISTER_VAL(CDDUART_BAUDRATE_500K), CDDUART_BAUDRATE_SBR_DIVISOR_REGISTER_VAL(CDDUART_BAUDRATE_500K), CDDUART_BAUDRATE_SBR_DIVISOR_REGISTER_VAL(CDDUART_BAUDRATE_500K), CDDUART_BAUDRATE_SBR_DIVISOR_REGISTER_VAL(CDDUART_BAUDRATE_500K)  }  //    with asTestCaseDataBandRate.sInputData
    },

    { // 1                                                 u5OSR register check                                                  //
      //Device 1                                                  Device 2                                                 Device 3                                                 Device 4                                                  Device 5                                                  Device 6     //
      { 0,                                                        0,                                                       0,                                                       0,                                                        0,                                                        0                                                          }, // not used, ulBaudRate set trough CddMlc_Cod_UartGetConfig  
      { CDDUART_BAUDRATE_OVS_REGISTER_VAL(CDDUART_BAUDRATE_500K), CDDUART_BAUDRATE_OVS_REGISTER_VAL(CDDUART_BAUDRATE_500K),CDDUART_BAUDRATE_OVS_REGISTER_VAL(CDDUART_BAUDRATE_500K),CDDUART_BAUDRATE_OVS_REGISTER_VAL(CDDUART_BAUDRATE_500K), CDDUART_BAUDRATE_OVS_REGISTER_VAL(CDDUART_BAUDRATE_500K), CDDUART_BAUDRATE_OVS_REGISTER_VAL(CDDUART_BAUDRATE_500K)   }  //  with asTestCaseDataBandRate.sInputData
    },

    { // 2                                                 u1SBNS(StopBits) register check                                      //
      //Device 1                                  Device 2                                  Device 3                                     Device 4                                    Device 5                                   Device 6     //
      {                       CDDUART_1_STOPBIT,                         CDDUART_1_STOPBIT,                        CDDUART_2_STOPBITS,                        CDDUART_1_STOPBIT,                         CDDUART_1_STOPBIT,                          CDDUART_1_STOPBIT    }, // UT2 shall be set as UT1 bk UT2 doesn't have callback function 
      {CDDUART_STOPBIT_SELECT(CDDUART_1_STOPBIT), CDDUART_STOPBIT_SELECT(CDDUART_1_STOPBIT), CDDUART_STOPBIT_SELECT(CDDUART_2_STOPBITS), CDDUART_STOPBIT_SELECT(CDDUART_2_STOPBITS), CDDUART_STOPBIT_SELECT(CDDUART_1_STOPBIT), CDDUART_STOPBIT_SELECT(CDDUART_1_STOPBIT) }  // expected value is based on which ifc is set
    },

    //--------------------------------------------------------------uCTRL--------------------------------------------------------------//
    { // 3                                                 u1PE register check                                                  //
      //Device 1                                Device 2                                 Device 3                                 Device 4                                 Device 5                                 Device 6     //
      {                      CDDUART_PARITY_ENABLE,                        CDDUART_PARITY_ENABLE,                        CDDUART_PARITY_DISABLE,                        CDDUART_PARITY_DISABLE,                        CDDUART_PARITY_ENABLE,                        CDDUART_PARITY_ENABLE   },
      {CDDUART_PARITY_SELECT(CDDUART_PARITY_ENABLE), CDDUART_PARITY_SELECT(CDDUART_PARITY_ENABLE), CDDUART_PARITY_SELECT(CDDUART_PARITY_DISABLE), CDDUART_PARITY_SELECT(CDDUART_PARITY_DISABLE), CDDUART_PARITY_SELECT(CDDUART_PARITY_ENABLE), CDDUART_PARITY_SELECT(CDDUART_PARITY_ENABLE)  } // expected value is based on which ifc is set
    },

    //--------------------------------------------------------------uSTAT--------------------------------------------------------------//
    { // 4                                                 u1MSBF register check                                                 //
      //Device 1                                    Device 2                                     Device 3                                     Device 4                                     Device 5                                    Device 6     //
      {                         CDDUART_MSB_FIRST,                           CDDUART_MSB_FIRST,                           CDDUART_LSB_FIRST,                           CDDUART_LSB_FIRST,                           CDDUART_MSB_FIRST ,                         CDDUART_MSB_FIRST   }, // UT2 shall be set as UT1 bk UT2 doesn't have callback function 
      {CDDUART_BIT_ORDER_SELECT(CDDUART_MSB_FIRST), CDDUART_BIT_ORDER_SELECT(CDDUART_MSB_FIRST), CDDUART_BIT_ORDER_SELECT(CDDUART_LSB_FIRST), CDDUART_BIT_ORDER_SELECT(CDDUART_LSB_FIRST), CDDUART_BIT_ORDER_SELECT(CDDUART_MSB_FIRST),CDDUART_BIT_ORDER_SELECT(CDDUART_MSB_FIRST)  }  // expected value is based on which ifc is set
    },

  };

  CddMlc_Cod_UartGetConfig_RetVal               = TRUE;
  CddUart_ucState                               = CDDUART_STATE_CYCLIC_OPERATION;
  CddMlc_Cod_UartGetConfig_HitCount             = 0u;
  CddTpsGen2_UartTx_HitCount                    = 0u;
  CddTpsGen3_UartTx_HitCount                    = 0u;
  CddTps_UartTxDummyIFC2_HitCount               = 0u;
  CddTps_UartTxDummyIFC3_HitCount               = 0u;
  CddMlc_Cod_UartGetConfig_Param2               = asTestCaseDataBandRate.sInputData;
  CddMlc_Cod_UartGetConfig_Param3               = 3u; 

  for (uint8 ucIdxDev = 0; ucIdxDev < CddUart_eDev_Count; ucIdxDev++)
  {
    CddUart_asDeviceCfg[ucIdxDev].ucStopBits = asTestCaseDataReg[2u].sInputData[ucIdxDev];
    CddUart_asDeviceCfg[ucIdxDev].ucParity   = asTestCaseDataReg[3u].sInputData[ucIdxDev];
    CddUart_asDeviceCfg[ucIdxDev].ucDataDir  = asTestCaseDataReg[4u].sInputData[ucIdxDev];

    //                                                    Fill Transfer data                                                  //
    if (ucIdxDev < TEST_SEQ_COUNT)
    {
      for (uint8 ucIdxSeq = 0; ucIdxSeq < 10; ucIdxSeq++)
      {
        Test_Uart_sMessageEntry[ucIdxDev].pucTxData[ucIdxSeq] = ucIdxDev*10 + ucIdxSeq;
      }
      Test_Uart_sMessageEntry[ucIdxDev].ucTxDataLength = 10;
    }
  }

  //Step 3) Call FUT
  rpCddUart_Cycle();
  //Step 4) Check expected output value

  AL_UNITTEST_CHECK(CddMlc_Cod_UartGetConfig_HitCount                                               , 5u,                                                               == );
  AL_UNITTEST_CHECK(CddTpsGen2_UartTx_HitCount                                                      , 1u,                                                               == );
  AL_UNITTEST_CHECK(CddTpsGen3_UartTx_HitCount                                                      , 0u,                                                               == );
  AL_UNITTEST_CHECK(CddTps_UartTxDummyIFC2_HitCount                                                 , 1u,                                                               == );
  AL_UNITTEST_CHECK(CddTps_UartTxDummyIFC3_HitCount                                                 , 1u,                                                               == );

  for (uint8 ucIdxDev = 0; ucIdxDev < CddUart_eDev_Count; ucIdxDev++)
  {
    //                                                   registers check                                                 //
    AL_UNITTEST_CHECK(CddUart_asDeviceCfg[ucIdxDev].ulBaudRate                                            , asTestCaseDataBandRate.sOutputData,                                 == );
    AL_UNITTEST_CHECK(UART_Register_UnitTest[CddUart_asDeviceCfg[ucIdxDev].ucUartIfc].uBAUD.sBit.u13SBR   , asTestCaseDataReg[0u].sOutputData[ucIdxDev],                        == );
    AL_UNITTEST_CHECK(UART_Register_UnitTest[CddUart_asDeviceCfg[ucIdxDev].ucUartIfc].uBAUD.sBit.u5OSR    , asTestCaseDataReg[1u].sOutputData[ucIdxDev],                        == );
    AL_UNITTEST_CHECK(UART_Register_UnitTest[CddUart_asDeviceCfg[ucIdxDev].ucUartIfc].uBAUD.sBit.u1SBNS   , asTestCaseDataReg[2u].sOutputData[ucIdxDev],                        == );
    AL_UNITTEST_CHECK(UART_Register_UnitTest[CddUart_asDeviceCfg[ucIdxDev].ucUartIfc].uCTRL.sBit.u1PE     , asTestCaseDataReg[3u].sOutputData[ucIdxDev],                        == );
    AL_UNITTEST_CHECK(UART_Register_UnitTest[CddUart_asDeviceCfg[ucIdxDev].ucUartIfc].uSTAT.sBit.u1MSBF   , asTestCaseDataReg[4u].sOutputData[ucIdxDev],                        == );
    AL_UNITTEST_CHECK(UART_Register_UnitTest[CddUart_asDeviceCfg[ucIdxDev].ucUartIfc].uCTRL.sBit.u1RE     , CDDUART_ENABLE_VAL_SET,                                             == );
    AL_UNITTEST_CHECK(UART_Register_UnitTest[CddUart_asDeviceCfg[ucIdxDev].ucUartIfc].uCTRL.sBit.u1TE     , CDDUART_ENABLE_VAL_SET,                                             == );

    //                                                    check that Transfer data is correct                                                 //
    if (ucIdxDev < TEST_SEQ_COUNT)
    {
      // Check 80 bytes of data for every sequnce
      for (uint8 ucIdxSeq = 0; ucIdxSeq < 10; ucIdxSeq++)
      {
        AL_UNITTEST_CHECK(CddUart_sMessageEntry[ucIdxDev].pucTxData[ucIdxSeq]     , Test_Uart_sMessageEntry[ucIdxDev].pucTxData[ucIdxSeq],                                              == );
      }

      AL_UNITTEST_CHECK(CddUart_sMessageEntry[ucIdxDev].ucTxDataLength          , Test_Uart_sMessageEntry[ucIdxDev].ucTxDataLength,                                                   == );
      AL_UNITTEST_CHECK(CddUart_asSeqHandler[ucIdxDev].ucSeqContext             , CDDUART_SEQ_CONTEXT_INITIALIZED_MSK,                                                                == );
      AL_UNITTEST_CHECK(CddUart_asSeqHandler[ucIdxDev].ucCycleCnt               , 0x0u,                                                                                               == );
    }
  }

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_rpCddUart_Cycle_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test cyclic after 
///       IRQ 0 was called ( message was successfully received )
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
/// 
/// \input Test_Uart_sMessageEntry[0].ucTxDataLength     = 10u;
/// \input CddTpsGen2_UartRx_HitCount                    = 0u;
/// \input CddTpsGen3_UartRx_HitCount                    = 0u;
/// \input CddTps_UartRxDummyIFC2_HitCount               = 0u;
/// \input CddTps_UartRxDummyIFC3_HitCount               = 0u;
/// \input CddTpsGen2_UartTx_HitCount                    = 0u;
/// \input CddTpsGen3_UartTx_HitCount                    = 0u;
/// \input CddTps_UartTxDummyIFC2_HitCount               = 0u;
/// \input CddTps_UartTxDummyIFC3_HitCount               = 0u;
/// \input CddUart_boIsDmaReady[0]                       = TRUE;
///
/// - Expectations:
///
/// \output UART_Register_UnitTest updated accordingly to input
/// \output One call of the TX call back set in CDDUART_DEVCB_CFG for every sequence 
///
//-----------------------------------------------------------------------------
void Mt_rpCddUart_Cycle_TestCase_2()
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Test_Uart_sMessageEntry[0].ucTxDataLength     = 10u;
  CddTpsGen2_UartRx_HitCount                    = 0u;
  CddTpsGen3_UartRx_HitCount                    = 0u;
  CddTps_UartRxDummyIFC2_HitCount               = 0u;
  CddTps_UartRxDummyIFC3_HitCount               = 0u;
  CddTpsGen2_UartTx_HitCount                    = 0u;
  CddTpsGen3_UartTx_HitCount                    = 0u;
  CddTps_UartTxDummyIFC2_HitCount               = 0u;
  CddTps_UartTxDummyIFC3_HitCount               = 0u;
  CddUart_boIsDmaReady[0]                       = TRUE;

  //Step 3) Call FUT
  rpCddUart_Cycle();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(CddTpsGen2_UartRx_HitCount                              , 0u,                                              == );
  AL_UNITTEST_CHECK(CddTpsGen3_UartRx_HitCount                              , 0u,                                              == );
  AL_UNITTEST_CHECK(CddTps_UartRxDummyIFC2_HitCount                         , 0u,                                              == );
  AL_UNITTEST_CHECK(CddTps_UartRxDummyIFC3_HitCount                         , 0u,                                              == );
  AL_UNITTEST_CHECK(CddTpsGen2_UartTx_HitCount                              , 1u,                                              == );
  AL_UNITTEST_CHECK(CddTpsGen3_UartTx_HitCount                              , 0u,                                              == );
  AL_UNITTEST_CHECK(CddTps_UartTxDummyIFC2_HitCount                         , 0u,                                              == );
  AL_UNITTEST_CHECK(CddTps_UartTxDummyIFC3_HitCount                         , 0u,                                              == );
  AL_UNITTEST_CHECK(CddUart_asSeqData[0].sStM.ucCbAct                       , 0u,                                              == );
  AL_UNITTEST_CHECK(CddUart_asSeqData[0].sStM.ucDevAct                      , 0u,                                              == );
  AL_UNITTEST_CHECK(CddUart_boIsDmaReady[0]                                 , FALSE,                                           == );
  AL_UNITTEST_CHECK(CddUart_asSeqHandler[0].ucTimeOutCnt                    , CddUart_asSeqHandler[0].ucTimeOutMax,            == );

  for (uint8 ucIdxData = 0; ucIdxData < 10; ucIdxData++)
  {
    AL_UNITTEST_CHECK(CddUart_sMessageEntry[0].pucTxData[ucIdxData], Test_Uart_sMessageEntry[0].pucTxData[ucIdxData], == );
  }

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_rpCddUart_Cycle_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test cyclic when timeout is reached 
///       
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
/// 
/// \input Set CddUart_sMessageEntry[ucIdx].pucTxData to NULL_PTR
/// \input populate test buffer data for tx
/// \input set tx and rx length to 10
/// \input reset hit counters 
/// \input set tx and rx callback functions for seq to NULL_PTR 
///
/// - Expectations:
///
/// \output ucTimeOutCnt is decremented on every FUT call
/// \output Tx for seq 1 and 2 are equal to tx test buffer
/// \output Tx for seq 0 is NULL_PTR
/// \output Only CddTps_UartTxDummyIFC3 and CddTps_UartTxDummyIFC2 will be called 
///
//-----------------------------------------------------------------------------
void Mt_rpCddUart_Cycle_TestCase_3()
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  for (uint8 ucIdxSeq = 0u; ucIdxSeq < TEST_SEQ_COUNT; ucIdxSeq++)
  {
    CddUart_sMessageEntry[ucIdxSeq].pucTxData = NULL_PTR;
    for (uint8 ucIdx = 0u; ucIdx < 10u; ucIdx++)
    {
      Test_Uart_sMessageEntry[ucIdxSeq].pucTxData[ucIdx]  = ((ucIdxSeq+1)*10) + ucIdx;
    }

    Test_Uart_sMessageEntry[ucIdxSeq].ucTxDataLength      = 10u;
    CddUart_sMessageEntry[ucIdxSeq].ucRxDataLength        = 10u;
    CddUart_sMessageEntry[ucIdxSeq].ucTxDataLength        = 10u;
    CddUart_asSeqHandler[ucIdxSeq].ucTimeOutCnt           = CddUart_asSeqHandler[ucIdxSeq].ucTimeOutMax;
    CddUart_asSeqData[ucIdxSeq].sStM.ucCbAct              = 0u;
    CddUart_asSeqData[ucIdxSeq].sStM.ucDevAct             = 0u;
    CddUart_boIsDmaReady[ucIdxSeq]                        = FALSE;
  }
  CddUart_boRxSuccess                                         = TRUE;
  CddTpsGen2_UartRx_HitCount                                  = 0u;
  CddTpsGen3_UartRx_HitCount                                  = 0u;
  CddTpsGen2_UartTx_HitCount                                  = 0u;
  CddTpsGen3_UartTx_HitCount                                  = 0u;
  CddTps_UartRxDummyIFC2_HitCount                             = 0u;
  CddTps_UartRxDummyIFC3_HitCount                             = 0u;
  CddTps_UartTxDummyIFC2_HitCount                             = 0u;
  CddTps_UartTxDummyIFC3_HitCount                             = 0u;
  CddUart_asSeqData[0].psDevData[0].psCbData[0].sDevCb.fpRx   = NULL_PTR;
  CddUart_asSeqData[0].psDevData[0].psCbData[1].sDevCb.fpTx   = NULL_PTR;

  for (uint8 ucIdx = 4u; ucIdx > 0u; ucIdx--)
  {
    //Step 3) Call FUT
    rpCddUart_Cycle();

   //Step 4) Check expected output value
    // Check that the ucTimeOutCnt of every seq reach 0
    if (ucIdx > 1u)
    {
      AL_UNITTEST_CHECK(CddUart_asSeqHandler[0].ucTimeOutCnt                    , (ucIdx - 2u),            == );
      AL_UNITTEST_CHECK(CddUart_asSeqHandler[1].ucTimeOutCnt                    , (ucIdx - 2u),            == );
      AL_UNITTEST_CHECK(CddUart_asSeqHandler[2].ucTimeOutCnt                    , (ucIdx - 2u),            == );
    }
  }

  // CddUart_sMessageEntry[0] is null ptr, test starting from next seq
  for (uint8 ucIdxSeq = 1u; ucIdxSeq < TEST_SEQ_COUNT; ucIdxSeq++)
  {
    for (uint8 ucIdx = 0u; ucIdx < 10u; ucIdx++)
    {
      AL_UNITTEST_CHECK(CddUart_sMessageEntry[ucIdxSeq].pucTxData[ucIdx]        , Test_Uart_sMessageEntry[ucIdxSeq].pucTxData[ucIdx],                   == );
    }
  }
  AL_UNITTEST_CHECK(CddUart_sMessageEntry[0].pucTxData                      , NULL_PTR,                                        == );
  AL_UNITTEST_CHECK(CddTpsGen2_UartRx_HitCount                              , 0u,                                              == );
  AL_UNITTEST_CHECK(CddTpsGen3_UartRx_HitCount                              , 0u,                                              == );
  AL_UNITTEST_CHECK(CddTps_UartRxDummyIFC2_HitCount                         , 0u,                                              == );
  AL_UNITTEST_CHECK(CddTps_UartRxDummyIFC3_HitCount                         , 0u,                                              == );
  AL_UNITTEST_CHECK(CddTpsGen2_UartTx_HitCount                              , 0u,                                              == );
  AL_UNITTEST_CHECK(CddTpsGen3_UartTx_HitCount                              , 0u,                                              == );
  AL_UNITTEST_CHECK(CddTps_UartTxDummyIFC2_HitCount                         , 1u,                                              == );
  AL_UNITTEST_CHECK(CddTps_UartTxDummyIFC3_HitCount                         , 1u,                                              == );

  // Reset callback functions 
  CddUart_asSeqData[0].psDevData[0].psCbData[0].sDevCb.fpRx = CddTpsGen2_UartRx;
  CddUart_asSeqData[0].psDevData[0].psCbData[1].sDevCb.fpTx = CddTpsGen2_UartTx;
  }

//-----------------------------------------------------------------------------
/// \Test Case : Mt_rpCddUart_Cycle_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test cyclic on reset state and for different BoundRate 
///             to check if the u5OSR register is updated correctly 
/// 
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions:
/// 
/// \input Set://  CddMlc_Cod_UartGetConfig_RetVal  |      ucCodBaudRate                   |   CddUart_ucState IN/OUT          |   u5OSR OUT                                                |   ucTimeOutCnt OUT
///            {   FALSE                            ,      CDDUART_BAUDRATE_CODING_1Mbps   ,   CDDUART_STATE_RESET             ,   CDDUART_BAUDRATE_OVS_REGISTER_VAL(CDDUART_BAUDRATE_500K) ,   3u             },
///            {   FALSE                            ,      CDDUART_BAUDRATE_CODING_1Mbps   ,   CDDUART_STATE_CYCLIC_OPERATION  ,   CDDUART_BAUDRATE_OVS_REGISTER_VAL(CDDUART_BAUDRATE_500K) ,   3u             },
///            {   TRUE                             ,      12u                             ,   CDDUART_STATE_CYCLIC_OPERATION  ,   CDDUART_BAUDRATE_OVS_REGISTER_VAL(CDDUART_BAUDRATE_500K) ,   2u             },
///            {   TRUE                             ,      CDDUART_BAUDRATE_CODING_1Mbps   ,   CDDUART_STATE_CYCLIC_OPERATION  ,   CDDUART_BAUDRATE_OVS_REGISTER_VAL(CDDUART_BAUDRATE_1M)   ,   1u             },
/// \input reset hit count to callback functions
/// \input UART_Register_UnitTest[1].uBAUD.sBit.u5OSR    = CDDUART_BAUDRATE_OVS_REGISTER_VAL(CDDUART_BAUDRATE_500K);
/// \input UART_Register_UnitTest[2].uBAUD.sBit.u5OSR    = CDDUART_BAUDRATE_OVS_REGISTER_VAL(CDDUART_BAUDRATE_500K);
/// \input UART_Register_UnitTest[3].uBAUD.sBit.u5OSR    = CDDUART_BAUDRATE_OVS_REGISTER_VAL(CDDUART_BAUDRATE_500K);
/// \input UCddUart_asSeqHandler[0].ucTimeOutCnt         = 3u;
/// \input UCddUart_asSeqHandler[1].ucTimeOutCnt         = 3u;
/// \input UCddUart_asSeqHandler[2].ucTimeOutCnt         = 3u;
///
/// - Expectations:
///
/// \output No hit on callback functions because CddUart_asSeqHandler[x].ucTimeOutCnt != 0u and ((psSeqHandler->ucSeqContext & CDDUART_SEQ_CONTEXT_COMPLETE_MSK) == 0U)
/// \output CddUart_ucState                              = ucArTestDataIn[ucIdx][2u]
/// \output UART_Register_UnitTest[1].uBAUD.sBit.u5OSR   = ucArTestDataIn[ucIdx][3u]
/// \output UART_Register_UnitTest[2].uBAUD.sBit.u5OSR   = ucArTestDataIn[ucIdx][3u]
/// \output UART_Register_UnitTest[3].uBAUD.sBit.u5OSR   = ucArTestDataIn[ucIdx][3u]
/// \output CddUart_asSeqHandler[0].ucTimeOutCnt         = ucArTestDataIn[ucIdx][4u]
/// \output CddUart_asSeqHandler[1].ucTimeOutCnt         = ucArTestDataIn[ucIdx][4u]
/// \output CddUart_asSeqHandler[2].ucTimeOutCnt         = ucArTestDataIn[ucIdx][4u]
/// \output CddTpsGen2_UartRx_HitCount                   = 0u
/// \output CddTpsGen3_UartRx_HitCount                   = 0u
/// \output CddTps_UartRxDummyIFC2_HitCount              = 0u
/// \output CddTps_UartRxDummyIFC3_HitCount              = 0u
/// \output CddTpsGen2_UartTx_HitCount                   = 0u
/// \output CddTpsGen3_UartTx_HitCount                   = 0u
/// \output CddTps_UartTxDummyIFC2_HitCount              = 0u
/// \output CddTps_UartTxDummyIFC3_HitCount              = 0u
///  
//-----------------------------------------------------------------------------
void Mt_rpCddUart_Cycle_TestCase_4()
{
  
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  uint8 ucArTestDataIn[4][5] =
  { //  CddMlc_Cod_UartGetConfig_RetVal  |      ucCodBaudRate                   |   CddUart_ucState IN/OUT          |   u5OSR OUT                                                |   ucTimeOutCnt OUT
    {   FALSE                            ,      CDDUART_BAUDRATE_CODING_1Mbps   ,   CDDUART_STATE_RESET             ,   CDDUART_BAUDRATE_OVS_REGISTER_VAL(CDDUART_BAUDRATE_500K) ,   3u             },
    {   FALSE                            ,      CDDUART_BAUDRATE_CODING_1Mbps   ,   CDDUART_STATE_CYCLIC_OPERATION  ,   CDDUART_BAUDRATE_OVS_REGISTER_VAL(CDDUART_BAUDRATE_500K) ,   3u             },
    {   TRUE                             ,      12u                             ,   CDDUART_STATE_CYCLIC_OPERATION  ,   CDDUART_BAUDRATE_OVS_REGISTER_VAL(CDDUART_BAUDRATE_500K) ,   2u             },
    {   TRUE                             ,      CDDUART_BAUDRATE_CODING_1Mbps   ,   CDDUART_STATE_CYCLIC_OPERATION  ,   CDDUART_BAUDRATE_OVS_REGISTER_VAL(CDDUART_BAUDRATE_1M)   ,   1u             },
  };
  
  CddTpsGen2_UartRx_HitCount                              = 0u;
  CddTpsGen3_UartRx_HitCount                              = 0u;
  CddTps_UartRxDummyIFC2_HitCount                         = 0u;
  CddTps_UartRxDummyIFC3_HitCount                         = 0u;
  CddTpsGen2_UartTx_HitCount                              = 0u;
  CddTpsGen3_UartTx_HitCount                              = 0u;
  CddTps_UartTxDummyIFC2_HitCount                         = 0u;
  CddTps_UartTxDummyIFC3_HitCount                         = 0u;
  CddUart_asDeviceCfg[0].ulBaudRate                       = CDDUART_BAUDRATE_1M * 2u;
  CddUart_asSeqHandler[0].ucTimeOutCnt                    = 3u;
  CddUart_asSeqHandler[1].ucTimeOutCnt                    = 3u;
  CddUart_asSeqHandler[2].ucTimeOutCnt                    = 3u;

  for (uint8 ucIdx = 0u; ucIdx < 4u; ucIdx++)
  {
    boCodingData                                  = FALSE;
    CddMlc_Cod_UartGetConfig_RetVal               = ucArTestDataIn[ucIdx][0u];
    CddMlc_Cod_UartGetConfig_Param2               = ucArTestDataIn[ucIdx][1u];
    CddUart_ucState                               = ucArTestDataIn[ucIdx][2u];
    UART_Register_UnitTest[1].uBAUD.sBit.u5OSR    = CDDUART_BAUDRATE_OVS_REGISTER_VAL(CDDUART_BAUDRATE_500K);
    UART_Register_UnitTest[2].uBAUD.sBit.u5OSR    = CDDUART_BAUDRATE_OVS_REGISTER_VAL(CDDUART_BAUDRATE_500K);
    UART_Register_UnitTest[3].uBAUD.sBit.u5OSR    = CDDUART_BAUDRATE_OVS_REGISTER_VAL(CDDUART_BAUDRATE_500K);

    //Step 3) Call FUT
    rpCddUart_Cycle();
    //Step 4) Check expected output value
    AL_UNITTEST_CHECK(CddUart_ucState                                         , ucArTestDataIn[ucIdx][2u],                       == );
    AL_UNITTEST_CHECK(UART_Register_UnitTest[1].uBAUD.sBit.u5OSR              , ucArTestDataIn[ucIdx][3u],                       == );
    AL_UNITTEST_CHECK(UART_Register_UnitTest[2].uBAUD.sBit.u5OSR              , ucArTestDataIn[ucIdx][3u],                       == );
    AL_UNITTEST_CHECK(UART_Register_UnitTest[3].uBAUD.sBit.u5OSR              , ucArTestDataIn[ucIdx][3u],                       == );
    AL_UNITTEST_CHECK(CddUart_asSeqHandler[0].ucTimeOutCnt                    , ucArTestDataIn[ucIdx][4u],                       == );
    AL_UNITTEST_CHECK(CddUart_asSeqHandler[1].ucTimeOutCnt                    , ucArTestDataIn[ucIdx][4u],                       == );
    AL_UNITTEST_CHECK(CddUart_asSeqHandler[2].ucTimeOutCnt                    , ucArTestDataIn[ucIdx][4u],                       == );
    AL_UNITTEST_CHECK(CddTpsGen2_UartRx_HitCount                              , 0u,                                              == );
    AL_UNITTEST_CHECK(CddTpsGen3_UartRx_HitCount                              , 0u,                                              == );
    AL_UNITTEST_CHECK(CddTps_UartRxDummyIFC2_HitCount                         , 0u,                                              == );
    AL_UNITTEST_CHECK(CddTps_UartRxDummyIFC3_HitCount                         , 0u,                                              == );
    AL_UNITTEST_CHECK(CddTpsGen2_UartTx_HitCount                              , 0u,                                              == );
    AL_UNITTEST_CHECK(CddTpsGen3_UartTx_HitCount                              , 0u,                                              == );
    AL_UNITTEST_CHECK(CddTps_UartTxDummyIFC2_HitCount                         , 0u,                                              == );
    AL_UNITTEST_CHECK(CddTps_UartTxDummyIFC3_HitCount                         , 0u,                                              == );

  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_rpCddUart_Cycle
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Check the entire flow of rpCddUart_Cycle function
///
///    - Test Design Technique: ET (Exploratory Testing)/ET (Exploratory Testing)
///
/// \Expected Test Results : All contained test cases are passed
///
//-----------------------------------------------------------------------------
void Mt_rpCddUart_Cycle(void)
{
  Mt_rpCddUart_Cycle_TestCase_1();
  Mt_rpCddUart_Cycle_TestCase_2();
  Mt_rpCddUart_Cycle_TestCase_3();
  Mt_rpCddUart_Cycle_TestCase_4();
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddUart_DMA_RX_CallbackFct
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test CddUart_DMA_RX_CallbackFct call
///       - Check that the Test_Uart_sMessageEntry buffer is taken the values from CddUart_aucRxDataDMA[ucTestTxDataLength]
///       - Check that ucCbAct and ucDevAct from sStM are incremented correctly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
/// 
/// \input reset HitCounts 
/// \input Test_Uart_sMessageEntry[0].ucRxDataLength     = 10u
/// \input CddUart_sMessageEntry[0].ucTxDataLength = 0 -> 16
/// \input CddUart_aucRxDataDMA[0][ucTestTxDataLength + ucIdx-1] = ucIdx* ucIdxIrq; 
///         CddUart_aucRxDataDMA is populated starting from ucTestTxDataLength!
/// \input Test_Uart_sMessageEntry[0].ucRxDataLength     = 10u;
/// \input CddUart_boRxSuccess                           = TRUE
/// \input CddUart_asSeqData[0].sStM.ucCbAct             = 0u;
/// \input CddUart_asSeqData[0].sStM.ucDevAct            = 0u;
/// \input CddUart_sMessageEntry[0].ucTxDataLength   = ucTestTxDataLength;
/// \input Test_Uart_sMessageEntry[0].ucTxDataLength = ucTestTxDataLength;
/// \input CddDma_EnableHwTrigger_Param1             = LPSPI1_TX;
/// \input CddDma_EnableHwTrigger_Param2             = TRUE;
/// \input Test_Uart_sMessageEntry[0].pucRxData[ucIdx-1u] = 0u;
/// \input Test_Uart_sMessageEntry[0].pucTxData[ucIdx-1u] = 10u + ucIdx * ucIdxIrq;
/// \input CddUart_aucRxDataDMA[0][ucTestTxDataLength + ucIdx-1] = ucIdx* ucIdxIrq;
/// 
///
/// - Expectations:
///
/// \output Test_Uart_sMessageEntry[0].pucRxData == CddUart_aucRxDataDMA[0][ucTestTxDataLength]
/// \output ucCbAct - for first device expect ucCbAct to reach 1, for the second device ucCbAct shall reach 4
/// \output ucDevAct increments from 0 to 1 because we have 2 DevCyc
/// \output ucCbAct and ucCbAct end up in stop condition (0xFFu)
/// \output CddUart_sMessageEntry[0].ucRxDataLength = Test_Uart_sMessageEntry[0].ucRxDataLength
/// \output CddUart_boIsDmaReady[0]                 = TRUE
/// \output CddTpsGen2_UartRx_HitCount              = 2u
/// \output CddTpsGen3_UartRx_HitCount              = 4u
/// \output CddTps_UartRxDummyIFC2_HitCount         = 0u
/// \output CddTps_UartRxDummyIFC3_HitCount         = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddUart_DMA_RX_CallbackFct()
{
  Test_Uart_sMessageEntry[0].ucRxDataLength     = 10u;
  CddUart_boRxSuccess                           = TRUE;
  CddTpsGen2_UartRx_HitCount                    = 0u;
  CddTpsGen3_UartRx_HitCount                    = 0u;
  CddTps_UartRxDummyIFC2_HitCount               = 0u;
  CddTps_UartRxDummyIFC3_HitCount               = 0u;
  CddTpsGen2_UartTx_HitCount                    = 0u;
  CddTpsGen3_UartTx_HitCount                    = 0u;
  CddTps_UartTxDummyIFC2_HitCount               = 0u;
  CddTps_UartTxDummyIFC3_HitCount               = 0u;
  CddUart_asSeqData[0].sStM.ucCbAct             = 0u;
  CddUart_asSeqData[0].sStM.ucDevAct            = 0u;


  // Simulate 6 IRQ for reading Rx data
  for (uint8 ucIdxIrq = 1u; ucIdxIrq <= 6u; ucIdxIrq++)
  {
    uint8 ucTestTxDataLength = ( ucIdxIrq == 1u ? 0u : (10u + ucIdxIrq) ); // start length from 0 to cover (CddUart_sMessageEntry[ucSeq].ucTxDataLength != 0u) case

    CddUart_sMessageEntry[0].ucTxDataLength   = ucTestTxDataLength;
    Test_Uart_sMessageEntry[0].ucTxDataLength = ucTestTxDataLength;
    CddDma_EnableHwTrigger_Param1             = LPSPI1_TX;
    CddDma_EnableHwTrigger_Param2             = TRUE;
    // Populate Rx buffer 
    for (uint8 ucIdx = 1u; ucIdx < 11; ucIdx++)
    {
      Test_Uart_sMessageEntry[0].pucRxData[ucIdx-1u] = 0u;
      Test_Uart_sMessageEntry[0].pucTxData[ucIdx-1u] = 10u + ucIdx * ucIdxIrq;
      CddUart_aucRxDataDMA[0][ucTestTxDataLength + ucIdx-1] = ucIdx* ucIdxIrq;
    }

    /* reset Cb and Dev index due to pointing to invalid location (0xFF) when StopCondition was reached 
    (during normal operation, when stop condition is reached, the Cyclic function resets all indexes */
    if ( (CddUart_asSeqData[0].sStM.ucCbAct == 0xFFu) || (CddUart_asSeqData[0].sStM.ucDevAct == 0xFFu) )
    {
      CddUart_asSeqData[0].sStM.ucCbAct  = 1u;
      CddUart_asSeqData[0].sStM.ucDevAct = 0u;
    }

    // Call IRQ
    CddUart_DMA_RX_CallbackFct();

     //Check the read data and if the action and active device is incremented correctly 
    for (uint8 ucIdx = 1u; ucIdx < 11u; ucIdx++)
    {
      AL_UNITTEST_CHECK(Test_Uart_sMessageEntry[0].pucRxData[ucIdx - 1]     , CddUart_aucRxDataDMA[0][ucTestTxDataLength + ucIdx - 1u],             == );
    }
    // After last device's callback, we enter in stop condition (0xFF)
    if (ucIdxIrq < 6u)
    {// first ucCbAct was made, expect 1 more from first devAct; first device has 2 CB, second has 4 CB
      /* if stop conditions was reached, indexes have 0xFF value */
      if (CddUart_boIsDmaReady[0] == FALSE)
      {
        AL_UNITTEST_CHECK(CddUart_asSeqData[0].sStM.ucCbAct, ((ucIdxIrq <= 1) ? 1u : ucIdxIrq - 2u), == );
        AL_UNITTEST_CHECK(CddUart_asSeqData[0].sStM.ucDevAct, ((ucIdxIrq <= 1) ? 0u : 1u), == );
      }
      else
      {
        AL_UNITTEST_CHECK(CddUart_asSeqData[0].sStM.ucCbAct, 0xFFu, == );
        AL_UNITTEST_CHECK(CddUart_asSeqData[0].sStM.ucDevAct, 0xFFu, == );
      }

    }
    else
    {
      AL_UNITTEST_CHECK(CddUart_asSeqData[0].sStM.ucCbAct                     , 0xFFu,                                          == );
      AL_UNITTEST_CHECK(CddUart_asSeqData[0].sStM.ucDevAct                    , 0xFFu,                                          == );
    }
  }
  AL_UNITTEST_CHECK(CddUart_sMessageEntry[0].ucRxDataLength                 , Test_Uart_sMessageEntry[0].ucRxDataLength,       == );
  AL_UNITTEST_CHECK(CddUart_boIsDmaReady[0]                                 , TRUE,                                            == );
  AL_UNITTEST_CHECK(CddTpsGen2_UartRx_HitCount                              , 6u,                                              == );
  AL_UNITTEST_CHECK(CddTpsGen3_UartRx_HitCount                              , 0u,                                              == );
  AL_UNITTEST_CHECK(CddTps_UartRxDummyIFC2_HitCount                         , 0u,                                              == );
  AL_UNITTEST_CHECK(CddTps_UartRxDummyIFC3_HitCount                         , 0u,                                              == );
  AL_UNITTEST_CHECK(CddDma_EnableHwTrigger_Param1                           , CDDUART_DMA_RX_CHANNEL,                          == );
  AL_UNITTEST_CHECK(CddTps_UartRxDummyIFC3_HitCount                         , FALSE,                                           == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddUart_Init_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check Uart initialization 
///        when the driver has not been initialized yet
///
///    - Test Design Technique: ET(Exploratory Testing )
///
/// - Preconditions:
/// 
/// \input CddUart_ucState                               = CDDUART_STATE_RESET;
/// \input CddUart_sS32K_14X_Registers.uCTRL.sBit.u1RE   = CDDUART_DISABLE_VAL_SET;
/// \input CddUart_sS32K_14X_Registers.uCTRL.sBit.u1TE   = CDDUART_DISABLE_VAL_SET;
/// \input CddUart_sS32K_14X_Registers.uBAUD.sBit.u5OSR  = 0u;
///
/// - Expectations:
///
/// \output CddUart_ucState,                              = CDDUART_STATE_INITIALIZED
/// \output CddUart_sS32K_14X_Registers.uCTRL.sBit.u1RE,  = CDDUART_ENABLE_VAL_SET
/// \output CddUart_sS32K_14X_Registers.uCTRL.sBit.u1TE,  = CDDUART_ENABLE_VAL_SET
/// \output CddUart_sS32K_14X_Registers.uBAUD.sBit.u5OSR, = 31U
///
//-----------------------------------------------------------------------------
void Mt_CddUart_Init_TestCase_1()
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddUart_ucState                               = CDDUART_STATE_RESET;
  CddUart_sS32K_14X_Registers.uCTRL.sBit.u1RE   = CDDUART_DISABLE_VAL_SET;
  CddUart_sS32K_14X_Registers.uCTRL.sBit.u1TE   = CDDUART_DISABLE_VAL_SET;
  CddUart_sS32K_14X_Registers.uBAUD.sBit.u5OSR  = 0u;

  //Step 3) Call FUT
  CddUart_Init();
  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(CddUart_ucState,                              CDDUART_STATE_INITIALIZED,             == );
  AL_UNITTEST_CHECK(CddUart_sS32K_14X_Registers.uCTRL.sBit.u1RE,  CDDUART_ENABLE_VAL_SET,                     == );
  AL_UNITTEST_CHECK(CddUart_sS32K_14X_Registers.uCTRL.sBit.u1TE,  CDDUART_ENABLE_VAL_SET,                     == );
  AL_UNITTEST_CHECK(CddUart_sS32K_14X_Registers.uBAUD.sBit.u5OSR, 31U,                                        == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddUart_Init_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check Uart initialization 
///        when the driver has been already initialized 
///
///    - Test Design Technique: ET(Exploratory Testing )
///
/// - Preconditions:
/// 
/// \input CddUart_ucState                               = CDDUART_STATE_INITIALIZED;
/// \input CddUart_sS32K_14X_Registers.uCTRL.sBit.u1RE   = CDDUART_DISABLE_VAL_SET;
/// \input CddUart_sS32K_14X_Registers.uCTRL.sBit.u1TE   = CDDUART_DISABLE_VAL_SET;
/// \input CddUart_sS32K_14X_Registers.uBAUD.sBit.u5OSR  = 0u;
///
/// - Expectations:
///
/// \output CddUart_ucState,                              = CDDUART_STATE_INITIALIZED
/// \output CddUart_sS32K_14X_Registers.uCTRL.sBit.u1RE,  = CDDUART_DISABLE_VAL_SET
/// \output CddUart_sS32K_14X_Registers.uCTRL.sBit.u1TE,  = CDDUART_DISABLE_VAL_SET
/// \output CddUart_sS32K_14X_Registers.uBAUD.sBit.u5OSR, = 0U
///
//-----------------------------------------------------------------------------
void Mt_CddUart_Init_TestCase_2()
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddUart_ucState                               = CDDUART_STATE_INITIALIZED;
  CddUart_sS32K_14X_Registers.uCTRL.sBit.u1RE   = CDDUART_DISABLE_VAL_SET;
  CddUart_sS32K_14X_Registers.uCTRL.sBit.u1TE   = CDDUART_DISABLE_VAL_SET;
  CddUart_sS32K_14X_Registers.uBAUD.sBit.u5OSR  = 0u;

  //Step 3) Call FUT
  CddUart_Init();
  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(CddUart_ucState,                              CDDUART_STATE_INITIALIZED,             == );
  AL_UNITTEST_CHECK(CddUart_sS32K_14X_Registers.uCTRL.sBit.u1RE,  CDDUART_DISABLE_VAL_SET,                    == );
  AL_UNITTEST_CHECK(CddUart_sS32K_14X_Registers.uCTRL.sBit.u1TE,  CDDUART_DISABLE_VAL_SET,                    == );
  AL_UNITTEST_CHECK(CddUart_sS32K_14X_Registers.uBAUD.sBit.u5OSR, 0U,                                         == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddUart_Init
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Check Uart initialization 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected Test Results : All contained test cases are passed
///
//-----------------------------------------------------------------------------
void Mt_CddUart_Init(void)
{
  Mt_CddUart_Init_TestCase_1();
  Mt_CddUart_Init_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddUart_DeInit_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check Uart deinitialization 
///        when the driver has the state different form STATE_RESET
///
///    - Test Design Technique: ET(Exploratory Testing )
///
/// - Preconditions:
/// 
/// \input CddUart_ucState                               = CDDUART_STATE_SINGLE_OPERATION;
/// \input CddUart_sS32K_14X_Registers.uCTRL.sBit.u1RE   = CDDUART_ENABLE_VAL_SET;
/// \input CddUart_sS32K_14X_Registers.uCTRL.sBit.u1TE   = CDDUART_ENABLE_VAL_SET;
/// \input CddUart_sS32K_14X_Registers.uBAUD.sBit.u5OSR  = 31u;
///
/// - Expectations:
///
/// \output CddUart_ucState,                              = CDDUART_STATE_RESET
/// \output CddUart_sS32K_14X_Registers.uCTRL.sBit.u1RE,  = CDDUART_DISABLE_VAL_SET
/// \output CddUart_sS32K_14X_Registers.uCTRL.sBit.u1TE,  = CDDUART_DISABLE_VAL_SET
/// \output CddUart_sS32K_14X_Registers.uBAUD.sBit.u5OSR, = 31U
///
//-----------------------------------------------------------------------------
void Mt_CddUart_DeInit_TestCase_1()
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddUart_ucState                               = CDDUART_STATE_SINGLE_OPERATION;
  CddUart_sS32K_14X_Registers.uCTRL.sBit.u1RE   = CDDUART_ENABLE_VAL_SET;
  CddUart_sS32K_14X_Registers.uCTRL.sBit.u1TE   = CDDUART_ENABLE_VAL_SET;
  CddUart_sS32K_14X_Registers.uBAUD.sBit.u5OSR  = 31u;

  //Step 3) Call FUT
  CddUart_DeInit();
  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(CddUart_ucState,                                  CDDUART_STATE_RESET,                == );
  AL_UNITTEST_CHECK(CddUart_sS32K_14X_Registers.uCTRL.sBit.u1RE,      CDDUART_DISABLE_VAL_SET,            == );
  AL_UNITTEST_CHECK(CddUart_sS32K_14X_Registers.uCTRL.sBit.u1TE,      CDDUART_DISABLE_VAL_SET,            == );
  AL_UNITTEST_CHECK(CddUart_sS32K_14X_Registers.uBAUD.sBit.u5OSR,     31U,                                == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddUart_DeInit_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check Uart deinitialization 
///        when the driver has the state STATE_RESET
///
///    - Test Design Technique: ET(Exploratory Testing )
///
/// - Preconditions:
/// 
/// \input CddUart_ucState                               = CDDUART_STATE_RESET;
/// \input CddUart_sS32K_14X_Registers.uCTRL.sBit.u1RE   = CDDUART_DISABLE_VAL_SET;
/// \input CddUart_sS32K_14X_Registers.uCTRL.sBit.u1TE   = CDDUART_DISABLE_VAL_SET;
/// \input CddUart_sS32K_14X_Registers.uBAUD.sBit.u5OSR  = 31u;
///
/// - Expectations:
///
/// \output CddUart_ucState,                              = CDDUART_STATE_RESET
/// \output CddUart_sS32K_14X_Registers.uCTRL.sBit.u1RE,  = CDDUART_DISABLE_VAL_SET
/// \output CddUart_sS32K_14X_Registers.uCTRL.sBit.u1TE,  = CDDUART_DISABLE_VAL_SET
/// \output CddUart_sS32K_14X_Registers.uBAUD.sBit.u5OSR, = 31U
///
//-----------------------------------------------------------------------------
void Mt_CddUart_DeInit_TestCase_2()
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddUart_ucState                               = CDDUART_STATE_RESET;
  CddUart_sS32K_14X_Registers.uCTRL.sBit.u1RE   = CDDUART_DISABLE_VAL_SET;
  CddUart_sS32K_14X_Registers.uCTRL.sBit.u1TE   = CDDUART_DISABLE_VAL_SET;
  CddUart_sS32K_14X_Registers.uBAUD.sBit.u5OSR  = 31u;

  //Step 3) Call FUT
  CddUart_DeInit();
  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(CddUart_ucState,                                CDDUART_STATE_RESET,                == );
  AL_UNITTEST_CHECK(CddUart_sS32K_14X_Registers.uCTRL.sBit.u1RE,    CDDUART_DISABLE_VAL_SET,            == );
  AL_UNITTEST_CHECK(CddUart_sS32K_14X_Registers.uCTRL.sBit.u1TE,    CDDUART_DISABLE_VAL_SET,            == );
  AL_UNITTEST_CHECK(CddUart_sS32K_14X_Registers.uBAUD.sBit.u5OSR,   31U,                                == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddUart_DeInit
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Check Uart deinitialization 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected Test Results : All contained test cases are passed
///
//-----------------------------------------------------------------------------
void Mt_CddUart_DeInit(void)
{
  Mt_CddUart_DeInit_TestCase_1();
  Mt_CddUart_DeInit_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddUart_ProcessSequence
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check ProcessSequence 
///        when ucCycleCnt is 1 and when eIfcCyclicMode is out of range
///
///    - Test Design Technique: ET(Exploratory Testing )
///
/// - Preconditions:
/// 
/// \input CddUart_asSeqHandler[2u].ucCycleCnt   = 1u;
/// \input CddUart_asSeqHandler[2u].ucSeqContext = CDDUART_SEQ_CONTEXT_INITIALIZED_MSK;
/// \input CddUart_asIfcCfg[1].eIfcCyclicMode    = CddUart_eIfcCyclicMode_DMA+1u;
/// \input 
///
/// - Expectations:
///
/// \output CddUart_asSeqHandler[2u].ucCycleCnt  = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddUart_ProcessSequence()
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddUart_asSeqHandler[2u].ucCycleCnt   = 1u;
  CddUart_asSeqHandler[2u].ucSeqContext = CDDUART_SEQ_CONTEXT_INITIALIZED_MSK;
  CddUart_asIfcCfg[1].eIfcCyclicMode    = CddUart_eIfcCyclicMode_DMA+1u;

  //Step 3) Call FUT
  for (uint8 ucIdx = 0u; ucIdx < 2u; ucIdx++)
  {
    CddUart_ProcessSequence(2);
  }
  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(CddUart_asSeqHandler[2u].ucCycleCnt ,                                0u,                == );
}

// ----------------------------------------------------------------------------
// CddUart_S32K_14X Unit Test Cases 
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Mt_CddUart_StartTransfer_Deriv
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check transfer function 
///        when transfer type is different from LPUART1
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions:
/// 
/// \input CddDma_StartJob_Param2.pulSourceAddress = NULL_PTR;
/// \input CddDma_StartJob_Param2.pulTargetAddress = NULL_PTR;
/// \input CddDma_StartJob_Param2.unRepetitions    = 0u;
/// \input CddDma_StartJob_HitCount                = 0u;
///
/// - Expectations:
///
/// \output CddDma_StartJob_HitCount = 0u;  CddDma_StartJob function is called only for LPUART1 
/// \output CddDma_StartJob param will be updated only for LPUART1 
///
//-----------------------------------------------------------------------------
void Mt_CddUart_StartTransfer_Deriv()
{
  //Step 1) Set pre - conditions
  uint32 ucExpectedVal[2][5] = 
  { //CddDma_StartJob_HitCount      pulSourceAddress                          pulTargetAddress                                unRepetitions                            CddDma_StartJob_Param3
    {0u                           , NULL_PTR                                , NULL_PTR                                      , NULL_PTR                                , NULL_PTR              },
    {2u                           , &CddUart_sMessageEntry[0].pucTxData[0]  , &UART_Register_UnitTest[1].uDATA.u32Register  , CddUart_sMessageEntry[0].ucTxDataLength , NULL_PTR              },
  
  };

  for (uint8 ucIdx = 0u; ucIdx < 2u; ucIdx++)
  {
    CddDma_StartJob_Param2.pulSourceAddress = NULL_PTR;
    CddDma_StartJob_Param2.pulTargetAddress = NULL_PTR;
    CddDma_StartJob_Param2.unRepetitions    = 0u;
    CddDma_StartJob_HitCount                = 0u;
    //Step 2) Assign Input values

    //Step 3) Call FUT
    CddUart_StartTransfer_Deriv(ucIdx,
                              (uint32*)&CddUart_sMessageEntry[0].pucTxData[0],  // PRQA S 310, 3305 //the cast is allowed since we need memory address
                              (uint32*)&CddUart_aucRxDataDMA[0][0],         // PRQA S 310, 3305 //the cast is allowed since we need memory address
                              CddUart_sMessageEntry[0].ucTxDataLength,
                              CddUart_sMessageEntry[0].ucRxDataLength);

    //Step 4) Check expected output value
    AL_UNITTEST_CHECK(CddDma_StartJob_HitCount,                              ucExpectedVal[ucIdx][0],         == );
    AL_UNITTEST_CHECK(CddDma_StartJob_Param2.pulSourceAddress,               ucExpectedVal[ucIdx][1],         == );
    AL_UNITTEST_CHECK(CddDma_StartJob_Param2.pulTargetAddress,               ucExpectedVal[ucIdx][2],         == );
    AL_UNITTEST_CHECK(CddDma_StartJob_Param2.unRepetitions,                  ucExpectedVal[ucIdx][3],         == );
    AL_UNITTEST_CHECK(CddDma_StartJob_Param3,                                ucExpectedVal[ucIdx][4],         == );
  }

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddUart_TransferCompleteDMA_Deriv
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check transfer function 
///        when transfer type is different from LPUART1
///
///    - Test Design Technique: ET(Exploratory Testing )
///
/// - Preconditions:
/// 
/// \input CddDma_IsJobCompleted_RetVal  = TRUE
///
/// - Expectations:
///
/// \output CddDma_IsJobCompleted is called when ucIfc == CDDUART_IFC1; CddDma_IsJobCompleted returns TRUE
/// \output CddDma_IsJobCompleted is not called when ucIfc != CDDUART_IFC1; boRetVal == FALSE
///
//-----------------------------------------------------------------------------
void Mt_CddUart_TransferCompleteDMA_Deriv()
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  boolean boExpectedRet[2]      = { FALSE, TRUE };
  CddDma_IsJobCompleted_RetVal  = TRUE;

  for (uint8 ucIdx = 0u; ucIdx < 2u; ucIdx++)
  {
    boolean boRetVal;

    //Step 3) Call FUT
    boRetVal = CddUart_TransferCompleteDMA_Deriv(ucIdx);

    //Step 4) Check expected output value
    AL_UNITTEST_CHECK(boRetVal, boExpectedRet[ucIdx], == );
  }

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddUart_FillTxFifo_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check Fill Fifo function 
///        when data is NULL_PTR
///
///    - Test Design Technique: ET(Exploratory Testing )
///
/// - Preconditions:
/// 
/// \input UART_Register_UnitTest[0].uDATA.sBit.u1R0T0 = 1u
/// \input UART_Register_UnitTest[0].uDATA.sBit.u1R2T2 = 1u
/// \input UART_Register_UnitTest[0].uDATA.sBit.u1R4T4 = 1u
/// \input UART_Register_UnitTest[0].uDATA.sBit.u1R6T6 = 1u
///
/// - Expectations:
///
/// \output UART_Register_UnitTest[0].uDATA.u32Register = 0x55;
///
//-----------------------------------------------------------------------------
void Mt_CddUart_FillTxFifo_TestCase_1()
{
  //Step 1) Set pre - conditions
  
  UART_Register_UnitTest[0].uDATA.sBit = (tsCddMlcUart_NXP_DATA)  {
                                                                  .u1R0T0 = 1u,
                                                                  .u1R2T2 = 1u,
                                                                  .u1R4T4 = 1u,
                                                                  .u1R6T6 = 1u,
                                                                  };
  //Step 2) Assign Input values

  //Step 3) Call FUT
  CddUart_FillTxFifo(0, NULL_PTR, 1u);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(UART_Register_UnitTest[0].uDATA.u32Register, 0x55u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddUart_FillTxFifo_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check Fill Fifo function 
///        when data is NULL_PTR
///
///    - Test Design Technique: ET(Exploratory Testing )
///
/// - Preconditions:
/// 
/// \input ucTestData                                   = 0x11u;
/// \input UART_Register_UnitTest[0].uDATA.sBit.u1R0T0  = 0u
/// \input UART_Register_UnitTest[0].uDATA.sBit.u1R1T1  = 1u
/// \input UART_Register_UnitTest[0].uDATA.sBit.u1R2T2  = 1u
/// \input UART_Register_UnitTest[0].uDATA.sBit.u1R3T3  = 1u
/// \input UART_Register_UnitTest[0].uDATA.sBit.u1R4T4  = 0u
/// \input UART_Register_UnitTest[0].uDATA.sBit.u1R5T5  = 1u
/// \input UART_Register_UnitTest[0].uDATA.sBit.u1R6T6  = 1u
///
/// - Expectations:
///
/// \output UART_Register_UnitTest[0].uDATA.u32Register = 0x11u;
///
//-----------------------------------------------------------------------------
void Mt_CddUart_FillTxFifo_TestCase_2()
{
  //Step 1) Set pre - conditions
  uint8 ucTestData                            = 0x11u;
  UART_Register_UnitTest[0].uDATA.sBit = (tsCddMlcUart_NXP_DATA){
                                                                .u1R0T0 = 0u,
                                                                .u1R1T1 = 1u,
                                                                .u1R2T2 = 1u,
                                                                .u1R3T3 = 1u,
                                                                .u1R4T4 = 0u,
                                                                .u1R5T5 = 1u,
                                                                .u1R6T6 = 1u,
                                                                };
  //Step 2) Assign Input values

  //Step 3) Call FUT
  CddUart_FillTxFifo(0, &ucTestData, 1u);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(UART_Register_UnitTest[0].uDATA.u32Register, 0x11u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddUart_FillTxFifo
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Check Fifo register fill 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected Test Results : All contained test cases are passed
///
//-----------------------------------------------------------------------------
void Mt_CddUart_FillTxFifo(void)
{
  Mt_CddUart_FillTxFifo_TestCase_1();
  Mt_CddUart_FillTxFifo_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddUart_ReadRxFifo_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check Read Fifo function 
///        when data is NULL_PTR
///
///    - Test Design Technique: ET(Exploratory Testing )
///
/// - Preconditions:
/// 
/// \input UART_Register_UnitTest[0].uDATA.u32Register = 0x55u;
///
/// - Expectations:
///
/// \output UART_Register_UnitTest[0].uDATA.u32Register = 0x55;
///
//-----------------------------------------------------------------------------
void Mt_CddUart_ReadRxFifo_TestCase_1()
{
  //Step 1) Set pre - conditions
  
  UART_Register_UnitTest[0].uDATA.u32Register = 0x55u;
  //Step 2) Assign Input values

  //Step 3) Call FUT
  CddUart_ReadRxFifo(0, NULL_PTR, 1u);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(UART_Register_UnitTest[0].uDATA.u32Register, 0x55u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddUart_ReadRxFifo_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check Read Fifo function 
///        when data is NULL_PTR
///
///    - Test Design Technique: ET(Exploratory Testing )
///
/// - Preconditions:
/// 
/// \input ucTestData                                   = 0x11u;
/// \input UART_Register_UnitTest[0].uDATA.u32Register  = 0x55u;
///
/// - Expectations:
///
/// \output ucTestData = 0x55u;
///
//-----------------------------------------------------------------------------
void Mt_CddUart_ReadRxFifo_TestCase_2()
{
  //Step 1) Set pre - conditions
  uint8 ucTestData                           = 0x11u;
  UART_Register_UnitTest[0].uDATA.u32Register = 0x55u;
  //Step 2) Assign Input values

  //Step 3) Call FUT
  CddUart_ReadRxFifo(0, &ucTestData, 1u);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ucTestData,      0x55u,       == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddUart_ReadRxFifo
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Check read of Fifo register  
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected Test Results : All contained test cases are passed
///
//-----------------------------------------------------------------------------
void Mt_CddUart_ReadRxFifo(void)
{
  Mt_CddUart_ReadRxFifo_TestCase_1();
  Mt_CddUart_ReadRxFifo_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddUart_RxIntEnable
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test CddUart_RxIntEnable 
///        ! for now this function is not doing anything 
///
///    - Test Design Technique: ET(Exploratory Testing )
///
/// - Preconditions:
/// 
/// \input no input
///
/// - Expectations:
///
/// \output  No expected value because function is added due to architecture design to support interrupt on incoming data, but not used in this project
///
//-----------------------------------------------------------------------------
void Mt_CddUart_RxIntEnable()
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  //Step 3) Call FUT
  CddUart_RxIntEnable(0);

  //Step 4) Check expected output value
  // No expected value because function is added due to architecture design to support interrupt on incoming data, but not used in this project
}

// ----------------------------------------------------------------------------
// RUN Test Cases
//-----------------------------------------------------------------------------
void ALUnitTest_AddTests(void)
{
  // CddUart
  ALUnitTest_AddFunction("Mt_riCddUartInit"                       , Mt_riCddUartInit                        );
  ALUnitTest_AddFunction("Mt_rpCddUart_Cycle"                     , Mt_rpCddUart_Cycle                      );
  ALUnitTest_AddFunction("Mt_CddUart_DMA_RX_CallbackFct"          , Mt_CddUart_DMA_RX_CallbackFct           );
  ALUnitTest_AddFunction("Mt_CddUart_Init"                        , Mt_CddUart_Init                         );
  ALUnitTest_AddFunction("Mt_CddUart_DeInit"                      , Mt_CddUart_DeInit                       );
  ALUnitTest_AddFunction("Mt_CddUart_ProcessSequence"             , Mt_CddUart_ProcessSequence              );
  // CddUart_S32K_14X
  ALUnitTest_AddFunction("Mt_CddUart_StartTransfer_Deriv"         , Mt_CddUart_StartTransfer_Deriv          );
  ALUnitTest_AddFunction("Mt_CddUart_TransferCompleteDMA_Deriv"   , Mt_CddUart_TransferCompleteDMA_Deriv    );
  ALUnitTest_AddFunction("Mt_CddUart_FillTxFifo"                  , Mt_CddUart_FillTxFifo                   );
  ALUnitTest_AddFunction("Mt_CddUart_ReadRxFifo"                  , Mt_CddUart_ReadRxFifo                   );
  ALUnitTest_AddFunction("Mt_CddUart_RxIntEnable"                 , Mt_CddUart_RxIntEnable                  );
}


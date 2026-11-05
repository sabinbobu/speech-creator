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
/// \brief  Unit Test Cases for SBC complex device driver
///
/// \author Kai Zhao  ALDE-RT (zhk2rt)
///         mailTo:kai.zhao[at]marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// Includes
//=============================================================================

#include <ALUnitTest_UserInterface.h>

// Headers of the unit test module
#include "Test.h"

// Stub headers
#include "Test_Stubs.h"

//=============================================================================
// Test Cases
//=============================================================================

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_Save_WK_STAT_0
///
/// \Functional Safety: ASIL-B
///
/// \Test methods:
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:
///        Check if the CddTle94x1_Save_WK_STAT_0() reads register WK_STAT_0 via SPI and saves its value in
///        the data mirror.
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. Every DT-entry represents a different Test Case interaction.
///      - DT-Info:
///         - Inputs:
///           - Mt_uclen: Buffer length provided to the Spi driver
///           - Mt_boReturn[]: Buffer return value provided to the Spi driver
///           - Mt_unRxData[]: Buffer data provided to the Spi driver
///         - Outputs:
///           - boReturn: Return value of this FUT
///           - ucRxData: the saved data of register WK_STAT_0
///
///    - Preconditions: none
///
///    - Expected test results:
///        - All conditions and assigned values of the DT need to be reached and passed.
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_Save_WK_STAT_0(void)
{
  boolean boReturn;

  // test step
  int nStep;
  // point to RxData
  uint16* punRxData;
  // point to Return
  boolean* pboReturn;

  typedef struct
  {
    uint8   Mt_uclen;
    boolean Mt_boReturn[2];
    uint16  Mt_unRxData[2];
  } tSetValues_FixData;

  typedef struct
  {
    boolean boReturn;
    uint16 ucRxData;
  } tCheckValues_FixData;

  typedef struct
  {
    tSetValues_FixData SetValues;
    tCheckValues_FixData CheckValues;
  } tUtCddSbc_TestSteps_FixData;

  static const tUtCddSbc_TestSteps_FixData aTestSteps[] =
  {
    //                  Intputs                         ||   Outputs
    //       Mt_uclen,  Mt_boReturn,   Mt_unRxData;     || boReturn, ucRxData ;
    /* 0 */{ { 1, {  TRUE, FALSE }, { 0xAAAA, 0xFFFF } }, {  TRUE, 0xAA } },
    /* 1 */{ { 2, { FALSE,  TRUE }, { 0xAAAA, 0xBBBB } }, {  TRUE, 0xBB } },
    /* 2 */{ { 2, { FALSE, FALSE }, { 0xAAAA, 0xBBBB } }, { FALSE, 0xBB } },
    /* 3 */{ { 1, { TRUE,   TRUE }, { 0x0146, 0xCCCC } }, {  TRUE, 0x01 } },
  };

  const int   nNrSteps = sizeof(aTestSteps) / sizeof(tUtCddSbc_TestSteps_FixData);

  for (nStep = 0; nStep < nNrSteps; nStep++)
  {
    //Step1: set return and RxData value in SPI-Mocks
    punRxData = (uint16*)&aTestSteps[nStep].SetValues.Mt_unRxData;
    pboReturn = (boolean*)&aTestSteps[nStep].SetValues.Mt_boReturn;

    Mt_CddSpi_SPIRegisterRxDataBuffer(aTestSteps[nStep].SetValues.Mt_uclen, punRxData, pboReturn);

    //Step2: call function and get the return value
    boReturn = CddTle94x1_Save_WK_STAT_0();

    //Step3: compare the return and received RxData value with the check values in TestSteps
    AL_UNITTEST_CHECK(boReturn, aTestSteps[nStep].CheckValues.boReturn, == );
    AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.StatRx.WK_STAT_0_Register.uData.ucWord, aTestSteps[nStep].CheckValues.ucRxData, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_Save_SUP_STAT_0
///
/// \Functional Safety: NA
///
/// \Test methods:
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:
///        Check if the CddTle94x1_Save_SUP_STAT_0() reads register SUP_STAT_0 via SPI and saves its value in
///        the data mirror.
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. Every DT-entry represents a different Test Case interaction.
///      - DT-Info:
///         - Inputs:
///           - Mt_uclen: Buffer length provided to the Spi driver
///           - Mt_boReturn[]: Buffer return value provided to the Spi driver
///           - Mt_unRxData[]: Buffer data provided to the Spi driver
///         - Outputs:
///           - boReturn: Return value of this FUT
///           - ucRxData: the saved data of register SUP_STAT_0
///
///    - Preconditions: none
///
///    - Expected test results:
///        - All conditions and assigned values of the DT need to be reached and passed.
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_Save_SUP_STAT_0(void)
{
  boolean boReturn;

  // test step
  int nStep;
  // point to RxData
  uint16* punRxData;
  // point to Return
  boolean* pboReturn;

  typedef struct
  {
    uint8   Mt_uclen;
    boolean Mt_boReturn[2];
    uint16  Mt_unRxData[2];
  } tSetValues_FixData;

  typedef struct
  {
    boolean boReturn;
    uint16 ucRxData;
  } tCheckValues_FixData;

  typedef struct
  {
    tSetValues_FixData SetValues;
    tCheckValues_FixData CheckValues;
  } tUtCddSbc_TestSteps_FixData;

  static const tUtCddSbc_TestSteps_FixData aTestSteps[] =
  { //                     Intputs                          ||     Outputs
    //       Mt_uclen,    Mt_boReturn,     Mt_unRxData;     || boReturn, ucRxData ;
    /* 0 */{ { 1,   { TRUE,    FALSE }, { 0xAAAA, 0xFFFF } }, {  TRUE,  0xAA } },
    /* 1 */{ { 2,   { FALSE,    TRUE }, { 0xAAAA, 0xBBBB } }, {  TRUE,  0xBB } },
    /* 2 */{ { 2,   { FALSE,   FALSE }, { 0xAAAA, 0xBBBB } }, { FALSE,  0xBB } },
    /* 3 */{ { 2,   { FALSE,    TRUE }, { 0xAAAA, 0x8041 } }, {  TRUE,  0x80 } },
  };

  const int   nNrSteps = sizeof(aTestSteps) / sizeof(tUtCddSbc_TestSteps_FixData);

  for (nStep = 0; nStep < nNrSteps; nStep++)
  {
    //Step1: set return and RxData value in SPI-Mocks
    punRxData = (uint16*)&aTestSteps[nStep].SetValues.Mt_unRxData;
    pboReturn = (boolean*)&aTestSteps[nStep].SetValues.Mt_boReturn;

    Mt_CddSpi_SPIRegisterRxDataBuffer(aTestSteps[nStep].SetValues.Mt_uclen, punRxData, pboReturn);

    //Step2: call function and get the return value
    boReturn = CddTle94x1_Save_SUP_STAT_0();

    //Step3: compare the return and received RxData value with the check values in TestSteps
    AL_UNITTEST_CHECK(boReturn, aTestSteps[nStep].CheckValues.boReturn, == );
    AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.StatRx.SUP_STAT_0_Register.uData.ucWord, aTestSteps[nStep].CheckValues.ucRxData, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_InitStatRead
///
/// \Functional Safety: NA
///
/// \Test methods:
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:
///        Check if the CddTle94x1_InitStatRead() reads status registers in the initialization sussessful.
///        Check the error flag CddTle94x1_sErrorType.boInitStatRead.
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. Every DT-entry represents a different Test Case interaction.
///      - DT-Info:
///         - Inputs:
///           - Mt_uclen: Buffer length provided to the Spi driver
///           - Mt_boReturn[]: Buffer return value provided to the Spi driver
///           - Mt_unRxData[]: Buffer data provided to the Spi driver
///         - Outputs:
///           - boReturn: Return value of this FUT
///           - boErrorType_InitStatRead: Error flag
///
///    - Preconditions: none
///
///    - Expected test results:
///        - All conditions and assigned values of the DT need to be reached and passed.
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_InitStatRead(void)
{
  boolean boReturn;
  // test step
  int nStep;
  // point to RxData
  uint16* punRxData;
  // point to Return
  boolean* pboReturn;

  typedef struct
  {
    uint8   Mt_uclen;
    boolean Mt_boReturn[4];
    uint16  Mt_unRxData[4];
  } tSetValues_FixData;

  typedef struct
  {
    boolean boReturn;
    boolean boErrorType_InitStatRead;
  } tCheckValues_FixData;

  typedef struct
  {
    tSetValues_FixData SetValues;
    tCheckValues_FixData CheckValues;
  } tUtCddSbc_TestSteps_FixData;

  static const tUtCddSbc_TestSteps_FixData aTestSteps[] =
  {   //                                            Intputs                           ||     Outputs
    //      Mt_uclen,     Mt_boReturn,                       Mt_unRxData;             || boReturn, boErrorType
    /* 0 */{ { 4, {  TRUE,  TRUE,  TRUE,  TRUE }, { 0x0046, 0x8041, 0xFFFF, 0xFFFF } }, {  TRUE,   FALSE } },
    /* 1 */{ { 4, { FALSE,  TRUE,  TRUE,  TRUE }, { 0x00AA, 0x0046, 0x8041, 0xFFFF } }, {  TRUE,   FALSE } },
    /* 3 */{ { 4, { FALSE, FALSE, FALSE,  TRUE }, { 0x00AA, 0x00BB, 0xFFFF, 0x0046 } }, { FALSE,    TRUE } },
    /* 4 */{ { 4, { FALSE,  TRUE, FALSE, FALSE }, { 0x00AA, 0x00BB, 0x00CC, 0xDDDD } }, { FALSE,    TRUE } },
    /* 5 */{ { 4, { FALSE,  TRUE, FALSE,  TRUE }, { 0x00AA, 0x0046, 0x00CC, 0x8041 } }, {  TRUE,   FALSE } },
  };

  const int   nNrSteps = sizeof(aTestSteps) / sizeof(tUtCddSbc_TestSteps_FixData);

  for (nStep = 0; nStep < nNrSteps; nStep++)
  {
    //Step1: set return and RxData value in SPI-Mocks
    punRxData = (uint16*)&aTestSteps[nStep].SetValues.Mt_unRxData;
    pboReturn = (boolean*)&aTestSteps[nStep].SetValues.Mt_boReturn;

    Mt_CddSpi_SPIRegisterRxDataBuffer(aTestSteps[nStep].SetValues.Mt_uclen, punRxData, pboReturn);

    //Step2: call function and get the return value
    boReturn = CddTle94x1_InitStatRead();

    //Step3: compare the return and error flag with the check values in TestSteps
    AL_UNITTEST_CHECK(boReturn, aTestSteps[nStep].CheckValues.boReturn, == );
    AL_UNITTEST_CHECK(CddTle94x1_sErrorType.boInitStatRead, aTestSteps[nStep].CheckValues.boErrorType_InitStatRead, == );
  }
}


////-----------------------------------------------------------------------------
///// \Test Case : Mt_CddTle94x1_InitSettings
/////
///// \Functional Safety: NA
/////
///// \Test methods:
/////        - Requirements-based test
/////
///// \Test Case Description
/////    - Test subject:
/////        Check if the CddTle94x1_InitSettings() writes the commands to control registers in the initialization sussessful.
/////        Check the error flag CddTle94x1_sErrorType.boInitCtrlWrite and the SPI data mirror.
/////
/////    - Test Design Technique: DT (Decision Table)
/////        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
/////        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
/////        set by the FUT. Every DT-entry represents a different Test Case interaction.
/////      - DT-Info:
/////         - Inputs:
/////           - Mt_uclen: Buffer length provided to the Spi driver
/////           - Mt_boReturn[]: Buffer return value provided to the Spi driver
/////           - Mt_unRxData[]: Buffer data provided to the Spi driver
/////         - Outputs:
/////           - boInitCtrlWrite: Return value
/////           - ucCtrlRxData[]: SPI data mirror
/////
/////    - Preconditions: none
/////
/////    - Expected test results:
/////        - All conditions and assigned values of the DT need to be reached and passed.
/////
////-----------------------------------------------------------------------------
void Mt_CddTle94x1_InitSettings(void)
{
  // test step
  int nStep;
  // point to RxData
  uint16* punRxData;
  // point to Return
  boolean* pboReturn;

  typedef struct
  {
    uint8   Mt_uclen;
    boolean Mt_boReturn[22];
    uint16  Mt_unRxData[22];
  } tSetValues_FixData;

  typedef struct
  {
    boolean boInitCtrlWrite;
    uint8  ucCtrlRxData[11];
  } tCheckValues_FixData;

  typedef struct
  {
    tSetValues_FixData SetValues;
    tCheckValues_FixData CheckValues;
  } tUtCddSbc_TestSteps_FixData;

  static const tUtCddSbc_TestSteps_FixData aTestSteps[] =
  { //                                             Intputs                                                                                                                                                                                                                           ||                Outputs
    //        Mt_uclen,                             Mt_boReturn,                                                                                        Mt_unRxData;                                                                                                                 ||  boInitCtrlWrite,     ucCtrlRxData
    /* 0 */{ { 22, { TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE }, { 0x0004, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000, 0x0304, 0x0304, 0x0404, 0x0404, 0x0404, 0x0C04, 0x0004, 0x0404, 0x1004, 0x1004, 0x0004, 0x0004, 0x0604,  0x0604, 0x0C0C, 0x0C0C } }, { FALSE, { 0x00, 0x00, 0x00, 0x03, 0x04, 0x0C, 0x04, 0x10, 0x00, 0x06, 0x0C } } },
    /* 1 */{ { 22, { TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE }, { 0x0004, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000, 0x0304, 0x0304, 0x0404, 0x0404, 0x0404, 0x0C04, 0x0004, 0x0404, 0x1004, 0x1004, 0x0004, 0x0004, 0x0604,  0x0604, 0x0404, 0x0204 } }, {  TRUE, { 0x00, 0x00, 0x00, 0x03, 0x04, 0x0C, 0x04, 0x10, 0x00, 0x06, 0x00 } } },
    /* 2 */{ { 22, { TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE }, { 0x0004, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000, 0x0304, 0x0304, 0x0404, 0x0404, 0x0404, 0x0C04, 0x0004, 0x0404, 0x1004, 0x1004, 0x0004, 0x0004, 0x0604,  0x2004, 0x0404, 0x0404 } }, {  TRUE, { 0x00, 0x00, 0x00, 0x03, 0x04, 0x0C, 0x04, 0x10, 0x00, 0x06, 0x00 } } },
    /* 3 */{ { 22, { TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE }, { 0x0004, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000, 0x0304, 0x0304, 0x0404, 0x0404, 0x0404, 0x0C04, 0x0004, 0x0804, 0x1004, 0x1004, 0x0004, 0x0804, 0x0604,  0x0604, 0x0404, 0x0404 } }, {  TRUE, { 0x00, 0x00, 0x00, 0x03, 0x04, 0x0C, 0x00, 0x10, 0x00, 0x06, 0x00 } } },
    /* 4 */{ { 22, { TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE }, { 0x0004, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000, 0x0304, 0x0304, 0x0404, 0x0404, 0x0404, 0x0A04, 0x0004, 0x0404, 0x1004, 0x1004, 0x0004, 0x0004, 0x0604,  0x0604, 0x0404, 0x0404 } }, {  TRUE, { 0x00, 0x00, 0x00, 0x03, 0x04, 0x00, 0x04, 0x10, 0x00, 0x06, 0x00 } } },
    /* 0 */{ { 22, { TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE }, { 0x0004, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000, 0x0304, 0x0304, 0x0404, 0x0204, 0x0404, 0x0C04, 0x0004, 0x0404, 0x1004, 0x1004, 0x0004, 0x0004, 0x0604,  0x0604, 0x0404, 0x0404 } }, {  TRUE, { 0x00, 0x00, 0x00, 0x03, 0x00, 0x0C, 0x04, 0x10, 0x00, 0x06, 0x00 } } },
    /* 0 */{ { 22, { TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE }, { 0x0004, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000, 0x0304, 0x0104, 0x0404, 0x0404, 0x0404, 0x0C04, 0x0004, 0x0404, 0x1004, 0x1004, 0x0004, 0x0004, 0x0604,  0x0604, 0x0404, 0x0404 } }, {  TRUE, { 0x00, 0x00, 0x00, 0x00, 0x04, 0x0C, 0x04, 0x10, 0x00, 0x06, 0x00 } } },
    /* 0 */{ { 22, { TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE }, { 0x0004, 0x0004, 0x0000, 0x0000, 0x0000, 0x0A00, 0x0304, 0x0304, 0x0404, 0x0404, 0x0404, 0x0C04, 0x0004, 0x0404, 0x1004, 0x1004, 0x0004, 0x0004, 0x0604,  0x0604, 0x0404, 0x0404 } }, {  TRUE, { 0x00, 0x00, 0x00, 0x03, 0x04, 0x0C, 0x04, 0x10, 0x00, 0x06, 0x00 } } },
    /* 0 */{ { 22, { TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE }, { 0x0004, 0x0004, 0x0000, 0x0B00, 0x0000, 0x0000, 0x0304, 0x0304, 0x0404, 0x0404, 0x0404, 0x0C04, 0x0004, 0x0404, 0x1004, 0x1004, 0x0004, 0x0004, 0x0604,  0x0604, 0x0404, 0x0404 } }, {  TRUE, { 0x00, 0x00, 0x00, 0x03, 0x04, 0x0C, 0x04, 0x10, 0x00, 0x06, 0x00 } } },
    /* 0 */{ { 22, { TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE }, { 0x0004, 0x0C04, 0x0000, 0x0000, 0x0000, 0x0000, 0x0304, 0x0304, 0x0404, 0x0404, 0x0404, 0x0C04, 0x0004, 0x0404, 0x1004, 0x1004, 0x0004, 0x0004, 0x0604,  0x0604, 0x0404, 0x0404 } }, {  TRUE, { 0x00, 0x00, 0x00, 0x03, 0x04, 0x0C, 0x04, 0x10, 0x00, 0x06, 0x00 } } },
  };
  const int   nNrSteps = sizeof(aTestSteps) / sizeof(tUtCddSbc_TestSteps_FixData);

  for (nStep = 0; nStep < nNrSteps; nStep++)
  {
    //Step1:  set return and RxData set values in SPI-Mocks
    punRxData = (uint16*)&aTestSteps[nStep].SetValues.Mt_unRxData;
    pboReturn = (boolean*)&aTestSteps[nStep].SetValues.Mt_boReturn;
    CddTle94x1_sErrorType.boInitCtrlWrite = 0;
    Mt_CddSpi_SPIRegisterRxDataBuffer(aTestSteps[nStep].SetValues.Mt_uclen, punRxData, pboReturn);

    //Step2:  call function
    CddTle94x1_InitSettings();

    //Step3: compare the CddTle94x1_sErrorType.boInitCtrlWrite with the check values in TestSteps
    AL_UNITTEST_CHECK(CddTle94x1_sErrorType.boInitCtrlWrite, aTestSteps[nStep].CheckValues.boInitCtrlWrite, == );
    //       compare received data mirror and check values
    AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.StatRx.SUP_STAT_0_Register.uData.ucWord, aTestSteps[nStep].CheckValues.ucCtrlRxData[0], == );
    AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.StatRx.WK_STAT_0_Register.uData.ucWord, aTestSteps[nStep].CheckValues.ucCtrlRxData[1], == );
    AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.StatRx.DEV_STAT_Register.uData.ucWord, aTestSteps[nStep].CheckValues.ucCtrlRxData[2], == );
    AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.CtrlRx.BUS_CTRL_0_Register.uData.ucWord, aTestSteps[nStep].CheckValues.ucCtrlRxData[3], == );
    AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.CtrlRx.HW_CTRL_0_Register.uData.ucWord, aTestSteps[nStep].CheckValues.ucCtrlRxData[4], == );
    AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.CtrlRx.HW_CTRL_2_Register.uData.ucWord, aTestSteps[nStep].CheckValues.ucCtrlRxData[5], == );
    AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.CtrlRx.HW_CTRL_3_Register.uData.ucWord, aTestSteps[nStep].CheckValues.ucCtrlRxData[6], == );
    AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.CtrlRx.HW_CTRL_1_Register.uData.ucWord, aTestSteps[nStep].CheckValues.ucCtrlRxData[7], == );
    AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.CtrlRx.PWM_CTRL_Register.uData.ucWord, aTestSteps[nStep].CheckValues.ucCtrlRxData[8], == );
    AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.CtrlRx.GPIO_CTRL_Register.uData.ucWord, aTestSteps[nStep].CheckValues.ucCtrlRxData[9], == );
    AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.CtrlRx.M_S_CTRL_Register.uData.ucWord, aTestSteps[nStep].CheckValues.ucCtrlRxData[10], == );

    //Step4: reinitial the DataMorror for next test case
    CddTle94x1_sDataMirror.StatRx.SUP_STAT_0_Register.uData.ucWord = 0;
    CddTle94x1_sDataMirror.StatRx.WK_STAT_0_Register.uData.ucWord = 0;
    CddTle94x1_sDataMirror.StatRx.DEV_STAT_Register.uData.ucWord = 0;
    CddTle94x1_sDataMirror.CtrlRx.BUS_CTRL_0_Register.uData.ucWord = 0;
    CddTle94x1_sDataMirror.CtrlRx.HW_CTRL_0_Register.uData.ucWord  = 0;
    CddTle94x1_sDataMirror.CtrlRx.HW_CTRL_2_Register.uData.ucWord  = 0;
    CddTle94x1_sDataMirror.CtrlRx.HW_CTRL_3_Register.uData.ucWord  = 0;
    CddTle94x1_sDataMirror.CtrlRx.HW_CTRL_1_Register.uData.ucWord  = 0;
    CddTle94x1_sDataMirror.CtrlRx.M_S_CTRL_Register.uData.ucWord   = 0;
  }
}

////-----------------------------------------------------------------------------
///// \Test Case : Mt_CddTle94x1_Init
/////
///// \Functional Safety: NA
/////
///// \Test methods:
/////        - Requirements-based test
/////
///// \Test Case Description
/////    - Test subject:
/////        Check if the CddTle94x1_Init() writes the commands to control registers in the initialization sussessful.
/////        Check the error flag CddTle94x1_sErrorType.boInitCtrlWrite and the SPI data mirror.
/////
/////    - Test Design Technique: DT (Decision Table)
/////        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
/////        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
/////        set by the FUT. Every DT-entry represents a different Test Case interaction.
/////      - DT-Info:
/////         - Inputs:
/////           - Mt_uclen: Buffer length provided to the Spi driver
/////           - Mt_boReturn[]: Buffer return value provided to the Spi driver
/////           - Mt_unRxData[]: Buffer data provided to the Spi driver
/////         - Outputs:
/////           - boInitCtrlWrite: Return value of this FUT
/////           - ucCtrlRxData[]: SPI data mirror
/////
/////    - Preconditions: none
/////
/////    - Expected test results:
/////        - All conditions and assigned values of the DT need to be reached and passed.
/////
////-----------------------------------------------------------------------------
//void Mt_CddTle94x1_Init(void)
//{
//  // test step
//  int nStep;
//  // point to RxData
//  uint16* punRxData;
//  // point to Return
//  boolean* pboReturn;
//
//  typedef struct
//  {
//    uint8   Mt_uclen;
//    boolean Mt_boReturn[20];
//    uint16  Mt_unRxData[20];
//  } tSetValues_FixData;
//
//  typedef struct
//  {
//    boolean boInitCtrlWrite;
//    uint8  ucCtrlRxData[9];
//  } tCheckValues_FixData;
//
//  typedef struct
//  {
//    tSetValues_FixData SetValues;
//    tCheckValues_FixData CheckValues;
//  } tUtCddSbc_TestSteps_FixData;
//
//  static const tUtCddSbc_TestSteps_FixData aTestSteps[] =
//  { //                                                                                                                      Intputs                                                                                                                       ||                           Outputs
//    //       Mt_uclen,                             Mt_boReturn,                                                                                                              Mt_unRxData;                                                                 ||  boInitCtrlWrite,     ucCtrlRxData
//    /* 0 */{ { 20, { TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE }, { 0x00, 0x00, 0x0004, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000, 0x0304, 0x0304, 0x0404, 0x0404, 0x0404, 0x0C04, 0x0004, 0x0404, 0x1004, 0x1004, 0x0404, 0x0404 } }, { FALSE, { 0x00, 0x00, 0x00, 0x03, 0x04, 0x0C, 0x04, 0x10, 0x04 } } },
//    /* 1 */{ { 20, { TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE }, { 0x00, 0x00, 0x0004, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000, 0x0304, 0x0304, 0x0404, 0x0404, 0x0404, 0x0C04, 0x0004, 0x0404, 0x1004, 0x1004, 0x0404, 0x0204 } }, {  TRUE, { 0x00, 0x00, 0x00, 0x03, 0x04, 0x0C, 0x04, 0x10, 0x00 } } },
//    /* 0 */{ { 20, { TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE }, { 0x00, 0x00, 0x0004, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000, 0x0304, 0x0304, 0x0404, 0x0404, 0x0404, 0x0C04, 0x0004, 0x0404, 0x1004, 0x1004, 0x0404, 0x0404 } }, { FALSE, { 0x00, 0x00, 0x00, 0x03, 0x04, 0x0C, 0x04, 0x10, 0x04 } } },
//  };
//
//  const int   nNrSteps = sizeof(aTestSteps) / sizeof(tUtCddSbc_TestSteps_FixData);
//
//  for (nStep = 0; nStep < nNrSteps; nStep++)
//  {
//    // Step1: set return and RxData value in SPI-Mocks
//    punRxData = (uint16*)&aTestSteps[nStep].SetValues.Mt_unRxData;
//    pboReturn = (boolean*)&aTestSteps[nStep].SetValues.Mt_boReturn;
//    CddTle94x1_sErrorType.boInitCtrlWrite = 0;
//    Mt_CddSpi_SPIRegisterRxDataBuffer(aTestSteps[nStep].SetValues.Mt_uclen, punRxData, pboReturn);
//
//    // Step2: call function
//    CddSbc_Init();
//
//    //Step3: compare the CddTle94x1_sErrorType.boInitCtrlWrite with the check values in TestSteps
//    AL_UNITTEST_CHECK(CddTle94x1_sErrorType.boInitCtrlWrite, aTestSteps[nStep].CheckValues.boInitCtrlWrite, == );
//    //       compare received data mirror and check values
//    AL_UNITTEST_CHECK(CddTle94x1_DataMirror.StatRx.SUP_STAT_0_Register.Data.ucWord, aTestSteps[nStep].CheckValues.ucCtrlRxData[0], == );
//    AL_UNITTEST_CHECK(CddTle94x1_DataMirror.StatRx.WK_STAT_0_Register.Data.ucWord, aTestSteps[nStep].CheckValues.ucCtrlRxData[1], == );
//    AL_UNITTEST_CHECK(CddTle94x1_DataMirror.StatRx.DEV_STAT_Register.Data.ucWord, aTestSteps[nStep].CheckValues.ucCtrlRxData[2], == );
//    AL_UNITTEST_CHECK(CddTle94x1_DataMirror.CtrlRx.BUS_CTRL_0_Register.Data.ucWord, aTestSteps[nStep].CheckValues.ucCtrlRxData[3], == );
//    AL_UNITTEST_CHECK(CddTle94x1_DataMirror.CtrlRx.HW_CTRL_0_Register.Data.ucWord, aTestSteps[nStep].CheckValues.ucCtrlRxData[4], == );
//    AL_UNITTEST_CHECK(CddTle94x1_DataMirror.CtrlRx.HW_CTRL_2_Register.Data.ucWord, aTestSteps[nStep].CheckValues.ucCtrlRxData[5], == );
//    AL_UNITTEST_CHECK(CddTle94x1_DataMirror.CtrlRx.HW_CTRL_3_Register.Data.ucWord, aTestSteps[nStep].CheckValues.ucCtrlRxData[6], == );
//    AL_UNITTEST_CHECK(CddTle94x1_DataMirror.CtrlRx.HW_CTRL_1_Register.Data.ucWord, aTestSteps[nStep].CheckValues.ucCtrlRxData[7], == );
//    AL_UNITTEST_CHECK(CddTle94x1_DataMirror.CtrlRx.M_S_CTRL_Register.Data.ucWord, aTestSteps[nStep].CheckValues.ucCtrlRxData[8], == );
//
//    //Step4: reinitial the DataMorror for next test case
//    CddTle94x1_DataMirror.StatRx.SUP_STAT_0_Register.Data.ucWord = 0;
//    CddTle94x1_DataMirror.StatRx.WK_STAT_0_Register.Data.ucWord = 0;
//    CddTle94x1_DataMirror.StatRx.DEV_STAT_Register.Data.ucWord = 0;
//    CddTle94x1_DataMirror.CtrlRx.BUS_CTRL_0_Register.Data.ucWord = 0;
//    CddTle94x1_DataMirror.CtrlRx.HW_CTRL_0_Register.Data.ucWord = 0;
//    CddTle94x1_DataMirror.CtrlRx.HW_CTRL_2_Register.Data.ucWord = 0;
//    CddTle94x1_DataMirror.CtrlRx.HW_CTRL_3_Register.Data.ucWord = 0;
//    CddTle94x1_DataMirror.CtrlRx.HW_CTRL_1_Register.Data.ucWord = 0;
//    CddTle94x1_DataMirror.CtrlRx.M_S_CTRL_Register.Data.ucWord = 0;
//  }
//}
//
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSbc_Init
///
/// \Functional Safety: NA
///
/// \Test methods:
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:
///        Call the API function CddSbc_Init(). This function is to be tested with Failed InitStateRead() .
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. Every DT-entry represents a different Test Case interaction.
///      - DT-Info:
///         - Inputs:
///           - Mt_uclen: Buffer length provided to the Spi driver
///           - Mt_boReturn[]: Buffer return value provided to the Spi driver
///           - Mt_unRxData[]: Buffer data provided to the Spi driver
///         - Outputs:
///           - boErrorType_InitStatRead: Error flag
///
///    - Preconditions: none
///
///    - Expected test results:
///        - All conditions and assigned values of the DT need to be reached and passed.
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_Init(void)
{
  boolean boReturn;
  // test step
  int nStep;
  // point to RxData
  uint16* punRxData;
  // point to Return
  boolean* pboReturn;

  typedef struct
  {
    uint8   Mt_uclen;
    boolean Mt_boReturn[4];
    uint16  Mt_unRxData[4];
  } tSetValues_FixData;

  typedef struct
  {
    boolean boErrorType_InitStatRead;
  } tCheckValues_FixData;

  typedef struct
  {
    tSetValues_FixData SetValues;
    tCheckValues_FixData CheckValues;
  } tUtCddSbc_TestSteps_FixData;

  static const tUtCddSbc_TestSteps_FixData aTestSteps[] =
  {   //                                            Intputs                           ||     Outputs
    //      Mt_uclen,     Mt_boReturn,                       Mt_unRxData;             ||  boErrorType
    /* 0 */{ { 4, {  TRUE,  TRUE,  TRUE,  TRUE }, { 0x0046, 0x8041, 0xFFFF, 0xFFFF } }, { FALSE } },
    /* 1 */{ { 4, { FALSE,  TRUE,  TRUE,  TRUE }, { 0x00AA, 0x0046, 0x8041, 0xFFFF } }, { FALSE } },
    /* 3 */{ { 4, { FALSE, FALSE, FALSE,  TRUE }, { 0x00AA, 0x00BB, 0xFFFF, 0x0046 } }, {  TRUE } },
    /* 4 */{ { 4, { FALSE,  TRUE, FALSE, FALSE }, { 0x00AA, 0x00BB, 0x00CC, 0xDDDD } }, {  TRUE } },
    /* 5 */{ { 4, { FALSE,  TRUE, FALSE,  TRUE }, { 0x00AA, 0x0046, 0x00CC, 0x8041 } }, { FALSE } },
  };

  const int   nNrSteps = sizeof(aTestSteps) / sizeof(tUtCddSbc_TestSteps_FixData);

  for (nStep = 0; nStep < nNrSteps; nStep++)
  {
    //Step1: set return and RxData value in SPI-Mocks
    punRxData = (uint16*)&aTestSteps[nStep].SetValues.Mt_unRxData;
    pboReturn = (boolean*)&aTestSteps[nStep].SetValues.Mt_boReturn;

    Mt_CddSpi_SPIRegisterRxDataBuffer(aTestSteps[nStep].SetValues.Mt_uclen, punRxData, pboReturn);

    //Step2: call function and get the return value
   CddTle94x1_Init();

    //Step3: compare error flag with the check values in TestSteps
    AL_UNITTEST_CHECK(CddTle94x1_sErrorType.boInitStatRead, aTestSteps[nStep].CheckValues.boErrorType_InitStatRead, == );
  }
}

////-----------------------------------------------------------------------------
///// \Test Case : Mt_rpiCddSbc20ms
/////
///// \Functional Safety: NA
/////
///// \Test methods:
/////        - Requirements-based test
/////
///// \Test Case Description
/////    - Test subject:
/////        Check the rpiCddSbc20ms()
/////
/////    - Test Design Technique: DT (Decision Table)
/////        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
/////        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
/////        set by the FUT. Every DT-entry represents a different Test Case interaction.
/////      - DT-Info:
/////         - Inputs:
/////           - ResetReason:    reset reason
/////           - boErrorReset:   error reset flag
/////         - Outputs:
/////           - ucPWM_CTRL_Reg:    Data for Pwm_Ctrl Register
/////           - ucGPIO_CTRL_Reg:   Data for GPIO_Ctrl Register
/////
/////    - Preconditions: none
/////
/////    - Expected test results:
/////        - All conditions and assigned values of the DT need to be reached and passed.
/////
////-----------------------------------------------------------------------------
//void Mt_rpiCddSbc20ms(void)
//{
//  // test step
//  int nStep;
//
//  typedef struct
//  {
//    uint8 ResetReason;
//    boolean boErrorReset;
//  } tSetValues_FixData;
//
//  typedef struct
//  {
//    Dem_EventStatusType Dtc430110_EventStatus;
//    Dem_EventStatusType Dtc430111_EventStatus;
//  } tCheckValues_FixData;
//
//  typedef struct
//  {
//    tSetValues_FixData SetValues;
//    tCheckValues_FixData CheckValues;
//  } tUtCddSbc_TestSteps_FixData;
//
//  static const tUtCddSbc_TestSteps_FixData aTestSteps[] =
//  { //                          Intputs            ||                  Outputs
//    //        ResetReason,     boErrorReset;    ||         Dtc430110_EventStatus,      Dtc430111_EventStatus
//    /* 0 */{ { eRESET_WATCHDOG,  FALSE },     { DEM_EVENT_STATUS_FAILED,       DEM_EVENT_STATUS_PASSED } },
//    /* 1 */{ { eRESET_SOFTWARE,  FALSE },     { DEM_EVENT_STATUS_FAILED,       DEM_EVENT_STATUS_PASSED } },
//    /* 2 */{ { eRESET_POWER_ON,  FALSE },     { DEM_EVENT_STATUS_PASSED,       DEM_EVENT_STATUS_PASSED } },
//    /* 3 */{ { eRESET_ECC_ERROR,  TRUE },     { DEM_EVENT_STATUS_PASSED,       DEM_EVENT_STATUS_FAILED } },
//    /* 4 */{ { eRESET_WAKEUP,     TRUE },     { DEM_EVENT_STATUS_PASSED,       DEM_EVENT_STATUS_FAILED } },
//    /* 5 */{ { eRESET_WAKEUP,    FALSE },     { DEM_EVENT_STATUS_PASSED,       DEM_EVENT_STATUS_PASSED } },
//  };
//
//  const int   nNrSteps = sizeof(aTestSteps) / sizeof(tUtCddSbc_TestSteps_FixData);
//
//  Mt_Dtc430110_EventStatus = DEM_EVENT_STATUS_PASSED;
//  Mt_Dtc430111_EventStatus = DEM_EVENT_STATUS_PASSED;
//
//  for (nStep = 0; nStep < nNrSteps; nStep++)
//  {
//    //Step1: simulate RTE ports of EftCrcStatus, EftCodM
//    CddSbc_tResetReason = aTestSteps[nStep].SetValues.ResetReason;
//    CddTle94x1_sErrorType.boErrorReset = aTestSteps[nStep].SetValues.boErrorReset;
//    CddTle94x1_ucFirstCycle = 0u;
//
//    // Step2: call function
//  	rpCddSbc20ms();
//
//    // Step3:
//    AL_UNITTEST_CHECK(Mt_Dtc430110_EventStatus, aTestSteps[nStep].CheckValues.Dtc430110_EventStatus, == );
//    AL_UNITTEST_CHECK(Mt_Dtc430111_EventStatus, aTestSteps[nStep].CheckValues.Dtc430111_EventStatus, == );
//    rpCddSbc20ms();
//  }
//}
//
//
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSbc_SetSleepMode
///
/// \Functional Safety: NA
///
/// \Test methods:
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:
///        Check if the CddSbc_SetSleepMode writes the correct commands to control registers for the sleep mode sussessful.
///        Check the error flag CddTle94x1_sErrorType.boGotoSleep_SpiFailure.
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. Every DT-entry represents a different Test Case interaction.
///      - DT-Info:
///         - Inputs:
///           - Mt_uclen: Buffer length provided to the Spi driver
///           - Mt_boReturn[]: Buffer return value provided to the Spi driver
///           - Mt_unRxData[]: Buffer data provided to the Spi driver
///         - Outputs:
///           - boGotoSleep_SpiFailure: error flag for SPI-Failure (goto sleep mode)
///           - boGoToSleep_Failure: error flag for goto sleep failure
///
///    - Preconditions: none
///
///    - Expected test results:
///        - All conditions and assigned values of the DT need to be reached and passed.
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_SetSleepMode(void)
{
  // test step
  int nStep;
  // point to RxData
  uint16* punRxData;
  // point to Return
  boolean* pboReturn;

  typedef struct
  {
    uint8   Mt_uclen;
    boolean Mt_boReturn[14];
    uint16  Mt_unRxData[14];
  } tSetValues_FixData;

  typedef struct
  {
    boolean boGotoSleep_SpiFailure;
    boolean boGoToSleep_Failure;
  } tCheckValues_FixData;

  typedef struct
  {
    tSetValues_FixData SetValues;
    tCheckValues_FixData CheckValues;
  } tUtCddSbc_TestSteps_FixData;

  // in order to introduce an error use a different value between 2*x and 2*x+1
  // RX data shall be swaped 
  static const tUtCddSbc_TestSteps_FixData aTestSteps[] =
  { //                                                     Intputs                                                                                                                             ||     Outputs
    //       Mt_uclen,                         Mt_boReturn,                                                                   Mt_unRxData;                                                     ||boGotoSleep_SpiFailure,   boGoToSleep_Failure
    /* 0 */{ { 14, { TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE}, { 0x0004, 0x0004, 0x0004, 0x0004, 0x0404, 0x0004, 0x0304, 0x0104, 0x0000, 0x0000, 0x0404, 0x0404, 0x4000, 0x4000 } }, {  FALSE, TRUE } },
    /* 1 */{ { 14, { TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE}, { 0x0004, 0x0004, 0x0004, 0x0204, 0x0404, 0x0004, 0x0304, 0x0104, 0x0000, 0x0000, 0x0404, 0x0404, 0x4000, 0x4000 } }, {  TRUE, TRUE } },
    /* 2 */{ { 14, { TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE}, { 0x0004, 0x0304, 0x0004, 0x0004, 0x0404, 0x0004, 0x0304, 0x0104, 0x0000, 0x0000, 0x0404, 0x0404, 0x4000, 0x4000 } }, {  TRUE, TRUE } },
    /* 3 */{ { 14, { TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE}, { 0x0004, 0x0004, 0x0004, 0x0004, 0x0404, 0x0204, 0x0304, 0x0104, 0x0000, 0x0000, 0x0404, 0x0404, 0x4000, 0x4000 } }, {  TRUE, TRUE } },
    /* 4 */{ { 14, { TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE}, { 0x0004, 0x0004, 0x0004, 0x0004, 0x0404, 0x0004, 0x0304, 0x0104, 0x0000, 0x0000, 0x0404, 0x0404, 0x4000, 0x4000 } }, {  FALSE, TRUE } },
    /* 5 */{ { 14, { TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE}, { 0x0004, 0x0004, 0x0004, 0x0004, 0x0404, 0x0004, 0x0304, 0x0304, 0x0000, 0x0000, 0x0404, 0x0404, 0x4000, 0x4000 } }, {  TRUE, TRUE } },
    /* 6 */{ { 14, { TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE,FALSE, TRUE, TRUE}, { 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0304, 0x0304, 0x0000, 0xFFFF, 0x0018, 0x0418, 0x4100, 0x4100 } }, {  TRUE, FALSE } }, // PWM write failed ,M_S mode write failed

  };

  const int   nNrSteps = sizeof(aTestSteps) / sizeof(tUtCddSbc_TestSteps_FixData);

  for (nStep = 0; nStep < nNrSteps; nStep++)
  {
    // set return and RxData value in SPI-Mocks
    punRxData = (uint16*)&aTestSteps[nStep].SetValues.Mt_unRxData[0];
    pboReturn = (boolean*)&aTestSteps[nStep].SetValues.Mt_boReturn[0];
    CddTle94x1_sErrorType.boGotoSleep_SpiFailure = FALSE;
    CddTle94x1_sErrorType.boGoToSleep_Failure = FALSE;

    Mt_CddSpi_SPIRegisterRxDataBuffer(aTestSteps[nStep].SetValues.Mt_uclen, punRxData, pboReturn);
    CddTle94x1_sDataMirror.CtrlTx.M_S_CTRL_Register.uData.ucWord = 0x00U;

   
    // call function
    CddTle94x1_SetSleepMode();

    // compare the CddTle94x1_sErrorType with the values in TestSteps
    AL_UNITTEST_CHECK(CddTle94x1_sErrorType.boGotoSleep_SpiFailure, aTestSteps[nStep].CheckValues.boGotoSleep_SpiFailure, == );
    AL_UNITTEST_CHECK(CddTle94x1_sErrorType.boGoToSleep_Failure, aTestSteps[nStep].CheckValues.boGoToSleep_Failure, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_SetCanMode
///
/// \Functional Safety: NA
///
/// \Test methods:
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:
///        Set the can mode with different index and modes. Call the CddSbc_SetCanMode() and
///        check if the error flag CddTle94x1_sErrorType.boCanModeError is set correctly.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results:
///        - All conditions and assigned values in the step2 need to be reached and passed.
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_SetCanMode(void)
{
  uint16 unReturnValue;
  // test step
  int nStep;
  // point to RxData
  uint16* punRxData;
  // point to Return
  boolean* pboReturn;

  typedef struct
  {
    uint8   Mt_uclen;
    boolean Mt_boReturn[2];
    uint16  Mt_unRxData[2];
    uint8   Mt_SpiState;
    uint8   Mt_CAN_CH;
    uint8   Mt_CAN_Mode;
  } tSetValues_FixData;

  typedef struct
  {
    boolean Mt_boCanModeError;
    boolean Mt_boCanChannelError;
  } tCheckValues_FixData;

  typedef struct
  {
    tSetValues_FixData SetValues;
    tCheckValues_FixData CheckValues;
  } tUtCddSbc_TestSteps_FixData;

  static const tUtCddSbc_TestSteps_FixData aTestSteps[] =
  { //                                      Intputs                                                                    ||     Outputs
    //     Mt_uclen,    Mt_boReturn,          Mt_unRxData,         Mt_SpiState                , Mt_CAN_CH, Mt_CAN_Mode;  Mt_boCanModeError, Mt_boCanChannelError
    /* 0 */{ { 2,     { TRUE,  TRUE},     { 0x0000, 0x0000 },   CDDSPI_STATE_CYCLIC_OPERATION,      0 ,          0 }, {       FALSE,              FALSE } },
    /* 1 */{ { 2,     { TRUE,  TRUE},     { 0x0000, 0x0000 },   CDDSPI_STATE_CYCLIC_OPERATION,      3 ,          0 }, {       FALSE,               TRUE } },
    /* 3 */{ { 2,     { TRUE,  TRUE},     { 0x0000, 0x0000 },   CDDSPI_STATE_CYCLIC_OPERATION,      0 ,          5 }, {        TRUE,              FALSE } },
    /* 4 */{ { 2,     { TRUE,  TRUE},     { 0x0304, 0x0304 },   CDDSPI_STATE_SINGLE_OPERATION,      0 ,          3 }, {       FALSE,              FALSE } },
    /* 5 */{ { 2,     { TRUE,  TRUE},     { 0x0304, 0x0304 },              CDDSPI_STATE_RESET,      0 ,          3 }, {       FALSE,              FALSE } },
    /* 6 */{ { 2,     {FALSE, FALSE},     { 0x0304, 0x0304 },   CDDSPI_STATE_SINGLE_OPERATION,      0 ,          3 }, {       FALSE,              FALSE } },

  };

  const int   nNrSteps = sizeof(aTestSteps) / sizeof(tUtCddSbc_TestSteps_FixData);

  for (nStep = 0; nStep < nNrSteps; nStep++)
  {
    //Step1: set return and RxData value in SPI-Mocks
    punRxData = (uint16*)&aTestSteps[nStep].SetValues.Mt_unRxData;
    pboReturn = (boolean*)&aTestSteps[nStep].SetValues.Mt_boReturn;
    Mt_CddSpi_SPIRegisterRxDataBuffer(aTestSteps[nStep].SetValues.Mt_uclen, punRxData, pboReturn);
    Mt_CddSpi_ucState = aTestSteps[nStep].SetValues.Mt_SpiState;

    CddTle94x1_SetCanMode(aTestSteps[nStep].SetValues.Mt_CAN_CH, aTestSteps[nStep].SetValues.Mt_CAN_Mode);

    //Step2: Check the error flag CddTle94x1_sErrorType.boCanModeError
    AL_UNITTEST_CHECK(CddTle94x1_sErrorType.boCanModeError, aTestSteps[nStep].CheckValues.Mt_boCanModeError, == );
    AL_UNITTEST_CHECK(CddTle94x1_sErrorType.boCanChannelError, aTestSteps[nStep].CheckValues.Mt_boCanChannelError, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_ValidateCanMode
///
/// \Functional Safety: NA
///
/// \Test methods:
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:
///        Set the can mode with different index and modes.
///        Call the CddTle94x1_ValidateCanMode() and
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results:
///        - All conditions and assigned values in the step2 need to be reached and passed.
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_ValidateCanMode(void)
{
  //Step1: Set can mode with index and mode in normal range.
  boolean boReturn = CddTle94x1_ValidateCanMode(CDDTLE94X1_CFG_CAN_NORMAL);

  //Step2: Check the error flag CddTle94x1_sErrorType.boCanModeError
  AL_UNITTEST_CHECK(CddTle94x1_sErrorType.boCanModeError, NO_ERROR, == );
  AL_UNITTEST_CHECK(boReturn, TRUE, ==);

  //Step1: Set can mode with index in normal range and mode out of range.
  boReturn = CddTle94x1_ValidateCanMode(10);
  //Step2: Check the error flag CddTle94x1_sErrorType.boCanModeError
  AL_UNITTEST_CHECK(CddTle94x1_sErrorType.boCanModeError, ERROR_ON, == );
  AL_UNITTEST_CHECK(boReturn, FALSE, == );

  //Step1: Set can mode with index and mode in normal range.
  boReturn = CddTle94x1_ValidateCanMode(CDDTLE94X1_CFG_CAN_WAKE_ON);

  //Step2: Check the error flag CddTle94x1_sErrorType.boCanModeError
  AL_UNITTEST_CHECK(CddTle94x1_sErrorType.boCanModeError, NO_ERROR, == );
  AL_UNITTEST_CHECK(boReturn, TRUE, == );

  //Step1: Set can mode with index and mode in normal range.
  boReturn = CddTle94x1_ValidateCanMode(CDDTLE94X1_CFG_CAN_RECEIVE_ONLY);

  //Step2: Check the error flag CddTle94x1_sErrorType.boCanModeError
  AL_UNITTEST_CHECK(CddTle94x1_sErrorType.boCanModeError, NO_ERROR, == );
  AL_UNITTEST_CHECK(boReturn, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_GetCanMode
///
/// \Functional Safety: NA
///
/// \Test methods:
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:
///        Simulate the can mode in Data mirror. Call the CddTle94x1_GetCanMode() and
///        check the return value.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results:
///        - All conditions and assigned values in the step3 need to be reached and passed.
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_GetCanMode(void)
{
  uint8 ucCanMode;
  uint16  Mt_unRxData[1] = {0x0000};
  boolean Mt_boReturn[1] = {TRUE};
  // point to RxData
  uint16* punRxData;
  // point to Return
  boolean* pboReturn;

  //Step1: simulate the CAN mode in Data mirror.
  CddTle94x1_sDataMirror.CtrlRx.BUS_CTRL_0_Register.uData.sBit.bCAN = 3;
  Mt_CddSpi_ucState = CDDSPI_STATE_CYCLIC_OPERATION;
  //Step2: call function and get the return value.
  ucCanMode = CddTle94x1_GetCanMode(0);
  //Step3: check the return value with simulated value.
  AL_UNITTEST_CHECK(ucCanMode, 3, == );

  //Step1: simulate the CAN mode in Data mirror.
  CddTle94x1_sDataMirror.CtrlRx.BUS_CTRL_0_Register.uData.sBit.bCAN = 1;
  Mt_CddSpi_ucState = CDDSPI_STATE_SINGLE_OPERATION;
  punRxData = (uint16*)&Mt_unRxData;
  pboReturn = (boolean*)&Mt_boReturn;
  Mt_CddSpi_SPIRegisterRxDataBuffer(1, punRxData, pboReturn);
  //Step2: call function with invalid index and get the return value
  ucCanMode = CddTle94x1_GetCanMode(1);
  //Step3: check the return value with default value
  AL_UNITTEST_CHECK(ucCanMode, 0, == );

  //Step1: simulate the CAN mode in Data mirror.
  CddTle94x1_sDataMirror.CtrlRx.BUS_CTRL_0_Register.uData.sBit.bCAN = 1;
  Mt_CddSpi_ucState = CDDSPI_STATE_SINGLE_OPERATION;
  Mt_boReturn[0] = FALSE;
  Mt_CddSpi_SPIRegisterRxDataBuffer(1, punRxData, pboReturn);
  //Step2: call function with invalid index and get the return value
  ucCanMode = CddTle94x1_GetCanMode(0);
  //Step3: check the return value with default value
  AL_UNITTEST_CHECK(ucCanMode, 1, == );

  //Step1: simulate the CAN mode in Data mirror.
  CddTle94x1_sDataMirror.CtrlRx.BUS_CTRL_0_Register.uData.sBit.bCAN = 0;
  Mt_CddSpi_ucState = CDDSPI_STATE_SINGLE_OPERATION;
  Mt_boReturn[0] = TRUE;
  Mt_CddSpi_SPIRegisterRxDataBuffer(1, punRxData, pboReturn);
  //Step2: call function with invalid index and get the return value
  ucCanMode = CddTle94x1_GetCanMode(0);
  //Step3: check the return value with default value
  AL_UNITTEST_CHECK(ucCanMode, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_GetCanUV
///
/// \Functional Safety: NA
///
/// \Test methods:
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:
///        Simulate the can mode in Data mirror. Call the CddSbc_GetCanUV() and
///        check the return value.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results:
///        - All conditions and assigned values in the step3 need to be reached and passed.
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_GetCanUV(void)
{
  uint8 ucCanUV;
  uint16  Mt_unRxData[1];
  boolean Mt_boReturn[1];
  // point to RxData
  uint16* punRxData;
  // point to Return
  boolean* pboReturn;

  //Step1: simulate the VCAN_UV in Data mirror.
  CddTle94x1_sDataMirror.StatRx.BUS_STAT_Register.uData.sBit.bVCAN_UV = 0;
  Mt_CddSpi_ucState = CDDSPI_STATE_CYCLIC_OPERATION;
  //Step2: call function and get the return value.
  ucCanUV = CddTle94x1_GetCanUV();
  //Step3: check the return value with simulated value.
  AL_UNITTEST_CHECK(ucCanUV, 0, == );

  //Step1: simulate the VCAN_UV in Data mirror.
  Mt_unRxData[0] = 0x0100;
  Mt_boReturn[0] = TRUE;
  Mt_CddSpi_ucState = CDDSPI_STATE_SINGLE_OPERATION;
  punRxData = (uint16*)&Mt_unRxData;
  pboReturn = (boolean*)&Mt_boReturn;
  Mt_CddSpi_SPIRegisterRxDataBuffer(1, punRxData, pboReturn);
  //Step2: call function with invalid index and get the return value
  ucCanUV = CddTle94x1_GetCanUV();
  //Step3: check the return value with default value
  AL_UNITTEST_CHECK(ucCanUV, 1, == );

  //Step1: simulate the VCAN_UV in Data mirror.
  Mt_unRxData[0] = 0x0100;
  Mt_boReturn[0] = FALSE;
  Mt_CddSpi_ucState = CDDSPI_STATE_SINGLE_OPERATION;
  punRxData = (uint16*)&Mt_unRxData;
  pboReturn = (boolean*)&Mt_boReturn;
  Mt_CddSpi_SPIRegisterRxDataBuffer(1, punRxData, pboReturn);
  //Step2: call function with invalid index and get the return value
  ucCanUV = CddTle94x1_GetCanUV();
  //Step3: check the return value with default value
  AL_UNITTEST_CHECK(ucCanUV, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_GetPWM
///
/// \Functional Safety: NA
///
/// \Test methods:
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:
///        Simulate the can mode in Data mirror. Call the CddSbc_GetPWM() and
///        check the return value.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results:
///        - All conditions and assigned values in the step3 need to be reached and passed.
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_GetPWM(void)
{
  uint8 ucPWM;
  uint16  Mt_unRxData[1];
  boolean Mt_boReturn[1];
  // point to RxData
  uint16* punRxData;
  // point to Return
  boolean* pboReturn;

  //Step1: simulate the VCAN_UV in Data mirror.
  CddTle94x1_sDataMirror.CtrlRx.PWM_CTRL_Register.uData.sBit.bPWM_DC = 0u;
  Mt_CddSpi_ucState = CDDSPI_STATE_CYCLIC_OPERATION;
  //Step2: call function and get the return value.
  ucPWM = CddTle94x1_GetPWM();
  //Step3: check the return value with simulated value.
  AL_UNITTEST_CHECK(ucPWM, 0, == );

  //Step1: simulate the PWM Val in Data mirror.
  Mt_unRxData[0] = 0x8000;
  Mt_boReturn[0] = TRUE;
  Mt_CddSpi_ucState = CDDSPI_STATE_SINGLE_OPERATION;
  punRxData = (uint16*)&Mt_unRxData;
  pboReturn = (boolean*)&Mt_boReturn;
  Mt_CddSpi_SPIRegisterRxDataBuffer(1, punRxData, pboReturn);
  //Step2: call function with invalid index and get the return value
  ucPWM = CddTle94x1_GetPWM();
  //Step3: check the return value with default value
  AL_UNITTEST_CHECK(ucPWM, 128u, == );

  //Step1: simulate the PWM Val in Data mirror.
  Mt_unRxData[0] = 0x8000;
  Mt_boReturn[0] = FALSE;
  Mt_CddSpi_ucState = CDDSPI_STATE_SINGLE_OPERATION;
  punRxData = (uint16*)&Mt_unRxData;
  pboReturn = (boolean*)&Mt_boReturn;
  Mt_CddSpi_SPIRegisterRxDataBuffer(1, punRxData, pboReturn);
  //Step2: call function with invalid index and get the return value
  ucPWM = CddTle94x1_GetPWM();
  //Step3: check the return value with default value
  AL_UNITTEST_CHECK(ucPWM, 128u, == );
}

#if ((CDDSBC_CFG_CYCLIC_OPERATION == STD_ON) && (CDDSBC_CFG_WK_INPUT == STD_ON))
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_GetWakeUpStatus
///
/// \Functional Safety: NA
///
/// \Test methods:
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:
///        Simulate the can mode in Data mirror. Call the CddTle94x1_GetWakeUpStatus() and
///        check the return value.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results:
///        - All conditions and assigned values in the step3 need to be reached and passed.
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_GetWakeUpStatus(void)
{
  boolean boWakeupStatus;

  //Step1: simulate the WK_LVL in Data mirror.
  CddTle94x1_sDataMirror.StatRx.WK_LVL_STAT_Register.uData.sBit.bWK_LVL = 0;
  //Step2: call function and get the return value.
  boWakeupStatus = CddTle94x1_GetWakeUpStatus();
  //Step3: check the return value with simulated value.
  AL_UNITTEST_CHECK(boWakeupStatus, 0, == );

  //Step1: simulate the WK_LVL in Data mirror.
  CddTle94x1_sDataMirror.StatRx.WK_LVL_STAT_Register.uData.sBit.bWK_LVL = 1;
  //Step2: call function and get the return value.
  boWakeupStatus = CddTle94x1_GetWakeUpStatus();
  //Step3: check the return value with simulated value.
  AL_UNITTEST_CHECK(boWakeupStatus, 1, == );
}
#endif

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_ReadReg
///
/// \Functional Safety: NA
///
/// \Test methods:
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:
///        Call the CddTle94x1_ReadReg() with SPI-register address.
///        Check the return values with the expected values.
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. Every DT-entry represents a different Test Case interaction.
///      - DT-Info:
///         - Inputs:
///           - Mt_uclen: Buffer length provided to the Spi driver
///           - Mt_boReturn[]: Buffer return value provided to the Spi driver
///           - Mt_unRxData[]: Buffer data provided to the Spi driver
///         - Outputs:
///           - unReturnValue: return value of the FUT
///
///    - Preconditions: none
///
///    - Expected test results:
///        - All conditions and assigned values of the DT need to be reached and passed.
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_ReadReg(void)
{
  uint16 unReturnValue;
  // test step
  int nStep;
  // point to RxData
  uint16* punRxData;
  // point to Return
  boolean* pboReturn;

  typedef struct
  {
    uint8   Mt_uclen;
    boolean Mt_boReturn[4];
    uint16  Mt_unRxData[4];
  } tSetValues_FixData;

  typedef struct
  {
    uint16 unReturnValue;
  } tCheckValues_FixData;

  typedef struct
  {
    tSetValues_FixData SetValues;
    tCheckValues_FixData CheckValues;
  } tUtCddSbc_TestSteps_FixData;

  static const tUtCddSbc_TestSteps_FixData aTestSteps[] =
  { //                                      Intputs                                  ||     Outputs
    //     Mt_uclen,       Mt_boReturn,                       Mt_unRxData;              unReturnValue
    /* 0 */{ { 4, {  TRUE,  TRUE,  TRUE,  TRUE }, { 0x8046, 0xFFFF, 0xFFFF, 0xFFFF } }, { 0x0080 } },
    /* 1 */{ { 4, { FALSE,  TRUE,  TRUE,  TRUE }, { 0x00AA, 0x8846, 0xFFFF, 0xFFFF } }, { 0x0088 } },
    /* 2 */{ { 4, { FALSE, FALSE, FALSE, FALSE }, { 0xAAAA, 0xBBBB, 0xCCCC, 0xDDDD } }, { 0xFFFF } },
  };

  const int   nNrSteps = sizeof(aTestSteps) / sizeof(tUtCddSbc_TestSteps_FixData);

  for (nStep = 0; nStep < nNrSteps; nStep++)
  {
    //Step1: set return and RxData value in SPI-Mocks
    punRxData = (uint16*)&aTestSteps[nStep].SetValues.Mt_unRxData;
    pboReturn = (boolean*)&aTestSteps[nStep].SetValues.Mt_boReturn;
    Mt_CddSpi_SPIRegisterRxDataBuffer(aTestSteps[nStep].SetValues.Mt_uclen, punRxData, pboReturn);

    //Step2: call function and get the return value
    unReturnValue = CddTle94x1_ReadReg(0x46);

    //Step3: compare the return value with the check values in TestSteps
    AL_UNITTEST_CHECK(unReturnValue, aTestSteps[nStep].CheckValues.unReturnValue, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_WriteClearReg
///
/// \Functional Safety: NA
///
/// \Test methods:
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:
///        Call the CddTle94x1_WriteClearReg() with SPI-register address and data.
///        Check the return values with the expected values.
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. Every DT-entry represents a different Test Case interaction.
///      - DT-Info:
///         - Inputs:
///           - Mt_uclen: Buffer length provided to the Spi driver
///           - ucAddress:  Address of SPI-register
///           - unData:     data to be sent to SPI-register
///           - Mt_boReturn[]: Buffer return value provided to the Spi driver
///           - Mt_unRxData[]: Buffer data provided to the Spi driver
///         - Outputs:
///           - unReturnValue: return value of the FUT
///
///    - Preconditions: none
///
///    - Expected test results:
///        - All conditions and assigned values of the DT need to be reached and passed.
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_WriteClearReg(void)
{
  boolean boReturn;

  // test step
  int nStep;
  // point to RxData
  uint16* punRxData;
  // point to Return
  boolean* pboReturn;

  typedef struct
  {
    uint8   Mt_uclen;
    uint8   ucAddress;
    uint16  unData;
    boolean Mt_boReturn[4];
    uint16  Mt_unRxData[4];
  } tSetValues_FixData;

  typedef struct
  {
    boolean boReturn;
  } tCheckValues_FixData;

  typedef struct
  {
    tSetValues_FixData SetValues;
    tCheckValues_FixData CheckValues;
  } tUtCddSbc_TestSteps_FixData;

  static const tUtCddSbc_TestSteps_FixData aTestSteps[] =
  { //                                      Intputs                                                        ||   Outputs
    //      Mt_uclen, ucAddress, unData        Mt_boReturn,                       Mt_unRxData;             ||  boReturn
    /* 0 */{ { 4, 0x01, 0x08, { TRUE, TRUE, TRUE, TRUE }, { 0x0801, 0x0801, 0xFFFF, 0xFFFF } }, { TRUE } },
    /* 1 */{ { 4, 0x04, 0x03, { FALSE, FALSE, TRUE, TRUE }, { 0xFFFF, 0xFFFF, 0x0304, 0x0304 } }, { TRUE } },
    /* 2 */{ { 4, 0x07, 0x01, { FALSE, FALSE, TRUE, TRUE }, { 0x0801, 0x0801, 0x0801, 0x08FF } }, { FALSE } },
  };

  const int   nNrSteps = sizeof(aTestSteps) / sizeof(tUtCddSbc_TestSteps_FixData);

  for (nStep = 0; nStep < nNrSteps; nStep++)
  {
    //Step1: set return and RxData value in SPI-Mocks
    punRxData = (uint16*)&aTestSteps[nStep].SetValues.Mt_unRxData;
    pboReturn = (boolean*)&aTestSteps[nStep].SetValues.Mt_boReturn;
    Mt_CddSpi_SPIRegisterRxDataBuffer(aTestSteps[nStep].SetValues.Mt_uclen, punRxData, pboReturn);

    //Step2: call function with SPI-register address and data, get the return value
    boReturn = CddTle94x1_WriteClearReg(aTestSteps[nStep].SetValues.ucAddress, aTestSteps[nStep].SetValues.unData);

    //Step3: compare the return value with the check values in TestSteps
    AL_UNITTEST_CHECK(boReturn, aTestSteps[nStep].CheckValues.boReturn, == );
  }
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_WriteClearReg2
///
/// \Functional Safety: NA
///
/// \Test methods:
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:
///        Call the CddTle94x1_WriteClearReg() with Return value "FALSE" of CddSpi_TransferMsg().
///        Check the return values with the expected values.
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. Every DT-entry represents a different Test Case interaction.
///      - DT-Info:
///         - Inputs:
///           - Mt_uclen: Buffer length provided to the Spi driver
///           - ucAddress:  Address of SPI-register
///           - unData:     data to be sent to SPI-register
///           - Mt_boReturn[]: Buffer return value provided to the Spi driver
///           - Mt_unRxData[]: Buffer data provided to the Spi driver
///         - Outputs:
///           - unReturnValue: return value of the FUT
///
///    - Preconditions: none
///
///    - Expected test results:
///        - All conditions and assigned values of the DT need to be reached and passed.
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_WriteClearReg2(void)
{
  boolean boReturn;

  // test step
  int nStep;
  // point to RxData
  uint16* punRxData;
  // point to Return
  boolean* pboReturn;

  typedef struct
  {
    uint8   Mt_uclen;
    uint8   ucAddress;
    uint16  unData;
    boolean Mt_boReturn[20];
    uint16  Mt_unRxData[20];
  } tSetValues_FixData;

  typedef struct
  {
    boolean boReturn;
  } tCheckValues_FixData;

  typedef struct
  {
    tSetValues_FixData SetValues;
    tCheckValues_FixData CheckValues;
  } tUtCddSbc_TestSteps_FixData;

  static const tUtCddSbc_TestSteps_FixData aTestSteps[] =
  { //                                      Intputs                                                                                                                                                                                                                                                                                              ||   Outputs
    //      Mt_uclen, ucAddress, unData        Mt_boReturn,                                                                                                                                   Mt_unRxData;                                                                                                                                       ||  boReturn
    /* 0 */{ { 4, 0x01, 0x08, { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, }, { 0x0801, 0x0801, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF } }, { FALSE } },
  };

  const int   nNrSteps = sizeof(aTestSteps) / sizeof(tUtCddSbc_TestSteps_FixData);

  for (nStep = 0; nStep < nNrSteps; nStep++)
  {
    //Step1: set return and RxData value in SPI-Mocks
    punRxData = (uint16*)&aTestSteps[nStep].SetValues.Mt_unRxData;
    pboReturn = (boolean*)&aTestSteps[nStep].SetValues.Mt_boReturn;
    Mt_CddSpi_SPIRegisterRxDataBuffer(aTestSteps[nStep].SetValues.Mt_uclen, punRxData, pboReturn);

    //Step2: call function with SPI-register address and data, get the return value
    boReturn = CddTle94x1_WriteClearReg(aTestSteps[nStep].SetValues.ucAddress, aTestSteps[nStep].SetValues.unData);

    //Step3: compare the return value with the check values in TestSteps
    AL_UNITTEST_CHECK(boReturn, aTestSteps[nStep].CheckValues.boReturn, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSbc_ScheduleTableFull
///
/// \Functional Safety: NA
///
/// \Test methods:
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:
///        Call the CddSbc_ScheduleTableFull with different value
///        and check the error flag boScheduleTableFull
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results:
///        - All conditions and assigned values in the step2 need to be reached and passed.
///
//-----------------------------------------------------------------------------
void Mt_CddSbc_ScheduleTableFull(void)
{
  //Step1: Call the function with error
  CddSbc_ScheduleTableFull(ERROR_ON);

  //Step2: Check the error flag
  AL_UNITTEST_CHECK(CddTle94x1_sErrorType.boScheduleTableFull, ERROR_ON, == );

  //Step1: Call the function without error
  CddSbc_ScheduleTableFull(NO_ERROR);

  //Step2: Check the error flag
  AL_UNITTEST_CHECK(CddTle94x1_sErrorType.boScheduleTableFull, NO_ERROR, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSbc_InsertNewSchedEntry
///
/// \Functional Safety: NA
///
/// \Test methods:
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:
///        Check if the CddSbc_InsertNewSchedEntry() inserts the new entry with SPI-register address and data into the
///        SPI- Schedule table correctly.
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. Every DT-entry represents a different Test Case interaction.
///      - DT-Info:
///         - Inputs:
///           - ucQueueWriteIndex: Index for write in the queue
///           - boProcessEntry: flag for process entry
///           - ucAddress: address for the SPI-register
///           - ucData: data for the SPI-register
///           - ucCommand: command for write or read
///           - CbkFunction: pointer to call back function
///         - Outputs:
///           - ucQueueWriteIndex: Index for write in the queue
///           - boReturn: Return value of this FUT
///           - boProcessEntry: flag for process entry
///           - CddSbc_unTxData: sent data for register
///           - boScheduleTableFull: error flag for the schedule table
///
///    - Preconditions: none
///
///    - Expected test results:
///        - All conditions and assigned values of the DT need to be reached and passed.
///
//-----------------------------------------------------------------------------
void Mt_CddSbc_InsertNewSchedEntry(void)
{
  boolean boReturn;
  uint8   ucAddress;
  uint8   ucData;
  uint8   ucCommand;
  pfReadClBck CbkFunction;

  // test step
  int nStep;

  typedef struct
  {
    uint8   ucQueueWriteIndex;
    boolean boProcessEntry;
    uint8   ucAddress;
    uint8   ucData;
    uint8   ucCommand;
    pfReadClBck CbkFunction;
  } tSetValues_FixData;

  typedef struct
  {
    uint8   ucQueueWriteIndex;
    boolean boReturn;
    boolean boProcessEntry;
    uint16  CddSbc_unTxData;
    boolean boScheduleTableFull;
  } tCheckValues_FixData;

  typedef struct
  {
    tSetValues_FixData SetValues;
    tCheckValues_FixData CheckValues;
  } tUtCddSbc_TestSteps_FixData;

  static const tUtCddSbc_TestSteps_FixData aTestSteps[] =
  { //                                      Intputs                                                            ||     Outputs
    //   ucQueueWriteIndex,  boProcessEntry, ucAddress, ucData      ucCommand,            CbkFunction;             ucQueueWriteIndex, boReturn,  boProcessEntry, CddSbc_unTxData, boScheduleTableFull
    /* 0 */{ {  4,             FALSE,         0x41,     0x00,  CDDTLE94X1_CFG_READ_CMD,                 NULL_PTR }, {       5,           TRUE,         TRUE,        0x0041,           FALSE } },
    /* 1 */{ {  7,             FALSE,         0x04,     0x03,  CDDTLE94X1_CFG_WRITE_CMD, CddTle94x1_CbkSetCanMode }, {       8,           TRUE,        TRUE,        0x0384,           FALSE } },
    /* 2 */{ { 11,              TRUE,         0x41,     0x00,  CDDTLE94X1_CFG_READ_CMD,                 NULL_PTR }, {      11,          FALSE,         TRUE,        0x0000,            TRUE } },
   // /* 3 */{ { 11,             FALSE,         0x01,     0x04, CDD_Tle94x1_WRITE_CMD,    CddTle94x1_CbkSetVcc2 }, {      12,           TRUE,         TRUE,        0x0481,           FALSE } },
   // /* 4 */{ { 19,             FALSE,         0x01,     0x04, CDD_Tle94x1_WRITE_CMD,    CddTle94x1_CbkSetVcc2 }, {       0,           TRUE,         TRUE,        0x0481,           FALSE } },

  };

  const int   nNrSteps = sizeof(aTestSteps) / sizeof(tUtCddSbc_TestSteps_FixData);

  for (nStep = 0; nStep < nNrSteps; nStep++)
  {
    //Step1: set the SPI-Schedule queue with set values in the test step
    CddSbc_ucQueueWriteIndex = aTestSteps[nStep].SetValues.ucQueueWriteIndex;
    CddSbc_asSpiScheduleQueue[CddSbc_ucQueueWriteIndex].CddSbc_boProcessEntry = aTestSteps[nStep].SetValues.boProcessEntry;

    //Step2: set the address, data, command and callback function with set values in the test step
    ucAddress = aTestSteps[nStep].SetValues.ucAddress;
    ucData = aTestSteps[nStep].SetValues.ucData;
    ucCommand = aTestSteps[nStep].SetValues.ucCommand;
    CbkFunction = aTestSteps[nStep].SetValues.CbkFunction;

    //Step3: Call the function with address, data, command and callback function
    boReturn = CddSbc_InsertNewSchedEntry(ucAddress, ucData, ucCommand, CbkFunction);

    //Step4: check the return, data and flags values with the check values in the test step
    AL_UNITTEST_CHECK(CddSbc_ucQueueWriteIndex, aTestSteps[nStep].CheckValues.ucQueueWriteIndex, == );
    AL_UNITTEST_CHECK(boReturn, aTestSteps[nStep].CheckValues.boReturn, == );
    if (aTestSteps[nStep].SetValues.boProcessEntry == TRUE) // the queue is full
    {
      AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[CddSbc_ucQueueWriteIndex].CddSbc_boProcessEntry, aTestSteps[nStep].CheckValues.boProcessEntry, == );
    }
    else
    {
      AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[(CddSbc_ucQueueWriteIndex + CDDSBC_CFG_MAX_SPI_SCHED_QUEUE - 1u) % CDDSBC_CFG_MAX_SPI_SCHED_QUEUE].CddSbc_boProcessEntry, aTestSteps[nStep].CheckValues.boProcessEntry, == );
      AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[(CddSbc_ucQueueWriteIndex + CDDSBC_CFG_MAX_SPI_SCHED_QUEUE - 1u) % CDDSBC_CFG_MAX_SPI_SCHED_QUEUE].CddSbc_unTxData, aTestSteps[nStep].CheckValues.CddSbc_unTxData, == );
    }

    AL_UNITTEST_CHECK(CddTle94x1_sErrorType.boScheduleTableFull, aTestSteps[nStep].CheckValues.boScheduleTableFull, == );
  }
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSbc_InsertDefaultMessage
///
/// \Functional Safety: NA
///
/// \Test methods:
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:
///        Call the CddSbc_InsertDefaultMessage and check if the default message
///        is inserted successful.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results:
///        - All conditions and assigned values in the step3 need to be reached and passed.
///
//-----------------------------------------------------------------------------
void Mt_CddSbc_InsertDefaultMessage(void)
{
  //Step1: Simulate the index for writting in the schedule queue
  CddSbc_ucQueueWriteIndex = 12;
  CddSbc_asSpiScheduleQueue[CddSbc_ucQueueWriteIndex].CddSbc_boProcessEntry = FALSE;

  //Step2: Call the function
  CddTle94x1_eDefaultMsg = eBUS_CTRL_0;
  CddSbc_InsertDefaultMessage();

  //Step3: Check the schedule queue after the call of the function
  AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[(CddSbc_ucQueueWriteIndex + CDDSBC_CFG_MAX_SPI_SCHED_QUEUE - 1u) % CDDSBC_CFG_MAX_SPI_SCHED_QUEUE].CddSbc_boProcessEntry, TRUE, == );
  AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[(CddSbc_ucQueueWriteIndex + CDDSBC_CFG_MAX_SPI_SCHED_QUEUE - 1u) % CDDSBC_CFG_MAX_SPI_SCHED_QUEUE].CddSbc_unTxData, 0x0004, == );

  //Step1: Simulate the index for writting in the schedule queue
  CddSbc_ucQueueWriteIndex = 15;
  CddSbc_asSpiScheduleQueue[CddSbc_ucQueueWriteIndex].CddSbc_boProcessEntry = FALSE;

  //Step2: Call the function
  CddTle94x1_eDefaultMsg = eBUS_STAT;
  CddSbc_InsertDefaultMessage();

  //Step3: Check the schedule queue after the call of the function
  AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[(CddSbc_ucQueueWriteIndex + CDDSBC_CFG_MAX_SPI_SCHED_QUEUE - 1u) % CDDSBC_CFG_MAX_SPI_SCHED_QUEUE].CddSbc_boProcessEntry, TRUE, == );
  AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[(CddSbc_ucQueueWriteIndex + CDDSBC_CFG_MAX_SPI_SCHED_QUEUE - 1u) % CDDSBC_CFG_MAX_SPI_SCHED_QUEUE].CddSbc_unTxData, 0x0044, == );

  //Step1: Simulate the index for writting in the schedule queue
  CddSbc_ucQueueWriteIndex = 19;
  CddSbc_asSpiScheduleQueue[CddSbc_ucQueueWriteIndex].CddSbc_boProcessEntry = FALSE;

  //Step2: Call the function
  CddTle94x1_eDefaultMsg = eSUP_STAT_0;
  CddSbc_InsertDefaultMessage();

  //Step3: Check the schedule queue after the call of the function
  AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[(CddSbc_ucQueueWriteIndex + CDDSBC_CFG_MAX_SPI_SCHED_QUEUE - 1u) % CDDSBC_CFG_MAX_SPI_SCHED_QUEUE].CddSbc_boProcessEntry, TRUE, == );
  AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[(CddSbc_ucQueueWriteIndex + CDDSBC_CFG_MAX_SPI_SCHED_QUEUE - 1u) % CDDSBC_CFG_MAX_SPI_SCHED_QUEUE].CddSbc_unTxData, 0x0041, == );

  //Step1: Simulate the invalid index for writting in the schedule queue
  CddSbc_ucQueueWriteIndex = 0;
  CddSbc_asSpiScheduleQueue[CddSbc_ucQueueWriteIndex].CddSbc_boProcessEntry = FALSE;

  //Step2: Call the function
  CddTle94x1_eDefaultMsg = 0xFF;
  CddSbc_InsertDefaultMessage();

  //Step3: Check the schedule queue after the call of the function
  AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[(CddSbc_ucQueueWriteIndex + CDDSBC_CFG_MAX_SPI_SCHED_QUEUE - 1u) % CDDSBC_CFG_MAX_SPI_SCHED_QUEUE].CddSbc_boProcessEntry, TRUE, == );
  AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[(CddSbc_ucQueueWriteIndex + CDDSBC_CFG_MAX_SPI_SCHED_QUEUE - 1u) % CDDSBC_CFG_MAX_SPI_SCHED_QUEUE].CddSbc_unTxData, 0x0041, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_CbkGetSupState0
///
/// \Functional Safety: NA
///
/// \Test methods:
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:
///        Call the CddTle94x1_CbkGetSupState0 to check if the received data is
///        saved in data mirror successful
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. Every DT-entry represents a different Test Case interaction.
///      - DT-Info:
///         - Inputs:
///           - ulData: received data (two bytes)
///           - unSentVal: sent data
///         - Outputs:
///           - ucRxData: received data for status register
///
///    - Preconditions: none
///
///    - Expected test results:
///        - All conditions and assigned values of the DT need to be reached and passed.
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_CbkGetSupState0(void)
{
  // test step
  int nStep;

  typedef struct
  {
    uint32 ulData;
    uint16 unSentVal;
  } tSetValues_FixData;

  typedef struct
  {
    uint8 ucRxData;
  } tCheckValues_FixData;

  typedef struct
  {
    tSetValues_FixData SetValues;
    tCheckValues_FixData CheckValues;
  } tUtCddSbc_TestSteps_FixData;

  static const tUtCddSbc_TestSteps_FixData aTestSteps[] =
  { //              Intputs         ||   Outputs
    //         ulData,     unSentVal;  ucRxData;
    /* 0 */{ { 0x0000AAAA,  0xAA41 }, { 0xAA } },
    /* 1 */{ { 0x000040AA,  0xAA41 }, { 0x40 } },
    /* 2 */{ { 0x0000AAAA,  0xAA43 }, { 0x40 } },
  };

  const int   nNrSteps = sizeof(aTestSteps) / sizeof(tUtCddSbc_TestSteps_FixData);

  for (nStep = 0; nStep < nNrSteps; nStep++)
  {
    //Step1: call the function with set data in test steps
    CddTle94x1_CbkGetSupState0(aTestSteps[nStep].SetValues.ulData, aTestSteps[nStep].SetValues.unSentVal);

    //Step2: compare the return and received RxData value with the check values in test steps
    AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.StatRx.SUP_STAT_0_Register.uData.ucWord, aTestSteps[nStep].CheckValues.ucRxData, == );
  }
}

#if ((CDDSBC_CFG_CYCLIC_OPERATION == STD_ON) && (CDDSBC_CFG_WK_INPUT == STD_ON))
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_CbkGetWakeUpStatus
///
/// \Functional Safety: NA
///
/// \Test methods:
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:
///        Call the CddTle94x1_CbkGetWakeUpStatus to check if the received data is
///        saved in data mirror successful
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. Every DT-entry represents a different Test Case interaction.
///      - DT-Info:
///         - Inputs:
///           - ulData: received data (two bytes)
///           - unSentVal: sent data
///         - Outputs:
///           - ucRxData: received data for status register
///
///    - Preconditions: none
///
///    - Expected test results:
///        - All conditions and assigned values of the DT need to be reached and passed.
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_CbkGetWakeUpStatus(void)
{
  // test step
  int nStep;

  typedef struct
  {
    uint32 ulData;
    uint16 unSentVal;
  } tSetValues_FixData;

  typedef struct
  {
    uint8 ucRxData;
  } tCheckValues_FixData;

  typedef struct
  {
    tSetValues_FixData SetValues;
    tCheckValues_FixData CheckValues;
  } tUtCddSbc_TestSteps_FixData;

  static const tUtCddSbc_TestSteps_FixData aTestSteps[] =
  { //              Intputs         ||   Outputs
    //         ulData,     unSentVal;  ucRxData;
    /* 0 */{ { 0x000033AA,  0xAA48 },{ 0x33 } },
    /* 1 */{ { 0x000001BB,  0xAA48 },{ 0x01 } },
    /* 2 */{ { 0x000048CC,  0xAA43 },{ 0x01 } },
  };

  const int   nNrSteps = sizeof(aTestSteps) / sizeof(tUtCddSbc_TestSteps_FixData);

  for (nStep = 0; nStep < nNrSteps; nStep++)
  {
    //Step1: call the function with set data in test steps
    CddTle94x1_CbkGetWakeUpStatus(aTestSteps[nStep].SetValues.ulData, aTestSteps[nStep].SetValues.unSentVal);

    //Step2: compare the return and received RxData value with the check values in test steps
    AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.StatRx.WK_LVL_STAT_Register.uData.ucWord, aTestSteps[nStep].CheckValues.ucRxData, == );
  }
}
#endif

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_CbkSetCanMode
///
/// \Functional Safety: NA
///
/// \Test methods:
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:
///        Call the CddTle94x1_CbkSetCanMode to check if the received data is
///        saved in data mirror successful
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. Every DT-entry represents a different Test Case interaction.
///      - DT-Info:
///         - Inputs:
///           - unErrorSequenceCounter: counter for the error sequence
///           - ulData: received data (two bytes)
///           - unSentVal: sent data
///         - Outputs:
///           - ucRxData: received data for status register
///           - boCyclic_CanMode
///           - boCyclic_SPI_Communication
///           - unErrorSequenceCounter: counter for the error sequence
///
///    - Preconditions: none
///
///    - Expected test results:
///        - All conditions and assigned values of the DT need to be reached and passed.
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_CbkSetCanMode(void)
{
  // test step
  int nStep;

  typedef struct
  {
    uint16 unErrorSequenceCounter;
    uint32 ulData;
    uint16 unSentVal;
  } tSetValues_FixData;

  typedef struct
  {
    boolean boCyclic_CanMode;
    boolean boCyclic_SPI_Communication;
    uint16 unErrorSequenceCounter;
    uint8 ucRxData;
  } tCheckValues_FixData;

  typedef struct
  {
    tSetValues_FixData SetValues;
    tCheckValues_FixData CheckValues;
  } tUtCddSbc_TestSteps_FixData;

  static const tUtCddSbc_TestSteps_FixData aTestSteps[] =
  { //                 Intputs                         ||   Outputs
    // unErrorSequenceCounter,  ulData,     unSentVal; ||   boCyclic_CanMode,  boCyclic_SPI_Communication, unErrorSequenceCounter , ucRxData;
    /* 0 */{ { 100,            0x00000304,  0x0384 },    { NO_ERROR,                 NO_ERROR,                  0,                    0x03 } },
    /* 1 */{ { 500,            0x00000204,  0x0384 },    { ERROR_ON,                 ERROR_ON,                500,                    0x03 } },
    /* 2 */{ { 500,            0x00000304,  0x0384 },    { NO_ERROR,                 NO_ERROR,                  0,                    0x03 } },
  };

  const int   nNrSteps = sizeof(aTestSteps) / sizeof(tUtCddSbc_TestSteps_FixData);

  for (nStep = 0; nStep < nNrSteps; nStep++)
  {
    //Step1: simulate the counter for error sequence
    CddTle94x1_unErrorSequenceCounter = aTestSteps[nStep].SetValues.unErrorSequenceCounter;
    CddTle94x1_sDataMirror.CtrlTx.BUS_CTRL_0_Register.uData.ucWord = aTestSteps[nStep].SetValues.unSentVal >> 8u;

    //Step2: call the function with set data in test steps
    CddTle94x1_CbkSetCanMode(aTestSteps[nStep].SetValues.ulData, aTestSteps[nStep].SetValues.unSentVal);

    //Step3: compare the return and received RxData value with the check values in test steps
    AL_UNITTEST_CHECK(CddTle94x1_sErrorType.boCyclic_CanMode, aTestSteps[nStep].CheckValues.boCyclic_CanMode, == );
    AL_UNITTEST_CHECK(CddTle94x1_sErrorType.boCyclic_SPI_Communication, aTestSteps[nStep].CheckValues.boCyclic_SPI_Communication, == );
    AL_UNITTEST_CHECK(CddTle94x1_unErrorSequenceCounter, aTestSteps[nStep].CheckValues.unErrorSequenceCounter, == );
    AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.CtrlRx.BUS_CTRL_0_Register.uData.ucWord, aTestSteps[nStep].CheckValues.ucRxData, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_CbkGetCanMode
///
/// \Functional Safety: NA
///
/// \Test methods:
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:
///        Call the CddTle94x1_CbkGetGanMode to check if the received data is
///        saved in data mirror successful
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. Every DT-entry represents a different Test Case interaction.
///      - DT-Info:
///         - Inputs:
///           - ulData: received data (two bytes)
///           - unSentVal: sent data
///         - Outputs:
///           - unErrorSequenceCounter: counter for the error sequence
///
///    - Preconditions: none
///
///    - Expected test results:
///        - All conditions and assigned values of the DT need to be reached and passed.
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_CbkGetCanMode(void)
{
  // test step
  int nStep;

  typedef struct
  {
    uint32 ulData;
    uint16 unSentVal;
  } tSetValues_FixData;

  typedef struct
  {
    uint8 ucRxData;
  } tCheckValues_FixData;

  typedef struct
  {
    tSetValues_FixData SetValues;
    tCheckValues_FixData CheckValues;
  } tUtCddSbc_TestSteps_FixData;

  static const tUtCddSbc_TestSteps_FixData aTestSteps[] =
  { //                 Intputs            ||   Outputs
    //        ulData,     unSentVal;      ||   ucRxData;
    /* 0 */{ { 0x00000304,  0x0304 },    {     0x03 } },
    /* 1 */{ { 0x00000204,  0x0304 },    {     0x02 } },
    /* 2 */{ { 0x00000304,  0x0304 },    {     0x03 } },
    /* 3 */{ { 0x00000504,  0x0507 },    {     0x00 } },
  };

  const int   nNrSteps = sizeof(aTestSteps) / sizeof(tUtCddSbc_TestSteps_FixData);

  for (nStep = 0; nStep < nNrSteps; nStep++)
  {
    //Step1:
    CddTle94x1_sDataMirror.CtrlRx.BUS_CTRL_0_Register.uData.ucWord = 0x00;

    //Step2: call the function with set data in test step
    CddTle94x1_CbkGetCanMode(aTestSteps[nStep].SetValues.ulData, aTestSteps[nStep].SetValues.unSentVal);

    //Step3: compare the return and received RxData value with the check values in test steps
    AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.CtrlRx.BUS_CTRL_0_Register.uData.ucWord, aTestSteps[nStep].CheckValues.ucRxData, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_CbkGetBusState
///
/// \Functional Safety: NA
///
/// \Test methods:
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:
///        Call the CddTle94x1_CbkGetBusState to check if the received data is
///        saved in data mirror successful
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. Every DT-entry represents a different Test Case interaction.
///      - DT-Info:
///         - Inputs:
///           - ulData: received data (two bytes)
///           - unSentVal: sent data
///         - Outputs:
///           - ucRxData: received data for status register
///
///    - Preconditions: none
///
///    - Expected test results:
///        - All conditions and assigned values of the DT need to be reached and passed.
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_CbkGetBusState(void)
{
  // test step
  int nStep;

  typedef struct
  {
    uint32 ulData;
    uint16 unSentVal;
  } tSetValues_FixData;

  typedef struct
  {
    uint8 ucRxData;
  } tCheckValues_FixData;

  typedef struct
  {
    tSetValues_FixData SetValues;
    tCheckValues_FixData CheckValues;
  } tUtCddSbc_TestSteps_FixData;

  static const tUtCddSbc_TestSteps_FixData aTestSteps[] =
  { //              Intputs         ||   Outputs
    //         ulData,     unSentVal;  ucRxData;
    /* 0 */{ { 0x00000040,  0x0044 },{ 0x00 } },
    /* 1 */{ { 0x0000BBBB,  0xAA44 },{ 0xBB } },
    /* 2 */{ { 0x0000CCBB,  0xAA40 },{ 0xBB } },
  };

  const int   nNrSteps = sizeof(aTestSteps) / sizeof(tUtCddSbc_TestSteps_FixData);

  for (nStep = 0; nStep < nNrSteps; nStep++)
  {
    //Step1: call the function with set data in test steps
    CddTle94x1_CbkGetBusState(aTestSteps[nStep].SetValues.ulData, aTestSteps[nStep].SetValues.unSentVal);

    //Step2: compare the return and received RxData value with the check values in test steps
    AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.StatRx.BUS_STAT_Register.uData.ucWord, aTestSteps[nStep].CheckValues.ucRxData, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_SpiTx
///
/// \Functional Safety: ASIL-B
///
/// \Test methods:
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:
///        Call the CddTle94x1_SpiTx to check if the data in SPI schedule queue is
///        sent successful
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. Every DT-entry represents a different Test Case interaction.
///      - DT-Info:
///         - Inputs:
///           - ucQueueReadIndex: index for reading the queue
///           - boProcessEntry: flag for process entry
///           - ulTxData: sent Data
///         - Outputs:
///            -ucQueueReadIndex: index for reading the queue
///           - unTxData: sent Data as return
///
///    - Preconditions: none
///
///    - Expected test results:
///        - All conditions and assigned values of the DT need to be reached and passed.
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_SpiTx(void)
{
  uint32 ulReturnTxMsg;
  // test step
  int nStep;

  typedef struct
  {
    uint8   ucQueueReadIndex;
    uint8   ucQueueTxIndex;
    boolean boProcessEntry;
    uint16  unTxData;
  } tSetValues_FixData;

  typedef struct
  {
    uint8   ucQueueReadIndex;
    uint8   ucQueueTxIndex;
    uint32  ulTxData;
  }tCheckValues_FixData;

  typedef struct
  {
    tSetValues_FixData SetValues;
    tCheckValues_FixData CheckValues;
  } tUtCddSbc_TestSteps_FixData;

  static const tUtCddSbc_TestSteps_FixData aTestSteps[] =
  { //                      Intputs                       ||        Outputs
    //      ucQueueReadIndex, ucQueueTxIndex, boProcessEntry, unTxData;  ||   ucQueueReadIndex, ucQueueTxIndex,  ulTxData
    /* 0 */{ { 4,                  5,           TRUE,       0x0041 },     {         5,            6,          0x00000041 } },
    /* 1 */{ { 6,                  7,           FALSE,       0x0042 },    {         6,            7,          0x00000000 } },
    /* 2 */{ {19,                  0,           TRUE,       0x8305 },     {         0,            1,          0x00008305 } },
  };

  const int   nNrSteps = sizeof(aTestSteps) / sizeof(tUtCddSbc_TestSteps_FixData);

  for (nStep = 0; nStep < nNrSteps; nStep++)
  {
    //Step1: simulate the SPI schedule queue with set values in test steps
    CddSbc_ucQueueReadIndex = aTestSteps[nStep].SetValues.ucQueueReadIndex;
    CddSbc_ucQueueTXIndex = aTestSteps[nStep].SetValues.ucQueueTxIndex;
    CddSbc_asSpiScheduleQueue[CddSbc_ucQueueTXIndex].CddSbc_boProcessEntry = aTestSteps[nStep].SetValues.boProcessEntry;
    CddSbc_asSpiScheduleQueue[CddSbc_ucQueueTXIndex].CddSbc_unTxData = aTestSteps[nStep].SetValues.unTxData;

    //Step2: call the function and save the return value
    ulReturnTxMsg = CddTle94x1_SpiTx(0);

    //Step3: compare the return value with check values in Test Steps
    AL_UNITTEST_CHECK(CddSbc_ucQueueReadIndex, aTestSteps[nStep].CheckValues.ucQueueReadIndex, == );
    AL_UNITTEST_CHECK(CddSbc_ucQueueTXIndex, aTestSteps[nStep].CheckValues.ucQueueTxIndex, == );
    AL_UNITTEST_CHECK(ulReturnTxMsg, aTestSteps[nStep].CheckValues.ulTxData, == );
  }
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_SpiRx
///
/// \Functional Safety: ASIL-B
///
/// \Test methods:
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:
///        Call the CddTle94x1_SpiRx to check if the received data is storen in
///        SPI schedule queue successful
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. Every DT-entry represents a different Test Case interaction.
///      - DT-Info:
///         - Inputs:
///           - ucQueueReadIndex: index for reading the queue
///           - ucQueueWriteIndex: Index for write in the queue
///           - ulRxData: sent data
///           - boProcessEntry: flag for process entry
///           - boNextProcessEntry: flag for next process entry
///           - ReadClbckFunc: pointer to call back function
///         - Outputs:
///           - ucQueueReadIndex:  Index for reading the queue
///           - ucQueueWriteIndex: Index for write in the queue
///           - unRxData: sent Data as return
///           - boProcessEntry: flag for process entry
///
///    - Preconditions: none
///
///    - Expected test results:
///        - All conditions and assigned values of the DT need to be reached and passed.
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_SpiRx(void)
{
  // test step
  int nStep;

  typedef struct
  {
    uint8   ucQueueReadIndex;
    uint32  ulRxData;
    boolean boProcessEntry;
    boolean boNextProcessEntry;
    pfReadClBck ReadClbckFunc;
  } tSetValues_FixData;

  typedef struct
  {
    uint8   ucQueueReadIndex;
    uint16  unRxData;
    boolean boProcessEntry;
  }tCheckValues_FixData;

  typedef struct
  {
    tSetValues_FixData SetValues;
    tCheckValues_FixData CheckValues;
  } tUtCddSbc_TestSteps_FixData;

  static const tUtCddSbc_TestSteps_FixData aTestSteps[] =
  { //                      Intputs                                                   ||        Outputs
    // ucQueueReadIndex,  ulRxData, boProcessEntry, boNextProcessEntry, ReadClbckFunc;||  ucQueueReadIndex,  unRxData, boProcessEntry,
    /* 0 */{ { 4,         0x00000041,   TRUE,            FALSE,                 NULL_PTR },        { 4,          0x0041,      FALSE } },
    /* 1 */{ { 8,         0x00000881,   TRUE,             TRUE, CddTle94x1_CbkSetCanMode },        { 8,          0x0881,      FALSE } },
    /* 2 */{ { 19,        0x00000046,   TRUE,            FALSE,                 NULL_PTR },        {19,          0x0046,      FALSE } },
  };

  const int   nNrSteps = sizeof(aTestSteps) / sizeof(tUtCddSbc_TestSteps_FixData);

  for (nStep = 0; nStep < nNrSteps; nStep++)
  {
    //Step1: simulate the SPI schedule queue with set values in test steps
    CddSbc_ucQueueReadIndex = aTestSteps[nStep].SetValues.ucQueueReadIndex;
    CddSbc_asSpiScheduleQueue[CddSbc_ucQueueReadIndex].CddSbc_boProcessEntry = aTestSteps[nStep].SetValues.boProcessEntry;

    CddSbc_asSpiScheduleQueue[(CddSbc_ucQueueReadIndex + 1u) % CDDSBC_CFG_MAX_SPI_SCHED_QUEUE].CddSbc_boProcessEntry = aTestSteps[nStep].SetValues.boNextProcessEntry;
    CddSbc_asSpiScheduleQueue[(CddSbc_ucQueueReadIndex + 2u) % CDDSBC_CFG_MAX_SPI_SCHED_QUEUE].CddSbc_boProcessEntry = aTestSteps[nStep].SetValues.boNextProcessEntry;

    CddSbc_asSpiScheduleQueue[CddSbc_ucQueueReadIndex].CddSbc_ReadClbckFunc = aTestSteps[nStep].SetValues.ReadClbckFunc;

    //Step2: call the function with sent data
    CddTle94x1_SpiRx(0, aTestSteps[nStep].SetValues.ulRxData);

    //Step3: compare SPI schedule queue with check values in Test Steps
    AL_UNITTEST_CHECK(CddSbc_ucQueueReadIndex, aTestSteps[nStep].CheckValues.ucQueueReadIndex, == );

    if (aTestSteps[nStep].SetValues.boProcessEntry == TRUE) // if boProcessEntry is True, RxData will be stored.
    {
      AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[CddSbc_ucQueueReadIndex].CddSbc_unRxData, aTestSteps[nStep].CheckValues.unRxData, == );
    }

    AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[CddSbc_ucQueueReadIndex].CddSbc_boProcessEntry, aTestSteps[nStep].CheckValues.boProcessEntry, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_SpiRx_2
///
/// \Functional Safety: ASIL-B
///
/// \Test methods:
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:
///      Set the CddSbc_asSpiScheduleQueue[CddSbc_ucQueueReadIndex].CddSbc_boProcessEntry with FALSE
///      Call the Mt_CddTle94x1_SpiRx_2() to check if the function works properly.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results:
///        - All conditions and assigned values in the step3 need to be reached and passed.
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_SpiRx_2(void)
{
  //Step 1: set CddSbc_asSpiScheduleQueue[CddSbc_ucQueueReadIndex].CddSbc_boProcessEntry with FALSE
  CddSbc_ucQueueReadIndex = 4;
  CddSbc_asSpiScheduleQueue[4].CddSbc_boProcessEntry = FALSE;

  //Step 2: Call the function
  CddTle94x1_SpiRx(0, 0xAAAA);

  //Step 3: Check CddSbc_ucQueueReadIndex and CddSbc_asSpiScheduleQueue[4].CddSbc_boProcessEntry
  AL_UNITTEST_CHECK(CddSbc_ucQueueReadIndex, 4, == );
  AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[4].CddSbc_boProcessEntry, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSbc_SpiQueue_Init
///
/// \Functional Safety: NA
///
/// \Test methods:
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:
///      Call the CddTle94x1_Init() to check if the CddSbc_asSpiScheduleQueue is properly initialized.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results:
///        - All conditions and assigned values in the step3 need to be reached and passed.
///
//-----------------------------------------------------------------------------
void Mt_CddSbc_SpiQueue_Init(void)
{
  //Step 1: set CddSbc_ucQueueReadIndex and CddSbc_ucQueueWriteIndex to 0
  CddSbc_ucQueueReadIndex = 0;
  CddSbc_ucQueueWriteIndex = 0;

  //        set CddSbc_asSpiScheduleQueue with 0.
  for (uint8 i = 0; i < CDDSBC_CFG_MAX_SPI_SCHED_QUEUE; i++)
  {
    CddSbc_asSpiScheduleQueue[i].CddSbc_boProcessEntry = FALSE;
    CddSbc_asSpiScheduleQueue[i].CddSbc_unTxData = 0u;
    CddSbc_asSpiScheduleQueue[i].CddSbc_unRxData = 0u;
    CddSbc_asSpiScheduleQueue[i].CddSbc_ReadClbckFunc = NULL_PTR;
  }

  //Step 2: call CddSbc_InsertDefaultMessage()
  CddTle94x1_eDefaultMsg = eBUS_CTRL_0;
  CddSbc_InsertDefaultMessage();

  //Step 3: Check CddSbc_ucQueueReadIndex and CddSbc_ucQueueWriteIndex
  AL_UNITTEST_CHECK(CddSbc_ucQueueReadIndex, 0, == );
  AL_UNITTEST_CHECK(CddSbc_ucQueueWriteIndex, 1, == );

  //        Check CddSbc_asSpiScheduleQueue
  AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[0].CddSbc_boProcessEntry, TRUE, ==);
  AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[0].CddSbc_unTxData, 0x0004, == );
  AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[0].CddSbc_ReadClbckFunc, CddTle94x1_CbkGetCanMode, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSbc_SpiQueue_FirstTx
///
/// \Functional Safety: NA
///
/// \Test methods:
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:
///      Call the CddSbc_SpiTx() to check if the CddSbc_asSpiScheduleQueue is properly initialized.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results:
///        - All conditions and assigned values in the step3 need to be reached and passed.
///
//-----------------------------------------------------------------------------
void  Mt_CddSbc_SpiQueue_FirstTx(void)
{
  //Step 1: call Mt_CddSbc_SpiQueue_Init()
  Mt_CddSbc_SpiQueue_Init();

  //Step 2: call CddSbc_SpiTx()
  uint32 ulTxDataMsg = CddTle94x1_SpiTx(0);

  //Step 3: Check CddSbc_ucQueueReadIndex and CddSbc_ucQueueWriteIndex
  AL_UNITTEST_CHECK(CddSbc_ucQueueReadIndex, 0, == );
  AL_UNITTEST_CHECK(CddSbc_ucQueueTXIndex, 1, == );

  //        Check CddSbc_asSpiScheduleQueue and return value
  AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[0].CddSbc_boProcessEntry, TRUE, == );
  AL_UNITTEST_CHECK(ulTxDataMsg, 0x00000000, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_ErrorSequenceCounterInc
///
/// \Functional Safety: NA
///
/// \Test methods:
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:
///      Call the CddTle94x1_ErrorSequenceCounterInc()to check if the error counter works properly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results:
///        - All conditions and assigned values in the step3 need to be reached and passed.
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_ErrorSequenceCounterInc(void)
{
  //Step 1: Set the Counte before function call
  CddTle94x1_unErrorSequenceCounter = 20;
  CddTle94x1_sErrorType.boCyclic_SPI_Communication = FALSE;

  //Step 2: Call CddTle94x1_ErrorSequenceCounterInc()
  CddTle94x1_ErrorSequenceCounterInc();

  //Step 3: Check the counter and the error flag
  AL_UNITTEST_CHECK(CddTle94x1_unErrorSequenceCounter, 21, ==);
  AL_UNITTEST_CHECK(CddTle94x1_sErrorType.boCyclic_SPI_Communication, FALSE, ==);

  //Step 1: Set the Counte before function call
  CddTle94x1_unErrorSequenceCounter = CDDSBC_CFG_MAX_CYCLIC_SEQ_ERRORS;

  //Step 2: Call CddTle94x1_ErrorSequenceCounterInc()
  CddTle94x1_ErrorSequenceCounterInc();

  //Step 3: Check the counter and the error flag
  AL_UNITTEST_CHECK(CddTle94x1_unErrorSequenceCounter, CDDSBC_CFG_MAX_CYCLIC_SEQ_ERRORS, == );
  AL_UNITTEST_CHECK(CddTle94x1_sErrorType.boCyclic_SPI_Communication, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_ErrorSequenceCounterClear
///
/// \Functional Safety: NA
///
/// \Test methods:
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:
///      Call the CddTle94x1_ErrorSequenceCounterClear()to check if the error clear works properly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results:
///        - All conditions and assigned values in the step3 need to be reached and passed.
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_ErrorSequenceCounterClear(void)
{
  //Step 1: Set the Counte before function call
  CddTle94x1_unErrorSequenceCounter = 20;

  //Step 2: Call CddTle94x1_ErrorSequenceCounterClear()
  CddTle94x1_ErrorSequenceCounterClear();

  //Step 3: Check the counter and the error flag
  AL_UNITTEST_CHECK(CddTle94x1_unErrorSequenceCounter, 0, == );
}

////-----------------------------------------------------------------------------
///// \Test Case : Mt_CddTle94x1_StoreResetReason
/////
///// \Functional Safety: NA
/////
///// \Test methods:
/////        - Requirements-based test
/////
///// \Test Case Description
/////    - Test subject:
/////        Call the Mt_CddTle94x1_StoreResetReason to check if the reset reason is
/////        saved properly in the static variables
/////
/////    - Test Design Technique: DT (Decision Table)
/////        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
/////        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
/////        set by the FUT. Every DT-entry represents a different Test Case interaction.
/////      - DT-Info:
/////         - Inputs:
/////           - tMCUResetReason:  reset reason of MCU
/////           - WK_STAT_0_CANWU:  SBC wakeup status
/////           - SUP_STAT_0_POR:   SBC power on reset
/////           - WDG_RESET:        SBC watchdog reset
/////           - ECC_Error:        ECC Error
/////           - MCU_Selftest_Err: MCU selftest Error
/////         - Outputs:
/////           - tResetReason:    variable for reset reason
/////           - MCUResetReason:  variable for reset reason of MCU
/////           - SBCResetReason:  variable for reset reason of SBC
/////
/////    - Preconditions: none
/////
/////    - Expected test results:
/////        - All conditions and assigned values of the DT need to be reached and passed.
/////
////-----------------------------------------------------------------------------
void Mt_CddTle94x1_StoreResetReason(void)
{
//  tieResetReason ResetReason;
//  // test step
//  int nStep;
//
//  typedef struct
//  {
//    Mcu_ResetType tMCUResetReason;
//    uint8  WK_STAT_0_CANWU;
//    uint8  SUP_STAT_0_POR;
//    uint8  WDG_RESET;
//    uint16  Ecc_Error;
//    uint16  Mcu_Selftest_Err;
//  } tSetValues_FixData;
//
//  typedef struct
//  {
//    tieResetReason tResetReason;
//    teMCUResetType  MCUResetReason;
//    teSBCResetType SBCResetReason;
//  } tCheckValues_FixData;
//
//  typedef struct
//  {
//    tSetValues_FixData SetValues;
//    tCheckValues_FixData CheckValues;
//  } tUtCddSbc_TestSteps_FixData;
//
//  static const tUtCddSbc_TestSteps_FixData aTestSteps[] =
//  { //                     Intputs                                                                     ||                  Outputs
//    //             tMCUResetReason, WK_STAT_0_CANWU , SUP_STAT_0_POR,  WDG_RESET,  ECC_ERROR, MCU_SELFTEST_ERR ||      CddSbc_tResetReason,   MCUResetReason ,     SBCResetReason ;
//    /* 0 */{ { MCU_RESET_UNDEFINED,          0,              0,            0,         0,            0 },      {          eRESET_UNDEFINED,           eNoResetMCU,       eNoResetSBC } },
//    /* 1 */{ {      MCU_XRES_RESET,          1,              0,            0,         0,            0 },      {             eRESET_WAKEUP,           eNoResetMCU,   eCANWakeUpReset } },
//    /* 2 */{ {  MCU_WATCHDOG_RESET,          0,              0,            0,         0,            0 },      {           eRESET_WATCHDOG,     eWatchdogResetMCU,       eNoResetSBC } },
//    /* 3 */{ {    MCU_CSV_HF_RESET,          0,              0,            0,         0,            0 },      {          eRESET_PLL_ERROR,             ePLLReset,       eNoResetSBC } },
//    /* 4 */{ {        MCU_SW_RESET,          0,              0,            0,         0,            0 },      {           eRESET_SOFTWARE,        eSoftwareReset,       eNoResetSBC } },
//    /* 5 */{ {   MCU_CSV_REF_RESET,          0,              0,            0,         0,            0 },      {          eRESET_PLL_ERROR,             ePLLReset,       eNoResetSBC } },
//    /* 6 */{ {      MCU_XRES_RESET,          0,              1,            0,         0,            0 },      {           eRESET_POWER_ON,           eNoResetMCU,  ePowerOnResetSBC } },
//    /* 7 */{ { MCU_ACT_FAULT_RESET,          0,              0,            0,         0,            0 },      {               OTHER_RESET,         eOtherReasons,       eNoResetSBC } },
//    /* 8 */{ {      MCU_XRES_RESET,          0,              0,            1,         0,            0 },      {           eRESET_WATCHDOG,           eNoResetMCU,       eNoResetSBC } },
//    /* 9 */{ {        MCU_SW_RESET,          0,              0,            0,   ERROR_ACTIVE,       0 },      {          eRESET_ECC_ERROR,             eECCReset,       eNoResetSBC } },
//    /*10 */{ {      MCU_XRES_RESET,          0,              0,            0,   ERROR_ACTIVE,       0 },      {          eRESET_ECC_ERROR,             eECCReset,       eNoResetSBC } },
//    /*11 */{ {        MCU_SW_RESET,          1,              0,            0,   ERROR_ACTIVE,       0 },      {          eRESET_ECC_ERROR,             eECCReset,       eNoResetSBC } },
//    /*12 */{ {        MCU_SW_RESET,          0,              0,            0,         0, ERROR_ACTIVE },      { eRESET_MPU_SELFTEST_ERROR,     eMCUSelfTestReset,       eNoResetSBC } },
//    /*13 */{ {        MCU_SW_RESET,          0,              0,            0,         0, ERROR_ACTIVE },      { eRESET_MPU_SELFTEST_ERROR,     eMCUSelfTestReset,       eNoResetSBC } },
//    /* 14 */{ {     MCU_XRES_RESET,          0,              0,            0,         0,            0 },      {               OTHER_RESET,           eNoResetMCU,       eNoResetSBC } },
//  };
//  const int   nNrSteps = sizeof(aTestSteps) / sizeof(tUtCddSbc_TestSteps_FixData);
//
//  for (nStep = 0; nStep < nNrSteps; nStep++)
//  {
//    //Initialize the variables
//    CddSbc_eMCUResetReason = eNoResetMCU;
//    CddSbc_eSBCResetReason = eNoResetSBC;
//
//    //Step1: simulate the reset reason
//    CddTle94x1_ECCResetReason = &aTestSteps[nStep].SetValues.Ecc_Error;
//    CddTle94x1_MPUSelfTestResetReason = aTestSteps[nStep].SetValues.Mcu_Selftest_Err;
//    Mt_MCUResetReason = aTestSteps[nStep].SetValues.tMCUResetReason;
//    CddTle94x1_ucWK_STAT_0_CANWU = aTestSteps[nStep].SetValues.WK_STAT_0_CANWU;
//    CddTle94x1_ucSUP_STAT_0_POR = aTestSteps[nStep].SetValues.SUP_STAT_0_POR;
//    CddTle94x1_boIsWdgReset = aTestSteps[nStep].SetValues.WDG_RESET;
//
//    //Step2: call the function with set data in test steps
//    CddTle94x1_StoreResetReason();
//    (void)CddSbc_GetResetReason(&ResetReason);
//
//    //Step3: compare the return and received RxData value with the check values in test steps
//    AL_UNITTEST_CHECK(CddSbc_tResetReason, aTestSteps[nStep].CheckValues.tResetReason, == );
//    AL_UNITTEST_CHECK(CddSbc_eMCUResetReason, aTestSteps[nStep].CheckValues.MCUResetReason, == );
//    AL_UNITTEST_CHECK(CddSbc_eSBCResetReason, aTestSteps[nStep].CheckValues.SBCResetReason, == );
//  }
  CddTle94x1_StoreSBCResetReason();
}

////-----------------------------------------------------------------------------
///// \Test Case : Mt_CddTle94x1_GetResetReason
/////
///// \Functional Safety: NA
/////
///// \Test methods:
/////        - Requirements-based test
/////
///// \Test Case Description
/////    - Test subject:
/////        Call the Mt_CddTle94x1_GetResetReason to check if the reset reason and return value is
/////        properly provided.
/////
/////    - Test Design Technique: DT (Decision Table)
/////        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
/////        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
/////        set by the FUT. Every DT-entry represents a different Test Case interaction.
/////      - DT-Info:
/////         - Inputs:
/////           - tMCUResetReason:  reset reason of MCU
/////         - Outputs:
/////           - ret:             return value
/////           - tResetReason:    variable for reset reason
/////
/////    - Preconditions: none
/////
/////    - Expected test results:
/////        - All conditions and assigned values of the DT need to be reached and passed.
/////
////-----------------------------------------------------------------------------
//void Mt_CddTle94x1_GetResetReason(void)
//{
//  tieResetReason ResetReason;
//  Std_ReturnType retVal;
//  // test step
//  int nStep;
//
//  typedef struct
//  {
//    tieResetReason tResetReason;
//  } tSetValues_FixData;
//
//  typedef struct
//  {
//    Std_ReturnType ret;
//    tieResetReason tResetReason;
//  } tCheckValues_FixData;
//
//  typedef struct
//  {
//    tSetValues_FixData SetValues;
//    tCheckValues_FixData CheckValues;
//  } tUtCddSbc_TestSteps_FixData;
//
//  static const tUtCddSbc_TestSteps_FixData aTestSteps[] =
//  { //              Intputs     ||                  Outputs
//    //          tResetReason    ||     ret,   tResetReason ;
//    /* 0 */{ {    eRESET_SNA },    {  RTE_E_NOK,     eRESET_SNA } },
//    /* 1 */{ { eRESET_WAKEUP },    {   RTE_E_OK,  eRESET_WAKEUP } },
// };
//  const int   nNrSteps = sizeof(aTestSteps) / sizeof(tUtCddSbc_TestSteps_FixData);
//
//  for (nStep = 0; nStep < nNrSteps; nStep++)
//  {
//    //Step1: simulate the reset reason
//    CddSbc_tResetReason = aTestSteps[nStep].SetValues.tResetReason;
//
//    //Step2: call the function with set data in test steps
//    retVal = CddSbc_GetResetReason(&ResetReason);
//
//    //Step3: compare the return and received RxData value with the check values in test steps
//    AL_UNITTEST_CHECK(retVal, aTestSteps[nStep].CheckValues.ret, == );
//    AL_UNITTEST_CHECK(ResetReason, aTestSteps[nStep].CheckValues.tResetReason, == );
//  }
//}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_DeInit
///
/// \Functional Safety: NA
///
/// \Test methods:
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:
///        CddTle94x1_DeInit is a dummy function
///
///    - Test Design Technique: None
///
///    - Preconditions: none
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_DeInit(void)
{
  CddTle94x1_DeInit();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_SetWdgWithSingleOperation
///
/// \Functional Safety: NA
///
/// \Test methods:
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:
///        Simulate the can mode in Data mirror. Call the CddTle94x1_SetWdgWithSingleOperation() and
///        check the return value.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results:
///        - All conditions and assigned values in the step3 need to be reached and passed.
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_SetWdgWithSingleOperation(void)
{
  uint16  Mt_unRxData[2];
  boolean Mt_boReturn[2];
  // point to RxData
  uint16* punRxData;
  // point to Return
  boolean* pboReturn;

  //Step1: simulate the received data.
  Mt_unRxData[0] = 0x0203;
  Mt_unRxData[1] = 0x0203;
  Mt_boReturn[0] = TRUE;
  Mt_boReturn[1] = TRUE;
  punRxData = (uint16*)&Mt_unRxData;
  pboReturn = (boolean*)&Mt_boReturn;
  Mt_CddSpi_SPIRegisterRxDataBuffer(2, punRxData, pboReturn);
  CddTle94x1_sDataMirror.CtrlTx.WD_CTRL_Register.uData.ucWord = 0x02;

  //Step2: call function with invalid index and get the return value
  CddTle94x1_SetWdgWithSingleOperation();

  //Step3: check the return value with default value
  AL_UNITTEST_CHECK(CddTle94x1_sErrorType.boSpiWdgFailure, NO_ERROR, == );

  //Step1: simulate the received data.
  Mt_unRxData[0] = 0x0103;
  Mt_unRxData[1] = 0x0103;
  Mt_boReturn[0] = FALSE;
  Mt_boReturn[1] = FALSE;
  punRxData = (uint16*)&Mt_unRxData;
  pboReturn = (boolean*)&Mt_boReturn;
  Mt_CddSpi_SPIRegisterRxDataBuffer(2, punRxData, pboReturn);
  CddTle94x1_sDataMirror.CtrlRx.WD_CTRL_Register.uData.ucWord = 0x01;

  //Step2: call function with invalid index and get the return value
  CddTle94x1_SetWdgWithSingleOperation();

  //Step3: check the return value with default value
  AL_UNITTEST_CHECK(CddTle94x1_sErrorType.boSpiWdgFailure, ERROR_ON, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_SetWdgWindowModeAnd10ms
///
/// \Functional Safety:  ASIL-B
///
/// \Test methods:
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:
///        Simulate the can mode in Data mirror. Call the CddTle94x1_SetWdgWindowModeAnd10ms() and
///        check the return value.
///
/// \MDRS WDGM Id Requirement(s) covered: 
///
/// LDM.MDRS_CDDSBC.486
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results:
///        - All conditions and assigned values in the step3 need to be reached and passed.
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_SetWdgWindowModeAnd10ms(void)
{
  uint16  Mt_unRxData[2];
  boolean Mt_boReturn[2];
  // point to RxData
  uint16* punRxData;
  // point to Return
  boolean* pboReturn;

  //Step1: simulate the received data.
  Mt_unRxData[0] = 0xA003;
  Mt_unRxData[1] = 0xA003;
  Mt_boReturn[0] = TRUE;
  Mt_boReturn[1] = TRUE;
  punRxData = (uint16*)&Mt_unRxData;
  pboReturn = (boolean*)&Mt_boReturn;
  Mt_CddSpi_SPIRegisterRxDataBuffer(2, punRxData, pboReturn);

  Mt_CddSpi_ucState = CDDSPI_STATE_SINGLE_OPERATION;

  //Step2: call function with invalid index and get the return value
  CddTle94x1_SetWdgWindowModeAnd10ms();

  //Step3: check the return value with default value
  AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.CtrlTx.WD_CTRL_Register.uData.ucWord, 0xA0, ==)
  AL_UNITTEST_CHECK(CddTle94x1_sErrorType.boSpiWdgFailure, NO_ERROR, == );

  //Step1: simulate the received data.
  Mt_CddSpi_ucState = CDDSPI_STATE_CYCLIC_OPERATION;

  //Step2: call function with invalid index and get the return value
  CddTle94x1_SetWdgWindowModeAnd10ms();

  //Step3: check the return value with default value
  AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.CtrlTx.WD_CTRL_Register.uData.ucWord, 0xA0, == )

  //Step1: simulate the received data.
  Mt_CddSpi_ucState = CDDSPI_STATE_RESET;

  //Step2: call function with invalid index and get the return value
  CddTle94x1_SetWdgWindowModeAnd10ms();

  //Step3: check the return value with default value
  AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.CtrlTx.WD_CTRL_Register.uData.ucWord, 0xA0, == )
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_SetWdgWindowModeAnd200ms
///
/// \Functional Safety:  ASIL-B
///
/// \Test methods:
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:
///        Simulate the can mode in Data mirror. Call the CddTle94x1_SetWdgWindowModeAnd200ms() and
///        check the return value.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results:
///        - All conditions and assigned values in the step3 need to be reached and passed.
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_SetWdgWindowModeAnd200ms(void)
{
  uint16  Mt_unRxData[2];
  boolean Mt_boReturn[2];
  // point to RxData
  uint16* punRxData;
  // point to Return
  boolean* pboReturn;

  //Step1: simulate the received data.
  Mt_unRxData[0] = 0x8403;
  Mt_unRxData[1] = 0x8403;
  Mt_boReturn[0] = TRUE;
  Mt_boReturn[1] = TRUE;
  punRxData = (uint16*)&Mt_unRxData;
  pboReturn = (boolean*)&Mt_boReturn;
  Mt_CddSpi_SPIRegisterRxDataBuffer(2, punRxData, pboReturn);

  Mt_CddSpi_ucState = CDDSPI_STATE_SINGLE_OPERATION;

  //Step2: call function with invalid index and get the return value
  CddTle94x1_SetWdgWindowModeAnd200ms();

  //Step3: check the return value with default value
  AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.CtrlTx.WD_CTRL_Register.uData.ucWord, 0x84, == );
  AL_UNITTEST_CHECK(CddTle94x1_sErrorType.boSpiWdgFailure, NO_ERROR, == );

  //Step1: simulate the received data.
  //Step1: simulate the received data.
  Mt_unRxData[0] = 0x2403;
  Mt_unRxData[1] = 0x2403;
  Mt_boReturn[0] = TRUE;
  Mt_boReturn[1] = TRUE;
  punRxData = (uint16*)&Mt_unRxData;
  pboReturn = (boolean*)&Mt_boReturn;
  Mt_CddSpi_SPIRegisterRxDataBuffer(2, punRxData, pboReturn);
  Mt_CddSpi_ucState = CDDSPI_STATE_CYCLIC_OPERATION;

  //Step2: call function with invalid index and get the return value
  CddTle94x1_SetWdgWindowModeAnd200ms();

  //Step3: check the return value with default value
  AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.CtrlTx.WD_CTRL_Register.uData.ucWord, 0x24, == );

  //Step1: simulate the received data.
  Mt_CddSpi_ucState = CDDSPI_STATE_RESET;

  //Step2: call function with invalid index and get the return value
  CddTle94x1_SetWdgWindowModeAnd200ms();

  //Step3: check the return value with default value
  AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.CtrlTx.WD_CTRL_Register.uData.ucWord, 0x24, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_SetWdgTimeoutModeAnd200ms
///
/// \Functional Safety:  ASIL-B
///
/// \Test methods:
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:
///        Simulate the can mode in Data mirror. Call the CddTle94x1_SetWdgTimeoutModeAnd200ms() and
///        check the return value.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results:
///        - All conditions and assigned values in the step3 need to be reached and passed.
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_SetWdgTimeoutModeAnd200ms(void)
{
  uint16  Mt_unRxData[2];
  boolean Mt_boReturn[2];
  // point to RxData
  uint16* punRxData;
  // point to Return
  boolean* pboReturn;

  //Step1: simulate the received data.
  Mt_unRxData[0] = 0x8403;
  Mt_unRxData[1] = 0x8403;
  Mt_boReturn[0] = TRUE;
  Mt_boReturn[1] = TRUE;
  punRxData = (uint16*)&Mt_unRxData;
  pboReturn = (boolean*)&Mt_boReturn;
  Mt_CddSpi_SPIRegisterRxDataBuffer(2, punRxData, pboReturn);

  Mt_CddSpi_ucState = CDDSPI_STATE_SINGLE_OPERATION;

  //Step2: call function with invalid index and get the return value
  CddTle94x1_SetWdgTimeoutModeAnd200ms();

  //Step3: check the return value with default value
  AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.CtrlTx.WD_CTRL_Register.uData.ucWord, 0x84, == );
  AL_UNITTEST_CHECK(CddTle94x1_sErrorType.boSpiWdgFailure, NO_ERROR, == );

  //Step1: simulate the received data.
  Mt_CddSpi_ucState = CDDSPI_STATE_CYCLIC_OPERATION;

  //Step2: call function with invalid index and get the return value
  CddTle94x1_SetWdgTimeoutModeAnd200ms();

  //Step3: check the return value with default value
  AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.CtrlTx.WD_CTRL_Register.uData.ucWord, 0x84, == );

  //Step1: simulate the received data.
  Mt_CddSpi_ucState = CDDSPI_STATE_RESET;

  //Step2: call function with invalid index and get the return value
  CddTle94x1_SetWdgTimeoutModeAnd200ms();

  //Step3: check the return value with default value
  AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.CtrlTx.WD_CTRL_Register.uData.ucWord, 0x84, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_GetWatchdogFlag
///
/// \Functional Safety: NA
///
/// \Test methods:
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:
///        Call the Mt_CddTle94x1_GetWatchdogFlag to check if the watchdog reset reason is
///        saved properly in the static variables
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. Every DT-entry represents a different Test Case interaction.
///      - DT-Info:
///         - Inputs:
///           - CddTle94x1_WdgResetReason: watchdog reset information in Retention RAM
///         - Outputs:
///           - WDG_RESET:             SBC watchdog reset
///
///    - Preconditions: none
///
///    - Expected test results:
///        - All conditions and assigned values of the DT need to be reached and passed.
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_GetWatchdogFlag(void)
{
//  // test step
//  int nStep;
//
//  typedef struct
//  {
//    uint16   CddTle94x1_WdgResetReason;
//  } tSetValues_FixData;
//
//  typedef struct
//  {
//    uint8  WDG_RESET;
//  } tCheckValues_FixData;
//
//  typedef struct
//  {
//    tSetValues_FixData SetValues;
//    tCheckValues_FixData CheckValues;
//  } tUtCddSbc_TestSteps_FixData;
//
//  static const tUtCddSbc_TestSteps_FixData aTestSteps[] =
//  {
//    //                  Intputs              ||   Outputs
//    //       CddTle94x1_WdgResetReasonV;     || WDG_RESET;
//    /* 0 */{ {       0xFDFD      },             {  0   } },
//    /* 1 */{ {       0x5A01      },             {  1   } },
//    /* 2 */{ {       0x5A10      },             {  0   } },
//  };
//
//  const int   nNrSteps = sizeof(aTestSteps) / sizeof(tUtCddSbc_TestSteps_FixData);
//
//  for (nStep = 0; nStep < nNrSteps; nStep++)
//  {
//    //Step1: simulate the watchdog reset value in retention RAM
//    CddTle94x1_WdgResetReason = aTestSteps[nStep].SetValues.CddTle94x1_WdgResetReason;
//
//    //Step2: call function
//    CddTle94x1_GetWatchdogFlag();
//
//    //Step3: compare the variable value with the check values in TestSteps
//    AL_UNITTEST_CHECK(CddTle94x1_boIsWdgReset, aTestSteps[nStep].CheckValues.WDG_RESET, == );
//   }

  CddTle94x1_ucDEV_STAT_DEV_STAT = 1u;
  CddTle94x1_ucTHERMO_STAT_TSD2 = 0u;
  CddTle94x1_ucSUP_STAT_0_VCC1_UV = 0u;
  CddTle94x1_GetWatchdogFlag();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_CbkSetWDCtrl
///
/// \Functional Safety: NA
///
/// \Test methods:
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:
///        Call the CddTle94x1_CbkSetWDCtrl to check if the received data is
///        saved in data mirror successful
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. Every DT-entry represents a different Test Case interaction.
///      - DT-Info:
///         - Inputs:
///           - unErrorSequenceCounter: counter for the error sequence
///           - ulData: received data (two bytes)
///           - unSentVal: sent data
///         - Outputs:
///           - ucRxData: received data for status register
///           - boSpiWdgFailure
///           - boCyclic_SPI_Communication
///           - unErrorSequenceCounter: counter for the error sequence
///
///    - Preconditions: none
///
///    - Expected test results:
///        - All conditions and assigned values of the DT need to be reached and passed.
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_CbkSetWDCtrl(void)
{
  // test step
  int nStep;

  typedef struct
  {
    uint16 unErrorSequenceCounter;
    uint32 ulData;
    uint16 unSentVal;
  } tSetValues_FixData;

  typedef struct
  {
    boolean boSpiWdgFailure;
    boolean boCyclic_SPI_Communication;
    uint16 unErrorSequenceCounter;
    uint8 ucRxData;
  } tCheckValues_FixData;

  typedef struct
  {
    tSetValues_FixData SetValues;
    tCheckValues_FixData CheckValues;
  } tUtCddSbc_TestSteps_FixData;

  static const tUtCddSbc_TestSteps_FixData aTestSteps[] =
  { //                 Intputs                         ||   Outputs
    // unErrorSequenceCounter,  ulData,     unSentVal; ||   boSpiWdgFailure,  boCyclic_SPI_Communication, unErrorSequenceCounter , ucRxData;
    /* 0 */{ { 100,            0x00002404,  0x2483 },    { NO_ERROR,                 NO_ERROR,                  0,                    0x24 } },
    /* 1 */{ { 500,            0x00002403,  0x8783 },    { ERROR_ON,                 ERROR_ON,                500,                    0x24 } },
    /* 2 */{ { 500,            0x00002403,  0x2483 },    { NO_ERROR,                 NO_ERROR,                  0,                    0x24 } },
  };

  const int   nNrSteps = sizeof(aTestSteps) / sizeof(tUtCddSbc_TestSteps_FixData);

  for (nStep = 0; nStep < nNrSteps; nStep++)
  {
    //Step1: simulate the counter for error sequence
    CddTle94x1_unErrorSequenceCounter = aTestSteps[nStep].SetValues.unErrorSequenceCounter;
    CddTle94x1_sDataMirror.CtrlTx.WD_CTRL_Register.uData.ucWord = aTestSteps[nStep].SetValues.unSentVal >> 8u;

    //Step2: call the function with set data in test steps
    CddTle94x1_CbkSetWDCtrl(aTestSteps[nStep].SetValues.ulData, aTestSteps[nStep].SetValues.unSentVal);

    //Step3: compare the return and received RxData value with the check values in test steps
    AL_UNITTEST_CHECK(CddTle94x1_sErrorType.boSpiWdgFailure, aTestSteps[nStep].CheckValues.boSpiWdgFailure, == );
    AL_UNITTEST_CHECK(CddTle94x1_sErrorType.boCyclic_SPI_Communication, aTestSteps[nStep].CheckValues.boCyclic_SPI_Communication, == );
    AL_UNITTEST_CHECK(CddTle94x1_unErrorSequenceCounter, aTestSteps[nStep].CheckValues.unErrorSequenceCounter, == );
    AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.CtrlRx.WD_CTRL_Register.uData.ucWord, aTestSteps[nStep].CheckValues.ucRxData, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_GetSBCResetReason
///
/// \Functional Safety: NA
///
/// \Test methods:
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:
///        CddTle94x1_GetSBCResetReason
///
///    - Test Design Technique: None
///
///    - Preconditions: none
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_GetSBCResetReason(void)
{
  CddTle94x1_ucSUP_STAT_0_POR = 1u;
  CddTle94x1_StoreSBCResetReason();
  AL_UNITTEST_CHECK(CddTle94x1_ucSBCResetReason, ePowerOnResetSBC, == );

  CddTle94x1_ucSUP_STAT_0_POR = 0u;
  CddTle94x1_boStatusWdgReset = TRUE;
  CddTle94x1_StoreSBCResetReason();
  AL_UNITTEST_CHECK(CddTle94x1_ucSBCResetReason, eWatchdogReset, == )


  CddTle94x1_ucSUP_STAT_0_POR = 0u;
  CddTle94x1_boStatusWdgReset = FALSE;
  CddTle94x1_ucWK_STAT_0_CANWU = 1u;
  CddTle94x1_StoreSBCResetReason();
  AL_UNITTEST_CHECK(CddTle94x1_ucSBCResetReason, eCANWakeUpReset, == )

  CddTle94x1_ucSUP_STAT_0_POR = 0u;
  CddTle94x1_boStatusWdgReset = TRUE;
  CddTle94x1_ucWK_STAT_0_CANWU = 0u;
  CddTle94x1_StoreSBCResetReason();
  AL_UNITTEST_CHECK(CddTle94x1_ucSBCResetReason, eWatchdogReset, == )

  CddTle94x1_ucSUP_STAT_0_POR = 0u;
  CddTle94x1_boStatusWdgReset = FALSE;
  CddTle94x1_ucWK_STAT_0_CANWU = 0u;
  CddTle94x1_StoreSBCResetReason();
  AL_UNITTEST_CHECK(CddTle94x1_ucSBCResetReason, eNoResetSBC, == )

  CddTle94x1_GetSBCResetReason();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_SetPWM
///
/// \Functional Safety: NA
///
/// \Test methods:
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:
///        CddTle94x1_SetPWM
///
///    - Test Design Technique: None
///
///    - Preconditions: none
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_SetPWM(void)
{
  uint16 unPWMDutyCycle;

  unPWMDutyCycle = 0;
  CddTle94x1_SetPWM(unPWMDutyCycle);
  AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.CtrlTx.PWM_CTRL_Register.uData.sBit.bPWM_DC, CDDTLE94X1_CFG_PWM_DC_0, == );
  AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.CtrlTx.GPIO_CTRL_Register.uData.sBit.bGPIO, CDDTLE94X1_CFG_GPIO_100, == );

  unPWMDutyCycle = 100;
  CddTle94x1_SetPWM(unPWMDutyCycle);
  AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.CtrlTx.PWM_CTRL_Register.uData.sBit.bPWM_DC, (uint16)(unPWMDutyCycle * 255u / 10000u), == );
  AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.CtrlTx.GPIO_CTRL_Register.uData.sBit.bGPIO, CDDTLE94X1_CFG_GPIO_110, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_CbkSetPWM
///
/// \Functional Safety: NA
///
/// \Test methods:
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:
///        CddTle94x1_CbkSetPWM
///
///    - Test Design Technique: None
///
///    - Preconditions: none
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_CbkSetPWM(void)
{
  CddTle94x1_sDataMirror.CtrlRx.PWM_CTRL_Register.uData.ucWord = 0;
  CddTle94x1_CbkSetPWM(0x0000FF00, 0x0018);
  AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.CtrlRx.PWM_CTRL_Register.uData.ucWord, 0xFF, == );

  CddTle94x1_sDataMirror.CtrlRx.PWM_CTRL_Register.uData.ucWord = 0;
  CddTle94x1_CbkSetPWM(0x0000FF00, 0x0028);
  AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.CtrlRx.PWM_CTRL_Register.uData.ucWord, 0x00, == );
}

#if (CDDSBC_CFG_VCC2_OPERATION == STD_ON)
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_SetVCC2_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function for deactivation of VCC2
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input uint8 CddTle94x1_SetVCC2_Param1                                           = CDDTLE94X1_CFG_VCC2_DEACTIVATION;
/// \input CddSbc_ucQueueWriteIndex                                                  = 1u;
/// \input CddSbc_asSpiScheduleQueue[1].CddSbc_boProcessEntry                        = FALSE;
/// \input CddSbc_asSpiScheduleQueue[2].CddSbc_boProcessEntry                        = FALSE;
/// \input CddTle94x1_sDataMirror.CtrlTx.M_S_CTRL_Register.uData.ucWord              = 4u;
///
///    - Expectations :
///
/// \output CddTle94x1_sDataMirror.CtrlTx.M_S_CTRL_Register.uData.sBit.bVCC2_ON,           = CDDTLE94X1_CFG_VCC2_OFF
/// \output CddSbc_asSpiScheduleQueue[1u].CddSbc_ReadClbckFunc,                            = NULL_PTR
/// \output CddSbc_asSpiScheduleQueue[2u].CddSbc_ReadClbckFunc,                            = CddTle94x1_CbkSetVCC2
/// \output CddSbc_asSpiScheduleQueue[1u].CddSbc_boProcessEntry,                           = TRUE
/// \output CddSbc_asSpiScheduleQueue[2u].CddSbc_boProcessEntry,                           = TRUE
/// \output CddSbc_asSpiScheduleQueue[1u].CddSbc_unTxData,                                 = 0x481u
/// \output CddSbc_asSpiScheduleQueue[2u].CddSbc_unTxData,                                 = 1u
/// \output CddTle94x1_sErrorType.boScheduleTableFull,                                     = NO_ERROR
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_SetVCC2_TestCase1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  CddTle94x1_SetVCC2_Param1                                                 = CDDTLE94X1_CFG_VCC2_DEACTIVATION;
  CddSbc_ucQueueWriteIndex                                                  = 1u;
  CddSbc_asSpiScheduleQueue[1].CddSbc_boProcessEntry                        = FALSE;
  CddSbc_asSpiScheduleQueue[2].CddSbc_boProcessEntry                        = FALSE;
  CddTle94x1_sDataMirror.CtrlTx.M_S_CTRL_Register.uData.ucWord              = 4u;

  //Step 3) Call FUT
  CddTle94x1_SetVCC2(CddTle94x1_SetVCC2_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.CtrlTx.M_S_CTRL_Register.uData.sBit.bVCC2_ON,             CDDTLE94X1_CFG_VCC2_OFF, == );
  AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[1u].CddSbc_ReadClbckFunc,                                             NULL_PTR, == );
  AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[2u].CddSbc_ReadClbckFunc,                                CddTle94x1_CbkSetVCC2, == );
  AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[1u].CddSbc_boProcessEntry,                                                TRUE, == );
  AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[2u].CddSbc_boProcessEntry,                                                TRUE, == );
  AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[1u].CddSbc_unTxData,                                                    0x481u, == );
  AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[2u].CddSbc_unTxData,                                                        1u, == );
  AL_UNITTEST_CHECK(CddTle94x1_sErrorType.boScheduleTableFull,                                                      NO_ERROR, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_SetVCC2_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function for activation of VCC2
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input uint8 CddTle94x1_SetVCC2_Param1                                           = CDDTLE94X1_CFG_VCC2_DEACTIVATION;
/// \input CddSbc_ucQueueWriteIndex                                                  = 1u;
/// \input CddSbc_asSpiScheduleQueue[1].CddSbc_boProcessEntry                        = FALSE;
/// \input CddSbc_asSpiScheduleQueue[2].CddSbc_boProcessEntry                        = FALSE;
/// \input CddTle94x1_sDataMirror.CtrlTx.M_S_CTRL_Register.uData.ucWord              = 4u;
///
///    - Expectations :
///
/// \output CddTle94x1_sDataMirror.CtrlTx.M_S_CTRL_Register.uData.sBit.bVCC2_ON,           = CDDTLE94X1_CFG_VCC2_ON1
/// \output CddSbc_asSpiScheduleQueue[1u].CddSbc_ReadClbckFunc,                            = NULL_PTR
/// \output CddSbc_asSpiScheduleQueue[2u].CddSbc_ReadClbckFunc,                            = CddTle94x1_CbkSetVCC2
/// \output CddSbc_asSpiScheduleQueue[1u].CddSbc_boProcessEntry,                           = TRUE
/// \output CddSbc_asSpiScheduleQueue[2u].CddSbc_boProcessEntry,                           = TRUE
/// \output CddSbc_asSpiScheduleQueue[1u].CddSbc_unTxData,                                 = 0xC81u
/// \output CddSbc_asSpiScheduleQueue[2u].CddSbc_unTxData,                                 = 1u
/// \output CddTle94x1_sErrorType.boScheduleTableFull,                                     = NO_ERROR
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_SetVCC2_TestCase2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  CddTle94x1_SetVCC2_Param1                                                 = CDDTLE94X1_CFG_VCC2_ACTIVATION;
  CddSbc_ucQueueWriteIndex                                                  = 1u;
  CddSbc_asSpiScheduleQueue[1].CddSbc_boProcessEntry                        = FALSE;
  CddSbc_asSpiScheduleQueue[2].CddSbc_boProcessEntry                        = FALSE;
  CddTle94x1_sDataMirror.CtrlTx.M_S_CTRL_Register.uData.ucWord              = 4u;


  //Step 3) Call FUT
  CddTle94x1_SetVCC2(CddTle94x1_SetVCC2_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.CtrlTx.M_S_CTRL_Register.uData.sBit.bVCC2_ON,             CDDTLE94X1_CFG_VCC2_ON1, == );
  AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[1u].CddSbc_ReadClbckFunc,                                             NULL_PTR, == );
  AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[2u].CddSbc_ReadClbckFunc,                                CddTle94x1_CbkSetVCC2, == );
  AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[1u].CddSbc_boProcessEntry,                                                TRUE, == );
  AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[2u].CddSbc_boProcessEntry,                                                TRUE, == );
  AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[1u].CddSbc_unTxData,                                                    0xC81u, == );
  AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[2u].CddSbc_unTxData,                                                        1u, == );
  AL_UNITTEST_CHECK(CddTle94x1_sErrorType.boScheduleTableFull,                                                      NO_ERROR, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_SetVCC2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function for activation/deactivation of VCC2
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_SetVCC2(void)
{
  Mt_CddTle94x1_SetVCC2_TestCase1();
  Mt_CddTle94x1_SetVCC2_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_CbkSetVCC2_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function is setting correctly the M_S_CTRL register 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input CddTle94x1_CbkSetVCC2_Param1 = 0xDB12u;
/// \input CddTle94x1_CbkSetVCC2_Param2 = 0x1u;
///
///    - Expectations :
///
/// \output CddTle94x1_sDataMirror.CtrlRx.M_S_CTRL_Register.uData.ucWord = 0xDBu
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_CbkSetVCC2_TestCase1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  CddTle94x1_CbkSetVCC2_Param1 = 0xDB12u;
  CddTle94x1_CbkSetVCC2_Param2 = 0x1u;

  //Step 3) Call FUT
  CddTle94x1_CbkSetVCC2(CddTle94x1_CbkSetVCC2_Param1, CddTle94x1_CbkSetVCC2_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.CtrlRx.M_S_CTRL_Register.uData.ucWord, 0xDBu, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_CbkSetVCC2_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function is setting correctly the M_S_CTRL register 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input CddTle94x1_sDataMirror.CtrlRx.M_S_CTRL_Register.uData.ucWord = 0x12u;
/// \input CddTle94x1_CbkSetVCC2_Param1                                 = 0xDB12u;
/// \input CddTle94x1_CbkSetVCC2_Param2                                 = 0x2u;
///
///    - Expectations :
///
/// \output CddTle94x1_sDataMirror.CtrlRx.M_S_CTRL_Register.uData.ucWord = 0x12
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_CbkSetVCC2_TestCase2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  CddTle94x1_sDataMirror.CtrlRx.M_S_CTRL_Register.uData.ucWord = 0x12u;
  CddTle94x1_CbkSetVCC2_Param1                                 = 0xDB12u;
  CddTle94x1_CbkSetVCC2_Param2                                 = 0x2u;

  //Step 3) Call FUT
  CddTle94x1_CbkSetVCC2(CddTle94x1_CbkSetVCC2_Param1, CddTle94x1_CbkSetVCC2_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.CtrlRx.M_S_CTRL_Register.uData.ucWord, 0x12, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_CbkSetVCC2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function is setting correctly the M_S_CTRL_Register
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_CbkSetVCC2(void)
{
  Mt_CddTle94x1_CbkSetVCC2_TestCase1();
  Mt_CddTle94x1_CbkSetVCC2_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_Short_To_VBAT_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function is setting correctly short to battery
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input IoHwAbUser_Read_VCCX1_HitCount         = 0u;
/// \input IoHwAbUser_Read_VCCX1_RetVal           = CDDTLE94X1_CFG_VCC2_SHORT2VBAT_THRESHOLD+1;
/// \input LPTMR0_GetTimeElapsed_HitCount         = 0u;
/// \input LPTMR0_GetTimeElapsed_RetVal           = UTILTIME_MSEC(499u);
/// \input boTimerInitialized                     = FALSE;
/// \input CddTle94x1_sErrorType.boShorttoVBAT    = FALSE;
///
///    - Expectations :
///
/// \output IoHwAbUser_Read_VCCX1_HitCount          = 0x1u
/// \output LPTMR0_GetTimeElapsed_HitCount          = 0x2u
/// \output boTimerInitialized                      = TRUE
/// \output CddTle94x1_sErrorType.boShorttoVBAT     = FALSE;
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_Short_To_VBAT_TestCase1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  IoHwAbUser_Read_VCCX1_HitCount         = 0u;
  IoHwAbUser_Read_VCCX1_RetVal           = CDDTLE94X1_CFG_VCC2_SHORT2VBAT_THRESHOLD+1;
  LPTMR0_GetTimeElapsed_HitCount         = 0u;
  LPTMR0_GetTimeElapsed_RetVal           = UTILTIME_MSEC(499u);
  boTimerInitialized                     = FALSE;
  CddTle94x1_sErrorType.boShorttoVBAT    = FALSE;

  //Step 3) Call FUT
  CddTle94x1_Short_To_VBAT();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(IoHwAbUser_Read_VCCX1_HitCount,                        0x1u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,                        0x2u, == );
  AL_UNITTEST_CHECK(boTimerInitialized,                                    TRUE, == );
  AL_UNITTEST_CHECK(CddTle94x1_sErrorType.boShorttoVBAT,                  FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_Short_To_VBAT_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function is setting correctly short to battery
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input IoHwAbUser_Read_VCCX1_HitCount        = 0u;
/// \input IoHwAbUser_Read_VCCX1_RetVal          = CDDTLE94X1_CFG_VCC2_SHORT2VBAT_THRESHOLD+1;
/// \input LPTMR0_GetTimeElapsed_HitCount        = 0u;
/// \input LPTMR0_GetTimeElapsed_RetVal          = UTILTIME_MSEC(800u);
/// \input ulDebounceStartTime                   = UTILTIME_MSEC(300u);
/// \input boTimerInitialized                    = TRUE;
/// \input CddTle94x1_sErrorType.boShorttoVBAT   = FALSE;
///
///    - Expectations :
///
/// \output IoHwAbUser_Read_VCCX1_HitCount,           = 0x1u
/// \output LPTMR0_GetTimeElapsed_HitCount,           = 0x1u
/// \output boTimerInitialized,                       = TRUE
/// \output CddTle94x1_sErrorType.boShorttoVBAT,      = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_Short_To_VBAT_TestCase2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  IoHwAbUser_Read_VCCX1_HitCount        = 0u;
  IoHwAbUser_Read_VCCX1_RetVal          = CDDTLE94X1_CFG_VCC2_SHORT2VBAT_THRESHOLD+1;
  LPTMR0_GetTimeElapsed_HitCount        = 0u;
  LPTMR0_GetTimeElapsed_RetVal          = UTILTIME_MSEC(800u);
  ulDebounceStartTime                   = UTILTIME_MSEC(300u);
  boTimerInitialized                    = TRUE;
  CddTle94x1_sErrorType.boShorttoVBAT   = FALSE;

  //Step 3) Call FUT
  CddTle94x1_Short_To_VBAT();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(IoHwAbUser_Read_VCCX1_HitCount,             0x1u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,             0x1u, == );
  AL_UNITTEST_CHECK(boTimerInitialized,                         TRUE, == );
  AL_UNITTEST_CHECK(CddTle94x1_sErrorType.boShorttoVBAT,        TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_Short_To_VBAT_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function is setting correctly short to battery
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input IoHwAbUser_Read_VCCX1_HitCount        = 0u;
/// \input IoHwAbUser_Read_VCCX1_RetVal          = CDDTLE94X1_CFG_VCC2_SHORT2VBAT_THRESHOLD;
/// \input LPTMR0_GetTimeElapsed_HitCount        = 0u;
/// \input boTimerInitialized                    = TRUE;
/// \input CddTle94x1_sErrorType.boShorttoVBAT   = FALSE;
///
///    - Expectations :
///
/// \output IoHwAbUser_Read_VCCX1_HitCount,           = 0x1u,
/// \output LPTMR0_GetTimeElapsed_HitCount,           = 0x0u,
/// \output boTimerInitialized,                       = FALSE
/// \output CddTle94x1_sErrorType.boShorttoVBAT,      = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_Short_To_VBAT_TestCase3(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  IoHwAbUser_Read_VCCX1_HitCount        = 0u;
  IoHwAbUser_Read_VCCX1_RetVal          = CDDTLE94X1_CFG_VCC2_SHORT2VBAT_THRESHOLD;
  LPTMR0_GetTimeElapsed_HitCount        = 0u;
  boTimerInitialized                    = TRUE;
  CddTle94x1_sErrorType.boShorttoVBAT   = FALSE;

  //Step 3) Call FUT
  CddTle94x1_Short_To_VBAT();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(IoHwAbUser_Read_VCCX1_HitCount,              0x1u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,              0x0u, == );
  AL_UNITTEST_CHECK(boTimerInitialized,                         FALSE, == );
  AL_UNITTEST_CHECK(CddTle94x1_sErrorType.boShorttoVBAT,        FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_Short_To_VBAT
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function is setting correctly short to battery
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_Short_To_VBAT(void)
{
  Mt_CddTle94x1_Short_To_VBAT_TestCase1();
  Mt_CddTle94x1_Short_To_VBAT_TestCase2();
  Mt_CddTle94x1_Short_To_VBAT_TestCase3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_Reset_Short_To_VBAT_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function is reseting correctly short to battery error
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input IoHwAbUser_Read_VCCX1_HitCount          = 0u;
/// \input IoHwAbUser_Read_VCCX1_RetVal            = CDDTLE94X1_CFG_VCC2_SHORT2VBAT_THRESHOLD;
/// \input CddTle94x1_sErrorType.boShorttoVBAT     = TRUE;
/// \input boTimerInitialized                      = FALSE;
/// \input LPTMR0_GetTimeElapsed_HitCount          = 0u;
/// \input LPTMR0_GetTimeElapsed_Param1            = UTILTIME_MSEC(300u);
///
///    - Expectations :
///
/// \output IoHwAbUser_Read_VCCX1_HitCount,            = 0x1u,
/// \output LPTMR0_GetTimeElapsed_HitCount,            = 0x2u,
/// \output boTimerInitialized,                        = TRUE,
/// \output CddTle94x1_sErrorType.boShorttoVBAT,       = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_Reset_Short_To_VBAT_TestCase1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  IoHwAbUser_Read_VCCX1_HitCount          = 0u;
  IoHwAbUser_Read_VCCX1_RetVal            = CDDTLE94X1_CFG_VCC2_SHORT2VBAT_THRESHOLD;
  CddTle94x1_sErrorType.boShorttoVBAT     = TRUE;
  boTimerInitialized                      = FALSE;
  LPTMR0_GetTimeElapsed_HitCount          = 0u;
  LPTMR0_GetTimeElapsed_Param1            = UTILTIME_MSEC(300u);

  //Step 3) Call FUT
  CddTle94x1_Reset_Short_To_VBAT();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(IoHwAbUser_Read_VCCX1_HitCount,             0x1u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,             0x2u, == );
  AL_UNITTEST_CHECK(boTimerInitialized,                         TRUE, == );
  AL_UNITTEST_CHECK(CddTle94x1_sErrorType.boShorttoVBAT,        TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_Reset_Short_To_VBAT_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function is reseting correctly short to battery error
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input IoHwAbUser_Read_VCCX1_HitCount          = 0u;
/// \input IoHwAbUser_Read_VCCX1_RetVal            = CDDTLE94X1_CFG_VCC2_SHORT2VBAT_THRESHOLD;
/// \input CddTle94x1_sErrorType.boShorttoVBAT     = TRUE;
/// \input boTimerInitialized                      = TRUE;
/// \input LPTMR0_GetTimeElapsed_HitCount          = 0u;
/// \input LPTMR0_GetTimeElapsed_Param1            = UTILTIME_MSEC(600u);
/// \input ulDebounceStartTime                     = UTILTIME_MSEC(100u);
///
///    - Expectations :
///
/// \output IoHwAbUser_Read_VCCX1_HitCount,            = 0x1u
/// \output LPTMR0_GetTimeElapsed_HitCount,            = 0x1u
/// \output boTimerInitialized,                        = TRUE
/// \output CddTle94x1_sErrorType.boShorttoVBAT,       = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_Reset_Short_To_VBAT_TestCase2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  IoHwAbUser_Read_VCCX1_HitCount          = 0u;
  IoHwAbUser_Read_VCCX1_RetVal            = CDDTLE94X1_CFG_VCC2_SHORT2VBAT_THRESHOLD;
  CddTle94x1_sErrorType.boShorttoVBAT     = TRUE;
  boTimerInitialized                      = TRUE;
  LPTMR0_GetTimeElapsed_HitCount          = 0u;
  LPTMR0_GetTimeElapsed_Param1            = UTILTIME_MSEC(600u);
  ulDebounceStartTime                     = UTILTIME_MSEC(100u);

  //Step 3) Call FUT
  CddTle94x1_Reset_Short_To_VBAT();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(IoHwAbUser_Read_VCCX1_HitCount,             0x1u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,             0x1u, == );
  AL_UNITTEST_CHECK(boTimerInitialized,                         TRUE, == );
  AL_UNITTEST_CHECK(CddTle94x1_sErrorType.boShorttoVBAT,       FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_Reset_Short_To_VBAT_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function is reseting correctly short to battery error
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input IoHwAbUser_Read_VCCX1_HitCount          = 0u;
/// \input IoHwAbUser_Read_VCCX1_RetVal            = CDDTLE94X1_CFG_VCC2_SHORT2VBAT_THRESHOLD+1;
/// \input CddTle94x1_sErrorType.boShorttoVBAT     = TRUE;
/// \input boTimerInitialized                      = TRUE;
/// \input LPTMR0_GetTimeElapsed_HitCount          = 0u;
/// \input LPTMR0_GetTimeElapsed_Param1            = UTILTIME_MSEC(500u);
///
///    - Expectations :
///
/// \output IoHwAbUser_Read_VCCX1_HitCount,            = 0x1u
/// \output LPTMR0_GetTimeElapsed_HitCount,            = 0x0u
/// \output boTimerInitialized,                        = FALSE
/// \output CddTle94x1_sErrorType.boShorttoVBAT,       = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_Reset_Short_To_VBAT_TestCase3(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  IoHwAbUser_Read_VCCX1_HitCount          = 0u;
  IoHwAbUser_Read_VCCX1_RetVal            = CDDTLE94X1_CFG_VCC2_SHORT2VBAT_THRESHOLD+1;
  CddTle94x1_sErrorType.boShorttoVBAT     = TRUE;
  boTimerInitialized                      = TRUE;
  LPTMR0_GetTimeElapsed_HitCount          = 0u;
  LPTMR0_GetTimeElapsed_Param1            = UTILTIME_MSEC(500u);

  //Step 3) Call FUT
  CddTle94x1_Reset_Short_To_VBAT();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(IoHwAbUser_Read_VCCX1_HitCount,             0x1u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,             0x0u, == );
  AL_UNITTEST_CHECK(boTimerInitialized,                        FALSE, == );
  AL_UNITTEST_CHECK(CddTle94x1_sErrorType.boShorttoVBAT,        TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_Short_To_VBAT
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function is reseting correctly short to battery error
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_Reset_Short_To_VBAT(void)
{
  Mt_CddTle94x1_Reset_Short_To_VBAT_TestCase1();
  Mt_CddTle94x1_Reset_Short_To_VBAT_TestCase2();
  Mt_CddTle94x1_Reset_Short_To_VBAT_TestCase3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_Short_To_GND_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function is setting correctly short to ground
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input IoHwAbUser_Read_VCCX1_HitCount         = 0u;
/// \input IoHwAbUser_Read_VCCX1_RetVal           = CDDTLE94X1_CFG_VCC2_SHORT2VGND_THRESHOLD+1;
/// \input LPTMR0_GetTimeElapsed_HitCount         = 0u;
/// \input LPTMR0_GetTimeElapsed_RetVal           = UTILTIME_MSEC(499u);
/// \input boTimerInitialized                     = FALSE;
/// \input CddTle94x1_sErrorType.boShorttoGND     = FALSE;
///
///    - Expectations :
///
/// \output IoHwAbUser_Read_VCCX1_HitCount          = 0x1u
/// \output LPTMR0_GetTimeElapsed_HitCount          = 0x2u
/// \output boTimerInitialized                      = TRUE
/// \output CddTle94x1_sErrorType.boShorttoGND      = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_Short_To_GND_TestCase1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  IoHwAbUser_Read_VCCX1_HitCount         = 0u;
  IoHwAbUser_Read_VCCX1_RetVal           = CDDTLE94X1_CFG_VCC2_SHORT2VGND_THRESHOLD-1;
  LPTMR0_GetTimeElapsed_HitCount         = 0u;
  LPTMR0_GetTimeElapsed_RetVal           = UTILTIME_MSEC(499u);
  boTimerInitialized                     = FALSE;
  CddTle94x1_sErrorType.boShorttoGND     = FALSE;

  //Step 3) Call FUT
  CddTle94x1_Short_To_GND();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(IoHwAbUser_Read_VCCX1_HitCount,                        0x1u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,                        0x2u, == );
  AL_UNITTEST_CHECK(boTimerInitialized,                                    TRUE, == );
  AL_UNITTEST_CHECK(CddTle94x1_sErrorType.boShorttoGND,                   FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_Short_To_GND_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function is setting correctly short to ground
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input IoHwAbUser_Read_VCCX1_HitCount        = 0u;
/// \input IoHwAbUser_Read_VCCX1_RetVal          = CDDTLE94X1_CFG_VCC2_SHORT2VGND_THRESHOLD-1;
/// \input LPTMR0_GetTimeElapsed_HitCount        = 0u;
/// \input LPTMR0_GetTimeElapsed_RetVal          = UTILTIME_MSEC(800u);
/// \input ulDebounceStartTime                   = UTILTIME_MSEC(300u);
/// \input boTimerInitialized                    = TRUE;
/// \input CddTle94x1_sErrorType.boShorttoGND    = FALSE;
///
///    - Expectations :
///
/// \output IoHwAbUser_Read_VCCX1_HitCount,           = 0x1u
/// \output LPTMR0_GetTimeElapsed_HitCount,           = 0x1u
/// \output boTimerInitialized,                       = TRUE
/// \output CddTle94x1_sErrorType.boShorttoGND,       = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_Short_To_GND_TestCase2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  IoHwAbUser_Read_VCCX1_HitCount        = 0u;
  IoHwAbUser_Read_VCCX1_RetVal          = CDDTLE94X1_CFG_VCC2_SHORT2VGND_THRESHOLD-1;
  LPTMR0_GetTimeElapsed_HitCount        = 0u;
  LPTMR0_GetTimeElapsed_RetVal          = UTILTIME_MSEC(800u);
  ulDebounceStartTime                   = UTILTIME_MSEC(300u);
  boTimerInitialized                    = TRUE;
  CddTle94x1_sErrorType.boShorttoGND    = FALSE;

  //Step 3) Call FUT
  CddTle94x1_Short_To_GND();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(IoHwAbUser_Read_VCCX1_HitCount,             0x1u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,             0x1u, == );
  AL_UNITTEST_CHECK(boTimerInitialized,                         TRUE, == );
  AL_UNITTEST_CHECK(CddTle94x1_sErrorType.boShorttoGND,         TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_Short_To_GND_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function is setting correctly short to ground
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input IoHwAbUser_Read_VCCX1_HitCount        = 0u;
/// \input IoHwAbUser_Read_VCCX1_RetVal          = CDDTLE94X1_CFG_VCC2_SHORT2VGND_THRESHOLD;
/// \input LPTMR0_GetTimeElapsed_HitCount        = 0u;
/// \input boTimerInitialized                    = TRUE;
/// \input CddTle94x1_sErrorType.boShorttoGND    = FALSE;
///
///    - Expectations :
///
/// \output IoHwAbUser_Read_VCCX1_HitCount,           = 0x1u,
/// \output LPTMR0_GetTimeElapsed_HitCount,           = 0x0u,
/// \output boTimerInitialized,                       = FALSE
/// \output CddTle94x1_sErrorType.boShorttoGND,       = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_Short_To_GND_TestCase3(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  IoHwAbUser_Read_VCCX1_HitCount        = 0u;
  IoHwAbUser_Read_VCCX1_RetVal          = CDDTLE94X1_CFG_VCC2_SHORT2VGND_THRESHOLD;
  LPTMR0_GetTimeElapsed_HitCount        = 0u;
  boTimerInitialized                    = TRUE;
  CddTle94x1_sErrorType.boShorttoGND    = FALSE;

  //Step 3) Call FUT
  CddTle94x1_Short_To_GND();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(IoHwAbUser_Read_VCCX1_HitCount,              0x1u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,              0x0u, == );
  AL_UNITTEST_CHECK(boTimerInitialized,                         FALSE, == );
  AL_UNITTEST_CHECK(CddTle94x1_sErrorType.boShorttoGND,         FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_Short_To_GND
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function is setting correctly short to ground
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_Short_To_GND(void)
{
  Mt_CddTle94x1_Short_To_GND_TestCase1();
  Mt_CddTle94x1_Short_To_GND_TestCase2();
  Mt_CddTle94x1_Short_To_GND_TestCase3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_Reset_Short_To_GND_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function is reseting correctly short to battery error
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input IoHwAbUser_Read_VCCX1_HitCount          = 0u;
/// \input IoHwAbUser_Read_VCCX1_RetVal            = CDDTLE94X1_CFG_VCC2_SHORT2VGND_THRESHOLD;
/// \input CddTle94x1_sErrorType.boShorttoGND      = TRUE;
/// \input boTimerInitialized                      = FALSE;
/// \input LPTMR0_GetTimeElapsed_HitCount          = 0u;
/// \input LPTMR0_GetTimeElapsed_Param1            = UTILTIME_MSEC(300u);
///
///    - Expectations :
///
/// \output IoHwAbUser_Read_VCCX1_HitCount,            = 0x1u
/// \output LPTMR0_GetTimeElapsed_HitCount,            = 0x2u
/// \output boTimerInitialized,                        = TRUE
/// \output CddTle94x1_sErrorType.boShorttoGND ,       = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_Reset_Short_To_GND_TestCase1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  IoHwAbUser_Read_VCCX1_HitCount          = 0u;
  IoHwAbUser_Read_VCCX1_RetVal            = CDDTLE94X1_CFG_VCC2_SHORT2VGND_THRESHOLD;
  CddTle94x1_sErrorType.boShorttoGND      = TRUE;
  boTimerInitialized                      = FALSE;
  LPTMR0_GetTimeElapsed_HitCount          = 0u;
  LPTMR0_GetTimeElapsed_Param1            = UTILTIME_MSEC(300u);

  //Step 3) Call FUT
  CddTle94x1_Reset_Short_To_GND();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(IoHwAbUser_Read_VCCX1_HitCount,             0x1u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,             0x2u, == );
  AL_UNITTEST_CHECK(boTimerInitialized,                         TRUE, == );
  AL_UNITTEST_CHECK(CddTle94x1_sErrorType.boShorttoGND ,        TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_Reset_Short_To_GND_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function is reseting correctly short to battery error
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input IoHwAbUser_Read_VCCX1_HitCount          = 0u;
/// \input IoHwAbUser_Read_VCCX1_RetVal            = CDDTLE94X1_CFG_VCC2_SHORT2VGND_THRESHOLD;
/// \input CddTle94x1_sErrorType.boShorttoGND      = TRUE;
/// \input boTimerInitialized                      = TRUE;
/// \input LPTMR0_GetTimeElapsed_HitCount          = 0u;
/// \input LPTMR0_GetTimeElapsed_Param1            = UTILTIME_MSEC(600u);
/// \input ulDebounceStartTime                     = UTILTIME_MSEC(100u);
///
///    - Expectations :
///
/// \output IoHwAbUser_Read_VCCX1_HitCount,            = 0x1u
/// \output LPTMR0_GetTimeElapsed_HitCount,            = 0x1u
/// \output boTimerInitialized,                        = TRUE
/// \output CddTle94x1_sErrorType.boShorttoGND ,       = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_Reset_Short_To_GND_TestCase2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  IoHwAbUser_Read_VCCX1_HitCount          = 0u;
  IoHwAbUser_Read_VCCX1_RetVal            = CDDTLE94X1_CFG_VCC2_SHORT2VGND_THRESHOLD;
  CddTle94x1_sErrorType.boShorttoGND      = TRUE;
  boTimerInitialized                      = TRUE;
  LPTMR0_GetTimeElapsed_HitCount          = 0u;
  LPTMR0_GetTimeElapsed_Param1            = UTILTIME_MSEC(600u);
  ulDebounceStartTime                     = UTILTIME_MSEC(100u);

  //Step 3) Call FUT
  CddTle94x1_Reset_Short_To_GND();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(IoHwAbUser_Read_VCCX1_HitCount,             0x1u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,             0x1u, == );
  AL_UNITTEST_CHECK(boTimerInitialized,                         TRUE, == );
  AL_UNITTEST_CHECK(CddTle94x1_sErrorType.boShorttoGND ,       FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_Reset_Short_To_GND_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function is reseting correctly short to battery error
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input IoHwAbUser_Read_VCCX1_HitCount          = 0u;
/// \input IoHwAbUser_Read_VCCX1_RetVal            = CDDTLE94X1_CFG_VCC2_SHORT2VGND_THRESHOLD-1;
/// \input CddTle94x1_sErrorType.boShorttoGND      = TRUE;
/// \input boTimerInitialized                      = TRUE;
/// \input LPTMR0_GetTimeElapsed_HitCount          = 0u;
/// \input LPTMR0_GetTimeElapsed_Param1            = UTILTIME_MSEC(500u);
///
///    - Expectations :
///
/// \output IoHwAbUser_Read_VCCX1_HitCount,            = 0x1u
/// \output LPTMR0_GetTimeElapsed_HitCount,            = 0x0u
/// \output boTimerInitialized,                        = FALSE
/// \output CddTle94x1_sErrorType.boShorttoGND ,       = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_Reset_Short_To_GND_TestCase3(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  IoHwAbUser_Read_VCCX1_HitCount          = 0u;
  IoHwAbUser_Read_VCCX1_RetVal            = CDDTLE94X1_CFG_VCC2_SHORT2VGND_THRESHOLD-1;
  CddTle94x1_sErrorType.boShorttoGND      = TRUE;
  boTimerInitialized                      = TRUE;
  LPTMR0_GetTimeElapsed_HitCount          = 0u;
  LPTMR0_GetTimeElapsed_Param1            = UTILTIME_MSEC(500u);

  //Step 3) Call FUT
  CddTle94x1_Reset_Short_To_GND();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(IoHwAbUser_Read_VCCX1_HitCount,             0x1u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,             0x0u, == );
  AL_UNITTEST_CHECK(boTimerInitialized,                        FALSE, == );
  AL_UNITTEST_CHECK(CddTle94x1_sErrorType.boShorttoGND ,        TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_Reset_Short_To_GND
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function is reseting correctly short to battery error
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_Reset_Short_To_GND(void)
{
  Mt_CddTle94x1_Reset_Short_To_GND_TestCase1();
  Mt_CddTle94x1_Reset_Short_To_GND_TestCase2();
  Mt_CddTle94x1_Reset_Short_To_GND_TestCase3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_CbkReadThermStatReg_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function is updating correctly the CTRL register
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input CddTle94x1_sDataMirror.StatRx.THERM_STAT_Register.uData.ucWord  = 0u;
/// \input CddTle94x1_CbkReadThermStatReg_Param1                           = 0xBD01u;
/// \input CddTle94x1_CbkReadThermStatReg_Param2                           = CDDTLE94X1_REGS_THERM_STAT_ADR;
///
///    - Expectations :
///
/// \output CddTle94x1_sDataMirror.StatRx.THERM_STAT_Register.uData.ucWord            = 0xBDu,
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_CbkReadThermStatReg_TestCase1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  CddTle94x1_sDataMirror.StatRx.THERM_STAT_Register.uData.ucWord  = 0u;
  CddTle94x1_CbkReadThermStatReg_Param1                           = 0xBD01u;
  CddTle94x1_CbkReadThermStatReg_Param2                           = CDDTLE94X1_REGS_THERM_STAT_ADR;

  //Step 3) Call FUT
  CddTle94x1_CbkReadThermStatReg(CddTle94x1_CbkReadThermStatReg_Param1, CddTle94x1_CbkReadThermStatReg_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.StatRx.THERM_STAT_Register.uData.ucWord,             0xBDu, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_CbkReadThermStatReg_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function is not updating the CTRL register
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input CddTle94x1_sDataMirror.StatRx.THERM_STAT_Register.uData.ucWord  = 0u;
/// \input CddTle94x1_CbkReadThermStatReg_Param1                           = 0xBD01u;
/// \input CddTle94x1_CbkReadThermStatReg_Param2                           = CDDTLE94X1_REGS_GPIO_OC_STAT_ADR;
///
///    - Expectations :
///
/// \output CddTle94x1_sDataMirror.StatRx.THERM_STAT_Register.uData.ucWord            = 0x0u,
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_CbkReadThermStatReg_TestCase2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  CddTle94x1_sDataMirror.StatRx.THERM_STAT_Register.uData.ucWord  = 0u;
  CddTle94x1_CbkReadThermStatReg_Param1                           = 0xBD01u;
  CddTle94x1_CbkReadThermStatReg_Param2                           = CDDTLE94X1_REGS_GPIO_OC_STAT_ADR;

  //Step 3) Call FUT
  CddTle94x1_CbkReadThermStatReg(CddTle94x1_CbkReadThermStatReg_Param1, CddTle94x1_CbkReadThermStatReg_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.StatRx.THERM_STAT_Register.uData.ucWord,             0x0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_CbkReadThermStatReg
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function is updating correctly the CTRL register
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_CbkReadThermStatReg(void)
{
  Mt_CddTle94x1_CbkReadThermStatReg_TestCase1();
  Mt_CddTle94x1_CbkReadThermStatReg_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_Thermal_Shutdown_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function checking correctly the thermal shutdown and if is 
///                     setting correctly the VCC2 flag
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input CddTle94x1_ulTSDHook_Activ_Val                                = 20212022u;
/// \input CddSbc_ucQueueWriteIndex                                      = 0u;
/// \input CddSbc_asSpiScheduleQueue[0].CddSbc_boProcessEntry            = FALSE;
/// \input CddSbc_asSpiScheduleQueue[1].CddSbc_boProcessEntry            = FALSE;
/// \input CddSbc_asSpiScheduleQueue[2].CddSbc_boProcessEntry            = FALSE;
/// \input CddSbc_asSpiScheduleQueue[3].CddSbc_boProcessEntry            = FALSE;
/// \input CddTle94x1_sDataMirror.CtrlTx.M_S_CTRL_Register.uData.ucWord  = 0u;
///
///    - Expectations :
///
/// \output CddTle94x1_sDataMirror.CtrlTx.M_S_CTRL_Register.uData.sBit.bVCC2_ON,             = CDDTLE94X1_CFG_VCC2_OFF
/// \output CddTle94x1_sErrorType.boTSDError,                                                = TRUE
/// \output CddSbc_asSpiScheduleQueue[0u].CddSbc_ReadClbckFunc,                              = NULL_PTR
/// \output CddSbc_asSpiScheduleQueue[1u].CddSbc_ReadClbckFunc,                              = CddTle94x1_CbkSetVCC2
/// \output CddSbc_asSpiScheduleQueue[2u].CddSbc_ReadClbckFunc,                              = NULL_PTR
/// \output CddSbc_asSpiScheduleQueue[3u].CddSbc_ReadClbckFunc,                              = CddTle94x1_CbkReadThermStatReg
/// \output CddSbc_asSpiScheduleQueue[0u].CddSbc_boProcessEntry,                             = TRUE
/// \output CddSbc_asSpiScheduleQueue[1u].CddSbc_boProcessEntry,                             = TRUE
/// \output CddSbc_asSpiScheduleQueue[0u].CddSbc_unTxData,                                   = 129u
/// \output CddSbc_asSpiScheduleQueue[1u].CddSbc_unTxData,                                   = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_Thermal_Shutdown_TestCase1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  CddTle94x1_ulTSDHook_Activ_Val                                = 20212022u;
  CddSbc_ucQueueWriteIndex                                      = 0u;
  CddSbc_asSpiScheduleQueue[0].CddSbc_boProcessEntry            = FALSE;
  CddSbc_asSpiScheduleQueue[1].CddSbc_boProcessEntry            = FALSE;
  CddSbc_asSpiScheduleQueue[2].CddSbc_boProcessEntry            = FALSE;
  CddSbc_asSpiScheduleQueue[3].CddSbc_boProcessEntry            = FALSE;
  CddTle94x1_sDataMirror.CtrlTx.M_S_CTRL_Register.uData.ucWord  = 0u;

  //Step 3) Call FUT
  CddTle94x1_Thermal_Shutdown();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.CtrlTx.M_S_CTRL_Register.uData.sBit.bVCC2_ON,             CDDTLE94X1_CFG_VCC2_OFF, == );
  AL_UNITTEST_CHECK(CddTle94x1_sErrorType.boTSDError,                                                                   TRUE, == );
  AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[0u].CddSbc_ReadClbckFunc,                                             NULL_PTR, == );
  AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[1u].CddSbc_ReadClbckFunc,                                CddTle94x1_CbkSetVCC2, == );
  AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[2u].CddSbc_ReadClbckFunc,                                             NULL_PTR, == );
  AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[3u].CddSbc_ReadClbckFunc,                       CddTle94x1_CbkReadThermStatReg, == );
  AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[0u].CddSbc_boProcessEntry,                                                TRUE, == );
  AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[1u].CddSbc_boProcessEntry,                                                TRUE, == );
  AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[0u].CddSbc_unTxData,                                                      129u, == );
  AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[1u].CddSbc_unTxData,                                                        1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_Thermal_Shutdown_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function checking correctly the thermal shutdown and if is 
///                     setting correctly the VCC2 flag
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input CddTle94x1_ulTSDHook_Activ_Val                                        = 0u;
/// \input CddTle94x1_sDataMirror.StatRx.THERM_STAT_Register.uData.sBit.bTSD1    = 0x5u;
/// \input CddSbc_ucQueueWriteIndex                                              = 0u;
/// \input CddSbc_asSpiScheduleQueue[0].CddSbc_boProcessEntry                    = FALSE;
/// \input CddSbc_asSpiScheduleQueue[1].CddSbc_boProcessEntry                    = FALSE;
///
///    - Expectations :
///
/// \output CddTle94x1_sDataMirror.CtrlTx.M_S_CTRL_Register.uData.sBit.bVCC2_ON,            = CDDTLE94X1_CFG_VCC2_OFF
/// \output CddSbc_asSpiScheduleQueue[0u].CddSbc_ReadClbckFunc,                             = NULL_PTR
/// \output CddSbc_asSpiScheduleQueue[1u].CddSbc_ReadClbckFunc,                             = CddTle94x1_CbkReadThermStatReg
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_Thermal_Shutdown_TestCase2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  CddTle94x1_ulTSDHook_Activ_Val                                        = 0u;
  CddTle94x1_sDataMirror.StatRx.THERM_STAT_Register.uData.sBit.bTSD1    = 0x5u;
  CddSbc_ucQueueWriteIndex                                              = 0u;
  CddSbc_asSpiScheduleQueue[0].CddSbc_boProcessEntry                    = FALSE;
  CddSbc_asSpiScheduleQueue[1].CddSbc_boProcessEntry                    = FALSE;

  //Step 3) Call FUT
  CddTle94x1_Thermal_Shutdown();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.CtrlTx.M_S_CTRL_Register.uData.sBit.bVCC2_ON,             CDDTLE94X1_CFG_VCC2_OFF, == );
  AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[0u].CddSbc_ReadClbckFunc,                                             NULL_PTR, == );
  AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[1u].CddSbc_ReadClbckFunc,                       CddTle94x1_CbkReadThermStatReg, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_Thermal_Shutdown_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function checking correctly the thermal shutdown and if is 
///                     setting correctly the VCC2 flag
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input CddTle94x1_ulTSDHook_Activ_Val                                        = 0u;
/// \input CddTle94x1_sDataMirror.StatRx.THERM_STAT_Register.uData.sBit.bTSD1    = 0u;
/// \input CddSbc_ucQueueWriteIndex                                              = 0u;
/// \input CddSbc_asSpiScheduleQueue[0].CddSbc_boProcessEntry                    = FALSE;
/// \input CddSbc_asSpiScheduleQueue[1].CddSbc_boProcessEntry                    = FALSE;
/// \input CddTle94x1_sErrorType.boTSDError                                      = TRUE;
/// \input LPTMR0_GetTimeElapsed_HitCount                                        = 0;
/// \input LPTMR0_GetTimeElapsed_RetVal                                          = 0x300u;
///
///    - Expectations :
///
/// \output CddTle94x1_sDataMirror.CtrlTx.M_S_CTRL_Register.uData.sBit.bVCC2_ON,           = CDDTLE94X1_CFG_VCC2_OFF
/// \output CddSbc_asSpiScheduleQueue[0u].CddSbc_ReadClbckFunc,                            = NULL_PTR
/// \output CddSbc_asSpiScheduleQueue[1u].CddSbc_ReadClbckFunc,                            = CddTle94x1_CbkReadThermStatReg
/// \output CddTle94x1_sErrorType.boTSDError,                                              = FALSE
/// \output LPTMR0_GetTimeElapsed_HitCount,                                                = 2u
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_Thermal_Shutdown_TestCase3(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  CddTle94x1_ulTSDHook_Activ_Val                                        = 0u;
  CddTle94x1_sDataMirror.StatRx.THERM_STAT_Register.uData.sBit.bTSD1    = 0u;
  CddSbc_ucQueueWriteIndex                                              = 0u;
  CddSbc_asSpiScheduleQueue[0].CddSbc_boProcessEntry                    = FALSE;
  CddSbc_asSpiScheduleQueue[1].CddSbc_boProcessEntry                    = FALSE;
  CddTle94x1_sErrorType.boTSDError                                      = TRUE;
  LPTMR0_GetTimeElapsed_HitCount                                        = 0;
  LPTMR0_GetTimeElapsed_RetVal                                          = 0x300u;

  //Step 3) Call FUT
  CddTle94x1_Thermal_Shutdown();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.CtrlTx.M_S_CTRL_Register.uData.sBit.bVCC2_ON,             CDDTLE94X1_CFG_VCC2_OFF, == );
  AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[0u].CddSbc_ReadClbckFunc,                                             NULL_PTR, == );
  AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[1u].CddSbc_ReadClbckFunc,                       CddTle94x1_CbkReadThermStatReg, == );
  AL_UNITTEST_CHECK(CddTle94x1_sErrorType.boTSDError,                                                                  FALSE, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,                                                                       2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_Thermal_Shutdown_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function checking correctly the thermal shutdown and if is 
///                     setting correctly the VCC2 flag
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input CddTle94x1_ulTSDHook_Activ_Val                                        = 0u;
/// \input CddTle94x1_sDataMirror.StatRx.THERM_STAT_Register.uData.sBit.bTSD1    = 0u;
/// \input CddSbc_ucQueueWriteIndex                                              = 0u;
/// \input CddSbc_asSpiScheduleQueue[0].CddSbc_boProcessEntry                    = FALSE;
/// \input CddSbc_asSpiScheduleQueue[1].CddSbc_boProcessEntry                    = FALSE;
/// \input CddSbc_asSpiScheduleQueue[2].CddSbc_boProcessEntry                    = FALSE;
/// \input CddSbc_asSpiScheduleQueue[3].CddSbc_boProcessEntry                    = FALSE;
/// \input CddTle94x1_sErrorType.boTSDError                                      = FALSE;
/// \input LPTMR0_GetTimeElapsed_HitCount                                        = 0;
/// \input LPTMR0_GetTimeElapsed_RetVal                                          = UTILTIME_SEC(5u);
/// \input boTimerInitialized                                                    = TRUE;
/// \input ulDebounceStartTime                                                   = 0;
///
///    - Expectations :
///
/// \output CddTle94x1_sDataMirror.CtrlTx.M_S_CTRL_Register.uData.sBit.bVCC2_ON,            = CDDTLE94X1_CFG_VCC2_ON1
/// \output CddSbc_asSpiScheduleQueue[0u].CddSbc_ReadClbckFunc,                             = NULL_PTR
/// \output CddSbc_asSpiScheduleQueue[1u].CddSbc_ReadClbckFunc,                             = CddTle94x1_CbkSetVCC2
/// \output CddSbc_asSpiScheduleQueue[2u].CddSbc_ReadClbckFunc,                             = NULL_PTR
/// \output CddSbc_asSpiScheduleQueue[3u].CddSbc_ReadClbckFunc,                             = CddTle94x1_CbkReadThermStatReg
/// \output CddTle94x1_sErrorType.boTSDError,                                               = FALSE
/// \output LPTMR0_GetTimeElapsed_HitCount,                                                 = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_Thermal_Shutdown_TestCase4(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  CddTle94x1_ulTSDHook_Activ_Val                                        = 0u;
  CddTle94x1_sDataMirror.StatRx.THERM_STAT_Register.uData.sBit.bTSD1    = 0u;
  CddSbc_ucQueueWriteIndex                                              = 0u;
  CddSbc_asSpiScheduleQueue[0].CddSbc_boProcessEntry                    = FALSE;
  CddSbc_asSpiScheduleQueue[1].CddSbc_boProcessEntry                    = FALSE;
  CddSbc_asSpiScheduleQueue[2].CddSbc_boProcessEntry                    = FALSE;
  CddSbc_asSpiScheduleQueue[3].CddSbc_boProcessEntry                    = FALSE;
  CddTle94x1_sErrorType.boTSDError                                      = FALSE;
  LPTMR0_GetTimeElapsed_HitCount                                        = 0;
  LPTMR0_GetTimeElapsed_RetVal                                          = UTILTIME_SEC(5u);
  boTimerInitialized                                                    = TRUE;
  ulDebounceStartTime                                                   = 0;

  //Step 3) Call FUT
  CddTle94x1_Thermal_Shutdown();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.CtrlTx.M_S_CTRL_Register.uData.sBit.bVCC2_ON,             CDDTLE94X1_CFG_VCC2_ON1, == );
  AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[0u].CddSbc_ReadClbckFunc,                                             NULL_PTR, == );
  AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[1u].CddSbc_ReadClbckFunc,                                CddTle94x1_CbkSetVCC2, == );
  AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[2u].CddSbc_ReadClbckFunc,                                             NULL_PTR, == );
  AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[3u].CddSbc_ReadClbckFunc,                       CddTle94x1_CbkReadThermStatReg, == );
  AL_UNITTEST_CHECK(CddTle94x1_sErrorType.boTSDError,                                                                  FALSE, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,                                                                       1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_Thermal_Shutdown_TestCase5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function checking correctly the thermal shutdown and if is 
///                     setting correctly the VCC2 flag
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input CddTle94x1_ulTSDHook_Activ_Val                                        = 0u;
/// \input CddTle94x1_sDataMirror.StatRx.THERM_STAT_Register.uData.sBit.bTSD1    = 0u;
/// \input CddSbc_ucQueueWriteIndex                                              = 0u;
/// \input CddSbc_asSpiScheduleQueue[0].CddSbc_boProcessEntry                    = FALSE;
/// \input CddSbc_asSpiScheduleQueue[1].CddSbc_boProcessEntry                    = FALSE;
/// \input CddTle94x1_sErrorType.boTSDError                                      = FALSE;
/// \input LPTMR0_GetTimeElapsed_HitCount                                        = 0;
/// \input boTimerInitialized                                                    = FALSE;
/// \input ulDebounceStartTime                                                   = 0;
///
///    - Expectations :
///
/// \output CddTle94x1_sDataMirror.CtrlTx.M_S_CTRL_Register.uData.sBit.bVCC2_ON           = CDDTLE94X1_CFG_VCC2_ON1
/// \output CddSbc_asSpiScheduleQueue[0u].CddSbc_ReadClbckFunc,                           = NULL_PTR
/// \output CddSbc_asSpiScheduleQueue[1u].CddSbc_ReadClbckFunc,                           = CddTle94x1_CbkReadThermStatReg
/// \output CddTle94x1_sErrorType.boTSDError,                                             = FALSE
/// \output LPTMR0_GetTimeElapsed_HitCount,                                               = 0u
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_Thermal_Shutdown_TestCase5(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  CddTle94x1_ulTSDHook_Activ_Val                                        = 0u;
  CddTle94x1_sDataMirror.StatRx.THERM_STAT_Register.uData.sBit.bTSD1    = 0u;
  CddSbc_ucQueueWriteIndex                                              = 0u;
  CddSbc_asSpiScheduleQueue[0].CddSbc_boProcessEntry                    = FALSE;
  CddSbc_asSpiScheduleQueue[1].CddSbc_boProcessEntry                    = FALSE;
  CddTle94x1_sErrorType.boTSDError                                      = FALSE;
  LPTMR0_GetTimeElapsed_HitCount                                        = 0;
  boTimerInitialized                                                    = FALSE;
  ulDebounceStartTime                                                   = 0;

  //Step 3) Call FUT
  CddTle94x1_Thermal_Shutdown();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddTle94x1_sDataMirror.CtrlTx.M_S_CTRL_Register.uData.sBit.bVCC2_ON,             CDDTLE94X1_CFG_VCC2_ON1, == );
  AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[0u].CddSbc_ReadClbckFunc,                                             NULL_PTR, == );
  AL_UNITTEST_CHECK(CddSbc_asSpiScheduleQueue[1u].CddSbc_ReadClbckFunc,                       CddTle94x1_CbkReadThermStatReg, == );
  AL_UNITTEST_CHECK(CddTle94x1_sErrorType.boTSDError,                                                                  FALSE, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,                                                                       0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTle94x1_Thermal_Shutdown
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function checking correctly the thermal shutdown and if is 
///                     setting correctly the VCC2 flag
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddTle94x1_Thermal_Shutdown(void)
{
  Mt_CddTle94x1_Thermal_Shutdown_TestCase1();
  Mt_CddTle94x1_Thermal_Shutdown_TestCase2();
  Mt_CddTle94x1_Thermal_Shutdown_TestCase3();
  Mt_CddTle94x1_Thermal_Shutdown_TestCase4();
  Mt_CddTle94x1_Thermal_Shutdown_TestCase5();
}

#endif // (CDDSBC_CFG_VCC2_OPERATION == STD_ON)

void ALUnitTest_AddTests(void)
{
  ALUnitTest_AddFunction("Mt_CddTle94x1_Save_WK_STAT_0", Mt_CddTle94x1_Save_WK_STAT_0);
  ALUnitTest_AddFunction("Mt_CddTle94x1_Save_SUP_STAT_0", Mt_CddTle94x1_Save_SUP_STAT_0);
  ALUnitTest_AddFunction("Mt_CddTle94x1_InitStatRead", Mt_CddTle94x1_InitStatRead);
  ALUnitTest_AddFunction("Mt_CddTle94x1_InitSettings", Mt_CddTle94x1_InitSettings);
  ALUnitTest_AddFunction("Mt_CddTle94x1_Init", Mt_CddTle94x1_Init);
//  ALUnitTest_AddFunction("Mt_rpiCddSbc20ms", Mt_rpiCddSbc20ms);
  ALUnitTest_AddFunction("Mt_CddTle94x1c_SetCanMode", Mt_CddTle94x1_SetCanMode);
  ALUnitTest_AddFunction("Mt_CddTle94x1_ValidateCanMode", Mt_CddTle94x1_ValidateCanMode);
  ALUnitTest_AddFunction("Mt_CddTle94x1_GetCanMode", Mt_CddTle94x1_GetCanMode);
  ALUnitTest_AddFunction("Mt_CddTle94x1_GetCanUV", Mt_CddTle94x1_GetCanUV);
  ALUnitTest_AddFunction("Mt_CddTle94x1_GetPWM", Mt_CddTle94x1_GetPWM);
  //ALUnitTest_AddFunction("Mt_CddTle94x1_GetWakeUpStatus", Mt_CddTle94x1_GetWakeUpStatus);
  ALUnitTest_AddFunction("Mt_CddTle94x1_SetSleepMode", Mt_CddTle94x1_SetSleepMode);
  ALUnitTest_AddFunction("Mt_CddTle94x1_ReadReg", Mt_CddTle94x1_ReadReg);
  ALUnitTest_AddFunction("Mt_CddTle94x1_WriteClearReg", Mt_CddTle94x1_WriteClearReg);
  ALUnitTest_AddFunction("Mt_CddTle94x1_WriteClearReg2", Mt_CddTle94x1_WriteClearReg2);
  ALUnitTest_AddFunction("Mt_CddSbc_ScheduleTableFull", Mt_CddSbc_ScheduleTableFull);
  ALUnitTest_AddFunction("Mt_CddSbc_InsertNewSchedEntry", Mt_CddSbc_InsertNewSchedEntry);
  ALUnitTest_AddFunction("Mt_CddSbc_InsertDefaultMessage", Mt_CddSbc_InsertDefaultMessage);
  ALUnitTest_AddFunction("Mt_CddTle94x1_CbkGetSupState0", Mt_CddTle94x1_CbkGetSupState0);
  //ALUnitTest_AddFunction("Mt_CddTle94x1_CbkGetWakeUpStatus", Mt_CddTle94x1_CbkGetWakeUpStatus);
  ALUnitTest_AddFunction("Mt_CddTle94x1_CbkSetCanMode", Mt_CddTle94x1_CbkSetCanMode);
  ALUnitTest_AddFunction("Mt_CddTle94x1_CbkGetCanMode", Mt_CddTle94x1_CbkGetCanMode);
  ALUnitTest_AddFunction("Mt_CddTle94x1_CbkGetBusState", Mt_CddTle94x1_CbkGetBusState);
  ALUnitTest_AddFunction("Mt_CddTle94x1_SpiTx", Mt_CddTle94x1_SpiTx);
  ALUnitTest_AddFunction("Mt_CddTle94x1_SpiRx", Mt_CddTle94x1_SpiRx);
  ALUnitTest_AddFunction("Mt_CddTle94x1_SpiRx_2", Mt_CddTle94x1_SpiRx_2);
  ALUnitTest_AddFunction("Mt_CddSbc_SpiQueue_Init", Mt_CddSbc_SpiQueue_Init);
  ALUnitTest_AddFunction("Mt_CddSbc_SpiQueue_FirstTx", Mt_CddSbc_SpiQueue_FirstTx);
  ALUnitTest_AddFunction("Mt_CddTle94x1_ErrorSequenceCounterInc", Mt_CddTle94x1_ErrorSequenceCounterInc);
  ALUnitTest_AddFunction("Mt_CddTle94x1_ErrorSequenceCounterClear", Mt_CddTle94x1_ErrorSequenceCounterClear);
  ALUnitTest_AddFunction("Mt_CddTle94x1_StoreResetReason", Mt_CddTle94x1_StoreResetReason);
//  ALUnitTest_AddFunction("Mt_CddTle94x1_GetResetReason", Mt_CddTle94x1_GetResetReason);
  ALUnitTest_AddFunction("Mt_CddTle94x1_DeInit", Mt_CddTle94x1_DeInit);
  ALUnitTest_AddFunction("Mt_CddTle94x1_SetWdgWithSingleOperation", Mt_CddTle94x1_SetWdgWithSingleOperation);
  ALUnitTest_AddFunction("Mt_CddTle94x1_SetWdgWindowModeAnd10ms", Mt_CddTle94x1_SetWdgWindowModeAnd10ms);
  ALUnitTest_AddFunction("Mt_CddTle94x1_SetWdgWindowModeAnd200ms", Mt_CddTle94x1_SetWdgWindowModeAnd200ms);
  ALUnitTest_AddFunction("Mt_CddTle94x1_SetWdgTimeoutModeAnd200ms", Mt_CddTle94x1_SetWdgTimeoutModeAnd200ms);
  ALUnitTest_AddFunction("Mt_CddTle94x1_GetWatchdogFlag", Mt_CddTle94x1_GetWatchdogFlag);
  ALUnitTest_AddFunction("Mt_CddTle94x1_CbkSetWDCtrl", Mt_CddTle94x1_CbkSetWDCtrl);
  ALUnitTest_AddFunction("Mt_CddTle94x1_GetSBCResetReason", Mt_CddTle94x1_GetSBCResetReason);
  ALUnitTest_AddFunction("Mt_CddTle94x1_SetPWM", Mt_CddTle94x1_SetPWM);
  ALUnitTest_AddFunction("Mt_CddTle94x1_CbkSetPWM", Mt_CddTle94x1_CbkSetPWM);
#if (CDDSBC_CFG_VCC2_OPERATION == STD_ON)
  ALUnitTest_AddFunction("Mt_CddTle94x1_SetVCC2", Mt_CddTle94x1_SetVCC2);
  ALUnitTest_AddFunction("Mt_CddTle94x1_CbkSetVCC2", Mt_CddTle94x1_CbkSetVCC2);
  ALUnitTest_AddFunction("Mt_CddTle94x1_Short_To_VBAT", Mt_CddTle94x1_Short_To_VBAT);
  ALUnitTest_AddFunction("Mt_CddTle94x1_Reset_Short_To_VBAT", Mt_CddTle94x1_Reset_Short_To_VBAT);
  ALUnitTest_AddFunction("Mt_CddTle94x1_Short_To_GND", Mt_CddTle94x1_Short_To_GND);
  ALUnitTest_AddFunction("Mt_CddTle94x1_Reset_Short_To_GND", Mt_CddTle94x1_Reset_Short_To_GND);
  ALUnitTest_AddFunction("Mt_CddTle94x1_CbkReadThermStatReg", Mt_CddTle94x1_CbkReadThermStatReg);
  ALUnitTest_AddFunction("Mt_CddTle94x1_Thermal_Shutdown", Mt_CddTle94x1_Thermal_Shutdown);
#endif //(CDDSBC_CFG_VCC2_OPERATION == STD_ON)
}


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
/// \brief  Unit Test Cases for software component module CddBooster
///
/// \author
///         mailTo:
//-----------------------------------------------------------------------------
#include <ALUnitTest_UserInterface.h>

// Stub headers
#include "Test_Stubs.h"
#include "Test_Ext.h"
// Headers of the unit test Module
#include "Test.h"

//=============================================================================
// Helper functions
//=============================================================================
static void MakeCopyOfInitializedStatics(void)
{
  // make backup of initialized structs (at start of 1st test)
  memcpy(&Test_DataMirror_Back,    &CddNcv78702_DataMirror,     sizeof(CddNcv78702_DataMirror));
  memcpy(&Test_SpiSchedTable_Back, &aCddNcv78702_SpiSchedTable, sizeof(aCddNcv78702_SpiSchedTable));
}


static void InitConditions(void)
{
  // initialize stub functions before executing test step
  RestoreStubContents();

  // initialize static RAM before executing test step
  CddNcv78702_unSchedIx = 0u;
  CddNcv78702_aunDummy  = 0u; 
  CddNcv78702_aunZero   = 0u;

  // restore from backup
  memcpy(&CddNcv78702_DataMirror,     &Test_DataMirror_Back,    sizeof(CddNcv78702_DataMirror));
  memcpy(&aCddNcv78702_SpiSchedTable, &Test_SpiSchedTable_Back, sizeof(aCddNcv78702_SpiSchedTable));
}


//=============================================================================
// Test Cases
//=============================================================================

//CddNcv78702.c

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddNcv78702_Init
///
/// \FuSa Relevant: ASIL-B
///
/// \Test Case Description
///    - Test subject:
///        Control the Boost GPIO pins
///
///    - Test Design Technique: - Requirement based test
///                             - ET (Exploratory Testing)
///
///  \Steps:
///         Step 1 : Set EFT data as invalid and check that booster is not enabled
///         Step 2 : Set EFT data as valid
///         Step 3 : Set Booster driver Cfg as Not Configured in EFT data
///         Step 4 : Check that booster is not enabled
///         Step 5 : Set EFT data as valid 
///         Step 6 : Set Booster Cfg as Dual Booster usage in EFT data
///         Step 7 : Check that booster is enabled
///
///    - Preconditions: none
///
///    - Expected test results:
///        - Boost GPIO pins are enabled for EFT valid, disabled for EFT invalid
///
//-----------------------------------------------------------------------------
void Mt_CddNcv78702_Init(void)
{
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Test_SetEftDataValid(FALSE);

  //Step 3) Call the FUT
  CddNcv78702_Init();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(Test_GetBoosterEn(), FALSE, == );

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Test_SetEftDataValid(TRUE);
  Test_Eft_EcuVarCfg()[0u].ucBoostCfg = CDDNCV78702_EFT_BoosterNone;

  //Step 3) Call the FUT
  CddNcv78702_Init();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(Test_GetBoosterEn(), FALSE, == );

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Test_Eft_EcuVarCfg()[0u].ucBoostCfg = CDDNCV78702_EFT_BoosterDual;

  //Step 3) Call the FUT
  CddNcv78702_Init();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(Test_GetBoosterEn(), TRUE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddNcv78702_Shutdown
///
/// \FuSa Relevant: ASIL-B
///
/// \Test Case Description
///    - Test subject:
///       Disable BOOST GPIO pins and set booster to sleep
///
///    - Test Design Technique: - Requirement based test
///                             - ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results:
///        - Booster is set to sleep mode  (PWM = 0u, Booster status disabled)
///
//-----------------------------------------------------------------------------
void Mt_CddNcv78702_Shutdown(void)
{
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  //Step 3) Call the FUT
  CddNcv78702_Shutdown();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(Test_GetBoosterPwmEn(), FALSE, == );
  AL_UNITTEST_CHECK(Test_GetBoosterEn(),    FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddNcv78702_SetBoostEnableGpio
///
/// \FuSa Relevant: ASIL-B
///
/// \Test Case Description
///    - Test subject:
///        Control GPIO pins of BOOST
///
///    - Test Design Technique:   Requirement based test
///                               DT (Decision Table)
///
///  \Steps:
///         Step 1 : Set Command to enable BOOST pin
///         Step 2 : Check that BOOST pin is controlled to HIGH
///         Step 3 : Set Command to disable BOOST pin
///         Step 4 : Check that BOOST pin is controlled to LOW
///
///    - Preconditions: none
///
///    - Expected test results:
///        -  Control GPIO pins of BOOST
///
//-----------------------------------------------------------------------------
void Mt_CddNcv78702_SetBoostEnableGpio(void)
{

  struct { boolean boEnableGPIO;          boolean boBoostEnDis; } asTestCaseData[]
    = { {                 TRUE ,                          TRUE  },    // enable boster GPIO pin
        {                FALSE ,                          FALSE }, }; // disable boster GPIO pin


  for (uint32 ulIdx = 0; ulIdx < _countof(asTestCaseData); ulIdx++)
  {
    //Step 1) Set pre - conditions
    InitConditions();  // default initialization

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    CddNcv78702_SetBoostEnableGpio_Param1 = asTestCaseData[ulIdx].boEnableGPIO;

    //Step 3) Call the FUT
    CddNcv78702_SetBoostEnableGpio(CddNcv78702_SetBoostEnableGpio_Param1);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(Test_GetBoosterEn(), asTestCaseData[ulIdx].boBoostEnDis, == );
  }
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddNcv78702_SetBoostBstSyncDuty
///
/// \FuSa Relevant: ASIL-B
///
/// \Test Case Description
///    - Test subject:
///        Control the duty cycle
///
///    - Test Design Technique:   Requirement based test
///                               DT (Decision Table)
///
///  \Steps:
///         Step 1 : Set Duty Cycle to turn ON booster
///         Step 2 : Check that setting Booster PWM is enabled
///         Step 3 : Set Duty Cycle to turn OFF booster
///         Step 4 : Check that setting Booster PWM is disabled
///
///    - Preconditions: none
///
///    - Expected test results:
///        - Control of BSTSYNC signal
///
//-----------------------------------------------------------------------------
void Mt_CddNcv78702_SetBoostBstSyncDuty(void)
{

  struct { uint16 unBstSyncDuty;          boolean boBoostEnDisPwm; } asTestCaseData[]
     = { {             0x4000u ,                             TRUE  },    // enable boster  BSTSYNC signal
         {             0x0000u ,                            FALSE  }, }; // disable boster  BSTSYNC signal


  for (uint32 ulIdx = 0; ulIdx < _countof(asTestCaseData); ulIdx++)
  {
    //Step 1) Set pre - conditions
    InitConditions();  // default initialization

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    CddNcv78702_SetBoostBstSyncDuty_Param1 = asTestCaseData[ulIdx].unBstSyncDuty;

    //Step 3) Call the FUT
    CddNcv78702_SetBoostBstSyncDuty(CddNcv78702_SetBoostBstSyncDuty_Param1);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(Test_GetBoosterPwmEn(), asTestCaseData[ulIdx].boBoostEnDisPwm, == );
  }
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddNcv78702_SetBoosterVoltage
///
/// \FuSa Relevant: ASIL-B
///
/// \Test Case Description
///    - Test subject:
///        Control the booster voltage
///
///    - Test Design Technique:   Requirement based test
///                               DT (Decision Table)
///
///  \Steps:
///         Step 1 : Set Booster target Duty Cycle to turn ON booster
///         Step 2 : Set Boost offset voltage value if not calibrated
///         Step 3 : Set Boost voltage adjustment factor value if not calibrated
///         Step 4 : Set EFT data validity
///         Step 5 : Check that boost voltage setpoint are calculated based on the 
///                  inputs from previous steps(1-4)
///
///    - Preconditions: none
///
///    - Expected test results:
///        - Set a new value for boost voltage setpoint (CddNcv78702_DataMirror.CtrlTx.Reg0x04.Bit.biBOOST_VSETPOINT)
///
//-----------------------------------------------------------------------------
void Mt_CddNcv78702_SetBoosterVoltage(void)
{
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  typedef struct tsTestCaseDataInput
  {
    uint16   unVBoostTarget_mV;
    sint16   snCalibBoostVoffset;
    uint16   unCalibBoostVfactor;
    boolean  boEftDataValid;
  }tsTestCaseDataInput;

  typedef struct tsTestCaseDataOutput
  {
    uint8   ucBoostVsetpoint;
  }tsTestCaseDataOutput;

  typedef struct tsTestCaseData
  {
    tsTestCaseDataInput  sInputData;
    tsTestCaseDataOutput sOutputData;
  }tsTestCaseData;

  tsTestCaseData asTestCaseData[] =
  {
    //           Inputs                                                          ||       Outputs
    //     VBoostTarget,        Voffset,       Vfactor     boEftDataValid        ||       Vsetpoint
    {  {    0x4000,             0x0100u,       0xFFFFu ,      TRUE   }            ,      { 0x53u   } },
    {  {    0xC350, /*50000*/   0x1000u,       0x0100u ,      TRUE   }            ,      { 0x70u   } },
    {  {    0xC350, /*50000*/   0x1000u,       0x0000u ,      FALSE  }            ,      { 0x00u   } },

  };

  for (uint8 ucIdx = 0; ucIdx < sizeof(asTestCaseData) / sizeof(asTestCaseData[0]); ucIdx++)
  {
    //Step 1: Set pre-conditions
    CddNcv78702_SetBoosterVoltage_Param1                        = 0u;
    CddNcv78702_DataMirror.CtrlTx.Reg0x04.Bit.biBOOST_VSETPOINT = 0u;
    Test_SetEftDataValid(asTestCaseData[ucIdx].sInputData.boEftDataValid);

    //Step 2) Assign Input values
    CddNcv78702_SetBoosterVoltage_Param2  = asTestCaseData[ucIdx].sInputData.unVBoostTarget_mV;
    Test_Eft_Calib()[0].nVOffset          = asTestCaseData[ucIdx].sInputData.snCalibBoostVoffset;
    Test_Eft_Calib()[0].unVFactor         = asTestCaseData[ucIdx].sInputData.unCalibBoostVfactor;
    Test_Eft_EcuVarCfg()[0].nVOffset      = asTestCaseData[ucIdx].sInputData.snCalibBoostVoffset / 2;
    Test_Eft_EcuVarCfg()[0].unVFactor     = asTestCaseData[ucIdx].sInputData.unCalibBoostVfactor / 2u;

    //Step 3) Call FUT
    CddNcv78702_SetBoosterVoltage(CddNcv78702_SetBoosterVoltage_Param1, CddNcv78702_SetBoosterVoltage_Param2);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CddNcv78702_DataMirror.CtrlTx.Reg0x04.Bit.biBOOST_VSETPOINT, asTestCaseData[ucIdx].sOutputData.ucBoostVsetpoint, == );

  }
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddNcv78702_IsSpiError
///
/// \Test Case Description
///    - Test subject:
///      Check if SPI error is reported
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results:
///        - Reutrn value is SPI error indication
///
//-----------------------------------------------------------------------------
void Mt_CddNcv78702_IsSpiError(void)
{
  boolean boRet;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddNcv78702_boSpiValid_Reg0x0A = FALSE;

  //Step 3) Call the FUT
  boRet = CddNcv78702_IsSpiError(0u);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(boRet, TRUE, == );

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddNcv78702_boSpiValid_Reg0x0A = TRUE;

  //Step 3) Call the FUT
  boRet = CddNcv78702_IsSpiError(0u);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(boRet, FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddNcv78702_IsThermalShutDown
///
/// \Test Case Description
///    - Test subject:
///      Check if thermal shutdown is reported
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results:
///        - Reutrn value is TSD error indication
///
//-----------------------------------------------------------------------------
void Mt_CddNcv78702_IsThermalShutDown(void)
{
  boolean boRet;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddNcv78702_DataMirror.StatRx.Reg0x0A.unRaw     = 0u;
  CddNcv78702_DataMirror.StatRx.Reg0x0A.Bit.biTSD = 0u;
  CddNcv78702_boSpiValid_Reg0x0A                  = FALSE;

  //Step 3) Call the FUT
  boRet = CddNcv78702_IsThermalShutDown(0u);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(boRet, FALSE, == );

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddNcv78702_DataMirror.StatRx.Reg0x0A.unRaw     = 0u;
  CddNcv78702_DataMirror.StatRx.Reg0x0A.Bit.biTSD = 1u;
  CddNcv78702_boSpiValid_Reg0x0A                  = TRUE;

  //Step 3) Call the FUT
  boRet = CddNcv78702_IsThermalShutDown(0u);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(boRet, TRUE, == );

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddNcv78702_DataMirror.StatRx.Reg0x0A.Bit.biTSD = 0u;

  //Step 3) Call the FUT
  boRet = CddNcv78702_IsThermalShutDown(0u);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(boRet, FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddNcv78702_IsThermalWarning
///
/// \Test Case Description
///    - Test subject:
///      Check if thermal warning is reported
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results:
///        - Reutrn value is TW error indication
///
//-----------------------------------------------------------------------------
void Mt_CddNcv78702_IsThermalWarning(void)
{
  boolean boRet;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddNcv78702_DataMirror.StatRx.Reg0x0A.unRaw    = 0u;
  CddNcv78702_DataMirror.StatRx.Reg0x0A.Bit.biTW = 0u;
  CddNcv78702_boSpiValid_Reg0x0A                 = FALSE;

  //Step 3) Call the FUT
  boRet = CddNcv78702_IsThermalWarning(0u);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(boRet, FALSE, == );

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddNcv78702_DataMirror.StatRx.Reg0x0A.unRaw    = 0u;
  CddNcv78702_DataMirror.StatRx.Reg0x0A.Bit.biTW = 1u;
  CddNcv78702_boSpiValid_Reg0x0A                 = TRUE;

  //Step 3) Call the FUT
  boRet = CddNcv78702_IsThermalWarning(0u);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(boRet, TRUE, == );

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddNcv78702_DataMirror.StatRx.Reg0x0A.Bit.biTW = 0u;

  //Step 3) Call the FUT
  boRet = CddNcv78702_IsThermalWarning(0u);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(boRet, FALSE, == );
}


//CddNcv78702_Com.c
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddNcv78702_SetBoostVsetpoint
///
/// \Test Case Description
///    - Test subject:
///      Set booster voltage setpoint
///
///    - Test Design Technique: DT (Decision Table)
///
///    - Preconditions: none
///
///    - Expected test results:
///        - Received booster voltage via SPI is set
///
//-----------------------------------------------------------------------------
void Mt_CddNcv78702_SetBoostVsetpoint(void)
{
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization
  CddNcv78702_DataMirror.CtrlTx.Reg0x04.Bit.biBOOST_VSETPOINT = 0u;

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddNcv78702_SetBoostVsetpoint_Param1 = CDDNCV78702_Cfg_BOOST_VSETPOINT_Max;

  //Step 3) Call the FUT
  CddNcv78702_SetBoostVsetpoint(CddNcv78702_SetBoostVsetpoint_Param1);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(CddNcv78702_DataMirror.CtrlTx.Reg0x04.Bit.biBOOST_VSETPOINT, CDDNCV78702_Cfg_BOOST_VSETPOINT_Max, ==);
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddNcv78702_CalculateAndAddOddParityBit
///
/// \Test Case Description
///    - Test subject:
///      Calculate the perity bit over the SPI command frame
///
///    - Test Design Technique: DT (Decision Table)
///
///    - Preconditions: none
///
///    - Expected test results:
///        - The SPI command frame (cmd, addr, data concatenated and parity bit added)
///
//-----------------------------------------------------------------------------
void Mt_CddNcv78702_CalculateAndAddOddParityBit(void)
{

  typedef struct tsTestCaseDataInput
  {
    uint16 unCmd;
    uint16 unAddr;
    uint16 unData;
  }tsTestCaseDataInput;

  typedef struct tsTestCaseDataOutput
  {
    uint16 unSPITxFrame;
  }tsTestCaseDataOutput;

  typedef struct tsTestCaseData
  {
    tsTestCaseDataInput  sInputData;
    tsTestCaseDataOutput sOutputData;
  }tsTestCaseData;

  tsTestCaseData asTestCaseData[] =
  {
    //           Inputs                                                     || Outputs
    //    Command                 Register Address              Data        || SpiTx Frame (with parity)
    {  {  CDDNCV78702_ReadCmd,    CDDNCV78702_ReadReg0x02Addr,  0u   }      ,  {  0x800u   } },
    {  {  CDDNCV78702_ReadCmd,    CDDNCV78702_ReadReg0x05Addr,  0u   }      ,  {  0x1600   } },
    {  {  CDDNCV78702_WriteCmd,   CDDNCV78702_WriteReg0x04Addr, 0u   }      ,  {  0xA400   } },

  };

  for (uint8 ucIdx = 0; ucIdx < sizeof(asTestCaseData) / sizeof(asTestCaseData[0]); ucIdx++)
  {
    //Step 1: Set pre-conditions
    CddNcv78702_CalculateAndAddOddParityBit_RetVal = 0u;

    //Step 2) Assign Input values
    CddNcv78702_CalculateAndAddOddParityBit_Param1 = asTestCaseData[ucIdx].sInputData.unCmd;
    CddNcv78702_CalculateAndAddOddParityBit_Param2 = asTestCaseData[ucIdx].sInputData.unAddr;
    CddNcv78702_CalculateAndAddOddParityBit_Param3 = asTestCaseData[ucIdx].sInputData.unData;
      
    //Step 3) Call FUT
    CddNcv78702_CalculateAndAddOddParityBit_RetVal = CddNcv78702_CalculateAndAddOddParityBit(CddNcv78702_CalculateAndAddOddParityBit_Param1, CddNcv78702_CalculateAndAddOddParityBit_Param2, CddNcv78702_CalculateAndAddOddParityBit_Param3);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CddNcv78702_CalculateAndAddOddParityBit_RetVal, asTestCaseData[ucIdx].sOutputData.unSPITxFrame, == );

  }
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddNcv78702_StAction
///
/// \Test Case Description
///    - Test subject:
///      Test the schedule table action
///
///    - Test Design Technique: DT (Decision Table)
///
///    - Preconditions: none
///
///    - Expected test results:
///        - Action is executed based on the scheduler
///
//-----------------------------------------------------------------------------
void Mt_CddNcv78702_StAction(void)
{
  struct { uint8 ucAction;          uint32 ucBoostCfg; boolean
                                                       boEftValid; uint16
                                                                   unReg0x0A; uint16
                                                                              unCnt; boolean 
                                                                                     boEnDis; boolean
                                                                                              boDuty; uint8 ucEn1; uint8 ucEn2; boolean boRet; } asTestCaseData[]
    = {  { CDDNCV78702_ST_ACT_DIS_BOOST,     255u,     TRUE,       0x0100,    5u,    FALSE,   FALSE,       0u,          0u,          FALSE     },  // disable boster
         { CDDNCV78702_ST_ACT_BSTSYNC_50,      2u,     TRUE,       0x0100,    5u,    FALSE,   TRUE,        1u,          1u,          FALSE     },  // dual booster
         { CDDNCV78702_ST_ACT_BSTSYNC_50,      1u,     TRUE,       0x0100,    5u,    FALSE,   TRUE,        1u,          0u,          FALSE     },  // single booster
         { CDDNCV78702_ST_ACT_BSTSYNC_50,    255u,     TRUE,       0x0100,    5u,    FALSE,   TRUE,        0u,          0u,          FALSE     },  // other config
         { CDDNCV78702_ST_ACT_EN_BOOST,      255u,     TRUE,       0x0100,    5u,    TRUE,    FALSE,       0u,          0u,          FALSE     },  // enable booster
         { CDDNCV78702_ST_CHECK_START,       255u,     TRUE,       0x0100,    5u,    FALSE,   FALSE,       0u,          0u,          FALSE     },  // check EFT data for startup
         { CDDNCV78702_ST_CHECK_START,       255u,     FALSE,      0x0100,    5u,    FALSE,   FALSE,       0u,          0u,          TRUE      },  // check EFT data for startup
         { CDDNCV78702_ST_CHECK_STATUS,        1u,     TRUE,       0x0100,    5u,    FALSE,   FALSE,       0u,          0u,          FALSE     },  // evaluate status (1 booster configured)
         { CDDNCV78702_ST_CHECK_STATUS,        2u,     TRUE,       0x0100,    5u,    FALSE,   FALSE,       0u,          0u,          FALSE     },  // evaluate status (2 booster configured)
         { CDDNCV78702_ST_CHECK_STATUS,        2u,     TRUE,       0x0020,    5u,    FALSE,   FALSE,       0u,          0u,          FALSE     },  // evaluate status (booster 1 working)
         { CDDNCV78702_ST_CHECK_STATUS,        2u,     TRUE,       0x0040,    5u,    FALSE,   FALSE,       0u,          0u,          FALSE     },  // evaluate status (booster 2 working)
         { CDDNCV78702_ST_CHECK_STATUS,        2u,     TRUE,       0x0160,    5u,    FALSE,   FALSE,       0u,          0u,          FALSE     },  // evaluate status (restart condition)
         { CDDNCV78702_ST_CHECK_STATUS,        2u,     TRUE,       0x0340,    5u,    FALSE,   FALSE,       0u,          0u,          FALSE     },  // evaluate status (HWR, not validated)
         { CDDNCV78702_ST_CHECK_STATUS,        2u,     TRUE,       0x0340,    0u,    FALSE,   FALSE,       0u,          0u,          TRUE      },  // evaluate status (HWR, validated)
         {            255u,                  255u,     TRUE,       0x0100,    5u,    FALSE,   FALSE,       0u,          0u,          FALSE     }, }; //invalid action

  for (uint32 ulIdx = 0; ulIdx < _countof(asTestCaseData); ulIdx++)
  {
    //Step 1) Set pre - conditions
    InitConditions();  // default initialization
    CddNcv78702_DataMirror.CtrlTx.Reg0x05.Bit.biBOOST1_EN = 0u;
    CddNcv78702_DataMirror.CtrlTx.Reg0x05.Bit.biBOOST2_EN = 0u;
    CddNcv78702_StAction_RetVal                           = TRUE;

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    CddNcv78702_StAction_Param1                           = asTestCaseData[ulIdx].ucAction;
    Test_Eft_EcuVarCfg()[0u].ucBoostCfg                   = asTestCaseData[ulIdx].ucBoostCfg; 
    Test_SetEftDataValid                                   (asTestCaseData[ulIdx].boEftValid);
    CddNcv78702_DataMirror.StatRx.Reg0x0A.unRaw           = asTestCaseData[ulIdx].unReg0x0A;
    CddLed78702_unRestartCnt                              = asTestCaseData[ulIdx].unCnt;

    //Step 3) Call the FUT
    CddNcv78702_StAction_RetVal = CddNcv78702_StAction(CddNcv78702_StAction_Param1);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(CddNcv78702_DataMirror.CtrlTx.Reg0x05.Bit.biBOOST1_EN, asTestCaseData[ulIdx].ucEn1,    == );
    AL_UNITTEST_CHECK(CddNcv78702_DataMirror.CtrlTx.Reg0x05.Bit.biBOOST2_EN, asTestCaseData[ulIdx].ucEn2,    == );
    AL_UNITTEST_CHECK(Test_GetBoosterEn(),                                    asTestCaseData[ulIdx].boEnDis, == );
    AL_UNITTEST_CHECK(Test_GetBoosterPwmEn(),                                 asTestCaseData[ulIdx].boDuty,  == );
    AL_UNITTEST_CHECK(CddNcv78702_StAction_RetVal,                            asTestCaseData[ulIdx].boRet,   == );
  }
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddNcv78702_SpiTx
///
/// \FuSa Relevant: ASIL-B
///
/// \Test Case Description
///    - Test subject:
///      Read the content of CddNcv78702_DataMirror for a given state
///
///    - Test Design Technique:   Requirement based test
///                               DT (Decision Table)
///
///    - Preconditions: none
///
///    - Expected test results:
///        - Obtain the Spi Tx frame : CddNcv78702_SpiTx_RetVal = 0xB000
///
//-----------------------------------------------------------------------------
void Mt_CddNcv78702_SpiTx(void)
{
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddNcv78702_SpiTx_Param1  = 0u;
  CddNcv78702_unSchedIx     = 3u;    //CDDNCV78702_ST_CHECK_START -> switch to state 4 CDDNCV78702_ST_ACT_DIS_BOOST
  CddNcv78702_SpiTx_RetVal  = 0u;
  CddNcv78702_DataMirror.CtrlTx.Reg0x06.unRaw = 0x00;

  //Step 3) Call the FUT
  CddNcv78702_SpiTx_RetVal = CddNcv78702_SpiTx(CddNcv78702_SpiTx_Param1);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(CddNcv78702_SpiTx_RetVal,   0xB000, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddNcv78702_SpiRx
///
/// \FuSa Relevant: ASIL-B
///
/// \Test Case Description
///    - Test subject:
///      Read the content of SPI RX
///
///    - Test Design Technique:   Requirement based test
///                               DT (Decision Table)
///
///    - Preconditions: none
///
///      - DT-Info:
///         - Inputs:
///            unSchedIx_Rx :  known value of Rx index of schedular table
///            ulSpiData_Rx :  known value of RX data from current index
///         - Expected results
///           - Save the data in CddNcv78702_DataMirror
///            unSchedIx_Rx_Next : expected RX index for next scheduler entry
///            unSchedIx_Tx_Next : expected TX index for next scheduler entry
///

//-----------------------------------------------------------------------------
void Mt_CddNcv78702_SpiRx(void)
{

  typedef struct tsTestCaseDataInput
  {
    uint16 unSchedIx_Rx;
    uint32 ulSpiData_Rx;
  }tsTestCaseDataInput;

  typedef struct tsTestCaseDataOutput
  {
    uint16 unSchedIx_Rx_Next;
    uint16 unSchedIx_Tx_Next;
  }tsTestCaseDataOutput;

  typedef struct tsTestCaseData
  {
    tsTestCaseDataInput  sInputData;
    tsTestCaseDataOutput sOutputData;
  }tsTestCaseData;

  tsTestCaseData asTestCaseData[] =
  {
    //   Inputs                        || Outputs
    // unSchedIx_Rx ,  SpiData_Rx      || Rx_Next        ,  Tx_Next
    {  {  0u        ,   0x800u  }       ,  {  1u       ,      1u    } },           /*    CDDNCV78702_ST_NO_ACT,                                          */
    {  {  1u        ,   0x800u  }       ,  {  2u       ,      2u    } },           /*    CDDNCV78702_ST_NO_ACT,                                          */
    {  {  2u        ,   0x800u  }       ,  {  3u       ,      3u    } },           /*    CDDNCV78702_ST_NO_ACT,                                          */
    {  {  3u        ,   0x800u  }       ,  {  4u       ,      4u    } },           /*    CDDNCV78702_ST_CHECK_START,    ->   Rx_Next = Tx_Next = 0u      */
    {  {  4u        ,   0x800u  }       ,  {  5u       ,      5u    } },           /*    CDDNCV78702_ST_ACT_DIS_BOOST,  ->   Rx_Next = Tx_Next = 0u      */
    {  {  5u        ,   0x800u  }       ,  {  6u       ,      6u    } },           /*    CDDNCV78702_ST_NO_ACT,                                          */
    {  {  6u        ,   0x800u  }       ,  {  7u       ,      7u    } },           /*    CDDNCV78702_ST_NO_ACT,                                          */
    {  {  7u        ,   0x800u  }       ,  {  8u       ,      8u    } },           /*    CDDNCV78702_ST_NO_ACT,                                          */
    {  {  8u        ,   0x800u  }       ,  {  9u       ,      9u    } },           /*    CDDNCV78702_ST_NO_ACT,                                          */
    {  {  9u        ,   0x800u  }       ,  {  10u      ,      10u   } },           /*    CDDNCV78702_ST_NO_ACT,                                          */
    {  {  10u       ,   0x800u  }       ,  {  11u      ,      11u   } },           /*    CDDNCV78702_ST_NO_ACT,                                          */
    {  {  11u       ,   0x800u  }       ,  {  12u      ,      12u   } },           /*    CDDNCV78702_ST_NO_ACT,                                          */
    {  {  12u       ,   0x800u  }       ,  {  13u      ,      13u   } },           /*    CDDNCV78702_ST_ACT_BSTSYNC_50,  ->   Rx_Next = Tx_Next = 0u     */
    {  {  13u       ,   0x800u  }       ,  {  14u      ,      14u   } },           /*    CDDNCV78702_ST_ACT_EN_BOOST,    ->   Rx_Next = Tx_Next = 0u     */
    /*------------Cyclic 0ms---------------------------*/             /*                                                                    */
    {  {  14u       ,   0x800u  }       ,  {  15u      ,      15u   } },            /*    CDDNCV78702_ST_NO_ACT,                                          */
    {  {  15u       ,   0x800u  }       ,  {  16u      ,      16u   } },           /*    CDDNCV78702_ST_NO_ACT,                                          */
    {  {  16u       ,   0x800u  }       ,  {  17u      ,      17u   } },           /*    CDDNCV78702_ST_NO_ACT,                                          */
    {  {  17u       ,   0x800u  }       ,  {  18u      ,      18u   } },           /*    CDDNCV78702_ST_NO_ACT,                                          */
    {  {  18u       ,   0x800u  }       ,  {  19u      ,      19u   } },           /*    CDDNCV78702_ST_NO_ACT,                                          */
    {  {  19u       ,   0x800u  }       ,  {  20u      ,      20u   } },           /*    CDDNCV78702_ST_NO_ACT,                                          */
    {  {  20u       ,   0x800u  }       ,  {  21u      ,      21u   } },           /*    CDDNCV78702_ST_NO_ACT,                                          */
    {  {  21u       ,   0x800u  }       ,  {  22u      ,      22u   } },           /*    CDDNCV78702_ST_NO_ACT,                                          */
    {  {  22u       ,   0x800u  }       ,  {  23u      ,      23u   } },           /*    CDDNCV78702_ST_NO_ACT,                                          */
    {  {  23u       ,   0x800u  }       ,  {  24u      ,      24u   } },           /*    CDDNCV78702_ST_NO_ACT,                                          */
    /*-------------Cyclic 10ms---------------------------*/           /*                                                                    */
    {  { 24u        ,   0x800u  }       ,  { 25u      ,      25u   } },            /*    CDDNCV78702_ST_NO_ACT,                                          */
    {  { 25u        ,   0x800u  }       ,  { 26u      ,      26u   } },            /*    CDDNCV78702_ST_NO_ACT,                                          */
    {  { 26u        ,   0x800u  }       ,  { 27u      ,      27u   } },            /*    CDDNCV78702_ST_NO_ACT,                                          */
    {  { 27u        ,   0x800u  }       ,  { 28u      ,      28u   } },            /*    CDDNCV78702_ST_NO_ACT,                                          */
    {  { 28u        ,   0x800u  }       ,  { 29u      ,      29u   } },            /*    CDDNCV78702_ST_NO_ACT,                                          */
    {  { 29u        ,   0x200u  }       ,  {  0u      ,       0u   } },            /*    CDDNCV78702_ST_NO_ACT,                                          */
    {  { 29u        ,   0x800u  }       ,  { 30u      ,      30u   } },            /*    CDDNCV78702_ST_NO_ACT,                                          */
    {  { 30u        ,   0x800u  }       ,  { 31u      ,      31u   } },            /*    CDDNCV78702_ST_CHECK_STATUS,                                    */
    {  { 31u        ,   0x800u  }       ,  { 32u      ,      32u   } },            /*    CDDNCV78702_ST_NO_ACT,                                          */
    {  { 32u        ,   0x800u  }       ,  { 33u      ,      33u   } },            /*    CDDNCV78702_ST_NO_ACT,                                          */
    {  { 33u        ,   0x800u  }       ,  { 14u      ,      14u   } },            /*    CDDNCV78702_ST_NO_ACT,                                          */
  };

  //Step 1: Set pre-conditions
  InitConditions();  // default initialization
  CddNcv78702_SpiRx_Param1 = 0u;            //doesn't influence????

  for (uint8 ucIdx = 0; ucIdx < sizeof(asTestCaseData) / sizeof(asTestCaseData[0]); ucIdx++)
  {
    uint32 TestIdx;

    //Step 2) Assign Input values
    CddNcv78702_unSchedIx    =  asTestCaseData[ucIdx].sInputData.unSchedIx_Rx;
    CddNcv78702_SpiRx_Param2 =  asTestCaseData[ucIdx].sInputData.ulSpiData_Rx;
    CddLed78702_unRestartCnt = 0u;
    TestIdx = CddNcv78702_unSchedIx;

    //Step 3) Call FUT
    CddNcv78702_SpiRx(CddNcv78702_SpiRx_Param1, CddNcv78702_SpiRx_Param2);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CddNcv78702_unSchedIx, asTestCaseData[ucIdx].sOutputData.unSchedIx_Rx_Next, == );
    AL_UNITTEST_CHECK(CddNcv78702_unSchedIx, asTestCaseData[ucIdx].sOutputData.unSchedIx_Tx_Next, == );
    AL_UNITTEST_CHECK(*aCddNcv78702_SpiSchedTable[TestIdx].punRx, asTestCaseData[ucIdx].sInputData.ulSpiData_Rx, == );
  }
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddNcv78702_SetBoostSleep
///
/// \Test Case Description
///    - Test subject:
///      Disable Booster before SBC sleep
///
///    - Test Design Technique: DT (Decision Table)
///
///    - Preconditions: none
///
///    - Expected test results:
///        - Booster gets disabled  and command is sent via SPI
///
//-----------------------------------------------------------------------------
void Mt_CddNcv78702_SetBoostSleep(void)
{
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  //Step 3) Call the FUT
  CddNcv78702_SetBoostSleep();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(Test_GetTransferMsg(CDDSPI_DEVICE(BOOST)),    0xB000, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddNcv78702_IsReset
///
/// \Test Case Description
///    - Test subject:
///      Check if booster is still in init state
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results:
///        - Return value depends on index
///
//-----------------------------------------------------------------------------
void Mt_CddNcv78702_IsReset(void)
{
  boolean boRet;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddNcv78702_unSchedIx = 13u;

  //Step 3) Call the FUT
  boRet = CddNcv78702_IsReset(0u);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(boRet, TRUE, == );

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddNcv78702_unSchedIx = 14u;

  //Step 3) Call the FUT
  boRet = CddNcv78702_IsReset(0u);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(boRet, FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddNcv78702_GetReg0x0A
///
/// \Test Case Description
///    - Test subject:
///      Check if booster is still in init state
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results:
///        - Return value depends on index
///
//-----------------------------------------------------------------------------
void Mt_CddNcv78702_GetReg0x0A(void)
{
  boolean boRet;
  tCddNcv78702_Reg0x0A Reg0x0A;
  CddNcv78702_DataMirror.StatRx.Reg0x0A.unRaw = 0xAA55;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Reg0x0A.unRaw = 0x55AA;
  CddNcv78702_boSpiValid_Reg0x0A = FALSE;

  //Step 3) Call the FUT
  boRet = CddNcv78702_GetReg0x0A(0u);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(boRet, FALSE, == );
  AL_UNITTEST_CHECK(Reg0x0A.unRaw, 0x55AA, == );

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddNcv78702_boSpiValid_Reg0x0A = TRUE;
  CddNcv78702_DataMirror.StatRx.Reg0x0A.unRaw = 0xAA55;

  //Step 3) Call the FUT
  boRet = CddNcv78702_GetReg0x0A(&Reg0x0A);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(boRet, TRUE, == );
  AL_UNITTEST_CHECK(Reg0x0A.unRaw, 0xAA55, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddNcv78702_SetBoostOverVoltageThr
///
/// \Test Case Description
///    - Test subject:
///      Read EFT booster variant coded and assign the overtreshold voltage
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results:
///        - Return value depends on EFT variant coded
///
//-----------------------------------------------------------------------------
Mt_CddNcv78702_SetBoostOverVoltageThr(void)
{

  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Test_Eft_EcuVarCfg()[0u].ucVariant = 3u;
  CddNcv78702_DataMirror.CtrlTx.Reg0x03.Bit.biBOOST_OVERVOLTSD_THR = CDDNCV78702_Cfg_BOOST_OVERVOLTSD_THR;

  //Step 3) Call the FUT
  CddNcv78702_SetBoostOverVoltageThr();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(CddNcv78702_DataMirror.CtrlTx.Reg0x03.Bit.biBOOST_OVERVOLTSD_THR, CDDNCV78702_Cfg_60V_BOOST_OVERVOLTSD_THR, == );

  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  InitConditions();  // default initialization

  //Step 3) Call the FUT
  CddNcv78702_SetBoostOverVoltageThr();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(CddNcv78702_DataMirror.CtrlTx.Reg0x03.Bit.biBOOST_OVERVOLTSD_THR, CDDNCV78702_Cfg_BOOST_OVERVOLTSD_THR, == );

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
  MakeCopyOfInitializedStatics();   // make backup of initialized structs

  //CddNcv78702.c
  ALUnitTest_AddFunction("Mt_CddNcv78702_Init"                                , Mt_CddNcv78702_Init);
  ALUnitTest_AddFunction("Mt_CddNcv78702_Shutdown"                            , Mt_CddNcv78702_Shutdown);
  ALUnitTest_AddFunction("Mt_CddNcv78702_SetBoostEnableGpio"                  , Mt_CddNcv78702_SetBoostEnableGpio);
  ALUnitTest_AddFunction("Mt_CddNcv78702_SetBoostBstSyncDuty"                 , Mt_CddNcv78702_SetBoostBstSyncDuty);
  ALUnitTest_AddFunction("Mt_CddNcv78702_SetBoosterVoltage"                   , Mt_CddNcv78702_SetBoosterVoltage);
  ALUnitTest_AddFunction("Mt_CddNcv78702_IsSpiError"                          , Mt_CddNcv78702_IsSpiError);
  ALUnitTest_AddFunction("Mt_CddNcv78702_IsThermalShutDown"                   , Mt_CddNcv78702_IsThermalShutDown);
  ALUnitTest_AddFunction("Mt_CddNcv78702_IsThermalWarning"                    , Mt_CddNcv78702_IsThermalWarning);

  //CddNcv78702_Com.c
  ALUnitTest_AddFunction("Mt_CddNcv78702_SetBoostVsetpoint"                   , Mt_CddNcv78702_SetBoostVsetpoint);
  ALUnitTest_AddFunction("Mt_CddNcv78702_IsReset"                             , Mt_CddNcv78702_IsReset);
  ALUnitTest_AddFunction("Mt_CddNcv78702_GetReg0x0A"                          , Mt_CddNcv78702_GetReg0x0A);
  ALUnitTest_AddFunction("Mt_CddNcv78702_CalculateAndAddOddParityBit"         , Mt_CddNcv78702_CalculateAndAddOddParityBit);
  ALUnitTest_AddFunction("Mt_CddNcv78702_StAction"                            , Mt_CddNcv78702_StAction);
  ALUnitTest_AddFunction("Mt_CddNcv78702_SpiTx"                               , Mt_CddNcv78702_SpiTx);
  ALUnitTest_AddFunction("Mt_CddNcv78702_SpiRx"                               , Mt_CddNcv78702_SpiRx);
  ALUnitTest_AddFunction("Mt_CddNcv78702_SetBoostSleep"                       , Mt_CddNcv78702_SetBoostSleep);
  ALUnitTest_AddFunction("Mt_CddNcv78702_SetBoostOverVoltageThr"              , Mt_CddNcv78702_SetBoostOverVoltageThr);

}

//*****************************************************************************
// (C) Marelli Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Marelli Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Marelli Automotive Lighting Reutlingen GmbH.
//*****************************************************************************
//-----------------------------------------------------------------------------
/// \file  Test.c
///
/// \brief  Unit test of generic code in CddTpsGen3 module
///
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
//-----------------------------------------------------------------------------

// Standard unit test header
#include <ALUnitTest_UserInterface.h>

// Stub headers
#include "Test_Ext.h"
#include "Test_Stubs.h"

// Headers of the unit test Module
#include "Test.h"

//-----------------------------------------------------------------------------
// Test implementation
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Initialization of test cases
//-----------------------------------------------------------------------------
static void MakeCopyOfInitializedStatics(void)
{
  // make backup of initialized structs (at start of 1st test)
  memcpy(&Test_DataMirror_Backup,     &CddTpsGen3_DataMirror,       sizeof(tsCddTpsGen3_DataMirror));
  memcpy(&Test_UartSchedTable_Backup, &CddTpsGen3_asUartSchedTable, sizeof(tsCddTpsGen3_UartSchedTable));
}

static void InitConditions(void)
{
  // initialize stub functions before executing test step
  RestoreStubContents();

  // initialize static RAM before executing test step
  CddTpsGen3_ucSchedIx = 0u;
  CddTpsGen3_ucChipIdx = 0u;
  CddTpsGen3_ucChipIdx_MuxCmd  = 0u;
  CddTpsGen3_boMuxCmdCompleted = FALSE;
  CddTpsGen3_boInitCompleted   = FALSE;
  CddTpsGen3_boReinitChips     = FALSE;

  for (uint8 ucIdx = 0u; ucIdx < TEST_Cfg_Chips; ucIdx++)
  {
    CddTpsGen3_ucDummy[ucIdx] = 0u;
    CddTpsGen3_aucZero[ucIdx] = 0u;
  }

  // restore from backup
  memcpy(&CddTpsGen3_DataMirror,        &Test_DataMirror_Backup,      sizeof(tsCddTpsGen3_DataMirror));
  memcpy(&CddTpsGen3_asUartSchedTable,  &Test_UartSchedTable_Backup,  sizeof(tsCddTpsGen3_UartSchedTable));
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTpsGen3_Init
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: 
///        Check that in the init function, data from the coding structure is 
///        extracted correctly and mapped into a chip global structure data  
///        needed for GEN3 devices
///
///    - Test Design Technique: DT (Decision Table)
///
///    - Preconditions: coding parameters available
///
///    - Expected test results: 
///        - coded data is mapped for gen3 devices
///
///      - DT-Info:
///         - Inputs:
///            aucCodDevId              :  coded chip id
///         - Expected results
///            aucMappedPhysicalAddress :  expected value returned  by the FUT, physical address mapped for the coded id
///            aucChipId                :  expected value returned  by the FUT, coded id saved for processing chip index continuosly
///            aboMaster                :  expected value returned  by the FUT, master-slave configuration decoded
///            ucConnectedDevs          :  expected value returned  by the FUT, connected GEN3 (only) devices
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen3_Init(void)
{
  typedef struct tsTestCaseDataInput
  {
    uint8   aucCodDevId[TEST_Cfg_Chips];
  }tsTestCaseDataInput;

  typedef struct tsTestCaseDataOutput
  {
    uint8   aucMappedPhysicalAddress[TEST_Cfg_Chips];
    uint8   aucChipId[TEST_Cfg_Chips];
    boolean aboMaster[TEST_Cfg_Chips];
    uint8   ucConnectedDevs;
  }tsTestCaseDataOutput;

  typedef struct tsTestCaseData
  {
    tsTestCaseDataInput   sDataInput;
    tsTestCaseDataOutput  sDataOutput;
  }tsTestCaseData;

  tsTestCaseData asTestCaseData[] =
  {
    /*             Input Data                   |                                                          Output Data                     */
    /*             CodDevId                     |             MappedPhysicalAddress   ,                                           ChipId    ,                                      Master   ,                     ConnectedDevs      */
    { {TEST_DRV_COD_TYPE_TPSGEN2_UART_ADDRS     }, { {0u, 0u, 0u, 0u, 0u, 0u, 0u},                                   {255u, 255u, 255u, 255u, 255u, 255u, 255u},  { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE},    0u }   },
    { {TEST_DRV_COD_TYPE_TPSGENx_1_UART_ADDRS   }, { {CDDTPSGEN3_DEV_ID11, CDDTPSGEN3_DEV_ID12, 0u, 0u, 0u, 0u, 0u}, {  0u,   2u, 255u, 255u, 255u, 255u, 255u},  { TRUE,  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE},    2u }   },
    { {TEST_DRV_COD_TYPE_TPSGEN3_664_UART_ADDRS }, { {CDDTPSGEN3_DEV_ID11, CDDTPSGEN3_DEV_ID12, 0u, 0u, 0u, 0u, 0u}, {  0u,   6u, 255u, 255u, 255u, 255u, 255u},  { TRUE,  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE},    2u }   },
  };

  for (uint8 ucIdx = 0u; ucIdx < sizeof(asTestCaseData) / sizeof(asTestCaseData[0]); ucIdx++)
  {
    //Step 1) Set pre - conditions
    InitConditions();
    CddTpsGen3_sDevData = (tsCddTpsGen3_DevData){ 0u };  //reset variable

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    Test_Drv_SetCHIP_IDs(asTestCaseData[ucIdx].sDataInput.aucCodDevId);

    //Step 3) Call the FUT
    CddTpsGen3_Init();

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 

    for (uint8 ucChipIdx = 0u; ucChipIdx < TEST_Cfg_Chips; ucChipIdx++)
    {
      AL_UNITTEST_CHECK(CddTpsGen3_sDevData.asMasterSlaveId[ucChipIdx].ucPhysicalAddr,  asTestCaseData[ucIdx].sDataOutput.aucMappedPhysicalAddress[ucChipIdx], == );
      AL_UNITTEST_CHECK(CddTpsGen3_sDevData.asMasterSlaveId[ucChipIdx].boIsMasterId,    asTestCaseData[ucIdx].sDataOutput.aboMaster[ucChipIdx],                == );
      AL_UNITTEST_CHECK(CddTpsGen3_sDevData.aucCodDevID[ucChipIdx],                     asTestCaseData[ucIdx].sDataOutput.aucChipId[ucChipIdx],                == );
    }
    AL_UNITTEST_CHECK(CddTpsGen3_sDevData.ucConnectedDevices, asTestCaseData[ucIdx].sDataOutput.ucConnectedDevs, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTpsGen3_pfGetDevData
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:
///      Check that the function returns the coding structure of GEN3
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: coding parameters read and mapped
///
///    - Expected test results:
///        - function returns correctly the content of the global coding structure of GEN3
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen3_pfGetDevData(void)
{
  //Step 1) Set pre - conditions
  InitConditions();
  tsCddTpsGen3_DevData* psRetDevData;
  uint8   aucMappedAddress[TEST_Cfg_Chips]  = { CDDTPSGEN3_DEV_ID11, CDDTPSGEN3_DEV_ID12, 0u, 0u, 0u, 0u, 0u };
  boolean aboMasterDev[TEST_Cfg_Chips]      = { TRUE,  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  for (uint8 ucChipIdx = 0u; ucChipIdx < TEST_Cfg_Chips; ucChipIdx++)
  {
    CddTpsGen3_sDevData.asMasterSlaveId[ucChipIdx].ucPhysicalAddr = aucMappedAddress[ucChipIdx];
    CddTpsGen3_sDevData.asMasterSlaveId[ucChipIdx].boIsMasterId   = aboMasterDev[ucChipIdx];
  }
  CddTpsGen3_sDevData.ucConnectedDevices = 2u;

  //Step 3) Call the FUT
  psRetDevData = CddTpsGen3_pfGetDevData();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  for (uint8 ucChipIdx = 0u; ucChipIdx < TEST_Cfg_Chips; ucChipIdx++)
  {
    AL_UNITTEST_CHECK(psRetDevData->asMasterSlaveId[ucChipIdx].ucPhysicalAddr, aucMappedAddress[ucChipIdx], == );
    AL_UNITTEST_CHECK(psRetDevData->asMasterSlaveId[ucChipIdx].boIsMasterId,   aboMasterDev[ucChipIdx],     == );
  }
  AL_UNITTEST_CHECK(psRetDevData->ucConnectedDevices, 2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTpsGen3_Cycle
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:
///      Check if empty function is called (coverage only)
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results:
///        - none
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen3_Cycle(void)
{
  //Step 1) Set pre - conditions
  // default initialization
  InitConditions();

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  //Step 3) Call the FUT
  CddTpsGen3_Cycle();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  // none: coverage only
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTpsGen3_SetDutyCycle_1_1024
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:
///        Check correct call of interface function to set PWM target values
///        into witdh registers
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: pwm duty values available
///
///    - Expected test results:
///        - pwm values are correctly computed in the width registers
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen3_SetDutyCycle_1_1024(void)
{
  //Step 1) Set pre - conditions
  InitConditions();
  uint8 aucTestEmpty[16] = { 0u };

  memcpy(&CddTpsGen3_DataMirror.CtrlTx.RegWIDTH_LSB[TEST_Chip2].ucByte[0], &aucTestEmpty[0], sizeof(CddTpsGen3_DataMirror.CtrlTx.RegWIDTH_LSB[TEST_Chip2].ucByte) / sizeof(CddTpsGen3_DataMirror.CtrlTx.RegWIDTH_LSB[TEST_Chip2].ucByte[0]));
  memcpy(&CddTpsGen3_DataMirror.CtrlTx.RegWIDTH_MSB[TEST_Chip2].ucByte[0], &aucTestEmpty[0], sizeof(CddTpsGen3_DataMirror.CtrlTx.RegWIDTH_MSB[TEST_Chip2].ucByte) / sizeof(CddTpsGen3_DataMirror.CtrlTx.RegWIDTH_MSB[TEST_Chip2].ucByte[0]));

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  uint16 aunTestInputDuty[] = TEST_DRV_PWM_1_1024_HBFLAT_16PXLS;

  //Step 3) Call the FUT
  CddTpsGen3_SetDutyCycle_1_1024(TEST_ChipInvalid, &aunTestInputDuty[0]);  // test using invalid index

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(aunTestInputDuty[14], 3u, == );                                             /* PWM val less than MIN_PWM_THD, not updated to  0u due to invalid chip id */

  //Step 3) Call the FUT
  CddTpsGen3_SetDutyCycle_1_1024(TEST_Chip2, &aunTestInputDuty[0]);        // test using valid index

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(CddTpsGen3_DataMirror.CtrlTx.RegWIDTH_LSB[TEST_Chip2].ucByte[0], 0xE8u, == );     /* ValPWM |= ( (ValPWM[i] & 0x0003) << 0u) |  (ValPWM[i+1] & 0x0003) << 2u) | (ValPWM[i+2] & 0x0003) << 4u) | (ValPWM[i+3] & 0x0003) << 6u) ) */
  AL_UNITTEST_CHECK(CddTpsGen3_DataMirror.CtrlTx.RegWIDTH_MSB[TEST_Chip2].ucByte[0], 0x05u, == );     /* ValPWM = ValPWM >> 2                     */
  AL_UNITTEST_CHECK(aunTestInputDuty[14],                                               0u, == );     /* PWM val less than MIN_PWM_THD will be 0u */
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTpsGen3_GetPixelFault
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:
///        Check correct call of interface function to get the pixel fault status
///        based on data mirror
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: Rx of electrical fault stored in data mirror
///
///    - Expected test results:
///        - function returns pixel faults per device
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen3_GetPixelFault(void)
{
  //Step 1) Set pre - conditions
  InitConditions();
  uint16 unRetVal = 0u;

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddTpsGen3_DataMirror.StatRx.RxELEFAULT[TEST_Chip2].ucRxByte[0] = 0x0Fu;  /* pixels 0..3  affected (open) */
  CddTpsGen3_DataMirror.StatRx.RxELEFAULT[TEST_Chip2].ucRxByte[1] = 0xFFu;  /* pixels 8..15 affected (open) */
  CddTpsGen3_DataMirror.StatRx.RxELEFAULT[TEST_Chip2].ucRxByte[2] = 0xF0u;  /* pixels 0..3  affected (short)*/
  CddTpsGen3_DataMirror.StatRx.RxELEFAULT[TEST_Chip2].ucRxByte[3] = 0x00u;  /* pixels 8..15 affected (short)*/

  //Step 3) Call the FUT
  unRetVal = CddTpsGen3_GetPixelFault(TEST_ChipInvalid);    // test using invalid index

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(unRetVal, 0x0000u, == ); 

  //Step 3) Call the FUT
  unRetVal = CddTpsGen3_GetPixelFault(TEST_Chip2);          // test using valid index

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(unRetVal, 0xFFFFu, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTpsGen3_GetComFault
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:
///        Check correct call of interface function to get the communication fault
///        status based on Rx evaluation
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results:
///        - function returns communication status per device
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen3_GetComFault(void)
{
  //Step 1) Set pre - conditions
  InitConditions();
  boolean boRetVal = TRUE;

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddTpsGen3_aboComStatus[TEST_Chip2] = TRUE;

  //Step 3) Call the FUT
  boRetVal = CddTpsGen3_GetComFault(TEST_ChipInvalid);      // test using invalid index

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(boRetVal, FALSE, == );

  //Step 3) Call the FUT
  boRetVal = CddTpsGen3_GetComFault(TEST_Chip2);            // test using invalid index

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(boRetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTpsGen3_GetCrcFault
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:
///        Check correct call of interface function to get the corrupt communication 
///        fault status based on Rx evaluation
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results:
///        - function returns corrupt communication status per device
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen3_GetCrcFault(void)
{
  //Step 1) Set pre - conditions
  InitConditions();
  boolean boRetVal = TRUE;

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddTpsGen3_aboCrcStatus[TEST_Chip2] = TRUE;

  //Step 3) Call the FUT
  boRetVal = CddTpsGen3_GetCrcFault(TEST_ChipInvalid);      // test using invalid index

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(boRetVal, FALSE, == );

  //Step 3) Call the FUT
  boRetVal = CddTpsGen3_GetCrcFault(TEST_Chip2);            // test using invalid index

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(boRetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTpsGen3_GetSensorInfo
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: 
///        Check correct call of interface function to get the sensor data 
///        based on data mirror and completion of all chips reading command
///
///    - Test Design Technique: DT (Decision Table)
///
///    - Preconditions: coding parameters available
///
///    - Expected test results: 
///        - function returns adc results status per device
///
///      - DT-Info:
///         - Inputs:
///            ucChipIdx              :  chip index
///            boComFault             :  chip communication error status
///            boMuxCompleted         :  completion status of reading all chips data for mux command
///            aucADCData[2]          :  data mirror sensor results for current chip
///         - Expected results
///            sSensorData            :  expected value returned  by the FUT, ADC results and signal quality
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen3_GetSensorInfo(void)
{
  typedef struct tsTestCaseDataInput
  {
    uint8   ucChipIdx;
    boolean boComFault;
    boolean boMuxCompleted;
    uint8   aucADCData[2];
  }tsTestCaseDataInput;

  typedef struct tsTestCaseDataOutput
  {
    tsCddMlc_SensorData sSensorData;
  }tsTestCaseDataOutput;

  typedef struct tsTestCaseData
  {
    tsTestCaseDataInput   sInputData;
    tsTestCaseDataOutput  sOutputData;
  }tsTestCaseData;

  tsTestCaseData asTestCaseData[] =
  {
    /*             Input Data                   |                                       Output Data                                         */
    /*     ChipIdx      ,   ComFault,   MuxCompleted,  ADC Values          |      ADC1 (temp),  ADC2 (binning),  SIG Qlty                   */
    { { TEST_ChipInvalid,   FALSE,      FALSE ,       { 252u,   0u    }   } , { { 0u,           0u,              SENSOR_QLTY_INVALID } }  },   // ADC value at -40°C
    { { TEST_Chip4,         FALSE,      FALSE ,       {  54u,   100u  }   } , { { 54u,          100u,            SENSOR_QLTY_SNA     } }  },   // ADC value at  80°C
    { { TEST_Chip4,         TRUE,       TRUE ,        {  54u,   100u  }   } , { { 54u,          100u,            SENSOR_QLTY_INVALID } }  },   // ADC value at  80°C
    { { TEST_Chip4,         FALSE,      TRUE ,        { 174u,   125u  }   } , { { 174u,         125u,            SENSOR_QLTY_VALID   } }  },   // ADC value at  25°C
  };

  for (uint8 ucIdx = 0u; ucIdx < sizeof(asTestCaseData) / sizeof(asTestCaseData[0]); ucIdx++)
  {
    //Step 1) Set pre - conditions
    InitConditions();
    tsCddMlc_SensorData sTestData = { 0u, 0u, SENSOR_QLTY_INVALID };

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    uint8 ucInputChip                                           = asTestCaseData[ucIdx].sInputData.ucChipIdx;
    CddTpsGen3_aboComStatus[ucInputChip]                        = asTestCaseData[ucIdx].sInputData.boComFault;
    CddTpsGen3_boMuxCmdCompleted                                = asTestCaseData[ucIdx].sInputData.boMuxCompleted;
    CddTpsGen3_DataMirror.StatRx.RxADC[ucInputChip].ucRxByte[0] = asTestCaseData[ucIdx].sInputData.aucADCData[0];
    CddTpsGen3_DataMirror.StatRx.RxADC[ucInputChip].ucRxByte[1] = asTestCaseData[ucIdx].sInputData.aucADCData[1];

    //Step 3) Call the FUT
    CddTpsGen3_GetSensorInfo(ucInputChip, &sTestData);      // test using invalid index

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(sTestData.ucADC1Value, asTestCaseData[ucIdx].sOutputData.sSensorData.ucADC1Value, == );
    AL_UNITTEST_CHECK(sTestData.ucADC2Value, asTestCaseData[ucIdx].sOutputData.sSensorData.ucADC2Value, == );
    AL_UNITTEST_CHECK(sTestData.eQlty,       asTestCaseData[ucIdx].sOutputData.sSensorData.eQlty,       == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTpsGen3_ReinitSch
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:
///        Check correct setting of reinitialization request
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results:
///        - function sets reinit command
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen3_ReinitSch(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  InitConditions();

  //Step 3) Call the FUT
  CddTpsGen3_ReinitSch(TRUE);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(CddTpsGen3_boReinitChips, TRUE, == );

  //Step 3) Call the FUT
  CddTpsGen3_ReinitSch(FALSE);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(CddTpsGen3_boReinitChips, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTpsGen3_GetInitStatus
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:
///        Check that the function reads the initialization status and returns
///        its value
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results:
///        - function returns initialization status
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen3_GetInitStatus(void)
{
  boolean boRetVal = FALSE;

  //Step 1) Set pre - conditions
  InitConditions();

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddTpsGen3_boInitCompleted = TRUE;

  //Step 3) Call the FUT
  boRetVal = CddTpsGen3_GetInitStatus();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(boRetVal, TRUE, == );

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddTpsGen3_boInitCompleted = FALSE;

  //Step 3) Call the FUT
  boRetVal = CddTpsGen3_GetInitStatus();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(boRetVal, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTpsGen3_ResetScheduler
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:
///        Check that the function reads the initialization status and the reset
///        request and decides if reset of command scheduler can occur
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results:
///        - function returns reset status
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen3_ResetScheduler(void)
{
  boolean boRetVal = FALSE;

  //Step 1) Set pre - conditions
  InitConditions();

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddTpsGen3_boInitCompleted = TRUE;
  CddTpsGen3_boReinitChips   = TRUE;

  //Step 3) Call the FUT
  boRetVal = CddTpsGen3_ResetScheduler();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(boRetVal, TRUE, == );

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddTpsGen3_boInitCompleted = FALSE;
  CddTpsGen3_boReinitChips   = TRUE;

  //Step 3) Call the FUT
  boRetVal = CddTpsGen3_ResetScheduler();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(boRetVal, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTpsGen3_UartTx
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: 
///        Check that the command frame is correctly computed based on the input
///        from the scheduler table. Check also that mandatory parameters for
///        DMA reception are set correctly at this stage.
///
///    - Test Design Technique: DT (Decision Table)
///
///    - Preconditions: data mirror initialized with default values
///
///    - Expected test results: 
///        - command frame is correctly computed with header bytes, data and crc
///
///      - DT-Info:
///         - Inputs:
///            ucSchedIdx_Tx            :  index of scheduler table line for Tx Cb
///            ucChipIdx                :  chip index for single fast commands
///            ucChipIdx_MuxCmd         :  chip index for single slow commands
///         - Expected results
///            aucHeaderBytes           :  expected value returned  by the FUT, header bytes containing INIT byte | DEVID | REG ADDRS
///            sTxCbData                :  expected value returned  by the FUT, command data for initiating transaction, containing Tx and Rx parameters
///            aucCrcBytes              :  expected value returned  by the FUT, CRC checking on Tx data
///            ucRxChOffset             :  expected value returned  by the FUT, Rx offset computed for correct pointing to Data Mirror of adressed chip
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen3_UartTx(void)
{
  typedef struct tsTestCaseDataInput
  {
    uint8 ucSchedIdx_Tx;
    uint8 ucChipIdx;
    uint8 ucChipIdx_MuxCmd;
  }tsTestCaseDataInput;

  typedef struct tsTestCaseDataOutput
  {
    uint8 aucHeaderBytes[CDDTPSGEN3_SIZE_HEADERBYTES];
    tsCddUart_MessageEntryType sTxCbData;
    uint8 aucCrcBytes[CDDTPSGEN3_SIZE_CRCBYTES];
    uint8 ucRxChOffset;
  }tsTestCaseDataOutput;

  typedef struct tsTestCaseData
  {
    tsTestCaseDataInput     sDataInput;
    tsTestCaseDataOutput    sDataOutput;
  }tsTestCaseData;

  tsTestCaseData asTestCaseData[] =
  {
    /*                     Input Data                  |                                                          Output Data                                                                                                                                                                    */
    /*                                                 |         [                       HEADER BYTES                                 ]    [                                    DATA MIRROR   + CMD DATA                                 ]    [ TX CRC BYTES ]                                   */
    /*     SchedIdx_Tx     ChipIdx    ChipIdx_MuxCmd   |         [    Command     | Device ID              | Reg.Addr                 ]    [   pucTx                   Tx Len                     pucRx                  Rx Len          ]    [  CRCL   CRCH ]     DataMirror RxChOffset         */
                                                                                                                                                                                                                        
    /*    --------- dynamic command   = broadcast      ----------------- */                                                                                                                                             
    {    {          0u,    0u,        0u               },   {   {  TEST_WR_01B,  CDDTPSGEN3_BROADCAST,     CDDTPSGEN3_AddrSYSCFG      },  { TEST_SYSCFG_DEFAULT_Tx,  WR_CMD_LEN(TEST_LEN_01B),  TEST_BR2_SYSCFG,       TEST_LEN_00B, FALSE}, { 0x79u, 0x48u},                           0u   }  },
    {    {          1u,    1u,        0u               },   {   {  TEST_WR_01B,  CDDTPSGEN3_BROADCAST,     CDDTPSGEN3_AddrSYSCFG      },  { TEST_SYSCFG_DEFAULT_Tx,  WR_CMD_LEN(TEST_LEN_01B),  TEST_BR2_SYSCFG,       TEST_LEN_00B, FALSE}, { 0x79u, 0x48u},                           0u   }  },
    /*    --------- dynamic command   = Single FAST    ----------------- */                                                                                                                                                                                
    {    {          2u,    0u,        0u               },   {   {  TEST_RE_01B,  CDDTPSGEN3_DEV_ID11,      CDDTPSGEN3_AddrICID        },  { TEST_ZERO_Tx,            WR_CMD_LEN(TEST_LEN_00B),  TEST_ICID_Rx,          TEST_LEN_03B, FALSE}, { 0x2Eu, 0xA6u},  CDDTPSGEN3_Para_CHIP_IDX(0u)  }  },
    {    {          2u,    1u,        0u               },   {   {  TEST_RE_01B,  CDDTPSGEN3_DEV_ID12,      CDDTPSGEN3_AddrICID        },  { TEST_ZERO_Tx,            WR_CMD_LEN(TEST_LEN_00B),  TEST_ICID_Rx,          TEST_LEN_03B, FALSE}, { 0x7Cu, 0x96u},  CDDTPSGEN3_Para_CHIP_IDX(1u)  }  },
    {    {          2u,    3u,        1u               },   {   {  0u,           0u,                       0u                         },  { TEST_ZERO_Tx,            0u,                        TEST_ZERO_Rx,          0u,           FALSE}, { 0x00u, 0x00u},                           0u   }  },  /*index out of range*/
    /*    --------- dynamic command   = Single SLOW    ----------------- */                                                                                                                                                                                
    {    {         17u,    2u,        1u               },   {   {  TEST_RE_04B,  CDDTPSGEN3_DEV_ID12,      CDDTPSGEN3_AddrOUTCTRL     },  { TEST_ZERO_Tx,            WR_CMD_LEN(TEST_LEN_00B),  TEST_SLEWRATE_Rx,      TEST_LEN_06B, FALSE}, { 0x9Du, 0x10u},  CDDTPSGEN3_Para_CHIP_IDX(1u)  }  },
    {    {         18u,    2u,        1u               },   {   {  TEST_RE_04B,  CDDTPSGEN3_DEV_ID12, CDDTPSGEN3_AddrFLT_OPEN_OR_DRVL },  { TEST_ZERO_Tx,            WR_CMD_LEN(TEST_LEN_00B),  TEST_ELEFAULT_Rx,      TEST_LEN_06B, FALSE}, { 0xDDu, 0x72u},  CDDTPSGEN3_Para_CHIP_IDX(1u)  }  },
    {    {         19u,    2u,        1u               },   {   {  TEST_WR_04B,  CDDTPSGEN3_DEV_ID12, CDDTPSGEN3_AddrFLT_OPEN_OR_DRVL },  { TEST_ELECFAULTS_Tx,      WR_CMD_LEN(TEST_LEN_04B),  TEST_CLR_ELEFAULT_Rx,  TEST_LEN_01B, FALSE}, { 0x95u, 0x78u},  CDDTPSGEN3_Para_CHIP_IDX(1u)  }  },
    {    {         19u,    2u,        2u               },   {   {  0u,           0u,                       0u                         },  { TEST_ZERO_Tx,            0u,                        TEST_ZERO_Rx,          0u,           FALSE}, { 0x00u, 0x00u},                           0u   }  },  /*index out of range*/
    /*    --------- default (out of range SchedIdx_Tx) ----------------- */                                                                                                                                                                                 
    {    {         20u,    0u,        0u               },   {   {  0u,           0u,                       0u                         },  { TEST_ZERO_Tx,            0u,                        TEST_ZERO_Rx,          0u,           FALSE}, { 0x00u, 0x00u},                           0u   }  },  /*index out of range*/
    /*    --------- TEST FOR MLC NOT POWERED  ----------------- */  
    {    {         2u,    0u,        0u                },   {   {  0u,           0u,                       0u                         },  { NULL_PTR,                0u,                        TEST_ZERO_Rx,          0u,           FALSE}, { 0x00u, 0x00u},                           0u   }  },  /* mlc not powered - abort transmission*/

  };

   //Step 1) Set pre - conditions
    uint8 aucCodDevId[CDDTPSGEN3_MAX_CHIPs]   = { 0u,                  6u,                  255u, 255u, 255u, 255u, 255u };
    uint8 aucDevPhyAdd[CDDTPSGEN3_MAX_CHIPs]  = { CDDTPSGEN3_DEV_ID11, CDDTPSGEN3_DEV_ID12, 0u,   0u,   0u,   0u,   0u   };
    memcpy(&CddTpsGen3_sDevData.aucCodDevID[0], &aucCodDevId[0], CDDTPSGEN3_MAX_CHIPs);
    CddTpsGen3_sDevData.asMasterSlaveId[0].ucPhysicalAddr = aucDevPhyAdd[0];
    CddTpsGen3_sDevData.asMasterSlaveId[1].ucPhysicalAddr = aucDevPhyAdd[1];
    CddTpsGen3_sDevData.ucConnectedDevices                = 2u;

  for (uint8 ucIdx = 0u; ucIdx < sizeof(asTestCaseData) / sizeof(asTestCaseData[0]); ucIdx++)
  {
    //Step 1) Set pre - conditions
    InitConditions();
    tsCddUart_MessageEntryType sTestTxCbData = { TEST_ZERO_Tx, 0u, TEST_ZERO_Rx, 0u, FALSE };

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    CddTpsGen3_ucSchedIx        = asTestCaseData[ucIdx].sDataInput.ucSchedIdx_Tx;
    CddTpsGen3_ucChipIdx        = asTestCaseData[ucIdx].sDataInput.ucChipIdx;
    CddTpsGen3_ucChipIdx_MuxCmd = asTestCaseData[ucIdx].sDataInput.ucChipIdx_MuxCmd;

    /* only for the last test data, check the Uart Tx when MLC is not powered*/
    if (ucIdx < 10u)
    {
      Test_Drv_SetCodingStatus(TRUE);
      Test_Drv_SetMlcPower(TRUE);
    }
    else
    {
      Test_Drv_SetMlcPower(FALSE);
    }
    //Step 3) Call the FUT
    CddTpsGen3_UartTx(&sTestTxCbData);

    uint8 ucTxLen     = asTestCaseData[ucIdx].sDataOutput.sTxCbData.ucTxDataLength;
    uint8 ucRxOffset  = asTestCaseData[ucIdx].sDataOutput.sTxCbData.ucRxDataLength * asTestCaseData[ucIdx].sDataOutput.ucRxChOffset;

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    if (ucIdx < 10u) // values for ucIdx < 8u are valid values; starting from ucIdx 8u input values are out of range or matrix not powered
    {
      AL_UNITTEST_CHECK(sTestTxCbData.pucTxData[0], asTestCaseData[ucIdx].sDataOutput.aucHeaderBytes[0], == );
      AL_UNITTEST_CHECK(sTestTxCbData.pucTxData[1], asTestCaseData[ucIdx].sDataOutput.aucHeaderBytes[1], == );
      AL_UNITTEST_CHECK(sTestTxCbData.pucTxData[2], asTestCaseData[ucIdx].sDataOutput.aucHeaderBytes[2], == );


      AL_UNITTEST_CHECK(sTestTxCbData.pucTxData[ucTxLen - 2], asTestCaseData[ucIdx].sDataOutput.aucCrcBytes[0], == );
      AL_UNITTEST_CHECK(sTestTxCbData.pucTxData[ucTxLen - 1], asTestCaseData[ucIdx].sDataOutput.aucCrcBytes[1], == );

      AL_UNITTEST_CHECK(sTestTxCbData.ucTxDataLength, asTestCaseData[ucIdx].sDataOutput.sTxCbData.ucTxDataLength, == );
      AL_UNITTEST_CHECK(sTestTxCbData.ucRxDataLength, asTestCaseData[ucIdx].sDataOutput.sTxCbData.ucRxDataLength, == );
      AL_UNITTEST_CHECK(sTestTxCbData.pucRxData, (asTestCaseData[ucIdx].sDataOutput.sTxCbData.pucRxData + ucRxOffset), == );
    }
    else
    {
      AL_UNITTEST_CHECK(sTestTxCbData.pucTxData,        asTestCaseData[ucIdx].sDataOutput.sTxCbData.pucTxData, == );
      AL_UNITTEST_CHECK(sTestTxCbData.pucRxData,        asTestCaseData[ucIdx].sDataOutput.sTxCbData.pucRxData, == );
      AL_UNITTEST_CHECK(sTestTxCbData.ucRxDataLength,   asTestCaseData[ucIdx].sDataOutput.sTxCbData.ucRxDataLength, == );
      AL_UNITTEST_CHECK(sTestTxCbData.ucTxDataLength,   asTestCaseData[ucIdx].sDataOutput.sTxCbData.ucTxDataLength, == );
    }
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTpsGen3_UartRx
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: 
///        Check that the chip index and scheduler index are correctly computed
///        based on the action and dynamic command from the scheduler table. 
///
///    - Test Design Technique: DT (Decision Table)
///
///    - Preconditions: data mirror initialized with default values
///
///    - Expected test results: 
///        - chip index, chip mux index and scheduler index are updated
///
///      - DT-Info:
///         - Inputs:
///            ucSchedIdx_Rx            :  index of scheduler table line for Rx Cb
///            ucChipIdx                :  chip index for single fast commands
///            ucChipIdx_MuxCmd         :  chip index for single slow commands
///            boRxStatus               :  reception status received by Cb
///            aucPreconditions[2]      :  coding and Vcc status as precondition
///         - Expected results
///            ucSchedIdx_Rx_Next       :  expected value returned  by the FUT, updated scheduler index for table indexing
///            ucChipIdx_Next           :  expected value returned  by the FUT, updated chip index
///            ucChipIdx_MuxCmd_Next    :  expected value returned  by the FUT, updated chip index for multiplexed commands
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen3_UartRx(void)
{
    typedef struct tsTestCaseDataInput
  {
    uint8   ucSchedIdx_Rx;
    uint8   ucChipIdx;
    uint8   ucChipIdx_MuxCmd;
    boolean boRxStatus;
    uint8   aucPreconditions[2];
  }tsTestCaseDataInput;

  typedef struct tsTestCaseDataOutput
  {
    uint8 ucSchedIdx_Rx_Next;
    uint8 ucChipIdx_Next;
    uint8 ucChipIdx_MuxCmd_Next;
  }tsTestCaseDataOutput;

  typedef struct tsTestCaseData
  {
    tsTestCaseDataInput     sDataInput;
    tsTestCaseDataOutput    sDataOutput;
  }tsTestCaseData;

  tsTestCaseData asTestCaseData[] =
  { 
    /*                     Input Data                                                  |            Output Data                 */
    /*                                                                  Preconditions  |                                        */
    /*     SchedIdx_Rx     ChipIdx    ChipIdx_MuxCmd  boRxStatus |   Coding | VCCx         Rx_Next   Chip_Next   ChipMux_Next   */
                                                                                                                                                                                                                        
    /*    --------- dynamic command   = broadcast      ----------------- */                                                                                                                                             
    {    {          0u,    0u,        0u,             FALSE,      { FALSE, FALSE }  },   {  0u,       0u,         0u   } },
    {    {          0u,    1u,        0u,             FALSE,      { TRUE,  FALSE }  },   {  0u,       0u,         0u   } },
    {    {          0u,    1u,        0u,             FALSE,      { FALSE, TRUE  }  },   {  0u,       0u,         0u   } },
    {    {          0u,    1u,        0u,             FALSE,      { TRUE,  TRUE  }  },   {  1u,       0u,         0u   } },
    /*    --------- dynamic command   = Single FAST    ----------------- */                                                                                                                                                                  
    {    {          2u,    0u,        0u,             FALSE,      { TRUE,  TRUE  }  },   {  2u,       1u,         0u   } },
    {    {          2u,    1u,        0u,             TRUE,       { TRUE,  TRUE  }  },   {  3u,       0u,         0u   } },
    {    {          2u,    3u,        1u,             TRUE,       { TRUE,  TRUE  }  },   {  3u,       0u,         1u   } },  /*index out of range*/
    /*    --------- dynamic command   = Single SLOW    ----------------- */                                                    
    {    {         19u,    2u,        0u,             FALSE,      { TRUE,  TRUE  }  },   { 10u,       0u,         1u   } }, 
    {    {         17u,    2u,        1u,             FALSE,      { TRUE,  TRUE  }  },   { 18u,       0u,         1u   } },
    {    {         18u,    2u,        1u,             TRUE,       { TRUE,  TRUE  }  },   { 19u,       0u,         1u   } },
    {    {         19u,    2u,        2u,             FALSE,      { TRUE,  TRUE  }  },   { 10u,       0u,         0u   } },  /*index out of range*/
    /*    --------- default (out of range SchedIdx_Rx) ----------------- */
  };

   //Step 1) Set pre - conditions
    uint8 aucCodDevId[CDDTPSGEN3_MAX_CHIPs]   = { 0u,                  6u,                  255u, 255u, 255u, 255u, 255u };
    uint8 aucDevPhyAdd[CDDTPSGEN3_MAX_CHIPs]  = { CDDTPSGEN3_DEV_ID11, CDDTPSGEN3_DEV_ID12, 0u,   0u,   0u,   0u,   0u   };
    memcpy(&CddTpsGen3_sDevData.aucCodDevID[0], &aucCodDevId[0], CDDTPSGEN3_MAX_CHIPs);
    CddTpsGen3_sDevData.asMasterSlaveId[0].ucPhysicalAddr = aucDevPhyAdd[0];
    CddTpsGen3_sDevData.asMasterSlaveId[1].ucPhysicalAddr = aucDevPhyAdd[1];
    CddTpsGen3_sDevData.ucConnectedDevices                = 2u;

  for (uint8 ucIdx = 0u; ucIdx < sizeof(asTestCaseData) / sizeof(asTestCaseData[0]); ucIdx++)
  {
    //Step 1) Set pre - conditions
    InitConditions();
    uint8 ucDummyRx;
    Test_Drv_SetCodingStatus(asTestCaseData[ucIdx].sDataInput.aucPreconditions[0]);
    Test_Drv_SetMlcPower    (asTestCaseData[ucIdx].sDataInput.aucPreconditions[1]);

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    if (ucIdx == 0) { CddTpsGen3_boInitCompleted = TRUE; CddTpsGen3_boReinitChips = TRUE; } /* start from reinit*/
    CddTpsGen3_ucSchedIx        = asTestCaseData[ucIdx].sDataInput.ucSchedIdx_Rx;
    CddTpsGen3_ucChipIdx        = asTestCaseData[ucIdx].sDataInput.ucChipIdx;
    CddTpsGen3_ucChipIdx_MuxCmd = asTestCaseData[ucIdx].sDataInput.ucChipIdx_MuxCmd;
    boolean boRxStatus          = asTestCaseData[ucIdx].sDataInput.boRxStatus;

    //Step 3) Call the FUT
    CddTpsGen3_UartRx(&ucDummyRx, boRxStatus);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    AL_UNITTEST_CHECK(CddTpsGen3_ucSchedIx,         asTestCaseData[ucIdx].sDataOutput.ucSchedIdx_Rx_Next,     == );
    AL_UNITTEST_CHECK(CddTpsGen3_ucChipIdx,         asTestCaseData[ucIdx].sDataOutput.ucChipIdx_Next,         == );
    AL_UNITTEST_CHECK(CddTpsGen3_ucChipIdx_MuxCmd,  asTestCaseData[ucIdx].sDataOutput.ucChipIdx_MuxCmd_Next,  == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTpsGen3_StAction_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:
///        Check reset value for handling default, no action and check commands
///
///    - Test Design Technique: DT (Decision Table)
///
///    - Preconditions: data mirror initialized with default values
///
///    - Expected test results: 
///        - function returns reset status
///
///      - DT-Info:
///         - Inputs:
///            ucCheckInitCmd           :  action command value
///            boCodingValid            :  coding validity
///            boVccxEn                 :  matrix power status
///         - Expected results
///            boIsReset                :  expected value returned  by the FUT, reset scheduler decision
///            boIsInitCompleted        :  expected value returned  by the FUT, initialization status to start cycle commands
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen3_StAction_TestCase1(void)
{
  struct { uint8 ucCheckInitCmd;              boolean boCodingValid; boolean boVccxEn; boolean boIsReset; boolean boIsInitCompleted; } asTestCaseData[]
    = {                                       
         { CDDTPSGEN3_ST_ACT_DIS_COMM,        FALSE,                 FALSE,            FALSE,             FALSE                      },
         { CDDTPSGEN3_ST_NO_ACT,              FALSE,                 FALSE,            FALSE,             FALSE                      },
         { CDDTPSGEN3_ST_ACT_CHECK_START,     FALSE,                 FALSE,            TRUE,              FALSE                      },
         { CDDTPSGEN3_ST_ACT_CHECK_START,     TRUE,                  FALSE,            TRUE,              FALSE                      },
         { CDDTPSGEN3_ST_ACT_CHECK_START,     FALSE,                 TRUE,             TRUE,              FALSE                      },
         { CDDTPSGEN3_ST_ACT_CHECK_START,     TRUE,                  TRUE,             FALSE,             FALSE                      },
         { CDDTPSGEN3_ST_ACT_START_CYCLE,     TRUE,                  TRUE,             FALSE,             TRUE                       },
         { CDDTPSGEN3_ST_ACT_CHECK_RESTART,   TRUE,                  TRUE,             FALSE,             FALSE                      },
      };

  for (uint8 ucIdx = 0u; ucIdx < sizeof(asTestCaseData) / sizeof(asTestCaseData[0]); ucIdx++)
  {
    //Step 1) Set pre - conditions
    InitConditions();
    Test_Drv_SetCodingStatus(asTestCaseData[ucIdx].boCodingValid);
    Test_Drv_SetMlcPower    (asTestCaseData[ucIdx].boVccxEn);

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    boolean boRetVal     = TRUE;
    uint8   ucTestAction = asTestCaseData[ucIdx].ucCheckInitCmd;

    //Step 3) Call the FUT
    boRetVal = CddTpsGen3_StAction(ucTestAction);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    AL_UNITTEST_CHECK(boRetVal,                   asTestCaseData[ucIdx].boIsReset,            == );
    AL_UNITTEST_CHECK(CddTpsGen3_boInitCompleted, asTestCaseData[ucIdx].boIsInitCompleted,  == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTpsGen3_StAction_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:
///        Check the handling of power on reset action
///
///    - Test Design Technique: DT (Decision Table)
///
///    - Preconditions: coding mapped, data mirror contains PWR status
///
///    - Expected test results: 
///        - function returns reset status and saves PWR on chip affected pos
///
///      - DT-Info:
///         - Inputs:
///            ucChipIdx           :  chip index value
///            ucRxStatus_PWRbit   :  STATUS register with PWR bit value
///         - Expected results
///            boIsReset           :  expected value returned  by the FUT, reset scheduler decision
///            ucPWR_OnBit         :  expected value returned  by the FUT, PWR set on bit position of affected chip
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen3_StAction_TestCase2(void)
{
  struct { uint8 ucChipIdx; uint8 ucRxStatus_PWRbit; boolean boIsReset; uint8 ucPWR_OnBit; } asTestCaseData[]
    = {
         { 1u,                 0x01u,                 FALSE,          0b00000000u   }, /* no PWR err*/
         { 1u,                 0x00u,                 TRUE,           0b01000000u   }, /* PWR err on chip 1*/
         { 0u,                 0xFFu,                 TRUE,           0b01000000u   }, /* no PWR err on chip 0, but previously set on chip 1 */
         { 0u,                 0xFEu,                 TRUE,           0b01000001u   }, /* PWR err on chip 0 + previously set on chip 1 */
      };

    //Step 1) Set pre - conditions
    uint8 aucCodDevId[CDDTPSGEN3_MAX_CHIPs] = { 0u,                  6u,                  255u, 255u, 255u, 255u, 255u };
    memcpy(&CddTpsGen3_sDevData.aucCodDevID[0], &aucCodDevId[0], CDDTPSGEN3_MAX_CHIPs);

  for (uint8 ucIdx = 0u; ucIdx < sizeof(asTestCaseData) / sizeof(asTestCaseData[0]); ucIdx++)
  {
    //Step 1) Set pre - conditions
    InitConditions();

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    boolean boRetVal = TRUE;
    CddTpsGen3_ucChipIdx_MuxCmd             = asTestCaseData[ucIdx].ucChipIdx;
    uint8 ucChipIdRemap                     = CDDTPSGEN3_Para_CHIP_IDX(CddTpsGen3_ucChipIdx_MuxCmd);
    CddTpsGen3_DataMirror.StatRx.RxSTATUS[ucChipIdRemap].ucRxByte[0] = asTestCaseData[ucIdx].ucRxStatus_PWRbit;

    //Step 3) Call the FUT
    boRetVal = CddTpsGen3_StAction(CDDTPSGEN3_ST_ACT_CHECK_PWR);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    AL_UNITTEST_CHECK(boRetVal,                       asTestCaseData[ucIdx].boIsReset,    == );
    AL_UNITTEST_CHECK(CddTpsGen3_ucPowerOnReset_Bit,  asTestCaseData[ucIdx].ucPWR_OnBit,  == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTpsGen3_StAction_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:
///        Check the handling of Chip Configuration Setting action
///
///    - Test Design Technique: DT (Decision Table)
///
///    - Preconditions: coding mapped, data mirror contains initialized values
///
///    - Expected test results: 
///        - function returns reset status and sets OUTCTRL Register for master-slave config
///
///      - DT-Info:
///         - Inputs:
///            ucChipIdx           :  chip index value
///         - Expected results
///            boIsReset           :  expected value returned  by the FUT, reset scheduler decision
///            ucRegOUTCTRL        :  expected value returned  by the FUT, OUTCTRL Register for master-slave config
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen3_StAction_TestCase3(void)
{
    //Step 1) Set pre - conditions
  uint8   aucChipIdx[CDDTPSGEN3_MAX_CHIPs]    = { 0u,    6u,    255u,  255u,  255u,  255u,  255u };
  boolean boMasterChip[CDDTPSGEN3_MAX_CHIPs]  = { TRUE,  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
  memcpy(&CddTpsGen3_sDevData.aucCodDevID[0], &aucChipIdx[0], CDDTPSGEN3_MAX_CHIPs);
  CddTpsGen3_sDevData.asMasterSlaveId[0].boIsMasterId = boMasterChip[0];
  CddTpsGen3_sDevData.asMasterSlaveId[1].boIsMasterId = boMasterChip[1];


  struct { uint8 ucChipIdx;  boolean boIsReset;  uint8 ucRegOUTCTRL; } asTestCaseData[]
    = {   
         {       0u,                 FALSE,            0x06u         },   /* biSYNCOEN  = biSYNCPEN  = 1 */
         {       1u,                 FALSE,            0x00u         },   /* biSYNCOEN  = biSYNCPEN  = 0 */
         {       2u,                 FALSE,            0x00u         },   /*index out of range*/
      };

  for (uint8 ucIdx = 0u; ucIdx < sizeof(asTestCaseData) / sizeof(asTestCaseData[0]); ucIdx++)
  {
    //Step 1) Set pre - conditions
    InitConditions();
    uint8 ucChipIdRemap = CDDTPSGEN3_Para_CHIP_IDX(asTestCaseData[ucIdx].ucChipIdx);

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    boolean boRetVal = TRUE;

    //Step 3) Call the FUT
    boRetVal = CddTpsGen3_StAction(CDDTPSGEN3_ST_ACT_CFG_CHIP);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    AL_UNITTEST_CHECK(boRetVal,                                                     asTestCaseData[ucIdx].boIsReset,      == );
    AL_UNITTEST_CHECK(CddTpsGen3_DataMirror.CtrlTx.RegOUTCTRL[ucChipIdRemap].ucRaw, asTestCaseData[ucIdx].ucRegOUTCTRL,   == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTpsGen3_StAction_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:
///        Check the handling of Leds and Phase Configuration Setting action
///
///    - Test Design Technique: DT (Decision Table)
///
///    - Preconditions: coding mapped, data mirror contains initialized values
///
///    - Expected test results: 
///        - function returns reset status and sets PHASE, SLEWRATE and DEFWIDTHS Registers
///
///      - DT-Info:
///         - Inputs:
///            ucCfgAction               :  action command value
///            ucChipIdx                 :  chip index value
///         - Expected results
///            boIsReset                 :  expected value returned  by the FUT, reset scheduler decision
///            aunRegPHASE_MSB[2]        :  expected value returned  by the FUT, PHASE_MSB Register settings for first and last register address
///            aunRegPHASE_LSB[2]        :  expected value returned  by the FUT, PHASE_LSB Register settings for first and last register address
///            ucRegSLEWRATE             :  expected value returned  by the FUT, Slewrate Registers settings
///            aucRegDEFWIDTH01_16[2]    :  expected value returned  by the FUT, DEFWIDTH Registers settings for first and last register address
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen3_StAction_TestCase4(void)
{
  //Step 1) Set pre - conditions
  uint8   aucChipIdx[CDDTPSGEN3_MAX_CHIPs]    = { 0u,    6u,    255u,  255u,  255u,  255u,  255u };
  boolean boMasterChip[CDDTPSGEN3_MAX_CHIPs]  = { TRUE,  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
  memcpy(&CddTpsGen3_sDevData.aucCodDevID[0], &aucChipIdx[0], CDDTPSGEN3_MAX_CHIPs);
  CddTpsGen3_sDevData.asMasterSlaveId[0].boIsMasterId = boMasterChip[0];
  CddTpsGen3_sDevData.asMasterSlaveId[1].boIsMasterId = boMasterChip[1];

  struct { uint8 
          ucCfgAction;        uint8 ucChipIdx; boolean boIsReset;  uint16 aunRegPHASE_MSB[2];  uint16 aunRegPHASE_LSB[2];  uint8 ucRegSLEWRATE;  uint8 aucRegDEFWIDTH01_16[2]; } asTestCaseData[]
    = {   
      { CDDTPSGEN3_ST_ACT_CFG_LEDS,        0u,             FALSE,        { 0x00u, 0x00u  },           { 0x00u, 0x00u },          0b00010010u,          { 0x00u, 0x00u }        },
      { CDDTPSGEN3_ST_ACT_CFG_LEDS,        1u,             FALSE,        { 0x00u, 0x00u  },           { 0x00u, 0x00u },          0b00010010u,          { 0x00u, 0x00u }        },
      { CDDTPSGEN3_ST_ACT_SET_PHASE,       0u,             FALSE,        { 0x00u, 0x3BFu },           { 0xFCu, 0xFFu },          0b00010010u,          { 0x00u, 0x00u }        },
      { CDDTPSGEN3_ST_ACT_SET_PHASE,       1u,             FALSE,        { 0x00u, 0x3BFu },           { 0xFCu, 0xFFu },          0b00010010u,          { 0x00u, 0x00u }        },
     };

  for (uint8 ucIdx = 0u; ucIdx < sizeof(asTestCaseData) / sizeof(asTestCaseData[0]); ucIdx++)
  {
    //Step 1) Set pre - conditions
    InitConditions();
    uint8 ucChipIdRemap = CDDTPSGEN3_Para_CHIP_IDX(asTestCaseData[ucIdx].ucChipIdx);

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    boolean boRetVal     = TRUE;
    uint8   ucTestAction = asTestCaseData[ucIdx].ucCfgAction;

    //Step 3) Call the FUT
    boRetVal = CddTpsGen3_StAction(ucTestAction);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    AL_UNITTEST_CHECK(boRetVal,  asTestCaseData[ucIdx].boIsReset,  == );

    AL_UNITTEST_CHECK(CddTpsGen3_DataMirror.CtrlTx.RegPHASE_MSB[ucChipIdRemap].ucByte[0],  asTestCaseData[ucIdx].aunRegPHASE_MSB[0] >>2u, == );  /* PHASE01H     = ValPhase >> 2                     */
    AL_UNITTEST_CHECK(CddTpsGen3_DataMirror.CtrlTx.RegPHASE_LSB[ucChipIdRemap].ucByte[0],  asTestCaseData[ucIdx].aunRegPHASE_LSB[0],      == );  /* PHASE04_01L |= ( (ValPhase[i] & 0x0003) << 0u) |  (ValPhase[i+1] & 0x0003) << 2u) | (ValPhase[i+2] & 0x0003) << 4u) | (ValPhase[i+3] & 0x0003) << 6u) */

                                                                                                                                          
    AL_UNITTEST_CHECK(CddTpsGen3_DataMirror.CtrlTx.RegPHASE_MSB[ucChipIdRemap].ucByte[15], asTestCaseData[ucIdx].aunRegPHASE_MSB[1] >>2u, == );  /* PHASE16H    */
    AL_UNITTEST_CHECK(CddTpsGen3_DataMirror.CtrlTx.RegPHASE_LSB[ucChipIdRemap].ucByte[3],  asTestCaseData[ucIdx].aunRegPHASE_LSB[1],      == );  /* PHASE16_13L */
                                                                                                                                          
    AL_UNITTEST_CHECK(CddTpsGen3_DataMirror.CtrlTx.RegSLEWRATE[ucChipIdRemap].ucByte[0],   asTestCaseData[ucIdx].ucRegSLEWRATE,           == );   // SLEWRATE_H
    AL_UNITTEST_CHECK(CddTpsGen3_DataMirror.CtrlTx.RegSLEWRATE[ucChipIdRemap].ucByte[1],   asTestCaseData[ucIdx].ucRegSLEWRATE,           == );   // SLEWRATE_L
                                                                                                                                          
    AL_UNITTEST_CHECK(CddTpsGen3_DataMirror.CtrlTx.RegDEFWIDTH[ucChipIdRemap].ucByte[0],   asTestCaseData[ucIdx].aucRegDEFWIDTH01_16[0],  == );
    AL_UNITTEST_CHECK(CddTpsGen3_DataMirror.CtrlTx.RegDEFWIDTH[ucChipIdRemap].ucByte[15],  asTestCaseData[ucIdx].aucRegDEFWIDTH01_16[1],  == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTpsGen3_StAction_TestCase5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:
///        Check the handling of System Configuration Setting action
///
///    - Test Design Technique: DT (Decision Table)
///
///    - Preconditions: coding mapped, data mirror contains initialized values
///
///    - Expected test results: 
///        - function returns reset status and sets SYSCFG, CMWTAP and PWMTICK Registers
///
///      - DT-Info:
///         - Inputs:
///            ucChipIdx          :  chip index value
///            ucBaudRate         :  baud rate value
///         - Expected results
///            boIsReset          :  expected value returned  by the FUT, reset scheduler decision
///            ucCMWTAPVal        :  expected value returned  by the FUT, CMWTAP Register setting
///            ucPWMTICK_DIV1     :  expected value returned  by the FUT, PWMTICK Register settings for PTBASE
///            ucPWMTICK_DIV2     :  expected value returned  by the FUT, PWMTICK Register settings for PTCNT
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen3_StAction_TestCase5(void)
{
  struct { uint8 ucChipIdx; uint8 ucBaudRate;        boolean boIsReset; uint8 ucCMWTAPVal;           uint8 ucPWMTICK_DIV1;      uint8 ucPWMTICK_DIV2;           } asTestCaseData[]
       = {
         {       0u,        TEST_DRV_BAUDRATE_1Mbps,         FALSE,     CDDTPSGEN3_CFG_CMWTAP_16MHz,       0u,                  CDDTPSGEN3_CFG_PWMTICK_16MHz    },
         {       1u,        TEST_DRV_BAUDRATE_1Mbps,         FALSE,     CDDTPSGEN3_CFG_CMWTAP_16MHz,       0u,                  CDDTPSGEN3_CFG_PWMTICK_16MHz    },
         {       0u,        TEST_DRV_BAUDRATE_500Kbps,       FALSE,     CDDTPSGEN3_CFG_CMWTAP_8MHz,        0u,                  CDDTPSGEN3_CFG_PWMTICK_8MHz     },
         {       1u,        TEST_DRV_BAUDRATE_500Kbps,       FALSE,     CDDTPSGEN3_CFG_CMWTAP_8MHz,        0u,                  CDDTPSGEN3_CFG_PWMTICK_8MHz     },
         {       1u,        0u,                              FALSE,     CDDTPSGEN3_CFG_CMWTAP_8MHz,        0u,                  CDDTPSGEN3_CFG_PWMTICK_8MHz     }, /* out of range index */
         };

  for (uint8 ucIdx = 0u; ucIdx < sizeof(asTestCaseData) / sizeof(asTestCaseData[0]); ucIdx++)
  {
    //Step 1) Set pre - conditions
    InitConditions();

    uint8 ucChipIdRemap = CDDTPSGEN3_Para_CHIP_IDX(asTestCaseData[ucIdx].ucChipIdx);
    CddTpsGen3_sDevData.ucBaudRate = asTestCaseData[ucIdx].ucBaudRate;

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    boolean boRetVal = TRUE;

    //Step 3) Call the FUT
    boRetVal = CddTpsGen3_StAction(CDDTPSGEN3_ST_ACT_SYSCFG);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    AL_UNITTEST_CHECK(boRetVal, asTestCaseData[ucIdx].boIsReset, == );

    AL_UNITTEST_CHECK(CddTpsGen3_DataMirror.CtrlTx.RegSYSCFG[ucChipIdRemap].sSysReg.RegSYSCFG.Bit.biACKEN,    TEST_BIT_ENABLED, == );
    AL_UNITTEST_CHECK(CddTpsGen3_DataMirror.CtrlTx.RegSYSCFG[ucChipIdRemap].sSysReg.RegSYSCFG.Bit.biCHPMP_SS, TEST_BIT_ENABLED, == );
    AL_UNITTEST_CHECK(CddTpsGen3_DataMirror.CtrlTx.RegSYSCFG[ucChipIdRemap].sSysReg.RegSYSCFG.Bit.biCMWEN,    TEST_BIT_ENABLED, == );

    AL_UNITTEST_CHECK(CddTpsGen3_DataMirror.CtrlTx.RegSYSCFG[ucChipIdRemap].sSysReg.RegCMWTAP.ucRaw,            asTestCaseData[ucIdx].ucCMWTAPVal, == );
    AL_UNITTEST_CHECK(CddTpsGen3_DataMirror.CtrlTx.RegSYSCFG[ucChipIdRemap].sSysReg.RegPWMTICK.Bit.biPTBASE,    asTestCaseData[ucIdx].ucPWMTICK_DIV1, == );
    AL_UNITTEST_CHECK(CddTpsGen3_DataMirror.CtrlTx.RegSYSCFG[ucChipIdRemap].sSysReg.RegPWMTICK.Bit.biPTCNT,     asTestCaseData[ucIdx].ucPWMTICK_DIV2, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTpsGen3_StAction
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:
///        Check the handling of each action from scheduler index
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results:
///          All contained test cases are passed
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen3_StAction(void)
{
  Mt_CddTpsGen3_StAction_TestCase1();
  Mt_CddTpsGen3_StAction_TestCase2();
  Mt_CddTpsGen3_StAction_TestCase3();
  Mt_CddTpsGen3_StAction_TestCase4();
  Mt_CddTpsGen3_StAction_TestCase5();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTpsGen3_GetADCReg
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:
///        Check that the function returns the adc results saved in Data Mirror
///        for the requested device
///
///    - Test Design Technique: DT (Decision Table)
///
///    - Preconditions: data mirror contains initialized values
///
///    - Expected test results: 
///        - function returns ADC1 and ADC2 register values from Data Mirror
///
///      - DT-Info:
///         - Inputs:
///            ucChipIdx          :  chip index value
///            aucRxADC[2]        :  Data Mirror values for ADC readings
///         - Expected results
///            aucSensorData[2]   :  expected value returned  by the FUT, sensor data
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen3_GetADCReg(void)
{
  struct { uint8 ucChipIdx;  uint8 aucRxADC[2];  uint8 aucSensorData[2]; }asTestCaseData[]
    =    {
         {   0u,                { 252u, 0u    } ,      { 252u, 0u   }    },        // ADC value at  -40°C
         {   1u,                { 54u,  100u  } ,      { 54u,  100u }    },        // ADC value at  80°C
         {   4u,                { 174u, 125u  } ,      { 174u, 125u }    },        // ADC value at  25°C
         {   6u,                { 20u,  0u    } ,      { 20u,  0u   }    },        // ADC value at  120°C
         {   7u,                { 252u, 0u    } ,      { 0u,   0u   }    },        /* out of range index*/
         };

  for (uint8 ucIdx = 0u; ucIdx < sizeof(asTestCaseData) / sizeof(asTestCaseData[0]); ucIdx++)
  {
    //Step 1) Set pre - conditions
    InitConditions();
    tuCddTpsGen3_RxADC sTestRxADC = { 0u, 0u };

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    uint8 ucChipId = asTestCaseData[ucIdx].ucChipIdx;
    CddTpsGen3_DataMirror.StatRx.RxADC[ucChipId].ucRxByte[0] = asTestCaseData[ucIdx].aucRxADC[0];
    CddTpsGen3_DataMirror.StatRx.RxADC[ucChipId].ucRxByte[1] = asTestCaseData[ucIdx].aucRxADC[1];

    //Step 3) Call the FUT
    CddTpsGen3_GetADCReg(ucChipId, &sTestRxADC);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    AL_UNITTEST_CHECK(sTestRxADC.ucRxByte[0], asTestCaseData[ucIdx].aucSensorData[0], == );
    AL_UNITTEST_CHECK(sTestRxADC.ucRxByte[1], asTestCaseData[ucIdx].aucSensorData[1], == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTpsGen3_GetELEFAULTReg
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:
///        Check that the function returns the pixel fault status saved in Data Mirror
///        for the requested device
///
///    - Test Design Technique: DT (Decision Table)
///
///    - Preconditions: data mirror contains initialized values
///
///    - Expected test results: 
///        - function returns Open-Circuit fault and Short-Circuit fault register values from Data Mirror
///
///      - DT-Info:
///         - Inputs:
///            ucChipIdx          :  chip index value
///            aucRxFLT_OC[2]     :  Data Mirror values for Open-Circuit fault readings
///            aucRxFLT_SC[2]     :  Data Mirror values for Short-Circuit fault readings
///         - Expected results
///            aucELEFAULT[4]     :  expected value returned  by the FUT, pixel fault data
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen3_GetELEFAULTReg(void)
{
  struct { uint8 ucChipIdx;  uint8 aucRxFLT_OC[2];  uint8 aucRxFLT_SC[2];     uint8 aucELEFAULT[4];           }asTestCaseData[]
    = {
         {   0u,                  { 0x0Fu, 0x00u } ,      { 0xF0u, 0x00u },   { 0x0Fu, 0x00u, 0xF0u, 0x00u } },        /* pixels 0..3  affected  */
         {   1u,                  { 0x00u, 0xFFu } ,      { 0x00u, 0x00u },   { 0x00u, 0xFFu, 0x00u, 0x00u } },        /* pixels 8..15 affected  */
         {   4u,                  { 0xFFu, 0xFFu } ,      { 0xFFu, 0xFFu },   { 0xFFu, 0xFFu, 0xFFu, 0xFFu } },        /* all pixels affected    */
         {   6u,                  { 0x00u, 0x00u } ,      { 0x00u, 0x00u },   { 0x00u, 0x00u, 0x00u, 0x00u } },        /* no pixels  affected    */
         {   7u,                  { 0xFEu, 0xFFu } ,      { 0x01u, 0x10u },   { 0x00u, 0x00u, 0x00u, 0x00u } },        /* out of range index*/
      };

  for (uint8 ucIdx = 0u; ucIdx < sizeof(asTestCaseData) / sizeof(asTestCaseData[0]); ucIdx++)
  {
    //Step 1) Set pre - conditions
    InitConditions();
    tuCddTpsGen3_RxELEFAULT sTestRxELEFAULT = { 0u, 0u, 0u, 0u};

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    uint8 ucChipId = asTestCaseData[ucIdx].ucChipIdx;
    CddTpsGen3_DataMirror.StatRx.RxELEFAULT[ucChipId].ucRxByte[0] = asTestCaseData[ucIdx].aucRxFLT_OC[0];
    CddTpsGen3_DataMirror.StatRx.RxELEFAULT[ucChipId].ucRxByte[1] = asTestCaseData[ucIdx].aucRxFLT_OC[1];
    CddTpsGen3_DataMirror.StatRx.RxELEFAULT[ucChipId].ucRxByte[2] = asTestCaseData[ucIdx].aucRxFLT_SC[0];
    CddTpsGen3_DataMirror.StatRx.RxELEFAULT[ucChipId].ucRxByte[3] = asTestCaseData[ucIdx].aucRxFLT_SC[1];

    //Step 3) Call the FUT
    CddTpsGen3_GetELEFAULTReg(ucChipId, &sTestRxELEFAULT);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    AL_UNITTEST_CHECK(sTestRxELEFAULT.ucRxByte[0], asTestCaseData[ucIdx].aucELEFAULT[0], == );
    AL_UNITTEST_CHECK(sTestRxELEFAULT.ucRxByte[1], asTestCaseData[ucIdx].aucELEFAULT[1], == );
    AL_UNITTEST_CHECK(sTestRxELEFAULT.ucRxByte[2], asTestCaseData[ucIdx].aucELEFAULT[2], == );
    AL_UNITTEST_CHECK(sTestRxELEFAULT.ucRxByte[3], asTestCaseData[ucIdx].aucELEFAULT[3], == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTpsGen3_GetPWRStatus
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:
///        Check that the function returns PWR status from global variable
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///       CddTpsGen3_ucPowerOnReset_Bit is set
///
///    - Expected test results:
///          function returns PWR status from global variable
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen3_GetPWRStatus(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  uint8 ucRetVal = 0x00u;
  CddTpsGen3_ucPowerOnReset_Bit = 0x41u;

  //Step 3) Call the FUT
  ucRetVal = CddTpsGen3_GetPWRStatus();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(ucRetVal, 0x41u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTpsGen3_CheckReadCommand
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:
///        Verify that the function checks if command type is a read command and
///        returns correct status
///
///    - Test Design Technique: DT (Decision Table)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - function returns True for accepted read commands, otherwise returns false
///
///      - DT-Info:
///         - Inputs:
///            ucCmdType          :  command type 
///         - Expected results
///           boIsReadCmd         :  expected value returned  by the FUT, command read detected
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen3_CheckReadCommand(void)
{
  struct { uint8 ucCmdType;           boolean boIsReadCmd; } asTestCaseData[]
    =    {
         { TEST_RE_01B,                       TRUE },
         { TEST_RE_02B,                       TRUE },
         { TEST_RE_03B,                       TRUE },
         { TEST_RE_04B,                       TRUE },
         { TEST_RE_12B,                       TRUE },
         { TEST_RE_16B,                       TRUE },
         { TEST_RE_32B,                       TRUE },
    /* read command type not suppored --- extended protocol */
         { CDDTPSGEN3_READ_05_BYTES,          FALSE },
         { CDDTPSGEN3_READ_08_BYTES,          FALSE },
         { CDDTPSGEN3_READ_20_BYTES,          FALSE },
    /* write command type   */
         { TEST_WR_32B,                       FALSE },
         };

  for (uint8 ucIdx = 0u; ucIdx < sizeof(asTestCaseData) / sizeof(asTestCaseData[0]); ucIdx++)
  {
    //Step 1) Set pre - conditions
    InitConditions();
    boolean boRetVal = FALSE;

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    uint8 ucTestCmdType = asTestCaseData[ucIdx].ucCmdType;

    //Step 3) Call the FUT
    boRetVal = CddTpsGen3_CheckReadCommand(ucTestCmdType);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    AL_UNITTEST_CHECK(boRetVal, asTestCaseData[ucIdx].boIsReadCmd, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTpsGen3_SetCrcStatus
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:
///        Verify that the function calculates the CRC over Rx Data from read commands 
///        and compares with the CRC saved in Data Mirror from Rx Callback call.
///        If CRC bytes are different, the function must set CRC error on the affected chip
///        position.
///
///    - Test Design Technique: DT (Decision Table)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - function returns True for accepted read commands, otherwise returns false
///
///      - DT-Info:
///         - Inputs:
///            ucSchedIdx_Rx       :  scheduler table index
///            ucChipIdx           :  chip index for single fast commands 
///            ucChipMuxIdx        :  chip index for single slow commands (multiplexed)
///            aucRxICID[3]        :  Data Mirror Rx content for ICID read data
///            aucRxADC[6]         :  Data Mirror Rx content for ADC read data
///         - Expected results
///           boIsCrcError         :  expected value returned  by the FUT, crc error detected
///
//-----------------------------------------------------------------------------
void Mt_CddTpsGen3_SetCrcStatus(void)
{

  struct { uint8 ucSchedIdx_Rx;  uint8 ucChipIdx; uint8 ucChipMuxIdx;  uint8 aucRxICID[3];    uint8 aucRxADC[6];                           boolean boIsCrcError; }asTestCaseData[]
    =    {
         /* read command type on single fast dyn command */
         {       2u,                   0u,              0u,           { 0x96u, 0x80u, 0x6Eu }, { 0x36u, 0x64u, 0x00u, 0x00u, 0x4Eu, 0x57u} ,        FALSE         },
         {       2u,                   1u,              0u,           { 0x98u, 0x80u, 0x6Eu }, { 0x36u, 0x64u, 0x00u, 0x00u, 0x4Eu, 0x57u} ,        TRUE          },
         /* read command type on single slow dyn command */
         {       14u,                  1u,              1u,           { 0x98u, 0x01u, 0xAAu }, { 0x36u, 0x64u, 0x00u, 0x00u, 0x4Fu, 0x57u} ,        TRUE          },
         {       14u,                  1u,              1u,           { 0x98u, 0x01u, 0xAAu }, { 0x36u, 0x64u, 0x00u, 0x00u, 0x4Eu, 0x57u} ,        FALSE         },
         /* write command type not suppored on Crc check */
         {       15u,                  0u,              1u,           { 0x96u, 0x80u, 0x6Fu }, { 0x36u, 0x64u, 0x00u, 0x00u, 0x4Eu, 0x57u} ,        FALSE         },
         };

  uint8 aucCrcInit[TEST_Cfg_Chips] = { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };

  for (uint8 ucIdx = 0u; ucIdx < sizeof(asTestCaseData) / sizeof(asTestCaseData[0]); ucIdx++)
  {
    //Step 1) Set pre - conditions
    InitConditions();
    memcpy(&CddTpsGen3_aboCrcStatus[0], &aucCrcInit[0], TEST_Cfg_Chips);   //start with reset value

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    CddTpsGen3_ucSchedIx        = asTestCaseData[ucIdx].ucSchedIdx_Rx;
    CddTpsGen3_ucChipIdx        = asTestCaseData[ucIdx].ucChipIdx;
    CddTpsGen3_ucChipIdx_MuxCmd = asTestCaseData[ucIdx].ucChipMuxIdx;

    tsCddTpsGen3_UartSchedTable* psTestTabEntry = &CddTpsGen3_asUartSchedTable[CddTpsGen3_ucSchedIx];

    uint8 ucTestChipType = (psTestTabEntry->eDynCmd == eSingleFASTCmd) ? asTestCaseData[ucIdx].ucChipIdx : asTestCaseData[ucIdx].ucChipMuxIdx;

    memcpy(&CddTpsGen3_DataMirror.StatRx.RxICID[CDDTPSGEN3_Para_CHIP_IDX(ucTestChipType)].ucRxByte[0], &asTestCaseData[ucIdx].aucRxICID[0], sizeof(asTestCaseData[ucIdx].aucRxICID)/sizeof(asTestCaseData[ucIdx].aucRxICID[0]));
    memcpy(&CddTpsGen3_DataMirror.StatRx.RxADC[CDDTPSGEN3_Para_CHIP_IDX(ucTestChipType)].ucRxByte[0],  &asTestCaseData[ucIdx].aucRxADC[0],  sizeof(asTestCaseData[ucIdx].aucRxADC) / sizeof(asTestCaseData[ucIdx].aucRxADC[0]));

    //Step 3) Call the FUT
    CddTpsGen3_SetCrcStatus(psTestTabEntry);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    AL_UNITTEST_CHECK(CddTpsGen3_aboCrcStatus[CDDTPSGEN3_Para_CHIP_IDX(ucTestChipType)], asTestCaseData[ucIdx].boIsCrcError, == );
  }
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
  MakeCopyOfInitializedStatics();
  /* CRC computation : http://www.sunshine2k.de/coding/javascript/crc/crc_js.html , CRC16 = CRC16_ARC*/

  /* CddTpsGen3.c */
  ALUnitTest_AddFunction("Mt_CddTpsGen3_Init",                Mt_CddTpsGen3_Init);
  ALUnitTest_AddFunction("Mt_CddTpsGen3_Cycle",               Mt_CddTpsGen3_Cycle);
  ALUnitTest_AddFunction("Mt_CddTpsGen3_pfGetDevData",        Mt_CddTpsGen3_pfGetDevData);
  ALUnitTest_AddFunction("Mt_CddTpsGen3_SetDutyCycle_1_1024", Mt_CddTpsGen3_SetDutyCycle_1_1024);
  ALUnitTest_AddFunction("Mt_CddTpsGen3_GetPixelFault",       Mt_CddTpsGen3_GetPixelFault);
  ALUnitTest_AddFunction("Mt_CddTpsGen3_GetComFault",         Mt_CddTpsGen3_GetComFault);
  ALUnitTest_AddFunction("Mt_CddTpsGen3_GetCrcFault",         Mt_CddTpsGen3_GetCrcFault);
  ALUnitTest_AddFunction("Mt_CddTpsGen3_GetSensorInfo",       Mt_CddTpsGen3_GetSensorInfo);
  ALUnitTest_AddFunction("Mt_CddTpsGen3_ReinitSch",           Mt_CddTpsGen3_ReinitSch);
  ALUnitTest_AddFunction("Mt_CddTpsGen3_ResetScheduler",      Mt_CddTpsGen3_ResetScheduler);
  ALUnitTest_AddFunction("Mt_CddTpsGen3_GetInitStatus",       Mt_CddTpsGen3_GetInitStatus);

  /* CddTpsGen3_Com.c */
  ALUnitTest_AddFunction("Mt_CddTpsGen3_UartTx",              Mt_CddTpsGen3_UartTx);
  ALUnitTest_AddFunction("Mt_CddTpsGen3_UartRx",              Mt_CddTpsGen3_UartRx);
  ALUnitTest_AddFunction("Mt_CddTpsGen3_StAction",            Mt_CddTpsGen3_StAction);
  ALUnitTest_AddFunction("Mt_CddTpsGen3_GetADCReg",           Mt_CddTpsGen3_GetADCReg);
  ALUnitTest_AddFunction("Mt_CddTpsGen3_GetELEFAULTReg",      Mt_CddTpsGen3_GetELEFAULTReg);
  ALUnitTest_AddFunction("Mt_CddTpsGen3_GetPWRStatus",        Mt_CddTpsGen3_GetPWRStatus);
  ALUnitTest_AddFunction("Mt_CddTpsGen3_CheckReadCommand",    Mt_CddTpsGen3_CheckReadCommand);
  ALUnitTest_AddFunction("Mt_CddTpsGen3_SetCrcStatus",        Mt_CddTpsGen3_SetCrcStatus);
}



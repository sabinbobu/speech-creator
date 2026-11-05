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
/// \file  Test_Adapter.c
///
/// \brief Additional test cases for adapter
///        These tests must be customized according to the adapter implementation
///
//-----------------------------------------------------------------------------

// Standard unit test header
#include <ALUnitTest_UserInterface.h>

// Stub headers
#include <Test_Ext.h>
#include "Test_Stubs.h"

// Headers of the unit test Module
#include <Test_Adapter.h>

#include <Test.h>

//-----------------------------------------------------------------------------
// Global variable stubs
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Test Cases
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddMlc_Read_CodingPara
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: 
///        Check the reading of coding parameters via RTE
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///         Rte_Read_CodM_CddMlc_Para_HitCount                          = 0u
///         Rte_Read_CodM_CddMlc_Para_Param1.eCodingState               = eParaFct0_CodingDataValid
///         Rte_Read_CodM_CddMlc_Para_Param1.psCodingParameters_Blocks  = &Coding_Dummy
///
///    - Expected test results: 
///        - save the coding data
///         sTestData.eCodingState = eParaFct0_CodingDataValid
///         Rte_Read_CodM_CddMlc_Para_HitCount         = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddMlc_Read_CodingPara(void)
{
  //Step 1) Set pre - conditions
  tsCddMlc_CodingParam sTestData = { 0u } ;
  Rte_Read_CodM_CddMlc_Para_HitCount = 0u;

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Rte_Read_CodM_CddMlc_Para_Param1.eCodingState               = eParaFct0_CodingDataValid;
  Rte_Read_CodM_CddMlc_Para_Param1.psCodingParameters_Blocks  = &Coding_Dummy;

  //Step 3) Call the FUT
  CddMlc_Read_CodingPara(&sTestData);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(sTestData.eCodingState,               eParaFct0_CodingDataValid, == );
  AL_UNITTEST_CHECK(Rte_Read_CodM_CddMlc_Para_HitCount,                          1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddMlc_ParaFct0
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: 
///        CHeck the validity of coding data
///
///    - Test Design Technique: DT (Decision Table)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - return coding data validity
///
///      - DT-Info:
///         - Inputs:
///            eCodingCmd :  state of coding parameters validity
///            pData      :  address of coding parameters
///         - Expected results
///            boRetValidity     :  expected value returned  by the FUT
///
//-----------------------------------------------------------------------------
void Mt_CddMlc_ParaFct0(void)
{
  typedef struct tsTestCaseDataInput
  {
    tParaFct0_Cmd         eCodingCmd;
    tNvmPara_CodingArea*  pData;
  }tsTestCaseDataInput;

  typedef struct tsTestCaseDataOutput
  {
    boolean boRetValidity;
  }tsTestCaseDataOutput;

  typedef struct tsTestCaseData
  {
    tsTestCaseDataInput  sInputData;
    tsTestCaseDataOutput sOutputData;
  }tsTestCaseData;

  boolean boRetVal;

  tsTestCaseData asTestCaseData[] =
  {                                                          
    //                  Inputs                               ||     Outputs
    //          eCodingCmd            ,  pData,              ||   RetValidity
   {    {  eParaFct0_CodingDataInvalid, &Coding_Dummy    }   ,   {  FALSE } },
   {    {  eParaFct0_CodingDataValid,   &Coding_Dummy    }   ,   {  TRUE  } },
   {    {  255,                         &Coding_Dummy    }   ,   {  FALSE } },
   {    {  255,                         NULL_PTR         }   ,   {  FALSE } },
  };

  //Step 1) Set pre - conditions
  tParaFct0_Cmd         eTestData_CodingStatus;
  tNvmPara_CodingArea*  psTestData;

  for (uint8 ucIdx = 0u; ucIdx < sizeof(asTestCaseData) / sizeof(asTestCaseData[0]); ucIdx++)
  {
    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    eTestData_CodingStatus  = asTestCaseData[ucIdx].sInputData.eCodingCmd;
    psTestData              = asTestCaseData[ucIdx].sInputData.pData;

    //Step 3) Call the FUT
    boRetVal = CddMlc_ParaFct0(eTestData_CodingStatus, psTestData);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    AL_UNITTEST_CHECK(boRetVal, asTestCaseData[ucIdx].sOutputData.boRetValidity, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddMlc_CodingDataValidation
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: 
///        Handle coding data validation
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///         Rte_Read_CodM_CddMlc_Para_HitCount                          = 0u
///         Rte_Read_CodM_CddMlc_Para_Param1.eCodingState               = eParaFct0_CodingDataValid
///         Rte_Read_CodM_CddMlc_Para_Param1.psCodingParameters_Blocks  = &Coding_Dummy
///
///    - Expected test results: 
///        -coding data validity
///         boRetVal = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CddMlc_CodingDataValidation(void)
{
  //Step 1) Set pre - conditions
  Rte_Read_CodM_CddMlc_Para_HitCount = 0u;

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Rte_Read_CodM_CddMlc_Para_Param1.eCodingState               = eParaFct0_CodingDataValid;
  Rte_Read_CodM_CddMlc_Para_Param1.psCodingParameters_Blocks  = &Coding_Dummy;

  //Step 3) Call the FUT
  boolean boRetVal = CddMlc_CodingDataValidation();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(boRetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddMlc_DeviceCfg
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: 
///        Save the supported number of pixels based on coding configuration
///
///    - Test Design Technique: DT (Decision Table)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - return coding data validity
///
///      - DT-Info:
///         - Inputs:
///            ucMlcType :  device matrix type from coding
///         - Expected results
///            ucSupportedPixels :  expected value returned  by the FUT, number of supported pixels
///            eDevConnected     :  expected value returned  by the FUT, device name connected
///
//-----------------------------------------------------------------------------
void Mt_CddMlc_DeviceCfg(void)
{
  typedef struct tsTestCaseDataInput
  {
    uint8 ucMlcType;
  }tsTestCaseDataInput;

  typedef struct tsTestCaseDataOutput
  {
    uint8                 ucSupportedPixels;
    teCddMlc_DeviceType   eDevConnected;
  }tsTestCaseDataOutput;

  typedef struct tsTestCaseData
  {
    tsTestCaseDataInput  sInputData;
    tsTestCaseDataOutput sOutputData;
  }tsTestCaseData;

  teCddMlc_DeviceType eRetDevType;

  tsTestCaseData asTestCaseData[] =
  {                                           
    //        Inputs                          ||                                Outputs
    //      ucMlcType                         ||       ucSupportedPixels                     ,         eDevConnected
    { { CDDMLC_COD_MATRIX_TYPE_DISABLED      }, {  0u                                        ,     eMlcDeviceMax           } },
    { { CDDMLC_COD_MATRIX_TYPE_TPSGEN2_662A  }, {  CDDMLC_TPSGEN2_MAX_SWITCHES_PER_DEVICE    ,     eMlcDevice_DEV_TI_GEN2  } },
    { { CDDMLC_COD_MATRIX_TYPE_TPSGEN2_663A  }, {  CDDMLC_TPSGEN2_3A_MAX_SWITCHES_PER_DEVICE ,     eMlcDevice_DEV_TI_GEN2  } },
    { { CDDMLC_COD_MATRIX_TYPE_TPSGEN3_664   }, {  CDDMLC_TPSGENx_MAX_SWITCHES_PER_DEVICE    ,     eMlcDevice_DEV_TI_GEN3  } },
    { { CDDMLC_COD_MATRIX_TYPE_TPSGEN3_665   }, {  CDDMLC_TPSGENx_MAX_SWITCHES_PER_DEVICE    ,     eMlcDevice_DEV_TI_GEN3  } },
    { { CDDMLC_COD_MATRIX_TYPE_TPSGEN3_667   }, {  CDDMLC_TPSGENx_MAX_SWITCHES_PER_DEVICE    ,     eMlcDevice_DEV_TI_GEN3  } },
    { { CDDMLC_COD_MATRIX_TYPE_TPSGENx_1     }, {  CDDMLC_TPSGENx_MAX_SWITCHES_PER_DEVICE    ,     eMlcDevice_DEV_MIXED_TI } },
    { { CDDMLC_COD_MATRIX_TYPE_TPSGENx_2     }, {  CDDMLC_TPSGENx_MAX_SWITCHES_PER_DEVICE    ,     eMlcDevice_DEV_MIXED_TI } },
    { { CDDMLC_COD_MATRIX_TYPE_NXP           }, {  0u                                        ,     eMlcDeviceMax           } },
  };

  for (uint8 ucIdx = 0u; ucIdx < sizeof(asTestCaseData) / sizeof(asTestCaseData[0]); ucIdx++)
  {
    //Step 1) Set pre - conditions
    CddMlc_sCodingData.ucMlcSwitchsSupported = 0u;
    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    CddMlc_sCodingData.ucMlcMatrixType = asTestCaseData[ucIdx].sInputData.ucMlcType;

    //Step 3) Call the FUT
    eRetDevType = CddMlc_DeviceCfg();

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    AL_UNITTEST_CHECK(CddMlc_sCodingData.ucMlcSwitchsSupported, asTestCaseData[ucIdx].sOutputData.ucSupportedPixels, == );
    AL_UNITTEST_CHECK(eRetDevType,                              asTestCaseData[ucIdx].sOutputData.eDevConnected,     == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddMlc_Data_LmmConfig
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: 
///        Evaluate and save the coding configuration, count the connected devices
///
///    - Test Design Technique: DT (Decision Table)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - coding data loaded into global variable
///
///      - DT-Info:
///         - Inputs:
///            ucMlcType :  device matrix type to load corresponding coding test configuration
///         - Expected results
///            ucCodMlcType                       :  expected value returned  by the FUT, matrix device type connected
///            ucMlcBaudRate                      :  expected value returned  by the FUT, baud rate configured
///            aucMlcUartDevID[TEST_Cfg_Chips]    :  expected value returned  by the FUT, matrix device IDs (physical addresses)
///            ucEepromId                         :  expected value returned  by the FUT, eeprom address attached to a connected chip
///            ucTotalDevConnected                :  expected value returned  by the FUT, total connected devices based on coding
///            ucMlcIfc                           :  expected value returned  by the FUT, communication interface
///
//-----------------------------------------------------------------------------
void Mt_CddMlc_Data_LmmConfig(void)
{
  typedef struct tsTestCaseDataInput
  {
    uint8 ucMlcType;
  }tsTestCaseDataInput;

  typedef struct tsTestCaseDataOutput
  {
    uint8   ucCodMlcType;
    uint8   ucMlcBaudRate;
    uint8   aucMlcUartDevID[TEST_Cfg_Chips];
    uint8   ucEepromId;
    uint8   ucTotalDevConnected;
    uint8   ucMlcIfc;
  }tsTestCaseDataOutput;

  typedef struct tsTestCaseData
  {
    tsTestCaseDataInput  sInputData;
    tsTestCaseDataOutput sOutputData;
  }tsTestCaseData;

  tsTestCaseData asTestCaseData[] =
  {
    //        Inputs              ||                                Outputs                                                          
    //                                                                                                                                                 Total connected
    //      ucMlcType             ||             ucCodMlcType,             ucMlcBaudRate,    aucMlcUartDevID,                            ucEeepromId ,   Devices ,     ucMlcIfc    
                                                                                                                                         
    { { TEST_DRV_DISABLED          } , { CDDMLC_COD_MATRIX_TYPE_DISABLED,      0u,             {0u, 0u, 0u, 0u, 0u, 0u, 0u},               255u,           0u ,          CDDMLC_COD_MATRIX_INTERFACE_PRIVATE_CAN   }  },
    { { TEST_DRV_TYPE_TPSGEN2_662A } , { CDDMLC_COD_MATRIX_TYPE_TPSGEN2_662A,  5u,             TEST_DRV_COD_TYPE_TPSGEN2_UART_ADDRS,       4u,             5u ,          CDDMLC_COD_MATRIX_INTERFACE_PRIVATE_CAN   }  },
    { { TEST_DRV_TYPE_TPSGEN2_663A } , { CDDMLC_COD_MATRIX_TYPE_TPSGEN2_663A,  10u,            TEST_DRV_COD_TYPE_TPSGEN2_UART_ADDRS,       255u,           5u ,          CDDMLC_COD_MATRIX_INTERFACE_PRIVATE_CAN   }  },
    { { TEST_DRV_TYPE_TPSGEN3_664  } , { CDDMLC_COD_MATRIX_TYPE_TPSGEN3_664,   5u,             TEST_DRV_COD_TYPE_TPSGEN3_664_UART_ADDRS,   255u,           2u ,          CDDMLC_COD_MATRIX_INTERFACE_PRIVATE_CAN   }  },
    { { TEST_DRV_TYPE_TPSGEN3_665  } , { CDDMLC_COD_MATRIX_TYPE_TPSGEN3_665,   10u,            TEST_DRV_COD_TYPE_TPSGEN3_665_UART_ADDRS,   255u,           2u ,          CDDMLC_COD_MATRIX_INTERFACE_PRIVATE_CAN   }  },
    { { TEST_DRV_TYPE_TPSGEN3_667  } , { CDDMLC_COD_MATRIX_TYPE_TPSGEN3_667,   10u,            TEST_DRV_COD_TYPE_TPSGEN3_667_UART_ADDRS,   255u,           2u ,          CDDMLC_COD_MATRIX_INTERFACE_PRIVATE_CAN   }  },
    { { TEST_DRV_TYPE_TPSGENx_1    } , { CDDMLC_COD_MATRIX_TYPE_TPSGENx_1,     5u,             TEST_DRV_COD_TYPE_TPSGENx_1_UART_ADDRS,     255u,           4u ,          CDDMLC_COD_MATRIX_INTERFACE_PRIVATE_CAN   }  },
    { { TEST_DRV_TYPE_TPSGENx_2    } , { CDDMLC_COD_MATRIX_TYPE_TPSGENx_2,     10u,            TEST_DRV_COD_TYPE_TPSGENx_1_UART_ADDRS,     255u,           4u ,          CDDMLC_COD_MATRIX_INTERFACE_PRIVATE_CAN   }  },
    { { TEST_DRV_TYPE_NXP          } , { CDDMLC_COD_MATRIX_TYPE_NXP,           0u,             {0u, 0u, 0u, 0u, 0u, 0u, 0u},               255u,           0u ,          CDDMLC_COD_MATRIX_INTERFACE_SATELLITE_CAN }  },
  };
  
  for (uint8 ucIdx = 0u; ucIdx < sizeof(asTestCaseData) / sizeof(asTestCaseData[0]); ucIdx++)
  {
    //Step 1) Set pre - conditions
    CddMlc_sCodingData = (tsCddMlc_CodingData){ 0u, 0u, {0u}, 0u, 0u, 0u, 0u, 0u, 0u, FALSE };
    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    uint8 ucInputMlcTypeData = asTestCaseData[ucIdx].sInputData.ucMlcType;
    // load coding parameters specific for each test case
    memcpy(&CddMlc_pCodingArea->LmmConfig.LMM_Config_Diagnosis, &Test_Drv_CodingConfig_Variants[ucInputMlcTypeData], sizeof(tsNvmPara_LmmConfig_LMM_Config_Diagnosis));

    //Step 3) Call the FUT
    CddMlc_Data_LmmConfig();

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    AL_UNITTEST_CHECK(CddMlc_sCodingData.ucMlcMatrixType,                   asTestCaseData[ucIdx].sOutputData.ucCodMlcType ,              == );
    AL_UNITTEST_CHECK(CddMlc_sCodingData.ucMlcBaudRate,                     asTestCaseData[ucIdx].sOutputData.ucMlcBaudRate,              == );
    for (uint8 ucDevIdx = 0u; ucDevIdx < TEST_Cfg_Chips; ucDevIdx++)
    {
     AL_UNITTEST_CHECK(CddMlc_sCodingData.aucMlcCanUartDeviceID[ucDevIdx],  asTestCaseData[ucIdx].sOutputData.aucMlcUartDevID[ucDevIdx],  == );
    }
    AL_UNITTEST_CHECK(CddMlc_sCodingData.ucMlcEepromDeviceID,               asTestCaseData[ucIdx].sOutputData.ucEepromId,                 == );
    AL_UNITTEST_CHECK(CddMlc_sCodingData.ucMlcConnectedDevs,                asTestCaseData[ucIdx].sOutputData.ucTotalDevConnected,        == );  // TBD: if type is NXP or invalid value, it is counted !!!
    AL_UNITTEST_CHECK(CddMlc_sCodingData.ucMlcCanUartInterface,             asTestCaseData[ucIdx].sOutputData.ucMlcIfc,                   == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddMlc_Cod_UartGetConfig
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: 
///        Function acts as callback, it's called by UART which gives its own configuration
///        as first parameter. Based on callback input, test that it sets the coded baud rate
///        and saves the mounted device as parameter
///
///    - Test Design Technique: DT (Decision Table)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - baud rate is saved and mounted devices are set on bits
///
///      - DT-Info:
///         - Inputs:
///            ucCbInputDevCfg    :  input parameter of UART device configuration
///            ucDevTypeConnected :  device matrix type to evaluate corresponding configuration
///            ucCodBaudRate      :  device baud rate load to evaluate corresponding configuration
///         - Expected results
///            ucBaudRate                      :  expected value returned  by the FUT, baud rate configured
///            pucCbMountedDevs                :  expected value returned  by the FUT, total mounted devices on bits, based on coding
///            boOutputStatus                  :  expected value returned  by the FUT, coding status
///
//-----------------------------------------------------------------------------
void Mt_CddMlc_Cod_UartGetConfig(void)
{
  typedef struct tsTestCaseDataInput
  {
    uint8 ucCbInputDevCfg;
    uint8 ucDevTypeConnected;
    uint8 ucCodBaudRate;
  }tsTestCaseDataInput;

  typedef struct tsTestCaseDataOutput
  {
    uint8   ucBaudRate;
    uint8   pucCbMountedDevs;
    boolean boOutputStatus;
  }tsTestCaseDataOutput;

  typedef struct tsTestCaseData
  {
    tsTestCaseDataInput   sInputData;
    tsTestCaseDataOutput  sOutputData;
  }tsTestCaseData;

  tsTestCaseData asTestCaseData[] =
  {
    //                              Inputs                                                  ||                     Outputs                                        
    // CbInputDevCfg                            DevTypeConnected ,               CodBaudRate , ||      BaudRate,   CbMountedDevs,   OutputStatus
                                            
    { { TEST_DRV_UART_DEV_MATRIX_GEN2,      CDDMLC_COD_MATRIX_TYPE_TPSGEN2_662A,        5u } ,   {     0u,         0u,              FALSE }  },
    { { TEST_DRV_UART_DEV_MATRIX_GEN2,      CDDMLC_COD_MATRIX_TYPE_TPSGEN2_662A,        5u } ,   {     5u,         1u,              TRUE  }  },
    { { TEST_DRV_UART_DEV_MATRIX_GEN3,      CDDMLC_COD_MATRIX_TYPE_TPSGEN3_664,         5u } ,   {     5u,         2u,              TRUE  }  },
    { { TEST_DRV_UART_DEV_MATRIX_GEN3,      CDDMLC_COD_MATRIX_TYPE_TPSGEN3_665,        10u } ,   {     10u,        2u,              TRUE  }  },
    { { TEST_DRV_UART_DEV_MATRIX_GEN2,      CDDMLC_COD_MATRIX_TYPE_TPSGEN3_667,        10u } ,   {     10u,        0u,              TRUE  }  },
    { { TEST_DRV_UART_DEV_MATRIX_GEN2,      CDDMLC_COD_MATRIX_TYPE_TPSGENx_1,          10u } ,   {     10u,        1u,              TRUE  }  },
    { { TEST_DRV_UART_DEV_MATRIX_GEN3,      CDDMLC_COD_MATRIX_TYPE_TPSGENx_2,           5u } ,   {     5u,         3u,              TRUE  }  },
    { { TEST_DRV_UART_DEV_MATRIX_GEN2,      CDDMLC_COD_MATRIX_TYPE_NXP,                10u } ,   {     10u,        0u,              TRUE  }  },
    { { TEST_DRV_UART_DEV_MATRIX_GEN3,      CDDMLC_COD_MATRIX_TYPE_TPSGEN2_663A,        5u } ,   {     5u,         0u,              TRUE  }  },
    { { TEST_DRV_UART_DEV_MATRIX_INVALID,   CDDMLC_COD_MATRIX_TYPE_TPSGENx_2,           5u } ,   {     5u,         0u,              TRUE  }  },
  };

  //Step 1) Set pre - conditions
  uint8  ucBaudRate = 0u, ucMounted = 0u;
  uint8  ucTestDataInputCfg;
  uint8* pucTestData_BaudRate   = &ucBaudRate;
  uint8* pucTestData_MountedDev = &ucMounted;

  for (uint8 ucIdx = 0u; ucIdx < sizeof(asTestCaseData) / sizeof(asTestCaseData[0]); ucIdx++)
  {
    //Step 1) Set pre - conditions
    boolean boRetVal = FALSE;
 
    CddMlc_sCodingData.boCodingValid   = (ucIdx == 0u) ? FALSE : TRUE;
    CddMlc_sCodingData.ucMlcMatrixType = asTestCaseData[ucIdx].sInputData.ucDevTypeConnected;
    CddMlc_sCodingData.ucMlcBaudRate   = asTestCaseData[ucIdx].sInputData.ucCodBaudRate;
    ucDev_Bit = ((asTestCaseData[ucIdx].sInputData.ucDevTypeConnected == CDDMLC_COD_MATRIX_TYPE_TPSGENx_1) || 
                 (asTestCaseData[ucIdx].sInputData.ucDevTypeConnected == CDDMLC_COD_MATRIX_TYPE_TPSGENx_2)) ?  ucDev_Bit : 0u;  // simulate continuous call from Uart for mixed config

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    ucTestDataInputCfg      = asTestCaseData[ucIdx].sInputData.ucCbInputDevCfg;
    
    //Step 3) Call the FUT
    boRetVal = CddMlc_Cod_UartGetConfig(ucTestDataInputCfg, pucTestData_BaudRate, pucTestData_MountedDev);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    AL_UNITTEST_CHECK(*pucTestData_BaudRate,    asTestCaseData[ucIdx].sOutputData.ucBaudRate,       == );
    AL_UNITTEST_CHECK(*pucTestData_MountedDev,  asTestCaseData[ucIdx].sOutputData.pucCbMountedDevs, == );   // TBD : check if it is needed to be static!
    AL_UNITTEST_CHECK(boRetVal,                 asTestCaseData[ucIdx].sOutputData.boOutputStatus,   == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddMlc_EvaluateCoding
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: 
///        The function validates the coding parameters integrity, loads the coding parameters,
///        stores the local name of the device connected and decides if cycle operation should start
///
///    - Test Design Technique: DT (Decision Table)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - cycle operation management
///
///      - DT-Info:
///         - Inputs:
///            ucLoadMlcConfig    :  device matrix type to load corresponding configuration
///            eCodingStatus      :  integrity of coding parameters
///         - Expected results
///            eDevName           :  expected value returned  by the FUT, local name of the device connected
///            ucCountConnected   :  expected value returned  by the FUT, total connected chips based on coding
///            boCodingStatus     :  expected value returned  by the FUT, coding status
///            boStartCycle       :  expected value returned  by the FUT, cycle operation status
///
//-----------------------------------------------------------------------------
void Mt_CddMlc_EvaluateCoding(void)
{
  typedef struct tsTestCaseDataInput
  {
    uint8         ucLoadMlcConfig;
    tParaFct0_Cmd eCodingStatus;
  }tsTestCaseDataInput;

  typedef struct tsTestCaseDataOutput
  {
    teCddMlc_DeviceType eDevName;
    uint8               ucCountConnected;
    boolean             boCodingStatus;
    boolean             boStartCycle;
  }tsTestCaseDataOutput;

  typedef struct tsTestCaseData
  {
    tsTestCaseDataInput   sInputData;
    tsTestCaseDataOutput  sOutputData;
  }tsTestCaseData;

  tsTestCaseData asTestCaseData[] =
  {
    //                              Inputs                       ||                     Outputs                                        
    // LoadMlcConfig                       CodingStatus ,        ||      DevName,             CountConnected,   CodingStatus  , StartCycle

    { { TEST_DRV_TYPE_TPSGEN2_662A, eParaFct0_CodingDataValid   }, {eMlcDevice_DEV_TI_GEN2,   5u,               TRUE  ,         TRUE   } },
    { { TEST_DRV_DISABLED,          eParaFct0_CodingDataInvalid }, {eMlcDevice_DEV_TI_GEN2,   5u,               FALSE ,         TRUE   } },
    { { TEST_DRV_DISABLED,          eParaFct0_CodingDataValid   }, {eMlcDeviceMax,            0u,               TRUE  ,         FALSE  } },
    { { TEST_DRV_TYPE_TPSGEN3_665,  eParaFct0_CodingDataValid   }, {eMlcDeviceMax,            0u,               TRUE  ,         FALSE  } },  /* coding will not be updated, unless new cycle*/
  };

  for (uint8 ucIdx = 0u; ucIdx < sizeof(asTestCaseData) / sizeof(asTestCaseData[0]); ucIdx++)
  {
    //Step 1) Set pre - conditions
    uint8 ucInputLoadMlcConfig = asTestCaseData[ucIdx].sInputData.ucLoadMlcConfig;
    // load coding parameters specific for each test case
    memcpy(&CddMlc_pCodingArea->LmmConfig.LMM_Config_Diagnosis, &Test_Drv_CodingConfig_Variants[ucInputLoadMlcConfig], sizeof(tsNvmPara_LmmConfig_LMM_Config_Diagnosis));
    Rte_Read_CodM_CddMlc_Para_Param1.eCodingState = asTestCaseData[ucIdx].sInputData.eCodingStatus;

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT

    //Step 3) Call the FUT
    CddMlc_EvaluateCoding();

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    AL_UNITTEST_CHECK(CddMlc_eConnectedDevice,                asTestCaseData[ucIdx].sOutputData.eDevName,         == );
    AL_UNITTEST_CHECK(CddMlc_sCodingData.ucMlcConnectedDevs,  asTestCaseData[ucIdx].sOutputData.ucCountConnected, == );
    AL_UNITTEST_CHECK(CddMlc_sCodingData.boCodingValid,       asTestCaseData[ucIdx].sOutputData.boCodingStatus,   == );
    AL_UNITTEST_CHECK(CddMlc_boExecuteOperation,              asTestCaseData[ucIdx].sOutputData.boStartCycle,     == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_riCddMlc_Init
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: 
///        Check if the function can perform device initialization routine after
///        validating the coding parameters integrity and getting the name of the device connected. 
///
///    - Test Design Technique: DT (Decision Table)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - cycle operation management
///
///      - DT-Info:
///         - Inputs:
///            ucLoadMlcConfig    :  device matrix type to load corresponding configuration
///            eCodingStatus      :  integrity of coding parameters
///         - Expected results
///            eDevName           :  expected value returned  by the FUT, local name of the device connected
///            boStartCycle       :  expected value returned  by the FUT, cycle operation status
///            ReloadCoding       :  expected value returned  by the FUT, coding update status
///            boInitFctCalled    :  expected value returned  by the FUT, init function call status
///
//-----------------------------------------------------------------------------
void Mt_riCddMlc_Init(void)
{
  typedef struct tsTestCaseDataInput
  {
    uint8         ucLoadMlcConfig;
    tParaFct0_Cmd eCodingStatus;
  }tsTestCaseDataInput;

  typedef struct tsTestCaseDataOutput
  {
    teCddMlc_DeviceType eDevName;
    boolean             boStartCycle;
    boolean             boReloadCoding;
    boolean             boInitFctCalled;
  }tsTestCaseDataOutput;

  typedef struct tsTestCaseData
  {
    tsTestCaseDataInput   sInputData;
    tsTestCaseDataOutput  sOutputData;
  }tsTestCaseData;

  tsTestCaseData asTestCaseData[] =
  {
    //                              Inputs                          ||                     Outputs                                        
    // LoadMlcConfig                          CodingStatus ,        ||      DevName,            StartCycle,   ReloadCoding,  InitFctCalled
                                       
    { { TEST_DRV_TYPE_TPSGEN2_662A,    eParaFct0_CodingDataInvalid }, {eMlcDeviceMax,            FALSE,       FALSE,         FALSE } },
    { { TEST_DRV_TYPE_TPSGEN2_662A,    eParaFct0_CodingDataValid   }, {eMlcDevice_DEV_TI_GEN2,   TRUE,        FALSE,         TRUE  } },
    { { TEST_DRV_DISABLED,             eParaFct0_CodingDataInvalid }, {eMlcDeviceMax,            FALSE,       FALSE,         FALSE } },
    { { TEST_DRV_TYPE_NXP,             eParaFct0_CodingDataValid   }, {eMlcDeviceMax,            FALSE,       TRUE,          FALSE } },
    { { TEST_DRV_TYPE_TPSGEN3_665,     eParaFct0_CodingDataInvalid }, {eMlcDeviceMax,            FALSE,       FALSE,         FALSE } },
    { { TEST_DRV_TYPE_TPSGEN3_665,     eParaFct0_CodingDataValid   }, {eMlcDevice_DEV_TI_GEN3,   TRUE,        FALSE,         TRUE  } },
    { { TEST_DRV_TYPE_TPSGENx_2,       eParaFct0_CodingDataInvalid }, {eMlcDeviceMax,            FALSE,       FALSE,         FALSE } },
    { { TEST_DRV_TYPE_TPSGENx_1,       eParaFct0_CodingDataValid   }, {eMlcDevice_DEV_MIXED_TI,  TRUE,        FALSE,         TRUE  } },
  };

  for (uint8 ucIdx = 0u; ucIdx < sizeof(asTestCaseData) / sizeof(asTestCaseData[0]); ucIdx++)
  {
    //Step 1) Set pre - conditions
     RestoreStubContents();

    //start the test case independently of other tests, init runnable is called only once
    CddMlc_eConnectedDevice                 = eMlcDeviceMax;
    CddMlc_boExecuteOperation               = FALSE;
    CddMlc_boActionToExecuteAfterNewConfig  = FALSE;

    uint8 ucInputLoadMlcConfig = asTestCaseData[ucIdx].sInputData.ucLoadMlcConfig;
    // load coding parameters specific for each test case
    memcpy(&CddMlc_pCodingArea->LmmConfig.LMM_Config_Diagnosis, &Test_Drv_CodingConfig_Variants[ucInputLoadMlcConfig], sizeof(tsNvmPara_LmmConfig_LMM_Config_Diagnosis));
    Rte_Read_CodM_CddMlc_Para_Param1.eCodingState = asTestCaseData[ucIdx].sInputData.eCodingStatus;

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    //Step 3) Call the FUT
    riCddMlc_Init();

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    AL_UNITTEST_CHECK(CddMlc_eConnectedDevice,                  asTestCaseData[ucIdx].sOutputData.eDevName,         == );
    AL_UNITTEST_CHECK(CddMlc_boExecuteOperation,                asTestCaseData[ucIdx].sOutputData.boStartCycle,     == );
    AL_UNITTEST_CHECK(CddMlc_boActionToExecuteAfterNewConfig,   asTestCaseData[ucIdx].sOutputData.boReloadCoding,   == );
    AL_UNITTEST_CHECK(Test_Drv_IsFctCalled(),                   asTestCaseData[ucIdx].sOutputData.boInitFctCalled,  == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_reCddMlc_NewTarget
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: 
///        Check usage of received duty cycle over RTE
///
///    - Test Design Technique: - ET (Exploratory Testing) 
///
///    - Preconditions: aunTestPWM_1_1024_Input containing duty cyle values
///                     for each pixel
///
///    - Expected test results: 
///        - duty cycle is updated 
///
//-----------------------------------------------------------------------------
void Mt_reCddMlc_NewTarget(void)
{
  //Step 1) Set pre - conditions
  uint16 aunTestPWM_1_1024_Input[7][16] = TEST_DRV_PWM_VALS_7CHIPS_16PXL;

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Test_Drv_SetTgtMtxPixels(aunTestPWM_1_1024_Input);

  //Step 3) Call the FUT
  reCddMlc_NewTarget();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(Test_Drv_GetDutyCycle(TEST_Chip0, 6), 204u,  == );
  AL_UNITTEST_CHECK(Test_Drv_GetDutyCycle(TEST_Chip3, 6), 0u,    == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddMlc_CheckReinitMatrix
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: 
///        Check reception of reinitialization command over RTE
///
///    - Test Design Technique: - ET (Exploratory Testing) 
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - reset command is updated
///
//-----------------------------------------------------------------------------
void Mt_CddMlc_CheckReinitMatrix(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Test_Drv_SetReinitMatrix(TRUE);
  Rte_Write_CtrlPxl_CddMlc_ReinitMatrix_Param1 = TRUE;

  //Step 3) Call the FUT
  CddMlc_CheckReinitMatrix();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(Test_Drv_GetReinitMatrix(),                   TRUE, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_CddMlc_ReinitMatrix_Param1, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_rpCddMlc_Cycle0
///
/// \Functional Safety: FuSa Relevant ASIL-B
///
/// \Test Case Description
///    - Test subject: 
///        Test the cyclic runnable for valid and Invalid Coding Data.
///        Check that for invalid coding the driver does not execute the cyclic routine.
///        General: in case the coding is invalid, the system shall be
///        running with no issue, but not functional (meaning no light
///        shall be controlled and last data for errors detected must be kept)
///
///    - Test Design Technique: DT (Decision Table),
///                             Requirement based test
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - cycle operation management
///
///      - DT-Info:
///         - Inputs:
///            ucLoadMlcConfig    :  device matrix type to load corresponding configuration
///            eCodingStatus      :  integrity of coding parameters
///            ucChipId           :  chip index under test
///            sSensorData        :  sensor data collected from driver
///            unChipPxlFault     :  pixel fault data collected from driver
///            boChipCommFault    :  device comm. error data collected from driver
///         - Expected results
///            eDevName           :  expected value returned  by the FUT, local name of the device connected
///            boStartCycle       :  expected value returned  by the FUT, cycle operation status
///            sAdcResult         :  expected value returned  by the FUT, remapped ADC values over RTE (for chip under test)
///            unBitPxlFault      :  expected value returned  by the FUT, remapped pixel fault values over RTE (for chip under test)
///            ucBitCommFault     :  expected value returned  by the FUT, remapped communication status  over RTE (for chip under test)
///
//-----------------------------------------------------------------------------
void Mt_rpCddMlc_Cycle0(void)
{
  typedef struct tsTestCaseDataInput
  {
    uint8                ucLoadMlcConfig;
    tParaFct0_Cmd        eCodingStatus;
    uint8                ucChipId;
    tsCddMlc_SensorData  sSensorData;
    uint16               unChipPxlFault;
    boolean              boChipCommFault;
  }tsTestCaseDataInput;

  typedef struct tsTestCaseDataOutput
  {
    teCddMlc_DeviceType       eDevName;
    boolean                   boStartCycle;
    tsRte_CddMlc_AdcResult    sAdcResult;
    uint16                    unBitPxlFault;
    uint8                     ucBitCommFault;
  }tsTestCaseDataOutput;

  typedef struct tsTestCaseData
  {
    tsTestCaseDataInput   sInputData;
    tsTestCaseDataOutput  sOutputData;
  }tsTestCaseData;

  tsTestCaseData asTestCaseData[] =
  {
    //                                                                    Inputs                                                        ||                                              Outputs                                        
    // LoadMlcConfig                        CodingStatus ,         ChipId,          SensorData,                     ChipPxlFault, ChipCommFault  ||   DevName,            StartCycle,   AdcSigQlty,       BitPxlFault,  BitCommFault
                                                                            
    { { TEST_DRV_TYPE_TPSGEN2_662A,  eParaFct0_CodingDataInvalid,  TEST_Chip1,     {0u,  0u, SENSOR_QLTY_INVALID},    0x0FFFu,       TRUE        }, {eMlcDeviceMax,            FALSE,  {0u,  0u,  CDD_MLC_QLTY_INVALID},  0x00u,       0x00u } },
    { { TEST_DRV_TYPE_TPSGEN2_662A,  eParaFct0_CodingDataValid,    TEST_Chip4,     {0u,  0u, CDD_MLC_QLTY_SNA   },    0x0FFFu,       TRUE        }, {eMlcDevice_DEV_TI_GEN2,   TRUE,   {0u,  0u,  CDD_MLC_QLTY_SNA    },  0x0FFFu,     0x10u } },
    { { TEST_DRV_DISABLED,           eParaFct0_CodingDataInvalid,  TEST_Chip4,     {0u,  0u, SENSOR_QLTY_INVALID},    0x000Fu,       FALSE       }, {eMlcDevice_DEV_TI_GEN2,   TRUE,   {0u,  0u,  CDD_MLC_QLTY_INVALID},  0x00u,       0x00u } },
    { { TEST_DRV_TYPE_TPSGEN3_665,   eParaFct0_CodingDataValid,    TEST_Chip6,     {220u,1u, SENSOR_QLTY_VALID  },    0x01FFu,       TRUE        }, {eMlcDevice_DEV_TI_GEN3,   TRUE,   {220u,1u,  CDD_MLC_QLTY_VALID  },  0x01FFu,     0x40u } },
    { { TEST_DRV_TYPE_TPSGENx_2,     eParaFct0_CodingDataInvalid,  TEST_Chip1,     {0u,  0u, SENSOR_QLTY_INVALID},    0x01FFu,       FALSE       }, {eMlcDevice_DEV_TI_GEN3,   TRUE,   {0u,  0u,  CDD_MLC_QLTY_INVALID},  0x01FFu,     0x00u } },
    { { TEST_DRV_TYPE_TPSGENx_1,     eParaFct0_CodingDataValid,    TEST_Chip4,     {120u,4u, SENSOR_QLTY_VALID  },    0x001Fu,       TRUE        }, {eMlcDevice_DEV_MIXED_TI,  TRUE,   {120u,4u,  CDD_MLC_QLTY_VALID  },  0x001Fu,     0x10u } },
    { { TEST_DRV_TYPE_TPSGENx_2,     eParaFct0_CodingDataInvalid,  TEST_Chip1,     {0u, 55u, SENSOR_QLTY_INVALID},    0x01FFu,       FALSE       }, {eMlcDevice_DEV_MIXED_TI,  TRUE,   {0u,  0u,  CDD_MLC_QLTY_INVALID},  0x00u,       0x00u } },
    { { TEST_DRV_TYPE_NXP,           eParaFct0_CodingDataValid,    TEST_Chip0,     {0u,  0u, SENSOR_QLTY_INVALID},    0x01FFu,       FALSE       }, {eMlcDeviceMax,            FALSE,   {0u,  0u,  CDD_MLC_QLTY_INVALID},  0x00u,       0x00u } },

  };

  //Step 1) Set pre - conditions   - set once, to start the test case independently, but also to simulate cyclic behaviour
  CddMlc_eConnectedDevice                 = eMlcDeviceMax;
  CddMlc_boExecuteOperation               = FALSE;
  CddMlc_boActionToExecuteAfterNewConfig  = FALSE;
  boCodingPrevStatus                      = FALSE;

  for (uint8 ucIdx = 0u; ucIdx < sizeof(asTestCaseData) / sizeof(asTestCaseData[0]); ucIdx++)
  {
    //Step 1) Set pre - conditions
    RestoreStubContents();

    uint8 ucChipIdx             = asTestCaseData[ucIdx].sInputData.ucChipId;
    uint8 ucInputLoadMlcConfig  = asTestCaseData[ucIdx].sInputData.ucLoadMlcConfig;
    // load coding parameters specific for each test case
    memcpy(&CddMlc_pCodingArea->LmmConfig.LMM_Config_Diagnosis, &Test_Drv_CodingConfig_Variants[ucInputLoadMlcConfig], sizeof(tsNvmPara_LmmConfig_LMM_Config_Diagnosis));

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    Test_Drv_SetVccxEn(TRUE);
    Rte_Read_IoHwAbUser_VccxLineState_Param1 = 0u;
    Rte_Read_CodM_CddMlc_Para_Param1.eCodingState             = asTestCaseData[ucIdx].sInputData.eCodingStatus;

    if (   ( (ucInputLoadMlcConfig == TEST_DRV_TYPE_TPSGEN2_662A) || (ucInputLoadMlcConfig == TEST_DRV_TYPE_TPSGEN2_663A) )
        || ( (ucInputLoadMlcConfig == TEST_DRV_TYPE_TPSGENx_1)    || (ucInputLoadMlcConfig == TEST_DRV_TYPE_TPSGENx_2)  ) )
    {
       Test_Drv_SetSensorDataGEN2(ucChipIdx, asTestCaseData[ucIdx].sInputData.sSensorData);
       Test_Drv_SetShortToGndGEN2(ucChipIdx, asTestCaseData[ucIdx].sInputData.unChipPxlFault);
       Test_Drv_SetComFaultGEN2  (ucChipIdx, asTestCaseData[ucIdx].sInputData.boChipCommFault);
    }

    if (   ( (ucInputLoadMlcConfig == TEST_DRV_TYPE_TPSGEN3_664) || (ucInputLoadMlcConfig == TEST_DRV_TYPE_TPSGEN3_665) || (ucInputLoadMlcConfig == TEST_DRV_TYPE_TPSGEN3_667))
        || ( (ucInputLoadMlcConfig == TEST_DRV_TYPE_TPSGENx_1)   || (ucInputLoadMlcConfig == TEST_DRV_TYPE_TPSGENx_2)   ))
    {
       Test_Drv_SetSensorDataGEN3(ucChipIdx, asTestCaseData[ucIdx].sInputData.sSensorData);
       Test_Drv_SetShortToGndGEN3(ucChipIdx, asTestCaseData[ucIdx].sInputData.unChipPxlFault);
       Test_Drv_SetComFaultGEN3  (ucChipIdx, asTestCaseData[ucIdx].sInputData.boChipCommFault);
    }

    //Step 3) Call the FUT
    if (ucIdx == 1u)  /* get in the cycle operation, HSS stabilized   -> needs only once, following test cases will be in cycle operation*/
    { 
      rpCddMlc_Cycle0();
      rpCddMlc_Cycle0();
      rpCddMlc_Cycle0();
      rpCddMlc_Cycle0();
      rpCddMlc_Cycle0();
      rpCddMlc_Cycle0();
    }
    else
    {
      rpCddMlc_Cycle0();
    }

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    AL_UNITTEST_CHECK(CddMlc_eConnectedDevice,                                                    asTestCaseData[ucIdx].sOutputData.eDevName,               == );
    AL_UNITTEST_CHECK(CddMlc_boExecuteOperation,                                                  asTestCaseData[ucIdx].sOutputData.boStartCycle,           == );
    AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_CddMlc_AdcResult_aVal_Param1[ucChipIdx].eQlty,            asTestCaseData[ucIdx].sOutputData.sAdcResult.eQlty,       == );
    AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_CddMlc_AdcResult_aVal_Param1[ucChipIdx].ucADC1Value,      asTestCaseData[ucIdx].sOutputData.sAdcResult.ucADC1Value, == );
    AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_CddMlc_AdcResult_aVal_Param1[ucChipIdx].ucADC2Value,      asTestCaseData[ucIdx].sOutputData.sAdcResult.ucADC2Value, == );
    AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_CddMlc_LedStatus_aVal_Param1[ucChipIdx].unLedFault,       asTestCaseData[ucIdx].sOutputData.unBitPxlFault,          == );
    AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_CddMlc_ComStatus_sVal_Param1.ucMlcStatus,                 asTestCaseData[ucIdx].sOutputData.ucBitCommFault,         == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddMlc_UpdateRTE_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: 
///        Verify correct processing over RTE when no communication faults 
///        are present, and sensor data is entirely valid, reporting of initialization
///        status completed
///
///    - Test Design Technique: - ET (Exploratory Testing) 
///
///    - Preconditions: 
///                     boInitStatus equals TRUE, indicating full init of chips
///
///    - Expected test results: 
///        -  no communication faults, all sensor data quality = CDD_MLC_QLTY_VALID
///        -  The corresponding RTE port for init status is set to CddMlc_SystemMode_CfgLeds
///
//-----------------------------------------------------------------------------
void Mt_CddMlc_UpdateRTE_TestCase1(void) 
{
  //Step 1) Set pre - conditions
  tsCddMlcStatus sTestStatus = { 0 }; 

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  for (uint8 ucDevId = 0; ucDevId < CDDMLC_CFG_MAX_CHIPS; ucDevId++) 
  {
    sTestStatus.aboComFault [ucDevId]       = FALSE;
    sTestStatus.asSensorData[ucDevId].eQlty = SENSOR_QLTY_VALID;
  }
  sTestStatus.ucPowerOnReset = 0; // Assume power-on reset status is 0 for no reset
  sTestStatus.boInitStatus   = TRUE;

   //Step 3) Call the FUT
  CddMlc_UpdateRTE(sTestStatus);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  // Expect no communication faults, all sensor data quality = CDD_MLC_QLTY_VALID
  for (uint8 ucDevId = 0; ucDevId < CDDMLC_CFG_MAX_CHIPS; ucDevId++)
  {
    AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_CddMlc_ComStatus_sVal_Param1.ucMlcStatus,                    0u, == );
    AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_CddMlc_ComStatus_sVal_Param1.ucPowerCycle,                   0u, == );
    AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_CddMlc_AdcResult_aVal_Param1[ucDevId].eQlty, CDD_MLC_QLTY_VALID, == );
  }
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_CddMlc_SystemMode_eVal_Param1,          CddMlc_SystemMode_CfgLeds, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddMlc_UpdateRTE_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: 
///       Ensure handling of communication faults correctly
///
///    - Test Design Technique: - ET (Exploratory Testing) 
///
///    - Preconditions: aboComFault contains TRUE for at least one device
///
///    - Expected test results: 
///        -  The corresponding bit in RTE ucMlcStatus field is set for devices with a communication fault
///
//-----------------------------------------------------------------------------
void Mt_CddMlc_UpdateRTE_TestCase2(void) 
{
  //Step 1) Set pre - conditions
  tsCddMlcStatus sTestStatus = { 0 }; 

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  sTestStatus.aboComFault [TEST_Chip0]       = TRUE;
  sTestStatus.aboComFault [TEST_Chip3]       = TRUE;
  sTestStatus.aboComFault [TEST_Chip5]       = TRUE;

   //Step 3) Call the FUT
  CddMlc_UpdateRTE(sTestStatus);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
   AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_CddMlc_ComStatus_sVal_Param1.ucMlcStatus,       0b00101001, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddMlc_UpdateRTE_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: 
///       Test that each possible sensor quality status is correctly remapped
///
///    - Test Design Technique: - ET (Exploratory Testing) 
///
///    - Preconditions: asSensorData[ucDevId].eQlty contains various values
///                     across the range of devices
///
///    - Expected test results: 
///        -  Sensor data quality is remapped and reflected over ADC RTE eQlty field
///
//-----------------------------------------------------------------------------
void Mt_CddMlc_UpdateRTE_TestCase3(void) 
{
  //Step 1) Set pre - conditions
  tsCddMlcStatus sTestStatus = { 0 }; 

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  sTestStatus.asSensorData[TEST_Chip0].eQlty = SENSOR_QLTY_VALID;
  sTestStatus.asSensorData[TEST_Chip3].eQlty = SENSOR_QLTY_INVALID;
  sTestStatus.asSensorData[TEST_Chip5].eQlty = SENSOR_QLTY_SNA;
  sTestStatus.asSensorData[TEST_Chip6].eQlty = 255u;

   //Step 3) Call the FUT
  CddMlc_UpdateRTE(sTestStatus);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_CddMlc_AdcResult_aVal_Param1[TEST_Chip0].eQlty,  CDD_MLC_QLTY_VALID,    == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_CddMlc_AdcResult_aVal_Param1[TEST_Chip3].eQlty,  CDD_MLC_QLTY_INVALID,  == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_CddMlc_AdcResult_aVal_Param1[TEST_Chip5].eQlty,  CDD_MLC_QLTY_SNA,      == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_CddMlc_AdcResult_aVal_Param1[TEST_Chip6].eQlty,  CDD_MLC_QLTY_SNA,      == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddMlc_UpdateRTE_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: 
///       Verify that Power On Reset (PWR) status is accurately saved
///
///    - Test Design Technique: - ET (Exploratory Testing) 
///
///    - Preconditions: sMlcComStatus.ucPowerOnReset is set to a nonzero value indicating a power cycle
///                     boInitStatus equals FALSE, indicating a power cycle
///
///    - Expected test results: 
///        -  PWR status is mirrored over RTE
///        -  The corresponding RTE port for init status is set to CddMlc_SystemMode_Powerup, indicating a reset
///
//-----------------------------------------------------------------------------
void Mt_CddMlc_UpdateRTE_TestCase4(void) 
{
  //Step 1) Set pre - conditions
  tsCddMlcStatus sTestStatus = { 0 }; 

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  sTestStatus.ucPowerOnReset = 0b00101001;  // chip 0, 3 and 5 are in reset
  sTestStatus.boInitStatus   = FALSE;

   //Step 3) Call the FUT
  CddMlc_UpdateRTE(sTestStatus);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
   AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_CddMlc_ComStatus_sVal_Param1.ucPowerCycle,   0b00101001u, == );
   AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_CddMlc_SystemMode_eVal_Param1, CddMlc_SystemMode_Powerup, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddMlc_UpdateRTE
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Verify correct processing over RTE of device faults
///
///    - Test Design Technique: - ET (Exploratory Testing) 
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddMlc_UpdateRTE(void)
{
  Mt_CddMlc_UpdateRTE_TestCase1();
  Mt_CddMlc_UpdateRTE_TestCase2();
  Mt_CddMlc_UpdateRTE_TestCase3();
  Mt_CddMlc_UpdateRTE_TestCase4();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_reCddMlcEE_CbkInit
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: 
///       Verify that the runnable event triggers the I2C state machine initialization
///       process and sets the callbacks events of the embedded EEPROM from Mlc
///
///    - Test Design Technique: - ET (Exploratory Testing) 
///
///    - Preconditions: callback functions events are set
///
///    - Expected test results: 
///        -  commands passed to I2C init functions
///
//-----------------------------------------------------------------------------
void Mt_reCddMlcEE_CbkInit(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Rte_Read_CtrlPxl_MatrixEE_CbkInitData_Param1.pfnMatrixEECbkSuccess  = &Test_Drv_I2C_CallbackFunction_Stub;
  Rte_Read_CtrlPxl_MatrixEE_CbkInitData_Param1.pfnMatrixEECbkFail     = &Test_Drv_I2C_CallbackFunction_Stub;
  Rte_Read_CtrlPxl_MatrixEE_CbkInitData_HitCount = 0u;

  //Step 3) Call the FUT
  reCddMlcEE_CbkInit();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(Test_Drv_I2C_GetStartInit().pfnInitSuccessClbk, Test_Drv_I2C_CallbackFunction_Stub, == )
  AL_UNITTEST_CHECK(Test_Drv_I2C_GetStartInit().pfnInitFailedClbk,  Test_Drv_I2C_CallbackFunction_Stub, == )
  AL_UNITTEST_CHECK(Rte_Read_CtrlPxl_MatrixEE_CbkInitData_HitCount,                                 1u, == )
}

//-----------------------------------------------------------------------------
/// \Test Case : reCddMlcEE_Read
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: 
///       Verify that the runnable event triggers the I2C state machine read
///       process and sets the callbacks events of the embedded EEPROM from Mlc
///
///    - Test Design Technique: - ET (Exploratory Testing) 
///
///    - Preconditions: callback functions events are set
///
///    - Expected test results: 
///        -  commands passed to I2C read functions
///
//-----------------------------------------------------------------------------
void Mt_reCddMlcEE_Read(void)
{
  //Step 1) Set pre - conditions
  uint8 Mt_DataTest[256] = { 0xFFu };

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Rte_Read_CtrlPxl_MatrixEE_DataRead_Param1.sMatrixEE0CbkFn.pfnMatrixEECbkSuccess  = &Test_Drv_I2C_CallbackFunction_Stub;
  Rte_Read_CtrlPxl_MatrixEE_DataRead_Param1.sMatrixEE0CbkFn.pfnMatrixEECbkFail     = &Test_Drv_I2C_CallbackFunction_Stub;
  Rte_Read_CtrlPxl_MatrixEE_DataRead_Param1.unMatrixEEStartAdd                     = TEST_DRV_EEPROM_START_ADDR(100u);
  Rte_Read_CtrlPxl_MatrixEE_DataRead_Param1.unMatrixEELength                       = TEST_DRV_EEPROM_SIZE;
  Rte_Read_CtrlPxl_MatrixEE_DataRead_Param1.pucMatrixEEbuffer                      = &Mt_DataTest[0];
  Rte_Read_CtrlPxl_MatrixEE_DataRead_HitCount = 0u;

  //Step 3) Call the FUT
  reCddMlcEE_Read();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(Test_Drv_I2C_GetReadEeprom().pfnReadSuccessClbk, Test_Drv_I2C_CallbackFunction_Stub, == )
  AL_UNITTEST_CHECK(Test_Drv_I2C_GetReadEeprom().pfnReadFailedClbk,  Test_Drv_I2C_CallbackFunction_Stub, == )
  AL_UNITTEST_CHECK(Test_Drv_I2C_GetReadEeprom().unReadStartAddress,                               100u, == )
  AL_UNITTEST_CHECK(Test_Drv_I2C_GetReadEeprom().unReadLength,                     TEST_DRV_EEPROM_SIZE, == )
  AL_UNITTEST_CHECK(Rte_Read_CtrlPxl_MatrixEE_DataRead_HitCount,                                     1u, == )
}

//-----------------------------------------------------------------------------
/// \Test Case : reCddMlcEE_Write
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: 
///       Verify that the runnable event triggers the I2C state machine write
///       process and sets the callbacks events of the embedded EEPROM from Mlc
///
///    - Test Design Technique: - ET (Exploratory Testing) 
///
///    - Preconditions: callback functions events are set
///
///    - Expected test results: 
///        -  commands passed to I2C write functions
///
//-----------------------------------------------------------------------------
void Mt_reCddMlcEE_Write(void)
{
  //Step 1) Set pre - conditions
  uint8 Mt_DataTest[256] = { 0xFFu };

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Rte_Read_CtrlPxl_MatrixEE_DataWrite_Param1.sMatrixEE0CbkFn.pfnMatrixEECbkSuccess  = &Test_Drv_I2C_CallbackFunction_Stub;
  Rte_Read_CtrlPxl_MatrixEE_DataWrite_Param1.sMatrixEE0CbkFn.pfnMatrixEECbkFail     = &Test_Drv_I2C_CallbackFunction_Stub;
  Rte_Read_CtrlPxl_MatrixEE_DataWrite_Param1.unMatrixEEStartAdd                     = TEST_DRV_EEPROM_START_ADDR(0u);
  Rte_Read_CtrlPxl_MatrixEE_DataWrite_Param1.unMatrixEELength                       = TEST_DRV_EEPROM_SIZE;
  Rte_Read_CtrlPxl_MatrixEE_DataWrite_Param1.pucMatrixEEbuffer                      = &Mt_DataTest[0];
  Rte_Read_CtrlPxl_MatrixEE_DataWrite_HitCount = 0u;

  //Step 3) Call the FUT
  reCddMlcEE_Write();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(Test_Drv_I2C_GetWriteEeprom().pfnWriteSuccessClbk, Test_Drv_I2C_CallbackFunction_Stub, == )
  AL_UNITTEST_CHECK(Test_Drv_I2C_GetWriteEeprom().pfnWriteFailedClbk,  Test_Drv_I2C_CallbackFunction_Stub, == )
  AL_UNITTEST_CHECK(Test_Drv_I2C_GetWriteEeprom().unWriteStartAddress,                                 0u, == )
  AL_UNITTEST_CHECK(Test_Drv_I2C_GetWriteEeprom().unWriteLength,                     TEST_DRV_EEPROM_SIZE, == )
  AL_UNITTEST_CHECK(*Test_Drv_I2C_GetWriteEeprom().pucWriteData,                                    0xFFu, == )
  AL_UNITTEST_CHECK(Rte_Read_CtrlPxl_MatrixEE_DataWrite_HitCount,                                      1u, == )
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddMlc_GetEEPROMAddressId
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: 
///        Test that the function returns the device matrix id to which eeprom is attached
///
///    - Test Design Technique: DT (Decision Table)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - cycle operation management
///
///      - DT-Info:
///         - Inputs:
///            ucInputMtxType     :  device matrix type connected
///         - Expected results
///            ucOutputMtxEEId    :  expected value returned  by the FUT, device matrix id to which eeprom is attached
///
//-----------------------------------------------------------------------------
void Mt_CddMlc_GetEEPROMAddressId(void)
{
  typedef struct tsTestCaseData
  {
    uint8 ucInputMtxType;
    uint8 ucOutputMtxEEId;
  }tsTestCaseData;

  tsTestCaseData asTestCaseData[] =
  {       /*  InputMtxType                 ||     OutputMtxEEId                */
    { CDDMLC_COD_MATRIX_TYPE_DISABLED,      CDDMLC_COD_DEV_ADDR_NOT_CONNECTED },
    { CDDMLC_COD_MATRIX_TYPE_TPSGEN2_662A,  0x04u                             }
  };

  for (uint8 ucIdx = 0u; ucIdx < sizeof(asTestCaseData) / sizeof(asTestCaseData[0]); ucIdx++)
  {
    //Step 1) Set pre - conditions
    uint8 ucRetVal = 0u;

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    CddMlc_sCodingData.ucMlcMatrixType = asTestCaseData[ucIdx].ucInputMtxType;

    //Step 3) Call the FUT
    ucRetVal = CddMlc_GetEEPROMAddressId();

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    AL_UNITTEST_CHECK(ucRetVal, asTestCaseData[ucIdx].ucOutputMtxEEId, == )
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddMlc_DevInit
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: 
///        Test that the function calls the correct initialization routine based on
///        the connected device type
///
///    - Test Design Technique: DT (Decision Table)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - init operation management
///
///      - DT-Info:
///         - Inputs:
///            eDevName           :  device matrix type connected
///         - Expected results
///            boInitFctCalled    :  expected value returned  by the FUT, init function call status
///            pfnDevInitFunct    :  expected value returned  by the FUT, init function
///
//-----------------------------------------------------------------------------
void Mt_CddMlc_DevInit(void)
{
  typedef struct tsTestCaseData
  {
    teCddMlc_DeviceType eDevName;
    boolean             boInitFctCalled;
    pMlcDevInitFunc     pfnDevInitFunct;
  }tsTestCaseData;

  tsTestCaseData asTestCaseData[] =
  {
    //   DevName,               InitFctCalled                                   
    { eMlcDeviceMax,            FALSE,         NULL_PTR         },
    { eMlcDevice_DEV_TI_GEN2,   TRUE,          CddTpsGen2_Init  },
    { eMlcDevice_DEV_TI_GEN3,   TRUE,          CddTpsGen3_Init  },
    { eMlcDevice_DEV_MIXED_TI,  TRUE,          CddTpsMixed_Init },
  };

  for (uint8 ucIdx = 0u; ucIdx < sizeof(asTestCaseData) / sizeof(asTestCaseData[0]); ucIdx++)
  {
    //Step 1) Set pre - conditions
    RestoreStubContents();

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    uint8 eDeviceId = asTestCaseData[ucIdx].eDevName;

    //Step 3) Call the FUT
    CddMlc_DevInit(eDeviceId);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    AL_UNITTEST_CHECK(Test_Drv_IsFctCalled(),                   asTestCaseData[ucIdx].boInitFctCalled,  == );
    AL_UNITTEST_CHECK(CddMlc_sDeviceAPIs[eDeviceId].init,       asTestCaseData[ucIdx].pfnDevInitFunct,  == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddMlc_DevCyclic
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: 
///        Test that the function calls the correct cyclic routine based on
///        the connected device type
///
///    - Test Design Technique: DT (Decision Table)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - cycle operation management
///
///      - DT-Info:
///         - Inputs:
///            eDevName             :  device matrix type connected
///         - Expected results
///            boCyclicFctCalled    :  expected value returned  by the FUT, cyclic function call status
///            pfnDevCyclicFunct    :  expected value returned  by the FUT, cyclic function
///
//-----------------------------------------------------------------------------
void Mt_CddMlc_DevCyclic(void)
{
  typedef struct tsTestCaseData
  {
    teCddMlc_DeviceType eDevName;
    boolean             boCyclicFctCalled;
    pMlcDevInitFunc     pfnDevCyclicFunct;
  }tsTestCaseData;

  tsTestCaseData asTestCaseData[] =
  {
    //   DevName,               CyclicFctCalled                                   
    { eMlcDeviceMax,            FALSE,         NULL_PTR          },
    { eMlcDevice_DEV_TI_GEN2,   TRUE,          CddTpsGen2_Cycle  },
    { eMlcDevice_DEV_TI_GEN3,   TRUE,          CddTpsGen3_Cycle  },
    { eMlcDevice_DEV_MIXED_TI,  TRUE,          CddTpsMixed_Cycle },
  };

  for (uint8 ucIdx = 0u; ucIdx < sizeof(asTestCaseData) / sizeof(asTestCaseData[0]); ucIdx++)
  {
    //Step 1) Set pre - conditions
    RestoreStubContents();

     //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    uint8 eDeviceId = asTestCaseData[ucIdx].eDevName;

    //Step 3) Call the FUT
    CddMlc_DevCyclic(eDeviceId);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    AL_UNITTEST_CHECK(Test_Drv_IsFctCalled(),                   asTestCaseData[ucIdx].boCyclicFctCalled,  == );
    AL_UNITTEST_CHECK(CddMlc_sDeviceAPIs[eDeviceId].cyclic,     asTestCaseData[ucIdx].pfnDevCyclicFunct,  == );
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
void ALUnitTest_AddTests_Adapter(void)
{
  ALUnitTest_AddFunction("Mt_CddMlc_Read_CodingPara",         Mt_CddMlc_Read_CodingPara);
  ALUnitTest_AddFunction("Mt_CddMlc_ParaFct0",                Mt_CddMlc_ParaFct0);
  ALUnitTest_AddFunction("Mt_CddMlc_CodingDataValidation",    Mt_CddMlc_CodingDataValidation);
  ALUnitTest_AddFunction("Mt_CddMlc_DeviceCfg",               Mt_CddMlc_DeviceCfg);
  ALUnitTest_AddFunction("Mt_CddMlc_Data_LmmConfig",          Mt_CddMlc_Data_LmmConfig);
  ALUnitTest_AddFunction("Mt_CddMlc_Cod_UartGetConfig",       Mt_CddMlc_Cod_UartGetConfig);
  ALUnitTest_AddFunction("Mt_CddMlc_EvaluateCoding",          Mt_CddMlc_EvaluateCoding);
  ALUnitTest_AddFunction("Mt_riCddMlc_Init",                  Mt_riCddMlc_Init);
  ALUnitTest_AddFunction("Mt_reCddMlc_NewTarget",             Mt_reCddMlc_NewTarget);
  ALUnitTest_AddFunction("Mt_CddMlc_CheckReinitMatrix",       Mt_CddMlc_CheckReinitMatrix);
  ALUnitTest_AddFunction("Mt_rpCddMlc_Cycle0",                Mt_rpCddMlc_Cycle0);
  ALUnitTest_AddFunction("Mt_CddMlc_UpdateRTE",               Mt_CddMlc_UpdateRTE);
  ALUnitTest_AddFunction("Mt_reCddMlcEE_CbkInit",             Mt_reCddMlcEE_CbkInit);
  ALUnitTest_AddFunction("Mt_reCddMlcEE_Read",                Mt_reCddMlcEE_Read);
  ALUnitTest_AddFunction("Mt_reCddMlcEE_Write",               Mt_reCddMlcEE_Write);
  ALUnitTest_AddFunction("Mt_CddMlc_GetEEPROMAddressId",      Mt_CddMlc_GetEEPROMAddressId);
  ALUnitTest_AddFunction("Mt_CddMlc_DevInit",                 Mt_CddMlc_DevInit);
  ALUnitTest_AddFunction("Mt_CddMlc_DevCyclic",               Mt_CddMlc_DevCyclic);
}


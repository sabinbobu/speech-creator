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
/// \brief  Unit test of generic code in CddMlc module
///
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
//-----------------------------------------------------------------------------

// Standard unit test header
#include <ALUnitTest_UserInterface.h>

// Stub headers
#include <Test_Ext.h>
#include "Test_Stubs.h"

// Headers of the unit test Module
#include <Test.h>
#include <Test_Adapter.h>

//-----------------------------------------------------------------------------
// Test implementation
//-----------------------------------------------------------------------------

static void InitConditions(void)
{
  RestoreStubContents();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddMlc_CheckPowerUp_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: 
///       Verify that MLC is not ready to operate if power guard is not yet satisfied
///
///    - Test Design Technique: - ET (Exploratory Testing) 
///
///    - Preconditions: MLC is powered, but power is not stable
///
///    - Expected test results: 
///        - The function should return FALSE, indicating power is not yet considered stable for MLC operations
///
//-----------------------------------------------------------------------------
void Mt_CddMlc_CheckPowerUp_TestCase1(void)
{
  //Step 1) Set pre - conditions
  boolean boRet         = FALSE;
  CddMlc_ucPowerUpGuard = 0u;
  Rte_Read_IoHwAbUser_VccxLineState_Param1 = 0u;

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Test_Drv_SetVccxEn(TRUE);

  //Step 3) Call the FUT
  for (int i = 0; i < CDDMLC_POWERUP_CYCLE_GUARD; ++i)
  {
    boRet = CddMlc_CheckPowerUp();
  }

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(boRet, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddMlc_CheckPowerUp_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: 
///       Verify that MLC is ready to operate when the power-up delay is reached
///
///    - Test Design Technique: - ET (Exploratory Testing) 
///
///    - Preconditions: MLC is powered, power-up delay exceeded
///
///    - Expected test results: 
///        - The function should return TRUE, indicating power is stable for MLC operations
///
//-----------------------------------------------------------------------------
void Mt_CddMlc_CheckPowerUp_TestCase2(void)
{
  //Step 1) Set pre - conditions
  boolean boRet         = FALSE;

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Test_Drv_SetVccxEn(TRUE);

  //Step 3) Call the FUT
  boRet = CddMlc_CheckPowerUp();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(boRet, TRUE,                 == );
  AL_UNITTEST_CHECK(CddMlc_boMlcPoweredUP, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddMlc_CheckPowerUp_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: 
///       Verify that power status is reset upon loss of power
///
///    - Test Design Technique: - ET (Exploratory Testing) 
///
///    - Preconditions: after being powered, a power loss occurs
///
///    - Expected test results: 
///        - The function should return FALSE, and power up delay should be reset
///
//-----------------------------------------------------------------------------
void Mt_CddMlc_CheckPowerUp_TestCase3(void)
{
  //Step 1) Set pre - conditions
  boolean boRet         = FALSE;

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Test_Drv_SetVccxEn(FALSE);

  //Step 3) Call the FUT
  boRet = CddMlc_CheckPowerUp();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(boRet, FALSE,                 == );
  AL_UNITTEST_CHECK(CddMlc_ucPowerUpGuard, 0u,    == );
  AL_UNITTEST_CHECK(CddMlc_boMlcPoweredUP, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddMlc_CheckPowerUp
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:   Verify if power is stable for the MLC to operate
///
///    - Test Design Technique: - ET (Exploratory Testing) 
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddMlc_CheckPowerUp(void)
{
  Mt_CddMlc_CheckPowerUp_TestCase1();
  Mt_CddMlc_CheckPowerUp_TestCase2();
  Mt_CddMlc_CheckPowerUp_TestCase3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddMlc_CheckPowerUp_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: 
///       Test variations of power status
///
///    - Test Design Technique: - ET (Exploratory Testing) 
///
///    - Preconditions: CddMlc_boMlcPoweredUP contains various values
///
///    - Expected test results: 
///        - The function should return the reflected value
///
//-----------------------------------------------------------------------------
void Mt_CddMlc_IsMlcPowered(void)
{
 //Step 1) Set pre - conditions
  boolean boRet = FALSE;
 //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddMlc_boMlcPoweredUP = TRUE;

 //Step 3) Call the FUT
  boRet = CddMlc_IsMlcPowered();

 //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(boRet, TRUE, == );

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddMlc_boMlcPoweredUP = FALSE;

  //Step 3) Call the FUT
  boRet = CddMlc_IsMlcPowered();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(boRet, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddMlc_SetTarget
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: 
///        Check usage of received duty cycle via RTE and passing it to the
///        configured driver
///
///    - Test Design Technique: DT (Decision Table),
///
///    - Preconditions: aunTestPWM_1_1024_Input containing duty cyle values
///                     for each pixel
///
///    - Expected test results: 
///        - duty cycle is updated 
///
///      - DT-Info:
///         - Inputs:
///            ucMlcConfig              :  device matrix type connected
///            aunTestPWM_1_1024_Input  :  input PWM for each pixel
///         - Expected results
///            aunTestPWM_1_1024_Output :  expected value returned  by the FUT, output PWM
///
//-----------------------------------------------------------------------------
void Mt_CddMlc_SetTarget(void)
{
  typedef struct tsTestCaseDataInput
  {
    uint8                ucMlcConfig;
    uint16               aunTestPWM_1_1024_Input[TEST_Cfg_Chips][TEST_Cfg_Pixels];
  }tsTestCaseDataInput;

  typedef struct tsTestCaseDataOutput
  {
    uint16               aunTestPWM_1_1024_Output[TEST_Cfg_Chips][TEST_Cfg_Pixels];
  }tsTestCaseDataOutput;

  typedef struct tsTestCaseData
  {
    tsTestCaseDataInput   sInputData;
    tsTestCaseDataOutput  sOutputData;
  }tsTestCaseData;

  tsTestCaseData asTestCaseData[] =
  {
    //                         Inputs                                       ||          Outputs                                        
    //  MlcConfig                        Input PWM,                         ||         Output PWM

    { { TEST_DRV_TYPE_TPSGEN2_662A,   TEST_DRV_PWM_VALS_7CHIPS_16PXL_20PERC  }, { TEST_DRV_PWM_VALS_7CHIPS_16PXL_20PERC   } },
    { { TEST_DRV_TYPE_TPSGEN2_663A,   TEST_DRV_PWM_VALS_7CHIPS_16PXL         }, { TEST_DRV_PWM_VALS_7CHIPS_16PXL          } },
    { { TEST_DRV_DISABLED,            TEST_DRV_PWM_VALS_7CHIPS_16PXL         }, { TEST_DRV_PWM_VALS_7CHIPS_16PXL          } },
    { { TEST_DRV_TYPE_TPSGEN3_664,    TEST_DRV_PWM_VALS_7CHIPS_16PXL_50PERC  }, { TEST_DRV_PWM_VALS_7CHIPS_16PXL_50PERC   } },
    { { TEST_DRV_TYPE_TPSGEN3_665,    TEST_DRV_PWM_VALS_7CHIPS_16PXL_20PERC  }, { TEST_DRV_PWM_VALS_7CHIPS_16PXL_20PERC   } },
    { { TEST_DRV_TYPE_TPSGEN3_667,    TEST_DRV_PWM_VALS_7CHIPS_16PXL_00PWMs  }, { TEST_DRV_PWM_VALS_7CHIPS_16PXL_00PWMs   } },
    { { TEST_DRV_TYPE_TPSGENx_1,      TEST_DRV_PWM_VALS_7CHIPS_16PXL_20PERC  }, { TEST_DRV_PWM_VALS_7CHIPS_16PXL_20PERC   } },
    { { TEST_DRV_TYPE_TPSGENx_2,      TEST_DRV_PWM_VALS_7CHIPS_16PXL_20PERC  }, { TEST_DRV_PWM_VALS_7CHIPS_16PXL_20PERC   } }
  };

  for (uint8 ucIdx = 0u; ucIdx < sizeof(asTestCaseData) / sizeof(asTestCaseData[0]); ucIdx++)
  {
    //Step 1) Set pre - conditions
    uint8           ucTestData_TypeFam  = 0u;
    tsCddMlcTarget* psTestDataPWM       = NULL_PTR;
    InitConditions();

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    psTestDataPWM          = &asTestCaseData[ucIdx].sInputData.aunTestPWM_1_1024_Input[0][0];
    ucTestData_TypeFam     =  asTestCaseData[ucIdx].sInputData.ucMlcConfig;

    Test_Drv_SetTgtMtxPixels(&asTestCaseData[ucIdx].sInputData.aunTestPWM_1_1024_Input[0][0]);

     //Step 3) Call the FUT
    CddMlc_SetTarget(ucTestData_TypeFam, &psTestDataPWM[0]);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    for (uint8 ucDevNbr = 0u; ucDevNbr < TEST_Cfg_Chips; ucDevNbr++)
    {
      for (uint8 ucPxlNbr = 0u; ucPxlNbr < TEST_Cfg_Pixels; ucPxlNbr++)
      {
        AL_UNITTEST_CHECK(CddMlc_sTarget.aunDutyCycle_1_1024[ucDevNbr][ucPxlNbr], asTestCaseData[ucIdx].sOutputData.aunTestPWM_1_1024_Output[ucDevNbr][ucPxlNbr], == );
      }
    }
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddMlc_CheckReinit
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: 
///        Check usage of received reinit command and passing it to the
///        configured driver
///
///    - Test Design Technique: DT (Decision Table),
///
///    - Preconditions: coding is read, command to reinit available
///
///    - Expected test results: 
///        - command to reinit is set accordingly
///
///      - DT-Info:
///         - Inputs:
///            ucMlcConfig       :  device matrix type connected
///            boCmdReinit       :  reinit command
///         - Expected results
///            boCmdReinitStatus :  expected value returned  by the FUT, output command status
///
//-----------------------------------------------------------------------------
void Mt_CddMlc_CheckReinit(void)
{
  typedef struct tsTestCaseDataInput
  {
    uint8                ucMlcConfig;
    boolean              boCmdReinit;
  }tsTestCaseDataInput;

  typedef struct tsTestCaseDataOutput
  {
    boolean              boCmdReinitStatus;
  }tsTestCaseDataOutput;

  typedef struct tsTestCaseData
  {
    tsTestCaseDataInput   sInputData;
    tsTestCaseDataOutput  sOutputData;
  }tsTestCaseData;

  tsTestCaseData asTestCaseData[] =
  {
    //                         Inputs            ||      Outputs                                        
    //  MlcConfig                     CmdReinit  ||    CmdReinitStatus

    { { TEST_DRV_TYPE_TPSGEN2_662A,     TRUE     },    { TRUE   } },
    { { TEST_DRV_TYPE_TPSGEN2_663A,     TRUE     },    { TRUE   } },
    { { TEST_DRV_DISABLED,              TRUE     },    { FALSE  } },
    { { TEST_DRV_TYPE_TPSGEN3_664,      FALSE    },    { FALSE  } },
    { { TEST_DRV_TYPE_TPSGEN3_665,      FALSE    },    { FALSE  } },
    { { TEST_DRV_TYPE_TPSGEN3_667,      FALSE    },    { FALSE  } },
    { { TEST_DRV_TYPE_TPSGENx_1,        TRUE     },    { TRUE   } },
    { { TEST_DRV_TYPE_TPSGENx_2,        FALSE    },    { FALSE  } }
  };

  for (uint8 ucIdx = 0u; ucIdx < sizeof(asTestCaseData) / sizeof(asTestCaseData[0]); ucIdx++)
  {
    //Step 1) Set pre - conditions
    uint8   ucTestData_TypeFam  = 0u;
    boolean boTestDataCmd       = FALSE;
    InitConditions();

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    ucTestData_TypeFam  = asTestCaseData[ucIdx].sInputData.ucMlcConfig;
    boTestDataCmd       = asTestCaseData[ucIdx].sInputData.boCmdReinit;

     //Step 3) Call the FUT
    CddMlc_CheckReinit(ucTestData_TypeFam, boTestDataCmd);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    AL_UNITTEST_CHECK(Test_Drv_GetReinitMatrix(), asTestCaseData[ucIdx].sOutputData.boCmdReinitStatus, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddMlcTPS92662_GetDeviceStatusFault
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: 
///        Check if there's a communication fault with a GEN2 device identified and save
///        its status. Return TRUE if all devices are broken.
///
///    - Test Design Technique: DT (Decision Table),
///
///    - Preconditions: different configurations for communication faults
///
///    - Expected test results: 
///        - bus error status and individual device status
///
///      - DT-Info:
///         - Inputs:
///            ucConnectedDevs                      :  connected devices of GEN2
///            boDeviceCommFault[TEST_Cfg_Chips]    :  individual device fault status
///         - Expected results
///            boBrokenComm                         :  expected value returned  by the FUT, all devices are broken = broken bus
///            boOutputCommFault[TEST_Cfg_Chips]    :  expected value returned  by the FUT, output of individual device fault status
///
//-----------------------------------------------------------------------------
void Mt_CddMlcTPS92662_GetDeviceStatusFault(void)
{
  typedef struct tsTestCaseDataInput
  {
    uint8                ucConnectedDevs;
    uint8                boDeviceCommFault[TEST_Cfg_Chips];
  }tsTestCaseDataInput;

  typedef struct tsTestCaseDataOutput
  {
    boolean              boBrokenComm;
    boolean              boOutputCommFault[TEST_Cfg_Chips];
  }tsTestCaseDataOutput;

  typedef struct tsTestCaseData
  {
    tsTestCaseDataInput   sInputData;
    tsTestCaseDataOutput  sOutputData;
  }tsTestCaseData;

  tsTestCaseData asTestCaseData[] =
  {
    //                Inputs                                          ||                          Outputs                                        
    //  ConnectedDevs     Individual Comm Error                       ||    Bus err         Output Individual Comm Error

    { { 7u,     { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE } },    { FALSE,  { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE }  } },  /* T1 : all devices without comm error */
    { { 4u,     { FALSE, FALSE, TRUE,  FALSE, FALSE, FALSE, FALSE } },    { FALSE,  { FALSE, FALSE, TRUE,  FALSE, FALSE, FALSE, FALSE }  } },  /* T2 : single device with comm error */
    { { 2u,     { FALSE, FALSE, FALSE, FALSE, TRUE,  FALSE, TRUE  } },    { TRUE,   { FALSE, FALSE, FALSE, FALSE, TRUE,  FALSE, TRUE  }  } },  /* T3 : all devices with comm error */
    { { 8u,     { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE  } },    { FALSE,  { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE  }  } },  /* T4 : more configured devices than supported */
    { { 0u,     { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE } },    { FALSE,  { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE }  } },  /* T5 : No devices configured */
  };

    for (uint8 ucIdx = 0u; ucIdx < sizeof(asTestCaseData) / sizeof(asTestCaseData[0]); ucIdx++)
  {
    //Step 1) Set pre - conditions
     InitConditions();
     boolean boRetVal = FALSE;
     boolean boTestDataOutputCommFault[TEST_Cfg_Chips] = { FALSE };

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
     CddMlc_pfGetCodingData()->ucMlcConnectedDevGEN2 = asTestCaseData[ucIdx].sInputData.ucConnectedDevs;

    for (uint8 ucDevNbr = 0u; ucDevNbr < TEST_Cfg_Chips; ucDevNbr++)
    {
      Test_Drv_SetComFaultGEN2(ucDevNbr, asTestCaseData[ucIdx].sInputData.boDeviceCommFault[ucDevNbr]);
    }

     //Step 3) Call the FUT
    boRetVal = CddMlcTPS92662_GetDeviceStatusFault(boTestDataOutputCommFault);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    AL_UNITTEST_CHECK(boRetVal, asTestCaseData[ucIdx].sOutputData.boBrokenComm, == );

    for (uint8 ucDevNbr = 0u; ucDevNbr < TEST_Cfg_Chips; ucDevNbr++)
    {
      AL_UNITTEST_CHECK(boTestDataOutputCommFault[ucDevNbr], asTestCaseData[ucIdx].sOutputData.boOutputCommFault[ucDevNbr], == );
    }
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddMlcTPS92664_GetDeviceStatusFault
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: 
///        Check if there's a communication fault with a GEN3 device identified and save
///        its status. Return TRUE if all devices are broken.
///
///    - Test Design Technique: DT (Decision Table),
///
///    - Preconditions: different configurations for communication faults
///
///    - Expected test results: 
///        - bus error status and individual device status
///
///      - DT-Info:
///         - Inputs:
///            ucConnectedDevs                      :  connected devices of GEN3
///            aboDeviceCommFault[TEST_Cfg_Chips]   :  individual device fault status
///         - Expected results
///            boBrokenComm                         :  expected value returned  by the FUT, all devices are broken = broken bus
///            aboOutputCommFault[TEST_Cfg_Chips]   :  expected value returned  by the FUT, output of individual device fault status
///
//-----------------------------------------------------------------------------
void Mt_CddMlcTPS92664_GetDeviceStatusFault(void)
{
  typedef struct tsTestCaseDataInput
  {
    uint8                ucConnectedDevs;
    uint8                aboDeviceCommFault[TEST_Cfg_Chips];
  }tsTestCaseDataInput;

  typedef struct tsTestCaseDataOutput
  {
    boolean              boBrokenComm;
    boolean              aboOutputCommFault[TEST_Cfg_Chips];
  }tsTestCaseDataOutput;

  typedef struct tsTestCaseData
  {
    tsTestCaseDataInput   sInputData;
    tsTestCaseDataOutput  sOutputData;
  }tsTestCaseData;

  tsTestCaseData asTestCaseData[] =
  {
    //                Inputs                                          ||                          Outputs                                        
    //  ConnectedDevs     Individual Comm Error                       ||    Bus err         Output Individual Comm Error

    { { 7u,     { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE } },    { FALSE,  { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE }  } },  /* T1 : all devices without comm error */
    { { 4u,     { FALSE, FALSE, TRUE,  FALSE, FALSE, FALSE, FALSE } },    { FALSE,  { FALSE, FALSE, TRUE,  FALSE, FALSE, FALSE, FALSE }  } },  /* T2 : single device with comm error */
    { { 2u,     { FALSE, FALSE, FALSE, FALSE, TRUE,  FALSE, TRUE  } },    { TRUE,   { FALSE, FALSE, FALSE, FALSE, TRUE,  FALSE, TRUE  }  } },  /* T3 : all devices with comm error */
    { { 8u,     { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE  } },    { FALSE,  { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE  }  } },  /* T4 : more configured devices than supported */
    { { 0u,     { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE } },    { FALSE,  { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE }  } },  /* T5 : No devices configured */
  };

    for (uint8 ucIdx = 0u; ucIdx < sizeof(asTestCaseData) / sizeof(asTestCaseData[0]); ucIdx++)
  {
    //Step 1) Set pre - conditions
     InitConditions();
     boolean boRetVal = FALSE;
     boolean boTestDataOutputCommFault[TEST_Cfg_Chips] = { FALSE };

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
     CddMlc_pfGetCodingData()->ucMlcConnectedDevGEN3 = asTestCaseData[ucIdx].sInputData.ucConnectedDevs;

    for (uint8 ucDevNbr = 0u; ucDevNbr < TEST_Cfg_Chips; ucDevNbr++)
    {
      Test_Drv_SetComFaultGEN3(ucDevNbr, asTestCaseData[ucIdx].sInputData.aboDeviceCommFault[ucDevNbr]);
    }

     //Step 3) Call the FUT
    boRetVal = CddMlcTPS92664_GetDeviceStatusFault(boTestDataOutputCommFault);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    AL_UNITTEST_CHECK(boRetVal, asTestCaseData[ucIdx].sOutputData.boBrokenComm, == );

    for (uint8 ucDevNbr = 0u; ucDevNbr < TEST_Cfg_Chips; ucDevNbr++)
    {
      AL_UNITTEST_CHECK(boTestDataOutputCommFault[ucDevNbr], asTestCaseData[ucIdx].sOutputData.aboOutputCommFault[ucDevNbr], == );
    }
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddMlcTPS9266x_GetDeviceStatusFault
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: 
///        Check if there's a communication fault with a GEN2 or GEN3 device identified and save
///        its status. Return TRUE if all devices are broken.
///
///    - Test Design Technique: DT (Decision Table),
///
///    - Preconditions: different configurations for communication faults
///
///    - Expected test results: 
///        - bus error status and individual device status
///
///      - DT-Info:
///         - Inputs:
///            ucConnectedDevs                      :  connected devices of each family (keep equal for easier testing)
///            aboDeviceCommFault[TEST_Cfg_Chips]   :  individual device fault status
///         - Expected results
///            boBrokenComm                         :  expected value returned  by the FUT, all devices are broken = broken bus
///            aboOutputCommFault[TEST_Cfg_Chips]   :  expected value returned  by the FUT, output of individual device fault status
///
//-----------------------------------------------------------------------------
void Mt_CddMlcTPS9266x_GetDeviceStatusFault(void)
{
  typedef struct tsTestCaseDataInput
  {
    uint8                ucConnectedDevs;
    uint8                aboDeviceCommFault[TEST_Cfg_Chips];
  }tsTestCaseDataInput;

  typedef struct tsTestCaseDataOutput
  {
    boolean              boBrokenComm;
    boolean              aboOutputCommFault[TEST_Cfg_Chips];
  }tsTestCaseDataOutput;

  typedef struct tsTestCaseData
  {
    tsTestCaseDataInput   sInputData;
    tsTestCaseDataOutput  sOutputData;
  }tsTestCaseData;

  tsTestCaseData asTestCaseData[] =
  {
    //                Inputs                                          ||                          Outputs                                        
    //  ConnectedDevs     Individual Comm Error                       ||    Bus err         Output Individual Comm Error

    { { 2u,     { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE } },    { FALSE,  { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE }  } },  /* T1 : all devices without comm error */
    { { 2u,     { TRUE,  FALSE, FALSE, FALSE, TRUE,  FALSE, FALSE } },    { FALSE,  { TRUE,  FALSE, FALSE, FALSE, TRUE,  FALSE, FALSE }  } },  /* T2 : single device with comm error (1st from each fam) */
    { { 2u,     { TRUE,  FALSE, TRUE,  FALSE, TRUE,  FALSE, TRUE  } },    { TRUE,   { TRUE,  FALSE, TRUE,  FALSE, TRUE,  FALSE, TRUE  }  } },  /* T3 : all devices with comm error */
    { { 0u,     { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE } },    { FALSE,  { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE }  } },  /* T4 : No devices configured */
  };

    for (uint8 ucIdx = 0u; ucIdx < sizeof(asTestCaseData) / sizeof(asTestCaseData[0]); ucIdx++)
  {
    //Step 1) Set pre - conditions
     InitConditions();
     boolean boRetVal = FALSE;
     boolean boTestDataOutputCommFault[TEST_Cfg_Chips] = { FALSE };

     memcpy(&CddMlc_sCodingData.aucMlcCanUartDeviceID[0], &Test_Drv_CodingConfig_Variants[CDDMLC_COD_MATRIX_TYPE_TPSGENx_1].LMM__UART_CAN_ADDRESSES[0], sizeof(CddMlc_sCodingData.aucMlcCanUartDeviceID));

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
     CddMlc_pfGetCodingData()->ucMlcConnectedDevGEN2 = asTestCaseData[ucIdx].sInputData.ucConnectedDevs;
     CddMlc_pfGetCodingData()->ucMlcConnectedDevGEN3 = asTestCaseData[ucIdx].sInputData.ucConnectedDevs;

    for (uint8 ucDevNbr = 0u; ucDevNbr < TEST_Cfg_Chips; ucDevNbr++)
    {
      Test_Drv_SetComFaultGEN2(ucDevNbr, asTestCaseData[ucIdx].sInputData.aboDeviceCommFault[ucDevNbr]);
      Test_Drv_SetComFaultGEN3(ucDevNbr, asTestCaseData[ucIdx].sInputData.aboDeviceCommFault[ucDevNbr]);
    }

     //Step 3) Call the FUT
    boRetVal = CddMlcTPS9266x_GetDeviceStatusFault(boTestDataOutputCommFault);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    AL_UNITTEST_CHECK(boRetVal, asTestCaseData[ucIdx].sOutputData.boBrokenComm, == );

    for (uint8 ucDevNbr = 0u; ucDevNbr < TEST_Cfg_Chips; ucDevNbr++)
    {
      AL_UNITTEST_CHECK(boTestDataOutputCommFault[ucDevNbr], asTestCaseData[ucIdx].sOutputData.aboOutputCommFault[ucDevNbr], == );
    }
  }
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddMlc_GetStatus
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: 
///        Ensure correct status report concerning communication errors, switch faults,
///        sensor data, power-on reset status for further processing or diagnostic purposes.
///
///    - Test Design Technique: DT (Decision Table),
///
///    - Preconditions: different configurations for faults
///
///    - Expected test results: 
///        - bus error status and individual device fault status
///
///      - DT-Info:
///         - Inputs:
///            ucLoadMlcConfig                      :  matrix type connected
///            ucConnectedDevs                      :  connected devices of GEN2
///            boInitCompleted                      :  individual driver initialization status
///            boDeviceCommFault[TEST_Cfg_Chips]    :  individual device comm fault status
///            aunChipPxlFault[TEST_Cfg_Chips]      :  individual device pixel fault status
///         - Expected results
///            boBrokenComm                         :  expected value returned  by the FUT, all devices are broken = broken bus
///            boInitStatus                         :  expected value returned  by the FUT, output of init status
///            boOutputCommFault[TEST_Cfg_Chips]    :  expected value returned  by the FUT, output of individual device comm fault status
///            unOutputChipPxlFault[TEST_Cfg_Chips] :  expected value returned  by the FUT, output of individual device pixel fault status
///
//-----------------------------------------------------------------------------
void Mt_CddMlc_GetStatus(void)
{
  typedef struct tsTestCaseDataInput
  {
    uint8                ucLoadMlcConfig;
    uint8                ucConnectedDevs;
    boolean              boInitCompleted;
    uint8                aboDeviceCommFault[TEST_Cfg_Chips];
    uint16               aunChipPxlFault   [TEST_Cfg_Chips];
  }tsTestCaseDataInput;

  typedef struct tsTestCaseDataOutput
  {
    boolean              boBrokenComm;
    boolean              boInitStatus;
    boolean              boOutputCommFault    [TEST_Cfg_Chips];
    uint16               unOutputChipPxlFault [TEST_Cfg_Chips];
  }tsTestCaseDataOutput;

  typedef struct tsTestCaseData
  {
    tsTestCaseDataInput   sInputData;
    tsTestCaseDataOutput  sOutputData;
  }tsTestCaseData;

  tsTestCaseData asTestCaseData[] =
  {
                                                  //                                                          Inputs                                                                                              ||                          Outputs                                        
                                                  //  Mlc Configured,     ConnectedDevs, InitCompleted,     Individual Comm Error ,                               Individual Pixel Error                                        || Bus err,  InitStatus       Output Individual Comm Error,                   Output Individual Pixel Error

 /* T1 : all GEN2 devices without comm error */   { { TEST_DRV_TYPE_TPSGEN2_663A, 7u,     TRUE,   { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE },   { 0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u }  }, {   FALSE,  TRUE,   { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE },   { 0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u } } },
 /* T2 : all GEN3 devices without comm error */   { { TEST_DRV_TYPE_TPSGEN3_664,  7u,     TRUE,   { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE },   { 0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u }  }, {   FALSE,  TRUE,   { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE },   { 0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u } } },
 /* T3 : single device with error */              { { TEST_DRV_TYPE_TPSGEN2_662A, 2u,     FALSE,  { FALSE, FALSE, TRUE,  FALSE, FALSE, FALSE, FALSE },   { 0x0000u, 0x0000u, 0x001Fu, 0x0000u, 0x0000u, 0x0000u, 0x0000u }  }, {   FALSE,  FALSE,  { FALSE, FALSE, TRUE,  FALSE, FALSE, FALSE, FALSE },   { 0x0000u, 0x0000u, 0x001Fu, 0x0000u, 0x0000u, 0x0000u, 0x0000u } } },
 /* T4 : single device with error */              { { TEST_DRV_TYPE_TPSGEN3_665,  3u,     FALSE,  { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE  },   { 0x0FF0u, 0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0FFFu }  }, {   FALSE,  FALSE,  { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE  },   { 0x0FF0u, 0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0FFFu } } },
 /* T5 : all cfg devices with comm error   */     { { TEST_DRV_TYPE_TPSGEN3_667,  2u,     TRUE,   { TRUE,  FALSE, FALSE, FALSE, FALSE, FALSE, TRUE  },   { 0x0FF0u, 0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0FFFu }  }, {   TRUE,   TRUE,   { TRUE,  FALSE, FALSE, FALSE, FALSE, FALSE, TRUE  },   { 0x0FF0u, 0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0FFFu } } },
 /* T6 : all cfg devices with comm error   */     { { TEST_DRV_TYPE_TPSGENx_1,    2u,     FALSE,  { TRUE,  FALSE, TRUE,  FALSE, TRUE,  FALSE, TRUE  },   { 0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u }  }, {   TRUE,   FALSE,  { TRUE,  FALSE, TRUE,  FALSE, TRUE,  FALSE, TRUE  },   { 0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u } } },
 /* T7 : all cfg devices with pixel error  */     { { TEST_DRV_TYPE_TPSGENx_2,    2u,     TRUE,   { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE },   { 0x0FFFu, 0x0000u, 0x0FFFu, 0x0000u, 0x001Fu, 0x0000u, 0x001Fu }  }, {   FALSE,  TRUE,   { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE },   { 0x0FFFu, 0x0000u, 0x0FFFu, 0x0000u, 0x001Fu, 0x0000u, 0x001Fu } } },
 /* T8 : no device configured, errors present */  { { TEST_DRV_DISABLED,          0u,     FALSE,  { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE },   { 0x0FFFu, 0x0000u, 0x0FFFu, 0x0000u, 0x001Fu, 0x0000u, 0x001Fu }  }, {   FALSE,  FALSE,  { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE },   { 0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u } } },
  };

    for (uint8 ucIdx = 0u; ucIdx < sizeof(asTestCaseData) / sizeof(asTestCaseData[0]); ucIdx++)
  {
    //Step 1) Set pre - conditions
     InitConditions();
     tsCddMlcStatus sTestDataOutput   = { 0 };
     uint8          ucTestDataMtxType = 0u;

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
     ucTestDataMtxType                               = asTestCaseData[ucIdx].sInputData.ucLoadMlcConfig;
     CddMlc_pfGetCodingData()->ucMlcConnectedDevGEN2 = asTestCaseData[ucIdx].sInputData.ucConnectedDevs;
     CddMlc_pfGetCodingData()->ucMlcConnectedDevGEN3 = asTestCaseData[ucIdx].sInputData.ucConnectedDevs;

    for (uint8 ucDevNbr = 0u; ucDevNbr < TEST_Cfg_Chips; ucDevNbr++)
    {
      Test_Drv_SetComFaultGEN2(ucDevNbr, asTestCaseData[ucIdx].sInputData.aboDeviceCommFault[ucDevNbr]);
      Test_Drv_SetComFaultGEN3(ucDevNbr, asTestCaseData[ucIdx].sInputData.aboDeviceCommFault[ucDevNbr]);

      Test_Drv_SetShortToGndGEN2(ucDevNbr, asTestCaseData[ucIdx].sInputData.aunChipPxlFault[ucDevNbr]);
      Test_Drv_SetShortToGndGEN3(ucDevNbr, asTestCaseData[ucIdx].sInputData.aunChipPxlFault[ucDevNbr]);
    }

    Test_Drv_SetDrvInit_Gen2(asTestCaseData[ucIdx].sInputData.boInitCompleted);
    Test_Drv_SetDrvInit_Gen3(asTestCaseData[ucIdx].sInputData.boInitCompleted);

     //Step 3) Call the FUT
    CddMlc_GetStatus(ucTestDataMtxType, &sTestDataOutput);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    for (uint8 ucDevNbr = 0u; ucDevNbr < TEST_Cfg_Chips; ucDevNbr++)
    {
      AL_UNITTEST_CHECK(sTestDataOutput.aboComFault[ucDevNbr],                     asTestCaseData[ucIdx].sOutputData.boOutputCommFault[ucDevNbr],     == );
      AL_UNITTEST_CHECK(sTestDataOutput.asSwitchFault[ucDevNbr].unSwitchFault_Bit, asTestCaseData[ucIdx].sOutputData.unOutputChipPxlFault[ucDevNbr],  == );
    }
      AL_UNITTEST_CHECK(sTestDataOutput.boBusFault,                                asTestCaseData[ucIdx].sOutputData.boBrokenComm,                    == );
      AL_UNITTEST_CHECK(sTestDataOutput.boInitStatus,                              asTestCaseData[ucIdx].sOutputData.boInitStatus,                    == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddMlcTPS92662_GetDeviceCrcFault
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: 
///        Check if there's a corrupt communication fault with a GEN2 device identified
///        and save its status.
///
///    - Test Design Technique: DT (Decision Table),
///
///    - Preconditions: different configurations for corrupt communication faults
///
///    - Expected test results: 
///        -  individual device status
///
///      - DT-Info:
///         - Inputs:
///            ucConnectedDevs                      :  connected devices of GEN2
///            boDeviceCrcFault[TEST_Cfg_Chips]     :  individual device fault status
///         - Expected results
///            boOutputCrcFault[TEST_Cfg_Chips]     :  expected value returned  by the FUT, output of individual device fault status
///
//-----------------------------------------------------------------------------
void Mt_CddMlcTPS92662_GetDeviceCrcFault(void)
{
  typedef struct tsTestCaseDataInput
  {
    uint8                ucConnectedDevs;
    uint8                boDeviceCrcFault[TEST_Cfg_Chips];
  }tsTestCaseDataInput;

  typedef struct tsTestCaseDataOutput
  {
    boolean              boOutputCrcFault[TEST_Cfg_Chips];
  }tsTestCaseDataOutput;

  typedef struct tsTestCaseData
  {
    tsTestCaseDataInput   sInputData;
    tsTestCaseDataOutput  sOutputData;
  }tsTestCaseData;

  tsTestCaseData asTestCaseData[] =
  {
    //                Inputs                                          ||                          Outputs                                        
    //  ConnectedDevs     Individual Crc Error                        ||          Output Individual Crc Error

    { { 7u,     { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE } },   { { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE }  } },  /* T1 : all devices without crc error */
    { { 4u,     { FALSE, FALSE, TRUE,  FALSE, FALSE, FALSE, FALSE } },   { { FALSE, FALSE, TRUE,  FALSE, FALSE, FALSE, FALSE }  } },  /* T2 : single device with crc error */
    { { 2u,     { FALSE, FALSE, FALSE, FALSE, TRUE,  FALSE, TRUE  } },   { { FALSE, FALSE, FALSE, FALSE, TRUE,  FALSE, TRUE  }  } },  /* T3 : all devices with crc error */
    { { 8u,     { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE  } },   { { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE  }  } },  /* T4 : more configured devices than supported */
    { { 0u,     { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE } },   { { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE }  } },  /* T5 : No devices configured */
  };

    for (uint8 ucIdx = 0u; ucIdx < sizeof(asTestCaseData) / sizeof(asTestCaseData[0]); ucIdx++)
  {
    //Step 1) Set pre - conditions
     InitConditions();
     boolean boRetVal = FALSE;
     boolean boTestDataOutputCrcFault[TEST_Cfg_Chips] = { FALSE };

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
     CddMlc_pfGetCodingData()->ucMlcConnectedDevGEN2 = asTestCaseData[ucIdx].sInputData.ucConnectedDevs;

    for (uint8 ucDevNbr = 0u; ucDevNbr < TEST_Cfg_Chips; ucDevNbr++)
    {
      Test_Drv_SetCrcFaultGEN2(ucDevNbr, asTestCaseData[ucIdx].sInputData.boDeviceCrcFault[ucDevNbr]);
    }

     //Step 3) Call the FUT
    boRetVal = CddMlcTPS92662_GetDeviceCrcFault(boTestDataOutputCrcFault);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    for (uint8 ucDevNbr = 0u; ucDevNbr < TEST_Cfg_Chips; ucDevNbr++)
    {
      AL_UNITTEST_CHECK(boTestDataOutputCrcFault[ucDevNbr], asTestCaseData[ucIdx].sOutputData.boOutputCrcFault[ucDevNbr], == );
    }
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddMlcTPS92664_GetDeviceCrcFault
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: 
///        Check if there's a corrupt communication fault with a GEN2 device identified
///        and save its status.
///
///    - Test Design Technique: DT (Decision Table),
///
///    - Preconditions: different configurations for corrupt communication faults
///
///    - Expected test results: 
///        -  individual device status
///
///      - DT-Info:
///         - Inputs:
///            ucConnectedDevs                      :  connected devices of GEN2
///            boDeviceCrcFault[TEST_Cfg_Chips]     :  individual device fault status
///         - Expected results
///            boOutputCrcFault[TEST_Cfg_Chips]     :  expected value returned  by the FUT, output of individual device fault status
///
//-----------------------------------------------------------------------------
void Mt_CddMlcTPS92664_GetDeviceCrcFault(void)
{
  typedef struct tsTestCaseDataInput
  {
    uint8                ucConnectedDevs;
    uint8                boDeviceCrcFault[TEST_Cfg_Chips];
  }tsTestCaseDataInput;

  typedef struct tsTestCaseDataOutput
  {
    boolean              boOutputCrcFault[TEST_Cfg_Chips];
  }tsTestCaseDataOutput;

  typedef struct tsTestCaseData
  {
    tsTestCaseDataInput   sInputData;
    tsTestCaseDataOutput  sOutputData;
  }tsTestCaseData;

  tsTestCaseData asTestCaseData[] =
  {
    //                Inputs                                          ||                          Outputs                                        
    //  ConnectedDevs     Individual Crc Error                        ||            Output Individual Crc Error

    { { 7u,     { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE } },    { { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE }  } },  /* T1 : all devices without crc error */
    { { 4u,     { FALSE, FALSE, TRUE,  FALSE, FALSE, FALSE, FALSE } },    { { FALSE, FALSE, TRUE,  FALSE, FALSE, FALSE, FALSE }  } },  /* T2 : single device with crc error */
    { { 2u,     { FALSE, FALSE, FALSE, FALSE, TRUE,  FALSE, TRUE  } },    { { FALSE, FALSE, FALSE, FALSE, TRUE,  FALSE, TRUE  }  } },  /* T3 : all devices with crc error */
    { { 8u,     { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE  } },    { { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE  }  } },  /* T4 : more configured devices than supported */
    { { 0u,     { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE } },    { { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE }  } },  /* T5 : No devices configured */
  };

    for (uint8 ucIdx = 0u; ucIdx < sizeof(asTestCaseData) / sizeof(asTestCaseData[0]); ucIdx++)
  {
    //Step 1) Set pre - conditions
     InitConditions();
     boolean boRetVal = FALSE;
     boolean boTestDataOutputCrcFault[TEST_Cfg_Chips] = { FALSE };

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
     CddMlc_pfGetCodingData()->ucMlcConnectedDevGEN3 = asTestCaseData[ucIdx].sInputData.ucConnectedDevs;

    for (uint8 ucDevNbr = 0u; ucDevNbr < TEST_Cfg_Chips; ucDevNbr++)
    {
      Test_Drv_SetCrcFaultGEN3(ucDevNbr, asTestCaseData[ucIdx].sInputData.boDeviceCrcFault[ucDevNbr]);
    }

     //Step 3) Call the FUT
    boRetVal = CddMlcTPS92664_GetDeviceCrcFault(boTestDataOutputCrcFault);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    for (uint8 ucDevNbr = 0u; ucDevNbr < TEST_Cfg_Chips; ucDevNbr++)
    {
      AL_UNITTEST_CHECK(boTestDataOutputCrcFault[ucDevNbr], asTestCaseData[ucIdx].sOutputData.boOutputCrcFault[ucDevNbr], == );
    }
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddMlcTPS9266x_GetDeviceCrcFault
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: 
///        Check if there's a communication fault with a GEN2 or GEN3 device identified and save
///        its status. Return TRUE if all devices are broken.
///
///    - Test Design Technique: DT (Decision Table),
///
///    - Preconditions: different configurations for communication faults
///
///    - Expected test results: 
///        - bus error status and individual device status
///
///      - DT-Info:
///         - Inputs:
///            ucConnectedDevs                      :  connected devices of each family (keep equal for easier testing)
///            aboDeviceCommFault[TEST_Cfg_Chips]   :  individual device fault status
///         - Expected results
///            boBrokenComm                         :  expected value returned  by the FUT, all devices are broken = broken bus
///            aboOutputCommFault[TEST_Cfg_Chips]   :  expected value returned  by the FUT, output of individual device fault status
///
//-----------------------------------------------------------------------------
void Mt_CddMlcTPS9266x_GetDeviceCrcFault(void)
{
  typedef struct tsTestCaseDataInput
  {
    uint8                ucConnectedDevs;
    uint8                boDeviceCrcFault[TEST_Cfg_Chips];
  }tsTestCaseDataInput;

  typedef struct tsTestCaseDataOutput
  {
    boolean              boOutputCrcFault[TEST_Cfg_Chips];
  }tsTestCaseDataOutput;

  typedef struct tsTestCaseData
  {
    tsTestCaseDataInput   sInputData;
    tsTestCaseDataOutput  sOutputData;
  }tsTestCaseData;

  tsTestCaseData asTestCaseData[] =
  {
    //                Inputs                                          ||                          Outputs                                        
    //  ConnectedDevs     Individual Crc Error                        ||            Output Individual Crc Error

    { { 2u,     { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE } },    { { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE }  } },  /* T1 : all devices without crc error */
    { { 2u,     { TRUE,  FALSE, FALSE, FALSE, TRUE,  FALSE, FALSE } },    { { TRUE,  FALSE, FALSE, FALSE, TRUE,  FALSE, FALSE }  } },  /* T2 : single device with crc error (1st from each fam) */
    { { 2u,     { TRUE,  FALSE, TRUE,  FALSE, TRUE,  FALSE, TRUE  } },    { { TRUE,  FALSE, TRUE,  FALSE, TRUE,  FALSE, TRUE  }  } },  /* T3 : all devices with crc error */
    { { 0u,     { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE } },    { { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE }  } },  /* T4 : No devices configured */
  };

    for (uint8 ucIdx = 0u; ucIdx < sizeof(asTestCaseData) / sizeof(asTestCaseData[0]); ucIdx++)
  {
    //Step 1) Set pre - conditions
     InitConditions();
     boolean boRetVal = FALSE;
     boolean boTestDataOutputCrcFault[TEST_Cfg_Chips] = { FALSE };

     memcpy(&CddMlc_sCodingData.aucMlcCanUartDeviceID[0], &Test_Drv_CodingConfig_Variants[CDDMLC_COD_MATRIX_TYPE_TPSGENx_1].LMM__UART_CAN_ADDRESSES[0], sizeof(CddMlc_sCodingData.aucMlcCanUartDeviceID));

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
     CddMlc_pfGetCodingData()->ucMlcConnectedDevGEN2 = asTestCaseData[ucIdx].sInputData.ucConnectedDevs;
     CddMlc_pfGetCodingData()->ucMlcConnectedDevGEN3 = asTestCaseData[ucIdx].sInputData.ucConnectedDevs;

    for (uint8 ucDevNbr = 0u; ucDevNbr < TEST_Cfg_Chips; ucDevNbr++)
    {
      Test_Drv_SetCrcFaultGEN2(ucDevNbr, asTestCaseData[ucIdx].sInputData.boDeviceCrcFault[ucDevNbr]);
      Test_Drv_SetCrcFaultGEN3(ucDevNbr, asTestCaseData[ucIdx].sInputData.boDeviceCrcFault[ucDevNbr]);
    }

     //Step 3) Call the FUT
    boRetVal = CddMlcTPS9266x_GetDeviceCrcFault(boTestDataOutputCrcFault);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    for (uint8 ucDevNbr = 0u; ucDevNbr < TEST_Cfg_Chips; ucDevNbr++)
    {
      AL_UNITTEST_CHECK(boTestDataOutputCrcFault[ucDevNbr], asTestCaseData[ucIdx].sOutputData.boOutputCrcFault[ucDevNbr], == );
    }
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddMlc_VccxLine_Fault
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: 
///       Check VccxLine Fault
///
///    - Test Design Technique: - ET (Exploratory Testing) 
///
///    - Preconditions: VccxLine state set to Sh2Gnd
///
///    - Expected test results: 
///        - The function should return the reflected value
///
//-----------------------------------------------------------------------------
void Mt_CddMlc_VccxLine_Fault(void)
{
  //Step 1) Set pre - conditions
  boolean boRet = FALSE;
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Rte_Read_IoHwAbUser_VccxLineState_Param1 = 1;

  //Step 3) Call the FUT
  boRet = CddMlc_VccxLine_Fault();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(boRet, TRUE, == );
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
  ALUnitTest_AddFunction("Mt_CddMlc_CheckPowerUp",                  Mt_CddMlc_CheckPowerUp);
  ALUnitTest_AddFunction("Mt_CddMlc_IsMlcPowered",                  Mt_CddMlc_IsMlcPowered);
  ALUnitTest_AddFunction("Mt_CddMlc_SetTarget",                     Mt_CddMlc_SetTarget);
  ALUnitTest_AddFunction("Mt_CddMlc_CheckReinit",                   Mt_CddMlc_CheckReinit);
  ALUnitTest_AddFunction("Mt_CddMlcTPS92662_GetDeviceStatusFault",  Mt_CddMlcTPS92662_GetDeviceStatusFault);
  ALUnitTest_AddFunction("Mt_CddMlcTPS92664_GetDeviceStatusFault",  Mt_CddMlcTPS92664_GetDeviceStatusFault);
  ALUnitTest_AddFunction("Mt_CddMlcTPS9266x_GetDeviceStatusFault",  Mt_CddMlcTPS9266x_GetDeviceStatusFault);
  ALUnitTest_AddFunction("Mt_CddMlc_GetStatus",                     Mt_CddMlc_GetStatus);
  ALUnitTest_AddFunction("Mt_CddMlcTPS92662_GetDeviceCrcFault",     Mt_CddMlcTPS92662_GetDeviceCrcFault);
  ALUnitTest_AddFunction("Mt_CddMlcTPS92664_GetDeviceCrcFault",     Mt_CddMlcTPS92664_GetDeviceCrcFault);
  ALUnitTest_AddFunction("Mt_CddMlcTPS9266x_GetDeviceCrcFault",     Mt_CddMlcTPS9266x_GetDeviceCrcFault);
  ALUnitTest_AddFunction("Mt_CddMlc_VccxLine_Fault",                Mt_CddMlc_VccxLine_Fault);

  // project specific tests of adapter
  ALUnitTest_AddTests_Adapter();
}


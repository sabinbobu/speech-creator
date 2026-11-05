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
/// \brief Module test of IoHwAb
///
//-----------------------------------------------------------------------------
//=============================================================================
// includes
//=============================================================================

#include <ALUnitTest_UserInterface.h>
#include "Test.h"
//#include "Test_Stubs.h"

//=============================================================================
// Global variables (of the module itself)
//=============================================================================


//=============================================================================
// Function declarations (of the module itself)
//=============================================================================


//=============================================================================
// Function parameter stubs (of the module ifself)
//=============================================================================




//=============================================================================
// Function return value stubs (of the module ifself)
//=============================================================================


//=============================================================================
// Stub function declarations
//=============================================================================




//=============================================================================
// Stub function parameter stubs
//=============================================================================


//=============================================================================
// Stub function returned value stubs
//=============================================================================



//=============================================================================
// Stub function hit count variables
//=============================================================================


//=============================================================================
// Stub function definitions
//=============================================================================


//=============================================================================
// Test Cases
//=============================================================================

//=============================================================================
// Global variable stubs ( registers, global variables from other modules which are referenced in the module )
//=============================================================================

Mt_IoHwAbUserLRDet Mt_IoHwAbUserMTValue;
uint32 Mt_IoHwAb_FTM0Register;
uint32 Mt_IoHwAb_FTM4Register;
uint32 Mt_IoHwAb_CHOV_BitStatus;
uint32 ulVccx2_Diag_Timer;
boolean boVccx2_en_state;
uint16 unNew_PWM = 0u;
uint16 unOld_PWM = 0xFFFFu;
uint16 unSensPeriodPwm0_Err = 5520u;
uint16 unSensPeriodPwm1_Err = 5520u;
teIoHwAb_HlsState eSensShGndNew[CFG_CntSens] = { eIoHwAb_Hls_noError, eIoHwAb_Hls_noError };
teIoHwAb_HlsState eSensShVbatNew[CFG_CntSens] = { eIoHwAb_Hls_noError, eIoHwAb_Hls_noError };
tisNvmDeltaPwmPara NvmBlockDeltaPwmPara = { 0u };
uint32 ulDebounceTimer[CFG_CntSens] = { 0u };
boolean boStartTimer[CFG_CntSens] = { FALSE, FALSE };

CONST_AL tEftData EftData =
{
  // ------------------------------------------------------------------
  // Eft_Crc
  // ------------------------------------------------------------------
    {
      { 1234u },                // Eft_Crc32
      { 1u, 255u, 255u, 255u }  // Eft_DocVers
    },
  // ------------------------------------------------------------------


  // ------------------------------------------------------------------
  // Eft_Calib
  // ------------------------------------------------------------------
    { // union
    {
      { { 'C', 'A', 'L', 'I' } },      // Eft_Calib_Text
      { 255u, 255u, 255u, 255u },      // Eft_Calib_Type

      CDDTPS92520_Eft_Calib_Default,   // TPS92520 calibration
      CDDNCV78702_Eft_Calib_Default    // NCV78702 calibration
    }
    },


  // ------------------------------------------------------------------
  // Eft_HwDesc
  // ------------------------------------------------------------------
    { // union
    {
      { { 'H', 'W', 'I', 'D' } },  // Eft_HwDesc_Text
      { 255u, 255u, 255u, 255u },  // Eft_HwDesc_Type
    }
    },


  // ------------------------------------------------------------------
  // Eft_EcuVarCfg
  // ------------------------------------------------------------------
    { // union
    {
      { { 'V', 'C', 'F', 'G' } },                         // Eft_EcuVarCfg_Text
      { 255u, 255u, 1u, 255u },                               // Eft_EcuVarCfg_Type
      CDDTPS92520_Eft_EcuVarCfg_Default,                  // TPS92520 configuration
      CDDNCV78702_Eft_EcuVarCfg_Default,                  // NCV78702 configuration
      { 0x3FFFu, 0xFFFFu },                               // NTC
      { 216u, 9661u },                                    // ADC IN
      { { 2u, 255u }, { 0u, 255u } },                     // STP
      { 0u, 255u },                                       // DC OUT
      { 3u, 255u },                                       // EXT SUPPLY 2
      { 0u, 255u },                                       // EXT SUPPLY 3
      { 0u, 255u },                                       // SWITCH ARRAY
      { { 1u, 255u }, { 2u, 255u },                       // HSS
        { 3u, 255u }, { 0u, 255u } },                     // HSS
      { 1u, 255u },                                       // CAN2
      { 0u, 255u },                                       // CAN3
      { 0u, 255u },                                       // LIN
      { 2u, 255u },                                       // GPIO SBC
      { 0u, 255u },                                       // WK SENSE
      { { 1u, 255u }, { 1u, 255u },                       // IN
        { 3u, 255u }, { 1u, 255u } },                     // IN
      {
        5000u ,                                           // ADC FACTOR PCB TEMP
      { 6273u, 6273u, 6273u, 6273u, 6273u, 6273u, 6273u,  // ADC FACTOR NTC
        6273u, 6273u, 6273u, 6273u, 6273u, 6273u, 6273u },// ADC FACTOR NTC
        24643u,                                           // ADC FACTOR Vbat
        24643u,                                           // ADC FACTOR LrDetect
        5000u,                                            // ADC FACTOR HssSense_1_2
        5000u,                                            // ADC FACTOR HssSense_3
        0u,                                               // ADC FACTOR PosSensor
      { 6273u,  6273u,  0u },                             // ADC FACTOR Vccx
      { 0u, 0u, 0u, 0u },                                 // ADC FACTOR In
        24643u,                                           // ADC FACTOR OutFct
        0u                                                // ADC FACTOR Vboost
      }
    }
    }
};

boolean boFlag;

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUser_Init
///
/// \Test Case Description
///        - Test subject: Test if function initializes private variables
///                        and call the internal functions
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Initialize all IoHwAbUser Buffers
///         Step2: Filter initialization
///         Step3: Get EftData
///         Step4: Get Voltage NTC
///         Step5: Call the function
///         Step6: Check all the initializations
///
/// - Preconditions:
///
/// \input  Adc_ReadGroup_Param2                        = 0u
///
/// - Expectations:
///
/// \output IoHwAbUser_unFactorVBAT                      = 24642u
/// \output IoHwAbUser_aulRingBuff[0]                    = 0u
/// \output IoHwAbUser_ulVBatMean                        = 0u
/// \output IoHwAbUser_ulVBatMins                        = 0u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_Init(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Adc_ReadGroup_Param2 = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_Init();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_aulRingBuff[0u], 0u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_unFactorVBAT, 24643u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_ulVBatMean, 0u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_ulVBatMin, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUser_DeInit_TestCase_1
///
/// \Test Case Description
///        - Test subject: Calling the function only for coverage
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Call the function
///
/// - Preconditions:
///
/// \input  -
///
/// - Expectations:
///
/// \output -
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_DeInit(void)
{
  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_DeInit();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUser_Cycle_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function is reading the ADC Raw value of ECU Temperature
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Gets adc raw value of hss sensors and then filter them
///         Step2: ADC measurement for High Side Switch
///         Step4: Calculate the mean value of the battery voltage and send it to the RTE.
///         Step5: Calculate the analog sensor value for pitch
///         Step6: DTC checking
///         Step7: Get voltage for each EXT NTC and PCB
///         Step8: Get voltage for each EXT NTC and PCB
///         Step9: Check the physical calculated value is correct based on the ADC Raw value
///
/// - Preconditions:
///
/// \input  IoHwAbUser_aulRingBuff[ulIndex]                                  = 10u
/// \input  Rte_Write_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount                  = 0u
/// \input  IoHwAbUser_CheckSens1_OpenLoad_RetVal                            = 40u
/// \input  IoHwAbUser_CheckSens0_OpenLoad_RetVal                            = 5u
/// \input  IoHwAbUser_ucMeasMode                                            = 1u
/// \input  IoHwAbUser_ucMeasCycle                                           = 1u
/// \input  Icu_GetMeasurementSens_HitCount                                  = 0u
/// \input  Icu_GetMeasurementSens_RetVal                                    = 1000u
/// \input  Icu_ChangeMeasurementMode_HitCount                               = 0u
/// \input  Mt_IoHwAb_FTM0Register                                           = 5u
/// \input  Mt_IoHwAb_FTM4Register                                           = 5u
/// \input  Mt_IoHwAb_CHOV_BitStatus                                         = 8u
/// \input  IoHwAbUser_unSensMeasPeriodAndDuty[0][0]                         = 5u
/// \input  IoHwAbUser_unSensMeasPeriodAndDuty[1][0]                         = 5u
/// \input  IoHwAbUser_unSensCalculatedDuty[0]                               = 20u
/// \input  IoHwAbUser_unSensCalculatedDuty[1]                               = 10u
/// \input  Dem_SetEventStatus_HitCount                                      = 0u
/// \input  IoHwAbUser_ulMountingSideRaw                                     = IOHWABUSER_MOUNTINGSIDERAW_LEFT
/// \input  Dem_SetEventStatus_Param1                                        = 0u
/// \input  Dem_SetEventStatus_Param2                                        = 0u
///
/// - Expectations:
///
/// \output IoHwAbUser_ulVBatMean                                            = 1329u
/// \output Rte_Write_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount                  = 11u
/// \output Dem_SetEventStatus_Param1                                        = LR_Detect
/// \output Dem_SetEventStatus_Param2                                        = DEM_EVENT_STATUS_PASSED
/// \output Dem_SetEventStatus_HitCount                                      = 1u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_Cycle_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  for (uint32 ulIndex = 0U; ulIndex < IOHWABUSER_RINGBUFFER_SIZE; ulIndex++)
  {
    IoHwAbUser_aulRingBuff[ulIndex] = 2048U; // raw value for ~12
  }
  boFlag = TRUE;
  Adc_ReadGroup_Param2 = 2048U;
  Rte_Write_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 0u;
  IoHwAbUser_CheckSens1_OpenLoad_RetVal = 40u;
  IoHwAbUser_CheckSens0_OpenLoad_RetVal = 5u;
  IoHwAbUser_ucMeasMode = 1u;
  IoHwAbUser_ucMeasCycle = 1u;
  Icu_GetMeasurementSens_HitCount = 0u;
  Icu_GetMeasurementSens_RetVal = 1000u;
  Icu_ChangeMeasurementMode_HitCount = 0u;
  Mt_IoHwAb_FTM0Register = 5u;
  Mt_IoHwAb_FTM4Register = 5u;
  Mt_IoHwAb_CHOV_BitStatus = 8u;
  IoHwAbUser_unSensMeasPeriodAndDuty[0][0] = 5u;
  IoHwAbUser_unSensMeasPeriodAndDuty[1][0] = 5u;
  IoHwAbUser_unSensCalculatedDuty[0] = 10u;
  IoHwAbUser_unSensCalculatedDuty[1] = 10u;
  Dem_SetEventStatus_HitCount = 0u;
  IoHwAbUser_ulMountingSideRaw = IOHWABUSER_MOUNTINGSIDERAW_LEFT;
  Dem_SetEventStatus_Param1 = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_Cycle();
  IoHwAbUser_Cycle();
  IoHwAbUser_Cycle();
  IoHwAbUser_Cycle();
  IoHwAbUser_Cycle();
  IoHwAbUser_Cycle();
  IoHwAbUser_Cycle();
  IoHwAbUser_Cycle();
  IoHwAbUser_Cycle();
  IoHwAbUser_Cycle();
  IoHwAbUser_Cycle();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_ulVBatMean, 12324u, == );
  AL_UNITTEST_CHECK(Rte_Write_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, LR_Detect, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, DEM_EVENT_STATUS_PASSED, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUser_Cycle_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function is reading the ADC Raw value of ECU Temperature
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Gets adc raw value of hss sensors and then filter them
///         Step2: ADC measurement for High Side Switch
///         Step4: Calculate the mean value of the battery voltage and send it to the RTE.
///         Step5: Calculate the analog sensor value for pitch
///         Step6: DTC checking
///         Step7: Get voltage for each EXT NTC and PCB
///         Step8: Get voltage for each EXT NTC and PCB
///         Step9: Check the physical calculated value is correct based on the ADC Raw value
///
/// - Preconditions:
///
/// \input  IoHwAbUser_aulRingBuff[ulIndex]                                  = 10u
/// \input  Rte_Write_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount                  = 0u
/// \input  IoHwAbUser_CheckSens1_OpenLoad_RetVal                            = 40u
/// \input  IoHwAbUser_CheckSens0_OpenLoad_RetVal                            = 5u
/// \input  IoHwAbUser_ucMeasMode                                            = 1u
/// \input  IoHwAbUser_ucMeasCycle                                           = 1u
/// \input  Icu_GetMeasurementSens_HitCount                                  = 0u
/// \input  Icu_GetMeasurementSens_RetVal                                    = 1000u
/// \input  Icu_ChangeMeasurementMode_HitCount                               = 0u
/// \input  Mt_IoHwAb_FTM0Register                                           = 5u
/// \input  Mt_IoHwAb_FTM4Register                                           = 5u
/// \input  Mt_IoHwAb_CHOV_BitStatus                                         = 8u
/// \input  IoHwAbUser_unSensMeasPeriodAndDuty[0][0]                         = 5u
/// \input  IoHwAbUser_unSensMeasPeriodAndDuty[1][0]                         = 5u
/// \input  IoHwAbUser_unSensCalculatedDuty[0]                               = 20u
/// \input  IoHwAbUser_unSensCalculatedDuty[1]                               = 10u
/// \input  Dem_SetEventStatus_HitCount                                      = 0u
/// \input  Dem_SetEventStatus_Param1                                        = 0u
/// \input  Dem_SetEventStatus_Param2                                        = 0u
/// \input  IoHwAbUser_ulMountingSideRaw                                     = 255u
///
/// - Expectations:
///
/// \output IoHwAbUser_ulVBatMean                                            = 192u
/// \output Rte_Write_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount                  = 100u
/// \output Dem_SetEventStatus_Param1                                        = LR_Detect
/// \output Dem_SetEventStatus_Param2                                        = DEM_EVENT_STATUS_FAILED
/// \output Dem_SetEventStatus_HitCount                                      = 11u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_Cycle_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  for (uint32 ulIndex = 0U; ulIndex < IOHWABUSER_RINGBUFFER_SIZE; ulIndex++)
  {
    IoHwAbUser_aulRingBuff[ulIndex] = 0u;
  }
  boFlag = FALSE;

  Adc_ReadGroup_Param2 = 2048U;
  Rte_Write_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 0u;
  IoHwAbUser_CheckSens1_OpenLoad_RetVal = 40u;
  IoHwAbUser_CheckSens0_OpenLoad_RetVal = 5u;
  IoHwAbUser_ucMeasMode = 1u;
  IoHwAbUser_ucMeasCycle = 1u;
  Icu_GetMeasurementSens_HitCount = 0u;
  Icu_GetMeasurementSens_RetVal = 1000u;
  Icu_ChangeMeasurementMode_HitCount = 0u;
  Mt_IoHwAb_FTM0Register = 5;
  Mt_IoHwAb_FTM4Register = 5;
  Mt_IoHwAb_CHOV_BitStatus = 8;
  IoHwAbUser_unSensMeasPeriodAndDuty[0][0] = 5u;
  IoHwAbUser_unSensMeasPeriodAndDuty[1][0] = 5u;
  IoHwAbUser_unSensCalculatedDuty[0] = 10u;
  IoHwAbUser_unSensCalculatedDuty[1] = 10u;
  IoHwAbUser_ulMountingSideRaw = 255u;
  Dem_SetEventStatus_Param1 = 0u;
  Dem_SetEventStatus_Param2 = 0u;


  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------


  for (uint8 ucIdx = 0u; ucIdx < 100u; ucIdx++)
  {
    IoHwAbUser_Cycle();
  }

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_ulVBatMean, 12324u, == );
  AL_UNITTEST_CHECK(Rte_Write_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount, 10u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, LR_Detect, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, DEM_EVENT_STATUS_FAILED, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 11u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUser_Cycle_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function is reading the ADC Raw value of ECU Temperature
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Gets adc raw value of hss sensors and then filter them
///         Step2: ADC measurement for High Side Switch
///         Step4: Calculate the mean value of the battery voltage and send it to the RTE.
///         Step5: Calculate the analog sensor value for pitch
///         Step6: DTC checking
///         Step7: Get voltage for each EXT NTC and PCB
///         Step8: Get voltage for each EXT NTC and PCB
///         Step9: Check the physical calculated value is correct based on the ADC Raw value
///
/// - Preconditions:
///
/// \input  IoHwAbUser_aulRingBuff[ulIndex]                                  = 10u
/// \input  Rte_Write_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount                  = 0u
/// \input  IoHwAbUser_CheckSens1_OpenLoad_RetVal                            = 40u
/// \input  IoHwAbUser_CheckSens0_OpenLoad_RetVal                            = 5u
/// \input  IoHwAbUser_ucMeasMode                                            = 1u
/// \input  IoHwAbUser_ucMeasCycle                                           = 1u
/// \input  Icu_GetMeasurementSens_HitCount                                  = 0u
/// \input  Icu_GetMeasurementSens_RetVal                                    = 1000u
/// \input  Icu_ChangeMeasurementMode_HitCount                               = 0u
/// \input  Mt_IoHwAb_FTM0Register                                           = 5u
/// \input  Mt_IoHwAb_FTM4Register                                           = 5u
/// \input  Mt_IoHwAb_CHOV_BitStatus                                         = 8u
/// \input  IoHwAbUser_unSensMeasPeriodAndDuty[0][0]                         = 5u
/// \input  IoHwAbUser_unSensMeasPeriodAndDuty[1][0]                         = 5u
/// \input  IoHwAbUser_unSensCalculatedDuty[0]                               = 20u
/// \input  IoHwAbUser_unSensCalculatedDuty[1]                               = 10u
/// \input  Dem_SetEventStatus_Param1                                        = 0u
/// \input  Dem_SetEventStatus_Param2                                        = 0u
/// \input  Dem_SetEventStatus_HitCount                                      = 0u
/// \input  IoHwAbUser_ulMountingSideRaw                                     = IOHWABUSER_MOUNTINGSIDERAW_LEFT
///
/// - Expectations:
///
/// \output IoHwAbUser_ulVBatMean                                            = 18661u
/// \output Rte_Write_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount                  = 1u
/// \output Dem_SetEventStatus_Param1                                        = 0u
/// \output Dem_SetEventStatus_Param2                                        = 0u
/// \output Dem_SetEventStatus_HitCount                                      = 0u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_Cycle_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  for (uint32 ulIndex = 0U; ulIndex < IOHWABUSER_RINGBUFFER_SIZE; ulIndex++)
  {
    IoHwAbUser_aulRingBuff[ulIndex] = 2048u;
  }
  Adc_ReadGroup_Param2 = 1U;
  Adc_ReadGroup_Param2 = 2048U;
  Rte_Write_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 0u;
  IoHwAbUser_CheckSens1_OpenLoad_RetVal = 40u;
  IoHwAbUser_CheckSens0_OpenLoad_RetVal = 5u;
  IoHwAbUser_ucMeasMode = 1u;
  IoHwAbUser_ucMeasCycle = 1u;
  Icu_GetMeasurementSens_HitCount = 0u;
  Icu_GetMeasurementSens_RetVal = 1000u;
  Icu_ChangeMeasurementMode_HitCount = 0u;
  Mt_IoHwAb_FTM0Register = 5;
  Mt_IoHwAb_FTM4Register = 5;
  Mt_IoHwAb_CHOV_BitStatus = 8;
  IoHwAbUser_unSensMeasPeriodAndDuty[0][0] = 5u;
  IoHwAbUser_unSensMeasPeriodAndDuty[1][0] = 5u;
  IoHwAbUser_unSensCalculatedDuty[0] = 10u;
  IoHwAbUser_unSensCalculatedDuty[1] = 10u;
  Dem_SetEventStatus_Param1 = 0u;
  Dem_SetEventStatus_Param2 = 0u;
  Dem_SetEventStatus_HitCount = 0u;
  IoHwAbUser_ulMountingSideRaw = IOHWABUSER_MOUNTINGSIDERAW_LEFT;


  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_Cycle();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_ulVBatMean, 12324u, == );
  AL_UNITTEST_CHECK(Rte_Write_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount, 0u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, 0u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, 0u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUser_Cycle_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test if function is the cyclic function doesn't perform LSS diagnostic
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set global LSS diagnostic flag as false
///         Step2: Check the CddSBC PWM getter hitcount. It shall be 0.
///
/// - Preconditions:
///
/// \input  IoHwAb_boLssDiagnostic                                           = FALSE
/// \input  CddSbc_GetPWM_HitCount                                           = 0u
/// \input  CddSbc_GetPWM_Param1                                             = 0xFFu
///
/// - Expectations:
///
/// \output IoHwAb_boLssDiagnostic                                           = FALSE
/// \output CddSbc_GetPWM_HitCount                                           = 0u
/// \output CddSbc_GetPWM_Param1                                             = 0xFFu
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_Cycle_TestCase_4(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAb_boLssDiagnostic = FALSE;
  CddSbc_GetPWM_HitCount = 0u;
  CddSbc_GetPWM_Param1 = 0xFFu;


  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_Cycle();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAb_boLssDiagnostic, FALSE, == );
  AL_UNITTEST_CHECK(CddSbc_GetPWM_HitCount, 0u, == );
  AL_UNITTEST_CHECK(CddSbc_GetPWM_Param1, 0xFFu, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUser_Cycle_TestCase_5
///
/// \Test Case Description
///        - Test subject: est if function is the cyclic function performs LSS diagnostic
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set global LSS diagnostic flag as true
///         Step2: Check the CddSBC PWM getter hitcount. It shall be 1.
///
/// - Preconditions:
///
/// \input  IoHwAb_boLssDiagnostic                                           = TRUE
/// \input  CddSbc_GetPWM_HitCount                                           = 0u
/// \input  CddSbc_GetPWM_Param1                                             = 0xFFu
/// - Expectations:
///
/// \output IoHwAb_boLssDiagnostic                                           = TRUE
/// \output CddSbc_GetPWM_HitCount                                           = 1u
/// \output CddSbc_GetPWM_Param1                                             = 0u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_Cycle_TestCase_5(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAb_boLssDiagnostic = TRUE;
  CddSbc_GetPWM_HitCount = 0u;
  CddSbc_GetPWM_Param1 = 0xFFu;


  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_Cycle();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAb_boLssDiagnostic, TRUE, == );
  AL_UNITTEST_CHECK(CddSbc_GetPWM_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CddSbc_GetPWM_Param1, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_IoHwAb_IoHwAbUser_Cycle
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Tests the cyclic function
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_Cycle(void)
{
  Mt_IoHwAb_IoHwAbUser_Cycle_TestCase_1();
  Mt_IoHwAb_IoHwAbUser_Cycle_TestCase_2();
  Mt_IoHwAb_IoHwAbUser_Cycle_TestCase_3();
  Mt_IoHwAb_IoHwAbUser_Cycle_TestCase_4();
  Mt_IoHwAb_IoHwAbUser_Cycle_TestCase_5();
}


// This function is needed to test Mt_IoHwAb_IoHwAbUser_InitGetMountingSide_TestCase_x
void Mt_IoHwAbuser_GetMountingSideMemoryValue(uint32* Mt_IoHwAbuser_MTMemoryValue)
{
  Mt_IoHwAbuser_MTMemoryValue[0] = Mt_IoHwAbUserMTValue.MT_MEM_ADDR_LR_DET;
  Mt_IoHwAbuser_MTMemoryValue[1] = Mt_IoHwAbUserMTValue.MT_MEM_ADDR_LR_DET_INV;
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUser_InitGetMountingSide_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function accesses the memory once when initialization
///                        and determines whether the mounting side of the ECU
///
/// \FuSa Relevant: ASIL B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the Mounting Side Memory value to right
///         Step2: Set the Inverted Mounting Side Memory value to right
///         Step3: Call the BSW-Interface IoHwAbUser_InitGetMountingSide() function
///         Step4: Check the Mounting side value is set to the right
///
/// - Preconditions:
///
/// \input  Mt_IoHwAbUserMTValue.MT_MEM_ADDR_LR_DET                                = 0x0202U
/// \input  Mt_IoHwAbUserMTValue.MT_MEM_ADDR_LR_DET_INV                            = 0xFDFDU
/// \input  IoHwAbUser_ulMountingSideRaw                                           = 0x0000u
/// \input  Rte_Write_IoHwAbUser_GetMountingSide_HitCount                          = 0u
///
/// - Expectations:
///
/// \output IoHwAbUser_ulMountingSideRaw                                           = IOHWABUSER_MOUNTINGSIDERAW_RIGHT
/// \output Rte_Write_IoHwAbUser_GetMountingSide_HitCount                          = 1u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_InitGetMountingSide_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Mt_IoHwAbUserMTValue.MT_MEM_ADDR_LR_DET = 0x0202U;
  Mt_IoHwAbUserMTValue.MT_MEM_ADDR_LR_DET_INV = 0xFDFDU;
  IoHwAbUser_ulMountingSideRaw = 0x0000u;
  Rte_Write_IoHwAbUser_GetMountingSide_HitCount = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_InitGetMountingSide();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_ulMountingSideRaw, IOHWABUSER_MOUNTINGSIDERAW_RIGHT, == );
  AL_UNITTEST_CHECK(Rte_Write_IoHwAbUser_GetMountingSide_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUser_InitGetMountingSide_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function accesses the memory once when initialization
///                        and determines whether the mounting side of the ECU
///
/// \FuSa Relevant: ASIL B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the Mounting Side Memory value to left
///         Step2: Set the Inverted Mounting Side Memory value to left
///         Step3: Call the BSW-Interface IoHwAbUser_InitGetMountingSide() function
///         Step4: Check the Mounting side value is set to the left
///
/// - Preconditions:
///
/// \input  Mt_IoHwAbUserMTValue.MT_MEM_ADDR_LR_DET                                = 0x0101U
/// \input  Mt_IoHwAbUserMTValue.MT_MEM_ADDR_LR_DET_INV                            = 0xFEFEU
/// \input  IoHwAbUser_ulMountingSideRaw                                           = 0x0000u
/// \input  Rte_Write_IoHwAbUser_GetMountingSide_HitCount                          = 0u
///
/// - Expectations:
///
/// \output IoHwAbUser_ulMountingSideRaw                                           = IOHWABUSER_MOUNTINGSIDERAW_LEFT
/// \output Rte_Write_IoHwAbUser_GetMountingSide_HitCount                          = 1u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_InitGetMountingSide_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Mt_IoHwAbUserMTValue.MT_MEM_ADDR_LR_DET = 0x0101U;
  Mt_IoHwAbUserMTValue.MT_MEM_ADDR_LR_DET_INV = 0xFEFEU;
  IoHwAbUser_ulMountingSideRaw = 0x0000u;
  Rte_Write_IoHwAbUser_GetMountingSide_HitCount = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_InitGetMountingSide();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_ulMountingSideRaw, IOHWABUSER_MOUNTINGSIDERAW_LEFT, == );
  AL_UNITTEST_CHECK(Rte_Write_IoHwAbUser_GetMountingSide_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUser_InitGetMountingSide_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function accesses the memory once when initialization
///                        and determines whether the mounting side of the ECU
///
/// \FuSa Relevant: ASIL B
///
/// \Used Test method: Requirements-based test, Fault injection
///
/// \Steps:
///         Step1: Set the Mounting Side Memory value to an invalid value
///         Step2: Set the Inverted Mounting Side Memory value to an invalid value
///         Step3: Call the BSW-Interface IoHwAbUser_InitGetMountingSide() function
///         Step4: Check the fault branch of the injection by setting the value of the memory address to UNKNOWN
///         Step5: Check the Mounting side value is set to the unknown
///
/// - Preconditions:
///
/// \input  Mt_IoHwAbUserMTValue.MT_MEM_ADDR_LR_DET                                = 0x0303U
/// \input  Mt_IoHwAbUserMTValue.MT_MEM_ADDR_LR_DET_INV                            = 0xFCFCU
/// \input  IoHwAbUser_ulMountingSideRaw                                           = 0x0000u
/// \input  Rte_Write_IoHwAbUser_GetMountingSide_HitCount                          = 0u
///
/// - Expectations:
///
/// \output IoHwAbUser_ulMountingSideRaw                                           = IOHWABUSER_MOUNTINGSIDERAW_UNKNOW
/// \output Rte_Write_IoHwAbUser_GetMountingSide_HitCount                          = 1u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_InitGetMountingSide_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Mt_IoHwAbUserMTValue.MT_MEM_ADDR_LR_DET = 0x0303U;
  Mt_IoHwAbUserMTValue.MT_MEM_ADDR_LR_DET_INV = 0xFCFCU;
  IoHwAbUser_ulMountingSideRaw = 0x0000u;
  Rte_Write_IoHwAbUser_GetMountingSide_HitCount = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_InitGetMountingSide();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_ulMountingSideRaw, IOHWABUSER_MOUNTINGSIDERAW_UNKNOW, == );
  AL_UNITTEST_CHECK(Rte_Write_IoHwAbUser_GetMountingSide_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUser_InitGetMountingSide_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test if function accesses the memory once when initialization
///                        and determines whether the mounting side of the ECU
///
/// \FuSa Relevant: ASIL B
///
/// \Used Test method: Requirements-based test, Fault injection
///
/// \Steps:
///         Step1: Set the Mounting Side Memory value to right 
///         Step2: Set the Inverted Mounting Side Memory value to left
///         Step3: Call the BSW-Interface IoHwAbUser_InitGetMountingSide() function
///         Step4: Check the fault branch of the injection by setting the value of the memory address to right and the inverted value of the memory address to left
///         Step5: Check the Mounting side value is set to the default value : RIGHT
///
/// - Preconditions:
///
/// \input  Mt_IoHwAbUserMTValue.MT_MEM_ADDR_LR_DET                                = 0x0202U
/// \input  Mt_IoHwAbUserMTValue.MT_MEM_ADDR_LR_DET_INV                            = 0xFCFCU
/// \input  IoHwAbUser_ulMountingSideRaw                                           = 0x0000u
/// \input  Rte_Write_IoHwAbUser_GetMountingSide_HitCount                          = 0u
///
/// - Expectations:
///
/// \output IoHwAbUser_ulMountingSideRaw                                           = IOHWABUSER_MOUNTINGSIDERAW_RIGHT
/// \output Rte_Write_IoHwAbUser_GetMountingSide_HitCount                          = 1u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_InitGetMountingSide_TestCase_4(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Mt_IoHwAbUserMTValue.MT_MEM_ADDR_LR_DET = 0x0202U;
  Mt_IoHwAbUserMTValue.MT_MEM_ADDR_LR_DET_INV = 0xFCFCU;
  IoHwAbUser_ulMountingSideRaw = 0x0000u;
  Rte_Write_IoHwAbUser_GetMountingSide_HitCount = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_InitGetMountingSide();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_ulMountingSideRaw, IOHWABUSER_MOUNTINGSIDERAW_RIGHT, == );
  AL_UNITTEST_CHECK(Rte_Write_IoHwAbUser_GetMountingSide_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_IoHwAb_IoHwAbUser_InitGetMountingSide
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Tests the mounting side init function
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_InitGetMountingSide(void)
{
  Mt_IoHwAb_IoHwAbUser_InitGetMountingSide_TestCase_1();
  Mt_IoHwAb_IoHwAbUser_InitGetMountingSide_TestCase_2();
  Mt_IoHwAb_IoHwAbUser_InitGetMountingSide_TestCase_3();
  Mt_IoHwAb_IoHwAbUser_InitGetMountingSide_TestCase_4();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUser_HSSOperation_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function change the DIO
///
/// \FuSa Relevant: -
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the initialization flag to false
///         Step2: Call the function
///         Step3: Check the waiting time and the toggle flag
///
/// - Preconditions:
///
/// \input  IoHwAbUser_HSSOperation_Param1                                                  = 1u
///
/// - Expectations:
///
/// \output IoHwAbUser_sHssDioInfo.ucWaitingTime                                              = 0u
/// \output IoHwAbUser_sHssDioInfo.boDioSel0Toggle                                            = FALSE
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_HSSOperation_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_HSSOperation_Param1 = 1u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_HSSOperation(IoHwAbUser_HSSOperation_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_sHssDioInfo.ucWaitingTime, 0u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_sHssDioInfo.boDioSel0Toggle, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUser_HSSOperation_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function change the DIO
///
/// \FuSa Relevant: -
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the initialization flag to true
///         Step2: Set the waiting time to 0
///         Step3: Call the function
///         Step4: Check the waiting time increments
///
/// - Preconditions:
///
/// \input  IoHwAbUser_HSSOperation_Param1                                                    = 0u
///
/// - Expectations:
///
/// \output IoHwAbUser_sHssDioInfo.ucWaitingTime                                              = 1u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_HSSOperation_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_HSSOperation_Param1 = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_HSSOperation(IoHwAbUser_HSSOperation_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_sHssDioInfo.ucWaitingTime, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUser_HSSOperation_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function change the DIO
///
/// \FuSa Relevant: -
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the initialization flag to true
///         Step2: Set the waiting time variable to 5ms after finishing the HSS voltage measurement process
///         Step3: Call the function
///         Step4: Check the toggling flag changed
///
/// - Preconditions:
///
/// \input  IoHwAbUser_HSSOperation_Param1                                                    = 0u
/// \input  IoHwAbUser_sHssDioInfo.ucWaitingTime                                              = IOHWABUSER_HSS_ADC_WAIT_TIME_30MS
/// \input  IoHwAbUser_sHssDioInfo.boDioSel0Toggle                                            = FALSE
///
/// - Expectations:
///
/// \output IoHwAbUser_sHssDioInfo.boDioSel0Toggle                                             = TRUE
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_HSSOperation_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_HSSOperation_Param1 = 0u;
  IoHwAbUser_sHssDioInfo.ucWaitingTime = IOHWABUSER_HSS_ADC_WAIT_TIME_30MS;
  IoHwAbUser_sHssDioInfo.boDioSel0Toggle = FALSE;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_HSSOperation(IoHwAbUser_HSSOperation_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_sHssDioInfo.boDioSel0Toggle, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUser_HSSOperation_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test if function change the DIO
///
/// \FuSa Relevant: -
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the initialization flag to true
///         Step2: Set the waiting time variable to 5ms after finishing the HSS voltage measurement process
///         Step3: Call the function
///         Step4: Check the toggling flag changed
///
/// - Preconditions:
///
/// \input  IoHwAbUser_HSSOperation_Param1                                                    = 0u
/// \input  IoHwAbUser_sHssDioInfo.ucWaitingTime                                              = IOHWABUSER_HSS_ADC_WAIT_TIME_30MS
/// \input  IoHwAbUser_sHssDioInfo.boDioSel0Toggle                                            = TRUE
///
/// - Expectations:
///
/// \output IoHwAbUser_sHssDioInfo.boDioSel0Toggle                                             = FALSE
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_HSSOperation_TestCase_4(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_HSSOperation_Param1 = 0u;
  IoHwAbUser_sHssDioInfo.ucWaitingTime = IOHWABUSER_HSS_ADC_WAIT_TIME_30MS;
  IoHwAbUser_sHssDioInfo.boDioSel0Toggle = TRUE;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_HSSOperation(IoHwAbUser_HSSOperation_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_sHssDioInfo.boDioSel0Toggle, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_IoHwAb_IoHwAbUser_HSSOperation
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Tests the HSS operation function
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_HSSOperation(void)
{
  Mt_IoHwAb_IoHwAbUser_HSSOperation_TestCase_1();
  Mt_IoHwAb_IoHwAbUser_HSSOperation_TestCase_2();
  Mt_IoHwAb_IoHwAbUser_HSSOperation_TestCase_3();
  Mt_IoHwAb_IoHwAbUser_HSSOperation_TestCase_4();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUser_GetMountingSideRaw
///
/// \Test Case Description
///        - Test subject: function sends the initially stored mounting side value to the RTE.
///
/// \FuSa Relevant: ASIL B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Initialize the mounting side when raw function is called for the first time
///         Step2: Send the stored mounting side raw value to RTE
///
/// - Preconditions:
///
/// \input  IoHwAbUser_ulMountingSideRaw                                = 1u
/// \input  Mt_IoHwAbUserMTValue.MT_MEM_ADDR_LR_DET                     = 1u
/// \input  Mt_IoHwAbUserMTValue.MT_MEM_ADDR_LR_DET_INV                 = 1u
///
/// - Expectations:
///
/// \output -IoHwAbUser_GetMountingSideRaw_Param1                      = 1u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_GetMountingSideRaw(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_ulMountingSideRaw = 1u;
  Mt_IoHwAbUserMTValue.MT_MEM_ADDR_LR_DET = 0x0101U;
  Mt_IoHwAbUserMTValue.MT_MEM_ADDR_LR_DET_INV = 0xFEFEU;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_GetMountingSideRaw(&IoHwAbUser_GetMountingSideRaw_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_GetMountingSideRaw_Param1, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUser_SetBoostMode
///
/// \Test Case Description
///        - Test subject: Test if sets the requested LED Boost mode value
///
/// \FuSa Relevant:-
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the Boost Mode value
///         Step2: Call the BSW-Interface IoHwAbUser_SetBoostMode()
///         Step3: Check the enable and disable value of the Dio channel and PWM value in Boost Mode variable
///
/// - Preconditions:
///
/// \input IoHwAbUser_SetBoostMode_Param1 = 0u
///
/// - Expectations:
///
/// \output Dio_WriteChannel_Param2       = 0u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_SetBoostMode(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetBoostMode_Param1 = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetBoostMode(IoHwAbUser_SetBoostMode_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Dio_WriteChannel_Param2, 0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUser_SetHss_En1_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if sets the requested High Side Switch
///                        value to Enable or Disable
///
/// \FuSa Relevant:-
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the High Side Switch value
///         Step2: Call the BSW-Interface IoHwAbUser_SetHss_En1()
///         Step3: Check the enable and disable value of the Dio channel and PWM value in High Side Switch variable
///
/// - Preconditions:
///
/// \input IoHwAbUser_SetHss_En1_Param1    = IOHWABUSER_MAX_TARGET_VALUE
///
/// - Expectations:
///
/// \output Dio_WriteChannel_Param2        = 1u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_SetHss_En1_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetHss_En1_Param1 = IOHWABUSER_MAX_TARGET_VALUE;


  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetHss_En1(IoHwAbUser_SetHss_En1_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Dio_WriteChannel_Param2, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUser_SetHss_En1_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if sets the requested High Side Switch
///                        value to Enable or Disable
///
/// \FuSa Relevant:-
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the High Side Switch value
///         Step2: Call the BSW-Interface IoHwAbUser_SetHss_En1()
///         Step3: Check the enable and disable value of the Dio channel and PWM value in High Side Switch variable
///
/// - Preconditions:
///
/// \input IoHwAbUser_SetHss_En1_Param1 = 0u
///
/// - Expectations:
///
/// \output Dio_WriteChannel_Param2     = 0u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_SetHss_En1_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetHss_En1_Param1 = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetHss_En1(IoHwAbUser_SetHss_En1_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Dio_WriteChannel_Param2, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_IoHwAb_IoHwAbUser_SetHss_En1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Tests the HSS enable function
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_SetHss_En1(void)
{
  Mt_IoHwAb_IoHwAbUser_SetHss_En1_TestCase_1();
  Mt_IoHwAb_IoHwAbUser_SetHss_En1_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUser_SetHss_En2_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if sets the requested High Side Switch
///                        value to Enable or Disable
///
/// \FuSa Relevant:-
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the High Side Switch value
///         Step2: Call the BSW-Interface IoHwAbUser_SetHss_En2()
///         Step3: Check the enable and disable value of the Dio channel and PWM value in High Side Switch variable
///
/// - Preconditions:
///
/// \input IoHwAbUser_SetHss_En2_Param1    = 1u
///
/// - Expectations:
///
/// \output Dio_WriteChannel_Param2        = 0u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_SetHss_En2_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetHss_En2_Param1 = 1u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetHss_En2(IoHwAbUser_SetHss_En2_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Dio_WriteChannel_Param2, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUser_SetHss_En2_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if sets the requested High Side Switch
///                        value to Enable or Disable
///
/// \FuSa Relevant:-
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the High Side Switch value
///         Step2: Call the BSW-Interface IoHwAbUser_SetHss_En2()
///         Step3: Check the enable and disable value of the Dio channel and PWM value in High Side Switch variable
///
/// - Preconditions:
///
/// \input IoHwAbUser_SetHss_En2_Param1   = IOHWABUSER_MAX_TARGET_VALUE
///
/// - Expectations:
///
/// \output Dio_WriteChannel_Param2        = 1u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_SetHss_En2_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetHss_En2_Param1 = IOHWABUSER_MAX_TARGET_VALUE;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetHss_En2(IoHwAbUser_SetHss_En2_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Dio_WriteChannel_Param2, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_IoHwAb_IoHwAbUser_SetHss_En2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Tests the HSS enable function
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_SetHss_En2(void)
{
  Mt_IoHwAb_IoHwAbUser_SetHss_En2_TestCase_1();
  Mt_IoHwAb_IoHwAbUser_SetHss_En2_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUser_SetHss_En3_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if sets the requested High Side Switch
///                        value to Enable or Disable
///
/// \FuSa Relevant:-
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the High Side Switch value
///         Step2: Call the BSW-Interface IoHwAbUser_SetHss_En3()
///         Step3: Check the enable and disable value of the Dio channel and PWM value in High Side Switch variable
///
/// - Preconditions:
///
/// \input IoHwAbUser_SetHss_En3_Param1    = IOHWABUSER_MAX_TARGET_VALUE
///
/// - Expectations:
///
/// \output Pwm_SetDutyCycle_Param2        = 1u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_SetHss_En3_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetHss_En3_Param1 = IOHWABUSER_MAX_TARGET_VALUE;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetHss_En3(IoHwAbUser_SetHss_En3_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Dio_WriteChannel_Param2, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUser_SetHss_En3_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if sets the requested High Side Switch
///                        value to Enable or Disable
///
/// \FuSa Relevant:-
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the High Side Switch value
///         Step2: Call the BSW-Interface IoHwAbUser_SetHss_En3()
///         Step3: Check the enable and disable value of the Dio channel and PWM value in High Side Switch variable
///
/// - Preconditions:
///
/// \input IoHwAbUser_SetHss_En3_Param1    = 0u
///
/// - Expectations:
///
/// \output Pwm_SetDutyCycle_Param2        = 0u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_SetHss_En3_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetHss_En3_Param1 = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetHss_En3(IoHwAbUser_SetHss_En3_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_Param2, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUser_SetHss_En3_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if sets the requested High Side Switch
///                        value to Enable or Disable
///
/// \FuSa Relevant:-
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the High Side Switch value
///         Step2: Call the BSW-Interface IoHwAbUser_SetHss_En3()
///         Step3: Check the enable and disable value of the Dio channel and PWM value in High Side Switch variable
///
/// - Preconditions:
///
/// \input IoHwAbUser_SetHss_En3_Param1    = 32769u
///
/// - Expectations:
///
/// \output Pwm_SetDutyCycle_Param2        = 32768u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_SetHss_En3_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetHss_En3_Param1 = 32769u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetHss_En3(IoHwAbUser_SetHss_En3_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Dio_WriteChannel_Param2, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_IoHwAb_IoHwAbUser_SetHss_En3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Tests the HSS enable function
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_SetHss_En3(void)
{
  Mt_IoHwAb_IoHwAbUser_SetHss_En3_TestCase_1();
  Mt_IoHwAb_IoHwAbUser_SetHss_En3_TestCase_2();
  Mt_IoHwAb_IoHwAbUser_SetHss_En3_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUser_SetHss_Error
///
/// \Test Case Description
///        - Test subject: Test if sets the requested Fault Reset
///                        value to Enable or Disable
///
/// \FuSa Relevant:-
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the Fault Reset value
///         Step2: Call the BSW-Interface IoHwAbUser_SetHss_Error()
///         Step3: Check the enable and disable value of the Dio channel and PWM value in Fault Reset variable
///
/// - Preconditions:
///
/// \input IoHwAbUser_SetHss_Error_Param1  = 1u
///
/// - Expectations:
///
/// \output Dio_WriteChannel_Param2        = 1u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_SetHss_Error(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetHss_Error_Param1 = 1u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetHss_Error(IoHwAbUser_SetHss_Error_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Dio_WriteChannel_Param2, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUser_SetHss_Sel1
///
/// \Test Case Description
///        - Test subject: Test if sets the requested High Side Switch Sel1
///                        value to Enable or Disable
///
/// \FuSa Relevant:-
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the High Side Switch Sel1 value
///         Step2: Call the BSW-Interface IoHwAbUser_SetHss_Sel1()
///         Step3: Check the enable and disable value of the Dio channel and PWM value in High Side Switch Sel1 variable
///
/// - Preconditions:
///
/// \input IoHwAbUser_SetHss_Sel1_Param1   = 1u
///
/// - Expectations:
///
/// \output Dio_WriteChannel_Param2        = 1u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_SetHss_Sel1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetHss_Sel1_Param1 = 1u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetHss_Sel1(IoHwAbUser_SetHss_Sel1_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Dio_WriteChannel_Param2, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUser_SetHss_Sel2
///
/// \Test Case Description
///        - Test subject: Test if sets the requested High Side Switch
///                        value to Enable or Disable
///
/// \FuSa Relevant:-
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the High Side Switch Sel1 value
///         Step2: Call the BSW-Interface IoHwAbUser_SetHss_Sel1()
///         Step3: Check the enable and disable value of the Dio channel and PWM value in High Side Switch Sel1 variable
///
/// - Preconditions:
///
/// \input IoHwAbUser_SetHss_Sel2_Param1  = 1u
///
/// - Expectations:
///
/// \output Dio_WriteChannel_Param2        = 1u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_SetHss_Sel2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetHss_Sel2_Param1 = 1u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetHss_Sel2(IoHwAbUser_SetHss_Sel2_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Dio_WriteChannel_Param2, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUser_SetHss_Sen
///
/// \Test Case Description
///        - Test subject: Test if sets the requested High Side Switch
///                        value to Enable or Disable
///
/// \FuSa Relevant:-
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the High Side Switch Sen value
///         Step2: Call the BSW-Interface IoHwAbUser_SetHss_Sen()
///         Step3: Check the enable and disable value of the Dio channel and PWM value in High Side Switch Sen variable
///
/// - Preconditions:
///
/// \input IoHwAbUser_SetHss_Sen_Param1    = 1u
///
/// - Expectations:
///
/// \output Dio_WriteChannel_Param2        = 1u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_SetHss_Sen(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetHss_Sen_Param1 = 1u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetHss_Sen(IoHwAbUser_SetHss_Sen_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Dio_WriteChannel_Param2, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUser_ResetHss
///
/// \Test Case Description
///        - Test subject: Test if sets the reset value of the requested
///                        High Side Switch.
///
/// \FuSa Relevant:-
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the requested High Side Switch Reset value
///         Step2: Call the BSW-Interface IoHwAbUser_ResetHss()
///         Step3: Check the enable and disable value of the Dio channel and PWM value in equested High Side Switch Reset variable
///
/// - Preconditions:
///
/// \input IoHwAbUser_ResetHss_Param1     = 2u
///
/// - Expectations:
///
/// \output Dio_WriteChannel_Param2        = 2u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_ResetHss(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_ResetHss_Param1 = 2u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_ResetHss(IoHwAbUser_ResetHss_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Dio_WriteChannel_Param2, 2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUser_SenseEnableHss
///
/// \Test Case Description
///        - Test subject: Test if the function  sets the Sense value of the requested
///                        High Side Switch.
///
/// \FuSa Relevant:-
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the Sense value of the requested High Side Switch.
///         Step2: Call the BSW-Interface IoHwAbUser_SenseEnableHss()
///         Step3: Check the enable and disable value of the Dio channel and PWM value in Sense value of the requested High Side Switch variable
///
/// - Preconditions:
///
/// \input IoHwAbUser_SenseEnableHss_Param1  = 2u
///
/// - Expectations:
///
/// \output Dio_WriteChannel_Param2          = 2u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_SenseEnableHss(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_SenseEnableHss_Param1 = 2u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_SenseEnableHss(IoHwAbUser_SenseEnableHss_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Dio_WriteChannel_Param2, 2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUser_SetDirLwr
///
/// \Test Case Description
///        - Test subject: Test if the function to set the direction pin of the LWR Stepper driver
///
/// \FuSa Relevant:-
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the Sense value of the LWR stepper driver
///         Step2: Call the BSW-Interface IoHwAbUser_SetDirLwr()
///         Step3: Check the enable and disable value of the Dio channel and PWM value in Sense value of the LWR stepper driver variable
///
/// - Preconditions:

///
/// \input IoHwAbUser_SetDirLwr_Param1     = 2u
///
/// - Expectations:
///
/// \output Dio_WriteChannel_Param2        = 2u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_SetDirLwr(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetDirLwr_Param1 = 2u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetDirLwr(IoHwAbUser_SetDirLwr_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Dio_WriteChannel_Param2, 2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUser_SetLwrSleep
///
/// \Test Case Description
///        - Test subject: test if the function sets the driver off pin of the LWR Stepper driver
///
/// \FuSa Relevant:-
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the Sense value of the LWR stepper driver
///         Step2: Call the BSW-Interface IoHwAbUser_SetDirLwr()
///         Step3: Check the enable and disable value of the Dio channel and PWM value in Sense value of the LWR stepper driver variable
///
/// - Preconditions:
///
/// \input IoHwAbUser_SetLwrSleep_Param1   = 2u
///
/// - Expectations:
///
/// \output Dio_WriteChannel_Param2        = 2u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_SetLwrSleep(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetLwrSleep_Param1 = 2u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetLwrSleep(IoHwAbUser_SetLwrSleep_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Dio_WriteChannel_Param2, 2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUser_SetLwrDrvOff
///
/// \Test Case Description
///        - Test subject:Test if sets the driver off pin of the LWR Stepper driver
///
/// \FuSa Relevant:-
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the Sense value of the LWR stepper driver
///         Step2: Call the BSW-Interface IoHwAbUser_SetDirLwr()
///         Step3: Check the enable and disable value of the Dio channel and PWM value in Sense value of the LWR stepper driver variable
///
/// - Preconditions:
///
/// \input IoHwAbUser_SetLwrDrvOff_Param1  = 0u
///
/// - Expectations:
///
/// \output Dio_WriteChannel_Param2        = 0u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_SetLwrDrvOff(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetLwrDrvOff_Param1 = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetLwrDrvOff(IoHwAbUser_SetLwrDrvOff_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Dio_WriteChannel_Param2, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUser_SetVccxEn
///
/// \Test Case Description
///        - Test subject: Test if sets the requested Vccx value to enable or disable
///
/// \FuSa Relevant:-
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the value of the Vccx pin 
///         Step2: Call the BSW-Interface IoHwAbUser_SetVccxEn()
///         Step3: Check the enable and disable value of the Dio channel and Vccx variable
///
/// - Preconditions:
///
/// \input IoHwAbUser_SetVccxEn_Param1     = 0u
///
/// - Expectations:
///
/// \output Dio_WriteChannel_Param2        = 0u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_SetVccxEn(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetVccxEn_Param1 = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetVccxEn(IoHwAbUser_SetVccxEn_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Dio_WriteChannel_Param2, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUserTimer0Notification_TestCase_1
///
/// \Test Case Description
///        - Test subject: sets the driver off pin of the LWR Stepper driver
///
/// \FuSa Relevant:-
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the element variable to 40
///         Step2: Set the Adc Raw Value of VBat and save it in the Ring Buffer
///         Step3: Call the BSW-Interface IoHwAbUserTimer0Notification()
///         Step4: Check the first element of the ring buffer
///
/// - Preconditions:
///
/// \input Adc_ReadGroup_HitCount             = 0u
/// \input Adc_ReadGroup_Param2               = 30u
/// \input IoHwAbUser_ucRingBuffElem          = 40u
///
/// - Expectations:
///
/// \output Adc_ReadGroup_HitCount            = 1u
/// \output IoHwAbUser_aulRingBuff[0u]        = 30u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUserTimer0Notification_TestCase_1(void)
{

  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_ucRingBuffElem = 40u;
  Adc_ReadGroup_HitCount = 0u;
  Adc_ReadGroup_Param2 = 30u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUserTimer0Notification();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Adc_ReadGroup_HitCount, 1u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_aulRingBuff[0u], 30u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUserTimer0Notification_TestCase_2
///
/// \Test Case Description
///        - Test subject: sets the driver off pin of the LWR Stepper driver
///
/// \FuSa Relevant:-
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the element variable to 40
///         Step2: Set the Adc Raw Value of VBat and save it in the Ring Buffer
///         Step3: Call the BSW-Interface IoHwAbUserTimer0Notification()
///         Step4: Check the first element of the ring buffer
///
/// - Preconditions:
///
/// \input Adc_ReadGroup_HitCount             = 0u
/// \input Adc_ReadGroup_Param2               = 30u
/// \input IoHwAbUser_ucRingBuffElem          = 40u
///
/// - Expectations:
///
/// \output Adc_ReadGroup_HitCount            = 1u
/// \output IoHwAbUser_aulRingBuff[0u]        = 30u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUserTimer0Notification_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_ucRingBuffElem = 40u;
  Adc_ReadGroup_HitCount = 0u;
  Adc_ReadGroup_Param2 = 30u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUserTimer0Notification();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Adc_ReadGroup_HitCount, 1u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_aulRingBuff[0u], 30u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUserTimer0Notification_TestCase_3
///
/// \Test Case Description
///        - Test subject: sets the driver off pin of the LWR Stepper driver
///
/// \FuSa Relevant:-
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the element variable to 40
///         Step2: Set the Adc Raw Value of VBat and save it in the Ring Buffer
///         Step3: Call the BSW-Interface IoHwAbUserTimer0Notification()
///         Step4: Check the first element of the ring buffer
///
/// - Preconditions:
///
/// \input Adc_ReadGroup_HitCount        = 0u
/// \input Adc_ReadGroup_Param2          = 30u
/// \input Adc_ReadGroup_Param2          = 37u
///
/// - Expectations:
///
/// \output IoHwAbUser_aulRingBuff[1u]      = 37u
/// \output Adc_ReadGroup_HitCount          = 2u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUserTimer0Notification_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_ucRingBuffElem = 40u;
  Adc_ReadGroup_HitCount = 0u;
  Adc_ReadGroup_Param2 = 30u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUserTimer0Notification();
  Adc_ReadGroup_Param2 = 37u;
  IoHwAbUserTimer0Notification();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_aulRingBuff[1u], 37u, == );
  AL_UNITTEST_CHECK(Adc_ReadGroup_HitCount, 2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_IoHwAb_IoHwAbUserTimer0Notification
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Tests the Timer notification function
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUserTimer0Notification(void)
{
  Mt_IoHwAb_IoHwAbUserTimer0Notification_TestCase_1();
  Mt_IoHwAb_IoHwAbUserTimer0Notification_TestCase_2();
  Mt_IoHwAb_IoHwAbUserTimer0Notification_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUser_CalcVBatMeanValue_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function calculates the mean value of VBat
///
/// \FuSa Relevant:-
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Sum all values from buffer
///         Step2: Calculate the mean voltage value and send it to the RTE
///         Step3: Call the BSW-Interface IoHwAbUser_CalcVBatMeanValue()
///         Step4: Check the value of the mean vbat
///
/// - Preconditions:
///
/// \input Rte_Write_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount            = 0u
/// \input IoHwAbUser_aulRingBuff[ucIndex]                            = 35u
///
/// - Expectations:
///
/// \output Rte_Write_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount             = 1u
/// \output IoHwAbUser_ulVBatMean                                       = 6739u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_CalcVBatMeanValue_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Rte_Write_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 0u;

  for (uint16 ucIndex = 0u; ucIndex < IOHWABUSER_RINGBUFFER_SIZE; ucIndex++)
  {
    IoHwAbUser_aulRingBuff[ucIndex] = 2048u;
  }

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_CalcVBatMeanValue();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Rte_Write_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount, 1u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_ulVBatMean, 12324u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUser_CalcVBatMeanValue_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function calculates the mean value of VBat
///
/// \FuSa Relevant:-
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Sum all values from buffer
///         Step2: Calculate the mean voltage value and send it to the RTE
///         Step3: Call the BSW-Interface IoHwAbUser_CalcVBatMeanValue()
///         Step4: Check the value of the mean vbat
///
/// - Preconditions:
///
/// \input Rte_Write_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount               = 0u
/// \input IoHwAbUser_aulRingBuff[0u]                                    = 0u
/// \input IoHwAbUser_aulRingBuff[ucIndex]                               = 100u
///
/// - Expectations:
///
/// \output Rte_Write_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount             = 1u
/// \output IoHwAbUser_ulVBatMean                                       = 18655u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_CalcVBatMeanValue_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Rte_Write_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 0u;


  for (uint16 ucIndex = 0u; ucIndex < IOHWABUSER_RINGBUFFER_SIZE; ucIndex += 2)
  {
    IoHwAbUser_aulRingBuff[ucIndex] = 0u;
    IoHwAbUser_aulRingBuff[ucIndex + 1] = 2048u;
  }

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_CalcVBatMeanValue();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Rte_Write_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount, 1u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_ulVBatMean, 6162, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_IoHwAb_IoHwAbUser_CalcVBatMeanValue
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function calculates the mean value of VBat
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_CalcVBatMeanValue(void)
{
  Mt_IoHwAb_IoHwAbUser_CalcVBatMeanValue_TestCase_1();
  Mt_IoHwAb_IoHwAbUser_CalcVBatMeanValue_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUser_HSSOperationForEcuHighVar_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function calculates the mean value of VBat
///
/// \FuSa Relevant:-
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the raw value of the filter value of HSS1_2 Sensor, HSS3 Sensor
///         Step2: Set the value for voltage for double channel high-side switch 1_2, switch 3
///         Step3: Sum all values from buffer
///         Step4: Call the BSW-Interface IoHwAbUser_HSSOperationForEcuHighVar()
///         Step5: Check the value of HSSSensorVoltage, toggling flag
///
/// - Preconditions:
///
/// \input Order1FilterValue_HitCount                                                = 0u
/// \input Order1FilterValue_Param1                                                  = 100u
/// \input Order1FilterValue_RetVal                                                  = 100u
/// \input IoHwAbUser_unFactorHssSenseS1_2                                           = 200u
/// \input IoHwAbUser_unFactorHssSense3                                              = 250u
/// \input IoHwAbUser_sHssDioInfo.boDioSel0Toggle                                    = FALSE
///
/// - Expectations:
///
/// \output Order1FilterValue_HitCount                                               = 2u
/// \output IoHwAbUser_aulHSSSensorVoltage[0u]                                       = 4u
/// \output IoHwAbUser_aulHSSSensorVoltage[2u]                                       = 6u
/// \output IoHwAbUser_sHssDioInfo.boDioSel0Toggle                                   = TRUE
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_HSSOperationForEcuHighVar_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Order1FilterValue_HitCount = 0u;
  Order1FilterValue_Param1 = 100u;
  Order1FilterValue_RetVal = 100u;
  IoHwAbUser_sHssDioInfo.boDioSel0Toggle = FALSE;
  IoHwAbUser_unFactorHssSenseS1_2 = 200u;
  IoHwAbUser_unFactorHssSense3 = 250u;

  for (uint16 ucIndex = 1u; ucIndex < IOHWABUSER_RINGBUFFER_SIZE; ucIndex++)
  {
    IoHwAbUser_aulRingBuff[ucIndex] = 100u;
  }

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_HSSOperationForEcuHighVar();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Order1FilterValue_HitCount, 2u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_aulHSSSensorVoltage[0u], 4u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_aulHSSSensorVoltage[2u], 6u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_sHssDioInfo.boDioSel0Toggle, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUser_HSSOperationForEcuHighVar_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function calculates ADC Value of High Side Switch for High ECU
///
/// \FuSa Relevant:-
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the raw value of the filter value of HSS1_2 Sensor, HSS3 Sensor
///         Step2: Set the value for voltage for double channel high-side switch 1_2, switch 3
///         Step3: Sum all values from buffer
///         Step4: Call the BSW-Interface IoHwAbUser_HSSOperationForEcuHighVar()
///         Step5: Check the value of HSSSensorVoltage, toggling flag
///
/// - Preconditions:
///
/// \input Order1FilterValue_HitCount                                             = 0u
/// \input Order1FilterValue_Param1                                               = 100u
/// \input Order1FilterValue_RetVal                                               = 100u
/// \input IoHwAbUser_aulRingBuff[ucIndex]                                        = 100u
/// \input IoHwAbUser_unFactorHssSenseS1_2                                        = 200u
/// \input IoHwAbUser_sHssDioInfo.boDioSel0Toggle                                 = TRUE
///
/// - Expectations:
///
/// \output Order1FilterValue_HitCount                                            = 1u
/// \output IoHwAbUser_aulHSSSensorVoltage[1u]                                    = 4u
/// \output IoHwAbUser_sHssDioInfo.boDioSel0Toggle                                = FALSE
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_HSSOperationForEcuHighVar_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Order1FilterValue_HitCount = 0u;
  Order1FilterValue_Param1 = 100u;
  Order1FilterValue_RetVal = 100u;
  IoHwAbUser_sHssDioInfo.boDioSel0Toggle = TRUE;
  IoHwAbUser_unFactorHssSenseS1_2 = 200u;

  for (uint16 ucIndex = 1u; ucIndex < IOHWABUSER_RINGBUFFER_SIZE; ucIndex++)
  {
    IoHwAbUser_aulRingBuff[ucIndex] = 100u;
  }

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_HSSOperationForEcuHighVar();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Order1FilterValue_HitCount, 2u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_aulHSSSensorVoltage[1u], 4u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_sHssDioInfo.boDioSel0Toggle, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_IoHwAb_IoHwAbUser_HSSOperationForEcuHighVar
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function calculates ADC Value of High Side Switch for High ECU
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_HSSOperationForEcuHighVar(void)
{
  Mt_IoHwAb_IoHwAbUser_HSSOperationForEcuHighVar_TestCase_1();
  Mt_IoHwAb_IoHwAbUser_HSSOperationForEcuHighVar_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUser_InitializeBuffers
///
/// \Test Case Description
///        - Test subject: Test if function initializes all buffers
///
/// \FuSa Relevant:-
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the actual voltage value from the Adc Port and initialize the Ring Buffer with this value
///         Step2: Fill the voltage ring buffer with the stored AdcRaw VBAT values
///         Step3: Call the BSW-Interface IoHwAbUser_InitializeBuffers()
///         Step4: Check the value of each buffer element
///
/// - Preconditions:
///
/// \input Adc_ReadGroup_HitCount                                             = 0u
/// \input Adc_ReadGroup_Param2                                               = 100u
///
/// - Expectations:
///
/// \output Adc_ReadGroup_HitCount                                            = 1u
/// \output IoHwAbUser_aulRingBuff[ucIndex]                                   = 100u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_InitializeBuffers(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Adc_ReadGroup_HitCount = 0u;
  Adc_ReadGroup_Param2 = 100u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_InitializeBuffers();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Adc_ReadGroup_HitCount, 1u, == );

  for (uint16 ucIndex = 0; ucIndex < IOHWABUSER_RINGBUFFER_SIZE; ucIndex++)
  {
    AL_UNITTEST_CHECK(IoHwAbUser_aulRingBuff[ucIndex], 100u, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUser_FilterInitialization
///
/// \Test Case Description
///        - Test subject: Test if function makes the initialization of filters
///
/// \FuSa Relevant:-
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the filter coefficient of HSS filter
///         Step2: Set the Raw value of Hss Adc raw values
///         Step3: Initialize the HSS filter
///         Step4: Initialize PCB Temp Filter
///         Step5: Initialize VCCX1 Temp Filter
///         Step6: Initialize Ext NTC Filter
///         Step7: Set the Adc Raw data for NTC
///         Step8: Call the BSW-Interface IoHwAbUser_FilterInitialization()
///         Step9: Check the filters were initialized
///
/// - Preconditions:
///
/// \input Adc_ReadGroup_HitCount                                             = 0u
/// \input Adc_ReadGroup_Param2                                               = 70u
/// \input Order1FilterInit_HitCount                                          = 0u
/// \input Order1FilterInit_Param1                                            = 100u
/// \input Order1FilterInit_Param2                                            = 0u
/// \input Order1FilterGetCoef_HitCount                                       = 100u
/// \input Order1FilterGetCoef_Param1                                         = 0u
/// \input Order1FilterGetCoef_Param2                                         = 100u
/// \input Order1FilterGetCoef_RetVal                                         = 400u
/// \input Adc_ReadGroup_Param2                                               = 100u
/// \input IoHwAbUser_unFilterCoefHssSenseS1_2                                = 100u
///
/// - Expectations:
///
/// \output Adc_ReadGroup_HitCount                                            = 18u
/// \output Order1FilterInit_HitCount                                         = 18u
/// \output Order1FilterGetCoef_HitCount                                      = 5u
/// \output IoHwAbUser_unFilterCoefHssSenseS1_2                               = 400u
/// \output IoHwAbUser_unFilterCoefHssSenseS3                                 = 400u
/// \output IoHwAbUser_unFilterCoefPCB                                        = 400u
/// \output IoHwAbUser_unFilterCoefNTC1_12                                    = 400u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_FilterInitialization(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Adc_ReadGroup_HitCount = 0u;
  Adc_ReadGroup_Param2 = 70u;
  Order1FilterInit_HitCount = 0u;
  Order1FilterInit_Param1 = 100u;
  Order1FilterInit_Param2 = 200u;
  Order1FilterGetCoef_HitCount = 0u;
  Order1FilterGetCoef_Param1 = 100u;
  Order1FilterGetCoef_Param2 = 100u;
  Order1FilterGetCoef_RetVal = 400u;
  Adc_ReadGroup_Param2 = 100u;
  IoHwAbUser_unFilterCoefHssSenseS1_2 = 100u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_FilterInitialization();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Adc_ReadGroup_HitCount, 18u, == );
  AL_UNITTEST_CHECK(Order1FilterInit_HitCount, 18u, == );
  AL_UNITTEST_CHECK(Order1FilterGetCoef_HitCount, 5u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_unFilterCoefHssSenseS1_2, 400u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_unFilterCoefHssSenseS3, 400u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_unFilterCoefPCB, 400u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_unFilterCoefNTC, 400u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_riIoHwAbUserInit
///
/// \Test Case Description
///        - Test subject: Test if function initializes runnable for IoHwAbUser
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Initialize all IoHwAbUser Buffers
///         Step2: Filter initialization
///         Step3: Get EftData
///         Step4: Get Voltage NTC
///         Step5: Call the runnable
///         Step6: Check all the initializations
///
/// - Preconditions:
///
/// \input Adc_ReadGroup_Param1                           = IOHWABUSER_ADC_GROUP_CHANNEL_MAP_ADC_VBAT
/// \input Adc_ReadGroup_Param2                           = 1023u
///
/// - Expectations:
///
/// \output IoHwAbUser_ulVBatMean                         = 6156u
/// \output IoHwAbUser_ulVBatMin                          = 0u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_riIoHwAbUserInit(void)
{
  Adc_ReadGroup_Param1 = IOHWABUSER_ADC_GROUP_CHANNEL_MAP_ADC_VBAT;
  Adc_ReadGroup_Param2 = 1023u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  riIoHwAbUserInit();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_ulVBatMean, 6156u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_ulVBatMin, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_riIoHwAbUserDeInit
///
/// \Test Case Description
///        - Test subject: Test if function deinitializes runnable for IoHwAbUser
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Call the runnable
///
/// - Preconditions:
///
/// \input -
///
/// - Expectations:
///
/// \output -
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_riIoHwAbUserDeInit(void)
{
  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  riIoHwAbUserDeInit();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_rpIoHwAbUser_Cycle
///
/// \Test Case Description
///        - Test subject: Test if function calls cyclic IoHwAbUser_Cycle
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Gets adc raw value of hss sensors and then filter them
///         Step2: ADC measurement for High Side Switch
///         Step4: Calculate the mean value of the battery voltage and send it to the RTE.
///         Step5: Calculate the analog sensor value for pitch
///         Step6: DTC checking
///         Step7: Get voltage for each EXT NTC and PCB
///         Step8: Call th runnable
///         Step9: Check the physical calculated value is correct based on the ADC Raw value
///
/// - Preconditions:
///
/// \input IoHwAbUser_aulRingBuff[ulIndex]                                              = 10u
/// \input Rte_Write_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount                              = 0u
///
/// - Expectations:
///
/// \output IoHwAbUser_ulVBatMean                                                      = 2467u
/// \output Rte_Write_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount                            = 1u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_rpIoHwAbUser_Cycle(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  uint32 ulSaveIoHwAbUser_ulVBatMean = IoHwAbUser_ulVBatMean;
  for (uint32 ulIndex = 0U; ulIndex < IOHWABUSER_RINGBUFFER_SIZE; ulIndex++)
  {
    IoHwAbUser_aulRingBuff[ulIndex] = 2048u;
  }

  Rte_Write_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------
  rpIoHwAbUser_Cycle(); // is not expected to be recalculated the VBAT mean

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_ulVBatMean, ulSaveIoHwAbUser_ulVBatMean, == );
  AL_UNITTEST_CHECK(Rte_Write_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUser_Set_Vccx_State_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function sets Vccx ON or OFF
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Turn Vccx OFF
///         Step2: Set Vccx2 flag to FALSE
///         Step3: Call IoHwAbUser_Set_Vccx_State
///         Step4: Check if the flag for VccxStatus
///
/// - Preconditions:
///
/// \input IoHwAbUser_Set_Vccx_State_Param1                            = FALSE
///
/// - Expectations:
///
/// \output IoHwAbUser_boVccxStatus                                     = FALSE
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_Set_Vccx_State_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_Set_Vccx_State_Param1 = FALSE;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_Set_Vccx_State(IoHwAbUser_Set_Vccx_State_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_boVccxStatus, FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUser_Set_Vccx_State_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function sets Vccx ON or OFF
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1a: Turn Vccx ON
///         Step1b: Set invalid Vbat Voltage
///         Step2: Set Vccx2 flag to FALSE
///         Step3: Set VCXX2 to STD_LOW
///         Step4: Call IoHwAbUser_Set_Vccx_State
///         Step5: Check if the flag for VccxStatus
///
/// - Preconditions:
///
/// \input IoHwAbUser_Set_Vccx_State_Param1                            = TRUE
/// \input IoHwAbUser_ulVBatMean                                       = 3000u
///
/// - Expectations:
///
/// \output IoHwAbUser_boVccxStatus                                     = FALSE
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_Set_Vccx_State_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_Set_Vccx_State_Param1 = TRUE;
  IoHwAbUser_ulVBatMean = 3000u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_Set_Vccx_State(IoHwAbUser_Set_Vccx_State_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_boVccxStatus, FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAb_IoHwAbUser_Set_Vccx_State_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function sets Vccx ON or OFF
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1a: Turn Vccx ON
///         Step1b: Set valid Vbat voltage
///         Step2: Set Vccx2 flag to TRUE
///         Step3: Set VCXX2 to STD_HIGH
///         Step4: Call IoHwAbUser_Set_Vccx_State
///         Step5: Check if the flag for VccxStatus
///
/// - Preconditions:
///
/// \input IoHwAbUser_Set_Vccx_State_Param1                            = TRUE
/// \input IoHwAbUser_ulVBatMean                                       = 7000u
///
/// - Expectations:
///
/// \output IoHwAbUser_boVccxStatus                                     = TRUE
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_Set_Vccx_State_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_Set_Vccx_State_Param1 = TRUE;
  IoHwAbUser_ulVBatMean = 7000u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_Set_Vccx_State(IoHwAbUser_Set_Vccx_State_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_boVccxStatus, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_IoHwAb_IoHwAbUser_Set_Vccx_State
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function sets Vccx ON or OFF
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_Set_Vccx_State(void)
{
  Mt_IoHwAb_IoHwAbUser_Set_Vccx_State_TestCase_1();
  Mt_IoHwAb_IoHwAbUser_Set_Vccx_State_TestCase_2();
  Mt_IoHwAb_IoHwAbUser_Set_Vccx_State_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAbIoHwAbUser_VccxStateCyclicCheck_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if diagnostic funtion is not active till VCCX_EN is set (IoHwAbUser_boVccxStatus == TRUE)
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set VCCX2 enable status false and not requested
///         Step2: Set actual error stats as short to Gnd
///         Step3: Check that nothing changed since diagnostic is not enabled
///
/// - Preconditions:
///
/// \input IoHwAbUser_boVccxStatus                              = FALSE
/// \input boVccx2_en_state                                     = FALSE
/// \input Rte_Write_IoHwAbUser_VccxLineState_Param1    = eVccx_Short2GND
/// \input Rte_Write_IoHwAbUser_VccxLineState_HitCount  =  0
///
/// - Expectations:
///
/// \output Rte_Write_IoHwAbUser_VccxLineState_Param1   = eVccx_Short2GND
/// \output Rte_Write_IoHwAbUser_VccxLineState_HitCount = 1
///
//-----------------------------------------------------------------------------
void Mt_IoHwAbIoHwAbUser_VccxStateCyclicCheck_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_boVccxStatus = FALSE;
  boVccx2_en_state = FALSE;
  Rte_Write_IoHwAbUser_VccxLineState_Param1 = eVccx_Short2GND;
  Rte_Write_IoHwAbUser_VccxLineState_HitCount = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_VccxStateCyclicCheck();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Rte_Write_IoHwAbUser_VccxLineState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_IoHwAbUser_VccxLineState_Param1, eVccx_noError, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAbIoHwAbUser_VccxStateCyclicCheck_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function sets enable the timer for diagnostc delay of 5ms after VCCX2_EN is set
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set VCCX2 enable status true and not active
///         Step2: Set actual error stats as short to Gnd
///         Step3: Check that delay timer is started and as VCCX2 error nothing changed (noe error) (diagnostic still closed)
///
/// - Preconditions:
///
/// \input IoHwAbUser_boVccxStatus                              = TRUE
/// \input boVccx2_en_state                                     = FALSE
/// \input Rte_Write_IoHwAbUser_VccxLineState_Param1    = eVccx_Short2GND
/// \input Rte_Write_IoHwAbUser_VccxLineState_HitCount  = 0
/// \input LPTMR0_GetTimeElapsed_HitCount                       = 0
/// \input LPTMR0_GetTimeElapsed_RetVal                         = 0
///
/// - Expectations:
///
/// \output Rte_Write_IoHwAbUser_VccxLineState_Param1   = eVccx_noError
/// \output Rte_Write_IoHwAbUser_VccxLineState_HitCount = 1
/// \output boVccx2_en_state = TRUE
/// \output LPTMR0_GetTimeElapsed_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAbIoHwAbUser_VccxStateCyclicCheck_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_boVccxStatus = TRUE;
  boVccx2_en_state = FALSE;
  Rte_Write_IoHwAbUser_VccxLineState_Param1 = eVccx_Short2GND;
  Rte_Write_IoHwAbUser_VccxLineState_HitCount = 0u;
  LPTMR0_GetTimeElapsed_HitCount = 0u;
  LPTMR0_GetTimeElapsed_RetVal = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_VccxStateCyclicCheck();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Rte_Write_IoHwAbUser_VccxLineState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_IoHwAbUser_VccxLineState_Param1, eVccx_noError, == );
  AL_UNITTEST_CHECK(boVccx2_en_state, TRUE, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount, 1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAbIoHwAbUser_VccxStateCyclicCheck_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function check the timer time-out to start the diagnosys (5ms) after VCCX2_EN is set but timer not expired
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set VCCX2 enable status true and not active
///         Step2: Set actual error stats as short to Gnd
///         Step3: Check that delay timer time-out not happend for diagnostic start and nothing changed (no error) as error status (diagnostic still closed)
///
/// - Preconditions:
///
///
/// \input IoHwAbUser_boVccxStatus                              = FALSE
/// \input boVccx2_en_state                                     = TRUE
/// \input Rte_Write_IoHwAbUser_VccxLineState_Param1    = eVccx_Short2GND
/// \input Rte_Write_IoHwAbUser_VccxLineState_HitCount  = 0
/// \input LPTMR0_GetTimeElapsed_HitCount                       = 0
/// \input LPTMR0_GetTimeElapsed_RetVal                         = 0
///
/// - Expectations:
///
/// \output Rte_Write_IoHwAbUser_VccxLineState_Param1   = eVccx_noError
/// \output Rte_Write_IoHwAbUser_VccxLineState_HitCount = 1
/// \output boVccx2_en_state = FALSE
/// \output LPTMR0_GetTimeElapsed_HitCount = 0u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAbIoHwAbUser_VccxStateCyclicCheck_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_boVccxStatus = FALSE;
  boVccx2_en_state = TRUE;
  Rte_Write_IoHwAbUser_VccxLineState_Param1 = eVccx_Short2GND;
  Rte_Write_IoHwAbUser_VccxLineState_HitCount = 0u;
  LPTMR0_GetTimeElapsed_HitCount = 0u;
  LPTMR0_GetTimeElapsed_RetVal = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_VccxStateCyclicCheck();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Rte_Write_IoHwAbUser_VccxLineState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_IoHwAbUser_VccxLineState_Param1, eVccx_noError, == );
  AL_UNITTEST_CHECK(boVccx2_en_state, FALSE, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount, 0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAbIoHwAbUser_VccxStateCyclicCheck_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test if function check the timer time-out to start the diagnosys (5ms) after VCCX2_EN is set and timer expired - diagnostic start
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set VCCX2 enable status true and active
///         Step2: Set actual error stats as short to Gnd
///         Step3: Check that delay timer time-out  happend for diagnostic start and nothing changed (no error) as error status (diagnostic still closed)
///
/// - Preconditions:
///
///
/// \input IoHwAbUser_boVccxStatus                              = TRUE
/// \input boVccx2_en_state                                     = TRUE
/// \input ulVccx2_Diag_Timer                                   = 30000u
/// \input Rte_Write_IoHwAbUser_VccxLineState_Param1    = eVccx_Short2GND
/// \input Rte_Write_IoHwAbUser_VccxLineState_HitCount  = 0
/// \input LPTMR0_GetTimeElapsed_HitCount                       = 0
/// \input LPTMR0_GetTimeElapsed_RetVal                         = 29900u
///
/// - Expectations:
///
/// \output Rte_Write_IoHwAbUser_VccxLineState_Param1   = eVccx_noError
/// \output Rte_Write_IoHwAbUser_VccxLineState_HitCount = 1
/// \output boVccx2_en_state = TRUE
/// \output LPTMR0_GetTimeElapsed_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAbIoHwAbUser_VccxStateCyclicCheck_TestCase_4(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_boVccxStatus = TRUE;
  boVccx2_en_state = TRUE;
  ulVccx2_Diag_Timer = 30000u;
  Rte_Write_IoHwAbUser_VccxLineState_Param1 = eVccx_Short2GND;
  Rte_Write_IoHwAbUser_VccxLineState_HitCount = 0u;
  LPTMR0_GetTimeElapsed_HitCount = 0u;
  LPTMR0_GetTimeElapsed_RetVal = 29900u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_VccxStateCyclicCheck();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Rte_Write_IoHwAbUser_VccxLineState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_IoHwAbUser_VccxLineState_Param1, eVccx_noError, == );
  AL_UNITTEST_CHECK(boVccx2_en_state, TRUE, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAbIoHwAbUser_VccxStateCyclicCheck_TestCase_5
///
/// \Test Case Description
///        - Test subject: Test if function check the timer time-out to start the diagnosys (5ms) after VCCX2_EN is set and timer expired - diagnostic start and power good = 1 (power ok)
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set VCCX2 enable status true and active
///         Step2: Set actual error stats as short to Gnd
///         Step3: Check that delay timer time-out  happend for diagnostic start
///         Step4: Check that no error is reported due the PG is ok 
///
/// - Preconditions:
///
///
/// \input IoHwAbUser_boVccxStatus                              = TRUE
/// \input boVccx2_en_state                                     = TRUE
/// \input ulVccx2_Diag_Timer                                   = 30000u
/// \input Rte_Write_IoHwAbUser_VccxLineState_Param1    = eVccx_Short2GND
/// \input Rte_Write_IoHwAbUser_VccxLineState_HitCount  = 0
/// \input LPTMR0_GetTimeElapsed_HitCount                       = 0
/// \input LPTMR0_GetTimeElapsed_RetVal                         = 32000u
/// \input Dio_ReadChannel_HitCount                             = 0u
/// \input Dio_ReadChannel_Param1                               = 0u
/// \input Dio_ReadChannel_RetVal                               = STD_HIGH
/// \input Dem_SetEventStatus_Param1                            = 0u
/// \input Dem_SetEventStatus_Param2                            = 0u
/// \input Dem_SetEventStatus_HitCount                          = 0u
///
/// - Expectations:
///
/// \output Rte_Write_IoHwAbUser_VccxLineState_Param1   = eVccx_noError
/// \output Rte_Write_IoHwAbUser_VccxLineState_HitCount = 1
/// \output boVccx2_en_state = TRUE
/// \output LPTMR0_GetTimeElapsed_HitCount = 1u
/// \output Dio_ReadChannel_HitCount = 1u
/// \output Dem_SetEventStatus_Param1 = VCCX2_SC_BAT
/// \output Dem_SetEventStatus_Param2 = DEM_EVENT_STATUS_PASSED
/// \output Dem_SetEventStatus_HitCount = 2u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAbIoHwAbUser_VccxStateCyclicCheck_TestCase_5(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_boVccxStatus = TRUE;
  boVccx2_en_state = TRUE;
  ulVccx2_Diag_Timer = 30000u;
  Rte_Write_IoHwAbUser_VccxLineState_Param1 = eVccx_Short2GND;
  Rte_Write_IoHwAbUser_VccxLineState_HitCount = 0u;
  LPTMR0_GetTimeElapsed_HitCount = 0u;
  LPTMR0_GetTimeElapsed_RetVal = 32000;
  Dio_ReadChannel_HitCount = 0u;
  Dio_ReadChannel_Param1 = 0u;
  Dio_ReadChannel_RetVal = STD_HIGH;
  Dem_SetEventStatus_Param1 = 0u;
  Dem_SetEventStatus_Param2 = 0u;
  Dem_SetEventStatus_HitCount = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_VccxStateCyclicCheck();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Rte_Write_IoHwAbUser_VccxLineState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_IoHwAbUser_VccxLineState_Param1, eVccx_noError, == );
  AL_UNITTEST_CHECK(boVccx2_en_state, TRUE, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dio_ReadChannel_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, VCCX2_SC_BAT, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, DEM_EVENT_STATUS_PASSED, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAbIoHwAbUser_VccxStateCyclicCheck_TestCase_6
///
/// \Test Case Description
///        - Test subject: Test if function check the timer time-out to start the diagnosys (5ms) after VCCX2_EN is set and timer expired - diagnostic start and power good = 0 (power not_ok)
///                        The ADC reads the VCCX2 and detects 20mv on output (Short2Gnd)
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
/// \Steps:
///         Step1: Set VCCX2 enable status true and active
///         Step2: Set actual error stats as Vccx_noError
///         Step3: Check that delay timer time-out  happend for diagnostic start
///         Step4: Check that Short2Gnd error is reported due the PG is not_ok and ADC returns 20mV 
///
/// - Preconditions:
///
///
/// \input IoHwAbUser_boVccxStatus                              = TRUE
/// \input boVccx2_en_state                                     = TRUE
/// \input ulVccx2_Diag_Timer                                   = 30000u
/// \input Rte_Write_IoHwAbUser_VccxLineState_Param1    = eVccx_noError
/// \input Rte_Write_IoHwAbUser_VccxLineState_HitCount  = 0
/// \input LPTMR0_GetTimeElapsed_HitCount                       = 0
/// \input LPTMR0_GetTimeElapsed_RetVal                         = 32000u
/// \input Dio_ReadChannel_HitCount                             = 0u
/// \input Dio_ReadChannel_Param1                               = 0u
/// \input Dio_ReadChannel_RetVal                               = STD_LOW
/// \input Adc_ReadGroup_Param2                                 = 20u
/// \input Dem_SetEventStatus_Param1                            = 0u
/// \input Dem_SetEventStatus_Param2                            = 0u
/// \input Dem_SetEventStatus_HitCount                          = 0u
///
/// - Expectations:
///
/// \output Rte_Write_IoHwAbUser_VccxLineState_Param1   = eVccx_Short2GND
/// \output Rte_Write_IoHwAbUser_VccxLineState_HitCount = 1
/// \output boVccx2_en_state = TRUE
/// \output LPTMR0_GetTimeElapsed_HitCount = 1u
/// \output Dio_ReadChannel_HitCount = 1u
/// \output Dem_SetEventStatus_Param1 = VCCX2_SC_GND
/// \output Dem_SetEventStatus_Param2 = DEM_EVENT_STATUS_FAILED
/// \output Dem_SetEventStatus_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAbIoHwAbUser_VccxStateCyclicCheck_TestCase_6(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_boVccxStatus = TRUE;
  boVccx2_en_state = TRUE;
  ulVccx2_Diag_Timer = 30000u;
  Rte_Write_IoHwAbUser_VccxLineState_Param1 = eVccx_noError;
  Rte_Write_IoHwAbUser_VccxLineState_HitCount = 0u;
  LPTMR0_GetTimeElapsed_HitCount = 0u;
  LPTMR0_GetTimeElapsed_RetVal = 32000;
  Dio_ReadChannel_HitCount = 0u;
  Dio_ReadChannel_Param1 = 0u;
  Dio_ReadChannel_RetVal = STD_LOW;
  Adc_ReadGroup_Param2 = 20u;
  Dem_SetEventStatus_Param1 = 0u;
  Dem_SetEventStatus_Param2 = 0u;
  Dem_SetEventStatus_HitCount = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_VccxStateCyclicCheck();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Rte_Write_IoHwAbUser_VccxLineState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_IoHwAbUser_VccxLineState_Param1, eVccx_Short2GND, == );
  AL_UNITTEST_CHECK(boVccx2_en_state, TRUE, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dio_ReadChannel_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, VCCX2_SC_GND, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, DEM_EVENT_STATUS_FAILED, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAbIoHwAbUser_VccxStateCyclicCheck_TestCase_7
///
/// \Test Case Description
///        - Test subject: Test if function check the timer time-out to start the diagnosys (5ms) after VCCX2_EN is set and timer expired - diagnostic start and power good = 0 (power not_ok)
///                        The ADC reads the VCCX2 and detects 5700mv on output (Short2Vbat)
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set VCCX2 enable status true and active
///         Step2: Set actual error stats as Vccx_noError
///         Step3: Check that delay timer time-out  happend for diagnostic start
///         Step4: Check that Short2Vbat error is reported due the PG is not_ok and ADC returns 5700mv 
///
/// - Preconditions:
///
///
/// \input IoHwAbUser_boVccxStatus                              = TRUE
/// \input boVccx2_en_state                                     = TRUE
/// \input ulVccx2_Diag_Timer                                   = 30000u
/// \input Rte_Write_IoHwAbUser_VccxLineState_Param1    = eVccx_noError
/// \input Rte_Write_IoHwAbUser_VccxLineState_HitCount  = 0
/// \input LPTMR0_GetTimeElapsed_HitCount                       = 0
/// \input LPTMR0_GetTimeElapsed_RetVal                         = 32000u
/// \input Dio_ReadChannel_HitCount                             = 0u
/// \input Dio_ReadChannel_Param1                               = 0u
/// \input Dio_ReadChannel_RetVal                               = STD_LOW
/// \input Adc_ReadGroup_Param2                                 = 5700u
/// \input Dem_SetEventStatus_Param1                            = 0u
/// \input Dem_SetEventStatus_Param2                            = 0u
/// \input Dem_SetEventStatus_HitCount                          = 0u
///
/// - Expectations:
///
/// \output Rte_Write_IoHwAbUser_VccxLineState_Param1   = eVccx_Short2Vbat
/// \output Rte_Write_IoHwAbUser_VccxLineState_HitCount = 1
/// \output boVccx2_en_state = TRUE
/// \output LPTMR0_GetTimeElapsed_HitCount = 1u
/// \output Dio_ReadChannel_HitCount = 1u
/// \output Dem_SetEventStatus_Param1 = VCCX2_SC_BAT
/// \output Dem_SetEventStatus_Param2 = DEM_EVENT_STATUS_FAILED
/// \output Dem_SetEventStatus_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAbIoHwAbUser_VccxStateCyclicCheck_TestCase_7(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_boVccxStatus = TRUE;
  boVccx2_en_state = TRUE;
  ulVccx2_Diag_Timer = 30000u;
  Rte_Write_IoHwAbUser_VccxLineState_Param1 = eVccx_noError;
  Rte_Write_IoHwAbUser_VccxLineState_HitCount = 0u;
  LPTMR0_GetTimeElapsed_HitCount = 0u;
  LPTMR0_GetTimeElapsed_RetVal = 32000;
  Dio_ReadChannel_HitCount = 0u;
  Dio_ReadChannel_Param1 = 0u;
  Dio_ReadChannel_RetVal = STD_LOW;
  Adc_ReadGroup_Param2 = 5700u;
  Dem_SetEventStatus_Param1 = 0u;
  Dem_SetEventStatus_Param2 = 0u;
  Dem_SetEventStatus_HitCount = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_VccxStateCyclicCheck();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Rte_Write_IoHwAbUser_VccxLineState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_IoHwAbUser_VccxLineState_Param1, eVccx_Short2Vbat, == );
  AL_UNITTEST_CHECK(boVccx2_en_state, TRUE, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dio_ReadChannel_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, VCCX2_SC_BAT, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, DEM_EVENT_STATUS_FAILED, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_IoHwAbIoHwAbUser_VccxStateCyclicCheck_TestCase_8
///
/// \Test Case Description
///        - Test subject: Test if function check the timer time-out to start the diagnosys (5ms) after VCCX2_EN is set and timer expired - diagnostic start and power good = 0 (power not_ok)
///                        The ADC reads the VCCX2 and detects 5000u on output (Short2Vbat)
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set VCCX2 enable status true and active
///         Step2: Set actual error stats as eVccx_Short2Vbat
///         Step3: Check that delay timer time-out  happend for diagnostic start
///         Step4: Check that no error error is reported due the PG is not_ok and ADC returns 5000mV (normal voltage) even the Power Goot is low 
///
/// - Preconditions:
///
///
/// \input IoHwAbUser_boVccxStatus                              = TRUE
/// \input boVccx2_en_state                                     = TRUE
/// \input ulVccx2_Diag_Timer                                   = 30000u
/// \input Rte_Write_IoHwAbUser_VccxLineState_Param1    = eVccx_Short2Vbat
/// \input Rte_Write_IoHwAbUser_VccxLineState_HitCount  = 0
/// \input LPTMR0_GetTimeElapsed_HitCount                       = 0
/// \input LPTMR0_GetTimeElapsed_RetVal                         = 32000u
/// \input Dio_ReadChannel_HitCount                             = 0u
/// \input Dio_ReadChannel_Param1                               = 0u
/// \input Dio_ReadChannel_RetVal                               = STD_LOW
/// \input Adc_ReadGroup_Param2                                 = 5000u
/// \input Dem_SetEventStatus_Param1                            = 0u
/// \input Dem_SetEventStatus_Param2                            = 0u
/// \input Dem_SetEventStatus_HitCount                          = 0u
///
/// - Expectations:
///
/// \output Rte_Write_IoHwAbUser_VccxLineState_Param1   = eVccx_noError
/// \output Rte_Write_IoHwAbUser_VccxLineState_HitCount = 1
/// \output boVccx2_en_state = TRUE
/// \output LPTMR0_GetTimeElapsed_HitCount = 1u
/// \output Dio_ReadChannel_HitCount = 1u
/// \output Dem_SetEventStatus_Param1 = VCCX2_SC_BAT
/// \output Dem_SetEventStatus_Param2 = DEM_EVENT_STATUS_PASSED
/// \output Dem_SetEventStatus_HitCount = 2u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAbIoHwAbUser_VccxStateCyclicCheck_TestCase_8(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_boVccxStatus = TRUE;
  boVccx2_en_state = TRUE;
  ulVccx2_Diag_Timer = 30000u;
  Rte_Write_IoHwAbUser_VccxLineState_Param1 = eVccx_Short2Vbat;
  Rte_Write_IoHwAbUser_VccxLineState_HitCount = 0u;
  LPTMR0_GetTimeElapsed_HitCount = 0u;
  LPTMR0_GetTimeElapsed_RetVal = 32000;
  Dio_ReadChannel_HitCount = 0u;
  Dio_ReadChannel_Param1 = 0u;
  Dio_ReadChannel_RetVal = STD_LOW;
  Adc_ReadGroup_Param2 = 500u;
  Dem_SetEventStatus_Param1 = 0u;
  Dem_SetEventStatus_Param2 = 0u;
  Dem_SetEventStatus_HitCount = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_VccxStateCyclicCheck();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Rte_Write_IoHwAbUser_VccxLineState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_IoHwAbUser_VccxLineState_Param1, eVccx_noError, == );
  AL_UNITTEST_CHECK(boVccx2_en_state, TRUE, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dio_ReadChannel_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, VCCX2_SC_BAT, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, DEM_EVENT_STATUS_PASSED, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_IoHwAbIoHwAbUser_VccxStateCyclicCheck
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function check the Vccx voltage cyclicly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_IoHwAbIoHwAbUser_VccxStateCyclicCheck(void)
{
  Mt_IoHwAbIoHwAbUser_VccxStateCyclicCheck_TestCase_1();
  Mt_IoHwAbIoHwAbUser_VccxStateCyclicCheck_TestCase_2();
  Mt_IoHwAbIoHwAbUser_VccxStateCyclicCheck_TestCase_3();
  Mt_IoHwAbIoHwAbUser_VccxStateCyclicCheck_TestCase_4();
  Mt_IoHwAbIoHwAbUser_VccxStateCyclicCheck_TestCase_5();
  Mt_IoHwAbIoHwAbUser_VccxStateCyclicCheck_TestCase_6();
  Mt_IoHwAbIoHwAbUser_VccxStateCyclicCheck_TestCase_7();
  Mt_IoHwAbIoHwAbUser_VccxStateCyclicCheck_TestCase_8();
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAbUser_Get_PCB
///
/// \Test Case Description
///        - Test subject: Test if function reads the PCB temperature from ECU
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the PCB raw value
///         Step2: Set the filter value of PCB
///         Step3: Set the factor value of PCB
///         Step3: Call the function IoHwAbUser_Get_PCB()
///         Step4: Check the value of the voltage of PCB
///
/// - Preconditions:
///
/// \input Adc_ReadGroup_Param2                              = 5501u
/// \input IoHwAbUser_unFilterCoefPCB                        = 500u
/// \input IoHwAbUser_slPCB_Filter                           = 300u
/// \input IoHwAbUser_unFactorPCB                            = 4000u
///
/// - Expectations:
///
/// \output Rte_Write_IoHwAb_GetPCB_Param1                   = 97u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAbUser_Get_PCB(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Adc_ReadGroup_Param2 = 50u;
  IoHwAbUser_unFilterCoefPCB = 500u;
  IoHwAbUser_slPCB_Filter = 300u;
  IoHwAbUser_unFactorPCB = 4000u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_Get_PCB();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Rte_Write_IoHwAb_GetPCB_Param1, 97u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAbUser_GetHss0Sense
///
/// \Test Case Description
///        - Test subject: Test if function return the voltage for hss sense 0
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the voltage for hss sense 0
///         Step3: Call the function IoHwAbUser_GetHss0Sense()
///         Step4: Check the value of the HSSS output 1 that should to be read by CddVnd7140 and CddVn7140
///
/// - Preconditions:
///
/// \input IoHwAbUser_GetHss0Sense_Param1                               = 5u
/// \input IoHwAbUser_aulHSSSensorVoltage[0u]                           = 10u
///
/// - Expectations:
///
/// \output IoHwAbUser_GetHss0Sense_Param1                              = 10u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_GetHss0Sense(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_GetHss0Sense_Param1 = 5u;
  IoHwAbUser_aulHSSSensorVoltage[0u] = 10u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_GetHss0Sense(&IoHwAbUser_GetHss0Sense_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_GetHss0Sense_Param1, 10u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAbUser_GetHss1Sense
///
/// \Test Case Description
///        - Test subject: Test if function return the voltage for hss sense 1
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the voltage for hss sense 1
///         Step3: Call the function IoHwAbUser_GetHss0Sens1()
///         Step4: Check the value of the HSSS output 2 that should to be read by CddVnd7140 and CddVn7140
///
/// - Preconditions:
///
/// \input IoHwAbUser_GetHss1Sense_Param1                             = 5u
/// \input IoHwAbUser_aulHSSSensorVoltage[1u]                         = 10u
///
/// - Expectations:
///
/// \output IoHwAbUser_GetHss1Sense_Param1                             = 10u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_GetHss1Sense(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_GetHss1Sense_Param1 = 5u;
  IoHwAbUser_aulHSSSensorVoltage[1u] = 10u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_GetHss1Sense(&IoHwAbUser_GetHss1Sense_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_GetHss1Sense_Param1, 10u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAbUser_GetHss2Sense
///
/// \Test Case Description
///        - Test subject: Test if function return the voltage for hss sense 2
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the voltage for hss sense 2
///         Step3: Call the function IoHwAbUser_GetHss2Sense()
///         Step4: Check the value of the HSSS output 2 that should to be read by CddVnd7140 and CddVn7140
///
/// - Preconditions:
///
/// \input IoHwAbUser_GetHss2Sense_Param1                               = 5u
/// \input IoHwAbUser_aulHSSSensorVoltage[2u]                           = 10u
///
/// - Expectations:
///
/// \output IoHwAbUser_GetHss1Sense_Param1                              = 10u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_GetHss2Sense(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_GetHss2Sense_Param1 = 5u;
  IoHwAbUser_aulHSSSensorVoltage[2u] = 10u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_GetHss2Sense(&IoHwAbUser_GetHss2Sense_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_GetHss2Sense_Param1, 10u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT1
///
/// \Test Case Description
///        - Test subject: Test if function returns ext NTC 1 voltage
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the voltage for external NTC 1
///         Step3: Call the function IoHwAbUser_GetVoltage_EXT1()
///         Step4: Check the voltage value of the returned NTC
///
/// - Preconditions:
///
/// \input IoHwAbUser_aulHSSSensorVoltage[0u]                             = 10u
///
/// - Expectations:
///
/// \output IoHwAbUser_GetVoltage_EXT1_RetVal                             = 10u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_aunNTCVoltage[0u] = 10u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_GetVoltage_EXT1_RetVal = IoHwAbUser_GetVoltage_EXT1();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_GetVoltage_EXT1_RetVal, 10u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT2
///
/// \Test Case Description
///        - Test subject: Test if function returns ext NTC 2 voltage
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the voltage for external NTC 2
///         Step3: Call the function IoHwAbUser_GetVoltage_EXT2()
///         Step4: Check the voltage value of the returned NTC
///
/// - Preconditions:
///
/// \input IoHwAbUser_aulHSSSensorVoltage[1u]                             = 10u
///
/// - Expectations:
///
/// \output IoHwAbUser_GetVoltage_EXT2_RetVal                             = 10u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_aunNTCVoltage[1u] = 10u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_GetVoltage_EXT2_RetVal = IoHwAbUser_GetVoltage_EXT2();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_GetVoltage_EXT2_RetVal, 10u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT3
///
/// \Test Case Description
///        - Test subject: Test if function returns ext NTC 3 voltage
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the voltage for external NTC 3
///         Step3: Call the function IoHwAbUser_GetVoltage_EXT3()
///         Step4: Check the voltage value of the returned NTC
///
/// - Preconditions:
///
/// \input IoHwAbUser_aulHSSSensorVoltage[2u]                             = 10u
///
/// - Expectations:
///
/// \output IoHwAbUser_GetVoltage_EXT3_RetVal                             = 10u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_aunNTCVoltage[2u] = 10u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_GetVoltage_EXT3_RetVal = IoHwAbUser_GetVoltage_EXT3();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_GetVoltage_EXT3_RetVal, 10u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT4
///
/// \Test Case Description
///        - Test subject: Test if function returns ext NTC 4 voltage
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the voltage for external NTC 4
///         Step3: Call the function IoHwAbUser_GetVoltage_EXT4()
///         Step4: Check the voltage value of the returned NTC
///
/// - Preconditions:
///
/// \input IoHwAbUser_aulHSSSensorVoltage[3u]                             = 10u
///
/// - Expectations:
///
/// \output IoHwAbUser_GetVoltage_EXT4_RetVal                             = 10u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT4(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_aunNTCVoltage[3u] = 10u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_GetVoltage_EXT4_RetVal = IoHwAbUser_GetVoltage_EXT4();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_GetVoltage_EXT4_RetVal, 10u, == );
}


// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT5
///
/// \Test Case Description
///        - Test subject: Test if function returns ext NTC 5 voltage
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the voltage for external NTC 5
///         Step3: Call the function IoHwAbUser_GetVoltage_EXT5()
///         Step4: Check the voltage value of the returned NTC
///
/// - Preconditions:
///
/// \input IoHwAbUser_aulHSSSensorVoltage[1u]                             = 10u
///
/// - Expectations:
///
/// \output IoHwAbUser_GetVoltage_EXT2_RetVal                             = 10u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT5(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_aunNTCVoltage[4u] = 10u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_GetVoltage_EXT5_RetVal = IoHwAbUser_GetVoltage_EXT5();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_GetVoltage_EXT5_RetVal, 10u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT6
///
/// \Test Case Description
///        - Test subject: Test if function returns ext NTC 6 voltage
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the voltage for external NTC 6
///         Step3: Call the function IoHwAbUser_GetVoltage_EXT6()
///         Step4: Check the voltage value of the returned NTC
///
/// - Preconditions:
///
/// \input IoHwAbUser_aulHSSSensorVoltage[5u]                             = 10u
///
/// - Expectations:
///
/// \output IoHwAbUser_GetVoltage_EXT6_RetVal                             = 10u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT6(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_aunNTCVoltage[5u] = 10u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_GetVoltage_EXT6_RetVal = IoHwAbUser_GetVoltage_EXT6();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_GetVoltage_EXT6_RetVal, 10u, == );
}


// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT7
///
/// \Test Case Description
///        - Test subject: Test if function returns ext NTC 7 voltage
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the voltage for external NTC 7
///         Step3: Call the function IoHwAbUser_GetVoltage_EXT7()
///         Step4: Check the voltage value of the returned NTC
///
/// - Preconditions:
///
/// \input IoHwAbUser_aulHSSSensorVoltage[6u]                             = 10u
///
/// - Expectations:
///
/// \output IoHwAbUser_GetVoltage_EXT7_RetVal                             = 10u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT7(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_aunNTCVoltage[6u] = 10u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_GetVoltage_EXT7_RetVal = IoHwAbUser_GetVoltage_EXT7();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_GetVoltage_EXT7_RetVal, 10u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAbUser_Read_VCCX1
///
/// \Test Case Description
///        - Test subject: Test if function read voltage from VCCX2
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the VCCX1 raw value
///         Step1: Set the filter value of VCCX1e
///         Step3: Call the function IoHwAbUser_Read_VCCX1()
///         Step4: Check the calculated, filtered voltage of VCCX1
///
/// - Preconditions:
///
/// \input Adc_ReadGroup_Param2                                = 300u
///
/// - Expectations:
///
/// \output IoHwAbUser_Read_VCCX1_RetVal                       = 153u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_Read_VCCX1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Adc_ReadGroup_Param2 = 300u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_Read_VCCX1_RetVal = IoHwAbUser_Read_VCCX1();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_Read_VCCX1_RetVal, 153u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT8
///
/// \Test Case Description
///        - Test subject: Test if function returns ext NTC 8 voltage
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the voltage for external NTC 8
///         Step3: Call the function IoHwAbUser_GetVoltage_EXT8()
///         Step4: Check the voltage value of the returned NTC
///
/// - Preconditions:
///
/// - Preconditions:
///
/// \input IoHwAbUser_aulHSSSensorVoltage[7u]                             = 10u
///
/// - Expectations:
///
/// \output IoHwAbUser_GetVoltage_EXT8_RetVal                             = 10u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT8(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_aunNTCVoltage[7u] = 10u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_GetVoltage_EXT8_RetVal = IoHwAbUser_GetVoltage_EXT8();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_GetVoltage_EXT8_RetVal, 10u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT9
///
/// \Test Case Description
///        - Test subject: Test if function returns ext NTC 9 voltage
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the voltage for external NTC 9
///         Step3: Call the function IoHwAbUser_GetVoltage_EXT9()
///         Step4: Check the voltage value of the returned NTC
///
/// - Preconditions:
///
/// - Preconditions:
///
/// \input IoHwAbUser_aulHSSSensorVoltage[8u]                             = 10u
///
/// - Expectations:
///
/// \output IoHwAbUser_GetVoltage_EXT9_RetVal                             = 10u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT9(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_aunNTCVoltage[8u] = 10u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_GetVoltage_EXT9_RetVal = IoHwAbUser_GetVoltage_EXT9();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_GetVoltage_EXT9_RetVal, 10u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT10
///
/// \Test Case Description
///        - Test subject: Test if function returns ext NTC 10 voltage
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the voltage for external NTC 10
///         Step3: Call the function IoHwAbUser_GetVoltage_EXT10()
///         Step4: Check the voltage value of the returned NTC
///
/// - Preconditions:
///
/// - Preconditions:
///
/// \input IoHwAbUser_aulHSSSensorVoltage[9u]                              = 10u
///
/// - Expectations:
///
/// \output IoHwAbUser_GetVoltage_EXT10_RetVal                             = 10u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT10(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_aunNTCVoltage[9u] = 10u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_GetVoltage_EXT10_RetVal = IoHwAbUser_GetVoltage_EXT10();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_GetVoltage_EXT10_RetVal, 10u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT11
///
/// \Test Case Description
///        - Test subject: Test if function returns ext NTC 11 voltage
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the voltage for external NTC 11
///         Step3: Call the function IoHwAbUser_GetVoltage_EXT11()
///         Step4: Check the voltage value of the returned NTC
///
/// - Preconditions:
///
/// \input IoHwAbUser_aulHSSSensorVoltage[10u]                              = 10u
///
/// - Expectations:
///
/// \output IoHwAbUser_GetVoltage_EXT11_RetVal                             = 10u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT11(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_aunNTCVoltage[10u] = 10u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_GetVoltage_EXT11_RetVal = IoHwAbUser_GetVoltage_EXT11();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_GetVoltage_EXT11_RetVal, 10u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT12
///
/// \Test Case Description
///        - Test subject: Test if function reads the voltage from EXT NTC
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the voltage for external NTC 12
///         Step3: Call the function IoHwAbUser_GetVoltage_EXT12()
///         Step4: Check the voltage value of the returned NTC
///
/// - Preconditions:
///
/// \input IoHwAbUser_aulHSSSensorVoltage[11u]                             = 10u
///
/// - Expectations:
///
/// \output IoHwAbUser_GetVoltage_EXT12_RetVal                             = 10u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT12(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_aunNTCVoltage[11u] = 10u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_GetVoltage_EXT12_RetVal = IoHwAbUser_GetVoltage_EXT12();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_GetVoltage_EXT12_RetVal, 10u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT13
///
/// \Test Case Description
///        - Test subject: Test if function reads the voltage from EXT NTC
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the voltage for external NTC 13
///         Step3: Call the function IoHwAbUser_GetVoltage_EXT13()
///         Step4: Check the voltage value of the returned NTC
///
/// - Preconditions:
///
/// \input IoHwAbUser_aulHSSSensorVoltage[12u]                             = 10u
///
/// - Expectations:
///
/// \output IoHwAbUser_GetVoltage_EXT13_RetVal                             = 10u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT13(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_aunNTCVoltage[12u] = 10u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_GetVoltage_EXT13_RetVal = IoHwAbUser_GetVoltage_EXT13();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_GetVoltage_EXT13_RetVal, 10u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT14
///
/// \Test Case Description
///        - Test subject: Test if function reads the voltage from EXT NTC
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the voltage for external NTC 14
///         Step3: Call the function IoHwAbUser_GetVoltage_EXT14()
///         Step4: Check the voltage value of the returned NTC
///
/// - Preconditions:
///
/// \input IoHwAbUser_aulHSSSensorVoltage[13u]                             = 10u
///
/// - Expectations:
///
/// \output IoHwAbUser_GetVoltage_EXT14_RetVal                             = 10u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT14(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_aunNTCVoltage[13u] = 10u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_GetVoltage_EXT14_RetVal = IoHwAbUser_GetVoltage_EXT14();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_GetVoltage_EXT13_RetVal, 10u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAbUser_GetVoltage_NTC
///
/// \Test Case Description
///        - Test subject: Test if function reads the voltage for NTC
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the voltage for external NTC 14
///         Step3: Call the function IoHwAbUser_GetVoltage_EXT14()
///         Step4: Check the voltage value of the returned NTC
///
/// - Preconditions:
///
/// \input Order1Filter_HitCount                                           = 0u
///
/// - Expectations:
///
/// \output Order1Filter_HitCount                                          = 14u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_GetVoltage_NTC(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Order1Filter_HitCount = 0u;
  Rte_Write_IoHwAb_GetVoltage_NTCs_HitCount = 0;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_GetVoltage_NTC();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Order1Filter_HitCount, 14u, == );
  AL_UNITTEST_CHECK(Rte_Write_IoHwAb_GetVoltage_NTCs_HitCount, 1u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAbUser_GetVoltage_NTCs_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function reads the voltage for NTC index
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the index of the wanted NTC voltage
///         Step2: Call the function IoHwAbUser_GetVoltage_NTCs()
///         Step3: Check the returned voltage value of indexed NTC
///
/// - Preconditions:
///
/// \input IoHwAbUser_GetVoltage_NTCs_Param1                              = 2u
///
/// - Expectations:
///
/// \output IoHwAbUser_GetVoltage_NTCs_RetVal                             = 153u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_GetVoltage_NTCs_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
 // Inputs
 //-----------------------------------------------------------------------------

  IoHwAbUser_GetVoltage_NTCs_Param1 = 2u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_GetVoltage_NTCs_RetVal = IoHwAbUser_GetVoltage_NTCs(IoHwAbUser_GetVoltage_NTCs_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_GetVoltage_NTCs_RetVal, 153u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAbUser_GetVoltage_NTCs_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function reads the voltage for NTC index
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test,fault injection test
///
/// \Steps:
///         Step1: Set an invalid index
///         Step2: Call the function IoHwAbUser_GetVoltage_NTCs()
///         Step3: Check the returned voltage value of indexed NTC
///
/// - Preconditions:
///
/// \input IoHwAbUser_GetVoltage_NTCs_Param1                              = 28u
///
/// - Expectations:
///
/// \output IoHwAbUser_GetVoltage_NTCs_RetVal                             = 0xFFFFU
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_GetVoltage_NTCs_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_GetVoltage_NTCs_Param1 = 28u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_GetVoltage_NTCs_RetVal = IoHwAbUser_GetVoltage_NTCs(IoHwAbUser_GetVoltage_NTCs_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_GetVoltage_NTCs_RetVal, 0xFFFFU, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_IoHwAb_IoHwAbUser_GetVoltage_NTCs
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function reads the voltage for NTC index
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_GetVoltage_NTCs(void)
{
  Mt_IoHwAb_IoHwAbUser_GetVoltage_NTCs_TestCase_1();
  Mt_IoHwAb_IoHwAbUser_GetVoltage_NTCs_TestCase_2();
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAbUser_GetSens_Raw
///
/// \Test Case Description
///        - Test subject: Test if function gets filtered raw value of analog height sensor inputs
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the calculated duty for both sensor
///         Step2: Call the function IoHwAbUser_GetSens_Raw()
///         Step3: Check the calulated duty values on RTE
///
/// - Preconditions:
///
/// \input IoHwAbUser_unSensCalculatedDuty[0]                              = 10u
/// \input IoHwAbUser_unSensCalculatedDuty[1]                              = 100u
/// \input Rte_Write_IoHwAb_GetSens_Raw_HitCount                           = 0u
///
/// - Expectations:
///
/// \output Rte_Write_IoHwAb_GetSens_Raw_RetVal.aucSensRaw[0]             = 10u
/// \output Rte_Write_IoHwAb_GetSens_Raw_RetVal.aucSensRaw[1]             = 100u
/// \output Rte_Write_IoHwAb_GetSens_Raw_HitCount                         = 1u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_GetSens_Raw(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_unSensCalculatedDuty[0] = 10;
  IoHwAbUser_unSensCalculatedDuty[1] = 100;
  Rte_Write_IoHwAb_GetSens_Raw_HitCount = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_GetSens_Raw();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Rte_Write_IoHwAb_GetSens_Raw_HitCount, 1u, == );

}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAbUser_GetSens_Balanced_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function gets filtered balanced value of analog height sensor inputs
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the calculated duty for both sensor
///         Step2: Call the function IoHwAbUser_GetSens_Raw()
///         Step3: Check the calulated duty values on RTE
///
/// - Preconditions:
///
/// \input Icu_ReadPwmSensor_Param1                              = ucIx
/// \input Icu_ReadPwmSensor_RetVal                              = 65535u
///
/// - Expectations:
///
/// \output IoHwAbUser_aslSensPwmTarget[0]                        = 52438u
/// \output IoHwAbUser_aslSensPwmTarget[1]                        = 52528u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_GetSens_Balanced_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  for (uint8 ucIx = 0u; ucIx < CFG_CntSens; ucIx++)
  {
    Icu_ReadPwmSensor_Param1 = ucIx;
    Icu_ReadPwmSensor_RetVal = 65535u;
  }

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_GetSens_Balanced();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_aslSensPwmTarget[0], 52438u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_aslSensPwmTarget[1], 52528, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAbUser_GetSens_Balanced_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function gets filtered balanced value of analog height sensor inputs
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the calculated duty for both sensor
///         Step2: Call the function IoHwAbUser_GetSens_Raw()
///         Step3: Check the calulated duty values on RTE
///
/// - Preconditions:
///
/// \input  IoHwAbUser_unSensCalculatedDuty[0u] = 60500u
/// \input  IoHwAbUser_unSensCalculatedDuty[1u] = 60500u
///
/// - Expectations:
///
/// \output IoHwAbUser_aslSensPwmTarget[0]                            = 8072u
/// \output IoHwAbUser_aslSensPwmTarget[1]                            = 8072u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_GetSens_Balanced_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_unSensCalculatedDuty[0u] = 60500u;
  IoHwAbUser_unSensCalculatedDuty[1u] = 60500u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_GetSens_Balanced();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_aslSensPwmTarget[0], 8072u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_aslSensPwmTarget[1], 8072u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAbUser_GetSens_Balanced_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function gets filtered balanced value of analog height sensor inputs
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the calculated duty for both sensor
///         Step2: Call the function IoHwAbUser_GetSens_Raw()
///         Step3: Check the calulated duty values on RTE
///
/// - Preconditions:
///
/// \input IoHwAbUser_unSensCalculatedDuty[0u] = 5000u
/// \input IoHwAbUser_unSensCalculatedDuty[1u] = 5000u
///
/// - Expectations:
///
/// \output IoHwAbUser_aslSensPwmTarget[0]                            = 57428u
/// \output IoHwAbUser_aslSensPwmTarget[1]                            = 57428u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_GetSens_Balanced_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_unSensCalculatedDuty[0u] = 5000u;
  IoHwAbUser_unSensCalculatedDuty[1u] = 5000u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_GetSens_Balanced();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_aslSensPwmTarget[0], 57428u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_aslSensPwmTarget[1], 57428u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAbUser_GetSens_Balanced_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test if function gets filtered balanced value of analog height sensor inputs
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the calculated duty for both sensor
///         Step2: Call the function IoHwAbUser_GetSens_Raw()
///         Step3: Check the calulated duty values on RTE
///
/// - Preconditions:
///
/// \input IoHwAbUser_unSensCalculatedDuty[0u] = 35000u
/// \input IoHwAbUser_unSensCalculatedDuty[1u] = 35000u
///
/// - Expectations:
///
/// \output IoHwAbUser_aslSensPwmTarget[0]                            = 35000u
/// \output IoHwAbUser_aslSensPwmTarget[1]                            = 35000u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_GetSens_Balanced_TestCase_4(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_unSensCalculatedDuty[0u] = 35000u;
  IoHwAbUser_unSensCalculatedDuty[1u] = 35000u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_GetSens_Balanced();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_aslSensPwmTarget[0], 35000u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_aslSensPwmTarget[1], 35000u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_IoHwAb_IoHwAbUser_GetSens_Balanced
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function reads the balanced sensor PWM values
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_GetSens_Balanced(void)
{
  Mt_IoHwAb_IoHwAbUser_GetSens_Balanced_TestCase_1();
  Mt_IoHwAb_IoHwAbUser_GetSens_Balanced_TestCase_2();
  Mt_IoHwAb_IoHwAbUser_GetSens_Balanced_TestCase_3();
  Mt_IoHwAb_IoHwAbUser_GetSens_Balanced_TestCase_4();
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAbUser_CalcInputPwmSens_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function gets filtered balanced value of analog height sensor inputs
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set sensor measurements - period or duty cycle
///         Step1: Convert to internal % format 0%..100% = 0x0 .. 0xFFFF
///         Step1: Set the duty cycle to exceeds 95%
///         Step2: Call the function IoHwAbUser_CalcInputPwmSens()
///         Step3: Check the measurements mode
///
/// - Preconditions:
///
/// \input IoHwAbUser_ucMeasMode                    = 1u
/// \input IoHwAbUser_ucMeasCycle                   = 1u
/// \input Icu_GetMeasurementSens_HitCount          = 0u
/// \input Icu_GetMeasurementSens_RetVal            = 1000u
/// \input Icu_ChangeMeasurementMode_HitCount       = 0u
/// \input Mt_IoHwAb_FTM0Register                   = 5u
/// \input Mt_IoHwAb_CHOV_BitStatus                 = 8u
/// \input Mt_IoHwAb_FTM4Register                   = 15u
/// \input IoHwAbUser_unSensMeasPeriodAndDuty[0][0] = 5u
/// \input IoHwAbUser_unSensMeasPeriodAndDuty[0][1] = 5u
/// \input IoHwAbUser_unSensCalculatedDuty[0]       = 10u
/// \input IoHwAbUser_unSensCalculatedDuty[1]       = 10u
///
/// - Expectations:
///
/// \output Icu_GetMeasurementSens_HitCount          = 2u
/// \output Icu_ChangeMeasurementMode_HitCount       = 2u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_CalcInputPwmSens_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_ucMeasMode = 1u;
  IoHwAbUser_ucMeasCycle = 1u;
  Icu_GetMeasurementSens_HitCount = 0u;
  Icu_GetMeasurementSens_RetVal = 1000u;
  Icu_ChangeMeasurementMode_HitCount = 0u;
  Mt_IoHwAb_FTM0Register = 5u;
  Mt_IoHwAb_FTM4Register = 15u;
  Mt_IoHwAb_CHOV_BitStatus = 8u;
  IoHwAbUser_unSensMeasPeriodAndDuty[0][0] = 5u;
  IoHwAbUser_unSensMeasPeriodAndDuty[1][0] = 5u;
  IoHwAbUser_unSensCalculatedDuty[0] = 10u;
  IoHwAbUser_unSensCalculatedDuty[1] = 10u;


  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_CalcInputPwmSens();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Icu_GetMeasurementSens_HitCount, 2u, == );
  AL_UNITTEST_CHECK(Icu_ChangeMeasurementMode_HitCount, 2u, == );
  AL_UNITTEST_CHECK(Icu_ChangeMeasurementMode_Param2, 1u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_ucMeasMode, 1u, == );
}


// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAbUser_CalcInputPwmSens_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function gets filtered balanced value of analog height sensor inputs
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set sensor measurements - period or duty cycle
///         Step1: Convert to internal % format 0%..100% = 0x0 .. 0xFFFF
///         Step1: Set the duty cycle to exceeds 95%
///         Step2: Call the function IoHwAbUser_CalcInputPwmSens()
///         Step3: Check the measurements mode
///
/// - Preconditions:
///
/// \input IoHwAbUser_ucMeasMode                    = 1u
/// \input IoHwAbUser_ucMeasCycle                   = 1u
/// \input Icu_GetMeasurementSens_HitCount          = 0u
/// \input Icu_GetMeasurementSens_RetVal            = 0u
/// \input Icu_ChangeMeasurementMode_HitCount       = 0u
/// \input Mt_IoHwAb_FTM0Register                   = 5u
/// \input Mt_IoHwAb_CHOV_BitStatus                 = 8u
/// \input Mt_IoHwAb_FTM4Register                   = 15u
/// \input IoHwAbUser_unSensMeasPeriodAndDuty[0][1] = 0u
/// \input IoHwAbUser_unSensMeasPeriodAndDuty[0][1] = 0u
/// \input IoHwAbUser_unSensCalculatedDuty[0]       = 0xFFFFu
/// \input IoHwAbUser_unSensCalculatedDuty[1]       = 0u
///
/// - Expectations:
///
/// \output Icu_GetMeasurementSens_HitCount          = 2u
/// \output Icu_ChangeMeasurementMode_HitCount       = 2u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_CalcInputPwmSens_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_ucMeasMode = 1u;
  IoHwAbUser_ucMeasCycle = 1u;
  Icu_GetMeasurementSens_HitCount = 0u;
  Icu_GetMeasurementSens_RetVal = 1u;
  Icu_ChangeMeasurementMode_HitCount = 0u;
  Mt_IoHwAb_FTM0Register = 1u;
  Mt_IoHwAb_FTM4Register = 1u;
  Mt_IoHwAb_CHOV_BitStatus = 1u;
  IoHwAbUser_unSensMeasPeriodAndDuty[0][1] = 1u;
  IoHwAbUser_unSensMeasPeriodAndDuty[1][1] = 1u;
  IoHwAbUser_unSensMeasPeriodAndDuty[0][0] = 1u;
  IoHwAbUser_unSensCalculatedDuty[0] = 0xFFFFu;
  IoHwAbUser_unSensCalculatedDuty[1] = 0u;


  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_CalcInputPwmSens();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Icu_GetMeasurementSens_HitCount, 2u, == );
  AL_UNITTEST_CHECK(Icu_ChangeMeasurementMode_HitCount, 2u, == );
}


// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAbUser_CalcInputPwmSens_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function gets filtered balanced value of analog height sensor inputs
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set sensor measurements - period or duty cycle
///         Step1: Convert to internal % format 0%..100% = 0x0 .. 0xFFFF
///         Step1: Set the duty cycle to exceeds 95%
///         Step2: Call the function IoHwAbUser_CalcInputPwmSens()
///         Step3: Check the measurements mode
///
/// - Preconditions:
///
/// \input IoHwAbUser_ucMeasMode                    = 1u
/// \input IoHwAbUser_ucMeasCycle                   = 1u
/// \input Icu_GetMeasurementSens_HitCount          = 0u
/// \input Icu_GetMeasurementSens_RetVal            = 1000u
/// \input Icu_ChangeMeasurementMode_HitCount       = 0u
/// \input Mt_IoHwAb_FTM0Register                   = 5u
/// \input Mt_IoHwAb_CHOV_BitStatus                 = 8u
/// \input Mt_IoHwAb_FTM4Register                   = 15u
/// \input IoHwAbUser_unSensMeasPeriodAndDuty[0][1] = 111u
/// \input IoHwAbUser_unSensMeasPeriodAndDuty[1][1] = 100u
/// \input IoHwAbUser_unSensMeasPeriodAndDuty[1][0] = 1u
/// \input IoHwAbUser_unSensCalculatedDuty[0]       = 0u
/// \input IoHwAbUser_unSensCalculatedDuty[1]       = 0u
///
/// - Expectations:
///
/// \output Icu_GetMeasurementSens_HitCount          = 2u
/// \output Icu_ChangeMeasurementMode_HitCount       = 2u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_CalcInputPwmSens_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_ucMeasMode = 1u;
  IoHwAbUser_ucMeasCycle = 1u;
  Icu_GetMeasurementSens_HitCount = 0u;
  Icu_GetMeasurementSens_RetVal = 1000u;
  Icu_ChangeMeasurementMode_HitCount = 0u;
  Mt_IoHwAb_FTM0Register = 1u;
  Mt_IoHwAb_FTM4Register = 15u;
  Mt_IoHwAb_CHOV_BitStatus = 8u;
  IoHwAbUser_unSensMeasPeriodAndDuty[0][1] = 111u;
  IoHwAbUser_unSensMeasPeriodAndDuty[1][1] = 100u;
  IoHwAbUser_unSensMeasPeriodAndDuty[1][0] = 1u;
  IoHwAbUser_unSensCalculatedDuty[0] = 0u;
  IoHwAbUser_unSensCalculatedDuty[1] = 0u;


  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_CalcInputPwmSens();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Icu_GetMeasurementSens_HitCount, 2u, == );
  AL_UNITTEST_CHECK(Icu_ChangeMeasurementMode_HitCount, 2u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAbUser_CalcInputPwmSens_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test if function gets filtered balanced value of analog height sensor inputs
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set sensor measurements - period or duty cycle
///         Step1: Convert to internal % format 0%..100% = 0x0 .. 0xFFFF
///         Step1: Set the duty cycle to exceeds 95%
///         Step2: Call the function IoHwAbUser_CalcInputPwmSens()
///         Step3: Check the measurements mode
///
/// - Preconditions:
///
/// \input IoHwAbUser_ucMeasMode                    = 1u
/// \input IoHwAbUser_ucMeasCycle                   = 10u
/// \input Icu_GetMeasurementSens_HitCount          = 0u
/// \input Icu_GetMeasurementSens_RetVal            = 1000u
/// \input Icu_ChangeMeasurementMode_HitCount       = 0u
/// \input Mt_IoHwAb_FTM0Register                   = 1u
/// \input Mt_IoHwAb_CHOV_BitStatus                 = 8u
/// \input Mt_IoHwAb_FTM4Register                   = 15u
/// \input IoHwAbUser_unSensMeasPeriodAndDuty[0][1] = 111u
/// \input IoHwAbUser_unSensMeasPeriodAndDuty[1][1] = 100u
/// \input IoHwAbUser_unSensMeasPeriodAndDuty[0][1] = 1u
/// \input IoHwAbUser_unSensCalculatedDuty[0]       = 0u
/// \input IoHwAbUser_unSensCalculatedDuty[1]       = 0u
///
/// - Expectations:
///
/// \output Icu_GetMeasurementSens_HitCount          = 2u
/// \output Icu_ChangeMeasurementMode_HitCount       = 2u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_CalcInputPwmSens_TestCase_4(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_ucMeasMode = 1u;
  IoHwAbUser_ucMeasCycle = 10u;
  Icu_GetMeasurementSens_HitCount = 0u;
  Icu_GetMeasurementSens_RetVal = 5499u;
  Icu_ChangeMeasurementMode_HitCount = 0u;
  Mt_IoHwAb_FTM0Register = 1u;
  Mt_IoHwAb_FTM4Register = 15u;
  Mt_IoHwAb_CHOV_BitStatus = 8u;
  IoHwAbUser_unSensMeasPeriodAndDuty[0][1] = 5000u; // strict higher 5500
  IoHwAbUser_unSensMeasPeriodAndDuty[1][1] = 100u;
  IoHwAbUser_unSensMeasPeriodAndDuty[1][0] = 5000u; // strict lower 4500
  IoHwAbUser_unSensCalculatedDuty[0] = 0u;
  IoHwAbUser_unSensCalculatedDuty[1] = 0u;


  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_CalcInputPwmSens();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Icu_GetMeasurementSens_HitCount, 2u, == );
  AL_UNITTEST_CHECK(Icu_ChangeMeasurementMode_HitCount, 2u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAbUser_CalcInputPwmSens_TestCase_5
///
/// \Test Case Description
///        - Test subject: Test if function gets filtered balanced value of analog height sensor inputs
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set sensor measurements - period or duty cycle
///         Step1: Convert to internal % format 0%..100% = 0x0 .. 0xFFFF
///         Step1: Set the duty cycle to exceeds 95%
///         Step2: Call the function IoHwAbUser_CalcInputPwmSens()
///         Step3: Check the measurements mode
///
/// - Preconditions:
///
/// \input IoHwAbUser_ucMeasMode                    = 1u
/// \input IoHwAbUser_ucMeasCycle                   = 10u
/// \input Icu_GetMeasurementSens_HitCount          = 0u
/// \input Icu_GetMeasurementSens_RetVal            = 0u
/// \input Icu_ChangeMeasurementMode_HitCount       = 0u
/// \input Mt_IoHwAb_FTM0Register                   = 1u
/// \input Mt_IoHwAb_CHOV_BitStatus                 = 1u
/// \input Mt_IoHwAb_FTM4Register                   = 1u
/// \input IoHwAbUser_unSensMeasPeriodAndDuty[0][0] = 1000u
/// \input IoHwAbUser_unSensMeasPeriodAndDuty[1][1] = 100u
/// \input IoHwAbUser_unSensMeasPeriodAndDuty[0][1] = 1u
/// \input IoHwAbUser_unSensCalculatedDuty[0]       = 1u
/// \input IoHwAbUser_unSensCalculatedDuty[1]       = 1u
///
/// - Expectations:
///
/// \output Icu_GetMeasurementSens_HitCount          = 2u
/// \output Icu_ChangeMeasurementMode_HitCount       = 2u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_CalcInputPwmSens_TestCase_5(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_ucMeasMode = 1u;
  IoHwAbUser_ucMeasCycle = 10u;
  Icu_GetMeasurementSens_HitCount = 0u;
  Icu_GetMeasurementSens_RetVal = 0u;
  Icu_ChangeMeasurementMode_HitCount = 0u;
  Mt_IoHwAb_FTM0Register = 1u;
  Mt_IoHwAb_FTM4Register = 1u;
  Mt_IoHwAb_CHOV_BitStatus = 1u;
  IoHwAbUser_unSensMeasPeriodAndDuty[0][0] = 1000u;
  IoHwAbUser_unSensMeasPeriodAndDuty[0][1] = 1u;
  IoHwAbUser_unSensMeasPeriodAndDuty[1][0] = 1u;
  IoHwAbUser_unSensCalculatedDuty[0] = 1u;
  IoHwAbUser_unSensCalculatedDuty[1] = 1u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_CalcInputPwmSens();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Icu_GetMeasurementSens_HitCount, 2u, == );
  AL_UNITTEST_CHECK(Icu_ChangeMeasurementMode_HitCount, 2u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAbUser_CalcInputPwmSens_TestCase_6
///
/// \Test Case Description
///        - Test subject: Test if function gets filtered balanced value of analog height sensor inputs
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set sensor measurements - period or duty cycle
///         Step1: Convert to internal % format 0%..100% = 0x0 .. 0xFFFF
///         Step1: Set the duty cycle to exceeds 95%
///         Step2: Call the function IoHwAbUser_CalcInputPwmSens()
///         Step3: Check the measurements mode
///
/// - Preconditions:
///
/// \input IoHwAbUser_ucMeasMode                    = 0u
/// \input Icu_GetMeasurementSens_RetVal            = 5000u
/// \input unSensPeriodPwm0_Err                     = 0u
/// \input unSensPeriodPwm1_Err                     = 0u
///
/// - Expectations:
///
/// \output unSensPeriodPwm0_Err                    = 5520u
/// \output unSensPeriodPwm1_Err                    = 5520u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_CalcInputPwmSens_TestCase_6(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_ucMeasMode = 0u;
  Icu_GetMeasurementSens_RetVal = 5000u;
  unSensPeriodPwm0_Err = 0u;
  unSensPeriodPwm1_Err = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_CalcInputPwmSens();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(unSensPeriodPwm0_Err, 5520u, == );
  AL_UNITTEST_CHECK(unSensPeriodPwm1_Err, 5520u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAbUser_CalcInputPwmSens_TestCase_7
///
/// \Test Case Description
///        - Test subject: Test if function gets filtered balanced value of analog height sensor inputs
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set sensor measurements - period or duty cycle
///         Step1: Convert to internal % format 0%..100% = 0x0 .. 0xFFFF
///         Step1: Set the duty cycle to exceeds 95%
///         Step2: Call the function IoHwAbUser_CalcInputPwmSens()
///         Step3: Check the measurements mode
///
/// - Preconditions:
///
/// \input IoHwAbUser_ucMeasMode                      = 1u
/// \input Icu_GetMeasurementSens_RetVal              = 150u
/// \input IoHwAbUser_unSensMeasPeriodAndDuty[0][0]   = 1500u
/// \input IoHwAbUser_unSensMeasPeriodAndDuty[1][0]   = 1500u
/// \input unSensPeriodPwm0_Err                       = 160u
/// \input unSensPeriodPwm1_Err                       = 160u
/// \input Mt_IoHwAb_FTM0Register                     = 10u
/// \input Mt_IoHwAb_FTM4Register                     = 10u
/// \input Mt_IoHwAb_CHOV_BitStatus                   = 10u
/// \input IoHwAbUser_unSensCalculatedDuty[0]         = 0u
/// \input IoHwAbUser_unSensCalculatedDuty[1]         = 0u
///
/// - Expectations:
///
/// \output IoHwAbUser_unSensCalculatedDuty[0]        = 0xFFFFu
/// \output IoHwAbUser_unSensCalculatedDuty[1]        = 0xFFFFu
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_CalcInputPwmSens_TestCase_7(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_ucMeasMode = 1u;
  Icu_GetMeasurementSens_RetVal = 150u;
  IoHwAbUser_unSensMeasPeriodAndDuty[0][0] = 1500u;
  IoHwAbUser_unSensMeasPeriodAndDuty[1][0] = 1500u;
  unSensPeriodPwm0_Err = 160u;
  unSensPeriodPwm1_Err = 160u;
  Mt_IoHwAb_FTM0Register = 10u;
  Mt_IoHwAb_FTM4Register = 10u;
  Mt_IoHwAb_CHOV_BitStatus = 10u;
  IoHwAbUser_unSensCalculatedDuty[0] = 0u;
  IoHwAbUser_unSensCalculatedDuty[1] = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_CalcInputPwmSens();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_unSensCalculatedDuty[0], 0xFFFFu, == );
  AL_UNITTEST_CHECK(IoHwAbUser_unSensCalculatedDuty[1], 0xFFFFu, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_IoHwAb_IoHwAbUser_CalcInputPwmSens
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function calculates the input PWM
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_CalcInputPwmSens(void)
{
  Mt_IoHwAb_IoHwAbUser_CalcInputPwmSens_TestCase_1();
  Mt_IoHwAb_IoHwAbUser_CalcInputPwmSens_TestCase_2();
  Mt_IoHwAb_IoHwAbUser_CalcInputPwmSens_TestCase_3();
  Mt_IoHwAb_IoHwAbUser_CalcInputPwmSens_TestCase_4();
  Mt_IoHwAb_IoHwAbUser_CalcInputPwmSens_TestCase_5();
  Mt_IoHwAb_IoHwAbUser_CalcInputPwmSens_TestCase_6();
  Mt_IoHwAb_IoHwAbUser_CalcInputPwmSens_TestCase_7();
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAbUser_CheckSens0_OpenLoad_TestCase_1
///
/// \Test Case Description
///        - Test subject: Check if CHOV bit of Channel 0 Status And Control register to confirm
///                         if Bhs sensor 0 is on high or low edge
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set register value
///         Step2: Call the function IoHwAbUser_CheckSens0_OpenLoad()
///         Step3: Check the returned value
///
/// - Preconditions:
///
/// \input Mt_IoHwAb_FTM0Register                            = 0u
/// \input Mt_IoHwAb_CHOV_BitStatus                          = 8u
///
/// - Expectations:
///

/// \output IoHwAbUser_CheckSens0_OpenLoad_RetVal       = 0u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_CheckSens0_OpenLoad_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Mt_IoHwAb_FTM0Register = 0u;
  Mt_IoHwAb_CHOV_BitStatus = 8u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_CheckSens0_OpenLoad_RetVal = IoHwAbUser_CheckSens0_OpenLoad();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_CheckSens0_OpenLoad_RetVal, 0u, == );
}


// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAbUser_CheckSens0_OpenLoad_TestCase_2
///
/// \Test Case Description
///        - Test subject: Check if CHOV bit of Channel 0 Status And Control register to confirm
///                         if Bhs sensor 0 is on high or low edge
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set register value
///         Step2: Call the function IoHwAbUser_CheckSens0_OpenLoad()
///         Step3: Check the returned value
///
/// - Preconditions:
///
/// \input Mt_IoHwAb_FTM0Register                            = 1u
/// \input Mt_IoHwAb_CHOV_BitStatus                          = 1u
///
/// - Expectations:
///

/// \output IoHwAbUser_CheckSens0_OpenLoad_RetVal           = 1u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_CheckSens0_OpenLoad_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Mt_IoHwAb_FTM0Register = 1u;
  Mt_IoHwAb_CHOV_BitStatus = 1u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_CheckSens0_OpenLoad_RetVal = IoHwAbUser_CheckSens0_OpenLoad();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_CheckSens0_OpenLoad_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_IoHwAb_IoHwAbUser_CheckSens0_OpenLoad
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function reports sensor 0 open load
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_CheckSens0_OpenLoad(void)
{
  Mt_IoHwAb_IoHwAbUser_CheckSens0_OpenLoad_TestCase_1();
  Mt_IoHwAb_IoHwAbUser_CheckSens0_OpenLoad_TestCase_2();
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAbUser_CheckSens1_OpenLoad_TestCase_1
///
/// \Test Case Description
///        - Test subject: Check if CHOV bit of Channel 0 Status And Control register to confirm
///                         if Bhs sensor 0 is on high or low edge
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set register value
///         Step2: Call the function IoHwAbUser_CheckSens1_OpenLoad()
///         Step3: Check the returned value
///
/// - Preconditions:
///
/// \input Mt_IoHwAb_FTM4Register                            = 1u
/// \input Mt_IoHwAb_CHOV_BitStatus                          = 1u
///
/// - Expectations:
///

/// \output IoHwAbUser_CheckSens1_OpenLoad_RetVal            = 1u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_CheckSens1_OpenLoad_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Mt_IoHwAb_FTM4Register = 1u;
  Mt_IoHwAb_CHOV_BitStatus = 1u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_CheckSens1_OpenLoad_RetVal = IoHwAbUser_CheckSens1_OpenLoad();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_CheckSens1_OpenLoad_RetVal, 1u, == );
}


// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAbUser_CheckSens1_OpenLoad_TestCase_2
///
/// \Test Case Description
///        - Test subject: Check if CHOV bit of Channel 0 Status And Control register to confirm
///                         if Bhs sensor 0 is on high or low edge
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set register value
///         Step2: Call the function IoHwAbUser_CheckSens1_OpenLoad()
///         Step3: Check the returned value
///
/// - Preconditions:
///
/// \input Mt_IoHwAb_FTM4Register                            = 0u
/// \input Mt_IoHwAb_CHOV_BitStatus                          = 0u
///
/// - Expectations:
///

/// \output IoHwAbUser_CheckSens1_OpenLoad_RetVal           = 0u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_CheckSens1_OpenLoad_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Mt_IoHwAb_FTM4Register = 0u;
  Mt_IoHwAb_CHOV_BitStatus = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_CheckSens1_OpenLoad_RetVal = IoHwAbUser_CheckSens1_OpenLoad();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_CheckSens1_OpenLoad_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_IoHwAb_IoHwAbUser_CheckSens1_OpenLoad
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function reports sensor 1 open load
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_CheckSens1_OpenLoad(void)
{
  Mt_IoHwAb_IoHwAbUser_CheckSens1_OpenLoad_TestCase_1();
  Mt_IoHwAb_IoHwAbUser_CheckSens1_OpenLoad_TestCase_2();
}

// This function is needed to simulate IoHwAbUser_CheckSens0_OpenLoad()
void Mt_IoHwAbuser_GetFTM0RegisterValues(uint32* Mt_IoHwAbuser_FTM0)
{
  Mt_IoHwAbuser_FTM0[0] = Mt_IoHwAb_FTM0Register;
  Mt_IoHwAbuser_FTM0[1] = Mt_IoHwAb_CHOV_BitStatus;
  //Mt_IoHwAbuser_CHOV_BitStatus = Mt_IoHwAb_CHOV_BitStatus;
}

// This function is needed to simulate IoHwAbUser_CheckSens1_OpenLoad()
void Mt_IoHwAbuser_GetFTM4RegisterValues(uint32* Mt_IoHwAbuser_FTM4)
{
  Mt_IoHwAbuser_FTM4[0] = Mt_IoHwAb_FTM4Register;
  Mt_IoHwAbuser_FTM4[1] = Mt_IoHwAb_CHOV_BitStatus;
  //Mt_IoHwAbuser_CHOV_BitStatus = Mt_IoHwAb_CHOV_BitStatus;
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAbUser_ReportVccx2Error_TestCase_1
///
/// \Test Case Description
///        - Test subject: Set or clear the specific DTC for short to vbat/short to ground for vccx2
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test, fault injection test
///
/// \Steps:
///         Step1: Set the VCCX1 error state
///         Step2: Call the function IoHwAbUser_ReportVccx2Error()
///         Step3: Check status of the DTC
///
/// - Preconditions:
///
/// \input IoHwAbUser_ReportVccx2Error_Param1              = eIoHwAb_Vccx_Short2Vbat
/// \input Dem_SetEventStatus_HitCount                     = 0u
///
/// - Expectations:
///

/// \output Dem_SetEventStatus_Param1                      = VCCX2_SC_BAT
/// \output Dem_SetEventStatus_Param2                      = DEM_EVENT_STATUS_FAILED
/// \output Dem_SetEventStatus_HitCount                    = 1u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_ReportVccx2Error_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_ReportVccx2Error_Param1 = eIoHwAb_Vccx_Short2Vbat;
  Dem_SetEventStatus_HitCount = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_ReportVccx2Error(IoHwAbUser_ReportVccx2Error_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, VCCX2_SC_BAT, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, DEM_EVENT_STATUS_FAILED, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 1u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAbUser_ReportVccx2Error_TestCase_2
///
/// \Test Case Description
///        - Test subject: Set or clear the specific DTC for short to vbat/short to ground for vccx2
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test, fault injection test
///
/// \Steps:
///         Step1: Set the VCCX1 error state 
///         Step2: Call the function IoHwAbUser_ReportVccx2Error()
///         Step3: Check status of the DTC
///
/// - Preconditions:
///
/// \input IoHwAbUser_ReportVccx2Error_Param1              = eIoHwAb_Vccx_Short2GND
/// \input Dem_SetEventStatus_HitCount                     = 0u
///
/// - Expectations:
///

/// \output Dem_SetEventStatus_Param1                      = VCCX2_SC_BAT
/// \output Dem_SetEventStatus_Param2                      = DEM_EVENT_STATUS_FAILED
/// \output Dem_SetEventStatus_HitCount                    = 1u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_ReportVccx2Error_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_ReportVccx2Error_Param1 = eIoHwAb_Vccx_Short2GND;
  Dem_SetEventStatus_HitCount = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_ReportVccx2Error(IoHwAbUser_ReportVccx2Error_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, VCCX2_SC_GND, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, DEM_EVENT_STATUS_FAILED, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 1u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAbUser_ReportVccx2Error_TestCase_3
///
/// \Test Case Description
///        - Test subject: Set or clear the specific DTC for short to vbat/short to ground for vccx2
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the VCCX1 error state 
///         Step2: Call the function IoHwAbUser_ReportVccx2Error()
///         Step3: Check status of the DTC
///
/// - Preconditions:
///
/// \input IoHwAbUser_ReportVccx2Error_Param1              = eIoHwAb_Vccx_noError
/// \input Dem_SetEventStatus_HitCount                     = 0u
///
/// - Expectations:
///

/// \output Dem_SetEventStatus_Param1                      = VCCX2_SC_BAT
/// \output Dem_SetEventStatus_Param2                      = DEM_EVENT_STATUS_FAILED
/// \output Dem_SetEventStatus_HitCount                    = 2u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_ReportVccx2Error_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_ReportVccx2Error_Param1 = eIoHwAb_Vccx_noError;
  Dem_SetEventStatus_HitCount = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_ReportVccx2Error(IoHwAbUser_ReportVccx2Error_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, VCCX2_SC_BAT, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, DEM_EVENT_STATUS_PASSED, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 2u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAbUser_ReportVccx2Error_TestCase_4
///
/// \Test Case Description
///        - Test subject: Set or clear the specific DTC for short to vbat/short to ground for vccx2
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the VCCX1 error state 
///         Step2: Call the function IoHwAbUser_ReportVccx2Error()
///         Step3: Check status of the DTC
///
/// - Preconditions:
///
/// \input IoHwAbUser_ReportVccx2Error_Param1              = 255u
/// \input Dem_SetEventStatus_HitCount                     = 0u
///
/// - Expectations:
///

/// \output Dem_SetEventStatus_Param1                      = VCCX2_SC_BAT
/// \output Dem_SetEventStatus_Param2                      = DEM_EVENT_STATUS_FAILED
/// \output Dem_SetEventStatus_HitCount                    = 0u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_ReportVccx2Error_TestCase_4(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_ReportVccx2Error_Param1 = 255u;
  Dem_SetEventStatus_HitCount = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_ReportVccx2Error(IoHwAbUser_ReportVccx2Error_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, VCCX2_SC_BAT, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, DEM_EVENT_STATUS_PASSED, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_IoHwAb_IoHwAbUser_ReportVccx2Error
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function reports vccx2 errors
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_ReportVccx2Error(void)
{
  Mt_IoHwAb_IoHwAbUser_ReportVccx2Error_TestCase_1();
  Mt_IoHwAb_IoHwAbUser_ReportVccx2Error_TestCase_2();
  Mt_IoHwAb_IoHwAbUser_ReportVccx2Error_TestCase_3();
  Mt_IoHwAb_IoHwAbUser_ReportVccx2Error_TestCase_4();
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAb_User_SetDio_EN_DC
///
/// \Test Case Description
///        - Test subject: Set the signal for channel 2(DC)
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the signal 
///         Step2: Write the value of the signal for channel 2
///
/// - Preconditions:
///
/// \input IoHwAb_User_SetDio_EN_DC_Param1              = 1u
///
/// - Expectations:
///

/// \output Dio_WriteChannel_Param2                      = 1u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAb_User_SetDio_EN_DC(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAb_User_SetDio_EN_DC_Param1 = 1u;;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAb_User_SetDio_EN_DC(IoHwAb_User_SetDio_EN_DC_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Dio_WriteChannel_Param2, 1u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAbUser_GetAdc_VoltDC_OUT1
///
/// \Test Case Description
///        - Test subject: SGet the adc filtered value for DC output 1.
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Take the filtered signal value of the adc for DC out1
///
/// - Preconditions:
///
/// \input IoHwAbUser_GetAdc_VoltDC_OUT1_Param1              = 1u
/// \input IoHwAbUser_aFltDC_OUT                             = 10u
/// \input UtilMath_FastIir_u_GetResult_HitCount             = 0u
///
/// - Expectations:
///

/// \output UtilMath_FastIir_u_GetResult_Param1              = 10u
/// \output UtilMath_FastIir_u_GetResult_HitCount            = 1u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_GetAdc_VoltDC_OUT1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_GetAdc_VoltDC_OUT1_Param1 = 1u;
  IoHwAbUser_aFltDC_OUT = 10u;
  UtilMath_FastIir_u_GetResult_HitCount = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_GetAdc_VoltDC_OUT1(&IoHwAbUser_GetAdc_VoltDC_OUT1_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(UtilMath_FastIir_u_GetResult_Param1, 10u, == );
  AL_UNITTEST_CHECK(UtilMath_FastIir_u_GetResult_HitCount, 1u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAbUser_SetTgtHss3_TestCase_1
///
/// \Test Case Description
///        - Test subject: Set the pwm duty cycle for HSS3
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Take the value of the pwm duty
///         Step2: Check if the duty is higher than IOHWABUSER_MAX_TARGET_VALUE
///         Step3: If the duty is higher than IOHWABUSER_MAX_TARGET_VALUE limit the duty to IOHWABUSER_MAX_TARGET_VALUE
///         Step4: Set the duty cycle for HSS3 
///
/// - Preconditions:
///
/// \input IoHwAbUser_SetTgtHss3_Param1              = IOHWABUSER_MAX_TARGET_VALUE + 1
///
/// - Expectations:
///

/// \output Pwm_SetDutyCycle_Param1                   = IOHWABUSER_MAX_TARGET_VALUE
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_SetTgtHss3_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetTgtHss3_Param1 = IOHWABUSER_MAX_TARGET_VALUE + 1;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetTgtHss3(IoHwAbUser_SetTgtHss3_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_Param2, IOHWABUSER_MAX_TARGET_VALUE, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAb_IoHwAbUser_SetTgtHss3_TestCase_2
///
/// \Test Case Description
///        - Test subject: Set the pwm duty cycle for HSS3
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Take the value of the pwm duty
///         Step2: Check if the duty is higher than IOHWABUSER_MAX_TARGET_VALUE
///         Step3: If the duty is higher than IOHWABUSER_MAX_TARGET_VALUE limit the duty to IOHWABUSER_MAX_TARGET_VALUE
///         Step4: Set the duty cycle for HSS3 
///
/// - Preconditions:
///
/// \input IoHwAbUser_SetTgtHss3_Param1              = 25000u
///
/// - Expectations:
///

/// \output Pwm_SetDutyCycle_Param1                   = 25000u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_SetTgtHss3_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetTgtHss3_Param1 = 25000u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetTgtHss3(IoHwAbUser_SetTgtHss3_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_Param2, 25000u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_IoHwAb_IoHwAbUser_SetTgtHss3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function sets hss3 PWM
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_IoHwAb_IoHwAbUser_SetTgtHss3(void)
{
  Mt_IoHwAb_IoHwAbUser_SetTgtHss3_TestCase_1();
  Mt_IoHwAb_IoHwAbUser_SetTgtHss3_TestCase_2();
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_reIoHwAbUser_GetLssDiagnostic_TestCase_1
///
/// \Test Case Description
///        - Test subject: Event runnable for LSS Diagnostic set (based on input coding)
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Read RTE port for LSS diagnostic
///         Step2: Call IoHwAbUser_SetLSSDiagnostic to set the global LSS diagnostic flag
///
/// - Preconditions:
///
/// \input Rte_Read_CddSwi_ScrollingOn_Stat_HitCount              = 0u
/// \input IoHwAb_boLssDiagnostic                                 = FALSE
/// \input Rte_Read_CddSwi_ScrollingOn_Stat_Param1 =              = &Temp1
/// \input Temp1 =                                                = &FALSE

///
/// - Expectations:
///

/// \output IoHwAb_boLssDiagnostic                                = FALSE
/// \output Rte_Read_CddSwi_ScrollingOn_Stat_HitCount             = 1u
///
//-----------------------------------------------------------------------------
void Mt_reIoHwAbUser_GetLssDiagnostic_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Rte_Read_CddSwi_ScrollingOn_Stat_HitCount = 0u;
  IoHwAb_boLssDiagnostic = FALSE;
  boolean Temp1 = FALSE;
  Rte_Read_CddSwi_ScrollingOn_Stat_Param1 = &Temp1;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  reIoHwAbUser_GetLssDiagnostic();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAb_boLssDiagnostic, FALSE, == );
  AL_UNITTEST_CHECK(Rte_Read_CddSwi_ScrollingOn_Stat_HitCount, 1u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_reIoHwAbUser_GetLssDiagnostic_TestCase_2
///
/// \Test Case Description
///        - Test subject: Event runnable for LSS Diagnostic set (based on input coding)
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Read RTE port for LSS diagnostic
///         Step2: Call IoHwAbUser_SetLSSDiagnostic to set the global LSS diagnostic flag
///
/// - Preconditions:
///
/// \input Rte_Read_CddSwi_ScrollingOn_Stat_HitCount              = 0u
/// \input IoHwAb_boLssDiagnostic                                 = FALSE
/// \input Rte_Read_CddSwi_ScrollingOn_Stat_Param1 =              = &Temp1
/// \input Temp1 =                                                = TRUE

///
/// - Expectations:
///

/// \output IoHwAb_boLssDiagnostic                                = TRUE
/// \output Rte_Read_CddSwi_ScrollingOn_Stat_HitCount             = 1u
///
//-----------------------------------------------------------------------------
void Mt_reIoHwAbUser_GetLssDiagnostic_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Rte_Read_CddSwi_ScrollingOn_Stat_HitCount = 0u;
  IoHwAb_boLssDiagnostic = FALSE;
  boolean Temp1 = TRUE;
  Rte_Read_CddSwi_ScrollingOn_Stat_Param1 = &Temp1;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  reIoHwAbUser_GetLssDiagnostic();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAb_boLssDiagnostic, TRUE, == );
  AL_UNITTEST_CHECK(Rte_Read_CddSwi_ScrollingOn_Stat_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_reIoHwAbUser_GetLssDiagnostic
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test Event runnable for LSS Diagnostic
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_reIoHwAbUser_GetLssDiagnostic(void)
{
  Mt_reIoHwAbUser_GetLssDiagnostic_TestCase_1();
  Mt_reIoHwAbUser_GetLssDiagnostic_TestCase_2();
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAbUser_GetOutFctDiag_TestCase_1
///
/// \Test Case Description
///        - Test subject: LSS Error Getter based on global error flags
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the error global flags for short to ground, short to Vbat
///         Step2: Call IoHwAbUser_GetOutFctDiag to return the status of LSS error
///
/// - Preconditions:
///
/// \input IoHwAbUser_GetOutFctDiag_Param1[0]                     = FALSE
/// \input IoHwAbUser_GetOutFctDiag_Param1[1]                     = FALSE
/// \input IoHwAbUser_boFctOut_ShGnd                              = FALSE
/// \input IoHwAbUser_boFctOut_ShVbat                             = FALSE
///
/// - Expectations:
///
/// \output IoHwAbUser_GetOutFctDiag_Param1[0]                    = FALSE
/// \output IoHwAbUser_GetOutFctDiag_Param1[1]                    = FALSE
///
//-----------------------------------------------------------------------------
void Mt_IoHwAbUser_GetOutFctDiag_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_GetOutFctDiag_Param1[0] = FALSE;
  IoHwAbUser_GetOutFctDiag_Param1[1] = FALSE;
  IoHwAbUser_boFctOut_ShGnd = FALSE;
  IoHwAbUser_boFctOut_ShVbat = FALSE;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_GetOutFctDiag(&IoHwAbUser_GetOutFctDiag_Param1[0]);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_GetOutFctDiag_Param1[0], FALSE, == );
  AL_UNITTEST_CHECK(IoHwAbUser_GetOutFctDiag_Param1[1], FALSE, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAbUser_GetOutFctDiag_TestCase_2
///
/// \Test Case Description
///        - Test subject: LSS Error Getter based on global error flags
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the error global flags for short to ground, short to Vbat
///         Step2: Call IoHwAbUser_GetOutFctDiag to return the status of LSS error
///
/// - Preconditions:
///
/// \input IoHwAbUser_GetOutFctDiag_Param1[0]                     = FALSE
/// \input IoHwAbUser_GetOutFctDiag_Param1[1]                     = FALSE
/// \input IoHwAbUser_boFctOut_ShGnd                              = TRUE
/// \input IoHwAbUser_boFctOut_ShVbat                             = TRUE
///
/// - Expectations:
///
/// \output IoHwAbUser_GetOutFctDiag_Param1[0]                    = TRUE
/// \output IoHwAbUser_GetOutFctDiag_Param1[1]                    = TRUE
///
//-----------------------------------------------------------------------------
void Mt_IoHwAbUser_GetOutFctDiag_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_GetOutFctDiag_Param1[0] = FALSE;
  IoHwAbUser_GetOutFctDiag_Param1[1] = FALSE;
  IoHwAbUser_boFctOut_ShGnd = TRUE;
  IoHwAbUser_boFctOut_ShVbat = TRUE;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_GetOutFctDiag(&IoHwAbUser_GetOutFctDiag_Param1[0]);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_GetOutFctDiag_Param1[0], TRUE, == );
  AL_UNITTEST_CHECK(IoHwAbUser_GetOutFctDiag_Param1[1], TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_IoHwAbUser_GetOutFctDiag
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test LSS Error Getter 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_IoHwAbUser_GetOutFctDiag(void)
{
  Mt_IoHwAbUser_GetOutFctDiag_TestCase_1();
  Mt_IoHwAbUser_GetOutFctDiag_TestCase_2();
}


// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAbUser_ProcessOutFctDiag_TestCase_1
///
/// \Test Case Description
///        - Test subject: Check LSS diagnostic when new CddSbc LSS Pwm is targeted
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the Old LSS Pwm target
///         Step2: Set the New and Different LSS Pwm target
///         Step2: Call IoHwAbUser_ProcessOutFctDiag to reset LSS voltage measurements
///
/// - Preconditions:
///
/// \input unOld_PWM                                              = 0u
/// \input CddSbc_GetPWM_HitCount                                 = 0u
/// \input CddSbc_GetPWM_RetVal                                   = 5000u
/// \input CddSbc_GetPWM_Param1                                   = 0xFFu
/// \input IoHwAbUser_ulFctOut_Voltage_Acc                        = 12345u
/// \input IoHwAbUser_ulFctOut_Cnt                                = 25u
///
/// - Expectations:
///
/// \output CddSbc_GetPWM_HitCount                                = 1u
/// \output CddSbc_GetPWM_Param1                                  = 0u
/// \output unNew_PWM                                             = 5000u
/// \output IoHwAbUser_ulFctOut_Voltage_Acc                       = 0u
/// \output IoHwAbUser_ulFctOut_Cnt                               = 0u
/// \output unOld_PWM                                             = 5000u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAbUser_ProcessOutFctDiag_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  unOld_PWM = 0u;
  CddSbc_GetPWM_HitCount = 0u;
  CddSbc_GetPWM_RetVal = 5000u;
  CddSbc_GetPWM_Param1 = 0xFFu;
  IoHwAbUser_ulFctOut_Voltage_Acc = 12345u;
  IoHwAbUser_ulFctOut_Cnt = 25u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_ProcessOutFctDiag();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(CddSbc_GetPWM_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CddSbc_GetPWM_Param1, 0u, == );
  AL_UNITTEST_CHECK(unNew_PWM, 5000u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_ulFctOut_Voltage_Acc, 0u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_ulFctOut_Cnt, 0u, == );
  AL_UNITTEST_CHECK(unOld_PWM, 5000u, == );
}


// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAbUser_ProcessOutFctDiag_TestCase_2
///
/// \Test Case Description
///        - Test subject: Check LSS diagnostic when there is no new CddSbc LSS Pwm targeted. The coverage case is when the sample point is not reached, so the voltage is accumulated
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the Old LSS Pwm target
///         Step2: Set the New LSS Pwm target equal to the old
///         Step2: Call IoHwAbUser_ProcessOutFctDiag to check LSS voltage measurements
///
/// - Preconditions:
///
/// \input unOld_PWM                                              = 5000u
/// \input CddSbc_GetPWM_HitCount                                 = 0u
/// \input CddSbc_GetPWM_RetVal                                   = 5000u
/// \input CddSbc_GetPWM_Param1                                   = 0xFFu
/// \input IoHwAbUser_ulFctOut_Voltage_Acc                        = 50500u
/// \input IoHwAbUser_ulFctOut_Cnt                                = 25u
/// \input Adc_ReadGroup_Param1                                   = 0u
/// \input Adc_ReadGroup_Param2                                   = 1200u
///
/// - Expectations:
///
/// \output CddSbc_GetPWM_HitCount                                = 1u
/// \output CddSbc_GetPWM_Param1                                  = 0u
/// \output unNew_PWM                                             = 5000u
/// \output IoHwAbUser_ulFctOut_Voltage_Acc                       = (50500u + 1200u)
/// \output IoHwAbUser_ulFctOut_Cnt                               = 26u
/// \output Adc_ReadGroup_Param1                                  = 21u
/// \output unOld_PWM                                             = 5000u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAbUser_ProcessOutFctDiag_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  unOld_PWM = 5000u;
  CddSbc_GetPWM_HitCount = 0u;
  CddSbc_GetPWM_RetVal = 5000u;
  CddSbc_GetPWM_Param1 = 0xFFu;
  IoHwAbUser_ulFctOut_Voltage_Acc = 50500u;
  IoHwAbUser_ulFctOut_Cnt = 25u;
  Adc_ReadGroup_Param1 = 0u;
  Adc_ReadGroup_Param2 = 1200u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_ProcessOutFctDiag();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(CddSbc_GetPWM_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CddSbc_GetPWM_Param1, 0u, == );
  AL_UNITTEST_CHECK(unNew_PWM, 5000u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_ulFctOut_Voltage_Acc, (50500u + 1200u), == );
  AL_UNITTEST_CHECK(IoHwAbUser_ulFctOut_Cnt, 26u, == );
  AL_UNITTEST_CHECK(Adc_ReadGroup_Param1, 21u, == );
  AL_UNITTEST_CHECK(unOld_PWM, 5000u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAbUser_ProcessOutFctDiag_TestCase_3
///
/// \Test Case Description
///        - Test subject: Check LSS diagnostic when there is no new CddSbc LSS Pwm targeted. The coverage case is when the sample point is reached, so the voltage mean is calculated. ShGnd is simulated.
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the Old LSS Pwm target
///         Step2: Set the New LSS Pwm target equal to the old
///         Step2: Call IoHwAbUser_ProcessOutFctDiag to check LSS voltage measurements.ShGnd is checked.
///
/// - Preconditions:
///
/// \input unOld_PWM                                              = 500u
/// \input CddSbc_GetPWM_HitCount                                 = 0u
/// \input CddSbc_GetPWM_RetVal                                   = 500u
/// \input CddSbc_GetPWM_Param1                                   = 0xFFu
/// \input IoHwAbUser_ulFctOut_Voltage_Acc                        = 290u
/// \input IoHwAbUser_ulFctOut_Cnt                                = 29u
/// \input Adc_ReadGroup_Param1                                   = 0u
/// \input Adc_ReadGroup_Param2                                   = 10u
/// \input IoHwAbUser_unFctOut_Voltage_mV                         = 0u
/// \input IoHwAbUser_unFactorFout                                = 24642u
/// \input IoHwAbUser_boFctOut_ShGnd                              = FALSE
///
/// - Expectations:
///
/// \output CddSbc_GetPWM_HitCount                                = 1u
/// \output CddSbc_GetPWM_Param1                                  = 0u
/// \output unNew_PWM                                             = 500u
/// \output IoHwAbUser_ulFctOut_Voltage_Acc                       = 0u
/// \output IoHwAbUser_ulFctOut_Cnt                               = 0u
/// \output Adc_ReadGroup_Param1                                  = 21u
/// \output unOld_PWM                                             = 500u
/// \output IoHwAbUser_unFctOut_Voltage_mV                        = (300u / 30u * IoHwAbUser_unFactorFout) / 4095u (60u)
/// \output IoHwAbUser_boFctOut_ShGnd                             = TRUE

///
//-----------------------------------------------------------------------------
void Mt_IoHwAbUser_ProcessOutFctDiag_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  unOld_PWM = 500u;
  CddSbc_GetPWM_HitCount = 0u;
  CddSbc_GetPWM_RetVal = 500u;
  CddSbc_GetPWM_Param1 = 0xFFu;
  IoHwAbUser_ulFctOut_Voltage_Acc = 290u;
  IoHwAbUser_ulFctOut_Cnt = 29u;
  Adc_ReadGroup_Param1 = 0u;
  Adc_ReadGroup_Param2 = 10u;
  IoHwAbUser_unFctOut_Voltage_mV = 0u;
  IoHwAbUser_unFactorFout = 24642u;
  IoHwAbUser_boFctOut_ShGnd = FALSE;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_ProcessOutFctDiag();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(CddSbc_GetPWM_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CddSbc_GetPWM_Param1, 0u, == );
  AL_UNITTEST_CHECK(unNew_PWM, 500u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_ulFctOut_Voltage_Acc, 0u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_ulFctOut_Cnt, 0u, == );
  AL_UNITTEST_CHECK(Adc_ReadGroup_Param1, 21u, == );
  AL_UNITTEST_CHECK(unOld_PWM, 500u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_unFctOut_Voltage_mV, (300u / 30u * IoHwAbUser_unFactorFout) / 4095u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_boFctOut_ShGnd, TRUE, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAbUser_ProcessOutFctDiag_TestCase_4
///
/// \Test Case Description
///        - Test subject: Check LSS diagnostic when there is no new CddSbc LSS Pwm targeted. The coverage case is when the sample point is reached, so the voltage mean is calculated. ShVbat is simulated.
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the Old LSS Pwm target
///         Step2: Set the New LSS Pwm target equal to the old
///         Step2: Call IoHwAbUser_ProcessOutFctDiag to check LSS voltage measurements.ShVbat is checked.
///
/// - Preconditions:
///
/// \input unOld_PWM                                              = 9500u
/// \input CddSbc_GetPWM_HitCount                                 = 0u
/// \input CddSbc_GetPWM_HitCount                                 = 0u
/// \input CddSbc_GetPWM_Param1                                   = 0xFFu
/// \input IoHwAbUser_ulFctOut_Voltage_Acc                        = 27200u
/// \input IoHwAbUser_ulFctOut_Cnt                                = 29u
/// \input Adc_ReadGroup_Param1                                   = 0u
/// \input Adc_ReadGroup_Param2                                   = 1000u
/// \input IoHwAbUser_unFctOut_Voltage_mV                         = 0u
/// \input IoHwAbUser_unFactorFout                                = 24642u
/// \input IoHwAbUser_boFctOut_ShGVbat                            = FALSE
///
/// - Expectations:
///
/// \output CddSbc_GetPWM_HitCount                                = 1u
/// \output CddSbc_GetPWM_Param1                                  = 0u
/// \output unNew_PWM                                             = 9500u
/// \output IoHwAbUser_ulFctOut_Voltage_Acc                       = 0u
/// \output IoHwAbUser_ulFctOut_Cnt                               = 0u
/// \output Adc_ReadGroup_Param1                                  = 21u
/// \output unOld_PWM                                             = 9500u
/// \output IoHwAbUser_unFctOut_Voltage_mV                        = (28200u / 30u * IoHwAbUser_unFactorFout) / 4095u (>5600u)
/// \output IoHwAbUser_boFctOut_ShVbat                            = TRUE
///
//-----------------------------------------------------------------------------
void Mt_IoHwAbUser_ProcessOutFctDiag_TestCase_4(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  unOld_PWM = 9500u;
  CddSbc_GetPWM_HitCount = 0u;
  CddSbc_GetPWM_RetVal = 9500u;
  CddSbc_GetPWM_Param1 = 0xFFu;
  IoHwAbUser_ulFctOut_Voltage_Acc = 27200u;
  IoHwAbUser_ulFctOut_Cnt = 29u;
  Adc_ReadGroup_Param1 = 0u;
  Adc_ReadGroup_Param2 = 1000u;
  IoHwAbUser_unFctOut_Voltage_mV = 0u;
  IoHwAbUser_unFactorFout = 24642u;
  IoHwAbUser_boFctOut_ShVbat = FALSE;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_ProcessOutFctDiag();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(CddSbc_GetPWM_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CddSbc_GetPWM_Param1, 0u, == );
  AL_UNITTEST_CHECK(unNew_PWM, 9500u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_ulFctOut_Voltage_Acc, 0u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_ulFctOut_Cnt, 0u, == );
  AL_UNITTEST_CHECK(Adc_ReadGroup_Param1, 21u, == );
  AL_UNITTEST_CHECK(unOld_PWM, 9500u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_unFctOut_Voltage_mV, (28200u / 30u * IoHwAbUser_unFactorFout) / 4095u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_boFctOut_ShVbat, TRUE, == );
}


// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAbUser_ProcessOutFctDiag_TestCase_5
///
/// \Test Case Description
///        - Test subject: Check LSS diagnostic when there is no new CddSbc LSS Pwm targeted. The coverage case is when the sample point is reached, so the voltage mean is calculated. ShGnd clear is simulated.
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the Old LSS Pwm target
///         Step2: Set the New LSS Pwm target equal to the old
///         Step2: Call IoHwAbUser_ProcessOutFctDiag to check LSS voltage measurements.ShGnd clear is checked.
///
/// - Preconditions:
///
/// \input unOld_PWM                                              = 500u
/// \input CddSbc_GetPWM_HitCount                                 = 0u
/// \input CddSbc_GetPWM_RetVal                                   = 500u
/// \input CddSbc_GetPWM_Param1                                   = 0xFFu
/// \input IoHwAbUser_ulFctOut_Voltage_Acc                        = 2450u
/// \input IoHwAbUser_ulFctOut_Cnt                                = 29u
/// \input Adc_ReadGroup_Param1                                   = 0u
/// \input Adc_ReadGroup_Param2                                   = 84u
/// \input IoHwAbUser_unFctOut_Voltage_mV                         = 0u
/// \input IoHwAbUser_unFactorFout                                = 24642u
/// \input IoHwAbUser_boFctOut_ShGVGnd                            = TRUE
///
/// - Expectations:
///
/// \output CddSbc_GetPWM_HitCount                                = 1u
/// \output CddSbc_GetPWM_Param1                                  = 0u
/// \output unNew_PWM                                             = 500u
/// \output IoHwAbUser_ulFctOut_Voltage_Acc                       = 0u
/// \output IoHwAbUser_ulFctOut_Cnt                               = 0u
/// \output Adc_ReadGroup_Param1                                  = 21u
/// \output unOld_PWM                                             = 500u
/// \output IoHwAbUser_unFctOut_Voltage_mV                        = (2534u / 30u * IoHwAbUser_unFactorFout) / 4095u (>500mV)
/// \output IoHwAbUser_boFctOut_ShGnd                             = FALSE
///
//-----------------------------------------------------------------------------
void Mt_IoHwAbUser_ProcessOutFctDiag_TestCase_5(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  unOld_PWM = 500u;
  CddSbc_GetPWM_HitCount = 0u;
  CddSbc_GetPWM_RetVal = 500u;
  CddSbc_GetPWM_Param1 = 0xFFu;
  IoHwAbUser_ulFctOut_Voltage_Acc = 2450u;
  IoHwAbUser_ulFctOut_Cnt = 29u;
  Adc_ReadGroup_Param1 = 0u;
  Adc_ReadGroup_Param2 = 84u;
  IoHwAbUser_unFctOut_Voltage_mV = 0u;
  IoHwAbUser_unFactorFout = 24642u;
  IoHwAbUser_boFctOut_ShGnd = TRUE;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_ProcessOutFctDiag();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(CddSbc_GetPWM_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CddSbc_GetPWM_Param1, 0u, == );
  AL_UNITTEST_CHECK(unNew_PWM, 500u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_ulFctOut_Voltage_Acc, 0u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_ulFctOut_Cnt, 0u, == );
  AL_UNITTEST_CHECK(Adc_ReadGroup_Param1, 21u, == );
  AL_UNITTEST_CHECK(unOld_PWM, 500u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_unFctOut_Voltage_mV, (2534u / 30u * IoHwAbUser_unFactorFout) / 4095u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_boFctOut_ShGnd, FALSE, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAbUser_ProcessOutFctDiag_TestCase_6
///
/// \Test Case Description
///        - Test subject: Check LSS diagnostic when there is no new CddSbc LSS Pwm targeted. The coverage case is when the sample point is reached, so the voltage mean is calculated. ShVbat clear is simulated.
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the Old LSS Pwm target
///         Step2: Set the New LSS Pwm target equal to the old
///         Step2: Call IoHwAbUser_ProcessOutFctDiag to check LSS voltage measurements.ShVbat clear is checked.
///
/// - Preconditions:
///
/// \input unOld_PWM                                              = 9500u
/// \input CddSbc_GetPWM_HitCount                                 = 0u
/// \input CddSbc_GetPWM_HitCount                                 = 0u
/// \input CddSbc_GetPWM_Param1                                   = 0xFFu
/// \input IoHwAbUser_ulFctOut_Voltage_Acc                        = 5770u
/// \input IoHwAbUser_ulFctOut_Cnt                                = 29u
/// \input Adc_ReadGroup_Param1                                   = 0u
/// \input Adc_ReadGroup_Param2                                   = 198u
/// \input IoHwAbUser_unFctOut_Voltage_mV                         = 0u
/// \input IoHwAbUser_unFactorFout                                = 24642u
/// \input IoHwAbUser_boFctOut_ShVbat                             = TRUE
///
/// - Expectations:
///
/// \output CddSbc_GetPWM_HitCount                                = 1u
/// \output CddSbc_GetPWM_Param1                                  = 0u
/// \output unNew_PWM                                             = 9500u
/// \output IoHwAbUser_ulFctOut_Voltage_Acc                       = 0u
/// \output IoHwAbUser_ulFctOut_Cnt                               = 0u
/// \output Adc_ReadGroup_Param1                                  = 21u
/// \output unOld_PWM                                             = 9500u
/// \output IoHwAbUser_unFctOut_Voltage_mV                        = (5968 / 30u * IoHwAbUser_unFactorFout) / 4095u (<1200mV)
/// \output IoHwAbUser_boFctOut_ShVbat                            = FALSE

///
//-----------------------------------------------------------------------------
void Mt_IoHwAbUser_ProcessOutFctDiag_TestCase_6(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  unOld_PWM = 9500u;
  CddSbc_GetPWM_HitCount = 0u;
  CddSbc_GetPWM_RetVal = 9500u;
  CddSbc_GetPWM_Param1 = 0xFFu;
  IoHwAbUser_ulFctOut_Voltage_Acc = 5770u;
  IoHwAbUser_ulFctOut_Cnt = 29u;
  Adc_ReadGroup_Param1 = 0u;
  Adc_ReadGroup_Param2 = 198u;
  IoHwAbUser_unFctOut_Voltage_mV = 0u;
  IoHwAbUser_unFactorFout = 24642u;
  IoHwAbUser_boFctOut_ShVbat = TRUE;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_ProcessOutFctDiag();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(CddSbc_GetPWM_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CddSbc_GetPWM_Param1, 0u, == );
  AL_UNITTEST_CHECK(unNew_PWM, 9500u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_ulFctOut_Voltage_Acc, 0u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_ulFctOut_Cnt, 0u, == );
  AL_UNITTEST_CHECK(Adc_ReadGroup_Param1, 21u, == );
  AL_UNITTEST_CHECK(unOld_PWM, 9500u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_unFctOut_Voltage_mV, (5968u / 30u * IoHwAbUser_unFactorFout) / 4095u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_boFctOut_ShVbat, FALSE, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAbUser_ProcessOutFctDiag_TestCase_7
///
/// \Test Case Description
///        - Test subject: Check LSS diagnostic when there is no new CddSbc LSS Pwm targeted. The coverage case is when the sample point is reached, so the voltage mean is calculated. No reaction for some errors.
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the Old LSS Pwm target
///         Step2: Set the New LSS Pwm target equal to the old
///         Step2: Call IoHwAbUser_ProcessOutFctDiag to check LSS voltage measurements.No further reaction.
///
/// - Preconditions:
///
/// \input unOld_PWM                                              = 9500u
/// \input CddSbc_GetPWM_HitCount                                 = 0u
/// \input CddSbc_GetPWM_RetVal                                   = 9500u
/// \input CddSbc_GetPWM_Param1                                   = 0xFFu
/// \input IoHwAbUser_ulFctOut_Voltage_Acc                        = 27200u
/// \input IoHwAbUser_ulFctOut_Cnt                                = 29u
/// \input Adc_ReadGroup_Param1                                   = 0u
/// \input Adc_ReadGroup_Param2                                   = 1000u
/// \input IoHwAbUser_unFctOut_Voltage_mV                         = 0u
/// \input IoHwAbUser_unFactorFout                                = 24642u
/// \input IoHwAbUser_boFctOut_ShVbat                             = TRUE
///
/// - Expectations:
///
/// \output CddSbc_GetPWM_HitCount                                = 1u
/// \output CddSbc_GetPWM_Param1                                  = 0u
/// \output unNew_PWM                                             = 9500u
/// \output IoHwAbUser_ulFctOut_Voltage_Acc                       = 0u
/// \output IoHwAbUser_ulFctOut_Cnt                               = 0u
/// \output Adc_ReadGroup_Param1                                  = 21u
/// \output unOld_PWM                                             = 9500u
/// \output IoHwAbUser_unFctOut_Voltage_mV                        = (28200u / 30u * IoHwAbUser_unFactorFout) / 4095u (>5600mV)
/// \output IoHwAbUser_boFctOut_ShVbat                            = TRUE

///
//-----------------------------------------------------------------------------
void Mt_IoHwAbUser_ProcessOutFctDiag_TestCase_7(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  unOld_PWM = 9500u;
  CddSbc_GetPWM_HitCount = 0u;
  CddSbc_GetPWM_RetVal = 9500u;
  CddSbc_GetPWM_Param1 = 0xFFu;
  IoHwAbUser_ulFctOut_Voltage_Acc = 20200u;
  IoHwAbUser_ulFctOut_Cnt = 29u;
  Adc_ReadGroup_Param1 = 0u;
  Adc_ReadGroup_Param2 = 1000u;
  IoHwAbUser_unFctOut_Voltage_mV = 0u;
  IoHwAbUser_unFactorFout = 24642u;
  IoHwAbUser_boFctOut_ShVbat = TRUE;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_ProcessOutFctDiag();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(CddSbc_GetPWM_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CddSbc_GetPWM_Param1, 0u, == );
  AL_UNITTEST_CHECK(unNew_PWM, 9500u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_ulFctOut_Voltage_Acc, 0u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_ulFctOut_Cnt, 0u, == );
  AL_UNITTEST_CHECK(Adc_ReadGroup_Param1, 21u, == );
  AL_UNITTEST_CHECK(unOld_PWM, 9500u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_unFctOut_Voltage_mV, (21200u / 30u * IoHwAbUser_unFactorFout) / 4095u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_boFctOut_ShVbat, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_IoHwAbUser_ProcessOutFctDiag
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test LSS function diag
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_IoHwAbUser_ProcessOutFctDiag(void)
{
  Mt_IoHwAbUser_ProcessOutFctDiag_TestCase_1();
  Mt_IoHwAbUser_ProcessOutFctDiag_TestCase_2();
  Mt_IoHwAbUser_ProcessOutFctDiag_TestCase_3();
  Mt_IoHwAbUser_ProcessOutFctDiag_TestCase_4();
  Mt_IoHwAbUser_ProcessOutFctDiag_TestCase_5();
  Mt_IoHwAbUser_ProcessOutFctDiag_TestCase_6();
  Mt_IoHwAbUser_ProcessOutFctDiag_TestCase_7();
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAbUser_SetNvm_ElecError_TestCase_1
///
/// \Test Case Description
///        - Test subject: HLS no error detection test. Nvm update not required
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the target levelling out of errors
///         Step2: Check the Nvm hit count (Nvm write not required) and no errors detection
///
/// - Preconditions:
///
/// \input IoHwAbUser_SetNvm_ElecError_Param1                     = 0u
/// \input IoHwAbUser_unSensCalculatedDuty[0u]                    = 0xD00u
/// \input eSensShVbatNew[0]                                      = eIoHwAb_Hls_noError
/// \input eSensShGndNew[0]                                       = eIoHwAb_Hls_noError
/// \input NvmBlockDeltaPwmPara.ucSensVbatError[0u]               = 0u
/// \input NvmBlockDeltaPwmPara.ucSensGndError[0u]                = 0u
/// \input NvM_WriteBlock_HitCount                                = 0u
///
/// - Expectations:
///
/// \output eSensShVbatNew[0]                                     = eIoHwAb_Hls_noError
/// \output eSensShGndNew[0]                                      = eIoHwAb_Hls_noError
/// \output NvmBlockDeltaPwmPara.ucSensVbatError[0u]              = 0u
/// \output NvmBlockDeltaPwmPara.ucSensGndError[0u]               = 0u
/// \output NvM_WriteBlock_HitCount                               = 0u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAbUser_SetNvm_ElecError_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetNvm_ElecError_Param1 = 0u;
  IoHwAbUser_unSensCalculatedDuty[0u] = 0xD00u;
  eSensShVbatNew[0] = eIoHwAb_Hls_Error;
  eSensShGndNew[0] = eIoHwAb_Hls_Error;
  NvmBlockDeltaPwmPara.ucSensVbatError[0u] = 0u;
  NvmBlockDeltaPwmPara.ucSensGndError[0u] = 0u;
  NvM_WriteBlock_HitCount = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetNvm_ElecError(IoHwAbUser_SetNvm_ElecError_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(eSensShVbatNew[0], eIoHwAb_Hls_noError, == );
  AL_UNITTEST_CHECK(eSensShGndNew[0], eIoHwAb_Hls_noError, == );
  AL_UNITTEST_CHECK(NvmBlockDeltaPwmPara.ucSensVbatError[0u], 0u, == );
  AL_UNITTEST_CHECK(NvmBlockDeltaPwmPara.ucSensGndError[0u], 0u, == );
  AL_UNITTEST_CHECK(NvM_WriteBlock_HitCount, 0u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAbUser_SetNvm_ElecError_TestCase_2
///
/// \Test Case Description
///        - Test subject: HLS short to Vbat error detection test. No Nvm update not required
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the target levelling  for Vbat short error
///         Step2: Check the Nvm hit count (No Nvm write required) and timer is triggered
///
/// - Preconditions:
///
/// \input IoHwAbUser_SetNvm_ElecError_Param1       = 0u;
/// \input IoHwAbUser_unSensCalculatedDuty[0u]      = IOHWABSUSER_95_PERCENT_PWM + 1u;
/// \input eSensShVbatNew[0]                        = eIoHwAb_Hls_noError;
/// \input eSensShGndNew[0]                         = eIoHwAb_Hls_noError;
/// \input boStartTimer[0]                          = FALSE;
/// \input ulDebounceTimer[0]                       = 0u;
/// \input LPTMR0_GetTimeElapsed_RetVal             = 10;
/// \input LPTMR0_GetTimeElapsed_HitCount           = 0u;
/// \input NvmBlockDeltaPwmPara.ucSensVbatError[0u] = 0u;
/// \input NvmBlockDeltaPwmPara.ucSensGndError[0u]  = 0u;
/// \input NvM_WriteBlock_HitCount                  = 0u;
/// \input NvM_WriteBlock_Param1                    = 0u;
/// \input NvM_WriteBlock_Param2                    = NULL_PTR;
///
/// - Expectations:
///
/// \output eSensShVbatNew[0]                        = eIoHwAb_Hls_noError
/// \output eSensShGndNew[0]                         = eIoHwAb_Hls_noError
/// \output NvmBlockDeltaPwmPara.ucSensVbatError[0u] = 0u
/// \output NvmBlockDeltaPwmPara.ucSensGndError[0u]  = 0u
/// \output boStartTimer[0]                          = TRUE
/// \output ulDebounceTimer[0]                       = 10
/// \output LPTMR0_GetTimeElapsed_HitCount           = 1u 
/// \output NvM_WriteBlock_HitCount                  = 0u 
///
//-----------------------------------------------------------------------------
void Mt_IoHwAbUser_SetNvm_ElecError_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetNvm_ElecError_Param1 = 0u;
  IoHwAbUser_unSensCalculatedDuty[0u] = IOHWABSUSER_95_PERCENT_PWM + 1u;
  eSensShVbatNew[0] = eIoHwAb_Hls_noError;
  eSensShGndNew[0] = eIoHwAb_Hls_noError;
  boStartTimer[0] = FALSE;
  ulDebounceTimer[0] = 0u;
  LPTMR0_GetTimeElapsed_RetVal = 10;
  LPTMR0_GetTimeElapsed_HitCount = 0u;
  NvmBlockDeltaPwmPara.ucSensVbatError[0u] = 0u;
  NvmBlockDeltaPwmPara.ucSensGndError[0u] = 0u;
  NvM_WriteBlock_HitCount = 0u;
  NvM_WriteBlock_Param1 = 0u;
  NvM_WriteBlock_Param2 = NULL_PTR;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetNvm_ElecError(IoHwAbUser_SetNvm_ElecError_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(eSensShVbatNew[0], eIoHwAb_Hls_noError, == );
  AL_UNITTEST_CHECK(eSensShGndNew[0], eIoHwAb_Hls_noError, == );
  AL_UNITTEST_CHECK(NvmBlockDeltaPwmPara.ucSensVbatError[0u], 0u, == );
  AL_UNITTEST_CHECK(NvmBlockDeltaPwmPara.ucSensGndError[0u], 0u, == );
  AL_UNITTEST_CHECK(boStartTimer[0], TRUE, == );
  AL_UNITTEST_CHECK(ulDebounceTimer[0], 10, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount, 1u, == );
  AL_UNITTEST_CHECK(NvM_WriteBlock_HitCount, 0u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAbUser_SetNvm_ElecError_TestCase_3
///
/// \Test Case Description
///        - Test subject: HLS short to Vbat error detection test. No Nvm update required
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the target levelling  for Vbat short error
///         Step2: Check the Nvm hit count (No Nvm write required) and timer is not done yet
///
/// - Preconditions:
///
/// \input IoHwAbUser_SetNvm_ElecError_Param1                     = 0u
/// \input IoHwAbUser_unSensCalculatedDuty[0u]                    = 0xF332u
/// \input eSensShVbatNew[0]                                      = eIoHwAb_Hls_noError
/// \input eSensShGndNew[0]                                       = eIoHwAb_Hls_noError
/// \input NvmBlockDeltaPwmPara.ucSensVbatError[0u]               = 0u
/// \input NvmBlockDeltaPwmPara.ucSensGndError[0u]                = 0u
/// \input NvM_WriteBlock_HitCount                                = 0u
/// \input NvM_WriteBlock_Param1                                  = 0u
/// \input NvM_WriteBlock_Param2                                  = NULL_PTR
///
/// - Expectations:
///
/// \output eSensShVbatNew[0]                        = eIoHwAb_Hls_noError
/// \output eSensShGndNew[0]                         = eIoHwAb_Hls_noError
/// \output NvmBlockDeltaPwmPara.ucSensVbatError[0u] = 0u
/// \output NvmBlockDeltaPwmPara.ucSensGndError[0u]  = 0u
/// \output boStartTimer[0]                          = TRUE
/// \output ulDebounceTimer[0]                       = 100
/// \output LPTMR0_GetTimeElapsed_HitCount           = 1u 
/// \output NvM_WriteBlock_HitCount                  = 0u 
///
//-----------------------------------------------------------------------------
void Mt_IoHwAbUser_SetNvm_ElecError_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetNvm_ElecError_Param1 = 0u;
  IoHwAbUser_unSensCalculatedDuty[0u] = IOHWABSUSER_95_PERCENT_PWM + 1u;
  eSensShVbatNew[0] = eIoHwAb_Hls_noError;
  eSensShGndNew[0] = eIoHwAb_Hls_noError;
  boStartTimer[0] = TRUE;
  ulDebounceTimer[0] = 100u;
  LPTMR0_GetTimeElapsed_RetVal = 101u;
  LPTMR0_GetTimeElapsed_HitCount = 0u;
  NvmBlockDeltaPwmPara.ucSensVbatError[0u] = 0u;
  NvmBlockDeltaPwmPara.ucSensGndError[0u] = 0u;
  NvM_WriteBlock_HitCount = 0u;
  NvM_WriteBlock_Param1 = 0u;
  NvM_WriteBlock_Param2 = NULL_PTR;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetNvm_ElecError(IoHwAbUser_SetNvm_ElecError_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(eSensShVbatNew[0], eIoHwAb_Hls_noError, == );
  AL_UNITTEST_CHECK(eSensShGndNew[0], eIoHwAb_Hls_noError, == );
  AL_UNITTEST_CHECK(NvmBlockDeltaPwmPara.ucSensVbatError[0u], 0u, == );
  AL_UNITTEST_CHECK(NvmBlockDeltaPwmPara.ucSensGndError[0u], 0u, == );
  AL_UNITTEST_CHECK(boStartTimer[0], TRUE, == );
  AL_UNITTEST_CHECK(ulDebounceTimer[0], 100u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount, 1u, == );
  AL_UNITTEST_CHECK(NvM_WriteBlock_HitCount, 0u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAbUser_SetNvm_ElecError_TestCase_4
///
/// \Test Case Description
///        - Test subject: HLS short to Vbat error detection test. Nvm update required
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the target levelling  for Vbat short error
///         Step2: Check the Nvm hit count (Nvm write required) and error detected (Short to Vbat)
///
/// - Preconditions:
///
/// \input IoHwAbUser_SetNvm_ElecError_Param1       = 0u;
/// \input IoHwAbUser_unSensCalculatedDuty[0u]      = IOHWABSUSER_95_PERCENT_PWM + 1u;
/// \input eSensShVbatNew[0]                        = eIoHwAb_Hls_noError;
/// \input eSensShGndNew[0]                         = eIoHwAb_Hls_noError;
/// \input boStartTimer[0]                          = TRUE;
/// \input ulDebounceTimer[0]                       = 100u;
/// \input LPTMR0_GetTimeElapsed_RetVal             = 10u;
/// \input LPTMR0_GetTimeElapsed_HitCount           = 0u;
/// \input NvmBlockDeltaPwmPara.ucSensVbatError[0u] = 0u;
/// \input NvmBlockDeltaPwmPara.ucSensGndError[0u]  = 0u;
/// \input NvM_WriteBlock_HitCount                  = 0u;
/// \input NvM_WriteBlock_Param1                    = 0u;
/// \input NvM_WriteBlock_Param2                    = NULL_PTR;
///
/// - Expectations:
///
/// \output eSensShVbatNew[0]                        = eIoHwAb_Hls_Error
/// \output eSensShGndNew[0]                         = eIoHwAb_Hls_noError
/// \output NvmBlockDeltaPwmPara.ucSensVbatError[0u] = 1u
/// \output NvmBlockDeltaPwmPara.ucSensGndError[0u]  = 0u
/// \output boStartTimer[0]                          = TRUE
/// \output ulDebounceTimer[0]                       = 100
/// \output LPTMR0_GetTimeElapsed_HitCount           = 1u 
/// \output NvM_WriteBlock_HitCount                  = 1u 
/// \output NvM_WriteBlock_Param1                    = NvmBlockDeltaPwmParaId 
/// \output NvM_WriteBlock_Param2                    = &NvmBlockDeltaPwmPara 
///
//-----------------------------------------------------------------------------
void Mt_IoHwAbUser_SetNvm_ElecError_TestCase_4(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetNvm_ElecError_Param1 = 0u;
  IoHwAbUser_unSensCalculatedDuty[0u] = IOHWABSUSER_95_PERCENT_PWM + 1u;
  eSensShVbatNew[0] = eIoHwAb_Hls_noError;
  eSensShGndNew[0] = eIoHwAb_Hls_noError;
  boStartTimer[0] = TRUE;
  ulDebounceTimer[0] = 100u;
  LPTMR0_GetTimeElapsed_RetVal = 10u;
  LPTMR0_GetTimeElapsed_HitCount = 0u;
  NvmBlockDeltaPwmPara.ucSensVbatError[0u] = 0u;
  NvmBlockDeltaPwmPara.ucSensGndError[0u] = 0u;
  NvM_WriteBlock_HitCount = 0u;
  NvM_WriteBlock_Param1 = 0u;
  NvM_WriteBlock_Param2 = NULL_PTR;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetNvm_ElecError(IoHwAbUser_SetNvm_ElecError_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(eSensShVbatNew[0], eIoHwAb_Hls_Error, == );
  AL_UNITTEST_CHECK(eSensShGndNew[0], eIoHwAb_Hls_noError, == );
  AL_UNITTEST_CHECK(NvmBlockDeltaPwmPara.ucSensVbatError[0u], 1u, == );
  AL_UNITTEST_CHECK(NvmBlockDeltaPwmPara.ucSensGndError[0u], 0u, == );
  AL_UNITTEST_CHECK(boStartTimer[0], TRUE, == );
  AL_UNITTEST_CHECK(ulDebounceTimer[0], 100u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount, 1u, == );
  AL_UNITTEST_CHECK(NvM_WriteBlock_HitCount, 1u, == );
  AL_UNITTEST_CHECK(NvM_WriteBlock_Param1, NvmBlockDeltaPwmParaId, == );
  AL_UNITTEST_CHECK(NvM_WriteBlock_Param2, &NvmBlockDeltaPwmPara, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAbUser_SetNvm_ElecError_TestCase_5
///
/// \Test Case Description
///        - Test subject: HLS short to Gnd error detection test. No Nvm update required
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the target levelling  for Vbat short error
///         Step2: Check the Nvm hit count (No Nvm write required) and timer gets triggered
///
/// - Preconditions:
///
/// \input IoHwAbUser_SetNvm_ElecError_Param1        = 0u;
/// \input IoHwAbUser_unSensCalculatedDuty[0u]       = IOHWABSUSER_5_PERCENT_PWM - 1u;
/// \input eSensShVbatNew[0]                         = eIoHwAb_Hls_noError;
/// \input eSensShGndNew[0]                          = eIoHwAb_Hls_noError;
/// \input boStartTimer[0]                           = FALSE;
/// \input ulDebounceTimer[0]                        = 0u;
/// \input LPTMR0_GetTimeElapsed_RetVal              = 10;
/// \input LPTMR0_GetTimeElapsed_HitCount            = 0u;
/// \input NvmBlockDeltaPwmPara.ucSensVbatError[0u]  = 0u;
/// \input NvmBlockDeltaPwmPara.ucSensGndError[0u]   = 0u;
/// \input NvM_WriteBlock_HitCount                   = 0u;
/// \input NvM_WriteBlock_Param1                     = 0u;
/// \input NvM_WriteBlock_Param2                     = NULL_PTR;
///
/// - Expectations:
///
/// \output eSensShVbatNew[0]                        = eIoHwAb_Hls_noError
/// \output eSensShGndNew[0]                         = eIoHwAb_Hls_noError
/// \output NvmBlockDeltaPwmPara.ucSensVbatError[0u] = 0u
/// \output NvmBlockDeltaPwmPara.ucSensGndError[0u]  = 0u
/// \output boStartTimer[0]                          = TRUE
/// \output ulDebounceTimer[0]                       = 10
/// \output LPTMR0_GetTimeElapsed_HitCount           = 1u 
/// \output NvM_WriteBlock_HitCount                  = 0u 
///
//-----------------------------------------------------------------------------
void Mt_IoHwAbUser_SetNvm_ElecError_TestCase_5(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetNvm_ElecError_Param1 = 0u;
  IoHwAbUser_unSensCalculatedDuty[0u] = IOHWABSUSER_5_PERCENT_PWM - 1u;
  eSensShVbatNew[0] = eIoHwAb_Hls_noError;
  eSensShGndNew[0] = eIoHwAb_Hls_noError;
  boStartTimer[0] = FALSE;
  ulDebounceTimer[0] = 0u;
  LPTMR0_GetTimeElapsed_RetVal = 10;
  LPTMR0_GetTimeElapsed_HitCount = 0u;
  NvmBlockDeltaPwmPara.ucSensVbatError[0u] = 0u;
  NvmBlockDeltaPwmPara.ucSensGndError[0u] = 0u;
  NvM_WriteBlock_HitCount = 0u;
  NvM_WriteBlock_Param1 = 0u;
  NvM_WriteBlock_Param2 = NULL_PTR;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetNvm_ElecError(IoHwAbUser_SetNvm_ElecError_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(eSensShVbatNew[0], eIoHwAb_Hls_noError, == );
  AL_UNITTEST_CHECK(eSensShGndNew[0], eIoHwAb_Hls_noError, == );
  AL_UNITTEST_CHECK(NvmBlockDeltaPwmPara.ucSensVbatError[0u], 0u, == );
  AL_UNITTEST_CHECK(NvmBlockDeltaPwmPara.ucSensGndError[0u], 0u, == );
  AL_UNITTEST_CHECK(boStartTimer[0], TRUE, == );
  AL_UNITTEST_CHECK(ulDebounceTimer[0], 10, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount, 1u, == );
  AL_UNITTEST_CHECK(NvM_WriteBlock_HitCount, 0u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAbUser_SetNvm_ElecError_TestCase_6
///
/// \Test Case Description
///        - Test subject: HLS short to Gnd error detection test. No Nvm update required
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the target levelling  for Vbat short error
///         Step2: Check the Nvm hit count (No Nvm write required) and timer is not done yet
///
/// - Preconditions:
///
/// \input IoHwAbUser_SetNvm_ElecError_Param1        = 0u;
/// \input IoHwAbUser_unSensCalculatedDuty[0u]       = IOHWABSUSER_5_PERCENT_PWM - 1u;
/// \input eSensShVbatNew[0]                         = eIoHwAb_Hls_noError;
/// \input eSensShGndNew[0]                          = eIoHwAb_Hls_noError;
/// \input boStartTimer[0]                           = TRUE;
/// \input ulDebounceTimer[0]                        = 100u;
/// \input LPTMR0_GetTimeElapsed_RetVal              = 101u;
/// \input LPTMR0_GetTimeElapsed_HitCount            = 0u;
/// \input NvmBlockDeltaPwmPara.ucSensVbatError[0u]  = 0u;
/// \input NvmBlockDeltaPwmPara.ucSensGndError[0u]   = 0u;
/// \input NvM_WriteBlock_HitCount                   = 0u;
/// \input NvM_WriteBlock_Param1                     = 0u;
/// \input NvM_WriteBlock_Param2                     = NULL_PTR;
///
/// - Expectations:
///
/// \output eSensShVbatNew[0]                        = eIoHwAb_Hls_noError
/// \output eSensShGndNew[0]                         = eIoHwAb_Hls_noError
/// \output NvmBlockDeltaPwmPara.ucSensVbatError[0u] = 0u
/// \output NvmBlockDeltaPwmPara.ucSensGndError[0u]  = 0u
/// \output boStartTimer[0]                          = TRUE
/// \output ulDebounceTimer[0]                       = 100
/// \output LPTMR0_GetTimeElapsed_HitCount           = 1u 
/// \output NvM_WriteBlock_HitCount                  = 0u 
/// 
//-----------------------------------------------------------------------------
void Mt_IoHwAbUser_SetNvm_ElecError_TestCase_6(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetNvm_ElecError_Param1 = 0u;
  IoHwAbUser_unSensCalculatedDuty[0u] = IOHWABSUSER_5_PERCENT_PWM - 1u;
  eSensShVbatNew[0] = eIoHwAb_Hls_noError;
  eSensShGndNew[0] = eIoHwAb_Hls_noError;
  boStartTimer[0] = TRUE;
  ulDebounceTimer[0] = 100u;
  LPTMR0_GetTimeElapsed_RetVal = 101u;
  LPTMR0_GetTimeElapsed_HitCount = 0u;
  NvmBlockDeltaPwmPara.ucSensVbatError[0u] = 0u;
  NvmBlockDeltaPwmPara.ucSensGndError[0u] = 0u;
  NvM_WriteBlock_HitCount = 0u;
  NvM_WriteBlock_Param1 = 0u;
  NvM_WriteBlock_Param2 = NULL_PTR;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetNvm_ElecError(IoHwAbUser_SetNvm_ElecError_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(eSensShVbatNew[0], eIoHwAb_Hls_noError, == );
  AL_UNITTEST_CHECK(eSensShGndNew[0], eIoHwAb_Hls_noError, == );
  AL_UNITTEST_CHECK(NvmBlockDeltaPwmPara.ucSensVbatError[0u], 0u, == );
  AL_UNITTEST_CHECK(NvmBlockDeltaPwmPara.ucSensGndError[0u], 0u, == );
  AL_UNITTEST_CHECK(boStartTimer[0], TRUE, == );
  AL_UNITTEST_CHECK(ulDebounceTimer[0], 100u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount, 1u, == );
  AL_UNITTEST_CHECK(NvM_WriteBlock_HitCount, 0u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAbUser_SetNvm_ElecError_TestCase_7
///
/// \Test Case Description
///        - Test subject: HLS short to Gnd error detection test. Nvm update required
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the target levelling  for Vbat short error
///         Step2: Check the Nvm hit count (Nvm write required) and error detected (Short to Gnd)
///
/// - Preconditions:
///
/// \input IoHwAbUser_SetNvm_ElecError_Param1       = 0u;
/// \input IoHwAbUser_unSensCalculatedDuty[0u]      = IOHWABSUSER_5_PERCENT_PWM - 1u;
/// \input eSensShVbatNew[0]                        = eIoHwAb_Hls_noError;
/// \input eSensShGndNew[0]                         = eIoHwAb_Hls_noError;
/// \input boStartTimer[0]                          = TRUE;
/// \input ulDebounceTimer[0]                       = 100u;
/// \input LPTMR0_GetTimeElapsed_RetVal             = 10u;
/// \input LPTMR0_GetTimeElapsed_HitCount           = 0u;
/// \input NvmBlockDeltaPwmPara.ucSensVbatError[0u] = 0u;
/// \input NvmBlockDeltaPwmPara.ucSensGndError[0u]  = 0u;
/// \input NvM_WriteBlock_HitCount                  = 0u;
/// \input NvM_WriteBlock_Param1                    = 0u;
/// \input NvM_WriteBlock_Param2                    = NULL_PTR;
///
/// - Expectations:
///
/// \output eSensShVbatNew[0]                        = eIoHwAb_Hls_noError
/// \output eSensShGndNew[0]                         = eIoHwAb_Hls_Error
/// \output NvmBlockDeltaPwmPara.ucSensVbatError[0u] = 0u
/// \output NvmBlockDeltaPwmPara.ucSensGndError[0u]  = 1u
/// \output boStartTimer[0]                          = TRUE
/// \output ulDebounceTimer[0]                       = 100
/// \output LPTMR0_GetTimeElapsed_HitCount           = 1u 
/// \output NvM_WriteBlock_HitCount                  = 1u 
/// \output NvM_WriteBlock_Param1                    = NvmBlockDeltaPwmParaId
/// \output NvM_WriteBlock_Param2                    = &NvmBlockDeltaPwmPara 
///
//-----------------------------------------------------------------------------
void Mt_IoHwAbUser_SetNvm_ElecError_TestCase_7(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetNvm_ElecError_Param1 = 0u;
  IoHwAbUser_unSensCalculatedDuty[0u] = IOHWABSUSER_5_PERCENT_PWM - 1u;
  eSensShVbatNew[0] = eIoHwAb_Hls_noError;
  eSensShGndNew[0] = eIoHwAb_Hls_noError;
  boStartTimer[0] = TRUE;
  ulDebounceTimer[0] = 100u;
  LPTMR0_GetTimeElapsed_RetVal = 10u;
  LPTMR0_GetTimeElapsed_HitCount = 0u;
  NvmBlockDeltaPwmPara.ucSensVbatError[0u] = 0u;
  NvmBlockDeltaPwmPara.ucSensGndError[0u] = 0u;
  NvM_WriteBlock_HitCount = 0u;
  NvM_WriteBlock_Param1 = 0u;
  NvM_WriteBlock_Param2 = NULL_PTR;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_SetNvm_ElecError(IoHwAbUser_SetNvm_ElecError_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(eSensShVbatNew[0], eIoHwAb_Hls_noError, == );
  AL_UNITTEST_CHECK(eSensShGndNew[0], eIoHwAb_Hls_Error, == );
  AL_UNITTEST_CHECK(NvmBlockDeltaPwmPara.ucSensVbatError[0u], 0u, == );
  AL_UNITTEST_CHECK(NvmBlockDeltaPwmPara.ucSensGndError[0u], 1u, == );
  AL_UNITTEST_CHECK(boStartTimer[0], TRUE, == );
  AL_UNITTEST_CHECK(ulDebounceTimer[0], 100u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount, 1u, == );
  AL_UNITTEST_CHECK(NvM_WriteBlock_HitCount, 1u, == );
  AL_UNITTEST_CHECK(NvM_WriteBlock_Param1, NvmBlockDeltaPwmParaId, == );
  AL_UNITTEST_CHECK(NvM_WriteBlock_Param2, &NvmBlockDeltaPwmPara, == );
}


//-----------------------------------------------------------------------------
/// \Test Case :  Mt_IoHwAbUser_SetNvm_ElecError
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Tests if the function sets the Sensor electrical errors
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_IoHwAbUser_SetNvm_ElecError(void)
{
  Mt_IoHwAbUser_SetNvm_ElecError_TestCase_1();
  Mt_IoHwAbUser_SetNvm_ElecError_TestCase_2();
  Mt_IoHwAbUser_SetNvm_ElecError_TestCase_3();
  Mt_IoHwAbUser_SetNvm_ElecError_TestCase_4();
  Mt_IoHwAbUser_SetNvm_ElecError_TestCase_5();
  Mt_IoHwAbUser_SetNvm_ElecError_TestCase_6();
  Mt_IoHwAbUser_SetNvm_ElecError_TestCase_7();
}


// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAbUser_ParaFct0_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test that function gets valid coding data
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
///
/// - Preconditions:
///
/// \input Rte_Read_CodM_IoHwAbUser_Para_Param1.eCodingState    = eParaFct0_CodingDataValid
/// \input Rte_Read_CodM_IoHwAbUser_Para_HitCount               = 0u
///
/// - Expectations:
///
/// \output IoHwAbUser_boIsCodingValid                          = TRUE
/// \output Rte_Read_CodM_IoHwAbUser_Para_HitCount              = 1u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAbUser_ParaFct0_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  Rte_Read_CodM_IoHwAbUser_Para_Param1.eCodingState = eParaFct0_CodingDataValid;
  Rte_Read_CodM_IoHwAbUser_Para_HitCount = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_ParaFct0();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_boIsCodingValid, TRUE, == );
  AL_UNITTEST_CHECK(Rte_Read_CodM_IoHwAbUser_Para_HitCount, 1u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_IoHwAbUser_ParaFct0_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test that function gets invalid coding data
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
///
/// - Preconditions:
///
/// \input Rte_Read_CodM_IoHwAbUser_Para_Param1.eCodingState    = eParaFct0_CodingDataInvalid
/// \input Rte_Read_CodM_IoHwAbUser_Para_HitCount               = 0u
///
/// - Expectations:
///
/// \output IoHwAbUser_boIsCodingValid                          = FALSE
/// \output Rte_Read_CodM_IoHwAbUser_Para_HitCount              = 1u
///
//-----------------------------------------------------------------------------
void Mt_IoHwAbUser_ParaFct0_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  Rte_Read_CodM_IoHwAbUser_Para_Param1.eCodingState = eParaFct0_CodingDataInvalid;
  Rte_Read_CodM_IoHwAbUser_Para_HitCount = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  IoHwAbUser_ParaFct0();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(IoHwAbUser_boIsCodingValid, FALSE, == );
  AL_UNITTEST_CHECK(Rte_Read_CodM_IoHwAbUser_Para_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_IoHwAbUser_ParaFct0
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Tests the coding getter function
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_IoHwAbUser_ParaFct0(void)
{
  Mt_IoHwAbUser_ParaFct0_TestCase_1();
  Mt_IoHwAbUser_ParaFct0_TestCase_2();
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
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_Init", Mt_IoHwAb_IoHwAbUser_Init);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_DeInit", Mt_IoHwAb_IoHwAbUser_DeInit);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_Cycle", Mt_IoHwAb_IoHwAbUser_Cycle);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_InitGetMountingSide", Mt_IoHwAb_IoHwAbUser_InitGetMountingSide);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_HSSOperation", Mt_IoHwAb_IoHwAbUser_HSSOperation);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_GetMountingSideRaw", Mt_IoHwAb_IoHwAbUser_GetMountingSideRaw);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_SetBoostMode", Mt_IoHwAb_IoHwAbUser_SetBoostMode);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_SetHss_Sen", Mt_IoHwAb_IoHwAbUser_SetHss_Sen);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_SetHss_Sel2", Mt_IoHwAb_IoHwAbUser_SetHss_Sel2);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_SetHss_Sel1", Mt_IoHwAb_IoHwAbUser_SetHss_Sel1);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_SetHss_Error", Mt_IoHwAb_IoHwAbUser_SetHss_Error);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_SetHss_En3", Mt_IoHwAb_IoHwAbUser_SetHss_En3);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_SetHss_En2", Mt_IoHwAb_IoHwAbUser_SetHss_En2);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_SetHss_En1", Mt_IoHwAb_IoHwAbUser_SetHss_En1);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_SetVccxEn", Mt_IoHwAb_IoHwAbUser_SetVccxEn);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_SetLwrDrvOff", Mt_IoHwAb_IoHwAbUser_SetLwrDrvOff);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_SetLwrSleep", Mt_IoHwAb_IoHwAbUser_SetLwrSleep);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_SetDirLwr", Mt_IoHwAb_IoHwAbUser_SetDirLwr);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_SenseEnableHss", Mt_IoHwAb_IoHwAbUser_SenseEnableHss);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_ResetHss", Mt_IoHwAb_IoHwAbUser_ResetHss);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUserTimer0Notification", Mt_IoHwAb_IoHwAbUserTimer0Notification);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_CalcVBatMeanValue", Mt_IoHwAb_IoHwAbUser_CalcVBatMeanValue);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_HSSOperationForEcuHighVar", Mt_IoHwAb_IoHwAbUser_HSSOperationForEcuHighVar);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_InitializeBuffers", Mt_IoHwAb_IoHwAbUser_InitializeBuffers);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_FilterInitialization", Mt_IoHwAb_IoHwAbUser_FilterInitialization);
  ALUnitTest_AddFunction("Mt_IoHwAb_rpIoHwAbUser_Cycle", Mt_IoHwAb_rpIoHwAbUser_Cycle);
  ALUnitTest_AddFunction("Mt_IoHwAb_riIoHwAbUserDeInit", Mt_IoHwAb_riIoHwAbUserDeInit);
  ALUnitTest_AddFunction("Mt_IoHwAb_riIoHwAbUserInit", Mt_IoHwAb_riIoHwAbUserInit);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_FilterInitialization", Mt_IoHwAb_IoHwAbUser_FilterInitialization);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_Set_Vccx_State", Mt_IoHwAb_IoHwAbUser_Set_Vccx_State);
  ALUnitTest_AddFunction("Mt_IoHwAbIoHwAbUser_VccxStateCyclicCheck", Mt_IoHwAbIoHwAbUser_VccxStateCyclicCheck);
  ALUnitTest_AddFunction("Mt_IoHwAbUser_Read_PCB", Mt_IoHwAbUser_Get_PCB);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_GetHss0Sense", Mt_IoHwAb_IoHwAbUser_GetHss0Sense);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_GetHss1Sense", Mt_IoHwAb_IoHwAbUser_GetHss1Sense);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_GetHss2Sense", Mt_IoHwAb_IoHwAbUser_GetHss2Sense);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_Read_VCXX1", Mt_IoHwAb_IoHwAbUser_Read_VCCX1);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT1", Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT1);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT2", Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT2);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT3", Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT3);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT4", Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT4);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT5", Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT5);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT6", Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT6);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT7", Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT7);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT8", Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT8);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT9", Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT9);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT10", Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT10);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT11", Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT11);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT12", Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT12);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT13", Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT13);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT14", Mt_IoHwAb_IoHwAbUser_GetVoltage_EXT14);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_GetVoltage_NTC", Mt_IoHwAb_IoHwAbUser_GetVoltage_NTC);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_GetVoltage_NTCs", Mt_IoHwAb_IoHwAbUser_GetVoltage_NTCs);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_GetSens_Raw", Mt_IoHwAb_IoHwAbUser_GetSens_Raw);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_GetSens_Balanced", Mt_IoHwAb_IoHwAbUser_GetSens_Balanced);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_CalcInputPwmSens", Mt_IoHwAb_IoHwAbUser_CalcInputPwmSens);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_CheckSens0_OpenLoad", Mt_IoHwAb_IoHwAbUser_CheckSens0_OpenLoad);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_CheckSens1_OpenLoad", Mt_IoHwAb_IoHwAbUser_CheckSens1_OpenLoad);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_ReportVccx2Error", Mt_IoHwAb_IoHwAbUser_ReportVccx2Error);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAb_User_SetDio_EN_DC", Mt_IoHwAb_IoHwAb_User_SetDio_EN_DC);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_GetAdc_VoltDC_OUT1", Mt_IoHwAb_IoHwAbUser_GetAdc_VoltDC_OUT1);
  ALUnitTest_AddFunction("Mt_IoHwAb_IoHwAbUser_SetTgtHss3", Mt_IoHwAb_IoHwAbUser_SetTgtHss3);
  ALUnitTest_AddFunction("Mt_reIoHwAbUser_GetLssDiagnostic", Mt_reIoHwAbUser_GetLssDiagnostic);
  ALUnitTest_AddFunction("Mt_IoHwAbUser_GetOutFctDiag", Mt_IoHwAbUser_GetOutFctDiag);
  ALUnitTest_AddFunction("Mt_IoHwAbUser_ProcessOutFctDiag", Mt_IoHwAbUser_ProcessOutFctDiag);
  ALUnitTest_AddFunction("Mt_IoHwAbUser_SetNvm_ElecError", Mt_IoHwAbUser_SetNvm_ElecError);
  ALUnitTest_AddFunction("Mt_IoHwAbUser_ParaFct0", Mt_IoHwAbUser_ParaFct0);
}
// EOF

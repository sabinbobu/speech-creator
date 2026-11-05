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
/// \brief Module test of Port
///
//-----------------------------------------------------------------------------
//=============================================================================
// includes
//=============================================================================
// Standard unit test header
#include <ALUnitTest_UserInterface.h>

// Headers of the unit test Module
#include "Test.h"

//=============================================================================
// Test Cases
//=============================================================================

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Port_Port_Init
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject: 
///        Check if the function Port_Init sets the correct value in registers.
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. Every DT-entry represents a different Test Case interaction.
///      - DT-Info:
///         - Inputs:
///           - In Port_Cfg.c
///         - Expected results
///           - registers value matchs the corresponding expected output value
///
///       For further information about specific input/outputs variables refer to the  input assignament (step 2) and output value check (step 4) of this Unit Test Case
///
///    - Preconditions:
///           -Module internal variables shall contain its init value set statically 
///
//-----------------------------------------------------------------------------
void Mt_Port_Port_Init(void)
{
  uint8 ucIdx;

  typedef struct tsTestCaseDataOutput
  {
    PORT_Type*                       portAddr;
    uint32                           pinPortIdx;
    uint8                            pullConfig;
    boolean                          passiveFilter;
    uint8                            driveSelect;
    uint8                            mux;
    uint8                            direction;
    uint8                            initValue;
    boolean                          digitalFilter;
    GPIO_Type*                       gpioAddr;
  }tsTestCaseDataOutput;

  typedef struct tsTestCaseData
  {
    tsTestCaseDataOutput sOutputData;
  }tsTestCaseData;

  static tsTestCaseData asTestCaseData[] =
  {
    //      Outputs
    //            |   |  PullCfg     | passiveFilter | driveSelect          |     muxing              | dir (IN = 0, OUT = 1) |      digitalFilter
    { PORTC_BASE,  3U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_PIN_DISABLED,       (uint8)0x0u,       0U, FALSE, PTC_BASE }, //29. ADC.EXT_1
    { PORTC_BASE,  1U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_PIN_DISABLED,       (uint8)0x0u,       0U, FALSE, PTC_BASE }, //39. ADC.EXT_2
    { PORTC_BASE,  0U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_PIN_DISABLED,       (uint8)0x0u,       0U, FALSE, PTC_BASE }, //40. ADC.EXT_3
    { PORTC_BASE, 17U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_PIN_DISABLED,       (uint8)0x0u,       0U, FALSE, PTC_BASE }, //43. ADC.EXT_4
    { PORTC_BASE, 16U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_PIN_DISABLED,       (uint8)0x0u,       0U, FALSE, PTC_BASE }, //44. ADC.EXT_5
    { PORTC_BASE, 15U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_PIN_DISABLED,       (uint8)0x0u,       0U, FALSE, PTC_BASE }, //45. ADC.EXT_6
    { PORTB_BASE,  3U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_PIN_DISABLED,       (uint8)0x0u,       0U, FALSE, PTB_BASE }, //47. ADC.EXT_7
    { PORTA_BASE,  6U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_PIN_DISABLED,       (uint8)0x0u,       0U, FALSE, PTA_BASE }, //58. ADC.EXT_8
    { PORTA_BASE,  2U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_PIN_DISABLED,       (uint8)0x0u,       0U, FALSE, PTA_BASE }, //73. ADC.EXT_9
    { PORTB_BASE, 13U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_PIN_DISABLED,       (uint8)0x0u,       0U, FALSE, PTB_BASE }, //67. ADC.EXT_10
    { PORTC_BASE,  2U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_PIN_DISABLED,       (uint8)0x0u,       0U, FALSE, PTC_BASE }, //30. ADC.EXT_11
    { PORTB_BASE, 15U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_PIN_DISABLED,       (uint8)0x0u,       0U, FALSE, PTB_BASE }, //65. ADC.EXT_12
    { PORTB_BASE, 14U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_PIN_DISABLED,       (uint8)0x0u,       0U, FALSE, PTB_BASE }, //66. ADC.EXT_13
    { PORTA_BASE, 16U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_PIN_DISABLED,       (uint8)0x0u,       0U, FALSE, PTA_BASE }, //82. ADC.EXT_14
    { PORTD_BASE,  4U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_PIN_DISABLED,       (uint8)0x0u,       0U, FALSE, PTD_BASE }, //69. ADC.VBAT
    { PORTA_BASE,  7U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_PIN_DISABLED,       (uint8)0x0u,       0U, FALSE, PTA_BASE }, //57. ADC.LR_DETECTION
    { PORTD_BASE,  2U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_PIN_DISABLED,       (uint8)0x0u,       0U, FALSE, PTD_BASE }, //71. ADC.PCB_TEMP
    { PORTA_BASE,  3U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_PIN_DISABLED,       (uint8)0x0u,       0U, FALSE, PTA_BASE }, //72. ADC.VCCX1
    { PORTE_BASE,  2U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_PIN_DISABLED,       (uint8)0x0u,       0U, FALSE, PTE_BASE }, //85. ADC.VCCX2 
    { PORTB_BASE, 16U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_PIN_DISABLED,       (uint8)0x0u,       0U, FALSE, PTB_BASE }, //64. ADC.HSS_SENSE_3
    { PORTA_BASE,  1U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_PIN_DISABLED,       (uint8)0x0u,       0U, FALSE, PTA_BASE }, //78. ADC.HSS_SENSE_1_2
    { PORTA_BASE,  0U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_PIN_DISABLED,       (uint8)0x0u,       0U, FALSE, PTA_BASE }, //79. ADC.OUT_FCT
    { PORTE_BASE,  5U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_MUX_ALT5,           (uint8)0x1u,       0U, FALSE, PTE_BASE }, // 8. CAN.CAN0_TX
    { PORTE_BASE,  4U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_MUX_ALT5,           (uint8)0x0u,       0U, FALSE, PTE_BASE }, // 9. CAN.CAN0_RX
    { PORTC_BASE,  7U, (uint8)0x02u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_MUX_ALT2,           (uint8)0x1u,       0U, FALSE, PTC_BASE }, //80. LPUART1_TX
    { PORTC_BASE,  6U, (uint8)0x02u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_MUX_ALT2,           (uint8)0x0u,       0U, FALSE, PTC_BASE }, //81. LPUART1_RX
    { PORTD_BASE, 16U, (uint8)0x02u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_MUX_ALT4,           (uint8)0x0u,       0U, FALSE, PTD_BASE }, //21. LPSPI0_MISO
    { PORTD_BASE, 15U, (uint8)0x02u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_MUX_ALT4,           (uint8)0x1u,       0U, FALSE, PTD_BASE }, //22. LPSPI0_CLK 
    { PORTB_BASE,  1U, (uint8)0x02u,  FALSE, (uint8)PORT_HIGH_DRIVE_STRENGTH, (uint8)PORT_MUX_ALT3,           (uint8)0x1u,       0U, FALSE, PTB_BASE }, //53. LPSPI0_MOSI
    { PORTB_BASE,  0U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_MUX_ALT3,           (uint8)0x1u,       0U, FALSE, PTB_BASE }, //54. LPSPI0_PCS0_TLE9471
    { PORTB_BASE,  5U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_MUX_ALT3,           (uint8)0x1u,       0U, FALSE, PTB_BASE }, //27. LPSPI0_PCS1_NCV78702
    { PORTA_BASE, 15U, (uint8)0x02u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_MUX_ALT3,           (uint8)0x1u,       0U, FALSE, PTA_BASE }, //83. LPSPI0_PCS3_DRV8899
    { PORTB_BASE, 17U, (uint8)0x02u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_MUX_ALT3,           (uint8)0x1u,       0U, FALSE, PTB_BASE }, //63. LPSPI1_PCS3_EWTZPY
    { PORTD_BASE,  1U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_MUX_ALT3,           (uint8)0x0u,       0U, FALSE, PTD_BASE }, // 3. LPSPI1_MISO
    { PORTD_BASE,  0U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_MUX_ALT3,           (uint8)0x1u,       0U, FALSE, PTD_BASE }, // 4. LPSPI1_CLK
    { PORTE_BASE,  1U, (uint8)0x02u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_MUX_ALT5,           (uint8)0x1u,       0U, FALSE, PTE_BASE }, //93. LPSPI1_PCS0_TPS92520
    { PORTE_BASE,  0U, (uint8)0x03u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_MUX_ALT5,           (uint8)0x1u,       0U, FALSE, PTE_BASE }, //94. LPSPI1_MOSI
    { PORTE_BASE,  9U, (uint8)0x02u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_MUX_AS_GPIO,        (uint8)0x1u,       0U, FALSE, PTE_BASE }, //23. GPIO.BOOST_ENABLE
    { PORTD_BASE, 14U, (uint8)0x02u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_MUX_AS_GPIO,        (uint8)0x0u,       0U, FALSE, PTD_BASE }, //24. GPIO.HWID_0
    { PORTD_BASE, 13U, (uint8)0x02u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_MUX_AS_GPIO,        (uint8)0x0u,       0U, FALSE, PTD_BASE }, //25. GPIO.HWID_1
    { PORTE_BASE, 14U, (uint8)0x02u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_MUX_AS_GPIO,        (uint8)0x1u,       0U, FALSE, PTE_BASE }, //17. GPIO.ST_DRVOFF
    { PORTA_BASE, 17U, (uint8)0x02u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_MUX_AS_GPIO,        (uint8)0x1u,       0U, FALSE, PTA_BASE }, //62. GPIO.ST_DIR_LWR
    { PORTD_BASE, 10U, (uint8)0x02u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_MUX_AS_GPIO,        (uint8)0x0u,       0U, FALSE, PTD_BASE }, //36. GPIO.ST_ERROR
    { PORTD_BASE,  8U, (uint8)0x02u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_MUX_AS_GPIO,        (uint8)0x1u,       0U, FALSE, PTD_BASE }, //42. GPIO.ST_SLEEP
    { PORTE_BASE,  7U, (uint8)0x00u,  FALSE, (uint8)PORT_HIGH_DRIVE_STRENGTH, (uint8)PORT_MUX_AS_GPIO,        (uint8)0x1u,       0U, FALSE, PTE_BASE }, //59. GPIO.HSS_ERROR
    { PORTB_BASE, 11U, (uint8)0x00u,  FALSE, (uint8)PORT_HIGH_DRIVE_STRENGTH, (uint8)PORT_MUX_AS_GPIO,        (uint8)0x1u,       0U, FALSE, PTB_BASE }, //74. GPIO.HSS_SEL_1
    { PORTD_BASE,  7U, (uint8)0x00u,  FALSE, (uint8)PORT_HIGH_DRIVE_STRENGTH, (uint8)PORT_MUX_AS_GPIO,        (uint8)0x1u,       0U, FALSE, PTD_BASE }, //31. GPIO.HSS_SEL_2
    { PORTD_BASE,  6U, (uint8)0x00u,  FALSE, (uint8)PORT_HIGH_DRIVE_STRENGTH, (uint8)PORT_MUX_AS_GPIO,        (uint8)0x1u,       0U, FALSE, PTD_BASE }, //32. GPIO.HSS_EN_1
    { PORTC_BASE,  9U, (uint8)0x00u,  FALSE, (uint8)PORT_HIGH_DRIVE_STRENGTH, (uint8)PORT_MUX_AS_GPIO,        (uint8)0x1u,       0U, FALSE, PTC_BASE }, //55. GPIO.HSS_EN_2
    { PORTC_BASE,  8U, (uint8)0x00u,  FALSE, (uint8)PORT_HIGH_DRIVE_STRENGTH, (uint8)PORT_MUX_ALT4,           (uint8)0x1u,       0U, FALSE, PTC_BASE }, //56. GPIO.HSS_EN_3 (PWM) 
    { PORTA_BASE, 12U, (uint8)0x00u,  FALSE, (uint8)PORT_HIGH_DRIVE_STRENGTH, (uint8)PORT_MUX_AS_GPIO,        (uint8)0x1u,       0U, FALSE, PTA_BASE }, //90. GPIO.HSS_SEN
    { PORTC_BASE, 10U, (uint8)0x02u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_MUX_AS_GPIO,        (uint8)0x1u,       0U, FALSE, PTC_BASE }, //52. GPIO.VCCX_EN
    { PORTA_BASE, 14U, (uint8)0x02u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_MUX_AS_GPIO,        (uint8)0x0u,       0U, FALSE, PTA_BASE }, //88. GPIO_VCCX2_PG
    { PORTE_BASE,  8U, (uint8)0x00u,  FALSE, (uint8)PORT_HIGH_DRIVE_STRENGTH, (uint8)PORT_MUX_ALT2,           (uint8)0x0u,       0U, FALSE, PTE_BASE }, //26. GPIO.IN_FCT_2_UC (PWM)
    { PORTE_BASE,  3U, (uint8)0x00u,  FALSE, (uint8)PORT_HIGH_DRIVE_STRENGTH, (uint8)PORT_MUX_AS_GPIO,        (uint8)0x0u,       0U, FALSE, PTE_BASE }, //18. PWM.IN_FCT_1_UC
    { PORTB_BASE,  2U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_MUX_ALT2,           (uint8)0x1u,       0U, FALSE, PTB_BASE }, //48. PWM.LEDCNTRL_1
    { PORTC_BASE, 14U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_MUX_ALT2,           (uint8)0x1u,       0U, FALSE, PTC_BASE }, //46. PWM.LEDCNTRL_2
    { PORTA_BASE, 11U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_MUX_ALT2,           (uint8)0x1u,       0U, FALSE, PTA_BASE }, //91. PWM.LEDCNTRL_3
    { PORTA_BASE, 13U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_MUX_ALT2,           (uint8)0x1u,       0U, FALSE, PTA_BASE }, //89. PWM.LEDCNTRL_4
    { PORTD_BASE,  3U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_MUX_ALT2,           (uint8)0x1u,       0U, FALSE, PTD_BASE }, //70. PWM.LEDCNTRL_5
    { PORTD_BASE, 11U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_MUX_ALT2,           (uint8)0x1u,       0U, FALSE, PTD_BASE }, //35. PWM.LEDCNTRL_6
    { PORTD_BASE,  5U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_MUX_ALT2,           (uint8)0x1u,       0U, FALSE, PTD_BASE }, //33. PWM.LEDCNTRL_7
    { PORTB_BASE,  9U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_MUX_ALT2,           (uint8)0x1u,       0U, FALSE, PTB_BASE }, //76. PWM.LEDCNTRL_9
    { PORTE_BASE, 11U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_MUX_ALT4,           (uint8)0x1u,       0U, FALSE, PTE_BASE }, // 5. PWM.LEDCNTRL_8
    { PORTC_BASE, 13U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_MUX_ALT3,           (uint8)0x1u,       0U, FALSE, PTC_BASE }, //49. PWM.LEDCNTRL_10
    { PORTB_BASE, 10U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_MUX_ALT2,           (uint8)0x1u,       0U, FALSE, PTB_BASE }, //75. PWM.LEDCNTRL_11
    { PORTC_BASE, 12U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_MUX_ALT2,           (uint8)0x1u,       0U, FALSE, PTC_BASE }, //50. PWM.LEDCNTRL_12
    { PORTE_BASE, 10U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_MUX_ALT2,           (uint8)0x1u,       0U, FALSE, PTE_BASE }, // 6. PWM.BOOST_SYNC
    { PORTE_BASE, 13U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_MUX_ALT2,           (uint8)0x1u,       0U, FALSE, PTE_BASE }, // 7. PWM.ST_STEP_LWR
    { PORTB_BASE, 12U, (uint8)0x02u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_MUX_ALT2,           (uint8)0x0u,       0U, FALSE, PTB_BASE }, //68. PWM.SENS_1_UC
    { PORTB_BASE,  4U, (uint8)0x02u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_MUX_ALT2,           (uint8)0x0u,       0U, FALSE, PTB_BASE }, //28. PWM.SENS_2_UC
    { PORTA_BASE, 31U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_MUX_ADC_INTERLEAVE, (uint8)0x0,        0U, FALSE, PTA_BASE }, //special case
    { PORTB_BASE, 13U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_MUX_ADC_INTERLEAVE, (uint8)0x0,        0U, FALSE, PTB_BASE }, //special case
    { PORTC_BASE, 31U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_MUX_AS_GPIO,        (uint8)0x0,        0U, FALSE, PTC_BASE }, //special case
    { PORTD_BASE, 31U, (uint8)0x00u,  FALSE, (uint8)PORT_LOW_DRIVE_STRENGTH,  (uint8)PORT_MUX_AS_GPIO,        (uint8)0x0,        0U, FALSE, PTD_BASE }, //special case
  };

  //Step 1) Set pre - conditions if needed
  dummyPTA.PDOR = 0xFFFFFFFFU;
  dummyPTB.PDOR = 0xFFFFFFFFU;
  dummyPTC.PDOR = 0xFFFFFFFFU;
  dummyPTD.PDOR = 0xFFFFFFFFU;
  dummyPTE.PDOR = 0xFFFFFFFFU;

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  //Step 3) Call the FUT

  Port_Init(&Port_ConfigData);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 


  for (ucIdx = 0U; ucIdx < sizeof(asTestCaseData) / sizeof(tsTestCaseData); ucIdx++)
  {
    //check pull configuration
    AL_UNITTEST_CHECK(asTestCaseData[ucIdx].sOutputData.portAddr->PCR[asTestCaseData[ucIdx].sOutputData.pinPortIdx] & 0x3u, asTestCaseData[ucIdx].sOutputData.pullConfig, == );
    //check passive filter
    AL_UNITTEST_CHECK((asTestCaseData[ucIdx].sOutputData.portAddr->PCR[asTestCaseData[ucIdx].sOutputData.pinPortIdx] & PORT_PCR_PFE_MASK) >> PORT_PCR_PFE_SHIFT, asTestCaseData[ucIdx].sOutputData.passiveFilter, == );
    //check drive select
    AL_UNITTEST_CHECK((asTestCaseData[ucIdx].sOutputData.portAddr->PCR[asTestCaseData[ucIdx].sOutputData.pinPortIdx] & PORT_PCR_DSE_MASK) >> PORT_PCR_DSE_SHIFT, asTestCaseData[ucIdx].sOutputData.driveSelect, == );
    //check pin mux
    if (asTestCaseData[ucIdx].sOutputData.mux == (uint8)PORT_MUX_ADC_INTERLEAVE)
    {
      AL_UNITTEST_CHECK((asTestCaseData[ucIdx].sOutputData.portAddr->PCR[asTestCaseData[ucIdx].sOutputData.pinPortIdx] & PORT_PCR_MUX_MASK) >> PORT_PCR_MUX_SHIFT, (uint8)PORT_PIN_DISABLED, == );
    }
    else
    {
      AL_UNITTEST_CHECK((asTestCaseData[ucIdx].sOutputData.portAddr->PCR[asTestCaseData[ucIdx].sOutputData.pinPortIdx] & PORT_PCR_MUX_MASK) >> PORT_PCR_MUX_SHIFT, asTestCaseData[ucIdx].sOutputData.mux, == );
    }

    //check digital filter
    AL_UNITTEST_CHECK((asTestCaseData[ucIdx].sOutputData.portAddr->DFER & (1UL << asTestCaseData[ucIdx].sOutputData.pinPortIdx)) >> asTestCaseData[ucIdx].sOutputData.pinPortIdx, asTestCaseData[ucIdx].sOutputData.digitalFilter, == );
    if (asTestCaseData[ucIdx].sOutputData.mux == (uint8)PORT_MUX_AS_GPIO)
    {//check direction
      AL_UNITTEST_CHECK((asTestCaseData[ucIdx].sOutputData.gpioAddr->PDDR & (1UL << asTestCaseData[ucIdx].sOutputData.pinPortIdx)) >> asTestCaseData[ucIdx].sOutputData.pinPortIdx, asTestCaseData[ucIdx].sOutputData.direction, == );

      if (asTestCaseData[ucIdx].sOutputData.direction == (uint8)0x1u)
      {//check port Init value
        AL_UNITTEST_CHECK((asTestCaseData[ucIdx].sOutputData.gpioAddr->PDOR & (1UL << asTestCaseData[ucIdx].sOutputData.pinPortIdx)) >> asTestCaseData[ucIdx].sOutputData.pinPortIdx, asTestCaseData[ucIdx].sOutputData.initValue, == );
      }
    }
  }

}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Port_PINS_GPIO_WritePin
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject: 
///        Check if the function PINS_GPIO_WritePin sets the correct state of the spi driver depending on its previous value.
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. Every DT-entry represents a different Test Case interaction.
///      - DT-Info:
///         - Inputs:
///           - GPIO base address 
///           - pin number
///           - pin value
///         - Expected results
///           - adc interleave Value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
///       For further information about specific input/outputs variables refer to the  input assignament (step 2) and output value check (step 4) of this Unit Test Case
///
///    - Preconditions:
///           - 
///
//-----------------------------------------------------------------------------
void Mt_Port_PINS_GPIO_WritePin(void)
{
  typedef struct tsTestCaseDataInput
  {
    GPIO_Type*                       gpioAddr;
    uint32                           ulpinPortIdx;
    uint8                            ucPinValue;
  }tsTestCaseDataInput;

  typedef struct tsTestCaseDataOutput
  {
    uint32 ulValue;
  }tsTestCaseDataOutput;

  typedef struct tsTestCaseData
  {
    tsTestCaseDataInput  sInputData;
    tsTestCaseDataOutput sOutputData;
  }tsTestCaseData;

  static tsTestCaseData asTestCaseData[] =
  {
    // Input                   ||  Output
    // base     | pin | value  ||  expectedValue 
    { { PTA_BASE,  0U,  0u  }  , {0u <<  0u } },
    { { PTA_BASE, 31U,  0u  }  , {0u << 31u } },  
    { { PTA_BASE,  0U,  1u  }  , {1u <<  0u } },
    { { PTA_BASE, 31U,  1u  }  , {1u << 31u } },
    { { PTB_BASE,  0U,  0u  }  , {0u <<  0u } },
    { { PTB_BASE, 31U,  0u  }  , {0u << 31u } },
    { { PTB_BASE,  0U,  1u  }  , {1u <<  0u } },
    { { PTB_BASE, 31U,  1u  }  , {1u << 31u } },
    { { PTC_BASE,  0U,  0u  }  , {0u <<  0u } },
    { { PTC_BASE, 31U,  0u  }  , {0u << 31u } },
    { { PTC_BASE,  0U,  1u  }  , {1u <<  0u } },
    { { PTC_BASE, 31U,  1u  }  , {1u << 31u } },
    { { PTD_BASE,  0U,  0u  }  , {0u <<  0u } },
    { { PTD_BASE, 31U,  0u  }  , {0u << 31u } },
    { { PTD_BASE,  0U,  1u  }  , {1u <<  0u } },
    { { PTD_BASE, 31U,  1u  }  , {1u << 31u } },
    { { PTE_BASE,  0U,  0u  }  , {0u <<  0u } },
    { { PTE_BASE, 31U,  0u  }  , {0u << 31u } },
    { { PTE_BASE,  0U,  1u  }  , {1u <<  0u } },
    { { PTE_BASE, 31U,  1u  }  , {1u << 31u } },
  };


  for (uint8 ucIdx = 0; ucIdx < sizeof(asTestCaseData) / sizeof(tsTestCaseData); ucIdx++)
  {
    //Step 1) Set pre - conditions if needed
    asTestCaseData[ucIdx].sInputData.gpioAddr->PDOR = 0x0U;

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT

    //Step 3) Call the FUT
    PINS_GPIO_WritePin(asTestCaseData[ucIdx].sInputData.gpioAddr, asTestCaseData[ucIdx].sInputData.ulpinPortIdx, asTestCaseData[ucIdx].sInputData.ucPinValue);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    AL_UNITTEST_CHECK(asTestCaseData[ucIdx].sInputData.gpioAddr->PDOR, asTestCaseData[ucIdx].sOutputData.ulValue, == );
  }
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Port_PINS_GetAdcInterleaveVal
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject: 
///        Check if the function PINS_GetAdcInterleaveVal sets the correct state of the spi driver depending on its previous value.
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. Every DT-entry represents a different Test Case interaction.
///      - DT-Info:
///         - Inputs:
///           - GPIO base address
///           - pin number
///           - SIM reg value
///         - Expected results
///           - adc interleave Value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
///       For further information about specific input/outputs variables refer to the  input assignament (step 2) and output value check (step 4) of this Unit Test Case
///
///    - Preconditions:
///           - 
///
//-----------------------------------------------------------------------------
void Mt_Port_PINS_GetAdcInterleaveVal(void)
{
  typedef struct tsTestCaseDataInput
  {
    PORT_Type*                       portAddr;
    uint32                           ulpinPortIdx;
    uint8                            ulCurrentVal;
  }tsTestCaseDataInput;

  typedef struct tsTestCaseDataOutput
  {
    uint32 ulAdcReturnValue;
  }tsTestCaseDataOutput;

  typedef struct tsTestCaseData
  {
    tsTestCaseDataInput  sInputData;
    tsTestCaseDataOutput sOutputData;
  }tsTestCaseData;

  static tsTestCaseData asTestCaseData[] =
  {
    // Input                      ||  Output
    // base |        pin          ||  expected State 
    { { PORTB_BASE,  0U, 0xFFu  } , {0xFFu | PIN_ADC_INTERLEAVE_ENABLE0 } },
    { { PORTB_BASE,  1U, 0xFFu  } , {0xFFu | PIN_ADC_INTERLEAVE_ENABLE1 } },
    { { PORTB_BASE, 13U, 0xFFu  } , {0xFFu | PIN_ADC_INTERLEAVE_ENABLE2 } },
    { { PORTB_BASE, 14U, 0xFFu  } , {0xFFu | PIN_ADC_INTERLEAVE_ENABLE3 } },
    { { PORTB_BASE, 15U, 0xFFu  } , {0xFFu & PIN_ADC_INTERLEAVE_DISABLE0} },
    { { PORTB_BASE, 16U, 0xFFu  } , {0xFFu & PIN_ADC_INTERLEAVE_DISABLE1} },
    { { PORTB_BASE, 31U, 0xFFu  } , {         PIN_ADC_INTERLEAVE_INVALID} },
    { { PORTC_BASE,  0U, 0xFFu  } , {0xFFu & PIN_ADC_INTERLEAVE_DISABLE2} },
    { { PORTC_BASE,  1U, 0xFFu  } , {0xFFu & PIN_ADC_INTERLEAVE_DISABLE3} },
    { { PORTC_BASE, 31U, 0xFFu  } , {         PIN_ADC_INTERLEAVE_INVALID} },
    { { PORTD_BASE, 31U, 0xFFu  } , {         PIN_ADC_INTERLEAVE_INVALID} },

  };

  uint32 returnValue;

  for (uint8 ucIdx = 0; ucIdx < sizeof(asTestCaseData) / sizeof(tsTestCaseData); ucIdx++)
  {
    //Step 1) Set pre - conditions if needed


    //Step 2) Assign all input values to the corresponding input variables identified in the FUT

    //Step 3) Call the FUT
    returnValue = PINS_GetAdcInterleaveVal(asTestCaseData[ucIdx].sInputData.portAddr, asTestCaseData[ucIdx].sInputData.ulpinPortIdx, asTestCaseData[ucIdx].sInputData.ulCurrentVal);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    AL_UNITTEST_CHECK(returnValue, asTestCaseData[ucIdx].sOutputData.ulAdcReturnValue, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Port_Read_Write
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject: 
///        Check if the function Mt_Port_Read_Write reads the value of a specific pin of a port correctly
///
/// \Steps:
///         Step1: Set pre - conditions if neededT
///         Step2: Call the FUT
///         Step3: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
///         - Inputs:
///           - port number
///           - pin number
///         - Expected results
///           - returned value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
///       For further information about specific input/outputs variables refer to the  input assignament (step 2) and output value check (step 4) of this Unit Test Case
///
///    - Preconditions:
///           - 
///
//-----------------------------------------------------------------------------
void Mt_Port_Read_Write(void)
{
  uint8 returnValue;

  //Step 3) Call the FUT
  returnValue = Port_Read(0U, 0U, NULL);

  //Step 3) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 

  AL_UNITTEST_CHECK(returnValue, E_NOT_OK, ==);

  //Step 2) Call the FUT
  returnValue = Port_Write(0U, 0U, 0U);

  //Step 3) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(returnValue, E_NOT_OK, == );
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
  ALUnitTest_AddFunction("Mt_Port_Port_Init", Mt_Port_Port_Init);
  ALUnitTest_AddFunction("Mt_Port_Port_Read_Write", Mt_Port_Read_Write);
  ALUnitTest_AddFunction("Mt_Port_Port_PINS_GetAdcInterleaveVal", Mt_Port_PINS_GetAdcInterleaveVal);
  ALUnitTest_AddFunction("Mt_Port_Port_PINS_GPIO_WritePin", Mt_Port_PINS_GPIO_WritePin);
}

// EOF

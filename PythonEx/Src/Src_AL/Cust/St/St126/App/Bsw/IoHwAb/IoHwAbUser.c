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
/// \file  IoHwAbUser.c
///
/// \brief  Basic Software I/O Hardware Abstraction User
///
/// \descr  Additional information can be found in the design description
///
//-----------------------------------------------------------------------------


//=============================================================================
//  Project-specific header file includes
//=============================================================================

#include <AL_Helper.h>
#include "IoHwAbUser.h"
#include <UtilUtility.h>
#include <UtilMath.h>
#include <Adc.h>
#include <Dio.h>
#include <Pwm.h>
#include <CddEft.h>
#include <Cfg/Cfg.h>
#include <Nvm.h>
#ifndef UNIT_TEST
#include <Icu.h>
#include <Rte.h>
#include <CddSbc.h>
#endif

//=============================================================================
//  Defines
//=============================================================================

#define IOHWAB_USER_VCCX2_VBAT_MIN_VAL                5600u
#define IOHWAB_USER_VCCX2_VBAT_MAX_VAL               37000u
#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
#define IOHWABUSER_FCT_OUT_ADC_SAMPLES_NR               30u
#define IOHWABUSER_FCT_OUT_SC_GND_MV                   100u
#define IOHWABUSER_FCT_OUT_SC_VBAT_MV                 5600u
#define IOHWABUSER_FCT_OUT_SC_GND_DC                  1000u
#define IOHWABUSER_FCT_OUT_SC_VBAT_DC                 9000u
#endif


//=============================================================================
//  Variable declarations
//=============================================================================
STATIC_AL boolean                       IoHwAbUser_boEftCrcStatus = TRUE;

STATIC_AL sint32                        IoHwAbUser_aslSensPwmTarget[IOHWABUSER_NR_PWMTARGET] = { 0, 0};

STATIC_AL boolean                       IoHwAbUser_boVccxStatus;

STATIC_AL tieMountingSideRaw            IoHwAbUser_ulMountingSideRaw= 0x0000u;

STATIC_AL uint8                         IoHwAbUser_ucRingBuffElem = 0x00u;

STATIC_AL uint16                        IoHwAbUser_unFactorVBAT = 0u;
STATIC_AL uint16                        IoHwAbUser_unFactorFout = 0u;

STATIC_AL uint16                        IoHwAbUser_unFilterCoefHssSenseS1_2;
STATIC_AL ORDER1_Filter                 IoHwAbUser_slHssSenseS1_2_Filter;

STATIC_AL uint16                        IoHwAbUser_unFilterCoefHssSenseS3;
STATIC_AL ORDER1_Filter                 IoHwAbUser_slHssSenseS3_Filter;

STATIC_AL ORDER1_Filter                 IoHwAbUser_slPCB_Filter;
STATIC_AL uint16                        IoHwAbUser_unFilterCoefPCB;
STATIC_AL uint16                        IoHwAbUser_unFilterCoefNTC;
STATIC_AL ORDER1_Filter                 IoHwAbUser_tNTC_Filter[IOHWABUSER_CFG_MAX_NO_OF_EXT_NTCS];

STATIC_AL ORDER1_Filter                 IoHwAbUser_slVCCX1_Filter;
STATIC_AL uint16                        IoHwAbUser_unFilterCoefVCCX1;


STATIC_AL uint16                        IoHwAbUser_unFilterCoefNTC;
STATIC_AL ORDER1_Filter                 IoHwAbUser_aslNTC_Filter[IOHWABUSER_CFG_MAX_NO_OF_EXT_NTCS];

STATIC_AL tiu32Voltage_mV               IoHwAbUser_ulVBatMean;
STATIC_AL tiu32Voltage_mV               IoHwAbUser_ulVBatMin;

STATIC_AL tiu16Voltage_mV               IoHwAbUser_ulPCB;
STATIC_AL uint16                        IoHwAbUser_unFactorPCB;

STATIC_AL tiu16Voltage_mV               IoHwAbUser_ulVCCX1;
STATIC_AL uint16                        IoHwAbUser_unFactorVCCX1, IoHwAbUser_unFactorVCCX2;

STATIC_AL uint16                        IoHwAbUser_unFactorNTC[IOHWABUSER_CFG_MAX_NO_OF_EXT_NTCS];
STATIC_AL tiu16Voltage_mV               IoHwAbUser_aunNTCVoltage[IOHWABUSER_CFG_MAX_NO_OF_EXT_NTCS];

STATIC_AL tiu32Voltage_mV               IoHwAbUser_ulADCHSS_3;
STATIC_AL tsIoHwAbUser_HSSDioInfo       IoHwAbUser_sHssDioInfo;
STATIC_AL uint16                        IoHwAbUser_unFactorHssSense3;
STATIC_AL uint16                        IoHwAbUser_unFactorHssSenseS1_2;
STATIC_AL tiu32Voltage_mV               IoHwAbUser_aulHSSSensorVoltage[IOHWABUSER_NR_HSSSENSOR];

STATIC_AL uint8                         IoHwAbUser_ucEXT_NTC;

STATIC_AL tiu32Voltage_mV               IoHwAbUser_aulRingBuff[IOHWABUSER_RINGBUFFER_SIZE];

STATIC_AL uint8                         IoHwAbUser_ucMeasMode = IOHWABUSER_MEAS_MODE_PERIOD;
STATIC_AL uint16                        IoHwAbUser_unSensMeasPeriodAndDuty[2u][2u] = { { 5000u, 0u },{ 5000u, 0u } };
STATIC_AL uint16                        IoHwAbUser_unSensCalculatedDuty[2u] = { 0u, 0u };
STATIC_AL uint8                         IoHwAbUser_ucMeasCycle = 0U;

STATIC_AL tsRteCodingParameters         IoHwAbUser_pCodingArea;
STATIC_AL boolean                       IoHwAbUser_boIsCodingValid = TRUE;

#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
STATIC_AL  uint32               IoHwAbUser_ulFctOut_Voltage_Acc = 0u;
STATIC_AL  uint32               IoHwAbUser_ulFctOut_Cnt         = 0u;
STATIC_AL  uint16               IoHwAbUser_unFctOut_Voltage_mV  = 0u;
STATIC_AL  boolean              IoHwAbUser_boFctOut_ShGnd       = FALSE;
STATIC_AL  boolean              IoHwAbUser_boFctOut_ShVbat      = FALSE;
STATIC_AL  boolean              IoHwAb_boLssDiagnostic          = FALSE;
#endif

#if defined(SAMPLE_ECO) || defined(UNIT_TEST)
STATIC_AL tFiltIir_u                    IoHwAbUser_aFltDC_OUT;      // fast P-T1 filter for DC_OUT inputs
#endif

#if (CFG_DEV_HOOK_EN == 1u)
#define IOHWABUSER_HOOK_KEY       0x5A5AA5A5u
STATIC_AL volatile uint32 VCCXErrors_ulTesterHookActivation = 0u;
STATIC_AL volatile uint32 ulVccx_mV_TestValue = 0u;
STATIC_AL volatile Dio_LevelType ulVccx_PG_Level = 0u;
#endif


// function pointer to all the getters for every external NTCs ( 10 for ECO, 14 for FULL)
STATIC_AL tiu16Voltage_mV( *IoHwAb_apfReadNTC[] )(void) =
{ IoHwAbUser_GetVoltage_EXT1,
  IoHwAbUser_GetVoltage_EXT2,
  IoHwAbUser_GetVoltage_EXT3,
  IoHwAbUser_GetVoltage_EXT4,
  IoHwAbUser_GetVoltage_EXT5,
  IoHwAbUser_GetVoltage_EXT6,
  IoHwAbUser_GetVoltage_EXT7,
  IoHwAbUser_GetVoltage_EXT8,
  IoHwAbUser_GetVoltage_EXT9,
  IoHwAbUser_GetVoltage_EXT10,
#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
  IoHwAbUser_GetVoltage_EXT11,
  IoHwAbUser_GetVoltage_EXT12,
  IoHwAbUser_GetVoltage_EXT13,
  IoHwAbUser_GetVoltage_EXT14
#endif
};

STATIC_AL CONST_AL Pwm_ChannelType IoHwAb_aulPwm_Channel_Map[IOHWABUSER_CFG_MAX_NO_OF_LS_CHANNELS] =
{
  #if defined(SAMPLE_FULL) || defined(UNIT_TEST)
  /*Channel Index*/
  IOHWABUSER_PWM_CHANNEL_MAP_LEDCNTRL_1,
  IOHWABUSER_PWM_CHANNEL_MAP_LEDCNTRL_2,
  IOHWABUSER_PWM_CHANNEL_MAP_LEDCNTRL_3,
  IOHWABUSER_PWM_CHANNEL_MAP_LEDCNTRL_4,
  IOHWABUSER_PWM_CHANNEL_MAP_LEDCNTRL_5,
  IOHWABUSER_PWM_CHANNEL_MAP_LEDCNTRL_6,
  IOHWABUSER_PWM_CHANNEL_MAP_LEDCNTRL_7,
  IOHWABUSER_PWM_CHANNEL_MAP_LEDCNTRL_8,
  IOHWABUSER_PWM_CHANNEL_MAP_LEDCNTRL_9,
  IOHWABUSER_PWM_CHANNEL_MAP_LEDCNTRL_10,
  IOHWABUSER_PWM_CHANNEL_MAP_LEDCNTRL_11,
  IOHWABUSER_PWM_CHANNEL_MAP_LEDCNTRL_12,
  IOHWABUSER_PWM_CHANNEL_MAP_HSS_EN_3,

  #elif defined(SAMPLE_ECO) || defined(UNIT_TEST)
  IOHWABUSER_PWM_CHANNEL_MAP_LEDCNTRL_1,
  IOHWABUSER_PWM_CHANNEL_MAP_LEDCNTRL_2,
  IOHWABUSER_PWM_CHANNEL_MAP_LEDCNTRL_3,
  IOHWABUSER_PWM_CHANNEL_MAP_LEDCNTRL_4,
  IOHWABUSER_PWM_CHANNEL_MAP_LEDCNTRL_5,
 #endif
};


STATIC_AL CONST_AL uint8 IoHwAb_aucAdc_EXT_Channel_Map[IOHWABUSER_CFG_MAX_NO_OF_EXT_NTCS] =
{
  #if defined(SAMPLE_FULL) || defined(UNIT_TEST)
  IOHWABUSER_ADC_CHANNEL_MAP_ADC_EXT_1,
  IOHWABUSER_ADC_CHANNEL_MAP_ADC_EXT_2,
  IOHWABUSER_ADC_CHANNEL_MAP_ADC_EXT_3,
  IOHWABUSER_ADC_CHANNEL_MAP_ADC_EXT_4,
  IOHWABUSER_ADC_CHANNEL_MAP_ADC_EXT_5,
  IOHWABUSER_ADC_CHANNEL_MAP_ADC_EXT_6,
  IOHWABUSER_ADC_CHANNEL_MAP_ADC_EXT_7,
  IOHWABUSER_ADC_CHANNEL_MAP_ADC_EXT_8,
  IOHWABUSER_ADC_CHANNEL_MAP_ADC_EXT_9,
  IOHWABUSER_ADC_CHANNEL_MAP_ADC_EXT_10,
  IOHWABUSER_ADC_CHANNEL_MAP_ADC_EXT_11,
  IOHWABUSER_ADC_CHANNEL_MAP_ADC_EXT_12,
  IOHWABUSER_ADC_CHANNEL_MAP_ADC_EXT_13,
  IOHWABUSER_ADC_CHANNEL_MAP_ADC_EXT_14,

  #elif defined(SAMPLE_ECO) || defined(UNIT_TEST)
  IOHWABUSER_ADC_CHANNEL_MAP_ADC_EXT_1,
  IOHWABUSER_ADC_CHANNEL_MAP_ADC_EXT_2,
  IOHWABUSER_ADC_CHANNEL_MAP_ADC_EXT_3,
  IOHWABUSER_ADC_CHANNEL_MAP_ADC_EXT_4,
  IOHWABUSER_ADC_CHANNEL_MAP_ADC_EXT_5,
  IOHWABUSER_ADC_CHANNEL_MAP_ADC_EXT_6,
  IOHWABUSER_ADC_CHANNEL_MAP_ADC_EXT_7,
  IOHWABUSER_ADC_CHANNEL_MAP_ADC_EXT_8,
  IOHWABUSER_ADC_CHANNEL_MAP_ADC_EXT_9,
  IOHWABUSER_ADC_CHANNEL_MAP_ADC_EXT_10,
  #endif
};



//=============================================================================
//  Function prototypes
//=============================================================================

STATIC_AL void IoHwAbUser_InitializeBuffers(void);
STATIC_AL void IoHwAbUser_FilterInitialization(void);
STATIC_AL void IoHwAbUser_HSSOperation(boolean boinit);
STATIC_AL void IoHwAbUser_HSSOperationForEcuHighVar(void);
STATIC_AL void IoHwAbUser_CalcVBatMeanValue(void);
STATIC_AL void IoHwAbUser_GetEftData(void);
STATIC_AL void IoHwAbUser_GetADC_HSSSense(void);
STATIC_AL void IoHwAbUser_GetSens_Raw(void);
STATIC_AL void IoHwAbUser_GetSens_Balanced(void);
STATIC_AL void IoHwAbUser_CalcInputPwmSens(void);
STATIC_AL void IoHwAbUser_SetNvm_ElecError(uint8 ucSensIdx);
STATIC_AL boolean IoHwAbUser_CheckSens0_OpenLoad(void);
STATIC_AL boolean IoHwAbUser_CheckSens1_OpenLoad(void);

#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
STATIC_AL void IoHwAbUser_ProcessOutFctDiag(void);
STATIC_AL void IoHwAbUser_ReportVccx2Error(teIoHwAb_VccxLineState eVccx1ErrorState);
#endif
#if defined(SAMPLE_ECO) || defined(UNIT_TEST)
STATIC_AL void IoHwAbUser_ParaFct0(void);
#endif

#if defined(SAMPLE_ECO) || defined(UNIT_TEST)
          void IoHwAb_User_SetDio_EN_DC(Dio_LevelType ucSignal) { Dio_WriteChannel(2, ucSignal); }
#endif

//=============================================================================
// Function definitions
//=============================================================================

#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
//-----------------------------------------------------------------------------
/// \brief IoHwAbUser_ProcessOutFctDiag
///
/// \descr Low Side Switch Diagnostic
///
/// \param  void
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void IoHwAbUser_ProcessOutFctDiag(void)
{
  uint16 unReadAdc_OutFct =  0u;
  STATIC_UT(uint16, unNew_PWM, 0u);
  STATIC_UT(uint16, unOld_PWM, 0xFFFFu);

  // Get LSS target PWM
  unNew_PWM = CddSbc_GetPWM(0u);

  // New target PWM
  if (unNew_PWM != unOld_PWM)
  {
    // Reset variables
    IoHwAbUser_ulFctOut_Voltage_Acc = 0u;
    IoHwAbUser_ulFctOut_Cnt = 0u;
  }
  else
  { 
    // Get the ADCRaw values of FCT_OUT (SBC low side switch)
    (void)Adc_ReadGroup(IOHWABUSER_ADC_GROUP_CHANNEL_MAP_ADC_OUT_FCT, &unReadAdc_OutFct);
    // Add ADC value for mean calculation
    IoHwAbUser_ulFctOut_Voltage_Acc += (uint32)unReadAdc_OutFct;

    IoHwAbUser_ulFctOut_Cnt++;

    // After 30 measurements (3 FCT OUT periods)
    if (IoHwAbUser_ulFctOut_Cnt == IOHWABUSER_FCT_OUT_ADC_SAMPLES_NR)
    {
      // Mean calculation
      IoHwAbUser_unFctOut_Voltage_mV = (uint16)(((IoHwAbUser_ulFctOut_Voltage_Acc / IOHWABUSER_FCT_OUT_ADC_SAMPLES_NR) * IoHwAbUser_unFactorFout) / IOHWABUSER_RESOLUTION_12BIT);

      // > 90% and low voltage detected => ScGnd
      if ((unNew_PWM < IOHWABUSER_FCT_OUT_SC_GND_DC) && (IoHwAbUser_unFctOut_Voltage_mV < IOHWABUSER_FCT_OUT_SC_GND_MV))
      {
        IoHwAbUser_boFctOut_ShGnd = TRUE;
      }
      // < 10% and high voltage detected => ScVbat
      else if ((unNew_PWM > IOHWABUSER_FCT_OUT_SC_VBAT_DC) && (IoHwAbUser_unFctOut_Voltage_mV > IOHWABUSER_FCT_OUT_SC_VBAT_MV))
      {
        IoHwAbUser_boFctOut_ShVbat = TRUE;
      }
      // No issues
      else if ((unNew_PWM < IOHWABUSER_FCT_OUT_SC_GND_DC) && (IoHwAbUser_unFctOut_Voltage_mV > 500u))
      {
        IoHwAbUser_boFctOut_ShGnd = FALSE;
      }
      else if ((unNew_PWM > IOHWABUSER_FCT_OUT_SC_VBAT_DC) && (IoHwAbUser_unFctOut_Voltage_mV < 1200u))
      {
        IoHwAbUser_boFctOut_ShVbat = FALSE;
      }
      else
      {
        // keep last error
      }

      IoHwAbUser_ulFctOut_Voltage_Acc = 0u;
      IoHwAbUser_ulFctOut_Cnt = 0u;
    }
  }
  // Update Old PWM value
  unOld_PWM = unNew_PWM;
} //PRQA S 5336  // STMIF = 6, Statement intended due function complexity

//-----------------------------------------------------------------------------
/// \brief IoHwAbUser_GetOutFctDiag
///
/// \descr
///
/// \param  boLssDiagnostic
///
/// \return void
//-----------------------------------------------------------------------------
void IoHwAbUser_GetOutFctDiag(boolean *boLssDiagnostic)
{
  boLssDiagnostic[0] = IoHwAbUser_boFctOut_ShGnd;
  boLssDiagnostic[1] = IoHwAbUser_boFctOut_ShVbat;
}


//-----------------------------------------------------------------------------
/// \brief IoHwAbUser_SetLSSDiagnostic
///
/// \descr
///
/// \param  boDiagStatus
///
/// \return void
//-----------------------------------------------------------------------------
void IoHwAbUser_SetLSSDiagnostic(boolean boDiagStatus)
{
  IoHwAb_boLssDiagnostic = boDiagStatus;
}
#endif


//-----------------------------------------------------------------------------
/// \brief  Init-function to intialize IoHwAbUser
///
/// \descr  IoHwAbUser_Init() reads RTE-Ports of EftCrcStatus and EftData,
///         initializes private variables and call the internal function
///         IoHwAbUser_InitGetMountingSide() to determine the Mounting Side call
///         only once initially.
///         Calling once at start up.
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void IoHwAbUser_Init(void)
{
  tsRte_Ntc sNTCVoltage = { 0, NULL_PTR };
  uint16 unRaw;
  uint16 unMv = 0;

  IoHwAbUser_ulVBatMean = 0u;
  IoHwAbUser_ulVBatMin = 0u;
  IoHwAbUser_ulPCB = 0u;
  IoHwAbUser_ulVCCX1 = 0u;
  sNTCVoltage.ucNrNTC = IOHWABUSER_CFG_MAX_NO_OF_EXT_NTCS;
  sNTCVoltage.Fct = IoHwAb_apfReadNTC;
  IoHwAbUser_boVccxStatus = FALSE;
#if defined(SAMPLE_ECO) || defined(UNIT_TEST)
 // Read the voltage for DC from ADC
  (void)Adc_ReadGroup(IOHWABUSER_ADC_CHANNEL_MAP_ADC_DC_OUT_1, &unRaw);
  unMv = (uint16)(((unRaw * EFT_ECUVARCFG_ADCFACTOR.unFactor_DcOut) / IOHWABUSER_RESOLUTION_12BIT));
  UtilMath_FastIir_u_Init(&IoHwAbUser_aFltDC_OUT, unMv);
#endif
  // Filter initialization
  IoHwAbUser_FilterInitialization();

  // Get EftData
  IoHwAbUser_GetEftData();

  // Initialize all IoHwAbUser Buffers
  IoHwAbUser_InitializeBuffers();

  // Function is called in EcuM Startup Two - fix for bugfix/LDMO-2198
  //IoHwAbUser_InitGetMountingSide();

  IoHwAbUser_HSSOperation(TRUE);

  IoHwAbUser_GetVoltage_NTC();

#ifdef SAMPLE_FULL
  IoHwAbUser_SetVccxEn(TRUE);
#endif
}

//-----------------------------------------------------------------------------
/// \brief  De-init function to de-intialzie IoHwAbUser
///
/// \descr  IoHwAbUser_DeInit() function is not used in the A230 Release,
///         but it has been created a Dummy function based on the SW Requirement
///         definition. It can be used when the DEINIT function is required
///         for later release.
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void IoHwAbUser_DeInit(void)
{
  (void)IoHwAbUser_ulVBatMean;

#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
  // set HSS_SEL to LOW
  IoHwAbUser_SetHss_Sel1(FALSE);
  IoHwAbUser_SetHss_Sel2(FALSE);
#endif
}

//-----------------------------------------------------------------------------
/// \brief  Cyclic function for IoHwAbUser
///
/// \descr  IoHwAbUser_Cycle() is reading the ADC Raw value of ECU Temperature
///         and NTC1 to NTC7 using a multiplexer.
///         Calling cyclically every 1ms
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void IoHwAbUser_Cycle(void)
{
  static uint8 ucSubCycle = 0u;
  uint16 unRaw;
  uint16 unMv;

  STATIC_UT(boolean, boFlag, FALSE);

#if defined(SAMPLE_ECO) || defined(UNIT_TEST)
  if (IoHwAbUser_boIsCodingValid != FALSE)
  {
    if (boFlag == FALSE)
    {
      IoHwAbUser_ParaFct0();
      boFlag = TRUE;
    }
}
  else
  {
    // Coding not available
  }
#endif

#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
  if (IoHwAb_boLssDiagnostic != FALSE)
  {
    IoHwAbUser_ProcessOutFctDiag();
  }
#endif
  
  // Subcycle 100ms is the smaller common multiple and we want to execute only when the subcycle is equal 0.
  // For this the subcycle ill be reset to 0 when it reaches 100ms before to execute any function. 
  //The subcycle is incremented at the end of the cycle
  if (ucSubCycle == IOHWABUSER_SUBCYCLE_100MS)
  {
    ucSubCycle = 0u;
  }

  // 1 ms execution
  IoHwAbUser_GetADC_HSSSense();   //Gets adc raw value of hss sensors and then filter them
  IoHwAbUser_HSSOperation(FALSE); // ADC measurement for High Side Switch
  IoHwAbUserTimer0Notification();  // CallBack called in ISR context, triggered every 312, 5 usec


  (void)IoHwAbUser_Read_VCCX1();

#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
  IoHwAbUser_Set_Vccx_State(TRUE);
  IoHwAbUser_VccxStateCyclicCheck();
#endif

  // 5 ms execution
  if (((ucSubCycle + 1u) % IOHWABUSER_SUBCYCLE_5MS) == 0u)
  {
    // Calculate the analog sensor value for pitch
    IoHwAbUser_CalcInputPwmSens();
    IoHwAbUser_GetSens_Raw();
    IoHwAbUser_GetSens_Balanced();
  }
  // 10 ms execution
  if (((ucSubCycle + 2u) % IOHWABUSER_SUBCYCLE_10MS) == 0u)
  {
    IoHwAbUser_CalcVBatMeanValue();  // Calculate the mean value of the battery voltage and send it to the RTE.
    if (IoHwAbUser_ulMountingSideRaw == IOHWABUSER_MOUNTINGSIDERAW_UNKNOW)
    {
      Rte_Call_DemPrj_ReportErrorStatus((uint16)LR_Detect, DEM_EVENT_STATUS_FAILED);
    }
    else
    {
      Rte_Call_DemPrj_ReportErrorStatus((uint16)LR_Detect, DEM_EVENT_STATUS_PASSED);
    }
  }
  // 100 ms execution
  if ((ucSubCycle % IOHWABUSER_SUBCYCLE_100MS) == 0u)
  {
    IoHwAbUser_GetVoltage_NTC();     // Get voltage for each EXT NTC
    IoHwAbUser_Get_PCB();
  }

#if defined(SAMPLE_ECO) || defined(UNIT_TEST)
  (void)Adc_ReadGroup(IOHWABUSER_ADC_CHANNEL_MAP_ADC_DC_OUT_1, &unRaw); // Workaround tbd
  unMv = (uint16)( ((unRaw * EFT_ECUVARCFG_ADCFACTOR.unFactor_DcOut) / IOHWABUSER_RESOLUTION_12BIT) );
  UtilMath_FastIir_u(&IoHwAbUser_aFltDC_OUT, unMv, IOHWABUSER_FLTDCOUT);
#endif
  ucSubCycle++;
}  //PRQA S 5310, 5324  // STCAL = 9, Statement intended due function complexity

#if defined(SAMPLE_ECO) || defined(UNIT_TEST)
//-----------------------------------------------------------------------------
/// \brief  Get voltage of DC_OUT1 inputs
///
/// \descr  
///
/// \param  pio_signal 
///
/// \return void 
//-----------------------------------------------------------------------------
void IoHwAbUser_GetAdc_VoltDC_OUT1(uint16 *pio_signal)
{
  *pio_signal = (uint16)UtilMath_FastIir_u_GetResult(&IoHwAbUser_aFltDC_OUT);
}

//-----------------------------------------------------------------------------
/// \brief IoHwAbUser_ParaFct0
///
/// \descr IoHwAbUse function to get coding data
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void IoHwAbUser_ParaFct0(void)
{
  tParaFct0_Cmd sCodingStatus = eParaFct0_CodingDataInvalid;
  (void)Rte_Read_CodM_IoHwAbUser_Para(&IoHwAbUser_pCodingArea);

  sCodingStatus = IoHwAbUser_pCodingArea.eCodingState;

  if (sCodingStatus == eParaFct0_CodingDataValid)
  {
    IoHwAbUser_boIsCodingValid = TRUE;
  }
  else
  {
    IoHwAbUser_boIsCodingValid = FALSE;
  }
}


#endif
//-----------------------------------------------------------------------------
/// \brief  IoHwAb_User_GetADC_HSSSense
///
/// \descr  Gets adc raw value of hss sensors and then filter them
///
/// \param  -
///
/// \return void
//------------------------------------------------------------------------------
STATIC_AL void IoHwAbUser_GetADC_HSSSense(void)
{
  uint16 unReadAdcRawHSSSenseS1_2 = 0u;
  uint16 unReadAdcRawHSSSenseS3 = 0u;

  // Get the ADCRaw values of HSS Sensors
  (void)Adc_ReadGroup(IOHWABUSER_ADC_GROUP_CHANNEL_MAP_ADC_HSS_SENSE_1_2, &unReadAdcRawHSSSenseS1_2);
#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
  (void)Adc_ReadGroup(IOHWABUSER_ADC_GROUP_CHANNEL_MAP_ADC_HSS_SENSE_3, &unReadAdcRawHSSSenseS3);
#endif
  // Get the filter value of HSS Sensors
  Order1Filter(&IoHwAbUser_slHssSenseS1_2_Filter, (sint16)unReadAdcRawHSSSenseS1_2, IoHwAbUser_unFilterCoefHssSenseS1_2);
#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
  Order1Filter(&IoHwAbUser_slHssSenseS3_Filter, (sint16)unReadAdcRawHSSSenseS3, IoHwAbUser_unFilterCoefHssSenseS3);
#endif
}

//-----------------------------------------------------------------------------
/// \brief  Internal function for mounting side in IoHwAbUser
///
/// \descr  IoHwAbUser_InitGetMountingSide()function accesses the memory only
///         once when initialization and determines whether the mounting side of
///         the ECU is left or right, and stores the mounting side value in
///         the global variable for use whenever the application requests it.
///         Calling once from the IoHwAbUser_Init() function.
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void IoHwAbUser_InitGetMountingSide(void)
{
#if defined(UNIT_TEST)
  uint32 Mt_IoHwAbuser_MTMemoryValue[2] = { 0x0000U, 0x1234U };
  Mt_IoHwAbuser_GetMountingSideMemoryValue(Mt_IoHwAbuser_MTMemoryValue);

  const volatile uint16* const LpLRDetectPtr = (const volatile uint16*)((uint32*)(&Mt_IoHwAbuser_MTMemoryValue[0]));
  const volatile uint16* const LpLRDetectInvPtr = (const volatile uint16*)((uint32*)(&Mt_IoHwAbuser_MTMemoryValue[1]));
#else
  // PRQA S 303 3 // Memory access is needed here by design.
  // PRQA S 306 3 // Memory access is needed here by design.
  const volatile uint16* const LpLRDetectPtr = (const volatile uint16*)(IOHWABUSER_MEM_ADR_LR_DET);
  const volatile uint16* const LpLRDetectInvPtr = (const volatile uint16*)(IOHWABUSER_MEM_ADR_LR_DET_INV);
#endif

  teRte_MountingSide eMountingSide = eMountedLeft;

  // Check if it's Left Ecu
  if ((*LpLRDetectPtr == IOHWABUSER_LEFT_ECU) && (*LpLRDetectInvPtr == IOHWABUSER_LEFT_ECU_INV))
  {
    IoHwAbUser_ulMountingSideRaw= IOHWABUSER_MOUNTINGSIDERAW_LEFT;
    eMountingSide = eMountedLeft;
  }

  // Check if it's right Ecu
  else if ((*LpLRDetectPtr == IOHWABUSER_RIGHT_ECU) && (*LpLRDetectInvPtr == IOHWABUSER_RIGHT_ECU_INV))
  {
    IoHwAbUser_ulMountingSideRaw= IOHWABUSER_MOUNTINGSIDERAW_RIGHT;
    eMountingSide = eMountedRight;
  }

  // Check if it's an unknown information
  else if ((*LpLRDetectPtr == IOHWABUSER_UNKNOWN_ECU) && (*LpLRDetectInvPtr == IOHWABUSER_UNKNOWN_ECU_INV))
  {
    IoHwAbUser_ulMountingSideRaw= IOHWABUSER_MOUNTINGSIDERAW_UNKNOW;
    eMountingSide = eMountedUndef;
  }
  else
  {
    IoHwAbUser_ulMountingSideRaw= IOHWABUSER_MOUNTINGSIDERAW_RIGHT;
    eMountingSide = eMountedRight;
  }
  // Write Left/Right information for other modules
  (void)Rte_Write_IoHwAbUser_GetMountingSide(&eMountingSide);
}

//-----------------------------------------------------------------------------
/// \brief  Internal function for GPIO Switching and ADC measurement for High Side Switch
///
/// \descr  Change the DIO of the HSS every 30 seconds and measure the ADC.
///
///
/// \param  boolean init - it is used to call once with TRUE for IoHwAbUser_sHssDioInfo initialization, after
///                        it is called with FALSE at cyclic runable
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void IoHwAbUser_HSSOperation(boolean boinit)
{
  // Check if the initialization is already done
  if (boinit != FALSE)
  {
#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
    Dio_WriteChannel(IOHWABUSER_DIO_CHANNEL_MAP_HSS_SEL_1, FALSE);
#endif

    IoHwAbUser_sHssDioInfo.ucWaitingTime = 0u;
    IoHwAbUser_sHssDioInfo.boDioSel0Toggle = FALSE;
  }
  else
  {
    // Check the waiting time (5ms)
    if (IoHwAbUser_sHssDioInfo.ucWaitingTime == IOHWABUSER_HSS_ADC_WAIT_TIME_30MS)
    {
       IoHwAbUser_HSSOperationForEcuHighVar();

      // Set the waiting time variable to 0 after finishing the HSS voltage measurement process
      IoHwAbUser_sHssDioInfo.ucWaitingTime = 0u;
    }
    else
    {
      // Increment the waiting time if it has not yet reached the 30 ms
      IoHwAbUser_sHssDioInfo.ucWaitingTime++;
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief Function uses the "CodM_ppCodMEftData0_GetData" interface to give us the eft data
///
/// \descr IoHwAbUser_GetEftData
///
/// \param  - void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void IoHwAbUser_GetEftData(void)
{
  uint8 ucIdx = 0u;
  uint8 ucCrc = 0u;

  // Get the VBAT and PCBTemperature factors from the EftData
  IoHwAbUser_unFactorVBAT = EFT_ECUVARCFG_ADCFACTOR.unFactor_Vbat;
  IoHwAbUser_unFactorPCB = EFT_ECUVARCFG_ADCFACTOR.unFactor_PcbTemp;
  IoHwAbUser_unFactorVCCX1 = EFT_ECUVARCFG_ADCFACTOR.unFactor_Vccx[0];
  IoHwAbUser_unFactorVCCX2 = EFT_ECUVARCFG_ADCFACTOR.unFactor_Vccx[1];
  IoHwAbUser_unFactorFout = EFT_ECUVARCFG_ADCFACTOR.unFactor_OutFct;

  // Fill the NTCs ADC factors buffer with the corresponding values
  for (ucIdx = 0u; ucIdx < IOHWABUSER_CFG_MAX_NO_OF_EXT_NTCS; ucIdx++)
  {
    IoHwAbUser_unFactorNTC[ucIdx] = EFT_ECUVARCFG_ADCFACTOR.unFactor_Ntc[ucIdx];
  }

  // Get the HssSensors factors from the EftData
  IoHwAbUser_unFactorHssSenseS1_2 = EFT_ECUVARCFG_ADCFACTOR.unFactor_HssSense_1_2;
 #if defined(SAMPLE_FULL) || defined(UNIT_TEST)
  IoHwAbUser_unFactorHssSense3 = EFT_ECUVARCFG_ADCFACTOR.unFactor_HssSense_3;
 #endif
}

//-----------------------------------------------------------------------------
/// \brief  API function to send the stored mounting side raw value to RTE
///
/// \descr  IoHwAbUser_GetMountingSideRaw() function sends the initially stored
///         mounting side value to the RTE.
///
/// \param  tieMountingSideRaw* peVal        Stored Mounting Side Value
///                                          Left   : 0xFEFE 0101
///                                          Right  : 0xFDFD 0202
///                                          Unknown: 0xFCFC 0303
///
/// \return void
//-----------------------------------------------------------------------------
void IoHwAbUser_GetMountingSideRaw(tieMountingSideRaw* pulVal)
{
  // Mounting Side is not initialized when raw function is called for the first time
  IoHwAbUser_InitGetMountingSide();
  // Send the stored mounting side raw value to RTE
  *pulVal = IoHwAbUser_ulMountingSideRaw;
}

//-----------------------------------------------------------------------------
/// \brief  API function to set the LED Boost mode
///
/// \descr  IoHwAbUser_SetBoostMode() sets the requested LED Boost mode value.
///
/// \param  boEnable1 sSetting   Parameter for setting Boost mode
///
/// \return void
//-----------------------------------------------------------------------------
void IoHwAbUser_SetBoostMode(const boolean boEnable1)
{
  // Set the LED Boost mode
  Dio_WriteChannel(IOHWABUSER_DIO_CHANNEL_MAP_BOOST_EN, (Dio_LevelType)boEnable1);
}

#if defined(SAMPLE_ECO)
//-----------------------------------------------------------------------------
/// \brief  API function to set the High Side Switch
///
/// \descr  IoHwAb_User_SetHss_En1() function sets the requested High Side Switch
///         value to Enable or Disable.
///
/// \param  tun16Percent_1_328 unTgtVal
///
/// \return void
//-----------------------------------------------------------------------------
void IoHwAbUser_SetHss_En1(tun16Percent_1_328 unTgtVal)
{
  if (unTgtVal == IOHWABUSER_MAX_TARGET_VALUE)
  {
    Dio_WriteChannel(IOHWABUSER_DIO_CHANNEL_MAP_HSS_EN_1, TRUE);
  }
  else
  {
    Dio_WriteChannel(IOHWABUSER_DIO_CHANNEL_MAP_HSS_EN_1, FALSE);
  }
}

#endif

#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
//-----------------------------------------------------------------------------
/// \brief  API function to set the High Side Switch
///
/// \descr  IoHwAb_User_SetHss_En1() function sets the requested High Side Switch
///         value to Enable or Disable.
///
/// \param  tun16Percent_1_328 unTgtVal
///
/// \return void
//-----------------------------------------------------------------------------
void IoHwAbUser_SetHss_En1(tun16Percent_1_328 unTgtVal)
{
  if (unTgtVal == IOHWABUSER_MAX_TARGET_VALUE)
  {
    Dio_WriteChannel(IOHWABUSER_DIO_CHANNEL_MAP_HSS_EN_1, TRUE);
  }
  else
  {
    Dio_WriteChannel(IOHWABUSER_DIO_CHANNEL_MAP_HSS_EN_1, FALSE);
  }
}

//-----------------------------------------------------------------------------
/// \brief  API function to set the High Side Switch
///
/// \descr  IoHwAb_User_SetHss_En2() function sets the requested High Side Switch
///         value to Enable or Disable.
///
/// \param  tun16Percent_1_328 unTgtVal
///
/// \return void
//-----------------------------------------------------------------------------
void IoHwAbUser_SetHss_En2(tun16Percent_1_328 unTgtVal)
{
  if (unTgtVal == IOHWABUSER_MAX_TARGET_VALUE)
  {
    Dio_WriteChannel(IOHWABUSER_DIO_CHANNEL_MAP_HSS_EN_2, TRUE);
  }
  else
  {
    Dio_WriteChannel(IOHWABUSER_DIO_CHANNEL_MAP_HSS_EN_2, FALSE);
  }
}

//-----------------------------------------------------------------------------
/// \brief  API function to set the High Side Switch
///
/// \descr  IoHwAb_User_SetHss_En3() function sets the requested High Side Switch
///         value to Enable or Disable.
///
/// \param  tun16Percent_1_328 unTgtVal
///
/// \return void
//-----------------------------------------------------------------------------
void IoHwAbUser_SetHss_En3(tun16Percent_1_328 unTgtVal)
{
  if (unTgtVal == IOHWABUSER_MAX_TARGET_VALUE)
  {
    Dio_WriteChannel(IOHWABUSER_DIO_CHANNEL_MAP_HSS_EN_3, TRUE);
  }
  else
  {
    Dio_WriteChannel(IOHWABUSER_DIO_CHANNEL_MAP_HSS_EN_3, FALSE);
  }
}

//-----------------------------------------------------------------------------
/// \brief  API function to set the High Side Switch
///
/// \descr  IoHwAb_User_SetHss_En3() function sets the Pwm duty cycle
///
/// \param  tun16Percent_1_328 unTgtVal
///
/// \return void
//-----------------------------------------------------------------------------
void IoHwAbUser_SetTgtHss3(tun16Percent_1_328 unTgtVal)
{
  uint16 unDuty = 0u;

  if (unTgtVal > IOHWABUSER_MAX_TARGET_VALUE)
  {
    unDuty = IOHWABUSER_MAX_TARGET_VALUE;
  }
  else
  {
    unDuty = unTgtVal;
  }

  Pwm_SetDutyCycle(IOHWABUSER_PWM_CHANNEL_MAP_HSS_EN_3, unDuty);
}

//-----------------------------------------------------------------------------
/// \brief  API function to set the Fault Reset
///
/// \descr  IoHwAbUser_SetHss_Error() function sets the requested Fault Reset
///         value to Enable or Disable.
///
/// \param  boolean boSettingValue
///
/// \return void
//-----------------------------------------------------------------------------
void IoHwAbUser_SetHss_Error(boolean boSettingValue)
{
  // Set the fault reset
  Dio_WriteChannel(IOHWABUSER_DIO_CHANNEL_MAP_HSS_ERROR, boSettingValue);
}

//-----------------------------------------------------------------------------
/// \brief  API function to set the Hss Sel1
///
/// \descr  IoHwAb_User_SetHss_Sel1() function sets the requested SEL0
///         value to Enable or Disable.
///
/// \param  boolean boSettingValue
///
/// \return void
//-----------------------------------------------------------------------------
void IoHwAbUser_SetHss_Sel1(boolean boSettingValue)
{
  // Set the SEL0
  Dio_WriteChannel(IOHWABUSER_DIO_CHANNEL_MAP_HSS_SEL_1, boSettingValue);
}

//-----------------------------------------------------------------------------
/// \brief  API function to set the Hss Sel2
///
/// \descr  IoHwAbUser_SetHss_Sel2() function sets the requested SEL1
///         value to Enable or Disable.
///
/// \param  boolean boSettingValue
///
/// \return void
//-----------------------------------------------------------------------------
void IoHwAbUser_SetHss_Sel2(boolean boSettingValue)
{
  // Set the SEL1
  Dio_WriteChannel(IOHWABUSER_DIO_CHANNEL_MAP_HSS_SEL_2, boSettingValue);
}
#endif

//-----------------------------------------------------------------------------
/// \brief  API function to set the Hss Sen
///
/// \descr  IoHwAb_User_SetHss_Sen() function sets the requested HSS SEN
///         value to Enable or Disable.
///
/// \param  boolean boSettingValue
///
/// \return void
//-----------------------------------------------------------------------------
void IoHwAbUser_SetHss_Sen(boolean boSettingValue)
{
  // Set the Sen
  Dio_WriteChannel(IOHWABUSER_DIO_CHANNEL_MAP_HSS_SEN, boSettingValue);
}

//-----------------------------------------------------------------------------
/// \brief  API function to Reset the High Side Switch
///
/// \descr  The IoHwAb_User_ResetHss() function sets the reset value of the requested
///         High Side Switch.
///
/// \param  boolean boReset
///
/// \return void
//-----------------------------------------------------------------------------
void IoHwAbUser_ResetHss(boolean boSettingValue)
{
  // No Reset handling for HSS.A310
  boSettingValue = (boolean)boSettingValue;
}

//-----------------------------------------------------------------------------
/// \brief  API function to Enable or Disable Sense of the High Side Switch
///
/// \descr  IoHwAb_User_SenseEnableHss() function sets the Sense value of the requested
///         High Side Switch.
///
/// \param  boolean boSetting
///
/// \return void
//-----------------------------------------------------------------------------
void IoHwAbUser_SenseEnableHss(boolean boSettingValue)
{
  // Enable or Disable Sense of the High Side Switch
  Dio_WriteChannel(IOHWABUSER_DIO_CHANNEL_MAP_HSS_SEN, boSettingValue);
}

//-----------------------------------------------------------------------------
/// \brief API function to read the PCB voltage from ECU
///
/// \descr IoHwAb_User_Get_PCB()
///
/// \param  boolean boValue
///
///
/// \return void
//-----------------------------------------------------------------------------
void IoHwAbUser_Get_PCB(void)
{
  uint16 unReadAdcRawPCB = 0u;

  // Get the PCB raw value
  (void)Adc_ReadGroup(IOHWABUSER_ADC_CHANNEL_MAP_ADC_PCB_TEMP, &unReadAdcRawPCB);
  // Get the filter value of PCB
  Order1Filter(&IoHwAbUser_slPCB_Filter, (sint16)unReadAdcRawPCB, IoHwAbUser_unFilterCoefPCB);
  //Calculate voltage of PCB
  IoHwAbUser_ulPCB = (((tiu16Voltage_mV)Order1FilterValue(&IoHwAbUser_slPCB_Filter) * IoHwAbUser_unFactorPCB) / IOHWABUSER_RESOLUTION_12BIT);

  (void)Rte_Write_IoHwAb_GetPCB(&IoHwAbUser_ulPCB);
}


//-----------------------------------------------------------------------------
/// \brief API function to read the VCCX1 voltage
///
/// \descr IoHwAbUser_Read_VCCX1()
///
/// \param  -
///
///
/// \return tiu16Voltage_mV
//-----------------------------------------------------------------------------
tiu16Voltage_mV IoHwAbUser_Read_VCCX1(void)
{
  uint16 unReadAdcRawVCCX1 = 0u;

  // Get the VCCX1 raw value
  (void)Adc_ReadGroup(IOHWABUSER_ADC_GROUP_CHANNEL_MAP_ADC_VCCX1, &unReadAdcRawVCCX1);
  // Get the filter value of VCCX1
  Order1Filter(&IoHwAbUser_slVCCX1_Filter, (sint16)unReadAdcRawVCCX1, IoHwAbUser_unFilterCoefVCCX1);
  //Calculate voltage of VCCX1
  IoHwAbUser_ulVCCX1 = (((tiu16Voltage_mV)Order1FilterValue(&IoHwAbUser_slVCCX1_Filter) * IoHwAbUser_unFactorVCCX1) / IOHWABUSER_RESOLUTION_12BIT);

  (void)Rte_Write_IoHwAb_VCCX1Voltage(&IoHwAbUser_ulVCCX1);
  return IoHwAbUser_ulVCCX1;
}

#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
//-----------------------------------------------------------------------------
/// \brief API function to set the direction pin of the LWR Stepper driver
///
/// \descr IoHwAb_User_SetDirLwr()
///
/// \param  boolean boValue
///
///
/// \return void
//-----------------------------------------------------------------------------
void IoHwAbUser_SetDirLwr(boolean boSettingValue)
{
  // Set the direction pin of the LWR Stepper driver
  Dio_WriteChannel(IOHWABUSER_DIO_CHANNEL_MAP_DIR_LWR, boSettingValue);
}

//-----------------------------------------------------------------------------
/// \brief API function to set the sleep pin of the LWR Stepper driver
///
/// \descr IoHwAbUser_SetLwrSleep()
///
/// \param  boolean boValue
///
///
/// \return void
//-----------------------------------------------------------------------------
void IoHwAbUser_SetLwrSleep(boolean boSettingValue)
{
  // Set the sleep pin of the LWR Stepper driver
  Dio_WriteChannel(IOHWABUSER_DIO_CHANNEL_MAP_ST_SLEEP, boSettingValue);
}

//-----------------------------------------------------------------------------
/// \brief API function to set the driver off pin of the LWR Stepper driver
///
/// \descr IoHwAb_User_SetLwrDrvOff()
///
/// \param  boolean boValue
///
///
/// \return void
//-----------------------------------------------------------------------------
void IoHwAbUser_SetLwrDrvOff(boolean boSettingValue)
{
  // Set the driver off pin of the LWR Stepper driver
  Dio_WriteChannel(IOHWABUSER_DIO_CHANNEL_MAP_ST_DRVOFF, boSettingValue);
}

//-----------------------------------------------------------------------------
/// \brief API function to set the driver off pin of the LWR Stepper driver
///
/// \descr IoHwAb_User_SetVccxEn()
///
/// \param  boolean boValue
///
///
/// \return void
//-----------------------------------------------------------------------------
void IoHwAbUser_SetVccxEn(boolean boSettingValue)
{
  // Set the Vccx pin of the matrice
  Dio_WriteChannel(IOHWABUSER_DIO_CHANNEL_MAP_VCCX_EN, boSettingValue);
}

//-----------------------------------------------------------------------------
/// \brief  IoHwAb_User_Set_Vccx_State
///
/// \descr  Function that sets Vccx ON or OFF
///
/// \param  boVccx_desiredState
///         -TRUE- Turn Vccx ON
///         -FALSE- Turn Vccx OFF
///
/// \return
//-----------------------------------------------------------------------------
void IoHwAbUser_Set_Vccx_State(boolean boVccx_desiredState)
{
  // enable 5V =  SWR LDM.SYRS.32305

  //Set VCCX 5V
  if (boVccx_desiredState != FALSE)
  {

    if ((IoHwAbUser_ulVBatMean > IOHWAB_USER_VCCX2_VBAT_MIN_VAL) && (IoHwAbUser_ulVBatMean < IOHWAB_USER_VCCX2_VBAT_MAX_VAL))
    {
      //Turn Vccx ON
      IoHwAbUser_SetVccxEn(TRUE);

      //Set Vccx flag to TRUE
      IoHwAbUser_boVccxStatus = TRUE;
    }
    else
    {
      //Turn Vccx ON
      IoHwAbUser_SetVccxEn(FALSE);
      //Set Vccx flag to FALSE
      IoHwAbUser_boVccxStatus = FALSE;
    }
  }

  //disable 5V =  SWR LDM.SYRS.32305
  //Set VCCX 0V
  else
  {
    //Turn Vccx OFF
    IoHwAbUser_SetVccxEn(FALSE);

    //Set Vccx flag to FALSE
    IoHwAbUser_boVccxStatus = FALSE;
  }
}


//-----------------------------------------------------------------------------
/// \brief  IoHwAbUser_VccxStateCyclicCheck
///
/// \descr  Cyclic Vccx function
///         Ranges of Vccx voltages are checked
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void IoHwAbUser_VccxStateCyclicCheck(void)
{
  // PG level
  Dio_LevelType VCCX2_level = STD_HIGH;

  //Vccx voltage
  tiu32Voltage_mV ulA_U_VCCX_mV = 0u;

  // VCCX2_EN_STATE
  STATIC_UT(boolean, boVccx2_en_state, FALSE);
  STATIC_UT(uint32, ulVccx2_Diag_Timer, 0u);
  boolean boVccxDiag_Active_Status = FALSE;

  uint16 unAdcResult = 0u;

  //Enum used to signal errors
  teRte_VccxLineState eVccxLineState;

  if ((IoHwAbUser_boVccxStatus != FALSE) && (boVccx2_en_state == FALSE))
  {
    boVccx2_en_state = TRUE;
    ulVccx2_Diag_Timer = TimerStart(UTILTIME_MSEC(5u));
  }
  else if ((IoHwAbUser_boVccxStatus == FALSE) && (boVccx2_en_state != FALSE))
  {
    boVccx2_en_state = FALSE;
  }
  else if((IoHwAbUser_boVccxStatus != FALSE) && (boVccx2_en_state != FALSE))
  {
    if (TimerTimeout(ulVccx2_Diag_Timer) != FALSE)
    {
      boVccxDiag_Active_Status = TRUE;
    }
    else
    {
      // keep boVccxDiag_Active_Status = FALSE
    }
  }
  else
  {
    // keep boVccxDiag_Active_Status = FALSE
  }


  // Diag Active?
  if (boVccxDiag_Active_Status != FALSE)
  {

#if (CFG_DEV_HOOK_EN == 1u)
    if (VCCXErrors_ulTesterHookActivation == IOHWABUSER_HOOK_KEY)
    {
      VCCX2_level = ulVccx_PG_Level;
    }
    else
    {
      // Read PG
      VCCX2_level = Dio_ReadChannel(IOHWABUSER_DIO_CHANNEL_MAP_VCCX2_PG);
    }
#else
    // Read PG
    VCCX2_level = Dio_ReadChannel(IOHWABUSER_DIO_CHANNEL_MAP_VCCX2_PG);
#endif

    // Is there PG failure
    if (VCCX2_level == STD_LOW)
    {
      // Get the actual voltage value from the Adc Port
      (void)Adc_ReadGroup(IOHWABUSER_ADC_GROUP_CHANNEL_MAP_ADC_VCCX2, &unAdcResult);

#if (CFG_DEV_HOOK_EN == 1u) 
      if (VCCXErrors_ulTesterHookActivation == IOHWABUSER_HOOK_KEY)
      {
        ulA_U_VCCX_mV = ulVccx_mV_TestValue;
      }
      else
      {
        ulA_U_VCCX_mV = ((uint32)(unAdcResult) * (uint32)(IoHwAbUser_unFactorVCCX2)) / IOHWABUSER_RESOLUTION_12BIT;
      }

#else

      ulA_U_VCCX_mV = ((uint32)(unAdcResult) * (uint32)(IoHwAbUser_unFactorVCCX2)) / IOHWABUSER_RESOLUTION_12BIT;

#endif

      // SWRS LDM.SYRS.32300 : The SW shall detect Short-to-GND:	EXT_IF_VCCX_2< 0,25V
   //Checking Short to GND limit
      if (ulA_U_VCCX_mV < IOHWABUSER_VCCX_SHORTTOGND_A_U_VCCX_MV)
      {
        //Set short to ground error
        eVccxLineState = eVccx_Short2GND;
      }

      // SWRS LDM.SYRS.32298 : The SW shall detect Short-to-VBAT:	EXT_IF_VCCX_2 > 5,5V
     //Checking Short to VBAT limit
      else if (ulA_U_VCCX_mV > IOHWABUSER_VCCX_SHORTTOVBAT_A_U_VCCX_MV)
      {
        //Set short to battery error
        eVccxLineState = eVccx_Short2Vbat;
      }
      //Report no error on Vccx line
      else
      {
         // Undeterminate - never will enter here
      }
    }
    else
    {
      eVccxLineState = eVccx_noError;
    }

    IoHwAbUser_ReportVccx2Error((teIoHwAb_VccxLineState)(eVccxLineState)); // PRQA S 4322 // Cast is needed - Rte port type could not be parameter type for a function

  }
  else
  {
    // do nothing VCCX2 is not activated
    eVccxLineState = eVccx_noError;
  }

  //Write RTE port for CtrlPxl
  (void)Rte_Write_IoHwAbUser_VccxLineState(&eVccxLineState);

}

//-----------------------------------------------------------------------------
/// \brief IoHwAbUser_ReportVccx2Error
///
/// \descr Set or clear the specific DTC for short to vbat/short to ground for vccx2
///
/// \param  eVccx1ErrorState: Status of the error
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void IoHwAbUser_ReportVccx2Error(teIoHwAb_VccxLineState eVccx1ErrorState)
{
  switch (eVccx1ErrorState)
  {
  case eIoHwAb_Vccx_Short2Vbat:
    // Set VCCX2_SC_BAT
    Rte_Call_DemPrj_ReportErrorStatus((uint16)VCCX2_SC_BAT, DEM_EVENT_STATUS_FAILED);
    break;
  case eIoHwAb_Vccx_Short2GND:
    // Set VCCX2_SC_GND
    Rte_Call_DemPrj_ReportErrorStatus((uint16)VCCX2_SC_GND, DEM_EVENT_STATUS_FAILED);
    break;
  case eIoHwAb_Vccx_noError:
    // Clear VCCX2_SC_GND
    Rte_Call_DemPrj_ReportErrorStatus((uint16)VCCX2_SC_GND, DEM_EVENT_STATUS_PASSED);
    // Clear VCCX2_SC_BAT
    Rte_Call_DemPrj_ReportErrorStatus((uint16)VCCX2_SC_BAT, DEM_EVENT_STATUS_PASSED);
    break;
  default:
    break;
  }
}
#endif

//-----------------------------------------------------------------------------
/// \brief IoHwAbUserTimer0Notification
///
/// \descr Used for populate buffer element for adc raw value of vbat
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void IoHwAbUserTimer0Notification(void)
{
  uint16 ulReadAdcRawVBAT = 0u;

  // Set the element variable to zero when it exceeds 31
  if (IoHwAbUser_ucRingBuffElem >= IOHWABUSER_RINGBUFFER_SIZE)
  {
    IoHwAbUser_ucRingBuffElem = 0u;
  }
  // Get the Adc Raw Value of VBat and save it in the Ring Buffer
  (void)Adc_ReadGroup(IOHWABUSER_ADC_GROUP_CHANNEL_MAP_ADC_VBAT, &ulReadAdcRawVBAT);

  IoHwAbUser_aulRingBuff[IoHwAbUser_ucRingBuffElem] = ulReadAdcRawVBAT;
  IoHwAbUser_ucRingBuffElem++;
}


//-----------------------------------------------------------------------------
/// \brief
///
/// \descr IoHwAbUser_CalcVBatMeanValue function calculates the mean value of VBat
///
/// \param  - void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void IoHwAbUser_CalcVBatMeanValue(void)
{
  uint8  ucIndex           = 0u;
  uint32 ulMeanAdcRawVBAT  = 0u;

  for(ucIndex = 0U; ucIndex < IOHWABUSER_RINGBUFFER_SIZE; ucIndex++)
  {
    // Sum all values from buffer
    ulMeanAdcRawVBAT += IoHwAbUser_aulRingBuff[ucIndex];
  }

  ulMeanAdcRawVBAT = ulMeanAdcRawVBAT / IOHWABUSER_RINGBUFFER_SIZE;

  // Calculate the mean voltage value and send it to the RTE
  IoHwAbUser_ulVBatMean = (uint32)((ulMeanAdcRawVBAT * IoHwAbUser_unFactorVBAT) / IOHWABUSER_RESOLUTION_12BIT);

  (void)Rte_Write_IoHwAb_User_GetAdc_DIAG_VBAT(&IoHwAbUser_ulVBatMean);
}


//-----------------------------------------------------------------------------
/// \brief Function calculates ADC Value of High Side Switch for High ECU
///
/// \descr IoHwAb_User_HSSOperationForEcuHighVar function calculates the mean value of HSS sensor
///
/// \param  - void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void IoHwAbUser_HSSOperationForEcuHighVar(void)
{
  uint32 ulReadAdcRawHSSSenseS1_2 = 0u;
#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
  uint32 ulReadAdcRawHSSSenseS3 = 0u;
#endif

  if (IoHwAbUser_sHssDioInfo.boDioSel0Toggle == FALSE)
  {
    // Get the raw value of the filter value of HSS1_2 Sensor
    ulReadAdcRawHSSSenseS1_2 = (uint32)Order1FilterValue(&IoHwAbUser_slHssSenseS1_2_Filter);

    // Get the value for voltage for double channel high-side switch 1_2
    IoHwAbUser_aulHSSSensorVoltage[IOHWABUSER_HSSSENSE_0] = ulReadAdcRawHSSSenseS1_2 * IoHwAbUser_unFactorHssSenseS1_2 / IOHWABUSER_RESOLUTION_12BIT;

#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
    Dio_WriteChannel(IOHWABUSER_DIO_CHANNEL_MAP_HSS_SEL_1, TRUE);
#endif
    IoHwAbUser_sHssDioInfo.boDioSel0Toggle = TRUE;
  }
  else
  {
    // Get the raw value of the filter value of HSS1_2 Sensor
    ulReadAdcRawHSSSenseS1_2 = (uint32)Order1FilterValue(&IoHwAbUser_slHssSenseS1_2_Filter);
    // Get the value for voltage for double channel high-side switch 1_2
    IoHwAbUser_aulHSSSensorVoltage[IOHWABUSER_HSSSENSE_1] = ulReadAdcRawHSSSenseS1_2 * IoHwAbUser_unFactorHssSenseS1_2 / IOHWABUSER_RESOLUTION_12BIT;

#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
    Dio_WriteChannel(IOHWABUSER_DIO_CHANNEL_MAP_HSS_SEL_1, FALSE);
#endif
    IoHwAbUser_sHssDioInfo.boDioSel0Toggle = FALSE;
  }

#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
  // Get the raw value of the filter value of HSS3 Sensor
  ulReadAdcRawHSSSenseS3 = (uint32)Order1FilterValue(&IoHwAbUser_slHssSenseS3_Filter);

  // Get the value for voltage for high-side switch 3
  IoHwAbUser_aulHSSSensorVoltage[IOHWABUSER_HSSSENSE_2] = ulReadAdcRawHSSSenseS3 * IoHwAbUser_unFactorHssSense3 / IOHWABUSER_RESOLUTION_12BIT;
#endif
}


//-----------------------------------------------------------------------------
/// \brief Function initialize all buffers
///
/// \descr IoHwAbUser_InitializeBuffers
///
/// \param  - void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void IoHwAbUser_InitializeBuffers(void)
{
  uint16 unResult = 0u;

  // Get the actual voltage value from the Adc Port and initialize the Ring Buffer with this value
  (void)Adc_ReadGroup(IOHWABUSER_ADC_GROUP_CHANNEL_MAP_ADC_VBAT, &unResult);

  // Fill the voltage ring buffer with the stored AdcRaw VBAT values
  for (uint8 ucIdx = 0U; ucIdx < IOHWABUSER_RINGBUFFER_SIZE; ucIdx++)
  {
    IoHwAbUser_aulRingBuff[ucIdx] = unResult;
  }

  // Calculate the mean voltage value and send it to the RTE
  IoHwAbUser_ulVBatMean = (uint32)(((uint32)unResult * IoHwAbUser_unFactorVBAT) / IOHWABUSER_RESOLUTION_12BIT);
  //
  (void)Rte_Write_IoHwAb_User_GetAdc_DIAG_VBAT(&IoHwAbUser_ulVBatMean);
}

//-----------------------------------------------------------------------------
/// \brief Function which return IoHwAbUser_GetVoltage
///
/// \descr IoHwAbUser_GetVoltage of index
///
/// \param  - ucIdx
///
/// \return tiu16Voltage_mV
//-----------------------------------------------------------------------------
tiu16Voltage_mV IoHwAbUser_GetVoltage_NTCs(uint8 ucIdx)
{
  tiu16Voltage_mV unReturn = 0u;

  if (ucIdx < IOHWABUSER_CFG_MAX_NO_OF_EXT_NTCS)
  {
    unReturn = IoHwAbUser_aunNTCVoltage[ucIdx];
  }
  else
  {
    unReturn = 0xFFFFU;
  }

  return unReturn;
}


//-----------------------------------------------------------------------------
/// \brief Function makes the initialization of filters
///
/// \descr IoHwAbUser_FilterInitialization
///
/// \param  - void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void IoHwAbUser_FilterInitialization(void)
{
  uint16 ulReadAdcRawHSSSenseS1_2 = 0u;
  uint16 unReadAdcRawHSSSenseS3 = 0u;
  uint16 unReadAdcRawPCBNTC = 0u;
  uint16 unReadAdcRawVCCX1= 0u;
  uint16 unReadAdcRawNTC[IOHWABUSER_CFG_MAX_NO_OF_EXT_NTCS] = { 0u };

  // Get the filter coefficient of HSS filter
  IoHwAbUser_unFilterCoefHssSenseS1_2 = Order1FilterGetCoef(IOHWABUSER_USAMPLIMGTIME_1, IOHWABUSER_UFILTERTIME_HSS);
  IoHwAbUser_unFilterCoefHssSenseS3 = Order1FilterGetCoef(IOHWABUSER_USAMPLIMGTIME_1, IOHWABUSER_UFILTERTIME_HSS3);

  // Get the Raw value of Hss Adc raw values
  (void)Adc_ReadGroup(IOHWABUSER_ADC_GROUP_CHANNEL_MAP_ADC_HSS_SENSE_1_2, &ulReadAdcRawHSSSenseS1_2);

#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
  (void)Adc_ReadGroup(IOHWABUSER_ADC_GROUP_CHANNEL_MAP_ADC_HSS_SENSE_3, &unReadAdcRawHSSSenseS3);

#endif

  // Initialize the HSS filter
  Order1FilterInit(&IoHwAbUser_slHssSenseS1_2_Filter, (sint16)ulReadAdcRawHSSSenseS1_2);
  Order1FilterInit(&IoHwAbUser_slHssSenseS3_Filter, (sint16)unReadAdcRawHSSSenseS3);

  //Initialize PCB Temp Filter
  IoHwAbUser_unFilterCoefPCB = Order1FilterGetCoef(IOHWABUSER_USAMPLIMGTIME_100, IOHWABUSER_UFILTERTIME_TEMP);

  (void)Adc_ReadGroup(IOHWABUSER_ADC_CHANNEL_MAP_ADC_PCB_TEMP, &unReadAdcRawPCBNTC);
  Order1FilterInit(&IoHwAbUser_slPCB_Filter, (sint16)unReadAdcRawPCBNTC);

  //Initialize VCCX1 Temp Filter
  IoHwAbUser_unFilterCoefVCCX1 = Order1FilterGetCoef(IOHWABUSER_USAMPLIMGTIME_1, IOHWABUSER_UFILTERTIME_VCCX1);

  (void)Adc_ReadGroup(IOHWABUSER_ADC_CHANNEL_MAP_ADC_PCB_TEMP, &unReadAdcRawVCCX1);
  Order1FilterInit(&IoHwAbUser_slVCCX1_Filter, (sint16)unReadAdcRawVCCX1);

  //Initialize Ext NTC Filter
  IoHwAbUser_unFilterCoefNTC = Order1FilterGetCoef(IOHWABUSER_USAMPLIMGTIME_100, IOHWABUSER_UFILTERTIME_TEMP);

  for (uint8 ucIdx = 0U; ucIdx < IOHWABUSER_CFG_MAX_NO_OF_EXT_NTCS; ucIdx++)
  {
    // Get the Adc Raw data for NTC
    (void)Adc_ReadGroup(IoHwAb_aucAdc_EXT_Channel_Map[ucIdx], &unReadAdcRawNTC[ucIdx]);

    // Initialized the filter of correspondent NTC
    Order1FilterInit(&IoHwAbUser_aslNTC_Filter[ucIdx], (sint16)unReadAdcRawNTC[ucIdx]);
  }
}

//-----------------------------------------------------------------------------
/// \brief Function gets diag value
///
/// \descr IoHwAbUser_GetHss0Sense sets the diagnose value for HSS output 1
///        to be read by CddVnd7140 and CddVn7140
///
/// \param  - uint32* unDiagVal
///
/// \return void
//-----------------------------------------------------------------------------
void IoHwAbUser_GetHss0Sense(uint32* unDiagVal)
{
  *unDiagVal = IoHwAbUser_aulHSSSensorVoltage[IOHWABUSER_HSSSENSE_0];
}

//-----------------------------------------------------------------------------
/// \brief Function gets diag value
///
/// \descr IoHwAbUser_GetHss1Sense sets the diagnose value for HSS output 2
///        to be read by CddVnd7140
///
/// \param  - uint32* unDiagVal
///
/// \return void
//-----------------------------------------------------------------------------
void IoHwAbUser_GetHss1Sense(uint32* unDiagVal)
{
  *unDiagVal = IoHwAbUser_aulHSSSensorVoltage[IOHWABUSER_HSSSENSE_1];
}

//-----------------------------------------------------------------------------
/// \brief Function gets diag value
///
/// \descr IoHwAbUser_GetHss2Sense sets the diagnose value for HSS output 3
///        to be read by CddVn7140
///
/// \param  - uint32* unDiagVal
///
/// \return void
//-----------------------------------------------------------------------------
void IoHwAbUser_GetHss2Sense(uint32* unDiagVal)
{
  *unDiagVal = IoHwAbUser_aulHSSSensorVoltage[IOHWABUSER_HSSSENSE_2];
}

//-----------------------------------------------------------------------------
/// \brief Function which gets the adc raw value for each NTC
///
/// \descr IoHwAbUser_GetVoltage_NTC
///
/// \param  - uint32* unDiagVal
///
/// \return void
//-----------------------------------------------------------------------------
void IoHwAbUser_GetVoltage_NTC(void)
{
  uint16 aunReadAdcRawNTC[IOHWABUSER_CFG_MAX_NO_OF_EXT_NTCS] = { 0u };
  tsRte_Voltage_mV stData = { 0u };

  for (uint8 ucIdx = 0u; ucIdx < IOHWABUSER_CFG_MAX_NO_OF_EXT_NTCS; ucIdx++)
  {
    // Get the Adc Raw data
    (void)Adc_ReadGroup(IoHwAb_aucAdc_EXT_Channel_Map[ucIdx], &aunReadAdcRawNTC[ucIdx]);
    // Get the filter value of correspondent NTC
    Order1Filter(&IoHwAbUser_aslNTC_Filter[ucIdx], (sint16)aunReadAdcRawNTC[ucIdx], IoHwAbUser_unFilterCoefNTC);
    // Calculate the voltage value of of correspondent NTC
    IoHwAbUser_aunNTCVoltage[ucIdx] = ((tiu16Voltage_mV)Order1FilterValue(&IoHwAbUser_aslNTC_Filter[ucIdx])) *  IoHwAbUser_unFactorNTC[ucIdx] / IOHWABUSER_RESOLUTION_12BIT;
    stData.aunNtcVoltage[ucIdx] = IoHwAbUser_aunNTCVoltage[ucIdx];
  }
  (void)Rte_Write_IoHwAb_GetVoltage_NTCs(&stData);
}

//-----------------------------------------------------------------------------
/// \brief Function which return IoHwAbUser_GetVoltage_EXT1
///
/// \descr IoHwAbUser_GetVoltage_EXT1
///
/// \param  - void
///
/// \return tiu16Voltage_mV
//-----------------------------------------------------------------------------
tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT1(void)
{
  return IoHwAbUser_aunNTCVoltage[0u];
}

//-----------------------------------------------------------------------------
/// \brief Function which return IoHwAbUser_GetVoltage_EXT2
///
/// \descr IoHwAbUser_GetVoltage_EXT2
///
/// \param  - void
///
/// \return tiu16Voltage_mV
//-----------------------------------------------------------------------------
tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT2(void)
{
  return IoHwAbUser_aunNTCVoltage[1u];
}

//-----------------------------------------------------------------------------
/// \brief Function which return IoHwAbUser_GetVoltage_EXT3
///
/// \descr IoHwAbUser_GetVoltage_EXT3
///
/// \param  - void
///
/// \return tiu16Voltage_mV
//-----------------------------------------------------------------------------
tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT3(void)
{
  return IoHwAbUser_aunNTCVoltage[2u];
}

//-----------------------------------------------------------------------------
/// \brief Function which return IoHwAbUser_GetVoltage_EXT4
///
/// \descr IoHwAbUser_GetVoltage_EXT4
///
/// \param  - void
///
/// \return tiu16Voltage_mV
//-----------------------------------------------------------------------------
tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT4(void)
{
  return IoHwAbUser_aunNTCVoltage[3u];
}

//-----------------------------------------------------------------------------
/// \brief Function which return IoHwAbUser_GetVoltage_EXT5
///
/// \descr IoHwAbUser_GetVoltage_EXT5
///
/// \param  - void
///
/// \return tiu16Voltage_mV
//-----------------------------------------------------------------------------
tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT5(void)
{
  return IoHwAbUser_aunNTCVoltage[4u];
}

//-----------------------------------------------------------------------------
/// \brief Function which return IoHwAbUser_GetVoltage_EXT6
///
/// \descr IoHwAbUser_GetVoltage_EXT6
///
/// \param  - void
///
/// \return tiu16Voltage_mV
//-----------------------------------------------------------------------------
tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT6(void)
{
  return IoHwAbUser_aunNTCVoltage[5u];
}

//-----------------------------------------------------------------------------
/// \brief Function which return IoHwAbUser_GetVoltage_EXT7
///
/// \descr IoHwAbUser_GetVoltage_EXT7
///
/// \param  - void
///
/// \return tiu16Voltage_mV
//-----------------------------------------------------------------------------
tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT7(void)
{
  return IoHwAbUser_aunNTCVoltage[6u];
}

//-----------------------------------------------------------------------------
/// \brief Function which return IoHwAbUser_GetVoltage_EXT8
///
/// \descr IoHwAbUser_GetVoltage_EXT8
///
/// \param  - void
///
/// \return tiu16Voltage_mV
//-----------------------------------------------------------------------------
tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT8(void)
{
  return IoHwAbUser_aunNTCVoltage[7u];
}

//-----------------------------------------------------------------------------
/// \brief Function which return IoHwAbUser_GetVoltage_EXT9
///
/// \descr IoHwAbUser_GetVoltage_EXT7
///
/// \param  - void
///
/// \return tiu16Voltage_mV
//-----------------------------------------------------------------------------
tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT9(void)
{
  return IoHwAbUser_aunNTCVoltage[8u];
}

//-----------------------------------------------------------------------------
/// \brief Function which return IoHwAbUser_GetVoltage_EXT10
///
/// \descr IoHwAbUser_GetVoltage_EXT10
///
/// \param  - void
///
/// \return tiu16Voltage_mV
//-----------------------------------------------------------------------------
tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT10(void)
{
  return IoHwAbUser_aunNTCVoltage[9u];
}

#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
//-----------------------------------------------------------------------------
/// \brief Function which return IoHwAbUser_GetVoltage_EXT11
///
/// \descr IoHwAbUser_GetVoltage_EXT11
///
/// \param  - void
///
/// \return tiu16Voltage_mV
//-----------------------------------------------------------------------------
tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT11(void)
{
  return IoHwAbUser_aunNTCVoltage[10u];
}

//-----------------------------------------------------------------------------
/// \brief Function which return IoHwAbUser_GetVoltage_EXT12
///
/// \descr IoHwAbUser_GetVoltage_EXT12
///
/// \param  - void
///
/// \return tiu16Voltage_mV
//-----------------------------------------------------------------------------
tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT12(void)
{
  return IoHwAbUser_aunNTCVoltage[11u];
}

//-----------------------------------------------------------------------------
/// \brief Function which return IoHwAbUser_GetVoltage_EXT13
///
/// \descr IoHwAbUser_GetVoltage_EXT13
///
/// \param  - void
///
/// \return tiu16Voltage_mV
//-----------------------------------------------------------------------------
tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT13(void)
{
  return IoHwAbUser_aunNTCVoltage[12u];
}

//-----------------------------------------------------------------------------
/// \brief Function which return IoHwAbUser_GetVoltage_EXT14
///
/// \descr IoHwAbUser_GetVoltage_EXT14
///
/// \param  - void
///
/// \return tiu16Voltage_mV
//-----------------------------------------------------------------------------
tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT14(void)
{
  return IoHwAbUser_aunNTCVoltage[13u];
}

#endif

//-----------------------------------------------------------------------------
/// \brief  Get filtered raw value of analog height sensor inputs
///
/// \descr  Get value in 16 bit raw format
///         Use digital P-T1 filter value
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void IoHwAbUser_GetSens_Raw(void)
{
  tsRte_SensorRaw aunSensRawValue;
  for (uint8 ucIx = 0u; ucIx < CFG_CntSens; ucIx++)
  {
    aunSensRawValue.aucSensRaw[ucIx] = IoHwAbUser_unSensCalculatedDuty[ucIx];
  }
  (void)Rte_Write_IoHwAb_GetSens_Raw(&aunSensRawValue); // send signal quality
}

//-----------------------------------------------------------------------------
/// \brief  Get filtered balanced value of analog height sensor inputs
///
/// \descr  Due to zero level programming the output range can be
///         +- raw value
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void IoHwAbUser_GetSens_Balanced(void)
{
  STATIC_AL sint32    slNvMDeltaPwm[2] = { 0, 0 }; // static used for debugging
  STATIC_AL uint16    unActualPwm[2] = { 0u, 0u }; // static used for debugging
  tsRte_SensorBalance alSensValue;

  //  // Get Nvm Data
  slNvMDeltaPwm[0] = NvmBlockDeltaPwmPara.slDeltaPwm_0;
  slNvMDeltaPwm[1] = NvmBlockDeltaPwmPara.slDeltaPwm_1;

  for (uint8 ucIx = 0u; ucIx < CFG_CntSens; ucIx++)
  {
    unActualPwm[ucIx] = IoHwAbUser_unSensCalculatedDuty[ucIx];

    if ((unActualPwm[ucIx] < IOHWABUSER_MAX_PWM) && (unActualPwm[ucIx] > 0u))
    {
      IoHwAbUser_aslSensPwmTarget[ucIx] = (sint32)unActualPwm[ucIx] + slNvMDeltaPwm[ucIx]; // PWM(target)=PWM(actual)+delta(PWM)

     if (IoHwAbUser_aslSensPwmTarget[ucIx] > IOHWABUSER_MAX_VAL_DUTY_RANGE) // >90% = 58982
     {
       IoHwAbUser_aslSensPwmTarget[ucIx] = (IoHwAbUser_aslSensPwmTarget[ucIx] - IOHWABUSER_ADJ_DUTY_PERCENT);    // 80%=52428 ==>PWM(target)=PWM(actual)-80%
     }
     else if (IoHwAbUser_aslSensPwmTarget[ucIx] < IOHWABUSER_MIN_VAL_DUTY_RANGE) // <10%=6554
     {
       IoHwAbUser_aslSensPwmTarget[ucIx] = (IoHwAbUser_aslSensPwmTarget[ucIx] + IOHWABUSER_ADJ_DUTY_PERCENT); // 80%=52428 ==>PWM(target)=PWM(actual)+80%
     }
     else
     {
     //do noting
     }
    }
    else
    {
      //do nothing
    }
    alSensValue.alSensBalance[ucIx] = (IoHwAbUser_aslSensPwmTarget[ucIx] - IOHWABUSER_PWMTARGET_OFFSET);//PRQA S 1820
  }

  (void)Rte_Write_IoHwAb_GetSens_Balanced(&alSensValue);
}//PRQA S 5336  // STMIF = 5


//-----------------------------------------------------------------------------
/// \brief  IoHwAbUser_CalcInputPwmSens
///
/// \descr  Read Period or Duty Cycle in counts from Icu 
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void IoHwAbUser_CalcInputPwmSens(void)
{
  STATIC_UT(uint16, unSensPeriodPwm0_Err, IOHWABUSER_DEFAULT_ERR_PERIOD);
  STATIC_UT(uint16, unSensPeriodPwm1_Err, IOHWABUSER_DEFAULT_ERR_PERIOD);

  //backup preview period 
  uint16 unSensPeriodPwm0 = IoHwAbUser_unSensMeasPeriodAndDuty[CFG_SENS_PWM0][IOHWABUSER_MEAS_MODE_PERIOD];
  uint16 unSensPeriodPwm1 = IoHwAbUser_unSensMeasPeriodAndDuty[CFG_SENS_PWM1][IOHWABUSER_MEAS_MODE_PERIOD];

  // Read sensor measurements - period or duty cycle
  IoHwAbUser_unSensMeasPeriodAndDuty[CFG_SENS_PWM0][IoHwAbUser_ucMeasMode] = Icu_GetMeasurementSens(CFG_SENS_PWM0);
  IoHwAbUser_unSensMeasPeriodAndDuty[CFG_SENS_PWM1][IoHwAbUser_ucMeasMode] = Icu_GetMeasurementSens(CFG_SENS_PWM1);

  if(IoHwAbUser_ucMeasMode == IOHWABUSER_MEAS_MODE_PERIOD)
  {
    if ( (IoHwAbUser_unSensMeasPeriodAndDuty[CFG_SENS_PWM0][IOHWABUSER_MEAS_MODE_PERIOD] < 4500u) || (IoHwAbUser_unSensMeasPeriodAndDuty[CFG_SENS_PWM0][IOHWABUSER_MEAS_MODE_PERIOD] > 5500u))
    {
      unSensPeriodPwm0_Err = IoHwAbUser_unSensMeasPeriodAndDuty[CFG_SENS_PWM0][IOHWABUSER_MEAS_MODE_PERIOD];
      //overwrite with the backup
      IoHwAbUser_unSensMeasPeriodAndDuty[CFG_SENS_PWM0][IOHWABUSER_MEAS_MODE_PERIOD] = unSensPeriodPwm0;
    }
    else
    {
      //reset error period
      unSensPeriodPwm0_Err = IOHWABUSER_DEFAULT_ERR_PERIOD;
      //keep new calculated period
    }
    if ((IoHwAbUser_unSensMeasPeriodAndDuty[CFG_SENS_PWM1][IOHWABUSER_MEAS_MODE_PERIOD] < 4500u) || (IoHwAbUser_unSensMeasPeriodAndDuty[CFG_SENS_PWM1][IOHWABUSER_MEAS_MODE_PERIOD] > 5500u))
    {
      unSensPeriodPwm1_Err = IoHwAbUser_unSensMeasPeriodAndDuty[CFG_SENS_PWM1][IOHWABUSER_MEAS_MODE_PERIOD];
      //overwrite with the backup
      IoHwAbUser_unSensMeasPeriodAndDuty[CFG_SENS_PWM1][IOHWABUSER_MEAS_MODE_PERIOD] = unSensPeriodPwm1;
    }
    else
    {
      //reset error period
      unSensPeriodPwm1_Err = IOHWABUSER_DEFAULT_ERR_PERIOD;
      //keep new calculated period
    }
  }

  // Convert to internal % format 0%..100% = 0x0 .. 0xFFFF
  IoHwAbUser_unSensCalculatedDuty[CFG_SENS_PWM0] = (uint16)(((uint32)IoHwAbUser_unSensMeasPeriodAndDuty[CFG_SENS_PWM0][IOHWABUSER_MEAS_MODE_DUTY] * 0xFFFFU) / IoHwAbUser_unSensMeasPeriodAndDuty[CFG_SENS_PWM0][IOHWABUSER_MEAS_MODE_PERIOD]);
  IoHwAbUser_unSensCalculatedDuty[CFG_SENS_PWM1] = (uint16)(((uint32)IoHwAbUser_unSensMeasPeriodAndDuty[CFG_SENS_PWM1][IOHWABUSER_MEAS_MODE_DUTY] * 0xFFFFU) / IoHwAbUser_unSensMeasPeriodAndDuty[CFG_SENS_PWM1][IOHWABUSER_MEAS_MODE_PERIOD]);

  // Check if Duty Cycle exceeds 95% - an error is present
  if (IoHwAbUser_unSensMeasPeriodAndDuty[CFG_SENS_PWM0][IOHWABUSER_MEAS_MODE_DUTY] > (unSensPeriodPwm0_Err - IOHWABUSER_ERR_PERIOD_OFFSET))
  {
    IoHwAbUser_unSensCalculatedDuty[CFG_SENS_PWM0] = (IoHwAbUser_CheckSens0_OpenLoad() != FALSE) ? 0xFFFFu : 0x0000u;
  }
  else
  {
    // do nothing
  }

  if (IoHwAbUser_unSensMeasPeriodAndDuty[CFG_SENS_PWM1][IOHWABUSER_MEAS_MODE_DUTY] > (unSensPeriodPwm1_Err - IOHWABUSER_ERR_PERIOD_OFFSET))
  {
    IoHwAbUser_unSensCalculatedDuty[CFG_SENS_PWM1] = (IoHwAbUser_CheckSens1_OpenLoad() != FALSE) ? 0xFFFFu : 0x0000u;
  }
  else
  {
    // do nothing
  }

  //let this change at the end in order to use ucMeasMode for collecting correctly the preaview measurement type
  if((IoHwAbUser_ucMeasCycle % 10U) == 0U ) // every 10th cycle we will be changed the measurement to period
  {
    IoHwAbUser_ucMeasMode = IOHWABUSER_MEAS_MODE_PERIOD;
    IoHwAbUser_ucMeasCycle = 0u;
  }
  else
  {
    IoHwAbUser_ucMeasMode = IOHWABUSER_MEAS_MODE_DUTY;
  }

  // Set NVM error flags
  IoHwAbUser_SetNvm_ElecError(CFG_SENS_PWM0);
  IoHwAbUser_SetNvm_ElecError(CFG_SENS_PWM1);

  // Set measurement mode
  Icu_ChangeMeasurementMode(CFG_SENS_PWM0, IoHwAbUser_ucMeasMode);
  Icu_ChangeMeasurementMode(CFG_SENS_PWM1, IoHwAbUser_ucMeasMode);

  IoHwAbUser_ucMeasCycle++;
}


//-----------------------------------------------------------------------------
/// \brief  IoHwAbUser_SetNvm_ElecError
///
/// \descr  Set Nvm Flag for HLS electrical errors based on previos state and duty cycle
///
/// \param  void
///
/// \return uint8
//-----------------------------------------------------------------------------
STATIC_AL void IoHwAbUser_SetNvm_ElecError(uint8 ucSensIdx)
{
#define IOHWABUSER_DEF_ERROR_INIT_STATE { eIoHwAb_Hls_noError, eIoHwAb_Hls_noError }
#define IOHWABUSER_DEF_TIMER_INIT_VAL   { FALSE, FALSE }

  STATIC_UT(uint32,            ulDebounceTimer[CFG_CntSens],  { 0u });
  STATIC_UT(boolean,           boStartTimer[CFG_CntSens],     IOHWABUSER_DEF_TIMER_INIT_VAL);
  STATIC_UT(teIoHwAb_HlsState, eSensShGndNew[CFG_CntSens],    IOHWABUSER_DEF_ERROR_INIT_STATE);
  STATIC_UT(teIoHwAb_HlsState, eSensShVbatNew[CFG_CntSens],   IOHWABUSER_DEF_ERROR_INIT_STATE);

  // Check sensor Sh2Vbat error state
  if (IoHwAbUser_unSensCalculatedDuty[ucSensIdx] > IOHWABSUSER_5_PERCENT_PWM && IoHwAbUser_unSensCalculatedDuty[ucSensIdx] < IOHWABSUSER_95_PERCENT_PWM)
  {
    eSensShVbatNew[ucSensIdx] = eIoHwAb_Hls_noError;
    boStartTimer[ucSensIdx] = FALSE;
  }
  else if (NvmBlockDeltaPwmPara.ucSensVbatError[ucSensIdx] == 1u || (IoHwAbUser_unSensCalculatedDuty[ucSensIdx] >= IOHWABSUSER_95_PERCENT_PWM && NvmBlockDeltaPwmPara.ucSensGndError[ucSensIdx] != 1u))
  {
    if (boStartTimer[ucSensIdx] == FALSE)
    {
      ulDebounceTimer[ucSensIdx] = TimerGetTick();
      boStartTimer[ucSensIdx] = TRUE;
    }
    else if (TimerGetTimeSince(ulDebounceTimer[ucSensIdx]) >= UTILTIME_MSEC(2000u))
    {
      //set the error only after 2 seconds
      eSensShVbatNew[ucSensIdx] = eIoHwAb_Hls_Error;
    }
    else
    {
      //go on check next time
    }
  }
  else
  {
    // do nothing
  }

  // Check sensor Sh2Gnd error state
  if (IoHwAbUser_unSensCalculatedDuty[ucSensIdx] > IOHWABSUSER_5_PERCENT_PWM && IoHwAbUser_unSensCalculatedDuty[ucSensIdx] < IOHWABSUSER_95_PERCENT_PWM)
  {
    eSensShGndNew[ucSensIdx] = eIoHwAb_Hls_noError;
    boStartTimer[ucSensIdx] = FALSE;
  }
  else if (NvmBlockDeltaPwmPara.ucSensGndError[ucSensIdx] == 1u || (IoHwAbUser_unSensCalculatedDuty[ucSensIdx] <= IOHWABSUSER_5_PERCENT_PWM  && NvmBlockDeltaPwmPara.ucSensVbatError[ucSensIdx] != 1u))
  {
    if (boStartTimer[ucSensIdx] == FALSE)
    {
      ulDebounceTimer[ucSensIdx]= TimerGetTick();
      boStartTimer[ucSensIdx] = TRUE;
    }
    else if (TimerGetTimeSince(ulDebounceTimer[ucSensIdx]) >= UTILTIME_MSEC(2000u))
    {
      //set the error only after 2 seconds
      eSensShGndNew[ucSensIdx] = eIoHwAb_Hls_Error;
    }
    else
    {
      //go on check next time
    }
  }
  else
  {
    // do nothing
  }

  // Check if error state has changed
  if (((NvmBlockDeltaPwmPara.ucSensVbatError[ucSensIdx] != (uint8)eSensShVbatNew[ucSensIdx])) ||
    ((NvmBlockDeltaPwmPara.ucSensGndError[ucSensIdx] != (uint8)eSensShGndNew[ucSensIdx])))
  {
    // Write new values
    NvmBlockDeltaPwmPara.ucSensVbatError[ucSensIdx] = (uint8)eSensShVbatNew[ucSensIdx];
    NvmBlockDeltaPwmPara.ucSensGndError[ucSensIdx] = (uint8)eSensShGndNew[ucSensIdx];

    (void)NvM_WriteBlock((NvM_BlockIdType)NvmBlockDeltaPwmParaId, (void*)&NvmBlockDeltaPwmPara);
  }
  else
  {
    // do nothing
  }
}


//-----------------------------------------------------------------------------
/// \brief  IoHwAbUser_CheckSens0_OpenLoad
///
/// \descr  Check CHOV bit of Channel 0 Status And Control register to confirm
///         if Bhs sensor 0 is on high or low edge
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean IoHwAbUser_CheckSens0_OpenLoad(void)
{
#if defined(UNIT_TEST)
  uint32 Mt_IoHwAbuser_FTM0[2] = { 0,0 };
  uint32 Mt_IoHwAbuser_CHOV_BitStatus = 0;

  Mt_IoHwAbuser_GetFTM0RegisterValues(Mt_IoHwAbuser_FTM0);

  return ((Mt_IoHwAbuser_FTM0[0] & Mt_IoHwAbuser_FTM0[1]) != 0u) ? TRUE : FALSE;
#else
  // PRQA S 306 1 // Cast needed for microcontroller registers access
  return ((*(uint32*)IOHWABUSER_FTM0_CHOV & IOHWABUSER_CHOV_BITSTATUS) != 0u) ? TRUE : FALSE;
#endif
}

//-----------------------------------------------------------------------------
/// \brief  IoHwAbUser_CheckSens1_OpenLoad
///
/// \descr  Check CHOV bit of Channel 0 Status And Control register to confirm
///         if Bhs sensor 0 is on high or low edge
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean IoHwAbUser_CheckSens1_OpenLoad(void)
{
#if defined(UNIT_TEST)
  uint32 Mt_IoHwAbuser_FTM4[2] = {0,0};
  uint32 Mt_IoHwAbuser_CHOV_BitStatus = 0;

  Mt_IoHwAbuser_GetFTM4RegisterValues(Mt_IoHwAbuser_FTM4);

  return ((Mt_IoHwAbuser_FTM4[0] & Mt_IoHwAbuser_FTM4[1]) != 0u) ? TRUE : FALSE;
#else
  // PRQA S 306 1 // Cast needed for microcontroller registers access
  return ((*(uint32*)IOHWABUSER_FTM4_CHOV & IOHWABUSER_CHOV_BITSTATUS) != 0u) ? TRUE : FALSE;
#endif
}


// EOF

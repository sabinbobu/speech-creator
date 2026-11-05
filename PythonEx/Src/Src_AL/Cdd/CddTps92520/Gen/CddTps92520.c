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
/// \file   CddTps92520.c
///
/// \brief  Specific code for TPS92520 hardware
///
/// \author OTT, Peter ALDE-RT/EES6
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
// standard includes
#include <Std_Types.h>
#include <AL_Helper.h>

// module API (include path)
#include <CddTps92520.h>

// module includes (relative to API)
#include <../Cfg/CddTps92520_Cfg.h>
#include <../Cfg/CddTps92520_RoutCfg.h>
#include <../Gen/CddTps92520_Com.h>
#include <../Gen/CddTps92520_Types.h>


//-----------------------------------------------------------------------------
// Start definitions of non initialized structures and unions or arrays variables
//-----------------------------------------------------------------------------
#define CDDTPS92520_VoltageSna   65535u  // internally used if voltage is unavailable


//-----------------------------------------------------------------------------
// Start definitions of non initialized structures and unions or arrays variables
//-----------------------------------------------------------------------------
#define ctadCddLed_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <../Cfg/CddTps92520_MemMap.h>

STATIC_AL uint16  CddTps92520_aunTgtDutyCycle[CDDTPS92520_CFG_NO_OF_CHANNELS];  // target duty cycle
STATIC_AL uint16  CddTps92520_aunTgtCurrent  [CDDTPS92520_CFG_NO_OF_CHANNELS];  // target current
STATIC_AL boolean CddTps92520_aboMultiLed    [CDDTPS92520_CFG_NO_OF_CHANNELS];  // indication of string with at least 2 LEDs

STATIC_AL uint16 CddTps92520_aunInputVoltage [CDDTPS92520_CFG_NO_OF_CHANNELS];  // buck input (typ. booster) voltage
STATIC_AL uint16 CddTps92520_aunLedVoltage   [CDDTPS92520_CFG_NO_OF_CHANNELS];  // LED string voltage

// function static variables, need to be defined in file for MPU usage
STATIC_AL boolean CddTps92520_aboEnable              [CDDTPS92520_CFG_NO_OF_CHANNELS];  // storage to keep state of BUCK_EN bits
STATIC_AL boolean CddTps92520_aboDriverActiveStatus  [CDDTPS92520_CFG_NO_OF_CHANNELS];  // storage to keep state of COMPOV bit
STATIC_AL boolean CddTps92520_aboOpenLoadStatus      [CDDTPS92520_CFG_NO_OF_CHANNELS];  // storage to keep state of OpenLoad state
STATIC_AL boolean CddTps92520_aboShortToGndStatus    [CDDTPS92520_CFG_NO_OF_CHANNELS];  // storage to keep state of ShortToGnd state
STATIC_AL boolean CddTps92520_aboOvercurrentStatus   [CDDTPS92520_CFG_NO_OF_CHANNELS];  // storage to keep state of HSILIM/LSILIM bits
STATIC_AL boolean CddTps92520_aboThermalShtDwnStatus [CDDTPS92520_CFG_NO_OF_CHANNELS];  // storage to keep state of TP bit
STATIC_AL boolean CddTps92520_aboThermalWarningStatus[CDDTPS92520_CFG_NO_OF_CHANNELS];  // storage to keep state of TW bit

#define ctadCddLed_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <../Cfg/CddTps92520_MemMap.h>
//-----------------------------------------------------------------------------
// End definitions of non initialized structures and unions or arrays variables
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Start declaration or definitions of functions
//-----------------------------------------------------------------------------
#define ctadCddLed_START_SEC_CODE
#include <../Cfg/CddTps92520_MemMap.h>


//-----------------------------------------------------------------------------
// Local function prototypes
//-----------------------------------------------------------------------------
STATIC_AL uint16 CddTps92520_RawToMillivolt     (const uint32 ulRaw);
STATIC_AL void   CddTps92520_MeasureInputVoltage(void);
STATIC_AL void   CddTps92520_MeasureLedVoltage  (void);
STATIC_AL uint16 CddTps92520_CalcCHxIADJ        (const uint32 ulChnIdx, const uint16 unCurrent);


//-----------------------------------------------------------------------------
// Function definitions
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
/// \brief  Conversion factor ADC raw value to mV
///
/// \descr  From data sheet:   U[mV] = RegisterValue *    64610 / 255
///         SW representation: U[mV] = RegisterValue * 16605023 / 65536
///
/// \param  uint32 ulRaw : raw ADC value multiplied by CDDTPS92520_AdcSamples
///
/// \return STATIC_AL uint16 voltage in mV
//-----------------------------------------------------------------------------
STATIC_AL uint16 CddTps92520_RawToMillivolt(const uint32 ulRaw)
{
  #define ADC_FACTOR   16605024u  // increment by 1 to avoid truncation by division
  #define SCALE_FACTOR    65536u

  uint32 ulProduct = ulRaw * (ADC_FACTOR / CDDTPS92520_AdcSamples);

  return (uint16)(ulProduct / SCALE_FACTOR);  // return value is definitely smaller than uint16 size
}


//-----------------------------------------------------------------------------
/// \brief  Measure input voltage on all channels 
///
/// \descr  Get the last recieved CHxVIN from Data Mirror
///         Do filtering and convert the raw value to mV
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddTps92520_MeasureInputVoltage(void)
{
  for (uint32 ul = 0u; ul < CDDTPS92520_CFG_NO_OF_CHANNELS; ul++)
  {
    CddTps92520_aunInputVoltage[ul] = CddTps92520_RawToMillivolt(CddTps92520_GetCHxVIN(ul));
  }
}


//-----------------------------------------------------------------------------
/// \brief  Measure LED voltage on all channels
///
/// \descr  Read the last recieved CHxVLEDON or CHxVLED from Data Mirror
///         depending on DutyCycle
///         Limitations are given for Dutycycle <5%.
///         Convert the ADC raw value in to mV.
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddTps92520_MeasureLedVoltage(void)
{
  for (uint32 ul = 0u; ul < CDDTPS92520_CFG_NO_OF_CHANNELS; ul++)
  {
    if ( (CddTps92520_aunTgtDutyCycle[ul] == CDDTPS92520_DutyCycle_0 )
      || (CddTps92520_aunTgtDutyCycle[ul] >  CDDTPS92520_ContHiThresh) )
    {
      CddTps92520_aunLedVoltage[ul] = CddTps92520_RawToMillivolt(CddTps92520_GetCHxVLED(ul));    // read VLED if ((DutyCycle = 0) || (DutyCycle > 99.9%))
    }
    else if (CddTps92520_aunTgtDutyCycle[ul] >= CDDTPS92520_MinDutyVledOn)
    {
      CddTps92520_aunLedVoltage[ul] = CddTps92520_RawToMillivolt(CddTps92520_GetCHxVLEDON(ul));  // read VLEDON else
    }
    else
    {
      CddTps92520_aunLedVoltage[ul] = CDDTPS92520_VoltageSna;     // voltage value not available
    }
  }
}


//-----------------------------------------------------------------------------
/// \brief  calculate device register values for LED current
///
/// \descr
///
/// \param  ulChnIdx
/// \param  unCurrent
///
/// \return uint16
//-----------------------------------------------------------------------------
STATIC_AL uint16 CddTps92520_CalcCHxIADJ(const uint32 ulChnIdx, const uint16 unCurrent)
{
  const uint32 ulDevice  = ulChnIdx / CDDTPS92520_NbOfChannel;
  const uint32 ulChannel = ulChnIdx % CDDTPS92520_NbOfChannel;

  // get EFT data
  const uint16 unIFactor = CDDTPS92520_CALIB_unIFactor (ulDevice, ulChannel);
  const sint16 snIOffset = CDDTPS92520_CALIB_nIOffset  (ulDevice, ulChannel);
  const uint16 unImax    = CDDTPS92520_ECUVARCFG_unImax(ulDevice, ulChannel);

  uint32 ulCHxIADJ;   // storage for return value
  sint32 lCurrent;    // signed storage because of possibly negative intermediate results

  lCurrent = (sint32)((unCurrent > unImax) ? unImax : unCurrent);  // limit to EFT data threshold

  lCurrent = (10 * lCurrent) + snIOffset;    // convert current to [0.1mA] and add calibration offset 

  lCurrent = (lCurrent < 0) ? 0 : lCurrent;  // avoid negative result for ulCHxIADJ

  ulCHxIADJ = ((uint32)lCurrent * unIFactor) / 65536u;  // multiply calibration factor
  // note: compiler will optimize division by shift operation

  //Limit to 0<= ChxIADJ <= 1023
  if (ulCHxIADJ > CDDTPS92520_CHxIADJ_Max)
  {
    ulCHxIADJ = CDDTPS92520_CHxIADJ_Max;
  }

  return (uint16)ulCHxIADJ;
}


//-----------------------------------------------------------------------------
/// \brief  Read LED duty cycle
///
/// \descr  get value of LED duty cycle based on response from IoHwAb
///
/// \param  uint32 ulChnIdx : Channel Index
///
/// \return uint16 : LED duty cycle
//-----------------------------------------------------------------------------
uint16  CddTps92520_GetDutyCycle_1_32768(const uint32 ulChnIdx)
{
  uint16 unRetVal = 0u;

  if (ulChnIdx < CDDTPS92520_CFG_NO_OF_CHANNELS)
  {
    unRetVal = CDDTPS92520_GetLedChannelPwm_1_32768(ulChnIdx);
  }

  return unRetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Read LED current
///
/// \descr  get value of LED current based on reception of unCHxIADJy
///
/// \param  uint32 ulChnIdx : Channel Index
///
/// \return uint16 : LED current
//-----------------------------------------------------------------------------
uint16  CddTps92520_GetCurrent_mA(const uint32 ulChnIdx)
{
  uint16 unRetVal = 0u;

  if (ulChnIdx < CDDTPS92520_CFG_NO_OF_CHANNELS)
  {
    // TODO: read unCHxIADJy --> backward calculation
    // CddTps92520_GetCHxIADJL  (const uint32 ulChnIdx, uint8* pucCHxIADJL);
    // CddTps92520_GetCHxIADJH  (const uint32 ulChnIdx, uint8* pucCHxIADJL);

    unRetVal = CddTps92520_aunTgtCurrent[ulChnIdx];
  }

  return unRetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Driver initialization
///
/// \descr  Initialize driver variables and check EFT data
///
/// \param  -
///
/// \return uint32 - bit mask indicating available channels
///                  Bit0 - Channel 0, Bit1 - channel 1...
//-----------------------------------------------------------------------------
uint32 CddTps92520_Init(void) 
{
  uint32 ulRet = 0u;

  if (CDDTPS92520_EftDataValid() != FALSE)
  {
    for (uint32 ulDev = 0u; ulDev < CDDTPS92520_Cfg_NbOfDevices; ulDev++)
    {
      for (uint32 ulChn = 0u; ulChn < CDDTPS92520_NbOfChannel; ulChn++)
      {
        uint32 ulMask = (uint32)1u << ((2u * ulDev) + ulChn);

        // check if channel is available (do not check output assignment yet, no requirement yet)
        if (CDDTPS92520_ECUVARCFG_ucAssignedOutput(ulDev, ulChn) != 0u)
        {
          ulRet |= ulMask;
        }
      }
    }
  }

  return ulRet;
}


//-----------------------------------------------------------------------------
/// \brief  Cyclic call for sampling driver status
///
/// \descr  Read voltages and status bits from buck driver
///         Do filtering and calculations on driver voltages
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
void CddTps92520_Cycle20ms(void)
{
  CddTps92520_MeasureInputVoltage();
  CddTps92520_MeasureLedVoltage  ();
}


//-----------------------------------------------------------------------------
/// \brief  Set the PWM duty cycle
///
/// \descr  sets duty cycle of LED_CTRL signals
///         Additionally, in case of single LED, handle also CHxEN
///
/// \param  uint32 ulChnIdx
///         uint16 unDuty
///
/// \return void
//-----------------------------------------------------------------------------
void CddTps92520_SetDutyCycle_1_32768(const uint32 ulChnIdx, const uint16 unDuty)
{
  if (ulChnIdx < CDDTPS92520_CFG_NO_OF_CHANNELS)
  {
    uint8 ucTon = CDDTPS92520_Cfg_CHxTON_HiFreq;  // high frequency for better resolution

    // if LED is operated at PWM >= 5%
    if (CddTps92520_aunTgtDutyCycle[ulChnIdx] >= CDDTPS92520_MinDutyVledOn)
    {
      ucTon = CDDTPS92520_Cfg_CHxTON_LoFreq;      // low frequency for high efficiency

      if (unDuty == 0u)    // check if a LED is switched off
      {
        CddTps92520_aboMultiLed[ulChnIdx] = (CddTps92520_aunLedVoltage[ulChnIdx] > CDDTPS92520_VoltSingleLed) ? TRUE : FALSE;
      }
    }

    CddTps92520_SetCHxTON(ulChnIdx, ucTon);  // set TON according to actual PWM

    CddTps92520_aunTgtDutyCycle[ulChnIdx] = unDuty;  // remember for diagnostic purposes

    if (CDDTPS92520_EftDataValid() != FALSE)  // end of line data available
    {
      CDDTPS92520_SetLedChannelPwm_1_32768(ulChnIdx, unDuty);

      if (unDuty > 0u)
      {
        CddTps92520_aboEnable[ulChnIdx] = TRUE;     // activate corresonding channel by BUCK_EN
      }
      else
      {
        if (CddTps92520_aboMultiLed[ulChnIdx] == FALSE)  // TODO if only 1 LED is connected
        {
          CddTps92520_aboEnable[ulChnIdx] = FALSE;  // deactivate corresonding channel by BUCK_EN
        }
      }

      CddTps92520_EnableChannel(ulChnIdx, CddTps92520_aboEnable[ulChnIdx]);
    }
  }
}


//-----------------------------------------------------------------------------
/// \brief  set current on LED channel
///
/// \descr
///
/// \param  ulChnIdx
/// \param  unCurrent
///
/// \return void
//-----------------------------------------------------------------------------
void CddTps92520_SetCurrent_mA(const uint32 ulChnIdx, const uint16 unCurrent)
{
  uint16 unCHxIADJ = 0u;
  tCddTps92520_CHxIADJL unCHxIADJL;

  if (ulChnIdx < CDDTPS92520_CFG_NO_OF_CHANNELS)
  {
    CddTps92520_aunTgtCurrent[ulChnIdx] = unCurrent;

    unCHxIADJ = CddTps92520_CalcCHxIADJ(ulChnIdx, unCurrent);

    unCHxIADJL.Bit.bi2CHxIADJ = unCHxIADJ & CDDTPS92520_CHxIADJL_CHxIADJ_BIT_MASK;
    unCHxIADJ = (unCHxIADJ >> 2u) & 0x00FFu;  //get CHxIADJ[9:2] to be set in CHxIADJH
    CddTps92520_SetCHxIADJL(ulChnIdx, unCHxIADJL);
    CddTps92520_SetCHxIADJH(ulChnIdx, (uint8) unCHxIADJ);
  }
}


//-----------------------------------------------------------------------------
/// \brief  Get the buck input voltage value in mV
///
/// \descr  This is typically the booster voltage of the corresponding channel
///
/// \param  ulChnIdx
///
/// \return uint16
//-----------------------------------------------------------------------------
uint16 CddTps92520_GetInputVoltage_mV(const uint32 ulChnIdx)
{
  uint16 unRetVal = 0u;

  if (ulChnIdx < CDDTPS92520_CFG_NO_OF_CHANNELS)
  {
    unRetVal = CddTps92520_aunInputVoltage[ulChnIdx];
  }

  return unRetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Get the LED voltage value in mV
///
/// \descr  LED voltage measured by driver
///         If 0 < TargetDuty < 5% then voltage cannot be measured
///
/// \param  ulChnIdx   : channel index
///         punVoltage : ponter to storage of LED voltage
///
/// \return boolean    : FALSE if voltage cannot be measured
//-----------------------------------------------------------------------------
boolean CddTps92520_GetLedVoltage_mV(const uint32 ulChnIdx, uint16* punVoltage)
{
  boolean boRetVal = FALSE;

  if ((ulChnIdx < CDDTPS92520_CFG_NO_OF_CHANNELS) && (punVoltage != NULL_PTR))
  {
    *punVoltage =  CddTps92520_aunLedVoltage[ulChnIdx];
    boRetVal    = (CddTps92520_aunLedVoltage[ulChnIdx] != CDDTPS92520_VoltageSna) ? TRUE : FALSE;
  }

  return boRetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Get the CHxCOMPOV bit to check if current regulator is in operation
///
/// \descr  returns TRUE if (CHxCOMPOV == 0)
///
/// \param  ulChnIdx
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CddTps92520_IsDriverActive(const uint32 ulChnIdx)
{
  boolean boRetVal = FALSE;
  tCddTps92520_STATUS1 STATUS1;

  if (ulChnIdx < CDDTPS92520_CFG_NO_OF_CHANNELS)
  {
    boolean boIsValid = CddTps92520_GetSTATUS1(ulChnIdx, &STATUS1);

    // discard RX data in case of SPI error, return value keeps unchanged
    if (boIsValid != FALSE)
    {
      uint32 ulChannel = ulChnIdx % CDDTPS92520_NbOfChannel;
      uint32 ulVLed    = CddTps92520_aunLedVoltage[ulChnIdx];  // needed for PWM < 5% only

      if (ulVLed != CDDTPS92520_VoltageSna) // PWM >= 5%
      {
        if (ulChannel == 0u)
        {
          CddTps92520_aboDriverActiveStatus[ulChnIdx] = (STATUS1.Bit.biCH1COMPOV == 0u) ? TRUE : FALSE;
        }
        else
        {
          CddTps92520_aboDriverActiveStatus[ulChnIdx] = (STATUS1.Bit.biCH2COMPOV == 0u) ? TRUE : FALSE;
        }
      }
      else
      {
        CddTps92520_aboDriverActiveStatus[ulChnIdx] = TRUE;
      }
    }

    boRetVal = CddTps92520_aboDriverActiveStatus[ulChnIdx];
  }

  return boRetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Get the Open Load status bit
///
/// \descr  returns TRUE if LED output is open
///
/// \param  ulChnIdx
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CddTps92520_IsOpenLoad(const uint32 ulChnIdx)
{
  boolean boRetVal = FALSE;
  tCddTps92520_STATUS1 STATUS1;

  if (ulChnIdx < CDDTPS92520_CFG_NO_OF_CHANNELS)
  {
    boolean boIsValid = CddTps92520_GetSTATUS1(ulChnIdx, &STATUS1);

    // discard RX data in case of SPI error, return value keeps unchanged
    if (boIsValid != FALSE)
    {
      uint32 ulChannel     = ulChnIdx % CDDTPS92520_NbOfChannel;
      uint32 ulVIn         = CddTps92520_aunInputVoltage[ulChnIdx];
      uint32 ulVLed        = CddTps92520_aunLedVoltage[ulChnIdx];
      uint32 ulVInVLedDiff = (ulVIn > ulVLed) ? (ulVIn - ulVLed) : 0u;  // avoid underflow

      if (ulVLed != CDDTPS92520_VoltageSna) // PWM >= 5%
      {
        // now check 1st condition for open load
        if (ulChannel == 0u)
        {
          CddTps92520_aboOpenLoadStatus[ulChnIdx] = (STATUS1.Bit.biCH1COMPOV == 0u) ? FALSE : TRUE;
        }
        else
        {
          CddTps92520_aboOpenLoadStatus[ulChnIdx] = (STATUS1.Bit.biCH2COMPOV == 0u) ? FALSE : TRUE;
        }

        if (ulVInVLedDiff <= CDDTPS92520_OpenLoadDiff)     // 2nd condition to detect open load
        {
          CddTps92520_aboOpenLoadStatus[ulChnIdx] = TRUE;  // overwrite previous result in this case
        }
      }
      else
      {
        CddTps92520_aboOpenLoadStatus[ulChnIdx] = FALSE;
      }
    }

    boRetVal = CddTps92520_aboOpenLoadStatus[ulChnIdx];
  }

  return boRetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Get the Short to Gnd Status
///
/// \descr  returns TRUE if LED output is shorted to GND
///
/// \param  ulChnIdx
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CddTps92520_IsShortToGnd(const uint32 ulChnIdx)
{
  boolean boRetVal = FALSE;
  tCddTps92520_STATUS1 STATUS1;

  if (ulChnIdx < CDDTPS92520_CFG_NO_OF_CHANNELS)
  {
    boolean boIsValid = CddTps92520_GetSTATUS1(ulChnIdx, &STATUS1);

    // discard RX data in case of SPI error, return value keeps unchanged
    if (boIsValid != FALSE)
    {
      uint32 ulChannel = ulChnIdx % CDDTPS92520_NbOfChannel;
      uint32 ulVLed    = CddTps92520_aunLedVoltage[ulChnIdx];

      if (ulVLed != CDDTPS92520_VoltageSna) // PWM >= 5%
      {
        if (ulChannel == 0u)
        {
          CddTps92520_aboShortToGndStatus[ulChnIdx] = (STATUS1.Bit.biCH1SHORT == 0u) ? FALSE : TRUE;
        }
        else
        {
          CddTps92520_aboShortToGndStatus[ulChnIdx] = (STATUS1.Bit.biCH2SHORT == 0u) ? FALSE : TRUE;
        }

        if (ulVLed >= CDDTPS92520_ShortGndThresh)      // 2nd condition: do not detect open load if LED voltage is above threshold
        {
          CddTps92520_aboShortToGndStatus[ulChnIdx] = FALSE;  // overwrite previous result in this case
        }
      }
      else
      {
        CddTps92520_aboShortToGndStatus[ulChnIdx] = FALSE;  // voltage measurement impossible
      }
    }

    boRetVal = CddTps92520_aboShortToGndStatus[ulChnIdx];
  }

  return boRetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Get the overcurrent status.
///
/// \descr  returns TRUE if either high-side or low-side overcurrent bit is set
///
/// \param  ulChnIdx
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CddTps92520_IsOvercurrent(const uint32 ulChnIdx)
{
  boolean boRetVal = FALSE;
  tCddTps92520_STATUS1 STATUS1;

  if (ulChnIdx < CDDTPS92520_CFG_NO_OF_CHANNELS)
  {
    boolean boIsValid = CddTps92520_GetSTATUS1(ulChnIdx, &STATUS1);

    // discard RX data in case of SPI error, return value keeps unchanged
    if (boIsValid != FALSE)
    {
      uint32 ulChannel = ulChnIdx % CDDTPS92520_NbOfChannel;

      if (ulChannel == 0u)
      {
        // Overcurrent fault set as soon as either high side or low-side overcurrent bit is set
        CddTps92520_aboOvercurrentStatus[ulChnIdx] = ((STATUS1.Bit.biCH1HSILIM == 0u) && (STATUS1.Bit.biCH1LSILIM == 0u)) ? FALSE : TRUE;
      }
      else
      {
        CddTps92520_aboOvercurrentStatus[ulChnIdx] = ((STATUS1.Bit.biCH2HSILIM == 0u) && (STATUS1.Bit.biCH2LSILIM == 0u)) ? FALSE : TRUE;
      }
    }

    boRetVal = CddTps92520_aboOvercurrentStatus[ulChnIdx];
  }

  return boRetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Check for thermal shutdown
///
/// \descr  returns TRUE if corresponding LED driver device is in thermal shutdown state
///
/// \param  uint32 ulChnIdx : Channel Index
///
/// \return boolean : thermal shutdown detected
//-----------------------------------------------------------------------------
boolean CddTps92520_IsThermalShutDown(const uint32 ulChnIdx)
{
  boolean boRetVal = FALSE;
  tCddTps92520_STATUS2 STATUS2;

  if (ulChnIdx < CDDTPS92520_CFG_NO_OF_CHANNELS)
  {
    boolean boIsValid = CddTps92520_GetSTATUS2(ulChnIdx, &STATUS2);

    // discard RX data in case of SPI error, return value keeps unchanged
    if (boIsValid != FALSE)
    {
      uint32 ulChannel = ulChnIdx % CDDTPS92520_NbOfChannel;

      if (ulChannel == 0u)
      {
        // Thermal Shutdown fault set as soon as buck temperature too high
        CddTps92520_aboThermalShtDwnStatus[ulChnIdx] = (STATUS2.Bit.biCH1TP == 0u) ? FALSE : TRUE;
      }
      else
      {
        CddTps92520_aboThermalShtDwnStatus[ulChnIdx] = (STATUS2.Bit.biCH2TP == 0u) ? FALSE : TRUE;
      }
    }

    boRetVal = CddTps92520_aboThermalShtDwnStatus[ulChnIdx];
  }

  return boRetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Check for thermal warning
///
/// \descr  returns TRUE if corresponding LED driver device is in thermal warning state
///
/// \param  uint32 ulChnIdx : Channel Index
///
/// \return boolean : thermal warning detected
//-----------------------------------------------------------------------------
boolean CddTps92520_IsThermalWarning(const uint32 ulChnIdx)
{
  boolean boRetVal = FALSE;
  tCddTps92520_STATUS3 STATUS3;

  if (ulChnIdx < CDDTPS92520_CFG_NO_OF_CHANNELS)
  {
    boolean boIsValid = CddTps92520_GetSTATUS3(ulChnIdx, &STATUS3);

    // discard RX data in case of SPI error, return value keeps unchanged
    if (boIsValid != FALSE)
    {
      // Thermal Warning set as soon as when the junction temperature exceeds the threshold programmed by TWLMT[9:2]
      CddTps92520_aboThermalWarningStatus[ulChnIdx] = (STATUS3.Bit.biTW == 0u) ? FALSE : TRUE;
    }

    boRetVal = CddTps92520_aboThermalWarningStatus[ulChnIdx];
  }

  return boRetVal;
}

//-----------------------------------------------------------------------------
/// \brief  CddTps92520_IsSpiError
///
/// \descr  Provides SPI Error status  
///
/// \param  ulChnIdx: Channel index
///
/// \return boolean
///           TRUE : SPI error occurred from the last call
///           FALSE: SPI error did NOT occurred from the last call
///
//-----------------------------------------------------------------------------
boolean CddTps92520_IsSpiError(const uint32 ulChnIdx)
{
  boolean boRetVal = FALSE;

  if (ulChnIdx < CDDTPS92520_CFG_NO_OF_CHANNELS)
  {
    boRetVal = CddTps92520_GetSpiError(ulChnIdx);
  }

  return boRetVal;
}


#define ctadCddLed_STOP_SEC_CODE
#include <../Cfg/CddTps92520_MemMap.h>
//-----------------------------------------------------------------------------
// End declaration or definitions of functions
//-----------------------------------------------------------------------------

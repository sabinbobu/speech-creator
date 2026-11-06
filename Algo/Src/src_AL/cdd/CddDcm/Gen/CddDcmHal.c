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
/// \file   CddDcmHal.c (HalDcmAlt1.c)
///
/// \brief  Module for controlling the Dc-motor outputs.
///
/// \descr  Alternative1 Dc-motor driver for controlling the Dc-motor output
///         voltage by reading back the output voltage.
///         Additional information can be found in the design description
///
/// \author Heusel Johannes ALRT/EEG-PM2 (F89037A)
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================

#include <Std_Types.h>
#include "ILCU_LevellingAdapter.h" /* ILCU_PORT: replaces DPE-only <Cfg/Cfg.h>, <UtilUtility.h>, <Pwm.h>, <IoHwAbUser.h>, <Rte.h> */

#include <CddDcm_Cfg.h>     // project specific DCM configuration
#include <CddDcmHal.h>
#include <CddDcmCtrl.h>




#undef STATIC
#define STATIC


//=============================================================================
// Local Configuration and debug #define flags
//=============================================================================

// ----------------------------------------------------------------------------
// --------------- Remarks/Notes on the program development -------------------
// ----------------------------------------------------------------------------
//
/// Beschreibung der Variablen im Debug-Modus um die Regelung mit Rdm zu beurteilen:
// --------------------------------------------------------------------------------
/// Dieses Merkmal ist nur moglich wenn beim Compilieren der HALDCM_DEBUG_OUTCTRL_WITH_RDM
/// Schalter in dieser Datei aktiviert worden ist.
///
/// Veranderbare Variablen um den Dc-Motorausgang mit Rdm zu verstellen, unabhangig von der
/// Anwendung (daruber liegende Softwareschicht).
///
/// HalDcm_ucDebugDirectCtrlWithRdm:
/// Wenn diese Variable auf 0 steht (default nach Power Up) dann hat die darueberliegende Ctrl-Sw Ebene
/// CddDcmCtrl.c (IpdDcmMon.c) die Kontrolle uber den Dc-Motorausgang. In dem Fall bewegt sich der
/// Dc-Motor wenn einer der Achssensoren bewegt wird.
/// Wenn diese Variable mit Rdm auf 1 gesetzt wird dann hat Rdm die alleinige Kontrolle uber den
/// Dc-Motorausgang, die Anwendung hat keinen Zugriff mehr auf den Dc-Motorausgang.
/// Mit den folgenden Variablen kann man mit Rdm den Dc-Motorausgang verstellen:
///
/// HalDcm_aucRdmEnablePwmOutput[x]:
/// 0x00: Ausgang deaktivieren und internes PWM Signal ausschalten, keine Regelung.
/// 0x11: Ausgang aktivieren, internes PWM Signal einschalten, Regelung ist aktiv.
/// 0x10: Ausgang deaktivieren, internes PWM Signal ist eingeschaltet, keine Regelung.
/// 0x01: Kein normaler Zustand, Ausgang aktivieren, internes PWM Signal wird
///       wahrscheinlich eingeschaltet sein.
/// Der Arrayindex x steht fur den Dc-Motorausgang DCM0 oder DCM1. Wenn die Software nur
/// fur einen Dc Motorausgang kompiliert worden ist, dann gibt es nur den [0] Index.
///
/// CddDcmHal_unOutputLevel[x]:
/// Hier kann der Sollwert fur die Regelung eingestellt werden als Promillwert von 150 bis 850.
/// Dieser Sollwert entspricht dem Verhaltnis von Kl15 zum Dc-Motorausgang als Promillwert.
/// Mit Rdm kann sogar der normale Arbeitsbereich 150..850 verlassen werden um den Grenzbereich
/// des Hardwarereglers/der Schaltung herauszufinden. Die normale Anwendung wird normalerweise
/// mit Werten von 150..850 arbeiten.
///
// ----------------------------------------------------------------------------------------
/// Die folgenden Variablen sind reine Anzeige-Variablen. Sie dienen nur zum Beobachten
/// des Dc-Motorausgangs mit Rdm. Diese Variablen sollten nicht mit Rdm verstellt werden,
/// dienen nur der Anzeige.
///
/// CddDcmHal_ucEnablePwmOutput[x]:
/// Aktueller Zustand des DC-Motors Enable/Disable Pins und des Pwm outputs.
/// 0x00: Ausgang ist deaktiviert und internes PWM signal ist ausgeschaltet.
/// 0x11: Ausgang ist aktiviert, internes PWM signal ist eingeschaltet.
/// 0x10: Ausgang ist deaktiviert, internes PWM signal ist eingeschaltet.
/// 0x01: Kein normaler Zustand, Ausgang ist aktiviert, internes PWM Signal
///       wird wahrscheinlich eingeschaltet.
///
/// CddDcmHal_unLastPwmSignal[x]:
/// Pwm Tastverhaltnis als Promillwert (0...1000) das aktuell vom uC ausgegeben wird.
///
/// CddDcmHal_ulAverageUdcmValue:
/// Aktuelle Dc-Motorversorgungsspannung (Klemme15) als mV value.
///
/// Aktuell gemessene Dc-Motorausgansspannung in mV.
///
/// CddDcmHal_ulOutputLevel_FB[x]:
/// Den aktuellen Dc-Motorausganslevel Level (Verhaltniss zwischen Kl15 und Dc-Ansteuerspannung)
/// (0...1000). Dieser Wert wird standig nachgeregelt so dass der eingestellte Sollwert-Level
/// von oben (CddDcmHal_unOutputLevel[x]) annahernd oder genau erreicht wird.
/// Wenn der Wert von CddDcmHal_ulOutputLevel_FB[x] auf 0xffff (65535) steht, dann ist die
/// Regelung der Dc-Motorspannung nicht aktiv.


//=============================================================================
// typedefs and defines, macros
//=============================================================================

#define HALDCM_MAX_ALLOWED_PWM_VALUE         ((uint16)1000)

#define HALDCM_MIN_LEVEL_LOW                 ((uint16) 60u)
#define HALDCM_MAX_LEVEL_HIGH                ((uint16)940u)

#define HALDCM_MIN_ALLOWED_SET_LEVEL         ((uint16)(HALDCM_MIN_LEVEL_LOW  + 20u)) 
#define HALDCM_MAX_ALLOWED_SET_LEVEL         ((uint16)(HALDCM_MAX_LEVEL_HIGH - 20u))
#define HALDCM_LEVEL_NOT_KNOWN_VALUE         ((uint16)0xffff)

#define HALDCM_CYCLE_CTRL_TIME_MS            (20u)
#define HALDCM_IRQ_HOOK_FCT_PERIOD_TIME_MS   (5u)
#ifndef UNIT_TEST
#define HALDCM_CYCLE_CTRL_TIME_COUNT         (HALDCM_CYCLE_CTRL_TIME_MS / HALDCM_IRQ_HOOK_FCT_PERIOD_TIME_MS)
#else
#define HALDCM_CYCLE_CTRL_TIME_COUNT         (2u)
#endif


#define HALDCM_THRESHOLD_DIFF_CONTROL        (3u)

// Bit values for the CddDcmHal_ucEnablePwmOutput[] variable
#define    DCM_OUTPUT_ENABLED_BIT_MSK       ((uint8)(0x01))
#define    PWM_SIGNAL_ACTIVE_BIT_MSK        ((uint8)(0x10))

// HALDCM_DIV_VALUE  = A * Uport_H * 1000       = 3,485 * 4,97 * 1000 = 17320,45
#define HALDCM_OPAMP_FACTOR_1_1000 3485u // Gain factor AIC2000 = 3,485 (scaled by 1000)
#define HALDCM_HIGH_LEVEL_mV 4970u // uC port output voltage Uport_High in mV
#define HALDCM_DIV_VALUE ((uint16)(((uint32)HALDCM_OPAMP_FACTOR_1_1000 * HALDCM_HIGH_LEVEL_mV) / 1000u))

// Assignment of the algorythmus for the Pwm output signal calculation/controling for each Dc-motor output.
// _HalDcmChannelLevelCtrlStart_ could be used for controling the output without the Dc-motor read back voltage.
//lint -esym(750,_HalDcmChannelCtrlAlgo0_,_HalDcmChannelCtrlAlgo1_) local macro 'xxx'not referenced

#define HALDCM_DIVIDER_PWM_CALCULATION         (HALDCM_DIV_VALUE)

//=============================================================================
// Global defined data
//=============================================================================


//=============================================================================
// Static/local defined data
//=============================================================================

// Initialised to 0 at start up.
STATIC_AL uint16 CddDcmHal_unOutputLevel;
STATIC_AL uint8  CddDcmHal_ucEnablePwmOutput;

STATIC_AL uint32 CddDcmHal_ulOutputLevel_FB;
STATIC_AL uint16 CddDcmHal_unMotorPwm;
STATIC_AL uint16 CddDcmHal_unLastPwmSignal;
STATIC_AL uint32 CddDcmHal_ulAverageUdcmValue;

//=============================================================================
// Local function prototypes
//=============================================================================

STATIC_AL void            CddDcmHal_SetMotorPwm(const uint16 unPwm);
STATIC_AL uint16          CddDcmHal_CalculatePwm(const uint32 ulOutpLevel, const uint32 ulVoltDcMotor_mV);
STATIC_AL uint16          CddDcmHal_ChannelLevelCtrlStart(void);
STATIC_AL uint16          CddDcmHal_ChannelLevelCtrlOn(void);
STATIC_AL void            CddDcmHal_ActivateChannel(const uint8 ucState);
STATIC_AL void            CddDcmHal_DoOutpPwmControl(void);

STATIC_AL uint16          CddDcm_GetVdcm(void);
STATIC_AL tiu32Voltage_mV CddDcm_GetVbat(void);
STATIC_AL void            CddDcm_OutputEnable(boolean enable);

//=============================================================================
// Function definitions
//=============================================================================
//lint -e661 Possible creation of out-of-bounds pointer


//******************************************************************************
// H E L P E R
//******************************************************************************

/**
* Helper function to enable/disable the DCM output pins
*/
STATIC_AL void CddDcm_OutputEnable(boolean enable)
{
  IoHwAb_User_SetDio_EN_DC((enable != FALSE) ? 1U : 0U);  // Enable DC motor 1
}

/**
* Helper function
* Return the actual DCM output voltage in [mV], 0 if error
*/
STATIC_AL uint16 CddDcm_GetVdcm(void)
{
  uint16 unDiagVdcm = 0U;

  IoHwAbUser_GetAdc_VoltDC_OUT1(&unDiagVdcm);
  return unDiagVdcm;
}

/**
* Helper function
* Return the actual VBAT voltage in [mV]
*/
STATIC_AL tiu32Voltage_mV CddDcm_GetVbat(void)
{
  tiu32Voltage_mV unDiagVbat;
  // Get the actual VBAT (KL15) level
  (void)Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT(&unDiagVbat);
  return unDiagVbat;
}


//-----------------------------------------------------------------------------
/// \brief  UINT16 _HalDcmCalculatePwm_(const UINT32 ulOutpLevel, const UINT32 ulVoltDcMotor_mV)
///         !!Called on interrupt level
///
/// \descr  This routine will calculate the unMotorPwm value from the given
///         OutputLevel und average DC-motor supply voltage.
///
/// \param       ulOutpLevel  Configured voltage level of the Dc-motor output as promille value
/// \param  ulVoltDcMotor_mV  Dc-motor supply voltage as mV value.
///
/// \return UINT16 Calculated Pwm (duty cycle) promille value
//-----------------------------------------------------------------------------
STATIC_AL uint16 CddDcmHal_CalculatePwm(const uint32 ulOutpLevel, const uint32 ulVoltDcMotor_mV)
{
  uint16 unCalcPwm = (uint16)(ulOutpLevel * ulVoltDcMotor_mV / HALDCM_DIVIDER_PWM_CALCULATION);
  return unCalcPwm;
}


//-----------------------------------------------------------------------------
/// \brief  UINT16 _HalDcmSetMotorPwm(const UINT8 ucDcmChannel, const UINT16 unPwm)
///         !!Called on interrupt level
///
/// \descr  Each time the Pwm signal will change, the lower level function
///         will be called.
///
/// \param         unPwm  Pwm value in 0.1 % steps to be set to the output.
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddDcmHal_SetMotorPwm(const uint16 unPwm)
{
  if(CddDcmHal_unLastPwmSignal != unPwm)
  {
    uint16 unPwmScaled_Mcal;
    CddDcmHal_unLastPwmSignal = unPwm;
    unPwmScaled_Mcal = (unPwm * 0x8000u) / 1000u;

  ILCU_LvlAdp_LwrPwmSetDuty(unPwmScaled_Mcal); /* ILCU_PORT: was Pwm_SetDutyCycle(ch 5); LWR PWM is ILCU IoHwAb CTRL_LWR (TIMG9 CC1) via adapter */
  }
}


//-----------------------------------------------------------------------------
/// \brief  UINT16 _HalDcmChannelLevelCtrlStart_(const UINT8 ucDcmChannel)
///         !!Called on interrupt level
///
/// \descr  This function calculate the pwm value without reading/using the
///         measured voltage at the related DC-Motor Ctrl-output. It is used for
///         calculating the first pwm settings just before the pwm channel
///         output is enabled.
///         This inline function will be called with a constant parameter value
///         (ucDcmChannel), so the compiler will remove all if statements
///         in the following code, because it will optimise the code during
///         compile time.
///         
/// \param  ucDcmChannel  Constant value of the Dcm motor channel Dcm0ChannelNumb..Dcm1ChannelNumb.
///
/// \return UINT16 unCurrentPwmValue: Calculated result of the Pwm signal, this value is also
///                written to the lower level hardware driver.
//-----------------------------------------------------------------------------
STATIC_AL uint16 CddDcmHal_ChannelLevelCtrlStart(void)
{
  uint16 unCurrentPwmValue;

  unCurrentPwmValue = CddDcmHal_CalculatePwm(CddDcmHal_unOutputLevel, CddDcmHal_ulAverageUdcmValue);

  CddDcmHal_SetMotorPwm(unCurrentPwmValue);

  return unCurrentPwmValue;
}


//-----------------------------------------------------------------------------
/// \brief  UINT16 _HalDcmChannelLevelCtrlOn_(const UINT8 ucDcmChannel)
///         !! Only called on interrupt level
///
/// \descr  This function is called every 20 ms for controlling the Dc-motor ouptuts.
///         It is called every 20 ms on interrupt level to recalculate the output
///         Dc-motor Pwm signal again. The calculated Pwm value will be written
///         to the lower level HalCc2 module.
///         This inline function will be called with a constant parameter value
///         (ucDcmChannel), so the compiler will remove all if statements
///         in the following code, because it will optimise the code during
///         compile time becaus of inline mechanism.
///         
/// \param  ucDcmChannel  Constant value of the Dcm motor channel Dcm0ChannelNumb..Dcm1ChannelNumb.
///
/// \return UINT16 unCurrentPwmValue: Calculated result of the Pwm signal, this value is also
///                written to the lower level hardware driver.
//-----------------------------------------------------------------------------
STATIC_AL uint16 CddDcmHal_ChannelLevelCtrlOn(void)
{
  uint16 unCurrentPwmValue = CddDcmHal_unMotorPwm;
  uint32 ulOutputLevel_FB  = CddDcmHal_ulOutputLevel_FB;
  uint32 ulOutputLevel     = CddDcmHal_unOutputLevel;
  uint32 ulOutLevelDiff    = (ulOutputLevel_FB >= ulOutputLevel) ?
                             (ulOutputLevel_FB - ulOutputLevel) : (ulOutputLevel - ulOutputLevel_FB);

  // Is the actual value not equal the rated/set/nominal value?
  if (ulOutLevelDiff >= HALDCM_THRESHOLD_DIFF_CONTROL)
  {
    uint16 unDeltaMotorPwm = CddDcmHal_CalculatePwm(ulOutLevelDiff, CddDcmHal_ulAverageUdcmValue);

    if (ulOutputLevel >= ulOutputLevel_FB)
    {
      unCurrentPwmValue += unDeltaMotorPwm;
      // Make sure that the new pwm value will not be too high.
      unCurrentPwmValue = min(unCurrentPwmValue,HALDCM_MAX_ALLOWED_PWM_VALUE);
    }
    else
    {
      unCurrentPwmValue = (unCurrentPwmValue > unDeltaMotorPwm) ? (unCurrentPwmValue - unDeltaMotorPwm) : 0u;
    }

    CddDcmHal_SetMotorPwm(unCurrentPwmValue);
  }

  return unCurrentPwmValue;
}


//-----------------------------------------------------------------------------
/// \brief  _inline void _HalDcmActivateChannel_(const UINT8 ucDcmChannel, const UINT8 ucState)
///         !! Only called on interrupt level
///
/// \descr  This function will activate or deactivate the Dc-Motor output channel.
///         This inline function will be called with a constant parameter value
///         (ucDcmChannel), so the compiler will remove all if statements
///         in the following code, because it will optimise the code during
///         compile time.
///
/// \param  ucDcmChannel  Constant value of the Dcm motor channel Dcm0ChannelNumb..Dcm1ChannelNumb.
/// \param       ucState  Activate(1) or Deactivate(0) of the related Dc-motor output.
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddDcmHal_ActivateChannel(const uint8 ucState)
{
  if(ucState != 0u)
  {

    uint16 unPwmScaled_Mcal;
    unPwmScaled_Mcal = (CddDcmHal_unLastPwmSignal * 0x8000u) / 1000u;

    ILCU_LvlAdp_LwrPwmStart(); /* ILCU_PORT: was Pwm_StartPwmChannel(ch 5) (DPE MCAL extension) */

    ILCU_LvlAdp_LwrPwmSetDuty(unPwmScaled_Mcal); /* ILCU_PORT: was Pwm_SetDutyCycle(ch 5) */

    CddDcm_OutputEnable(TRUE);
  }
  else
  {
    // Disable motor output
    CddDcm_OutputEnable(FALSE);
    //!!! Muessen wir hier den Duty Cycle noch merken, kurz vorm Abschalten?
    ILCU_LvlAdp_LwrPwmToIdle(); /* ILCU_PORT: was Pwm_ClampPwmChannel(ch 5, PWM_LOW) (DPE MCAL extension); ILCU idle level is low */
  }
}


//-----------------------------------------------------------------------------
/// \brief  void _HalDcmDoOutpPwmControl_(const UINT8 ucDcmChannel)
///         !! Only called on interrupt level
///
/// \descr  This function is called every 20 ms for controlling the Dc-motor ouptuts.
///         It is called every 20 ms on interrupt level to recalculate the output
///         Dc-motor Pwm signal again. The calculated Pwm value will be written
///         to the lower level HalCc2 module.
///         This inline function will be called with a constant parameter value
///         (ucDcmChannel), so the compiler will remove all if statements
///         in the following code, because it will optimise the code during
///         compile time.
///         In case the Dcm-output is disabled this function will also check for short to Vbat.
///
/// \param  ucDcmChannel  Constant value of the Dcm motor channel Dcm0ChannelNumb..Dcm1ChannelNumb.
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddDcmHal_DoOutpPwmControl(void)
{
  // Initilised to 0 in start up code.
  static uint8  HalDcm_aucOldEnablePwmOutput;

  uint32 ulHalSignalVLwr;
  uint8  ucEnablePwmOutput;

  // At first read the output voltage at the related Dc-motor output pin.
  ulHalSignalVLwr = CddDcm_GetVdcm();

  ucEnablePwmOutput = CddDcmHal_ucEnablePwmOutput;

  // Check for a changed enable/disable request condition.
  if(HalDcm_aucOldEnablePwmOutput != ucEnablePwmOutput)
  {
    HalDcm_aucOldEnablePwmOutput = ucEnablePwmOutput;

    if((ucEnablePwmOutput & DCM_OUTPUT_ENABLED_BIT_MSK) != 0u)
    {
      // Starting to control the dc motor output now, setting the first pwm signal output.
      CddDcmHal_unMotorPwm = CddDcmHal_ChannelLevelCtrlStart();

      // Enable motor output
      CddDcmHal_ActivateChannel(1u);
    }
    else
    {
      // Disable motor output
      CddDcmHal_ActivateChannel(0u);

     // Changing the Pwm value will be done only in the interrupt function,
     // to avoid calling conflict with code on task level.
     // Check for Pwm switched Off, make sure Pwm will be set to 0.
      if((ucEnablePwmOutput & PWM_SIGNAL_ACTIVE_BIT_MSK) == 0u)
      {
        CddDcmHal_SetMotorPwm(0u);
        CddDcmHal_unMotorPwm = 0;
      }

      // Mark the read back level as unknown.
      CddDcmHal_ulOutputLevel_FB = HALDCM_LEVEL_NOT_KNOWN_VALUE;
    }

    // Only enable/disable the ouptut, we will not do any voltage control now.
    // In case the ouptut is just enabled now we will do the voltage control in the
    // next cyclic call of this function.
  }
  else if((ucEnablePwmOutput & DCM_OUTPUT_ENABLED_BIT_MSK) != 0u)
  {

    // Ok, this is not the first time after switching on the output channel, so we can
    // read back the generated voltage for check of conditions such as "short to Gnd or Vbat".

    // Calculate the real output level by measering the Dc-motor output voltage.
    if (CddDcmHal_ulAverageUdcmValue != 0u)
    {
      CddDcmHal_ulOutputLevel_FB = (uint16)(((uint32)1000 * ulHalSignalVLwr) / (uint16)CddDcmHal_ulAverageUdcmValue);
    }
    else
    {
      CddDcmHal_ulOutputLevel_FB = 0u;
    }

    // Recalculate the DC-motor Pwm value and set the calculated Pwm value to the lower level
    // driver, because supply voltage or temperature condition of the electronic-components might
    // have changed.
    CddDcmHal_unMotorPwm = CddDcmHal_ChannelLevelCtrlOn();
  }
  else
  {
    // do nothing
  }
}


//-----------------------------------------------------------------------------
/// \brief  void HalDcmIrqHookOutputPwm(void)
///         !!Called from SysHook interrupt
///
/// \descr  This function is called every 5 ms from the system hook.
///         It will calculate the average voltage from the Dc-motor supply voltage
///         and it will call the pwm controller function for the recalculation of
///         the pwm signal every HALDCM_CYCLE_CTRL_TIME_COUNT (20 ms).
///         
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void CddDcmHal_IrqHookOutputPwm(void)
{
  static uint8  HalDcm_ucSumCounter;
  uint32 ulHalSignalVDcm = CddDcm_GetVbat();

  if(++HalDcm_ucSumCounter >= HALDCM_CYCLE_CTRL_TIME_COUNT)
  {
    HalDcm_ucSumCounter = 0U;

    // Addition U_Bat Filter disabled.
    CddDcmHal_ulAverageUdcmValue = ulHalSignalVDcm;

    CddDcmHal_DoOutpPwmControl();
  }
}


//-----------------------------------------------------------------------------
/// \brief  void HalDcmSetOutpLevel(const UINT8 ucDcmChannel, UINT16 unOutputLevel)
///
/// \descr  Setting output level to the related Dcm channel.
///         
/// \param  ucDcmChannel   Dc-motor channel number Dcm0ChannelNumb..Dcm1ChannelNumb.
/// \param  unOutputLevel  Output Level as 0.1% steps between allowed Min and Max
///                        constant values.
/// \return void
//-----------------------------------------------------------------------------
void CddDcmHal_SetOutpLevelChannel(uint16 unOutputLevel)
{
  // If it is not in the specified range, then we will correct the value.
  unOutputLevel = max(unOutputLevel,HALDCM_MIN_ALLOWED_SET_LEVEL);
  unOutputLevel = min(unOutputLevel,HALDCM_MAX_ALLOWED_SET_LEVEL);

  // Store Otuput-Level, must be done in an atomic way, 16 bit assignment is atomic.
  CddDcmHal_unOutputLevel = unOutputLevel;
}


//-----------------------------------------------------------------------------
/// \brief  void HalDcmEnableChannel(const UINT8 ucDcmChannel, const BOOL boState)
///
/// \descr  This function will store the enable/disable state of the specified
///         Dc-motor output. The Dc-motor output will be disabled only from the
///         cyclic interrupt function. Here we set only the flag.
///         
/// \param  ucDcmChannel  Dc-motor channel number Dcm0ChannelNumb..Dcm1ChannelNumb.
/// \param       boState  Enable(1) or disable(0) state of the related Dc-motor output.
///
/// \return void
//-----------------------------------------------------------------------------
void CddDcmHal_EnableChannel(const boolean boState)
{

  if(boState != FALSE)
  {
    // In case the Dcm output is enabled we have to make sure that the Pwm signal will be switched on again.
    CddDcmHal_ucEnablePwmOutput = (uint8)(PWM_SIGNAL_ACTIVE_BIT_MSK | DCM_OUTPUT_ENABLED_BIT_MSK);
  }
  else
  {
    // Clear only the Dcm enable bit, do nothing with the Pwm signal bit.
    CddDcmHal_ucEnablePwmOutput &= (uint8)(~DCM_OUTPUT_ENABLED_BIT_MSK);
  }
  
  // The interrupt function will find out that a new command/request has to be processed.
}


//-----------------------------------------------------------------------------
/// \brief  void HalDcmDisableAndPwmOffChannel(const UINT8 ucDcmChannel)
///
/// \descr  Will deactivate the Dc motor output and switch off the pwm signal.
///         This function will clear the Dcm-output-enable bit and the Pwm-signal-
///         active bit. Controlling the outputs will be done by the priodicall
///         controller/Irq function.
///         
/// \param  ucDcmChannel  Dc-motor channel number Dcm0ChannelNumb..Dcm1ChannelNumb.
///
/// \return void
//-----------------------------------------------------------------------------
void CddDcmHal_DisableAndPwmOffChannel(void)
{
  // PWM_SIGNAL_ACTIVE_BIT_MSK and DCM_OUTPUT_ENABLED_BIT_MSK will be cleared.
  CddDcmHal_ucEnablePwmOutput = 0u;
}


//-----------------------------------------------------------------------------
/// \brief  void HalDcmInit(void)
///
/// \descr  Will be called to initialize the Dc-motor driver. Setting default
///         pwm signal to 0% duty cycle (0 promille value) and disable the
///         Dc-motor output.
///         
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void CddDcmHal_Init(void)
{
  // Make sure that the first pwm setting will change the pwm signal.
  CddDcmHal_unLastPwmSignal = (uint16)0xffff;

  CddDcmHal_EnableChannel(FALSE);
  
  // The following function must be called after the disable function was called,
  // otherwise the interrupt function might overwrite the PWM off settings.
  CddDcmHal_SetMotorPwm(0u);

  CddDcmHal_ulOutputLevel_FB = HALDCM_LEVEL_NOT_KNOWN_VALUE;

}


//-----------------------------------------------------------------------------
/// \brief  void HalDcmResetVoltageState(const UINT8 ucDcmChannel)
///
/// \descr  This function will clear the internal measured output voltage
///         calculation.
///
/// \param  ucDcmChannel  Dc-motor channel number Dcm0ChannelNumb..Dcm1ChannelNumb.
///
/// \return void
//-----------------------------------------------------------------------------
void CddDcmHal_ResetVoltageState(void)
{
  // This asignment will be done in atomic way for the variable used also
  // on interrupt level.
  CddDcmHal_ulOutputLevel_FB = HALDCM_LEVEL_NOT_KNOWN_VALUE;
}

//-----------------------------------------------------------------------------
/// \brief  UINT8 HalDcm_GetVoltageState(const UINT8 ucDcmChannel)
///
/// \descr  This function will check the last measured output Dc-motor level.
///
/// \param  ucDcmChannel  Dc-motor channel number Dcm0ChannelNumb..Dcm1ChannelNumb.
///
/// \return UINT8 ucDetectionResult: Ok or error reason.
//-----------------------------------------------------------------------------
uint8 CddDcmHal_GetVoltageState(void)
{
  uint8 ucDetectionResult;
  uint32 ulOutputLevel_FB = CddDcmHal_ulOutputLevel_FB;

  if (ulOutputLevel_FB == HALDCM_LEVEL_NOT_KNOWN_VALUE)
  {
    ucDetectionResult = HALDCM_LEVEL_UNKNOWN;
  }
  else if (ulOutputLevel_FB < HALDCM_MIN_LEVEL_LOW)
  {
    // Signal too low detected (short to Gnd).
    ucDetectionResult = HALDCM_LEVEL_LOW;
  }
  else if (ulOutputLevel_FB > HALDCM_MAX_LEVEL_HIGH)
  {
    // Signal too high detected (short to VBat).
    ucDetectionResult = HALDCM_LEVEL_HIGH;
  }
  else
  {
    ucDetectionResult = HALDCM_LEVEL_OK;
  }
  return ucDetectionResult;
}



//******************************************************************************
// R T E   I N T E R F A C E
//******************************************************************************


void riCddDcm_Init(void)
{
  CddDcmHal_Init();

  CddDcmCtrl_Init();
}


void rpCddDcm_Cycle0(void)
{
  static uint8 ucTimeCnt;
  ucTimeCnt++;
  if (ucTimeCnt >= CDDDCM_SUBCYCLE)
  {
    CddDcmCtrl_Main();
    ucTimeCnt = 0u;
  }

  // start motor

  CddDcmHal_IrqHookOutputPwm();

}

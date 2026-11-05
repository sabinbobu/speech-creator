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
/// \file  CddStp88XXVolt.c
///
/// \brief  TI DRV88XX specific complex device driver
///
/// \descr  Stepper Driver, voltage range state machine processing.
///
///         Internal handling:
///            * CddStpVolt_ucVoltRange:                                                      tVolt_Range  -  Lo3=1, Lo2=2, Lo1=3, Norm=4, Hi1=5, Hi2=6
///         External handling:
///            * CddStpVolt_ucPreResult & CddStpVolt_ucEndResult & CddStp88XX_ucStateVolt:    uint8        -  StateVoltOff=0, StateVoltUnder=1, StateVoltNormal=2, StateVoltOver=3, StateVoltStartValue=0xFF
///
///         * STP_SPANNUNG_LO3  /* e.g.  '76' */ [0.1 V]  Spannungsschwelle fuer die harte Abschaltung des Treibers bei Unterspannung
///         * STP_SPANNUNG_LO2  /* e.g.  '86' */ [0.1 V]  Spannungsschwelle fur das Anhalten des Motors bei Unterspannung (N.b.: KEIN Anhalten bei Ref-Run)
///         * STP_SPANNUNG_LO1  /* e.g.  '96' */ [0.1 V]  Spannungsschwelle fur die Reaktivierung des Motors nach Unterspannung
///         * STP_SPANNUNG_HI1  /* e.g. '187' */ [0.1 V]  Spannungsschwelle fur die Reaktivierung des Motors nach Ueberspannung
///         * STP_SPANNUNG_HI2  /* e.g. '197' */ [0.1 V]  Spannungsschwelle fur das Anhalten des Motors bei Ueberspannung
///         * STP_SPANNUNG_RED  /* e.g. '110' */ [0.1 V]  Spannung, unter der die maximale Verstellfrequenz reduziert wird. Die Reduktion der maximalen Verstellfrequenz erfolgt annaehernd linear zur Versorgungsspannung.
///
///          SPANNUNG_DEBOUNCE_ON;  // vergl. 'Cod_StpSpannungDebOn()'
///                                 // FLM3.SWRS.14433, FLM3.SWRS.27065, FLM3.SWRS.27066
///                                 //    * The application shall repeat the referencing of LWR Stepper when the referencing was interrupted by low voltage and VBAT is once again greater or equal than COD_STP_SPANNUNG_LO1 for COD_STP_SPANNUNG_DEBOUNCE_ON.
///                                 //    * The application shall resume   LWR Stepper movement, when VBAT is once again is greater than COD_STP_SPANNUNG_LO1 for COD_STP_SPANNUNG_DEBOUNCE_ON. 
///                                 //    * The application shall continue LWR Stepper movement, when VBAT is once again is lower   than COD_STP_SPANNUNG_HI1 for COD_STP_SPANNUNG_DEBOUNCE_ON. 
///          SPANNUNG_DEBOUNCE_OFF; // vergl. 'Cod_StpSpannungDebOff()'
///                                 // FLM3.SWRS.27502, FLM3.SWRS.27062, FLM3.SWRS.27063
///                                 //    * The application shall set the LWR Stepper to off (lost reference) when VBAT is lower   than COD_STP_SPANNUNG_LO3 for COD_STP_SPANNUNG_DEBOUNCE_OFF and the LWR Stepper is moving in normal operation. 
///                                 //    * The application shall stop and hold LWR Stepper position movement, if  VBAT is greater than COD_STP_SPANNUNG_HI2 for COD_STP_SPANNUNG_DEBOUNCE_OFF.
///                                 //    * The application shall stop and hold LWR Stepper position movement, if  VBAT is lower   than COD_STP_SPANNUNG_LO2 for COD_STP_SPANNUNG_DEBOUNCE_OFF.
///
///         Hi2  ('6') - e.g. '19,7V'                                          /=====================\                                               |
///         Hi1  ('5') - e.g. '18,7V'                                     /===/  |                    \==================\                           |
///         Norm ('4') - e.g. '13,5V' ====\                          /===/  |    |-> Hi2: stop moving   |                 \=========                 |
///         Lo1  ('3') - e.g. ' 9,6V'      \===\                /===/  |    |-> Hi1: -                  |-> Hi1: Restart    |                        |
///         Lo2  ('2') - e.g. ' 8,6V'        |   \===\     /===/  |    |-> Norm: -                                          |-> Norm                 |
///         Lo3  ('1') - e.g. ' 7,6V'        |     |  \===/  |    |-> Lo1: Restart
///                                          |     |    |    |-> Lo2: -
///                                          |     |    |-> Lo3: hard off
///                                          |     |-> Lo2: stop moving - but do NOT stop Ref-Run
///                                          |-> Lo1: -
///
/// \author Wuesteney, Ulrich ALRT/EEG4 * (wu82rt)
///         J. Kling ALRT-EES6 (f84304b)
//-----------------------------------------------------------------------------


//-Die Zeiten von 6ms werden beim 10 ms zyklischen Aufruf zu 0 zerfallen.


//=============================================================================
// includes
//=============================================================================
#include <Std_Types.h>
#include <AL_Helper.h> // e.g. 'STATIC_AL'


#ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
  #include <../Cust/St/St126/Cdd/CddStp/CddStpPrj.h>
  #include <CddStpData.h>
#include <Rte.h>
#else // Unit-Tests!
  //#define CFA_CNT_STP_88XX   (4u)
  #include <CddStpPrj.h>
  #include <CddStpData.h>

  extern unsigned long CddStp_UnitTest__u32Voltage_mV;
#endif

#ifdef CDDSTP_CFG_SIMULATION // defined in '.\Asr6\Src\Src_AL\Cust\Bw\Bw16\App\Bsw\Cdd\CddStp\CddStpPrj.h'
  #include <CddStp_Simulation.h>
#endif // CDDSTP_CFG_SIMULATION

#include <88XX/CddStp88XX.h>
#include <88XX/CddStp88XXVolt.h>
#include <Bsw/IoHwAb/IoHwAbUser.h>



// ---------------------------------------------------------------------------
// preprocessor definitions
// ---------------------------------------------------------------------------
#define CDDSTP88XX_StateVoltStartValue  (0xffu)


// Runable cycle time for timer counter variable, called every 10ms
//#define CONV_MS_TO_CNT(Time_ms)  ((Time_ms) / 10)                                         // -> see CddStpVolt_ConvMsToCnt()

//#define NewState(unT_ms,ucNewSt)   { unTime_ms = (unT_ms); ucNewState = (ucNewSt); }      // -> see direct assignments unTime_ms = ???; ucNewState = ???;

// ---------------------------------------------------------------------------
// const
// ---------------------------------------------------------------------------

#define T_Lo1_Start_ms                      (50u)   // Startphase: Time for State change from Below to Normal


// ---------------------------------------------------------------------------
// type definitions
// ---------------------------------------------------------------------------

#define CDDSTP88XXVOLT_HI_DISABLEOFFSET     (0u) // '0'=disable, '400'=active  -  [0.1 V] - add 40 V to disable high voltage detection!
 

// ---------------------------------------------------------------------------
// local types
// ---------------------------------------------------------------------------
typedef enum
{
  eInit   = 0,
  eLow3   = 1,
  eLow2   = 2,
  eLow1   = 3,
  eNormal = 4,
  eHigh1  = 5,
  eHigh2  = 6
} tVolt_Range;


//=============================================================================
// variables
//=============================================================================

STATIC_AL uint8       CddStpVolt_ucPreResult;                                  // StateVoltOff=0, StateVoltUnder=1, StateVoltNormal=2, StateVoltOver=3, StateVoltStartValue=0xFF
// Init Value to make sure that the first call will be reported.
STATIC_AL uint8       CddStpVolt_ucEndResult = CDDSTP88XX_StateVoltStartValue; // StateVoltOff=0, StateVoltUnder=1, StateVoltNormal=2, StateVoltOver=3, StateVoltStartValue=0xFF
STATIC_AL uint16      CddStpVolt_unTimerCnt  = 0u;
STATIC_AL tVolt_Range CddStpVolt_ucVoltRange = eInit;                          // Lo3=1, Lo2=2, Lo1=3, Norm=4, Hi1=5, Hi2=6


// ---------------------------------------------------------------------------
// local prototypes
// ---------------------------------------------------------------------------
STATIC_AL void   CddStpVolt_TimerStop(void);                                         // Stop timer to make sure the CddStpVolt_ucPreResult is canceled / discard 'CddStpVolt_ucPreResult' and keep 'CddStpVolt_ucEndResult'
STATIC_AL void   CddStpVolt_TimerRestart(uint16 unTime_Cnt, uint8 ucPreResult);      // countdown of 'CddStpVolt_unTimerCnt' in fct 'CddStp88XXVolt_StpVoltCycle'
STATIC_AL void   CddStpVolt_FinalResult(uint8 ucEndResult);                          // set 'CddStpVolt_ucEndResult' and call 'CddStp88XX_Volt' (and set 'CddStp88XX_ucStateVolt')
STATIC_AL uint16 CddStpVolt_ConvMsToCnt(uint16 unTime_ms);


// ---------------------------------------------------------------------------
// inline functions
// ---------------------------------------------------------------------------
STATIC_AL uint16 CddStpVolt_ConvMsToCnt(uint16 unTime_ms)
{
  return ((unTime_ms) / 10u);
}


//-----------------------------------------------------------------------------
/// \brief  Called only on every change of the ucVoltRange value
///
/// \descr  This function is the state machine for calculating the 
///         StateVolt result. If the state transition is relevant it will
///         start/retrigger the timer for delay time implementation.
///         In case a change of state is detected the CddStpVolt_TimerRestart() is
///         called for changing the state variable delayed.
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void CddStp88XXVolt_StpVoltRng(void)
{
  STATIC_UT(uint8, ucNormalTiming, 0u);
  uint16           unVoltage_mV;
  uint32           ulChangeVoltRange;
  tVolt_Range      VoltRange; // Lo3=1, Lo2=2, Lo1=3, Norm=4, Hi1=5, Hi2=6
  uint8            ucNewState = CDDSTP88XX_StateVoltOff;
  uint16           unTime_ms  = 0xffffu; // countdown of 'CddStpVolt_unTimerCnt' in fct 'CddStp88XXVolt_StpVoltCycle'
  tsRteCodingParameters sCodingParameters;

  IoHwAb_User_GetAdc_DIAG_VBAT(&unVoltage_mV);  //TODO

  (void)Rte_Read_CodM_CddStp_Para(&sCodingParameters);

  if (sCodingParameters.eCodingState != eParaFct0_CodingDataInvalid)
  {

#ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
#else // Unit-Tests!
    CddStp_UnitTest_Printf("                      *#*#*#*#*#*#*#* JK - CddStp88XXVolt_StpVoltRng (unVoltage_mV=%d) *#*#*#*#*#*#*#*\n", unVoltage_mV); // = 13500 = 13,5V
//printf("                        *#*#*#*#*#*#*#* JK - CddStp88XXVolt_StpVoltRng ((uint16) Cod_StpSpannungHi2()=%d) *#*#*#*#*#*#*#*\n", (uint16)Cod_StpSpannungHi2()); // = 165 = 16,5V
//printf("                        *#*#*#*#*#*#*#* JK - CddStp88XXVolt_StpVoltRng (((uint16)Cod_StpSpannungHi2() + CDDSTP88XXVOLT_HI_DISABLEOFFSET) * 100u)=%d) *#*#*#*#*#*#*#*\n", (((uint16)Cod_StpSpannungHi2() + CDDSTP88XXVOLT_HI_DISABLEOFFSET) * 100u)); // = 56500
//printf("                        *#*#*#*#*#*#*#* JK - CddStp88XXVolt_StpVoltRng ((uint16) Cod_StpSpannungLo1()=%d) *#*#*#*#*#*#*#*\n", (uint16)Cod_StpSpannungLo1()); // = 90 = 9,0V
#endif

    // if 'CDDSTP88XXVOLT_HI_DISABLEOFFSET' is active: add 40 V to disable high voltage detection!
    if (unVoltage_mV >= (((uint16)Cod_StpSpannungHi2() + CDDSTP88XXVOLT_HI_DISABLEOFFSET) * 100u))      // [mv]
    {
      VoltRange = eHigh2;
    }
    else if (unVoltage_mV >= (((uint16)Cod_StpSpannungHi1() + CDDSTP88XXVOLT_HI_DISABLEOFFSET) * 100u)) // [mv]
    {
      VoltRange = eHigh1;
    }
    else if (unVoltage_mV >= ((uint16)Cod_StpSpannungLo1() * 100u)) // [mv] // e.g. Lo1=96 -> *100 = 9600 -> 9,6V
    {
      VoltRange = eNormal;
    }
    else if (unVoltage_mV >= ((uint16)Cod_StpSpannungLo2() * 100u)) // [mv]
    {
      VoltRange = eLow1;
    }
    else if (unVoltage_mV >= ((uint16)Cod_StpSpannungLo3() * 100u)) // [mv]
    {
      VoltRange = eLow2;
    }
    else
    {
      VoltRange = eLow3;
    }

    ulChangeVoltRange = (uint32) CddStpVolt_ucVoltRange ^ (uint32) VoltRange;

    if(ulChangeVoltRange != 0u)  // Check for changed value
    {
      const  tVolt_Range NewVoltRange = VoltRange; // Lo3=1, Lo2=2, Lo1=3, Norm=4, Hi1=5, Hi2=6
         
      switch (CddStpVolt_ucEndResult) // StateVoltOff=0, StateVoltUnder=1, StateVoltNormal=2, StateVoltOver=3, StateVoltStartValue=0xFF
      {
        case CDDSTP88XX_StateVoltStartValue:  // Init start value
        case CDDSTP88XX_StateVoltOff:
        {
          switch (NewVoltRange) // Lo3=1, Lo2=2, Lo1=3, Norm=4, Hi1=5, Hi2=6
          {
            case eNormal:
            case eHigh1:
            {
              if (ucNormalTiming == 0u)        // Start phase/mode
              {
                ucNormalTiming = 1u;
                // fast to normal
                unTime_ms = T_Lo1_Start_ms;
                ucNewState = CDDSTP88XX_StateVoltNormal;
              }
              else  // normal/running mode
              {
                // slow to normal
                unTime_ms = (uint16)Cod_StpSpgDebOn() * 10u;
                ucNewState = CDDSTP88XX_StateVoltNormal;
              }
              break;
            }
        
            // fast to Over
            case eHigh2:
            {
              unTime_ms = (uint16)Cod_StpSpgDebOff() * 10u;
              ucNewState = CDDSTP88XX_StateVoltOver;
              break;
            }

            // No change of state or for the Start state switch to Off state.
            //case eLow3:
            //case eLow2:
            //case eLow1:
            default:
            {
              CddStpVolt_TimerStop(); // Stop timer to make sure the CddStpVolt_ucPreResult is canceled / discard 'CddStpVolt_ucPreResult' and keep 'CddStpVolt_ucEndResult'
        
              if (CddStpVolt_ucEndResult == CDDSTP88XX_StateVoltStartValue)
              {
                unTime_ms = 0u; // immediately to Off
                ucNewState = CDDSTP88XX_StateVoltOff;
              }
              break;
            }
          }
          break;    
        }

    
        case CDDSTP88XX_StateVoltUnder:
        {
          switch (NewVoltRange) // Lo3=1, Lo2=2, Lo1=3, Norm=4, Hi1=5, Hi2=6
          {
            // fast to off
            case eLow3:
            {
              unTime_ms = (uint16)Cod_StpSpgDebOff() * 10u;
              ucNewState = CDDSTP88XX_StateVoltOff;
              CddStp88XX_boIgnoreOLDetection = TRUE;
              break;
            }
        
            // slow to normal
            case eNormal:
            case eHigh1:
            {
              unTime_ms = (uint16)Cod_StpSpgDebOn() * 10u;
              ucNewState = CDDSTP88XX_StateVoltNormal;
              break;
            }
                
            // fast to Over
            case eHigh2:
            {
              unTime_ms = (uint16)Cod_StpSpgDebOff() * 10u;
              ucNewState = CDDSTP88XX_StateVoltOver;
              break;
            }

            // No change of state
            //case eLow2:
            //case eLow1:  // Stop timer to make sure the CddStpVolt_ucPreResult is canceled.
            default:
            {
              CddStpVolt_TimerStop(); // Stop timer to make sure the CddStpVolt_ucPreResult is canceled / discard 'CddStpVolt_ucPreResult' and keep 'CddStpVolt_ucEndResult'
              break;
            }
          }
          break;    
        }

    
        case CDDSTP88XX_StateVoltNormal:
        {
          switch (NewVoltRange) // Lo3=1, Lo2=2, Lo1=3, Norm=4, Hi1=5, Hi2=6
          {
            // fast to off
            case eLow3:
            {
              unTime_ms = (uint16)Cod_StpSpgDebOff() * 10u;
              ucNewState = CDDSTP88XX_StateVoltOff;
              CddStp88XX_boIgnoreOLDetection = TRUE;
              break;
            }

            // fast to under
            case eLow2:
            {
              unTime_ms = (uint16)Cod_StpSpgDebOff() * 10u;
              ucNewState = CDDSTP88XX_StateVoltUnder;
              break;
            }

            // fast to Over
            case eHigh2:
            {
              unTime_ms = (uint16)Cod_StpSpgDebOff() * 10u;
              ucNewState = CDDSTP88XX_StateVoltOver;
              break;
            }

            // No change of state
            //eLow1
            //eNormal
            //eHigh1    // Stop timer to make sure the CddStpVolt_ucPreResult is canceled.        
            default:
            {
              CddStpVolt_TimerStop(); // Stop timer to make sure the CddStpVolt_ucPreResult is canceled / discard 'CddStpVolt_ucPreResult' and keep 'CddStpVolt_ucEndResult'
              break;
            }
          }
          break;    
        }

    
        case CDDSTP88XX_StateVoltOver:
        {
          switch (NewVoltRange) // Lo3=1, Lo2=2, Lo1=3, Norm=4, Hi1=5, Hi2=6
          {
            // fast to off
            case eLow3:
            {
              unTime_ms = (uint16)Cod_StpSpgDebOff() * 10u;
              ucNewState = CDDSTP88XX_StateVoltOff;
              break;
            }

            // slow to under
            case eLow2:
            {
              unTime_ms = (uint16)Cod_StpSpgDebOn() * 10u;
              ucNewState = CDDSTP88XX_StateVoltUnder;
              break;
            }

            // slow to normal
            case eLow1:
            case eNormal:
            {
              unTime_ms = (uint16)Cod_StpSpgDebOn() * 10u;
              ucNewState = CDDSTP88XX_StateVoltNormal;
              break;
            }

            // No change of state
            //case eHigh1:
            //case eHigh2: // Stop timer to make sure the CddStpVolt_ucPreResult is canceled.        
            default:
            {
              CddStpVolt_TimerStop(); // Stop timer to make sure the CddStpVolt_ucPreResult is canceled / discard 'CddStpVolt_ucPreResult' and keep 'CddStpVolt_ucEndResult'
              break;
            }
          }
          break;
        } // end of 'case CDDSTP88XX_StateVoltOver:'


        default:  // unknown state, should not happen
        {
          CddStpVolt_TimerStop();  // Stop timer to make sure the CddStpVolt_ucPreResult is canceled / discard 'CddStpVolt_ucPreResult' and keep 'CddStpVolt_ucEndResult'
          unTime_ms = 0u; // change state Fast_T_ms immediately to off
          ucNewState = CDDSTP88XX_StateVoltOff;
          break;
        }
      }  // end of 'switch (CddStpVolt_ucEndResult)'
  
      if (unTime_ms != 0xffffu)
      {
        CddStpVolt_TimerRestart(CddStpVolt_ConvMsToCnt(unTime_ms), ucNewState); // countdown of 'CddStpVolt_unTimerCnt' in fct 'CddStp88XXVolt_StpVoltCycle'
      }
    } // end of 'if(ulChangeVoltRange != 0u)  // Check for changed value'

    CddStpVolt_ucVoltRange = VoltRange;
  }
// PRQA S 5310, 5316, 5324, 5330, 5336 1    // program architecture and readability
}


//-----------------------------------------------------------------------------
/// \brief  Called every 10ms for checking the timer variable.
///
/// \descr
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void CddStp88XXVolt_StpVoltCycle(void)
{
  if (CddStpVolt_unTimerCnt != 0u)
  {
    CddStpVolt_unTimerCnt--;
    if (CddStpVolt_unTimerCnt == 0u)
    {
      CddStpVolt_FinalResult(CddStpVolt_ucPreResult); // set 'CddStpVolt_ucEndResult' and call 'CddStp88XX_Volt' (and set 'CddStp88XX_ucStateVolt')
    }
  }
}


//-----------------------------------------------------------------------------
/// \brief  Get actual stepper volt state.
///
/// \descr  Return the stepper state voltage value. In case the StartValue/Init
///         value is still valid (Voltage state unknown) we will return the
///         CDDSTP88XX_StateVoltOff state.
///
/// \param  -
///
/// \return uint8 Volt state
//-----------------------------------------------------------------------------
uint8 CddStp88XXVolt_GetStpVoltState(void)
{
  uint8 ucResult = CddStpVolt_ucEndResult; // StateVoltOff=0, StateVoltUnder=1, StateVoltNormal=2, StateVoltOver=3, StateVoltStartValue=0xFF
  
  if (ucResult == CDDSTP88XX_StateVoltStartValue)
  {
    ucResult = CDDSTP88XX_StateVoltOff;
  }
  
  return ucResult;
}


//-----------------------------------------------------------------------------
/// \brief  Stop stepper Volt timer.
///
/// \descr  Stop timer to make sure the CddStpVolt_ucPreResult is canceled
///         I.e. discard 'CddStpVolt_ucPreResult' and keep 'CddStpVolt_ucEndResult'
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddStpVolt_TimerStop(void)
{
  CddStpVolt_unTimerCnt = 0u; // -> discard 'CddStpVolt_ucPreResult' and keep 'CddStpVolt_ucEndResult'
}


//-----------------------------------------------------------------------------
/// \brief  This fct will restart the timer used in this modul
///
/// \descr  In case the time is 0 the final end state fct will be
///         called immidiately.
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddStpVolt_TimerRestart(uint16 unTime_Cnt, uint8 ucPreResult)
{
  CddStpVolt_unTimerCnt  = unTime_Cnt;
  CddStpVolt_ucPreResult = ucPreResult; // StateVoltOff=0, StateVoltUnder=1, StateVoltNormal=2, StateVoltOver=3, StateVoltStartValue=0xFF

  // set immediately?
  if (CddStpVolt_unTimerCnt == 0u) // countdown of 'CddStpVolt_unTimerCnt' in fct 'CddStp88XXVolt_StpVoltCycle'
  {
    CddStpVolt_FinalResult(CddStpVolt_ucPreResult); // set 'CddStpVolt_ucEndResult' and call 'CddStp88XX_Volt' (and set 'CddStp88XX_ucStateVolt')
  }
}


//-----------------------------------------------------------------------------
/// \brief  This function will set the final state each time a new
///         state is calculated.
/// \descr  In additional it will inform the Stepper module about the
///         change of state by calling the CddStp88XX_Volt() function.
///
/// \param  ucEndResult: StateVoltOff=0, StateVoltUnder=1, StateVoltNormal=2, StateVoltOver=3, StateVoltStartValue=0xFF
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddStpVolt_FinalResult(uint8 ucEndResult)
{
  // changed?
  if (CddStpVolt_ucEndResult != ucEndResult)
  {
    CddStpVolt_ucEndResult = ucEndResult; // StateVoltOff=0, StateVoltUnder=1, StateVoltNormal=2, StateVoltOver=3, StateVoltStartValue=0xFF
    
    // inform the stepper module for change of volt state.
    CddStp88XX_Volt(ucEndResult); // set 'CddStp88XX_ucStateVolt'
  }
}


//-----------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param  [paramName]
///
/// \return [returnTyp]
//-----------------------------------------------------------------------------
void IoHwAb_User_GetAdc_DIAG_VBAT(uint16* pio_signal)
{
  tiu32Voltage_mV u32Voltage_mV = 15000;

#ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
  // jk-tbd: 'ppIoHwAbUserEcuSupply0' / 'Rte_Read_ppIoHwAbUserEcuSupply0_ulActualMean'  <-->  'Rte_Read_ppIoHwAbUserEcuSupply0_ulActualMin'
  (void)Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT(&u32Voltage_mV);
#else // Unit-Tests!
  u32Voltage_mV = CddStp_UnitTest__u32Voltage_mV;
#endif // UNIT_TEST

  *pio_signal = (uint16)u32Voltage_mV;

#ifdef CDDSTP_CFG_SIMULATION // defined in '.\Asr6\Src\Src_AL\Cust\Bw\Bw16\App\Bsw\Cdd\CddStp\CddStpPrj.h'
  // simulation
  if (CddStp_Simulation_IsSimActive() != FALSE)
  {
    uint16 unValue;
    if (CddStp_Simulation_HandleVBatt_EcuSupply(&unValue) != FALSE)
    {
      *pio_signal = (uint16)unValue;
    }
    else
    {
    }
  }
  else
  {
  }
#endif // CDDSTP_CFG_SIMULATION
}

//EOF

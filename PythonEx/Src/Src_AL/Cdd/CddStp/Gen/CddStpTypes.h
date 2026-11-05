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
/// \file  CddStpTypes.h
///
/// \brief  Texas Instruments TI-DRV88XX specific complex device driver
///
/// \descr  OnBoard Stepper Driver 
///
///         Additional information can be found in the design description (Link:
///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
///
/// \author Wuesteney, Ulrich ALRT/EEG4 * (wu82rt)
///         J. Kling ALRT-EES6 (f84304b)
//-----------------------------------------------------------------------------

#ifndef __CDDSTPTYPES_H__
#define __CDDSTPTYPES_H__


//=============================================================================
// includes
//=============================================================================
//  #include <Std_Types.h>

  #include <88XX/CddStp88XX_HalStp.h>


//  -----------------------------------------------------------------------------------------------
//  defines
//  -----------------------------------------------------------------------------------------------

// frequency interface of StpCtrlXxxMsg
// convert frequency to log. value according 16 * log(f), f = frequency in HS/s, use rounding correction
// LOG2_10Kn(f) returns 10000 * log2(f)

//#define CDDSTP_FREQ(f)  ((uint8)((uint32)((uint32)(16UL * LOG2_10Kn(f)) + (uint32) 5000UL) / (uint32) 10000UL))

#define CDDSTP_Freq010   (uint8) (0x36  + 3) // add 3 because of driver frequency tolerance for discret use of frequency
#define CDDSTP_Freq021   (uint8) (0x46  + 3) // add 3 because of driver frequency tolerance for discret use of frequency
#define CDDSTP_Freq031   (uint8) (0x4F  + 3) // add 3 because of driver frequency tolerance for discret use of frequency
#define CDDSTP_Freq042   (uint8) (0x56  + 3) // add 3 because of driver frequency tolerance for discret use of frequency
#define CDDSTP_Freq052   (uint8) (0x5B  + 3) // add 3 because of driver frequency tolerance for discret use of frequency
#define CDDSTP_Freq056   (uint8) 0x5D
#define CDDSTP_Freq073   (uint8) 0x63
#define CDDSTP_Freq099   (uint8) 0x6A
#define CDDSTP_Freq103   (uint8) 0x6B
#define CDDSTP_Freq112   (uint8) 0x6D
#define CDDSTP_Freq122   (uint8) 0x6F
#define CDDSTP_Freq128   (uint8) 0x70
#define CDDSTP_Freq140   (uint8) 0x72
#define CDDSTP_Freq146   (uint8) 0x73
#define CDDSTP_Freq181   (uint8) 0x78
#define CDDSTP_Freq189   (uint8) 0x79
#define CDDSTP_Freq206   (uint8) 0x7B
#define CDDSTP_Freq235   (uint8) 0x7E
#define CDDSTP_Freq267   (uint8) 0x81
#define CDDSTP_Freq512   (uint8) 0x90
#define CDDSTP_Freq609   (uint8) 0x94
#define CDDSTP_Freq2000  (uint8) 0xB0
#define CDDSTP_FreqMax   (uint8) 0xFF


#ifndef SUPPORT_UNKNOWN
#define SUPPORT_UNKNOWN 2U
#endif /*SUPPORT_UNKNOWN*/


// CDDSTP timebase in microseconds
#define CDDSTP_TimeBaseFreq                 (CDDSTP88XX_HALSTP_TimeBaseFreq)

// Conversion macro from stepper timer ticks to µs
#if ((CDDSTP_TimeBaseFreq == ((1000ul * 1024ul) / 1000ul)) || (CDDSTP_TimeBaseFreq == ((625ul * 1024ul) / 1000ul)))
  #define CDDSTP_TICKS_TO_US(StpTicks)        ((((StpTicks) / (CDDSTP_TimeBaseFreq / 128ul)) * (1024ul / 128ul)))   // = (StpTicks / CDDSTP_TimeBaseFreq) * 1024
#else
//#define CDDSTP_TICKS_TO_US(StpTicks)        (((StpTicks) * (8388608ul / CDDSTP_TimeBaseFreq)) / 8192ul)           // = (StpTicks * 1024) / CDDSTP_TimeBaseFreq  //! overflow is possible!
#error TBD
#endif
  
// buffer for data exchange with HalStp
#define CDDSTP_HsInfoBufSize                (CDDSTP88XX_HALSTP_HsInfoBufLen)
#define CDDSTP_HsInfoBufMask                (CDDSTP88XX_HALSTP_HsInfoBufLen - 1u)

#define CDDSTP_SamplingTime                 (10)                                                      // default cyclic StpCtrlMsg sampling time
#define CDDSTP_DynCalcTime                  (CDDSTP_SamplingTime + 3)                                 // ms (calculation time for CddStpDyn)


// define maximumn HS period used in CddStp
#define  CDDSTP_MaxHsPeriod                 ((uint16) 32767)  // 32.8 ms ->   ca.32 HS/s (representable by 15 bit)

// frequency interface of StpCtrlXxxMsg
// convert frequency to log. value according 16 * log(f), f = frequency in HS/s, use rounding correction
// LOG2_10Kn(f) returns 10000 * log2(f)

#define CDDSTP_FREQ(f)  ((uint8)((uint32)((uint32)(16UL * LOG2_10Kn(f)) + (uint32) 5000UL) / (uint32) 10000UL))



//  -----------------------------------------------------------------------------------------------
//  types
//  -----------------------------------------------------------------------------------------------

// dynamic profile
typedef enum
{
  eDynProfile_PD0  = 0,
  eDynProfile_PD1  = 1,
  eDynProfile_PD2  = 2,
  eDynProfile_PD3  = 3,
  eDynProfile_PD4  = 4,
  eDynProfile_PD5  = 5,
  eDynProfile_PD6  = 6,
  eDynProfile_PD7  = 7,

  eDynProfile_Inv  = 0xFF
} tCddStp_DynProfile;


// referencing profile
typedef enum
{
  eRefProfile_PR0  = 0,
  eRefProfile_PR1  = 1,
  eRefProfile_Cnt  = 2,
  eRefProfile_Inv  = 0xFF
} tCddStp_RefProfile;


// step mode
typedef enum
{
  eStepMode_MS  = 0,
  eStepMode_HS  = 1
} tCddStp_StepMode;


// criteria for new referencing process
typedef enum
{
  eCddStp_NewRefNever       = 0,   // no new referencing in any under-/overvoltage case
  eCddStp_NewRefAlways      = 1,   // new referencing caused by under-/overvoltage during stepper movement
  eCddStp_NewRefConditional = 2    // like "Always", but not in case of "SlowMotion" condition
} tCddStp_NewRefCriteria;









//  // Alx1_div/Platform_Types_HCM.h
//
//  // jk-obsolet // error quality
//  // jk-obsolet typedef enum enum_ErrQty
//  // jk-obsolet {
//  // jk-obsolet   E_SNA = 0,
//  // jk-obsolet   E_FAILED = 1,
//  // jk-obsolet   E_PASSED = 2,
//  // jk-obsolet   E_TIMEOUT = 3
//  // jk-obsolet }
//  // jk-obsolet tieErrQty;
//
//  // jk-obsolet typedef enum
//  // jk-obsolet {
//  // jk-obsolet   E_TYPE_SNA = 0,
//  // jk-obsolet   E_TYPE_FAILED_ShrtGnd = 1,
//  // jk-obsolet   E_TYPE_FAILED_ShrtVbatOpenload = 2,
//  // jk-obsolet   E_TYPE_FAILED_InvalidType = 3,
//  // jk-obsolet   E_TYPE_PASSED = 4
//  // jk-obsolet }tieErrTypeA;
//
//  // jk-obsolet // system mode
//  // jk-obsolet typedef enum enum_SysMode
//  // jk-obsolet {
//  // jk-obsolet   SYS_MODE_NORMAL = 0,
//  // jk-obsolet   SYS_MODE_INVALID = 1,
//  // jk-obsolet   SYS_MODE_ERROR = 2,
//  // jk-obsolet   SYS_MODE_PBL = 3, // primary boot loader flash mode (PBL)
//  // jk-obsolet   SYS_MODE_STARTUP = 4, // ECU startup
//  // jk-obsolet   SYS_MODE_PRODUCTION = 5, // ECU factory test (Eft/PAV)
//  // jk-obsolet   SYS_MODE_PARAMETER = 6, // parameter flash mode
//  // jk-obsolet   SYS_MODE_ANALYSIS = 7, // Analyze mode (normal mode with RDM)
//  // jk-obsolet   SYS_MODE_SHUTDOWN = 8
//  // jk-obsolet }
//  // jk-obsolet tieSysMode;
//
//  // aas typedef unsigned char tieSigQty;
//  // aas typedef unsigned char UInt8;
//
//  // [%] percent
//  typedef uint8 tiucPercent;
//#define MAX_tiucPercent (tiucPercent)100u
//#define MIN_tiucPercent (tiucPercent)0u
//  typedef struct struct_Percent
//  {
//    tiucPercent ucVal;
//    tieSigQty eQty;
//  }
//  tisPercent;
//
//// jk-obsolet   // [100/128%] percent (100% = 0x80)
//// jk-obsolet   typedef uint8 tiucPercent_100_128;
//// jk-obsolet #define MAX_tiucPercent_100_128 (tiucPercent_100_128)0x80U
//// jk-obsolet #define MIN_tiucPercent_100_128 (tiucPercent_100_128)0x00U
//  // jk-obsolet typedef struct struct_Percent_100_128
//  // jk-obsolet {
//  // jk-obsolet   tiucPercent_100_128 ucVal;
//  // jk-obsolet   tieSigQty eQty;
//  // jk-obsolet }
//  // jk-obsolet tisPercent_100_128;
//
//// jk-obsolet   // [1/2%] percent (100% = 200)
//// jk-obsolet   typedef uint8 tiucPercent_1_2;
//// jk-obsolet #define MAX_tiucPercent_1_2 (tiucPercent_1_2)200U
//// jk-obsolet #define MIN_tiucPercent_1_2 (tiucPercent_1_2)0U
//// jk-obsolet   typedef struct struct_Percent_1_2
//// jk-obsolet   {
//// jk-obsolet     tiucPercent_1_2 ucVal;
//// jk-obsolet     tieSigQty eQty;
//// jk-obsolet   }
//// jk-obsolet   tisPercent_1_2;
//
//// jk-obsolet   // [1/10%] percent
//// jk-obsolet   typedef uint16 tiunPercent_1_10;
//// jk-obsolet   typedef struct struct_Percent_1_10
//// jk-obsolet   {
//// jk-obsolet     tiunPercent_1_10 unVal;
//// jk-obsolet     tieSigQty eQty;
//// jk-obsolet   }
//// jk-obsolet   tisPercent_1_10;
//
//// jk-obsolet   // [100/32768%] percent (100% = 0x8000)
//// jk-obsolet   typedef uint16 tiunPercent_1_328;
//// jk-obsolet #define MAX_tiunPercent_1_328 (tiunPercent_1_328)0x8000U
//// jk-obsolet #define MIN_tiunPercent_1_328 (tiunPercent_1_328)0x0000U
//// jk-obsolet   typedef struct struct_Percent_1_328
//// jk-obsolet   {
//// jk-obsolet     tiunPercent_1_328 unVal;
//// jk-obsolet     tieSigQty eQty;
//// jk-obsolet   }
//// jk-obsolet   tisPercent_1_328;
//
//  // [(1/328%)/20ms] 0.15  percent/sec. for ramp steps for tiunPercent_1_328 types called in 20ms cycle 
//  // [(1/328%)/10ms] 0.305 percent/sec. for ramp steps for tiunPercent_1_328 types called in 10ms cycle 
//  // [(1/328%)/5ms]  0.61  percent/sec. for ramp steps for tiunPercent_1_328 types called in 5ms cycle
//  typedef uint8 tiucSlopePercent;
//#define MAX_tiucSlopePercent (tiucSlopePercent)0x00u
//  typedef struct struct_SlopePercent
//  {
//    tiucSlopePercent ucVal;
//    tieSigQty eQty;
//  }
//  tisSlopePercent;
//
//  typedef uint16 tiunSlopePercent;
//#define MAX_tiunSlopePercent (tiunSlopePercent)MAX_tiucSlopePercent
//  typedef struct struct_SlopePercent_U16
//  {
//    tiunSlopePercent unVal;
//    tieSigQty eQty;
//  }
//  tisSlopePercent_U16;
//
//
//  // [10%/s]
//  typedef uint8 tiucSlopePercent_10;
//#define MAX_tiucSlopePercent_10 (tiucSlopePercent_10)0x00u
//  typedef struct struct_SlopePercent_U8_10
//  {
//    tiucSlopePercent_10 ucVal;
//    tieSigQty eQty;
//  }
//  tisSlopePercent_U8_10;
//
//  // [10%/s]
//  typedef uint16 tiunSlopePercent_10;
//#define MAX_tiunSlopePercent_10 (tiunSlopePercent_10)0x00u
//  typedef struct struct_SlopePercent_U16_10
//  {
//    tiunSlopePercent_10 unVal;
//    tieSigQty eQty;
//  }
//  tisSlopePercent_U16_10;
//
//  // [mA] current
//  typedef uint16 tiunCurrent;
//  typedef struct struct_Current
//  {
//    tiunCurrent unVal;
//    tieSigQty eQty;
//  }
//  tisCurrent;
//
//  // [14.58mA] current (0..1200mA = 0..82)
//  typedef uint8 tiucCurrent_14p58;
//
//  // [mV] voltage
//  typedef uint16 tiunVoltage_mV;
//  typedef struct struct_Voltage
//  {
//    tiunVoltage_mV unVal;
//    tieSigQty eQty;
//  }
//  tisVoltage_mV;
//
//  typedef struct struct_SupplyStatus
//  {
//    tiunVoltage_mV unVal;
//    boolean        boRangeOk;
//  }
//  tisSupplyStatus;
//
//  // [1/10V] voltage
//  typedef uint8  tiucVoltage_1_10V;
//  typedef uint16 tiunVoltage_1_10V;
//
//  typedef struct struct_Voltage8_1_10V
//  {
//    tiucVoltage_1_10V ucVal;
//    tieSigQty eQty;
//  }
//  tisVoltage8_1_10V;
//
//  typedef struct struct_Voltage16_1_10V
//  {
//    tiunVoltage_1_10V unVal;
//    tieSigQty eQty;
//  }
//  tisVoltage16_1_10V;
//
//  // setpoint for output voltage regulation (desired booster output voltage)
//  typedef  tiunVoltage_1_10V  tiunBoostcSetUout;
//  typedef  tisVoltage16_1_10V tisBoostcSetUout;
//
//
//  // [degrees C] temperature
//  typedef uint8  ucTemperatureRaw;
//  typedef uint8  tiucTemperature; // 0..255 = -40..215 degrees C
//  typedef struct struct_Temperature
//  {
//    tiucTemperature ucVal;
//    tieSigQty eQty;
//  }
//  tisTemperature;
//
//
//  typedef uint16  tinTemperature_1_10C; // -3276,8 ..3276,7 degrees C
//  typedef struct struct_Temperature16_1_10C
//  {
//    tinTemperature_1_10C nVal;
//    tieSigQty eQty;
//  }
//  tisTemperature16_1_10C;
//
//
//  // animation mode
//  typedef uint8 tiucAnimationMode;
//#define DEFAULT_tiucAnimationMode (tiucAnimationMode)0x00u
//  typedef struct struct_AnimationMode
//  {
//    tiucAnimationMode ucVal;
//    tieSigQty eQty;
//  }
//  tisAnimationMode;
//
//
//  // animation status
//  typedef enum enum_AnimationStatus
//  {
//    ANIMATION_STATE_OFF = 0,
//    ANIMATION_STATE_ONGOING = 1,
//    ANIMATION_STATE_ON = 2,
//    ANIMATION_STATE_SNA = 3
//  }
//  tieAnimationStatus;
//
//
//  // animation cycle status
//  typedef enum enum_AnimationCycleStatus
//  {
//    ANIMATION_STATE_CYCLE_OFF = 0,
//    ANIMATION_STATE_CYCLE_ON_ONPERIOD = 1,
//    ANIMATION_STATE_CYCLE_ON_OFFPERIOD = 2,
//    ANIMATION_STATE_CYCLE_SNA = 3
//  }
//  tieAnimationCycleStatus;
//
//
//  // limitation status (derating)
//  typedef enum enum_LimitStatus
//  {
//    LIMIT_INACTIVE = 0,
//    LIMIT_ACTIVE_PWM = 1,
//    LIMIT_ACTIVE_CURRENT = 2,
//    LIMIT_ACTIVE_PWM_CURRENT = 3,
//    LIMIT_UNUSED4 = 4,
//    LIMIT_UNUSED5 = 5,
//    LIMIT_UNUSED6 = 6,
//    LIMIT_SNA = 7
//  }
//  tieLimitStatus;
//
//#define DEFAULT_tieLimitStatus (tieLimitStatus)S_INACTIVE
//  typedef struct struct_LimitStatus
//  {
//    tieLimitStatus eVal;
//    tieSigQty eQty;
//  }
//  tisLimitStatus;
//
//
//  typedef struct struct_TempDerating
//  {
//    tiucTemperature  ucStartTempDerating;
//    tiucTemperature  ucMaxTempDerating;
//    tiucPercent      ucRelBrightnessDerating;     // (% relative to nominal brightness)
//    tieSigQty        eQty;
//  }
//  tisTempDerating;
//
//
//  typedef struct struct_TempBand
//  {
//    uint8      ucMin;
//    uint8      ucMax;
//    //tieSigQty  eQty; TODO
//  }
//  tisTempBand;
//
//  // digital value (Bcm interface)
//  typedef enum enum_DigitalBcm
//  {
//    D_OFF = 0,
//    D_ON = 1,
//    D_UNUSED = 2,
//    D_SNA = 3
//  }
//  tieDigitalBcm;
//
//
//#define MOTSTATE_ActAngleNotAvail 0x7FF
//
//  /*******************************************************************************
//  * types
//  *******************************************************************************/
//
//  // -----------------------------------------------------------------------------------------
//  // Control commands
//
//  // SIGNALS:  CTR_SPN_ENG_VE_LH, CTR_SPN_ENG_VE_RH
//  //           CTR_SPN_ENG_HRZTL_LH, CTR_SPN_ENG_HRZTL_RH
//  typedef enum                            // Bezeichnungen laut Nachrichtenkatalog
//  {                                       // -------------------------------------
//    CtrlStp_eCtrl_Init = 0,      // no description available
//    CtrlStp_eCtrl_PosWork = 1,      // normal operation
//    CtrlStp_eCtrl_PosInactive = 2,      // freeze position
//    CtrlStp_eCtrl_ReferenceRun = 3,      // do reference run
//    CtrlStp_eCtrl_PosSleep = 4,      // goto sleep position
//    CtrlStp_eCtrl_PosSafety = 5,      // goto safety position
//    CtrlStp_eCtrl_SoftStop = 6,      // soft stop (hold)
//    CtrlStp_eCtrl_Invalid = 15       // signal empty, sending out of service
//                                     // all other values: reserved
//  } tCtrlMot_eCtrl;
//
//  // storage to hold tCtrlStp_eCtrl as well as additional info, e.g. stepper low temp
//  typedef struct
//  {
//    uint32  Ctrl : 4;  // for storage of tCtrlMot_eCtrl
//    uint32  Lowtemp : 1;  // low temperature provided by AppM
//    uint32  Timeout : 1;  // signal timeout on CAN
//    uint32  Enable : 1;
//    uint32  CanBusOff : 1;  // BusOff (CAN bus)
//
//    uint32  SttWarn : 1;  // start/stop: warning for impending start of engine
//    uint32  RefRequest : 1;  // request ref-run
//    uint32  PowerModeIO : 1;  // power mode IngnitionOn_2, Running_2, ...
//    uint32  PowerPackSS : 1;  // power pack status starting
//    uint32  Reserved : 5;
//  }
//  tMotCtrl0_CtrlBit;
//
//  typedef uint32 tiulBit32;
//  typedef union
//  {
//    tiulBit32          Bit32;
//    tMotCtrl0_CtrlBit  Bit;
//  }
//  tMotCtrl0_Detail;
//
//  // -----------------------------------------------------------------------------------------
//  // Status information
//
//  // CAN Frames: ST_LP_EX_SPN_LH, ST_LP_EX_SPN_RH
//  // // CAN Signals ST_PO_SPN_VE_LH, ST_PO_SPN_VE_RH
//  // #define CTRLSTP_ActLwrValInvalid   0x0FFF
//  // 
//  // // CAN Signals ST_PO_SPN_HRZTL_LH, ST_PO_SPN_HRZTL_RH
//  // #define CTRLSTP_ActKlValInvalid   0x0FFF
//
//  // #define PRJ_TYP_Lr06 (1u)
//
//  // CAN Signals ST_SPN_ENG_LH_VE, ST_SPN_ENG_RH_VE, ST_SPN_ENG_LH_HRZTL, ST_SPN_ENG_RH_HRZTL
//  typedef enum
//  {
//    // #ifndef PRJ_TYP_Lr06 && (!defined PRJ_TYP_Gm22 && !defined PRJ_TYP_Ps60)
//    //  CtrlStp_eMainState_NoSupport     =  0,  // Keine Beschreibung vorhanden.
//    //  CtrlStp_eMainState_Init          =  1,  // Initialisierung inklusive Referenzlauf
//    //  CtrlStp_eMainState_Normal        =  2,  // Normalbetrieb
//    //  CtrlStp_eMainState_NormOffset    =  3,  // Normalbetrieb mit Offset von Lichtslave
//    //  CtrlStp_eMainState_ErrNotGlaring =  4,  // Funktionsfehler, nicht blendend
//    //  CtrlStp_eMainState_NoInit        =  5,  // Motor nicht referenziert
//    //  CtrlStp_eMainState_ErrGlaring    =  6,  // Funktionsfehler blendend
//    //  CtrlStp_eMainState_NormSafety    =  7,  // Normalbetrieb mit SafetyPos-Anforderung vom Master
//    //  CtrlStp_eMainState_Invalid       = 15   // Sendefunktion nicht in Betrieb
//    // #else                                    // only 2 bits are used:
//    CtrlStp_eMainState_2OffUnRef = 0,  // Off after Init (power on) or UnRef after StepLoss
//    CtrlStp_eMainState_2Referencing = 1,  // Referenzlauf
//    CtrlStp_eMainState_2Normal = 2,  // Stopped (Hold) or Moving (Run)
//    CtrlStp_eMainState_2Error = 3   // Fehler
//                                    // #endif
//  }
//  tMotState0_eMainState;
//
//  // bytewise access
//  typedef struct
//  {
//    tMotState0_eMainState  ucMainState;    // Main status
//    uint8  ucReserved2;
//    uint8  ucReserved3;
//    uint8  ucReserved4;
//  }
//  tMotState0_StateGroup;
//
//  typedef union
//  {
//    tMotState0_StateGroup Group;
//    //tLwrState0Bit   Bit; // no bits available
//    tiulBit32       Bit32;
//  }
//  tMotState0_Detail;
//

#endif // __CDDSTPTYPES_H__

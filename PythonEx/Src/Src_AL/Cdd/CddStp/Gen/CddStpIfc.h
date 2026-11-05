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
/// \file  CddStpIfc.h
///
/// \brief
///
/// \author J. Kling ALRT-EES6 (f84304b)
///
//-----------------------------------------------------------------------------

#ifndef CDDSTPIFC_H
#define CDDSTPIFC_H

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/

// #include <Alx1_div/Platform_Types_HCM.h>
// #include <CddStpTypes.h>
#include <RteCommonTypes.h>
//
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ //*****************************************************************************
/*Platform_Types_HCM.h*/ // (C) Automotive Lighting Reutlingen GmbH
/*Platform_Types_HCM.h*/ //     Tuebinger Strasse 123, 72762 Reutlingen, Germany
/*Platform_Types_HCM.h*/ //
/*Platform_Types_HCM.h*/ // Automotive Lighting Reutlingen GmbH owns all the rights to this work.
/*Platform_Types_HCM.h*/ // This work shall not be copied, reproduced, used, modified, transferred
/*Platform_Types_HCM.h*/ // or its information shall not be disclosed without the prior written
/*Platform_Types_HCM.h*/ // authorization of Automotive Lighting Reutlingen GmbH.
/*Platform_Types_HCM.h*/ //*****************************************************************************
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ //-----------------------------------------------------------------------------
/*Platform_Types_HCM.h*/ /// \file   Alx1_div/Platform_Types_HCM.h
/*Platform_Types_HCM.h*/ ///
/*Platform_Types_HCM.h*/ /// \brief  Alx1 - Generic AUTOSAR types and other generic system types
/*Platform_Types_HCM.h*/ ///
/*Platform_Types_HCM.h*/ /// \descr
/*Platform_Types_HCM.h*/ ///
/*Platform_Types_HCM.h*/ /// \author  (ksc2rt)
/*Platform_Types_HCM.h*/ ///         mailTo:       christopher.kormanyos@al-lighting.com
/*Platform_Types_HCM.h*/ //-----------------------------------------------------------------------------
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ #ifndef _PLATFORM_TYPES_2013_01_02_H_
/*Platform_Types_HCM.h*/ #define _PLATFORM_TYPES_2013_01_02_H_
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ // *****************************************************************************
/*Platform_Types_HCM.h*/ // includes
/*Platform_Types_HCM.h*/ // *****************************************************************************
/*Platform_Types_HCM.h*/ #include <Dem.h>
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ // error quality
/*Platform_Types_HCM.h*/ typedef enum enum_ErrQty
/*Platform_Types_HCM.h*/ {
/*Platform_Types_HCM.h*/   E_SNA = 0,
/*Platform_Types_HCM.h*/   E_FAILED = 1,
/*Platform_Types_HCM.h*/   E_PASSED = 2,
/*Platform_Types_HCM.h*/   E_TIMEOUT = 3
/*Platform_Types_HCM.h*/ }
/*Platform_Types_HCM.h*/ tieErrQty;
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ // system mode
/*Platform_Types_HCM.h*/ typedef enum enum_SysMode
/*Platform_Types_HCM.h*/ {
/*Platform_Types_HCM.h*/   SYS_MODE_NORMAL = 0,
/*Platform_Types_HCM.h*/   SYS_MODE_INVALID = 1,
/*Platform_Types_HCM.h*/   SYS_MODE_ERROR = 2,
/*Platform_Types_HCM.h*/   SYS_MODE_PBL = 3, // primary boot loader flash mode (PBL)
/*Platform_Types_HCM.h*/   SYS_MODE_STARTUP = 4, // ECU startup
/*Platform_Types_HCM.h*/   SYS_MODE_PRODUCTION = 5, // ECU factory test (Eft/PAV)
/*Platform_Types_HCM.h*/   SYS_MODE_PARAMETER = 6, // parameter flash mode
/*Platform_Types_HCM.h*/   SYS_MODE_ANALYSIS = 7, // Analyze mode (normal mode with RDM)
/*Platform_Types_HCM.h*/   SYS_MODE_SHUTDOWN = 8
/*Platform_Types_HCM.h*/ }
/*Platform_Types_HCM.h*/ tieSysMode;
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/  //typedef unsigned char tieSigQty;
/*Platform_Types_HCM.h*/  typedef unsigned char UInt8;
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ // [%] percent
/*Platform_Types_HCM.h*/ typedef uint8 tiucPercent;
/*Platform_Types_HCM.h*/ #define MAX_tiucPercent (tiucPercent)100u
/*Platform_Types_HCM.h*/ #define MIN_tiucPercent (tiucPercent)0u
/*Platform_Types_HCM.h*/ typedef struct struct_Percent
/*Platform_Types_HCM.h*/ {
/*Platform_Types_HCM.h*/   tiucPercent ucVal;
/*Platform_Types_HCM.h*/   tieSigQty eQty;
/*Platform_Types_HCM.h*/ }
/*Platform_Types_HCM.h*/ tisPercent;
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ // [100/128%] percent (100% = 0x80)
/*Platform_Types_HCM.h*/ typedef uint8 tiucPercent_100_128;
/*Platform_Types_HCM.h*/ #define MAX_tiucPercent_100_128 (tiucPercent_100_128)0x80U
/*Platform_Types_HCM.h*/ #define MIN_tiucPercent_100_128 (tiucPercent_100_128)0x00U
/*Platform_Types_HCM.h*/ typedef struct struct_Percent_100_128
/*Platform_Types_HCM.h*/ {
/*Platform_Types_HCM.h*/   tiucPercent_100_128 ucVal;
/*Platform_Types_HCM.h*/   tieSigQty eQty;
/*Platform_Types_HCM.h*/ }
/*Platform_Types_HCM.h*/ tisPercent_100_128;
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ // [1/2%] percent (100% = 200)
/*Platform_Types_HCM.h*/ typedef uint8 tiucPercent_1_2;
/*Platform_Types_HCM.h*/ #define MAX_tiucPercent_1_2 (tiucPercent_1_2)200U
/*Platform_Types_HCM.h*/ #define MIN_tiucPercent_1_2 (tiucPercent_1_2)0U
/*Platform_Types_HCM.h*/ typedef struct struct_Percent_1_2
/*Platform_Types_HCM.h*/ {
/*Platform_Types_HCM.h*/   tiucPercent_1_2 ucVal;
/*Platform_Types_HCM.h*/   tieSigQty eQty;
/*Platform_Types_HCM.h*/ }
/*Platform_Types_HCM.h*/ tisPercent_1_2;
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ // [1/10%] percent
/*Platform_Types_HCM.h*/ typedef uint16 tiunPercent_1_10;
/*Platform_Types_HCM.h*/ typedef struct struct_Percent_1_10
/*Platform_Types_HCM.h*/ {
/*Platform_Types_HCM.h*/   tiunPercent_1_10 unVal;
/*Platform_Types_HCM.h*/   tieSigQty eQty;
/*Platform_Types_HCM.h*/ }
/*Platform_Types_HCM.h*/ tisPercent_1_10;
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ // [100/32768%] percent (100% = 0x8000)
/*Platform_Types_HCM.h*/ typedef uint16 tiunPercent_1_328;
/*Platform_Types_HCM.h*/ #define MAX_tiunPercent_1_328 (tiunPercent_1_328)0x8000U
/*Platform_Types_HCM.h*/ #define MIN_tiunPercent_1_328 (tiunPercent_1_328)0x0000U
/*Platform_Types_HCM.h*/ typedef struct struct_Percent_1_328
/*Platform_Types_HCM.h*/ {
/*Platform_Types_HCM.h*/   tiunPercent_1_328 unVal;
/*Platform_Types_HCM.h*/   tieSigQty eQty;
/*Platform_Types_HCM.h*/ }
/*Platform_Types_HCM.h*/ tisPercent_1_328;
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ // [(1/328%)/20ms] 0.15  percent/sec. for ramp steps for tiunPercent_1_328 types called in 20ms cycle 
/*Platform_Types_HCM.h*/ // [(1/328%)/10ms] 0.305 percent/sec. for ramp steps for tiunPercent_1_328 types called in 10ms cycle 
/*Platform_Types_HCM.h*/ // [(1/328%)/5ms]  0.61  percent/sec. for ramp steps for tiunPercent_1_328 types called in 5ms cycle
/*Platform_Types_HCM.h*/ typedef uint8 tiucSlopePercent;
/*Platform_Types_HCM.h*/ #define MAX_tiucSlopePercent (tiucSlopePercent)0x00u
/*Platform_Types_HCM.h*/ typedef struct struct_SlopePercent
/*Platform_Types_HCM.h*/ {
/*Platform_Types_HCM.h*/   tiucSlopePercent ucVal;
/*Platform_Types_HCM.h*/   tieSigQty eQty;
/*Platform_Types_HCM.h*/ }
/*Platform_Types_HCM.h*/ tisSlopePercent;
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ typedef uint16 tiunSlopePercent;
/*Platform_Types_HCM.h*/ #define MAX_tiunSlopePercent (tiunSlopePercent)MAX_tiucSlopePercent
/*Platform_Types_HCM.h*/ typedef struct struct_SlopePercent_U16
/*Platform_Types_HCM.h*/ {
/*Platform_Types_HCM.h*/   tiunSlopePercent unVal;
/*Platform_Types_HCM.h*/   tieSigQty eQty;
/*Platform_Types_HCM.h*/ }
/*Platform_Types_HCM.h*/ tisSlopePercent_U16;
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ // [10%/s]
/*Platform_Types_HCM.h*/ typedef uint8 tiucSlopePercent_10;
/*Platform_Types_HCM.h*/ #define MAX_tiucSlopePercent_10 (tiucSlopePercent_10)0x00u
/*Platform_Types_HCM.h*/ typedef struct struct_SlopePercent_U8_10
/*Platform_Types_HCM.h*/ {
/*Platform_Types_HCM.h*/   tiucSlopePercent_10 ucVal;
/*Platform_Types_HCM.h*/   tieSigQty eQty;
/*Platform_Types_HCM.h*/ }
/*Platform_Types_HCM.h*/ tisSlopePercent_U8_10;
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ // [10%/s]
/*Platform_Types_HCM.h*/ typedef uint16 tiunSlopePercent_10;
/*Platform_Types_HCM.h*/ #define MAX_tiunSlopePercent_10 (tiunSlopePercent_10)0x00u
/*Platform_Types_HCM.h*/ typedef struct struct_SlopePercent_U16_10
/*Platform_Types_HCM.h*/ {
/*Platform_Types_HCM.h*/   tiunSlopePercent_10 unVal;
/*Platform_Types_HCM.h*/   tieSigQty eQty;
/*Platform_Types_HCM.h*/ }
/*Platform_Types_HCM.h*/ tisSlopePercent_U16_10;
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ // [mA] current
/*Platform_Types_HCM.h*/ typedef uint16 tiunCurrent;
/*Platform_Types_HCM.h*/ typedef struct struct_Current
/*Platform_Types_HCM.h*/ {
/*Platform_Types_HCM.h*/   tiunCurrent unVal;
/*Platform_Types_HCM.h*/   tieSigQty eQty;
/*Platform_Types_HCM.h*/ }
/*Platform_Types_HCM.h*/ tisCurrent;
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ // [14.58mA] current (0..1200mA = 0..82)
/*Platform_Types_HCM.h*/ typedef uint8 tiucCurrent_14p58;
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ // [mV] voltage
/*Platform_Types_HCM.h*/ typedef uint16 tiunVoltage_mV;
/*Platform_Types_HCM.h*/ typedef struct struct_Voltage
/*Platform_Types_HCM.h*/ {
/*Platform_Types_HCM.h*/   tiunVoltage_mV unVal;
/*Platform_Types_HCM.h*/   tieSigQty eQty;
/*Platform_Types_HCM.h*/ }
/*Platform_Types_HCM.h*/ tisVoltage_mV;
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ typedef struct struct_SupplyStatus
/*Platform_Types_HCM.h*/ {
/*Platform_Types_HCM.h*/   tiunVoltage_mV unVal;
/*Platform_Types_HCM.h*/   boolean        boRangeOk;
/*Platform_Types_HCM.h*/ }
/*Platform_Types_HCM.h*/ tisSupplyStatus;
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ // [1/10V] voltage
/*Platform_Types_HCM.h*/ typedef uint8  tiucVoltage_1_10V;
/*Platform_Types_HCM.h*/ typedef uint16 tiunVoltage_1_10V;
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ typedef struct struct_Voltage8_1_10V
/*Platform_Types_HCM.h*/ {
/*Platform_Types_HCM.h*/   tiucVoltage_1_10V ucVal;
/*Platform_Types_HCM.h*/   tieSigQty eQty;
/*Platform_Types_HCM.h*/ }
/*Platform_Types_HCM.h*/ tisVoltage8_1_10V;
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ typedef struct struct_Voltage16_1_10V
/*Platform_Types_HCM.h*/ {
/*Platform_Types_HCM.h*/   tiunVoltage_1_10V unVal;
/*Platform_Types_HCM.h*/   tieSigQty eQty;
/*Platform_Types_HCM.h*/ }
/*Platform_Types_HCM.h*/ tisVoltage16_1_10V;
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ // setpoint for output voltage regulation (desired booster output voltage)
/*Platform_Types_HCM.h*/ typedef  tiunVoltage_1_10V  tiunBoostcSetUout;
/*Platform_Types_HCM.h*/ typedef  tisVoltage16_1_10V tisBoostcSetUout;
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ // [degrees C] temperature
/*Platform_Types_HCM.h*/ typedef uint8  ucTemperatureRaw;
/*Platform_Types_HCM.h*/ typedef uint8  tiucTemperature; // 0..255 = -40..215 degrees C
/*Platform_Types_HCM.h*/ typedef struct struct_Temperature
/*Platform_Types_HCM.h*/ {
/*Platform_Types_HCM.h*/   tiucTemperature ucVal;
/*Platform_Types_HCM.h*/   tieSigQty eQty;
/*Platform_Types_HCM.h*/ }
/*Platform_Types_HCM.h*/ tisTemperature;
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ typedef uint16  tinTemperature_1_10C; // -3276,8 ..3276,7 degrees C
/*Platform_Types_HCM.h*/ typedef struct struct_Temperature16_1_10C
/*Platform_Types_HCM.h*/ {
/*Platform_Types_HCM.h*/   tinTemperature_1_10C nVal;
/*Platform_Types_HCM.h*/   tieSigQty eQty;
/*Platform_Types_HCM.h*/ }
/*Platform_Types_HCM.h*/ tisTemperature16_1_10C;
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ // animation mode
/*Platform_Types_HCM.h*/ typedef uint8 tiucAnimationMode;
/*Platform_Types_HCM.h*/ #define DEFAULT_tiucAnimationMode (tiucAnimationMode)0x00u
/*Platform_Types_HCM.h*/ typedef struct struct_AnimationMode
/*Platform_Types_HCM.h*/ {
/*Platform_Types_HCM.h*/   tiucAnimationMode ucVal;
/*Platform_Types_HCM.h*/   tieSigQty eQty;
/*Platform_Types_HCM.h*/ }
/*Platform_Types_HCM.h*/ tisAnimationMode;
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ // animation status
/*Platform_Types_HCM.h*/ typedef enum enum_AnimationStatus
/*Platform_Types_HCM.h*/ {
/*Platform_Types_HCM.h*/   ANIMATION_STATE_OFF = 0,
/*Platform_Types_HCM.h*/   ANIMATION_STATE_ONGOING = 1,
/*Platform_Types_HCM.h*/   ANIMATION_STATE_ON = 2,
/*Platform_Types_HCM.h*/   ANIMATION_STATE_SNA = 3
/*Platform_Types_HCM.h*/ }
/*Platform_Types_HCM.h*/ tieAnimationStatus;
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ // animation cycle status
/*Platform_Types_HCM.h*/ typedef enum enum_AnimationCycleStatus
/*Platform_Types_HCM.h*/ {
/*Platform_Types_HCM.h*/   ANIMATION_STATE_CYCLE_OFF = 0,
/*Platform_Types_HCM.h*/   ANIMATION_STATE_CYCLE_ON_ONPERIOD = 1,
/*Platform_Types_HCM.h*/   ANIMATION_STATE_CYCLE_ON_OFFPERIOD = 2,
/*Platform_Types_HCM.h*/   ANIMATION_STATE_CYCLE_SNA = 3
/*Platform_Types_HCM.h*/ }
/*Platform_Types_HCM.h*/ tieAnimationCycleStatus;
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ // limitation status (derating)
/*Platform_Types_HCM.h*/ typedef enum enum_LimitStatus
/*Platform_Types_HCM.h*/ {
/*Platform_Types_HCM.h*/   LIMIT_INACTIVE = 0,
/*Platform_Types_HCM.h*/   LIMIT_ACTIVE_PWM = 1,
/*Platform_Types_HCM.h*/   LIMIT_ACTIVE_CURRENT = 2,
/*Platform_Types_HCM.h*/   LIMIT_ACTIVE_PWM_CURRENT = 3,
/*Platform_Types_HCM.h*/   LIMIT_UNUSED4 = 4,
/*Platform_Types_HCM.h*/   LIMIT_UNUSED5 = 5,
/*Platform_Types_HCM.h*/   LIMIT_UNUSED6 = 6,
/*Platform_Types_HCM.h*/   LIMIT_SNA = 7
/*Platform_Types_HCM.h*/ }
/*Platform_Types_HCM.h*/ tieLimitStatus;
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ #define DEFAULT_tieLimitStatus (tieLimitStatus)S_INACTIVE
/*Platform_Types_HCM.h*/ typedef struct struct_LimitStatus
/*Platform_Types_HCM.h*/ {
/*Platform_Types_HCM.h*/   tieLimitStatus eVal;
/*Platform_Types_HCM.h*/   tieSigQty eQty;
/*Platform_Types_HCM.h*/ }
/*Platform_Types_HCM.h*/ tisLimitStatus;
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ typedef struct struct_TempDerating
/*Platform_Types_HCM.h*/ {
/*Platform_Types_HCM.h*/   tiucTemperature  ucStartTempDerating;
/*Platform_Types_HCM.h*/   tiucTemperature  ucMaxTempDerating;
/*Platform_Types_HCM.h*/   tiucPercent      ucRelBrightnessDerating;     // (% relative to nominal brightness)
/*Platform_Types_HCM.h*/   tieSigQty        eQty;
/*Platform_Types_HCM.h*/ }
/*Platform_Types_HCM.h*/ tisTempDerating;
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ typedef struct struct_TempBand
/*Platform_Types_HCM.h*/ {
/*Platform_Types_HCM.h*/   uint8      ucMin;
/*Platform_Types_HCM.h*/   uint8      ucMax;
/*Platform_Types_HCM.h*/   //tieSigQty  eQty; TODO
/*Platform_Types_HCM.h*/ }
/*Platform_Types_HCM.h*/ tisTempBand;
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ // digital value (Bcm interface)
/*Platform_Types_HCM.h*/ typedef enum enum_DigitalBcm
/*Platform_Types_HCM.h*/ {
/*Platform_Types_HCM.h*/   D_OFF = 0,
/*Platform_Types_HCM.h*/   D_ON = 1,
/*Platform_Types_HCM.h*/   D_UNUSED = 2,
/*Platform_Types_HCM.h*/   D_SNA = 3
/*Platform_Types_HCM.h*/ }
/*Platform_Types_HCM.h*/ tieDigitalBcm;
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ #define MOTSTATE_ActAngleNotAvail 0x7FF
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ // /*******************************************************************************
/*Platform_Types_HCM.h*/ // * types
/*Platform_Types_HCM.h*/ // *******************************************************************************/
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ // -----------------------------------------------------------------------------------------
/*Platform_Types_HCM.h*/ // Control commands
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ // SIGNALS:  CTR_SPN_ENG_VE_LH, CTR_SPN_ENG_VE_RH
/*Platform_Types_HCM.h*/ //           CTR_SPN_ENG_HRZTL_LH, CTR_SPN_ENG_HRZTL_RH
/*Platform_Types_HCM.h*/ typedef enum                            // Bezeichnungen laut Nachrichtenkatalog
/*Platform_Types_HCM.h*/ {                                       // -------------------------------------
/*Platform_Types_HCM.h*/   CtrlStp_eCtrl_Init = 0,      // no description available
/*Platform_Types_HCM.h*/   CtrlStp_eCtrl_PosWork = 1,      // normal operation
/*Platform_Types_HCM.h*/   CtrlStp_eCtrl_PosInactive = 2,      // freeze position
/*Platform_Types_HCM.h*/   CtrlStp_eCtrl_ReferenceRun = 3,      // do reference run
/*Platform_Types_HCM.h*/   CtrlStp_eCtrl_PosSleep = 4,      // goto sleep position
/*Platform_Types_HCM.h*/   CtrlStp_eCtrl_PosSafety = 5,      // goto safety position
/*Platform_Types_HCM.h*/   CtrlStp_eCtrl_SoftStop = 6,      // soft stop (hold)
/*Platform_Types_HCM.h*/   CtrlStp_eCtrl_Invalid = 15       // signal empty, sending out of service
/*Platform_Types_HCM.h*/                                    // all other values: reserved
/*Platform_Types_HCM.h*/ } tCtrlMot_eCtrl;
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ // storage to hold tCtrlStp_eCtrl as well as additional info, e.g. stepper low temp
/*Platform_Types_HCM.h*/ typedef struct
/*Platform_Types_HCM.h*/ {
/*Platform_Types_HCM.h*/   uint32  Ctrl : 4;  // for storage of tCtrlMot_eCtrl
/*Platform_Types_HCM.h*/   uint32  Lowtemp : 1;  // low temperature provided by AppM
/*Platform_Types_HCM.h*/   uint32  Timeout : 1;  // signal timeout on CAN
/*Platform_Types_HCM.h*/   uint32  Enable : 1;
/*Platform_Types_HCM.h*/   uint32  CanBusOff : 1;  // BusOff (CAN bus)
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/   uint32  SttWarn : 1;  // start/stop: warning for impending start of engine
/*Platform_Types_HCM.h*/   uint32  RefRequest : 1;  // request ref-run
/*Platform_Types_HCM.h*/   uint32  PowerModeIO : 1;  // power mode IngnitionOn_2, Running_2, ...
/*Platform_Types_HCM.h*/   uint32  PowerPackSS : 1;  // power pack status starting
/*Platform_Types_HCM.h*/   uint32  Reserved : 5;
/*Platform_Types_HCM.h*/ }
/*Platform_Types_HCM.h*/ tMotCtrl0_CtrlBit;
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ typedef uint32 tiulBit32;
/*Platform_Types_HCM.h*/ typedef union
/*Platform_Types_HCM.h*/ {
/*Platform_Types_HCM.h*/   tiulBit32          Bit32;
/*Platform_Types_HCM.h*/   tMotCtrl0_CtrlBit  Bit;
/*Platform_Types_HCM.h*/ }
/*Platform_Types_HCM.h*/ tMotCtrl0_Detail;
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ // -----------------------------------------------------------------------------------------
/*Platform_Types_HCM.h*/ // Status information
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ // CAN Frames: ST_LP_EX_SPN_LH, ST_LP_EX_SPN_RH
/*Platform_Types_HCM.h*/ // // CAN Signals ST_PO_SPN_VE_LH, ST_PO_SPN_VE_RH
/*Platform_Types_HCM.h*/ // #define CTRLSTP_ActLwrValInvalid   0x0FFF
/*Platform_Types_HCM.h*/ // 
/*Platform_Types_HCM.h*/ // // CAN Signals ST_PO_SPN_HRZTL_LH, ST_PO_SPN_HRZTL_RH
/*Platform_Types_HCM.h*/ // #define CTRLSTP_ActKlValInvalid   0x0FFF
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ // #define PRJ_TYP_Lr06 (1u)
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ // CAN Signals ST_SPN_ENG_LH_VE, ST_SPN_ENG_RH_VE, ST_SPN_ENG_LH_HRZTL, ST_SPN_ENG_RH_HRZTL
/*Platform_Types_HCM.h*/ typedef enum
/*Platform_Types_HCM.h*/ {
/*Platform_Types_HCM.h*/   // #ifndef PRJ_TYP_Lr06 && (!defined PRJ_TYP_Gm22 && !defined PRJ_TYP_Ps60)
/*Platform_Types_HCM.h*/   //  CtrlStp_eMainState_NoSupport     =  0,  // Keine Beschreibung vorhanden.
/*Platform_Types_HCM.h*/   //  CtrlStp_eMainState_Init          =  1,  // Initialisierung inklusive Referenzlauf
/*Platform_Types_HCM.h*/   //  CtrlStp_eMainState_Normal        =  2,  // Normalbetrieb
/*Platform_Types_HCM.h*/   //  CtrlStp_eMainState_NormOffset    =  3,  // Normalbetrieb mit Offset von Lichtslave
/*Platform_Types_HCM.h*/   //  CtrlStp_eMainState_ErrNotGlaring =  4,  // Funktionsfehler, nicht blendend
/*Platform_Types_HCM.h*/   //  CtrlStp_eMainState_NoInit        =  5,  // Motor nicht referenziert
/*Platform_Types_HCM.h*/   //  CtrlStp_eMainState_ErrGlaring    =  6,  // Funktionsfehler blendend
/*Platform_Types_HCM.h*/   //  CtrlStp_eMainState_NormSafety    =  7,  // Normalbetrieb mit SafetyPos-Anforderung vom Master
/*Platform_Types_HCM.h*/   //  CtrlStp_eMainState_Invalid       = 15   // Sendefunktion nicht in Betrieb
/*Platform_Types_HCM.h*/   // #else                                    // only 2 bits are used:
/*Platform_Types_HCM.h*/   CtrlStp_eMainState_2OffUnRef = 0,  // Off after Init (power on) or UnRef after StepLoss
/*Platform_Types_HCM.h*/   CtrlStp_eMainState_2Referencing = 1,  // Referenzlauf
/*Platform_Types_HCM.h*/   CtrlStp_eMainState_2Normal = 2,  // Stopped (Hold) or Moving (Run)
/*Platform_Types_HCM.h*/   CtrlStp_eMainState_2Error = 3   // Fehler
/*Platform_Types_HCM.h*/                                   // #endif
/*Platform_Types_HCM.h*/ }
/*Platform_Types_HCM.h*/ tMotState0_eMainState;
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ // bytewise access
/*Platform_Types_HCM.h*/ typedef struct
/*Platform_Types_HCM.h*/ {
/*Platform_Types_HCM.h*/   tMotState0_eMainState  ucMainState;    // Main status
/*Platform_Types_HCM.h*/   uint8  ucReserved2;
/*Platform_Types_HCM.h*/   uint8  ucReserved3;
/*Platform_Types_HCM.h*/   uint8  ucReserved4;
/*Platform_Types_HCM.h*/ }
/*Platform_Types_HCM.h*/ tMotState0_StateGroup;
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ typedef union
/*Platform_Types_HCM.h*/ {
/*Platform_Types_HCM.h*/   tMotState0_StateGroup Group;
/*Platform_Types_HCM.h*/   //tLwrState0Bit   Bit; // no bits available
/*Platform_Types_HCM.h*/   tiulBit32       Bit32;
/*Platform_Types_HCM.h*/ }
/*Platform_Types_HCM.h*/ tMotState0_Detail;
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ 
/*Platform_Types_HCM.h*/ #endif // _PLATFORM_TYPES_2013_01_02_H_















typedef uint32 tiulDiagCmd;
typedef uint8  tiucDiagIndex;
typedef uint8  tiucCntIndex;
typedef uint8  tiucCtrlIndex;
typedef uint8  tiucParaIndex;
typedef uint32 tiulCntCmd;
typedef uint32 tiulCtrlCmd;
typedef uint32 tiulParaCmd;
//typedef uint8  tieSigQty0;
typedef sint16 tinStpPos0;
typedef uint16 tiunStpTmin0;
// aas typedef uint32 tiulBit32;
//typedef enum enum_SigQty
//{
//  SIG_SNA      = 0,
//  SIG_VALID    = 1,
//  SIG_INIT     = 2,
//  SIG_INVALID  = 3,
//  SIG_TIMEOUT  = 4,
//  SIG_DEFAULT  = 5,
//  SIG_DISABLED = 255
//}tieSigQty0;
typedef enum
{
  AfsMCtrStpSp_None            = 0x00,     //No safety position requested
  AfsMCtrStpSp_Freeze          = 0x01,     //Safety freeze //SoftStop
  AfsMCtrStpSp_Pos             = 0x02,     //Safety position
  AfsMCtrStpSp_Reserved        = 0x03      //reserved
} tieAfsMCtrStpSp;
typedef enum
{
  AfsMCtrStpRef_Disabled     = 0x00,       //referencing disabled
  AfsMCtrStpRef_Allowed      = 0x01,       //referencing allowed
  AfsMCtrStpRef_Reserved1    = 0x02,       //reserved
  AfsMCtrStpRef_Reserved2    = 0x03        //reserved
} tieAfsMCtrStpRef;
typedef enum
{
  PowerMode_KeyOut = 0x00,               // No action required
  PowerMode_KeyRecentlyOut = 0x01,       // Outside of accepted range - disable all functionality and raise an invalid message DTC
  PowerMode_KeyApproved_0 = 0x02,        // Outside of accepted range - disable all functionality and raise an invalid message DTC
  PowerMode_PostAccessory_0 = 0x03,      // Outside of accepted range - disable all functionality and raise an invalid message DTC
  PowerMode_Accessory_1 = 0x04,          // No action required
  PowerMode_PostIgnition_1 = 0x05,       // Outside of accepted range - disable all functionality and raise an invalid message DTC
  PowerMode_IgnitionOn_2 = 0x06,         // Carry out Leveling reference run upon entering PM6 Disable IHB / AFS123 functionality
  PowerMode_Running_2 = 0x07,            // Carry out Leveling reference run upon entering PM7 Disable IHB / AFS123 functionality when in PM7 AND the VehicleSpeed is <10km / h
  PowerMode_NotUsed = 0x08,              // Outside of accepted range - disable all functionality and raise an invalid message DTC
  PowerMode_Crank_3 = 0x09               // Leveling motor fixed position to ensure no steps are lost during cranking
} tiePowerMode;
typedef enum
{
  PowerPackStatus_Init = 0x00,                          // Normal functionality
  PowerPackStatus_Awake = 0x01,                         // Normal functionality
  PowerPackStatus_Ready = 0x02,                         // Normal functionality
  PowerPackStatus_PreStarting = 0x03,                   // Leveling motor fixed position to ensure no steps are lost during cranking
  PowerPackStatus_StartingInProgress = 0x04,            // Leveling motor fixed position to ensure no steps are lost during cranking
  PowerPackStatus_Running_Running = 0x05,               // Normal functionality
  PowerPackStatus_Running_Standby = 0x06,               // Normal functionality
  PowerPackStatus_Running_StartingInProgress = 0x07,    // Normal functionality
  PowerPackStatus_Running_RemoteStarted = 0x08,         // Normal functionality
  PowerPackStatus_AfterRun = 0x09,                      // Normal functionality
  PowerPackStatus_NotUsed0 = 0x0A,                      // Normal functionality
  PowerPackStatus_NotUsed1 = 0x0B,                      // Normal functionality
  PowerPackStatus_NotUsed2 = 0x0C,                      // Normal functionality
  PowerPackStatus_NotUsed3 = 0x0D,                      // Normal functionality
  PowerPackStatus_NotUsed4 = 0x0E,                      // Normal functionality
  PowerPackStatus_NotUsed5 = 0x0F                       // Normal functionality
} tiePowerPackStatus;
typedef struct
{
  uint8 ucVoltRng;
} tisVoltRng0;
typedef struct
{
  UInt8 ucData0;
} tisCntData0;
typedef struct
{
  uint8 ucData0;
} tisCtrlData0;
typedef struct
{
  UInt8 ucData0;
} tisParaData0;
typedef struct
{
  UInt8 ucData0;
} tisDiagData0;
typedef struct
{
  tieSigQty eSigQty;
} tisTrigger0;
typedef struct
{
  sint16 nStatStpPosVer;      //Actual Position of Vertical Stepper;(0-1000): 0,01*raw-5;0x3FF = "(invalid)"
  uint8 eStatStpModeVer;      //Actual Operating Mode of Vertical Stepper; tieStatStpMode
  uint8 eStatStpSpVer;        //Safety Position of Vertical Stepper; tieStatStpSp
  uint8 eStatStpTwVer;        //Thermal Warning of Vertical Stepper; tieStatStpTw
} tStatStp;
typedef struct
{
  tStatStp       StatStp;     // Stat stepper signals
  tieSigQty    eStatStpQty;  // Quality factor
} tisActStatStp0;
typedef struct
{
  // Vehicle Info signals from CAN
  uint8 ePowerMode;        //reflects the current  state of the Power Mode Superviser; ePowerMode
  uint8 ePowerModeQF;      //tiePowerModeQF
  uint32 ulGlobalRealTime; //=E/0.1 (seconds) Resolution 0.1 second Range(0000 0000H - FFFF FFFEH) approx. 0 to 13.6 years
  uint8 ucIncarTemp;       //N = E + 40    Resolution 1 °C   Range : -40 °C to + 215 °C
  uint8 ucOutdoorTemp;     //N = E + 40    Resolution 1 °C   Range : -40 °C to + 215 °C
  uint8 ucMECUVoltage;     //N = E / 0.25  Resolution 0.25 V  Range : 0 to 63, 75 V
  uint32 ulTotalDistance;  //N = E Resolution 1 bit = 1 km Range : 0 - 1 000 000 km minimum / 000000H to F4240H

  // Quality factors for vehicle info signals from CAN
  tieSigQty ePowerModeQty;
  tieSigQty eGlobalRealTimeQty;
  tieSigQty eIncarTempQty;
  tieSigQty eOutdoorTempQty;
  tieSigQty eMECUVoltageQty;
  tieSigQty eTotalDistanceQty;
} tisVehInfoMsg;
typedef struct
{
  sint16 nCtrStpTgtVer;   //Control Stepper Target Position [0,01 Deg]
  tieAfsMCtrStpRef eCtrStpRefVer;   //Control Stepper Reference Request; tieAfsMCtrStpRef
  tieAfsMCtrStpSp  eCtrStpSpVer;    //Control Stepper Safety Request; tieAfsMCtrStpSp
  uint8  eCtrStpRstAck;   //Control Stepper Acknowledge Request; tieAfsMCtrStpRstAck
} tAfsMCtrStp;
typedef struct
{
  tAfsMCtrStp    CtrStp;     // Ctr stp signals
  tieSigQty    eCtrStpQty;  // Quality factor
} tisTgtLwr0;
typedef struct
{
  // engine/power condition signals from CAN
  uint8 eMHStopInProgress;         //Eco - Start Stop event is in progress.
  uint8 eMHStopStartStatus;        //Status of the Eco-Start Stop-Start Feature
  uint8 ePowerMode;                //reflects the current  state of the Power Mode Superviser; ePowerMode
  uint8 ePowerModeQF;              //tiePowerModeQF
  tiePowerPackStatus ePowerPackStatus;          //tiePowerPackStatus
  uint8 eABSPwrTrnTorqReq;         //tieABSPwrTrnTorqReq

  // Quality factors for engine/power condition signals from CAN
  tieSigQty eMHStopInProgressQty;
  tieSigQty eMHStopStartStatusQty;
  tieSigQty ePowerModeQty;
  tieSigQty ePowerModeQFQty;
  tieSigQty ePowerPackStatusQty;
  tieSigQty eABSPwrTrnTorqReqQty;
} tisPowerCondMsg;
typedef struct
{
  tinStpPos0 nPos;
  tiunStpTmin0 unTmin;
  tieSigQty eSigQty;
} tisTgtStpSig0;
typedef struct
{
  tinStpPos0 nPos;
} tisActStpSig0;
typedef struct
{
  tiulBit32 sState;
} tisStpState0;



/*******************************************************************************
* Version
*******************************************************************************/


/*******************************************************************************
* definitions
*******************************************************************************/

#define CDDSTP_POSDEVHIST_MAX  (6) // count of AHL position deviation histogram ranges


/*******************************************************************************
* types
*******************************************************************************/

// -----------------------------------------------------------------------------------------

// StepperTemperatureState Interface

typedef enum
{
  CddStp_eTempState_NormTemp   = 0,   // must be 0 (init. value)
  CddStp_eTempState_LowTemp,          // 1
  CddStp_eTempState_HighTemp,         // 2
  CddStp_eTempState_TempIx            // 3 // numbers of temperature index
} tCddStpTempState;


// CtrlFct0 Interface

typedef enum 
{
  CddStp_eCtrlFct0_ModeOff       = 0,   // switch current off
  CddStp_eCtrlFct0_ModeOn        = 1,   // switch current on
  CddStp_eCtrlFct0_ModeStop      = 2,   // stop motor using deceleration ramp
  CddStp_eCtrlFct0_ModeRef       = 3,   // reference run request (as significant type)
  CddStp_eCtrlFct0_ModeRel       = 4,   // positioning mode related to start position
  CddStp_eCtrlFct0_ModeAbs       = 5,   // positioning mode related to reference position

  CddStp_eCtrlFct0_ErrInhibit    = 6,   // suppression of error detection (el. errors and step loss)
  CddStp_eCtrlFct0_ErrActivate   = 7,   // re-activation of error detection

  CddStp_eCtrlFct0_ErrClr        = 8,   // unlock error state
  CddStp_eCtrlFct0_LowTemp       = 9,   // low temperature
  CddStp_eCtrlFct0_GetTempState  = 10,  // get temperature state
  CddStp_eCtrlFct0_SetCARunRef   = 11,  // set run current of next 12 HS to reference current for bump reference run
  CddStp_eCtrlFct0_SetIsReady    = 12,  // set CddStpState IsReady bit
  CddStp_eCtrlFct0_ModeNextRefExtSig = 13,  // request for next step of extended reference run - as significant type
  CddStp_eCtrlFct0_ModeNextRefExtVol = 14,  // request for next step of extended reference run - as volatile type
  CddStp_eCtrlFct0_ClearRefExtVol = 15  // clear any potentially-requested volatile (extended) reference run
} tCddStpCtrlFct0_Cmd;

typedef struct
{
  boolean  boErrInhibit;
} tCddStpCtrlFct0_ErrInhibit;

typedef struct
{
  boolean  boLT;
} tCddStpCtrlFct0_LowTemp;

typedef struct
{
  boolean  boSoftStop;
} tCddStpCtrlFct0_SoftStop;

typedef struct
{
  boolean  boDem;
} tCddStpCtrlFct0_Dem;

typedef struct
{
  tCddStpTempState  eTemp;
} tCddStpCtrlFct0_GetTempState;


// common argument/return buffer type
typedef union
{
  tisCtrlData0                   sCtrlData;
  tCddStpCtrlFct0_ErrInhibit     ErrInhibit;
  tCddStpCtrlFct0_LowTemp        LowTemp;
  tCddStpCtrlFct0_GetTempState   GetTempState;
  tCddStpCtrlFct0_SoftStop       SoftStop;
  tCddStpCtrlFct0_Dem            Dem;
}
tCddStpCtrlFct0_DataBuffer;


// -----------------------------------------------------------------------------------------
// CntFct0 Interface

typedef enum 
{
  CddStp_eCntCmd_GetHsCnt            = 0,   // get half step count
  CddStp_eCntCmd_GetIrunTime         = 1,   // get Irun  time in fast timer ticks
  CddStp_eCntCmd_GetStpOnTime        = 2,   // get StpOn time in OS counter ticks
  CddStp_eCntCmd_GetRefStartCnt      = 3,   // get count of started of reference runs
  CddStp_eCntCmd_GetIsRefCnt         = 4,   // get count of correct ended reference runs
  CddStp_eCntCmd_GetKlPosDevHistCnts = 5,   // get KL position deviation histogram counters
  CddStp_eCntCmd_GetLastDeviation    = 6    // get Last Deviation 
} tCddStpCntFct0_Cmd;

typedef struct
{
  uint32  ulHsCount;
} tCddStpCntFct0_GetHsCnt;

typedef struct
{
  uint32  ulTime;
} tCddStpCntFct0_GetIrunTime;

typedef struct
{
  uint32  ulTime;
} tCddStpCntFct0_GetStpOnTime;

typedef struct
{
  uint16  unRefStartCnt;
} tCddStpCntFct0_GetRefStartCnt;

typedef struct
{
  uint16  unIsRefCnt;
} tCddStpCntFct0_GetIsRefCnt;

typedef struct
{
  uint16  aunKlPosDevHistCnts[CDDSTP_POSDEVHIST_MAX];
} tCddStpCntFct0_GetKlPosDevHistCnts;

typedef struct
{
  sint16  nLastDeviation;
} tCddStpCntFct0_GetLastDeviaton;

// common argument/return buffer type
typedef union
{
  tisCntData0                        sCntData;
  tCddStpCntFct0_GetHsCnt            GetHsCnt;
  tCddStpCntFct0_GetIrunTime         GetIrunTime;
  tCddStpCntFct0_GetStpOnTime        GetStpOnTime;
  tCddStpCntFct0_GetRefStartCnt      GetRefStartCnt;
  tCddStpCntFct0_GetIsRefCnt         GetIsRefCnt;
  tCddStpCntFct0_GetKlPosDevHistCnts GetKlPosDevHistCnts;
  tCddStpCntFct0_GetLastDeviaton     GetLastDeviation;
}
tCddStpCntFct0_DataBuffer;


typedef struct
{
  uint8  ucErrLock;    // all "locked" errors
  uint8  ucDummy1;
  uint8  ucDummy2;
  uint8  ucDummy3;
}
tStpStateGroup;

typedef struct
{
  unsigned  ErrElecOL     : 1 ;  // electrical failure: open load
  unsigned  ErrElecSC     : 1 ;  // electrical failure: short circuit
  unsigned  ErrTherm      : 1 ;  // overtemperature shutdown
  unsigned  ErrPos        : 1 ;  // positioning failure
  unsigned  ErrPrealarm   : 1 ;  // overtemperature warning: after prealarm confirmation time
  unsigned  ErrTimeout    : 1 ;  // LIN timeout error
  unsigned  ErrDrvDefect  : 1 ;  // driver defect error
  unsigned  ErrPsens      : 1 ;  // positioning-sensor defect

  unsigned  VoltNorm      : 1 ;  // voltage ok (not overvoltage and not undervoltage)
  unsigned  VoltOver      : 1 ;  // overvoltage
  unsigned  VoltUSSM      : 1 ;  // undervoltage soft stop motion (not hard stop motion) if VoltNorm = VoltOver = 0
  unsigned  Reduced       : 1 ;  // reduced dynamic by low voltage
  unsigned  StepLoss      : 1 ;  // possibly step loss caused by interrupted movement
  unsigned  Prealarm      : 1 ;  // overtemperature warning: raw driver bit
  unsigned  Kl15Off       : 1 ;  // LED6.1 specific: Kl15 off
  unsigned  InitActive    : 1 ;  // driver in initialization phase
  
  unsigned  IsReady       : 1 ;  // new commands acceptable
  unsigned  IsMoving      : 1 ;  // stepper is moving
  unsigned  IsInside      : 1 ;  // AFS module position inside (relating to hall sensor)
  unsigned  Timeout       : 1 ;  // LIN timeout 
  unsigned  RefActive     : 1 ;  // referencing active (of single "sub-ref. run")
  unsigned  IsRef         : 1 ;  // referencing done
  unsigned  FullRef       : 1 ;  // referencing by rising PSENS slope done (supported by driver with hall sensor only)
  unsigned  IsRefVolatile : 1 ;  // referencing with volatile slope evaluation done (successfully)

  unsigned  ErrPsensSigLo : 1 ;  // position sensor signal short to GND
  unsigned  ErrPsensSigHi : 1 ;  // position sensor signal short to Ubat / open load (coil)
  unsigned  ErrPsensSupLo : 1 ;  // position sensor supply short to GND
  unsigned  ErrPsensSupHi : 1 ;  // position sensor supply short to Ubat
  unsigned  SpiValid      : 1 ;  // SPI communication valid (!= 0x3F or != 0xFF)
  unsigned  Reserved3     : 3 ;
}
tStpStateBit;

// aas typedef uint32 tiulBit32;

typedef union
{
  tStpStateBit   Bit;
  tiulBit32      Bit32;
  tStpStateGroup Group;
  uint32         ulData;
}
tStpState;

#define CDDSTP_StpStateInit          { { 0, 0, 0, 0, 0, 0, 0, 0,   \
                                         1, 0, 0, 0, 0, 0, 0, 0,   \
                                         0, 0, 0, 0, 0, 0, 0, 0,   \
                                         0, 0, 0, 0, 0           } }

/// 
/// \struct  tPsensInf
/// 
/// \brief   Psens Message
///
/// \descr   Psens Message
///
typedef struct
{
  uint8  biState         : 2;       ///< Psens state
  uint8  biErrSigLo      : 1;       ///< position sensor signal short to GND
  uint8  biErrSigHi      : 1;       ///< position sensor signal short to Ubat / open load (coil)
  uint8  biErrSupLo      : 1;       ///< position sensor supply short to GND
  uint8  biErrSupHi      : 1;       ///< position sensor supply short to Ubat
  uint8  biReserved1     : 2;
}tPsensInfStateErrBit;

#define BB_PsensErr_Mask   (0x3C)   // mask with PsensErr bits

typedef union
{
  uint8                ucStateErr;  
  tPsensInfStateErrBit StateErr;    ///< Psens state and error bits
}tPsensInfStateErrAll;

typedef struct
{
  sint16 biSlopePosition : 16;      ///< position at Psens slope
  tPsensInfStateErrAll StateErrAll; ///< Psens state, error bits
  uint8  biIsPositive    : 1;       ///< Psens signal (logical)
  uint8  biIsRegSlope    : 1;       ///< Psens regular slope
  uint8  biReserved2     : 6;
}tPsensInfBit;

typedef struct
{
  sint16 nSlopePosition;            ///< position at Psens slope
  uint8  ucStateErrRaw;             ///< Psens state, error bits
  uint8  ucSpecBitsRaw;             ///< special bits
}tPsensInfVal;

typedef union
{
  tPsensInfBit Bit;
  tPsensInfVal Val;
  uint32       ulRaw;
}tPsensInf;


/*******************************************************************************
* prototypes
*******************************************************************************/

void* CddStp_GetVirtData_TestIfc(uint32* pulSize);
void  CddStp_CtrlFct0(tiulCtrlCmd ulCmd, tiucCtrlIndex ucIndex, tisCtrlData0* pData);


/*******************************************************************************
* inline functions
*******************************************************************************/

// Conversion of AUTOSAR step position tinStpPos to HS and vice versa
// The "tinStpPos" uses a resolution of 1/16 microsteps

#define CDDSTP_Hs2Ms_Factor    8

//lint -e528 Symbol 'xxx' not referenced, usage of static inline

// convert HS to 1/16 MS
INLINE sint16 CddStp_Hs2Ms(const sint16 nPos)
{
  return (sint16)(nPos * 8);
}

// convert 1/16 MS to HS, round result
INLINE sint16 CddStp_Ms2Hs(const sint16 nPos)
{
  // use shift operation to optimize rounding algorithm
  //lint -e702 LINT Info: Shift right of signed quantity (int)
  return ((nPos + 4) >> 3); // prqa ....
  //lint +e702 LINT Info: Shift right of signed quantity (int)
}

// round 1/16 MS to a value that fits to HS position
INLINE sint16 CddStp_MsRnd2HsPos(const sint16 nPos)
{
  return (sint16)((nPos + 4) & 0xFFF8);
}


#endif /* CDDSTPIFC_H */

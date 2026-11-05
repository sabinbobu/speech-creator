#ifndef __NVM_PARA_LED_H__
#define __NVM_PARA_LED_H__

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
/// \file  NvM_Para_Led.h
///
/// \brief
///
/// \descr
///
///         Additional information can be found in the design description (Link:
///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
///
/// \author Wiesner, Matthias ALDE-RT/EEG-PM2
///         mailTo:matthias.wiesner@al-lighting.com
//-----------------------------------------------------------------------------



/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include <AL_Helper.h>
#include <Cfg/Cfg.h>
#include <Swc/Ctrl/Led/CtrlLedIfc.h>
#include <Bsw/Nvm/NvM_Para_LedInit.h>


/*******************************************************************************
* Defintions
*******************************************************************************/

#define CFG_BoostOff_Cnt           (8u)       // Maximum number of consider Leds

/*******************************************************************************
* types
*******************************************************************************/


/******************************************************************************/
/* Supply on/off times                                                        */
/******************************************************************************/

typedef struct
{
  uint8  LED_SUPPLY_MIN_ON_T;
  uint8  LED_SUPPLY_MIN_OFF_T;
  uint8  LED_SUPPLY_MIN_OFF_FAST_T;
  uint8  LED_SUPPLY_MAX_ON_T;
  uint8  LED_SUPPLY_MAX_OFF_T;
  uint8  aucReserved[3];
}
tNvmPara_Led_SupplyOnOffTimes; // 8 bytes


/******************************************************************************/
/* VoltageDerating                                                            */
/******************************************************************************/

typedef struct
{
  uint8  aucLM_UBAT_LOWER_U1       [CFG_LM_Cnt];
  uint8  aucLM_UBAT_UPPER_U1       [CFG_LM_Cnt];
  uint8  aucLM_UBAT_MAX_DERATING_P1[CFG_LM_Cnt];
  uint8  ucUBAT_DERATING_DELAY;
  uint8  ucUBAT_DERATING_GRADIENT;
  uint16 reserved;
}
tNvmPara_Led_VoltageDerating; // 28 bytes


/******************************************************************************/
/* Boost Converter                                                            */
/******************************************************************************/

typedef enum
{
  eBoost_None   = 0,
  eBoost_Slave  = 1,
  eBoost_Master = 2,
  eBoost_Single = 3
}
tBoost_Config;

typedef struct
{
  uint8  BOOST_OUTPUT_VOLTAGE1;
  uint8  BOOST_OUTPUT_VOLTAGE2;
  uint8  BOOST_OUTPUT_VOLTAGE3;
  uint8  BOOST_OUTPUT_VOLTAGE4;
  uint8  LED_OPEN_CIRCUIT_VALUE1;
  uint8  LED_OPEN_CIRCUIT_VALUE2;
  uint8  LED_OPEN_CIRCUIT_VALUE3;
  uint8  LED_OPEN_CIRCUIT_VALUE4;
  uint16 BOOST_VOLT_ERROR_DEBOUNCE;
  uint8  BOOST_VOLT_ERROR_THRESHOLD;
  uint8  BOOST_01_CONFIG       : 2 ;
  uint8  BOOST_02_CONFIG       : 2 ;
  uint8  BOOST_03_CONFIG       : 2 ;
  uint8  BOOST_04_CONFIG       : 2 ;
}
tNvmPara_Led_BoostConverter; // 12 bytes


/******************************************************************************/
/* LED error detection                                                        */
/******************************************************************************/

typedef struct
{
  uint16 LED_SHORT_UBAT_DEBOUNCE;
  uint16 LED_OVERCURRENT_DEBOUNCE;
  uint8  LED_SHORT_UBAT_RANGE;
  uint8  reserviert1;
  uint16 reserviert2;
}
tNvmPara_Led_ErrDetect; //  8 bytes


/******************************************************************************/
/* LED Gamma config                                                           */
/******************************************************************************/

typedef struct
{
  uint8  aucPoint[6];
  uint16 reserved;
}
tNvmPara_Led_GammaConfig; // 8 bytes


/******************************************************************************/
/* LED Leuchtmittel config                                                    */
/******************************************************************************/

// A logical lamp has one of these unique names
typedef enum NvM_Para_BinningStrategy
{
  BINNING_ON_DUTY     = 1,
  BINNING_ON_CURRENT  = 2,
  BINNING_NOT_DEFINED = 3
} tNvM_Para_BinningStrategy;


typedef enum NvM_Para_PSIN_Index 
{
  PSIN_1 = 0,
  PSIN_2 = 1,
  PSIN_3 = 2,
  PSIN_4 = 3,
  NOT_USED
} PowerSupplyLinePSIN;

typedef struct
{
  uint16  CURRENT_PATH;
  uint8   BINNING_STRATEGY;
  uint8   ucBUCK_TOFF;
  uint16  LED_START_DEBOUNCE;
  uint16  LED_OPERATING_DEBOUNCE;
  uint8   LED_UNDER_VOLTAGE_VALUE;
  uint8   LED_OVER_VOLTAGE_VALUE;
  sint16  nDeltaI_Offset;
  uint8   PSIN_SUPPLY;
  uint8   reserviert1;
  uint16  reserviert2;
}
tNvmPara_Led_Leuchtmittel_Config; // 16 bytes


/**************************************************************************/
/* The Led block contains additional information for a Led                */
/**************************************************************************/

typedef struct
{
  tNvmPara_Led_SupplyOnOffTimes    LedSupplyTimes;     //   8 bytes
  tNvmPara_Led_VoltageDerating     LedVoltageDerating; //  28 bytes
  tNvmPara_Led_BoostConverter      LedBoostConverter;  //  12 bytes
  tNvmPara_Led_ErrDetect           LedErrDetect;       //   8 bytes
  tNvmPara_Led_GammaConfig         LedGammaConfig;     //   8 bytes
  tNvmPara_Led_Leuchtmittel_Config LedConfigLM1;       //  16 bytes
  tNvmPara_Led_Leuchtmittel_Config LedConfigLM2;       //  16 bytes
  tNvmPara_Led_Leuchtmittel_Config LedConfigLM3;       //  16 bytes
  tNvmPara_Led_Leuchtmittel_Config LedConfigLM4;       //  16 bytes
  tNvmPara_Led_Leuchtmittel_Config LedConfigLM5;       //  16 bytes
  tNvmPara_Led_Leuchtmittel_Config LedConfigLM6;       //  16 bytes
  tNvmPara_Led_Leuchtmittel_Config LedConfigLM7;       //  16 bytes
  tNvmPara_Led_Leuchtmittel_Config LedConfigLM8;       //  16 bytes
}                                                      // -------
tNvmPara_LedBlock;                                     // 192 bytes



/**************************************************************************/
/* ROM CONSTANTS:                                                         */
/**************************************************************************/

typedef struct
{
  uint8  LM_ID_LT1     : 4;
  uint8  LM_ID_LT2     : 4;
  uint8  LM_ID_LT3     : 4;
  uint8  LM_ID_LT4     : 4;
  uint8  LM_ID_LT5     : 4;
  uint8  LM_ID_LT6     : 4;
  uint8  LM_ID_LT7     : 4;
  uint8  LM_ID_LT8     : 4;
}
tNvmPara_Led_LMtoLTMapping;

/*******************************************************************/

typedef struct
{
  uint8  aucLM_THERMAL_DERATING_CONFIG[CFG_LM_Cnt];
}
tNvmPara_Led_LMtoThermalDeratingMapping;

/*******************************************************************/

typedef struct
{
  uint16  aunLM_MINIMAL_CURRENT_CONFIG[CFG_LM_Cnt];
}
tNvmPara_Led_LMtoMinCurrentDeratingMapping;


// Plausibilization (CddLed):
/*******************************************************************/
typedef struct
{
  uint8  ucIsLmUsed;              // bit field that indicates if a LM is used for the checked LF, LSB ist LM1, e.g. 0x03 means LM1 and LM2 is used
  uint8  ucEnableLmPlausCheck;    // bit field that indicates if a LM needs to be plausibility checked, LSB ist LM1, e.g. 0x02 means LM2 is checked
  uint8  ucMinBrightnessLmFirst;  // Min brightness value of the first plausibility check LM beginning with LM1
  uint8  ucMinBrightnessLmSecond; // Min brightness value of the second plausibility check LM beginning with LM1
  uint8  ucMinBrightnessLmThird;  // Min brightness value of the third plausibility check LM beginning with LM1
  uint8  ucMinBrightnessLmFourth; // Min brightness value of the fourth plausibility check LM beginning with LM1
  uint8  aucReserved[2];          // reserved for future use and to be 32bit-aligned
}
tNvmPara_Led_PlausConfig;


#endif // __NVM_PARA_LED_H__

// EOF

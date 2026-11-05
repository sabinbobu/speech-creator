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
//  \file   CodM_Para_Led.h
//
//  \brief  Content of datagroup "Led"
//
//  \descr  Source: PS60_R2.xlsm. 
//         
//          For further details see coding parameter
//
//  \author Cretu Vlad (F78845C)
//          mailTo:vladut-ioan.cretu@marelli.com
//
//  \date   22.06.2019, 14:06:20
//-----------------------------------------------------------------------------
//=============================================================================
// Includes
//=============================================================================
#ifndef __CODM_PARA_LED_H__
#define __CODM_PARA_LED_H__

#include <Cfg/Cfg.h>

//=============================================================================
// Definitions
//=============================================================================
#define CODM_PARA_LED_RESREVED_SIZE 2u
#define CODM_PARA_LED_RESREVED_SIZE 2u
#define CODM_PARA_LED_GAMMA_POINTS 17u
#define CODM_PARA_LED_NTC_SIZE     4u
#define CODM_PARA_LED_RESERVED_SIZE 16u
#define CODM_PARA_LED_BINNING_CLASS 5u
#define CODM_PARA_LED_SIZE_PARAMS   12u

//=============================================================================
// Types
//=============================================================================


//=============================================================================
// Supply voltages                                                            
//=============================================================================
typedef struct
{
  uint8  LED_SUPPLY_MIN_OFF_V;
  uint8  LED_SUPPLY_MIN_OFF_T;
  uint8  LED_SUPPLY_MIN_ON_V;
  uint8  LED_SUPPLY_MIN_ON_T;
}
tNvmPara_Led1_LedSupplyVoltage;

//=============================================================================
// VoltageDerating                                                           
//=============================================================================

typedef struct
{
  uint8 aucLED_VBAT_DERATING_V1; // voltage derating, lower base voltage array
                                          // for all led drivers 01-12
  uint8 aucLED_VBAT_DERATING_V2; // voltage derating, upper base voltage  array
                                          // for all led drivers 01-12
  uint8 aucLED_VBAT_MAX_DERATING_P1; // voltage derating, limiter value at lower
                                          // base voltage array for all led drivers 01-12
  uint8 LED_VBAT_DERATING_DELAY; //Delay of voltage derating
  uint8 LED_VBAT_DERATING_FILTER; // Filter time constant for voltage derating
  uint8 aucLED_VBAT_DERATING_V3; // voltage derating, upper base voltage  array
                                          // for all led drivers 01-12
  uint8 aucLED_VBAT_DERATING_V4; // voltage derating, upper base voltage  array
                                          // for all led drivers 01-12
  uint8 aucLED_VBAT_MAX_DERATING_P2; // voltage derating, limiter value at lower
                                          // base voltage array for all led drivers 01-12
  uint8 aucLED_VBAT_MAX_DERATING_P3; // voltage derating, limiter value at lower
                                          // base voltage array for all led drivers 01-12
  uint8 reserviert1;
}
tNvmPara_Led1_LedVoltageDerating;

//=============================================================================
// Boost Converter                                                            
//=============================================================================
typedef struct
{
  uint8 ucBOOST_VOLT_HEADROOM; // Offset for booster voltage. Booster voltage
                                          // shall be calculated by adding max(DRVxx_LED_OVER_VOLTAGE_VALUE)
                                          // and BOOST_VOLT_HEADROOM
  uint8 ucBOOST_VOLT_ERROR_THRESHOLD; // Fault threshold for detecting a booster error.
                                          // If the booster voltage is lower than (expected
                                          // value - BOOST_VOLT_ERROR_THRESHOLD) then
                                          // a booster error DTC shall be entered
  uint8 ucBOOST_VOLT_ERROR_DEBOUNCE; // Debounce counter for the booster fault detection
  uint8 ucreserviert1;
}
tNvmPara_Led1_LedBoostConverter;


//=============================================================================
// LM_Name mapping                                                            
//=============================================================================

//=============================================================================
// LED error detection                                                         
//=============================================================================
typedef struct
{
  uint8 reservied;
  uint8 LED_SHORT_UBAT_RANGE; // Fault threshold for detecting "short-circuit
    // UBAT". Detection: If the voltage of a LED
    // chain is in the range
    //Ubat +- LED_SHORT_UBAT_RANGE
    // before switching on, then the fault is detected
  uint8 LED_SHORT_UBAT_DEBOUNCE; // Debounce counter for "short-circuit to Ubat"-Failure
                                          // detection
  uint8 LED_OVERCURRENT_DEBOUNCE; // Debounce counter for overcurrent fault detection
                                          //
  uint8 reserviert2[2];
}
tNvmPara_Led1_LedErrDetect;

typedef struct
{
  uint8 CRC32_0;                          // 32 bit CRC checksum over complete FUSIConfig-Block
  uint8 CRC32_1;                          // 32 bit CRC checksum over complete FUSIConfig-Block
  uint8 CRC32_2;                          // 32 bit CRC checksum over complete FUSIConfig-Block
  uint8 CRC32_3;                          // 32 bit CRC checksum over complete FUSIConfig-Block
  uint8 FUSA_DRV01_NAMES[CODM_PARA_LED_SIZE_PARAMS];
  uint8 FUSA_DRV01_LED_UNDER_VOLTAGE[CODM_PARA_LED_SIZE_PARAMS]; // Error limit: lower limit for "line voltage

  uint8 FUSA_DRV01_LED_OVER_VOLTAGE[CODM_PARA_LED_SIZE_PARAMS];  // Error limit: upper limit for "line voltage
  uint8 FUSA_DRV01_MIN_PWM[CODM_PARA_LED_SIZE_PARAMS];           // Minimum Pwm
  uint16 FUSA_MIN_CURRENT_DRVS[CODM_PARA_LED_SIZE_PARAMS];       // Minimum Current
  uint8 FUSA_LB_FS_BEHAVIOUR;             // Low Beam Fail Safe Behaviour Value
  uint8 FUSA_TI_FS_BEHAVIOUR;             // Turn Indicator Fail Safe Behaviour Value
  uint8 reserviert1[2];                   // Low Beam Fail Safe Behaviour Value
}
tNvmPara_Led1_FUSAConfig;
//=============================================================================
// LED NTC Resistor config                                                 
//=============================================================================

typedef struct
{
  uint16 DRV01_CURRENT_BINNING_CLASSES[6]; //Current Binning Class 0
  uint8 DRV01_ALLOCATED_RCOD; // Resistor which is assigned to channel for
                                          // binning
  uint8 DRV01_LED_ERROR_DEBOUNCE; // Standard debounce  time for LED error detection
  uint8 reserviert1[2];
}
tNvmPara_Led1_LedConfigDRV01;

typedef struct
{
  uint16 DRV02_CURRENT_BINNING_CLASSES[6]; //Current Binning Class 0
  uint8  DRV02_ALLOCATED_RCOD; // Resistor which is assigned to channel for
                                          // binning
  uint8  DRV02_LED_ERROR_DEBOUNCE; // Standard debounce  time for LED error detection
  uint8  reserviert1[2];
}
tNvmPara_Led1_LedConfigDRV02;

typedef struct
{
  uint16 DRV03_CURRENT_BINNING_CLASSES[6]; //Current Binning Class 0-6
  uint8 DRV03_ALLOCATED_RCOD; // Resistor which is assigned to channel for
                                          // binning
  uint8 DRV03_LED_ERROR_DEBOUNCE; // Standard debounce  time for LED error detection
                                          //
  uint8 reserviert1[2];
}
tNvmPara_Led1_LedConfigDRV03;

typedef struct
{
  uint16 DRV04_CURRENT_BINNING_CLASSES[6];
  uint8 DRV04_ALLOCATED_RCOD; // Resistor which is assigned to channel for binning
  uint8 DRV04_LED_ERROR_DEBOUNCE; // Standard debounce  time for LED error detection
  uint8 reserviert1[2];
}
tNvmPara_Led1_LedConfigDRV04;

typedef struct
{
  uint16 DRV05_CURRENT_BINNING_CLASSES[6]; //Current Binning Class 0
  uint8 DRV05_ALLOCATED_RCOD; // Resistor which is assigned to channel for binning
  uint8 DRV05_LED_ERROR_DEBOUNCE; // Standard debounce  time for LED error detection
  uint8 reserviert1[2];
}
tNvmPara_Led1_LedConfigDRV05;

typedef struct
{
  uint16 DRV06_CURRENT_BINNING_CLASSES[6]; //Current Binning Class 0
  uint8 DRV06_ALLOCATED_RCOD; // Resistor which is assigned to channel for binning
  uint8 DRV06_LED_ERROR_DEBOUNCE; // Standard debounce  time for LED error detection
  uint8 DRV06_LED_UNDER_VOLTAGE_VALUE; // Error limit: lower limit for "line voltage out of tolerance" (minus 1.5V tolerance added)
  uint8 DRV06_LED_OVER_VOLTAGE_VALUE; // Standard debounce  time for LED error detection (time base 20ms)
  uint8 reserviert1[2];
}
tNvmPara_Led1_LedConfigDRV06;

typedef struct
{
  uint16 DRV07_CURRENT_BINNING_CLASSES[6];
  uint8 DRV07_ALLOCATED_RCOD; // Resistor which is assigned to channel for binning
  uint8 DRV07_LED_ERROR_DEBOUNCE; // Standard debounce  time for LED error detection
  uint8 reserviert1[2];
}
tNvmPara_Led1_LedConfigDRV07;

typedef struct
{
  uint16 DRV08_CURRENT_BINNING_CLASSES[6];
  uint8 DRV08_ALLOCATED_RCOD; // Resistor which is assigned to channel for binning
  uint8 DRV08_LED_ERROR_DEBOUNCE; // Standard debounce  time for LED error detection
  uint8 reserviert1[2];
}
tNvmPara_Led1_LedConfigDRV08;

typedef struct
{
  uint16 DRV09_CURRENT_BINNING_CLASSES[6];
  uint8 DRV09_ALLOCATED_RCOD; // Resistor which is assigned to channel for binning
  uint8 DRV09_LED_ERROR_DEBOUNCE; // Standard debounce  time for LED error detection
  uint8 reserviert1[2];
}
tNvmPara_Led1_LedConfigDRV09;

typedef struct
{
  uint16 DRV10_CURRENT_BINNING_CLASSES[6];
  uint8 DRV10_ALLOCATED_RCOD; // Resistor which is assigned to channel for binning
  uint8 DRV10_LED_ERROR_DEBOUNCE; // Standard debounce  time for LED error detection (time base 20ms)
  uint8 reserviert1[2];
}
tNvmPara_Led1_LedConfigDRV10;

typedef struct
{
  uint16 DRV11_CURRENT_BINNING_CLASSES[6];
  uint8 DRV11_ALLOCATED_RCOD; // Resistor which is assigned to channel for binning
  uint8 DRV11_LED_ERROR_DEBOUNCE; // Standard debounce  time for LED error detection
  uint8 reserviert1[2];
}
tNvmPara_Led1_LedConfigDRV11;

typedef struct
{
  uint16 DRV12_CURRENT_BINNING_CLASSES[6];
  uint8  DRV12_ALLOCATED_RCOD; // Resistor which is assigned to channel for binning
  uint8 DRV12_LED_ERROR_DEBOUNCE; // Standard debounce  time for LED error detection
  uint8 reserviert1[2];
}
tNvmPara_Led1_LedConfigDRV12;

//=============================================================================
// The Led1 block contains additional information for a Led 
//=============================================================================

typedef struct
{
  uint8 FUSA_DRV13_NAME; //OUTPUT OFF = 0; SM=8; RGB=9;
  uint8 reserviert1[3];
}
tNvmPara_Led1_LedConfigDRV13;

typedef struct
{
  uint16 unDELAY_TI_NOT_REQUESTED;
  uint16 unCONFIG_TIME; 
  uint8 reserviert1[8];
}
tNvmPara_Led1_BasicFunctions;


//=============================================================================
// The Led1 block contains additional information for a Led 
//=============================================================================
typedef struct
{
  tNvmPara_Led1_LedSupplyVoltage         LedSupplyVoltage;
  tNvmPara_Led1_LedVoltageDerating       LedVoltageDerating;
  tNvmPara_Led1_LedBoostConverter        LedBoostConverter;
  tNvmPara_Led1_LedErrDetect             LedErrDetect;
  tNvmPara_Led1_FUSAConfig               FUSAConfig;
  tNvmPara_Led1_LedConfigDRV01           LedConfigDRV01;
  tNvmPara_Led1_LedConfigDRV02           LedConfigDRV02;
  tNvmPara_Led1_LedConfigDRV03           LedConfigDRV03;
  tNvmPara_Led1_LedConfigDRV04           LedConfigDRV04;

#if defined (CFG_VARIANT_FULL) || (UNIT_TEST)
  tNvmPara_Led1_LedConfigDRV05           LedConfigDRV05;
  tNvmPara_Led1_LedConfigDRV06           LedConfigDRV06;
  tNvmPara_Led1_LedConfigDRV07           LedConfigDRV07;
  tNvmPara_Led1_LedConfigDRV08           LedConfigDRV08;
  tNvmPara_Led1_LedConfigDRV09           LedConfigDRV09;
  tNvmPara_Led1_LedConfigDRV10           LedConfigDRV10;
  tNvmPara_Led1_LedConfigDRV11           LedConfigDRV11;
  tNvmPara_Led1_LedConfigDRV12           LedConfigDRV12;
#endif

  tNvmPara_Led1_LedConfigDRV13           LedConfigDRV13;
  tNvmPara_Led1_BasicFunctions           BasicFunctions;

} tNvmPara_Led1Block;


#endif // __CODM_PARA_LED_H__

// EOF

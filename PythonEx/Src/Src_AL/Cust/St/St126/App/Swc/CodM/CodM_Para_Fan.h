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
///  \file   CodM_Para_Fan.h
///
///  \brief  Content of datagroup "Fan"
///
///  \descr  Source: PS60_R2.xlsm. 
///         
///          For further details see coding parameter
///
///  \author Cretu Vlad (F78845C)
///          mailTo:vladut-ioan.cretu[at]marelli.com
///
///  \date   22.06.2019, 14:06:20
//-----------------------------------------------------------------------------
//=============================================================================
// Includes
//=============================================================================
#ifndef __CODM_PARA_FAN1_H__
#define __CODM_PARA_FAN1_H__

#include <Cfg/Cfg.h>
//=============================================================================
// Definitions
//=============================================================================
#define CODM_PARA_RESERVIERT_SIZE 2u

#define CODM_PARA_THERMO_SIZE 12u
//=============================================================================
// Types
//=============================================================================
typedef struct
{
  // Temperature threshold to activate the fan
  uint8 ucFan1_Actv_Threshold_Termozones[CODM_PARA_THERMO_SIZE];
}
tNvmPara_Fan1_FAN1_HT_THRESHOLDS;

typedef struct 
{                              
  // Temperature threshold to activate the fan
  // for high temperature on External Satellites
  // -40°C … 0°C … 150°C= 0 … 40 … 190
  uint8 ucFan2_Actv_Threshold_Termozones[CODM_PARA_THERMO_SIZE];
}
tNvmPara_Fan1_FAN2_HT_THRESHOLDS;

typedef struct
{      
  // Fan switches off, if terminal 30 is below
  // this threshold, for the debounce time FAN_SUPPLY_MIN_OFF_T.                                        
  uint8 ucFAN1_SUPPLY_OFF_V_MIN; 
  // Debounce time of the Fan to switch-off, if terminal 30 is below FAN_SUPPLY_MIN_OFF_V.                                        
  uint8 ucFAN1_SUPPLY_OFF_T_MIN;
  // Fan switches on when terminal 30 is above this threshold value is for the debounce time FAN_SUPPLY_MIN_ON_T.                                       
  uint8 ucFAN1_SUPPLY_ON_V_MIN;
  // Debounce time for the Fan to switch-on, if terminal 30 is above FAN_SUPPLY_MIN_ON_V.
  uint8 ucFAN1_SUPPLY_ON_T_MIN; 
  // Fan switches off when terminal 30 is above this threshold is for the debounce time FAN_SUPPLY_MAX_OFF_T.                                        
  uint8 ucFAN1_SUPPLY_OFF_V_MAX;
  // Debounce time for the Fan to switch-off, if terminal 30 is above FAN_SUPPLY_MAX_OFF_V.
  uint8 ucFAN1_SUPPLY_OFF_T_MAX; 
  // Fan switches on, if terminal 30 is below this threshold, for the debounce time FAN_SUPPLY_MAX_ON_T.                                        
  uint8 ucFAN1_SUPPLY_ON_V_MAX; 
  // Debounce time for the Fan to switch on, if terminal 30 is below FAN_SUPPLY_MAX_ON_V.                                        
  uint8 ucFAN1_SUPPLY_ON_T_MAX; 
  //Reserved                                        
  uint8 areserviert2[CODM_PARA_RESERVIERT_SIZE];
}
tNvmPara_Fan1_FAN1_SUPPLY;

typedef struct
{
  // Fan switches off, if terminal 30 is below
  // this threshold, for the debounce time FAN_SUPPLY_MIN_OFF_T.                                        
  uint8 ucFAN2_SUPPLY_OFF_V_MIN;
  // Debounce time of the Fan to switch-off, if terminal 30 is below FAN_SUPPLY_MIN_OFF_V.                                        
  uint8 ucFAN2_SUPPLY_OFF_T_MIN;
  // Fan switches on when terminal 30 is above this threshold value is for the debounce time FAN_SUPPLY_MIN_ON_T.                                       
  uint8 ucFAN2_SUPPLY_ON_V_MIN;
  // Debounce time for the Fan to switch-on, if terminal 30 is above FAN_SUPPLY_MIN_ON_V.
  uint8 ucFAN2_SUPPLY_ON_T_MIN;
  // Fan switches off when terminal 30 is above this threshold is for the debounce time FAN_SUPPLY_MAX_OFF_T.                                        
  uint8 ucFAN2_SUPPLY_OFF_V_MAX;
  // Debounce time for the Fan to switch-off, if terminal 30 is above FAN_SUPPLY_MAX_OFF_V.
  uint8 ucFAN2_SUPPLY_OFF_T_MAX;
  // Fan switches on, if terminal 30 is below this threshold, for the debounce time FAN_SUPPLY_MAX_ON_T.                                        
  uint8 ucFAN2_SUPPLY_ON_V_MAX;
  // Debounce time for the Fan to switch on, if terminal 30 is below FAN_SUPPLY_MAX_ON_V.                                        
  uint8 ucFAN2_SUPPLY_ON_T_MAX;
  //Reserved                                        
  uint8 areserviert2[CODM_PARA_RESERVIERT_SIZE];
}
tNvmPara_Fan1_FAN2_SUPPLY;

typedef struct
{
  uint16 HSS1_OPEN_LOAD_THRESHOLD; // Unit: 1mV ~  Ein Open Load wird erkannt wenn
                                          // die Sensorspannung unterhalb dieses Schwellwertes
                                          // liegt ~ Origin: SG Hersteller
  uint16 HSS2_OPEN_LOAD_THRESHOLD; // Unit: 1mV ~  Ein Open Load wird erkannt wenn
                                          // die Sensorspannung untererhalb dieses Schwellwertes
                                          // liegt ~ Origin: SG Hersteller
  uint16 HSS3_OPEN_LOAD_THRESHOLD; // Unit: 1mV ~  Ein Open Load wird erkannt wenn
                                          // die Sensorspannung unterhalb dieses Schwellwertes
                                          // liegt ~ Origin: SG Hersteller
  uint16 HSS1_SHORT_TO_GND_THRESHOLD; // Unit: 1mV ~  Ein Kurzschluss nach Masse wird
                                          // erkannt wenn die Sensorspannung oberhalb
                                          // dieses Schwellwertes liegt ~ Origin: SG Hersteller
  uint16 HSS2_SHORT_TO_GND_THRESHOLD; // Unit: 1mV ~  Ein Kurzschluss nach Masse wird
                                          // erkannt wenn die Sensorspannung oberhalb
                                          // dieses Schwellwertes liegt ~ Origin: SG Hersteller
  uint16 HSS3_SHORT_TO_GND_THRESHOLD; // Unit: 1mV ~  Ein Kurzschluss nach Masse wird
                                          // erkannt wenn die Sensorspannung oberhalb
                                          // dieses Schwellwertes liegt ~ Origin: SG Hersteller
  uint16 HSS1_SHORT_TO_UBAT_THRESHOLD; // Unit: 1mV ~  Ein Kurzschluss nach Masse wird
                                          // erkannt wenn die Sensorspannung oberhalb
                                          // dieses Schwellwertes liegt ~ Origin: SG Hersteller
  uint16 HSS2_SHORT_TO_UBAT_THRESHOLD; // Unit: 1mV ~  Ein Kurzschluss nach Masse wird
                                          // erkannt wenn die Sensorspannung oberhalb
                                          // dieses Schwellwertes liegt ~ Origin: SG Hersteller
  uint16 HSS3_SHORT_TO_UBAT_THRESHOLD; // Unit: 1mV ~  Ein Kurzschluss nach Masse wird
                                          // erkannt wenn die Sensorspannung oberhalb
                                          // dieses Schwellwertes liegt ~ Origin: SG Hersteller
  uint8 HSS_DIAG_DEBOUNCE; // Unit: 20 ms ~ Values: 0.. 255 (0.. 5,1 s)
                                          // ~ Entprellzaehler bei Diagnose ~ Origin:
                                          // SG Hersteller
  uint8 HSS3_MIN_PWM;
}
tNvmPara_Fan1_HSS_DIAG;

typedef struct
{
  uint8 ucFanHysterezis;
  uint8 ucreserviert1;
}
tNvmPara_Fan1_Fans_Hysterezis;

typedef struct
{
  uint8 aucFan1_ActivationThreshold_Thzs[CODM_PARA_THERMO_SIZE];
}
tNvmPara_Fan1_Fan1_BehaviorOnNTCFailure;

typedef struct
{
  uint8 ucFan2_ActivationThreshold_Thzs[CODM_PARA_THERMO_SIZE];
}
tNvmPara_Fan1_Fan2_BehaviorOnNTCFailure;

typedef struct
{
  uint8 ucFan1Enabled; // Boolean which states the presence of the
                                          // FAN1
  uint8 ucFan2Enabled; // Boolean which states the presence of the
                                          // FAN2
}
tNvmPara_Fan1_Fans_Presence;

typedef struct 
{
  tNvmPara_Fan1_FAN1_HT_THRESHOLDS        FAN1_HT_THRESHOLDS;       
  tNvmPara_Fan1_FAN2_HT_THRESHOLDS        FAN2_HT_THRESHOLDS;                                   
  tNvmPara_Fan1_FAN1_SUPPLY               FAN1_SUPPLY;         
  tNvmPara_Fan1_FAN2_SUPPLY               FAN2_SUPPLY;
  tNvmPara_Fan1_HSS_DIAG                  HSS_DIAG;
  tNvmPara_Fan1_Fans_Hysterezis           Fans_Hysterezis;
  tNvmPara_Fan1_Fan1_BehaviorOnNTCFailure Fan1_BehaviorOnNTCFailure;
  tNvmPara_Fan1_Fan2_BehaviorOnNTCFailure Fan2_BehaviorOnNTCFailure;
  tNvmPara_Fan1_Fans_Presence             Fans_Presence;
} tNvmPara_Fan1Block;                                       // 88 bytes                                                                           

#endif // __CODM_PARA_FAN1_H__

// EOF

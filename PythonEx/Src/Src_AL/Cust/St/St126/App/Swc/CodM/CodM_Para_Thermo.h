#ifndef __CODM_PARA_THERMO_H__
#define __CODM_PARA_THERMO_H__


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
///  \file   CodM_Para_Thermo1.h
///
///  \brief  Content of datagroup "Thermo1"
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
// includes
//=============================================================================
#include <Cfg/Cfg.h>

//=============================================================================
// Defines
//=============================================================================
#define CODM_PARA_THERMO_RESERVED_SIZE             16
#define CODM_PARA_THERMO_PG_SIZE                   10
#define CODM_PARA_THERMO_NTC_SIZE                  4

#define CODM_PARA_THERMO_SIZE                      12u
#define CODM_PARA_PCB_THERMO_SIZE                  5u
#define CODM_PARA_RSRVD_SIZE                       5u

//=============================================================================
// Types
//=============================================================================
typedef struct
{
  // Ntcs sources

  uint8 ucNtcSource_Thermozones[CODM_PARA_THERMO_SIZE];
}
tNvmPara_Thermo1_NTC_SOURCES;

typedef struct
{
  // NTC Types
  uint8 ucNtcType_Thermozones[CODM_PARA_THERMO_SIZE];
}
tNvmPara_Thermo1_NTC_Types;

typedef struct
{
  // Temperatures 1 for all thermozones
  uint8 ucTemp1_Thermozones[CODM_PARA_THERMO_SIZE];
}
tNvmPara_Thermo1_Thermozones_Temp1;

typedef struct
{
  // Temp 2 for all thermozones
  uint8 ucTemp2_Thermozones[CODM_PARA_THERMO_SIZE];
}
tNvmPara_Thermo1_Thermozones_Temp2;

typedef struct
{
  // Temp 3 for all thermozones
  uint8 ucTemp3_Thermozones[CODM_PARA_THERMO_SIZE];
}
tNvmPara_Thermo1_Thermozones_Temp3;

typedef struct
{
  // Temp 4 for all thermozones
  uint8 ucTemp4_Thermozones[CODM_PARA_THERMO_SIZE];
}
tNvmPara_Thermo1_Thermozones_Temp4;

typedef struct
{
  // Temp 5 for all thermozones
  uint8 ucTemp5_Thermozones[CODM_PARA_THERMO_SIZE];
}
tNvmPara_Thermo1_Thermozones_Temp5;

typedef struct
{
  uint8 aucThermzonePcb_Temps[CODM_PARA_PCB_THERMO_SIZE]; // array with temp thresholds for pcb interpolation
}
tNvmPara_Thermo1_ThermzonePCB_Temp;

typedef struct
{
  // PowFact 1 for all thermozones
  uint8 ucPowFact1_Thermozones[CODM_PARA_THERMO_SIZE];
}
tNvmPara_Thermo1_Thermozones_PowerFactor_1;

typedef struct
{
  // PowFact 2 for all thermozones
  uint8 ucPowFact2_Thermozones[CODM_PARA_THERMO_SIZE];
}
tNvmPara_Thermo1_Thermozones_PowerFactor_2;

typedef struct
{
  // PowFact 3 for all thermozones
  uint8 ucPowFact3_Thermozones[CODM_PARA_THERMO_SIZE];
}
tNvmPara_Thermo1_Thermozones_PowerFactor_3;

typedef struct
{
  // PowFact 4 for all thermozones
  uint8 ucPowFact4_Thermozones[CODM_PARA_THERMO_SIZE];
}
tNvmPara_Thermo1_Thermozones_PowerFactor_4;

typedef struct
{
  // PowFact 5 for all thermozones
  uint8 ucPowFact5_Thermozones[CODM_PARA_THERMO_SIZE];
}
tNvmPara_Thermo1_Thermozones_PowerFactor_5;

typedef struct
{
  uint8 aucThermozonePcb_PowFcts[CODM_PARA_PCB_THERMO_SIZE]; // array with pow factors for pcb interpolation
}
tNvmPara_Thermo1_ThermozonePCB_PowFct;

typedef struct
{
  // FaultyNtc for all thermozones
  uint8 ucFaultyNtc_PowFct_Thermozones[CODM_PARA_THERMO_SIZE];
}
tNvmPara_Thermo1_Thermozone_BehaviourNtcFaulty;

typedef struct
{
  // FctGroup1 for all thermozones
  uint8 ucFctGroup1_State_Thermozones[CODM_PARA_THERMO_SIZE];
}
tNvmPara_Thermo1_Thermozones_FunctionGroup_1;

typedef struct
{
  // FctGroup2 for all thermozones
  uint8 ucFctGroup2_State_Thermozones[CODM_PARA_THERMO_SIZE];
}
tNvmPara_Thermo1_Thermozones_FunctionGroup_2;

typedef struct
{
  // FctGroup3 for all thermozones
  uint8 ucFctGroup3_State_Thermozones[CODM_PARA_THERMO_SIZE];
}
tNvmPara_Thermo1_Thermozones_FunctionGroup_3;

typedef struct
{
  // FctGroup4 for all thermozones
  uint8 ucFctGroup4_State_Thermozones[CODM_PARA_THERMO_SIZE];
}
tNvmPara_Thermo1_Thermozones_FunctionGroup_4;

typedef struct
{
  uint8 ucPowFct_RisingRateLimiter;
  uint8 ucPowFct_FallingRateLimiter;
}
tNvmPara_Thermo1_Thermzones_PowRateLimiter;

typedef struct
{
  uint16 unNtc_Sh2GndThreshold;
  uint16 unNtc_OpenLoad;
  uint16 unNtc_Sh2Vbat;
  uint8  ucDebounceFilterT;
  uint8  ucreserviert1;
}
tNvmPara_Thermo1_ExtNTCsErrThresh_DebFilter;

typedef struct
{
  uint16 unPcbNtc_Sh2GndThreshold;
  uint16 unPcbNtc_OpenLoad;
  uint16 unPcbDebounceFilterT;
  uint8  ucreserviert1[2];
}
tNvmPara_Thermo1_PCBNtc_ErrThresh;

typedef struct 
{
  tNvmPara_Thermo1_NTC_SOURCES                   NTC_SOURCES;
  tNvmPara_Thermo1_NTC_Types                     NTC_Types;
  tNvmPara_Thermo1_Thermozones_Temp1             Thermozones_Temp1;
  tNvmPara_Thermo1_Thermozones_Temp2             Thermozones_Temp2;
  tNvmPara_Thermo1_Thermozones_Temp3             Thermozones_Temp3;
  tNvmPara_Thermo1_Thermozones_Temp4             Thermozones_Temp4;
  tNvmPara_Thermo1_Thermozones_Temp5             Thermozones_Temp5;
  tNvmPara_Thermo1_ThermzonePCB_Temp             ThermzonePCB_Temp;
  tNvmPara_Thermo1_Thermozones_PowerFactor_1     Thermozones_PowerFactor_1;
  tNvmPara_Thermo1_Thermozones_PowerFactor_2     Thermozones_PowerFactor_2;
  tNvmPara_Thermo1_Thermozones_PowerFactor_3     Thermozones_PowerFactor_3;
  tNvmPara_Thermo1_Thermozones_PowerFactor_4     Thermozones_PowerFactor_4;
  tNvmPara_Thermo1_Thermozones_PowerFactor_5     Thermozones_PowerFactor_5;
  tNvmPara_Thermo1_ThermozonePCB_PowFct          ThermozonePCB_PowFct;
  tNvmPara_Thermo1_Thermozone_BehaviourNtcFaulty Thermozone_BehaviourNtcFaulty;
  tNvmPara_Thermo1_Thermozones_FunctionGroup_1   Thermozones_FunctionGroup_1;
  tNvmPara_Thermo1_Thermozones_FunctionGroup_2   Thermozones_FunctionGroup_2;
  tNvmPara_Thermo1_Thermozones_FunctionGroup_3   Thermozones_FunctionGroup_3;
  tNvmPara_Thermo1_Thermozones_FunctionGroup_4   Thermozones_FunctionGroup_4;
  tNvmPara_Thermo1_Thermzones_PowRateLimiter     Thermzones_PowRateLimiter;
  tNvmPara_Thermo1_ExtNTCsErrThresh_DebFilter    ExtNTCsErrThresh_DebFilter;
  tNvmPara_Thermo1_PCBNtc_ErrThresh              PCBNtc_ErrThresh;
} tNvmPara_Thermo1Block;

#endif // __CODM_PARA_THERMO_H__

// EOF

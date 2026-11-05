#ifndef _NVM_PARA_THERMO_H_
  #define _NVM_PARA_THERMO_H_


/*******************************************************************************
* types with INIT values:
*******************************************************************************/


// Temperature measurement and limitations by NTCs & RBins:

// the software supports 8 NTC,
// for this 8 NTC's the software supports 16 different NTC Tables
// 15 tables in ROM, 1 "free" table in NvM
// which table is used for which NTC is defined by this structue: 
typedef enum 
{
  NTC_CURVE_RAM   = 0, 
  NTC_CURVE_ROM1  = 1,
  NTC_CURVE_ROM2  = 2,
  NTC_CURVE_ROM3  = 3,
  NTC_CURVE_ROM4  = 4,
  NTC_CURVE_ROM5  = 5,
  NTC_CURVE_ROM6  = 6,
  NTC_CURVE_ROM7  = 7,
  NTC_CURVE_ROM8  = 8,
  NTC_CURVE_ROM9  = 9,
  NTC_CURVE_ROM10 = 10,
  NTC_CURVE_ROM11 = 11,
  NTC_CURVE_ROM12 = 12,
  NTC_CURVE_ROM13 = 13,
  NTC_CURVE_ROM14 = 14,
  NTC_CURVE_ROM15 = 15
}
eNvM_Para_Thermo_Thermo_NTCType;

typedef struct
{
  uint8     ALLOCATED_NTC_TYPE : 4;
  uint8     u4Bit_reserved     : 4;
}
tNvM_Para_Thermo_NTCType_Config;

typedef struct
{
  uint8  NODE_0 ;
  uint8  NODE_1 ;
  uint8  NODE_2 ;
  uint8  NODE_3 ;
  uint8  NODE_4 ;
  uint8  NODE_5 ;
  uint8  NODE_6 ;
  uint8  NODE_7 ;
  uint8  SHORT_GND_VALUE    ;
  uint8  OPEN_LOAD_VALUE    ;
  uint16 reserviert         ;
}
tNvmPara_Thermo_NTC_Resistor_InterpolationTable;

typedef struct
{
  tNvM_Para_Thermo_NTCType_Config                 ThermoConfigRSensNTCTypeAllocation[8];
  tNvmPara_Thermo_NTC_Resistor_InterpolationTable ThermoConfigRSensNTCTableforDevlopmentPhase;
}tNvmPara_Thermo_NTC_Config;                      // 8 Bytes + 12 Bytes

typedef struct
{ 
  sint8  T1_LEDCHAIN;
  sint8  T2_LEDCHAIN;
  uint8  T3_LEDCHAIN;
  uint8  T4_LEDCHAIN;
  uint8  T5_LEDCHAIN;
  uint8  DeratingFactor_T1;
  uint8  DeratingFactor_T4;
  uint8  DeratingFactor_T5;
}
tNvmPara_Thermo_NTCLimit;


typedef enum 
{
  RBIN_DEF_RAM   = 0, 
  RBIN_DEF_ROM1  = 1,
  RBIN_DEF_ROM2  = 2,
  RBIN_DEF_ROM3  = 3,
  RBIN_DEF_MAX   = 4
}
eNvM_Para_Thermo_Thermo_RBinType;

typedef struct
{
  uint8     ALLOCATED_RBIN_TYPE : 4;
  uint8     u4Bit_reserved      : 4;
}
tNvM_Para_Thermo_RBINType_Config;

typedef struct
{
  uint16  u16Input_Max;
  uint16  u16Input_Min;
  uint8   u8Output_Max;
  uint8   u8Output_Min;
  uint16  u16Value_ShortGnd;
  uint16  u16Value_OpenLoad;
  uint16  u16Reserved;
}
tNvmPara_Thermo_RBIN_Resistor_InterpolationTable;

typedef struct
{
  tNvM_Para_Thermo_RBINType_Config                 ThermoConfigRSensRbinTypeAllocation[8];
  tNvmPara_Thermo_RBIN_Resistor_InterpolationTable ThermoConfigRSensRbinTableforDevlopmentPhase;
}tNvmPara_Thermo_RBIN_Config;

typedef struct
{
  tNvmPara_Thermo_NTC_Config      Thermo_NTC_Config;         // 20 bytes ((8 * 1) + 12)
  tNvmPara_Thermo_NTCLimit        ThermoConfigNTCLimits[8];  // 64 bytes (8 * 8)
  tNvmPara_Thermo_RBIN_Config     ThermoConfigRbin;          // 20 bytes ((8 * 1) + 12)
} tNvmPara_Thermo;                                           // sum: 104 bytes

//generic PARAMS for all E3 Projects:
#define NVM_PARA_THERMO_CHIPLIMITS_C1  120    /*   DeratingStart_inCelsiusC1  */
#define NVM_PARA_THERMO_CHIPLIMITS_C2  120    /*   DeratingStart_inCelsiusC2  */
#define NVM_PARA_THERMO_CHIPLIMITS_C3  120    /*   DeratingStart_inCelsiusC3  */
#define NVM_PARA_THERMO_CHIPLIMITS_C4  120    /*   DeratingStart_inCelsiusC4  */


#define NVM_PARA_THERMO_PCBLIMI_TEMP1                125      /*   0: TEMP1                        */
#define NVM_PARA_THERMO_PCBLIMI_TEMP2                135      /*   2: TEMP2                        */
#define NVM_PARA_THERMO_PCBLIMI_DERATING_FACTOR_MAX  100      /*   1: Factor1                      */
#define NVM_PARA_THERMO_PCBLIMI_DERATING_FACTOR_MIN   30      /*   3: Factor1                      */


#define NVM_PARA_THERMO_NTC_RESISTOR_RAM_TABLE       \
{                                                    \
  254,   /* NODE_0 (ADC Raw Value / 16)         */   \
  248,   /* NODE_1 (ADC Raw Value / 16)         */   \
  236,   /* NODE_2 (ADC Raw Value / 16)         */   \
  139,   /* NODE_3 (ADC Raw Value / 16)         */   \
  125,   /* NODE_4 (ADC Raw Value / 16)         */   \
  120,   /* NODE_5 (ADC Raw Value / 16)         */   \
  118,   /* NODE_6 (ADC Raw Value / 16)         */   \
  114,   /* NODE_7 (ADC Raw Value / 16)         */   \
  31 ,   /* SHORT_GND_VALUE                     */   \
  255,   /* OPENLOAD_VALUE                      */   \
  0u     /* DUMMY  (reserviert)                 */   \
}

#endif // _NVM_PARA_THERMO_H_

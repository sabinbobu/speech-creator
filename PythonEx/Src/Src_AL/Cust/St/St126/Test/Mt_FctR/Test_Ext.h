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
/// \file  Test_Ext.h
///
/// \brief Stub functions for access to coding parameters excluded from test
///
//-----------------------------------------------------------------------------
#ifndef TEST_EXT_2022_09_07_H_
#define TEST_EXT_2022_09_07_H_

//=============================================================================
// Includes
//=============================================================================
#include <CodM_Para.h>
#include <FctR_Types.h>

//-----------------------------------------------------------------------------
// Types
//-----------------------------------------------------------------------------
extern tNvmPara_CodingArea*   applicationCodingData;
extern tNvmPara_CodingArea*   FctR_pCodingArea;

// Ecu mounting side
typedef enum
{
  Mount_Left   = 0,
  Mount_Right  = 1,
  Mount_Undef  = 255
}teEcuSide;


typedef enum { DRV_01 = 1, DRV_02, DRV_03, DRV_04, DRV_05, DRV_06, DRV_07, DRV_08, DRV_09, DRV_10, DRV_11, DRV_12, HSS3,  DRV_NOTUSED = 255  }eDrvId;
typedef enum { LMM_1  = 1,  LMM_2,  LMM_3,  LMM_4,  LMM_5,  LMM_6,  LMM_7,  LMM_8,                                 LMM_NOTUSED = 255         }eLMMId;
typedef enum { PXL_1  = 1,  PXL_2,  PXL_3,  PXL_4,  PXL_5,  PXL_6,  PXL_7,  PXL_8,  PXL_9, PXL_10, PXL_11, PXL_12, PXL_NOTUSED = 255         }eSwitchId;



#define LGHT_CFG_PWM_100   100u
#define LGHT_CFG_PWM_98    98u
#define LGHT_CFG_PWM_97    97u
#define LGHT_CFG_PWM_95    95u
#define LGHT_CFG_PWM_93    93u
#define LGHT_CFG_PWM_79    79u
#define LGHT_CFG_PWM_75    75u
#define LGHT_CFG_PWM_70    70u
#define LGHT_CFG_PWM_69    69u
#define LGHT_CFG_PWM_66    66u
#define LGHT_CFG_PWM_60    60u
#define LGHT_CFG_PWM_58    58u
#define LGHT_CFG_PWM_53    53u
#define LGHT_CFG_PWM_46    46u
#define LGHT_CFG_PWM_0      0u

#define LGHT_CFG_TON_0      0u
#define LGHT_CFG_TON_100    100u
#define LGHT_CFG_TOFF       0u
#define LGHT_CFG_TOFF_100   100u

#define LGHT_PRIO_0   0u
#define LGHT_PRIO_1   1u
#define LGHT_PRIO_2   2u
#define LGHT_PRIO_3   3u
#define LGHT_PRIO_4   4u
#define LGHT_PRIO_5   5u
#define LGHT_PRIO_6   6u
#define LGHT_PRIO_7   7u
#define LGHT_PRIO_8   8u
#define LGHT_PRIO_9   9u
#define LGHT_PRIO_10  10u
#define LGHT_PRIO_11  11u
#define LGHT_PRIO_12  12u
#define LGHT_PRIO_13  13u
#define LGHT_PRIO_14  14u
#define LGHT_PRIO_15  15u

#define LOG_LMP_1     0u
#define LOG_LMP_2     1u
#define LOG_LMP_3     2u
#define LOG_LMP_4     3u
#define LOG_LMP_5     4u
#define LOG_LMP_6     5u
#define LOG_LMP_7     6u
#define LOG_LMP_8     7u
#define LOG_LMP_9     8u
#define LOG_LMP_10    9u
#define LOG_LMP_11    10u
#define LOG_LMP_12    11u
#define LOG_LMP_13    12u
#define LOG_LMP_14    13u
#define LOG_LMP_15    14u
#define LOG_LMP_16    15u
#define LOG_LMP__UKN  255u


#define LGHT_CFG_RAMP     0u

#define LGHT_FBIT_ACTIVE       1u
#define LGHT_FBIT_NOT_ACTIVE   0u

#define LGHT_ABIT_ACTIVE       1u
#define LGHT_ABIT_NOT_ACTIVE   0u

#define FCTR_CFG_LUT_LSM \
{        /* {          ucPower,         ucTimeOn,          ucTimeOff,  4th byte(  biPriority :4,  biRampType :2,        biErrorImpact:1,  biActive:1)         }, */\
/* 0   */   { LGHT_CFG_PWM_93,     LGHT_CFG_TON_0,     LGHT_CFG_TOFF,                LGHT_PRIO_8 , LGHT_CFG_RAMP , LGHT_FBIT_NOT_ACTIVE , LGHT_ABIT_NOT_ACTIVE }, \
/* 1   */   { LGHT_CFG_PWM_95,     LGHT_CFG_TON_0,     LGHT_CFG_TOFF,                LGHT_PRIO_8 , LGHT_CFG_RAMP , LGHT_FBIT_NOT_ACTIVE , LGHT_ABIT_NOT_ACTIVE }, \
/* 2   */   { LGHT_CFG_PWM_98,     LGHT_CFG_TON_0,     LGHT_CFG_TOFF,                LGHT_PRIO_8 , LGHT_CFG_RAMP , LGHT_FBIT_NOT_ACTIVE , LGHT_ABIT_NOT_ACTIVE }, \
/* 3   */   { LGHT_CFG_PWM_97,     LGHT_CFG_TON_0,     LGHT_CFG_TOFF,                LGHT_PRIO_8 , LGHT_CFG_RAMP , LGHT_FBIT_NOT_ACTIVE , LGHT_ABIT_NOT_ACTIVE }, \
/* 4   */   { LGHT_CFG_PWM_0,    LGHT_CFG_TON_100,     LGHT_CFG_TOFF,               LGHT_PRIO_15 , LGHT_CFG_RAMP , LGHT_FBIT_NOT_ACTIVE , LGHT_ABIT_NOT_ACTIVE }, \
/* 5   */   { LGHT_CFG_PWM_97,     LGHT_CFG_TON_0,     LGHT_CFG_TOFF,                LGHT_PRIO_6 , LGHT_CFG_RAMP , LGHT_FBIT_NOT_ACTIVE , LGHT_ABIT_NOT_ACTIVE }, \
/* 6   */   { LGHT_CFG_PWM_95,     LGHT_CFG_TON_0,     LGHT_CFG_TOFF,                LGHT_PRIO_6 , LGHT_CFG_RAMP , LGHT_FBIT_NOT_ACTIVE , LGHT_ABIT_NOT_ACTIVE }, \
/* 7   */   { LGHT_CFG_PWM_100,    LGHT_CFG_TON_0,     LGHT_CFG_TOFF,               LGHT_PRIO_14 , LGHT_CFG_RAMP , LGHT_FBIT_NOT_ACTIVE , LGHT_ABIT_NOT_ACTIVE }, \
/* 8   */   { LGHT_CFG_PWM_97,     LGHT_CFG_TON_0,     LGHT_CFG_TOFF,                LGHT_PRIO_7 , LGHT_CFG_RAMP , LGHT_FBIT_NOT_ACTIVE , LGHT_ABIT_NOT_ACTIVE }, \
/* 9   */   { LGHT_CFG_PWM_100,    LGHT_CFG_TON_0,     LGHT_CFG_TOFF,                LGHT_PRIO_8 , LGHT_CFG_RAMP , LGHT_FBIT_NOT_ACTIVE , LGHT_ABIT_NOT_ACTIVE }, \
/* 10  */   { LGHT_CFG_PWM_79,     LGHT_CFG_TON_0,     LGHT_CFG_TOFF,                LGHT_PRIO_8 , LGHT_CFG_RAMP , LGHT_FBIT_NOT_ACTIVE , LGHT_ABIT_NOT_ACTIVE }, \
/* 11  */   { LGHT_CFG_PWM_58,     LGHT_CFG_TON_0,     LGHT_CFG_TOFF,                LGHT_PRIO_8 , LGHT_CFG_RAMP , LGHT_FBIT_NOT_ACTIVE , LGHT_ABIT_NOT_ACTIVE }, \
/* 12  */   { LGHT_CFG_PWM_70,     LGHT_CFG_TON_0,     LGHT_CFG_TOFF,                LGHT_PRIO_8 , LGHT_CFG_RAMP , LGHT_FBIT_NOT_ACTIVE , LGHT_ABIT_NOT_ACTIVE }, \
/* 13  */   { LGHT_CFG_PWM_75,     LGHT_CFG_TON_0,     LGHT_CFG_TOFF,                LGHT_PRIO_8 , LGHT_CFG_RAMP , LGHT_FBIT_NOT_ACTIVE , LGHT_ABIT_NOT_ACTIVE }, \
/* 14  */   { LGHT_CFG_PWM_69,     LGHT_CFG_TON_0,     LGHT_CFG_TOFF,                LGHT_PRIO_8 , LGHT_CFG_RAMP , LGHT_FBIT_NOT_ACTIVE , LGHT_ABIT_NOT_ACTIVE }, \
/* 15  */   { LGHT_CFG_PWM_98,     LGHT_CFG_TON_0,     LGHT_CFG_TOFF,                LGHT_PRIO_6 , LGHT_CFG_RAMP , LGHT_FBIT_NOT_ACTIVE , LGHT_ABIT_NOT_ACTIVE }, \
/* 16  */   { LGHT_CFG_PWM_46,     LGHT_CFG_TON_0,     LGHT_CFG_TOFF,               LGHT_PRIO_14 , LGHT_CFG_RAMP , LGHT_FBIT_NOT_ACTIVE , LGHT_ABIT_NOT_ACTIVE }, \
/* 17  */   { LGHT_CFG_PWM_98,     LGHT_CFG_TON_0,     LGHT_CFG_TOFF,                LGHT_PRIO_7 , LGHT_CFG_RAMP , LGHT_FBIT_NOT_ACTIVE , LGHT_ABIT_NOT_ACTIVE }, \
/* 18  */   { LGHT_CFG_PWM_0,      LGHT_CFG_TON_0,     LGHT_CFG_TOFF,                LGHT_PRIO_8 , LGHT_CFG_RAMP , LGHT_FBIT_NOT_ACTIVE , LGHT_ABIT_NOT_ACTIVE }, \
/* 19  */   { LGHT_CFG_PWM_0,      LGHT_CFG_TON_0,     LGHT_CFG_TOFF,                LGHT_PRIO_6 , LGHT_CFG_RAMP , LGHT_FBIT_NOT_ACTIVE , LGHT_ABIT_NOT_ACTIVE }, \
/* 20  */   { LGHT_CFG_PWM_0,      LGHT_CFG_TON_0,     LGHT_CFG_TOFF,               LGHT_PRIO_14 , LGHT_CFG_RAMP , LGHT_FBIT_NOT_ACTIVE , LGHT_ABIT_NOT_ACTIVE }, \
/* 21  */   { LGHT_CFG_PWM_0,      LGHT_CFG_TON_0,     LGHT_CFG_TOFF,                LGHT_PRIO_7 , LGHT_CFG_RAMP , LGHT_FBIT_NOT_ACTIVE , LGHT_ABIT_NOT_ACTIVE }, \
/* 22  */   { LGHT_CFG_PWM_100,    LGHT_CFG_TON_0,     LGHT_CFG_TOFF_100,            LGHT_PRIO_7 , LGHT_CFG_RAMP , LGHT_FBIT_NOT_ACTIVE , LGHT_ABIT_NOT_ACTIVE }, \
/* 23  */   { LGHT_CFG_PWM_100,    LGHT_CFG_TON_0,     LGHT_CFG_TOFF,                LGHT_PRIO_8 , LGHT_CFG_RAMP , LGHT_FBIT_ACTIVE     , LGHT_ABIT_NOT_ACTIVE }, \
/* 24  */   { LGHT_CFG_PWM_46,     LGHT_CFG_TON_0,     LGHT_CFG_TOFF,                LGHT_PRIO_8 , LGHT_CFG_RAMP , LGHT_FBIT_NOT_ACTIVE , LGHT_ABIT_ACTIVE     }, \
/* 25  */   { LGHT_CFG_PWM_0,      LGHT_CFG_TON_0,     LGHT_CFG_TOFF,                LGHT_PRIO_7 , LGHT_CFG_RAMP , LGHT_FBIT_NOT_ACTIVE , LGHT_ABIT_ACTIVE     }, \
/* 26  */   { LGHT_CFG_PWM_100,    LGHT_CFG_TON_0,     LGHT_CFG_TOFF,                LGHT_PRIO_6 , LGHT_CFG_RAMP , LGHT_FBIT_NOT_ACTIVE , LGHT_ABIT_NOT_ACTIVE }, \
/* 27  */   { LGHT_CFG_PWM_100,    LGHT_CFG_TON_0,     LGHT_CFG_TOFF,                LGHT_PRIO_7 , LGHT_CFG_RAMP , LGHT_FBIT_NOT_ACTIVE , LGHT_ABIT_NOT_ACTIVE }, \
/* 28  */   { LGHT_CFG_PWM_0,      LGHT_CFG_TON_0,     LGHT_CFG_TOFF,               LGHT_PRIO_15 , LGHT_CFG_RAMP , LGHT_FBIT_NOT_ACTIVE , LGHT_ABIT_NOT_ACTIVE }, \
/* 29  */   { LGHT_CFG_PWM_0,      LGHT_CFG_TON_0,     LGHT_CFG_TOFF,               LGHT_PRIO_15 , LGHT_CFG_RAMP , LGHT_FBIT_NOT_ACTIVE , LGHT_ABIT_NOT_ACTIVE }, \
/* 30  */   { LGHT_CFG_PWM_0,      LGHT_CFG_TON_0,     LGHT_CFG_TOFF,               LGHT_PRIO_15 , LGHT_CFG_RAMP , LGHT_FBIT_NOT_ACTIVE , LGHT_ABIT_NOT_ACTIVE }, \
/* 31  */   { LGHT_CFG_PWM_0,      LGHT_CFG_TON_0,     LGHT_CFG_TOFF,               LGHT_PRIO_15 , LGHT_CFG_RAMP , LGHT_FBIT_NOT_ACTIVE , LGHT_ABIT_NOT_ACTIVE }, \
/* 32  */   { LGHT_CFG_PWM_0,      LGHT_CFG_TON_0,     LGHT_CFG_TOFF,               LGHT_PRIO_15 , LGHT_CFG_RAMP , LGHT_FBIT_NOT_ACTIVE , LGHT_ABIT_NOT_ACTIVE }, \
/* 33  */   { LGHT_CFG_PWM_0,      LGHT_CFG_TON_0,     LGHT_CFG_TOFF,               LGHT_PRIO_15 , LGHT_CFG_RAMP , LGHT_FBIT_NOT_ACTIVE , LGHT_ABIT_NOT_ACTIVE }, \
/* 34  */   { LGHT_CFG_PWM_0,      LGHT_CFG_TON_0,     LGHT_CFG_TOFF,               LGHT_PRIO_15 , LGHT_CFG_RAMP , LGHT_FBIT_NOT_ACTIVE , LGHT_ABIT_NOT_ACTIVE }, \
/* 35  */   { LGHT_CFG_PWM_0,      LGHT_CFG_TON_0,     LGHT_CFG_TOFF,               LGHT_PRIO_15 , LGHT_CFG_RAMP , LGHT_FBIT_NOT_ACTIVE , LGHT_ABIT_NOT_ACTIVE }, \
/* 36  */   { LGHT_CFG_PWM_0,      LGHT_CFG_TON_0,     LGHT_CFG_TOFF,               LGHT_PRIO_15 , LGHT_CFG_RAMP , LGHT_FBIT_NOT_ACTIVE , LGHT_ABIT_NOT_ACTIVE }, \
/* 37  */   { LGHT_CFG_PWM_0,      LGHT_CFG_TON_0,     LGHT_CFG_TOFF,               LGHT_PRIO_15 , LGHT_CFG_RAMP , LGHT_FBIT_NOT_ACTIVE , LGHT_ABIT_NOT_ACTIVE }, \
/* 38  */   { LGHT_CFG_PWM_0,      LGHT_CFG_TON_0,     LGHT_CFG_TOFF,               LGHT_PRIO_15 , LGHT_CFG_RAMP , LGHT_FBIT_NOT_ACTIVE , LGHT_ABIT_NOT_ACTIVE }, \
/* 39  */   { LGHT_CFG_PWM_0,      LGHT_CFG_TON_0,     LGHT_CFG_TOFF,               LGHT_PRIO_15 , LGHT_CFG_RAMP , LGHT_FBIT_NOT_ACTIVE , LGHT_ABIT_NOT_ACTIVE }, \
}

//tNvmPara_Lmm_Row Config_Illuminants_Table[] = FCTR_CFG_ILLUMINAT_LSM;
//const tNvmPara_Lmm_LutCell ConfigTable[] = FCTR_CFG_LUT_LSM;


#define FCTR_CFG_ILLUMINAT_LSM  \
{ \
                                             /* IL1 , IL2, IL3, IL4, IL5, IL6, IL7, IL8, IL9, IL10, IL11, IL12, IL13, IL14, IL15, IL16 */\
/* 0  - Low Beam LD1 - Town Light (class V) */ {   0,   9,  11,  18,   4,   4,   4,   4,   4,    4,    4,    4,    4,    4,    9,    4  }, \
/* 1  - Low Beam LD2 - Pedestrian           */ {   0,   9,  11,  18,   4,   4,   4,   4,   4,    4,    4,    4,    4,    4,    9,    4  }, \
/* 2  - Low Beam LD3 - Country (class C)    */ {   1,   9,  12,  18,   4,   4,   4,   4,   4,    4,    4,    4,    4,    4,    9,    4  }, \
/* 3  - Low Beam LD4 - Motorway Light       */ {   1,   3,  10,  18,   4,   4,   4,   4,   4,    4,    4,    4,    4,    4,    9,    4  }, \
/* 4  - Low Beam LD5 - Low Beam Boost       */ {   2,   9,   9,  18,   4,   4,   4,   4,   4,    4,    4,    4,    4,    4,    9,    4  }, \
/* 5  - Low Beam LD6 - Bad Weather RHD      */ {   1,   9,  13,  12,   4,   4,   4,   4,   4,    4,    4,    4,    4,    4,    9,    4  }, \
/* 6  - Low Beam LD7 - Foggy Weather RHD    */ {   1,   10, 12,   9,   4,   4,   4,   4,   4,    4,    4,    4,    4,    4,    9,    4  }, \
/* 7  - Low Beam LD8 - Bad Weather LHD      */ {   3,   9,  13,  12,   4,   4,   4,   4,   4,    4,    4,    4,    4,    4,    9,    4  }, \
/* 8  - Low Beam LD9 - Foggy Weather LHD    */ {   1,   10, 14,   9,   4,   4,   4,   4,   4,    4,    4,    4,    4,    4,    9,    4  }, \
/* 9  - Low Beam LD10 - Reserved            */ {   4,   4,   4,   4,   4,   4,   4,   4,   4,    4,    4,    4,    4,    4,    4,    4  }, \
/* 10 - Low Beam LD11 - Reserved            */ {   4,   4,   4,   4,   4,   4,   4,   4,   4,    4,    4,    4,    4,    4,    4,    4  }, \
/* 11 - Low Beam LD12 - Reserved            */ {   4,   4,   4,   4,   4,   4,   4,   4,   4,    4,    4,    4,    4,    4,    4,    4  }, \
/* 12 - Low Beam LD13 - Reserved            */ {   4,   4,   4,   4,   4,   4,   4,   4,   4,    4,    4,    4,    4,    4,    4,    4  }, \
/* 13 - High Beam LD1 - High Beam           */ {   5,   5,  15,  19,   4,   4,   4,   4,   4,    4,    4,    4,    4,    4,   26,   26  }, \
/* 14 - High Beam LD2 - High Beam Boost     */ {   6,   6,   5,  19,   4,   4,   4,   4,   4,    4,    4,    4,    4,    4,   26,   26  }, \
/* 15 - High Beam LD3 - Adjustement Mode    */ {   7,   7,   7,  20,   4,   4,   4,   4,   4,    4,    4,    4,    4,    4,    7,    7  }, \
/* 16 - High Beam LD4 - Aiming Mode         */ {   7,   7,  16,  20,   4,   4,   4,   4,   4,    4,    4,    4,    4,    4,    7,    7  }, \
/* 17 - High Beam LD5 - FlashToPass         */ {   8,   8,  17,  21,   4,   4,   4,   4,   4,    4,    4,    4,    4,    4,   27,   27  }, \
/* 18 - High Beam LD6 - Reserved            */ {   4,   4,   4,   4,   4,   4,   4,   4,   4,    4,    4,    4,    4,    4,    4,    4  }, \
/* 19 - High Beam LD7 - Reserved            */ {   4,   4,   4,   4,   4,   4,   4,   4,   4,    4,    4,    4,    4,    4,    4,    4  }, \
/* 20 - High Beam LD8 - Reserved            */ {   4,   4,   4,   4,   4,   4,   4,   4,   4,    4,    4,    4,    4,    4,    4,    4  }, \
/* 21 - High Beam LD9 - Reserved            */ {   4,   4,   4,   4,   4,   4,   4,   4,   4,    4,    4,    4,    4,    4,    4,    4  }, \
/* 22 - Daytime Running Light DRL           */ {   4,   4,   4,   4,   4,   4,   4,  23,  23,   23,    4,    4,    4,    4,    4,    4  }, \
/* 23 - Position Light                      */ {   4,   4,   4,   4,   4,   4,   4,  24,  24,   24,    4,    4,    4,    4,    4,    4  }, \
/* 24 - Parking Light                       */ {   4,   4,   4,   4,   4,   4,   4,  24,  24,   24,    4,    4,    4,    4,    4,    4  }, \
/* 25 - Static Bending Light (SBL)          */ {   4,   4,   4,  22,   4,   4,   4,   4,   4,    4,    4,    4,    4,    4,    4,    4  }, \
/* 26 - Cornering Light (CL)                */ {   4,   4,   4,   4,   4,   4,   4,   4,   4,    4,    4,    4,    4,    4,    4,    4  }, \
/* 27 - Fog Light                           */ {   4,   4,   4,   4,   4,   4,   4,   4,   4,    4,    4,    4,    4,    4,    4,    4  }, \
/* 28 - Side Marker                         */ {   4,   4,   4,   4,   4,   4,   4,   4,   4,    4,    4,    4,    4,    4,    4,    4  }, \
/* 29 - Turn Indicator                      */ {   4,   4,   4,   4,   4,   4,   4,  25,  25,   25,    9,    4,    4,    4,    4,    4  }, \
/* 30 - Turn Indicator PO                   */ {   4,   4,   4,   4,   4,   4,   4,  25,  25,   25,    9,    4,    4,    4,    4,    4  }, \
/* 31 - Turn Indicator Freq PO              */ {   4,   4,   4,   4,   4,   4,   4,   4,   4,    4,    4,    4,    4,    4,    4,    4  }, \
/* 32 - Invalid                             */ {   4,   4,   4,   4,   4,   4,   4,  23,  23,   23,    4,    4,    4,    4,    4,    4  }, \
}


//-----------------------------------------------------------------------------
// Access specific coding parameters
//-----------------------------------------------------------------------------

void FctR_CreateCodingData_FULLVariant(void);

#endif // TEST_EXT_2022_09_07_H_

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
/// \file  AppM.h
///
/// \brief The software component AppM applies the binning current and duty 
///        cycle to the light sources, reduces the light source duty cycle due 
///        to thermal and supply voltage influences and requests the fan and 
///        CMD activation due to environmental conditions.
///        These functionalities are needed to protect the ECU and head lamp 
///        from thermal and electric damage.
///
//-----------------------------------------------------------------------------
#ifndef APP_M_2019_12_12_H_
#define APP_M_2019_12_12_H_


#ifndef UNIT_TEST
#include <Rte.h>
#endif
#include <RteCommonTypes.h>
#include <AL_Helper.h>

CONST_AL  tNvmPara_CodingArea*  CPM_pCodingArea;

//-----------------------------------------------------------------------------
//  "define" and "typedef" statements at the module level
//-----------------------------------------------------------------------------
#ifndef CPM_CFG_ERR_SNA
#define CPM_CFG_ERR_SNA 0U
#endif /*CPM_CFG_ERR_SNA*/

#ifndef CPM_CFG_ERR_NO
#define CPM_CFG_ERR_NO 2U
#endif /*CPM_CFG_ERR_NO*/

#ifndef CPM_CFG_ERR_YES
#define CPM_CFG_ERR_YES 1U
#endif /*CPM_CFG_ERR_YES*/

#define CPM_PWM_MAX_0_100                            100u
#define CPM_HSS3_INDEX                               12u

#define CPM_HSS3_DRVINDEX                            13u
#define CPM_FANHYSTERESIS_RESOLUTION                 1000u
#define CPM_MV_RESOLUTION                            100u
#ifndef UNIT_TEST
#define CPM_PERCENT_VAL                              32767u
#else
#define CPM_PERCENT_VAL                              100u
#endif
#define CPM_FROM_CTRLLED_PERCENT_VAL                 1000u
#define CPM_CFG_LED_MAX_NO_OF_LS_CHANNELS            CFG_LED_CHANNELS_NR
#define CPM_CFG_MAX_NO_OF_THERMOZONES                CFG_THERMOZONES_NR
#define CPM_CFG_MAX_NO_OF_MLC                        7u
#define CPM_CFG_MAX_NO_OF_SWITCHES_ON_MLC            12u
#define CPM_CFG_MAX_NO_OF_LOGICAL_UNIT               CFG_LOGICAL_UNITS
#define CPM_CFG_BIN_MAX_NO_OF_CLASSES                5u
#define CPM_FANM_PARA_HYSTERESIS                     20000
#define CPM_FAN_NR                                   2u
#define CPM_CFG_MATRIX_BUCK                          1u
#define CPM_CFG_NON_MATRIX_BUCK                      0u
#define CPM_SCALING_65535                            0xFFFFu
#ifndef UNIT_TEST
#define CPM_SCALING_32768                            0x8000u
#else 
#define CPM_SCALING_32768                            0xEEEEu
#endif
#define CPM_CFG_UNKNOWN_BINNING                      0xFFu
#define CPM_SCALING_1000                             0x03E8u
#define CPM_MAX_NO_OF_IO_TEMP                        14u
#define CPM_FIRST_INDEX_MLC                          15u
#define CPM_NR_OF_FAN                                2u
#define CPM_MAX_LIMIT_FOR_FALLING_RISING_LIMITER     100
#define CPM_RATE_LIMITER_RESOLUTION                  100
#define CPM_100_PERCENT_LIMITER                      10000
#define CPM_SCALING_X_TO_Y_VALUE(x, y, val) ((val) == 0u) ? 0u : (uint16)( ( (uint32)((uint32)(y) * (uint32)(val))   ) / (uint32)(x)) //scaling number (from x->y)
// Ecu operating mode
typedef enum
{
  eEcu_StandBy = 0u,
  eEcu_NormalMode = 1u,
  eEcu_SwitchToStandBy = 2u,
  eEcu_Wake = 3u,
  eEcu_COM_OFF = 4u
}teCPM_EcuOperationgMode;

// Signal quality
typedef enum
{
  eEcu_SIG_SNA = 0U,
  eEcu_SIG_VALID = 1U,
  eEcu_SIG_INIT = 2U,
  eEcu_SIG_INVALID = 3U,
  eEcu_SIG_TIMEOUT = 4U,
  eEcu_SIG_DEFAULT = 5U,
  eEcu_SIG_E2E_CRCERR = 6U,
  eEcu_SIG_E2E_ALIVEERR = 7U,
  eEcu_SIG_E2E_TIMEOUT = 8U,
  eEcu_SIG_UNAVAILABLE = 9U,
  eEcu_SIG_DISABLED = 255U
}teCPM_SigQty;

typedef enum
{
  eCPM_MountedLeft = 0u,
  eCPM_MountedRight = 1u,
  eCPM_MountedUndef = 255u
}teCPM_MountingSide;

typedef struct
{
  teCPM_EcuOperationgMode       ePhaseVie;
  teCPM_SigQty         eSigQty; // Signal Quality
}tsCPM_LifePhases;

typedef struct tsCPM_PowFactTemp {
  sint16 snNTCTemperatureCelsius[CPM_CFG_MAX_NO_OF_THERMOZONES];
  uint8  ucPowerFactor[CPM_CFG_MAX_NO_OF_THERMOZONES];
}tsCPM_PowFactTemp;

static tis32Temperature_mCelsius AppM_lPcbTemperature0 = 0;

typedef unsigned long tiu32TempChannel;


typedef struct
{
  sint32 lVal;
  tiu32TempChannel ulTempChannel;
  tieSigQty eQty;
}tisTemperature_mCelsius;

typedef unsigned long tiu32LsChannel;


typedef unsigned short tiu16Percent_1_328;

typedef struct
{
  tiu16Current_mA unCurrent;
  tiu16Percent_1_328 unDutyCycle;
}tisLsTarget;


typedef struct tAppMThermo_CodHelper
{
  uint8 Drv_Unit : 4; //LED driver number
  uint8 Lmms_Unit : 4; //LMM number
  uint8 SwNr_Unit : 4; //Switchnumber
  uint8 ThermZone_Unit : 4; //Thermozone
  uint8 BasePwm_Unit; //Base PWM  
} tAppMThermo_CodHelper;

typedef struct
{
  tiu16Percent_1_328 unCurrent;
  tiu16Percent_1_328 unDutyCycle;
}tisLsTarget_perc;

typedef unsigned char tiu8Binning;
typedef unsigned long tiu32Resistance_Ohm;

typedef tiu16Percent_1_328 tiu16Percent_1_328Arr16[16];

typedef struct
{
  tieHssState aeSetting[3];
}tisHssTarget;

typedef struct
{


  tiu8Binning ucVal;




  tieSigQty eQty;


}tisBinning;

void rpCpm20ms(void);
void riCpmInit(void);


  typedef Std_ReturnType(*tRteCurrent) (uint16*);
  typedef Std_ReturnType(*tRteDutyCycle) (uint8*);
  typedef Std_ReturnType(*tRteTemp) (uint8*);
  typedef Std_ReturnType(*tRteBool) (boolean*);
  typedef Std_ReturnType(*tRteShort) (uint8*);

#endif // APP_M_2019_12_12_H_

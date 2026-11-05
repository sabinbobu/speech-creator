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
/// \brief Stub functions for access to software modules excluded from test
///
//-----------------------------------------------------------------------------
#ifndef TEST_EXT_2021_08_19_H_
#define TEST_EXT_2021_08_19_H_


#include <Std_Types.h>

//boolean                     Test_EftDataValid(void);
//void                        Test_SetEftDataValid(boolean boValid);

//-----------------------------------------------------------------------------
// Types
//-----------------------------------------------------------------------------
typedef struct
{
  uint8 BOOST_VOLT_HEADROOM; // Offset for booster voltage. Booster voltage
  uint8 BOOST_VOLT_ERROR_THRESHOLD; // Fault threshold for detecting a booster error.
  uint8 BOOST_VOLT_ERROR_DEBOUNCE; // Debounce counter for the booster fault detection
}
tPara_Led1_LedBoostConverter;

typedef struct
{
  uint8 LED_OPEN_LOAD_VALUE; // Fault threshold for detecting open load error.
  uint8 LED_SHORT_UBAT_RANGE; // Fault threshold for detecting "short-circuit
  uint8 LED_SHORT_UBAT_DEBOUNCE; // Debounce counter for "short-circuit to Ubat"-Failure
  uint8 LED_OVERCURRENT_DEBOUNCE; // Debounce counter for overcurrent fault detection
}
tPara_Led1_LedErrDetect;

typedef struct
{
  uint8 FUSA_DRV_LED_UNDER_VOLTAGE[12];
  uint8 FUSA_DRV_LED_OVER_VOLTAGE[12];
}
tPara_Led1_FUSAConfig;

typedef struct
{
  tPara_Led1_LedBoostConverter        LedBoostConverter;
  tPara_Led1_LedErrDetect             LedErrDetect;
  tPara_Led1_FUSAConfig               FUSAConfig;
} tPara_Led1Block;

typedef struct
{
  tPara_Led1Block             Led1;
} tPara_CodingArea;


extern tPara_CodingArea applicationCodingData;

//-----------------------------------------------------------------------------
// Access to chip specific implementation
//-----------------------------------------------------------------------------
#define CDDBOOST_Drv_Init()          Test_Driver_Init()
#define CDDBOOST_Drv_Shutdown()
#define CDDBOOST_Drv_SetBoosterVoltage(Idx,VBoost_mV)

#define CDDBOOST_Drv_IsReset(Idx)                      Test_IsReset(Idx)
#define CDDBOOST_Drv_IsSpiError(Idx)                   Test_IsSpiError(Idx)
#define CDDBOOST_Drv_IsThermalShutDown(Idx)            Test_IsThermalShutDown(Idx)
#define CDDBOOST_Drv_IsThermalWarning(Idx)             Test_IsThermalWarning(Idx)


//-----------------------------------------------------------------------------
// Access to IoHwAbUser
//-----------------------------------------------------------------------------
#define CDDBOOST_GetECUSupply(pVolt)     Test_GetECUSupply(pVolt)


//-----------------------------------------------------------------------------
// Parameter access
//-----------------------------------------------------------------------------
#define CDDBOOST_Para_LED_VBAT_MIN_ON_V   6500u     // (100u * (uint32)applicationCodingData.Led1.LedSupplyVoltage.LED_VBAT_MIN_ON_V)  // [0.1V]-->[mV]
#define CDDBOOST_Para_BOOST_VOLT_HEADROOM             (100u * (uint32)applicationCodingData.Led1.LedBoostConverter.BOOST_VOLT_HEADROOM)        // [0.1V]-->[mV]
#define CDDBOOST_Para_FUSA_DRV_LED_OVER_VOLTAGE(x)    (200u * (uint32)applicationCodingData.Led1.FUSAConfig.FUSA_DRV_LED_OVER_VOLTAGE[x])      // [0.2V]-->[mV]

#define CDDLED_Cfg_NbOfChannels       12u

void   RestoreStubContents(void);

uint32 Test_Driver_Init(void);

boolean Test_IsReset(uint32 ulIdx);
boolean Test_IsSpiError(uint32 ulIdx);
boolean Test_IsThermalShutDown(uint32 ulIdx);
boolean Test_IsThermalWarning(uint32 ulIdx);

void Test_SetReset          (uint32 ulIdx, boolean boReset);
void Test_SetSpiError       (uint32 ulIdx, boolean boSpiErr);
void Test_SetThermalShutDown(uint32 ulIdx, boolean boTSD);
void Test_SetThermalWarning (uint32 ulIdx, boolean boTW);

void Test_GetECUSupply(uint32* pulVolt);
void Test_SetECUSupply(uint32 ulVolt);



#endif // TEST_EXT_2021_08_19_H_

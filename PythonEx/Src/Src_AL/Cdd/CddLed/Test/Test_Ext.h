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


//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Types
//-----------------------------------------------------------------------------
typedef struct
{
uint8 BOOST_VOLT_HEADROOM             ; // Offset for booster voltage. Booster voltage
uint8 BOOST_VOLT_ERROR_THRESHOLD      ; // Fault threshold for detecting a booster error.
uint8 BOOST_VOLT_ERROR_DEBOUNCE       ; // Debounce counter for the booster fault detection
}
tPara_Led1_LedBoostConverter;

typedef struct
{
uint8 LED_OPEN_LOAD_VALUE             ; // Fault threshold for detecting open load error.
uint8 LED_SHORT_UBAT_RANGE            ; // Fault threshold for detecting "short-circuit
uint8 LED_SHORT_UBAT_DEBOUNCE         ; // Debounce counter for "short-circuit to Ubat"-Failure
uint8 LED_OVERCURRENT_DEBOUNCE        ; // Debounce counter for overcurrent fault detection
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
#define CDDLED_Drv_Init()                    Test_Drv_Init()
#define CDDLED_Drv_Cycle20ms()               // intentionally empty

#define CDDLED_Drv_SetCurrent(Idx,Current)   Test_Drv_SetCurrent  (Idx, Current)
#define CDDLED_Drv_SetDutyCycle(Idx,Duty)    Test_Drv_SetDutyCycle(Idx, Duty)

#define CDDLED_Drv_GetInputVoltage_mV(Idx)   Test_Drv_GetInputVoltage_mV(Idx)
#define CDDLED_Drv_GetLedVoltage_mV(Idx,Ptr) Test_Drv_GetLedVoltage_mV  (Idx,Ptr)

#define CDDLED_Drv_IsShortToGnd(Idx)         Test_Drv_IsShortToGnd(Idx)
#define CDDLED_Drv_IsOpenLoad(Idx)           Test_Drv_IsOpenLoad  (Idx)

#define CDDLED_Drv_GetCurrent_mA(Idx)         Test_Drv_GetCurrent_mA       (Idx)
#define CDDLED_Drv_GetDutyCycle_1_32768(Idx)  Test_Drv_GetDutyCycle_1_32768(Idx)

#define CDDLED_Drv_IsDriverActive(Idx)        Test_Drv_IsDriverActive   (Idx)
#define CDDLED_Drv_IsOvercurrent(Idx)         Test_Drv_IsOvercurrent    (Idx)
#define CDDLED_Drv_IsThermalShutDown(Idx)     Test_Drv_IsThermalShutDown(Idx)
#define CDDLED_Drv_IsThermalWarning(Idx)      Test_Drv_IsThermalWarning (Idx)
#define CDDLED_Drv_IsSpiError(Idx)            Test_Drv_IsSpiError       (Idx)


//-----------------------------------------------------------------------------
// Access to IoHwAbUser
//-----------------------------------------------------------------------------
#define CDDLED_GetECUSupply(pVolt)           Test_GetECUSupply(pVolt)


// Stub functions
uint32  Test_Drv_Init                (void);  
void    Test_Drv_SetCurrent          (uint32 ulChnIdx, uint16 unCurrent);
void    Test_Drv_SetDutyCycle        (uint32 ulChnIdx, uint16 unDuty);
uint16  Test_Drv_GetInputVoltage_mV  (uint32 ulChnIdx);
boolean Test_Drv_GetLedVoltage_mV    (uint32 ulChnIdx, uint16* punVoltage);
uint16  Test_Drv_GetLedVoltOnOff_mV  (uint32 ulChnIdx);
uint16  Test_Drv_GetCurrent_mA       (uint32 ulChnIdx);
uint16  Test_Drv_GetDutyCycle_1_32768(uint32 ulChnIdx);
boolean Test_Drv_IsDriverActive      (uint32 ulChnIdx);
boolean Test_Drv_IsShortToGnd        (uint32 ulChnIdx);
boolean Test_Drv_IsOpenLoad          (uint32 ulChnIdx);
boolean Test_Drv_IsOvercurrent       (uint32 ulChnIdx);
boolean Test_Drv_IsThermalShutDown   (uint32 ulChnIdx);
boolean Test_Drv_IsThermalWarning    (uint32 ulChnIdx);
boolean Test_Drv_IsSpiError          (uint32 ulChnIdx);

void    Test_GetECUSupply            (uint32* pulVolt);

// Functions to set/read stub values
uint16  Test_Drv_GetCurrent          (uint32 ulChnIdx);
uint16  Test_Drv_GetDutyCycle        (uint32 ulChnIdx);
void    Test_Drv_SetInitVal          (uint32 ulInitVal);
void    Test_Drv_SetInputVoltage_mV  (uint32 ulChnIdx, uint16  unInputVoltage);
void    Test_Drv_SetLedVoltage_mV    (uint32 ulChnIdx, uint16  unLedVoltage, boolean boValid);
void    Test_Drv_SetLedVoltOnOff_mV  (uint32 ulChnIdx, uint16  unLedVoltOnOff);
void    Test_Drv_SetCurrent_mA       (uint32 ulChnIdx, uint16  unCurrent);
void    Test_Drv_SetDutyCycle_1_32768(uint32 ulChnIdx, uint16  unDutyCycle);
void    Test_Drv_SetDriverActive     (uint32 ulChnIdx, boolean boDriverActive);
void    Test_Drv_SetShortToGnd       (uint32 ulChnIdx, boolean boShortGnd);
void    Test_Drv_SetOpenLoad         (uint32 ulChnIdx, boolean boOpenLoad);
void    Test_Drv_SetOvercurrent      (uint32 ulChnIdx, boolean boOvercurren);
void    Test_Drv_SetThermalShutDown  (uint32 ulChnIdx, boolean boThermalShutDown);
void    Test_Drv_SetThermalWarning   (uint32 ulChnIdx, boolean boThermalWarning);
void    Test_Drv_SetSpiError         (uint32 ulChnIdx, boolean boSpiError);


//-----------------------------------------------------------------------------
// Access to IoHwAbUser
//-----------------------------------------------------------------------------
#define CDDLED_Para_BOOST_VOLT_HEADROOM           (100u * (uint32)applicationCodingData.Led1.LedBoostConverter.BOOST_VOLT_HEADROOM)        // [0.1V]-->[mV]
#define CDDLED_Para_BOOST_VOLT_ERROR_THRESHOLD    (100u * (uint32)applicationCodingData.Led1.LedBoostConverter.BOOST_VOLT_ERROR_THRESHOLD) // [0.1V]-->[mV]
#define CDDLED_Para_FUSA_DRV_LED_UNDER_VOLTAGE(x) (200u * (uint32)applicationCodingData.Led1.FUSAConfig.FUSA_DRV_LED_UNDER_VOLTAGE[x])     // [0.2V]-->[mV]
#define CDDLED_Para_FUSA_DRV_LED_OVER_VOLTAGE(x)  (200u * (uint32)applicationCodingData.Led1.FUSAConfig.FUSA_DRV_LED_OVER_VOLTAGE[x])      // [0.2V]-->[mV]
#define CDDLED_Para_LED_SHORT_UBAT_RANGE                          applicationCodingData.Led1.LedErrDetect.LED_SHORT_UBAT_RANGE             // [%]
#define CDDLED_Para_LED_OVERCURRENT_DEBOUNCE                      applicationCodingData.Led1.LedErrDetect.LED_OVERCURRENT_DEBOUNCE         // [20ms]


// Function to initialize stub values
void RestoreStubContents(void);


#endif // TEST_EXT_2021_08_19_H_

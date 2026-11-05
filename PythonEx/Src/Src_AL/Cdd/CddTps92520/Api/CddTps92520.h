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
/// \file   CddTps92520.h
///
/// \brief  API for CddTps92520
///
/// \author OTT, Peter ALDE-RT/EES6
//-----------------------------------------------------------------------------
#ifndef CDD_TPS92520_2021_01_21_H_
#define CDD_TPS92520_2021_01_21_H_


//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <Std_Types.h>


//-----------------------------------------------------------------------------
// version
//-----------------------------------------------------------------------------
#define CDDTPS92520_VERSION_MAJOR   2
#define CDDTPS92520_VERSION_MINOR   0
#define CDDTPS92520_VERSION_PATCH   0


//-----------------------------------------------------------------------------
// release notes
//-----------------------------------------------------------------------------
// 2.0.0  Changed format of CddTps92520_GetLedVoltage_mV
//        CddTps92520_GetLedOnOffVoltage_mV removed
//        Support of missing buck driver #0
//        SPI fault handling                                --> to do
//        Analog values sampled at 10ms (schedule table change)
//        IFT timer set to 3.6ms
//        Dynamic adaption of buck frequency
// 1.3.1  Bugfix for pseudo open load errors after repairing open load conditions
// 1.3.0  Bugfix for pseudo open load and short to GND errors
// 1.2.0  MPU support
// 1.1.0  Averaging of analog values
//        Full implementation of CddTps92520_aboMultiLed
// 1.0.0  Add support for VLED_OFF, BUCK_EN
//        Switch off BUCK_EN depending on LED voltage
//        Add dummy functions to read back duty cycle and current
//        Modify function interface
//        Optimize current calculation
//        Check if status from driver is valid
//        Add voltage check for open load
//        Add check of target PWM for voltage evaluation
// 0.0.2  Add function CddTps92520_SpiGetConfig()
// 0.0.1  Change schedule table to leave standalone mode at startup
// 0.0.0  Initial version based on FLM3 implementation


//-----------------------------------------------------------------------------
// open issues
//-----------------------------------------------------------------------------
// Value of EFT parameter AssignedOutput is not used --> not planned
// Value of EFT parameter Pmax and Imin are not used --> not planned
// Implementation of CddTps92520_GetCurrent_mA       --> not planned


//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Start declaration or definitions of functions
//-----------------------------------------------------------------------------
#define ctadCddLed_START_SEC_CODE
#include <../Cfg/CddTps92520_MemMap.h>

uint32  CddTps92520_Init(void);  
void    CddTps92520_Cycle20ms(void);

void    CddTps92520_SetCurrent_mA        (const uint32 ulChnIdx, const uint16 unCurrent);
void    CddTps92520_SetDutyCycle_1_32768 (const uint32 ulChnIdx, const uint16 unDuty);

uint16  CddTps92520_GetCurrent_mA        (const uint32 ulChnIdx);
uint16  CddTps92520_GetDutyCycle_1_32768 (const uint32 ulChnIdx);

uint16  CddTps92520_GetInputVoltage_mV   (const uint32 ulChnIdx);
boolean CddTps92520_GetLedVoltage_mV     (const uint32 ulChnIdx, uint16* punVoltage);

boolean CddTps92520_IsDriverActive       (const uint32 ulChnIdx);
boolean CddTps92520_IsShortToGnd         (const uint32 ulChnIdx);
boolean CddTps92520_IsOpenLoad           (const uint32 ulChnIdx);
boolean CddTps92520_IsOvercurrent        (const uint32 ulChnIdx);
boolean CddTps92520_IsThermalShutDown    (const uint32 ulChnIdx);
boolean CddTps92520_IsThermalWarning     (const uint32 ulChnIdx);
boolean CddTps92520_IsSpiError           (const uint32 ulChnIdx);

#define ctadCddLed_STOP_SEC_CODE
#include <../Cfg/CddTps92520_MemMap.h>
//-----------------------------------------------------------------------------
// End declaration or definitions of functions
//-----------------------------------------------------------------------------


#endif // CDD_TPS92520_2021_01_21_H_

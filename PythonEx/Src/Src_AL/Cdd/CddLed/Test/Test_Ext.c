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
/// \file  Test_Ext.c
///
/// \brief Stub functions for access to software modules excluded from test
///
//-----------------------------------------------------------------------------
#include <../Cfg/CddLed_Cfg.h>
#include <Test_Ext.h>


#define TEST_BACK 0  // index 0 used for backup
#define TEST_USE  1  // index 1 used for operation

#define TEST_Cfg_Channels 12u  // support up to 12 channels for test

#if (CDDLED_Cfg_NbOfChannels > TEST_Cfg_Channels)
  #error Test not supported
#endif


//-----------------------------------------------------------------------------
// Stub variables
//-----------------------------------------------------------------------------
tPara_CodingArea applicationCodingData = { { { 30u, 50u, 50u }, { 50u, 10u, 15u, 5u },
  { { 0u,   0u, 0u, 50u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u },
    { 0u, 185u, 0u,  0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } } } };  // booster voltage will be (185 * .2 + 30/10 - 50/10)V = 37V

struct
{
  uint32  ulInitResp;
  uint16  aunTgtCurrent       [TEST_Cfg_Channels];
  uint16  aunTgtDutyCycle     [TEST_Cfg_Channels];
  uint16  aunInputVoltage     [TEST_Cfg_Channels];
  uint16  aunLedVoltage       [TEST_Cfg_Channels];
  uint16  aunLedVoltOnOff     [TEST_Cfg_Channels];
  uint16  aunActCurrent       [TEST_Cfg_Channels];
  uint16  aunActDutyCycle     [TEST_Cfg_Channels];
  boolean aboIsDriverActive   [TEST_Cfg_Channels];
  boolean aboIsShortToGnd     [TEST_Cfg_Channels];
  boolean aboIsOpenLoad       [TEST_Cfg_Channels];
  boolean aboIsOvercurrent    [TEST_Cfg_Channels];
  boolean aboIsThermalShutDown[TEST_Cfg_Channels];
  boolean aboIsThermalWarning [TEST_Cfg_Channels];
  boolean aboIsSpiError       [TEST_Cfg_Channels];
  boolean aboLedVoltageValid  [TEST_Cfg_Channels];
}
TestStruct[2] =
{
  {
    0x0FFF,   // 12 channels
    {     0u,     0u,     0u,     0u,     0u,     0u,     0u,     0u,     0u,     0u,     0u,     0u },  // target current
    {     0u,     0u,     0u,     0u,     0u,     0u,     0u,     0u,     0u,     0u,     0u,     0u },  // target duty cycle
    { 45000u, 45000u, 45000u, 45000u, 45000u, 45000u, 45000u, 45000u, 45000u, 45000u, 45000u, 45000u },  // InputVoltage
    {     0u,     0u,     0u,     0u,     0u,     0u,     0u,     0u,     0u,     0u,     0u,     0u },  // LedVoltage
    {  1000u,   500u,  2000u,  3000u,  1000u,     0u,     0u,     0u,     0u,     0u,     0u,     0u },  // LedVoltOnOff
    {     0u,     0u,     0u,     0u,     0u,     0u,     0u,     0u,     0u,     0u,     0u,     0u },  // actual current
    {     0u,     0u,     0u,     0u,     0u,     0u,     0u,     0u,     0u,     0u,     0u,     0u },  // actual dutyCycle
    {  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE },  // driver active
    {  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE },  // short to GND
    {  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE },  // open load
    {  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE },  // overcurrent
    {  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE },  // thermal shutdown
    {  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE },  // thermal warning
    {  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE,  FALSE },  // SPI error
    {  TRUE,   TRUE,   TRUE,   TRUE,   TRUE,   TRUE,   TRUE,   TRUE,   TRUE,   TRUE,   TRUE,   TRUE  }   // LedVoltage valid
  }
};


//-----------------------------------------------------------------------------
// Stub functions
//-----------------------------------------------------------------------------
void    Test_Drv_SetCurrent   (uint32 ulChnIdx, uint16 unCurrent)   { TestStruct[TEST_USE].aunTgtCurrent  [ulChnIdx] = unCurrent; }
void    Test_Drv_SetDutyCycle (uint32 ulChnIdx, uint16 unDuty)      { TestStruct[TEST_USE].aunTgtDutyCycle[ulChnIdx] = unDuty;    }

boolean Test_Drv_GetLedVoltage_mV(uint32 ulChnIdx, uint16* punVoltage)
{
  *punVoltage = TestStruct[TEST_USE].aunLedVoltage[ulChnIdx];

  return TestStruct[TEST_USE].aboLedVoltageValid[ulChnIdx];
}

uint32  Test_Drv_Init                (void)                    { return TestStruct[TEST_USE].ulInitResp;                     }
uint16  Test_Drv_GetInputVoltage_mV  (uint32 ulChnIdx)         { return TestStruct[TEST_USE].aunInputVoltage     [ulChnIdx]; }
uint16  Test_Drv_GetLedVoltOnOff_mV  (uint32 ulChnIdx)         { return TestStruct[TEST_USE].aunLedVoltOnOff     [ulChnIdx]; }
uint16  Test_Drv_GetCurrent_mA       (uint32 ulChnIdx)         { return TestStruct[TEST_USE].aunActCurrent       [ulChnIdx]; }
uint16  Test_Drv_GetDutyCycle_1_32768(uint32 ulChnIdx)         { return TestStruct[TEST_USE].aunActDutyCycle     [ulChnIdx]; }
boolean Test_Drv_IsDriverActive      (uint32 ulChnIdx)         { return TestStruct[TEST_USE].aboIsDriverActive   [ulChnIdx]; }
boolean Test_Drv_IsShortToGnd        (uint32 ulChnIdx)         { return TestStruct[TEST_USE].aboIsShortToGnd     [ulChnIdx]; }
boolean Test_Drv_IsOpenLoad          (uint32 ulChnIdx)         { return TestStruct[TEST_USE].aboIsOpenLoad       [ulChnIdx]; }
boolean Test_Drv_IsOvercurrent       (uint32 ulChnIdx)         { return TestStruct[TEST_USE].aboIsOvercurrent    [ulChnIdx]; }
boolean Test_Drv_IsThermalShutDown   (uint32 ulChnIdx)         { return TestStruct[TEST_USE].aboIsThermalShutDown[ulChnIdx]; }
boolean Test_Drv_IsThermalWarning    (uint32 ulChnIdx)         { return TestStruct[TEST_USE].aboIsThermalWarning [ulChnIdx]; }
boolean Test_Drv_IsSpiError          (uint32 ulChnIdx)         { return TestStruct[TEST_USE].aboIsSpiError       [ulChnIdx]; }


void    Test_GetECUSupply            (uint32* pulVolt)
{
  *pulVolt = 13000u;
}


//-----------------------------------------------------------------------------
// Functions to set/read stub values
//-----------------------------------------------------------------------------
uint16  Test_Drv_GetCurrent  (uint32 ulChnIdx)  { return TestStruct[TEST_USE].aunTgtCurrent  [ulChnIdx]; }
uint16  Test_Drv_GetDutyCycle(uint32 ulChnIdx)  { return TestStruct[TEST_USE].aunTgtDutyCycle[ulChnIdx]; }

void Test_Drv_SetLedVoltage_mV(uint32 ulChnIdx, uint16 unLedVoltage, boolean boValid)
{
  TestStruct[TEST_USE].aunLedVoltage     [ulChnIdx] = unLedVoltage;
  TestStruct[TEST_USE].aboLedVoltageValid[ulChnIdx] = boValid;
}

void    Test_Drv_SetInitVal          (uint32 ulInitVal)                           { TestStruct[TEST_USE].ulInitResp                     = ulInitVal;         }
void    Test_Drv_SetInputVoltage_mV  (uint32 ulChnIdx, uint16  unInputVoltage)    { TestStruct[TEST_USE].aunInputVoltage     [ulChnIdx] = unInputVoltage;    }
void    Test_Drv_SetLedVoltOnOff_mV  (uint32 ulChnIdx, uint16  unLedVoltOnOff)    { TestStruct[TEST_USE].aunLedVoltOnOff     [ulChnIdx] = unLedVoltOnOff;    }
void    Test_Drv_SetCurrent_mA       (uint32 ulChnIdx, uint16  unCurrent)         { TestStruct[TEST_USE].aunActCurrent       [ulChnIdx] = unCurrent;         }
void    Test_Drv_SetDutyCycle_1_32768(uint32 ulChnIdx, uint16  unDutyCycle)       { TestStruct[TEST_USE].aunActDutyCycle        [ulChnIdx] = unDutyCycle;    }
void    Test_Drv_SetDriverActive     (uint32 ulChnIdx, boolean boDriverActive)    { TestStruct[TEST_USE].aboIsDriverActive   [ulChnIdx] = boDriverActive;    }
void    Test_Drv_SetShortToGnd       (uint32 ulChnIdx, boolean boShortGnd)        { TestStruct[TEST_USE].aboIsShortToGnd     [ulChnIdx] = boShortGnd;        }
void    Test_Drv_SetOpenLoad         (uint32 ulChnIdx, boolean boOpenLoad)        { TestStruct[TEST_USE].aboIsOpenLoad       [ulChnIdx] = boOpenLoad;        }
void    Test_Drv_SetOvercurrent      (uint32 ulChnIdx, boolean boOvercurrent)     { TestStruct[TEST_USE].aboIsOvercurrent    [ulChnIdx] = boOvercurrent;     }
void    Test_Drv_SetThermalShutDown  (uint32 ulChnIdx, boolean boThermalShutDown) { TestStruct[TEST_USE].aboIsThermalShutDown[ulChnIdx] = boThermalShutDown; }
void    Test_Drv_SetThermalWarning   (uint32 ulChnIdx, boolean boThermalWarning)  { TestStruct[TEST_USE].aboIsThermalWarning [ulChnIdx] = boThermalWarning;  }
void    Test_Drv_SetSpiError         (uint32 ulChnIdx, boolean boSpiError)        { TestStruct[TEST_USE].aboIsSpiError       [ulChnIdx] = boSpiError;        }


//-----------------------------------------------------------------------------
// Function to initialize stub values
//-----------------------------------------------------------------------------
void RestoreStubContents(void)
{
  TestStruct[TEST_USE] = TestStruct[TEST_BACK];
}


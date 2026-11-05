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
/// \file   CddTps92520_Com.h
///
/// \brief  SPI communication interface
///
/// \author OTT, Peter ALDE-RT/EES6
//-----------------------------------------------------------------------------
#ifndef CDD_TPS92520_COM_2021_01_21_H_
#define CDD_TPS92520_COM_2021_01_21_H_


//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <Std_Types.h>

#include <../Gen/CddTps92520_Types.h>
#include <../Cfg/CddTps92520_Cfg.h>


//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------
#define CDDTPS92520_NbOfBit_SPIFrame         16u
#define CDDTPS92520_ParityBit            0x0100u // Set parity bit (bit8) to '1'


//-----------------------------------------------------------------------------
// Mirror TPS92520 regiters
//-----------------------------------------------------------------------------
typedef struct tCddTps92520_CtrlReg
{
  tCddTps92520_SYSCFG1    aSYSCFG1                           [CDDTPS92520_Cfg_NbOfDevices];
  tCddTps92520_SYSCFG2    aSYSCFG2                           [CDDTPS92520_Cfg_NbOfDevices];
  tCddTps92520_CMWTAP     aCMWTAP                            [CDDTPS92520_Cfg_NbOfDevices];
  tCddTps92520_TWLMT      aTWLMT                             [CDDTPS92520_Cfg_NbOfDevices];
  tCddTps92520_SLEEP      aSLEEP                             [CDDTPS92520_Cfg_NbOfDevices];
  tCddTps92520_CHxIADJL   aCHxIADJL [CDDTPS92520_NbOfChannel][CDDTPS92520_Cfg_NbOfDevices];
  tCddTps92520_CHxIADJH   aCHxIADJH [CDDTPS92520_NbOfChannel][CDDTPS92520_Cfg_NbOfDevices];
  tCddTps92520_PWMDIV     aPWMDIV                            [CDDTPS92520_Cfg_NbOfDevices];
  tCddTps92520_CHxPWML    aCHxPWML  [CDDTPS92520_NbOfChannel][CDDTPS92520_Cfg_NbOfDevices];
  tCddTps92520_CHxPWMH    aCHxPWMH  [CDDTPS92520_NbOfChannel][CDDTPS92520_Cfg_NbOfDevices];
  tCddTps92520_CHxTON     aCHxTON   [CDDTPS92520_NbOfChannel][CDDTPS92520_Cfg_NbOfDevices];
  tCddTps92520_LHCFG1     aLHCFG1                            [CDDTPS92520_Cfg_NbOfDevices];
  tCddTps92520_RESET      aRESET                             [CDDTPS92520_Cfg_NbOfDevices];
}tCddTps92520_CtrlReg;

typedef struct tCddTps92520_StatReg
{
  tCddTps92520_STATUS1     aSTATUS1                            [CDDTPS92520_Cfg_NbOfDevices];
  tCddTps92520_STATUS2     aSTATUS2                            [CDDTPS92520_Cfg_NbOfDevices];
  tCddTps92520_STATUS3     aSTATUS3                            [CDDTPS92520_Cfg_NbOfDevices];
  tCddTps92520_CHxVIN      aCHxVIN    [CDDTPS92520_NbOfChannel][CDDTPS92520_Cfg_NbOfDevices];
  tCddTps92520_CHxVLED     aCHxVLED   [CDDTPS92520_NbOfChannel][CDDTPS92520_Cfg_NbOfDevices];
  tCddTps92520_CHxVLEDON   aCHxVLEDON [CDDTPS92520_NbOfChannel][CDDTPS92520_Cfg_NbOfDevices];
  tCddTps92520_TEMPL       aTEMPL                              [CDDTPS92520_Cfg_NbOfDevices];
  tCddTps92520_TEMPH       aTEMPH                              [CDDTPS92520_Cfg_NbOfDevices];
  tCddTps92520_V5D         aV5D                                [CDDTPS92520_Cfg_NbOfDevices];
}tCddTps92520_StatReg;

typedef struct tCddTps92520_DataMirror
{
  tCddTps92520_CtrlReg CtrlTx;
  tCddTps92520_CtrlReg CtrlRx;
  tCddTps92520_StatReg StatRx;
}tCddTps92520_DataMirror;


//-----------------------------------------------------------------------------
// Interfaces
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Start declaration or definitions of functions
//-----------------------------------------------------------------------------
#define ctadCddLed_START_SEC_CODE
#include <../Cfg/CddTps92520_MemMap.h>

void    CddTps92520_EnableChannel(const uint32 ulChIdx,  const boolean               boEn);
void    CddTps92520_SetCHxIADJH  (const uint32 ulChnIdx, const uint8                 ucCHxIDJH);
void    CddTps92520_SetCHxIADJL  (const uint32 ulChnIdx, const tCddTps92520_CHxIADJL CHxIADJL);
void    CddTps92520_SetCHxTON    (const uint32 ulChnIdx, const uint8 ucCHxTON);

boolean CddTps92520_GetSTATUS1   (const uint32 ulChnIdx, tCddTps92520_STATUS1* pSTATUS1);
boolean CddTps92520_GetSTATUS2   (const uint32 ulChnIdx, tCddTps92520_STATUS2* pSTATUS2);
boolean CddTps92520_GetSTATUS3   (const uint32 ulChnIdx, tCddTps92520_STATUS3* pSTATUS3);

uint32  CddTps92520_GetCHxVIN    (const uint32 ulChnIdx);
uint32  CddTps92520_GetCHxVLED   (const uint32 ulChnIdx);
uint32  CddTps92520_GetCHxVLEDON (const uint32 ulChnIdx);

boolean CddTps92520_GetCHxIADJL  (const uint32 ulChnIdx, uint8* pucCHxIADJL);
boolean CddTps92520_GetCHxIADJH  (const uint32 ulChnIdx, uint8* pucCHxIADJH);

boolean CddTps92520_GetSpiError  (const uint32 ulChnIdx);

#define ctadCddLed_STOP_SEC_CODE
#include <../Cfg/CddTps92520_MemMap.h>
//-----------------------------------------------------------------------------
// End declaration or definitions of functions
//-----------------------------------------------------------------------------


#endif // CDD_TPS92520_COM_2021_01_21_H_

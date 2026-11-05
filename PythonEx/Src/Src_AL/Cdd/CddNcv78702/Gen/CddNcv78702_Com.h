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
/// \file  CddNcv78702_Com.h
///
/// \brief Header file for NCV78702 SPI communication code
///
/// \author OTT, Peter ALDE-RT/EES6
//-----------------------------------------------------------------------------
#ifndef CDD_NCV78702_COM_2021_03_26_H_
#define CDD_NCV78702_COM_2021_03_26_H_


//=============================================================================
// Includes
//=============================================================================
#include <Std_Types.h>

#include <../Gen/CddNcv78702_Types.h>
#include <../Cfg/CddNcv78702_Cfg.h>


//=============================================================================
// Defines
//=============================================================================
#define CDDNCV78702_NbOfBit_SPIFrame 16u
#define CDDNCV78702_ParityBitReadFrame 0x0200u
#define CDDNCV78702_ParityBitWriteFrame 0x0400u

//=============================================================================
// Mirror NCV78702 regiters
//=============================================================================
typedef struct tCddNcv78702_CtrlReg
{
  tCddNcv78702_Reg0x00 Reg0x00;
  tCddNcv78702_Reg0x01 Reg0x01;
  tCddNcv78702_Reg0x02 Reg0x02;
  tCddNcv78702_Reg0x03 Reg0x03;
  tCddNcv78702_Reg0x04 Reg0x04;
  tCddNcv78702_Reg0x05 Reg0x05;
  tCddNcv78702_Reg0x06 Reg0x06;
  tCddNcv78702_Reg0x07 Reg0x07;
  tCddNcv78702_Reg0x08 Reg0x08;
  tCddNcv78702_Reg0x09 Reg0x09;
}tCddNcv78702_CtrlReg;

typedef struct tCddNcv78702_StatReg
{
  tCddNcv78702_Reg0x0A Reg0x0A;
  tCddNcv78702_Reg0x0B Reg0x0B;
  tCddNcv78702_Reg0x0C Reg0x0C;
  tCddNcv78702_Reg0x0D Reg0x0D;
}tCddNcv78702_StatReg;

typedef struct tCddNcv78702_DataMirror
{
  tCddNcv78702_CtrlReg CtrlTx;
  tCddNcv78702_CtrlReg CtrlRx;
  tCddNcv78702_StatReg StatRx;
}tCddNcv78702_DataMirror;

//-----------------------------------------------------------------------------
// Start declaration or definitions of functions
//-----------------------------------------------------------------------------
#define ctadCddBoost_START_SEC_CODE
#include <../Cfg/CddNcv78702_MemMap.h>

void CddNcv78702_SetBoostVsetpoint  (const uint8 ucBoostVsetpoint);
void CddNcv78702_SetBoostBstSyncDuty(const uint16  unBstSyncDuty_1_32768);
void CddNcv78702_SetBoostEnableGpio (const boolean boBoostEnable);
void CddNcv78702_SetBoostSleep      (void);
#if defined (CFG_VARIANT_ECO) || defined (UNIT_TEST)
void CddNcv78702_SetBoostOverVoltageThr(void);
#endif

boolean CddNcv78702_GetReg0x0A(tCddNcv78702_Reg0x0A* pReg0x0A);

#define ctadCddBoost_STOP_SEC_CODE
#include <../Cfg/CddNcv78702_MemMap.h>
//-----------------------------------------------------------------------------
// End declaration or definitions of functions
//-----------------------------------------------------------------------------

#endif // CDD_NCV78702_COM_2021_03_26_H_

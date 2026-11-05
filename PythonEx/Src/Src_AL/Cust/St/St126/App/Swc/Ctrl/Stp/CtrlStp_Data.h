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
/// \file  CtrlStp_Data.h
///
/// \brief Access for CtrlStp to coding data
///
//-----------------------------------------------------------------------------
#ifndef CTRL_STP_DATA_2020_06_30_H_
#define CTRL_STP_DATA_2020_06_30_H_


//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <Std_Types.h>
#include <AL_Helper.h>
#ifndef UNIT_TEST
#include <Rte.h>
#endif // !UNIT_TEST
#include <../Swc/Ctrl/Stp/Api/CtrlStp.h>
#include <CodM_Para_AvacStp.h>

#ifdef UNIT_TEST
#include <RteCommonTypes.h> 
#endif //UNIT_TEST


//=============================================================================
// Types
//=============================================================================
typedef struct
{
  sint16 snAvacStp_AfsLevelling_Town_Ped;  // AFS OFFSET For town
  sint16 snAvacStp_AfsLevelling_MW;        // AFS OFFSET For motorway
  sint16 snAvacStp_AfsLevelling_MW_Boost;  // AFS OFFSET For motorway boosted, left headlamp
  sint16 snAvacStp_AfsLevelling_BDW_LHD;   // AFS OFFSET For badweather Left hand drive
  sint16 snAvacStp_AfsLevelling_BDW_RHD;   // AFS OFFSET For badweather Right hand drive
  sint16 snAvacStp_AfsLevelling_Foggy_LHD; // AFS OFFSET For Foggy left hand drive,
  sint16 snAvacStp_AfsLevelling_Foggy_RHD; // AFS OFFSET For Foggy right hand drive
  sint16 snAvacStp_AfsLevelling_Off;       // AFS OFFSET For state OFF
  sint16 snAvacStp_AfsLevelling_HB;        // AFS OFFSET For when High beam is activated
}
tCtrlStp_AvacStp_AfsOffset;

typedef struct
{
  uint16 unAvacStp_LowerStpBlockRange;
  uint16 unAvacStp_UpperStpBlockRange;
  uint16 unAvacStp_LowerStpMovementRange;
  uint16 unAvacStp_UpperStpMovementRange;
  uint8  ucAvacStp_ParkingLowering : 7;
  uint8  ucAvacStp_ParkingSign : 1;
  uint8  ucAvacStp_SafetyPos : 7; 
  uint8  ucAvacStp_SafetySign : 1;
  uint8  ucAvacStp_Hs_Degree_Denominator;
  uint16 unAvacStp_Hs_Degree_Counter;
  uint16 unAvacStp_Transmission_Factor;
  uint8  ucAvacStp_Direction : 1;
}
tCtrlStp_AvacStp_SwGeo;

//-----------------------------------------------------------------------------
// proptotypes
//-----------------------------------------------------------------------------
boolean CtrlStp_CodingDataReady(teCtrlStp_MountingSide* pMountingSide);
void CtrlStp_ParaFct0(tParaFct0_Cmd eCmd,tNvmPara_CodingArea* pData);

uint16  Cod_LwrAnschlagMi        (void);
uint16  Cod_LwrAnschlagPl        (void);
uint16  Cod_LwrMaxWinkelMi       (void);
uint16  Cod_LwrMaxWinkelPl       (void);
sint16  Cod_LwrAp                (void);
sint16  Cod_LwrSp                (void);
uint16  Cod_LwrHsZeitSp          (void);
uint16  Cod_LwrHsZeitAp          (void);
uint16  Cod_LwrHsZeitMinTt       (void);
boolean Cod_LwrEnable            (void);
uint16  Cod_LwrHsGrad            (void);
uint8   Cod_LwrHsWertStart       (void);
boolean Cod_LwrTestDlAktiv       (void);
uint16  Cod_LwrTestDlWeg         (void);
uint16  Cod_LwrTestDlPeriode     (void);
uint8   Cod_LwrWellRefTimeout    (void);
uint8   Cod_LwrAutorefZeitversatz(void);
sint16  Cod_AfsLevellingHBOffset(void);
sint16  Cod_AfsLevellingTownPedOffset(void);
sint16  Cod_AfsLevellingMWBoostOffset(void);
sint16  Cod_AfsLevellingMWOffset(void);
sint16  Cod_AfsLevellingLeftBdwLhdOffset(void);
sint16  Cod_AfsLevellingLeftBdwRhdOffset(void);
sint16  Cod_AfsLevellingLeftFoggyLhdOffset(void);
sint16  Cod_AfsLevellingLeftFoggyRhdOffset(void);
sint16  Cod_AfsLevellingOffOffset(void);
uint8   Cod_AfsLevellingHBAperture(void);
uint8   Cod_AfsLevellingGFHBOffAngSpd(void);
uint8   Cod_AfsLevellingGFHBOffSgmDim(void);
uint8   Cod_AfsLevellingGFHBOnAngSpd(void);
uint8   Cod_AfsLevellingGFHBOnSgmDim(void);
uint16  Cod_AfsLevellingCorrectSpeed(void);
uint16  Cod_LwrMaxRefSpeed(void);
uint16  Cod_LwrSttDelay(void);
uint16  Cod_GFHBOffsetLevellingDelay(void);
uint16  Cod_LevellingStepperFailureReportTime(void);

#endif // CTRL_STP_DATA_2020_06_30_H_

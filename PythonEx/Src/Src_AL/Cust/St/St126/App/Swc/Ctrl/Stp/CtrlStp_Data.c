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
/// \file  CtrlStp_Data.c
///
/// \brief Access for CtrlStp to coding data
///
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
//#include <IntegrationTest.h>
#include "CtrlStp_Data.h"
#include <CtrlStp_RteAccess.h>

//-----------------------------------------------------------------------------
// local types
//-----------------------------------------------------------------------------
typedef struct
{
  uint16  unLwrAnschlagMi;
  uint16  unLwrAnschlagPl;
  uint16  unLwrMaxWinkelMi;
  uint16  unLwrMaxWinkelPl;
  uint16  unLwrHsZeitAp;
  uint16  unLwrHsZeitSp;
  uint16  unLwrHsZeitMinTt;
  uint16  unLwrHsGrad;
  uint16  unLwrTestDlWeg;
  uint16  unLwrTestDlPeriode;
  sint16  nLwrAp;
  sint16  nLwrSp;
  uint8   ucLwrHsWertStart;
  boolean boLwrEnable;
  boolean boLwrTestDlAktiv;
  uint8   ucLwrWellRefTimeout;
  uint8   ucLwrAutorefZeitversatz;
} tCtrlStp_CodingData;

//-----------------------------------------------------------------------------
// variables
//-----------------------------------------------------------------------------
//STATIC_AL tCtrlStp_CodingData CtrlStp_CodingData;

STATIC_AL tNvmPara_AvacStpBlock CtrlStp_CodingData = NVMPARA_AVACSTPBLOCK_INIT;
STATIC_AL sint16 CtrlStp_SafetyPos;
STATIC_AL sint16 CtrlStp_ParkingPos;
STATIC_AL tCtrlStp_AvacStp_SwGeo     CtrlStp_sHeadlampGeo = { 0 };
STATIC_AL tCtrlStp_AvacStp_AfsOffset CtrlStp_sAfsOffset   = { 0 };
//-----------------------------------------------------------------------------
// interface functions
//-----------------------------------------------------------------------------
uint16  Cod_LwrAnschlagMi(void)         { return CtrlStp_sHeadlampGeo.unAvacStp_LowerStpBlockRange;        }
uint16  Cod_LwrAnschlagPl(void)         { return CtrlStp_sHeadlampGeo.unAvacStp_UpperStpBlockRange;        }
uint16  Cod_LwrMaxWinkelMi(void)        { return CtrlStp_sHeadlampGeo.unAvacStp_LowerStpMovementRange;     }
uint16  Cod_LwrMaxWinkelPl(void)        { return CtrlStp_sHeadlampGeo.unAvacStp_UpperStpMovementRange;     }
sint16  Cod_LwrAp(void)                 { return CtrlStp_ParkingPos;                                       } // 6883
sint16  Cod_LwrSp(void)                 { return CtrlStp_SafetyPos;                                        } // 6883
uint16  Cod_LwrHsZeitAp(void)           { return CtrlStp_CodingData.Dynamik.unAvacStp_HsPeriod_PP;         }
uint16  Cod_LwrHsZeitSp(void)           { return CtrlStp_CodingData.Dynamik.unAvacStp_HsPeriod_SP;         }
uint16  Cod_LwrHsZeitMinTt(void)        { return CtrlStp_CodingData.Dynamik.unAvacStp_HsPeriodMin_LT;      }
boolean Cod_LwrEnable(void)             { return (boolean)CtrlStp_CodingData.Modus.ucAvacStp_Enable;       }
uint16  Cod_LwrHsGrad(void)             { return CtrlStp_sHeadlampGeo.unAvacStp_Transmission_Factor;       }
uint8   Cod_LwrHsWertStart(void)        { return CtrlStp_CodingData.Modus.ucAvacStp_Movement_Threshold_HS; }
boolean Cod_LwrTestDlAktiv(void)        { return (boolean)CtrlStp_CodingData.Modus.ucAvacStp_TestActive;   }
uint16  Cod_LwrTestDlWeg(void)          { return CtrlStp_CodingData.Modus.ucAvacStp_Test_AdjRange;         }
uint16  Cod_LwrTestDlPeriode(void)      { return CtrlStp_CodingData.Modus.ucAvacStp_Test_AdjPeriod;        }
uint8   Cod_LwrWellRefTimeout(void)     { return 100; }//CtrlStp_CodingData.ucLwrWellRefTimeout;      }
uint8   Cod_LwrAutorefZeitversatz(void) { return CtrlStp_CodingData.Modus.ucAvacStp_Autoreferencing_Delay; }
sint16  Cod_AfsLevellingHBOffset(void)              { return CtrlStp_sAfsOffset.snAvacStp_AfsLevelling_HB;        }
sint16  Cod_AfsLevellingTownPedOffset(void)         { return CtrlStp_sAfsOffset.snAvacStp_AfsLevelling_Town_Ped;  }
sint16  Cod_AfsLevellingMWBoostOffset(void)         { return CtrlStp_sAfsOffset.snAvacStp_AfsLevelling_MW_Boost;  }
sint16  Cod_AfsLevellingMWOffset(void)              { return CtrlStp_sAfsOffset.snAvacStp_AfsLevelling_MW;        }
sint16  Cod_AfsLevellingLeftBdwLhdOffset(void)      { return CtrlStp_sAfsOffset.snAvacStp_AfsLevelling_BDW_LHD;   }
sint16  Cod_AfsLevellingLeftBdwRhdOffset(void)      { return CtrlStp_sAfsOffset.snAvacStp_AfsLevelling_BDW_RHD;   }
sint16  Cod_AfsLevellingLeftFoggyLhdOffset(void)    { return CtrlStp_sAfsOffset.snAvacStp_AfsLevelling_Foggy_LHD; }
sint16  Cod_AfsLevellingLeftFoggyRhdOffset(void)    { return CtrlStp_sAfsOffset.snAvacStp_AfsLevelling_Foggy_RHD; }
sint16  Cod_AfsLevellingOffOffset(void)             { return CtrlStp_sAfsOffset.snAvacStp_AfsLevelling_Off;       }
//uint8   Cod_AfsLevellingHBAperture(void)             { return CtrlStp_CodingData.AfsOffset_OperationData.ucHB_APERTURE;}
//uint8   Cod_AfsLevellingGFHBOffAngSpd(void)          { return CtrlStp_CodingData.AfsOffset_OperationData.ucGFHB_CURTAIN_EFFECT_OFF_ANGULAR_SPEED*5u;}
//uint8   Cod_AfsLevellingGFHBOffSgmDim(void)          { return CtrlStp_CodingData.AfsOffset_OperationData.ucGFHB_CURTAIN_EFFECT_OFF_SEGMENT_DIMING*5u/100u;}
//uint8   Cod_AfsLevellingGFHBOnAngSpd(void)           { return CtrlStp_CodingData.AfsOffset_OperationData.ucGFHB_CURTAIN_EFFECT_ON_ANGULAR_SPEED*5u;}
//uint8   Cod_AfsLevellingGFHBOnSgmDim(void)           { return CtrlStp_CodingData.AfsOffset_OperationData.ucGFHB_CURTAIN_EFFECT_ON_SEGMENT_DIMING*5u/100u;}
uint16  Cod_AfsLevellingCorrectSpeed(void)           { return CtrlStp_CodingData.AfsOffset_OperationData.unOFFSET_AFS_CORRECT_SPEED*5u/100u;}
uint16  Cod_LwrMaxRefSpeed(void)                     { return CtrlStp_CodingData.PitchData.unREFERENCING_SPEED_MAX * 100u; }
uint16  Cod_LwrSttDelay(void)                        { return CtrlStp_CodingData.PitchData.unSTT_TRANSITION_DELAY; }
uint16  Cod_GFHBOffsetLevellingDelay(void)           { return CtrlStp_CodingData.AfsOffset_OperationData.unGFHB_OFFSET_LEVELLING_DELAY; }
uint16  Cod_LevellingStepperFailureReportTime(void)  { return (uint16)CtrlStp_CodingData.Modus.ucAvacStp_Levelling_Stepper_Failure_Report_Time * 100u; }

//-----------------------------------------------------------------------------
/// \brief  Check if coding data are available
///
/// \descr  Check also EFT data (in this case coding data is illegal)
///         and mounting side (needed to select coding data)
///
/// \param  pMountingSide
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CtrlStp_CodingDataReady(teCtrlStp_MountingSide* pMountingSide)
{
  boolean         boRet = FALSE;

  tsRteCodingParameters sCodingParameters;

  (void)Rte_Read_CodM_CtrlStp_Para(&sCodingParameters);

  if ((((uint8)*pMountingSide == (uint8)eMountedLeft) || ((uint8)*pMountingSide == (uint8)eMountedRight))
    && (sCodingParameters.eCodingState == eParaFct0_CodingDataValid))
  {
    boRet = TRUE;
  }

  return boRet;

}


//-----------------------------------------------------------------------------
/// \brief  Read coding data
///
/// \descr  Read coding data and store results in local variables
///         Do scaling calculations if needed
///
/// \param  MountingSide
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_ParaFct0 (tParaFct0_Cmd eCmd, tNvmPara_CodingArea*  pData)
{
#if defined (UNIT_TEST)
 extern boolean         boLwrApVz;
 extern boolean         boLwrSpVz;
#else

  boolean         boLwrApVz;
  boolean         boLwrSpVz;
#endif
  uint8           ucLwrTestDlPeriode;
  uint8           ucLwrApWert;
  uint8           ucLwrSpWert;
  teCtrlStp_MountingSide eMountingSide;

  (void)CtrlStp_RteAccess_Read_EcuSide(&eMountingSide);

  if (eCmd == eParaFct0_CodingDataValid)
  {
   CtrlStp_CodingData = pData->AvacStp;
  }
  else
  {
   // leave init values
  }
  
  ucLwrSpWert = CtrlStp_CodingData.SwGeoLi.ucAvacStp_SafetyPos_L;
  ucLwrApWert = CtrlStp_CodingData.SwGeoLi.ucAvacStp_ParkingLowering_L;

  boLwrSpVz = (CtrlStp_CodingData.SwGeoLi.ucAvacStp_SafetySign_L == 1u) ? TRUE : FALSE;

  CtrlStp_SafetyPos  = (boLwrSpVz != FALSE) ? (-1 * (sint16)ucLwrSpWert) : ((sint16)ucLwrSpWert);  // stored in [0.01deg]
  CtrlStp_ParkingPos = (boLwrApVz != FALSE) ? (-5 * (sint16)ucLwrApWert) : (5 * (sint16)ucLwrApWert);  // stored in [0.05deg]

  if (eMountingSide == CtrlStp_eMountedLeft)
  {
    CtrlStp_sHeadlampGeo.unAvacStp_LowerStpBlockRange    = CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpBlockRange_L;
    CtrlStp_sHeadlampGeo.unAvacStp_LowerStpMovementRange = CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpMovementRange_L;
    CtrlStp_sHeadlampGeo.unAvacStp_Transmission_Factor   = CtrlStp_CodingData.SwGeoLi.unAvacStp_Transmission_Factor_L;
    CtrlStp_sHeadlampGeo.unAvacStp_UpperStpBlockRange    = CtrlStp_CodingData.SwGeoLi.unAvacStp_UpperStpBlockRange_L;
    CtrlStp_sHeadlampGeo.unAvacStp_UpperStpMovementRange = CtrlStp_CodingData.SwGeoLi.unAvacStp_UpperStpMovementRange_L;

    CtrlStp_sAfsOffset.snAvacStp_AfsLevelling_BDW_LHD   = CtrlStp_CodingData.AfsOffset_Left.snAvacStp_AfsLevelling_BDW_LHD_L;
    CtrlStp_sAfsOffset.snAvacStp_AfsLevelling_BDW_RHD   = CtrlStp_CodingData.AfsOffset_Left.snAvacStp_AfsLevelling_BDW_RHD_L;
    CtrlStp_sAfsOffset.snAvacStp_AfsLevelling_Foggy_LHD = CtrlStp_CodingData.AfsOffset_Left.snAvacStp_AfsLevelling_Foggy_LHD_L;
    CtrlStp_sAfsOffset.snAvacStp_AfsLevelling_Foggy_RHD = CtrlStp_CodingData.AfsOffset_Left.snAvacStp_AfsLevelling_Foggy_RHD_L;
    CtrlStp_sAfsOffset.snAvacStp_AfsLevelling_HB        = CtrlStp_CodingData.AfsOffset_Left.snAvacStp_AfsLevelling_HB_L;
    CtrlStp_sAfsOffset.snAvacStp_AfsLevelling_MW        = CtrlStp_CodingData.AfsOffset_Left.snAvacStp_AfsLevelling_MW_L;
    CtrlStp_sAfsOffset.snAvacStp_AfsLevelling_MW_Boost  = CtrlStp_CodingData.AfsOffset_Left.snAvacStp_AfsLevelling_MW_Boost_L;
    CtrlStp_sAfsOffset.snAvacStp_AfsLevelling_Off       = CtrlStp_CodingData.AfsOffset_Left.snAvacStp_AfsLevelling_Off_L;
    CtrlStp_sAfsOffset.snAvacStp_AfsLevelling_Town_Ped  = CtrlStp_CodingData.AfsOffset_Left.snAvacStp_AfsLevelling_Town_Ped_L;
  }
  else if (eMountingSide == CtrlStp_eMountedRight)
  {
    CtrlStp_sHeadlampGeo.unAvacStp_LowerStpBlockRange    = CtrlStp_CodingData.SwGeoRe.unAvacStp_LowerStpBlockRange_R;
    CtrlStp_sHeadlampGeo.unAvacStp_LowerStpMovementRange = CtrlStp_CodingData.SwGeoRe.unAvacStp_LowerStpMovementRange_R;
    CtrlStp_sHeadlampGeo.unAvacStp_Transmission_Factor   = CtrlStp_CodingData.SwGeoRe.unAvacStp_Transmission_Factor_R;
    CtrlStp_sHeadlampGeo.unAvacStp_UpperStpBlockRange    = CtrlStp_CodingData.SwGeoRe.unAvacStp_UpperStpBlockRange_R;
    CtrlStp_sHeadlampGeo.unAvacStp_UpperStpMovementRange = CtrlStp_CodingData.SwGeoRe.unAvacStp_UpperStpMovementRange_R;

    CtrlStp_sAfsOffset.snAvacStp_AfsLevelling_BDW_LHD   = CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_BDW_LHD_R;
    CtrlStp_sAfsOffset.snAvacStp_AfsLevelling_BDW_RHD   = CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_BDW_RHD_R;
    CtrlStp_sAfsOffset.snAvacStp_AfsLevelling_Foggy_LHD = CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_Foggy_LHD_R;
    CtrlStp_sAfsOffset.snAvacStp_AfsLevelling_Foggy_RHD = CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_Foggy_RHD_R;
    CtrlStp_sAfsOffset.snAvacStp_AfsLevelling_HB        = CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_HB_R;
    CtrlStp_sAfsOffset.snAvacStp_AfsLevelling_MW        = CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_MW_R;
    CtrlStp_sAfsOffset.snAvacStp_AfsLevelling_MW_Boost  = CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_MW_Boost_R;
    CtrlStp_sAfsOffset.snAvacStp_AfsLevelling_Off       = CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_Off_R;
    CtrlStp_sAfsOffset.snAvacStp_AfsLevelling_Town_Ped  = CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_Town_Ped_R;
  }
  else
  {
    // no behavior
  }

  //CtrlStp_CodingData.unLwrTestDlPeriode = 10u * (uint16)ucLwrTestDlPeriode;  // adapt for 10ms sampling time

  //PRQA S 5324 1 // STCAL >7 for a number of similar RTE calls
}


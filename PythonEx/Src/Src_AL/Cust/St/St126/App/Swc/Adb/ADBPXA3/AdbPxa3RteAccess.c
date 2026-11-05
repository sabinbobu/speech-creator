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
/// \file  AdbMxb2Data.c
///
/// \brief  
///
/// \descr  
///
///         Additional information can be found in the design description (Link:
///        
///
/// \author Tanase Alexandru  (F58375C)
///         mailTo: alexandru-anton.tanase[at]marelli.com
//-----------------------------------------------------------------------------

#include <UtilMath.h>
#include <UtilBase.h>
#include <Bsw/Common/Std_Types.h>
//lint -e451 Header file repeatedly included but does not have a standard include guard
#include <Rte.h>
//lint +e451 Header file repeatedly included but does not have a standard include guard
#include "AdbPxa3RteAccess.h"

//=============================================================================
// typedefs
//=============================================================================

//=============================================================================
// defines
//=============================================================================

#define CTRLPXLSCALE               10u
#define PWRNOOBJECT                -1
#define COUNTERLIMITLOW             0u
#define COUNTERLIMITHIGH            4u
#define NODIMMING                   0

//=============================================================================
// Vars
//=============================================================================

//=============================================================================
// Functions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  AdbPxa3_Rte_Read_HeadlampSide()
///
/// \descr  get mounting side
///
/// \param  pSideTL 
///
/// \return Std_ReturnType 
//-----------------------------------------------------------------------------
Std_ReturnType AdbPxa3_Rte_Read_HeadlampSide(tieAdbHeadlampSide* pSideTL)
{
    Std_ReturnType ret;
    teRte_MountingSide eMountingSide = { 0 };

    (void)Rte_Read_IoHwAbUser_GetMountingSide(&eMountingSide);

      switch (eMountingSide)
      {
      case eMountedLeft:
        *pSideTL = LeftHeadlamp;
        break;
      case eMountedRight:
        *pSideTL = RightHeadlamp;
        break;
      case eMountedUndef:
      default:
        *pSideTL = UndefHeadlamp;
        break;
      }
    return ret;
}

//-----------------------------------------------------------------------------
/// \brief  AdbPxa3_Rte_Read_PxaMode()
///
/// \descr  get global enable signal for AdbPxa
///
/// \param  pPxaModeTL 
///
/// \return Std_ReturnType 
//-----------------------------------------------------------------------------
Std_ReturnType AdbPxa3_Rte_Read_PxaMode(tieAdbPxaMode* pPxaModeTL)
{
  Std_ReturnType ret;
  tAdbOut PxaModeMsg;
  tsRte_Ld_ActivationRoutineControl sLd_ActivationRoutineControl;
  boolean boPxaFbit;
  (void)Rte_Read_FctR_PXALightDistr_Fbit(&boPxaFbit);
  (void)Rte_Read_ppsAdb_Out_sVal_0(&PxaModeMsg);
  //read rte port
  (void)Rte_Read_Diag_LdActivationRoutineControl(&sLd_ActivationRoutineControl);
  //check diag request
  if (sLd_ActivationRoutineControl.boRequestStatus != FALSE)
  {
    // Create mask containing all HighBeam light distributions
    const tuRte_TgtLgtFct uHbMask = { .Bits.biHB_HighBeam = 1u,
                                      .Bits.biHB_FlashToPass = 1u,
                                      .Bits.biHB_Boost = 1u,
    };

    *pPxaModeTL = (sLd_ActivationRoutineControl.uTgtLgtFct.ulRaw & uHbMask.ulRaw) != 0U ? PxaHiBeam : PxaOff;
  }
  else
  {
    *pPxaModeTL = (boPxaFbit != FALSE) ? PxaFault : (tieAdbPxaMode)PxaModeMsg.State;
  }

  return ret;
}


//-----------------------------------------------------------------------------
/// \brief  AdbPxa3_Rte_Read_LightDist()
///
/// \descr  get requested light dstribution for AdbPxa
///
/// \param  pLightDistTL 
///
/// \return Std_ReturnType 
//-----------------------------------------------------------------------------
Std_ReturnType AdbPxa3_Rte_Read_LightDist(tieAdbLightDist84Pxl* pLightDistTL)
{
  Std_ReturnType ret;
  teRte_AfsModeSig_sVal  LightDistMsg;
  boolean boPxaFbit = FALSE;
  tsRte_Ld_ActivationRoutineControl sLd_ActivationRoutineControl;

  (void)Rte_Read_FctR_AfsModeSig_sVal(&LightDistMsg);
  (void)Rte_Read_FctR_PXALightDistr_Fbit(&boPxaFbit);
  (void)Rte_Read_Diag_LdActivationRoutineControl(&sLd_ActivationRoutineControl);

  if (boPxaFbit != FALSE)
  {
    LightDistMsg = eLb_to_PXA_AfsOff;
  }
  else if ((sLd_ActivationRoutineControl.boRequestStatus != FALSE) && (sLd_ActivationRoutineControl.uTgtLgtFct.Bits.biHB_Adjustement_Mode != 0U))
  {
    LightDistMsg = eLb_to_PXA_Adjustment;
  }
  else if ((sLd_ActivationRoutineControl.boRequestStatus != FALSE) && ((sLd_ActivationRoutineControl.uTgtLgtFct.Bits.biHB_Reserved2 & 0x01) != 0U))
  {
    LightDistMsg = eLb_to_PXA_TestLightDistribution;
  }
  else
  {
    LightDistMsg = LightDistMsg;
  }

  switch (LightDistMsg)
  {
    case eLb_to_PXA_CountryLight:
    *pLightDistTL = Ld_LowBeamCountry;
    break;
    case eLb_to_PXA_MotorwayLight:
    *pLightDistTL = Ld_MotorwayLight; //TODO define
    break;
    case eLb_to_PXA_TownLight:
    *pLightDistTL = Ld_TownLight;
    break;
    case eLb_to_PXA_BadWeather_Lhd:
    *pLightDistTL = Ld_Badweather_Lhd;
    break;
    case eLb_to_PXA_BadWeather_Rhd:
    *pLightDistTL = Ld_Badweather_Rhd;
    break;
    case eLb_to_PXA_Foggy_Lhd:
    *pLightDistTL = Ld_Foggy_Lhd;
    break;
    case eLb_to_PXA_Foggy_Rhd:
    *pLightDistTL = Ld_Foggy_Rhd;
    break;
    case eLb_to_PXA_LB_Boosted:
    *pLightDistTL = Ld_LowBeamBoost;
    break;
    case eLb_to_PXA_Pedestrian:
    *pLightDistTL = Ld_Pedestrian;
    break;
    case eLb_to_PXA_Adjustment:
    *pLightDistTL = Ld_Adjustment;
    break;
    case eLb_to_PXA_Adjustment_Blink:
    *pLightDistTL = Ld_AdjustmentBlink;
    break;
    case eLb_to_PXA_TestLightDistribution:
    *pLightDistTL = Ld_TestLightDistr;
     break;
    case eLb_to_PXA_AfsOff:
    default:
    *pLightDistTL = Ld_Off;
    break;
  }

  return ret;
}



//-----------------------------------------------------------------------------
/// \brief  AdbPxa3_Rte_Read_DblPos
///
/// \descr  Read DBL position
///
/// \param  pDblPosTL
///
/// \return Std_ReturnType 
//-----------------------------------------------------------------------------
Std_ReturnType AdbPxa3_Rte_Read_DblPos(tAdbAngleTL_deg* pDblPosTL)
{
  Std_ReturnType ret = 0u;
  tsRte_DblOut DblOutMsg;
  sint32 SwvlAngle;
   teRte_MountingSide eMountingSide = { eMountedLeft };
 
  (void)Rte_Read_Dbl_SwivellingOut(&DblOutMsg);
  (void)Rte_Read_IoHwAbUser_GetMountingSide(&eMountingSide);

   // Resolution 0.05 degree
  if (eMountingSide != eMountedUndef)
  {
    SwvlAngle = (sint32)(DblOutMsg.SwivelAngle[eMountingSide]);
    SwvlAngle = max(-640, min(639, SwvlAngle));

    //PRQA S 4394 ++  // Cast is needed for scaling to matlab model scale
    //PRQA S 4544 ++  // Shift is needed for scaling to matlab model scale
    SwvlAngle = ((sint32)((uint32)DblOutMsg.SwivelAngle[eMountingSide] << 9)) / 20;  // convert to model lsb

    *pDblPosTL = (tAdbAngleTL_deg)SwvlAngle;
  }

  return ret;
}


//-----------------------------------------------------------------------------
/// \brief  AdbPxa3_Rte_Read_AdbChannel01
///
/// \descr  Read AdbChannel from RTE
///
/// \param  pChannelTL
///
/// \return Std_ReturnType 
//-----------------------------------------------------------------------------

Std_ReturnType AdbPxa3_Rte_Read_AdbChannel01(tAdbChannelTL* pChannelTL)
{
  Std_ReturnType ret = 0;
  tAdbOut AlhM_tAdbOut;
  sint32 EdgeLeft, EdgeRight, EdgeTop, EdgeBottom;
  tieAdbHeadlampSide AdbPxa3_Side = UndefHeadlamp; // TODO: UndefHeadlamp;

  (void)AdbPxa3_Rte_Read_HeadlampSide(&AdbPxa3_Side);
  (void)Rte_Read_ppsAdb_Out_sVal_0(&AlhM_tAdbOut);

  EdgeLeft = (sint32)AlhM_tAdbOut.Channel[AdbPxa3_Side].EdgeLeft; //[0.1 deg]
  EdgeLeft = max(-320, min(319, EdgeLeft));                                     // limit to model min/max (+/- 32 deg)
  EdgeLeft = ((sint32)((uint32)EdgeLeft << 9)) / 10;                            // convert to model lsb
  
  EdgeRight = (sint32)AlhM_tAdbOut.Channel[AdbPxa3_Side].EdgeRight; //[0.1 deg]
  EdgeRight = max(-320, min(319, EdgeRight));                                    // limit to model min/max
  EdgeRight = ((sint32)((uint32)EdgeRight << 9)) / 10;                           // convert to model lsb

  EdgeTop = ((sint32)AlhM_tAdbOut.Channel[AdbPxa3_Side].EdgeTop); //[0.1 deg]
  EdgeTop = max(-320, min(319, EdgeTop));                                      // limit to model min/max (+/- 32 deg)
  EdgeTop = ((sint32)((uint32)EdgeTop << 9)) / 10;                             // convert to model lsb

  EdgeBottom = ((sint32)AlhM_tAdbOut.Channel[AdbPxa3_Side].EdgeBottom); //[0.1 deg]
  EdgeBottom = max(-320, min(319, EdgeBottom));                                   // limit to model min/max (+/- 32 deg)
  EdgeBottom = ((sint32)((uint32)EdgeBottom << 9)) / 10;                          // convert to model lsb

  //PRQA S 4332 ++  // Cast is needed for scaling to matlab model scale
  pChannelTL->ObjType = (tieAdbObjType)AlhM_tAdbOut.Channel[AdbPxa3_Side].Type;

  // If no object is present, use maximum brightness
  if (AlhM_tAdbOut.Channel[AdbPxa3_Side].PowerFactor >= 0)
  {
    // we use a unit of 0.5%
    pChannelTL->IntensityValue = (tAdbIntensityTL_pct)(AlhM_tAdbOut.Channel[AdbPxa3_Side].PowerFactor) * 10;
  }
  else
  {
    // use maximum value
    pChannelTL->IntensityValue = 0;
  }

  pChannelTL->LuminousIntensity = (tAdbLuminousIntensityTL_cd)0;
  pChannelTL->NormalizedDimmingTimeUp = (tAdbTimeTL_s)AlhM_tAdbOut.Channel[AdbPxa3_Side].NormalizedDimmingTimeUp;
  pChannelTL->NormalizedDimmingTimeDown = (tAdbTimeTL_s)AlhM_tAdbOut.Channel[AdbPxa3_Side].NormalizedDimmingTimeDown;
  pChannelTL->EdgeLeft = (tAdbAngleTL_deg)(EdgeLeft);
  pChannelTL->EdgeRight = (tAdbAngleTL_deg)(EdgeRight);
  pChannelTL->EdgeTop = (tAdbAngleTL_deg)(EdgeTop);
  pChannelTL->EdgeBottom = (tAdbAngleTL_deg)(EdgeBottom);
  pChannelTL->Distance = (tAdbDistanceTL_m)AlhM_tAdbOut.Channel[AdbPxa3_Side].Distance;

  return ret;
}

//-----------------------------------------------------------------------------
/// \brief  AdbPxa3_Rte_Read_AdbChannel02
///
/// \descr  Read AdbChannel from RTE
///
/// \param  pChannelTL
///
/// \return Std_ReturnType 
//-----------------------------------------------------------------------------

Std_ReturnType AdbPxa3_Rte_Read_AdbChannel02(tAdbChannelTL* pChannelTL)
{
    Std_ReturnType ret = 0;
    tAdbOut AlhM_tAdbOut;
    sint32 EdgeLeft, EdgeRight, EdgeTop, EdgeBottom;
    tieAdbHeadlampSide AdbPxa3_Side = UndefHeadlamp; // TODO: UndefHeadlamp;

    (void)AdbPxa3_Rte_Read_HeadlampSide(&AdbPxa3_Side);
    (void)Rte_Read_ppsAdb_Out_sVal_1(&AlhM_tAdbOut);

    EdgeLeft = (sint32)AlhM_tAdbOut.Channel[AdbPxa3_Side].EdgeLeft; //[0.1 deg]
    EdgeLeft = max(-320, min(319, EdgeLeft));                                     // limit to model min/max (+/- 32 deg)
    EdgeLeft = ((sint32)((uint32)EdgeLeft << 9)) / 10;                            // convert to model lsb

    EdgeRight = (sint32)AlhM_tAdbOut.Channel[AdbPxa3_Side].EdgeRight; //[0.1 deg]
    EdgeRight = max(-320, min(319, EdgeRight));                                    // limit to model min/max
    EdgeRight = ((sint32)((uint32)EdgeRight << 9)) / 10;                           // convert to model lsb

    EdgeTop = ((sint32)AlhM_tAdbOut.Channel[AdbPxa3_Side].EdgeTop); //[0.1 deg]
    EdgeTop = max(-320, min(319, EdgeTop));                                      // limit to model min/max (+/- 32 deg)
    EdgeTop = ((sint32)((uint32)EdgeTop << 9)) / 10;                             // convert to model lsb

    EdgeBottom = ((sint32)AlhM_tAdbOut.Channel[AdbPxa3_Side].EdgeBottom); //[0.1 deg]
    EdgeBottom = max(-320, min(319, EdgeBottom));                                   // limit to model min/max (+/- 32 deg)
    EdgeBottom = ((sint32)((uint32)EdgeBottom << 9)) / 10;                          // convert to model lsb

                                                                                    //PRQA S 4332 ++  // Cast is needed for scaling to matlab model scale
    pChannelTL->ObjType = (tieAdbObjType)AlhM_tAdbOut.Channel[AdbPxa3_Side].Type;
    
    // If no object is present, use maximum brightness
    if (AlhM_tAdbOut.Channel[AdbPxa3_Side].PowerFactor >= 0)
    {
      // we use a unit of 0.5%
      pChannelTL->IntensityValue = (tAdbIntensityTL_pct)(AlhM_tAdbOut.Channel[AdbPxa3_Side].PowerFactor) * 100;
    }
    else
    {
      // use maximum value
      pChannelTL->IntensityValue = 0;
    }

    pChannelTL->LuminousIntensity = (tAdbLuminousIntensityTL_cd)0;
    pChannelTL->NormalizedDimmingTimeUp = (tAdbTimeTL_s)AlhM_tAdbOut.Channel[AdbPxa3_Side].NormalizedDimmingTimeUp;
    pChannelTL->NormalizedDimmingTimeDown = (tAdbTimeTL_s)AlhM_tAdbOut.Channel[AdbPxa3_Side].NormalizedDimmingTimeDown;
    pChannelTL->EdgeLeft = (tAdbAngleTL_deg)(EdgeLeft);
    pChannelTL->EdgeRight = (tAdbAngleTL_deg)(EdgeRight);
    pChannelTL->EdgeTop = (tAdbAngleTL_deg)(EdgeTop);
    pChannelTL->EdgeBottom = (tAdbAngleTL_deg)(EdgeBottom);
    pChannelTL->Distance = (tAdbDistanceTL_m)AlhM_tAdbOut.Channel[AdbPxa3_Side].Distance;

  return ret;
}

//-----------------------------------------------------------------------------
/// \brief  AdbPxa3_Rte_Read_AdbChannel03
///
/// \descr  Read AdbChannel from RTE
///
/// \param  pChannelTL
///
/// \return Std_ReturnType 
//-----------------------------------------------------------------------------

Std_ReturnType AdbPxa3_Rte_Read_AdbChannel03(tAdbChannelTL* pChannelTL)
{
    Std_ReturnType ret = 0;
    tAdbOut AlhM_tAdbOut;
    sint32 EdgeLeft, EdgeRight, EdgeTop, EdgeBottom;
    tieAdbHeadlampSide AdbPxa3_Side = UndefHeadlamp; // TODO: UndefHeadlamp;

    (void)AdbPxa3_Rte_Read_HeadlampSide(&AdbPxa3_Side);
    (void)Rte_Read_ppsAdb_Out_sVal_2(&AlhM_tAdbOut);

    EdgeLeft = (sint32)AlhM_tAdbOut.Channel[AdbPxa3_Side].EdgeLeft; //[0.1 deg]
    EdgeLeft = max(-320, min(319, EdgeLeft));                                     // limit to model min/max (+/- 32 deg)
    EdgeLeft = ((sint32)((uint32)EdgeLeft << 9)) / 10;                            // convert to model lsb

    EdgeRight = (sint32)AlhM_tAdbOut.Channel[AdbPxa3_Side].EdgeRight; //[0.1 deg]
    EdgeRight = max(-320, min(319, EdgeRight));                                    // limit to model min/max
    EdgeRight = ((sint32)((uint32)EdgeRight << 9)) / 10;                           // convert to model lsb

    EdgeTop = ((sint32)AlhM_tAdbOut.Channel[AdbPxa3_Side].EdgeTop); //[0.1 deg]
    EdgeTop = max(-320, min(319, EdgeTop));                                      // limit to model min/max (+/- 32 deg)
    EdgeTop = ((sint32)((uint32)EdgeTop << 9)) / 10;                             // convert to model lsb

    EdgeBottom = ((sint32)AlhM_tAdbOut.Channel[AdbPxa3_Side].EdgeBottom); //[0.1 deg]
    EdgeBottom = max(-320, min(319, EdgeBottom));                                   // limit to model min/max (+/- 32 deg)
    EdgeBottom = ((sint32)((uint32)EdgeBottom << 9)) / 10;                          // convert to model lsb

                                                                                    //PRQA S 4332 ++  // Cast is needed for scaling to matlab model scale
    pChannelTL->ObjType = (tieAdbObjType)AlhM_tAdbOut.Channel[AdbPxa3_Side].Type;

    // If no object is present, use maximum brightness
    if (AlhM_tAdbOut.Channel[AdbPxa3_Side].PowerFactor >= 0)
    {
      // we use a unit of 0.5%
      pChannelTL->IntensityValue = (tAdbIntensityTL_pct)(AlhM_tAdbOut.Channel[AdbPxa3_Side].PowerFactor) * 100;
    }
    else
    {
      // use maximum value
      pChannelTL->IntensityValue = 0;
    }

    pChannelTL->LuminousIntensity = (tAdbLuminousIntensityTL_cd)0;
    pChannelTL->NormalizedDimmingTimeUp = (tAdbTimeTL_s)AlhM_tAdbOut.Channel[AdbPxa3_Side].NormalizedDimmingTimeUp;
    pChannelTL->NormalizedDimmingTimeDown = (tAdbTimeTL_s)AlhM_tAdbOut.Channel[AdbPxa3_Side].NormalizedDimmingTimeDown;
    pChannelTL->EdgeLeft = (tAdbAngleTL_deg)(EdgeLeft);
    pChannelTL->EdgeRight = (tAdbAngleTL_deg)(EdgeRight);
    pChannelTL->EdgeTop = (tAdbAngleTL_deg)(EdgeTop);
    pChannelTL->EdgeBottom = (tAdbAngleTL_deg)(EdgeBottom);
    pChannelTL->Distance = (tAdbDistanceTL_m)AlhM_tAdbOut.Channel[AdbPxa3_Side].Distance;

  return ret;
}

//-----------------------------------------------------------------------------
/// \brief  AdbPxa3_Rte_Read_AdbChannel04
///
/// \descr  Read AdbChannel from RTE
///
/// \param  pChannelTL
///
/// \return Std_ReturnType 
//-----------------------------------------------------------------------------

Std_ReturnType AdbPxa3_Rte_Read_AdbChannel04(tAdbChannelTL* pChannelTL)
{
    Std_ReturnType ret = 0;
    tAdbOut AlhM_tAdbOut;
    sint32 EdgeLeft, EdgeRight, EdgeTop, EdgeBottom;
    tieAdbHeadlampSide AdbPxa3_Side = UndefHeadlamp; // TODO: UndefHeadlamp;

    (void)AdbPxa3_Rte_Read_HeadlampSide(&AdbPxa3_Side);
    (void)Rte_Read_ppsAdb_Out_sVal_3(&AlhM_tAdbOut);

    EdgeLeft = (sint32)AlhM_tAdbOut.Channel[AdbPxa3_Side].EdgeLeft; //[0.1 deg]
    EdgeLeft = max(-320, min(319, EdgeLeft));                                     // limit to model min/max (+/- 32 deg)
    EdgeLeft = ((sint32)((uint32)EdgeLeft << 9)) / 10;                            // convert to model lsb

    EdgeRight = (sint32)AlhM_tAdbOut.Channel[AdbPxa3_Side].EdgeRight; //[0.1 deg]
    EdgeRight = max(-320, min(319, EdgeRight));                                    // limit to model min/max
    EdgeRight = ((sint32)((uint32)EdgeRight << 9)) / 10;                           // convert to model lsb

    EdgeTop = ((sint32)AlhM_tAdbOut.Channel[AdbPxa3_Side].EdgeTop); //[0.1 deg]
    EdgeTop = max(-320, min(319, EdgeTop));                                      // limit to model min/max (+/- 32 deg)
    EdgeTop = ((sint32)((uint32)EdgeTop << 9)) / 10;                             // convert to model lsb

    EdgeBottom = ((sint32)AlhM_tAdbOut.Channel[AdbPxa3_Side].EdgeBottom); //[0.1 deg]
    EdgeBottom = max(-320, min(319, EdgeBottom));                                   // limit to model min/max (+/- 32 deg)
    EdgeBottom = ((sint32)((uint32)EdgeBottom << 9)) / 10;                          // convert to model lsb

                                                                                    //PRQA S 4332 ++  // Cast is needed for scaling to matlab model scale
    pChannelTL->ObjType = (tieAdbObjType)AlhM_tAdbOut.Channel[AdbPxa3_Side].Type;

    // If no object is present, use maximum brightness
    if (AlhM_tAdbOut.Channel[AdbPxa3_Side].PowerFactor >= 0)
    {
      // we use a unit of 0.5%
      pChannelTL->IntensityValue = (tAdbIntensityTL_pct)(AlhM_tAdbOut.Channel[AdbPxa3_Side].PowerFactor) * 100;
    }
    else
    {
      // use maximum value
      pChannelTL->IntensityValue = 0;
    }

    pChannelTL->LuminousIntensity = (tAdbLuminousIntensityTL_cd)0;
    pChannelTL->NormalizedDimmingTimeUp = (tAdbTimeTL_s)AlhM_tAdbOut.Channel[AdbPxa3_Side].NormalizedDimmingTimeUp;
    pChannelTL->NormalizedDimmingTimeDown = (tAdbTimeTL_s)AlhM_tAdbOut.Channel[AdbPxa3_Side].NormalizedDimmingTimeDown;
    pChannelTL->EdgeLeft = (tAdbAngleTL_deg)(EdgeLeft);
    pChannelTL->EdgeRight = (tAdbAngleTL_deg)(EdgeRight);
    pChannelTL->EdgeTop = (tAdbAngleTL_deg)(EdgeTop);
    pChannelTL->EdgeBottom = (tAdbAngleTL_deg)(EdgeBottom);
    pChannelTL->Distance = (tAdbDistanceTL_m)AlhM_tAdbOut.Channel[AdbPxa3_Side].Distance;

  return ret;
}

//-----------------------------------------------------------------------------
/// \brief  AdbPxa3_Rte_Read_AdbChannel05
///
/// \descr  Read AdbChannel from RTE
///
/// \param  pChannelTL
///
/// \return Std_ReturnType 
//-----------------------------------------------------------------------------

Std_ReturnType AdbPxa3_Rte_Read_AdbChannel05(tAdbChannelTL* pChannelTL)
{
  Std_ReturnType ret = 0;
  tAdbOut AlhM_tAdbOut;
  sint32 EdgeLeft, EdgeRight, EdgeTop, EdgeBottom;
  tieAdbHeadlampSide AdbPxa3_Side = UndefHeadlamp; // TODO: UndefHeadlamp;

  (void)AdbPxa3_Rte_Read_HeadlampSide(&AdbPxa3_Side);
  (void)Rte_Read_ppsAdb_Out_sVal_4(&AlhM_tAdbOut);

  EdgeLeft = (sint32)AlhM_tAdbOut.Channel[AdbPxa3_Side].EdgeLeft; //[0.1 deg]
  EdgeLeft = max(-320, min(319, EdgeLeft));                                     // limit to model min/max (+/- 32 deg)
  EdgeLeft = ((sint32)((uint32)EdgeLeft << 9)) / 10;                            // convert to model lsb

  EdgeRight = (sint32)AlhM_tAdbOut.Channel[AdbPxa3_Side].EdgeRight; //[0.1 deg]
  EdgeRight = max(-320, min(319, EdgeRight));                                    // limit to model min/max
  EdgeRight = ((sint32)((uint32)EdgeRight << 9)) / 10;                           // convert to model lsb

  EdgeTop = ((sint32)AlhM_tAdbOut.Channel[AdbPxa3_Side].EdgeTop); //[0.1 deg]
  EdgeTop = max(-320, min(319, EdgeTop));                                      // limit to model min/max (+/- 32 deg)
  EdgeTop = ((sint32)((uint32)EdgeTop << 9)) / 10;                             // convert to model lsb

  EdgeBottom = ((sint32)AlhM_tAdbOut.Channel[AdbPxa3_Side].EdgeBottom); //[0.1 deg]
  EdgeBottom = max(-320, min(319, EdgeBottom));                                   // limit to model min/max (+/- 32 deg)
  EdgeBottom = ((sint32)((uint32)EdgeBottom << 9)) / 10;                          // convert to model lsb

                                                                                  //PRQA S 4332 ++  // Cast is needed for scaling to matlab model scale
  pChannelTL->ObjType = (tieAdbObjType)AlhM_tAdbOut.Channel[AdbPxa3_Side].Type;

  // If no object is present, use maximum brightness
  if (AlhM_tAdbOut.Channel[AdbPxa3_Side].PowerFactor >= 0)
  {
    // we use a unit of 0.5%
    pChannelTL->IntensityValue = (tAdbIntensityTL_pct)(AlhM_tAdbOut.Channel[AdbPxa3_Side].PowerFactor) *  2;
  }
  else
  {
    // use maximum value
    pChannelTL->IntensityValue = 0;
  }

  pChannelTL->LuminousIntensity = (tAdbLuminousIntensityTL_cd)0;
  pChannelTL->NormalizedDimmingTimeUp = (tAdbTimeTL_s)AlhM_tAdbOut.Channel[AdbPxa3_Side].NormalizedDimmingTimeUp;
  pChannelTL->NormalizedDimmingTimeDown = (tAdbTimeTL_s)AlhM_tAdbOut.Channel[AdbPxa3_Side].NormalizedDimmingTimeDown;
  pChannelTL->EdgeLeft = (tAdbAngleTL_deg)(EdgeLeft);
  pChannelTL->EdgeRight = (tAdbAngleTL_deg)(EdgeRight);
  pChannelTL->EdgeTop = (tAdbAngleTL_deg)(EdgeTop);
  pChannelTL->EdgeBottom = (tAdbAngleTL_deg)(EdgeBottom);
  pChannelTL->Distance = (tAdbDistanceTL_m)AlhM_tAdbOut.Channel[AdbPxa3_Side].Distance;

  return ret;
}

//-----------------------------------------------------------------------------
/// \brief  AdbPxa3_Rte_Read_CodM_Calibration_Type()
///
/// \descr  get EU or UK versions of light distributions
///
/// \param  boolean 
///
/// \return Std_ReturnType 
//-----------------------------------------------------------------------------
//Std_ReturnType AdbPxa3_Rte_Read_CodM_Calibration_Type(uint8* Calibration_Type)
//{
//  Std_ReturnType ret;
//  teRte_CodM_eHeadLampType eCalibrationType;
//  //read port
//  ret = Rte_Read_CodM_Calibration_Type_Port(&eCalibrationType);
//  switch (eCalibrationType)
//  {
//  case eCal_High_EU:
//    *Calibration_Type = 0u;
//    break;
//  case eCal_High_UK:
//    *Calibration_Type = 1u;
//    break;
//  default:
//    *Calibration_Type = 0u;
//    break;
//  }
//  return ret;
//}

//-----------------------------------------------------------------------------
/// \brief  AdbPxa3_Rte_Read_AfsLgtFctMgr_Animation_IntensityMatrix()
///
/// \descr  Animation welcome/goodbye light distributions
///
/// \param   
///
/// \return Std_ReturnType 
//-----------------------------------------------------------------------------
//Std_ReturnType AdbPxa3_Rte_Read_AfsLgtFctMgr_Animation_IntensityMatrix(void)
//{
//  Std_ReturnType ret;
//  tsRte_AnimationIntensityMatrix AnimationIntensityValues;
//  //read port
//  ret = Rte_Read_AfsLgtFctMgr_Animation_IntensityMatrix_Port(&AnimationIntensityValues);
//
//  for (uint8 ucIndex = 0u; ucIndex < STR_COL_COUNT; ucIndex++)
//  {
//    //PRQA S 4461 ++  // Cast is needed for scaling to matlab model scale
//    paucAnimationDistribution[0][ucIndex] = (uint16)AnimationIntensityValues.AnimationIntensityMatrix.Top[ucIndex] / CTRLPXLSCALE;
//    paucAnimationDistribution[1][ucIndex] = (uint16)AnimationIntensityValues.AnimationIntensityMatrix.Mid[ucIndex] / CTRLPXLSCALE;
//    paucAnimationDistribution[2][ucIndex] = (uint16)AnimationIntensityValues.AnimationIntensityMatrix.Bottom[ucIndex] / CTRLPXLSCALE;
//  }
//
//  return ret;
//}

//-----------------------------------------------------------------------------
/// \brief  AdbPxa3_Rte_Write_ActualLedIntensities
///
/// \descr  Write Led Intensities to RTE
///
/// \param  ActLedIntensitiesTL
///
/// \return Std_ReturnType 
//-----------------------------------------------------------------------------
Std_ReturnType AdbPxa3_Rte_Write_ActualLedIntensities(tAdbestingtAdbIntensityTL_pct ActLedIntensitiesTL[3][30])
{
  Std_ReturnType ret;
  tsRte_PxaIntensityMatrix IntensityMsg;
  sint16 idx;

  // write LedIntensities to RTE
  for (idx = 0; idx < 30; idx++)
  {
    IntensityMsg.Top[idx]
      = (ActLedIntensitiesTL[0][idx] == 999) ? 1000 : ActLedIntensitiesTL[0][idx];

    IntensityMsg.Mid[idx]
      = (ActLedIntensitiesTL[1][idx] == 999) ? 1000 : ActLedIntensitiesTL[1][idx];

    IntensityMsg.Bottom[idx]
      = (ActLedIntensitiesTL[2][idx] == 999) ? 1000 : ActLedIntensitiesTL[2][idx];
  }

  ret = Rte_Write_AdbPxa_IntensityMatrix(&IntensityMsg);

  return ret;
}

//-----------------------------------------------------------------------------
/// \brief AdbPxa3_Rte_Read_MatrixErrorState 
///
/// \descr Reads error status for whole matrix  
///
/// \param void 
///
/// \return boolean  
//-----------------------------------------------------------------------------
//boolean AdbPxa3_Rte_Read_MatrixErrorState(void)
//{
//  // matrix error status 
//  boolean boMatrixStatus = FALSE;
//
//  (void)Rte_Read_CtrlPxl_MatrixState_Port(&boMatrixStatus);
//
//  return boMatrixStatus;
//}
//-----------------------------------------------------------------------------
/// \brief AdbPxa3_Rte_Read_SignalAvailability 
///
/// \descr Reads availability of HB control signal
///
/// \param void 
///
/// \return boolean  
//-----------------------------------------------------------------------------
//boolean AdbPxa3_Rte_Read_SignalAvailability(void)
//{
//  boolean boSignalAvailability = FALSE;
//
//  (void)Rte_Read_AfsHb_SignalAvailability_Port(&boSignalAvailability);
//
//  return boSignalAvailability;
//}

//-----------------------------------------------------------------------------
/// \brief AdbPxa3_Rte_Write_SigPrep_MatrixErrStatus 
///
/// \descr writes HB err state 
///
/// \param tieAdbPxaMode_HbState eHbState 
///
/// \return void
//-----------------------------------------------------------------------------
//void AdbPxa3_Rte_Write_SigPrep_HbErrStatus(tieAdbPxaMode_HbState eHbState)
//{
//  teRte_DrvledDiag eHbErrState = Indeterminate;
//
//  // map parameter to output signal
//  switch (eHbState)
//  {
//  case eIndeterminate:
//    eHbErrState = Indeterminate;
//    break;
//
//  case eNoFault:
//    eHbErrState = NoFault;
//    break;
//
//  case eFault:
//    eHbErrState = Fault;
//    break;
//
//  case eNotUsed:
//    eHbErrState = NotUsed;
//    break;
//
//  default:
//    break;
//  }
//
//  // write signal to sigprep
//  (void)Rte_Write_AdbPxa3_HbErrState_Port(&eHbErrState);
//
//
//}

//-----------------------------------------------------------------------------
/// \brief AdbPxa3_Rte_Write_SigPrep_HbStatus 
///
/// \descr writes Hb status to sigprep tx signal
///
/// \param boolean boStatus 
///
/// \return void
//-----------------------------------------------------------------------------
//void AdbPxa3_Rte_Write_SigPrep_HbStatus(boolean boStatus)
//{
//  teRte_DrvledEtat eHbStatus = OFF;
//
//  // check HB status 
//  if (boStatus != FALSE)
//  {
//    eHbStatus = ON;
//  }
//  else
//  {
//    eHbStatus = OFF;
//  }
//  // send output signal 
//  (void)Rte_Write_AdbPxa3_HbStatus_Port(&eHbStatus);
//}

//-----------------------------------------------------------------------------
/// \brief  AdbPxa3_Rte_Read_FTPStatus
///
/// \descr  get FlashToPass status
///
/// \param  boFTPStatus
///
/// \return void
//-----------------------------------------------------------------------------
void AdbPxa3_Rte_Read_FTPStatus(boolean* boFTPStatus)
{
  boolean boF2PStatus = FALSE;
  tsRte_SysMonLgtFctsReq  dataLgtFctsReq = { 0 };

  (void)Rte_Read_SysMon_StdLgtFcts_Req(&dataLgtFctsReq);

  if (ReqLighted_On == dataLgtFctsReq.eHbFlash_Request)
  {
      boF2PStatus = TRUE;
  }

  *boFTPStatus = boF2PStatus;
}


//-----------------------------------------------------------------------------
/// \brief  AdbPxa3_Rte_Read_MXBStatus
///
/// \descr  Reads errors and signal quality for matrix and sets otgoing signals
///
/// \param  boolean HBBstatus, boolean CurtainStatus
///
/// \return void 
//-----------------------------------------------------------------------------
void AdbPxa3_Rte_Read_MXBStatus(boolean* HBBstatus, boolean* CurtainStatus)
{
    tAdbStatus AdbStatusOut;
    tsRte_Ld_ActivationRoutineControl sLd_ActivationRoutineControl;

    (void)Rte_Read_Diag_LdActivationRoutineControl(&sLd_ActivationRoutineControl);
    if ((sLd_ActivationRoutineControl.boRequestStatus != FALSE) && (sLd_ActivationRoutineControl.uTgtLgtFct.Bits.biHB_Boost != 0U))
    {
      *CurtainStatus = FALSE;
      *HBBstatus = TRUE;
    }
    else
    {
      // write status to RTE
      (void)Rte_Read_Adb_StatusOut(&AdbStatusOut);

      *CurtainStatus = AdbStatusOut.CurtainEffectStatus;
      *HBBstatus = AdbStatusOut.HBBStatus;
    }

}


//-----------------------------------------------------------------------------
/// \brief  AdbPxa3_Rte_Read_CameraAvailability
///
/// \descr  get StatusPercep - camera availability status
///
/// \param  boStatusPercep
///
/// \return void
//-----------------------------------------------------------------------------
//void AdbPxa3_Rte_Read_CameraAvailability(boolean* boStatusPercep)
//{
//  tsRte_CamObj sCamObj;
//
//  //CamObj
//  (void)Rte_Read_SigPrep_CamObj_Port(&sCamObj);
//  //check signal qty and value
//  *boStatusPercep = ((sCamObj.eSigQty == SIG_VALID) && (sCamObj.eStatusPercep == eStsPrc_Avalaible)) ? TRUE : FALSE;
//
//}

//-----------------------------------------------------------------------------
/// \brief  AdbPxa3_Rte_Read_CmdMxbStatus
///
/// \descr  Read CMD_MXB value from SigPrep
///
/// \param  boCmdMxbStatus
///
/// \return void
//-----------------------------------------------------------------------------
//void AdbPxa3_Rte_Read_CmdMxbStatus(boolean* boCmdMxbStatus)
//{
//  tsRte_Gfhb_status GFHB_status;
//
//  // Read signal from Rte
//  (void)Rte_Read_SigPrep_GlareFreeHighBeam_Status_Port(&GFHB_status);
//  
//  //check signal qty
//  if (GFHB_status.eSigQty == SIG_VALID)
//  {
//    *boCmdMxbStatus = GFHB_status.boGfhbSts;
//  }
//  else
//  {
//    *boCmdMxbStatus = FALSE;
//  }
//}


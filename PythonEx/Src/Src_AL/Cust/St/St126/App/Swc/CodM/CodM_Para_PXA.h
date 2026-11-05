#ifndef __CODM_PARA_PXA_H__
#define __CODM_PARA_PXA_H__


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
///  \file   CodM_Para_PXA.h
///
///  \brief  Content of datagroup "PXA"
///
///  \descr  Source: PS60_R2_Sample.xlsm. 
///          Version TBD 
///          For further details see coding parameter
///
///  \author Cretu Vlad (F78845C)
///          mailTo:vladut-ioan.cretu[at]marelli.com
///
///  \date   04.03.2019, 16:49:53
//-----------------------------------------------------------------------------
//=============================================================================
// includes
//=============================================================================


//=============================================================================
// Definitions
//=============================================================================
#define CODM_PARA_PXA_STR_ROW_COUNT                   3u
#define CODM_PARA_PXA_COL_COUNT                       30u

#define CODM_PARA_PXA_SIGNED_ROW_COUNT                30u
#define CODM_PARA_PXA_SIGNED_COL_COUNT                2u

#define CODM_PARA_PXA_RESERVED_SIZE_PXA               1u
//=============================================================================
// Types
//=============================================================================

typedef struct
{
  // Light intesity for Led from row1 to row3, column1 to column 30
  uint8 anLIGHT_INTENS_LFT[CODM_PARA_PXA_STR_ROW_COUNT][CODM_PARA_PXA_COL_COUNT];
  // row 0 - top, row 1 -middle, row 2 - bottom
  uint8 anLIGHT_INTENS_RGT[CODM_PARA_PXA_STR_ROW_COUNT][CODM_PARA_PXA_COL_COUNT];
}
tNvmPara_PXA_LghtDstrbtn;


typedef struct
{
  // Light intesity for Led from row1 to row30 (Left Border)
  sint16 alLIGHT_INTENS_LFT[CODM_PARA_PXA_SIGNED_ROW_COUNT][CODM_PARA_PXA_SIGNED_COL_COUNT];
  // Light intesity for led from row1 to row30 (Right border)
  sint16 alLIGHT_INTENS_RGT[CODM_PARA_PXA_SIGNED_ROW_COUNT][CODM_PARA_PXA_SIGNED_COL_COUNT]; 

}
tNvmPara_PXA_Border_LghtDstrbtn;

typedef struct
{
  // Activation speed of curtain effect in [deg/sec]
  uint8 ucACTIVATION_SPEED;
  // Deactivation speed of curtain effect in [deg/sec]
  uint8 ucDEACTIVATION_SPEED;
  // Dimming Time ON for curtain effect in [10ms]
  sint16 snDIMMING_TIME_ON;
  // Dimming Time OFF for curtain effect in [10ms]
  sint16 snDIMMING_TIME_OFF;
  // Central Area for curtain effect in [deg]
  sint16 snCENTRAL_AREA;
  // Index of Left Center Pixel (one based indexing)
  uint8 ucLEFT_HL_CENTER_PIXEL_LEFT; 
  // Index of Right Center Pixel (one based indexing)
  uint8 ucLEFT_HL_CENTER_PIXEL_RIGHT; 
  // Index of Left Center Pixel (one based indexing)
  uint8 ucRIGHT_HL_CENTER_PIXEL_LEFT; 
  // Index of Right Center Pixel (one based indexing)
  uint8 ucRIGHT_HL_CENTER_PIXEL_RIGHT; 
  // Offset for left side central area [deg]
  sint16 snCENTRAL_AREA_LEFTSIDE_OFFSET;
  // Offset for right side central area [deg]
  sint16 snCENTRAL_AREA_RIGHTSIDE_OFFSET;
  // Delay for the Activation of Mid Row w.r.t. Bottom Row
  uint8 ucACTIVATION_MID_ROW_DELAY;
  // Delay for the Activation of Top Row w.r.t. Mid Row
  uint8 ucACTIVATION_TOP_ROW_DELAY;
  // Delay for the Deactivation of Mid Row w.r.t. Top Row
  uint8 ucDEACTIVATION_MID_ROW_DELAY;
  // Delay for the Deactivation of Bottom Row w.r.t. Mid Row
  uint8 ucDEACTIVATION_BOTTOM_ROW_DELAY;
  // Swivelling angle speed limit
  sint16 snSWIVELLING_ANGLE_SPEED_LIMIT; 

}
tNvmPara_PXA_CurtainEffectParams;

typedef struct
{
  // Curtain Sequence from Pixel 1 to Pixel 30
  uint8 ucCurtainAnimSeq[CODM_PARA_PXA_COL_COUNT];
}
tNvmPara_PXA_CurtainEffectSequence;

typedef struct
{
  // Flag for HB Dimming: 0 - not dimmed ; 1 - dimmed
  uint8 ucIS_HB_DIMMED;

  // Minimum intensity for cases when dimming results between 0 and 1 percent [%]
  uint8 ucPIXEL_MIN_INTENSITY;

  // Town
  // Dimming Time for Town to Country transition in [100ms]
  uint8 ucTOWN_TO_COUNTRY;
  // Dimming Time for Town to AdverseW transition in [100ms]
  uint8 ucTOWN_TO_ADVERSEW;

  // Country
  // Dimming Time for Country to Town transition in [100ms]
  uint8 ucCOUNTRY_TO_TOWN;
  // Dimming Time for Country to AdverseW transition in [100ms]
  uint8 ucCOUNTRY_TO_ADVERSEW;

  // AdverseW
  // Dimming Time for AdverseW to Town transition in [100ms]
  uint8 ucADVERSEW_TO_TOWN;
  // Dimming Time for AdverseW to Country transition in [100ms]
  uint8 ucADVERSEW_TO_COUNTRY;

  // ManualHB
  // Dimming Time for ManualHB ON in [10ms]
  uint8 ucMANUALHB_ON;
  // Dimming Time for ManualHB OFF in [10ms]
  uint8 ucMANUALHB_OFF;

  // FlashToPass
  // Dimming Time for FlashToPass ON in [10ms]
  uint8 ucFLASHTOPASS_ON;
  // Dimming Time for FlashToPass OFF in [10ms]
  uint8 ucFLASHTOPASS_OFF;
}
tsNvmPara_PXA_DimmingTimes;

typedef struct
{
  sint16 reserviert1[CODM_PARA_PXA_RESERVED_SIZE_PXA];
}
tNvmPara_PXA_Reserved;

typedef struct
{
  tNvmPara_PXA_LghtDstrbtn            BadWeather_LHD;
  tNvmPara_PXA_LghtDstrbtn            BadWeather_RHD;
  tNvmPara_PXA_LghtDstrbtn            Foggy_LHD;
  tNvmPara_PXA_LghtDstrbtn            Foggy_RHD;
  tNvmPara_PXA_LghtDstrbtn            CountryLight;
  tNvmPara_PXA_LghtDstrbtn            LowBeamBoost;
  tNvmPara_PXA_LghtDstrbtn            ManualHighBeam;
  tNvmPara_PXA_LghtDstrbtn            LowBeamMotorway;
  tNvmPara_PXA_LghtDstrbtn            HighBeamBoost;
  tNvmPara_PXA_LghtDstrbtn            TownLight;
  tNvmPara_PXA_LghtDstrbtn            Adjustement_LgtDstrbn;
  tNvmPara_PXA_LghtDstrbtn            Adjustement_LgtDstrBlinkPhasebn;
  tNvmPara_PXA_LghtDstrbtn            Pedestrian;
  tNvmPara_PXA_LghtDstrbtn            AlignmentCamera;
  tNvmPara_PXA_LghtDstrbtn            TestDistribution;
  tNvmPara_PXA_Border_LghtDstrbtn     PixelBorders;
  tNvmPara_PXA_CurtainEffectParams    CurtainParameters;
  tNvmPara_PXA_CurtainEffectSequence  ActivationIn2Out;
  tNvmPara_PXA_CurtainEffectSequence  ActivationOut2In;
  tNvmPara_PXA_CurtainEffectSequence  DeactivationIn2Out;
  tNvmPara_PXA_CurtainEffectSequence  DeactivationOut2In;
  tsNvmPara_PXA_DimmingTimes           DimmingTimes;
  tNvmPara_PXA_Reserved               Reserved;

} tNvmPara_PXABlock;

#endif // __CODM_PARA_PXA_H__

// EOF

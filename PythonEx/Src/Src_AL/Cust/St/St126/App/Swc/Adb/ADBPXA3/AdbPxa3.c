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
/// \file  AdbPxa3.c
///
/// \brief  Transmits to the Pixel the intensity it has to be lit up
///
/// \descr  Depending on the inputs it gets from Mxb or Light Distribution
///         the module transmits to the matrix pixel which one should be lit
///         up or not and at what intensity
///
///         Additional information can be found in the design description (Link:
///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
///
/// \author Alf Traulsen (taf2rt)
///         mailTo:alf.traulsen[at]al-lighting.com
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================

#include <Bsw/Common/Std_Types.h>
#include "AdbPxa3Data.h"
#include "AdbPxa3RteAccess.h"
#include "AdbPxa3.h"
#include "AdbPxa3Types.h"
#include "AdbPxa3Ifc.h"
#include "AdbPxa3Main.h"
#include "Rte.h"

//=============================================================================
// Prototypes
//=============================================================================

void AdbPxa3_Write_Status(tieAdbPxaMode ePxaMode);
void AdbPxa3_Write_State(void);
void AdbPxa3_Read_MXBStatus(boolean HBBstatus, boolean CurtainStatus);

tieAdbHeadlampSide AdbPxa3_Side = UndefHeadlamp;

//tNvmPara_PXA_LghtDstrbtn LightDistributionValues;
//taucLigthDistrubution *paucAnimationDistribution;

//=============================================================================
// Constants
//=============================================================================

//const uint8 var[3][30] = Cod_AdbPxa3_parPixelIntLayout_Adjust_LUT;

//=============================================================================
// Defines
//=============================================================================
//#define SLOTS_NR 4u

//=============================================================================
// Functions
//=============================================================================


//-----------------------------------------------------------------------------
/// \brief  AppAdbPxa3_Init
///
/// \descr  initialize Adb
///
/// \param  - 
///
/// \return void 
//-----------------------------------------------------------------------------
void AdbPxa3_Init(void)
{
  (void)AdbPxa3_Rte_Read_HeadlampSide(&AdbPxa3_Side);

 // if (AdbPxa3_Side == RightHeadlamp)
 // {
 //   paucAnimationDistribution = LightDistributionValues.anLIGHT_INTENS_RGT;
 // }
 // else
  //{
  //  paucAnimationDistribution = LightDistributionValues.anLIGHT_INTENS_LFT;
  //}

  return;
}

//-----------------------------------------------------------------------------
/// \brief  AdbPxa3_Write_Status
///
/// \descr  Reads status for matrix and sets otgoing signals
///
/// \param  tieAdbPxaMode ePxaMode
///
/// \return void 
//-----------------------------------------------------------------------------
//void AdbPxa3_Write_Status(tieAdbPxaMode ePxaMode)
//{
//  boolean boMatrixErrStatus = FALSE;
//  boolean boHbStatus = FALSE;
//
//
//  // read matrix error state
//  boMatrixErrStatus = AdbPxa3_Rte_Read_MatrixErrorState();
//  // read signal status
//
//  // HB is on only if pxamode is HiBeam and there are no matrix errors
//  if (boMatrixErrStatus != TRUE)
//  {
//    // check LgtFctMgr_Cfg modes which are associated with high beam distribution
//    boHbStatus = ((ePxaMode == PxaHiBeam) || (ePxaMode == PxaActive)) ? TRUE : FALSE;
//  }
//  else
//  {
//    // HB is off if there are errors
//    boHbStatus = FALSE;
//  }
//
//  // Write outgoing signals to sigprep
//  AdbPxa3_Rte_Write_SigPrep_HbStatus(boHbStatus);
//
//}

//-----------------------------------------------------------------------------
/// \brief  AdbPxa3_Write_State
///
/// \descr  Reads errors and signal quality for matrix and sets otgoing signals
///
/// \param  tieAdbPxaMode ePxaMode
///
/// \return void 
//-----------------------------------------------------------------------------
//void AdbPxa3_Write_State(void)
//{
//  boolean boSignalAvailability = FALSE;
//  tieAdbPxaMode_HbState eHbState = eIndeterminate;
//  boolean boMatrixErrStatus = FALSE;
//
//  boSignalAvailability = AdbPxa3_Rte_Read_SignalAvailability();
//  // read matrix error state
//  boMatrixErrStatus = AdbPxa3_Rte_Read_MatrixErrorState();
//
//
//  if (boSignalAvailability != TRUE)
//  {
//    eHbState = eIndeterminate;
//  }
//  else if (boMatrixErrStatus != TRUE)
//  {
//    // mark state with no fault 
//    eHbState = eNoFault;
//  }
//  else
//  {
//    // HB is off if there are errors
//    eHbState = eFault;
//  }
//
//  // Write outgoing signals to sigprep
//  AdbPxa3_Rte_Write_SigPrep_HbErrStatus(eHbState);
//
//}

// ---------------------------------------------------------------------------
///
///  \func     rpAdbPxa3_Cycle0
///
///  \brief    cyclic function called every 5ms
///
///  \param    none
///
///  \return   none
///
// ---------------------------------------------------------------------------
void AdbPxa3_Cycle0(void)
{

  static uint8                  AdbPxa3_Slot;
  static boolean                AdbPxa3_boCycleComplete = TRUE; // start with a completed cycle
  static tieAdbPxaMode          AdbPxa3_PxaMode = PxaOff;
  static tAdbAngleTL_deg        AdbPxa3_DblPos = 0;
  static tieAdbLightDist84Pxl   AdbPxa3_LightDist = Ld_Off;
  static boolean                AdbPxa3_boHBBStatus = FALSE; //HBB
  static boolean                AdbPxa3_boFTPStatus = FALSE;
  static boolean                AdbPxa3_boCurtainStatus = FALSE; //Curtain

  // --------------------------------------------------------------------------
  // Step 0: check for valid coding data
  // --------------------------------------------------------------------------
  if (AdbPxa3Data_GetCodingValid() == FALSE)
  {
    return;
  }

  // --------------------------------------------------------------------------
  //Step 1 : set input signals for PXA3 (only if last cycle was completed => this is a new cyle)
  // --------------------------------------------------------------------------
  if (AdbPxa3_boCycleComplete != FALSE)
  {
    // --------------------------------------------------------------------------
    (void)AdbPxa3_Rte_Read_MXBStatus(&AdbPxa3_boHBBStatus, &AdbPxa3_boCurtainStatus);
    // --------------------------------------------------------------------------
    (void)AdbPxa3_Rte_Read_PxaMode(&AdbPxa3_PxaMode);
    // --------------------------------------------------------------------------
    (void)AdbPxa3_Rte_Read_LightDist(&AdbPxa3_LightDist);
    // --------------------------------------------------------------------------
    (void)AdbPxa3_Rte_Read_DblPos(&AdbPxa3_DblPos);
    // --------------------------------------------------------------------------
    (void)AdbPxa3_Rte_Read_AdbChannel01(Get_AdbPxa3_AdbChannel1_Addr());
    // --------------------------------------------------------------------------
    (void)AdbPxa3_Rte_Read_AdbChannel02(Get_AdbPxa3_AdbChannel2_Addr());
    // --------------------------------------------------------------------------
    (void)AdbPxa3_Rte_Read_AdbChannel03(Get_AdbPxa3_AdbChannel3_Addr());
    // --------------------------------------------------------------------------
    (void)AdbPxa3_Rte_Read_AdbChannel04(Get_AdbPxa3_AdbChannel4_Addr());
    // --------------------------------------------------------------------------
    (void)AdbPxa3_Rte_Read_AdbChannel05(Get_AdbPxa3_AdbChannel5_Addr());
    // --------------------------------------------------------------------------
    (void)AdbPxa3_Rte_Read_FTPStatus(&AdbPxa3_boFTPStatus);

  }

  // --------------------------------------------------------------------------
  //Step 2 : call the AdbPxa3Main function ( cycle time: 4 * 5ms = 20ms ).
  // --------------------------------------------------------------------------
  AdbPxa3_Slot = AdbPxa3Main(AdbPxa3_Side, AdbPxa3_PxaMode, AdbPxa3_DblPos, AdbPxa3_LightDist, AdbPxa3_boHBBStatus, AdbPxa3_boFTPStatus, AdbPxa3_boCurtainStatus);
  // --------------------------------------------------------------------------
  //Step 3 : get results and write to RTE (only if cycle is completed)
  // --------------------------------------------------------------------------

  (void)AdbPxa3_Rte_Write_ActualLedIntensities(Get_AdbPxa3_PixelIntensity_Addr());
  // handles outgoing status messages
  //AdbPxa3_Write_Status(AdbPxa3_PxaMode);
  //AdbPxa3_Write_State();
  //PRQA S 5324, 5330 1 // Program architecture and code readability.
}

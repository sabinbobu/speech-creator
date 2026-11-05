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
/// \file  AdbMxb4.c
///
/// \brief  
///
/// \descr  
///
///         Additional information can be found in the design description (Link:
///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
///
/// \author Tony Vornicu  (F63906B)
///         mailTo:tony.vornicu@al-lighting.com
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================

#include <Bsw/Common/Std_Types.h>

#include "AdbMxb4Data.h"
#include "AdbMxb4.h"
#include "AdbMxb3Ifc.h"
#include "AdbMxb3Main.h"

//=============================================================================
// Functions
//=============================================================================


//-----------------------------------------------------------------------------
/// \brief  AdbMxb1_Init
///
/// \descr  initialize Adb
///
/// \param  - 
///
/// \return void 
//-----------------------------------------------------------------------------
void AdbMxb4_Init(void)
{
  return; // nothing to do
}


// ---------------------------------------------------------------------------
///
///  \func     AdbMxb4_Cycle0
///
///  \brief    cyclic function called every 20ms
///
///  \param    none
///
///  \return   none
///
// ---------------------------------------------------------------------------
void AdbMxb4_Cycle0(void)
{
  tieAdbMode nAdbMode;
  boolean CurtainEffectStatus;
  boolean HBBStatus;
  boolean boGfhbDiag = FALSE;

  // --------------------------------------------------------------------------
  // check for valid coding data
  // --------------------------------------------------------------------------
  if (AdbMxb4Data_GetCodingValid() == FALSE)
  {
    return;
  }

  // --------------------------------------------------------------------------
  // read inputs
  // --------------------------------------------------------------------------

  // --------------------------------------------------------------------------
  // CamObject 1
  AdbMxb4Data_ConvertCamObj(Get_Sa2_CamObject1(), ADBMXB4DATA_CAMOBJ_1);
  // --------------------------------------------------------------------------
  // CamObject 2
  AdbMxb4Data_ConvertCamObj(Get_Sa2_CamObject2(), ADBMXB4DATA_CAMOBJ_2);
  // --------------------------------------------------------------------------
  // CamObject 3
  AdbMxb4Data_ConvertCamObj(Get_Sa2_CamObject3(), ADBMXB4DATA_CAMOBJ_3);
  // --------------------------------------------------------------------------
  // CamObject 4
  AdbMxb4Data_ConvertCamObj(Get_Sa2_CamObject4(), ADBMXB4DATA_CAMOBJ_4);
  // --------------------------------------------------------------------------
  // CamObject 5
  AdbMxb4Data_ConvertCamObj(Get_Sa2_CamObject5(), ADBMXB4DATA_CAMOBJ_5);

  //This Objects are only for Sign's
  // --------------------------------------------------------------------------
  // CamObject 6
  AdbMxb4Data_ConvertCamObj_Percieve(Get_Sa2_CamObject6(), ADBMXB4DATA_CAMOBJ_PERCEIVE_1);
  // --------------------------------------------------------------------------
  // CamObject 7
  AdbMxb4Data_ConvertCamObj_Percieve(Get_Sa2_CamObject7(), ADBMXB4DATA_CAMOBJ_PERCEIVE_2);
  // --------------------------------------------------------------------------
  // CamObject 8
  AdbMxb4Data_ConvertCamObj_Percieve(Get_Sa2_CamObject8(), ADBMXB4DATA_CAMOBJ_PERCEIVE_3);


  // --------------------------------------------------------------------------
  // call algorithm
  // --------------------------------------------------------------------------
  nAdbMode = AdbMxb3Main(AdbMxb4Data_GetTrafficStyle(),
                         AdbMxb4Data_GetSpeed(),
                         AdbMxb4Data_GetMotorwayDetection(),
                         AdbMxb4Data_GetHBActivation(),
                         AdbMxb4Data_GetHBFlashActivation(),
                         AdbMxb4Data_GetGFHB_CMD(),
                         AdbMxb4Data_GetCurvatureAngle(),
                         AdbMxb4Data_GetConfigVehicleMode(),
                         AdbMxb4Data_GetVESMainState(),
                         AdbMxb4Data_GetYawRate(),
                         AdbMxb4Data_GetMountingSide(),
                         &CurtainEffectStatus,
                         &HBBStatus
                        ); 
  //---------------------------------------------------------------------------

  // --------------------------------------------------------------------------
  // write outputs
  // --------------------------------------------------------------------------
  // --------------------------------------------------------------------------
  // --------------------------------------------------------------------------
  // Adb Status
  AdbMxb4Data_AdbStatus(CurtainEffectStatus, HBBStatus);
  // --------------------------------------------------------------------------
  // Adb Channel 1  
  AdbMxb4Data_ConvertAdbChannel(Get_Sa2_AdbChannel1_LeftHL(), Get_Sa2_AdbChannel1_RightHL(), nAdbMode, ADBMXB4DATA_CHANNEL_1);
  // --------------------------------------------------------------------------
  // Adb Channel 2
  AdbMxb4Data_ConvertAdbChannel(Get_Sa2_AdbChannel2_LeftHL(), Get_Sa2_AdbChannel2_RightHL(), nAdbMode, ADBMXB4DATA_CHANNEL_2);
  // --------------------------------------------------------------------------
  // Adb Channel 3
  AdbMxb4Data_ConvertAdbChannel(Get_Sa2_AdbChannel3_LeftHL(), Get_Sa2_AdbChannel3_RightHL(), nAdbMode, ADBMXB4DATA_CHANNEL_3);
  // --------------------------------------------------------------------------
  // Adb Channel 4
  AdbMxb4Data_ConvertAdbChannel(Get_Sa2_AdbChannel4_LeftHL(), Get_Sa2_AdbChannel4_RightHL(), nAdbMode, ADBMXB4DATA_CHANNEL_4);
  // --------------------------------------------------------------------------
  // Adb Channel 5
  AdbMxb4Data_ConvertAdbChannel(Get_Sa2_AdbChannel5_LeftHL(), Get_Sa2_AdbChannel5_RightHL(), nAdbMode, ADBMXB4DATA_CHANNEL_5);

  // Send GFHB_DIAG to SysMonTx
  boGfhbDiag = AdbMxb4Data_Get_GfhbDiag();
  Rte_Write_AdbMxb_Gfhb_Diag(&boGfhbDiag);

  // PRQA S 5310 1 // PRQA S 5324 1 // PRQA S 5330 1 // PRQA S 5334 1 // PRQA S 5344 1 // program architecture and readability
}

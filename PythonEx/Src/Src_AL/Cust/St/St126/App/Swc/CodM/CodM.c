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
/// \file   CodM.c
///
/// \brief
///
/// \descr  This module stores the coding parameters for all the modules, initializes the ram mirror,
///         stores data to rom memory. Selects the ECU Variant and updates the side of the steeringwheel
///         Based on the variant selected.
///
///
///
///
/// \author Cretu Vlad (F78845C)
///         mailTo:vladut-ioan.cretu[at]marelli.com
//-----------------------------------------------------------------------------
//=============================================================================
// includes
//=============================================================================
#include "CodM.h"
#include "CodM_Hw.h"
#include "CodM_RteAccess.h"

#include <Std_Types.h>
#include <Cfg/Cfg.h>
#include <RteCommonTypes.h>
#include <Dem.h>
#include <EcuM.h>
#include <SysCrc.h>
#ifndef UNIT_TEST
#include <CddEft.h>
#endif
#include <Bsw/Nvm/Nvm.h>

//=============================================================================
// preprocessor definitions
//=============================================================================


//=============================================================================
// typedefs
//=============================================================================

//=============================================================================
// variables
//=============================================================================
STATIC_AL boolean CodM_boPavDataValid;
STATIC_AL boolean boSteeringWhl_FlagRx = FALSE;
//=============================================================================
// prototypes
//=============================================================================
STATIC_AL void    CodM_InitModules(tParaFct0_Cmd eCmd);

// TO BE USED
//STATIC_AL void    CodM_DetectSideChange(void);
//STATIC_AL boolean CodM_DetectTouristMSwitchOff(void);
//STATIC_AL boolean CodM_DetectTouristMSwitchOn(void);
//----------------------------------------------------------------------------
/// \brief  Initialization
///
/// \descr  Provide pointer to coding area.
///
/// \param  -
///
/// \return -
//-----------------------------------------------------------------------------
void CodM_Init(void)
{
  //teRte_CodM_eHeadLampType eHeadlampType;
  //eHeadlampType = eCal_INVALID;
  tsSysCrc_CalibGetStatus sCrcCalibStatus;
  boolean boCrcEftStatus;

#ifndef UNIT_TEST
  boCrcEftStatus = EFT_DATA_VALID_STATUS;
#else
  boCrcEftStatus = CddEft_DataValid();
#endif
  // Open diagnostic window (in normal init without diag-mux-on received over the CAN, the diagnostic will not work)
  Rte_Call_DemPrj_Set_DiagWindow(TRUE);

  if (boCrcEftStatus != FALSE)
  {
    // Check if the coding is present
    if ((CalibrationRom[0] != 0xFFu) || (CalibrationRom[1] != 0xFFu))
    {

      // Set the dtc with passed
      Rte_Call_DemPrj_ReportErrorStatus((uint16)CALIB_ERR_MISSING_CALIB, DEM_EVENT_STATUS_PASSED);
      // Read SysCrc calib status
      (void)SysCrc_RomSegs_GetCalibState(&sCrcCalibStatus);
      // Check if CRC ok?
      if ((sCrcCalibStatus.boCalibCheckInitStatus != FALSE) && (sCrcCalibStatus.boCalibFailStatus == FALSE))
      {
        // Init coding valid
        CodM_InitModules(eParaFct0_CodingDataValid);

        // Reset DTC Calibration Parameter failure
        Rte_Call_DemPrj_ReportErrorStatus((uint16)CALIB_PARAM_CALIB_DEFECT, DEM_EVENT_STATUS_PASSED);
      }
      else
      {
        // Initialize modules according to the validity of the coding data
        CodM_InitModules(eParaFct0_CodingDataInvalid);

        // Set DTC Calibration Parameter failure
        Rte_Call_DemPrj_ReportErrorStatus((uint16)CALIB_PARAM_CALIB_DEFECT, DEM_EVENT_STATUS_FAILED);
      }
    }
    else
    {
      // Coding missing set dtc
      Rte_Call_DemPrj_ReportErrorStatus((uint16)CALIB_ERR_MISSING_CALIB, DEM_EVENT_STATUS_FAILED);
      // Set coding invalid
      CodM_InitModules(eParaFct0_CodingDataInvalid);
    }

  }
  else
  {
    // Initialize modules according to the validity of the coding data
    CodM_InitModules(eParaFct0_CodingDataInvalid);
  }
  // Close diagnostic window (in normal init without diag-mux-on received over the CAN, the diagnostic will not work)
  Rte_Call_DemPrj_Set_DiagWindow(FALSE);
}
//-----------------------------------------------------------------------------
/// \brief  Initialize modules with a pointer to coding area.
///
/// \descr
///
/// \param  eCmd
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CodM_InitModules(tParaFct0_Cmd eCmd)
{
  tsRteCodingParameters CodingParameters;

  // Mapped the state and the coding blocks
  CodingParameters.eCodingState = eCmd;
  //PRQA S 310,311,312, 3305 1 // special memory mapping mechanism, the address of CalibrationRom is strict alligned and the type is compatible
  CodingParameters.psCodingParameters_Blocks = (tNvmPara_CodingArea*)&CalibrationRom[0];
    
  // calls to application components
  (void)Rte_Write_CodM_AppM_Para(&CodingParameters);
  (void)Rte_Write_CodM_Err_Para(&CodingParameters);
  (void)Rte_Write_CodM_CtrlLed_Para(&CodingParameters);
  (void)Rte_Write_CodM_Rsens_Para(&CodingParameters);
  (void)Rte_Write_CodM_CtrlFan_Para(&CodingParameters);
  (void)Rte_Write_CodM_SysVolt_Para(&CodingParameters);
  (void)Rte_Write_CodM_CddLed_Para(&CodingParameters);
  (void)Rte_Write_CodM_CddSwi_Para(&CodingParameters);
  (void)Rte_Write_CodM_CddBoost_Para(&CodingParameters);
  (void)Rte_Write_CodM_SigPrep_Para(&CodingParameters);
  (void)Rte_Write_CodM_SysMon_Para(&CodingParameters);
  // PRQA S 3200 1
  (void)Rte_Write_CodM_FctR_Para(&CodingParameters); // The suppression is made because this variable is read and used but in other modules
  (void)Rte_Write_CodM_Anima_Para(&CodingParameters);
  (void)Rte_Write_CodM_Pitch_Para(&CodingParameters);
#if defined(CFG_VARIANT_ECO) || defined(UNIT_TEST)
  (void)Rte_Write_CodM_IoHwAbUser_Para(&CodingParameters);
#endif
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
  // PRQA S 3200 3
  (void)Rte_Write_CodM_Adb_Pxa_Para(&CodingParameters); //The suppression is made because this variable is read and used but in other modules
// // Adb
  (void)Rte_Write_CodM_Adb_Mxb_Para(&CodingParameters); //The suppression is made because this variable is read and used but in other modules
  (void)Rte_Write_CodM_CtrlStp_Para(&CodingParameters);
  (void)Rte_Write_CodM_CddStp_Para(&CodingParameters);
  (void)Rte_Write_CodM_CtrlPxl_Para(&CodingParameters);
  (void)Rte_Write_CodM_CddMlc_Para(&CodingParameters);
  // Dbl
  (void)Rte_Write_CodM_Dbl_Para(&CodingParameters);
#endif

}//PRQA S 5324 55 //The number of calls is intended

// To be called when the tourist mode is clarified
//-----------------------------------------------------------------------------
/// \brief  Cycle runnable used to select the region between UK and EU
///
/// \descr  Based on the side of the steering wheel, selection for UK or EU will be made.
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CodM_Cycle0(void)
{
#if 0
  tsRte_HandTraffic sSteeringWheel_Side = { eRightHandTraffic, SIG_SNA };
  //teRte_CodM_eHeadLampType eHeadlampType;
  static uint8 ucHeadlampIdentity = 0u;

  // Read the port only at the first cycle after the init was done.
  if (boSteeringWhl_FlagRx == FALSE)
  {
    // Reading the from RTE
  //  (void)CodM_RteAccess_Read_CodM_SteeringWheel_Side_Info(&sSteeringWheel_Side);

    // Wait until the signal is received with the valid value
    if (sSteeringWheel_Side.eSigQty == SIG_VALID)
    {

      // If UK Version is selected ram mirror reinit
      if (sSteeringWheel_Side.eHandTraffic == eLeftHandTraffic)
      {
        //eHeadlampType = eCal_FULL;

        //// Update variant identity for minimum brightness param integrity check
        //ucHeadlampIdentity = (uint8)eCal_Family;

        //CodM_InitRamMirror((uint8)eHeadlampType);

        //CodM_InitModules(eParaFct0_CodingDataValid);

        // Write version selected
        //(void)Rte_Write_CodM_Calibration_Type(&eHeadlampType);

      }
      else
      {
        // Nothing changed the EU region selection is kept.
      }

      // Set the flag on true for calling the handling only once
      boSteeringWhl_FlagRx = TRUE;
    }
    else
    {
      // Continue until a valid signal is received.
    }
  }
  else
  {
    // CodM_DetectSideChange();
  }

  // Check Minimum Brightness Parameters Integrity (CRC32)
 // CodM_CheckAndUpdateMinBrightnessParam(ucHeadlampIdentity);
#endif
} //PRQA S 5334 1 // architecture


// To be used
//-----------------------------------------------------------------------------
/// \brief  CodM_DetectSideChange
///
/// \descr  detects and changes side
///
/// \param  void
///
///
/// \return -void
//-----------------------------------------------------------------------------
//STATIC_AL void CodM_DetectSideChange(void)
//{
//  // requests from tourist mode to change distributions
//  boolean boTMSwitchOn, boTMSwitchOff;
//  teRte_CodM_eHeadLampType eHeadlampType;
//
//  boTMSwitchOn = CodM_DetectTouristMSwitchOn();
//  boTMSwitchOff = CodM_DetectTouristMSwitchOff();
//
//
//
//  // If UK Version is selected ram mirror reinit
//  if(boTMSwitchOn != FALSE)
//  {
//    eHeadlampType = eCal_High_UK;
//    CodM_InitRamMirror((uint8)eHeadlampType);
//    CodM_InitModules(eParaFct0_CodingDataValid);
//
//    // Write version selected
//    (void)CodM_RteAccess_Write_CodM_Calibration(&eHeadlampType);
//
//  }
//  else if (boTMSwitchOff != FALSE)
//  {
//    eHeadlampType = eCal_High_EU;
//    CodM_InitRamMirror((uint8)eHeadlampType);
//    CodM_InitModules(eParaFct0_CodingDataValid);
//
//    // Write version selected
//    (void)CodM_RteAccess_Write_CodM_Calibration(&eHeadlampType);
//
//  }
//  else
//  {
//    // leave previous values
//  }
//}

//-----------------------------------------------------------------------------
/// \brief  CodM_GetheadlampHW_FullVersion
///
/// \descr  analyzes the output of CodM_GetHedlampHW_Region() and CodM_GetHedlampHW_Version() in order
///         to determine the full version of the headlamp and sends the information via RTE port
///
/// \param
///
/// \return uint8 : returns the full version of the headlamp
//-----------------------------------------------------------------------------
// TO BE USED
//STATIC_AL teRte_CodM_eHeadLampType CodM_GetHeadlampHW_FullVersion(void)
//{
//  uint8 ucRegion;
//  uint8 ucVersion;
//  uint8 ucHeadlamp;
//  teRte_CodM_eHeadLampType sHeadlampStruct;
//
//  // get the region and version specific for the headlamp
//
//  ucVersion = CodM_GetHedlampHW_Version();
//
//  //If invalid Code read for HW Region or HW version
//  if ((ucRegion == (uint8)eCal_INVALID) || (ucVersion == (uint8)eCal_INVALID))
//  {
//    // Set invalid Coding read to the variable
//    ucHeadlamp = (uint8)eCal_INVALID;
//  }
//  else
//  {
//    // addion in order to get the full version
//   // ucHeadlamp = (uint8)(ucRegion + ucVersion);
//    ucHeadlamp = ucVersion;
//  }
//
//  // PAV data valid, set the variant of the headlamp to the one determined above
//  sHeadlampStruct = (uint8)ucHeadlamp;
//
//  return sHeadlampStruct;
//}

// TO BE USED
//-----------------------------------------------------------------------------
/// \brief CodM_RteAccess_DetectTouristMSwitchOff
///
/// \descr returns true if request was turned off from on
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
//STATIC_AL boolean CodM_DetectTouristMSwitchOff(void)
//{
//  static teCodM_HandTraffic   ePrevValue =(teCodM_HandTraffic)eInitValue;
//  teCodM_HandTraffic          eCurrentValue = (teCodM_HandTraffic)eInitValue;
//  boolean boReturn = FALSE;
//
//  eCurrentValue = (teCodM_HandTraffic)CodM_RteAccess_GetTouristMState();
//
//  // check if request was switched from on to off
//  if ((ePrevValue != eRightHandTraffic) && (eCurrentValue == eRightHandTraffic))
//  {
//    boReturn = TRUE;
//  }
//  else
//  {
//    // leave return value false
//  }
//
//  ePrevValue = eCurrentValue;
//
//  return boReturn;
//}


// TO BE USED
//-----------------------------------------------------------------------------
/// \brief CodM_RteAccess_DetectTouristMSwitchOn
///
/// \descr returns true if request was turned off from on
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
//STATIC_AL boolean CodM_DetectTouristMSwitchOn(void)
//{
//  static teCodM_HandTraffic   ePrevValue = eInitValue;
//  teCodM_HandTraffic          eCurrentValue = eInitValue;
//  boolean boReturn = FALSE;
//
//  eCurrentValue = CodM_RteAccess_GetTouristMState();
//
//  // check if request was switched from on to off
//  if ((ePrevValue != eLeftHandTraffic) && (eCurrentValue == eLeftHandTraffic))
//  {
//    boReturn = TRUE;
//  }
//  else
//  {
//    // leave return value false
//  }
//
//  ePrevValue = eCurrentValue;
//
//  return boReturn;
//}

// EOF

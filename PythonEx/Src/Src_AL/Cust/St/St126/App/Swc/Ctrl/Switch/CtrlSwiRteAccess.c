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
/// \file   CtrlFanRteAccess.c
///
/// \brief  encapsule RTE access
///
/// \descr  Functions used for the CtrlFan RTE wrapper, for input/output 
///
/// \author Cretu Vladut-Ioan ALRO/AL (F78845C)
///         mailTo:vladut-ioan.cretu[at]magnetimarelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================
#include <CtrlSwi.h>
#include <CtrlSwiRteAccess.h>

//=============================================================================
// functions prototype
//=============================================================================

////-----------------------------------------------------------------------------
///// \brief  CtrlFanRteAccess_DiagFct0(teRte_CtrlFan_DiagFct0_FanCmd eCmd)         TBD
/////                                                                               TBD
///// \descr  Diagnosis control for fan                                             TBD
/////                                                                               TBD
///// \param  ulCmd - Command for fan control                                       TBD
/////                                                                               TBD
///// \return Feedback to diagnose                                                  TBD
////-----------------------------------------------------------------------------
//teRte_DiagFeedback CtrlFanRteAccess_DiagFct0(teRte_CtrlFan_DiagFct0_FanCmd eCmd)
//{
//  teRte_DiagFeedback eRetVal;
//
//  switch(eCmd)
//  {
//    case eCtrlFan_DiagFct0_StartExtTakeover:
//      //Activate diagnosis control
//      CtrlFan_Diag_ActivateDiagnosisControl();
//      eRetVal = eDiag_ProcessingDone;
//      break;
//    case eCtrlFan_DiagFct0_StopExtTakeover:
//      //Deactivate diagnosis control
//      CtrlFan_Diag_DeactivateDiagnosisControl();
//      CtrlFan_Diag_DeactivateFanControl();
//      eRetVal = eDiag_ProcessingDone;
//      break;
//    case eCtrlFan_DiagFct0_SetOff:
//      //Deactivate fan
//      CtrlFan_Diag_DeactivateFanControl();
//      eRetVal = eDiag_ProcessingDone;
//      break;
//    case eCtrlFan_DiagFct0_SetOn:
//      //Activate fan
//      CtrlFan_Diag_ActivateFanControl();
//      eRetVal = eDiag_ProcessingDone;
//      break;
//    default:
//      eRetVal = eDiag_RequestOutOfRange;
//      break;
//  }
//
//  return eRetVal;
//}

////-----------------------------------------------------------------------------
///// \brief  CtrlFanRteAccess_SetALEC                                           TBD
/////                                                                            TBD
///// \descr  Set the specific Alec according to eErrorType input parameter      TBD
/////                                                                            TBD
///// \param  eErrorTyp - type of fan error                                      TBD
/////                                                                            TBD
///// \return void                                                               TBD
////-----------------------------------------------------------------------------
//void CtrlFanRteAccess_SetALEC(teCtrlFan_newALECsError eErrorType)
//{
//  switch (eErrorType)
//  {
//  case eShort2GND:
//    Rte_Call_DemPrj_ReportErrorStatus((uint16)Fan1_E_SC_GND, DEM_EVENT_STATUS_FAILED);
//    Rte_Call_DemPrj_ReportErrorStatus((uint16)Fan1_E_OC,     DEM_EVENT_STATUS_PASSED);
//    Rte_Call_DemPrj_ReportErrorStatus((uint16)Fan1_E_SC_BAT, DEM_EVENT_STATUS_PASSED);
//    break;
//  case eShort2VBAT:
//    Rte_Call_DemPrj_ReportErrorStatus((uint16)Fan1_E_SC_GND, DEM_EVENT_STATUS_PASSED);
//    Rte_Call_DemPrj_ReportErrorStatus((uint16)Fan1_E_OC,     DEM_EVENT_STATUS_PASSED);
//    Rte_Call_DemPrj_ReportErrorStatus((uint16)Fan1_E_SC_BAT, DEM_EVENT_STATUS_FAILED);
//    break;
//  case eOpenLoad:
//    Rte_Call_DemPrj_ReportErrorStatus((uint16)Fan1_E_SC_GND, DEM_EVENT_STATUS_PASSED);
//    Rte_Call_DemPrj_ReportErrorStatus((uint16)Fan1_E_OC,     DEM_EVENT_STATUS_FAILED);
//    Rte_Call_DemPrj_ReportErrorStatus((uint16)Fan1_E_SC_BAT, DEM_EVENT_STATUS_PASSED);
//    break;
//  default:
//    Rte_Call_DemPrj_ReportErrorStatus((uint16)Fan1_E_SC_GND, DEM_EVENT_STATUS_PASSED);
//    Rte_Call_DemPrj_ReportErrorStatus((uint16)Fan1_E_OC,     DEM_EVENT_STATUS_PASSED);
//    Rte_Call_DemPrj_ReportErrorStatus((uint16)Fan1_E_SC_BAT, DEM_EVENT_STATUS_PASSED);
//    break;
//  }
//}
//-----------------------------------------------------------------------------
/// \brief  CtrlSwi_RteAccess_MapParams
///
/// \descr  Mapps the coding parameter in order to acces the in CtrlSwi
///
/// \param  [void]
///
/// \return [void]
//-----------------------------------------------------------------------------
void CtrlSwi_RteAccess_MapParams(void)
{
  tsRteCodingParameters sCodingParameters;

  // Read coding params
  (void)Rte_Read_CodM_CtrlFan_Para(&sCodingParameters);

  // Call the parafct for the mapping of the parameters
  CtrlSwi_ParaFct0(sCodingParameters.eCodingState, sCodingParameters.psCodingParameters_Blocks);

}



// EOF

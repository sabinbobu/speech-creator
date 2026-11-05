
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
/// \file   SysMonTx_Callbacks.c
///
/// \brief  Output Frame Tx Callbacks
///
/// \descr  Output Frame Tx Callbacks
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//  includes
//-----------------------------------------------------------------------------
#include <SysMonTx_Callbacks.h>
#include <SysMonRx_ASIL.h>
//#include <p_NM.h>
#include <SysMonCheck.h>

//-----------------------------------------------------------------------------
// definitions
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// functions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \brief  SysMon_TxCallbacks_CyclicFrame_457
///
/// \descr  Cyclic callback for 0x457 message frame
///
/// \param  void
///
/// \return void 
//-----------------------------------------------------------------------------
void SysMon_TxCallbacks_CyclicFrame_457(void) //left
{
  tsRte_Hs6_Diag_Drvled_L_457 data    = { 0 };
  uint8  ucLowBeamFault[1]            = { 0 };
  uint8  ucFrontTurnIndicatorFault[1] = { 0 };
  uint8  ucLevellingAdjustFault[1] = { 0 };
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  uint8  ucDynamicBendingBeamFault[1] = { 0 };
  uint8  ucGfhbFault[1]               = { 0 };
  uint8  ucStaticBendingBeamFault[1]  = { 0 };
  tsRte_Hs6_Diag_Drvled_BendingBeamFault sBendingBeamFault = { 0 };
#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)
  uint8   ucDiagTI            = SYSMONTX_CALLBACKS_DIAG_TI_OK;
  boolean boDiagLowBeam       = FALSE;
  boolean boDiagTurnIndicator = FALSE;
  boolean boDiagLbEmergOpMode = FALSE;
  boolean boDiagTiEmergOpMode = FALSE;
  boolean boDiagTiElecError   = FALSE;
  tsRte_LgtFctState sLgtFctDiag;
  tSysMon_SendFrame457 stData;

  (void)Rte_Read_FctR_LgtFctState(&sLgtFctDiag);
  (void)Rte_Read_DrvLedDiag(&data); // for ECO version the modules which write the LED status must be configured 

  // Get DIAG LB in case of Emergecy Operation Mode
  boDiagLbEmergOpMode = SysMonRx_ASIL_Get_boDiagLowBeamStatus();
  // Get DIAG TI in case of Emergency Operation Mode
  boDiagTiEmergOpMode = SysMonRx_ASIL_Get_boDiagTurnIndicatorStatus();
  // Get DIAG TI in case of Electrical Errors
  boDiagTiElecError = SysMonCheck_TI_Diag_Status();

  // Get Diagnostic Status from SysMonRx_ASIL
  boDiagLowBeam       = ((boDiagLbEmergOpMode != FALSE) || (sLgtFctDiag.boLb_State != FALSE)) ? TRUE : FALSE;
  boDiagTurnIndicator = ((boDiagTiEmergOpMode != FALSE) || (boDiagTiElecError != FALSE)) ? TRUE : FALSE;

  // Convert TI from boolean to result on 2 bits.
  ucDiagTI = (boDiagTurnIndicator != FALSE) ? SYSMONTX_CALLBACKS_DIAG_TI_NOK : SYSMONTX_CALLBACKS_DIAG_TI_OK;

  ucLowBeamFault[0]            = (uint8)boDiagLowBeam;
  ucFrontTurnIndicatorFault[0] = (uint8)ucDiagTI;
  ucLevellingAdjustFault[0]    = (uint8)data.eLevellingAdjustFault;

#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version

  (void)Rte_Read_Dbl_SysMonTx_FullStatus(&sBendingBeamFault);

  ucDynamicBendingBeamFault[0] = (uint8)sBendingBeamFault.eDynamicBendingBeamFault;
  ucGfhbFault[0]               = (uint8)(sLgtFctDiag.boGfHb_State);
  ucStaticBendingBeamFault[0]  = (uint8)(sLgtFctDiag.boSbl_State);

  //send status
  stData.ucDynamicBendingBeamFault = ucDynamicBendingBeamFault[0]; // can we transform the arrays into nonarray variables?
  stData.ucGfhbFault               = ucGfhbFault[0];
  stData.ucStaticBendingBeamFault  = ucStaticBendingBeamFault[0];
  

#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)

  stData.ucLowBeamFault            = ucLowBeamFault[0];
  stData.ucFrontTurnIndicatorFault = ucFrontTurnIndicatorFault[0];
  stData.ucLevellingAdjustFault    = ucLevellingAdjustFault[0];

  (void)Rte_Write_SysMon_SendFrame457(&stData);
}



//-----------------------------------------------------------------------------
/// \brief  SysMon_TxCallbacks_CyclicFrame_477
///
/// \descr  Cyclic callback for 0x477 message frame
///
/// \param  void
///
/// \return void 
//-----------------------------------------------------------------------------
void SysMon_TxCallbacks_CyclicFrame_477(void)
{
  uint8   ucDiagTI                  = SYSMONTX_CALLBACKS_DIAG_TI_OK;
  boolean boDiagLowBeam             = FALSE;
  boolean boDiagTurnIndicator       = FALSE;
  boolean boDiagLbEmergOpMode       = FALSE;
  boolean boDiagTiEmergOpMode       = FALSE;
  boolean boDiagTiElecError         = FALSE;
#if defined (CFG_VARIANT_ECO) || defined (UNIT_TEST) // Applicable only for ECO version
  tsRte_Hs6_Diag_Drvled_R_477 data  = { 0 };
  uint8  ucLevellingAdjustFaultR[1] = { 0 };
#endif
  
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  uint8  ucGfhbFault[1]              = { 0 };
  uint8  ucStaticBendingBeamFault[1] = { 0 };
#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)

  uint8   ucLowBeamFault[1]             = { 0 };
  uint8   ucFrontTurnIndicatorFault[1]  = { 0 };

  tsRte_LgtFctState sLgtFctState;
  tSysMon_SendFrame477 stData;

  (void)Rte_Read_FctR_LgtFctState(&sLgtFctState);
#if defined (CFG_VARIANT_ECO) || defined (UNIT_TEST) // Applicable only for ECO version
  (void)Rte_Read_DrvLedDiagR(&data);
#endif

  // Get DIAG LB in case of Emergecy Operation Mode
  boDiagLbEmergOpMode = SysMonRx_ASIL_Get_boDiagLowBeamStatus();
  // Get DIAG TI in case of Emergency Operation Mode
  boDiagTiEmergOpMode = SysMonRx_ASIL_Get_boDiagTurnIndicatorStatus();
  // Get DIAG TI in case of Electrical Errors
  boDiagTiElecError = SysMonCheck_TI_Diag_Status();

  // Get Diagnostic Status from SysMonRx_ASIL
  boDiagLowBeam       = ((boDiagLbEmergOpMode != FALSE) || (sLgtFctState.boLb_State != FALSE)) ? TRUE : FALSE;
  boDiagTurnIndicator = ((boDiagTiEmergOpMode != FALSE) || (boDiagTiElecError != FALSE)) ? TRUE : FALSE;

  // Convert TI from boolean to result on 2 bits.
  ucDiagTI = (boDiagTurnIndicator != FALSE) ? SYSMONTX_CALLBACKS_DIAG_TI_NOK : SYSMONTX_CALLBACKS_DIAG_TI_OK;

  ucFrontTurnIndicatorFault[0] = (uint8)ucDiagTI;
  ucLowBeamFault[0]            = (uint8)boDiagLowBeam;
#if defined (CFG_VARIANT_ECO) || defined (UNIT_TEST) // Applicable only for ECO version
  ucLevellingAdjustFaultR[0]   = (uint8)data.eLevellingAdjustFaultR;
#endif

#if defined (CFG_VARIANT_FULL) ||  defined (UNIT_TEST) // Applicable only for FULL version
  ucGfhbFault[0] = (uint8)(sLgtFctState.boGfHb_State);
  ucStaticBendingBeamFault[0] = (uint8)(sLgtFctState.boSbl_State);

  stData.ucGfhbFault = ucGfhbFault[0];
  stData.ucStaticBendingBeamFault = ucStaticBendingBeamFault[0];
#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)

  stData.ucLowBeamFault            = ucLowBeamFault[0];
  stData.ucFrontTurnIndicatorFault = ucFrontTurnIndicatorFault[0];
#if defined (CFG_VARIANT_ECO) || defined (UNIT_TEST) // Applicable only for ECO version
  stData.ucLevellingAdjustFaultR   = ucLevellingAdjustFaultR[0];
#endif

  (void)Rte_Write_SysMon_SendFrame477(&stData);
}



//-----------------------------------------------------------------------------
/// \brief  SysMon_TxCallbacks_ToFrame_4x7
///
/// \descr  Time-Out callback for 457/477 cylic message frame
///
/// \param  void
///
/// \return void 
//-----------------------------------------------------------------------------
void SysMon_TxCallbacks_ToFrame_4x7(void)
{
  return;
}



// EOF

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
/// \file  CtrlPxl_Diag.c
///
/// \brief Diagnostic handling for CtrlPxl
///
/// \author Caba Ionut-Stefan (F37899C)
///         mailTo:ionut-stefan.caba[at]marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================
#include <AL_Helper.h>
#include "CtrlPxl_RteAccess.h"
#include "CtrlPxl_Diag.h"
#include "CtrlPxl_Cfg.h"
#include "CtrlPxl_Data.h"
#include "CtrlPxl_Types.h"

//=============================================================================
// types
//=============================================================================
STATIC_AL tsCtrlPxl_MatrixFaultStates CtrlPxl_sMatrixFault;
STATIC_AL tuCtrlPxl_PxlFault CtrlPxl_aPxlState[CFG_MLC_Chip_Cnt] ;
STATIC_AL uint8 CtrlPxl_aucCrcState[CFG_MLC_Chip_Cnt] ;
STATIC_AL tsCtrlPxl_ComStatus CtrlPxl_sMlcStatus = { 0u, 0u };

//=============================================================================
// functions prototype
//=============================================================================

STATIC_AL void CtrlPxl_Diag_HandleMlcComFault(void);
STATIC_AL void CtrlPxl_Diag_HandleMlcPxlFault(void);
STATIC_AL void CtrlPxl_Diag_HandleMlcCrcFault(void);
STATIC_AL void CtrlPxl_Diag_Handle_VCCx(void);

#ifdef UNIT_TEST
STATIC_AL void CtrlPxl_Special_UT_Instrumentation_Force_DefaultVccxState(uint8* pucData);
#endif

//=============================================================================
// functions
//=============================================================================
//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_Diag_HandleMlcCrcFault
///
/// \descr  This function handles crc defect
///
/// \param  none
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlPxl_Diag_HandleMlcCrcFault(void)
{
  STATIC_UT(TIMER, ulCrcDefect_CycleTimer, 0u);
  STATIC_UT(TIMER, ulCrcDefect_GeneralTimer, 0u);
  STATIC_UT(uint32, ulCrcDefect_Timer, 0u);

  boolean boErrPermanent = FALSE;
  boolean boErrPresent = FALSE;

  //get the cycle time : 10ms
  ulCrcDefect_CycleTimer = (TimerGetTimeSince(ulCrcDefect_GeneralTimer) / CTRLPXL_MS_CONVERTION);
  ulCrcDefect_GeneralTimer = TimerGetTick();

  //get the CRC error status from matrix driver
  CTRLPXL_RTE_RE_GET_MLC_CRCERROR(CtrlPxl_aucCrcState);

  for (uint8_fast ucIdx = 0u; ucIdx < CFG_MLC_Chip_Cnt; ucIdx++)
  {
    boErrPresent |= (CtrlPxl_aucCrcState[ucIdx] != 0u) ? TRUE : FALSE;
  }
  // set error status only if the maturation time is reached
  // if an error appears, but disappears in the meantime, don't take into account
  if (ulCrcDefect_Timer < CTRL_PXL_CRC_DEFECT_DEBOUNCE_TIME)
  {
    if (boErrPresent != FALSE)
    {
      ulCrcDefect_Timer += ulCrcDefect_CycleTimer;
    }
    else
    {
      //in the meantime, CRC defect dissapears, reset timer
      ulCrcDefect_Timer = 0u;
    }
  }
  else
  {
    // timer reset if matrix doesn't send error present after timer exceeded maturation
    if (boErrPresent == FALSE)
    {
      ulCrcDefect_Timer = 0u;
    }
    //set CRC defect after timer expired
    boErrPermanent = TRUE;
  }
  CtrlPxl_sMatrixFault.boCrcFault = (boErrPermanent != FALSE) ? TRUE : FALSE;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_Diag_HandleMlcPxlFault
///
/// \descr  This function handles pixel defect
///
/// \param  none
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlPxl_Diag_HandleMlcPxlFault(void)
{
  STATIC_UT(TIMER, ulPxlDefect_CycleTimer, 0u);
  STATIC_UT(TIMER, ulPxlDefect_GeneralTimer, 0u);
  STATIC_UT(uint32, ulPxlDefect_Timer, 0u);

  boolean boErrPermanent = FALSE;
  boolean boErrPresent = FALSE;

  //get the cycle time : 10ms
  ulPxlDefect_CycleTimer = (TimerGetTimeSince(ulPxlDefect_GeneralTimer) / CTRLPXL_MS_CONVERTION);
  ulPxlDefect_GeneralTimer = TimerGetTick();

  //get the pixel error status from matrix driver
  boErrPresent = CtrlPxl_RteAccess_Get_PxlErrorStatus(CtrlPxl_aPxlState);

  // set error status only if the maturation time is reached
  // if an error appears, but disappears in the meantime, don't take into account
  if (ulPxlDefect_Timer < CTRL_PXL_LED_DEFECT_DEBOUNCE_TIME) 
  {
    if (boErrPresent != FALSE)
    {
      ulPxlDefect_Timer += ulPxlDefect_CycleTimer;
    }
    else
    {
      //in the meantime, pixel defect dissapears, reset timer
      ulPxlDefect_Timer = 0u;
    }
  }
  else
  {
    // timer reset if matrix doesn't send error present after timer exceeded maturation
    if (boErrPresent == FALSE)
    {
      ulPxlDefect_Timer = 0u;
    }
    //set pixel defect after timer expired
    boErrPermanent = TRUE;
  }
  CtrlPxl_sMatrixFault.boPxlFault = (boErrPermanent != FALSE) ? TRUE : FALSE;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_Diag_HandleMlcComFault
///
/// \descr this function is used to handle communication fault
///
/// \param  -
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlPxl_Diag_HandleMlcComFault(void)
{
  STATIC_UT(TIMER, ulComDefect_CycleTimer, 0u);
  STATIC_UT(TIMER, ulComDefect_GeneralTimer, 0u);
  STATIC_UT(uint32,ulComDefect_Timer, 0u);

  boolean boErrPermanent = FALSE;
  boolean boErrPresent = FALSE;
  //get the cycle time : 10ms
  ulComDefect_CycleTimer = (TimerGetTimeSince(ulComDefect_GeneralTimer) / CTRLPXL_MS_CONVERTION);
  ulComDefect_GeneralTimer = TimerGetTick();

  //get the pixel error status from matrix driver
  boErrPresent = CtrlPxl_RteAccess_Get_CommErrorStatus(&CtrlPxl_sMlcStatus);

  // set error status only if the maturation time is reached
  // if an error appears, but disappears in the meantime, don't take into account
  if (ulComDefect_Timer < CTRL_PXL_COM_ERROR_DEBOUNCE_TIME)
  {
    if (boErrPresent != FALSE)
    {
      ulComDefect_Timer += ulComDefect_CycleTimer;
    }
    else
    {
      //in the meantime, communication defect dissapears, reset timer
      ulComDefect_Timer = 0u;
    }
  }
  else
  {
    // timer reset if matrix doesn't send error present after timer exceeded maturation
    if (boErrPresent == FALSE)
    {
      ulComDefect_Timer = 0u;
    }
    //set communication defect after timer expired
    boErrPermanent = TRUE;
  }
  CtrlPxl_sMatrixFault.boCommFault = (boErrPermanent != FALSE) ? TRUE : FALSE;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_Diag_Handle_VCCx
///
/// \descr  Handler for matrix external supply error error
///
/// \param  -none
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlPxl_Diag_Handle_VCCx(void)
{
  //read VccxState
  const teCtrlPxl_VccxLineState ucVccxState = CTRLPXL_RTE_RE_GET_VCCX_STATUS;

#ifdef UNIT_TEST
  CtrlPxl_Special_UT_Instrumentation_Force_DefaultVccxState(&ucVccxState);
#endif

  switch (ucVccxState)
  {
  case eMatrixVccx_noError: 
    CtrlPxl_sMatrixFault.boShortToGnd   = FALSE;
    CtrlPxl_sMatrixFault.boShortToVbat  = FALSE;
    break;
  case eMatrixVccx_Short2GND:
    CtrlPxl_sMatrixFault.boShortToGnd   = TRUE; 
    CtrlPxl_sMatrixFault.boShortToVbat  = FALSE;
    break;
  case eMatrixVccx_Short2Vbat : 
    CtrlPxl_sMatrixFault.boShortToVbat  = TRUE; 
    CtrlPxl_sMatrixFault.boShortToGnd   = FALSE;
    break;
  default:
    break;
  }
}

//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_Diag_ErrorDetected
///
/// \descr  check if there is any kind of error on MLC and call the function to
///         set the corresponding error status through the DTC
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------
void CtrlPxl_Diag_ErrorDetected(void)
{
  CtrlPxl_Diag_HandleMlcComFault();
  CtrlPxl_Diag_HandleMlcPxlFault();
  CtrlPxl_Diag_HandleMlcCrcFault();
  CtrlPxl_Diag_Handle_VCCx();
  CTRLPXL_RTE_SE_MATRIX_FAULT(&CtrlPxl_sMatrixFault)
}


//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_GetMtxFaults
///
/// \descr  Map the corespomding error based on [chip][pxl.indx] and return all error via uint8
///
/// \param  ucDevice  : MLC device index
/// \param  ucSwitch  : pixel index
///
/// \return tuCtrlPxl_bErr : matrix errors (loss of comm / corrupt comm/ pxl defect)
//-----------------------------------------------------------------------------
tuCtrlPxl_bErr CtrlPxl_GetMtxFaults(uint8_fast ucDevice, uint8_fast ucSwitch)
{
  tuCtrlPxl_bErr uMtxFaults;
  uint8 ucRetError = FALSE;
  //initialization of faults
  uMtxFaults.ucRaw = 0U;

  //loss comm error detected
  if (CtrlPxl_sMatrixFault.boCommFault != FALSE)
  {
    uMtxFaults.bErr.bLossComm = ( ((CtrlPxl_sMlcStatus.ucMlcStatus)  & ((uint32)1u << ucDevice)) != 0u) ? TRUE : FALSE;
  }

  //CRC error detected
  if (CtrlPxl_sMatrixFault.boCrcFault != FALSE)
  {
    uMtxFaults.bErr.bCoruptComm = (CtrlPxl_aucCrcState[ucDevice] != 0u) ? TRUE : FALSE;
  }

  //pixel error detected
  if (CtrlPxl_sMatrixFault.boPxlFault != FALSE)
  {
    uMtxFaults.bErr.bPxlFault = ((CtrlPxl_aPxlState[ucDevice].bPxl.unLedFault & (uint16)((uint16)1u << ucSwitch)) != 0u) ? TRUE : FALSE;
  }

  return uMtxFaults;
}

#ifdef UNIT_TEST
//-----------------------------------------------------------------------------
/// \brief CtrlPxl_Special_UT_Instrumentation_Force_DefaultVccxState
///
/// \descr Special UT instrumentation handler (simulates undefined Vccx state)
///
/// \param  uint16* puncData
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlPxl_Special_UT_Instrumentation_Force_DefaultVccxState(uint8* pucData)
{
  STATIC_UT(boolean, CtrlPxl_Force_DefaultVccxState, FALSE);

  if (CtrlPxl_Force_DefaultVccxState == TRUE)
  {
    *pucData = 255u;
  }
  else
  {
    // skip the UT instrumentation
  }

}
#endif

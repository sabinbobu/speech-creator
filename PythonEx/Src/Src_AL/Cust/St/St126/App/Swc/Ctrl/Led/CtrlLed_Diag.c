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
/// \file  CtrlLed_Diag.c
///
/// \brief core module for CtrlLed
///
/// \author Caba Ionut-Stefan (F37899C)
///         mailTo:ionut-stefan.caba[at]marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================
#include "CtrlLed_Diag.h"
#include "CtrlLed_Rte.h"
#include "CtrlLed_Data.h"
#include "CtrlLed_Cfg.h"
#include <Util_Time.h>

//=============================================================================
// defines
//=============================================================================
//derating status is active while the current is lower then 70% of nominal current
#define CTRLLED_DIAG_DERATING_STATUS(current, nominal_current) (current) < ((7U * (nominal_current)) / 10U) ? TRUE : FALSE

#define CTRLLED_SET_DTC       1U
#define CTRLLED_RESETSET_DTC  2U
#define CTRLLED_NO_DTC_ACTION 3U

//=============================================================================
// types
//=============================================================================
STATIC_AL CONST_AL tsCtrlLed_DtcChList      asDTC_List[]       = CTRLLED_DTC_CH_LIST;
STATIC_AL CONST_AL tsCtrlLed_ReactionChList asReaction_List[]  = CTRLLED_REACTION_CH_LIST;
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
STATIC_AL tsCtrlLed_DtcMtxHbLbList asMtx_DTC_List[] = CTRLLED_DTC_MTX_PXL_LIST;
STATIC_AL CONST_AL uint8 asReactionPxl_List[] = CTRLLED_PIXEL_REACTION_LIST;
#endif
//=============================================================================
// function prototypes
//=============================================================================
STATIC_AL tsCtrlLed_ChannelSettings CtrlLed_Diag_DisableError_Cmd (uint8_fast ucIdx, CONST_AL boolean boVinStatus, uint16 unCurrent);
STATIC_AL void CtrlLed_HandleChannelErrors(uint8_fast ucIl, uint8_fast ucChannel, uint8 ucErr, boolean boNewReq);
STATIC_AL void CtrlLed_ReportDtc(uint8 ucDtcState, uint16 *punPrvCh, uint8_fast ucIl, uint8_fast ucCh, uint16 *punActCh);
STATIC_AL void CtrlLed_Diag_SetChannelDtc(uint8 ucChannelName, uint8 ucErr);
STATIC_AL void CtrlLed_Diag_ResetDtc(uint8 ucChannelName, uint16 *punPrvCh, uint8_fast ucIl, uint8_fast ucCh);
STATIC_AL uint8 CtrlLed_Diag_CountErrorBitPos(uint16 unVal);
STATIC_AL boolean CtrlLed_Diag_ChReacBuckErr(uint8_fast ucIl, uint8_fast ucCh, boolean boNewLightReq, uint8 ucErr);
STATIC_AL void CtrlLed_GetHss3DiagStatus(uint8 *pucData);
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
STATIC_AL uint8 CtrlLed_Diag_Check_MtxVccx_Eeprom_Fault(boolean boVccxGnd, boolean boVccxBat, tsRte_MtxEeprom_ErrStatus sMtxEeprom_ErrStatus);
STATIC_AL void CtrlLed_SetResetMtxDtc(boolean boDtcStatus, uint8_fast ucRow);
STATIC_AL void CtrlLed_SetMtxDtc(uint8_fast ucRow, uint8_fast ucErr, boolean boHbStatus);
STATIC_AL void CtrlLed_ResetMtxDtc(uint8_fast ucRow, uint8_fast ucErr);
#endif

#if defined UNIT_TEST
/* -------------------------------------------------- --------------------------------------------*/
/* Special UT instrumentation to force channel errors reset for double-check of invalid condition */
/* ---------------------------------------------------------------------------------------------- */
STATIC_AL void CtrlLed_Special_UT_Instrumentation_Force_ResetVars(uint8* pucDtcAction, uint8* pucErrStatus);
#endif

//=============================================================================
// functions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_Diag_ErrorHandler
///
/// \descr   
///
/// \param   
///
/// \return void
//-----------------------------------------------------------------------------
tsCtrlLed_ErrorHandler CtrlLed_Diag_ErrorHandler(uint8_fast ucIl, uint8_fast ucCh, uint16 unDuty, uint16 unCurrent)
{
  tsCtrlLed_aChannelState sChannelState;
  tsCtrlLed_ErrorHandler sCtrlLed_ErrHandler;
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
  static boolean boNonMtxChOff[CTRLLED_CFG_MAX_BUCK_DRV] = { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
  static uint16 unDutyPrv[CTRLLED_CFG_MAX_BUCK_DRV] = { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
  static boolean boNewLightReq[CTRLLED_CFG_MAX_BUCK_DRV] = { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
#else
  static boolean boNonMtxChOff[CTRLLED_CFG_MAX_BUCK_DRV] = { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
  static uint16 unDutyPrv[CTRLLED_CFG_MAX_BUCK_DRV] = { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
  static boolean boNewLightReq[CTRLLED_CFG_MAX_BUCK_DRV] = { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
#endif

#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
  if (ucCh == (CTRLLED_CFG_MAX_BUCK_DRV - 1U))
#else
  if (ucCh == CTRLLED_CFG_BASIC_LED_CH)
#endif
  {
    CtrlLed_GetHss3DiagStatus(&sChannelState.asChannelState[ucCh].ucChannelStatus);
  }
  else

  {
    CTRLLED_RTE_RE_GET_LED_STATES(ucCh, &sChannelState)
  }
  //store values
  const uint8 ucChannelStatus = sChannelState.asChannelState[ucCh].ucChannelStatus;
  const boolean boVinSts = sChannelState.asChannelState[ucCh].boVinOk;

  if (unDuty == 0u)// while duty cycle is 0 do not report other LED states besides OFF status
  {
    sCtrlLed_ErrHandler.ucLedState[ucCh] = CTRLLED_DIAG_STATUS_LED_OFF;
  }
  else
  {
    sCtrlLed_ErrHandler.ucLedState[ucCh] = ucChannelStatus;
  }

  //disable error command
  sCtrlLed_ErrHandler.sCtrlLed_ChannelSettings = CtrlLed_Diag_DisableError_Cmd(ucCh, boVinSts, unCurrent);  
  //new light request
  if ((unDutyPrv[ucCh] == 0u) && (unDuty != 0u)) 
  {
    boNewLightReq[ucCh] = TRUE;
  }
  else
  {
    boNewLightReq[ucCh] = FALSE;
  }

  //check for electrical error for bucks and set the coresponding dtc
  CtrlLed_HandleChannelErrors(ucIl, ucCh, sCtrlLed_ErrHandler.ucLedState[ucCh], boNewLightReq[ucCh]);
  //store the channel reaction based on buck error
  sCtrlLed_ErrHandler.boSwitchOffBuck[ucCh] = CtrlLed_Diag_ChReacBuckErr(ucIl, ucCh, boNewLightReq[ucCh], sCtrlLed_ErrHandler.ucLedState[ucCh]);

  //store the new value
  unDutyPrv[ucCh] = unDuty;

  //return channel state
  return sCtrlLed_ErrHandler;
}
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_GetMatrixError
///
/// \descr  
///
/// \param   ucRow, ucLmmPxl, ucIll, *pboActualRowErr
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CtrlLed_GetMatrixError(uint8 ucRow, uint8 ucLmmPxl, uint8 ucIll)
{
  tuCtrlLed_bErr uLuMtxErr[CTRLLED_CFG_NR_OF_LOGICAL_UNITS] = { 0U };
  CTRLLED_RTE_RE_GET_LU_MTX_ERR(ucLmmPxl, uLuMtxErr)
  boolean boErrStatus = FALSE;

  //check errors
  if (uLuMtxErr[ucLmmPxl].ucRaw != 0U)
  {
    if ((uLuMtxErr[ucLmmPxl].bErr.bPxlFault != 0U) && (CtrlLed_pfInternalHandling()->ucMatrixRowLightBitPrv != 0U))
    {
      CtrlLed_pfInternalHandling()->sRowMtxErr[ucRow].boErrPresent[CTRLLED_SEL_PIXEL_DEFECT] = TRUE;
      boErrStatus = (asReactionPxl_List[CTRLLED_SEL_PIXEL_DEFECT] == CTRLLED_SWITCH_OFF) ? TRUE : FALSE;
      CtrlLed_pfInternalHandling()->sRowMtxErr[ucRow].boRowErr_Act |= TRUE;
    }

    if (uLuMtxErr[ucLmmPxl].bErr.bCoruptComm != 0U)
    {
      CtrlLed_pfInternalHandling()->sRowMtxErr[ucRow].boErrPresent[CTRLLED_SEL_CORUPT_COM] = TRUE;
      boErrStatus = (asReactionPxl_List[CTRLLED_SEL_CORUPT_COM] == CTRLLED_SWITCH_OFF) ? TRUE : FALSE;
      CtrlLed_pfInternalHandling()->sRowMtxErr[ucRow].boRowErr_Act |= TRUE;
    }

    if (uLuMtxErr[ucLmmPxl].bErr.bLossComm != 0U)
    {
      CtrlLed_pfInternalHandling()->sRowMtxErr[ucRow].boErrPresent[CTRLLED_SEL_LOSS_COM] = TRUE;
      boErrStatus = (asReactionPxl_List[CTRLLED_SEL_LOSS_COM] == CTRLLED_SWITCH_OFF) ? TRUE : FALSE;
      CtrlLed_pfInternalHandling()->sRowMtxErr[ucRow].boRowErr_Act |= TRUE;
    }

    CtrlLed_pfInternalHandling()->sRowMtxErr[ucRow].ucIlluminantAssigned = ucIll;
  }

  return boErrStatus;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_HandleMatrixDtc
///
/// \descr  This function handles DTC set and reset for matrix errors
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlLed_HandleMatrixDtc(void)
{
  boolean boRowErrPrv[CTRLLED_MAX_MTX_COL_SEL] = { FALSE, FALSE, FALSE }, boRowErrAct[CTRLLED_MAX_MTX_COL_SEL] = { FALSE, FALSE, FALSE };
  uint8 ucIlValue = CTRLLED_CFG_UNKNOWN_UINT8_VALUE;
  uint8_fast ucRow = 0U;
  //set and reset DTC only if Matrix is ON
  if (CtrlLed_pfInternalHandling()->ucMatrixRowLightBit != 0U)
  {
    for (ucRow = 0U; ucRow < CTRLLED_MAX_MTX_COL_SEL; ucRow++)
    {
      boRowErrAct[ucRow] = CtrlLed_pfInternalHandling()->sRowMtxErr[ucRow].boRowErr_Act;
      boRowErrPrv[ucRow] = CtrlLed_pfInternalHandling()->sRowMtxErr[ucRow].boRowErr_Prv;
      ucIlValue = CtrlLed_pfInternalHandling()->sRowMtxErr[ucRow].ucIlluminantAssigned;
      //check if error row has been changed
      if (((boRowErrPrv[ucRow] != boRowErrAct[ucRow]) || (CtrlLed_pfInternalHandling()->ucMatrixRowLightBitPrv != CtrlLed_pfInternalHandling()->ucMatrixRowLightBit)) && (ucIlValue != CTRLLED_CFG_UNKNOWN_UINT8_VALUE))
      {
        const uint8 ucDtcState = ((boRowErrAct[ucRow] == FALSE) && (CtrlLed_pfInternalHandling()->ucMatrixRowLightBitPrv == 0U)) ? CTRLLED_RESETSET_DTC : (boRowErrAct[ucRow] != FALSE) ? CTRLLED_SET_DTC : CTRLLED_NO_DTC_ACTION;
        switch (ucDtcState)
        {
          //error inactive and before matrix was OFF
        case CTRLLED_RESETSET_DTC:
          CtrlLed_pfInternalHandling()->sRowMtxErr[ucRow].boRowErr_Prv = boRowErrAct[ucRow];
          //reset DTC
          CtrlLed_SetResetMtxDtc(FALSE, ucRow);
          break;
          //error active
        case CTRLLED_SET_DTC:
          CtrlLed_pfInternalHandling()->sRowMtxErr[ucRow].boRowErr_Prv = boRowErrAct[ucRow];
          //set DTC
          CtrlLed_SetResetMtxDtc(TRUE, ucRow);
          break;
        default:
          break;
        }

        CtrlLed_pfInternalHandling()->uIlluminantError[ucIlValue].bIlErr.bMtxPD = CtrlLed_pfInternalHandling()->sRowMtxErr[ucRow].boErrPresent[0];
        CtrlLed_pfInternalHandling()->uIlluminantError[ucIlValue].bIlErr.bMtxCC = CtrlLed_pfInternalHandling()->sRowMtxErr[ucRow].boErrPresent[1];
        CtrlLed_pfInternalHandling()->uIlluminantError[ucIlValue].bIlErr.bMtxLC = CtrlLed_pfInternalHandling()->sRowMtxErr[ucRow].boErrPresent[2];
      }
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_SetResetMtxDtc
///
/// \descr  
///
/// \param   boDtcStatus, ucRow
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlLed_SetResetMtxDtc(boolean boDtcStatus, uint8_fast ucRow)
{
  uint8_fast ucErr = 0U;

  for (ucErr = 0U; ucErr < CTRLLED_SEL_MAX_PXL_ERR; ucErr++)
  {
    const uint8 ucLocMatrixRowLight = CtrlLed_pfInternalHandling()->ucMatrixRowLightBit;
    const boolean boErrPresent = CtrlLed_pfInternalHandling()->sRowMtxErr[ucRow].boErrPresent[ucErr];

    if((boErrPresent != FALSE) && (CTRLLED_CHECK_BIT_U16((uint16)ucLocMatrixRowLight, CTRLLED_MTX_ROW_TOP) != FALSE))
    {
      if (boDtcStatus != FALSE) //set dtc
      {
        CtrlLed_SetMtxDtc(ucRow, ucErr, TRUE);
      }
      else
      {
        CtrlLed_ResetMtxDtc(ucRow, ucErr);
      }
    }
    else if ((boErrPresent != FALSE) && (CTRLLED_CHECK_BIT_U16((uint16)ucLocMatrixRowLight, CTRLLED_MTX_ROW_MID) != FALSE) || (CTRLLED_CHECK_BIT_U16((uint16)ucLocMatrixRowLight, CTRLLED_MTX_ROW_BTM) != FALSE))
    {
      if (boDtcStatus != FALSE)
      {
        CtrlLed_SetMtxDtc(ucRow, ucErr, FALSE);
      }
      else
      {
        CtrlLed_ResetMtxDtc(ucRow, ucErr);
      }
    }
    else
    {

    }
  }
}

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_SetMtxDtc
///
/// \descr  
///
/// \param   ucRow, ucErr, boHbStatus
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlLed_SetMtxDtc(uint8_fast ucRow, uint8_fast ucErr, boolean boHbStatus)
{
  tsCtrlLed_DtcMtxHbLbList * pDtcList;
  pDtcList = asMtx_DTC_List;

  switch (ucRow)
  {
  case CTRLLED_MTX_ROW_MID: //kink
    Rte_Call_DemPrj_ReportErrorStatus(pDtcList[ucRow].unDTC[ucErr], DEM_EVENT_STATUS_FAILED);
    if (boHbStatus != FALSE)
    {
      Rte_Call_DemPrj_ReportErrorStatus(pDtcList[ucRow + 1U].unDTC[ucErr], DEM_EVENT_STATUS_FAILED);
    }
    break;
  default:
    Rte_Call_DemPrj_ReportErrorStatus(pDtcList[ucRow].unDTC[ucErr], DEM_EVENT_STATUS_FAILED);
    break;
  }
}

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_ResetMtxDtc
///
/// \descr  
///
/// \param   ucRow, ucErr
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlLed_ResetMtxDtc(uint8_fast ucRow, uint8_fast ucErr)
{
  tsCtrlLed_DtcMtxHbLbList * pDtcList;
  pDtcList = asMtx_DTC_List;
  switch (ucRow)
  {
  case CTRLLED_MTX_ROW_MID: //kink
    Rte_Call_DemPrj_ReportErrorStatus(pDtcList[ucRow].unDTC[ucErr], DEM_EVENT_STATUS_PASSED);
    CtrlLed_pfInternalHandling()->sRowMtxErr[ucRow].boErrPresent[ucErr] = FALSE;
    Rte_Call_DemPrj_ReportErrorStatus(pDtcList[ucRow + 1U].unDTC[ucErr], DEM_EVENT_STATUS_PASSED);
    CtrlLed_pfInternalHandling()->sRowMtxErr[ucRow + 1U].boErrPresent[ucErr] = FALSE;
    break;
  default:
    Rte_Call_DemPrj_ReportErrorStatus(pDtcList[ucRow].unDTC[ucErr], DEM_EVENT_STATUS_PASSED);
    CtrlLed_pfInternalHandling()->sRowMtxErr[ucRow].boErrPresent[ucErr] = FALSE;
    break;
  }
}
#endif

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_Diag_ChReacAtMtxErr
///
/// \descr   this function return TRUE when Matrix error appear except pixel defect
///
/// \param   ucIl
///
/// \return reaction (TRUE - switch off the coresponding channel)
//-----------------------------------------------------------------------------
STATIC_AL boolean CtrlLed_Diag_ChReacBuckErr(uint8_fast ucIl, uint8_fast ucCh, boolean boNewLightReq, uint8 ucErr)
{
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
  static boolean boSwitchOffBuck[CTRLLED_CFG_MAX_BUCK_DRV] = { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
  static boolean aboDiagChannelStates[CTRLLED_CFG_MAX_BUCK_DRV] = { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };

#else
  static boolean boSwitchOffBuck[CTRLLED_CFG_MAX_BUCK_DRV] = { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
  static uint8 aboDiagChannelStates[CTRLLED_CFG_MAX_BUCK_DRV] = { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
#endif
  if (boSwitchOffBuck[ucCh] == FALSE) //the reaction is not validated yet
  {
    
    if ((ucErr > CTRLLED_DIAG_STATUS_OK) && (ucErr < CTRLLED_DIAG_MAX_CNT))
    {
      const uint8 ucChFctName = CtrlLed_GetAndCheckLedName(ucCh, ucIl);
      if (asReaction_List[ucChFctName].ucReaction[ucErr - CTRLLED_DIAG_START_ERR_CNT] == CTRLLED_SWITCH_OFF)
      {
        boSwitchOffBuck[ucCh] = TRUE;
      }
      else
      {
        boSwitchOffBuck[ucCh] = FALSE;
      }
      aboDiagChannelStates[ucCh] = TRUE;
    }
    else
    {
      aboDiagChannelStates[ucCh] = FALSE;
    }
  }

  if (boNewLightReq != FALSE)
  {
    boSwitchOffBuck[ucCh] = FALSE;
  }

  CTRLLED_RTE_SE_CH_STS(ucCh, aboDiagChannelStates[ucCh]);

  return boSwitchOffBuck[ucCh];
}

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_HandleChDtc
///
/// \descr   this function handle the DTCs for LED channels based on error received
///
/// \param   ucChannel, ucErr
///
/// \return reaction _TRUE (switch off)
//-----------------------------------------------------------------------------
STATIC_AL void CtrlLed_HandleChannelErrors(uint8_fast ucIl, uint8_fast ucChannel, uint8 ucErr, boolean boNewReq)
{ 
  //store errors
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
  static uint16 unHbIllErrPrv = 0U;
  static uint16 unHbIllErr = 0U;
  static uint16 aunChannelError[CTRLLED_CFG_MAX_BUCK_DRV] = { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
  static uint16 aunChannelError_Prv[CTRLLED_CFG_MAX_BUCK_DRV] = { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
#else
  //without HSS3
  static uint16 aunChannelError[CTRLLED_CFG_MAX_BUCK_DRV] = { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
  static uint16 aunChannelError_Prv[CTRLLED_CFG_MAX_BUCK_DRV] = { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
#endif
  //store reaction channel
  aunChannelError[ucChannel] = ((ucErr > CTRLLED_DIAG_STATUS_OK) && (ucErr < CTRLLED_DIAG_MAX_CNT)) ?
  /*set error*/(uint16)((uint16)(1U) << (uint16)((uint16)ucErr - CTRLLED_DIAG_START_ERR_CNT)) :
  ((aunChannelError[ucChannel] != 0U) && (boNewReq != FALSE)) ?
  /*reset error*/ 0U :
  /*do nothing*/ aunChannelError[ucChannel];

  const uint8 ucDtcState = (aunChannelError[ucChannel] == aunChannelError_Prv[ucChannel]) ? CTRLLED_NO_DTC_ACTION :
    ((aunChannelError[ucChannel] != aunChannelError_Prv[ucChannel]) && (ucErr == CTRLLED_DIAG_STATUS_OK)) ? CTRLLED_RESETSET_DTC : CTRLLED_SET_DTC;

  if ((ucDtcState != CTRLLED_NO_DTC_ACTION) && (ucDtcState > 0U))
  {
#if defined UNIT_TEST
    /* -------------------------------------------------- --------------------------------------------*/
    /* Special UT instrumentation to force channel errors reset for double-check of invalid condition */
    /* ---------------------------------------------------------------------------------------------- */
    CtrlLed_Special_UT_Instrumentation_Force_ResetVars(&ucDtcState, &ucErr);
#endif
    //1 -->set dtc, 2 -->reset dtc
    if ( ((ucDtcState == CTRLLED_SET_DTC) && (ucErr == CTRLLED_DIAG_STATUS_OK)) || ((ucDtcState == CTRLLED_RESETSET_DTC) && (ucErr != CTRLLED_DIAG_STATUS_OK)) )
    {
      //proof of work -> program should not be here
      //reset vars
      aunChannelError[ucChannel] = 0U;
      aunChannelError_Prv[ucChannel] = 0U;
    }
    else
    {
      CtrlLed_ReportDtc(ucDtcState, aunChannelError_Prv, ucIl, ucChannel, aunChannelError);
    }
  }
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
  //customer request, in case the kink illuminant has a problem and the light distribution has been changed from LB to HB, set the dtc also for HB illuminant
  //should follow the DIAG feedback (LB kink Illuminant = ERR => HB Illuminant = ERR for HB request)
  else if((ucIl == CTRLLED_ILLUMINANT_HB) && ((CTRLLED_CHECK_BIT_U16((uint16)CtrlLed_pfInternalHandling()->ucMatrixRowLightBit, CTRLLED_MTX_ROW_TOP) != FALSE)))
  {
    const uint16 unKinkIllErr = (CtrlLed_pfInternalHandling()->uIlluminantError[CTRLLED_ILLUMINANT_KINK].unRaw & 0x3FFU);
    //no error on hb illuminant and kink has an error
    if((unHbIllErr == 0U) && (unKinkIllErr != 0U))
    {
      const uint8 ucErrIdx = CtrlLed_Diag_CountErrorBitPos(unKinkIllErr);
      //put the same DTC as for KINK illuminant
      CtrlLed_Diag_SetChannelDtc(CTRLLED_CH_NAME_PXL_HB, ucErrIdx);
    }
    //store HB error
    unHbIllErr = (unKinkIllErr | (CtrlLed_pfInternalHandling()->uIlluminantError[CTRLLED_ILLUMINANT_KINK].unRaw & 0x3FFU));
  }
#endif
  else
  {
    //do nothing
  }

  aunChannelError_Prv[ucChannel] = aunChannelError[ucChannel];
}

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_ReportChReactionAndDtc
///
/// \descr   this function set or reset the DTCs for LED channels
///
/// \param    
///
/// \return ucReaction
//-----------------------------------------------------------------------------
STATIC_AL void CtrlLed_ReportDtc(uint8 ucDtcState, uint16 *punPrvCh, uint8_fast ucIl, uint8_fast ucCh, uint16 *punActCh)
{
  uint8 ucErrIdx = CTRLLED_CFG_UNKNOWN_UINT8_VALUE;
  //store channel name from coding
  const uint8 ucChFctName = CtrlLed_GetAndCheckLedName(ucCh, ucIl);
  //unknown led channel name
  if (ucChFctName != CTRLLED_CFG_UNKNOWN_UINT8_VALUE)
  {
    if (ucDtcState == CTRLLED_SET_DTC)
    {
      ucErrIdx = CtrlLed_Diag_CountErrorBitPos(punActCh[ucCh]);
      if (ucErrIdx != CTRLLED_CFG_UNKNOWN_UINT8_VALUE)
      {
        CtrlLed_pfInternalHandling()->uIlluminantError[ucIl].unRaw |= (uint16)((uint16)1U << (uint16)(ucErrIdx));
        CtrlLed_Diag_SetChannelDtc(ucChFctName, ucErrIdx);
      }
      
      if (punPrvCh[ucCh] != 0U)
      {
        CtrlLed_Diag_ResetDtc(ucChFctName, punPrvCh, ucIl, ucCh);
      }
    }
    else
    {
      CtrlLed_Diag_ResetDtc(ucChFctName, punPrvCh, ucIl, ucCh);
    }
  }

}

//-----------------------------------------------------------------------------
/// \brief   CtrlLed_Diag_CountErrorBitPos
///
/// \descr
///
/// \param  punActCh
/// \param  ucCh
///
/// \return STATIC_AL uint8
//-----------------------------------------------------------------------------
STATIC_AL uint8 CtrlLed_Diag_CountErrorBitPos(uint16 unVal)
{
  uint8 ucCount = 0U;
  uint8 ucBitPos = 0U;
  uint16 unMask = 0U;
  if (unVal != 0U)
  {
    while (ucBitPos <= CTRLLED_DIAG_MAX_ERR_USED)
    {
      unMask = (uint16)((uint16)1U << (uint16)ucBitPos);
      //check for error bit detection
      if ((unVal & unMask) != 0U) //only one error
      {
        ucCount = ucBitPos;
        break;
      }
      ucBitPos++;
    }
  }
  else
  {
    ucCount = CTRLLED_CFG_UNKNOWN_UINT8_VALUE;
  }

  return ucCount;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_Diag_SetChannelDtc
///
/// \descr   
///
/// \param   ucChannelName, *punPrvCh, ucCh
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlLed_Diag_SetChannelDtc(uint8 ucChannelName, uint8 ucErr)
{
  //set DTC
  if (asDTC_List[ucChannelName].unDTC[ucErr] != CTRLLED_DTC_NOT_USED)
  {
    Rte_Call_DemPrj_ReportErrorStatus(asDTC_List[ucChannelName].unDTC[ucErr], DEM_EVENT_STATUS_FAILED);
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
    //channel name is pixel and kink illuminant have a problem and high beam was requested
    if ((ucChannelName == CTRLLED_CH_NAME_PXL_LB) && (CtrlLed_pfInternalHandling()->uIlluminantError[CTRLLED_ILLUMINANT_KINK].unRaw != 0U) && ((CTRLLED_CHECK_BIT_U16((uint16)CtrlLed_pfInternalHandling()->ucMatrixRowLightBit, CTRLLED_MTX_ROW_TOP) != FALSE)))
    {
      Rte_Call_DemPrj_ReportErrorStatus(asDTC_List[CTRLLED_CH_NAME_PXL_HB].unDTC[ucErr], DEM_EVENT_STATUS_FAILED);
    }
#endif
  }
}

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_Diag_ResetDtc
///
/// \descr   
///
/// \param   ucChannelName, *punPrvCh, ucIl, ucCh
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlLed_Diag_ResetDtc(uint8 ucChannelName, uint16 *punPrvCh, uint8_fast ucIl, uint8_fast ucCh)
{
  uint8_fast ucErr = 0U;
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
  boolean boKinkErr = FALSE;
#endif
  for (ucErr = 0U; ucErr < CTRLLED_DIAG_MAX_ERR_USED; ucErr++)
  {
    //reset the coresponding DTC
    if (((punPrvCh[ucCh] & ((uint16)((uint16)1U << (uint16)ucErr))) != 0U) && (asDTC_List[ucChannelName].unDTC[ucErr] != CTRLLED_DTC_NOT_USED))
    {
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
      boKinkErr = (((CtrlLed_pfInternalHandling()->uIlluminantError[CTRLLED_ILLUMINANT_KINK].unRaw) & ((uint16)((uint16)(1U) << (uint16)(ucErr)))) != 0U) ? TRUE : boKinkErr;
#endif
      CtrlLed_pfInternalHandling()->uIlluminantError[ucIl].unRaw &= (uint16)(~(uint16)((uint16)(1U) << (uint16)(ucErr)));

      Rte_Call_DemPrj_ReportErrorStatus(asDTC_List[ucChannelName].unDTC[ucErr], DEM_EVENT_STATUS_PASSED);
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
      //restore dtc in case channel name is pixel and kink illuminant have a
      if ((ucChannelName == CTRLLED_CH_NAME_PXL_LB) && (boKinkErr != FALSE) && (asDTC_List[CTRLLED_CH_NAME_PXL_HB].unDTC[ucErr] != CTRLLED_DTC_NOT_USED))
      {
        CtrlLed_pfInternalHandling()->uIlluminantError[CTRLLED_ILLUMINANT_HB].unRaw &= (uint16)(~(uint16)((uint16)(1U) << (uint16)(ucErr)));
        Rte_Call_DemPrj_ReportErrorStatus(asDTC_List[CTRLLED_CH_NAME_PXL_HB].unDTC[ucErr], DEM_EVENT_STATUS_PASSED);
      }
#endif
      break;
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_Diag_DisableError_Cmd
///
/// \descr   
///
/// \param   ucIdx, boVinStatus, unCurrent
///
/// \return tsCtrlLed_ChannelSettings
//-----------------------------------------------------------------------------
STATIC_AL tsCtrlLed_ChannelSettings CtrlLed_Diag_DisableError_Cmd(uint8_fast ucIdx, CONST_AL boolean boVinStatus, uint16 unCurrent)
{
  const  uint16                    unVolt_mV           = CTRLLED_RTE_RE_VOLT_MV
  const  boolean                   boLedDiagEnabled    = (unVolt_mV > CTRLLED_DIAG_SKIP_UNDER_x_mV) ? TRUE : FALSE;
  const  boolean                   boLedDeratingActive = (unCurrent != 0u) ? CTRLLED_DIAG_DERATING_STATUS(unCurrent, Cod_LedBinningCurrent(ucIdx)) : FALSE;
  //cannot be set for MATRIX channel                    
  const  boolean                   boLedMlcConnected   = (Cod_LedChannelType(ucIdx) == CTRLLED_CFG_MATRIX_BUCK) ? TRUE : FALSE;
  static tsCtrlLed_ChannelSettings sCtrlLed_ChannelSettings;

  sCtrlLed_ChannelSettings.ulDisable_ErrE2E             = 0u;

  sCtrlLed_ChannelSettings.ulDisable_ErrOpenLoad        = ((boLedDiagEnabled == FALSE) || (boVinStatus == FALSE)) ?\
                                                          (sCtrlLed_ChannelSettings.ulDisable_ErrOpenLoad | ((uint32)((uint32)1u << (uint32)ucIdx))) : (sCtrlLed_ChannelSettings.ulDisable_ErrOpenLoad & ((uint32)(~((uint32)1u << (uint32)ucIdx))));
                                    
  sCtrlLed_ChannelSettings.ulDisable_ErrOverCurrent     = 0u;
                                   
  sCtrlLed_ChannelSettings.ulDisable_ErrShortToGnd      = ((boLedDiagEnabled == FALSE) || (boLedDeratingActive != FALSE) || (boLedMlcConnected != FALSE)) ? \
                                                          (sCtrlLed_ChannelSettings.ulDisable_ErrShortToGnd | ((uint32)((uint32)1u << (uint32)ucIdx))) : (sCtrlLed_ChannelSettings.ulDisable_ErrShortToGnd & ((uint32)(~((uint32)1u << (uint32)ucIdx))));
                                    
  sCtrlLed_ChannelSettings.ulDisable_ErrShortToUbat     = (boLedDiagEnabled == FALSE) ?\
                                                          (sCtrlLed_ChannelSettings.ulDisable_ErrShortToUbat | ((uint32)((uint32)1u << (uint32)ucIdx))) : (sCtrlLed_ChannelSettings.ulDisable_ErrShortToUbat & ((uint32)(~((uint32)1u << (uint32)ucIdx))));
                                    
  sCtrlLed_ChannelSettings.ulDisable_ErrSpi             = 0u;
                                   
  sCtrlLed_ChannelSettings.ulDisable_ErrThermalShutdown = 0u;
                                    
  sCtrlLed_ChannelSettings.ulDisable_ErrUnderVoltage    = ((boLedDiagEnabled == FALSE) || (boLedDeratingActive != FALSE) || (boLedMlcConnected != FALSE)) ? \
                                                          (sCtrlLed_ChannelSettings.ulDisable_ErrUnderVoltage | ((uint32)((uint32)1u << (uint32)ucIdx))) : (sCtrlLed_ChannelSettings.ulDisable_ErrUnderVoltage & ((uint32)(~((uint32)1u << (uint32)ucIdx))));
  
  sCtrlLed_ChannelSettings.ulDisable_ErrOverVoltage     = 0xFFFU;

  //return disable error settings
  return sCtrlLed_ChannelSettings;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_GetHss3DiagStatus
///
/// \descr   
///
/// \param  *pucData
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlLed_GetHss3DiagStatus(uint8 *pucData)
{
  uint8 ucHssErr;
  boolean boEnabled;
  CTRLLED_RTE_RE_HSS3_STATUS(&ucHssErr, &boEnabled)
  switch (ucHssErr)
  {
  case 0U:
    *pucData = CTRLLED_DIAG_ERR_OPEN_LOAD;
    break;
  case 1U:
    *pucData = CTRLLED_DIAG_ERR_SHORT_TO_BAT;
    break;
  case 2U:
    *pucData = CTRLLED_DIAG_ERR_SHORT_TO_GND; 
    break;
  default:
    *pucData = (boEnabled != FALSE) ? CTRLLED_DIAG_STATUS_OK : CTRLLED_DIAG_STATUS_LED_OFF;
    break;
  }
}

#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
//-----------------------------------------------------------------------------
/// \brief  CtrlLed_Diag_Check_MtxVccx_Eeprom_Fault
///
/// \descr  This function checks each type of matrix error and sets/resets the fault
///         on the corresponding error bit position
///
/// \param  boVccxGnd       : Vccx Short to Gnd fault
/// \param  boVccxBat       : Vccx Short to Vbat fault
/// \param  sMtxEeprom_ErrStatus : eeprom checkum or no access fault
///
/// \return STATIC_AL uint8
//-----------------------------------------------------------------------------
STATIC_AL uint8 CtrlLed_Diag_Check_MtxVccx_Eeprom_Fault(boolean boVccxGnd, boolean boVccxBat, tsRte_MtxEeprom_ErrStatus sMtxEeprom_ErrStatus)
{
  //store the matrix error on bit position
  uint8 ucStoreVccxEEprom_Bit;

  if (boVccxGnd != FALSE)
  {
    ucStoreVccxEEprom_Bit |= (uint8)(1u << CTRLLED_DIAG_MTX_VCCx_GND_BIT_POS);
  }
  else
  {
    ucStoreVccxEEprom_Bit &= (uint8)(~((uint8)(1u << CTRLLED_DIAG_MTX_VCCx_GND_BIT_POS)));
  }

  if (boVccxBat != FALSE)
  {
    ucStoreVccxEEprom_Bit |= (uint8)(1u << CTRLLED_DIAG_MTX_VCCx_BAT_BIT_POS);
  }
  else
  {
    ucStoreVccxEEprom_Bit &= (uint8)(~(uint8)(1u << CTRLLED_DIAG_MTX_VCCx_BAT_BIT_POS));
  }

  if (sMtxEeprom_ErrStatus.boEepromWrngChksumFault != FALSE)
  {
    ucStoreVccxEEprom_Bit |= (uint8)(1u << CTRLLED_DIAG_MTX_EEEPROM_CHKSUM_BIT_POS);
  }
  else
  {
    ucStoreVccxEEprom_Bit &= (uint8)(~(uint8)(1u << CTRLLED_DIAG_MTX_EEEPROM_CHKSUM_BIT_POS));
  }

  if (sMtxEeprom_ErrStatus.boEepromNoAccessFault != FALSE)
  {
    ucStoreVccxEEprom_Bit |= (uint8)(1u << CTRLLED_DIAG_MTX_EEEPROM_NOACCESS_BIT_POS);
  }
  else
  {
    ucStoreVccxEEprom_Bit &= (uint8)(~(uint8)(1u << CTRLLED_DIAG_MTX_EEEPROM_NOACCESS_BIT_POS));
  }

  return ucStoreVccxEEprom_Bit;
}


//-----------------------------------------------------------------------------
/// \brief  CtrlLed_Diag_MtxErrorHandler
///
/// \descr   
///
/// \param   void
///
/// \return  boolean
//-----------------------------------------------------------------------------
boolean CtrlLed_Diag_MtxVccx_Eeprom(void)
{
  tsRte_MtxEeprom_ErrStatus sMtxEeprom_ErrStatus;
  boolean boVccxGnd_Fault      = FALSE;
  boolean boVccxBat_Fault      = FALSE;
  boolean boMtxEepromErrStatus = FALSE;
  boolean boRetVccxErrStatus   = FALSE;
  uint8_fast ucIdxIl;
  uint8   ucStoreVccxEEprom_Bit = 0x0u;            /*  1st pos :VccxGnd | VccxBat | EepromWrngChksum | EepromNoAccess */
  static uint8 ucStoreVccxEEprom_Prv_Bit = 0x0u;   /*  1st pos :VccxGnd | VccxBat | EepromWrngChksum | EepromNoAccess */

  // get matrix supply error status
  CTRLLED_RTE_RE_GET_VCCX_MTX_ERR(&boVccxGnd_Fault, &boVccxBat_Fault)

  //get matrix eeprom error status
  CTRLLED_RTE_RE_GET_MTX_EEPROM_ERR(&sMtxEeprom_ErrStatus)

  //store eeprom error status
  boMtxEepromErrStatus = ((sMtxEeprom_ErrStatus.boEepromWrngChksumFault != FALSE) || (sMtxEeprom_ErrStatus.boEepromNoAccessFault != FALSE)) ? TRUE : FALSE;
 
  //check each type of error (function needed to check each error to avoid MISRA warnings)
  ucStoreVccxEEprom_Bit =  CtrlLed_Diag_Check_MtxVccx_Eeprom_Fault(boVccxGnd_Fault, boVccxBat_Fault, sMtxEeprom_ErrStatus);

  //check if error has changed 
 if (ucStoreVccxEEprom_Prv_Bit != ucStoreVccxEEprom_Bit)
 {
   boRetVccxErrStatus = ((boVccxGnd_Fault != FALSE) || (boVccxBat_Fault != FALSE)) ? TRUE : FALSE;
    for (ucIdxIl = 0u; ucIdxIl < CTRLLED_CFG_NO_ILLUMINANTS; ucIdxIl++)
    {

      if (CtrlLed_pfCodingData()->aboIlMtxType[ucIdxIl] != FALSE)
      {
        /* set/reset error/DTC for matrix supply */
        CtrlLed_pfInternalHandling()->uIlluminantError[ucIdxIl].bIlErr.bMtxVccXSG = (boVccxGnd_Fault != FALSE) ? 1U : 0U;
        Rte_Call_DemPrj_ReportErrorStatus((uint16)VCCX2_SC_GND, (boVccxGnd_Fault != FALSE) ? DEM_EVENT_STATUS_FAILED : DEM_EVENT_STATUS_PASSED);
        CtrlLed_pfInternalHandling()->uIlluminantError[ucIdxIl].bIlErr.bMtxVccXSB = (boVccxBat_Fault != FALSE) ? 1U : 0U;
        Rte_Call_DemPrj_ReportErrorStatus((uint16)VCCX2_SC_BAT, (boVccxBat_Fault != FALSE) ? DEM_EVENT_STATUS_FAILED : DEM_EVENT_STATUS_PASSED);

        /* set/reset error/DTC for matrix eeprom access */
        CtrlLed_pfInternalHandling()->uIlluminantError[ucIdxIl].bIlErr.bMtxEeprom = (boMtxEepromErrStatus != FALSE) ? 1U : 0U;
        Rte_Call_DemPrj_ReportErrorStatus((uint16)LMM_SatEEPROM_WRNG_CHKSUM, (sMtxEeprom_ErrStatus.boEepromWrngChksumFault != FALSE) ? DEM_EVENT_STATUS_FAILED : DEM_EVENT_STATUS_PASSED);
        Rte_Call_DemPrj_ReportErrorStatus((uint16)LMM_SatEEPROM_NO_ACC,      (sMtxEeprom_ErrStatus.boEepromNoAccessFault != FALSE)   ? DEM_EVENT_STATUS_FAILED : DEM_EVENT_STATUS_PASSED);
      }
    }
  }
  
  ucStoreVccxEEprom_Prv_Bit = ucStoreVccxEEprom_Bit;

  return boRetVccxErrStatus;
}

#endif //if defined FULL Variant





#ifdef UNIT_TEST
//-----------------------------------------------------------------------------
/// \brief  CtrlLed_Special_UT_Instrumentation_Force_ResetVars
///
/// \descr  Special UT instrumentation handler (simulates uninitialized coding)
///
/// \param  pucDtcAction : DTC action
/// \param  pucErrStatus : diag Led error
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlLed_Special_UT_Instrumentation_Force_ResetVars(uint8* pucDtcAction, uint8* pucErrStatus)
{
  STATIC_UT(uint8, CtrlLed_ForceReset, 0x00u);

  if (CtrlLed_ForceReset == 0xAAu)
  {
    *pucDtcAction = CTRLLED_SET_DTC;
    *pucErrStatus = CTRLLED_DIAG_STATUS_OK;
  }
  else if (CtrlLed_ForceReset == 0x55u)
  {
    *pucDtcAction = CTRLLED_RESETSET_DTC;
    *pucErrStatus = CTRLLED_DIAG_ERR_BOOST;
  }
  else
  {
    // skip the UT instrumentation
  }

}
#endif

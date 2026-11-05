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
/// \file   CddSwi_Router.c
///
/// \brief  Specific code for Cdd Switch Router
///
/// \author Adrian Horlescu (F31197D)
///         mailTo:adrian-marian.horlescu[at]marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// Includes
//=============================================================================

#include <Std_Types.h>
#include <Cfg/Cfg.h>
#include <CddSwi.h>
#include <CddSwi_Cfg.h>
#include <CddSwi_Types.h>
#include <CddSwi_Router.h>
#include <CddVn7140.h>
#include <IoHwAbUser.h>


#ifndef UNIT_TEST
#include <Rte.h>
#include <CddSbc.h>
#endif


#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
#include <CddVnd7140.h>
#endif

//=============================================================================
// Defines and Typedef
//=============================================================================

//=============================================================================
// Global variables
//=============================================================================

CONST_AL  tNvmPara_CodingArea*  CddSwi_pCodingArea;
STATIC_AL boolean               CddSwi_boCodingValid;

//=============================================================================
//  Static variable declarations
//=============================================================================
STATIC_AL CONST_AL tsCddSwi_Router CddSwi_asRouteList[CDDSWI_CFG_SWI_CNT] = CDDSWI_CFG_ROUTE_LIST;

//=============================================================================
// Function prototypes
//=============================================================================

//=============================================================================
// Macros
//=============================================================================

//=============================================================================
// interface functions
//=============================================================================

#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
uint16  Cod_HSS1Shor2GndThr(void) { return CddSwi_pCodingArea->Fan1.HSS_DIAG.HSS1_SHORT_TO_GND_THRESHOLD; }
uint16  Cod_HSS1Shor2VbatThr(void) { return CddSwi_pCodingArea->Fan1.HSS_DIAG.HSS1_SHORT_TO_UBAT_THRESHOLD; }
uint16  Cod_HSS1OpenLoadThr(void) { return CddSwi_pCodingArea->Fan1.HSS_DIAG.HSS1_OPEN_LOAD_THRESHOLD; }
uint16  Cod_HSS2Shor2GndThr(void) { return CddSwi_pCodingArea->Fan1.HSS_DIAG.HSS2_SHORT_TO_GND_THRESHOLD; }
uint16  Cod_HSS2Shor2VbatThr(void) { return CddSwi_pCodingArea->Fan1.HSS_DIAG.HSS2_SHORT_TO_UBAT_THRESHOLD; }
uint16  Cod_HSS2OpenLoadThr(void) { return CddSwi_pCodingArea->Fan1.HSS_DIAG.HSS2_OPEN_LOAD_THRESHOLD; }
uint16  Cod_HSS3Shor2GndThr(void) { return CddSwi_pCodingArea->Fan1.HSS_DIAG.HSS3_SHORT_TO_GND_THRESHOLD; }
uint16  Cod_HSS3Shor2VbatThr(void) { return CddSwi_pCodingArea->Fan1.HSS_DIAG.HSS3_SHORT_TO_UBAT_THRESHOLD; }
uint16  Cod_HSS3OpenLoadThr(void) { return CddSwi_pCodingArea->Fan1.HSS_DIAG.HSS3_OPEN_LOAD_THRESHOLD; }
#elif defined (CFG_VARIANT_ECO)
uint16  Cod_HSS3Shor2GndThr(void) { return (CddSwi_pCodingArea->Fan1.Fans_Presence.ucFan1Enabled != 0u) ? CddSwi_pCodingArea->Fan1.HSS_DIAG.HSS1_SHORT_TO_GND_THRESHOLD : (CddSwi_pCodingArea->Led1.LedConfigDRV13.FUSA_DRV13_NAME != 0u) ? CddSwi_pCodingArea->Fan1.HSS_DIAG.HSS3_SHORT_TO_GND_THRESHOLD : 0u; }
uint16  Cod_HSS3Shor2VbatThr(void) { return (CddSwi_pCodingArea->Fan1.Fans_Presence.ucFan1Enabled != 0u) ? CddSwi_pCodingArea->Fan1.HSS_DIAG.HSS1_SHORT_TO_UBAT_THRESHOLD : (CddSwi_pCodingArea->Led1.LedConfigDRV13.FUSA_DRV13_NAME != 0u) ? CddSwi_pCodingArea->Fan1.HSS_DIAG.HSS3_SHORT_TO_UBAT_THRESHOLD : 0u; }
uint16  Cod_HSS3OpenLoadThr(void) { return (CddSwi_pCodingArea->Fan1.Fans_Presence.ucFan1Enabled != 0u) ? CddSwi_pCodingArea->Fan1.HSS_DIAG.HSS1_OPEN_LOAD_THRESHOLD : (CddSwi_pCodingArea->Led1.LedConfigDRV13.FUSA_DRV13_NAME != 0u) ? CddSwi_pCodingArea->Fan1.HSS_DIAG.HSS3_OPEN_LOAD_THRESHOLD : 0u; }
#endif
boolean Cod_DiagValid(void) { return CddSwi_boCodingValid; }
uint8   Cod_HSS3Min_Pwm(void) { return CddSwi_pCodingArea->Fan1.HSS_DIAG.HSS3_MIN_PWM; }

//=============================================================================
// Function definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  CddSwi_Init
///
/// \descr  intialisation
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddSwi_Rou_Init(void)
{
  tScrollingPresent_Stat  tLssDiagStatus;

  // Maps the coding parameters to CddSwi
  (void)CddSwi_Rou_MapParams();

#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
  for (uint8_least ucIx = 0u; ucIx < CDDSWI_CFG_VND7140_CNT; ucIx++)
  {
    CddVnd7140_Init(ucIx);
  }
#endif

  for (uint8_least ucIx = 0u; ucIx < CDDSWI_CFG_VN7140_CNT; ucIx++)
  {
    CddVn7140_Init(ucIx);
  }

#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
  tLssDiagStatus = CddSwi_Rou_CheckScrollingSatellite_Status();
  (void)Rte_Write_CddSwi_ScrollingOn_Stat(&tLssDiagStatus);
#endif

}

//-----------------------------------------------------------------------------
/// \brief  CddSwi_Rou_Cycle0
///
/// \descr  cyclic behaviour
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddSwi_Rou_Cycle0(void)
{
#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
  for (uint8_least ucIx = 0u; ucIx < CDDSWI_CFG_VND7140_CNT; ucIx++)
  {
    CddVnd7140_Cycle0();
  }
#endif

  for (uint8_least ucIx = 0u; ucIx < CDDSWI_CFG_VN7140_CNT; ucIx++)
  {
    CddVn7140_Cycle0();
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddSwi_Rou_SetTgt
///
/// \descr  set target value on HSS channel
///
/// \param  ulChnIdx - channel index
/// \param  unTgtVal - target value for HSS output
///
/// \return void
//-----------------------------------------------------------------------------
void CddSwi_Rou_SetTgt(CONST_AL uint32 ulChnIdx, CONST_AL uint16 unTgtVal)
{
#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
  uint16 unLssPwm_Tgt = 0u;
#endif
  switch (CddSwi_asRouteList[ulChnIdx].eDrvTyp)
  {
#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
  case eDrvVnd7140:
    CddVnd7140_SetTgt(CddSwi_asRouteList[ulChnIdx].ucDrvIdx, CddSwi_asRouteList[ulChnIdx].ucOutIdx, unTgtVal);
    break;
#endif
  case eDrvVn7140:
    CddVn7140_SetTgt(CddSwi_asRouteList[ulChnIdx].ucDrvIdx, CddSwi_asRouteList[ulChnIdx].ucOutIdx, unTgtVal);
    break;
#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
  case eDrvTle94x1:
    unLssPwm_Tgt = unTgtVal;
    (void)Rte_Write_CddSwi_SetLssPwm_Req(&unLssPwm_Tgt);
    break;
#endif

  default:
    break;
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddSwi_Rou_GetState
///
/// \descr  return switch state on channel
///
/// \param  ulChnIdx - channel index
///
/// \return tsCddSwi_SwitchStatus
//-----------------------------------------------------------------------------
tsCddSwi_SwitchStatus CddSwi_Rou_GetState(CONST_AL uint32 ulChnIdx)
{
  tsCddSwi_SwitchStatus  sSwitchStatus;

#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
  tsCddVnd7140_DrvStatus sCddVnd7140_CddDrvStatus;
  boolean boLss_Status[2u] = { FALSE, FALSE };
#endif
  tsCddVn7140_DrvStatus  sCddVn7140_CddDrvStatus;


  switch (CddSwi_asRouteList[ulChnIdx].eDrvTyp)
  {
#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
  case eDrvVnd7140:
    sCddVnd7140_CddDrvStatus = CddVnd7140_GetState(CddSwi_asRouteList[ulChnIdx].ucDrvIdx, CddSwi_asRouteList[ulChnIdx].ucOutIdx);
    sSwitchStatus.unHssActVal = sCddVnd7140_CddDrvStatus.unActVal;
    sSwitchStatus.unHssActCurrent = sCddVnd7140_CddDrvStatus.unActCurrent;
    sSwitchStatus.ucHssOpenLoad = sCddVnd7140_CddDrvStatus.ucErrOpenLoad;
    sSwitchStatus.ucHssShort2GND = sCddVnd7140_CddDrvStatus.ucErrShort2GND;
    sSwitchStatus.ucHssShort2VBAT = sCddVnd7140_CddDrvStatus.ucErrShort2VBAT;
    sSwitchStatus.ucHssHwState = sCddVnd7140_CddDrvStatus.ucHwState;
    break;
#endif
  case eDrvVn7140:
    sCddVn7140_CddDrvStatus = CddVn7140_GetState(CddSwi_asRouteList[ulChnIdx].ucDrvIdx, CddSwi_asRouteList[ulChnIdx].ucOutIdx);
    sSwitchStatus.unHssActVal = sCddVn7140_CddDrvStatus.unActVal;
    sSwitchStatus.unHssActCurrent = sCddVn7140_CddDrvStatus.unActCurrent;
    sSwitchStatus.ucHssOpenLoad = sCddVn7140_CddDrvStatus.ucErrOpenLoad;
    sSwitchStatus.ucHssShort2GND = sCddVn7140_CddDrvStatus.ucErrShort2GND;
    sSwitchStatus.ucHssShort2VBAT = sCddVn7140_CddDrvStatus.ucErrShort2VBAT;
    sSwitchStatus.ucHssHwState = sCddVn7140_CddDrvStatus.ucHwState;
    break;

#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
  case eDrvTle94x1:
    IoHwAbUser_GetOutFctDiag(&boLss_Status[0]);
    sSwitchStatus.unHssActVal = CddSbc_GetPWM(0u);
    sSwitchStatus.unHssActCurrent = 0xFFFFu;
    sSwitchStatus.ucHssOpenLoad = 0u;
    sSwitchStatus.ucHssShort2GND = boLss_Status[0];
    sSwitchStatus.ucHssShort2VBAT = boLss_Status[1];
    break;
#endif

  default:
    break;

  }

  return sSwitchStatus;
}

//-----------------------------------------------------------------------------
/// \brief  CddSwi_Rou_DeInit
///
/// \descr  deintialisation
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddSwi_Rou_DeInit(void)
{
#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
  for (uint8_least ucIx = 0u; ucIx < CDDSWI_CFG_VND7140_CNT; ucIx++)
  {
    CddVnd7140_DeInit(ucIx);
  }
#endif

  for (uint8_least ucIx = 0u; ucIx < CDDSWI_CFG_VN7140_CNT; ucIx++)
  {
    CddVn7140_DeInit(ucIx);
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddSwi_Rou_Read_Fan1ActivationState
///
/// \descr  Read fan state from Rte
///
/// \param  pData - buffer to store fan state
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType CddSwi_Rou_Read_Fan1_TgtVal(tCddSwi_TgtVal *pData)
{
  Std_ReturnType                     ucReturnValue;
  tRteSwitchTgtVal                   unFan1_TgtValue;

  //Read Fan 1 request
  ucReturnValue = Rte_Read_CtrlSwi_TgtValue_Fan1(&unFan1_TgtValue);

  *pData = unFan1_TgtValue;

  return ucReturnValue;
}

//-----------------------------------------------------------------------------
/// \brief  CddSwi_Rou_Read_RGB_SM_TgtVal
///
/// \descr  Read fan state from Rte
///
/// \param  pData - buffer to store RGB_SM state
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType CddSwi_Rou_Read_RGB_SM_TgtVal(tCddSwi_TgtVal *pData)
{
  Std_ReturnType                     ucReturnValue;
  tRteSwitchTgtVal                   unRgbSm_TgtValue;

  //Read RGB request
  ucReturnValue = Rte_Read_CtrlSwi_TgtValue_SMRGB(&unRgbSm_TgtValue);

  *pData = unRgbSm_TgtValue;

  return ucReturnValue;
}


#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
//-----------------------------------------------------------------------------
/// \brief  CddSwi_Rou_Read_Fan2ActivationState
///
/// \descr  Read fan state from Rte
///
/// \param  pData - buffer to store fan state
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType CddSwi_Rou_Read_Fan2_TgtVal(tCddSwi_TgtVal *pData)
{
  Std_ReturnType                     ucReturnValue;
  tRteSwitchTgtVal                   unFan2_TgtValue;

  //Read Fan 2 request
  ucReturnValue = Rte_Read_CtrlSwi_TgtValue_Fan2(&unFan2_TgtValue);

  *pData = unFan2_TgtValue;

  return ucReturnValue;
}


//-----------------------------------------------------------------------------
/// \brief  CddSwi_Rou_Read_Ti_PosDrl_Scrolling_TgtVal
///
/// \descr  Read Ti PosDrl Scrolling request from Rte
///
/// \param  pData - buffer to store Scrolling state
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType CddSwi_Rou_Read_Ti_PosDrl_Scrolling_TgtVal(uint16 *pData)
{
  Std_ReturnType                     ucReturnValue;
  teRte_SateliteStatus               eScrollingSatelite_TgtValue;
  uint16 unDataOut = 0u;

  //Read RGB request
  ucReturnValue = Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite(&eScrollingSatelite_TgtValue);

  switch (eScrollingSatelite_TgtValue)
  {
  case eRte_ScrollingSatelite_Off: unDataOut = 10000u; break;
  case eRte_eScrollingSatelite_On_Scrolling_Off: unDataOut = 5000u; break;
  case eRte_eScrollingSatelite_On_Scrolling_On: unDataOut = 0u; break;
  default: break;
  }

  *pData = unDataOut;

  return ucReturnValue;
}
#endif

//-----------------------------------------------------------------------------
/// \brief  CddSwi_Rou_Write_SwitchStatus
///
/// \descr  Write HSS State on Rte
///
/// \param  asState - array with HSS state
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType CddSwi_Rou_Write_SwitchStatus(tsCddSwi_SwitchStatus* asState)
{
  Std_ReturnType                     ucReturnValue;
  tsRte_HssStatus                    asSwitchStatus;

  for (uint8_least ucIdx = 0u; ucIdx < CDDSWI_CFG_OUTPUTS_CNT; ucIdx++)
  {
    asSwitchStatus.sSwitchStatus[ucIdx].ucHwState = asState[ucIdx].ucHssHwState;
    asSwitchStatus.sSwitchStatus[ucIdx].unActVal = asState[ucIdx].unHssActVal;
    asSwitchStatus.sSwitchStatus[ucIdx].unActCurrent = asState[ucIdx].unHssActCurrent;
    asSwitchStatus.sSwitchStatus[ucIdx].ucErrOpenLoad = asState[ucIdx].ucHssOpenLoad;
    asSwitchStatus.sSwitchStatus[ucIdx].ucErrShort2GND = asState[ucIdx].ucHssShort2GND;
    asSwitchStatus.sSwitchStatus[ucIdx].ucErrShort2VBAT = asState[ucIdx].ucHssShort2VBAT;
  }

  ucReturnValue = Rte_Write_CddSwi_SwitchStatus(&asSwitchStatus);

  return ucReturnValue;
}

//-----------------------------------------------------------------------------
/// \func   CddSwi_Rou_ParaFct0
///
/// \brief  CddSwi coding parameters
///
/// \param  eCmd (coding data valid / invalid)
/// \param  pData (pointer to coding data ram copy)
///
/// \return void
//-----------------------------------------------------------------------------
void CddSwi_Rou_ParaFct0(CONST_AL tParaFct0_Cmd eCmd, CONST_AL tNvmPara_CodingArea* CONST_AL pData)
{
  // set pointer to Nvm Data
  CddSwi_pCodingArea = pData;
  CddSwi_boCodingValid = (eCmd == eParaFct0_CodingDataValid) ? TRUE : FALSE;
}

//-----------------------------------------------------------------------------
/// \brief  CddSwi_MapParams
///
/// \descr  Maps the coding parameter in order to acces them in CddSwi
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddSwi_Rou_MapParams(void)
{
  tsRteCodingParameters sCodingParameters;

  (void)Rte_Read_CodM_CddSwi_Para(&sCodingParameters);

  CddSwi_Rou_ParaFct0(sCodingParameters.eCodingState, sCodingParameters.psCodingParameters_Blocks);
}

#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
//-----------------------------------------------------------------------------
/// \brief CddSwi_Rou_CheckScrollingSatellite_Status
///
/// \descr
///
/// \param  -
///
/// \return tScrollingPresent_Stat
//-----------------------------------------------------------------------------
tScrollingPresent_Stat CddSwi_Rou_CheckScrollingSatellite_Status(void)
{
  tScrollingPresent_Stat  ScrollingRetVal = { FALSE, FALSE };
  uint8_least ucIndx = 0u;

  for (ucIndx = 0u; ucIndx < CODM_PARA_LED_SIZE_PARAMS; ucIndx++)
  {
    if (CddSwi_pCodingArea->Led1.FUSAConfig.FUSA_DRV01_NAMES[ucIndx] == 7u)
    {
      ScrollingRetVal.boScrollingTIPresent_Stat = TRUE;
      break;
    }
    else
    {
      ScrollingRetVal.boScrollingTIPresent_Stat = FALSE;
    }
    //If TI scrolling is active then use the request, but if DRL is active too, prioritize TI request
  }

  if (ScrollingRetVal.boScrollingTIPresent_Stat == FALSE)
  {
    for (ucIndx = 0u; ucIndx < CODM_PARA_LED_SIZE_PARAMS; ucIndx++)
    {
      if (CddSwi_pCodingArea->Led1.FUSAConfig.FUSA_DRV01_NAMES[ucIndx] == 5u)
      {
        ScrollingRetVal.boScrollingDRLPresent_Stat = TRUE;
        break;
      }
      else
      {
        ScrollingRetVal.boScrollingDRLPresent_Stat = FALSE;
      }
      //If TI scrolling is active then use the request, but if DRL is active too, prioritize TI request
    }
  }
  return ScrollingRetVal;
}

#endif
// EOF

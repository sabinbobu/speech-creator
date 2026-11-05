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
/// \file   CddSwi.c
///
/// \brief  Specific code for Cdd Switch. An interface which controlls all the
///         HSS Chips
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
#include <CddSwi_Router.h>
#include <AL_Helper.h>

#ifdef CFG_VARIANT_FULL
#include <CddVnd7140.h>
#include <CddVnd7140_Cfg.h>
#include <CddVnd7140_Types.h>
#include <CtrlSwiRteAccess.h>
#endif

#include "CddSwi_Types.h"

//=============================================================================
// Defines and Typedef
//=============================================================================

//=============================================================================
//  Static variable declarations
//=============================================================================

STATIC_AL boolean CddSwi_boFanActive;

#if defined(SAMPLE_ECO) || defined(UNIT_TEST)
STATIC_AL boolean CddSwi_boHss3Active;
#endif

#ifdef UNIT_TEST
STATIC_AL sint8 snHSS3_MinDutyCycle_ut = 0;// variable used only to simulate target Value for HSS3
#endif // UNIT_TEST

//=============================================================================
// Function prototypes
//=============================================================================

//=============================================================================
// Macros
//=============================================================================


//=============================================================================
// Function definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  CddSwi_Init
///
/// \descr  Init Function
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddSwi_Init(void)
{
  tsCddSwi_SwitchStatus asSwitchStatus[CDDSWI_CFG_OUTPUTS_CNT];

  CddSwi_Rou_Init();

  CddSwi_boFanActive = (CddSwi_pCodingArea->Fan1.Fans_Presence.ucFan1Enabled == 1u) ? TRUE : FALSE;

#if defined(SAMPLE_ECO)
  CddSwi_boHss3Active = ((CddSwi_pCodingArea->Led1.LedConfigDRV13.FUSA_DRV13_NAME == CDDSWI_HSS_SM) || (CddSwi_pCodingArea->Led1.LedConfigDRV13.FUSA_DRV13_NAME == CDDSWI_HSS_DRL)) ? TRUE : FALSE;
#endif

  for (uint8_least ucIdx = 0; ucIdx < CDDSWI_CFG_OUTPUTS_CNT; ucIdx++)
  {
    asSwitchStatus[ucIdx] = CddSwi_GetState(ucIdx);
  }

  (void)CddSwi_Rou_Write_SwitchStatus(asSwitchStatus);
}

//-----------------------------------------------------------------------------
/// \brief  CddSwi_SetTgt
///
/// \descr  set target value on a HSS channel
///
/// \param  ulChnIdx - channel index
/// \param  unTgtVal - target value for HSS output
///
/// \return void
//-----------------------------------------------------------------------------
void CddSwi_SetTgt(CONST_AL uint32 ulChnIdx, CONST_AL uint16 unTgtVal)
{
  // evaluate the target value and set the output
  CddSwi_Rou_SetTgt(ulChnIdx, unTgtVal);
}

//-----------------------------------------------------------------------------
/// \brief  CddSwi_Cycle0
///
/// \descr  cyclic behaviour for the Cddhss chips. Reads the requests for the fan
///         from fctR module (LB Request) and the thermo requests. Set target value
///         for hss outputs. Get Error status
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddSwi_Cycle0(void)
{
  tsCddSwi_SwitchStatus asSwitchStatus[CDDSWI_CFG_OUTPUTS_CNT];
  uint8 ucHss_MinDuty = Cod_HSS3Min_Pwm();
#ifdef CFG_VARIANT_FULL
  uint16 aunTgtVal[CDDSWI_CFG_OUTPUTS_CNT] = { 0u, 0u, 0u, 0u};
  tCddSwi_TgtVal aucFanTgtValue[NO_OF_FANS] = { 0u, 0u, 0u};
#else 
  uint16 aunTgtVal[CDDSWI_CFG_OUTPUTS_CNT] = { 0u };
  tCddSwi_TgtVal aucFanTgtValue[NO_OF_FANS] = { 0u };
#endif
 
#if 0
  uint16 unHSS3_MinDutyCycle = (ucHss_MinDuty * CDDSWI_CFG_MAX_TGT_VAL) / 100u;
#endif
  uint16 unHSS3_MinDutyCycle = 0u;

  // Read Fan State
  (void)CddSwi_Rou_Read_Fan1_TgtVal(&aucFanTgtValue[FAN_NO_0]);
  (void)CddSwi_Rou_Read_RGB_SM_TgtVal(&aucFanTgtValue[RGB_SM]);
#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
  (void)CddSwi_Rou_Read_Fan2_TgtVal(&aucFanTgtValue[FAN_NO_1]);
  (void)CddSwi_Rou_Read_Ti_PosDrl_Scrolling_TgtVal(&aunTgtVal[3]);
#endif

  // FAN
#if defined (SAMPLE_FULL) || defined(UNIT_TEST)
  for (uint8_least ucIdx = 0; ucIdx < CDDSWI_CFG_OUTPUTS_CNT - 1u; ucIdx++)
#else
  for (uint8_least ucIdx = 0; ucIdx < CDDSWI_CFG_OUTPUTS_CNT; ucIdx++)
#endif
  {
    if (ucIdx == CDDSWI_CFG_HSS_OUTPUT1)
    {
      // Set Target Value for HSS1
     #if defined(SAMPLE_FULL) || defined(UNIT_TEST)
      aunTgtVal[ucIdx] = (aucFanTgtValue[FAN_NO_0] != CDDSWI_CFG_MIN_TGT_VAL) ? CDDSWI_CFG_MAX_TGT_VAL : CDDSWI_CFG_MIN_TGT_VAL;
#elif defined(SAMPLE_ECO)
      if (CddSwi_boHss3Active != FALSE)
      {
        // no duty cycle
        aunTgtVal[ucIdx] = (aucFanTgtValue[RGB_SM] > unHSS3_MinDutyCycle) ? CDDSWI_CFG_MAX_TGT_VAL : CDDSWI_CFG_MIN_TGT_VAL;
      }
      else if (CddSwi_boFanActive != FALSE)
      {
        aunTgtVal[ucIdx] = (aucFanTgtValue[FAN_NO_0] != CDDSWI_CFG_MIN_TGT_VAL) ? CDDSWI_CFG_MAX_TGT_VAL : CDDSWI_CFG_MIN_TGT_VAL;
      }
      else
      {
        aunTgtVal[ucIdx] = CDDSWI_CFG_MIN_TGT_VAL;
      }
#endif
    }
#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
    else if (ucIdx == CDDSWI_CFG_HSS_OUTPUT2)
    {
      // Set Target Value for HSS2
      aunTgtVal[ucIdx] = (aucFanTgtValue[FAN_NO_1] != CDDSWI_CFG_MIN_TGT_VAL) ? CDDSWI_CFG_MAX_TGT_VAL : CDDSWI_CFG_MIN_TGT_VAL;
    }
    else
    {
      // Set Target Value for HSS3 
#ifndef UNIT_TEST
      aunTgtVal[ucIdx] = (aucFanTgtValue[RGB_SM] >= unHSS3_MinDutyCycle) ? aucFanTgtValue[RGB_SM] : CDDSWI_CFG_MIN_TGT_VAL;
#else
      aunTgtVal[ucIdx] = (aucFanTgtValue[RGB_SM] >= snHSS3_MinDutyCycle_ut) ? aucFanTgtValue[RGB_SM] : CDDSWI_CFG_MIN_TGT_VAL;

#endif // !UNIT_TEST

    }
#endif

    CddSwi_SetTgt(ucIdx, aunTgtVal[ucIdx]);
    asSwitchStatus[ucIdx] = CddSwi_GetState(ucIdx);
  }

  // SBC LSS
#ifdef CFG_VARIANT_FULL
  CddSwi_SetTgt(3u, aunTgtVal[3]);
  asSwitchStatus[3] = CddSwi_GetState(3u);
#endif

  CddSwi_Rou_Cycle0();

  (void)CddSwi_Rou_Write_SwitchStatus(asSwitchStatus);

} //PRQA S 5324  // STCAL = 8, Statement intended due function complexity

//-----------------------------------------------------------------------------
/// \brief  CddSwi_GetState
///
/// \descr  return switch state on HSS channel
///
/// \param  ulChnIdx - channel index
///
/// \return tsCddSwi_SwitchStatus
//-----------------------------------------------------------------------------
tsCddSwi_SwitchStatus CddSwi_GetState(CONST_AL uint32 ulChnIdx)
{
  tsCddSwi_SwitchStatus asSwitchStatus[CDDSWI_CFG_OUTPUTS_CNT];

  if (ulChnIdx < CDDSWI_CFG_OUTPUTS_CNT)
  {
    asSwitchStatus[ulChnIdx] = CddSwi_Rou_GetState(ulChnIdx);
  }
  else
  {
    // channel index out of bound
  }

  // return the switch state
  return asSwitchStatus[ulChnIdx];
}

//-----------------------------------------------------------------------------
/// \brief  CddSwi_DeInit
///
/// \descr  deintialisation
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddSwi_DeInit(void)
{
  CddSwi_Rou_DeInit();
}

// EOF

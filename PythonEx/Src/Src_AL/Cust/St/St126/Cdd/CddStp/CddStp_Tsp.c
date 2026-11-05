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
/// \file  CddStp_Tsp.c
///
/// \brief  2 Stepper-Timer:
///          * CddStp_Tsp_Start(0, count);   // Stepper-Timer: HW-Pin-Toggling With u-Steps
///          * Gpt_StartTimer(  0, count);   // Help-Timer:    IRQ at the end: callback 'StpTimer0Notification' -> 'CddStp88XX_HalStpVer_TimerCb'
///
/// \author G. Dobato
///
//-----------------------------------------------------------------------------

#include <Std_Types.h>
#include <AL_Helper.h> //-- STATIC_AL
#include <Pwm.h>
#include <Lpit.h>


#ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
#include <../Cdd/CddStp/CddStp_Tsp.h>
#include <../Cdd/CddStp/CddStp_Tsp_Types.h>
#include <../Cdd/CddStp/CddStp_Tsp_TmrCfg.h>
#include <S32K146.h>
#else // Unit-Tests!
#include <CddStp_Tsp.h>
#include <CddStp_Tsp_Types.h>
#endif


//=============================================================================
// Pre-processor definitions
//=============================================================================


#define CDDSTP_RESOLUTION_CORRECTION_PWM  10U   // timer resolution correction from 1MHz to 10MHz
#define CDDSTP_RESOLUTION_CORRECTION_HLP  16U   // timer resolution correction from 1MHz to 16MHz


#define CDDSTP_TSP_PWMCH_IDX        12U

#define CDDSTP_TSP_CNT                1U
#define CDDSTP_TSP_LPIT_INSTANCE_IDX  0U  // index of Lpit timer used for cddstp


STATIC_AL boolean CddStp_Tsp_BoInitialized = FALSE;


//=============================================================================
// Private variables
//=============================================================================


//-----------------------------------------------------------------------------
/// \brief  CddStp_Tsp_Init
///
/// \descr  stop both timers at init .
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddStp_Tsp_Init(void)
{
  // disable channels
  CddStp_Tsp_Stop(0u);
  CddStp_Tsp_StopHelpTmr(0u);
}


//-----------------------------------------------------------------------------
/// \brief  CddStp_Tsp_Start
///
/// \descr  start pwm timer channel
///
/// \param   ucIdx - stepper index ,  period period of pwm
///
/// \return void
//-----------------------------------------------------------------------------
void CddStp_Tsp_Start(uint8 ucIdx, uint32 period)
{
  volatile uint32 ulTimerPeriod;
  (void) ucIdx;
  // get time in us
  ulTimerPeriod = period * CDDSTP_RESOLUTION_CORRECTION_PWM;

  // start channel with set period and 50% dutyin\

  Pwm_StartPwmChannel((Pwm_ChannelType)CDDSTP_TSP_PWMCH_IDX);
  
#ifndef UNIT_TEST
  // PRQA S 306 6 // direct memory access
  FTM4->SC &= (uint32) ~((uint32) 0x18U); //disable clock source for FTM4 (count register will not be incremented)
  FTM4->MOD = ulTimerPeriod; //set new period
  FTM4->CONTROLS[5].CnV = ulTimerPeriod >> 1u; //set new duty (50%)
  FTM4->CNT = 0u; //reset counter (writing any value will reset the counter)
  FTM4->SC |= 0x08U; //enable clock source for FTM4 (all above registers will be written from their buffers - sync)
  FTM4->SYNC |= FTM_SYNC_SWSYNC_MASK + FTM_SYNC_REINIT_MASK; //sw sync
  //Pwm_SetPeriodAndDuty((Pwm_ChannelType)CDDSTP_TSP_PWMCH_IDX, ulTimerPeriod, 0x4000);
#endif
}

//-----------------------------------------------------------------------------
/// \brief  CddStp_Tsp_StartHelpTimer
///
/// \descr  starts timer for incrementing to next step, with set time
///
/// \param  ucIdx - stepper index ,  period - amount of time in us
///
/// \return void
//-----------------------------------------------------------------------------
void CddStp_Tsp_StartHelpTimer(uint8 ucIdx, uint32 period)
{
  volatile uint32 ulTimerPeriod;

  (void)ucIdx;

  // get time in us
  ulTimerPeriod = period * CDDSTP_RESOLUTION_CORRECTION_HLP;

  Lpit_LpitSetTmrChCompVal(&Lpit_sLpitDatatCfg.sLpitTmrCfg.sLpitTmrCfg[CDDSTP_TSP_LPIT_INSTANCE_IDX], ulTimerPeriod);

  Lpit_LpitSetTmrChIntEnbl(&Lpit_sLpitDatatCfg.sLpitTmrCfg.sLpitTmrCfg[CDDSTP_TSP_LPIT_INSTANCE_IDX], TRUE);

  Lpit_LpitSetTmrEnblBit(&Lpit_sLpitDatatCfg.sLpitTmrCfg.sLpitTmrCfg[CDDSTP_TSP_LPIT_INSTANCE_IDX], TRUE);
}

//-----------------------------------------------------------------------------
/// \brief  CddStp_Tsp_Stop
///
/// \descr
///
/// \param  ucIdx
///
/// \return void
//-----------------------------------------------------------------------------
void CddStp_Tsp_Stop(uint8 ucIdx)
{
 (void)ucIdx;

  Pwm_ClampPwmChannel((Pwm_ChannelType)CDDSTP_TSP_PWMCH_IDX, PWM_LOW);
  // PRQA S 4342 1 // program architecture and readability - FALSE will always be 0 , this is better for portability - warning - QAC
}
//-----------------------------------------------------------------------------
/// \brief  CddStp_Tsp_Stop
///
/// \descr
///
/// \param  ucIdx
///
/// \return void
//-----------------------------------------------------------------------------
void CddStp_Tsp_ResetFlag(uint8 ucIdx)
{
 (void)ucIdx;

  Lpit_LpitClearTimeout(&Lpit_sLpitDatatCfg.sLpitTmrCfg.sLpitTmrCfg[CDDSTP_TSP_LPIT_INSTANCE_IDX]);
}
/// \brief  CddStp_Tsp_Stop
///
/// \descr
///
/// \param  ucIdx
///
/// \return void
//-----------------------------------------------------------------------------
void CddStp_Tsp_StopHelpTmr(uint8 ucIdx)
{
 (void)ucIdx;

  Lpit_LpitSetTmrEnblBit(&Lpit_sLpitDatatCfg.sLpitTmrCfg.sLpitTmrCfg[CDDSTP_TSP_LPIT_INSTANCE_IDX], FALSE);
}

//-----------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
uint32 CddStp_Tsp_GetTicks(uint8 ucIdx)
{
 uint32 ulTicks = 0u;

 (void)ucIdx;

 ulTicks = Lpit_LpitReturnCount(&Lpit_sLpitDatatCfg.sLpitTmrCfg.sLpitTmrCfg[CDDSTP_TSP_LPIT_INSTANCE_IDX]);

 // apply correction factor 
 ulTicks = ulTicks / CDDSTP_RESOLUTION_CORRECTION_HLP;

 return ulTicks;
}


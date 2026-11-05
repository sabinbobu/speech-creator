//*****************************************************************************
// (C) Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Automotive Lighting Reutlingen GmbH.
//*****************************************************************************


//=============================================================================
// Includes
//=============================================================================
#include <LPTMR.h>
#include <lptmr_driver.h>
#include <UtilUtility.h>
#include <Cfg/Cfg.h>



//extern "C"
/* LPTMR configuration structure 0 */
static const lptmr_config_t  lptmr_1_config0 = {
  // dmaRequest, interruptEnable, freeRun, workMode, 
  //clockSelect, prescaler, bypassPrescaler, compareValue, 
  //counterUnits, pinSelect, pinPolarity
  false, true, false,  LPTMR_WORKMODE_TIMER,
  LPTMR_CLOCKSOURCE_PCC, LPTMR_PRESCALE_16_GLITCHFILTER_8, false, 1000U,
  LPTMR_COUNTER_UNITS_TICKS, LPTMR_PINSELECT_TRGMUX, LPTMR_PINPOLARITY_RISING
};

const LPTMR_SpecificType LPTMR_Config =
{
  1U,
  (lptmr_config_t*)&lptmr_1_config0 // PRQA S 310, 311 // Necessary cast to avoid using ThirdParty structures
};

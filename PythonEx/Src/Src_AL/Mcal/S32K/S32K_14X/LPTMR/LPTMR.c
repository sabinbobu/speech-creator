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
/// \file  LPTMR.c
///
/// \brief  
///
/// \descr  
///
/// \author Cosmin Cojocaru (f11501c)
///         mailTo:constantin-cosmin.cojocaru(at)marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// Includes
//=============================================================================
#include <LPTMR.h>
#include <Cfg/Cfg.h>
#include <stddef.h>
#include <string.h>
#include <UtilUtility.h>

#ifndef UNIT_TEST
#include <lptmr_driver.h>
#include <interrupt_manager.h>
#include <RTX_Config_CPUload.h>
#endif

#if defined (CPU_S32K142)
  #include <S32K142.h>
#elif defined (CPU_S32K144)
  #include <S32K144.h>
#elif defined (CPU_S32K146)
  #include <S32K146.h>
#endif


//=============================================================================
// Private macros
//=============================================================================

#define LPTMR_CHECK_CONFIG_NR       11u

//=============================================================================
// Public variables definitions
//=============================================================================

//=============================================================================
// Private variables definitions
//=============================================================================


//=============================================================================
// Public functions definitions
//=============================================================================
//-----------------------------------------------------------------------------
// \brief   spi_init
//
// \descr   Initialized Spi peripheral
//
// \param   void
//
// \return  -
//-----------------------------------------------------------------------------

STATIC_AL uint32 ulLPTMR0_MicrosecondTimer;

// LPTMR init configuration
STATIC_AL volatile lptmr_config_t LPTMR_sTimerCfg_Init = { 0 };

// Check LPTMR Params callbacks
STATIC_AL boolean LPTMR_Check_ByPassPrescaler_Cfg  (lptmr_config_t * const psLPTMRCfg);
STATIC_AL boolean LPTMR_Check_ClkSelect_Cfg        (lptmr_config_t * const psLPTMRCfg);
STATIC_AL boolean LPTMR_Check_CompVal_Cfg          (lptmr_config_t * const psLPTMRCfg);
STATIC_AL boolean LPTMR_Check_CntUnit_Cfg          (lptmr_config_t * const psLPTMRCfg);
STATIC_AL boolean LPTMR_Check_DmaReq_Cfg           (lptmr_config_t * const psLPTMRCfg);
STATIC_AL boolean LPTMR_Check_FreeRun_Cfg          (lptmr_config_t * const psLPTMRCfg);
STATIC_AL boolean LPTMR_Check_IntEnbl_Cfg          (lptmr_config_t * const psLPTMRCfg);
STATIC_AL boolean LPTMR_Check_PinPol_Cfg           (lptmr_config_t * const psLPTMRCfg);
STATIC_AL boolean LPTMR_Check_PinSel_Cfg           (lptmr_config_t * const psLPTMRCfg);
STATIC_AL boolean LPTMR_Check_Prescaler_Cfg        (lptmr_config_t * const psLPTMRCfg);
STATIC_AL boolean LPTMR_Check_WorkMode_Cfg         (lptmr_config_t * const psLPTMRCfg);

// Callbacks array for LPTMR config. check
STATIC_AL boolean(*pfLPTMR_CheckCfg[LPTMR_CHECK_CONFIG_NR]) (lptmr_config_t * const psLPTMRCfg) =
{
  LPTMR_Check_ByPassPrescaler_Cfg,
  LPTMR_Check_ClkSelect_Cfg,
  LPTMR_Check_CompVal_Cfg,
  LPTMR_Check_CntUnit_Cfg,
  LPTMR_Check_DmaReq_Cfg,
  LPTMR_Check_FreeRun_Cfg,
  LPTMR_Check_IntEnbl_Cfg,
  LPTMR_Check_PinPol_Cfg,
  LPTMR_Check_PinSel_Cfg,
  LPTMR_Check_Prescaler_Cfg,
  LPTMR_Check_WorkMode_Cfg
};


void LPTMR_INIT(const LPTMR_ConfigType* ConfigPtr)
{
    // PRQA S 316 2 // Intended cast
    LPTMR_DRV_Init(INST_LPTMR_1, (lptmr_config_t*)ConfigPtr->lptmr_cfg, false);
    /* Enable IRQ for LPTMR */
    //INT_SYS_EnableIRQ(LPTMR0_IRQn);

    /* Start LPTMR counter */
    LPTMR_DRV_StartCounter(INST_LPTMR_1);

    // Memorize init configuration for LPTMR instance
    // PRQA S 316 1 // type cast neede from generic void* type
    LPTMR_sTimerCfg_Init = *(lptmr_config_t* )ConfigPtr->lptmr_cfg;
}

/*!
 * \brief: LPTMR IRQ handler.
 */
void LPTMR0_IRQHandler(void)
{
    /* Clear compare flag */
    LPTMR_DRV_ClearCompareFlag(INST_LPTMR_1);
    ulLPTMR0_MicrosecondTimer += 1000u;
    RTX_Timer_Notification();
}

uint32 LPTMR0_GetTimeElapsed(const uint32 ulStartValue)
{
  return (ulLPTMR0_MicrosecondTimer + (LPTMR_DRV_GetCounterValueByCount(INST_LPTMR_1)))- ulStartValue;
}


//-----------------------------------------------------------------------------
/// \brief LPTMR_Check_ByPassPrescaler_Cfg
///
/// \descr Check the prescaler consistency
///
/// \param  psLPTMRCfg - LPTMR config
///
/// \return boolean - TRUE -> error, config was changed since INIT
//-----------------------------------------------------------------------------
STATIC_AL boolean LPTMR_Check_ByPassPrescaler_Cfg(lptmr_config_t * const psLPTMRCfg)
{
  return (psLPTMRCfg->bypassPrescaler != LPTMR_sTimerCfg_Init.bypassPrescaler) ? TRUE : FALSE;
}

//-----------------------------------------------------------------------------
/// \brief LPTMR_Check_ClkSelect_Cfg
///
/// \descr Check the clock selector consistency
///
/// \param  psLPTMRCfg - LPTMR config
///
/// \return boolean - TRUE -> error, config was changed since INIT
//-----------------------------------------------------------------------------
STATIC_AL boolean LPTMR_Check_ClkSelect_Cfg(lptmr_config_t * const psLPTMRCfg)
{
  return (psLPTMRCfg->clockSelect != LPTMR_sTimerCfg_Init.clockSelect) ? TRUE : FALSE;
}


//-----------------------------------------------------------------------------
/// \brief LPTMR_Check_CompVal_Cfg
///
/// \descr Check the compare value consistency
///
/// \param  psLPTMRCfg - LPTMR config
///
/// \return boolean - TRUE -> error, config was changed since INIT
//-----------------------------------------------------------------------------
STATIC_AL boolean LPTMR_Check_CompVal_Cfg(lptmr_config_t * const psLPTMRCfg)
{
  return (psLPTMRCfg->compareValue != LPTMR_sTimerCfg_Init.compareValue) ? TRUE : FALSE;
}

//-----------------------------------------------------------------------------
/// \brief LPTMR_Check_CntUnit_Cfg
///
/// \descr Check the counter unit value consistency
///
/// \param  psLPTMRCfg - LPTMR config
///
/// \return boolean - TRUE -> error, config was changed since INIT
//-----------------------------------------------------------------------------
STATIC_AL boolean LPTMR_Check_CntUnit_Cfg(lptmr_config_t * const psLPTMRCfg)
{
  return (psLPTMRCfg->counterUnits != LPTMR_sTimerCfg_Init.counterUnits) ? TRUE : FALSE;
}

//-----------------------------------------------------------------------------
/// \brief LPTMR_Check_DmaReq_Cfg
///
/// \descr Check the dma request value consistency
///
/// \param  psLPTMRCfg - LPTMR config
///
/// \return boolean - TRUE -> error, config was changed since INIT
//-----------------------------------------------------------------------------
STATIC_AL boolean LPTMR_Check_DmaReq_Cfg(lptmr_config_t * const psLPTMRCfg)
{
  return (psLPTMRCfg->dmaRequest != LPTMR_sTimerCfg_Init.dmaRequest) ? TRUE : FALSE;
}

//-----------------------------------------------------------------------------
/// \brief LPTMR_Check_FreeRun_Cfg
///
/// \descr Check the free run mode value consistency
///
/// \param  psLPTMRCfg - LPTMR config
///
/// \return boolean - TRUE -> error, config was changed since INIT
//-----------------------------------------------------------------------------
STATIC_AL boolean LPTMR_Check_FreeRun_Cfg(lptmr_config_t * const psLPTMRCfg)
{
  return (psLPTMRCfg->freeRun != LPTMR_sTimerCfg_Init.freeRun) ? TRUE : FALSE;
}

//-----------------------------------------------------------------------------
/// \brief LPTMR_Check_IntEnbl_Cfg
///
/// \descr Check the Interrupt Enable value consistency
///
/// \param  psLPTMRCfg - LPTMR config
///
/// \return boolean - TRUE -> error, config was changed since INIT
//-----------------------------------------------------------------------------
STATIC_AL boolean LPTMR_Check_IntEnbl_Cfg(lptmr_config_t * const psLPTMRCfg)
{
  return (psLPTMRCfg->interruptEnable != LPTMR_sTimerCfg_Init.interruptEnable) ? TRUE : FALSE;
}

//-----------------------------------------------------------------------------
/// \brief LPTMR_Check_PinSel_Cfg
///
/// \descr Check the Pin Select value consistency
///
/// \param  psLPTMRCfg - LPTMR config
///
/// \return boolean - TRUE -> error, config was changed since INIT
//-----------------------------------------------------------------------------
STATIC_AL boolean LPTMR_Check_PinSel_Cfg(lptmr_config_t * const psLPTMRCfg)
{
  return (psLPTMRCfg->pinSelect != LPTMR_sTimerCfg_Init.pinSelect) ? TRUE : FALSE;
}


//-----------------------------------------------------------------------------
/// \brief LPTMR_Check_PinPol_Cfg
///
/// \descr Check the pin polarity value consistency
///
/// \param  psLPTMRCfg - LPTMR config
///
/// \return boolean - TRUE -> error, config was changed since INIT
//-----------------------------------------------------------------------------
STATIC_AL boolean LPTMR_Check_PinPol_Cfg(lptmr_config_t * const psLPTMRCfg)
{
  return (psLPTMRCfg->pinPolarity != LPTMR_sTimerCfg_Init.pinPolarity) ? TRUE : FALSE;
}

//-----------------------------------------------------------------------------
/// \brief LPTMR_Check_Prescaler_Cfg
///
/// \descr Check the prescaler value consistency
///
/// \param  psLPTMRCfg - LPTMR config
///
/// \return boolean - TRUE -> error, config was changed since INIT
//-----------------------------------------------------------------------------
STATIC_AL boolean LPTMR_Check_Prescaler_Cfg(lptmr_config_t * const psLPTMRCfg)
{
  return (psLPTMRCfg->prescaler != LPTMR_sTimerCfg_Init.prescaler) ? TRUE : FALSE;
}

//-----------------------------------------------------------------------------
/// \brief LPTMR_Check_WorkMode_Cfg
///
/// \descr Check the work mode value consistency
///
/// \param  psLPTMRCfg - LPTMR config
///
/// \return boolean - TRUE -> error, config was changed since INIT
//-----------------------------------------------------------------------------
STATIC_AL boolean LPTMR_Check_WorkMode_Cfg(lptmr_config_t * const psLPTMRCfg)
{
  return (psLPTMRCfg->workMode != LPTMR_sTimerCfg_Init.workMode) ? TRUE : FALSE;
}

//-----------------------------------------------------------------------------
/// \brief LPTMR_Check_Config
///
/// \descr Check the LPTMR configuration consistency
///
/// \param  void
///
/// \return boolean - TRUE -> error, config was changed since INIT
//-----------------------------------------------------------------------------
boolean LPTMR_Check_Config(void)
{
  lptmr_config_t sLPTMR_config = { 0 };
  boolean boCfgErrStatus = FALSE, boReturnFct = FALSE;

  // Get LPTMR configuration
  LPTMR_DRV_GetConfig(INST_LPTMR_1, &sLPTMR_config);

  // check all config parameter
  for (uint8_least ucIndx = 0u; ucIndx < LPTMR_CHECK_CONFIG_NR; ucIndx++)
  {
    // check config parameter
    if (pfLPTMR_CheckCfg[ucIndx](&sLPTMR_config) != FALSE)
    {
      boCfgErrStatus = TRUE;
      break;
    }
  }
  
  // Check if timer is running and configuration is kept
  if ((LPTMR_DRV_IsRunning(INST_LPTMR_1) == false) || (boCfgErrStatus != FALSE))
  {
    LPTMR_DRV_StopCounter(INST_LPTMR_1);
    boReturnFct = TRUE;
  }

  return boReturnFct;
}


// EOF

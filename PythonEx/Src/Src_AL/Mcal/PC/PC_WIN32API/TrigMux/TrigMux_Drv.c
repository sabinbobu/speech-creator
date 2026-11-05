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
/// \file TrigMux_Drv.c
///
/// \brief TrigMux Driver file (low access to the TRIGMUX pheripheric)
///
/// \author Stefan Tyirean (f75617c)
///         mailto: stefan.tyirean[at]marelli.com
///
/// \Date April 2021
///
//-----------------------------------------------------------------------------

//====================================================================
// Include files
//====================================================================

#include "TrigMux_Drv.h"
#include "TrigMux_TargetTypes.h"
#include <UtilUtility.h>

#if defined (CPU_S32K142)
  #include <S32K142.h>
#elif defined (CPU_S32K144)
  #include <S32K144.h>
#elif defined (CPU_S32K146)
  #include <S32K146.h>
#endif

#if defined (UNIT_TEST)
#include "TrigMux_reg_stubs.h"
#endif

//====================================================================
// Defines
//====================================================================

#define TRIGMUX_DRV_TRIGGER_DIV_SELECTOR            4u
#define TRIGMUX_DRV_TRIGGER_MOD_SELECTOR            4u
#define TRIGMUX_DRV_TRIGGER_CLEAR_MASK              0x3Fu
#define TRIGMUX_DRV_TRIGGER_CLEAR_MASK_SHIFTER      8u
#define TRIGMUX_DRV_TRIGGER_BIT_ENBL                1u
#define TRIGMUX_DRV_TRIGGER_LOCK_POS                31u
#define TRIGMUX_DRV_TRIGGER_SEL_MAX_VAL             0x7Fu

//====================================================================
// Local functions declaration
//====================================================================

STATIC_AL void TrigMux_InitTrgMuxCh(CONST_AL tsTrigMux_TrigMuxCfg * CONST_AL psTrgMux);

//-----------------------------------------------------------------------------
/// \brief TrigMux_Drv_Init
///
/// \descr TrigMus Driver Init procedure
///
/// \param  psTrigMuxCfgData - TrigMux Data configuration (instances, channels)
///
/// \return Std_ReturnType - Always returns E_OK
//-----------------------------------------------------------------------------
Std_ReturnType TrigMux_Drv_Init(CONST_AL tsTrigMux_CfgData* CONST_AL psTrigMuxCfgData)
{
  return E_OK;
}

//-----------------------------------------------------------------------------
/// \brief TrigMux_InitTrgMuxCh
///
/// \descr TrigMux Driver Initialization
///
/// \param  psTrgMux - TrigMux Configuration
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void TrigMux_InitTrgMuxCh(CONST_AL tsTrigMux_TrigMuxCfg * CONST_AL psTrgMux)
{
  return;
}

// EOF

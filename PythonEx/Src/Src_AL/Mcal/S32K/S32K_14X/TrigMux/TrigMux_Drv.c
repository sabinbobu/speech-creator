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
  // TriggerMux Channel Index
  uint8 ucTriggerIdx = 0u;

  for (ucTriggerIdx = 0u; ucTriggerIdx < psTrigMuxCfgData->sTrigMuxInstanceCfg.ucCfgLength; ucTriggerIdx++)
  {
    // TrigMux Channels Initialization
    TrigMux_InitTrgMuxCh(&psTrigMuxCfgData->sTrigMuxInstanceCfg.psTrigMuxCfg[ucTriggerIdx]);
  }

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
  // TriggerMux Instance
  TRGMUX_Type *sTrigMuxInstance = NULL_PTR;
  // Temp register value
  volatile uint32 ulRegValue = 0u;

  // Get TrigMux Instance (only TRIGMUX0 is valid)
  // PRQA S 306 1 //Cast between a pointer and an integral type need to access peripheral uC registers
  sTrigMuxInstance = (psTrgMux->ucTrigMuxInst == 0u) ? TRGMUX : NULL_PTR;

  // TRIGMUX valid
  if ((sTrigMuxInstance != NULL_PTR) && ((uint32)psTrgMux->eTrigSource <= TRIGMUX_DRV_TRIGGER_SEL_MAX_VAL) && ((uint32)psTrgMux->eTrigTarget <= TRIGMUX_DRV_TRIGGER_SEL_MAX_VAL))
  {
    // Get Trigger target (register based on input)
    // PRQA S 310 1 // Cast needed
     vuint32* pulTriggerMuxTargetAddr = (vuint32*)sTrigMuxInstance + ((uint8)psTrgMux->eTrigTarget / TRIGMUX_DRV_TRIGGER_DIV_SELECTOR);

    // Set target field in register given above
    uint8 ucBitSelectorOffset = (uint8)psTrgMux->eTrigTarget % TRIGMUX_DRV_TRIGGER_MOD_SELECTOR;

    // Get Target Register Value
    ulRegValue = *(vuint32*)pulTriggerMuxTargetAddr;

    // Set Trigger channel Source
    // PRQA S 4391 2 // Cast needed
    ulRegValue &= (uint32)(~(uint32)((uint32)TRIGMUX_DRV_TRIGGER_CLEAR_MASK << (TRIGMUX_DRV_TRIGGER_CLEAR_MASK_SHIFTER * ucBitSelectorOffset)));
    ulRegValue |= (uint32)((uint32)psTrgMux->eTrigSource << (TRIGMUX_DRV_TRIGGER_CLEAR_MASK_SHIFTER * ucBitSelectorOffset));

    // TriggerMux Lock Option
    if (psTrgMux->boLock != FALSE)
    {
      // Write Lock bit
      ulRegValue |= (uint32)((uint32)TRIGMUX_DRV_TRIGGER_BIT_ENBL << TRIGMUX_DRV_TRIGGER_LOCK_POS);
    }
    else
    {
      // Skip, lock disabled already
    }
    // Upload target register with trigmux channel configuration
    *(vuint32*)pulTriggerMuxTargetAddr = ulRegValue;
  }
  else
  {
    // NULL_PTR or channel invalid configuration
  }
}

// EOF

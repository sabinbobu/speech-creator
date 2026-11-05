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
/// \file  TrigMux_Drv.c
///
/// \brief
///
//-----------------------------------------------------------------------------

#include "TrigMux_Drv.h"
#include <UtilUtility.h>
#include <../Cdd/CddAdc/Gen/CddAdc_Types.h>

static void CddAdc_InitTrgMuxCh(const tsCddAdc_TrigMuxCfg * const sTrgMux);

//-----------------------------------------------------------------------------
/// \brief CddAdc_InitTrigMux
///
/// \descr
///
/// \param  -
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType CddAdc_Drv_InitTrigMux(tsCddAdc_CfgData sCfgData)
{

  uint8 ucTriggerIdx;

  for (ucTriggerIdx = 0u; ucTriggerIdx < sCfgData.psTrigMuxInstanceCfg.ucCfgLength; ucTriggerIdx++)
  {
    CddAdc_InitTrgMuxCh(&sCfgData.psTrigMuxInstanceCfg.psTrigMuxCfg[ucTriggerIdx]);
  }

  return E_OK;
}

//-----------------------------------------------------------------------------
/// \brief CddAdc_InitTrgMuxCh
///
/// \descr
///
/// \param  sTrgMux
///
/// \return void
//-----------------------------------------------------------------------------
static void CddAdc_InitTrgMuxCh(const tsCddAdc_TrigMuxCfg * const sTrgMux)
{
  volatile uint32* pulTriggerMuxTargetAddr = (vuint32*)sTrgMux->psTrigMuxInst + ((uint8)sTrgMux->eTrigTarget / 4u);
  uint8 ucBitSelectorOffset = (uint8)sTrgMux->eTrigTarget % 4u;
  volatile uint32 ulRegValue = 0u;

  ulRegValue = *(vuint32*)pulTriggerMuxTargetAddr;
  ulRegValue &= (vuint32)(~(vuint32)(0x3Fu << (8u * ucBitSelectorOffset)));
  ulRegValue |= (vuint32)((vuint32)sTrgMux->eTrigSource << (8u * ucBitSelectorOffset));

  if (sTrgMux->boLock != FALSE)
  {
    ulRegValue |= (vuint32)(1u << 31);
  }
  else
  {
  }
  *(vuint32*)pulTriggerMuxTargetAddr = ulRegValue;
}


// EOF
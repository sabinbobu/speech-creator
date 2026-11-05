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
/// \file  CddAdc.c
///
/// \brief
///
//-----------------------------------------------------------------------------

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
/// \file  CddAdc.c
///
/// \brief
///
//-----------------------------------------------------------------------------

//====================================================================
// Include files
//====================================================================

#include <../Cdd/CddAdc/S32K/S32K_14X/_146/CddAdc_S32K_14X_146_Reg_Types.h>
#include <../Cdd/CddAdc/Gen/CddAdc_Types.h>
#include <../Cdd/CddAdc/Api/CddAdc.h>
#include <../Cdd/CddAdc/Gen/Dma/Dma_Job.h>
#include <../Cdd/CddAdc/Gen/Pdb/Pdb_Drv.h>
#include <../Cdd/CddAdc/Gen/Lpit/Lpit_Drv.h>
#include <../Cdd/CddAdc/Gen/TrigMux/TrigMux_Drv.h>
#include <../Cdd/CddAdc/Gen/Adc/Adc_Drv.h>


#define CDDADC_DEFINE_IN_DATA_CFG
#include <../Cdd/CddAdc/Cfg/CddAdc_Cfg.h>
#undef CDDADC_DEFINE_IN_DATA_CFG

#define CDDADC_DEFINE_IN_MAP_CFG
#include <../Cdd/CddAdc/Cfg/CddAdc_Cfg.h>
#undef CDDADC_DEFINE_IN_MAP_CFG

#define CDDADC_DEFINE_ADC_INSTANCE_CFG
#include <../Cdd/CddAdc/Cfg/CddAdc_Cfg.h>
#undef CDDADC_DEFINE_ADC_INSTANCE_CFG

#define CDDADC_DEFINE_LPIT_INSTANCE_CFG
#include <../Cdd/CddAdc/Cfg/CddAdc_Cfg.h>
#undef CDDADC_DEFINE_LPIT_INSTANCE_CFG

#define CDDADC_DEFINE_LPIT_TMR_CFG
#include <../Cdd/CddAdc/Cfg/CddAdc_Cfg.h>
#undef CDDADC_DEFINE_LPIT_TMR_CFG

#define CDDADC_DEFINE_PDB_INSTANCE_CFG
#include <../Cdd/CddAdc/Cfg/CddAdc_Cfg.h>
#undef CDDADC_DEFINE_PDB_INSTANCE_CFG

#define CDDADC_DEFINE_TRG_MUX_CFG
#include <../Cdd/CddAdc/Cfg/CddAdc_Cfg.h>
#undef CDDADC_DEFINE_TRG_MUX_CFG


//====================================================================
// Global variables
//====================================================================


//====================================================================
// Local function definitions
//====================================================================

static void CddAdc_MountAllConfigforShare(tsCddAdc_CfgData* const sCfgData);

//-----------------------------------------------------------------------------
/// \brief CddAdc_Init
///
/// \descr
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void CddAdc_AdcInit(void)
{
  Std_ReturnType eAdcDrvInitStatus;
  Std_ReturnType eDamJobInitStatus;

  tsCddAdc_CfgData sInputCfgData;

  CddAdc_MountAllConfigforShare(&sInputCfgData);

  eAdcDrvInitStatus = CddAdc_Drv_InitAdc(sInputCfgData);
 
  eDamJobInitStatus = CddAdc_InitDmaJob(sInputCfgData);

  if ((eAdcDrvInitStatus == E_OK) && (eDamJobInitStatus == E_OK))
  {
    // Programmable delay bloc init
    (void)CddAdc_Drv_InitPdb(sInputCfgData);
    (void)CddAdc_Drv_InitTrigMux(sInputCfgData);
    (void)CddAdc_Drv_InitLpit(sInputCfgData);
  }
  else
  {
    // No Hw Dma Trigger
  }
}

//-----------------------------------------------------------------------------
/// \brief CddAdc_MountAllConfigforShare
///
/// \descr
///
/// \param  sCfgData
///
/// \return void
//-----------------------------------------------------------------------------
static void CddAdc_MountAllConfigforShare(tsCddAdc_CfgData* const sCfgData)
{
  sCfgData->psAdcInstanceCfg.psAdcInstCfg       = &CddAdc_asAdcInstCfg[0];
  sCfgData->psAdcInstanceCfg.ucCfgLength        = sizeof(CddAdc_asAdcInstCfg) / sizeof(CddAdc_asAdcInstCfg[0]);
  sCfgData->psAdcInputChCfg.psAdcInCfg          = &CddAdc_asAdcChMapCfg[0];
  sCfgData->psAdcInputChCfg.ucCfgLength         = sizeof(CddAdc_asAdcChMapCfg) / sizeof(CddAdc_asAdcChMapCfg[0]);
  sCfgData->psAdcDataOut.pulAdcDataOut          = &CddAdc_aulAdcChData[0];
  sCfgData->psAdcDataOut.ucCfgLength            = sizeof(CddAdc_aulAdcChData) / sizeof(CddAdc_aulAdcChData[0]);
  sCfgData->psPdbInstanceCfg.psPdbInstCfg       = &CddAdc_asPdbInstCfg[0];
  sCfgData->psPdbInstanceCfg.ucCfgLength        = sizeof(CddAdc_asPdbInstCfg) / sizeof(CddAdc_asPdbInstCfg[0]);
  sCfgData->psLpitInstanceCfg.psLpitInstCfg     = &CddAdc_asLpitInstCfg[0];
  sCfgData->psLpitInstanceCfg.ucCfgLength       = sizeof(CddAdc_asLpitInstCfg) / sizeof(CddAdc_asLpitInstCfg[0]);
  sCfgData->psLpitTmrCfg.psLpitTmrCfg           = &CddAdc_asLpitTmrCfg[0];
  sCfgData->psLpitTmrCfg.ucCfgLength            = sizeof(CddAdc_asLpitTmrCfg) / sizeof(CddAdc_asLpitTmrCfg[0]);
  sCfgData->psTrigMuxInstanceCfg.psTrigMuxCfg   = &CddAdc_asTrgMuxCfg[0];
  sCfgData->psTrigMuxInstanceCfg.ucCfgLength    = sizeof(CddAdc_asTrgMuxCfg) / sizeof(CddAdc_asTrgMuxCfg[0]);
}

//-----------------------------------------------------------------------------
/// \brief CddAdc_GetAdcRawValue
///
/// \descr
///
/// \param  ucInputIx
///
/// \return uint16
//-----------------------------------------------------------------------------
Std_ReturnType Adc_ReadGroup(uint8 ucAdcIn, uint16* const unAdcValue)
{
  *unAdcValue =  CddAdc_Drv_GetAdcRawValue(ucAdcIn);

  return E_OK;
}

// EOF

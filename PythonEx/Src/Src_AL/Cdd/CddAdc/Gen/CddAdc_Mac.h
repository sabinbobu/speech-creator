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
/// \file  CddAdc_Mac.h
///
/// \brief
///
//-----------------------------------------------------------------------------

#include "CddAdc_Mac_Prep.h"

#if defined (CDDADC_DEFINE_ADC_INSTANCE_CFG)

#define BEGIN_ADC_INSTANCE_CFG_MAP    const tsCddAdc_AdcInstanceCfg CddAdc_asAdcInstCfg[] = {
#define ADC_INST_CFG(adcinst, clkdiv, sampletime, resolution, clkin, trigger, pretriggersel, triggersel, dma, voltref, continousconv, monitoring, avgenbl, avgsmp) {adcinst, clkdiv, sampletime, resolution, clkin, trigger, pretriggersel, triggersel, dma, voltref, continousconv, monitoring, avgenbl, avgsmp},
#define END_ADC_INSTANCE_CFG_MAP  };

#define BEGIN_ADC_CHN_MAP_CFG
#define ADC_IN_CH_MAP_CFG(inputidx, adcinst,  adcchnl, inselctor, interruptenbl, pdbinst, pdbchnl, pdbdelay, pdbtrgout, pdbb2b, pdbchnlenbl, data )
#define END_ADC_CHN_MAP_CFG

#define BEGIN_PDB_INSTANCE_CFG_MAP
#define PDB_INST_CFG(pdbinst, loadmod, intenbl, dmaenbl, clkpresc, clkmul, trigsel, continous, period, intcompval, modenbl)
#define END_PDB_INSTANCE_CFG_MAP

#define BEGIN_LPIT_INSTANCE_CFG_MAP
#define LPIT_INST_CFG(instance, degugenbl, dozeenbl)
#define END_LPIT_INSTANCE_CFG_MAP

#define BEGIN_LPIT_CHN_MAP_CFG
#define LPIT_CHN_MAP_CFG(instance, ch, tmrmode, period, trigsrc, trigsel, rot, soi, sot, chainenbl, intenbl)
#define END_LPIT_CHN_MAP_CFG

#define BEGIN_TRIGMUX_CHN_CFG
#define TRGMUX_CHN_MAP_CFG(instance, sorce, target, lock)
#define END_TRIGMUX_CHN_CFG


#elif defined (CDDADC_DEFINE_IN_MAP_CFG)

#define BEGIN_ADC_INSTANCE_CFG_MAP
#define ADC_INST_CFG(adcinst, clkdiv, sampletime, resolution, clkin, trigger, pretriggersel, triggersel, dma, voltref, continousconv, monitoring, avgenbl, avgsmp )
#define END_ADC_INSTANCE_CFG_MAP 

#define BEGIN_ADC_CHN_MAP_CFG   const tsCddAdc_AdcInputCfg CddAdc_asAdcChMapCfg[] = {
#define ADC_IN_CH_MAP_CFG(inputidx, adcinst,  adcchnl, inselctor, interruptenbl, pdbinst, pdbchnl, pdbdelay, pdbtrgout, pdbb2b, pdbchnlenbl, data)  {inputidx, adcinst, adcchnl, inselctor, interruptenbl, pdbinst, pdbchnl, pdbdelay, pdbtrgout, pdbb2b, pdbchnlenbl, data},
#define END_ADC_CHN_MAP_CFG  };

#define BEGIN_PDB_INSTANCE_CFG_MAP
#define PDB_INST_CFG(pdbinst, loadmod, intenbl, dmaenbl, clkpresc, clkmul, trigsel, continous, period, intcompval, modenbl )
#define END_PDB_INSTANCE_CFG_MAP

#define BEGIN_LPIT_INSTANCE_CFG_MAP
#define LPIT_INST_CFG(instance, egugenbl, dozeenbl)
#define END_LPIT_INSTANCE_CFG_MAP

#define BEGIN_LPIT_CHN_MAP_CFG
#define LPIT_CHN_MAP_CFG(instance, ch, tmrmode, period, trigsrc, trigsel, rot, soi, sot, chainenbl, intenbl)
#define END_LPIT_CHN_MAP_CFG

#define BEGIN_TRIGMUX_CHN_CFG
#define TRGMUX_CHN_MAP_CFG(instance, sorce, target, lock)
#define END_TRIGMUX_CHN_CFG

#elif defined (CDDADC_DEFINE_IN_DATA_CFG)

#define BEGIN_ADC_INSTANCE_CFG_MAP
#define ADC_INST_CFG(adcinst, clkdiv, sampletime, resolution, clkin, trigger, pretriggersel, triggersel, dma, voltref, continousconv, monitoring, avgenbl, avgsmp )
#define END_ADC_INSTANCE_CFG_MAP 

#define BEGIN_ADC_CHN_MAP_CFG   static uint32 CddAdc_aulAdcChData[] = {
#define ADC_IN_CH_MAP_CFG(inputidx, adcinst,  adcchnl, inselctor, interruptenbl, pdbinst, pdbchnl, pdbdelay, pdbtrgout, pdbb2b, pdbchnlenbl, data )   0ul,
#define END_ADC_CHN_MAP_CFG  };

#define BEGIN_PDB_INSTANCE_CFG_MAP
#define PDB_INST_CFG(pdbinst, loadmod, intenbl, dmaenbl, clkpresc, clkmul, trigsel, continous, period, intcompval, modenbl )
#define END_PDB_INSTANCE_CFG_MAP

#define BEGIN_LPIT_INSTANCE_CFG_MAP
#define LPIT_INST_CFG(instance, egugenbl, dozeenbl)
#define END_LPIT_INSTANCE_CFG_MAP

#define BEGIN_LPIT_CHN_MAP_CFG
#define LPIT_CHN_MAP_CFG(instance, ch, tmrmode, period, trigsrc, trigsel, rot, soi, sot, chainenbl, intenbl)
#define END_LPIT_CHN_MAP_CFG

#define BEGIN_TRIGMUX_CHN_CFG
#define TRGMUX_CHN_MAP_CFG(instance, sorce, target, lock)
#define END_TRIGMUX_CHN_CFG


#elif defined (CDDADC_DEFINE_PDB_INSTANCE_CFG)

#define BEGIN_ADC_INSTANCE_CFG_MAP
#define ADC_INST_CFG(adcinst, clkdiv, sampletime, resolution, clkin, trigger, pretriggersel, triggersel, dma, voltref, continousconv, monitoring, avgenbl, avgsmp )
#define END_ADC_INSTANCE_CFG_MAP 

#define BEGIN_ADC_CHN_MAP_CFG
#define ADC_IN_CH_MAP_CFG(inputidx, adcinst,  adcchnl, inselctor, interruptenbl, pdbinst, pdbchnl, pdbdelay, pdbtrgout, pdbb2b, pdbchnlenbl, data )
#define END_ADC_CHN_MAP_CFG

#define BEGIN_PDB_INSTANCE_CFG_MAP  const tsCddAdc_PdbInstanceCfg CddAdc_asPdbInstCfg[] = {
#define PDB_INST_CFG(pdbinst, loadmod, intenbl, dmaenbl, clkpresc, clkmul, trigsel, continous, period, intcompval, modenbl) { pdbinst, loadmod, intenbl, dmaenbl, clkpresc, clkmul, trigsel, continous, period, intcompval, modenbl },
#define END_PDB_INSTANCE_CFG_MAP  };

#define BEGIN_LPIT_INSTANCE_CFG_MAP
#define LPIT_INST_CFG(instance, degugenbl, dozeenbl)
#define END_LPIT_INSTANCE_CFG_MAP

#define BEGIN_LPIT_CHN_MAP_CFG
#define LPIT_CHN_MAP_CFG(instance, ch, tmrmode, period, trigsrc, trigsel, rot, soi, sot, chainenbl, intenbl)
#define END_LPIT_CHN_MAP_CFG

#define BEGIN_TRIGMUX_CHN_CFG
#define TRGMUX_CHN_MAP_CFG(instance, sorce, target, lock)
#define END_TRIGMUX_CHN_CFG


#elif defined (CDDADC_DEFINE_LPIT_INSTANCE_CFG)

#define BEGIN_ADC_INSTANCE_CFG_MAP
#define ADC_INST_CFG(adcinst, clkdiv, sampletime, resolution, clkin, trigger, pretriggersel, triggersel, dma, voltref, continousconv, monitoring, avgenbl, avgsmp )
#define END_ADC_INSTANCE_CFG_MAP 

#define BEGIN_ADC_CHN_MAP_CFG
#define ADC_IN_CH_MAP_CFG(inputidx, adcinst,  adcchnl, inselctor, interruptenbl, pdbinst, pdbchnl, pdbdelay, pdbtrgout, pdbb2b, pdbchnlenbl, data )
#define END_ADC_CHN_MAP_CFG

#define BEGIN_PDB_INSTANCE_CFG_MAP
#define PDB_INST_CFG(pdbinst, loadmod, intenbl, dmaenbl, clkpresc, clkmul, trigsel, continous, period, intcompval, modenbl )
#define END_PDB_INSTANCE_CFG_MAP

#define BEGIN_LPIT_INSTANCE_CFG_MAP   const tsCddAdc_LpitInstanceCfg CddAdc_asLpitInstCfg[] = {
#define LPIT_INST_CFG(instance, degugenbl, dozeenbl)   {instance, degugenbl, dozeenbl},
#define END_LPIT_INSTANCE_CFG_MAP };

#define BEGIN_LPIT_CHN_MAP_CFG
#define LPIT_CHN_MAP_CFG(instance, ch, tmrmode, period, trigsrc, trigsel, rot, soi, sot, chainenbl, intenbl)
#define END_LPIT_CHN_MAP_CFG

#define BEGIN_TRIGMUX_CHN_CFG
#define TRGMUX_CHN_MAP_CFG(instance, sorce, target, lock)
#define END_TRIGMUX_CHN_CFG


#elif defined (CDDADC_DEFINE_LPIT_TMR_CFG)

#define BEGIN_ADC_INSTANCE_CFG_MAP
#define ADC_INST_CFG(adcinst, clkdiv, sampletime, resolution, clkin, trigger, pretriggersel, triggersel, dma, voltref, continousconv, monitoring, avgenbl, avgsmp )
#define END_ADC_INSTANCE_CFG_MAP 

#define BEGIN_ADC_CHN_MAP_CFG
#define ADC_IN_CH_MAP_CFG(inputidx, adcinst,  adcchnl, inselctor, interruptenbl, pdbinst, pdbchnl, pdbdelay, pdbtrgout, pdbb2b, pdbchnlenbl, data )
#define END_ADC_CHN_MAP_CFG

#define BEGIN_PDB_INSTANCE_CFG_MAP
#define PDB_INST_CFG(pdbinst, loadmod, intenbl, dmaenbl, clkpresc, clkmul, trigsel, continous, period, intcompval, modenbl )
#define END_PDB_INSTANCE_CFG_MAP

#define BEGIN_LPIT_INSTANCE_CFG_MAP
#define LPIT_INST_CFG(instance, degugenbl, dozeenbl)
#define END_LPIT_INSTANCE_CFG_MAP

#define BEGIN_LPIT_CHN_MAP_CFG    const tsCddAdc_LpitTmrCfg CddAdc_asLpitTmrCfg[] = {
#define LPIT_CHN_MAP_CFG(instance, ch, tmrmode, period, trigsrc, trigsel, rot, soi, sot, chainenbl, intenbl) {instance, ch, tmrmode, period, trigsrc, trigsel, rot, soi, sot, chainenbl, intenbl}
#define END_LPIT_CHN_MAP_CFG };

#define BEGIN_TRIGMUX_CHN_CFG
#define TRGMUX_CHN_MAP_CFG(instance, sorce, target, lock)
#define END_TRIGMUX_CHN_CFG

#elif defined (CDDADC_DEFINE_TRG_MUX_CFG)

#define BEGIN_ADC_INSTANCE_CFG_MAP
#define ADC_INST_CFG(adcinst, clkdiv, sampletime, resolution, clkin, trigger, pretriggersel, triggersel, dma, voltref, continousconv, monitoring, avgenbl, avgsmp )
#define END_ADC_INSTANCE_CFG_MAP 

#define BEGIN_ADC_CHN_MAP_CFG
#define ADC_IN_CH_MAP_CFG(inputidx, adcinst,  adcchnl, inselctor, interruptenbl, pdbinst, pdbchnl, pdbdelay, pdbtrgout, pdbb2b, pdbchnlenbl, data )
#define END_ADC_CHN_MAP_CFG

#define BEGIN_PDB_INSTANCE_CFG_MAP
#define PDB_INST_CFG(pdbinst, loadmod, intenbl, dmaenbl, clkpresc, clkmul, trigsel, continous, period, intcompval, modenbl )
#define END_PDB_INSTANCE_CFG_MAP

#define BEGIN_LPIT_INSTANCE_CFG_MAP
#define LPIT_INST_CFG(instance, degugenbl, dozeenbl)
#define END_LPIT_INSTANCE_CFG_MAP

#define BEGIN_LPIT_CHN_MAP_CFG
#define LPIT_CHN_MAP_CFG(instance, ch, tmrmode, period, trigsrc, trigsel, rot, soi, sot, chainenbl, intenbl)
#define END_LPIT_CHN_MAP_CFG

#define BEGIN_TRIGMUX_CHN_CFG   const tsCddAdc_TrigMuxCfg CddAdc_asTrgMuxCfg[] = {
#define TRGMUX_CHN_MAP_CFG(instance, sorce, target, lock) {instance, sorce, target, lock},
#define END_TRIGMUX_CHN_CFG   };

#else
#error "Adc configuration undefined, please select the correct one!"
#endif

// EOF

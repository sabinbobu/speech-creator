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
/// \file  Pdb_Drv.c
///
/// \brief
///
//-----------------------------------------------------------------------------

#include "Pdb_Drv.h"
#include <UtilUtility.h>
#include <../Cdd/CddAdc/Gen/CddAdc_Types.h>

static void CddAdc_PdbCfgLoad(const tsCddAdc_PdbInstanceCfg* const sPdbInstance);
static void CddAdc_PdbInitChannels(const tsCddAdc_AdcInputCfg* const sPdbChannel);
static void CddAdc_PdbInitInstance(const tsCddAdc_PdbInstanceCfg* const sPdbInstance);

Std_ReturnType CddAdc_Drv_InitPdb(tsCddAdc_CfgData sCfgData)
{
  uint8 ucPdbIdx;
  uint8 ucPdbChIndx;

  for (ucPdbIdx = 0u; ucPdbIdx < sCfgData.psPdbInstanceCfg.ucCfgLength; ucPdbIdx++)
  {
    CddAdc_PdbInitInstance(&sCfgData.psPdbInstanceCfg.psPdbInstCfg[ucPdbIdx]);
  }

  for (ucPdbChIndx = 0u; ucPdbChIndx < sCfgData.psAdcInputChCfg.ucCfgLength; ucPdbChIndx++)
  {
    CddAdc_PdbInitChannels(&sCfgData.psAdcInputChCfg.psAdcInCfg[ucPdbChIndx]);
  }

  // Load Pdb configuration and start PDB by Sw trig
  for (ucPdbIdx = 0u; ucPdbIdx < sCfgData.psPdbInstanceCfg.ucCfgLength; ucPdbIdx++)
  {
    CddAdc_PdbCfgLoad(&sCfgData.psPdbInstanceCfg.psPdbInstCfg[ucPdbIdx]);
  }

  return E_OK;
}

//-----------------------------------------------------------------------------
/// \brief CddAdc_PdbCfgLoad
///
/// \descr
///
/// \param  sPdbInstance
///
/// \return void
//-----------------------------------------------------------------------------
static void CddAdc_PdbCfgLoad(const tsCddAdc_PdbInstanceCfg* const sPdbInstance)
{
  sPdbInstance->psPdbInst->SC.Bit.PDBEN = (vuint32)((sPdbInstance->boModEnbl != FALSE) ? 1u : 0u);
  sPdbInstance->psPdbInst->SC.Bit.LDOK  = (vuint32)1u;
}

//-----------------------------------------------------------------------------
/// \brief CddAdc_PdbInitChannels
///
/// \descr
///
/// \param  sPdbChannel
///
/// \return void
//-----------------------------------------------------------------------------
static void CddAdc_PdbInitChannels(const tsCddAdc_AdcInputCfg* const sPdbChannel)
{
  uint8 ucPdbCh = sPdbChannel->ucPdbChannel;
  uint8 ucAdcCh = (sPdbChannel->ucAdcCh) % 8u;
  uint32 ulGetTso = sPdbChannel->psPdbInst->CH[ucPdbCh].C1.Bit.TOS;
  uint32 ulGetBb = sPdbChannel->psPdbInst->CH[ucPdbCh].C1.Bit.BB;
  uint32 ulGetEn = sPdbChannel->psPdbInst->CH[ucPdbCh].C1.Bit.EN;

  sPdbChannel->psPdbInst->CH[ucPdbCh].C1.Bit.TOS = (sPdbChannel->boPdbTriggerOutput != FALSE) ? (ulGetTso | (vuint32)(1u << ucAdcCh)) : (vuint32)ulGetTso;
  sPdbChannel->psPdbInst->CH[ucPdbCh].C1.Bit.BB = (sPdbChannel->boPdbBack2Back != FALSE) ? (ulGetBb | (vuint32)(1u << ucAdcCh)) : (vuint32)ulGetBb;
  sPdbChannel->psPdbInst->CH[ucPdbCh].C1.Bit.EN = (sPdbChannel->boPdbAdcChnEnbl != FALSE) ? (ulGetEn | (vuint32)(1u << ucAdcCh)) : (vuint32)ulGetEn;

  sPdbChannel->psPdbInst->CH[ucPdbCh].DLY[ucAdcCh].Bit.DLY = (vuint32)sPdbChannel->ulPdbChnInDelayOffset_Reg;
}

//-----------------------------------------------------------------------------
/// \brief CddAdc_PdbInitInstance
///
/// \descr
///
/// \param  sPdbInstance
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
static void CddAdc_PdbInitInstance(const tsCddAdc_PdbInstanceCfg* const sPdbInstance)
{
  sPdbInstance->psPdbInst->SC.Bit.LDMOD = (vuint32)sPdbInstance->eLdMod;

  sPdbInstance->psPdbInst->SC.Bit.PDBIE = (vuint32)(((sPdbInstance->boIntEnable != FALSE) || (sPdbInstance->boDmaEnable != FALSE)) ? 1u : 0u);
  sPdbInstance->psPdbInst->SC.Bit.DMAEN = (vuint32)((sPdbInstance->boDmaEnable != FALSE) ? 1u : 0u);
  sPdbInstance->psPdbInst->SC.Bit.PDBEIE = (vuint32)1u;
  sPdbInstance->psPdbInst->SC.Bit.PRESCALER = (vuint32)(sPdbInstance->ePrescaler);
  sPdbInstance->psPdbInst->SC.Bit.MULT = (vuint32)(sPdbInstance->eMul);
  sPdbInstance->psPdbInst->SC.Bit.TRGSEL = (vuint32)(sPdbInstance->eTrigger);
  sPdbInstance->psPdbInst->SC.Bit.CONT = (vuint32)((sPdbInstance->boContinousMode != FALSE) ? 1u : 0u);
  sPdbInstance->psPdbInst->MOD.Bit.MOD = (vuint32)sPdbInstance->ulPdbPeriod_Reg;
  sPdbInstance->psPdbInst->IDLY.Bit.IDLY = (vuint32)sPdbInstance->ulIntDmaTrigTime_Reg;
}


//-----------------------------------------------------------------------------
/// \brief PDB0_IRQHandler
///
/// \descr
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void PDB0_IRQHandler(void)
{
  tsCddAdc_PdbReg* PdbBaseAddresses = PDB0;
  PdbBaseAddresses->SC.Bit.PDBEN = (vuint32)0u;
  PdbBaseAddresses->CH[0].S.Bit.ERR = (vuint32)0u;
  PdbBaseAddresses->CH[1].S.Bit.ERR = (vuint32)0u;
  PdbBaseAddresses->SC.Bit.PDBEN = (vuint32)1u;
  PdbBaseAddresses->SC.Bit.SWTRIG = (vuint32)1u;
}

//-----------------------------------------------------------------------------
/// \brief PDB1_IRQHandler
///
/// \descr
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void PDB1_IRQHandler(void)
{
  tsCddAdc_PdbReg* PdbBaseAddresses = PDB1;
  PdbBaseAddresses->SC.Bit.PDBEN = (vuint32)0u;
  PdbBaseAddresses->CH[0].S.Bit.ERR = (vuint32)0u;
  PdbBaseAddresses->CH[1].S.Bit.ERR = (vuint32)0u;
  PdbBaseAddresses->SC.Bit.PDBEN = (vuint32)1u;
  PdbBaseAddresses->SC.Bit.SWTRIG = (vuint32)1u;
}
// EOF

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
/// \file  Lpit_Drv.c
///
/// \brief
///
//-----------------------------------------------------------------------------

#include "Lpit_Drv.h"
#include <UtilUtility.h>
#include <../Cdd/CddAdc/Gen/CddAdc_Types.h>

static void CddAdc_Drv_LpitSetTmrEnblBit(const tsCddAdc_LpitTmrCfg* const sLpitTmr, uint32 ulEnblBit);
static void CddAdc_Drv_LpitSetDebugMode(tsCddAdc_LpitReg* const sLpitInst, uint32 ulDbgBit);
static void CddAdc_Drv_LpitSetDozeMode(tsCddAdc_LpitReg* const sLpitInst, uint32 ulDozeBit);
static void CddAdc_Drv_LpitSetModEnblStat(tsCddAdc_LpitReg* const sLpitInst, uint32 ulEnblBit);
static void CddAdc_Drv_LpitSetTmrChMode(const tsCddAdc_LpitTmrCfg* const sLpitTmr, uint32 ulTmrMode);
static void CddAdc_Drv_LpitSetTmrChTrigSrc(const tsCddAdc_LpitTmrCfg* const sLpitTmr, uint32 ulTrigSrc);
static void CddAdc_Drv_LpitSetTmrChTrigSel(const tsCddAdc_LpitTmrCfg* const sLpitTmr, uint32 ulTrigSel);
static void CddAdc_Drv_LpitSetTmrChRoT(const tsCddAdc_LpitTmrCfg* const sLpitTmr, uint32 ulReloadOnTrg);
static void CddAdc_Drv_LpitSetTmrChSoI(const tsCddAdc_LpitTmrCfg* const sLpitTmr, uint32 ulStartOnInt);
static void CddAdc_Drv_LpitSetTmrChSoT(const tsCddAdc_LpitTmrCfg* const sLpitTmr, uint32 ulStartOnTrg);
static void CddAdc_Drv_LpitSetTmrChChain(const tsCddAdc_LpitTmrCfg* const sLpitTmr, uint32 ulChainEnbl);
static void CddAdc_Drv_LpitSetTmrChIntEnbl(const tsCddAdc_LpitTmrCfg* const sLpitTmr, uint32 ulChainEnbl);
static void CddAdc_Drv_LpitSetTmrChCompVal(const tsCddAdc_LpitTmrCfg* const sLpitTmr, uint32 ulCompVal);
static void CddAdc_LpitSetTmrEnable(const tsCddAdc_LpitTmrCfg* const sLpitTmr, boolean boEnblStat);
static void CddAdc_InitLpitTmrChn(const tsCddAdc_LpitTmrCfg* const sLpitTmr);
static void CddAdc_InitLpitInstance(tsCddAdc_LpitInstanceCfg * const sLpitInstance);

//-----------------------------------------------------------------------------
/// \brief CddAdc_InitLpit
///
/// \descr
///
/// \param  -
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType CddAdc_Drv_InitLpit(tsCddAdc_CfgData sCfgData)
{
  uint8 ucLpitInstIx;
  uint8 ucLpitTmrIx;

  for (ucLpitInstIx = 0u; ucLpitInstIx < sCfgData.psLpitInstanceCfg.ucCfgLength; ucLpitInstIx++)
  {
    CddAdc_InitLpitInstance(&sCfgData.psLpitInstanceCfg.psLpitInstCfg[ucLpitInstIx]);
  }

  for (ucLpitTmrIx = 0u; ucLpitTmrIx < sCfgData.psLpitTmrCfg.ucCfgLength; ucLpitTmrIx++)
  {
    CddAdc_InitLpitTmrChn(&sCfgData.psLpitTmrCfg.psLpitTmrCfg[ucLpitTmrIx]);
  }

  return E_OK;
}

//-----------------------------------------------------------------------------
/// \brief CddAdc_LpitSetTmrEnable
///
/// \descr
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
static void CddAdc_LpitSetTmrEnable(const tsCddAdc_LpitTmrCfg* const sLpitTmr, boolean boEnblStat)
{
  CddAdc_Drv_LpitSetTmrEnblBit(sLpitTmr, (boEnblStat != FALSE) ? 1u : 0u);
}

//-----------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param  sLpitTmr
///
/// \return void
//-----------------------------------------------------------------------------
static void CddAdc_InitLpitTmrChn(const tsCddAdc_LpitTmrCfg* const sLpitTmr)
{
  uint8 ucChnNr = sLpitTmr->ucChnNr;

  CddAdc_Drv_LpitSetTmrChMode(sLpitTmr, (uint32)sLpitTmr->eTimerMode);
  CddAdc_Drv_LpitSetTmrChTrigSrc(sLpitTmr, (uint32)sLpitTmr->eTriggerSrc);
  CddAdc_Drv_LpitSetTmrChTrigSel(sLpitTmr, (uint32)sLpitTmr->eTriggerSel);
  CddAdc_Drv_LpitSetTmrChRoT(sLpitTmr, (sLpitTmr->boReloadOnTrigger != FALSE) ? 1u : 0u);
  CddAdc_Drv_LpitSetTmrChSoI(sLpitTmr, (sLpitTmr->boStopOnInterrupt != FALSE) ? 1u : 0u);
  CddAdc_Drv_LpitSetTmrChSoT(sLpitTmr, (sLpitTmr->boStopOnInterrupt != FALSE) ? 1u : 0u);
  CddAdc_Drv_LpitSetTmrChChain(sLpitTmr, (sLpitTmr->boChainChannel != FALSE) ? 1u : 0u);
  CddAdc_Drv_LpitSetTmrChIntEnbl(sLpitTmr, (sLpitTmr->boIntEnbl != FALSE) ? 1u : 0u);
  CddAdc_Drv_LpitSetTmrChCompVal(sLpitTmr, (uint32)sLpitTmr->ulPeriod_Reg);
  CddAdc_LpitSetTmrEnable(sLpitTmr, TRUE);
}

//-----------------------------------------------------------------------------
/// \brief CddAdc_InitLpitInstance
///
/// \descr
///
/// \param  sLpitInstance
///
/// \return void
//-----------------------------------------------------------------------------
static void CddAdc_InitLpitInstance(tsCddAdc_LpitInstanceCfg * const sLpitInstance)
{
  CddAdc_Drv_LpitSetDebugMode(sLpitInstance->psLpitInst, (sLpitInstance->boEnableDebug != FALSE) ? 1u : 0u);
  CddAdc_Drv_LpitSetDozeMode(sLpitInstance->psLpitInst, (sLpitInstance->boEnableDoze != FALSE) ? 1u : 0u);
  CddAdc_Drv_LpitSetModEnblStat(sLpitInstance->psLpitInst, 1u);
}

//-----------------------------------------------------------------------------
/// \brief CddAdc_Drv_LpitSetTmrChCompVal
///
/// \descr
///
/// \param  sLpitTmr
/// \param  ulCompVal
///
/// \return void
//-----------------------------------------------------------------------------
static void CddAdc_Drv_LpitSetTmrChCompVal(const tsCddAdc_LpitTmrCfg* const sLpitTmr, uint32 ulCompVal)
{
  uint8 ucChnNr = sLpitTmr->ucChnNr;
  vuint32 ulRegValue = sLpitTmr->psLpitInst->TMR[ucChnNr].TVAL.Reg;

  ulRegValue = ulCompVal;

  sLpitTmr->psLpitInst->TMR[ucChnNr].TVAL.Reg = ulRegValue;
}


//-----------------------------------------------------------------------------
/// \brief CddAdc_Drv_LpitSetTmrChIntEnbl
///
/// \descr
///
/// \param  sLpitTmr
/// \param  ulChainEnbl
///
/// \return void
//-----------------------------------------------------------------------------
static void CddAdc_Drv_LpitSetTmrChIntEnbl(const tsCddAdc_LpitTmrCfg* const sLpitTmr, uint32 ulChainEnbl)
{
  uint8 ucChnNr = sLpitTmr->ucChnNr;
  vuint32 ulRegValue = sLpitTmr->psLpitInst->MIER.Reg;

  switch (ucChnNr)
  {
    case 0u: 
      ulRegValue = ulRegValue & 0xFFFFFFFEu;
      ulRegValue = ulRegValue | (ulChainEnbl << 0u);
    break;
    case 1u:
      ulRegValue = ulRegValue & 0xFFFFFFFDu;
      ulRegValue = ulRegValue | (ulChainEnbl << 1u);
    break;
    case 2u:
      ulRegValue = ulRegValue & 0xFFFFFFFBu;
      ulRegValue = ulRegValue | (ulChainEnbl << 2u);
    break;
    case 3u:
      ulRegValue = ulRegValue & 0xFFFFFFF7u;
      ulRegValue = ulRegValue | (ulChainEnbl << 3u);
    break;
    default: break;
  }

  sLpitTmr->psLpitInst->MIER.Reg = ulRegValue;
}

//-----------------------------------------------------------------------------
/// \brief CddAdc_Drv_LpitSetTmrChChain
///
/// \descr
///
/// \param  sLpitTmr
/// \param  ulChainEnbl
///
/// \return void
//-----------------------------------------------------------------------------
static void CddAdc_Drv_LpitSetTmrChChain(const tsCddAdc_LpitTmrCfg* const sLpitTmr, uint32 ulChainEnbl)
{
  uint8 ucChnNr = sLpitTmr->ucChnNr;

  vuint32 ulRegValue = sLpitTmr->psLpitInst->TMR[ucChnNr].TCTRL.Reg;

  ulRegValue = ulRegValue & 0xFFFFFFFDu;
  ulRegValue = ulRegValue | (ulChainEnbl << 1u);

  sLpitTmr->psLpitInst->TMR[ucChnNr].TCTRL.Reg = ulRegValue;
}

//-----------------------------------------------------------------------------
/// \brief CddAdc_Drv_LpitSetTmrChSoT
///
/// \descr
///
/// \param  sLpitTmr
/// \param  ulStartOnTrg
///
/// \return void
//-----------------------------------------------------------------------------
static void CddAdc_Drv_LpitSetTmrChSoT(const tsCddAdc_LpitTmrCfg* const sLpitTmr, uint32 ulStartOnTrg)
{
  uint8 ucChnNr = sLpitTmr->ucChnNr;

  vuint32 ulRegValue = sLpitTmr->psLpitInst->TMR[ucChnNr].TCTRL.Reg;

  ulRegValue = ulRegValue & 0xFFFEFFFFu;
  ulRegValue = ulRegValue | (ulStartOnTrg << 16u);

  sLpitTmr->psLpitInst->TMR[ucChnNr].TCTRL.Reg = ulRegValue;
}

//-----------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param  sLpitTmr
/// \param  ulStartOnInt
///
/// \return void
//-----------------------------------------------------------------------------
static void CddAdc_Drv_LpitSetTmrChSoI(const tsCddAdc_LpitTmrCfg* const sLpitTmr, uint32 ulStartOnInt)
{
  uint8 ucChnNr = sLpitTmr->ucChnNr;

  vuint32 ulRegValue = sLpitTmr->psLpitInst->TMR[ucChnNr].TCTRL.Reg;

  ulRegValue = ulRegValue & 0xFFFDFFFFu;
  ulRegValue = ulRegValue | (ulStartOnInt << 17u);

  sLpitTmr->psLpitInst->TMR[ucChnNr].TCTRL.Reg = ulRegValue;
}

//-----------------------------------------------------------------------------
/// \brief CddAdc_Drv_LpitSetTmrChRoT
///
/// \descr
///
/// \param  sLpitTmr
/// \param  ulReloadOnTrg
///
/// \return void
//-----------------------------------------------------------------------------
static void CddAdc_Drv_LpitSetTmrChRoT(const tsCddAdc_LpitTmrCfg* const sLpitTmr, uint32 ulReloadOnTrg)
{
  uint8 ucChnNr = sLpitTmr->ucChnNr;

  vuint32 ulRegValue = sLpitTmr->psLpitInst->TMR[ucChnNr].TCTRL.Reg;

  ulRegValue = ulRegValue & 0xFFFBFFFFu;
  ulRegValue = ulRegValue | (ulReloadOnTrg << 18u);

  sLpitTmr->psLpitInst->TMR[ucChnNr].TCTRL.Reg = ulRegValue;
}

//-----------------------------------------------------------------------------
/// \brief CddAdc_Drv_LpitSetTmrChTrigSel
///
/// \descr
///
/// \param  sLpitTmr
/// \param  ulTrigSel
///
/// \return void
//-----------------------------------------------------------------------------
static void CddAdc_Drv_LpitSetTmrChTrigSel(const tsCddAdc_LpitTmrCfg* const sLpitTmr, uint32 ulTrigSel)
{
  uint8 ucChnNr = sLpitTmr->ucChnNr;

  vuint32 ulRegValue = sLpitTmr->psLpitInst->TMR[ucChnNr].TCTRL.Reg;

  ulRegValue = ulRegValue & 0xF0FFFFFFu;
  ulRegValue = ulRegValue | (ulTrigSel << 24u);

  sLpitTmr->psLpitInst->TMR[ucChnNr].TCTRL.Reg = ulRegValue;
}

//-----------------------------------------------------------------------------
/// \brief CddAdc_Drv_LpitSetTmrChTrigSrc
///
/// \descr
///
/// \param  sLpitTmr
/// \param  ulTrigSel
///
/// \return void
//-----------------------------------------------------------------------------
static void CddAdc_Drv_LpitSetTmrChTrigSrc(const tsCddAdc_LpitTmrCfg* const sLpitTmr, uint32 ulTrigSrc)
{
  uint8 ucChnNr = sLpitTmr->ucChnNr;

  vuint32 ulRegValue = sLpitTmr->psLpitInst->TMR[ucChnNr].TCTRL.Reg;

  ulRegValue = ulRegValue & 0xFF7FFFFFu;
  ulRegValue = ulRegValue | (ulTrigSrc << 23u);

  sLpitTmr->psLpitInst->TMR[ucChnNr].TCTRL.Reg = ulRegValue;
}


//-----------------------------------------------------------------------------
/// \brief CddAdc_Drv_LpitSetTmrChMode
///
/// \descr
///
/// \param  sLpitTmr
/// \param  ulTmrMode
///
/// \return void
//-----------------------------------------------------------------------------
static void CddAdc_Drv_LpitSetTmrChMode(const tsCddAdc_LpitTmrCfg* const sLpitTmr, uint32 ulTmrMode)
{
  uint8 ucChnNr = sLpitTmr->ucChnNr;

  vuint32 ulRegValue = sLpitTmr->psLpitInst->TMR[ucChnNr].TCTRL.Reg;

  ulRegValue = ulRegValue & 0xFFFFFFF3u;
  ulRegValue = ulRegValue | (ulTmrMode << 2u);

  sLpitTmr->psLpitInst->TMR[ucChnNr].TCTRL.Reg = ulRegValue;
}


//-----------------------------------------------------------------------------
/// \brief CddAdc_Drv_LpitSetDebugMode
///
/// \descr
///
/// \param  sLpitInst
/// \param  ulEnblBit
///
/// \return void
//-----------------------------------------------------------------------------
static void CddAdc_Drv_LpitSetDebugMode(tsCddAdc_LpitReg* const sLpitInst, uint32 ulDbgBit)
{
  vuint32 ulRegValue = sLpitInst->MCR.Reg;

  ulRegValue = ulRegValue & 0xFFFFFFF7u;
  ulRegValue = ulRegValue | (ulDbgBit << 3u);

  sLpitInst->MCR.Reg = ulRegValue;
}

//-----------------------------------------------------------------------------
/// \brief CddAdc_Drv_LpitSetDozeMode
///
/// \descr
///
/// \param  sLpitInst
/// \param  ulEnblBit
///
/// \return void
//-----------------------------------------------------------------------------
static void CddAdc_Drv_LpitSetDozeMode(tsCddAdc_LpitReg* const sLpitInst, uint32 ulDozelBit)
{
  vuint32 ulRegValue = sLpitInst->MCR.Reg;

  ulRegValue = ulRegValue & 0xFFFFFFFBu;
  ulRegValue = ulRegValue | (ulDozelBit << 2u);

  sLpitInst->MCR.Reg = ulRegValue;
}

//-----------------------------------------------------------------------------
/// \brief CddAdc_Drv_LpitSetModEnblStat
///
/// \descr
///
/// \param  sLpitInst
/// \param  ulEnblBit
///
/// \return void
//-----------------------------------------------------------------------------
static void CddAdc_Drv_LpitSetModEnblStat(tsCddAdc_LpitReg* const sLpitInst, uint32 ulEnblBit)
{
  uint32 ulRegValue = sLpitInst->MCR.Reg;

  ulRegValue = ulRegValue & 0xFFFFFFFEu;
  ulRegValue = ulRegValue | (ulEnblBit << 0u);

  sLpitInst->MCR.Reg = ulRegValue;
}

//-----------------------------------------------------------------------------
/// \brief CddAdc_Drv_LpitSetTmrEnblBit
///
/// \descr
///
/// \param  sLpitTmr
/// \param  ulEnblBit
///
/// \return void
//-----------------------------------------------------------------------------
static void CddAdc_Drv_LpitSetTmrEnblBit(const tsCddAdc_LpitTmrCfg* const sLpitTmr, uint32 ulEnblBit)
{
  uint8 ucChnNr = sLpitTmr->ucChnNr;
  vuint32 ulRegValue = sLpitTmr->psLpitInst->TMR[ucChnNr].TCTRL.Reg;
  
  ulRegValue = ulRegValue & 0xFFFFFFFEu;
  ulRegValue = ulRegValue | (ulEnblBit << 0u);

  sLpitTmr->psLpitInst->TMR[ucChnNr].TCTRL.Reg = ulRegValue;
}
// EOF

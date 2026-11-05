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
/// \brief Lpit Driver file (low access to the Lpit pheripheric)
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

#include "Lpit_Drv.h"
#include <UtilUtility.h>
#include "Lpit_TargetTypes.h"

#ifdef UNIT_TEST
#include <Lpit_reg_stubs.h>
#endif

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

#define LPIT_DRV_MSR_CLRTOF_BIT_MASK          0xFFFFFFFEu
#define LPIT_DRV_MIER_CH0INTEN_BIT_MASK       0xFFFFFFFEu
#define LPIT_DRV_MIER_CH1INTEN_BIT_MASK       0xFFFFFFFDu
#define LPIT_DRV_MIER_CH2INTEN_BIT_MASK       0xFFFFFFFBu
#define LPIT_DRV_MIER_CH3INTEN_BIT_MASK       0xFFFFFFF7u
#define LPIT_DRV_TCTRL_CHAINENBL_BIT_MASK     0xFFFFFFFDu
#define LPIT_DRV_TCTRL_SOT_BIT_MASK           0xFFFEFFFFu
#define LPIT_DRV_TCTRL_SOI_BIT_MASK           0xFFFDFFFFu
#define LPIT_DRV_TCTRL_CHEN_BIT_MASK          0xFFFFFFFEu
#define LPIT_DRV_TCTRL_ROT_BIT_MASK           0xFFFBFFFFu
#define LPIT_DRV_TCTRL_TRIGSEL_BIT_MASK       0xF0FFFFFFu
#define LPIT_DRV_TCTRL_TRIGSRC_BIT_MASK       0xFF7FFFFFu
#define LPIT_DRV_TCTRL_CHMODE_BIT_MASK        0xFFFFFFF3u
#define LPIT_DRV_MCR_DBGEN_BIT_MASK           0xFFFFFFF7u
#define LPIT_DRV_MCR_DOZE_BIT_MASK            0xFFFFFFFBu
#define LPIT_DRV_MCR_MODEN_BIT_MASK           0xFFFFFFFEu
#define LPIT_DRV_MIER_CHnINTEN_BIT_MAX_VAL    0x1u
#define LPIT_DRV_TCTRL_CHAINENBL_BIT_MAX_VAL  0x1u
#define LPIT_DRV_TCTRL_SOT_BIT_MAX_VAL        0x1u
#define LPIT_DRV_TCTRL_SOI_BIT_MAX_VAL        0x1u
#define LPIT_DRV_TCTRL_ROT_BIT_MAX_VAL        0x1u
#define LPIT_DRV_TCTRL_TRIGSEL_BIT_MAX_VAL    0xFu
#define LPIT_DRV_TCTRL_TRIGSRC_BIT_MAX_VAL    0x1u
#define LPIT_DRV_TCTRL_CHMODE_BIT_MAX_VAL     0x3u
#define LLPIT_DRV_MCR_DBGEN_BIT_MAX_VAL       0x1u
#define LPIT_DRV_MCR_DOZE_BIT_MAX_VAL         0x1u
#define LPIT_DRV_MCR_MODEN_BIT_MAX_VAL        0x1u
#define LPIT_DRV_TCTRL_CHEN_BIT_MAX_VAL       0x1u
#define LPIT_DRV_ENABLE_BIT                   1u
#define LPIT_DRV_DISABLE_BIT                  0u
#define LPIT_DRV_MSR_CLRTOF_BIT_POS           0u
#define LPIT_DRV_MIER_CH0INTEN_BIT_POS        0u
#define LPIT_DRV_MIER_CH1INTEN_BIT_POS        1u
#define LPIT_DRV_MIER_CH2INTEN_BIT_POS        2u
#define LPIT_DRV_MIER_CH3INTEN_BIT_POS        3u
#define LPIT_DRV_TCTRL_CHAINENBL_BIT_POS      1u
#define LPIT_DRV_TCTRL_SOT_BIT_POS            16u
#define LPIT_DRV_TCTRL_SOI_BIT_POS            17u
#define LPIT_DRV_TCTRL_ROT_BIT_POS            18u
#define LPIT_DRV_TCTRL_TRIGSEL_BIT_POS        24u
#define LPIT_DRV_TCTRL_TRIGSRC_BIT_POS        23u
#define LPIT_DRV_TCTRL_CHMODE_BIT_POS         2u
#define LPIT_DRV_MCR_DBGEN_BIT_POS            3u
#define LPIT_DRV_MCR_DOZE_BIT_POS             2u
#define LPIT_DRV_MCR_MODEN_BIT_POS            0u
#define LPIT_DRV_TCTRL_CHEN_BIT_POS           0u

//====================================================================
// Local functions declaration
//====================================================================

STATIC_AL void Lpit_Drv_LpitSetDebugMode    (LPIT_Type* CONST_AL psLpitInst, uint32 ulDbgBit);
STATIC_AL void Lpit_Drv_LpitSetDozeMode     (LPIT_Type* CONST_AL psLpitInst, uint32 ulDozeBit);
STATIC_AL void Lpit_Drv_LpitSetModEnblStat  (LPIT_Type* CONST_AL psLpitInst, uint32 ulEnblBit);
STATIC_AL void Lpit_Drv_LpitSetTmrChMode    (CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, uint32 ulTmrMode);
STATIC_AL void Lpit_Drv_LpitSetTmrChTrigSrc (CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, uint32 ulTrigSrc);
STATIC_AL void Lpit_Drv_LpitSetTmrChTrigSel (CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, uint32 ulTrigSel);
STATIC_AL void Lpit_Drv_LpitSetTmrChRoT     (CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, uint32 ulReloadOnTrg);
STATIC_AL void Lpit_Drv_LpitSetTmrChSoI     (CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, uint32 ulStartOnInt);
STATIC_AL void Lpit_Drv_LpitSetTmrChSoT     (CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, uint32 ulStartOnTrg);
STATIC_AL void Lpit_Drv_LpitSetTmrChChain   (CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, uint32 ulChainEnbl);
STATIC_AL void Lpit_LpitSetTmrEnable        (CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, boolean boEnblStat);
STATIC_AL void Lpit_InitLpitTmrChn          (CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr);
STATIC_AL void Lpit_InitLpitInstance        (CONST_AL tsLpit_LpitInstanceCfg * CONST_AL psLpitInstance);

//====================================================================
// Functions definitions
//====================================================================

//-----------------------------------------------------------------------------
/// \brief Lpit_InitLpit
///
/// \descr Lpit Instances/channels init procedure
///
/// \param  sLpitCfgData - Lpit config stucture (channel and structures)
///
/// \return Std_ReturnType - always return E_OK
//-----------------------------------------------------------------------------
Std_ReturnType Lpit_Drv_Init(CONST_AL tsLpit_CfgData* CONST_AL psLpitCfgData)
{
  // Lpit instance index
  uint8 ucLpitInstIx = 0u;
  // Lpit Timer channel index
  uint8 ucLpitTmrIx = 0u;

  // Lpit instances init
  for (ucLpitInstIx = 0u; ucLpitInstIx < psLpitCfgData->sLpitInstanceCfg.ucCfgLength; ucLpitInstIx++)
  {
    Lpit_InitLpitInstance(&psLpitCfgData->sLpitInstanceCfg.psLpitInstCfg[ucLpitInstIx]);
  }

  // Lpit Timer channels init
  for (ucLpitTmrIx = 0u; ucLpitTmrIx < psLpitCfgData->sLpitTmrCfg.ucCfgLength; ucLpitTmrIx++)
  {
    Lpit_InitLpitTmrChn(&psLpitCfgData->sLpitTmrCfg.sLpitTmrCfg[ucLpitTmrIx]);
  }

  return E_OK;
}

//-----------------------------------------------------------------------------
/// \brief Lpit_LpitSetTmrEnable
///
/// \descr Timer Instance enable/disable procedure
///
/// \param psLpitTmr - LPIT timer global config. structure
/// \param boEnblStat - Enable Status (enable/disable)
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Lpit_LpitSetTmrEnable(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, boolean boEnblStat)
{
  // Call LL set/clear timer enable bit
  Lpit_Drv_LpitSetTmrEnblBit(psLpitTmr, (boEnblStat != FALSE) ? LPIT_DRV_ENABLE_BIT : LPIT_DRV_DISABLE_BIT);
}

//-----------------------------------------------------------------------------
/// \brief Lpit_InitLpitTmrChn
///
/// \descr Timer Channel n Initialization procedure
///
/// \param  psLpitTmr - LPIT timer global config. structure
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Lpit_InitLpitTmrChn(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr)
{
  // Get Timer channel number
  uint8 ucChnNr = psLpitTmr->ucChnNr;

  // Set Timer Mode
  Lpit_Drv_LpitSetTmrChMode     (psLpitTmr, (uint32)psLpitTmr->eTimerMode);
  // Set Timer trigger source
  Lpit_Drv_LpitSetTmrChTrigSrc  (psLpitTmr, (uint32)psLpitTmr->eTriggerSrc);
  // Configure Timer trigger selector
  Lpit_Drv_LpitSetTmrChTrigSel  (psLpitTmr, (uint32)psLpitTmr->eTriggerSel);
  // Configure Channel Reload on Trigger 
  Lpit_Drv_LpitSetTmrChRoT      (psLpitTmr, (psLpitTmr->boReloadOnTrigger != FALSE) ? LPIT_DRV_ENABLE_BIT : LPIT_DRV_DISABLE_BIT);
  // Configure Channel Start on Interrupt
  Lpit_Drv_LpitSetTmrChSoI      (psLpitTmr, (psLpitTmr->boStopOnInterrupt != FALSE) ? LPIT_DRV_ENABLE_BIT : LPIT_DRV_DISABLE_BIT);
  // Configure Channel Start on Trigger
  Lpit_Drv_LpitSetTmrChSoT      (psLpitTmr, (psLpitTmr->boStartOnTrigger != FALSE) ? LPIT_DRV_ENABLE_BIT : LPIT_DRV_DISABLE_BIT);
  // Configure Channel Chain
  Lpit_Drv_LpitSetTmrChChain    (psLpitTmr, (psLpitTmr->boChainChannel != FALSE) ? LPIT_DRV_ENABLE_BIT : LPIT_DRV_DISABLE_BIT);
  // Configure Channel Interrupt Enable
  Lpit_Drv_LpitSetTmrChIntEnbl  (psLpitTmr, (psLpitTmr->boIntEnbl != FALSE) ? LPIT_DRV_ENABLE_BIT : LPIT_DRV_DISABLE_BIT);
  // Update Channel Compare Value
  Lpit_Drv_LpitSetTmrChCompVal  (psLpitTmr, (uint32)psLpitTmr->ulPeriod_Reg);
  // Enable Lpit Timer Instance
  Lpit_LpitSetTmrEnable         (psLpitTmr, TRUE);

  // PRQA S 5324 1 // HIS metrics violation suppressed (STCAL = 10)
}

//-----------------------------------------------------------------------------
/// \brief Lpit_InitLpitInstance
///
/// \descr Lpit Instance Init procedure
///
/// \param  sLpitInstance - Lpit config stucture (instances)
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Lpit_InitLpitInstance(CONST_AL tsLpit_LpitInstanceCfg * CONST_AL psLpitInstance)
{
  // LPIT instance temp
  LPIT_Type *psLpitInst = NULL_PTR;

  // Set LPIT instance
  // PRQA S 306 1 //Cast between a pointer and an integral type need to access peripheral uC registers
  psLpitInst = (psLpitInstance->ucLpitInst == 0u) ? LPIT0 : NULL_PTR;

  // LPIT instance valid
  if (psLpitInst != NULL_PTR)
  {
    // Configure Debug Mode
    Lpit_Drv_LpitSetDebugMode   (psLpitInst, (psLpitInstance->boEnableDebug != FALSE) ? LPIT_DRV_ENABLE_BIT : LPIT_DRV_DISABLE_BIT);
    // Configure Doze Mode
    Lpit_Drv_LpitSetDozeMode    (psLpitInst, (psLpitInstance->boEnableDoze != FALSE)  ? LPIT_DRV_ENABLE_BIT : LPIT_DRV_DISABLE_BIT);
    // Configure Module Enable
    Lpit_Drv_LpitSetModEnblStat (psLpitInst, (psLpitInstance->boEnableModule != FALSE) ? LPIT_DRV_ENABLE_BIT : LPIT_DRV_DISABLE_BIT);
  }
  else
  {
    // NULL_PTR, avoid wrong access
  }
}

//-----------------------------------------------------------------------------
/// \brief Lpit_Drv_LpitSetTmrChCompVal
///
/// \descr Timer Comapre value (period) update procedure
///
/// \param  sLpitTmr - Timer Config Structure
/// \param  ulCompVal - Compare Value (Tick Period)
///
/// \return void
//-----------------------------------------------------------------------------
void Lpit_Drv_LpitSetTmrChCompVal(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, uint32 ulCompVal)
{
  // LPIT instance temp
  LPIT_Type   *psLpitInstance = NULL_PTR;
  // Temp Channel Number
  uint8       ucChnNr = 0u;

  // Set LPIT instance
  // PRQA S 306 1 //Cast between a pointer and an integral type need to access peripheral uC registers
  psLpitInstance = (psLpitTmr->ucLpitInst == 0u) ? LPIT0 : NULL_PTR;

  // Get Channel Number
  ucChnNr = psLpitTmr->ucChnNr;

  // LPIT instance valid
  if (psLpitInstance != NULL_PTR)
  {
    // Update TVAL register with Compare value
    psLpitInstance->TMR[ucChnNr].TVAL = ulCompVal;
  }
  else
  {
    // NULL_PTR, avoid wrong access
  }
}

//-----------------------------------------------------------------------------
/// \brief Lpit_Drv_LpitClearTimeout
///
/// \descr Clear Time-Out Flag in MSR register procedure
///
/// \param  sLpitTmr - Timer Config Structure
///
/// \return void
//-----------------------------------------------------------------------------
void Lpit_Drv_LpitClearTimeout(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr)
{
  // LPIT instance temp
  LPIT_Type   *psLpitInstance = NULL_PTR;
  // Temp Register Value
  vuint32     ulRegValue = 0u;
  // Temp Channel Number
  uint8       ucChnNr = 0u;

  // Get Channel Number
  ucChnNr = psLpitTmr->ucChnNr;

  // Set LPIT instance
  // PRQA S 306 1 //Cast between a pointer and an integral type need to access peripheral uC registers
  psLpitInstance = (psLpitTmr->ucLpitInst == 0u) ? LPIT0 : NULL_PTR;

  // LPIT instance valid
  if (psLpitInstance != NULL_PTR)
  {
    // Read MSR register
    ulRegValue = psLpitInstance->MSR;
    // Clear TOF bitfield in MSR register (write by 1)
    ulRegValue &= LPIT_DRV_MSR_CLRTOF_BIT_MASK;
    ulRegValue |= ((uint32)LPIT_DRV_ENABLE_BIT << LPIT_DRV_MSR_CLRTOF_BIT_POS);
    // Update MSR register
    psLpitInstance->MSR = ulRegValue;
  }
  else
  {
    // NULL_PTR, avoid wrong access
  }
}

//-----------------------------------------------------------------------------
/// \brief Lpit_Drv_LpitSetTmrChIntEnbl
///
/// \descr Lpit Channel Interrupt enable procedure
///
/// \param  psLpitTmr - LPIT Timer configuration
/// \param  ulIntEnbl - Enable Channel Interrupt Enable bit
///
/// \return void
//-----------------------------------------------------------------------------
void Lpit_Drv_LpitSetTmrChIntEnbl(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, uint32 ulIntEnbl)
{
  // LPIT instance temp
  LPIT_Type   *psLpitInstance = NULL_PTR;
  // Temp Register Value
  vuint32     ulRegValue = 0u;
  // Temp Channel Number
  uint8       ucChnNr = 0u;

  // Get channel number
  ucChnNr = psLpitTmr->ucChnNr;

  // Set LPIT instance
  // PRQA S 306 1 //Cast between a pointer and an integral type need to access peripheral uC registers
  psLpitInstance = (psLpitTmr->ucLpitInst == 0u) ? LPIT0 : NULL_PTR;

  // LPIT instance valid and configuration ok
  if ((psLpitInstance != NULL_PTR) && (ulIntEnbl <= LPIT_DRV_MIER_CHnINTEN_BIT_MAX_VAL))
  {
    // Get MIER register value
    ulRegValue = psLpitInstance->MIER;

    // LPIT channel
    switch (ucChnNr)
    {
      case 0u:
        // Clear Ch0 Int Enable Bit
        ulRegValue &= LPIT_DRV_MIER_CH0INTEN_BIT_MASK;
        // Write Ch0 Int Enable Bit
        ulRegValue |= (ulIntEnbl << LPIT_DRV_MIER_CH0INTEN_BIT_POS);
        break;
      case 1u:
        // Clear Ch1 Int Enable Bit
        ulRegValue &= LPIT_DRV_MIER_CH1INTEN_BIT_MASK;
        // Write Ch1 Int Enable Bit
        ulRegValue |= (ulIntEnbl << LPIT_DRV_MIER_CH1INTEN_BIT_POS);
        break;
      case 2u:
        // Clear Ch2 Int Enable Bit
        ulRegValue &= LPIT_DRV_MIER_CH2INTEN_BIT_MASK;
        // Write Ch2 Int Enable Bit
        ulRegValue |= (ulIntEnbl << LPIT_DRV_MIER_CH2INTEN_BIT_POS);
        break;
      case 3u:
        // Clear Ch3 Int Enable Bit
        ulRegValue &= LPIT_DRV_MIER_CH3INTEN_BIT_MASK;
        // Write Ch3 Int Enable Bit
        ulRegValue |= (ulIntEnbl << LPIT_DRV_MIER_CH3INTEN_BIT_POS);
        break;
      default: break;
    }

    // Update MIER register value
    psLpitInstance->MIER = ulRegValue;
  }
  else
  {
    // NULL_PTR, avoid wrong access, config not ok
  }
}

//-----------------------------------------------------------------------------
/// \brief Lpit_Drv_LpitSetTmrChChain
///
/// \descr Timer Chain enable procedure
///
/// \param  psLpitTmr - LPIT Timer configuration
/// \param  ulChainEnbl - Chain Enable Bit
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Lpit_Drv_LpitSetTmrChChain(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, uint32 ulChainEnbl)
{
  // LPIT instance temp
  LPIT_Type   *psLpitInstance = NULL_PTR;
  // Temp Register Value
  vuint32     ulRegValue = 0u;
  // Temp Channel Number
  uint8       ucChnNr = 0u;

  // Get Timer Channel Number
  ucChnNr = psLpitTmr->ucChnNr;

  // Set LPIT instance
  // PRQA S 306 1 //Cast between a pointer and an integral type need to access peripheral uC registers
  psLpitInstance = (psLpitTmr->ucLpitInst == 0u) ? LPIT0 : NULL_PTR;

  // LPIT instance valid and configuration ok
  if((psLpitInstance != NULL_PTR) && (ulChainEnbl <= LPIT_DRV_TCTRL_CHAINENBL_BIT_MAX_VAL))
  {
    // Get TCTRL register value
    ulRegValue = psLpitInstance->TMR[ucChnNr].TCTRL;
    // Clear CHAINENBL bit field in TCTRL register
    ulRegValue &= LPIT_DRV_TCTRL_CHAINENBL_BIT_MASK;
    // Set CHAINENBL bit in TCTRL register
    ulRegValue |= (ulChainEnbl << LPIT_DRV_TCTRL_CHAINENBL_BIT_POS);
    // Update TCTRL register
    psLpitInstance->TMR[ucChnNr].TCTRL = ulRegValue;
  }
  else
  {
    // NULL_PTR, avoid wrong access, config not ok
  }
}

//-----------------------------------------------------------------------------
/// \brief Lpit_Drv_LpitSetTmrChSoT
///
/// \descr Channel Start on Trigger configure procedure
///
/// \param  psLpitTmr - LPIT Timer configuration
/// \param  ulStartOnTrg - Start on Trigger bit configuration
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Lpit_Drv_LpitSetTmrChSoT(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, uint32 ulStartOnTrg)
{
  // LPIT instance temp
  LPIT_Type   *psLpitInstance = NULL_PTR;
  // Temp Register Value
  vuint32     ulRegValue = 0u;
  // Temp Channel Number
  uint8       ucChnNr = 0u;

  //  Get channel number
  ucChnNr = psLpitTmr->ucChnNr;

  // Set LPIT instance
  // PRQA S 306 1 //Cast between a pointer and an integral type need to access peripheral uC registers
  psLpitInstance = (psLpitTmr->ucLpitInst == 0u) ? LPIT0 : NULL_PTR;

  // LPIT instance valid and configuration ok
  if ((psLpitInstance != NULL_PTR) && (ulStartOnTrg <= LPIT_DRV_TCTRL_SOT_BIT_MAX_VAL))
  {
    // Get TCTRL register value
    ulRegValue = psLpitInstance->TMR[ucChnNr].TCTRL;
    // Clear SOT bit field in TCTRL register
    ulRegValue &= LPIT_DRV_TCTRL_SOT_BIT_MASK;
    // Write SOT bit in TCTRL register
    ulRegValue |= (ulStartOnTrg << LPIT_DRV_TCTRL_SOT_BIT_POS);
    // Update TCTRL register
    psLpitInstance->TMR[ucChnNr].TCTRL = ulRegValue;
  }
  else
  {
    // NULL_PTR, avoid wrong access, config not ok
  }
}

//-----------------------------------------------------------------------------
/// \brief Lpit_Drv_LpitSetTmrChSoI
///
/// \descr  Channel Start on Interrupt configure procedure
///
/// \param  sLpitTmr - LPIT Timer configuration
/// \param  ulStartOnInt - Start on Interrupt bit configuration
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Lpit_Drv_LpitSetTmrChSoI(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, uint32 ulStartOnInt)
{
  // LPIT instance temp
  LPIT_Type   *psLpitInstance = NULL_PTR;
  // Temp Register Value
  vuint32     ulRegValue = 0u;
  // Temp Channel Number
  uint8       ucChnNr = 0u;

  //  Get channel number
  ucChnNr = psLpitTmr->ucChnNr;

  // Set LPIT instance
  // PRQA S 306 1 //Cast between a pointer and an integral type need to access peripheral uC registers
  psLpitInstance = (psLpitTmr->ucLpitInst == 0u) ? LPIT0 : NULL_PTR;

  // LPIT instance valid and configuration ok
  if ((psLpitInstance != NULL_PTR) && (ulStartOnInt <= LPIT_DRV_TCTRL_SOI_BIT_MAX_VAL))
  {
    // Get TCTRL register value
    ulRegValue = psLpitInstance->TMR[ucChnNr].TCTRL;
    // Clear SOI bit field in TCTRL register
    ulRegValue &= LPIT_DRV_TCTRL_SOI_BIT_MASK;
    // Write SOT bit in TCTRL register
    ulRegValue |= (ulStartOnInt << LPIT_DRV_TCTRL_SOI_BIT_POS);
    // Update TCTRL register
    psLpitInstance->TMR[ucChnNr].TCTRL = ulRegValue;
  }
  else
  {
    // NULL_PTR, avoid wrong access, config not ok
  }
}

//-----------------------------------------------------------------------------
/// \brief Lpit_Drv_LpitSetTmrChRoT
///
/// \descr Channel Reload on Trigger configure procedure
///
/// \param  sLpitTmr - LPIT Timer configuration
/// \param  ulReloadOnTrg - Reload on Trigger bit configuration
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Lpit_Drv_LpitSetTmrChRoT(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, uint32 ulReloadOnTrg)
{
  // LPIT instance temp
  LPIT_Type   *psLpitInstance = NULL_PTR;
  // Temp Register Value
  vuint32     ulRegValue = 0u;
  // Temp Channel Number
  uint8       ucChnNr = 0u;

  //  Get channel number
  ucChnNr = psLpitTmr->ucChnNr;

  // Set LPIT instance
  // PRQA S 306 1 //Cast between a pointer and an integral type need to access peripheral uC registers
  psLpitInstance = (psLpitTmr->ucLpitInst == 0u) ? LPIT0 : NULL_PTR;

  // LPIT instance valid and configuration ok
  if ((psLpitInstance != NULL_PTR) && (ulReloadOnTrg <= LPIT_DRV_TCTRL_ROT_BIT_MAX_VAL))
  {
    // Get TCTRL register value
    ulRegValue = psLpitInstance->TMR[ucChnNr].TCTRL;
    // Clear ROT bit field in TCTRL register
    ulRegValue &= LPIT_DRV_TCTRL_ROT_BIT_MASK;
    // Write ROT bit in TCTRL register
    ulRegValue |= (ulReloadOnTrg << LPIT_DRV_TCTRL_ROT_BIT_POS);
    // Update TCTRL register
    psLpitInstance->TMR[ucChnNr].TCTRL = ulRegValue;
  }
  else
  {
    // NULL_PTR, avoid wrong access, config not ok
  }
}

//-----------------------------------------------------------------------------
/// \brief Lpit_Drv_LpitSetTmrChTrigSel
///
/// \descr Timer Channel Triger Selection procedure
///
/// \param  sLpitTmr - LPIT Timer configuration
/// \param  ulTrigSel - Trigger Selector configuration
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Lpit_Drv_LpitSetTmrChTrigSel(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, uint32 ulTrigSel)
{
  // LPIT instance temp
  LPIT_Type   *psLpitInstance = NULL_PTR;
  // Temp Register Value
  vuint32     ulRegValue = 0u;
  // Temp Channel Number
  uint8       ucChnNr = 0u;

  // Get channel number
  ucChnNr = psLpitTmr->ucChnNr;

  // Set LPIT instance
  // PRQA S 306 1 //Cast between a pointer and an integral type need to access peripheral uC registers
  psLpitInstance = (psLpitTmr->ucLpitInst == 0u) ? LPIT0 : NULL_PTR;

  // LPIT instance valid and configuration ok
  if ((psLpitInstance != NULL_PTR) && (ulTrigSel <= LPIT_DRV_TCTRL_TRIGSEL_BIT_MAX_VAL))
  {
    // Get TCTRL register value
    ulRegValue = psLpitInstance->TMR[ucChnNr].TCTRL;
    // Clear TRIGSEL bit field in TCTRL register
    ulRegValue &= LPIT_DRV_TCTRL_TRIGSEL_BIT_MASK;
    // Write TRIGSEL bit in TCTRL register
    ulRegValue |= (ulTrigSel << LPIT_DRV_TCTRL_TRIGSEL_BIT_POS);
    // Update TCTRL register
    psLpitInstance->TMR[ucChnNr].TCTRL = ulRegValue;
  }
  else
  {
    // NULL_PTR, avoid wrong access, config not ok
  }
}

//-----------------------------------------------------------------------------
/// \brief Lpit_Drv_LpitSetTmrChTrigSrc
///
/// \descr LPIT Timer Trigger Source selector procedure (HW/SW)
///
/// \param  sLpitTmr - LPIT Timer configuration
/// \param  ulTrigSrc - Timer Trigger Source
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Lpit_Drv_LpitSetTmrChTrigSrc(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, uint32 ulTrigSrc)
{
  // LPIT instance temp
  LPIT_Type   *psLpitInstance = NULL_PTR;
  // Temp Register Value
  vuint32     ulRegValue = 0u;
  // Temp Channel Number
  uint8       ucChnNr = 0u;

  // Get channel number
  ucChnNr = psLpitTmr->ucChnNr;

  // Set LPIT instance
  // PRQA S 306 1 //Cast between a pointer and an integral type need to access peripheral uC registers
  psLpitInstance = (psLpitTmr->ucLpitInst == 0u) ? LPIT0 : NULL_PTR;

  // LPIT instance valid and configuration ok
  if ((psLpitInstance != NULL_PTR) && (ulTrigSrc <= LPIT_DRV_TCTRL_TRIGSRC_BIT_MAX_VAL))
  {
    // Get TCTRL register value
    ulRegValue = psLpitInstance->TMR[ucChnNr].TCTRL;
    // Clear TRIGSRC bit field in TCTRL register
    ulRegValue &= LPIT_DRV_TCTRL_TRIGSRC_BIT_MASK;
    // Write TRIGSRC bit in TCTRL register
    ulRegValue |= (ulTrigSrc << LPIT_DRV_TCTRL_TRIGSRC_BIT_POS);
    // Update TCTRL register
    psLpitInstance->TMR[ucChnNr].TCTRL = ulRegValue;
  }
  else
  {
    // NULL_PTR, avoid wrong access, config not ok
  }
}

//-----------------------------------------------------------------------------
/// \brief Lpit_Drv_LpitSetTmrChMode
///
/// \descr LPIT Channel Mode Setup procedure
///
/// \param  sLpitTmr - LPIT Timer configuration
/// \param  ulTmrMode - Timer Mode
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Lpit_Drv_LpitSetTmrChMode(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, uint32 ulTmrMode)
{
  // LPIT instance temp
  LPIT_Type   *psLpitInstance = NULL_PTR;
  // Temp Register Value
  vuint32     ulRegValue = 0u;
  // Temp Channel Number
  uint8       ucChnNr = 0u;

  // Get channel number
  ucChnNr = psLpitTmr->ucChnNr;

  // Set LPIT instance
  // PRQA S 306 1 //Cast between a pointer and an integral type need to access peripheral uC registers
  psLpitInstance = (psLpitTmr->ucLpitInst == 0u) ? LPIT0 : NULL_PTR;

  // LPIT instance valid and configuration ok
  if ((psLpitInstance != NULL_PTR) && (ulTmrMode <= LPIT_DRV_TCTRL_CHMODE_BIT_MAX_VAL))
  {
    // Get TCTRL register value
    ulRegValue = psLpitInstance->TMR[ucChnNr].TCTRL;
    // Clear CHMODE bit field in TCTRL register
    ulRegValue &= LPIT_DRV_TCTRL_CHMODE_BIT_MASK;
    // Write CHMODE bit in TCTRL register
    ulRegValue |= (ulTmrMode << LPIT_DRV_TCTRL_CHMODE_BIT_POS);
    // Update TCTRL register
    psLpitInstance->TMR[ucChnNr].TCTRL = ulRegValue;
  }
  else
  {
    // NULL_PTR, avoid wrong access, config not ok
  }
}

//-----------------------------------------------------------------------------
/// \brief Lpit_Drv_LpitSetDebugMode
///
/// \descr LPIT instance set debug mode procedure
///
/// \param  sLpitInst - LPIT instance
/// \param  ulEnblBit - Debug Enable Bit
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Lpit_Drv_LpitSetDebugMode(LPIT_Type* CONST_AL psLpitInst, uint32 ulDbgBit)
{
  // LPIT instance valid and configuration ok
  if ((psLpitInst != NULL_PTR) && (ulDbgBit <= LLPIT_DRV_MCR_DBGEN_BIT_MAX_VAL))
  {
    // Temp Register Value
    vuint32     ulRegValue = 0u;

    // Get MCR register value
    ulRegValue = psLpitInst->MCR;
    // Clear DBGEN bit field in MCR register
    ulRegValue &= LPIT_DRV_MCR_DBGEN_BIT_MASK;
    // Write DBGEN bit in MCR register
    ulRegValue |= (ulDbgBit << LPIT_DRV_MCR_DBGEN_BIT_POS);
    // Update MCR register
    psLpitInst->MCR = ulRegValue;
  }
  else
  {
    // NULL_PTR, avoid wrong access, config not ok
  }
}

//-----------------------------------------------------------------------------
/// \brief Lpit_Drv_LpitSetDozeMode
///
/// \descr LPIT instance set doze mode procedure
///
/// \param  sLpitInst - LPIT instance
/// \param  ulDozeBit - Doze Enable Bit
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Lpit_Drv_LpitSetDozeMode(LPIT_Type* CONST_AL psLpitInst, uint32 ulDozeBit)
{
  // LPIT instance valid and configuration ok
  if ((psLpitInst != NULL_PTR) && (ulDozeBit <= LPIT_DRV_MCR_DOZE_BIT_MAX_VAL))
  {
    // Temp Register Value
    vuint32     ulRegValue = 0u;

    // Get MCR register value
    ulRegValue = psLpitInst->MCR;
    // Clear DOZE bit field in MCR register
    ulRegValue &= LPIT_DRV_MCR_DOZE_BIT_MASK;
    // Write DOZE bit in MCR register
    ulRegValue |= (ulDozeBit << LPIT_DRV_MCR_DOZE_BIT_POS);
    // Update MCR register
    psLpitInst->MCR = ulRegValue;
  }
  else
  {
    // NULL_PTR, avoid wrong access, config not ok
  }
}

//-----------------------------------------------------------------------------
/// \brief Lpit_Drv_LpitSetModEnblStat
///
/// \descr LPIT Module Enable set procedure
///
/// \param  sLpitInst - LPIT instance module
/// \param  ulEnblBit - Module Enable Bit
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Lpit_Drv_LpitSetModEnblStat(LPIT_Type* CONST_AL psLpitInst, uint32 ulEnblBit)
{
  // LPIT instance valid and configuration ok
  if ((psLpitInst != NULL_PTR) && (ulEnblBit <= LPIT_DRV_MCR_MODEN_BIT_MAX_VAL))
  {
    // Temp Register Value
    vuint32     ulRegValue = 0u;

    // Get MCR register value
    ulRegValue = psLpitInst->MCR;
    // Clear MODEN bit field in MCR register
    ulRegValue &= LPIT_DRV_MCR_MODEN_BIT_MASK;
    // Write MODEN bit in MCR register
    ulRegValue |= (ulEnblBit << LPIT_DRV_MCR_MODEN_BIT_POS);
    // Update MCR register
    psLpitInst->MCR = ulRegValue;
  }
  else
  {
    // NULL_PTR, avoid wrong access, config not ok
  }
}

//-----------------------------------------------------------------------------
/// \brief Lpit_Drv_LpitSetTmrEnblBit
///
/// \descr LPIT Timer Channel Enable procedure
///
/// \param  sLpitTmr - LPIT Timer configuration
/// \param  ulEnblBit - Timer Enable Bit
///
/// \return void
//-----------------------------------------------------------------------------
void Lpit_Drv_LpitSetTmrEnblBit(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, uint32 ulEnblBit)
{
  // LPIT instance temp
  LPIT_Type   *psLpitInstance = NULL_PTR;
  // Temp Register Value
  vuint32     ulRegValue = 0u;
  // Temp Channel Number
  uint8       ucChnNr = 0u;

  // Get channel number
  ucChnNr = psLpitTmr->ucChnNr;

  // Set LPIT instance
  // PRQA S 306 1 //Cast between a pointer and an integral type need to access peripheral uC registers
  psLpitInstance = (psLpitTmr->ucLpitInst == 0u) ? LPIT0 : NULL_PTR;

  // LPIT instance valid and configuration ok
  if ((psLpitInstance != NULL_PTR) && (ulEnblBit <= LPIT_DRV_TCTRL_CHEN_BIT_MAX_VAL))
  {
    // Get TCTRL register value
    ulRegValue = psLpitInstance->TMR[ucChnNr].TCTRL;
    // Clear CHEN bit field in TCTRL register
    ulRegValue &= LPIT_DRV_TCTRL_CHEN_BIT_MASK;
    // Write CHMEN bit in TCTRL register
    ulRegValue |= (ulEnblBit << LPIT_DRV_TCTRL_CHEN_BIT_POS);
    // Update TCTRL register
    psLpitInstance->TMR[ucChnNr].TCTRL = ulRegValue;
  }
  else
  {
    // NULL_PTR, avoid wrong access, config not ok
  }
}

/// \brief Lpit_Drv_LpitReturnCount
///
/// \descr Timer value return its value procedure
///
/// \param  sLpitTmr - LPIT Timer configuration
///
/// \return void
//-----------------------------------------------------------------------------
uint32 Lpit_Drv_LpitReturnCount(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr)
{
  // LPIT instance temp
  LPIT_Type   *psLpitInstance = NULL_PTR;
  // Temp Register Value
  vuint32     ulRegValue = 0u;
  // Temp Channel Number
  uint8       ucChnNr = 0u;

  // Get channel number
  ucChnNr = psLpitTmr->ucChnNr;

  // Set LPIT instance
  // PRQA S 306 1 //Cast between a pointer and an integral type need to access peripheral uC registers
  psLpitInstance = (psLpitTmr->ucLpitInst == 0u) ? LPIT0 : NULL_PTR;

  // LPIT instance valid
  if (psLpitInstance != NULL_PTR)
  {
    // Get Timer Cnt Value
     ulRegValue = psLpitInstance->TMR[ucChnNr].CVAL;
  }
  else
  {
    // NULL_PTR, avoid wrong access
  }

  return (ulRegValue);
}


//-----------------------------------------------------------------------------
/// \brief Lpit_Drv_ClearInterruptFlag
///
/// \descr Interrupt clear flag
///
/// \param  ucInstance - LPIT timer instance
/// \param  ucTimer - Timer channel
///
/// \return void
//-----------------------------------------------------------------------------
void Lpit_Drv_ClearInterruptFlag(uint8 ucInstance, uint8 ucTimer)
{
  // LPIT instance temp
  LPIT_Type   *psLpitInstance = NULL_PTR;

  // Temp Register Value
  vuint32     ulRegValue = 0u;

  // Set LPIT instance
   // PRQA S 306 1 //Cast between a pointer and an integral type need to access peripheral uC registers
  psLpitInstance = (ucInstance == 0u) ? LPIT0 : NULL_PTR;
 
  if (psLpitInstance != NULL_PTR)
  {
    ulRegValue = 0u;
    ulRegValue = (uint32)((uint32)1u << ucTimer);
    psLpitInstance->MSR = ulRegValue;
  }
  else
  {
    // instance not correct, skip 
  }

}

//-----------------------------------------------------------------------------
/// \brief Lpit_Drv_TimerChannelEnable
///
/// \descr LPIT Timer channel enable procedure
///
/// \param  ucInstance - LPIT instance
/// \param  ucTimer - 
///
/// \return void
//-----------------------------------------------------------------------------
void Lpit_Drv_TimerChannelEnable(uint8 ucInstance, uint8 ucTimer)
{
  // LPIT instance temp
  LPIT_Type   *psLpitInstance = NULL_PTR;

  // Temp Register Value
  vuint32     ulRegValue = 0u;

  // Set LPIT instance
   // PRQA S 306 1 //Cast between a pointer and an integral type need to access peripheral uC registers
  psLpitInstance = (ucInstance == 0u) ? LPIT0 : NULL_PTR;

  if (psLpitInstance != NULL_PTR)
  {
    ulRegValue = psLpitInstance->SETTEN;
    ulRegValue |= (uint32)((uint32)1u << ucTimer);
    psLpitInstance->SETTEN = ulRegValue;
  }
  else
  {
    // instance not correct, skip 
  }
}

// EOF

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

#if defined (CPU_S32K142)
  #include <S32K142.h>
#elif defined (CPU_S32K144)
  #include <S32K144.h>
#elif defined (CPU_S32K146)
  #include <S32K146.h>
#endif

#if defined (UNIT_TEST)
#include "Lpit_reg_stubs.h"
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

STATIC_AL void Lpit_Drv_LpitSetDebugMode(LPIT_Type* CONST_AL psLpitInst, uint32 ulDbgBit);
STATIC_AL void Lpit_Drv_LpitSetDozeMode(LPIT_Type* CONST_AL psLpitInst, uint32 ulDozeBit);
STATIC_AL void Lpit_Drv_LpitSetModEnblStat(LPIT_Type* CONST_AL psLpitInst, uint32 ulEnblBit);
STATIC_AL void Lpit_Drv_LpitSetTmrChMode(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, uint32 ulTmrMode);
STATIC_AL void Lpit_Drv_LpitSetTmrChTrigSrc(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, uint32 ulTrigSrc);
STATIC_AL void Lpit_Drv_LpitSetTmrChTrigSel(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, uint32 ulTrigSel);
STATIC_AL void Lpit_Drv_LpitSetTmrChRoT(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, uint32 ulReloadOnTrg);
STATIC_AL void Lpit_Drv_LpitSetTmrChSoI(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, uint32 ulStartOnInt);
STATIC_AL void Lpit_Drv_LpitSetTmrChSoT(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, uint32 ulStartOnTrg);
STATIC_AL void Lpit_Drv_LpitSetTmrChChain(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, uint32 ulChainEnbl);
STATIC_AL void Lpit_LpitSetTmrEnable(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, boolean boEnblStat);
STATIC_AL void Lpit_InitLpitTmrChn(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr);
STATIC_AL void Lpit_InitLpitInstance(CONST_AL tsLpit_LpitInstanceCfg * CONST_AL psLpitInstance);

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
  return;
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
  return;
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
  return;
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
  return;
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
  return;
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
  return;
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
  return;
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
  return;
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
  return;
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
  return;
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
  return;
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
  return;
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
  return;
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
  return;
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
  return;
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
  return;
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
  return;
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
  return;
}

// EOF

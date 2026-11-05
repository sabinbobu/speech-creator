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
/// \brief Lpit Driver file (low access to the PDB pheripheric)
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

#include "Pdb_Drv.h"
#include <UtilUtility.h>
#include "Pdb_TargetTypes.h"

#if defined (CPU_S32K142)
  #include <S32K142.h>
#elif defined (CPU_S32K144)
  #include <S32K144.h>
#elif defined (CPU_S32K146)
  #include <S32K146.h>
#endif

#if defined (UNIT_TEST)
#include "Pdb_reg_stubs.h"
#endif

//====================================================================
// Defines
//====================================================================

#define PDB_DRV_CHn_DLY_MASK                  0xFFFF0000u
#define PDB_DRV_SC_ENBL_MASK                  0xFFFFFF7Fu
#define PDB_DRV_SC_LDOK_MASK                  0xFFFFFFFEu
#define PDB_DRV_SC_LDMOD_MASK                 0xFFFCFFFFu
#define PDB_DRV_SC_INTEN_MASK                 0xFFFFFFDFu
#define PDB_DRV_SC_DMAEN_MASK                 0xFFFF7FFFu
#define PDB_DRV_SC_ERRINT_EN_MASK             0xFFFDFFFFu
#define PDB_DRV_SC_PRSC_MASK                  0xFFFF8FFFu
#define PDB_DRV_SC_MUL_MASK                   0xFFFFFFF3u
#define PDB_DRV_SC_TRIGSEL_MASK               0xFFFFF0FFu
#define PDB_DRV_SC_CONT_MASK                  0xFFFFFFFDu
#define PDB_DRV_MOD_MOD_MASK                  0xFFFF0000u
#define PDB_DRV_IDLY_IDLY_MASK                0xFFFF0000u
#define PDB_DRV_PDB_CHn_ERR_MASK              0xFFFFFF00u
#define PDB_DRV_ENABLE_BIT                    1u
#define PDB_DRV_DISABLE_BIT                   0u
#define PDB_DRV_MAX_ADC_CHN_PDB_IN            8u
#define PDB_DRV_CHn_DLY_POS                   0u
#define PDB_DRV_CHn_DLY_VAL_MAX               0xFFFFu
#define PDB_DRV_SC_ENBL_VAL_MAX               0x1u
#define PDB_DRV_SC_LDOK_VAL_MAX               0x1u
#define PDB_DRV_CHn_C1_EN_VAL_MAX             0x1u
#define PDB_DRV_CHn_C1_BB_VAL_MAX             0x1u
#define PDB_DRV_CHn_C1_TOS_VAL_MAX            0x1u
#define PDB_DRV_SC_LDMOD_VAL_MAX              0x3u
#define PDB_DRV_SC_DMAEN_VAL_MAX              0x1u
#define PDB_DRV_SC_ERRINT_EN_VAL_MAX          0x1u
#define PDB_DRV_SC_INTEN_VAL_MAX              0x1u
#define PDB_DRV_SC_PRSC_VAL_MAX               0x7u
#define PDB_DRV_SC_MUL_VAL_MAX                0x3u
#define PDB_DRV_SC_TRIGSEL_VAL_MAX            0xFu
#define PDB_DRV_SC_CONT_VAL_MAX               0x1u
#define PDB_DRV_MOD_MOD_MAX_VAL               0xFFFFu
#define PDB_DRV_IDLY_IDLY_MAX_VAL             0xFFFFu
#define PDB_DRV_PDB_CH_MAX                    2u
#define PDB_DRV_SC_ENBL_POS                   7u
#define PDB_DRV_SC_LDOK_POS                   0u
#define PDB_DRV_CHn_C1_EN_OFFSET_MASK         0u
#define PDB_DRV_CHn_C1_BB_OFFSET_MASK         16u
#define PDB_DRV_CHn_C1_TOS_OFFSET_MASK        8u
#define PDB_DRV_SC_LDMOD_POS                  18u
#define PDB_DRV_SC_INTEN_VAL_POS              5u
#define PDB_DRV_SC_DMAEN_POS                  15u
#define PDB_DRV_SC_ERRINT_EN_POS              17u
#define PDB_DRV_SC_PRSC_POS                   12u
#define PDB_DRV_SC_MUL_POS                    2u
#define PDB_DRV_SC_TRIGSEL_POS                8u
#define PDB_DRV_SC_CONT_POS                   1u
#define PDB_DRV_MOD_MOD_POS                   0u
#define PDB_DRV_IDLY_IDLY_POS                 0u

//====================================================================
// Local functions declaration
//====================================================================

STATIC_AL void Pdb_Drv_PdbSetPdbEnbl(PDB_Type* CONST_AL psPdbInstance, uint32 ulPdbEnbl);
STATIC_AL void Pdb_Drv_PdbSetPdbChTos(CONST_AL tsPdb_PdbInputCfg* CONST_AL psPdbChannel, uint32 ulTos);
STATIC_AL void Pdb_Drv_PdbSetPdbChBb(CONST_AL tsPdb_PdbInputCfg* CONST_AL psPdbChannel, uint32 ulBb);
STATIC_AL void Pdb_Drv_PdbSetPdbChEn(CONST_AL tsPdb_PdbInputCfg* CONST_AL psPdbChannel, uint32 ulEn);
STATIC_AL void Pdb_Drv_PdbSetPdbChDly(CONST_AL tsPdb_PdbInputCfg* CONST_AL psPdbChannel, uint32 ulDly);
STATIC_AL void Pdb_Drv_PdbSetPdbLdOk(PDB_Type* CONST_AL psPdbInstance, uint32 ulLdok);
STATIC_AL void Pdb_Drv_PdbSetPdbLdMod(PDB_Type* CONST_AL psPdbInstance, uint32 ulLdMod);
STATIC_AL void Pdb_Drv_PdbSetPdbIntEn(PDB_Type* CONST_AL psPdbInstance, uint32 ulIntEn);
STATIC_AL void Pdb_Drv_PdbSetPdbDmaEn(PDB_Type* CONST_AL psPdbInstance, uint32 ulDmaEn);
STATIC_AL void Pdb_Drv_PdbSetPdbErrIntEn(PDB_Type* CONST_AL psPdbInstance, uint32 ulErrIntEn);
STATIC_AL void Pdb_Drv_PdbSetPdbPrescaler(PDB_Type* CONST_AL psPdbInstance, uint32 ulPrescaler);
STATIC_AL void Pdb_Drv_PdbSetPdbMult(PDB_Type* CONST_AL psPdbInstance, uint32 ulMult);
STATIC_AL void Pdb_Drv_PdbSetPdbTrigSel(PDB_Type* CONST_AL psPdbInstance, uint32 ulTrigSel);
STATIC_AL void Pdb_Drv_PdbSetPdbContinous(PDB_Type* CONST_AL psPdbInstance, uint32 ulContinous);
STATIC_AL void Pdb_Drv_PdbSetPdbTmrMod(PDB_Type* CONST_AL psPdbInstance, uint32 ulTmrMod);
STATIC_AL void Pdb_Drv_PdbSetPdbTmrIdly(PDB_Type* CONST_AL psPdbInstance, uint32 ulTmrIdly);
STATIC_AL void Pdb_Drv_PdbClearChErr(PDB_Type* CONST_AL psPdbInstance, uint8 ucChn);
STATIC_AL void Pdb_Drv_CfgLoad(CONST_AL tsPdb_PdbInstanceCfg* CONST_AL psPdbInstance);
STATIC_AL void Pdb_Drv_InitChannels(CONST_AL tsPdb_PdbInputCfg* CONST_AL psPdbChannel);
STATIC_AL void Pdb_Drv_InitInstance(CONST_AL tsPdb_PdbInstanceCfg* CONST_AL psPdbInstance);

//-----------------------------------------------------------------------------
/// \brief Pdb_Drv_Init
///
/// \descr Loe Level Pdb driver Init
///
/// \param  sPdbCfgData - PDB global data config
///
/// \return Std_ReturnType - always returns E_OK
//-----------------------------------------------------------------------------
Std_ReturnType Pdb_Drv_Init(CONST_AL tsPdb_CfgData* CONST_AL psPdbDataCfg)
{
  return E_OK;
}

//-----------------------------------------------------------------------------
/// \brief Pdb_Drv_CfgLoad
///
/// \descr Load Pdb configuration procedure
///
/// \param  psPdbInstance - PDB instance
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Pdb_Drv_CfgLoad(CONST_AL tsPdb_PdbInstanceCfg* CONST_AL psPdbInstance)
{
  return;
}

//-----------------------------------------------------------------------------
/// \brief Pdb_Drv_InitChannels
///
/// \descr Pdb Channels initialization procedure
///
/// \param  sPdbChannel - Pdb Channel configuration data input
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Pdb_Drv_InitChannels(CONST_AL tsPdb_PdbInputCfg* CONST_AL psPdbChannel)
{
  return;
}

//-----------------------------------------------------------------------------
/// \brief Pdb_Drv_InitInstance
///
/// \descr PDB init driver
///
/// \param  psPdbInstance
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void Pdb_Drv_InitInstance(CONST_AL tsPdb_PdbInstanceCfg* CONST_AL psPdbInstance)
{
  return;
}

//-----------------------------------------------------------------------------
/// \brief PDB0_IRQHandler
///
/// \descr PDB0 Error Interrupt handler. PDB0 is reset in case of some PDB-ADC conversion errors
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void PDB0_IRQHandler(void)
{
  return;
}

//-----------------------------------------------------------------------------
/// \brief PDB1_IRQHandler
///
/// \descr PDB1 Error Interrupt handler. PDB1 is reset in case of some PDB-ADC conversion errors
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void PDB1_IRQHandler(void)
{
  return;
}

//-----------------------------------------------------------------------------
/// \brief Pdb_Drv_PdbSetPdbChDly
///
/// \descr PDB Delay Timer configuration procedure
///
/// \param  psPdbChannel - PDB channel
/// \param  ulDly - Delay raw value
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Pdb_Drv_PdbSetPdbChDly(CONST_AL tsPdb_PdbInputCfg* CONST_AL psPdbChannel, uint32 ulDly)
{
  return;
}

//-----------------------------------------------------------------------------
/// \brief Pdb_Drv_PdbSetPdbEnbl
///
/// \descr Pdb Global Enable procedure
///
/// \param  psPdbInstance - PDB instance
/// \param  ulPdbEnbl - Pdb Enable Bit
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Pdb_Drv_PdbSetPdbEnbl(PDB_Type* CONST_AL psPdbInstance, uint32 ulPdbEnbl)
{
  return;
}

//-----------------------------------------------------------------------------
/// \brief Pdb_Drv_PdbSetPdbLdOk
///
/// \descr PDB Load Ok configure procedure
///
/// \param  psPdbInstance - PDB instance
/// \param  ulLdok - LDOK bit
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Pdb_Drv_PdbSetPdbLdOk(PDB_Type* CONST_AL psPdbInstance, uint32 ulLdok)
{
  return;
}

//-----------------------------------------------------------------------------
/// \brief Pdb_Drv_PdbSetPdbChEn
///
/// \descr PDB Channel enable procedure
///
/// \param  psPdbChannel - PDB channel data structure
/// \param  ulEn - PDB channel enable
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Pdb_Drv_PdbSetPdbChEn(CONST_AL tsPdb_PdbInputCfg* CONST_AL psPdbChannel, uint32 ulEn)
{
  return;
}

//-----------------------------------------------------------------------------
/// \brief Pdb_Drv_PdbSetPdbChBb
///
/// \descr PDB Channel Back to Back configuration procedure
///
/// \param  sPdbChannel - PDB channel data structure
/// \param  ulBb - Back to Back Bit enable
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Pdb_Drv_PdbSetPdbChBb(CONST_AL tsPdb_PdbInputCfg* CONST_AL psPdbChannel, uint32 ulBb)
{
  return;
}

//-----------------------------------------------------------------------------
/// \brief Pdb_Drv_PdbSetPdbChTos
///
/// \descr PDB Trigger Output Selct configuration procedure
///
/// \param  sPdbChannel - PDB channel data structure
/// \param  ulTos - TOS bit enable
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Pdb_Drv_PdbSetPdbChTos(CONST_AL tsPdb_PdbInputCfg* CONST_AL psPdbChannel, uint32 ulTos)
{
  return;
}

//-----------------------------------------------------------------------------
/// \brief Pdb_Drv_PdbSetPdbLdMod
///
/// \descr PDB Load Mode configuration procedure
///
/// \param  psPdbInstance - PDB channel data structure
/// \param  ulLdMod - Load Mode Bit config
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Pdb_Drv_PdbSetPdbLdMod(PDB_Type* CONST_AL psPdbInstance, uint32 ulLdMod)
{
  return;
}

//-----------------------------------------------------------------------------
/// \brief Pdb_Drv_PdbSetPdbIntEn
///
/// \descr PDB Interrupt Enable procedure
///
/// \param  psPdbInstance - PDB instance
/// \param  ulIntEn - Interrupt Enable Bit
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Pdb_Drv_PdbSetPdbIntEn(PDB_Type* CONST_AL psPdbInstance, uint32 ulIntEn)
{
  return;
}

//-----------------------------------------------------------------------------
/// \brief  Pdb_Drv_PdbSetPdbDmaEn
///
/// \descr PDB DMA request enable procedure
///
/// \param  psPdbInstance  - PDB instance
/// \param  ulDmaEn - DMA enable bit
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Pdb_Drv_PdbSetPdbDmaEn(PDB_Type* CONST_AL psPdbInstance, uint32 ulDmaEn)
{
  return;
}

//-----------------------------------------------------------------------------
/// \brief Pdb_Drv_PdbSetPdbErrIntEn
///
/// \descr PDB error interrupt enable procedure
///
/// \param  psPdbInstance - PDB instance
/// \param  ulErrIntEn - Error interrupt enable
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Pdb_Drv_PdbSetPdbErrIntEn(PDB_Type* CONST_AL psPdbInstance, uint32 ulErrIntEn)
{
  return;
}

//-----------------------------------------------------------------------------
/// \brief Pdb_Drv_PdbSetPdbPrescaler
///
/// \descr PDB Clock prescaler set procedure
///
/// \param  psPdbInstance - PDB instance
/// \param  ulPrescaler - PDB precaler value
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Pdb_Drv_PdbSetPdbPrescaler(PDB_Type* CONST_AL psPdbInstance, uint32 ulPrescaler)
{
  return;
}

//-----------------------------------------------------------------------------
/// \brief Pdb_Drv_PdbSetPdbMult
///
/// \descr PDB Multiplier of prescaler (divider) configuration procedure
///
/// \param  psPdbInstance - PDB instance
/// \param  ulMult - Multiplier value
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Pdb_Drv_PdbSetPdbMult(PDB_Type* CONST_AL psPdbInstance, uint32 ulMult)
{
  return;
}

//-----------------------------------------------------------------------------
/// \brief Pdb_Drv_PdbSetPdbTrigSel
///
/// \descr PDB Trigger Selector configuration procedure
///
/// \param  psPdbInstance - PDB instance
/// \param  ulTrigSel - Trigger Selector Bit value
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Pdb_Drv_PdbSetPdbTrigSel(PDB_Type* CONST_AL psPdbInstance, uint32 ulTrigSel)
{
  return;
}

//-----------------------------------------------------------------------------
/// \brief Pdb_Drv_PdbSetPdbContinous
///
/// \descr PDB continous function enable procedure
///
/// \param  psPdbInstance - PDB instance
/// \param  ulContinous - Continous mode option
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Pdb_Drv_PdbSetPdbContinous(PDB_Type* CONST_AL psPdbInstance, uint32 ulContinous)
{
  return;
}

//-----------------------------------------------------------------------------
/// \brief Pdb_Drv_PdbSetPdbTmrMod
///
/// \descr PDB Timer modulus value setup procedure
///
/// \param  psPdbInstance - PDB instance
/// \param  ulTmrMod - Timer modulus value (16bit)
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Pdb_Drv_PdbSetPdbTmrMod(PDB_Type* CONST_AL psPdbInstance, uint32 ulTmrMod)
{
  return;
}

//-----------------------------------------------------------------------------
/// \brief Pdb_Drv_PdbSetPdbTmrIdly
///
/// \descr PDB Delay Timer configuration procedure
///
/// \param  psPdbInstance - PDB instance
/// \param  ulTmrIdly - Delay value
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Pdb_Drv_PdbSetPdbTmrIdly(PDB_Type* CONST_AL psPdbInstance, uint32 ulTmrIdly)
{
  return;
}

//-----------------------------------------------------------------------------
/// \brief Pdb_Drv_PdbClearChErr
///
/// \descr PDB error flags clear procedure
///
/// \param  psPdbInstance - PDB instance
/// \param  ucChn - PDB channel
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Pdb_Drv_PdbClearChErr(PDB_Type* CONST_AL psPdbInstance, uint8 ucChn)
{
  return;
}

// EOF

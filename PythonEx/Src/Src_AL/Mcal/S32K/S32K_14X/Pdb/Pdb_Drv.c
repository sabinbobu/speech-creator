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

STATIC_AL void Pdb_Drv_PdbSetPdbEnbl      (PDB_Type* CONST_AL psPdbInstance, uint32 ulPdbEnbl);
STATIC_AL void Pdb_Drv_PdbSetPdbChTos     (CONST_AL tsPdb_PdbInputCfg* CONST_AL psPdbChannel, uint32 ulTos);
STATIC_AL void Pdb_Drv_PdbSetPdbChBb      (CONST_AL tsPdb_PdbInputCfg* CONST_AL psPdbChannel, uint32 ulBb);
STATIC_AL void Pdb_Drv_PdbSetPdbChEn      (CONST_AL tsPdb_PdbInputCfg* CONST_AL psPdbChannel, uint32 ulEn);
STATIC_AL void Pdb_Drv_PdbSetPdbChDly     (CONST_AL tsPdb_PdbInputCfg* CONST_AL psPdbChannel, uint32 ulDly);
STATIC_AL void Pdb_Drv_PdbSetPdbLdOk      (PDB_Type* CONST_AL psPdbInstance, uint32 ulLdok);
STATIC_AL void Pdb_Drv_PdbSetPdbLdMod     (PDB_Type* CONST_AL psPdbInstance, uint32 ulLdMod);
STATIC_AL void Pdb_Drv_PdbSetPdbIntEn     (PDB_Type* CONST_AL psPdbInstance, uint32 ulIntEn);
STATIC_AL void Pdb_Drv_PdbSetPdbDmaEn     (PDB_Type* CONST_AL psPdbInstance, uint32 ulDmaEn);
STATIC_AL void Pdb_Drv_PdbSetPdbErrIntEn  (PDB_Type* CONST_AL psPdbInstance, uint32 ulErrIntEn);
STATIC_AL void Pdb_Drv_PdbSetPdbPrescaler (PDB_Type* CONST_AL psPdbInstance, uint32 ulPrescaler);
STATIC_AL void Pdb_Drv_PdbSetPdbMult      (PDB_Type* CONST_AL psPdbInstance, uint32 ulMult);
STATIC_AL void Pdb_Drv_PdbSetPdbTrigSel   (PDB_Type* CONST_AL psPdbInstance, uint32 ulTrigSel);
STATIC_AL void Pdb_Drv_PdbSetPdbContinous (PDB_Type* CONST_AL psPdbInstance, uint32 ulContinous);
STATIC_AL void Pdb_Drv_PdbSetPdbTmrMod    (PDB_Type* CONST_AL psPdbInstance, uint32 ulTmrMod);
STATIC_AL void Pdb_Drv_PdbSetPdbTmrIdly   (PDB_Type* CONST_AL psPdbInstance, uint32 ulTmrIdly);
STATIC_AL void Pdb_Drv_PdbClearChErr      (PDB_Type* CONST_AL psPdbInstance, uint8 ucChn);
STATIC_AL void Pdb_Drv_CfgLoad            (CONST_AL tsPdb_PdbInstanceCfg* CONST_AL psPdbInstance);
STATIC_AL void Pdb_Drv_InitChannels       (CONST_AL tsPdb_PdbInputCfg* CONST_AL psPdbChannel);
STATIC_AL void Pdb_Drv_InitInstance       (CONST_AL tsPdb_PdbInstanceCfg* CONST_AL psPdbInstance);

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
  // Pdb instance index
  uint8 ucPdbIdx = 0u;
  // Pdb Channel Index
  uint8 ucPdbChIndx = 0u;

  // Pdb Instances initialization
  for (ucPdbIdx = 0u; ucPdbIdx < psPdbDataCfg->sPdbInstanceCfg.ucCfgLength; ucPdbIdx++)
  {
    Pdb_Drv_InitInstance(&psPdbDataCfg->sPdbInstanceCfg.psPdbInstCfg[ucPdbIdx]);
  }

  // Pdb Channels configuration
  for (ucPdbChIndx = 0u; ucPdbChIndx < psPdbDataCfg->sPdbInputChCfg.ucCfgLength; ucPdbChIndx++)
  {
    Pdb_Drv_InitChannels(&psPdbDataCfg->sPdbInputChCfg.psPdbInCfg[ucPdbChIndx]);
  }

  // Load Pdb configuration and start PDB
  for (ucPdbIdx = 0u; ucPdbIdx < psPdbDataCfg->sPdbInstanceCfg.ucCfgLength; ucPdbIdx++)
  {
    Pdb_Drv_CfgLoad(&psPdbDataCfg->sPdbInstanceCfg.psPdbInstCfg[ucPdbIdx]);
  }

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
  // Init PDB instance
  PDB_Type *psPdbInst = NULL_PTR;

  // Set PDB instance based on input configuration
  // PRQA S 306 1 //Cast between a pointer and an integral type need to access peripheral uC registers
  psPdbInst = (psPdbInstance->ucPdbInst == 0u) ? PDB0 : ((psPdbInstance->ucPdbInst == 1u) ? PDB1 : NULL_PTR);

  // PDB instance valid
  if (psPdbInstance != NULL_PTR)
  {
    // Configure module enable/disable
    Pdb_Drv_PdbSetPdbEnbl(psPdbInst, (psPdbInstance->boModEnbl != FALSE) ? PDB_DRV_ENABLE_BIT : PDB_DRV_DISABLE_BIT);
    // Load configuration
    Pdb_Drv_PdbSetPdbLdOk(psPdbInst, PDB_DRV_ENABLE_BIT);
  }
  else
  {
    // PDB instance invalid
  }
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
  // Channel Trigger Output configuration
  Pdb_Drv_PdbSetPdbChTos  (psPdbChannel, (psPdbChannel->boPdbTriggerOutput != FALSE) ? PDB_DRV_ENABLE_BIT : PDB_DRV_DISABLE_BIT);
  // Channel Back2Back Output configuration
  Pdb_Drv_PdbSetPdbChBb   (psPdbChannel, (psPdbChannel->boPdbBack2Back != FALSE) ? PDB_DRV_ENABLE_BIT : PDB_DRV_DISABLE_BIT);
  // Channel Enable configuration
  Pdb_Drv_PdbSetPdbChEn   (psPdbChannel, (psPdbChannel->boPdbAdcChnEnbl != FALSE) ? PDB_DRV_ENABLE_BIT : PDB_DRV_DISABLE_BIT);
  // Global Channel delay configuration
  Pdb_Drv_PdbSetPdbChDly  (psPdbChannel, psPdbChannel->ulPdbChnInDelayOffset_Reg);
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
  // Set local PDB instance as NULL
  PDB_Type *psPdbInst = NULL_PTR;

  // Set PDB instance
  // PRQA S 306 1 //Cast between a pointer and an integral type need to access peripheral uC registers
  psPdbInst = (psPdbInstance->ucPdbInst == 0u) ? PDB0 : ((psPdbInstance->ucPdbInst == 1u) ? PDB1 : NULL_PTR);

  // PDB instance valid
  if (psPdbInst != NULL_PTR)
  {
    // Configure Load Mode
    Pdb_Drv_PdbSetPdbLdMod      (psPdbInst, (uint32)psPdbInstance->eLdMod);
    // Configure Interrupt Enable/ Dma Enable
    Pdb_Drv_PdbSetPdbIntEn      (psPdbInst, ((psPdbInstance->boIntEnable != FALSE) || (psPdbInstance->boDmaEnable != FALSE)) ? PDB_DRV_ENABLE_BIT : PDB_DRV_DISABLE_BIT);
    // Configure Dma Enable
    Pdb_Drv_PdbSetPdbDmaEn      (psPdbInst, (psPdbInstance->boDmaEnable != FALSE) ? PDB_DRV_ENABLE_BIT : PDB_DRV_DISABLE_BIT);
    // Configure Error Interrupt Enable (Enable for ADC handlig error - reset conversion chain)
    Pdb_Drv_PdbSetPdbErrIntEn   (psPdbInst, PDB_DRV_ENABLE_BIT);
    // Configure PDB prescaler
    Pdb_Drv_PdbSetPdbPrescaler  (psPdbInst, (uint32)psPdbInstance->ePrescaler);
    // Configure PDB Multiplier
    Pdb_Drv_PdbSetPdbMult       (psPdbInst, (uint32)psPdbInstance->eMul);
    // Configure PDB trigger selector
    Pdb_Drv_PdbSetPdbTrigSel    (psPdbInst, (uint32)psPdbInstance->eTrigger);
    // Configure Pdb Continous Mode
    Pdb_Drv_PdbSetPdbContinous  (psPdbInst, (psPdbInstance->boContinousMode != FALSE) ? PDB_DRV_ENABLE_BIT : PDB_DRV_DISABLE_BIT);
    // Configure Pdb Timer Modul (Period)
    Pdb_Drv_PdbSetPdbTmrMod     (psPdbInst, psPdbInstance->ulPdbPeriod_Reg);
    // Configure Pdb Timer Delay
    Pdb_Drv_PdbSetPdbTmrIdly    (psPdbInst, psPdbInstance->ulIntDmaTrigTime_Reg);
  }
  else
  {
    // PDB instance invalid
  }
  
  // PRQA S 5324 1 // HIS metrics violation suppressed (STCAL = 10)
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
  // Get PDB0 instance
  // PRQA S 306 1 // Cast needed for microcontroller registers access
  PDB_Type* PdbBaseAddresses = PDB0;
  // PDB0 chnnels
  uint8 ucPdb0Chn = 0u;

  // Disable PDB0
  Pdb_Drv_PdbSetPdbEnbl(PdbBaseAddresses, PDB_DRV_DISABLE_BIT);

  for (ucPdb0Chn = 0u; ucPdb0Chn < PDB_CH_COUNT; ucPdb0Chn++)
  {
    // Clear PDB0 Channels Clear Error flag
    Pdb_Drv_PdbClearChErr(PdbBaseAddresses, ucPdb0Chn);
  }

  // Enable PDB0
  Pdb_Drv_PdbSetPdbEnbl(PdbBaseAddresses, PDB_DRV_ENABLE_BIT);
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
  // Get PDB1 instance
  // PRQA S 306 1 // Cast needed for microcontroller registers access
  PDB_Type* PdbBaseAddresses = PDB1;
  // PDB1 chnnels
  uint8 ucPdb1Chn = 0u;

  // Disable PDB1
  Pdb_Drv_PdbSetPdbEnbl(PdbBaseAddresses, PDB_DRV_DISABLE_BIT);

  for (ucPdb1Chn = 0u; ucPdb1Chn < PDB_CH_COUNT; ucPdb1Chn++)
  {
    // Clear PDB1 Channels Clear Error flag
    Pdb_Drv_PdbClearChErr(PdbBaseAddresses, ucPdb1Chn);
  }

  // Enable PDB1
  Pdb_Drv_PdbSetPdbEnbl(PdbBaseAddresses, PDB_DRV_ENABLE_BIT);
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
  // PDB instance
  PDB_Type *psPdbInst = NULL_PTR;
  // Get PDB channel
  uint8 ucPdbCh = psPdbChannel->ucPdbChannel;
  // Adc channel configuration (maximum 8 Adc channels per PDB channel)
  uint8 ucAdcCh = (psPdbChannel->ucAdcCh) % PDB_DRV_MAX_ADC_CHN_PDB_IN;

  // Get PDB instance
  // PRQA S 306 1 //Cast between a pointer and an integral type need to access peripheral uC registers
  psPdbInst = (psPdbChannel->ucPdbInst == 0u) ? PDB0 : ((psPdbChannel->ucPdbInst == 1u) ? PDB1 : NULL_PTR);

  // PDB instance valid and input param is in range
  if ((psPdbInst != NULL_PTR) && (ulDly <= PDB_DRV_CHn_DLY_VAL_MAX) && (ucAdcCh < PDB_DRV_MAX_ADC_CHN_PDB_IN))
  {
    // Get DLY register
    vuint32 ulRegValue = psPdbInst->CH[ucPdbCh].DLY[ucAdcCh];
    // Clear DLY biot field inside DLY register
    ulRegValue &= PDB_DRV_CHn_DLY_MASK;
    // Set DLY value
    ulRegValue |= (ulDly << PDB_DRV_CHn_DLY_POS);
    // Update CHn DLY register value
    psPdbInst->CH[ucPdbCh].DLY[ucAdcCh] = ulRegValue;
  }
  else
  {
    // PDB instance or value invalid, skip configuration
  }
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
  // PDB instance valid and input param is in range
  if ((psPdbInstance != NULL_PTR) && (ulPdbEnbl <= PDB_DRV_SC_ENBL_VAL_MAX))
  {
    // Get SC register value
    vuint32 ulRegValue = psPdbInstance->SC;
    // Clear ENBL biot field inside SC register
    ulRegValue &= PDB_DRV_SC_ENBL_MASK;
    // Set ENBL value in SC register
    ulRegValue |= (ulPdbEnbl << PDB_DRV_SC_ENBL_POS);
    // Update SC register
    psPdbInstance->SC = ulRegValue;
  }
  else
  {
    // PDB instance or value invalid, skip configuration
  }
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
  // PDB instance valid and input param is in range
  if ((psPdbInstance != NULL_PTR) && (ulLdok <= PDB_DRV_SC_LDOK_VAL_MAX))
  {
    // Get SC register value
    vuint32 ulRegValue = psPdbInstance->SC;
    // Clear LDOK biot field inside SC register
    ulRegValue &= PDB_DRV_SC_LDOK_MASK;
    // Set LDOK value in SC register
    ulRegValue |= (ulLdok << PDB_DRV_SC_LDOK_POS);
    // Update SC register
    psPdbInstance->SC = ulRegValue;
  }
  else
  {
    // PDB instance or value invalid, skip configuration
  }
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
  // PDB instance
  PDB_Type *psPdbInst = NULL_PTR;
  // Get PDB channel
  uint8 ucPdbCh = psPdbChannel->ucPdbChannel;
  // Adc channel configuration (maximum 8 Adc channels per PDB channel)
  uint8 ucAdcCh = (psPdbChannel->ucAdcCh) % PDB_DRV_MAX_ADC_CHN_PDB_IN;

  // Get PDB instance
  // PRQA S 306 1 //Cast between a pointer and an integral type need to access peripheral uC registers
  psPdbInst = (psPdbChannel->ucPdbInst == 0u) ? PDB0 : ((psPdbChannel->ucPdbInst == 1u) ? PDB1 : NULL_PTR);

  // PDB instance valid and input param is in range
  if ((psPdbInst != NULL_PTR) && (ulEn <= PDB_DRV_CHn_C1_EN_VAL_MAX) && (ucPdbCh < PDB_DRV_MAX_ADC_CHN_PDB_IN))
  {
    // Get CHn.C1 register value
    vuint32 ulRegValue = psPdbInst->CH[ucPdbCh].C1;
    // Clear EN bitfield inside CHn.C1 register
    ulRegValue &= (~((uint32)1u << (ucAdcCh + PDB_DRV_CHn_C1_EN_OFFSET_MASK)));
    // Write EN inside CHn.C1 register
    ulRegValue |= (ulEn <<  (ucAdcCh + PDB_DRV_CHn_C1_EN_OFFSET_MASK));
    // Update CHn.C1 register
    psPdbInst->CH[ucPdbCh].C1 = ulRegValue;
  }
  else
  {
    // PDB instance or value invalid, skip configuration
  }
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
  // PDB instance
  PDB_Type *psPdbInst = NULL_PTR;
  // Get PDB channel
  uint8 ucPdbCh = psPdbChannel->ucPdbChannel;
  // Adc channel configuration (maximum 8 Adc channels per PDB channel)
  uint8 ucAdcCh = (psPdbChannel->ucAdcCh) % PDB_DRV_MAX_ADC_CHN_PDB_IN;

  // Get PDB instance
  // PRQA S 306 1 //Cast between a pointer and an integral type need to access peripheral uC registers
  psPdbInst = (psPdbChannel->ucPdbInst == 0u) ? PDB0 : ((psPdbChannel->ucPdbInst == 1u) ? PDB1 : NULL_PTR);

  // PDB instance valid and input param is in range
  if ((psPdbInst != NULL_PTR) && (ulBb <= PDB_DRV_CHn_C1_BB_VAL_MAX) && (ucPdbCh < PDB_DRV_MAX_ADC_CHN_PDB_IN))
  {
    // Get CHn.C1 register value
    vuint32 ulRegValue = psPdbInst->CH[ucPdbCh].C1;
    // Clear BB bitfield inside CHn.C1 register
    ulRegValue &= (~((uint32)1u << (ucAdcCh + PDB_DRV_CHn_C1_BB_OFFSET_MASK)));
    // Write BB inside CHn.C1 register
    ulRegValue |= (ulBb << (ucAdcCh + PDB_DRV_CHn_C1_BB_OFFSET_MASK));
    // Update CHn.C1 register
    psPdbInst->CH[ucPdbCh].C1 = ulRegValue;
  }
  else
  {
    // PDB instance or value invalid, skip configuration
  }
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
  // PDB instance
  PDB_Type *psPdbInst = NULL_PTR;
  // Get PDB channel
  uint8 ucPdbCh = psPdbChannel->ucPdbChannel;
  // Adc channel configuration (maximum 8 Adc channels per PDB channel)
  uint8 ucAdcCh = (psPdbChannel->ucAdcCh) % PDB_DRV_MAX_ADC_CHN_PDB_IN;

  // Get PDB instance
  // PRQA S 306 1 //Cast between a pointer and an integral type need to access peripheral uC registers
  psPdbInst = (psPdbChannel->ucPdbInst == 0u) ? PDB0 : ((psPdbChannel->ucPdbInst == 1u) ? PDB1 : NULL_PTR);

  // PDB instance valid and input param is in range
  if ((psPdbInst != NULL_PTR) && (ulTos <= PDB_DRV_CHn_C1_TOS_VAL_MAX) && (ucPdbCh < PDB_DRV_MAX_ADC_CHN_PDB_IN))
  {
    // Get CHn.C1 register value
    vuint32 ulRegValue = psPdbInst->CH[ucPdbCh].C1;
    // Clear BB bitfield inside CHn.C1 register
    ulRegValue &= (~((uint32)1u << (ucAdcCh + PDB_DRV_CHn_C1_TOS_OFFSET_MASK)));
    // Write BB inside CHn.C1 register
    ulRegValue |= (ulTos << (ucAdcCh + PDB_DRV_CHn_C1_TOS_OFFSET_MASK));
    // Update CHn.C1 register
    psPdbInst->CH[ucPdbCh].C1 = ulRegValue;
  }
  else
  {
    // PDB instance or value invalid, skip configuration
  }
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
  // PDB instance valid and input param is in range
  if ((psPdbInstance != NULL_PTR) && (ulLdMod <= PDB_DRV_SC_LDMOD_VAL_MAX))
  {
    // Get SC register value
    vuint32 ulRegValue = psPdbInstance->SC;
    // Clear LDMOD bit in SC register
    ulRegValue &= PDB_DRV_SC_LDMOD_MASK;
    // Write LDMOD in SC register
    ulRegValue |= (ulLdMod << PDB_DRV_SC_LDMOD_POS);
    // Update SC register
    psPdbInstance->SC = ulRegValue;
  }
  else
  {
    // PDB instance or value invalid, skip configuration
  }
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
  // PDB instance valid and input param is in range
  if ((psPdbInstance != NULL_PTR) && (ulIntEn <= PDB_DRV_SC_INTEN_VAL_MAX))
  {
    // Get SC register value
    vuint32 ulRegValue = psPdbInstance->SC;
    // Clear INTEN bit in SC register
    ulRegValue &= PDB_DRV_SC_INTEN_MASK;
    // Write INTEN in SC register
    ulRegValue |= (ulIntEn << PDB_DRV_SC_INTEN_VAL_POS);
    // Load SC register
    psPdbInstance->SC = ulRegValue;
  }
  else
  {
    // PDB instance or value invalid, skip configuration
  }
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
  // PDB instance valid and input param is in range
  if ((psPdbInstance != NULL_PTR) && (ulDmaEn <= PDB_DRV_SC_DMAEN_VAL_MAX))
  {
    // Get SC register value
    vuint32 ulRegValue = psPdbInstance->SC;
    // Clear DMAEN bit in SC register
    ulRegValue &= PDB_DRV_SC_DMAEN_MASK;
    // Write DMAEN in SC register
    ulRegValue |= (ulDmaEn << PDB_DRV_SC_DMAEN_POS);
    // Load SC register
    psPdbInstance->SC = ulRegValue;
  }
  else
  {
    // PDB instance or value invalid, skip configuration
  }
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
  // PDB instance valid and input param is in range
  if ((psPdbInstance != NULL_PTR) && (ulErrIntEn <= PDB_DRV_SC_ERRINT_EN_VAL_MAX))
  {
    // Get SC register 
    vuint32 ulRegValue = psPdbInstance->SC;
    // Clear ERRINT bit in SC register
    ulRegValue &= PDB_DRV_SC_ERRINT_EN_MASK;
    // Write ERRINT in SC register
    ulRegValue |= (ulErrIntEn << PDB_DRV_SC_ERRINT_EN_POS);
    // Load SC register
    psPdbInstance->SC = ulRegValue;
  }
  else
  {
    // PDB instance or value invalid, skip configuration
  }
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
  // PDB instance valid and input param is in range
  if ((psPdbInstance != NULL_PTR) && (ulPrescaler <= PDB_DRV_SC_PRSC_VAL_MAX))
  {
    // Get SC register 
    vuint32 ulRegValue = psPdbInstance->SC;
    // Clear PRSC bit in SC register
    ulRegValue &= PDB_DRV_SC_PRSC_MASK;
    // Write ERRINT in SC register
    ulRegValue |= (ulPrescaler << PDB_DRV_SC_PRSC_POS);
    // Load SC register
    psPdbInstance->SC = ulRegValue;
  }
  else
  {
    // PDB instance or value invalid, skip configuration
  }
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
  // PDB instance valid and input param is in range
  if ((psPdbInstance != NULL_PTR) && (ulMult <= PDB_DRV_SC_MUL_VAL_MAX))
  {
    // Get SC register 
    vuint32 ulRegValue = psPdbInstance->SC;
    // Clear MULT bit in SC register
    ulRegValue &= PDB_DRV_SC_MUL_MASK;
    // Write MULT value in SC register
    ulRegValue |= (ulMult << PDB_DRV_SC_MUL_POS);
    // Load SC register
    psPdbInstance->SC = ulRegValue;
  }
  else
  {
    // PDB instance or value invalid, skip configuration
  }
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
  // PDB instance valid and input param is in range
  if ((psPdbInstance != NULL_PTR) && (ulTrigSel <= PDB_DRV_SC_TRIGSEL_VAL_MAX))
  {
    // Get SC register 
    vuint32 ulRegValue = psPdbInstance->SC;
    // Clear TRIGSEL bit in SC register
    ulRegValue &= PDB_DRV_SC_TRIGSEL_MASK;
    // Write TRIGSEL value in SC register
    ulRegValue |= (ulTrigSel << PDB_DRV_SC_TRIGSEL_POS);
    // Load SC register
    psPdbInstance->SC = ulRegValue;
  }
  else
  {
    // PDB instance or value invalid, skip configuration
  }
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
  // PDB instance valid and input param is in range
  if ((psPdbInstance != NULL_PTR) && (ulContinous <= PDB_DRV_SC_CONT_VAL_MAX))
  {
    // Get SC register 
    vuint32 ulRegValue = psPdbInstance->SC;
    // Clear CONT bit in SC register
    ulRegValue &= PDB_DRV_SC_CONT_MASK;
    // Write CONT value in SC register
    ulRegValue |= (ulContinous << PDB_DRV_SC_CONT_POS);
    // Load SC register
    psPdbInstance->SC = ulRegValue;
  }
  else
  {
    // PDB instance or value invalid, skip configuration
  }
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
  // PDB instance valid and input param is in range
  if ((psPdbInstance != NULL_PTR) && (ulTmrMod <= PDB_DRV_MOD_MOD_MAX_VAL))
  {
    // Get MOD register 
    vuint32 ulRegValue = psPdbInstance->MOD;
    // Clear MOD bits in MOD register
    ulRegValue &= PDB_DRV_MOD_MOD_MASK;
    // Write MOD value in MOD register
    ulRegValue |= (ulTmrMod << PDB_DRV_MOD_MOD_POS);
    // Update MOD register
    psPdbInstance->MOD = ulRegValue;
  }
  else
  {
    // PDB instance or value invalid, skip configuration
  }
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
  // PDB instance valid and input param is in range
  if ((psPdbInstance != NULL_PTR) && (ulTmrIdly <= PDB_DRV_IDLY_IDLY_MAX_VAL))
  {
    // Get IDLY register value
    vuint32 ulRegValue = psPdbInstance->IDLY;
    // Clear IDLY bits in IDLY register
    ulRegValue &= PDB_DRV_IDLY_IDLY_MASK;
    // Write IDLY value in IDLY register
    ulRegValue |= (ulTmrIdly << PDB_DRV_IDLY_IDLY_POS);
    // Update IDLY register
    psPdbInstance->IDLY = ulRegValue;
  }
  else
  {
    // PDB instance or value invalid, skip configuration
  }
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

  // PDB instance valid and input param is in range
  if ((psPdbInstance != NULL_PTR) && (ucChn < PDB_CH_COUNT))
  {
    // Get PDB chN status register CHn.S
    vuint32 ulRegValue = psPdbInstance->CH[ucChn].S;
    // Clear ERR flages (0 writing)
    ulRegValue &= PDB_DRV_PDB_CHn_ERR_MASK;
    // Update CHn.S register
    psPdbInstance->CH[ucChn].S = ulRegValue;
  }
  else
  {
    // PDB instance or value invalid, skip configuration
  }
}

// EOF

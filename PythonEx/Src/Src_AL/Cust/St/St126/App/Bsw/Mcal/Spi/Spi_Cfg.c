//*****************************************************************************
// (C) Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Automotive Lighting Reutlingen GmbH.
//*****************************************************************************


//=============================================================================
// Includes
//=============================================================================
#include <Spi.h>
#include <UtilUtility.h>
#include <lpspi_master_driver.h>
#include <Cfg/Cfg.h>

#ifdef LDMO_A0_SAMPLE
  #ifdef SAMPLE_FULL
  
  const lpspi_master_config_t lpspi_0_MasterConfig_SBC = {
    /* bitsPerSec whichPcs    pcsPolarity        isPcsContinuous bitcount lpspiSrcClk */
       500000UL, LPSPI_PCS0, LPSPI_ACTIVE_LOW,  true,            16U,      8000000UL,
    /* clkPhase                   clkPolarity             lsbFirst transferType */ 
       LPSPI_CLOCK_PHASE_2ND_EDGE, LPSPI_SCK_ACTIVE_HIGH, true,   LPSPI_USING_DMA, 
    /* rxDMAChannel txDMAChannel callback callbackParam */
       2U,          1U,          NULL,    NULL
  };
    
  const lpspi_master_config_t lpspi_0_MasterConfig_BOOST = {
    /* bitsPerSec whichPcs    pcsPolarity        isPcsContinuous bitcount lpspiSrcClk */
       500000UL, LPSPI_PCS2, LPSPI_ACTIVE_LOW,   true,           16U,     8000000UL,
    /* clkPhase                   clkPolarity             lsbFirst transferType */ 
       LPSPI_CLOCK_PHASE_1ST_EDGE, LPSPI_SCK_ACTIVE_HIGH, false,   LPSPI_USING_DMA, 
    /* rxDMAChannel txDMAChannel callback callbackParam */
       2U,          1U,          NULL,    NULL
  };
  
  const lpspi_master_config_t lpspi_0_MasterConfig_STP = {
    /* bitsPerSec whichPcs    pcsPolarity        isPcsContinuous bitcount lpspiSrcClk */
       500000UL,  LPSPI_PCS3, LPSPI_ACTIVE_LOW,  true,           8U,     8000000UL,
    /* clkPhase                   clkPolarity             lsbFirst transferType */ 
       LPSPI_CLOCK_PHASE_2ND_EDGE, LPSPI_SCK_ACTIVE_HIGH, false,   LPSPI_USING_DMA, 
    /* rxDMAChannel txDMAChannel callback callbackParam */
       2U,          1U,          NULL,    NULL
  };

    const lpspi_master_config_t lpspi_1_MasterConfig_BUCK = {
    /* bitsPerSec whichPcs    pcsPolarity        isPcsContinuous bitcount lpspiSrcClk */
       500000UL, LPSPI_PCS0, LPSPI_ACTIVE_LOW,   true,          16U,     8000000UL,
    /* clkPhase                   clkPolarity             lsbFirst transferType */ 
       LPSPI_CLOCK_PHASE_1ST_EDGE, LPSPI_SCK_ACTIVE_HIGH, false,   LPSPI_USING_DMA, 
    /* rxDMAChannel txDMAChannel callback callbackParam */
       4U,          3U,          NULL,    NULL
  };
  #elif defined(SAMPLE_ECO)
  
  const lpspi_master_config_t lpspi_0_MasterConfig_SBC = {
    /* bitsPerSec whichPcs    pcsPolarity        isPcsContinuous bitcount lpspiSrcClk */
       500000UL,  LPSPI_PCS0, LPSPI_ACTIVE_LOW,  true,          16U,      8000000UL,
    /* clkPhase                   clkPolarity             lsbFirst transferType */ 
       LPSPI_CLOCK_PHASE_2ND_EDGE, LPSPI_SCK_ACTIVE_HIGH, true,   LPSPI_USING_DMA, 
    /* rxDMAChannel txDMAChannel callback callbackParam */
       2U,          1U,          NULL,    NULL
  };
  
  const lpspi_master_config_t lpspi_0_MasterConfig_BOOST = {
    /* bitsPerSec whichPcs    pcsPolarity        isPcsContinuous bitcount lpspiSrcClk */
       500000UL, LPSPI_PCS2, LPSPI_ACTIVE_LOW,   true,           16U,     8000000UL,
    /* clkPhase                   clkPolarity             lsbFirst transferType */ 
       LPSPI_CLOCK_PHASE_1ST_EDGE, LPSPI_SCK_ACTIVE_HIGH, false,   LPSPI_USING_DMA, 
    /* rxDMAChannel txDMAChannel callback callbackParam */
       2U,          1U,          NULL,    NULL
  };

  const lpspi_master_config_t lpspi_1_MasterConfig_BUCK = {
    /* bitsPerSec whichPcs    pcsPolarity        isPcsContinuous bitcount lpspiSrcClk */
       500000UL, LPSPI_PCS0, LPSPI_ACTIVE_LOW,   true,          16U,     8000000UL,
    /* clkPhase                   clkPolarity             lsbFirst transferType */ 
       LPSPI_CLOCK_PHASE_1ST_EDGE, LPSPI_SCK_ACTIVE_HIGH, false,   LPSPI_USING_DMA, 
    /* rxDMAChannel txDMAChannel callback callbackParam */
       4U,          3U,          NULL,    NULL
  };
  

  
  #endif
#endif

lpspi_state_t lpspi_1State;
lpspi_state_t lpspi_2State;
#ifdef SAMPLE_FULL
lpspi_state_t lpspi_3State;
#endif
lpspi_state_t lpspi_4State;


const spi_config_map_t Spi_Cfg_atyCharacteristicsCust[e_total_number_of_spi_instances] =
{
  {0U, e_active_config_SBC,          &lpspi_1State, (const lpspi_master_config_t*) &lpspi_0_MasterConfig_SBC},
  {0U, e_active_config_BOOST,        &lpspi_2State, (const lpspi_master_config_t*) &lpspi_0_MasterConfig_BOOST},
#ifdef SAMPLE_FULL
  {0U, e_active_config_STEPPER,      &lpspi_3State, (const lpspi_master_config_t*) &lpspi_0_MasterConfig_STP},
#endif
  {1U, e_active_config_BUCK,         &lpspi_4State, (const lpspi_master_config_t*) &lpspi_1_MasterConfig_BUCK}
};

const Spi_SpecificType Spi_Config =
{
  UTIL_COUNTOF(Spi_Cfg_atyCharacteristicsCust),
  (spi_config_map_t*)&Spi_Cfg_atyCharacteristicsCust[0]
};
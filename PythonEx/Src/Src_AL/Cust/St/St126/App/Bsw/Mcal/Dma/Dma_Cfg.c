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
#include <UtilUtility.h>
#include <edma_driver.h>

#define EDMA_CHN0_NUMBER   0U
#define EDMA_CHN1_NUMBER   1U
#define EDMA_CHN2_NUMBER   2U
#define EDMA_CONFIGURED_CHANNELS_COUNT 3U

static edma_state_t dmaController_State;

static edma_chn_state_t dmaControllerChn0_State;

static edma_chn_state_t dmaControllerChn1_State;

static edma_chn_state_t dmaControllerChn2_State;


static edma_chn_state_t * const edmaChnStateArray[EDMA_CONFIGURED_CHANNELS_COUNT] = {
    &dmaControllerChn0_State,
    &dmaControllerChn1_State,
    &dmaControllerChn2_State,
};

static edma_channel_config_t dmaControllerChn0_Config = {
  /* chn prio,                 virt chn config,  source,            callback, param, trig */
    EDMA_CHN_DEFAULT_PRIORITY, EDMA_CHN0_NUMBER, EDMA_REQ_FLEXCAN0, NULL,    NULL,  FALSE
};

static edma_channel_config_t dmaControllerChn1_Config = {
  /* chn prio,                 virt chn config,  source,            callback, param, trig */
    EDMA_CHN_DEFAULT_PRIORITY, EDMA_CHN1_NUMBER, EDMA_REQ_LPSPI0_TX, NULL,    NULL,  FALSE
};

static edma_channel_config_t dmaControllerChn2_Config = {
  /* chn prio,                 virt chn config,  source,            callback, param, trig */
    EDMA_CHN_DEFAULT_PRIORITY, EDMA_CHN2_NUMBER, EDMA_REQ_LPSPI0_RX, NULL,    NULL,  FALSE
};

const edma_channel_config_t * const edmaChnConfigArray[EDMA_CONFIGURED_CHANNELS_COUNT] = {
    &dmaControllerChn0_Config,
    &dmaControllerChn1_Config,
    &dmaControllerChn2_Config,
};

const edma_user_config_t dmaController_InitConfig = {
  /* chnArbitration                 haltOnError*/
  EDMA_ARBITRATION_FIXED_PRIORITY,  FALSE
};

const DmaSpecificCharacteristicsType Dma_Cfg_atyCharacteristicsCust[1] =
{
  (edma_state_t*)&dmaController_State,
  (edma_user_config_t*)&dmaController_InitConfig,
  (edma_chn_state_t * const )&edmaChnStateArray,
  (edma_channel_config_t * const)&edmaChnConfigArray,
  EDMA_CONFIGURED_CHANNELS_COUNT
};


const Dma_SpecificType Dma_Config =
{
  UTIL_COUNTOF(Dma_Cfg_atyCharacteristicsCust),
  &Dma_Cfg_atyCharacteristicsCust[0U]
};

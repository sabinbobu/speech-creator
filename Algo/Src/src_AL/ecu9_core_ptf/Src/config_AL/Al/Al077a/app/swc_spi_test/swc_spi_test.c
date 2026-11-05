#include "Spi.h"
#include "Spi_Cfg.h"

#define SWC_SPI_TEST_BUFFER_SIZE 8U

static uint8 swc_spi_test_tx_buffer[SPI_MAX_CHANNELS][SWC_SPI_TEST_BUFFER_SIZE];
static uint8 swc_spi_test_rx_buffer[SPI_MAX_CHANNELS][SWC_SPI_TEST_BUFFER_SIZE];

extern const struct Spi_ChannelConfigType_PC_s Spi_ChannelConfig_PC[SPI_MAX_CHANNELS];
extern const struct Spi_SeqConfigType_PC_s Spi_SeqConfig_PC[SPI_MAX_SEQ];

void swc_spi_test_init(void)
{
    const Spi_ConfigType *config = &Spi_Config;
    uint32 channel;
    uint32 index;

    Spi_Init(config);

    for (channel = 0U; channel < config->maxChannels; channel++)
    {
        for (index = 0U; index < SWC_SPI_TEST_BUFFER_SIZE; index++)
        {
            swc_spi_test_tx_buffer[channel][index] = (uint8)(index + 1U);
            swc_spi_test_rx_buffer[channel][index] = 0U;
        }

        if (config->channelCfg[channel].channelBufType == SPI_EB)
        {
            Spi_SetupEB(Spi_ChannelConfig_PC[channel].channelId,
                        (Spi_DataBufferType *)&swc_spi_test_tx_buffer[channel][0U],
                        (Spi_DataBufferType *)&swc_spi_test_rx_buffer[channel][0U],
                        2U);
        }
    }
}

void swc_spi_test_trigger(void)
{
    Spi_AsyncTransmit(Spi_SeqConfig_PC[0].seqId);
    Spi_AsyncTransmit(Spi_SeqConfig_PC[1].seqId);
}

void SpiApp_McspiJob_SBC_EndNotification(void)
{
}

void SpiApp_McspiSeq_SBC_EndNotification(void)
{
}

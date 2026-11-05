#include "Can.h"
#include "Can_Cfg.h"
#include "Spi.h"
#include "Spi_Cfg.h"
#include "swc_sbc_demo.h"

#define SWC_SBC_DEMO_SBC_WRITE_CMD    (0x80U)
#define SWC_SBC_DEMO_SBC_READ_CMD     (0x00U)
#define SWC_SBC_DEMO_SBC_WRITE_COUNT  (9U)
#define SWC_SBC_DEMO_TRANSFER_TIMEOUT (100U)

typedef struct
{
    uint8 address;
    uint8 data;
} SwcSbcDemo_SbcRegisterWriteType;

typedef union
{
    uint32 alignment;
    Spi_DataBufferType bytes[4];
} SwcSbcDemo_SbcSpiBufferType;

typedef enum
{
    SWC_SBC_DEMO_SBC_WRITE = 0U,
    SWC_SBC_DEMO_SBC_WAIT_WRITE,
    SWC_SBC_DEMO_SBC_READBACK,
    SWC_SBC_DEMO_SBC_WAIT_READBACK,
    SWC_SBC_DEMO_SBC_COMPLETE,
    SWC_SBC_DEMO_SBC_READY,
    SWC_SBC_DEMO_SBC_FAILED
} SwcSbcDemo_SbcStateType;

static const SwcSbcDemo_SbcRegisterWriteType SwcSbcDemo_SbcInitWrites[SWC_SBC_DEMO_SBC_WRITE_COUNT] =
{
    { 0x41U, 0x00U },
    { 0x46U, 0x00U },
    { 0x43U, 0x00U },
    { 0x04U, 0x03U },
    { 0x02U, 0x04U },
    { 0x0FU, 0x0CU },
    { 0x1DU, 0x04U },
    { 0x0EU, 0x10U },
    { 0x01U, 0x0CU }
};

static SwcSbcDemo_SbcSpiBufferType SwcSbcDemo_SbcTxBuffer;
static SwcSbcDemo_SbcSpiBufferType SwcSbcDemo_SbcRxBuffer;
static volatile uint8 SwcSbcDemo_SpiTransferComplete;
static uint8 SwcSbcDemo_SbcWriteIndex;
static uint16 SwcSbcDemo_TransferWaitTicks;
static SwcSbcDemo_SbcStateType SwcSbcDemo_SbcState;
static boolean SwcSbcDemo_CanDriverInitialized;

volatile uint8 SwcSbcDemo_InitState = SWC_SBC_DEMO_INIT_PENDING;

static void swc_sbc_demo_SbcFail(void)
{
    SwcSbcDemo_SbcState = SWC_SBC_DEMO_SBC_FAILED;
    SwcSbcDemo_InitState = SWC_SBC_DEMO_INIT_ERROR;
}

static Std_ReturnType swc_sbc_demo_SbcStartTransfer(uint16 frame)
{
    SwcSbcDemo_SbcTxBuffer.bytes[0] = (Spi_DataBufferType)(frame & 0x00FFU);
    SwcSbcDemo_SbcTxBuffer.bytes[1] = (Spi_DataBufferType)(frame >> 8U);
    SwcSbcDemo_SbcRxBuffer.bytes[0] = 0U;
    SwcSbcDemo_SbcRxBuffer.bytes[1] = 0U;
    SwcSbcDemo_SpiTransferComplete = 0U;

    if (Spi_SetupEB(SpiConf_SpiChannel_SpiChannel_0,
                    SwcSbcDemo_SbcTxBuffer.bytes,
                    SwcSbcDemo_SbcRxBuffer.bytes,
                    1U) != E_OK)
    {
        return E_NOT_OK;
    }

    return Spi_AsyncTransmit(SpiConf_SpiSequence_SpiSequence_SBC);
}

static void swc_sbc_demo_SbcMainFunction(void)
{
    uint16 rxFrame;
    uint16 frame;
    Spi_SeqResultType sequenceResult;

    switch (SwcSbcDemo_SbcState)
    {
        case SWC_SBC_DEMO_SBC_WRITE:
            frame = (uint16)(((uint16)SwcSbcDemo_SbcInitWrites[SwcSbcDemo_SbcWriteIndex].data << 8U) |
                    (uint16)(SwcSbcDemo_SbcInitWrites[SwcSbcDemo_SbcWriteIndex].address |
                             SWC_SBC_DEMO_SBC_WRITE_CMD));
            if (swc_sbc_demo_SbcStartTransfer(frame) != E_OK)
            {
                swc_sbc_demo_SbcFail();
            }
            else
            {
                SwcSbcDemo_SbcState = SWC_SBC_DEMO_SBC_WAIT_WRITE;
            }
            break;

        case SWC_SBC_DEMO_SBC_WAIT_WRITE:
            sequenceResult = Spi_GetSequenceResult(SpiConf_SpiSequence_SpiSequence_SBC);
            if (sequenceResult == SPI_SEQ_OK)
            {
                SwcSbcDemo_TransferWaitTicks = 0U;
                SwcSbcDemo_SpiTransferComplete = 0U;
                SwcSbcDemo_SbcState = SWC_SBC_DEMO_SBC_READBACK;
            }
            else if ((sequenceResult != SPI_SEQ_PENDING) ||
                     (SwcSbcDemo_SpiTransferComplete != 0U) ||
                     (++SwcSbcDemo_TransferWaitTicks >= SWC_SBC_DEMO_TRANSFER_TIMEOUT))
            {
                swc_sbc_demo_SbcFail();
            }
            break;

        case SWC_SBC_DEMO_SBC_READBACK:
            frame = (uint16)(SwcSbcDemo_SbcInitWrites[SwcSbcDemo_SbcWriteIndex].address |
                             SWC_SBC_DEMO_SBC_READ_CMD);
            if (swc_sbc_demo_SbcStartTransfer(frame) != E_OK)
            {
                swc_sbc_demo_SbcFail();
            }
            else
            {
                SwcSbcDemo_SbcState = SWC_SBC_DEMO_SBC_WAIT_READBACK;
            }
            break;

        case SWC_SBC_DEMO_SBC_WAIT_READBACK:
            sequenceResult = Spi_GetSequenceResult(SpiConf_SpiSequence_SpiSequence_SBC);
            if (sequenceResult == SPI_SEQ_OK)
            {
                SwcSbcDemo_TransferWaitTicks = 0U;
                SwcSbcDemo_SpiTransferComplete = 0U;
                rxFrame = (uint16)((uint16)SwcSbcDemo_SbcRxBuffer.bytes[0] |
                                   ((uint16)SwcSbcDemo_SbcRxBuffer.bytes[1] << 8U));
                if ((uint8)(rxFrame >> 8U) != SwcSbcDemo_SbcInitWrites[SwcSbcDemo_SbcWriteIndex].data)
                {
                    swc_sbc_demo_SbcFail();
                }
                else
                {
                    SwcSbcDemo_SbcWriteIndex++;
                    SwcSbcDemo_SbcState = (SwcSbcDemo_SbcWriteIndex < SWC_SBC_DEMO_SBC_WRITE_COUNT) ?
                        SWC_SBC_DEMO_SBC_WRITE : SWC_SBC_DEMO_SBC_COMPLETE;
                }
            }
            else if ((sequenceResult != SPI_SEQ_PENDING) ||
                     (SwcSbcDemo_SpiTransferComplete != 0U) ||
                     (++SwcSbcDemo_TransferWaitTicks >= SWC_SBC_DEMO_TRANSFER_TIMEOUT))
            {
                swc_sbc_demo_SbcFail();
            }
            break;

        case SWC_SBC_DEMO_SBC_COMPLETE:
            if (Can_SetControllerMode(CanConf_CanController_CanController_0,
                                      CAN_CS_STARTED) == E_OK)
            {
                SwcSbcDemo_SbcState = SWC_SBC_DEMO_SBC_READY;
                SwcSbcDemo_InitState = SWC_SBC_DEMO_INIT_READY;
            }
            else
            {
                swc_sbc_demo_SbcFail();
            }
            break;

        case SWC_SBC_DEMO_SBC_FAILED:
        case SWC_SBC_DEMO_SBC_READY:
        default:
            break;
    }
}

void swc_sbc_demo_init(void)
{
    SwcSbcDemo_SbcWriteIndex = 0U;
    SwcSbcDemo_TransferWaitTicks = 0U;
    SwcSbcDemo_SpiTransferComplete = 0U;
    SwcSbcDemo_SbcState = SWC_SBC_DEMO_SBC_WRITE;
    SwcSbcDemo_InitState = SWC_SBC_DEMO_INIT_PENDING;
    SwcSbcDemo_CanDriverInitialized = FALSE;
}

void swc_sbc_demo_SpiSequenceEndNotification(void)
{
    SwcSbcDemo_SpiTransferComplete = 1U;
}

void swc_sbc_demo_MainFunction(void)
{
    if (SwcSbcDemo_CanDriverInitialized == FALSE)
    {
        Can_Init(&Can_Config);
        SwcSbcDemo_CanDriverInitialized = TRUE;
    }

    if (SwcSbcDemo_InitState != SWC_SBC_DEMO_INIT_READY)
    {
        swc_sbc_demo_SbcMainFunction();
    }
}

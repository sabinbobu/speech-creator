#include "Com.h"
#include "Com_Cfg.h"
#include "Can.h"
#include "Can_Cfg.h"
#include "swc_can_demo.h"
#include "swc_sbc_demo.h"

volatile uint8 SwcCanDemo_Status = SWC_CAN_DEMO_STATUS_ACTIVE;
volatile uint8 SwcCanDemo_TxCounter;
volatile uint16 SwcCanDemo_TxValue;
volatile uint32 SwcCanDemo_TxErrorCount;
volatile uint32 SwcCanDemo_RxFrameCount;
volatile uint8 SwcCanDemo_RxCounter;
volatile uint16 SwcCanDemo_RxValue;

static uint32 SwcCanDemo_LastRxUpdateCount;

void swc_can_demo_init(void)
{
    SwcCanDemo_Status = SWC_CAN_DEMO_STATUS_ACTIVE;
    SwcCanDemo_TxCounter = 0U;
    SwcCanDemo_TxValue = 0U;
    SwcCanDemo_TxErrorCount = 0U;
    SwcCanDemo_RxFrameCount = 0U;
    SwcCanDemo_RxCounter = 0U;
    SwcCanDemo_RxValue = 0U;
    SwcCanDemo_LastRxUpdateCount = 0U;
}

void swc_can_demo_MainFunction(void)
{
    Com_SignalStatus_t rxCounterStatus;
    uint32 rxCounter;
    uint32 rxValue;

    if (SwcSbcDemo_InitState != SWC_SBC_DEMO_INIT_READY)
    {
        return;
    }

#if (CAN_RX_POLLING == STD_ON)
    Can_MainFunction_Read();
#endif
#if (CAN_TX_POLLING == STD_ON)
    Can_MainFunction_Write();
#endif

    SwcCanDemo_TxCounter++;
    SwcCanDemo_TxValue++;

    if ((Com_WriteSignal(COM_SIGNAL_ID_SAMPLE_TX_COUNTER,
                         SwcCanDemo_TxCounter, 0U) != COM_STATUS_OK) ||
        (Com_WriteSignal(COM_SIGNAL_ID_SAMPLE_TX_VALUE,
                         SwcCanDemo_TxValue, 0U) != COM_STATUS_OK))
    {
        SwcCanDemo_Status = SWC_CAN_DEMO_STATUS_ERROR;
        SwcCanDemo_TxErrorCount++;
        return;
    }

    if ((Com_ReadSignal(COM_SIGNAL_ID_SAMPLE_RX_COUNTER,
                        &rxCounter, &rxCounterStatus) == COM_STATUS_OK) &&
        (Com_ReadSignal(COM_SIGNAL_ID_SAMPLE_RX_VALUE,
                        &rxValue, NULL) == COM_STATUS_OK))
    {
        if (rxCounterStatus.updateCount != SwcCanDemo_LastRxUpdateCount)
        {
            SwcCanDemo_LastRxUpdateCount = rxCounterStatus.updateCount;
            SwcCanDemo_RxCounter = (uint8)rxCounter;
            SwcCanDemo_RxValue = (uint16)rxValue;
            SwcCanDemo_RxFrameCount++;
        }
    }
    else
    {
        SwcCanDemo_Status = SWC_CAN_DEMO_STATUS_ERROR;
    }
}

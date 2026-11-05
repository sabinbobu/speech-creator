/*
* Copyright (C) 2023-2024 Texas Instruments Incorporated
*
* All rights reserved not granted herein.
* Limited License.  
*
* Texas Instruments Incorporated grants a world-wide, royalty-free, 
* non-exclusive license under copyrights and patents it now or hereafter 
* owns or controls to make, have made, use, import, offer to sell and sell ("Utilize")
* this software subject to the terms herein.  With respect to the foregoing patent 
* license, such license is granted  solely to the extent that any such patent is necessary 
* to Utilize the software alone.  The patent license shall not apply to any combinations which 
* include this software, other than combinations with devices manufactured by or for TI ("TI Devices").  
* No hardware patent is licensed hereunder.
*
* Redistributions must preserve existing copyright notices and reproduce this license (including the 
* above copyright notice and the disclaimer and (if applicable) source code license limitations below) 
* in the documentation and/or other materials provided with the distribution
*
* Redistribution and use in binary form, without modification, are permitted provided that the following
* conditions are met:
*
*	* No reverse engineering, decompilation, or disassembly of this software is permitted with respect to any 
*     software provided in binary form.
*	* any redistribution and use are licensed by TI for use only with TI Devices.
*	* Nothing shall obligate TI to provide you with source code for the software licensed and provided to you in object code.
*
* If software source code is provided to you, modification and redistribution of the source code are permitted 
* provided that the following conditions are met:
*
*   * any redistribution and use of the source code, including any resulting derivative works, are licensed by 
*     TI for use only with TI Devices.
*   * any redistribution and use of any object code compiled from the source code and any resulting derivative 
*     works, are licensed by TI for use only with TI Devices.
*
* Neither the name of Texas Instruments Incorporated nor the names of its suppliers may be used to endorse or 
* promote products derived from this software without specific prior written permission.
*
* DISCLAIMER.
*
* THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, 
* BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
* IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
* OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
* POSSIBILITY OF SUCH DAMAGE.
*/

/**
 *  \file     swc_led.c
 *
 *  \brief    This file contains the LED software component example
 */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* Include Files */
//#include "DioApp_Startup.h"
#include "EcuM_Types.h"
#include "Std_Types.h"
#include "Adc_Types.h"
#include <assert.h>
#include "Os.h"
#include "swc_led.h"

volatile uint8 Gpt_notifyRecvFlag = 0U;
Adc_ValueGroupType    Adc_AppBuffer[ADC_MAX_GROUP][ADC_NUM_CHANNEL];
Adc_ValueGroupType    Adc_AppReadBuffer[ADC_MAX_GROUP][4 * 100 * ADC_NUM_CHANNEL];
volatile uint32     gAdcAppGroupDone[ADC_MAX_GROUP];
/* SPI External Buffers for Tx and Rx */
#define RX_TX_BUF_SIZE_WORD 8U
uint8 gMcspiTxBuffer[SPI_MAX_CHANNELS][RX_TX_BUF_SIZE_WORD];
uint8 gMcspiRxBuffer[SPI_MAX_CHANNELS][RX_TX_BUF_SIZE_WORD];

/** \brief SPI Channel Pre-Compile Configuration struct declaration */
extern const struct Spi_ChannelConfigType_PC_s Spi_ChannelConfig_PC[SPI_MAX_CHANNELS];

/** \brief SPI Job Pre-Compile Configuration struct declaration */
extern const struct Spi_JobConfigType_PC_s Spi_JobConfig_PC[SPI_MAX_JOBS];

/** \brief SPI Sequence Pre-Compile Configuration struct declaration */
extern const struct Spi_SeqConfigType_PC_s Spi_SeqConfig_PC[SPI_MAX_SEQ];

#define PWM_DUTY_10_PERCENT             (0x0CCC)
#define PWM_DUTY_90_PERCENT             (0x7333)

static void GptExample_InterruptConfig(void)
{
#if defined(GPT_CHANNEL_0) || defined(GPT_CHANNEL_1)
    NVIC_EnableIRQ(TIMG0_INT_IRQn);
    NVIC_SetPriority(TIMG0_INT_IRQn, 3);
#endif
#if defined(GPT_CHANNEL_2) || defined(GPT_CHANNEL_3)
    NVIC_EnableIRQ(TIMG6_INT_IRQn);
    NVIC_SetPriority(TIMG6_INT_IRQn, 3);
#endif
#if defined(GPT_CHANNEL_4) || defined(GPT_CHANNEL_5)
    NVIC_EnableIRQ(TIMG7_INT_IRQn);
    NVIC_SetPriority(TIMG7_INT_IRQn, 3);
#endif
#if defined(GPT_CHANNEL_6) || defined(GPT_CHANNEL_7)
    NVIC_EnableIRQ(TIMG8_INT_IRQn);
    NVIC_SetPriority(TIMG8_INT_IRQn, 3);
#endif
#if defined(GPT_CHANNEL_8) || defined(GPT_CHANNEL_9)
    NVIC_EnableIRQ(TIMG12_INT_IRQn);
    NVIC_SetPriority(TIMG12_INT_IRQn, 3);
#endif
#if defined(GPT_CHANNEL_10) || defined(GPT_CHANNEL_11) || defined(GPT_CHANNEL_12) || defined(GPT_CHANNEL_13)
    NVIC_EnableIRQ(TIMA0_INT_IRQn);
    NVIC_SetPriority(TIMA0_INT_IRQn, 3);
#endif
#if defined(GPT_CHANNEL_14) || defined(GPT_CHANNEL_15)
    NVIC_EnableIRQ(TIMA1_INT_IRQn);
    NVIC_SetPriority(TIMA1_INT_IRQn, 3);
#endif
#if defined(GPT_CHANNEL_16) || defined(GPT_CHANNEL_17)
    NVIC_EnableIRQ(TIMG9_INT_IRQn);
    NVIC_SetPriority(TIMG9_INT_IRQn, 3);
#endif
#if defined(GPT_CHANNEL_18) || defined(GPT_CHANNEL_19) || defined(GPT_CHANNEL_20) || defined(GPT_CHANNEL_21)
    NVIC_EnableIRQ(TIMG14_INT_IRQn);
    NVIC_SetPriority(TIMG14_INT_IRQn, 3);
#endif
}

static void AdcApp_configInterrupt(void)
{
    NVIC_EnableIRQ(ADC0_INT_IRQn);
    NVIC_EnableIRQ(ADC1_INT_IRQn);
}

static void SpiApp_interruptConfig(void)
{    
     
#if defined(SPI_UNIT_SPI0_ACTIVE)
    NVIC_EnableIRQ(SPI0_INT_IRQn);
    NVIC_SetPriority(SPI0_INT_IRQn, 3);
#endif
#if defined(SPI_UNIT_SPI1_ACTIVE)
    NVIC_EnableIRQ(SPI1_INT_IRQn);
    NVIC_SetPriority(SPI1_INT_IRQn, 3);
#endif
#if defined(SPI_UNIT_SPI2_ACTIVE)
    NVIC_EnableIRQ(SPI2_INT_IRQn);
    NVIC_SetPriority(SPI2_INT_IRQn, 3);
#endif
#if (SPI_DMA_ENABLE == STD_ON)
    NVIC_EnableIRQ(DMA_INT_IRQn);
    NVIC_SetPriority(DMA_INT_IRQn, 3);
#endif

	return;
}

void swc_led_init (void)
{
    uint32 grpIdx;
    const Spi_ConfigType *cfgPtr = &Spi_Config;
    uint32              index, chIndex;
    uint8              *tempTxPtr, *tempRxPtr;
    uint32              byteLength[SPI_MAX_CHANNELS] = {0U};
    uint32              xferLength[SPI_MAX_CHANNELS] = {0U};

    AdcApp_configInterrupt();
    GptExample_InterruptConfig();
    Gpt_EnableNotification(GPT_TIMG_CHANNEL2);
    Gpt_StartTimer(GPT_TIMG_CHANNEL2, 10000);

    SpiApp_interruptConfig();
    Spi_Init(cfgPtr);

    /* Init test params */
    for (chIndex = 0U; chIndex < cfgPtr->maxChannels; chIndex++)
    {
        /* Init TX buffer with known data and memset RX buffer */
        tempTxPtr = (Spi_DataBufferType *) &gMcspiTxBuffer[chIndex][0U];
        tempRxPtr = (Spi_DataBufferType *) &gMcspiRxBuffer[chIndex][0U];
        for (index = 0U; index < (RX_TX_BUF_SIZE_WORD); index++)
        {
            *tempTxPtr++ = (Spi_DataBufferType) (index + 1U);
            *tempRxPtr++ = 0U;
        }
		if (cfgPtr->channelCfg[chIndex].dataWidth <= 8U)
        {
            xferLength[chIndex] = 32U;
        }
        else if (cfgPtr->channelCfg[chIndex].dataWidth <= 16U)
        {
            xferLength[chIndex] = 32U / 2;
        }
        else
        {
            xferLength[chIndex] = 32U;
        }
    }

    for (chIndex = 0U; chIndex < cfgPtr->maxChannels; chIndex++)
    {
        /* Memset RX buffer for every run */
        if (cfgPtr->channelCfg[chIndex].dataWidth <= 8U)
        {
            byteLength[chIndex] = xferLength[chIndex];
        }
        else if (cfgPtr->channelCfg[chIndex].dataWidth <= 16U)
        {
            byteLength[chIndex] = xferLength[chIndex] * 2U;
        }
        else
        {
            byteLength[chIndex] = xferLength[chIndex];
        }
        tempRxPtr = (uint8 *) &gMcspiRxBuffer[chIndex][0U];
        for (index = 0U; index < byteLength[chIndex]; index++)
        {
            *tempRxPtr++ = 0U;
        }
        /* SetUp Buffers EB: External Buffer, IB: Internal Buffer */
        if (cfgPtr->channelCfg[chIndex].channelBufType == SPI_EB)
        {
            Spi_DataBufferType *srcDataBuf, *destDataBuf;

            /* Setup EB for TX/RX */
            srcDataBuf  = (Spi_DataBufferType *) &gMcspiTxBuffer[chIndex][0U];
            destDataBuf = (Spi_DataBufferType *) &gMcspiRxBuffer[chIndex][0U];
            Spi_SetupEB(Spi_ChannelConfig_PC[chIndex].channelId,srcDataBuf,destDataBuf,2);
        }
    }

        Spi_AsyncTransmit(Spi_SeqConfig_PC[0].seqId);
        Spi_AsyncTransmit(Spi_SeqConfig_PC[1].seqId);

    for (grpIdx = 0U; grpIdx < AdcConfigSet.maxGroup; grpIdx++)
    {
        Adc_SetupResultBuffer(grpIdx, &Adc_AppBuffer[grpIdx][0]);
        gAdcAppGroupDone[grpIdx] = FALSE;
        /* Enable notification */
        Adc_EnableGroupNotification(grpIdx);
        /* Start conversion */
        Adc_StartGroupConversion(grpIdx);
    }
}

void Gpt_Channel_Notify1(void)
{   
    if (Gpt_notifyRecvFlag == 0)
    {
        Gpt_notifyRecvFlag = 1U;
        Pwm_SetDutyCycle(PWM_TIMG_CHANNEL1, PWM_DUTY_90_PERCENT);
    }
    else
    {
        Gpt_notifyRecvFlag = 0U;
        Pwm_SetDutyCycle(PWM_TIMG_CHANNEL1, PWM_DUTY_10_PERCENT);
    }
}

void AdcApp_procIsr(uint32 grpIdx)
{
    Adc_StatusType status;
    Std_ReturnType retVal;
    /* Check group status - it should be COMPLETED state */
    status = Adc_GetGroupStatus(grpIdx);
    if (status == ADC_STREAM_COMPLETED)
    {

        /* Read and store the result */
        retVal = Adc_ReadGroup(grpIdx, &Adc_AppReadBuffer[grpIdx][0]);
    }
    else
    {

    }
    gAdcAppGroupDone[grpIdx] = TRUE;
    return;
}

void AdcApp_HwUnit0_Group0EndNotification(void)
{
    AdcApp_procIsr(0U);
}

void AdcApp_HwUnit1_Group1EndNotification(void)
{
    AdcApp_procIsr(1U);
}

void SpiApp_McspiJob_SBC_EndNotification(void)
{
    //SpiApp_McspiJobDone[0U] = TRUE;
}

void SpiApp_McspiSeq_SBC_EndNotification(void)
{
    //SpiApp_McspiSeqDone[0U] = TRUE;
}

void SchM_Enter_Dio_DIO_EXCLUSIVE_AREA_0()
{
  DisableAllInterrupts();
}

void SchM_Exit_Dio_DIO_EXCLUSIVE_AREA_0()
{
  EnableAllInterrupts();
}

void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_0()
{
  DisableAllInterrupts();
}

void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_0()
{
  EnableAllInterrupts();
}

void SchM_Enter_Pwm_PWM_EXCLUSIVE_AREA_0(void)
{
  DisableAllInterrupts();
}

void SchM_Exit_Pwm_PWM_EXCLUSIVE_AREA_0(void)
{
  EnableAllInterrupts();
}

void  SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_0()
{
  DisableAllInterrupts();
}

void   SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_0()
{
  EnableAllInterrupts();
}

void SchM_Enter_Gpt_GPT_EXCLUSIVE_AREA_0(void)
{
  DisableAllInterrupts();
}

void SchM_Exit_Gpt_GPT_EXCLUSIVE_AREA_0(void)
{
  EnableAllInterrupts();
}

void SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_0()
{
  DisableAllInterrupts();
}

void SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_0()
{
  EnableAllInterrupts();
}

void SchM_Enter_Spi_SPI_EXCLUSIVE_AREA_0(void)
{
  DisableAllInterrupts();
	
}
void SchM_Exit_Spi_SPI_EXCLUSIVE_AREA_0(void)
{
  EnableAllInterrupts();

}

void EcuM_CheckWakeup(EcuM_WakeupSourceType wakeupSource)
{

}

Std_ReturnType Det_ReportError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId,
    uint8 ErrorId)
{
    return E_OK;
}

Std_ReturnType Det_ReportRuntimeError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId,
    uint8 ErrorId)
{
    return E_OK;
}

void Dem_ReportErrorStatus(Dem_EventIdType     eventId,
                           Dem_EventStatusType eventStatus)
{
    if (DEM_EVENT_STATUS_FAILED == eventStatus)
    {
        assert(FALSE);
    }

    return;
}


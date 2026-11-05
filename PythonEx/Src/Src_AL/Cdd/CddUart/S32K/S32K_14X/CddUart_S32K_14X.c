//*****************************************************************************
// (C) Marelli Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Marelli Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Marelli Automotive Lighting Reutlingen GmbH.
//*****************************************************************************
//-----------------------------------------------------------------------------
/// \file  CddUart_S32K_14X.c
///
/// \brief
///
/// \author Caba Ionut-Stefan (F37899C)
///         mailTo:ionut-stefan.caba[at]marelli.com
///
//-----------------------------------------------------------------------------

//=============================================================================
// Includes
//=============================================================================
#include <AL_Helper.h>
#include <../Cdd/CddUart/Cfg/CddUart_Cfg.h>
#include <CddUart_S32K_14X.h>
#include <CddUart_S32K_14X_Types.h>
#include <CddDma.h>
#include <CddUart.h>
#ifdef CPU_S32K146 
#include <CddDma_S32K_14X_Types.h>
#include <S32K146.h>
#endif

//=============================================================================
// Preprocessor definitions
//=============================================================================
#if defined (UNIT_TEST)
tsCddUart_S32K_14X_Registers  UART_Register_UnitTest[CddUart_eDev_Count];
tsCddDma_S32K_146_Registers   CDDDMA_BASE_UnitTest;
#define CDDUART_S32K_14X_PERIF_IFCBASE(ifc)          &UART_Register_UnitTest[ifc]
#define CDDUART_S32K_14X_DMA_BASE                    &CDDDMA_BASE_UnitTest
#else
#define CDDUART_S32K_14X_PERIF_BASE                 (0x4006A000u)
#define CDDUART_S32K_14X_PERIF_IFCBASE(ifc)         ((volatile tsCddUart_S32K_14X_Registers*)(CDDUART_S32K_14X_PERIF_BASE + (0x00001000UL * (ifc)) ))
#define CDDUART_S32K_14X_DMA_BASE                    CDDDMA
#endif

//=============================================================================
// Private type definitions
//=============================================================================

//=============================================================================
// Private variables
//=============================================================================
// configuration of RX and TX transfers with DMA
STATIC_AL tsCddDma_Parameter            CddUart_sDMAConfigReception;
STATIC_AL tsCddDma_Parameter            CddUart_sDMAConfigTransmission;
STATIC_AL tsCddUart_S32K_14X_Registers  CddUart_sS32K_14X_Registers;

STATIC_AL boolean CddUart_boRxSuccess     = FALSE;
STATIC_AL uint32  CddMlcUart_CommandStart = 0u;

//=============================================================================
// Private functions prototypes 
//=============================================================================

STATIC_AL void CddUart_DMA_RX_CallbackFct(void);

//=============================================================================
// Public functions  implementation
//=============================================================================


//-----------------------------------------------------------------------------
/// \brief  CddUart_InitIfc_Deriv
///
/// \descr  Initialize UART driver for each configured instance with a
///         predefined configuration (Kbps) until the Interface config is available
///         This is called at module UART intialization only.
///
/// \param  ucIfc : UART interface to be initialized
///
/// \return void
//-----------------------------------------------------------------------------
void CddUart_InitIfc_Deriv(uint8 ucIfc)
{
  //access the register structure
  volatile  tsCddUart_S32K_14X_Registers* psUART_Register = CDDUART_S32K_14X_PERIF_IFCBASE(ucIfc);      // PRQA S 303 //Message: Cast between a pointer to volatile object and an integral type. Reason: the cast is allowed since we are accessing hardware registers
  psUART_Register = &CddUart_sS32K_14X_Registers;


  psUART_Register->uCTRL.sBit = (tsCddMlcUart_NXP_CTRL) {
                                                                        .u1RE       = CDDUART_DISABLE_VAL_SET,        // receiver disabled
                                                                        .u1TE       = CDDUART_DISABLE_VAL_SET,        // transmitter disabled
  };


  /* Configure the UART interface  - 8N1 protocol = 8 bits of data, 1 stop bit */
  psUART_Register->uBAUD.sBit = (tsCddMlcUart_NXP_BAUD) {
                                                                        .u13SBR     = 1U,        // baud = 16Mhz / 500k = 32 => OSR +1 = 32; SBR = 1
                                                                        .u5OSR      = 31U,
                                                                        .u1SBNS     = 0U,        // one stop bit
                                                                        .u1RXEDGIE  = 0U,        // RX input active angle interrupt disabled
                                                                        .u1LBKDIE   = 0U,        // LIN Break Detect Interrupt Disabled
                                                                        .u1BOTHEDGE = 0U,        // BOTHEDGE=0: receiver samples only on rising edge
                                                                        .u2MATCFG   = 0U,        // Match configuration disabled
                                                                        .u1M10      = 0U,        // M10=0: Rx and Tx use 7 to 9 bit data characters
                                                                        .u1MAEN1    = 0U,        // Match address disabled
                                                                        .u1MAEN2    = 0U,        // Match address disabled
                                                                        .u1RDMAE    = 0U,        // Receiver DMA request enabled
                                                                        .u1TDMAE    = 0U,        // Transmitter DMA request enabled
  };


  /* Configure the UART Control -  No parity, 8 bit data character*/
  psUART_Register->uCTRL.sBit = (tsCddMlcUart_NXP_CTRL) {
                                                                        .u1PE       = 0U,         // no hardware parity generation or checking
                                                                        .u1M        = 0U,         // Receiver and transmitter use 8-bit data characters
                                                                        .u1DOZEEN   = 0U,         // LPUART is enabled in Doze mode (=low power)
                                                                        .u1LOOPS    = 0U,         // TX and RX use different pins
                                                                        .u1M7       = 0U,         // receiver and transmitter use 8-bit to 10-bit data characters
                                                                        .u1SBK      = 0U,         // normal transmitter operation - no break character
                                                                        .u1TIE      = 0U,         // transmit interrupt disabled (hardware interrupt disabled)
                                                                        .u1TCIE     = 0U,         // transmission complete interrupt disabled (hardware interrupt disabled)
  };


  /* Configure the UART Status*/
  psUART_Register->uSTAT.sBit = (tsCddMlcUart_NXP_STAT) {
                                                                        .u1RXINV    = 0U,         // Receive Data not inverted
                                                                        .u1MSBF     = 0U,         // LSB (least significant bit) first
                                                                        .u1BRK13    = 0U,
  };


  psUART_Register->uFIFO.sBit = (tsCddMlcUart_NXP_FIFO) {
                                                                        .u1TXFE     = 0U,         // Transmit FIFO is not enabled. Buffer is depth 1.
                                                                        .u1RXFE     = 0U,         // Receive FIFO is not enabled. Buffer is depth 1
  };


  psUART_Register->uWATER.sBit = (tsCddMlcUart_NXP_WATER) {
                                                                        .u2TXWATER  = 0U,         // When the number of datawords in the receive FIFO/buffer is greater than the value in this register field, an interrupt is generated
                                                                        .u2RXWATER  = 0U,
  };


  psUART_Register->uCTRL.sBit = (tsCddMlcUart_NXP_CTRL) {
                                                                        .u1RE       = CDDUART_ENABLE_VAL_SET,         // receiver enabled
                                                                        .u1TE       = CDDUART_ENABLE_VAL_SET,         // transmitter enabled
  };


}


//-----------------------------------------------------------------------------
/// \brief  CddUart_DeInitIfc_Deriv
///
/// \descr  DeInitialize UART driver for each configured instance
///
/// \param  ucIfc :  UART interface to be deinitialized
///
/// \return void
//-----------------------------------------------------------------------------
void CddUart_DeInitIfc_Deriv(uint8 ucIfc)
{
  //access the register structure
  volatile  tsCddUart_S32K_14X_Registers* psUART_Register = CDDUART_S32K_14X_PERIF_IFCBASE(ucIfc);  // PRQA S 303  //Message: Cast between a pointer to volatile object and an integral type. Reason: the cast is allowed since we are accessing hardware registers
  psUART_Register = &CddUart_sS32K_14X_Registers;

  psUART_Register->uCTRL.sBit = (tsCddMlcUart_NXP_CTRL){
                                                                        .u1RE = CDDUART_DISABLE_VAL_SET,        // receiver disabled
                                                                        .u1TE = CDDUART_DISABLE_VAL_SET,        // transmitter disabled
  };

}

//-----------------------------------------------------------------------------
/// \brief  CddUart_ConfigureTransfer_Param
///
/// \descr  Configure transmission parameters passed to the function by setting
///         the Target HW Registers for :
///             - baudrate
///             - data direction (LSB/MSB)
///             - data width (8bits)
///             - interrupt source
///
/// \param  psDevCfg : pointer to  device data configuration
///
/// \return void
//-----------------------------------------------------------------------------
void CddUart_ConfigureTransfer_Param(const tsCddUartDevCfg* psDevCfg)
{

  //keep it the same as in CddUart_Cfg.h, meaning that :
  //                    ucDevice 0 = TPS92662
  //                    ucDevice 1 = TPS92664

  //get the base address for the current instance of UART
  volatile  tsCddUart_S32K_14X_Registers* psUART_Register = CDDUART_S32K_14X_PERIF_IFCBASE(psDevCfg->ucUartIfc);   // PRQA S 303  //Message: Cast between a pointer to volatile object and an integral type. Reason: the cast is allowed since we are accessing hardware registers

  // register values must be updated only when the transmitter and receiver are both disabled
  psUART_Register->uCTRL.sBit = (tsCddMlcUart_NXP_CTRL){
                                                                      .u1RE = CDDUART_DISABLE_VAL_SET,
                                                                      .u1TE = CDDUART_DISABLE_VAL_SET,
  };

  uint16 unOverSamplingFactor;
  //1. Set Baud Rate and calculate OVS factor
  switch (psDevCfg->ulBaudRate)
  {
  case CDDUART_BAUDRATE_500K:
    unOverSamplingFactor = CDDUART_BAUDRATE_OVS_REGISTER_VAL(CDDUART_BAUDRATE_500K);
    
    break;

  case CDDUART_BAUDRATE_1M:
    unOverSamplingFactor = CDDUART_BAUDRATE_OVS_REGISTER_VAL(CDDUART_BAUDRATE_1M);
    break;

  default:
    //consider UART baud rate as 500KHz default
    unOverSamplingFactor = CDDUART_BAUDRATE_OVS_REGISTER_VAL(CDDUART_BAUDRATE_500K);
    break;
  }

  uint16 unSBRVal = CDDUART_BAUDRATE_SBR_DIVISOR_REGISTER_VAL(psDevCfg->ulBaudRate);

  /* Configure the UART interface  - baud rate divisior and OverSampling Ratio */
  psUART_Register->uBAUD.sBit = (tsCddMlcUart_NXP_BAUD) {
                                                             .u13SBR     = unSBRVal,             // baud = 16Mhz / 500k = 32 => OSR +1 = 32; SBR = 1
                                                             .u5OSR      = (uint8)unOverSamplingFactor,
                                                             .u1SBNS     = CDDUART_STOPBIT_SELECT(psDevCfg->ucStopBits),        // one stop bit
                                                             .u1RXEDGIE  = 0U,        // RX input active angle interrupt disabled
                                                             .u1LBKDIE   = 0U,        // LIN Break Detect Interrupt Disabled
                                                             .u1BOTHEDGE = 0U,        // BOTHEDGE=0: receiver samples only on rising edge
                                                             .u2MATCFG   = 0U,        // Match configuration disabled
                                                             .u1M10      = 0U,        // M10=0: Rx and Tx use 7 to 9 bit data characters
                                                             .u1MAEN1    = 0U,        // Match address disabled
                                                             .u1MAEN2    = 0U,        // Match address disabled
                                                             .u1RDMAE    = 0U,        // Receiver DMA request enabled
                                                             .u1TDMAE    = 0U,        // Transmitter DMA request enabled
  };

  
  //2. Configure UART Interface protocol based on Data Length and Data Direction (LSB/MSB)
  /* Configure the UART Control -  No parity, data width (8 bit data character) */
  psUART_Register->uCTRL.sBit = (tsCddMlcUart_NXP_CTRL) {
                                                            .u1PE       = CDDUART_PARITY_SELECT(psDevCfg->ucParity),         // no hardware parity generation or checking
                                                            .u1M        = 0U,                                                // Receiver and transmitter use 8-bit data characters
                                                            .u1DOZEEN   = 0U,                                                // LPUART is enabled in Doze mode (=low power)
                                                            .u1LOOPS    = 0U,                                                // TX and RX use different pins
                                                            .u1M7       = 0U,                                                // receiver and transmitter use 8-bit to 10-bit data characters
                                                            .u1SBK      = 0U,                                                // normal transmitter operation - no break character
                                                            .u1TIE      = CDDUART_DISABLE_INTERRUPT,                         // transmit interrupt disabled (hardware interrupt disabled)
                                                            .u1TCIE     = CDDUART_DISABLE_INTERRUPT,                         // transmission complete interrupt disabled (hardware interrupt disabled)
  };


  /* Configure the UART Status  - data direction */
  psUART_Register->uSTAT.sBit = (tsCddMlcUart_NXP_STAT) {
                                                           .u1RXINV    = 0U,                                                 // Receive Data not inverted
                                                           .u1MSBF     = CDDUART_BIT_ORDER_SELECT(psDevCfg->ucDataDir),      // LSB (least significant bit) first
                                                           .u1BRK13    = 0U,
  };

  // Enable uart Tx and Rx
  psUART_Register->uCTRL.sBit.u1RE = CDDUART_ENABLE_VAL_SET;
  psUART_Register->uCTRL.sBit.u1TE = CDDUART_ENABLE_VAL_SET;

}


//-----------------------------------------------------------------------------
/// \brief  CddUart_StartTransfer_Deriv
///
/// \descr  Creates the parameters for eDMA, starts the transfer
///         for Tx and Rx channels and enable eDMA data flow on LPUART
///
/// \param  ucIfc             : UART interface
/// \param  pulTransferData   : address for TX data
/// \param  pulReceiveData    : address for Rx data
/// \param  ucTxLen           : number of elements to be sent
/// \param  ucRxLen           : number of elements to be received
///
/// \return void
//-----------------------------------------------------------------------------
void CddUart_StartTransfer_Deriv(uint8 ucIfc, uint32* pulTransferData, uint32* pulReceiveData, uint8 ucTxLen, uint8 ucRxLen)
{
  // PRQA S 303  3 //Message: Cast between a pointer to volatile object and an integral type. Reason: the cast is allowed since we are accessing hardware registers
  //access the register structure
  volatile  tsCddUart_S32K_14X_Registers* psUART_Register = CDDUART_S32K_14X_PERIF_IFCBASE(ucIfc);

  //reset RX flag for DMA job completion
  CddUart_boRxSuccess = FALSE;

  psUART_Register->uBAUD.sBit.u1TDMAE = CDDUART_DISABLE_VAL_SET;         // disable transmit DMA request
  psUART_Register->uBAUD.sBit.u1RDMAE = CDDUART_DISABLE_VAL_SET;         // disable receive DMA request


  CddUart_sDMAConfigReception.pulSourceAddress    = (volatile uint32*)&(psUART_Register->uDATA.u32Register);      // PRQA S 312   //Register address needed for the dma (therefore the cast for its type)      // configures the source address of the rx parameter for dma ( data register of Uart)
  CddUart_sDMAConfigReception.pulTargetAddress    = pulReceiveData;                                               // PRQA S 310  //PRQA S 3305  //(correct usage) configures the target address of the rx parameter for dma ( pucRxData of AddMessage function)
  CddUart_sDMAConfigReception.unRepetitions       = (uint16)((uint16)ucTxLen + (uint16)ucRxLen);                                  // configures the size parameter half-duplex

  CddUart_sDMAConfigTransmission.pulSourceAddress = pulTransferData;                                              // PRQA S 310  //PRQA S 3305  //(correct usage) configures the source address of the tx parameter for dma ( data register of Uart)
  CddUart_sDMAConfigTransmission.pulTargetAddress = (volatile uint32*)&(psUART_Register->uDATA.u32Register);      // PRQA S 312   //Register address needed for the dma (therefore the cast for its type)      // configures the target address of the tx parameter for dma ( pucRxBuf of AddMessage function)
  CddUart_sDMAConfigTransmission.unRepetitions    = (uint16)ucTxLen;                                              // configures the size parameter 


  if (ucIfc == (uint8)CDDUART_IFC1)//means LPUART1
  {  
    //Start transfer for DMA Rx channel
    CddDma_StartJob(CDDUART_DMA_RX_CHANNEL, &CddUart_sDMAConfigReception, &CddUart_DMA_RX_CallbackFct);
    //Start transfer for DMA Tx channel
    CddDma_StartJob(CDDUART_DMA_TX_CHANNEL, &CddUart_sDMAConfigTransmission, NULL_PTR);
  }
  else
  {
    //not available 
  }
  //enable DMA requests for the current instance
  psUART_Register->uBAUD.sBit.u1RDMAE = CDDUART_ENABLE_VAL_SET;         //enable receive DMA request
  psUART_Register->uBAUD.sBit.u1TDMAE = CDDUART_ENABLE_VAL_SET;         //enable transmit DMA request
}


//-----------------------------------------------------------------------------
/// \brief   DMA_RX_CallbackFct
///
/// \descr   CHANNEL CDDDMA_REQ_LPUART1_RX (DMA CH.8) transfer complete - RX callback
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddUart_DMA_RX_CallbackFct(void)
{
  // PRQA S 303  3 //Message: Cast between a pointer to volatile object and an integral type. Reason: the cast is allowed since we are accessing hardware registers
  //access the register structure
  volatile  tsCddDma_S32K_146_Registers* psDMA_Register = CDDUART_S32K_14X_DMA_BASE;

  //disable requests for RX channel
  CddDma_EnableHwTrigger(CDDUART_DMA_RX_CHANNEL, FALSE);

  //clear interrupt status
  psDMA_Register->Reg_CINT.ucData = (uint8)CDDUART_DMA_RX_CHANNEL;

  CddUart_boRxSuccess = TRUE;            // successful reception
  CddUart_SendReceived_Irq0();            // calls the callback function when the full response is received 
}

//-----------------------------------------------------------------------------
/// \brief  CddUart_TransferCompleteDMA_Derive
///
/// \descr  Check if a transmission has been already completed on RX channel
///
/// \param  ucIfc     : Uart Interface in which the transmission completion is checked
///
/// \return boolean 
///           -TRUE : Transmission has been completed
///           -FALSE: Transmission has not been completed
//-----------------------------------------------------------------------------
boolean CddUart_TransferCompleteDMA_Deriv(uint8 ucIfc)
{
  boolean boJobDone = FALSE;
  if (ucIfc == (uint8)CDDUART_IFC1)
  {
    boJobDone = CddDma_IsJobCompleted(CDDUART_DMA_RX_CHANNEL);
  }
  else
  {
    //no other interfaces configured yet
  }
  return boJobDone;
}

//-----------------------------------------------------------------------------
/// \brief  CddUart_GetRxCbStatus
///
/// \descr  This function informs the upper layer about the reception status
///         TRUE - interrupt performed, Reception completed successfully
///         FALSE - interrupt not triggered
///
/// \param  -
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CddUart_GetRxCbStatus(void)
{
  return CddUart_boRxSuccess;
}

//-----------------------------------------------------------------------------
/// \brief  CddUart_FillTxFifo
///
/// \descr  Write to the HW register the data passed as argument
///
/// \param  ucIfc     : interface to select the Tx-HW Buffer to be filled up 
/// \param  pucTxData : pointer to buffer data
/// \param  ucLength  : number of elements 
///
/// \return void
//-----------------------------------------------------------------------------
void CddUart_FillTxFifo(uint8 ucIfc, uint8* pucTxData, uint8 ucLength)
{
  // PRQA S 303  3 //Message: Cast between a pointer to volatile object and an integral type. Reason: the cast is allowed since we are accessing hardware registers
  //access the register structure
  volatile  tsCddUart_S32K_14X_Registers* psUART_Register = CDDUART_S32K_14X_PERIF_IFCBASE(ucIfc);
  //psUART_Register = &CddUart_sS32K_14X_Registers;

  if (pucTxData != NULL_PTR)
  {
    for (uint8 ucIdx = 0u; ucIdx < ucLength; ucIdx++)
    {
      psUART_Register->uDATA.u32Register = (uint32)pucTxData[ucIdx];

     // while ((psUART_Register->uSTAT.u32Register & CDDUART_STAT_TDRE_MASK) >> CDDUART_STAT_TDRE_SHIFT == 0U) {}

    }
  }

}

//-----------------------------------------------------------------------------
/// \brief  CddUart_ReadRxFifo
///
/// \descr  Read from the HW register and save the data to the buffer 
///         passed as argument
///
/// \param  ucIfc      : interface to select the Rx-HW Buffer to be read
/// \param  pucRxData  : pointer to buffer data
/// \param  unLength   : number of elements 
///
/// \return void
//-----------------------------------------------------------------------------
void CddUart_ReadRxFifo(uint8 ucIfc, uint8* pucRxData, uint16 unLength) 
{
  // PRQA S 303  3 //Message: Cast between a pointer to volatile object and an integral type. Reason: the cast is allowed since we are accessing hardware registers
  //access the register structure
  volatile  tsCddUart_S32K_14X_Registers* psUART_Register = CDDUART_S32K_14X_PERIF_IFCBASE(ucIfc);
  //psUART_Register = &CddUart_sS32K_14X_Registers;

  if (pucRxData != NULL_PTR)
  {
    for (uint8 ucIdx = 0u; ucIdx < unLength; ucIdx++)
    {
      pucRxData[ucIdx] = (uint8)psUART_Register->uDATA.u32Register;  //cast needed because only 8 bits out of 32 are filled with data
    }

  }
}

//-----------------------------------------------------------------------------
/// \brief  CddUart_RxIntEnable
///
/// \descr  Enable Rx Interrupt
///
/// \param  ucIfc : uart interface in which Rx Interrupt is enabled
///
/// \return void
//-----------------------------------------------------------------------------
void CddUart_RxIntEnable(uint8 ucIfc)
{
  (void)ucIfc;
}


//-----------------------------------------------------------------------------
/// \brief CddUart_IfcIdle_Deriv
///
/// \descr  Check Idle Status
///
/// \param  ucIfc: Uart Interface in which status is checked 
///
/// \return boolean 
///           -TRUE : Interface is in idle status
///           -FALSE: Interface is not in idle status
//-----------------------------------------------------------------------------
boolean CddUart_IfcIdle_Deriv(uint8 ucIfc)
{
  // PRQA S 303 2 //Message: Cast between a pointer to volatile object and an integral type. Reason: the cast is allowed since we are accessing hardware registers
  volatile  tsCddUart_S32K_14X_Registers* psUART_Register = CDDUART_S32K_14X_PERIF_IFCBASE(ucIfc);
  psUART_Register = &CddUart_sS32K_14X_Registers;

  return (psUART_Register->uSTAT.sBit.u1IDLE != 0u) ? TRUE : FALSE;
}




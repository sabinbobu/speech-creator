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
/// \file  CddSpi_S32K_14X.c
///
/// \brief
///
//-----------------------------------------------------------------------------
//=============================================================================
//  includes
//=============================================================================
#include <Std_Types.h>
#include <CddSpi_Cfg.h>
#include <CddSpi_S32K_14X.h>
#include <CddSpi_S32K_14X_Types.h>
#include <AL_Helper.h>
#include <CddDma.h>

//=============================================================================
// Private Preprocessor definitions
//=============================================================================
#define CDDSPI_S32K_14X_REF_FREQ                      5000000UL       //500Khz
#define CDDSPI_S32K_14X_FIFO_ELEMENTS                 4U
#define CDDSPI_S32K_14X_AUX_FIFO_ELEMENTS             20U
#ifndef UNIT_TEST
#define CDDSPI_S32K_14X_PERI_BASE                       (0x4002C000UL)
#define CDDSPI_S32K_14X_PERI_IFCBASE(n)                 ((volatile tsCddSpi_S32K146_PERI*)(CDDSPI_S32K_14X_PERI_BASE + (0x00001000UL * (n)) ))
#define CDDSPI_S32K_14X_PERI                            ((volatile tsCddSpi_S32K146_PERI*)(CDDSPI_S32K_14X_PERI_BASE + 0x00000000UL))
#else
STATIC_AL volatile tsCddSpi_S32K146_PERI                dummyPERI;
#define CDDSPI_S32K_14X_PERI_IFCBASE(n)                 ((volatile tsCddSpi_S32K146_PERI*)(&dummyPERI))
#define CDDSPI_S32K_14X_PERI                            ((volatile tsCddSpi_S32K146_PERI*)(&dummyPERI))
#endif


#define CDDSPI_S32K_14X_PRESCASCALER_1MBAUD 0x3U
#define CDDSPI_S32K_14X_PRESCASCALER_500KBAUD 0x4U

//=============================================================================
// Private variables
//=============================================================================

//=============================================================================
// Private function  prototypes
//=============================================================================

//=============================================================================
// Public functions  impleme;ntation
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  CddSpi_InitIfc_Deriv
///
/// \descr  Configure Spi Motorola Master Mode
///         Configure Peripheral Devider 
///
/// \param  ucIfc: Spi Interface to be configured
///
/// \return - 
//-----------------------------------------------------------------------------
void CddSpi_InitIfc_Deriv(uint8 ucIfc)
{
  // PRQA S 303 3 //Message: Cast between a pointer to volatile object and an integral type. Reason: the cast is allowed since we are accessing hardware registers
  //Resgisters structure
  volatile tsCddSpi_S32K146_PERI* psPERI = CDDSPI_S32K_14X_PERI_IFCBASE(ucIfc); 

  //Software reset of and disable LPSPI
  psPERI->unCR.sBit.u1RST = 1U;
  psPERI->unCR.ulData = 0U;

  //Set master mode
  psPERI->unCFGR1.sBit.u1MASTER = 1U;

  //Set pins configuration
  psPERI->unCFGR1.sBit.u1PCSCFG = 0U; //PCS[3:2] are configured for chip select function
  psPERI->unCFGR1.sBit.u1OUTCFG = 0U; //Output data retains last value when chip select is negated
  psPERI->unCFGR1.sBit.u1PCSCFG = 0U; //SIN is used for input data and SOUT is used for output data

  //get FifoSize

  //disable LPSPI
  psPERI->unCR.sBit.u1MEN = 0U;

  //Set PCS polarity
  psPERI->unCFGR1.sBit.u4PCSPOL = 0U; //=0 PCS[n] pin is active low

  //Set Delays
  //In master mode: configures the delay from the last SCK edge to the PCS negation.
  //   - The delay is equal to (SCKPCS + 1) cycles of the LPSPI functional clock divided by the Prescaler Value TCR[PRESCALE] configuration.
  //   - The minimum delay is 1 cycle.
  psPERI->unCCR.sBit.u8SCKPCS = 0U; 
  //In master mode: configures the delay from the PCS assertion to the first SCK edge.
  //   - The delay is equal to(PCSSCK + 1) cycles of the LPSPI functional clock divided by the Prescaler Value TCR[PRESCALE] configuration.
  //   - The minimum delay is 1 cycle.
  psPERI->unCCR.sBit.u8PCSSCK = 0U;
  //In master mode:
  //   - Configures the delay from the PCS negation to the next PCS assertion.
  //     - The delay is equal to(DBT + 2) cycles of the LPSPI functional clock divided by the Prescaler Value TCR[PRESCALE] configuration.
  //     - The minimum delay is 2 cycles.
  //     - Half of the delay occurs before PCS assertion and the other half of the delay occurs after PCS negation.
  //       If the command word is updated between 2 transfers, then the command word is updated half - way between the PCS negation of
  //       the last transfer and PCS assertion of the next transfer.
  //     - The command word sets which PCS signal is used(of PCS[3:0]), the polarity / phase of the SCK signal, and the Prescaler Value.
  //   - Configures the delay from the last SCK edge of a transfer word and the first SCK edge of the next transfer word, in a continuous transfer.
  //     - The delay is equal to(DBT + 1) cycles of the LPSPI functional clock divided by the Prescaler Value TCR[PRESCALE] configuration.
  //     - The minimum delay is 1 cycle.
  psPERI->unCCR.sBit.u8DBT = 0U;
  //In master mode, the SCK Divider configures the divide ratio of the SCK pin.
  //   - The SCK period is equal to(SCKDIV + 2) cycles of the LPSPI functional clock divided by the Prescaler Value TCR[PRESCALE] configuration.
  //   - The minimum SCK period is 2 cycles.
  //   - If the SCK period is an odd number of cycles, then the 1st half of the SCK period will be 1 cycle longer than the 2nd half of the SCK period.
  psPERI->unCCR.sBit.u8SCKDIV = 0U;

  //Set Sampling Point
  //When set, LPSPI master will sample the input data on a delayed LPSPI_SCK edge, which improves the setup time when sampling data
  //The input data setup time in master mode with delayed LPSPI_SCK edge is equal to the input data setup time in slave mode
  psPERI->unCFGR1.sBit.u1SAMPLE = 1U; 

  //Enable SPI
  psPERI->unCR.sBit.u1MEN = 1U;

  //default value - as in SDK - not relevant
  psPERI->unFCR.sBit.u2TXWATER = 2U;

}

//-----------------------------------------------------------------------------
/// \brief CddSpi_DeInitIFc_Deriv
///
/// \descr Disable Spi Interface
///
/// \param  ucIfc : Spi Interface to be deinitialized
///
/// \return void
//-----------------------------------------------------------------------------
void CddSpi_DeInitIfc_Deriv(uint8 ucIfc)
{
  // PRQA S 303 3 //Message: Cast between a pointer to volatile object and an integral type. Reason: the cast is allowed since we are accessing hardware registers
  //Resgisters structure
  volatile tsCddSpi_S32K146_PERI* psPERI = CDDSPI_S32K_14X_PERI_IFCBASE(ucIfc); 

  //Software reset of and disable LPSPI
  psPERI->unCR.sBit.u1RST = 1U;
  psPERI->unCR.ulData = 0U;
}

//-----------------------------------------------------------------------------
/// \brief  CddSpi_ConfigureTransfer_Deriv
///
/// \descr  Configure transmission parameters passed to the function by setting
///         the Target HW Registers accordingly:
///          - Baudrate
///          - LSB/MSB
///          - Clock Phase
///          - Clock Polarity
///          - Data Width
///          - LSB/MSB
///
/// \param  psDevCfg : pointer to  device data configuration
///
/// \return -
//-----------------------------------------------------------------------------
void CddSpi_ConfigureTransfer_Deriv(const tsCddSpiDevCfg* psDevCfg)
{
  // PRQA S 303 2 //Message: Cast between a pointer to volatile object and an integral type. Reason: the cast is allowed since we are accessing hardware registers
  volatile tsCddSpi_S32K146_PERI* psPERI = CDDSPI_S32K_14X_PERI_IFCBASE((uint32)psDevCfg->ucSpiIfc); 

  //Reset Status Register
  psPERI->unSR.ulData = 0U;

  tuCddSpi_S32K146_TCR uTempTCR;
  uint8 ucContBit = (psDevCfg->ucElements > 1U) ? 1U : 0U;
  uint8 ucPrescale = psDevCfg->ucBrs == CDDSPI_BRS_1M ? CDDSPI_S32K_14X_PRESCASCALER_1MBAUD : CDDSPI_S32K_14X_PRESCASCALER_500KBAUD;
  uint8 ucLSBF = (psDevCfg->ucDataDir == 0U) ? 1U : 0U;

  uTempTCR.sBit = (tsCddSpi_S32K146_TCR) {
                                          .u12FRAMESZ = psDevCfg->ucDataLen - 1U,
                                          .u2WIDTH    = 0U,                   //1 bit transfer
                                          .u1TXMSK    = 0U,                   //Normal transfer
                                          .u1RXMSK    = 0U,                   //Normal transfer
                                          .u1CONTC    = 0U,                   //...
                                          .u1CONT     = ucContBit,            //...
                                          .u1BYSW     = 0U,                   //Byte swap is disabled
                                          .u1LSBF     = ucLSBF,               //0 - MSB, 1 - LSB
                                          .u2PCS      = psDevCfg->ucCs,       //Which Chip Select
                                          .u3PRESCALE = ucPrescale,           //1, 2, 4, 8, 16, 32 ,64, 128
                                          .u1CPHA     = psDevCfg->ucCPha,     //
                                          .u1CPOL     = psDevCfg->ucCPol,     //
  };

  psPERI->unTCR.ulData = uTempTCR.ulData;
}

//-----------------------------------------------------------------------------
/// \brief CddSpi_TxFifoPut_Deriv
///
/// \descr Put data passed as argument to the Tx-Hw Buffer
///
/// \param  ucIfc: Interface whose TX-Hw buffer has to be filled up
///         punData: Pointer to Buffer Data
///         unLength: Number of elements
///
/// \return  void
//-----------------------------------------------------------------------------
void CddSpi_TxFifoPut_Deriv(uint8 ucIfc, const uint16* punData, uint16 unLength)
{
  // PRQA S 303 2 //Message: Cast between a pointer to volatile object and an integral type. Reason: the cast is allowed since we are accessing hardware registers
  volatile tsCddSpi_S32K146_PERI* psPERI = CDDSPI_S32K_14X_PERI_IFCBASE(ucIfc); 

  if (punData != NULL_PTR)
  {
    for (uint16 unIdx = 0U; unIdx < unLength; unIdx++)
    {
      psPERI->unTDR.ulData = (uint32)punData[unIdx];
      while (psPERI->unFSR.sBit.u3TXCOUNT == CDDSPI_S32K_14X_FIFO_ELEMENTS)
      {
        //if the HW get stuck at this point it will occure a WDT reset
#ifdef UNIT_TEST
        // in case of Unit Test simulate HW decrement
        psPERI->unFSR.sBit.u3TXCOUNT--;
#endif
      }
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief CddSpi_RxFifoGet_Deriv
///
/// \descr Return Data available in Rx-HW Buffer 
///
/// \param  ucIfc : Spi interface whose Rx-HW buffer belongs to.
///         punData: Pointer to Buffer Data
///         unLength: Number of elements
///
/// \return void
//-----------------------------------------------------------------------------
void  CddSpi_RxFifoGet_Deriv(uint8 ucIfc, uint16* punData, uint16 unLength)
{
  // PRQA S 303 2 //Message: Cast between a pointer to volatile object and an integral type. Reason: the cast is allowed since we are accessing hardware registers
  volatile tsCddSpi_S32K146_PERI* psPERI = CDDSPI_S32K_14X_PERI_IFCBASE(ucIfc); 

  if (punData != NULL_PTR)
  {
    for (uint16 unIdx = 0U; unIdx < unLength; unIdx++)
    {
      punData[unIdx] = (uint16)psPERI->unRDR.ulData;
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief CddSpi_IfcIdle_Deriv
///
/// \descr  Check Idle Status
///
/// \param  ucIfc: Spi Interface in which status is checked 
///
/// \return boolean 
///           -TRUE : Interface is in idle status
///           -FALSE: Interface is not in idle status
//-----------------------------------------------------------------------------
boolean CddSpi_IfcIdle_Deriv(uint8 ucIfc)
{
  // PRQA S 303 2 //Message: Cast between a pointer to volatile object and an integral type. Reason: the cast is allowed since we are accessing hardware registers
  volatile tsCddSpi_S32K146_PERI* psPERI = CDDSPI_S32K_14X_PERI_IFCBASE(ucIfc); 

  return ((psPERI->unSR.sBit.u1MBF == 0U) ? TRUE : FALSE);
}

//-----------------------------------------------------------------------------
/// \brief  CddSpi_TransferComplete_Derive
///
/// \descr  Check if a transmission has been already completed
///
/// \param  ucIfc     : Spi Interface in which the transmission completion is checked
/// \param  unTranSize: Number of data that the transmission consists of
///
/// \return boolean 
///           -TRUE : Transmission has been completed
///           -FALSE: Transmission has not been completed
//-----------------------------------------------------------------------------
boolean CddSpi_TransferComplete_Deriv(uint8 ucIfc, uint16 unTranSize)
{
  // PRQA S 303 2 //Message: Cast between a pointer to volatile object and an integral type. Reason: the cast is allowed since we are accessing hardware registers
  volatile tsCddSpi_S32K146_PERI* psPERI = CDDSPI_S32K_14X_PERI_IFCBASE(ucIfc); 

  return ((psPERI->unFSR.sBit.u3RXCOUNT == unTranSize) ? TRUE : FALSE);
}

//-----------------------------------------------------------------------------
/// \brief  CddSpi_TransferCompleteDMA_Derive
///
/// \descr  Check if a transmission has been already completed on RX channel
///
/// \param  ucIfc     : Spi Interface in which the transmission completion is checked
///
/// \return boolean 
///           -TRUE : Transmission has been completed
///           -FALSE: Transmission has not been completed
//-----------------------------------------------------------------------------
boolean CddSpi_TransferCompleteDMA_Deriv(uint8 ucIfc)
{
  return CddDma_IsJobCompleted(ucIfc == 0U ? LPSPI0_RX : LPSPI1_RX);
}

//-----------------------------------------------------------------------------
/// \brief CddSpi_RxEventTriggered_Deriv
///
/// \descr Check if Rx Event has been triggered
///
/// \param  ucIfc : Spi Interface in which Rx Event is checked
///
/// \return boolean
///          -TRUE  : Event has been triggered
///          -FALSE : Event has not been triggered
//-----------------------------------------------------------------------------
boolean CddSpi_RxEventTriggered_Deriv(uint8 ucIfc)
{
  (void)ucIfc;
  return FALSE;
}

//-----------------------------------------------------------------------------
/// \brief CddSpi_RxIntEnable_Deriv
///
/// \descr Enable Rx Interrupt
///
/// \param  ucIfc : Spi Interface in which Rx Interrupt is enabled
///
/// \return void
//-----------------------------------------------------------------------------
void CddSpi_RxIntEnable_Deriv(uint8 ucIfc)
{
  (void)ucIfc;
}

//-----------------------------------------------------------------------------
/// \brief CddSpi_RxIntDisable_Deriv
///
/// \descr Disable Rx Interrupt
///
/// \param  ucIfc : Spi Interface in which Rx Interrupt is disabled
///
/// \return void
//-----------------------------------------------------------------------------
void CddSpi_RxIntDisable_Deriv(uint8 ucIfc)
{
  (void)ucIfc;
}

//-----------------------------------------------------------------------------
/// \brief CddSpi_RxTriggerEventClear_Deriv
///
/// \descr Clear Triggered Rx Event
///
/// \param  ucIfc : Spi Interface in which Rx Event is cleared
///
/// \return void
//-----------------------------------------------------------------------------
void CddSpi_RxTriggerEventClear_Deriv(uint8 ucIfc)
{
  (void)ucIfc;
}

//-----------------------------------------------------------------------------
/// \brief CddSpi_DmaStop_Deriv
///
/// \descr Disable DMA data flow
///
/// \param  ucIfc : Spi Interface in which Dma data flow is disabled
///
/// \return void
//-----------------------------------------------------------------------------
void CddSpi_DmaStop_Deriv(uint8 ucIfc)
{
  // PRQA S 303 2 //Message: Cast between a pointer to volatile object and an integral type. Reason: the cast is allowed since we are accessing hardware registers
  volatile tsCddSpi_S32K146_PERI* psPERI = CDDSPI_S32K_14X_PERI_IFCBASE(ucIfc); 

  //disable DMA data flow
  psPERI->unDER.sBit.u1RDDE = 0U; //Receive Data DMA Enable
  psPERI->unDER.sBit.u1TDDE = 0U; //Transmit Data DMA Enable

  //Clear Status Register
  psPERI->unSR.ulData = 0U;
  //Clear TCR
  psPERI->unTCR.ulData = 0U;
}

//-----------------------------------------------------------------------------
/// \brief  CddSpi_GetCommandWord_Deriv
///
/// \descr  Returns the transmission configuration parameters passed to the function by setting
///         a local HW Register accordingly:
///          - Baudrate
///          - LSB/MSB
///          - Clock Phase
///          - Clock Polarity
///          - Data Width
///          - LSB/MSB
///
/// \param  psDevCfg : pointer to device data configuration
///         ucIdx : index of device (helpful if is a daisy cahin config)
///
/// \return uTempTCR.ulData : command word for a specific index
//-----------------------------------------------------------------------------
uint32 CddSpi_GetCommandWord_Deriv(const tsCddSpiDevCfg* psDevCfg, uint8 ucIdx)
{
  tuCddSpi_S32K146_TCR uTempTCR;

  boolean boIsLast = ((ucIdx + 1U) == psDevCfg->ucElements ? TRUE : FALSE);
  uint8 ucContC = (psDevCfg->ucElements > 1U && ucIdx > 0U)       ? 1U : 0U;
  uint8 ucCont  = (psDevCfg->ucElements > 1U && boIsLast != TRUE) ? 1U : 0U;
  uint8 ucPrescale = psDevCfg->ucBrs == CDDSPI_BRS_1M ? CDDSPI_S32K_14X_PRESCASCALER_1MBAUD : CDDSPI_S32K_14X_PRESCASCALER_500KBAUD;
  uint8 ucLSBF = (psDevCfg->ucDataDir == 0U) ? 1U : 0U;

  uTempTCR.sBit = (tsCddSpi_S32K146_TCR) {
                                          .u12FRAMESZ = psDevCfg->ucDataLen - 1U, //
                                          .u2WIDTH    = 0U,                       //1 bit transfer
                                          .u1TXMSK    = 0U,                       //Normal transfer
                                          .u1RXMSK    = 0U,                       //Normal transfer
                                          .u1CONTC    = ucContC,                  //...
                                          .u1CONT     = ucCont,                   //...
                                          .u1BYSW     = 0U,                       //Byte swap is disabled
                                          .u1LSBF     = ucLSBF,                   //0 - MSB, 1 - LSB
                                          .u2PCS      = psDevCfg->ucCs,           //Which Chip Select
                                          .u3PRESCALE = ucPrescale,               //1, 2, 4, 8, 16, 32 ,64, 128
                                          .u1CPHA     = psDevCfg->ucCPha,         //
                                          .u1CPOL     = psDevCfg->ucCPol,         //
  };

  return uTempTCR.ulData;
}

//-----------------------------------------------------------------------------
/// \brief  CddSpi_StartTransfer_Deriv
///
/// \descr  Creates the parameters for eDMA, starts the transfer
///         for Tx and Rx channels and enable eDMA data flow on LPSPI
///
/// \param  ucIfc : Spi Interface
///         pulTransferData : address for TX data
///.........pulReceiveData : addres for RX data
///         unLen : number of words to be transferd
///
/// \return -
//-----------------------------------------------------------------------------

void CddSpi_StartTransfer_Deriv(uint8 ucIfc, uint32* pulTransferData, uint32* pulReceiveData, uint16 unLen)
{
  // PRQA S 303 2 //Message: Cast between a pointer to volatile object and an integral type. Reason: the cast is allowed since we are accessing hardware registers
  volatile tsCddSpi_S32K146_PERI* psPERI = CDDSPI_S32K_14X_PERI_IFCBASE(ucIfc); 

  //Clear Status Register
  psPERI->unSR.ulData  = 0U;
  //Clear TCR
  psPERI->unTCR.ulData = 0U;

  //disable DMA data flow
  psPERI->unDER.sBit.u1RDDE = 0U; //Receive Data DMA Enable
  psPERI->unDER.sBit.u1TDDE = 0U; //Transmit Data DMA Enable
 
  /*
    Msg: 310(Casting to different object pointer type.)
    Msg: 312(Dangerous pointer cast results in loss of volatile qualification.)
  */
  tsCddDma_Parameter sCddDmaConfigTX = { .pulSourceAddress = pulTransferData,
                                         .pulTargetAddress = (uint32*)(&(psPERI->unTCR)), // PRQA S 310, 312  //the cast is allowed since we are accessing hardware register
                                         .unRepetitions    = unLen
  };

  /*
    Msg: 310(Casting to different object pointer type.)
    Msg: 312(Dangerous pointer cast results in loss of volatile qualification.)
  */
  tsCddDma_Parameter sCddDmaConfigRX = { .pulSourceAddress = (uint32*)(&(psPERI->unRDR)), // PRQA S 310, 312  //the cast is allowed since we are accessing hardware register
                                         .pulTargetAddress = pulReceiveData,
                                         .unRepetitions    = unLen
  };

  //Start transfer for RX channel
  CddDma_StartJob((ucIfc == 0U ? LPSPI0_RX : LPSPI1_RX), &sCddDmaConfigRX, NULL_PTR);
  //Start transfer for TX channel
  CddDma_StartJob((ucIfc == 0U ? LPSPI0_TX : LPSPI1_TX), &sCddDmaConfigTX, NULL_PTR);
  

  //enable DMA data flow
  psPERI->unDER.sBit.u1RDDE = 1U; //Receive Data DMA Enable
  psPERI->unDER.sBit.u1TDDE = 1U; //Transmit Data DMA Enable
}

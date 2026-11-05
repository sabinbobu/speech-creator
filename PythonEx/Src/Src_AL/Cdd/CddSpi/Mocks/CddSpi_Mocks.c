#include <Std_Types.h>
#include <stdio.h>

/* PRQA S 3408 EOF */

//==============================================================================
// Extern Vars
//==============================================================================
//CddSpi_Init variables to read and check
uint16   Mt_CddSpi_Init_CallCounter = 0U;

//CddSpi_TransferMsg variables to read and check
uint16   Mt_CddSpi_TransferMsg_CallCounter = 0U;
boolean  Mt_CddSpi_TransferMsg_boRetVal;
uint8    Mt_CddSpi_TransferMsg_ucDevice;

//CddSpi_TransferMsg variables to set and simulate
uint16*  Mt_CddSpi_TransferMsg_punDataTx;
uint16*  Mt_CddSpi_SpiBuffer_punRxData;
boolean* Mt_CddSpi_pboReturn;

//Index for Buffer 
uint8 Mt_CddSpi_SpiBuffer_ucAccessIndex;
uint8 Mt_CddSpi_SpiBuffer_ucIndexMax;

//Spi driver state
uint8 Mt_CddSpi_ucState;

//==============================================================================
// Mocks
//==============================================================================
void CddSpi_Init(void)
{
  Mt_CddSpi_Init_CallCounter++;
}

// ---------------------------------------------------------------------------
///
///  \func   Mt_CddSpi_SPIRegisterRxDataBuffer
///
///  \brief  By calling this function the RxData Buffer can be created.
///
///  \param  uint8    ucLen: the length of buffer
///          uint16*  puRxData: point to the RxData of buffer
///          boolean* pboRetur: point to the Return value of buffer
///
///  \return void
///
// ---------------------------------------------------------------------------
void Mt_CddSpi_SPIRegisterRxDataBuffer(uint8 ucLen, uint16* punRxData, boolean * pboReturn)
{
  // get the RxData Buffer
  Mt_CddSpi_SpiBuffer_punRxData = punRxData;

  // get the Return Buffer
  Mt_CddSpi_pboReturn = pboReturn;

  // set the AccessIndex with 0
  Mt_CddSpi_SpiBuffer_ucAccessIndex = 0;

  // set the maximal Index
  Mt_CddSpi_SpiBuffer_ucIndexMax = ucLen;

  // reset the Call counter
  Mt_CddSpi_TransferMsg_CallCounter = 0;
}

// ---------------------------------------------------------------------------
///
/// \func  CddSpi_TransferMsg
///
/// \brief This function simulates the SPI-Transfer. The TxData is stored in 
///        Mt_CddSpi_TransferMsg_punDataTx. The RxData and the return value are
///        simulated with the buffer *(Mt_CddSpi_SpiBuffer_punRxData) with the
///        Index Mt_CddSpi_SpiBuffer_ucAccessIndex.
///
/// \param  eDevice = target SPI peripheral
///                   - use macro CDDSPI_DEVICE(name) as parameter
///                   - name = name of SPI peripheral specified in CddSpi_Cfg.h
///         pData   = in/out parameter (pointer)
///                   - data given in this variable will be sent to peripheral
///                   - data received by the peripheral will be placed in this
///                     variable if the function returns "true"
///
/// \return boolean   returns true if the function call was successful and 
///                   the variable pointed to by pData holds the value 
///                   received by the SPI peripheral
///
// ---------------------------------------------------------------------------
boolean CddSpi_TransferMsg(uint8 ucDevice, uint16* punData)
{
  boolean boReturn = FALSE;

  // counter for check
  Mt_CddSpi_TransferMsg_CallCounter++;
  // get the device number
  Mt_CddSpi_TransferMsg_ucDevice = ucDevice;
  // get the SPI Tx Data
  Mt_CddSpi_TransferMsg_punDataTx = punData;

  // Read back the simulated receive data from buffer.
  if (Mt_CddSpi_SpiBuffer_ucAccessIndex < Mt_CddSpi_SpiBuffer_ucIndexMax)
  {
    // get the RxData with the index
    *punData = *(Mt_CddSpi_SpiBuffer_punRxData + Mt_CddSpi_SpiBuffer_ucAccessIndex);

    // get the return value with the index
    boReturn = *(Mt_CddSpi_pboReturn + Mt_CddSpi_SpiBuffer_ucAccessIndex);
    Mt_CddSpi_SpiBuffer_ucAccessIndex++;
  }
  else
  {
    // set 0xFFFF if index is out of range
    *punData = 0xFFFF;
  }

  return boReturn;
}


//-----------------------------------------------------------------------------
/// \brief CddSpi_GetState
///
/// \descr Return CddSpi State:
///         -CDDSPI_STATE_RESET
///         -CDDSPI_STATE_SINGLE_OPERATION
///         -CDDSPI_STATE_CYCLIC_OPERATION
///
/// \param  -
///
/// \return teCddSpiState
//-----------------------------------------------------------------------------
uint8 CddSpi_GetState(void)
{
  return Mt_CddSpi_ucState;
}

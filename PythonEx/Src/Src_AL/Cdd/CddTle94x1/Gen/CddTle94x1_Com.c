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
/// \file  CddTle94x1_Com.c
///
/// \brief  SBC Infineon TLE9471 specific complex device driver
///
/// \descr  System Basic Chip
///
/// \author Diana Ursan
/// \e-mail: elena-diana.ursan[at]marelli.com
///
//-----------------------------------------------------------------------------

//=============================================================================
// Standard / system header file includes
//=============================================================================

#include <AL_Helper.h>

//=============================================================================
//  Project-specific header file includes
//=============================================================================
#include <CddSbc.h>
#include <CddTle94x1.h>
#include <CddTle94x1_Cb.h>
#include <CddTle94x1_Cfg.h>
#include "CddTle94x1_Types.h"
#include "CddTle94x1_Com.h"
#include <../../St126/Cdd/CddSbc/CddSbc_Cfg.h>
#ifndef UNIT_TEST
#include <interrupt_manager.h>
#endif

//=============================================================================
// Global Variables
//=============================================================================

//=============================================================================
// Local variable
//=============================================================================
// current entry in the schedule queue whose data must be sent via SPI bus
STATIC_AL uint8 CddSbc_ucQueueReadIndex = 0u;
STATIC_AL uint8 CddSbc_ucQueueTXIndex = 1u;

// current entry in the schedule queue available for new data
STATIC_AL uint8 CddSbc_ucQueueWriteIndex = 1u;

// SPI schedule queue: this queue contains the messages which are sent to the SPI one at a time, at each call of CddSbc_SpiRx and CddSbc_SpiTx
STATIC_AL tsCddSbc_SpiScheduleQueue CddSbc_asSpiScheduleQueue[CDDSBC_CFG_MAX_SPI_SCHED_QUEUE] = { 0 };


//=============================================================================
// Function definitions
//=============================================================================
//-----------------------------------------------------------------------------
/// \brief  Called between reception of SPI telegram and transmission of next SPI telegram
///
/// \descr  The function argument provides the data read from the SPI, which is saved
///         in the current entry of the scheduler queue
///
/// \param  uint16      unIx:         unused
///         uint32      ulData:       raw RX data (16 LSB are valid)
///
/// \return void
//-----------------------------------------------------------------------------
void CddTle94x1_SpiRx(uint16 unIx, uint32 ulData)
{
  (void)unIx;
#ifndef UNIT_TEST
  DISABLE_INTERRUPTS();
#endif

  // If the entry is not processed.
  if (CddSbc_asSpiScheduleQueue[CddSbc_ucQueueReadIndex].CddSbc_boProcessEntry != FALSE)
  {

    // copy data read from SPI to the read buffer
    CddSbc_asSpiScheduleQueue[CddSbc_ucQueueReadIndex].CddSbc_unRxData = (uint16)ulData;


    // If there is a callback function configured
    if (CddSbc_asSpiScheduleQueue[CddSbc_ucQueueReadIndex].CddSbc_ReadClbckFunc != NULL_PTR)
    {
      // send the read data to the user
      CddSbc_asSpiScheduleQueue[CddSbc_ucQueueReadIndex].CddSbc_ReadClbckFunc(ulData, CddSbc_asSpiScheduleQueue[CddSbc_ucQueueReadIndex].CddSbc_unTxData);
    }
    else
    {
      // do nothing
    }

    // finished processing this entry
    CddSbc_asSpiScheduleQueue[CddSbc_ucQueueReadIndex].CddSbc_boProcessEntry = FALSE;

    // If there is no more entry to process in the queue
    uint8 ucNextQueueReadIndex = (CddSbc_ucQueueReadIndex + 1u) % CDDSBC_CFG_MAX_SPI_SCHED_QUEUE;

    if (CddSbc_asSpiScheduleQueue[ucNextQueueReadIndex].CddSbc_boProcessEntry == FALSE)
    {
      // Insert the default message
      CddSbc_InsertDefaultMessage();
    }
    else
    {
      // do nothing
    }
  }
  else
  {
    // do nothing
  }
#ifndef UNIT_TEST
  ENABLE_INTERRUPTS();
#endif
}

//-----------------------------------------------------------------------------
/// \brief  Called between reception of SPI telegram and transmission of next SPI telegram
///
/// \descr  This function gets the raw SPI Tx from the queue and sents it to the CddSpi with a return
///
/// \param  uint16      unIx:         unused
///
/// \return uint32 ulReturnSpiTxMsg
//-----------------------------------------------------------------------------
uint32 CddTle94x1_SpiTx(uint16 unIx)
{
  (void)unIx;

  uint32 ulReturnSpiTxMsg = 0u;
#ifndef UNIT_TEST
  DISABLE_INTERRUPTS();
#endif

  // If there are messages to process
  if (CddSbc_asSpiScheduleQueue[CddSbc_ucQueueTXIndex].CddSbc_boProcessEntry != FALSE)
  {
    // Store the message in the return value
    ulReturnSpiTxMsg = CddSbc_asSpiScheduleQueue[CddSbc_ucQueueTXIndex].CddSbc_unTxData;

    // finished processing this entry
    //CddSbc_asSpiScheduleQueue[CddSbc_ucQueueTXIndex].CddSbc_boProcessEntry = FALSE;

    CddSbc_ucQueueReadIndex = CddSbc_ucQueueTXIndex;

    // increment the read index circularly
    CddSbc_ucQueueTXIndex = (CddSbc_ucQueueTXIndex + 1u) % CDDSBC_CFG_MAX_SPI_SCHED_QUEUE;
  }
  else
  {
    // do nothing
  }
#ifndef UNIT_TEST
  ENABLE_INTERRUPTS();
#endif
  return ulReturnSpiTxMsg;
}

//-----------------------------------------------------------------------------
//
/// \brief  Function which inserts a new read/write command in the scheduler queue
///
/// \descr  The function increments the write counter and, if the place is free
///         i.e. the entry on that place was already processed, assembles the SPI
///         message from the SBC register address (the most significant nibble)
///         and the data to be written in the register (the least significant nibble)
///
/// \param  uint8 ucAddress             : address of the SBC register
///         uint8 ucData                : data to be written in the SBC register
///         uint8 ucCommand             : write or read the register
///         pfReadClBck ClbckFunction   : callback function
///
/// \return boolean        : insertion was successful
//
//-----------------------------------------------------------------------------
boolean CddSbc_InsertNewSchedEntry(uint8 ucAddress, uint8 ucData, uint8 ucCommand, pfReadClBck ClbckFunction)
{
  uint16 unData = ucData;
  boolean boRetVal = FALSE;
  STATIC_UT(boolean, boInsertStatus, FALSE);

#ifndef UNIT_TEST
  DISABLE_INTERRUPTS();
#endif

  /*if (CddSbc_ucQueueWriteIndex == CddSbc_ucQueueReadIndex)
  {
    // increment the write index circularly
    CddSbc_ucQueueWriteIndex = (CddSbc_ucQueueWriteIndex + 1u) % CDDSBC_CFG_MAX_SPI_SCHED_QUEUE;
  }*/

  // be careful not to overwrite unprocessed entries
  if (FALSE == CddSbc_asSpiScheduleQueue[CddSbc_ucQueueWriteIndex].CddSbc_boProcessEntry)
  {

    // mark the entry as unprocessed
    CddSbc_asSpiScheduleQueue[CddSbc_ucQueueWriteIndex].CddSbc_boProcessEntry = TRUE;

    // Shift the data in the right position
    unData = unData << 8u;

    // Concatenate the Address + the Command + the Data
    unData = unData | ucAddress | ucCommand;

    // add the data to be sent to the SBC
    CddSbc_asSpiScheduleQueue[CddSbc_ucQueueWriteIndex].CddSbc_unTxData = unData;

    // set up a callback to retrieve SBC register content
    CddSbc_asSpiScheduleQueue[CddSbc_ucQueueWriteIndex].CddSbc_ReadClbckFunc = ClbckFunction;

    // insertion was successful
    boRetVal = TRUE;

    // increment the write index circularly
    CddSbc_ucQueueWriteIndex = (CddSbc_ucQueueWriteIndex + 1u) % CDDSBC_CFG_MAX_SPI_SCHED_QUEUE;

    // First successful insertion after error/init.
    if (boInsertStatus == FALSE)
    {
      // Set the flag in order to have this part executed only once
      boInsertStatus = TRUE;

      // Report no error. Only once after init/error occurence
      CddSbc_ScheduleTableFull(NO_ERROR);
    }
  }
  else
  {
    // Reset successful insertion flag
    boInsertStatus = FALSE;

    // Schedule table full, unsuccessful insertion!
    CddSbc_ScheduleTableFull(ERROR_ON);
  }

#ifndef UNIT_TEST
  ENABLE_INTERRUPTS();
#endif
  return boRetVal;
}

// EOF

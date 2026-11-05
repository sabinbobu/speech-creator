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
/// \file  CddSbc.c
///
/// \brief  SBC complex device driver
///
/// \descr  System Basic Chip
///
///         Additional information can be found in the design description (Link:
///         doors://ITTOR47DOORSAL.mmemea.marelliad.net:36693/?version=2&prodID=0&urn=urn:telelogic::1-43eb3f040fd3425e-M-00045927)
///
/// \author Kai Zhao  ALDE-RT (zhk2rt)
///         mailTo: Kai.Zhao[at]marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// Standard / system header file includes
//=============================================================================

//=============================================================================
//  Project-specific header file includes
//=============================================================================
#include <CddSpi.h>


#define  SBC9471_WD_CTRL_ADR                  0x03U // Watchdog Control
#define  CDD_SBC9471_WRITE_CMD                0x80u
//CHECKSUM
#define CDD_SBC9471_WD_Checksum_0             0u    // Counts as 0 for checksum calculation
#define CDD_SBC9471_WD_Checksum_1             1u    // Counts as 1 for checksum calculation

//WD_WIN
#define CDD_SBC9471_WD_TimeOut                0u    // Watchdog works as a Time-Out watchdog
#define CDD_SBC9471_WD_Window                 1u    // Watchdog works as a Window watchdog

//WD_TIMER
#define CDD_SBC9471_WD_TIMER_10ms             0u    // 10ms
#define CDD_SBC9471_WD_TIMER_20ms             1u    // 20ms
#define CDD_SBC9471_WD_TIMER_50ms             2u    // 50ms
#define CDD_SBC9471_WD_TIMER_100ms            3u    // 100ms
#define CDD_SBC9471_WD_TIMER_200ms            4u    // 200ms
#define CDD_SBC9471_WD_TIMER_500ms            5u    // 500ms
#define CDD_SBC9471_WD_TIMER_1000ms           6u    // 1000ms
#define CDD_SBC9471_WD_TIMER_10000ms          7u    // 10000ms

#define CDDSBC_CFG_MAX_WRITE_ATTEMPTS        10u

typedef struct // PRQA S 0635 // The bit field were declared with uint8 - which is Unsigned integer
{
  uint8 WD_TIMER     : 3;             // Watchdog Timer Period
  uint8              : 1;             // Reserved, always reads as 0
  uint8 WD_EN_WK_BUS : 1;             // Watchdog Enable after Bus (CAN) Wake-up in SBC Stop Mode
  uint8 WD_WIN       : 1;             // Watchdog Type Selection
  uint8 WD_STM_EN_0  : 1;             // Watchdog Deactivation during Stop Mode, bit 0
  uint8 CHECKSUM     : 1;             // Watchdog Setting Check Sum Bit
} tSbc9471_WD_CTRL_Bit;

typedef struct
{
  uint8 Address;
  union
  {                                                                                                         // PRQA S 0750 // Union has to be used in order to save memory. The data has to be accessed by Word or by Bits but not both at the same time.
    tSbc9471_WD_CTRL_Bit         Bit;        // bit access to the register data
    uint8                       Word;        // word access to the register data
  } Data;
} tSbc9471_Access_WD_CTRL_Register;

 tSbc9471_Access_WD_CTRL_Register    WD_CTRL_Register;

static boolean CddSbc9471_WriteClearReg(uint8 ucAddress, uint16 unDataField)
{
  uint8 ucAddressField, ucIterationIndex = 0u;
  uint16 unTxData, unRxData;
  boolean boReturn = TRUE;

  // Concatenate the address field of the message
  ucAddressField = ucAddress | CDD_SBC9471_WRITE_CMD;

  // Concatenate the address field of the message with the data field and store the obtained message in the buffer
  unTxData = unDataField;
  unTxData = unTxData << 8u;
  unTxData = unTxData | ucAddressField;

  // Try to send the data to the register for a maximum of 10 times
  while ((CddSpi_TransferMsg((uint8)CDDSPI_DEVICE(SBC), &unTxData) != TRUE) && (ucIterationIndex < CDDSBC_CFG_MAX_WRITE_ATTEMPTS))
  {
    // Increment the error counter
    ucIterationIndex++;
  }

  return boReturn;
}

//-----------------------------------------------------------------------------
/// \brief  CddSbc_SetWdgTimeoutModeAnd200ms
///
/// \descr  API function to set the watchdog with timeout mode and 200ms
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddSbc_SetWdgTimeoutModeAnd200ms(void)
{
  tSbc9471_Access_WD_CTRL_Register    WD_CTRL_Register;

  // Set Watchdog Timer Periode in the WD_CTRL register.WD_TIMER
  WD_CTRL_Register.Data.Bit.WD_TIMER = CDD_SBC9471_WD_TIMER_1000ms;

  // Set Watchdog with Timeout watchdog in the WD_CTRL register.WD_WIN
  WD_CTRL_Register.Data.Bit.WD_WIN = CDD_SBC9471_WD_TimeOut;

  // Set Watchdog Checksum in the WD_CTRL register.CHECKSUM
  WD_CTRL_Register.Data.Bit.CHECKSUM = CDD_SBC9471_WD_Checksum_0;


  (void)CddSbc9471_WriteClearReg(SBC9471_WD_CTRL_ADR, WD_CTRL_Register.Data.Word);
}


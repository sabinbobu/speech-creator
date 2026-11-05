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
/// \file  CddTle94x1_Com.h
///
/// \brief  SBC complex device driver
///
/// \descr  System Basic Chip
///
/// \author ZHAO, Kai ALDE-RT/EES6
///
//-----------------------------------------------------------------------------
#ifndef CDD_TLE94X1_COM_2021_03_08_H_
#define CDD_TLE94X1_COM_2021_03_08_H_

//=============================================================================
//  preprocessor definitions
//=============================================================================

//=============================================================================
//  includes
//=============================================================================

//=============================================================================
//  definitions
//=============================================================================
//#if (CDDSBC_CFG_CYCLIC_OPERATION == STD_ON)
typedef void(*pfReadClBck) (uint32 ReadVal, uint16 SentVal); // pointer to the callback function which returns the values read from the SBC registers

// SPI schedule queue entry
typedef struct
{
  boolean      CddSbc_boProcessEntry;
  uint16       CddSbc_unTxData;
  uint16       CddSbc_unRxData;
  pfReadClBck  CddSbc_ReadClbckFunc;
} tsCddSbc_SpiScheduleQueue;

//=============================================================================
//  prototypes
//=============================================================================

boolean CddSbc_InsertNewSchedEntry(uint8 ucAddress, uint8 ucData, uint8 ucCommand, pfReadClBck ClbckFunction);
//#endif

#endif // CDD_TLE94X1_COM_2021_03_08_H_
// EOF

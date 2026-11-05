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
/// \file   Fee.c
///
/// \brief  Implementation of the Fee mechanism 
///
/// \descr  Implementation of the logical  Fee operation.
///         Calculates the address and offset of the memory block.
///         Compute the index of the requested memory block
///
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
//-----------------------------------------------------------------------------
#include "Fee.h"
#include "Fee_InternalFct.h"

//=============================================================================
// preprocessor definitions
//=============================================================================

//=============================================================================
// variables
//=============================================================================

tieFeeState Fee_State             = FEE_STATE_NOT_INIT;
MemIf_StatusType Fee_t_Status     = MEMIF_UNINIT;        // status of FLASH EEPROM Emulation
MemIf_JobResultType Fee_JobResult = MEMIF_JOB_OK;  // result of last job



//=============================================================================
// functions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  FeeStateMachine
///
/// \descr  State Flow of the Fee mechanism
///
/// \param  eFee_State
///
/// \return void
//-----------------------------------------------------------------------------
void FeeStateMachine(tieFeeState eFee_State)
{
  return;
}

//-----------------------------------------------------------------------------
/// \brief  Fee_LookUpIndex
///
/// \descr  Get the index of the block id from FeeBlockTable array
///
/// \param  unBlockNumber   : number of logical block
///
/// \return uint16 : ID number of the block
//-----------------------------------------------------------------------------
uint16 Fee_LookUpIndex(uint16 unBlockNumber)
{
  (uint16)unBlockNumber;
  return 0U;
}

volatile  uint16 unAddressOffset = 0x00;          //PRQA S 3408
//-----------------------------------------------------------------------------
/// \brief  Fee_GetAddressOffset
///
/// \descr  This function calculates the address offset for 32 bit aligned memory-space
///
/// \param  unBlockNumber : number of logical block
///
/// \return uint16 :  address offset of the block
//-----------------------------------------------------------------------------
uint16 Fee_GetAddressOffset(uint16 unBlockNumber)
{
  (uint16)unBlockNumber;
  return 0U;

}

//EOF


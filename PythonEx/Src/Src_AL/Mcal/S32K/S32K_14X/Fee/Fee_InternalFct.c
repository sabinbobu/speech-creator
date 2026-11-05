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


#include <Fee.h>
#include <Fee_InternalFct.h>


//=============================================================================
// preprocessor definitions
//=============================================================================

//=============================================================================
// variables
//=============================================================================


tieFeeState Fee_State = FEE_STATE_NOT_INIT;
MemIf_StatusType Fee_t_Status = MEMIF_UNINIT;        // status of FLASH EEPROM Emulation
MemIf_JobResultType Fee_JobResult = MEMIF_JOB_OK;  // result of last job



//=============================================================================
// prototypes
//=============================================================================

void FeeStateMachine(tieFeeState eFee_State)
{
  Std_ReturnType boStatus;
  switch (eFee_State)
  {
  case FEE_STATE_NOT_INIT:
    // Nothing to do here
    break;

  case FEE_STATE_IDLE:
    // Nothing to do here
    break;

  case FEE_STATE_WRITE:

    boStatus = Fee_GetOpStatus();
    if (boStatus != E_OK)
    {
      Fee_JobResult = MEMIF_BLOCK_INVALID;
    }
    else
    {
      Fee_JobResult = MEMIF_JOB_OK;
      Fee_State = FEE_STATE_IDLE; 
    }
    break;

  case FEE_STATE_READ:

    boStatus = Fee_GetOpStatus();
    if (boStatus != E_OK)
    {
      Fee_JobResult = MEMIF_BLOCK_INVALID;  // or MEMIF_JOB_FAILED
    }
    else
    {
      Fee_JobResult = MEMIF_JOB_OK;
      Fee_State = FEE_STATE_IDLE;
    }
    break;

  case FEE_STATE_READ_ALL:
    break;
  case FEE_STATE_ERROR:
    break;
  default:
    break;
  }

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
  uint16 unIdx;
  uint16 unResult = 0xFFFFu;
  for (unIdx = 0; unIdx < (uint16)FeeBlockCount; unIdx++)
  {
    if (FeeBlockTable[unIdx].unBlockId == unBlockNumber)
    {
      unResult = unIdx;
      break;
    }
  }
  return unResult;
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
  uint16 unIdx;
  
  
  unAddressOffset = 0x00;

  for (unIdx = 0; unIdx < (uint16)FeeBlockCount; unIdx++)
  {
    if (FeeBlockTable[unIdx].unBlockId == unBlockNumber)
    {
      break;
    }
    else
    {
      unAddressOffset = unAddressOffset + FeeBlockTable[unIdx].unBlockSize + (((FeeBlockTable[unIdx].unBlockSize & 0x03U) == 0x00U) ? 0x00U : (4U - FeeBlockTable[unIdx].unBlockSize % 4U));      //PRQA S 400  //no side effect
    }
  }
  return unAddressOffset;
}

//EOF


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
/// \file   Nvm.c
///
/// \brief  Nvm mechanism implementation source code
///
/// \descr  Functions for NVRAM manager mechanism that are responsible for:
///         Initialization of the RAM data blocks  (NvM_ReadAll)
///         Write the content of a RAM block to its corresponding NV block (NvM_WriteAll) 
///         Copy the data of the NV block to its corresponding RAM block (NvM_ReadBlock)
///         Fill a RAM block with NVRAM data (NvM_WriteBlock)
///
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
//-----------------------------------------------------------------------------


//=============================================================================
// includes
//=============================================================================


#include <Std_Types.h>
#include <Nvm.h>
#include <Nvm_Internal.h>
#include <Crc.h>
//lint -e451 Header file repeatedly included but does not have a standard include guard
#include "string.h"
//lint +e451 Header file repeatedly included but does not have a standard include guard
//#include <Util/UtilBase.h>

#ifndef UNIT_TEST
#include <Rte.h>
#else
#include <RteCommonTypes.h>
#endif

//=============================================================================
// preprocessor definitions
//=============================================================================

//=============================================================================
// variables
//=============================================================================



//tNvmBlockdescriptor NvMBlockTable[NvMBlockCount] = 

//=============================================================================
// prototypes
//=============================================================================




//-----------------------------------------------------------------------------
/// \brief    NvM_Init
///
/// \descr    Initialization of the NvM state
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void NvM_Init(void)
{
  NvM_eState = NVM_STATE_IDLE;
}



//-----------------------------------------------------------------------------
/// \brief  NvM_MainFunction 
///
/// \descr  This function will be called cyclic
///
/// \param  - 
///
/// \return - void
//-----------------------------------------------------------------------------

void NvM_MainFunction(void)
{
  NvMStateMachine();
}

//-----------------------------------------------------------------------------
/// \brief  NvM_GetState 
///
/// \descr  Get the state of the Nvm module
///
/// \param  - 
///
/// \return internal Nvm State
//-----------------------------------------------------------------------------

  tieNvMState NvM_GetState(void)
{
  return (NvM_eState);
}


//-----------------------------------------------------------------------------
/// \brief  NvM_ReadBlock 
///
/// \descr  Service to copy the data of the NV block to its corresponding RAM block.
///
/// \param  BlockId : The block identifier uniquely identifies one NVRAM block descriptor.
///                   A NVRAM block descriptor contains all needed information about a single NVRAM block.
///
/// \param  NvM_DstPtr   Pointer to the RAM data block.
///
/// \return   E_OK: request has been accepted 
///           E_NOT_OK: request has not been accepted
//-----------------------------------------------------------------------------
//PRQA S 1505  1 // library function
Std_ReturnType NvM_ReadBlock( NvM_BlockIdType BlockId, void* NvM_DstPtr )  

{
  NvM_AdminBlockType* pAdminBlock;
  NvM_QueueType NvmJob;
  Std_ReturnType retValue;
  if (BlockId < (uint16)NvMBlockCount)
  {
    pAdminBlock = &NvM_aAdminTable[BlockId];
    pAdminBlock->BlockState = NVM_STATE_READ_BLOCK;
    pAdminBlock->BlockSubState = NVM_SUB_STATE_MEM_IF_REQ;
    NvmJob.job = NVM_STATE_READ_BLOCK;
    NvmJob.blockId = BlockId;
    NvmJob.pucData = NvM_DstPtr;          //PRQA S 317   //correct assignment
    retValue = NvM_QueueBlock(&NvmJob);
    if (E_OK == retValue)
    {
      pAdminBlock->ErrorStatus = NVM_REQ_PENDING;
    }
    else
    {
      pAdminBlock->ErrorStatus = NVM_REQ_OK;
    }
  }
  else
  {
    // Report Error
    retValue = E_NOT_OK;
  }
  return retValue;

#if 0  
  tieNvMError retValue = NVM_OK;
  if (NvM_eState == Nvm_eState_IDLE)
  {
    NvM_CurrentId = Id;
    myReq.command_enu = R_EEL_CMD_READ;
    myReq.identifier_u16 = sampleApp_eelConfig_enu.IDLTab_pstr[Id].ID_u16;
    myReq.length_u16 = sampleApp_eelConfig_enu.IDLTab_pstr[Id].len_u16;
    myReq.address_pu08 = MemIfBlockTable[Id];
    R_EEL_Execute( &myReq );
    if  ( R_EEL_BUSY != myReq.status_enu )
    {
      Nvm_LastError = myReq.status_enu ;
      NvM_eState = Nvm_eState_IDLE;
      retValue = NVM_READ_ERROR;
    }
    else
    {
      NvM_eState = Nvm_eState_READ;
    }
  }
  else
  {
    retValue = NVM_BUSY;  
  }
  return retValue;
#endif
}

	//const NvM_BlockDescriptorType *	bPtr;
	//AdministrativeBlockType * 		admPtr;
	//NvM_QueueType qEntry;
	//int rv;


  //BlockStateType          BlockState;
  //BlockSubStateType       BlockSubState;
  //uint8                   DataIndex;        // Selected data index if "Data Set" type
  //boolean                 BlockWriteProtected;  // Block write protected?
  //NvM_RequestResultType   ErrorStatus;      // Status of block
  //boolean                 BlockChanged;      // Block changed?
  //boolean                 BlockValid;        // Block valid? (RAM block only?)
  //uint8                   NumberOfWriteFailed;  // Current write retry cycle
  //Nvm_CrcType             RamCrc;
  //Nvm_CrcType             NvCrc;          // The CRC of this block, read from NV
  //void *          savedpucData;      //



//-----------------------------------------------------------------------------
///\brief  NvM_WriteBlock
///
/// \descr  Service to copy the data of the RAM block to its corresponding NV block.
///
/// \param  BlockId  The block identifier uniquely identifies one NVRAM block descriptor.
///                 A NVRAM block descriptor contains all needed information about a single NVRAM block.
///
/// \param  NvM_SrcPtr  Pointer to the RAM data block.
///
/// \return   E_OK: request has been accepted
///           E_NOT_OK: request has not been accepted
//-----------------------------------------------------------------------------
Std_ReturnType NvM_WriteBlock(NvM_BlockIdType BlockId, void* NvM_SrcPtr )
{
  NvM_AdminBlockType * pAdminBlock;
  NvM_QueueType NvmJob;
  Std_ReturnType retValue;
  if (BlockId < (uint16)NvMBlockCount)
  {
    pAdminBlock = &NvM_aAdminTable[BlockId];
    pAdminBlock->BlockState = NVM_STATE_WRITE_BLOCK;
    pAdminBlock->BlockSubState = NVM_SUB_STATE_DO_CRC;
    pAdminBlock->RamCrc = 0;
    NvmJob.job = NVM_STATE_WRITE_BLOCK;
    NvmJob.blockId = BlockId;
    NvmJob.pucData = NvM_SrcPtr;              //PRQA S 317   //correct assignment
    retValue = NvM_QueueBlock(&NvmJob);
    if (E_OK == retValue)
    {
      pAdminBlock->ErrorStatus = NVM_REQ_PENDING;
    }
    else
    {
      pAdminBlock->ErrorStatus = NVM_REQ_NOT_OK;
    }

  }
  else
  {
    // Report Error
    retValue = E_NOT_OK;
  }
  return retValue;
}

#if (NVM_API_CONFIG_USE_PRIO_QUEUE == STD_ON)
//-----------------------------------------------------------------------------
/// \brief  NvM_WriteBlockPrio
///
/// \descr  
///
/// \param  BlockId 
/// \param  NvM_SrcPtr 
///
/// \return Std_ReturnType 
//-----------------------------------------------------------------------------
Std_ReturnType NvM_WriteBlockPrio(NvM_BlockIdType BlockId, void* NvM_SrcPtr )
{
  NvM_AdminBlockType * pAdminBlock;
  NvM_QueueType NvmJob;
  Std_ReturnType retValue;

  if (BlockId < NvMBlockCount)
  {
    pAdminBlock = &NvM_aAdminTable[BlockId];
    pAdminBlock->BlockState = NVM_STATE_WRITE_BLOCK;
    pAdminBlock->BlockSubState = NVM_SUB_STATE_DO_CRC;
    pAdminBlock->RamCrc = 0;
    NvmJob.job = NVM_STATE_WRITE_BLOCK;
    NvmJob.blockId = BlockId;
    NvmJob.pucData = NvM_SrcPtr;
    retValue = NvM_QueueBlockPrio(&NvmJob);
    if (E_OK == retValue)
    {
      pAdminBlock->ErrorStatus = NVM_REQ_PENDING;
    }
    else
    {
      pAdminBlock->ErrorStatus = NVM_REQ_NOT_OK;
    }
  }
  else
  {
    // Report Error
    retValue = E_NOT_OK;
  }
  return retValue;
}
#endif

//-----------------------------------------------------------------------------
/// \brief  NvM_WriteAll 
///
/// \descr  Write all permanent blocks to NvM - initiates a multi block write request.
///
/// \param  - 
///
/// \return -
//-----------------------------------------------------------------------------

void NvM_WriteAll(void)
{
  NvM_AdminMultiBlock.MultiBlockState = NVM_STATE_WRITE_ALL;
  NvM_AdminMultiBlock.MultiBlockSubState = NVM_MB_SUB_STATE_INIT;
  NvM_AdminMultiBlock.ErrorStatus = NVM_REQ_PENDING;
  NvM_AdminMultiBlock.SingleBlockErrorStatus = NVM_REQ_OK;

}

//-----------------------------------------------------------------------------
/// \brief  NvM_CancelWriteAll
///
/// \descr  Cancels a previously started WriteAll request
///
/// \param  - 
///
/// \return -
//-----------------------------------------------------------------------------
void NvM_CancelWriteAll(void)
{
  NvM_ClearQueue();
#if (NVM_API_CONFIG_USE_PRIO_QUEUE == STD_ON)
  NvM_ClearQueuePrio();
#endif
}


//-----------------------------------------------------------------------------
/// \brief  NvM_ReadAll 
///
/// \descr  reads all permanent blocks from NvM - Initiates a multi block read request.
///
/// \param  - 
///
/// \return -
//-----------------------------------------------------------------------------
void NvM_ReadAll(void)
{
  NvM_AdminMultiBlock.MultiBlockState = NVM_STATE_READ_ALL;
  NvM_AdminMultiBlock.MultiBlockSubState = NVM_MB_SUB_STATE_INIT;
  NvM_AdminMultiBlock.ErrorStatus = NVM_REQ_PENDING;
  NvM_AdminMultiBlock.SingleBlockErrorStatus = NVM_REQ_OK;
}


//-----------------------------------------------------------------------------
/// \brief  NvM_GetErrorStatus
///
/// \descr  Service to read the block dependent error/status information.
///
/// \param[in]  BlockId  The block identifier uniquely identifies one NVRAM block descriptor.
///                 A NVRAM block descriptor contains all needed information about a single NVRAM block.
///
/// \param[out] RequestResultPtr: Pointer to where to store the request result.See NvM_RequestResultType .
///
///
/// \return   E_OK: The block dependent error/status information was read successfully. 
///           E_NOT_OK: An error occured. 
///
//-----------------------------------------------------------------------------


Std_ReturnType NvM_GetErrorStatus(NvM_BlockIdType BlockId, NvM_RequestResultType *RequestResultPtr)
{
#ifdef NVM_API_V2
  if ((uint16)NvmBlockMultiBlockRequestId == BlockId)
#else
  if (MultiBlockRequest == BlockId)
#endif
  {
    /* get the ErrorStatus */
    *RequestResultPtr = NvM_AdminMultiBlock.ErrorStatus;
  }
  else
  {
    /* get the ErrorStatus */
    *RequestResultPtr = NvM_aAdminTable[BlockId].ErrorStatus;
  }
  return E_OK;
}


#if defined (CFG_VARIANT_FULL) ||defined(UNIT_TEST) // Applicable only for FULL version
//-----------------------------------------------------------------------------
/// \brief  reNvm_WritePxlData
///
/// \descr  Event runnable called by CtrlPxl to copy eeprom data to the 
///         dedicated matrix Nvm block
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void reNvm_WritePxlData(void)
{
  tsRte_NvMBlock NvmSourceData;

  //read data from RTE which will be written in Nvm Block
  (void)Rte_Read_CtrlPxl_Nvm_WriteData(&NvmSourceData);

  //copy data from RTE port to the Pixel NVM Block
  UtilMemCopy(&NvmBlockMatrixEEPromContent.Data[0], NvmSourceData.pucData, NvmSourceData.unSize);

  //send request to write the dedicated Nvm Block
  (void)NvM_WriteBlock((NvM_BlockIdType)NvmBlockMatrixEEPromContentId, &NvmBlockMatrixEEPromContent.Data[0]);

}
#endif


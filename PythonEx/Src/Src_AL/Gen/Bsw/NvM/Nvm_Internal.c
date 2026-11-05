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
/// \file   Nvm_Internal.c
///
/// \brief  Handler for Nvm requests
///
/// \descr  Functions for NVRAM manager mechanism that are responsible for:
///         Read, Compute and retrieve Crc for each memory block
///         Handle queue operations for multiple concurent single block requests
///         Behaviour of the NvM (State machine)
///         Handle Nvm requests for single block operations
///         
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
//-----------------------------------------------------------------------------


//=============================================================================
// includes
//=============================================================================


#include <AL_Helper.h>
#include <Nvm.h>
#include <NvM_Internal.h>
#include <Crc.h>

#include <MemIf_Types.h>
//lint -e451 Header file repeatedly included but does not have a standard include guard
#include <string.h>
//lint +e451 Header file repeatedly included but does not have a standard include guard


//=============================================================================
// preprocessor definitions
//=============================================================================
#define NMV_CRC_SIZE 4U
#ifndef  NvM_QUEUE_SIZE
  #define  NvM_QUEUE_SIZE 10   //#Rma era 10
#endif
#define Nvm_EmptyMarker -1

#define NVM_CRC_START_VALUE 0x0U
//=============================================================================
// variables
//=============================================================================

// tbd declare as static

NvM_AdminBlockType NvM_aAdminTable[NvMBlockCount];
NvM_AdminMultiBlockType NvM_AdminMultiBlock;

STATIC_AL uint8  NvM_aucMemIf_Buffer[sizeof(memif_io_buffer_t)];

// PRQA S 1504 1 // maybe errornous QAC message
tieNvMState NvM_eState = NVM_STATE_NOT_INIT;
//tNvMBlockDescriptor NvMBlockTable[NvMBlockCount] = 
#ifdef UNIT_TEST
const tieNvMState NvM_Test = NVM_STATE_RESTORE_BLOCK_DEFAULTS;
#endif

STATIC_AL NvM_QueueType NvmQueue[NvM_QUEUE_SIZE];
STATIC_AL sint16 NvM_ucQueueFront = Nvm_EmptyMarker;
STATIC_AL sint16 NvM_ucQueueRear = Nvm_EmptyMarker;

#if (NVM_API_CONFIG_USE_PRIO_QUEUE == STD_ON)
  STATIC_AL NvM_QueueType NvmQueuePrio[NvM_QUEUE_SIZE];
  STATIC_AL sint16 NvM_ucQueuePrioFront = Nvm_EmptyMarker;
  STATIC_AL sint16 NvM_ucQueuePrioRear = Nvm_EmptyMarker;
#endif

STATIC_AL boolean NvM_boNeedsRewrite = FALSE;


//=============================================================================
// prototypes
//=============================================================================
STATIC_AL uint32 MemIfReadCrc(uint8 * pucSrc);
STATIC_AL void MemIfWriteCrc(uint8 * pucDest, uint32 ulCrc);
STATIC_AL void Nvm_ReadAllMainFunction(void);
STATIC_AL void Nvm_WriteAllMainFunction(void);
STATIC_AL boolean NvM_ReadAllInit(void);
STATIC_AL boolean NvM_WriteAllInit(void);
#ifdef NVM_API_V2
STATIC_AL boolean NvM_RestoreBlocksAfterSwChange(void);
#endif
STATIC_AL void HandleBlockWrite(tNvMBlockDescriptor* pBlock, NvM_AdminBlockType* pAdminBlock, void* pData, boolean boMulti);
STATIC_AL void HandleBlockRead(tNvMBlockDescriptor* pBlock, NvM_AdminBlockType* pAdminBlock, void* pData, boolean bMulti);

//=============================================================================
// helper functions
//=============================================================================



STATIC_AL uint32 MemIfReadCrc(uint8* pucSrc)
{
  uint32 ulCRC = 0U;
  UtilMemCopy((uint8*) &ulCRC, pucSrc, sizeof(ulCRC));         // PRQA S 310   // correct cast - working with actual address
  return ulCRC;
}

STATIC_AL void MemIfWriteCrc(uint8* pucDest, uint32 ulCrc)
{
  uint8* pulCRC = pucDest;
  *pulCRC = (uint8) ulCrc;
  pulCRC++;
  ulCrc = ulCrc >> 8U;
  *pulCRC = (uint8) ulCrc;
  pulCRC++;
  ulCrc = ulCrc >> 8U;
  *pulCRC = (uint8) ulCrc;
  pulCRC++;
  ulCrc = ulCrc >> 8U;
  *pulCRC = (uint8) ulCrc;
}


STATIC_AL boolean NwM_IsQueueFull(void)
{
  boolean boResult;
  if ((NvM_ucQueueRear + 1) % NvM_QUEUE_SIZE == NvM_ucQueueFront)
  {
    boResult = TRUE;  
  }
  else
  {
    boResult = FALSE;  
  }
  return boResult;
}

STATIC_AL boolean NwM_IsQueueEmpty(void)
{
  boolean boResult;
  if ((NvM_ucQueueRear == Nvm_EmptyMarker) && (NvM_ucQueueFront == Nvm_EmptyMarker))
  {
    boResult = TRUE;  
  }
  else
  {
    boResult = FALSE;  
  }
  return boResult;
}



Std_ReturnType NvM_QueueBlock(NvM_QueueType* pJob)
{
  Std_ReturnType result = E_NOT_OK;

  /* #Rma Check if the job is already present in the queue */

   if (!NwM_IsQueueFull() )       //PRQA S 4558   //intentionally no modification of existing code
   {
     if (NwM_IsQueueEmpty() != 0U)
     {
       NvM_ucQueueRear = 0;
       NvM_ucQueueFront = 0;
     }
     else
     {
       NvM_ucQueueRear = (NvM_ucQueueRear + 1) % NvM_QUEUE_SIZE;
     }
     (void)memcpy(&NvmQueue[NvM_ucQueueRear], pJob, sizeof(NvM_QueueType));
     result = E_OK;
   }
  
  return result;
}

STATIC_AL Std_ReturnType NvM_GetQueuedBlock(NvM_QueueType* pJob)
{
  Std_ReturnType result = E_NOT_OK;
  if (!NwM_IsQueueEmpty())        //PRQA S 4558   //intentionally no modification of existing code
  {
    (void)memcpy(pJob, &NvmQueue[NvM_ucQueueFront], sizeof(NvM_QueueType));
    if (NvM_ucQueueFront == NvM_ucQueueRear)
    {
      NvM_ucQueueRear = Nvm_EmptyMarker;
      NvM_ucQueueFront = Nvm_EmptyMarker;
    }
    else
    {
      NvM_ucQueueFront = (NvM_ucQueueFront + 1) % NvM_QUEUE_SIZE;
    }
    result = E_OK;
  }
  return result;
}

void NvM_ClearQueue(void)
{
  UtilMemClr((uint8*)NvmQueue, sizeof(NvM_QueueType)*NvM_QUEUE_SIZE); // PRQA S 310   //PRQA S 1840  
  NvM_ucQueueRear = Nvm_EmptyMarker;
  NvM_ucQueueFront = Nvm_EmptyMarker;
}

#if (NVM_API_CONFIG_USE_PRIO_QUEUE == STD_ON)
STATIC_AL boolean NwM_IsQueuePrioFull()
{
  boolean boResult;
  if ((NvM_ucQueuePrioRear + 1) % NvM_QUEUE_SIZE == NvM_ucQueuePrioFront)
  {
    boResult = TRUE;  
  }
  else
  {
    boResult = FALSE;  
  }
  return boResult;
}

STATIC_AL boolean NwM_IsQueuePrioEmpty()
{
  boolean boResult;
  if ((NvM_ucQueuePrioRear == Nvm_EmptyMarker) && (NvM_ucQueuePrioFront == Nvm_EmptyMarker))
  {
    boResult = TRUE;  
  }
  else
  {
    boResult = FALSE;  
  }
  return boResult;
}


Std_ReturnType NvM_QueueBlockPrio(NvM_QueueType* pJob)
{
  Std_ReturnType result = E_NOT_OK;
  if (!NwM_IsQueuePrioFull() )
  {
    if (NwM_IsQueuePrioEmpty())
    {
      NvM_ucQueuePrioRear = 0;
      NvM_ucQueuePrioFront = 0;
    }
    else
    {
      NvM_ucQueuePrioRear = (NvM_ucQueuePrioRear + 1) % NvM_QUEUE_SIZE;
    }
    memcpy(&NvmQueuePrio[NvM_ucQueuePrioRear], pJob, sizeof(NvM_QueueType));
    result = E_OK;
  }
  return result;
}

STATIC_AL Std_ReturnType NvM_GetQueuedPrioBlock(NvM_QueueType* pJob)
{
  Std_ReturnType result = E_NOT_OK;
  if (!NwM_IsQueuePrioEmpty())
  {
    memcpy(pJob, &NvmQueuePrio[NvM_ucQueuePrioFront], sizeof(NvM_QueueType));
    if (NvM_ucQueuePrioFront == NvM_ucQueuePrioRear)
    {
      NvM_ucQueuePrioRear = Nvm_EmptyMarker;
      NvM_ucQueuePrioFront = Nvm_EmptyMarker;
    }
    else
    {
      NvM_ucQueuePrioFront = (NvM_ucQueuePrioFront + 1) % NvM_QUEUE_SIZE;
    }
    result = E_OK;
  }
  return result;
}

void NvM_ClearQueuePrio(void)
{
  UtilMemClr((uint8*)NvmQueuePrio, sizeof(NvM_QueueType)*NvM_QUEUE_SIZE); // PRQA S 310
  NvM_ucQueuePrioRear = Nvm_EmptyMarker;
  NvM_ucQueuePrioFront = Nvm_EmptyMarker;
}
#endif


STATIC_AL void HandleBlockWrite(tNvMBlockDescriptor* pBlock, NvM_AdminBlockType* pAdminBlock, void* pData, boolean boMulti)
{
  MemIf_JobResultType eMemIf_result;
  (void) boMulti;  // make QAC happy
  (void) pData;    // make QAC happy

  switch (pAdminBlock->BlockSubState) 
  {
    case NVM_SUB_STATE_DO_CRC :
      // todo split in smaller pieces
      pAdminBlock->BlockSubState = NVM_SUB_STATE_MEM_IF_REQ;
      
      UtilMemCopy((uint8*) NvM_aucMemIf_Buffer,pBlock->RamMirror,pBlock->BlockSize_u16);

      pAdminBlock->RamCrc = Crc_CalculateCRC32(NvM_aucMemIf_Buffer,(uint32) pBlock->BlockSize_u16, pAdminBlock->RamCrc);

      MemIfWriteCrc(&NvM_aucMemIf_Buffer[pBlock->BlockSize_u16] ,pAdminBlock->RamCrc);
      if (E_OK == MemIf_Write(pBlock->MemIfDevice_u8,pBlock->MemIfBlockId_u16, NvM_aucMemIf_Buffer))
      {
        pAdminBlock->ErrorStatus = NVM_REQ_PENDING;
      }
      else
      {
        pAdminBlock->ErrorStatus = NVM_REQ_NOT_OK;
      }
    break;
    case NVM_SUB_STATE_MEM_IF_REQ:
      eMemIf_result = MemIf_GetJobResult(pBlock->MemIfDevice_u8);
      switch(eMemIf_result)
      {
        case MEMIF_JOB_OK :
          pAdminBlock->ErrorStatus = NVM_REQ_OK;
          pAdminBlock->NvCrc = pAdminBlock->RamCrc;
          pAdminBlock->BlockChanged = FALSE;
          pAdminBlock->BlockValid = TRUE;
          pAdminBlock->BlockState = NVM_STATE_IDLE;
          // if 
          break;                      
        case MEMIF_JOB_FAILED :
          // report NvM_E_Hardware to DEM
          pAdminBlock->ErrorStatus = NVM_REQ_NOT_OK;
          // Tbd implement Error recovery
          // first impl. : finish job
          pAdminBlock->BlockState = NVM_STATE_IDLE; 
          break;
        case MEMIF_JOB_PENDING :
          // wait until Job finished
          break;
        case MEMIF_JOB_CANCELLED :
          pAdminBlock->ErrorStatus = NVM_REQ_NOT_OK;
          pAdminBlock->BlockState = NVM_STATE_IDLE;
          break;
        case MEMIF_BLOCK_INCONSISTENT :
        case MEMIF_BLOCK_INVALID :    // tbd  Check Admin Block
          pAdminBlock->ErrorStatus = NVM_REQ_NOT_OK;
          pAdminBlock->BlockChanged = TRUE;    
          pAdminBlock->BlockValid = FALSE;
          pAdminBlock->BlockState = NVM_STATE_IDLE;
          break;
        default: 
          // this should never happen
          break;
      }
    break;
    default :
    break;
  }
  // PRQA S 5342 1 // program architecture and readability
}


STATIC_AL void HandleBlockRead(tNvMBlockDescriptor* pBlock, NvM_AdminBlockType* pAdminBlock, void* pData, boolean bMulti)
{
  MemIf_JobResultType eMemIf_result;
  (void) bMulti;  // make QAC happy
  switch (pAdminBlock->BlockSubState) 
  {
    case NVM_SUB_STATE_DO_CRC :
      // todo split in smaller pieces
      pAdminBlock->RamCrc = Crc_CalculateCRC32(NvM_aucMemIf_Buffer, (uint32) pBlock->BlockSize_u16, pAdminBlock->RamCrc);
      pAdminBlock->NvCrc = MemIfReadCrc(&NvM_aucMemIf_Buffer[pBlock->BlockSize_u16]);

      if (pAdminBlock->RamCrc == pAdminBlock->NvCrc) 
      {
        UtilMemCopy(pData, (uint8*) NvM_aucMemIf_Buffer, pBlock->BlockSize_u16);    //PRQA S 317  //correct cast
        //UTIL_MEMCOPY(pData, (uint8*)NvM_aucMemIf_Buffer, pBlock->BlockSize_u16);
        pAdminBlock->ErrorStatus = NVM_REQ_OK;
        pAdminBlock->BlockChanged = FALSE;
        pAdminBlock->BlockValid = TRUE;
        pAdminBlock->BlockSubState = NVM_SUB_STATE_FINALIZE;
      }
      else
      {
        pAdminBlock->ErrorStatus = NVM_REQ_NOT_OK;
        pAdminBlock->BlockChanged = FALSE;
        pAdminBlock->BlockValid = TRUE;
        pAdminBlock->BlockSubState = NVM_SUB_STATE_FINALIZE;
      }
    break;
    case NVM_SUB_STATE_MEM_IF_REQ:
      //tbd Handling of Crc Size
      if (E_OK == MemIf_Read(pBlock->MemIfDevice_u8,pBlock->MemIfBlockId_u16, 0U, NvM_aucMemIf_Buffer,pBlock->BlockSize_u16+ NMV_CRC_SIZE))
      {
        pAdminBlock->ErrorStatus = NVM_REQ_PENDING;
        pAdminBlock->BlockSubState = NVM_SUB_STATE_MEM_IF_PROC;
      }
      else
      {
        pAdminBlock->ErrorStatus = NVM_REQ_NOT_OK;
        pAdminBlock->BlockSubState = NVM_SUB_STATE_FINALIZE;
      }
    break;
    case NVM_SUB_STATE_MEM_IF_PROC :
      eMemIf_result = MemIf_GetJobResult(pBlock->MemIfDevice_u8);
      switch(eMemIf_result)
      {
        case MEMIF_JOB_OK :
          pAdminBlock->RamCrc = NVM_CRC_START_VALUE;
          pAdminBlock->BlockSubState = NVM_SUB_STATE_DO_CRC;  
          //pAdminBlock->ErrorStatus = NVM_REQ_OK;
          //pAdminBlock->NvCrc = pAdminBlock->RamCrc;
          //pAdminBlock->BlockChanged = FALSE;
          //pAdminBlock->BlockValid = TRUE;
          //pAdminBlock->BlockState = NvM_eState_IDLE;
          break;                      
        case MEMIF_JOB_FAILED :
          // report NvM_E_Hardware to DEM
          pAdminBlock->ErrorStatus = NVM_REQ_NOT_OK;
          // Tbd implement Error recovery
          // first impl. : finish job
          pAdminBlock->BlockSubState = NVM_SUB_STATE_FINALIZE;
          break;
        case MEMIF_JOB_PENDING :
          // wait until Job finished
          break;
        case MEMIF_JOB_CANCELLED :
          pAdminBlock->ErrorStatus = NVM_REQ_NOT_OK;
          pAdminBlock->BlockSubState = NVM_SUB_STATE_FINALIZE;
          break;
        case MEMIF_BLOCK_INCONSISTENT :
        case MEMIF_BLOCK_INVALID :    // tbd  Check Admin Block
          pAdminBlock->ErrorStatus = NVM_REQ_NOT_OK;
          pAdminBlock->BlockChanged = TRUE;    
          pAdminBlock->BlockValid = FALSE;
          pAdminBlock->BlockSubState = NVM_SUB_STATE_FINALIZE;
          break;
        default: 
          // this should never happen
          break;
      }
      break;
    case NVM_SUB_STATE_FINALIZE:
      if (pAdminBlock->ErrorStatus != NVM_REQ_OK)
      {
        if (pBlock->InitRom != NULL_PTR)
        {
          UtilMemCopy(pBlock->RamMirror,pBlock->InitRom, pBlock->BlockSize_u16);
          //UTIL_MEMCOPY(pBlock->RamMirror, pBlock->InitRom, pBlock->BlockSize_u16);
        }
        else if (pBlock->pfnInitCallback != NULL_PTR)
        {
          pBlock->pfnInitCallback();
        }
        else
        {
          // architecture
        }
        // tbd both InitRom and InitFunc are defined, error?
      }
      pAdminBlock->BlockState = NVM_STATE_IDLE;
      break;
    default :
      break;
  }
  // PRQA S 5316, 5342 1 // program architecture and readability
}



#ifdef UNIT_TEST
boolean BlockOver = TRUE;
#endif


STATIC_AL void Nvm_ReadAllMainFunction(void)
{
  NvM_AdminBlockType* pAdminBlock;
  switch (NvM_AdminMultiBlock.MultiBlockSubState)
  {
    case NVM_MB_SUB_STATE_INIT:
      if (NvM_ReadAllInit() != 0U)
      {
#ifdef UNIT_TEST
          NvM_AdminMultiBlock.unCurrentBlock = (BlockOver != FALSE ) ? (uint16)NvMBlockCount : 0u;
#endif

        while ((NvM_AdminMultiBlock.unCurrentBlock < (uint16)NvMBlockCount))            //PRQA S 2461    //intentionally no modification of existing code
        {
          if (NvM_aAdminTable[NvM_AdminMultiBlock.unCurrentBlock].ErrorStatus != NVM_REQ_BLOCK_SKIPPED)
          {
            pAdminBlock = &NvM_aAdminTable[NvM_AdminMultiBlock.unCurrentBlock];
            pAdminBlock->BlockState = NVM_STATE_READ_BLOCK;
            pAdminBlock->BlockSubState = NVM_SUB_STATE_MEM_IF_REQ;
            pAdminBlock->ErrorStatus = NVM_REQ_PENDING;
            break;
          }
          NvM_AdminMultiBlock.unCurrentBlock++;
        }
        NvM_AdminMultiBlock.MultiBlockSubState = NVM_MB_SUB_STATE_PROCESS_BLOCKS;
      }
      else
      {
        // nothing to do
        NvM_AdminMultiBlock.MultiBlockState = NVM_STATE_IDLE;
        NvM_AdminMultiBlock.ErrorStatus = NVM_REQ_OK;
        NvM_eState = NVM_STATE_IDLE;
      }
      break;
    case NVM_MB_SUB_STATE_PROCESS_BLOCKS:
      HandleBlockRead(&NvMBlockTable[NvM_AdminMultiBlock.unCurrentBlock], 
                      &NvM_aAdminTable[NvM_AdminMultiBlock.unCurrentBlock], 
                      NvMBlockTable[NvM_AdminMultiBlock.unCurrentBlock].RamMirror, FALSE);
      if (NvM_aAdminTable[NvM_AdminMultiBlock.unCurrentBlock].BlockState == NVM_STATE_IDLE)
      {
        if (NvM_aAdminTable[NvM_AdminMultiBlock.unCurrentBlock].ErrorStatus != NVM_REQ_OK)
        {
          NvM_AdminMultiBlock.SingleBlockErrorStatus = NvM_aAdminTable[NvM_AdminMultiBlock.unCurrentBlock].ErrorStatus;
        }
        
        // Get the next block
        while ((NvM_AdminMultiBlock.unCurrentBlock < (uint16)NvMBlockCount))          //PRQA S 2461    //intentionally no modification of existing code
        {
          NvM_AdminMultiBlock.unCurrentBlock++;
          if (NvM_AdminMultiBlock.unCurrentBlock >= (uint16)NvMBlockCount)
          {
            // all blocks are processed
            NvM_eState = NVM_STATE_IDLE;
#ifdef NVM_API_V2
            if (E_OK == NvM_aAdminTable[NvmBlockConfigBlockId].ErrorStatus)
            {
              // The config block was read succussfully, check for Config MisMatch
              if (E_OK != NvmCheckConfigBlock())
              {
                //restore Config Block to default
                Nvm_InitConfigBlock();
                NvM_boNeedsRewrite = NvM_RestoreBlocksAfterSwChange();
              }
            }
            else
            {
                // this bas to be discussed, but should work for PSA;
                //restore Config Block to default
                Nvm_InitConfigBlock();
                NvM_boNeedsRewrite = NvM_RestoreBlocksAfterSwChange();
            }
#endif
            NvM_AdminMultiBlock.MultiBlockState = NVM_STATE_IDLE;
            NvM_AdminMultiBlock.ErrorStatus = NvM_AdminMultiBlock.SingleBlockErrorStatus;

          }
          else if (NvM_aAdminTable[NvM_AdminMultiBlock.unCurrentBlock].ErrorStatus != NVM_REQ_BLOCK_SKIPPED)
          {
            // get the next block
            pAdminBlock = &NvM_aAdminTable[NvM_AdminMultiBlock.unCurrentBlock];
            pAdminBlock->BlockState = NVM_STATE_READ_BLOCK;
            pAdminBlock->BlockSubState = NVM_SUB_STATE_MEM_IF_REQ;
            pAdminBlock->ErrorStatus = NVM_REQ_PENDING;
            break;
          }
          else
          {
            //architecture
          }
          //NvM_AdminMultiBlock.unCurrentBlock++;
        }
      }

      break;
    default:
      break;
  }
// PRQA S 5316,5336,5342 1 // program architecture and readability
}


STATIC_AL void Nvm_WriteAllMainFunction(void)
{
  NvM_AdminBlockType* pAdminBlock;
  switch (NvM_AdminMultiBlock.MultiBlockSubState)
  {
  case NVM_MB_SUB_STATE_INIT:
    if (NvM_WriteAllInit() != 0U)
    {
#ifdef UNIT_TEST
      NvM_AdminMultiBlock.unCurrentBlock = (BlockOver != FALSE) ? (uint16)NvMBlockCount : 0u;
#endif

      while ((NvM_AdminMultiBlock.unCurrentBlock < (uint16)NvMBlockCount))          //PRQA S 2461    //intentionally no modification of existing code
      {
        if (NvM_aAdminTable[NvM_AdminMultiBlock.unCurrentBlock].ErrorStatus != NVM_REQ_BLOCK_SKIPPED)
        {
          pAdminBlock = &NvM_aAdminTable[NvM_AdminMultiBlock.unCurrentBlock];
          pAdminBlock->BlockState = NVM_STATE_WRITE_BLOCK;
          pAdminBlock->BlockSubState = NVM_SUB_STATE_DO_CRC;
          pAdminBlock->ErrorStatus = NVM_REQ_PENDING;
          break;
        }
        NvM_AdminMultiBlock.unCurrentBlock++;
      }
      NvM_AdminMultiBlock.MultiBlockSubState = NVM_MB_SUB_STATE_PROCESS_BLOCKS;
    }
    else
    {
      // nothing to do
      NvM_AdminMultiBlock.MultiBlockState = NVM_STATE_IDLE;
      NvM_AdminMultiBlock.ErrorStatus = NVM_REQ_OK;
      NvM_eState = NVM_STATE_IDLE;
    }
    break;
  case NVM_MB_SUB_STATE_PROCESS_BLOCKS:
    HandleBlockWrite(&NvMBlockTable[NvM_AdminMultiBlock.unCurrentBlock],
      &NvM_aAdminTable[NvM_AdminMultiBlock.unCurrentBlock],
      NvMBlockTable[NvM_AdminMultiBlock.unCurrentBlock].RamMirror, FALSE);
    if (NvM_aAdminTable[NvM_AdminMultiBlock.unCurrentBlock].BlockState == NVM_STATE_IDLE)
    {
      if (NvM_aAdminTable[NvM_AdminMultiBlock.unCurrentBlock].ErrorStatus != NVM_REQ_OK)
      {
        NvM_AdminMultiBlock.SingleBlockErrorStatus = NvM_aAdminTable[NvM_AdminMultiBlock.unCurrentBlock].ErrorStatus;
      }

      // Get the next block
      while ((NvM_AdminMultiBlock.unCurrentBlock < (uint16)NvMBlockCount))            //PRQA S 2461    //intentionally no modification of existing code
      {
        NvM_AdminMultiBlock.unCurrentBlock++;
        if (NvM_AdminMultiBlock.unCurrentBlock >= (uint16)NvMBlockCount)
        {
          // all blocks are processed
          NvM_eState = NVM_STATE_IDLE;
          NvM_AdminMultiBlock.MultiBlockState = NVM_STATE_IDLE;
          NvM_AdminMultiBlock.ErrorStatus = NvM_AdminMultiBlock.SingleBlockErrorStatus;

        }
        else if (NvM_aAdminTable[NvM_AdminMultiBlock.unCurrentBlock].ErrorStatus != NVM_REQ_BLOCK_SKIPPED)
        {
          // get the next block
          pAdminBlock = &NvM_aAdminTable[NvM_AdminMultiBlock.unCurrentBlock];
          pAdminBlock->BlockState = NVM_STATE_READ_BLOCK;
          pAdminBlock->BlockSubState = NVM_SUB_STATE_DO_CRC;
          pAdminBlock->ErrorStatus = NVM_REQ_PENDING;
          break;
        }
        else
        {
          //architecture
        }
        //NvM_AdminMultiBlock.unCurrentBlock++;
      }
    }

    break;
  default:
    break;
  }
// PRQA S 5316,5336,5342 1 // program architecture and readability
}

void NvMStateMachine(void)
{
  //NvM_eState = NVM_STATE_WRITE_ALL;
  static NvM_QueueType Job;
  if ((NVM_STATE_IDLE == NvM_eState) && (NvM_boNeedsRewrite != FALSE))
  {
    NvM_WriteAll();
    NvM_boNeedsRewrite = FALSE;
  }
  
  if (NVM_STATE_IDLE == NvM_eState)
  {
      
    if (NvM_AdminMultiBlock.MultiBlockState == NVM_STATE_READ_ALL)
    {
      NvM_eState = NVM_STATE_READ_ALL;
    }
    else if (NvM_AdminMultiBlock.MultiBlockState == NVM_STATE_WRITE_ALL)
    {
      NvM_eState = NVM_STATE_WRITE_ALL;
    }
#if (NVM_API_CONFIG_USE_PRIO_QUEUE == STD_ON)
    else if (E_OK == NvM_GetQueuedPrioBlock(&Job))
    {
      NvM_eState = Job.job;
    }
#endif
    else if (E_OK == NvM_GetQueuedBlock(&Job))
    {
      NvM_eState = Job.job;
    }
    else
    {
      //architecture
    }
  }
  switch(NvM_eState)
  {
    case NVM_STATE_NOT_INIT:
      // Nothing to do here
      break;
    case NVM_STATE_IDLE:
      break;
    case NVM_STATE_WRITE_BLOCK:
      HandleBlockWrite(&NvMBlockTable[Job.blockId],&NvM_aAdminTable[Job.blockId],Job.pucData,FALSE);
      if (NvM_aAdminTable[Job.blockId].BlockState == NVM_STATE_IDLE)
      {
        NvM_eState = NVM_STATE_IDLE;
      }
      break;
    case NVM_STATE_WRITE_ALL:
      Nvm_WriteAllMainFunction();
      break;
    case NVM_STATE_READ_BLOCK:
      HandleBlockRead(&NvMBlockTable[Job.blockId],&NvM_aAdminTable[Job.blockId],Job.pucData,FALSE);
      if (NvM_aAdminTable[Job.blockId].BlockState == NVM_STATE_IDLE)
      {
        NvM_eState = NVM_STATE_IDLE;
      }
      break;
    case NVM_STATE_READ_ALL:
      Nvm_ReadAllMainFunction();
      break;
    default : 
      break;
  }
  // PRQA S 5310, 5316, 5336 1 // program architecture and readability
}



/*
* Initiate the read all job
*/
STATIC_AL boolean NvM_ReadAllInit(void)
{

  /*  Initiate the read all job */
  const tNvMBlockDescriptor* pBlockDescriptor = NvMBlockTable;
  NvM_AdminBlockType* pAdminBlock = NvM_aAdminTable;


  uint16 i;
  boolean needsProcessing = FALSE;

  NvM_AdminMultiBlock.unCurrentBlock = 0;
  // Set status to pending in the administration blocks
  ////AdminMultiBlock.ErrorStatus = NVM_REQ_PENDING; /** req 3.1.5/NVM304 */
  ////AdminMultiReq.PendingErrorStatus = NVM_REQ_OK;
  ////AdminMultiReq.currBlockIndex = 0;
  for (i = 0; i < (uint16)(NvMBlockCount); i++)
  {
    if (pBlockDescriptor->Flags_u16 & NVM_FLAG_READ_ALL)         //PRQA S 3344   //intentionally no modification of existing code
    {
      //NVM_ASSERT(BlockDescriptorList->RamBlockDataAddress != NULL);
      //DET_VALIDATE_RV(BlockDescriptorList->RamBlockDataAddress != NULL, NVM_READ_ALL_ID, NVM_E_WRONG_CONFIG, FALSE);
      ///* 3.1.5/NVM245 */
      //NVM_ASSERT(BlockDescriptorList->BlockManagementType != NVM_BLOCK_DATASET);
      //DET_VALIDATE_RV(BlockDescriptorList->BlockManagementType != NVM_BLOCK_DATASET, NVM_READ_ALL_ID, NVM_E_WRONG_CONFIG, FALSE);

      pAdminBlock->ErrorStatus = NVM_REQ_PENDING;
      pAdminBlock->BlockSubState = NVM_SUB_STATE_MEM_IF_REQ;
      needsProcessing = TRUE;
    }
    else
    {
      pAdminBlock->ErrorStatus = NVM_REQ_BLOCK_SKIPPED;  /* req  3.1.5/NVM287 */
    }

    pAdminBlock++;
    pBlockDescriptor++;
  }

  return needsProcessing;

}
#ifdef NVM_API_V2

STATIC_AL boolean NvM_RestoreBlocksAfterSwChange(void)
{
  uint16 i;
  const tNvMBlockDescriptor* pBlockDescriptor = NvMBlockTable;

  NvM_AdminBlockType* pAdminBlock = NvM_aAdminTable;
  boolean needsProcessing = FALSE;


  for (i = 0; i < (uint16)(NvMBlockCount); i++)
  {
    if ((pBlockDescriptor->Flags_u16 & NVM_FLAG_RESISTANT_TO_SW_CHANGE) == 0U)
    {
      // block needs ReInit after SW change

      //pAdminBlock->ErrorStatus = NVM_REQ_PENDING;
      //pAdminBlock->RamCrc = NVM_CRC_START_VALUE;
      //pAdminBlock->BlockSubState = NVM_SUB_STATE_DO_CRC;
      needsProcessing = TRUE;
      if (pBlockDescriptor->InitRom != NULL_PTR)
      {
        UtilMemCopy(pBlockDescriptor->RamMirror,pBlockDescriptor->InitRom, pBlockDescriptor->BlockSize_u16);
      }
      else if (pBlockDescriptor->pfnInitCallback != NULL_PTR)
      {
        pBlockDescriptor->pfnInitCallback();
      }
      else
      {
        //architecture
      }

    }
    else
    {
      //pAdminBlock->ErrorStatus = NVM_REQ_BLOCK_SKIPPED;  /* req  3.1.5/NVM287 */
    }

    //pAdminBlock++;
    pBlockDescriptor++;
  }

  return needsProcessing;


}
#endif

STATIC_AL boolean NvM_WriteAllInit(void)
{

  /*  Initiate the read all job */
  const tNvMBlockDescriptor* pBlockDescriptor = NvMBlockTable;
  NvM_AdminBlockType* pAdminBlock = NvM_aAdminTable;
  uint16 i;
  boolean needsProcessing = FALSE;

  NvM_AdminMultiBlock.unCurrentBlock = 0;
  // Set status to pending in the administration blocks
  ////AdminMultiBlock.ErrorStatus = NVM_REQ_PENDING; /** req 3.1.5/NVM304 */
  ////AdminMultiReq.PendingErrorStatus = NVM_REQ_OK;
  ////AdminMultiReq.currBlockIndex = 0;
  for (i = 0U; i < (uint16)(NvMBlockCount); i++)
  {
#ifdef NVM_API_V2
    if (pBlockDescriptor->Flags_u16 & NVM_FLAG_WRITE_ALL)        //PRQA S 3344   //intentionally no modification of existing code
#else
    if (pBlockDescriptor->Flags_u16 & NVM_FLAG_READ_ALL)         //PRQA S 3344   //intentionally no modification of existing code
#endif
    {
      //NVM_ASSERT(BlockDescriptorList->RamBlockDataAddress != NULL);
      //DET_VALIDATE_RV(BlockDescriptorList->RamBlockDataAddress != NULL, NVM_READ_ALL_ID, NVM_E_WRONG_CONFIG, FALSE);
      ///* 3.1.5/NVM245 */
      //NVM_ASSERT(BlockDescriptorList->BlockManagementType != NVM_BLOCK_DATASET);
      //DET_VALIDATE_RV(BlockDescriptorList->BlockManagementType != NVM_BLOCK_DATASET, NVM_READ_ALL_ID, NVM_E_WRONG_CONFIG, FALSE);

      pAdminBlock->ErrorStatus = NVM_REQ_PENDING;
      pAdminBlock->RamCrc = NVM_CRC_START_VALUE;
      pAdminBlock->BlockSubState = NVM_SUB_STATE_DO_CRC;
      needsProcessing = TRUE;
    }
    else
    {
      pAdminBlock->ErrorStatus = NVM_REQ_BLOCK_SKIPPED;  /* req  3.1.5/NVM287 */
    }

    pAdminBlock++;
    pBlockDescriptor++;
  }

  return needsProcessing;

}

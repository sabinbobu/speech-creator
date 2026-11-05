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
/// \file   Nvm_Internal.h
///
/// \brief  Header file for Nvm_Internal.c
///
/// \descr  Declarations, management types and NVRAM block structures
///
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
//-----------------------------------------------------------------------------

#ifndef NVM_INTERNAL_2021_03_31_H_
#define NVM_INTERNAL_2021_03_31_H_


  #include <Std_Types.h>
  #include <Nvm_Types.h>
  #include <MemIf.h>
  #include <UtilBase.h>

  #define NVM_CRC_SIZE 4u
  

extern tieNvMState NvM_eState;


typedef struct {
  tieNvMState job;
  NvM_BlockIdType blockId;
  uint8 * pucData;    /* Src or Dest ptr */
  uint8   dataIndex;
  boolean blockChanged;
  uint8    serviceId;
} NvM_QueueType;


typedef uint32 tNvmCrc;

// tbd
  typedef  enum Nvm_SubState
  {
    NVM_SUB_STATE_DO_CRC       = 0u,
    NVM_SUB_STATE_MEM_IF_REQ   = 1u,
    NVM_SUB_STATE_MEM_IF_PROC  = 2u,
    NVM_SUB_STATE_FINALIZE     = 3u
  }
  tieNvMSubState;

  typedef  enum Nvm_MultiBlockSubState
  {
    NVM_MB_SUB_STATE_INIT = 0u,
    NVM_MB_SUB_STATE_PROCESS_BLOCKS = 1u
  }
  tieMultiBlockSubState;

typedef uint8 BlockSubStateType;

typedef struct {
  tieNvMState             BlockState;
  tieNvMSubState          BlockSubState;
  uint8                   DataIndex;            // Selected data index if "Data Set" type
  boolean                 BlockWriteProtected;  // Block write protected?
  NvM_RequestResultType   ErrorStatus;          // Status of block
  boolean                 BlockChanged;         // Block changed?
  boolean                 BlockValid;           // Block valid? (RAM block only?)
  uint8                   NumberOfWriteFailed;  // Current write retry cycle
  tNvmCrc                 RamCrc;
  tNvmCrc                 NvCrc;                // The CRC of this block, read from NV
  void *          savedpucData;                 //
} NvM_AdminBlockType;

typedef struct {
  NvM_RequestResultType   ErrorStatus;          // Status of Multiblock request
  NvM_RequestResultType   SingleBlockErrorStatus;
  tieNvMState             MultiBlockState;
  tieMultiBlockSubState   MultiBlockSubState;
  uint16                  unCurrentBlock;
} NvM_AdminMultiBlockType;

extern NvM_AdminBlockType NvM_aAdminTable[NvMBlockCount];
extern NvM_AdminMultiBlockType NvM_AdminMultiBlock;

void NvMStateMachine(void);
Std_ReturnType NvM_QueueBlock(NvM_QueueType * pJob);
void NvM_ClearQueue(void);

#if (NVM_API_CONFIG_USE_PRIO_QUEUE == STD_ON)
Std_ReturnType NvM_QueueBlockPrio(NvM_QueueType * pJob);
void NvM_ClearQueuePrio(void);
#endif


#endif // NVM_INTERNAL_2021_03_31_H_

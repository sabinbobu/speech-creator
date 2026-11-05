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
/// \file  Test.h
///
/// \brief This file contains functions prototypes of the tested module, 
///        including functions parameters and global variables
///
//-----------------------------------------------------------------------------
#ifndef TEST_2023_08_25_H_
#define TEST_2023_08_25_H_

//=============================================================================
// Includes
//=============================================================================
#include <AL_Helper.h>

// Headers of the Nvm Module
#include <Nvm.h>
#include <Nvm_Id.h>
#include <ctaaNvm.h>
#include <Nvm_Internal.h>

//=============================================================================
// Typedefs
//=============================================================================


//=============================================================================
// Defines
//=============================================================================

#define NvM_QUEUE_SIZE              10
#define NVM_CRC_START_VALUE         0x0U
#define Nvm_EmptyMarker             -1

//=============================================================================
// Module global variables
//=============================================================================
//ctaaNvm.c
extern boolean                  NvM_boInitialized;

//Nvm.c

//Nvm_Internal.c
extern NvM_AdminBlockType       NvM_aAdminTable[NvMBlockCount];
extern NvM_AdminMultiBlockType  NvM_AdminMultiBlock;

extern uint8                    NvM_aucMemIf_Buffer[sizeof(memif_io_buffer_t)];
extern tieNvMState              NvM_eState;

extern NvM_QueueType            NvmQueue[NvM_QUEUE_SIZE];
extern sint16                   NvM_ucQueueFront;
extern sint16                   NvM_ucQueueRear;

#if (NVM_API_CONFIG_USE_PRIO_QUEUE == STD_ON)
extern NvM_QueueType            NvmQueuePrio[NvM_QUEUE_SIZE];
extern sint16                   NvM_ucQueuePrioFront;
extern sint16                   NvM_ucQueuePrioRear;
#endif

extern boolean                  NvM_boNeedsRewrite;
extern boolean                  BlockOver;


//=============================================================================
// Module function declarations
//=============================================================================

//ctaaNvm.c

//Nvm.c

//Nvm_Id.c
extern void                     NvM_GetDefaultConfigBlock(tNvMConfigBlock* ConfigBlock);

extern uint32                   MemIfReadCrc(uint8* pucSrc);
extern void                     MemIfWriteCrc(uint8* pucDest, uint32 ulCrc);

//--------------------------------- 
#if (NVM_API_CONFIG_USE_PRIO_QUEUE == STD_ON)
extern boolean                  NwM_IsQueuePrioFull();
extern boolean                  NwM_IsQueuePrioEmpty();
extern Std_ReturnType           NvM_QueueBlockPrio(NvM_QueueType* pJob);
extern Std_ReturnType           NvM_GetQueuedPrioBlock(NvM_QueueType* pJob);
#endif
//----------------------------------

extern void                     HandleBlockWrite(tNvMBlockDescriptor* pBlock, NvM_AdminBlockType* pAdminBlock, void* pData, boolean boMulti);
extern void                     HandleBlockRead(tNvMBlockDescriptor* pBlock, NvM_AdminBlockType* pAdminBlock, void* pData, boolean bMulti);
extern void                     Nvm_ReadAllMainFunction(void);
extern void                     Nvm_WriteAllMainFunction(void);
extern boolean                  NvM_ReadAllInit(void);
extern boolean                  NvM_WriteAllInit(void);
extern boolean                  NvM_RestoreBlocksAfterSwChange(void);

//=============================================================================
// Module function parameter stubs
//=============================================================================

//Nvm.c
NvM_BlockIdType                 NvM_ReadBlock_Param1;
void*                           NvM_ReadBlock_Param2;
NvM_BlockIdType                 NvM_WriteBlock_Param1;
void*                           NvM_WriteBlock_Param2;
NvM_BlockIdType                 NvM_WriteBlockPrio_Param1;
void*                           NvM_WriteBlockPrio_Param2;

NvM_BlockIdType                 NvM_GetErrorStatus_Param1;
NvM_RequestResultType           NvM_GetErrorStatus_Param2;

//Nvm_Id.c
tNvMConfigBlock                 NvM_GetDefaultConfigBlock_Param1;

//Nvm_Internal.c
uint8                           MemIfReadCrc_Param1[2];
uint8                           MemIfWriteCrc_Param1[2];
uint32                          MemIfWriteCrc_Param2;

NvM_QueueType*                  NvM_QueueBlock_Param1;
NvM_QueueType*                  NvM_GetQueuedBlock_Param1;
#if (NVM_API_CONFIG_USE_PRIO_QUEUE == STD_ON)
NvM_QueueType*                  NvM_QueueBlockPrio_Param1;
NvM_QueueType*                  NvM_GetQueuedPrioBlock_Param1;
#endif

tNvMBlockDescriptor             HandleBlockWrite_Param1;
NvM_AdminBlockType              HandleBlockWrite_Param2;
void*                           HandleBlockWrite_Param3;
boolean                         HandleBlockWrite_Param4;

tNvMBlockDescriptor             HandleBlockRead_Param1;
NvM_AdminBlockType              HandleBlockRead_Param2;
void*                           HandleBlockRead_Param3;
boolean                         HandleBlockRead_Param4;


//=============================================================================
// Module function return value stubs
//=============================================================================

//Nvm.c
tieNvMState                     NvM_GetState_RetVal;
Std_ReturnType                  NvM_ReadBlock_RetVal;
Std_ReturnType                  NvM_WriteBlock_RetVal;
Std_ReturnType                  NvM_WriteBlockPrio_RetVal;
Std_ReturnType                  NvM_GetErrorStatus_RetVal;

//Nvm_Id.c
Std_ReturnType                  NvmCheckConfigBlock_RetVal;

//Nvm_Internal.c                
uint32                          MemIfReadCrc_RetVal;
boolean                         NwM_IsQueueFull_RetVal;
boolean                         NwM_IsQueueEmpty_RetVal;
Std_ReturnType                  NvM_QueueBlock_RetVal;
Std_ReturnType                  NvM_GetQueuedBlock_RetVal;

#if (NVM_API_CONFIG_USE_PRIO_QUEUE == STD_ON)
boolean                         NwM_IsQueuePrioFull_RetVal;
boolean                         NwM_IsQueuePrioEmpty_RetVal;
Std_ReturnType                  NvM_QueueBlockPrio_RetVal;
Std_ReturnType                  NvM_GetQueuedPrioBlock_RetVal;
#endif
boolean                         NvM_ReadAllInit_RetVal;
boolean                         NvM_WriteAllInit_RetVal;
boolean                         NvM_RestoreBlocksAfterSwChange_RetVal;


//=============================================================================
// Module static variables inside functions 
//=============================================================================


#endif // TEST_2023_08_25_H_

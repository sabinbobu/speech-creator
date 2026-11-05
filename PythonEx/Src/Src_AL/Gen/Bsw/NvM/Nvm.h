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
/// \file   Nvm.h
///
/// \brief  Header file for Nvm.c
///
/// \descr  Declarations, NV job types and NVRAM block descriptors
///
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
//-----------------------------------------------------------------------------


#ifndef NVM_2021_03_31_H_
#define NVM_2021_03_31_H_



  //lint -e451 Header file repeatedly included but does not have a standard include guard
  #include <AL_Helper.h>
  //lint +e451 Header file repeatedly included but does not have a standard include guard
  #include "NvM_Types.h"

  #include "MemIf.h"

  #define NVM_CRC_SIZE 4u
  
  #define _MAC_ENUM
//lint -e451 Header file repeatedly included but does not have a standard include guard
  #include <Bsw/NvM/Nvm_Cfg.h>
//lint +e451 Header file repeatedly included but does not have a standard include guard
  #undef  _MAC_ENUM

#define _MAC_MEMIF_BUFFER
//lint -e451 Header file repeatedly included but does not have a standard include guard
#include <Bsw/Nvm/Nvm_Cfg.h>
//lint +e451 Header file repeatedly included but does not have a standard include guard
#undef _MAC_MEMIF_BUFFER

// NVM Flag definitions

#define NVM_FLAG_READ_ALL                0x0001U

#ifdef NVM_API_V2
#define NVM_FLAG_WRITE_ALL               0x0002U
#define NVM_FLAG_RESISTANT_TO_SW_CHANGE  0x0004U
#endif // NVM_API_V2


#define NVM_FLAG_READ_WRITE_ALL (NVM_FLAG_READ_ALL | NVM_FLAG_WRITE_ALL)


  typedef  enum NvM_eState
  {
    NVM_STATE_NOT_INIT     = 0u,
    NVM_STATE_IDLE         = 1u,
    NVM_STATE_WRITE_BLOCK  = 2u,
    NVM_STATE_WRITE_ALL    = 3u,
    NVM_STATE_READ_BLOCK   = 4u,
    NVM_STATE_READ_ALL     = 5u,
    NVM_STATE_RESTORE_BLOCK_DEFAULTS = 6u,
    NVM_STATE_SETDATAINDEX    = 7u,
    NVM_STATE_GETDATAINDEX    = 8u,
    NVM_STATE_SETRAMBLOCKSTATUS = 9u,
    NVM_STATE_INVALIDATE_NV_BLOCK = 10u
  }
  tieNvMState;

  typedef  enum NvM_JobType
  {
    NVM_JOB_WRITE          = 0u,
    NVM_JOB_WRITE_ALL      = 1u,
    NVM_JOB_READ           = 2u,
    NVM_JOB_READ_ALL       = 3u,
  }
  tieNvMJobType;




  typedef  enum NvM_Error
  {
    NVM_OK              = 0u,
    NVM_BUSY            = 1u,
    NVM_FATAL_ERROR     = 2u,
    NVM_WRITE_ERROR     = 3u,
    NVM_READ_ERROR      = 5u,
    NVM_CRC_ERROR       = 6u
  }
  tieNvMError;


#define NVM_BLOCK_STATUS_INIT 0
  
  typedef void(*pNvmInitFunc) (void);
  typedef void(*pNvmCallbackFunc) (void);


  typedef struct struct_Nvm_BlockDescriptor
  {
    uint8 BlockStatus;
    uint8 *RamMirror;
    uint8  MemIfDevice_u8;
    uint16 MemIfBlockId_u16;
    uint16 BlockSize_u16;
    uint16 Flags_u16;
    uint8 *InitRom;
    pNvmInitFunc pfnInitCallback;
    pNvmCallbackFunc pfnCallBackFunc;
  }  tNvMBlockDescriptor;

  
  typedef unsigned int tNvmBlockId;

  

  #define _MAC_EXTERN
//lint -e451 Header file repeatedly included but does not have a standard include guard
  #include <Bsw/Nvm/Nvm_Cfg.h>
//lint +e451 Header file repeatedly included but does not have a standard include guard
  #undef _MAC_EXTERN

  #ifndef NVM_API_CONFIG_USE_PRIO_QUEUE
    #define NVM_API_CONFIG_USE_PRIO_QUEUE  STD_OFF
  #endif

  /* API functions */
  
  void NvM_Init(void);
  void NvM_MainFunction(void);
  Std_ReturnType NvM_WriteBlock(NvM_BlockIdType BlockId, void* NvM_SrcPtr);
#if (NVM_API_CONFIG_USE_PRIO_QUEUE == STD_ON)
  Std_ReturnType NvM_WriteBlockPrio(NvM_BlockIdType BlockId, void* NvM_SrcPtr);
#endif
  Std_ReturnType NvM_ReadBlock(NvM_BlockIdType BlockId, void* NvM_DstPtr);
  void NvM_WriteAll(void);
  void NvM_CancelWriteAll(void);
  void NvM_ReadAll(void);

  Std_ReturnType NvM_GetErrorStatus(NvM_BlockIdType BlockId, NvM_RequestResultType *RequestResultPtr);
  tieNvMState NvM_GetState(void);
 // tieNvMError Nvm_Format(void);

#if defined (CFG_VARIANT_FULL) || defined(UNIT_TEST) // Applicable only for FULL version
  void reNvm_WritePxlData(void);
#endif

#endif // NVM_2021_03_31_H_

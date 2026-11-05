#ifndef _FEE_H_
#define _FEE_H_

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
/// \file   Fee.h
///
/// \brief  Header file for Fee.c
///
/// \descr  Functions used for Flash EEPROM EMULATION
///         Types of Fee Block structures and commands
///
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
//-----------------------------------------------------------------------------

#include <Bsw/MemIf/MemIf_Types.h>

  #define _MAC_ENUM
//lint -e451 Header file repeatedly included but does not have a standard include guard
  #include <Fee_Cfg.h>
//lint +e451 Header file repeatedly included but does not have a standard include guard
  #undef  _MAC_ENUM



#define FEE_BLOCK_STATUS_INIT 0


// Service Id of Fee_Init 
#define FEE_INIT_SID                 (uint8)( 0x00 )
// Service Id of Fee_SetMode 
#define FEE_SETMODE_SID              (uint8)( 0x01 )
// Service Id of Fee_Read 
#define FEE_READ_SID                 (uint8)( 0x02 )
// Service Id of Fee_Write 
#define FEE_WRITE_SID                (uint8)( 0x03 )
// Service Id of Fee_Cancel 
#define FEE_CANCEL_SID               (uint8)( 0x04 )
// Service Id of Fee_GetStatus 
#define FEE_GETSTATUS_SID            (uint8)( 0x05 )
// Service Id of Fee_GetJobResult 
#define FEE_GETJOBRESULT_SID         (uint8)( 0x06 )
// Service Id of Fee_InvalidateBlock 
#define FEE_INVALIDATEBLOCK_SID      (uint8)( 0x07 )
// Service Id of Fee_GetVersionInfo 
#define FEE_GET_VERSION_INFO_SID     (uint8)( 0x08 )
// Service Id of Fee_EraseImmediateBlock 
#define FEE_ERASEIMMEDIATEBLOCK_SID  (uint8)( 0x09 )

/*******************************************************************************
**                      DET Error Codes                                       **
*******************************************************************************/

// API service called when module was not initialized
#define  FEE_E_UNINIT             0x01
//  API service called with invalid block number
#define  FEE_E_INVALID_BLOCK_NO   0x02
// API service called with invalid block offset
#define  FEE_E_INVALID_BLOCK_OFS  0x03
// API service called with invalid data pointer
#define  FEE_E_PARAM_POINTER      0x04
// API service called with invalid length information
#define  FEE_E_INVALID_BLOCK_LEN  0x05
// API service called while module is busy processing a user request
#define  FEE_E_BUSY               0x06
// API service called while module is busy doing internal management operations.
#define  FEE_E_BUSY_INTERNAL      0x07
// Fee_Cancel called while no job was pending.
#define  FEE_E_INVALID_CANCEL     0x08
// Fee_Init failed.
#define  FEE_E_INIT_FAILED        0x09


/*******************************************************************************
* Flash hardware algorithm operation commands
*******************************************************************************/
#define FEE_VERIFY_BLOCK             0x00U
#define FEE_VERIFY_SECTION           0x01U
#define FEE_PROGRAM_CHECK            0x02U
#define FEE_READ_RESOURCE            0x03U
#define FEE_PROGRAM_LONGWORD         0x06U
#define FEE_PROGRAM_PHRASE           0x07U
#define FEE_ERASE_BLOCK              0x08U
#define FEE_ERASE_SECTOR             0x09U
#define FEE_PROGRAM_SECTION          0x0BU
#define FEE_VERIFY_ALL_BLOCK         0x40U
#define FEE_READ_ONCE                0x41U
#define FEE_PROGRAM_ONCE             0x43U
#define FEE_ERASE_ALL_BLOCK          0x44U
#define FEE_SECURITY_BY_PASS         0x45U
#define FEE_PFLASH_SWAP              0x46U
#define FEE_ERASE_ALL_BLOCK_UNSECURE 0x49U
#define FEE_PROGRAM_PARTITION        0x80U
#define FEE_SET_EERAM                0x81U



  typedef struct struct_Fee_BlockDescriptor
  {
    uint16  unBlockId;
    uint16  unBlockSize;
    boolean boImmediateData;
  }  tFeeBlockDescriptor;

  typedef  enum Fee_State
  {
    FEE_STATE_NOT_INIT  = 0u,
    FEE_STATE_IDLE      = 1u,
    FEE_STATE_WRITE     = 2u,
    FEE_STATE_READ      = 4u,
    FEE_STATE_READ_ALL  = 5u,
    FEE_STATE_FORMAT1   = 6u,
    FEE_STATE_FORMAT2   = 7u,
    FEE_STATE_ERROR     = 8u
  }
  tieFeeState;

#if 0
  typedef enum Fee_FlexRAM_Control
  {
    EEE_ENABLE                          = 0x00U,    /* Make FlexRAM available for emulated EEPROM */
    EEE_QUICK_WRITE                     = 0x55U,    /* Make FlexRAM available for EEPROM quick writes */
    EEE_STATUS_QUERY                    = 0x77U,    /* EEPROM quick write status query */
    EEE_COMPLETE_INTERRUPT_QUICK_WRITE  = 0xAAU,    /* Complete interrupted EEPROM quick write process */
    EEE_DISABLE                         = 0xFFU,    /* Make FlexRAM available as RAM */
  } tieFee_FlexRAM_Control; 
#endif 



  //FEE module status
  typedef enum Fee_ErrType
  {
    FEE_ERR_NO          = 0x00u,                   ///< Generic operation success status
    FEE_ERR_ERROR       = 0x01u,                   ///< Generic operation failure status
    FEE_ERR_BUSY        = 0x02u,                   ///< Previous operation not completed
    FEE_ERR_ADDRESS     = 0x03u,                   ///< Invalid address error
    FEE_ERR_ALREADY_PARTITIONED = 0x04u,           ///< Memory already partitioned

    /* EEE specific error codes */
    FEE_ERR_NO_ENOUGH_SPACE   = 0xD00U, /*!< The data is too big to fit in any of the block */
    FEE_ERR_NO_ENOUGH_BLOCK   = 0xD01U, /*!< The block numbers is not enough for round robin */
    FEE_ERR_DATA_NOT_FOUND    = 0xD02U, /*!< The required data is not found in the EEPROM emulation */
    FEE_ERR_NOT_IN_CACHE      = 0xD03U, /*!< The required data is not in the cache table */
    FEE_ERR_PROGRAM_INDICATOR = 0xD04U, /*!< Failed to make block indicator to non-blank for several times */
    FEE_HVOP_INPROGRESS       = 0xD05U, /*!< The high voltage operation is in progress */

  }tieFeeErr;




  #define _MAC_EXTERN
//lint -e451 Header file repeatedly included but does not have a standard include guard
  #include <Bsw/MCal/Fee/Fee_Cfg.h>
//lint +e451 Header file repeatedly included but does not have a standard include guard
  #undef _MAC_EXTERN



//=============================================================================
// Exported Functions Declaration
//=============================================================================
// Flash access functions

  void Fee_Init(void);

  void Fee_SetMode(MemIf_ModeType Mode);

  Std_ReturnType Fee_Read(uint16 BlockNumber,
                          uint16 BlockOffset,
                          uint8* DataBufferPtr,
                          uint16 Length);

  Std_ReturnType Fee_Write(uint16 BlockNumber,
                           uint8* DataBufferPtr);

  MemIf_StatusType Fee_GetStatus(void);

  MemIf_JobResultType Fee_GetJobResult(void);

  Std_ReturnType Fee_InvalidateBlock(uint16 BlockNumber);

  Std_ReturnType Fee_EraseImmediateBlock(uint16 BlockNumber);

  void Fee_MainFunction(void);

  Std_ReturnType Fee_GetOpStatus(void);

#if FEE_USE_FEE_FORMAT == STD_ON
  Std_ReturnType Fee_Format(void);
#endif

#endif /*_FEE_H_ */

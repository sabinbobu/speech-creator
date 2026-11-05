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
/// \file  Fee_TargetTypes.h
///
/// \brief
///
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
//-----------------------------------------------------------------------------
/*---- Protection against multiple inclusion -------------------------------*/
#ifndef FEE_TARGET_TYPES_2021_04_13_H_
#define FEE_TARGET_TYPES_2021_04_13_H_

#include <AL_Helper.h>
#include <MemIf_Types.h>
#include <Device_TargetTypes.h>

//=============================================================================
// Private types
//=============================================================================

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

//=============================================================================
// typedef
//=============================================================================

typedef void(*flash_callback_t)(void);
#define NULL_CALLBACK      ((flash_callback_t)0xFFFFFFFFU)

typedef  enum Fee_State
{
  FEE_STATE_NOT_INIT = 0u,
  FEE_STATE_IDLE = 1u,
  FEE_STATE_WRITE = 2u,
  FEE_STATE_READ = 4u,
  FEE_STATE_READ_ALL = 5u,
  FEE_STATE_FORMAT1 = 6u,
  FEE_STATE_FORMAT2 = 7u,
  FEE_STATE_ERROR = 8u
}tieFeeState;

//FEE module status
typedef enum Fee_ErrType
{
  FEE_ERR_NO = 0x00u,                   ///< Generic operation success status
  FEE_ERR_ERROR = 0x01u,                   ///< Generic operation failure status
  FEE_ERR_BUSY = 0x02u,                   ///< Previous operation not completed
  FEE_ERR_ADDRESS = 0x03u,                   ///< Invalid address error
  FEE_ERR_ALREADY_PARTITIONED = 0x04u,           ///< Memory already partitioned

  /* EEE specific error codes */
  FEE_ERR_NO_ENOUGH_SPACE = 0xD00U, /*!< The data is too big to fit in any of the block */
  FEE_ERR_NO_ENOUGH_BLOCK = 0xD01U, /*!< The block numbers is not enough for round robin */
  FEE_ERR_DATA_NOT_FOUND = 0xD02U, /*!< The required data is not found in the EEPROM emulation */
  FEE_ERR_NOT_IN_CACHE = 0xD03U, /*!< The required data is not in the cache table */
  FEE_ERR_PROGRAM_INDICATOR = 0xD04U, /*!< Failed to make block indicator to non-blank for several times */
  FEE_HVOP_INPROGRESS = 0xD05U, /*!< The high voltage operation is in progress */
}tieFeeErr;

typedef enum
{
  EEE_ENABLE = 0x00U,    /*!< Make FlexRAM available for emulated EEPROM */
  EEE_QUICK_WRITE = 0x55U,    /*!< Make FlexRAM available for EEPROM quick writes */
  EEE_STATUS_QUERY = 0x77U,    /*!< EEPROM quick write status query */
  EEE_COMPLETE_INTERRUPT_QUICK_WRITE = 0xAAU,    /*!< Complete interrupted EEPROM quick write process */
  EEE_DISABLE = 0xFFU,    /*!< Make FlexRAM available as RAM */
} flash_flexRam_function_control_code_t;

typedef struct
{
  uint32_t PFlashBase;            /*!< The base address of P-Flash memory */
  uint32_t PFlashSize;            /*!< The size in byte of P-Flash memory */
  uint32_t DFlashBase;            /*!< For FlexNVM device, this is the base address of D-Flash memory
                                   *    (FlexNVM memory); For non-FlexNVM device, this field is unused */
  uint32_t EERAMBase;             /*!< The base address of FlexRAM (for FlexNVM device)
                                   *    or acceleration RAM memory (for non-FlexNVM device) */
  flash_callback_t CallBack;      /*!< Call back function to service the time critical events. Any code reachable from this function
                                   *   must not be placed in a Flash block targeted for a program/erase operation */
} flash_user_config_t;   /* Flash User Configuration Structure*/

typedef struct
{
  uint32_t PFlashBase;          /*!< The base address of P-Flash memory */
  uint32_t PFlashSize;          /*!< The size in byte of P-Flash memory */
  uint32_t DFlashBase;          /*!< For FlexNVM device, this is the base address of D-Flash memory (FlexNVM memory);
                                 *    For non-FlexNVM device, this field is unused */
  uint32_t DFlashSize;          /*!< For FlexNVM device, this is the size in byte of area
                                 *    which is used as D-Flash from FlexNVM memory;
                                 *    For non-FlexNVM device, this field is unused */
  uint32_t EERAMBase;           /*!< The base address of FlexRAM (for FlexNVM device)
                                 *    or acceleration RAM memory (for non-FlexNVM device) */
  uint32_t EEESize;             /*!< For FlexNVM device, this is the size in byte of EEPROM area which was partitioned
                                 *    from FlexRAM; For non-FlexNVM device, this field is unused */
  flash_callback_t CallBack;    /*!< Call back function to service the time critical events. Any code reachable from this function
                                 *   must not be placed in a Flash block targeted for a program/erase operation */
} flash_ssd_config_t;     /*Flash SSD Configuration Structure*/

typedef struct struct_Fee_BlockDescriptor
{
  uint16  unBlockId;
  uint16  unBlockSize;
  boolean boImmediateData;
}tFeeBlockDescriptor;

//=============================================================================
// Register Stubs for UT
//=============================================================================
/** FTFC - Size of Registers Arrays */
#define FTFC_FCCOB_COUNT                         12u
#define FTFC_FPROT_COUNT                         4u

/** FTFC - Register Layout Typedef */
typedef struct {
 uint8_t FSTAT;                              /**< Flash Status Register, offset: 0x0 */
 uint8_t FCNFG;                              /**< Flash Configuration Register, offset: 0x1 */
 uint8_t FSEC;                               /**< Flash Security Register, offset: 0x2 */
 uint8_t FOPT;                               /**< Flash Option Register, offset: 0x3 */
 uint8_t FCCOB[FTFC_FCCOB_COUNT];            /**< Flash Common Command Object Registers, array offset: 0x4, array step: 0x1 */
 uint8_t FPROT[FTFC_FPROT_COUNT];            /**< Program Flash Protection Registers, array offset: 0x10, array step: 0x1 */
 uint8_t RESERVED_0[2];
 uint8_t FEPROT;                             /**< EEPROM Protection Register, offset: 0x16 */
 uint8_t FDPROT;                             /**< Data Flash Protection Register, offset: 0x17 */
 uint8_t RESERVED_1[20];
 uint8_t FCSESTAT;                           /**< Flash CSEc Status Register, offset: 0x2C */
 uint8_t RESERVED_2[1];
 uint8_t FERSTAT;                            /**< Flash Error Status Register, offset: 0x2E */
 uint8_t FERCNFG;                            /**< Flash Error Configuration Register, offset: 0x2F */
} FTFC_Type, *FTFC_MemMapPtr;

/** Number of instances of the FTFC module. */
#define FTFC_INSTANCE_COUNT                       (1u)

FTFC_Type FTFC_sReg;

#define FTFC_BASE                                 (&FTFC_sReg)
#define FTFC                                      (FTFC_BASE)

/* FCNFG Bit Fields */
#define FTFC_FCNFG_EEERDY_MASK                    0x1u
#define FTFC_FSTAT_CCIF_MASK                      0x80u
#define FTFC_FSTAT_MGSTAT0_MASK                   0x1u
#define FTFC_FSTAT_FPVIOL_MASK                    0x10u
#define FTFC_FSTAT_ACCERR_MASK                    0x20u
#define FTFC_FSTAT_RDCOLERR_MASK                  0x40u

#define FTFx_FCNFG_EEERDY_MASK                    FTFC_FCNFG_EEERDY_MASK
#define FTFx_FSTAT_MGSTAT0_MASK                   FTFC_FSTAT_MGSTAT0_MASK
#define FTFx_FSTAT_FPVIOL_MASK                    FTFC_FSTAT_FPVIOL_MASK
#define FTFx_FSTAT_ACCERR_MASK                    FTFC_FSTAT_ACCERR_MASK
#define FTFx_FSTAT_RDCOLERR_MASK                  FTFC_FSTAT_RDCOLERR_MASK


#define FTFx_FCNFG                                FTFC->FCNFG
#define FTFx_FSTAT                                FTFC->FSTAT


#define FTFx_FSTAT_ERROR_BITS (FTFx_FSTAT & (FTFx_FSTAT_MGSTAT0_MASK | FTFx_FSTAT_FPVIOL_MASK | FTFx_FSTAT_ACCERR_MASK | FTFx_FSTAT_RDCOLERR_MASK))


#endif // FEE_TARGET_TYPES_2021_04_13_H_

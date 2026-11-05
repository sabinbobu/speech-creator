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
/// \file  Fee.c
///
/// \brief  Flash EEPROM EMULATION
///
/// \descr  Functions for EMULATED EEPROM mechanism that are responsible for:
///         Initialize the flash memory to simulate EEPROM.
///         Partition the flash memory for EEPROM functionality (FlexRAM block, FlexNVM block)
///         Read the requested memory block by accessing the FlexRAM address space
///         Write the requested memory block into E-Flash by accessing the FlexRAM address space
///
///
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
//-----------------------------------------------------------------------------

#include <Fee.h>
#include <Fee_InternalFct.h>
#include <Std_Types.h>

#ifndef UNIT_TEST
#include <flash_driver.h>
#include <interrupt_manager.h>
#else
typedef struct
{
  uint8_t brownOutCode;               /*!< Brown-out detection code */
  uint16_t numOfRecordReqMaintain;    /*!< Number of EEPROM quick write records requiring maintenance */
  uint16_t sectorEraseCount;          /*!< EEPROM sector erase count */
} flash_eeprom_status_t;

#include <Fee_TargetTypes.h>        //needed for register stubs 
#define DEV_ASSERT(x) ((void)0)     //needed for UT
#endif


//=============================================================================
// preprocessor definitions
//=============================================================================


//=============================================================================
// Private types
//=============================================================================

typedef Std_ReturnType(*CallbackFuncType)(void);
/* Function declarations */

STATIC_AL Std_ReturnType Fee_EEERead(const flash_ssd_config_t * pSSDConfig, uint32 ulAddress, uint32 ulSize, uint8 *pucData);
STATIC_AL Std_ReturnType Fee_EEEWrite(const flash_ssd_config_t * pSSDConfig, uint32 ulAddress, uint32 ulSize, const uint8 * pucData);
STATIC_AL Std_ReturnType Fee_WaitEEWriteToFinish(const flash_ssd_config_t * pSSDConfig, uint32 ulAddress, const uint8 * pucData, uint8 ucStep);


//=============================================================================
// variables
//=============================================================================
/* Declare a FLASH config struct which initialized by FlashInit, and will be used by all flash operations */
STATIC_AL flash_ssd_config_t flashSSDConfig;

//=============================================================================
// Exported variables
//=============================================================================
STATIC_AL const flash_user_config_t Flash_InitConfig0 =
{
  .PFlashBase = 0x00000000U,       // Base address of Program Flash block
  .PFlashSize = 0x00040000U,         // Size of Program Flash block
  .DFlashBase = 0x10000000U,       // Base address of Data Flash block
  .EERAMBase  = 0x14000000U,       // Base address of FlexRAM block
  // If using callback, any code reachable from this function must not be placed in a Flash block targeted for a program/erase operation.
  .CallBack = NULL_CALLBACK         //PRQA S 305    //SDK requirement
};

#if (FEE_DEV_ERROR_DETECT == STD_ON)
  #define FEE_UNINITIALIZED 0
  #define FEE_INITIALIZED 1

  static uint8 Fee_ucInitStatus = FEE_UNINITIALIZED;
#endif


//=============================================================================
// prototypes
//=============================================================================


//-----------------------------------------------------------------------------
/// \brief  Initialization
///
/// \descr    invoke the function call to partitions the FlexNVM
///           invoke the function call to FlexRAM Configuration to store the EEPROM Data
///           Check if previous flash operation is done before any FlexRAM change
///
/// \param  - 
///
/// \return - 
//-----------------------------------------------------------------------------
  void Fee_Init(void)
  {

    (void)FLASH_DRV_Init(&Flash_InitConfig0, &flashSSDConfig);

#if ((FEATURE_FLS_HAS_FLEX_NVM == 1U) && (FEATURE_FLS_HAS_FLEX_RAM == 1U))  || defined(UNIT_TEST)
    /* Config FlexRAM as EEPROM if it is currently used as traditional RAM */
    if (flashSSDConfig.EEESize == 0u)
    {

      /* Configure FlexRAM as EEPROM and FlexNVM as EEPROM backup region,
           * DEFlashPartition will be failed if the IFR region isn't blank.
           * Refer to the device document for valid EEPROM Data Size Code
           * and FlexNVM Partition Code. For example on S32K146:
           *  EEEDataSizeCode = 0x02u: EEPROM size = 4 Kbytes
           *  DEPartitionCode = 0x08u: EEPROM backup size = 64 Kbytes */
      (void)FLASH_DRV_DEFlashPartition(&flashSSDConfig, 0x02u, 0x08u, 0x0u, false, true);

      /* Re-initialize the driver to update the new EEPROM configuration */
      (void)FLASH_DRV_Init(&Flash_InitConfig0, &flashSSDConfig);
      DEV_ASSERT(STATUS_SUCCESS == ret);

      /* Make FlexRAM available for EEPROM */
      (void)FLASH_DRV_SetFlexRamFunction(&flashSSDConfig, EEE_ENABLE, 0x00u, (flash_eeprom_status_t*)NULL);

      Fee_State = FEE_STATE_IDLE;
      Fee_t_Status = MEMIF_IDLE;
    }
    else
    {
      (void)FLASH_DRV_SetFlexRamFunction(&flashSSDConfig, EEE_ENABLE, 0x00u, (flash_eeprom_status_t*)NULL);
      Fee_State = FEE_STATE_IDLE;
      Fee_t_Status = MEMIF_IDLE;
    }
#endif /* (FEATURE_FLS_HAS_FLEX_NVM == 1u) & (FEATURE_FLS_HAS_FLEX_RAM == 1u) */

    flashSSDConfig.CallBack = NULL_CALLBACK;         //PRQA S 305    // null Callback function definition from nxp for fee operations
  }

//--------------------------------------------------------------------------------------------------------------
/// \brief  Fee_Read
///
/// \descr  This function shall take the block start address and offset and calculate the corresponding memory read address
///
/// \param  BlockNumber   : Number of logical block, which is the start address of that block in flash memory
/// \param  BlockOffset   : read address offset inside the block
/// \param  DataBufferPtr : pointer to data buffer
/// \param  Length        : number of bytes to read
///
/// \return Std_ReturnType
///           E_OK: The requested job has been accepted by the module.
///           E_NOT_OK: The requested job has not been accepted by the module
//---------------------------------------------------------------------------------------------------------------
  Std_ReturnType Fee_Read(uint16 BlockNumber,
                        uint16 BlockOffset,
                        uint8* DataBufferPtr,
                        uint16 Length)
{
  Std_ReturnType retValue = E_OK;
  uint16 unAddressOffset;
  uint16 unblockOffset;
  uint16 unIdx;
  uint16 unBlockSize;
  (void)Length;             // make QAC happy

  if (FEE_STATE_IDLE == Fee_State)
  {

      // Get index for blocknumber from FeeBlockTable array
      unIdx = Fee_LookUpIndex(BlockNumber);
      // Get Address offset for BlockNumber
      unAddressOffset = Fee_GetAddressOffset(BlockNumber);
      // Size of data to be written
      unBlockSize = FeeBlockTable[unIdx].unBlockSize;

      unblockOffset = BlockOffset;
      // Read from EEPROM
      if (Fee_EEERead(&flashSSDConfig, unAddressOffset, unBlockSize, DataBufferPtr) != E_OK)
      {
        Fee_State = FEE_STATE_IDLE;
        retValue = E_NOT_OK;
      }
      else
      {
       // Fee_JobResult = MEMIF_JOB_PENDING;
        Fee_JobResult = MEMIF_JOB_OK;
        Fee_State = FEE_STATE_READ;
      }

  }
  else
  {
    retValue = E_NOT_OK;
  }

  return retValue;

}



//-----------------------------------------------------------------------------
/// \brief  Fee_EEERead
///
/// \descr  EEPROM Emulated Read. Reads from FLexRAM which is partitioned as EEPROM use
///
/// \param  pSSDConfig  : configuration structure pointer
/// \param  ulAddress   : start address for the intended block to be read
/// \param  ulSize      : number of bytes to read
/// \param  pucData     : pointer to source address from which data has to be read
///
/// \return Std_ReturnType
///         E_OK     : operation was successful
///         E_NOT_OK : failure occured
//-----------------------------------------------------------------------------
STATIC_AL Std_ReturnType Fee_EEERead(const flash_ssd_config_t * pSSDConfig, uint32 ulAddress, uint32 ulSize, uint8 *pucData)
{
  // Variable used to store the return value of the function
  Std_ReturnType retValue = E_OK;
  tieFeeErr Fee_Error;

  // EEE address to read
  uint32 EEEAddress = flashSSDConfig.EERAMBase + (uint32)ulAddress;
  uint8 *EEEAddressPtr = (uint8 *)EEEAddress;           //PRQA S 306  // cast needed, working with actual addresses

  uint32 unReadIdx = ulSize;

  // Check if EEE is enabled
  if ((FTFC->FCNFG & (uint8)FTFC_FCNFG_EEERDY_MASK) == (uint8)FTFC_FCNFG_EEERDY_MASK)       //PRQA S 306  // correct usage for accessing fee registers
  {
    // Check for valid address
    if ((EEEAddress < pSSDConfig->EERAMBase) || ((EEEAddress + ulSize) > (pSSDConfig->EERAMBase + pSSDConfig->EEESize)))
    {
      Fee_Error = FEE_ERR_ADDRESS;
      retValue = E_NOT_OK;
    }
    else
    {
      Fee_Error = FEE_ERR_NO;
      retValue = E_OK;

      for (uint32 ulIx = 0u; ulIx < unReadIdx; ulIx++)
      {
        *pucData = *EEEAddressPtr;
        pucData++;
        EEEAddressPtr++;
      }

    }
  }
  else
  {
    Fee_Error = FEE_ERR_ERROR;
    retValue = E_NOT_OK;
  }

  return retValue;
}



//-----------------------------------------------------------------------------
/// \brief  Fee_WaitEEWriteToFinish
///
/// \descr  Write to EEPROM with data was aligned and wait until operation finish
///
/// \param  pSSDConfig  : configuration structure pointer
/// \param  ulAddress   : start address for the intended block to be read
/// \param  pucData     : pointer to data buffer
/// \param  ucStep      : memory alignment
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
STATIC_AL Std_ReturnType Fee_WaitEEWriteToFinish(const flash_ssd_config_t * pSSDConfig, uint32 ulAddress, const uint8 * pucData, uint8 ucStep)
{
  DEV_ASSERT(pucData != NULL);

  /* Return code variable */
  Std_ReturnType retValue = E_OK;
  tieFeeErr Fee_Error;

  uint32 ulTemp;                    /* Temporary variable   */

#if (FEATURE_FLS_IS_FTFM == 1U)
  ulTemp = *(volatile uint32_t *)ulAddress;

  switch (ucStep)
  {
  case 0x4U:
    ulTemp = (uint32_t)(pucData[3]) << 24U;
    ulTemp |= (uint32_t)(pucData[2]) << 16U;
    ulTemp |= (uint32_t)(pucData[1]) << 8U;
    ulTemp |= (uint32_t)(pucData[0]);
    break;
  case 0x1U:
    ulTemp = (ulTemp & 0xFFFFFF00U) | (uint32_t)(pucData[0]);
    break;
  case 0x2U:
    ulTemp = (ulTemp & 0xFFFF0000U) | ((uint32_t)(pucData[1]) << 8U);
    ulTemp |= (uint32_t)(pucData[0]);
    break;
  case 0x3U:
    ulTemp = (ulTemp & 0xFF000000U) | ((uint32_t)(pucData[2]) << 16U);
    ulTemp |= (uint32_t)(pucData[1]) << 8U;
    ulTemp |= (uint32_t)(pucData[0]);
    break;
  default:
    /* Undefined value */
    break;
  }

  *(volatile uint32_t *)ulAddress = ulTemp;
#else
  if (0x04U == ucStep)
  {
    ulTemp  = (uint32)(pucData[3]) << 24U;
    ulTemp |= (uint32)(pucData[2]) << 16U;
    ulTemp |= (uint32)(pucData[1]) << 8U;
    ulTemp |= (uint32)(pucData[0]);
    *(volatile uint32 *)ulAddress = ulTemp;                   //PRQA S 303      // cast needed, working with actual addresses
  }
  if (0x01U == ucStep)
  {
    *(uint8 *)ulAddress = *pucData;                             //PRQA S 306      // cast needed, working with actual addresses
  }
  if (0x02U == ucStep)
  {
    ulTemp = (uint32)(pucData[1]) << 8U;
    ulTemp |= (uint32)(pucData[0]);
    *(volatile uint16 *)ulAddress = (uint16)ulTemp;           //PRQA S 303      // cast needed, working with actual addresses
  }
#endif

#ifndef UNIT_TEST
  /* This section will not be included for unit test, because it tests microcontroller behaviour and it can be achieved only by changing implementation specific to UT.*/
  while (0U == (FTFx_FCNFG & FTFx_FCNFG_EEERDY_MASK))       //PRQA S 306  // correct usage for accessing fee registers
  {
    /* Wait till EEERDY bit is set
     * Serve callback function as often as possible
     */
    if (NULL_CALLBACK != pSSDConfig->CallBack)              //PRQA S 305    //PRQA S 307  // null Callback function definition from nxp for fee operations
    {
      (pSSDConfig->CallBack)();
    }

    /* Check for protection violation error */
    if (FTFx_FSTAT_ERROR_BITS != 0U)          //PRQA S 306  // correct usage for accessing fee registers
    {
      break;
    }

  }
#endif

  /* Check for protection violation error */
  if (FTFx_FSTAT_ERROR_BITS != 0U)            //PRQA S 306  // correct usage for accessing fee registers
  {
    retValue = E_NOT_OK;
  }

  return retValue;
}



//-----------------------------------------------------------------------------
/// \brief  Fee_EEEWrite
///
/// \descr
///
/// \param  pSSDConfig    : configuration structure pointer
/// \param  ulAddress     : start address for the intended block to write
/// \param  ulSize        : number of bytes to write
/// \param  pucData       : pointer to source address from which data has to be read
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
STATIC_AL Std_ReturnType Fee_EEEWrite(const flash_ssd_config_t * pSSDConfig,  uint32 ulAddress,  uint32 ulSize,  const uint8 * pucData)
{
  DEV_ASSERT(pSSDConfig != NULL);
  DEV_ASSERT(pucData != NULL);
  DEV_ASSERT(ulSize > 0U);
#if (FEATURE_FLS_IS_FTFM == 1U)
  DEV_ASSERT(0U == (ulAddress & 3U));
#endif
 /* Return code variable */
  Std_ReturnType retValue = E_OK;
  tieFeeErr Fee_Error;

  uint8 unIdx = 0U;

  /* Check if EEE is enabled */
  if ((FTFx_FCNFG & FTFx_FCNFG_EEERDY_MASK) == FTFx_FCNFG_EEERDY_MASK)          //PRQA S 306  // correct usage for accessing fee registers
  {
    /* Check range */
    if ((ulAddress < pSSDConfig->EERAMBase) || ((ulAddress + ulSize) > (pSSDConfig->EERAMBase + pSSDConfig->EEESize)))
    {
      Fee_Error = FEE_ERR_ADDRESS;
      retValue = E_NOT_OK;
    }

    while ((ulSize > 0U) && (retValue == E_OK))
    {
#if (FEATURE_FLS_IS_FTFM == 1U)
      if (ulSize >= 4U)
      {
        unIdx = 4U;
      }
      else
      {
        unIdx = size;
      }
#else
      /* destination is 32bit-aligned and size is not less than 4 */
      if ((0U == (ulAddress & 3U)) && (ulSize >= 4U))
      {
        unIdx = 4U;
      }
      else if ((0U == (ulAddress & 1U)) && (ulSize >= 2U))
      {
        unIdx = 2U;
      }
      else
      {
        unIdx = 1U;
      }
#endif

      retValue = Fee_WaitEEWriteToFinish(pSSDConfig, ulAddress, pucData, unIdx);
      /* Update destination address for next iteration */
      ulAddress += unIdx;
      /* Update size for next iteration */
      ulSize -= unIdx;
      /* Update data for next iteration */
      pucData += unIdx;
    }
  }
  else
  {
    retValue = E_NOT_OK;
  }

  return retValue;
}


//-----------------------------------------------------------------------------
/// \brief  Fee_write
///
/// \descr  This function shall take the block start address and offset and calculate the corresponding memory write address
///
/// \param  BlockNumber   : Number of logical block, which is the start address of that block in flash memory
/// \param  DataBufferPtr : pointer to data buffer
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------

Std_ReturnType Fee_Write(uint16 BlockNumber,
                         uint8* DataBufferPtr)
{
  uint16 unIdx;
  uint16 unBlockSize;
  uint16 unAddressOffset;

  // Variable used to store the return value of the function
  Std_ReturnType retValue = E_OK;

  if ((FEE_STATE_IDLE == Fee_State) || (FEE_STATE_WRITE == Fee_State))
  {
    
      // Get index for blocknumber from FeeBlockTable array
      unIdx = Fee_LookUpIndex(BlockNumber);
      // Get Address offset for BlockNumber
      unAddressOffset = Fee_GetAddressOffset(BlockNumber);
      // Size of data to be written
      unBlockSize = FeeBlockTable[unIdx].unBlockSize;

      // Write into EEPROM
      if (Fee_EEEWrite(&flashSSDConfig, flashSSDConfig.EERAMBase + unAddressOffset, unBlockSize, DataBufferPtr) != E_OK)
      {
        Fee_JobResult = MEMIF_JOB_FAILED;
        Fee_State = FEE_STATE_IDLE;
        retValue = E_NOT_OK;
      }
      else
      {
        Fee_JobResult = MEMIF_JOB_OK;
        //Fee_JobResult = MEMIF_JOB_PENDING;
        Fee_State = FEE_STATE_WRITE;
      }
 
  }
  else
  {
    retValue = E_NOT_OK;
  }

  return retValue;
}



//-----------------------------------------------------------------------------
/// \brief  Fee_GetStatus
///
/// \descr  Get status of the memory interface
///
/// \param  -
///
/// \return MemIf_StatusType
//-----------------------------------------------------------------------------
MemIf_StatusType Fee_GetStatus(void)
{

  MemIf_StatusType MemIfStatus;
  Std_ReturnType boState;

  /* Initialize the status as busy internal */
  MemIfStatus = MEMIF_BUSY_INTERNAL;

  /* Report DET error if the module is uninitialized */
#if (FEE_DEV_ERROR_DETECT == STD_ON)
  if (Fee_ucInitStatus != FEE_INITIALIZED)
  {
    /* Report Error to DET */
    //Fee_Det_ReportError(AlDet_ModId_Fee, FEE_INSTANCE_ID, FEE_INIT_SID, FEE_E_INIT_FAILED);
    Fee_Det_ReportError(AlDet_ModId_Fee, FEE_INSTANCE_ID, FEE_GETSTATUS_SID, FEE_E_UNINIT);
    /* Set status to MEMIF_UNINIT */
    MemIfStatus = MEMIF_UNINIT;
  }
  else
#endif
  {
    /* Invoke EEL_GetDriverStatus function to get driver status */
    boState= Fee_GetOpStatus();

    /* To report idle status, check if last operation completed and Fee itself is idle */
    if ( (boState == E_OK)  &&  (FEE_STATE_IDLE == Fee_State))
    {
      /* Set status to MEMIF_IDLE */
      MemIfStatus = MEMIF_IDLE;
    }

    /* Check if Fee is busy */
    else if (Fee_State != FEE_STATE_IDLE)
    {
      /* Check the Fee state to report the status as Idle when the driver
      * is busy due to ongoing request during cancel processing */
      //if (FEE_JOB_CANCELED == Fee_GstVar.GucState)
      //{
      //  /* Set status to MEMIF_IDLE */
      //  MemIfStatus = MEMIF_IDLE;
      //}
      //else
      {
        /* Set status to MEMIF_BUSY */
        MemIfStatus = MEMIF_BUSY;
      }
    }
    else
    {
      /* To avoid MISRA warnings */
    }
  }
  return(MemIfStatus);

}

//-----------------------------------------------------------------------------
/// \brief  Fee_SetMode
///
/// \descr
///
/// \param  Mode  : desired mode for underlying module
///
/// \return void
//-----------------------------------------------------------------------------
void Fee_SetMode(MemIf_ModeType Mode)
{
  (void)Mode;
}


//-----------------------------------------------------------------------------
/// \brief  Fee_GetJobResult
///
/// \descr  return the status of the requested job
///
/// \param  -
///
/// \return MemIf_JobResultType
//-----------------------------------------------------------------------------
MemIf_JobResultType Fee_GetJobResult(void)
{
  return Fee_JobResult;
}

//-----------------------------------------------------------------------------
/// \brief  Fee_InvalidateBlock
///
/// \descr  inavlidates the requested block
///
/// \param  BlockNumber : Number of logical block, which is the start address of that block in flash memory
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Fee_InvalidateBlock(uint16 BlockNumber)
{
  (void) BlockNumber;

  return (Std_ReturnType) 0U;
}

//-----------------------------------------------------------------------------
/// \brief  Fee_EraseImmediateBlock
///
/// \descr  erases the requested block
///
/// \param  BlockNumber : Number of logical block, which is the start address of that block in flash memory
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Fee_EraseImmediateBlock(uint16 BlockNumber)
{
  (void) BlockNumber;

  return (Std_ReturnType) 0U;
}




//-----------------------------------------------------------------------------
/// \brief  Fee_MainFunction
///
/// \descr
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void Fee_MainFunction(void)
{
  Std_ReturnType boStatus;

  boStatus = Fee_GetOpStatus();

  if  ( boStatus == E_OK)
  {
    FeeStateMachine(Fee_State);
  }
}



//-----------------------------------------------------------------------------
/// \brief    Fee_GetOpStatus
///
/// \descr    This function checks the status of the flash memory
///
/// \param  -
///
/// \return Std_ReturnType
///           E_OK : previous operation has completed
///           E_NOT_OK: an operation is ongoing
//-----------------------------------------------------------------------------
Std_ReturnType Fee_GetOpStatus(void)
{
  Std_ReturnType boState;

  uint8 unFStat = FTFC->FSTAT;          //PRQA S 306  // correct usage for accessing fee registers
  uint8 unFCnfg = FTFC->FCNFG;          //PRQA S 306  // correct usage for accessing fee registers

  //read complete interrupt flag
  if (((unFStat & (uint8_t)FTFC_FSTAT_CCIF_MASK) == 0U) ||
      ((unFCnfg & (uint8_t)FTFC_FCNFG_EEERDY_MASK) == 0U))
  {
    boState = E_NOT_OK;
  }
  else
  {
    boState = E_OK;
  }

  return boState;

}


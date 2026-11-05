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
/// \file  SysCrc.c
///
/// \brief SysCrc Driver Source File
///
/// \author Cruciu Denis-Mihai (F31196D)
///         mailTo: denis-mihai.cruciu[at]marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// Include files
//=============================================================================
#include <SysCrc.h>
#include <CddDma.h>
#include <UtilUtility.h>
#include <SysCrc_Cfg.h>

#if defined (CPU_S32K142)
  #include <S32K142.h>
#elif defined (CPU_S32K144)
  #include <S32K144.h>
#elif defined (CPU_S32K146)
  #include <S32K146.h>
#endif

#if defined UNIT_TEST
  #include<SysCrc_reg_stubs.h>
  #include <RteCommonTypes.h>
#else
  #include <crc_hw_access.h>
  #include <Rte.h>
#endif
// PRQA S 306 EOF // Intended cast

//=============================================================================
// Defines
//=============================================================================
// to reset the final XOR of the HW-Autosar-CRC32 interface
#define SYS_CRC_ALLTIME_XOR_VALUE_REVERSE (0xFFFFFFFFu) 

//Invalid Checksum values 
#define SYS_CRC_INVALID_CHECKSUM_VALLUE_1 0x00000000u
#define SYS_CRC_INVALID_CHECKSUM_VALLUE_2 0xA000F7F0u
#define SYS_CRC_INVALID_CHECKSUM_VALLUE_3 0xFFFFFFFFu

//Maximum Dma Transfer Size(in bytes) per every transfer
#define SYS_CRC_MAX_DMA_TRANSFER_SIZE 0x1FEU

//=============================================================================
// Private variables
//=============================================================================
// the current segment
STATIC_AL uint8  SysCrc_ucRomSegmentIdx; 

// due to stored CRC (=0xFFF...) this ROM is NOT flashed via 'S19'-File BUT via an 'ELF'-File
STATIC_AL boolean  SysCrc_ucProbablyElfFile;

// Stores segments config
STATIC_AL CONST_AL tsSysCrc_SegmentConfig SysCrc_RomSegs_RomSegs[eSegmentsCount] = SYS_CRC_ROM_SEGMENTS; // PRQA S 1840 1 //  The behavior is as expected; no side effect

// Ecu calculated CRC
STATIC_AL uint32 SysCrc_RomSegs_ulRegCalcCRC[eSegmentsCount];
// Stores CRC status
STATIC_AL boolean SysCrc_RomSegs_boCrcStatus[eSegmentsCount];

//semaphore to check if the CRC calculation started
STATIC_AL boolean SysCrc_boCRCCalcStarted = FALSE;
//semaphore to check if the CRC calculation is finish
STATIC_AL boolean SysCrc_boCRCCalcFinished = FALSE;
//// will be initialized with the start memory address for every segment
STATIC_AL uint32  SysCrc_ulRomAddress = 0u;
// will be initialized with the memory length with every new CRC request
STATIC_AL uint32  SysCrc_ulRomLength = 0u;

STATIC_AL boolean SysCrc_boCalibCrcStatus     = FALSE;
STATIC_AL boolean SysCrc_boCalibCrcCheckInit  = FALSE;
//=============================================================================
// Private types
//=============================================================================

//=============================================================================
// Private functions
//=============================================================================
STATIC_AL void     SysCrc_RomSegs_InitCRC(void);
STATIC_AL boolean  SysCrc_RomSegs_DoCRCSegment(uint8 ucSegment);
STATIC_AL void     SysCrc_RomSegs_CheckCrc(void);
STATIC_AL uint32   SysCrc_RomSegs_CatchCrc(void);
STATIC_AL boolean  SysCrc_RomSegs_Crc32_Vector_AUTOSAR(const uint32 ulCrc_StartAddressVal, const uint32 ulLength, uint32 * pulResult);
STATIC_AL void     SysCrc_Dma_Transfer(uint32* pulSourceAdress,uint32* pulTargetAdress, uint16 unLen);

STATIC_AL void     SysCrc_RomSegs_CallbackFunction(tSysCrc_pFnct pFct);
STATIC_AL void     SysCrc_DmaNotification(void);


//=============================================================================
//  Functions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  SysCrc_RomSegs_GetCalibCrcStatus
///
/// \descr  Get CRC status for CAL data segment
///
/// \param  void
///
/// \return CRC check status: TRUE = failure; FALSE = success
//-----------------------------------------------------------------------------
boolean SysCrc_RomSegs_GetCalibCrcStatus(void)
{
  return SysCrc_RomSegs_boCrcStatus[eCalibrationSegment];
}

//-----------------------------------------------------------------------------
/// \brief  SysCrc_RomSegs_CallbackFunction
///
/// \descr  Function executes valid callback pointers
///
/// \param  pFct - function pointer
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysCrc_RomSegs_CallbackFunction(tSysCrc_pFnct pFct)
{
  // Check if callback function is defined
  if (NULL_PTR != pFct)
  {
    // Execute callback function
    pFct();
  }
  else
  {
    // Invalid pointer function
  }
}

//-----------------------------------------------------------------------------
/// \brief  SysCrc_RomSegs_Init
///
/// \descr  Perform CRC check for CAL data at init and
///         report CRC failure if CRC is not correct.
///
/// \param   ConfigPtr Configuration input data for SysCrc driver
///
/// \return void
//-----------------------------------------------------------------------------
void SysCrc_RomSegs_Init(const SysCrc_ConfigType* ConfigPtr)
{
  (void)CRC_DRV_Init(INST_SYSCRC, (crc_user_config_t*)ConfigPtr->SysCrc_cfg);  // PRQA S 316 2 // Intended cast
  SysCrc_RomSegs_SegmentCrcCheck(eCalibrationSegment);

  if ((SysCrc_RomSegs_boCrcStatus[eCalibrationSegment] != TRUE))
  {
    // No CRC failure
      Rte_Call_DemPrj_ReportErrorStatus((uint16)SysCrc_RomSegs_RomSegs[eCalibrationSegment].SysCrc_unDtc, DEM_EVENT_STATUS_PASSED);
  }
  else
  {
    // Report CRC failure
      Rte_Call_DemPrj_ReportErrorStatus((uint16)SysCrc_RomSegs_RomSegs[eCalibrationSegment].SysCrc_unDtc, DEM_EVENT_STATUS_FAILED);

    SysCrc_RomSegs_CallbackFunction(SysCrc_RomSegs_RomSegs[eCalibrationSegment].SysCrc_pfnCrcFailure);
  }
  
  // Initialize the cyclic calculation of CRC
  SysCrc_RomSegs_InitCRC();

  // CRC State Init Done
  SysCrc_boCalibCrcCheckInit = TRUE;
}

// ---------------------------------------------------------------------------
/// \brief  Initialize the calculation of the CRC32.
///
/// \descr  This function has to be called once before calling SysCrc_RomSegs_DoCRC
///
/// \param  - 
///
/// \return void 
// ---------------------------------------------------------------------------
STATIC_AL void SysCrc_RomSegs_InitCRC(void)
{ 
  SysCrc_ucRomSegmentIdx = 0u;
  SysCrc_RomSegs_ulRegCalcCRC[SysCrc_ucRomSegmentIdx] = 0u;
}

// ---------------------------------------------------------------------------
/// 
/// \brief  Organizes the CRC32 calculation
///
/// \descr  This function calls the function 'SysCrc_RomSegs_DoCRCSegment'.
///         If the function SysCrc_RomSegs_DoCRCSegment is done with the calculation of one segment,
///         the function SysCrc_RomSegs_DoCRC checks if there are other segments for calculation defined. 
///
/// 
/// \param  - 
///
/// \return void 
// ---------------------------------------------------------------------------
void SysCrc_RomSegs_DoCRC(void)
{
  // calc CRC of current segment and check if current segment is ready?
  if (SysCrc_RomSegs_DoCRCSegment(SysCrc_ucRomSegmentIdx) != FALSE)
  {
    // calc CRC of current segment is ready
    SysCrc_RomSegs_CheckCrc();
    // reset for next CRC-Calculation...:
    //SysCrc_RomSegs_ulRegCalcCRC[SysCrc_ucRomSegmentIdx] = 0u;
    // take the next segment (n.b.: ...'uint8')
    SysCrc_ucRomSegmentIdx++;
    // NOT ready checking all segments?
    if (SysCrc_ucRomSegmentIdx >= countof(SysCrc_RomSegs_RomSegs))
    {
      // restart all the checking again and again
      SysCrc_ucRomSegmentIdx = 0u;
    }
    else
    {
      // keep going
    }
  }
  else
  {
    // CRC on this segment is not ready
  }
}

// ---------------------------------------------------------------------------
/// 
/// \brief  Calculates a CRC32 for a defined segment.
///
/// \descr  This function checks the length of a segment part. This segment part
///         is passed to the BSWMD Crc function Crc_CalculateCRC32
///
/// \param  ucSegment The actual segment that the CRC32 is to be calculated on.
///
/// \return TRUE if the segment has been finished this time, FALSE otherwise.
// ---------------------------------------------------------------------------
STATIC_AL boolean SysCrc_RomSegs_DoCRCSegment(uint8 ucSegment)
{
  uint32 udFinal = SysCrc_RomSegs_RomSegs[ucSegment].SysCrc_ulStartAddrOfSegment + SysCrc_RomSegs_RomSegs[ucSegment].SysCrc_ulSizeOfSegment;
  boolean boRetValue = FALSE;
  uint32 ulCrcResult;

  // PRQA S 306 1     // program architecture and readability, conversion is possible for 32 bit micros (or less)
  boRetValue = SysCrc_RomSegs_Crc32_Vector_AUTOSAR(SysCrc_RomSegs_RomSegs[ucSegment].SysCrc_ulStartAddrOfSegment,SysCrc_RomSegs_RomSegs[ucSegment].SysCrc_ulSizeOfSegment,&ulCrcResult);

  //check if the CRC is finish
  if (boRetValue == TRUE)
  {
     SysCrc_RomSegs_ulRegCalcCRC[SysCrc_ucRomSegmentIdx] = ulCrcResult;
  }
  //trigger the DMA using pooling
  if (CddDma_IsJobCompleted(SYS_CRC) == TRUE)
  {
    SysCrc_DmaNotification();
  }

  return boRetValue; 
}

// ---------------------------------------------------------------------------
/// \brief  Calculates and check CRC32 for a defined segment.
///
/// \descr  This function checks the length of a segment part. This segment part
///         is passed to the BSWMD Crc function Crc_CalculateCRC32
///
/// \param  eSegId - The Id of the segment that the CRC32 is to be calculated on.
///
/// \return void
// ---------------------------------------------------------------------------
void SysCrc_RomSegs_SegmentCrcCheck(teSysCrc_SegmentId eSegId)
{
  uint32 ulCrcResult = 0u;
  uint32 ulTimeOut = 4800000U;
  uint32 ulIndex = 0U;
  boolean boRetValue = FALSE;

  // PRQA S 306 1     // intended cast to obtain the CRC value from the corresponding memory address 
  uint32 ulRomCrc = *((uint32*)SysCrc_RomSegs_RomSegs[eSegId].SysCrc_ulRomCalcCRC);

  (void)SysCrc_RomSegs_Crc32_Vector_AUTOSAR(SysCrc_RomSegs_RomSegs[eSegId].SysCrc_ulStartAddrOfSegment,SysCrc_RomSegs_RomSegs[eSegId].SysCrc_ulSizeOfSegment,&ulCrcResult);
 
  while (ulIndex++ < ulTimeOut)
  {
	  if (CddDma_IsJobCompleted(SYS_CRC) == TRUE)
	  {
		  SysCrc_DmaNotification();
	  }
	  if (SysCrc_boCRCCalcFinished == TRUE)
	  {
		  //Get the CRC result
		  ulCrcResult = CRC_DRV_GetCrcResult(INST_SYSCRC);
		  // reset interrupt semaphore
		  SysCrc_boCRCCalcFinished = FALSE;
		  // reset application semaphore
		  SysCrc_boCRCCalcStarted = FALSE;
		  // initialize the CRC seed value
		  CRC_SetSeedReg(CRC, SYS_CRC_INITIAL_SEED_VALUE);
		  break;
	  }
  }

  // Get CRC stored in ROM
  if (SysCrc_RomSegs_RomSegs[eSegId].SysCrc_boSwapCrc != FALSE)
  {
    // Swap MSB/LSB
    // PRQA S 4397 1  // Casts ok inside UTIL_SWAPLONG macro
    ulRomCrc = UTIL_SWAPLONG(ulRomCrc);
  }
  else
  {
    // Swap is not required from configuration file
  }

  // Mainly for debugging and after flashing 'elf'-files 
  if ((ulRomCrc == SYS_CRC_INVALID_CHECKSUM_VALLUE_1) ||
      (ulRomCrc == SYS_CRC_INVALID_CHECKSUM_VALLUE_2) ||
      (ulRomCrc == SYS_CRC_INVALID_CHECKSUM_VALLUE_3))
  {
    // ... due to stored CRC (=0xFFF...) this ROM is NOT flashed via 'S19'-File BUT via an 'ELF'-File
  }
  else
  {
    // Flashed via S19 file
    // Check if calculated CRC is equal with CRC stored in ROM
    if (ulCrcResult != ulRomCrc)
    {
      // CRC failure
      SysCrc_RomSegs_boCrcStatus[eSegId] = TRUE;
      // Report CRC failure
      Rte_Call_DemPrj_ReportErrorStatus(SysCrc_RomSegs_RomSegs[eSegId].SysCrc_unDtc, DEM_EVENT_STATUS_FAILED);
    }
    else
    {
      // No CRC failure
      SysCrc_RomSegs_boCrcStatus[eSegId] = FALSE;
      Rte_Call_DemPrj_ReportErrorStatus(SysCrc_RomSegs_RomSegs[eSegId].SysCrc_unDtc, DEM_EVENT_STATUS_PASSED);
    }
  }
}

// ---------------------------------------------------------------------------
/// 
/// \brief  Compares the calculated CRC32 value to a value calculated before 
///         flashing by ALHexManip and is the interface to DemPrj
///
/// \descr  Do set a DEM- Event-Status depending on the current calculation
///
/// \param  - 
///
/// \return void 
//-----------------------------------------------------------------------------
STATIC_AL void SysCrc_RomSegs_CheckCrc(void)
{
  uint32 ulRomCrc;
  
  // Get value of the CRC stored in ROM
  ulRomCrc = SysCrc_RomSegs_CatchCrc();

  // Due to stored CRC (=0xFFF...) this ROM is NOT flashed via 'S19'-File BUT via an 'ELF'-File
  if (SysCrc_ucProbablyElfFile == FALSE)
  // i.e.: No CRC-DTC if current ROM seems to be from an 'ELF'-File
  {
    // equal? (calc & stored)
    // PRQA S 306 1 // need to get value of ROM-Address
    if (SysCrc_RomSegs_ulRegCalcCRC[SysCrc_ucRomSegmentIdx] == ulRomCrc)
    {
      // No CRC failure
        Rte_Call_DemPrj_ReportErrorStatus(SysCrc_RomSegs_RomSegs[SysCrc_ucRomSegmentIdx].SysCrc_unDtc, DEM_EVENT_STATUS_PASSED);
    }
    else
    {
      // Report CRC failure
        Rte_Call_DemPrj_ReportErrorStatus(SysCrc_RomSegs_RomSegs[SysCrc_ucRomSegmentIdx].SysCrc_unDtc, DEM_EVENT_STATUS_FAILED);
      SysCrc_RomSegs_CallbackFunction(SysCrc_RomSegs_RomSegs[SysCrc_ucRomSegmentIdx].SysCrc_pfnCrcFailure);
    }
  }
  else
  {
    // ROM probably flshed via 'ELF'-file
  }
}

// ---------------------------------------------------------------------------
/// \brief  SysCrc_RomSegs_CatchCrc
///
/// \descr  Reads out the calculated CRC value from ROM, puts the
///         bytes in the right order and returns this CRC.
/// 
/// \param  - 
///
/// \return Calculated CRC from ROM 
// ---------------------------------------------------------------------------
STATIC_AL uint32 SysCrc_RomSegs_CatchCrc(void)
{
  uint32 ulRomCrc;
  SysCrc_ucProbablyElfFile = FALSE;
  // PRQA S 306 1 // need to get value of ROM-Address
  ulRomCrc = *((uint32*)SysCrc_RomSegs_RomSegs[SysCrc_ucRomSegmentIdx].SysCrc_ulRomCalcCRC);

  // swap MSB/LSB
  if (SysCrc_RomSegs_RomSegs[SysCrc_ucRomSegmentIdx].SysCrc_boSwapCrc != FALSE)
  {
    // PRQA S 4397 1  // Casts ok inside UTIL_SWAPLONG macro
    ulRomCrc = UTIL_SWAPLONG(ulRomCrc);
  }
  else
  {
    // Swap is not required from configuration file
  }

  // mainly for debugging and after flashing 'elf'-files ...:
  if ((ulRomCrc == SYS_CRC_INVALID_CHECKSUM_VALLUE_1) ||
      (ulRomCrc == SYS_CRC_INVALID_CHECKSUM_VALLUE_2) ||
      (ulRomCrc == SYS_CRC_INVALID_CHECKSUM_VALLUE_3))
  {
    // ... due to stored CRC (=0xFFF...) this ROM is NOT flashed via 'S19'-File BUT via an 'ELF'-File
    SysCrc_ucProbablyElfFile = TRUE;
  }
  else
  {
    SysCrc_ucProbablyElfFile = FALSE;
  }

  return ulRomCrc;
}

//-----------------------------------------------------------------------------
/// \brief SysCrc_Dma_Transfer
///
/// \descr In this function the DMA feeds the CRC register with data
///
/// \param  pulSourceAdress
/// \param  pulTargetAdress
/// \param  unLen
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void SysCrc_Dma_Transfer(uint32* pulSourceAdress,uint32* pulTargetAdress, uint16 unLen)
{
  tsCddDma_Parameter sCddDmaConfigRX = 
  { 
    .pulSourceAddress = pulSourceAdress, //start adress
    .pulTargetAddress = pulTargetAdress, //register adress
    .unRepetitions = unLen // Transfer data size for each DMA transfer
  };

  //Start transfer for RX channel
  CddDma_StartJob((SYS_CRC), &sCddDmaConfigRX, NULL_PTR);

}



//-----------------------------------------------------------------------------
/// \brief SysCrc_RomSegs_Crc32_Vector_AUTOSAR
///
/// \descr Calculate the CRC via Hardware
///
/// \param  ulCrc_StartAddressVal
/// \param  ulLength
/// \param  ulResult
///
/// \return  uint32
//-----------------------------------------------------------------------------
STATIC_AL boolean SysCrc_RomSegs_Crc32_Vector_AUTOSAR(const uint32 ulCrc_StartAddressVal, const uint32 ulLength, uint32 * pulResult)
{
  boolean boRet = FALSE;

  if (SysCrc_boCRCCalcFinished == TRUE)  // CRC calculation is ready, collect results
  {
    (*pulResult) = CRC_DRV_GetCrcResult(INST_SYSCRC);
    // reset interrupt semaphore
    SysCrc_boCRCCalcFinished = FALSE;
    // reset application semaphore
    SysCrc_boCRCCalcStarted = FALSE;
    // exit function positive 
    boRet = TRUE;
    // initialize the CRC seed value
    CRC_SetSeedReg(CRC, SYS_CRC_INITIAL_SEED_VALUE);
  }
  else if (SysCrc_boCRCCalcStarted == FALSE)
  {
    SysCrc_boCRCCalcStarted = TRUE;
    SysCrc_ulRomAddress = ulCrc_StartAddressVal;
    SysCrc_ulRomLength = ulLength;
    if(SysCrc_ulRomLength > SYS_CRC_MAX_DMA_TRANSFER_SIZE)
    {
      SysCrc_Dma_Transfer((uint32*)SysCrc_ulRomAddress,(uint32*)CRC_BASE, SYS_CRC_MAX_DMA_TRANSFER_SIZE); 
    }
    else
    {
      SysCrc_Dma_Transfer((uint32*)SysCrc_ulRomAddress,(uint32*)CRC_BASE, (uint16)SysCrc_ulRomLength);
    }
  }
  else
  {
    //do nothing
  }

  return boRet;
}


//-----------------------------------------------------------------------------
/// \brief SysCrc_DmaNotification
///
/// \descr DMA interrupt body for CRC calculation initial DMA job start is called 
///        on a cycle task every interrupt will increment the segment address and 
///        decrement the data length until all blocks are passed through CRC 
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysCrc_DmaNotification(void)
{
 if(SysCrc_ulRomLength > 0u) // if there is data to be calculated
  {  
   SysCrc_ulRomLength -= SYS_CRC_MAX_DMA_TRANSFER_SIZE;
   SysCrc_ulRomAddress += SYS_CRC_MAX_DMA_TRANSFER_SIZE;
    // check if there is still data to be passed to CRC  
    if( SysCrc_ulRomLength > SYS_CRC_MAX_DMA_TRANSFER_SIZE) // last block not yet reached 
    {
      SysCrc_Dma_Transfer((uint32*)SysCrc_ulRomAddress,(uint32*)CRC_BASE, SYS_CRC_MAX_DMA_TRANSFER_SIZE);
    }
    else //last block will be sent to DMA, interrupt semaphore for stopping is activated 
    {
      SysCrc_Dma_Transfer((uint32*)SysCrc_ulRomAddress,(uint32*)CRC_BASE, (uint16)SysCrc_ulRomLength);
      //next interrupt shall confirm the finish of CRC calculation by checking 0 data to be transfered
      SysCrc_ulRomLength = 0u; 
    }
  }
  else // this is the interrupt call of last block calculation
  {
    // this semaphore shall be set to FALSE before to start a new CRC calculation job
    SysCrc_boCRCCalcFinished = TRUE;
  }
}

//-----------------------------------------------------------------------------
/// \brief SysCrc_RomSegs_RomSegCalCbStatus
///
/// \descr
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void SysCrc_RomSegs_RomSegCalCbStatus(void) 
{
  // Crc calib state
  SysCrc_boCalibCrcStatus = TRUE;
}


//-----------------------------------------------------------------------------
/// \brief SysCrc_RomSegs_GetCalibState
///
/// \descr
///
/// \param  psCalibState
///
/// \return void
//-----------------------------------------------------------------------------
void SysCrc_RomSegs_GetCalibState(tsSysCrc_CalibGetStatus *psCalibState)
{
  // Map the crc init status
  psCalibState->boCalibCheckInitStatus = SysCrc_boCalibCrcCheckInit;
  // Map the crc actual state
  psCalibState->boCalibFailStatus      = SysCrc_boCalibCrcStatus;
}

// EOF

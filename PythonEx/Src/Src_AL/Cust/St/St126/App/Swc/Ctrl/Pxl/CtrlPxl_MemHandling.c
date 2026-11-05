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
/// \file   CtrlPxl_MemHandling.c
///
/// \brief  CtrlPxlMemHandling for EEProm and NVM
///
/// \descr  This file contains the handling of EEPROM and Nvm for access and
///         usage of data
///
/// \author Ionut Caba  ALRO-CJ (F37899C)
///         mailTo:ionut-stefan.caba[at]marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// header files
//=============================================================================
//TODO GEN3: #include <Cfg/CddMlc_Cfg.h>
#include "CtrlPxl_MemHandling.h"
#include "CtrlPxl_RteAccess.h"
#include <Crc.h>
#include "CtrlPxl_DataInterfaces.h"

//=============================================================================
// defines
//=============================================================================
#define CTRL_PXL_MEM_HANDLING_EEPROM_ACCESS                     (TRUE)  //used for setting DTC and reaction for EEProm
#define CTRL_PXL_MEM_HANDLING_NVM_ACCESS                        (FALSE) //used for setting DTC and reaction for NVM

//=============================================================================
// variables
//=============================================================================
  //CRC8-SAE_J1850
STATIC_AL uint8 CtrlPxl_CRC8_Eeprom = 0xFF;
STATIC_AL uint8 CtrlPxl_CRC8_Nvm    = 0xFF;

//extern tsCtrlPxl_InternalHandling CtrlPxl_sInternalHandling;
//=============================================================================
// function prototypes
//=============================================================================
STATIC_AL void CtrlPxl_HandleEEPromData(void);
STATIC_AL void CtrlPxl_MatrixEEClbkInit_Fail(void);
STATIC_AL void CtrlPxl_MatrixEEClbkInit_Success(void);
STATIC_AL void CtrlPxl_CompareEEPromAndNvmData(void);
STATIC_AL void CtrlPxl_AccessCalibDataAndCopy(uint8* pucDataBuff);
STATIC_AL void CtrlPxl_CheckBrightness(uint8 *pucDataBuff);


//=============================================================================
// functions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_ProcessMatrixEEPROM
///
/// \descr  The function calls the EEPROM State MAchine cyclic
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlPxl_ProcessMatrixEEPROM(void)
{
  //get the internal handling state
  tsCtrlPxl_InternalHandling *psCtrlPxl_InternalHandling = CtrlPxl_GetInternalHandlingStruct();

  //check if EEPROM can be used
  if (psCtrlPxl_InternalHandling->sEepromHandling.sEepromControl.boMatrixEEPromInitHandlingReady == TRUE)
  {
    //EEPROM shall be read just once, after that this flag should be true to avoid reading again EEPROM. Now, only diag is allowed
    //diagnostic mode can be used because EEProm was checked
  }
  else
  {
    // follow the state machine for EEPROM
    CtrlPxl_HandleEEPromData();
  }
}

//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_HandleEEPromData
///
/// \descr  The function implements a state machine for EEProm where it compares
///         CRC from Nvm with CRC from EEProm when data was accessed for validity.
///
/// \param  -
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlPxl_HandleEEPromData(void)
{
  //Variable for writing the EEPROM Job state on RTE for diag mode
  teEEPRom_Jobs eEEPromJobState = eEEProm_Job_Initial;
  tsCtrlPxl_InternalHandling *psCtrlPxl_InternalHandling = CtrlPxl_GetInternalHandlingStruct();

  //EEPROM State Machine
  switch (psCtrlPxl_InternalHandling->sEepromHandling.sEepromControl.eEEPromStates)
  {
    case eEEProm_Init:
      // Nvm has been checked -> proceed to initialize the EEPROM
      CtrlPxl_RteAccess_MatrixEE_Init(CtrlPxl_MatrixEEClbkInit_Success, CtrlPxl_MatrixEEClbkInit_Fail);
      break;

    case eEEProm_Read:
      //read entire data from EEPROM
      CtrlPxl_RteAccess_ReadEntireMatrixData(CTRL_PXL_MEM_HANDLING_EEPROM_ACCESS, CTRLPXL_EEPROM_MAPPING_BYTES);

      break;

    case eEEProm_Write:
      break;

    case eEEProm_CompareCRC:
      psCtrlPxl_InternalHandling->sEepromHandling.sEepromControl.eEEPromStates = eEEProm_Finished;

      //save CRC read from EEPROM (previously read)
      CtrlPxl_CRC8_Eeprom = CTRLPXL_EEPROM_MAPPING_FIELDS.CrcPatternAndReservedGroup.sCrcPatterAndReserved.ucCrc;

      //check validity of CRC value from EEProm and check if CRC from NVM and EEProm match
       CtrlPxl_CompareEEPromAndNvmData();
      break;

    case eEEProm_Wait:
        // waiting for a callback
      break;

    case eEEProm_Finished:
      // in this phase, diagnosis is allowed to use EEPROM
      psCtrlPxl_InternalHandling->sEepromHandling.sEepromControl.boMatrixEEPromInitHandlingReady = TRUE;

      //inform diagnosis that EEPROM is ready
      //write Eeprom ready for diagnostic - TODO
      
      //set on RTE the job state - tbd check if needed
      //CtrlPxlRteAccess_SetEEPromJob(eEEPromJobState);

      break;

    default:
      break;
  }

  //write RTE port with EEPROM status
  CTRLPXL_RTE_SE_EEPROM_ERR_STATUS(psCtrlPxl_InternalHandling->sEepromHandling.sEepromControl.boEepromChecksumFaultStatus, psCtrlPxl_InternalHandling->sEepromHandling.sEepromControl.boEepromAccessFaultStatus);//add one param for wrong checksum
}

//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_ReadAndCheckNvMMatrixData
///
/// \descr   This function access data from Nvm, and in case of error maximum brighntess 
///          values will be used until eeprom data will be read 
///
/// \param  -void
///
/// \return   void
//-----------------------------------------------------------------------------
void CtrlPxl_ReadAndCheckNvMMatrixData(void)
{
  boolean boBinningClassValid = FALSE;
  uint32  ulSizeOfData = 0u;
  uint8   ucCrcCalculated = 0u;

  tsCtrlPxl_InternalHandling *psCtrlPxl_InternalHandling = CtrlPxl_GetInternalHandlingStruct();

  //diagnostic control cannot use EEProm until the handling will be done (include initialization, reading and checking data)
  psCtrlPxl_InternalHandling->sEepromHandling.sEepromControl.boMatrixEEPromInitHandlingReady = FALSE;

  //write eeprom status to diagnosis
  //TBD- create port

  // read entire memory
  CtrlPxl_RteAccess_ReadEntireMatrixData(CTRL_PXL_MEM_HANDLING_NVM_ACCESS, CTRLPXL_EEPROM_MAPPING_BYTES);  //-> call either MLC read or Nvm read

  //read CRC from NVM  (CRC from NVM is the CRC calculated over EEPROM data) 
  CtrlPxl_CRC8_Nvm = psCtrlPxl_InternalHandling->sEepromHandling.sMtxEEPromMapping.uMtxEEPromMapping.MatrixParam_Data.CrcPatternAndReservedGroup.sCrcPatterAndReserved.ucCrc;

  ucCrcCalculated = Crc_CalculateCRC8H1D((const uint8*)&NvmBlockMatrixEEPromContent.Data[CTRL_PXL_EEPROM_CRC_OFFSET], (CTRL_PXL_EEPROM_SIZE - CTRL_PXL_EEPROM_CRC_OFFSET), CRC_SEED_INIT_CRC8H2F_VAL); //- do we need it???

  if ((CtrlPxl_CRC8_Nvm == ucCrcCalculated) && ((CtrlPxl_CRC8_Nvm != 0u)  || (ucCrcCalculated != 0u)) )
  {
    boBinningClassValid = TRUE;
    // copy brightness value from Nvm in CTRLPXL_NVM_BRIGHTNESS.ucBrightness
    CtrlPxl_AccessCalibDataAndCopy(CTRLPXL_EEPROM_MAPPING_FIELDS.LMMBrightnessAndReservedGroup.Data);
    //copy binning class into calibration struct control
    UtilMemCopy(&CTRLPXL_NVM_BINNING[0], CTRLPXL_EEPROM_MAPPING_FIELDS.LedChannelBCAndReservedGroup.Data, CTRL_PXL_NUMBER_OF_EEPROM_BINNING_CLASS);

  }
  else
  {
    //CRC value is invalid or eeprom is empty -> set maximum brightness 
    for (uint8 ucBCIdx = 0u; ucBCIdx < CTRL_PXL_NUMBER_OF_EEPROM_BRIGHTNESS; ucBCIdx++)
    {
      CTRLPXL_NVM_BRIGHTNESS[ucBCIdx] = CTRL_PXL_BRIGHTNESS_FACTOR;
    }

    for (uint8 ucBinIdx = 0u; ucBinIdx < CTRL_PXL_NUMBER_OF_EEPROM_BINNING_CLASS; ucBinIdx++)
    {
      CTRLPXL_NVM_BINNING[ucBinIdx] = CTRL_PXL_CFG_BINNING_CLASS_0;
    }

    boBinningClassValid = FALSE;
  }
  
  //write the port with binning class and quality signal used in selection of current value
  CtrlPxl_RteAccess_WriteBinningClass(boBinningClassValid, CTRLPXL_NVM_BINNING);

   //go to Init state from EEProm
  psCtrlPxl_InternalHandling->sEepromHandling.sEepromControl.eEEPromStates = eEEProm_Init;

}

//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_MatrixEEClbkInit_Fail
///
/// \descr  callback function called when init of eeprom has failed
///
/// \param  void
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlPxl_MatrixEEClbkInit_Fail(void)
{
  tsCtrlPxl_InternalHandling *psCtrlPxl_InternalHandling = CtrlPxl_GetInternalHandlingStruct();
  //go to Finished state, eeprom can't be handled
  psCtrlPxl_InternalHandling->sEepromHandling.sEepromControl.eEEPromStates = eEEProm_Finished;
  //set eeprom error as present
  psCtrlPxl_InternalHandling->sEepromHandling.sEepromControl.boEepromAccessFaultStatus = TRUE;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_MatrixEEClbkInit_Success
///
/// \descr  callback function called when init of eeprom has succeeded
///
/// \param  void
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlPxl_MatrixEEClbkInit_Success(void)
{
  tsCtrlPxl_InternalHandling *psCtrlPxl_InternalHandling = CtrlPxl_GetInternalHandlingStruct();

  //go to Read state as eeprom can be handled
  psCtrlPxl_InternalHandling->sEepromHandling.sEepromControl.eEEPromStates = eEEProm_Read;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_MtxEEClbkRead_Success
///
/// \descr  callback function called when read of eeprom has succeeded
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlPxl_MtxEEClbkRead_Success(void)
{
  teEEPRom_Jobs eEEPromJobState;
  tsCtrlPxl_InternalHandling *psCtrlPxl_InternalHandling = CtrlPxl_GetInternalHandlingStruct();

  //check if eeprom can be used
  if (psCtrlPxl_InternalHandling->sEepromHandling.sEepromControl.boMatrixEEPromInitHandlingReady != FALSE )
  {
    //check for diagnostic mode
    if(psCtrlPxl_InternalHandling->sEepromHandling.sEepromControl.sDiagControl.sDiagEEPromControlActive.boEEPromRead != FALSE)
    {
      //we are in the diagnosis path 
      // go to finished state
      psCtrlPxl_InternalHandling->sEepromHandling.sEepromControl.eEEPromStates = eEEProm_Finished;

      //mark the job state to finished when it reached here
      eEEPromJobState = eEEProm_Job_Finished_Ok;

      //trigger the job as finished
     // CtrlPxlRteAccess_SetEEPromJob(eEEPromJobState);   - to be cheked if needed
      //reset EEPROM read diagnosis flag
      psCtrlPxl_InternalHandling->sEepromHandling.sEepromControl.sDiagControl.sDiagEEPromControlActive.boEEPromRead = FALSE;
    }
    else if (psCtrlPxl_InternalHandling->sEepromHandling.sEepromControl.sDiagControl.sDiagEEPromControlActive.boEEPromWrite != FALSE)
    {
      //we are in the diagnosis path 
      //go to wait state because on this diag command, program shall go into write state
      psCtrlPxl_InternalHandling->sEepromHandling.sEepromControl.eEEPromStates = eEEProm_Wait;
    }
    else
    {
      //other commands are not implemented for EEPROM diag
    }
  }
  else
  {
    //normal path -> go to compare CRC value between Eeprom and NVM
    psCtrlPxl_InternalHandling->sEepromHandling.sEepromControl.eEEPromStates = eEEProm_CompareCRC;
  }
}

//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_MtxEEClbkRead_Fail
///
/// \descr  callback function called when read of eeprom has failed
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlPxl_MtxEEClbkRead_Fail(void)
{
  teEEPRom_Jobs eEEPromJobState = eEEProm_Job_Error;
  tsCtrlPxl_InternalHandling *psCtrlPxl_InternalHandling = CtrlPxl_GetInternalHandlingStruct();

  //set eeprom error as present 
  psCtrlPxl_InternalHandling->sEepromHandling.sEepromControl.boEepromAccessFaultStatus = TRUE;
  
  //go to Finished state, eeprom can't be handled
  psCtrlPxl_InternalHandling->sEepromHandling.sEepromControl.eEEPromStates = eEEProm_Finished;

  //check for diagnostic EEPROM mode
  if ((psCtrlPxl_InternalHandling->sEepromHandling.sEepromControl.boMatrixEEPromInitHandlingReady == TRUE) &&
     ((psCtrlPxl_InternalHandling->sEepromHandling.sEepromControl.sDiagControl.sDiagEEPromControlActive.boEEPromRead   != FALSE) ||
      (psCtrlPxl_InternalHandling->sEepromHandling.sEepromControl.sDiagControl.sDiagEEPromControlActive.boEEPromWrite != FALSE))
    )
  {
    //diagnostic is active, follow diagnostic path
    // set the job state to Read
    //rte port to Diag for read job 
    //    CtrlPxlRteAccess_SetEEPromJob(eEEPromJobState);

    //deactivate EEProm read diag flag
    psCtrlPxl_InternalHandling->sEepromHandling.sEepromControl.boMatrixEEPromInitHandlingReady = FALSE;
  }
  else
  {
    //diagnostic not allowed, do nothing
  }
}


//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_MtxEEClbkWrite_Success
///
/// \descr  callback function called when writing of eeprom has succeeded
///
/// \param  -
///
/// \return 
//-----------------------------------------------------------------------------
void CtrlPxl_MtxEEClbkWrite_Success(void)
{
  teEEPRom_Jobs eEEPromJobState;

  //writing has been reached from diagnostic mode
  tsCtrlPxl_InternalHandling *psCtrlPxl_InternalHandling = CtrlPxl_GetInternalHandlingStruct();

  //go to finished state
  psCtrlPxl_InternalHandling->sEepromHandling.sEepromControl.eEEPromStates = eEEProm_Finished;

  //check for diagnostic mode
  if ((psCtrlPxl_InternalHandling->sEepromHandling.sEepromControl.boMatrixEEPromInitHandlingReady == TRUE) && (psCtrlPxl_InternalHandling->sEepromHandling.sEepromControl.sDiagControl.sDiagEEPromControlActive.boEEPromWrite != FALSE))
  {
    //we are in diagnostic mode
    //update the EEPROM status
    eEEPromJobState = eEEProm_Job_Finished_Ok;

    //set the job on RTE port to diagnosis
    //CtrlPxlRteAccess_SetEEPromJob(eEEPromJobState);

    //deactivate EEPROM write diagnosis flag
    psCtrlPxl_InternalHandling->sEepromHandling.sEepromControl.sDiagControl.sDiagEEPromControlActive.boEEPromWrite = FALSE;
  }
  else
  {
    // not used in normal path
  }
}

//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_MtxEEClbkWrite_Fail
///
/// \descr  callback function called when writing of eeprom has failed
///
/// \param  -
///
/// \return 
//-----------------------------------------------------------------------------
void CtrlPxl_MtxEEClbkWrite_Fail(void)
{
  teEEPRom_Jobs eEEPromJobState = eEEProm_Job_Error;

  //writing has been reached from diagnostic mode
  tsCtrlPxl_InternalHandling *psCtrlPxl_InternalHandling = CtrlPxl_GetInternalHandlingStruct();

  //set the error and activate reaction
  psCtrlPxl_InternalHandling->sEepromHandling.sEepromControl.boEepromAccessFaultStatus = TRUE;

  //go to finished state
  psCtrlPxl_InternalHandling->sEepromHandling.sEepromControl.eEEPromStates = eEEProm_Finished;

  //check for diagnostic mode
  if ((psCtrlPxl_InternalHandling->sEepromHandling.sEepromControl.boMatrixEEPromInitHandlingReady == TRUE) &&
      (psCtrlPxl_InternalHandling->sEepromHandling.sEepromControl.sDiagControl.sDiagEEPromControlActive.boEEPromWrite != FALSE))
  {
    //we are in diagnostic mode
    //set the job on RTE port to diagnosis
    //CtrlPxlRteAccess_SetEEPromJob(eEEPromJobState);

    //deactivate EEPROM write diagnosis flag
    psCtrlPxl_InternalHandling->sEepromHandling.sEepromControl.sDiagControl.sDiagEEPromControlActive.boEEPromWrite = FALSE;
  }
  else
  {
    // not used in normal path
  }
}


//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_CompareEEPromAndNvmData
///
/// \descr  this function compares the EEPROM CRC and NVM CRC stored. In case the content of the 
///         two memories don't match and the CRC is valid (different by 0x00 and 0xFF), entire eeprom 
///         shall be copied into NVM as backup, otherwise, a reaction and  error will be set.
///
/// \param  -
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlPxl_CompareEEPromAndNvmData(void)
{
  //writing has been reached from diagnostic mode
  tsCtrlPxl_InternalHandling *psCtrlPxl_InternalHandling = CtrlPxl_GetInternalHandlingStruct();
  uint8 ucCrcCalculated;

  //reset the error
  psCtrlPxl_InternalHandling->sEepromHandling.sEepromControl.boEepromChecksumFaultStatus = FALSE;

  //check CRC value from EEPROM with 0x00 and 0xFF (empty, invalid)
  if ((CtrlPxl_CRC8_Eeprom != 0u) && (CtrlPxl_CRC8_Eeprom != 0xFFu))
  {
    //calculate CRC over EEPROM data read before
    ucCrcCalculated = Crc_CalculateCRC8H1D((const uint8*)&CTRLPXL_EEPROM_MAPPING_BYTES[CTRL_PXL_EEPROM_CRC_OFFSET], (CTRL_PXL_EEPROM_SIZE - CTRL_PXL_EEPROM_CRC_OFFSET) , CRC_SEED_INIT_CRC8H2F_VAL);
   
    //eeprom contain valid data -> compare if data from nvm and eeprom are identically
    if  (CtrlPxl_CRC8_Eeprom != ucCrcCalculated)   // eeprom data wrong
    {
      // memory is filled with invalid data -> set error and activate reaction
      psCtrlPxl_InternalHandling->sEepromHandling.sEepromControl.boEepromChecksumFaultStatus = TRUE;
    }
    else if (ucCrcCalculated != CtrlPxl_CRC8_Nvm)  // eeprom data is correct, but different from Nvm -> update NVM structure
    {
      for (uint8_fast ucBCIdx = 0u; ucBCIdx < CTRL_PXL_NUMBER_OF_EEPROM_BINNING_CLASS; ucBCIdx++)
      {
        CTRLPXL_NVM_BINNING[ucBCIdx] = CTRLPXL_EEPROM_MAPPING_FIELDS.LedChannelBCAndReservedGroup.sLedChannelBCAndReserved.uLedChannelBC.ucLedChannelBC[ucBCIdx];
      }


      CtrlPxl_CheckBrightness(CTRLPXL_EEPROM_MAPPING_FIELDS.LMMBrightnessAndReservedGroup.Data);

      //write RTE port with binning class and quality signal 
      CtrlPxl_RteAccess_WriteBinningClass(TRUE, CTRLPXL_NVM_BINNING);

      //data from Nvm and Eeprom are not identical -> save the content in NVM
      CtrlPxl_RteAccess_WriteEntireEEpromDataIntoNvM(CTRLPXL_EEPROM_MAPPING_BYTES);

      // set error and activate reaction
      psCtrlPxl_InternalHandling->sEepromHandling.sEepromControl.boEepromChecksumFaultStatus = TRUE;

    }
    else
    {
      //data will not be copied in Nvm because they contain the same data
    }
  }
 else
 {
   // memory is filled with valid data -> set error and activate reaction
   psCtrlPxl_InternalHandling->sEepromHandling.sEepromControl.boEepromChecksumFaultStatus = TRUE;
 }
}


//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_AccessCalibDataAndCopy
///
/// \descr  Access calibration data read from Nvm
///
/// \param  pucDataBuff
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlPxl_AccessCalibDataAndCopy(uint8 *pucDataBuff)
{

  for (uint8_fast ucColId = 0u; ucColId < CTRL_PXL_NUMBER_OF_LMM_CHIP_EEPROM; ucColId++)
  {
    for (uint8_fast ucLineId = 0u; ucLineId < CTRLPXL_SIZEOF_EEPROM_BRIGHTVAL_PER_LMM; ucLineId++)
    {
      CTRLPXL_NVM_BRIGHTNESS[(ucColId * CTRLPXL_SIZEOF_EEPROM_BRIGHTVAL_PER_LMM) + ucLineId] = pucDataBuff[(CTRLPXL_NR_BYTES_BRIGHTVAL_WITH_RESERVED_PER_LMM * ucColId) + ucLineId];  
   
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_CheckBrightness
/// 
/// \descr  Access brightness data read from eeprom and check if it is in the
///         accepted range : 0..200 
///
/// \param  pucDataBuff
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlPxl_CheckBrightness(uint8 *pucDataBuff)
{

  uint8 ucBrightnessVal;

  for (uint8_fast ucColId = 0u; ucColId < CTRL_PXL_NUMBER_OF_LMM_CHIP_EEPROM; ucColId++)
  {
    for (uint8_fast ucLineId = 0u; ucLineId < CTRLPXL_SIZEOF_EEPROM_BRIGHTVAL_PER_LMM; ucLineId++)
    {
      ucBrightnessVal = pucDataBuff[(ucColId * CTRLPXL_NR_BYTES_BRIGHTVAL_WITH_RESERVED_PER_LMM) + ucLineId];

      CTRLPXL_EEPROM_MAPPING_FIELDS.LMMBrightnessAndReservedGroup.Data[(ucColId * CTRLPXL_NR_BYTES_BRIGHTVAL_WITH_RESERVED_PER_LMM) + ucLineId] = (ucBrightnessVal > CTRL_PXL_BRIGHTNESS_FACTOR) ? CTRL_PXL_BRIGHTNESS_FACTOR : ucBrightnessVal;

    }
  }
}



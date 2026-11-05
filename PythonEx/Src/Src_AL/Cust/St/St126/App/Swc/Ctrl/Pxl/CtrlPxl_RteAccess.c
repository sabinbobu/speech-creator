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
/// \file   CtrlPxl_RteAccess.c
///
/// \brief  encapsulate RTE access
///
/// \descr  Functions used for the CtrlPxl RTE wrapper, for input/output 
///
/// \author Caba, Ionut-Stefan ALRO/AL (F37899C)
///         mailTo:ionut-stefan.caba[at]magnetimarelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================
#include "CtrlPxl_RteAccess.h"
#include "CtrlPxl_Types.h"
#include "CtrlPxl_Cfg.h"
#include "CtrlPxl_MemHandling.h"

#ifdef UNIT_TEST
#include <RteCommonTypes.h> 
#endif //UNIT_TEST

//=============================================================================
// function prototypes
//=============================================================================
STATIC_AL Std_ReturnType CtrlPxl_RteAccess_Read_EcuSide(teCtrlPxl_EcuSide* peEcuSide);
STATIC_AL Std_ReturnType CtrlPxl_RteAccess_Read_VccxLineState(teCtrlPxl_VccxLineState* peVccxState);
STATIC_AL void CtrlPxl_RteAccess_ReadNvmMatrixData(uint8* pucData, uint16 unSize);
STATIC_AL void CtrlPxl_RteAccess_MtxEE_Read(uint8 *pucBuff_List, uint16 unStartAddr, uint16 unLength, void(*pfnSuccess)(void), void(*pfnFail)(void));


//=============================================================================
// variables
//=============================================================================


//=============================================================================
// functions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_RteAccess_Get_Intensities_CPM
///
/// \descr  this function takes intensities via RTE
///
/// \param  *punMxBuff
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlPxl_RteAccess_Get_Intensities_CPM(uint16* punMxBuff)
{
  tsRte_TgtPxlSig0Arr *psTgtPxlSig0Arr;
  psTgtPxlSig0Arr = (tsRte_TgtPxlSig0Arr *)punMxBuff;         //PRQA S 310 // cast needed
  (void)Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels(psTgtPxlSig0Arr);
}

//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_RteAccess_Set_MLCTgtPWMs
///
/// write  CtrlPxl intensity to Mlc
///
/// \param  *punData
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlPxl_RteAccess_Set_MLCTgtPWMs(uint16 *punData)
{
  tsRte_TgtMtxPixels_sVal *punMlcLedPwms;
  //PRQA S 310 1 // Cast needed
  punMlcLedPwms = (tsRte_TgtMtxPixels_sVal*)punData;
  //write intensities to mlc 
  (void)Rte_Write_CtrlPxl_TgtMtxPixels_sVal((tsRte_TgtMtxPixels_sVal*)punMlcLedPwms);
}

//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_RteAccess_Set_MLC_EnableTransmission
///
/// \descr  This function sends the command to restart the configuration of
///         the MLC driver (sets the state to CddMlc_SystemMode_CfgComm, so the 
///         chips will be  reinitialized)
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlPxl_RteAccess_Set_MLC_EnableTransmission(void)
{
  uint8 ucMatrixControl_Command = CTRL_PXL_MATRIX_SYSMODE_CTRL_RESETCOMM;

  //write reset communication trigger command to matrix
  (void)Rte_Write_CtrlPxl_CddMlc_SysCtrlCommand(&ucMatrixControl_Command);
}

//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_RteAccess_Set_MLC_DisableTransmission
///
/// \descr  This function disables the communication of the MLC chips ( sends the
///         command to disable the communication -> state is set to 
///         CddMlc_SystemMode_Inactive )
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
//void CtrlPxl_RteAccess_Set_MLC_DisableTransmission(void)
//{
//  uint8 ucMatrixControl_Command = CTRL_PXL_MATRIX_SYSMODE_CTRL_SETINACTIVE;
//
//  //write reset communication trigger command to matrix
//  (void)Rte_Write_CtrlPxl_CddMlc_SysCtrlCommand(&ucMatrixControl_Command);
//
//}

//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_RteAccess_Reset_MLCSettings
///
/// \descr  This function sends the command to reset the MLC settings -> clear internal
///         flags and sets MLC state to CddMlc_SystemMode_CfgComm and the State machine
///         is restarted
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlPxl_RteAccess_Reset_MLCSettings(void)
{
  //roCddMlc_ResetMlcSettings();
  boolean boMatrixReset = TRUE;

  //write reset communication trigger command to matrix
  (void)Rte_Write_CtrlPxl_CddMlc_ReinitMatrix(&boMatrixReset);
}

//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_RteAccess_Get_ECU_Side
///
/// \descr  this function return ECU side, used for coding data handling
///
/// \param  void
///
/// \return eEcuSide - stores Ecu mounting side
//-----------------------------------------------------------------------------
uint8 CtrlPxl_RteAccess_Get_ECU_Side(void)
{
  teCtrlPxl_EcuSide eEcuSide = eEcu_Undef;
  //read ECU side
  (void)CtrlPxl_RteAccess_Read_EcuSide(&eEcuSide);
  //return ECU side, cast needed for macro
  return (uint8)eEcuSide;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_RteAccess_Read_EcuSide
///
/// \descr  Read Ecu mounting side from Rte
///
/// \param  *peEcuSide - stores Ecu mounting side
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
STATIC_AL Std_ReturnType CtrlPxl_RteAccess_Read_EcuSide(teCtrlPxl_EcuSide* peEcuSide)
{
  Std_ReturnType     ucReturnValue;
  teRte_MountingSide eMountingSide;

  ucReturnValue = Rte_Read_IoHwAbUser_GetMountingSide(&eMountingSide);

  switch (eMountingSide)
  {
  case eMountedLeft:
    *peEcuSide = eEcu_Left;
    break;
  case eMountedRight:
    *peEcuSide = eEcu_Right;
    break;
  default:
    *peEcuSide = eEcu_Undef;
    break;
  }

  return ucReturnValue;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_RteAccess_Get_Coding
///
/// \descr  Read Coding Data via RTE
///
/// \param  *psCodingParam - pointer to commands and coding data
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlPxl_RteAccess_Get_Coding(tsCtrlPxl_CodingParameters *psCodingParam)
{
  tsRteCodingParameters sRteCodingParameters;

  (void)Rte_Read_CodM_CtrlPxl_Para(&sRteCodingParameters);

  //PRQA S 310 1 // Cast needed
  psCodingParam->eCodingState       = sRteCodingParameters.eCodingState;
  psCodingParam->psCodingParameters = sRteCodingParameters.psCodingParameters_Blocks;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_RteAccess_Get_PxlErrorStatus
///
/// \descr  return pixel error active/inactive
///
/// \param  *puLedFault : pixel errors mapped on bit field
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CtrlPxl_RteAccess_Get_PxlErrorStatus(tuCtrlPxl_PxlFault* puLedFault )
{
  uint8_fast ucIdx;
  boolean boError = FALSE;
  STATIC_UT(tsRte_CddMlc_LedStatus, CtrlPxl_asPxlState[CTRL_PXL_NUMBER_OF_MLC_CHIP], { 0U });

  //proceed to reading the Mlc Pixel Faults via RTE
  (void)Rte_Read_CtrlPxl_CddMlc_LedStatus_aVal((tasRte_MlcLedStatus*)CtrlPxl_asPxlState);    //PRQA S 310 // cast needed

  //check each MLC chip for pixel fault; stop when first fault was found
  for (ucIdx = 0u; ucIdx < CTRL_PXL_NUMBER_OF_MLC_CHIP; ucIdx++)
  {
    puLedFault[ucIdx].bPxl.unLedFault = CtrlPxl_asPxlState[ucIdx].unLedFault;

    if (puLedFault[ucIdx].bPxl.unLedFault != 0u)
    {
      boError = TRUE;   //set error as active
    }
  }

  //return error status
  return boError;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_RteAccess_Get_CommErrorStatus
///
/// \descr  return communication error active/inactive
///
/// \param  psCddMlcComStatus  : matrix comm status for each chip
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CtrlPxl_RteAccess_Get_CommErrorStatus(tsCtrlPxl_ComStatus* psCddMlcComStatus)
{
  boolean boError = FALSE;

  //proceed to reading Comm status from CddMlc port via RTE
  (void)Rte_Read_CtrlPxl_CddMlc_ComStatus_sVal((tsRte_CddMlcComStatus*)psCddMlcComStatus);   //PRQA S 310 // cast needed

  //set as error present or inactive based on the communciation status
  boError = (psCddMlcComStatus->ucMlcStatus != 0u) ? TRUE : FALSE;

  //return communication error status
  return boError;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_RteAccess_Get_ResetErrorStatus
///
/// \descr  return mlc power cycle status (reset triggered or not)
///
/// \param  -
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CtrlPxl_RteAccess_Get_ResetErrorStatus(void)
{
  tsRte_CddMlcComStatus sCddMlcComStatus;
  boolean boError = FALSE;

  //proceed to reading Comm status from CddMlc port via RTE
  (void)Rte_Read_CtrlPxl_CddMlc_ComStatus_sVal(&sCddMlcComStatus);

  //set as error present or inactive by checking if reset has occured
  boError = (sCddMlcComStatus.ucPowerCycle != 0u) ? TRUE : FALSE;

  //return power cycle status
  return boError;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_RteAccess_Write_MatrixFaultStatus
///
/// \descr  send to CtrlLed the error status of matrix
///
/// \param  psMatrixFaultState
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlPxl_RteAccess_Write_MatrixFaultStatus(tsCtrlPxl_MatrixFaultStates *psMatrixFaultState)
{
  tsRte_MatrixFaultStates psMatrixFault;

  psMatrixFault.boCommError           = psMatrixFaultState->boCommFault;
  psMatrixFault.boPxlError            = psMatrixFaultState->boPxlFault;
  psMatrixFault.boShortToGndError     = psMatrixFaultState->boShortToGnd;
  psMatrixFault.boShortToVbatError    = psMatrixFaultState->boShortToVbat;

  (void)Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState(&psMatrixFault);
}

//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_RteAccess_Read_VccxLineState
///
/// \descr  Read matrix driver external supply line status
///
/// \param  peVccxState : store external supply state
///
/// \return teRte_VccxLineState
//-----------------------------------------------------------------------------
STATIC_AL Std_ReturnType CtrlPxl_RteAccess_Read_VccxLineState(teCtrlPxl_VccxLineState* peVccxState)
{
  Std_ReturnType          ucReturnValue;
  teRte_VccxLineState     eVccxLineState;

  ucReturnValue = Rte_Read_IoHwAbUser_VccxLineState(&eVccxLineState);

  switch (eVccxLineState)
  {
  case eVccx_Short2GND:
    *peVccxState = eMatrixVccx_Short2GND;
    break;
  case  eVccx_Short2Vbat:
    *peVccxState = eMatrixVccx_Short2Vbat;
    break;
  default:
    *peVccxState = eMatrixVccx_noError;
    break;
  }

  return ucReturnValue;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_RteAccess_Get_VccxState
///
/// \descr  this function return Vccx Status, used for matrix external supply
///         error handling
///
/// \param  void
///
/// \return eVccxLineState - stores Vccx State
//-----------------------------------------------------------------------------
teCtrlPxl_VccxLineState CtrlPxl_RteAccess_Get_VccxState(void)
{
  teCtrlPxl_VccxLineState eVccxLineState = eMatrixVccx_noError;

  //read Vccx State side
  (void)CtrlPxl_RteAccess_Read_VccxLineState(&eVccxLineState);

  //return Vccx Line Status
  return eVccxLineState;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_RteAccess_Get_MlcCrcError
///
/// \descr  read crc frame error
///
/// \param  pucCrcErrorStatus : crc error status for each matrix chip
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlPxl_RteAccess_Get_MlcCrcError(uint8* pucCrcErrorStatus)
{
  (void)Rte_Read_CtrlPxl_CddMlc_CrcError_sVal((tsRte_MlcComErrorStatus*)pucCrcErrorStatus);   //PRQA S 310 // cast needed
}

//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_RteAccess_Write_MlcErrors
///
/// \descr  Write Matrix Status Errors to CtrlLED
///
/// \param  puMtxbErr : write matrix errors on bit fields to CtrLed mapped on logical units
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlPxl_RteAccess_Write_MlcErrors(tuCtrlPxl_bErr* puMtxbErr)
{
  tauRte_CtrlPxl_Mtx_bErr auMatrixErrors;

  for (uint8 ucIdx = 0u; ucIdx < sizeof(tauRte_CtrlPxl_Mtx_bErr) / sizeof(tuRte_CtrlPxl_bErr); ucIdx++)
  {
    auMatrixErrors.auMtxErrorStatus[ucIdx].ucRaw = (puMtxbErr + ucIdx)->ucRaw;
  }

  (void)Rte_Write_CtrlPxl_CtrlLed_Matrix_bErr_aVal(&auMatrixErrors);
}

//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_RteAccess_Write_Mtx_PxlActPercPWM_ValidFrames
///
/// \descr  Write PWM value [%] of each Pxl segment to validation frames
///
/// \param  *psPxlPWM
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlPxl_RteAccess_Write_Mtx_PxlActPercPWM_ValidFrames(tsRte_ucActualPxlPWM*  psPxlPWM)
{
  (void)Rte_Write_CtrlPxl_ActualPxlPWM(psPxlPWM);
}

//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_RteAccess_Write_Mtx_PxlError_ValidFrames
///
/// \descr  Write pixel defect status [T/F] of each Pxl segment to validation frames
///
/// \param  *psPxlError_DiagStatus
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlPxl_RteAccess_Write_Mtx_PxlError_ValidFrames(tsRte_boMtxSegmentFault*  psPxlError_DiagStatus)
{
  (void)Rte_Write_CtrlPxl_ActualPxlError(psPxlError_DiagStatus);
}

//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_RteAccess_MatrixEE_Init
///
/// \descr  Initialization of EEProm, where pfnSuccess should receive a success
///         initialization, else pfnFail parameter should receive a failure
///
/// \param  pfnSuccess    : returned success callback 
/// \param  pfnFail       : returned failed callback 
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlPxl_RteAccess_MatrixEE_Init(void(*pfnSuccess)(void), void(*pfnFail)(void))
{
  tsRte_MatrixEE0CbkFn sEepromData;
  //go to wait transition until receive callbacks from EEPROM
  CtrlPxl_GetInternalHandlingStruct()->sEepromHandling.sEepromControl.eEEPromStates = eEEProm_Wait;
  sEepromData.pfnMatrixEECbkSuccess = pfnSuccess;
  sEepromData.pfnMatrixEECbkFail    = pfnFail;

  //trigger port to start initialization of I2C state machine from MLC for Eeprom data
  (void)Rte_Write_CtrlPxl_MatrixEE_CbkInitData(&sEepromData);
}

//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_RteAccess_ReadNvmMatrixData
///
/// \descr  This function is called at each wake-up/start-up when data shall be 
///         read from NVM block
///
/// \param  pucData : buffer to copy Nvm block content
/// \param  unSize  : size of data
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlPxl_RteAccess_ReadNvmMatrixData(uint8* pucData, uint16 unSize)
{
  tsRte_NvMBlock sPxlNvmBlock;
  sPxlNvmBlock.pucData = pucData;
  sPxlNvmBlock.unSize  = unSize;

  //copy the content of Nvm data
  (void)UtilMemCopy(sPxlNvmBlock.pucData, &NvmBlockMatrixEEPromContent.Data[0], sPxlNvmBlock.unSize);
}

//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_RteAccess_MtxEE_Read
///
/// \descr  This function triggers the reading operation of EEPROM memory of
///         matrix
///
/// \param  pucBuff_List: buffer to store data read from EEPROM
/// \param  unStartAddr : starting point of EEPROM read
/// \param  unLength    : no. of bytes to be read
/// \param  pfnSuccess  : callback function for successful reading status
/// \param  pfnFail     : callback function for failed reading status
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlPxl_RteAccess_MtxEE_Read(uint8 *pucBuff_List, uint16 unStartAddr, uint16 unLength, void(*pfnSuccess)(void), void(*pfnFail)(void))
{
  tsRte_MatrixEE0peration sEepromData;
  //go to wait transition until receive callbacks from EEPROM
  CtrlPxl_GetInternalHandlingStruct()->sEepromHandling.sEepromControl.eEEPromStates = eEEProm_Wait;
  sEepromData.pucMatrixEEbuffer   = pucBuff_List;
  sEepromData.unMatrixEEStartAdd  = unStartAddr;
  sEepromData.unMatrixEELength    = unLength;
  sEepromData.sMatrixEE0CbkFn.pfnMatrixEECbkSuccess = pfnSuccess;
  sEepromData.sMatrixEE0CbkFn.pfnMatrixEECbkFail    = pfnFail;

  //trigger port to read from MLC the Eeprom data
  (void)Rte_Write_CtrlPxl_MatrixEE_DataRead(&sEepromData);
}

//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_RteAccess_MtxEE_Write
///
/// \descr This function triggers the writing operation of EEPROM memory of
///         matrix
///
/// \param  ucBuff_List    : buffer to write data in EEPROM
/// \param  unStartAddr    : starting point of EEPROM write
/// \param  unLength       : no. of bytes to be written
/// \param  pfnSuccess     : callback function for successful writing status
/// \param  pfnFail        : callback function for failed writing status
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
 void CtrlPxl_RteAccess_MtxEE_Write(uint8 ucBuff_List[], uint16 unStartAddr, uint16 unLength, void(*pfnSuccess)(void), void(*pfnFail)(void))
{
  tsRte_MatrixEE0peration sEepromData;
  //go to wait transition until receive callbacks from EEPROM
  CtrlPxl_GetInternalHandlingStruct()->sEepromHandling.sEepromControl.eEEPromStates = eEEProm_Wait;
  sEepromData.pucMatrixEEbuffer     = ucBuff_List;
  sEepromData.unMatrixEEStartAdd    = unStartAddr;
  sEepromData.unMatrixEELength      = unLength;
  sEepromData.sMatrixEE0CbkFn.pfnMatrixEECbkSuccess = pfnSuccess;
  sEepromData.sMatrixEE0CbkFn.pfnMatrixEECbkFail    = pfnFail;

  //trigger port to write data to Eeprom data
  (void)Rte_Write_CtrlPxl_MatrixEE_DataWrite(&sEepromData);
}

//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_RteAccess_ReadEntireMatrixData
///
/// \descr  This function reads the entire MLC EEPROM data  or the Nvm block
///         depending on the boAccessEEPromReading parameter
///
/// \param  boAccessEEPromReading   : TRUE (read from Eeprom), FALSE (read from nvm)
/// \param  pucMtxEEProm_MemCfg     : buffer for eeprom memory
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlPxl_RteAccess_ReadEntireMatrixData(boolean boAccessEEPromReading, uint8* pucMtxEEProm_MemCf)
{
  if (boAccessEEPromReading != FALSE)
  {
   // read entire EEPROM memory 
    //call the MLC access function
    CtrlPxl_RteAccess_MtxEE_Read(pucMtxEEProm_MemCf, CTRL_PXL_START_EEPROM_ADDRESS, CTRL_PXL_EEPROM_SIZE, CtrlPxl_MtxEEClbkRead_Success, CtrlPxl_MtxEEClbkRead_Fail);
  }
  else
  {
    //EEPROM not ready, read data from the NVM
    CtrlPxl_RteAccess_ReadNvmMatrixData(pucMtxEEProm_MemCf, CTRL_PXL_EEPROM_SIZE);
  }

}

//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_RteAccess_WriteBinningClass
///
/// \descr  Send binning class for all LED channels 
///
/// \param  boValidData  : eeprom valid (TRUE)
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlPxl_RteAccess_WriteBinningClass(boolean boValidData, uint8* pucData)
{
  (void)boValidData;

  tasRte_CtrlPxl_BinEEprom sCtrlPxl_BinEeprom;

  //write for each binning class for matrix channels
  for (uint8 ucIdx = 0u; ucIdx < sizeof(tasRte_CtrlPxl_BinEEprom)/sizeof(tsRte_Binning0); ucIdx++)
  {
    //set signal qaulity based on error received
    if ( (pucData[ucIdx] >= CTRL_PXL_CFG_MAX_BINNING_CLASSES) /* (boValidData == FALSE)*/)
    {
      //set binning class quality factor as invalid
      sCtrlPxl_BinEeprom[ucIdx].eSigQty = SIG_INVALID;

      // set default binning value for out of range binning : Class 0
      pucData[ucIdx] =  CTRL_PXL_CFG_BINNING_CLASS_0 ;
    }
    else
    {

      //set binning class quality factor as valid
      sCtrlPxl_BinEeprom[ucIdx].eSigQty = SIG_VALID;
    }

    //invalid data, set the default binning class
    sCtrlPxl_BinEeprom[ucIdx].ucBinning = pucData[ucIdx];
  }
  
  //write RTE port to RSens
  (void)Rte_Write_CtrlPxl_CtrlLed_EepromBinningClass_aVal(&sCtrlPxl_BinEeprom);

}

//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_RteAccess_WriteEntireEEpromDataIntoNvM
///
/// \descr  This functions is called when data from NvM is different by data
///         from EEProm and copies entire structure of EEProm in NVM
///
/// \param  uMtxEEProm_MemCfg : eeprom memory mapped 
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlPxl_RteAccess_WriteEntireEEpromDataIntoNvM(uint8* pucMtxEEProm_MemCfg)
{
  tsRte_NvMBlock sPxlNvmBlock;
  sPxlNvmBlock.pucData = pucMtxEEProm_MemCfg;
  sPxlNvmBlock.unSize  = CTRL_PXL_EEPROM_SIZE;

  //trigger Nvm block writing
  (void)Rte_Write_CtrlPxl_Nvm_WriteData(&sPxlNvmBlock); 
}

//-----------------------------------------------------------------------------
/// \brief CtrlPxl_RteAccess_Set_MtxEeprom_ErrorStatus
///
/// \descr  This function sends the matrix eeprom error status : Wrong Checksum
///         Fault for invalid CRC and NoAccess Fault for received failed callbacks
///
/// \param  boWrng_Chksum  : Wrong Checksum Fault Status
/// \param  boNoAccess     : NoAccess Fault for received failed callbacks
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlPxl_RteAccess_Set_MtxEeprom_ErrorStatus(boolean boWrng_Chksum, boolean boNoAccess)
{
  tsRte_MtxEeprom_ErrStatus sMtxEeprom_ErrStatus;

  sMtxEeprom_ErrStatus.boEepromWrngChksumFault = boWrng_Chksum;
  sMtxEeprom_ErrStatus.boEepromNoAccessFault   = boNoAccess;

  (void)Rte_Write_CtrlPxl_MtxEeprom_ErrorStatus(&sMtxEeprom_ErrStatus);
}

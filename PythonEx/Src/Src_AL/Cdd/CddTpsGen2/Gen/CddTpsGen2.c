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
/// \file  CddTpsGen2.c
///
/// \brief
///
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
//standard includes
#include <AL_Helper.h>

// module API (include path)
#include <CddTpsGen2.h>

// module includes (relative to API)
#include <CddTpsGen2_Types.h>
#include <CddTpsGen2_Cod.h>
#include <CddTpsGen2_Com.h>

#include <CddTpsGen2_Cod.h>

//-----------------------------------------------------------------------------
// Variables
//-----------------------------------------------------------------------------
STATIC_AL tsCddTpsGen2_DevData CddTpsGen2_sDevData;
STATIC_AL boolean CddTpsGen2_boReinitChips = FALSE;

STATIC_AL tCddTpsGen2_I2C_pFnct CddTpsGen2_I2C_pfnInitSuccessClbk = NULL_PTR;        // Init Success Callback pointer
STATIC_AL tCddTpsGen2_I2C_pFnct CddTpsGen2_I2C_pfnInitFailedClbk = NULL_PTR;         // Init Failed Callback pointer
STATIC_AL tCddTpsGen2_I2C_pFnct CddTpsGen2_I2C_pfnWriteSuccessClbk = NULL_PTR;       // Write Success Callback pointer
STATIC_AL tCddTpsGen2_I2C_pFnct CddTpsGen2_I2C_pfnWriteFailedClbk = NULL_PTR;        // Write Failed Callback pointer
STATIC_AL tCddTpsGen2_I2C_pFnct CddTpsGen2_I2C_pfnReadSuccessClbk = NULL_PTR;        // Read Success Callback pointer
STATIC_AL tCddTpsGen2_I2C_pFnct CddTpsGen2_I2C_pfnReadFailedClbk = NULL_PTR;         // Read Failed Callback pointer

STATIC_AL uint8 *CddTpsGen2_I2C_ucPtrReadData = NULL_PTR;                       // Pointer to data buffer used at read operation
STATIC_AL uint8 *CddTpsGen2_I2C_ucPtrWriteData = NULL_PTR;                      // Pointer to data buffer used at write operation

STATIC_AL uint16 CddTpsGen2_I2C_unWriteStartAddress = 0u;                       // Start Address for Write operation
STATIC_AL uint16 CddTpsGen2_I2C_unWriteEndAddress = 0u;                         // End Address for Write Operation

STATIC_AL uint16 CddTpsGen2_I2C_unReadStartAddress = 0u;                        // Start Address for Read operation
STATIC_AL uint16 CddTpsGen2_I2C_unReadEndAddress = 0u;                          // End Address for Read operation
STATIC_AL uint8 CddTpsGen2_I2C_ucReadBytesLeft = 0u;                            // Bytes Left to read on current operation
STATIC_AL uint8 CddTpsGen2_I2C_ucCmdReadData_RxLength = 0u;                     // I2C Read Data Command Length

STATIC_AL tCddTpsGen2_I2C_eState CddTpsGen2_I2C_State = CddTpsGen2_I2C_NotInit;           // I2C Current Operation State - Set to NotInit since Init operation not yet trigger.
STATIC_AL tCddTpsGen2_I2C_eState CddTpsGen2_I2C_Response = CddTpsGen2_I2C_NotInit;           // I2C Current Operation State - Set to NotInit since Init operation not yet trigger.

STATIC_AL uint8 CddTpsGen2_I2C_ucInitTimeoutCounter = 0u;                       // Init Operation Timeout Counter
STATIC_AL uint8 CddTpsGen2_I2C_ucReadTimeoutCounter = 0u;                       // Read Operation Timeout Counter
STATIC_AL uint8 CddTpsGen2_I2C_ucWriteTimeoutCounter = 0u;                      // Write Operation Timeout Counter

STATIC_AL tCddTpsGen2_I2C_eStatus CddTpsGen2_I2C_InitStatus = CddTpsGen2_I2C_Rejected;    // Init Operation Status - Set to rejected since Init operation not yet trigger.
STATIC_AL tCddTpsGen2_I2C_eStatus CddTpsGen2_I2C_ReadStatus = CddTpsGen2_I2C_Rejected;    // Read Operation Status - Set to rejected since Init operation not yet trigger.
STATIC_AL tCddTpsGen2_I2C_eStatus CddTpsGen2_I2C_WriteStatus = CddTpsGen2_I2C_Rejected;   // Write Operation Status - Set to rejected since Init operation not yet trigger.

//-----------------------------------------------------------------------------
// Prototypes
//-----------------------------------------------------------------------------
STATIC_AL void CddTpsGen2_DoAddressingMap(tsCddTpsGen2_DevData* psData);

STATIC_AL void CddTpsGen2_I2C_CommandReadStart(uint8 *pucSelSch);
STATIC_AL void CddTpsGen2_I2C_CallbackFunction(tCddTpsGen2_I2C_pFnct pFct);
STATIC_AL void CddTpsGen2_I2C_CommandReadData(uint8 *pucSelSch);

STATIC_AL void CddTpsGen2_I2C_TimeoutInit(void);
STATIC_AL void CddTpsGen2_I2C_TimeoutRead(void);
STATIC_AL void CddTpsGen2_I2C_TimeoutWrite(void);

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_DoAddressingMap
///
/// \descr  Extract the LmmConfig data from the coding structure and map into
///         a chip global structure the data about : chip ID, chip address,
///         no. of supported devices, no. of connected devices
///
/// \param  psData  : structure where to save chip data
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CddTpsGen2_DoAddressingMap(tsCddTpsGen2_DevData* psData)
{
    uint8  ucChipID = 0u, ucDeviceIdx = 0U, ucDeviceConnected = 0U; 
    // Mlc chips physical addresses
    CONST_AL uint8 aucAddress[] = CDDTPSGEN2_ADDRESS_LIST;
    psData->ucEepromAddr = CDDTPSGEN2_ADDR_NOT_CONNECTED;
    psData->ucBaudRate = CDDMLC_Para_BAUDRATE;
    psData->ucEepromId = CDDTPSGEN2_ADDR_NOT_CONNECTED;

    for (ucDeviceIdx = 0; ucDeviceIdx < CDDTPSGEN2_MAX_CHIPs; ucDeviceIdx++)
    {
      //suppose the chip is not connected
      psData->aucCodDevID[ucDeviceIdx] = CDDTPSGEN2_ADDR_NOT_CONNECTED;
      
      // get the chip physical address
      ucChipID = CDDTPSGEN2_Para_Get_CHIP_ID(ucDeviceIdx);

      // in case the EEPROM is connected to a MLC device not addressed in coding data, skip the usage of EEPROM functionality
      if ( (CDDMLC_Para_CHIP_EEPROM_ID != CDDTPSGEN2_ADDR_NOT_CONNECTED) && (CDDMLC_Para_CHIP_EEPROM_ID == ucChipID) )
      {
        psData->ucEepromAddr = aucAddress[ucChipID];
        psData->ucEepromId = CDDMLC_Para_CHIP_EEPROM_ID;
      }

      if ((ucChipID != CDDTPSGEN2_ADDR_NOT_CONNECTED) && (ucChipID <= CDDTPSGEN2_COD_DEV_ADDR_SLAVE_MAX_ID))
      {
        // the physical address  is the digital mapping of the device ID with the DEVID Byte with Parity
        psData->asMasterSlaveId[ucDeviceConnected].ucPhysicalAddr = aucAddress[ucChipID];
        psData->asMasterSlaveId[ucDeviceConnected].boIsMasterId   = FALSE;

        psData->aucCodDevID[ucDeviceConnected] = ucDeviceIdx;
        ucDeviceConnected++;
      }
      else if ((ucChipID != CDDTPSGEN2_ADDR_NOT_CONNECTED) && (ucChipID <= CDDTPSGEN2_COD_DEV_ADDR_MASTER_MAX_ID))
      {
        // the physical address  is the digital mapping of the device ID with the DEVID Byte with Parity
        psData->asMasterSlaveId[ucDeviceConnected].ucPhysicalAddr = aucAddress[ucChipID - CDDTPSGEN2_COD_DEV_ADDR_MASTER_OFFSET_ID];
        psData->asMasterSlaveId[ucDeviceConnected].boIsMasterId   = TRUE;

        psData->aucCodDevID[ucDeviceConnected] = ucDeviceIdx;
        ucDeviceConnected++;
      }
      else
      {
        // do nothing; the chip is not connected
      }

    }

    psData->ucConnectedDevices = ucDeviceConnected;
  }


//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_Init
///
/// \descr  Init function of Tps92662/3 chip type, 2nd generation
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void CddTpsGen2_Init(void)
{
  //do remapping of addresses
  CddTpsGen2_DoAddressingMap(&CddTpsGen2_sDevData);
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_Cycle
///
/// \descr  Cycle function of Tps92662/3 chip type, 2nd generation
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void CddTpsGen2_Cycle(void)
{
  return;
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_SetDutyCycle_1_1024
///
/// \descr  This functions sets the duty cycle for each pixel and check sfor minimun
///         PWM value
///
/// \param  ucChipIdx
/// \param  punDuty
///
/// \return void
//-----------------------------------------------------------------------------
void CddTpsGen2_SetDutyCycle_1_1024(const uint8 ucChipIdx,  uint16* punDuty)
{
  if (ucChipIdx < CDDTPSGEN2_MAX_CHIPs)
  {
    for (uint8_fast ucPxl = 0u; ucPxl < CDDTPSGEN2_TPS92662A_MAX_SWITCHS_PER_DEVICE; ucPxl++)
    {
      // if pixel is operated at PWM values under 0.5%, switch OFF pixel
      if (punDuty[ucPxl] < CDDTPSGEN2_MIN_PWM_THD)
      {
        punDuty[ucPxl] = CDDTPSGEN2_MIN_PWM_VAL;
      }
      else
      {
        // don't perform any action
      }
    }

    CddTpsGen2_SetWIDTHReg(ucChipIdx, punDuty);
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_pfGetDevData
///
/// \descr  This function returns coding data structure for GEN2
///
/// \param  -
///
/// \return tsCddTpsGen2_DevData *
//-----------------------------------------------------------------------------
tsCddTpsGen2_DevData* CddTpsGen2_pfGetDevData(void)
{
  return &CddTpsGen2_sDevData;
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_GetPixelFault
///
/// \descr  This function collects the electrical fault for the current device
///
/// \param  ucChipIdx
///
/// \return uint16
//-----------------------------------------------------------------------------
uint16 CddTpsGen2_GetPixelFault(uint8 ucChipIdx)
{
  uint16 unPxlFault_Bit = 0u;
  tuCddTpsGen2_RxELEFAULT uLEDFault;

  if (ucChipIdx < CDDTPSGEN2_MAX_CHIPs)
  {
    CddTpsGen2_GetELEFAULTReg(ucChipIdx, &uLEDFault);

    unPxlFault_Bit  = ((uint16)((uint16)uLEDFault.ucRxByte[0] << 0u) & 0x00FFu);   // save the FAULTL value for the 0-7 LEDs
    unPxlFault_Bit |= ((uint16)((uint16)uLEDFault.ucRxByte[1] << 8u) & 0x0F00u);   // save the FAULTH value for the 8-11 LEDs
  }

  return unPxlFault_Bit;
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_GetComFault
///
/// \descr  This function collects the communication error status for the 
///         current device
///
/// \param  ucChipIdx
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CddTpsGen2_GetComFault(const uint8_fast ucChipIdx)
{
  boolean boDevComFault = FALSE;

  if (ucChipIdx < CDDTPSGEN2_MAX_CHIPs)
  {
    boDevComFault = CddTpsGen2_GetComFAULT(ucChipIdx);
  }
  return boDevComFault;
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_GetCrcFault
///
/// \descr  This function collects the CRC error status for the 
///         current device
///
/// \param  ucChipIdx
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CddTpsGen2_GetCrcFault(const uint8_fast ucChipIdx)
{
  boolean boCrcFault = FALSE;

  if (ucChipIdx < CDDTPSGEN2_MAX_CHIPs)
  {
    boCrcFault = CddTpsGen2_GetCrcFAULT(ucChipIdx);
  }
  return boCrcFault;
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_GetSensorInfo
///
/// \descr  This function collects the adc results status for the 
///         current device
///
/// \param  ucChipIdx
/// \param  psSensorData
///
/// \return void
//-----------------------------------------------------------------------------
void CddTpsGen2_GetSensorInfo(const uint8_fast ucChipIdx, tsCddMlc_SensorData* psSensorData)
{
  boolean boComFault = FALSE;
  tuCddTpsGen2_RxADC uADCInfo;

  if (ucChipIdx < CDDTPSGEN2_MAX_CHIPs)
  {
    CddTpsGen2_GetADCReg(ucChipIdx, &uADCInfo);
    boComFault = CddTpsGen2_GetComFAULT(ucChipIdx);

    psSensorData->ucADC1Value = uADCInfo.ucRxByte[0];
    psSensorData->ucADC2Value = uADCInfo.ucRxByte[1];

    psSensorData->eQlty = (boComFault != FALSE) ? SENSOR_QLTY_INVALID : (CddTpsGen2_GetMuxCmdCompleted() != FALSE) ? SENSOR_QLTY_VALID : SENSOR_QLTY_SNA;
  }
}

//-----------------------------------------------------------------------------
/// \brief CddTpsGen2_ReinitSch
///
/// \descr This function set the command status for chips(scheduler) based on
///        the request from upper layer
///
/// \param  boCom
///
/// \return void
//-----------------------------------------------------------------------------
void CddTpsGen2_ReinitSch(boolean boCom)
{
  CddTpsGen2_boReinitChips = boCom;
}

//-----------------------------------------------------------------------------
/// \brief CddTpsGen2_ResetScheduler
///
/// \descr This function restart the scheduler at first index while initialization 
///        is completed and command for reset is requested
///
/// \param void
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CddTpsGen2_ResetScheduler(void)
{
  boolean boRetVal = FALSE;
  //check for chips initialization
  if (CddTpsGen2_GetInitCmdCompleted() != FALSE)
  {
    boRetVal = CddTpsGen2_boReinitChips;
  }
  return boRetVal;
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_GetInitStatus
///
/// \descr  This function returns the initialization status of all connected chips
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CddTpsGen2_GetInitStatus(void)
{
  return CddTpsGen2_GetInitCmdCompleted();
}

//---------------------------------------------------------EEPROM I2C--------------------------------------------------------------\\

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_I2C_StartInit
///
/// \descr  Function triggers the I2C state machine initialization process and 
///         sets the callbacks events of the embedded EEPROM from Mlc
///
/// \param  Init Success Callback pointer
/// \param  Init Failed Callback pointer
///
/// \return status of init process
//------------------------------------------------------------------------------
tCddTpsGen2_I2C_eStatus* CddTpsGen2_I2C_StartInit(tCddTpsGen2_I2C_pFnct pfnInitSuccessClbk, tCddTpsGen2_I2C_pFnct pfnInitFailedClbk)
{
  // Set the callback function for initialization succeded
  CddTpsGen2_I2C_pfnInitSuccessClbk = pfnInitSuccessClbk;
  // Set the callback function for initialization failed
  CddTpsGen2_I2C_pfnInitFailedClbk = pfnInitFailedClbk;
  // Reset the init timout counter
  CddTpsGen2_I2C_ucInitTimeoutCounter = 0u;
  // Start the I2C initialization process
  CddTpsGen2_I2C_State = CddTpsGen2_I2C_Preinit;
  // Mark the current status of accepted init operation
  CddTpsGen2_I2C_InitStatus = CddTpsGen2_I2C_Pending;
  // Return the pointer to init operation status
  return &CddTpsGen2_I2C_InitStatus;
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_I2C_ReadEeprom
///
/// \descr  Function triggers I2C state machine to read the embedded EEPROM from Mlc
///
/// \param  Buffer where to store read bytes
/// \param  Reading Start address 
/// \param  Number of bytes to be read from EEPROM
/// \param  Read Success Callback pointer
/// \param  Read Failed Callback pointer
///
/// \return status of reading process
//-----------------------------------------------------------------------------
tCddTpsGen2_I2C_eStatus* CddTpsGen2_I2C_ReadEeprom(uint8 *ucData_List, uint16 unStartAddress, uint16 unLength, tCddTpsGen2_I2C_pFnct pfnReadSuccessClbk, tCddTpsGen2_I2C_pFnct pfnReadFailedClbk)
{
  // Set the callback function for read failed
  CddTpsGen2_I2C_pfnReadFailedClbk = pfnReadFailedClbk;

  // The I2C Bus is Idle and data pointer given is valid and address range is valid?
  if ((CddTpsGen2_I2C_State == CddTpsGen2_I2C_Idle) && (NULL_PTR != ucData_List) && ((unStartAddress + unLength) <= CDDTPSGEN2_EEPROM_SIZE))
  {
    // Set the pointer where to store data read from Eeprom
    CddTpsGen2_I2C_ucPtrReadData = ucData_List;
    // Set the start address for read operation
    CddTpsGen2_I2C_unReadStartAddress = unStartAddress;
    // Set the last address for read operation
    CddTpsGen2_I2C_unReadEndAddress = unStartAddress + unLength;
    // Reset the read timout counter
    CddTpsGen2_I2C_ucReadTimeoutCounter = 0u;
    // Trigger read operation by setting the proper state          
    CddTpsGen2_I2C_State = CddTpsGen2_I2C_Read_Start;
    // Mark the current status of accepted read operation
    CddTpsGen2_I2C_ReadStatus = CddTpsGen2_I2C_Pending;
    // Set the callback function for read succeded
    CddTpsGen2_I2C_pfnReadSuccessClbk = pfnReadSuccessClbk;
  }
  else
  {
    // Read Failed Callback Defined? // Call function for read failed
    CddTpsGen2_I2C_CallbackFunction(CddTpsGen2_I2C_pfnReadFailedClbk);
    // Mark the current status of rejected operation
    CddTpsGen2_I2C_ReadStatus = CddTpsGen2_I2C_Rejected;
  }
  // Return the pointer to read operation status
  return &CddTpsGen2_I2C_ReadStatus;
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_I2C_WriteEeprom
///
/// \descr  Function triggers I2C state machine to write the embedded EEPROM from Mlc
///
/// \param  Buffer where to load the write bytes
/// \param  Reading Start address 
/// \param  Number of bytes to be written in EEPROM
/// \param  Write Success Callback pointer
/// \param  Write Failed Callback pointer
///
/// \return status of writting process
//-----------------------------------------------------------------------------
tCddTpsGen2_I2C_eStatus* CddTpsGen2_I2C_WriteEeprom(uint8 *ucData_List, uint16 unStartAddress, uint16 unLength, tCddTpsGen2_I2C_pFnct pfnWriteSuccessClbk, tCddTpsGen2_I2C_pFnct pfnWriteFailedClbk)
{
  // Set the callback function for write failed
  CddTpsGen2_I2C_pfnWriteFailedClbk = pfnWriteFailedClbk;

  // The I2C Bus is Idle and data pointer given is valid and address range is valid?
  if ((CddTpsGen2_I2C_State == CddTpsGen2_I2C_Idle) && (NULL_PTR != ucData_List) && ((unStartAddress + unLength) <= CDDTPSGEN2_EEPROM_SIZE))
  {
    // Set the point from where to load data write in Eeprom
    CddTpsGen2_I2C_ucPtrWriteData = ucData_List;
    // Set the start address for write operation
    CddTpsGen2_I2C_unWriteStartAddress = unStartAddress;
    // Set the last address for write operation
    CddTpsGen2_I2C_unWriteEndAddress = unStartAddress + unLength;
    // Reset the write timout counter
    CddTpsGen2_I2C_ucWriteTimeoutCounter = 0u;
    // Trigger write operation by setting the proper state
    CddTpsGen2_I2C_State = CddTpsGen2_I2C_Write_Data;
    // Mark the current status of accepted write operation
    CddTpsGen2_I2C_WriteStatus = CddTpsGen2_I2C_Pending;
    // Set the callback function for write succeded
    CddTpsGen2_I2C_pfnWriteSuccessClbk = pfnWriteSuccessClbk;
  }
  else
  {
    // Write Failed Callback Defined? // Call function for write failed
    CddTpsGen2_I2C_CallbackFunction(CddTpsGen2_I2C_pfnWriteFailedClbk);
    // Mark the current status of rejected operation
    CddTpsGen2_I2C_WriteStatus = CddTpsGen2_I2C_Rejected;
  }
  // Return the pointer to write operation status
  return &CddTpsGen2_I2C_WriteStatus;
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_I2C_CallbackFunction
///
/// \descr  Function executes valid callback pointers
///
/// \param  function pointer
///
/// \return none
//-----------------------------------------------------------------------------
STATIC_AL void CddTpsGen2_I2C_CallbackFunction(tCddTpsGen2_I2C_pFnct pFct)
{
  // Callback Function Defined?
  if (NULL_PTR != pFct)
  {
    // Execute Callback Function
    pFct();
  }
  else
  {
    // invalid pointer function
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_I2C_HandlePreinit
///
/// \descr  The function handle the response of the I2C Init Command.
///         If the acknowledge byte is received from the Mlc Device
///         that has attached an EEPROM chip, the I2C StateMachine jumps
///         in idle state, otherwise it will remain in preinitialization state.
///
/// \param  *pucAck
///
/// \return none
//-----------------------------------------------------------------------------
void CddTpsGen2_I2C_HandlePreinit(uint8 *pucAck)
{
  // Init Command is aknowledged?
  if (CDDTPSGEN2_ACK_BYTE == *pucAck)
  {
    // Jump to Idle state
    CddTpsGen2_I2C_State = CddTpsGen2_I2C_Init;
    // Reset Acknowledge Byte
    *pucAck = 0x00u;
  }
  else
  {
    // Acknowledge Byte not received yet - remain in current state
    CddTpsGen2_I2C_State = CddTpsGen2_I2C_NotInit;
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_I2C_HandleInit
///
/// \descr  The function handle the response of the I2C Init Command.
///         If the acknowledge byte is received from the Mlc Device
///         that has attached an EEPROM chip, the I2C StateMachine jumps
///         in idle state, otherwise it will remain in initialization state.
///
/// \param  *pucAck
///
/// \return none
//-----------------------------------------------------------------------------
void CddTpsGen2_I2C_HandleInit(uint8 *pucAck)
{
  // Init Command is aknowledged?
  if (CDDTPSGEN2_ACK_BYTE == *pucAck)
  {
    // Jump to Idle state
    CddTpsGen2_I2C_State = CddTpsGen2_I2C_Idle;
    // Reset Acknowledge Byte
    *pucAck = 0x00u;
    // Init Success Callback Defined?
    CddTpsGen2_I2C_CallbackFunction(CddTpsGen2_I2C_pfnInitSuccessClbk);
    // Mark Init Operation Complete
    CddTpsGen2_I2C_InitStatus = CddTpsGen2_I2C_Completed;
  }
  else
  {
    // Acknowledge Byte not received yet - remain in current state
    CddTpsGen2_I2C_State = CddTpsGen2_I2C_NotInit;
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_I2C_HandleStart
///
/// \descr  The function handle the response of the I2C Start Command.
///         If the acknowledge byte is received from the Mlc Device
///         that has attached an EEPROM chip, the I2C StateMachine jumps
///         to the ReadStatus or WriteStatus depending of current operation,
///         otherwise it will jump in to idle state.
///
/// \param  *pucAck
///
/// \return none
//-----------------------------------------------------------------------------
void CddTpsGen2_I2C_HandleStart(uint8 *pucAck)
{
  // Start Command is acknowledged?
  if (CDDTPSGEN2_ACK_BYTE == *pucAck)
  {
    // Depending of current state
    switch (CddTpsGen2_I2C_State)
    {
    case CddTpsGen2_I2C_Read_Start:
    case CddTpsGen2_I2C_Read_Status:
    case CddTpsGen2_I2C_Read_Data:
      // Step to get the status of reading operation
      CddTpsGen2_I2C_State = CddTpsGen2_I2C_Read_Status;
      break;
    case CddTpsGen2_I2C_Write_Data://?
    case CddTpsGen2_I2C_Write_Start:
    case CddTpsGen2_I2C_Write_Status:
      // Step to get the status of writing operation
      CddTpsGen2_I2C_State = CddTpsGen2_I2C_Write_Status;
      break;
    default:
      // Jump to Idle State
      CddTpsGen2_I2C_State = CddTpsGen2_I2C_Idle;
      break;
    }
    // Reset Acknowledge Byte
    *pucAck = 0x00u;
  }
  else
  {
    // Acknowledge Byte not received yet - remain in current state
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_I2C_HandleReset
///
/// \descr  This functions sets the EE state machine to idle state
///
/// \param  uint8 *pucAck
///
/// \return none
//-----------------------------------------------------------------------------
void CddTpsGen2_I2C_HandleReset(uint8 *pucAck)
{
  (void)*pucAck;
  // Jump to Write Start state
  CddTpsGen2_I2C_State = CddTpsGen2_I2C_Idle;
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_I2C_HandleWritingStatus
///
/// \descr  The function handle the response of I2C Get Write Status Command.
///         The status checks if the FIFO is not empty or I2C is not busy,
///         then evaluated if there are no failures during reading operation,
///         a variable length I2C Read Data Command is triggered, depending
///         of left bytes to be read, If one of status error bits are active,
///         then the I2C State Machine is reset and receive FIFO is flushed.
///         See Single Byte EEPROM Write Diagram from TPS92662Q1 Datasheet. 
///
/// \param  ucStatus
///
/// \return none
//-----------------------------------------------------------------------------
void CddTpsGen2_I2C_HandleWritingStatus(const uint8 ucStatus)
{
  // I2C Communication is not busy?
  if ((ucStatus & (uint8)CDDTPSGEN2_I2CSTAT_BUSY) != (uint8)CDDTPSGEN2_I2CSTAT_BUSY)
  {
    // If one of status bits for writing operation (BUSYERR ADRNACK SDALOW DATNACK) are active? 
    if (0u != (uint8)(ucStatus & (uint8)CDDTPSGEN2_I2C_WR_STATUS_VALID))
    {
      // Reset the I2C State Machine
      CddTpsGen2_I2C_State = CddTpsGen2_I2C_ControlReset;
      // Write Failed Callback Defined?
      CddTpsGen2_I2C_CallbackFunction(CddTpsGen2_I2C_pfnWriteFailedClbk);
      // Notice failure of reading operation
      CddTpsGen2_I2C_WriteStatus = CddTpsGen2_I2C_Failed;
    }// Only SLANACK = 1 ? (write in progress ?)
    else if ((ucStatus & (uint8)CDDTPSGEN2_I2CSTAT_SLANACK) != 0u)
    {
      // JSump in Start Writing State
      CddTpsGen2_I2C_State = CddTpsGen2_I2C_Write_Start;
    }
    else
    {
      // Step to next byte
      CddTpsGen2_I2C_unWriteStartAddress++;
      // Increment pointer from where to load the next byte
      CddTpsGen2_I2C_ucPtrWriteData++;

      // Are there more bytes to be written?
      if (CddTpsGen2_I2C_unWriteStartAddress < CddTpsGen2_I2C_unWriteEndAddress)
      {
        // Jump to Write Data State
        CddTpsGen2_I2C_State = CddTpsGen2_I2C_Write_Data;
      }
      else
      {
        // Mark Write Operation Complete
        CddTpsGen2_I2C_WriteStatus = CddTpsGen2_I2C_Completed;
        // Write Success Callback Defined?
        CddTpsGen2_I2C_CallbackFunction(CddTpsGen2_I2C_pfnWriteSuccessClbk);
        // Jump in Idle State
        CddTpsGen2_I2C_State = CddTpsGen2_I2C_Idle;
      }

      // Reset Write Timeout Counter
      CddTpsGen2_I2C_ucWriteTimeoutCounter = 0u;
    }
  }
  else
  {
    // I2C not ready - remain in current state
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_I2C_CommandReadStart
///
/// \descr  Function which computes the length and trigger reading operation.
///         The I2CLEN Register can be configured to read up to 255 bytes in one
///         operation. If there are not bytes to be read, operation is complete.
///
/// \param  *pucSelSch
///
/// \return none
//-----------------------------------------------------------------------------
STATIC_AL void CddTpsGen2_I2C_CommandReadStart(uint8 *pucSelSch)
{
  //Compute the difference between End and Strart Read Address request
  uint16 unlength;

  // If difference is positive Start < End 
  if (CddTpsGen2_I2C_unReadEndAddress > CddTpsGen2_I2C_unReadStartAddress)
  {// Read operation should be triggered
    unlength = (CddTpsGen2_I2C_unReadEndAddress - CddTpsGen2_I2C_unReadStartAddress);

    // Read length greater than I2CLEN register
    if (unlength > 255u)
    {
      // Limit to maximum length
      CddTpsGen2_I2C_ucReadBytesLeft = 255u;
    }
    else
    {
      //Update Remaining Bytes for Reading Operation
      CddTpsGen2_I2C_ucReadBytesLeft = (uint8)unlength;
    }
    *pucSelSch = CDDTPSGEN2_STATE_EE_READ_START;
    // Update the I2C Start Read Command   
    CddTpsGen2_I2C_CmdReadStart(CddTpsGen2_I2C_ucReadBytesLeft, (uint8)CddTpsGen2_I2C_unReadStartAddress);
  }
  else
  {
    // Read Success Callback Defined?
    CddTpsGen2_I2C_CallbackFunction(CddTpsGen2_I2C_pfnReadSuccessClbk);
    // No Operation pending
    CddTpsGen2_I2C_ReadStatus = CddTpsGen2_I2C_Completed;
    // Exit to Idle State
    CddTpsGen2_I2C_State = CddTpsGen2_I2C_Idle;
    // Reset Read Timeout Counter
    CddTpsGen2_I2C_ucReadTimeoutCounter = 0u;
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_I2C_CommandReadData
///
/// \descr  Function which reads from 16Byte length I2C FIFO. The reading command
///         is chosen depending left bytes in combinations of 16/12/4/3/2/1 bytes.
///
/// \param  *pucSelSch
///
/// \return none
//-----------------------------------------------------------------------------
STATIC_AL void CddTpsGen2_I2C_CommandReadData(uint8 *pucSelSch)
{
  // Select the Frame Initilization Byte and expected payload length according to bytes left
  switch (CddTpsGen2_I2C_ucReadBytesLeft)
  {
    // There are 15, 14, 13 or 12 bytes left?
  case 15u:
  case 14u:
  case 13u:
  case 12u:
    *pucSelSch = CDDTPSGEN2_STATE_EE_READ_12_BYTES;
    CddTpsGen2_I2C_ucCmdReadData_RxLength = 12u;                   // set the expected payload length to 12 bytes
    break;
    // There are 11, 10, 9, 8, 7, 6, 5 or 4 bytes left?
  case 11u:
  case 10u:
  case 9u:
  case 8u:
  case 7u:
  case 6u:
  case 5u:
  case 4u:
    *pucSelSch = CDDTPSGEN2_STATE_EE_READ_4_BYTES;
    CddTpsGen2_I2C_ucCmdReadData_RxLength = 4u;                    // set the expected payload length to 4 bytes
    break;
    // There are 3 bytes left?
  case 3u:
    *pucSelSch = CDDTPSGEN2_STATE_EE_READ_3_BYTES;
    CddTpsGen2_I2C_ucCmdReadData_RxLength = 3u;                    // set the expected payload length to 3 bytes
    break;
    // There are 2 bytes left?
  case 2u:
    *pucSelSch = CDDTPSGEN2_STATE_EE_READ_2_BYTES;
    CddTpsGen2_I2C_ucCmdReadData_RxLength = 2u;                    // set the expected payload length to 2 bytes
    break;
    // There is one byte left?
  case 1u:
    *pucSelSch = CDDTPSGEN2_STATE_EE_READ_1_BYTE;
    CddTpsGen2_I2C_ucCmdReadData_RxLength = 1u;                    // set the expected payload length to 1 byte
    break;
    // There are more than 15 bytes left
  default:
    *pucSelSch = CDDTPSGEN2_STATE_EE_READ_16_BYTES;
    //Read 16 bytes - maximum length of reading FIFO
    CddTpsGen2_I2C_ucCmdReadData_RxLength = 16u;                   // set the expected payload length to 16 bytes
    break;
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_I2C_HandleReadingStatus
///
/// \descr  The function handles the response of I2C Get Read Status Command.
///         The status is copied and if the FIFO is not empty or I2C busy,
///         then evaluated if there are no failures during reading operation,
///         depending of left bytes to be read, variable length I2C Read Data
///         Command is triggered. If one of status error bits are active,
///         the the I2C State Machine is reset and receive FIFO is flushed.
///         See Multi-Byte EEPROM Read Diagram from TPS92662Q1 Datasheet. 
///
/// \param  ucStatus - Get the I2C Status from EEPROM Response
///
/// \return none
//-----------------------------------------------------------------------------
void CddTpsGen2_I2C_HandleReadingStatus(const uint8 ucStatus)
{  
  // I2C Communication is not busy or receive FIFO is not empty?
  if ((ucStatus & ((uint8)CDDTPSGEN2_I2CSTAT_BUSY | (uint8)CDDTPSGEN2_I2CSTAT_RFE)) != ((uint8)CDDTPSGEN2_I2CSTAT_BUSY | (uint8)CDDTPSGEN2_I2CSTAT_RFE))
  {
    // If one of status bits for reading operation (BUSYERR ADRNACK SDALOW) are active? 
    if (0u != (uint8)(ucStatus & (uint8)CDDTPSGEN2_I2C_RD_STATUS_VALID))
    {
      // Reset the I2C State Machine and flush the receive FIFO
      CddTpsGen2_I2C_State = CddTpsGen2_I2C_ControlReset;
      // Read Failed Callback Defined?
      CddTpsGen2_I2C_CallbackFunction(CddTpsGen2_I2C_pfnReadFailedClbk);
      // Notice failure of reading operation
      CddTpsGen2_I2C_ReadStatus = CddTpsGen2_I2C_Failed;
    }// Only SLANACK = 1 ? (write in progress ?) or no bytes left to be read on current suboperation?
    else if ((0u != (ucStatus & (uint8)CDDTPSGEN2_I2CSTAT_SLANACK)) || (0u == CddTpsGen2_I2C_ucReadBytesLeft))
    {
      // Jump in Start Reading to evaluate if are next bytes to be read
      CddTpsGen2_I2C_State = CddTpsGen2_I2C_Read_Start;
    }
    else
    {// No errors occured
      // If there are less than 16 bytes or if the receive FIFO is full?
      if ((CddTpsGen2_I2C_ucReadBytesLeft < 16u) || ((ucStatus & (uint8)CDDTPSGEN2_I2CSTAT_RFF) == (uint8)CDDTPSGEN2_I2CSTAT_RFF))
      {
        // Read remaining bytes left
        CddTpsGen2_I2C_State = CddTpsGen2_I2C_Read_Data;
      }
      else
      {
        // Wait to fill all 16 Bytes FIFO
      }
    }
  }
  else
  {
    // I2C not ready - remain in current state
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_I2C_HandleReadData
///
/// \descr  The function handles the response of the 16/12/4/3/2/1 bytes variable
///         length I2C Read Data Command. The received bytes from I2C FIFO are copied
///         to specified pointer. Next the I2C StateMachine jumps in Read Status state
///         to evaluate how many byte left must be further read. If pointer buffer is
///         not valid the I2C State Machine is reset and FIFO is flushed.
///
/// \param  *pucData
///
/// \return none
//-----------------------------------------------------------------------------
void CddTpsGen2_I2C_HandleReadData(uint8 *pucData)
{
  uint8 ucTemp;
  // Pointer to read data buffer valid?
  if (NULL_PTR != CddTpsGen2_I2C_ucPtrReadData)
  { // Parse each byte received on current read operation
    for (ucTemp = 0u; ((ucTemp < CddTpsGen2_I2C_ucCmdReadData_RxLength) && (CddTpsGen2_I2C_ucReadBytesLeft > 0u)); ucTemp++)
    {
      // Store the received bytes
      *(CddTpsGen2_I2C_ucPtrReadData++) = pucData[ucTemp];
      // Increment the start address
      CddTpsGen2_I2C_unReadStartAddress++;
      // Decrement left bytes
      CddTpsGen2_I2C_ucReadBytesLeft--;
    }
    // Jump to Read Status State
    CddTpsGen2_I2C_State = CddTpsGen2_I2C_Read_Status;
    // Reset Read Timeout Counter
    CddTpsGen2_I2C_ucReadTimeoutCounter = 0u;
  }
  else
  {
    // Reading failed due to wrong buffer pointer
    CddTpsGen2_I2C_State = CddTpsGen2_I2C_ControlReset;
    // Read Failed Callback Defined?
    CddTpsGen2_I2C_CallbackFunction(CddTpsGen2_I2C_pfnReadFailedClbk);
    // Mark  Read Operation Rejection
    CddTpsGen2_I2C_ReadStatus = CddTpsGen2_I2C_Rejected;
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_I2C_CommandWriteData
///
/// \descr  Function which writes one byte length in I2CDAT register.
///         If source pointer is not valid reset the I2C State Machine.
///
/// \param  none
///
/// \return none
//-----------------------------------------------------------------------------
STATIC_AL void CddTpsGen2_I2C_CommandWriteData(void)
{
  // Valid pointer from where to load the write byte?
  if (NULL_PTR != CddTpsGen2_I2C_ucPtrWriteData)
  {
    // Update the I2C Write Data Command    
    CddTpsGen2_I2C_CmdWriteData(CddTpsGen2_I2C_ucPtrWriteData);
  }
  else
  {
    // Reset the I2C State Machine
    CddTpsGen2_I2C_State = CddTpsGen2_I2C_ControlReset;
    // Write Failed Callback Defined?
    CddTpsGen2_I2C_CallbackFunction(CddTpsGen2_I2C_pfnWriteFailedClbk);
    // Notice failure of write operation
    CddTpsGen2_I2C_WriteStatus = CddTpsGen2_I2C_Failed;
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_I2C_HandleWriteData
///
/// \descr  The function handles the response of the I2C Write Data Command.
///         If the acknowledge byte is received from the Mlc Device
///         that has attached an EEPROM chip, the I2C StateMachine jumps
///         to the Write Start State, otherwise it will remain in current state.
///
/// \param  *pucAck
///
/// \return none
//-----------------------------------------------------------------------------
void CddTpsGen2_I2C_HandleWriteData(uint8 *pucAck)
{
  // The Write Data Command is acknowledged?
  if (CDDTPSGEN2_ACK_BYTE == *pucAck)
  {
    // Jump to Write Start state
    CddTpsGen2_I2C_State = CddTpsGen2_I2C_Write_Start;

    // Reset Acknowledge Byte
    *pucAck = 0x00u;
  }
  else
  {
    // Acknowledge Byte not received yet - remain in current state
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_I2C_CheckEEActivation
///
/// \descr  This function selects the line from the EEprom scheduler to 
///         perform the desired action
///
/// \param  *pucGoToSt
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CddTpsGen2_I2C_CheckEEActivation(uint8 *pucGoToSt)
{
  switch (CddTpsGen2_I2C_State)
  {
  case CddTpsGen2_I2C_Preinit:
    *pucGoToSt = CDDTPSGEN2_STATE_EE_PREINIT; //select line from schEE
    CddTpsGen2_I2C_CmdPreinit();
    break;
  case CddTpsGen2_I2C_Init:
    *pucGoToSt = CDDTPSGEN2_STATE_EE_INIT; //select line from schEE
    break;
  case  CddTpsGen2_I2C_Read_Start:
    CddTpsGen2_I2C_CommandReadStart(pucGoToSt);
    break;
  case  CddTpsGen2_I2C_Read_Status:
    *pucGoToSt = CDDTPSGEN2_STATE_EE_RR_STATUS; //select line from schEE
    break;
  case  CddTpsGen2_I2C_Read_Data:
    CddTpsGen2_I2C_CommandReadData(pucGoToSt);
    break;
  case CddTpsGen2_I2C_Write_Data:
    *pucGoToSt = CDDTPSGEN2_STATE_EE_WRITE_DATA; //select line from schEE
    CddTpsGen2_I2C_CommandWriteData();
    break;
  case CddTpsGen2_I2C_Write_Start:
    *pucGoToSt = CDDTPSGEN2_STATE_EE_WRITE_START; //select line from schEE
    CddTpsGen2_I2C_CmdWriteStart((uint8)CddTpsGen2_I2C_unWriteStartAddress);
    break;
  case CddTpsGen2_I2C_Write_Status:
    *pucGoToSt = CDDTPSGEN2_STATE_EE_RW_STATUS; //select line from schEE
    break;
  case CddTpsGen2_I2C_ControlReset:
    *pucGoToSt = CDDTPSGEN2_STATE_EE_RESET; //select line from schEE
    CddTpsGen2_I2C_CmdReset();
    break;
  default:
    break;
  }
  
  return ((CddTpsGen2_I2C_State == CddTpsGen2_I2C_Idle) || (CddTpsGen2_I2C_State == CddTpsGen2_I2C_NotInit)) ? FALSE : TRUE;
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_I2C_Timeout
///
/// \descr  This function call a timeout callback(failed) in case of eeprom is 
///         stucked while init, reading or writing is in progress
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddTpsGen2_I2C_Timeout(void)
{
  if (CDDTPSGEN2_Para_CHIP_EEPROM_ADDR != 0xFFu)
  {
    switch (CddTpsGen2_I2C_State)
    {
    case CddTpsGen2_I2C_Preinit:
    case CddTpsGen2_I2C_Init:
      CddTpsGen2_I2C_TimeoutInit();
      break;
    case CddTpsGen2_I2C_Read_Start:
    case CddTpsGen2_I2C_Read_Status:
    case CddTpsGen2_I2C_Read_Data:
      CddTpsGen2_I2C_TimeoutRead();
      break;
    case CddTpsGen2_I2C_Write_Data:
    case CddTpsGen2_I2C_Write_Start:
    case CddTpsGen2_I2C_Write_Status:
      CddTpsGen2_I2C_TimeoutWrite();
      break;
    default:
      break;
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_I2C_TimeoutInit
///
/// \descr  The Function increments the EEPROM Init Counter and if it reached
///         the configured threshold it will trigger init failed callback.
///
/// \param  none
///
/// \return none
//-----------------------------------------------------------------------------
STATIC_AL void CddTpsGen2_I2C_TimeoutInit(void)
{
  // Read Timeout Counter did not reached configured threshold?
  if (CddTpsGen2_I2C_ucInitTimeoutCounter < CDDTPSGEN2_I2C_INIT_TIMEOUT)
  {
    // Increment Timeout Read Counter
    CddTpsGen2_I2C_ucInitTimeoutCounter++;
  }
  else
  {
    // Jump into Not Initialized State
    CddTpsGen2_I2C_State = CddTpsGen2_I2C_NotInit;
    // Init Failed Callback Defined?
    CddTpsGen2_I2C_CallbackFunction(CddTpsGen2_I2C_pfnInitFailedClbk);
    // Mark Init Operation as Failed
    CddTpsGen2_I2C_InitStatus = CddTpsGen2_I2C_Failed;
  }
}


//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_I2C_TimeoutRead
///
/// \descr  The Function increments the EEPROM Read Counter and if it reached
///         the configured threshold it will trigger Reset of I2C State Machine
///         and empty the 16 Bytes Read FIFO.
///
/// \param  none
///
/// \return none
//-----------------------------------------------------------------------------
STATIC_AL void CddTpsGen2_I2C_TimeoutRead(void)
{
  // Read Timeout Counter did not reached configured threshold?
  if (CddTpsGen2_I2C_ucReadTimeoutCounter < CDDTPSGEN2_READ_LOOP_TIMEOUT)
  {
    // Increment Timeout Read Counter
    CddTpsGen2_I2C_ucReadTimeoutCounter++;
  }
  else
  {
    // Read Timeout Reached => Trigger Reset I2C State Machine and empty FIFO
    CddTpsGen2_I2C_State = CddTpsGen2_I2C_ControlReset;
    // Read Failed Callback Defined?
    CddTpsGen2_I2C_CallbackFunction(CddTpsGen2_I2C_pfnReadFailedClbk);
    // Mark Read Operation as failed
    CddTpsGen2_I2C_ReadStatus = CddTpsGen2_I2C_Failed;
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_I2C_TimeoutWrite
///
/// \descr  The Function increments the EEPROM Write Counter and if it reached
///         the configured threshold it will trigger Reset of I2C State Machine.
///
/// \param  none
///
/// \return none
//-----------------------------------------------------------------------------
STATIC_AL void CddTpsGen2_I2C_TimeoutWrite(void)
{
  // Write Timeout Counter did not reached configured threshold?
  if (CddTpsGen2_I2C_ucWriteTimeoutCounter < CDDTPSGEN2_WRITE_BYTE_TIMEOUT)
  {
    // Increment Timeout Write Counter
    CddTpsGen2_I2C_ucWriteTimeoutCounter++;
  }
  else
  {
    // Write Timeout Reached => Trigger Reset I2C State Machine
    CddTpsGen2_I2C_State = CddTpsGen2_I2C_ControlReset;
    // Write Failed Callback Defined?
    CddTpsGen2_I2C_CallbackFunction(CddTpsGen2_I2C_pfnWriteFailedClbk);
    // Mark Write Operation as Failed
    CddTpsGen2_I2C_WriteStatus = CddTpsGen2_I2C_Failed;
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen2_GetEEConnectedId
///
/// \descr  The function returns the ID of the MLC connected EEPROM device
///
/// \param  none
///
/// \return uint8
//-----------------------------------------------------------------------------
uint8 CddTpsGen2_GetEEConnectedId(void)
{
  return CddTpsGen2_sDevData.ucEepromId;
}

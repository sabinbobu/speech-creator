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
#include <CddTpsGen3.h>

// module includes (relative to API)
#include <CddTpsGen3_Types.h>
#include <CddTpsGen3_Cfg.h>
#include <CddTpsGen3_Cod.h>
#include <CddTpsGen3_Com.h>


//-----------------------------------------------------------------------------
// Variables
//-----------------------------------------------------------------------------
STATIC_AL tsCddTpsGen3_DevData CddTpsGen3_sDevData;
STATIC_AL boolean CddTpsGen3_boReinitChips = FALSE;

//-----------------------------------------------------------------------------
// Prototypes
//-----------------------------------------------------------------------------
STATIC_AL void CddTpsGen3_DoAddressingMap(tsCddTpsGen3_DevData* psData);

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen3_DoAddressingMap
///
/// \descr  Extract the LmmConfig data from the coding structure and map into
///         a chip global structure the data about : chip ID, chip address,
///         no. of supported devices, no. of connected devices
///
/// \param  psCodingData  : structure where to save chip data
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CddTpsGen3_DoAddressingMap(tsCddTpsGen3_DevData* psData)
{
  uint8  ucChipID = 0U;
  uint8  ucDeviceIdx = 0U;
  uint8  ucDeviceConnected = 0U;
  // Mlc chips physical addresses
  CONST_AL uint8 aucAddress[] = CDDTPSGEN3_ADDRESS_LIST;
  psData->ucBaudRate = CDDTPSGEN3_Para_Get_BAUDRATE;

  for (ucDeviceIdx = 0; ucDeviceIdx < CDDTPSGEN3_MAX_CHIPs; ucDeviceIdx++)
  {
    //suppose the chip is not connected
    psData->aucCodDevID[ucDeviceIdx] = CDDTPSGEN3_ADDR_NOT_CONNECTED;

    // get the chip physical address
    ucChipID = CDDTPSGEN3_Para_Get_CHIP_ID(ucDeviceIdx);

    if ((ucChipID != CDDTPSGEN3_ADDR_NOT_CONNECTED) && ((ucChipID >= CDDTPSGEN3_COD_DEV_ADDR_GEN3_START_ADDR_ID) && (ucChipID <= CDDTPSGEN3_COD_DEV_ADDR_SLAVE_MAX_ID)))
    {
      // the physical address  is the digital mapping of the device ID with the DEVID Byte with Parity
      psData->asMasterSlaveId[ucDeviceConnected].ucPhysicalAddr = aucAddress[ucChipID - CDDTPSGEN3_COD_DEV_ADDR_GEN3_START_ADDR_ID];
      psData->asMasterSlaveId[ucDeviceConnected].boIsMasterId   = FALSE;

      psData->aucCodDevID[ucDeviceConnected] = ucDeviceIdx;
      ucDeviceConnected++;

      //!!!EEPROM not supported for GEN3
      // TODO GEN3 : in case the EEPROM is connected to a MLC device not addressed in coding data, skip the usage of EEPROM functionality

    }
    else if ((ucChipID != CDDTPSGEN3_ADDR_NOT_CONNECTED) && ((ucChipID >= (CDDTPSGEN3_COD_DEV_ADDR_GEN3_START_ADDR_ID + CDDTPSGEN3_COD_DEV_ADDR_MASTER_OFFSET_ID)) && (ucChipID <= CDDTPSGEN3_COD_DEV_ADDR_MASTER_MAX_ID)))
    {
      psData->asMasterSlaveId[ucDeviceConnected].ucPhysicalAddr = aucAddress[ucChipID - CDDTPSGEN3_COD_DEV_ADDR_GEN3_START_ADDR_ID - CDDTPSGEN3_COD_DEV_ADDR_MASTER_OFFSET_ID];
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
/// \brief  CddTpsGen3_Init
///
/// \descr  Init function of Tps92662/3 chip type,  2nd generation
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void CddTpsGen3_Init(void)
{
  //do remapping of addresses
  CddTpsGen3_DoAddressingMap(&CddTpsGen3_sDevData);
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen3_Cycle
///
/// \descr  Cycle function of Tps92664/5/7 chip type, 3rd generation
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void CddTpsGen3_Cycle(void)
{
  return;
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen3_SetDutyCycle_1_1024
///
/// \descr  This functions sets the duty cycle for each pixel and check sfor minimun
///         PWM value
///
/// \param  ucChipIdx
/// \param  unDuty
///
/// \return void
//-----------------------------------------------------------------------------
void CddTpsGen3_SetDutyCycle_1_1024(const uint8 ucChipIdx, uint16* punDuty)
{
  if (ucChipIdx < CDDTPSGEN3_MAX_CHIPs)
  {
    for (uint8_fast ucPxl = 0u; ucPxl < CDDTPSGEN3_TPS9266x_MAX_SWITCHS_PER_DEVICE; ucPxl++)
    {
      // if pixel is operated at PWM values under 0.5%, switch OFF pixel
      if (punDuty[ucPxl] < CDDTPSGEN3_MIN_PWM_THD)
      {
        punDuty[ucPxl] = CDDTPSGEN3_MIN_PWM_VAL;
      }
      else
      {
        // don't perform any action
      }
    }

    CddTpsGen3_SetWIDTHReg(ucChipIdx, punDuty);
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen3_pfGetDevData
///
/// \descr  This function returns coding data structure for GEN3
///
/// \param  -
///
/// \return tsCddTpsGen3_DevData *
//-----------------------------------------------------------------------------
tsCddTpsGen3_DevData* CddTpsGen3_pfGetDevData(void)
{
  return &CddTpsGen3_sDevData;
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen3_GetPixelFault
///
/// \descr  This function collects the electrical fault for the current device
///
/// \param  ucChipIdx
///
/// \return uint16
//-----------------------------------------------------------------------------
uint16 CddTpsGen3_GetPixelFault(uint8 ucChipIdx)
{
  uint16 unPxlFault_Bit = 0u;
  tuCddTpsGen3_RxELEFAULT uLEDFault;

  uint16 unPxlFaultOpen = 0u;
  uint16 unPxlFaultShort = 0u;

  if (ucChipIdx < CDDTPSGEN3_MAX_CHIPs)
  {

    CddTpsGen3_GetELEFAULTReg(ucChipIdx, &uLEDFault);

    unPxlFaultOpen  = ((uint16)((uint16)uLEDFault.ucRxByte[0] << 0u) & 0x00FFu);             // save the FAULT_OPEN_OR_DRVL value for the [8:1]  LEDs
    unPxlFaultOpen |= ((uint16)((uint16)uLEDFault.ucRxByte[1] << 8u) & 0xFF00u);             // save the FAULT_OPEN_OR_DRVH value for the [16:9] LEDs

    unPxlFaultShort  = ((uint16)((uint16)uLEDFault.ucRxByte[2] << 0u) & 0x00FFu);            // save the FAULT_SHORTL value for the [8:1]  LEDs
    unPxlFaultShort |= ((uint16)((uint16)uLEDFault.ucRxByte[3] << 8u) & 0xFF00u);            // save the FAULT_SHORTH value for the [16:9] LEDs

    unPxlFault_Bit = unPxlFaultOpen | unPxlFaultShort;    /* compatibility with GEN2 : pixel defect is considered when any short or open happens */
  }

  return unPxlFault_Bit;
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen3_GetComFault
///
/// \descr  This function collects the communication error status for the 
///         current device
///
/// \param  ucChipIdx
///
/// \return void
//-----------------------------------------------------------------------------
boolean CddTpsGen3_GetComFault(const uint8_fast ucChipIdx)
{
  boolean boDevComFault = FALSE;

  if (ucChipIdx < CDDTPSGEN3_MAX_CHIPs)
  {
    boDevComFault = CddTpsGen3_GetComFAULT(ucChipIdx);
  }
  return boDevComFault;
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen3_GetCrcFault
///
/// \descr  This function collects the CRC error status for the 
///         current device
///
/// \param  ucChipIdx
///
/// \return void
//-----------------------------------------------------------------------------
boolean CddTpsGen3_GetCrcFault(const uint8_fast ucChipIdx)
{
  boolean boCrcFault = FALSE;

  if (ucChipIdx < CDDTPSGEN3_MAX_CHIPs)
  {
    boCrcFault = CddTpsGen3_GetCrcFAULT(ucChipIdx);
  }
  return boCrcFault;
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen3_GetSensorInfo
///
/// \descr  This function collects the adc results status for the 
///         current device
///
/// \param  ucChipIdx
/// \param  psSensorData
///
/// \return void
//-----------------------------------------------------------------------------
void CddTpsGen3_GetSensorInfo(const uint8_fast ucChipIdx, tsCddMlc_SensorData* psSensorData)
{
  boolean boComFault = FALSE;
  tuCddTpsGen3_RxADC uADCInfo;

  if (ucChipIdx < CDDTPSGEN3_MAX_CHIPs)
  {
    CddTpsGen3_GetADCReg(ucChipIdx, &uADCInfo);
    boComFault = CddTpsGen3_GetComFAULT(ucChipIdx);

    psSensorData->ucADC1Value = uADCInfo.ucRxByte[0];
    psSensorData->ucADC2Value = uADCInfo.ucRxByte[1];

    psSensorData->eQlty = (boComFault != FALSE) ? SENSOR_QLTY_INVALID : (CddTpsGen3_GetMuxCmdCompleted() != FALSE) ? SENSOR_QLTY_VALID : SENSOR_QLTY_SNA;
  }
}

//-----------------------------------------------------------------------------
/// \brief CddTpsGen3_ReinitSch
///
/// \descr This function set the command status for chips(scheduler) based on
///        the request from upper layer
///
/// \param  boCom
///
/// \return void
//-----------------------------------------------------------------------------
void CddTpsGen3_ReinitSch(boolean boCom)
{
  CddTpsGen3_boReinitChips = boCom;
}

//-----------------------------------------------------------------------------
/// \brief CddTpsGen3_ResetScheduler
///
/// \descr This function restart the scheduler at first index while initialization 
///        is completed and command for reset is requested
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CddTpsGen3_ResetScheduler(void)
{
  boolean boRetVal = FALSE;
  //check for chips initialization
  if (CddTpsGen3_GetInitCmdCompleted() != FALSE)
  {
    boRetVal = CddTpsGen3_boReinitChips;
  }
  return boRetVal;
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsGen3_GetInitStatus
///
/// \descr  This function returns the initialization status of all connected chips
///
/// \param  -void
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CddTpsGen3_GetInitStatus(void)
{
  return CddTpsGen3_GetInitCmdCompleted();
}

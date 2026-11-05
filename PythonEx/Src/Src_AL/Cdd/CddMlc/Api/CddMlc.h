//*****************************************************************************
// (C) Marelli Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Marelli Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Marelli Automotive Lighting Reutlingen GmbH.
//*****************************************************************************
//-----------------------------------------------------------------------------
/// \file  CddMlc.h
///
/// \brief
///
//-----------------------------------------------------------------------------
#ifndef CDD_MLC_2024_04_01_H
#define CDD_MLC_2024_04_01_H

//-----------------------------------------------------------------------------
// version
//-----------------------------------------------------------------------------
#define CDDMLC_VERSION_MAJOR   3
#define CDDMLC_VERSION_MINOR   1
#define CDDMLC_VERSION_PATCH   0

//-----------------------------------------------------------------------------
// release notes
//-----------------------------------------------------------------------------
// 0.0.0  Initial version of generic implementation for matrix module
// 0.0.1  Added Reinit Matrix command via RTE
//        SNA for ADCs is present
// 1.0.0  Minor updates for setting of mounted devices in coding function
//        LINT and QA-C fixed
// 1.1.0  EEPROM for TPS92662 has been implemented, remain timeout to be
//        implemented
// 2.0.0  EEPROM for TPS92662 is implemented, including timeout
// 3.0.0  CRC/PWR cycle/Init Status have been implemented
// 3.1.0  CRC error fixed, added also under Simulation Hook


//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <AL_Helper.h>
#include <CddMlc_Types.h>


//-----------------------------------------------------------------------------
// Types
//-----------------------------------------------------------------------------

// target values for all devices
typedef struct
{
  uint16 aunDutyCycle_1_1024[CDDMLC_CFG_MAX_CHIPS][CDDMLC_TPSGENx_MAX_SWITCHES_PER_DEVICE];
} tsCddMlcTarget;

typedef struct
{
  uint16 unSwitchFault_Bit;
}tsSwitchFault;

typedef struct
{
  boolean boComFault[CFG_MLC_Chip_Cnt];
}tsChipComFault;

//Buffer which stores the faulty LED values for each MLC device
//typedef tsSwitchFault tasMlcLedFault[CFG_MLC_Chip_Cnt];
//typedef tsChipComFault aboMlcChipComFault[CFG_MLC_Chip_Cnt];

// target values for all devices
typedef struct
{
  boolean boInitStatus; //init drivers status
  boolean boVccXFault; //matrix supply fault status
  boolean boBusFault;  //uart broken (bus off)
  boolean aboCrcFault[CFG_MLC_Chip_Cnt];
  uint8   ucPowerOnReset; //power chip is lost
  boolean aboComFault[CFG_MLC_Chip_Cnt]; //uart communication with chips is lost
  tsSwitchFault asSwitchFault[CFG_MLC_Chip_Cnt]; //leds faults
  tsCddMlc_SensorData asSensorData[CFG_MLC_Chip_Cnt]; //ADC temperature and binning
}tsCddMlcStatus;

//-----------------------------------------------------------------------------
// Prototypes
//-----------------------------------------------------------------------------

void    CddMlc_SetTarget(uint8 ucChipConnected, tsCddMlcTarget* psTargetPWM);
void    CddMlc_GetStatus(uint8 ucMtxCfgType, tsCddMlcStatus *psStatus);
void    CddMlc_CheckReinit(uint8 ucMtxCfgType, boolean boCmdStatus);

boolean CddMlc_CheckPowerUp(void);
boolean CddMlc_IsMlcPowered(void);

boolean CddMlc_Cod_UartGetConfig(uint8 ucDevUartCfg, uint8* pucBaudRate, uint8 *pucMountedDev);

//-----------------------------------------------------------------------------
// Access to functions
//-----------------------------------------------------------------------------
//void CddMlcUart_SendReceived_Irq(void);
#define CDDMLC_IS_DEVICE_POWERED()   CddMlc_IsMlcPowered()


#endif // CDD_MLC_2024_04_01_H

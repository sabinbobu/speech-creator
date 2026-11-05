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
/// \file  CddTpsGen2.h
///
/// \brief
///
//-----------------------------------------------------------------------------
#ifndef CDD_TPS_GEN2_2024_01_30_H_
#define CDD_TPS_GEN2_2024_01_30_H_

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <Std_Types.h>

#include <CddTpsGen2_Types.h>
#include <CddMlc_Types.h>

//-----------------------------------------------------------------------------
// version
//-----------------------------------------------------------------------------
#define CDDTPSGEN2_VERSION_MAJOR   3
#define CDDTPSGEN2_VERSION_MINOR   2
#define CDDTPSGEN2_VERSION_PATCH   0


//-----------------------------------------------------------------------------
// release notes
//-----------------------------------------------------------------------------
// 0.0.0  Initial version of generation 2 (TPS92662/3) implementation
// 0.0.1  Restart scheduler mechanism in case a command for reinit is received 
//        from upper layer is ready.
//        SNA for ADC is used.
// 0.1.0  EEPROM has been implemented, timeout n/a
// 1.0.0  EEPROM implementation ready, including timeout
// 2.0.0  startup activation depending on supply voltage of device scheduler
//        CRC error handling                             
//        PWR is not available - tbc with other projects 
// 3.0.0  Dynamic PWM frequency and WDG selection based on System Clock
// 3.1.0  SlewRate set according to SYRS requirement to SLOW slewrate
// 3.2.0  CRC error fixed 

//-----------------------------------------------------------------------------
// open issues
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Declaration or definitions of functions
//-----------------------------------------------------------------------------
void    CddTpsGen2_Init(void);
void    CddTpsGen2_Cycle(void);

void    CddTpsGen2_SetDutyCycle_1_1024(const uint8 ucChipIdx, uint16* punDuty);
uint16  CddTpsGen2_GetPixelFault(uint8 ucChipIdx);
boolean CddTpsGen2_GetComFault  (const uint8_fast ucChipIdx);
boolean CddTpsGen2_GetCrcFault  (const uint8_fast ucChipIdx);
void    CddTpsGen2_GetSensorInfo(const uint8_fast ucChipIdx, tsCddMlc_SensorData* psSensorData);
uint8   CddTpsGen2_GetPWRStatus (void);
boolean CddTpsGen2_GetInitStatus(void);

void    CddTpsGen2_ReinitSch(boolean boCom);
boolean CddTpsGen2_ResetScheduler(void);


tCddTpsGen2_I2C_eStatus* CddTpsGen2_I2C_StartInit(tCddTpsGen2_I2C_pFnct pfnInitSuccessClbk, tCddTpsGen2_I2C_pFnct pfnInitFailedClbk);
tCddTpsGen2_I2C_eStatus* CddTpsGen2_I2C_ReadEeprom(uint8 *ucData_List, uint16 unStartAddress, uint16 unLength, tCddTpsGen2_I2C_pFnct pfnReadSuccessClbk, tCddTpsGen2_I2C_pFnct pfnReadFailedClbk);
tCddTpsGen2_I2C_eStatus* CddTpsGen2_I2C_WriteEeprom(uint8 *ucData_List, uint16 unStartAddress, uint16 unLength, tCddTpsGen2_I2C_pFnct pfnWriteSuccessClbk, tCddTpsGen2_I2C_pFnct pfnWriteFailedClbk);
void CddTpsGen2_I2C_Timeout(void);
uint8 CddTpsGen2_GetEEConnectedId(void);

#endif // CDD_TPS_GEN2_2024_01_30_H_

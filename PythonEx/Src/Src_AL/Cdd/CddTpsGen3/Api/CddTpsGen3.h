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
/// \file  CddTpsGen3.h
///
/// \brief
///
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
///
//-----------------------------------------------------------------------------
#ifndef CDD_TPS_GEN3_2024_02_05_H
#define CDD_TPS_GEN3_2024_02_05_H

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <Std_Types.h>

#ifndef UNIT_TEST
#include <CddMlc_Types.h>
#else
#include <Test/Test_Ext.h>
#endif

//-----------------------------------------------------------------------------
// version
//-----------------------------------------------------------------------------
#define CDDTPSGEN3_VERSION_MAJOR   2
#define CDDTPSGEN3_VERSION_MINOR   2
#define CDDTPSGEN3_VERSION_PATCH   0


//-----------------------------------------------------------------------------
// release notes
//-----------------------------------------------------------------------------
// 0.0.0  -Initial version of generation 3 (TPS92664/5/7) implementation
// 0.0.1  -Restart scheduler mechanism in case a command for reinit is received 
//        from upper layer is ready.
//        -SNA for ADC is used.
// 1.0.0  startup activation depending on supply voltage of device scheduler
//        CRC error handling                             
//        PWR is not available - tbc with other projects 
// 2.0.0  Dynamic PWM frequency and WDG selection based on System Clock
// 2.1.0  Read commands added for checking slewrate and pwm tick config registers
// 2.2.0  CRC error fixed

//-----------------------------------------------------------------------------
// open issues
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Declaration or definitions of functions
//-----------------------------------------------------------------------------
void    CddTpsGen3_Init(void);
void    CddTpsGen3_Cycle(void);

void    CddTpsGen3_SetDutyCycle_1_1024(const uint8 ucChipIdx, uint16* punDuty);
uint16  CddTpsGen3_GetPixelFault(uint8 ucChipIdx);
boolean CddTpsGen3_GetComFault  (const uint8_fast ucChipIdx);
boolean CddTpsGen3_GetCrcFault  (const uint8_fast ucChipIdx);
void    CddTpsGen3_GetSensorInfo(const uint8_fast ucChipIdx, tsCddMlc_SensorData* psSensorData);
uint8   CddTpsGen3_GetPWRStatus (void);
boolean CddTpsGen3_GetInitStatus(void);

void    CddTpsGen3_ReinitSch(boolean boCom);
boolean CddTpsGen3_ResetScheduler(void);

#endif // CDD_TPS_GEN3_2024_02_05_H

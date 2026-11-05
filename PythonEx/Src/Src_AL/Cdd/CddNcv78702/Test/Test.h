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
/// \file  Test.h
///
/// \brief This file contains functions prototypes of the tested module, 
///        including functions parameters and global variables
///
//-----------------------------------------------------------------------------
#ifndef TEST_2023_08_25_H_
#define TEST_2023_08_25_H_

//=============================================================================
// Includes
//=============================================================================
#include <AL_Helper.h>
#include <CddNcv78702.h>
#include <../Gen/CddNcv78702_Com.h>
#include <../Gen/CddNcv78702_Sched.h>
#include <string.h>

//=============================================================================
// Typedefs
//=============================================================================
// SPI schedule table entry datatype
typedef struct tCddNcv78702_SpiSchedTable
{
  uint8         ucNextEntry;  // index of next schedule table entry
  uint8         ucAction;     // index of action function done after Rx --> TODO change as function pointer ?
  uint16        unCmd;        // Read/Write Command to send
  uint16        unAddr;       // SPI address (combination of low and high nibble)
  const uint16* punTx;        // SPI control register data for transmission     - offset related to 1st address of stuct
  uint16*       punRx;        // SPI status register data for reception         - offset related to 1st address of stuct
} tCddNcv78702_SpiSchedTable;


//=============================================================================
// Defines
//=============================================================================


//=============================================================================
// Module global variables
//=============================================================================
//CddNcv78702_Com.c
extern uint16 CddNcv78702_unSchedIx;
extern uint16 CddNcv78702_aunDummy;
extern tCddNcv78702_DataMirror CddNcv78702_DataMirror;
extern uint16 CddNcv78702_aunZero;
extern tCddNcv78702_SpiSchedTable aCddNcv78702_SpiSchedTable[CDDNCV78702_Cfg_SpiSchedTableLen];
extern boolean CddNcv78702_boSpiValid_Reg0x0A;
extern uint16 CddLed78702_unRestartCnt;

//=============================================================================
// Module function declarations
//=============================================================================
//CddNcv78702.h
extern uint32  CddNcv78702_Init(void);
extern void    CddNcv78702_Shutdown(void);
extern void    CddNcv78702_SetBoosterVoltage(const uint32 ulIdx, const uint16 unVBoostTarget_mV);

extern boolean CddNcv78702_IsReset(const uint32 ulIdx);
extern boolean CddNcv78702_IsSpiError(const uint32 ulIdx);
extern boolean CddNcv78702_IsThermalShutDown(const uint32 ulIdx);
extern boolean CddNcv78702_IsThermalWarning(const uint32 ulIdx);

extern uint32  CddNcv78702_SpiTx(const uint16 unIx);
extern void    CddNcv78702_SpiRx(const uint16 unIx, const uint32 ulData);

//CddNcv78702_Com.h
extern void    CddNcv78702_SetBoostVsetpoint(const uint8 ucBoostVsetpoint);
extern void    CddNcv78702_SetBoostBstSyncDuty(const uint16  unBstSyncDuty_1_32768);
extern void    CddNcv78702_SetBoostEnableGpio(const boolean boBoostEnable);
extern void    CddNcv78702_SetBoostSleep(void);
extern uint16  CddNcv78702_CalculateAndAddOddParityBit(const uint16 unCmd, const uint16 unAddr, const uint16 unData);
extern boolean CddNcv78702_StAction(const uint8 ucAction);
extern boolean CddNcv78702_GetReg0x0A(tCddNcv78702_Reg0x0A* pReg0x0A);
extern void    CddNcv78702_SetBoostOverVoltageThr(void);

//=============================================================================
// Module function parameter stubs
//=============================================================================
//CddNcv78702.h
uint32  CddNcv78702_SetBoosterVoltage_Param1;
uint16  CddNcv78702_SetBoosterVoltage_Param2;
uint16  CddNcv78702_SpiTx_Param1;
uint16  CddNcv78702_SpiRx_Param1;
uint32  CddNcv78702_SpiRx_Param2;

//CddNcv78702_Com.h
uint8   CddNcv78702_SetBoostVsetpoint_Param1;
uint16  CddNcv78702_SetBoostBstSyncDuty_Param1;
boolean CddNcv78702_SetBoostEnableGpio_Param1;
uint16  CddNcv78702_CalculateAndAddOddParityBit_Param1;
uint16  CddNcv78702_CalculateAndAddOddParityBit_Param2;
uint16  CddNcv78702_CalculateAndAddOddParityBit_Param3;
uint8   CddNcv78702_StAction_Param1;

//=============================================================================
// Module function return value stubs
//=============================================================================
//CddNcv78702.h
uint32  CddNcv78702_SpiTx_RetVal;
uint16  CddNcv78702_CalculateAndAddOddParityBit_RetVal;
boolean CddNcv78702_StAction_RetVal;

//=============================================================================
// Global variable stubs
//=============================================================================

// backups of initialized structs
tCddNcv78702_DataMirror    Test_DataMirror_Back;
tCddNcv78702_SpiSchedTable Test_SpiSchedTable_Back[CDDNCV78702_Cfg_SpiSchedTableLen];



#endif // TEST_2023_08_25_H_

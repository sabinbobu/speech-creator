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

// Headers of the Module

#include <CddTle94x1.h>
#include <CddTle94x1_Cfg.h>
#include <CddTle94x1_Com.h>
#include <CddTle94x1_Regs.h>
#include <CddTle94x1_Types.h>

// Headers of other modules
#include <CddSbc_Types.h>
#include <CddSpi.h>
#include <Util_Time.h>

//=============================================================================
// Typedefs
//=============================================================================

//=============================================================================
// Defines
//=============================================================================

//=============================================================================
// Module global variables
//=============================================================================
extern volatile uint32           CddTle94x1_ulTSDHook_Activ_Val;

extern tsCddTle94x1_DataMirror   CddTle94x1_sDataMirror;
extern tsCddTle94x1_ErrorState   CddTle94x1_sErrorType;
extern tsCddSbc_SpiScheduleQueue CddSbc_asSpiScheduleQueue[CDDSBC_CFG_MAX_SPI_SCHED_QUEUE];
extern uint8                     CddSbc_ucQueueWriteIndex;
extern uint8                     CddSbc_ucQueueReadIndex;
extern uint8                     CddSbc_ucQueueTXIndex;
extern uint16                    CddTle94x1_unErrorSequenceCounter;
extern uint8                     CddTle94x1_ucSUP_STAT_0_POR;
extern uint8                     CddTle94x1_ucWK_STAT_0_CANWU;
extern boolean                   CddTle94x1_boStatusWdgReset;

#if ((CDDSBC_CFG_CYCLIC_OPERATION == STD_ON) && (CDDSBC_CFG_WK_INPUT == STD_ON))
extern uint8                     CddTle94x1_ucWK_STAT_0_WK_WU;
#endif

extern teCddTle94x1_MsgType      CddTle94x1_eDefaultMsg;
extern uint8                     Mt_CddSpi_ucState;
extern uint8                     CddTle94x1_ucDEV_STAT_DEV_STAT;
extern uint8                     CddTle94x1_ucTHERMO_STAT_TSD2;
extern uint8                     CddTle94x1_ucSUP_STAT_0_VCC1_UV;
extern uint8                     CddTle94x1_ucSBCResetReason;




//=============================================================================
// Module function declarations
//=============================================================================
extern boolean                   CddTle94x1_WriteClearReg(uint8 ucAddress, uint16 unDataField);
extern uint16                    CddTle94x1_ReadReg(uint8 ucAddress);
extern void                      CddTle94x1_SetCanMode(uint8 ucSbcCanChannel, uint8 ucCanMode);
extern void                      CddTle94x1_SetSleepMode(void);
extern void                      CddSbc_InsertDefaultMessage(void);
extern void                      CddTle94x1_SpiRx(uint16 unIx, uint32 ulData);
extern uint32                    CddTle94x1_SpiTx(uint16 unIx);
extern boolean                   CddTle94x1_InsertNewSchedEntry(uint8 ucAddress, uint8 ucData, uint8 ucCommand, pfReadClBck ClbckFunction);
extern boolean                   CddTle94x1_Save_WK_STAT_0();
extern boolean                   CddTle94x1_Save_SUP_STAT_0();
extern boolean                   CddTle94x1_InitStatRead(void);
extern void                      CddTle94x1_InitSettings(void);
extern void                      CddTle94x1_CbkSetCanMode(uint32 ulData, uint16 unSentVal);
extern void                      CddTle94x1_CbkGetCanMode(uint32 ulData, uint16 unSentVal);
extern void                      CddTle94x1_CbkGetBusState(uint32 ulData, uint16 unSentVal);
extern void                      CddTle94x1_CbkGetSupState0(uint32 ulData, uint16 unSentVal);

#if (CDDSBC_CFG_VCC2_OPERATION == STD_ON)
extern void                      CddTle94x1_SetVCC2(uint8 ucCmd);
extern void                      CddTle94x1_CbkSetVCC2(uint32 ulData, uint16 unSentVal);
extern void                      CddTle94x1_Short_To_VBAT(void);
extern void                      CddTle94x1_Reset_Short_To_VBAT(void);
extern void                      CddTle94x1_Short_To_GND(void);
extern void                      CddTle94x1_Reset_Short_To_GND(void);
extern void                      CddTle94x1_ReadThermStatReg(void);
extern void                      CddTle94x1_CbkReadThermStatReg(uint32 ulData, uint16 unSentVal);
extern void                      CddTle94x1_Thermal_Shutdown(void);
#endif

#if ((CDDSBC_CFG_CYCLIC_OPERATION == STD_ON) && (CDDSBC_CFG_WK_INPUT == STD_ON))
extern void                      CddTle94x1_CbkGetWakeUpStatus(uint32 ulData, uint16 unSentVal);
#endif

extern void                      CddTle94x1_CbkSetCanMode(uint32 ulData, uint16 unSentVal);
extern void                      CddTle94x1_CbkSetWDCtrl(uint32 ulData, uint16 unSentVal);
extern void                      CddTle94x1_ErrorSequenceCounterInc(void);
extern void                      CddTle94x1_ErrorSequenceCounterClear(void);
extern boolean                   CddTle94x1_ValidateCanMode(uint8 ucCanMode);

#if ((CDDSBC_CFG_CYCLIC_OPERATION == STD_ON) && (CDDSBC_CFG_WK_INPUT == STD_ON))
extern boolean                   CddTle94x1_GetWakeUpStatus(void);
#endif

extern void                      CddTle94x1_StoreSBCResetReason(void);
extern void                      CddTle94x1_SetWdgWithSingleOperation(void);
extern void                      CddTle94x1_GetWatchdogFlag(void);
extern void                      CddTle94x1_CbkSetPWM(uint32 ulData, uint16 unSentVal);

//=============================================================================
// Module function parameter stubs
//=============================================================================
uint8  CddTle94x1_SetVCC2_Param1;
uint32 CddTle94x1_CbkSetVCC2_Param1;
uint16 CddTle94x1_CbkSetVCC2_Param2;
uint32 CddTle94x1_CbkReadThermStatReg_Param1;
uint16 CddTle94x1_CbkReadThermStatReg_Param2;
//=============================================================================
// Module function return value stubs
//=============================================================================

//=============================================================================
// Module static variables inside functions 
//=============================================================================
boolean                          boInsertStatus;
TIMER                            ulDebounceStartTime;
boolean                          boTimerInitialized;

#endif // TEST_2023_08_25_H_

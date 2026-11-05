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
#include "AL_Helper.h"

// Headers of the Module
#include <CddTpsGen2.h>
#include <CddTpsGen2_Cb.h>
#include <../Gen/CddTpsGen2_Com.h>
#include <../Cfg/CddTpsGen2_Cfg.h>
#include <../Cfg/CddTpsGen2_RoutCfg.h>
#include <../Gen/CddTpsGen2_Sched.h>

//=============================================================================
// Defines
//=============================================================================
/* 1 */  #define CDDTPSGEN2_MPHASE_Tx           &CddTpsGen2_DataMirror.CtrlTx.RegMPHASE[0].ucByte[0]
/* 2 */  #define CDDTPSGEN2_MWIDTH_Tx           &CddTpsGen2_DataMirror.CtrlTx.RegMWIDTH[0].ucByte[0]
/* 3 */  #define CDDTPSGEN2_STRINGS_Tx          &CddTpsGen2_DataMirror.CtrlTx.RegSTRINGS[0].ucByte[0] 
/* 4 */  #define CDDTPSGEN2_SYSCFG_DEFAULT_Tx   &CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG_DEFAULT[0].ucRaw
/* 5 */  #define CDDTPSGEN2_SYSCFG_Tx           &CddTpsGen2_DataMirror.CtrlTx.RegSYSCFG[0].ucByte[0]
/* 6 */  #define CDDTPSGEN2_ADCID_Tx            &CddTpsGen2_DataMirror.CtrlTx.RegADCID[0].ucRaw
/* 7 */  #define CDDTPSGEN2_SOFTSYNC_Tx         &CddTpsGen2_DataMirror.CtrlTx.RegSOFTSYNC[0].ucRaw
/* 8 */  #define CDDTPSGEN2_I2CCFG_Tx           &CddTpsGen2_DataMirror.CtrlTx.RegI2CCfg[0].ucByte[0]
/* 9 */  #define CDDTPSGEN2_ELECFAULTS_Tx       &CddTpsGen2_DataMirror.CtrlTx.RegELEFAULT[0].ucByte[0]

/* 1 */  #define CDDTPSGEN2_I2CSTATUS_Rx        &CddTpsGen2_DataMirror.StatRx.RegI2CStatus.ucByte[0]
/* 2 */  #define CDDTPSGEN2_ICID_Rx             &CddTpsGen2_DataMirror.StatRx.RxICID[0].ucRxByte[0]
/* 3 */  #define CDDTPSGEN2_SYSCFG_Rx           &CddTpsGen2_DataMirror.StatRx.RxSYSCFG[0].ucRxByte[0]
/* 4 */  #define CDDTPSGEN2_PHASES_Rx           &CddTpsGen2_DataMirror.StatRx.RxPHASES[0].ucRxByte[0]
/* 5 */  #define CDDTPSGEN2_CFGLEDS_Rx          &CddTpsGen2_DataMirror.StatRx.RxCFGLEDS[0].ucRxByte[0]
/* 6 */  #define CDDTPSGEN2_PWMS_Rx             &CddTpsGen2_DataMirror.StatRx.RxPWMS[0].ucRxByte[0]
/* 7 */  #define CDDTPSGEN2_ELEFAULT_Rx         &CddTpsGen2_DataMirror.StatRx.RxELEFAULT[0].ucRxByte[0]
/* 8 */  #define CDDTPSGEN2_CLR_ELEFAULT_Rx     &CddTpsGen2_DataMirror.StatRx.RxCLR_ELEFAULT[0].ucRxByte[0]
/* 9 */  #define CDDTPSGEN2_ADC_Rx              &CddTpsGen2_DataMirror.StatRx.RxADC[0].ucRxByte[0]
/* 10 */ #define CDDTPSGEN2_CONFIG1_Rx          &CddTpsGen2_DataMirror.StatRx.RxCONFIG1[0].ucRxByte[0]
/* 11 */ #define CDDTPSGEN2_CONFIG2_Rx          &CddTpsGen2_DataMirror.StatRx.RxCONFIG2[0].ucRxByte[0]

/* 1 */  #define CDDTPSGEN2_I2CTICK_EETx        &CddTpsGen2_DataMirrorEE.CtrlTx.TxI2CTICK.ucRaw
/* 2 */  #define CDDTPSGEN2_I2C_STARTCMD_EETx   &CddTpsGen2_DataMirrorEE.CtrlTx.TxsI2CSEQCFG.ucByte[0]
/* 3 */  #define CDDTPSGEN2_I2C_DATA_EETx       &CddTpsGen2_DataMirrorEE.CtrlTx.TxI2CDAT.ucRaw
/* 3 */  #define CDDTPSGEN2_I2C_SYSCFG_EETx     &CddTpsGen2_DataMirrorEE.CtrlTx.TxSYSCFGEE.ucRaw

/* 1 */  #define CDDTPSGEN2_ACK_EERx            &CddTpsGen2_DataMirrorEE.StatRx.RxACK
/* 2 */  #define CDDTPSGEN2_I2C_STAT_EERx       &CddTpsGen2_DataMirrorEE.StatRx.RxI2CSTAT.ucRxByte[0]
/* 3 */  #define CDDTPSGEN2_I2C_DATA_EERx       &CddTpsGen2_DataMirrorEE.StatRx.RxI2CDATA.ucRxByte[0]

#define CDDTPSGEN2_BROADCAST1_ADCID_Rx   &CddTpsGen2_BroadcastData.RxBrADCID.ucRxByte[0]
#define CDDTPSGEN2_BROADCAST2_SYSCFG_Rx  &CddTpsGen2_BroadcastData.RxBrSYSCFG.ucRxByte[0]
#define CDDTPSGEN2_Zero_Tx               &CddTpsGen2_aucZero[0]
#define CDDTPSGEN2_Dummy_Rx              &CddTpsGen2_ucDummy[0]
//=============================================================================
// Typedefs
//=============================================================================
typedef struct tsCddTpsGen2_UartSchedTable
{
  sint8 scNextEntry;                //offset to next scheduler table entry
  uint8 ucAction;                   // index of action function done after Rx
  teGen2_DynCmdType  eDynCmd;       // dynamic command type evaluation
  uint8 ucCmd;                      // read/write command to send
  uint8 ucRegAddr;                  // device register address
  uint8 *pucTx;                     // control register data for transmission
  uint8 ucTxSize;                   // size of Tx Buffer command data
  uint8 *pucRx;                     // status register data for reception
  uint8 ucRxSize;                   // size of Rx Buffer received data
} tsCddTpsGen2_UartSchedTable;


//=============================================================================
// Module global variables
//=============================================================================
extern tsCddTpsGen2_DevData CddTpsGen2_sDevData;
extern uint8     CddTpsGen2_ucSchedIx;
extern uint8     CddTpsGen2_ucChipIdx;
extern uint8     CddTpsGen2_ucChipIdx_MuxCmd;
extern uint8     CddTpsGen2_aucTxBuffer[CDDTPSGEN2_MAX_CMD_LENGTH];
extern uint8     CddTpsGen2_ucPowerOnReset_Bit;
extern uint8     CddTpsGen2_ucSchedIxEE;
extern uint8     CddTpsGen2_ucChipIdx_EE;
extern boolean   CddTpsGen2_boReinitChips;
extern boolean   CddTpsGen2_aboComStatus[CFG_MAX_NO_OF_MLC];
extern boolean   CddTpsGen2_aboCrcStatus[CFG_MAX_NO_OF_MLC];
extern boolean   CddTpsGen2_boMuxCmdCompleted;
extern boolean   CddTpsGen2_boInitCompleted;

extern tsCddTpsGen2_UartSchedTable  CddTpsGen2_asUartSchedTable[];
extern tsCddTpsGen2_DataMirror      CddTpsGen2_DataMirror;
extern tsCddTpsGen2_DataMirrorEE    CddTpsGen2_DataMirrorEE;
extern tsCddTpsGen2_BrCmd           CddTpsGen2_BroadcastData;
extern uint8                        CddTpsGen2_ucDummy[CFG_MAX_NO_OF_MLC];
extern uint8                        CddTpsGen2_aucZero[CFG_MAX_NO_OF_MLC];

extern tsCddTpsGen2_DevData CddTpsGen2_sDevData;
extern boolean CddTpsGen2_boReinitChips ;

extern tCddTpsGen2_I2C_pFnct CddTpsGen2_I2C_pfnInitSuccessClbk;        // Init Success Callback pointer
extern tCddTpsGen2_I2C_pFnct CddTpsGen2_I2C_pfnInitFailedClbk;         // Init Failed Callback pointer
extern tCddTpsGen2_I2C_pFnct CddTpsGen2_I2C_pfnWriteSuccessClbk;       // Write Success Callback pointer
extern tCddTpsGen2_I2C_pFnct CddTpsGen2_I2C_pfnWriteFailedClbk;        // Write Failed Callback pointer
extern tCddTpsGen2_I2C_pFnct CddTpsGen2_I2C_pfnReadSuccessClbk;        // Read Success Callback pointer
extern tCddTpsGen2_I2C_pFnct CddTpsGen2_I2C_pfnReadFailedClbk;         // Read Failed Callback pointer

extern uint8* CddTpsGen2_I2C_ucPtrReadData ;                       // Pointer to data buffer used at read operation
extern uint8* CddTpsGen2_I2C_ucPtrWriteData;                      // Pointer to data buffer used at write operation

extern uint16 CddTpsGen2_I2C_unWriteStartAddress;                       // Start Address for Write operation
extern uint16 CddTpsGen2_I2C_unWriteEndAddress;                         // End Address for Write Operation

extern uint16 CddTpsGen2_I2C_unReadStartAddress;                        // Start Address for Read operation
extern uint16 CddTpsGen2_I2C_unReadEndAddress;                          // End Address for Read operation
extern uint8 CddTpsGen2_I2C_ucReadBytesLeft;                            // Bytes Left to read on current operation
extern uint8 CddTpsGen2_I2C_ucCmdReadData_RxLength;                     // I2C Read Data Command Length

extern tCddTpsGen2_I2C_eState CddTpsGen2_I2C_State;           // I2C Current Operation State - Set to NotInit since Init operation not yet trigger.
extern tCddTpsGen2_I2C_eState CddTpsGen2_I2C_Response;           // I2C Current Operation State - Set to NotInit since Init operation not yet trigger.

extern uint8 CddTpsGen2_I2C_ucInitTimeoutCounter ;                     // Init Operation Timeout Counter
extern uint8 CddTpsGen2_I2C_ucReadTimeoutCounter ;                     // Read Operation Timeout Counter
extern uint8 CddTpsGen2_I2C_ucWriteTimeoutCounter;                     // Write Operation Timeout Counter

extern tCddTpsGen2_I2C_eStatus CddTpsGen2_I2C_InitStatus;    // Init Operation Status - Set to rejected since Init operation not yet trigger.
extern tCddTpsGen2_I2C_eStatus CddTpsGen2_I2C_ReadStatus;    // Read Operation Status - Set to rejected since Init operation not yet trigger.
extern tCddTpsGen2_I2C_eStatus CddTpsGen2_I2C_WriteStatus;   // Write Operation Status - Set to rejected since Init operation not yet trigger.

extern tsCddTpsGen2_UartSchedTable CddTpsGen2_asUartSchedTableEE[];

//=============================================================================
// Module function declarations
//=============================================================================
extern boolean CddTpsGen2_GetComFAULT(const uint8_fast ucChipIdx);
extern boolean CddTpsGen2_GetCrcFault(const uint8_fast ucChipIdx);
extern boolean CddTpsGen2_GetMuxCmdCompleted(void);
extern boolean CddTpsGen2_GetInitCmdCompleted(void);
extern boolean CddTpsGen2_GetInitStatus(void);
extern boolean CddTpsGen2_StAction(const uint8 ucAction);
extern boolean CddTpsGen2_CheckReadCommand(const uint8 ucSchCmd);
extern void    CddTpsGen2_SetWIDTHReg(const uint8 ucChipIdx, const uint16* punDuty);
extern void    CddTpsGen2_GetADCReg(const uint8_fast ucChipIdx, tuCddTpsGen2_RxADC* puADCReg);
extern void    CddTpsGen2_GetELEFAULTReg(const uint8_fast ucChipIdx, tuCddTpsGen2_RxELEFAULT* puELEFAULTReg);
extern void    CddTpsGen2_StActionEE(const uint8 ucAction);
extern void    CddTpsGen2_SchHandleEE(const tsCddTpsGen2_UartSchedTable* pTabEntry);

extern tCddTpsGen2_I2C_eStatus* CddTpsGen2_I2C_StartInit(tCddTpsGen2_I2C_pFnct pfnInitSuccessClbk, tCddTpsGen2_I2C_pFnct pfnInitFailedClbk);
extern tCddTpsGen2_I2C_eStatus* CddTpsGen2_I2C_ReadEeprom(uint8* ucData_List, uint16 unStartAddress, uint16 unLength, tCddTpsGen2_I2C_pFnct pfnReadSuccessClbk, tCddTpsGen2_I2C_pFnct pfnReadFailedClbk);
extern tCddTpsGen2_I2C_eStatus* CddTpsGen2_I2C_WriteEeprom(uint8* ucData_List, uint16 unStartAddress, uint16 unLength, tCddTpsGen2_I2C_pFnct pfnWriteSuccessClbk, tCddTpsGen2_I2C_pFnct pfnWriteFailedClbk);
extern boolean                  CddTpsGen2_I2C_CheckEEActivation(uint8* pucGoToSt);
extern uint8                    CddTpsGen2_GetEEConnectedId(void);
extern void                     CddTpsGen2_I2C_HandlePreinit(uint8* pucAck);
extern void                     CddTpsGen2_I2C_HandleInit(uint8* pucAck);
extern void                     CddTpsGen2_I2C_HandleWritingStatus(const uint8 ucStatus);
extern void                     CddTpsGen2_I2C_CommandReadStart(uint8* pucSelSch);
extern void                     CddTpsGen2_I2C_CommandReadData(uint8* pucSelSch);
extern void                     CddTpsGen2_I2C_HandleReadingStatus(const uint8 ucStatus);
extern void                     CddTpsGen2_I2C_HandleReadData(uint8* pucData);
extern void                     CddTpsGen2_I2C_CommandWriteData(void);
extern void                     CddTpsGen2_I2C_HandleWriteData(uint8* pucAck);
extern void                     CddTpsGen2_I2C_HandleReset(uint8* pucAck);
extern void                     CddTpsGen2_I2C_Timeout(void);

#endif // TEST_2023_08_25_H_


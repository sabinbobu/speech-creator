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
/// \file  Test.h
///
/// \brief This file contains functions prototypes of the tested module, 
///        including functions parameters and global variables
///
//-----------------------------------------------------------------------------
#ifndef TEST_2024_09_17_H
#define TEST_2024_09_17_H

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <AL_Helper.h>
#include <string.h>

// Headers of the Module
#include <CddTpsGen3_Cod.h>
#include <CddTpsGen3_Com.h>
#include <CddTpsGen3_Sched.h>
#include <CddTpsGen3.h>

//-----------------------------------------------------------------------------
// Typedefs
//-----------------------------------------------------------------------------
typedef struct tsCddTpsGen3_UartSchedTable
{
  sint8 scNextEntry;                //offset to next scheduler table entry
  uint8 ucAction;                   // index of action function done after Rx
  teGen3_DynCmdType  eDynCmd;       // dynamic command type evaluation
  uint8  ucCmd;                     // read/write command to send
  uint8  ucRegAddr;                 // device register address
  uint8* pucTx;                     // control register data for transmission
  uint8  ucTxSize;                  // size of Tx Buffer command data
  uint8* pucRx;                     // status register data for reception
  uint8  ucRxSize;                  // size of Rx Buffer received data
} tsCddTpsGen3_UartSchedTable;

//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------

/* redefine for purpose test */
#define TEST_WR_01B CDDTPSGEN3_WRITE_01_BYTES
#define TEST_WR_02B CDDTPSGEN3_WRITE_02_BYTES
#define TEST_WR_03B CDDTPSGEN3_WRITE_03_BYTES
#define TEST_WR_04B CDDTPSGEN3_WRITE_04_BYTES
#define TEST_WR_12B CDDTPSGEN3_WRITE_12_BYTES
#define TEST_WR_16B CDDTPSGEN3_WRITE_16_BYTES
#define TEST_WR_32B CDDTPSGEN3_WRITE_32_BYTES

#define TEST_WR_05B CDDTPSGEN3_WRITE_05_BYTES
#define TEST_WR_08B CDDTPSGEN3_WRITE_08_BYTES
#define TEST_WR_20B CDDTPSGEN3_WRITE_20_BYTES

#define TEST_RE_01B CDDTPSGEN3_READ_01_BYTES 
#define TEST_RE_02B CDDTPSGEN3_READ_02_BYTES 
#define TEST_RE_03B CDDTPSGEN3_READ_03_BYTES 
#define TEST_RE_04B CDDTPSGEN3_READ_04_BYTES 
#define TEST_RE_12B CDDTPSGEN3_READ_12_BYTES 
#define TEST_RE_16B CDDTPSGEN3_READ_16_BYTES 
#define TEST_RE_32B CDDTPSGEN3_READ_32_BYTES 

#define TEST_LEN_00B CDDTPSGEN3_LEN_0_BYTES
#define TEST_LEN_01B CDDTPSGEN3_LEN_1_BYTE
#define TEST_LEN_02B CDDTPSGEN3_LEN_2_BYTES
#define TEST_LEN_03B CDDTPSGEN3_LEN_3_BYTES
#define TEST_LEN_04B CDDTPSGEN3_LEN_4_BYTES
#define TEST_LEN_05B CDDTPSGEN3_LEN_5_BYTES
#define TEST_LEN_06B CDDTPSGEN3_LEN_6_BYTES
#define TEST_LEN_12B CDDTPSGEN3_LEN_12_BYTES
#define TEST_LEN_16B CDDTPSGEN3_LEN_16_BYTES
#define TEST_LEN_32B CDDTPSGEN3_LEN_32_BYTES
#define TEST_LEN_34B CDDTPSGEN3_LEN_34_BYTES

#define WR_CMD_LEN(x)   (x + CDDTPSGEN3_SIZE_HEADERBYTES + CDDTPSGEN3_SIZE_CRCBYTES )

/* define for purpose test (originally, defined in a C file ) */
/*  1 */  #define TEST_PHASE_MSB_Tx         &CddTpsGen3_DataMirror.CtrlTx.RegPHASE_MSB[0].ucByte[0]
/*  2 */  #define TEST_PHASE_LSB_Tx         &CddTpsGen3_DataMirror.CtrlTx.RegPHASE_LSB[0].ucByte[0]
/*  3 */  #define TEST_WIDTH_MSB_Tx         &CddTpsGen3_DataMirror.CtrlTx.RegWIDTH_MSB[0].ucByte[0]
/*  4 */  #define TEST_WIDTH_LSB_Tx         &CddTpsGen3_DataMirror.CtrlTx.RegWIDTH_LSB[0].ucByte[0]
/*  5 */  #define TEST_SLEWRATE_Tx          &CddTpsGen3_DataMirror.CtrlTx.RegSLEWRATE[0].ucByte[0]
/*  6 */  #define TEST_DEFWIDTH_Tx          &CddTpsGen3_DataMirror.CtrlTx.RegDEFWIDTH[0].ucByte[0]
/*  7 */  #define TEST_SYSCFG_DEFAULT_Tx    &CddTpsGen3_DataMirror.CtrlTx.RegSYSCFG_DEFAULT[0].ucRaw
/*  8 */  #define TEST_SYSCFG_Tx            &CddTpsGen3_DataMirror.CtrlTx.RegSYSCFG[0].ucByte[0]
/*  9 */  #define TEST_SSYNC_STATUS_Tx      &CddTpsGen3_DataMirror.CtrlTx.RegSSYNC_STATUS[0].ucByte[0]
/* 10 */  #define TEST_MTPCFG_FS_Tx         &CddTpsGen3_DataMirror.CtrlTx.Reg_MPTCFG_FS[0].ucRaw
/* 11 */  #define TEST_OUTCTRL_Tx           &CddTpsGen3_DataMirror.CtrlTx.RegOUTCTRL[0].ucRaw
/* 12 */  #define TEST_ELECFAULTS_Tx        &CddTpsGen3_DataMirror.CtrlTx.RegELEFAULT[0].ucByte[0]

/*  1 */  #define TEST_ICID_Rx              &CddTpsGen3_DataMirror.StatRx.RxICID[0].ucRxByte[0]
/*  2 */  #define TEST_SYSCONFIG_Rx         &CddTpsGen3_DataMirror.StatRx.RxSYSCONFIG[0].ucRxByte[0]
/*  3 */  #define TEST_SYSCFG_Rx            &CddTpsGen3_DataMirror.StatRx.RxSYSCFG[0].ucRxByte[0]
/*  4 */  #define TEST_SSYNC_STATUS_Rx      &CddTpsGen3_DataMirror.StatRx.RxSSYNC_STATUS[0].ucRxByte[0]
/*  5 */  #define TEST_PHASES_MSB_Rx        &CddTpsGen3_DataMirror.StatRx.RxPHASES_MSB[0].ucRxByte[0]
/*  6 */  #define TEST_PHASES_LSB_Rx        &CddTpsGen3_DataMirror.StatRx.RxPHASES_LSB[0].ucRxByte[0]
/*  7 */  #define TEST_CFGLEDS_Rx           &CddTpsGen3_DataMirror.StatRx.RxCFGLEDS[0].ucRxByte[0]
/*  8 */  #define TEST_CFGDEF_Rx            &CddTpsGen3_DataMirror.StatRx.RxCFGDEF[0].ucRxByte[0]
/*  9 */  #define TEST_EXIT_FS_Rx           &CddTpsGen3_DataMirror.StatRx.RxEXIT_FS[0].ucRxByte[0]
/* 10 */  #define TEST_OUTCTRL_Rx           &CddTpsGen3_DataMirror.StatRx.RxOUTCTRL[0].ucRxByte[0]
/* 11 */  #define TEST_PWM_MSB_Rx           &CddTpsGen3_DataMirror.StatRx.RxPWMS_MSB[0].ucRxByte[0]
/* 12 */  #define TEST_PWM_LSB_Rx           &CddTpsGen3_DataMirror.StatRx.RxPWMS_LSB[0].ucRxByte[0]
/* 13 */  #define TEST_ELEFAULT_Rx          &CddTpsGen3_DataMirror.StatRx.RxELEFAULT[0].ucRxByte[0]
/* 14 */  #define TEST_CLR_ELEFAULT_Rx      &CddTpsGen3_DataMirror.StatRx.RxCLR_ELEFAULT[0].ucRxByte[0]
/* 15 */  #define TEST_ADC_Rx               &CddTpsGen3_DataMirror.StatRx.RxADC[0].ucRxByte[0]
/* 16 */  #define TEST_STATUS_Rx            &CddTpsGen3_DataMirror.StatRx.RxSTATUS[0].ucRxByte[0]
/* 17 */  #define TEST_SLEWRATE_Rx          &CddTpsGen3_DataMirror.StatRx.RxSLEWRATE[0].ucRxByte[0]

/*  1 */  #define TEST_BR1_ADCID            &CddTpsGen3_BroadcastData.RxBrADCID.ucRxByte[0]
/*  2 */  #define TEST_BR2_SYSCFG           &CddTpsGen3_BroadcastData.RxBrSYSCFG.ucRxByte[0]

          #define TEST_ZERO_Tx              &CddTpsGen3_aucZero[0]
          #define TEST_ZERO_Rx              &CddTpsGen3_ucDummy[0]

//-----------------------------------------------------------------------------
// Module global variables
//-----------------------------------------------------------------------------
/* CddTpsGen3.c */
extern tsCddTpsGen3_DevData   CddTpsGen3_sDevData;
extern boolean                CddTpsGen3_boReinitChips;

/* CddTpsGen3_Com.c */
extern uint8     CddTpsGen3_ucSchedIx;
extern uint8     CddTpsGen3_ucChipIdx;
extern uint8     CddTpsGen3_ucChipIdx_MuxCmd;

extern boolean   CddTpsGen3_aboComStatus[CFG_MAX_NO_OF_MLC_CHIPS];
extern boolean   CddTpsGen3_aboCrcStatus[CFG_MAX_NO_OF_MLC_CHIPS];
extern uint8     CddTpsGen3_ucPowerOnReset_Bit;
extern boolean   CddTpsGen3_boMuxCmdCompleted;
extern boolean   CddTpsGen3_boInitCompleted;

extern CONST_AL uint16 CddTpsGen3_aunPhaseShifts_TPS9266x[][CDDTPSGEN3_TPS9266x_MAX_SWITCHS_PER_DEVICE];
extern CONST_AL uint8  CddTpsGen3_aucDefaultWidths_TPS9266x[][CDDTPSGEN3_TPS9266x_MAX_SWITCHS_PER_DEVICE];
extern CONST_AL uint8  CddTpsGen3_aucConfigSlewrate_LSB[];
extern CONST_AL uint8  CddTpsGen3_aucConfigSlewrate_MSB[];

/* data mirror and scheduler variables*/
extern uint8                    CddTpsGen3_ucDummy[CFG_MAX_NO_OF_MLC_CHIPS];
extern uint8                    CddTpsGen3_aucZero[CFG_MAX_NO_OF_MLC_CHIPS];
extern uint8                    CddTpsGen3_aucTxBuffer[CDDTPSGEN3_MAX_CMD_LENGTH];
extern tsCddTpsGen3_DataMirror  CddTpsGen3_DataMirror;
extern tsCddTpsGen3_BrCmd       CddTpsGen3_BroadcastData;
extern CONST_AL tsCddTpsGen3_UartSchedTable CddTpsGen3_asUartSchedTable[];

//-----------------------------------------------------------------------------
// Module function declarations
//-----------------------------------------------------------------------------

/* static functions of CddTpsGen3.c*/
void    CddTpsGen3_DoAddressingMap(tsCddTpsGen3_DevData* psData);

/* APIs CddTpsGen3.c */
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

/* static functions of CddTpsGen3_Com.c*/
void    CddTpsGen3_SetComStatus(boolean boRxStat, teGen3_DynCmdType eCmdType);
void    CddTpsGen3_BuildTxFrame(const tsCddTpsGen3_UartSchedTable* psEntryData, uint8 ucChipAddress, uint8 ucChipIdx, tsCddUart_MessageEntryType* sTxCbData);
void    CddTpsGen3_PrepareTxFrameForSingleCmd(tsCddUart_MessageEntryType* psTxCbData, const tsCddTpsGen3_UartSchedTable* pTabEntry, uint8 ucChipAddress, uint8 ucChipIdx);
uint16  CddTpsGen3_Calc16BitCRCValue (uint8* pucData, uint8 ucLength);
void    CddTpsGen3_SchHandle         (const tsCddTpsGen3_UartSchedTable* pTabEntry);
boolean CddTpsGen3_StAction          (const uint8 ucAction);
void    CddTpsGen3_UseDummyTxRx      (tsCddUart_MessageEntryType* psTxCbData);
void    CddTpsGen3_SetPHASEReg_MSB   (const uint8_fast ucChipIdx, const uint16* punPhase);
void    CddTpsGen3_SetPHASEReg_LSB   (const uint8_fast ucChipIdx, const uint16* punPhase);
void    CddTpsGen3_SetCFGLEDSReg     (const uint8_fast ucChipIdx, const uint8* pucDefWidth);
void    CddTpsGen3_SetWIDTHReg_LSB   (const uint8 ucChipIdx,      const uint16* punDuty);
void    CddTpsGen3_SetWIDTHReg_MSB   (const uint8 ucChipIdx,      const uint16* punDuty);
boolean CddTpsGen3_CheckCRC          (uint8* ucPtrData, uint8 ucLength);
boolean CddTpsGen3_CheckReadCommand  (const uint8 ucSchCmd);
void    CddTpsGen3_SetCrcStatus      (const tsCddTpsGen3_UartSchedTable* pTabEntry);

/* APIs CddTpsGen3_Com.c */
void    CddTpsGen3_SetWIDTHReg(const uint8 ucChipIdx, const uint16* punDuty);
void    CddTpsGen3_GetADCReg(const uint8_fast ucChipIdx, tuCddTpsGen3_RxADC* puADCReg);
void    CddTpsGen3_GetELEFAULTReg(const uint8_fast ucChipIdx, tuCddTpsGen3_RxELEFAULT* puELEFAULTReg);
boolean CddTpsGen3_GetComFAULT(const uint8_fast ucChipIdx);
boolean CddTpsGen3_GetMuxCmdCompleted(void);
boolean CddTpsGen3_GetInitCmdCompleted(void);
boolean CddTpsGen3_GetCrcFAULT(const uint8_fast ucChipIdx);

/* callback functions*/
void    CddTpsGen3_UartRx(const uint8* pucRxData, boolean boRxStatus);
void    CddTpsGen3_UartTx(tsCddUart_MessageEntryType* psTxCbData);

//-----------------------------------------------------------------------------
// Module function parameter stubs
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Module function return value stubs
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Module static variables inside functions 
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Global variable stubs
//-----------------------------------------------------------------------------

// backups of initialized structs
tsCddTpsGen3_DataMirror     Test_DataMirror_Backup;
tsCddTpsGen3_UartSchedTable Test_UartSchedTable_Backup[];

#endif // TEST_2024_09_17_H

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

#include <CddStp_Simulation.h>
#include <CddStpIfc.h>
#include <CddStp88XX_HalStp.h>
#include <CddStp88XXTemp.h>
#include <CddStpDyn.h>
#include <CddStp88XX_FctTables.h>
#include <CddStpData.h>

//=============================================================================
// Defines
//=============================================================================

#define tCddStp_Attr tCddStp88XX_Attr
#define CFA_CNT_STP_ONBRD  (4u)
#define CDDSTP88XX_StateVoltStartValue  (0xffu)
#define CDDSTP88XX_StateVoltOff        (0u)
#define CDDSTP88XX_StateVoltUnder      (1u)
#define CDDSTP88XX_StateVoltNormal     (2u)
#define CDDSTP88XX_StateVoltOver       (3u)
//CddStpDyn.c
#define CDDSTPDYN_PrePostStepScale     (10000u)  // scaling of pre/post step parameters
#define CDDSTPDYN_PrePostStepMin        (2000u)  // minimum step time because of SPI jitter
#define CDDSTPDYN_PrePostStepMax       (65535u)  // maximum step time to avoid overflow
#define CDDSTPDYN_PostStepAdd           (4000u)  // minimum delta between post step time and direction change time
#define CDDSTPDYN_StpTableSize            (76u)  // maximum size for step table (according to slowest AL profile)
#define CDDSTPDYN_ZeitUmkehrMin         (4000u)  // minimum value needed in case of wrong coding parameters
#define CDDSTPDYN_AnzahlRef2Min           (16u)  // minimum value needed in case of wrong coding parameters

//CddStp_Tsp.c
#define CDDSTP_RESOLUTION_CORRECTION_PWM  10U   // timer resolution correction from 1MHz to 10MHz
#define CDDSTP_RESOLUTION_CORRECTION_HLP  16U   // timer resolution correction from 1MHz to 16MHz
#define CDDSTP_TSP_PWMCH_IDX        12U
#define CDDSTP_TSP_CNT                1U
#define CDDSTP_TSP_LPIT_INSTANCE_IDX  0U  // index of Lpit timer used for cddstp
#define  CDDSTP_MaxHsPeriod                 ((uint16) 32767)  // 32.8 ms ->   ca.32 HS/s (representable by 15 bit)

#define tCddSpiL2Channel uint8
#define  CDDSTP8899_RegValVBATSDD          (0xFFu)  // control and status register value in case of VBATS < 2.5 V: SPI does not work and data is set by pull up resistances
#define  CDDSTP8899_SRBValVBATSDD          (0x3Fu)  // Basic       status register value in case of VBATS < 2.5 V: SPI does not work and data is set by pull up resistances
#define CDDSTP88XX_HALSTP_ErrVoltDefault         (13000u)                      // default value of the voltage stored in Err-ISR [mV]
#define cDebugSize  10u
#define CDDSTP8899_SpiSt_IxMax                                 11u  // size of SPI-Schedule-Table
#define CDDSTP_HsInfoBufMask                (CDDSTP88XX_HALSTP_HsInfoBufLen - 1u)

#define CDDSTP88XX_HALSTP_HsInfoBufLen         (64u)
#define CFA_CNT_STP_88XX   (4u)


//=============================================================================
// Typedefs
//=============================================================================

typedef enum
{
  eInit = 0,
  eLow3 = 1,
  eLow2 = 2,
  eLow1 = 3,
  eNormal = 4,
  eHigh1 = 5,
  eHigh2 = 6,
  eUndef = 99 // only UT
} tVolt_Range;

typedef struct
{
  unsigned int  biFirstStep : 1;
  unsigned int  biAboveResF1 : 1; // !resonance frequency 1 is lower  than 2!
  unsigned int  biAboveResF2 : 1; // !resonance frequency 2 is higher than 1!
  unsigned int  biStop : 1;
}tCddStpDynBits;

typedef struct
{
  unsigned  biDummy1 : 16;   // do not use bit access to this variable
  unsigned  biDummy2 : 8;   // do not use bit access to this variable
  unsigned  biInit : 1;   // reset dynamic calculation if this bit is set
  unsigned  biReserved : 7;
}tStpTabRamBit;

typedef struct
{
  uint16  unMinPeriod;         // min. HS duration (frequency limitation)
  uint8   ucMaxIx;             // max. index to step table
  uint8   ucDummy;             // used for bitwise access
}tStpTabRamVal;

typedef union
{
  tStpTabRamVal Val;           // use Val for initialization
  tStpTabRamBit Bit;
}tStpTabRam;

typedef struct
{
  uint16  biInit : 1; //  0: HalStp is initialized
  uint16  biTestStep : 1; //  1: test step
  uint16  biTestStepDone : 1; //  2: test step done
  uint16  biStopStpPZ : 1; //  3: stop stepper profile zero (not motor enable !MotEn) - stored in case of stop while movement
  uint16  biStopStp : 1; //  4: stop stepper
  uint16  biHsMode : 1; //  5: half step mode
  uint16  biReserved : 2; //  6: reserved
  uint16  biMotEn : 1; //  8: motor enable                                                       // only used for DRV88XX
  uint16  biDriverReset : 1; //  9: driver reset       - detected by missing SPI communication         // only used for DRV88XX
// orig.: uint16  biReserved6   : 6; // 10: reserved
  uint16  biTbdClrTiFaultBits : 1; // 10: CTRL4 Bit7: CLR_FLT - Write '1' to this bit to clear all latched fault bits. This bit automatically resets after being written.
//  uint16  biReserved5         : 5; // 11: reserved
  uint16  biTbdEnOlDtctn : 1; // 11: Enable Open-Load-Detection
  uint16  biReserved4 : 4; // 12: reserved
}tHSBits;

typedef union
{
  tHSBits Bit;     ///< bit signal access
  uint16  unRaw;   ///< raw signal access
} tHalStpBits;


typedef void(*tFct_Void_Void)                                (void);
typedef void(*tFct_Void_Bool)                                (boolean);
typedef void(*tFct_Void_Bool_Bool)                           (boolean, boolean);
typedef boolean(*tFct_Bool_Void)                             (void);
typedef boolean(*tFct_Bool_Bool)                             (boolean);
typedef boolean(*tFct_Bool_Bool_Uint8)                       (boolean, uint8);
typedef sint32(*tFct_Int32_Void)                             (void);
typedef uint8(*tFct_Uint8_Void)                              (void);
typedef uint32(*tFct_Uint32_pInt32_pUint32)                  (sint32*, uint32*);
typedef void(*tFct_Void_Uint8)                               (uint8);
typedef void(*tFct_Void_Uint8_Uint8_Uint8)                   (uint8, uint8, uint8);
typedef volatile uint8* (*tFct_VolatileUint8_Void)           (void);
typedef tStpInfo* (*tFct_ptStpInfo_Void)                     (void);
typedef void(*tFct_Void_ConstInt32)                          (const sint32);
typedef void(*tFct_Void_ConsteHalStpRegisters_ConstUint16)   (const eCddStp88XX_HalStpRegisters, const uint16);
typedef void(*tFct_Void_ConsteHalStpRegisters_ConstBool)     (const eCddStp88XX_HalStpRegisters, const boolean);
typedef uint32(*tFct_Uint32_Void)                            (void);

typedef struct
{
  boolean bState_EnOl;
  boolean bState_DisOut;
  // tbd: CddStp88XX_aBitsMod[CFG_Stp_IdxVer].Bit.biDisOLDetect
  // tbd: CddStp88XX_HalStp_BitsLwr.Bit.biMotEn
  uint8   ucSpiOkCounter;
  tFTimer ftTime;
  uint8   ucNextEntry;       // index of next schedule table entry
  uint8   ucAddr;            // SPI address (combination of low and high nibble) - e.g. 'DRV8899_wCR3_'
} tCddStp8899Com_DebugOlErrorProblem;

typedef struct
{
  uint8        ucNextEntry;       // index of next schedule table entry
  uint8        ucAddr;            // SPI address (combination of low and high nibble)
  const uint8* pucCtrlTx;         // SPI control register data for transmission       - offset related to 1st address of stuct 
  uint8* pucRxDataByte;     // SPI control/status register data 1 for reception - offset related to 1st address of stuct
  uint8* pucRxDummy;        // SPI status register data 2 for reception - use instead of this:  'uint8* pucStatusBasic = ST_STAT_RX_SRB'
} tCddStp8899Com_SpiSchedTable;

typedef void(*tStateFctPtrCddStp88XX)(uint8, tAction);

//=============================================================================
// Module global variables
//=============================================================================

extern uint32                                    CddStp_UnitTestHelper_ul1;
extern uint32                                    CddStp_UnitTestHelper_ul2;
extern boolean                                   CddStp_UnitTestHelper_bo1;
extern boolean                                   CddStp_UnitTestHelper_bo2;



extern tCddStp_Simulation_Data                   CddStp_Simulation_Data;
extern uint32                                    CddStpDynBuf_ulAccStepTime;
extern uint32                                    CddStpDynBuf_ulBufIx;
extern tHsInfo*                                  CddStpDynBuf_pHsBuf;
extern tHsInfo                                   CddStpDynBuf_HsEntry;

extern uint8                                     CddStpVolt_ucPreResult;
extern uint8                                     CddStpVolt_ucEndResult;
extern uint16                                    CddStpVolt_unTimerCnt;
extern tVolt_Range                               CddStpVolt_ucVoltRange;

//CddStpDyn.c
extern tCddStpDynBits                            CddStpDyn_Bits;
extern uint8                                     CddStpDyn_ucIx;
extern sint32                                    CddStpDyn_lCurrentDir;
extern sint32                                    CddStpDyn_lStepsToDo;
extern uint8                                     CddStpDyn_ucActTabIx;
extern uint8                                     CddStpDyn_aucLastTabIx[CFA_CNT_STP_88XX];
extern uint16                                    CddStpDyn_aunHsZeit[CFA_CNT_STP_88XX][CDDSTPDYN_StpTableSize];
extern uint16                                    CddStpDyn_unRefSteps[CFA_CNT_STP_88XX];         //   - referencing
extern uint16                                    CddStp_unPreStepLen[CFA_CNT_STP_88XX];         // length of pre step in microseconds
extern uint16                                    CddStp_unPostStepLen[CFA_CNT_STP_88XX];         // length of post step in microseconds

extern boolean                                   CddStp_Tsp_BoInitialized;
extern tStpTabRam*                               CddStpDyn_pStpInfo;
extern tNvmPara_SystemBlock                      CddStp_tCodingAreaSys;
extern tNvmPara_AvacStpBlock                     CddStp_tCodingAreaLwr;
extern tStateCddStp88XX                          CddStp88XX_aeState[CFA_CNT_STP_88XX];
extern tCddStpEvent                              CddStp88XX_aEventBits[CFA_CNT_STP_88XX];

tNvmPara_CodingArea                              Coding_Dummy = { 0 };
extern tCddStp8899Com_DataMirror                 CddStp8899Com_DataMirror;
extern tActCtrl                                  CddStp88XX_aStpCtrl[CFA_CNT_STP_88XX];
extern uint8                                     CddStp8899Com_aucCheckDrvDefectCnt[CFA_CNT_STP_88XX];
extern tStpState                                 CddStp88XX_aStpState[CFA_CNT_STP_88XX];
extern uint16                                    CddStp8899Com_aunTxData;
extern uint8                                     CddStp8899Com_aucStReqOnceMore[CFA_CNT_STP_88XX];
extern tsRte_CddStpActual                        CddStp_ActAll;

extern tCddStp88XXBitsMod                        CddStp88XX_aBitsMod[CFA_CNT_STP_88XX];
extern tCddStp88XXBits                           CddStp88XX_aBits[CFA_CNT_STP_88XX];
extern tFTimer                                   CddStp88XX_astWaitDurLT[CFA_CNT_STP_88XX];
extern tCddStpTempState                          CddStp88XX_aeTemp[CFA_CNT_STP_88XX];
extern uint32                                    CddStp88XX_HalStp_ulHsCntLwr;
extern uint32                                    CddStp88XX_HalStp_ulIrunTimeLwr;
extern tStateHalStp                              CddStp88XX_HalStp_eStateLwr;
extern uint8                                     CddStp88XX_HalStp_ucStepModeLwr;
extern tHalStpBits                               CddStp88XX_HalStp_BitsLwr;
extern uint32                                    CddStp88XX_HalStp_ulTestStepCntLwr;
extern uint8                                     CddStp88XX_HalStp_ucOLCntLwr;
extern tCddStp8899Com_StatReg_Fault              CddStp8899_aSRegFault[CFA_CNT_STP_88XX];
extern uint8                                     CddStp88XX_aucOLCntMax[CFA_CNT_STP_88XX];
extern uint8                                     CddStp88XX_HalStp_ucSCCntLwr;
extern uint16                                    CddStp88XX_HalStp_unErrVoltLwr;
extern tStpInfo                                  CddStp88XX_HalStp_StpInfoLwr;
extern uint8                                     CddStp88XX_HalStp_ucPhaseCounterLwr;
extern tHalStpBitsInt                            CddStp88XX_HalStp_BitsIntLwr;
extern uint8                                     CddStp88XX_HalStp_ucCurAmpltLwr;
extern tHsInfo                                   CddStp88XX_HalStp_HSInfoBufSaveLwr;
extern uint32                                    CddStp88XX_HalStp_ulSet0Lwr;
extern tStpPos                                   CddStp88XX_aStpPos[CFA_CNT_STP_88XX];
extern uCddStp88XXBitsGlobalInitOnce             CddStp88XX_BitsGlobalInitOnce;
extern uint16                                    CddStpDyn_aunHsZeit[CFA_CNT_STP_88XX][CDDSTPDYN_StpTableSize];
extern boolean                                   CddStp88XX_boUVShtDwn; // LDM specific, flag used to indicate under voltage shutdown
extern uint32                                    IoHwAb_SystemTick_1Ms; // every millisecond this variable is incremented
extern uint32                                    CddStp88XX_aulStpOnStart[CFA_CNT_STP_88XX];
extern uint32                                    CddStp88XX_aulStpOnTime[CFA_CNT_STP_88XX];
extern uint16                                    CddStp88XX_aunRefStartCnt[CFA_CNT_STP_88XX];
extern uint16                                    CddStp88XX_aunIsRefCnt[CFA_CNT_STP_88XX];
extern uint8                                     CddStp88XX_ucStateVolt;                      // state of Volt state machine - StateVoltOff=0, StateVoltUnder=1, StateVoltNormal=2, StateVoltOver=3, StateVoltStartValue=0xFF
extern tFTimer                                   CddStp88XX_aftWaitVoltage[CFA_CNT_STP_88XX];
extern tFTimer                                   CddStp88XX_aftWaitStabilize[CFA_CNT_STP_88XX];
extern sint32                                    CddStp88XX_alActPosMem[CFA_CNT_STP_88XX];  // actual position in state Move, Ref1, Ref2 to avoid hanging in case of hanging CddStp8899_HalStp state machine in StateStep because of DMA or timer INT mismatch
extern uint8                                     CddStp88XX_aucActPosMemCnt[CFA_CNT_STP_88XX];  // count of no change of actual position in state Move, Ref1, Ref2 to avoid hanging in case of hanging CddStp8899_HalStp state machine in StateStep because of DMA or timer INT mismatch
extern tActCtrl                                  CddStp88XX_aStpCtrlOld[CFA_CNT_STP_88XX];
extern tCddStp8899Com_StatReg_Basic              CddStp8899_aSRegBasic[CFA_CNT_STP_88XX]; // Basic-Status - comes each time 'automatically' - 1 | 1 | UVLO | CPUV | OCP | RSVD | TF | OL
extern tCddStp8899Com_StatReg_Fault              CddStp8899_aSRegFault[CFA_CNT_STP_88XX]; // Fault-Status                                   - FAULT | SPI_ERROR | UVLO | CPUV | OCP | RSVD | TF | OL
extern tCddStp8899Com_StatReg_Diag1              CddStp8899_aSRegDiag1[CFA_CNT_STP_88XX]; // Diag-Status-1                                  - OCP_LS2_B | OCP_HS2_B | OCP_LS1_B | OCP_HS1_B | OCP_LS2_A | OCP_HS2_A | OCP_LS1_A | OCP_HS1_A
extern tCddStp8899Com_StatReg_Diag2              CddStp8899_aSRegDiag2[CFA_CNT_STP_88XX]; // Diag-Status-2                                  - UTW | OTW | OTS | RSVD | OL_B | OL_A
extern uint8                                     CddStp88XX_aucErrVoltHiLimitSCCnt[CFA_CNT_STP_88XX]; // check to detect case of no pseudo SC error (ErrElecSC)  -  if > 'CDDSTP88XX_ErrVoltHiLimitSCCntMax' than pseudo SC error
extern sint16                                    CddStp88XX_anRef1Pos[CFA_CNT_STP_88XX];
extern uint8                                     CddStp8899Com_aucActSchedTable[CFA_CNT_STP_88XX];                      // number of actual schedule table CddStp8899Com_eSt3
extern uint8                                     CddStp8899Com_aucSchedState[CFA_CNT_STP_88XX];// = { CDDSTP8899_SpiSt_StartIx0, CDDSTP8899_SpiSt_StartIx0, CDDSTP8899_SpiSt_StartIx0, CDDSTP8899_SpiSt_StartIx0 };  // index to         schedule table CddStp8899Com_eSt3
extern boolean                                   CddStp8899Com_DoClearFaultBit[CFA_CNT_STP_88XX];    // usually 'CLR_FLT' in CReg4 is '0' - only on request do WRITE ONCE a '1'
extern uint8                                     CddStp8899Com_aucDebouncingCtr_OL[CFA_CNT_STP_88XX];
extern uint8                                     CddStp8899Com_aucDebouncingCtr_OCP[CFA_CNT_STP_88XX];
extern uint8                                     CddStp8899Com_ucDEBUG_SpiOkCounter;
extern tCddStp8899Com_DebugOlErrorProblem        CddStp8899Com_Debug__OlErrorProblem[cDebugSize];
extern uint8                                     CddStp8899Com_Debug__ucIdx = 0;
extern uint16                                    CddStp88XX_unIsReadyDelayCnt[CFA_CNT_STP_88XX];
extern uint8                                     CddStp8899Com_ucDEBUG_DebouncingCtr_OL_Max;
extern tPsensInf                                 CddStp88XX_aPsensInf[CFA_CNT_STP_88XX];
extern uint8                                     CddStp8899Com_ucDEBUG_DebouncingCtr_OCP_Max;
extern tCddStp8899Com_SpiSchedTable              CddStp8899Com_SpiSchedTable[CDDSTP8899_SpiSt_IxMax + 1u];
extern uint8                                     CddStp88XX_ucAhlErrPsensCnt;                               // for Hor stepper only
extern boolean                                   CddStp88xx__LwrSleepAndDisable; // HW-Pins of 'Sleep' and 'Disable' are 'active'
extern uint8                                     CddStp8899Com_aucTrqDac_LastTx[CFA_CNT_STP_88XX];
extern uint16                                    CddStp88XX_aunAhlPosDevHistCnts[CDDSTP_POSDEVHIST_MAX];  // for Hor stepper only
extern uint8                                     CddStp8899_ucDummy;             // suppress LINT warnings
extern uint8                                     CddStp88XX_aucCurAmpltHoldTemp[][CddStp_eTempState_TempIx];
extern uint8                                     CddStp88XX_aucCurAmpltRunTemp[][CddStp_eTempState_TempIx];
extern uint8                                     CddStp88XX_aucCurAmpltRefTemp[][CddStp_eTempState_TempIx];
extern uint32                                    CddStp_Counter_DeInit;
extern uint32                                    CddStp_Counter_Init;
extern uint32                                    CddStp_Counter_Cycle;

//=============================================================================
// Module function declarations
//=============================================================================

extern void            CddStp88XX_DeInit(uint8 ucIx);
extern void            CddStp88XX_CheckPsensSlopeAndActPos(uint8 ucIx);
extern void            CddStp88XX_CalcCorrQuota(/*const*/ uint8 ucIx);
extern void            CddStp88XX_HandleStp(uint8 ucIx);
extern void            CddStp88XX_HandleStpOnTime(uint8 ucIx, boolean boStpOn);
extern uint32          CddStp88XX_GetStpOnTime(uint8 ucIx);
extern uint16          CddStp88XX_GetRefStartCnt(uint8 ucIx);
extern uint16          CddStp88XX_GetIsRefCnt(uint8 ucIx);
extern void            CddStp88XX_GetAhlPosDevHistCnts(uint8 ucIx, uint16* punAhlPosDevHistCnts);
extern void            CddStp88XX_StartWait88XXVoltage(uint8 ucIx);
extern void            CddStp88XX_StartWaitVoltage(uint8 ucIx);
extern void            CddStp88XX_ReadDRV88XXTestRegAll(uint8 ucIx);
extern void            CddStp88XX_SetCurrent(uint8 ucIx);
extern void            CddStp88XX_StateMachine(uint8 ucIx, const tCommandCddStp88XX eCmd);
extern uint32          CddStp88XX_Transition_Init(uint8 ucIx, const tCommandCddStp88XX eCmd);
extern uint32          CddStp88XX_Transition_InitOff(uint8 ucIx, const tCommandCddStp88XX eCmd);
extern uint32          CddStp88XX_Transition_Off(uint8 ucIx, const tCommandCddStp88XX eCmd);
extern uint32          CddStp88XX_Transition_StbyIdle(uint8 ucIx, const tCommandCddStp88XX eCmd);
extern uint32          CddStp88XX_Transition_IdleStby(uint8 ucIx, const tCommandCddStp88XX eCmd);
extern uint32          CddStp88XX_Transition_MoveIdle(uint8 ucIx, const tCommandCddStp88XX eCmd);
extern uint32          CddStp88XX_Transition_MoveOff(uint8 ucIx, const tCommandCddStp88XX eCmd);
extern uint32          CddStp88XX_Transition_IdleMove(uint8 ucIx, const tCommandCddStp88XX eCmd);
extern uint32          CddStp88XX_Transition_RefOff(uint8 ucIx, const tCommandCddStp88XX eCmd);
extern uint32          CddStp88XX_Transition_Ref1(uint8 ucIx, const tCommandCddStp88XX eCmd);
extern uint32          CddStp88XX_Transition_RefWait(uint8 ucIx, const tCommandCddStp88XX eCmd);
extern uint32          CddStp88XX_Transition_RefWaitIdle(uint8 ucIx, const tCommandCddStp88XX eCmd);
extern uint32          CddStp88XX_Transition_Ref1Ref2(uint8 ucIx, const tCommandCddStp88XX eCmd);
extern uint32          CddStp88XX_Transition_Ref1RefWait(uint8 ucIx, const tCommandCddStp88XX eCmd); // * Sref reference run uses Psens *
extern uint32          CddStp88XX_Transition_Ref2RefWait(uint8 ucIx, const tCommandCddStp88XX eCmd);
extern uint32          CddStp88XX_Transition_TestStep(uint8 ucIx, const tCommandCddStp88XX eCmd);
extern uint32          CddStp88XX_Transition_TestStepIdle(uint8 ucIx, const tCommandCddStp88XX eCmd);
extern uint32          CddStp88XX_Transition_Err(uint8 ucIx, const tCommandCddStp88XX eCmd);
extern uint32          CddStp88XX_Transition_Err_Sub(uint8 ucIx, const tCommandCddStp88XX eCmd, boolean boLessThanErrVoltHiLimit);
extern uint32          CddStp88XX_Transition_OffStby(uint8 ucIx, const tCommandCddStp88XX eCmd);
extern uint32          CddStp88XX_Transition_OffIdle(uint8 ucIx, const tCommandCddStp88XX eCmd);
extern uint32          CddStp88XX_Transition_ErrClr(uint8 ucIx, const tCommandCddStp88XX eCmd);
extern void            CddStp88XX_StateFct_Init(uint8 ucIx, tAction Action);
extern void            CddStp88XX_StateFct_Off(uint8 ucIx, tAction Action);
extern void            CddStp88XX_StateFct_Stby(uint8 ucIx, tAction Action);
extern void            CddStp88XX_StateFct_Idle(uint8 ucIx, tAction Action);
extern void            CddStp88XX_StateFct_Move(uint8 ucIx, tAction Action);
extern void            CddStp88XX_StateFct_Ref1(uint8 ucIx, tAction Action);
extern void            CddStp88XX_StateFct_Ref2(uint8 ucIx, tAction Action);
extern void            CddStp88XX_StateFct_RefWait(uint8 ucIx, tAction Action);
extern void            CddStp88XX_StateFct_TestStep(uint8 ucIx, tAction Action);
extern void            CddStp88XX_StateFct_Err(uint8 ucIx, tAction Action);
extern void            CddStp88XX_Init_(uint8 ucIx);
extern void            CddStp88XX_Ctrl(uint8 ucIx);
extern boolean         CddStp88XX_HandleWaitStabilize(uint8 ucIx);
extern void            CddStp88XX_HandleWaitVoltage(uint8 ucIx);
extern void            CddStp88XX_HandleResetErrVolt(uint8 ucIx, boolean boClearSRegsScOl);
extern void            CddStp88XX_HandleStepLoss(uint8 ucIx);
extern boolean         CddStp88XX_HandleStepHanging(uint8 ucIx, boolean boRef);
extern void            CddStp88XX_HandleWrongRef1Motion(uint8 ucIx);
extern void            CddStp88XX_StpStateVoltNormSet(void);
extern void            CddStp88XX_StpStateVoltNormClear(void);
extern void            CddStp88XX_StpStateOvSet(void);
extern void            CddStp88XX_StpStateOvClear(void);
extern void            CddStp88XX_StpStateUvSSMSet(void);                  // undervoltage soft stop motion
extern void            CddStp88XX_StpStateUvSSMClear(void);
extern uint8           CddStp88XX_GetCurrentIndex(const uint8 ucCurrent);
extern void            CddStp88XX_EftCodingLr_2(void);

extern void                         CddStpDyn_CalcNormal(void);
extern void                         CddStpDyn_CalcRef2(void);
extern void                         CddStpDyn_CalcRef1(void);
extern void                         CddStpDyn_PreStep(void);
extern void                         CddStpDyn_GetStartConditions(void);
extern uint8                        CddStpDyn_GetIx(uint8 ucIx, uint16 unStepTime);
extern uint16                       CddStpDyn_GetStpTime(uint8 ucTabIx);
extern uint16                       CddStpDyn_CalcNextHalfStepTime(uint8 ucIx, uint16 unT_n1);
extern /*obsolet: 'inline'*/ void   CddStpDyn_DecActTabIx(void);
extern /*obsolet: 'inline'*/ void   CddStpDyn_IncActTabIx(void);
extern /*obsolet: 'inline'*/ sint32 CddStpDyn_GetSign(sint32 lValue);

extern void           CddStp_Init(void);
extern void           CddStp_DeInit(void);
extern void           CddStp_Cycle(void);
extern Std_ReturnType CddStp_StpOff(void);
extern Std_ReturnType CddStp_StpOn(void);

extern void   CddStpVolt_TimerStop(void);                                         // Stop timer to make sure the CddStpVolt_ucPreResult is canceled / discard 'CddStpVolt_ucPreResult' and keep 'CddStpVolt_ucEndResult'
extern void   CddStpVolt_TimerRestart(uint16 unTime_Cnt, uint8 ucPreResult);      // countdown of 'CddStpVolt_unTimerCnt' in fct 'CddStp88XXVolt_StpVoltCycle'
extern void   CddStpVolt_FinalResult(uint8 ucEndResult);                          // set 'CddStpVolt_ucEndResult' and call 'CddStp88XX_Volt' (and set 'CddStp88XX_ucStateVolt')
extern uint16 CddStpVolt_ConvMsToCnt(uint16 unTime_ms);

extern void           CddStp88XX_HalStpLwr_EmptyBuffer(void);
extern boolean        CddStp88XX_HalStpLwr_SendCReg1(boolean boSend);
extern boolean        CddStp88XX_HalStpLwr_SendCReg2(boolean boSend);
extern boolean        CddStp88XX_HalStpLwr_SendCReg3(boolean boSend);
extern boolean        CddStp88XX_HalStpLwr_SendCReg4(boolean boSend);
extern boolean        CddStp88XX_HalStpLwr_SendCRegAll(void);
extern boolean        CddStp88XX_HalStpLwr_DRV88XXCRegInit(void);
extern boolean        CddStp88XX_HalStpLwr_DRV88XXCRegDeinit(void);
extern void           CddStp88XX_HalStpLwr_ClrSCCnt_(void);
extern boolean        CddStp88XX_HalStpLwr_IncSCCnt_(void);
extern boolean        CddStp88XX_HalStpLwr_IsSCCntMax_(void);
extern uint16         CddStp88XX_HalStpLwr_GetErrVolt_(void);
extern void           CddStp88XX_HalStpLwr_ResetErrVolt_(void);
extern boolean        CddStp88XX_HalStpLwr_IsStateHoldCont_(void);
extern boolean        CddStp88XX_HalStpLwr_IsStateTestStep_(void);
extern uint32         CddStp88XX_HalStpLwr_CalcCount(const uint32 ulCount);
extern void           CddStp88XX_HalStpLwr_StepReload(const uint32 ulCount);
extern void           CddStp88XX_HalStpLwr_HandleCurAmplt_(tCurAmpltStateCddStp88XX eCurAmpltState, uint8 ucCurAmpltHold, uint8 ucCurAmpltRun);
extern void           CddStp88XX_HalStpLwr_HandleInc(boolean boIncCntActPos, boolean boIncBufIx);
extern boolean        CddStp88XX_HalStpLwr_HandleDir(void); // dir stepper (currently: SPI - future: HW-Pin)
extern boolean        CddStp88XX_HalStpLwr_GetPause(void);
extern void           CddStp88XX_HalStpLwr_HandleTestStep(void);
extern void           CddStp88XX_HalStpLwr_HandleCommonStep(const tStateHalStp eState);
extern void           CddStp88XX_HalStpLwr_StateMachine(const tCommandHalStp eCmd);
extern uint32         CddStp88XX_HalStpLwr_TransitionInitHoldCont(const tCommandHalStp eCmd);
extern uint32         CddStp88XX_HalStpLwr_TransitionTestStepHoldCont(const tCommandHalStp eCmd);
extern uint32         CddStp88XX_HalStpLwr_Transition2LastStep(const tCommandHalStp eCmd);
extern uint32         CddStp88XX_HalStpLwr_Transition2Step(const tCommandHalStp eCmd);
extern uint32         CddStp88XX_HalStpLwr_TransitionStepHold(const tCommandHalStp eCmd);
extern uint32         CddStp88XX_HalStpLwr_TransitionHoldHoldCont(const tCommandHalStp eCmd);
extern uint32         CddStp88XX_HalStpLwr_Transition2FirstStep(const tCommandHalStp eCmd);
extern uint32         CddStp88XX_HalStpLwr_Transition2TestStep(const tCommandHalStp eCmd);
extern void           CddStp88XX_HalStpLwr_InitStateFct(tAction Action);
extern void           CddStp88XX_HalStpLwr_FirstStepStateFct(tAction Action);
extern void           CddStp88XX_HalStpLwr_LastStepStateFct(tAction Action);
extern void           CddStp88XX_HalStpLwr_StepStateFct(tAction Action);
extern void           CddStp88XX_HalStpLwr_HoldStateFct(tAction Action);
extern void           CddStp88XX_HalStpLwr_HoldContStateFct(tAction Action);
extern void           CddStp88XX_HalStpLwr_TestStepStateFct(tAction Action);
extern void           CddStp88XX_HalStpLwr_ClrOLCnt_(void);
extern boolean        CddStp88XX_HalStpLwr_IncOLCnt_(void);
extern boolean        CddStp88XX_HalStpLwr_IsOLCntMax_(void);
extern boolean        CddStp88XX_HalStpLwr_SetHsMode_(boolean boHsMode, uint8 ucCurAmpltRun);
extern void           CddStp88XXTemp_StateMachine(uint8 ucIx, const tCommandCddStp88XX eCmd);

extern void           CddStp8899Com_SpiRx(uint16 unIx, uint16 unData);
extern uint16         CddStp8899Com_SpiTx(uint16 unIx);
extern boolean        CddStp8899Com_CheckSpiComSt0(tCddSpiL2Channel SpiL2Channel);

extern uint32 CddStp8899Temp_TransitionInitNorm(uint8 ucIx, const tCommandCddStp88XX eCmd);
extern uint32 CddStp8899Temp_TransitionNormLow(uint8 ucIx, const tCommandCddStp88XX eCmd);
extern uint32 CddStp8899Temp_TransitionNormHigh(uint8 ucIx, const tCommandCddStp88XX eCmd);
extern uint32 CddStp8899Temp_TransitionLowNorm(uint8 ucIx, const tCommandCddStp88XX eCmd);
extern uint32 CddStp8899Temp_TransitionHighNorm(uint8 ucIx, const tCommandCddStp88XX eCmd);
extern uint32 CddStp8899Temp_TransitionLowHigh(uint8 ucIx, const tCommandCddStp88XX eCmd);
extern void   CddStp8899Temp_StateFctInit(uint8 ucIx, tAction Action);
extern void   CddStp8899Temp_StateFctNorm(uint8 ucIx, tAction Action);
extern void   CddStp8899Temp_StateFctLow(uint8 ucIx, tAction Action);
extern void   CddStp8899Temp_StateFctHigh(uint8 ucIx, tAction Action);

//=============================================================================
// Module function parameter stubs
//=============================================================================

uint8                 CddStp8899_FctTables_UT_Dummy_Param1;
uint8                 CddStp_Simulation_HandleStatusRegisters_Param1;
uint8                 CddStp_Simulation_HandleStatusRegisters_Param2;
uint8                 CddStp_Simulation_HandleStatusRegisters_Param3;
uint8                 CddStp_Simulation_HandleStatusRegisters_Param4;
uint16                CddStp_Simulation_HandleVBatt_EcuSupply_Param1;
boolean               CddStp_Simulation_HandleSpiRxStatusBits_Param1;
boolean               CddStp_Simulation_HandleSpiRxStatusBits_Param2;
boolean               CddStp_Simulation_HandleSpiRxStatusBits_Param3;
boolean               CddStp_Simulation_HandleSpiRxStatusBits_Param4;
boolean               CddStp_Simulation_HandleSpiRxStatusBits_Param5;
boolean               CddStp_Simulation_HandleSpiRxStatusBits_Param6;
boolean               CddStp_Simulation_HandleSpiRxStatusBits_Param7;
boolean               CddStp_Simulation_HandleSpiRxStatusBits_Param8;
boolean               CddStp_Simulation_HandleSpiRxStatusBits_Param9;
uint32                CddStpDynBuf_CloseBufferr_Param1;
uint16                CddStpVolt_ConvMsToCnt_Param1;
uint8                 CddStpVolt_FinalResult_Param1;
uint8                 CddStpDyn_CalcNextHalfStepTime_Param1;
uint16                CddStpDyn_CalcNextHalfStepTime_Param2;
uint8                 CddStpDyn_Init_Param1;
boolean               CddStpDyn_Init_Param2;
uint8                 CddStpDyn_SetFreq_Param1;
uint16                CddStpDyn_SetFreq_Param2;
uint16                CddStpDyn_SetFreq_Param3;
uint16                CddStpVolt_TimerRestart_Param1;
uint8                 CddStpVolt_TimerRestart_Param2;
uint16*               IoHwAb_User_GetAdc_DIAG_VBAT_Param1;
uint8                 CddStpDyn_GetIx_Param1;
uint16                CddStpDyn_GetIx_Param2;
sint32                CddStpDyn_GetSign_Param1;
uint8                 CddStpDyn_GetStpTime_Param1;
uint8                 CddStp_Tsp_Start_Param1;
uint32                CddStp_Tsp_Start_Param2;
uint8                 CddStp_Tsp_StartHelpTimer_Param1;
uint32                CddStp_Tsp_StartHelpTimer_Param2;
uint8                 CddStp_Tsp_Stop_Param1;
uint8                 CddStp_Tsp_ResetFlag_Param1;
uint8                 CddStp_Tsp_StopHelpTmr_Param1;
uint8                 CddStp_Tsp_GetTicks_Param1;
uint32                CddStpPrjLwr_CalcRemainingTicks_Param1;
uint8                 CddStpPrj_SetEventFinishMove_Param1;
tParaFct0_Cmd         CddStp_ParaFct0_Param1;
tNvmPara_CodingArea*  CddStp_ParaFct0_Param2;

uint8                 CddStp8899Com_GetSRegBsc_Param1;
uint8*                CddStp8899Com_GetSRegBsc_Param2;
uint8                 CddStp8899Com_GetSRegFlt_Param1;
uint8*                CddStp8899Com_GetSRegFlt_Param2;
uint8                 CddStp8899Com_GetSRegDiag1_Param1;
uint8*                CddStp8899Com_GetSRegDiag1_Param2;
uint8                 CddStp8899Com_GetSRegDiag2_Param1;
uint8*                CddStp8899Com_GetSRegDiag2_Param2;
uint8                 CddStp8899Com_GetSRegDiag12_Param1;
uint8*                CddStp8899Com_GetSRegDiag12_Param2;
uint8*                CddStp8899Com_GetSRegDiag12_Param3;
uint8                 CddStp8899Com_GetSRegFltDiag2_Param1;
uint8*                CddStp8899Com_GetSRegFltDiag2_Param2;
uint8*                CddStp8899Com_GetSRegFltDiag2_Param3;
uint8                 CddStp8899Com_GetSRegBscFltDiag12_Param1;
uint8*                CddStp8899Com_GetSRegBscFltDiag12_Param2;
uint8*                CddStp8899Com_GetSRegBscFltDiag12_Param3;
uint8*                CddStp8899Com_GetSRegBscFltDiag12_Param4;
uint8*                CddStp8899Com_GetSRegBscFltDiag12_Param5;
tCddSpiL2Channel      CddStp8899Com_CheckSpiComSt0_Param1;

tCddSpiL2Channel                  CddStp8899Com_Simulation_HandleSpiRxStatusBits_Param1;
boolean                           CddStp8899Com_Simulation_HandleSpiRxStatusBits_Param2;
boolean                           CddStp8899Com_Simulation_HandleSpiRxStatusBits_Param3;
boolean                           CddStp8899Com_Simulation_HandleSpiRxStatusBits_Param4;
boolean                           CddStp8899Com_Simulation_HandleSpiRxStatusBits_Param5;
boolean                           CddStp8899Com_Simulation_HandleSpiRxStatusBits_Param6;
boolean                           CddStp8899Com_Simulation_HandleSpiRxStatusBits_Param7;
boolean                           CddStp8899Com_Simulation_HandleSpiRxStatusBits_Param8;
boolean                           CddStp8899Com_Simulation_HandleSpiRxStatusBits_Param9;
uint16                            CddStp8899Com_SpiRx_Param1;
uint16                            CddStp8899Com_SpiRx_Param2;
uint16                            CddStp_SpiRx_Param1;
uint32                            CddStp_SpiRx_Param2;
uint16                            CddStp_SpiTx_Param1;
uint16                            CddStp8899Com_SpiTx_Param1;
uint8                             CddStp8899Temp_TransitionInitNorm_Param1;
tCommandCddStp88XX                CddStp8899Temp_TransitionInitNorm_Param2;
uint8                             CddStp8899Temp_TransitionNormLow_Param1;
tCommandCddStp88XX                CddStp8899Temp_TransitionNormLow_Param2;
uint8                             CddStp8899Temp_TransitionNormHigh_Param1;
tCommandCddStp88XX                CddStp8899Temp_TransitionNormHigh_Param2;
uint8                             CddStp8899Temp_TransitionLowNorm_Param1;
tCommandCddStp88XX                CddStp8899Temp_TransitionLowNorm_Param2;
uint8                             CddStp8899Temp_TransitionHighNorm_Param1;
tCommandCddStp88XX                CddStp8899Temp_TransitionHighNorm_Param2;
uint8                             CddStp8899Temp_TransitionLowHigh_Param1;
tCommandCddStp88XX                CddStp8899Temp_TransitionLowHigh_Param2;
uint8                             CddStp8899Temp_StateFctInit_Param1;
tAction                           CddStp8899Temp_StateFctInit_Param2;
uint8                             CddStp8899Temp_StateFctNorm_Param1;
tAction                           CddStp8899Temp_StateFctNorm_Param2;
uint8                             CddStp8899Temp_StateFctLow_Param1;
tAction                           CddStp8899Temp_StateFctLow_Param2;
uint8                             CddStp8899Temp_StateFctHigh_Param1;
tAction                           CddStp8899Temp_StateFctHigh_Param2;
uint8                             CddStp88XXTemp_StateMachine_Param1;
tCommandCddStp88XX                CddStp88XXTemp_StateMachine_Param2;
uint32                            CddStpPrjLwr_GPT_StartHelp_Param1;
uint32                            CddStpPrjLwr_BothTimers_Prepare_Param1;
uint32                            CddStpPrjLwr_BothTimers_Prepare_Param2;
boolean                           CddStp8899_HalStp_SetDIR_Param1;
uint8                             CddStp88XX_HalStpLwr_SetCARunRefCnt_Param1;
boolean                           CddStp88XX_HalStpLwr_Init_Param1;
boolean                           CddStp88XX_HalStpLwr_SetHsMode__Param1;
uint8                             CddStp88XX_HalStpLwr_SetHsMode__Param2;
boolean                           CddStp88XX_HalStpLwr_SetHsMode_Param1;
uint8                             CddStp88XX_HalStpLwr_SetHsMode_Param2;
boolean                           CddStp88XX_HalStpLwr_SetTestStep_Param1;
boolean                           CddStp88XX_HalStpLwr_SpiSendCReg0_Param1;
boolean                           CddStp88XX_HalStpLwr_SpiSendCReg1_Param1;
boolean                           CddStp88XX_HalStpLwr_SpiSendCReg2_Param1;
boolean                           CddStp88XX_HalStpLwr_SpiSendCReg3_Param1;
boolean                           CddStp88XX_HalStpLwr_SpiSendCReg4_Param1;
sint32*                           CddStp88XX_HalStpLwr_GetWriteIx_Param1;
uint32*                           CddStp88XX_HalStpLwr_GetWriteIx_Param2;
sint32                            CddStp88XX_HalStpLwr_SetActPos__Param1;
sint32                            CddStp88XX_HalStpLwr_SetActPos_Param1;
sint32                            CddStp88XX_HalStpLwr_IncActPos__Param1;
sint32                            CddStp88XX_HalStpLwr_IncActPos_Param1;
boolean                           CddStp88XX_HalStpLwr_HandleMotEn__Param1;
boolean                           CddStp88XX_HalStpLwr_HandleMotEn__Param2;
boolean                           CddStp88XX_HalStpLwr_HandleMotEn_Param1;
boolean                           CddStp88XX_HalStpLwr_HandleMotEn_Param2;
boolean                           CddStp88XX_HalStpLwr_ResetStp_Param1;
boolean                           CddStp88XX_HalStpLwr_StopStp__Param1;
boolean                           CddStp88XX_HalStpLwr_StopStp_Param1;
boolean                           CddStp88XX_HalStpLwr_HandleInc_Param1;
boolean                           CddStp88XX_HalStpLwr_HandleInc_Param2;
tStateHalStp                      CddStp88XX_HalStpLwr_HandleCommonStep_Param1;
tCommandHalStp                    CddStp88XX_HalStpLwr_TransitionInitHoldCont_Param1;
tCommandHalStp                    CddStp88XX_HalStpLwr_TransitionTestStepHoldCont_Param1;
tCommandHalStp                    CddStp88XX_HalStpLwr_Transition2LastStep_Param1;
tCommandHalStp                    CddStp88XX_HalStpLwr_Transition2Step_Param1;
tCommandHalStp                    CddStp88XX_HalStpLwr_TransitionStepHold_Param1;
tCommandHalStp                    CddStp88XX_HalStpLwr_TransitionHoldHoldCont_Param1;
tCommandHalStp                    CddStp88XX_HalStpLwr_Transition2FirstStep_Param1;
tCommandHalStp                    CddStp88XX_HalStpLwr_Transition2TestStep_Param1;
tAction                           CddStp88XX_HalStpLwr_InitStateFct_Param1;
tAction                           CddStp88XX_HalStpLwr_FirstStepStateFct_Param1;
tAction                           CddStp88XX_HalStpLwr_LastStepStateFct_Param1;
tAction                           CddStp88XX_HalStpLwr_StepStateFct_Param1;
tAction                           CddStp88XX_HalStpLwr_HoldStateFct_Param1;
tAction                           CddStp88XX_HalStpLwr_HoldContStateFct_Param1;
tAction                           CddStp88XX_HalStpLwr_TestStepStateFct_Param1;
tCurAmpltStateCddStp88XX          CddStp88XX_HalStpLwr_HandleCurAmplt__Param1;
uint8                             CddStp88XX_HalStpLwr_HandleCurAmplt__Param2;
uint8                             CddStp88XX_HalStpLwr_HandleCurAmplt__Param3;
boolean*                          IoHwAb_User_GetDio_ERRN_LWR_Param1;
uint8                             CddStp88XX_DeInit_Param1;
uint8                             CddStp88XX_GetState_Param1;
uint32                            CddStp88XX_CtrlFct0_Param1;
uint8                             CddStp88XX_CtrlFct0_Param2;
tCddStpCtrlFct0_DataBuffer        CddStp88XX_CtrlFct0_Param3;
uint32                            CddStp88XX_CntFct0_Param1;
uint8                             CddStp88XX_CntFct0_Param2;
tisCntData0*                      CddStp88XX_CntFct0_Param3;
uint32                            CddStp88XX_ParaFct0_Param1;
uint8                             CddStp88XX_ParaFct0_Param2;
tisParaData0*                     CddStp88XX_ParaFct0_Param3;
uint8                             CddStp88XX_HandleStp_Param1;
uint8                             CddStpDyn_CalcNextSteps_Param1;
tHsInfo*                          CddStpDyn_CalcNextSteps_Param2;
uint32                            CddStpDyn_CalcNextSteps_Param3;
sint32                            CddStpDyn_CalcNextSteps_Param4;
sint32                            CddStpDyn_CalcNextSteps_Param5;
uint32                            CddStpDyn_CalcNextSteps_Param6;
tCddStpDyn_CalcMode               CddStpDyn_CalcNextSteps_Param7;
uint8                             CddStp88XX_Volt_Param1;
uint8                             CddStp88XX_HandleStpOnTime_Param1;
boolean                           CddStp88XX_HandleStpOnTime_Param2;
uint8                             CddStp88XX_GetStpOnTime_Param1;
uint8                             CddStp88XX_GetRefStartCnt_Param1;
uint8                             CddStp88XX_GetIsRefCnt_Param1;
uint8                             CddStp88XX_GetAhlPosDevHistCnts_Param1;
uint16*                           CddStp88XX_GetAhlPosDevHistCnts_Param2;
uint8                             CddStp88XX_StartWait88XXVoltage_Param1;
uint8                             CddStp88XX_StartWaitVoltage_Param1;
uint8                             CddStp88XX_HandleWaitVoltage_Param1;
uint8                             CddStp88XX_HandleWaitStabilize_Param1;
uint8                             CddStp88XX_ReadDRV88XXTestRegAll_Param1;
uint8                             CddStp88XX_CheckPsensSlopeAndActPos_Param1;
uint8                             CddStp88XX_CalcCorrQuota_Param1;
uint8                             CddStp88XX_HandleResetErrVolt_Param1;
boolean                           CddStp88XX_HandleResetErrVolt_Param2;
uint8                             CddStp88XX_HandleStepLoss_Param1;
uint8                             CddStp88XX_HandleStepHanging_Param1;
boolean                           CddStp88XX_HandleStepHanging_Param2;
uint8                             CddStp88XX_HandleWrongRef1Motion_Param1;
uint8                             CddStp88XX_Ctrl_Param1;
uint8                             CddStp88XX_Event_Param1;
tEventCmdCddStp                   CddStp88XX_Event_Param2;
uint8                             CddStp88XX_GetCurrentIndex_Param1;
uint8                             CddStp88XX_Transition_RefWait_Param1;
tCommandCddStp88XX                CddStp88XX_Transition_RefWait_Param2;
uint8                             CddStp88XX_Transition_Init_Param1;
tCommandCddStp88XX                CddStp88XX_Transition_Init_Param2;
uint8                             CddStp88XX_Transition_InitOff_Param1;
tCommandCddStp88XX                CddStp88XX_Transition_InitOff_Param2;
uint8                             CddStp88XX_Transition_Off_Param1;
tCommandCddStp88XX                CddStp88XX_Transition_Off_Param2;
uint8                             CddStp88XX_Transition_RefOff_Param1;
tCommandCddStp88XX                CddStp88XX_Transition_RefOff_Param2;
uint8                             CddStp88XX_Transition_Ref1_Param1;
tCommandCddStp88XX                CddStp88XX_Transition_Ref1_Param2;
uint8                             CddStp88XX_Transition_RefWaitIdle_Param1;
tCommandCddStp88XX                CddStp88XX_Transition_RefWaitIdle_Param2;
uint8                             CddStp88XX_Transition_Ref1Ref2_Param1;
tCommandCddStp88XX                CddStp88XX_Transition_Ref1Ref2_Param2;
uint8                             CddStp88XX_Transition_Ref1RefWait_Param1;
tCommandCddStp88XX                CddStp88XX_Transition_Ref1RefWait_Param2;
uint8                             CddStp88XX_Transition_Ref2RefWait_Param1;
tCommandCddStp88XX                CddStp88XX_Transition_Ref2RefWait_Param2;
uint8                             CddStp88XX_Transition_MoveIdle_Param1;
tCommandCddStp88XX                CddStp88XX_Transition_MoveIdle_Param2;
uint8                             CddStp88XX_Init__Param1;
uint8                             CddStp88XX_Init_Param1;
uint8                             CddStp88XX_TgtVal_Param1;
uint8                             CddStp88XX_Cycle0_Param1;
uint8                             CddStp88XX_Transition_IdleStby_Param1;
tCommandCddStp88XX                CddStp88XX_Transition_IdleStby_Param2;
uint8                             CddStp88XX_Transition_IdleMove_Param1;
tCommandCddStp88XX                CddStp88XX_Transition_IdleMove_Param2;
uint8                             CddStp88XX_StateFct_Init_Param1;
tAction                           CddStp88XX_StateFct_Init_Param2;
uint8                             CddStp88XX_StateFct_Off_Param1;
tAction                           CddStp88XX_StateFct_Off_Param2;
uint8                             CddStp88XX_StateFct_Stby_Param1;
tAction                           CddStp88XX_StateFct_Stby_Param2;
uint8                             CddStp88XX_StateFct_Idle_Param1;
tAction                           CddStp88XX_StateFct_Idle_Param2;
uint8                             CddStp88XX_StateFct_Move_Param1;
tAction                           CddStp88XX_StateFct_Move_Param2;
uint8                             CddStp88XX_StateFct_Ref1_Param1;
tAction                           CddStp88XX_StateFct_Ref1_Param2;
uint8                             CddStp88XX_StateFct_Ref2_Param1;
tAction                           CddStp88XX_StateFct_Ref2_Param2;
uint8                             CddStp88XX_StateFct_RefWait_Param1;
tAction                           CddStp88XX_StateFct_RefWait_Param2;
uint8                             CddStp88XX_StateFct_TestStep_Param1;
tAction                           CddStp88XX_StateFct_TestStep_Param2;
uint8                             CddStp88XX_StateFct_Err_Param1;
tAction                           CddStp88XX_StateFct_Err_Param2;
uint8                             CddStp88XX_SetCurrent_Param1;
uint8                             CddStp88XX_Transition_ErrClr_Param1;
tCommandCddStp88XX                CddStp88XX_Transition_ErrClr_Param2;
uint8                             CddStp88XX_Transition_TestStep_Param1;
tCommandCddStp88XX                CddStp88XX_Transition_TestStep_Param2;
uint8                             CddStp88XX_Transition_TestStepIdle_Param1;
tCommandCddStp88XX                CddStp88XX_Transition_TestStepIdle_Param2;
uint8                             CddStp88XX_Transition_Err_Sub_Param1;
tCommandCddStp88XX                CddStp88XX_Transition_Err_Sub_Param2;
boolean                           CddStp88XX_Transition_Err_Sub_Param3;
uint8                             CddStp88XX_Transition_Err_Param1;
tCommandCddStp88XX                CddStp88XX_Transition_Err_Param2;
uint8                             CddStp88XX_Transition_OffStby_Param1;
tCommandCddStp88XX                CddStp88XX_Transition_OffStby_Param2;
uint8                             CddStp88XX_Transition_OffIdle_Param1;
tCommandCddStp88XX                CddStp88XX_Transition_OffIdle_Param2;
uint32*                           CddStp_GetVirtData_TestIfc_Param1;
tiulCtrlCmd                       CddStp_CtrlFct0_Param1;
tiucCtrlIndex                     CddStp_CtrlFct0_Param2;
tisCtrlData0*                     CddStp_CtrlFct0_Param3;
tieStepperIndex                   CddStp_StartRefRun_Param1;
ti16StepperPosition_halfsteps     CddStp_StartRefRun_Param2;
tieStepperIndex                   roCddStpStartRefRun_Param1;
ti16StepperPosition_halfsteps     roCddStpStartRefRun_Param2;
uint8                             CddStp88XX_Transition_MoveOff_Param1;
tCommandCddStp88XX                CddStp88XX_Transition_MoveOff_Param2;
uint8                             CddStp88XX_Transition_StbyIdle_Param1;
tCommandCddStp88XX                CddStp88XX_Transition_StbyIdle_Param2;
boolean                           CddStp_SetOLIgnore_Param1;
uint8                             CddStp8899Com_SetFaultClr_Param1;
boolean                           CddStp88XX_HalStpLwr_SendCReg1_Param1;
boolean                           CddStp88XX_HalStpLwr_SendCReg2_Param1;
boolean                           CddStp88XX_HalStpLwr_SendCReg3_Param1;
boolean                           CddStp88XX_HalStpLwr_SendCReg4_Param1;
uint8                             CddStp88XX_CondStpStateBitIsReady_Param1;
uint8                             CddStp88XX_StateMachine_Param1;
tCommandCddStp88XX                CddStp88XX_StateMachine_Param2;

//=============================================================================
// Module function return value stubs
//=============================================================================

boolean                   CddStp_Simulation_IsSimActive_RetVal;
uint8                     CddStp8899_FctTables_UT_Dummy_RetVal;
boolean                   CddStp_Simulation_HandleDriverDefect_FatalError_RetVal;
boolean                   CddStp_Simulation_HandleLowTempMode_RetVal;
boolean                   CddStp_Simulation_HandleVBatt_EcuSupply_RetVal;
uint16                    CddStpVolt_ConvMsToCnt_RetVal;
uint16                    CddStpDyn_CalcNextHalfStepTime_RetVal;
boolean                   CddStpDyn_SetFreq_RetVal;
boolean                   CddStp_ParaFct0_RetVal;
uint8                     CddStpDyn_GetIx_RetVal;
sint32                    CddStpDyn_GetSign_RetVal;

uint16                    CddStpDyn_GetStpTime_RetVal;
uint32                    CddStp_Tsp_GetTicks_RetVal;
uint32                    CddStpPrjLwr_CalcRemainingTicks_RetVal;

boolean                   CddStp8899Com_GetSRegBsc_RetVal;
boolean                   CddStp8899Com_GetSRegFlt_RetVal;
boolean                   CddStp8899Com_GetSRegDiag1_RetVal;
boolean                   CddStp8899Com_GetSRegDiag2_RetVal;
boolean                   CddStp8899Com_GetSRegDiag12_RetVal;
boolean                   CddStp8899Com_GetSRegFltDiag2_RetVal;
boolean                   CddStp8899Com_GetSRegBscFltDiag12_RetVal;
boolean                   CddStp8899Com_CheckSpiComSt0_RetVal;
uint16                    CddStp8899Com_SpiTx_RetVal;
uint32                    CddStp_SpiTx_RetVal;
uint32                    CddStp8899Temp_TransitionInitNorm_RetVal;
uint32                    CddStp8899Temp_TransitionNormLow_RetVal;
uint32                    CddStp8899Temp_TransitionNormHigh_RetVal;
uint32                    CddStp8899Temp_TransitionLowNorm_RetVal;
uint32                    CddStp8899Temp_TransitionHighNorm_RetVal;
uint32                    CddStp8899Temp_TransitionLowHigh_RetVal;
uint32                    CddStpPrjLwr_GPT_GetRemainingCnt_RetVal;
uint32                    CddStp88XX_HalStpLwr_GetHsCnt_RetVal;
uint32                    CddStp88XX_HalStpLwr_GetIrunTime_RetVal;
boolean                   CddStp88XX_HalStpLwr_Init_RetVal;
boolean                   CddStp88XX_HalStpLwr_SetHsMode__RetVal;
boolean                   CddStp88XX_HalStpLwr_SetHsMode_RetVal;
boolean                   CddStp88XX_HalStpLwr_GetHsMode_RetVal;
boolean                   CddStp88XX_HalStpLwr_IsTestStepDone_RetVal;
boolean                   CddStp88XX_HalStpLwr_SetTestStep_RetVal;
boolean                   CddStp88XX_HalStpLwr_DRV88XXCRegInit_RetVal;
boolean                   CddStp88XX_HalStpLwr_DRV88XXCRegDeinit_RetVal;
boolean                   CddStp88XX_HalStpLwr_SpiSendCReg0_RetVal;
boolean                   CddStp88XX_HalStpLwr_SpiSendCReg1_RetVal;
boolean                   CddStp88XX_HalStpLwr_SpiSendCReg2_RetVal;
boolean                   CddStp88XX_HalStpLwr_SpiSendCReg3_RetVal;
boolean                   CddStp88XX_HalStpLwr_SpiSendCReg4_RetVal;
boolean                   CddStp88XX_HalStpLwr_SpiSendCRegAll_RetVal;
boolean                   CddStp88XX_HalStpLwr_IsDriverReset_RetVal;
boolean                   CddStp88XX_HalStpLwr_IncOLCnt__RetVal;
boolean                   CddStp88XX_HalStpLwr_IncOLCnt_RetVal;
boolean                   CddStp88XX_HalStpLwr_IsOLCntMax__RetVal;
boolean                   CddStp88XX_HalStpLwr_IsOLCntMax_RetVal;
boolean                   CddStp88XX_HalStpLwr_IncSCCnt__RetVal;
boolean                   CddStp88XX_HalStpLwr_IncSCCnt_RetVal;
boolean                   CddStp88XX_HalStpLwr_IsSCCntMax__RetVal;
boolean                   CddStp88XX_HalStpLwr_IsSCCntMax_RetVal;
boolean                   CddStp88XX_HalStpLwr_GetPsensPort_RetVal;
uint16                    CddStp88XX_HalStpLwr_GetErrVolt__RetVal;
uint32                    CddStp88XX_HalStpLwr_GetErrVolt_RetVal;
boolean                   CddStp88XX_HalStpLwr_IsFinishMove_RetVal;
boolean                   CddStp88XX_HalStpLwr_IsStateTestStep__RetVal;
uint32                    CddStp88XX_HalStpLwr_GetWriteIx_RetVal;
sint32                    CddStp88XX_HalStpLwr_GetActPos__RetVal;
sint32                    CddStp88XX_HalStpLwr_GetActPos_RetVal;
uint8                     CddStp88XX_HalStpLwr_GetPhaseCounter__RetVal;
uint8                     CddStp88XX_HalStpLwr_GetPhaseCounter_RetVal;
uint8                     CddStp88XX_HalStpLwr_GetCurAmplt_RetVal;
boolean                   CddStp88XX_HalStpLwr_HandleDir_RetVal;
boolean                   CddStp88XX_HalStpLwr_GetPause_RetVal;
uint32                    CddStp88XX_HalStpLwr_TransitionInitHoldCont_RetVal;
uint32                    CddStp88XX_HalStpLwr_TransitionTestStepHoldCont_RetVal;
uint32                    CddStp88XX_HalStpLwr_Transition2LastStep_RetVal;
uint32                    CddStp88XX_HalStpLwr_Transition2Step_RetVal;
uint32                    CddStp88XX_HalStpLwr_TransitionStepHold_RetVal;
uint32                    CddStp88XX_HalStpLwr_TransitionHoldHoldCont_RetVal;
uint32                    CddStp88XX_HalStpLwr_Transition2FirstStep_RetVal;
uint32                    CddStp88XX_HalStpLwr_Transition2TestStep_RetVal;
tStpInfo*                 CddStp88XX_HalStpLwr_GetStpInfo__RetVal;
tStpInfo*                 CddStp88XX_HalStpLwr_GetStpInfo_RetVal;
teRte_IdentityConfig      Appl_GetIdentity_RetVal;
uint32                    CddStp88XX_GetStpOnTime_RetVal;
uint16                    CddStp88XX_GetRefStartCnt_RetVal;
uint16                    CddStp88XX_GetIsRefCnt_RetVal;
boolean                   CddStp88XX_HandleWaitStabilize_RetVal;
boolean                   CddStp88XX_HandleStepHanging_RetVal;
uint8                     CddStp88XX_GetCurrentIndex_RetVal;
uint32                    CddStp88XX_Transition_RefWait_RetVal;
uint32                    CddStp88XX_Transition_Init_RetVal;
uint32                    CddStp88XX_Transition_InitOff_RetVal;
uint32                    CddStp88XX_Transition_Off_RetVal;
uint32                    CddStp88XX_Transition_RefOff_RetVal;
uint32                    CddStp88XX_Transition_Ref1_RetVal;
uint32                    CddStp88XX_Transition_RefWaitIdle_RetVal;
uint32                    CddStp88XX_Transition_Ref1Ref2_RetVal;
uint32                    CddStp88XX_Transition_Ref1RefWait_RetVal;
uint32                    CddStp88XX_Transition_Ref2RefWait_RetVal;
uint32                    CddStp88XX_Transition_MoveIdle_RetVal;
uint32                    CddStp88XX_Transition_IdleStby_RetVal;
uint32                    CddStp88XX_Transition_IdleMove_RetVal;
uint32                    CddStp88XX_Transition_ErrClr_RetVal;
uint32                    CddStp88XX_Transition_OffIdle_RetVal;
uint32                    CddStp88XX_Transition_OffStby_RetVal;
uint32                    CddStp88XX_Transition_Err_RetVal;
uint32                    CddStp88XX_Transition_Err_Sub_RetVal;
uint32                    CddStp88XX_Transition_TestStepIdle_RetVal;
uint32                    CddStp88XX_Transition_TestStep_RetVal;
void*                     CddStp_GetVirtData_TestIfc_RetVal;
Std_ReturnType            CddStp_StartRefRun_RetVal;
Std_ReturnType            roCddStpOff_RetVal;
Std_ReturnType            CddStp_StpOff_RetVal;
Std_ReturnType            roCddStpOn_RetVal;
Std_ReturnType            CddStp_StpOn_RetVal;
uint32                    CddStp88XX_Transition_MoveOff_RetVal;
uint32                    CddStp88XX_Transition_StbyIdle_RetVal;
boolean                   CddStp88XX_HalStpLwr_SendCReg1_RetVal;
boolean                   CddStp88XX_HalStpLwr_SendCReg2_RetVal;
boolean                   CddStp88XX_HalStpLwr_SendCReg3_RetVal;
boolean                   CddStp88XX_HalStpLwr_SendCReg4_RetVal;
boolean                   CddStp88XX_CondStpStateBitIsReady_RetVal;
uint8                     CddStp88XXVolt_GetStpVoltState_RetVal;
boolean                   Cod_LwrRichtungRe_RetVal;
boolean                   Cod_LwrRichtungLi_RetVal;
boolean                   Cod_LwrTestKeinFehlereintrag_RetVal;
boolean                   Cod_StpQuelleTT_RetVal;
boolean                   CddStp88XX_HalStpLwr_SendCRegAll_RetVal;

//=============================================================================
// Module static variables inside functions 
//=============================================================================

CONST_AL tsLpit_CfgData Lpit_sLpitDatatCfg;
uint8                   ucQuelle;
uint8                   ucNumOfSteppers_EFT;
uint8                   ucDlyCntr;
boolean                 bResult;

boolean                 bIsLowtemp; // 'CddStp8899Temp_CheckLowTemp'
TIMER                   CddStp88XX_astWaitErrPrealarm[CFA_CNT_STP_88XX];
uint8                   ucNormalTiming;
boolean                 boCddStp_Cycle10ms_Initialized;
boolean                 CddStp8899_boEftCodValid; // flag to check only once
tFTimer                 CddStp88XX_aftWaitErrInh[CFA_CNT_STP_88XX];
boolean                 CddStp_boDioErrLwr;
boolean                 boCddStp_Cycle_Initialized;
tStpState               CddStp88XX_aStpStateOld[CFA_CNT_STP_88XX];
tStateTempCddStp88XX    CddStp88XX_aeTempState[CFA_CNT_STP_88XX];
boolean                 CddStp_UnitTest__TspIsRunning;
boolean                 CddStp_UnitTest__TspIsIni;
unsigned long           CddStp_UnitTest__u32Voltage_mV;

tCddStp88XX_Attr        CddStp88XX_aAttr[4];

#endif // TEST_2023_08_25_H_

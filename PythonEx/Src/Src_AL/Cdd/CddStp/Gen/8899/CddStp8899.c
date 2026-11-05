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
/// \file  CddStp8899.c
///
/// \brief  Texas Instruments TI-DRV8899 specific complex device driver
///
/// \descr  Main part of Stepper Driver 
///
///         State-Machine:
//            * Init     -> Off
//            * Off      -> TestStep (or '-> Idle'  or '-> Standby')
//            * TestStep -> Idle
//            * Idle     -> Move
//            *          -> Ref1  = (tStateCddStp88XX)'CddStp88XX_eStateRef1' in var 'CddStp88XX_aeState'
//            * Ref1     -> Ref2
//            * Ref2     -> RefWait
//            * RefWait  -> Idle
///
///         Additional information can be found in the design description (Link:
///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
///
/// \author Wuesteney, Ulrich ALRT/EEG4 * (wu82rt)
///         J. Kling ALRT-EES6 (f84304b)
//-----------------------------------------------------------------------------


//
// biDisOLDetect
//    OL: NICHT Anhalten/Abschalten!!  -- danach: LATCH LOESCHEN!!
//    Check: Ist die Unterdruckung der OL-Erkennung WAHREND der Verstellung (move & ref) notwendig
//    biMotEn / biTbdEnOlDtctn / EnOl
//    Disable OL-Detection during Moving (no Pseudo-Errors in HCM)
//    Die OL - Erkennung war im CddStp deaktiviert(siehe Verstellungs - State - Funktionen CddStp88XX_StateFct_Move(), CddStp88XX_StateFct_Ref1() und CddStp88XX_StateFct_Ref2() im Fall ActEntry :
//      CddStp88XX_aBitsMod[ucIx].Bit.biDisOLDetect = 1u
//      aber da in den Registern des OnSemi - Schrittmotortreibers NCV70516 die OL - Information nicht ge - latch - t war, ging sie nach einer Reparatur des Fehlers wahrend der Verstellung verloren!
//
//
//
// (page - 33) 7.3.11.4 Open - Load Detection(OL)
// If the winding current in any coil drops below the open load current threshold(IOL = 30mA)
//  and the ITRIP level set by the indexer,
//  and if this condition persists for more than the open load detection time(tOL = 200ms),
//  an open - load condition is detected.
// The EN_OL bit must be '1' to enable open load detection.
// When an open load fault is detected, the OL and FAULT bits are latched high in the SPI register and the nFAULT pin is driven low.
// If the OL_A bit is high, it indicates an open load fault in winding A, between AOUT1 and AOUT2.
// Similarly, an open load fault between BOUT1 and BOUT2 causes the OL_B bit to go high.
// Normal operation resumes and the nFAULT line is released when the open load condition is removed
//  and a clear faults command has been issued either through the CLR_FLT bit or an nSLEEP reset pulse.
// The fault also clears when the device is power cycled or comes out of sleep mode.
// 
// IOL Open load current threshold 30 mA
// tOL Open load detection time EN_OL = 1b 200 ms
// ITRIP Current trip accuracy
//   IO = 1 A, 10 % to 20 % current setting  -13%   ... 10 %
//   IO = 1 A, 20 % to 67 % current setting   -8%   ...  8 %
//   IO = 1 A, 67 % to 100 % current setting  -7.5% ...  7.5%
// Table 23. CTRL4 Control Register Field Descriptions
//   Bit7 : CLR_FLT - Write '1' to this bit to clear all latched fault bits. This bit automatically resets after being written.
//   'CddStp88XX_HalStpLwr_SendCReg4' & 'xxx_CLR_FLT' & 'biTbdClrTiFaultBits' (& 'CDDSTP_ITM')
//   Reset in 'CddStp88XX_HalStp_eStateHoldCont' or in 'CddStp88XX_StateFct_Idle'?


//=============================================================================
// includes
//=============================================================================

#include <Std_Types.h>
#include <AL_Helper.h> //-- STATIC_AL
#include <Util_Time.h>
//#include <CodM.h> //TODO CddStp tbd remove workaround to get EFT data

#include <CddSpi.h>

//#include <Rte_ctacCddStp.h>

#include <CddStpIfc.h>
#include <CddStpCfg.h>      // incl. nothing

#ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
#include <../Cdd/CddStp/CddStpData.h>
#include <../Cdd/CddStp/Cfg/CddStp_Cfg.h>
#include <../Cdd/CddStp/CddStpPrj.h>
#include <CddEft.h>
#include <Rte.h>
#else // Unit-Tests!
  //#define CFA_CNT_STP_88XX   (4u)
#define CFG_Stp_IdxVer     (0u)   // Index  of Vertical   Stepper

#include <CddStpPrj.h>
#include <CddStpData.h>
#include <CddStp_Cfg.h>
#include <stddef.h>
#include <Gpt.h>

#define LIT_SigWarn (0x00u)  // do not change numbers

#define GptConf_GptChannelConfiguration_StpTimer0  0U
#endif // UNIT_TEST

#ifdef CDDSTP_CFG_SIMULATION // defined in '.\Asr6\Src\Src_AL\Cust\Bw\Bw16\App\Bsw\Cdd\CddStp\CddStpPrj.h'
#include <CddStp_Simulation.h>
#endif // CDDSTP_CFG_SIMULATION

#include <CddStpDyn.h>
#include <CddStp8899Types.h>
#include <CddStp8899Com.h>
#include <CddStp88XX_FctTables.h>
#include <CddStp88XXVolt.h>
//#include <../Cdd/CddStp/Gen/88XX/CddStp88XX_HalStp.h>


#include <Bsw/IoHwAb/IoHwAbUser.h>

// jk-tbd
#define SYSVOLT_VBATSDriverReset 5000u // [mV]  5.0V - DRV88XX specific
STATIC_AL uint32 IoHwAb_SystemTick_1Ms; // every millisecond this variable is incremented
#define ApplMainResetStpAlternativeTriggerCnt(x)  ((void)(x)) //tbd

//typedef enum
//{
//  ePluggedLeft   = 0,
//  ePluggedRight  = 1,
//  eIdentityUndef = 255
//} tIdentityConfig;

STATIC_AL teRte_IdentityConfig Appl_GetIdentity(void) // { return ePluggedLeft;  }
{
 teRte_IdentityConfig eIdentity;
 teRte_MountingSide eMountingSide = { 0 };

 // Read MountingSide RTE port
 (void)Rte_Read_IoHwAbUser_GetMountingSide(&eMountingSide);

 switch (eMountingSide)
 {
 case eMountedLeft:
  eIdentity = ePluggedLeft;
  break;

 case eMountedRight:
  eIdentity = ePluggedRight;
  break;

 default:
  eIdentity = eIdentityUndef;
  break;
 }
 return eIdentity;
}


// ---------------------------------------------------------------------------
// local prototypes
// ---------------------------------------------------------------------------
STATIC_AL void            CddStp88XX_DeInit                   (uint8 ucIx);
STATIC_AL void            CddStp88XX_CheckPsensSlopeAndActPos (uint8 ucIx);
STATIC_AL void            CddStp88XX_CalcCorrQuota            (/*const*/ uint8 ucIx);
STATIC_AL void            CddStp88XX_HandleStp                (uint8 ucIx);
STATIC_AL void            CddStp88XX_HandleStpOnTime          (uint8 ucIx, boolean boStpOn);
STATIC_AL uint32          CddStp88XX_GetStpOnTime             (uint8 ucIx);
STATIC_AL uint16          CddStp88XX_GetRefStartCnt           (uint8 ucIx);
STATIC_AL uint16          CddStp88XX_GetIsRefCnt              (uint8 ucIx);
STATIC_AL void            CddStp88XX_GetAhlPosDevHistCnts     (uint8 ucIx, uint16* punAhlPosDevHistCnts);
STATIC_AL void            CddStp88XX_StartWait88XXVoltage     (uint8 ucIx);
STATIC_AL void            CddStp88XX_StartWaitVoltage         (uint8 ucIx);
STATIC_AL void            CddStp88XX_ReadDRV88XXTestRegAll    (uint8 ucIx);

STATIC_AL void            CddStp88XX_SetCurrent               (uint8 ucIx);

STATIC_AL void            CddStp88XX_SetStpStateBitIsReady    (uint8 ucIx);
STATIC_AL boolean         CddStp88XX_CondStpStateBitIsReady   (uint8 ucIx);
STATIC_AL void            CddStp88XX_StateMachine(uint8 ucIx, const tCommandCddStp88XX eCmd);
STATIC_AL uint32          CddStp88XX_Transition_Init(uint8 ucIx, const tCommandCddStp88XX eCmd);
STATIC_AL uint32          CddStp88XX_Transition_InitOff(uint8 ucIx, const tCommandCddStp88XX eCmd);
STATIC_AL uint32          CddStp88XX_Transition_Off(uint8 ucIx, const tCommandCddStp88XX eCmd);
STATIC_AL uint32          CddStp88XX_Transition_StbyIdle(uint8 ucIx, const tCommandCddStp88XX eCmd);
STATIC_AL uint32          CddStp88XX_Transition_IdleStby(uint8 ucIx, const tCommandCddStp88XX eCmd);
STATIC_AL uint32          CddStp88XX_Transition_MoveIdle(uint8 ucIx, const tCommandCddStp88XX eCmd);
STATIC_AL uint32          CddStp88XX_Transition_MoveOff(uint8 ucIx, const tCommandCddStp88XX eCmd);
STATIC_AL uint32          CddStp88XX_Transition_IdleMove(uint8 ucIx, const tCommandCddStp88XX eCmd);
STATIC_AL uint32          CddStp88XX_Transition_RefOff(uint8 ucIx, const tCommandCddStp88XX eCmd);
STATIC_AL uint32          CddStp88XX_Transition_Ref1(uint8 ucIx, const tCommandCddStp88XX eCmd);
STATIC_AL uint32          CddStp88XX_Transition_RefWait(uint8 ucIx, const tCommandCddStp88XX eCmd);
STATIC_AL uint32          CddStp88XX_Transition_RefWaitIdle(uint8 ucIx, const tCommandCddStp88XX eCmd);
STATIC_AL uint32          CddStp88XX_Transition_Ref1Ref2(uint8 ucIx, const tCommandCddStp88XX eCmd);
STATIC_AL uint32          CddStp88XX_Transition_Ref1RefWait(uint8 ucIx, const tCommandCddStp88XX eCmd); // * Sref reference run uses Psens *
STATIC_AL uint32          CddStp88XX_Transition_Ref2RefWait(uint8 ucIx, const tCommandCddStp88XX eCmd);
STATIC_AL uint32          CddStp88XX_Transition_TestStep(uint8 ucIx, const tCommandCddStp88XX eCmd);
STATIC_AL uint32          CddStp88XX_Transition_TestStepIdle(uint8 ucIx, const tCommandCddStp88XX eCmd);
STATIC_AL uint32          CddStp88XX_Transition_Err(uint8 ucIx, const tCommandCddStp88XX eCmd);
STATIC_AL uint32          CddStp88XX_Transition_Err_Sub(uint8 ucIx, const tCommandCddStp88XX eCmd, boolean boLessThanErrVoltHiLimit);
STATIC_AL uint32          CddStp88XX_Transition_OffStby(uint8 ucIx, const tCommandCddStp88XX eCmd);
STATIC_AL uint32          CddStp88XX_Transition_OffIdle(uint8 ucIx, const tCommandCddStp88XX eCmd);
STATIC_AL uint32          CddStp88XX_Transition_ErrClr(uint8 ucIx, const tCommandCddStp88XX eCmd);

STATIC_AL void            CddStp88XX_StateFct_Init            (uint8 ucIx, tAction Action);
STATIC_AL void            CddStp88XX_StateFct_Off             (uint8 ucIx, tAction Action);
STATIC_AL void            CddStp88XX_StateFct_Stby            (uint8 ucIx, tAction Action);
STATIC_AL void            CddStp88XX_StateFct_Idle            (uint8 ucIx, tAction Action);
STATIC_AL void            CddStp88XX_StateFct_Move            (uint8 ucIx, tAction Action);
STATIC_AL void            CddStp88XX_StateFct_Ref1            (uint8 ucIx, tAction Action);
STATIC_AL void            CddStp88XX_StateFct_Ref2            (uint8 ucIx, tAction Action);
STATIC_AL void            CddStp88XX_StateFct_RefWait         (uint8 ucIx, tAction Action);
STATIC_AL void            CddStp88XX_StateFct_TestStep        (uint8 ucIx, tAction Action);
STATIC_AL void            CddStp88XX_StateFct_Err             (uint8 ucIx, tAction Action);

STATIC_AL void            CddStp88XX_Init_                    (uint8 ucIx);
STATIC_AL void            CddStp88XX_Ctrl                     (uint8 ucIx);
STATIC_AL boolean         CddStp88XX_HandleWaitStabilize      (uint8 ucIx);
STATIC_AL void            CddStp88XX_HandleWaitVoltage        (uint8 ucIx);
STATIC_AL void            CddStp88XX_HandleResetErrVolt       (uint8 ucIx, boolean boClearSRegsScOl);
STATIC_AL void            CddStp88XX_HandleStepLoss           (uint8 ucIx);
STATIC_AL boolean         CddStp88XX_HandleStepHanging        (uint8 ucIx, boolean boRef);
STATIC_AL void            CddStp88XX_HandleWrongRef1Motion    (uint8 ucIx);
// jk-tbd - No Driver-Reset for TI - static void            CddStp88XX_HandleDriverReset        (uint8 ucIx);
STATIC_AL void            CddStp88XX_StpStateVoltNormSet      (void);
STATIC_AL void            CddStp88XX_StpStateVoltNormClear    (void);
STATIC_AL void            CddStp88XX_StpStateOvSet            (void);
STATIC_AL void            CddStp88XX_StpStateOvClear          (void);
STATIC_AL void            CddStp88XX_StpStateUvSSMSet         (void);                  // undervoltage soft stop motion
STATIC_AL void            CddStp88XX_StpStateUvSSMClear       (void);                  // undervoltage soft stop motion
STATIC_AL uint8           CddStp88XX_GetCurrentIndex          (const uint8 ucCurrent);

STATIC_AL void            CddStp88XX_EftCodingLr_2            (void);


// ---------------------------------------------------------------------------
// preprocessor definitions
// ---------------------------------------------------------------------------
#define CDDSTP88XX_WaitVoltage_FTimer     FT_MSEC(300u) // time in case of voltage out of range change or voltage is low or over to debounce voltage toggling [ms]
#define CDDSTP88XX_WaitStabilize_FTimer   FT_MSEC(39u)  // time in case transition from OffState or StandbyState to IdleState to stabilize stepper rotor [ms]

#define CDDSTP88XX_WaitErrInh_FTimer      FT_MSEC(50u)  // duration of set time after negative slope of ErrInh state message bit [ms]

#define CDDSTP88XX_WaitSRegAll_FTimer     FT_MSEC(50u)  // time to check all status registers for OL or SC error detection
#define CDDSTP88XX_WaitOLCheck_FTimer     FT_MSEC(200u)  // time to detect OL error

#define CDDSTP88XX_PosIgnoreMissingPsensP (256)         // actual position after failed Sref reference // * Sref reference run uses Psens *
#define CDDSTP88XX_PosIgnoreMissingPsensN (-512)        // actual position after failed Sref reference // * Sref reference run uses Psens *

#define CDDSTP88XX_ErrVoltHiLimitSCCntMax (3u)          // maximal count of consecutively changes in StateOff in case of ErrVoltHiLimit and SC while movement

#define CDDSTP88XX_TickMax                (0x7000FFFFu) // maximal fast timer FTimer tick to avoid calculation overflow (value is less than 0x7FFFFFFF)

#define CDDSTP88XX_SReg3MspHsMask         (0x70u)       // mask of DRV8899 status register RX content (MSP) to suppress parity bit, MSP offset of TestStep to use only half step value (MSP reset value 0x10 +/- TestStep 0x04 = 0x14/0x0C at 0 HS, 0x24/0x1C at 1 HS, 0x34/0x2C at 2 HS, 0x44/0x3C at 3 HS, 0x54/0x4C at 4 HS, 0x64/0x5C at 5 HS, 0x74/0x6C at 6 HS, 0x04/0x7C at 7 HS)
#define CDDSTP88XX_SReg3Msp2MsCnt         (0x08u)       // count of 2 micro steps to subtract from DRV8899 status register RX content (MSP) to get the same HS value in both coded directions (biRichtung = 0/1): reset value    0x0C/0x04 at 0 HS, 0x1C/0x14 at 1 HS, 0x2C/0x24 at 2 HS, 0x3C/0x34 at 3 HS, 0x4C/0x44 at 4 HS, 0x5C/0x54 at 5 HS, 0x6C/0x64 at 6 HS, 0x7C/0x74 at 7 HS)
#define CDDSTP88XX_HsPerCycleMask         (0x0007)      // mask to get modulo 8 HS count per cycle
#define CDDSTP88XX_NegRefCntMask          (0xFFF8)      // mask to get modulo 8 HS count greater in case of negative reference HS count, because of 8 HS per cycle

#define CDDSTP88XX_ACTPOSMEMCNT_MAX       (30u) /*10u*/ // maximal count of task calls (CDDSTP_SamplingTime) with no change of actual position in state Move, Ref1, Ref2 to avoid hanging in case of hanging CddStp8899_HalStp state machine in StateStep because timer INT mismatch is part of Move, Ref1, Ref2 (note maximum of Cod_LwrVorbestZeit(), Cod_LwrHsZeitUmkehr(), Cod_NachbestZeit())! CddStp_HalStp is reset and in case of Ref1/2: CddStpDyn is initialized!

#define CDDSTP88XX_REF1ERRPSENS_MAX       (1u)          // maximal count of Ref1 pseudo ErrPsens
#define CDDSTP88XX_WRONGREF1POSBEFORE     (10)          // 10 HS before Ref1 phase is finished to avoid pseudo ErrPsens

// DRV8899 specific definitions
// MSP: (Translator) Micro-Step-Position
// jk-MSP #define CDDSTP8899_MSP_1_4                3u             // shift right count to get 1/4 (SM 011) from 1/32 (SM 000) MS
// jk-MSP #define CDDSTP8899_Mask_PC                (CDDSTP8899_Mask_MSP >> CDDSTP8899_MSP_1_4) // rest of MSP in CR4 after shift right to get 1/4 from 1/16 MS
// jk-MSP #define CDDSTP8899_ResetVal_MSP           0x10           // reset read value of SR3 MSP register


// ---------------------------------------------------------------------------
// type definitions
// ---------------------------------------------------------------------------
typedef enum
{
 CDDSTP88XX_ePosInit = 0,  // must be 0 (init. value)
 CDDSTP88XX_ePosLower,                 // 1 // Psens position < Psens.ucPosFehlerGrenze
 CDDSTP88XX_ePosMiddleUp,              // 2 // Psens position changes from CDDSTP88XX_ePosLower
 CDDSTP88XX_ePosMiddleDown,            // 3 // Psens position changes from CDDSTP88XX_ePosUpper
 CDDSTP88XX_ePosUpper                  // 4 // Psens position > ucPosFehlerGrenze
} tDesensPsensPosStateCddStp88XX;

typedef enum
{
 CDDSTP88XX_eSlopeNone = 0,  // must be 0 (init. value)
 CDDSTP88XX_eSlopeSingleOrSameSign,    // 1 // one single Psens slope found
 CDDSTP88XX_eSlopesDiffSign            // 2 // multiple Psens slopes with different signs found
} tDesensPsensSlopeCddStp88XX;


// ---------------------------------------------------------------------------
// const
// ---------------------------------------------------------------------------

// calculation of driver current: phys. value --> current index
#define CDDSTP88XX_CurrentTableSize  15u   // only 2^x-1 allowed


// jk-tbd
STATIC_AL void IoHwAb_User_GetDio_ERRN_LWR(boolean* pResult)
{
 /*PORT_INPUT2(P,  8,  0, pResult);*/
 STATIC_UT(boolean, CddStp_boDioErrLwr, FALSE);
 *pResult = CddStp_boDioErrLwr;
}


//=============================================================================
// variables
//=============================================================================

/* orig: 'uint8' */ tCddStp8899Com_StatReg_Basic CddStp8899_aSRegBasic[CFA_CNT_STP_88XX]; // Basic-Status - comes each time 'automatically' - 1 | 1 | UVLO | CPUV | OCP | RSVD | TF | OL
/* orig: 'uint8' */ tCddStp8899Com_StatReg_Fault CddStp8899_aSRegFault[CFA_CNT_STP_88XX]; // Fault-Status                                   - FAULT | SPI_ERROR | UVLO | CPUV | OCP | RSVD | TF | OL
/* orig: 'uint8' */ tCddStp8899Com_StatReg_Diag1 CddStp8899_aSRegDiag1[CFA_CNT_STP_88XX]; // Diag-Status-1                                  - OCP_LS2_B | OCP_HS2_B | OCP_LS1_B | OCP_HS1_B | OCP_LS2_A | OCP_HS2_A | OCP_LS1_A | OCP_HS1_A
/* orig: 'uint8' */ tCddStp8899Com_StatReg_Diag2 CddStp8899_aSRegDiag2[CFA_CNT_STP_88XX]; // Diag-Status-2                                  - UTW | OTW | OTS | RSVD | OL_B | OL_A

STATIC_AL uint8                                  CddStp88XX_ucStateVolt;                      // state of Volt state machine - StateVoltOff=0, StateVoltUnder=1, StateVoltNormal=2, StateVoltOver=3, StateVoltStartValue=0xFF
STATIC_AL uint16                                 CddStp88XX_unDIAG_VBAT;                      // Vbat [mV] 

STATIC_AL uint32                                 CddStp88XX_aulStpOnTime[CFA_CNT_STP_88XX];
STATIC_AL uint32                                 CddStp88XX_aulStpOnStart[CFA_CNT_STP_88XX];

STATIC_AL uint16                                 CddStp88XX_aunRefStartCnt[CFA_CNT_STP_88XX];
STATIC_AL uint16                                 CddStp88XX_aunIsRefCnt[CFA_CNT_STP_88XX];
#if((CFA_CNT_STP_ONBRD == 2) && (CFA_CNT_STPVER0_ONBRD != 2))
// 2nd on-board stepper as horizontal (not as workaround for 2nd on-board stepper as vertical)
STATIC_AL uint16                               CddStp88XX_aunAhlPosDevHistCnts[CDDSTP_POSDEVHIST_MAX];  // for Hor stepper only
STATIC_AL uint8                                CddStp88XX_ucAhlPosDevHistOffset;                          // for Hor stepper only
STATIC_AL uint8                                CddStp88XX_ucAhlPosDevHistBase;                            // for Hor stepper only
//PDH STATIC_AL uint16                         CddStp88XX_ucAhlPosDevHistFactor;                          // for Hor stepper only
STATIC_AL sint16                               CddStp88XX_nAhlPosDevOld;                                  // for Hor stepper only
#endif

STATIC_AL sint32                               CddStp88XX_alActPosMem[CFA_CNT_STP_88XX];  // actual position in state Move, Ref1, Ref2 to avoid hanging in case of hanging CddStp8899_HalStp state machine in StateStep because of DMA or timer INT mismatch
STATIC_AL uint8                                CddStp88XX_aucActPosMemCnt[CFA_CNT_STP_88XX];  // count of no change of actual position in state Move, Ref1, Ref2 to avoid hanging in case of hanging CddStp8899_HalStp state machine in StateStep because of DMA or timer INT mismatch

uint16                                           CddStp88XX_aunTgtTmin[CFA_CNT_STP_88XX];  // target value for Vmax (halfstep duration in microseconds)

tCddStp88XXBitsMod                               CddStp88XX_aBitsMod[CFA_CNT_STP_88XX];
boolean                                          CddStp88XX_boIgnoreOLDetection = FALSE; // LDM specific, ignore OL in case of UV shutdown so recovery can be made
tCddStp88XXBits                                  CddStp88XX_aBits[CFA_CNT_STP_88XX];
uCddStp88XXBitsGlobalInitOnce                    CddStp88XX_BitsGlobalInitOnce;

tActCtrl                                         CddStp88XX_aStpCtrl                  [CFA_CNT_STP_88XX];
STATIC_AL tActCtrl                               CddStp88XX_aStpCtrlOld               [CFA_CNT_STP_88XX];
tStpState                                        CddStp88XX_aStpState                 [CFA_CNT_STP_88XX];
//static tStpState                               CddStp88XX_aStpStateOld              [CFA_CNT_STP_88XX];
STATIC_AL uint16                                 CddStp88XX_unIsReadyDelayCnt         [CFA_CNT_STP_88XX];
tStpPos                                          CddStp88XX_aStpPos                   [CFA_CNT_STP_88XX];
tCddStpEvent                                     CddStp88XX_aEventBits                [CFA_CNT_STP_88XX];
STATIC_AL tPsensInf                              CddStp88XX_aPsensInf                 [CFA_CNT_STP_88XX];
STATIC_AL  sint32                                CddStp88XX_alDeviation               [CFA_CNT_STP_88XX];
sint32                                           CddStp88XX_alLastDeviation           [CFA_CNT_STP_88XX];
/*static*/ sint16                                CddStp88XX_anRef1Pos                 [CFA_CNT_STP_88XX];
STATIC_AL uint8                                  CddStp88XX_ucAhlErrPsensCnt;                               // for Hor stepper only

uint8                                            CddStp88XX_aucOLCntMax               [CFA_CNT_STP_88XX];
STATIC_AL tFTimer                                CddStp88XX_aftWaitStabilize          [CFA_CNT_STP_88XX];
STATIC_AL tFTimer                                CddStp88XX_aftWaitVoltage            [CFA_CNT_STP_88XX];

STATIC_AL boolean                                CddStp88XX_boUVShtDwn = FALSE; // LDM specific, flag used to indicate under voltage shutdown

//static tFTimer                                 CddStp88XX_aftWaitErrInh             [CFA_CNT_STP_88XX];

STATIC_AL uint8                                  CddStp88XX_aucErrVoltHiLimitSCCnt[CFA_CNT_STP_88XX]; // check to detect case of no pseudo SC error (ErrElecSC)  -  if > 'CDDSTP88XX_ErrVoltHiLimitSCCntMax' than pseudo SC error

tStateCddStp88XX                                 CddStp88XX_aeState[CFA_CNT_STP_88XX] = { CddStp88XX_eMaxStates , CddStp88XX_eMaxStates, CddStp88XX_eMaxStates, CddStp88XX_eMaxStates};

uint8                                            CddStp88XX_ucNumOfSteppers_EFT = 0;
uint8                                            CddStp88XX_ucNumOfSteppers_Coding = 0;

// actual state of all steppers               pos speed   Support    Init  IsReady IsMoving RefActive IsRef LowTemp TempMode IsFatalError boVoltNorm
/*static*/ tsRte_CddStpActual CddStp_ActAll = { { 0,  0u, { SUPPORT_NO, FALSE, FALSE, FALSE,   FALSE,    FALSE, FALSE,     0,     FALSE,       FALSE } } }; // LWR
boolean                                          CddStp88xx__LwrSleepAndDisable = TRUE; // HW-Pins of 'Sleep' and 'Disable' are 'active'

#if((CFA_CNT_STP_ONBRD == 2) && (CFA_CNT_STPVER0_ONBRD != 2))
#else
uint8                                       CddStp8899_ucDummy;                                       // suppress LINT warnings
#endif


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// (De)Init and Main functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//-----------------------------------------------------------------------------
/// \brief  Stepper initialization
///
/// \param  uint8 ucIx
///
/// \return none
//-----------------------------------------------------------------------------
STATIC_AL void CddStp88XX_Init_(uint8 ucIx)
{
 CddStp_UnitTest_Printf("\n                      *#*#*#*#*#*#*#* JK - CddStp88XX_Init_ *#*#*#*#*#*#*#*\n"); // #include <stdio.h>

//A  uint32  ulCnt_;
//A  sint8   cTmp1;       // for temporary storage of buffer values
//A  sint8   cTmp0 = 0;   // initialize for first loop
//A  sint32  lMax  = 0;   //
//A  sint32  lAbs  = 0;   // for calculation of maximum absolute value

  // jk-tbd STP_RUNTIME_INTDIS_START(CddStp88XX_Init_)

 CDDSTP88XX_OptimizeArrayIndex(ucIx)

#if(CFA_CNT_STP_ONBRD == 2)
  (void)IoHwAb_User_SetDio_EN_VPS(1); // switch on VPS
#endif

// jk-obsolet CddStpPsens_InitSingle(ucIx);       // init module CddStpPsens to actualize message Psens (Sref)

// shift ErrPos statistic results of last power-on cycles, actual values have to be placed to entry 0
//A  for(ulCnt_ = 0; ulCnt_ <= 7; ulCnt_++)
 {
  //A    sint32 lAbsTmp;
  //A    sint32 lMaxTmp;

  //A    cTmp1 = Nvm_RamCopy.ErrPosStatisticStp.cDeviation[ucIx][ulCnt_];
  //A    Nvm_RamCopy.ErrPosStatisticStp.cDeviation[ucIx][ulCnt_] = cTmp0;
  //A    cTmp0 = cTmp1;

  //A    lMaxTmp = cTmp0;
  //A    lAbsTmp = UTIL_ABS(lMaxTmp);

  //A    if (lAbsTmp > lAbs)
  {
   //A      lMax = lMaxTmp;
   //A      lAbs = lAbsTmp;
  }
 }

 CddStp88XX_alDeviation[ucIx] = 0;
 if (CddStp88XX_aBitsMod[0].Bit.biHalStpInit == 0u)    // init HalStp (all on board stepper drivers) only once -> only use first instance of array ucIx = 0 (not compatible to Afs2)!
 {
  CddStp88XX_HalStp_Init();                          // init HalStp
 }
 CddStp88XX_aBitsMod[ucIx].ulRaw = 0;                 // clear module internal used bits
 CddStp88XX_aBitsMod[0].Bit.biHalStpInit = 1u;         // init HalStp (all on board stepper drivers) only once -> only use first instance of array ucIx = 0 (not compatible to Afs2)!

 // last table entry is the maximum value of all entries since ECU production
//A  Nvm_RamCopy.ErrPosStatisticStp.cDeviation[ucIx][7] = (sint8) lMax;
//A  CddStp88XX_aBitsMod[ucIx].Bit.biUpdStat = 1u;

//! CddStp88XX_aBits[ucIx].unRaw = 0;                  // do not clear external used bits
 CddStp88XX_aBits[ucIx].Bit.biTestStepDone = 0;
 CddStp88XX_aBits[ucIx].Bit.biRetryTestStepDone = 0u;
 //! CddStp88XX_aBits[ucIx].Bit.biInvPsensPol = 0;      // polarity changed by _InvertPsensPolarity()
 //A  if (CddStp88XX_GetAttr(ucIx)->biUsePsens == 1u)    // Sref
 {
  //A (void)ReceiveMessage(CddStp88XX_AMsgId[ucIx].Psens, &CddStp88XX_aPsensInf[ucIx]);         // Psens state and position - initial Psens state is LIT_SigWarn, see first event function CddStp88XX_Psens()

  //S CddStp88XX_aStpState[ucIx].Bit.IsInside = CddStp88XX_aPsensInf[ucIx].Bit.biIsPositive;    //                          - initial value is 0, but ignored,    see first event function CddStp88XX_Psens()
  //S CddStp88XX_aBitsMod[ucIx].Bit.biIsRegSlope = CddStp88XX_aPsensInf[ucIx].Bit.biIsRegSlope; //                          - initial value is 0, but ignored,    see first event function CddStp88XX_Psens()
 }

 CddStp88XX_aunTgtTmin[ucIx] = 0;          // set by CddStp88XX_SetTgtVal()

 CddStp88XX_HalStpFct[ucIx].pSetActPos(0); // reset value

 CddStp88XX_aStpCtrl[ucIx].Bit.nPos = 0;   // reset only position value
 CddStp88XX_aStpCtrl[ucIx].Bit.Stop = 1u;   // stop

 CddStp88XX_ucStateVolt = CDDSTP88XX_StateVoltOff;

 (void)CddStp88XX_HalStpFct[ucIx].pInit(TRUE); // init HalStp instance                                        // see case ActExit in CddStp88XX_StateFct_Init() - because of dynamical use of InitState (not compatible to Afs2)

 (void)IoHwAb_User_GetAdc_DIAG_VBAT(&CddStp88XX_unDIAG_VBAT);
 CddStp88XX_aStpState[ucIx].Bit.Reduced = CddStpDyn_SetFreq(ucIx, CddStp88XX_aunTgtTmin[ucIx], CddStp88XX_unDIAG_VBAT);     // needed to init CddStpDyn!

//CddStp88XX_aeTempOldState[ucIx] = CddStp88XX_eMaxStatesTemp;             // force tracking in case of first state

  // jk-tbd STP_RUNTIME_INTDIS_STOP(CddStp88XX_Init_)
}


//-----------------------------------------------------------------------------
/// \brief  Stepper EFT, coding data an mounting side left/right handling
///         Check valid EFT and valid Coding data and mounting side left/right is defined
///               and set var 'CddStp_ActAll.sLwrActual.sStatusError.eStatSupported' to '(tieSupportInfo)SUPPORT_YES' or '(tieSupportInfo)SUPPORT_NO'
///         Do this cheking only until valid data (EFT & Cod) is available
///
/// \param  -
///
/// \return none
//-----------------------------------------------------------------------------
void CddStp88XX_EftCodingLr(void)
{
 STATIC_UT(boolean, CddStp8899_boEftCodValid, FALSE); // flag to check only once

 if (CddStp8899_boEftCodValid == FALSE) // already checked?
 {
  boolean boEftDataStatus = FALSE;
  tsRteCodingParameters sCodingParameters;
  teRte_IdentityConfig eIdentity = Appl_GetIdentity();

#ifndef UNIT_TEST
  boEftDataStatus = EFT_DATA_VALID_STATUS;
#else
  boEftDataStatus = CddEft_DataValid();
#endif
  
  (void)Rte_Read_CodM_CddStp_Para(&sCodingParameters);

  if ((boEftDataStatus                != FALSE)
   && (sCodingParameters.eCodingState != eParaFct0_CodingDataInvalid)
   && (eIdentity                      != eIdentityUndef))
  {
   CddStp8899_boEftCodValid = TRUE; // flag to check only once
   CddStp88XX_EftCodingLr_2();
  }

  // EFT or Cod or Id is still not valid
  else
  {
   CddStp_ActAll.sLwrActual.sStatusError.eStatSupported = (tieSupportInfo)SUPPORT_UNKNOWN;
  }
 }

 // already checked!
 else
 {
  // do NOT set this HERE again (should be already set): 'CddStp_ActAll.sLwrActual.sStatusError.eStatSupported = (tieSupportInfo)SUPPORT_UNKNOWN;'
 }
}


//-----------------------------------------------------------------------------
/// \brief  Stepper EFT, coding data an mounting side left/right handling
///         Check valid EFT and valid Coding data and mounting side left/right is defined
///               and set var 'CddStp_ActAll.sLwrActual.sStatusError.eStatSupported' to '(tieSupportInfo)SUPPORT_YES' or '(tieSupportInfo)SUPPORT_NO'
///         Do this cheking only until valid data (EFT & Cod) is available
///
/// \param  -
///
/// \return none
//-----------------------------------------------------------------------------
STATIC_AL void CddStp88XX_EftCodingLr_2(void)
{
 //tieEftDataPtr pEftData = NULL_PTR;
 boolean boLwrEnable = FALSE;
 uint8 ucNumOfSteppers_EFT = 0;

 // read RTE-Port ppCodMEftData0 to get the availablity of the stepper
 // old: CodM_ppCodMEftData0_GetData(&pEftData); // EFT-Mapping: \ECU_FLM3\04_SW\01_DOCU\01_SYRD\SYRS_Asr6-Bw16_EFTParameters.xlsm
 //(void)Rte_Call_ppCodMEftData0_GetData(&pEftData); // new

 // tbd:
 // if (pEftData != NULL_PTR) ... !!!

 // check Coding-Data
 (void)CddStp_MapParams(); // before use of ANY Cod_XXX()
 boLwrEnable = Cod_LwrEnableStp();
 // check EFT-Data
 ucNumOfSteppers_EFT = 1;
 //if (pEftData->EFT_ECUVARCFG_STEPPER[0] >= 1u) // 01 = DRV8899
 //{
 //  ucNumOfSteppers_EFT++;
 //}
 //if (pEftData->EFT_ECUVARCFG_STEPPER[2] >= 1u) // 01 = DRV8899
 //{
 //  ucNumOfSteppers_EFT++;
 //}
 //if (pEftData->EFT_ECUVARCFG_STEPPER[4] >= 1u) // 01 = DRV8899
 //{
 //  ucNumOfSteppers_EFT++;
 //}
 CddStp88XX_ucNumOfSteppers_EFT = 1;// ucNumOfSteppers_EFT;
#ifdef UNIT_TEST
 CddStp_UnitTest_Printf("                      *#*#*#*#*#*#*#* JK - in fct 'CddStp88XX_EftCodingLr_2':  'pEftData->EFT_ECUVARCFG_STEPPER[0]'=%d, 'boLwrEnable'=%d) *#*#*#*#*#*#*#*\n", pEftData->EFT_ECUVARCFG_STEPPER[0], boLwrEnable);
 #endif
 if (//((pEftData->EFT_ECUVARCFG_STEPPER[0] >= 1u) && // 01 = DRV8899
  (boLwrEnable != FALSE) &&                   // LWR enable
  (CddStp88XX_ucNumOfSteppers_EFT >= 1u))
 {
#ifdef UNIT_TEST
  CddStp_UnitTest_Printf("                      *#*#*#*#*#*#*#* JK - in fct 'CddStp88XX_EftCodingLr_2':  Do ini NOW");
#endif
  sint32  lSchrittMod = (sint32)Cod_LwrSchrittMod();

  CddStp88XX_ucNumOfSteppers_Coding = 1;

  //void CddStp88XX_ParaFct0(const uint32 ulCmd                     , const uint8 ucIx, tisParaData0* pData);
  CddStp88XX_ParaFct0((tiulParaCmd)eParaFct0_CodingDataValid, 0, NULL); //jk-tbd-CD !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  // only LWR (ucIx = 0):
  (void)CddStp88XX_HalStpFct[0].pSetHsMode((lSchrittMod == (sint32)NvmPara_eSchrittMod2) ? TRUE : FALSE,                  // see case ActExit in CddStp88XX_StateFct_Init() - because of dynamical use of InitState (not compatible to Afs2)
   CddStp88XX_aucCurAmpltRunTemp[0][CddStp88XX_aeTemp[0]]);  // ... (not compatible to Afs2)

  CddStpDyn_Init(0, ((lSchrittMod == (sint32)NvmPara_eSchrittMod2) ? TRUE : FALSE));                                      // ... (not compatible to Afs2)

  CddStp_ActAll.sLwrActual.sStatusError.eStatSupported = (tieSupportInfo)SUPPORT_YES; //  depends on PAV/EFT & Coding and on validity of them
 }

 // CddStp8899_boEftCodValid == TRUE  ->  already checked!
 else
 {
  CddStp88XX_ucNumOfSteppers_Coding = 0;
  CddStp_ActAll.sLwrActual.sStatusError.eStatSupported = (tieSupportInfo)SUPPORT_NO;
 }
}


//-----------------------------------------------------------------------------
/// \brief  Stepper initialization
///         Currently NOT useful because it is called ONLY AFTER several calls of 'rpCddStp_Cycle0'
///
/// \param  uint8 ucIx
///
/// \return none
//-----------------------------------------------------------------------------
void CddStp88XX_Init(uint8 ucIx)
{
 CddStp_UnitTest_Printf("\n                      *#*#*#*#*#*#*#* JK - CddStp88XX_Init *#*#*#*#*#*#*#*\n"); // #include <stdio.h>

 CddStp88XX_Init_(ucIx);
 CddStp88XX_StateMachine(ucIx, CddStp88XX_eCmdInit);

 // jk-NOT here:  // jk-tbd jk-tbd jk-tbd jk-tbd jk-tbd jk-tbd 
 // jk-NOT here:  CddStpDyn_CodingDataValid(); // called in fct 'roCddStp_ParaFct0'/'CddStp88XX_ParaFct0' (explicit temporarily called in fct 'CddStp88XX_Init_')
 // jk-NOT here:  // jk-tbd jk-tbd jk-tbd jk-tbd jk-tbd jk-tbd 
}


//-----------------------------------------------------------------------------
/// \brief  Stepper deinitialization (not used in AutoSar)
///
/// \param  uint8 ucIx
///
/// \return none
//-----------------------------------------------------------------------------
STATIC_AL void CddStp88XX_DeInit(uint8 ucIx)
{
 CDDSTP88XX_OptimizeArrayIndex(ucIx)

  CddStp88XX_HalStpFct[ucIx].pResetStp(FALSE); // reset HalStp state machine and motor is disabled
 (void)CddStp88XX_HalStpFct[ucIx].pInit(FALSE);

 CddStp88XX_HalStpFct[ucIx].pSetActPos(0);                                      // reset value

 CddStp88XX_aStpCtrl[ucIx].Bit.nPos = 0;                                        // reset only position value
 CddStp88XX_aStpCtrl[ucIx].Bit.Stop = 1u;                                        // stop

//A  CddStp88XX_DemReportErrorStatus(ucIx, CddStp88XX_eDemEType_OL,     ERRLOG_NoDetecting);
//A  CddStp88XX_DemReportErrorStatus(ucIx, CddStp88XX_eDemEType_SC,     ERRLOG_NoDetecting);
//A  CddStp88XX_DemReportErrorStatus(ucIx, CddStp88XX_eDemEType_TempSD, ERRLOG_NoDetecting);
//A  CddStp88XX_DemReportErrorStatus(ucIx, CddStp88XX_eDemEType_Pos,    ERRLOG_NoDetecting);

 CddStp88XX_aStpState[ucIx].ulData = 0; // clear all bits because of no more new setting values are received by StpCtrl, ...
}


//-----------------------------------------------------------------------------
/// \brief  This function updates CddStp_ActAll by using CddStp88XX_aStpState[]
///
/// \param  uint8 ucIx
///
/// \return -
//----------------------------------------------------------------------------
void CddStp88XX_GetState(uint8 ucIx)
{
 CDDSTP88XX_OptimizeArrayIndex(ucIx)

  // check valid EFT-Data and valid Coding-Data and set var 'CddStp_ActAll.sLwrActual.sStatusError.eStatSupported' to '(tieSupportInfo)SUPPORT_YES' or '(tieSupportInfo)SUPPORT_NO'
  // do this cheking only until valid data (EFT & Cod) is available
  CddStp88XX_EftCodingLr();

 // send current position only if driver is turned on
 if (CddStp88XX_aStpCtrl[ucIx].Bit.On != 0u)
 {
   CddStp_ActAll.sLwrActual.nPosition = CddStp88XX_aStpPos[ucIx].nPos;
 }
 else
 {
   // keep previous value
 }
 
 CddStp_ActAll.sLwrActual.sStatusError.boIsOn = CddStp88XX_aStpCtrl[ucIx].Bit.On;
 CddStp_ActAll.sLwrActual.sStatusError.boIsReady   = CddStp88XX_CondStpStateBitIsReady(ucIx);  // = CddStp88XX_aStpState[ucIx].Bit.IsReady + DELAY
 CddStp_ActAll.sLwrActual.sStatusError.boIsMoving = CddStp88XX_aStpState[ucIx].Bit.IsMoving;
 CddStp_ActAll.sLwrActual.sStatusError.boRefActive = CddStp88XX_aStpState[ucIx].Bit.RefActive;
 CddStp_ActAll.sLwrActual.sStatusError.boIsRef = CddStp88XX_aStpState[ucIx].Bit.IsRef;

  // new
  CddStp_ActAll.sLwrActual.sStatusError.boInitActive     =  CddStp88XX_aStpState[ucIx].Bit.InitActive;
  CddStp_ActAll.sLwrActual.sStatusError.boIsFatalError   = ((CddStp88XX_aeState[ucIx] == CddStp88XX_eStateErr) || (CddStp88XX_aStpState[ucIx].Bit.ErrDrvDefect == 1u)) ? TRUE : FALSE;
  CddStp_ActAll.sLwrActual.sStatusError.boLowTemp        =  CddStp88XX_aBits[ucIx].Bit.biLT;
  CddStp_ActAll.sLwrActual.sStatusError.eTempMode        =  (tieStpTempMode)CddStp88XX_aeTemp[ucIx];
  CddStp_ActAll.sLwrActual.sStatusError.boStepLoss       = (CddStp88XX_aStpState[ucIx].Bit.StepLoss  !=    0u) ? TRUE : FALSE;
  CddStp_ActAll.sLwrActual.sStatusError.boCommDefect     = (CddStp88XX_aStpState[ucIx].Bit.SpiValid  ==    0u) ? TRUE : FALSE;
  CddStp_ActAll.sLwrActual.sStatusError.boElecOL         = (CddStp88XX_aStpState[ucIx].Bit.ErrElecOL != FALSE) ? TRUE : FALSE;
  CddStp_ActAll.sLwrActual.sStatusError.boElecSC         = (CddStp88XX_aStpState[ucIx].Bit.ErrElecSC != FALSE) ? TRUE : FALSE;
  CddStp_ActAll.sLwrActual.sStatusError.boVoltUSSM       = (CddStp88XX_aStpState[ucIx].Bit.VoltUSSM  !=    0u) ? TRUE : FALSE;
  CddStp_ActAll.sLwrActual.sStatusError.boVoltUVShtDwn   = (CddStp88XX_boUVShtDwn                    != FALSE) ? TRUE : FALSE;
  CddStp_ActAll.sLwrActual.sStatusError.boVoltOver       = (CddStp88XX_aStpState[ucIx].Bit.VoltOver  !=    0u) ? TRUE : FALSE;
  CddStp_ActAll.sLwrActual.sStatusError.boOverTempShtDwn = (CddStp88XX_aStpState[ucIx].Bit.ErrTherm  != FALSE) ? TRUE : FALSE;

#ifdef CDDSTP_CFG_SIMULATION // defined in '.\Asr6\Src\Src_AL\Cust\Bw\Bw16\App\Bsw\Cdd\CddStp\CddStpPrj.h'
 // simulation
 if (CddStp_Simulation_IsSimActive() != FALSE)
 {
  CddStp_ActAll.sLwrActual.sStatusError.boIsFatalError = CddStp_ActAll.sLwrActual.sStatusError.boIsFatalError != FALSE ? TRUE : CddStp_Simulation_HandleDriverDefect_FatalError();
 }
#endif // CDDSTP_CFG_SIMULATION
}


//-----------------------------------------------------------------------------
/// \brief  This function is called cyclic every 10ms
///
/// \param  uint8 ucIx
///
/// \return -
//----------------------------------------------------------------------------
void CddStp88XX_Cycle0(uint8 ucIx)
{
 // jk-tbd STP_RUNTIME_INTDIS_START(CddStp88XX_Cyc)

 //  CDDSTP88XX_OptimizeArrayIndex(ucIx)

 IoHwAb_SystemTick_1Ms += 10u; // jk-tbd!!!

  // Workaround of TI-Chip: Need minimum time between Off-On
  if (CddStp88XX_unIsReadyDelayCnt[ucIx] > 0u)
  {
    CddStp88XX_unIsReadyDelayCnt[ucIx]--; // wait at least 5 x 10ms-Cyclic between OFF & ON
  }
 if (ucIx == 0u)                      // LWR stepper driver?
 {
  // call stepper driver volt state machine
  CddStp88XXVolt_StpVoltCycle();   // handles all steppers - therefore it has to be called only once
 }

 CddStp88XX_Event(ucIx, CDDSTP_eAlternativeTrigger);//TTTESTTT //AL51 //workaround //tbd

 // write NVM if statistics changed
//A  if (CddStp88XX_aBitsMod[ucIx].Bit.biUpdStat)
 {
  //A    if (NVM_WRITE_RAMCOPY(ErrPosStatisticStp, None))
  {
   // NVM-write was successful.
//A      CddStp88XX_aBitsMod[ucIx].Bit.biUpdStat = 0;
  }
 }

 // handle flag which indicates valid actual position
 if ((CddStp88XX_aStpState[ucIx].Group.ucErrLock == 0u)
  && (CddStp88XX_aStpState[ucIx].Bit.VoltNorm == 1u)
  && (CddStp88XX_aStpState[ucIx].Bit.IsRef == 1u))
 {
  CddStp88XX_aBits[ucIx].Bit.biActPosValid = TRUE;
 }
 else
 {
  CddStp88XX_aBits[ucIx].Bit.biActPosValid = FALSE;
 }
  // jk-tbd STP_RUNTIME_INTDIS_STOP(CddStp88XX_Cyc)
}


//-----------------------------------------------------------------------------
/// \brief  This function is called on signal port data reception
///
/// \param  uint8 ucIx
///
/// \return -
//-----------------------------------------------------------------------------
void CddStp88XX_TgtVal(uint8 ucIx)
{
 CDDSTP88XX_OptimizeArrayIndex(ucIx)

  /////  __DI();            // call from interrupt level is not possible (no counter)!
  /////  osDisableGlobal(); // call from interrupt level is not possible (no counter)!
  //SuspendAllInterrupts();

  //CddStp88XX_aBits[ucIx].Bit.biSigInit = TRUE;  // needed ? //TBD

  CddStp88XX_Ctrl(ucIx); // call state machine

  // handle flag which indicates valid actual position
 if ((CddStp88XX_aStpState[ucIx].Group.ucErrLock == 0u)
  && (CddStp88XX_aStpState[ucIx].Bit.VoltNorm == 1u)
  && (CddStp88XX_aStpState[ucIx].Bit.IsRef == 1u))
 {
  CddStp88XX_aBits[ucIx].Bit.biActPosValid = TRUE;
 }
 else
 {
  CddStp88XX_aBits[ucIx].Bit.biActPosValid = FALSE;
 }

 /////  __EI();           // call from interrupt level is not possible (no counter)!
 /////  osEnableGlobal(); // call from interrupt level is not possible (no counter)!
 //ResumeAllInterrupts();
}


//-----------------------------------------------------------------------------
/// \brief  This function is called on CtrlFct0 operation invocation
///
/// \param  const uint8     ulCmd
///         const uint8     ucIx
///         tisCtrlData0*   pData
///
/// \return none
//-----------------------------------------------------------------------------
void CddStp88XX_CtrlFct0(const uint32 ulCmd, const uint8 ucIx, tisCtrlData0* pData)
{
 tCddStpCtrlFct0_Cmd         eCmd = (tCddStpCtrlFct0_Cmd)ulCmd; // PRQA S 4342 1 // program architecture and readability - intentionally no modification of existing code  - An expression of 'essentially unsigned' type (unsigned long) is being cast to enum type 'tCddStpCtrlFct0_Cmd'.) Depth: 0 Ref: MISRA C:2012 Rule-10.5
 tCddStpCtrlFct0_DataBuffer* pBuffer_ = (tCddStpCtrlFct0_DataBuffer*)(void*)pData; // PRQA S 316 1 // program architecture and readability - intentionally no modification of existing code - [I] Cast from a pointer to void to a pointer to object type.) Depth: 0 Ref: MISRA C:2012 Rule-11.5; REFERENCE - ISO:C90-6.3.4 Cast Operators - Semantics

 switch (eCmd)
 {
 case CddStp_eCtrlFct0_ModeOff:                    // Treiber ausschalten // UWY SS
  if (CddStp88XX_aStpCtrl[ucIx].Bit.On == 1u)     // already switched on driver?
  {
   //Gpt_DisableNotification(GptConf_GptChannelConfiguration_StpTimer0);

   // ok: IoHwAb_SetDo(DioConf_DioChannel_DioChannel_0_1_ST_SLEEP, STD_LOW);   // N.b.: inverse logic!  -  Pin: Stp-NOT-Sleep -> 'Low'=DO-Sleep
   (void)IoHwAbUser_SetLwrSleep(FALSE);  // N.b.: inverse logic!  -  Pin: Stp-NOT-Sleep -> 'Low'=DO-Sleep

   // ok: IoHwAb_SetDo(DioConf_DioChannel_DioChannel_0_2_ST_DRVOFF, STD_HIGH); // UWY - switch off driver  -  Write '1' to Hi-Z all outputs  -  OR'ed with SPI-Ctrl 'DIS_OUT'
   (void)IoHwAbUser_SetLwrDrvOff(TRUE);  // UWY - switch off driver  -  Write '1' to Hi-Z all outputs  -  OR'ed with SPI-Ctrl 'DIS_OUT'

   CddStp88xx__LwrSleepAndDisable = TRUE;

   // new: Due to OR'ed behaviour of HW-Pin & SW-Bit
   // tbd: CddStp88XX_HalStpLwr_HandleMotEn_(FALSE, FALSE); // boMotEn = FALSE to disable driver (handle difference, because function is called several times!), boSendCReg12 = FALSE
   /*jk-new*/ CddStp88XX_aBitsMod[CFG_Stp_IdxVer].Bit.biDisOLDetect = 1u; // Disable OL-Detection (CReg4-EN_OL) for next re-start (no Pseudo-Errors) (inverse logic: EnOl <-> DisOl)
   /*jk-new*/ (void)CddStp88XX_HalStpFct[ucIx].pHandleMotEn(FALSE, TRUE); // boMotEn = FALSE to disable driver (CReg2-DIS_OUT) (handle difference, because function is called several times!), boSendCReg12 = TRUE

   CddStp88XX_aStpCtrl[ucIx].Bit.Stop = 0;
   CddStp88XX_aStpCtrl[ucIx].Bit.Corr = 0;
   CddStp88XX_aStpCtrl[ucIx].Bit.Ref = 0;
   CddStp88XX_aStpCtrl[ucIx].Bit.On = 0;             // switch off driver
   CddStpPrj_SetEventFinishMove(ucIx);

   CddStp88XX_aStpState[ucIx].Bit.IsReady = 0;
  }
  break;

 case CddStp_eCtrlFct0_ModeOn:                     // Treiber einschalten // UWY SS
  if (CddStp88XX_aStpCtrl[ucIx].Bit.On == 0u)     // already switched on driver?
  {
   //Gpt_EnableNotification(GptConf_GptChannelConfiguration_StpTimer0);

   // ok: //IoHwAb_SetDo(110, STD_HIGH); // Pin: Stp-NOT-Sleep -> 'High'=NO-Sleep - 110=DioConf_DioChannel_DioChannel_13_6_ST_SLEEP (#define DioConf_DioChannel_DioChannel_HSS_1 88U)
   // ok: IoHwAb_SetDo(DioConf_DioChannel_DioChannel_0_1_ST_SLEEP, STD_HIGH); // N.b.: inverse logic!  -  Pin: Stp-NOT-Sleep -> 'High'=NO-Sleep
   (void)IoHwAbUser_SetLwrSleep(TRUE);  // N.b.: inverse logic!  -  Pin: Stp-NOT-Sleep -> 'High'=NO-Sleep

   // ok: IoHwAb_SetDo(DioConf_DioChannel_DioChannel_0_2_ST_DRVOFF, STD_LOW); // UWY - now switch on driver to avoid high current before reference run!!!   -  Write '1' to Hi-Z all outputs  -  OR'ed with SPI-Ctrl 'DIS_OUT'
   (void)IoHwAbUser_SetLwrDrvOff(FALSE);  // UWY - now switch on driver to avoid high current before reference run!!!   -  Write '1' to Hi-Z all outputs  -  OR'ed with SPI-Ctrl 'DIS_OUT'
   CddStp88xx__LwrSleepAndDisable = FALSE;

   CddStp88XX_aStpCtrl[ucIx].Bit.Stop = 0;
   CddStp88XX_aStpCtrl[ucIx].Bit.Corr = 0;
   CddStp88XX_aStpCtrl[ucIx].Bit.Ref = 0;
   CddStp88XX_aStpCtrl[ucIx].Bit.On = 1u;           // switch on driver
   CddStpPrj_SetEventFinishMove(ucIx);

   CddStp88XX_aStpState[ucIx].Bit.IsReady = 0;
  }
  break;

 case CddStp_eCtrlFct0_ModeRel:            // Verstellmodus bezogen auf Anfangsposition (!only used in case of failed reference run!) // UWY SS - obsolete
  CddStp88XX_aStpCtrl[ucIx].Bit.Corr = 0;

  CddStp88XX_aStpState[ucIx].Bit.IsRef = 0;         // only used in case of failed reference run!
  CddStp88XX_aStpState[ucIx].Bit.FullRef = 0;         // only used in case of failed reference run!

  CddStp88XX_HalStpFct[ucIx].pSetActPos(0);           // reset value for use of complete range

  CddStp88XX_aStpCtrl[ucIx].Bit.Stop = 0;
  CddStp88XX_aStpCtrl[ucIx].Bit.Ref = 0;
  CddStpPrj_SetEventFinishMove(ucIx);

  CddStp88XX_aStpState[ucIx].Bit.IsReady = 0;         // OSEK timing

  // Aktualisierung ActPos noetig ?
  break;

 case CddStp_eCtrlFct0_ModeAbs:            // Verstellmodus bezogen auf Referenzierposition // UWY SS - standard
  CddStp88XX_aStpCtrl[ucIx].Bit.Corr = 1u;
  CddStp88XX_HalStpFct[ucIx].pIncActPos(CddStp88XX_alDeviation[ucIx]);  // correct actual position of HalStp
  CddStp88XX_alDeviation[ucIx] = 0;                                      // to allow multipe use after reference run without change of actual position

  CddStp88XX_aStpCtrl[ucIx].Bit.Stop = 0;
  CddStp88XX_aStpCtrl[ucIx].Bit.Ref = 0;
  CddStpPrj_SetEventFinishMove(ucIx);

  CddStp88XX_aStpState[ucIx].Bit.IsReady = 0;         // OSEK timing

  // Aktualisierung ActPos noetig ?
  break;

 case CddStp_eCtrlFct0_ModeStop:           // Motor mit Bremsrampe stoppen / starten // UWY SS boStop
  if (CddStp88XX_aStpState[ucIx].Bit.RefActive == 0u)  // FLM3
  {
   CddStp88XX_aStpCtrl[ucIx].Bit.Stop = (pBuffer_->SoftStop.boSoftStop == 1u) ? 1u : 0u;
   //CddStp88XX_aStpCtrl[ucIx].Bit.Ref  = 0;           // FLM3
  }
  CddStpPrj_SetEventFinishMove(ucIx);

  //    CddStp88XX_aStpState[ucIx].Bit.IsReady = 0;
  break;

 case CddStp_eCtrlFct0_ModeRef:            // Referenzieranforderung // UWY SS roCddStpStartRefRun()
  CddStp88XX_aStpCtrl[ucIx].Bit.Stop = 0;
  CddStp88XX_aStpCtrl[ucIx].Bit.Corr = 0;
  CddStp88XX_aStpCtrl[ucIx].Bit.Ref = 1u;
  CddStp88XX_aStpCtrlOld[ucIx].Bit.Ref = 0;          // to support possibility of slope detection again
  CddStpPrj_SetEventFinishMove(ucIx);

  CddStp88XX_aStpState[ucIx].Bit.IsReady = 0;

  CddStp88XX_aunRefStartCnt[ucIx]++;
  break;

 case CddStp_eCtrlFct0_ErrInhibit:         // Unterdrueckung der Fehlererkennung (ErrElecOL/SC and step loss) // UWY SS ???
  CddStp88XX_aStpCtrl[ucIx].Bit.ErrInh = pBuffer_->ErrInhibit.boErrInhibit;
  CddStpPrj_SetEventFinishMove(ucIx);

  break;

 case CddStp_eCtrlFct0_ErrActivate:        // Reaktivierung der Fehlererkennung // UWY SS ???
  break;

 case CddStp_eCtrlFct0_ErrClr:             // unlock error state // UWY SS ???
  CddStp88XX_aStpCtrl[ucIx].Bit.ErrClr = 1u;
  CddStpPrj_SetEventFinishMove(ucIx);
  break;

 case CddStp_eCtrlFct0_LowTemp:            // low temperature // UWY SS ???
  CddStp88XX_aBits[ucIx].Bit.biLT = pBuffer_->LowTemp.boLT;               // not cleared at call of CddStp88XX_Init_() (not compatible to Afs2)
  // bit CddStp88XX_aBitsMod[ucIx].Bit.biLockLT is cleared in CddStp88XX_StateFct_Init() at call of CddStp88XX_Init_() (not compatible to Afs2)
  break;

 case CddStp_eCtrlFct0_GetTempState:       // get temperature state // UWY SS ???
  pBuffer_->GetTempState.eTemp = CddStp88XX_aeTemp[ucIx];
  break;

 case CddStp_eCtrlFct0_SetCARunRef:        // set run current of next 12 HS to reference current for bump reference run // UWY SS ???
#if((CFA_CNT_STP_ONBRD == 2) && (CFA_CNT_STPVER0_ONBRD != 2))
// 2nd on-board stepper as horizontal (not as workaround for 2nd on-board stepper as vertical)
  if (ucIx == CFG_Stp_IdxHor)                          // for Hor stepper only
  {
   CddStp88XX_HalStpFct[ucIx].pHandleCurAmplt(CDDSTP88XX_eCurAmpltStateNoChange, CddStp88XX_aucCurAmpltHoldTemp[ucIx][CddStp88XX_aeTemp[ucIx]], CddStp88XX_aucCurAmpltRefTemp[ucIx][CddStp88XX_aeTemp[ucIx]]); // increase normal current to reference amplitude
   CddStp88XX_HalStpFct[ucIx].pSetCARunRefCnt(12);   // for Hor stepper only
  }
#endif
  break;

  case CddStp_eCtrlFct0_SetIsReady:         // set CddStpState IsReady bit
    CddStp88XX_SetStpStateBitIsReady(ucIx); //  CddStp88XX_aStpState[ucIx].Bit.IsReady = 1u;
    break;

 default:
  break;
 }
 // PRQA S 5316, 5330 1 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio2) Msg: 5316(HIS metrics violation: 'CddStp88XX_CtrlFct0() : STCYC = 17' exceeds threshold 10 for Cyclomatic complexity (STCYC).) Depth: 0 Ref:  | warning - QAC(Prio2) Msg: 5330(HIS metrics violation: 'CddStp88XX_CtrlFct0() : STST3 = 67' exceeds threshold 50 for Number of statements in function (STST3).) Depth: 0 Ref: 
}


//-----------------------------------------------------------------------------
/// \brief  This function is called on ParaFct0 operation invocation
///
/// \param  const uint8         ulCmd
///         const uint8         ucIx
///         tisParaData0*       pData
///
/// \return none
//-----------------------------------------------------------------------------
void CddStp88XX_ParaFct0(const uint32 ulCmd, const uint8 ucIx, tisParaData0* pData)
{
 uint8         ucInst;
 tParaFct0_Cmd eCmd = (tParaFct0_Cmd)ulCmd; // PRQA S 4342 1 // program architecture and readability - intentionally no modification of existing code  - An expression of 'essentially unsigned' type (unsigned long) is being cast to enum type 'tCddStpCtrlFct0_Cmd'.) Depth: 0 Ref: MISRA C:2012 Rule-10.5

 (void)ucIx;
 (void)pData;  // suppress LINT Info 818: Pointer parameter 'pData' (line 700) could be declared as pointing to const
               // Remark: Parameter is used

 switch (eCmd)
 {
 case eParaFct0_CodingDataInvalid:
 {
  CddStp88XX_BitsGlobalInitOnce.Bit.biCodingDataValid = 0;                                                                 // (not compatible to Afs2)
  break;
 }

 case eParaFct0_CodingDataValid:
 {
  CddStp88XX_BitsGlobalInitOnce.Bit.biCodingDataValid = 1u;                                                                 // (not compatible to Afs2)
  break;
 }

 default:
  break;
 }
 CddStpDyn_CodingDataValid();

 // add offset to get max. count of sequenced set of DRV88XX OL error bit - CDDSTP88XX_HALSTP_OLCntMaxMS | CDDSTP88XX_HALSTP_OLCntMaxHS (not compatible to Afs2)
 CddStp88XX_aucOLCntMax[CFG_Stp_IdxVer] = (uint8)(Cod_LwrOlFehlerzaehler() + (uint8)1);
#if(CFA_CNT_STP_ONBRD == 2)
 CddStp88XX_aucOLCntMax[CFG_Stp_IdxHor] = (uint8)(Cod_AhlOlFehlerzaehler() + (uint8)1);
#endif
#if(CFA_CNT_STP_88XX == 3)
 CddStp88XX_aucOLCntMax[CFG_Stp_IdxSht] = (uint8)(Cod_GlwOlFehlerzaehler() + (uint8)1);
#endif

 for (ucInst = 0u; ucInst < CFA_CNT_STP_88XX; ucInst++)
 {
  CddStp88XX_SetCurrent(ucInst); // calculate currents for NT, LT and HT from NVM RAM values and send by SPI to stepper driver
 }
#ifdef CFG_Prj_Bw07 // FLE & FLE2
 if (V_ACTIVE_IDENTITY_LOG == kVIdentityEcuMConfiguration_FLE_L) //tbd
#else // Bw10 = FLM (=HCM)
 if (Appl_GetIdentity() == ePluggedLeft)
#endif      
 {
  CddStp88XX_aBits[CFG_Stp_IdxVer].Bit.biRichtung = Cod_LwrRichtungLi();
  CddStp88XX_aBits[CFG_Stp_IdxVer].Bit.biPsensPol = 0; // not used
  CddStp88XX_aBits[CFG_Stp_IdxVer].Bit.biRegelflanke = 0; // not used
#if(CFA_CNT_STP_ONBRD == 2)
  CddStp88XX_aBits[CFG_Stp_IdxHor].Bit.biRichtung = ~Cod_AhlRichtungLi();     // AL definition (inside direction) is inverse to BMW definition (positive direction)
  CddStp88XX_aBits[CFG_Stp_IdxHor].Bit.biPsensPol = ~Cod_AhlPsensPolLi();     // AL definition (inside direction) is inverse to BMW definition (positive direction)
  CddStp88XX_aBits[CFG_Stp_IdxHor].Bit.biRegelflanke = ~Cod_AhlRegelflankeLi();  // AL definition (inside direction) is inverse to BMW definition (positive direction)
#endif
 }
 else
 {
  CddStp88XX_aBits[CFG_Stp_IdxVer].Bit.biRichtung = Cod_LwrRichtungRe();
  CddStp88XX_aBits[CFG_Stp_IdxVer].Bit.biPsensPol = 0; // not used
  CddStp88XX_aBits[CFG_Stp_IdxVer].Bit.biRegelflanke = 0; // not used
#if(CFA_CNT_STP_ONBRD == 2)
  CddStp88XX_aBits[CFG_Stp_IdxHor].Bit.biRichtung = Cod_AhlRichtungRe();
  CddStp88XX_aBits[CFG_Stp_IdxHor].Bit.biPsensPol = Cod_AhlPsensPolRe();
  CddStp88XX_aBits[CFG_Stp_IdxHor].Bit.biRegelflanke = Cod_AhlRegelflankeRe();
#endif
 }
#if((CFA_CNT_STP_ONBRD == 2) && (CFA_CNT_STPVER0_ONBRD != 2))
 // 2nd on-board stepper as horizontal (not as workaround for 2nd on-board stepper as vertical)
 CddStp88XX_ucAhlPosDevHistOffset = Cod_AhlAbwHistOffset();                       // for Hor stepper only
 CddStp88XX_ucAhlPosDevHistBase = Cod_AhlAbwHistBasis();                        // for Hor stepper only
#endif
//PDH  CddStp88XX_ucAhlPosDevHistFactor = (uint8)(8 / Ahl.Psens.ucAbwHistBasis);   // for Hor stepper only
}


//-----------------------------------------------------------------------------
/// \brief  This function is called on CntFct0 operation invocation
///
/// \param  const uint8        ulCmd
///         const uint8        ucIx
///         const tisCntData0* pData
///
/// \return none
//-----------------------------------------------------------------------------
void CddStp88XX_CntFct0(const uint32 ulCmd, const uint8 ucIx, tisCntData0* pData)
{
 tCddStpCntFct0_Cmd         eCmd = (tCddStpCntFct0_Cmd)ulCmd; // PRQA S 4342 1 // program architecture and readability - intentionally no modification of existing code  - An expression of 'essentially unsigned' type (unsigned long) is being cast to enum type 'tCddStpCtrlFct0_Cmd'.) Depth: 0 Ref: MISRA C:2012 Rule-10.5
 tCddStpCntFct0_DataBuffer* pBuffer_ = (tCddStpCntFct0_DataBuffer*)(void*)pData; // PRQA S 316 1 // program architecture and readability - intentionally no modification of existing code - [I] Cast from a pointer to void to a pointer to object type.) Depth: 0 Ref: MISRA C:2012 Rule-11.5; REFERENCE - ISO:C90-6.3.4 Cast Operators - Semantics

 switch (eCmd)
 {
 case CddStp_eCntCmd_GetHsCnt:            // get half step count
  pBuffer_->GetHsCnt.ulHsCount = CddStp88XX_HalStpFct[ucIx].pGetHsCnt();
  break;

 case CddStp_eCntCmd_GetIrunTime:         // get running (moving) motor time [msec]
  pBuffer_->GetIrunTime.ulTime = CddStp88XX_HalStpFct[ucIx].pGetIrunTime();
  break;

 case CddStp_eCntCmd_GetStpOnTime:        // get stepper on time [msec]
  pBuffer_->GetStpOnTime.ulTime = CddStp88XX_GetStpOnTime(ucIx);
  break;

 case CddStp_eCntCmd_GetRefStartCnt:      // get count of started of reference runs
  pBuffer_->GetRefStartCnt.unRefStartCnt = CddStp88XX_GetRefStartCnt(ucIx);
  break;

 case CddStp_eCntCmd_GetIsRefCnt:         // get count of correct ended reference runs
  pBuffer_->GetIsRefCnt.unIsRefCnt = CddStp88XX_GetIsRefCnt(ucIx);
  break;

 case CddStp_eCntCmd_GetKlPosDevHistCnts: // get position deviation histogram counters
  CddStp88XX_GetAhlPosDevHistCnts(ucIx, pBuffer_->GetKlPosDevHistCnts.aunKlPosDevHistCnts);
  break;

 case CddStp_eCntCmd_GetLastDeviation:    // get Last deviation // only used in Alx1
  pBuffer_->GetLastDeviation.nLastDeviation = (sint16)CddStp88XX_GetLastDeviation(ucIx);
  break;

 default:
  break;
 }
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// additional event functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_Ctrl
///
///  \brief    Event function to handle ucIx stepper control
///
///  \param    uint8 ucIx
///
///  \return   none
///
///  \descr
///
// ---------------------------------------------------------------------------
STATIC_AL void CddStp88XX_Ctrl(uint8 ucIx)
{
 STATIC_UT_NOINIT(tFTimer, CddStp88XX_aftWaitErrInh[CFA_CNT_STP_88XX]);

 // jk-tbd STP_RUNTIME_INTDIS_START(CddStp88XX_Ctrl)

 CDDSTP88XX_OptimizeArrayIndex(ucIx)

  /////  __DI();            // call from interrupt level is not possible (no counter)!
  /////  osDisableGlobal(); // call from interrupt level is not possible (no counter)!
  //SuspendAllInterrupts();

  ApplMainResetStpAlternativeTriggerCnt(ucIx);

 //A  CddStp88XX_aStpCtrlOld[ucIx] = CddStp88XX_aStpCtrl[ucIx];
 //A  (void)ReceiveMessage(CddStp88XX_AMsgId[ucIx].Ctrl, &CddStp88XX_aStpCtrl[ucIx]);

   // enlarge set time of ErrInh bit to save time to clear stepper driver errors by SPI communication (read more times all status registers):
 if (CddStp88XX_aBits[ucIx].Bit.biWaitErrInh == 1u)
 {
  //  keine CddStp88XX_HalStpLwr_SendSRegX()-Funktionen, da sowieso immer alle StatusRegister gelesen werden
  //(void)CddStp88XX_HalStpFct[ucIx].pSpiSendSRegAll();          // read all the status registers to clear the error bit
  /*jk-tbd - Not Needed Any Longer ?!?!*/ // (void)CddStp8899Com_StartRxNotificationSr12367A8A(ucIx);     // synchronize the sending of SPI commands to read all status registers with the reading of the results after all three values are received
  CddStp88XX_aBits[ucIx].Bit.biTransitionErrDone = 0;          // not: check of error bits is done in CddStp88XX_Transition_Err() - used in CddStp88XX_HalStpVer/Hor/Sht_ErrnCb() and in CddStp88XX_Transition_Err()

  if ((FastTimerTimeout(CddStp88XX_aftWaitErrInh[ucIx]) != FALSE))
  {
   CddStp88XX_aBits[ucIx].Bit.biWaitErrInh = 0;
  }
 }
 // check negative slope of ErrInh bit to clear stepper driver errors by SPI communication (read all status registers):
 if ((CddStp88XX_aStpCtrlOld[ucIx].Bit.ErrInh == 1u)          // neg. slope detected
  && (CddStp88XX_aStpCtrl[ucIx].Bit.ErrInh == 0u))
 {
  //  keine CddStp88XX_HalStpLwr_SendSRegX()-Funktionen, da sowieso immer alle StatusRegister gelesen werden
  // (void)CddStp88XX_HalStpFct[ucIx].pSpiSendSRegAll();          // read all the status registers to clear the error bit
  /*jk-tbd - Not Needed Any Longer*/ // (void)CddStp8899Com_StartRxNotificationSr12367A8A(ucIx);     // synchronize the sending of SPI commands to read all status registers with the reading of the results after all three values are received
  CddStp88XX_aBits[ucIx].Bit.biTransitionErrDone = 0;          // not: check of error bits is done in CddStp88XX_Transition_Err() - used in CddStp88XX_HalStpVer/Hor/Sht_ErrnCb() and in CddStp88XX_Transition_Err()

  CddStp88XX_aftWaitErrInh[ucIx] = FastTimerStart(CDDSTP88XX_WaitErrInh_FTimer);
  CddStp88XX_aBits[ucIx].Bit.biWaitErrInh = 1u;
 }

 CddStp88XX_CalcCorrQuota(ucIx); // correct actual position based on Psens slopes

 // check positive slope of ErrClr bit to clear ErrPos stepper state bit:
 if (CddStp88XX_Transition_ErrClr(ucIx, CddStp88XX_eCmdCtrl) != FALSE)
 {
  CddStp88XX_aStpState[ucIx].Bit.ErrPos = 0;
  //A    CddStp88XX_DemReportErrorStatus(ucIx, CddStp88XX_eDemEType_Pos, ERRLOG_NoDetecting);

  //  CddStp88XX_aStpState[ucIx].Bit.ErrPsensSigLo = 0;
  //  CddStp88XX_aStpState[ucIx].Bit.ErrPsensSigHi = 0;
  //  CddStp88XX_aStpState[ucIx].Bit.ErrPsensSupLo = 0;
  //  CddStp88XX_aStpState[ucIx].Bit.ErrPsensSupHi = 0;
  //  CddStp88XX_aStpState[ucIx].Bit.ErrPsens      = 0;
      // jk-obsolet CddStpPsens_InitSingle(ucIx); // reinit module CddStpPsens to actualize message Psens (Sref)

      // jk-obsolet CddStp88XX_aeDesensPsensPosState[ucIx] = CDDSTP88XX_ePosInit; // reset Psens desensibility state machine
 }

 // handle acknowledge to Ctrl
 CddStp88XX_StateMachine(ucIx, CddStp88XX_eCmdCtrl);
 if (CddStp88XX_aBitsMod[ucIx].Bit.biRefWaitExit == 1u)  // special StpCtrl message handling to force state machine from Exit of RefWait (= Entry of Idle) in Move if necessary without acknowledge by StpState bit 'IsReady'
 {
  CddStp88XX_StateMachine(ucIx, CddStp88XX_eCmdCtrl); // transition from StateIdle to StateMove if no Stop bit is set in StpCtrl message
  CddStp88XX_aBitsMod[ucIx].Bit.biRefWaitExit = 0;
 }

 CddStp88XX_aStpCtrlOld[ucIx] = CddStp88XX_aStpCtrl[ucIx];//A

/////  __EI();           // call from interrupt level is not possible (no counter)!
/////  osEnableGlobal(); // call from interrupt level is not possible (no counter)!
//ResumeAllInterrupts();

  // jk-tbd STP_RUNTIME_INTDIS_STOP(CddStp88XX_Ctrl)
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_Event
///
///  \brief    Event function to handle ucIx stepper Event (HalStp: FinishMove)
///
///  \param    uint8 ucIx
///            tEventCmdCddStp eEventCmd event command
///
///  \return   none
///
///  \descr    SetEvent() is called from task level
///
// -------------------------------------------------------------------------
void CddStp88XX_Event(uint8 ucIx, tEventCmdCddStp eEventCmd)
{
 // jk-tbd STP_RUNTIME_INTDIS_START(CddStp88XX_Event)

 CDDSTP88XX_OptimizeArrayIndex(ucIx)

  /////  __DI();            // call from interrupt level is not possible (no counter)!
  /////  osDisableGlobal(); // call from interrupt level is not possible (no counter)!
  //SuspendAllInterrupts();

  if (CddStp88XX_aEventBits[ucIx].unData != 0x0000u)         // CDDSTP_eStandardEvent: is any event bit set?
  {
   // -------------------- first block: check FinishMove (in StateMachine the SPI sending is not done in case of pending sequence)
   if (CddStp88XX_aEventBits[ucIx].Bit.biFinishMove == 1u)
   {
    CddStp88XX_aEventBits[ucIx].Bit.biFinishMove = 0;

    CddStp88XX_Ctrl(ucIx); // use new set position if it is changed
    CddStp88XX_StateMachine(ucIx, CddStp88XX_eCmdEvent); // transition to StateIdle because HalStp INTs are disabled, also if (setpoint != actual position)
//    CddStp88XX_StateMachine(ucIx, CddStp88XX_eCmdEvent); // transition to Move enable HalStp INTs by start if (setpoint != actual position)

//A   CddStp88XX_HalStpFct[ucIx].pGetHsCnt(); // (get) half step count and clear it
   }
   else
   {
    // CTC
   }
  }
  else if (eEventCmd == CDDSTP_eAlternativeTrigger)          // alternative trigger?
  {
   CddStp88XX_StateMachine(ucIx, CddStp88XX_eCmdEvent);   // transition to StateIdle because HalStp INTs are disabled, also if (setpoint != actual position)
  }
  else
  {
   // suppress MISRA warning - QAC(Prio4) Msg: 2004(No concluding 'else' exists in this 'if'-'else'-'if' statement.) Depth: 0 Ref: MISRA-C:2004 Rule 14.10
  }

 /////  __EI();           // call from interrupt level is not possible (no counter)!
 /////  osEnableGlobal(); // call from interrupt level is not possible (no counter)!
 //ResumeAllInterrupts();

   // jk-tbd STP_RUNTIME_INTDIS_STOP(CddStp88XX_Event)
}


// jk-PSens // ---------------------------------------------------------------------------
// jk-PSens ///
// jk-PSens ///  \func     CddStp88XX_Psens
// jk-PSens ///
// jk-PSens ///  \brief    Event function to handle ucIx Psens
// jk-PSens ///
// jk-PSens ///  \param    uint8 ucIx
// jk-PSens ///
// jk-PSens ///  \return   none
// jk-PSens ///
// jk-PSens ///  \descr
// jk-PSens ///
// jk-PSens // ---------------------------------------------------------------------------
// jk-PSens void CddStp88XX_Psens(uint8 ucIx)
// jk-PSens {
// jk-PSens   // jk-tbd STP_RUNTIME_INTDIS_START(CddStp88XX_Psens)
// jk-PSens 
// jk-PSens   CDDSTP88XX_OptimizeArrayIndex(ucIx)
// jk-PSens 
// jk-PSens   CddStp88XX_aPsensInfOld[ucIx] = CddStp88XX_aPsensInf[ucIx];
// jk-PSens //A  (void)ReceiveMessage(CddStp88XX_AMsgId[ucIx].Psens, &CddStp88XX_aPsensInf[ucIx]); // Psens state and position
// jk-PSens 
// jk-PSens   // initial values not available in CddStp88XX_Init()
// jk-PSens   if ((CddStp88XX_aPsensInfOld[ucIx].Bit.StateErrAll.StateErr.biState == LIT_SigWarn) ? TRUE : FALSE)    // first message Psens? //S
// jk-PSens   {
// jk-PSens     CddStp88XX_aStpState[ucIx].Bit.IsInside    =   CddStp88XX_aPsensInf[ucIx].Bit.biIsPositive;             //S
// jk-PSens     CddStp88XX_aBitsMod[ucIx].Bit.biIsRegSlope =   CddStp88XX_aPsensInf[ucIx].Bit.biIsRegSlope;             //S
// jk-PSens   }
// jk-PSens 
// jk-PSens   // copy Psens error bits
// jk-PSens //ErrPsensDiag  CddStp88XX_aStpState[ucIx].Bit.ErrPsensSigLo =   CddStp88XX_aPsensInf[ucIx].Bit.StateErrAll.StateErr.biErrSigLo;
// jk-PSens //ErrPsensDiag  CddStp88XX_aStpState[ucIx].Bit.ErrPsensSigHi =   CddStp88XX_aPsensInf[ucIx].Bit.StateErrAll.StateErr.biErrSigHi;
// jk-PSens //ErrPsensDiag  CddStp88XX_aStpState[ucIx].Bit.ErrPsensSupLo =   CddStp88XX_aPsensInf[ucIx].Bit.StateErrAll.StateErr.biErrSupLo;
// jk-PSens //ErrPsensDiag  CddStp88XX_aStpState[ucIx].Bit.ErrPsensSupHi =   CddStp88XX_aPsensInf[ucIx].Bit.StateErrAll.StateErr.biErrSupHi;
// jk-PSens //ErrPsensDiag  CddStp88XX_aStpState[ucIx].Bit.ErrPsens      = ((CddStp88XX_aPsensInf[ucIx].Bit.StateErrAll.ucStateErr & BB_PsensErr_Mask) == 0) ? 0 : 1;
// jk-PSens 
// jk-PSens   CddStp88XX_StateMachine(ucIx, CddStp88XX_eCmdPsens); // transition to StateIdle because HalStp INTs are disabled, also if (setpoint != actual position)
// jk-PSens 
// jk-PSens   // jk-tbd STP_RUNTIME_INTDIS_STOP(CddStp88XX_Psens)
// jk-PSens }


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_StpStateVoltNormSet
///
///  \brief    Function to set stepper state bit VoltNorm at all active steppers
///
///  \param    none
///
///  \return   none
///
///  \descr
///
// ---------------------------------------------------------------------------
STATIC_AL void CddStp88XX_StpStateVoltNormSet(void)
{
#if (CFA_CNT_STP_88XX >= 1)
 CddStp88XX_aStpState[0].Bit.VoltNorm = 1u;
 CddStp_ActAll.sLwrActual.sStatusError.boVoltNorm = TRUE;
 CddStp88XX_boIgnoreOLDetection = FALSE;
#endif
#if (CFA_CNT_STP_88XX >= 2)
 CddStp88XX_aStpState[1].Bit.VoltNorm = 1u;
#endif
#if (CFA_CNT_STP_88XX >= 3)
 CddStp88XX_aStpState[2].Bit.VoltNorm = 1u;
#endif
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_StpStateVoltNormClear
///
///  \brief    Function to clear stepper state bit VoltNorm at all active steppers
///
///  \param    none
///
///  \return   none
///
///  \descr
///
// ---------------------------------------------------------------------------
STATIC_AL void CddStp88XX_StpStateVoltNormClear(void)
{
#if (CFA_CNT_STP_88XX >= 1)
 CddStp88XX_aStpState[0].Bit.VoltNorm = 0;
 CddStp_ActAll.sLwrActual.sStatusError.boVoltNorm = FALSE;
#endif
#if (CFA_CNT_STP_88XX >= 2)
 CddStp88XX_aStpState[1].Bit.VoltNorm = 0;
#endif
#if (CFA_CNT_STP_88XX >= 3)
 CddStp88XX_aStpState[2].Bit.VoltNorm = 0;
#endif
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_StpStateOvSet
///
///  \brief    Function to set stepper state bit VoltOver at all active steppers
///
///  \param    none
///
///  \return   none
///
///  \descr
///
// ---------------------------------------------------------------------------
STATIC_AL void CddStp88XX_StpStateOvSet(void)
{
#if (CFA_CNT_STP_88XX >= 1)
 CddStp88XX_aStpState[0].Bit.VoltOver = 1u;
#endif
#if (CFA_CNT_STP_88XX >= 2)
 CddStp88XX_aStpState[1].Bit.VoltOver = 1u;
#endif
#if (CFA_CNT_STP_88XX >= 3)
 CddStp88XX_aStpState[2].Bit.VoltOver = 1u;
#endif
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_StpStateOvClear
///
///  \brief    Function to clear stepper state bit VoltOver at all active steppers
///
///  \param    none
///
///  \return   none
///
///  \descr
///
// ---------------------------------------------------------------------------
STATIC_AL void CddStp88XX_StpStateOvClear(void)
{
#if (CFA_CNT_STP_88XX >= 1)
 CddStp88XX_aStpState[0].Bit.VoltOver = 0;
#endif
#if (CFA_CNT_STP_88XX >= 2)
 CddStp88XX_aStpState[1].Bit.VoltOver = 0;
#endif
#if (CFA_CNT_STP_88XX >= 3)
 CddStp88XX_aStpState[2].Bit.VoltOver = 0;
#endif
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_StpStateUvSSMSet
///
///  \brief    Function to set stepper state bit VoltUSSM at all active steppers
///            undervoltage soft stop motion
///
///  \param    none
///
///  \return   none
///
///  \descr
///
// ---------------------------------------------------------------------------
STATIC_AL void CddStp88XX_StpStateUvSSMSet(void)
{
#if (CFA_CNT_STP_88XX >= 1)
 CddStp88XX_aStpState[0].Bit.VoltUSSM = 1u;
#endif
#if (CFA_CNT_STP_88XX >= 2)
 CddStp88XX_aStpState[1].Bit.VoltUSSM = 1u;
#endif
#if (CFA_CNT_STP_88XX >= 3)
 CddStp88XX_aStpState[2].Bit.VoltUSSM = 1u;
#endif
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_StpStateUvSSMClear
///
///  \brief    Function to clear stepper state bit VoltUSSM at all active steppers
///
///  \param    none
///
///  \return   none
///
///  \descr
///
// ---------------------------------------------------------------------------
STATIC_AL void CddStp88XX_StpStateUvSSMClear(void)
{
#if (CFA_CNT_STP_88XX >= 1)
 CddStp88XX_aStpState[0].Bit.VoltUSSM = 0;
#endif
#if (CFA_CNT_STP_88XX >= 2)
 CddStp88XX_aStpState[1].Bit.VoltUSSM = 0;
#endif
#if (CFA_CNT_STP_88XX >= 3)
 CddStp88XX_aStpState[2].Bit.VoltUSSM = 0;
#endif
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_Volt
///
///  \brief    Callback function to handle stepper Volt changed
///
///  \param    uint8 ucStateVolt
///
///  \return   none
///
///  \descr
///
// ---------------------------------------------------------------------------
void CddStp88XX_Volt(const uint8 ucStateVolt)
{
 uint8  ucIndex;

 tsRte_CtrlStpValidation sCtrlStpStatus = { 0 };

 (void)Rte_Read_CtrlStp_Validation_Port(&sCtrlStpStatus);

 // jk-tbd STP_RUNTIME_INTDIS_START(CddStp88XX_Volt)

 CddStp88XX_ucStateVolt = ucStateVolt;                                 // StateVoltOff=0, StateVoltUnder=1, StateVoltNormal=2, StateVoltOver=3, StateVoltStartValue=0xFF

 if (CddStp88XX_ucStateVolt != CDDSTP88XX_StateVoltNormal)             // handle StpState bits 'VoltNorm' and 'VoltOver' to notify under/over voltage while moving (stopping by using ramp)
 {
  CddStp88XX_StpStateVoltNormClear();
  if (CddStp88XX_ucStateVolt == CDDSTP88XX_StateVoltOver)             // overvoltage, not undervoltage?
  {
   CddStp88XX_StpStateOvSet();
   CddStp88XX_StpStateUvSSMClear();
   CddStp88XX_boUVShtDwn = FALSE;
   Rte_Call_DemPrj_ReportErrorStatus((uint16)STP_E_OV, DEM_EVENT_STATUS_FAILED); // set overvoltage DTC
   Rte_Call_DemPrj_ReportErrorStatus((uint16)STP_E_UV, DEM_EVENT_STATUS_PASSED); // clear undervoltage DTC
  }
  else                                                                // undervoltage
  {
   CddStp88XX_StpStateOvClear();
   Rte_Call_DemPrj_ReportErrorStatus((uint16)STP_E_OV, DEM_EVENT_STATUS_PASSED); // clear overvoltage DTC
   if (CddStp88XX_ucStateVolt == CDDSTP88XX_StateVoltUnder)          // undervoltage soft stop motion?
   {
    CddStp88XX_StpStateUvSSMSet();
    CddStp88XX_boUVShtDwn = FALSE;
   }
   else                                                              // undervoltage hard stop motion (step loss in case of motion)
//    if (CddStp88XX_ucStateVolt == CDDSTP88XX_StateVoltOff)
   {
    CddStp88XX_StpStateUvSSMClear();
    CddStp88XX_boUVShtDwn = TRUE;
   }
   if (sCtrlStpStatus.eADL_MODE == eStpSubModeAvailable) // this condition is LDM specific and generally not needed for setting UV DTC
   {
     Rte_Call_DemPrj_ReportErrorStatus((uint16)STP_E_UV, DEM_EVENT_STATUS_FAILED); // set undervoltage DTC only in available mode
   }
   else
   {
     // no behavior
   }
  }
 }

 else // i.e.: CddStp88XX_ucStateVolt == CDDSTP88XX_StateVoltNormal
 {
  CddStp88XX_StpStateVoltNormSet();
  CddStp88XX_StpStateOvClear();
  CddStp88XX_StpStateUvSSMClear();
  CddStp88XX_boUVShtDwn = FALSE;
  Rte_Call_DemPrj_ReportErrorStatus((uint16)STP_E_UV, DEM_EVENT_STATUS_PASSED); // clear undervoltage DTC
  Rte_Call_DemPrj_ReportErrorStatus((uint16)STP_E_OV, DEM_EVENT_STATUS_PASSED); // clear overvoltage DTC
 }

 for (ucIndex = 0; ucIndex < CFA_CNT_STP_88XX; ucIndex++)
 {
  CddStpPrj_SetEventFinishMove(ucIndex);
 }

 // jk-tbd STP_RUNTIME_INTDIS_STOP(CddStp88XX_Volt)
 // PRQA S 5324 1 // voltage error handling exceeds threshold of function calls due to program architecture and readability
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Event functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_HandleStp
///
///  \brief    Handle ucIx stepper position and state
///
///  \param    uint8 ucIx
///
///  \return   none
///
///  \descr
///
// ---------------------------------------------------------------------------
STATIC_AL void CddStp88XX_HandleStp(uint8 ucIx)
{
 STATIC_UT_NOINIT(tStpState, CddStp88XX_aStpStateOld[CFA_CNT_STP_88XX]);

 CDDSTP88XX_OptimizeArrayIndex(ucIx)

  // update internal Data-Mirror ('CddStp8899_aSRegXXX') of necessary HW-Status-Registers ('CddStp8899Com_DataMirror.StatvRx.aSRegXXX')
  (void)CddStp8899Com_GetSRegBscFltDiag12(ucIx, &CddStp8899_aSRegBasic[ucIx].ucRaw
   , &CddStp8899_aSRegFault[ucIx].ucRaw
   , &CddStp8899_aSRegDiag1[ucIx].ucRaw
   , &CddStp8899_aSRegDiag2[ucIx].ucRaw);

 // send actual position message
 CddStp88XX_aStpPos[ucIx].nPos = (sint16)CddStp88XX_HalStpFct[ucIx].pGetActPos(); // -> 'CddStp88XX_HalStpLwr_GetActPos' -> 'CddStp88XX_HalStpLwr_GetActPos_' -> 'CddStp88XX_HalStp_StpInfoLwr.lActPos'
//A  (void)SendMessage(CddStp88XX_AMsgId[ucIx].Pos, &CddStp88XX_aStpPos[ucIx]);

  // check DRV88XX thermal warning bit and send state message
 CddStp88XX_aStpState[ucIx].Bit.Prealarm = CddStp8899_aSRegDiag2[ucIx].Bit.u1OTW;
 //A  CddStp88XX_aStpState[ucIx].Val.ucAckCtrl = CddStp88XX_aStpCtrl[ucIx].Val.ucCtrl;
 if (CddStp88XX_aStpState[ucIx].ulData != CddStp88XX_aStpStateOld[ucIx].ulData) // set message only if value has changed to avoid useless events
 {
  //A    (void)SendMessage(CddStp88XX_AMsgId[ucIx].State, &CddStp88XX_aStpState[ucIx]);
  CddStp88XX_aStpStateOld[ucIx].ulData = CddStp88XX_aStpState[ucIx].ulData;
 }
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_HandleStpOnTime
///
///  \brief    Handle ucIx stepper on (moving and hold) phase time
///
///  \param    uint8 ucIx
///            boolean boStpOn
///            = TRUE:  stepper is on, start time calculation
///            = FALSE: stepper is off, stop time calculation
///
///  \return   none
///
///  \descr
///
// ---------------------------------------------------------------------------
STATIC_AL void CddStp88XX_HandleStpOnTime(uint8 ucIx, boolean boStpOn)
{
 tFTimer tTick = IoHwAb_SystemTick_1Ms;

 if (CddStp88XX_aBitsMod[ucIx].Bit.biStpOn != boStpOn)                      // state really changed?
 {
  CddStp88XX_aBitsMod[ucIx].Bit.biStpOn = boStpOn;

  if (boStpOn != FALSE) // Stp 'ON'?
  {
   CddStp88XX_aulStpOnStart[ucIx] = tTick;
  }
  else                  // Stp 'OFF'!
  {
   CddStp88XX_aulStpOnTime[ucIx] += (uint32)(tTick - CddStp88XX_aulStpOnStart[ucIx]);
  }
 }
}


// ---------------------------------------------------------------------------
///
///  \func   CddStp88XX_GetStpOnTime
///
///  \brief  Get time of LWR/AHL stepper on (moving and hold) phase and clear it internal
///
///  \param  uint8 ucIx
///
///  \return uint32
///
///  \descr
///
// ---------------------------------------------------------------------------
STATIC_AL uint32 CddStp88XX_GetStpOnTime(uint8 ucIx)
{
 uint32 ulReturn = CddStp88XX_aulStpOnTime[ucIx];

 if (CddStp88XX_aBitsMod[ucIx].Bit.biStpOn == 1u)                   // stepper is moving right now?
 {
  tFTimer tTick = IoHwAb_SystemTick_1Ms;

  ulReturn += (uint32)(tTick - CddStp88XX_aulStpOnStart[ucIx]);    // save actual timer value
  CddStp88XX_aulStpOnStart[ucIx] = tTick;                          // restart timer
 }

 CddStp88XX_aulStpOnTime[ucIx] = 0;                                 // reset after read

 return ulReturn;
}


// ---------------------------------------------------------------------------
///
///  \func   CddStp88XX_GetRefStartCnt
///
///  \brief  Get count of LWR/AHL started of reference runs and clear it internal
///
///  \param  uint8 ucIx
///
///  \return uint16
///
///  \descr
///
// ---------------------------------------------------------------------------
STATIC_AL uint16 CddStp88XX_GetRefStartCnt(uint8 ucIx)
{
 uint16 unReturn = CddStp88XX_aunRefStartCnt[ucIx];

 CddStp88XX_aunRefStartCnt[ucIx] = 0;                                       // reset after read

 return unReturn;
}


// ---------------------------------------------------------------------------
///
///  \func   CddStp88XX_GetIsRefCnt
///
///  \brief  Get count of LWR/AHL correct ended reference runs and clear it internal
///
///  \param  uint8 ucIx
///
///  \return uint16
///
///  \descr
///
// ---------------------------------------------------------------------------
STATIC_AL uint16 CddStp88XX_GetIsRefCnt(uint8 ucIx)
{
 uint16 unReturn = CddStp88XX_aunIsRefCnt[ucIx];

 CddStp88XX_aunIsRefCnt[ucIx] = 0;                                          // reset after read

 return unReturn;
}


// ---------------------------------------------------------------------------
///
///  \func   CddStp88XX_GetAhlPosDevHistCnts
///
///  \brief  Get counts of AHL stepper position deviation histogram ranges and clear it internal
///
///  \param  uint8 ucIx
///          uint16* pointer to array [CDDSTP_POSDEVHIST_MAX - 1]
///
///  \return none
///
///  \descr
///
// ---------------------------------------------------------------------------
STATIC_AL void CddStp88XX_GetAhlPosDevHistCnts(uint8 ucIx, uint16* punAhlPosDevHistCnts)
{
#if((CFA_CNT_STP_ONBRD == 2) && (CFA_CNT_STPVER0_ONBRD != 2))
 // 2nd on-board stepper as horizontal (not as workaround for 2nd on-board stepper as vertical)
 uint32 ulIndex;

 if (ucIx == CFG_Stp_IdxHor)
 {
  for (ulIndex = 0; ulIndex < CDDSTP_POSDEVHIST_MAX; ulIndex++)
  {
   punAhlPosDevHistCnts[ulIndex] = CddStp88XX_aunAhlPosDevHistCnts[ulIndex]; // for Hor stepper only - copy
   CddStp88XX_aunAhlPosDevHistCnts[ulIndex] = 0;                                         // for Hor stepper only - reset after read
  }
 }
#else
 (void)ucIx;
 (void)punAhlPosDevHistCnts;
#endif
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_StartWait88XXVoltage
///
///  \brief    Start wait ucIx if DRV88XX UV3 is set in case of voltage out of range
///
///  \param    uint8 ucIx
///
///  \return   none
///
///  \descr
///
// ---------------------------------------------------------------------------
STATIC_AL void CddStp88XX_StartWait88XXVoltage(uint8 ucIx)
{
 CDDSTP88XX_OptimizeArrayIndex(ucIx)

  if (CddStp88XX_aBitsMod[ucIx].Bit.biOldStateNotInit == 1u) // if the old state is not init
  {
   // This function is called in this case but the timeout polling follows always.
   // To avoid range overflow in timeout polling the flag is used:
   CddStp88XX_aftWaitVoltage[ucIx] = FastTimerStart(CDDSTP88XX_WaitVoltage_FTimer);
   CddStp88XX_aBitsMod[ucIx].Bit.biWaitVoltage = 1u;
  }
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_StartWaitVoltage
///
///  \brief    Start wait ucIx if voltage is low or over
///
///  \param    uint8 ucIx
///
///  \return   none
///
///  \descr
///
// ---------------------------------------------------------------------------
STATIC_AL void CddStp88XX_StartWaitVoltage(uint8 ucIx)
{
 CDDSTP88XX_OptimizeArrayIndex(ucIx)

  if (CddStp88XX_ucStateVolt != CDDSTP88XX_StateVoltNormal)  // check StateOff before StateErr to avoid DRV88XX pseudo error detection in case of under/overvoltage
  {
   // This function is called in this case but the timeout polling follows always.
   // To avoid range overflow in timeout polling the flag is used:
   CddStp88XX_aftWaitVoltage[ucIx] = FastTimerStart(CDDSTP88XX_WaitVoltage_FTimer);
   CddStp88XX_aBitsMod[ucIx].Bit.biWaitVoltage = 1u;
  }
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_HandleWaitVoltage
///
///  \brief    ucIx handle wait flag and timer in case of voltage out of range change
///
///  \param    uint8 ucIx
///
///  \return   none
///
///  \descr    This function is called cyclic with cycle time less than the half of the short timer range
///            to avoid range overflow in timeout polling
///
// ---------------------------------------------------------------------------
STATIC_AL void CddStp88XX_HandleWaitVoltage(uint8 ucIx)
{
 // This function is called cyclic with cycle time less than the half of the short timer range
 // to avoid range overflow in timeout polling
 if ((CddStp88XX_aBitsMod[ucIx].Bit.biWaitVoltage == 1u)
  && (FastTimerTimeout(CddStp88XX_aftWaitVoltage[ucIx]) == TRUE) // PRQA S 4558 1 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio7) Msg: 4558(An expression of 'essentially unsigned' type (unsigned char) is being used as the left-hand operand of this logical operator (&&).) Depth: 0 Ref: MISRA C:2012 Rule-10.1
  )
 {
  CddStp88XX_aBitsMod[ucIx].Bit.biWaitVoltage = 0;
 }
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_HandleWaitStabilize
///
///  \brief    ucIx handle wait flag and timer in case of stepper rotor stabilize phase
///
///  \param    uint8 ucIx
///
///  \return   boolean CddStp88XX_aBitsMod[ucIx].Bit.biWaitStabilize
///
///  \descr    This function is called cyclic with cycle time less than the half of the short timer range
///            to avoid range overflow in timeout polling
///
// ---------------------------------------------------------------------------
STATIC_AL boolean CddStp88XX_HandleWaitStabilize(uint8 ucIx)
{
 // This function is called cyclic with cycle time less than the half of the short timer range
 // to avoid range overflow in timeout polling
 if ((CddStp88XX_aBitsMod[ucIx].Bit.biWaitStabilize != FALSE) 
  && (FastTimerTimeout(CddStp88XX_aftWaitStabilize[ucIx]) == TRUE)) // PRQA S 4558 1 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio7) Msg: 4558(An expression of 'essentially unsigned' type (unsigned char) is being used as the left-hand operand of this logical operator (&&).) Depth: 0 Ref: MISRA C:2012 Rule-10.1
 {
  CddStp88XX_aBitsMod[ucIx].Bit.biWaitStabilize = 0;
 }

 return (CddStp88XX_aBitsMod[ucIx].Bit.biWaitStabilize == 1u) ? TRUE : FALSE;
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_ReadDRV88XXTestRegAll
///
///  \brief    Read all ucIx DRV88XX control or status registers
///
///  \param    uint8 ucIx
///
///  \return   none
///
///  \descr
///
// ---------------------------------------------------------------------------
STATIC_AL void CddStp88XX_ReadDRV88XXTestRegAll(uint8 ucIx)
{
 CDDSTP88XX_OptimizeArrayIndex(ucIx)

  // read DRV88XX debug information
  if (CddStp88XX_aBits[ucIx].Bit.biGetRegAll == 1u)
  {
   //  keine CddStp88XX_HalStpLwr_SendSRegX()-Funktionen, da sowieso immer alle StatusRegister gelesen werden
   //(void)CddStp88XX_HalStpFct[ucIx].pSpiSendSRegAll(); // debug information: content of status registers
  }
}


/// ---------------------------------------------------------------------------
/// \func     CddStp88XX_HandleNvmStpStatistics_
///
/// \brief    handle deviation for NVM statistics
///
/// \param    uint8 ucIx
///           sint32 lDeviation
///
/// \return   none
///
/// \descr    store deviation if larger than last one and set NVM update flag.
/// ---------------------------------------------------------------------------
/* //A
STATIC_AL void CddStp88XX_HandleNvmStpStatistics_(uint8 ucIx, sint32 lDeviation)
{
  // write statistics to NVM if necessary
  if(UTIL_ABS(lDeviation) > UTIL_ABS((sint32) Nvm_RamCopy.ErrPosStatisticStp.cDeviation[ucIx][0]))
  {
    // limit to sint8
    lDeviation = min(lDeviation,  127);
    lDeviation = max(lDeviation, -128);

    Nvm_RamCopy.ErrPosStatisticStp.cDeviation[ucIx][0] = (sint8) lDeviation;
    CddStp88XX_aBitsMod[ucIx].Bit.biUpdStat  = 1u;
  }
}
*/ //A


///////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief  Calculate driver specific current index
///
/// \descr  Calculate DRV88XX specific current index
///         use physical value in [mA] as input 
///
/// \param  uint8 ucCurrent     physical value [1/10 mA]
///
/// \return DRV88XX current index
///
STATIC_AL uint8 CddStp88XX_GetCurrentIndex(const uint8 ucCurrent)
{
 uint8 ucReturn;

 // DRV8899 specific current settings
 static const uint8 CddStp8899_aucCurrentValue[CDDSTP88XX_CurrentTableSize] = // size e.g. '15'
 {
   97,    //   950....970 mA --> index  0
   91,    //   880....910 mA --> index  1
   85,    //   820....850 mA --> index  2
   79,    //   760....790 mA --> index  3
   73,    //   700....730 mA --> index  4
   67,    //   640....670 mA --> index  5
   61,    //   580....610 mA --> index  6
   55,    //   520....550 mA --> index  7
   49,    //   460....490 mA --> index  8
   43,    //   400....430 mA --> index  9
   37,    //   340....370 mA --> index 10
   30,    //   270....300 mA --> index 11
   24,    //   210....240 mA --> index 12
   18,    //   150....180 mA --> index 13
   12     //    90....120 mA --> index 14
          //     0.....60 mA --> index 15   // no table entry necessary
 };
 uint8 ucTabInc = ((CDDSTP88XX_CurrentTableSize + 1u) / 4u);        // start with increment 1/4 table size - e.g. '4'
 uint8 ucTabIx = ((CDDSTP88XX_CurrentTableSize + 1u) / 2u) - 1u;   // set exactly to middle of table      - e.g. '7'

 while (ucTabInc > 0u)
 {
  if (ucCurrent < CddStp8899_aucCurrentValue[ucTabIx])
  {
   ucTabIx += ucTabInc;
  }
  else
  {
   ucTabIx -= ucTabInc;
  }

  ucTabInc >>= 1u;        // divide increment by 2
 }

 if (ucCurrent < CddStp8899_aucCurrentValue[ucTabIx])
 {
  ucReturn = ucTabIx + 1u;
 }
 else
 {
  ucReturn = ucTabIx;
 }

 return ucReturn;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief  Calculate all current indices for one stepper
///
/// \descr  Calculate Ihold, Irun and Iref values for NT, LT and HT from NVM RAM and send by SPI to stepper driver
///
/// \param  uint8 ucIx          stepper #
///
/// \return -
///
STATIC_AL void CddStp88XX_SetCurrent(uint8 ucIx)
{
  CDDSTP88XX_OptimizeArrayIndex(ucIx)

  CddStp88XX_aucCurAmpltHoldTemp[ucIx][CddStp_eTempState_NormTemp] = CddStp88XX_GetCurrentIndex(Cod_LwrHaltNT()); // Ihold [1/10 mA]
 CddStp88XX_aucCurAmpltRunTemp[ucIx][CddStp_eTempState_NormTemp] = CddStp88XX_GetCurrentIndex(Cod_LwrFahrNT()); // Irun [1/10 mA]
 CddStp88XX_aucCurAmpltRefTemp[ucIx][CddStp_eTempState_NormTemp] = CddStp88XX_GetCurrentIndex(Cod_LwrRef3NT()); // Iref [1/10 mA]

 CddStp88XX_aucCurAmpltHoldTemp[ucIx][CddStp_eTempState_LowTemp] = CddStp88XX_GetCurrentIndex(Cod_LwrHaltTT()); // Ihold [1/10 mA]
 CddStp88XX_aucCurAmpltRunTemp[ucIx][CddStp_eTempState_LowTemp] = CddStp88XX_GetCurrentIndex(Cod_LwrFahrTT()); // Irun [1/10 mA]
 CddStp88XX_aucCurAmpltRefTemp[ucIx][CddStp_eTempState_LowTemp] = CddStp88XX_GetCurrentIndex(Cod_LwrRef3TT()); // Iref [1/10 mA]

 CddStp88XX_aucCurAmpltHoldTemp[ucIx][CddStp_eTempState_HighTemp] = CddStp88XX_GetCurrentIndex(Cod_LwrHaltHT()); // Ihold [1/10 mA]
 CddStp88XX_aucCurAmpltRunTemp[ucIx][CddStp_eTempState_HighTemp] = CddStp88XX_GetCurrentIndex(Cod_LwrFahrHT()); // Irun [1/10 mA]
 CddStp88XX_aucCurAmpltRefTemp[ucIx][CddStp_eTempState_HighTemp] = CddStp88XX_GetCurrentIndex(Cod_LwrRef3HT()); // Iref [1/10 mA]

 // send by SPI communication new value to stepper driver
 CddStp88XX_HalStpFct[ucIx].pHandleCurAmplt((uint8)CDDSTP88XX_eCurAmpltStateNoChange,
  CddStp88XX_aucCurAmpltHoldTemp[ucIx][CddStp88XX_aeTemp[ucIx]],
  CddStp88XX_aucCurAmpltRunTemp[ucIx][CddStp88XX_aeTemp[ucIx]]);

 // PRQA S 5324 1 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio2) Msg: 5324(HIS metrics violation: 'CddStp88XX_SetCurrent() : STCAL = 10' exceeds threshold 7 for Number of Distinct Function Calls (STCAL).) Depth: 0 Ref: 
}


//-----------------------------------------------------------------------------
/// \brief  CddStp88XX_SetStpStateBitIsReady
///
/// \descr  Set 'IsReady'-Bit of struct CddStp88XX_aStpState
///         Workaround of TI-Chip: Need minimum time between Off-On
///
/// \param  ucIx
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddStp88XX_SetStpStateBitIsReady(uint8 ucIx)
{
  CddStp88XX_unIsReadyDelayCnt[ucIx] = 5;      // wait at least 5 x 10ms-Cyclic (3: error comes each 10th time, 4: never)
  CddStp88XX_aStpState[ucIx].Bit.IsReady = 1u; // do set already now the bit in order to keep compatibility
}


//-----------------------------------------------------------------------------
/// \brief  CddStp88XX_CondStpStateBitIsReady
///
/// \descr  Check 'IsReady'-Bit of struct CddStp88XX_aStpState
///         Workaround of TI-Chip: Need minimum time between Off-On
///
/// \param  ucIx
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL boolean CddStp88XX_CondStpStateBitIsReady(uint8 ucIx)
{
  boolean boIsReady = FALSE;

  // bit has to be TRUE  -  AND  -  Delay-Counter has to be decremented to zero (in 10ms-Cyclic)
  if ((CddStp88XX_aStpState[ucIx].Bit.IsReady == 1u) && (CddStp88XX_unIsReadyDelayCnt[ucIx] == 0u))
  {
    boIsReady = TRUE;
  }
  return boIsReady;
}

// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_DemReportErrorStatus
///
///  \brief    Interface function to set error entry by using DemPrj_ReportErrorStatus() dependent from Cod_XxxTestKeinFehlereintrag()
///
///  \param    uint8                    ucIx
///            tCddStp88XXDemErrorType  Event-Type of Stp error events
///            Dem_EventStatusType      EventStatus (DEM_EVENT_STATUS_PASSED | DEM_EVENT_STATUS_FAILED | ERRLOG_NoDetecting)
///
///  \return   none
///
///  \descr    In case of (Xxx.Modus.biTestKeinFehlereintrag == 0) an error entry is set in error memory 
///            by using DemPrj_ReportErrorStatus(). If the bit is set, nothing is done.
///
// ---------------------------------------------------------------------------
//void CddStp88XX_DemReportErrorStatus(uint8 ucIx, tCddStp88XXDemErrorType DemErrorType, Dem_EventStatusType EventStatus)
//{
//  (void)ucIx;
//
//// jk-orig   static const Dem_EventIdType CddStp88XX_atAssignedDemEventIds [CFG_Stp_Cnt] [CddStp88XX_eMaxDemEType] =
//// jk-orig   {
//// jk-orig     // DemEType_OL     .._SC       .._Driver              .._Pos       .._TempSD           .._TempWarn          .._RefUVolt        .._MoveUVolt        .._MoveOvVolt
//// jk-orig #if (CFG_Stp_CntVer > 0)
//// jk-orig   #ifndef PRJ_TYP_Lr06
//// jk-orig     { StpV0_E_OC, StpV0_E_SC, StpV0_E_DRIVER_DEFECT, StpV0_E_POS, StpV0_E_OVTEMP_OFF, StpV0_E_OVTEMP_WARN, StpV0_E_REF_UVOLT, StpV0_E_MOVE_UVOLT, StpV0_E_MOVE_OVVOLT}
//// jk-orig   #else
//// jk-orig     { StpV0_E_OC, StpV0_E_SC, SPI_Bus1_E_DEFECT,     StpV0_E_POS, StpV0_E_OVTEMP_OFF, StpV0_E_OVTEMP_WARN, StpV0_E_REF_UVOLT, StpV0_E_MOVE_UVOLT, StpV0_E_MOVE_OVVOLT}
//// jk-orig   #endif
//// jk-orig   #if (CFG_Stp_CntVer == 2)
//// jk-orig     ,
//// jk-orig     { StpV1_E_OC, StpV1_E_SC, StpV1_E_DRIVER_DEFECT, StpV1_E_POS, StpV1_E_OVTEMP_OFF, StpV1_E_OVTEMP_WARN, StpV1_E_REF_UVOLT, StpV1_E_MOVE_UVOLT, StpV1_E_MOVE_OVVOLT}
//// jk-orig   #endif
//// jk-orig   #if (CFG_Stp_CntHor == 1u)
//// jk-orig     ,
//// jk-orig     { StpH0_E_OC, StpH0_E_SC, StpH0_E_DRIVER_DEFECT, StpH0_E_POS, StpH0_E_OVTEMP_OFF, StpH0_E_OVTEMP_WARN, StpH0_E_REF_UVOLT, StpH0_E_MOVE_UVOLT, StpH0_E_MOVE_OVVOLT}
//// jk-orig     #if (CFG_Stp_CntSht == 1u)
//// jk-orig     ,
//// jk-orig     { StpS0_E_OC, StpS0_E_SC, StpS0_E_DRIVER_DEFECT, StpS0_E_POS, StpS0_E_OVTEMP_OFF, StpS0_E_OVTEMP_WARN, StpS0_E_REF_UVOLT, StpS0_E_MOVE_UVOLT, StpS0_E_MOVE_OVVOLT}
//// jk-orig     #endif
//// jk-orig   #endif
//// jk-orig #else
//// jk-orig   #error CddStp88XX configuration necessity not fulfilled: Stp-ucIx 0 as Vert0, then optional 1 as Hor0 and then optional 2 as Sht0!
//// jk-orig                                                                                  or optional 1 as Ver1 and ...
//// jk-orig   // -> rework for assignment of Dem Events necessary...
//// jk-orig #endif
//// jk-orig   };
//// jk-orig   
//// jk-orig   #if(CFA_CNT_STP_ONBRD == 2)
//// jk-orig   boolean boTestKeinFehlereintrag = (ucIx == CFG_Stp_IdxVer) ? Cod_LwrTestKeinFehlereintrag() : Cod_AhlTestKeinFehlereintrag();
//// jk-orig   #else
//// jk-orig   boolean boTestKeinFehlereintrag = Cod_LwrTestKeinFehlereintrag();
//// jk-orig   #endif
//// jk-orig 
//// jk-orig   if((CFG_Stp_Cnt > ucIx) && (CddStp88XX_eMaxDemEType > DemErrorType) )
//// jk-orig   {
//// jk-orig     Dem_EventIdType EventId_;
//// jk-orig 
//// jk-orig     // get assigned Event Id (of this Stp error type) - allocated via ucIx 
//// jk-orig     EventId_ = CddStp88XX_atAssignedDemEventIds[ucIx][DemErrorType];
//// jk-orig 
//// jk-orig     if (boTestKeinFehlereintrag == FALSE)
//// jk-orig     {
//// jk-orig       DemPrj_ReportErrorStatus(EventId_, EventStatus);
//// jk-orig     }
//// jk-orig   }
//// jk-orig   // else: unsupported case -> no Dem Event can be reported
//
//  boolean boTestKeinFehlereintrag = Cod_LwrTestKeinFehlereintrag();
//  if (boTestKeinFehlereintrag == FALSE)
//  {
//    // PRQA S 288 4 // original name '...ÜBERTEMPERATUR...' is taken for better understanding - warning - QAC(Prio6) Msg: 288([I] This source file has comments containing characters which are not members of the basic source character set.) Depth: 0 Ref: MISRA C:2012 Dir-1.1; REFERENCE - ISO:C90-5.2.1 Character Sets
//
//    // Primary DTCs
//    //   FLM3.SWRS.29496: DTC 8059f6 - OL & SC  - LEUCHTWEITENREGULIERUNG_STELLMOTOR_KURZSCHLUSS_ODER_LEITUNGSUNTERBRECHUNG_AN_WICKLUNG
//    //   FLM3.SWRS.29511: DTC 8059f7 - TempSD   - LEUCHTWEITENREGULIERUNG_SCHRITTMOTORTREIBER_ÜBERTEMPERATURABSCHALTUNG
//    //   FLM3.SWRS.29508: DTC 805a0d - Driver   - STEUERGERÄT_LEUCHTWEITENREGULIERUNG_SCHRITTMOTORTREIBER_DEFEKT
//    // Secondary DTCs
//    //   FLM3.SWRS.29505: DTC 430000 - RefUVolt - STELLMOTOR_LEUCHTWEITENREGULIERUNG_REFERENZIERUNG_WEGEN_UNTERSPANNUNG_ABGEBROCHEN
//    //   FLM3.SWRS.29502: DTC 430001 - MoveUVolt- STELLMOTOR_LEUCHTWEITENREGULIERUNG_VERSTELLUNG_WEGEN_UNTERSPANNUNG_ABGEBROCHEN
//    //   FLM3.SWRS.29499: DTC 430005 - TempWarn - STELLMOTOR_LEUCHTWEITENREGULIERUNG_ÜBERTEMPERATURWARNUNG
//    //
//    // N.b.:
//    // CddStp88XX_eDemEType_Driver:     // 2 - *** NO 'PASSED' ***: stepper driver defect (call from CAT1-ISR is not possible)
//    // CddStp88XX_eDemEType_MoveOvVolt: // 8 - *** NO DTC ***:      break of run because of overvoltage (SysVoltOver)
//
//    switch (DemErrorType)
//    {
//    // Primary DTCs - FLM3.SWRS.29496: OL & SC  - LEUCHTWEITENREGULIERUNG_STELLMOTOR_KURZSCHLUSS_ODER_LEITUNGSUNTERBRECHUNG_AN_WICKLUNG
//    case CddStp88XX_eDemEType_OL:         // 0 - Open_Load (ErrElecOL)
//    case CddStp88XX_eDemEType_SC:         // 1 - Shortcut (pIsSCCntMax & ErrElecSC)
//      (void)Rte_Call_Dtc8059f6_SetEventStatus((Dem_EventStatusType)(EventStatus == DEM_EVENT_STATUS_FAILED ? RTE_E_ptDtc8059f6_E_NOT_OK : DEM_EVENT_STATUS_PASSED)); // EventStatus: DEM_EVENT_STATUS_PASSED | DEM_EVENT_STATUS_FAILED
//      break;
//
//    // Primary DTCs - FLM3.SWRS.29508: Driver-Err - STEUERGERÄT_LEUCHTWEITENREGULIERUNG_SCHRITTMOTORTREIBER_DEFEKT
//    case CddStp88XX_eDemEType_Driver:     // 2 - *** NO 'PASSED' possible ***: stepper driver defect (call from CAT1-ISR is not possible)
//      (void)Rte_Call_Dtc805a0d_SetEventStatus((Dem_EventStatusType)(EventStatus == DEM_EVENT_STATUS_FAILED ? RTE_E_ptDtc805a0d_E_NOT_OK : DEM_EVENT_STATUS_PASSED));
//      break;
//
//    case CddStp88XX_eDemEType_Pos:        // 3 - hori. stepper/PSense (no DTC): position error
//      break;
//
//    // Primary DTCs - FLM3.SWRS.29511: TempSD   - LEUCHTWEITENREGULIERUNG_SCHRITTMOTORTREIBER_ÜBERTEMPERATURABSCHALTUNG
//    case CddStp88XX_eDemEType_TempSD:     // 4 - thermal shutdown (OTS / ErrTherm)
//      (void)Rte_Call_Dtc8059f7_SetEventStatus((Dem_EventStatusType)(EventStatus == DEM_EVENT_STATUS_FAILED ? RTE_E_ptDtc8059f7_E_NOT_OK : DEM_EVENT_STATUS_PASSED));
//      break;
//
//      // Secondary DTCs - FLM3.SWRS.29499: TempWarn - STELLMOTOR_LEUCHTWEITENREGULIERUNG_ÜBERTEMPERATURWARNUNG
//    case CddStp88XX_eDemEType_TempWarn:   // 5 - thermal warning info
//      (void)Rte_Call_Dtc430005_SetEventStatus((Dem_EventStatusType)(EventStatus == DEM_EVENT_STATUS_FAILED ? RTE_E_ptDtc430005_E_NOT_OK : DEM_EVENT_STATUS_PASSED));
//      break;
//
//      // Secondary DTCs - FLM3.SWRS.29505: RefUVolt - STELLMOTOR_LEUCHTWEITENREGULIERUNG_REFERENZIERUNG_WEGEN_UNTERSPANNUNG_ABGEBROCHEN
//    case CddStp88XX_eDemEType_RefUVolt:   // 6 - break of reference run because of undervoltage (SysVoltOff)
//      (void)Rte_Call_Dtc430000_SetEventStatus((Dem_EventStatusType)(EventStatus == DEM_EVENT_STATUS_FAILED ? RTE_E_ptDtc430000_E_NOT_OK : DEM_EVENT_STATUS_PASSED));
//      break;
//
//      // Secondary DTCs - FLM3.SWRS.29502: MoveUVolt- STELLMOTOR_LEUCHTWEITENREGULIERUNG_VERSTELLUNG_WEGEN_UNTERSPANNUNG_ABGEBROCHEN
//    case CddStp88XX_eDemEType_MoveUVolt:  // 7 - break of run because of undervoltage (SysVoltUnder)
//      (void)Rte_Call_Dtc430001_SetEventStatus((Dem_EventStatusType)(EventStatus == DEM_EVENT_STATUS_FAILED ? RTE_E_ptDtc430001_E_NOT_OK : DEM_EVENT_STATUS_PASSED));
//      break;
//
//    // CddStp88XX_ucStateVolt == CDDSTP88XX_StateVoltOver
//    case CddStp88XX_eDemEType_MoveOvVolt: // 8 - *** NO DTC ***: break of run because of overvoltage (SysVoltOver)
//      break;
//
//    default:
//      break;
//    }
//  }
//}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_CheckPsensSlopeAndActPos
///
///  \brief    Function to handle ucIx position sensor negative or positive slope and check actual position
///
///  \param    uint8 ucIx
///
///  \return   none
///
///  \descr    Only works in case of Sref:
///            Check of result of CddStp88XX_aPsensInf[ucIx].nSlopePosition
///
// ---------------------------------------------------------------------------
STATIC_AL void CddStp88XX_CheckPsensSlopeAndActPos(uint8 ucIx)
{
#if(CFA_CNT_STP_ONBRD == 2)
 sint32 lDevAbs;                                             // absolute value of difference between actual position and
 sint32 lSlopePos;
 sint32 lAddSlopeTol;                                        // additional slope tolerance
 sint32 lCoarseCorrLimit;                                    // limit to switch from fine to coarse correction
 sint32 lActPos_ = CddStp88XX_HalStpFct[ucIx].pGetActPos(); // actual position

 CDDSTP88XX_OptimizeArrayIndex(ucIx)

  if (CddStp88XX_GetAttr(ucIx)->biUsePsens == 1u)             // Sref
  {
   typedef struct
   {
    uint8  biIsInside : 1;
   }tBits;

   tBits Bits_;

   Bits_.biIsInside = CddStp88XX_aPsensInf[ucIx].Bit.biIsPositive;                            // logical polarity
   CddStp88XX_aBitsMod[ucIx].Bit.biIsRegSlope = CddStp88XX_aPsensInf[ucIx].Bit.biIsRegSlope; // static Psens regulation slope configuration

   if (CddStp88XX_aBits[ucIx].Bit.biRegelflanke == 1u)                                         // already AL and not BMW definition
   {
    lAddSlopeTol = (sint32)-Cod_AhlHilfsflankeTol();                                   // tolerance sign depends on slope type (reg/add)
   }
   else
   {
    lAddSlopeTol = (sint32)Cod_AhlHilfsflankeTol();                                   // tolerance sign depends on slope type (reg/add)
   }

   if (CddStp88XX_aBitsMod[ucIx].Bit.biIsRegSlope == 1u)
   {
    lSlopePos = 0;                                                                     // for calculation of deviation at reference run
    lCoarseCorrLimit = (sint32)Cod_AhlFeinkorrGrenze();                                      // for fine position correction
   }
   else
   {
    lSlopePos = (sint32)lAddSlopeTol;                                                 // for calculation of deviation at reference run
    lCoarseCorrLimit = (sint32)(Cod_AhlFeinkorrGrenze()
     + Cod_AhlHilfsflankeTol());                                    // for fine position correction
   }

   if ((CddStp88XX_aStpCtrl[ucIx].Bit.Corr == 1u)                                           // 'absolute' positioning used
//      && (CddStp88XX_aStpState[ucIx].Bit.IsRef == 1u)                                         // referenced?
&& (CddStp88XX_aStpState[ucIx].Bit.FullRef == 1u)                                       // 'good slope' already found
&& (CddStp88XX_aStpState[ucIx].Bit.ErrPos == 0u))                                       // ErrPos not yet detected
   {
    CddStp88XX_DesensStateMachine(ucIx, lActPos_, Bits_.biIsInside, lCoarseCorrLimit);       // desensibilisize Psens signal
   }

   if ((CddStp88XX_aStpState[ucIx].Bit.IsInside) != (Bits_.biIsInside))                       // Psens slope?
   {
    CddStp88XX_aStpState[ucIx].Bit.IsInside = Bits_.biIsInside;

    // check of saved result Psens position (HalStp)
    if (CddStp88XX_aStpState[ucIx].Bit.FullRef == 0u)                                         // not full referenced?
    {
     if ((CddStp88XX_aPsensInf[ucIx].Bit.StateErrAll.StateErr.biState == LIT_SigOk)      // Psens state OK?
      && (CddStp88XX_aPsensInfOld[ucIx].Bit.StateErrAll.StateErr.biState == LIT_SigOk))  // also the last Psens state OK?
     {
      CddStp88XX_alDeviation[ucIx] = ((CddStp88XX_aBitsMod[ucIx].Bit.biSlopePosInvalid == 0u)
       //same as next line                        || ((CddStp88XX_aBitsMod[ucIx].Bit.biIsPositiveRefStart) != CddStp88XX_aStpState[ucIx].Bit.IsInside )     // change of position sensor level after slope // * Sref reference run uses Psens *
       || ((CddStp88XX_aBitsMod[ucIx].Bit.biIsPositiveRefStart) != CddStp88XX_aPsensInf[ucIx].Bit.biIsPositive)) // change of position sensor level after slope // * Sref reference run uses Psens *
       ? (lSlopePos - (sint32)CddStp88XX_aPsensInf[ucIx].Val.nSlopePosition)
       : 0;
     }
    }
    else // normal work with best Psens slope position found in middle Psens desensibility states (see CddStp88XX_HandlePensDesensPosMiddle())
    {
     sint16 nDesensBestPsensSlopePosition;
     boolean  boIsRegSlope;

     if (CddStp88XX_HandlePensDesensPosMiddle(ucIx, &nDesensBestPsensSlopePosition, &boIsRegSlope)) // valid best slope found?
     {
      CddStp88XX_alDeviation[ucIx] = boIsRegSlope
       ? -((sint32)nDesensBestPsensSlopePosition)
       : (lAddSlopeTol - ((sint32)nDesensBestPsensSlopePosition));
      CddStp88XX_aBitsMod[ucIx].Bit.biIsRegSlopeBest = boIsRegSlope; // save additional information to deviation of best slope for calculation of position correction in CddStp88XX_CalcPosCorr_() called by CddStp88XX_DesensStateMachine()
     }
    }

    if (CddStp88XX_aStpCtrl[ucIx].Bit.Corr == 1u)      // 'absolute' positioning used
    {
     if (CddStp88XX_aStpState[ucIx].Bit.IsRef == 1u)  // referenced?
     {
      CddStp88XX_alLastDeviation[ucIx] = CddStp88XX_alDeviation[ucIx];                            // save old value for diagnosis

//A          CddStp88XX_HandleNvmStpStatistics_(ucIx, CddStp88XX_alLastDeviation[ucIx]);

      lDevAbs = UTIL_ABS(CddStp88XX_alDeviation[ucIx]);

      // in case of FullRef is not yet set: do 100% correction at once for full reference after ErrPos occurance 
      if ((CddStp88XX_aStpState[ucIx].Bit.ErrPos == 0u)                                          // ErrPos not yet detected
       && (CddStp88XX_aStpState[ucIx].Bit.FullRef == 0u)                                         // 'good slope' not found
       && (lDevAbs <= Cod_AhlPosFehlerGrenze())                                                  // no position error?
       && (CddStp88XX_aBitsMod[ucIx].Bit.biIsRegSlope == 1u))                                    // complete referencing --> do 100% correction at once
      {
       CddStp88XX_aStpState[ucIx].Bit.FullRef = 1u;
       CddStp88XX_HalStpFct[ucIx].pIncActPos(CddStp88XX_alDeviation[ucIx]);                      // correct actual position of HalStp
      }
     }
    }
    else //if (CddStp88XX_aStpCtrl[ucIx].Bit.Corr == 0u) // 'absolute' positioning not used - also in case of ref.
    {
     if ((CddStp88XX_aStpCtrl[ucIx].Bit.Ref == 0u)                                                // reference run is not started explicit
      && (CddStp88XX_aStpState[ucIx].Bit.ErrPos == 0u)                                            // ErrPos not yet detected
      && (CddStp88XX_aPsensInf[ucIx].Bit.StateErrAll.StateErr.biState == LIT_SigOk)              // Psens state OK?
      && (CddStp88XX_aPsensInfOld[ucIx].Bit.StateErrAll.StateErr.biState == LIT_SigOk))          // also the last Psens state OK?
     {
      CddStp88XX_aStpState[ucIx].Bit.IsRef = 1u;
      if (CddStp88XX_aBitsMod[ucIx].Bit.biIsRegSlope)                                              // do not clear an already set FullRef bit of StpState!
      {
       CddStp88XX_aStpState[ucIx].Bit.FullRef = CddStp88XX_aBitsMod[ucIx].Bit.biIsRegSlope;      // full ref. if regulation slope has occured
      }
      CddStp88XX_DemReportErrorStatus(ucIx, CddStp88XX_eDemEType_Pos, DEM_EVENT_STATUS_PASSED);   // no position error
//!       CddStp88XX_aunIsRefCnt[ucIx]++;  // !do not increment counter because of here the StpCtrl.Ref bit is not set explicit!
     }
    }
   }
  }

#else
 //(void)ucIx;
 CddStp8899_ucDummy = ucIx;
#endif
}

/// ---------------------------------------------------------------------------
/// \func     CddStp88XX_CalcCorrQuota()
///
/// \brief    calculate correction quota depending on actual target position change
///
/// \param    uint8 ucIx
///
/// \return   none
///
/// \descr    After a position correction value is calculated, the actual position
///           counter has to be modified. The absolute size of the modification
///           will be limited to the target position change. The modification
///           will be done only if the correction sign is identical to the sign
///           of the target position change.
///           Only works in case of Sref.
/// ---------------------------------------------------------------------------
STATIC_AL void CddStp88XX_CalcCorrQuota(uint8 ucIx)
{
#if(CFA_CNT_STP_ONBRD == 2)
 uint16 unMaxCorrValue;  // maximum correction value (halfsteps, absolute)
 uint16 unCorrQuotaAbs;  // absolute quota of correction (halfsteps) in this 20ms sample
 sint16  nTgtPosChange;  // target position change in halfsteps
 typedef struct
 {
  uint8  biTgtPosDir : 1; // direction of target position change
 }tBits;

 tBits Bits_;

 CDDSTP88XX_OptimizeArrayIndex(ucIx)

  if ((CddStp88XX_GetAttr(ucIx)->biUsePsens == 1u)    // Sref
   && (Cod_AhlKorrAktiv() != 0))                      // activation by NVM
  {
   // get target position change and store actual value for next calculation
   nTgtPosChange = CddStp88XX_aStpCtrl[ucIx].Val.nPos - CddStp88XX_aStpCtrlOld[ucIx].Val.nPos;

   // get sign of target position change (target position direction)
   Bits_.biTgtPosDir = (nTgtPosChange < 0) ? 1u : 0u;

   // compare absolute values of correction value and position change: use lower value
   nTgtPosChange = UTIL_ABS(nTgtPosChange);
   unMaxCorrValue = min((uint16)nTgtPosChange, CddStp88XX_aunCorrValueAbs[ucIx]);

   // using of correction value depends on sign of correction value and position change
   if (Bits_.biTgtPosDir ^ CddStp88XX_aBitsMod[ucIx].Bit.biCorrValueSign)
   {
    // use correction
    unCorrQuotaAbs = unMaxCorrValue;
   }
   else
   {
    // do not use correction because unwanted movement is expected
    unCorrQuotaAbs = 0;
   }

   if (CddStp88XX_aBitsMod[ucIx].Bit.biCorrValueSign == 0u)
   {
    // modify actual position counter
    CddStp88XX_HalStpFct[ucIx].pIncActPos(-((sint32)(unCorrQuotaAbs)));
   }
   else
   {
    // modify actual position counter
    CddStp88XX_HalStpFct[ucIx].pIncActPos(((sint32)(unCorrQuotaAbs)));
   }

   // reduce remaining change request in the same way
   CddStp88XX_aunCorrValueAbs[ucIx] -= unCorrQuotaAbs;
  }
#else
 (void)ucIx;
#endif
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_HandleResetErrVolt
///
///  \brief    Handle reset error voltage saved in module HalStp
///
///  \param    uint8 ucIx
///            boolean boClearSRegsScOl
///
///  \return   none
///
// ---------------------------------------------------------------------------
STATIC_AL void CddStp88XX_HandleResetErrVolt(uint8 ucIx, boolean boClearSRegsScOl)
{
  boolean boHigherThanErrVoltLoLimit = FALSE;
  boolean boLessThanErrVoltHiLimit   = FALSE;
  uint32  ulStpSpannungLo1 = ((uint32)Cod_StpSpannungLo1() * 100u);
  uint32  ulStpSpannungHi1 = ((uint32)Cod_StpSpannungHi1() * 100u);

 CDDSTP88XX_OptimizeArrayIndex(ucIx)

  /////  __DI();            // call from interrupt level is not possible (no counter)!
  /////  osDisableGlobal(); // call from interrupt level is not possible (no counter)!
  //SuspendAllInterrupts(); // 

  boHigherThanErrVoltLoLimit = ((CddStp88XX_HalStpFct[ucIx].pGetErrVolt() > ulStpSpannungLo1) ? TRUE : FALSE); // error voltage in specified range in case of ErrElecSC or ErrElecOL?
 boLessThanErrVoltHiLimit = ((CddStp88XX_HalStpFct[ucIx].pGetErrVolt() < ulStpSpannungHi1) ? TRUE : FALSE); // error voltage in specified range in case of ErrElecSC or ErrElecOL?

 (void)IoHwAb_User_GetAdc_DIAG_VBAT(&CddStp88XX_unDIAG_VBAT);

 // update internal Data-Mirror ('CddStp8899_aSRegXXX') of necessary HW-Status-Registers ('CddStp8899Com_DataMirror.StatvRx.aSRegXXX')
 (void)CddStp8899Com_GetSRegFltDiag2(ucIx, &CddStp8899_aSRegFault[ucIx].ucRaw, &CddStp8899_aSRegDiag2[ucIx].ucRaw);

#ifdef JK_TBD
 /*jk-tbd*/ if (0); // 
#endif

// jk-tbd if (   (CddStp8899Com_CheckRxNotificationSr12367A8A(ucIx) != FALSE) // in case of DRV88XX-ERRN-ISR the read status register RX content is started - therefore wait till all registers are read (in all other cases the result is always FALSE)
 if (((boLessThanErrVoltHiLimit == FALSE)                     // error voltage not(!) in specified range in case of ErrElecSC or ErrElecOL?
  || (boHigherThanErrVoltLoLimit == FALSE))                    // error voltage not(!) in specified range in case of ErrElecSC or ErrElecOL?
  && (CddStp88XX_unDIAG_VBAT < ulStpSpannungHi1)                    // voltage in specified range?
  && (CddStp88XX_unDIAG_VBAT > ulStpSpannungLo1)                    // voltage in specified range?
  && (CddStp88XX_aucErrVoltHiLimitSCCnt[ucIx] == 0u)                // check to detect case of no pseudo SC error (ErrElecSC)
  // jk-tbd: correct logic???
  && (CddStp8899_aSRegFault[ucIx].Bit.u1UVLO != 0u)                 // ('UV3')   'UVLO' Indicates an undervoltage lockout  fault condition. Latched high after power-up, remains set until it is cleared through the CLR_FLT bit or an nSLEEP reset pulse.
  && (CddStp8899_aSRegFault[ucIx].Bit.u1OCP != 0u)                 // ('SHORT') 'OCP'  Indicates overcurrent fault condition.
  && (CddStp8899_aSRegFault[ucIx].Bit.u1OL != 0u)                 // ('OPEN')  'OL'   Indicates open-load condition.
  && (CddStp8899_aSRegDiag2[ucIx].Bit.u1OTW != 0u)                 // ('TW')    'OTW'  Indicates overtemperature warning.#
  )
 {
  CddStp88XX_HalStpFct[ucIx].pResetErrVolt();                         // error is ignored, therefore reset error voltage

  if (boClearSRegsScOl != FALSE)
  {
   // Delete SC and OL pseudo errors directly in contents of status registers SR0..2 because of SPI communication delay of CddSpi:
//0   CddStp8899_aSRegDiag2[ucIx].ucRaw &= (uint8)(~CDDSTP8899_old_Mask_UV3);
//0   CddStp8899_aSRegDiag1[ucIx].ucRaw &= (uint8)(~CDDSTP8899_old_Mask_TW);
   CddStp8899_aSRegFault[ucIx].Bit.u1OL = 0; // ('OPEN')  'OL'   Indicates open-load condition.
   CddStp8899_aSRegFault[ucIx].Bit.u1OCP = 0; // ('SHORT') 'OCP'  Indicates overcurrent fault condition.
  }
 }

 /////  __EI();           // call from interrupt level is not possible (no counter)!
 /////  osEnableGlobal(); // call from interrupt level is not possible (no counter)!
 //ResumeAllInterrupts(); // 
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_HandleStepLoss
///
///  \brief    Handle StepLoss and IsRef/FullRef bits of StpState
///
///  \param    uint8 ucIx
///
///  \return   none
///
///  \descr    
///
// ---------------------------------------------------------------------------
STATIC_AL void CddStp88XX_HandleStepLoss(uint8 ucIx)
{
#if(CFA_CNT_STP_ONBRD == 2)
 boolean boVorwarnNeuref = (ucIx == CFG_Stp_IdxVer) ? Cod_LwrVorwarnNeuref() : Cod_AhlVorwarnNeuref();
#else
 boolean boVorwarnNeuref = Cod_LwrVorwarnNeuref();
#endif

 //A  if (CDDSTP88XX_NewRefNever != CddStp88XX_GetAttr(ucIx)->ucNewRefLoVoltCnt)//A
 if ((boVorwarnNeuref != FALSE)
  || ((CddStp88XX_aStpCtrl[ucIx].Bit.ErrInh == 0u)      //A
   && (CddStp88XX_aBits[ucIx].Bit.biWaitErrInh == 0u))) //A
 {
  CddStp88XX_aStpState[ucIx].Bit.StepLoss = 1u;
  CddStp88XX_aStpState[ucIx].Bit.IsRef = 0;
  CddStp88XX_aStpState[ucIx].Bit.FullRef = 0;

  Rte_Call_DemPrj_ReportErrorStatus((uint16)STP_LOSS, DEM_EVENT_STATUS_FAILED); // set step loss DTC
 }
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_HandleStepHanging
///
///  \brief    while stepper moving check whether the actual position changes in normal voltage range
///
///  \param    uint8   ucIx
///            boolean boRef
///
///  \return   boolean
///            = TRUE:  reset is done
///            = FALSE: no reset is done
///
///  \descr    to avoid hanging in case of hanging CddStp8899_HalStp 
///            state machine in StateStep because of DMA or timer INT mismatch
///
// ---------------------------------------------------------------------------
STATIC_AL boolean CddStp88XX_HandleStepHanging(uint8 ucIx, boolean boRef)
{
 boolean boReturn = FALSE;

 if (CddStp88XX_ucStateVolt == CDDSTP88XX_StateVoltNormal)
 {
  if (CddStp88XX_alActPosMem[ucIx] != CddStp88XX_HalStpFct[ucIx].pGetActPos()) // -> 'CddStp88XX_HalStpLwr_GetActPos' -> 'CddStp88XX_HalStpLwr_GetActPos_' -> 'CddStp88XX_HalStp_StpInfoLwr.lActPos'
  {
   CddStp88XX_aucActPosMemCnt[ucIx] = 0;
  }
  else      // no change of actual position
  {
   if (CddStp88XX_aucActPosMemCnt[ucIx] <= CDDSTP88XX_ACTPOSMEMCNT_MAX)   // attention - the actual function is callled each 10 ms and asynchronous also -> increase enought!
   {
    CddStp88XX_aucActPosMemCnt[ucIx]++;
   }
   else    // hanging CddStp8899_HalStp state machine in StateStep because of DMA or timer INT mismatch
   {
    CddStp88XX_aucActPosMemCnt[ucIx] = 0;
    CddStp88XX_HalStpFct[ucIx].pResetStp(FALSE); // reset HalStp state machine
    // after hanging CddStp8899_HalStp state machine in StateStep 
    // - continue moving (position may be wrong, LWR may glare but AHL position can be corrected) ...
    // - or reaction as StepLoss because of info buffer reinitialization handle
//      CddStp88XX_HandleStepLoss(ucIx);

    if ((ucIx == 0u)              // LWR stepper driver?
     && (boRef != FALSE))        // reference run?
    {
     // exception in case of reference run of vertical motor (LWR without position sensor) because of single CddStpDyn calculation:
     CddStpDyn_Init(ucIx, ((Cod_LwrSchrittMod() == (uint8)NvmPara_eSchrittMod2)) ? TRUE : FALSE);
    }
#if (CFG_Stp_CntVer == 2)
    if ((ucIx == 1u)              // second vertical stepper driver?
     && (boRef != FALSE))        // reference run?
    {
     // exception in case of reference run of vertical motor (AHL without position sensor) because of single CddStpDyn calculation:
     CddStpDyn_Init(ucIx, (Cod_AhlSchrittMod() == (sint32)NvmPara_eSchrittMod2)) ? TRUE : FALSE);
    }
#endif

    boReturn = TRUE;
   }
  }
  CddStp88XX_alActPosMem[ucIx] = CddStp88XX_HalStpFct[ucIx].pGetActPos(); // -> 'CddStp88XX_HalStpLwr_GetActPos' -> 'CddStp88XX_HalStpLwr_GetActPos_' -> 'CddStp88XX_HalStp_StpInfoLwr.lActPos'
 }
 return boReturn;
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_HandleWrongRef1Motion
///
///  \brief    while AHL stepper reference phase Ref1 check whether the actual position sensor level is really correct to wait for slope and whether a slope is found at first trial.
///
///  \param    uint8 ucIx
///
///  \return   none
///
///  \descr    to avoid referencing in wrong direction because of CtrlStp has read a 
///            different position sensor level than CddStp and to start Ref1 motion twice 
///            in case of no position sensor slope is found. 
///            In both cases Ref1 phase is started a second time (counter decrement from 1)!
// ---------------------------------------------------------------------------
STATIC_AL void CddStp88XX_HandleWrongRef1Motion(uint8 ucIx)
{
 // jk: 'CddStp88XX_GetAttr'/'tCddStp88XX_Attr'/'tCddStp_Attr' is ONLY about 'PSenes'
 if (CddStp88XX_GetAttr(ucIx)->biUsePsens == 1u) // Sref
 {
  sint16 nActPos_ = (sint16)CddStp88XX_HalStpFct[ucIx].pGetActPos(); // -> 'CddStp88XX_HalStpLwr_GetActPos' -> 'CddStp88XX_HalStpLwr_GetActPos_' -> 'CddStp88XX_HalStp_StpInfoLwr.lActPos'

  if (CddStp88XX_aStpState[ucIx].Bit.IsInside != CddStp88XX_aPsensInf[ucIx].Bit.biIsPositive)        // save actual Psens level
  {
   CddStp88XX_aStpState[ucIx].Bit.IsInside = CddStp88XX_aPsensInf[ucIx].Bit.biIsPositive;
  }

  if ((CddStp88XX_ucAhlErrPsensCnt > 0u)                                                                // maximal count of Ref1 pseudo ErrPsens not reached?
   && (((CddStp88XX_anRef1Pos[ucIx] >= 0) && (CddStp88XX_aPsensInf[ucIx].Bit.biIsPositive == 1u))   // wrong direction at actual high level?
    || ((CddStp88XX_anRef1Pos[ucIx] < 0) && (CddStp88XX_aPsensInf[ucIx].Bit.biIsPositive == 0u))   // wrong direction at actual low  level?
    || ((CddStp88XX_anRef1Pos[ucIx] >= 0) && (nActPos_ >= (CddStp88XX_anRef1Pos[ucIx] - CDDSTP88XX_WRONGREF1POSBEFORE)))   // is Ref1 phase finished to avoid pseudo ErrPsens?
    || ((CddStp88XX_anRef1Pos[ucIx] < 0) && (nActPos_ <= (CddStp88XX_anRef1Pos[ucIx] + CDDSTP88XX_WRONGREF1POSBEFORE))))) // is Ref1 phase finished to avoid pseudo ErrPsens?
  {
   CddStp88XX_ucAhlErrPsensCnt--;

   CddStp88XX_HalStpFct[ucIx].pSetActPos(0);         // reset value for use of complete range

   CddStp88XX_anRef1Pos[ucIx] = (CddStp88XX_aPsensInf[ucIx].Bit.biIsPositive == 1u) ? -UTIL_ABS(CddStp88XX_anRef1Pos[ucIx])
    : UTIL_ABS(CddStp88XX_anRef1Pos[ucIx]);
   //!   CddStpPsens_ResetPsens(ucIx); // reset variables of position sensor 'Psens'
   CddStp88XX_aBitsMod[ucIx].Bit.biIsPositiveRefStart = CddStp88XX_aPsensInf[ucIx].Bit.biIsPositive; // save position sensor level at start of reference run
   CddStp88XX_aBitsMod[ucIx].Bit.biSlopePosInvalid = 1u;
   CddStp88XX_alDeviation[ucIx] = 0;
  }
 }
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_HandleDriverReset
///
///  \brief    Handle DRV88XX specific driver reset
///
///  \param    uint8 ucIx
///
///  \return   none
///
///  \descr    DRV88XX specific
///
// ---------------------------------------------------------------------------
// jk-tbd - No Driver-Reset for TIstatic void CddStp88XX_HandleDriverReset(uint8 ucIx)
// jk-tbd - No Driver-Reset for TI{
// jk-tbd - No Driver-Reset for TI   if (CddStp88XX_HalStpFct[ucIx].pIsDriverReset() != FALSE)       // DRV88XX specific driver reset?
// jk-tbd - No Driver-Reset for TI   {
// jk-tbd - No Driver-Reset for TI     (void)IoHwAb_User_GetAdc_DIAG_VBAT(&CddStp88XX_unDIAG_VBAT);  // get DIAG_VBAT value
// jk-tbd - No Driver-Reset for TI 
// jk-tbd - No Driver-Reset for TI     if (CddStp88XX_unDIAG_VBAT >= SYSVOLT_VBATSDriverReset)       // voltage VBATS not too low and provokes no DRV88XX specific driver reset?
// jk-tbd - No Driver-Reset for TI     {
// jk-tbd - No Driver-Reset for TI       if (CddStp88XX_aBitsMod[ucIx].Bit.biClrDriverResetDeb == 1u) // driver reset debounce set?
// jk-tbd - No Driver-Reset for TI       {
// jk-tbd - No Driver-Reset for TI         CddStp88XX_HalStpFct[ucIx].pClrDriverReset();             // clear driver reset flag
// jk-tbd - No Driver-Reset for TI 
// jk-tbd - No Driver-Reset for TI         (void)CddStp88XX_HalStpFct[ucIx].pResetTestStepCnt();     // prepare test steps - attention: step loss is possible (in case of Sref it is corrected)     //SL
// jk-tbd - No Driver-Reset for TI         CddStp88XX_aBits[ucIx].Bit.biTestStepDone = 0;            // because of driver reset the test steps have to be done (micro step increment for SC and OL) //SL
// jk-tbd - No Driver-Reset for TI       }
// jk-tbd - No Driver-Reset for TI       else
// jk-tbd - No Driver-Reset for TI       {
// jk-tbd - No Driver-Reset for TI         CddStp88XX_aBitsMod[ucIx].Bit.biClrDriverResetDeb = 1u;    // set driver reset debounce flag to handle transition functions and clear driver reset flag in next cycle
// jk-tbd - No Driver-Reset for TI         
// jk-tbd - No Driver-Reset for TI //SL    CddStp88XX_HandleStepLoss(ucIx);
// jk-tbd - No Driver-Reset for TI       }
// jk-tbd - No Driver-Reset for TI     }
// jk-tbd - No Driver-Reset for TI   }
// jk-tbd - No Driver-Reset for TI   else
// jk-tbd - No Driver-Reset for TI   {
// jk-tbd - No Driver-Reset for TI     CddStp88XX_aBitsMod[ucIx].Bit.biClrDriverResetDeb = 0;        // reset driver reset debounce flag to handle transition functions and clear driver reset flag in next cycle
// jk-tbd - No Driver-Reset for TI   }
// jk-tbd - No Driver-Reset for TI }


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// StateMachine transition functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_Transition_InitOff
///
///  \brief    Ix transition function from StateInit to StateOff
///
///  \param    uint8 ucIx
///            const tCommandCddStp88XX eCmd
///
///  \return   uint32
///            = TRUE:  condition is valid
///            = FALSE: condition is not valid
///
///  \descr    Synchronization CddStp88XX with HalStp (init phase)
///
// ---------------------------------------------------------------------------
STATIC_AL uint32 CddStp88XX_Transition_InitOff(uint8 ucIx, const tCommandCddStp88XX eCmd)
{
#if(CFA_CNT_STP_ONBRD == 2)
 boolean boCodLwrEnable = (ucIx == CFG_Stp_IdxVer) ? Cod_LwrEnableStp() : Cod_AhlEnable();
#else
 boolean boCodLwrEnable = Cod_LwrEnableStp();
#endif

 CDDSTP88XX_OptimizeArrayIndex(ucIx)

  (void)eCmd;

 //if (CddStp88XX_ucStateVolt == CDDSTP88XX_StateVoltOver)       // overvoltage, not undervoltage?
 {
  //  CddStp88XX_aStpState[ucIx].Bit.VoltOver = 1u;      // see CddStp88XX_Volt()
  //  CddStp88XX_aStpState[ucIx].Bit.VoltUSSM = 0;      // see CddStp88XX_Volt()
 }
 //else                                                            // undervoltage
 {
  //  CddStp88XX_aStpState[ucIx].Bit.VoltOver = 0;      // see CddStp88XX_Volt()
  //  if (CddStp88XX_ucStateVolt == CDDSTP88XX_StateVoltUnder)    // undervoltage soft stop motion?
  //  {
  //    CddStp88XX_aStpState[ucIx].Bit.VoltUSSM = 1u;    // see CddStp88XX_Volt()
  //  }
  //  else                                                          // undervoltage hard stop motion (step loss in case of motion)
  ////if (CddStp88XX_ucStateVolt == CDDSTP88XX_StateVoltOff)
  //  {
  //    CddStp88XX_aStpState[ucIx].Bit.VoltUSSM = 0;    // see CddStp88XX_Volt()
  //  }
 }

#if ( CFG_OPT_STP & CFG_Stp_OnAfterPowerOn )
 CddStp88XX_aStpCtrl[ucIx].Bit.On = 1u; // switch on driver
#endif


          // jk-new C:\temp\FLM3\Asr6\Src\Src_AL\Cdd\CddStp\HCM\88XX\CddStp88XX_HalStp.h
          // jk-new definition of status register no error data
          // jk-new #define CDDSTP88XX_HALSTP_SREG_NOERR           (0x00u)                       // no error data for even parity DRV8899 1st silicon
          // jk-new #define CDDSTP88XX_HALSTP_SREG_NOERR           (0x80u)                       // no error data for odd  parity DRV8899 2nd silicon


#ifdef JK_TBD
 /*jk-tbd*/ if (0); // 
#endif
 return (uint32)((  /* jk-tbd ((CddStp8899Com_CheckRxNotificationSr12367A8A(ucIx) != FALSE))     // in case of CddStp88XX_InitState(ActEntry) the read status register RX content is started - therefore wait till all registers are read
                  &&*/((boCodLwrEnable != FALSE))                                           // XXX stepper configured as enable?          //A
  && ((CddStp8899_aSRegBasic[ucIx].ucRaw & 0x3Fu) == 0x00u)    // no pending error stored in DRV88XX (p.e. after under voltage pseudo errors of previous moving cycle)?
  && ((CddStp8899_aSRegFault[ucIx].ucRaw == 0x00u))   // no pending error stored in DRV88XX (p.e. after under voltage pseudo errors of previous moving cycle)?
  && ((CddStp8899_aSRegDiag1[ucIx].ucRaw == 0x00u))   // no pending error stored in DRV88XX (p.e. after under voltage pseudo errors of previous moving cycle)?
  && ((CddStp8899_aSRegDiag2[ucIx].ucRaw == 0x00u))   // no pending error stored in DRV88XX (p.e. after under voltage pseudo errors of previous moving cycle)?
//MSP            &&  ((CddStp8899_aSReg3 [ucIx]  == CDDSTP88XX_HALSTP_SREG_NOERR))   // no pending error stored in DRV88XX (p.e. after under voltage pseudo errors of previous moving cycle)?
//               &&  ((CddStp8899_aSReg4 [ucIx]  == CDDSTP88XX_HALSTP_SREG_NOERR))   // no pending error stored in DRV88XX (p.e. after under voltage pseudo errors of previous moving cycle)?
//               &&  ((CddStp8899_aSReg5 [ucIx]  == CDDSTP88XX_HALSTP_SREG_NOERR))   // no pending error stored in DRV88XX (p.e. after under voltage pseudo errors of previous moving cycle)?
//!              &&  ((CddStp8899_aSReg6 [ucIx]  == CDDSTP88XX_HALSTP_SREG_NOERR))   // no pending error stored in DRV88XX (p.e. after under voltage pseudo errors of previous moving cycle)?
//               &&  ((CddStp8899_aSReg7 [ucIx]  == CDDSTP88XX_HALSTP_SREG_NOERR))   // no pending error stored in DRV88XX (p.e. after under voltage pseudo errors of previous moving cycle)?
//               &&  ((CddStp8899_aSReg8 [ucIx]  == CDDSTP88XX_HALSTP_SREG_NOERR))   // no pending error stored in DRV88XX (p.e. after under voltage pseudo errors of previous moving cycle)?
// jk-tbd        &&  ((CddStp8899_aSReg7A[ucIx] & CDDSTP8899_old_Mask_SHORT_OPEN) == 0u)  // no pending error stored in DRV88XX (p.e. after under voltage pseudo errors of previous moving cycle)?
// jk-tbd        &&  ((CddStp8899_aSReg8A[ucIx] & CDDSTP8899_old_Mask_SHORT_OPEN) == 0u)  // no pending error stored in DRV88XX (p.e. after under voltage pseudo errors of previous moving cycle)?
&& ((CddStp88XX_aStpCtrl[ucIx].Bit.On == 1u))                          // switch on driver (not compatible to Afs2)  //A
&& ((CddStp88XX_BitsGlobalInitOnce.Bit.biCodingDataValid == 1u))     // (not compatible to Afs2)                   //A
) ? 1u : 0u);
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_Transition_Init
///
///  \brief    ucIx transition function to StateInit
///
///  \param    uint8 ucIx
///            const tCommandCddStp88XX eCmd
///
///  \return   uint32
///            = TRUE:  condition is valid
///            = FALSE: condition is not valid
///
///  \descr   This state switches off stepper motor and is possible more times in one PowerOn cycle (not compatible to Afs2)
///
// ---------------------------------------------------------------------------
STATIC_AL uint32 CddStp88XX_Transition_Init(uint8 ucIx, const tCommandCddStp88XX eCmd)
{
 (void)eCmd;

 return (uint32)((CddStp88XX_aStpCtrl[ucIx].Bit.On == 0u) ? 1u : 0u);   // driver switched off? 
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_Transition_Off
///
///  \brief    ucIx transition function to StateOff
///
///  \param    uint8 ucIx
///            const tCommandCddStp88XX eCmd
///
///  \return   uint32
///            = TRUE:  condition is valid
///            = FALSE: condition is not valid
///
///  \descr    - DRV88XX undervoltage or overvoltage bits
///              include additional action if condition TRUE: set or reset StpState bit VoltOver and increment Ov or Uv counter and save it in NVM
///            - SysVolt undervoltage or overvoltage states and DRV88XX errors 'Therm, SC counter, OL counter'
///              include additional action if condition TRUE: set or reset StpState bit VoltOver and increment Ov or Uv counter and save it in NVM
///            - biTransOff: special transition condition to StateOff
///
// ---------------------------------------------------------------------------
STATIC_AL uint32 CddStp88XX_Transition_Off(uint8 ucIx, const tCommandCddStp88XX eCmd)
{
 uint32  ulReturn = (uint32)(FALSE);
 boolean boIsSCCntMax;
 boolean boIsOLCntMax;
 boolean boIsErrnInactive = FALSE;                               // ERRN high

 CDDSTP88XX_OptimizeArrayIndex(ucIx)

  (void)eCmd;

 // ensure actual status register values if ERRN is low
 if (ucIx == 0u)                                                  // LWR stepper driver?
 {
  // jk-tbd: N.b.: 'IoHwAb_User_GetDio_ERRN_LWR' is currently ALWAYS '0' (...'CddStp_boDioErrLwr')
  (void)IoHwAb_User_GetDio_ERRN_LWR(&boIsErrnInactive);         // LWR ERRN high
 }
 else if (ucIx == 1u)                                             // AHL stepper driver?
 {
#if(CFA_CNT_STP_ONBRD == 2)
  (void)IoHwAb_User_GetDio_ERRN_AHL(&boIsErrnInactive);         // AHL ERRN high
#endif
 }
 else
 {
  // suppress MISRA warning - QAC(Prio4) Msg: 2004(No concluding 'else' exists in this 'if'-'else'-'if' statement.) Depth: 0 Ref: MISRA-C:2004 Rule 14.10
 }
 if (boIsErrnInactive == FALSE)                                  // ERRN low? - in case of change of DRV88XX warning or error reason and new status register values are not read because of SPI communication delay of CddSpi
 {
  //  keine CddStp88XX_HalStpLwr_SendSRegX()-Funktionen, da sowieso immer alle StatusRegister gelesen werden
  // (void)CddStp88XX_HalStpFct[ucIx].pSpiSendSRegAll();          // read all the status registers to update if other bits are set

//! (void)CddStp8899Com_StartRxNotificationSr12367A8A(ucIx);     // synchronize the sending of SPI commands to read all status registers with the reading of the results after all three values are received
//! CddStp88XX_aBits[ucIx].Bit.biTransitionErrDone = 0;          // not: check of error bits is done in CddStp88XX_Transition_Err() - used in CddStp88XX_HalStpVer/Hor/Sht_ErrnCb() and in CddStp88XX_Transition_Err()
 }

 // update internal Data-Mirror ('CddStp8899_aSRegXXX') of necessary HW-Status-Registers ('CddStp8899Com_DataMirror.StatvRx.aSRegXXX')
 (void)CddStp8899Com_GetSRegFltDiag2(ucIx, &CddStp8899_aSRegFault[ucIx].ucRaw, &CddStp8899_aSRegDiag2[ucIx].ucRaw);

 boIsSCCntMax = CddStp88XX_HalStpFct[ucIx].pIsSCCntMax();                     // maximal value of overcurrent counter
 boIsOLCntMax = CddStp88XX_HalStpFct[ucIx].pIsOLCntMax();                     // maximal value of openload counter

 // PRQA S 4558 2 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio7) Msg: 4558(An expression of 'essentially unsigned' type (unsigned char) is being used as the left-hand operand of this logical operator (||).) Depth: 0 Ref: MISRA C:2012 Rule-10.1
 if ((CddStp88XX_HalStpFct[ucIx].pIsDriverReset())                         // DRV88XX specific driver reset?
  || ((CddStp88XX_aBitsMod[ucIx].Bit.biTransOff == 1u))                    // special transition condition to StateOff?
  || ((CddStp8899_aSRegFault[ucIx].Bit.u1UVLO) != 0u)                      // undervoltage error DRV88XX?
  || (CddStp88XX_ucStateVolt == CDDSTP88XX_StateVoltOff)                   // undervoltage
  || ((CddStp88XX_ucStateVolt != CDDSTP88XX_StateVoltNormal)            // check StateOff before StateErr to avoid DRV88XX pseudo error detection in case of under/overvoltage
   && (((CddStp8899_aSRegDiag2[ucIx].Bit.u1OTS) != 0u)              // DRV88XX ('over') thermal shutdown error bit - i.e.: TSD detected?
    || (boIsSCCntMax != FALSE)                                       // maximal value of overcurrent counter
    || (boIsOLCntMax != FALSE))))                                    // maximal value of openload counter
 {
  //  if (CddStp88XX_ucStateVolt == CDDSTP88XX_StateVoltOver)                    // overvoltage and errors (Therm, SC counter, OL counter)
  //  {
  //    CddStp88XX_aStpState[ucIx].Bit.VoltOver = 1u;      // see CddStp88XX_Volt()
  //    CddStp88XX_aStpState[ucIx].Bit.VoltUSSM = 0;      // see CddStp88XX_Volt()
  //  }
  //  else /*if (   (CddStp88XX_ucStateVolt == CDDSTP88XX_StateVoltOff)        // undervoltage and errors (Therm, SC counter, OL counter)
  //             || (CddStp88XX_ucStateVolt == CDDSTP88XX_StateVoltUnder)      
  //             || ((CddStp8899_aSRegDiag2[ucIx].ucRaw & CDDSTP8899_old_Mask_UV3) != 0))  // undervoltage error bit DRV88XX
  //       */
  //  {
  //    CddStp88XX_aStpState[ucIx].Bit.VoltOver = 0;      // see CddStp88XX_Volt()
  //    if (CddStp88XX_ucStateVolt == CDDSTP88XX_StateVoltUnder)                 // undervoltage soft stop motion?
  //    {
  //      CddStp88XX_aStpState[ucIx].Bit.VoltUSSM = 1u;    // see CddStp88XX_Volt()
  //    }
  //    else                                                                     // undervoltage hard stop motion (step loss in case of motion)
  ////  if (CddStp88XX_ucStateVolt == CDDSTP88XX_StateVoltOff)
  //    {
  //      CddStp88XX_aStpState[ucIx].Bit.VoltUSSM = 0;    // see CddStp88XX_Volt()
  //    }
  //  }

  ulReturn = (uint32)(TRUE);
 }

 return ulReturn;
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_Transition_RefOff
///
///  \brief    ucIx transition function from StateRef1, StateRef2, StateRefWait to StateOff
///
///  \param    uint8 ucIx
///            const tCommandCddStp88XX eCmd
///
///  \return   uint32
///            = TRUE:  condition is valid
///            = FALSE: condition is not valid
///
///  \descr    - DRV88XX undervoltage or overvoltage bits (standard condition)
///            - SysVolt undervoltage or overvoltage states and DRV88XX errors 'Therm, SC counter, OL counter' (standard condition)
///            - SysVolt undervoltage or overvoltage states (additional condition in case of StateRef)
///              include additional action if condition TRUE: set or reset StpState bit VoltOver and increment Ov or Uv counter and save it in NVM
///            - biTransOff: special transition condition to StateOff
///
// ---------------------------------------------------------------------------
STATIC_AL uint32 CddStp88XX_Transition_RefOff(uint8 ucIx, const tCommandCddStp88XX eCmd)
{
 uint32  ulReturn = (uint32)(FALSE);
 boolean boLessThanErrVoltHiLimit = ((CddStp88XX_HalStpFct[ucIx].pGetErrVolt() < ((uint32)Cod_StpSpannungHi1() * 100u)) ? TRUE : FALSE); // error voltage in specified range in case of ErrElecSC or ErrElecOL?

 CDDSTP88XX_OptimizeArrayIndex(ucIx)

  // update internal Data-Mirror ('CddStp8899_aSRegXXX') of necessary HW-Status-Registers ('CddStp8899Com_DataMirror.StatvRx.aSRegXXX')
  (void)CddStp8899Com_GetSRegFlt(ucIx, &CddStp8899_aSRegFault[ucIx].ucRaw);

 // standard condition
 if (CddStp88XX_Transition_Off(ucIx, eCmd) != (uint32)(FALSE))                   // handle CddStp88XX_aStpState[ucIx].Bit.VoltOver and increment NVM counter
 {
  //CddStp88XX_DemReportErrorStatus(ucIx, CddStp88XX_eDemEType_RefUVolt, DEM_EVENT_STATUS_FAILED);  // break of reference run because of undervoltage (SysVoltOff)

  ulReturn = (uint32)(TRUE);
 }
 else
  // in all cases (not only in case of return value TRUE of CddStp88XX_Transition_Off())
  if ((boLessThanErrVoltHiLimit == FALSE)                                      // error voltage not(!) in specified range in case of ErrElecSC or ErrElecOL?
   && ((CddStp8899_aSRegFault[ucIx].Bit.u1OL != 0u)        // only used openload error bit set?
    || (CddStp8899_aSRegFault[ucIx].Bit.u1OCP != 0u))       // overcurrent error bit set coil X/Y?
//!     && (!CddStp88XX_aStpState[ucIx].Bit.StepLoss)
//!     && ( CddStp88XX_aStpState[ucIx].Bit.IsRef)
)
  {
   //! CddStp88XX_HandleStepLoss(ucIx);
   //  CddStp88XX_aStpState[ucIx].Bit.VoltOver = 1u; // exception: used against CDDSTP88XX_StateVoltOver!    // see CddStp88XX_Volt()
   CddStp88XX_aucErrVoltHiLimitSCCnt[ucIx]++;
   ulReturn = (CddStp88XX_aucErrVoltHiLimitSCCnt[ucIx] < CDDSTP88XX_ErrVoltHiLimitSCCntMax) ? 1u : 0u;    // TRUE in case of pseudo SC error
  }
  else
  {
   CddStp88XX_aucErrVoltHiLimitSCCnt[ucIx] = 0; // check to detect case of no pseudo SC error (ErrElecSC)

   // additional condition in case of StateRef
//! if (CddStp88XX_ucStateVolt != CDDSTP88XX_StateVoltNormal)      //! Afs2: break reference run in case of not normal voltage
//! {
//    if (CddStp88XX_ucStateVolt == CDDSTP88XX_StateVoltOver)      // overvoltage, not undervoltage?
//    {
//      if (CddStp88XX_aStpState[ucIx].Bit.VoltOver == 0u)
//      {
//        CddStp88XX_aStpState[ucIx].Bit.VoltOver = 1u;      // see CddStp88XX_Volt()
//        CddStp88XX_aStpState[ucIx].Bit.VoltUSSM = 0;      // see CddStp88XX_Volt()
////      CddStp88XX_DemReportErrorStatus(ucIx, CddStp88XX_eDemEType_REF_OVOLT, DEM_EVENT_STATUS_FAILED);   // break of reference run because of overvoltage (SysVoltOver)
//      }
//    }
//    else                                                           // undervoltage
//    {
//      if (CddStp88XX_aStpState[ucIx].Bit.VoltOver == 1u)
//      {
//        CddStp88XX_aStpState[ucIx].Bit.VoltOver = 0;      // see CddStp88XX_Volt()
////      CddStp88XX_DemReportErrorStatus(ucIx, CddStp88XX_eDemEType_RefUVolt, DEM_EVENT_STATUS_FAILED);    // break of reference run because of undervoltage (SysVoltUnder)
//
//        if (CddStp88XX_ucStateVolt == CDDSTP88XX_StateVoltUnder) // undervoltage soft stop motion?
//        {
//          CddStp88XX_aStpState[ucIx].Bit.VoltUSSM = 1u;  // see CddStp88XX_Volt()
//        }
//        else                                                       // undervoltage hard stop motion (step loss in case of motion)
////      if (CddStp88XX_ucStateVolt == CDDSTP88XX_StateVoltOff)
//        {
//          CddStp88XX_aStpState[ucIx].Bit.VoltUSSM = 0;  // see CddStp88XX_Volt()
//        }
//      }
//    }
//    CddStp88XX_aStpState[ucIx].Bit.RefBreak = 1u;                                                          // break of reference run because of undervoltage/overvoltage (SysVoltUnder/Over)

//!   ulReturn = (uint32)(TRUE);
//! }
  }

 return ulReturn;
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_Transition_Ref1
///
///  \brief    ucIx transition function to StateRef1
///
///  \param    uint8 ucIx
///            const tCommandCddStp88XX eCmd
///
///  \return   uint32
///            = TRUE:  condition is valid
///            = FALSE: condition is not valid
///
///  \descr
///
// ---------------------------------------------------------------------------
STATIC_AL uint32 CddStp88XX_Transition_Ref1(uint8 ucIx, const tCommandCddStp88XX eCmd)
{
 CDDSTP88XX_OptimizeArrayIndex(ucIx)

  (void)eCmd;

 // PRQA S 3415 3 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio7) Msg: 3415(Right hand operand of '&&' or '||' is an expression with possible side effects.) Depth: 0 Ref: MISRA C:2012 Rule-13.5; REFERENCE - ISO:C90-5,1,2,3 Program Execution
 return (((CddStp88XX_aStpCtrl[ucIx].Bit.Ref == 1u)
            && (CddStp88XX_aStpCtrlOld[ucIx].Bit.Ref == 0u)               // positive slope? -> start reference movement only one time!
            && (CddStp8899Com_GetCRegRxMotEn(ucIx) != FALSE))  ? 1u : 0u  // (not compatible to Afs2) // DRV88XX specific: ensure CReg1 MOTEN bit is set (not verified in CddStp88XXCom!) - transition from OffState is forced to IdleState who calls SpiSendCRegAll() while (CddStp88XX_[ucIx].Bit.biWaitStabilize == 1u)
// UWY - timing!!!                  && (CddStp88XX_aBitsMod[ucIx].Bit.biWaitStabilize == 0u) // stabilizing current in idle state finished?
);
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_Transition_RefWait
///
///  \brief    ucIx transition function to StateRefWait
///
///  \param    uint8 ucIx
///            const tCommandCddStp88XX eCmd
///
///  \return   uint32
///            = TRUE:  condition is valid
///            = FALSE: condition is not valid
///
///  \descr    only used in case of Sref to suppress a reference run in wrong direction 
///            if Psens level has switched after read of CtrlRef module to check the 
///            reference direction before start of reference run. 
///
// ---------------------------------------------------------------------------
STATIC_AL uint32 CddStp88XX_Transition_RefWait(uint8 ucIx, const tCommandCddStp88XX eCmd)
{
 CDDSTP88XX_OptimizeArrayIndex(ucIx)

  (void)ucIx;
 (void)eCmd;

 return (uint32)(
  //A                      (CddStp88XX_Transition_Ref1(ucIx, eCmd) != (uint32)(FALSE)) // StpCtrl bit Ref: positive slope? -> start reference movement only one time!
  //A                   && (   (CddStp88XX_GetAttr(ucIx)->biUsePsens == 1u)            // Sref
  //A                   && (   ((CddStp88XX_aStpCtrl[ucIx].Val.nPos >= 0) && (CddStp88XX_aStpState[ucIx].Bit.IsInside == 1u))  // already referenced because of Psens level has switched after read of CtrlRef module?
  //A                       || ((CddStp88XX_aStpCtrl[ucIx].Val.nPos <  0) && (CddStp88XX_aStpState[ucIx].Bit.IsInside == 0u))) // already referenced because of Psens level has switched after read of CtrlRef module?
  //A                      )
  FALSE//A
  );
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_Transition_RefWaitIdle
///
///  \brief    ucIx transition function from StateRefWait to StateIdle
///
///  \param    uint8 ucIx
///            const tCommandCddStp88XX eCmd
///
///  \return   uint32
///            = TRUE:  condition is valid
///            = FALSE: condition is not valid
///
///  \descr
///
// ---------------------------------------------------------------------------
STATIC_AL uint32 CddStp88XX_Transition_RefWaitIdle(uint8 ucIx, const tCommandCddStp88XX eCmd)
{
 CDDSTP88XX_OptimizeArrayIndex(ucIx)

  (void)eCmd;

 return (CddStp88XX_aStpCtrl[ucIx].Bit.Ref == 0u) ? 1u : 0u;
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_Transition_Ref1Ref2
///
///  \brief    ucIx transition function from StateRef1 to StateRef2
///
///  \param    uint8 ucIx
///            const tCommandCddStp88XX eCmd
///
///  \return   uint32
///            = TRUE:  condition is valid
///            = FALSE: condition is not valid
///
///  \descr
///
// ---------------------------------------------------------------------------
STATIC_AL uint32 CddStp88XX_Transition_Ref1Ref2(uint8 ucIx, const tCommandCddStp88XX eCmd)
{
 boolean boReturn;
 sint16  nActPos_;

 CDDSTP88XX_OptimizeArrayIndex(ucIx)

  (void)eCmd;
 nActPos_ = (sint16)CddStp88XX_HalStpFct[ucIx].pGetActPos(); // -> 'CddStp88XX_HalStpLwr_GetActPos' -> 'CddStp88XX_HalStpLwr_GetActPos_' -> 'CddStp88XX_HalStp_StpInfoLwr.lActPos'

 // jk: 'CddStp88XX_GetAttr'/'tCddStp88XX_Attr'/'tCddStp_Attr' is ONLY about 'PSenes'
 if (CddStp88XX_GetAttr(ucIx)->biUsePsens == 1u) // Sref
 {
  // PRQA S 4558 3 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio7) Msg: 4558(An expression of 'essentially unsigned' type (unsigned char) is being used as the left-hand operand of this logical operator (&&).) Depth: 0 Ref: MISRA C:2012 Rule-10.1
  boReturn = (
   (((CddStp88XX_HalStpFct[ucIx].pIsFinishMove())                                                     // -> 'CddStp88XX_HalStpLwr_IsFinishMove' -> 'CddStp88XX_HalStpLwr_IsStateHoldCont_' -> '(CddStp88XX_HalStp_eStateLwr == CddStp88XX_HalStp_eStateHoldCont) ? TRUE : FALSE;'
    && (((nActPos_ == CddStp88XX_anRef1Pos[ucIx]) ? TRUE : FALSE)))                                     // only in case of the motor has moved the complete reference target way (in this case the slope is not found)
  /*&& (nActPos_ == CddStp88XX_aStpCtrl[ucIx].Val.nPos))*/
    || (CddStp88XX_aBitsMod[ucIx].Bit.biIsPositiveRefStart != CddStp88XX_aPsensInf[ucIx].Bit.biIsPositive)) // change of position sensor level after slope // * Sref reference run uses Psens *
   && (CddStp88XX_aStpCtrl[ucIx].Bit.Ref == 1u)
   //!             && (CddStp88XX_aBitsMod[ucIx].Bit.biSlopePosInvalid == 0u)                                                  // valid last position sensor change position  // * Sref reference run uses Psens *
   ) ? 1u : 0u;
 }    // end of 'Sref' / 'biUsePsens'

 else // Href
 {
  // PRQA S 4404, 4558 3 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio7) Msg: 4404(An expression of 'essentially Boolean' type (_Bool) is being converted to unsigned type, 'unsigned char' on assignment.) Depth: 0 Ref: MISRA C:2012 Rule-10.3 | warning - QAC(Prio7) Msg: 4558(An expression of 'essentially unsigned' type (unsigned char) is being used as the left-hand operand of this logical operator (&&).) Depth: 0 Ref: MISRA C:2012 Rule-10.1
  boReturn = ((CddStp88XX_HalStpFct[ucIx].pIsFinishMove() != FALSE)       // -> 'CddStp88XX_HalStpLwr_IsFinishMove' -> 'CddStp88XX_HalStpLwr_IsStateHoldCont_' -> '(CddStp88XX_HalStp_eStateLwr == CddStp88XX_HalStp_eStateHoldCont) ? TRUE : FALSE;'
   && ((nActPos_ == CddStp88XX_anRef1Pos[ucIx]) ? TRUE : FALSE)   // only in case of the motor has moved the complete reference target way (no position sensor is available)
 /*&& ( nActPos_ == CddStp88XX_aStpCtrl[ucIx].Val.nPos)*/
   && (CddStp88XX_aStpCtrl[ucIx].Bit.Ref == 1u)
   );
 }
 return boReturn;
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_Transition_Ref1RefWait
///
///  \brief    ucIx transition function from StateRef1 to step StateRefWait
///
///  \param    uint8 ucIx
///            const tCommandCddStp88XX eCmd
///
///  \return   uint32
///            = TRUE:  condition is valid
///            = FALSE: condition is not valid
///
///  \descr
///
// ---------------------------------------------------------------------------
STATIC_AL uint32 CddStp88XX_Transition_Ref1RefWait(uint8 ucIx, const tCommandCddStp88XX eCmd)
{
 CDDSTP88XX_OptimizeArrayIndex(ucIx)

  (void)eCmd;

 // PRQA S 4558 3 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio7) Msg: 4558(An expression of 'essentially unsigned' type (unsigned char) is being used as the left-hand operand of this logical operator (&&).) Depth: 0 Ref: MISRA C:2012 Rule-10.1
 return ((CddStp88XX_HalStpFct[ucIx].pIsFinishMove())                 // -> 'CddStp88XX_HalStpLwr_IsFinishMove' -> 'CddStp88XX_HalStpLwr_IsStateHoldCont_' -> '(CddStp88XX_HalStp_eStateLwr == CddStp88XX_HalStp_eStateHoldCont) ? TRUE : FALSE;'
  && (((CddStp88XX_aStpCtrl[ucIx].Bit.Stop == 1u) ? TRUE : FALSE)   // if stopped by Ctrl: no error
   || ((CddStp88XX_aStpCtrl[ucIx].Bit.Ref == 0u) ? TRUE : FALSE)   // if break   by Ctrl: no error
   ? TRUE : FALSE)
  ? 1u : 0u);
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_Transition_Ref2RefWait
///
///  \brief    ucIx transition function from StateRef2 to StateRefWait
///
///  \param    uint8 ucIx
///            const tCommandCddStp88XX eCmd
///
///  \return   uint32
///            = TRUE:  condition is valid
///            = FALSE: condition is not valid
///
///  \descr
///
// ---------------------------------------------------------------------------
STATIC_AL uint32 CddStp88XX_Transition_Ref2RefWait(uint8 ucIx, const tCommandCddStp88XX eCmd)
{
 CDDSTP88XX_OptimizeArrayIndex(ucIx)

  (void)eCmd;

 return (uint32)(CddStp88XX_HalStpFct[ucIx].pIsFinishMove()); // -> 'CddStp88XX_HalStpLwr_IsFinishMove' -> 'CddStp88XX_HalStpLwr_IsStateHoldCont_' -> '(CddStp88XX_HalStp_eStateLwr == CddStp88XX_HalStp_eStateHoldCont) ? TRUE : FALSE;'
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_Transition_MoveIdle
///
///  \brief    ucIx transition function from StateMove to StateIdle
///
///  \param    uint8 ucIx
///            const tCommandCddStp88XX eCmd
///
///  \return   uint32
///            = TRUE:  condition is valid
///            = FALSE: condition is not valid
///
///  \descr
///
// ---------------------------------------------------------------------------
STATIC_AL uint32 CddStp88XX_Transition_MoveIdle(uint8 ucIx, const tCommandCddStp88XX eCmd)
{
 CDDSTP88XX_OptimizeArrayIndex(ucIx)

  (void)eCmd;

 return (uint32)((CddStp88XX_HalStpFct[ucIx].pIsFinishMove()) // -> 'CddStp88XX_HalStpLwr_IsFinishMove' -> 'CddStp88XX_HalStpLwr_IsStateHoldCont_' -> '(CddStp88XX_HalStp_eStateLwr == CddStp88XX_HalStp_eStateHoldCont) ? TRUE : FALSE;'
  /*|| (eCmd == CddStp88XX_eCmdEvent)*/);
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_Transition_MoveOff
///
///  \brief    ucIx transition function from StateMove to StateOff
///
///  \param    uint8 ucIx
///            const tCommandCddStp88XX eCmd
///
///  \return   uint32
///            = TRUE:  condition is valid
///            = FALSE: condition is not valid
///
///  \descr    - DRV88XX undervoltage or overvoltage bits (standard condition)
///              include additional action if condition TRUE: set StpState bit StepLoss and reset StpState bit IsRef
///            - SysVolt undervoltage or overvoltage states and DRV88XX errors 'Therm, SC counter, OL counter' (standard condition)
///              include additional action if condition TRUE: set StpState bit StepLoss and reset StpState bit IsRef
///
// ---------------------------------------------------------------------------
STATIC_AL uint32 CddStp88XX_Transition_MoveOff(uint8 ucIx, const tCommandCddStp88XX eCmd)
{
 uint32  ulReturn = (uint32)(FALSE);
 boolean boLessThanErrVoltHiLimit = (CddStp88XX_HalStpFct[ucIx].pGetErrVolt() < ((uint32)Cod_StpSpannungHi1() * 100u)) ? TRUE : FALSE; // error voltage in specified range in case of ErrElecSC or ErrElecOL?

 CDDSTP88XX_OptimizeArrayIndex(ucIx)

  // update internal Data-Mirror ('CddStp8899_aSRegXXX') of necessary HW-Status-Registers ('CddStp8899Com_DataMirror.StatvRx.aSRegXXX')
  (void)CddStp8899Com_GetSRegFlt(ucIx, &CddStp8899_aSRegFault[ucIx].ucRaw);

 // standard condition
 if (CddStp88XX_Transition_Off(ucIx, eCmd) != (uint32)(FALSE))                      // handle CddStp88XX_aStpState[ucIx].Bit.VoltOver and increment NVM counter
 {
  // additional action if condition TRUE
  if (((CddStp8899_aSRegFault[ucIx].Bit.u1UVLO != 0u)                        // undervoltage error DRV88XX or VoltStateMachine?
   || (CddStp88XX_ucStateVolt == CDDSTP88XX_StateVoltOff))
   && (CddStp88XX_aStpState[ucIx].Bit.IsRef == 1u))                       // only if already referenced
  {
   CddStp88XX_HandleStepLoss(ucIx);
  }
  ulReturn = (uint32)(TRUE);
 } // end of 'if (CddStp88XX_Transition_Off(ucIx, eCmd) != FALSE)'

 else
  // in all cases (not only in case of return value TRUE of CddStp88XX_Transition_Off())
  if ((boLessThanErrVoltHiLimit == FALSE)                                      // error voltage not(!) in specified range in case of ErrElecSC or ErrElecOL?
   && ((CddStp8899_aSRegFault[ucIx].Bit.u1OL != 0u)     // only used openload error bit set?
    || (CddStp8899_aSRegFault[ucIx].Bit.u1OCP != 0u))    // overcurrent error bit set coil X/Y?
//!   && (CddStp88XX_aStpState[ucIx].Bit.StepLoss     == 0u)
//!   && (CddStp88XX_aStpState[ucIx].Bit.IsRef        == 1u)
)
  {
   CddStp88XX_HandleStepLoss(ucIx);
   //  CddStp88XX_aStpState[ucIx].Bit.VoltOver = 1u; // exception: used against CDDSTP88XX_StateVoltOver!  // see CddStp88XX_Volt()
   //  CddStp88XX_aStpState[ucIx].Bit.VoltUSSM = 0; //                                                     // see CddStp88XX_Volt()
   CddStp88XX_aucErrVoltHiLimitSCCnt[ucIx]++;
   ulReturn = (CddStp88XX_aucErrVoltHiLimitSCCnt[ucIx] < CDDSTP88XX_ErrVoltHiLimitSCCntMax) ? 1u : 0u;  // TRUE in case of pseudo SC error
  }

  else
  {
   CddStp88XX_aucErrVoltHiLimitSCCnt[ucIx] = 0; // check to detect case of no pseudo SC error (ErrElecSC)
  }

 return ulReturn;
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_Transition_StbyIdle
///
///  \brief    ucIx transition function from StateStby to StateIdle
///
///  \param    uint8 ucIx
///            const tCommandCddStp88XX eCmd
///
///  \return   uint32
///            = TRUE:  condition is valid
///            = FALSE: condition is not valid
///
///  \descr    - No SysVolt undervoltage or overvoltage states
///              include additional action if condition TRUE: set DEM 'ErrTherm, ErrElecSC, ErrElecOL' absent
///
// ---------------------------------------------------------------------------
STATIC_AL uint32 CddStp88XX_Transition_StbyIdle(uint8 ucIx, const tCommandCddStp88XX eCmd)
{
 uint32  ulReturn = (uint32)(FALSE);

 CDDSTP88XX_OptimizeArrayIndex(ucIx)

  (void)eCmd;

 CddStp88XX_HandleWaitVoltage(ucIx); // get wait in case of voltage out of range change flag to check below

 if ((CddStp88XX_ucStateVolt == CDDSTP88XX_StateVoltNormal)      // normal voltage?
  && (CddStp88XX_aBitsMod[ucIx].Bit.biWaitVoltage == 0u)         // debounce of DRV88XX in case of voltage error change ready?
  && (!((CddStp88XX_GetAttr(ucIx)->biUsePsens == 1u)                                     // Sref:
   && (CddStp88XX_aPsensInf[ucIx].Bit.StateErrAll.StateErr.biState == 0U /*LIT_SigWarn*/)))) //       Psens state not warning?
 {
  // CddStp88XX_DemReportErrorStatus(ucIx, CddStp88XX_eDemEType_OL,     DEM_EVENT_STATUS_PASSED);
  // CddStp88XX_DemReportErrorStatus(ucIx, CddStp88XX_eDemEType_SC,     DEM_EVENT_STATUS_PASSED);
  // CddStp88XX_DemReportErrorStatus(ucIx, CddStp88XX_eDemEType_TempSD, DEM_EVENT_STATUS_PASSED);
  Rte_Call_DemPrj_ReportErrorStatus((uint16)StpV0_E_SC        , DEM_EVENT_STATUS_PASSED); // reset short circuit DTC
  Rte_Call_DemPrj_ReportErrorStatus((uint16)StpV0_E_OC        , DEM_EVENT_STATUS_PASSED); // reset open load DTC
  Rte_Call_DemPrj_ReportErrorStatus((uint16)StpV0_E_OVTEMP_OFF, DEM_EVENT_STATUS_PASSED); // reset thermal shutdown DTC

  ulReturn = (uint32)(TRUE);
 }

 return ulReturn;
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_Transition_IdleStby
///
///  \brief    ucIx transition function from StateIdle to StateStby
///
///  \param    uint8 ucIx
///            const tCommandCddStp88XX eCmd
///
///  \return   uint32
///            = TRUE:  condition is valid
///            = FALSE: condition is not valid
///
///  \descr
///
// ---------------------------------------------------------------------------
STATIC_AL uint32 CddStp88XX_Transition_IdleStby(uint8 ucIx, const tCommandCddStp88XX eCmd)
{
 CDDSTP88XX_OptimizeArrayIndex(ucIx)

  (void)ucIx;
 (void)eCmd;

 return ((CddStp88XX_ucStateVolt == CDDSTP88XX_StateVoltOver)         // overvoltage?
  || (CddStp88XX_ucStateVolt == CDDSTP88XX_StateVoltUnder)) ? 1u : 0u;      // undervoltage?
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_Transition_IdleMove
///
///  \brief    ucIx transition function from StateIdle to StateMove
///
///  \param    uint8 ucIx
///            const tCommandCddStp88XX eCmd
///
///  \return   uint32
///            = TRUE:  condition is valid
///            = FALSE: condition is not valid
///
///  \descr
///
// ---------------------------------------------------------------------------
STATIC_AL uint32 CddStp88XX_Transition_IdleMove(uint8 ucIx, const tCommandCddStp88XX eCmd)
{
 sint16  nActPos_;

 CDDSTP88XX_OptimizeArrayIndex(ucIx)

  (void)eCmd;

 // PRQA S 1863, 3415, 4558 3 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio7) Msg: 1863(The operands of this equality operator are of different 'essential signedness' but will both be promoted to 'signed int' for comparison.) Depth: 0 Ref: MISRA C:2012 Rule-10.4 | warning - QAC(Prio7) Msg: 4558(An expression of 'essentially unsigned' type (unsigned char) is being used as the right-hand operand of this logical operator (&&).) Depth: 0 Ref: MISRA C:2012 Rule-10.1 | warning - QAC(Prio7) Msg: 3415(Right hand operand of '&&' or '||' is an expression with possible side effects.) Depth: 0 Ref: MISRA C:2012 Rule-13.5; REFERENCE - ISO:C90-5,1,2,3 Program Execution
 nActPos_ = (sint16)CddStp88XX_HalStpFct[ucIx].pGetActPos(); // -> 'CddStp88XX_HalStpLwr_GetActPos' -> 'CddStp88XX_HalStpLwr_GetActPos_' -> 'CddStp88XX_HalStp_StpInfoLwr.lActPos'
 return          ((CddStp88XX_aStpState[ucIx].Bit.IsRef == 1u) // FLM3
  && (CddStp88XX_HalStpFct[ucIx].pIsFinishMove()) // -> 'CddStp88XX_HalStpLwr_IsFinishMove' -> 'CddStp88XX_HalStpLwr_IsStateHoldCont_' -> '(CddStp88XX_HalStp_eStateLwr == CddStp88XX_HalStp_eStateHoldCont) ? TRUE : FALSE;'
  && (CddStp88XX_aStpCtrl[ucIx].Bit.Ref == 0u)
  && (CddStp88XX_aStpCtrl[ucIx].Bit.Stop == 0u)
  && (nActPos_ != (sint16)CddStp88XX_aStpCtrl[ucIx].Val.nPos)
  && (CddStp88XX_aBitsMod[ucIx].Bit.biWaitStabilize == 0u)) ? 1u : 0u;
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_Transition_TestStep
///
///  \brief    ucIx transition function to StateTestStep
///
///  \param    uint8 ucIx
///            const tCommandCddStp88XX eCmd
///
///  \return   uint32
///            = TRUE:  condition is valid
///            = FALSE: condition is not valid
///
///  \descr
///
// ---------------------------------------------------------------------------
STATIC_AL uint32 CddStp88XX_Transition_TestStep(uint8 ucIx, const tCommandCddStp88XX eCmd)
{
 CDDSTP88XX_OptimizeArrayIndex(ucIx)

  (void)eCmd;

 return         ((CddStp88XX_HalStpFct[ucIx].pIsDriverReset() == FALSE)  // no DRV88XX specific driver reset?
  && (CddStp88XX_aBits[ucIx].Bit.biTestStepDone == 0u)       // no test steps if HalStp test steps are not done
  && (CddStp88XX_ucStateVolt == CDDSTP88XX_StateVoltNormal)  // test steps only if normal voltage                //! Afs2: test steps only in case of normal voltage
//!!              && (CddStp88XX_ucStateVolt != CDDSTP88XX_StateVoltOff)     // test steps over off voltage                      //! (not compatible to Afs2) !
&& (CddStp88XX_aStpState[0].Bit.SpiValid == 1u)            // SPI valid bit (driver is not in Sleep mode)?
) ? 1u : 0u;
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_Transition_TestStepIdle
///
///  \brief    ucIx transition function from StateTestStep to StateIdle
///
///  \param    uint8 ucIx
///            const tCommandCddStp88XX eCmd
///
///  \return   uint32
///            = TRUE:  condition is valid
///            = FALSE: condition is not valid
///
///  \descr
///
// ---------------------------------------------------------------------------
STATIC_AL uint32 CddStp88XX_Transition_TestStepIdle(uint8 ucIx, const tCommandCddStp88XX eCmd)
{
 CDDSTP88XX_OptimizeArrayIndex(ucIx)

  (void)eCmd;

 // PRQA S 4558 2 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio7) Msg: 4558(An expression of 'essentially unsigned' type (unsigned char) is being used as the left-hand operand of this logical operator (&&).) Depth: 0 Ref: MISRA C:2012 Rule-10.1
 return ((CddStp88XX_HalStpFct[ucIx].pIsTestStepDone())
  && (!((CddStp88XX_GetAttr(ucIx)->biUsePsens == 1u)                                      // Sref:
   && (CddStp88XX_aPsensInf[ucIx].Bit.StateErrAll.StateErr.biState == 0U /*LIT_SigWarn*/)))) ? 1u : 0u; //       Psens state not warning?
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_Transition_Err_Sub
///
///  \brief    ucIx sub function of TransitionErr to check DRV88XX status registers and handling error counter
///
///  \param    uint8 ucIx
///            const tCommandCddStp88XX eCmd
///            boolean boLessThanErrVoltHiLimit stored error voltage in HalStp error pin ISR 'StpIsrErrn_Lwr/Kl/Glw'
///
///  \return   uint32
///            = TRUE:  condition is valid
///            = FALSE: condition is not valid
///
///  \descr    - [Check] DRV88XX errors 'Therm, SC counter, OL counter'
///              include additional action if condition TRUE: set DEM 'ErrTherm, ErrElecSC, ErrElecOL' active
///
// ---------------------------------------------------------------------------
STATIC_AL uint32 CddStp88XX_Transition_Err_Sub(uint8 ucIx, const tCommandCddStp88XX eCmd, boolean boLessThanErrVoltHiLimit)
{
  uint32  ulReturn = (uint32)(FALSE);
  boolean boIsSCCntMax = FALSE;
  boolean boIsOLCntMax = FALSE;
  boolean boHigherThanErrVoltLoLimit         = (CddStp88XX_HalStpFct[ucIx].pGetErrVolt() >  ((uint32)Cod_StpSpannungLo1() * 100u)) ? TRUE : FALSE; // error voltage in specified range in case of ErrElecSC or ErrElecOL?
//boolean boLessThanErrVoltHiLimit           = (CddStp88XX_HalStpFct[ucIx].pGetErrVolt() <  (        Cod_StpSpannungHi1() * 100u)) ? TRUE : FALSE; // error voltage in specified range in case of ErrElecSC or ErrElecOL?
 boolean boHigherThanErrVoltHiLimitSCCntMax = (CddStp88XX_aucErrVoltHiLimitSCCnt[ucIx] >= CDDSTP88XX_ErrVoltHiLimitSCCntMax) ? TRUE : FALSE; // check to detect case of no pseudo SC error (ErrElecSC)

 CDDSTP88XX_OptimizeArrayIndex(ucIx)

  (void)eCmd;

 // update internal Data-Mirror ('CddStp8899_aSRegXXX') of necessary HW-Status-Registers ('CddStp8899Com_DataMirror.StatvRx.aSRegXXX')
 (void)CddStp8899Com_GetSRegFltDiag2(ucIx, &CddStp8899_aSRegFault[ucIx].ucRaw, &CddStp8899_aSRegDiag2[ucIx].ucRaw);
 /*jk-tbd - Not Needed Any Longer*/  // (void)CddStp8899Com_GetSReg3(ucIx, &CddStp8899_aSReg3[ucIx]);      // DRV88XX micro step position

 boIsSCCntMax = CddStp88XX_HalStpFct[ucIx].pIsSCCntMax();              // maximal value of overcurrent counter
 boIsOLCntMax = CddStp88XX_HalStpFct[ucIx].pIsOLCntMax();              // maximal value of openload counter

 // jk-tbd - No Driver-Reset for TI - CddStp88XX_HandleDriverReset(ucIx); // handle DRV88XX specific driver reset

 if ((CddStp8899_aSRegDiag2[ucIx].Bit.u1OTS != 0u)             // DRV88XX ('over') thermal shutdown error bit - i.e.: TSD detected?
  || (CddStp88XX_aStpState[ucIx].Bit.ErrDrvDefect == 1u)             // DRV88XX driver defect error bit (HalStp)
  || ((CddStp88XX_aStpCtrl[ucIx].Bit.ErrInh == 0u)
   && (CddStp88XX_aBits[ucIx].Bit.biWaitErrInh == 0u)
   && (boHigherThanErrVoltLoLimit != FALSE)          // error voltage in specified range in case of ErrElecSC or ErrElecOL?
   && ((boLessThanErrVoltHiLimit != FALSE)          // error voltage in specified range in case of ErrElecSC or ErrElecOL?
    || (boHigherThanErrVoltHiLimitSCCntMax != FALSE))         // TRUE in case of no pseudo SC error
   && ((boIsSCCntMax != FALSE)                                 // maximal value of overcurrent counter
    || (boIsOLCntMax != FALSE))))                              // maximal value of openload counter
 {
  if ((CddStp8899_aSRegDiag2[ucIx].Bit.u1OTS) != 0u)        // DRV88XX ('over') thermal shutdown error bit - i.e.: TSD detected?
  {
   if (CddStp88XX_aStpState[ucIx].Bit.ErrTherm == 0u) // jk: call DEM only once - jk-tbd
   {
    CddStp88XX_aStpState[ucIx].Bit.ErrTherm = 1u;
    //CddStp88XX_DemReportErrorStatus(ucIx, CddStp88XX_eDemEType_TempSD, DEM_EVENT_STATUS_FAILED); // thermal shutdown (OTS / ErrTherm)
    Rte_Call_DemPrj_ReportErrorStatus((uint16)StpV0_E_OVTEMP_OFF, DEM_EVENT_STATUS_FAILED); // set thermal shutdown DTC
   }
  }

  else if (CddStp88XX_aStpState[ucIx].Bit.ErrDrvDefect == 1u)          // DRV88XX driver defect error bit (HalStp)
  {
   if (CddStp88XX_aBitsMod[ucIx].Bit.biDemErrDrvDefect == 0u)
   {
    CddStp88XX_aBitsMod[ucIx].Bit.biDemErrDrvDefect = 1u;
    //CddStp88XX_DemReportErrorStatus(ucIx, CddStp88XX_eDemEType_Driver, DEM_EVENT_STATUS_FAILED);  // stepper driver defect (call from CAT1-ISR is not possible)
   }
  }

  else if (CddStp88XX_HalStpFct[ucIx].pIsSCCntMax() != FALSE)         // maximal value of overcurrent counter
//  else if ((CddStp8899_aSRegFault[ucIx].Bit.u1OCP) != 0) // DRV88XX overcurrent error bit
  {
   if (CddStp88XX_aStpState[ucIx].Bit.ErrElecSC == 0u)
   {
    CddStp88XX_aStpState[ucIx].Bit.ErrElecSC = 1u;
    //CddStp88XX_DemReportErrorStatus(ucIx, CddStp88XX_eDemEType_SC, DEM_EVENT_STATUS_FAILED); // Shortcut (pIsSCCntMax & ErrElecSC)
    Rte_Call_DemPrj_ReportErrorStatus((uint16)StpV0_E_SC, DEM_EVENT_STATUS_FAILED); // set short circuit dtc
   }
  }

  else if (CddStp88XX_HalStpFct[ucIx].pIsOLCntMax() != FALSE)                // maximal value of openload counter
  {
    if (CddStp88XX_aStpState[ucIx].Bit.ErrElecOL == 0u)
    {
      CddStp88XX_aStpState[ucIx].Bit.ErrElecOL = 1u;
      //CddStp88XX_DemReportErrorStatus(ucIx, CddStp88XX_eDemEType_OL,DEM_EVENT_STATUS_FAILED);
      Rte_Call_DemPrj_ReportErrorStatus((uint16)StpV0_E_OC, DEM_EVENT_STATUS_FAILED); // set open load DTC
    }
  }
  else
  {
   // no driver error 
  }

  ulReturn = (uint32)(TRUE);
 }

 // jk-tbd: MSP  Micro-Step-Position
 // jk-tbd: MSP  else if (   (   (((CddStp88XX_aunCReg4[ucIx] - CDDSTP8899_ResetVal_MSP) & CDDSTP8899_Mask_MSP) >> CDDSTP8899_MSP_1_4) 
 // jk-tbd: MSP               != (CddStp88XX_HalStpFct[ucIx].pGetPhaseCounter() & CDDSTP8899_Mask_PC))         // check microstep counter of DRV8899
 // jk-tbd: MSP           && (CddStp88XX_aeState[ucIx] == CddStp88XX_eStateIdle))                              // only in case of StateIdle (in entry action control register 4 CReg4 is read)
 // jk-tbd: MSP  else if (   ((CddStp8899_aSReg3[ucIx] & CDDSTP8899_Mask_MSP) != CddStp88XX_HalStpFct[ucIx].pGetPhaseCounter()) // check microstep counter of DRV88XX
 // jk-tbd: MSP           && (CddStp88XX_aeState[ucIx] == CddStp88XX_eStateIdle))                                                  // only in case of StateIdle (in entry action status register 3 is read)
 // jk-tbd: MSP  {
 // jk-tbd: MSP    if (CddStp88XX_aStpState[ucIx].Bit.ErrPos == 0u)
 // jk-tbd: MSP    {
 // jk-tbd: MSP      CddStp88XX_aStpState[ucIx].Bit.ErrPos = 1u; // state machine continues without error!
 // jk-tbd: MSP      CddStp88XX_DemReportErrorStatus(ucIx, CddStp88XX_eDemEType_Pos,DEM_EVENT_STATUS_FAILED);                      // position error
 // jk-tbd: MSP    }
 // jk-tbd: MSP    ulReturn = (uint32)(TRUE);
 // jk-tbd: MSP  }
 else
 {
  // suppress MISRA warning - QAC(Prio4) Msg: 2004(No concluding 'else' exists in this 'if'-'else'-'if' statement.) Depth: 0 Ref: MISRA-C:2004 Rule 14.10
 }

 return ulReturn;

 // PRQA S 5336, 5316 1 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio2) Msg: 5336(HIS metrics violation: 'CddStp88XX_HandlePensDesensPosMiddle() : STMIF = 6' exceeds threshold 4 for Number nesting of control structures (STMIF).) Depth: 0 Ref: 
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_Transition_Err
///
///  \brief    ucIx transition function to StateErr include error check
///
///  \param    uint8 ucIx
///            const tCommandCddStp88XX eCmd
///
///  \return   uint32
///            = TRUE:  condition is valid      (-> 'CddStp88XX_eStateErr')
///            = FALSE: condition is not valid
///
///  \descr    - Increment DRV88XX error counters 'SC counter, OL counter' and handle DRV88XX error clear bits
///            - [Check] DRV88XX errors 'Therm, SC counter, OL counter' (standard condition)
///              include additional action if condition TRUE: set DEM 'ErrTherm, ErrElecSC, ErrElecOL' active
///
// ---------------------------------------------------------------------------
STATIC_AL uint32 CddStp88XX_Transition_Err(uint8 ucIx, const tCommandCddStp88XX eCmd)
{
  boolean boHigherThanErrVoltLoLimit         = FALSE;
  boolean boLessThanErrVoltHiLimit           = FALSE;
  boolean boHigherThanErrVoltHiLimitSCCntMax = FALSE;
  boolean boIsErrnInactive                   = FALSE; // ERRN high

 CDDSTP88XX_OptimizeArrayIndex(ucIx)

  /////  __DI();            // call from interrupt level is not possible (no counter)!
  /////  osDisableGlobal(); // call from interrupt level is not possible (no counter)!
  //SuspendAllInterrupts(); // 

  boHigherThanErrVoltLoLimit = (CddStp88XX_HalStpFct[ucIx].pGetErrVolt() > ((uint32)Cod_StpSpannungLo1() * 100u)) ? TRUE : FALSE; // error voltage in specified range in case of ErrElecSC or ErrElecOL?
 boLessThanErrVoltHiLimit = (CddStp88XX_HalStpFct[ucIx].pGetErrVolt() < ((uint32)Cod_StpSpannungHi1() * 100u)) ? TRUE : FALSE; // error voltage in specified range in case of ErrElecSC or ErrElecOL?
 boHigherThanErrVoltHiLimitSCCntMax = (CddStp88XX_aucErrVoltHiLimitSCCnt[ucIx] >= CDDSTP88XX_ErrVoltHiLimitSCCntMax) ? TRUE : FALSE; // check to detect case of no pseudo SC error (ErrElecSC)

 // ensure actual status register values if ERRN is low
 if (ucIx == 0u)                                                             // LWR stepper driver?
 {
  // jk-tbd: N.b.: 'IoHwAb_User_GetDio_ERRN_LWR' is currently ALWAYS '0'   (...'CddStp_boDioErrLwr')
  (void)IoHwAb_User_GetDio_ERRN_LWR(&boIsErrnInactive);                     // LWR ERRN high
 }
 else
 {
  // suppress MISRA warning - QAC(Prio4) Msg: 2004(No concluding 'else' exists in this 'if'-'else'-'if' statement.) Depth: 0 Ref: MISRA-C:2004 Rule 14.10
 }

 if (boIsErrnInactive == FALSE)                                              // ERRN low? - in case of change of DRV88XX warning or error reason and new status register values are not read because of SPI communication delay of CddSpi
 {
  // keine CddStp88XX_HalStpLwr_SendSRegX()-Funktionen, da sowieso immer alle StatusRegister gelesen werden
  // (void)CddStp88XX_HalStpFct[ucIx].pSpiSendSRegAll();                    // read all the status registers to update if other bits are set

  //! (void)CddStp8899Com_StartRxNotificationSr12367A8A(ucIx);                 // synchronize the sending of SPI commands to read all status registers with the reading of the results after all three values are received
  //! CddStp88XX_aBits[ucIx].Bit.biTransitionErrDone = 0;                      // not: check of error bits is done in CddStp88XX_Transition_Err() - used in CddStp88XX_HalStpVer/Hor/Sht_ErrnCb() and in CddStp88XX_Transition_Err()
 }

 // jk - currently not used: // update internal Data-Mirror ('CddStp8899_aSRegXXX') of necessary HW-Status-Registers ('CddStp8899Com_DataMirror.StatvRx.aSRegXXX')
 // jk - currently not used: (void)CddStp8899Com_GetSRegBscFltDiag12(ucIx, &CddStp8899_aSRegBasic[ucIx].ucRaw
 // jk - currently not used:                                             , &CddStp8899_aSRegFault[ucIx].ucRaw
 // jk - currently not used:                                             , &CddStp8899_aSRegDiag1[ucIx].ucRaw
 // jk - currently not used:                                             , &CddStp8899_aSRegDiag2[ucIx].ucRaw);

 if ((CddStp88XX_aStpCtrl[ucIx].Bit.ErrInh == 0u)             // (Inhibit driver errors and step loss)
  && (CddStp88XX_aBits[ucIx].Bit.biWaitErrInh == 0u)          // (to avoid range overflow in timeout polling) (wait because of soon Motor-Start)(currently NOT used)
  && (boHigherThanErrVoltLoLimit != FALSE)                    // error voltage in specified range in case of ErrElecSC or ErrElecOL?
  && ((boLessThanErrVoltHiLimit != FALSE)                  // error voltage in specified range in case of ErrElecSC or ErrElecOL?
   || (boHigherThanErrVoltHiLimitSCCntMax != FALSE)))      // TRUE in case of no pseudo SC error
 {
#ifdef JK_TBD
  /*jk-tbd*/ if (0); // 
#endif
// jk-tbd    if (   (CddStp8899Com_CheckRxNotificationSr12367A8A(ucI) != FALSE)       // in case of DRV88XX-ERRN-ISR the read status register RX content is started - therefore wait till all registers are read (in all other cases the result is always FALSE)
// jk-tbd        && (CddStp88XX_aBits[ucIx].Bit.biTransitionErrDone == 0u))            // check of error bits is not(!) done in CddStp88XX_Transition_Err() - used in CddStp88XX_HalStpVer/Hor/Sht_ErrnCb() and in CddStp88XX_Transition_Err()
// jk-tbd    {
// jk-tbd      CddStp88XX_aBits[ucIx].Bit.biTransitionErrDone = 1u;                    // check of error bits is done in CddStp88XX_Transition_Err() - used in CddStp88XX_HalStpVer/Hor/Sht_ErrnCb() and in CddStp88XX_Transition_Err()
// jk-tbd

  if (CddStp88XX_aBitsMod[ucIx].Bit.biDisOLDetect == 0u)                  // DRV88XX: OL detection is disabled? - Note: if counter is not cleared, the result is independent from OL counter incrementation
  {
   if (CddStp88XX_HalStpFct[ucIx].pIncOLCnt() != FALSE)                  // openload error bit set?  (-> 'CddStp88XX_HalStpLwr_IncOLCnt' -> 'CddStp88XX_HalStpLwr_IncOLCnt_' -> '...CddStp88XX_HalStp_ucOLCntLwr')
   {
    //  keine CddStp88XX_HalStpLwr_SendSRegX()-Funktionen, da sowieso immer alle StatusRegister gelesen werden
    // (void)CddStp88XX_HalStpFct[ucIx].pSpiSendSRegAll();              // read all the status registers to clear the error bit - once more!

    /*jk-tbd - Not Needed Any Longer?!?!*/ // (void)CddStp8899Com_StartRxNotificationSr12367A8A(ucIx);           // synchronize the sending of SPI commands to read all status registers with the reading of the results after all three values are received
    // jk-tbd CddStp88XX_aBits[ucIx].Bit.biTransitionErrDone = 0;                 // not: check of error bits is done in CddStp88XX_Transition_Err() - used in CddStp88XX_HalStpVer/Hor/Sht_ErrnCb() and in CddStp88XX_Transition_Err()
     if ((CddStp88XX_aBits[ucIx].Bit.biTestStepDone == 1u) && (CddStp88XX_aBits[ucIx].Bit.biRetryTestStepDone == 0u))
     {
       // do another test step for validating the OL error
       CddStp88XX_aBits[ucIx].Bit.biTestStepDone = 0u;
       CddStp88XX_HalStpFct[ucIx].pResetTestStepCnt();
       CddStp_SetOLIgnore(TRUE);
       CddStp88XX_aBits[ucIx].Bit.biDoRetryTestStep = 1u;
     }
    CddStp88XX_HandleResetErrVolt(ucIx, FALSE);                         // error is checked, therefore reset error voltage but do not clear the SC and OL bits of status registers that the state functions are able to react
   }
  }

  else // i.e.: 'CddStp88XX_aBitsMod[ucIx].Bit.biDisOLDetect' == TRUE  -> OL-Detection IS DISABLED (due to 'move' or 'ref')
  {
   // jk-tbd keine CddStp88XX_HalStpLwr_SendSRegX()-Funktionen, da sowieso immer alle StatusRegister gelesen werden
   // jk-tbd (void)CddStp88XX_HalStpFct[ucIx].pSpiSendSRegAll();               // read all the status registers to clear the error bit - once more!

//!     (void)CddStp8899Com_StartRxNotificationSr12367A8A(ucIx);             // synchronize the sending of SPI commands to read all status registers with the reading of the results after all three values are received
//!     CddStp88XX_aBits[ucIx].Bit.biTransitionErrDone = 0;                  // not: check of error bits is done in CddStp88XX_Transition_Err() - used in CddStp88XX_HalStpVer/Hor/Sht_ErrnCb() and in CddStp88XX_Transition_Err()

   CddStp88XX_HalStpFct[ucIx].pClrOLCnt();                              // clear the openload counter
  }

  if (CddStp88XX_HalStpFct[ucIx].pIncSCCnt() != FALSE)                   // overcurrent error bit set?
  {
   // jk-tbd  keine CddStp88XX_HalStpLwr_SendSRegX()-Funktionen, da sowieso immer alle StatusRegister gelesen werden
   // jk-tbd (void)CddStp88XX_HalStpFct[ucIx].pSpiSendSRegAll();               // read all the status registers to clear the error bit - once more!

   // jk-tbd (void)CddStp8899Com_StartRxNotificationSr12367A8A(ucIx);             // synchronize the sending of SPI commands to read all status registers with the reading of the results after all three values are received
   // jk-tbd CddStp88XX_aBits[ucIx].Bit.biTransitionErrDone = 0;                  // not: check of error bits is done in CddStp88XX_Transition_Err() - used in CddStp88XX_HalStpVer/Hor/Sht_ErrnCb() and in CddStp88XX_Transition_Err()

   CddStp88XX_HandleResetErrVolt(ucIx, FALSE);                          // error is checked, therefore reset error voltage but do not clear the SC and OL bits of status registers that the state functions are able to react
  }
  //CddStp88XX_DemReportErrorStatus(ucIx, CddStp88XX_eDemEType_OL, DEM_EVENT_STATUS_PASSED);
  //CddStp88XX_DemReportErrorStatus(ucIx, CddStp88XX_eDemEType_SC, DEM_EVENT_STATUS_PASSED);
  Rte_Call_DemPrj_ReportErrorStatus((uint16)StpV0_E_SC, DEM_EVENT_STATUS_PASSED); // reset short circuit DTC
  Rte_Call_DemPrj_ReportErrorStatus((uint16)StpV0_E_OC, DEM_EVENT_STATUS_PASSED); // reset open load DTC
// jk-tbd    }
 }

 else // voltages are some kind of bad / out-of-range
 {
  //A CddStp88XX_DemReportErrorStatus(ucIx, CddStp88XX_eDemEType_Pos,ERRLOG_NoDetecting);

      // jk-tbd  keine CddStp88XX_HalStpLwr_SendSRegX()-Funktionen, da sowieso immer alle StatusRegister gelesen werden
      // jk-tbd (void)CddStp88XX_HalStpFct[ucIx].pSpiSendSRegAll();                   // read all the status registers to clear the error bit - once more!

  //! (void)CddStp8899Com_StartRxNotificationSr12367A8A(ucIx);                 // synchronize the sending of SPI commands to read all status registers with the reading of the results after all three values are received
  //! CddStp88XX_aBits[ucIx].Bit.biTransitionErrDone = 0;                      // not: check of error bits is done in CddStp88XX_Transition_Err() - used in CddStp88XX_HalStpVer/Hor/Sht_ErrnCb() and in CddStp88XX_Transition_Err()

  CddStp88XX_HandleResetErrVolt(ucIx, FALSE);                              // error is checked, therefore reset error voltage but do not clear the SC and OL bits of status registers that the state functions are able to react
 }

 /////  __EI();           // call from interrupt level is not possible (no counter)!
 /////  osEnableGlobal(); // call from interrupt level is not possible (no counter)!
 //ResumeAllInterrupts(); // 

 return (CddStp88XX_Transition_Err_Sub(ucIx, eCmd, boLessThanErrVoltHiLimit));
 // PRQA S 5310 1 // 
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_Transition_OffStby
///
///  \brief    ucIx transition function from StateOff to StateStby
///
///  \param    uint8 ucIx
///            const tCommandCddStp88XX eCmd
///
///  \return   uint32
///            = TRUE:  condition is valid
///            = FALSE: condition is not valid
///
///  \descr    DRV88XX undervoltage or overvoltage bits
///
// ---------------------------------------------------------------------------
STATIC_AL uint32 CddStp88XX_Transition_OffStby(uint8 ucIx, const tCommandCddStp88XX eCmd)
{
 CDDSTP88XX_OptimizeArrayIndex(ucIx)

  (void)eCmd;

 // update internal Data-Mirror ('CddStp8899_aSRegXXX') of necessary HW-Status-Registers ('CddStp8899Com_DataMirror.StatvRx.aSRegXXX')
 (void)CddStp8899Com_GetSRegBscFltDiag12(ucIx, &CddStp8899_aSRegBasic[ucIx].ucRaw
  , &CddStp8899_aSRegFault[ucIx].ucRaw
  , &CddStp8899_aSRegDiag1[ucIx].ucRaw
  , &CddStp8899_aSRegDiag2[ucIx].ucRaw);

 return  ((CddStp88XX_HalStpFct[ucIx].pIsDriverReset() == FALSE)             // no DRV88XX specific driver reset?
  && ((CddStp88XX_ucStateVolt == CDDSTP88XX_StateVoltOver)           // overvoltage?
   || (CddStp88XX_ucStateVolt == CDDSTP88XX_StateVoltUnder))         // undervoltage?
  && (CddStp8899_aSRegFault[ucIx].Bit.u1UVLO == 0u)                // no undervoltage error DRV88XX?
  && (CddStp88XX_aBitsMod[ucIx].Bit.biWaitVoltage == 0u)                // debounce of in case of voltage out of range change ready?
  && (CddStp88XX_aBits[ucIx].Bit.biTestStepDone == 1u)                // HalStp test steps are done?
  && (CddStp88XX_aStpState[0].Bit.SpiValid == 1u)               // SPI valid bit (driver is not in Sleep mode)?
  ) ? 1u : 0u;
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_Transition_OffIdle
///
///  \brief    ucIx transition function from StateOff to StateIdle
///
///  \param    uint8 ucIx
///            const tCommandCddStp88XX eCmd
///
///  \return   uint32
///            = TRUE:  condition is valid
///            = FALSE: condition is not valid
///
///  \descr    - No SysVolt undervoltage or overvoltage states and no DRV88XX undervoltage or overvoltage bits and timeout finished
///              include additional action if condition TRUE: set DEM 'ErrTherm, ErrElecSC, ErrElecOL' absent
///
// ---------------------------------------------------------------------------
STATIC_AL uint32 CddStp88XX_Transition_OffIdle(uint8 ucIx, const tCommandCddStp88XX eCmd)
{
 uint32  ulReturn = (uint32)(FALSE);
 // jk-obsolet: currently not used    boolean boRxNotificationCr134A67;

 CDDSTP88XX_OptimizeArrayIndex(ucIx)

  (void)eCmd;

#ifdef JK_TBD
 /*jk-tbd*/ if (0); // boRxNotificationCr134A67 = CddStp8899Com_CheckRxNotificationCr134A67(ucIx);  // in case of ActEntry and ActD0 in OffState the write control register RX content is started - therefore wait till all registers are read (verify OK)
#endif

  // update internal Data-Mirror ('CddStp8899_aSRegXXX') of necessary HW-Status-Registers ('CddStp8899Com_DataMirror.StatvRx.aSRegXXX')
 (void)CddStp8899Com_GetSRegBscFltDiag12(ucIx, &CddStp8899_aSRegBasic[ucIx].ucRaw
  , &CddStp8899_aSRegFault[ucIx].ucRaw
  , &CddStp8899_aSRegDiag1[ucIx].ucRaw
  , &CddStp8899_aSRegDiag2[ucIx].ucRaw);

 CddStp88XX_HandleWaitVoltage(ucIx);                                                 // get wait in case of voltage out of range change flag to check below

 if ((CddStp88XX_HalStpFct[ucIx].pIsDriverReset() == FALSE)                       // no DRV88XX specific driver reset?
// jk-tbd && (boRxNotificationCr134A67 != FALSE)                                      // in case of ActEntry and ActD0 in OffState the write control register RX content is started - therefore wait till all control registers are written
&& (CddStp88XX_ucStateVolt == CDDSTP88XX_StateVoltNormal)                       // normal voltage?
&& (CddStp8899_aSRegFault[ucIx].Bit.u1UVLO == 0u)                          // no undervoltage error DRV88XX?
&& (CddStp88XX_aBitsMod[ucIx].Bit.biWaitVoltage == 0u)                          // debounce of in case of voltage out of range change ready?
&& (CddStp88XX_aBits[ucIx].Bit.biTestStepDone == 1u)                          // HalStp test steps are done?
&& (!((CddStp88XX_GetAttr(ucIx)->biUsePsens == 1u)                          // Sref:
 && (CddStp88XX_aPsensInf[ucIx].Bit.StateErrAll.StateErr.biState == 0U/*LIT_SigWarn*/) //       Psens state not warning?
 && (CddStp88XX_aStpState[0].Bit.SpiValid == 1u))))                              // SPI valid bit (driver is not in Sleep mode)?
 {
  //CddStp88XX_DemReportErrorStatus(ucIx, CddStp88XX_eDemEType_OL,     DEM_EVENT_STATUS_PASSED);
  //CddStp88XX_DemReportErrorStatus(ucIx, CddStp88XX_eDemEType_SC,     DEM_EVENT_STATUS_PASSED);
  //CddStp88XX_DemReportErrorStatus(ucIx, CddStp88XX_eDemEType_TempSD, DEM_EVENT_STATUS_PASSED);
  Rte_Call_DemPrj_ReportErrorStatus((uint16)StpV0_E_SC        , DEM_EVENT_STATUS_PASSED); // reset short circuit DTC
  Rte_Call_DemPrj_ReportErrorStatus((uint16)StpV0_E_OC        , DEM_EVENT_STATUS_PASSED); // reset open load DTC
  Rte_Call_DemPrj_ReportErrorStatus((uint16)StpV0_E_OVTEMP_OFF, DEM_EVENT_STATUS_PASSED); // reset thermal shutdown DTC

  ulReturn = (uint32)(TRUE);
 }

 return ulReturn;
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_Transition_ErrClr
///
///  \brief    ucIx transition function to leave StateErr by clearing StpCtrl bit 'ErrClr'
///
///  \param    uint8 ucIx
///            const tCommandCddStp88XX eCmd
///
///  \return   uint32
///            = TRUE:  condition is valid
///            = FALSE: condition is not valid
///
///  \descr
///
// ---------------------------------------------------------------------------
STATIC_AL uint32 CddStp88XX_Transition_ErrClr(uint8 ucIx, const tCommandCddStp88XX eCmd)
{
 CDDSTP88XX_OptimizeArrayIndex(ucIx)

  (void)eCmd;

 return ((CddStp88XX_aStpCtrlOld[ucIx].Bit.ErrClr == 0u) // positive slope?
  && (CddStp88XX_aStpCtrl[ucIx].Bit.ErrClr == 1u)) ? 1u : 0u;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// StateMachine state functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_StateFct_Init
///
///  \brief    ucIx Init state function to handle state CddStp88XX_eStateInit
///
///  \param    uint8 ucIx
///            tAction Action
///
///  \return   none
///
///  \descr    This state switches off stepper motor and is possible more times in one PowerOn cycle (not compatible to Afs2)
///
// ---------------------------------------------------------------------------
STATIC_AL void CddStp88XX_StateFct_Init(uint8 ucIx, tAction Action)
{
 //static boolean boIdleStateHctActEntry = FALSE; //------------------------------------------------------ !the case ActEntry is never called because of zero initialisation of variables! -> This is OK (in other case the StpOnTime is wrong)!!!

 switch (Action)
 {
  // ~~~~~ Action-Entry ~~~~~
 case ActEntry: // perform entry action -------------------------------------------------------------- !the case ActEntry is never called because of zero initialisation of variables! -> This is OK (in other case the StpOnTime is wrong)!!!
//  case ActDo:    // perform do activity  -------------------------------------------------------------- !the case ActEntry is never called because of zero initialisation of variables! -> This is OK (in other case the StpOnTime is wrong)!!!
//  if (boIdleStateHctActEntry == FALSE)  // case ActEntry // perform entry action ---------------------- !the case ActEntry is never called because of zero initialisation of variables! -> This is OK (in other case the StpOnTime is wrong)!!!
 {
  //    boIdleStateHctActEntry = TRUE; //------------------------------------------------------------------ !the case ActEntry is never called because of zero initialisation of variables! -> This is OK (in other case the StpOnTime is wrong)!!!

  CddStp88XX_HandleStpOnTime(ucIx, FALSE); //------------------------------------------------------- !the case ActEntry is never called because of zero initialisation of variables! -> This is OK (in other case the StpOnTime is wrong)!!!

  CddStp88XX_DeInit(ucIx);
  CddStp88XX_Volt(CddStp88XXVolt_GetStpVoltState());      // simulate stepper Volt event to leave initial stepper Volt state  CddStp88XX_ucStateVolt = CDDSTP88XX_StateVoltOff

  CddStp88XX_SetStpStateBitIsReady(ucIx); // CddStp88XX_aStpState[ucIx].Bit.IsReady = 1u;
  CddStp88XX_aStpState[ucIx].Bit.InitActive = 1u;

  CddStp88XX_aBitsMod[ucIx].Bit.biWaitStabilize = 0;

  //  keine CddStp88XX_HalStpLwr_SendSRegX()-Funktionen, da sowieso immer alle StatusRegister gelesen werden
  // (void)CddStp88XX_HalStpFct[ucIx].pSpiSendSRegAll();      // read all the status registers: no pending error stored in DRV88XX (p.e. after under voltage pseudo errors of previous moving cycle)
  /*jk-tbd - Not Needed Any Longer*/ // (void)CddStp8899Com_StartRxNotificationSr12367A8A(ucIx); // synchronize the sending of SPI commands to read status registers 1, 2, 3, 6, 7A, 8A with the reading of the results after all three values are received
  CddStp88XX_aBits[ucIx].Bit.biTransitionErrDone = 0;      // not: check of error bits is done in CddStp88XX_Transition_Err() - used in CddStp88XX_HalStpVer/Hor/Sht_ErrnCb() and in CddStp88XX_Transition_Err()
  break;
 }


 // ~~~~~ Action-Do ~~~~~
 case ActDo:              // perform do activity
                          //  else                                  // case ActDo    // perform do activity ----------------------- !the case ActEntry is never called because of zero initialisation of variables! -> This is OK (in other case the StpOnTime is wrong)!!!
 {
  //  keine CddStp88XX_HalStpLwr_SendSRegX()-Funktionen, da sowieso immer alle StatusRegister gelesen werden
  // (void)CddStp88XX_HalStpFct[ucIx].pSpiSendSRegAll();      // read all the status registers: no pending error stored in DRV88XX (p.e. after under voltage pseudo errors of previous moving cycle)
  /*jk-tbd - Not Needed Any Longer*/ // (void)CddStp8899Com_StartRxNotificationSr12367A8A(ucIx); // synchronize the sending of SPI commands to read all status registers with the reading of the results after all three values are received
  CddStp88XX_aBits[ucIx].Bit.biTransitionErrDone = 0;      // not: check of error bits is done in CddStp88XX_Transition_Err() - used in CddStp88XX_HalStpVer/Hor/Sht_ErrnCb() and in CddStp88XX_Transition_Err()
  break;
 }


 // ~~~~~ Action-Exit ~~~~~
 case ActExit:              // perform exit action // used because this state is first state of state machine (init)
 {
#if(CFA_CNT_STP_ONBRD == 2)
  sint32 lSchrittMod = (ucIx == CFG_Stp_IdxVer) ? (sint32)Cod_LwrSchrittMod() : (sint32)Cod_AhlSchrittMod();
#else
  sint32 lSchrittMod = (sint32)Cod_LwrSchrittMod();
#endif

  CddStp88XX_Init_(ucIx);    // reset all variables - by clearing also CddStp88XX_aBitsMod[ucIx] also biLockLT = 0 - this unlocks the low temperature state in this power on cycle (not compatible to Afs2) - not cleared is CddStp88XX_aBits[ucIx] biLT!
  CddStp88XX_Volt(CddStp88XXVolt_GetStpVoltState());      // simulate stepper Volt event to leave initial stepper Volt state  CddStp88XX_ucStateVolt = CDDSTP88XX_StateVoltOff

  (void)CddStp88XX_HalStpFct[ucIx].pInit(TRUE);            // init HalStp instance                             // instead of in CddStp88XX_Init() - because of dynamical use of InitState (not compatible to Afs2)
  (void)CddStp88XX_HalStpFct[ucIx].pSetHsMode(((lSchrittMod == (sint32)NvmPara_eSchrittMod2) ? TRUE : FALSE),                  // instead of in CddStp88XX_Init() - because of dynamical use of InitState (not compatible to Afs2)
   CddStp88XX_aucCurAmpltRunTemp[ucIx][CddStp88XX_aeTemp[ucIx]]);
  break;
 }

 default:         // switch of enum variable: against MISRA warning - QAC(Prio2) Msg: 2018(This switch default label is unreachable.) Depth: 0 Ref: 
 {
  // This is not a valid action, must be an error.
  // Assert(....);
  break;
 }
 }
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_StateFct_Off
///
///  \brief    ucIx Off state function to handle state CddStp88XX_eStateOff
///
///  \param    uint8 ucIx
///            tAction Action
///
///  \return   none
///
///  \descr
///
// ---------------------------------------------------------------------------
STATIC_AL void CddStp88XX_StateFct_Off(uint8 ucIx, tAction Action)
{
 CDDSTP88XX_OptimizeArrayIndex(ucIx)

  switch (Action)
  {
   // ~~~~~ Action-Entry ~~~~~
  case ActEntry:              // perform entry action
  {
   CddStp88XX_HandleStpOnTime(ucIx, FALSE);

   CddStp88XX_StartWait88XXVoltage(ucIx);

   CddStp88XX_HalStpFct[ucIx].pStopStp(FALSE); // stop HalStp state machine if DRV88XX has not stopped (Openload, ...) and motor is enabled

   CddStpDyn_Init(ucIx, CddStp88XX_HalStpFct[ucIx].pGetHsMode());

   CddStp88XX_HalStpFct[ucIx].pHandleMotEn(FALSE, TRUE);     // disable stepper motor driver, send SPI commands
   /*jk-tbd - Not Needed Any Longer*/ // (void)CddStp8899Com_StartRxNotificationCr134A67(ucIx);    // synchronize the sending of SPI commands to write control registers 1, 2 with the reading of the results after all two values are received (verify OK)

   CddStp88XX_aStpState[ucIx].Bit.ErrElecSC = 0;
   CddStp88XX_aStpState[ucIx].Bit.ErrElecOL = 0;
   CddStp88XX_aStpState[ucIx].Bit.ErrTherm  = 0;
   //    CddStp88XX_aStpState[ucIx].Bit.ErrPos           = 0;
   //!   CddStp88XX_aStpState[ucIx].Bit.ErrPrealarm      = 0;      // overtemperature warning: after prealarm configuration time
   //!   CddStp88XX_aStpState[ucIx].Bit.Timeout          = 0;
   CddStp88XX_aStpState[ucIx].Bit.ErrDrvDefect = 0;
   CddStp88XX_aBitsMod[ucIx].Bit.biDemErrDrvDefect = 0;
   //    CddStp88XX_aStpState[ucIx].Bit.ErrPsens         = 0;

   //    CddStp88XX_aStpState[ucIx].Bit.StepLoss         = ...;    // see CddStp88XX_Transition_MoveOff()
   //    CddStp88XX_aStpState[ucIx].Bit.Prealarm         = 0;      // see CddStp88XX_HandleStp() // overtemperature warning: raw driver bit

   //    CddStp88XX_aStpState[ucIx].Bit.VoltNorm         = 0;      // see CddStp88XX_Volt()
   //    CddStp88XX_aStpState[ucIx].Bit.VoltOver         = 1u;      // see one of CddStp88XX_Transition_...Off() - include increment NVM counter
   //    CddStp88XX_aStpState[ucIx].Bit.VoltUSSM         = 0;      // see CddStp88XX_Volt()
   CddStp88XX_aStpState[ucIx].Bit.Reduced = 0;

   if (CddStp88XX_GetAttr(ucIx)->biUsePsens == 1u) // Sref
   {
    CddStp88XX_aStpState[ucIx].Bit.IsInside = CddStp88XX_aPsensInf[ucIx].Bit.biIsPositive;  // logical polarity
   }
   else                                            // Href
   {
    CddStp88XX_aStpState[ucIx].Bit.IsInside = 0;
   }
   //    CddStp88XX_aStpState[ucIx].Bit.IsRef            = ...;    // see CddStp88XX_HandleStepLoss() called by CddStp88XX_Transition_MoveOff()
   //    CddStp88XX_aStpState[ucIx].Bit.FullRef          = ...;    // see CddStp88XX_HandleStepLoss() called by CddStp88XX_Transition_MoveOff()

   CddStp88XX_aStpState[ucIx].Bit.IsReady = 0;
   CddStp88XX_aStpState[ucIx].Bit.IsMoving = 0;
   CddStp88XX_aStpState[ucIx].Bit.RefActive = 0;

   CddStp88XX_aBitsMod[ucIx].Bit.biTransOff = 0;

   if (CddStp88XX_GetAttr(ucIx)->biUsePsens == 1u) // Sref
   {
    CddStp88XX_aBitsMod[ucIx].Bit.biSlopePosInvalid = 0;
   }

   CddStp88XX_aBitsMod[ucIx].Bit.biWaitStabilize = 0;

   //A   CddStp88XX_DemReportErrorStatus(ucIx, CddStp88XX_eDemEType_OL,     ERRLOG_NoDetecting);
   //A   CddStp88XX_DemReportErrorStatus(ucIx, CddStp88XX_eDemEType_SC,     ERRLOG_NoDetecting);
   //A   CddStp88XX_DemReportErrorStatus(ucIx, CddStp88XX_eDemEType_TempSD, ERRLOG_NoDetecting);
   //A   CddStp88XX_DemReportErrorStatus(ucIx, CddStp88XX_eDemEType_Pos,    ERRLOG_NoDetecting);

   // jk-obsolet CddStp88XX_aunCorrValueAbs[ucIx] = 0; // if (CddStp88XX_GetAttr(ucIx)->biUsePsens == 1u) // Sref: clear position correction value to avoid steps if setting position in StpCtrl has changed while voltage is not normal and then is normal again
   break;
  }


  // ~~~~~ Action-Do ~~~~~
  case ActDo:              // perform do activity
  {
   boolean boIsErrnInactive = FALSE;                                                                             // ERRN high

   if (ucIx == 0u)                                                                                                // LWR stepper driver?
   {
    // jk-tbd: N.b.: 'IoHwAb_User_GetDio_ERRN_LWR' is currently ALWAYS '0'   (...'CddStp_boDioErrLwr')
        (void)IoHwAb_User_GetDio_ERRN_LWR(&boIsErrnInactive);                                                       // LWR ERRN high
   }
   else if (ucIx == 1u)                                                                                           // AHL stepper driver?
   {
#if(CFA_CNT_STP_ONBRD == 2)
    (void)IoHwAb_User_GetDio_ERRN_AHL(&boIsErrnInactive);                                                       // AHL ERRN high
#endif
   }
   else
   {
    // suppress MISRA warning - QAC(Prio4) Msg: 2004(No concluding 'else' exists in this 'if'-'else'-'if' statement.) Depth: 0 Ref: MISRA-C:2004 Rule 14.10
   }

   // update internal Data-Mirror ('CddStp8899_aSRegXXX') of necessary HW-Status-Registers ('CddStp8899Com_DataMirror.StatvRx.aSRegXXX')
   (void)CddStp8899Com_GetSRegBscFltDiag12(ucIx, &CddStp8899_aSRegBasic[ucIx].ucRaw
    , &CddStp8899_aSRegFault[ucIx].ucRaw
    , &CddStp8899_aSRegDiag1[ucIx].ucRaw
    , &CddStp8899_aSRegDiag2[ucIx].ucRaw);

   CddStp88XX_aBitsMod[ucIx].Bit.biDisOLDetect = 0;                                                             // OL detection is enabled
   CddStp88XX_HalStpFct[ucIx].pHandleMotEn(FALSE, TRUE);                                                        // disable stepper motor driver (sometimes also send value by CddStp88XX_HalStpFct[ucIx].pSpiSendSRegAll(), see below)

   // jk-tbd - No Driver-Reset for TI - CddStp88XX_HandleDriverReset(ucIx);                                                                          // handle DRV88XX specific driver reset

   (void)CddStp88XX_HalStpFct[ucIx].pSpiSendCRegAll();                                                          // write all the control registers to ensure actual values

   // PRQA S 4558 2 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio7) Msg: 4558(An expression of 'essentially unsigned' type (unsigned char) is being used as the left-hand operand of this logical operator (&&).) Depth: 0 Ref: MISRA C:2012 Rule-10.1
   if ((CddStp88XX_HalStpFct[ucIx].pIsDriverReset())                                                         // DRV88XX specific driver reset?
    || ((boIsErrnInactive == FALSE) ? TRUE : FALSE)                                                          // ERRN low? - in case of change of DRV88XX warning or error reason while this state the new status register values are required!
    || (CddStp8899_aSRegFault[ucIx].Bit.u1UVLO != 0u)                      // DRV88XX UV3 warning error bit
    || (   /*(!CddStp88XX_aBits[ucIx].Bit.biTestStepDone)                                                    // exception after transition from Init state: no change to Standby state in case of under or over voltage if TestStep is not done
        && */(((CddStp8899_aSRegDiag2[ucIx].Bit.u1OTS) != 0u)                      // DRV88XX ('over') thermal shutdown error bit - i.e.: TSD detected?
 || ((CddStp8899_aSRegDiag2[ucIx].Bit.u1OTW) != 0u)                      // DRV88XX thermal warning error bit
//                || ((CddStp8899_aSRegDiag2[ucIx].ucRaw & CDDSTP8899_old_Mask_UV3)    != 0u)                      // DRV88XX UV3 warning error bit
|| ((CddStp8899_aSRegFault[ucIx].Bit.u1OCP) != 0u)
|| ((CddStp8899_aSRegFault[ucIx].Bit.u1OL) != 0u))))   // do not use (CddStp88XX_HalStpFct[ucIx].pIsSCCntMax()) maximal value of overcurrent counter because Standby does not call CddStp88XX_Transition_Err()!
   { // do not retry to enable driver by reading the register in case of SC, SH, OL, TW and TSD.
     //  keine CddStp88XX_HalStpLwr_SendSRegX()-Funktionen, da sowieso immer alle StatusRegister gelesen werden
     // (void)CddStp88XX_HalStpFct[ucIx].pSpiSendSRegAll();                                                        // read all the status registers to clear the error bit
     /*jk-tbd - Not Needed Any Longer*/ // (void)CddStp8899Com_StartRxNotificationSr12367A8A(ucIx);                                                   // synchronize the sending of SPI commands to read all status registers with the reading of the results after all three values are received
    CddStp88XX_aBits[ucIx].Bit.biTransitionErrDone = 0;                                                        // not: check of error bits is done in CddStp88XX_Transition_Err() - used in CddStp88XX_HalStpVer/Hor/Sht_ErrnCb() and in CddStp88XX_Transition_Err()
   }

   (void)IoHwAb_User_GetAdc_DIAG_VBAT(&CddStp88XX_unDIAG_VBAT);
   CddStp88XX_aStpState[ucIx].Bit.Reduced = CddStpDyn_SetFreq(ucIx, CddStp88XX_aunTgtTmin[ucIx], CddStp88XX_unDIAG_VBAT);
   break;
  }


  // ~~~~~ Action-Exit ~~~~~
  case ActExit:              // perform exit action // used because this state is first state of state machine (init)
  {
   if (CddStp88XX_ucStateVolt == CDDSTP88XX_StateVoltNormal)        // normal voltage?
   {
    //-     CddStp88XX_HalStpFct[ucIx].pHandleCurAmplt(CDDSTP88XX_eCurAmpltStateNoChange, /*CddStp88XX_aucCurAmpltHoldTemp*/CddStp88XX_aucCurAmpltRunTemp[ucIx][CddStp88XX_aeTemp[ucIx]], CDDSTP88XX_eCurAmpltNoChange); // increase hold current to actual normal (run) amplitude to stabilize the stepper rotor
    CddStp88XX_HalStpFct[ucIx].pHandleCurAmplt((uint8)CDDSTP88XX_eCurAmpltStateHold
     ,     /*CddStp88XX_aucCurAmpltHoldTemp*/CddStp88XX_aucCurAmpltRunTemp[ucIx][CddStp88XX_aeTemp[ucIx]]
     , CDDSTP88XX_eCurAmpltNoChange); // increase hold current to actual normal (run) amplitude to stabilize the stepper rotor
// This function is called in this case but the timeout polling follows always.
// To avoid range overflow in timeout polling the flag is used:
    CddStp88XX_aftWaitStabilize[ucIx] = FastTimerStart(CDDSTP88XX_WaitStabilize_FTimer);
    CddStp88XX_aBitsMod[ucIx].Bit.biWaitStabilize = 1u;
#ifdef JK_TBD
    /*jk-tbd*/if (1) // always! - just remember!
#endif
     CddStp88XX_aBitsMod[ucIx].Bit.biWaitStabilize = 0; // needed because yet no Fast-Timer available

   //CddStp88XX_DemReportErrorStatus(ucIx, CddStp88XX_eDemEType_RefUVolt,   DEM_EVENT_STATUS_PASSED);
   //CddStp88XX_DemReportErrorStatus(ucIx, CddStp88XX_eDemEType_MoveUVolt,  DEM_EVENT_STATUS_PASSED); // break of run because of undervoltage (SysVoltUnder)
   //CddStp88XX_DemReportErrorStatus(ucIx, CddStp88XX_eDemEType_MoveOvVolt, DEM_EVENT_STATUS_PASSED); // break of run because of overvoltage (SysVoltOver)
   }

   CddStp88XX_HalStpFct[ucIx].pHandleMotEn(TRUE, TRUE);              // enable stepper motor driver
   if (CddStp88XX_aBitsMod[ucIx].Bit.biOldStateNotInit == 0u)         // if the old state is(!) init
   {
    CddStp88XX_aBitsMod[ucIx].Bit.biOldStateNotInit = 1u;            // no more init state
   }

   //0   CddStp88XX_HandleResetErrVolt(ucIx, TRUE);                        // reset error voltage and clear SC and OL bits of status registers
   CddStp88XX_HandleResetErrVolt(ucIx, FALSE);                       // reset error voltage and do not clear SC and OL bits of status registers
   break;
  }
  default:         // switch of enum variable: against MISRA warning - QAC(Prio2) Msg: 2018(This switch default label is unreachable.) Depth: 0 Ref: 
  {
   // This is not a valid action, must be an error.
   // Assert(....);
   break;
  }
  }
 CddStp88XX_CheckPsensSlopeAndActPos(ucIx);

 // PRQA S 5324 2 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio2) Msg: 5324(HIS metrics violation: 'CddStp88XX_SetCurrent() : STCAL = 10' exceeds threshold 7 for Number of Distinct Function Calls (STCAL).) Depth: 0 Ref: 
 // PRQA S 5330 1 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio2) Msg: 5330(HIS metrics violation : 'CddStp88XX_StateFct_Off() : STST3 = 53' exceeds threshold 50 for Number of statements in function(STST3).) Depth : 0 Ref :
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_StateFct_Stby
///
///  \brief    ucIx Standby state function to handle state CddStp88XX_eStateStby
///
///  \param    uint8 ucIx
///            tAction Action
///
///  \return   none
///
///  \descr
///
// ---------------------------------------------------------------------------
STATIC_AL void CddStp88XX_StateFct_Stby(uint8 ucIx, tAction Action)
{
 CDDSTP88XX_OptimizeArrayIndex(ucIx)

  switch (Action)
  {
   // ~~~~~ Action-Entry ~~~~~
  case ActEntry:              // perform entry action
  {
   CddStp88XX_HandleStpOnTime(ucIx, TRUE);

   CddStp88XX_StartWaitVoltage(ucIx);

   //    CddStp88XX_aStpState[ucIx].Bit.VoltNorm = 0;                    // see CddStp88XX_Volt()
   //    if (CddStp88XX_ucStateVolt == CDDSTP88XX_StateVoltOver)                // overvoltage, not undervoltage?
   //    {
   //      CddStp88XX_aStpState[ucIx].Bit.VoltOver = 1u;                  // see CddStp88XX_Volt()
   //      CddStp88XX_aStpState[ucIx].Bit.VoltUSSM = 0;                  // see CddStp88XX_Volt()
   //    }
   //    else                                                                     // undervoltage
   //    {
   //      CddStp88XX_aStpState[ucIx].Bit.VoltOver = 0;                  // see CddStp88XX_Volt()
   //      if (CddStp88XX_ucStateVolt == CDDSTP88XX_StateVoltUnder)             // undervoltage soft stop motion?
   //      {
   //        CddStp88XX_aStpState[ucIx].Bit.VoltUSSM = 1u;                // see CddStp88XX_Volt()
   //      }
   //      else                                                                   // undervoltage hard stop motion (step loss in case of motion)
   ////    if (CddStp88XX_ucStateVolt == CDDSTP88XX_StateVoltOff)
   //      {
   //        CddStp88XX_aStpState[ucIx].Bit.VoltUSSM = 0;                // see CddStp88XX_Volt()
   //      }
   //    }

   CddStp88XX_aBitsMod[ucIx].Bit.biWaitStabilizeChg = 0;                   // reset flag to detect change of biWaitStabilize flag

// jk-obsolet       CddStp88XX_aunCorrValueAbs[ucIx] = 0; // if (CddStp88XX_GetAttr(ucIx)->biUsePsens == 1u) // Sref: clear position correction value to avoid steps if setting position in StpCtrl has changed while voltage is not normal and then is normal again
   break;
  }


  // ~~~~~ Action-Do ~~~~~
  case ActDo:              // perform do activity
  {
   // update internal Data-Mirror ('CddStp8899_aSRegXXX') of necessary HW-Status-Registers ('CddStp8899Com_DataMirror.StatvRx.aSRegXXX')
   (void)CddStp8899Com_GetSRegBscFltDiag12(ucIx, &CddStp8899_aSRegBasic[ucIx].ucRaw
    , &CddStp8899_aSRegFault[ucIx].ucRaw
    , &CddStp8899_aSRegDiag1[ucIx].ucRaw
    , &CddStp8899_aSRegDiag2[ucIx].ucRaw);

   if (CddStp88XX_aBitsMod[ucIx].Bit.biWaitStabilize == 0u)
   {
    if (CddStp88XX_aBitsMod[ucIx].Bit.biWaitStabilizeChg == 0u)              // change of biWaitStabilize flag not detected?
    {
     CddStp88XX_aBitsMod[ucIx].Bit.biWaitStabilizeChg = 1u;                 // change of biWaitStabilize flag detected
     CddStp88XX_HalStpFct[ucIx].pHandleCurAmplt((uint8)CDDSTP88XX_eCurAmpltStateHold,
      CddStp88XX_aucCurAmpltHoldTemp[ucIx][CddStp88XX_aeTemp[ucIx]],
      CDDSTP88XX_eCurAmpltNoChange); // decrease current to hold amplitude (do not stabilize the stepper rotor)
    }
   }
   else
   {
    (void)CddStp88XX_HandleWaitStabilize(ucIx);                             // stabilize hold current has actual normal (run) amplitude!
//red.  (void)CddStp88XX_HalStpFct[ucIx].pSpiSendCRegAll();                     // write all the control registers to ensure actual values
   }

   CddStp88XX_aBitsMod[ucIx].Bit.biDisOLDetect = 0;                          // OL detection is enable
   (void)CddStp88XX_HalStpFct[ucIx].pSpiSendCReg4(FALSE);                    // jk: send also EN_OL (Open-Load-Detection by SPI)

   // check for change to StateOff (zero coil current)
   if ((CddStp88XX_aBitsMod[ucIx].Bit.biWaitStabilize == 0u)
    && (((CddStp8899_aSRegDiag2[ucIx].Bit.u1OTS) != 0u)   // DRV88XX ('over') thermal shutdown error bit - i.e.: TSD detected?
     || ((CddStp8899_aSRegDiag2[ucIx].Bit.u1OTW) != 0u)   // DRV88XX thermal warning error bit
     || (CddStp8899_aSRegFault[ucIx].Bit.u1UVLO != 0u)   // DRV88XX UV3 warning error bit
     || ((CddStp8899_aSRegFault[ucIx].Bit.u1OCP) != 0u)
     || ((CddStp8899_aSRegFault[ucIx].Bit.u1OL) != 0u))) // do not use (CddStp88XX_HalStpFct[ucIx].pIsSCCntMax()) maximal value of overcurrent counter because Standby does not call CddStp88XX_Transition_Err()!
   { // do not retry to enable driver by reading the register in case of SC, SH, OL, TW and TSD.
     // to protect the driver it will be disabled.
//!     CddStp88XX_HalStpFct[ucIx].pHandleMotEn(FALSE, FALSE);                  // disable stepper motor driver (send value by CddStp88XX_HalStpFct[ucIx].pSpiSendCRegAll(), see line after if block)
//!     (void)CddStp88XX_HalStpFct[ucIx].pSpiSendSRegAll();                     // read all the status registers to clear the error bit
//!     (void)CddStp8899Com_StartRxNotificationSr12367A8A(ucIx);                // synchronize the sending of SPI commands to read all status registers with the reading of the results after all three values are received
//!     CddStp88XX_aBits[ucIx].Bit.biTransitionErrDone = 0;                     // not: check of error bits is done in CddStp88XX_Transition_Err() - used in CddStp88XX_HalStpVer/Hor/Sht_ErrnCb() and in CddStp88XX_Transition_Err()

    CddStp88XX_aBitsMod[ucIx].Bit.biTransOff = 1u;                           // stop StateStby by setting special transition condition to StateOff
    CddStp88XX_aBitsMod[ucIx].Bit.biWaitVoltage = 0;                        // stop voltage wait - also started in StateOff
   }
   (void)CddStp88XX_HalStpFct[ucIx].pSpiSendCRegAll();                       // write all the control registers to ensure actual values

   (void)IoHwAb_User_GetAdc_DIAG_VBAT(&CddStp88XX_unDIAG_VBAT);
   CddStp88XX_aStpState[ucIx].Bit.Reduced = CddStpDyn_SetFreq(ucIx, CddStp88XX_aunTgtTmin[ucIx], CddStp88XX_unDIAG_VBAT);
   break;
  }


  // ~~~~~ Action-Exit ~~~~~
  case ActExit:              // perform exit action
  {
   //!   CddStp88XX_HalStpFct[ucIx].pHandleMotEn(TRUE, TRUE);                      // enable stepper motor driver

   //0   CddStp88XX_HandleResetErrVolt(ucIx, TRUE);                                // reset error voltage and clear SC and OL bits of status registers
   CddStp88XX_HandleResetErrVolt(ucIx, FALSE);                               // reset error voltage and do not clear SC and OL bits of status registers
   break;
  }
  default:         // switch of enum variable: against MISRA warning - QAC(Prio2) Msg: 2018(This switch default label is unreachable.) Depth: 0 Ref: 
  {
   // This is not a valid action, must be an error.
   // Assert(....);
   break;
  }
  }
 CddStp88XX_CheckPsensSlopeAndActPos(ucIx);

 // PRQA S 5324 1 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio2) Msg: 5324(HIS metrics violation: 'CddStp88XX_SetCurrent() : STCAL = 10' exceeds threshold 7 for Number of Distinct Function Calls (STCAL).) Depth: 0 Ref: 
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_StateFct_Idle
///
///  \brief    ucIx Idle state function to handle state CddStp88XX_eStateIdle
///
///  \param    uint8 ucIx
///            tAction Action
///
///  \return   none
///
///  \descr
///
// ---------------------------------------------------------------------------
STATIC_AL void CddStp88XX_StateFct_Idle(uint8 ucIx, tAction Action)
{
 CDDSTP88XX_OptimizeArrayIndex(ucIx)

  switch (Action)
  {
   // ~~~~~ Action-Entry ~~~~~
  case ActEntry:              // perform entry action
  {
   CddStp88XX_HandleStpOnTime(ucIx, TRUE);

   //    CddStp88XX_aStpState[ucIx].Bit.VoltNorm = 1u;                            // see CddStp88XX_Volt()
   //    CddStp88XX_aStpState[ucIx].Bit.VoltOver = 0;                            // see CddStp88XX_Volt()
   //    CddStp88XX_aStpState[ucIx].Bit.VoltUSSM = 0;                            // see CddStp88XX_Volt()
   CddStp88XX_SetStpStateBitIsReady(ucIx); // CddStp88XX_aStpState[ucIx].Bit.IsReady = 1u; 
   //  keine CddStp88XX_HalStpLwr_SendSRegX()-Funktionen, da sowieso immer alle StatusRegister gelesen werden
     //(void)CddStp88XX_HalStpFct[ucIx].pSpiSendSReg3();                       // update microstep position counter

     // jk: 'CddStp88XX_GetAttr'/'tCddStp88XX_Attr'/'tCddStp_Attr' is ONLY about 'PSenes'
   if (CddStp88XX_GetAttr(ucIx)->biUsePsens == 1u) // Sref
   {
    CddStp88XX_aBitsMod[ucIx].Bit.biSlopePosInvalid = 0;
   }

   CddStp88XX_aBitsMod[ucIx].Bit.biWaitStabilizeChg = 0;                   // reset flag to detect change of biWaitStabilize flag

   // to avoid missing OL detection now in IdleState in case of OL while MoveState before (DRV8899 is not able to detect OL), start a new read of status registers and check the state:
   //  keine CddStp88XX_HalStpLwr_SendSRegX()-Funktionen, da sowieso immer alle StatusRegister gelesen werden
   // (void)CddStp88XX_HalStpFct[ucIx].pSpiSendSRegAll();                     // read all the status registers to clear the error bit - once more!
   /*jk-tbd - Not Needed Any Longer*/ // (void)CddStp8899Com_StartRxNotificationSr12367A8A(ucIx);                // synchronize the sending of SPI commands to read all status registers with the reading of the results after all three values are received
   CddStp88XX_aBits[ucIx].Bit.biTransitionErrDone = 0;                     // not: check of error bits is done in CddStp88XX_Transition_Err() - used in CddStp88XX_HalStpVer/Hor/Sht_ErrnCb() and in CddStp88XX_Transition_Err()

   break;
  }


  // ~~~~~ Action-Do ~~~~~
  case ActDo:              // perform do activity
  {
   if (CddStp88XX_aBitsMod[ucIx].Bit.biWaitStabilize == 0u)
   {
    if (CddStp88XX_aBitsMod[ucIx].Bit.biWaitStabilizeChg == 0u)            // change of biWaitStabilize flag not detected?
    {
     CddStp88XX_aBitsMod[ucIx].Bit.biWaitStabilizeChg = 1u;               // change of biWaitStabilize flag detected
     if (CddStp88XX_aStpCtrl[ucIx].Bit.Ref == 0u)                         // only in case of no reference run (previous states are Init - Off - TestStep)) to avoid too late switch to run current because of SPI sending delay!
     {
      CddStp88XX_HalStpFct[ucIx].pHandleCurAmplt((uint8)CDDSTP88XX_eCurAmpltStateHold
       , CddStp88XX_aucCurAmpltHoldTemp[ucIx][CddStp88XX_aeTemp[ucIx]]
       , CDDSTP88XX_eCurAmpltNoChange); // decrease current to hold amplitude (do not stabilize the stepper rotor)
     }
    }
   }
   else
   {
    (void)CddStp88XX_HandleWaitStabilize(ucIx);                           // stabilize hold current has actual normal (run) amplitude!
    (void)CddStp88XX_HalStpFct[ucIx].pSpiSendCRegAll();                   // write all the control registers to ensure actual values
   }

   // update internal Data-Mirror ('CddStp8899_aSRegXXX') of necessary HW-Status-Registers ('CddStp8899Com_DataMirror.StatvRx.aSRegXXX')
   (void)CddStp8899Com_GetSRegBscFltDiag12(ucIx, &CddStp8899_aSRegBasic[ucIx].ucRaw
    , &CddStp8899_aSRegFault[ucIx].ucRaw
    , &CddStp8899_aSRegDiag1[ucIx].ucRaw
    , &CddStp8899_aSRegDiag2[ucIx].ucRaw);

   if ((CddStp8899_aSRegDiag2[ucIx].Bit.u1OTW) != 0u)                        // thermal warning bit set?
   {
    // keine CddStp88XX_HalStpLwr_SendSRegX()-Funktionen, da sowieso immer alle StatusRegister gelesen werden
    // (void)CddStp88XX_HalStpFct[ucIx].pSpiSendSReg1();                     // update thermal warning bit

    CddStp88XX_HandleResetErrVolt(ucIx, FALSE);                             // error is checked, therefore reset error voltage but do not clear the SC and OL bits of status registers
   }

   (void)IoHwAb_User_GetAdc_DIAG_VBAT(&CddStp88XX_unDIAG_VBAT);
   CddStp88XX_aStpState[ucIx].Bit.Reduced = CddStpDyn_SetFreq(ucIx, CddStp88XX_aunTgtTmin[ucIx], CddStp88XX_unDIAG_VBAT);
   CddStp88XX_aBitsMod[ucIx].Bit.biDisOLDetect = 0;                        // OL detection is enable
   (void)CddStp88XX_HalStpFct[ucIx].pSpiSendCReg4(FALSE);                  // jk: send also EN_OL (Open-Load-Detection by SPI)

   break;
  }


  // ~~~~~ Action-Exit ~~~~~
  case ActExit:              // perform exit action
  {
   CddStp88XX_aStpState[ucIx].Bit.IsReady = 0;
   break;
  }
  default:         // switch of enum variable: against MISRA warning - QAC(Prio2) Msg: 2018(This switch default label is unreachable.) Depth: 0 Ref: 
  {
   // This is not a valid action, must be an error.
   // Assert(....);
   break;
  }
  }
 CddStp88XX_CheckPsensSlopeAndActPos(ucIx);

 // PRQA S 5324 1 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio2) Msg: 5324(HIS metrics violation: 'CddStp88XX_SetCurrent() : STCAL = 10' exceeds threshold 7 for Number of Distinct Function Calls (STCAL).) Depth: 0 Ref: 
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_StateFct_Move
///
///  \brief    ucIx Move state function to handle state CddStp88XX_eStateMove
///
///  \param    uint8 ucIx
///            tAction Action
///
///  \return   none
///
///  \descr
///
// ---------------------------------------------------------------------------
STATIC_AL void CddStp88XX_StateFct_Move(uint8 ucIx, tAction Action)
{
 tCddStpDyn_CalcMode CalcMode;

 CDDSTP88XX_OptimizeArrayIndex(ucIx)

  CalcMode.ucData = 0;
 CalcMode.Bit.Stop = ((CddStp88XX_aStpCtrl[ucIx].Bit.Stop == 1u)
  || (CddStp88XX_ucStateVolt != CDDSTP88XX_StateVoltNormal))    // hope that the movement can be stopped before no step is possible
  ? 1u : 0u;
 if (CddStp88XX_ucStateVolt != CDDSTP88XX_StateVoltNormal)            // handle StpState bits 'VoltNorm' and 'VoltOver' to notify under/over voltage while moving (stopping by using ramp)
 {
  //  CddStp88XX_aStpState[ucIx].Bit.VoltNorm = 0;             // see CddStp88XX_Volt()
  if (CddStp88XX_ucStateVolt == CDDSTP88XX_StateVoltOver)            // overvoltage, not undervoltage?
  {
   //    CddStp88XX_aStpState[ucIx].Bit.VoltOver = 1;           // see CddStp88XX_Volt()
   //    CddStp88XX_aStpState[ucIx].Bit.VoltUSSM = 0;           // see CddStp88XX_Volt()
         //CddStp88XX_DemReportErrorStatus(ucIx, CddStp88XX_eDemEType_MoveOvVolt, DEM_EVENT_STATUS_FAILED);  // break of run because of overvoltage (SysVoltOver)
  }
  else                                                                 // undervoltage
  {
   //    CddStp88XX_aStpState[ucIx].Bit.VoltOver = 0;           // see CddStp88XX_Volt()
         //CddStp88XX_DemReportErrorStatus(ucIx, CddStp88XX_eDemEType_MoveUVolt, DEM_EVENT_STATUS_FAILED);   // break of run because of undervoltage (SysVoltUnder)

   //    if (CddStp88XX_ucStateVolt == CDDSTP88XX_StateVoltUnder)         // undervoltage soft stop motion?
   //    {
   //      CddStp88XX_aStpState[ucIx].Bit.VoltUSSM = 1;         // see CddStp88XX_Volt()
   //    }
   //    else                                                               // undervoltage hard stop motion (step loss in case of motion)
   ////  if (CddStp88XX_ucStateVolt == CDDSTP88XX_StateVoltOff)
   //    {
   //      CddStp88XX_aStpState[ucIx].Bit.VoltUSSM = 0;         // see CddStp88XX_Volt()
   //    }
  }
 }
 //else
 //{
 //  CddStp88XX_aStpState[ucIx].Bit.VoltNorm = 1;             // see CddStp88XX_Volt()
 //  CddStp88XX_aStpState[ucIx].Bit.VoltOver = 0;             // see CddStp88XX_Volt()
 //  CddStp88XX_aStpState[ucIx].Bit.VoltUSSM = 0;             // see CddStp88XX_Volt()
 //}

 switch (Action)
 {
  // ~~~~~ Action-Entry ~~~~~
 case ActEntry:              // perform entry action
 {
  sint32 lActPos_;
  uint32 ulRemainingTicks;
  uint32 ulWriteIx;

  CddStp88XX_HandleStpOnTime(ucIx, TRUE);

  CddStp88XX_aStpState[ucIx].Bit.IsMoving = 1u;
  CddStp88XX_aBits[ucIx].Bit.biRetryTestStepDone = 0u;

  CddStp88XX_aBitsMod[ucIx].Bit.biDisOLDetect = 1u;             // to avoid OL-Pseudo error at low voltage
  (void)CddStp88XX_HalStpFct[ucIx].pSpiSendCReg4(FALSE);        // jk: send also EN_OL (Open-Load-Detection by SPI)

  (void)IoHwAb_User_GetAdc_DIAG_VBAT(&CddStp88XX_unDIAG_VBAT);
  CddStp88XX_aStpState[ucIx].Bit.Reduced = CddStpDyn_SetFreq(ucIx, CddStp88XX_aunTgtTmin[ucIx], CddStp88XX_unDIAG_VBAT);
  ulWriteIx = CddStp88XX_HalStpFct[ucIx].pGetWriteIx(&lActPos_, &ulRemainingTicks);
  CddStpDyn_CalcNextSteps(ucIx,
   CddStp88XX_HalStpFct[ucIx].pGetStpInfo()->HsInfoBuf,
   ulWriteIx,
   CddStp88XX_aStpCtrl[ucIx].Val.nPos,
   lActPos_,
   ulRemainingTicks,
   CalcMode);
  CddStp88XX_HalStpFct[ucIx].pStartStp();                      // MotEn is activated and normal current is set via SPI

  CddStp88XX_aucActPosMemCnt[ucIx] = 0;                        // reset count of no change of actual position in state Move, Ref1, Ref2 to avoid hanging in case of hanging CddStp8899_HalStp state machine in StateStep because of DMA or timer INT mismatch
  break;
 }


 // ~~~~~ Action-Do ~~~~~
 case ActDo:              // perform do activity
 {
  sint32  lActPos_;
  uint32  ulWriteIx;
  boolean boReturnHSH;
  uint32  ulRemainingTicks;

  boReturnHSH = CddStp88XX_HandleStepHanging(ucIx, FALSE);     // check whether the actual position changes to avoid hanging in case of hanging CddStp8899_HalStp state machine in StateStep because of DMA or timer INT mismatch

  (void)IoHwAb_User_GetAdc_DIAG_VBAT(&CddStp88XX_unDIAG_VBAT);
  CddStp88XX_aStpState[ucIx].Bit.Reduced = CddStpDyn_SetFreq(ucIx, CddStp88XX_aunTgtTmin[ucIx], CddStp88XX_unDIAG_VBAT);
  ulWriteIx = CddStp88XX_HalStpFct[ucIx].pGetWriteIx(&lActPos_, &ulRemainingTicks);
  CddStpDyn_CalcNextSteps(ucIx,
   CddStp88XX_HalStpFct[ucIx].pGetStpInfo()->HsInfoBuf,
   ulWriteIx,
   CddStp88XX_aStpCtrl[ucIx].Val.nPos,
   lActPos_,
   ulRemainingTicks,
   CalcMode);
  if (boReturnHSH != FALSE)                                     // check has reset the CddStp8899_HalStp state machine?
  {
   CddStp88XX_HalStpFct[ucIx].pStartStp();                    // call state machine to continue
  }

  // update internal Data-Mirror ('CddStp8899_aSRegXXX') of necessary HW-Status-Registers ('CddStp8899Com_DataMirror.StatvRx.aSRegXXX')
  (void)CddStp8899Com_GetSRegBscFltDiag12(ucIx, &CddStp8899_aSRegBasic[ucIx].ucRaw
   , &CddStp8899_aSRegFault[ucIx].ucRaw
   , &CddStp8899_aSRegDiag1[ucIx].ucRaw
   , &CddStp8899_aSRegDiag2[ucIx].ucRaw);

  if ((CddStp8899_aSRegDiag2[ucIx].Bit.u1OTW) != 0u)                        // thermal warning bit set?
  {
   //  keine CddStp88XX_HalStpLwr_SendSRegX()-Funktionen, da sowieso immer alle StatusRegister gelesen werden
   //(void)CddStp88XX_HalStpFct[ucIx].pSpiSendSReg1();          // update thermal warning bit

   CddStp88XX_HandleResetErrVolt(ucIx, FALSE);                // error is checked, therefore reset error voltage but do not clear the SC and OL bits of status registers
  }
  break;
 }


 // ~~~~~ Action-Exit ~~~~~
 case ActExit:              // perform exit action
 {
  CddStp88XX_aStpState[ucIx].Bit.IsMoving = 0;
  break;
 }
 default:         // switch of enum variable: against MISRA warning - QAC(Prio2) Msg: 2018(This switch default label is unreachable.) Depth: 0 Ref: 
 {
  // This is not a valid action, must be an error.
  // Assert(....);
  break;
 }
 }
 CddStp88XX_CheckPsensSlopeAndActPos(ucIx);

 // PRQA S 5324 1 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio2) Msg: 5324(HIS metrics violation: 'CddStp88XX_SetCurrent() : STCAL = 10' exceeds threshold 7 for Number of Distinct Function Calls (STCAL).) Depth: 0 Ref: 
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_StateFct_Ref1
///
///  \brief    ucIx Reference phase 1 state function to handle state CddStp88XX_eStateRef1
///
///  \param    uint8 ucIx
///            tAction Action
///
///  \return   none
///
///  \descr
///
// ---------------------------------------------------------------------------
STATIC_AL void CddStp88XX_StateFct_Ref1(uint8 ucIx, tAction Action)
{
 boolean             boReturn = FALSE;
 tCddStpDyn_CalcMode CalcMode;

 CDDSTP88XX_OptimizeArrayIndex(ucIx)

  CalcMode.ucData = 0;
 CalcMode.Bit.Stop = ((CddStp88XX_aStpCtrl[ucIx].Bit.Stop == 1u)  // if stopped by Ctrl: no error
  || (CddStp88XX_aStpCtrl[ucIx].Bit.Ref == 0u)) ? TRUE : FALSE; // if break   by Ctrl: no error
 if (CddStp88XX_GetAttr(ucIx)->biUsePsens == 1u) // Sref
 {
 }
 else                                            // Href
 {
  CalcMode.Bit.Ref1 = 1u;
  if (CalcMode.Bit.Stop == 1u) //! in this case the Stop bit is ignored by CddStpDyn_CalcNextSteps()!
  {
   CddStp88XX_aBitsMod[ucIx].Bit.biTransOff = 1u; // stop StateRef by setting special transition condition to StateOff
   boReturn = TRUE;
  }
 }

 if (boReturn == FALSE)
 {
  switch (Action)
  {
   // ~~~~~ Action-Entry ~~~~~
  case ActEntry:              // perform entry action
  {
   sint32 lActPos_;
   uint32 ulRemainingTicks;
   uint32 ulWriteIx;

   CddStp88XX_HandleStpOnTime(ucIx, TRUE);

   CddStp88XX_HalStpFct[ucIx].pSetActPos(0); // reset value for use of complete range

// UWY - see new interface function roCddStpStartRefRun()        CddStp88XX_anRef1Pos[ucIx] = CddStp88XX_aStpCtrl[ucIx].Val.nPos;                 // save given reference position (manipulated in case of Href)

        // jk: 'CddStp88XX_GetAttr'/'tCddStp88XX_Attr'/'tCddStp_Attr' is ONLY about 'PSenes'
   if (CddStp88XX_GetAttr(ucIx)->biUsePsens == 1u) // Sref
   {
    CddStp88XX_ucAhlErrPsensCnt = CDDSTP88XX_REF1ERRPSENS_MAX;                     // maximal count of Ref1 pseudo ErrPsens

//!       CddStpPsens_ResetPsens(ucIx); // reset variables of position sensor 'Psens'
    CddStp88XX_aBitsMod[ucIx].Bit.biIsPositiveRefStart = CddStp88XX_aPsensInf[ucIx].Bit.biIsPositive; // save position sensor level at start of reference run
    CddStp88XX_aBitsMod[ucIx].Bit.biSlopePosInvalid = 1u;
    CddStp88XX_alDeviation[ucIx] = 0;
   }
   else                                            // Href
   {
    // because of DRV8899 can not be reset in ECU (RHB pin is fixed to GND) the LWR reference HS count is modulo 8 (8 HS per cycle) and actual driver HS position is considered to avoid different positions after a series of reference runs:
    // DRV8899 - SReg3: MSP reset value 0x10 at 0 HS but TestStep increments/decrements 0x04 MSP (depends on biRichtung).  Also reset value of MSP is 0x14/0x0C -> Reset value of actual HS position (high nibble without parity bit) is 0x10/0x00. This can be corrected by CDDSTP88XX_SReg3Msp2MsCnt: -> 0x00.
#ifdef JK_TBD
    /*jk-tbd*/ if (0); // 
#endif
    sint16 nLwrActHsPosAtRef = /*jk-tbd*/0;// ((((sint16)CddStp8899_aSReg3[ucIx] - (sint16)CDDSTP88XX_SReg3Msp2MsCnt) & (sint16)CDDSTP88XX_SReg3MspHsMask) >> 4); // HS in high nipple with reset value 0x10 corrected for each HS of a cycle in both TestStep directions -> shifted in low nipple is the LWR HS position correction!

    if (CddStp88XX_aBits[ucIx].Bit.biRichtung == 1u)                                // inverse direction?
    {
     // PRQA S 4532, 4542 1 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio7) Msg: 4532(An expression of 'essentially signed' type (signed short) is being used as the left-hand operand of this bitwise operator (&).) Depth: 0 Ref: MISRA C:2012 Rule-10.1 | warning - QAC(Prio7) Msg: 4542(A non-negative constant expression of 'essentially signed' type (signed short) is being used as the right-hand operand of this bitwise operator (&).) Depth: 0 Ref: MISRA C:2012 Rule-10.1
     nLwrActHsPosAtRef = (-nLwrActHsPosAtRef) & (sint16)CDDSTP88XX_HsPerCycleMask; // turn DRV8899 phase counter step series from 0 - 1 - 2 - 3 - 4 - 5 - 6 - 7 to 0 - 7 - 6 - 5 - 4 - 3 - 2 - 1
    }
    // PRQA S 2855, 4532 1 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio6) Msg: 2855(Constant: Casting to a signed integer type of insufficient size.) Depth: 0 Ref: MISRA C:2012 Dir-1.1 | warning - QAC(Prio7) Msg: 4532(An expression of 'essentially signed' type (signed short) is being used as the left-hand operand of this bitwise operator (&).) Depth: 0 Ref: MISRA C:2012 Rule-10.1
    CddStp88XX_anRef1Pos[ucIx] &= (sint16)CDDSTP88XX_NegRefCntMask;                 // add HS to given negative reference HS count (modulo 8 HS because of 8 HS per cycle)
    CddStp88XX_anRef1Pos[ucIx] -= nLwrActHsPosAtRef;                                // add HS to given negative reference HS count by subtracting actual HS position
   }

   // turn direction in case of wrong reference target position in relation to actual position sensor level
   CddStp88XX_HandleWrongRef1Motion(ucIx);             // check whether the actual position sensor level is really correct to wait for slope or if motion should be turned to the other direction

   (void)IoHwAb_User_GetAdc_DIAG_VBAT(&CddStp88XX_unDIAG_VBAT);
   CddStp88XX_aStpState[ucIx].Bit.Reduced = CddStpDyn_SetFreq(ucIx, CddStp88XX_aunTgtTmin[ucIx], CddStp88XX_unDIAG_VBAT);
   ulWriteIx = CddStp88XX_HalStpFct[ucIx].pGetWriteIx(&lActPos_, &ulRemainingTicks); // now get the new actual values (after reset)
   CddStpDyn_CalcNextSteps(ucIx,
    CddStp88XX_HalStpFct[ucIx].pGetStpInfo()->HsInfoBuf,
    ulWriteIx,
    CddStp88XX_anRef1Pos[ucIx], // because of DRV8899 can not be reset in ECU (RHB pin is fixed to GND) the LWR reference HS count is modulo 8 and actual driver HS position is considered to avoid different positions after a series of reference runs
    lActPos_,
    ulRemainingTicks,
    CalcMode);
   CddStp88XX_HalStpFct[ucIx].pStartStp();          // MotEn is activated and normal current is set via SPI

   CddStp88XX_aBitsMod[ucIx].Bit.biDisOLDetect = 1u;       // to avoid OL-Pseudo error at low voltage
   (void)CddStp88XX_HalStpFct[ucIx].pSpiSendCReg4(FALSE);  // jk: send also EN_OL (Open-Load-Detection by SPI)

//      CddStp88XX_aStpState[ucIx].Bit.VoltNorm  = 1u; // see CddStp88XX_Volt()
//      CddStp88XX_aStpState[ucIx].Bit.VoltOver  = 0; // see CddStp88XX_Volt()
//      CddStp88XX_aStpState[ucIx].Bit.VoltUSSM  = 0; // see CddStp88XX_Volt()
   CddStp88XX_aStpState[ucIx].Bit.IsRef = 0;
   CddStp88XX_aStpState[ucIx].Bit.FullRef = 0;
   CddStp88XX_aStpState[ucIx].Bit.RefActive = 1u;
   CddStp88XX_aStpState[ucIx].Bit.IsMoving = 1u;
   CddStp88XX_aStpState[ucIx].Bit.StepLoss = 0;
   CddStp88XX_aStpState[ucIx].Bit.ErrPos = 0;
   //A     CddStp88XX_DemReportErrorStatus(ucIx, CddStp88XX_eDemEType_Pos, ERRLOG_NoDetecting);

   Rte_Call_DemPrj_ReportErrorStatus((uint16)STP_LOSS, DEM_EVENT_STATUS_PASSED); // clear step loss DTC

   CddStp88XX_aucActPosMemCnt[ucIx] = 0;                   // reset count of no change of actual position in state Move, Ref1, Ref2 to avoid hanging in case of hanging CddStp8899_HalStp state machine in StateStep because of DMA or timer INT mismatch
   break;
  }


  // ~~~~~ Action-Do ~~~~~
  case ActDo:              // perform do activity
  {
   sint32 lActPos_;
   uint32 ulRemainingTicks;
   uint32 ulWriteIx;
   boolean boReturnHSH;

   // turn direction in case of wrong reference target position in relation to actual position sensor level
   CddStp88XX_HandleWrongRef1Motion(ucIx);                 // check whether the actual position sensor level is really correct to wait for slope or if motion should be turned to the other direction

   boReturnHSH = CddStp88XX_HandleStepHanging(ucIx, TRUE); // check whether the actual position changes to avoid hanging in case of hanging CddStp8899_HalStp state machine in StateStep because of DMA or timer INT mismatch

   (void)IoHwAb_User_GetAdc_DIAG_VBAT(&CddStp88XX_unDIAG_VBAT);
   CddStp88XX_aStpState[ucIx].Bit.Reduced = CddStpDyn_SetFreq(ucIx, CddStp88XX_aunTgtTmin[ucIx], CddStp88XX_unDIAG_VBAT);
   ulWriteIx = CddStp88XX_HalStpFct[ucIx].pGetWriteIx(&lActPos_, &ulRemainingTicks);
   CddStpDyn_CalcNextSteps(ucIx,
    CddStp88XX_HalStpFct[ucIx].pGetStpInfo()->HsInfoBuf,
    ulWriteIx,
    CddStp88XX_anRef1Pos[ucIx],     // because of DRV8899 can not be reset in ECU (RHB pin is fixed to GND) the LWR reference HS count is modulo 8 and actual driver HS position is considered to avoid different positions after a series of reference runs
    lActPos_,
    ulRemainingTicks,
    CalcMode);
   if (boReturnHSH != FALSE)                                // check has reset the CddStp8899_HalStp state machine?
   {
    CddStp88XX_HalStpFct[ucIx].pStartStp();               // call state machine to continue
   }
   break;
  }


  // ~~~~~ Action-Exit ~~~~~
  case ActExit:              // perform exit action
  {
   // empty
   break;
  }
  default:         // switch of enum variable: against MISRA warning - QAC(Prio2) Msg: 2018(This switch default label is unreachable.) Depth: 0 Ref: 
  {
   // This is not a valid action, must be an error.
   // Assert(....);
   break;
  }
  }
  CddStp88XX_CheckPsensSlopeAndActPos(ucIx);
 }

 // PRQA S 5324 1 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio2) Msg: 5324(HIS metrics violation: 'CddStp88XX_SetCurrent() : STCAL = 10' exceeds threshold 7 for Number of Distinct Function Calls (STCAL).) Depth: 0 Ref: 
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_StateFct_Ref2
///
///  \brief    ucIx Reference phase 2 state function to handle state CddStp88XX_eStateRef2
///
///  \param    uint8 ucIx
///            tAction Action
///
///  \return   none
///
///  \descr
///
// ---------------------------------------------------------------------------
STATIC_AL void CddStp88XX_StateFct_Ref2(uint8 ucIx, tAction Action)
{
 boolean             boReturn = FALSE;
 sint32              lTgtPos;
 tCddStpDyn_CalcMode CalcMode;

 CDDSTP88XX_OptimizeArrayIndex(ucIx)

  CalcMode.ucData = 0;
 if (CddStp88XX_GetAttr(ucIx)->biUsePsens == 1u) // Sref
 {
  lTgtPos = 0;           // special case for CddStpDyn: no steps to do because of lActPos = 0 (//!Stop!)
  CalcMode.Bit.Stop = 1u; // * Sref reference run uses Psens *
 }
 else                                            // Href
 {
  lTgtPos = (sint32)CDDSTP88XX_CNT_Phase2;                // special case for CddStpDyn: calculate all steps without ramp!
  CalcMode.Bit.Stop = ((CddStp88XX_aStpCtrl[ucIx].Bit.Stop == 1u)   // if stopped by Ctrl: no error
   || (CddStp88XX_aStpCtrl[ucIx].Bit.Ref == 0u)) ? TRUE : FALSE; // if break   by Ctrl: no error
  CalcMode.Bit.Ref2 = 1u;
  if (CalcMode.Bit.Stop == 1u) //! in this case the Stop bit is ignored by CddStpDyn_CalcNextSteps()!
  {
   CddStp88XX_aBitsMod[ucIx].Bit.biTransOff = 1u; // stop StateRef by setting special transition condition to StateOff
   boReturn = TRUE;
  }
 }

 if (boReturn == FALSE)
 {
  switch (Action)
  {
   // ~~~~~ Action-Entry ~~~~~
  case ActEntry:              // perform entry action
  {
   sint32 lActPos_;
   uint32 ulRemainingTicks;
   uint32 ulWriteIx;

   CddStp88XX_HandleStpOnTime(ucIx, TRUE);

   if (CddStp88XX_GetAttr(ucIx)->biUsePsens == 1u) // Sref
   {
    if (CddStp88XX_aBitsMod[ucIx].Bit.biIsPositiveRefStart != CddStp88XX_aPsensInf[ucIx].Bit.biIsPositive) // change of position sensor level after slope // * Sref reference run uses Psens *
    {
     CddStp88XX_aBitsMod[ucIx].Bit.biSlopePosInvalid = 0;
    }
   }
   else                                            // Href
   {
    // before start of Ref2 phase: switch current (not compatible to Afs2)
//-       CddStp88XX_HalStpFct[ucIx].pHandleCurAmplt(CDDSTP88XX_eCurAmpltStateNoChange, CDDSTP88XX_eCurAmpltNoChange, CddStp88XX_aucCurAmpltRefTemp[ucIx][CddStp88XX_aeTemp[ucIx]]); // switch Irun current to level of Ref2 phase
    CddStp88XX_HalStpFct[ucIx].pHandleCurAmplt((uint8)CDDSTP88XX_eCurAmpltStateNorm
     , CDDSTP88XX_eCurAmpltNoChange
     , CddStp88XX_aucCurAmpltRefTemp[ucIx][CddStp88XX_aeTemp[ucIx]]); // switch Irun current to level of Ref2 phase
   }

   (void)IoHwAb_User_GetAdc_DIAG_VBAT(&CddStp88XX_unDIAG_VBAT);
   CddStp88XX_aStpState[ucIx].Bit.Reduced = CddStpDyn_SetFreq(ucIx, CddStp88XX_aunTgtTmin[ucIx], CddStp88XX_unDIAG_VBAT);
   ulWriteIx = CddStp88XX_HalStpFct[ucIx].pGetWriteIx(&lActPos_, &ulRemainingTicks);
   CddStpDyn_CalcNextSteps(ucIx,
    CddStp88XX_HalStpFct[ucIx].pGetStpInfo()->HsInfoBuf,
    ulWriteIx,
    lTgtPos,
    0,
    ulRemainingTicks,
    CalcMode);
   if (CddStp88XX_GetAttr(ucIx)->biUsePsens == 1u)            // Sref
   {
    //!Stop!     CddStp88XX_HalStpFct[ucIx].pStartStp(); // * Sref reference run uses Psens *
   }
   else                                                       // Href
   {
    CddStp88XX_HalStpFct[ucIx].pStartStp();                 // MotEn is activated and normal current is set via SPI
   }

   CddStp88XX_aBitsMod[ucIx].Bit.biDisOLDetect = 1u;         // to avoid OL-Pseudo error at low voltage
   (void)CddStp88XX_HalStpFct[ucIx].pSpiSendCReg4(FALSE);    // jk: send also EN_OL (Open-Load-Detection by SPI)

   CddStp88XX_aucActPosMemCnt[ucIx] = 0;                     // reset count of no change of actual position in state Move, Ref1, Ref2 to avoid hanging in case of hanging CddStp8899_HalStp state machine in StateStep because of DMA or timer INT mismatch
   break;
  }


  // ~~~~~ Action-Do ~~~~~
  case ActDo:              // perform do activity
  {
   if (CddStp88XX_GetAttr(ucIx)->biUsePsens == 1u)            // Sref
   {
    sint32 lActPos_;
    uint32 ulRemainingTicks;
    uint32 ulWriteIx;
    boolean boReturnHSH;

    boReturnHSH = CddStp88XX_HandleStepHanging(ucIx, TRUE); // check whether the actual position changes to avoid hanging in case of hanging CddStp8899_HalStp state machine in StateStep because of DMA or timer INT mismatch

    (void)IoHwAb_User_GetAdc_DIAG_VBAT(&CddStp88XX_unDIAG_VBAT);
    CddStp88XX_aStpState[ucIx].Bit.Reduced = CddStpDyn_SetFreq(ucIx, CddStp88XX_aunTgtTmin[ucIx], CddStp88XX_unDIAG_VBAT);
    ulWriteIx = CddStp88XX_HalStpFct[ucIx].pGetWriteIx(&lActPos_, &ulRemainingTicks);
    CddStpDyn_CalcNextSteps(ucIx,
     CddStp88XX_HalStpFct[ucIx].pGetStpInfo()->HsInfoBuf,
     ulWriteIx,
     lTgtPos,
     0,
     ulRemainingTicks,
     CalcMode);
    if (boReturnHSH != FALSE)                                // check has reset the CddStp8899_HalStp state machine?
    {
     CddStp88XX_HalStpFct[ucIx].pStartStp();               // call state machine to continue
    }
    //!Stop!     CddStp88XX_HalStpFct[ucIx].pStartStp(); // * Sref reference run uses Psens *
   }
   else                                                       // Href
   {
   }
   break;
  }


  // ~~~~~ Action-Exit ~~~~~
  case ActExit:              // perform exit action
  {
   // after Ref2 phase: switch current back (not compatible to Afs2)
//-     CddStp88XX_HalStpFct[ucIx].pHandleCurAmplt(CDDSTP88XX_eCurAmpltStateNoChange, CDDSTP88XX_eCurAmpltNoChange, CddStp88XX_aucCurAmpltRunTemp[ucIx][CddStp88XX_aeTemp[ucIx]]); // switch Irun current back to level of normal moveing phase
   CddStp88XX_HalStpFct[ucIx].pHandleCurAmplt((uint8)CDDSTP88XX_eCurAmpltStateNorm
    , CDDSTP88XX_eCurAmpltNoChange
    , CddStp88XX_aucCurAmpltRunTemp[ucIx][CddStp88XX_aeTemp[ucIx]]); // switch Irun current back to level of normal moveing phase

   CddStp88XX_aStpState[ucIx].Bit.IsMoving = 0;
   CddStp88XX_aStpState[ucIx].Bit.RefActive = 0;
   break;
  }
  default:         // switch of enum variable: against MISRA warning - QAC(Prio2) Msg: 2018(This switch default label is unreachable.) Depth: 0 Ref: 
  {
   // This is not a valid action, must be an error.
   // Assert(....);
   break;
  }
  }
  CddStp88XX_CheckPsensSlopeAndActPos(ucIx);
 }
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_StateFct_RefWait
///
///  \brief    ucIx Reference Wait state function to handle state CddStp88XX_eStateRefWait
///
///  \param    uint8 ucIx
///            tAction Action
///
///  \return   none
///
///  \descr
///
// ---------------------------------------------------------------------------
STATIC_AL void CddStp88XX_StateFct_RefWait(uint8 ucIx, tAction Action)
{
 CDDSTP88XX_OptimizeArrayIndex(ucIx)

  switch (Action)
  {
   // ~~~~~ Action-Entry ~~~~~
  case ActEntry:              // perform entry action
  {
   CddStp88XX_HandleStpOnTime(ucIx, TRUE);

   if ((CddStp88XX_aStpCtrl[ucIx].Bit.Stop == 1u)  // if stopped by Ctrl: no error
    || (CddStp88XX_aStpCtrl[ucIx].Bit.Ref == 0u)) // if break   by Ctrl: no error
   {
    CddStp88XX_aBitsMod[ucIx].Bit.biTransOff = 1u; // stop StateRef by setting special transition condition to StateOff
   }
   else
   {
    if (CddStp88XX_GetAttr(ucIx)->biUsePsens == 1u) // Sref
    {
#if(CFA_CNT_STP_ONBRD == 2)
     if (CddStp88XX_aBitsMod[ucIx].Bit.biSlopePosInvalid == 0u) // valid last position sensor change position
     {
      CddStp88XX_aStpState[ucIx].Bit.IsRef = 1u;
      CddStp88XX_aStpState[ucIx].Bit.FullRef = CddStp88XX_aBitsMod[ucIx].Bit.biIsRegSlope; // full ref. if regulation slope has occured
      CddStp88XX_DemReportErrorStatus(ucIx, CddStp88XX_eDemEType_Pos, DEM_EVENT_STATUS_PASSED);   // no position error
      CddStp88XX_aunIsRefCnt[ucIx]++;
     }
     else
     {

#if ( CFG_OPT_STP & CFG_Stp_IgnoreMissingPsens )

      CddStp88XX_aStpState[ucIx].Bit.IsRef = 1u;
      if (CddStp88XX_aStpPos[ucIx].nPos < 0)
      {
       CddStp88XX_HalStpFct[ucIx].pSetActPos(CDDSTP88XX_PosIgnoreMissingPsensN);
      }
      else
      {
       CddStp88XX_HalStpFct[ucIx].pSetActPos(CDDSTP88XX_PosIgnoreMissingPsensP);
      }
      CddStp88XX_DemReportErrorStatus(ucIx, CddStp88XX_eDemEType_Pos, DEM_EVENT_STATUS_PASSED);   // no position error
      CddStp88XX_aunIsRefCnt[ucIx]++;

#else

      if ((CddStp88XX_aStpCtrl[ucIx].Bit.Stop == 0u)                 // if stopped by Ctrl: no error // * Sref reference run uses Psens *
       && (CddStp88XX_aStpCtrl[ucIx].Bit.Ref == 1u))                // if break   by Ctrl: no error // * Sref reference run uses Psens *
      {
       //ErrPsensDiag  if (CddStp88XX_aStpState[ucIx].Bit.ErrPos == 0u)
       if (CddStp88XX_aStpState[ucIx].Bit.ErrPsens == 0u)//ErrPsensDiag
       {
        //ErrPsensDiag    CddStp88XX_aStpState[ucIx].Bit.ErrPos = 1u;                   // state machine continues without error!
        CddStp88XX_aStpState[ucIx].Bit.ErrPsens = 1u;//ErrPsensDiag   // state machine continues without error!
        if (Cod_AhlTestPsDefIgnor() == FALSE)                         // only Dem is set failed
        {
         CddStp88XX_DemReportErrorStatus(ucIx, CddStp88XX_eDemEType_Pos, DEM_EVENT_STATUS_FAILED);   // position error
        }
       }
      }

#endif

     }
#endif
    }    // end of 'if (SRef')

    else // Href
    {
     //        CddStp88XX_alDeviation[ucIx] = (sint16)-CddStp88XX_HalStpFct[ucIx].pGetActPos();                          // to reset ActPos in CddStp88XX_CtrlFct0() case CddStp_eCtrlFct0_ModeAbs (compatible to Afs2)

               // PRQA S 1820, 4446 1 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio7) Msg: 1820(The left-hand operand is non-constant and 'essentially signed' (signed short) but will be implicitly converted to an unsigned type (unsigned int) in this arithmetic operation.) Depth: 0 Ref: MISRA C:2012 Rule-10.4 |  warning - QAC(Prio7) Msg: 4446(A non-constant expression of 'essentially unsigned' type (unsigned int) is being converted to signed type, 'signed long' on assignment.) Depth: 0 Ref: MISRA C:2012 Rule-10.3
     CddStp88XX_alDeviation[ucIx] = (sint32)CDDSTP88XX_CNT_Phase2 - CddStp88XX_HalStpFct[ucIx].pGetActPos(); // to reset ActPos in CddStp88XX_CtrlFct0() case CddStp_eCtrlFct0_ModeAbs include steps of Ref2 phase (not compatible to Afs2)

     CddStp88XX_aStpState[ucIx].Bit.IsRef = 1u;
     //CddStp88XX_DemReportErrorStatus(ucIx, CddStp88XX_eDemEType_Pos, DEM_EVENT_STATUS_PASSED);   // no position error (hori. stepper/PSense)
     CddStp88XX_aunIsRefCnt[ucIx]++;
    }

    CddStp88XX_SetStpStateBitIsReady(ucIx); // CddStp88XX_aStpState[ucIx].Bit.IsReady = 1u;
    CddStp88XX_HalStpFct[ucIx].pHandleCurAmplt((uint8)CDDSTP88XX_eCurAmpltStateHold
     , CddStp88XX_aucCurAmpltHoldTemp[ucIx][CddStp88XX_aeTemp[ucIx]]
     , CDDSTP88XX_eCurAmpltNoChange); // decrease current to hold amplitude (do not stabilize the stepper rotor)
   }
   break;
  }


  // ~~~~~ Action-Do ~~~~~
  case ActDo:              // perform do activity
  {
   (void)IoHwAb_User_GetAdc_DIAG_VBAT(&CddStp88XX_unDIAG_VBAT);
   CddStp88XX_aStpState[ucIx].Bit.Reduced = CddStpDyn_SetFreq(ucIx, CddStp88XX_aunTgtTmin[ucIx], CddStp88XX_unDIAG_VBAT);

   // PRQA S 4424 1 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio7) Msg: 4424(An expression of 'essentially enum' type (tCddStpCtrlFct0_Cmd) is being converted to unsigned type, 'unsigned long' on assignment.) Depth: 0 Ref: MISRA C:2012 Rule-10.3
   CddStp88XX_CtrlFct0(CddStp_eCtrlFct0_ModeAbs, 0u, NULL);  // clear Ref and Stop bit and start movement - in FLM3 with only LWR it is obsolete to wait till CtrlStp has checked StpState IsRef bit and clears StpCtrl Ref bit -> do it here!

   break;
  }


  // ~~~~~ Action-Exit ~~~~~
  case ActExit:              // perform exit action
  {
   CddStp88XX_aBitsMod[ucIx].Bit.biRefWaitExit = 1u; // special StpCtrl message handling to force state machine from Exit of RefWait (= Entry of Idle) in Move if necessary without acknowledge by StpState bit 'IsReady'
   break;
  }
  default:         // switch of enum variable: against MISRA warning - QAC(Prio2) Msg: 2018(This switch default label is unreachable.) Depth: 0 Ref: 
  {
   // This is not a valid action, must be an error.
   // Assert(....);
   break;
  }
  }
 CddStp88XX_CheckPsensSlopeAndActPos(ucIx);
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_StateFct_TestStep
///
///  \brief    ucIx TestStep state function to handle state CddStp88XX_eStateTestStep
///
///  \param    uint8 ucIx
///            tAction Action
///
///  \return   none
///
///  \descr
///
// ---------------------------------------------------------------------------
STATIC_AL void CddStp88XX_StateFct_TestStep(uint8 ucIx, tAction Action)
{
 CDDSTP88XX_OptimizeArrayIndex(ucIx)

  // update internal Data-Mirror ('CddStp8899_aSRegXXX') of necessary HW-Status-Registers ('CddStp8899Com_DataMirror.StatvRx.aSRegXXX')
  (void)CddStp8899Com_GetSRegBscFltDiag12(ucIx, &CddStp8899_aSRegBasic[ucIx].ucRaw
   , &CddStp8899_aSRegFault[ucIx].ucRaw
   , &CddStp8899_aSRegDiag1[ucIx].ucRaw
   , &CddStp8899_aSRegDiag2[ucIx].ucRaw);

 switch (Action)
 {
  // ~~~~~ Action-Entry ~~~~~
 case ActEntry:              // perform entry action
 {
  CddStp88XX_HandleStpOnTime(ucIx, FALSE);

  CddStp88XX_aBitsMod[ucIx].Bit.biSetTestStep = CddStp88XX_HalStpFct[ucIx].pSetTestStep(TRUE); // test steps (synchronization HalStp with CddStp88XX because of SysVolt) - reset TestStepDone flag!

  CddStp88XX_HalStpFct[ucIx].pHandleCurAmplt((uint8)CDDSTP88XX_eCurAmpltStateHold
   , CddStp88XX_aucCurAmpltHoldTemp[ucIx][CddStp88XX_aeTemp[ucIx]]
   , CDDSTP88XX_eCurAmpltNoChange); // decrease current to hold amplitude (do not stabilize the stepper rotor)
  break;
 }


 // ~~~~~ Action-Do ~~~~~
 case ActDo:              // perform do activity
 {
  // PRQA S 4558 2 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio7) Msg: 4558(An expression of 'essentially unsigned' type (unsigned char) is being used as the left-hand operand of this logical operator (&&).) Depth: 0 Ref: MISRA C:2012 Rule-10.1
  if ((CddStp88XX_HalStpFct[ucIx].pSetTestStep(FALSE)) // test steps (synchronization HalStp with CddStp88XX because of SysVolt) - do not reset TestStepDone flag
   && (CddStp88XX_aBitsMod[ucIx].Bit.biSetTestStep == 0u))
  {
   CddStp88XX_aBitsMod[ucIx].Bit.biSetTestStep = 1u;

  }

  // LDM specific: retry mechanism in case of pseudo OL
  if (CddStp88XX_aBits[ucIx].Bit.biDoRetryTestStep != 0u)
  {
    CddStp88XX_aBits[ucIx].Bit.biRetryTestStepDone = 1u;
    CddStp_SetOLIgnore(FALSE);
    CddStp8899Com_SetFaultClr(ucIx);
    CddStp88XX_aBits[ucIx].Bit.biDoRetryTestStep = 0u;
  }
 

  break;
 }


 // ~~~~~ Action-Exit ~~~~~
 case ActExit:              // perform exit action
 {
  boolean boIsSCCntMax = CddStp88XX_HalStpFct[ucIx].pIsSCCntMax(); // maximal value of overcurrent counter
  boolean boIsOLCntMax = CddStp88XX_HalStpFct[ucIx].pIsOLCntMax(); // maximal value of openload counter

  CddStp88XX_aBits[ucIx].Bit.biTestStepDone = 1u;

  CddStp88XX_aStpState[ucIx].Bit.InitActive = 0;

  if (!((boIsSCCntMax != FALSE)                                  // special maximal value of overcurrent counter in HalStp state 'TestStep'
   || (boIsOLCntMax != FALSE)))                                // special maximal value of openload counter in HalStp state 'TestStep'
  {
   //        CddStp88XX_DemReportErrorStatus(ucIx, CddStp88XX_eDemEType_OL, DEM_EVENT_STATUS_PASSED);
   //        CddStp88XX_DemReportErrorStatus(ucIx, CddStp88XX_eDemEType_SC, DEM_EVENT_STATUS_PASSED);
  }

  if ((CddStp8899_aSRegDiag2[ucIx].Bit.u1OTS) == 0u) // DRV88XX ('over') thermal shutdown error bit - i.e.: NO TSD detected?
  {
   //        CddStp88XX_DemReportErrorStatus(ucIx, CddStp88XX_eDemEType_TempSD, DEM_EVENT_STATUS_PASSED); // no thermal shutdown (OTS / ErrTherm)
    Rte_Call_DemPrj_ReportErrorStatus((uint16)StpV0_E_OVTEMP_OFF, DEM_EVENT_STATUS_PASSED); // reset thermal shutdown DTC
  }

  if (CddStp88XX_aBitsMod[ucIx].Bit.biWaitStabilize == 1u)          // if necessary set stabilizing current once more to avoid too late switch to run current because of SPI sending delay!
  {
   //-     CddStp88XX_HalStpFct[ucIx].pHandleCurAmplt(CDDSTP88XX_eCurAmpltStateNoChange, /*CddStp88XX_aucCurAmpltHoldTemp*/CddStp88XX_aucCurAmpltRunTemp[ucIx][CddStp88XX_aeTemp[ucIx]], CDDSTP88XX_eCurAmpltNoChange); // increase hold current to actual normal (run) amplitude to stabilize the stepper rotor
   CddStp88XX_HalStpFct[ucIx].pHandleCurAmplt((uint8)CDDSTP88XX_eCurAmpltStateHold
    ,     /*CddStp88XX_aucCurAmpltHoldTemp*/CddStp88XX_aucCurAmpltRunTemp[ucIx][CddStp88XX_aeTemp[ucIx]]
    , CDDSTP88XX_eCurAmpltNoChange); // increase hold current to actual normal (run) amplitude to stabilize the stepper rotor
  }
  break;
 }

 default:         // switch of enum variable: against MISRA warning - QAC(Prio2) Msg: 2018(This switch default label is unreachable.) Depth: 0 Ref: 
 {
  // This is not a valid action, must be an error.
  // Assert(....);
  break;
 }
 }

 CddStp88XX_CheckPsensSlopeAndActPos(ucIx);
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_StateFct_Err
///
///  \brief    ucIx Error state function to handle state CddStp88XX_eStateErr
///
///  \param    uint8 ucIx
///            tAction Action
///
///  \return   none
///
///  \descr
///
// ---------------------------------------------------------------------------
STATIC_AL void CddStp88XX_StateFct_Err(uint8 ucIx, tAction Action)
{
 CDDSTP88XX_OptimizeArrayIndex(ucIx)

  switch (Action)
  {
   // ~~~~~ Action-Entry ~~~~~
  case ActEntry:              // perform entry action
  {
   CddStp88XX_HandleStpOnTime(ucIx, FALSE);

   CddStp88XX_HalStpFct[ucIx].pResetStp(FALSE); // reset HalStp state machine if DRV88XX has not stopped (Openload, ...) and motor is disabled because 88XX has no voltage monitor with automatic output disabling (UV3 for undervoltage is only warning)

//    CddStp88XX_aStpState[ucIx].Bit.VoltNorm  = 1u;                                  // see CddStp88XX_Volt()
//    CddStp88XX_aStpState[ucIx].Bit.VoltOver  = 0;                                  // see CddStp88XX_Volt()
//    CddStp88XX_aStpState[ucIx].Bit.VoltUSSM  = 0;                                  // see CddStp88XX_Volt()
   CddStp88XX_aStpState[ucIx].Bit.StepLoss = 0;
   CddStp88XX_aStpState[ucIx].Bit.IsRef = 0;
   CddStp88XX_aStpState[ucIx].Bit.FullRef = 0;
   CddStp88XX_aStpState[ucIx].Bit.RefActive = 0;
   CddStp88XX_aStpState[ucIx].Bit.IsMoving = 0;
   break;
  }


  // ~~~~~ Action-Do ~~~~~
  case ActDo:              // perform do activity
  {
   //  keine CddStp88XX_HalStpLwr_SendSRegX()-Funktionen, da sowieso immer alle StatusRegister gelesen werden
   // (void)CddStp88XX_HalStpFct[ucIx].pSpiSendSRegAll();          // update content of status registers (reset SReg1 and SReg2)
   /*jk-tbd - Not Needed Any Longer*/ // (void)CddStp8899Com_StartRxNotificationSr12367A8A(ucIx);     // synchronize the sending of SPI commands to read all status registers with the reading of the results after all three values are received
   CddStp88XX_aBits[ucIx].Bit.biTransitionErrDone = 0;          // not: check of error bits is done in CddStp88XX_Transition_Err() - used in CddStp88XX_HalStpVer/Hor/Sht_ErrnCb() and in CddStp88XX_Transition_Err()

   (void)CddStp88XX_HalStpFct[ucIx].pSpiSendCRegAll();          // write all the control registers to ensure actual values

   (void)IoHwAb_User_GetAdc_DIAG_VBAT(&CddStp88XX_unDIAG_VBAT);
   CddStp88XX_aStpState[ucIx].Bit.Reduced = CddStpDyn_SetFreq(ucIx, CddStp88XX_aunTgtTmin[ucIx], CddStp88XX_unDIAG_VBAT);
   break;
  }


  // ~~~~~ Action-Exit ~~~~~
  case ActExit:              // perform exit action
  {
   // reset HalStp counters
   CddStp88XX_HalStpFct[ucIx].pClrSCCnt();
   CddStp88XX_HalStpFct[ucIx].pClrOLCnt();

   CddStp88XX_aStpCtrl[ucIx].Bit.ErrClr = 0; // clear ErrClr bit to allow a new command CddStp_eCtrlFct0_ErrClr by call CddStp88XX_CtrlFct0()
   break;
  }
  default:         // switch of enum variable: against MISRA warning - QAC(Prio2) Msg: 2018(This switch default label is unreachable.) Depth: 0 Ref: 
  {
   // This is not a valid action, must be an error.
   // Assert(....);
   break;
  }
  }
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// StateMachine transition function tables
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ---------------------------------------------------------------------------
// Transition function table for ucIx state CddStp88XX_eStateInit
// ---------------------------------------------------------------------------
static const tTransitionCddStp88XX CddStp88XX_atTransitionInit[] =
{
 //  new state                  transition function
 { CddStp88XX_eStateOff,       CddStp88XX_Transition_InitOff     }
};

// ---------------------------------------------------------------------------
// Transition function table for ucIx state CddStp88XX_eStateOff
// ---------------------------------------------------------------------------
static const tTransitionCddStp88XX CddStp88XX_atTransitionOff[] =
{
 //  new state                  transition function
//! { CddStp88XX_eStateErr,     CddStp88XX_Transition_Err         },  // check StateOff before StateErr to avoid DRV88XX pseudo error detection in case of under/overvoltage
  { CddStp88XX_eStateTestStep,  CddStp88XX_Transition_TestStep    },
  //!!{ CddStp88XX_eStateRef1,    CddStp88XX_Transition_Ref1        },  // (not compatible to Afs2) - check StateRef1 before StateStby to avoid transition to Standby in case of not normal voltage
    { CddStp88XX_eStateStby,      CddStp88XX_Transition_OffStby     },
    { CddStp88XX_eStateIdle,      CddStp88XX_Transition_OffIdle     },
    { CddStp88XX_eStateInit,      CddStp88XX_Transition_Init        }   // (not compatible to Afs2)
};

// ---------------------------------------------------------------------------
// Transition function table for ucIx state CddStp88XX_eStateStby
// ---------------------------------------------------------------------------
static const tTransitionCddStp88XX CddStp88XX_atTransitionStby[] =
{
 //  new state                  transition function
 { CddStp88XX_eStateOff,       CddStp88XX_Transition_Off         },  // check StateOff before StateErr to avoid DRV88XX pseudo error detection in case of under/overvoltage
//! { CddStp88XX_eStateErr,     CddStp88XX_Transition_Err         },
  { CddStp88XX_eStateIdle,      CddStp88XX_Transition_StbyIdle    },
  { CddStp88XX_eStateInit,      CddStp88XX_Transition_Init        }   // (not compatible to Afs2)
};

// ---------------------------------------------------------------------------
// Transition function table for ucIx state CddStp88XX_eStateIdle
// ---------------------------------------------------------------------------
static const tTransitionCddStp88XX CddStp88XX_atTransitionIdle[] =
{
 //  new state                  transition function
 { CddStp88XX_eStateOff,       CddStp88XX_Transition_Off         },  // check StateOff before StateErr to avoid DRV88XX pseudo error detection in case of under/overvoltage
 { CddStp88XX_eStateErr,       CddStp88XX_Transition_Err         },
 { CddStp88XX_eStateTestStep,  CddStp88XX_Transition_TestStep    },  // check StateTestStep before StateRef1
 { CddStp88XX_eStateRefWait,   CddStp88XX_Transition_RefWait     },  // check State RefWait before StateRef1 (only used in case of Sref)
 { CddStp88XX_eStateRef1,      CddStp88XX_Transition_Ref1        },
 { CddStp88XX_eStateStby,      CddStp88XX_Transition_IdleStby    },
 { CddStp88XX_eStateMove,      CddStp88XX_Transition_IdleMove    },
 { CddStp88XX_eStateInit,      CddStp88XX_Transition_Init        }   // (not compatible to Afs2)
};

// ---------------------------------------------------------------------------
// Transition function table for ucIx state CddStp88XX_eStateMove
// ---------------------------------------------------------------------------
static const tTransitionCddStp88XX CddStp88XX_atTransitionMove[] =
{
 //  new state                  transition function
 { CddStp88XX_eStateOff,       CddStp88XX_Transition_MoveOff     },  // check StateOff before StateErr to avoid DRV88XX pseudo error detection in case of under/overvoltage
 { CddStp88XX_eStateErr,       CddStp88XX_Transition_Err         },  // HalStp does not increment SC and OL counters (DRV88XX)!
 { CddStp88XX_eStateIdle,      CddStp88XX_Transition_MoveIdle    },
 { CddStp88XX_eStateInit,      CddStp88XX_Transition_Init        }   // (not compatible to Afs2)
};

// ---------------------------------------------------------------------------
// Transition function table for ucIx state CddStp88XX_eStateRef1
// ---------------------------------------------------------------------------
static const tTransitionCddStp88XX CddStp88XX_atTransitionRef1[] =
{
 //  new state                  transition function
 { CddStp88XX_eStateOff,       CddStp88XX_Transition_RefOff      },  // check StateOff before StateErr to avoid DRV88XX pseudo error detection in case of under/overvoltage
 { CddStp88XX_eStateErr,       CddStp88XX_Transition_Err         },  // HalStp does not increment SC and OL counters (DRV88XX)!
 { CddStp88XX_eStateRef2,      CddStp88XX_Transition_Ref1Ref2    },
 { CddStp88XX_eStateRefWait,   CddStp88XX_Transition_Ref1RefWait },  // * Sref reference run uses Psens *
 { CddStp88XX_eStateInit,      CddStp88XX_Transition_Init        }   // (not compatible to Afs2)
};

// ---------------------------------------------------------------------------
// Transition function table for ucIx state CddStp88XX_eStateRef2
// ---------------------------------------------------------------------------
static const tTransitionCddStp88XX CddStp88XX_atTransitionRef2[] =
{
 //  new state                  transition function
 { CddStp88XX_eStateOff,       CddStp88XX_Transition_RefOff      },  // check StateOff before StateErr to avoid DRV88XX pseudo error detection in case of under/overvoltage
 { CddStp88XX_eStateErr,       CddStp88XX_Transition_Err         },  // HalStp does not increment SC and OL counters (DRV88XX)!
 { CddStp88XX_eStateRefWait,   CddStp88XX_Transition_Ref2RefWait },
 { CddStp88XX_eStateInit,      CddStp88XX_Transition_Init        }   // (not compatible to Afs2)
};

// ---------------------------------------------------------------------------
// Transition function table for ucIx state CddStp88XX_eStateRefWait
// ---------------------------------------------------------------------------
static const tTransitionCddStp88XX CddStp88XX_atTransitionRefWait[] =
{
 //  new state                  transition function
 { CddStp88XX_eStateOff,       CddStp88XX_Transition_RefOff      },  // check StateOff before StateErr to avoid DRV88XX pseudo error detection in case of under/overvoltage
 { CddStp88XX_eStateErr,       CddStp88XX_Transition_Err         },
 { CddStp88XX_eStateIdle,      CddStp88XX_Transition_RefWaitIdle },
 { CddStp88XX_eStateInit,      CddStp88XX_Transition_Init        }   // (not compatible to Afs2)
};

// ---------------------------------------------------------------------------
// Transition function table for ucIx state CddStp88XX_eStateTestStep
// ---------------------------------------------------------------------------
static const tTransitionCddStp88XX CddStp88XX_atTransitionTestStep[] =
{
 //  new state                  transition function
 { CddStp88XX_eStateErr,       CddStp88XX_Transition_Err         },  // HalStp does not increment SC and OL counters (DRV88XX)!
 { CddStp88XX_eStateIdle,      CddStp88XX_Transition_TestStepIdle},
 { CddStp88XX_eStateInit,      CddStp88XX_Transition_Init        }   // (not compatible to Afs2)
};

// ---------------------------------------------------------------------------
// Transition function table for ucIx state CddStp88XX_eStateErr
// ---------------------------------------------------------------------------
static const tTransitionCddStp88XX CddStp88XX_atTransitionErr[] =
{
 //  new state                  transition function
 { CddStp88XX_eStateOff,       CddStp88XX_Transition_ErrClr      },
 { CddStp88XX_eStateInit,      CddStp88XX_Transition_Init        }   // (not compatible to Afs2)
};


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// StateMachine table and function
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ---------------------------------------------------------------------------
// State machine table for ucIx complex driver DRV88XX
// ---------------------------------------------------------------------------

static const tStateMachineCddStp88XXSF CddStp88XX_atStateMachine[CddStp88XX_eMaxStates] =
{ //   state name                     transition count (of tr-table) [ucCount]        transition table [tTransitionCddStp88XX]   state function [tStateFctPtrCddStp88XX]
  { /* CddStp88XX_eStateInit,     */  UTIL_COUNTOF(CddStp88XX_atTransitionInit),      CddStp88XX_atTransitionInit,               CddStp88XX_StateFct_Init     },
  { /* CddStp88XX_eStateOff,      */  UTIL_COUNTOF(CddStp88XX_atTransitionOff),       CddStp88XX_atTransitionOff,                CddStp88XX_StateFct_Off      },
  { /* CddStp88XX_eStateStby,     */  UTIL_COUNTOF(CddStp88XX_atTransitionStby),      CddStp88XX_atTransitionStby,               CddStp88XX_StateFct_Stby     },
  { /* CddStp88XX_eStateIdle,     */  UTIL_COUNTOF(CddStp88XX_atTransitionIdle),      CddStp88XX_atTransitionIdle,               CddStp88XX_StateFct_Idle     },
  { /* CddStp88XX_eStateMove,     */  UTIL_COUNTOF(CddStp88XX_atTransitionMove),      CddStp88XX_atTransitionMove,               CddStp88XX_StateFct_Move     },
  { /* CddStp88XX_eStateRef1,     */  UTIL_COUNTOF(CddStp88XX_atTransitionRef1),      CddStp88XX_atTransitionRef1,               CddStp88XX_StateFct_Ref1     },
  { /* CddStp88XX_eStateRef2,     */  UTIL_COUNTOF(CddStp88XX_atTransitionRef2),      CddStp88XX_atTransitionRef2,               CddStp88XX_StateFct_Ref2     },
  { /* CddStp88XX_eStateRefWait,  */  UTIL_COUNTOF(CddStp88XX_atTransitionRefWait),   CddStp88XX_atTransitionRefWait,            CddStp88XX_StateFct_RefWait  },
  { /* CddStp88XX_eStateTestStep, */  UTIL_COUNTOF(CddStp88XX_atTransitionTestStep),  CddStp88XX_atTransitionTestStep,           CddStp88XX_StateFct_TestStep },
  { /* CddStp88XX_eStateErr,      */  UTIL_COUNTOF(CddStp88XX_atTransitionErr),       CddStp88XX_atTransitionErr,                CddStp88XX_StateFct_Err      }
};


// ---------------------------------------------------------------------------
///
///  \func     CddStp88XX_StateMachine
///
///  \brief    ucIx complex driver state machine
///
///  \param    uint8 ucIx
///            tCommandCddStp88XX eCmd
///
///  \return   none
///
///  \descr
///
// ---------------------------------------------------------------------------
STATIC_AL void CddStp88XX_StateMachine(uint8 ucIx, const tCommandCddStp88XX eCmd)
{
 // State-Machine:
 //  * State-Fcts with each 3 sections: ENTRY (once), DO (multiple), EXIT (once)
 //  * Transition-Fcts with TRUE (=DO the transition into this new state) and/or FALSE (= do NOT change into new state and STAY in current state)
 //  * i.e. a transition into another state is done if the Trans-Fct returns TRUE
 //  * Each 'State' has one or more possible transitions (ordered by priority)
 //  * E.g. state 'Standby':
 //                State-Fct: 'CddStp88XX_StateFct_Stby' (with 'Entry' & 'Do' & 'Exit')
 //                and possible transitions (true/false) in table 'CddStp88XX_atTransitionStby': ..._TransitionOff, ..._TransitionStbyIdle, ..._TransitionInit
 //                I.e. the state 'Standby' is maintained if ALL THREE trans.-fcts return 'false'
 //
 // eNewState   = eStateCurrent
 // pTransition = CddStp88XX_atStateMachine[eStateCurrent].pTransition
 // foreach (pTransition)  // order by priority
 //    if (pTransition->ptTransitionFct(...) == TRUE) // transition in another state possible?
 //       eNewState = pTransition->eNewState
 //       pOldStateFct(ActExit)                                          // old/current state-fct: EXIT
 //       CddStp88XX_atStateMachine[eNewState].pStateFct(ActEntry)       // new         state-fct: ENTRY
 //       break
 // if (eStateCurrent == eNewState) // still the old state i.e. NO transition into another state?
 //    pOldStateFct(ucIx, ActDo)                                         // current      state-fct: DO
 //
 //
 // typicall run: Init, Off, TestStep, Idle, Ref, ...


 //lint -esym(727, CddStp88XX_aeState) Symbol not explicitly initialized
 tStateCddStp88XX eStateBegin = CddStp88XX_aeState[ucIx];
 boolean boPowerOn = (CddStp88XX_aeState[ucIx] == CddStp88XX_eMaxStates) ? TRUE : FALSE;

 if (boPowerOn == TRUE)
 {
  CddStp88XX_aeState[ucIx] = CddStp88XX_eStateInit;
  eStateBegin = CddStp88XX_eStateInit;
  CddStp88XX_StateFct_Init(ucIx, ActEntry); // initial state entry call after power on
 }

 CDDSTP88XX_OptimizeArrayIndex(ucIx)

  // jk-tbd STP_RUNTIME_INTDIS_START(CddStp88XX_StateMachine)

  CddStp88XXTemp_StateMachine(ucIx, eCmd);

 // Execute state machine
 {
  boolean                             boBreak = FALSE;
  tStateCddStp88XX                   eNewState_ = eStateBegin;
  const tStateFctPtrCddStp88XX       pOldStateFct = CddStp88XX_atStateMachine[eStateBegin].pStateFct;
  const tTransitionCddStp88XX*       pTransition_ = CddStp88XX_atStateMachine[eStateBegin].pTransition;
  const tTransitionCddStp88XX* const pTransitionEnd = &pTransition_[CddStp88XX_atStateMachine[eStateBegin].ucCount];

#ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
#else // Unit-Tests!
  CddStp_UnitTest_Printf("                      *#*#*#*#*#*#*#* JK - CddStp88XX_StateMachine (eStateBegin=%d, pTransition_=0x%X) *#*#*#*#*#*#*#*\n", CddStp88XX_aeState[ucIx], pTransition_);
#endif

  for (; ((pTransition_ < pTransitionEnd) && (boBreak == FALSE)); pTransition_++)
  {

#ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
#else // Unit-Tests!
   CddStp_UnitTest_Printf("                      *#*#*#*#*#*#*#* JK - CddStp88XX_StateMachine; Transition-Check *#*#*#*#*#*#*#*\n");
#endif

   // Check transition condition
   if (pTransition_->ptTransitionFct(ucIx, eCmd) != (uint32)(FALSE))
   {
    // Ok, transition condition complied, get the the new state
    eNewState_ = pTransition_->eNewState;

#ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
#else // Unit-Tests!
    CddStp_UnitTest_Printf("                      *#*#*#*#*#*#*#* JK - CddStp88XX_StateMachine Transition-Check (eNewState_=%d) *#*#*#*#*#*#*#*\n", eNewState_);
#endif

#ifdef CDDSTP_ITM
    // N.b.: '_channel_' (=index) has to be 1...30  (1...x1E)
    // 24+0 = 'E0000060'
    ITM_TRACE_D8(24 + 0, (uint8)eNewState_); // CddStp88XX_eStateInit = 0,  CddStp88XX_eStateOff = 1,  CddStp88XX_eStateStby = 2,  CddStp88XX_eStateIdle = 3,  CddStp88XX_eStateMove = 4,  CddStp88XX_eStateRef1 = 5,  CddStp88XX_eStateRef2 = 6,  CddStp88XX_eStateRefWait = 7,  CddStp88XX_eStateTestStep = 8,  CddStp88XX_eStateErr = 9
#endif

// Call actual state exit action
#ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
          // check obsolet for Unit-Tests
    if (pOldStateFct != (tStateFctPtrCddStp88XX)0)
#else // Unit-Tests!
#endif
    {
     pOldStateFct(ucIx, ActExit);
    }

    // Call new state entry action
#ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
        // check obsolet for Unit-Tests
    if (CddStp88XX_atStateMachine[eNewState_].pStateFct != (tStateFctPtrCddStp88XX)0) // somehow a difficult line for Unit-Tests
#else // Unit-Tests!
#endif
    {
     CddStp88XX_atStateMachine[eNewState_].pStateFct(ucIx, ActEntry);
    }

    // Assign the new state to the state variable
    CddStp88XX_aeState[ucIx] = eNewState_;

    // Leave the for loop
    boBreak = TRUE;
   }
  }

  if ((eStateBegin == eNewState_) && (pOldStateFct != (tStateFctPtrCddStp88XX)0))
  {
   // Call ActDo activity because state was not changed and a state function exist.
   pOldStateFct(ucIx, ActDo);
  }
 }

 // common code ...
 CddStp88XX_HandleStp(ucIx);

 CddStp88XX_ReadDRV88XXTestRegAll(ucIx); // debug test only in case of (CddStp88XX_aBits[ucIx].Bit.biGetRegAll == 1u)

 // jk-tbd STP_RUNTIME_INTDIS_STOP(CddStp88XX_StateMachine)
}

//lint -restore

//EOF

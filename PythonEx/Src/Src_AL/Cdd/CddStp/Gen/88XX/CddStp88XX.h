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
/// \file  CddStp88XX.h
///
/// \brief  Texas Instruments TI-DRV88XX specific complex device driver
///
/// \descr  Stepper Driver 
///
///         Additional information can be found in the design description (Link:
///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
///
/// \author Wuesteney, Ulrich ALRT/EEG4 * (wu82rt)
///         J. Kling ALRT-EES6 (f84304b)
//-----------------------------------------------------------------------------

#ifndef CDDSTP88XX_H
#define CDDSTP88XX_H


/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/

#include <Util_Time.h>

#include <CddStpCfg.h>      // incl. nothing
#include <../Cdd/CddStp/Cfg/CddStp_Cfg.h>
#include <CddStpIfc.h>      // incl. 'CddStpTypes.h'

#include <_CddStp88XX.h>           // !
#include <CddStp8899Types.h>
#include <RteCommonTypes.h>


/*******************************************************************************
* Version
*******************************************************************************/


/*******************************************************************************
* Default Definition
*******************************************************************************/

  //-----------------------------------------------------------------------------
  // Step motor
  //-----------------------------------------------------------------------------




// Result states from the CddStp88XXVolt module.
#define CDDSTP88XX_StateVoltOff        (0u)
#define CDDSTP88XX_StateVoltUnder      (1u)
#define CDDSTP88XX_StateVoltNormal     (2u)
#define CDDSTP88XX_StateVoltOver       (3u)

//#define CDDSTP88XX_StateVoltStartValue (0xff)

#define CDDSTP88XX_CNT_Phase2          (12u)          // count of steps for jump compensation phase 2 of reference run (leave hard bump position)


#if (CFG_DEV_HOOK_EN == 1u) // tester hook
#define CDDSTP_OTS_HOOK_KEY       0xDEADC0DEu
#define CDDSTP_OTW_HOOK_KEY       0x3C3CC3C3u
#define CDDSTP_OCP_HOOK_KEY       0x4F4FF4F4u
#define CDDSTP_UTW_HOOK_KEY       0x1A1AA1A1u
#define CDDSTP_SPI_ERR_HOOK_KEY   0xAB1221BAu
#define CDDSTP_RESET_HOOK_KEY     0x50505050u
extern volatile uint32 CddStp_ulTesterHookActivation;
#endif

//  stepper typedefs
typedef enum
{
  CDDSTP_eStandardEvent = 0u,          // standard event handling
  CDDSTP_eAlternativeTrigger           // alternative trigger handling
} tEventCmdCddStp;


// -----------------------------------------------------------------------------
// stepper control signals

typedef struct
{
  sint16   nPos;         // target position in halfsteps
  uint8    ucFreq;       // max. frequency
  uint8    ucCtrl;       // control bits
}
tActCtrlVal;

// bitfield of 32 bits
typedef struct
{
  signed    nPos : 16;    //  0...15: target position in halfsteps (has to be set 1st BEFORE 'Stop'=0)  

  unsigned  ucFreq : 8;    // 16...23: max. frequency

  unsigned  Stop : 1;    // 24: Motor auf Stillstand abbremsen
  unsigned  Corr : 1;    // 25: Korrekturwert in Istposition einrechnen
  unsigned  Ref : 1;    // 26: Referenzlauf starten
  unsigned  ErrClr : 1;    // 27: Fehlerstatus loeschen
  unsigned  ErrInh : 1;    // 28: Inhibit driver errors and step loss
  unsigned  On : 1;    // 29: switch driver on
  unsigned  Dem : 1;    // 30: Dem written
  unsigned  RefVolatile : 1;    // 31: Referenzlauf als "fluechtig" (volatile) markieren
}
tActCtrlBit;

typedef union
{
  uint32       ulData;
  uint16       unData[2];
  tActCtrlVal  Val;
  tActCtrlBit  Bit;
}
tActCtrl;


// -----------------------------------------------------------------------------
// stepper pos

typedef struct
{
  sint16 nPos;         // actual position in halfsteps
}
tStpPos;

typedef tStpPos   tStpPosVer0;
typedef tStpPos   tStpPosVer1;
typedef tStpPos   tStpPosHor0;
typedef tStpPos   tStpPosHor1;
typedef tStpPos   tStpPosSht0;
typedef tStpPos   tStpPosSht1;


// ---------------------------------------------------------------------------
// externals
// ---------------------------------------------------------------------------

extern tsRte_CddStpActual                CddStp_ActAll;
extern sint16                         CddStp88XX_anRef1Pos[CFA_CNT_STP_88XX];

extern tCddStp88XXBits                CddStp88XX_aBits[CFA_CNT_STP_88XX];
extern tCddStp88XXBitsMod             CddStp88XX_aBitsMod[CFA_CNT_STP_88XX];
extern boolean                        CddStp88XX_boIgnoreOLDetection;
extern uCddStp88XXBitsGlobalInitOnce  CddStp88XX_BitsGlobalInitOnce; // prqa ....
extern tCddStpEvent                   CddStp88XX_aEventBits[CFA_CNT_STP_88XX];

extern TIMER                          CddStp88XX_aftWaitPreHold2[CFA_CNT_STP_88XX]; // - DRV88XX specific

extern tActCtrl                       CddStp88XX_aStpCtrl[CFA_CNT_STP_88XX];
extern tStpState                      CddStp88XX_aStpState[CFA_CNT_STP_88XX];
extern tStpPos                        CddStp88XX_aStpPos[CFA_CNT_STP_88XX];
extern uint16                         CddStp88XX_aunTgtTmin[CFA_CNT_STP_88XX];

extern uint8                          CddStp88XX_aucOLCntMax[CFA_CNT_STP_88XX];

extern tStateCddStp88XX               CddStp88XX_aeState[CFA_CNT_STP_88XX];

extern uint8                          CddStp88XX_ucNumOfSteppers_EFT;
extern uint8                          CddStp88XX_ucNumOfSteppers_Coding;


// ---------------------------------------------------------------------------
// function prototypes
// ---------------------------------------------------------------------------

void     CddStp88XX_Init(uint8 ucIx);
//void   CddStp88XX_DeInit  (uint8 ucIx);
void     CddStp88XX_DeInit_Interface(uint8 ucIx);
void     CddStp88XX_Cycle0(uint8 ucIx);
void     CddStp88XX_TgtVal(uint8 ucIx);
void     CddStp88XX_CtrlFct0(const uint32 ulCmd, const uint8 ucIx, tisCtrlData0* pData);
void     CddStp88XX_ParaFct0(const uint32 ulCmd, const uint8 ucIx, tisParaData0* pData);
void     CddStp88XX_CntFct0( const uint32 ulCmd, const uint8 ucIx, tisCntData0*  pData);
void     CddStp88XX_EftCodingLr(void);

void     CddStp88XX_cbCtrl(uint8 ucIx);
void     CddStp88XX_cbEvent(uint8 ucIx);
void     CddStp88XX_cbPsens(uint8 ucIx);
void     CddStp88XX_cbVolt(uint8 ucStateVolt);

boolean  CddStp88XX_HandleCurAmpltPreHold(uint8 ucIx, tCurAmpltStateCddStp88XX eCurAmpltState, uint8 ucCurAmpltHold, uint8 ucCurAmpltRun); // - DRV88XX specific

//void     CddStp88XX_DemReportErrorStatus(uint8 ucIx, tCddStp88XXDemErrorType DemErrorType, Dem_EventStatusType EventStatus);

void     CddStp88XX_Event(uint8 ucIx, tEventCmdCddStp eEventCmd);
void     CddStp88XX_Volt(const uint8 ucStateVolt);


// ---------------------------------------------------------------------------
// inline functions
// ---------------------------------------------------------------------------

//lint -e528 Symbol 'xxx' not referenced, usage of static inline
INLINE void CddStp88XX_SetTgtVal(uint8 ucIx, sint16 nPos, uint16 unTmin)
{
  CDDSTP88XX_OptimizeArrayIndex(ucIx)
    CddStp88XX_aStpCtrl[ucIx].Val.nPos = nPos; // UWY new interface usus HS directly! // CddStp_Ms2Hs(nPos);  // convert to implementation specific format
  CddStp88XX_aunTgtTmin[ucIx] = unTmin;
}

void CddStp88XX_GetState(uint8 ucIx);
INLINE boolean CddStp88XX_ActPosIsValid(uint8 ucIx)
{
  CDDSTP88XX_OptimizeArrayIndex(ucIx)
    return CddStp88XX_aBits[ucIx].Bit.biActPosValid;
}

INLINE sint16 CddStp88XX_GetActPos(uint8 ucIx)
{
  CDDSTP88XX_OptimizeArrayIndex(ucIx)
    return CddStp_Hs2Ms(CddStp88XX_aStpPos[ucIx].nPos);
}

INLINE uint8 CddStp88XX_GetNumOfSteppers_EFT(void)
{
  CddStp88XX_EftCodingLr();
  return CddStp88XX_ucNumOfSteppers_EFT;
}

INLINE uint8 CddStp88XX_GetNumOfSteppers_Coding(void)
{
  CddStp88XX_EftCodingLr();
  return CddStp88XX_ucNumOfSteppers_Coding;
}

INLINE const tCddStp88XXBitsMod* CddStp88XX_GetBitsMod(const uint8 ucIx)
{
  return (const tCddStp88XXBitsMod*)(const void*)(&CddStp88XX_aBitsMod[ucIx]);
}

INLINE const tCddStp_Bits* CddStp88XX_GetBits(const uint8 ucIx)
{
  return (const tCddStp_Bits*)(const void*)(&CddStp88XX_aBits[ucIx]);
}


#if ( CFG_OPT_STP &  CFG_Stp_UseInvPsensPol )

INLINE void CddStp88XX_InvertPsensPolarity(uint8 ucIx, boolean boInvert)
{
  CddStp88XX_aBits[ucIx].Bit.biInvPsensPol = boInvert ? 1 : 0;
  // jk-obsolet CddStpPsens_Measurement(ucIx, TRUE);
  CddStp88XX_aBits[ucIx].Bit.biInvPsensPolValid = 1;
  // jk-obsolet CddStpPsens_Measurement(ucIx, TRUE);
}

#endif


#if (( CFG_OPT_STP &  CFG_Stp_PsensDiag ) && ( CFG_OPT_STP &  CFG_Stp_SwitchPsensSigDiag ))
INLINE void CddStp88XX_SwitchPsensSignalDiag(uint8 ucIx, boolean boSwitchOn)
{
  CddStp88XX_aBits[ucIx].Bit.biPsensSigDiag = boSwitchOn ? 1 : 0;
}

#endif


extern sint32 CddStp88XX_alLastDeviation[CFA_CNT_STP_88XX];

INLINE sint32 CddStp88XX_GetLastDeviation(uint8 ucIx)
{
  return CddStp88XX_alLastDeviation[ucIx];
}


void IoHwAb_User_GetAdc_DIAG_VBAT(uint16* pio_signal);

#endif /* CDDSTP88XX_H */


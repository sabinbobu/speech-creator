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
/// \file  ctscCddStp.c
///
/// \brief  
///
/// \descr  
///
/// \author Thomas Schnizer  (sct3rt)
///         J. Kling ALRT-EES6 (f84304b)
///
///         
//-----------------------------------------------------------------------------


//=============================================================================
// includes
//=============================================================================

#include <Std_Types.h>
#include <AL_Helper.h> //-- STATIC_AL
#include <../Cdd/CddStp/CddStp_Tsp.h>

//#include <Rte_ctacCddStp.h> // RTE / KPIT
#include <CddStpIfc.h>

#ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
  #include <CddStpPrj.h>
  #include <CodM_Para/CodM_Para_System.h>
  #include <ctscCddStp.h>
  #include <Rte.h>
#else // Unit-Tests!
//  #define CFA_CNT_STP_88XX   (4u)
  #include <CddStpPrj.h>
  #include <CodM_Para/CodM_Para_Lwr.h>
  #include <ctscCddStp.h>
  #include <stddef.h>
#endif

#ifdef CDDSTP_CFG_SIMULATION // simulation via e.g. 'RDM'  -  defined in '.\Asr6\Src\Src_AL\Cust\Bw\Bw16\App\Bsw\Cdd\CddStp\CddStpPrj.h'
  #include <CddStp_Simulation.h>
#endif // CDDSTP_CFG_SIMULATION

#include <88XX/CddStp88XX.h>
#include <88XX/CddStp88XXVolt.h>
#include <88XX/CddStp88XXTemp.h>
#include <Dyn/CddStpDyn.h>


STATIC_AL uint32 CddStp_Counter_StartRefRun;

STATIC_AL void           rrCddStp_TgtSig0(void);                                                               // UWY
STATIC_AL Std_ReturnType   CddStp_StartRefRun(tieStepperIndex stepperIndex, ti16StepperPosition_halfsteps position);

#if 0
STATIC_AL Std_ReturnType   CddStp_GetData_Internal(uint32* pulOpTimeHoldCur, uint32* pulOpTimeMoveCur, uint32* pulOpMovedHs, uint8* pucStartRefRunCnt, uint8* pucFinishedRefRunCnt);
#endif

// extern tStpState                         CddStp88XX_aStpState                 [CFA_CNT_STP_88XX]; // UWY
// extern sint16                            CddStp88XX_anRef1Pos                 [CFA_CNT_STP_88XX]; // UWY
// extern tsRte_CddStpActual                   CddStp_ActAll;                                           // UWY

// interface memory area supporting access by virtual addressing for module testing
typedef struct
{
  uint8 ucEnable;
} tCddStp_sTestIfc; // prqa ....

STATIC_AL tCddStp_sTestIfc CddStp_sTestIfc = { 0xFF };     // interface not present

// return address and length of virtual data struct
void* CddStp_GetVirtData_TestIfc(uint32* pulSize)
{
  *pulSize = sizeof(CddStp_sTestIfc);
  return  (void*) (&CddStp_sTestIfc);
}


//-----------------------------------------------------------------------------
/// \brief  Stepper Initialization
///         Currently NOT useful because it is called ONLY AFTER several calls of 'rpCddStp_Cycle0'
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
void riCddStp_Init(void)
{
    #ifdef CDDSTP_ITM
      ITM_TRACE_ENABLE(0xFFFFFFFF);
    #endif

    (void)CddStp_sTestIfc; // suppress QAC Misra warning

    // Stp instance 0
    CddStp88XX_Init(0);

    CddStp88XX_GetState(0); // update CddStp_ActAll with CddStp88XX_aStpState[ucIx]

    (void)Rte_Write_ppCddStpActual0_sStpActualValues(&CddStp_ActAll); // 'CddStp_ActAll' is updated in fct 'CddStp88XX_GetState' (by using CddStp88XX_aStpState[])
}

static volatile boolean boStartTmr = FALSE, boStopTmr = FALSE;
//-----------------------------------------------------------------------------
/// \brief  Cyclic runnable '10ms'
///         This is necessary e.g. in case of missing input signal.
///         FLM3: 'rpCddStp10ms'
//          Usually called via Rte.c: TASK(OsTask_Timing_0_10ms) -> .\FLM3\Asr6\Src\Src_AL\Cdd\CddStp\Gen\CddStp.c: rpCddStp10ms -> CddStp_Cycle10ms -> rpCddStp_Cycle0
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
void rpCddStp_Cycle0(void)
{
  CddStp88XXVolt_StpVoltRng();// jk-tbd
  CddStp8899Temp_CheckLowTemp();

  // Stp instance 0
  rrCddStp_TgtSig0();             // UWY - optimal would be an event controlled call , not cyclic!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  CddStp88XX_Cycle0(0);


  CddStp88XX_GetState(0);                 // update CddStp_ActAll with CddStp88XX_aStpState[ucIx]

  // jk-obsolet: StpActPos.nPos  = CddStp88XX_GetActPos(0);
  // dtg StpActPos.eSigQty       = CddStp88XX_ActPosIsValid(0) ? SIG_VALID : SIG_INVALID;

  // jk-obsolet (void)Rte_Write_CddStp_ActStpSig0_sPos_0_Port(&StpActPos);
  (void)Rte_Write_ppCddStpActual0_sStpActualValues(&CddStp_ActAll); // 'CddStp_ActAll' is updated in fct 'CddStp88XX_GetState' (by using CddStp88XX_aStpState[])

  // PRQA S 5324, 5336 1 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio2) Msg: 5324(HIS metrics violation: 'CddStp88XX_SetCurrent() : STCAL = 10' exceeds threshold 7 for Number of Distinct Function Calls (STCAL).) Depth: 0 Ref: 
}

//-----------------------------------------------------------------------------
/// \brief  This runnable is called on data reception of target value Ver.
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void rrCddStp_TgtSig0(void)
{
    tsRte_CtrlStpTarget StpTgtSig;

    (void)Rte_Read_ppCtrlStpTarget0_StpTargetValues(&StpTgtSig);

// UWY    if(StpTgtSig.eSigQty == SIG_VALID)  // wait for 1st write access to port value
    {
      tCddStpCtrlFct0_DataBuffer sBuffer;

      sBuffer.SoftStop.boSoftStop = StpTgtSig.sLwrTarget.boStop;
      CddStp88XX_CtrlFct0((uint32)CddStp_eCtrlFct0_ModeStop, 0u, &sBuffer.sCtrlData);

      CddStp88XX_SetTgtVal(0, StpTgtSig.sLwrTarget.nPosition, StpTgtSig.sLwrTarget.unMinStepPeriod);

      CddStp88XX_TgtVal(0);

      CddStp88XX_GetState(0);                 // update CddStp_ActAll with CddStp88XX_aStpState[ucIx]
      // jk-obsolet: StpActPos.nPos  = CddStp88XX_GetActPos(0);
      //dtg StpActPos.eSigQty  = CddStp88XX_ActPosIsValid(0) ? SIG_VALID : SIG_INVALID;

      (void)Rte_Write_ppCddStpActual0_sStpActualValues(&CddStp_ActAll);
    }

    // PRQA S 5324 1 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio2) Msg: 5324(HIS metrics violation: 'rrCddStp_TgtSig0() : STCAL = 8' exceeds threshold 7 for Number of Distinct Function Calls (STCAL).) Depth: 0 Ref: 
}


//-----------------------------------------------------------------------------
/// \brief  This runnable is called on data reception of target value Ver.
///
/// \descr  Main entry of 'RTE'
///
/// \param  stepperIndex
/// \param  position
///
/// \return void
//-----------------------------------------------------------------------------
void roCddStpStartRefRun(tieStepperIndex stepperIndex, ti16StepperPosition_halfsteps position)
{
  (void)CddStp_StartRefRun(stepperIndex, position);
}

//-----------------------------------------------------------------------------
/// \brief  CddStp_StartRefRun
///
/// \descr  2nd hop/entry of 'RTE'
///
/// \param  stepperIndex
/// \param  position
///
/// \return STATIC_AL Std_ReturnType
//-----------------------------------------------------------------------------
STATIC_AL Std_ReturnType CddStp_StartRefRun(tieStepperIndex stepperIndex, ti16StepperPosition_halfsteps position)
{
  (void)stepperIndex; // only '1' stepper

  CddStp88XX_anRef1Pos[0] = position;                                 // UWY - see CddStp88XX_Ref1StateFct() in case ActEntry
  CddStp_CtrlFct0((uint32)CddStp_eCtrlFct0_ModeRef, 0u, NULL);        // UWY
  CddStp_Counter_StartRefRun++;                                       // UWY

  return 0;
}

#if 0
//-----------------------------------------------------------------------------
/// \brief  This runnable is called in order to return current Statistic-Data
///
/// \descr  Main entry of 'RTE'
///         SWRS.28287 - 'CddStpGetStepperStatisticData' / 'Rte_Call_ctaaStatM_ppCddStpGetStepperStatisticData_GetData' / 'Rte_Call_ppCddStpGetStepperStatisticData_GetData'
///
/// \param  pulOpTimeHoldCur      - Operating time holding current [ms]
/// \param  pulOpTimeMoveCur      - Operating time movement current [ms]
/// \param  pulOpMovedHs          - Amount of moved half-steps [hs]
/// \param  pucStartRefRunCnt     - Amount of the started reference runs
/// \param  pucFinishedRefRunCnt  - Amount of the finished reference runs 
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType CddStp_GetData(uint32* pulOpTimeHoldCur,                                   // PRQA S 1330 3 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio7) Msg: 1330(The parameter identifiers in this function declaration differ from those in a previous declaration.) Depth: 0 Ref: MISRA C:2012 Rule-8.3
                              uint32* pulOpTimeMoveCur,  uint32* pulOpMovedHs,
                              uint8*  pucStartRefRunCnt, uint8*  pucFinishedRefRunCnt)
{
  return CddStp_GetData_Internal(pulOpTimeHoldCur, pulOpTimeMoveCur, pulOpMovedHs, pucStartRefRunCnt, pucFinishedRefRunCnt);
}


//-----------------------------------------------------------------------------
/// \brief  Called in order to return current Statistic-Data
///
/// \descr  2nd hop/entry of 'RTE'
///
/// \param  pulOpTimeHoldCur      - Operating time holding current [ms]
/// \param  pulOpTimeMoveCur      - Operating time movement current [ms]
/// \param  pulOpMovedHs          - Amount of moved half-steps [hs]
/// \param  pucStartRefRunCnt     - Amount of the started reference runs
/// \param  pucFinishedRefRunCnt  - Amount of the finished reference runs 
///
/// \return STATIC_AL Std_ReturnType
//-----------------------------------------------------------------------------
STATIC_AL Std_ReturnType CddStp_GetData_Internal(uint32* pulOpTimeHoldCur,
                                                 uint32* pulOpTimeMoveCur,  uint32* pulOpMovedHs,
                                                 uint8*  pucStartRefRunCnt, uint8*  pucFinishedRefRunCnt)
{
  // 'tiulCntCmd ulCmd':
  //   CddStp_eCntCmd_GetStpOnTime:    // get stepper on time [msec]                  ##   pBuffer_->GetStpOnTime.ulTime          = CddStp88XX_GetStpOnTime(ucIx);
  //   CddStp_eCntCmd_GetIrunTime:     // get running (moving) motor time [msec]      ##   pBuffer_->GetIrunTime.ulTime           = CddStp88XX_HalStpFct[ucIx].pGetIrunTime();
  //   CddStp_eCntCmd_GetHsCnt:        // get half step count                         ##   pBuffer_->GetHsCnt.ulHsCount           = CddStp88XX_HalStpFct[ucIx].pGetHsCnt();
  //   CddStp_eCntCmd_GetRefStartCnt:  // get count of started of reference runs      ##   pBuffer_->GetRefStartCnt.unRefStartCnt = CddStp88XX_GetRefStartCnt(ucIx);
  //   CddStp_eCntCmd_GetIsRefCnt:     // get count of correct ended reference runs   ##   pBuffer_->GetIsRefCnt.unIsRefCnt       = CddStp88XX_GetIsRefCnt(ucIx);  // CddStp_eCntCmd_GetKlPosDevHistCnts: // get position deviation histogram counters   ##   CddStp88XX_GetAhlPosDevHistCnts(ucIx, pBuffer_->GetKlPosDevHistCnts.aunKlPosDevHistCnts);

  // MilliSeconds & uint32 ('unsigned long') (0 .. 4,294,967,295) -> max 4.294.967.295ms = 4.294.967secs = 71.582,8mins = 1.193hrs = 50days

  uint16 unStartRefRunCnt, unFinishedRefRunCnt;

  // PRQA S 316 5 // program architecture and readability - intentionally no modification of existing code - [I] Cast from a pointer to void to a pointer to object type.) Depth: 0 Ref: MISRA C:2012 Rule-11.5; REFERENCE - ISO:C90-6.3.4 Cast Operators - Semantics
  CddStp88XX_CntFct0((uint32)CddStp_eCntCmd_GetStpOnTime,   0, (tisCntData0*) (void*) pulOpTimeHoldCur);      // get stepper on time [msec]                  
  CddStp88XX_CntFct0((uint32)CddStp_eCntCmd_GetIrunTime,    0, (tisCntData0*) (void*) pulOpTimeMoveCur);      // get running (moving) motor time [msec]      
  CddStp88XX_CntFct0((uint32)CddStp_eCntCmd_GetHsCnt,       0, (tisCntData0*) (void*) pulOpMovedHs);          // get half step count                         
  CddStp88XX_CntFct0((uint32)CddStp_eCntCmd_GetRefStartCnt, 0, (tisCntData0*) (void*) &unStartRefRunCnt);     // get count of started of reference runs      
  CddStp88XX_CntFct0((uint32)CddStp_eCntCmd_GetIsRefCnt,    0, (tisCntData0*) (void*) &unFinishedRefRunCnt);  // get count of correct ended reference runs   

  *pucStartRefRunCnt    = (unStartRefRunCnt    > 255u) ? 255u : (uint8)unStartRefRunCnt;     // RTE comes via uint8 and internal Stp-Handling is via uint16
  *pucFinishedRefRunCnt = (unFinishedRefRunCnt > 255u) ? 255u : (uint8)unFinishedRefRunCnt;  // RTE comes via uint8 and internal Stp-Handling is via uint16

  return 0;
}
#endif

//-----------------------------------------------------------------------------
/// \brief  This runnable is called on CtrlCmd invocation
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void CddStp_CtrlFct0(tiulCtrlCmd ulCmd, tiucCtrlIndex ucIndex, tisCtrlData0* pData)
{
//  tisTgtStpSig0 StpTgtSig = {0, 0, 0};
    tsRte_CtrlStpTarget StpTgtSig = { { 0, TRUE, 0u } };   // LWR
// jk-obsolet: tisActStpSig0 StpActPos;
// jk-obsolet: currently not used      tisStpState0  StpActState;

    (void)Rte_Read_ppCtrlStpTarget0_StpTargetValues(&StpTgtSig);

    CddStp88XX_SetTgtVal(ucIndex, StpTgtSig.sLwrTarget.nPosition, StpTgtSig.sLwrTarget.unMinStepPeriod);
    CddStp88XX_CtrlFct0(ulCmd, ucIndex, pData);

    CddStp88XX_GetState(0);                 // update CddStp_ActAll with CddStp88XX_aStpState[ucIx]
    // jk-obsolet: StpActPos.nPos = CddStp88XX_GetActPos(ucIndex);
    //dtg StpActPos.eSigQty   = CddStp88XX_ActPosIsValid(ucIndex) ? SIG_VALID : SIG_INVALID;

    // jk-obsolet (void)Rte_Write_CddStp_ActStpSig0_sPos_0_Port(&StpActPos);
    (void)Rte_Write_ppCddStpActual0_sStpActualValues(&CddStp_ActAll);
}


// jk-obsolet //-----------------------------------------------------------------------------
// jk-obsolet /// \brief  This runnable is called on ParaCmd invocation
// jk-obsolet ///
// jk-obsolet /// \param  
// jk-obsolet ///
// jk-obsolet /// \return void
// jk-obsolet //-----------------------------------------------------------------------------
// jk-obsolet void roCddStp_ParaFct0(const tParaFct0_Cmd eCmd, const tNvmPara_CodingArea* const pData)
// jk-obsolet {
// jk-obsolet   // PRQA S 311 2 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio7) Msg: 311(Dangerous pointer cast results in loss of const qualification.) Depth: 0 Ref: MISRA C:2012 Rule-11.8
// jk-obsolet   // PRQA S 316 1 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio5) Msg: 316([I] Cast from a pointer to void to a pointer to object type.) Depth: 0 Ref: MISRA C:2012 Rule-11.5; REFERENCE - ISO:C90-6.3.4 Cast Operators - Semantics
// jk-obsolet   CddStp88XX_ParaFct0((tiulParaCmd) eCmd, 0, (tisParaData0*) (void*) pData); // prqa ....
// jk-obsolet }


// jk-obsolet //-----------------------------------------------------------------------------
// jk-obsolet /// \brief  This runnable is called on CntCmd invocation
// jk-obsolet ///
// jk-obsolet /// \param  
// jk-obsolet ///
// jk-obsolet /// \return void
// jk-obsolet //-----------------------------------------------------------------------------
// jk-obsolet void roCddStp_CntFct0(tiulCntCmd ulCmd, tiucCntIndex ucIndex, tisCntData0* pData)
// jk-obsolet {
// jk-obsolet      CddStp88XX_CntFct0(ulCmd, ucIndex, pData);
// jk-obsolet }


// jk-obsolet //-----------------------------------------------------------------------------
// jk-obsolet /// \brief  This runnable is called on DataReception of StpEvent0_sTrigger
// jk-obsolet ///
// jk-obsolet /// \descr  
// jk-obsolet ///
// jk-obsolet /// \param  - 
// jk-obsolet ///
// jk-obsolet /// \return void 
// jk-obsolet //-----------------------------------------------------------------------------
// jk-obsolet void rrCddStp_Event0(void)
// jk-obsolet {
// jk-obsolet    CddStp88XX_Event(0, CDDSTP_eStandardEvent);
// jk-obsolet }


//EOF

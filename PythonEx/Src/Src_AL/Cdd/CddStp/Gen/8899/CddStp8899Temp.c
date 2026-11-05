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
/// \file   CddStp8899Temp.c
///
/// \brief  Complex driver for DRV8899 stepper control temperature state machine
///
/// \descr  Temperature state machine in addition to stepper state machine.
///
///         There are 3 main states (stored in array-var 'CddStp88XX_aeTemp'):
///            * CddStp_eTempState_NormTemp = 0  -  must be 0 (init. value)
///            * CddStp_eTempState_LowTemp  = 1  -  this is MAX only ONCE valid during one Power-Cycle: During startup for a predefined amount of time
///            * CddStp_eTempState_HighTemp = 2  -  depends on 'RegDiag2.Bit.u1OTW'
///
///         Additional handling of:
///            * 'bIsLowtemp'   -   independened of state 'CddStp_eTempState_LowTemp'
///
/// \author Wuesteney, Ulrich ALRT/EEG4 * (wu82rt)
///         J. Kling ALRT-EES6 (f84304b)
//-----------------------------------------------------------------------------


//=============================================================================
// includes
//=============================================================================
#include <Std_Types.h>
#include <AL_Helper.h> //-- STATIC_AL

#ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
  #include <../../Cust/St/St126/Cdd/CddStp/CddStpPrj.h>

  #include <CddStpData.h>
  #include <CodM_Para/CodM_Para_System.h>
#else // Unit-Tests!
  //#define CFA_CNT_STP_88XX   (4u)
  #include <CddStpPrj.h>
  #include <CddStpData.h>
  #include <CodM_Para/CodM_Para_System.h>
#endif

#ifdef CDDSTP_CFG_SIMULATION // defined in '.\Asr6\Src\Src_AL\Cust\Bw\Bw16\App\Bsw\Cdd\CddStp\CddStpPrj.h'
  #include <CddStp_Simulation.h>
#endif // CDDSTP_CFG_SIMULATION

#include <Util_Time.h>

#include <CddStpCfg.h>
#include <CddStpIfc.h>

#include <88XX/CddStp88XX.h>   
#include <8899/CddStp8899Com.h>
#include <88XX/CddStp88XX.h>   
#include <88XX/_CddStp88XX.h>  
#include <88XX/CddStp88XXTemp.h>



// ---------------------------------------------------------------------------
// local prototypes
// ---------------------------------------------------------------------------
STATIC_AL uint32 CddStp8899Temp_TransitionInitNorm  (uint8 ucIx, const tCommandCddStp88XX eCmd);
STATIC_AL uint32 CddStp8899Temp_TransitionNormLow   (uint8 ucIx, const tCommandCddStp88XX eCmd);
STATIC_AL uint32 CddStp8899Temp_TransitionNormHigh  (uint8 ucIx, const tCommandCddStp88XX eCmd);
STATIC_AL uint32 CddStp8899Temp_TransitionLowNorm   (uint8 ucIx, const tCommandCddStp88XX eCmd);
STATIC_AL uint32 CddStp8899Temp_TransitionHighNorm  (uint8 ucIx, const tCommandCddStp88XX eCmd);
STATIC_AL uint32 CddStp8899Temp_TransitionLowHigh   (uint8 ucIx, const tCommandCddStp88XX eCmd);

STATIC_AL void   CddStp8899Temp_StateFctInit        (uint8 ucIx, tAction Action);
STATIC_AL void   CddStp8899Temp_StateFctNorm        (uint8 ucIx, tAction Action);
STATIC_AL void   CddStp8899Temp_StateFctLow         (uint8 ucIx, tAction Action);
STATIC_AL void   CddStp8899Temp_StateFctHigh        (uint8 ucIx, tAction Action);


// ---------------------------------------------------------------------------
// preprocessor definitions
// ---------------------------------------------------------------------------
#define CDDSTP8899_WaitErrPrealarm_FTimer        FT_SEC(CDDSTP_ErrPrealarmTime) // duration of thermal warning to set ErrPrealarm state message bit [s]

//NVM #define CDDSTP8899_WaitMinHT_FTimer        FT_SEC(CDDSTP_HighTempMinTime) // minimal duration of high temperature state [s]
//NVM #define CDDSTP8899_WaitDurLT_FTimer        FT_SEC(CDDSTP_LowTempDuration) // minimal duration of low  temperature state [s]


// ---------------------------------------------------------------------------
// vars
// ---------------------------------------------------------------------------

tCddStpTempState              CddStp88XX_aeTemp[CFA_CNT_STP_88XX];

//STATIC_AL tFTimer           CddStp88XX_astWaitErrPrealarm[CFA_CNT_STP_88XX];

STATIC_AL tFTimer             CddStp88XX_astWaitMinHT[CFA_CNT_STP_88XX];
STATIC_AL tFTimer             CddStp88XX_astWaitDurLT[CFA_CNT_STP_88XX];

#if (CFG_DEV_HOOK_EN == 1u) // tester hook
volatile uint32 CddStp_ulTesterHookActivation = 0u;
#endif
//=============================================================================
// Public functions  implementation
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  CddStp8899Temp_CheckLowTemp
///
/// \descr  Check the low temperature for LWR
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void CddStp8899Temp_CheckLowTemp(void)
{
  // EFT & Cod valid ?
  if (CddStp_ActAll.sLwrActual.sStatusError.eStatSupported == (tieSupportInfo)SUPPORT_YES) //  depends on PAV/EFT & Coding and on validity of them
  {
    STATIC_UT(boolean, bIsLowtemp, FALSE);
#if defined (UNIT_TEST)
    extern uint8 ucQuelle;
#else
    uint8 ucQuelle;
#endif
    tis32Temperature_mCelsius temperature;
    tCddStpCtrlFct0_DataBuffer sBuffer;

    // jk-tbd: should be somewhere in Coding-Data = CddStpData.c
    //(void)Rte_Call_ppCodingData0_GetSTP_QUELLE_TT(&ucQuelle); // Source of temp.: 1..12=NTC1-12, 16=PCB, 17=CAN - SWRS.27423
    if (ucQuelle == 16u) // PCB-Temperature? (N.b.: Future use will be probably 0 or 1 or 2 !!!)
    {
      // PRQA S 288 1 // warning - QAC(Prio6) Msg: 288([I] Source file 'C:/temp/FLM3/Asr6/Src/Src_AL/Cdd/CddStp/Gen/8899/CddStp8899Temp.c' has comments containing characters which are not members of the basic source character set.) Depth: 0 Ref: MISRA C:2012 Dir-1.1; REFERENCE - ISO:C90-5.2.1 Character Sets
     // (void)Rte_Read_ppRSensPcbTemperature0_lActual(&temperature);    // PCB-NTC - SWRS.27695 - 23,45°C = '23450'
      temperature = temperature / 1000;
    }
    else if (ucQuelle == 17u) // CAN-Temperature? (N.b.: Future use will be probably 0 or 1 or 2 !!!)
    {
     // (void)Rte_Read_ppSigPrepATemp_lActual(&temperature) ;            // CAN     - SWRS.27697 - 23°C    = '23'
      temperature = temperature / 1000;
    }
    else
    {
      // not supported
      temperature = 25; // 25°C
    }

    temperature += 40; // add 'Coding'-Offset

    // Low-Temp? (e.g. 'Cod_StpWertTT' = '30'   ->  = '-10°C') (see 'Bit.Lowtemp' and 'LowTemp.boLT', too)
    bIsLowtemp = ((uint8)temperature < Cod_StpWertTT()) ? TRUE : FALSE; // 'Cod_StpWertTT()': [Deg + 40] Temperaturgrenzwert, unter dem der Tieftemperaturmodus aktiviert wird
   
#ifdef CDDSTP_CFG_SIMULATION // defined in '.\Asr6\Src\Src_AL\Cust\Bw\Bw16\App\Bsw\Cdd\CddStp\CddStpPrj.h'
    // simulation
    if (CddStp_Simulation_IsSimActive() != FALSE)
    {
      bIsLowtemp = CddStp_Simulation_HandleLowTempMode();
    }
#endif // CDDSTP_CFG_SIMULATION

#if (CFG_DEV_HOOK_EN == 1u)
    if (CddStp_ulTesterHookActivation == CDDSTP_UTW_HOOK_KEY)
    {
      bIsLowtemp = TRUE;
    }
    else if (CddStp_ulTesterHookActivation == CDDSTP_RESET_HOOK_KEY)
    {
      bIsLowtemp = FALSE;
    }
    else
    {
      // nothing to do
    }
#endif

    sBuffer.LowTemp.boLT = bIsLowtemp;
    CddStp88XX_CtrlFct0((uint32)CddStp_eCtrlFct0_LowTemp, 0u, &sBuffer.sCtrlData);
  }
  else
  {
  }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Stepper Temperature StateMachine transition functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ---------------------------------------------------------------------------
///
///  \func     CddStp8899Temp_TransitionInitNorm
///
///  \brief    Ix transition function from StateTempInit to StateTempNorm
///
///  \param    uint8 ucIx
///            const tCommandCddStp88XX eCmd
///
///  \return   uint32
///            = TRUE:  condition is valid
///            = FALSE: condition is not valid
///
///  \descr    Temperature handling
///
// ---------------------------------------------------------------------------
STATIC_AL uint32 CddStp8899Temp_TransitionInitNorm(uint8 ucIx, const tCommandCddStp88XX eCmd)
{
  // only valid in Unit-Tests
  CddStp_UnitTest_Printf("                      *#*#*#*#*#*#*#* JK - CddStp8899Temp_TransitionInitNorm\n");

  (void)ucIx;
  (void)eCmd;
  return TRUE;
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp8899Temp_TransitionNormLow
///
///  \brief    Ix transition function from StateTempNorm to StateTempLow
///
///  \param    uint8 ucIx
///            const tCommandCddStp88XX eCmd
///
///  \return   uint32
///            = TRUE:  condition is valid
///            = FALSE: condition is not valid
///
///  \descr    Temperature handling
///
// ---------------------------------------------------------------------------
STATIC_AL uint32 CddStp8899Temp_TransitionNormLow(uint8 ucIx, const tCommandCddStp88XX eCmd)
{
  // only valid in Unit-Tests
  CddStp_UnitTest_Printf("                      *#*#*#*#*#*#*#* JK - CddStp8899Temp_TransitionNormLow\n");

  CDDSTP88XX_OptimizeArrayIndex(ucIx)

  (void)eCmd;
  return (   (CddStp88XX_aBitsMod[ucIx].Bit.biLockLT == 0u)      // low temperature state not locked in this power on cycle?
          && (CddStp88XX_aBits[ucIx].Bit.biLT == 1u)) ? 1u : 0u; // low temperature?
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp8899Temp_TransitionNormHigh
///
///  \brief    Ix transition function from StateTempNorm to StateTempHigh
///
///  \param    uint8 ucIx
///            const tCommandCddStp88XX eCmd
///
///  \return   uint32
///            = TRUE:  condition is valid
///            = FALSE: condition is not valid
///
///  \descr    Temperature handling
///
// ---------------------------------------------------------------------------
STATIC_AL uint32 CddStp8899Temp_TransitionNormHigh(uint8 ucIx, const tCommandCddStp88XX eCmd)
{
  // only valid in Unit-Tests
  CddStp_UnitTest_Printf("                      *#*#*#*#*#*#*#* JK - CddStp8899Temp_TransitionNormHigh\n");

  tCddStp8899Com_StatReg_Diag2 stRegDiag2;  // Diag-Status-2  -  UTW | OTW | OTS | RSVD | OL_B | OL_A

  CDDSTP88XX_OptimizeArrayIndex(ucIx)

  (void)eCmd;

  // update local Data-Mirror ('CddStp8899_aSRegXXX') of necessary HW-Status-Registers ('CddStp8899Com_DataMirror.StatvRx.aSRegXXX')
  // get Status-Register-Diag-2 contents from RAM mirror (verified)
  (void)CddStp8899Com_GetSRegDiag2(ucIx, &stRegDiag2.ucRaw);

  // PRQA S 3344, 4559 1 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio7) Msg: 3344(Controlling expression is not an 'essentially Boolean' expression.) Depth: 0 Ref: MISRA C:2012 Rule-14.4 | warning - QAC(Prio7) Msg: 4559(An expression of 'essentially unsigned' type (unsigned char) is being used as the first operand of this conditional operator (?).) Depth: 0 Ref: MISRA C:2012 Rule-10.1
  return (stRegDiag2.Bit.u1OTW != 0u) ? 1u : 0u;
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp8899Temp_TransitionLowNorm
///
///  \brief    Ix transition function from StateTempLow to StateTempNorm
///
///  \param    uint8 ucIx
///            const tCommandCddStp88XX eCmd
///
///  \return   uint32
///            = TRUE:  condition is valid
///            = FALSE: condition is not valid
///
///  \descr    Temperature handling
///
// ---------------------------------------------------------------------------
STATIC_AL uint32 CddStp8899Temp_TransitionLowNorm(uint8 ucIx, const tCommandCddStp88XX eCmd)
{
  // only valid in Unit-Tests
  CddStp_UnitTest_Printf("                      *#*#*#*#*#*#*#* JK - CddStp8899Temp_TransitionLowNorm\n");

  CDDSTP88XX_OptimizeArrayIndex(ucIx)

  (void)eCmd;

  // PRQA S 4558 2 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio7) Msg: 4558(An expression of 'essentially unsigned' type (unsigned char) is being used as the right-hand operand of this logical operator (&&).) Depth: 0 Ref: MISRA C:2012 Rule-10.1
  if (   (CddStp88XX_aBitsMod[ucIx].Bit.biWaitDurLT == 1u)
      && (FastTimerTimeout(CddStp88XX_astWaitDurLT[ucIx])))
  {
    CddStp88XX_aBitsMod[ucIx].Bit.biWaitDurLT = 0;
    CddStp88XX_aBitsMod[ucIx].Bit.biLockLT = 1;            // low temperature state locked in this power on cycle
  }

  return (CddStp88XX_aBitsMod[ucIx].Bit.biWaitDurLT == 0u) ? 1u : 0u; // (not compatible to Afs2) - support clear of CddStp88XX_aBitsMod[] in CddStp8899 state machine Init state
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp8899Temp_TransitionHighNorm
///
///  \brief    Ix transition function from StateTempHigh to StateTempNorm
///
///  \param    uint8 ucIx
///            const tCommandCddStp88XX eCmd
///
///  \return   uint32
///            = TRUE:  condition is valid
///            = FALSE: condition is not valid
///
///  \descr    Temperature handling
///
// ---------------------------------------------------------------------------
STATIC_AL uint32 CddStp8899Temp_TransitionHighNorm(uint8 ucIx, const tCommandCddStp88XX eCmd)
{
  // only valid in Unit-Tests
  CddStp_UnitTest_Printf("                      *#*#*#*#*#*#*#* JK - CddStp8899Temp_TransitionHighNorm\n");

  tCddStp8899Com_StatReg_Diag2 stRegDiag2;  // Diag-Status-2  -  UTW | OTW | OTS | RSVD | OL_B | OL_A

  CDDSTP88XX_OptimizeArrayIndex(ucIx)

  (void)eCmd;

  // update local Data-Mirror ('CddStp8899_aSRegXXX') of necessary HW-Status-Registers ('CddStp8899Com_DataMirror.StatvRx.aSRegXXX')
  // get Status-Register-Diag-2 contents from RAM mirror (verified)
  (void)CddStp8899Com_GetSRegDiag2(ucIx, &stRegDiag2.ucRaw);
  
  // PRQA S 4558 2 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio7) Msg: 4558(An expression of 'essentially unsigned' type (unsigned char) is being used as the right-hand operand of this logical operator (&&).) Depth: 0 Ref: MISRA C:2012 Rule-10.1
  if (   (CddStp88XX_aBitsMod[ucIx].Bit.biWaitMinHT == 1u)
      && (FastTimerTimeout(CddStp88XX_astWaitMinHT[ucIx])))
  {
    CddStp88XX_aBitsMod[ucIx].Bit.biWaitMinHT = 0;
  }

  return (   (CddStp88XX_aBitsMod[ucIx].Bit.biWaitMinHT == 0u)
          && (stRegDiag2.Bit.u1OTW == 0u)) ? 1u : 0u;
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp8899Temp_TransitionLowHigh
///
///  \brief    Ix transition function from StateTempLow to StateTempHigh
///
///  \param    uint8 ucIx
///            const tCommandCddStp88XX eCmd
///
///  \return   uint32
///            = TRUE:  condition is valid
///            = FALSE: condition is not valid
///
///  \descr    Temperature handling
///
// ---------------------------------------------------------------------------
STATIC_AL uint32 CddStp8899Temp_TransitionLowHigh(uint8 ucIx, const tCommandCddStp88XX eCmd)
{
  // only valid in Unit-Tests
  CddStp_UnitTest_Printf("                      *#*#*#*#*#*#*#* JK - CddStp8899Temp_TransitionLowHigh\n");

  return (uint32) (CddStp8899Temp_TransitionNormHigh(ucIx, eCmd));
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// StateMachine state functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ---------------------------------------------------------------------------
///
///  \func     CddStp8899Temp_StateFctInit
///
///  \brief    ucIx Temperature Init state function to handle state CddStp88XX_eStateTempInit
///
///  \param    uint8 ucIx
///            tAction Action
///
///  \return   none
///
///  \descr
///
// ---------------------------------------------------------------------------
STATIC_AL void CddStp8899Temp_StateFctInit(uint8 ucIx, tAction Action)
{
  (void)ucIx;
  switch (Action)
  {
    case ActEntry: // perform entry action
    {
      // empty
      break;
    }

    case ActDo:    // perform do activity
    {
      // empty
      break;
    }

    case ActExit:  // perform exit action // used because this state is first state of state machine (init)
    {
//A   CddStp88XX_DemReportErrorStatus(ucIx, CddStp88XX_eDemEType_TempWarn, ERRLOG_NoDetecting);       // no detecting of thermal warning info active
     // CddStp88XX_DemReportErrorStatus(ucIx, CddStp88XX_eDemEType_TempWarn, DEM_EVENT_STATUS_PASSED);  // no thermal warning info
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
}


// ---------------------------------------------------------------------------
///
///  \func     CddStp8899Temp_StateFctNorm
///
///  \brief    ucIx Temperature Norm state function to handle state CddStp88XX_eStateTempNorm
///
///  \param    uint8 ucIx
///            tAction Action
///
///  \return   none
///
///  \descr
///
// ---------------------------------------------------------------------------
STATIC_AL void CddStp8899Temp_StateFctNorm(uint8 ucIx, tAction Action)
{
  switch (Action)
  {
    case ActEntry: // perform entry action
    {
      CddStp88XX_aeTemp[ucIx] = CddStp_eTempState_NormTemp;

      CddStp88XX_HalStpFct[ucIx].pHandleCurAmplt((uint8)CDDSTP88XX_eCurAmpltStateNoChange, CddStp88XX_aucCurAmpltHoldTemp[ucIx][CddStp88XX_aeTemp[ucIx]], CddStp88XX_aucCurAmpltRunTemp[ucIx][CddStp88XX_aeTemp[ucIx]]); // switch to hold or normal current depending on actual temperature

      Rte_Call_DemPrj_ReportErrorStatus((uint16)STP_OTW, DEM_EVENT_STATUS_PASSED); // clear thermal warning DTC
      break;
    }

    case ActDo:    // perform do activity
    case ActExit:  // perform exit action // used because this state is first state of state machine (init)
    {
      CddStp88XX_aBitsMod[ucIx].Bit.biExitLT = 0;
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
///  \func     CddStp8899Temp_StateFctLow
///
///  \brief    ucIx Temperature Low state function to handle state CddStp88XX_eStateTempLow
///
///  \param    uint8 ucIx
///            tAction Action
///
///  \return   none
///
///  \descr
///
// ---------------------------------------------------------------------------
STATIC_AL void CddStp8899Temp_StateFctLow(uint8 ucIx, tAction Action)
{
  switch (Action)
  {
    case ActEntry: // perform entry action
    {
      CddStp88XX_aeTemp[ucIx] = CddStp_eTempState_LowTemp;

      CddStp88XX_HalStpFct[ucIx].pHandleCurAmplt((uint8)CDDSTP88XX_eCurAmpltStateNoChange, CddStp88XX_aucCurAmpltHoldTemp[ucIx][CddStp88XX_aeTemp[ucIx]]
                                                                                         , CddStp88XX_aucCurAmpltRunTemp[ ucIx][CddStp88XX_aeTemp[ucIx]]); // switch to hold or normal current depending on actual temperature (normally high current)

      CddStp88XX_aBitsMod[ucIx].Bit.biWaitDurLT = 1;
//NVM CddStp88XX_astWaitDurLT[ucIx] = FastTimerStart(CDDSTP8899_WaitDurLT_FTimer);
      CddStp88XX_astWaitDurLT[ucIx] = FastTimerStart(FT_SEC(Cod_StpZeitTT()));
      break;
    }

    case ActDo:    // perform do activity
    {
      //  keine CddStp88XX_HalStpLwr_SendSRegX()-Funktionen, da sowieso immer alle StatusRegister gelesen werden
      //(void)CddStp88XX_HalStpFct[ucIx].pSpiSendSRegAll();      // update all the status registers to detect SC Error
      break;
    }

    case ActExit:  // perform exit action // used because this state is first state of state machine (init)
    {
    //  keine CddStp88XX_HalStpLwr_SendSRegX()-Funktionen, da sowieso immer alle StatusRegister gelesen werden
      //(void)CddStp88XX_HalStpFct[ucIx].pSpiSendSRegAll();      // read all the status registers to clear the error bit: OL Error at low temperature
      CddStp88XX_aBitsMod[ucIx].Bit.biExitLT = 1;
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
///  \func     CddStp8899Temp_StateFctHigh
///
///  \brief    ucIx Temperature High state function to handle state CddStp88XX_eStateTempHigh
///
///  \param    uint8 ucIx
///            tAction Action
///
///  \return   none
///
///  \descr
///
// ---------------------------------------------------------------------------
STATIC_AL void CddStp8899Temp_StateFctHigh(uint8 ucIx, tAction Action)
{
  STATIC_UT_NOINIT(TIMER, CddStp88XX_astWaitErrPrealarm[CFA_CNT_STP_88XX]);

  switch (Action)
  {
    case ActEntry: // perform entry action
    {
      CddStp88XX_aeTemp[ucIx] = CddStp_eTempState_HighTemp;
      
      CddStp88XX_HalStpFct[ucIx].pHandleCurAmplt((uint8)CDDSTP88XX_eCurAmpltStateNoChange, CddStp88XX_aucCurAmpltHoldTemp[ucIx][CddStp88XX_aeTemp[ucIx]], CddStp88XX_aucCurAmpltRunTemp[ucIx][CddStp88XX_aeTemp[ucIx]]); // switch to hold or normal current depending on actual temperature (normally low current)

      //CddStp88XX_DemReportErrorStatus(ucIx, CddStp88XX_eDemEType_TempWarn, DEM_EVENT_STATUS_FAILED);  // thermal warning info

      Rte_Call_DemPrj_ReportErrorStatus((uint16)STP_OTW, DEM_EVENT_STATUS_FAILED); // set thermal warning DTC

      CddStp88XX_aBitsMod[ucIx].Bit.biWaitErrPrealarm = 1;
      CddStp88XX_astWaitErrPrealarm[ucIx] = FastTimerStart(CDDSTP8899_WaitErrPrealarm_FTimer);
      CddStp88XX_aBitsMod[ucIx].Bit.biWaitMinHT = 1;
//NVM CddStp88XX_astWaitMinHT[ucIx] = FastTimerStart(CDDSTP8899_WaitMinHT_FTimer);
      CddStp88XX_astWaitMinHT[ucIx] = FastTimerStart(FT_SEC(Cod_StpZeitHT()));
      break;
    }

    case ActDo:    // perform do activity
    {
      // PRQA S 4558 2 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio7) Msg: 4558(An expression of 'essentially unsigned' type (unsigned char) is being used as the right-hand operand of this logical operator (&&).) Depth: 0 Ref: MISRA C:2012 Rule-10.1
      if (   (CddStp88XX_aBitsMod[ucIx].Bit.biWaitErrPrealarm == 1u)
          && (FastTimerTimeout(CddStp88XX_astWaitErrPrealarm[ucIx])))
      {
        tCddStp8899Com_StatReg_Diag2 stRegDiag2;  // Diag-Status-2  -  UTW | OTW | OTS | RSVD | OL_B | OL_A

        // update local Data-Mirror ('CddStp8899_aSRegXXX') of necessary HW-Status-Registers ('CddStp8899Com_DataMirror.StatvRx.aSRegXXX')
        // get Status-Register-Diag-2 contents from RAM mirror (verified)
        (void)CddStp8899Com_GetSRegDiag2(ucIx, &stRegDiag2.ucRaw);

        if ((stRegDiag2.Bit.u1OTW) != 0u)                                 // thermal warning bit set?
        {
          CddStp88XX_aStpState[ucIx].Bit.ErrPrealarm = 1;                                  // overtemperature warning: after prealarm configuration time
//!       CddStp88XX_HalStpFct[ucIx].pHandleMotEn(FALSE, TRUE,FALSE);                      // disable stepper motor driver
        }
        CddStp88XX_aBitsMod[ucIx].Bit.biWaitErrPrealarm = 0;
      }

      CddStp88XX_aBitsMod[ucIx].Bit.biExitLT = 0;
      break;
    }

    case ActExit:  // perform exit action // used because this state is first state of state machine (init)
    {
//      CddStp88XX_DemReportErrorStatus(ucIx, CddStp88XX_eDemEType_TempWarn, DEM_EVENT_STATUS_PASSED);  // no thermal warning info

      CddStp88XX_aBitsMod[ucIx].Bit.biExitLT = 0;

      CddStp88XX_aStpState[ucIx].Bit.ErrPrealarm = 0;                                      // no overtemperature warning
//!   CddStp88XX_HalStpFct[ucIx].pHandleMotEn(TRUE, TRUE, FALSE);                          // enable stepper motor driver
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
// Stepper Temperature StateMachine transition function tables
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ---------------------------------------------------------------------------
// Stepper Temperature Transition function table for ucIx state CddStp88XX_eStateTempInit
// ---------------------------------------------------------------------------
STATIC_AL const tTempTransitionCddStp88XX CddStp8899_atTransitionTempInit[] =
{
  //  new state                  transition function
  { CddStp88XX_eStateTempNorm,  CddStp8899Temp_TransitionInitNorm}
};

// ---------------------------------------------------------------------------
// Stepper Temperature Transition function table for ucIx state CddStp88XX_eStateTempNorm
// ---------------------------------------------------------------------------
STATIC_AL const tTempTransitionCddStp88XX CddStp8899_atTransitionTempNorm[] =
{
  //  new state                  transition function
  { CddStp88XX_eStateTempHigh,  CddStp8899Temp_TransitionNormHigh}, // (not compatible to Afs2) - check StateHigh before StateLow to avoid transition to Low in case of Thermal Warning of driver to save the driver
  { CddStp88XX_eStateTempLow,   CddStp8899Temp_TransitionNormLow }
};

// ---------------------------------------------------------------------------
// Stepper Temperature Transition function table for ucIx state CddStp88XX_eStateTempLow
// ---------------------------------------------------------------------------
STATIC_AL const tTempTransitionCddStp88XX CddStp8899_atTransitionTempLow[] =
{
  //  new state                  transition function
  { CddStp88XX_eStateTempHigh,  CddStp8899Temp_TransitionLowHigh }, // (not compatible to Afs2) - check StateHigh before StateNorm to avoid transition to Norm in case of Thermal Warning of driver to save the driver
  { CddStp88XX_eStateTempNorm,  CddStp8899Temp_TransitionLowNorm }
};

// ---------------------------------------------------------------------------
// Stepper Temperature Transition function table for ucIx state CddStp88XX_eStateTempHigh
// ---------------------------------------------------------------------------
STATIC_AL const tTempTransitionCddStp88XX CddStp8899_atTransitionTempHigh[] =
{
  //  new state                  transition function
  { CddStp88XX_eStateTempNorm,  CddStp8899Temp_TransitionHighNorm},
};


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Stepper Temperature StateMachine table and function
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ---------------------------------------------------------------------------
// Stepper Temperature State machine table for ucIx complex driver DRV8899
// ---------------------------------------------------------------------------

STATIC_AL CONST_AL tTempStateMachineCddStp88XXSF CddStp8899_atTempStateMachine[CddStp88XX_eMaxStatesTemp] =
{ //   state name                      transition count                            transition table                  state function
  { /* CddStp88XX_eStateTempInit, */  UTIL_COUNTOF(CddStp8899_atTransitionTempInit),  CddStp8899_atTransitionTempInit, CddStp8899Temp_StateFctInit },
  { /* CddStp88XX_eStateTempNorm, */  UTIL_COUNTOF(CddStp8899_atTransitionTempNorm),  CddStp8899_atTransitionTempNorm, CddStp8899Temp_StateFctNorm },
  { /* CddStp88XX_eStateTempLow,  */  UTIL_COUNTOF(CddStp8899_atTransitionTempLow),   CddStp8899_atTransitionTempLow,  CddStp8899Temp_StateFctLow  },
  { /* CddStp88XX_eStateTempHigh, */  UTIL_COUNTOF(CddStp8899_atTransitionTempHigh),  CddStp8899_atTransitionTempHigh, CddStp8899Temp_StateFctHigh }
};


// ---------------------------------------------------------------------------
///
///  \func     CddStp8899Temp_StateMachine
///
///  \brief    ucIx stepper temperature state machine
///
///  \param    uint8 ucIx
///            tCommandCddStp88XX eCmd
///
///  \return   none
///
///  \descr
///
// ---------------------------------------------------------------------------
void CddStp88XXTemp_StateMachine(uint8 ucIx, const tCommandCddStp88XX eCmd)
{
  STATIC_UT_NOINIT(tStateTempCddStp88XX, CddStp88XX_aeTempState[CFA_CNT_STP_88XX]);

  // Temp-State-Debugging
  // tStateTempCddStp88XX CddStp88XX_aeTempOldState[CFA_CNT_STP_88XX]; // Temp-State-Debugging

  //lint -esym(727, CddStp88XX_aeTempState) Symbol not explicitly initialized
  tStateTempCddStp88XX eStateBegin = CddStp88XX_aeTempState[ucIx];

  CDDSTP88XX_OptimizeArrayIndex(ucIx)

  // jk-tbd STP_RUNTIME_INTDIS_START(CddStp8899Temp_StateMachine)

  //  Temp-State-Debugging
  //
  //  if (CddStp88XX_aeTempOldState[ucIx] != eStateBegin) // ignore same state of this state machine to avoid too much entries in buffer
  //  {
  //    CddStp8899_DebugStateTempTracking(ucIx, eStateBegin); // +++ debug code for tracking Temperature StateMachine states +++

  //    // Save current state of the machine state
  //    CddStp88XX_aeTempOldState[ucIx] = eStateBegin;
  //  }

  // Execute state machine
  {
    boolean                                 boBreak        = FALSE;
    tStateTempCddStp88XX                   eNewState_     = eStateBegin;
    const tStateFctPtrCddStp88XX           pOldStateFct   = CddStp8899_atTempStateMachine[eStateBegin].pStateFct;
    const tTempTransitionCddStp88XX*       pTransition_   = CddStp8899_atTempStateMachine[eStateBegin].pTransition;
    const tTempTransitionCddStp88XX* const pTransitionEnd = &pTransition_[CddStp8899_atTempStateMachine[eStateBegin].ucCount];

    // only valid in Unit-Tests
    CddStp_UnitTest_Printf("                      *#*#*#*#*#*#*#* JK - CddStp88XXTemp_StateMachine (eStateBegin=%d, pTransition_=0x%X) *#*#*#*#*#*#*#*\n", eStateBegin, pTransition_);

    // PRQA S 4558 1 // warning - QAC(Prio7) Msg: 4558(An expression of 'essentially unsigned' type (unsigned char) is being used as the  operand of this logical operator (!).) Depth: 0 Ref: MISRA C:2012 Rule-10.1
    for ( ; ( (pTransition_ < pTransitionEnd) && (!boBreak) ); pTransition_++)
    {
      // only valid in Unit-Tests
      CddStp_UnitTest_Printf("                      *#*#*#*#*#*#*#* JK - CddStp88XXTemp_StateMachine - 2 - State-Change-Check\n");

      // Check transition condition
      if ( pTransition_->ptTransitionFct(ucIx, eCmd) != FALSE)
      {
        // only valid in Unit-Tests
        CddStp_UnitTest_Printf("                      *#*#*#*#*#*#*#* JK - CddStp88XXTemp_StateMachine - 3 - new state\n");

        // Ok, transition condition complied, get the the new state
        eNewState_ = pTransition_->eNewState;
        #ifdef CDDSTP_ITM
          // N.b.: '_channel_' (=index) has to be 1...30  (1...x1E)
          // 24+2 = 'E0000068'
          ITM_TRACE_D8(24+2, (uint8)eNewState_); // CddStp88XX_eStateTempInit = 0,  CddStp88XX_eStateTempNorm = 1,  CddStp88XX_eStateTempLow = 2,  CddStp88XX_eStateTempHigh = 3
        #endif

        // Call actual state exit action
        if ( pOldStateFct != (tStateFctPtrCddStp88XX)0 )
        {
          pOldStateFct(ucIx, ActExit);
        }

        // Call new state entry action
        if ( CddStp8899_atTempStateMachine[eNewState_].pStateFct != (tStateFctPtrCddStp88XX)0 )
        {
          CddStp8899_atTempStateMachine[eNewState_].pStateFct(ucIx, ActEntry);
        }

        // Assign the new state to the state variable
        CddStp88XX_aeTempState[ucIx] = eNewState_;

        // Leave the for loop
        boBreak = TRUE;
      }
    }

    // only valid in Unit-Tests
    CddStp_UnitTest_Printf("                      *#*#*#*#*#*#*#* JK - CddStp88XXTemp_StateMachine - 4 - State-Change-Check ready\n");

    if ( (eStateBegin == eNewState_) && (pOldStateFct != (tStateFctPtrCddStp88XX)0) )
    {
      // only valid in Unit-Tests
      CddStp_UnitTest_Printf("                      *#*#*#*#*#*#*#* JK - CddStp88XXTemp_StateMachine - 5 - NO change\n");

      // Call ActDo activity because state was not changed and a state function exist.
      pOldStateFct(ucIx, ActDo);
    }
  }

  // common code ...

  // jk-tbd STP_RUNTIME_INTDIS_STOP(CddStp8899Temp_StateMachine)
}

//EOF

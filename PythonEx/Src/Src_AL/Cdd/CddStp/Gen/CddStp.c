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
/// \file  CddStp.c
///
/// \brief
///
/// \author J. Kling ALRT-EES6 (f84304b)
///
//-----------------------------------------------------------------------------

//=============================================================================
//  includes
//=============================================================================
#include <Std_Types.h>
#include <AL_Helper.h> //-- STATIC_AL
//#include <Gpt.h>        // C:\temp\FLM3\Asr6\Src\Src_ThirdParty\Src_FLM3\Src_KPIT-FLM3\ApplicationStack\AppMode\MCAL\100_Gpt\ssc\inc\Gpt.h

#ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
#include <CddStpPrj.h>
#include <ctscCddStp.h> // include-path-issue with project 'Mt_CddStp'
#include <Rte.h>
#else // Unit-Tests!
  //#define CFA_CNT_STP_88XX   (4u)
  #include <CddStpPrj.h>
  #include <ctscCddStp.h>
  #include <stddef.h>

#endif

//#include <IntegrationTest.h> // 'ENTER_INIT_RUNNABLE' etc

#ifdef CDDSTP_CFG_SIMULATION // defined in '.\Asr6\Src\Src_AL\Cust\Bw\Bw16\App\Bsw\Cdd\CddStp\CddStpPrj.h'
  #include <CddStp_Simulation.h>
#endif // CDDSTP_CFG_SIMULATION


#include "CddStp.h"
#include <Bsw/Sys/Load/SysLoad.h>

#ifdef SYS_LOAD_RUNNABLE
SYS_LOAD_MEAS_VAR_DEC(riCddStpInit)
SYS_LOAD_MEAS_VAR_DEC(rpCddStp_Cycle)
#endif

//=============================================================================
// Preprocessor definitions
//=============================================================================

//=============================================================================
// Private typedefs 
//=============================================================================

//=============================================================================
// Private variables
//=============================================================================

#ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
#else // Unit-Tests!
  STATIC_AL uint32 CddStp_Counter_Init;
  STATIC_AL uint32 CddStp_Counter_DeInit;
  STATIC_AL uint32 CddStp_Counter_Cycle;
#endif

//=============================================================================
// Private functions prototypes
//=============================================================================

STATIC_AL void           CddStp_Init(void);
STATIC_AL void           CddStp_DeInit(void);
STATIC_AL void           CddStp_Cycle(void);
STATIC_AL Std_ReturnType CddStp_StpOff(void);
STATIC_AL Std_ReturnType CddStp_StpOn(void);

#ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
#else // Unit-Tests!
  STATIC_AL uint32 CddStp_Counter_StartRefRun;
  // jk-obsolet: STATIC_AL void IoHwAb_SetDo(uint16 ChannelId, uint8 Level) { (void)ChannelId; (void)Level; }
#endif


//=============================================================================
// External functions
//=============================================================================


//=============================================================================
// Public functions  implementation
//=============================================================================


//-----------------------------------------------------------------------------
/// \brief  CddStp_Init
///
/// \descr
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddStp_Init(void)
{
#ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
#else // Unit-Tests!
  CddStp_Counter_Init++;
#endif

  CddStp88XX_EftCodingLr(); // Stepper EFT, coding data an mounting side left/right handling

  // jk-obsolet: IoHwAb_SetDo(110, STD_HIGH); // Pin: Stp-NOT-Sleep -> 'High'=NO-Sleep - 110=DioConf_DioChannel_DioChannel_13_6_ST_SLEEP (#define DioConf_DioChannel_DioChannel_HSS_1 88U)
  (void)CddStp_StpOff();

  // call adapted HCM-Code
  riCddStp_Init(); // in file '.\FLM3\Asr6\Src\Src_AL\Cdd\CddStp\HCM\Cust\ctscCddStp_.c'

}


//-----------------------------------------------------------------------------
/// \brief  riCddStpDeInit
///
/// \descr
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void riCddStpDeInit(void)
{
#ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
#else // Unit-Tests!
  CddStp_Counter_DeInit = 1;
#endif

  CddStp_DeInit();
}


//-----------------------------------------------------------------------------
/// \brief  CddStp_DeInit
///
/// \descr
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddStp_DeInit(void)
{
#ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
#else // Unit-Tests!
  CddStp_Counter_DeInit++;
#endif
  // PRQA S 5334 1 // tbd!! - warning - QAC(Prio2) Msg: 5334(HIS metrics violation: 'CddStp_DeInit() : STST3 = 0' is less than threshold 1 for Number of statements in function (STST3).) Depth: 0 Ref: 
}


//-----------------------------------------------------------------------------
/// \brief  rpCddStp10ms
///
/// \descr  (HCM-Code uses 'rpCddStp_Cycle0')
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void rpCddStp10ms(void)
{
  //ENTER_CYCLIC_RUNNABLE(RPCDDSTP10MS);

#ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
#else // Unit-Tests!
  CddStp_Counter_Cycle = 1;
#endif

  CddStp_Cycle();

  //EXIT_CYCLIC_RUNNABLE(RPCDDSTP10MS);
}

//-----------------------------------------------------------------------------
/// \brief  rpCddStp_Cycle
///
/// \descr  cycle function for CddStp at every 20ms
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void rpCddStp_Cycle(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(rpCddStp_Cycle)
#endif

  //ENTER_CYCLIC_RUNNABLE(RPCDDSTP10MS);

#ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
#else // Unit-Tests!
  CddStp_Counter_Cycle = 1;
#endif

  CddStp_Cycle();

  //EXIT_CYCLIC_RUNNABLE(RPCDDSTP10MS);

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(rpCddStp_Cycle)
#endif
}

//-----------------------------------------------------------------------------
/// \brief  riCddStpInit
///
/// \descr  Init function for CddStp
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void riCddStpInit(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(riCddStpInit)
#endif

  //ENTER_CYCLIC_RUNNABLE(RPCDDSTP10MS);

#ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
#else // Unit-Tests!
  CddStp_Counter_Cycle = 1;
#endif

  CddStp_Init();

  //EXIT_CYCLIC_RUNNABLE(RPCDDSTP10MS);

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(riCddStpInit)
#endif
}


//-----------------------------------------------------------------------------
/// \brief  CddStp_Cycle10ms
///
/// \descr
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddStp_Cycle(void)
{
#ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
#else // Unit-Tests!
  CddStp_Counter_Cycle++;
#endif
  {
    STATIC_UT(boolean, boCddStp_Cycle_Initialized, FALSE);
    //
    //This should be placed in CddStp Init Function
    //
    if (boCddStp_Cycle_Initialized == FALSE)
    {
      CddStp_Init();
      boCddStp_Cycle_Initialized = TRUE;
    }
  }

  // call adapted HCM-Code
  rpCddStp_Cycle0();  // in file '.\FLM3\Asr6\Src\Src_AL\Cdd\CddStp\HCM\Cust\ctscCddStp.c'
}


//-----------------------------------------------------------------------------
/// \brief  roCddStpOff
///
/// \descr  Switch stepper OFF
///
/// \param  -
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType roCddStpOff(void)
{
  return CddStp_StpOff();
}


//-----------------------------------------------------------------------------
/// \brief  CddStp_StpOff
///
/// \descr  Switch stepper OFF
///
/// \param  -
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
STATIC_AL Std_ReturnType CddStp_StpOff(void)
{
  CddStp_CtrlFct0((tiulCtrlCmd)CddStp_eCtrlFct0_ModeOff, 0u, NULL);   // UWY
  // jk-tbd !
  return (Std_ReturnType)E_SNA;

}


//-----------------------------------------------------------------------------
/// \brief  roCddStpOn
///
/// \descr  Switch stepper ON
///
/// \param  -
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType roCddStpOn(void)
{
  return CddStp_StpOn();
}


//-----------------------------------------------------------------------------
/// \brief  CddStp_StpOn
///
/// \descr  Switch stepper ON
///
/// \param  -
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
STATIC_AL Std_ReturnType CddStp_StpOn(void)
{
  CddStp_CtrlFct0((tiulCtrlCmd)CddStp_eCtrlFct0_ModeOn, 0u, NULL);   // UWY
  // jk-tbd !
  return (Std_ReturnType)E_SNA;
}

// EOF

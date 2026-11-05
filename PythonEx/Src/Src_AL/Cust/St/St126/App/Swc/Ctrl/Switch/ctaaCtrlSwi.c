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
/// \file  CtrlFan.c
///
/// \brief
///
/// \descr  These files is the interface with the RTE. CtrlFan must receive information
///         from the other modules like SysVolt, Thermo Management and CddHss.
///         Also it contains module API functions which are called by the RTE/OS in
///         order to integrate the module into the arhitecture and for the module's
///         functionality to be used by other SWCs.
///
/// \author Cretu Vladut-Ioan (F78845C)
///         mailTo:vladut-ioan.cretu[at]marelli.com
//-----------------------------------------------------------------------------
//=============================================================================
// includes
//=============================================================================

#include <CtrlSwi.h>
#include <CtrlSwi_Cfg.h>
#include <ctaaCtrlSwi.h>
#include <CtrlSwiRteAccess.h>
#include <Bsw/Sys/Load/SysLoad.h>

#ifdef SYS_LOAD_RUNNABLE
SYS_LOAD_MEAS_VAR_DEC(riCtrlSwiInit)
SYS_LOAD_MEAS_VAR_DEC(rpCtrlSwiCycle0)
#endif


//=============================================================================
// prototypes
//=============================================================================

//=============================================================================
// functions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  initialisation runnable
///
/// \descr  Call init function CtrlSwi_Init()
///         Calling once at start up.
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void riCtrlSwiInit(void)
{
  //ENTER_INIT_RUNNABLE(RICTRLHSSINIT);
  CtrlSwi_Init();
  //EXIT_INIT_RUNNABLE(RICTRLHSSINIT);
}

//-----------------------------------------------------------------------------
/// \brief  cyclic runnable
///
/// \descr  Call cyclic function CtrlSwi_Cycle10ms() every 10ms
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void rpCtrlSwiCycle0(void)
{
  //ENTER_CYCLIC_RUNNABLE(RPCTRLHSS10MS);
  CtrlSwi_Cycle0();
  //EXIT_CYCLIC_RUNNABLE(RPCTRLHSS10MS);
}

#if 0 //not used in LDM
//-----------------------------------------------------------------------------
/// \brief  deinitialisation runnable
///
/// \descr  Call deinit function CtrlSwi_DeInit()
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void riCtrlSwiDeInit(void)
{
  //ENTER_DE_INIT_RUNNABLE(RICTRLHSSDEINIT)
  CtrlSwi_DeInit();
  //EXIT_DE_INIT_RUNNABLE(RICTRLHSSDEINIT)
}
#endif
//EOF

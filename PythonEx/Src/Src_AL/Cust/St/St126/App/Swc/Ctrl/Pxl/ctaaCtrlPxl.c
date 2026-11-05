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
/// \file  ctaaCtrlPxl.c
///
/// \brief
///
/// \descr  These files is the interface with the RTE. CtrlPxl must receive information
///         from the other modules like CtrlLed, Coding.
///         Also it contains module API functions which are called by the RTE/OS in
///         order to integrate the module into the arhitecture and for the module's
///         functionality to be used by other SWCs.
///
/// \author Caba Ionut (F37899C)
///         mailTo:ionut-stefan.caba[at]marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================
#include "CtrlPxl.h"
#include "ctaaCtrlPxl.h"
#include <Bsw/Sys/Load/SysLoad.h>

//=============================================================================
// macro
//=============================================================================
#ifdef SYS_LOAD_RUNNABLE
SYS_LOAD_MEAS_VAR_DEC(riCtrlPxl_Init)
SYS_LOAD_MEAS_VAR_DEC(rpCtrlPxl_Cycle0)
#endif
//=============================================================================
// functions
//=============================================================================
//-----------------------------------------------------------------------------
/// \brief  riCtrlPxl_Init
///
/// \descr  initialization of Pxl.
///
/// \param  none
///
/// \return none
//-----------------------------------------------------------------------------
void riCtrlPxl_Init(void)
{
#ifdef SYS_LOAD_RUNNABLE
	SYS_LOAD_MEAS_BEGIN(riCtrlPxl_Init)
#endif

  CtrlPxl_Init();

#ifdef SYS_LOAD_RUNNABLE
	SYS_LOAD_MEAS_END(riCtrlPxl_Init)
#endif
}

// ---------------------------------------------------------------------------
///
///  \func     rpCtrlPxl_Cycle0
///
///  \brief    cyclic function 
///
///  \param    none
///
///  \return   none
///
// ---------------------------------------------------------------------------
void rpCtrlPxl_Cycle0(void)
{
#ifdef SYS_LOAD_RUNNABLE
	SYS_LOAD_MEAS_BEGIN(rpCtrlPxl_Cycle0)
#endif

  CtrlPxl_Cycle0();

#ifdef SYS_LOAD_RUNNABLE
	SYS_LOAD_MEAS_END(rpCtrlPxl_Cycle0)
#endif
}


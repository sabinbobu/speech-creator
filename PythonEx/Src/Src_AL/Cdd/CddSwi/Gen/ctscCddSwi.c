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
/// \file  ctscCddSwi.c
///
/// \brief
///
/// \author Adrian Horlescu (F31197D)
///         mailTo:adrian-marian.horlescu[at]marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// Includes
//=============================================================================
#include <Std_Types.h>

#include <CddSwi.h>
#include "ctscCddSwi.h"
#include <Bsw/Sys/Load/SysLoad.h>

#ifdef SYS_LOAD_RUNNABLE
SYS_LOAD_MEAS_VAR_DEC(riCddSwi_Init)
SYS_LOAD_MEAS_VAR_DEC(rpCddSwi_Cycle0)
#endif

//=============================================================================
// Defines and Typedef
//=============================================================================

//=============================================================================
//  Static variable declarations
//=============================================================================

//=============================================================================
// Function prototypes
//=============================================================================

//=============================================================================
// Macros
//=============================================================================

//=============================================================================
// Function definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  riCddSwi_Init
///
/// \descr  Initialization runnable
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void riCddSwi_Init(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(riCddSwi_Init)
#endif

    CddSwi_Init();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(riCddSwi_Init)
#endif
}

//-----------------------------------------------------------------------------
/// \brief  rpCddSwi_Cycle
///
/// \descr  Cyclic runnable
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void rpCddSwi_Cycle0(void)
{

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(rpCddSwi_Cycle0)
#endif

   CddSwi_Cycle0();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(rpCddSwi_Cycle0)
#endif
}


// EOF

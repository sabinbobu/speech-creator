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
/// \file  ctaaSysMon_E2E.c
///
/// \brief  File containing the interfaces to communicate through RTE.
///
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================

#include <ctaaSysMon_E2E.h>
#include <SysMon_E2E.h>
//#include <ProcessE2E.h>

//-----------------------------------------------------------------------------
// functions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \brief  riSysMon_E2EInit
///
/// \descr  runnable for initialization of E2E mechanism through SysMon
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void riSysMon_E2EInit(void)
{
  SysMon_E2EInit();
}


//-----------------------------------------------------------------------------
/// \brief  rpSysMon_E2ECycle10ms
///
/// \descr  cyclic runnable for E2E Main Function
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void rpSysMon_E2ECycle10ms(void)
{
  SysMon_E2ECycle10ms();
}

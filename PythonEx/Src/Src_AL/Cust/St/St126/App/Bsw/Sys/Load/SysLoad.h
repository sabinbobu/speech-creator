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
/// \file  SysLoad.h
///
/// \brief
///
//-----------------------------------------------------------------------------
#ifndef SYS_LOAD_2019_12_11_H_
#define SYS_LOAD_2019_12_11_H_

//=============================================================================
//  Macros
//=============================================================================
#ifndef CFG_Var_rta
#define CFG_Var_rta      13u
#endif

#ifndef CFG_Var_default
#define CFG_Var_default      0u
#endif

#if (TYP_RTA == CFG_Var_rta)
#include "SysLoad_Mac.h"
#endif



#endif // SYS_LOAD_2019_12_11_H_

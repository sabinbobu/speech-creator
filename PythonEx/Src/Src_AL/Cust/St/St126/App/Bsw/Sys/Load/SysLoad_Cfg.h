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
/// \file  SysLoad_Cfg.h
///
/// \brief
///
//-----------------------------------------------------------------------------
#ifndef SYS_LOAD_CFG_2019_12_13_H_
#define SYS_LOAD_CFG_2019_12_13_H_

//=============================================================================
//  Includes
//=============================================================================

#include <Bsw/Sys/Load/SysLoad_Types.h>

//=============================================================================
//                            Configurations
//=============================================================================
//	Valid configurations are: MEASURE_RUNNABLE
//                            MEASURE_ISR
//                            MEASURE_TASK
//                            MEASURE_STACK
//                            MEASURE_RUNNABLE_PERIOD_ONLY
//
//=============================================================================

#define SYS_LOAD_MEASUREMENT_TYPE           MEASURE_RUNNABLE

#endif // SYS_LOAD_CFG_2019_12_13_H_

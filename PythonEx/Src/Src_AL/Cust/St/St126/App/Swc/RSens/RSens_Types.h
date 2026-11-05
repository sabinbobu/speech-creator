#ifndef RSENS_TYPES_2021_12_21_H_
#define RSENS_TYPES_2021_12_21_H_
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
/// \file  RSens_Types.h
///
/// \brief
/// \author Sergej Immel  (F55102A)
///         mailTo:sergej.immel@al-lighting.com
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//=============================================================================
// includes
//=============================================================================
#include <Std_Types.h>
#include <Cfg/Cfg.h>
//lint -e451 Header file repeatedly included but does not have a standard include guard
#ifndef UNIT_TEST
#include <Rte.h>
#endif
//lint +e451 Header file repeatedly included but does not have a standard include guard
#include <CodM.h>
#define ROW   8
#define COL   3
#define LMMROW   8u
#define LMMCOL   2u

typedef sint16 NtcTables[ROW][COL];
typedef sint16 LmmTables[LMMROW][LMMCOL];

#endif // RSENS_TYPES_2021_12_21_H_

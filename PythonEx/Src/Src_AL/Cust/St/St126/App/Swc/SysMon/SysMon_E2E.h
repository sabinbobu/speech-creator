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
/// \file  SysMon_E2E.h
///
/// \brief  This file contains the interfaces to integrate E2E library with SysMon
///
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef SYS_MON_E2E_2021_08_02_H_
#define SYS_MON_E2E_2021_08_02_H_
#include <RteCommonTypes.h>
#include <CommonE2E.h>

//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// function prototypes
//-----------------------------------------------------------------------------
void SysMon_E2EInit(void);
void SysMon_E2ECycle10ms(void);
teRte_SigQty SysMon_E2EGetChunkState(Tu8_Int CONST_AL unChunkId, EECO_TEP_ProfileOneChunkStatusPtr CONST_AL pte_ChunkStateE2E);


#endif // SYS_MON_E2E_2021_08_02_H_

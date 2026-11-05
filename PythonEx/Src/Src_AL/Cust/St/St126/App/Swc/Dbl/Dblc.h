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
/// \file     Dblc.h
///
/// \Project  Litronic 6
///
/// \brief    -
///
/// \descr    dynamic bending light control
///
///
/// \data     29.04.2003
///
/// \author   VORNICU Tony - EEG-PM4 (F63906B)
///           mailTo:tony.vornicu[at]al-lighting.com
//-----------------------------------------------------------------------------
#ifndef DBLC_2021_11_02_H_
#define DBLC_2021_11_02_H_

//=============================================================================
// includes
//=============================================================================
#include <Swc/CodM/CodM.h>
#include <Swc/CodM/CodM_Para.h>
#include <RteCommonTypes.h>
#include <Cfg/Cfg.h>

//****************************************************************************
// public defines
//****************************************************************************

#define INC  	                      0x00
#define DEC                         0x01


//=============================================================================
// extern variables
//=============================================================================
extern  tsRteCodingParameters Dbl_sCodingParam;

//****************************************************************************
// public datatypes
//****************************************************************************

//****************************************************************************
// public data
//****************************************************************************

//=============================================================================
// function prototypes
//=============================================================================

/// runnable init point
void Dbl_Init(void);
/// primary runnable entry point
void Dbl_Cycle(void);

#endif // DBLC_2021_11_02_H_

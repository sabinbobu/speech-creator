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
/// \file  ctaaCddSbc.h
///
/// \brief
///
/// \descr
///
/// \author
///
//-----------------------------------------------------------------------------
#ifndef __CTAA_CDDSBC_H___
#define __CTAA_CDDSBC_H___

//-----------------------------------------------------------------------------
// function prototypes
//-----------------------------------------------------------------------------
void riCddSbc_Init(void);
void rpCddSbc_Cycle0(void);
#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
void reCddSbc_SetLssPwm(void);
#endif


#endif

//EOF

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
/// \file   ctscIoHwAbUser.h
///
/// \brief  
///
/// \descr  Init and Cyclic Runnable prototypes for IoHwAbUser
///
/// \author Henrietta Futo (F31185D)
///         mailTo:henrietta-helena.futo[at]marelli.com
//-----------------------------------------------------------------------------

#ifndef CTAA_IO_HW_AB_USER_2021_03_15_H_
#define CTAA_IO_HW_AB_USER_2021_03_15_H_

//-----------------------------------------------------------------------------
// function prototypes
//-----------------------------------------------------------------------------

void riIoHwAbUserInit(void);
void riIoHwAbUserDeInit(void);
void rpIoHwAbUser_Cycle(void);
#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
void reIoHwAbUser_GetLssDiagnostic(void);
#endif

#endif // CTAA_IO_HW_AB_USER_2021_03_15_H_

// EOF

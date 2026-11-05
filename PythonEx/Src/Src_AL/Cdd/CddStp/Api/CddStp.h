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
/// \file  CddStp.h
///
/// \brief
///
/// \author J. Kling ALRT-EES6 (f84304b)
///
//-----------------------------------------------------------------------------

#ifndef CDD_STP_H__
#define CDD_STP_H__

#ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
#else // Unit-Tests!
#endif

void riCddStpDeInit(void); // yet NOT available in RTE!!
void rpCddStp10ms(void);   // 
void rpCddStp_Cycle(void);
void riCddStpInit(void);

Std_ReturnType roCddStpOff(void);
Std_ReturnType roCddStpOn(void);

#endif // CDD_STP_H__

// EOF

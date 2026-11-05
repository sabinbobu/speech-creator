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
/// \file  ctscCddStp.h
///
/// \brief
///
/// \author J. Kling ALRT-EES6 (f84304b)
///
//-----------------------------------------------------------------------------

#ifndef CTSCCDDSTP_H
#define CTSCCDDSTP_H

/****************************************************************************/
/* Prototypes                                                               */
/****************************************************************************/

void rpCddStp_Cycle0(void); // FLM3: 'rpCddStp10ms'
void riCddStp_Init(void);
void roCddStpStartRefRun(tieStepperIndex stepperIndex, ti16StepperPosition_halfsteps position);

#endif /* CTSCCDDSTP_H */

// EOF

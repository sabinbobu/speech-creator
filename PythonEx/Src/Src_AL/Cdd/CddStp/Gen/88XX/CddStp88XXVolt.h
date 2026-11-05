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
/// \file  CddStp88XXVolt.h
///
/// \brief  Texas Instruments TI-DRV88XX specific Volt state machine
///
/// \descr  Volt for Stepper Driver 
///
///         Additional information can be found in the design description (Link:
///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
///
/// \author Wuesteney, Ulrich ALRT/EEG4 * (wu82rt)
///         J. Kling ALRT-EES6 (f84304b)
//-----------------------------------------------------------------------------

#ifndef CDDSTP88XXVOLT_H
#define CDDSTP88XXVOLT_H


// ---------------------------------------------------------------------------
// function prototypes
// ---------------------------------------------------------------------------

uint8 CddStp88XXVolt_GetStpVoltState(void);

void CddStp88XXVolt_StpVoltRng(void);
void CddStp88XXVolt_StpVoltCycle(void);

void IoHwAb_User_GetAdc_DIAG_VBAT(uint16* pio_signal);

#endif /* CDDSTP88XXVOLT_H */

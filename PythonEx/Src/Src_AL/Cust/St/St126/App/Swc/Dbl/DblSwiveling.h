//*****************************************************************************
// (C) Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Automotive Lighting Reutlingen GmbH.
//*****************************************************************************
/// ---------------------------------------------------------------------------
///
///  \file    DblSwiveling.h
///
///  \author  Bernd Dreier  Bernd.Dreier@al-lighting.com
///           ported by     VORNICU Tony - EEG-PM4 (F63906B)
///                         mailTo:tony.vornicu@al-lighting.com
///
///  \owner   Ralf Sondershaus Ralf.Sondershaus@al-lighting.com
///
///  \date    05.04.2004
///
///  \brief   swiveling rate limiter for DBL
///
///  \descr   swiveling rate limiter for DBL
///
/// ---------------------------------------------------------------------------
#ifndef DBL_SWIVELING_2021_11_02_H_
#define DBL_SWIVELING_2021_11_02_H_

//=============================================================================
// includes
//=============================================================================
  #include <Std_Types.h>
  #include <AL_Helper.h>

//=============================================================================
// function prototypes
//=============================================================================
  /// Calculates the maximal increase / decrease of the swivelling angle per time step
  void DblcCalculateSwiveling(sint32 nC, sint32 nCG, uint8 ucStreetClass);
  /// Limit the swiveling angle
  sint32 DblcLimitSwiveling(sint32 nC, sint32 nCG, sint32 nHla, sint32 nHlaOld, uint8 ucStreetClass);

#endif // DBL_SWIVELING_2021_11_02_H_

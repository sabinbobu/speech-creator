#ifndef __AVAC_VDD_H__
#define __AVAC_VDD_H__

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
/// \file  AvacVdd.h
///
/// \brief  
///
/// \descr  
///
///         Additional information can be found in the design description (Link:
///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
///
/// \author Alf Traulsen  (taf2rt)
///         mailTo:alf.traulsen@al-lighting.com
//-----------------------------------------------------------------------------

  #include <Std_Types.h>
  #include "AvacVddAdvanced.h"

  void AvacVdd_Init(void);
  void AvacVdd_DetectVehicleDynamic(void);
  void AvacVdd_DetectStreetQuality(void);

  // -----------------------------------------------------------------------------
  // interface

  // states depending on vehicle speed and acceleration
  extern  uint8 AvacVdd_ucDynState;

  INLINE void        AvacVddSetDynState_(uint8 uc)  {        AvacVdd_ucDynState = uc; }
  INLINE uint8 AvacVddGetDynState_(void)      { return AvacVdd_ucDynState;      }

  INLINE boolean  AvacVddGetDynState_HighAccel_ (void) { return ((AvacVdd_ucDynState & AVACVDD_DynState_HighAccel  ) != 0 ? TRUE : FALSE); }
  INLINE boolean  AvacVddGetDynState_ConstSpeed_(void) { return ((AvacVdd_ucDynState & AVACVDD_DynState_ConstSpeed ) != 0 ? TRUE : FALSE); }
  INLINE boolean  AvacVddGetDynState_ZeroSpeed_ (void) { return ((AvacVdd_ucDynState & AVACVDD_DynState_ZeroSpeed  ) != 0 ? TRUE : FALSE); }
  INLINE boolean  AvacVddGetDynState_Invalid_   (void) { return ((AvacVdd_ucDynState & AVACVDD_DynState_Invalid    ) != 0 ? TRUE : FALSE); }

  // measurement of acceleration change
  extern  uint8 AvacVdd_ucAccIndex;

  INLINE void        AvacVddSetAccIndex_(uint8 uc)  {        AvacVdd_ucAccIndex = uc; }
  INLINE uint8 AvacVddGetAccIndex_(void)      { return AvacVdd_ucAccIndex;      }

  // measurement of street quality
  extern  uint8 AvacVdd_ucBadStreetIndex;

  INLINE void        AvacVddSetBadStreetIndex_(uint8 uc)  {        AvacVdd_ucBadStreetIndex = uc; }
  INLINE uint8 AvacVddGetBadStreetIndex_(void)      { return AvacVdd_ucBadStreetIndex;      }

#endif // __AVAC_VDD_H__

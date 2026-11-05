#ifndef __AVAC_UTIL_H__
#define __AVAC_UTIL_H__

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
/// \file  AvacUtil.h
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
#include <../Util/UtilMath.h>


/// calculation of filter coefficient and call of _Order1Filter(), C164: 15us
sint16  AvacUtil_Order1FilterByRelTime (ORDER1_Filter* pFilter, uint16 unRelTime, sint16  nValue);
/// Das Eingangssignal Value wird auf LimitMin bis LimitMax begrenzt.
sint16  AvacUtil_SignalLimiter(sint16 LimitMax, sint16 LimitMin, sint16 Value);
/// Das Ausgangssignal (*pRateLimiter) wird dem Eingangssignal nachgeführt.
void    AvacUtil_RateLimiter(sint16* pRateLimiter, sint16 RateUp, sint16 RateDown, sint16 Value);


#endif // __AVAC_UTIL_H__

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
/// \file  AvacUtil.c
///
/// \brief  
///
/// \descr  
///
///         Additional information can be found in the design description (Link:
///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
///
/// \author Alf Traulsen  (taf2rt)
///         mailTo:alf.traulsen[at]al-lighting.com
//-----------------------------------------------------------------------------

#include <Std_Types.h>

#include "AvacUtil.h"


// *****************************************************************************
// Function    : AvacUtil_Order1FilterByRelTime()                              C164: 15us
// 
// Parameter   : ORDER1_Filter* pFilter - pointer to filter structure
//               uint16 unRelTime       - filter time relative to sampling time; the unit for filter time is 10 ms
//               sint16 nValue          - input value
//
// Returnvalue : actual filter value
//
// Description : calculation of filter coefficient and call of Order1Filter().
// *****************************************************************************
sint16 AvacUtil_Order1FilterByRelTime(ORDER1_Filter* pFilter, uint16 unRelTime, sint16 nValue)
{
  // 2 * 10 ms = 20ms sampling time
  uint16 unSamplimgTime = 2u;  // because parameter unRelTime is already relative to sampling time

  uint16 unBeta = Order1FilterGetCoef(unSamplimgTime, unRelTime);

  Order1Filter(pFilter, nValue, unBeta);
  return Order1FilterValue(pFilter);
}


/*DOC*************************************************************************

Funktion    AvacUtil_SignalLimiter()

Parameter   sint16  LimitMax     - obere Grenze
            sint16  LimitMin     - untere Grenze
            sint16  Value        - Wert, der begrenzt werden soll

Ergebnis    sint16 - begrenzter Wert
            
Beschreibung
Das Eingangssignal Value wird auf LimitMin bis LimitMax begrenzt.

*************************************************************************DOC*/
sint16 AvacUtil_SignalLimiter(sint16 LimitMax, sint16 LimitMin, sint16 Value)
{
  sint16 ret;
  if(Value > LimitMax)
  {
    ret = LimitMax;
  }
  else if(Value < LimitMin)
  {
    ret = LimitMin;
  }
  else
  {
    ret = Value;
  }
  return ret;
}

/*DOC*************************************************************************

Funktion    AvacUtil_RateLimiter()

Parameter   sint16* pRateLimiter - Zeiger auf die Speichervariable
            sint16  RateUp       - Gradient fur steigende Signale
            sint16  RateDown     - Gradient fur fallende Signale
            sint16  Value        - Neuer Wert der begrenzt werden soll

Ergebnis    keines
            
Beschreibung
Das Ausgangssignal (*pRateLimiter) wird dem Eingangssignal nachgefuhrt,
aber nur mit der maximalen Anderung RateUp bzw. RateDown pro Funktionsaufruf.

*************************************************************************DOC*/
void AvacUtil_RateLimiter(sint16* pRateLimiter, sint16 RateUp, sint16 RateDown, sint16 Value)
{
  if(Value > *pRateLimiter + RateUp)
  {
    *pRateLimiter += RateUp;
  }
  else if(Value < *pRateLimiter - RateDown)
  {
    *pRateLimiter -= RateDown;
  }
  else
  {
    *pRateLimiter = Value;
  }
}

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
/// \file  AvacStat1Util.c
///
/// \brief  
///
/// \descr  
///
///         Additional information can be found in the design description
///
/// \author Alf Traulsen  (taf2rt)
//-----------------------------------------------------------------------------

#include <Std_Types.h>
#include <UtilMath.h>

#include "AvacStat1Util.h"


// *****************************************************************************
// Function    : AvacStat1Util_Order1Filter()
// 
// Parameter   : ORDER1_Filter* pFilter - pointer to filter structure
//               uint16 unBeta          - filter coefficient
//               sint16 nValue          - input value
//
// Returnvalue : none
//
// Description : Lowpass 1st order.
//               Y(n) = (1 - Beta) * X(n) + Beta * Y(n-1) ,   0 < Beta < 1
//               unBeta is normalized to 128 (1...127).
//               filter time constant = - (sampling time) / LN(Beta).
//               If unBeta == 0, the filter algorithm is skipped.
//               The filter storage is scaled by factor 512.
// *****************************************************************************

void AvacStat1Util_Order1Filter(ORDER1_Filter* pFilter, sint16 nValue, uint16 unBeta)
{
  if(unBeta != 0u)
  {
    //PRQA S 4533, 4394 1 // Compiler can do right shift // Shift right of signed quantity (long)
    *pFilter = ((*pFilter * (sint16) unBeta + 64) >> 7u) + (sint16)((128u - unBeta) * 4u) * (sint32) nValue;
  }
}

// *****************************************************************************
// Function    : AvacStat1Util_Order1FilterInit()
// 
// Parameter   : ORDER1_Filter* pFilter - pointer to filter structure
//               sint16 Value            - initialization value
//
// Returnvalue : none
//
// Description : Initialize filter variable by scaling input value.
//               Provide additional inline function for internal use.
// *****************************************************************************

void AvacStat1Util_Order1FilterInit(ORDER1_Filter* pFilter, sint16 Value)
{
  *pFilter = (sint32) Value * 512;
}

// *****************************************************************************
// Function    : AvacStat1Util_Order1FilterValue()
// 
// Parameter   : ORDER1_Filter* pFilter - pointer to filter structure
//
// Returnvalue : actual filter output value
//
// Description : get actual filter output value without new filter calculation
// *****************************************************************************

sint16 AvacStat1Util_Order1FilterValue(ORDER1_Filter* pFilter)
{
  // undo scaling
  //PRQA S 4533 1 // Compiler can do right shift
  return (sint16) ((*pFilter + 256) >> 9u);
}

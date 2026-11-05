#ifndef __CODM_PARA_CURVERADIUS_H__
#define __CODM_PARA_CURVERADIUS_H__


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
///  \file   CodM_Para_CurveRadius.h
///
///  \brief  Content of datagroup "CurveRadius"
///
///  \descr  Source: PS60_R2.xlsm. 
///          Version TBD 
///          For further details see coding parameter
///
///  \author Cretu Vlad (F78845C)
///          mailTo:vladut-ioan.cretu[at]marelli.com
///
///  \date   24.03.2020, 11:22:09
//-----------------------------------------------------------------------------
//=============================================================================
// Includes
//=============================================================================

//=============================================================================
// Definitions
//=============================================================================
#define MAX_VALUES                      7801
//=============================================================================
// Types
//=============================================================================
#include <Std_Types.h>
      
typedef struct 
{
  sint16 asnCurvePoint_VAL[MAX_VALUES];
}
tNvmPara_CurveRadius_CurvePointsValues;

typedef struct 
{
  tNvmPara_CurveRadius_CurvePointsValues CurvePointsValues;
} 
tNvmPara_CurveRadiusBlock;

#endif // __CODM_PARA_CURVERADIUS_H__

// EOF

#ifndef __AVACSTAT1UTIL_H__
#define __AVACSTAT1UTIL_H__

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
/// \file  AvacStat1Util.h
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
#include "ILCU_LevellingAdapter.h" /* ILCU_PORT: replaces DPE-only <UtilMath.h> */


#define TAU_AvacStatUtil_Min     1
#define TAU_AvacStatUtil_1x     47
#define TAU_AvacStatUtil_2x     78
#define TAU_AvacStatUtil_3x     92
#define TAU_AvacStatUtil_4x    100
#define TAU_AvacStatUtil_5x    105
#define TAU_AvacStatUtil_6x    108
#define TAU_AvacStatUtil_8x    113
#define TAU_AvacStatUtil_10x   116
#define TAU_AvacStatUtil_12x   118
#define TAU_AvacStatUtil_15x   120
#define TAU_AvacStatUtil_20x   122
#define TAU_AvacStatUtil_25x   123
#define TAU_AvacStatUtil_30x   124
#define TAU_AvacStatUtil_40x   125
#define TAU_AvacStatUtil_60x   126
#define TAU_AvacStatUtil_130x  127

void    AvacStat1Util_Order1Filter          (ORDER1_Filter* pFilter, sint16  nValue, uint16 unBeta);
void    AvacStat1Util_Order1FilterInit      (ORDER1_Filter* pFilter, sint16 Value);
sint16  AvacStat1Util_Order1FilterValue     (ORDER1_Filter* pFilter);


#endif // __AVAC_UTIL_H__

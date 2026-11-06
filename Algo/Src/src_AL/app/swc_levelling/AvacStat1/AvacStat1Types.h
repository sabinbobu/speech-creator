#ifndef __AVACSTAT1TYPES_H
  #define __AVACSTAT1TYPES_H

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
/// \file  AvacStat1Types.h
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
#include "ILCU_LevellingAdapter.h" /* ILCU_PORT: replaces DPE-only <RteCommonTypes.h> */

//=============================================================================
// typedefs
//=============================================================================

// -----------------------------------------------------------------------------
// pitch
typedef struct tAvacStat_Pitch_tag
{
  sint16      nAngle;           ///< [1/10 mrad] front side up --> positive value
  sint16      nHeightErr;       ///< [1/10 mrad] headlights up --> positive value
  teRte_SigQty   eSigQty;
} tAvacStat_Pitch;

// -----------------------------------------------------------------------------
// speed
#define BB_MotionNeu     0x00U     ///< neutral, parking  
#define BB_MotionLow     0x01U     ///< forward low  gear, high torque
#define BB_MotionMid     0x02U     ///< forward mid  gear, mid torque
#define BB_MotionHig     0x03U     ///< forward high gear, low torque
#define BB_MotionRev     0x0FU     ///< reverse

#define BB_MotionErr     0x3DU     ///< motion signal error 
#define BB_MotionSNA     0x3EU     ///< motion signal not available
#define BB_MotionSNV     0x3FU     ///< motion signal not valid


typedef struct tAvacStat_Speed_tag
{
  sint16    nSpeed;         ///< [1/10 km/h]  forward      --> positive value
  sint16    nAcceleration;  ///< [1/10 m/s^2] acceleration --> positive value
  uint16    unMotion;       ///< \brief optional motion direction and gear information.
                            ///  \descr optional motion direction and gear information
                            ///  - \c BB_MotionErr       <b>unknown/error                   </b> 
                            ///  - \c BB_MotionRev       <b>reverse                         </b>
                            ///  - \c BB_MotionNeu       <b>neutral, parking                </b>
                            ///  - \c BB_MotionLow       <b>forward low  gear, high torque  </b>
                            ///  - \c BB_MotionMid       <b>forward mid  gear, mid torque   </b>
                            ///  - \c BB_MotionHig       <b>forward high gear, low torque   </b>
  teRte_SigQty eSigQty;
} tAvacStat_Speed;

typedef struct tAvacStat_Out_tag
{
  sint16      nAngle;    ///< [1/10 mrad] headlamp up --> positive value
  teRte_SigQty   eSigQty;
}tAvacStat_Out;


typedef enum
{
  eUNDEFINED  = 0u,
  eLOW_SPEED  = 1u,
  eHIGH_SPEED = 2u
}teAvacStat_SpeedMode;

#endif //__AVACSTAT1TYPES_H

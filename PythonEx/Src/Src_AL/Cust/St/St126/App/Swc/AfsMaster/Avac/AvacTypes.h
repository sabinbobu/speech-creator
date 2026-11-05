#ifndef __AVACTYPES_H__
#define __AVACTYPES_H__

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
/// \file  AvacTypes.h
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
#ifndef UNIT_TEST
#include <Rte.h>
#elif defined UNIT_TEST
#include <Rte/RteCommonTypes.h>
#endif
//=============================================================================
// typedefs
//=============================================================================

// -----------------------------------------------------------------------------
// pitch
typedef struct tAvac_Pitch_tag
{
  sint16      nAngle;           ///< [1/10 mrad] front side up --> positive value
  sint16      nHeightErr;       ///< [1/10 mrad] headlights up --> positive value
  teRte_SigQty   eSigQty;
} tAvac_Pitch;

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


typedef struct tAvac_Speed_tag
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
} tAvac_Speed;

// -----------------------------------------------------------------------------
// Acceleration PreDetection
typedef struct tAvac_AccelPreDetect_tag
{
  sint16    nValue;
  sint16    nDelta;
  teRte_SigQty eSigQty;
} tAvac_AccelPreDetect;


// -----------------------------------------------------------------------------
// Brake PreDetection
typedef struct tAvac_BrakePreDetect_tag
{
  sint16    nValue;
  sint16    nDelta;
  teRte_SigQty eSigQty;
} tAvac_BrakePreDetect;

typedef struct tAvac_Out_tag
{
  sint16      nAngle;    ///< [1/10 mrad] headlamp up --> positive value
  teRte_SigQty   eSigQty;
}tAvac_Out;

#endif // __AVACTYPES_H__

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
/// \file  CtrlStp_Util.h
///
/// \brief Geometrical calculations in CtrlStp
///
//-----------------------------------------------------------------------------
#ifndef CTRL_STP_UTIL_2020_07_02_H_
#define CTRL_STP_UTIL_2020_07_02_H_


//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <Std_Types.h>
#include <AL_Helper.h>


//-----------------------------------------------------------------------------
// prototypes
//-----------------------------------------------------------------------------
sint16  CtrlStp_Angle2StpPos (uint16 unTransmFactor, uint16 unOffset, sint16 nAngle);
sint16  CtrlStp_CheckForStart(uint8  ucThresh, boolean boMoving, sint16 nOldPos, sint16 nNewPos);
sint16  CtrlStp_LimitAngle   (uint16 unNegRange, uint16 unPosRange, sint16 nAngle);
uint16  CtrlStp_Speed2Tmin   (uint16 unTransmFactor, uint16 unSpeed);
sint16  CtrlStp_StpPos2Angle (uint16 unTransmFactor, uint16 unOffset, sint16 nStpPos);
uint16  CtrlStp_Tmin2Speed   (uint16 unTransmFactor, uint16 unTmin);


#endif // CTRL_STP_UTIL_2020_07_02_H_

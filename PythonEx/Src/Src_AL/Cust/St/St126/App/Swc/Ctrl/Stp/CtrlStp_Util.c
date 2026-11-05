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
/// \file  CtrlStp_Util.c
///
/// \brief Geometrical calculations in CtrlStp
///
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
//#include <IntegrationTest.h>
#include "CtrlStp_Util.h"
#include <UtilUtility.h>


//-----------------------------------------------------------------------------
/// \brief  convert angle to halfstep position
///
/// \descr  Calculate halfstep position based on formula
///
///         Position[HS] =  TransmissionFactor[HS/deg]     * (Angle[deg]     + Offset[deg]    )
///                      = (TransmissionFactor[0.01HS/deg] * (Angle[0.01deg] + Offset[0.01deg])) / 10000
///
///         Round result
///
/// \param  uint16 unTransmFactor [0.01HS/deg]
///         uint16 unOffset       [0.01deg]
///         sint16 nAngle         [0.01deg]
///
/// \return sint16 stepper position [HS]
//-----------------------------------------------------------------------------
sint16 CtrlStp_Angle2StpPos(uint16 unTransmFactor, uint16 unOffset, sint16 nAngle)
{
  sint16 nStpPos;

  nAngle += (sint16)unOffset;

  if (nAngle >= 0)
  {
    nStpPos = (sint16)(((sint32)unTransmFactor * nAngle + 5000) / 10000);  // add 5000 for rounding
  }
  else
  {
    nStpPos = (sint16)(((sint32)unTransmFactor * nAngle - 5000) / 10000);  // subtract 5000 for rounding
  }

  return nStpPos;
}


//-----------------------------------------------------------------------------
/// \brief  Check new halfstep position to decide if movement is requested
///
/// \descr  start stepper movement only if threshold is exceeded
///         or motor is already moving
///
///         Check for |NewPos[HS] - OldPos[HS]| >= Thresh[HS]
///
/// \param  uint8   ucThresh [HS]      - minimum value for movement
///         boolean boMoving [boolean] - motor already in movement
///         sint16  nOldPos  [HS]      - momentary target position
///         sint16  nNewPos  [HS]      - new target position
///
/// \return sint16 target position[HS]
//-----------------------------------------------------------------------------
sint16 CtrlStp_CheckForStart(uint8 ucThresh, boolean boMoving, sint16 nOldPos, sint16 nNewPos)
{
  sint16 nTgtPos = nOldPos;
  sint16 nDelta  = nNewPos - nOldPos;

  if (nDelta < 0)
  {
    nDelta = -nDelta;
  }

  if ((boMoving != FALSE) || (nDelta >= (sint16)ucThresh))
  {
    nTgtPos = nNewPos;
  }

  return nTgtPos;
}


//-----------------------------------------------------------------------------
/// \brief  Limit angle according to mechanical headlamp parameters
///
/// \descr  Limit input parameter Angle[0.01 deg] to
///           - upper limit: PosRange [0.01 deg]
///           - lower limit: NegRange [0.01 deg]
///
/// \param  uint16 unNegRange [0.01 deg] absolute value of negative range
///         uint16 unPosRange [0.01 deg] absolute value of positive range
///         sint16 nAngle     [0.01 deg]
///
/// \return sint16 nAngle with limitation
//-----------------------------------------------------------------------------
sint16 CtrlStp_LimitAngle(uint16 unNegRange, uint16 unPosRange, sint16 nAngle)
{
  sint16 nMinVal = -(sint16)unNegRange;
  sint16 nMaxVal =  (sint16)unPosRange;

  nAngle = UTIL_MAX(nAngle, nMinVal);  // lower limit
  nAngle = UTIL_MIN(nAngle, nMaxVal);  // upper limit

  return nAngle;
}


//-----------------------------------------------------------------------------
/// \brief  Convert speed to Tmin
///
/// \descr  Calculate minimum HS time by speed based on formula
///
///         Tmin[s/HS]  = 1          / (TransmissionFactor[HS/deg]     * Speed[deg/s]
///         Tmin[us/HS] = 1000000    / (TransmissionFactor[HS/deg]     * Speed[deg/s]
///                     = 1000000000 / (TransmissionFactor[0.01HS/deg] * Speed[0.1deg/s]
///
///          Avoid division by 0
///          Limit to output to 16 bit
///
/// \param  uint16 unSpeed              [0.1deg/s]
///         uint16 unTransmissionFactor [0.01HS/deg]
///
/// \return uint16 Tmin [us/HS]
//-----------------------------------------------------------------------------
uint16 CtrlStp_Speed2Tmin(uint16 unTransmFactor, uint16 unSpeed)
{
  uint32 ulDenominator = (uint32)unTransmFactor * unSpeed;
  uint16 unTmin = 0u;

  if (ulDenominator != 0u)  // avoid zero-division
  {
    uint32 ulTmin = 1000000000u / ulDenominator;

    unTmin = (uint16)UTIL_MIN(ulTmin, 65535u);  // limit Tmin to uint16
  }

  return unTmin;
}


//-----------------------------------------------------------------------------
/// \brief  convert stepper position to angle
///
/// \descr  Invert function CtrlStp_Angle2StpPos() according to formula
///
///         Angle[deg]    =  ( StpPos[HS]          / TransmissionFactor[HS/deg]    ) - Offset[deg]
///         Angle[0.1deg] =  ((StpPos[HS] * 10   ) / TransmissionFactor[HS/deg]    ) - Offset[0.1deg]
///                       =  ((StpPos[HS] * 1000 ) / TransmissionFactor[0.01HS/deg]) - Offset[0.1deg]
///                       = (((StpPos[HS] * 10000) / TransmissionFactor[0.01HS/deg]) - Offset[0.01deg]) / 10
///
///         Avoid division by 0
///         Round result
///
/// \param  uint16 unTransmFactor   [0.01HS/deg]
///         uint16 unOffset         [0.01deg]
///         sint16 stepper position [HS]
///
/// \return sint16 nAngle [0.1deg]
//-----------------------------------------------------------------------------
sint16 CtrlStp_StpPos2Angle(uint16 unTransmFactor, uint16 unOffset, sint16 nStpPos)
{
  sint32 lAngle = 0;
  uint16 unRndConst = unTransmFactor / 2u;  // for rounding
  
  if (unTransmFactor != 0u)
  {
    lAngle = ((sint32)nStpPos * 10000 + (sint32)unRndConst) / (sint32)unTransmFactor;  // do not consider negative nStpPos

    lAngle = lAngle - (sint32)unOffset;
  }
  else
  {
    // no behavior
  }

  return (sint16)lAngle;
}


//-----------------------------------------------------------------------------
/// \brief  Convert Tmin to speed
///
/// \descr  Invert function CtrlStp_Speed2Tmin() according to formula
///
///         Speed[deg/s]    = 1         / (TransmissionFactor[HS/deg]     * Tmin[s/HS] )
///         Speed[0.1deg/s] = 10        / (TransmissionFactor[HS/deg]     * Tmin[s/HS] )
///                         = 100000000 / (TransmissionFactor[0.01HS/deg] * Tmin[us/HS])
///
///         Avoid division by 0
///         Limit to output to 16 bit
///
/// \param  uint16 unTransmissionFactor [0.01HS/deg]
///         uint16 unTmin               [us/HS]
///
/// \return uint16 unSpeed              [0.1deg/s]
//-----------------------------------------------------------------------------
uint16 CtrlStp_Tmin2Speed(uint16 unTransmFactor, uint16 unTmin)
{
  uint32 ulDenominator = (uint32)unTransmFactor * unTmin;
  uint32 ulRndConst = ulDenominator / 2u;  // for rounding
  uint16 unSpeed = 0u;

  if (ulDenominator != 0u)  // avoid zero-division
  {
    uint32 ulTmin = (1000000000u + ulRndConst) / ulDenominator;

    unSpeed = (uint16)UTIL_MIN(ulTmin, 65535u);  // limit Tmin to uint16
  }

  return unSpeed;
}


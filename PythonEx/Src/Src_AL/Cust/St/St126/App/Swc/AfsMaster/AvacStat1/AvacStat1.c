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
/// \file  AvacStat1.c
///
/// \brief  
///
/// \descr  static AVAC, No. 1
///
/// \author Alf Traulsen
///              
//-----------------------------------------------------------------------------

#include <Cfg/Cfg.h>

#include <Std_Types.h>
#ifndef UNIT_TEST
#include <Rte.h>
#endif
#include <UtilUtility.h>
#include <UtilMath.h>

#include "AvacStat1Util.h"
#include <AvacStat1Data.h>
#include "AvacStat1.h"
#include "AvacStat1Types.h"

// *****************************************************************************
// Defines
// *****************************************************************************

#define REGULATION_ModeNormal             0x00u
#define REGULATION_ModeFreezeRegulation   0x01u
#define REGULATION_ModePowerOnDelay       0x02u
#define REGULATION_ModeNoDynamic          0x04u

/*-------------------------------------------------------------------------------------*/
/*  Regulate States for Static ALWR caused by Vehicle-Dynamik (LwrRegulationMode)      */
/*-------------------------------------------------------------------------------------*/

#define STATIC_Lwr_Zero_Speed        5u
#define STATIC_Lwr_Below_Min_Speed   4u
#define STATIC_Lwr_Vehicle_Start     3u
#define STATIC_Lwr_Transient_State   2u
#define STATIC_Lwr_Acceleration      1u
#define STATIC_Lwr_Constant_Speed    0u

/*-------------------------------------------------------------------------------------*/
/*  Flags for LwrRegulateExtendedMode                                                  */
/*-------------------------------------------------------------------------------------*/
                                               
#define STATIC_LwrFlagVehicleStart             0x01u
#define STATIC_LwrFlagAboveMaxSpeed            0x02u
#define STATIC_LwrFlagLightOn                  0x04u
#define STATIC_LwrFlagMotorFree                0x08u
#define STATIC_LwrFlagPowerOnAdjust            0x10u
#define STATIC_LwrFlagFreezeRegulation         0x20u
#define STATIC_LwrFlagPowerOnDelay             0x40u
#define STATIC_LwrFlagRefAngleValid            0x80u

/*-------------------------------------------------------------------------------------*/
/*  Regulation Parameters for Static ALWR                                                */
/*-------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
// Downsamling for sample time 20ms
#ifndef UNIT_TEST
#define ECUFUNC_AvacStat1DownSampling   5   // => 100ms sample time
#else
uint8 AvacStat1_ucSamplingUnitTest = 0u;
#define ECUFUNC_AvacStat1DownSampling   AvacStat1_ucSamplingUnitTest   // => 100ms sample time
#endif

/*-------------------------------------------------------------------------*/
// Delay time for SafetyAngle at 100ms sample time
#ifndef UNIT_TEST
#define ECUFUNC_AvacStat1SafetyAngleDelay 200  // 20s
#else
uint8 AvacStat1_ucSafetyDelayUnitTest = 200u;
#define ECUFUNC_AvacStat1SafetyAngleDelay AvacStat1_ucSafetyDelayUnitTest  // 20s
#endif

/*-------------------------------------------------------------------------*/
// Begrenzung von GetHeadlightAngle()
#define STATIC_AngleMin                875  //  0 degrees
#define STATIC_AngleMax                  0  //  5 degrees

/*-------------------------------------------------------------------------*/

#define STATIC_ControlFilterCoeff               123 // Time const. for LwrControlFilter (2.5s at 100ms)
#define STATIC_AutoAngleGradientLimit             5 // Maximum gradient bewteen actual and previous (100 ms) AutoAngle [0.1 mrad]

/* Konstanten fuer LwrMovingStatus nach VW-Norm */
#define LWR_ZeroSpeed     0x00
#define LWR_ConstantSpeed 0x55
#define LWR_Acceleration  0xFF

// *****************************************************************************
// Prototypes
// *****************************************************************************

STATIC_AL sint16  AvacStat1_GetHeadlightAngle(void);
STATIC_AL void    AvacStat1_SetRegMode(sint16 Speed, sint16 Acc, uint8 Mode);
STATIC_AL boolean AvacStat1_SetStaticFilterParameters(void);
STATIC_AL void    AvacStat1_CheckZeroLvl(void);
STATIC_AL void    AvacStat1_SetSpeedMode(void);

// *****************************************************************************
// Variables
// *****************************************************************************
STATIC_AL uint8 AvacStat1_byLwrRegulationMode;
STATIC_AL uint8 AvacStat1_byLwrRegulationExtendedMode;

STATIC_AL ORDER1_Filter AvacStat1_LwrStaticFilter;
STATIC_AL ORDER1_Filter AvacStat1_LwrControlFilter;
STATIC_AL ORDER1_Filter AvacStat1_LwrAccelerationFilter;

STATIC_AL uint8  AvacStat1_byStaticFilterSampleTime;
STATIC_AL uint8  AvacStat1_bySampleTimeLong;

STATIC_AL uint8  AvacStat1_byTstatic;
STATIC_AL uint8  AvacStat1_byTcontrol;

STATIC_AL sint16 AvacStat1_nLwrTransientStateCounter;
STATIC_AL sint16 AvacStat1_nLwrStaticFilterServiceCounter;
STATIC_AL sint16 AvacStat1_nLwrConstantSpeedCounter;
STATIC_AL sint16 AvacStat1_nLwrLoadChangeCounter;

STATIC_AL sint16 AvacStat1_nActualHeadlightAngle;
STATIC_AL sint16 AvacStat1_nAutoAngle;
STATIC_AL sint16 AvacStat1_nAutoAngleGrad;
STATIC_AL sint16 AvacStat1_nStaticAngle;
STATIC_AL sint16 AvacStat1_nControlAngle;
STATIC_AL sint16 AvacStat1_nRefAngle;
STATIC_AL sint16 AvacStat1_anOldControlAngle[4];
STATIC_AL uint8  AvacStat1_byAngleMinChange;

STATIC_AL sint16 AvacStat1_nAutoAngleMin;// = STATIC_AngleMin;
STATIC_AL sint16 AvacStat1_nAutoAngleMax;// = STATIC_AngleMax;

STATIC_AL boolean AvacStat1_boCodingValidity = FALSE;

#if (CFG_DEV_HOOK_EN == 1u) // tester hook
volatile uint32 AvacStat1_ulTesterHookActivation = 0u;
#endif

//-----------------------------------------------------------------------------
/// \brief AvacStat1_CheckZeroLvl
///
/// \descr Checks and sets DTC for zero level programming
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void AvacStat1_CheckZeroLvl(void)
{
  // Set DTC for Zero Level Programming
  if (NvmBlockDeltaPwmPara.ucZeroLevProg != 0xFFu)
  {
    Rte_Call_DemPrj_ReportErrorStatus((uint16)ZERO_LVL_PROG, DEM_EVENT_STATUS_FAILED);
  }
  else
  {
    Rte_Call_DemPrj_ReportErrorStatus((uint16)ZERO_LVL_PROG, DEM_EVENT_STATUS_PASSED);
  }
}


/*DOC*************************************************************************

Funktion    SetStaticFilterParameters

Parameter   keine

Ergebnis    BOOL: Soll StaticFilter bedient werden

Beschreibung
Verlangsamt das StaticFilter und entscheidet, ob das Abtastintervall abgelaufen ist und damit das
StaticFilter bedient wird.

*************************************************************************DOC*/
STATIC_AL boolean AvacStat1_SetStaticFilterParameters(void)
{
  boolean ret;

  if(AvacStat1_byStaticFilterSampleTime == AvacStat1_bySampleTimeLong)
  {
    AvacStat1_byLwrRegulationExtendedMode |= STATIC_LwrFlagMotorFree;
  }
  else
  {
    if ( --AvacStat1_nLwrConstantSpeedCounter <= 0 )
    {
        AvacStat1_nLwrConstantSpeedCounter = Cod_AvacStat1_ConstantSpeedInterval();

        if( AvacStat1_byTstatic < Cod_AvacStat1_StaticFilterCoefAtConstSpeed() )
        {

          if(    ( AvacStat1_byTstatic == NvmBlockStatAvacPrj1Para.abyFilterCoefToUnlock[0] )//Cod_AvacStat1_FilterCoefToUnlock(0) )
              || ( AvacStat1_byTstatic == NvmBlockStatAvacPrj1Para.abyFilterCoefToUnlock[1] )//Cod_AvacStat1_FilterCoefToUnlock(1) )
              || ( AvacStat1_byTstatic == NvmBlockStatAvacPrj1Para.abyFilterCoefToUnlock[2] )//Cod_AvacStat1_FilterCoefToUnlock(2) )
              || ( AvacStat1_byTstatic == NvmBlockStatAvacPrj1Para.abyFilterCoefToUnlock[3] )//Cod_AvacStat1_FilterCoefToUnlock(3) )
              || ( AvacStat1_byTstatic == NvmBlockStatAvacPrj1Para.abyFilterCoefToUnlock[4] )//Cod_AvacStat1_FilterCoefToUnlock(4) )
            )
          {
            AvacStat1_byLwrRegulationExtendedMode |= STATIC_LwrFlagMotorFree;
          }

          AvacStat1_byTstatic += Cod_AvacStat1_FilterCoefInc();
          if( AvacStat1_byTstatic > Cod_AvacStat1_StaticFilterCoefAtConstSpeed() )
          {
            AvacStat1_byTstatic = Cod_AvacStat1_StaticFilterCoefAtConstSpeed();
          }

          AvacStat1_byStaticFilterSampleTime = Cod_AvacStat1_SampleTimeShort(); //?? Schon durch InitRegulation !!
        }
        else
        {
          AvacStat1_byStaticFilterSampleTime = AvacStat1_bySampleTimeLong;
        }
    }
  }

  if( --AvacStat1_nLwrStaticFilterServiceCounter <= 0 )
  {
    AvacStat1_nLwrStaticFilterServiceCounter = (sint16)AvacStat1_byStaticFilterSampleTime;
    ret = TRUE;
  }
  else
  {  
    ret = FALSE;
  }

  return ret;
}


/*DOC*************************************************************************

Funktion    SetRegulationMode

Parameter   keine

Ergebnis    keines

Beschreibung
Erkennt den Fahrzustand und bestimmt den Regelmodus.

*************************************************************************DOC*/
STATIC_AL void AvacStat1_SetRegMode(sint16 Speed, sint16 Acc, uint8 Mode)
{
  uint8 ucHighFrozenVehSpeed, ucFrozenVehSpeed;

  // --------------------------------------------------------------------------
  // filter acceleration
  // --------------------------------------------------------------------------
  AvacStat1Util_Order1Filter(&AvacStat1_LwrAccelerationFilter, Acc, (uint16)Cod_AvacStat1_AccFilterCoeff());
  Acc = AvacStat1Util_Order1FilterValue(&AvacStat1_LwrAccelerationFilter);
  Acc = UTIL_ABS(Acc);

  // --------------------------------------------------------------------------
  // set flags
  // --------------------------------------------------------------------------
  // Evaluate regulation mode
  if (Mode == REGULATION_ModePowerOnDelay)
  {
     AvacStat1_byLwrRegulationExtendedMode |= STATIC_LwrFlagPowerOnDelay;
  }   
  else if (Mode == REGULATION_ModeFreezeRegulation)
  {   
     AvacStat1_byLwrRegulationExtendedMode |= STATIC_LwrFlagFreezeRegulation;
  }
  else // go on
  {
    if (Mode == REGULATION_ModeNoDynamic)
    {
       AvacStat1_byLwrRegulationExtendedMode &= (uint8)(~STATIC_LwrFlagFreezeRegulation); 
       AvacStat1_byLwrRegulationExtendedMode &= (uint8)(~STATIC_LwrFlagPowerOnDelay);

       // manipulate speed and acc values, reduce filtertime at constant speed
       Speed = 50 * (sint16)Cod_AvacStat1_HighFrozenVehSpeed();
       Acc   = 0;
       AvacStat1_bySampleTimeLong = Cod_AvacStat1_SampleTimeShort();
    }
    else
    {
       AvacStat1_byLwrRegulationExtendedMode &= (uint8)(~STATIC_LwrFlagFreezeRegulation); 
       AvacStat1_byLwrRegulationExtendedMode &= (uint8)(~STATIC_LwrFlagPowerOnDelay);
       AvacStat1_bySampleTimeLong = Cod_AvacStat1_SampleTimeLong();
    }

    // freeze regulation, if speed is above MaxSpeed
    if( Speed >= 100 * (sint16)Cod_AvacStat1_MaxSpeed())
    {
       AvacStat1_byLwrRegulationExtendedMode |= STATIC_LwrFlagAboveMaxSpeed;
    }
    else
    {
       AvacStat1_byLwrRegulationExtendedMode &= (uint8)(~STATIC_LwrFlagAboveMaxSpeed);
    }

    // no single pulse -> Vehicle is moving, reset Values for ZeroSpeed.
    if (Speed > 100 * (sint16)Cod_AvacStat1_HighFrozenVehSpeed()) // if ( Speed > 2)
    {
      AvacStat1_nLwrLoadChangeCounter = Cod_AvacStat1_LoadChangeInterval();
      AvacStat1_byLwrRegulationExtendedMode &= (uint8)(~STATIC_LwrFlagRefAngleValid);
    }

    // definite detection of vehicle start only if 2 * MinSpeed expired
    ucHighFrozenVehSpeed = Cod_AvacStat1_HighFrozenVehSpeed();
    if( (!((AvacStat1_byLwrRegulationExtendedMode & STATIC_LwrFlagVehicleStart) != FALSE)) && (Speed > 200 * (sint16)ucHighFrozenVehSpeed) )
    {
      AvacStat1_byLwrRegulationExtendedMode |= STATIC_LwrFlagVehicleStart;
    }
  
    // --------------------------------------------------------------------------
    // set state machine:
    // --------------------------------------------------------------------------
    ucFrozenVehSpeed = Cod_AvacStat1_FrozenVehSpeed();
    if ( (AvacStat1_byLwrRegulationMode == STATIC_Lwr_Zero_Speed) && (Speed > 100 * (sint16)ucFrozenVehSpeed) )
    {  
       AvacStat1_byLwrRegulationMode = STATIC_Lwr_Vehicle_Start;
    }
    else if ( (Speed < 100 * (sint16)Cod_AvacStat1_FrozenVehSpeed()) && (AvacStat1_nLwrTransientStateCounter == 0) )
    {  
       AvacStat1_byLwrRegulationMode = STATIC_Lwr_Zero_Speed;
    }  
    else if ( (Speed < 100 * (sint16)Cod_AvacStat1_FrozenVehSpeed()) && (AvacStat1_nLwrTransientStateCounter != 0) )
    {  
       AvacStat1_byLwrRegulationMode = STATIC_Lwr_Transient_State;
    }  
    else if ( Speed <= 100 * (sint16)Cod_AvacStat1_HighFrozenVehSpeed()) // Speed > byZeroSpeed
    {
       AvacStat1_byLwrRegulationMode = STATIC_Lwr_Below_Min_Speed;
    }
    else if ( Acc >=  2* (sint16)Cod_AvacStat1_HighDynamicLimit())
    {
       AvacStat1_byLwrRegulationMode = STATIC_Lwr_Acceleration;
    }  
    else if ( (Acc <= 2 * (sint16)Cod_AvacStat1_HighDynamicLimit()) && (AvacStat1_nLwrTransientStateCounter == 0) )
    {
       AvacStat1_byLwrRegulationMode = STATIC_Lwr_Constant_Speed;
    }  
    else if ( (Acc <= 2 * (sint16)Cod_AvacStat1_HighDynamicLimit()) && (AvacStat1_nLwrTransientStateCounter != 0) )
    {
       AvacStat1_byLwrRegulationMode = STATIC_Lwr_Transient_State;
    } 
    else
    {
      // do nothing
    }
  }

  //PRQA S 5310, 5324, 5336 1 // Program architecture and code readability.
}

/*---------------------------------------------------------------------------*/

/*DOC*************************************************************************

Funktion    sint16 AvacStat1_GetHeadlightAngle(void)

Parameter   keine

Ergebnis    sint16 - Scheinwerfer-Sollwinkel
            
Beschreibung
Berechnet den Scheinwerferwinkel aus dem Fahrzeugwinkel, abhangig vom Regelmodus.

*************************************************************************DOC*/
STATIC_AL sint16 AvacStat1_GetHeadlightAngle(void)
{
  boolean boLowBeamOn;

  if(    ((AvacStat1_byLwrRegulationExtendedMode & STATIC_LwrFlagFreezeRegulation) != FALSE)
      || ((AvacStat1_byLwrRegulationExtendedMode & STATIC_LwrFlagPowerOnDelay) != FALSE) )
  {
    return AvacStat1_nActualHeadlightAngle;
  }

  switch ( AvacStat1_byLwrRegulationMode )
  {
    case STATIC_Lwr_Zero_Speed:
      if(AvacStat1_nAutoAngle > AvacStat1_nAutoAngleMax)
      {
        AvacStat1_nAutoAngle = AvacStat1_nAutoAngleMax;
      }
      if(AvacStat1_nAutoAngle < AvacStat1_nAutoAngleMin)
      {
        AvacStat1_nAutoAngle = AvacStat1_nAutoAngleMin;
      }

      // Referenzwinkel fuer Beladungskorrektur merken
      if( !((AvacStat1_byLwrRegulationExtendedMode & STATIC_LwrFlagRefAngleValid) != FALSE) )
      {
        AvacStat1_byLwrRegulationExtendedMode |= STATIC_LwrFlagRefAngleValid;
        AvacStat1_nRefAngle = AvacStat1_nAutoAngle;
      }
      
      // If vehicle has not started yet
      if( !((AvacStat1_byLwrRegulationExtendedMode & STATIC_LwrFlagVehicleStart) != FALSE) )
      {
        boLowBeamOn = AvacStat1Data_GetLowBeamOn();

        // Do Power-On-Adjustment of DC-Motor only if not already done
        if( (!((AvacStat1_byLwrRegulationExtendedMode & STATIC_LwrFlagPowerOnAdjust) != FALSE)) && (boLowBeamOn == FALSE) )
        {
          AvacStat1_byLwrRegulationExtendedMode |= STATIC_LwrFlagPowerOnAdjust;

          if( UTIL_ABS(AvacStat1_nActualHeadlightAngle + AvacStat1_nAutoAngle) >= (sint16)Cod_AvacStat1_PowerOnMinChange() )
          {
            AvacStat1_nActualHeadlightAngle = (-1) * AvacStat1_nAutoAngle;
            AvacStat1_nStaticAngle = AvacStat1_nAutoAngle;
            AvacStat1Util_Order1FilterInit(&AvacStat1_LwrStaticFilter, AvacStat1_nAutoAngle);

            AvacStat1Util_Order1FilterInit(&AvacStat1_LwrControlFilter, AvacStat1_nAutoAngle);
            AvacStat1_nControlAngle = AvacStat1_nAutoAngle;

            AvacStat1_anOldControlAngle[0] = AvacStat1_nAutoAngle;
            AvacStat1_anOldControlAngle[1] = AvacStat1_nAutoAngle;
            AvacStat1_anOldControlAngle[2] = AvacStat1_nAutoAngle;
            AvacStat1_anOldControlAngle[3] = AvacStat1_nAutoAngle;
          }

          return AvacStat1_nActualHeadlightAngle;
        }
        else
        {
          if(AvacStat1Data_GetLowBeamOn() == TRUE)
          {
            if( !( (AvacStat1_byLwrRegulationExtendedMode & STATIC_LwrFlagLightOn) != FALSE) )
            {
              AvacStat1_byLwrRegulationExtendedMode |= STATIC_LwrFlagPowerOnAdjust;
              AvacStat1_byLwrRegulationExtendedMode |= STATIC_LwrFlagLightOn;

              if( UTIL_ABS(AvacStat1_nActualHeadlightAngle + AvacStat1_nAutoAngle) >= (sint16)Cod_AvacStat1_DynamicMinChange() )
              {
                AvacStat1_nActualHeadlightAngle = (-1) * AvacStat1_nAutoAngle;
                AvacStat1_nRefAngle = AvacStat1_nAutoAngle;

                AvacStat1_nStaticAngle = AvacStat1_nAutoAngle;
                AvacStat1Util_Order1FilterInit(&AvacStat1_LwrStaticFilter, AvacStat1_nAutoAngle);

                AvacStat1Util_Order1FilterInit(&AvacStat1_LwrControlFilter, AvacStat1_nAutoAngle);
                AvacStat1_nControlAngle = AvacStat1_nAutoAngle;

                AvacStat1_anOldControlAngle[0] = AvacStat1_nAutoAngle;
                AvacStat1_anOldControlAngle[1] = AvacStat1_nAutoAngle;
                AvacStat1_anOldControlAngle[2] = AvacStat1_nAutoAngle;
                AvacStat1_anOldControlAngle[3] = AvacStat1_nAutoAngle;

                AvacStat1_nLwrLoadChangeCounter = Cod_AvacStat1_LoadChangeInterval();

                return AvacStat1_nActualHeadlightAngle;
              }
            }
          }
          else
          {
            AvacStat1_byLwrRegulationExtendedMode &= (uint8)(~STATIC_LwrFlagLightOn);
          }
        }
      }
      else // Intermediate Stop
      {
        AvacStat1_byAngleMinChange = Cod_AvacStat1_InterStopMinChange();

        if(AvacStat1_byTstatic >= Cod_AvacStat1_StaticFilterCoefAtInterStop())
        {
           AvacStat1_byTstatic = Cod_AvacStat1_StaticFilterCoefAtInterStop();
           AvacStat1_byStaticFilterSampleTime = Cod_AvacStat1_SampleTimeShort();
           AvacStat1_nLwrConstantSpeedCounter = Cod_AvacStat1_ConstantSpeedInterval();
        }

        if(AvacStat1Data_GetLowBeamOn() == TRUE)
        {
          if( !( (AvacStat1_byLwrRegulationExtendedMode & STATIC_LwrFlagLightOn) != FALSE) )
          {
            AvacStat1_byLwrRegulationExtendedMode |= STATIC_LwrFlagLightOn;

            if( UTIL_ABS(AvacStat1_nActualHeadlightAngle + AvacStat1_nAutoAngle) >= (sint16)Cod_AvacStat1_InterStopMinChange() )
            {
              AvacStat1_nActualHeadlightAngle = (-1) * AvacStat1_nAutoAngle;
              AvacStat1_nRefAngle = AvacStat1_nAutoAngle;

              AvacStat1_nStaticAngle = AvacStat1_nAutoAngle;
              AvacStat1Util_Order1FilterInit(&AvacStat1_LwrStaticFilter, AvacStat1_nAutoAngle);

              AvacStat1Util_Order1FilterInit(&AvacStat1_LwrControlFilter, AvacStat1_nAutoAngle);
              AvacStat1_nControlAngle = AvacStat1_nAutoAngle;

              AvacStat1_anOldControlAngle[0] = AvacStat1_nAutoAngle;
              AvacStat1_anOldControlAngle[1] = AvacStat1_nAutoAngle;
              AvacStat1_anOldControlAngle[2] = AvacStat1_nAutoAngle;
              AvacStat1_anOldControlAngle[3] = AvacStat1_nAutoAngle;

              AvacStat1_nLwrLoadChangeCounter    = Cod_AvacStat1_LoadChangeInterval();
              AvacStat1_byTstatic                = Cod_AvacStat1_StaticFilterCoefAtZeroSpeed();
              AvacStat1_byStaticFilterSampleTime = Cod_AvacStat1_SampleTimeShort();
              AvacStat1_nLwrConstantSpeedCounter = Cod_AvacStat1_ConstantSpeedInterval();

              return AvacStat1_nActualHeadlightAngle;
            }
          }
        }
        else
        {
          AvacStat1_byLwrRegulationExtendedMode &= (uint8)(~STATIC_LwrFlagLightOn);
        }
      }

      if( UTIL_ABS(AvacStat1_nAutoAngle - AvacStat1_nRefAngle) > (sint16)AvacStat1_byAngleMinChange ) // Load change ?
      {
        AvacStat1_byTstatic                = Cod_AvacStat1_StaticFilterCoefAtZeroSpeed();
        AvacStat1_byStaticFilterSampleTime = Cod_AvacStat1_SampleTimeShort();
        AvacStat1_nLwrConstantSpeedCounter = Cod_AvacStat1_ConstantSpeedInterval();

        if( AvacStat1_nLwrLoadChangeCounter <= 0 )
        {
          AvacStat1_nActualHeadlightAngle = (-1) * AvacStat1_nAutoAngle;
          AvacStat1_nRefAngle = AvacStat1_nAutoAngle;

          AvacStat1_nStaticAngle = AvacStat1_nAutoAngle;
          AvacStat1Util_Order1FilterInit(&AvacStat1_LwrStaticFilter, AvacStat1_nAutoAngle);

          AvacStat1_nControlAngle = AvacStat1_nAutoAngle;
          AvacStat1Util_Order1FilterInit(&AvacStat1_LwrControlFilter, AvacStat1_nAutoAngle);

          AvacStat1_anOldControlAngle[0] = AvacStat1_nAutoAngle;
          AvacStat1_anOldControlAngle[1] = AvacStat1_nAutoAngle;
          AvacStat1_anOldControlAngle[2] = AvacStat1_nAutoAngle;
          AvacStat1_anOldControlAngle[3] = AvacStat1_nAutoAngle;

          AvacStat1_nLwrLoadChangeCounter = Cod_AvacStat1_LoadChangeInterval();

        }
        else
        {  
          AvacStat1_nLwrLoadChangeCounter--;
        }
      }
      else // no Load change
      {
        AvacStat1_nLwrLoadChangeCounter = Cod_AvacStat1_LoadChangeInterval();
      }
      break; // end of case STATIC_Lwr_Zero_Speed    

    case STATIC_Lwr_Below_Min_Speed:
      AvacStat1_nLwrTransientStateCounter = Cod_AvacStat1_TransientStatePeriod();
      break; // end of case STATIC_Lwr_Below_Min_Speed

    case STATIC_Lwr_Vehicle_Start:
      AvacStat1_nLwrTransientStateCounter = Cod_AvacStat1_TransientStatePeriod();
      AvacStat1_nAutoAngleGrad = AvacStat1_nStaticAngle;
      break; // end of case STATIC_Lwr_Vehicle_Start

    case STATIC_Lwr_Transient_State:
      if( AvacStat1_nLwrTransientStateCounter != 0 )
      {
        AvacStat1_nLwrTransientStateCounter--;
      }
      break; // end of case STATIC_Lwr_Transient_State

    case STATIC_Lwr_Acceleration:
      AvacStat1_nLwrTransientStateCounter = Cod_AvacStat1_TransientStatePeriod();
      break; // end of case STATIC_Lwr_Acceleration

    case STATIC_Lwr_Constant_Speed:
      if( !( (AvacStat1_byLwrRegulationExtendedMode & STATIC_LwrFlagAboveMaxSpeed) != FALSE ) )
      {
        if( AvacStat1_nAutoAngle > (AvacStat1_nAutoAngleGrad + STATIC_AutoAngleGradientLimit) )
        {
          AvacStat1_nAutoAngleGrad = AvacStat1_nAutoAngleGrad + STATIC_AutoAngleGradientLimit;
        }
        else if ( AvacStat1_nAutoAngle < (AvacStat1_nAutoAngleGrad - STATIC_AutoAngleGradientLimit) )
        {
          AvacStat1_nAutoAngleGrad = AvacStat1_nAutoAngleGrad - STATIC_AutoAngleGradientLimit;
        }
        else
        {
          AvacStat1_nAutoAngleGrad = AvacStat1_nAutoAngle;
        }

        AvacStat1Util_Order1Filter(&AvacStat1_LwrControlFilter, AvacStat1_nAutoAngleGrad, AvacStat1_byTcontrol);
        AvacStat1_nControlAngle = AvacStat1Util_Order1FilterValue(&AvacStat1_LwrControlFilter);

        AvacStat1_anOldControlAngle[3] = AvacStat1_anOldControlAngle[2];
        AvacStat1_anOldControlAngle[2] = AvacStat1_anOldControlAngle[1];
        AvacStat1_anOldControlAngle[1] = AvacStat1_anOldControlAngle[0];
        AvacStat1_anOldControlAngle[0] = AvacStat1_nControlAngle;

        AvacStat1_nControlAngle = (sint16)(( AvacStat1_anOldControlAngle[3]
                                              + AvacStat1_anOldControlAngle[2]
                                              + AvacStat1_anOldControlAngle[1]
                                              + AvacStat1_anOldControlAngle[0]) /4);

        if( AvacStat1_SetStaticFilterParameters() != FALSE)
        {
          AvacStat1Util_Order1Filter(&AvacStat1_LwrStaticFilter, AvacStat1_nControlAngle, AvacStat1_byTstatic);
          AvacStat1_nStaticAngle = AvacStat1Util_Order1FilterValue(&AvacStat1_LwrStaticFilter);
        }


        if( (AvacStat1_byLwrRegulationExtendedMode & STATIC_LwrFlagMotorFree) != 0u )
        {

          if(AvacStat1_nStaticAngle > AvacStat1_nAutoAngleMax)
          {
            AvacStat1_nStaticAngle = AvacStat1_nAutoAngleMax;
          }

          if(AvacStat1_nStaticAngle < AvacStat1_nAutoAngleMin)
          {
            AvacStat1_nStaticAngle = AvacStat1_nAutoAngleMin;
          }

          if( UTIL_ABS(AvacStat1_nActualHeadlightAngle + AvacStat1_nStaticAngle)
              >= (sint16)Cod_AvacStat1_StaticMinChange() )
          {
            AvacStat1_nActualHeadlightAngle = (-1) * AvacStat1_nStaticAngle;
            AvacStat1_byLwrRegulationExtendedMode &= (uint8)(~STATIC_LwrFlagMotorFree);
          }
        }
      }
      break; // end of case STATIC_Lwr_Constant_Speed

    default:
      break;
  } // end of switch (LwrRegulationMode)  

  return AvacStat1_nActualHeadlightAngle;

  //PRQA S 5310, 5316, 5324, 5330, 5336, 5338 1 // Program architecture and code readability.
}   // End of Function 'GetHeadlightAngle()'


// -----------------------------------------------------------------------------
void AvacStat1_Cycle0(void)
{
  if (AvacStat1_boCodingValidity != FALSE)
  {
    STATIC_AL boolean  boEepromDataSaved = TRUE;      // cleared, if eep-write is denied, set otherwise

    STATIC_AL uint8    ucNoSampleHit = ECUFUNC_AvacStat1DownSampling;

    STATIC_AL uint8    ucSafetyAngleDelayCounter;

    STATIC_AL uint8    ucPowerOnDelayCounter = 10;

    sint16          nAccelerationRaw;
    sint16          nNewHeadlightAngle;

    uint8           byMode;
    tAvacStat_Out   AvacOut;
    sint16          nSpeed;
    tAvacStat_Speed Speed;
    tAvacStat_Pitch Pitch;
    boolean         boLowBeamOn;

    boolean         boAvacS_En;
    boolean         boAvacS_Ok;

    if (NvmBlockDeltaPwmPara.eASL_Present != eASL_Absent)
    {
      // Check and report zero lvl prog error
      AvacStat1_CheckZeroLvl();
    }
    else
    {
      // nothing to do
    }

    // --------------------------------------------------------------------------
    // Downsampling
    // --------------------------------------------------------------------------
    if (--ucNoSampleHit != 0u)
    {
      return;
    }
    else
    {
      ucNoSampleHit = ECUFUNC_AvacStat1DownSampling;
    }


    // --------------------------------------------------------------------------
    // AVAC
    // --------------------------------------------------------------------------

    // Get input values
    AvacStat1Data_ReadPitch(&Pitch);
    AvacStat1Data_ReadSpeed(&Speed);
    boLowBeamOn = AvacStat1Data_GetLowBeamOn();

    switch (Speed.eSigQty) // inclusive Acceleration
    {
    case SIG_INVALID:
      byMode = REGULATION_ModeNoDynamic;
      break;

    case SIG_INIT:
    case SIG_SNA:
      byMode = REGULATION_ModeFreezeRegulation;
      break;

    case SIG_VALID:
      byMode = REGULATION_ModeNormal;
      break;

    default: // this should not happen
      byMode = REGULATION_ModeFreezeRegulation;
      break;
    }
    nSpeed = Speed.nSpeed;
    nAccelerationRaw = Speed.nAcceleration;

    if (Pitch.eSigQty != SIG_VALID)
    {
      byMode = REGULATION_ModeFreezeRegulation;
    }
    AvacStat1_nAutoAngle = Pitch.nAngle;

    boAvacS_En = AvacStat1Data_GetAvacS_En();
    boAvacS_Ok = AvacStat1Data_GetAvacS_Ok();

    // Freeze regulation, if disabled
    if ((!(boAvacS_En != FALSE)) || (!(boAvacS_Ok != FALSE)))
    {
      byMode = REGULATION_ModeFreezeRegulation;
    }

    // Calc new headlight angle
    AvacStat1_SetRegMode(nSpeed, nAccelerationRaw, byMode);
    nNewHeadlightAngle = AvacStat1_GetHeadlightAngle();

    // Enable Power On Adjustment by setting low beam to "on"
    if ((ucPowerOnDelayCounter != 0u) && (byMode != REGULATION_ModeFreezeRegulation))
    {
      ucPowerOnDelayCounter--;
      boLowBeamOn = TRUE;
    }

    // Update Eeprom HeadlightAngle only if changed, and "light is on"
    if ((NvmGet_AvacStat1_HeadlightAngle() != nNewHeadlightAngle) && (boLowBeamOn == TRUE))
    {
      // Store new HeadlightAngle
      NvmSet_AvacStat1_HeadlightAngle(nNewHeadlightAngle);

      // Reset counter for SafetyAngle
      ucSafetyAngleDelayCounter = ECUFUNC_AvacStat1SafetyAngleDelay; // 20s


      // update adjustment counter, avoid counter overflow
      if (NvmGet_AvacStat1_AdjCounter() < 65535u)
      {
        uint16 unCnt = NvmGet_AvacStat1_AdjCounter();
        NvmSet_AvacStat1_AdjCounter(unCnt++);
      }

      // update of EepromData is necessary
      boEepromDataSaved = FALSE;
    }

    // Update SafetyAngle
    if (Pitch.eSigQty == SIG_VALID)
    {
      // Immediate update when moving down
      if (NvmGet_AvacStat1_HeadlightAngle() < NvmGet_AvacStat1_SafetyAngle())
      {
        NvmSet_AvacStat1_SafetyAngle(NvmGet_AvacStat1_HeadlightAngle());
        boEepromDataSaved = FALSE;
      }
      // Delayed update when moving up
      else if (NvmGet_AvacStat1_HeadlightAngle() > NvmGet_AvacStat1_SafetyAngle())
      {
        if (ucSafetyAngleDelayCounter > 0u)
        {
          ucSafetyAngleDelayCounter--;
        }
        else
        {
          NvmSet_AvacStat1_SafetyAngle(NvmGet_AvacStat1_HeadlightAngle());
          boEepromDataSaved = FALSE;
        }
      }
      else
      {
        // do nothing
      }
    }

    // Write new headlight angle to EEPROM, if changed or not saved
    if (boEepromDataSaved == FALSE)
    {
      boEepromDataSaved = NvmWrite_AvacStat1_StatAvacOp1Data();
    }

    // Send output values, propagate state of PitchMsg
    AvacOut.eSigQty = Pitch.eSigQty;

    // Take safety angle, if avac-state is confirmed invalid, otherwise take (possibly frozen) regulation angle
    AvacOut.nAngle = (AvacOut.eSigQty == SIG_INVALID) ? NvmGet_AvacStat1_SafetyAngle() : NvmGet_AvacStat1_HeadlightAngle();

    AvacStat1Data_WriteAvacOut((const tAvacStat_Out*)&AvacOut);

    AvacStat1_SetSpeedMode();

  }
  else
  {
    AvacStat1_boCodingValidity = AvacStat1Data_CodingDataValidation();
  }
  

#if (CFG_DEV_HOOK_EN == 1u)
  if (AvacStat1_ulTesterHookActivation == AVACSTAT1_RESET_ZLP_HOOK_KEY)
  {
    // RESET zero level programming
    if (NvmBlockDeltaPwmPara.ucZeroLevProg != 0x00u)
    {
      NvmBlockDeltaPwmPara.ucZeroLevProg &= 0x00u;
      (void)NvM_WriteBlock((NvM_BlockIdType)NvmBlockDeltaPwmParaId, (void*)&NvmBlockDeltaPwmPara);
    }
  }
  else
  {
    // nothing to do
  }
#endif

  //PRQA S 5310, 5316, 5324, 5330, 5336 1 // Program architecture and code readability.
}


/*---------------------------------------------------------------------------*/
void AvacStat1_Init(void)
{
  AvacStat1_boCodingValidity = AvacStat1Data_CodingDataValidation(); // read coding and validate it

  if (AvacStat1_boCodingValidity != FALSE)
  {
    // check if ASL feature is preset
    NvmBlockDeltaPwmPara.eASL_Present = (AvacStat1_pCodingArea->AvacStp.DCMotorData.ucAsl_Enable != FALSE) ? eASL_Present : eASL_Absent; // Asl_Enable
    NvmBlockDeltaPwmPara.eNVM_VAC_Input = eInput_HLS;
    (void)NvM_WriteBlock((NvM_BlockIdType)NvmBlockDeltaPwmParaId, (void*)&NvmBlockDeltaPwmPara);
  }

  // initialization is done after Eeprom RAM copy is loaded.
  AvacStat1_byLwrRegulationMode = STATIC_Lwr_Zero_Speed;
  AvacStat1_byLwrRegulationExtendedMode = 0;
  //Avac_wLwrMovingStatus = LWR_ZeroSpeed;

  AvacStat1_byStaticFilterSampleTime = Cod_AvacStat1_SampleTimeShort();

  // SampleTimeLong is modified by safety-concept => use copy of IpdEepRamCopy
  AvacStat1_bySampleTimeLong         = Cod_AvacStat1_SampleTimeLong();

  AvacStat1_nActualHeadlightAngle = NvmGet_AvacStat1_HeadlightAngle();
  AvacStat1_nStaticAngle = (-1) * AvacStat1_nActualHeadlightAngle;
  AvacStat1_nControlAngle = AvacStat1_nStaticAngle;

  AvacStat1Util_Order1FilterInit(&AvacStat1_LwrStaticFilter, AvacStat1_nStaticAngle);
  AvacStat1Util_Order1FilterInit(&AvacStat1_LwrControlFilter, AvacStat1_nControlAngle);
  AvacStat1Util_Order1FilterInit(&AvacStat1_LwrAccelerationFilter, 0);

  AvacStat1_byTstatic = Cod_AvacStat1_StaticFilterCoefAtZeroSpeed();
  AvacStat1_byTcontrol = STATIC_ControlFilterCoeff;

  //LwrStaticFilterCorrectionCounter = STATIC_StaticFilterCorrectionInterval;  //LwrNonVolatileOnceData.StaticFilterCorrectionInterval;
  AvacStat1_nLwrStaticFilterServiceCounter = (sint16)AvacStat1_byStaticFilterSampleTime;
  AvacStat1_nLwrConstantSpeedCounter = Cod_AvacStat1_ConstantSpeedInterval();
  AvacStat1_nLwrLoadChangeCounter = Cod_AvacStat1_LoadChangeInterval();

  AvacStat1_byAngleMinChange = Cod_AvacStat1_DynamicMinChange();

  AvacStat1_nAutoAngleMax = STATIC_AngleMin;
  AvacStat1_nAutoAngleMin = STATIC_AngleMax;

  //PRQA S 5324 1 // Program architecture and code readability.
}


//-----------------------------------------------------------------------------
/// \func   AvacStat1_SetSpeedMode()
///
/// \brief  Set speed mode based on ASL phase and speed data
///
/// \param  void 
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void AvacStat1_SetSpeedMode(void)
{
  teAvacStat1_LvlPhase eLvlPhase        = eAvacStat1State_Init;
  tAvacStat_Speed      sSpeed           = {0};
  uint8                ucFrozenVehSpeed = 0u; 
  teAvacStat_SpeedMode eSpeedMode       = eUNDEFINED;

  ucFrozenVehSpeed = Cod_AvacStat1_FrozenVehSpeed();
  AvacStat1Data_ReadAslPhase(&eLvlPhase);
  AvacStat1Data_ReadSpeed(&sSpeed);

  // Set Speed Mode
  if (eLvlPhase == eAvacStat1State_Adj)
  {
    if (sSpeed.nSpeed <= 100 * (sint16)ucFrozenVehSpeed)
    {
      eSpeedMode = eLOW_SPEED;
    }
    else
    {
      eSpeedMode = eHIGH_SPEED;
    }
  }
  else
  {
    eSpeedMode = eUNDEFINED;
  }

  // Write Data Out
  (void)AvacStat1Data_WriteSpeedMode(&eSpeedMode);
}

//EOF

// *****************************************************************************
// Filename    : AvacVddAdvanced.c
// 
// Project     : Litronic 6
// 
// Author      : Peter Ott    EEG2  (Otp2rt) / Alf Traulsen, EEG2 (taf2rt)
// Owner       : Alf Traulsen, EEG2 (taf2rt)
// 
// Date        : 12.09.2003
// 
// Description : advanced dynamic detection for dynAVAC, using additional signals
// 
// (C) Automotive-Lighting Reutlingen GmbH  -  ALRT/EEG2
//     Tuebinger Strasse 123, 72703 Reutlingen, Germany
// *****************************************************************************

#include <Cfg/Cfg.h>

#if(1) //CFG_TYP_AVACVDD == CFG_AvacVdd_Advanced)

  // PRQA S 3410 ++ // Third party header file
//  #include <stdlib.h>
  // PRQA S 3410 -- // Third party header file

  //#include <Util/UtilType.h>
  //#include <Util/UtilBase.h>

  #include <Std_Types.h>
  //#include <Util/UtilUtility.h> TO DO
  #include <../Util/UtilMath.h>
#ifndef UNIT_TEST
  #include <Rte/Rte.h>
#endif
  //#include <Nvm/Nvm.h>

  //#include "Avac.h"
  #include "AvacTypes.h"
  #include "AvacUtil.h"
  #include <Swc/AfsMaster/Avac/AvacData.h>
  #include "AvacVddAdvanced.h"
  #include "AvacVdd.h"

  // -----------------------------------------------------------------------------
  // defines
  // -----------------------------------------------------------------------------
  #define AVACVDD_CycleTime                    20u   // [ms] sampling time for digital filters in this runnable
  #define AVACVDD_AccelFilterTime             100u   // [ms] filter time for static filter
  #define AVACVDD_BadStreetHPFilterTime        80u   // [ms] filter time for bad street high pass filter
  #define AVACVDD_BadStreetLPFilterRiseTime   800u   // [ms] filter time for bad street low pass filter (rising)
  #define AVACVDD_BadStreetLPFilterFallTime  2600u   // [ms] filter time for bad street low pass filter (falling)


  // -----------------------------------------------------------------------------
  // variables
  // -----------------------------------------------------------------------------

  uint8  AvacVdd_ucDynState;        // showing constant speed/acceleration/standstill
  uint8  AvacVdd_ucAccIndex;        // acceleration change
  uint8  AvacVdd_ucBadStreetIndex;  // street quality

  //uint8  AvacVdd_ucDynStateOld;     // Comparision with new detection

  STATIC_AL sint8          AvacVdd_acAccelArray[AVACVDD_SizeofAccelerationArray]; // array to store old
                                                                              // acceleration values
  STATIC_AL ORDER1_Filter AvacVdd_AccelFilter;   // additional filtering of blackboard acceleration signal
  STATIC_AL ORDER1_Filter AvacVddBadStreetHP;    // high pass substitute for bad street detection
  STATIC_AL ORDER1_Filter AvacVddBadStreetLP;    // low pass for integration of bad street coefficient

  STATIC_AL uint16        AvacVdd_unAccelFilterCoef;            // coefficient for acceleration filtering
  STATIC_AL uint16        AvacVdd_unBadStreetHPFilterCoef;      // coefficient for bad street high pass filtering
  STATIC_AL uint16        AvacVdd_unBadStreetLPFilterCoefRise;  // coefficient for bad street low pass filtering (rising)
  STATIC_AL uint16        AvacVdd_unBadStreetLPFilterCoefFall;  // coefficient for bad street low pass filtering (falling)


  // *****************************************************************************
  // Function    : DetectVehicleDynamic_()
  //
  // Description : Set IVdd_ucDynState and IVdd_ucAccIndex
  //
  //               sampling time 20ms
  // *****************************************************************************

  // testing xxx
  //sint16 AvacVdd_nAccelerationRaw; // xxx
  //sint16 AvacVdd_nAcceleration;    // xxx
  // xxxxxxxxxxx

  void AvacVdd_DetectVehicleDynamic(void)
  {
    tAvac_Speed           Speed;
    tAvac_AccelPreDetect  AccelPreDetect;
    tAvac_BrakePreDetect  BrakePreDetect;

    sint16         nAccelerationRaw;  // absolute value of acceleration from blackboard
    sint16         nAcceleration;     // acceleration filtered

    // -----------------------------------------------------------------------------
    // get acceleration information from blackboard

    AvacData_ReadSpeed(&Speed);
    AvacData_ReadAccelPreDetect(&AccelPreDetect);
    AvacData_ReadBrakePreDetect(&BrakePreDetect);

    if(Speed.eSigQty != SIG_VALID)
    {
      AvacVddSetDynState_(AVACVDD_DynState_Invalid);
      AvacVddSetAccIndex_(AVACVDD_AccIndex_Invalid);
    }
    else
    {
      // -----------------------------------------------------------------------------
      // prepare absolute acceleration values: raw and filtered

      nAccelerationRaw = Speed.nAcceleration;

      // additional filtering time 100ms
      Order1Filter(&AvacVdd_AccelFilter, nAccelerationRaw, AvacVdd_unAccelFilterCoef);
      nAcceleration    =  Order1FilterValue(&AvacVdd_AccelFilter);

      nAcceleration    = (sint16)UTIL_ABS(nAcceleration);
      nAccelerationRaw = (sint16)UTIL_ABS(nAccelerationRaw);

      // -----------------------------------------------------------------------------
      // prepare dynamic state

      sint8 scAccelPreDetectThresholdUp   = Cod_AvacAccelPreDetectThresholdUp();
      sint8 scAccelPreDetectThresholdDown = Cod_AvacAccelPreDetectThresholdDown();
      sint8 scBrakePreDetectThresholdUp   = Cod_AvacBrakePreDetectThresholdUp();
      sint8 scBrakePreDetectThresholdDown = Cod_AvacBrakePreDetectThresholdDown();

      if( Speed.nSpeed < AVACVDD_MinSpeed )
      {
        AvacVddSetDynState_(AVACVDD_DynState_ZeroSpeed);
      }
      else if( nAccelerationRaw >= (sint16)Cod_AvacHighDynamicLimit() )
      {
        AvacVddSetDynState_(AVACVDD_DynState_HighAccel);
      }
      else if(    (     ( AccelPreDetect.eSigQty == SIG_VALID )
                    &&  (    (AccelPreDetect.nDelta >= (sint16)scAccelPreDetectThresholdUp)
                          || (AccelPreDetect.nDelta <= (sint16)scAccelPreDetectThresholdDown)
                        )
                  )
               || (     ( BrakePreDetect.eSigQty == SIG_VALID )
                    &&  (    (BrakePreDetect.nValue >= (sint16)scBrakePreDetectThresholdUp)
                          || (BrakePreDetect.nValue <= (sint16)scBrakePreDetectThresholdDown)
                        )
                  )
             )
      {
        AvacVddSetDynState_(AVACVDD_DynState_HighAccel);
      }
      else if(nAcceleration <= AVACVDD_LowDynamicLimit)
      {
        AvacVddSetDynState_(AVACVDD_DynState_ConstSpeed);
      }
      else
      {
        AvacVddSetDynState_(0);
      }

      // -----------------------------------------------------------------------------
      // prepare old dynamic state (comparision)
      /*
      if( (S14_GET_VALUE(SpeedMsg.Speed) ) < AVACVDD_MinSpeed )
      {
        AvacVdd_ucDynStateOld = AVACVDD_DynState_ZeroSpeed;
      }
      else if(AvacVdd_nAccelerationRaw >= IpdEepRamCopy.AvacData.HighDynamicLimit)
      {
        AvacVdd_ucDynStateOld = AVACVDD_DynState_HighAccel;
      }
      else if(AvacVdd_nAcceleration <= AVACVDD_LowDynamicLimit)
      {
        AvacVdd_ucDynStateOld = AVACVDD_DynState_ConstSpeed;
      }
      else
      {
        AvacVdd_ucDynStateOld = 0;
      }
      */

      // -----------------------------------------------------------------------------
      // calculate acceleration index (measurement of acceleration change)

      { // scope for variables
        //lint -esym(727, boEverySecondPass)
        static   boolean          boEverySecondPass;
        sint16         nAccelerationMax;
        sint16         nAccelerationMin;
        uint16         unDelta;           // acceleration variance in [1/10 m/s^2]
        sint16         nIndex;

        nAccelerationMin = nAcceleration;  // initialize with actual values
        nAccelerationMax = nAcceleration;

        for(nIndex = AVACVDD_SizeofAccelerationArray - 2; nIndex >= 0; nIndex--)
        {
          if(AvacVdd_acAccelArray[nIndex] > nAccelerationMax)
          {
            nAccelerationMax = AvacVdd_acAccelArray[nIndex];
          }

          if(AvacVdd_acAccelArray[nIndex] < nAccelerationMin)
          {
            nAccelerationMin = AvacVdd_acAccelArray[nIndex];
          }
          
          if(boEverySecondPass != FALSE)   // reduce sampling rate to 40ms
          {
            AvacVdd_acAccelArray[nIndex + 1] = AvacVdd_acAccelArray[nIndex];
          }
        }

        if(boEverySecondPass != FALSE)
        {
          AvacVdd_acAccelArray[0] = (sint8) nAcceleration;  // ignore overflow (possible) 
        }

        boEverySecondPass = (boEverySecondPass == TRUE) ? FALSE : TRUE;  // boEverySecondPass toggled alle 20ms

        // nAccMax > nAccMin => (nAccMax - nAccMin) > 0
        // disable lint-warning
        //lint -e734        
        //PRQA S 4393 1 // signed to unsigned cast -> see above
        unDelta = (uint16)(nAccelerationMax - nAccelerationMin);
        //lint +e734

        // calculate index as acceleration difference related to threshold value
        unDelta = (uint16)((uint32)unDelta * (AVACVDD_ScalingValue / (uint16)AVACVDD_AccelerationThreshold));

        AvacVddSetAccIndex_( (uint8) min(unDelta, AVACVDD_ScalingValue) );  // limit to 100%
      }
    }
    //PRQA S 5310, 5316, 5324, 5336 1 // Program architecture and code readability.
  }

  // *****************************************************************************
  // Function    : DetectStreetQuality_()
  // 
  // Description : Set BadStreetIndex.
  //               Do not notice signal errors because the influence of this index
  //               is small and the value normally will be 0 in error cases.
  // 
  // *****************************************************************************

  void AvacVdd_DetectStreetQuality(void)
  {
    tAvac_Pitch Pitch;
    sint16      nBadStreetSignal;
    sint16      nAutoAngle;

    AvacData_ReadPitch(&Pitch);

    nAutoAngle = Pitch.nAngle;
    Order1Filter(&AvacVddBadStreetHP, nAutoAngle, AvacVdd_unBadStreetHPFilterCoef);
    nBadStreetSignal = nAutoAngle - Order1FilterValue(&AvacVddBadStreetHP);
    nBadStreetSignal = (sint16)UTIL_ABS(nBadStreetSignal);

    // factor 1024 was evaluated by tests
    nBadStreetSignal = (sint16)( ((sint32)nBadStreetSignal * (sint16)Cod_AvacBadStreetTolerance()) / (1024 / (sint16)AVACVDD_ScalingValue) );

    // change BadStreetIndex only at constant speed
    if( AvacVddGetDynState_ConstSpeed_() != FALSE)
    {
      if(nBadStreetSignal > Order1FilterValue(&AvacVddBadStreetLP))  // rising signal
      {
        Order1Filter(&AvacVddBadStreetLP, nBadStreetSignal, AvacVdd_unBadStreetLPFilterCoefRise);
        nBadStreetSignal = Order1FilterValue(&AvacVddBadStreetLP);
      }
      else  // falling signal
      {
        Order1Filter(&AvacVddBadStreetLP, nBadStreetSignal, AvacVdd_unBadStreetLPFilterCoefFall);
        nBadStreetSignal = Order1FilterValue(&AvacVddBadStreetLP);
      }

      // remark: nBadStreetSignal >= 0, due to calling "abs" above => limiting and cast ok
      AvacVddSetBadStreetIndex_( (uint8) min(nBadStreetSignal, (sint16)AVACVDD_ScalingValue) );  // limit to 100%
    }
    //PRQA S 5324 1 // Program architecture and code readability.
  }


  // *****************************************************************************
  // Function    : void reAppAvacVddAdvanced_Init(void)
  // 
  // Description : Initialization called at system start after detecting master ECU
  // 
  // *****************************************************************************

  //void _AvacVddAdvancedInit(void)
  void AvacVdd_Init(void)
  {
    // assume that static variables are initialized by operating system

    AvacVdd_unAccelFilterCoef           = Order1FilterGetCoef(AVACVDD_CycleTime, AVACVDD_AccelFilterTime);
    AvacVdd_unBadStreetHPFilterCoef     = Order1FilterGetCoef(AVACVDD_CycleTime, AVACVDD_BadStreetHPFilterTime);
    AvacVdd_unBadStreetLPFilterCoefRise = Order1FilterGetCoef(AVACVDD_CycleTime, AVACVDD_BadStreetLPFilterRiseTime);
    AvacVdd_unBadStreetLPFilterCoefFall = Order1FilterGetCoef(AVACVDD_CycleTime, AVACVDD_BadStreetLPFilterFallTime);

    return;
  }


#endif  // (CFG_TYP_AVACVDD == CFG_AvacVdd_Advanced)

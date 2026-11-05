// *****************************************************************************
// Filename    : AvacDyn1.c
// 
// Project     : Litronic 6
// 
// Author      : Peter Ott  (otp2rt)
// Owner       : Alf Traulsen EEG2  (taf2rt)
// 
// Date        : 27.05.2002
// 
// Description : standard dynamic AVAC
// 
// (C) Automotive-Lighting Reutlingen GmbH  -  ALRT/EEG2
//     Tuebinger Strasse 123, 72703 Reutlingen, Germany
// *****************************************************************************

#include <Cfg/Cfg.h>

#if(1) //CFG_TYP_ALGAVAC == CFG_AlgAvac_Dyn1)
// Because of NULL definition this header must be first.
// PRQA S 3410 ++ // Third party header file
//#include <stdlib.h>
// PRQA S 3410 -- // Third party header file

//#include <Util/UtilType.h>
//#include <Util/UtilBase.h>

#include <Std_Types.h>
//#include <Util/UtilUtility.h> TO DO
#include <../Util/UtilMath.h>

//#include <Nvm/Nvm.h>
//#include <Ctrl/Ctrl.h>

//#include "Avac.h"
#include "AvacTypes.h"
#include <Swc/AfsMaster/Avac/AvacData.h>
#include "AvacAlgDyn1.h"
#include "AvacVdd.h"
#include "AvacUtil.h"
#include "AvacAlg.h"
#ifndef UNIT_TEST
#include "Rte.h"
#endif
#include "AL_Helper/AL_Helper.h" // TO DO


// -----------------------------------------------------------------------------
// defines
// -----------------------------------------------------------------------------
#define AVAC_StaticCycleTime       20u   // [ms] sampling time for static AVAC
#define AVAC_StaticFilterTime    2600u   // [ms] filter time for static filter


  // -----------------------------------------------------------------------------
  // variables

  #ifdef MATLAB_MEX_FILE
    #define STATIC_AVAC
  #else
#define STATIC_AVAC STATIC_AL
  #endif
  
  STATIC_AVAC sint16        Avac_nAutoAngle;         // copy of blackboard: auto angle
  STATIC_AVAC teRte_SigQty     Avac_AngleQty;           // state of angle signals

  #if(CFG_OPT_AVAC & CFG_Avac_SupportHeightCorr)
    STATIC_AVAC sint16         Avac_nHeightCorrAngle;         // copy of blackboard: height correction angle
    STATIC_AVAC sint16         Avac_nStaticHeightCorrAngle;   // filtered height corr anlge
    STATIC_AVAC ORDER1_Filter Avac_HeightCorrFilter;          // angle filter for static height corr angle
  #endif

  STATIC_AVAC uint8         Avac_ucDynamicIndex;     // factor for dynamic regulation (0...100%)
  STATIC_AVAC sint8         Avac_cDynamicIndexCtr;   // counter for delay calculation (HD mode)

  STATIC_AVAC sint16        Avac_nStaticAngleGrad;   // static angle after gradient limitation
  STATIC_AVAC sint16        Avac_nDynamicAngleGrad;  // dynamic angle after gradient limitation

  STATIC_AVAC uint8         Avac_ucActualFilterTime; // filter time used for dynamic filtering
  STATIC_AVAC boolean       Avac_boMovingUp;         // direction of dynamic headlamp movement

  STATIC_AVAC ORDER1_Filter Avac_StaticFilter;       // angle filter for static regulation
  STATIC_AVAC ORDER1_Filter Avac_DynamicFilter;      // angle filter for dynamic regulation

  STATIC_AVAC sint16        Avac_nStaticAngle;       // static headlight angle
  STATIC_AVAC sint16        Avac_nDynamicAngle;      // dynamic headlight angle
  STATIC_AVAC sint16        Avac_nAngleSum;          // sum of static and dynamic value

  STATIC_AVAC uint16        Avac_unStaticFilterCoef; // coefficient for static filtering

  //-------------------------------------------------------------------------------------
  #ifdef MATLAB_MEX_FILE

    static void InitAvacStatics()
    {
      Avac_nAutoAngle           = 0;     // copy of blackboard: auto angle
      Avac_ucAngleState         = 0;     // state of angle signals

      #if(CFG_OPT_AVAC & CFG_Avac_SupportHeightCorr)
        Avac_nHeightCorrAngle       = 0;     // copy of blackboard: height correction angle
        Avac_nStaticHeightCorrAngle = 0;     // filtered height corr angle
      #endif

      Avac_ucDynamicIndex       = 0;     
      Avac_cDynamicIndexCtr     = 0;   

      Avac_nStaticAngleGrad     = 0;   
      Avac_nDynamicAngleGrad    = 0;  

      Avac_ucActualFilterTime   = 0; 
      Avac_boMovingUp           = 0;         

      Avac_StaticFilter         = 0;       
      Avac_DynamicFilter        = 0;      

      Avac_nStaticAngle         = 0;       
      Avac_nDynamicAngle        = 0;      
      Avac_nAngleSum            = 0;          
    }

  #endif // MATLAB_MEX_FILE
  // -----------------------------------------------------------------------------------



  // *****************************************************************************
  // Function    : GetAutoAngle_()
  // 
  // Description : Read auto angle from blackboard and check signal state. Save
  //               this information static because it is needed more than once.
  // 
  // *****************************************************************************

  STATIC_AL void GetAutoAngle_(void)
  {
    tAvac_Pitch    Pitch;

    AvacData_ReadPitch(&Pitch);

    Avac_AngleQty = (AvacData_GetPitchConfigValid() == TRUE ) ? Pitch.eSigQty : SIG_INVALID ;

    if(Avac_AngleQty == SIG_VALID)
    {
      Avac_nAutoAngle = Pitch.nAngle;

      #if(CFG_OPT_AVAC & CFG_Avac_SupportHeightCorr)
        Avac_nHeightCorrAngle = Pitch.nHeightErr;
        //Avac_nHeightCorrAngle = (-1) * Avac_nHeightCorrAngle; // will produce lint-warning
        Avac_nHeightCorrAngle *= (-1);                          // uses other assambler code, no lint warning
      #endif
    }
    //PRQA S 5324 1 // Program architecture and code readability.
  }

  // *****************************************************************************
  // Function    : DoStaticRegulation_()
  // 
  // Description : calculate static headlight angle
  // 
  // *****************************************************************************

  STATIC_AL void DoStaticRegulation_(void)
  {
    //lint -esym(727, ucStartupCounter)
    static uint8  ucStartupCounter;    // count samples beginning at system start
    //tEcuFuncCtrlMsg    EcuFuncCtrlMsg;
    //
    //(void) Rte_Read_SigPrepRx_EcuFuncCtrlMsg_Port(&EcuFuncCtrlMsg);

    if(ucStartupCounter < 255u)
    {
      ucStartupCounter++;
    }

    boolean boAvacData_GetAvacS_Ok          = AvacData_GetAvacS_Ok();
    boolean boAvacData_GetAvacS_En          = AvacData_GetAvacS_En();
    boolean boAvacVddGetDynState_ConstSpeed = AvacVddGetDynState_ConstSpeed_();
    boolean boAvacVddGetDynState_ZeroSpeed  = AvacVddGetDynState_ZeroSpeed_();
    boolean boAvacVddGetDynState_Invalid    = AvacVddGetDynState_Invalid_();

    // static regulation at constant speed or vehicle standstill
    if(((boAvacData_GetAvacS_Ok != FALSE) && (boAvacData_GetAvacS_En != FALSE)) && 
      ((boAvacVddGetDynState_ConstSpeed != FALSE) || (boAvacVddGetDynState_ZeroSpeed != FALSE) || (boAvacVddGetDynState_Invalid != FALSE)))
    {
      sint16 nGradientDown = (sint16)Cod_AvacGradietnLimiterDown(); //AVAC_StaticAngleGradNormal;
      sint16 nGradientUp   = (sint16)Cod_AvacGradientLimiterUp();   //AVAC_StaticAngleGradNormal;

      if(ucStartupCounter < 50u)      // 1 s after system start + sensor delay
      {
        nGradientDown = max(nGradientDown, AVAC_StaticAngleGradFast);
      }

      AvacUtil_RateLimiter(&Avac_nStaticAngleGrad, nGradientUp, nGradientDown, (sint16)((-1) * Avac_nAutoAngle));
      Order1Filter(&Avac_StaticFilter, Avac_nStaticAngleGrad, Avac_unStaticFilterCoef);
      Avac_nStaticAngle = Order1FilterValue(&Avac_StaticFilter);

      #if(CFG_OPT_AVAC & CFG_Avac_SupportHeightCorr)
      #error Not supported
      /*
        // calculate static HeightCorrAngle
        if( AvacVddGetDynState_ZeroSpeed_() )
        {
          Order1Filter(&Avac_HeightCorrFilter, Avac_nHeightCorrAngle, TAU_Abtast_Min);
          Avac_nStaticHeightCorrAngle = Order1FilterValue(&Avac_HeightCorrFilter);
        }
        else
        {
          Order1Filter(&Avac_HeightCorrFilter, Avac_nHeightCorrAngle, TAU_Abtast_130x);
          Avac_nStaticHeightCorrAngle = Order1FilterValue(&Avac_HeightCorrFilter);
        }
        */
      #endif
    }
    //PRQA S 5324 1 // Program architecture and code readability.
  }

  // *****************************************************************************
  // Function    : SetDynamicIndex_()
  // 
  // Description : calculate dynamic index
  // 
  // *****************************************************************************

  STATIC_AL void SetDynamicIndex_(void)
  {
    //lint -esym(727, ucSampling)
    static uint8     ucSampling;
    //tEcuFuncCtrlMsg  EcuFuncCtrlMsg;

    //(void) Rte_Read_SigPrepRx_EcuFuncCtrlMsg_Port(&EcuFuncCtrlMsg);

    boolean boAvacData_GetAvacD_Ok         = AvacData_GetAvacD_Ok();
    boolean boAvacData_GetAvacD_En         = AvacData_GetAvacD_En();
    boolean boAvacVddGetDynState_HighAccel = AvacVddGetDynState_HighAccel_();
    boolean boAvacVddGetDynState_ZeroSpeed = AvacVddGetDynState_ZeroSpeed_();

    if(((boAvacData_GetAvacD_Ok != FALSE) && (boAvacData_GetAvacD_En != FALSE)) && 
      ((boAvacVddGetDynState_HighAccel != FALSE) || (boAvacVddGetDynState_ZeroSpeed != FALSE) /*|| (AvacVddGetDynState_Invalid_())*/))
    {
      Avac_ucDynamicIndex   = AVAC_ScalingValue;
      Avac_cDynamicIndexCtr = AVAC_DynamicIndexCtrStart;
    }
    else if(Avac_ucDynamicIndex > 0u)     // hold regulation mode for a delay time, then reduce HD
    {
      if( (--Avac_cDynamicIndexCtr <= 0) && ( (++ucSampling & 0x01U) == 0x01U ) )  // end of delay time
      {
        if(Avac_ucDynamicIndex > (uint8)AVAC_DynamicIndexDown)
        {
          Avac_ucDynamicIndex -= (uint8)AVAC_DynamicIndexDown;
        }
        else
        {
          Avac_ucDynamicIndex = 0;
        }
      }
    }
    else
    {
      // do nothing
    }
    //PRQA S 5324 1 // Program architecture and code readability.
  }

  // *****************************************************************************
  // Function    : SetFilterTimeConstants_()
  // 
  // Description : calculate filter time constants for dynamic regulation by using
  //               vehicle dynamic information and headlamp moving direction. The
  //               eeprom values and the result are filter time constants
  //               relative to the sampling time of 10 ms.
  // *****************************************************************************

  STATIC_AL void SetFilterTimeConstants_(void)
  {
    uint16  unFilterMax;
    uint16  unFilterMid;
    uint16  unFilterMin;
    uint16  unFilterZeroSpeed;
    uint16  unActualFilterTime;
    uint16  unMoveBackIndex = 0;

    // -----------------------------------------------------------------------------
    // choose set of filter time constants dependent on headlamp moving direction

    if(Avac_boMovingUp != FALSE)
    {
      unFilterMax       = Cod_AvacFilterUpMax();
      unFilterMid       = Cod_AvacFilterUpMid();
      unFilterMin       = Cod_AvacFilterUpMin();
      unFilterZeroSpeed = Cod_AvacFilterUpMax();

      if(Avac_nDynamicAngle < (-1)*AVAC_MoveBackThreshold)     // headlamps clearly lower than static position
      {
        unMoveBackIndex = (uint16)(sint16)(-Avac_nDynamicAngle - AVAC_MoveBackThreshold); // check how much movement up towards 
      }                                                                            // static position is necessary
    }
    else                                                   // headlamps moving down
    {
      unFilterMax       = (uint16)Cod_AvacFilterDownMax();
      unFilterMid       = (uint16)Cod_AvacFilterDownMid();
      unFilterMin       = (uint16)Cod_AvacFilterDownMin();
      unFilterZeroSpeed = (uint16)Cod_AvacFilterDownMid();

      if(Avac_nDynamicAngle > AVAC_MoveBackThreshold)      // headlamps clearly above static position
      {
        unMoveBackIndex = (uint16)(sint16)(Avac_nDynamicAngle - AVAC_MoveBackThreshold);  // check how much movement down towards
      }                                                                            // static position is necessary
    }

    // calculate index, showing how much movement towards static position is left
    // limit unMoveBackIndex and normalize to 0...128 (0...100%)
    unMoveBackIndex = min(unMoveBackIndex, AVAC_MoveBackLimit - (uint16)AVAC_MoveBackThreshold);
    unMoveBackIndex = (uint16)(((uint32)unMoveBackIndex * AVAC_ScalingValue) / (AVAC_MoveBackLimit - (uint16)AVAC_MoveBackThreshold));

    // -----------------------------------------------------------------------------
    // calculate filter time constant

    unActualFilterTime = unFilterMax;  // initialize with default value

    if(AvacVddGetAccIndex_() != AVACVDD_AccIndex_Invalid)
    {
      // do linear interpolation between mid and max dependent on acceleration index
      unActualFilterTime -= (uint16)(((uint32)AvacVddGetAccIndex_() * ((uint32)unFilterMax - (uint32)unFilterMid)) / AVACVDD_ScalingValue);
    }

    // reduce filter time linear down to min value if unMoveBackIndex between 0 and AVAC_ScalingValue
    unActualFilterTime -= (uint16)(((uint32)unMoveBackIndex * ((uint32)unActualFilterTime - (uint32)unFilterMin)) / AVAC_ScalingValue);

    // extend filter time depending on street surface quality
    if(unActualFilterTime < (uint16)((uint16)AvacVddGetBadStreetIndex_() / (AVACVDD_ScalingValue / AVAC_BadStreetFilterTime)))
    {
      unActualFilterTime  = (uint16)((uint16)AvacVddGetBadStreetIndex_() / (AVACVDD_ScalingValue / AVAC_BadStreetFilterTime));
    }

    if ( AvacVddGetDynState_Invalid_() != FALSE)
    {
      unActualFilterTime = unFilterMid;
    }
    else if( AvacVddGetDynState_ZeroSpeed_() != FALSE)
    {
      unActualFilterTime = unFilterZeroSpeed;
    }
    else
    {
      // do nothing
    }

    Avac_ucActualFilterTime = (uint8) unActualFilterTime;

    //PRQA S 5324 1 // Program architecture and code readability.
  }


  // *****************************************************************************
  // Function    : DoDynamicRegulation_()
  // 
  // Description : calculate dynamic headlight angle
  // 
  // *****************************************************************************

  STATIC_AL void DoDynamicRegulation_(void)
  {
    sint16   nDynamicFilterInput;
    sint16   nDynamicAngle;

    nDynamicAngle = (sint16)(((-1) * Avac_nAutoAngle) - Avac_nStaticAngle);

    #if(CFG_OPT_AVAC & CFG_Avac_SupportHeightCorr)
      // calculate dynamic HeightCorrAngle
      {
        sint16 nDynamicHeightCorrAngle;

        nDynamicHeightCorrAngle = Avac_nHeightCorrAngle - Avac_nStaticHeightCorrAngle;

        // evalutate height corr angle with parameter
        if(nDynamicHeightCorrAngle > 0)
        {
          nDynamicHeightCorrAngle *= Nvm_RamCopy.AvacAdditionalPara.ucHightCorrUp;
        }
        else
        {
          nDynamicHeightCorrAngle *= Nvm_RamCopy.AvacAdditionalPara.ucHightCorrDown;
        }

        nDynamicHeightCorrAngle /= 32;
        
        nDynamicAngle += nDynamicHeightCorrAngle;
      }
    #endif

    AvacUtil_RateLimiter(&Avac_nDynamicAngleGrad, AVAC_DynamicAngleGrad, AVAC_DynamicAngleGrad, nDynamicAngle);

    Avac_nDynamicAngleGrad = AvacUtil_SignalLimiter(AVAC_DynamicAngleMax, -AVAC_DynamicAngleMax, Avac_nDynamicAngleGrad);

    #if( (1L * AVAC_ScalingValue * AVAC_DynamicAngleMax / 2) > 32767L )
      #error  AL error: overflow possible
    #endif

    nDynamicFilterInput = (sint16)(((sint32)Avac_nDynamicAngleGrad * ((sint32)Avac_ucDynamicIndex / 2)) / (sint32)(AVAC_ScalingValue / 2u));

    if(nDynamicFilterInput > Avac_nDynamicAngle)           // check direction
    {
      Avac_boMovingUp = TRUE;                              // headlamps moving up
    }
    else
    {
      Avac_boMovingUp = FALSE;
    }

    Avac_nDynamicAngle = AvacUtil_Order1FilterByRelTime(&Avac_DynamicFilter, Avac_ucActualFilterTime, nDynamicFilterInput);
    //PRQA S 5324 1 // Program architecture and code readability.
  }


  // ------------------------------------------------------------------------------
  /// Is light switched on?
  // ------------------------------------------------------------------------------
  //static inline boolean AvacDyn1_IsLightOn(void)
  //{
  //  tEnvConditionMsg EnvConditionMsg;
  //  (void) Rte_Read_SigPrepRx_EnvConditionMsg_Port(&EnvConditionMsg);

  //  // if light is switched on physically, AVAC must be active.
  //  if (EnvConditionMsg.State.LowBeam == 1U)
  //  {
  //    return TRUE;
  //  }

  //#if (CFG_OPT_ENVCOND & CFG_EnvCond_SuppLoBmOnRq)  
  //  if (EnvConditionMsg.State.LowBeamOnReq == ON) 
  //  { 
  //    return TRUE; 
  //  }
  //#endif

  //#if (CFG_OPT_AM & CFG_Am_HasExtCmd)
  //  if (IsEcuFuncCmdExt(Vacd, BbGetMessageEcuFuncCmdExt(), amPLAY))
  //  {
  //    return TRUE;
  //  }
  //#endif

  //  return FALSE;

  ////PRQA S 5338 1 // Program architecture and code readability.
  //}

  // *****************************************************************************
  // Function    : CreateOutputSignal_()
  // 
  // Description : add static and dynamic headlight angle
  //               make hysteresis
  // 
  // *****************************************************************************

  STATIC_AL void CreateOutputSignal_(void)
  {
    static boolean boLightOn = TRUE;

    sint16  nMinChange;
    sint16  nRemainingError;

    boolean boAvacVddGetDynState_ConstSpeed = AvacVddGetDynState_ConstSpeed_();
    boolean boAvacVddGetDynState_Invalid    = AvacVddGetDynState_Invalid_();

    if( (boAvacVddGetDynState_ConstSpeed != FALSE) || (boAvacVddGetDynState_Invalid != FALSE) )
    {
      nMinChange      = AVAC_AngleMinChange;
      nRemainingError = AVAC_AngleRemainingError;
    }
    else
    {
      nMinChange      = AVAC_AngleMinChangeZero;       // small hysteresis because of numeric
      nRemainingError = AVAC_AngleRemainingErrorZero;  // problems of adding dynamic and static value
    }
    
    // updata AngleSum only, if Light is switched on
    if (AvacData_GetLowBeamOn() != FALSE)
    {
      boLightOn = TRUE;

      // make hysteresis and accept a small remaining error to reduce output jitter
      if(((Avac_nStaticAngle + Avac_nDynamicAngle) - Avac_nAngleSum) >= nMinChange)
      {
        Avac_nAngleSum = Avac_nStaticAngle + Avac_nDynamicAngle - nRemainingError;
      }
      if((Avac_nAngleSum - (Avac_nStaticAngle + Avac_nDynamicAngle)) >= nMinChange)
      {
        Avac_nAngleSum = Avac_nStaticAngle + Avac_nDynamicAngle + nRemainingError;
      }

      Avac_nAngleSum = min(Avac_nAngleSum,  AVAC_OutputAngleMax);
      Avac_nAngleSum = max(Avac_nAngleSum, -AVAC_OutputAngleMax);
    }
    else
    {
      if(boLightOn != FALSE)
      {
        Avac_nAngleSum = Avac_nStaticAngle;
        boLightOn = FALSE;
      }
    }

    // -----------------------------------------------------------------------------
    // send AVAC output messages
    {
      tAvac_Out AvacOut;

      AvacOut.nAngle = Avac_nAngleSum;
      AvacOut.eSigQty = Avac_AngleQty;

      AvacData_WriteAvacOut((const tAvac_Out*)&AvacOut);
    }
    //PRQA S 5324 1 // Program architecture and code readability.
  }


  // *****************************************************************************
  // Function    : AvacAlg_Main()
  // 
  // Description : called every 20 ms to perform AVAC regulation
  // 
  // *****************************************************************************

  void AvacAlg_Main(void)
  {
    //AvacVdd_DetectVehicleDynamic(); --> called by Avac.c

    GetAutoAngle_();  // get angle and status information

    if(Avac_AngleQty == SIG_VALID)  // freeze regulation while signals are invalid
    {
      SetDynamicIndex_();
      DoDynamicRegulation_();
    }
    CreateOutputSignal_();
    //PRQA S 5324 1 // Program architecture and code readability.
  }


  // *****************************************************************************
  // Function    : AvacAlg_Add_Main()
  // 
  // Description : called every 20 ms to perform additional AVAC regulation
  // 
  // *****************************************************************************

  void AvacAlg_Add_Main(void)
  {
    //AvacVdd_DetectStreetQuality(); --> called by Avac.c

    if(Avac_AngleQty == SIG_VALID)  // freeze regulation while signals are invalid
    {
      SetFilterTimeConstants_();
      DoStaticRegulation_();
    }
    //PRQA S 5324 1 // Program architecture and code readability.
  }

  // *****************************************************************************
  // Function    : AvacAlg_Init()
  // 
  // Description : Initialization called at system start after detecting master ECU
  // 
  // *****************************************************************************

  void AvacAlg_Init(void)
  {
    //AvacVdd_Init(); --> called by Avac.c

    #ifdef MATLAB_MEX_FILE
      InitAvacStatics();
    #else

      // assume that static variables are initialized by operating system

      Avac_AngleQty = SIG_VALID;  // init. necessary ??
      Avac_nStaticAngle = 0; //CtrlGetVertSafetyAngle_();
      Avac_nStaticAngleGrad = Avac_nStaticAngle;
      Order1FilterInit(&Avac_StaticFilter, Avac_nStaticAngle);
      Avac_unStaticFilterCoef = Order1FilterGetCoef(AVAC_StaticCycleTime, AVAC_StaticFilterTime);
    #endif
    //PRQA S 5324 1 // Program architecture and code readability.
  }


  // *****************************************************************************
  // Function    : reAppAvac_DeInit()
  // 
  // Description : Deinitialization called at system shutdown
  // 
  // *****************************************************************************

  void reAppAvac_DeInit(void){ return; }

#endif  // (CFG_TYP_ALGAVAC == CFG_AlgAvac_Dyn1)

/*
  //#define USE_HeightCorrection
    #if defined(USE_HeightCorrection)
      static  sint16  StaticDisplacementFront;       // Federweg vorne statischer Zustand
      static  sint16  DisplacementFrontGrad;         // Federweg gradientenbegrenzt
      static  ORDER1_Filter  Avac_StaticFilterFront;  // static filtering of DisplacementFront
    #endif

    #if defined(USE_HeightCorrection)

      RateLimiter(&DisplacementFrontGrad, 1, 1, nFront);
      StaticDisplacementFront = Order1Filter(&Avac_StaticFilterFront, DisplacementFrontGrad, TAU_Abtast_130x);

    #endif

    #if defined(USE_HeightCorrection)
      static sint16 HeightError;             // !!!! change to "register" after application
      static sint16 HeightCorrectionAngle;
    #endif

    #if defined(USE_HeightCorrection)

      if(IpdEepRamCopy.AvacData.DefaultHeadlightRange)  // disable height correction if (DefaultHeadlightRange == 0)
      {
        HeightError = nFront - StaticDisplacementFront
                      - (sint16) (((sint32) Avac_nDynamicAngleGrad * (sint16) IpdEepRamCopy.AvacData.FrontEndOverhang) / 100);

        HeightCorrectionAngle = - HeightError / (sint16) IpdEepRamCopy.AvacData.DefaultHeadlightRange;

        Avac_nDynamicAngleGrad += HeightCorrectionAngle;
      }

    #endif
*/

//*****************************************************************************
// (C) Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Automotive Lighting Reutlingen GmbH.
//*****************************************************************************
/// ---------------------------------------------------------------------------
///
///  \file    ClLrRelation.c
///
///  \author  Bernd Dreier  Bernd.Dreier[at]al-lighting.com
///           ported by     VORNICU Tony - EEG-PM4 (F63906B)
///                         mailTo:tony.vornicu[at]al-lighting.com
///
///  \owner   Ralf Sondershaus Ralf.Sondershaus[at]al-lighting.com
///
///  \date    21.01.2007
///
///  \brief   left | right relation, 32 bit code
///
///  \descr   left | right relation, 32 bit code
///
/// ---------------------------------------------------------------------------

#include <Cfg/Cfg.h>
#include <Std_Types.h>
#include "DblcSm.h"
#include <Dbl_RteAccess.h>


#if defined (CFG_VARIANT_FULL) || defined(UNIT_TEST) // Applicable only for FULL version
#if ( CFG_TYP_CL_LR06 != CFG_Cl_None )

  #if( CFG_OPT_CL & CFG_Cl_LR_Relation2 )

    #include "ClLrRelation.h"
    #include "ClAlg.h"
  #endif

  #if (CFG_OPT_ENVCOND & CFG_EnvCond_SuppSportMode)
    #include <Swc/Rte/Rte.h>
  #endif

  //#include <Util/Util_LIT_Types.h>

#include "DblData.h"

#define DBL_TRANISTION_STEPS 10
STATIC_AL sint32 Dbl_SmoothTransition(sint32 slParam1, sint32 slParam2);


/// ---------------------------------------------------------------------------
///
/// \func         sint32 SmoothTransition(sint32 Param1, sint32 Param2)
///
/// \param slParam1            input: calculated Hoa
/// \param slParam2            input: target Hoa
///
/// \return sint32 - calculated Hoa
///
/// ---------------------------------------------------------------------------
STATIC_AL sint32 Dbl_SmoothTransition(sint32 slParam1, sint32 slParam2)
{
	sint32 slRetVal;
	if (slParam1 < slParam2)
	{
		slParam1 += DBL_TRANISTION_STEPS;
		slParam1 = min(slParam1, slParam2);
	}
	else if (slParam1 > slParam2)
	{
		slParam1 -= DBL_TRANISTION_STEPS;
		slParam1 = max(slParam1, slParam2);
	}
	else
	{
		//do nothing; at target
	}
	slRetVal = slParam1;
	return slRetVal;
}

  #if( CFG_OPT_CL & CFG_Cl_LR_Relation1 )
    /// ---------------------------------------------------------------------------
    ///
    /// \func         boolean LrRelation1( sint32 nHeadLightAngle, sint32* pnAngleLeft, sint32* pnAngleRight )
    ///
    /// \param nHeadLightAngle input: head light angle
    /// \param pnAngleLeft     output: left head light angle
    /// \param pnAngleRight    output: right head light angle
    ///
    /// \return nothing
    ///
    /// \brief        alpha | alpha/2, linear 150 - 75 [0.1°]
    ///
    /// \descr        alpha | alpha/2, linear 150 - 75 [0.1°]
    ///
    /// ---------------------------------------------------------------------------
    void LrRelation1( sint32 nHeadLightAngle, sint32* pnAngleLeft, sint32* pnAngleRight )
    {
      // left turn : nHeadLightAngle < 0
      *pnAngleLeft  = (nHeadLightAngle < 0) ? (nHeadLightAngle  ) : (nHeadLightAngle/2);
      *pnAngleRight = (nHeadLightAngle < 0) ? (nHeadLightAngle/2) : (nHeadLightAngle  );
    }
  #endif  // ( CFG_OPT_CL & CFG_Cl_LR_Relation1 )

  #if ( CFG_OPT_CL & CFG_Cl_LR_Relation2 )
/// ---------------------------------------------------------------------------
///
/// \func         boolean LrRelation2( sint32 nHla, sint32* pnAngleLeft, sint32* pnAngleRight )
///
/// \param nHla            input: head light angle
/// \param pnAngleLeft     output: left head light angle
/// \param pnAngleRight    output: right head light angle
///
/// \return nothing
///
/// \brief        alpha | alpha/2, adaptive 150 - 75 [0.1°]
///
/// \descr        alpha | alpha/2, adaptive 150 - 75 [0.1°]
///
/// ---------------------------------------------------------------------------

void LrRelation2(sint32 nHla, sint32* pnAngleLeft, sint32* pnAngleRight )
{
 static boolean boFlag = FALSE;
 boolean boIsHbActive = Dbl_GetHBStatus();
 teDbl_MountingSide eMountingSide = Dbl_GetSide();
 teTraffic eTrafficSide = Dbl_GetTrafficSide();
 static sint32 HoaLEFT = 0;
 static sint32 HoaRIGHT = 0;
 sint32 HoaLEFTTarget = 0;
 sint32 HoaRIGHTTarget = 0;
 teDbl_TypeDir eSteeringType = Dbl_RteAccess_ReadSteeringType();

 static sint32 nAlphaLEFT, nAlphaRIGHT;
 static teDir  Dir = eRight;
 sint32 slCurvature = 0;

   // switch between VehPathCurvature source: from CAN or calculated internally
  if (Dbl_sCurvatureData.ucCurvatureMode == (uint8)DBLSM_CURVATURE_RECEIVED_ON_CAN)
  {
    (void)Dbl_RteAccess_ReadCurvature(&slCurvature); // READ CURVATURE
  }
  else 
  {
     slCurvature = Dbl_sCurvatureData.slCurvatureProcessedValue; // curvature value calculated in state machine
  }
      //
      // Matlab: alpha
      //  [    (Hia*S0-2*Hoa+Hia*S1)/Hia^3]
      //  [ -(2*Hia*S0-3*Hoa+Hia*S1)/Hia^2]
      //  [                             S0]
      //  [                              0]
      //
      // Matlab: alpha/2
      //  [    (Hia*S0-2*Hoa_2+Hia*S1_2)/Hia^3]
      //  [ -(2*Hia*S0-3*Hoa_2+Hia*S1_2)/Hia^2]
      //  [                                 S0]
      //  [                                  0]

      //  
      //                             (2*Hia*S0-3*Hoa+Hia*S1)           (Hia*S0-2*Hoa+Hia*S1) 
      //  f(HLA)     =  S0 * HLA  - ------------------------- HLA^2 + ----------------------- HLA^3
      //                                     Hia^2                              Hia^3     
      //
      // define relation parameter Hia = input angle (x-axis), Hoa = output angle (y-axis)

 if (boIsHbActive == FALSE)
 {
   // right curve
   if (slCurvature <= 0)
   {
     if (eSteeringType == eDBL_TypeDir_SteeringLeft)
     {// left headlamp 
		 HoaLEFTTarget = (((sint32)CodAFSPolySolver2Angle_RHT_RightCurve(Dbl_eMountedLeft) * DBL_PIVALUE) / DBL_ANGLE_FACTOR_18); // 70
       // right headlamp 
		 HoaRIGHTTarget = (((sint32)CodAFSPolySolver2Angle_RHT_RightCurve(Dbl_eMountedRight) * DBL_PIVALUE) / DBL_ANGLE_FACTOR_18); // 70
     }
     else if (eSteeringType == eDBL_TypeDir_SteeringRight)
     {// left headlamp 
		 HoaLEFTTarget = (((sint32)CodAFSPolySolver2Angle_LHT_BothRightCurve() * DBL_PIVALUE) / DBL_ANGLE_FACTOR_18); // 80
         // right headlamp 
		 HoaRIGHTTarget = (((sint32)CodAFSPolySolver2Angle_LHT_BothRightCurve() * DBL_PIVALUE) / DBL_ANGLE_FACTOR_18); // 80
     }
     else
     {
       // do nothing; invalid hand traffic
     }
   }
   else
   {
     // left curve
     if (eSteeringType == eDBL_TypeDir_SteeringLeft)
     {// left headlamp 
		 HoaLEFTTarget = (((sint32)CodAFSPolySolver2Angle_RHT_BothLeftCurve() * DBL_PIVALUE) / DBL_ANGLE_FACTOR_18); // -80
     // right headlamp 
		 HoaRIGHTTarget = (((sint32)CodAFSPolySolver2Angle_RHT_BothLeftCurve() * DBL_PIVALUE) / DBL_ANGLE_FACTOR_18); // -80
     }
     else if (eSteeringType == eDBL_TypeDir_SteeringRight)
     {// left headlamp 
		 HoaLEFTTarget = (((sint32)CodAFSPolySolver2Angle_LHT_LeftCurve(Dbl_eMountedLeft) * DBL_PIVALUE) / DBL_ANGLE_FACTOR_18); // -70
     // right headlamp 
		 HoaRIGHTTarget = (((sint32)CodAFSPolySolver2Angle_LHT_LeftCurve(Dbl_eMountedRight) * DBL_PIVALUE) / DBL_ANGLE_FACTOR_18); // -70
     }
     else
     {
       // do nothing; invalid hand traffic
     }
     }
 }
 else
 {
	 HoaLEFTTarget = ((CodDblHbAngleMax() * DBL_PIVALUE) / DBL_ANGLE_FACTOR_18);  // PRQA S 1850 // This warning will be eliminated when CodM will be available, now is hardcoded values
	 HoaRIGHTTarget = ((CodDblHbAngleMax() * DBL_PIVALUE) / DBL_ANGLE_FACTOR_18);  // PRQA S 1850 // This warning will be eliminated when CodM will be available, now is hardcoded values
 }

 // workaround use flag as sempaphore // only once the flag will be false
 if (boFlag == FALSE)
 {
	 HoaLEFT = HoaLEFTTarget;// Dbl_SmoothTransition(HoaLEFT, HoaLEFTTarget);
	 HoaRIGHT = HoaRIGHTTarget;// Dbl_SmoothTransition(HoaRIGHT, HoaRIGHTTarget);
	 boFlag = TRUE;
 }
 else
 {
	 HoaLEFT = Dbl_SmoothTransition(HoaLEFT, HoaLEFTTarget);
	 HoaRIGHT = Dbl_SmoothTransition(HoaRIGHT, HoaRIGHTTarget);
 }
      const sint32 S0   = (sint32) (CodAFSPolySolver2Angle_S0());
      const sint32 S1   = (sint32) (CodAFSPolySolver2Angle_S1());
      const sint32 S1_2 = (sint32) (CodAFSPolySolver2Angle_S12());
      sint32 Hia;

    #if (CFG_OPT_ENVCOND & CFG_EnvCond_SuppSportMode)
      if (BbGetMessageEnvCondition().State.SportMode)
      {
        Hia = ((AFSPolySolver2Add_Angle()*DBL_PIVALUE) / DBL_ANGLE_FACTOR_18);
      }
      else
    #endif
      {
        Hia = ((CodAFSPolySolver2_Angle()*DBL_PIVALUE) / DBL_ANGLE_FACTOR_18);  // PRQA S 1850 // This warning will be eliminated when CodM will be available, now is hardcoded values
      }

   if (nHla < 0)
   {
     nHla = -nHla;
     Dir = eLeft;
   }
   else
   {
     Dir = eRight;
   }

   // calculate alpha | alpha/2 angle via cubic polynom
   nAlphaLEFT = ClPoly3(nHla, Hia, HoaLEFT, S0, S1);
   nAlphaRIGHT = ClPoly3(nHla, Hia, HoaRIGHT, S0, S1_2);

   if (eSteeringType != eDBL_TypeDir_Invalid)
   {
     *pnAngleLeft = (Dir == eLeft) ? (nAlphaLEFT) : (-nAlphaLEFT);
     *pnAngleRight = (Dir == eLeft) ? (nAlphaRIGHT) : (-nAlphaRIGHT);
   }
   else
   {
     *pnAngleLeft = 0;
     *pnAngleRight = 0;
   }
    } // PRQA S 5324, 5336, 5310  // STCAL = 13 exceeds threshold, STMIF = 5 exceeds threshold 4, STPTH = 112' exceeds threshold 80
  #endif // ( CFG_OPT_CL & CFG_Cl_LR_Relation2 )

  #if ( CFG_OPT_CL & CFG_Cl_LR_Relation4 )
    /// ---------------------------------------------------------------------------
    ///
    /// \func         boolean LrRelation4( sint32 nHeadLightAngle, sint32* pnAngleLeft, sint32* pnAngleRight )
    ///
    /// \param nHeadLightAngle input: head light angle
    /// \param pnAngleLeft     output: left head light angle
    /// \param pnAngleRight    output: right head light angle
    ///
    /// \return nothing
    ///
    /// \brief        alpha | alpha/3, adaptive 150 - 50 [0.1°]
    ///
    /// \descr        alpha | alpha/3, adaptive 150 - 50 [0.1°]
    ///
    /// ---------------------------------------------------------------------------
    void LrRelation4( sint32 nHeadLightAngle, sint32* pnAngleLeft, sint32* pnAngleRight )
    {
      // left turn
      if ( nHeadLightAngle < 0 )
      {
        register sint32 A0_X;

        //  Matlab: 
        //  alpha angle:   [      0      
        //                      7/10     
        //                      1/4250  
        //                     -1/21675000 ]
        //
        //                 7                       1                            1  
        //  AngleLeft  =  --- nHeadLightAngle  + ------ nHeadLightAngle^2 - ---------- nHeadLightAngle^3
        //                10                      4250                       21675000     
        //
        //
        //  -> *10 | /10 improvement of temporary accuracy
        //
        //
        //                                          1                            1  
        //                 7 * nHeadLightAngle  + ------ nHeadLightAngle^2 - ---------- nHeadLightAngle^3 )
        //                                         425                         2167500     
        //  AngleLeft  =  ---------------------------------------------------------------------------------- 
        //                                                       10
        //
        //  -> last term changed: 2167500 = 43350 * 50
        //
        //
        //                                          1                             nHeadLightAngle^2  
        //                 7 * nHeadLightAngle  + ------ nHeadLightAngle^2 - ( ( ------------------- ) nHeadLightAngle ) / 50
        //                                         425                                  43350     
        //  AngleLeft  =  ------------------------------------------------------------------------------------------------- 
        //                                                       10
        //
        //
        // =====================================================================================================================
        //  Matlab: 
        //  alpha/2 angle: [      0      
        //                      7/10      
        //                     -14/46117  
        //                      1/15628063 ]
        //
        //                 7                       14                           1  
        //  AngleLeft  =  --- nHeadLightAngle  - ------ nHeadLightAngle^2 + ---------- nHeadLightAngle^3
        //                10                      46117                       15628063     
        //
        //
        //  -> *10 | /10 improvement of temporary accuracy
        //
        //
        //                                         140                           10  
        //                 7 * nHeadLightAngle  - ------ nHeadLightAngle^2 - ---------- nHeadLightAngle^3 )
        //                                        46117                       15628063     
        //  AngleLeft  =  ---------------------------------------------------------------------------------- 
        //                                                       10
        //
        //  -> last term changed: 15628063 = 11 * 23 * 223 * 277 = 5129 * 3047
        //
        //
        //                                         140                            10 * nHeadLightAngle^2  
        //                 7 * nHeadLightAngle  - ------ nHeadLightAngle^2 - ( ( ----------------------- ) nHeadLightAngle ) / 3047
        //                                        46117                                5129     
        //  AngleLeft  =  ------------------------------------------------------------------------------------------------- 
        //                                                       10
        //
        //
        // =====================================================================================================================

              
        nHeadLightAngle *= -1;
        
        A0_X = nHeadLightAngle * 7;


        // alpha
        *pnAngleLeft     = ( A0_X 
                             + ( (   nHeadLightAngle * nHeadLightAngle                             ) * 1  / 425       ) 
                             - ( ( ( nHeadLightAngle * nHeadLightAngle / 43350 ) * nHeadLightAngle ) / 50L) ) 
                            / 10;

        // alpha / 2
        *pnAngleRight    = ( A0_X 
                             - ( (   (sint32)nHeadLightAngle * nHeadLightAngle * 140          ) / 46117      ) 
                             + ( ( ( (sint32)nHeadLightAngle * nHeadLightAngle * 10 / 5129    ) * nHeadLightAngle ) / 3047L) )
                           / 10;


        *pnAngleLeft  *= -1;
        *pnAngleRight *= -1;
      }
      // right turn
      else  
      {
        sint32 A0_X;

        A0_X = nHeadLightAngle * 7;


        // alpha
        *pnAngleRight     = ( A0_X 
                             + ( (   nHeadLightAngle * nHeadLightAngle                             ) * 1  / 425       ) 
                             - ( ( ( nHeadLightAngle * nHeadLightAngle / 43350 ) * nHeadLightAngle ) / 50L) ) 
                            / 10;

        // alpha / 2
        *pnAngleLeft      = ( A0_X 
                             - ( (   nHeadLightAngle * nHeadLightAngle * 140          ) / 46117      ) 
                             + ( ( ( nHeadLightAngle * nHeadLightAngle * 10 / 5129    ) * nHeadLightAngle ) / 3047L) )
                           / 10;





      }
    }
  #endif // ( CFG_OPT_CL & CFG_Cl_LR_Relation4 )

  #if( CFG_OPT_CL & CFG_Cl_LR_Relation5 )
    /// ---------------------------------------------------------------------------
    ///
    /// \func         boolean LrRelation5( sint32 nHeadLightAngle, sint32* pnAngleLeft, sint32* pnAngleRight )
    ///
    /// \param nHeadLightAngle input: head light angle
    /// \param pnAngleLeft     output: left head light angle
    /// \param pnAngleRight    output: right head light angle
    ///
    /// \return nothing
    ///
    /// \brief        alpha | alpha/3, linear 150 - 50 [0.1°]
    ///
    /// \descr        alpha | alpha/3, linear 150 - 50 [0.1°]
    ///
    /// ---------------------------------------------------------------------------
    void LrRelation5( sint32 nHeadLightAngle, sint32* pnAngleLeft, sint32* pnAngleRight )
    {
      // left turn: nHeadLightAngle < 0
      *pnAngleLeft  = (nHeadLightAngle < 0) ? (nHeadLightAngle    ) : (nHeadLightAngle / 3);
      *pnAngleRight = (nHeadLightAngle < 0) ? (nHeadLightAngle / 3) : (nHeadLightAngle    );
    }
  #endif // ( CFG_OPT_CL & CFG_Cl_LR_Relation5 )

  #if( CFG_OPT_CL & CFG_Cl_LR_Relation6 )
    /// ---------------------------------------------------------------------------
    ///
    /// \func         boolean LrRelation6( sint32 nHeadLightAngle, sint32* pnAngleLeft, sint32* pnAngleRight )
    ///
    /// \param nHeadLightAngle input: head light angle
    /// \param pnAngleLeft     output: left head light angle
    /// \param pnAngleRight    output: right head light angle
    ///
    /// \return nothing
    ///
    /// \brief        alpha | 0, linear 150 - 75 [0.1°]
    ///
    /// \descr        alpha | 0, linear 150 - 75 [0.1°]
    ///
    /// ---------------------------------------------------------------------------
    void LrRelation6( sint32 nHeadLightAngle, sint32* pnAngleLeft, sint32* pnAngleRight )
    {
      // left turn: nHeadLightAngle < 0
      *pnAngleLeft  = (nHeadLightAngle < 0) ? (nHeadLightAngle) : (0);
      *pnAngleRight = (nHeadLightAngle < 0) ? (0              ) : (nHeadLightAngle/2);
    }
  #endif // ( CFG_OPT_CL & CFG_Cl_LR_Relation5 )
 
  //-------------------------------------------------------------------------------
  //
  //                         DEVELOPMENT FUNCTIONS
  //
  //-------------------------------------------------------------------------------
 
  #if( CFG_OPT_CL & CFG_Cl_LR_RelationDev )
    /// ---------------------------------------------------------------------------
    ///
    /// \func         boolean LrRelation( sint32 nHeadLightAngle, sint32* pnAngleLeft, sint32* pnAngleRight )
    ///
    /// \param nHeadLightAngle input: head light angle
    /// \param pnAngleLeft     output: left head light angle
    /// \param pnAngleRight    output: right head light angle
    ///
    /// \return nothing
    ///
    /// \brief        for application 
    ///
    /// \descr        depending on AFSHldDevParameter settings (EEPROM), the
    /// input swiveling angle is delegated to the left and right swiveling angles.
    ///
    /// ---------------------------------------------------------------------------
    void LrRelation(sint32 nHeadLightAngle, sint32* pnAngleLeft, sint32* pnAngleRight)
    {
      switch (CodAFSHldDev_RelationType)
      {
#if( CFG_OPT_CL & CFG_Cl_LR_Relation1 )
        // alpha | alpha/2, linear 150 - 75 [0.1°]
        //   only for comparison with adaptive relations 
      case 1:
      {
        LrRelation1(nHeadLightAngle, pnAngleLeft, pnAngleRight);
      }
      break;
#endif

#if( CFG_OPT_CL & CFG_Cl_LR_Relation2 )
      // adaptive  150 - 75 [0.1°]
      //   used in standard AL projects
      case 2:
      {
        LrRelation2(nHeadLightAngle, pnAngleLeft, pnAngleRight);
      }
      break;
#endif

#if 0
      //#if( CFG_OPT_CL & CFG_Cl_LR_Relation3 )
      //  // adaptive  140 - 70 [0.1°] 
      //  //   used in DC W221 project
      //  case 3:
      //    {
      //      LrRelation3( nHeadLightAngle, pnAngleLeft, pnAngleRight );
      //    }
      //    break;
      //#endif
#endif

#if( CFG_OPT_CL & CFG_Cl_LR_Relation4 )
  // adaptive  150 - 50 [0.1°] 
  //   used in PSA X6 project
      case 4:
      {
        LrRelation4(nHeadLightAngle, pnAngleLeft, pnAngleRight);
      }
      break;
#endif

#if( CFG_OPT_CL & CFG_Cl_LR_Relation5 )
      // alpha | alpha/3, linear [0.1°] 
      //   used in PSA X6 project
      case 5:
      {
        LrRelation5(nHeadLightAngle, pnAngleLeft, pnAngleRight);
      }
      break;
#endif     

#if( CFG_OPT_CL & CFG_Cl_LR_Relation6 )
      // alpha | 0, linear [0.1°] 
      //   Ford U388
      case 6:
      {
        LrRelation6(nHeadLightAngle, pnAngleLeft, pnAngleRight);
      }
      break;
#endif     


      default:
      {
        *pnAngleLeft = 0;
        *pnAngleRight = 0;
      }
      }
    }
#endif // (CFG_OPT_CL & CFG_Cl_LR_RelationDev )
#endif 

#endif

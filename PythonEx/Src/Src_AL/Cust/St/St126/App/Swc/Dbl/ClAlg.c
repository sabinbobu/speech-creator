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
///  \file    ClAlg.c
///
///  \author  Bernd Dreier  Bernd.Dreier[at]al-lighting.com,
///           ported by     VORNICU Tony - EEG-PM4 (F63906B)
///                         mailTo:tony.vornicu[at]al-lighting.com
///
///  \owner   Ralf Sondershaus Ralf.Sondershaus[at]al-lighting.com
///
///  \date    15.02.2007
///
///  \brief   curve light algorithm, 32 bit code
///
///  \descr   curve light algorithm, 32 bit code
///
/// ---------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================

#include "Dbl_RteAccess.h"
#include "DblcSm.h"
#include <UtilMath.h>
#include <UtilDebounce.h>
#include <AL_Helper.h>
#include <Cfg/Cfg.h>


#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
#if( CFG_TYP_CL_LR06 == CFG_Cl_Alg2 )

#if (CFG_OPT_ENVCOND & CFG_EnvCond_SuppSportMode)
  //#include <Swc/Rte/Rte.h>
#endif

#include "ClAlg.h"
#include "Dblc.h"
#include "DblData.h"
#include <UtilMath.h>


// enable/disable debug macros
// #define CLDEBUG
/* PRQA S 1863, 1850, 4460, 602, 2004, 3675, 4393, 3415, 288, 5330, 3675, 1852, 1860, 4394  EOF */ // This code is generated 

//****************************************************************************
// local defines
//****************************************************************************

#if defined CLDEBUG
  #define CL_ASSERT(x) if(!(x)) _INT326(0x01)
#else
  #define CL_ASSERT(x)
#endif


//****************************************************************************
// global variables
//****************************************************************************

/// filter register for speed filter
STATIC_AL ORDER1_Filter32    Cl_Filter_Speed;

/// ---------------------------------------------------------------------------
///
/// \func     sint32 _ClPolySolverCalcMaxStartSlope( sint32 nCrev )
///
/// \brief    calculate poly solver start slope limit in dependency of reversal point Crev
///
/// \param     nCrev
///
/// \return    
///
/// \descr     
///
/// ---------------------------------------------------------------------------
STATIC_AL sint32 _ClPolySolverCalcMaxStartSlope( sint32 nCrev )  // PRQA S 602 // The name of the function will be modified in release2
{
  sint32 nSlopeLimit;
  //       
  //  Crev | start 
  //       | slope    
  // ------+--------
  //     0 |  100       
  //   500 |   81
  //  2000 |   24  
  //  7000 |    9  
  //
  nSlopeLimit = (nCrev <= 2000) ? \
    ((nCrev * 19) / -500  + 100) : \
    ((nCrev *  3) / -1000 + 30 );

  return nSlopeLimit;
}

/// ---------------------------------------------------------------------------
/// 
/// \brief       start slope calculation
///
/// \param        nV     speed     [kmh]           
/// \param        nEndC  curvature [0.000025 1/m] 
/// \param        nDir   direction [left|right]    
/// \param        nC     curvature [0.000025 1/m] 
///
/// \return       start slope                    
///
/// \descr       calculates the start slope of the polynom function in dependency 
///              of the vehicle speed and the swiveling direction
///
/// ---------------------------------------------------------------------------
STATIC_AL sint32 _ClPolySolverCalcStartSlope(sint32 nV, sint32 nEndC, teDir nDir, sint32 nC) // PRQA S 602 // The name of the function will be modified in release2
{
  static   ORDER1_Filter32 StartSlopeFilter;
  static   sint32 nPrevC;
           sint32 nSlopeTemp;
           sint32 nSlope2Temp;
           sint32 nSlopeCorr;         // slope correction, in dependency curvature gradient
           sint32 t;

  // clamp v and interpolate linearily
#if (CFG_OPT_ENVCOND & CFG_EnvCond_SuppSportMode)
  if (BbGetMessageEnvCondition().State.SportMode)
  {
    nSlopeTemp = UtilLinearInterpolatePClamp32( (sint16) nV,
                                                (sint16) CodAFSPolySolver2Add_V1(),
                                                (sint16) CodAFSPolySolver2Add_V2(),
                                                (sint16) CodAFSPolySolver2Add_Slope1((uint8)nDir),
                                                (sint16) CodAFSPolySolver2Add_Slope2((uint8)nDir));
  }
  else
#endif
  {
    nSlopeTemp = (sint32)UtilLinearInterpolatePClamp32( (sint16) nV,
                                                        (sint16) CodAFSPolySolver2_V1(),
                                                        (sint16) CodAFSPolySolver2_V2(),
                                                        (sint16) CodAFSPolySolver2_Slope1((uint8)nDir),
                                                        (sint16) CodAFSPolySolver2_Slope2((uint8)nDir));
  }

  //  calculate slope correction dependend on curvature gradient and End C
  //    (example W221 parameters)
  //  slope rises    dependend on curvature gradient rise   (problem center passing)
  //                                                                                    
  //  curvarure gradient typical values : 0  - 32 [1/ 20ms*0000025m]  =>  example: 126[degree/s]  = (C * 1024/1300)/0.02
  //                     max value      :      63 [1/ 20ms*0000025m]  =>           250[degree/s]  = (C * 1024/1300)/0.02        
  //            ( calculate curvature gradient) / nSlopeDenominator 
  //lint -e727
  {
    uint8 ucSlopeDenG;

  #if (CFG_OPT_ENVCOND & CFG_EnvCond_SuppSportMode)
    if (BbGetMessageEnvCondition().State.SportMode)
    {
      ucSlopeDenG = CodAFSPolySolver2Add_SlopeDenG((uint8)nDir);
    }
    else
  #endif
    {
      ucSlopeDenG = CodAFSPolySolver2_SlopeDenG((uint8)nDir);
    }
    if (ucSlopeDenG != 0)
    {
      nSlopeCorr  = (UTIL_ABS(nPrevC - nC) / ucSlopeDenG );
    }
    else
    {
      nSlopeCorr = 0;
    }
  }
  //lint +e727

  nSlopeTemp += nSlopeCorr;

  // store nC in order to calculate curature gradient
  nPrevC      = nC;

  // check slope upper limit
  //   range check is not necessary because slope is not reduced  
#if (CFG_OPT_ENVCOND & CFG_EnvCond_SuppSportMode)
  if (BbGetMessageEnvCondition().State.SportMode)
  {
    nSlopeTemp = min(nSlopeTemp, (sint32)NvmBlockAFSPolySolver2Add.ParameterSport[nDir].ucSlope2);
  }
  else
#endif
  {
    nSlope2Temp = (sint32)CodAFSPolySolver2_Slope2((uint8)nDir);
    nSlopeTemp = min(nSlopeTemp, nSlope2Temp);
  }

  // eliminate step width > 1
  t = _ClPolySolverCalcMaxStartSlope( nEndC );
  nSlopeTemp = min(t, nSlopeTemp);
  
  nSlopeTemp = Order1TrackingFilter32( &StartSlopeFilter ,
                                     TAU_Abtast_130x, 
                                     nSlopeTemp, 
                                     2 );
  return nSlopeTemp;
}// PRQA S 5324 //Readability

// TO BE DELETED WHEN UtilMath32 will be available

  //-----------------------------------------------------------------------------
/// \brief UtilMath_LinearInterpolateP32
///
/// \descr Linear interpolation of two points
///        Linear interpolation of two points:
///                                           
///                  x - x1                    
///        Return   -------- (y2 - y1) + y1    
///                  x2 - x1                    
///       Uses correct rounding rules, i.e. 7.6 -> 8, 7.4 -> 7
///
/// \param  lx  -> interpolation value
///         lx1 -> lower x bound
///         lx2 -> upper x bound
///         ly1 -> lower y bound
///         ly2 -> upper y bound
///
/// \return Interpolated ly value for the given lx value
//-----------------------------------------------------------------------------
sint32 UtilMath_LinearInterpolateP32(sint32 lx, sint32 lx1, sint32 lx2, sint32 ly1, sint32 ly2)
{
#define DX (lx2-lx1)
#define XX (lx -lx1)
#define DY (ly2-ly1)

  sint32 dx = DX;
  sint32 d;
  sint32 dx2;

  sint32 sdResult;

  if (dx != 0)
  {
    d = XX * DY + ly1 * dx;
    dx2 = dx / 2;

    if (d > 0)
    {
      d += dx2;
    }
    else
    {
      d -= dx2;
    }

    sdResult = d / dx;
  }
  else
  {
    sdResult = ly1;
  }

  return sdResult;

#undef DX
#undef XX
#undef DY
}

//-----------------------------------------------------------------------------
/// \brief      Linear interpolations, 32 bit cod
///
/// \descr      Linear interpolation of two points of signed integers with clamping
///
/// \param  x   -
/// \param  x1  -
/// \param  x2  -
/// \param  y1  -
/// \param  y2  -
///
/// \return     sint16
//-----------------------------------------------------------------------------
 sint16  UtilLinearInterpolatePClamp32(sint16 x, sint16 x1, sint16 x2, sint16 y1, sint16 y2)
{
  x = min(x2, max(x1, x));
  return UtilMath_LinearInterpolateP32((sint32)x, (sint32)x1, (sint32)x2, (sint32)y1, (sint32)y2);
}

/// ---------------------------------------------------------------------------
///
/// \brief        end slope calculation
///
/// \param        nC    curvature
/// \param        nRise 
///
/// \return       end slope                    
///
/// \descr       calculates the end slope of the polynom function in dependency 
///              of the swiveling direction and curvature
///
/// ---------------------------------------------------------------------------
STATIC_AL sint32 _ClPolySolverCalcEndSlope( sint32 nC, teDir nDir  )
{
  #define END_SLOPE_CHANG_DELAY 4
  
 volatile static  sint32 nSlopeEnd;       // actual Slope 
          sint32 nSlopeTemp;      // new calculated Slope 

#if (CFG_OPT_ENVCOND & CFG_EnvCond_SuppSportMode)
  if (BbGetMessageEnvCondition().State.SportMode)
  {
    // Check C
    if ( nC <= (sint32) CodAFSPolySolver2Add_C2((uint8)nDir))
    {
      // set end slope to slope 2 
      nSlopeTemp  = (sint32) CodAFSPolySolver2Add_EndSlope2((uint8)nDir);
    }
    else if ( nC >= (sint32) CodAFSPolySolver2Add_C1((uint8)nDir)
    {
      //   set end slope to slope 1 
      nSlopeTemp  = (sint32) CodAFSPolySolver2Add_EndSlope1((uint8)nDir);
      // limit end slope
      nC = nC/16;

      //  Matlab: f(nC) = a2 nL^2+ a1 nL + a0
      //  [  0      ]  a2   
      //  [ -4/225  ]  a1
      //  [ 12      ]  a0

      nSlopeTemp = min( ( ( ( -4 * nC ) / 225 ) + 12), nSlopeTemp ) ;
    }
    else
    {
      // calculat slope in dependency of C
      // 
      // \n         (C - C1) * (E2 - E1)
      // \n Slope = ---------------------  + E1
      // \n              (C2 - C1)
      //
      nSlopeTemp = UtilMath_LinearInterpolateP32(nC,
        (sint32) CodAFSPolySolver2Add_C1((uint8)nDir),
        (sint32) CodAFSPolySolver2Add_C2((uint8)nDir)),
        (sint32) CodAFSPolySolver2Add_EndSlope1((uint8)nDir),
        (sint32) CodAFSPolySolver2Add_EndSlope2((uint8)nDir));
    }    
  }
  else
#else
  {
    // Check C
    if ( nC <= (sint32) CodAFSPolySolver2_C2((uint8)nDir)) 
    {
      // set end slope to slope 2 
      nSlopeTemp  = (sint32) CodAFSPolySolver2_EndSlope2((uint8)nDir);
    }
    else if ( nC >= (sint32) CodAFSPolySolver2_C1((uint8)nDir)) 
    {
      //   set end slope to slope 1 
      nSlopeTemp  = (sint32) CodAFSPolySolver2_EndSlope1((uint8)nDir);
      // limit end slope
      nC = nC/16;

      //  Matlab: f(nC) = a2 nL^2+ a1 nL + a0
      //  [  0      ]  a2   
      //  [ -4/225  ]  a1
      //  [ 12      ]  a0

      nSlopeTemp = min( ( ( ( -4 * nC ) / 225 ) + 12), nSlopeTemp ) ;
    }
    else
    {
      // calculat slope in dependency of C
      // 
      // \n         (C - C1) * (E2 - E1)
      // \n Slope = ---------------------  + E1
      // \n              (C2 - C1)
      //
      nSlopeTemp = UtilMath_LinearInterpolateP32(nC,
        (sint32) CodAFSPolySolver2_C1((uint8)nDir),
        (sint32) CodAFSPolySolver2_C2((uint8)nDir),
        (sint32) CodAFSPolySolver2_EndSlope1((uint8)nDir),
        (sint32) CodAFSPolySolver2_EndSlope2((uint8)nDir));
    }
  }
#endif

  // eliminate step width > 1
  //lint -e727
  if (nSlopeEnd < (nSlopeTemp*END_SLOPE_CHANG_DELAY))
  //lint +e727
  {
    nSlopeEnd++;
  }
  else if (nSlopeEnd > nSlopeTemp*END_SLOPE_CHANG_DELAY)
  {
    nSlopeEnd--;
  }

  return nSlopeEnd/END_SLOPE_CHANG_DELAY;
}

/// ---------------------------------------------------------------------------
///
/// \brief       end curvature calculation
///
/// \param        nV    speed     [kmh]           
/// \param        nDir  direction [left|right] 
///
/// \return       end curvature    
///
/// \descr       calculates the end curvature the polynom function in dependency 
///              of the vehicle speed and swiveling direction
///
/// ---------------------------------------------------------------------------
STATIC_AL sint32 _ClPolySolverCalcEndC(sint32 nV, teDir nDir)
{
  sint32 nC;

  // speed dependent interpolation of nC   
  //
  //         (V - V1) * (C2 - C1)
  // nC    = ---------------------  + C1
  //              (V2 - V1)  
  //
#if (CFG_OPT_ENVCOND & CFG_EnvCond_SuppSportMode)
  if (BbGetMessageEnvCondition().State.SportMode)
  {
    nC = UtilLinearInterpolatePClamp32(nV,
      (sint32) CodAFSPolySolver2Add_V1(),
      (sint32) CodAFSPolySolver2Add_V2(),
      (sint32) CodAFSPolySolver2Add_C1((uint8)nDir),
      (sint32) CodAFSPolySolver2Add_C2((uint8)nDir));     
  }
  else
#endif
  {
    nC = (sint32)UtilLinearInterpolatePClamp32( (sint16) nV,
                                                (sint16) CodAFSPolySolver2_V1(),
                                                (sint16) CodAFSPolySolver2_V2(),
                                                CodAFSPolySolver2_C1((uint8)nDir),
                                                CodAFSPolySolver2_C2((uint8)nDir));
  }
  return nC;
}

/// ---------------------------------------------------------------------------
/// 
/// \brief       Poly Solver calculation
///
/// \param       nC    curvature 
/// \param       nVin  speed [km/h]
///
/// \return      swivelling angle
///
/// \callgraph                
///
/// \descr       poly solver calculation
/// 
/// \image html  PICT_CL_ALG_MATLAB_021213.jpg Matlab Screenshot of PolySolver Output
///
/// ---------------------------------------------------------------------------
sint32 ClPolySolver(sint32 nC, sint32 nVin)
{
  static  sint32 nCc    = 0;         // end point for the polynom function (maximal received curvature)
  static  sint32 nCprev = 0;         // curvature of previous call
  static  teDir  nDir   = eRight;      //  bend direction 
  static  uint8 nRise  = INC;        //  bend rise 
  static  uint16 unTotalSwivelBack;  // amount of curvature that has been swivelled backwards
  static  boolean boSteerBackDetect;   // variable that indicates steerback detection

  // timer for swivel back detect
  tUtilDebounceControl* Dbl_Timer_Details;

  Dbl_Timer_Details = Dbl_GetTimer();
  

  // register variables 
  sint32  nSW   = 0;
  //sint32  nSW2  = 0;
  sint32  nStartSlope;  
  sint32  nEndSlope;
  sint32  nV;  // velocity [km/h]

  // check EEPROM invalid flag
  if (Dbl_boIsCodingValid == TRUE )
  {
    // internal velocity calculation in [km/h] will be replaced in final version!!!!!
    nV = nVin/10;

    // left or right bend
    //   nC <  0 => left  bend
    //   nC >  0 => right bend
    if ( nC < 0 )
    {
      // change bend direction 
      if ( nDir == eRight )  
      {
        nCc = 0; // reset nCc      
      }

      nDir = eLeft;
#ifndef UNIT_TEST
      nC   = UTIL_ABS(nC); // PRQA S 400 // This variable should be modified twice
#endif
#ifdef UNIT_TEST
      nC *= -1;
#endif
    }
    else if ( nC > 0)
    {
      if ( nDir == eLeft )  
      {
        nCc = 0; // reset nCc      
      }
      nDir = eRight;
    }
    else  // nC = 0
    {
      nCc = 0;   // reset nCc
    }

    // detect if nC increasing or decreasing
    if ((nCprev - nC) < -2)
    {
        // curvature is increasing
        if (nCc < nC)
        {
            // save nC in nCc 
            //   nCc is the end point for the polynom function
            nCc = nC;
        }
        nRise = INC;
  
        // reset timer and mark swivel back as not active
        Dbl_Timer_Details->eState = Di_Sna;
        boSteerBackDetect = FALSE;
        unTotalSwivelBack = 0;
  
    }
    // switch to decrement only if n
    else if ((nCprev - nC) > 2)
    {
        nRise = DEC;
  
        unTotalSwivelBack = unTotalSwivelBack + (uint16)(nCprev - nC); // PRQA S 400 // This variable should be modified twice
  
        UtilDebounce(Dbl_Timer_Details, TRUE);
  
        // check if time has expired and angle is bigger than parameter
        if ((Dbl_Timer_Details->eState == Di_On) && (unTotalSwivelBack >= CodDriveSit_SwvlBckAngle())) 
        {
            // mark driving situation as swivel back
            boSteerBackDetect = TRUE;
            unTotalSwivelBack = 0u;
        }
        else
        {
            // don t mark status as swivel back
        }
  
    }
    else
    {
        // not intended to be reached
    }
  
    // store previous curvature to calculate the rising of the C parameter
    nCprev = nC;

    // if nCc is speed dependend end point 
    //   then speed dependend end point is used for further calculations
    if (nCc == 0)
    {
       nCc = _ClPolySolverCalcEndC(nV,  nDir);
    }
    else
    {
      if (nRise == INC)
      {
      #if (CFG_OPT_ENVCOND & CFG_EnvCond_SuppSportMode)
        if (BbGetMessageEnvCondition().State.SportMode)
        {
          if (nCc <= NvmBlockAFSPolySolver2Add.ParameterSport[nDir].nC1)
          {
            if (nCc < NvmBlockAFSPolySolver2Add.ParameterSport[nDir].nC2)
            {
              // calculate speed dependend end point
              nCc = _ClPolySolverCalcEndC(nV,  nDir);
            }
          }
        }
        else
      #endif
        {
          if (nCc <= CodAFSPolySolver2_C1((uint8)nDir))
          {
            if (nCc < CodAFSPolySolver2_C2((uint8)nDir))
            {
              // calculate speed dependend end point
              nCc = _ClPolySolverCalcEndC(nV,  nDir);
            }
          }
        }
      }
    }

    // calculte start slope
    nStartSlope = _ClPolySolverCalcStartSlope(nV, nCc, nDir, nC);

    // calculte end slope
    nEndSlope   = _ClPolySolverCalcEndSlope( nCc, nDir );
  
    if ( nC <= nCc )
    {
      #define MAX_HLA_OUT        CodAFSPolySolver2_Angle()  // Head light angle output  [0.1°]  
      #define MAX_HLA_OUT_MRAD_  (((sint32)MAX_HLA_OUT*314)/18)               // Head light angle output  [mRad]
    
      //Matlab: 
      //[    (L*S+L*E-     5100)/L^3]
      //[ -(2*L*S+L*E-     7650)/L^2]
      //[                          S]
      //[                          0]

      //[    (L*S+L*E- 2*HLAOUT)/L^3]
      //[ -(2*L*S+L*E- 3*HLAOUT)/L^2]
      //[                          S]
      //[                          0]

      //
      //
      //                      2*nLCalc*nS+nLCalc*nE-3*HLAOUT              nLCalc*nS + nLCalc*E-2*HLAOUT
      //  nSW = nS * nLW -   --------------------------------  * nLW^2 + ------------------------------- * nLW^3
      //                                nLCalc^2                                   nLCalc^3
      //
      sint32 nLS; 
      sint32 nLE; 
      sint32 nHlaMradTemp;

      // check parameters
      CL_ASSERT(nCc         < BB_CurvatureMax);
      CL_ASSERT(nC          < BB_CurvatureMax);
      CL_ASSERT(nStartSlope < 45);
      CL_ASSERT(nEndSlope   < 45);

      nLS  = (nCc*nStartSlope) / 10;   // nLS max (7000 * 45) / 10 = 31500 
      nLE  = (nCc*nEndSlope  ) / 10;   // nLE max (7000 * 45) / 10 = 31500

      nSW  = nLS + nLE - (MAX_HLA_OUT_MRAD_*2L);
      nSW *= nC;
      nSW /= nCc;
      nSW += (-2*nLS - nLE) + (MAX_HLA_OUT_MRAD_*3L);
      nSW *= ((nC*nC) / nCc); // PRQA S 400 // This variable should be modified twice
      nSW /= nCc;
      nSW += (nC*nStartSlope) / 10;

      nHlaMradTemp = MAX_HLA_OUT_MRAD_;
      nSW = min(nSW, nHlaMradTemp); // PRQA S 400 // This variable should be modified twice
    }
    else
    {
      nSW = MAX_HLA_OUT_MRAD_;
    }

    if ( nDir == eLeft )
    {
      nSW *= -1;
    }
  }

  // write status of swivel back driving situation
  Dbl_SetSteerbackDetection(boSteerBackDetect);

  return nSW; 
}//PRQA S 5310, 5336, 5316, 5324  //Readability

/// reset speed filter
void ClResetSpeedFilter(void)
{
  Cl_Filter_Speed = 0;
}

/// ---------------------------------------------------------------------------
/// 
/// \brief       Calculate the idle position of the system
///
/// \param       nHla   horizontal swiveling angle
/// \param       nVin   speed [0.1 km/h]
///
/// \return      reduced or unchanged head light angle
///
/// \descr       Calculate the idle position of the system
///
/// ---------------------------------------------------------------------------
sint32 ClHlaIdlePosition(sint32 nHla, sint32 nVin)
{
  sint32 nFiteredV;
  sint32 nClParV11;
  sint32 nV;

   nV = nVin / 10;

  // subtract speed offset if speed > V0 
#if (CFG_OPT_ENVCOND & CFG_EnvCond_SuppSportMode)
  if (BbGetMessageEnvCondition().State.SportMode)
  {
    if ( nV > NvmBlockAFSPolySolver2Add.ucV0 )
    {
      nVin -= NvmBlockAFSPolySolver2Add.ucV0*10;
    }
    else 
    {
      nVin  = 0;
    }
  }
  else
#endif
  {
    if ( nV > CodAFSPolySolver2_V0() )
    {
      nVin -= CodAFSPolySolver2_V0()*10;
    }
    else 
    {
      nVin  = 0;
    }
  }

  // low pass filtering  of speed value
  nFiteredV = Order1Filter32( &Cl_Filter_Speed, TAU_Abtast_20x, nVin );

  // calculate Cl V1 Parameter
  //   V1 Parameter in     [0.1 km/h]
  //   subtract offset, V0 [0.1 km/h]
#if (CFG_OPT_ENVCOND & CFG_EnvCond_SuppSportMode)
  if (BbGetMessageEnvCondition().State.SportMode)
  {
    nClParV11 = ( NvmBlockAFSPolySolver2Add.ucV1  - 
                    NvmBlockAFSPolySolver2Add.ucV0) * 10;
  }
#endif
  {
    nClParV11 = (sint32)( CodAFSPolySolver2_V1()  - 
                    CodAFSPolySolver2_V0()) * 10;
  }

  // reduce head light angle only if 
  //   actual filtered speed is lower V11-(speed offset)
  if ((nFiteredV < nClParV11) && (nClParV11 != 0)) // PRQA S 3415 // Required operands to check if the actual filtered soeed is lower V11
  {
    // calculate reduced headlight angle
    nHla = ((nHla * nFiteredV ) / nClParV11 ); // PRQA S 400 // This variable should be modified twice
  }
  return nHla;
}

/// ---------------------------------------------------------------------------
/// 
/// \brief       Calculate the head light angle attenuation factor
///
/// \param       nC     curvature
/// \param       nVin   speed [0.1 km/h]
///
/// \return      attenuation factor 0 - 1000 [0.1%]
///
///               Function calculates the head light angle attenuation factor for 
///\n               attenuation(Daempfung) at high speed
///\n               --> first implementation: only speed dependend calculation
///\n               --> evolution: speed and steering wheel angele dependend calculation
///
/// ---------------------------------------------------------------------------
sint32 ClHlaAttenuationFactor(sint32 nC, sint32 nVin)
{ 
  sint32 nFactor;
  sint32 nV;
  sint32 lV3;
  sint32 lV4;
  (void) nC;

#if (CFG_OPT_ENVCOND & CFG_EnvCond_SuppSportMode)
  if (BbGetMessageEnvCondition().State.SportMode)
  {
    lV3 = (sint32)NvmBlockAFSPolySolver2Add.ucV3;
    lV4 = (sint32)NvmBlockAFSPolySolver2Add.ucV4;
  }
  else
#endif
  {
    lV3 = (sint32)CodAFSPolySolver2_V3();
    lV4 = (sint32)CodAFSPolySolver2_V4();
  }

  // Matlab:
  //    [     1000/(-V1+V0)]  
  //    [ -1000*V1/(-V1+V0)]
  //
  //              (V[km/n] - V4[km/h]) * 1000 
  //   nFactor = -------------------------------------
  //              ( -V4[km/h] + V3[km/h] )

  if (lV3 - lV4 != 0)
  {
    nV = min(10*lV4, max(10*lV3, nVin));

    nFactor  = 100*( nV - 10*lV4);
    nFactor /=     (lV3 -    lV4);
  }
  else
  {
    // no attenuation
    nFactor = 1000;
  }

  return nFactor;
}


/// ---------------------------------------------------------------------------
/// \func ClPoly3
///
/// \param x   polynomial parameter (i.e. nominal swiveling angle)
/// \param x1  interpolation value x
/// \param y1  interpolation value y
/// \param m0  interpolation start slope, unit [0.1]
/// \param m1  interpolation end slope, unit [0.1]
///
/// \return polynomial value
///
/// \brief calculate cubic polynomial
///
/// evaluate cubic polynomial:\n
/// \n
///                     (2*x1 *m0-3*y1 +x1 *m1)         (x1*m0 - 2*y1 + x1*m1)      \n
///  f(x) =  m0 * x  - ------------------------- x^2 + ----------------------- x^3  \n
///                             x1^2                             x1^3               \n
///\n
/// The slopes are given as [0.1] slopes, so the equation is scaled by a factor of 10.
///
/// ---------------------------------------------------------------------------
sint32 ClPoly3(sint32 x, sint32 x1, sint32 y1, sint32 m0, sint32 m1)
{
  const sint32 a = (30*y1 - x1*m1) -  2*x1*m0;
  const sint32 b = (x1*m1 + x1*m0) - 20*y1;
  sint32 p = a + (b*x)/x1;
  p *= x;
  p /= x1;
  p += x1*m0;
  p *= x;
  p /= x1;
  p /= 10;
  return p;
}

#endif // ( CFG_TYP_CL_LR06 == CFG_Cl_Alg2 )
#endif // CFG_VARIANT_FULL

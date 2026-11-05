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
///  \file    DblIdle.c
///
///  \author  Bernd Dreier  Bernd.Dreier[at]al-lighting.com
///           ported by     VORNICU Tony - EEG-PM4 (F63906B)
///                         mailTo:tony.vornicu[at]al-lighting.com
///
///  \owner   Ralf Sondershaus 
///
///  \date    05.04.2007
///
///  \brief   idle control for DBL (dead zone)
///
///  \descr   idle control for DBL (dead zone)
///
/// ---------------------------------------------------------------------------

#include <Cfg/Cfg.h>
#include "DblcSm.h"

#if ( CFG_TYP_CL_LR06 != CFG_Cl_None )

  #include <DblIdle.h>
  #include <UtilMath.h>
  #include "DblData.h"

/* PRQA S 616, 1840, 1843,  1852, 3344, 4394, 4539  EOF */ // This file uses generated code 

#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
 
  // ------------------------
  // define tIdle data type
  typedef enum 
  {
    IdleOn,
    IdleOff,
    IdleOffToOn,
    IdleOnToOff
  } tIdle;

  /// 
  /// \brief       Idle curvature signal
  ///
  /// \param       nC           curvature
  /// \param       nIdleRange   idle range (interval [-nIdleRange, +nIdleRange] of dead curvature)
  ///
  /// Transforms the input curvature signal into a biased curvature signal with a dead
  /// interval [-nIdleRange, +nIdleRange]. The curvature is zero in the dead interval.
  /// Outside the dead interval, the curvature is nC - nIdleRange.
  ///
  /// \return      nC > 0: max(0, nC-nIdleRange), nC < 0: -max(0, -nC-nIdleRange)
  ///
  ///
  sint32 ClIdleSignal( sint32 nC, sint32 nIdleRange )
  {
    register sint32 nRetValue;
    register teDir  Dir = eRight;  

    if ( nC < 0 )
    {
      nC *= -1;
      Dir = eLeft;
    }

    nRetValue = max(0, nC - nIdleRange);

    if ( Dir == eLeft)
    {
      nRetValue *= -1;
    }

    return nRetValue;	
  }

  #if ( !(CFG_OPT_CL & CFG_Cl_IdleRangeAlg2) )
    /// ---------------------------------------------------------------------------
    /// \func       sint32 ClIdleRange( sint32 nC, sint32 nCg )
    ///
    /// \brief      idle range calculation, 2nd Algorithm    
    ///
    /// \param      nC   Curvature          [0.000025/m]
    /// \param      nCg  CurvatureGradient  [0.000025/m]
    ///
    /// \return     idle range in curvature [0.000025/m]
    ///
    ///               calculates the idle range of the system, switch the idle range 
    ///               on and off dependent of the curvature and the curvature
    ///               gradient
    ///\n             switching from off to on is delayed by nIdleOnDelayTime 
    ///  
    ///\n             calling cycle time: 20ms
    ///
    /// ---------------------------------------------------------------------------
    sint32 ClIdleRange( sint32 nC, sint32 nCg )
    {
      static tIdle  ucIdleState       = IdleOn; 
      static sint32  nIdleRange        = 80;  
      static sint32  nIdleOnDelayTime  =  0;  // delay time in order to switch from off to on state
  
      register teDir Dir = eRight;

      if ( nC < 0 )
      {
         Dir = eLeft; 
         nC  = UTIL_ABS(nC);
      }

      switch ( ucIdleState )
      {
        // idle range is active
        case IdleOn:
          {
            nIdleRange = (sint32)NvmBlockAFSHld.ucIdleRange[Dir];
        
            // switch OFF idle range if "curvature > idle curvature"
            if ( nC > (sint32)NvmBlockAFSHld.ucIdleRange[Dir] )
            {
              ucIdleState = IdleOnToOff;
            }
          }
          break;

        // idle range is deactive, 
        //   signal is not reduced
        case IdleOff:
          {
            nIdleRange = 0;
            // if bendy road ends (curvature gradient low) and
            //   curvature is in idle range borders turn idle range on 
            if ( ( UTIL_ABS(nCg ) < 400 ) &&  
                 ( UTIL_ABS(nC  ) < (sint32)NvmBlockAFSHld.ucIdleRange[Dir] ) )
            {
              nIdleOnDelayTime++; 

              // wait for 200 * 20[ms]  = 4 [sec]
              if ( nIdleOnDelayTime >= 200 )
              {    
                nIdleOnDelayTime = 0;
                ucIdleState = IdleOffToOn;
              }    
            }
            else
            {
              nIdleOnDelayTime = 0;
            }
          }
          break;
  
        // switch idle range off
        case IdleOnToOff:  // 3
          {
            nIdleRange -= 2;

            if (nIdleRange < 0)
            {
              nIdleRange  = 0;
              ucIdleState = IdleOff;
            }

          }
          break;

        // switch idle range on
        case IdleOffToOn:  // 2
          {
            if ( nC > (sint32)NvmBlockAFSHld.ucIdleRange[Dir] )
            {
              ucIdleState = IdleOnToOff;
              nIdleRange -= 2;

              if ( nIdleRange < 0 )
              {
                nIdleRange = 0;
              }
            }
            else
            {
              nIdleRange += 2;
              if (nIdleRange >= (sint32)NvmBlockAFSHld.ucIdleRange[Dir] )
              {
                nIdleRange  = (sint32)NvmBlockAFSHld.ucIdleRange[Dir];
                ucIdleState = IdleOn;
              }
            }

          }
          break;
      }
      return nIdleRange;
    }

  #else  // ( CFG_OPT_CL & CFG_Cl_IdleRangeAlg2 )
    /// ---------------------------------------------------------------------------
    /// \func       INLINE uint32 Time2Inc( uint32 unTime )           
    ///
    /// \brief      time convertion to increments per 20ms calculation,
    ///
    /// \param      unTime  time [100ms]
    ///
    /// \return     increment per 20ms
    ///
    /// ---------------------------------------------------------------------------
    STATIC_AL sint32 Time2Inc( uint32 unTime )           
    { 
      return (sint32)(unTime * (100 / 20) );    // Time[100ms] * 100ms / 20ms 
    }  

    /// ---------------------------------------------------------------------------
    /// \func       INLINE uint32 Time2Step( uint32 unTime, sint32 nTarget ) 
    ///
    /// \brief    
    ///
    /// \param      unTime    time  [100ms]
    /// \param      unTarget  target to reach in time
    ///
    /// \return     increment per 20ms in order to reach target in time
    ///
    /// \descr    
    /// ---------------------------------------------------------------------------
    STATIC_AL sint32 Time2Step( uint32 unTime, sint32 nTarget ) 
    {
      sint32 unStep;
    
      if (unTime != 0)
      {
        unStep = ( nTarget / ((sint32)unTime * (100 / 20) ) ); // Time[100ms] * 100ms / 20ms
      }
      else
      {
        unStep = 1;
      }
    
      return (unStep) ? (unStep) : (1);
    }

    /// ---------------------------------------------------------------------------
    /// \func       INLINE uint32 CalcIdleRange( sint32 nV, teDir Dir )
    ///
    /// \brief    
    ///
    /// \param      nV    [km/h]         vehicle speed  
    /// \param      Dir   [left, right]  curvature direction
    /// \param      ucSc  [???]          not needed  
    ///
    /// \return     [0.000025/m]   idle range 
    ///
    /// \descr    
    /// ---------------------------------------------------------------------------
#ifndef UNIT_TEST
    STATIC_AL INLINE sint32 CalcIdleRange( sint32 nV, teDir Dir, uint8 ucSc )
#else
    sint32 CalcIdleRange(sint32 nV, teDir Dir, uint8 ucSc)
#endif
    {
      sint32 nIdle;
    
      (void)ucSc;

      if ( nV <= CodAfsIdle_IdleV0() )
      {
        nIdle = (sint32)CodAfsIdle_IdleRange0((uint8)Dir);
      }
      else if ( nV >= CodAfsIdle_IdleV1() )
      {
        nIdle = (sint32)CodAfsIdle_IdleRange1((uint8)Dir) ;
      }
      else
      {
        tPoint  pointP1;
        tPoint  pointP2;
        tLinEqu LinEquC;

        // calc idle range
        pointP1.nX = (sint16)CodAfsIdle_IdleV0();
        pointP1.nY = (sint16)CodAfsIdle_IdleRange0((uint8)Dir);
    
        pointP2.nX = (sint16)CodAfsIdle_IdleV1();
        pointP2.nY = (sint16)CodAfsIdle_IdleRange1((uint8)Dir);

        LinEquSolver(pointP1, pointP2, &LinEquC);

        nIdle = LinEquCalculator((sint16)nV, &LinEquC);
      }

      return nIdle;
    }

    /// ---------------------------------------------------------------------------
    /// \func       sint32 ClIdleRange( sint32 nV, sint32 nC, sint32 nCg )
    ///
    /// \brief      Idle range calculation in dependency of vehicle speed
    ///
    /// \param      nV   [0.1km/h]     vehicle speed    
    /// \param      nC   [0.000025/m]  curvature 
    /// \param      nCg                curvature gradient
    /// \param      ucSc [%]           steet classification 10-100%
    ///
    /// \return     [0.000025/m]   idle range
    ///
    /// ---------------------------------------------------------------------------
    sint32 ClIdleRange( sint32 nV, sint32 nC, sint32 nCg, uint8 ucSc )
    {
      static tIdle   ucIdleState       = IdleOn; 
      static sint32  nIdleRange        = 80;  
      static sint32  nIdleOnDelayTime  =  0;  // delay time in order to switch from off to on state
      static sint32  nIdleRangeTmp;     // switch to register !!!!!!!!!!!!!

      teDir Dir = eRight;

      if ( nC < 0 )
      {
         Dir = eLeft;
#ifndef UNIT_TEST
         nC  = UTIL_ABS(nC);
#else 
         nC *= -1;
#endif
      }

      // calculate idle range in dependency of vehicle speed
      nIdleRangeTmp = CalcIdleRange( nV/10, Dir, ucSc );

      switch ( ucIdleState )
      {
        // idle range is active
        case IdleOn:
          {
            nIdleRange = nIdleRangeTmp;
           
            // switch OFF idle range if "curvature > idle curvature"
            if ( nC > nIdleRangeTmp )
            {
              ucIdleState = IdleOnToOff;
          
              nIdleRange -= Time2Step( CodAfsIdle_OffTime(), nIdleRangeTmp );

              if (nIdleRange < 0)
              {
                nIdleRange  = 0;
                ucIdleState = IdleOff;
              }
            }

          }
          break;

        // idle range is deactive, 
        //   signal is not reduced
        case IdleOff:
          {
            nIdleRange = 0;
            // if bendy road ends (curvature gradient low) and
            //   curvature is in idle range borders turn idle range on 
#ifndef UNIT_TEST            
            if ( ( UTIL_ABS(nCg ) < 400 ) &&  
                 ( UTIL_ABS(nC) < nIdleRangeTmp ) 
               )
#else
            if ((UTIL_ABS(nCg) < 400) &&
              (nC < nIdleRangeTmp)
              )
#endif
            {
              nIdleOnDelayTime++; 

              // delay switch on 
              if ( nIdleOnDelayTime >= Time2Inc( CodAfsIdle_OnDelay() ) )
              {    
                nIdleOnDelayTime = 0;
                ucIdleState = IdleOffToOn;
              }    
            }
            else
            {
              nIdleOnDelayTime = 0;
            }
          }
          break;
  
        // switch idle range off
        case IdleOnToOff:  // 3
          {
            nIdleRange -= Time2Step( CodAfsIdle_OffTime(), nIdleRangeTmp );

            if (nIdleRange < 0)
            {
              nIdleRange  = 0;
              ucIdleState = IdleOff;
            }
          }
          break;

        // switch idle range on
        case IdleOffToOn:  // 2
          {
            if ( nC > nIdleRangeTmp )
            {
              ucIdleState = IdleOnToOff;
              nIdleRange -= Time2Step( CodAfsIdle_OffTime(), nIdleRangeTmp );

              if ( nIdleRange < 0 )
              {
                nIdleRange  = 0;
                ucIdleState = IdleOff;
              }
            }
            else
            {
              nIdleRange += Time2Step( CodAfsIdle_OnTime(), nIdleRangeTmp );

              if (nIdleRange >= nIdleRangeTmp )
              {
                nIdleRange  = nIdleRangeTmp;
                ucIdleState = IdleOn;
              }
            }

          }
          break;
#ifndef UNIT_TEST
        // should never be called
        default:
          {
          }
          break;
#endif
      }

      return nIdleRange;
    }

  #endif //( CFG_OPT_CL & CFG_Cl_IdleRangeAlg2 )

#endif //( CFG_TYP_CL_LR06 != CFG_Cl_None )
#endif // CFG_VARIANT_FULL

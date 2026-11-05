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
///  \file    ClAlg.h
///
///  \author  Bernd Dreier  Bernd.Dreier[at]al-lighting.com
///           ported by     VORNICU Tony - EEG-PM4 (F63906B)
///                         mailTo:tony.vornicu@al-lighting.com
///
///  \owner   Bernd Dreier   Bernd.Dreier[at]al-lighting.com
///
///  \date    26.06.2003
///
///  \brief   curve light algorithm 
///
///  \descr   curve light algorithm 
///
/// ---------------------------------------------------------------------------
#ifndef CL_ALG_2021_11_02_H_
#define CL_ALG_2021_11_02_H_

  //****************************************************************************
  // includes
  //****************************************************************************

  #include <Cfg/Cfg.h>
  #include <Std_Types.h>

  //#include <Swc/AfsMaster/Dbl/Dblc.h>

  //=============================================================================
  // externals (for use in inline functions only)
  //=============================================================================

   #if defined (CFG_VARIANT_FULL) || (UNIT_TEST) // Applicable only for FULL version

  extern boolean Dbl_boIsCodingValid;

  //****************************************************************************
  // private defines
  //****************************************************************************

  //****************************************************************************
  // public defines
  //****************************************************************************

  #if( CFG_TYP_CL_LR06 == CFG_Cl_None )

    #define _CL_SOLVER(x, y)
    #define _CL_INIT() 
 
  #elif ( CFG_TYP_CL_LR06 == CFG_Cl_Alg2 )

    #define _CL_SOLVER( LW, V )  ClPolySolver( LW, V )
    #define _CL_INIT()           ClPolyInit( )

  #else

    //#error Unsupported configuration (f.i. CFG_Cl_Alg1)

  #endif  // ( CFG_TYP_CL_LR06 == CFG_Cl_xxx )

  sint16  UtilLinearInterpolatePClamp32(sint16 x, sint16 x1, sint16 x2, sint16 y1, sint16 y2);
  sint32 UtilMath_LinearInterpolateP32(sint32 lx, sint32 lx1, sint32 lx2, sint32 ly1, sint32 ly2);
  #if ( CFG_TYP_CL_LR06 == CFG_Cl_Alg2 )
  
    void   ClPolyInit( void );
    sint32 ClPolySolver(sint32, sint32);

    // head light angle idle position
    sint32 ClHlaIdlePosition(sint32, sint32);
    sint32 ClHlaAttenuationFactor(sint32, sint32);

    /// calculate cubic polynomial, slopes are given with units [0.1]
    sint32 ClPoly3(sint32 x, sint32 x1, sint32 y1, sint32 m0, sint32 m1);

    /// reset speed filter
    void ClResetSpeedFilter(void);

#if 0
      // idle processing/ straight ahead detection
    //#if ( CFG_OPT_CL & CFG_Cl_IdleRangeAlg2 )
    //  INT32  ClIdleRange( INT32, INT32, INT32, UINT8 );
    //  INT32  ClIdleSignal( INT32, INT32 );
    //#else
    //  INT32  ClIdleRange( INT32, INT32 );
    //  INT32  ClIdleSignal( INT32, INT32 );
    //#endif
#endif

  #endif
#endif  
#endif // CL_ALG_2021_11_02_H_

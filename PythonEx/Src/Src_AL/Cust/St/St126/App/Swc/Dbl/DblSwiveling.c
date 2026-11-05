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
///  \file    DblSwiveling.c
///
///  \author  Bernd Dreier  Bernd.Dreier[at]al-lighting.com
///           ported by     VORNICU Tony - EEG-PM4 (F63906B)
///                         mailTo:tony.vornicu[at]al-lighting.com
///
///  \owner   Ralf Sondershaus Ralf.Sondershaus[at]al-lighting.com
///
///  \date    05.04.2004
///
///  \brief   swiveling rate limiter for DBL
///
///  \descr   swiveling rate limiter for DBL
///
/// ---------------------------------------------------------------------------

#include <UtilMath.h>
#include <Cfg/Cfg.h>
 
#if (CFG_TYP_CL_LR06 != CFG_Cl_None)

#include "DblSwiveling.h"
#include "DblData.h"
#include "Dbl_Types.h"
#include "Dbl_RteAccess.h"
#include "DblcSm.h"

//****************************************************************************
// Prototypes
//****************************************************************************

#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version

//  
// select swivelling rate limiter algorithm
//
#if (~CFG_OPT_CL & CFG_Cl_SwiRateLim2)

/// ---------------------------------------------------------------------------
///
/// \brief       calculate swiveling rates/steps
///
/// \descr       swivelling ratat limiter algorithm 1 is used in order to calculate swiveling rates/steps \n
///              Sets the swiveling rate limiters on the BlackBoard depending
///              on the curvatures gradient and the street classification.
///              Calculates the maximal increase / decrease of the swivelling angle per time step (i.e. per function call, per 20 ms))
///
/// \param       nC             curvature, not used in algorthm 1
/// \param       nCG            curvature gradient
/// \param       pnSwiLeft      swivelling rate for swivelling to right
/// \param       pnSwiRight     swivelling rate for swivelling to left  
/// \param       ucStreetClass  street class  [%]
///
/// ---------------------------------------------------------------------------
void DblcCalculateSwiveling(sint32 nC, sint32 nCG, uint8 ucStreetClass)
{
  sint32 nGradC;      // curvature gradient
  sint16 nOutMaxStep; // max out step [10 < x < 90]
  tsRte_SwiRateLimMsg SwiRateLim;

  // unused function parameters 
  nC = nC;  

  // calculate curvature gradient
  //   correct correction factor for normal swiveling 
  nGradC = ( nCG * NvmBlockAFSHld.ucCGCorrection );

  // check street class 
  //   in order to limit nOutMaxStep
  if ( ucStreetClass > NvmBlockAFSHld.ucHlaOutMaxStep )
  {
    nOutMaxStep = NvmBlockAFSHld.ucHlaOutMaxStep;
  }
  else if ( ucStreetClass < NvmBlockAFSHld.ucHlaOutMinStep )
  {
    nOutMaxStep = NvmBlockAFSHld.ucHlaOutMinStep; 
  }
  else
  {
    nOutMaxStep = ucStreetClass;
  }


  // curvature gradient >= 0   
  //   -> main swiveling to right
  if ( nGradC > 0 )
  {
    // limit swiveling left to min
    SwiRateLim.nLimit[Left]  = -NvmBlockAFSHld.ucHlaOutMinStep;

    // limit max
    if ( nGradC > nOutMaxStep )   
    {
      SwiRateLim.nLimit[Right] =  nOutMaxStep;
    }
    // limit min
    else if ( nGradC < NvmBlockAFSHld.ucHlaOutMinStep )
    {
      SwiRateLim.nLimit[Right] =  NvmBlockAFSHld.ucHlaOutMinStep;
    }
    else
    {
      SwiRateLim.nLimit[Right] = (sint16) nGradC; 
    }
  }
  // curvature gradient < 0   
  //   -> main swiveling to left
  else
  {
    // limit swiveling right to min
    SwiRateLim.nLimit[Right]  = NvmBlockAFSHld.ucHlaOutMinStep;

    // limit max
    if ( nGradC < -nOutMaxStep )   
    {
      SwiRateLim.nLimit[Left] =  -nOutMaxStep;
    }
    // limit min
    else if ( nGradC > -NvmBlockAFSHld.ucHlaOutMinStep )
    {
      SwiRateLim.nLimit[Left] =  -NvmBlockAFSHld.ucHlaOutMinStep;
    }
    else
    {
      SwiRateLim.nLimit[Left] = (sint16) nGradC; 
    }
  }
  (void)Rte_Write_DblSwiveling_SwiRateLimMsg_Port(&SwiRateLim);
}

#elif (CFG_OPT_CL & CFG_Cl_SwiRateLim2)

/// (internal) resolution of swiveling limits
#define DBLC_SWIV_HIGHRES   128

//----------------------------------------------------------
/// \brief       convert  0.1 Deg/Sec -> 0.1 mRad/Sec
///
/// \descr       swivelling ratat limiter algorithm 2 is used in order to calculate swiveling rates/steps 
///
/// \param       0.2 Degree / Second
/// \return      0.1 mRad / 20ms
//----------------------------------------------------------
STATIC_AL sint16 Dblc_Convert_Deg_mRad( sint16 nDeg )
{
  return (sint16) (((sint32) nDeg * 314 * 2) / (18 * 50));
}

//----------------------------------------------------------
/// \brief       convert  0.1 Deg/Sec -> 0.1 mRad/Sec
///
/// \descr       swivelling ratat limiter algorithm 2 is used in order to calculate swiveling rates/steps 
///
/// \param       0.2 Degree / Second
/// \return      0.1 mRad / 20ms
//----------------------------------------------------------
STATIC_AL sint16 Dblc_Convert_Deg_mRadHr( sint16 nDeg ) 
{
  return max(1, (sint16) (((sint32) nDeg * (DBLC_SWIV_HIGHRES * 314 * 2)) / (18 * 50 * 50)));
}

/// ---------------------------------------------------------------------------
///
/// \brief       calculate swiveling rates/steps
///
/// \descr       swivelling ratat limiter algorithm 2 is used in order to calculate swiveling rates/steps 
///
/// \param       nC             curvature
/// \param       nCG            curvature gradient
/// \param       pnSwiLeft      swivelling rate for swivelling to right
/// \param       pnSwiRight     swivelling rate for swivelling to left  
/// \param       ucStreetClass  street class  [%]
///
/// ---------------------------------------------------------------------------
void DblcCalculateSwiveling( sint32 nC, sint32 nCG, uint8 ucStreetClass )
{
 sint16 nCGCor;              // curvature gradient (high-res)
 sint16 nCGCorTemp;
 tsDbl_SwiRateLimMsg SwiRateLim;
 static  sint16 nSwi[2]   = {0,0};   // high-res for swiveling limits
 sint16 nSwiTmp[2];          // current limits for left and right *curves* (no high-res)
 sint16 nTemp;

  // unused function parameters 
  (void) ucStreetClass;

  //LINT:  initialize variables    
  nSwiTmp[0] = 0;
  nSwiTmp[1] = 0;

  // calculate curvature gradient
  //   correct correction factor for normal swiveling 
  nTemp  = Dblc_Convert_Deg_mRadHr((sint16) CodAfsSwiRateLim_ChangeRateOut());
  nCGCorTemp = (sint16)(DBLC_SWIV_HIGHRES * nCG * CodAfsSwiRateLim_CGCorrection());
  nCGCor = UTIL_ABS( nCGCorTemp ) / 10;
  nCGCor = max(nTemp, nCGCor);

  // right bend
  if ( nC >= 0 )                  // right bend 
  {
    if ( nCG > (sint32)CodAfsSwiRateLim_ConstCurvature() )         // increase bend radius 
    {
      nSwiTmp[eRight] =  Dblc_Convert_Deg_mRad((sint16) CodAfsSwiRateLim_LimOutFast());       // 1
      nSwiTmp[eLeft]  = -Dblc_Convert_Deg_mRad((sint16) CodAfsSwiRateLim_LimInSlow() );       // 2  
    }
    else if ( nCG < -(sint32)CodAfsSwiRateLim_ConstCurvature())     // decreas bend radius
    {
      nSwiTmp[eLeft]  = -Dblc_Convert_Deg_mRad((sint16) CodAfsSwiRateLim_LimInFast() );       // 5   
      nSwiTmp[eRight] =  Dblc_Convert_Deg_mRad((sint16) CodAfsSwiRateLim_LimOutSlow());       // 6 
    }
    else                           // constant bend radius
    {
      nSwiTmp[eRight] =  Dblc_Convert_Deg_mRad((sint16) CodAfsSwiRateLim_LimOutSlow());       // 3 
      nSwiTmp[eLeft]  = -Dblc_Convert_Deg_mRad((sint16) CodAfsSwiRateLim_LimInSlow() );       // 4   
    }
  }  

  // left bend
  else 
  { 
    if ( nCG < -(sint32)CodAfsSwiRateLim_ConstCurvature() )         // increase bend radius 
    {
      nSwiTmp[eLeft]  = -Dblc_Convert_Deg_mRad((sint16) CodAfsSwiRateLim_LimOutFast());      //  7
      nSwiTmp[eRight] =  Dblc_Convert_Deg_mRad((sint16) CodAfsSwiRateLim_LimInSlow() );      //  8
    }
    else if ( nCG > (sint32)CodAfsSwiRateLim_ConstCurvature())         // decreas bend radius
    {
      nSwiTmp[eRight] =  Dblc_Convert_Deg_mRad((sint16) CodAfsSwiRateLim_LimInFast() );      // 11
      nSwiTmp[eLeft]  = -Dblc_Convert_Deg_mRad((sint16) CodAfsSwiRateLim_LimOutSlow());      // 12  
    }
    else                             // constant bend radius
    {
      nSwiTmp[eLeft]  = -Dblc_Convert_Deg_mRad((sint16) CodAfsSwiRateLim_LimOutSlow());      //  9
      nSwiTmp[eRight] =  Dblc_Convert_Deg_mRad((sint16) CodAfsSwiRateLim_LimInFast() );      // 10 
    }
  }


  //------------------------------------------
  if ( (nSwi[eLeft]-nCGCor) > DBLC_SWIV_HIGHRES * nSwiTmp[eLeft] )
  {
    nSwi[eLeft] -= nCGCor;
  }
  else if ( (nSwi[eLeft] + Dblc_Convert_Deg_mRadHr((sint16) CodAfsSwiRateLim_ChangeRateIn())) < DBLC_SWIV_HIGHRES * nSwiTmp[eLeft])
  {
    nSwi[eLeft] += Dblc_Convert_Deg_mRadHr((sint16) CodAfsSwiRateLim_ChangeRateIn());
  }
  else
  {
    nSwi[eLeft] = (sint16) (DBLC_SWIV_HIGHRES * nSwiTmp[eLeft]);
  }

  //------------------------------------------
  if ((nSwi[eRight] + nCGCor) < DBLC_SWIV_HIGHRES * nSwiTmp[eRight])
  {
    nSwi[eRight] += nCGCor;
  }
  else if ((nSwi[eRight] - Dblc_Convert_Deg_mRadHr((sint16) CodAfsSwiRateLim_ChangeRateIn())) > DBLC_SWIV_HIGHRES * nSwiTmp[eRight])
  {
    nSwi[eRight] -= Dblc_Convert_Deg_mRadHr((sint16) CodAfsSwiRateLim_ChangeRateIn());
  }
  else
  {
    nSwi[eRight] = (sint16) (DBLC_SWIV_HIGHRES * nSwiTmp[eRight]);
  }

  SwiRateLim.nLimit[eLeft] = nSwi[eLeft] / DBLC_SWIV_HIGHRES;
  SwiRateLim.nLimit[eRight] = nSwi[eRight] / DBLC_SWIV_HIGHRES;
  Dbl_RteAccess_WriteSwimRate(SwiRateLim);
}// PRQA S 5324 ////Architecture and readability

#endif

/// ---------------------------------------------------------------------------
///
/// \brief Limit the swiveling angle
///
/// Limit the swiveling angle
///
/// \param       nC             curvature
/// \param       nCG            curvature gradient
/// \param       nHla           swivelling angle
/// \param       nHlaOld        swivelling angle of the previous step   
/// \param       ucStreetClass  street class  [%]
///
/// ---------------------------------------------------------------------------
sint32 DblcLimitSwiveling(sint32 nC, sint32 nCG, sint32 nHla, sint32 nHlaOld, uint8 ucStreetClass)
{
  // max. allowed swivelling step
  tsDbl_SwiRateLimMsg SwiRateLim;
  sint32 hla;
  sint32 nHlaDiff;

  // calculate swiveling rates/steps     
  DblcCalculateSwiveling( nC, nCG, ucStreetClass );

  // read back limits from black board
  SwiRateLim = Dbl_RteAccess_ReadSwimRate();

  // detect swiveling direction 
  //   > 0 => swivelling right
  //   < 0 => swivelling left
  nHlaDiff = nHla - nHlaOld;

  // swiveling right
  if ( nHlaDiff > 0 )
  {
    // if new calculated head light angle is less 
    //   than the old head light angle + new allowed swivelling range
    //   use the new calculate head light angle
    //   otherwise use the old head light angle + the new allowed swivelling step
    if ( nHla <= ( nHlaOld + SwiRateLim.nLimit[eRight]) )  
    {
      hla = nHla;
    }  
    else
    {
      hla = nHlaOld + SwiRateLim.nLimit[eRight];
    }
  }
  // swiveling left
  else if( nHlaDiff < 0 )
  {
    // nSwiLeft negative value !!!!!
    if ( nHla >= ( nHlaOld + SwiRateLim.nLimit[eLeft]) )  
    {
      hla = nHla;
    }  
    else
    {
      hla = nHlaOld + SwiRateLim.nLimit[eLeft];
    }
  }
  else
  {
    hla = nHlaOld;
  }

  return hla;
}

#endif // (CFG_TYP_CL_LR06 != CFG_Cl_None)
#endif // CFG_VARIANT_FULL

#ifndef __CDDSTPDYN_H__
#define __CDDSTPDYN_H__

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
  /// \file  CddStpDyn.h
  ///
  /// \brief  
  ///
  /// \descr  
  ///
  ///         Additional information can be found in the design description (Link:
  ///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
  ///
  /// \author Ott, Peter ALRT/EEG-PM2 *  (otp2rt)
  ///         mailTo:Peter.Ott@al-lighting.com       
  //-----------------------------------------------------------------------------

  #include <Std_Types.h>
  #include <CddStpTypes.h>  // incl. '88XX/CddStp88XX_HalStp.h'


  //  ---------------------------------------------------------------------------
  //  defines
  //  ---------------------------------------------------------------------------




  //  ---------------------------------------------------------------------------
  //  types
  //  ---------------------------------------------------------------------------

  typedef struct
  {
    unsigned Ref1             : 1 ; // calculate for referencing against hard stop
    unsigned Ref2             : 1 ; // calculate for last referencing steps to leave hard stop
    unsigned Stop             : 1 ; // calculate for immediately stop (ignore other conditions)
    unsigned Reserved         : 5 ;
  }
  tCddStpDyn_tCalcModeBit;

  typedef union
  {
    uint8                   ucData;
    tCddStpDyn_tCalcModeBit Bit;
  }
  tCddStpDyn_CalcMode;


  //  ---------------------------------------------------------------------------
  //  constants
  //  ---------------------------------------------------------------------------



  //  ---------------------------------------------------------------------------
  //  prototypes
  //  ---------------------------------------------------------------------------

  void CddStpDyn_CodingDataValid(void);

  void    CddStpDyn_Init         (uint8 ucIx, boolean boHsMode);
  boolean CddStpDyn_SetFreq      (uint8 ucIx, uint16 unTmin,   uint16 unVolt);
  void    CddStpDyn_CalcNextSteps(uint8 ucIx, tHsInfo* pHsBuf, uint32 ulBufIx, sint32 lTgtPos, sint32 lActPos, uint32 ulRemainingTicks, tCddStpDyn_CalcMode CalcMode);

#endif // __CDDSTPDYN_H__

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
  /// \file  CddStp88XX_FctTables.h
  ///
  ///  \brief  Definitions for CddStp88XX functions and function tables
  ///
  ///  \descr  Function tables for Blackboard messages, ErrLog, ...
  ///
  /// \author Wuesteney, Ulrich ALRT/EEG4 * (wu82rt)
  ///         J. Kling ALRT-EES6 (f84304b)
  //-----------------------------------------------------------------------------

#ifndef __CDDSTP88XX_FCTTABLES_H__
#define __CDDSTP88XX_FCTTABLES_H__

  // jk-obsolet #include <Alx1_div/Alx1_Hal_Dxx_Util/Util_Lit_Types.h>

  #include <88XX/_CddStp88XX.h>
  #include <8899/CddStp8899Types.h>
  #include <8899/CddStp8899Cfg.h>
  #include <88XX/CddStp88XXTemp.h>


  // ---------------------------------------------------------------------------
  // CddStp88XX Attributes
  typedef struct
  {
    uint8   biUsePsens             : 1;     // use position sensor
    uint8   biUsePsensDiag         : 1;     // use position sensor diagnosis
    uint8   ucDummyBits            : 6;
  }
  tCddStp88XX_Attr;

  #define tCddStp_Attr tCddStp88XX_Attr
  

#ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
  extern const tCddStp88XX_Attr CddStp88XX_aAttr[];
#else // Unit-Tests!
  extern tCddStp88XX_Attr CddStp88XX_aAttr[];
#endif // UNIT_TEST


  // jk: 'tCddStp88XX_Attr'/'tCddStp_Attr' is ONLY about 'PSenes'
  INLINE CONST_AL tCddStp_Attr* CddStp88XX_GetAttr(const uint8 ucIx) 
  {
    // jk: 'tCddStp88XX_Attr'/'tCddStp_Attr' is ONLY about 'PSenes'
    return (const tCddStp_Attr*)(const void*)(&CddStp88XX_aAttr[ucIx]); 
  }


  extern uint8 CddStp88XX_aucCurAmpltRunTemp[] [CddStp_eTempState_TempIx];
  extern uint8 CddStp88XX_aucCurAmpltHoldTemp[][CddStp_eTempState_TempIx];
  extern uint8 CddStp88XX_aucCurAmpltRefTemp[] [CddStp_eTempState_TempIx];


#endif // __CDDSTP88XX_FCTTABLES_H__

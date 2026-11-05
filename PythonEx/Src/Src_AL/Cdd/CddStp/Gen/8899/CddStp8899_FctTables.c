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
/// \file  Cdd8899_FctTables.c
///
/// \brief  Constants for CddStp8899 functions and function tables
///
/// \descr  Function tables for stepper motor currents, ...
///
///         Additional information can be found in the design description (Link:
///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
///
/// \author Wuesteney, Ulrich ALRT/EEG4 * (wu82rt)
///         J. Kling ALRT-EES6 (f84304b)
//-----------------------------------------------------------------------------


// ---------------------------------------------------------------------------
// includes
// ---------------------------------------------------------------------------
#include <Std_Types.h>
#include <AL_Helper.h> //-- STATIC_AL

#ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
#else // Unit-Tests!
  #define CFA_CNT_STP_88XX   (4u)
  STATIC_AL uint8 CddStp8899_FctTables_UT_Dummy(uint8 uc) { return uc+1; }
#endif

#include <CddStpCfg.h>      // incl. nothing
#include <88XX/CddStp88XX.h>
#include <88XX/CddStp88XX_FctTables.h>


// prqa ....
// braced macros: against MISRA warning - QAC(Prio2) Msg: 3457(Macro defines a braced initializer.) Depth: 0 Ref: 

// temperature dependent hold current values (HoldCurrent = Ihold)
//                    ! Do not change order NT, LT, HT: index is given by tCddStpTempState!
// ====================================================================================================================
// use column order:    normal temp (NT),                low temp (LT),                   high temp (HT)
// ====================================================================================================================
#define _arrayCUH0 { CDDSTP8899_CurAmpltHold_NTVer,   CDDSTP8899_CurAmpltHold_LTVer,   CDDSTP8899_CurAmpltHold_HTVer }

#define _arrayCUH1 { CDDSTP8899_CurAmpltHold_NTHor,   CDDSTP8899_CurAmpltHold_LTHor,   CDDSTP8899_CurAmpltHold_HTHor }

#define _arrayCUH2 { CDDSTP8899_CurAmpltHold_NTSht,   CDDSTP8899_CurAmpltHold_LTSht,   CDDSTP8899_CurAmpltHold_HTSht }


// temperature dependent movement current values (NormalCurrent = Irun)
//                    ! Do not change order us, HS and NT, LT, HT: index is given by tCddStpTempState!
// ====================================================================================================================
// use line order:      us (micro steps), 
//                      HS (comment out not used mode HS for compensated half steps or HSNC for not compensated half steps) 
// in the column order: normal temp (NT),                low temp (LT),                   high temp (HT)
// ====================================================================================================================
#define _arrayCUN0 { CDDSTP8899_CurAmpltRunMS_NTVer, CDDSTP8899_CurAmpltRunMS_LTVer, CDDSTP8899_CurAmpltRunMS_HTVer } // us as default
                
#define _arrayCUN1 { CDDSTP8899_CurAmpltRunMS_NTHor, CDDSTP8899_CurAmpltRunMS_LTHor, CDDSTP8899_CurAmpltRunMS_HTHor } // us as default

#define _arrayCUN2 { CDDSTP8899_CurAmpltRunMS_NTSht, CDDSTP8899_CurAmpltRunMS_LTSht, CDDSTP8899_CurAmpltRunMS_HTSht } // us as default


// temperature dependent reference current values (RefCurrent = Iref)
//                    ! Do not change order NT, LT, HT: index is given by tCddStpTempState!
// ====================================================================================================================
// use column order:    normal temp (NT),                low temp (LT),                   high temp (HT)
// ====================================================================================================================
#define _arrayCUR0 { CDDSTP8899_CurAmpltRef_NTVer,   CDDSTP8899_CurAmpltRef_LTVer,   CDDSTP8899_CurAmpltRef_HTVer }

#define _arrayCUR1 { CDDSTP8899_CurAmpltRef_NTHor,   CDDSTP8899_CurAmpltRef_LTHor,   CDDSTP8899_CurAmpltRef_HTHor }

#define _arrayCUR2 { CDDSTP8899_CurAmpltRef_NTSht,   CDDSTP8899_CurAmpltRef_LTSht,   CDDSTP8899_CurAmpltRef_HTSht }


#if(  CFA_CNT_STP_88XX == 1)
//#error number of stepper: 1
#elif(CFA_CNT_STP_88XX == 2)
#error number of stepper: 2
#elif(CFA_CNT_STP_88XX == 3)
#error number of stepper: 3
#elif(CFA_CNT_STP_88XX == 4)
// ok
#elif(CFA_CNT_STP_88XX == 5)
#error number of stepper: 5
#else
  #error Unsupported number of stepper
#endif

uint8 CddStp88XX_aucCurAmpltHoldTemp[][CddStp_eTempState_TempIx] = 
{
  _arrayCUH0
// jk-tbd #if(CFA_CNT_STP_88XX == 1)
// jk-tbd  ,_arrayCUH1
// jk-tbd #endif
// jk-tbd #if(CFA_CNT_STP_88XX == 2)
// jk-tbd  ,_arrayCUH2
#if(CFA_CNT_STP_88XX == 4u)
  ,_arrayCUH0,_arrayCUH0,_arrayCUH0
#else
//  #error Unsupported number of stepper
#endif
};
uint8 CddStp88XX_aucCurAmpltRunTemp[] [CddStp_eTempState_TempIx] = 
{
  _arrayCUN0
// jk-tbd #if(CFA_CNT_STP_88XX == 1)
// jk-tbd  ,_arrayCUN1
// jk-tbd #endif
// jk-tbd #if(CFA_CNT_STP_88XX == 2)
// jk-tbd  ,_arrayCUN2
#if(CFA_CNT_STP_88XX == 4)
  ,_arrayCUN0,_arrayCUN0,_arrayCUN0
#else
//  #error Unsupported number of stepper
#endif
};
uint8 CddStp88XX_aucCurAmpltRefTemp[] [CddStp_eTempState_TempIx] = 
{
  _arrayCUR0
// jk-tbd #if(CFA_CNT_STP_88XX == 1)
// jk-tbd  ,_arrayCUR1
// jk-tbd #endif
// jk-tbd #if(CFA_CNT_STP_88XX == 2)
// jk-tbd  ,_arrayCUR2
#if(CFA_CNT_STP_88XX == 4)
  ,_arrayCUR0,_arrayCUR0,_arrayCUR0
#else
//  #error Unsupported number of stepper
#endif
};


// mapping of stepper attributes
// ====================================================================================================================
//            attributes according to CFG file
// ====================================================================================================================
/*
#define   _CDDSTP8899_Ver0_UsePsens_ ((CFG_LNK_PSENSVER0 == CFG_LnkDrv_PsensNone) ? 0 : 1)
#define   _CDDSTP8899_Hor0_UsePsens_ ((CFG_LNK_PSENSHOR0 == CFG_LnkDrv_PsensNone) ? 0 : 1)
//#define _CDDSTP8899_Sht0_UsePsens_ ((CFG_LNK_PSENSSHT0 == CFG_LnkDrv_PsensNone) ? 0 : 1)

#define   _CDDSTP_Ver0_UsePsensDiag_ ((_CDDSTP8899_Ver0_UsePsens_ && (CFG_OPT_STP & CFG_Stp_PsensDiag)) ? 1 : 0)
#define   _CDDSTP_Hor0_UsePsensDiag_ ((_CDDSTP8899_Hor0_UsePsens_ && (CFG_OPT_STP & CFG_Stp_PsensDiag)) ? 1 : 0)
//#define _CDDSTP_Sht0_UsePsensDiag_ ((_CDDSTP8899_Sht0_UsePsens_ && (CFG_OPT_STP & CFG_Stp_PsensDiag)) ? 1 : 0)

#define   _ATT0 {_CDDSTP8899_Ver0_UsePsens_, _CDDSTP_Ver0_UsePsensDiag_, 0} // Ver0
#define   _ATT1 {_CDDSTP8899_Hor0_UsePsens_, _CDDSTP_Hor0_UsePsensDiag_, 0} // Hor0
//#define _ATT2 {_CDDSTP8899_Sht0_UsePsens_, _CDDSTP_Sht0_UsePsensDiag_, 0} // Sht0
*/

#define   _arrayATT0 {0, 0, 0} // Ver0
#if(CFA_CNT_STPVER0_ONBRD == 2)
  #define   _arrayATT1 {0, 0, 0} // Ver1
#else
  #define   _arrayATT1 {1, 0, 0} // Hor0
#endif
//#define _arrayATT2 {1, 0, 0} // Sht0

// jk: 'tCddStp88XX_Attr' is ONLY about 'PSenes'
// jk-orig: const tCddStp88XX_Attr     CddStp88XX_aAttr[] = { _ATT0, _ATT1/*, _ATT2*/ };
#ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
  const tCddStp88XX_Attr CddStp88XX_aAttr[] = { _arrayATT0, _arrayATT0, _arrayATT0, _arrayATT0 };
#else // Unit-Tests!
  tCddStp88XX_Attr CddStp88XX_aAttr[] = { _arrayATT0, _arrayATT0, _arrayATT0, _arrayATT0 };
#endif // UNIT_TEST

//EOF

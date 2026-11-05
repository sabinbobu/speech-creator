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
  /// \file  CddStpData.h
  ///
  /// \brief  Project specific access to stepper coding parameters (read only)
  ///
  /// \descr  The stepper coding parameters are read from NvM blocks System, Lwr and Ahl
  ///
  ///         Additional information can be found in the design description (Link:
  ///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
  ///
  /// \author Ulrich Wuesteney  (wu82rt)
  ///         mailTo:Ulrich.Wuesteney@al-lighting.com
  ///         J. Kling ALRT-EES6 (f84304b)
  ///
  //-----------------------------------------------------------------------------

#ifndef __CDD_STP_DATA_H__
  #define __CDD_STP_DATA_H__


//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------


/*******************************************************************************
* types
*******************************************************************************/
typedef enum
{
  NvmPara_eSchrittMod2 = 0,   // 1/2  step (half step)
  NvmPara_eSchrittMod4 = 1,   // 1/4  step (reserved)
  NvmPara_eSchrittMod8 = 2,   // 1/8  step (micro step)
  NvmPara_eSchrittMod16 = 3    // 1/16 step (reserved)
}
tNvmPara_Lwr_SchrittMod;

//-----------------------------------------------------------------------------
// proptotypes
//-----------------------------------------------------------------------------
boolean CddStp_ReadCodingData(void);
boolean CddStp_ParaFct0(tParaFct0_Cmd eCmd,tNvmPara_CodingArea* pData);
void CddStp_MapParams(void);
void CddStp_SetOLIgnore(boolean boIgnore);

// System for CddStp88XX.c
#endif // __CDD_STP_DATA_H__
uint8  Cod_StpSpgDebOn                    (void);
uint8  Cod_StpSpgDebOff                   (void);
uint8  Cod_StpSpannungLo3                 (void);
uint8  Cod_StpSpannungLo2                 (void);
uint8  Cod_StpSpannungLo1                 (void);
uint8  Cod_StpSpannungHi1                 (void);
uint8  Cod_StpSpannungHi2                 (void);
uint8  Cod_StpSpannungRed                 (void);
uint8  Cod_StpZeitTT                      (void);
uint8  Cod_StpZeitHT                      (void);
uint8  Cod_StpWertTT                      (void);
uint8  Cod_StpQuelleTT                    (void);
//



// Lwr for CddStp88XX.c

boolean       Cod_LwrEnableStp            (void);
uint8         Cod_LwrSchrittMod           (void);
uint8         Cod_LwrOlFehlerzaehler      (void);
//boolean     Cod_LwrTestDlAktiv          (void);
boolean       Cod_LwrTestKeinFehlereintrag(void);
boolean       Cod_LwrTestOlIgnor          (void);
//uint16      Cod_LwrTestDlWeg            (void);
//uint8       Cod_LwrTestDlPeriode        (void);
//uint8       Cod_LwrHsWertStart          (void);
//boolean     Cod_LwrVorwarnAnhalten      (void);
//boolean     Cod_LwrTestPsDefIgnor       (void);
boolean       Cod_LwrVorwarnNeuref        (void);
uint8         Cod_LwrVorwarnQuelle        (void);
//boolean     Cod_LwrAbsenkAhlFehVps      (void);
//boolean     Cod_LwrAbsenkAhlFehRef      (void);
//boolean     Cod_LwrAbsenkAhlFehPos      (void);
//boolean     Cod_LwrAbsenkAhlFehTe       (void);
//uint8       Cod_LwrAutorefVersatz       (void);
//uint8       Cod_LwrAbsenkOffset         (void);

uint8         Cod_LwrHaltTT               (void);
uint8         Cod_LwrHaltNT               (void);
uint8         Cod_LwrHaltHT               (void);
uint8         Cod_LwrFahrTT               (void);
uint8         Cod_LwrFahrNT               (void);
uint8         Cod_LwrFahrHT               (void);
uint8         Cod_LwrRef3TT               (void);
uint8         Cod_LwrRef3NT               (void);
uint8         Cod_LwrRef3HT               (void);

uint16        Cod_LwrVmin                 (void);
uint16        Cod_LwrVmax                 (void);
uint16        Cod_LwrAcc                  (void);
boolean       Cod_LwrBremsSchnell         (void);
uint8         Cod_LwrHsZeitUmkehr         (void);
uint8         Cod_LwrVorbestZeit          (void);
uint8         Cod_LwrNachbestZeit         (void);
uint16        Cod_LwrResHsZeitU1          (void);
uint16        Cod_LwrResHsZeitO1          (void);
uint16        Cod_LwrResHsZeitU2          (void);
uint16        Cod_LwrResHsZeitO2          (void);
//
uint16        Cod_LwrHsZeitSp             (void);
uint16        Cod_LwrHsZeitAp             (void);
uint16        Cod_LwrHsZeitRef1           (void);
uint16        Cod_LwrHsZeitRef2           (void);
uint16        Cod_LwrHsZeitRef3           (void);
uint16        Cod_LwrHsAnzahlRef2         (void);

//
//
boolean       Cod_LwrRichtungLi           (void);
//
//

//
//
boolean       Cod_LwrRichtungRe           (void);

#ifndef __NV_M_PARA_LWR_H__
#define __NV_M_PARA_LWR_H__

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
/// \file  NvM_Para_Lwr.h
///
/// \brief  Generic NvM LWR parameter structure definitions
///
/// \descr  
///
///         Additional information can be found in the design description (Link:
///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
///
/// \author Wuesteney, Ulrich ALRT/EEG4 * (wu82rt)
//-----------------------------------------------------------------------------

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/

#include <Bsw/Nvm/NvM_Para_LwrInit.h>


/*******************************************************************************
* Version
*******************************************************************************/


/*******************************************************************************
* Defintions
*******************************************************************************/
#define NVM_PARA_SIZE_LWR          84


/*******************************************************************************
* types
*******************************************************************************/
typedef enum 
{
  NvmPara_eSchrittMod2  = 0,   // 1/2  step (half step)
  NvmPara_eSchrittMod4  = 1,   // 1/4  step (reserved)
  NvmPara_eSchrittMod8  = 2,   // 1/8  step (micro step)
  NvmPara_eSchrittMod16 = 3    // 1/16 step (reserved)
}
tNvmPara_Lwr_SchrittMod;


typedef struct
{
  uint8  biEnable                : 1;
  uint8  biReserviert            : 1;
  uint8  eSchrittMod             : 2;
  uint8  u4OlFehlerzaehler       : 4;

  uint8  biTestDlAktiv           : 1;
  uint8  biTestKeinFehlereintrag : 1;
  uint8  biTestOlIgnor           : 1;
  uint8  u5Reserviert            : 5;

  uint16 unTestDlWeg;
  uint8  ucTestDlPeriode;
  uint8  ucHsWertStart;

  uint8  biVorwarnAnhalten       : 1;
  uint8  biVorwarnNeuref         : 1;
  uint8  eVorwarnQuelle          : 2;
  uint8  biAbsenkAhlFehVps       : 1;
  uint8  biAbsenkAhlFehRef       : 1;
  uint8  biAbsenkAhlFehPos       : 1;
  uint8  biAbsenkAhlFehTe        : 1;

  uint8  ucAutorefVersatz;
  uint8  ucAbsenkOffset;
  uint8  aucReserviert[3];
}
tNvmPara_Lwr_Modus;


typedef struct
{
  uint8  ucHaltTT;
  uint8  ucHaltNT;
  uint8  ucHaltHT;
  uint8  ucFahrTT;
  uint8  ucFahrNT;
  uint8  ucFahrHT;
  uint8  ucRef3TT;
  uint8  ucRef3NT;
  uint8  ucRef3HT;
  uint8  ucReserviert;
}
tNvmPara_Strom;


typedef struct
{
  uint16 unVmin;       
  uint16 unVmax;       
  uint16 unAcc;        
  uint8  biBremsSchnell        : 1;
  uint8  u7HsZeitUmkehr        : 7;
  uint8  u4VorbestZeit         : 4;
  uint8  u4NachbestZeit        : 4;
  uint16 unResHsZeitU1;
  uint16 unResHsZeitO1;
  uint16 unResHsZeitU2;
  uint16 unResHsZeitO2;
  uint16 unHsZeitMinTieftemp;
  uint16 unHsZeitSp;
  uint16 unHsZeitAp;
  uint16 unHsZeitRef1;
  uint16 unHsZeitRef2;
  uint16 unHsZeitRef3;
  uint16 unHsAnzahlRef2;
}
tNvmPara_Dynamik;


typedef struct
{
  uint16  unAnschlagMi;
  uint16  unAnschlagPl;
  uint16  unMaxWinkelMi;
  uint16  unMaxWinkelPl;
  uint8   u7PsensPosWert         : 7;
  uint8   biPsensPosVz           : 1;
  uint8   u7ApWert               : 7;
  uint8   biApVz                 : 1;
  uint8   u7SpWert               : 7;
  uint8   biSpVz                 : 1;
  uint8   ucHsGradNenner;
  uint16  unHsGradZaehler;
  uint8   biRichtung             : 1;
  uint8   biPsensPol             : 1;  // used for AHL only
  uint8   biRegelflanke          : 1;  // used for AHL only
  uint8   biRefMi                : 1;
  uint8   biRefPl                : 1;
  uint8   u3Reserviert           : 3;
  uint8   ucReserviert;
}
tNvmPara_SwGeo;


typedef struct
{
  tNvmPara_Lwr_Modus          Modus;      //  12 bytes
  tNvmPara_Strom              Strom;      //  10 bytes
  tNvmPara_Dynamik            Dynamik;    //  30 bytes
  tNvmPara_SwGeo              SwGeoLi;    //  16 bytes
  tNvmPara_SwGeo              SwGeoRe;    //  16 bytes
}                                         // ---------
tNvmPara_LwrBlock;                        //  84 bytes


#endif // __NV_M_PARA_LWR_H__

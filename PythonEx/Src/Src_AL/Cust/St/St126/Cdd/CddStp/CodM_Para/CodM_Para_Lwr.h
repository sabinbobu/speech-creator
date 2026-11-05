#ifndef  __CODM_PARA__LWR_H
#define  __CODM_PARA__LWR_H

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/

#include <Std_Types.h> // jk-tbd 

/*******************************************************************************
* Version
*******************************************************************************/


/*******************************************************************************
* Defintions
*******************************************************************************/
#define NVM_PARA_SIZE_LWR          100


/*******************************************************************************
* types
*******************************************************************************/
// jk-obsolet typedef enum 
// jk-obsolet {
// jk-obsolet   NvmPara_eSchrittMod2  = 0,   // 1/2  step (half step)
// jk-obsolet   NvmPara_eSchrittMod4  = 1,   // 1/4  step (reserved)
// jk-obsolet   NvmPara_eSchrittMod8  = 2,   // 1/8  step (micro step)
// jk-obsolet   NvmPara_eSchrittMod16 = 3    // 1/16 step (reserved)
// jk-obsolet }
// jk-obsolet tNvmPara_Lwr_SchrittMod;


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

#define NVM_PARA_LWR_MODUS_INIT                           \
{                                                         \
  1,                        /* biEnable                */ \
  0,                        /* biReserviert            */ \
  NvmPara_eSchrittMod8,     /* eSchrittMod             */ \
  1,                        /* u4OlFehlerzaehler       */ \
  0,                        /* biTestDlAktiv           */ \
  0,                        /* biTestKeinFehlereintrag */ \
  0,                        /* biTestOlIgnor           */ \
  0,                        /* u5Reserviert            */ \
  200,                      /* unTestDlWeg             */ \
  20,                       /* ucTestDlPeriode         */ \
  0,                        /* ucHsWertStart           */ \
  0,                        /* biVorwarnAnhalten       */ \
  0,                        /* biVorwarnNeuref         */ \
  0,                        /* eVorwarnQuelle          */ \
  0,                        /* biAbsenkAhlFehVps       */ \
  0,                        /* biAbsenkAhlFehRef       */ \
  0,                        /* biAbsenkAhlFehPos       */ \
  0,                        /* biAbsenkAhlFehTe        */ \
  30,                       /* ucAutorefVersatz        */ \
  0,                        /* ucAbsenkOffset          */ \
  {0, 0, 0}                 /* aucReserviert           */ \
}


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

#define NVM_PARA_LWR_STROM_INIT                 \
{                                               \
  10,                        /* ucHaltTT     */ \
  6,                         /* ucHaltNT     */ \
  6,                         /* ucHaltHT     */ \
  67,                        /* ucFahrTT     */ \
  57,                        /* ucFahrNT     */ \
  48,                        /* ucFahrHT     */ \
  67,                        /* ucRef3TT     */ \
  57,                        /* ucRef3NT     */ \
  48,                        /* ucRef3HT     */ \
  0                          /* ucReserviert */ \
}


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

#define NVM_PARA_LWR_DYNAMIK_INIT              \
{                                              \
  100,               /* unVmin              */ \
  800,               /* unVmax              */ \
  12000,             /* unAcc               */ \
  0,                 /* biBremsSchnell      */ \
  16,                /* u7HsZeitUmkehr      */ \
  6,                 /* u4VorbestZeit       */ \
  5,                 /* u4NachbestZeit      */ \
  0,                 /* unResHsZeitU1       */ \
  0,                 /* unResHsZeitO1       */ \
  0,                 /* unResHsZeitU2       */ \
  0,                 /* unResHsZeitO2       */ \
  1000,              /* unHsZeitMinTieftemp */ \
  8503,              /* unHsZeitSp          */ \
  8503,              /* unHsZeitAp          */ \
  2208,              /* unHsZeitRef1        */ \
  10000,             /* unHsZeitRef2        */ \
  10000,             /* unHsZeitRef3        */ \
  16                 /* unHsAnzahlRef2      */ \
}


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

#define NVM_PARA_LWR_SW_GEO_INIT       \
{                                      \
  320,          /* unAnschlagMi     */ \
  220,          /* unAnschlagPl     */ \
  300,          /* unMaxWinkelMi    */ \
  200,          /* unMaxWinkelPl    */ \
  0,            /* u7PsensPosWert   */ \
  0,            /* biPsensPosVz     */ \
  14,           /* u7ApWert         */ \
  1,            /* biApVz           */ \
  14,           /* u7SpWert         */ \
  1,            /* biSpVz           */ \
  169,          /* ucHsGradNenner   */ \
  140,          /* unHsGradZaehler  */ \
  0,            /* biRichtung       */ \
  0,            /* biPsensPol       */ \
  0,            /* biRegelflanke    */ \
  0,            /* biRefMi          */ \
  0,            /* biRefPl          */ \
  0,            /* u3Reserviert     */ \
  0             /* ucReserviert     */ \
}

typedef struct
{
  uint8 areserviert1[16];
}
tNvmPara_LWR_Reserviert;


typedef struct
{
  tNvmPara_Lwr_Modus          Modus;      //  12 bytes
  tNvmPara_Strom              Strom;      //  10 bytes
  tNvmPara_Dynamik            Dynamik;    //  30 bytes
  tNvmPara_SwGeo              SwGeoLi;    //  16 bytes
  tNvmPara_SwGeo              SwGeoRe;    //  16 bytes
  tNvmPara_LWR_Reserviert     Reserviert; //  16 bytes
}                                         // ---------
tNvmPara_LwrBlock;                        //  100 bytes

#define NVM_PARA_LWRBLOCK_INIT \
{                              \
  NVM_PARA_LWR_MODUS_INIT,     \
  NVM_PARA_LWR_STROM_INIT,     \
  NVM_PARA_LWR_DYNAMIK_INIT,   \
  NVM_PARA_LWR_SW_GEO_INIT,    \
  NVM_PARA_LWR_SW_GEO_INIT,    \
}


#endif /*  __CODM_PARA__LWR_H */


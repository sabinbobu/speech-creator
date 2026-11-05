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
/// \file  CddStp_Data.c
///
/// \brief Access for CddStp to coding data
///
/// \author U. Wuesteney
///
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <Std_Types.h>
#include <AL_Helper.h> //-- STATIC_AL
#include <RteCommonTypes.h>
//#include <IntegrationTest.h>

//#include <Rte_ctacCddStp.h>

#ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
  #include <CddStpData.h>
  #include <Rte.h>
  #include <CodM_Para_System.h>
  #include <CodM_Para_AvacStp.h>
#else // Unit-Tests!
  //#define CFA_CNT_STP_88XX 4

  extern uint8 CddStpDyn_UnitTest___tCodingAreaLwr_Modus_eSchrittMod;
#endif



//-----------------------------------------------------------------------------
// variables
//-----------------------------------------------------------------------------
STATIC_AL tNvmPara_SystemBlock  CddStp_tCodingAreaSys;     // system part of NvmPara_CodingArea
STATIC_AL boolean CddStpData_boIgnoreOL;     // system part of NvmPara_CodingArea
STATIC_AL tNvmPara_AvacStpBlock CddStp_tCodingAreaLwr = NVMPARA_AVACSTPBLOCK_INIT;     // LWR    part of NvmPara_CodingArea


//-----------------------------------------------------------------------------
// interface functions
//-----------------------------------------------------------------------------

// System for CddStp88XX.c

uint8      Cod_StpSpgDebOn(void) { return 30; }// CddStp_tCodingAreaSys.STP_SPANNUNG_DEBOUNCE_ON;  /* e.g.  '30' */ }  // [0,01 s]    Einschalt Verzogerungszeit nach Spannungs bedingtem Anhalten oder Abschalten
uint8      Cod_StpSpgDebOff(void) { return 1; }// CddStp_tCodingAreaSys.STP_SPANNUNG_DEBOUNCE_OFF; /* e.g.   '1' */ }  // [0,01 s]    Ausschalt Verzogerungszeit  fur Spannungs bedingtes Anhalten oder Abschalten
uint8      Cod_StpSpannungLo3 (void) { return CddStp_tCodingAreaSys.Stepper.Stp_Voltage_Low3;          /* e.g.  '76' */ }  // [0.1 V]    Spannungsschwelle fuer die harte Abschaltung des Treibers bei Unterspannung
uint8      Cod_StpSpannungLo2 (void) { return CddStp_tCodingAreaSys.Stepper.Stp_Voltage_Low2;          /* e.g.  '86' */ }  // [0.1 V]    Spannungsschwelle fur das Anhalten des Motors bei Unterspannung (N.b.: KEIN Anhalten bei Ref-Run)
uint8      Cod_StpSpannungLo1 (void) { return CddStp_tCodingAreaSys.Stepper.Stp_Voltage_Low1;          /* e.g.  '96' */ }  // [0.1 V]    Spannungsschwelle fur die Reaktivierung des Motors nach Unterspannung
uint8      Cod_StpSpannungHi1 (void) { return CddStp_tCodingAreaSys.Stepper.Stp_Voltage_High1;          /* e.g. '187' */ }  // [0.1 V]    Spannungsschwelle fur die Reaktivierung des Motors nach Ueberspannung
uint8      Cod_StpSpannungHi2 (void) { return CddStp_tCodingAreaSys.Stepper.Stp_Voltage_High2;          /* e.g. '197' */ }  // [0.1 V]    Spannungsschwelle fur das Anhalten des Motors bei Ueberspannung
uint8      Cod_StpSpannungRed (void) { return CddStp_tCodingAreaSys.Stepper.Stp_Voltage_High_Reduce;          /* e.g. '110' */ }  // [0.1 V]    Spannung, unter der die maximale Verstellfrequenz reduziert wird. Die Reduktion der maximalen Verstellfrequenz erfolgt annaehernd linear zur Versorgungsspannung.
uint8      Cod_StpZeitTT      (void) { return CddStp_tCodingAreaSys.Stepper.Stp_DurationLowTempMode;               /* e.g.  '60' */ }  // [s]        Dauer des Tieftemperaturmodus, unabhaengig davon, ob die Tieftemperaturinformation nach Ende des Zeitintervalls noch anliegt. Der Tieftemperaturzustand kann nur einmal pro Power-On-Zyklus aktiviert werden.
uint8      Cod_StpZeitHT      (void) { return CddStp_tCodingAreaSys.Stepper.Stp_DurationHighTempMode;               /* e.g.  '60' */ }  // [s]        Minimale Dauer des Hochtemperaturmodus. Der Hochtemperaturmodus wird jedes Mal aktiviert, wenn vom Schrittmotortreiber eine Uebertemperaturwarnung erfolgt und verbleibt fur mindestens STP_ZEIT_HT in diesem Zustand.
uint8      Cod_StpWertTT      (void) { return CddStp_tCodingAreaSys.Stepper.Stp_LowTempModeThreshold;               /* e.g.  '30' */ }  // [Deg + 40] Temperaturgrenzwert, unter dem der Tieftemperaturmodus aktiviert wird
uint8      Cod_StpQuelleTT    (void) { return CddStp_tCodingAreaSys.Stepper.Stp_Source_LowTemp;             /* e.g.  '16' */ }  //            Source of temp.: 1..12=NTC1-12, 16=PCB, 17=CAN - SWRS.27423     -----    < 0 = Temperaturmessung durch Sensor im FLE

//
// Hi2   - e.g. '19,7V'                                          /=====================\                                                     |
// Hi1   - e.g. '18,7V'                                     /===/  |                    \==================\                                 |
// Norm  - e.g. '13,5V' ====\                          /===/  |    |-> Hi2: stop moving   |                 \=========                       |
// Lo1   - e.g. ' 9,6V'      \===\                /===/  |    |-> Hi1: -                  |-> Hi1: Restart    |                              |
// Lo2   - e.g. ' 8,6V'        |   \===\     /===/  |    |-> Norm: -                                          |-> Norm                       |
// Lo3   - e.g. ' 7,6V'        |     |  \===/  |    |-> Lo1: Restart
//                             |     |    |    |-> Lo2: -
//                             |     |    |-> Lo3: hard off
//                             |     |-> Lo2: stop moving - but do NOT stop Ref-Run
//                             |-> Lo1: -
//

// Lwr for CddStp88XX.c

#define TR_EL_FA  ? TRUE : FALSE // easy MISRA-Reading

// Modus ('tNvmPara_Lwr_Modus')
boolean    Cod_LwrEnableStp            (void)     { return (CddStp_tCodingAreaLwr.Modus.ucAvacStp_Enable != 0u) TR_EL_FA;                /* e.g. '1' */  }
uint8      Cod_LwrSchrittMod           (void)     { return  CddStp_tCodingAreaLwr.Modus.ucAvacStp_Step_mode;                             /* e.g. '2' */  }
uint8      Cod_LwrOlFehlerzaehler      (void)     { return  CddStp_tCodingAreaLwr.Modus.ucAvacStp_OL_Errorcount_Threshold;                       /* e.g. '1' */  }
boolean    Cod_LwrTestKeinFehlereintrag(void)     { return (CddStp_tCodingAreaLwr.Modus.ucAvacStp_Test_NoError != 0u) TR_EL_FA; /* e.g. '0' */  }
boolean    Cod_LwrTestOlIgnor          (void)     { return (CddStp_tCodingAreaLwr.Modus.ucAvacStp_Test_IgnoreOL != 0u) TR_EL_FA;           /* e.g. '0' */  }
boolean    Cod_LwrVorwarnNeuref        (void)     { return (CddStp_tCodingAreaLwr.Modus.ucAvacStp_NewRef_ForWarning != 0u) TR_EL_FA;         /* e.g. '0' */  }

// Strom ('tNvmPara_Strom')
uint8      Cod_LwrHaltTT               (void)     { return CddStp_tCodingAreaLwr.Strom.ucAvacStp_Hold_Current_LT;  /* e.g. '11' */  }
uint8      Cod_LwrHaltNT               (void)     { return CddStp_tCodingAreaLwr.Strom.ucAvacStp_Hold_Current_NT;  /* e.g. '11' */  }
uint8      Cod_LwrHaltHT               (void)     { return CddStp_tCodingAreaLwr.Strom.ucAvacStp_Hold_Current_HT;  /* e.g. '11' */  }
uint8      Cod_LwrFahrTT               (void)     { return CddStp_tCodingAreaLwr.Strom.ucAvacStp_Run_Current_LT;  /* e.g.  '56' */  }
uint8      Cod_LwrFahrNT               (void)     { return CddStp_tCodingAreaLwr.Strom.ucAvacStp_Run_Current_NT;  /* e.g.  '56' */  }
uint8      Cod_LwrFahrHT               (void)     { return CddStp_tCodingAreaLwr.Strom.ucAvacStp_Run_Current_HT;  /* e.g.  '56' */  }
uint8      Cod_LwrRef3TT               (void)     { return CddStp_tCodingAreaLwr.Strom.ucAvacStp_Ref_Current_LT;  /* e.g.  '56' */  }
uint8      Cod_LwrRef3NT               (void)     { return CddStp_tCodingAreaLwr.Strom.ucAvacStp_Ref_Current_NT;  /* e.g.  '56' */  }
uint8      Cod_LwrRef3HT               (void)     { return CddStp_tCodingAreaLwr.Strom.ucAvacStp_Ref_Current_HT;  /* e.g.  '56' */  }

// Dynamik ('tNvmPara_Dynamik')
uint16     Cod_LwrVmin                 (void)     { return  CddStp_tCodingAreaLwr.Dynamik.unAvacStp_V_min;                          /* e.g. '100'   */  }
uint16     Cod_LwrVmax                 (void)     { return  CddStp_tCodingAreaLwr.Dynamik.unAvacStp_V_max;                          /* e.g. '800'   */  }
uint16     Cod_LwrAcc                  (void)     { return  CddStp_tCodingAreaLwr.Dynamik.unAvacStp_Acceleration;                           /* e.g. '12000' */  }
boolean    Cod_LwrBremsSchnell         (void)     { return (CddStp_tCodingAreaLwr.Dynamik.ucAvacStp_Fast_Deceleration != 0u) TR_EL_FA;  /* e.g. '0' */  }
uint8      Cod_LwrHsZeitUmkehr         (void)     { return  CddStp_tCodingAreaLwr.Dynamik.ucAvacStp_Reversing_Time;                  /* e.g. '16' */  }
uint8      Cod_LwrVorbestZeit          (void)     { return  CddStp_tCodingAreaLwr.Dynamik.ucAvacStp_PreStepTime;                   /* e.g. '3' */  }
uint8      Cod_LwrNachbestZeit         (void)     { return  CddStp_tCodingAreaLwr.Dynamik.ucAvacStp_PostStepTime;                  /* e.g. '3' */  }
uint16     Cod_LwrResHsZeitU1          (void)     { return  CddStp_tCodingAreaLwr.Dynamik.unAvacStp_Res_Hs_Time_U1;                   /* e.g. '0' */  }
uint16     Cod_LwrResHsZeitO1          (void)     { return  CddStp_tCodingAreaLwr.Dynamik.unAvacStp_Res_Hs_Time_O1;                   /* e.g. '0' */  }
uint16     Cod_LwrResHsZeitU2          (void)     { return  CddStp_tCodingAreaLwr.Dynamik.unAvacStp_Res_Hs_Time_U2;                   /* e.g. '0' */  }
uint16     Cod_LwrResHsZeitO2          (void)     { return  CddStp_tCodingAreaLwr.Dynamik.unAvacStp_Res_Hs_Time_O2;                   /* e.g. '0' */  }
uint16     Cod_LwrHsZeitRef1           (void)     { return  CddStp_tCodingAreaLwr.Dynamik.unAvacStp_HsPeriod_ref1;                    /* e.g. '0' */  }
uint16     Cod_LwrHsZeitRef2           (void)     { return  CddStp_tCodingAreaLwr.Dynamik.unAvacStp_HsPeriod_ref2;                    /* e.g. '0' */  }
uint16     Cod_LwrHsZeitRef3           (void)     { return  CddStp_tCodingAreaLwr.Dynamik.unAvacStp_HsPeriod_ref3;                    /* e.g. '0' */  }
uint16     Cod_LwrHsAnzahlRef2         (void)     { return  CddStp_tCodingAreaLwr.Dynamik.unAvacStp_HS_ref2;                  /* e.g. '0' */  }

// SwGeoLi ('tNvmPara_SwGeo')
boolean    Cod_LwrRichtungLi           (void)     { return (CddStp_tCodingAreaLwr.SwGeoLi.ucAvacStp_Direction_L != 0u) TR_EL_FA;      /* e.g. '' */  }

// SwGeoRe ('tNvmPara_SwGeo')
boolean    Cod_LwrRichtungRe           (void)     { return (CddStp_tCodingAreaLwr.SwGeoRe.ucAvacStp_Direction_R != 0u) TR_EL_FA;      /* e.g. '' */  }


//-----------------------------------------------------------------------------
/// \brief  CddStp_ReadCodingData
///
/// \descr
///
/// \param  -
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CddStp_ParaFct0(tParaFct0_Cmd eCmd,tNvmPara_CodingArea* pData)
{
  boolean         boRet = FALSE;
  boolean         boData = FALSE;
  uint8           ucData;

  switch (eCmd)
  {
  case eParaFct0_CodingDataValid:
  {
   boRet = TRUE;

   CddStp_tCodingAreaSys = pData->Sys;
   CddStp_tCodingAreaLwr = pData->AvacStp;
   CddStpData_boIgnoreOL = CddStp_tCodingAreaLwr.Modus.ucAvacStp_Test_IgnoreOL;
  }
  break;

  case eParaFct0_CodingDataInvalid:
  {
   boRet = FALSE;
  }
  break;

  default:
   break;
  }

  return boRet;

}

//-----------------------------------------------------------------------------
/// \brief  CddStp_SetOLIgnore
///
/// \descr Set OL ignore flag
///
/// \param  -
///
/// \return boolean
//-----------------------------------------------------------------------------
void CddStp_SetOLIgnore(boolean boIgnore) {
  CddStp_tCodingAreaLwr.Modus.ucAvacStp_Test_IgnoreOL = (boIgnore != FALSE) ? 1u : CddStpData_boIgnoreOL;
}


//-----------------------------------------------------------------------------
/// \brief  CddStp_MapParams
///
/// \descr  Mapps the coding parameter in order to acces the in CtrlStp
///
/// \param  [void]
///
/// \return [void]
//-----------------------------------------------------------------------------
void CddStp_MapParams(void)
{
 tsRteCodingParameters sCodingParameters;

 (void)Rte_Read_CodM_CddStp_Para(&sCodingParameters);

 (void)CddStp_ParaFct0(sCodingParameters.eCodingState, sCodingParameters.psCodingParameters_Blocks);

}

// EOF

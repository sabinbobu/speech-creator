#ifndef __NVM_PARA_SYSTEM_H__
#define __NVM_PARA_SYSTEM_H__

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
/// \file  NvM_Para_System.h
///
/// \brief  
///
/// \descr  System parameters:
///         - CAF Type
///         - Headlamp identification
///         - Handling of CCMs (also influences DTCs)
///         - Voltage range
///         - DiaFctTest Off and On time
///
///         Additional information can be found in the design description (Link:
///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
///
/// \author Schmid, Oliver ALRT/EEG-PM3 (sdo2rt)
///         mailTo:oliver.schmid@al-lighting.com       
//-----------------------------------------------------------------------------

#define NVM_PARA_SIZE_SYSTEM                          10u

typedef enum 
{
  NvmPara_Sys_eQuelleTt_FLE  = 0,  // TT-Erkennung ueber Sensor im FLE
  NvmPara_Sys_eQuelleTt_CAN  = 1,  // TT-Erkennung ueber CAN-Signal
  NvmPara_Sys_eQuelleTt_Res1 = 2,  // reserviert
  NvmPara_Sys_eQuelleTt_Res2 = 3   // reserviert
}
tNvmPara_Sys_QuelleTT;


typedef struct
{
  uint8  STP_SPANNUNG_LO3;     ///< [0.1 V] Spannungsschwelle fuer die harte Abschaltung des Treibers bei Unterspannung
  uint8  STP_SPANNUNG_LO2;     ///< [0.1 V] Spannungsschwelle für das Anhalten des Motors bei Unterspannung
  uint8  STP_SPANNUNG_LO1;     ///< [0.1 V] Spannungsschwelle für die Reaktivierung des Motors nach Unterspannung
  uint8  STP_SPANNUNG_HI1;     ///< [0.1 V] Spannungsschwelle für die Reaktivierung des Motors nach Ueberspannung
  uint8  STP_SPANNUNG_HI2;     ///< [0.1 V] Spannungsschwelle für das Anhalten des Motors bei Ueberspannung
  uint8  STP_SPANNUNG_RED;     ///< [0.1 V] Spannung, unter der die maximale Verstellfrequenz reduziert wird. Die Reduktion der maximalen Verstellfrequenz erfolgt annaehernd linear zur Versorgungsspannung.
  uint8  STP_ZEIT_TT;          ///< [s]     Dauer des Tieftemperaturmodus, unabhaengig davon, ob die Tieftemperaturinformation nach Ende des Zeitintervalls noch anliegt. Der Tieftemperaturzustand kann nur einmal pro Power-On-Zyklus aktiviert werden.
  uint8  STP_ZEIT_HT;          ///< [s]     Minimale Dauer des Hochtemperaturmodus. Der Hochtemperaturmodus wird jedes Mal aktiviert, wenn vom Schrittmotortreiber eine Uebertemperaturwarnung erfolgt und verbleibt für mindestens STP_ZEIT_HT in diesem Zustand.
  uint8  STP_WERT_TT;          ///< [Deg + 40] Temperaturgrenzwert, unter dem der Tieftemperaturmodus aktiviert wird
  uint8  STP_QUELLE_TT : 2;    ///< 0 = Temperaturmessung durch Sensor im FLE
                               ///< 1 = Auswertung CAN-Signal
                               ///< 2 = reserviert
                               ///< 3 = reserviert
  uint8  reserviert1   : 6;    ///< Reserviert
  uint16 reserviert2;          ///< Reserviert
}
tNvmPara_SystemBlock; /* 12 byte */

#endif // __NVM_PARA_SYSTEM_H__

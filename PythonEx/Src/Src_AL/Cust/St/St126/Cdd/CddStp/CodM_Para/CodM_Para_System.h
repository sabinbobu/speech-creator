#ifndef __CODM_PARA_SYSTEM_H__
#define __CODM_PARA_SYSTEM_H__

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
/// \file  CodM_Para_System.h
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

#include <Std_Types.h> // tbd!! 

#define NVM_PARA_SIZE_SYSTEM         38

/// CCM is never transmitted
#define NVM_PARA_SYS_CCM_DISABLED                     0u
/// CCM is transmitted if at least one used LED fails
#define NVM_PARA_SYS_CCM_SEND_IF_ANY_USED_FAILS       1u
/// CCM is transmitted if at least one mandatory LED fails (i.e. the bit ErrorImpact in LMM is 1)
#define NVM_PARA_SYS_CCM_SEND_IF_MANDATORY_FAILS      2u


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
  uint8 ucCarConfigValid; //0xAA = invalid ( 170 )
                          //0x55 = valid (85)
  uint8 ucVehicleType;                // OK
  uint8 ucSteeringWheelPosition;      // OK                Not used in Code
  uint8 ucModelYear;                  // not sent in CANOe currently not used in Code
  uint8 ucGearBoxType;                // OK
  uint8 ucHeadlightsVariant;          // OK
  uint8 ucHeadLampsSymmetry;          // not evaluated but sent
  uint16 unWheelBase;                 //OK
  uint8 ucSuspension;                 // CANOE OK, Code not evaluated

  uint8 biDeliveryModeBattery : 1;          // OK
  uint8 biDeliveryModeSuspension : 1;       // OK
  uint8 biDeliveryModeLocking : 1;          // OK
  uint8 biDeliveryFactoryModeActive : 1;    // OK
  uint8 biCorneringLightsFitted : 1;        // OK
  uint8 biExteriorLightsWakeUpSequence : 1; 
  uint8 biCornerLampFunction : 1;
  uint8 biSideMarkersFitted : 1;
  
  uint8 ucCornerOnThreshold;
  uint8 ucLaserHighBeam;
  uint8 ucAdaptDrvBeam;
  uint8 ucFntAnimatedIndicator;
  uint8 ucAutoSwitching;
  uint8 ucAfs123Fitted;
  uint8 ucHandOfDrive;
  uint8 ucHeightInputSelection;
  uint8 ucHdlampLvlSensPos;
  uint8 ucVariantId;
  uint8 biSblEnabled : 1;
  uint8 biADBInitialisation : 2;
#ifdef L663
  uint8 biFrontFogFuntionality : 3;
  uint8 biAhbSystemStatus : 2;
  uint8 ucSensorSlopeType; 
#else
  uint8 biReserved : 5;
#endif
  uint8 ucFrontCamera; 
  uint8 ucTouristMode;
  uint8 ucWakeupShutdownSeqTyp;
  uint8 ucManualHeadLampLeveling;
  uint8 auReserved2[5];
#if defined(D7U_AND_L663) || defined(MULTICAN)
  uint8 ucDynBendingLight;
  uint8 ucSignPostDimming;
  uint8 ucPixelTouristMode;
  uint8 auReserved[3];
#endif
}
tNvmPara_CarConfig;

typedef struct
{
uint8 ucVehicleType                   ; //02 = L560
                                        //12 = L494
                                        //13 = X512
                                        //200 - 203 = AL interne Varianten
uint8 ucHeadlightsVariant;              //

}
tNvmPara_System_VariantSelection;


#if defined(D7U) || defined(MULTICAN)
#define NVMPARA_SYSTEM_CARCONFIG_INIT                       \
{                                                           \
  170,              /* ucCarConfigValid*/                   \
  0,                /* ucVehicleType*/                      \
  0,                /* ucSteeringWheelPosition*/            \
  0,                /* ucModelYear */                       \
  0,                /* ucGearBoxType*/                      \
  0,                /* ucHeadlightsVariant*/                \
  0,                /* ucHeadLampsSymmetry*/                \
  0,                /* unWheelBase */                       \
  0,                /* ucSuspension*/                       \
  0,                /* biDeliveryModeBattery*/              \
  0,                /* biDeliveryModeSuspension*/           \
  0,                /* biDeliveryModeLocking*/              \
  0,                /* biDeliveryFactoryModeActive*/        \
  0,                /* biCorneringLightsFitted*/            \
  0,                /* biExteriorLightsWakeUpSequence*/     \
  0,                /* biCornerLampFunction*/               \
  0,                /* biSideMarkersFitted*/                \
  0,                /* ucCornerOnThreshold*/                \
  0,                /* ucLaserHighBeam*/                    \
  0,                /* ucAdaptDrvBeam*/                     \
  0,                /* ucFntAnimatedIndicator*/             \
  0,                /* ucAutoSwitching*/                    \
  0,                /* ucAfs123Fitted*/                     \
  0,                /* ucHandOfDrive*/                      \
  0,                /* ucHeightInputSelection*/             \
  0,                /* ucHdlampLvlSensPos*/                 \
  0,                /* ucVariantId*/                        \
  0,                /* biSblEnabled */                      \
  0,                /* biADBInitialisation */               \
  0,                /* biReserved */                        \
  0,                /* ucFrontCamera */                     \
  0,                /* ucTouristMode */                     \
  0,                /* ucWakeupShutdownSeqTyp */            \
  0,                /* ucManualHeadLampLeveling */          \
  {0,0,0,0,0},      /* auReserved2[5]*/                     \
  0,                /* ucDynBendingLight */                 \
  0,                /* ucSignPostDimming */                 \
  0,                /* ucPixelTouristMode */                \
  {0,0,0}           /* auReserved[3]*/                      \
}                                                            
#elif defined L663
#define NVMPARA_SYSTEM_CARCONFIG_INIT                       \
{                                                           \
  170,              /* ucCarConfigValid*/                   \
  0,                /* ucVehicleType*/                      \
  0,                /* ucSteeringWheelPosition*/            \
  0,                /* ucModelYear */                       \
  0,                /* ucGearBoxType*/                      \
  0,                /* ucHeadlightsVariant*/                \
  0,                /* ucHeadLampsSymmetry*/                \
  0,                /* unWheelBase */                       \
  0,                /* ucSuspension*/                       \
  0,                /* biDeliveryModeBattery*/              \
  0,                /* biDeliveryModeSuspension*/           \
  0,                /* biDeliveryModeLocking*/              \
  0,                /* biDeliveryFactoryModeActive*/        \
  0,                /* biCorneringLightsFitted*/            \
  0,                /* biExteriorLightsWakeUpSequence*/     \
  0,                /* biCornerLampFunction*/               \
  0,                /* biSideMarkersFitted*/                \
  0,                /* ucCornerOnThreshold*/                \
  0,                /* ucLaserHighBeam*/                    \
  0,                /* ucAdaptDrvBeam*/                     \
  0,                /* ucFntAnimatedIndicator*/             \
  0,                /* ucAutoSwitching*/                    \
  0,                /* ucAfs123Fitted*/                     \
  0,                /* ucHandOfDrive*/                      \
  0,                /* ucHeightInputSelection*/             \
  0,                /* ucHdlampLvlSensPos*/                 \
  0,                /* ucVariantId*/                        \
  0,                /* biSblEnabled */                      \
  0,                /* biADBInitialisation */               \
  0,                /* biFrontFogFuntionality */            \
  0,                /* biAhbSystemStatus */                 \
  0,                /* ucSensorSlopeType */                 \
  0,                /* ucFrontCamera */                     \
  0,                /* ucTouristMode */                     \
  0,                /* ucWakeupShutdownSeqTyp */            \
  0,                /* ucManualHeadLampLeveling */          \
  {0,0,0,0,0},      /* auReserved2[5]*/                     \
  0,                /* ucDynBendingLight */                 \
  0,                /* ucSignPostDimming */                 \
  0,                /* ucPixelTouristMode */                \
  {0,0,0}           /* auReserved[3]*/                      \
}                                                            
#else
#define NVMPARA_SYSTEM_CARCONFIG_INIT                       \
{                                                           \
  170,              /* ucCarConfigValid*/                   \
  0,                /* ucVehicleType*/                      \
  0,                /* ucSteeringWheelPosition*/            \
  0,                /* ucModelYear */                       \
  0,                /* ucGearBoxType*/                      \
  0,                /* ucHeadlightsVariant*/                \
  0,                /* ucHeadLampsSymmetry*/                \
  0,                /* unWheelBase */                       \
  0,                /* ucSuspension*/                       \
  0,                /* biDeliveryModeBattery*/              \
  0,                /* biDeliveryModeSuspension*/           \
  0,                /* biDeliveryModeLocking*/              \
  0,                /* biDeliveryFactoryModeActive*/        \
  0,                /* biCorneringLightsFitted*/            \
  0,                /* biExteriorLightsWakeUpSequence*/     \
  0,                /* biCornerLampFunction*/               \
  0,                /* biSideMarkersFitted*/                \
  0,                /* ucCornerOnThreshold*/                \
  0,                /* ucLaserHighBeam*/                    \
  0,                /* ucAdaptDrvBeam*/                     \
  0,                /* ucFntAnimatedIndicator*/             \
  0,                /* ucAutoSwitching*/                    \
  0,                /* ucAfs123Fitted*/                     \
  0,                /* ucHandOfDrive*/                      \
  0,                /* ucHeightInputSelection*/             \
  0,                /* ucHdlampLvlSensPos*/                 \
  0,                /* ucVariantId*/                        \
  0,                /* biSblEnabled */                      \
  0,                /* biADBInitialisation */               \
  0,                /* biReserved */                        \
  0,                /* ucFrontCamera */                     \
  0,                /* ucTouristMode */                     \
  0,                /* ucWakeupShutdownSeqTyp */            \
  0,                /* ucManualHeadLampLeveling */          \
  {0,0,0,0,0}       /* auReserved2[5]*/                     \
}                                                            
#endif

typedef struct
{
  uint8 ucCafTypeIx_High;
  uint8 ucCafTypeIx_Middle;
  uint8 ucCafTypeIx_Low;
  uint8 ucReserviert;
  uint8 ucSYS_LowSupply_V;
  uint8 ucSYS_LowSupply_T;
  uint8 ucSYS_HighSupply_V;
  uint8 ucSYS_HighSupply_T; 
  uint8 ucDIA_FctTest_OffTime;
  uint8 ucDIA_FctTest_OnTime;

  tNvmPara_System_VariantSelection  VariantSelection;   //2 Bytes
  
  uint8 STP_SPANNUNG_DEBOUNCE_ON;  ///< [0,01 s] Einschalt Verzögerungszeit nach Spannungs bedingtem Anhalten oder Abschalten
                                    // FLM3.SWRS.14433, FLM3.SWRS.27065, FLM3.SWRS.27066
                                    //    * The application shall repeat the referencing of LWR Stepper when the referencing was interrupted by low voltage and VBAT is once again greater or equal than COD_STP_SPANNUNG_LO1 for COD_STP_SPANNUNG_DEBOUNCE_ON.
                                    //    * The application shall resume   LWR Stepper movement, when VBAT is once again is greater than COD_STP_SPANNUNG_LO1 for COD_STP_SPANNUNG_DEBOUNCE_ON. 
                                    //    * The application shall continue LWR Stepper movement, when VBAT is once again is lower   than COD_STP_SPANNUNG_HI1 for COD_STP_SPANNUNG_DEBOUNCE_ON. 
  uint8 STP_SPANNUNG_DEBOUNCE_OFF; ///< [0,01 s] Ausschalt Verzögerungszeit  für Spannungs bedingtes Anhalten oder Abschalten
                                    // FLM3.SWRS.27502, FLM3.SWRS.27062, FLM3.SWRS.27063
                                    //    * The application shall set the LWR Stepper to off (lost reference) when VBAT is lower   than COD_STP_SPANNUNG_LO3 for COD_STP_SPANNUNG_DEBOUNCE_OFF and the LWR Stepper is moving in normal operation. 
                                    //    * The application shall stop and hold LWR Stepper position movement, if  VBAT is greater than COD_STP_SPANNUNG_HI2 for COD_STP_SPANNUNG_DEBOUNCE_OFF.
                                    //    * The application shall stop and hold LWR Stepper position movement, if  VBAT is lower   than COD_STP_SPANNUNG_LO2 for COD_STP_SPANNUNG_DEBOUNCE_OFF.
  uint8 STP_SPANNUNG_LO3;          ///< [0.1 V] Spannungsschwelle fuer die harte Abschaltung des Treibers bei Unterspannung
  uint8 STP_SPANNUNG_LO2;          ///< [0.1 V] Spannungsschwelle für das Anhalten des Motors bei Unterspannung  (N.b.: KEIN Anhalten bei Ref-Run)
  uint8 STP_SPANNUNG_LO1;          ///< [0.1 V] Spannungsschwelle für die Reaktivierung des Motors nach Unterspannung
  uint8 STP_SPANNUNG_HI1;          ///< [0.1 V] Spannungsschwelle für die Reaktivierung des Motors nach Ueberspannung
  uint8 STP_SPANNUNG_HI2;          ///< [0.1 V] Spannungsschwelle für das Anhalten des Motors bei Ueberspannung
  uint8 STP_SPANNUNG_RED;          ///< [0.1 V] Spannung, unter der die maximale Verstellfrequenz reduziert wird. Die Reduktion der maximalen Verstellfrequenz erfolgt annaehernd linear zur Versorgungsspannung.

  uint8 STP_ZEIT_TT;               ///< [s]     Dauer des Tieftemperaturmodus, unabhaengig davon, ob die Tieftemperaturinformation nach Ende des Zeitintervalls noch anliegt. Der Tieftemperaturzustand kann nur einmal pro Power-On-Zyklus aktiviert werden.
  uint8 STP_ZEIT_HT;               ///< [s]     Minimale Dauer des Hochtemperaturmodus. Der Hochtemperaturmodus wird jedes Mal aktiviert, wenn vom Schrittmotortreiber eine Uebertemperaturwarnung erfolgt und verbleibt für mindestens STP_ZEIT_HT in diesem Zustand.
  uint8 STP_WERT_TT;               ///< [Deg + 40] Temperaturgrenzwert, unter dem der Tieftemperaturmodus aktiviert wird

  uint8 STP_QUELLE_TT /* : 2 */;   ///  FLM3:  // Source of temp.: 1..12=NTC1-12, 16=PCB, 17=CAN - SWRS.27423     -----    < 0 = Temperaturmessung durch Sensor im FLE

// jk-obsolet uint8 reserviertQTT : 2;
// jk-obsolet uint8 reserviert    : 6;   ///< Reserviert
// jk-obsolet uint8 ucReserviert2[16];
}
tNvmPara_SystemBlock;







#endif // __CODM_PARA_SYSTEM_H__

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

///-----------------------------------------------------------------------------
///  \file   NvM_Para_System.h
///
///  \brief  Content of datagroup "System"
///
///  \descr  Source: LDMO_CodingTool_FULL.xlsm. 
///          Version TBD 
///          For further details see coding parameter
///
///  \author This file is auto generated - please do not edit
///
///  \date   22.09.2021, 11:36:17
///-----------------------------------------------------------------------------
typedef struct
{
  //0xAA = invalid ( 170 )
  //0x55 = valid (85)
  uint8 ucCarConfigValid;
  // OK                               
  uint8 ucVehicleType;
  // OK
  uint8 ucSteeringWheelPosition;
  // not sent inCANOe
  uint8 ucModelYear;
  // OK
  uint8 ucGearBoxType;
  // OK
  uint8 ucHeadlightsVariant;
  // not evaluated but sent
  uint8 ucHeadLampsSymmetry;
  // OK
  uint16 unWheelBase;
  // CANOE OK, Code not evaluated
  uint8 ucSuspension;
  // OK
  uint8 biDeliveryModeBattery : 1;
  // OK
  uint8 biDeliveryModeSuspension : 1;
  // OK
  uint8 biDeliveryModeLocking : 1;
  // OK
  uint8 biDeliveryFactoryModeActive : 1;
  // OK
  uint8 biCorneringLightsFitted : 1;
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
  uint8 biReserved : 5;
  uint8 ucFrontCamera;
  uint8 ucTouristMode;
  uint8 ucWakeupShutdownSeqTyp;
#ifdef D7U
  uint8 ucDynBendingLight;
  uint8 ucSignPostDimming;
  uint8 auReserved[4];
#endif
}
tNvmPara_CarConfig;

typedef struct
{
  uint8 CodingTypeIx_High; // High-Level Codierdatensyntax-Index: Incompatibility
                                          // of the data themselves and others
  uint8 CodingTypeIx_Middle; // Middle-Level Codierdatensyntax-Index: Incompatibility
                                          // of the data themselves and others
  uint8 CodingTypeIx_Low; // Low-Level Codierdatensyntax-Index: small
                                          // changes in Codierdatensyntax
  uint8 reserviert1;
  uint8 SYS_LowSupply_V; //Undervoltage fault: voltage value
  uint8 SYS_LowSupply_T; //Undervoltage fault: time duration
  uint8 SYS_HighSupply_V; //Overvoltage fault: voltage value
  uint8 SYS_HighSupply_T; //Overvoltage fault: time duration
}
tNvmPara_System_SystemData;

typedef struct
{
  uint8 VehicleType; //02 = L560
                                          //12 = L494
                                          //13 = X512
                                          //15 = X760
                                          //03 = L550
                                          //18 = L551
                                          //200 - 203 = AL interne Variant
  uint8 HeadlightsVariant; //Selects the headlights variant
                                          //0x00 = Not Supported
                                          //0x01 = Headlamp_Variant_Low_A
                                          //0x02 = Headlamp_Variant_Low_B
                                          //0x03 = Headlamp_Variant_Low_C
                                          //0x04 = Headlamp_Variant_Mid_A
                                          //0x05 = Headlamp_Variant_Mid_B
                                          //0x06 = Headlamp_Variant_Mid_C
                                          //0x07 = Headlamp_Variant_Mid+_A
                                          //0x08 = Headlamp_Variant_Mid+_B
                                          //0x09 = Headlamp_Variant_Mid+_C
                                          //0x0A = Headlamp_Variant_High_A
                                          //0x0B = Headlamp_Variant_High_B
                                          //0x0C = Headlamp_Variant_High_C
                                          //0x0D = Headlamp_Variant_High+_A
                                          //0x0E = Headlamp_Variant_High+_B
                                          //0x0F = Headlamp_Variant_High+_C
                                          //0xFF = Error
                                          //
}
tNvmPara_System_VariantSelection;

typedef struct
{
  uint8 Stp_Voltage_Low3; // Voltage threshold for hard dhutdoen of the
                                          // driver in case of undervoltage
  uint8 Stp_Voltage_Low2; // Voltage threshold to stop the engine in case
                                          // of undervoltage
  uint8 Stp_Voltage_Low1; // Voltage threshold to reactivate the motor
                                          // by undervoltage
  uint8 Stp_Voltage_High1; // Voltage threshold to reactivate the engine
                                          // after overvoltage
  uint8 Stp_Voltage_High2; // Voltage threshold to stop the engine in case
                                          // of overvoltage
  uint8 Stp_Voltage_High_Reduce; // Voltage, at which maximum adjustable frequency
                                          // is reduced. The reduction of the maximum
                                          // adjustable frequency is performed almost
                                          // linearly to the supply voltage.
  uint8 Stp_DurationLowTempMode; // Duration of the low-temperature mode, regardless
                                          // of whether the low-temperature information
                                          // if it is present after the end of the time
                                          // intervals. The low-temperature state can
                                          // be enabled once per Power-On-Cycles.
  uint8 Stp_DurationHighTempMode; // Minimum duration of the high temperature
                                          // mode. The high temperature mode is activated
                                          // every time, if in the stepper motor driver
                                          // warning an over temperature warning is and
                                          // remains for at least STP_ZEIT_HT in this
                                          // state.
  uint8 Stp_LowTempModeThreshold; // Temperature threshold below the low-temperature
                                          // mode is activated
  uint8 Stp_Source_LowTemp : 2; // 0 = Temperature measurement through the sensor
                                          // in FLE
                                          //1 = evaluation CAN-Signal
                                          //2 = reserved
                                          //3 = reserved
  uint8 reserviert11 : 6;
}
tNvmPara_System_Stepper;

typedef struct
{
  uint8 ucDbl_Enable; // 0: Dbl feature disabled, 1: Dbl feature enabled
  uint8 ucGFHB_Enable; // 0: GFHB feature disabled, 1: GFHB feature
                                          // enabled
  uint8 ucCurtainEffect_Enable; // 0: CurtainEffect feature disabled, 1: CurtainEffect
                                          // feature enabled
  uint8 ucTSAG_Enable; // 0: TSAG feature disabled, 1: TSAG feature
                                          // enabled
  uint8 ucMotorway_Enable; // 0: Motorway feature disabled, 1: Motorway
                                          // feature enabled
  uint8 ucHBB_Enable; // Always set to 1 for DPEMCA
  uint8 AIMING_MODE_FEEDBACK_COUNTER;
  uint8 AIMING_MODE_FEEDBACK_FREQU;
}
tNvmPara_System_Configurability;

typedef struct
{
  uint8 ucPixelFault_DebounceTime;
  uint8 ucCrcFault_DebounceTime;
  uint8 ucComFault_DebounceTime;
  uint8 ucComFault_NumberOfRetries;
  uint8 ucreserviert1[4];
}
tNvmPara_System_PxlDebounce;

typedef struct
{
  tNvmPara_System_SystemData             SystemData;
  tNvmPara_System_VariantSelection       VariantSelection;
  tNvmPara_System_Stepper                Stepper;
  tNvmPara_System_Configurability        Configurability;
  tNvmPara_System_PxlDebounce            PxlDebounce;
} tNvmPara_SystemBlock;

#endif // __CODM_PARA_SYSTEM_H__

// EOF
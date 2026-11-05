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
/// \file   ErrCust_Types.h
///
/// \brief  Provide data types for ErrCust module
///
/// \descr  
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef __ERRCUST_TYPES_H__
#define __ERRCUST_TYPES_H__

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <Std_Types.h>

//-----------------------------------------------------------------------------
// defines
//-----------------------------------------------------------------------------
#define       JDD_MAX_FIFO_ENTRIES        20u

// Number of LED Channels
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
#define ERRCUST_NO_OF_LED_CHANNELS       (uint8) 12u
#elif defined (CFG_VARIANT_ECO)
#define ERRCUST_NO_OF_LED_CHANNELS       (uint8)  4u
#endif

// Number of Logical Units
#define ERRCUST_LU_NR                    (uint8)103u
// Reserved bits for D421
#define ERRCUST_RESERVED_D421            (uint8)0x7F
// Reserved bits for D422
#define ERRCUST_RESERVED_D422            (uint8)0x0F
// Start index of EXT NTC RBIN
#define ERRCUST_EXT_NTCBIN_START         (uint8)  0u
// Start index of LMM NTC RBIN
#define ERRCUST_LMM_NTCBIN_START         (uint8) 14u
// Start index of EEPROM NTC RBIN
#define ERRCUST_EEPROM_NTCBIN_START      (uint8) 21u
// Number of maximum NTC BIN inputs
#define ERRCUST_MAX_NTCBIN_INPUTS        (uint8) 33u

// Light functions
#define ERRCUST_LIGHT_FUNCTION_LB        (uint8)  0u
#define ERRCUST_LIGHT_FUNCTION_HB        (uint8)  1u
#define ERRCUST_LIGHT_FUNCTION_DRL_POS   (uint8)  2u
#define ERRCUST_LIGHT_FUNCTION_TI        (uint8)  3u
#define ERRCUST_LIGHT_FUNCTION_SM        (uint8)  4u
#define ERRCUST_LIGHT_FUNCTION_RGB       (uint8)  5u
#define ERRCUST_LIGHT_FUNCTION_FOG       (uint8)  6u
#define ERRCUST_LIGHT_FUNCTION_CORNERING (uint8)  7u

#define ERRCUST_LF_LB                    (uint8)  1u
#define ERRCUST_LF_LB_FuSa               (uint8)  2u
#define ERRCUST_LF_HB                    (uint8)  3u
#define ERRCUST_LF_DRL_POS               (uint8)  4u
#define ERRCUST_LF_DRL_POS_SCRL          (uint8)  5u
#define ERRCUST_LF_TI                    (uint8)  6u
#define ERRCUST_LF_TI_SCRL               (uint8)  7u
#define ERRCUST_LF_SM                    (uint8)  8u
#define ERRCUST_LF_RGB                   (uint8)  9u
#define ERRCUST_LF_FOG                   (uint8) 10u
#define ERRCUST_LF_LB_BOOST              (uint8) 11u
#define ERRCUST_LF_HB_BOOST              (uint8) 12u
#define ERRCUST_LF_CL                    (uint8) 13u
#define ERRCUST_LF_PXL                   (uint8) 14u
#define ERRCUST_LF_MXB                   (uint8) 15u

//Bits shift macros
#define ERRCUST_1BIT_SHIFT               (uint8)  1u
#define ERRCUST_2BIT_SHIFT               (uint8)  2u
#define ERRCUST_3BIT_SHIFT               (uint8)  3u
#define ERRCUST_4BIT_SHIFT               (uint8)  4u
#define ERRCUST_5BIT_SHIFT               (uint8)  5u
#define ERRCUST_6BIT_SHIFT               (uint8)  6u
#define ERRCUST_7BIT_SHIFT               (uint8)  7u
#define ERRCUST_8BIT_SHIFT               (uint8)  8u
#define ERRCUST_9BIT_SHIFT               (uint8)  9u
#define ERRCUST_15BIT_SHIFT              (uint8) 15u

// Starting index from the second element
#define ERRCUST_START_INDEX_2            (uint8)  2u
// Index offset for 6'th element
#define ERRCUST_OFFSET_INDEX_6           (uint8)  6u
// Index offset for 10'th element
#define ERRCUST_OFFSET_INDEX_10          (uint8) 10u


//-----------------------------------------------------------------------------
// enum
//-----------------------------------------------------------------------------
typedef enum
{
  eDiag_FunctionFailed = 0U,
  eDiag_FunctionInhibated,
  eDiag_FunctionNotImplemented,
  eDiag_FunctionActive
}teErrCust_Types_DrvleEclairage;

typedef enum
{
  eDiag_Indeterminate = 0U,
  eDiag_NoFault,
  eDiag_Fault,
  eDiag_NotUsed
}teErrCust_Types_DrvledDiag;

typedef enum
{
  eDiag_OFF = 0U,
  eDiag_ON
}teErrCust_Types_DrvledEtat;

typedef enum
{
  eErrCust_ClearSingleDtc = 0U,
  eErrCust_ClearNotSupported,
  eErrCust_ClearGroupOfDtcs,
  eErrCust_ClearAllDtcs
}teErrCust_Types_Clear;

typedef enum
{
  eLeft = 0,
  eRight = 1,
  eUndef = 255
}teErrCust_Types_MountingSide;

//-----------------------------------------------------------------------------
// structures
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// RTE data for levelling
typedef struct {
  // stepper level position
  sint8  cStpPosDegree;
  // Status of Automatic Levelling
  uint8   ucStsAutoLvl;
  // Step loss, position or direction defect of leveling stepper
  boolean boStpLossLvl;
  // Communication defect of leveling stepper
  boolean boCommDefLvl;
  // Electrical defect of leveling stepper
  boolean boElecDefLvl;
  // Levelling stepper in motion (this value tells to the tester if the stepper is moving or not)
  boolean boMoveLvlStp;
  // Position defect of levelling stepper
  boolean boPosDefLvl;
  // Thermic defect of levelling stepper
  boolean boThermDefLvl;
} tsErrCust_TypesActStatStp;

//-----------------------------------------------------------------------------
// Aftermarket RBIN/NTC Failure data
typedef struct
{
  uint8 ucErrPerLightFunc;
}tsErrCust_AftermarketRbinNtcFailureData;

//-----------------------------------------------------------------------------
// Aftermarket RBIN EEPROM LMM data
typedef struct
{
  uint8 ucFirstByte;
  uint8 ucSecondByte;
  uint8 ucThirdByte;
  uint8 ucFourthByte;
  uint8 ucFifthByte;
}tsErrCust_AftermarketRbinEepromLmmData;

//-----------------------------------------------------------------------------
// Aftermarket LED Channel Output data
typedef struct
{
  uint8 ucFirstErrorByte;
  uint8 ucSecondErrorByte;
}tsErrCust_AftermarketLedChnlOutData;

//-----------------------------------------------------------------------------
// Aftermarket ATTITUDE ECU data
typedef struct
{
  sint16 snOffsetCalibVehicleAttitude;
  sint16 snInstValVehiculeAttitude;
}tsErrCust_AftermarketAttitudeEcuData;

//-----------------------------------------------------------------------------
// Aftermarket LVL ECU data
typedef struct
{
  uint8 ucVoltageTerminal;
  sint8 scInstantLvlPos;
  uint8 ucLvlInfo;
}tsErrCust_AftermarketLvlEcuData;

//-----------------------------------------------------------------------------
// Aftermarket CONTEXT ECU data
typedef struct
{
  uint8  ucVoltageTerminal;
  uint8  ucEtatInfo;
  uint8  ucVehicleSpeed;
  uint32 ulKilometrage;
  uint8  ucInstVal_FL_Bhs;
  uint8  ucInstVal_RL_Bhs;
}tsErrCust_AftermarketContextEcuData;

//-----------------------------------------------------------------------------
// Dtc structure
typedef struct {
  uint32 ulDtc;
  uint8  ucCycle;
} tsErrCust_PsDtcs;

//-----------------------------------------------------------------------------
// Attitude data
typedef struct {
  // Offset Calibration Vehicle Attitude
  sint16  snOffsetCalibVehicle_Attitude;
  // Instant Value Vehicule Attitude
  sint16  snInstValVehicule_Attitude;
} tsErrCust_FreezeAttFrameDataRamStruct;

//-----------------------------------------------------------------------------
// Levelling data
typedef struct {
  // Cl15 voltage
  uint8  ucCl15;
  // stepper level position
  sint8  scInstantLvl_Pos;
  // Status of Automatic Levelling
  uint8  bStsAutoLvl : 2;
  // reserved 2-3
  uint8  breserved : 2;
  // Step loss, position or direction defect of leveling stepper
  uint8  bStpLossLvl : 1;
  // Communication or time out defect of leveling stepper
  uint8  bCommDefLvl : 1;
  // Communication or time out defect of leveling stepper
  uint8  bElecDefLvl : 1;
  // Levelling stepper in motion (this value tells to the tester if the stepper is moving or not)
  uint8  bMoveLvlStp : 1;
} tsErrCust_FreezeStpFrameDataRamStruct;

//-----------------------------------------------------------------------------
// Context data
typedef struct {
  // Voltage Terminal
  uint8  ucCl15;
  // state of ETAT_RESEAU_ELEC
  uint8  bEtatReseauElec : 4;
  // state of ETAT_PRINCIP_SEV
  uint8  bEtatPrincipSev : 2;
  // reserved
  uint8  breserved : 2;
  // Vehicle Speed
  uint8  ucVehicleSpeed;
  // Kilometrage
  uint32 ulKilometrage;
  // Instantaneous value of Front Left BHS
  uint8  ucInstValFlBhs;
  // Instantaneous value of Rear Left BHS
  uint8  ucInstValRlBhs;
} tsErrCust_FreezeCtxFrameDataRamStruct;

// Structure for light functions state
// 0 = OK, 1 = NOK
typedef struct
{
  boolean boLb_State;
  boolean boSbl_State;
  boolean boTi_State;
  boolean boHb_State;
  boolean boGfHb_State;
  boolean boDrl_State;
  boolean boPos_State;
}tsErrCust_LgtFctState;

// Structure for light functions status 
// 0 = OFF, 1 = ON
typedef struct
{
  boolean boLb_Status;
  boolean boSbl_Status;
  boolean boTi_Status;
  boolean boHb_Status;
  boolean boGfHb_Status;
  boolean boDrl_Status;
  boolean boPos_Status;
  boolean boSM_Status;
  boolean boFog_Status;
}tsErrCust_LgtFctStatus;

// Structure for RBIN failure per light function
typedef struct
{
  uint8  aucChannelName[ERRCUST_NO_OF_LED_CHANNELS];
  uint8  aucRbinError[ERRCUST_NO_OF_LED_CHANNELS];
  uint8  aucNtcError[ERRCUST_NO_OF_LED_CHANNELS];
}tsErrCust_RbinFailLightFunc;


#endif // __ERRCUST_TYPES_H__

//EOF

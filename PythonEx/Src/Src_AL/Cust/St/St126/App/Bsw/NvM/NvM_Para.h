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
/// \file   NvM_Para.h
///
/// \brief  NvM Parameter structure definitions
///
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef NV_M_PARA_2021_03_31_H_
#define NV_M_PARA_2021_03_31_H_


//=============================================================================
// includes
//=============================================================================

#include <AL_Helper.h>
#include <ErrCust.h>
#include <Dem.h>
#include <stdbool.h>
//#include <Swc/CodM/CodM_Para.h>

//=============================================================================
// Data types
//=============================================================================

typedef struct
{
  uint8  aucRbinNtcErrPerLightFunc[ERRCUST_FREEZE_FRAME_DATA_ENTRIES];          // Bit 0: [Data] RBIN NTC Failure per light function: LB_Diag               [0xD420]
                                                                                // Bit 1: [Data] RBIN NTC Failure per light function: HB_Diag               [0xD420]
                                                                                // Bit 2: [Data] RBIN NTC Failure per light function: DRL_POS_Diag          [0xD420]
                                                                                // Bit 3: [Data] RBIN NTC Failure per light function: TI_Diag               [0xD420]
                                                                                // Bit 4: [Data] RBIN NTC Failure per light function: SM_Diag               [0xD420]
                                                                                // Bit 5: [Data] RBIN NTC Failure per light function: RGB_Diag              [0xD420]
                                                                                // Bit 6: [Data] RBIN NTC Failure per light function: Fog_Light_Diag        [0xD420]
                                                                                // Bit 7: [Data] RBIN NTC Failure per light function: Cornering_Light_Diag  [0xD420]
  uint8  aucRbinEepromLmmFirstByte[ERRCUST_FREEZE_FRAME_DATA_ENTRIES];          // Bits 0-7: [Data] RBIN/NTC DIAG 8-1   [0xD421]
  uint8  aucRbinEepromLmmSecondByte[ERRCUST_FREEZE_FRAME_DATA_ENTRIES];         // Bits 0-1: [Data] EEPROM DIAG 2-1     [0xD421]
                                                                                // Bits 2-7: [Data] RBIN/NTC DIAG 14-9  [0xD421]
  uint8  aucRbinEepromLmmThirdByte[ERRCUST_FREEZE_FRAME_DATA_ENTRIES];          // Bits 0-7: [Data] EEPROM DIAG 10-3    [0xD421]
  uint8  aucRbinEepromLmmFourthByte[ERRCUST_FREEZE_FRAME_DATA_ENTRIES];         // Bits 0-5: [Data] LMM DIAG 6-1        [0xD421]
                                                                                // Bits 6-7: [Data] EEPROM DIAG 12-11   [0xD421]
  uint8  aucRbinEepromLmmFifthByte[ERRCUST_FREEZE_FRAME_DATA_ENTRIES];          // Bits 0-6: reserved                   [0xD421]
                                                                                // Bit 7: [Data] LMM DIAG 7             [0xD421]
  uint8  aucLedChnlOutFirstByte[ERRCUST_FREEZE_FRAME_DATA_ENTRIES];             // Bits 0-7: [Data] LED Channel Output Diag 8-1   [0xD422]
  uint8  aucLedChnlOutSecondByte[ERRCUST_FREEZE_FRAME_DATA_ENTRIES];            // Bits 0-3: reserved                             [0xD422]
                                                                                // Bits 4-7: [Data] LED Channel Output Diag 12-9  [0xD422]
  sint16 asnOFFSET_CALIB_VEHICLE_ATTITUDE[ERRCUST_FREEZE_FRAME_DATA_ENTRIES];   // [Data] Calibration offset of vehicle attitude from network   [0xD4C9]
  sint16 asnINST_VAL_VEHICULE_ATTITUDE[ERRCUST_FREEZE_FRAME_DATA_ENTRIES];      // [Data] Instantaneous value of vehicle attitude from network  [0xD4C9]
  sint8  ascINSTANT_LVL_POS[ERRCUST_FREEZE_FRAME_DATA_ENTRIES];                 // [Data] Instantaneous angular levelling position                             [0xD4CB]
  uint8  aucLVL_INFO[ERRCUST_FREEZE_FRAME_DATA_ENTRIES];                        // Bits 0-1 [Data] Status of automatic levelling                               [0xD4CB]
                                                                                // Bits 2-3 reserved                                                           [0xD4CB]
                                                                                // Bit 4: [Data] Step loss, position or direction defect of levelling stepper  [0xD4CB]
                                                                                // Bit 5: [Data] Communication or time out defect of levelling stepper         [0xD4CB]
                                                                                // Bit 6: [Data] Electrical or thermic defect of levelling stepper             [0xD4CB]
                                                                                // Bit 7: [Data] Levelling stepper in motion                                   [0xD4CB]
  uint8  aucVOLTAGE_TERMINAL_DTC[ERRCUST_FREEZE_FRAME_DATA_ENTRIES];            // [Data] Voltage terminal value                 [0xE888]
  uint8  aucETAT_INFO_DTC[ERRCUST_FREEZE_FRAME_DATA_ENTRIES];                   // Bits 0-3: [Data] ETAT_RESEAU_ELEC state       [0xE888]
                                                                                // Bits 4-5: [Data] ETAT_PRINCIP_SEV state       [0xE888]
                                                                                // Bits 6-7 reserved                             [0xE888]
  uint8  VEHICLE_SPEED_DTC[ERRCUST_FREEZE_FRAME_DATA_ENTRIES];                  // [Data] Vehicle speed value                    [0xE888]
  uint32 KILOMETRAGE_DTC[ERRCUST_FREEZE_FRAME_DATA_ENTRIES];                    // [Data] Kilometrage value                      [0xE888]
  uint8  INST_VAL_FL_BODY_HIGH_SENSOR_DTC[ERRCUST_FREEZE_FRAME_DATA_ENTRIES];   // [Data] Instantaneous value of Front Left BHS  [0xE888]
  uint8  INST_VAL_RL_BODY_HIGH_SENSOR_DTC[ERRCUST_FREEZE_FRAME_DATA_ENTRIES];   // [Data] Instantaneous value of Rear Left BHS   [0xE888]
  uint8  aucAge[ERRCUST_FREEZE_FRAME_DATA_ENTRIES];                             // Age of the entry (age == 0: entry is free)
  uint8  aucDtcId[ERRCUST_FREEZE_FRAME_DATA_ENTRIES];                           // Dtc id of the freeze frame data
} tFreezeFrameDataPs8Struct;

//Structure for keeping aging counter and status for each DemEvntId
typedef struct {
  uint8 aucAgingCounter[DEM_CONFIG_ENTRY_MAX];                        // aging error counter
  uint8 aucStatus[DEM_CONFIG_ENTRY_MAX];                              // status flags
} tNvmDemData;


//Structure for keeping aging counter, status, bsi status, freeze frame index in deletion stamp for each DTC
typedef struct
{
  uint8  aucAgingCounter[ERRCUST_NUMBER_OF_DTCS];               // aging counter (40 = present)
  uint8  aucErrStatus[ERRCUST_NUMBER_OF_DTCS];                  // error status
  uint8  aucErrFreezeFrameIndex[ERRCUST_NUMBER_OF_DTCS];        // index of freeze frame data (FF if no data is avail)
  uint16 unReserved;                                            // reserved
  uint16 unDeletionStamp;                                       // deletion stamp
} tErrCustPs5Struct;

typedef enum
{
  eInput_Invalid = 0U,
  eInput_CAN = 1U,
  eInput_HLS = 2U
}teVacInput;

typedef enum
{
  eOptionSTT_Absent  = 0U,
  eOptionSTT_Present = 1U
}teFunctionSTT;

#if defined(SAMPLE_ECO) || defined(UNIT_TEST)
typedef enum
{
  eASL_Absent,
  eASL_Present
}teAslInput;
#endif

typedef struct tisNvmDeltaPwmPara
{
  sint32  slDeltaPwm_0;
  sint32  slDeltaPwm_1;
  uint16  unSensOffset_0;
  uint16  unSensOffset_1;
  uint8   ucZeroLevProg;
  sint16  snVehicleAttitude;
  teVacInput    eNVM_VAC_Input;
  teVacInput    eZeroLevProgInput;
  teFunctionSTT eNVM_Function_STT;
  uint8 ucSensPlausError[CFG_CntSens];
  uint8 ucSensGndError[CFG_CntSens];
  uint8 ucSensVbatError[CFG_CntSens];
#if defined(SAMPLE_ECO) || defined(UNIT_TEST)
  teAslInput eASL_Present;
#endif
}tisNvmDeltaPwmPara;

//StatM blocksize in bytes NvM
#define STATM_BLOCK_SIZE         512u
#define STATM_PADDING_SIZE         (STATM_BLOCK_SIZE-sizeof(tstStatistics))
#define STATM_MAX_LED_CHN          12u
#define STATM_MAX_FAN_NR            2u
#define STATM_MAX_TEMP_ZONES       12u
#define STATM_TEMP_CLASSES          6u
#define STATM_NR_BUCKS              6u

typedef struct tstStatistics {
    uint32 ulLedOnTime[STATM_MAX_LED_CHN];
    uint32 ulStepperHoldTime;
    uint32 ulStepperMoveTime;
    uint16 unStepperStarted;
    uint16 unStepperFinishedUnsuccesfull;
    uint16 unStepperSteploss;
    uint32 ulFanOnTime[STATM_MAX_FAN_NR];
    uint32 ulEcuOnTime;
    uint32 ulTempZoneTime[STATM_MAX_TEMP_ZONES][STATM_TEMP_CLASSES];
    uint32 ulPCBTempTime[STATM_TEMP_CLASSES];
    uint16 unEcuReset;
    uint16 unBuck_TW[STATM_NR_BUCKS];
    uint16 unBooster_TW;
    uint16 unBuck_TSD[STATM_NR_BUCKS];
    uint16 unBooster_TSD;
    uint16 unBooster_TempOut;
    uint16 unBooster_BoostOV;
    uint16 unBooster_VBSTDIV_UV;
    uint16 unBooster_VBSTDRIVE_NOK;
    uint16 unBooster_VBoostUV_Err;
    uint16 unBooster_VBoostOV_Err;
} tstStatistics;

typedef struct tstNvmStat {
    tstStatistics sStatistics;
    uint8 aucReserved[STATM_PADDING_SIZE];
} tstNvmStat;


/*    EEPROM Configuration     */

/* 1st Row : CRC,EEPROM Pattern, Marelli ID */

typedef volatile struct
{
  uint8       ucCrc;
  uint8       ucPattern[4];
  uint8       ucMarelliID;
  uint8       Reserved[10];
} tsCrcPatternAndReserved;

typedef union
{
  tsCrcPatternAndReserved  sCrcPatterAndReserved;
  uint8 Data[16];
}CtrlPxl_CrcPatternAndReserved_UnionType;

/* 2nd-8th Rows : PWM values (brightness) in 0.5% (8bit) */

//LMM_x (x=1..8) mapping 
typedef struct
{
  uint8 ucPXL_Bright_1;
  uint8 ucPXL_Bright_2;
  uint8 ucPXL_Bright_3;
  uint8 ucPXL_Bright_4;
  uint8 ucPXL_Bright_5;
  uint8 ucPXL_Bright_6;
  uint8 ucPXL_Bright_7;
  uint8 ucPXL_Bright_8;
  uint8 ucPXL_Bright_9;
  uint8 ucPXL_Bright_10;
  uint8 ucPXL_Bright_11;
  uint8 ucPXL_Bright_12;
}tsPXLChannel;

typedef union
{
  uint8        ucChannelByte[12u];
  tsPXLChannel sLEDChBrightness;
}tuPxlChannel;

typedef struct
{
  tuPxlChannel  uLEDChannelBrightness;
  uint8         Reserved[4u];
}tsPxlChannelAndReserved;

typedef union
{
  tsPxlChannelAndReserved   sLedChannelBrightnessAndReserved;
  uint8                     Data[16u];
}tuLEDChannelBrightnessAndReserved;

typedef struct
{
  tuLEDChannelBrightnessAndReserved LMM1;
  tuLEDChannelBrightnessAndReserved LMM2;
  tuLEDChannelBrightnessAndReserved LMM3;
  tuLEDChannelBrightnessAndReserved LMM4;
  tuLEDChannelBrightnessAndReserved LMM5;
  tuLEDChannelBrightnessAndReserved LMM6;
  tuLEDChannelBrightnessAndReserved LMM7;
  tuLEDChannelBrightnessAndReserved LMM8;   //reserved
}tsChannelBrightness;

typedef union
{
  tsChannelBrightness   sLMMBrightness;
  uint8                 Data[128];
}CtrlPxl_LMMBrightnessAndReserved_UnionType;


/* 9th Row : LED Channel BC(12bytes) */
typedef struct
{
  uint8 ucCh1;
  uint8 ucCh2;
  uint8 ucCh3;
  uint8 ucCh4;
  uint8 ucCh5;
  uint8 ucCh6;
  uint8 ucCh7;
  uint8 ucCh8;
  uint8 ucCh9;
  uint8 ucCh10;
  uint8 ucCh11;
  uint8 ucCh12;
}tsLedChannelBinningClass;

typedef union
{
  uint8                     ucLedChannelBC[12u];
  tsLedChannelBinningClass  sLedChannelBinClass;
}tuLedChannelBC;

typedef struct
{
  tuLedChannelBC  uLedChannelBC;
  uint8           Reserved[4u];
}tsLedChannelBCAndReserved;

typedef union
{
  tsLedChannelBCAndReserved sLedChannelBCAndReserved;
  uint8                     Data[16u];
}CtrlPxl_LedChannelBCAndReserved_UnionType;

/* 10th Row : Supplier (16 characters)  */
typedef struct
{
  uint8   ucSupplier[16u];
}tsSupplier;

/* 11th Row : Serial Number (16 bytes - ASCII)    */
typedef struct
{
  uint8   ucSN[16u];
}tsSerialNumber;


/* 12th Row : Production date (16 bytes - ASCII)  */
typedef struct
{
  uint8   ucProductionDate[16u];
}tsProductionDate;

/* 13th Row : Headlamp Identification (16 bytes- ASCII)  */
typedef struct
{
  uint8   ucHdlmpID[16u];
}tsHeadlampIdentification;

/* 14th Row : PartNumber HEADLAMP (16 bytes- ASCII)  */
typedef struct
{
  uint8   ucPartNumbHdlmp[16u];
}tsPartNumberHeadlamp;

/* 15th Row : Reserved (16 bytes- ASCII)  */
typedef struct
{
  uint8 Reserved[16u];
}tsReservedGroup;


typedef struct
{
  tsSupplier                sSupplierName;
  tsSerialNumber            sSerialNumber;
  tsProductionDate          sProductionDate;
  tsHeadlampIdentification  sHeadlampIdentification;
  tsPartNumberHeadlamp      sPartNumberHeadlamp;
  tsReservedGroup           sReservedIdentifGroup;
}tsIdentificationGroup;

typedef union
{
  tsIdentificationGroup   sIdentificationGroup;
  uint8                   Data[96u];
}CtrlPxl_IdentificationGroup_UnionType;


typedef struct
{
  CtrlPxl_CrcPatternAndReserved_UnionType     CrcPatternAndReservedGroup;       /* EEPROM: 1st row : ADDR 00-0F */
  CtrlPxl_LMMBrightnessAndReserved_UnionType  LMMBrightnessAndReservedGroup;    /* EEPROM: 2nd - 9th row : ADDR 10-8F */
  CtrlPxl_LedChannelBCAndReserved_UnionType   LedChannelBCAndReservedGroup;     /* EEPROM: 10th row : ADDR 90-9F */
  CtrlPxl_IdentificationGroup_UnionType       IdentificationGroup;              /* EEPROM: 11-16th row : ADDR A0-FF */
}tsMatrixParam_Data;


typedef union
{
  tsMatrixParam_Data MatrixParam_Data;
  uint8 Data[256u];
} tuNvmPara_EEProm;



typedef struct
{
  bool   boMotorStarted;
  bool   boMotorStopped;
  sint16  nPosition;
}
tDcMotorDataStruct;

typedef struct
{
  uint8   ucHeader;
  uint8   ucMaxAdjustingTime;
  uint8   ucInvalid;
}
tDcMotorCharacteristicStruct;

typedef struct tisStatAvacPrj1Para_tag
{
  uint8  byZeroSpeed;
  uint8  byMinSpeed;
  uint8  byMaxSpeed;

  uint8  byStaticFilterCoefAtInterStop;
  uint8  byStaticFilterCoefAtZeroSpeed;
  uint8  byStaticFilterCoefAtConstSpeed;

  uint8  bySampleTimeShort;
  uint8  bySampleTimeLong;

  sint16 nTransientStatePeriod;
  sint16 nConstantSpeedInterval;

  uint8  byFilterCoefInc;
  uint8  abyFilterCoefToUnlock[5];
}
tisStatAvacPrj1Para;

typedef struct tisStatAvac1Para_tag
{
  uint8  byDataHeader[2];
  uint8  byHighDynamicLimit;
  uint8  byAccFilterCoeff;
  uint8  byPowerOnMinChange;
  uint8  byDynamicMinChange;
  uint8  byInterStopMinChange;
  uint8  byStaticMinChange;
  sint16 nLoadChangeInterval;
}
tisStatAvac1Para;

typedef struct tisStatAvacOp1Data_tag
{
  sint16 nHeadlightAngle;
  sint16 nSafetyAngle;
  uint16 unAdjCounter;
}
tisStatAvacOp1Data;

// Network Management Backup Counters
typedef struct tisNmBackupCounters
{
  uint8 ucC_ABS_BSI_Counter;
  uint8 ucC_BusOff_Counter;
  uint8 ucC_Mute_Counter;
  uint8 ucUCE_ABS_RL_F_1_HDC_Counter;
}
tisNmBackupCounters;

#endif // NV_M_PARA_2021_03_31_H_

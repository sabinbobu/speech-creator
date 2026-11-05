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
/// \file  CtrlPxl_Types.h
///
/// \brief file contain all types for CtrlPxl module
///
/// \author Ionut Caba  ALRO-CJ (F37899C)
///         mailTo:ionut-stefan.caba[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef CTRL_PXL_TYPES_2021_03_09_H_
#define CTRL_PXL_TYPES_2021_03_09_H_

//=============================================================================
// includes
//=============================================================================
#include <Std_Types.h>
#include <CodM.h>
#include <Cfg/Cfg.h>
#include <UtilDebounce.h>
#include "CtrlPxl_Cfg.h"
#include <Bsw/Nvm/NvM_Para.h>

//=============================================================================
// defines
//=============================================================================

//=============================================================================
// types
//=============================================================================
typedef enum
{
  eEcu_Left = 0u,
  eEcu_Right = 1u,
  eEcu_Undef = 255u
}teCtrlPxl_EcuSide;

typedef enum
{
  eMatrixVccx_noError     = 0, //No error detected for Vccx voltage line
  eMatrixVccx_Short2GND   = 1, //Short to ground detected for Vccx line
  eMatrixVccx_Short2Vbat  = 2, //Short to battery detected for Vccx line
}teCtrlPxl_VccxLineState;

//Communication/ CRC frame defect states
typedef enum
{
  eCommDefect_NoErr = 0u,
  eCommDefect_RetryError,
  eCommDefect_WaitError,
  eCommDefect_SetError,
  eCommDefect_PermanentErr
}teCtrlPxl_MlcCommDefectStates;

//EEProm Handling
typedef enum
{
  eEEProm_Init = 0,
  eEEProm_Read,
  eEEProm_Write,
  eEEProm_CompareCRC,
  eEEProm_Wait,
  eEEProm_Finished,
  eEEProm_All
} teEEPromStates;

typedef enum
{
  eEEProm_Job_Initial = 0,
  eEEProm_Job_Pending,
  eEEProm_Job_Finished_Ok,
  eEEProm_Job_Error
}teEEPRom_Jobs;

typedef struct
{
  uint8 bDrv_Unit       : 4; //LED driver number
  uint8 bLmms_Unit      : 4; //LMM number
  uint8 bSwNr_Unit      : 4; //Switchnumber
  uint8 bThermZone_Unit : 4; //Thermozone
  uint8 ucBasePwm_Unit; //Base PWM  
}tsCtrlPxl_CodHelper;

typedef struct
{
  tNvmPara_CodingArea* psCodingParameters;
  tParaFct0_Cmd        eCodingState;
}tsCtrlPxl_CodingParameters;

typedef struct
{
  boolean boCommFault;
  boolean boCrcFault;
  boolean boPxlFault;
  boolean boShortToGnd;
  boolean boShortToVbat;
}tsCtrlPxl_MatrixFaultStates;

/* Structure containing all matrix errors on bit-field*/
typedef struct {
  uint8 bLossComm   : 1u;
  uint8 bCoruptComm : 1u;
  uint8 bPxlFault   : 1u;
  uint8 bEEPromErr  : 1u;
  uint8 Reserved    : 4u;
}tsCtrlPxl_bErr;

typedef union
{
  tsCtrlPxl_bErr  bErr;         // matrix errors mapped on bit fields
  uint8           ucRaw;
}tuCtrlPxl_bErr;

typedef struct
{
  tuCtrlPxl_bErr uMatrixErrors;
}tsCtrlPxl_MatrixErrors;

typedef struct
{
  uint8 ucMlcStatus;            //matrix communication status - the chip affected has 1 on the bit position
  uint8 ucPowerCycle;
}tsCtrlPxl_ComStatus;


typedef struct
{
  uint16 unLedFault;       // Led Status Segment : each bit represents a pixel
}tsCtrlPxl_bitsPxl;

typedef union
{
  tsCtrlPxl_bitsPxl bPxl;
  uint16            unRaw;
}tuCtrlPxl_PxlFault;


/* DEV - validation frames data */
typedef struct
{
  boolean boPxlDefect[CTRLPXL_CFG_MAX_NR_OF_PXL];
}tsCtrlPxl_ValidationFrames_PxlDefect;

/* DEV - validation frames data */
typedef struct
{
  uint8 ucPWMValue_Percentage[CTRLPXL_CFG_MAX_NR_OF_PXL];
}tsCtrlPxl_ValidationFrames_PWMValue;


/* ----------------  INTERNAL HANDLING ------------------------------------------- */

typedef struct
{
  uint8 aucMapLu[CTRLPXL_CFG_NR_OF_MATRIX_DRV][CTRLPXL_CFG_NR_OF_PXLs_STRING];       //corresponding logical units to[lmm][pxl] from "mapping list" from coding IFD
  uint8 aucMapLuToSeg[CTRLPXL_CFG_NR_OF_MATRIX_DRV][CTRLPXL_CFG_NR_OF_PXLs_STRING];  //save segment position corresponding to logical unit from "Matrix" sheet from coding IFD
  uint8 aucMapMtxSegments[CTRLPXL_CFG_MAX_NR_OF_PXL];                                //corresponding logical units to segments from "Matrix" sheet from coding IFD
}tsCtrlPxl_CodingData;


/* Union containing the mapping of Matrix Eeprom Memory */
/* -----------------  !! KEEP THE STRUCTURE SAME AS THE NVM MEMORY !! ------------ */
typedef union {
  tsMatrixParam_Data MatrixParam_Data;
  uint8 Data[256u];
}tuEEPromMapping;

typedef struct
{
  tuEEPromMapping uMtxEEPromMapping;
}tsEepromCfg;

// Calibration and binning class from mtx eeprom
typedef struct
{
  uint8 aucBrightnessVal[CTRL_PXL_NUMBER_OF_EEPROM_BRIGHTNESS];
  uint8 aucBinningClass[CTRL_PXL_NUMBER_OF_EEPROM_BINNING_CLASS];
}tsCtrlPxl_CalibData;


//Diagnostic control over EEPROM
typedef struct
{
  //activated when EEProm write from diag is request
  boolean boEEPromWrite;
  //activated when EEProm read from diag is request
  boolean boEEPromRead;
}tsEepromDiagCtrl;


typedef struct
{
  /* should be used only for IO Control (pwm control/ matrix on,off) as active and deactivate when return control to ECU
   services are called */
  boolean boDiagMatrixControlActive;
  //used only for EEProm (Lmm) services 
  tsEepromDiagCtrl sDiagEEPromControlActive;
}tsDiagControl;


//matrix structure for Eeprom control
typedef struct
{
  // diag control for CtrlPxl 
  tsDiagControl sDiagControl;
  // Represents diag status from EEPromCallback: TRUE = SUCCESS; FALSE = FAIL to inform diagnostic request
  boolean boMatrixEEPromInitHandlingReady;
  // Represent the status for EEProm handle based on callbacks from Lmm
  teEEPromStates eEEPromStates;
  //eeprom fault status - wrong checksum
  boolean boEepromChecksumFaultStatus;
  //eeprom fault status - no access
  boolean boEepromAccessFaultStatus;
}tsCtrlPxl_EepromControl;


/* Structure for Eeprom Handling: control & mapping*/
typedef struct
{
  tsCtrlPxl_CalibData         sCalibNvmDataUsed;
  tsCtrlPxl_EepromControl     sEepromControl;
  tsEepromCfg                 sMtxEEPromMapping;
}tsEEpromHandling;

/* Internal Structure containing the handling of Coding Mapping and Eeprom Mapping & Control*/
typedef struct
{
  tsCtrlPxl_CodingData        sCodingData;
  tsEEpromHandling            sEepromHandling;
}tsCtrlPxl_InternalHandling;


#endif // CTRL_PXL_TYPES_2021_03_09_H_

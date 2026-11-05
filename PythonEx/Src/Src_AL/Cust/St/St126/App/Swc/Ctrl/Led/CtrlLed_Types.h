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
/// \file  CtrlLed_Types.h
///
/// \brief  header file for types usage into core module
///
/// \author Caba Ionut-Stefan (F37899C)
///         mailTo:ionut-stefan.caba[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef CTRL_LED_TYPES_2021_03_30_H_
#define CTRL_LED_TYPES_2021_03_30_H_

//=============================================================================
// includes
//=============================================================================
#include <Std_Types.h>
#include <AL_Helper.h>
#include <Cfg/Cfg.h>
#include "CtrlLed_Cfg.h"
#include <Util_Time.h>
#include <CodM.h>

//=============================================================================
// types
//=============================================================================
typedef struct
{
  uint16 unOldIntensity;
  uint16 unOldRamping;
  uint16 unCurrentIntensity;
  uint16 unNewRamp;
}tsCtrlLed_RampValues;

// Ecu mounting side
typedef enum
{
  eEcu_Left = 0,
  eEcu_Right = 1,
  eEcu_Undef = 255
}teCtrlLed_EcuSide;

typedef struct
{
  // errors
  uint8  biDeratingState : 2;  ///< derating activation state
  uint8  biDeratingActive : 1;  ///< voltage derating factor <95%
} tsCtrlLed_LedBits;

typedef struct
{
  uint16                 unVoltageDeratingFactor;             ///< LED current depens on the Voltage derating
  tFTimer                VoltageDeratingDelay;                ///< delay start time
  tsCtrlLed_LedBits      Bit;
} tsCtrlLed_TgtDerating;

typedef struct
{
  tNvmPara_CodingArea* psCodingParameters_Blocks;
  tParaFct0_Cmd        eCodingState;
}tsCtrlLed_CodingParam;

typedef struct
{
  uint8 ucChannelStatus;
  boolean boVinOk;
}tsCtrlLed_ChannelState;

typedef struct
{
  tsCtrlLed_ChannelState asChannelState[CTRLLED_CFG_MAX_BUCK_DRV];
}tsCtrlLed_aChannelState;


typedef struct
{
  uint32 ulDisable_ErrE2E;
  uint32 ulDisable_ErrOpenLoad;
  uint32 ulDisable_ErrOverCurrent;
  uint32 ulDisable_ErrShortToGnd;
  uint32 ulDisable_ErrShortToUbat;
  uint32 ulDisable_ErrSpi;
  uint32 ulDisable_ErrThermalShutdown;
  uint32 ulDisable_ErrUnderVoltage;
  uint32 ulDisable_ErrOverVoltage;
}tsCtrlLed_ChannelSettings;

typedef struct
{
  uint8 ucLedState[CTRLLED_CFG_MAX_BUCK_DRV];
  tsCtrlLed_ChannelSettings sCtrlLed_ChannelSettings;
  boolean boSwitchOffBuck[CTRLLED_CFG_MAX_BUCK_DRV];
}tsCtrlLed_ErrorHandler;

typedef struct
{
  uint8 bDrv_Unit : 4; //LED driver number
  uint8 bLmms_Unit : 4; //LMM number
  uint8 bSwNr_Unit : 4; //Switchnumber
  uint8 bThermZone_Unit : 4; //Thermozone
  uint8 ucBasePwm_Unit; //Base PWM  
} tsCtrlLed_CodHelper;

typedef struct
{
  uint8 ucIlluminantAssigned;
  boolean boErrPresent[3];//3 type of error
  boolean boRowErr_Prv;
  boolean boRowErr_Act;
}tsCtrlLed_RowMtxErr;

typedef struct
{
  uint8 aucUg[13]; //fit on 104bits
} tsCtrlLed_CodHelperUg;

typedef struct
{
  tsCtrlLed_CodHelperUg uUnitGroups;
  uint8 ucName;
  uint8 ucIlluminantAssigned;
}tsCtrlLed_UnitGroups;

typedef struct
{
  uint16 aunGamma[CTRLLED_CFG_GAMMA_NUMBER][CTRLLED_CFG_GAMMA_POINTS];
  uint8  aucGammaSel[CTRLLED_CFG_NO_ILLUMINANTS];
  //uint8  aucGammaSelLuMx[CTRLLED_CFG_NR_OF_LOGICAL_UNITS]; //used only for matrix (decompressed data)
}tsCtrlLed_Gamma;


typedef enum
{
  eCheckError,
  eDoDebounce,
  eResetError,
  eWriteError
}teCtrlLed_DebounceState;

typedef enum
{
  CtrlLed_Diag_NoProblem = 0u,
  CtrlLed_Diag_ProblemOn_Btm = 1u,
  CtrlLed_Diag_ProblemOn_Mid = 2u,
  CtrlLed_Diag_ProblemOn_Top = 3u,
}teCtrlLed_MatrixRow;

typedef enum
{
  CtrlLed_Diag_MtxOff,
  CtrlLed_Diag_MtxLb_Dtc,
  CtrlLed_Diag_MtxHb_Dtc
}teCtrlLed_MatrixLight;

typedef enum
{
  CtrlLed_MtxDoNothing = 0U,
  CtrlLed_MtxFreeze_Write = 1U,
  CtrlLed_MtxFreeze_Skip = 2U,
  CtrlLed_MtxSwitchOff = 3U
}teCtrlLed_MatrixVoltCnd;

typedef struct
{
  TIMER ErrorDebounce;
  boolean boErrorWriteStatus;
}tsCtrlLed_ErrStatus;

typedef struct
{
  /* 0  */ uint16 bLedOL  : 1U;  //buck-> open load
  /* 1  */ uint16 bLedSG  : 1U;  //buck-> short to ground
  /* 2  */ uint16 bLedSB  : 1U;  //buck-> short to battery
  /* 3  */ uint16 bLedVL  : 1U;  //buck-> voltage low/under voltage
  /* 4  */ uint16 bLedVH  : 1U;  //buck-> voltage high/over voltage
  /* 5  */ uint16 bLedTS  : 1U;  //buck-> thermal shoutdown
  /* 6  */ uint16 bLedOC  : 1U;  //buck-> over current
  /* 7  */ uint16 bLedSPI : 1U;  //buck-> SPI
  /* 8  */ uint16 bLedCRC : 1U;  //buck-> CRC
  /* 9  */ uint16 bLedBoost : 1U;  //buck-> Boost
  /* 10 */ uint16 bMtxCC  : 1U;  //matrix-> corupt communication
  /* 11 */ uint16 bMtxLC  : 1U;  //matrix-> loss communication
  /* 12 */ uint16 bMtxPD  : 1U;  //matrix-> pixel defect
  /* 13 */ uint16 bMtxVccXSG : 1U;  //matrix-> Vccx short to ground
  /* 14 */ uint16 bMtxVccXSB : 1U;  //matrix-> Vccx short to battery
  /* 15 */ uint16 bMtxEeprom : 1U;  //matrix-> Eeprom no access/ wrong checksum
}tsCtrlLed_tsIlErr;

typedef union
{
  tsCtrlLed_tsIlErr bIlErr;
  uint16 unRaw;
}tuCtrlLed_IlErr;

typedef struct {
  uint8 bLossComm : 1u;
  uint8 bCoruptComm : 1u;
  uint8 bPxlFault : 1u;
  uint8 Reserved : 5u;
}tsCtrlLed_bErr;

typedef union
{
  tsCtrlLed_bErr  bErr;         // matrix errors mapped on bit fields
  uint8           ucRaw;
}tuCtrlLed_bErr;

typedef struct
{
  uint16 aunChannelIlluminant[CTRLLED_CFG_NO_ILLUMINANTS]; //used on bits
  uint8 aucChannelType[CTRLLED_CFG_LED_CHANNELS_NR];
  uint16 aunBinningCurrent[CTRLLED_CFG_LED_CHANNELS_NR];
  uint8 aucBinningSelection[CTRLLED_CFG_BASIC_LED_CH];
  tsCtrlLed_Gamma sGamma;
  uint8 ucLedName[CTRLLED_CFG_MAX_BUCK_DRV];
  uint8 ucLogicalUnitIl[CTRLLED_CFG_NO_ILLUMINANTS];
  uint8  aucAnimaMap[CTRLLED_CFG_NR_OF_LOGICAL_UNITS];
#if defined(CFG_VARIANT_FULL) || (UNIT_TEST)
  tsCtrlLed_UnitGroups asUnitGroups[CTRLLED_CFG_NO_UNIT_GROUPS];
  uint8 aucLmmSwitchNo[CTRLLED_CFG_MAX_NR_OF_PXL];
  uint8 aucLuIl[CTRLLED_CFG_NR_OF_LOGICAL_UNITS];
  boolean aboIlMtxType[CTRLLED_CFG_NO_ILLUMINANTS];
#endif
}tsCtrlled_CodingData;

typedef struct
{
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
  boolean boMtxLightStatus; //light distribution status
  boolean boFbitMtx; 
  boolean boMtxLightIlStatus[CTRLLED_CFG_NO_ILLUMINANTS]; //true - matrix illuminant is lighting
  uint8   ucMatrixRowLightBit; //pos 0->Lb_Btm, 1->Lb_Mid, 2-Hb
  uint8   ucMatrixRowLightBitPrv;
  tsCtrlLed_RowMtxErr sRowMtxErr[CTRLLED_MAX_MTX_COL_SEL];
  uint32 aulPixelAffected[CTRLLED_MAX_MTX_COL_SEL];
#endif
  tuCtrlLed_IlErr uIlluminantError[CTRLLED_CFG_NO_ILLUMINANTS];
}tsCtrlled_InternalHandlings;

typedef struct
{
  uint16 unDTC[CTRLLED_DIAG_MAX_ERR_USED];
}tsCtrlLed_DtcChList;

typedef struct
{
  uint8 ucReaction[CTRLLED_DIAG_MAX_ERR_USED];
}tsCtrlLed_ReactionChList;

#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
typedef struct
{
  uint8 ucReaction[1];
}tsCtrlLed_ReactionMtxList;

typedef struct
{
  uint8 ucReaction[1];
}tsCtrlLed_ReactionVccxList;

typedef struct
{
  uint16 unDTC[3];
}tsCtrlLed_DtcMtxHbLbList;


#endif
#endif // CTRL_LED_TYPES_2021_03_30_H_

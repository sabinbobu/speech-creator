#ifndef __RSENS_H__
#define __RSENS_H__

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
/// \file  RSens.h
///
/// \brief  
///
/// \descr  
///
///         Additional information can be found in the design description (Link:
///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
///
/// \author Sergej Immel  (F55102A)
///         mailTo:sergej.immel@al-lighting.com
//-----------------------------------------------------------------------------
//=============================================================================
// includes
//=============================================================================
#include <Cfg/Cfg.h>
//lint -e451 Header file repeatedly included but does not have a standard include guard
#ifndef UNIT_TEST
#include <Rte.h>
#endif
//lint +e451 Header file repeatedly included but does not have a standard include guard
#include <CodM.h>
#include <RSens_Types.h>


#define RSENS_THERMOZONE_COUNTER       12u

#if defined  (CFG_VARIANT_FULL) || defined (UNIT_TEST)
#define RSENS_LED_BINNING_CLASSES      12u
#else
#define RSENS_LED_BINNING_CLASSES      4u
#endif
//=============================================================================
// function prototypes
//=============================================================================
void RSens_ParaFct0(const tParaFct0_Cmd eCmd, const tNvmPara_CodingArea* const pData);
void RSens_Init(void);
void RSens_Cycle0(void);


/*******************************************************************************
* Definitions
*******************************************************************************/

typedef enum
{
  RSENS_CODINGMODE_UNDEFINE,
  RSENS_CODINGMODE_INIT,
  RSENS_CODINGMODE_INVALID,
  RSENS_CODINGMODE_DEFAULT,
  RSENS_CODINGMODE_VALID
} tRSens_CodingMode;

typedef struct
{
  uint8 biNoErr : 1;
  uint8 biGNDErr : 1;
  uint8 biVBATErr : 1;
  uint8 biOLErr : 1;
  uint8 biOvTemp : 1;
  uint8 Dummy : 3;
}tRSens_NTCBINFlag;

typedef union
{
  tRSens_NTCBINFlag  NTCBINFlag;
  uint8              ucRaw;
}tRsens_ErrorFlags;

typedef struct
{
  sint16 snTemp0;
  sint16 snTemp1;
  sint16 snVoltage0;
  sint16 snVoltage1;
}tsRsens_InterpolationInfo;

typedef enum
{
  eRSENS_SIG_SNA = 0U,
  eRSENS_SIG_VALID = 1U,
  eRSENS_SIG_INIT = 2U,
  eRSENS_SIG_INVALID = 3U,
  eRSENS_SIG_TIMEOUT = 4U,
  eRSENS_SIG_DEFAULT = 5U,
  eRSENS_SIG_E2E_CRCERR = 6U,
  eRSENS_SIG_E2E_ALIVEERR = 7U,
  eRSENS_SIG_E2E_TIMEOUT = 8U,
  eRSENS_SIG_UNAVAILABLE = 9U,
  eRSENS_SIG_DISABLED = 255U
}teRSens_SigQty;

typedef struct
{
  boolean boSh2Gnd;
  boolean boSh2Vbat;
  boolean boOpenload;
  teRSens_SigQty eSigQty;
}tsRsens_NTCErrState;

extern NtcTables RSens_Data_asnNTCB4000;
extern NtcTables RSens_Data_asnNTCB3650;
extern NtcTables RSens_Data_asnNTCB3380;



// interpolation table for Led NTcs
extern NtcTables* RSens_Data_apsnNTC[];
// interpolation table for LMM Temp
extern NtcTables  RSens_Data_asnLMM;



#endif // __RSENS_H__

#ifndef __AVACSTAT1DATA_H__
#define __AVACSTAT1DATA_H__

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
/// \file  AvacStat1Data.h
///
/// \brief  
///
/// \descr  
///
///         Additional information can be found in the design description (Link:
///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
///
/// \author Alf Traulsen  (taf2rt)
///         mailTo:alf.traulsen@al-lighting.com
//-----------------------------------------------------------------------------

#include <Std_Types.h>
#include <Nvm.h>

#include <Swc/CodM/CodM.h>
#include <Swc/CodM/CodM_Para.h>

#include "AvacStat1Init.h"
#include <AvacStat1Types.h>


extern tNvmPara_CodingArea* AvacStat1_pCodingArea;  // pointer to const data

typedef struct
{
  tNvmPara_CodingArea* psCodingParameters_Blocks;
  tParaFct0_Cmd        eCodingState;
}tsAvacStat1_CodingParam;

typedef enum
{
  eAvacStat1State_Init = 0,      // initial state
  eAvacStat1State_Adj = 1,      // Adjustment phase
  eAvacStat1State_Fail = 2       // dc motor defect
} teAvacStat1_LvlPhase;

// ----------------------------------------------------------------------------
// Function prototypes
// ----------------------------------------------------------------------------

void    AvacStat1Data_Get_CodingPara(tsAvacStat1_CodingParam *psCodingParam);
boolean AvacStat1Data_CodingDataValidation(void);
void    AvacStat1Data_Init(void);

boolean AvacStat1Data_GetLowBeamOn(void);
boolean AvacStat1Data_GetAvacS_Ok(void);
boolean AvacStat1Data_GetAvacS_En(void);

void AvacStat1Data_ReadPitch(tAvacStat_Pitch* pPitch);
void AvacStat1Data_ReadSpeed(tAvacStat_Speed* pSpeed);
void AvacStat1Data_ReadAslPhase(teAvacStat1_LvlPhase* psData);
void AvacStat1Data_WriteAvacOut(const tAvacStat_Out* pAvacOut);
void AvacStat1Data_WriteSpeedMode(const teAvacStat_SpeedMode* peAvacSpeedMode);

// ----------------------------------------------------------------------------
// AvacCodingData
// ----------------------------------------------------------------------------
INLINE boolean  AvacStat1Data_GetCodingValid(void)   {return true;} //AvacData_boCodingValid;}

// ----------------------------------------------------------------------------
INLINE sint16 Cod_AvacStat1_SafetyAngle(void)   { return (sint16)AVAC_SAFETY_POS; }

// ----------------------------------------------------------------------------
INLINE uint8  Cod_AvacStat1_FrozenVehSpeed(void)                { return AvacStat1_pCodingArea->AvacStp.DCMotorData.ucASL_FROZEN_VEH_SPEED; } // ASL_FROZEN_VEH_SPEED      = 2 km/h
INLINE uint8  Cod_AvacStat1_HighFrozenVehSpeed(void)            { return AvacStat1_pCodingArea->AvacStp.DCMotorData.ucASL_HIGH_FROZEN_VEH_SPEED; } // ASL_HIGH_FROZEN_VEH_SPEED = 5 km/h
INLINE uint8  Cod_AvacStat1_MaxSpeed(void)                      { return NvmBlockStatAvacPrj1Para.byMaxSpeed;  }

INLINE uint8  Cod_AvacStat1_StaticFilterCoefAtInterStop(void)   { return NvmBlockStatAvacPrj1Para.byStaticFilterCoefAtInterStop;  }
INLINE uint8  Cod_AvacStat1_StaticFilterCoefAtZeroSpeed(void)   { return NvmBlockStatAvacPrj1Para.byStaticFilterCoefAtZeroSpeed;  }
INLINE uint8  Cod_AvacStat1_StaticFilterCoefAtConstSpeed(void)  { return NvmBlockStatAvacPrj1Para.byStaticFilterCoefAtConstSpeed; }

INLINE uint8  Cod_AvacStat1_SampleTimeShort(void)               { return NvmBlockStatAvacPrj1Para.bySampleTimeShort; }
INLINE uint8  Cod_AvacStat1_SampleTimeLong(void)                { return NvmBlockStatAvacPrj1Para.bySampleTimeLong;  }

INLINE sint16 Cod_AvacStat1_TransientStatePeriod(void)          { return NvmBlockStatAvacPrj1Para.nTransientStatePeriod;  }
INLINE sint16 Cod_AvacStat1_ConstantSpeedInterval(void)         { return NvmBlockStatAvacPrj1Para.nConstantSpeedInterval; }

INLINE uint8  Cod_AvacStat1_FilterCoefInc(void)                 { return NvmBlockStatAvacPrj1Para.byFilterCoefInc;            }
INLINE uint8  Cod_AvacStat1_FilterCoefToUnlock(uint16 idx)      { return NvmBlockStatAvacPrj1Para.abyFilterCoefToUnlock[idx]; }

// ----------------------------------------------------------------------------
INLINE uint8  Cod_AvacStat1_HighDynamicLimit(void)    { return NvmBlockStatAvac1Para.byHighDynamicLimit;   }
INLINE uint8  Cod_AvacStat1_AccFilterCoeff(void)      { return NvmBlockStatAvac1Para.byAccFilterCoeff;     }
INLINE uint8  Cod_AvacStat1_PowerOnMinChange(void)    { return NvmBlockStatAvac1Para.byPowerOnMinChange;   }
INLINE uint8  Cod_AvacStat1_DynamicMinChange(void)    { return NvmBlockStatAvac1Para.byDynamicMinChange;   }
INLINE uint8  Cod_AvacStat1_InterStopMinChange(void)  { return NvmBlockStatAvac1Para.byInterStopMinChange; }
INLINE uint8  Cod_AvacStat1_StaticMinChange(void)     { return NvmBlockStatAvac1Para.byStaticMinChange;    }
INLINE sint16 Cod_AvacStat1_LoadChangeInterval(void)  { return NvmBlockStatAvac1Para.nLoadChangeInterval;  }
INLINE sint16 Cod_AvacLoadChangeInterval(void)        { return NvmBlockStatAvac1Para.nLoadChangeInterval;  }
INLINE sint16 Cod_AvacSafetyAngle(void)               { return (sint16)AVAC_SAFETY_POS; }

// ----------------------------------------------------------------------------
INLINE boolean NvmWrite_AvacStat1_StatAvacOp1Data(void)
{
  return (NvM_WriteBlock(NvmBlockStatAvacOp1DataId, (void*)&NvmBlockStatAvacOp1Data) == E_OK) ? TRUE : FALSE;
}

INLINE sint16 NvmGet_AvacStat1_HeadlightAngle(void)        { return NvmBlockStatAvacOp1Data.nHeadlightAngle; }
INLINE sint16 NvmGet_AvacStat1_SafetyAngle(void)           { return NvmBlockStatAvacOp1Data.nSafetyAngle;    }
INLINE uint16 NvmGet_AvacStat1_AdjCounter(void)            { return NvmBlockStatAvacOp1Data.unAdjCounter;    }

INLINE void   NvmSet_AvacStat1_HeadlightAngle(sint16 val)  { NvmBlockStatAvacOp1Data.nHeadlightAngle = val;                                                      }
INLINE void   NvmSet_AvacStat1_SafetyAngle(sint16 val)     { NvmBlockStatAvacOp1Data.nSafetyAngle = (val < Cod_AvacSafetyAngle()) ? val : Cod_AvacSafetyAngle(); }
INLINE void   NvmSet_AvacStat1_AdjCounter(uint16 val)      { NvmBlockStatAvacOp1Data.unAdjCounter = val;                                                         }

#endif // __AVACSTAT1DATA_H__

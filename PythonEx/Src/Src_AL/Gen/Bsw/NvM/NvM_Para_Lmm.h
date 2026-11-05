#ifndef _NVM_PARA_LMM_H_
  #define _NVM_PARA_LMM_H_

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
/// \file  NvM_Para_Lmm.h
///
/// \brief  Lmm coding data structure
///
/// \descr  
///
/// \author Alexander Kemmler (F89048A)
///         mailTo: alexander.kemmler@al-lighting.com
//-----------------------------------------------------------------------------

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/

#include <Cfg/Cfg.h>


/*******************************************************************************
* Version
*******************************************************************************/


/*******************************************************************************
* Definitions
*******************************************************************************/

/// Helper macro to parametrize a LMM cell in the same order as in the excel file
#define PARA_CELL(h,p,r,tan,taus,f,a) {h,tan,taus,p,r,f,a}

/// Helper macro to parametrize an unused LMM cell (because the LED is not used in prj)
#define PARA_CELL_LM_NOT_USED() PARA_CELL(0,15,0,0,0,FALSE,FALSE)
/*******************************************************************************
* types
*******************************************************************************/

/// Ramp types for logical lamps
typedef enum
{
  RAMP_ZK     = 0,  ///< zeitkonstant
  RAMP_SK     = 1,  ///< steigungskonstant
  RAMP_HART   = 2   ///< hart
} te_LmmRampType;

/// A cell consists of total 4 bytes
typedef struct
{
  uint8 ucIntensity;          ///< [%] Intensity
  uint8 ucTimeOn;             ///< [100 ms] Time for activation
  uint8 ucTimeOff;            ///< [100 ms] Time for deactivation
  uint8 Priority      : 4;    ///< [-] Priority (0 is highest)
  uint8 RampType      : 2;    ///< [RAMP_ZK, RAMP_SK, RAMP_HART] Time for deactivation
  uint8 ErrorImpact   : 1;    ///< 1 = switch off light function in case of a mailfunction of the logical lamp
  uint8 Active        : 1;    ///< 1 = Activate logical lamp only if it is activated already by another light function
}
tNvmPara_Lmm_LmmCell;

/// Lmm_Row
/// A single row consists of CFG_LM_Cnt Cells.
typedef struct
{
  tNvmPara_Lmm_LmmCell  cell[CFG_LM_Cnt];    ///< An index for each Logical Lamp
}
tNvmPara_Lmm_Row;

/// LmmBlock
/// Rows 0 ... CFG_LF_Cnt
typedef struct
{
  tNvmPara_Lmm_Row  row[CFG_LF_Cnt];    ///< An row for each light function
}
tNvmPara_LmmBlock;

#endif // _NVM_PARA_LMM_H_

// EOF


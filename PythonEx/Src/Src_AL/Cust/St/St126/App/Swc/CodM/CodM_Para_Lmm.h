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
///  \file   CodM_Para_Lmm.h
///
///  \brief  Content of datagroup "Lmm"
///
///  \descr  Source: PS60_R2.xlsm. 
///         
///          For further details see coding parameter
///
///  \author Cretu Vlad (F78845C)
///          mailTo:vladut-ioan.cretu[at]marelli.com
///
///  \date   22.06.2019, 14:06:20
//-----------------------------------------------------------------------------
//=============================================================================
// Includes
//=============================================================================
#ifndef __CODM_PARA__LMM_H
#define __CODM_PARA__LMM_H


#include <Cfg/Cfg.h>

//=============================================================================
// Definitions
//=============================================================================
#define CODM_PARA_LMM_WL_DrlPosChnCnt    4u   // number of channels for DRL/POS function
#define CODM_PARA_GAMMA_PTS_SIZE        17u
#define CODM_PARA_ILLUM_SIZE            CFG_LSM_LED_ILLUMINANT_NR
//=============================================================================
// Types
//=============================================================================

// Ramp types for logical lamps
enum
{
  RAMP_ZK     = 0,  ///< zeitkonstant
  RAMP_HART   = 2   ///< hart
};

// A LMM cell consists of an index into a Look-Up-Table
typedef struct
{
  // Index into Look-Up-Table [0 ... CFG_LF_LUT_Size-1]
  uint8 ucIdx;    
}
tNvmPara_Lmm_LmmCell;

// A single row consists of CFG_LM_Cnt Cells.
// Total size: CFG_LM_Cnt bytes
typedef struct
{
  // An index for each Logical Lamp
  tNvmPara_Lmm_LmmCell cell[CODM_PARA_ILLUM_SIZE];
}
tNvmPara_Lmm_Row;

//----------------------------------------------------------------------------
// Rows 0 ... CFG_LF_Cnt-1
// Size 384 byte
//----------------------------------------------------------------------------
typedef struct
{
  // 32 x 12 bytes = 384 bytes
  tNvmPara_Lmm_Row row[CFG_LF_Cnt]; 
}
tNvmPara_LmmABlock;

// ----------------------------------------------------------------------------
// Look up tables
// ----------------------------------------------------------------------------

// A cell consists of total 4 bytes
typedef struct
{
  // [%] PWM
  uint8 ucPower;
  // [100 ms] Time for activation
  uint8 ucTimeOn;
  // [100 ms] Time for deactivation
  uint8 ucTimeOff;
  // [-] Priority (0 is highest)
  uint8 biPriority : 4;
  // Reserved
  uint8 biRampType      : 2;
  // 1 = switch off light function in case of a mailfunction of the logical lamp
  uint8 biErrorImpact   : 1;  
  // 1 = Activate logical lamp only if it is activated already by another light function
  uint8 biActive        : 1;    
}
tNvmPara_Lmm_LutCell;

// The Look-Up-Table.
// Total number of bytes: CFG_LF_LUT_Size x NVM_PARA_LMM_LUT_ENTRY_SIZE.
typedef struct
{
  // The cells (40 x 4 bytes = 160 bytes)
  tNvmPara_Lmm_LutCell cell[CFG_LF_LUT_Size]; 
}
tNvmPara_LmmX_Lut;


typedef struct
{
  uint16 GAMMA_1_POINTS[CODM_PARA_GAMMA_PTS_SIZE];
                                          // 100%
  uint16 GAMMA_2_POINTS[CODM_PARA_GAMMA_PTS_SIZE];

  uint8 PXA_APPLY_RVRS_GAMMA            ; //Rev Gam = 0,  No Reverse Gamma Applied
                                          //Rev Gam = 1,  Reverse Gamma Applied
  uint8 RVRS_GAMMA_CURVE_SELECTION      ; //Value = 0, Rev_Gamma_Curve_1 selection
                                          //Value = 1, Rev_Gamma_Curve_2 selection
}
tNvmPara_LmmX_GammaCurveConfig;

typedef struct
{
  uint8 GAMMA_Curve_Config_LMs[16u];
  uint8 reserved1;
  uint8 reserved2;
}
tNvmPara_LmmX_LMGammaConfig;

typedef struct
{
  uint8 LSM_Illum_Assigned_Units_Left_LMs[16];
  uint8 reserved1;
  uint8 reserved2;
}
tNvmPara_LmmX_LMUnitConfigLeftHeadlamp;

typedef struct
{
  uint8 LSM_Illum_Assigned_Units_Right_LMs[16];
  uint8 reserved1;
  uint8 reserved2;
}
tNvmPara_LmmX_LMUnitConfigRightHeadlamp;


typedef struct
{
  uint16 REVERSEGAMMA_PXA_X1[CODM_PARA_GAMMA_PTS_SIZE];
  uint16 REVERSEGAMMA_PXA_X2[CODM_PARA_GAMMA_PTS_SIZE];
}
tNvmPara_LmmX_RvrsGammaPxa_XPts;

typedef struct
{
  uint16 REVERSEGAMMA_PXA_Y1[CODM_PARA_GAMMA_PTS_SIZE];
  uint16 REVERSEGAMMA_PXA_Y2[CODM_PARA_GAMMA_PTS_SIZE];
}
tNvmPara_LmmX_RvrsGammaPxa_Ypts;


typedef struct
{
  uint8 reserviert1[16];
}
tNvmPara_LmmX_Reserved;

//----------------------------------------------------------------------------
// The X block contains additional information for a LMM (like Look-Up-Tables).
// Total size: 182 Bytes
// ----------------------------------------------------------------------------
typedef struct
{
  tNvmPara_LmmX_Lut                       Lut;
  tNvmPara_LmmX_GammaCurveConfig          GammaCurveConfig;
  tNvmPara_LmmX_LMGammaConfig             LMGammaConfig;
  tNvmPara_LmmX_LMUnitConfigLeftHeadlamp  LMUnitConfigLeftHeadlamp;
  tNvmPara_LmmX_LMUnitConfigRightHeadlamp LMUnitConfigRightHeadlamp;
  tNvmPara_LmmX_RvrsGammaPxa_XPts         RvrsGammaPxa_XPts;
  tNvmPara_LmmX_RvrsGammaPxa_Ypts         RvrsGammaPxa_Ypts;
  tNvmPara_LmmX_Reserved                  Reserved;
}                                                // -----------
tNvmPara_LmmXBlock;                              // 266 bytes

#endif /*  __CODM_PARA__LMM_H */

// EOF

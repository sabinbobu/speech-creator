#ifndef __ADBPXA3RTEACCESS_H__
#define __ADBPXA3RTEACCESS_H__

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
/// \file  AdbMxb2Data.h
///
/// \brief  
///
/// \descr  
///
///         Additional information can be found in the design description (Link:
///        
/// \author Tanase Alexandru  (F58375C)
///         mailTo: alexandru-anton.tanase[at]marelli.com
//-----------------------------------------------------------------------------


#include <Bsw/Common/Std_Types.h>
#include "AdbPxa3Types.h"


//extern taucLigthDistrubution *paucAnimationDistribution;

// ----------------------------------------------------------------------------
// Local Types
// ----------------------------------------------------------------------------

typedef enum tieAdbPxaMode_HbState_tag {
  eIndeterminate = 0,
  eNoFault = 1,
  eFault = 2,
  eNotUsed = 3
} tieAdbPxaMode_HbState;



// ----------------------------------------------------------------------------
// Function prototypes
// ----------------------------------------------------------------------------

Std_ReturnType AdbPxa3_Rte_Read_HeadlampSide(tieAdbHeadlampSide* pSideTL);
Std_ReturnType AdbPxa3_Rte_Read_PxaMode(tieAdbPxaMode* pPxaModeTL);
Std_ReturnType AdbPxa3_Rte_Read_LightDist(tieAdbLightDist84Pxl* pLightDistTL);
Std_ReturnType AdbPxa3_Rte_Read_DblPos(tAdbAngleTL_deg* pDblPosTL);
//Std_ReturnType AdbPxa3_Rte_Read_CodM_Calibration_Type(uint8* Calibration_Type);
Std_ReturnType AdbPxa3_Rte_Read_AfsLgtFctMgr_Animation_IntensityMatrix(void);
Std_ReturnType AdbPxa3_Rte_Read_AdbChannel01(tAdbChannelTL* pChannelTL);
Std_ReturnType AdbPxa3_Rte_Read_AdbChannel02(tAdbChannelTL* pChannelTL);
Std_ReturnType AdbPxa3_Rte_Read_AdbChannel03(tAdbChannelTL* pChannelTL);
Std_ReturnType AdbPxa3_Rte_Read_AdbChannel04(tAdbChannelTL* pChannelTL);
Std_ReturnType AdbPxa3_Rte_Read_AdbChannel05(tAdbChannelTL* pChannelTL);
void AdbPxa3_Rte_Read_CameraAvailability(boolean* boStatusPercep);
void AdbPxa3_Rte_Read_MXBStatus(boolean* HBBstatus, boolean* CurtainStatus);


Std_ReturnType AdbPxa3_Rte_Write_ActualLedIntensities(tAdbestingtAdbIntensityTL_pct ActLedIntensitiesTL[3][30]);

//void AdbPxa3_Rte_Write_SigPrep_HbStatus(boolean boStatus);

//void AdbPxa3_Rte_Write_SigPrep_HbErrStatus(tieAdbPxaMode_HbState eHbState);

//boolean AdbPxa3_Rte_Read_MatrixErrorState(void);

//boolean AdbPxa3_Rte_Read_SignalAvailability(void);

void AdbPxa3_Rte_Read_FTPStatus(boolean* boFTPStatus);

//void AdbPxa3_Rte_Read_CmdMxbStatus(boolean* boCmdMxbStatus);


#endif // __ADBPXA3RTEACCESS_H__

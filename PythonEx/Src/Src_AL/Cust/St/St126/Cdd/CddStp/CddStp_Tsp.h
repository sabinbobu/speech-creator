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
/// \file  CddStp_Tsp.h
///
/// \brief
///
//-----------------------------------------------------------------------------
#ifndef CDD_STP_TSP_2020_03_05_H_
#define CDD_STP_TSP_2020_03_05_H_

#include <Std_Types.h>

// in Daisy-Chain:
//    LWR = 0  -  AHL = 1  -  LLR = 2
#define CDDSTP_STEP_LWR    0U
#define CDDSTP_STEP_AHL    1U
#define CDDSTP_STEP_LLR    2U

void   CddStp_Tsp_Init(void);
void   CddStp_Tsp_Start(   uint8 ucIdx, uint32 period);

void CddStp_Tsp_StartHelpTimer(uint8 ucIdx, uint32 period);
void CddStp_Tsp_ResetFlag(uint8 ucIdx);
void CddStp_Tsp_Stop(uint8 ucIdx);
void CddStp_Tsp_StopHelpTmr(uint8 ucIdx);

uint32 CddStp_Tsp_GetTicks(uint8 ucIdx);


#endif // CDD_STP_TSP_2020_03_05_H_

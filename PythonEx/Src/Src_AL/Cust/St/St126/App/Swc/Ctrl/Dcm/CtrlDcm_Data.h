//*****************************************************************************
// (C) Marelli Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Marelli Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Marelli Automotive Lighting Reutlingen GmbH.
//*****************************************************************************
//-----------------------------------------------------------------------------
/// \file  CtrlDcm_Data.h
///
/// \brief
///
//-----------------------------------------------------------------------------
#ifndef CTRL_DCM_DATA_2022_06_23_H
#define CTRL_DCM_DATA_2022_06_23_H

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

#ifndef UNIT_TEST
#include <Rte.h>
#endif // !UNIT_TEST
#include <Std_Types.h>
#include <AL_Helper.h>
#include <../Swc/Ctrl/Dcm/Api/CtrlDcm.h>
#include <CodM_Para_AvacStp.h>

#ifdef UNIT_TEST
#include <RteCommonTypes.h> 
#endif //UNIT_TEST


//=============================================================================
// Types
//=============================================================================


//-----------------------------------------------------------------------------
// proptotypes
//-----------------------------------------------------------------------------
boolean CtrlDcm_CodingDataReady(teCtrlDcm_MountingSide* pMountingSide);
void CtrlDcm_ParaFct0(tParaFct0_Cmd eCmd,tNvmPara_CodingArea* pData);

sint8   Cod_DcmMinVehAtt        (void);
sint8   Cod_DcmMaxVehAtt        (void);
sint16  Cod_DcmMinAdjASL        (void);
sint16  Cod_DcmMaxAdjASL        (void);
sint16  Cod_DcmSp               (void);
uint8   Cod_DcmVehAttThrStill   (void);
uint8   Cod_DcmFrozenVehSpeedASL(void);
boolean Cod_DcmEnable           (void);
uint8   Cod_DcmVehAttThrMotion  (void);
uint8   Cod_DcmMotionDelayASL   (void);

#endif // CTRL_DCM_DATA_2022_06_23_H

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
// \file   CddDcm.h
//
// \brief  Interface header for DC motor driver
//
// \descr  DC motor driver
//
// \author Braun, Martin ALRT/EEG-CA (bnm2rt)
//         Paland, Marco ALRT/EEG-PM2 (pm88rt)
//         mailto:marco.paland@external.al-lighting.com
//-----------------------------------------------------------------------------

#ifndef _CDDDCM_H_
#define _CDDDCM_H_

//#include <Cfg.h>
#include "ILCU_LevellingAdapter.h" /* ILCU_PORT: replaces DPE-only <Bsw/NvM/NvM_Para.h> */
//#include <Nvm.h>


extern tDcMotorDataStruct           NvmInit_ParaDcMotorDataDefault;
extern tDcMotorCharacteristicStruct NvmInit_ParaDcMotorCharacteristicDefault;

//#if (CFG_TYP_DCM != CFG_Dcm_None)



//#endif // (CFG_TYP_DCM == CFG_Dcm_None)

#endif // _CDDDCM_H_


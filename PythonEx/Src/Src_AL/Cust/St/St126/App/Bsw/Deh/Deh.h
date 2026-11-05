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
/// \file  Deh.h
///
/// \brief  DEH handling
///
/// \descr  
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef __DEH_H__
#define __DEH_H__

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <RteCommonTypes.h>
#include <Bsw/Nvm/NvM_Para.h>

#define ECU_ABS_INIT        0xFFu

//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------
#ifndef NmBackupCountersINIT
#define NmBackupCountersINIT \
    { 0u, 0u, 0u , ECU_ABS_INIT}
#endif

//=============================================================================
// init data for Nvm-Parameter
//=============================================================================
extern const tisNmBackupCounters  NvmInit_NmBackupCountersDefault;


//-----------------------------------------------------------------------------
// typedefs
//-----------------------------------------------------------------------------
typedef enum
{
  eDeh_Undef = 0,
  eDeh_Apeared = 1,
  eDeh_ApearedConf = 2,
  eDeh_Disapeared = 3,
  eDeh_DisapearedConf = 4,
  eDeh_DisapearedConf_LGM = 5,
  eDeh_Init = 6,
  eDeh_ApearedConf_DirectSent = 7
}teDeh_EventState;


typedef struct
{
  uint16 unDemEvent;
  uint32 ulDTCCode;
  uint8 ucDemEvntCnt_Apeared;
  uint8 ucDemEvntCnt_Disapeared;
  teDeh_EventState eEventState;
}tsDeh_EventLog;

//-----------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------
// Initialization of the Deh module
void  Deh_Init(void);
// Deh Cyclic function
void  Deh_Cycle0(void);
// Callback functions for Detection/Confirmation of DEH Appearance/Disappearance
void  Deh_AppearanceDetected(uint16 unEventId);
void  Deh_AppearanceConfirmed(uint16 unEventId);
void  Deh_DisappearanceDetected(uint16 unEventId);
void  Deh_DisappearanceConfirmed(uint16 unEventId);
void  Deh_ClearAndInitDehLogTab(void);


#endif // __DEH_H__


// EOF

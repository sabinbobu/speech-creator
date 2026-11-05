#ifndef __CODM_PARA_ANIMATION_H__
#define __CODM_PARA_ANIMATION_H__


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
///  \file   CodM_Para_Animation.h
///
///  \brief  Content of datagroup "Animation"
///
///  \descr  Source: PS60_R2.xlsm. 
///          Version TBD 
///          For further details see coding parameter
///
///  \author This file is auto generated - please do not edit
///
///  \date   11.05.2020, 09:41:16
//-----------------------------------------------------------------------------
//=============================================================================
// Includes
//=============================================================================

//=============================================================================
// Definitions
//=============================================================================
#if defined (CFG_VARIANT_FULL) || (UNIT_TEST)
#define CODM_PARA_ANIM_BYTESTREAM_SIZE          8052u
#else
#define CODM_PARA_ANIM_BYTESTREAM_SIZE          3072u
#endif
#define CODM_PARA_RESERVED_SIZE                     3u
#define CODM_PARA_ANIM_MAPPING_SIZE             103u
//=============================================================================
// Types
//=============================================================================


typedef struct
{
  uint8 aucByteStream[CODM_PARA_ANIM_BYTESTREAM_SIZE];
}
tNvmPara_Animation_AnimationByteStream;

typedef struct
{
  uint16 unDELAY_TRANSITION_ANIMATION;
  uint16 unAUTO_RELOCK_DELAY;
  uint16 unWELCOME_ANIMATION_DELAY;
  uint16 unUNLOCK_ANIMATION_DELAY;
  uint16 unUNLOCK_EXTENSION_ANIMATION_DELAY;
  uint16 unBYEBYE_ANIMATION_DELAY;
  uint16 unLOCK_DAY_ANIMATION_DELAY;
  uint16 unLOCK_NIGHT_ANIMATION_DELAY;
  uint16 unLOCK_EXTENSION_ANIMATION_DELAY;
  uint16 unEND_BYEBYE_ANIMATION_DELAY;
  uint16 unLOCALIZATION_ANIMATION_DELAY;
  uint16 unREMOTE_LIGHT_ANIMATION_DELAY;
  uint16 unSHOWROOM_EVENT_ANIMATION_DELAY;
  uint16 unreserviert1[CODM_PARA_RESERVED_SIZE];
}
tNvmPara_Animation_AnimationsDelay;

typedef struct
{
  uint8 ucAnimaUnitMapping[CODM_PARA_ANIM_MAPPING_SIZE];
}
tNvmPara_Animation_AnimationsMapping;

typedef struct
{
  uint8 reserviert1[15];
}
tNvmPara_Animation_Reserved;

typedef struct
{
  tNvmPara_Animation_AnimationByteStream AnimationByteStream;
  tNvmPara_Animation_AnimationsDelay     AnimationsDelay;
  tNvmPara_Animation_AnimationsMapping   AnimationsMapping;
  tNvmPara_Animation_Reserved            Reserved;
} tNvmPara_AnimationBlock;

#endif // __CODM_PARA_ANIMATION_H__

// EOF

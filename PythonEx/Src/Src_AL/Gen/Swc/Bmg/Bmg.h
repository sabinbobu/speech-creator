#ifndef __BMG_H__
  #define __BMG_H__

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
/// \file  Bmg.h
///
/// \brief  Functions for AL- specific initialization:
///             - mounting side LEDFT /RIGHT
///
/// \descr  
///
/// \author Cosmin Cojocaru (f11501c)
///         mailTo:constantin-cosmin.cojocaru(at)marelli.com
//-----------------------------------------------------------------------------

#include <Swc/Bmg/BmgCfg.h>

#ifdef __cplusplus
extern "C" {
#endif

  void Bmg_BootStatus_detection(void);
  

#ifdef BMG_DETECT_VBAT_LEVEL
  boolean Bmg_BootStatus_isVbatValid(void);
#endif
#ifdef BMG_DETECT_MOUNTING_SIDE
  boolean Bmg_BootStatus_isMountingSideLeft(void);
  boolean Bmg_BootStatus_isMountingSideRight(void);
#endif

#ifdef BMG_DETECT_ENTRY_CONDITION
  boolean Bmg_BootStatus_waitForRAMAppl(void);
#endif

#ifdef BMG_DETECT_HW_ID
  uint8 Bmg_BootStatus_getHwID(void);
#endif

#ifdef __cplusplus
}
#endif

#endif // __BMG_H__

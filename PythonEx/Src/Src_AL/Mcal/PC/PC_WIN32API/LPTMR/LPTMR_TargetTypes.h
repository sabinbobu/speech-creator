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
/// \file  LPTMR_TargetTypes.h
///
/// \brief
///
//-----------------------------------------------------------------------------
#ifndef LPTMR_TARGET_TYPES_2021_04_13_H_
#define LPTMR_TARGET_TYPES_2021_04_13_H_

  #include <Std_Types.h>
  #include <Cfg/Cfg.h>
 
  #if defined(__cplusplus)
  extern "C"
  {
  #endif
    
  #define INST_LPTMR_1  (0U)


  typedef struct LPTMR_SpecificType
  {
    uint8 ucCountOfLPTMRInstances;
    void* lptmr_cfg;
  } LPTMR_SpecificType;

  #if defined(__cplusplus)
  }
  #endif

#endif // LPTMR_TARGET_TYPES_2021_04_13_H_

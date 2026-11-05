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
/// \file  SysCrc.h
///
/// \brief
///
//-----------------------------------------------------------------------------
#ifndef SYS_CRC_2021_06_25_H_
  #define SYS_CRC_2021_06_25_H_

  //=============================================================================
  // Includes
  //=============================================================================
  #include <SysCrc_TargetTypes.h>
  #include <AL_Helper.h>
  #include <Std_Types.h>
  
  //=============================================================================
  // Types
  //=============================================================================
  typedef SysCrc_SpecificType SysCrc_ConfigType;
  
  //=============================================================================
  // Exported types
  //=============================================================================
  
  //=============================================================================
  // Exported Variables
  //=============================================================================
  extern const SysCrc_SpecificType SysCrc_Config;
  
  //=============================================================================
  // Exported functions prototype
  //=============================================================================
  void    SysCrc_RomSegs_Init(const SysCrc_ConfigType* ConfigPtr);
  void    SysCrc_RomSegs_DoCRC(void);
  void    SysCrc_RomSegs_SegmentCrcCheck(teSysCrc_SegmentId eSegId);
  boolean SysCrc_RomSegs_GetCalibCrcStatus(void);
  void    SysCrc_RomSegs_RomSegCalCbStatus(void);
  void    SysCrc_RomSegs_GetCalibState(tsSysCrc_CalibGetStatus *psCalibState);


#endif // SYS_CRC_2021_06_25_H_

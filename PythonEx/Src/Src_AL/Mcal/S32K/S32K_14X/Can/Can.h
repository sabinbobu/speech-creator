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
/// \file   Can.h
///
/// \brief  Public interface of Can
///
/// \descr  CAN driver
///
/// \author Ramona-Andreea Bolboaca (f33613c)
///         mailTo:ramona-andreea.bolboaca(at)magnetimarelli.com
//-----------------------------------------------------------------------------

#ifndef __CAN_H_2019_05_17__
  #define __CAN_H_2019_05_17__

  //=============================================================================
  // Includes
  //=============================================================================
  #include <Can_Cfg.h>


  extern const Can_SpecificType Can_Config;

  //=============================================================================
  // Public functions declaration
  //=============================================================================
  void Can_Init(const Can_SpecificType* Can_Config);
  void Can_Enable(uint8 channel);
  //void Can_Disable(uint8 channel);
  //void Can_ChangeSpeed(const uint32 new_speed);
  boolean Can_SendMsg(const uint8* data, uint32 size);
  void Can_Cycle(void);
  void Can_Cycle_SetDownloadIsInProgress(boolean value);


#endif // __CAN_H_2019_05_17__

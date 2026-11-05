#ifndef __CAN_CFG_H_2020_10_29__
  #define __CAN_CFG_H_2020_10_29__
//*****************************************************************************
// (C) Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Automotive Lighting Reutlingen GmbH.
//*****************************************************************************

///----------------------------------------------------------------------------
/// \file   Can_Cfg.h
///
/// \brief  X-Macros
///
/// \descr  X-Macros for building the CAN message maps tables
///
/// \author Ramona-Andreea Bolboaca (f33613c)
///         mailTo:ramona-andreea.bolboaca(at)magnetimarelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// Includes
//=============================================================================
#include <Std_Types.h>

#define CAN_RX_MAILBOX  (0UL)
#define CAN_RX_MSG_ID   (0x6F1U)

#define RX_BUFF_0 0x00U
#define RX_BUFF_1 0x01U

#define CAN_TX_MAILBOX 0x01U
#define CAN_TX_MSG_ID  0x643UL

typedef struct Can_Cfg_atyCharacteristicsConfig
{
  void* ptyInstType;
  void* ptyUsrCfgType;
} Can_Cfg_atyCharacteristicsConfig;

typedef struct Can_SpecificType
{
  uint8 ucCountOfCanInstances;
  const Can_Cfg_atyCharacteristicsConfig* Can_Cfg_atyCharacteristics;
} Can_SpecificType;

#endif //__CAN_CFG_H_2020_10_29__
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
/// \brief  Can transmit, receive and clock map configuration
///
/// \descr  Can transmit, receive and clock map configuration
///
///
/// \author Ramona-Andreea Bolboaca (f33613c)
///         mailTo:ramona-andreea.bolboaca(at)magnetimarelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// Includes
//=============================================================================

#include <Can.h>
#include <UtilUtility.h>
#include <can_pal.h>

can_instance_t can_instance_1 = {
  CAN_INST_TYPE_FLEXCAN, 0U
};

can_user_config_t can_user_config_1 = {
  /* max buff,  mode,            clock source,       enableFD, payload_size*/ 
     2U,        CAN_NORMAL_MODE, CAN_CLK_SOURCE_OSC, FALSE,     CAN_PAYLOAD_SIZE_8, 
    /* nominal bitrate */
    {7U, 4U, 1U, 1U, 1U}, 
    /*data bitrate*/
    {7U, 4U, 1U, 1U, 1U}, 
  /* extension */
  NULL_PTR
};

const Can_Cfg_atyCharacteristicsConfig Can_Cfg_atyCharacteristics[1U] =
{
  /* CAN instance,                   CAN user config */
  {(can_instance_t*)&can_instance_1, (can_user_config_t*)&can_user_config_1},
};

const Can_SpecificType Can_Config =
{
  UTIL_COUNTOF(Can_Cfg_atyCharacteristics),
  &Can_Cfg_atyCharacteristics[0U]
};

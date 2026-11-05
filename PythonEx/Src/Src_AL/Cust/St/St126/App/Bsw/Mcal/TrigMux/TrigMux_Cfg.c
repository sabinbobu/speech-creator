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
/// \file  TrigMux_Cfg.c
///
/// \brief Project related TrigMux configuration
///
/// \author Stefan Tyirean (f75617c)
///         mailto: stefan.tyirean[at]marelli.com
///
/// \Date April 2021
///
//-----------------------------------------------------------------------------

#include <TrigMux.h>
#include <UtilUtility.h>
#include <Std_Types.h>

// TrigMux Instances Configuration
STATIC_AL CONST_AL tsTrigMux_TrigMuxCfg TrigMux_asTrgMuxCfg[] = 
{
  /*TrigMux Inst,         Trigger Source,                    Trigger Traget,                 Lock Bit*/
  {     0u,         eTRGMUX_TRIG_SOURCE_LPIT_CH3,   eTRGMUX_TARGET_MODULE_PDB0_TRG_IN,        FALSE},
  {     0u,         eTRGMUX_TRIG_SOURCE_LPIT_CH3,   eTRGMUX_TARGET_MODULE_PDB1_TRG_IN,        FALSE}
};

// Extern data configuration passed to TrigMux Init function
const tsTrigMux_CfgData TrigMux_sTrigMuxDatatCfg =
{
  /*     Config array,                count*/
  { &TrigMux_asTrgMuxCfg[0], countof(TrigMux_asTrgMuxCfg) }
};

// EOF

#ifndef __HAL_DCM_ALT1_H__
#define __HAL_DCM_ALT1_H__

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
/// \file   CddDcmHal.h (HalDcmAlt1.h)
///
/// \brief  Interface Header file for the HalDcmAlt1 module.
///
/// \descr  Alternative1 Dc-motor driver with controlling the Dc-motor output
///         voltage by reading back the output voltage.
///         Additional information can be found in the design description (Link:
///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
///
/// \author Heusel Johannes ALRT/EEG-PM2 (F89037A)
///         mailTo:johannes.heusel@al-lighting.com
///         Hempelmann Bernd ALRT/EEG (he82rt)
///         mailTo: bernd.hempelmann@external.al-lighting.com
//-----------------------------------------------------------------------------


//=============================================================================
// includes
//=============================================================================

#include <Std_Types.h>
#include "ILCU_LevellingAdapter.h" /* ILCU_PORT: replaces DPE-only <Cfg/Cfg.h> */

//#if ( (CFG_DRV_DCM != CFG_Drv_None))

  //=============================================================================
  // preprocessor definitions
  //=============================================================================

  // Return codes of the HalDcm_GetVoltageState() functions
  #define HALDCM_LEVEL_UNKNOWN         0u
  #define HALDCM_LEVEL_OK              1u
  #define HALDCM_LEVEL_LOW             2u
  #define HALDCM_LEVEL_HIGH            3u

  #define CDDDCM_PWM_CHANNEL_MAP_DC_MOTOR 5u

  #define CDDDCM_SUBCYCLE                 4u 

  // Setting numbers of Dc-motor channels and assign the channel number outputs.
  // Both Dc-Motor channels exist

  #define min(a,b)  (((a)<(b)) ? (a) : (b))
  #define max(a,b)  (((a)>(b)) ? (a) : (b))

  //=============================================================================
  // function prototypes
  //=============================================================================

  void  CddDcmHal_Init(void);
  void  CddDcmHal_IrqHookOutputPwm(void);

  void  CddDcmHal_SetOutpLevelChannel(uint16 unOutputLevel);
  void  CddDcmHal_EnableChannel(const boolean boState);
  void  CddDcmHal_DisableAndPwmOffChannel(void);

  void  CddDcmHal_ResetVoltageState(void);
  uint8 CddDcmHal_GetVoltageState(void);

  //=============================================================================
  // inline functions
  //=============================================================================


#endif // __HAL_DCM_ALT1_H__

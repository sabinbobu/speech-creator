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
/// \file  Lpit.c
///
/// \brief Mcal Lpit interfaces/runnables definitions
///
/// \author Stefan Tyirean (f75617c)
///         mailto: stefan.tyirean[at]marelli.com
///
/// \Date April 2021
///
//-----------------------------------------------------------------------------

//====================================================================
// Include files
//===================================================================

#include <Lpit.h>
#include "Lpit_Drv.h"
#include "Lpit_TargetTypes.h"

//====================================================================
// Global function definitions
//====================================================================

//-----------------------------------------------------------------------------
/// \brief Lpit_Init
///
/// \descr Low Power Interrupt Timer init based on input configuration
///
/// \param  psLpitCfgIn - Lpit input configuration
///
/// \return void
//-----------------------------------------------------------------------------
void Lpit_Init(CONST_AL tsLpit_CfgData * CONST_AL psLpitCfgIn)
{
  // Check input config parameter
  if (psLpitCfgIn != NULL_PTR)
  {
    // Call local Lpit init function
    (void)Lpit_Drv_Init(psLpitCfgIn);
  }
  else
  {
    // NULL_PTR, Lpit configuration shall be avoided
  }

}

//-----------------------------------------------------------------------------
/// \brief Lpit_LpitSetTmrEnblBit
///
/// \descr Interface to Low Level function <Lpit_Drv_LpitSetTmrEnblBit>
///
/// \param  psLpitTmr - LPIT Timer config data
/// \param  ulEnblBit - Enable Bit
///
/// \return void
//-----------------------------------------------------------------------------
void Lpit_LpitSetTmrEnblBit(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, uint32 ulEnblBit)
{
  Lpit_Drv_LpitSetTmrEnblBit(psLpitTmr, ulEnblBit);
}

//-----------------------------------------------------------------------------
/// \brief Lpit_LpitSetTmrChCompVal
///
/// \descr Interface to Low Level function <Lpit_Drv_LpitSetTmrChCompVal>
///
/// \param  psLpitTmr - LPIT Timer config data
/// \param  ulCompVal - Compare Value
///
/// \return void
//-----------------------------------------------------------------------------
void Lpit_LpitSetTmrChCompVal(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, uint32 ulCompVal)
{
  Lpit_Drv_LpitSetTmrChCompVal(psLpitTmr, ulCompVal);
}

//-----------------------------------------------------------------------------
/// \brief Lpit_LpitSetTmrChIntEnbl
///
/// \descr Interface to Low Level function <Lpit_Drv_LpitSetTmrChIntEnbl>
///
/// \param  psLpitTmr - LPIT Timer config data
/// \param  ulIntEnbl - Interupt Enable Bit
///
/// \return void
//-----------------------------------------------------------------------------
void Lpit_LpitSetTmrChIntEnbl(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, uint32 ulIntEnbl)
{
  Lpit_Drv_LpitSetTmrChIntEnbl(psLpitTmr, ulIntEnbl);
}

//-----------------------------------------------------------------------------
/// \brief Lpit_LpitReturnCount
///
/// \descr Interface to Low Level function <Lpit_Drv_LpitReturnCount>
///
/// \param  psLpitTmr - LPIT Timer config data
///
/// \return uint32 - Counter register value
//-----------------------------------------------------------------------------
uint32 Lpit_LpitReturnCount(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr)
{
  uint32 ulRetFct = Lpit_Drv_LpitReturnCount(psLpitTmr);

  return ulRetFct;
}

//-----------------------------------------------------------------------------
/// \brief Lpit_LpitClearTimeout
///
/// \descr Interface to Low Level function <Lpit_Drv_LpitClearTimeout>
///
/// \param  psLpitTmr - LPIT Timer config data
///
/// \return void
//-----------------------------------------------------------------------------
void Lpit_LpitClearTimeout(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr)
{
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
/// \file  Lpit.c
///
/// \brief Mcal Lpit interfaces/runnables definitions
///
/// \author Stefan Tyirean (f75617c)
///         mailto: stefan.tyirean[at]marelli.com
///
/// \Date April 2021
///
//-----------------------------------------------------------------------------

//====================================================================
// Include files
//===================================================================

#include <Lpit.h>
#include "Lpit_Drv.h"
#include "Lpit_TargetTypes.h"

//====================================================================
// Global function definitions
//====================================================================

//-----------------------------------------------------------------------------
/// \brief Lpit_Init
///
/// \descr Low Power Interrupt Timer init based on input configuration
///
/// \param  psLpitCfgIn - Lpit input configuration
///
/// \return void
//-----------------------------------------------------------------------------
  void Lpit_Init(CONST_AL tsLpit_CfgData * CONST_AL psLpitCfgIn)
  {
    return;
  }

  //-----------------------------------------------------------------------------
  /// \brief Lpit_LpitSetTmrEnblBit
  ///
  /// \descr Interface to Low Level function <Lpit_Drv_LpitSetTmrEnblBit>
  ///
  /// \param  psLpitTmr - LPIT Timer config data
  /// \param  ulEnblBit - Enable Bit
  ///
  /// \return void
  //-----------------------------------------------------------------------------
  void Lpit_LpitSetTmrEnblBit(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, uint32 ulEnblBit)
  {
    return;
  }

  //-----------------------------------------------------------------------------
  /// \brief Lpit_LpitSetTmrChCompVal
  ///
  /// \descr Interface to Low Level function <Lpit_Drv_LpitSetTmrChCompVal>
  ///
  /// \param  psLpitTmr - LPIT Timer config data
  /// \param  ulCompVal - Compare Value
  ///
  /// \return void
  //-----------------------------------------------------------------------------
  void Lpit_LpitSetTmrChCompVal(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, uint32 ulCompVal)
  {
    return;
  }

  //-----------------------------------------------------------------------------
  /// \brief Lpit_LpitSetTmrChIntEnbl
  ///
  /// \descr Interface to Low Level function <Lpit_Drv_LpitSetTmrChIntEnbl>
  ///
  /// \param  psLpitTmr - LPIT Timer config data
  /// \param  ulIntEnbl - Interupt Enable Bit
  ///
  /// \return void
  //-----------------------------------------------------------------------------
  void Lpit_LpitSetTmrChIntEnbl(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, uint32 ulIntEnbl)
  {
    return;
  }

  //-----------------------------------------------------------------------------
  /// \brief Lpit_LpitReturnCount
  ///
  /// \descr Interface to Low Level function <Lpit_Drv_LpitReturnCount>
  ///
  /// \param  psLpitTmr - LPIT Timer config data
  ///
  /// \return uint32 - Counter register value
  //-----------------------------------------------------------------------------
  uint32 Lpit_LpitReturnCount(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr)
  {
    return;
  }

  //-----------------------------------------------------------------------------
  /// \brief Lpit_LpitClearTimeout
  ///
  /// \descr Interface to Low Level function <Lpit_Drv_LpitClearTimeout>
  ///
  /// \param  psLpitTmr - LPIT Timer config data
  ///
  /// \return void
  //-----------------------------------------------------------------------------
  void Lpit_LpitClearTimeout(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr)
  {
    return;
  }

  // EOF

}

// EOF

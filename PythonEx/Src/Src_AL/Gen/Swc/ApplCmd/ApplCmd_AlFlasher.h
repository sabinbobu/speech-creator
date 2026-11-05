#ifndef APPLCMD_ALFLASHER_H_
#define APPLCMD_ALFLASHER_H_

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
/// \file  ApplCmd_AlFlasher.h
///
/// \brief  
///
/// \descr  
///
///         Additional information can be found in the design description (Link:
///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
///
/// \author Heusel Johannes ALRT/EEG-PM2 (F89037A)
///         mailTo:johannes.heusel(at)al-lighting.com
//-----------------------------------------------------------------------------

//=============================================================================
// Includes
//=============================================================================

#include <Std_Types.h>


//=============================================================================
// Public Variables
//=============================================================================

uint32 ApplCmd_AlFlasher_Crc32_Vector_AUTOSAR(const uint8*  Crc_DataPtr,
  uint32  Crc_Length,
  uint32  Crc_StartValue32,
  boolean Crc_IsFirstCall);

extern boolean boLoginActivated;

#endif // APPLCMD_ALFLASHER_H_

#ifndef __APPL_CMD_H__
#define __APPL_CMD_H__

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
/// \file  ApplCmd.h
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
// Public functions declaration
//=============================================================================
  
//uint8  AppCmd_Execute(uint8 cmdID,  MsgContextType *const pMsgContext );
uint8  AppCmd_Execute(uint8_t cmdID, uint8_t cmdList,  MsgContextType *const pMsgContext );

#endif // __APPL_CMD_H__

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
/// \file  ApplCmd.c
///
/// \brief
///
/// \descr
///
///         Additional information can be found in the design description (Link:
///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
///
/// \author Heusel Johannes ALDE-RT/EEG-PM2 (F89037A)
///         mailTo:johannes.heusel(at)al-lighting.com
//-----------------------------------------------------------------------------

//=============================================================================
// Includes
//=============================================================================

#include <Swc/ApplCmd/ApplCmd_AlFlasher.h>
#include <Bsw/Com/ComBuf/ComBuf.h>
#include <Swc/ApplCmd/ApplCmd.h>
#include <Swc/ApplCmd/ApplCmdTcb.h>


//=============================================================================
// function prototyping used in ApplCmdCfg.h
//=============================================================================
#define APPLCMD_MAC_DECL_FCT
//lint -e451 Header file repeatedly included but does not have a standard include guard
#include <Swc/ApplCmd/ApplCmdCfg.h>
//lint +e451 Header file repeatedly included but does not have a standard include guard
#undef  APPLCMD_MAC_DECL_FCT


//=============================================================================
// Generate Command list over X-Macro  
//=============================================================================

#define MAC_APPLCMD_LIST_ID
//lint -e451 Header file repeatedly included but does not have a standard include guard
#include <Swc/ApplCmd/ApplCmdCfg.h>
//lint +e451 Header file repeatedly included but does not have a standard include guard
#undef  MAC_APPLCMD_LIST_ID

#define MAC_APPLCMD_LEVEL_ENUM
//lint -e451 Header file repeatedly included but does not have a standard include guard
#include <Swc/ApplCmd/ApplCmdCfg.h>
//lint +e451 Header file repeatedly included but does not have a standard include guard
#undef  MAC_APPLCMD_LEVEL_ENUM

#define MAC_APPLCMD_LIST_CALLBACK
//lint -e451 Header file repeatedly included but does not have a standard include guard
#include <Swc/ApplCmd/ApplCmdCfg.h>
//lint +e451 Header file repeatedly included but does not have a standard include guard
#undef  MAC_APPLCMD_LIST_CALLBACK

#define MAC_APPLCMD_LEVEL_LIST
//lint -e451 Header file repeatedly included but does not have a standard include guard
#include <Swc/ApplCmd/ApplCmdCfg.h>
//lint +e451 Header file repeatedly included but does not have a standard include guard
#undef  MAC_APPLCMD_LEVEL_LIST

#define MAC_APPLCMD_LEVEL_RANGE_LIST
//lint -e451 Header file repeatedly included but does not have a standard include guard
#include <Swc/ApplCmd/ApplCmdCfg.h>
//lint +e451 Header file repeatedly included but does not have a standard include guard
#undef  MAC_APPLCMD_LEVEL_RANGE_LIST


//=============================================================================
// Variable declaration intern 
//=============================================================================
boolean boLoginActivated = FALSE;

//=============================================================================
// Public functions definition
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  Dummy function to switch to next cmd table
///
/// \descr  will not be accessed just to keep compilation of xmacro silent
///
/// \param  pMsgContext 
///
/// \return uint8 
//-----------------------------------------------------------------------------
uint8  ApplCmd_Change_Level( MsgContextType *const pMsgContext )
{
  // PRQA S 3112 1 // parameter not used at the moment
  (void) pMsgContext;

  return 0U;
}

//-----------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  cmdID 
/// \param  pMsgContext 
///
/// \return uint8 
//-----------------------------------------------------------------------------
// PRQA S 5336 L_STMIF // Program architecture and readability
uint8 AppCmd_Execute(uint8_t cmdID, uint8_t cmdList,  MsgContextType *const pMsgContext)
{
  static uint16_t  cmdLevelCounter = 0U;

  uint8 ResponseCode = 0x11u ;/*service not supported*/
  uint16 Idx; 
  uint16 IdxMax =  Cmd_LevelRange[cmdList];
  tApplCmd *usedLevel = fctCmd_Level[cmdList];
 
 

  if (cmdLevelCounter < ((uint16)eMaxCmdLevel))
  {   
    cmdLevelCounter++;
    
    for (Idx = 0; Idx < IdxMax; Idx++)
    {
      if(usedLevel->id == cmdID)
      {
        if(   ( usedLevel->loginRequested == TRUE )
           && ( boLoginActivated == FALSE) )
        {
          ResponseCode = 0x7Fu;  /*DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION*/
        }
        else
        {
          if (cmdList != usedLevel->level) //usedLevel->function == nullptr)
          {
            ComBuf_GetMsgContext(APPL_USED_COMBUF_ID, (uint8_t) cmdLevelCounter, &cmdID, pMsgContext);
            // PRQA S 3670 1 // architecture design
            ResponseCode = AppCmd_Execute(cmdID, usedLevel->level, pMsgContext );
          }
          else
          {
            ResponseCode = usedLevel->function(pMsgContext);
          }
          
        }
        break;
      }
      usedLevel++;
    }  
    cmdLevelCounter--;

    if (ResponseCode == 0U)
    {
      ComBuf_TxPosResp(APPL_USED_COMBUF_ID, (uint8) cmdLevelCounter, cmdID, pMsgContext);
    }

  }

  return ResponseCode;
}
// PRQA L:L_STMIF

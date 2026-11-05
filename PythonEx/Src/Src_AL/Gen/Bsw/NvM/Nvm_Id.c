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
/// \file  Nvm_Id.c
///
/// \brief
///
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
//-------------------------------------------------------
//-----------------------------------------------------------------------------


//=============================================================================
// includes
//=============================================================================


#include <Std_Types.h>
#include <Nvm.h>
#include <Nvm_Id.h>
#include <Nvm_Internal.h>



//=============================================================================
// preprocessor definitions
//=============================================================================

#define CFG_NvmAdditionalKeyByte 0U


STATIC_AL void NvM_GetDefaultConfigBlock(tNvMConfigBlock* ConfigBlock);

//=============================================================================
// variables
//=============================================================================

Std_ReturnType NvmCheckConfigBlock(void)
{
  Std_ReturnType result;
  tNvMConfigBlock DefaultConfigBlock;
  NvM_GetDefaultConfigBlock(&DefaultConfigBlock);
 if (memcmp((void*)&DefaultConfigBlock, (void*)&NvmBlockConfigBlock, sizeof(NvmBlockConfigBlock)) != 0)
  {
    result = E_NOT_OK;
  }
  else
  {
    result = E_OK;

  }
  return result;
}


STATIC_AL void NvM_GetDefaultConfigBlock(tNvMConfigBlock* ConfigBlock)
{
    
#ifdef CFG_Develop
    static const char          strTime   [sizeof(CFG_InfoTime)] = CFG_InfoTime;        // 11+1=12 ASCII chars plus end of string terminator 
#endif
    static const char          strVersion[sizeof(CFG_InfoVersion)] = CFG_InfoVersion;     // 10+1=11 ASCII chars plus end of string terminator
    (void)memcpy( (void*)  ConfigBlock->strVersion,(void*) strVersion, sizeof(NvmBlockConfigBlock.strVersion) ); // PRQA S 311 1   //program architecture and readability
    ConfigBlock->reserved = 0;
// Make sure, that ALL elements are initialized    
 #ifdef CFG_Develop
    ConfigBlock->aucKeyBytes[0] = (uint8) strTime[3];
    ConfigBlock->aucKeyBytes[1] = (uint8) strTime[4];
    ConfigBlock->aucKeyBytes[2] = (uint8) strTime[6];
    ConfigBlock->aucKeyBytes[3] = (uint8) strTime[7];
#else
    ConfigBlock->aucKeyBytes[0] = 0U;
    ConfigBlock->aucKeyBytes[1] = 0U;
    ConfigBlock->aucKeyBytes[2] = 0U;
    ConfigBlock->aucKeyBytes[3] = 0U;
#endif

}


void Nvm_InitConfigBlock(void)
{
  NvM_GetDefaultConfigBlock(&NvmBlockConfigBlock);
}




//tNvmBlockdescriptor NvMBlockTable[NvMBlockCount] = 
//=============================================================================
// prototypes
//=============================================================================








